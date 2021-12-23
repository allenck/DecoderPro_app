#include "junitappender.h"
#include "assert1.h"
#include "loglevel.h"
#include "loggingevent.h"
#include "stringutils.h"
#include "consoleinterface.h"
#include <QDebug>

JUnitAppender::JUnitAppender(QObject *parent) : QObject(parent)
{
 list.clear();
 connect(ConsoleInterface::instance(), SIGNAL(message(QString,LoggingEvent*)), this, SLOT(message(QString,LoggingEvent*)));
}

void JUnitAppender::message(QString, LoggingEvent * evt)
{
  append(evt);
}
/**
 * Log4J Appender that works with JUnit tests to check for expected vs
 * unexpected log messages
 *
 * Much of the interface is static to avoid lots of instance() calls, but this
 * is not a problem as there should be only one of these while tests are running
 *
 * @see jmri.util.JUnitUtil
 *
 * @author Bob Jacobsen - Copyright 2007
 */
// /*public*/ class JUnitAppender extends org.apache.log4j.ConsoleAppender {

/*static*/ QList<LoggingEvent*> JUnitAppender::list = QList<LoggingEvent*>();

/**
 * Called for each logging event.
 *
 * @param event the event to log
 */
//@Override
/*public*/ /*synchronized*/ void JUnitAppender::append(LoggingEvent* event) {
//    if (hold) {
        list.append(event);
//    } else {
//        super.append(event);
//    }
}

/**
 * Called once options are set.
 *
 * Currently just reflects back to super-class.
 */
//@Override
/*public*/ void JUnitAppender::activateOptions() {
    if (JUnitAppender::_instance != nullptr) {
        //System.err.println("JUnitAppender initialized more than once"); // can't count on logging here
        qDebug() << "JUnitAppender initialized more than once";
    } else {
        JUnitAppender::_instance = this;
    }

    //super.activateOptions();
}
#if 0
/**
 * Do clean-up at end.
 *
 * Currently just reflects back to super-class.
 */
@Override
/*public*/ synchronized void close() {
    list.clear();
    super.close();
}

static bool hold = false;

static private JUnitAppender instance = null;
#endif

/*public*/ /*static*/ bool JUnitAppender::unexpectedMessageSeen(LogLevel* l) {
    if (l == LogLevel::FATAL) {
        return unexpectedFatalSeen;
    }
    if (l == LogLevel::ERROR) {
        return unexpectedFatalSeen || unexpectedErrorSeen;
    }
    if (l == LogLevel::WARN) {
        return unexpectedFatalSeen || unexpectedErrorSeen || unexpectedWarnSeen;
    }
    if (l == LogLevel::INFO) {
        return unexpectedFatalSeen || unexpectedErrorSeen || unexpectedWarnSeen || unexpectedInfoSeen;
    }
    throw new IllegalArgumentException("Did not expect " + l->toString());
}

/*public*/ /*static*/ QString JUnitAppender::unexpectedMessageContent(LogLevel* l) {
    if (l == LogLevel::FATAL) {
        return unexpectedFatalContent;
    }
    if (l == LogLevel::ERROR) {
        if (unexpectedFatalContent != nullptr ) return unexpectedFatalContent;
        return unexpectedErrorContent;
    }
    if (l == LogLevel::WARN) {
        if (unexpectedFatalContent != nullptr ) return unexpectedFatalContent;
        if (unexpectedErrorContent != nullptr ) return unexpectedErrorContent;
        return unexpectedWarnContent;
    }
    if (l == LogLevel::INFO) {
        if (unexpectedFatalContent != nullptr ) return unexpectedFatalContent;
        if (unexpectedErrorContent != nullptr ) return unexpectedErrorContent;
        if (unexpectedWarnContent != nullptr ) return unexpectedWarnContent;
        return unexpectedInfoContent;
    }
    throw new IllegalArgumentException("Did not expect " + l->toString());
}

