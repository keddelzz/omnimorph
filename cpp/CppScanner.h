#pragma once

#include "ScannerDriver.h"

class CppScanner
    : public ScannerDriver
{

public:
    static CppScanner *fromString(std::string string);
    static CppScanner *fromFile(std::string filePath);

protected:
    State startState() const final;
    State errorState() const final;
    bool isErrorState(State state) const final;
    bool isAcceptingState(State state) const final;
    TokenType tokenType(State state) const final;
    State nextState(State state, Char c) const final;

private:
    explicit CppScanner(
        std::string fileName,
        std::vector<u8> fileContents
    );

#include "CppScanner.h.fsm"

};
