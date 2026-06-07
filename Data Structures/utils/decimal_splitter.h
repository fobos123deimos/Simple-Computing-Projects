#ifndef DECIMAL_SPLITTER_H
#define DECIMAL_SPLITTER_H

#include <math.h>

#define DECIMAL_SPLITTER_EPSILON 1e-12L
#define DECIMAL_SPLITTER_MAX_DECIMAL_PLACES 18

/*
 * Stores the separated parts of a decimal number.
 *
 * integer_part:
 *   The integer part of the number.
 *
 * decimal_part:
 *   The decimal digits converted to an integer.
 *
 * has_decimal_part:
 *   1 if the number has decimal digits.
 *   0 otherwise.
 */
typedef struct {
    long long integer_part;
    unsigned long long decimal_part;
    int has_decimal_part;
} DecimalParts;

/*
 * Calculates 10^decimal_places using integer multiplication.
 */
static inline unsigned long long power_of_10(unsigned int decimal_places) {
    unsigned long long result = 1;

    for (unsigned int i = 0; i < decimal_places; i++) {
        result *= 10;
    }

    return result;
}

/*
 * Checks whether a number has a decimal part.
 *
 * Returns:
 *   1 if the number has decimal digits.
 *   0 otherwise.
 */
static inline int has_decimal_part(long double number) {
    long double integer_part;
    long double fractional_part = modfl(number, &integer_part);

    return fabsl(fractional_part) > DECIMAL_SPLITTER_EPSILON;
}

/*
 * Splits a decimal number into integer and decimal parts.
 *
 * Example:
 *
 *   number = 123.4567
 *   decimal_places = 2
 *
 * Result:
 *
 *   integer_part = 123
 *   decimal_part = 45
 *   has_decimal_part = 1
 */
static inline DecimalParts split_decimal(long double number, unsigned int decimal_places) {
    DecimalParts result;
    long double integer_part;
    long double fractional_part;

    if (decimal_places > DECIMAL_SPLITTER_MAX_DECIMAL_PLACES) {
        decimal_places = DECIMAL_SPLITTER_MAX_DECIMAL_PLACES;
    }

    fractional_part = modfl(number, &integer_part);

    result.integer_part = (long long)integer_part;
    result.has_decimal_part = fabsl(fractional_part) > DECIMAL_SPLITTER_EPSILON;

    if (fractional_part < 0) {
        fractional_part = -fractional_part;
    }

    result.decimal_part = (unsigned long long)(fractional_part * power_of_10(decimal_places));

    return result;
}

#endif