#ifndef JUNITAPPENDER_H
#define JUNITAPPENDER_H
#include <QObject>
#include <QList>
#include "loglevel.h"

class LoggingEvent;
class JUnitAppender : public QObject
{
    Q_OBJECT
public:
    explicit JUnitAppender(QObject *parent = nullptr);

    /*public*/ static void assertErrorMessage(QString msg);
    /*public*/ static void start();
    /*public*/ static void end();
    /*public*/ /*synchronized*/ void append(LoggingEvent* event);
    /*public*/ static int clearBacklog(LogLevel::VALS level);
    /*public*/ static int clearBacklog();

signals:

public slots:
    void message(QString, LoggingEvent*evt);
private:
    static QList<LoggingEvent*> list;// = new java.util.ArrayList<>();
    bool hold;

protected:
    /*protected*/ static bool compare(LoggingEvent* e1, QString s2);

};

#endif // JUNITAPPENDER_H
