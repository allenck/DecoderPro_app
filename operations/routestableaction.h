#ifndef ROUTESTABLEACTION_H
#define ROUTESTABLEACTION_H

#include "abstractaction.h"
#include <QObject>

namespace Operations
{
 class RoutesTableFrame;
 class RoutesTableAction : public AbstractAction
 {
   Q_OBJECT
  public:
   RoutesTableAction(QObject* parent);
   /*public*/ RoutesTableAction(QString s, QObject* parent);

 public slots:
   /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
   static RoutesTableFrame* f;// = null;
   void common();
 };
}
#endif // ROUTESTABLEACTION_H
