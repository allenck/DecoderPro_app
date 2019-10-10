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
    /*public*/ static int clearBacklog(LogLevel *level);
    /*public*/ static int clearBacklog();
    /*public*/ static bool verifyNoBacklog();
    /*public*/ static JUnitAppender* instance();
    /*public*/ void activateOptions();
    /*public*/ static void suppressMessage(LogLevel* level, QString msg, QString file, int line);
    /*public*/ static void suppressMessageStartsWith(LogLevel* level, QString msg, QString file, int line);
    /*public*/ static void suppressErrorMessage(QString msg, QString file, int line);
    /*public*/ static void suppressErrorMessageStartsWith(QString msg, QString file, int line);
    /*public*/ static void suppressWarnMessage(QString msg, QString file, int line);
    /*public*/ static void resetUnexpectedMessageFlags(LogLevel* severity);
    /*public*/ static bool unexpectedMessageSeen(LogLevel* l);
    /*public*/ static QString unexpectedMessageContent(LogLevel* l);

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
    /*protected*/ static bool compareStartsWith(LoggingEvent* e1, QString s2);

};

#endif // JUNITAPPENDER_H
