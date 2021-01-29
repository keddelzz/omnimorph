#include <iostream>
#include <functional>

#include "flatfunction.h"
#include "hlist.h"
#include "generic.h"
#include "testdata.h"
#include "validspecialization.h"

// show primitives
template<typename T, typename = std::enable_if<false>>
struct ShowP {
//    static std::string show(T); // no implementation
};
template<>
struct ShowP<int, void> {
    static std::string show(int value) { return std::to_string(value); }
};
template<>
struct ShowP<bool, void> {
    static std::string show(bool value) { return value ? "true" : "false"; }
};
template<>
struct ShowP<std::string, void> {
    static std::string show(std::string value) { return value; }
};

// user defined
template<typename T, typename = std::enable_if<false>>
struct ShowU {
//    static std::string show(T); // no implementation
};
// no specialization

// leveraging generic repr
template<typename T, typename = std::enable_if<false>>
struct ShowG {
//    static std::string show(T); // no implementation
};

// forwarder
template<typename T, typename = std::enable_if<false>>
struct Show {
//    static std::string show(T); // no implementation
};
template<typename T> // always prefer primitive show instances
struct Show<T, typename std::enable_if<
        ValidSpecialization<ShowP, T>::value
        >::type> {
    static std::string show(T value) { return ShowP<T>::show(value); }
};
template<typename T> // if no primitive exists, prefer user defined instance over generic
struct Show<T, typename std::enable_if<
        !ValidSpecialization<ShowP, T>::value and
         ValidSpecialization<ShowU, T>::value
        >::type> {
    static std::string show(T value) { return ShowU<T>::show(value); }
};
template<typename T> // else use generic repr
struct Show<T, typename std::enable_if<
        !ValidSpecialization<ShowP, T>::value and
        !ValidSpecialization<ShowU, T>::value and
         ValidSpecialization<ShowG, T>::value
        >::type> {
    static std::string show(T value) { return ShowG<T>::show(value); }
};

template<>
struct ShowG<HNil, void> {
    static std::string show(HNil) { return "HNil"; }
};
template<typename H, typename T>
struct ShowG<HList<H, T>, void> {
    static std::string show(HList<H, T> value) {
        Show<H> showHead;
        Show<T> showTail;
        return showHead.show(value.head) + " :: " + showTail.show(value.tail);
    };
};

template<typename T>
std::string show(T value) {
    return Show<T, void>::show(value);
}

int main() {
    std::cout
        << show<int>(42)
        << std::endl;
    // @TODO: ValidSpecialization isn't the right thing!
    //        We need to check whether ShowX<T>::show exists.
    //        But I have a strong tingle if it works, once we solved the problem.
}

int main2() {
    constexpr const char *meh = "meh";
    auto test = hlist(1, 2, std::string(meh));
    std::cout << hlist() << std::endl;
    std::cout << test << std::endl;

    const char *streetName = "New Years Street";
    const char *name = "Peter Finger";
    SimpleAddress a(streetName, 32);
    TestPerson p(name, a, 55);

    auto x = to_repr<TestPerson>(p);
    auto b = to_value<TestPerson>(x);
    return 0;
}
