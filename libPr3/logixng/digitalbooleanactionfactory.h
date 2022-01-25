#ifndef DIGITALBOOLEANACTIONFACTORY_H
#define DIGITALBOOLEANACTIONFACTORY_H
#include <QSet>
#include <QtCore>
/**
 * Factory class for DigitalBooleanAction classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalBooleanActionFactory {

    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/virtual void init() {}

    /**
     * Get a set of classes that implements the DigitalBooleanAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ QSet<Map.Entry<Category, Class<? extends Base>>> getClasses();

};
Q_DECLARE_INTERFACE(DigitalBooleanActionFactory, "DigitalBooleanActionFactory")
#endif // DIGITALBOOLEANACTIONFACTORY_H
