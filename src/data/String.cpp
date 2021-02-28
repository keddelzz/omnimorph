#include "String.h"

#include <ostream>
#include <cstring>
#include <cassert>

String::String(u64 length)
{
    String::initialize(*this, nullptr, length, true);
}

String::String(char *string, s64 length)
{
    String::initialize(*this, string, length, true);
}

String::String(const char *string, s64 length)
{
    String::initialize(*this, string, length, false);
}

String::~String()
{
    if (owned) {
        // @malloc @free
        free(data);
        owned = false;
        length = 0;
        data = nullptr;
    }
}

String::String(const String &other)
{
    String::initialize(*this, reinterpret_cast<const char *>(other.data), other.length, other.owned);
}

void String::initialize(String &string, const char *str, s64 length, bool own)
{
    if (length < 0 and str != nullptr) {
        length = strlen(str);
    }
    string.length = length;

    if (own) {
        string.owned = length > 0;
        string.data = nullptr;
        
        if (string.owned) {
            const auto byteSize = sizeof(u8) * length;
            // @malloc @free
            string.data = reinterpret_cast<u8 *>(malloc(byteSize + 1));
            memset(string.data, 0, byteSize + 1);

            if (str != nullptr) {
                memcpy(string.data, str, byteSize);
            }
        }
    } else {
        string.owned = false;
        string.data = const_cast<u8 *>(reinterpret_cast<const u8 *>(str));
    }
}

bool String::operator==(const String &other) const
{
    if (length != other.length) return false;
    if (data == other.data) return true;

    for (auto i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) return false;
    }

    return true;
}

std::ostream &operator<<(std::ostream &stream, const String &string)
{
    return stream.write(reinterpret_cast<char *>(string.data), string.length);
}
