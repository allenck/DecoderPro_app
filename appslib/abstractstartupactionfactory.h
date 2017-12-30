#ifndef ABSTRACTSTARTUPACTIONFACTORY_H
#define ABSTRACTSTARTUPACTIONFACTORY_H
#include "startupactionfactory.h"

class AbstractStartupActionFactory : public StartupActionFactory
{
public:
 AbstractStartupActionFactory(QObject* parent = 0);
 /*public*/ virtual QString getTitle(/*Class<?>*/QString clazz) throw (IllegalArgumentException);
 /*public*/ virtual QStringList getOverriddenClasses(/*Class<?>*/QString clazz) throw (IllegalArgumentException);
};

#endif // ABSTRACTSTARTUPACTIONFACTORY_H
