#ifndef STARTUPPAUSEFACTORY_H
#define STARTUPPAUSEFACTORY_H
#include "startupmodelfactory.h"
#include <QSpinBox>

class StartupPauseFactory : public StartupModelFactory
{
public:
 StartupPauseFactory();
 /*public*/ QString /*Class<? extends StartupModel>*/ getModelClass() ;
 /*public*/ StartupModel* newModel();
 /*public*/ QString getDescription();
 /*public*/ QString getActionText();
 /*public*/ void editModel(StartupModel* model, QWidget* parent);
 /*public*/ void initialize();

private:
 /*private*/ QWidget* getDialogMessage(QSpinBox* spinner);

};

#endif // STARTUPPAUSEFACTORY_H
