#ifndef JMRITWOSTATEPROPERTYLISTENER_H
#define JMRITWOSTATEPROPERTYLISTENER_H
#include "jmrisimplepropertylistener.h"
#include "logger.h"

class JmriTwoStatePropertyListener : public JmriSimplePropertyListener
{
    Q_OBJECT
public:
    //explicit JmriTwoStatePropertyListener(QObject *parent = 0);
    JmriTwoStatePropertyListener(QString propName, int type, QString name, int varType, Conditional* client, QObject *parent = 0);
    JmriTwoStatePropertyListener(QString propName, int type, NamedBeanHandle<NamedBean*>* namedBean, int varType, Conditional* client,QObject *parent = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

signals:

public slots:
private:
    Logger* log;
};

#endif // JMRITWOSTATEPROPERTYLISTENER_H
