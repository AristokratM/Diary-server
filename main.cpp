#include "mainwindow.h"
#include <DiaryServer.h>
#include <QApplication>
#include <QSqlDatabase>
#include <UserDAO.h>
#include <UsersController.h>
#include <notedao.h>
#include <notescontroller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("Diary.sqlite");
    if (!sdb.open())
    {
        qDebug() << sdb.lastError().text();
    }

    if(!sdb.open())
    {
        qDebug() << "Что-то не так с соединением!";
        return -1;
    }
    NoteDAO* noteDAO = new NoteDAO();
    UserDAO* userDAO = new UserDAO();
    INotesController* notesController = new NotesController(*noteDAO);
    IUsersController* usersController = new UsersController(*userDAO);

    MainWindow w;
    DiaryServer *ds = new DiaryServer(*usersController, *notesController);
    w.show();
    return a.exec();
}
