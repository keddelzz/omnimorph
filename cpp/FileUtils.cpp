#include "FileUtils.h"

#include <fstream>

namespace cpp {

std::vector<u8> FileUtils::readEntireFile(const std::string &filePath)
{
    std::ifstream stream(filePath);
    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();

    std::string buffer(size, ' ');
    stream.seekg(0);
    stream.read(&buffer[0], size);

    std::vector<u8> fileContents(buffer.size());
    memcpy(fileContents.data(), buffer.data(), buffer.size());
    return std::move(fileContents);
}

}
