#ifndef JMRITWOSTATEPROPERTYLISTENER_H
#define JMRITWOSTATEPROPERTYLISTENER_H
#include "jmrisimplepropertylistener.h"
#include "logger.h"

class JmriTwoStatePropertyListener :  public JmriSimplePropertyListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit JmriTwoStatePropertyListener(QObject *parent = 0);
    JmriTwoStatePropertyListener(QString propName, int type, QString name, int varType, Conditional* client, QObject *parent = 0);
    JmriTwoStatePropertyListener(QString propName, int type, NamedBeanHandle<NamedBean*>* namedBean, int varType, Conditional* client,QObject *parent = 0);
    QObject* pself() override{return (QObject*)this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
    Logger* log;
};

#endif // JMRITWOSTATEPROPERTYLISTENER_H
