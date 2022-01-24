#ifndef BUILDREPORTOPTIONACTION_H
#define BUILDREPORTOPTIONACTION_H

#include "abstractaction.h"
#include "buildreportoptionframe.h"
#include <QPointer>

namespace Operations
{
 class BuildReportOptionFrame;
 class BuildReportOptionAction : public AbstractAction
 {
  Q_OBJECT

 public:
  BuildReportOptionAction(QObject* parent);
  /*public*/ BuildReportOptionAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  QPointer<BuildReportOptionFrame> f;// = null;

 };
}
#endif // BUILDREPORTOPTIONACTION_H