/*public*/ /*static*/ void JUnitAppender::resetUnexpectedMessageFlags(LogLevel* severity) {
    // cases statements are organized to flow
    switch (severity->toInt()) {
        case StandardLevel::INFO:
            unexpectedInfoSeen = false;
            unexpectedInfoContent = nullptr;
            //$FALL-THROUGH$
        case StandardLevel::WARN:
            unexpectedWarnSeen = false;
            unexpectedWarnContent = nullptr;
            //$FALL-THROUGH$
        case StandardLevel::ERROR:
            unexpectedErrorSeen = false;
            unexpectedErrorContent = nullptr;
            //$FALL-THROUGH$
        case StandardLevel::FATAL:
            unexpectedFatalSeen = false;
            unexpectedFatalContent = nullptr;
            break;
        default:
            //Log.warn("Unhandled serverity code: {}", severity.toInt());
     qDebug() << tr("Unhandled serverity code: %1").arg(severity->toInt());
            break;
    }
}

/**
 * Tell appender that a JUnit test is starting.
 * <p>
 * This causes log messages to be held for examination.
 */
/*public*/ /*static*/ void JUnitAppender::start() {
   hold = true;
   if(_instance == nullptr)
   {
     _instance = new JUnitAppender();
   }
}

/**
 * Tell appender that the JUnit test is ended.
 * <p>
 * Any queued messages at this point will be passed through to the actual
 * log.
 */
/*public*/ /*static*/ void JUnitAppender::end() {
    hold = false;
    while (!list.isEmpty()) {
//        LoggingEvent evt = list.remove(0);
        LoggingEvent* evt = list.at(0);
        list.removeAt(0);
//        instance().superappend(evt);
    }
}

/**
 * do common local processing of event, then pass up to super class
 *
 * @param l the event to process
 */
void JUnitAppender::superappend(LoggingEvent* l) {
    if (l->getLevel() == LogLevel::FATAL) {
        unexpectedFatalSeen = true;
        unexpectedFatalContent = l->getMessage();
    }
    if (l->getLevel() == LogLevel::ERROR) {
        if (compare(l, "Uncaught Exception caught by jmri.util.exceptionhandler.UncaughtExceptionHandler")) {
            // still an error, just suppressed
        } else {
            unexpectedErrorSeen = true;
            unexpectedErrorContent = l->getMessage();
        }
    }
    if (l->getLevel() == LogLevel::WARN) {
        unexpectedWarnSeen = true;
        unexpectedWarnContent = l->getMessage();
    }
    if (l->getLevel() == LogLevel::INFO) {
        unexpectedInfoSeen = true;
        unexpectedInfoContent = l->getMessage();
    }

    //super.append(l);
}

/**
 * Remove any messages stored up, returning how many there were. This is
 * used to skip over messages that don't matter, e.g. during setting up a
 * test. Removed messages are not sent for further logging.
 *
 * @param level lowest level counted in return value, e.g. WARN means WARN
 *                  and higher will be counted
 * @return count of skipped messages
 * @see #clearBacklog()
 */
/*public*/ /*static*/ int JUnitAppender::clearBacklog(LogLevel* level) {
    if (list.isEmpty()) {
        return 0;
    }
    int retval = 0;
#if 1
    for (LoggingEvent* event : list) {
        if (event != nullptr && event->getLevel() != 0 && event->getLevel() >= level) {
            retval++; // higher number -> more severe, specific, limited
        } // with Log4J 2, this could have used isMoreSpecificThan(level)
    }
#endif
    list.clear();
    return retval;
}

/**
 * Remove any messages stored up, returning how many of WARN or higher
 * severity there are. This is used to skip over messages that don't matter,
 * e.g. during setting up a test. Removed messages are not sent for further
 * logging.
 *
 * @return count of skipped messages of WARN or more specific level
 * @see #clearBacklog(Level)
 */
/*public*/ /*static*/ int JUnitAppender::clearBacklog() {
//    return clearBacklog(LogLevel::WARN);
    return 0;
}

/**
 * Verify that no messages were emitted, logging any that were. Does not
 * stop the logging. Clears the accumulated list.
 *
 * @return true if no messages logged
 */
/*public*/ /*static*/ bool JUnitAppender::verifyNoBacklog() {
    if (list.isEmpty()) {
        return true;
    }
    bool ret = true;
    while (!list.isEmpty()) { // should probably add a skip of lower levels?
        LoggingEvent* evt = list.at(0);
        if(evt->getLevel() == LogLevel::ERROR || evt->getLevel() == LogLevel::WARN)
         ret = false;
        list.removeAt(0);
        instance()->superappend(evt);
    }
    return ret;
}

