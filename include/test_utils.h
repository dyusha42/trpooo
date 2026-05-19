#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <vector>
#include <cmath>
#include <limits>

template<typename T>
constexpr T get_tolerance() {
    return std::numeric_limits<T>::epsilon() * 100;
}

template<typename T>
bool almost_equal(T a, T b, T tolerance = get_tolerance<T>()) {
    return std::abs(a - b) <= tolerance * std::max(T(1.0), std::max(std::abs(a), std::abs(b)));
}

template<typename T>
bool vectors_almost_equal(const std::vector<T>& a, const std::vector<T>& b, T tolerance = get_tolerance<T>()) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (!almost_equal(a[i], b[i], tolerance)) {
            return false;
        }
    }
    return true;
}

#endif
