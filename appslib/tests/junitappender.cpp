#include "junitappender.h"
#include "assert1.h"
#include "level.h"
#include "loggingevent.h"
#include "stringutils.h"
#include "consoleinterface.h"
#include <QDebug>

JUnitAppender::JUnitAppender(QObject *parent) : QObject(parent)
{
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

static boolean hold = false;

static private JUnitAppender instance = null;

// package-level access for testing
static boolean unexpectedFatalSeen = false;
static String  unexpectedFatalContent = null;
static boolean unexpectedErrorSeen = false;
static String  unexpectedErrorContent = null;
static boolean unexpectedWarnSeen = false;
static String  unexpectedWarnContent = null;
static boolean unexpectedInfoSeen = false;
static String  unexpectedInfoContent = null;

/*public*/ static boolean unexpectedMessageSeen(Level l) {
    if (l == Level.FATAL) {
        return unexpectedFatalSeen;
    }
    if (l == Level.ERROR) {
        return unexpectedFatalSeen || unexpectedErrorSeen;
    }
    if (l == Level.WARN) {
        return unexpectedFatalSeen || unexpectedErrorSeen || unexpectedWarnSeen;
    }
    if (l == Level.INFO) {
        return unexpectedFatalSeen || unexpectedErrorSeen || unexpectedWarnSeen || unexpectedInfoSeen;
    }
    throw new java.lang.IllegalArgumentException("Did not expect " + l);
}

/*public*/ static String unexpectedMessageContent(Level l) {
    if (l == Level.FATAL) {
        return unexpectedFatalContent;
    }
    if (l == Level.ERROR) {
        if (unexpectedFatalContent != null ) return unexpectedFatalContent;
        return unexpectedErrorContent;
    }
    if (l == Level.WARN) {
        if (unexpectedFatalContent != null ) return unexpectedFatalContent;
        if (unexpectedErrorContent != null ) return unexpectedErrorContent;
        return unexpectedWarnContent;
    }
    if (l == Level.INFO) {
        if (unexpectedFatalContent != null ) return unexpectedFatalContent;
        if (unexpectedErrorContent != null ) return unexpectedErrorContent;
        if (unexpectedWarnContent != null ) return unexpectedWarnContent;
        return unexpectedInfoContent;
    }
    throw new java.lang.IllegalArgumentException("Did not expect " + l);
}

/*public*/ static void resetUnexpectedMessageFlags(Level severity) {
    // cases statements are organized to flow
    switch (severity.toInt()) {
        case Level.INFO_INT:
            unexpectedInfoSeen = false;
            unexpectedInfoContent = null;
            //$FALL-THROUGH$
        case Level.WARN_INT:
            unexpectedWarnSeen = false;
            unexpectedWarnContent = null;
            //$FALL-THROUGH$
        case Level.ERROR_INT:
            unexpectedErrorSeen = false;
            unexpectedErrorContent = null;
            //$FALL-THROUGH$
        case Level.FATAL_INT:
            unexpectedFatalSeen = false;
            unexpectedFatalContent = null;
            break;
        default:
            Log.warn("Unhandled serverity code: {}", severity.toInt());
            break;
    }
}
#endif
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
#if 0
/**
 * do common local processing of event, then pass up to super class
 *
 * @param l the event to process
 */
void superappend(LoggingEvent l) {
    if (l.getLevel() == Level.FATAL) {
        unexpectedFatalSeen = true;
        unexpectedFatalContent = l.getMessage().toString();
    }
    if (l.getLevel() == Level.ERROR) {
        if (compare(l, "Uncaught Exception caught by jmri.util.exceptionhandler.UncaughtExceptionHandler")) {
            // still an error, just suppressed
        } else {
            unexpectedErrorSeen = true;
            unexpectedErrorContent = l.getMessage().toString();
        }
    }
    if (l.getLevel() == Level.WARN) {
        unexpectedWarnSeen = true;
        unexpectedWarnContent = l.getMessage().toString();
    }
    if (l.getLevel() == Level.INFO) {
        unexpectedInfoSeen = true;
        unexpectedInfoContent = l.getMessage().toString();
    }

    super.append(l);
}
#endif
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
/*public*/ /*static*/ int JUnitAppender::clearBacklog(LogLevel::VALS level) {
    if (list.isEmpty()) {
        return 0;
    }
    int retval = 0;
#if 0
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
#if 0
/**
 * Verify that no messages were emitted, logging any that were. Does not
 * stop the logging. Clears the accumulated list.
 *
 * @return true if no messages logged
 */
/*public*/ static boolean verifyNoBacklog() {
    if (list.isEmpty()) {
        return true;
    }
    while (!list.isEmpty()) { // should probably add a skip of lower levels?
        LoggingEvent evt = list.remove(0);
        instance().superappend(evt);
    }
    return false;
}
#endif
/**
 * Check that the next queued message was of Error severity, and has a
 * specific message. White space is ignored.
 * <p>
 * Invokes a JUnit Assert if the message doesn't match.
 *
 * @param msg the message to assert exists
 */
/*public*/ /*static*/ void JUnitAppender::assertErrorMessage(QString msg) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg);
        return;
    }

    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    // next piece of code appears three times, should be refactored away during Log4J 2 migration
    while ((evt->getLevel() == LogLevel::INFO) || (evt->getLevel() == LogLevel::DEBUG) || (evt->getLevel() == LogLevel::TRACE))
    { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Only debug/info messages present: " + msg);
            return;
        }
        //evt = list.remove(0);
        evt = list.at(0);
           list.removeAt(0);}

    // check the remaining message, if any
    if (evt->getLevel() != LogLevel::ERROR) {
        qDebug() << "value: " << evt->getLevel() << "expected: " << LogLevel::ERROR;
        Assert::fail("Level mismatch when looking for ERROR message: \"" +
                msg +
                "\" found \"" +
                 evt->getMessage() +
                "\"");
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for ERROR message \"" + msg + "\" got \"" + evt->getMessage() + "\"");
    }
}
#if 0
/**
 * Check that the next queued message was of Error severity, and has a
 * specific message. White space is ignored.
 * <p>
 * Invokes a JUnit Assert if the message doesn't match.
 *
 * @param msg the message to assert exists
 */
