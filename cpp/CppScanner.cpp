#include "CppScanner.h"

#include <fstream>
#include <sstream>

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

CppScanner *CppScanner::fromFile(std::string filePath)
{
    std::ifstream t(filePath);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();

    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size);

    std::vector<u8> fileContents(buffer.size());
    memcpy(fileContents.data(), buffer.data(), buffer.size());

    return new CppScanner(std::move(filePath), fileContents);
}

#include "CppScanner.cpp.fsm"
