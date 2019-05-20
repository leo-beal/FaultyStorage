#include <iostream>
#include <string>

#include "Utility.hpp"

int main(){

    std::string data = "ur mom gay";

    const char* stuff = data.c_str();

    auto msg = util::createWrite("test.txt", 0, 10, stuff);

    std::cout << msg << std::endl;

    delete msg;

    return 0;
}