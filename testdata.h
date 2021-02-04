#pragma once

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
using SimpleAddress_Repr_1 = HList<Member<int>, SimpleAddress_Repr_2>;
using SimpleAddress_Repr_0 = HList<Member<const char *>, SimpleAddress_Repr_1>;
using SimpleAddress_Repr   = Class<SimpleAddress_Repr_0>;
SimpleAddress_Repr Generic_SimpleAddress_to(const SimpleAddress &p) {
    const SimpleAddress_Repr_1 tl1({"house_number", p.house_number}, {});
    const SimpleAddress_Repr_0 tl0({"street_name", p.street_name}, tl1);
    return Class("SimpleAddress", tl0);
};
SimpleAddress Generic_SimpleAddress_from(const SimpleAddress_Repr &r) {
    const auto &tl0 = r.value;
    const auto &tl1 = tl0.tail;
    return SimpleAddress(tl0.head.value, tl1.head.value);
};

template<>
struct Generic<SimpleAddress>
{
    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;
    constexpr Generic() = default;
    FlatFunction<const Type &, Repr> to   { Generic_SimpleAddress_to };
    FlatFunction<const Repr &, Type> from { Generic_SimpleAddress_from };
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
using TestPerson_Repr_2 = HList<Member<int>, TestPerson_Repr_3>;
using TestPerson_Repr_1 = HList<Member<SimpleAddress>, TestPerson_Repr_2>;
using TestPerson_Repr_0 = HList<Member<const char *>, TestPerson_Repr_1>;
using TestPerson_Repr   = Class<TestPerson_Repr_0>;
TestPerson_Repr Generic_TestPerson_to(const TestPerson &p) {
    auto tl2 = TestPerson_Repr_2({"age", p.age}, {});
    auto tl1 = TestPerson_Repr_1({"address", p.address}, tl2);
    auto tl0 = TestPerson_Repr_0({"name", p.name}, tl1);
    return Class("TestPerson", tl0);
};
TestPerson Generic_TestPerson_from(const TestPerson_Repr &r) {
    const auto &tl0 = r.value;
    const auto &tl1 = tl0.tail;
    const auto &tl2 = tl1.tail;
    return TestPerson(tl0.head.value, tl1.head.value, tl2.head.value);
};

template<>
struct Generic<TestPerson>
{
    using Type = TestPerson;
    using Repr = TestPerson_Repr;
    constexpr Generic() = default;
    FlatFunction<const Type &, Repr> to   { Generic_TestPerson_to };
    FlatFunction<const Repr &, Type> from { Generic_TestPerson_from };
};
