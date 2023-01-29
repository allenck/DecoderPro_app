#ifndef STRINGACTIONFACTORY_H
#define STRINGACTIONFACTORY_H
#include "base.h"
/**
 * Factory class for StringActionBean classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class StringActionFactory {
 public:
    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/virtual  void init() {}

    /**
     * Get a set of classes that implements the StringActionBean interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet<QHash<Category, /*Class<? extends Base>*/QString>> getClasses() =0;

};
Q_DECLARE_INTERFACE(StringActionFactory, "StringActionFactory")
#endif // STRINGACTIONFACTORY_H
