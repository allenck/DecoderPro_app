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
 ScriptButtonModelFactory();
 ~ScriptButtonModelFactory() {}
 ScriptButtonModelFactory(const ScriptButtonModelFactory&) : StartupModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ StartupModel* newModel();
 /*public*/ QString getDescription();
 /*public*/ QString getActionText();
 /*public*/ void editModel(StartupModel* model, QWidget* parent);
 /*public*/ void initialize();
 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ ScriptFileChooser* chooser;// = null;

};
Q_DECLARE_METATYPE(ScriptButtonModelFactory)
#endif // SCRIPTBUTTONMODELFACTORY_H
