#include "errormemo.h"

//ErrorMemo::ErrorMemo(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Memo class to remember errors encountered during
 * loading
 *
 * @author Bob Jacobsen  Copyright (c) 2010
 * @version $Revision: 19798 $
 */

//public class ErrorMemo {
/*public*/ ErrorMemo::ErrorMemo(XmlAdapter* adapter,
        QString operation,
        QString description,
        QString systemName,
        QString userName,
        Exception exception, QObject *parent)  : QObject(parent)
{
    this->level = level;
    this->adapter = adapter;
    this->operation = operation;
    this->description = description;
    this->systemName = systemName;
    this->userName = userName;
    this->exception = exception;
    title = "loading";
}

/*public*/ ErrorMemo::ErrorMemo(XmlAdapter* adapter,
        QString operation,
        QString description,
        QString systemName,
        QString userName,
        Exception exception,
        QString title, QObject *parent)  : QObject(parent)
{
    //this(level, adapter, operation, description, systemName, userName, exception);
    this->level = level;
    this->adapter = adapter;
    this->operation = operation;
    this->description = description;
    this->systemName = systemName;
    this->userName = userName;
    this->exception = exception;
    this->title=title;
}


