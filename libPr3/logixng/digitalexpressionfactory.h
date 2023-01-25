#ifndef DIGITALEXPRESSIONFACTORY_H
#define DIGITALEXPRESSIONFACTORY_H
#include <QtCore>

class Category;
/**
 * Factory class for DigitalExpressionBean classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalExpressionFactory {
public:
    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/ virtual void init() {}

    /**
     * Get a set of classes that implements the DigitalExpressionBean interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet<QHash<Category, /*Class<? extends DigitalExpressionBean>*/QString>> getExpressionClasses()=0;

};
Q_DECLARE_INTERFACE(DigitalExpressionFactory, "DigitalExpressionFactory")
#endif // DIGITALEXPRESSIONFACTORY_H
