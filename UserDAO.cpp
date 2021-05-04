#include "UserDAO.h"

#include <stdexcept>

UserDAO::UserDAO()
{

}
UserDAO::~UserDAO() {

}

User& UserDAO::AddUser(const string& login, const  string& password) {
    User* user = new User();
    user->setLogin(login);
    user->setPassword(password);
    QSqlQuery query;
    query.prepare("INSERT INTO Users(login, password) "
            "VALUES(:login, :password);");

    query.bindValue(":title", QString::fromStdString(user->getLogin()));
    query.bindValue(":text", QString::fromStdString(user->getLogin()));
    if (!query.exec())
    {
        qDebug() << "Кажется данные не вставляются, " + query.lastError().text();
    }
    return *user;
}

vector<User> UserDAO::GetAllUsers() {
    vector<User> users;
    QString str = "SELECT * FROM Users;";
    QSqlQuery query;
    if (query.exec(str))
    {
        QSqlRecord record = query.record();
        int id = 0;
        QString login = "", password = "";

        while (query.next())
        {
            id = query.value(record.indexOf("id")).toInt();
            login = query.value(record.indexOf("login")).toString();
            password = query.value(record.indexOf("password")).toString();

            User *user = new User();
            user->setId(id);
            user->setLogin(login.toStdString());
            user->setPassword(password.toStdString());
            users.push_back(*user);
         }
    }
    return users;
}

User UserDAO::GetUser(const int& id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE id=:id;");
    query.bindValue(":id", id);
    if (query.exec())
    {
        QSqlRecord record = query.record();
        int id = 0;
        QString login = "", password = "";
            id = query.value(record.indexOf("id")).toInt();
            login = query.value(record.indexOf("login")).toString();
            password = query.value(record.indexOf("password")).toString();

            User *user = new User();
            user->setId(id);
            user->setLogin(login.toStdString());
            user->setPassword(password.toStdString());
    }
    throw logic_error("No user found!");
}
int UserDAO::CorrectLoginAndPassword(const string& login, const  string& password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE login=:login and password=:password;");
    query.bindValue(":login", QString::fromStdString(login));
    query.bindValue(":password", QString::fromStdString(password));
    if (query.exec())
    {
          QSqlRecord record = query.record();
        while(query.next()) {
            if (record.count() == 0) return -1;
            return query.value(record.indexOf("id")).toInt();
        }
    }
    return -1;
}

