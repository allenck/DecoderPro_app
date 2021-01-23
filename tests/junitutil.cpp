#include "junitutil.h"
#include "loggerfactory.h"
#include <QDateTime>
#include "fileutil.h"
#include "profile.h"
#include "rosterconfigmanager.h"
#include "instancemanager.h"
#include "profilemanager.h"
#include "nullprofile.h"
#include "sleeperthread.h"
#include "assert1.h"
#include "junitappender.h"
#include <QDebug>
#include "testuserpreferencesmanager.h"
#include "configuremanager.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "defaultsignalmastlogicmanager.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "defaultmemorymanager.h"
#include "internalreportermanager.h"
#include "layoutblockmanager.h"
#include <QApplication>
#include "internalsensormanager.h"
#include "joptionpane.h"
#include "jmriconfigurationmanager.h"
#include "defaultlogixmanager.h"
#include "defaultconditionalmanager.h"
#include "debugthrottlemanager.h"
#include "mockshutdownmanager.h"
#include "jmriuserinterfaceconfigurationprovider.h"
#include "debugprogrammermanager.h"
#include "blockmanager.h"

JUnitUtil::JUnitUtil(QObject *parent) : QObject(parent)
{

}
/**
 * Common utility methods for working with JUnit.
 * <p>
 * To release the current thread and allow other listeners to execute:  <code><pre>
 * JUnitUtil.releaseThread(this);
 * </pre></code> Note that this is not appropriate for Swing objects; you need
 * to use Jemmy for that.
 * <p>
 * If you're using the InstanceManager, setUp() implementation should start
 * with:
 * <pre><code>
 * JUnitUtil.setUp();
 * JUnitUtil.initInternalTurnoutManager();
 * JUnitUtil.initInternalLightManager();
 * JUnitUtil.initInternalSensorManager();
 * JUnitUtil.initDebugThrottleManager();
 * </code></pre>
 * <p>
 * Your tearDown() should end with:
 * <pre><code>
 * JUnitUtil.tearDown();
 * </code></pre>
 * <p>
 * Note that memory managers and some others are completely internal, and will
 * be reset when you reset the instance manager.
 *
 * @author Bob Jacobsen Copyright 2009, 2015
 * @since 2.5.3
 */
// /*public*/ class JUnitUtil {

/**
 * Standard time (in mSec) to wait when releasing
 * a thread during a test.
 * <p>
 * public in case modification is needed from a test or script.
 */
/*static*/ /*final*/ /*public*/ int JUnitUtil::DEFAULT_RELEASETHREAD_DELAY = 50;

/**
 * Standard time step (in mSec) when looping in a waitFor operation.
 * <p>
 * public in case modification is needed from a test or script.
 */
/*static*/ /*final*/ /*public*/ int JUnitUtil::WAITFOR_DELAY_STEP = 5;
/**
 * Maximum time to wait before failing a waitFor operation.
 * The default value is really long, but that only matters when the test is failing anyway,
 * and some of the LayoutEditor/SignalMastLogic tests are slow. But too long will cause CI jobs
 * to time out before this logs the error....
 * <p>
 * public in case modification is needed from a test or script.
 */
/*static*/ /*final*/ /*public*/ int JUnitUtil::WAITFOR_MAX_DELAY = 10000;

/**
 * When true, prints each setUp method to help identify which tests include a failure.
 * When checkSetUpTearDownSequence is also true, this also sprints on execution of tearDown.
 * <p>
 * Set from the jmri.util.JUnitUtil.printSetUpTearDownNames environment variable.
 */
/*static*/ bool JUnitUtil::printSetUpTearDownNames = false; //bool.getbool("jmri.util.JUnitUtil.printSetUpTearDownNames"); // false unless set true

/**
 * When true, checks that calls to setUp and tearDown properly alterante, printing an
 * error message with context information on System.err if inconsistent calls are observed.
 * <p>
 * Set from the jmri.util.JUnitUtil.checkSetUpTearDownSequence environment variable.
 */
/*static*/ bool JUnitUtil::checkSetUpTearDownSequence = false; //bool.getbool("jmri.util.JUnitUtil.checkSetUpTearDownSequence"); // false unless set true

/**
 * Adds extensive error information to the output of checkSetUpTearDownSequence.
 * Note: The context checking and storage required for this takes a lot of time.
 * <p>
 * Set from the jmri.util.JUnitUtil.checkSequenceDumpsStack environment variable.
 */
/*static*/ bool JUnitUtil::checkSequenceDumpsStack =    false; //bool.getbool("jmri.util.JUnitUtil.checkSequenceDumpsStack"); // false unless set true

/**
 * Check for any threads left behind after a test calls {@link #tearDown}
 * <p>
 * Set from the jmri.util.JUnitUtil.checkRemnantThreads environment variable.
 */
/*static*/ bool JUnitUtil::checkRemnantThreads =    false; //bool.getbool("jmri.util.JUnitUtil.checkRemnantThreads"); // false unless set true

/**
 * Check for tests that take an excessive time
 * <p>
 * Set from the jmri.util.JUnitUtil.checkTestDuration environment variable.
 */
/*static*/ bool JUnitUtil::checkTestDuration =      false; //bool.getbool("jmri.util.JUnitUtil.checkTestDuration"); // false unless set true
/*static*/ long    JUnitUtil::checkTestDurationMax =   5000; //Long.getLong("jmri.util.JUnitUtil.checkTestDurationMax", 5000); // milliseconds

/*static*/ qint64    JUnitUtil::checkTestDurationStartTime = 0;  // working value

/*static*/ /*private*/ int JUnitUtil::threadCount = 0;

/*static*/ /*private*/ bool JUnitUtil::didSetUp = false;
/*static*/ /*private*/ bool JUnitUtil::didTearDown = true;
/*static*/ /*private*/ QString JUnitUtil::lastSetUpClassName = "<unknown>";
/*static*/ /*private*/ QString JUnitUtil::lastSetUpThreadName = "<unknown>";
//    static /*private*/ StackTraceElement[] lastSetUpStackTrace = new StackTraceElement[0];
/*static*/ /*private*/ QString JUnitUtil::lastTearDownClassName = "<unknown>";
/*static*/ /*private*/QString JUnitUtil::lastTearDownThreadName = "<unknown>";
//    static /*private*/ StackTraceElement[] lastTearDownStackTrace = new StackTraceElement[0];

/*static*/ /*private*/ bool JUnitUtil::isLoggingInitialized = false;
/*static*/ /*private*/ QString JUnitUtil::initPrefsDir = "";
/**
 * JMRI standard setUp for tests. This should be the first line in the {@code @Before}
 * annotated method.
 */
