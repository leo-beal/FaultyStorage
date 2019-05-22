#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include <vector>
#include <memory>

//set this to only import on windows. Use unistd on linux.
#include <windows.h>

#include "Utility.hpp"
#include "Algorithms.hpp"

int numFiles;
std::vector<std::string> files;

void sendFiles(char* memBlock, int segs, int lenRem){
    std::vector<char*> data = algo::vectorize(memBlock, segs, lenRem);
    for(int x = 0; x < numFiles; x++){
        files.push_back("file_" + std::to_string(x));
    }
    for(int x = 0; x < data.size() - 1; x++){
        unsigned char* toSend;
        unsigned char* ack;
        for(int y = 0; y < numFiles; y++){
            toSend = util::createWrite(files[y], x * 10, 10, data[x]);
            do{
                int ret;
                util::sendUDP(toSend);
                ack = util::getUDP(ret);
            }while(!util::validWrite((char*)ack));
        }
    }

    for(int x = 0; x < numFiles; x++){
        unsigned char* toSend;
        unsigned char* ack;
        if(lenRem > 0){
            toSend = util::createWrite(files[x], (data.size() - 1) * 10, lenRem, data[data.size() - 1]);
        }else{
            toSend = util::createWrite(files[x], (data.size() - 1) * 10, 10, data[data.size() - 1]);
        }
        do{
            int ret;
            util::sendUDP(toSend);
            ack = util::getUDP(ret);
        }while(!util::validWrite((char*)ack));
        delete ack;
    }
}

int main(int argc, char* argv[]) {

    util::init();

    char* file;
    int segs;
    int lenRem;
    int size;
    int wait;
    std::string readFrom = "D:\\cs\\cs6890\\FaultyDisk\\TestData\\SmalTextFile.txt";
    std::string writeTo;

    numFiles = 3;

    file = util::readBlock(readFrom, segs, lenRem);

    size = segs * 10 + lenRem;

    if(lenRem > 0) {
        size -= 10;
    }

    sendFiles(file, segs, lenRem);

    util::end();


    return 0;
}
