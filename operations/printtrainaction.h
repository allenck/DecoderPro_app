#ifndef PRINTTRAINACTION_H
#define PRINTTRAINACTION_H

#include "abstractaction.h"

class HardcopyWriter;
class JFrame;
namespace Operations
{
 class Train;
 class PrintTrainAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintTrainAction(QString actionName, JFrame* mFrame, bool isPreview, JFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);
 void on_PrintCancelled(QString);

 private:
  /**
   * Frame hosting the printing
   */
  JFrame* mFrame;
  JFrame* frame; // TrainEditFrame
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  static /*final*/ QString TAB;// = "\t"; // NOI18N

 protected:
  /*protected*/ static /*final*/ int NUMBER_OF_HEADER_LINES;// = 10;

  /*protected*/ void printTrain(HardcopyWriter* writer, Train* train);
 friend class PrintTrainsAction;
 };
}
#endif // PRINTTRAINACTION_H
