#ifndef STRINGEXPRESSIONFACTORY_H
#define STRINGEXPRESSIONFACTORY_H
#include <QtCore>
#include "category.h"

/**
 * Factory class for StringExpressionBean classes.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*interface*/class StringExpressionFactory {
public:
    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/ virtual void init() {}

    /**
     * Get a set of classes that implements the StringExpression interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet<QHash<Category*, /*Class<? extends Base>*/QString>> getClasses()=0;

};
Q_DECLARE_INTERFACE(StringExpressionFactory, "StringExpressionFactory")
#endif // STRINGEXPRESSIONFACTORY_H
