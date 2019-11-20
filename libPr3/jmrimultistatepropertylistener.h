#ifndef JMRIMULTISTATEPROPERTYLISTENER_H
#define JMRIMULTISTATEPROPERTYLISTENER_H
#include "jmrisimplepropertylistener.h"
#include "logger.h"

class JmriMultiStatePropertyListener : public JmriSimplePropertyListener
{
    Q_OBJECT
public:
    //explicit JmriMultiStatePropertyListener(QObject *parent = 0);
    JmriMultiStatePropertyListener(QString propName, int type, QString name, int varType,
                              Conditional* client, int state, QObject *parent = 0);
    /*public*/ void setState(int state);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
private:
    QList<int>* _states;
    Logger* log;

};

#endif // JMRIMULTISTATEPROPERTYLISTENER_H
