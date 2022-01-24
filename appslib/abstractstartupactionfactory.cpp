#include "abstractstartupactionfactory.h"

AbstractStartupActionFactory::AbstractStartupActionFactory(QObject* parent)
 : QObject(parent)
{

}
/**
 * Abstract implementation of {@link apps.startup.StartupActionFactory} that
 * covers some boilerplate code for most implementations.
 *
 * @author Randall Wood (C) 2016
 */
//abstract /*public*/ class AbstractStartupActionFactory implements StartupActionFactory {

/**
 * {@inheritDoc}
 *
 * This implementation calls
 * {@link #getTitle(java.lang.Class, java.util.Locale)} with the default
 * locale.
 *
 * @param clazz the class
 * @return the title
 * @throws IllegalArgumentException if the class is not supported by this
 *                                  factory
 */
//@Override
/*public*/ QString AbstractStartupActionFactory::getTitle(/*Class<?>*/QString clazz) throw (IllegalArgumentException) {
 QLocale locale = QLocale();
    return StartupActionFactory::getTitle(clazz, locale);
}

/**
 * {@inheritDoc}
 *
 * This implementation returns an empty array.
 *
 * @param clazz the class
 * @return an empty array
 * @throws IllegalArgumentException if the class is not supported by this
 *                                  factory
 */
//@Override
/*public*/ QStringList AbstractStartupActionFactory::getOverriddenClasses(/*Class<?>*/QString clazz) throw (IllegalArgumentException) {
    return QStringList();
}
