#include <iostream>

#include <omnimorph/Generic.h>

#include "../common/Vec2i.h"
#include "../common/Vec2i.h.generic"
#include "../common/Fid.h"
#include "../common/Fid.h.generic"
#include "../common/Nested.h"
#include "../common/Nested.h.generic"

void gprint(std::ostream &stream, int value)
{ stream << value; }
void gprint(std::ostream &stream, float value)
{ stream << value; }
void gprint(std::ostream &stream, double value)
{ stream << value; }
void gprint(std::ostream &stream, bool value)
{ stream << (value ? "true" : "false"); }

void gprint_elements(std::ostream &, bool, const HNil &) {}
template<typename H, typename T>
void gprint_elements(std::ostream &stream, bool first, const HList<Named<const H &>, T> &list)
{
    if (not first) stream << ", ";
    stream << list.head.name << " = ";
    gprint(stream, list.head.value);
    gprint_elements(stream, false, list.tail);
}

template<typename T>
void gprint(std::ostream &stream, const T &value)
{
    using Generic = ConstReferenceLabelledGeneric<T>;
    const auto repr = Generic::to(value);
    stream << Generic::name;
    stream << '(';
    gprint_elements(stream, true, repr);
    stream << ')';
}

int main() {
    std::cout << "Hello, generic-printer" << std::endl;

    gprint(std::cout, 55); std::cout << std::endl;

    const Vec2i v{13, 37};
    gprint(std::cout, v); std::cout << std::endl;

    const Fid f{13.37, 42, 55.6789101112};
    gprint(std::cout, f); std::cout << std::endl;

    const Nested nest{true, f, v};
    gprint(std::cout, nest); std::cout << std::endl;

    return EXIT_SUCCESS;
}