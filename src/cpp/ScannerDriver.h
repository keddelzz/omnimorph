#pragma once

#include <string>
#include <vector>

#include "Token.h"
#include "../data/String.h"

namespace cpp {

class ScannerDriver
{

public:
    virtual ~ScannerDriver();
    bool hasNext();
    Token next();

protected:
    explicit ScannerDriver();
    virtual void initialize(const String &fileName, const String &fileContents);

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
    union {;
        String m_fileName;
    };
    union {
        String m_fileContents;
    };

    bool  m_scanError { false };
    bool  m_eofReturned { false };
    bool  m_errorReturned { false };
    bool  m_haveNextToken { false };
    Token m_nextToken { };

    State m_currentState { -1 };
    State m_lastAcceptingState { -1 };

    s64 m_currentOffset { -1 }; // offset into memory
    s64 m_startOffset { -1 };   // offset into memory
    s64 m_endOffset  { -1 };    // offset into memory

    FilePosition m_currentPosition { 0, 0 };    // line:column in file
    FilePosition m_startAccepting;     // line:column in file
    FilePosition m_endAccepting;       // line:column in file

};

}
