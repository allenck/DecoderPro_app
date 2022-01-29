#ifndef DIGITALACTIONFACTORY_H
#define DIGITALACTIONFACTORY_H
#include "category.h"

/**
 * Factory class for DigitalAction classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/ class DigitalActionFactory {

    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/ virtual void init() {}

    /**
     * Get a set of classes that implements the DigitalAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet</*Map.Entry<Category, Class<? extends DigitalActionBean>>*/QString> getActionClasses()=0;

};

#endif // DIGITALACTIONFACTORY_H
