#include "rpc_provider.h"
#include <string>
#include "rpc_application.h"
void RPCProvider::NotifyService(::google::protobuf::Service* service){

}

void RPCProvider::Run(){
    auto& config = RPCApplication::GetConfig();
    std::string ip = config.Load("rpc_server_ip");
    uint16_t port = std::stoi(config.Load("rpc_server_port").c_str());
    muduo::net::InetAddress addr(ip, port);
    muduo::net::TcpServer server(&m_event_loop, addr, "RPCProvider");

    // 设置回调

    // 1. 连接回调
    server.setConnectionCallback(std::bind(&RPCProvider::OnConnection, this, std::placeholders::_1));
    // 2. 消息到达回调
    server.setMessageCallback(std::bind(&RPCProvider::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    // 设置线程数量
    server.setThreadNum(4);

    std::cout << "RPCProvider start at " << ip << ":" << port << std::endl;
    server.start();
    m_event_loop.loop();
}

void RPCProvider::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        // 新连接
        std::cout << "New connection from " << conn->peerAddress().toIpPort() << std::endl;
    }
    else
    {
        // 连接断开
        std::cout << "Connection from " << conn->peerAddress().toIpPort() << " disconnected" << std::endl;
        conn->shutdown(); // 关闭连接
    }
}

void RPCProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp time)
{
    // 1. 获取完整消息
    std::string recv_buf = buffer->retrieveAllAsString();
    // 2. 反序列化
    std::cout << "recv_buf: " << recv_buf << std::endl;
    // 3. 创建rpc请求和响应
}