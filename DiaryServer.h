#include "INotesController.h"
#include "IUsersController.h"

#include <DiaryServerWorker.h>
#include <QTcpServer>

#ifndef DIARYSERVER_H
#define DIARYSERVER_H

#endif // DIARYSERVER_H
class DiaryServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(DiaryServer)
public:
    explicit DiaryServer(IUsersController& usersController, INotesController& notesController, QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void logMessage(const QString &msg);
private slots:
    void jsonReceived(DiaryServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(DiaryServerWorker *sender);
    void userError(DiaryServerWorker *sender);
private:
    QVector<DiaryServerWorker *> m_clients;
    INotesController *notesController;
    IUsersController *usersController;
};

