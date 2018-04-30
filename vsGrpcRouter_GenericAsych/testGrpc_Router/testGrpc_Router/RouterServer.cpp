//
//  RouterServer.cpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpc/support/log.h>

#include "router.pb.h"
#include "RouterServer.hpp"
#include "CCallData.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using route::StoreRequest;
using route::StoreResponse;
using route::VSStoreDB;


RouterServer::RouterServer() {
}

RouterServer::~RouterServer() {
  server_->Shutdown();
  cq_->Shutdown();
}

void RouterServer::HandleIncomingRpcRequests() {
  new CCallData(&asynch_service_, cq_.get());
  void* tag;
  bool ok;
  while(true) {
    //
    //block waiting to read the next event from the completion queue.
    //the event is uniquely identified by its tag - which here is gonna
    //be memory address of CCallData instance : this pointer
    //Return value of Next should always be checked. This return
    //value tells us whether there is any kind of event or cq_ is
    //shutting down.
    //
    bool ret = cq_->Next(&tag, &ok);
    if (ret) {
      std::cout << "cq_->Next returned true" << std::endl;
    }
    if (ok) {
      std::cout << "ok returned true" << std::endl;
    }
    CCallData* c = static_cast<CCallData*>(tag);
    if (c) {
      c->Proceed();
    }
  } //end while
}

void RouterServer::RunServer() {
    grpc_init();
    gpr_set_log_verbosity(GPR_LOG_SEVERITY_INFO);
    grpc_tracer_set_enabled("all", 1);

    std::string server_address("0.0.0.0:50051");
    
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&asynch_service_);
    cq_ = builder.AddCompletionQueue();
    
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    HandleIncomingRpcRequests();
    
    grpc_shutdown();
}