/**
 * Check that the next queued message was of Error severity, and has a
 * specific message. White space is ignored.
 * <p>
 * Invokes a JUnit Assert if the message doesn't match.
 *
 * @param msg the message to assert exists
 */
/*public*/ /*static*/ void JUnitAppender::assertErrorMessage(QString msg, QString file, int line) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg,file, line);
        return;
    }

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    // next piece of code appears three times, should be refactored away during Log4J 2 migration
    while ((evt->getLevel() == LogLevel::WARN) || (evt->getLevel() == LogLevel::INFO) || (evt->getLevel() == LogLevel::DEBUG) || (evt->getLevel() == LogLevel::TRACE))
    { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Only debug/info messages present: " + msg,file, line);
            return;
        }
        //evt = list.remove(0);
        evt = list.at(0);
           list.removeAt(0);
    }

    // check the remaining message, if any
    if (evt->getLevel() != LogLevel::ERROR) {
        qDebug() << "value: " << evt->getLevel() << "expected: " << LogLevel::ERROR;
        Assert::fail("Level mismatch when looking for ERROR message: \"" +
                msg +
                "\" found \"" +
                 evt->getMessage() +
                "\"", file, line);
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for ERROR message \"" + msg + "\" got \"" + evt->getMessage() + "\"", file, line);
    }
}
#if 1
/**
 * Check that the next queued message was of Error severity, and has a
 * specific message. White space is ignored.
 * <p>
 * Invokes a JUnit Assert if the message doesn't match.
 *
 * @param msg the message to assert exists
 */
/*public*/ /*static*/ void JUnitAppender::assertErrorMessageStartsWith(QString msg, QString file, int line) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg, file, line);
        return;
    }

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    // next piece of code appears three times, should be refactored away during Log4J 2 migration
    while ((evt->getLevel() == LogLevel::INFO) || (evt->getLevel() == LogLevel::DEBUG) || (evt->getLevel() == LogLevel::TRACE)) { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Only debug/info messages present: " + msg, file, line);
            return;
        }
        evt = list.at(0);
        list.removeAt(0);
    }

    // check the remaining message, if any
    if (evt->getLevel() != LogLevel::ERROR) {
        Assert::fail("Level mismatch when looking for ERROR message: \"" +
                msg +
                "\" found \"" +
                evt->getMessage() +
                "\"", file, line);
    }

    if (!compareStartsWith(evt, msg)) {
        Assert::fail("Looking for ERROR message \"" + msg + "\" got \"" + evt->getMessage() + "\"", file, line);
    }
}
#endif
/**
 * If there's a next matching message of specific severity, just ignore it.
 * Not an error if not present; mismatch is an error. Skips messages of
 * lower severity while looking for the specific one. White space is
 * ignored.
 *
 * @param level the level at which to suppress the message
 * @param msg   the message to suppress
 */
/*public*/ /*static*/ void JUnitAppender::suppressMessage(LogLevel *level, QString msg, QString file, int line) {
    if (list.isEmpty()) {
        return;
    }

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    while (((level->equals(LogLevel::WARN)) &&
            (evt->getLevel() == LogLevel::TRACE ||
                    evt->getLevel() == LogLevel::DEBUG ||
                    evt->getLevel() == LogLevel::INFO ||
                    evt->getLevel() == LogLevel::WARN)) ||
            ((level->equals(LogLevel::ERROR)) &&
                    (evt->getLevel() == LogLevel::TRACE ||
                            evt->getLevel() == LogLevel::DEBUG ||
                            evt->getLevel() == LogLevel::INFO ||
                            evt->getLevel() == LogLevel::WARN ||
                            evt->getLevel() == LogLevel::ERROR))) { // this is much better with Log4J 2's compareTo method
        if (list.isEmpty()) {
            return;
        }
        evt = list.at(0);
        list.removeAt(0);
    }

    // check the remaining message, if any
    if (!evt->getLevel()->equals(level)) {
        Assert::fail("Level mismatch when looking for " +
                level->toString() +
                " message: \"" +
                msg +
                "\" found \"" +
                evt->getMessage() +
                "\"", file,line);
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for " + level->toString() + " message \"" + msg + "\" got \"" + evt->getMessage() + "\"",file,line);
    }
}

