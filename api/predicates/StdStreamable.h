#pragma once

#include <ostream>

#include "ExistsOperator.h"

GENERATE_EXISTS_OPERATOR(OStdStreamble, <<)
template<typename T>
constexpr bool OStreamable = OStdStreamble<std::ostream &, T>;

GENERATE_EXISTS_OPERATOR(IStdStreamble, >>)
template<typename T>
constexpr bool IStreamable = IStdStreamble<std::ostream &, T>;
