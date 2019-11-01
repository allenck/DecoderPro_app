#ifndef PRINTROUTESACTION_H
#define PRINTROUTESACTION_H

#include "printrouteaction.h"

namespace Operations
{
 class PrintRoutesAction : public PrintRouteAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintRoutesAction(QString actionName, bool preview, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);

 private:
  /*private*/ static /*final*/ char FORM_FEED;// = '\f';
  Logger* log;
 };
}
#endif // PRINTROUTESACTION_H
