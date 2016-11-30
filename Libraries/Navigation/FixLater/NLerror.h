#ifndef NLerror_h
#define NLerror_h

#include <stdexcept>
#include <string>


class NLerror: public std::runtime_error {
public:
    NLerror(const std::string s):runtime_error(s){};
};

#endif