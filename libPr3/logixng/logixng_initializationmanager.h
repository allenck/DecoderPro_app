#ifndef LOGIXNG_INITIALIZATIONMANAGER_H
#define LOGIXNG_INITIALIZATIONMANAGER_H
#include "logixng.h"

/**
 * Manager for initialization of LogixNG.
 * This manager has a list of LogixNGs that will be executed before all other
 * LogixNGs are executed.
 *
 * @author Daniel Bergqvist   Copyright (C) 2021
 */
/*public*/ /*interface*/class LogixNG_InitializationManager {
    public:
    /**
     * Adds a LogixNG to the end of list.
     * @param logixNG the LogixNG
     */
    virtual void add(LogixNG* logixNG)=0;

    /**
     * Deletes a LogixNG from the list.
     * @param logixNG the LogixNG
     */
    virtual void _delete(LogixNG* logixNG)=0;

    /**
     * Deletes a LogixNG from the list.
     * @param index the index of the LogixNG to delete
     */
    virtual void _delete(int index)=0;

    /**
     * Moves the LogixNG up (higher priority)
     * @param index the index of the LogixNG to move up
     */
    virtual void moveUp(int index)=0;

    /**
     * Moves the LogixNG down (lower priority)
     * @param index the index of the LogixNG to move down
     */
    virtual void moveDown(int index)=0;

    /**
     * Returns an unmodifiable list of the initialization LogixNGs
     * @return the list
     */
    virtual QList<LogixNG*> getList()=0;

    /**
     * Print the tree to a stream.
     *
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     */
    /*public*/ virtual void printTree(QLocale locale, PrintWriter* writer, QString indent)=0;
};
Q_DECLARE_INTERFACE(LogixNG_InitializationManager, "LogixNG_InitializationManager")
#endif // LOGIXNG_INITIALIZATIONMANAGER_H
