#define once

#include "../data/types.h"

#include "Value.h"
#include "Array.h"
#include "Object.h"

namespace json {

class Show
{
public:
    inline static void json(StringBuilder &buffer, const json::Value &value)
    {
        return Show::json(buffer, value, 0);
    }

private:
    static void makeIndentation(StringBuilder &buffer, int level);
    static void json(StringBuilder &buffer, const json::Value &value, int level);

private:
    Show() = delete;
};

}
