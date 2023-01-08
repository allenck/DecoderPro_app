#ifndef SCRIPTBUTTONMODELFACTORY_H
#define SCRIPTBUTTONMODELFACTORY_H
#include "startupmodelfactory.h"

class ScriptButtonModel;
class ScriptFileChooser;
class ScriptButtonModelFactory : QObject, public StartupModelFactory
{
 Q_OBJECT
  Q_INTERFACES(StartupModelFactory)
public:
 Q_INVOKABLE ScriptButtonModelFactory();
 ~ScriptButtonModelFactory() {}
 ScriptButtonModelFactory(const ScriptButtonModelFactory&) : StartupModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass() override ;
 /*public*/ StartupModel* newModel() override ;
 /*public*/ QString getDescription() override ;
 /*public*/ QString getActionText() override ;
 /*public*/ void editModel(StartupModel* model, QWidget* parent) override ;
 /*public*/ void initialize() override ;
 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ ScriptFileChooser* chooser;// = null;

};
Q_DECLARE_METATYPE(ScriptButtonModelFactory)
#endif // SCRIPTBUTTONMODELFACTORY_H
