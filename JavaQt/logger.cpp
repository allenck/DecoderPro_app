#include "logger.h"
#include <QDebug>
#include <QString>
#include "consoleinterface.h"
//#include "systemconsole.h"
#include "loggerbase.h"
#include "loggingevent.h"

//QString Logger::name;
Logger::Logger(QString name, QObject *parent) :
    QObject(parent)
{
 bDebugEnabled = false;
 bInfoEnabled = true;
 bTraceEnabled =false;
 this->name = name;
 this->parent = parent;
}
Logger::Logger(const Logger & other) : QObject()
{
 this->bDebugEnabled = other.bDebugEnabled;
 this->bInfoEnabled = other.bInfoEnabled;
 this->name = other.name;
}
///*static*/ void Logger::error(QString s, QVariant ex)
//{
// LoggerBase::error(s, ex);
//}
/*static*/ void Logger::error(QString s, Throwable* ex)
{
 LoggerBase::error(s, ex);
}

bool Logger::isDebugEnabled() const
{ return bDebugEnabled;}

bool Logger::isInfoEnabled()
{ return bInfoEnabled;}

bool Logger::isTraceEnabled()
{ return bTraceEnabled;}

void Logger::debug(QString s) const
{
 LoggerBase::debug(name, s);
}
void Logger::debug(QString s, Throwable throwable)
{
 LoggerBase::debug(name, s, throwable);
}

void Logger::warn(QString s) const
{
 LoggerBase::warn(name, s);
}

void Logger::warn(QString s, Throwable ex)
{
 LoggerBase::warn(name, s, ex);
}


void Logger::info(QString s)
{
 LoggerBase::info(name, s);
}

void Logger::trace(QString s)
{
 LoggerBase::trace(name, s);
}

void Logger::setDebugEnabled(bool bState) { bDebugEnabled = bState;}
void Logger::setInfoEnabled(bool bState) { bInfoEnabled = bState;}
void Logger::setTraceEnabled(bool bState) { bTraceEnabled = bState;}

