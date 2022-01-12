#ifndef PERFORMSCRIPTMODELFACTORY_H
#define PERFORMSCRIPTMODELFACTORY_H
#include "abstractfilemodelfactory.h"

class PerformScriptModel;
class PerformScriptModelFactory : public AbstractFileModelFactory
{
 Q_OBJECT
public:
 /*public*/ PerformScriptModelFactory();
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ StartupModel* newModel();
 /*public*/ QString getDescription();
  QObject* self() override {return (QObject*)this;}

protected:
 //@Override
 /*protected*/ JFileChooser* setFileChooser();
};

#endif // PERFORMSCRIPTMODELFACTORY_H
