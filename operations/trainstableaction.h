#ifndef TRAINSTABLEACTION_H
#define TRAINSTABLEACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

namespace Operations
{
 class TrainsTableFrame;
 class APPSLIBSHARED_EXPORT TrainsTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainsTableAction(QObject* parent);
  /*public*/ TrainsTableAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/);
 private:
  void common();
  static TrainsTableFrame* f;// = null;

 };
}

#endif // TRAINSTABLEACTION_H
