//
//  main.cpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/24/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include "RouterServer.hpp"

int main(int argc, const char * argv[]) {
    int i = 100;
    i = 23;
    std::cout << "Hello, World aha" << i << std::endl;
    
    RunServer();
    
    return 0;
}
