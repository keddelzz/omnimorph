#pragma once

#include "generic.h"

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

template<>
struct CopyGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<int, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<const char *, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;

    static Repr to(const Type &value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(value.house_number, tl2);
        const SimpleAddress_Repr_0 tl0(value.street_name, tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        return SimpleAddress(tl0.head, tl1.head);
    }
};

template<>
struct LabelledCopyGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<MemberValue<int>, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<MemberValue<const char *>, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;
    static constexpr const char *name = "SimpleAddress";

    static Repr to(const Type & value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(member_value(value, house_number), tl2);
        const SimpleAddress_Repr_0 tl0(member_value(value, street_name), tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        return SimpleAddress(tl0.head.value, tl1.head.value);
    }
};

template<>
struct ReferenceGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<int &, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<const char * &, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;

    static Repr to(Type &value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(value.house_number, tl2);
        const SimpleAddress_Repr_0 tl0(value.street_name, tl1);
        return tl0;
    }
};

template<>
struct LabelledReferenceGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<MemberReference<int>, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<MemberReference<const char *>, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;
    static constexpr const char *name = "SimpleAddress";

    static Repr to(Type &value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(member_reference(value, house_number), tl2);
        const SimpleAddress_Repr_0 tl0(member_reference(value, street_name), tl1);
        return tl0;
    }
};

template<>
struct PointerGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<int *, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<const char * *, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;

    static Repr to(Type &value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(&value.house_number, tl2);
        const SimpleAddress_Repr_0 tl0(&value.street_name, tl1);
        return tl0;
    }
};

template<>
struct LabelledPointerGeneric<SimpleAddress>
{
    using SimpleAddress_Repr_2 = HNil;
    using SimpleAddress_Repr_1 = HList<MemberPointer<int>, SimpleAddress_Repr_2>;
    using SimpleAddress_Repr_0 = HList<MemberPointer<const char *>, SimpleAddress_Repr_1>;
    using SimpleAddress_Repr   = SimpleAddress_Repr_0;

    using Type = SimpleAddress;
    using Repr = SimpleAddress_Repr;

    static Repr to(Type &value) {
        const SimpleAddress_Repr_2 tl2{};
        const SimpleAddress_Repr_1 tl1(member_pointer(value, house_number), tl2);
        const SimpleAddress_Repr_0 tl0(member_pointer(value, street_name), tl1);
        return tl0;
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

/*
using TestPerson_Repr_3 = HNil;
using TestPerson_Repr_2 = HList<Member<int>, TestPerson_Repr_3>;
using TestPerson_Repr_1 = HList<Member<SimpleAddress>, TestPerson_Repr_2>;
using TestPerson_Repr_0 = HList<Member<const char *>, TestPerson_Repr_1>;
using TestPerson_Repr   = Class<TestPerson, TestPerson_Repr_0>;
template<>
struct Generic<TestPerson>
{
    using Type    = TestPerson;
    using Members = TestPerson_Repr_0;
    using Repr    = TestPerson_Repr;
    constexpr Generic() = default;
    static Repr to(const Type &value) {
        constexpr auto tl2 = TestPerson_Repr_2(member_of(TestPerson, age), {});
        constexpr auto tl1 = TestPerson_Repr_1(member_of(TestPerson, address), tl2);
        constexpr auto tl0 = TestPerson_Repr_0(member_of(TestPerson, name), tl1);
        return TestPerson_Repr("TestPerson", FlatPointer(&value), tl0);
    }
    static Type from(const Repr &repr) {
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
*/

struct Vec3
{
    Vec3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}
    float x, y, z;
};

/*
using Vec3_Repr_3 = HNil;
using Vec3_Repr_2 = HList<Member<float>, Vec3_Repr_3>;
using Vec3_Repr_1 = HList<Member<float>, Vec3_Repr_2>;
using Vec3_Repr_0 = HList<Member<float>, Vec3_Repr_1>;
using Vec3_Repr   = Class<Vec3, Vec3_Repr_0>;
template<>
struct Generic<Vec3>
{
    using Type    = Vec3;
    using Members = Vec3_Repr_0;
    using Repr    = Vec3_Repr;
    constexpr Generic() = default;
    static Repr to(const Type &value) {
        constexpr auto tl2 = Vec3_Repr_2(member_of(Vec3, x), {});
        constexpr auto tl1 = Vec3_Repr_1(member_of(Vec3, y), tl2);
        constexpr auto tl0 = Vec3_Repr_0(member_of(Vec3, z), tl1);
        return Vec3_Repr("Vec3", FlatPointer(&value), tl0);
    }
    static Type from(const Repr &repr) {
        const auto &tl0 = repr.members;
        const auto &tl1 = tl0.tail;
        const auto &tl2 = tl1.tail;
        return Vec3(
            *tl0.head.of(repr.base),
            *tl1.head.of(repr.base),
            *tl2.head.of(repr.base)
        );
    };
};
*/

struct Vac3
{
    Vac3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}
    float x, y, z;
};

/*
using Vac3_Repr_3 = HNil;
using Vac3_Repr_2 = HList<Member<float>, Vac3_Repr_3>;
using Vac3_Repr_1 = HList<Member<float>, Vac3_Repr_2>;
using Vac3_Repr_0 = HList<Member<float>, Vac3_Repr_1>;
using Vac3_Repr   = Class<Vac3, Vac3_Repr_0>;
template<>
struct Generic<Vac3>
{
    using Type    = Vac3;
    using Members = Vac3_Repr_0;
    using Repr    = Vac3_Repr;
    constexpr Generic() = default;
    static Repr to(const Type &value) {
        constexpr auto tl2 = Vac3_Repr_2(member_of(Vac3, x), {});
        constexpr auto tl1 = Vac3_Repr_1(member_of(Vac3, y), tl2);
        constexpr auto tl0 = Vac3_Repr_0(member_of(Vac3, z), tl1);
        return Vac3_Repr("Vac3", FlatPointer(&value), tl0);
    }
    static Type from(const Repr &repr) {
        const auto &tl0 = repr.members;
        const auto &tl1 = tl0.tail;
        const auto &tl2 = tl1.tail;
        return Vac3(
            *tl0.head.of(repr.base),
            *tl1.head.of(repr.base),
            *tl2.head.of(repr.base)
        );
    };
};
*/