#ifndef OPERATIONSPREFERENCESPANEL_H
#define OPERATIONSPREFERENCESPANEL_H
#include "operationspanel.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT OperationsPreferencesPanel : public OperationsPanel, public PreferencesPanel
 {
  Q_OBJECT
  Q_INTERFACES(PreferencesPanel)
 public:
  explicit OperationsPreferencesPanel(QWidget *parent = 0);
  /*public*/ QString getPreferencesItem()override;
  /*public*/ QString getPreferencesItemText()override;
  /*public*/ QString getLabelKey()override;
  /*public*/ QWidget* getPreferencesComponent()override;
  /*public*/ bool isPersistant() override;
  /*public*/ bool isRestartRequired()override;
  /*public*/ bool isPreferencesValid()override;
   QObject* ppself() override{return (QObject*)this;}

 signals:

 public slots:
 protected:
 };
}
#endif // OPERATIONSPREFERENCESPANEL_H
