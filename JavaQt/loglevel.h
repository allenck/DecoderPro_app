#ifndef LOGLEVEL_H
#define LOGLEVEL_H
//#include "priority.h"
#include <limits.h>
#include <QString>

class StandardLevel
{
public:
 enum val
 {
  /**
   * No events will be logged.
   */
  OFF = 0 ,

  /**
   * A severe error that will prevent the application from continuing.
   */
  FATAL = 100 ,

  /**
   * An error in the application, possibly recoverable.
   */
  ERROR = 200 ,

  /**
   * An event that might possible lead to an error.
   */
  WARN = 300 ,

  /**
   * An event for informational purposes.
   */
  INFO = 400 ,

  /**
   * A general debugging event.
   */
  DEBUG = 500 ,

  /**
   * A fine-grained debug message, typically capturing the flow through the application.
   */
  TRACE = 600 ,

  /**
   * All events should be logged.
   */
  ALL = INT_MAX
 };
};
class LogLevel //: public Priority
{
public:
// enum VALS
// {
//   FATAL = 50000,
//   ERROR = 40000,
//   WARN = 30000,
//   INFO = 20000,
//   DEBUG = 10000,
//   ALL = -2147483648,
//   OFF = 2147483647,
//   TRACE = 5000
// };
 LogLevel(QString sArg, int intLevel);
 /*public*/ static LogLevel* OFF;// = new LogLevel("OFF", StandardLevel::OFF);
 /*public*/ static LogLevel* FATAL;// = new LogLevel("FATAL", StandardLevel::FATAL);
 /*public*/ static LogLevel* ERROR;// = new LogLevel("ERROR",  StandardLevel::ERROR);
 /*public*/ static LogLevel* WARN;// = new LogLevel("WARN",  StandardLevel::WARN);
 /*public*/ static LogLevel* INFO;// = new LogLevel("INFO",  StandardLevel::INFO);
 /*public*/ static LogLevel* DEBUG;// = new LogLevel("DEBUG",  StandardLevel::DEBUG);
 /*public*/ static LogLevel* TRACE;// = new LogLevel("TRACE",  StandardLevel::TRACE);
 /*public*/ static LogLevel* ALL;// = new LogLevel("ALL",  StandardLevel::ALL);
 /*public*/ static /*final*/ int TRACE_INT;// = 5000;
 /*public*/ static LogLevel toLevel(QString sArg);
 /*public*/ static LogLevel toLevel(int val);
 /*public*/ static LogLevel toLevel(int val, LogLevel defaultLevel);
 /*public*/ static LogLevel toLevel(QString sArg, LogLevel defaultLevel);
 /*public*/ int toInt();
 /*public*/ QString toString();
 /*public*/ bool equals(LogLevel* other);

private:
 static /*final*/ long serialVersionUID;// = 3491141966387921974L;
// /*private*/ void readObject(ObjectInputStream s) throw new IOException, ClassNotFoundException;
// /*private*/ void writeObject(ObjectOutputStream s) /*throw (IOException)*/;
// /*private*/ QObject* readResolve(); // throw (ObjectStreamException);
 QString sArg;
 int intLevel;
protected:
 /*protected*/ LogLevel(int level, QString levelStr, int syslogEquivalent);
friend class LoggerBase;
};

#endif // LOGLEVEL_H
