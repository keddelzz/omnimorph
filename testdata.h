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

template<>
struct CopyGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<int, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<SimpleAddress, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<const char *, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;

    static Repr to(const Type &value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(value.age, tl3);
        const TestPerson_Repr_1 tl1(value.address, tl2);
        const TestPerson_Repr_0 tl0(value.name, tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        const auto tl3 = tl2.tail;
        return TestPerson(tl0.head, tl1.head, tl2.head);
    }
};

template<>
struct LabelledCopyGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<MemberValue<int>, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<MemberValue<SimpleAddress>, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<MemberValue<const char *>, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;
    static constexpr const char *name = "TestPerson";

    static Repr to(const Type & value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(member_value(value, age), tl3);
        const TestPerson_Repr_1 tl1(member_value(value, address), tl2);
        const TestPerson_Repr_0 tl0(member_value(value, name), tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        const auto tl3 = tl2.tail;
        return TestPerson(tl0.head.value, tl1.head.value, tl2.head.value);
    }
};

template<>
struct ReferenceGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<int &, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<SimpleAddress &, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<const char * &, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;

    static Repr to(Type &value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(value.age, tl3);
        const TestPerson_Repr_1 tl1(value.address, tl2);
        const TestPerson_Repr_0 tl0(value.name, tl1);
        return tl0;
    }
};

template<>
struct LabelledReferenceGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<MemberReference<int>, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<MemberReference<SimpleAddress>, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<MemberReference<const char *>, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;
    static constexpr const char *name = "TestPerson";

    static Repr to(Type &value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(member_reference(value, age), tl3);
        const TestPerson_Repr_1 tl1(member_reference(value, address), tl2);
        const TestPerson_Repr_0 tl0(member_reference(value, name), tl1);
        return tl0;
    }
};

template<>
struct PointerGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<int *, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<SimpleAddress *, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<const char * *, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;

    static Repr to(Type &value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(&value.age, tl3);
        const TestPerson_Repr_1 tl1(&value.address, tl2);
        const TestPerson_Repr_0 tl0(&value.name, tl1);
        return tl0;
    }
};

template<>
struct LabelledPointerGeneric<TestPerson>
{
    using TestPerson_Repr_3 = HNil;
    using TestPerson_Repr_2 = HList<MemberPointer<int>, TestPerson_Repr_3>;
    using TestPerson_Repr_1 = HList<MemberPointer<SimpleAddress>, TestPerson_Repr_2>;
    using TestPerson_Repr_0 = HList<MemberPointer<const char *>, TestPerson_Repr_1>;
    using TestPerson_Repr   = TestPerson_Repr_0;

    using Type = TestPerson;
    using Repr = TestPerson_Repr;

    static Repr to(Type &value) {
        const TestPerson_Repr_3 tl3{};
        const TestPerson_Repr_2 tl2(member_pointer(value, age), tl3);
        const TestPerson_Repr_1 tl1(member_pointer(value, address), tl2);
        const TestPerson_Repr_0 tl0(member_pointer(value, name), tl1);
        return tl0;
    }
};

struct Vec3
{
    Vec3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}
    float x, y, z;
};

template<>
struct CopyGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<float, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<float, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<float, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;

    static Repr to(const Type &value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(value.z, tl3);
        const Vec3_Repr_1 tl1(value.y, tl2);
        const Vec3_Repr_0 tl0(value.x, tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        const auto tl3 = tl2.tail;
        return Vec3(tl0.head, tl1.head, tl2.head);
    }
};

template<>
struct LabelledCopyGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<MemberValue<float>, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<MemberValue<float>, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<MemberValue<float>, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;
    static constexpr const char *name = "Vec3";

    static Repr to(const Type & value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(member_value(value, z), tl3);
        const Vec3_Repr_1 tl1(member_value(value, y), tl2);
        const Vec3_Repr_0 tl0(member_value(value, x), tl1);
        return tl0;
    }

    static Type from(const Repr &repr) {
        const auto tl0 = repr;
        const auto tl1 = tl0.tail;
        const auto tl2 = tl1.tail;
        const auto tl3 = tl2.tail;
        return Vec3(tl0.head.value, tl1.head.value, tl2.head.value);
    }
};

template<>
struct ReferenceGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<float &, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<float &, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<float &, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;

    static Repr to(Type &value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(value.z, tl3);
        const Vec3_Repr_1 tl1(value.y, tl2);
        const Vec3_Repr_0 tl0(value.x, tl1);
        return tl0;
    }
};

template<>
struct LabelledReferenceGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<MemberReference<float>, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<MemberReference<float>, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<MemberReference<float>, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;
    static constexpr const char *name = "Vec3";

    static Repr to(Type &value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(member_reference(value, z), tl3);
        const Vec3_Repr_1 tl1(member_reference(value, y), tl2);
        const Vec3_Repr_0 tl0(member_reference(value, x), tl1);
        return tl0;
    }
};

template<>
struct PointerGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<float *, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<float *, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<float *, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;

    static Repr to(Type &value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(&value.z, tl3);
        const Vec3_Repr_1 tl1(&value.y, tl2);
        const Vec3_Repr_0 tl0(&value.x, tl1);
        return tl0;
    }
};

template<>
struct LabelledPointerGeneric<Vec3>
{
    using Vec3_Repr_3 = HNil;
    using Vec3_Repr_2 = HList<MemberPointer<float>, Vec3_Repr_3>;
    using Vec3_Repr_1 = HList<MemberPointer<float>, Vec3_Repr_2>;
    using Vec3_Repr_0 = HList<MemberPointer<float>, Vec3_Repr_1>;
    using Vec3_Repr   = Vec3_Repr_0;

    using Type = Vec3;
    using Repr = Vec3_Repr;

    static Repr to(Type &value) {
        const Vec3_Repr_3 tl3{};
        const Vec3_Repr_2 tl2(member_pointer(value, z), tl3);
        const Vec3_Repr_1 tl1(member_pointer(value, y), tl2);
        const Vec3_Repr_0 tl0(member_pointer(value, x), tl1);
        return tl0;
    }
};

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