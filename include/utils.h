#pragma once

#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <complex>
#include <cmath>
#include <algorithm>
#include <iomanip>

// not sure if we should go lower, using this threshold for most computations
static constexpr double EPS = 1e-6;

/*
Returns the binary representation of the given value with a fixed number of bits.
*/
std::string binary(size_t value, const size_t bitNr);

/*
Taken from: https://graphics.stanford.edu/~seander/bithacks.html#SwappingBitsXOR
Swaps specified amount of consecutive bits of the given value starting at indices j and k.
Example: value = 100110, j = 1, k = 3, n = 2
        result = 111000
*/
size_t swapBits(size_t value, size_t j, size_t k, size_t consecutiveBits);

/*
Returns a string representation of the given complex number in the form a+ib.
*/
std::string toString(std::complex<double> z);

/*
Reads a complex number in the form a+ib.
a and b must be in decimal form or fractions.
*/
std::complex<double> readComplex(std::string& str);

/*
Removes all but the last trailing zero of a string containing a decimal number.
*/
std::string removeTrailingZeros(std::string& value);

/*
Removes leading and trailing whitespaces.
*/
std::string trim(std::string& str);

/*
Converts a string to lowercase, reading from src and writing in dst.
*/
void lower(std::string& src, std::string& dst);

/*
Checks if all of the characters in the string are digits.
*/
bool isInteger(const std::string& s);