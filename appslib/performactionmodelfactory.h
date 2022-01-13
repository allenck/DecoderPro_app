#ifndef PERFORMACTIONMODELFACTORY_H
#define PERFORMACTIONMODELFACTORY_H
#include "abstractactionmodelfactory.h"
#include "performactionmodel.h"
#include "class.h"

class PerformActionModelFactory : public AbstractActionModelFactory
{
 Q_OBJECT
public:
 Q_INVOKABLE/*public*/ PerformActionModelFactory() ;
 ~PerformActionModelFactory() {}
 PerformActionModelFactory(const PerformActionModelFactory&) : AbstractActionModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass()override;
 /*public*/ PerformActionModel* newModel()override;
 /*public*/ QString getEditModelMessage()override;
 /*public*/ QString getDescription()override;

 QObject* self() override {return (QObject*)this;}

};
Q_DECLARE_METATYPE(PerformActionModelFactory)
#endif // PERFORMACTIONMODELFACTORY_H
