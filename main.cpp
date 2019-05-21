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

void getUDP(){
    int ret = 0;
    unsigned char* test;
    while(ret <= 0) {
        test = util::getUDP("127.0.0.1", ret);
        //std::cout << sizeof(test) << " " << std::hex << test[sizeof(test - 1)] << std::endl;
        //sleep(1);
    }
}

int main(int argc, char* argv[]) {
    //Needs to be converted to c string
    std::string what("ur mom gay");

    auto msg = util::createWrite("test.txt", 0, 10, what.c_str());

    //util::sendUDP("127.0.0.1", msg);

    //auto t1 = std::make_shared<std::thread>(getUDP);
    auto t2 = std::make_shared<std::thread>(util::sendUDP, "127.0.0.1", msg);

    t2->join();
    //t1->join();



    return 0;
}