#include <iostream>

#include "../../api/Generic.h"
#include "Vec2i.h"
#include "Vec2i.h.generic"
#include "Fid.h"
#include "Fid.h.generic"
#include "Nested.h"
#include "Nested.h.generic"

// @TODO: Can we somehow make CMake include the generic representation, if the
//        type is included?

void gclear(int *value) { *value = 0; }
void gclear(float *value) { *value = 0; }
void gclear(double *value) { *value = 0; }
void gclear(bool *value) { *value = false; }

void gclear_elements(HNil) {}
template<typename H, typename T>
void gclear_elements(HList<H *, T> &list)
{
    gclear(list.head);
    gclear_elements(list.tail);
}

template<typename T>
void gclear(T *value)
{
    auto repr = PointerGeneric<T>::to(*value);
    gclear_elements(repr);
}

std::ostream &operator<<(std::ostream &stream, const Vec2i &v)
{ return stream << "Vec2i(" << v.x << ", " << v.y << ")"; }
std::ostream &operator<<(std::ostream &stream, const Fid &f)
{ return stream << "Fid(" << f.f << ", " << f.i << ", " << f.d << ")"; }
std::ostream &operator<<(std::ostream &stream, const Nested &f)
{ return stream << "Nested(" << f.flag << ", " << f.fid << ", " << f.vec << ")"; }

template<typename T>
void printClearPrint(T &value)
{
    std::cout << value << std::endl;
    gclear(&value);
    std::cout << value << std::endl << std::endl;
}

int main() {
    std::cout << "Hello, generic-clear" << std::endl;

    int x = 5;
    printClearPrint(x);

    Vec2i v{13, 37};
    Fid f{13.37, 42, 55.6789101112};
    Nested nest{true, f, v};

    printClearPrint(v);
    printClearPrint(f);
    printClearPrint(nest);

    return EXIT_SUCCESS;
}