#ifndef FAULTYDISK_ALGORITHMS_HPP
#define FAULTYDISK_ALGORITHMS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cstring>

namespace algo{
    std::vector <char*> vectorize (char* memblock, const int& segs, const int& lenRem);

    char* devectorize (const std::vector<char*>& vect);

    char* vote (const std::vector<char*>& vect);
}

#endif //FAULTYDISK_ALGORITHMS_HPP
