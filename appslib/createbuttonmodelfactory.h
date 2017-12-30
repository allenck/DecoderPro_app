#ifndef CREATEBUTTONMODELFACTORY_H
#define CREATEBUTTONMODELFACTORY_H
#include "abstractactionmodelfactory.h"

class CreateButtonModel;
class CreateButtonModelFactory : public AbstractActionModelFactory
{
public:
 CreateButtonModelFactory();
 ~CreateButtonModelFactory() {}
 CreateButtonModelFactory(const CreateButtonModelFactory&) : AbstractActionModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass() ;
 /*public*/ StartupModel* newModel();
 /*public*/ QString getEditModelMessage();
 /*public*/ QString getDescription();

};
Q_DECLARE_METATYPE(CreateButtonModelFactory)
#endif // CREATEBUTTONMODELFACTORY_H
