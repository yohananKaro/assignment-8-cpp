// student test suite for assignment 8

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TypeInfo.hpp"
#include "MySwap.hpp"
#include "Formatter.hpp"
#include "Derivative.hpp"
#include "PhysicsUnits.hpp"
#include "DecltypeUtils.hpp"
#include <string>

using namespace metaengine;

// typeinfo tests

// check if float returns unknown
TEST_CASE("TypeInfo<float> - Unknown (primary template)") {
    CHECK(std::string(TypeInfo<float>::name) == "Unknown");
    CHECK(TypeInfo<float>::is_numeric == false);
    CHECK(TypeInfo<float>::is_pointer == false);
    CHECK(TypeInfo<float>::size == sizeof(float));
}

// pointer to bool
TEST_CASE("TypeInfo<bool*> - pointer to bool") {
    CHECK(TypeInfo<bool*>::is_pointer == true);
    CHECK(std::string(TypeInfo<bool*>::name) == "pointer");
    std::string desc = TypeInfo<bool*>::describe();
    CHECK(desc.find("pointer") != std::string::npos);
}

// pointer size
TEST_CASE("TypeInfo<int*> - size equals sizeof pointer") {
    CHECK(TypeInfo<int*>::size == sizeof(int*));
}

// int min and max
TEST_CASE("TypeInfo<int> - min and max values are correct") {
    CHECK(TypeInfo<int>::min_value == (-2147483647 - 1));
    CHECK(TypeInfo<int>::max_value == 2147483647);
}

// check string description contains text
TEST_CASE("TypeInfo<string> - describe contains text") {
    std::string desc = TypeInfo<std::string>::describe();
    CHECK(desc.find("text") != std::string::npos);
}

// swap tests

// swap zero with itself
TEST_CASE("mySwap<int> - swap zero with itself") {
    int a = 0, b = 0;
    mySwap(a, b);
    CHECK(a == 0);
    CHECK(b == 0);
}

// swap both negative
TEST_CASE("mySwap<int> - both negative") {
    int a = -100, b = -200;
    mySwap(a, b);
    CHECK(a == -200);
    CHECK(b == -100);
}

// swap both empty strings
TEST_CASE("mySwap<string> - both empty") {
    std::string a, b;
    mySwap(a, b);
    CHECK(a.empty());
    CHECK(b.empty());
}

// swap both false
TEST_CASE("mySwap<bool> - both false") {
    bool a = false, b = false;
    mySwap(a, b);
    CHECK(a == false);
    CHECK(b == false);
}

// swap double with zero
TEST_CASE("mySwap<double> - swap with zero") {
    double a = 0.0, b = 99.9;
    mySwap(a, b);
    CHECK(a == doctest::Approx(99.9));
    CHECK(b == doctest::Approx(0.0));
}

// formatter tests

// negative int format
TEST_CASE("Formatter<int> - format negative") {
    CHECK(Formatter<int>::format(-999) == "-999");
}

// hex format for 256
TEST_CASE("Formatter<int> - formatHex 256") {
    CHECK(Formatter<int>::formatHex(256) == "0x100");
}

// precision 0
TEST_CASE("Formatter<double> - format precision 0") {
    CHECK(Formatter<double>::format(3.7, 0) == "4");
}

// bool false formatting
TEST_CASE("Formatter<bool> - format false") {
    CHECK(Formatter<bool>::format(false) == "false");
    CHECK(Formatter<bool>::formatYesNo(false) == "No");
    CHECK(Formatter<bool>::formatOnOff(false) == "OFF");
}

// empty string formatting
TEST_CASE("Formatter<string> - empty string format") {
    CHECK(Formatter<std::string>::format("") == "\"\"");
    CHECK(Formatter<std::string>::formatUpper("") == "");
    CHECK(Formatter<std::string>::formatLower("") == "");
}

// format with label and length
TEST_CASE("Formatter<string> - formatWithLabel length check") {
    std::string result = Formatter<std::string>::formatWithLabel("key", "hi");
    CHECK(result.find("length: 2") != std::string::npos);
    CHECK(result.find("key") != std::string::npos);
}

// derivative tests

// constant zero
TEST_CASE("Derivative - Const<0> eval is always 0") {
    CHECK(Const<0>::eval(0) == 0);
    CHECK(Const<0>::eval(100) == 0);
    CHECK(Const<0>::eval(-50) == 0);
}

// d/dx[x] = 1
TEST_CASE("Derivative - d/dx[x] = 1") {
    using DVar = Derivative<Var>;
    CHECK(DVar::eval(0) == 1);
    CHECK(DVar::eval(999) == 1);
}

// derivative of sum
TEST_CASE("Derivative - d/dx[x + 5] = 1") {
    using Expr = Add<Var, Const<5>>;
    using DExpr = Derivative<Expr>;
    CHECK(DExpr::eval(0) == 1);
    CHECK(DExpr::eval(10) == 1);
}

// derivative of product
TEST_CASE("Derivative - d/dx[x * 3] = 3") {
    using Expr = Mul<Var, Const<3>>;
    using DExpr = Derivative<Expr>;
    CHECK(DExpr::eval(0) == 3);
    CHECK(DExpr::eval(10) == 3);
}

// physics units tests

// power 2^10
TEST_CASE("PhysicsUnits - power(2, 10)") {
    constexpr double p = power(2.0, 10);
    CHECK(p == doctest::Approx(1024.0));
}

// absVal checks
TEST_CASE("PhysicsUnits - absVal") {
    CHECK(absVal(-3.5) == doctest::Approx(3.5));
    CHECK(absVal(0.0) == doctest::Approx(0.0));
    CHECK(absVal(7.2) == doctest::Approx(7.2));
}

// degrees to radians 360
TEST_CASE("PhysicsUnits - degreesToRadians 360") {
    constexpr double r = degreesToRadians(360.0);
    CHECK(r == doctest::Approx(2.0 * PI));
}

// free fall distance at t=0
TEST_CASE("PhysicsUnits - freeFallDistance zero time") {
    constexpr double d = freeFallDistance(0.0);
    CHECK(d == doctest::Approx(0.0));
}

// miles to km at 0
TEST_CASE("PhysicsUnits - milesToKm zero") {
    constexpr double k = milesToKm(0.0);
    CHECK(k == doctest::Approx(0.0));
}

// decltype tests

// add floats
TEST_CASE("DecltypeUtils - add float+float") {
    auto r = add(1.5F, 2.5F);
    CHECK(r == doctest::Approx(4.0F));
}

// float type check
TEST_CASE("DecltypeUtils - isAddResultFloating float+int") {
    CHECK(isAddResultFloating<float, int>() == true);
}

// integral type check
TEST_CASE("DecltypeUtils - isMulResultIntegral short+int") {
    CHECK(isMulResultIntegral<short, int>() == true);
}