/**
 * If there's a next matching message of specific severity, just ignore it.
 * Not an error if not present; mismatch is an error. Skips messages of
 * lower severity while looking for the specific one. White space is
 * ignored.
 *
 * @param level the level at which to suppress the message
 * @param msg   the message to suppress
 */
/*public*/ /*static*/ void JUnitAppender::suppressMessageStartsWith(LogLevel* level, QString msg, QString file, int line) {
    if (list.isEmpty()) {
        return;
    }

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    while (((level->equals(LogLevel::WARN)) &&
            (evt->getLevel() == LogLevel::TRACE ||
                    evt->getLevel() == LogLevel::DEBUG ||
                    evt->getLevel() == LogLevel::INFO ||
                    evt->getLevel() == LogLevel::WARN)) ||
            ((level->equals(LogLevel::ERROR)) &&
                    (evt->getLevel() == LogLevel::TRACE ||
                            evt->getLevel() == LogLevel::DEBUG ||
                            evt->getLevel() == LogLevel::INFO ||
                            evt->getLevel() == LogLevel::WARN ||
                            evt->getLevel() == LogLevel::ERROR))) { // this is much better with Log4J 2's compareTo method
        if (list.isEmpty()) {
            return;
        }
        evt = list.at(0);
        list.removeAt(0);
    }

    // check the remaining message, if any
    if (!evt->getLevel()->equals(level)) {
        Assert::fail("Level mismatch when looking for " +
                level->toString() +
                " message: \"" +
                msg +
                "\" found \"" +
                 evt->getMessage() +
                "\"", file,line);
    }

    if (!compareStartsWith(evt, msg)) {
        Assert::fail("Looking for " + level->toString() + " message \"" + msg + "\" got \"" + evt->getMessage() + "\"", file, line);
    }
}

/**
 * If there's a next matching message of Error severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ /*static*/ void JUnitAppender::suppressErrorMessage(QString msg, QString file, int line) {
    suppressMessage(LogLevel::ERROR, msg, file, line);
}

/**
 * If there's a next matching message of Error severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ /*static*/ void JUnitAppender::suppressErrorMessageStartsWith(QString msg, QString file, int line) {
    suppressMessageStartsWith(LogLevel::ERROR, msg, file, line);
}

/**
 * If there's a next matching message of Warn severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ /*static*/ void JUnitAppender::suppressWarnMessage(QString msg, QString file, int line) {
    suppressMessage(LogLevel::WARN, msg, file, line);
}

/**
 * See if a message (completely matching particular text) has been emitted
 * yet. White space is ignored. All messages before the requested one are
 * dropped; it the requested message hasn't been issued, this means that the
 * message queue is cleared.
 *
 * @param msg the message text to check for
 * @return null if not present, else the LoggingEvent for possible further
 *         checks of level, etc
 */
/*public*/ /*static*/ LoggingEvent* JUnitAppender::checkForMessage(QString msg) {
    if (list.isEmpty())
        return nullptr;

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);
    while (!compare(evt, msg)) {
        if (list.isEmpty()) {
            return nullptr; // normal to not find it
        }
        evt = list.at(0);
        list.removeAt(0);
    }
    // fall through with a match

    return evt;
}
#if 0
/**
 * See if a message that starts with particular text has been emitted yet.
 * White space is ignored. All messages before the matching one are dropped;
 * it a matching message hasn't been issued, this means that the message
 * queue is cleared.
 *
 * @param msg the message text to check for
 * @return null if not present, else the LoggingEvent for possible further
 *         checks of level, etc
 */
