#include "logger.h"
#include <QDebug>
#include <QString>
#include "consoleinterface.h"
//#include "systemconsole.h"
#include "loggerbase.h"

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
/*static*/ void Logger::error(QString s, QVariant ex)
{
 LoggerBase::error(s, ex);
}
bool Logger::isDebugEnabled()
{ return bDebugEnabled;}

bool Logger::isInfoEnabled()
{ return bInfoEnabled;}

bool Logger::isTraceEnabled()
{ return bTraceEnabled;}


void Logger::debug(QString s)
{
 LoggerBase::debug(name, s);
}

void Logger::warn(QString s)
{
 LoggerBase::warn(name, s);
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
