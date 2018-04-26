//
//  main.cpp
//  testGrpc_Router_Client
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include "RouterClient.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    RouterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string key("redis");
    std::string value("fast");
    std::string response = client.Store(key, value);
    std::cout << "Server sent the response as: " << response << std::endl;
    
    return 0;
}
