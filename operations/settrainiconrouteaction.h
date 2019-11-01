#ifndef SETTRAINICONROUTEACTION_H
#define SETTRAINICONROUTEACTION_H

#include "abstractaction.h"
namespace Operations
{
 class SetTrainIconRouteFrame;
 class SetTrainIconRouteAction : public AbstractAction
 {
 public:
  /*public*/ SetTrainIconRouteAction(QString s, QObject* parent);
  /*public*/ SetTrainIconRouteAction(QString s, QString routeName, QObject* parent)
  ;
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e =0);

 private:
  SetTrainIconRouteFrame* f;// = null;
  void common();
  QString routeName;

 };
}
#endif // SETTRAINICONROUTEACTION_H
