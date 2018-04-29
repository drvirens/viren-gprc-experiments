//
//  CCallData.cpp
//  testGrpc_Router
//
//  Created by Virendra Shakya on 4/28/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include "CCallData.hpp"


CCallData::CCallData(route::VSStoreDB::AsyncService* asynch_service,
              grpc::ServerCompletionQueue* cq)
            : asynch_service_(asynch_service)
            , cq_(cq)
            , responder_(&ctx_)
            , status_(eCallStatus_Create) {
  Proceed();
}

void CCallData::Proceed() {
  switch (status_) {
    case eCallStatus_Create: {
      status_ = eCallStatus_Process;
      asynch_service_->RequestStore(&ctx_, &request_, &responder_, cq_, cq_, this);
    } break;
    
    case eCallStatus_Process: {
      //spawn new CallData instance to server new clients while we process
      //the one for "this" CallData. The "this" instance will deallocate
      //itself as part of its eCallStatus_Finish state.
      
      new CCallData(asynch_service_, cq_);
      
      doActuallProcessing();
      
      //we're done. notify gRPC runtime we are finished
      status_ = eCallStatus_Finish;
      responder_.Finish(response_, grpc::Status::OK, this);
    } break;
    
    case eCallStatus_Finish: {
      delete this;
    } break;
    
    default: {
    } break;
  } //end switch
}

void CCallData::doActuallProcessing() {
  std::string prefix("Hey there, so server received the key [");
  response_.set_message(prefix + request_.key() + "] and value [" + request_.value() + "]!");
}

CCallData::~CCallData() {
}
