#include "FileUtils.h"

#include <fstream>
#include <cstring>

namespace cpp {

String FileUtils::readEntireFile(const String &filePath)
{
    // @Cleanup
    std::string stdFilePath(filePath.length, '\0');
    memcpy(stdFilePath.data(), filePath.data, filePath.length);

    std::ifstream stream(stdFilePath);
    stream.seekg(0, std::ios::end);
    const auto size = u64(stream.tellg());

    String result(size);
    stream.seekg(0);
    stream.read(reinterpret_cast<char *>(result.data), size);
    result.length = strlen(reinterpret_cast<const char *>(result.data));

    return result;
}

void FileUtils::writeEntireFile(const String &filePath, const String &fileContents)
{
    // @Cleanup
    std::string stdFilePath(filePath.length, '\0');
    memcpy(stdFilePath.data(), filePath.data, filePath.length);

    std::ofstream stream(stdFilePath);
    stream.write(reinterpret_cast<char *>(fileContents.data), fileContents.length);

    stream.flush();
    stream.close();
}

}
