#ifndef STACK_H
#define STACK_H
#include <QObject>

/**
 * A table that is a stack
 *
 * @author Daniel Bergqvist 2020
 */
/*public*/ /*interface*/class Stack {
    public:
    /**
     * Pushes a value on the top of the stack so the stack grow.
     * @param value the value to push to the stack
     */
    /*public*/ virtual void push(QObject* value)=0;

    /**
     * Pops the topmost value off the top of the stack so the stack shrinks.
     * @return the value that is on the top of the stack
     */
    /*public*/ virtual QObject* pop()=0;

    /**
     * Get the value at an index
     * @param index the index from bottom of the table
     * @return value the new value
     */
    /*public*/ virtual QObject getValueAtIndex(int index)=0;

    /**
     * Set the value at an index
     * @param index the index from bottom of the table
     * @param value the new value
     */
    /*public*/ virtual void setValueAtIndex(int index, QObject* value)=0;

    /**
     * Get the number of items on the stack
     * @return the number of items
     */
    /*public*/ virtual int getCount()=0;

    /**
     * Reset the number of items on the stack.
     * This is used when parameters are put on the stack before a call to a
     * module and those parameters needs to be removed when the module returns.
     * The new count must be less than or equal to the current number of items.
     * @param newCount the new number of items
     */
    /*public*/ virtual void setCount(int newCount)=0;

};
Q_DECLARE_INTERFACE(Stack, "Stack")
#endif // STACK_H
