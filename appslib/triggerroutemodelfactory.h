#ifndef TRIGGERROUTEMODELFACTORY_H
#define TRIGGERROUTEMODELFACTORY_H
#include "startupmodelfactory.h"

class Logger;
class TriggerRouteModelFactory : public StartupModelFactory
{
 Q_OBJECT
public:
 TriggerRouteModelFactory();
 ~TriggerRouteModelFactory() {}
 TriggerRouteModelFactory(const TriggerRouteModelFactory&) : StartupModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ QString getDescription();
 /*public*/ QString getActionText();
 /*public*/ StartupModel* newModel();
 /*public*/ void editModel(StartupModel* model, QWidget* parent);
 /*public*/ void initialize();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TriggerRouteModelFactory.class.getName());

};
Q_DECLARE_METATYPE(TriggerRouteModelFactory)
#endif // TRIGGERROUTEMODELFACTORY_H
