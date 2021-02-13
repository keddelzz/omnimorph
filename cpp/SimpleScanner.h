#pragma once

#include "ScannerDriver.h"

class SimpleScanner
    : public ScannerDriver
{

public:
    static SimpleScanner *fromString(std::string string);

protected:
    State startState() const final;
    State errorState() const final;
    bool isErrorState(State state) const final;
    bool isAcceptingState(State state) const final;
    TokenType tokenType(State state) const final;
    State nextState(State state, Char c) const final;

private:
    explicit SimpleScanner(
        std::string fileName,
        std::vector<u8> fileContents
    );

    State advance_0(ScannerDriver::Char c) const;
    State advance_1(ScannerDriver::Char c) const;
    State advance_2(ScannerDriver::Char c) const;
    State advance_3(ScannerDriver::Char c) const;
    State advance_4(ScannerDriver::Char c) const;
    State advance_5(ScannerDriver::Char c) const;
    State advance_6(ScannerDriver::Char c) const;
    State advance_7(ScannerDriver::Char c) const;

};
