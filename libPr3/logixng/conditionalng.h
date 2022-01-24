#ifndef CONDITIONALNG_H
#define CONDITIONALNG_H
#include "base.h"
#include "stack.h"
#include "symboltable.h"
#include "namedbean.h"

class FemaleDigitalActionSocket;
class LogixNG_Thread;
/**
 * ConditionalNG.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*interface*/class ConditionalNG /*extends*/ : public Base, public NamedBean {
 Q_INTERFACES(Base NamedBean)
    /**
     * Get the thread that this conditionalNG executes on.
     * @return the thread
     */
    /*public*/ virtual  LogixNG_Thread* getCurrentThread()=0;

    /**
     * Get the thread id that this conditionalNG should execute on when JMRI
     * starts next time.
     * It's not currently possible to move a ConditionalNG from one thread to
     * another without restarting JMRI.
     * @return the thread ID
     */
    /*public*/ virtual  int getStartupThreadId()=0;

    /**
     * Set the thread id that this conditionalNG should execute on when JMRI
     * starts next time.
     * It's not currently possible to move a ConditionalNG from one thread to
     * another without restarting JMRI.
     * @param threadId the thread ID
     */
    /*public*/ virtual  void setStartupThreadId(int threadId)=0;

    /**
     * Get the female socket of this ConditionalNG.
     * @return the female socket
     */
    /*public*/ virtual  FemaleDigitalActionSocket* getFemaleSocket()=0;

    /**
     * Set whenether this ConditionalNG is enabled or disabled.
     * <P>
     * This method must call registerListeners() / unregisterListeners().
     *
     * @param enable true if this ConditionalNG should be enabled, false otherwise
     */
    /*public*/ virtual  void setEnabled(bool enable)=0;

    /**
     * Determines whether this ConditionalNG is enabled.
     *
     * @return true if the ConditionalNG is enabled, false otherwise
     */
    //@Override
    /*public*/ virtual  bool isEnabled()=0;

    /**
     * Set whenether execute() should run on the LogixNG thread at once or
     * should dispatch the call until later.
     * Most tests turns off the delay to simplify the tests.
     *
     * @param value true if execute() should run on LogixNG thread delayed,
     *              false otherwise.
     */
    /*public*/ virtual  void setRunDelayed(bool value)=0;

    /**
     * Get whenether execute() should run on the LogixNG thread at once or
     * should dispatch the call until later.
     * Most tests turns off the delay to simplify the tests.
     * @return true if execute() should run on LogixNG thread delayed,
     * false otherwise.
     */
    /*public*/ virtual  bool getRunDelayed()=0;

    /**
     * Execute the ConditionalNG.
     */
    /*public*/ virtual  void execute()=0;

    /**
     * Execute the ConditionalNG.
     * @param allowRunDelayed true if it's ok to run delayed, false otherwise
     */
    /*public*/ virtual  void execute(bool allowRunDelayed)=0;

    /**
     * Execute the female socket.
     * @param socket the female socket
     */
    /*public*/ virtual  void execute(FemaleDigitalActionSocket* socket)=0;

    /**
     * Get the stack
     * @return the stack
     */
    /*public*/ virtual  Stack* getStack()=0;

    /**
     * Get the current symbol table
     * @return the symbol table
     */
    /*public*/ virtual  SymbolTable* getSymbolTable()=0;

    /**
     * Set the current symbol table
     * @param symbolTable the symbol table
     */
    /*public*/ virtual  void setSymbolTable(SymbolTable* symbolTable)=0;

};
#endif // CONDITIONALNG_H
