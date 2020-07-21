#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include "bean.h"
#include "editor.h"

class Editor;
class EditorManager : public Bean
{
 Q_OBJECT
public:
 /*public*/ static /*final*/ QString EDITORS;// = "editors";
 /*public*/ static /*final*/ QString TITLE;// = "title";
 Q_INVOKABLE explicit EditorManager(QObject *parent = nullptr);
 ~EditorManager() {}
 EditorManager(const EditorManager&) : Bean() {}
 /*public*/ void add(/*@Nonnull*/ Editor* editor);
 /*public*/ bool contains(/*@Nonnull*/ Editor* editor);
 /*public*/ QSet<Editor*> getAll();
 /*public*/ Editor* get(/*@Nonnull*/ QString name);

 /*synchronized*/ /*public*/ QList<Editor *> getEditorsList();
 /*public*/ QList<Editor*> getEditorsList(QString type);
 /*public*/ Editor* getEditor(QString name);
 /*public*/ bool addEditor(/*@Nonnull*/ Editor* editor);
 /*public*/ bool removeEditor(/*@Nonnull*/ Editor *editor);

signals:

public slots:
private:
 QSet<Editor*> set = QSet<Editor*>();
};
Q_DECLARE_METATYPE(EditorManager)
#endif // EDITORMANAGER_H
