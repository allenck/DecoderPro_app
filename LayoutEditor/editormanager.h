#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <QObject>
#include "editor.h"

class Editor;
class EditorManager : public QObject
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit EditorManager(QObject *parent = nullptr);
 ~EditorManager() {}
 EditorManager(const EditorManager&) : QObject() {}
 /*synchronized*/ /*public*/ QList<Editor *> getEditorsList();
 /*public*/ QList<Editor*> getEditorsList(QString type);
 /*public*/ Editor* getEditor(QString name);
 /*public*/ bool addEditor(/*@Nonnull*/ Editor* editor);
 /*public*/ bool removeEditor(/*@Nonnull*/ Editor *editor);

signals:

public slots:
private:
 QSet<Editor*> editors = QSet<Editor*>();
};
Q_DECLARE_METATYPE(EditorManager)
#endif // EDITORMANAGER_H
