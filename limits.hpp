#ifndef LAB4_LIMITS_HPP
#define LAB4_LIMITS_HPP

#include "pair/Pair.hpp"

template <typename T>
struct custom_limits {
    static T max();
    static T min();
};

template <>
struct custom_limits<int> {
    static int max() { return 2147483647; }
    static int min() { return -2147483648; }
};

template <>
struct custom_limits<double> {
    static double max() { return 1.79769e+308; }
    static double min() { return -1.79769e+308; }
};

template <typename T1, typename T2>
struct custom_limits<Pair<T1, T2>> {
static Pair<T1, T2> max() {
    return Pair<T1, T2>(custom_limits<T1>::max(), custom_limits<T2>::max());
}

static Pair<T1, T2> min() {
    return Pair<T1, T2>(custom_limits<T1>::min(), custom_limits<T2>::min());
}
};


#endif //LAB4_LIMITS_HPP
