#include <vector>
#include <string>

#include "../types.h"

namespace cpp {

class FileUtils
{
public:
    static std::vector<u8> readEntireFile(const std::string& filePath);

private:
    FileUtils() {}
};

}
