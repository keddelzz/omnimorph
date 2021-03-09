#include "Show.h"

namespace json {

void Show::makeIndentation(StringBuilder &buffer, int level)
{
    const String singleIndentation("  ");
    while (level > 0) {
        buffer.append(singleIndentation);
        --level;
    }
}

void Show::json(StringBuilder &buffer, const Value &value, int level)
{
    switch (value.type()) {
        case Value::Type::Null: buffer.append("null"); break;
        case Value::Type::Undefined: buffer.append("undefined"); break;
        case Value::Type::Bool: buffer.append(value.asBool() ? "true" : "false"); break;
        case Value::Type::Int: buffer.append(value.asInt()); break;
        case Value::Type::Float: buffer.append(value.asFloat()); break;
        case Value::Type::String:
            // @NOTE: This is an example, so no escaping happens
            buffer.append('"').append(value.asString()).append('"'); break;

        case Value::Type::Array:  {
            buffer.append("[\n");

            const auto &array = value.asArray();
            for (uint64_t i = 0; i < array.size(); ++i) {
                makeIndentation(buffer, level + 1);
                Show::json(buffer, array[i], level + 1);

                if (i != array.size() - 1) {
                    buffer.append(',');
                }
                buffer.append('\n');
            }

            makeIndentation(buffer, level);
            buffer.append(']');
        } break;

        case Value::Type::Object: {
            buffer.append("{\n");

            const auto &object = value.asObject();
            for (uint64_t i = 0; i < object.size(); ++i) {
                const auto &key = object.key(i);
                const auto &value = object[key];

                makeIndentation(buffer, level + 1);
                Show::json(buffer, key, level + 1);
                buffer.append(" : ");
                Show::json(buffer, value, level + 1);

                if (i != object.size() - 1) {
                    buffer.append(',');
                }
                buffer.append('\n');
            }

            makeIndentation(buffer, level);
            buffer.append('}');
        } break;

        default:
            assert(false);
            break;
    }
}

}
