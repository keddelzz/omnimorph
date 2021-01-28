#include <iostream>
#include <functional>

#include "flatfunction.h"
#include "hlist.h"
#include "generic.h"
//#include "show.h"

/*
template<typename T>
struct ShowG
{
    constexpr ShowG() = default;
    std::string show(T value) {
        Show<typename Generic<T>::Repr> r;
        auto repr = to_repr<T>(value);
        return r.show(repr);
    }
};
*/
struct SimpleAddress
{
public:
    SimpleAddress(const char *street_name, int house_number)
        : street_name(street_name)
        , house_number(house_number)
    {}

    const char *street_name;
    int house_number;
};

using SimpleAddress_Repr_2 = HNil;
using SimpleAddress_Repr_1 = HList<int, SimpleAddress_Repr_2>;
using SimpleAddress_Repr_0 = HList<const char *, SimpleAddress_Repr_1>;
using SimpleAddress_Repr   = SimpleAddress_Repr_0;
SimpleAddress_Repr Generic_SimpleAddress_to(const SimpleAddress &p) {
    auto tl = SimpleAddress_Repr_1(p.house_number, {});
    return SimpleAddress_Repr(p.street_name, tl);
};
SimpleAddress Generic_SimpleAddress_from(const SimpleAddress_Repr &r) {
    return SimpleAddress(r.head, r.tail.head);
};

template<>
struct Generic<SimpleAddress>
{
    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;
    constexpr Generic() = default;
    FlatFunction to   { Generic_SimpleAddress_to };
    FlatFunction from { Generic_SimpleAddress_from };
};

class TestPerson
{
public:
    TestPerson(const char *name, const SimpleAddress &address, int age)
        : name(name)
        , address(address)
        , age(age)
    {}

    const char *name;
    SimpleAddress address;
    int age;
};

using TestPerson_Repr_3 = HNil;
using TestPerson_Repr_2 = HList<int, TestPerson_Repr_3>;
using TestPerson_Repr_1 = HList<SimpleAddress, TestPerson_Repr_2>;
using TestPerson_Repr_0 = HList<const char *, TestPerson_Repr_1>;
using TestPerson_Repr   = TestPerson_Repr_0;
TestPerson_Repr Generic_TestPerson_to(const TestPerson &p) {
    auto tl2 = TestPerson_Repr_2(p.age, {});
    auto tl1 = TestPerson_Repr_1(p.address, tl2);
    auto tl0 = TestPerson_Repr_0(p.name, tl1);
    return tl0;
};
TestPerson Generic_TestPerson_from(const TestPerson_Repr &r) {
    return TestPerson(r.head, r.tail.head, r.tail.tail.head);
};

template<>
struct Generic<TestPerson>
{
    using Type = TestPerson;
    using Repr = TestPerson_Repr;
    constexpr Generic() = default;
    FlatFunction to   { Generic_TestPerson_to };
    FlatFunction from { Generic_TestPerson_from };
};

int main() {
    constexpr const char *meh = "meh";
    auto test = hlist(1, 2, std::string(meh));
    std::cout << hlist() << std::endl;
    std::cout << test << std::endl;

    const char *streetName = "New Years Street";
    const char *name = "Peter Finger";
    SimpleAddress a(streetName, 32);
    TestPerson p(name, a, 55);

    auto x = to_repr<TestPerson>(p);
    auto b = to_value<TestPerson>(x);

//    std::cout << ShowG<TestPerson>().show(p) << std::endl;

    return 0;
}
