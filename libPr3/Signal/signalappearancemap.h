#ifndef SIGNALAPPEARANCEMAP_H
#define SIGNALAPPEARANCEMAP_H
#include <QString>
#include <QList>
#include "signalsystem.h"
#include <QVector>
#include <QStringList>
#include "abstractnamedbean.h"
/**
 * Access to signal appearance information.
 * <p>
 * Maps to an appearance* file in a signal system.
 *
 * This interface does not provide any methods to change the map.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @version     $Revision: 20084 $
 */
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalAppearanceMap  : public AbstractNamedBean
{
public:
    SignalAppearanceMap(QString systemName="", QString userName="") :AbstractNamedBean(systemName, userName, NULL) {}
    /**
     * Check if an aspect can be displayed by this particular Map
     */
    /*public*/ virtual bool checkAspect(QString aspect) = 0;
    
    /**
     * Get all available aspect names
     */
//    /*public*/ java.util.Enumeration<QString> getAspects() = 0;
    virtual QStringListIterator getAspects() = 0;
    
    /**
     * Get the associated signal system and the common information
     * it contains
     */
    /*public*/ virtual SignalSystem* getSignalSystem() = 0;
    
    /**
     * Get a property associated with a specific aspect
     */
    /*public*/ virtual QString getProperty(QString aspect, QString key) = 0;
    
    /**
     * Get an Image Link associated with a specific aspect and type
     */
    /*public*/ virtual QString getImageLink(QString aspect, QString key) = 0;
    
    /**
     * Return a list of valid icon sets
     */
    /*public*/ virtual QVector<QString> getImageTypes(QString aspect) = 0;
    
    /**
     * Return an aspect for a specific appearance
     */
    /*public*/ virtual QString getSpecificAppearance(int appearance) = 0;
    
    /**
     * Constant representing the "held" apsect for a signal
     */
    /*public*/ /*final*/ static const int HELD = 0;
    
    /**
     * Constant representing the "permissive" apsect for a signal
     */
    /*public*/ /*final*/ static const int PERMISSIVE = 1;
    
    /**
     * Constant representing the "danager" apsect for a signal
     */
    /*public*/ /*final*/ static const int DANGER = 2;
    
    /**
     * Constant representing the "dark" apsect for a signal
     */
    /*public*/ /*final*/ static const int DARK = 3;
    
    /**
    * Returns a list of postential aspects that we could set the signalmast to
    * given the state of the advanced signal mast.
    */
    /*public*/ virtual QVector<QString> getValidAspectsForAdvancedAspect(QString advancedAspect) = 0;
friend class DefaultSignalMastLogic;
friend class DestinationMast;
};
#endif // SIGNALAPPEARANCEMAP_H
