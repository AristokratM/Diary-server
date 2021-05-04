#include "notedao.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>

NoteDAO::NoteDAO()
{

}
NoteDAO::~NoteDAO() {

}

Note& NoteDAO::AddNote(const string& title, const  string& text, const int& userId) {
    Note* note = new Note();
    note->setText(text);
    note->setTitle(title);
    note->setUserId(userId);
    QSqlQuery query;
    query.prepare("INSERT INTO Notes(userId, title, text, createdDate) "
            "VALUES(:userId, :title, :text, :createdDate);");

    query.bindValue(":userId", note->getUserId());
    query.bindValue(":title", QString::fromStdString(note->getTitle()));
    query.bindValue(":text", QString::fromStdString(note->getText()));
    query.bindValue(":createdDate", QVariant::fromValue(note->getCreatedDate()));

    if (!query.exec())
    {
        qDebug() << "Кажется данные не вставляются, " + query.lastError().text();
    }
    return *note;
}

vector<Note> NoteDAO::GetAllNotes() {
    vector<Note> notes;
    QString str = "SELECT * FROM Notes;";
    QSqlQuery query;
    if (query.exec(str))
    {
        QSqlRecord record = query.record();
        int id = 0, userId = 0;
        QString title = "", text = "";

        while (query.next())
        {
            id = query.value(record.indexOf("id")).toInt();
            userId = query.value(record.indexOf("userId")).toInt();
            title = query.value(record.indexOf("title")).toString();
            text = query.value(record.indexOf("text")).toString();

            Note *note = new Note();
            note->setId(id);
            note->setUserId(userId);
            note->setTitle(title.toStdString());
            note->setText(text.toStdString());
            notes.push_back(*note);

        }
    }
    return notes;
}

vector<Note> NoteDAO::GetAllNotesByUserId(const int &id)
{
    vector<Note> userNotes;
    QSqlQuery query;
    query.prepare("SELECT * FROM Notes WHERE userId=:id;");
    query.bindValue(":id", id);
    if (query.exec())
    {
        QSqlRecord record = query.record();
        int id = 0, userId = 0;
        QString title = "", text = "";

        while (query.next())
        {
            id = query.value(record.indexOf("id")).toInt();
            userId = query.value(record.indexOf("userId")).toInt();
            title = query.value(record.indexOf("title")).toString();
            text = query.value(record.indexOf("text")).toString();

            Note *note = new Note();
            note->setId(id);
            note->setUserId(userId);
            note->setTitle(title.toStdString());
            note->setText(text.toStdString());
            userNotes.push_back(*note);
        }
    }
    return userNotes;
}

Note NoteDAO::GetNote(const int& id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Notes WHERE id=:id)");
    query.bindValue(":id", id);
    if (query.exec())
    {
        QSqlRecord record = query.record();
        int id = 0, userId = 0;
        QString title = "", text = "";

            id = query.value(record.indexOf("id")).toInt();
            userId = query.value(record.indexOf("userId")).toInt();
            title = query.value(record.indexOf("title")).toString();
            text = query.value(record.indexOf("text")).toString();

            Note *note = new Note();
            note->setId(id);
            note->setUserId(userId);
            note->setTitle(title.toStdString());
            note->setText(text.toStdString());
            return *note;
     }
    throw logic_error("No note found!");
}


