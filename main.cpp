#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

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

char* getFiles(int segs, int lenRem){
    char* memBlock;
    std::vector<std::vector<char*>*> chunkedChunks;
    std::vector<char*> chunks;

    for(int x = 0; x < segs; x++){
        unsigned char* toSend;
        unsigned char* ack;
        char* parsed;
        short len;
        chunkedChunks.push_back(new std::vector<char*>);
        for(int y = 0; y < numFiles; y++) {
            toSend = util::createRead(files[y], x * 10);
            do {
                int ret;
                util::sendUDP(toSend);
                ack = util::getUDP(ret);
            } while (!util::parseRead((char *) ack, parsed, len));
            chunkedChunks[x]->push_back(parsed);
        }
        if (algo::discrep(*chunkedChunks[x], len)){
            chunks.push_back(algo::vote(*chunkedChunks[x], len));
        }else{
            chunks.push_back(chunkedChunks[x]->at(0));
        }
        delete ack;
    }

    memBlock = algo::devectorize(chunks, lenRem);

    return memBlock;
}

int main(int argc, char* argv[]) {

    //Windows:
    //Test data string "D:\\cs\\cs6890\\FaultyDisk\\TestData\\SmalTextFile.txt"
    //Safe zone string "D:\\cs\\cs6890\\FaultyDisk\\SafeZone\\SmalTextFile.txt"

    numFiles = 3;
    int wait = 30;
    std::string readFrom = "D:\\cs\\cs6890\\FaultyDisk\\TestData\\SmalTextFile.txt";
    std::string writeTo = "D:\\cs\\cs6890\\FaultyDisk\\SafeZone\\SmalTextFile.txt";

    for(int x = 0; x < argc; x++){
        if(std::string(argv[x]) == "-n"){
            try {
                numFiles = std::stoi(std::string(argv[x+1]));
                x++;
            }catch(...){
                std::cout << "Improper usage of -n. Defaulting to 3 copies." << std::endl;
            }
        }
        if(std::string(argv[x]) == "-t"){
            try{
                wait = std::stoi(std::string(argv[x+1]));
                x++;
            }catch(...){
                std::cout << "Improper usage of -t. Defaulting to 30 seconds" << std::endl;
            }
        }
        if(std::string(argv[x]) == "-r"){
            readFrom = std::string(argv[x+1]);
            x++;
        }
        if(std::string(argv[x]) == "-w"){
            writeTo = std::string(argv[x+1]);
            x++;
        }
    }

    util::init();

    char* file;
    char* toWrite;
    int segs;
    int lenRem;
    int size;

    file = util::readBlock(readFrom, segs, lenRem);

    size = segs * 10 + lenRem;

    if(lenRem > 0) {
        size -= 10;
    }

    sendFiles(file, segs, lenRem);

    std::this_thread::sleep_for(std::chrono::seconds(wait));

    toWrite = getFiles(segs, lenRem);

    util::writeBlcok(writeTo, (unsigned char*)toWrite, size);

    util::end();


    return 0;
}
