#include <iostream>
#include <vector>

#include "testdata.h"
#include "hasmember.h"
#include "show.h"

/*
template<typename Source>
class Morpher
{
public:
    explicit constexpr Morpher(const Source &source)
        : source(source)
    {}

    template<typename Target>
    Target morph()
    {
        using SGen = Generic<Source>;
        using TGen = Generic<Target>;
        using SMbs = typename SGen::Members;
        using TMbs = typename TGen::Members;
        using SRep = typename SGen::Repr;
        using TRep = typename TGen::Repr;
        static_assert(
            std::is_same_v<SMbs, TMbs>,
            "In order to morph two types their representations have to be the same!"
        );

        const auto repr = SGen::to(source).members;
        return TGen::from(TRep(nullptr, repr));
    }
private:
    const Source &source;
};
*/

int main() {
    SimpleAddress a("Nullptr Street", 55);
    TestPerson b("Simon Segfault", a, 42);
    Vec3 t(1, 2, 3);
    Vac3 u(9, 8, 7);

    std::cout
        << show(a) << std::endl
        << show(b) << std::endl
        << show(t) << std::endl
        << show(u) << std::endl
        ;

    return EXIT_SUCCESS;
}

// @TODO: Does the assemble work?
// @TODO: Do we need an Generic instance for std::move?
// @TODO: Try out inductive datastructures
// @TODO: Going constexpr
// @TODO: Const versions of reference and pointer generic-instances
