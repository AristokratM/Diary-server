#pragma once
#ifndef NOTESCONTROLLER_H
#define NOTESCONTROLLER_H
#include "notedao.h"
#include "mainwindow.h"
#include "INotesController.h"
class NotesController:  public INotesController
{
public:
    NotesController(NoteDAO& noteDAO);
    Note& AddNote(const string& title, const  string& text, const int& userId);
    Note GetNote(const int& id) ;
    vector<Note> GetAllNotes();
    vector<Note> GetAllNotesByUserId(const int& id);
private:
    MainWindow *view;
    NoteDAO *noteDAO;
};

#endif // NOTESCONTROLLER_H
