#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include "bean.h"
#include "editor.h"
#include "instancemanagerautodefault.h"
#include "class.h"

class Editor;
class EditorManager : public Bean, public PropertyChangeListener, public InstanceManagerAutoDefault
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener InstanceManagerAutoDefault)
public:
 /*public*/ static /*final*/ QString EDITORS;// = "editors";
 /*public*/ static /*final*/ QString TITLE;// = "title";
 Q_INVOKABLE explicit EditorManager(QObject *parent = nullptr);
 ~EditorManager() {}
 EditorManager(const EditorManager&) : Bean() {}
 /*public*/ void add(/*@Nonnull*/ Editor* editor);
 QT_DEPRECATED/*public*/ bool contains(/*@Nonnull*/ Editor* editor);
 /*public*/ bool contains(QString name);
 /*public*/ QSet<Editor*> getAll();
 /*public*/ Editor* get(/*@Nonnull*/ QString name);
 /*public*/ /*<T extends Editor>*/ QObject* get(/*@Nonnull*/ QString type, /*@Nonnull*/ QString name);

 /*synchronized*/ /*public*/ QList<Editor *> getEditorsList();
 /*public*/ QList<Editor*> getEditorsList(QString type);
 /*public*/ Editor* getEditor(QString name);
 /*public*/ bool addEditor(/*@Nonnull*/ Editor* editor);
 QT_DEPRECATED /*public*/ bool removeEditor(/*@Nonnull*/ Editor *editor);
 /*public*/ void remove(/*@Nonnull*/ Editor* editor);
 QObject* self() { return(QObject*)this;}
signals:

public slots:
private:
 QSet<Editor*> set = QSet<Editor*>();
};
Q_DECLARE_METATYPE(EditorManager)
#endif // EDITORMANAGER_H
