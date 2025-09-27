#include "rpc_config.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void RPCConfig::Trim(std::string& src_buf){
    // 去除前导空格
    int idx = src_buf.find_first_not_of(' ');
    if(idx!=-1){
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // 去掉后导空格
    idx = src_buf.find_last_not_of(' ');
    if(idx!=-1){
        src_buf = src_buf.substr(0, idx+1);
    }
}
void RPCConfig::LoadConfigFile(const char* config_file){
    FILE* pf=fopen(config_file, "r");
    if(pf==nullptr){
        std::cout << "cannot open config file: " << config_file << std::endl;
        exit(EXIT_FAILURE);
    }
    /*
        1. 去除前导空格
        2. 清理注释
        3. 获取key=value
    */
    while(!feof(pf)){
        char buf[512] = {0};
        fgets(buf, 512, pf);
        string str_buf(buf);
        Trim(str_buf);
        // 去掉注释
        if(str_buf[0]=='#' || str_buf.empty()) continue;
        int idx = str_buf.find('=');
        if(idx==-1) continue;
        int endidx = str_buf.find('\n', idx);
        string key = str_buf.substr(0, idx);
        Trim(key);
        string value = str_buf.substr(idx+1, endidx-idx-1);
        Trim(value);
        m_configMap.insert({key, value});
    }
}

std::string RPCConfig::Load(const std::string& key){
    auto it = m_configMap.find(key);
    if(it==m_configMap.end()){
        return "";
    }
    return it->second;
}