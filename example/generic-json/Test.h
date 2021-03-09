#pragma once

#include "../common/Fid.h"
#include "../common/Vec2i.h"
#include "../common/Nested.h"
#include "Individual.h"

struct Test
{
    generic(Test)

    Fid fid;
    Fid anotherFid;
    Vec2i vector;
    Nested nested;
    Individual person;
};
