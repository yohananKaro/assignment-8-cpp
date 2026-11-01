#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <string>

namespace metaengine {

// constant expression
template <int N>
struct Const {
    static constexpr int eval(int /*val*/) { return N; }
    static std::string toString() { return std::to_string(N); }
};

// variable x expression
struct Var {
    static constexpr int eval(int val) { return val; }
    static std::string toString() { return "x"; }
};

// addition of two expressions
template <typename L, typename R>
struct Add {
    static constexpr int eval(int val) { return L::eval(val) + R::eval(val); }
    static std::string toString() { return "(" + L::toString() + " + " + R::toString() + ")"; }
};

// multiplication of two expressions
template <typename L, typename R>
struct Mul {
    static constexpr int eval(int val) { return L::eval(val) * R::eval(val); }
    static std::string toString() { return "(" + L::toString() + " * " + R::toString() + ")"; }
};

// power expression
template <typename E, int N>
struct Power {
    static constexpr int eval(int val) {
        int result = 1;
        for (int idx = 0; idx < N; ++idx) { 
            result *= E::eval(val); 
        }
        return result;
    }
    static std::string toString() {
        return "(" + E::toString() + "^" + std::to_string(N) + ")";
    }
};

// base case: power 0 is 1
template <typename E>
struct Power<E, 0> {
    static constexpr int eval(int /*val*/) { return 1; }
    static std::string toString() { return "1"; }
};

// base case: power 1 is E
template <typename E>
struct Power<E, 1> {
    static constexpr int eval(int val) { return E::eval(val); }
    static std::string toString() { return E::toString(); }
};

// compile-time symbolic derivation
template <typename E>
struct Derive;

// derivative of constant is 0
template <int N>
struct Derive<Const<N>> {
    using type = Const<0>;
};

// derivative of x is 1
template <>
struct Derive<Var> {
    using type = Const<1>;
};

// sum rule: d(L+R) = dL + dR
template <typename L, typename R>
struct Derive<Add<L, R>> {
    using type = Add<typename Derive<L>::type, typename Derive<R>::type>;
};

// product rule: d(L*R) = dL*R + L*dR
template <typename L, typename R>
struct Derive<Mul<L, R>> {
    using type = Add<
        Mul<typename Derive<L>::type, R>,
        Mul<L, typename Derive<R>::type>
    >;
};

// alias helper for derivative type
template <typename E>
using Derivative = typename Derive<E>::type;

} // namespace metaengine

#endif // DERIVATIVE_HPP
