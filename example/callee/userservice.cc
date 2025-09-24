#include<iostream>
#include<string>
#include "../user.pb.h"

using namespace std;
using namespace example;

class UserService : public UserServiceRpc{
public:
    bool Login(const string name, const string pwd){
        cout << "name: " << name << " pwd: " << pwd << endl;
        return true;
    }
}