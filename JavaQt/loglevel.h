#ifndef LOGLEVEL_H
#define LOGLEVEL_H
#include "priority.h"

class LogLevel : public Priority
{
public:
 enum VALS
 {
   FATAL = 50000,
   ERROR = 40000,
   WARN = 30000,
   INFO = 20000,
   DEBUG = 10000,
   ALL = -2147483648,
   OFF = 2147483647,
   TRACE = 5000
 };
 LogLevel();
 /*public*/ static /*final*/ int TRACE_INT;// = 5000;
 /*public*/ static LogLevel toLevel(QString sArg);
 /*public*/ static LogLevel toLevel(int val);
 /*public*/ static LogLevel toLevel(int val, LogLevel defaultLevel);
 /*public*/ static LogLevel toLevel(QString sArg, LogLevel defaultLevel);
private:
 static /*final*/ long serialVersionUID;// = 3491141966387921974L;
// /*private*/ void readObject(ObjectInputStream s) throw IOException, ClassNotFoundException;
// /*private*/ void writeObject(ObjectOutputStream s) throw (IOException);
// /*private*/ QObject* readResolve(); // throw (ObjectStreamException);

protected:
 /*protected*/ LogLevel(int level, QString levelStr, int syslogEquivalent);
friend class LoggerBase;
};

#endif // LOGLEVEL_H
