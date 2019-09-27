#ifndef THROTTLESETTING_H
#define THROTTLESETTING_H

#include <QObject>
#include "libPr3_global.h"
#include "namedbeanhandle.h"

class Logger;
class LIBPR3SHARED_EXPORT ThrottleSetting : public QObject
{
    Q_OBJECT
public:
    explicit ThrottleSetting(QObject *parent = 0);
    /*public*/ ThrottleSetting(long time, QString command, QString value, QString beanName, QObject *parent = 0);
    /*public*/ ThrottleSetting(long time, QString command, QString value, QString beanName, float sp, QObject *parent= nullptr);
    /*public*/ ThrottleSetting(ThrottleSetting* ts,QObject *parent = 0);
    /*public*/ void setTime(long time);
    /*public*/ long getTime();
    /*public*/ void setCommand(QString command);
    /*public*/ QString getCommand();
    /*public*/ void setValue(QString value);
    /*public*/ QString getValue();
    /*public*/ void setSpeed(float s);
    /*public*/ float getSpeed();
     /*public*/ void setNamedBean(QString cmd, QString name);
     // _namedHandle may be of 3 different types
     /*public*/  void setNamedBeanHandle(NamedBeanHandle<NamedBean *> *bh);
     // _namedHandle may be of 3 different types
     /*public*/ NamedBeanHandle<NamedBean *> *getNamedBeanHandle();
     /*public*/ QString getBeanDisplayName();
     /*public*/ QString getBeanSystemName();
    Q_INVOKABLE virtual /*public*/ QString toString();

signals:

public slots:
private:
    long    _time;
    QString  _command;
    QString  _value;
    float  _speed;
    /*private*/ NamedBeanHandle<NamedBean*>* _namedHandle = nullptr;
 static Logger* log;
};

#endif // THROTTLESETTING_H
