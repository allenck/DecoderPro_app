#ifndef DIGITALACTIONFACTORY_H
#define DIGITALACTIONFACTORY_H
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
    /*public*/ QSet<Map.Entry<Category, Class<? extends DigitalActionBean>>> getActionClasses();

};

#endif // DIGITALACTIONFACTORY_H
