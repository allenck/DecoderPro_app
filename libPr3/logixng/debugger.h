#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QObject>
#include "propertychangeprovider.h"
#include "conditionalng.h"
#include "propertychangesupport.h"

class Debugger : public QObject, public PropertyChangeProvider
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeProvider)
 public:
  explicit Debugger(QObject *parent = nullptr){}
  /*public*/  static /*final*/ QString STEP_BEFORE;// = "StepBefore";
  /*public*/  static /*final*/ QString STEP_AFTER;// = "StepAfter";
  /*public*/  void activateDebugger(ConditionalNG* conditionalNG);
  /*public*/  void deActivateDebugger();
  /*public*/  bool isDebuggerActive() ;
  /*public*/  ConditionalNG* getDebugConditionalNG();
  /*public*/  void setBreak(bool value);
  /*public*/  bool getBreak();
  /*public*/  void addPropertyChangeListener(PropertyChangeListener* listener)override;
  /*public*/  void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
  /*public*/  QVector<PropertyChangeListener*> getPropertyChangeListeners()const override;
  /*public*/  QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName)override;
  /*public*/  void removePropertyChangeListener(PropertyChangeListener* listener)override;
  /*public*/  void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener)override;

 signals:

 private:
  /*private*/ ConditionalNG* _debugConditionalNG = nullptr;
  /*private*/ bool _break = false;

  /*private*/ /*final*/ PropertyChangeSupport* _pcs = new PropertyChangeSupport(this);
 protected:
  /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

  friend class AbstractDebuggerMaleSocket;
};

#endif // DEBUGGER_H
