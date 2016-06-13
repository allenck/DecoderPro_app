#ifndef THROTTLESETTING_H
#define THROTTLESETTING_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ThrottleSetting : public QObject
{
    Q_OBJECT
public:
    explicit ThrottleSetting(QObject *parent = 0);
    /*public*/ ThrottleSetting(long time, QString command, QString value, QString blockName, QObject *parent = 0);
    /*public*/ ThrottleSetting(ThrottleSetting* ts,QObject *parent = 0);
    /*public*/ void setTime(long time);
    /*public*/ long getTime();
    /*public*/ void setCommand(QString command);
    /*public*/ QString getCommand();
    /*public*/ void setValue(QString value);
    /*public*/ QString getValue();
    /*public*/ void setBlockName(QString blockName);
    /*public*/ QString getBlockName();
    /*public*/ QString toString();

signals:

public slots:
private:
    long    _time;
    QString  _command;
    QString  _value;
    QString  _blockName;

};

#endif // THROTTLESETTING_H
