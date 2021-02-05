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
using SimpleAddress_Repr   = Class<SimpleAddress, SimpleAddress_Repr_0>;
template<>
struct Generic<SimpleAddress>
{
    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;
    constexpr Generic() = default;
    static Repr to(const Type &value) {
        constexpr SimpleAddress_Repr_1 tl1(member_of(SimpleAddress, house_number), {});
        constexpr SimpleAddress_Repr_0 tl0(member_of(SimpleAddress, street_name), tl1);
        return SimpleAddress_Repr("SimpleAddress", FlatPointer(&value), tl0);
    };
    static Type from(const Repr &repr) {
        const auto &tl0 = repr.members;
        const auto &tl1 = tl0.tail;
        return SimpleAddress(
            *tl0.head.of(repr.base),
            *tl1.head.of(repr.base)
        );
    }
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
using TestPerson_Repr   = Class<TestPerson, TestPerson_Repr_0>;
template<>
struct Generic<TestPerson>
{
    using Type = TestPerson;
    using Repr = TestPerson_Repr;
    constexpr Generic() = default;
    static Repr to(const Type &value) {
        constexpr auto tl2 = TestPerson_Repr_2(member_of(TestPerson, age), {});
        constexpr auto tl1 = TestPerson_Repr_1(member_of(TestPerson, address), tl2);
        constexpr auto tl0 = TestPerson_Repr_0(member_of(TestPerson, name), tl1);
        return TestPerson_Repr("TestPerson", FlatPointer(&value), tl0);
    }
    static Type Generic_TestPerson_from(const Repr &repr) {
        const auto &tl0 = repr.members;
        const auto &tl1 = tl0.tail;
        const auto &tl2 = tl1.tail;
        return TestPerson(
            *tl0.head.of(repr.base),
            *tl1.head.of(repr.base),
            *tl2.head.of(repr.base)
        );
    };
};
