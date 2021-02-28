#ifndef JMRISIMPLEPROPERTYLISTENER_H
#define JMRISIMPLEPROPERTYLISTENER_H
#include "propertychangelistener.h"
#include "namedbeanhandle.h"

//class NamedBeanHandle;
class Conditional;
class Logger;
class JmriSimplePropertyListener : public QObject, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit JmriSimplePropertyListener(QObject *parent = 0);
    JmriSimplePropertyListener(QString propName, int type, QString varName, int varType, Conditional* client, QObject *parent = 0);
    //template <class T>
    JmriSimplePropertyListener(QString propName, int type, NamedBeanHandle<NamedBean*>* namedBean, int varType, Conditional* client, QObject *parent = 0);
     NamedBeanHandle<NamedBean*>* getNamedBean();
     /*public*/ NamedBean* getBean();
    /*public*/ int getType();
    /*public*/ QString getPropertyName();
    /*public*/ int getVarType();
    /*public*/ QString getDevName();
    /*public*/ void addConditional(Conditional* client);
    /*public*/ void setEnabled(bool state);
    /*public*/ void calculateClient(int idx, PropertyChangeEvent* evt);
     QObject* self() override{return (QObject*)this;}
signals:

public slots:
     /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
    static Logger* log;
    int _type;
    QString _varName;
    int _varType;
    QString _propertyName;
    QList <Conditional*>* _clients;
    bool _enabled;
    NamedBeanHandle<NamedBean*>* _namedBean;
    friend class JmriTwoStatePropertyListener;
    friend class JmriMultiStatePropertyListener;
};

#endif // JMRISIMPLEPROPERTYLISTENER_H
