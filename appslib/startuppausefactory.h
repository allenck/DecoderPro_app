#ifndef STARTUPPAUSEFACTORY_H
#define STARTUPPAUSEFACTORY_H
#include "startupmodelfactory.h"
#include <QSpinBox>

class StartupPauseFactory : public QObject, public StartupModelFactory
{
 Q_OBJECT
  Q_INTERFACES(StartupModelFactory)
public:
 StartupPauseFactory();
 /*public*/ QString /*Class<? extends StartupModel>*/ getModelClass() ;
 /*public*/ StartupModel* newModel()override;
 /*public*/ QString getDescription()override;
 /*public*/ QString getActionText()override;
 /*public*/ void editModel(StartupModel* model, QWidget* parent)override;
 /*public*/ void initialize()override;
 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ QWidget* getDialogMessage(QSpinBox* spinner);

};

#endif // STARTUPPAUSEFACTORY_H
