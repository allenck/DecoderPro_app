#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
#include "action.h"
#include "javaqt_global.h"
#include "propertychangelistener.h"
#include "propertychangesupport.h"

//class SwingPropertyChangeSupport;
class PropertyChangeEvent;
class ArrayTable;
class JAVAQTSHARED_EXPORT AbstractAction : public Action, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit AbstractAction(QObject *parent = 0);
 /*public*/  AbstractAction(QObject *parent = 0);
 /*public*/  AbstractAction(const AbstractAction&)  {}
 static bool shouldReconfigure(PropertyChangeEvent* e);
 static void setEnabledFromAction(QWidget* c, Action* a);
 static void setToolTipTextFromAction(QWidget* c, Action* a);
 static bool hasSelectedKey(Action* a) ;
 static bool isSelected(Action* a);
 /*public*/  AbstractAction(QString name, QObject *parent);
 /*public*/  AbstractAction(QString name, QIcon icon, QObject* parent);
 /*public*/  QVariant getValue(QString key) override;
 /*public*/  void putValue(QString key, QVariant newValue) override;
 /*public*/  bool isEnabled() override;
 /*public*/  void setEnabled(bool newValue) override;
 /*public*/  QStringList  getKeys();
 /*public*/  /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* listener) override;
 /*public*/  /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* listener) override;
 Q_INVOKABLE /*public*/ void setClassname(QString);
 /*public*/ QString getClassname();
 QObject* self() override {return (QObject*)this;}


signals:
 void propertyChange(PropertyChangeEvent*) override;

public slots:
 void actionPerformed(JActionEvent* = 0)  override{}

private:
 /*private*/ static bool RECONFIGURE_ON_NULL;
 /**
  * Contains the array of key bindings.
  */
 /*private*/ /*transient*/ QMap<QString, QVariant>* arrayTable;
 /**
  * If any <code>PropertyChangeListeners</code> have been registered, the
  * <code>changeSupport</code> field describes them.
  */
 /*protected*/  PropertyChangeSupport* changeSupport;
 void common();
 QString _class;

protected:
 /**
  * Specifies whether action is enabled; the default is true.
  */
 /*protected*/  bool enabled;// = true;
 /*protected*/  void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
 /*protected*/  QVariant clone() /*throws CloneNotSupportedException*/;


};

#endif // ABSTRACTACTION_H
