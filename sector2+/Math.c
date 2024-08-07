#ifndef MATH_C
#define MATH_C

#include"Constants.h"

int round(double num) {
    double tmp = num - (int)(num);
    return tmp >= 0.5 ? (int)(num) + 1 : (int)(num);
}

/**
 * power can't be a negative number (if power is negative return 1)
 * power is rounded to the closet whole number
 */
uint_64 pow(uint_64 base, uint_8 power) {
    uint_64 result = base;
    int p = round(power);
    for (uint_8 i = 1; i < p;  result *= base, i++);
    return power < 1 ? 1 : result;
}

#endif