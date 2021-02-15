#include "CppScanner.h"

#include "FileUtils.h"

namespace cpp {

void CppScanner::initialize(std::string fileName, std::vector<u8> fileContents)
{
    ScannerDriver::initialize(fileName, fileContents);
}

void CppScanner::initialize(std::vector<u8> fileContents)
{
    ScannerDriver::initialize(fileContents);
}

#include "CppScanner.cpp.fsm"

}
