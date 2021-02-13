#include "SimpleScanner.h"

SimpleScanner::SimpleScanner(
    std::string fileName,
    std::vector<u8> fileContents)
    : ScannerDriver(std::move(fileName), std::move(fileContents))
{}

SimpleScanner *SimpleScanner::fromString(std::string string)
{
    std::vector<u8> fileContents(string.size());
    memcpy(fileContents.data(), string.data(), string.size());
    return new SimpleScanner("<string>", fileContents);
}

ScannerDriver::State SimpleScanner::startState() const
{
    return 0;
}

ScannerDriver::State SimpleScanner::errorState() const
{
    return -1;
}

bool SimpleScanner::isErrorState(ScannerDriver::State state) const
{
    return state < 0;
}

bool SimpleScanner::isAcceptingState(ScannerDriver::State state) const
{
    return between<State>(1, state, 7);
}

TokenType SimpleScanner::tokenType(ScannerDriver::State state) const
{
    switch (state) {
        case 0 : return TokenType::Error;
        case 1 : return TokenType::White;
        case 2 : return TokenType::LPar;
        case 3 : return TokenType::RPar;
        case 4 : return TokenType::Star;
        case 5 : return TokenType::Plus;
        case 6 : return TokenType::IntLit;
        case 7 : return TokenType::Ident;
        default: return TokenType::Error;
    }
}

ScannerDriver::State SimpleScanner::advance_0(ScannerDriver::Char c) const
{
    if (' ' == c)
        return State(1);
    if (0xD == c)
        return State(1);
    if (between<Char>(0x9, c, 0xA))
        return State(1);

    if ('(' == c)
        return State(2);
    if (')' == c)
        return State(3);

    if ('*' == c)
        return State(4);
    if ('+' == c)
        return State(5);

    if (between<Char>('0', c, '9'))
        return State(6);

    if (between<Char>('a', c, 'z'))
        return State(7);
    if (between<Char>('A', c, 'Z'))
        return State(7);
    if ('_' == c)
        return State(7);

    return errorState();
}

ScannerDriver::State SimpleScanner::advance_1(ScannerDriver::Char c) const
{
    if (' ' == c)
        return State(1);
    if (0xD == c)
        return State(1);
    if (between<Char>(0x9, c, 0xA))
        return State(1);

    return errorState();
}

ScannerDriver::State SimpleScanner::advance_2(ScannerDriver::Char c) const
{
    (void) c;
    return errorState();
}

ScannerDriver::State SimpleScanner::advance_3(ScannerDriver::Char c) const
{
    (void) c;
    return errorState();
}

ScannerDriver::State SimpleScanner::advance_4(ScannerDriver::Char c) const
{
    (void) c;
    return errorState();
}

ScannerDriver::State SimpleScanner::advance_5(ScannerDriver::Char c) const
{
    (void) c;
    return errorState();
}

ScannerDriver::State SimpleScanner::advance_6(ScannerDriver::Char c) const
{
    if (between<Char>('0', c, '9'))
        return State(6);

    return errorState();
}

ScannerDriver::State SimpleScanner::advance_7(ScannerDriver::Char c) const
{
    if ('_' == c)
        return State(7);
    if (between<Char>('0', c, '9'))
        return State(7);
    if (between<Char>('a', c, 'z'))
        return State(7);
    if (between<Char>('A', c, 'Z'))
        return State(7);

    return errorState();
}

ScannerDriver::State SimpleScanner::nextState(ScannerDriver::State state, ScannerDriver::Char c) const
{
    switch (state) {
        case 0 : return advance_0(c);
        case 1 : return advance_1(c);
        case 2 : return advance_2(c);
        case 3 : return advance_3(c);
        case 4 : return advance_4(c);
        case 5 : return advance_5(c);
        case 6 : return advance_6(c);
        case 7 : return advance_7(c);
        default: return advance_0(c);
    }
}
