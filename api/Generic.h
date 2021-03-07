#pragma once

#include "Representation.h"

#define generic(T)                                 \
    friend class CopyGeneric<T>;                   \
    friend class CopyLabelledGeneric<T>;           \
                                                   \
    friend class ConstReferenceGeneric<T>;         \
    friend class ConstReferenceLabelledGeneric<T>; \
                                                   \
    friend class ReferenceGeneric<T>;              \
    friend class ReferenceLabelledGeneric<T>;      \
                                                   \
    friend class ConstPointerGeneric<T>;           \
    friend class ConstPointerLabelledGeneric<T>;   \
                                                   \
    friend class PointerGeneric<T>;                \
    friend class PointerLabelledGeneric<T>;

// @TODO: Document representation

template<typename T>
struct CopyGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
//  static Type from(const Repr &repr);          // generated
};

template<typename T>
struct CopyLabelledGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
//  static Type from(const Repr &repr);          // generated
};

template<typename T>
struct ConstReferenceGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
};

template<typename T>
struct ConstReferenceLabelledGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
};

template<typename T>
struct ReferenceGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};

template<typename T>
struct ReferenceLabelledGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};

template<typename T>
struct ConstPointerGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
};

template<typename T>
struct ConstPointerLabelledGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
};

template<typename T>
struct PointerGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};

template<typename T>
struct PointerLabelledGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(Type &value);                 // generated
};
