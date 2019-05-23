#include <iostream>
#include <string>

#include "Utility.hpp"
#include "Algorithms.hpp"

int main(){

    char* mem;
    int segs;
    int remLen;

    std::vector<char*> chunks;

    mem = util::readBlock("D:\\cs\\cs6890\\FaultyDisk\\TestData\\LargeTextFile.txt", segs, remLen);

    std::cout << "segs: " << segs << " remLen: " << remLen << " size: " << segs*10 + remLen << std::endl;

    int size = segs * 10 + remLen;

    if(remLen > 0) {
        size -= 10;
    }

    chunks = algo::vectorize(mem, segs, remLen);

    std::cout << "vector size: " << chunks.size() << std::endl;

    mem = algo::devectorize(chunks, remLen);

    size += 1;
    char* memp = new char[size];
    memcpy(memp, mem, size - 1);
    memp[size - 1] = 0;

    util::writeBlcok("D:\\cs\\cs6890\\FaultyDisk\\SafeZone\\LargeTextFile", (unsigned char*)mem, size);

    return 0;
}
