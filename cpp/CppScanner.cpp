#include "CppScanner.h"
#include "FileUtils.h"

namespace cpp {

CppScanner::CppScanner(
    std::string fileName,
    std::vector<u8> fileContents)
    : ScannerDriver(std::move(fileName), std::move(fileContents))
{}

CppScanner::CppScanner(std::vector<u8> fileContents)
    : CppScanner("<string>", std::move(fileContents))
{}

#include "CppScanner.cpp.fsm"

}
