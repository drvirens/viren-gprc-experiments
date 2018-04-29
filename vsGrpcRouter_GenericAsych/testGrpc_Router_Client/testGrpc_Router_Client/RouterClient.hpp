//
//  RouterClient.hpp
//  testGrpc_Router_Client
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef RouterClient_hpp
#define RouterClient_hpp

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "router.grpc.pb.h"
#include "router.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using route::StoreRequest;
using route::StoreResponse;
using route::VSStoreDB;

class RouterClient {
  public:
    explicit RouterClient(std::shared_ptr<Channel> channel);
    void Store(const std::string& key, const std::string& value);
    void AsyncCompleteRpc();
    
  private:
    struct AsynchClientCall {
      route::StoreResponse response_;
      grpc::ClientContext context_;
      grpc::Status status_;
      std::unique_ptr<grpc::ClientAsyncResponseReader<route::StoreResponse>> response_reader_;
    };
    std::unique_ptr<VSStoreDB::Stub> stub_;
    grpc::CompletionQueue cq_;
};

#endif /* RouterClient_hpp */
