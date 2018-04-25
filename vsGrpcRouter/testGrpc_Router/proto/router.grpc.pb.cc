// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: proto/router.proto

#include "proto/router.pb.h"
#include "proto/router.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace route {

static const char* VSStoreDB_method_names[] = {
  "/route.VSStoreDB/Store",
  "/route.VSStoreDB/Get",
};

std::unique_ptr< VSStoreDB::Stub> VSStoreDB::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< VSStoreDB::Stub> stub(new VSStoreDB::Stub(channel));
  return stub;
}

VSStoreDB::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Store_(VSStoreDB_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Get_(VSStoreDB_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status VSStoreDB::Stub::Store(::grpc::ClientContext* context, const ::route::StoreRequest& request, ::route::StoreResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Store_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::route::StoreResponse>* VSStoreDB::Stub::AsyncStoreRaw(::grpc::ClientContext* context, const ::route::StoreRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::route::StoreResponse>::Create(channel_.get(), cq, rpcmethod_Store_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::route::StoreResponse>* VSStoreDB::Stub::PrepareAsyncStoreRaw(::grpc::ClientContext* context, const ::route::StoreRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::route::StoreResponse>::Create(channel_.get(), cq, rpcmethod_Store_, context, request, false);
}

::grpc::Status VSStoreDB::Stub::Get(::grpc::ClientContext* context, const ::route::GetRequest& request, ::route::GetResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Get_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::route::GetResponse>* VSStoreDB::Stub::AsyncGetRaw(::grpc::ClientContext* context, const ::route::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::route::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::route::GetResponse>* VSStoreDB::Stub::PrepareAsyncGetRaw(::grpc::ClientContext* context, const ::route::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::route::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, false);
}

VSStoreDB::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VSStoreDB_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VSStoreDB::Service, ::route::StoreRequest, ::route::StoreResponse>(
          std::mem_fn(&VSStoreDB::Service::Store), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VSStoreDB_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VSStoreDB::Service, ::route::GetRequest, ::route::GetResponse>(
          std::mem_fn(&VSStoreDB::Service::Get), this)));
}

VSStoreDB::Service::~Service() {
}

::grpc::Status VSStoreDB::Service::Store(::grpc::ServerContext* context, const ::route::StoreRequest* request, ::route::StoreResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VSStoreDB::Service::Get(::grpc::ServerContext* context, const ::route::GetRequest* request, ::route::GetResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace route

