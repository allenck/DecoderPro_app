#ifndef SETUPEXCELPROGRAMFRAMEACTION_H
#define SETUPEXCELPROGRAMFRAMEACTION_H
#include "abstractaction.h"
#include "setupexcelprogrammanifestframe.h"
#include <QPointer>

namespace Operations
{

 class SetupExcelProgramManifestFrame;
 class SetupExcelProgramFrameAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SetupExcelProgramFrameAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent *e);
 private:
  QPointer<SetupExcelProgramManifestFrame> f;// = NULL;

 };
}
#endif // SETUPEXCELPROGRAMFRAMEACTION_H
