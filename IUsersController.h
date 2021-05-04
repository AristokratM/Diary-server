#ifndef IUSERSCONTROLLER_H
#define IUSERSCONTROLLER_H


#include "user.h"

#include <iterator>
#include <vector>
class IUsersController {

public:
    virtual User& AddUser(const string& login, const  string& password) = 0;
    virtual User GetUser(const int& id) = 0;
    virtual vector<User> GetAllUsers() = 0;
    virtual int CorrectLoginAndPassword(const string& login, const  string& password) = 0;
};
#endif // IUSERSCONTROLLER_H
