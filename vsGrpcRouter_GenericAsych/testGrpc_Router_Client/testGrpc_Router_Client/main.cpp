//
//  main.cpp
//  testGrpc_Router_Client
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <thread>
#include "RouterClient.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";

    bool usenginxproxy = true;
    std::stringstream ss;
    std::string local_host;
    int port;
    if (usenginxproxy) {
      port = 80; //80?
    } else {
      port = 50051;
    }
    ss << "localhost:" << port;
    local_host = ss.str();
  
    RouterClient client(grpc::CreateChannel(local_host,
                              grpc::InsecureChannelCredentials()));
    std::thread the_thread = std::thread(&RouterClient::AsyncCompleteRpc,
                                          &client);
  
    for (int i = 0; i < 1; i++) {
      std::stringstream k;
      k << "keY_" << i;
      std::string key = k.str();
      
      std::stringstream v;
      v << "value_" << i;
      std::string value = v.str();
      
      client.Store(key, value);
    }
  
    the_thread.join();
    
    return 0;
}
