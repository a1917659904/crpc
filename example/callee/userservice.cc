#include<iostream>
#include<string>
#include "user.pb.h"
#include "rpc_application.h"
#include "rpc_provider.h"
using namespace std;
using namespace example;

class UserService : public UserServiceRpc{
public:
    bool Login(const string name, const string pwd){
        cout << "name: " << name << " pwd: " << pwd << endl;
        return true;
    }

    void Login(::google::protobuf::RpcController* controller,
                       const ::example::LoginRequest* request,
                       ::example::LoginResponse* response,
                       ::google::protobuf::Closure* done){
        bool ret = Login(request->name(), request->pwd());
        if(ret){
            response->mutable_result()->set_code(200);
            response->mutable_result()->set_msg("");
        }else{
            response->mutable_result()->set_code(400);
            response->mutable_result()->set_msg("login failed");
        }
        done->Run();
    }
};

int main(int argc, char** argv){
    RPCApplication::Init(argc, argv);
    RPCProvider provider;
    provider.NotifyService(new UserService());
    provider.Run(8080);
    return 0;
}