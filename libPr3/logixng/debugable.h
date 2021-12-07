#ifndef DEBUGABLE_H
#define DEBUGABLE_H
#include "base.h"

/**
 * Debug configuration for this male socket.
 * <P>
 * In some cases, it may be desirable to be able to execute the LogixNG
 * without fully working agains the layout. For example, when developing
 * a LogixNG for a club layout, it may be desirable to be able to run the
 * LogixNG without affecting turnouts on the layout while testing the
 * LogixNG.
 */
/*public*/ /*interface*/class DebugConfig {
    public:
    /*public*/ DebugConfig* getCopy();

};
Q_DECLARE_INTERFACE(DebugConfig, "DebugConfig")

/**
 * A LogixNG item that is debugable.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*interface*/class Debugable : public Base {
  Q_INTERFACES(Base)
public:
    /**
     * Set the debug configuration for this male socket.
     * <P>
     * Each implementation of MaleSocket has their own implementation of
     * DebugConfig. Use reflection to get the proper class
     * &lt;package-name&gt;.debug.&lt;ClassName&gt;Debug that returns a JPanel
     * that can configure debugging for this male socket.
     *
     * @param config the new configuration or null to turn off debugging
     */
    /*public*/ virtual void setDebugConfig(DebugConfig* config)=0;

    /**
     * Get the debug configuration for this male socket.
     *
     * @return the configuration or null if debugging is turned off for this male socket
     */
    /*public*/ virtual DebugConfig* getDebugConfig()=0;

    /**
     * Create a debug configuration for this male socket.
     *
     * @return the new configuration
     */
    /*public*/ virtual DebugConfig* createDebugConfig()=0;

};
Q_DECLARE_INTERFACE(Debugable, "Debugable")
#endif // DEBUGABLE_H
