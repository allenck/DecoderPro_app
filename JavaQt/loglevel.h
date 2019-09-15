#ifndef LOGLEVEL_H
#define LOGLEVEL_H
#include "priority.h"

class LogLevel : public Priority
{
public:
 enum VALS
 {
   OFF,
   FATAL,
   ERROR,
   WARN,
   INFO,
   DEBUG,
   TRACE,
   ALL

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

};

#endif // LOGLEVEL_H
