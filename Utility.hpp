#ifndef FAULTYDISK_UTILITY_HPP
#define FAULTYDISK_UTILITY_HPP

#include <string>
#include <cstring>

#define R_LEN 37
#define D_LEN 49
#define W_LEN 48
#define A_LEN 49

namespace util{
    unsigned char* createWrite(const std::string& file, const unsigned int& loc, const unsigned short& len, const char* data);

    bool validWrite (char* ack);

    unsigned char* createRead(const std::string& file, const int& loc);

    bool parseRead(char* data);
}

#endif //FAULTYDISK_UTILITY_HPP
