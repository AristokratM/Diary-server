#include <DiaryServer.h>
#include <DiaryServerWorker.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonobject.h>
#include <string>

DiaryServer::DiaryServer(IUsersController& usersController, INotesController& notesController, QObject *parent)
    :QTcpServer(parent)
{
    this->notesController = &notesController;
    this->usersController = &usersController;
}
void DiaryServer::incomingConnection(qintptr socketDescriptor)
{
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    DiaryServerWorker *worker = new DiaryServerWorker(this);
    // we attempt to bind the worker to the client
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        // if we fail we clean up
        worker->deleteLater();
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(worker, &DiaryServerWorker::disconnectedFromClient, this, std::bind(&DiaryServer::userDisconnected, this, worker));
    connect(worker, &DiaryServerWorker::error, this, std::bind(&DiaryServer::userError, this, worker));
    connect(worker, &DiaryServerWorker::jsonReceived, this, std::bind(&DiaryServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &DiaryServerWorker::logMessage, this, &DiaryServer::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    m_clients.append(worker);
    // we log the event
    emit logMessage(QStringLiteral("New client Connected"));
}
void DiaryServer::jsonReceived(DiaryServerWorker *sender, const QJsonObject &doc)
{
    QJsonValue action = doc.value(QString::fromStdString("Action"));
    QJsonValue login = doc.value(QString::fromStdString("Login"));
    QJsonValue password = doc.value(QString::fromStdString("Password"));
    QJsonObject data = doc.value(QString::fromStdString("Data")).toObject();
    QJsonObject *response = new QJsonObject();
    QJsonDocument *documentResponse = new QJsonDocument();
    if(action.toString() == "Login") {
        int userId = usersController->CorrectLoginAndPassword(login.toString().toStdString(), password.toString().toStdString());
        response->insert("UserId", userId);
        documentResponse->setObject(*response);
    } else
    if (action.toString() == "AddUser") {
        response->insert("UserId", usersController->AddUser(login.toString().toStdString(), password.toString().toStdString()).getId());
        documentResponse->setObject(*response);
    } else
    if (action.toString() == "AddNote") {
        string title = data.value(QString::fromStdString("Title")).toString().toStdString();
        string text = data.value(QString::fromStdString("Text")).toString().toStdString();
        int userId = usersController->CorrectLoginAndPassword(login.toString().toStdString(), password.toString().toStdString());
        response->insert("NoteId", notesController->AddNote(title, text, userId).getId());
        documentResponse->setObject(*response);
    } else
    if(action.toString() == "GetNote") {
        int noteId = data.value(QString::fromStdString("NoteId")).toInt();
        Note note = notesController->GetNote(noteId);
        response->insert("NoteId", note.getId());
        response->insert("Text", QString::fromStdString(note.getText()));
        response->insert("Title", QString::fromStdString(note.getText()));
        documentResponse->setObject(*response);
    } else
    if(action.toString() == "GetAllUserNotes") {
        int userId = usersController->CorrectLoginAndPassword(login.toString().toStdString(), password.toString().toStdString());
        vector<Note> notes = notesController->GetAllNotesByUserId(userId);
        QJsonArray *notesArray = new QJsonArray();

        for (Note note: notes) {
            QJsonObject *noteJson = new QJsonObject();
            noteJson->insert("NoteId", note.getId());
            noteJson->insert("Text", QString::fromStdString(note.getText()));
            noteJson->insert("Title", QString::fromStdString(note.getText()));
            notesArray->append(*noteJson);
        }
        documentResponse->setArray(*notesArray);
    }

    sender->sendJson(documentResponse->object());
    delete response;
    delete documentResponse;
}

void DiaryServer::userDisconnected(DiaryServerWorker *sender)
{

}

void DiaryServer::userError(DiaryServerWorker *sender)
{

}
