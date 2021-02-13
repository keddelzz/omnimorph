#include "ScannerDriver.h"

#include <cassert>
#include <cstring>

ScannerDriver::ScannerDriver(
    std::string fileName,
    std::vector<u8> fileContents)
    : m_fileName(std::move(fileName))
    , m_fileContents(std::move(fileContents))
{
    if (not m_fileContents.empty())
        m_currentOffset = 0;
}

bool ScannerDriver::hasNext()
{
    if (not m_haveNextToken) {
        m_nextToken = scanNextToken();
        if (not m_nextToken.isNullToken()) {
            m_haveNextToken = true;
        }
    }

    if (m_errorReturned) return false;
    if (m_scanError)     return true;

    return m_haveNextToken || not m_eofReturned;
}

Token ScannerDriver::next()
{
    if (not m_haveNextToken and not hasNext()) {
        assert(false);
    }

    if (m_scanError) {
        m_errorReturned = true;
        const FileRange range(m_fileName, m_currentPosition, m_currentPosition);
        static const char *errorLexemeString = "<error>";
        static const auto start = reinterpret_cast<const u8 *>(errorLexemeString);
        static const auto end = start + strlen(errorLexemeString);
        static const Lexeme errorLexeme(start, end);
        return Token(TokenType::Error, errorLexeme, range);
    }

    if (m_haveNextToken) {
        m_haveNextToken = false;
        return m_nextToken;
    }

    static const char *eofLexemeString = "<eof>";
    static const auto start = reinterpret_cast<const u8 *>(eofLexemeString);
    static const auto end = start + strlen(eofLexemeString);
    static const Lexeme eofLexeme(start, end);
    m_eofReturned = true;
    auto position = m_endAccepting;
    position.column + 1;
    const FileRange range(m_fileName, position, position);
    return Token(TokenType::Eof, eofLexeme, range);
}

bool ScannerDriver::hasCharacter() const
{
    return between<s64>(0, m_currentOffset, m_fileContents.size() - 1);
}

ScannerDriver::Char ScannerDriver::nextCharacter()
{
    assert(hasCharacter());

    const auto c = m_fileContents[m_currentOffset];
    ++m_currentOffset;

    if ('\n' == c) {
        ++m_currentPosition.line;
        m_currentPosition.column = 0;
    } else {
        ++m_currentPosition.column;
    }

    return c;
}

void ScannerDriver::rememberRecoveryPoint()
{
    if (isAcceptingState(m_currentState)) {
        m_lastAcceptingState = m_currentState;
        m_endOffset = m_currentOffset;
        m_endAccepting = m_currentPosition;
    }
}

void ScannerDriver::restoreRecoveryPoint()
{
    m_currentState = m_lastAcceptingState;
    m_currentOffset = m_endOffset;
    m_currentPosition = m_endAccepting;
}

Token ScannerDriver::scanNextToken()
{
    m_currentState = startState();
    m_lastAcceptingState = errorState();
    m_startOffset = m_currentOffset;
    m_startAccepting = m_currentPosition;

    rememberRecoveryPoint();
    while (not isErrorState(m_currentState) && hasCharacter()) {
        const auto c   = nextCharacter();
        m_currentState = nextState(m_currentState, c);
        rememberRecoveryPoint();
    }

    if (not isErrorState(m_lastAcceptingState)) {
        const auto type = tokenType(m_lastAcceptingState);
        restoreRecoveryPoint();

        const Lexeme lexeme(
            m_fileContents.data() + m_startOffset,
            m_fileContents.data() + m_endOffset
        );
        const auto &start = m_startAccepting;
        const auto &end = m_endAccepting;
        const FileRange range(m_fileName, start, end);
        return Token(type, lexeme, range);
    } else {
        if (isErrorState(m_currentState)) {
            m_scanError = true;
        }
        return Token();
    }
}
