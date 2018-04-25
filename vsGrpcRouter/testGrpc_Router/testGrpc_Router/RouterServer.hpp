//
//  RouterServer.hpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef RouterServer_hpp
#define RouterServer_hpp

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "router.pb.h"
#include "router.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using route::StoreRequest;
using route::StoreResponse;
using route::VSStoreDB;

#endif /* RouterServer_hpp */
