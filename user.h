#pragma once
#ifndef USER_H
#define USER_H
#include<string>
using namespace std;
class User {
public:
    User();
    string getLogin() const;
    void setLogin(const string &value);

    string getPassword() const;
    void setPassword(const string &value);

    int getId() const;
    void setId(int value);

    void Display();

    string ToString();
private:
    string login;
    string password;
    int id;
};

#endif // USER_H