/*public*/ /*static*/ void JUnitUtil::setUp() {
#if 0
    if (!isLoggingInitialized) {
        // init logging if needed
        isLoggingInitialized = true;
        QString filename = System.getProperty("jmri.log4jconfigfilename", "tests.lcf");
        Log4JUtil.initLogging(filename);
    }
#endif
    // need to do this each time
    try {
        JUnitAppender::start();
#if 0
        // reset warn _only_ once logic to make tests repeatable
        Log4JUtil.restartWarnOnce();
        // ensure logging of deprecated method calls;
        // individual tests can turn off as needed
        Log4JUtil.setDeprecatedLogging(true);
#endif
    } catch (Throwable e) {
//        System.err.println("Could not start JUnitAppender, but test continues:\n" + e);
        qDebug() << "Could not start JUnitAppender, but test continues:\n" + e.getMessage();
    }

    // clear the backlog and reset the UnexpectedMessageFlags so that
    // errors from a previous test do not interfere with the current test.
    JUnitAppender::clearBacklog();
    JUnitAppender::resetUnexpectedMessageFlags(LogLevel::INFO);

#if 0
    // do not set the UncaughtExceptionHandler while unit testing
    // individual tests can explicitly set it after calling this method
    Thread.setDefaultUncaughtExceptionHandler(null);

    // make sure the jmri.prefsdir property match the property passed
    // to the tests.
    if (initPrefsDir == null) {
        initPrefsDir = System.getProperty("jmri.prefsdir", "./temp");
    }
    System.setProperty("jmri.prefsdir",initPrefsDir);

    // silence the Jemmy GUI unit testing framework
    JUnitUtil.silenceGUITestOutput();

    // ideally this would be resetWindows(false, true) to force an error if an earlier
    // test left a window open, but different platforms seem to have just
    // enough differences that this is, for now, turned off
    resetWindows(false, false);
#endif
    // Do a minimal amount of de-novo setup
    resetInstanceManager();
#if 0
    // Log and/or check the use of setUp and tearDown
    if (checkSetUpTearDownSequence || printSetUpTearDownNames) {
        lastSetUpClassName = getTestClassName();

        if (printSetUpTearDownNames) System.err.println(">> Starting test in "+lastSetUpClassName);

        if ( checkSetUpTearDownSequence)  {
            if (checkSequenceDumpsStack)  lastSetUpThreadName = Thread.currentThread().getName();

            if (didSetUp || ! didTearDown) {
                System.err.println("   "+getTestClassName()+".setUp on thread "+lastSetUpThreadName+" unexpectedly found setUp="+didSetUp+" tearDown="+didTearDown+"; last tearDown was in "+lastTearDownClassName+" thread "+lastTearDownThreadName);
                if (checkSequenceDumpsStack) {
                    System.err.println("---- This stack ------");
                    Thread.dumpStack();
                    System.err.println("---- Last setUp stack ------");
                    for (StackTraceElement e : lastSetUpStackTrace) System.err.println("	at "+e);
                    System.err.println("---- Last tearDown stack ------");
                    for (StackTraceElement e : lastTearDownStackTrace) System.err.println("	at "+e);
                    System.err.println("----------------------");
                }
            }

            didTearDown = false;
            didSetUp = true;

            if (checkSequenceDumpsStack) lastSetUpStackTrace = Thread.currentThread().getStackTrace();
        }
    }
#endif
    // checking time?
    if (checkTestDuration) checkTestDurationStartTime = QDateTime::currentMSecsSinceEpoch(); //System.currentTimeMillis();

    if(QDir::currentPath() != FileUtil::getProgramPath())
     QDir::setCurrent(FileUtil::getProgramPath());
}

/**
 * Teardown from tests. This should be the last line in the {@code @After}
 * annotated method.
 */
/*public*/ /*static*/ void JUnitUtil::tearDown() {
 testClassName = "";

    // checking time?
    if (checkTestDuration) {
        quint64 duration = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() - checkTestDurationStartTime;
        if (duration > checkTestDurationMax) {
            // test too long, log that
            log->warn(tr("Test in %1 duration %2 msec exceeded limit %3").arg(getTestClassName()).arg(duration).arg(checkTestDurationMax));
        }
    }
    // Log and/or check the use of setUp and tearDown
    if (checkSetUpTearDownSequence || printSetUpTearDownNames) {
        lastTearDownClassName = getTestClassName();
#if 0
        if (checkSetUpTearDownSequence) {
            if (checkSequenceDumpsStack) lastTearDownThreadName = Thread.currentThread().getName();

            if (! didSetUp || didTearDown) {
                System.err.println("   "+getTestClassName()+".tearDown on thread "+lastTearDownThreadName+" unexpectedly found setUp="+didSetUp+" tearDown="+didTearDown+"; last setUp was in "+lastSetUpClassName+" thread "+lastSetUpThreadName);
                if (checkSequenceDumpsStack) {
                    System.err.println("---- This stack ------");
                    Thread.dumpStack();
                    System.err.println("---- Last setUp stack ------");
                    for (StackTraceElement e : lastSetUpStackTrace) System.err.println("	at "+e);
                    System.err.println("---- Last tearDown stack ------");
                    for (StackTraceElement e : lastTearDownStackTrace) System.err.println("	at "+e);
                    System.err.println("----------------------");
                }
            }
            didSetUp = false;
            didTearDown = true;
            if (checkSequenceDumpsStack) lastTearDownStackTrace = Thread.currentThread().getStackTrace();
        }

        // To save time & space, only print end when doing full check
        if (printSetUpTearDownNames && checkSetUpTearDownSequence)  System.err.println("<<   Ending test in "+lastTearDownClassName);
#endif
    }
#if 0
    // ideally this would be resetWindows(false, true) to force an error if an earlier
    // test left a window open, but different platforms seem to have just
    // enough differences that this is, for now, turned off
    resetWindows(false, false);
#endif
    // Check final status of logging in the test just completed
    JUnitAppender::end();

    LogLevel* severity = LogLevel::ERROR; // level at or above which we'll complain
    bool unexpectedMessageSeen = JUnitAppender::unexpectedMessageSeen(severity);
    QString unexpectedMessageContent = JUnitAppender::unexpectedMessageContent(severity);
    JUnitAppender::verifyNoBacklog();
    JUnitAppender::resetUnexpectedMessageFlags(severity);
    Assert::assertFalse("Unexpected "+severity->toString()+" or higher messages emitted: "+unexpectedMessageContent, unexpectedMessageSeen, __FILE__, __LINE__);
#if 0
    // Optionally, check that no threads were left running (controlled by jmri.util.JUnitUtil.checkRemnantThreads environment var)
    if (checkRemnantThreads) {
        checkThreads();
    }

    // Optionally, print whatever is on the Swing queue to see what's keeping things alive
    //Object entry = java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().peekEvent();
    //if (entry != null) System.err.println("entry: "+entry);

    // Optionally, check that the Swing queue is idle
    //new org.netbeans.jemmy.QueueTool().waitEmpty(250);
#endif
}
#if 0
/**
 * Release the current thread, allowing other threads to process. Waits for
 * {@value #DEFAULT_RELEASETHREAD_DELAY} milliseconds.
 * <p>
 * This cannot be used on the Swing or AWT event threads. For those, please
 * use Jemmy's wait routine.
 *
 * @param self currently ignored
 * @deprecated 4.9.1 Use the various waitFor routines instead
 */
