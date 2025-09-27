#include "rpc_application.h"
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

RPCConfig RPCApplication::m_config;
void showArgsHelp()
{
    std::cout << "format: command -i <config_file>" << std::endl;
}

void RPCApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        showArgsHelp();
        exit(EXIT_FAILURE);
    }
    int c = 0;
    std::string config_file_;
    while((c=getopt(argc, argv, "i:"))!=-1){
        switch(c){
            case 'i':
                config_file_ = std::string(optarg);
                break;
            case '?':
                cout<<"invalid agrs"<<endl;
                showArgsHelp();
                exit(EXIT_FAILURE);
            case ':':
                cout<<"need config file"<<endl;
                showArgsHelp();
                exit(EXIT_FAILURE);
        }
    }
    // 加载配置文件
    m_config.LoadConfigFile(config_file_.c_str());
}

RPCApplication& RPCApplication::GetInstance()
{
    static RPCApplication app;
    return app;
}