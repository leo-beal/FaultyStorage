#ifndef FAULTYDISK_UTILITY_HPP
#define FAULTYDISK_UTILITY_HPP

#include <string>

namespace util{
    char* createWrite(const std::string& file, const int& loc, const int& len, char* data);

    bool validWrite (char* ack);

    char* createRead(const std::string& file, const int& loc);

    bool parseRead(char* data);
}

#endif //FAULTYDISK_UTILITY_HPP
