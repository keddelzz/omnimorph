#include "StringBuilder.h"

#include "Utils.h"

StringBuilder::StringBuilder()
{
    ensureCapacity(1024);
}

void StringBuilder::ensureCapacity(u64 newCapacity)
{
    if (newCapacity > capacity) {
        newCapacity = Utils::nextPot(newCapacity);
        while (newCapacity < capacity) newCapacity <<= 1;

        if (newCapacity > capacity) {
            void *newData = nullptr;
            if (data == nullptr) {
                newData = malloc(sizeof(u8) * newCapacity);
            } else {
                newData = realloc(data, sizeof(u8) * newCapacity);
            }
            data = static_cast<u8 *>(newData);
            capacity = newCapacity;
        }
    }
}

StringBuilder &StringBuilder::append(u8 c)
{
    u8 x = c;
    String temp;
    temp.owned = false;
    temp.data = &x;
    temp.length = 1;
    return append(temp);
}

StringBuilder &StringBuilder::append(const String &string)
{
    ensureCapacity(length + string.length);
    memcpy(&data[length], string.data, string.length);
    length += string.length;
    return *this;
}

String StringBuilder::toString()
{
    String result;
    result.owned = true;
    result.length = length;
    result.data = data;

    length = 0;
    capacity = 0;
    data = nullptr;

    return result;
}
