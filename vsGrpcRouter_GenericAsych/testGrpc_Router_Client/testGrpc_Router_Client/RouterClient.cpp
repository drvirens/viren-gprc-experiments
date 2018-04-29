//
//  RouterClient.cpp
//  testGrpc_Router_Client
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include "RouterClient.hpp"

RouterClient::RouterClient(std::shared_ptr<Channel> channel)
 : stub_(VSStoreDB::NewStub(channel))
{}

void RouterClient::Store(const std::string& key, const std::string& value)
{
    StoreRequest request;
    request.set_key(key);
    request.set_value(value);
  
    AsynchClientCall* call = new AsynchClientCall();
    call->response_reader_ = stub_->PrepareAsyncStore(&call->context_,
                                request, &cq_);
    call->response_reader_->StartCall();
    call->response_reader_->Finish(&call->response_, &call->status_, (void*)call);
}

void RouterClient::AsyncCompleteRpc() {
    void* got_tag;
    bool ok = false;
  
    while (cq_.Next(&got_tag, &ok)) {
      AsynchClientCall* call = static_cast<AsynchClientCall*>(got_tag);
      GPR_CODEGEN_ASSERT(ok);
      if (call->status_.ok()) {
        std::cout << "RouterClient received: " << call->response_.message() << std::endl;
      } else {
        std::cout << "RouterClient RPC call fucking failed"<< std::endl;
      }
      delete call;
    } //end while
}
