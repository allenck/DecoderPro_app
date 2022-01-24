#ifndef PRINTROUTESACTION_H
#define PRINTROUTESACTION_H

#include "printrouteaction.h"

namespace Operations
{
 class PrintRoutesAction : public PrintRouteAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintRoutesAction(bool preview, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/=0)override;

 private:
  /*private*/ static /*final*/ char FORM_FEED;// = '\f';
  Logger* log;
  Route* _route;
 };
}
#endif // PRINTROUTESACTION_H
