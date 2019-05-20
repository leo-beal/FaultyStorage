#include "Utility.hpp"



unsigned char* util::createWrite(const std::string &file, const unsigned int &loc, const unsigned short &len, char *data) {
    unsigned char* msg = new unsigned char[W_LEN];

    //Set first byte to W (Write) opcode
    msg[0] = 'W';

    //Set bytes 1 - 32 to the file to write to
    for (int x = 0; x < 32; x++){
        if(file.size() < x){
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