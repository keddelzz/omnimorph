#pragma once

using FlatPointer = std::conditional<sizeof(void *) == 8, uint64_t, uint32_t>::type;