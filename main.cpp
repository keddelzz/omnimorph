#include <iostream>
#include <vector>

#include "testdata.h"
#include "hasmember.h"

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

class Tst {
    uint8_t asd[5000];
};

class Muh {
public:
    const char *name;
    Tst asd;
    const char *name2;
};

int main() {
//    const auto kek = Morpher(Vec3(1, 2, 3)).morph<Vac3>();

    const auto x = member_of(Vec3, x);
    const auto y = member_of(Vec3, y);
    const auto z = member_of(Vec3, z);
    const auto w = member_of(Muh, asd);

    return EXIT_SUCCESS;
}

// @TODO: Does the assemble work?
// @TODO: Do we need an Generic instance for std::move?
// @TODO: Try out inductive datastructures
// @TODO: Going constexpr
