#ifndef PRINTTRAINBUILDREPORTACTION_H
#define PRINTTRAINBUILDREPORTACTION_H

#include "abstractaction.h"
class JFrame;
namespace Operations
{
 class PrintTrainBuildReportAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintTrainBuildReportAction(QString actionName, bool preview, JFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  JFrame* frame;
 };
}
#endif // PRINTTRAINBUILDREPORTACTION_H
