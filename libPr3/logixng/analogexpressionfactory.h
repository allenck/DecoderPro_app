#ifndef ANALOGEXPRESSIONFACTORY_H
#define ANALOGEXPRESSIONFACTORY_H
#include "category.h"

class Base;
/**
 * Factory class for AnalogExpressionBean classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogExpressionFactory {
public:
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
     /*public*/ virtual const QSet<QMap<Category*, QString> >getClasses()=0;
  virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(AnalogExpressionFactory, "AnalogExpressionFactory")
#endif // ANALOGEXPRESSIONFACTORY_H
