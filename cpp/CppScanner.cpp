#include "CppScanner.h"

CppScanner::CppScanner(
    std::string fileName,
    std::vector<u8> fileContents)
    : ScannerDriver(std::move(fileName), std::move(fileContents))
{}

CppScanner *CppScanner::fromString(std::string string)
{
    std::vector<u8> fileContents(string.size());
    memcpy(fileContents.data(), string.data(), string.size());
    return new CppScanner("<string>", fileContents);
}

#include "CppScanner.cpp.fsm"
