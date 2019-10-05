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

    /*public*/ static void assertErrorMessage(QString msg, QString file=__FILE__, int line=__LINE__);
    /*public*/ static void assertWarnMessage(QString msg, QString file=__FILE__, int line=__LINE__);
    /*public*/ static void assertMessage(QString msg, QString file=__FILE__, int line=__LINE__);
    /*public*/ static LoggingEvent* checkForMessage(QString msg);
    /*public*/ static void start();
    /*public*/ static void end();
    /*public*/ /*synchronized*/ void append(LoggingEvent* event);
    /*public*/ static int clearBacklog(LogLevel::VALS level);
    /*public*/ static int clearBacklog();
    /*public*/ static bool verifyNoBacklog();
    /*public*/ static JUnitAppender* instance();
    /*public*/ void activateOptions();

signals:

public slots:
    void message(QString, LoggingEvent*evt);
private:
    static QList<LoggingEvent*> list;// = new java.util.ArrayList<>();
    static bool hold;
    static /*private*/ JUnitAppender* _instance;// = null;
    // package-level access for testing
    static bool unexpectedFatalSeen;// = false;
    static QString  unexpectedFatalContent;// = null;
    static bool unexpectedErrorSeen;// = false;
    static QString  unexpectedErrorContent;// = null;
    static bool unexpectedWarnSeen;// = false;
    static QString  unexpectedWarnContent;// = null;
    static bool unexpectedInfoSeen;// = false;
    static QString  unexpectedInfoContent;// = null;
    void superappend(LoggingEvent* l);

protected:
    /*protected*/ static bool compare(LoggingEvent* e1, QString s2);

};

#endif // JUNITAPPENDER_H
