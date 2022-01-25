#ifndef ANALOGACTIONFACTORY_H
#define ANALOGACTIONFACTORY_H
/**
 * Factory class for AnalogAction classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
public interface AnalogActionFactory {

    /**
     * Init the factory, for example create categories.
     */
    public default void init() {}

    /**
     * Get a set of classes that implements the AnalogAction interface.
     *
     * @return a set of entries with category and class
     */
    public Set<Map.Entry<Category, Class<? extends Base>>> getClasses();

}

#endif // ANALOGACTIONFACTORY_H
