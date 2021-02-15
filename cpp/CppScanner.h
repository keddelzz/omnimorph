#pragma once

#include "ScannerDriver.h"

namespace cpp {

class CppScanner
    : public ScannerDriver
{

public:
    explicit CppScanner(
        std::string fileName,
        std::vector<u8> fileContents
    );
    explicit CppScanner(std::vector<u8> fileContents);

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
