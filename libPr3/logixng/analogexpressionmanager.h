#ifndef ANALOGEXPRESSIONMANAGER_H
#define ANALOGEXPRESSIONMANAGER_H
#include "maleanalogexpressionsocket.h"
#include "femaleanalogexpressionsocket.h"
#include "femalesocketlistener.h"

/**
 * Manager for Expression
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/class AnalogExpressionManager : public BaseManager/*<MaleAnalogExpressionSocket>*/ {

 public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleAnalogExpressionSocket for the action.
     *
     * @param expression the bean
     * @return the male socket for this expression
     * @throws IllegalArgumentException if the expression has an invalid system name
     */
    /*public*/ virtual MaleAnalogExpressionSocket* registerExpression(/*@Nonnull*/ AnalogExpressionBean* expression)
            /*throws IllegalArgumentException*/=0;

    /**
     * Create a new system name for an Expression.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /**
     * Create a female socket for analog expressions
     * @param parent the parent that will own the new female socket
     * @param listener the listener for the female socket
     * @param socketName the name of the new socket
     * @return the new female socket
     */
    /*public*/ virtual FemaleAnalogExpressionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName)=0;

    /**
     * Get a set of classes that implements the DigitalAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QMap<Category*, QList</*Class<? extends Base>*/Base*>> getExpressionClasses()=0;

    /*.*
     * Add an Expression.
     *
     * @param expression the expression to add
     * @throws IllegalArgumentException if the expression has an invalid system name
     */
//    public void addExpression(Expression expression)
//            throws IllegalArgumentException;

    /*.*
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
//    public Expression getExpression(String name);

//    public Expression getByUserName(String s);

//    public Expression getBySystemName(String s);

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the AnalogExpressionManager is
     * {@link #getSystemNamePrefix() } and "AE";
     */
    //@Override
    /*public*/ virtual /*default*/ QString getSubSystemNamePrefix() {
        return getSystemNamePrefix() + "AE";
    }

    /**
     * Delete Expression by removing it from the manager. The Expression must
     * first be deactivated so it stops processing.
     *
     * @param x the Expression to delete
     */
    /*public*/ void deleteAnalogExpression(MaleAnalogExpressionSocket* x);

};

#endif // ANALOGEXPRESSIONMANAGER_H
