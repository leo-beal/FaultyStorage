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

#include "Utility.hpp"

#define PORT_OUT 1982
#define PORT_IN 1983
#define MAXLINE 1024

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[MAXLINE];
    //Needs to be converted to c string
    std::string what("Wtest.txt000000000000000000000000000000000000000");
    struct sockaddr_in serv;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv, 0, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_OUT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n, len;

    sendto(sockfd, what.c_str(), strlen(what.c_str()), 0, (const struct sockaddr *) &serv, sizeof(serv));

    close(sockfd);

    return 0;
}