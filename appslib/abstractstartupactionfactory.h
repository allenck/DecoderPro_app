#ifndef ABSTRACTSTARTUPACTIONFACTORY_H
#define ABSTRACTSTARTUPACTIONFACTORY_H
#include "startupactionfactory.h"

class AbstractStartupActionFactory : public QObject, public StartupActionFactory
{
  Q_OBJECT
  Q_INTERFACES(StartupActionFactory)
public:
 AbstractStartupActionFactory(QObject* parent = 0);
 /*public*/ virtual QString getTitle(/*Class<?>*/QString clazz) throw (IllegalArgumentException);
 /*public*/ virtual QStringList getOverriddenClasses(/*Class<?>*/QString clazz) throw (IllegalArgumentException);

 QObject* self() override {return (QObject*)this;}

};

#endif // ABSTRACTSTARTUPACTIONFACTORY_H
