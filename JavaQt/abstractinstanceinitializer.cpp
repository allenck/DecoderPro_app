#include "abstractinstanceinitializer.h"

AbstractInstanceInitializer::AbstractInstanceInitializer()
{

}
// /*public*/ class AbstractInstanceInitializer implements InstanceInitializer {

/**
 * The default implementation always throws an IllegalArgumentException. If
 * called by an overriding method, the last line of the overriding method
 * should be {@code return super.getDefault(type);}.
 *
 * {@inheritDoc }
 */
//@Override
/*public*/ /*<T>*/ QObject* AbstractInstanceInitializer::getDefault(/*Class<T>*/QString type) const throw (IllegalArgumentException) {
    throw /*new*/ IllegalArgumentException();
}

/**
 * The default implementation returns an empty set.
 *
 * {@inheritDoc }
 */
//@Override
/*public*/ QSet</*Class<?>*/QString> AbstractInstanceInitializer::getInitalizes() {
    return QSet<QString>();
}


