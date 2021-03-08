#pragma once

#include <omnimorph/Generic.h>

#include "data/types.h"

struct Individual
{
    generic(Individual)
    String name;
    int age;
    StringList pets;
};