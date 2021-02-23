#ifndef INSTANCEMANAGERAUTOINITIALIZE_H
#define INSTANCEMANAGERAUTOINITIALIZE_H
#include <QObject>

/**
 * Provide a hint to the {@link jmri.InstanceManager} that this object needs
 * have additional initialization performed after the InstanceManager initially
 * creates it.  This allows two classes that have circular dependencies on
 * being able to get the default instance of each other to be managed
 * successfully.
 * <p>
 * More specifically, the constructors or code called by the constructors
 * of classes implementing the {@link InstanceManagerAutoDefault} interface
 * (i.e. that have the InstanceManager automatically
 * create their objects) should never ask the InstanceManager for reference to other
 * automatically-created types. They may ask the InstanceManager for references in their
 * {@link #initialize()} method, but they can only store those; they can't assume
 * that the objects referred to have completed their initialization and are operational.
 * See the diagram below for why.
 * <p>
 * Note: the need to have a class implement this probably is indicative of other
 * design issues in the implementing class and its dependencies.
 * <p>
 * <img src="doc-files/InstanceManagerAutoInitialize-Sequence.png" alt="Initialization sequence UML diagram">
 *
 * @author Randall Wood Copyright 2017
 */
/*public*/ class InstanceManagerAutoInitialize
{
//Q_OBJECT
public:
    /**
     * Perform any initialization that occurs after this object has been
     * constructed and made available by the InstanceManager.
     */
 /*public*/ virtual void initialize() =0;

};
Q_DECLARE_INTERFACE(InstanceManagerAutoInitialize, "InstanceManagerAutoInitialize")
#endif // INSTANCEMANAGERAUTOINITIALIZE_H
