#include "loggerbase.h"
#include <QDebug>
#include <QString>
#include "consoleinterface.h"
//#include "systemconsole.h"

//QString Logger::name;
LoggerBase::LoggerBase(QString name, QObject *parent) :
    QObject(parent)
{
// bDebugEnabled = false;
// bInfoEnabled = true;
// bTraceEnabled =false;
// this->name = name;
// this->parent = parent;
}

LoggerBase::LoggerBase(const LoggerBase & other) : QObject()
{
// this->bDebugEnabled = other.bDebugEnabled;
// this->bInfoEnabled = other.bInfoEnabled;
// this->name = other.name;
}
/*static*/ void LoggerBase::error(QString s, QVariant ex)
{
 qDebug() << tr("Error: ") << s << ex.toString();
 ConsoleInterface::instance()->sendMessage(tr("Error: ")+ s);
}
/*static*/ void LoggerBase::error(QString s, Throwable ex)
{
 qDebug() << tr("Error: ") << s << ex.getMessage();
 ConsoleInterface::instance()->sendMessage(tr("Error: ")+ s);
}

//bool Logger::isDebugEnabled()
//{ return bDebugEnabled;}

//bool Logger::isInfoEnabled()
//{ return bInfoEnabled;}

//bool Logger::isTraceEnabled()
//{ return bTraceEnabled;}


void LoggerBase::debug(QString name,QString s)
{
 qDebug() << tr("%1: Debug: %2").arg(name).arg(s);
}

void LoggerBase::warn(QString name,QString s)
{
 qDebug() << tr("%1: Warning: %2").arg(name).arg(s);
 ConsoleInterface::instance()->sendMessage(tr("Warning: ")+ s);
}

void LoggerBase::info(QString name,QString s)
{
 qDebug() << tr("%1: Info: %2").arg(name).arg(s);
 ConsoleInterface::instance()->sendMessage(tr("Info: ")+ s);
}

void LoggerBase::trace(QString name,QString s)
{
 qDebug() << tr("%1: trace: %2").arg(name).arg(s);
 ConsoleInterface::instance()->sendMessage(tr("Info: ")+ s);
}

//void Logger::setDebugEnabled(bool bState) { bDebugEnabled = bState;}
//void Logger::setInfoEnabled(bool bState) { bInfoEnabled = bState;}
