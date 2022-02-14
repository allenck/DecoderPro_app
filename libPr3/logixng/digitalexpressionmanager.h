#ifndef DIGITALEXPRESSIONMANAGER_H
#define DIGITALEXPRESSIONMANAGER_H
#include "maledigitalexpressionsocket.h"
#include "basemanager.h"
#include "femaledigitalexpressionsocket.h"
#include "femalesocketlistener.h"
/**
 * Manager for DigitalExpressionBean
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/class  DigitalExpressionManager :public BaseManager/*<MaleDigitalExpressionSocket>*/ {
Q_INTERFACES(Manager)
 public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleActionSocket for the action.
     *
     * @param expression the bean
     * @return the male socket for this expression
     * @throws IllegalArgumentException if the expression has an invalid system name
     */
    /*public*/ virtual MaleDigitalExpressionSocket* registerExpression(/*@Nonnull*/ DigitalExpressionBean* expression)
            /*throws IllegalArgumentException*/=0;

    /**
     * Create a new system name for an DigitalExpressionBean.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /*public*/ virtual FemaleDigitalExpressionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName)=0;
/*
    public FemaleDigitalExpressionSocket createFemaleExpressionSocket(
            Base parent,
            FemaleSocketListener listener,
            String socketName,
            MaleDigitalExpressionSocket maleSocket);
*/
    /**
     * Get a set of classes that implements the DigitalAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QMap<Category::TYPE, QList</*Class<? extends Base>*/QString> > getExpressionClasses()=0;

    /*.*
     * Add an DigitalExpressionBean.
     *
     * @param expression the expression to add
     * @throws IllegalArgumentException if the expression has an invalid system name
     */
//    public void addExpression(DigitalExpressionBean expression)
//            throws IllegalArgumentException;

    /*.*
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
//    public DigitalExpressionBean getExpression(String name);

//    public DigitalExpressionBean getByUserName(String s);

//    public DigitalExpressionBean getBySystemName(String s);

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the DigitalExpressionManager is
     * {@link #getSystemNamePrefix() } and "DE";
     */
    //@Override
    /*default*/ /*public*/ virtual QString getSubSystemNamePrefix() {
        return getSystemNamePrefix() + "DE";
    }

    /**
     * Delete DigitalExpression by removing it from the manager. The Expression must
     * first be deactivated so it stops processing.
     *
     * @param x the DigitalExpression to delete
     */
    public void deleteDigitalExpression(MaleDigitalExpressionSocket x);

};
#endif // DIGITALEXPRESSIONMANAGER_H
