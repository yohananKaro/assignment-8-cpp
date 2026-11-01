#ifndef DECLTYPEUTILS_HPP
#define DECLTYPEUTILS_HPP

#include <type_traits>

namespace metaengine {

// add two values and deduce return type with decltype
template <typename A, typename B>
auto add(A val1, B val2) -> decltype(val1 + val2) {
    return val1 + val2;
}

// multiply with decltype deduction
template <typename A, typename B>
auto multiply(A val1, B val2) -> decltype(val1 * val2) {
    return val1 * val2;
}

// max of two values
template <typename A, typename B>
auto maxOf(A val1, B val2) -> decltype(val1 + val2) {
    return (val1 > val2) ? static_cast<decltype(val1 + val2)>(val1)
                         : static_cast<decltype(val1 + val2)>(val2);
}

// min of two values
template <typename A, typename B>
auto minOf(A val1, B val2) -> decltype(val1 + val2) {
    return (val1 < val2) ? static_cast<decltype(val1 + val2)>(val1)
                         : static_cast<decltype(val1 + val2)>(val2);
}

// check if add result is floating point
template <typename A, typename B>
bool isAddResultFloating() {
    return std::is_floating_point_v<decltype(A{} + B{})>;
}

// check if multiply result is integral
template <typename A, typename B>
bool isMulResultIntegral() {
    return std::is_integral_v<decltype(A{} * B{})>;
}

} // namespace metaengine

#endif // DECLTYPEUTILS_HPP
