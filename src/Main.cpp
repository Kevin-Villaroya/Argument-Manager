#include <cstdlib>
#include <iostream>

#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <vector>

#include "arguments/ManagerArguments.hpp"

int main(int argc, char* argv[]){
    ManagerArguments manager(argc, argv);

    //check the existence of the argument -minThread with a value int
    manager.checkRequiredArgument("-command");

    if(manager.contains("-h")){
        std::cout << "This is the help menu <TODO>" << std::endl;
        exit(0);
    }

    if(manager.contains("-command")){
        std::cout << manager.getValue<int>("-command") << std::endl;
    }

    return EXIT_SUCCESS;
}