#include "Utility.hpp"



unsigned char* util::createWrite(const std::string &file, const unsigned int &loc, const unsigned short &len, const char *data) {
    unsigned char* msg = new unsigned char[W_LEN];

    //Set first byte to W (Write) opcode
    msg[0] = 'W';

    //Set bytes 1 - 32 to the file to write to
    for (int x = 0; x < 32; x++){
        if(file.size() > x){
            msg[x + 1] = file.at(x);
        }
        else{
            msg[x + 1] = 0;
        }
    }

    //Set bytes 33-36 to the location
    memcpy(msg + 33, (unsigned char *)&(loc), sizeof(loc));

    //Set byte 37 to the data length
    msg[37] = len;

    //Set bytes 38-47 to the data (Assume zero padded at the end)
    memcpy(msg + 38, data, static_cast<size_t>(len));

    return msg;
}

unsigned char* util::createRead(const std::string &file, const int &loc) {
    unsigned char* msg = new unsigned char[R_LEN];

    return msg;
}

bool util::validWrite(char *ack) {

}

bool util::parseRead(char *data) {

}

void util::sendUDP(std::string IP, const unsigned char *data) {
    int sockfd;
    struct sockaddr_in serv;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv, 0, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_OUT);
    serv.sin_addr.s_addr = inet_addr(IP.c_str());

    //ABSTRACT THIS PLEASE I BEG YOU. toSend and its lengths have to absolutely match 5000%
    if(data[0] == 'W' || data[0] == 'w') {
        sendto(sockfd, data, W_LEN, 0, (const struct sockaddr *) &serv, sizeof(serv));
    }
    if(data[0] == 'R' || data[0] == 'r') {
        sendto(sockfd, data, R_LEN, 0, (const struct sockaddr *) &serv, sizeof(serv));
    }

    close(sockfd);
}

unsigned char* util::getUDP(std::string IP, int& ret) {
    int sockfd;
    unsigned char buffer[MAXLINE];
    unsigned char* retVal;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_IN);
    servaddr.sin_addr.s_addr = inet_addr(IP.c_str());

    int len;
    ssize_t n;

    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        perror("bind");
        exit(1);
    }

    n = recvfrom(sockfd, (unsigned char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *) &servaddr,
                 &len);
    buffer[n] = '\0';

    ret = n;

    std::cout << n << std::endl;

    //std::cout << "Got message: " << buffer[0] << std::endl;

    close(sockfd);

    if(buffer[0] == 'A' || buffer[0] == 'a'){
        retVal = new unsigned char[A_LEN];
        memcpy(retVal, buffer, A_LEN);
    }
    if(buffer[0] == 'D' || buffer[0] == 'd'){
        retVal = new unsigned char[D_LEN];
        memcpy(retVal, buffer, D_LEN);
    }

    close(sockfd);
}

