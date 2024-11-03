#include "utils.h"

std::string binary(size_t value, const size_t bitNr){
    std::string res{};
    while (value > 0) {
        res = std::to_string(value % 2) + res;
        value /= 2;
    }
    while (res.length() < bitNr){
         res = '0' + res;
    }
    return res;
}

size_t swapBits(size_t value, size_t j, size_t k, size_t consecutiveBits){
    if (j == k){
        return value;
    }
    size_t x = ((value >> j) ^ (value >> k)) & ((1U << consecutiveBits) - 1); // XOR temporary
    return value ^ ((x << j) | (x << k));
}

std::string toString(std::complex<double> z){
    std::ostringstream res;
    res << std::fixed << std::setprecision(6);
    bool hasReal = std::abs(z.real()) >= EPS;
    bool hasImag = std::abs(z.imag()) >= EPS;

    if (std::abs(z.real()) >= EPS){
        std::string realStr = std::to_string(z.real());
        res << removeTrailingZeros(realStr);
    }
    if (hasReal && hasImag && z.imag() > 0){
        res << "+";
    }
    if (std::abs(z.imag()) >= EPS){
        std::string imagStr = std::to_string(z.imag());
        res << removeTrailingZeros(imagStr) << "i";
    }

    if (!hasReal && !hasImag ) res << "0";
    return res.str();
}

std::complex<double> readComplex(std::string& str){
    str = trim(str);
    
    double real = 0.0;
    double imag = 0.0;
    std::string realStr;
    std::string imagStr;

    auto iPos = str.find('i');
    auto sep = str.find_last_of("+-");

    if (iPos != std::string::npos){
        if (iPos == 0){
            imag = 1.0;
        }
        else if (str[iPos - 1] == '+' || str[iPos - 1] == '-'){
            imag = (iPos - 1 == '-') ? -1.0 : 1.0;
            if (sep != std::string::npos && sep != 0){
                realStr = str.substr(0, sep);
                realStr = trim(realStr);
                real = std::stod(realStr);
            }
        }
        else {
            if (sep == std::string::npos || sep == 0){
                imagStr = str.substr(0, iPos);
                imagStr = trim(imagStr);
                imag = std::stod(imagStr);
            }
            else {
                imagStr = str.substr(sep, iPos);
                imagStr = trim(imagStr);
                imag = std::stod(imagStr);
                realStr = str.substr(0, sep);
                realStr = trim(realStr);
                real = std::stod(realStr);
            }
        }
    }
    else {
        real = std::stod(str);
    }
    return std::complex<double>(real, imag);
}

std::string removeTrailingZeros(std::string& value){
    auto dotPos = value.find('.');
    if (dotPos != std::string::npos) {
        value = value.substr(0, value.find_last_not_of('0') + 1);
    }
    if (value.back() == '.'){
        value += '0';
    }
    return value;
}

std::string trim(std::string& str){
    auto first = str.find_first_not_of(" \t\n\r\f\v\"");
    auto last = str.find_last_not_of(" \t\n\r\f\v\"");
    if (first == std::string::npos){
        return "";
    }
    return str.substr(first, last - first + 1);
}

void lower(std::string& src, std::string& dst){
    std::transform(src.begin(), src.end(), dst.begin(), [](char c) {return std::tolower(c);});
}

// taken from https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool isInteger(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}