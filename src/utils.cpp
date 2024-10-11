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

std::string toString(std::complex<double> z){
    std::ostringstream res;
    res << std::fixed << std::setprecision(6);
    std::string realStr = std::to_string(z.real());
    res << removeTrailingZeros(realStr);
    if (std::abs(z.imag()) >= EPS){
        std::string imagStr = std::to_string(z.imag());
        res << "+" << removeTrailingZeros(imagStr) << "i";
    } 
    return res.str();
}

std::string removeTrailingZeros(std::string& value){
    auto dotPos = value.find('.');
    if (dotPos != std::string::npos) {
        value = value.substr(0, value.find_last_not_of('0') + 2);
    }
    return value;
}

void printHelp(){
    std::cout << "No help message yet..." << std::endl;
}