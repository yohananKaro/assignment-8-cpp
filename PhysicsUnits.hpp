#ifndef PHYSICSUNITS_HPP
#define PHYSICSUNITS_HPP

namespace metaengine {

// physics constants
inline constexpr double PI = 3.14159265358979323846; // NOLINT
inline constexpr double GRAVITY = 9.80665;
inline constexpr double SPEED_OF_LIGHT = 299792458.0;

// conversion constants
inline constexpr double CELSIUS_TO_FAHRENHEIT_SCALE = 9.0 / 5.0;
inline constexpr double FAHRENHEIT_OFFSET = 32.0;
inline constexpr double KM_PER_MILE = 0.621371;
inline constexpr double MILES_PER_KM = 1.60934;
inline constexpr double DEGREES_IN_HALF_CIRCLE = 180.0;
inline constexpr double HALF = 0.5;

// celsius to fahrenheit
constexpr double celsiusToFahrenheit(double celsius) {
    return (celsius * CELSIUS_TO_FAHRENHEIT_SCALE) + FAHRENHEIT_OFFSET;
}

// fahrenheit to celsius
constexpr double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - FAHRENHEIT_OFFSET) / CELSIUS_TO_FAHRENHEIT_SCALE;
}

// km to miles
constexpr double kmToMiles(double kilometers) {
    return kilometers * KM_PER_MILE;
}

// miles to km
constexpr double milesToKm(double miles) {
    return miles * MILES_PER_KM;
}

// degrees to radians
constexpr double degreesToRadians(double degrees) {
    return degrees * PI / DEGREES_IN_HALF_CIRCLE;
}

// radians to degrees
constexpr double radiansToDegrees(double radians) {
    return radians * DEGREES_IN_HALF_CIRCLE / PI;
}

// compile-time recursive power
constexpr double power(double base, int exp) {
    if (exp == 0) { 
        return 1.0; 
    }
    return base * power(base, exp - 1);
}

// absolute value
constexpr double absVal(double val) {
    return val < 0.0 ? -val : val;
}

// kinetic energy
constexpr double kineticEnergy(double mass_kg, double velocity_ms) {
    return HALF * mass_kg * velocity_ms * velocity_ms;
}

// potential energy
constexpr double potentialEnergy(double mass_kg, double height_m) {
    return mass_kg * GRAVITY * height_m;
}

// rest mass energy
constexpr double massEnergy(double mass_kg) {
    return mass_kg * SPEED_OF_LIGHT * SPEED_OF_LIGHT;
}

// free fall distance
constexpr double freeFallDistance(double time_s) {
    return HALF * GRAVITY * time_s * time_s;
}

} // namespace metaengine

#endif // PHYSICSUNITS_HPP
