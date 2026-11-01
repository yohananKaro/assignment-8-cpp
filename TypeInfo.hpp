#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <string>

namespace metaengine {

// primary template for unknown types
template <typename T>
struct TypeInfo {
    static constexpr const char* name = "Unknown";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(T);

    static std::string describe() {
        return "Unknown type of size " + std::to_string(sizeof(T)) + " bytes";
    }
};

// int specialization
template <>
struct TypeInfo<int> {
    static constexpr const char* name = "int";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(int);
    // min and max limits needed for tests
    static constexpr int min_value = (-2147483647 - 1);
    static constexpr int max_value = 2147483647;

    static std::string describe() {
        return "int: numeric type, size " + std::to_string(sizeof(int)) +
               " bytes, range [-2147483648, 2147483647]";
    }
};

// double specialization
template <>
struct TypeInfo<double> {
    static constexpr const char* name = "double";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(double);

    static std::string describe() {
        return "double: floating-point type, size " + std::to_string(sizeof(double)) +
               " bytes, epsilon 1e-9";
    }
};

// bool specialization
template <>
struct TypeInfo<bool> {
    static constexpr const char* name = "bool";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(bool);

    static std::string describe() {
        return "bool: boolean type, size " + std::to_string(sizeof(bool)) + " byte";
    }
};

// std::string specialization
template <>
struct TypeInfo<std::string> {
    static constexpr const char* name = "string";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(std::string);

    static std::string describe() {
        return "string: text type, size " + std::to_string(sizeof(std::string)) + " bytes";
    }
};

// partial specialization for pointers
template <typename T>
struct TypeInfo<T*> {
    static constexpr const char* name = "pointer";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = true;
    static constexpr std::size_t size = sizeof(T*);

    static std::string describe() {
        return std::string("pointer to ") + TypeInfo<T>::name +
               ", size " + std::to_string(sizeof(T*)) + " bytes";
    }
};

} // namespace metaengine

#endif // TYPEINFO_HPP
