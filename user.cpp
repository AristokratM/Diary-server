#include "user.h"
#include <iostream>
#include <iomanip>
User::User()
{

}
string User::getLogin() const
{
    return login;
}

void User::setLogin(const string &value)
{
    login = value;
}

string User::getPassword() const
{
    return password;
}

void User::setPassword(const string &value)
{
    password = value;
}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}
string User::ToString()
{
    return  "Login " + getLogin() + "\n";
}
void User::Display()
{
    cout<<this->ToString();
}
