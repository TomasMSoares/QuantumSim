#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>
#include <cmath>
#include <iomanip>

// not sure if we should go lower, using this threshold for most computations
static constexpr double EPS = 1e-8;

/*
Returns the binary representation of the given value with a fixed number of bits.
*/
std::string binary(size_t value, const size_t bitNr);

/*
Returns a string representation of the given complex number in the form a+ib.
*/
std::string toString(std::complex<double> z);

/*
Removes all but the last trailing zero of a string containing a decimal number.
*/
std::string removeTrailingZeros(std::string& value);

void printHelp();

