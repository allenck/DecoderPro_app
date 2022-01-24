#ifndef ABSTRACTIDENTIFY_H
#define ABSTRACTIDENTIFY_H

#include <QObject>
#include "logger.h"
#include "libPr3_global.h"
#include "programmer.h"

class LIBPR3SHARED_EXPORT AbstractIdentify : public QObject, public ProgListener
{
  Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
    AbstractIdentify(Programmer* programmer, QObject *parent = 0);
    /*public*/ void start();
    /*public*/ bool isRunning();
    /*abstract*/ /*public*/ virtual bool test1() = 0;  // no argument to start

    /*abstract*/ /*public*/ virtual bool test2(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test3(int value) = 0 ;

    /*abstract*/ /*public*/ virtual bool test4(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test5(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test6(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test7(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test8(int value) = 0;

    /*abstract*/ /*public*/ virtual bool test9(int value) = 0;
    /*public*/ bool isOptionalCv();
    /*public*/ void setOptionalCv(bool flag);

signals:

public slots:
    /*public*/ virtual void programmingOpReply(int value, int status);

private:
    static Logger* log;
    /** State of the internal sequence */
    int state = 0;
    int retry = 0;
    int lastValue = 0;
    bool optionalCv = false;
    QString cvToRead;
    QString cvToWrite;Programmer* programmer;
    ProgrammingMode* savedMode;
    static /*final*/ int RETRY_COUNT;// = 2;

protected:
    /*protected*/ void identifyDone();
    /*protected*/ void readCV(QString cv);
    /*protected*/ void writeCV(QString cv, int value);
/*abstract*/ /*protected*/ virtual void statusUpdate(QString status) = 0;
    /*abstract*/ /*protected*/ virtual void error() = 0;

};

#endif // ABSTRACTIDENTIFY_H
