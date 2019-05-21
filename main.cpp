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

int main(int argc, char* argv[]) {
    //Needs to be converted to c string
    std::string what("ur mom ga");

    int ret;

    util::init();

    auto msg = util::createWrite("test.txt", 0, 9, what.c_str());

    //end of file
    auto rd = util::createRead("test.txt", 10);

    unsigned char* data;

    char* parsed;

    short len;

    //util::sendUDP("127.0.0.1", msg);

    //auto t1 = std::make_shared<std::thread>(getUDP);
    //auto t2 = std::make_shared<std::thread>(util::sendUDP, "127.0.0.1", msg);

    //t2->join();
    //t1->join();

    util::sendUDP(msg);

    util::getUDP(ret);

    util::sendUDP(rd);

    data = util::getUDP(ret);

    util::parseRead((char*)data, parsed, len);

    std::cout << parsed << " " << len << " " << strlen(parsed) << std::endl;

    util::end();

    return 0;
}
