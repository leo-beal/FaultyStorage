#include <iostream>
#include <string>

#include "Utility.hpp"

int main(){
    int sockfd;
    char buffer[MAXLINE];
    std::string what("ur mom gay");
    auto msg = util::createWrite("test.txt", 0, 10, what.c_str());
    struct sockaddr_in servaddr;



    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
/*


    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_OUT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");



    sendto(sockfd, (const char *)msg, W_LEN,
           0, (const struct sockaddr *) &servaddr,
           sizeof(servaddr));
    printf("Write message sent.\n");

    close(sockfd);

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    */

    int n, len;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_IN);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        return 0;
    }
    for(int i = 0; i < 10000; i++) {
        n = recv(sockfd, (char *) buffer, MAXLINE,
                     0);

        std::cout << n << std::endl << std::flush;
        std::cout << i << std::endl << std::flush;
        if (n >= 0){
            close(sockfd);
            return 0;
        }
    }

    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}