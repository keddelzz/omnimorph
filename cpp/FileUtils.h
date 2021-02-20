#include <vector>
#include <string>

#include "../data/String.h"

namespace cpp {

class FileUtils
{
public:
    static String readEntireFile(const String &filePath);

private:
    FileUtils() {}
};

}
