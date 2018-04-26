//
//  RouterServer.cpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include "RouterServer.hpp"

::grpc::Status StorageServiceImpl::Store(::grpc::ServerContext* context, const ::route::StoreRequest* request, ::route::StoreResponse* response) {
    std::string prefix("ServerSentResponseString: this is key: [");
    response->set_message(prefix + request->key() + "] and value is [" + request->value() + "]");
    return Status::OK;
}

::grpc::Status StorageServiceImpl::Get(::grpc::ServerContext* context, const ::route::GetRequest* request, ::route::GetResponse* response) {
    return Status::OK;
}

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    StorageServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    //assemble server
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    server->Wait();
}
