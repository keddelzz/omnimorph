#include <iostream>

#include "../../api/Generic.h"
#include "Vec2i.h"
#include "Vec2i.h.generic"
#include "Fid.h"
#include "Fid.h.generic"
#include "Nested.h"
#include "Nested.h.generic"

void gprint(std::ostream &stream, int value)
{ stream << value; }
void gprint(std::ostream &stream, float value)
{ stream << value; }
void gprint(std::ostream &stream, double value)
{ stream << value; }
void gprint(std::ostream &stream, bool value)
{ stream << (value ? "true" : "false"); }

void gprint_elements(std::ostream &, bool, HNil) {}
template<typename H, typename T>
void gprint_elements(std::ostream &stream, bool first, const HList<H, T> &list)
{
    if (not first) stream << ", ";
    gprint(stream, list.head);
    gprint_elements(stream, false, list.tail);
}

template<typename T>
void gprint(std::ostream &stream, const T &value)
{
    const auto repr = CopyGeneric<T>::to(value);
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