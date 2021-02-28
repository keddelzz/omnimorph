#include <vector>
#include <string>

#include "../data/String.h"

namespace cpp {

class FileUtils
{
public:
    static String readEntireFile(const String &filePath);
    static void writeEntireFile(const String &filePath, const String &fileContents);

private:
    FileUtils() {}
};

}
