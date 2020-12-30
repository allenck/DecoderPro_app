#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H
#include "action.h"
#include "javaqt_global.h"

class PropertyChangeListener;
class SwingPropertyChangeSupport;
class PropertyChangeEvent;
class ArrayTable;
class JAVAQTSHARED_EXPORT AbstractAction : public Action
{
 Q_OBJECT
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
 /*public*/  QVariant getValue(QString key);
 /*public*/  void putValue(QString key, QVariant newValue);
 /*public*/  bool isEnabled();
 /*public*/  void setEnabled(bool newValue);
 /*public*/  QStringList  getKeys();
 /*public*/  /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/  /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 Q_INVOKABLE /*public*/ void setClassname(QString);
 /*public*/ QString getClassname();

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
 virtual void actionPerformed(JActionEvent* = 0) {}

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
// /*protected*/  SwingPropertyChangeSupport* changeSupport;
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