@Deprecated // 4.9.1 Use the various waitFor routines instead
/*public*/ static void releaseThread(Object self) {
    releaseThread(self, DEFAULT_RELEASETHREAD_DELAY);
}

/**
 * Release the current thread, allowing other threads to process.
 * <p>
 * This cannot be used on the Swing or AWT event threads. For those, please
 * use Jemmy's wait routine.
 *
 * @param self  currently ignored
 * @param delay milliseconds to wait
 * @deprecated 4.9.1 Use the various waitFor routines instead
 */
@Deprecated // 4.9.1 Use the various waitFor routines instead
/*public*/ static void releaseThread(Object self, int delay) {
    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
        log.error("Cannot use releaseThread on Swing thread", new Exception());
        return;
    }
    try {
        int priority = Thread.currentThread().getPriority();
        Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
        Thread.sleep(delay);
        Thread.currentThread().setPriority(priority);
    } catch (InterruptedException e) {
        Assert.fail("failed due to InterruptedException");
    }
}
#endif
/**
 * Wait for a specific condition to be true, without having to wait longer
 * <p>
 * To be used in tests, will do an assert if the total delay is longer than
 * WAITFOR_MAX_DELAY
 * <p>
 * Typical use:
 * <code>JUnitUtil.waitFor(()->{return replyVariable != null;},"reply not received")</code>
 *
 * @param condition condition being waited for
 * @param name      name of condition being waited for; will appear in
 *                  Assert.fail if condition not true fast enough
 */
/*static*/ /*public*/ void JUnitUtil::waitFor(ReleaseUntil* condition, QString name,
                                              QString file, int line)
{
//    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
//        log.error("Cannot use waitFor on Swing thread", new Exception());
//        return;
//    }

 int delay = 0;
 try
 {
  while (delay < WAITFOR_MAX_DELAY)
  {
   if (condition->ready())
   {
    log->debug(tr("return delay = %1").arg(delay));
    return;
   }
#if 0
         int priority = Thread.currentThread().getPriority();
         try {
             Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
             Thread.sleep(WAITFOR_DELAY_STEP);
             delay += WAITFOR_DELAY_STEP;
         } catch (InterruptedException e) {
             Assert.fail("failed due to InterruptedException");
         } finally {
             Thread.currentThread().setPriority(priority);
         }
#endif
   SleeperThread::msleep(WAITFOR_DELAY_STEP);
   delay += WAITFOR_DELAY_STEP;
   qApp->processEvents();
  }

  Assert::fail("\"" + name + "\" did not occur in time", file, line);
 }
 catch (Exception ex)
 {
  Assert::fail("Exception while waiting for \"" + name + "\" " + ex.getMessage(), file, line);
 }
}

/*static*/ /*public*/ void JUnitUtil::waitFor(bool (*condition)(), QString name,
                                              QString file, int line)
{

 int delay = 0;
 try
 {
  while (delay < WAITFOR_MAX_DELAY)
  {
   if ((*condition)())
   {
    log->debug(tr("return delay = %1").arg(delay));
    return;
   }
   SleeperThread::msleep(WAITFOR_DELAY_STEP);
   delay += WAITFOR_DELAY_STEP;
   qApp->processEvents();
  }

  Assert::fail("\"" + name + "\" did not occur in time", file, line);
 }
 catch (Exception ex)
 {
  Assert::fail("Exception while waiting for \"" + name + "\" " + ex.getMessage(), file, line);
 }
}
/**
 * Wait for a specific condition to be true, without having to wait longer
 * <p>
 * To be used in assumptions, will return false if the total delay is longer
 * than WAITFOR_MAX_DELAY
 * <p>
 * Typical use:
 * <code>Assume.assumeTrue("reply not received", JUnitUtil.waitForTrue(()->{return replyVariable != null;}));</code>
 *
 * @param condition condition to wait for
 * @return true if condition is met before WAITFOR_MAX_DELAY, false
 *         otherwise
 */
/*static*/ /*public*/ bool JUnitUtil::waitFor(ReleaseUntil* condition, QString file, int line) {
//    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
//        log.error("Cannot use waitFor on Swing thread", new Exception());
//        return false;
//    }
    int delay = 0;
#if 0
    try {
        while (delay < WAITFOR_MAX_DELAY) {
            if (condition.ready()) {
                return true;
            }
            int priority = Thread.currentThread().getPriority();
            try {
                Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
                Thread.sleep(WAITFOR_DELAY_STEP);
                delay += WAITFOR_DELAY_STEP;
            } catch (InterruptedException e) {
                return false;
            } finally {
                Thread.currentThread().setPriority(priority);
            }
        }
        return false;
    } catch (Exception ex) {
        log.error("Exception in waitFor condition.", ex);
        return false;
    }
#endif
    try {
        while (delay < WAITFOR_MAX_DELAY) {
            if (condition->ready()) {
                return true;
            }
            SleeperThread::msleep(WAITFOR_DELAY_STEP);
            delay += WAITFOR_DELAY_STEP;
            qApp->processEvents();
        }

        Assert::fail("did not occur in time", file, line);
    } catch (Exception ex) {
        Assert::fail("Exception while waiting for  " + ex.getMessage(), file, line);
    }

}

/**
 * Wait for a specific amount of time
 * <p>
 * It's better to wait for a condition, but if you can't find a condition,
 * this will have to do.
 * <p>
 *
 * @param time Delay in msec
 */
