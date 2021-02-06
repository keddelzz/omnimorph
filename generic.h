#pragma once

#include "grepr.h"

//
// The representation of type `T` containing copies of the fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then `CopyGeneric<T>::Repr` would be of type
//
//     HList<
//         A,
//         HList<
//             B,
//             HList<
//                 C,
//                 HNil>>>
//
template<typename T>
struct CopyGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type & value);          // generated
//  static Type from(const Repr &repr);          // generated
};

//
// The representation of type `T` containing labelled copies of the fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then the `LabelledGeneric<T>::Repr` would be of type
//
//     HList<
//         MemberValue<A>,
//         HList<
//             MemberValue<B>,
//             HList<
//                 MemberValue<C>,
//                 HNil>>>
//
template<typename T>
struct LabelledCopyGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
    static constexpr const char *name = nullptr; // generated
//  static Repr to(const Type &value);           // generated
//  static Type from(const Repr &repr);          // generated
};

//
// The representation of type `T` containing pointers to fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then `ReferenceGeneric<T>::Repr` would be of type
//
//     HList<
//         A &,
//         HList<
//             B &,
//             HList<
//                 C &,
//                 HNil>>>
//
template<typename T>
struct ReferenceGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};

//
// The representation of type `T` containing labelled references to fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then `LabelledReferenceGeneric<T>::Repr` would be of type
//
//     HList<
//         MemberRef<A>,
//         HList<
//             MemberRef<B>,
//             HList<
//                 MemberRef<C>,
//                 HNil>>>
//
template<typename T>
struct LabelledReferenceGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
    static constexpr const char *name = nullptr; // generated
//  static Repr to(Type &value);                 // generated
};

//
// The representation of type `T` containing pointers to fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then `PointerGeneric<T>::Repr` would be of type
//
//     HList<
//         A *,
//         HList<
//             B *,
//             HList<
//                 C *,
//                 HNil>>>
//
template<typename T>
struct PointerGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};

//
// The representation of type `T` containing labelled pointers to fields in `T`.
//
// Imagine a struct like
//
//     struct Abc {
//         A a;
//         B b;
//         C c;
//     };
//
// then `LabelledPointerGeneric<T>::Repr` would be of type
//
//     HList<
//         MemberPointer<A>,
//         HList<
//             MemberPointer<B>,
//             HList<
//                 MemberPointer<C>,
//                 HNil>>>
//
template<typename T>
struct LabelledPointerGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
    static constexpr const char *name = nullptr; // generated
//  static Repr to(Type &value);                 // generated
};
