#ifndef RESTARTSTARTUPACTIONFACTORY_H
#define RESTARTSTARTUPACTIONFACTORY_H
#include "abstractstartupactionfactory.h"

class RestartStartupActionFactory : public AbstractStartupActionFactory
{
 Q_OBJECT
public:
 RestartStartupActionFactory(QObject* parent = 0);
 ~RestartStartupActionFactory() {}
 RestartStartupActionFactory(const RestartStartupActionFactory&) : AbstractStartupActionFactory() {}
 /*public*/ QString getTitle(/*Class<?> */QString clazz, QLocale locale) throw (IllegalArgumentException) ;
 /*public*/ QStringList getActionClasses();
 QObject* self() override {return (QObject*)this;}

};
Q_DECLARE_METATYPE(RestartStartupActionFactory)
#endif // RESTARTSTARTUPACTIONFACTORY_H
