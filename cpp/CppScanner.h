#pragma once

#include "ScannerDriver.h"

namespace cpp {

class CppScanner
    : public ScannerDriver
{

public:
    explicit CppScanner() = default;
    void initialize(std::string fileName, std::vector<u8> fileContents) final;
    void initialize(std::vector<u8> fileContents) final;

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
