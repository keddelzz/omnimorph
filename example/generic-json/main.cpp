#include <iostream>

#include "data/types.h"

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
    root.insert("type", String("Individual"));
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
int main() {
    std::cout << "Hello, generic-json" << std::endl;

    const auto individual = testIndividual();
    const auto jsonIndividual = to_json(individual);
    printJson(jsonIndividual);

    const Fid fid { 13.37f, 55, 42.1337 };
    const auto jsonFid = to_json(fid);

    return EXIT_SUCCESS;
}
