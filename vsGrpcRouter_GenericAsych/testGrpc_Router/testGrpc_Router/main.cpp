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
    std::cout << "Hello, World aha" << std::endl;
    
    RouterServer server;
    server.RunServer();
    
    
    return 0;
}