/*public*/ static void assertErrorMessageStartsWith(String msg) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg);
        return;
    }

    LoggingEvent evt = list.remove(0);

    // next piece of code appears three times, should be refactored away during Log4J 2 migration
    while ((evt.getLevel() == Level.INFO) || (evt.getLevel() == Level.DEBUG) || (evt.getLevel() == Level.TRACE)) { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Only debug/info messages present: " + msg);
            return;
        }
        evt = list.remove(0);
    }

    // check the remaining message, if any
    if (evt.getLevel() != Level.ERROR) {
        Assert::fail("Level mismatch when looking for ERROR message: \"" +
                msg +
                "\" found \"" +
                (String) evt.getMessage() +
                "\"");
    }

    if (!compareStartsWith(evt, msg)) {
        Assert::fail("Looking for ERROR message \"" + msg + "\" got \"" + evt.getMessage() + "\"");
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
/*public*/ static void suppressMessage(Level level, String msg) {
    if (list.isEmpty()) {
        return;
    }

    LoggingEvent evt = list.remove(0);

    while (((level.equals(Level.WARN)) &&
            (evt.getLevel() == Level.TRACE ||
                    evt.getLevel() == Level.DEBUG ||
                    evt.getLevel() == Level.INFO ||
                    evt.getLevel() == Level.WARN)) ||
            ((level.equals(Level.ERROR)) &&
                    (evt.getLevel() == Level.TRACE ||
                            evt.getLevel() == Level.DEBUG ||
                            evt.getLevel() == Level.INFO ||
                            evt.getLevel() == Level.WARN ||
                            evt.getLevel() == Level.ERROR))) { // this is much better with Log4J 2's compareTo method
        if (list.isEmpty()) {
            return;
        }
        evt = list.remove(0);
    }

    // check the remaining message, if any
    if (evt.getLevel() != level) {
        Assert::fail("Level mismatch when looking for " +
                level +
                " message: \"" +
                msg +
                "\" found \"" +
                (String) evt.getMessage() +
                "\"");
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for " + level + " message \"" + msg + "\" got \"" + evt.getMessage() + "\"");
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
/*public*/ static void suppressMessageStartsWith(Level level, String msg) {
    if (list.isEmpty()) {
        return;
    }

    LoggingEvent evt = list.remove(0);

    while (((level.equals(Level.WARN)) &&
            (evt.getLevel() == Level.TRACE ||
                    evt.getLevel() == Level.DEBUG ||
                    evt.getLevel() == Level.INFO ||
                    evt.getLevel() == Level.WARN)) ||
            ((level.equals(Level.ERROR)) &&
                    (evt.getLevel() == Level.TRACE ||
                            evt.getLevel() == Level.DEBUG ||
                            evt.getLevel() == Level.INFO ||
                            evt.getLevel() == Level.WARN ||
                            evt.getLevel() == Level.ERROR))) { // this is much better with Log4J 2's compareTo method
        if (list.isEmpty()) {
            return;
        }
        evt = list.remove(0);
    }

    // check the remaining message, if any
    if (evt.getLevel() != level) {
        Assert::fail("Level mismatch when looking for " +
                level +
                " message: \"" +
                msg +
                "\" found \"" +
                (String) evt.getMessage() +
                "\"");
    }

    if (!compareStartsWith(evt, msg)) {
        Assert::fail("Looking for " + level + " message \"" + msg + "\" got \"" + evt.getMessage() + "\"");
    }
}

/**
 * If there's a next matching message of Error severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ static void suppressErrorMessage(String msg) {
    suppressMessage(Level.ERROR, msg);
}

/**
 * If there's a next matching message of Error severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ static void suppressErrorMessageStartsWith(String msg) {
    suppressMessageStartsWith(Level.ERROR, msg);
}

/**
 * If there's a next matching message of Warn severity, just ignore it. Not
 * an error if not present; mismatch is an error. White space is ignored.
 *
 * @param msg the message to suppress
 */
/*public*/ static void suppressWarnMessage(String msg) {
    suppressMessage(Level.WARN, msg);
}
#endif
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
/*public*/ /*static*/ void JUnitAppender::assertWarnMessage(QString msg) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg);
        return;
    }
    LoggingEvent* evt = checkForMessage(msg);

    if (evt == nullptr) {
        Assert::fail("Looking for message \"" + msg + "\" and didn't find it");
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
/*public*/ /*static*/ void JUnitAppender::assertMessage(QString msg) {
    if (list.isEmpty()) {
        Assert::fail("No message present: " + msg);
        return;
    }
    LoggingEvent* evt = list.at(0);
    list.removeAt(0);

    while ((evt->getLevel() == LogLevel::INFO) || (evt->getLevel() == LogLevel::DEBUG) || (evt->getLevel() == LogLevel::TRACE)) { // better in Log4J 2
        if (list.isEmpty()) {
            Assert::fail("Message not found: " + msg);
            return;
        }
        evt = list.at(0);
        list.removeAt(0);
    }

    if (!compare(evt, msg)) {
        Assert::fail("Looking for message \"" + msg + "\" got \"" + evt->getMessage() + "\"");
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
#if 0
/**
 * Compare two message strings, handling nulls and ignoring whitespace.
 *
 * @param e1 the event
 * @param s2 the string to compare e1 to
 * @return true if message in e1 starts with s2; false otherwise
 */
protected static boolean compareStartsWith(LoggingEvent e1, String s2) {
    if (e1 == null) {
        System.err.println("Logging event null when comparing to " + s2);
        return s2 == null;
    } else if (e1.getMessage() == null) {
        System.err.println("Logging event has null message when comparing to " + s2);
        return s2 == null;
    }
    String s1 = e1.getMessage().toString();
    return StringUtils.deleteWhitespace(s1).startsWith(StringUtils.deleteWhitespace(s2));
}
#endif
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