/*public*/ static LoggingEvent checkForMessageStartingWith(String msg) {
    if (list.isEmpty())
        return null;

    String tmsg = StringUtils.deleteWhitespace(msg);

    LoggingEvent evt = list.remove(0);
    while (!StringUtils.deleteWhitespace(evt.getMessage().toString()).startsWith(tmsg)) {
        if (list.isEmpty()) {
            return null; // normal to not find it
        }
        evt = list.remove(0);
    }
    // fall through with a match

    return evt;
}
#endif
/**
 * Check that the next queued message was of Warn severity, and has a
 * specific message. White space is ignored.
 * <p>
 * Invokes a JUnit Assert if the message doesn't match.
 *
 * @param msg the message to assert exists
 */
/*public*/ /*static*/ void JUnitAppender::assertWarnMessage(QString msg,QString file, int line)
{
 if (list.isEmpty()) {
        Assert::fail("No message present: " + msg, file, line);
        return;
    }
    LoggingEvent* evt = checkForMessage(msg);

    if (evt == nullptr) {
        Assert::fail("Looking for message \"" + msg + "\" and didn't find it", file, line);
    }
}

/**
 * Assert that a specific message, of any severity, has been logged. White
 * space is ignored.
 * <p>
 * Invokes a JUnit Assert if no matching message is found, but doesn't
 * require it to be the next message. This allows use e.g. for
 * debug-severity messages.
 *
 * @param msg the message to assert exists
 */
/*public*/ /*static*/ void JUnitAppender::assertMessage(QString msg,QString file, int line) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg,file, line);
        return;
    }
    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    while ((evt->getLevel() == LogLevel::INFO) || (evt->getLevel() == LogLevel::DEBUG) || (evt->getLevel() == LogLevel::TRACE)) { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Message not found: " + msg, file, line);
            return;
        }
        evt = list.at(0);
        list.removeAt(0);
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for message \"" + msg + "\" got \"" + evt->getMessage() + "\"", file, line);
    }
}

/**
 * Compare two message strings, handling nulls and ignoring whitespace.
 *
 * @param e1 the event
 * @param s2 the string to compare e1 to
 * @return true if message in e1 equals s2; false otherwise
 */
/*protected*/ /*static*/ bool JUnitAppender::compare(LoggingEvent* e1, QString s2) {
    if (e1 == nullptr) {
//        System.err.println("Logging event null when comparing to " + s2);
        return s2 == "";
    } else if (e1->getMessage() == nullptr) {
//        System.err.println("Logging event has null message when comparing to " + s2);
        return s2 == "";
    }
    QString s1 = e1->getMessage();
    return StringUtils::deleteWhitespace(s1.toUpper()) ==(StringUtils::deleteWhitespace(s2.toUpper()));
}

/**
 * Compare two message strings, handling nulls and ignoring whitespace.
 *
 * @param e1 the event
 * @param s2 the string to compare e1 to
 * @return true if message in e1 starts with s2; false otherwise
 */
/*protected*/ /*static*/ bool JUnitAppender::compareStartsWith(LoggingEvent* e1, QString s2) {
    if (e1 == nullptr) {
        /*System.err.println*/qDebug() << ("Logging event null when comparing to " + s2);
        return s2 == "";
    } else if (e1->getMessage() == "") {
        /*System.err.println*/qDebug() << ("Logging event has null message when comparing to " + s2);
        return s2 == "";
    }
    QString s1 = e1->getMessage();
    return StringUtils::deleteWhitespace(s1).startsWith(StringUtils::deleteWhitespace(s2));
}

/*public*/ /*static*/ JUnitAppender* JUnitAppender::instance() {
    return JUnitAppender::_instance;
}

/*static*/ /*private*/ JUnitAppender* JUnitAppender::_instance = nullptr;
// package-level access for testing
/*static*/ bool JUnitAppender::unexpectedFatalSeen = false;
/*static*/ QString  JUnitAppender::unexpectedFatalContent = nullptr;
/*static*/ bool JUnitAppender::unexpectedErrorSeen = false;
/*static*/ QString  JUnitAppender::unexpectedErrorContent = nullptr;
/*static*/ bool JUnitAppender::unexpectedWarnSeen = false;
/*static*/ QString  JUnitAppender::unexpectedWarnContent = nullptr;
/*static*/ bool JUnitAppender::unexpectedInfoSeen = false;
/*static*/ QString  JUnitAppender::unexpectedInfoContent = nullptr;
bool JUnitAppender::hold = false;

