#include "CppScanner.h"

#include "FileUtils.h"

namespace cpp {

void CppScanner::initialize(const String &fileName, const String &fileContents)
{
    ScannerDriver::initialize(fileName, fileContents);
}

#include "CppScanner.cpp.fsm"

}
