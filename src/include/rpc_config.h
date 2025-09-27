#pragma once

#include <unordered_map>
#include <string>
/*
    rpc server ip
    rpc server port
    zookeeper ip
    zookeeper port
*/
class RPCConfig {
public:
    // 加载、解析配置文件
    void LoadConfigFile(const char* config_file);
    // 查询配置项
    std::string Load(const std::string& key);
private:
    std::unordered_map<std::string, std::string> m_configMap;
    void Trim(std::string& src_buf);
};