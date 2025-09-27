#pragma once
#include "rpc_config.h"
// 负责框架初始化
class RPCApplication
{
private:
    RPCApplication(){}
    ~RPCApplication(){}
    RPCApplication(const RPCApplication&) = delete;
    RPCApplication& operator=(const RPCApplication&) = delete;
public:
    static RPCConfig m_config;
    static void Init(int argc, char **argv);
    static RPCApplication& GetInstance();
    static RPCConfig& GetConfig();
};