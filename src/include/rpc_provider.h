#pragma once
#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
// pub rpc
class RPCProvider {
public:
    RPCProvider(){}
    // 发布RPC服务接口
    void NotifyService(::google::protobuf::Service* service);
    // 启动RPC服务
    void Run();
private:
    std::map<std::string, ::google::protobuf::Service*> m_services;
    muduo::net::EventLoop m_event_loop;

    // 建立新连接时的回调函数
    void OnConnection(const muduo::net::TcpConnectionPtr& conn);
    // 读取数据时回调函数
    void OnMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buffer,
                   muduo::Timestamp time);

};