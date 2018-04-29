//
//  RouterServer.hpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef RouterServer_hpp
#define RouterServer_hpp

#include <grpcpp/grpcpp.h>
#include "router.grpc.pb.h"

class RouterServer final {
 public:
   RouterServer();
   ~RouterServer();
    void RunServer();
  
  private:
    void HandleIncomingRpcRequests();
    
  private:
    route::VSStoreDB::AsyncService asynch_service_;
    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;
};



#endif /* RouterServer_hpp */
