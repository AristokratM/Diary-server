QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DiaryServer.cpp \
    DiaryServerWorker.cpp \
    UserDAO.cpp \
    UsersController.cpp \
    main.cpp \
    mainwindow.cpp \
    note.cpp \
    notedao.cpp \
    notescontroller.cpp \
    user.cpp

HEADERS += \
    DiaryServer.h \
    DiaryServerWorker.h \
    INotesController.h \
    IUsersController.h \
    UserDAO.h \
    UsersController.h \
    mainwindow.h \
    note.h \
    notedao.h \
    notescontroller.h \
    user.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
