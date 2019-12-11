#ifndef ROSTERFRAMESTARTUPACTIONFACTORY_H
#define ROSTERFRAMESTARTUPACTIONFACTORY_H
#include "abstractstartupactionfactory.h"

class RosterFrameStartupActionFactory : public AbstractStartupActionFactory
{
 Q_OBJECT
public:
 RosterFrameStartupActionFactory(QObject *parent= nullptr);
 /*public*/ QString getTitle(/*Class<?>*/QString clazz, QLocale locale) throw (IllegalArgumentException);
 /*public*/ /*Class<?>*/QStringList getActionClasses();

};

#endif // ROSTERFRAMESTARTUPACTIONFACTORY_H
