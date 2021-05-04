#ifndef DIARYSERVERWORKER_H
#define DIARYSERVERWORKER_H

#include "INotesController.h"
#include "IUsersController.h"

#include <QObject>
#include <QTcpSocket>

class DiaryServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiaryServerWorker)
public:
    explicit DiaryServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userLogin() const;
    void setUserLogin(const QString &userLogin);
    void sendJson(const QJsonObject &jsonData);
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    QTcpSocket *m_serverSocket;
    QString m_userLogin;
};

#endif // DIARYSERVERWORKER_H
