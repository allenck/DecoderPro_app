#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include "bean.h"
#include "editor.h"
#include "instancemanagerautodefault.h"
#include "class.h"
#include "abstractshutdowntask.h"

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
 /*public*/ void setChanged(bool flag);
 /*public*/ void add(/*@Nonnull*/ Editor* editor);
 QT_DEPRECATED/*public*/ bool contains(/*@Nonnull*/ Editor* editor);
 /*public*/ bool contains(QString name);
 /*public*/ bool containsE(/*@Nonnull*/ Editor* editor);
 /*public*/ QSet<Editor*> getAll();
 /*public*/ /*<T extends Editor>*/ QSet<Editor*> getAll(/*@Nonnull Class<T>*/QString type);
 /*public*/ Editor* get(/*@Nonnull*/ QString name);
 /*public*/ /*<T extends Editor>*/ QObject* get(/*@Nonnull*/ QString type, /*@Nonnull*/ QString name);
 /*public*/ Editor* getByName(/*@Nonnull*/ QString name);
 /*synchronized*/ /*public*/ QList<Editor *> getEditorsList();
 /*public*/ QList<Editor*> getEditorsList(QString type);
 /*public*/ Editor* getEditor(QString name);
 /*public*/ bool addEditor(/*@Nonnull*/ Editor* editor);
 QT_DEPRECATED /*public*/ bool removeEditor(/*@Nonnull*/ Editor *editor);

 /*public*/ void remove(/*@Nonnull*/ Editor* editor);
 QObject* pself() { return(QObject*)this;}

 /*public*/ /*transient*/ AbstractShutDownTask* shutDownTask = nullptr;
 /*public*/ void setShutDownTask();

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 QSet<Editor*> set = QSet<Editor*>();
 bool panelSetChanged = false;
 void notifyStoreNeeded();

 friend class EMShutdownTask;
};
Q_DECLARE_METATYPE(EditorManager)

class EMShutdownTask : public AbstractShutDownTask
{
  Q_OBJECT
  EditorManager* em;
 public:
  EMShutdownTask(QString name, EditorManager* em) : AbstractShutDownTask(name){this->em =em;}
  //@Override
  /*public*/ bool call() /*throw (Exception)*/ override {
      if (em->panelSetChanged) {
          em->notifyStoreNeeded();
      }
      return true;
  }

  //@Override
  /*public*/ void run() override {
  }
};
#endif // EDITORMANAGER_H
