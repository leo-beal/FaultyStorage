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

//set this to only import on windows. Use unistd on linux.
#include <windows.h>

#include "Utility.hpp"

#define PORT_OUT 1982
#define PORT_IN 1983
#define MAXLINE 1024

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[MAXLINE];
    //Needs to be converted to c string
    std::string what("ur mom gay");
    struct sockaddr_in serv;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv, 0, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_OUT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n, len;

    auto toSend = util::createWrite("test.txt", 10, 10, what.c_str());

    //ABSTRACT THIS PLEASE I BEG YOU. toSend and its lengths have to absolutely match 5000%.
    sendto(sockfd, toSend, W_LEN, 0, (const struct sockaddr *) &serv, sizeof(serv));

    sleep(5);

    close(sockfd);

    return 0;
}