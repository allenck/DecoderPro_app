#ifndef CLIPBOARDEDITOR_H
#define CLIPBOARDEDITOR_H

#include "treeeditor.h"
#include <QObject>

class ClipboardEventListener;
class ClipboardEditor : public TreeEditor
{
  Q_OBJECT
 public:
  explicit ClipboardEditor(QWidget *parent = nullptr);
  /*public*/  void windowClosed(QCloseEvent* e);
  /*public*/  void addClipboardEventListener(ClipboardEventListener* listener);

 private:
  /**
   * Maintain a list of listeners -- normally only one.
   */
  /*private*/ /*final*/ QList<ClipboardEventListener*> listenerList =  QList<ClipboardEventListener*>();

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*final*/ QMap<QString, QString> clipboardData = QMap<QString, QString>();
  void fireClipboardEvent();
  friend class TreeEditor;
  friend class TEClipboardListener;
};
class ClipboardEventListener : public EventListener
{
  Q_INTERFACES(EventListener)
 public:
  /*public*/ virtual void clipboardEventOccurred(){};
};
Q_DECLARE_INTERFACE(ClipboardEventListener, "ClipboardEventListener")
#endif // CLIPBOARDEDITOR_H
