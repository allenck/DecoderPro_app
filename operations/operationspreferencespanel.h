#ifndef OPERATIONSPREFERENCESPANEL_H
#define OPERATIONSPREFERENCESPANEL_H
#include "operationspanel.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT OperationsPreferencesPanel : public OperationsPanel
 {
  Q_OBJECT
 public:
  explicit OperationsPreferencesPanel(QWidget *parent = 0);
  /*public*/ QString getPreferencesItem();
  /*public*/ QString getPreferencesItemText();
  /*public*/ QString getLabelKey();
  /*public*/ QWidget* getPreferencesComponent();
  /*public*/ bool isPersistant() ;
  /*public*/ bool isRestartRequired();
  /*public*/ bool isPreferencesValid();

 signals:

 public slots:
 protected:
 };
}
#endif // OPERATIONSPREFERENCESPANEL_H
