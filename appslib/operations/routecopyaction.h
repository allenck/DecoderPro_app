#ifndef ROUTECOPYACTION_H
#define ROUTECOPYACTION_H

#include "abstractaction.h"

namespace Operations
{
 class RouteCopyFrame;
 class RouteCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ RouteCopyAction(QString s, QObject* parent);
  /*public*/ RouteCopyAction(QString s, QString routeName,  QObject* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  RouteCopyFrame* f;// = null;
  void common();
  QString routeName;

 };
}
#endif // ROUTECOPYACTION_H
