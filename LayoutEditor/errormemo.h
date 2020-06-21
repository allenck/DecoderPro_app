#ifndef ERRORMEMO_H
#define ERRORMEMO_H

#include <QObject>
#include "xmladapter.h"
#include "level.h"

class XmlAdapter;
class ErrorMemo : public QObject
{
    Q_OBJECT
public:
    //explicit ErrorMemo(QObject *parent = 0);
    /*public*/ ErrorMemo(XmlAdapter* adapter,
            QString operation,
            QString description,
            QString systemName,
            QString userName,
            Throwable *exception, QObject *parent = 0) ;
    /*public*/ ErrorMemo(XmlAdapter* adapter,
            QString operation,
            QString description,
            QString systemName,
            QString userName,
            Throwable* exception,
            QString title, QObject *parent = 0);
    Level* level;
    /*public*/ XmlAdapter* adapter;
    /*public*/ QString operation;
    /*public*/ QString description;
    /*public*/ QString systemName;
    /*public*/ QString userName;
    /*public*/ Throwable* exception;
    /*public*/ QString title;// = "loading";

signals:

public slots:

};

#endif // ERRORMEMO_H
