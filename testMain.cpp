#include <iostream>
#include <string>

#include "Utility.hpp"
#include "Algorithms.hpp"

int main(){

    std::string t1 = "aaaaaaaaaa";
    std::string t2 = "aaaaaaaaaa";
    std::string t3 = "aaaaaaaaaa";

    //char* t3prime = (char*)t3.c_str();
    //t3prime[7] = 0;
    //t3 = t3prime;

    std::vector<unsigned char*> test;

    test.push_back((unsigned char*)t1.c_str());
    test.push_back((unsigned char*)t2.c_str());
    test.push_back((unsigned char*)t3.c_str());

    //char t =

    //std::string t = algo::vote(test);

    std::cout << algo::discrep(test, 10) << std::endl;

    std::cout << algo::vote(test, 10) << " == " << strlen(algo::vote(test, 10)) <<  std::endl;

    return 0;
}
