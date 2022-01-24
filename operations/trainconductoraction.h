#ifndef TRAINCONDUCTORACTION_H
#define TRAINCONDUCTORACTION_H

#include "abstractaction.h"
#include "trainconductorframe.h"
#include <QPointer>

namespace Operations
{
 class TrainConductorFrame;
 class Train;
 class TrainConductorAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ TrainConductorAction(QString s, Train* train, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent * /*e*/);

 private:
  Train* train;
  QPointer<TrainConductorFrame> f;// = NULL;

 };
}
#endif // TRAINCONDUCTORACTION_H
