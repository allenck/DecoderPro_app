#ifndef PERFORMACTIONMODELFACTORY_H
#define PERFORMACTIONMODELFACTORY_H
#include "abstractactionmodelfactory.h"
#include "performactionmodel.h"
#include "class.h"

class PerformActionModelFactory : public AbstractActionModelFactory
{
public:
 /*public*/ PerformActionModelFactory() ;
 ~PerformActionModelFactory() {}
 PerformActionModelFactory(const PerformActionModelFactory&) : AbstractActionModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ PerformActionModel* newModel();
 /*public*/ QString getEditModelMessage();
 /*public*/ QString getDescription();

};
Q_DECLARE_METATYPE(PerformActionModelFactory)
#endif // PERFORMACTIONMODELFACTORY_H
