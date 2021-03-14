#include <iostream>

#include <omnimorph/Generic.h>
#include <omnimorph/predicates/StdStreamable.h>
#include <vector>

#include "../common/Vec2i.h"
#include "../common/Vec2i.h.generic"
#include "../common/Fid.h"
#include "../common/Fid.h.generic"
#include "../common/Nested.h"
#include "../common/Nested.h.generic"

void gprint_elements(std::ostream &, bool, const HNil &) {}
template<typename H, typename T>
void gprint_elements(std::ostream &stream, bool first, const HList<Named<const H &>, T> &list)
{
    if (not first) stream << ", ";
    stream << list.head.name << " = " << list.head.value;
    gprint_elements(stream, false, list.tail);
}

template<typename T,
        typename = std::enable_if_t<not OStreamable<T>, void>>
std::ostream &operator<<(std::ostream &stream, const T &value)
{
    using Generic = ConstReferenceLabelledGeneric<T>;
    const auto repr = Generic::to(value);
    stream << Generic::name << std::string("(");
    gprint_elements(stream, true, repr);
    stream << ')';
    return stream;
}

int main() {
    std::cout << "Hello, generic-printer" << std::endl;

    std::cout << 55 << std::endl;

    const Vec2i v{13, 37};
    std::cout << v << std::endl;

    const Fid f{13.37, 42, 55.6789101112};
    std::cout << f << std::endl;

    const Nested nest{true, f, v};
    std::cout << nest << std::endl;

    return EXIT_SUCCESS;
}