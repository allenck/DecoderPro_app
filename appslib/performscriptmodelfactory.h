#ifndef PERFORMSCRIPTMODELFACTORY_H
#define PERFORMSCRIPTMODELFACTORY_H
#include "abstractfilemodelfactory.h"

class PerformScriptModel;
class PerformScriptModelFactory : public AbstractFileModelFactory
{
public:
 /*public*/ PerformScriptModelFactory();
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ StartupModel* newModel();
 /*public*/ QString getDescription();

protected:
 //@Override
 /*protected*/ JFileChooser* setFileChooser();
};

#endif // PERFORMSCRIPTMODELFACTORY_H
