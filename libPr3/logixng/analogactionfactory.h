#ifndef ANALOGACTIONFACTORY_H
#define ANALOGACTIONFACTORY_H
#include "category.h"
/**
 * Factory class for AnalogAction classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogActionFactory {

 public:
    /**
     * Init the factory, for example create categories.
     */
    /*public*/virtual /*default*/ void init() {}

    /**
     * Get a set of classes that implements the AnalogAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet</*Map.Entry<Category, Class<? extends Base>>*/QString > getClasses()=0;

};

#endif // ANALOGACTIONFACTORY_H
