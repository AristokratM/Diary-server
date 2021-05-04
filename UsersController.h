#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

#include "UserDAO.h"
#include "IUsersController.h"

class UsersController:  public IUsersController
{
public:
    UsersController(UserDAO& noteDAO);
    User& AddUser(const string& login, const  string& password);
    User GetUser(const int& id) ;
    vector<User> GetAllUsers();
    int CorrectLoginAndPassword(const string& login, const  string& password);
private:
    UserDAO *userDAO;
};

#endif // USERSCONTROLLER_H
