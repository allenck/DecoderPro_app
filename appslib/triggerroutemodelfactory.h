#ifndef TRIGGERROUTEMODELFACTORY_H
#define TRIGGERROUTEMODELFACTORY_H
#include "startupmodelfactory.h"

class Logger;
class TriggerRouteModelFactory : public QObject, public StartupModelFactory
{
 Q_OBJECT
  Q_INTERFACES(StartupModelFactory)
public:
 TriggerRouteModelFactory();
 ~TriggerRouteModelFactory() {}
 TriggerRouteModelFactory(const TriggerRouteModelFactory&) : StartupModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass()override;
 /*public*/ QString getDescription()override;
 /*public*/ QString getActionText()override;
 /*public*/ StartupModel* newModel()override;
 /*public*/ void editModel(StartupModel* model, QWidget* parent)override;
 /*public*/ void initialize()override;

 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TriggerRouteModelFactory.class.getName());

};
Q_DECLARE_METATYPE(TriggerRouteModelFactory)
#endif // TRIGGERROUTEMODELFACTORY_H
