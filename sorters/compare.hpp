#ifndef COMPARE_HPP
#define COMPARE_HPP

#include <string>

template<typename T>
int compare_default(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

#endif // COMPARE_HPP
