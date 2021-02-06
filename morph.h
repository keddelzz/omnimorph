#pragma once

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
        using SGen = CopyGeneric<Source>;
        using TGen = CopyGeneric<Target>;
        using SRep = typename SGen::Repr;
        using TRep = typename TGen::Repr;
        static_assert(
                std::is_same_v<SRep, TRep>,
                "In order to morph two types their representations have to be the same!"
        );

        const auto repr = SGen::to(source);
        return TGen::from(repr);
    }
private:
    const Source &source;
};

/*
int main() {
    SimpleAddress a("Nullptr Street", 55);
    TestPerson b("Simon Segfault", a, 42);
    Vec3 t(1, 2, 3);
    Vac3 u(9, 8, 7);

    auto x = Morpher(t).morph<Vac3>();

    std::cout
        << show(a) << std::endl
        << show(b) << std::endl
        << show(t) << std::endl
        << show(u) << std::endl
        << show(x) << std::endl
        ;

    return EXIT_SUCCESS;
}
 */