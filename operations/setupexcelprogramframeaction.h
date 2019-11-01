#ifndef SETUPEXCELPROGRAMFRAMEACTION_H
#define SETUPEXCELPROGRAMFRAMEACTION_H
#include "abstractaction.h"
namespace Operations
{

 class SetupExcelProgramManifestFrame;
 class SetupExcelProgramFrameAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SetupExcelProgramFrameAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);
 private:
  SetupExcelProgramManifestFrame* f;// = NULL;

 };
}
#endif // SETUPEXCELPROGRAMFRAMEACTION_H
