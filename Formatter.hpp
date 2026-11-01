#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace metaengine {

// default formatter template
template <typename T>
struct Formatter {
    static std::string format(const T& val) {
        return std::to_string(val);
    }
};

// int specialization
template <>
struct Formatter<int> {
    static std::string format(int val) {
        return std::to_string(val);
    }

    // hex format with 0x prefix
    static std::string formatHex(int val) {
        std::ostringstream oss;
        oss << "0x" << std::hex << std::uppercase << val;
        return oss.str();
    }

    // format with label
    static std::string formatWithLabel(const std::string& labelStr, int val) {
        return labelStr + ": " + std::to_string(val);
    }
};

// double specialization
template <>
struct Formatter<double> {
    // fixed precision format
    static std::string format(double val, int precision = 2) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << val;
        return oss.str();
    }

    // scientific notation
    static std::string formatScientific(double val, int precision = 3) {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(precision) << val;
        return oss.str();
    }

    // format with label
    static std::string formatWithLabel(const std::string& labelStr, double val, int precision = 2) {
        std::ostringstream oss;
        oss << labelStr << ": " << std::fixed << std::setprecision(precision) << val;
        return oss.str();
    }
};

// bool specialization
template <>
struct Formatter<bool> {
    static std::string format(bool val) { return val ? "true" : "false"; }
    static std::string formatYesNo(bool val) { return val ? "Yes" : "No"; }
    static std::string formatOnOff(bool val) { return val ? "ON" : "OFF"; }
};

// std::string specialization
template <>
struct Formatter<std::string> {
    // wrap with quotes
    static std::string format(const std::string& val) {
        return "\"" + val + "\"";
    }

    // convert to uppercase
    static std::string formatUpper(const std::string& val) {
        std::string result = val;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char chVal) { return static_cast<char>(std::toupper(chVal)); });
        return result;
    }

    // convert to lowercase
    static std::string formatLower(const std::string& val) {
        std::string result = val;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char chVal) { return static_cast<char>(std::tolower(chVal)); });
        return result;
    }

    // label with string length
    static std::string formatWithLabel(const std::string& labelStr, const std::string& val) {
        return labelStr + ": \"" + val + "\" (length: " + std::to_string(val.length()) + ")";
    }
};

} // namespace metaengine

#endif // FORMATTER_HPP
