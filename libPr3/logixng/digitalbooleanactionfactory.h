#ifndef DIGITALBOOLEANACTIONFACTORY_H
#define DIGITALBOOLEANACTIONFACTORY_H
#include <QSet>
#include <QtCore>

class Category;
/**
 * Factory class for DigitalBooleanAction classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalBooleanActionFactory {
public:
    /**
     * Init the factory, for example create categories.
     */
    /*public*/ /*default*/virtual void init() {}

    /**
     * Get a set of classes that implements the DigitalBooleanAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QSet<QHash<Category, /*Class<? extends Base>*/QString>> getClasses()=0;

};
Q_DECLARE_INTERFACE(DigitalBooleanActionFactory, "DigitalBooleanActionFactory")
#endif // DIGITALBOOLEANACTIONFACTORY_H
