#ifndef ANALOGEXPRESSIONFACTORY_H
#define ANALOGEXPRESSIONFACTORY_H
#include "category.h"

/**
 * Factory class for AnalogExpressionBean classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogExpressionFactory {

    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/ virtual void init() {}

    /**
     * Get a set of classes that implements the AnalogExpression interface.
     *
     * @return a set of entries with category and class
     */
//    /*public*/ Set<Map.Entry<Category, Class<? extends Base>>> getClasses();
     /*public*/ virtual QSet<QString> getClasses()=0;
};
#endif // ANALOGEXPRESSIONFACTORY_H
