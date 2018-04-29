//
//  CCallData.hpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/28/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef CCallData_hpp
#define CCallData_hpp

#include <grpcpp/grpcpp.h>
#include "router.grpc.pb.h"

class CCallData {
 public:
   CCallData(route::VSStoreDB::AsyncService* asynch_service,
              grpc::ServerCompletionQueue* cq);
   ~CCallData();
   void Proceed();
  
 private:
   void doActuallProcessing();
 
 private:
   route::VSStoreDB::AsyncService* asynch_service_;
   grpc::ServerCompletionQueue* cq_;
   grpc::ServerContext ctx_;
   route::StoreRequest request_;
   route::StoreResponse response_;
   grpc::ServerAsyncResponseWriter<route::StoreResponse> responder_;
  
   enum ECallStatus {
    eCallStatus_Create,
    eCallStatus_Process,
    eCallStatus_Finish
   };
   ECallStatus status_;
};

#endif /* CCallData_hpp */