/*static*/ /*public*/ void JUnitUtil::waitFor(int time) {
//    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
//        log.error("Cannot use waitFor on Swing thread", new Exception());
//        return;
//    }
    int delay = 0;

    try {
        while (delay < time) {
//            int priority = Thread.currentThread().getPriority();
//            try {
//                Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
//                Thread.sleep(WAITFOR_DELAY_STEP);
//                delay += WAITFOR_DELAY_STEP;
//            } catch (InterruptedException e) {
//                return;
//            } finally {
//                Thread.currentThread().setPriority(priority);
//            }
         SleeperThread::msleep(WAITFOR_DELAY_STEP);
         delay += WAITFOR_DELAY_STEP;
         qApp->processEvents();
        }
        return;
    } catch (Exception ex) {
        log->error("Exception in waitFor condition.", ex);
        return;
    }
}

/**
 * Wait for a specific condition to be true, without having to wait longer
 * <p>
 * To be used in tests, will do an assert if the total delay is longer than
 * 1 second
 * <p>
 * Typical use:
 * <code>JUnitUtil.fasterWaitFor(()->{return replyVariable != null;},"reply not received")</code>
 *
 * @param condition condition being waited for
 * @param name      name of condition being waited for; will appear in
 *                  Assert.fail if condition not true fast enough
 */
/*static*/ /*public*/ bool JUnitUtil::fasterWaitFor(ReleaseUntil* condition, QString name, QString file, int line){
//    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
//        log.error("Cannot use waitFor on Swing thread", new Exception());
//        return;
//    }
    int delay = 0;
    try {
        while (delay < 1000) {
            if (condition->ready()) {
                return true;
            }
//            int priority = Thread.currentThread().getPriority();
//            try {
//                Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
//                Thread.sleep(5);
//                delay += 5;
//            } catch (InterruptedException e) {
//                Assert.fail("failed due to InterruptedException");
//            } finally {
//                Thread.currentThread().setPriority(priority);
//            }
            SleeperThread::msleep(5);
            delay += 5;
            qApp->processEvents();
        }
        Assert::fail("\"" + name + "\" did not occur in time", file, line);
    } catch (Exception ex) {
        Assert::fail("Exception while waiting for \"" + name + "\" " + ex.getMessage(), file, line);
    }
}
#if 0
/**
 * Wait at most 1 second for a specific condition to be true, without having to wait longer
 * <p>
 * To be used in assumptions, will return false if the total delay is longer
 * than 1000 milliseconds.
 * <p>
 * Typical use:
 * <code>Assume.assumeTrue("reply not received", JUnitUtil.fasterWaitForTrue(()->{return replyVariable != null;}));</code>
 *
 * @param condition condition to wait for
 * @return true if condition is met before 1 second, false
 *         otherwise
 */
static /*public*/ bool fasterWaitFor(ReleaseUntil condition) {
    if (javax.swing.SwingUtilities.isEventDispatchThread()) {
        log.error("Cannot use waitFor on Swing thread", new Exception());
        return false;
    }
    int delay = 0;
    try {
        while (delay < 1000) {
            if (condition.ready()) {
                return true;
            }
            int priority = Thread.currentThread().getPriority();
            try {
                Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
                Thread.sleep(5);
                delay += 5;
            } catch (InterruptedException e) {
                return false;
            } finally {
                Thread.currentThread().setPriority(priority);
            }
        }
        return false;
    } catch (Exception ex) {
        log.error("Exception in waitFor condition.", ex);
        return false;
    }
}

/**
 * Reset the user files path in the default
 * {@link jmri.util.FileUtilSupport} object (used by
 * {@link jmri.util.FileUtil}) to the default settings/user files path for
 * tests of {@code git-working-copy/temp}.
 */
/*public*/ static void resetFileUtilSupport() {
    try {
        Field field = FileUtilSupport.class.getDeclaredField("defaultInstance");
        field.setAccessible(true);
        field.set(null, null);
        FileUtilSupport.getDefault().setUserFilesPath(ProfileManager.getDefault().getActiveProfile(), FileUtil.getPreferencesPath());
    } catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException ex) {
        log.error("Exception resetting FileUtilSupport", ex);
    }
}

static /*public*/ interface ReleaseUntil {

    /*public*/ bool ready() throws Exception;
}

/**
 * Set a NamedBean (Turnout, Sensor, SignalHead, ...) to a specific value in
 * a thread-safe way.
 * <p>
 * You can't assume that all the consequences of that setting will have
 * propagated through when this returns; those might take a long time. But
 * the set operation itself will be complete.
 *
 * @param bean  the bean
 * @param state the desired state
 */
static /*public*/ void setBeanState(NamedBean bean, int state) {
    try {
        javax.swing.SwingUtilities.invokeAndWait(
                () -> {
                    try {
                        bean.setState(state);
                    } catch (JmriException e) {
                        log.error("Threw exception while setting state: ", e);
                    }
                }
        );
    } catch (InterruptedException e) {
        log.warn("Interrupted while setting state: ", e);
    } catch (InvocationTargetException e) {
        log.warn("Failed during invocation while setting state: ", e);
    }
}

/**
 * Set a NamedBean (Turnout, Sensor, SignalHead, ...) to a specific value in
 * a thread-safe way, including waiting for the state to appear.
 * <p>
 * You can't assume that all the consequences of that setting will have
 * propagated through when this returns; those might take a long time. But
 * the set operation itself will be complete.
 *
 * @param bean  the bean
 * @param state the desired state
 */
static /*public*/ void setBeanStateAndWait(NamedBean bean, int state) {
    setBeanState(bean, state);
    JUnitUtil.waitFor(() -> {
        return state == bean.getState();
    }, "setAndWait " + bean.getSystemName() + ": " + state);
}
#endif
/*public*/ /*static*/ void JUnitUtil::resetInstanceManager() {
    // clear all instances from the static InstanceManager
    InstanceManager::getDefault()->clearAll();
    // ensure the auto-default UserPreferencesManager is not created by installing a test one
    InstanceManager::setDefault("UserPreferencesManager", new TestUserPreferencesManager());
}

/*public*/ /*static*/ void JUnitUtil::resetTurnoutOperationManager() {
    InstanceManager::reset("TurnoutOperationManager");
    InstanceManager::getDefault("TurnoutOperationManager"); // force creation
}

/*public*/ /*static*/ void JUnitUtil::initConfigureManager() {
    InstanceManager::setDefault("ConfigureManager", new JmriConfigurationManager());
}

/*public*/ /*static*/ void JUnitUtil::initDefaultUserMessagePreferences() {
    // remove the existing user preferences manager (if present)
    InstanceManager::reset("UserPreferencesManager");
    // create a test user preferences manager
    InstanceManager::setDefault("UserPreferencesManager", new TestUserPreferencesManager());
}

