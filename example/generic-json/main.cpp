#include <iostream>

#include "data/types.h"
#include "data/Validated.h"

#include "json/Value.h"
#include "json/Array.h"
#include "json/Object.h"
#include "json/Show.h"

#include "Individual.h"
#include "Individual.h.generic"

#include "../common/Fid.h"
#include "../common/Fid.h.generic"
#include "../common/Vec2i.h"
#include "../common/Vec2i.h.generic"
#include "../common/Nested.h"
#include "../common/Nested.h.generic"

std::ostream &operator<<(std::ostream &stream, const Vec2i &v)
{ return stream << "Vec2i(" << v.x << ", " << v.y << ")"; }
std::ostream &operator<<(std::ostream &stream, const Fid &f)
{ return stream << "Fid(" << f.f << ", " << f.i << ", " << f.d << ")"; }
std::ostream &operator<<(std::ostream &stream, const Nested &f)
{ return stream << "Nested(" << f.flag << ", " << f.fid << ", " << f.vec << ")"; }
template<typename T>
std::ostream &operator<<(std::ostream &stream, const List<T> &l)
{
    stream << "List(";
    for (uint64_t i = 0; i < l.length; ++i) {
        stream << l[i];
        if (i < l.length - 1) {
            stream << ", ";
        }
    }
    return stream << ")";
}
std::ostream &operator<<(std::ostream &stream, const Individual &i)
{ return stream << "Individual(" << i.name << ", " << i.age << ", " << i.pets << ")"; }

json::Value jsonTestIndividual()
{
    json::Object root;
    root.insert("_type", String("Individual"));
    root.insert("name", String("Simon Segfault"));
    root.insert("age", int64_t(42));

    json::Array pets;
    pets.append(String("cat"));
    pets.append(String("dog"));
    root.insert("pets", pets);

    return root;
}

Individual testIndividual()
{
    Individual individual;
    individual.name = "Nicole Nullpointer";
    individual.age = 0xC0FFEE;
    individual.pets.append("fish");
    return individual;
}

String showJson(const json::Value &json)
{
    StringBuilder buffer;
    json::Show::json(buffer, json);
    return buffer.toString();
}

void printJson(const json::Value &json)
{
    std::cout << showJson(json) << std::endl;
}

json::Value to_json(bool value) { return json::Value(value); }
json::Value to_json(int value) { return json::Value(int64_t(value)); }
json::Value to_json(float value) { return json::Value(value); }
json::Value to_json(double value) { return json::Value(value); }
json::Value to_json(const String &value) { return json::Value(value); }
template<typename T>
json::Value to_json(const List<T> &value)
{
    json::Array array;
    for (uint64_t i = 0; i < value.length; ++i) {
        array.append(to_json(value[i]));
    }
    return json::Value(array);
}

void to_json_members(json::Object &object, const HNil &) {}
template<typename Head, typename Tail>
void to_json_members(json::Object &object, const HList<Named<const Head&>, Tail> &members)
{
    const auto &member = members.head;
    object.insert(member.name, to_json(member.value));
    to_json_members(object, members.tail);
}

template<typename T>
json::Value to_json(const T &value)
{
    using Generic = ConstReferenceLabelledGeneric<T>;
    const auto repr = Generic::to(value);

    json::Object object;
    object.insert("_type", String(Generic::name));
    to_json_members(object, repr);
    return json::Value(object);
}

template<typename T>
using Val = Validated<String, T>;

void from_json(const json::Value &json, Val<bool> &out)
{
    if (not json.isBool()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not a bool!");
        out = Val<bool>::failure(message.toString());
        return;
    }

    out = Val<bool>::success(json.asBool());
}
void from_json(const json::Value &json, Val<int> &out)
{
    if (not json.isInt()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not an integer!");
        out = Val<int>::failure(message.toString());
        return;
    }

    out = Val<int>::success(json.asInt());
}
void from_json(const json::Value &json, Val<float> &out)
{
    if (not json.isFloat()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not a float!");
        out = Val<float>::failure(message.toString());
        return;
    }

    out = Val<float>::success(json.asFloat());
}
void from_json(const json::Value &json, Val<double> &out)
{
    if (not json.isFloat()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not a double!");
        out = Val<double>::failure(message.toString());
        return;
    }

    out = Val<double>::success(json.asFloat());
}
void from_json(const json::Value &json, Val<String> &out)
{
    if (not json.isString()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not a string!");
        out = Val<String>::failure(message.toString());
        return;
    }

    auto string = json.asString();
    out = Val<String>::success(std::move(string));
}

template<typename T>
void from_json(const json::Value &json, Val<List<T>> &out)
{
    if (not json.isArray()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not an array!");
        out = Val<List<T>>::failure(message.toString());
        return;
    }

    const auto &array = json.asArray();
    List<T> result;

    for (uint64_t i = 0; i < array.size(); ++i) {
        const auto &value = array[i];

        auto validatedT = Val<T>::failure("");
        from_json(value, validatedT);

        if (validatedT.hasError()) {
            // @TODO: Print 'xth element couldn't be dejsonified'
            out = Val<List<T>>::failure(validatedT.error());
            return;
        }

        result.append(validatedT.value());
    }

    out = Val<List<T>>::success(std::move(result));
}

template<typename T>
Val<T> from_json_members(T &result, const json::Object &object, HNil &)
{
    return Val<T>::success(std::move(result));
}
template<typename T, typename Head, typename Tail>
Val<T> from_json_members(T &result, const json::Object &object, HList<Named<Head &>, Tail> &members)
{
    const auto &member = members.head;

    const String memberName(member.name);
    if (not object.contains(memberName)) {
        StringBuilder message;
        message.append('\'').append(showJson(object)).append("' doesn't contain member '").append(memberName).append("'!");
        return Val<T>::failure(message.toString());
    }

    auto validatedHead = Val<Head>::failure("");
    from_json(object[memberName], validatedHead);

    if (validatedHead.hasError()) {
        // @TODO: Print element '...' couldn't be dejsonified'
        return Val<T>::failure(std::move(validatedHead.error()));
    }
    member.value = validatedHead.value();

    return from_json_members(result, object, members.tail);
}

template<typename T>
void from_json(const json::Value &json, Val<T> &out)
{
    using Generic = ReferenceLabelledGeneric<T>;

    if (not json.isObject()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is not an object!");
        out = Val<T>::failure(message.toString());
        return;
    }
    const auto &object = json.asObject();

    if (not object.contains("_type") or not object["_type"].isString()) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' doesn't have a field '_type' of type string!");
        out = Val<T>::failure(message.toString());
        return;
    }
    const auto &actualType = object["_type"].asString();
    const String expectType(Generic::name);

    if (expectType != actualType) {
        StringBuilder message;
        message.append('\'').append(showJson(json)).append("' is of type '")
            .append(actualType).append("' but is required to be of type '")
            .append(expectType).append("'!");
        out = Val<T>::failure(message.toString());
        return;
    }

    T result;
    auto repr = Generic::to(result);
    out = from_json_members(result, object, repr);
}

int main() {
    std::cout << "Hello, generic-json" << std::endl;

    const auto individual = testIndividual();
    const auto jsonIndividual = to_json(individual);
    printJson(jsonIndividual);

    const auto jsonIndividual2 = jsonTestIndividual();

    auto validated = Val<Individual>::failure("");
    from_json(jsonIndividual2, validated);

    if (validated.hasValue()) {
        std::cout << "value: " << validated.value();
    } else {
        std::cout << "error: " << validated.error();
    }

    return EXIT_SUCCESS;
}
