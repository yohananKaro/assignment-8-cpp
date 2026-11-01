#ifndef MYSWAP_HPP
#define MYSWAP_HPP

#include <string>
#include <iostream>

namespace metaengine {

// generic swap using temp variable
template <typename T>
void mySwap(T& val1, T& val2) {
    std::cout << "Generic swap\n";
    T tempVal = val1;
    val1 = val2;
    val2 = tempVal;
}

// xor swap for ints without extra temp variable
template <>
inline void mySwap<int>(int& val1, int& val2) {
    std::cout << "Int XOR swap\n";
    // avoid zeroing if swapping the same variable
    if (&val1 != &val2) {
        val1 ^= val2;
        val2 ^= val1;
        val1 ^= val2;
    }
}

// std::string specialization using internal swap (O(1))
template <>
inline void mySwap<std::string>(std::string& val1, std::string& val2) {
    std::cout << "String optimized swap\n";
    val1.swap(val2);
}

// bool swap with xor
template <>
inline void mySwap<bool>(bool& val1, bool& val2) {
    std::cout << "Bool logical swap\n";
    val1 = val1 ^ val2;
    val2 = val1 ^ val2;
    val1 = val1 ^ val2;
}

} // namespace metaengine

#endif // MYSWAP_HPP
