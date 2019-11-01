#ifndef IMPORTCARROSTERACTION_H
#define IMPORTCARROSTERACTION_H
#include "abstractaction.h"
#include "appslib_global.h"
namespace Operations
{
 class APPSLIBSHARED_EXPORT ImportCarRosterAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ImportCarRosterAction(QString name, QWidget* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae);
 };
}
#endif // IMPORTCARROSTERACTION_H
