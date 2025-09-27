#pragma once
#include "google/protobuf/service.h"
// pub rpc
class RPCProvider {
public:
    RPCProvider(){}
    // 发布RPC服务接口
    void NotifyService(::google::protobuf::Service* service);
    // 启动RPC服务
    void Run(int port);
private:
    std::map<std::string, ::google::protobuf::Service*> m_services;
};