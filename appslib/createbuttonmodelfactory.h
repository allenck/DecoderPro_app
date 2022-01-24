#ifndef CREATEBUTTONMODELFACTORY_H
#define CREATEBUTTONMODELFACTORY_H
#include "abstractactionmodelfactory.h"

class CreateButtonModel;
class CreateButtonModelFactory : public AbstractActionModelFactory
{
 Q_OBJECT
public:
 CreateButtonModelFactory();
 ~CreateButtonModelFactory() {}
 CreateButtonModelFactory(const CreateButtonModelFactory&) : AbstractActionModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass()override;
 /*public*/ StartupModel* newModel()override;
 /*public*/ QString getEditModelMessage()override;
 /*public*/ QString getDescription()override;

 QObject* self() override {return (QObject*)this;}

};
Q_DECLARE_METATYPE(CreateButtonModelFactory)
#endif // CREATEBUTTONMODELFACTORY_H
