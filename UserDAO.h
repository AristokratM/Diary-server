#ifndef USERDAO_H
#define USERDAO_H
#include<string>
#include <vector>
#include "user.h"
#include <QtSql>
using namespace std;

class UserDAO
{
public:
    UserDAO();
    ~UserDAO();
    User& AddUser(const string& login, const  string& password);
    User GetUser(const int& id) ;
    int CorrectLoginAndPassword(const string& login, const  string& password);
    vector<User> GetAllUsers();
};
#endif // USERDAO_H
