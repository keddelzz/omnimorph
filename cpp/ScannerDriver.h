#pragma once

#include <string>
#include <vector>

#include "Token.h"

namespace cpp {

class ScannerDriver
{

public:
    virtual ~ScannerDriver() = default;
    bool hasNext();
    Token next();

protected:
    explicit ScannerDriver(
        std::string fileName,
        std::vector<u8> fileContents
    );

    using Char = s32;

    using State = s32;
    virtual State startState() const = 0;
    virtual State errorState() const = 0;
    virtual bool isErrorState(State state) const = 0;
    virtual bool isAcceptingState(State state) const = 0;
    virtual TokenType tokenType(State state) const = 0; // iff isAcceptingState(state), which token does it recognize
    virtual State nextState(State state, Char c) const = 0;

    template<typename T>
    static bool between(T min, T value, T max)
    {
        return min <= value and value <= max;
    }

private:
    bool hasCharacter() const;
    Char nextCharacter();

    void rememberRecoveryPoint();
    void restoreRecoveryPoint();
    Token scanNextToken();

private:
    std::string     m_fileName;
    std::vector<u8> m_fileContents;

    bool  m_scanError { false };
    bool  m_eofReturned { false };
    bool  m_errorReturned { false };
    bool  m_haveNextToken { false };
    Token m_nextToken { };

    State m_currentState;
    State m_lastAcceptingState;

    s64 m_currentOffset { -1 }; // offset into memory
    s64 m_startOffset;          // offset into memory
    s64 m_endOffset;            // offset into memory

    FilePosition m_currentPosition { 0, 0 };    // line:column in file
    FilePosition m_startAccepting;     // line:column in file
    FilePosition m_endAccepting;       // line:column in file

};

}
