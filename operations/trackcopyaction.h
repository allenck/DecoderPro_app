#ifndef TRACKCOPYACTION_H
#define TRACKCOPYACTION_H

#include "abstractaction.h"
#include "trackcopyframe.h"
#include <QPointer>

namespace Operations
{
 class LocationEditFrame;
 class TrackCopyFrame;
 class TrackCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
   /*public*/ TrackCopyAction(QObject* parent);
  TrackCopyAction(LocationEditFrame* lef, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0);

 private:
  /*private*/ LocationEditFrame* _lef;
  QPointer<TrackCopyFrame> f;// = null;

 };
}
#endif // TRACKCOPYACTION_H
