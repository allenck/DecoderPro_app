#ifndef PRIORITY_H
#define PRIORITY_H

#include <QObject>
#include <QVector>

class Priority : public QObject
{
 Q_OBJECT
public:
 enum PVAL
 {
  FATAL,
  ERROR,
  WARN,
  INFO,
  DEBUG
 };

 /*public*/ static /*final*/ int OFF_INT;// = 2147483647;
 /*public*/ static /*final*/ int FATAL_INT;// = 50000;
 /*public*/ static /*final*/ int ERROR_INT;// = 40000;
 /*public*/ static /*final*/ int WARN_INT;// = 30000;
 /*public*/ static /*final*/ int INFO_INT;// = 20000;
 /*public*/ static /*final*/ int DEBUG_INT;// = 10000;
 /*public*/ static /*final*/ int ALL_INT;// = -2147483648;
 /*protected*/ Priority(int level, QString levelStr, int syslogEquivalent);
 /*public*/ bool equals(QObject* o);
 /*public*/ /*final*/ int getSyslogEquivalent();
 /*public*/ bool isGreaterOrEqual(Priority* r);
 /*public*/ static QVector<Priority*> getAllPossiblePriorities();
 /*public*/ /*final*/ QString toString();
 /*public*/ /*final*/ int toInt();
 /*public*/ static Priority* toPriority(QString sArg);
 /*public*/ static Priority* toPriority(int val);
 /*public*/ static Priority* toPriority(int val, Priority *defaultPriority);
 /*public*/ static Priority* toPriority(QString sArg, Priority* defaultPriority);

signals:

public slots:
private:
 /*transient*/ int level;
 /*transient*/ QString levelStr;
 /*transient*/ int syslogEquivalent;

protected:
 Priority();

};

#endif // PRIORITY_H
