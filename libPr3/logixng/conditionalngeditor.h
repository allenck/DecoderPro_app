#ifndef CONDITIONALNGEDITOR_H
#define CONDITIONALNGEDITOR_H

#include "treeeditor.h"
#include "eventlistener.h"
#include <QObject>
#include "femalesocketlistener.h"

class ConditionalNGEventListener;
class ConditionalNGEditor : public TreeEditor
{
  Q_OBJECT
 public:
  /*public*/  class ConditionalNGEventListener :   public EventListener
  {
       //Q_OBJECT
       //Q_INTERFACES(EventListener)
   public:
    /*public*/ virtual void conditionalNGEventOccurred() {}
  };
  ConditionalNGEditor(QWidget* parent=nullptr);
  /*/*public*/  ConditionalNGEditor(/*@Nonnull*/ ConditionalNG* conditionalNG, QWidget* parent=nullptr);
  /*public*/  void closeEvent(QCloseEvent* e);
  /*public*/  void addLogixNGEventListener(ConditionalNGEventListener* listener);

 private:
  /**
   * Maintain a list of listeners -- normally only one.
   */
  /*private*/ /*final*/ QList<ConditionalNGEventListener*> listenerList = QList<ConditionalNGEventListener*>();

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*final*/ QMap<QString, QString> logixNGData = QMap<QString, QString>();
  void fireLogixNGEvent();

 protected:
  /*protected*/ /*final*/ ConditionalNG* _conditionalNG;
  friend class ConditionalNGEventListener;
  friend class LogixNGEventListenerImpl;
};

class CNGEFemaleSocketListener : public QObject, public FemaleSocketListener
{
 public:
  //@Override
  /*public*/  void connected(FemaleSocket* socket)override {
      throw new UnsupportedOperationException("Not supported");
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket)override {
      throw new UnsupportedOperationException("Not supported");
  }
  QObject* self() override{return (QObject*)this;}
};

#endif // CONDITIONALNGEDITOR_H
