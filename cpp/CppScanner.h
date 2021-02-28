#pragma once

#include "ScannerDriver.h"
#include "../data/String.h"

namespace cpp {

class CppScanner
    : public ScannerDriver
{

public:
    explicit CppScanner() = default;
    ~CppScanner() = default;
    void initialize(const String &fileName, const String &fileContents) final;

protected:
    State startState() const final;
    State errorState() const final;
    bool isErrorState(State state) const final;
    bool isAcceptingState(State state) const final;
    TokenType tokenType(State state) const final;
    State nextState(State state, Char c) const final;

#include "CppScanner.h.fsm"

};

}
