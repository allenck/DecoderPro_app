#ifndef PERFORMFILEMODELFACTORY_H
#define PERFORMFILEMODELFACTORY_H
#include "abstractfilemodelfactory.h"

class PerformFileModel;
class JFileChooser;
class PerformFileModelFactory : public AbstractFileModelFactory
{
public:
 PerformFileModelFactory();
 ~PerformFileModelFactory() {}
 PerformFileModelFactory(const PerformFileModelFactory&) : AbstractFileModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ StartupModel* newModel();
 /*public*/ QString getDescription();

protected:
 /*protected*/ JFileChooser* setFileChooser();

};
Q_DECLARE_METATYPE(PerformFileModelFactory)
#endif // PERFORMFILEMODELFACTORY_H
