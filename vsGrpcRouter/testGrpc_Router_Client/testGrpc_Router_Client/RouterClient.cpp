//
//  RouterClient.cpp
//  testGrpc_Router_Client
//
//  Created by Virendra Shakya on 4/25/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include "RouterClient.hpp"

RouterClient::RouterClient(std::shared_ptr<Channel> channel) : stub_(VSStoreDB::NewStub(channel))
{}

std::string RouterClient::Store(const std::string& key, const std::string& value)
{
    StoreRequest request;
    request.set_key(key);
    request.set_value(value);
    
    StoreResponse response;
    ClientContext context;
    CompletionQueue q;
    Status status;
    
    std::unique_ptr<ClientAsyncResponseReader<StoreResponse> > rpc(stub_->PrepareAsyncStore(&context, request, &q));
    rpc->StartCall();
    
    rpc->Finish(&response, &status, (void*)1);
    void* got_tag;
    bool ok = false;
    GPR_CODEGEN_ASSERT(q.Next(&got_tag, &ok));
    GPR_CODEGEN_ASSERT(got_tag == (void*)1);
    GPR_CODEGEN_ASSERT(ok);
    
    if (status.ok()) {
        return response.message();
    }
    return "RPC fucking failed";
}
