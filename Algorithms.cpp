#include "Algorithms.hpp"

std::vector <char*> algo::vectorize(char *memblock, const int &segs, const int &lenRem) {
    std::vector<char*> vect;
    for(int x = 0; x < segs; x++){
        if(x < segs - 1) {
            vect.push_back(new char[10]);
            memcpy(vect[x], memblock + x, 10);
        }else{
            if(lenRem > 0){
                vect.push_back(new char[lenRem]);
                memcpy(vect[x], memblock + x, lenRem);
            }else{
                vect.push_back(new char[10]);
                memcpy(vect[x], memblock + x, 10);
            }
        }
    }
    return vect;
}

char* algo::devectorize(const std::vector<char *> &vect) {
    char* memblock = new char[((vect.size() - 1) * 10) + strlen(vect[vect.size() - 1])];
    for(int x = 0; x < vect.size(); x++){
        memcpy(memblock + x, vect[x], strlen(vect[x]));
    }
    return memblock;
}
