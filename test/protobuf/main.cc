#include "test.pb.h"
#include <string>
#include <iostream>

using namespace test::protobuf;
using namespace std;

int main(){
    LoginRequest req;
    req.set_name("test");
    req.set_pwd("pwd");
    std::string send_str;
    if(req.SerializeToString(&send_str)){
        cout<<send_str.c_str()<<endl;
    }
    LoginRequest parse_req;
    if(parse_req.ParseFromString(send_str)){
        cout<<parse_req.name()<<endl;
        cout<<parse_req.pwd()<<endl;
    }
    LoginReponse resp;
    Result* rc=resp.mutable_result();
    resp.set_success(true);
    rc->set_code(200);
    rc->set_msg("success");
    if(rc->SerializeToString(&send_str)){
        cout<<rc->DebugString()<<endl;
        // 是二进制形式，没办法直接打印
        cout<<send_str.c_str()<<endl;
    }

    GetFriendListRequest get_friend_list_req;
    Result* gres=get_friend_list_req.mutable_result();
    gres->set_code(200);
    gres->set_msg("get friend list success");

    User* user1=get_friend_list_req.add_user();
    user1->set_id(1);
    user1->set_name("friend1");
    user1->set_age(20);
    user1->set_sex(User::MALE);
    User* user2=get_friend_list_req.add_user();
    user2->set_id(2);
    user2->set_name("friend2");
    user2->set_age(30);
    user2->set_sex(User::FEMALE);
    if(get_friend_list_req.SerializeToString(&send_str)){
        cout<<get_friend_list_req.DebugString()<<endl;
        cout<<send_str.c_str()<<endl;
    }
}