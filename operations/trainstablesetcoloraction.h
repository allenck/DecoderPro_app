#ifndef TRAINSTABLESETCOLORACTION_H
#define TRAINSTABLESETCOLORACTION_H

#include "abstractaction.h"
#include "trainstablesetcolorframe.h"
#include <QPointer>

namespace Operations
{
 class Train;
 class TrainsTableSetColorFrame;
 class TrainsTableSetColorAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainsTableSetColorAction(QObject* parent);
  /*public*/ TrainsTableSetColorAction(QString s, Train* train, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/);

 private:
  QPointer<TrainsTableSetColorFrame> f;// = null;
  Train* _train;// = null;
  void common();
 };
}
#endif // TRAINSTABLESETCOLORACTION_H