/*public*/ /*static*/ void JUnitUtil::initInternalTurnoutManager() {
    // now done automatically by InstanceManager's autoinit
    InstanceManager::turnoutManagerInstance();
}

/*public*/ /*static*/ void JUnitUtil::initInternalLightManager() {
    // now done automatically by InstanceManager's autoinit
    InstanceManager::lightManagerInstance();
}

/*public*/ /*static*/ void JUnitUtil::initInternalSensorManager() {
    // now done automatically by InstanceManager's autoinit
    InstanceManager::sensorManagerInstance();
    InternalSensorManager::setDefaultStateForNewSensors(Sensor::UNKNOWN);
}

/*public*/ /*static*/ void JUnitUtil::initRouteManager() {
    // routes provide sensors, so ensure the sensor manager is initialized
    // routes need turnouts, so ensure the turnout manager is initialized
    JUnitUtil::initInternalSensorManager();
    JUnitUtil::initInternalTurnoutManager();
    // now done automatically by InstanceManager's autoinit
    InstanceManager::getDefault("RouteManager");
}

/*public*/ /*static*/ void JUnitUtil::initMemoryManager() {
    MemoryManager* m = new DefaultMemoryManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(m, Manager::MEMORIES);
    }
}

/*public*/ /*static*/ void JUnitUtil::initReporterManager() {
    ReporterManager* m = new InternalReporterManager((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"));
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(m, Manager::REPORTERS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initOBlockManager() {
    OBlockManager* b = new OBlockManager();
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(b, Manager::OBLOCKS);
    }
}

/*public*/ /*static*/ void JUnitUtil::deregisterBlockManagerShutdownTask() {
        if (! InstanceManager::isInitialized("ShutDownManager")) return;
        if (! InstanceManager::isInitialized("BlockManager")) return;

        ((ShutDownManager*)InstanceManager
                ::getDefault("ShutDownManager"))
                ->deregister(((BlockManager*)InstanceManager::getDefault("BlockManager"))->shutDownTask);
    }
/*public*/ /*static*/ void JUnitUtil::initWarrantManager() {
    WarrantManager* w = new WarrantManager();
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(w, Manager::WARRANTS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initSignalMastLogicManager() {
    SignalMastLogicManager* w = new DefaultSignalMastLogicManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig((QObject*)w, Manager::SIGNALMASTLOGICS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initLayoutBlockManager() {
    LayoutBlockManager* w = new LayoutBlockManager();
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(w, Manager::LAYOUTBLOCKS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initSectionManager() {
    SectionManager* w = new SectionManager();
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(w, Manager::SECTIONS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initInternalSignalHeadManager() {
    SignalHeadManager* m = new AbstractSignalHeadManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    InstanceManager::setDefault("SignalHeadManager", m);
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(m, Manager::SIGNALHEADS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initDefaultSignalMastManager() {
    InstanceManager::setDefault("SignalMastManager", new DefaultSignalMastManager(InstanceManager::getDefault("InternalSystemConnectionMemo")));
}
#if 0
/*public*/ static void initDebugCommandStation() {
    jmri.CommandStation cs = new jmri.CommandStation() {
        @Override
        /*public*/ bool sendPacket(@Nonnull byte[] packet, int repeats) {
        return true;
        }

        @Override
        /*public*/ String getUserName() {
            return "testCS";
        }

        @Override
        /*public*/ String getSystemPrefix() {
            return "I";
        }

    };

    InstanceManager::store(cs, jmri.CommandStation.class);
}
#endif
/*public*/ /*static*/ void JUnitUtil::initDebugThrottleManager() {
    ThrottleManager* m = new DebugThrottleManager();
    InstanceManager::store(m, "ThrottleManager");
}

/*public*/ /*static*/ void JUnitUtil::initDebugProgrammerManager() {
    DebugProgrammerManager* m = new DebugProgrammerManager();
    InstanceManager::store(m, "AddressedProgrammerManager");
    InstanceManager::store(m, "GlobalProgrammerManager");
    //InstanceManager::store(m, "ProgrammerManager"); // added ACK

}
#if 0
/*public*/ static void initDebugPowerManager() {
    InstanceManager::setDefault(PowerManager.class, new PowerManagerScaffold());
}

/*public*/ static void initIdTagManager() {
    InstanceManager::reset(jmri.IdTagManager.class);
    InstanceManager::store(new DefaultIdTagManager(InstanceManager::getDefault(InternalSystemConnectionMemo.class)), jmri.IdTagManager.class);
}

/*public*/ static void initRailComManager() {
    InstanceManager::reset(jmri.RailComManager.class);
    InstanceManager::store(new DefaultRailComManager(), jmri.RailComManager.class);
}
#endif
/*public*/ /*static*/ void JUnitUtil::initLogixManager() {
    LogixManager* m = new DefaultLogixManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(m, Manager::LOGIXS);
    }
}

/*public*/ /*static*/ void JUnitUtil::initConditionalManager() {
    ConditionalManager* m = new DefaultConditionalManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr) {
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(m, Manager::CONDITIONALS);
    }
}
#if 0
/*public*/ static void initInternalTurnoutManagerThrowException() {
    InstanceManager::setDefault(TurnoutManager.class, new TurnoutManagerThrowExceptionScaffold());
}

/*public*/ static void initInternalSensorManagerThrowException() {
    InstanceManager::setDefault(SensorManager.class, new SensorManagerThrowExceptionScaffold());
}

/*public*/ static void initLightManagerThrowException() {
    InstanceManager::setDefault(LightManager.class, new InternalLightManagerThrowExceptionScaffold());
}

/*public*/ static void initMemoryManagerThrowException() {
    InstanceManager::setDefault(MemoryManager.class, new MemoryManagerThrowExceptionScaffold());
}

/*public*/ static void initSignalHeadManagerThrowException() {
    InstanceManager::setDefault(SignalHeadManager.class, new SignalHeadManagerThrowExceptionScaffold());
}

/*public*/ static void initSignalMastManagerThrowException() {
    InstanceManager::setDefault(SignalMastManager.class, new SignalMastManagerThrowExceptionScaffold());
}

/*public*/ static void initWarrantManagerThrowException() {
    InstanceManager::setDefault(WarrantManager.class, new WarrantManagerThrowExceptionScaffold());
}

/*public*/ static void initOBlockManagerThrowException() {
    InstanceManager::setDefault(OBlockManager.class, new OBlockManagerThrowExceptionScaffold());
}

/*public*/ static void initRouteManagerThrowException() {
    InstanceManager::setDefault(RouteManager.class, new RouteManagerThrowExceptionScaffold());
}

/**
 * Initialize a {@link jmri.util.zeroconf.MockZeroConfServiceManager} after
 * ensuring that any existing
 * {@link jmri.util.zeroconf.ZeroConfServiceManager} (real or mocked) has
 * stopped all services it is managing.
 */
/*public*/ static void initZeroConfServiceManager() {
    resetZeroConfServiceManager();
    InstanceManager::setDefault(ZeroConfServiceManager.class, new MockZeroConfServiceManager());
}

/**
 * Ensure that any existing
 * {@link jmri.util.zeroconf.ZeroConfServiceManager} (real or mocked) has
 * stopped all services it is managing.
 */
/*public*/ static void resetZeroConfServiceManager() {
    ZeroConfServiceManager manager = InstanceManager::containsDefault(ZeroConfServiceManager.class)
            ? InstanceManager::getDefault(ZeroConfServiceManager.class)
            : null;
    if (manager != null) {
        manager.stopAll();
        JUnitUtil.waitFor(() -> {
            return (manager.allServices().isEmpty());
        }, "Stopping all ZeroConf Services");
    }
}

/**
 * End any running BlockBossLogic (Simple Signal Logic) objects
 */
/*public*/ static void clearBlockBossLogic() {
    jmri.jmrit.blockboss.BlockBossLogic.stopAllAndClear();
}

/**
 * Leaves ShutDownManager, if any, in place,
 * but removes its contents.
 * @see #initShutDownManager()
 */
/*public*/ static void clearShutDownManager() {
    ShutDownManager sm = InstanceManager::getNullableDefault(jmri.ShutDownManager.class);
    if (sm == null) return;
    List<ShutDownTask> list = sm.tasks();
    while (!list.isEmpty()) {
        sm.deregister(list.get(0));
        list = sm.tasks();  // avoid ConcurrentModificationException
    }

    // use reflection to reset static fields in the class.
    try {
        Class<?> c = jmri.managers.DefaultShutDownManager.class;
        Field f = c.getDeclaredField("shuttingDown");
        f.setAccessible(true);
        f.set(sm, false);
    } catch (NoSuchFieldException | IllegalArgumentException | IllegalAccessException x) {
        log.error("Failed to reset DefaultShutDownManager shuttingDown field", x);
    }

}
#endif
/**
 * Creates, if needed, a new ShutDownManager, clearing any existing
 * ShutDownManager, and ensuring the ShutDownManager is not in the state of
 * ShuttingDown if the ShutDownManager is a MockShutDownManager.
 */
/*public*/ /*static*/ void JUnitUtil::initShutDownManager() {
    ShutDownManager* manager = (ShutDownManager*)InstanceManager::getDefault("ShutDownManager");
    QList<ShutDownTask*> tasks = manager->tasks();
    while (!tasks.isEmpty()) {
        manager->deregister(tasks.at(0));
        tasks = manager->tasks(); // avoid ConcurrentModificationException
    }
    //if (manager instanceof MockShutDownManager)
    if(static_cast<MockShutDownManager*>(manager))
    {
        ((MockShutDownManager*) manager)->resetShuttingDown();
    }
}
#if 0
/*public*/ static void initStartupActionsManager() {
    InstanceManager::store(
            new apps.StartupActionsManager(),
            apps.StartupActionsManager.class);
}

/*public*/ static void initConnectionConfigManager() {
    InstanceManager::setDefault(ConnectionConfigManager.class, new ConnectionConfigManager());
}
#endif
/*public*/ /*static*/ void JUnitUtil::initRosterConfigManager() {
    RosterConfigManager* manager = new RosterConfigManager();
    try {
        manager->initialize(ProfileManager::getDefault()->getActiveProfile());
    } catch (InitializationException ex) {
        log->error("Failed to initialize RosterConfigManager", ex);
    }
    InstanceManager::setDefault("RosterConfigManager", manager);
}
#if 0
/*
 * Use reflection to reset the jmri.Application instance
 */
/*public*/ static void resetApplication() {
    try {
        Class<?> c = jmri.Application.class;
        Field f = c.getDeclaredField("name");
        f.setAccessible(true);
        f.set(new jmri.Application(), null);
    } catch (NoSuchFieldException | IllegalArgumentException | IllegalAccessException x) {
        log.error("Failed to reset jmri.Application static field", x);
    }
}

/*
 * Use reflection to reset the apps.AppsBase instance
 */
/*public*/ static void resetAppsBase() {
    try {
        Class<?> c = apps.AppsBase.class;
        Field f = c.getDeclaredField("preInit");
        f.setAccessible(true);
        f.set(null, false);
    } catch (NoSuchFieldException | IllegalArgumentException | IllegalAccessException x) {
        log.error("Failed to reset apps.AppsBase static preInit field", x);
    }
}

/*
 * Use reflection to reset the jmri.util.node.NodeIdentity instance
 */
/*public*/ static void resetNodeIdentity() {
    try {
        Class<?> c = jmri.util.node.NodeIdentity.class;
        Field f = c.getDeclaredField("instance");
        f.setAccessible(true);
        f.set(c, null);
    } catch (NoSuchFieldException | IllegalArgumentException | IllegalAccessException x) {
        log.error("Failed to reset jmri.util.node.NodeIdentity instance", x);
    }
}


/*public*/ static void initGuiLafPreferencesManager() {
    GuiLafPreferencesManager m = new GuiLafPreferencesManager();
    InstanceManager::setDefault(GuiLafPreferencesManager.class, m);
}
#endif
/**
 * Use only if profile contents are not to be verified or modified in test.
 * If a profile will be written to and its contents verified as part of a
 * test use {@link #resetProfileManager(jmri.profile.Profile)} with a
 * provided profile.
 * <p>
 * The new profile will have the name {@literal TestProfile }, the id
 * {@literal 00000000 }, and will be in the directory {@literal temp }
 * within the sources working copy.
 */
/*public*/ /*static*/ void JUnitUtil::resetProfileManager() {
    try {
        Profile* profile = new NullProfile("TestProfile", "00000000", FileUtil::getFile(FileUtil::SETTINGS));
        resetProfileManager(profile);
    } catch (FileNotFoundException ex) {
        log->error(tr("Settings directory \"%1\" does not exist").arg(FileUtil::SETTINGS));
    }
    catch (IOException  ex) {
        log->error("Unable to create profile", ex);
    }
    catch ( IllegalArgumentException ex) {
        log->error("Unable to create profile", ex);
    }
}

/**
 * Use if the profile needs to be written to or cleared as part of the test.
 * Suggested use in the {@link org.junit.Before} annotated method is:      <code>
 *
 * @Rule
 * public org.junit.rules.TemporaryFolder folder = new org.junit.rules.TemporaryFolder();
 *
 * @Before
 * public void setUp() {
 *     resetProfileManager(new jmri.profile.NullProfile(folder.newFolder(jmri.profile.Profile.PROFILE)));
 * }
 * </code>
 *
 * @param profile the provided profile
 */
/*public*/ /*static*/ void JUnitUtil::resetProfileManager(Profile* profile) {
    ProfileManager::getDefault()->setActiveProfile(profile);
}

/**
 * PreferencesProviders retain per-profile objects; reset them to force that
 * information to be dumped.
 */
/*public*/ /*static*/ void JUnitUtil::resetPreferencesProviders() {
#if 0
    try {
        // reset UI provider
        Field providers = JmriUserInterfaceConfigurationProvider::getDeclaredField("PROVIDERS");
        providers.setAccessible(true);
        ((HashMap<?, ?>) providers.get(null)).clear();
        // reset XML storage provider
        providers = JmriConfigurationProvider.class.getDeclaredField("PROVIDERS");
        providers.setAccessible(true);
        ((HashMap<?, ?>) providers.get(null)).clear();
        // reset java.util.prefs.Preferences storage provider
        Field shared = JmriPreferencesProvider.class.getDeclaredField("SHARED_PROVIDERS");
        Field privat = JmriPreferencesProvider.class.getDeclaredField("/*private*/_PROVIDERS");
        shared.setAccessible(true);
        ((HashMap<?, ?>) shared.get(null)).clear();
        privat.setAccessible(true);
        ((HashMap<?, ?>) privat.get(null)).clear();
    } catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException ex) {
        log.error("Unable to reset preferences providers", ex);
    }
#endif
}
#if 0
/**
 * Silences the outputs from the Jemmy GUI Test framework.
 */
/*public*/ static void silenceGUITestOutput() {
    JUnitUtil.setGUITestOutput(TestOut.getNullOutput());
}

/**
 * Sets the outputs for the Jemmy GUI Test framework to the defaults. Call
 * this after setting up logging to enable outputs for a specific test.
 */
/*public*/ static void verboseGUITestOutput() {
    JUnitUtil.setGUITestOutput(new TestOut());
}

/**
 * Set the outputs for the Jemmy GUI Test framework.
 *
 * @param output a container for the input, output, and error streams
 */
/*public*/ static void setGUITestOutput(TestOut output) {
    org.netbeans.jemmy.JemmyProperties.setCurrentOutput(output);
}
#endif
/**
 * Service method to find the test class name in the traceback. Heuristic:
 * First jmri or apps class that isn't this one.
 * @return String class name
 */
/*static*/ QString JUnitUtil::getTestClassName() {
#if 0
    StackTraceElement[] trace = Thread.currentThread().getStackTrace();

    for (StackTraceElement e : trace) {
        String name = e.getClassName();
        if (name.startsWith("jmri") || name.startsWith("apps")) {
            if (!name.endsWith("JUnitUtil")) {
                return name;
            }
        }
    }
#endif
    return testClassName;
}
/*static*/ QString JUnitUtil::testClassName = "";

/**
 * Dispose of any disposable windows. This should only be used if there is
 * no ability to actually close windows opened by a test using
 * {@link #dispose(java.awt.Window)} or
 * {@link #disposeFrame(java.lang.String, bool, bool)}, since this may
 * mask other side effects that should be dealt with explicitly.
 *
 * @param warn  log a warning for each window if true
 * @param error log an error (failing the test) for each window if true
 */
/*public*/ /*static*/ void JUnitUtil::resetWindows(bool warn, bool error) {
    // close any open remaining windows from earlier tests
    for (QWidget* frame : QApplication::topLevelWidgets())
    {
      if(frame->windowTitle() == "PanelPro")
       continue; // don't close this app!
//        if (frame.isDisplayable()) {
//            if (frame.getClass().getName().equals("javax.swing.SwingUtilities$SharedOwnerFrame")) {
//                String message = "Cleaning up nameless invisible frame created by creating a dialog with a null parent in {}.";
//                if (error) {
//                    log.error(message, getTestClassName());
//                } else if (warn) {
//                    log.warn(message, getTestClassName());
//                }
//            } else
     {
       QString message = tr("Cleaning up frame \"%1\" (a %2) in %3.").arg(frame->windowTitle()).arg(frame->metaObject()->className()).arg(getTestClassName());
       if (error) {
           log->error(message);
       } else if (warn) {
           log->warn(message);
       }
       else
       {
        if(log->isDebugEnabled())
         log->debug(message);
       }
       if(qobject_cast<QMainWindow*>(frame))
        JUnitUtil::dispose(frame);
     }
    }
#if 0
    for (Window window : Window.getWindows()) {
        if (window.isDisplayable()) {
            if (window.getClass().getName().equals("javax.swing.SwingUtilities$SharedOwnerFrame")) {
                String message = "Cleaning up nameless invisible window created by creating a dialog with a null parent in {}.";
                if (error) {
                    log.error(message, getTestClassName());
                } else if (warn) {
                    log.warn(message, getTestClassName());
                }
            } else {
                String message = "Cleaning up window \"{}\" (a {}) in {}.";
                if (error) {
                    log.error(message, window.getName(), window.getClass(), getTestClassName());
                } else if (warn) {
                    log.warn(message, window.getName(), window.getClass(), getTestClassName());
                }
            }
            JUnitUtil.dispose(window);
        }
    }
#endif
}

#if 0
/**
 * Dispose of a visible frame searched for by title. Disposes of the first
 * visible frame found with the given title. Asserts that the calling test
 * failed if the frame cannot be found.
 *
 * @param title the title of the frame to dispose of
 * @param ce    true to match title param as a substring of the frame's
 *              title; false to require an exact match
 * @param cc    true if search is case sensitive; false otherwise
 */
/*public*/ static void disposeFrame(QString title, bool ce, bool cc) {
    Frame frame = FrameWaiter.getFrame(title, ce, cc);
    if (frame != null) {
        JUnitUtil.dispose(frame);
    } else {
        Assert.fail("Unable to find frame \"" + title + "\" to dispose.", __FILE__, __LINE__);
    }
}
#endif
/**
 * Dispose of a window. Disposes of the window on the GUI thread, returning
 * only after the window is disposed of.
 *
 * @param window the window to dispose of
 */
/*public*/ /*static*/ void JUnitUtil::dispose(/*@Nonnull*/ QWidget* window) {
    //java.util.Objects.requireNonNull(window, "Window cannot be null");

//    ThreadingUtil.runOnGUI(() -> {
//        window.dispose();
//    });
 window->close();
}
#if 0
/*public*/ static Thread getThreadByName(String threadName) {
    for (Thread t : Thread.getAllStackTraces().keySet()) {
        if (t.getName().equals(threadName)) return t;
    }
    return null;
}

/*public*/ static Thread getThreadStartsWithName(String threadName) {
    for (Thread t : Thread.getAllStackTraces().keySet()) {
        if (t.getName().startsWith(threadName)) return t;
    }
    return null;
}

static SortedSet<String> threadNames = new TreeSet<>(Arrays.asList(new String[]{
    // names we know about from normal running
    "main",
    "Java2D Disposer",
    "AWT-Shutdown",
    "AWT-EventQueue",
    "GC Daemon",
    "Finalizer",
    "Reference Handler",
    "Signal Dispatcher",                // POSIX signals in JRE
    "Java2D Queue Flusher",
    "Time-limited test",
    "WindowMonitor-DispatchThread",
    "RMI Reaper",
    "RMI TCP Accept",
    "TimerQueue",
    "Java Sound Event Dispatcher",
    "Aqua L&F",                         // macOS
    "AppKit Thread",
    "JMRI Common Timer",
    "BluecoveAsynchronousShutdownThread", // from LocoNet BlueTooth implementation
    "Keep-Alive-Timer",                 // from "system" group
    "process reaper"                    // observed in macOS JRE
}));
static List<Thread> threadsSeen = new ArrayList<>();

/**
 * Do a diagnostic check of threads,
 * providing a traceback if any new ones are still around.
 * <p>
 * First implementation is rather simplistic.
 */
static void checkThreads() {
    // now check for extra threads
    threadCount = 0;
    Thread.getAllStackTraces().keySet().forEach((t) ->
        {
            if (threadsSeen.contains(t)) return;
            if (t.getState() == Thread.State.TERMINATED) return; // going away, just not cleaned up yet
            String name = t.getName();
            if (! (threadNames.contains(name)
                 || name.startsWith("RMI TCP Accept")
                 || name.startsWith("AWT-EventQueue")
                 || name.startsWith("Aqua L&F")
                 || name.startsWith("Image Fetcher ")
                 || name.startsWith("JmDNS(")
                 || name.startsWith("SocketListener(")
                 || name.startsWith("SocketListener(")
                 || (name.startsWith("SwingWorker-pool-1-thread-") &&
                        ( t.getThreadGroup() != null &&
                            (t.getThreadGroup().getName().contains("FailOnTimeoutGroup") || t.getThreadGroup().getName().contains("main") )
                        )
                    )
                )) {

                    // if still running, wait to see if being terminated

                    threadCount++;
                    threadsSeen.add(t);

                    // for anonymous threads, show the traceback in hopes of finding what it is
                    if (name.startsWith("Thread-")) {
                        Exception ex = new Exception("traceback of numbered thread");
                        ex.setStackTrace(Thread.getAllStackTraces().get(t));
                        log.warn("Found remnant thread \"{}\" in group \"{}\" after {}", t.getName(), (t.getThreadGroup() != null ? t.getThreadGroup().getName() : "<no group>"), getTestClassName(), ex);
                    } else {
                        log.warn("Found remnant thread \"{}\" in group \"{}\" after {}", t.getName(), (t.getThreadGroup() != null ? t.getThreadGroup().getName() : "<no group>"), getTestClassName());
                    }
            }
        });
}

/* Global Panel operations */
/**
 * Close all panels associated with the {@link EditorManager} default
 * instance.
 */
/*public*/ static void closeAllPanels() {
    EditorManager manager = InstanceManager::getNullableDefault(EditorManager.class);
    if (manager != null) {
        for (Editor e : manager.getEditorsList()) {
            new EditorFrameOperator(e).closeFrameWithConfirmations();
        }
    }
}

/* GraphicsEnvironment utility methods */

/**
 * Get the content pane of a dialog.
 *
 * @param title the dialog title
 * @return the content pane
 */
/*public*/ static Container findContainer(String title) {
    return new JDialogOperator(title).getContentPane();
}

/**
 * Press a button after finding it in a container by title.
 *
 * @param clazz an object no longer used
 * @param frame container containing button to press
 * @param text button title
 * @return the pressed button
 * @deprecated use {@link #pressButton(Container, String)} instead
 */
@Deprecated // for removal after 4.18
/*public*/ static AbstractButton pressButton(SwingTestCase clazz, Container frame, String text) {
    return pressButton(frame, text);
}

/**
 * Press a button after finding it in a container by title.
 *
 * @param frame container containing button to press
 * @param text button title
 * @return the pressed button
 */
/*public*/ static AbstractButton pressButton(Container frame, String text) {
    AbstractButton button = JButtonOperator.findAbstractButton(frame, text, true, true);
    Assert.assertNotNull(text + " Button not found", button);
    AbstractButtonOperator abo = new AbstractButtonOperator(button);
    abo.doClick();
    return button;
}
#endif

/*public*/ /*static*/ void JUnitUtil::runTests(QObject* test, QStringList testList)
{
 try
 {
  foreach(QString testName, testList)
  {
   testClassName = testName;
   log->info(tr("begin '%1'").arg(testName));
   if(!QMetaObject::invokeMethod(test, "setUp", Qt::DirectConnection))
    throw Exception(tr("can't invoke 'setup' method when running test '%1").arg(testName));
   if(!QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection))
    throw Exception(tr("can't invoke '%1' method when running test ").arg(testName));
   log->info(tr("end '%1'").arg(testName));
   if(!QMetaObject::invokeMethod(test, "tearDown", Qt::DirectConnection))
    throw Exception(tr("can't invoke 'tearDown' method when running test '%1").arg(testName));
  }
  log->info(tr("Tests complete!"));
 }
 catch(Exception ex)
 {
  JOptionPane::showMessageDialog(nullptr, tr("Unhandled exception while running test '%1'\n%2")
     .arg(testClassName).arg(ex.getMessage()), "Unhandled Exception",  JOptionPane::WARNING_MESSAGE);
 }
}
/*private*/ /*final*/ /*static*/ Logger* JUnitUtil::log = LoggerFactory::getLogger("JUnitUtil");


