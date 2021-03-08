#include <iostream>

#include "data/types.h"

#include "json/Value.h"
#include "json/Array.h"
#include "json/Object.h"
#include "json/Show.h"

#include "Individual.h"

json::Value jsonTestIndividual()
{
    json::Object root;
    root.insert("type", String("Individual"));
    root.insert("name", String("Simon Segfault"));
    root.insert("age", int64_t(42));

    json::Array pets;
    pets.append(String("cat"));
    pets.append(String("dog"));
    root.insert("pets", pets);

    return root;
}

Individual testIndividual()
{
    Individual individual;
    individual.name = "Nicole Nullpointer";
    individual.age = 0xC0FFEE;
    individual.pets.append("fish");
    return individual;
}

int main() {
    std::cout << "Hello, generic-json" << std::endl;

    const auto jsonIndividual = jsonTestIndividuals();
//    const auto individual = testIndividual();

    StringBuilder buffer;
    json::Show::json(buffer, jsonIndividual);
    std::cout << buffer.toString() << std::endl;

    return EXIT_SUCCESS;
}
