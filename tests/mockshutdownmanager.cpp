#include "mockshutdownmanager.h"

/**
 * Mock ShutDownManager for unit testing.
 * <p>
 * To clear the state of shutting down, call
 * {@link #resetShuttingDown()}.
 * <p>
 * This overrides the DefaultShutDownManager with two changes to that manager's behavior:
 * <ul>
 * <li>This does not register a shutdown hook with the Runtime to catch SIGTERM, Ctrl-C, and the like.</li>
 * <li>This does not call System.exit() when {@link #shutdown()} or {@link #restart()} are called.</li>
 * </ul>
 *
 * @author Randall Wood Copyright 2019
 */
///*public*/ class MockShutDownManager extends DefaultShutDownManager {

    /*public*/ MockShutDownManager::MockShutDownManager(QObject *parent) {
        //super();
        //        Runtime.getRuntime().removeShutdownHook(shutdownHook);
    }

    /**
     * {@inheritDoc}
     *
     * This implementation runs all shutdown tasks, but does not actually call
     * System.exit().
     */
    //@Overide
    /*public*/ bool MockShutDownManager::restart() {
        return DefaultShutDownManager::shutdown(0, false);
    }

    /**
     * {@inheritDoc}
     *
     * This implementation runs all shutdown tasks, but does not actually call
     * System.exit().
     */
    //@Overide
    /*public*/ bool MockShutDownManager::shutdown() {
        return DefaultShutDownManager::shutdown(100, false);
    }

    /*public*/ void MockShutDownManager::resetShuttingDown() {
        setShuttingDown(false);
    }
