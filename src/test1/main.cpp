#include<iostream>
#include<string>
#include "test.h"

int main(int argc, char **agrv)
{
    std::string ret = rabin_karp("hello world", "world");
    std::cout << ret << std::endl;
    return 0;
}