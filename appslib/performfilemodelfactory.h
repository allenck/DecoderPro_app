#ifndef PERFORMFILEMODELFACTORY_H
#define PERFORMFILEMODELFACTORY_H
#include "abstractfilemodelfactory.h"

class PerformFileModel;
class JFileChooser;
class PerformFileModelFactory : public AbstractFileModelFactory
{
 Q_OBJECT
public:
 PerformFileModelFactory();
 ~PerformFileModelFactory() {}
 PerformFileModelFactory(const PerformFileModelFactory&) : AbstractFileModelFactory() {}
 /*public*/ /*Class<? extends StartupModel>*/QString getModelClass();
 /*public*/ StartupModel* newModel()override;
 /*public*/ QString getDescription()override;

 QObject* self() override {return (QObject*)this;}

protected:
 /*protected*/ JFileChooser* setFileChooser();

};
Q_DECLARE_METATYPE(PerformFileModelFactory)
#endif // PERFORMFILEMODELFACTORY_H
