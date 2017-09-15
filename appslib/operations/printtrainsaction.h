#ifndef PRINTTRAINSACTION_H
#define PRINTTRAINSACTION_H

#include "printtrainaction.h"

class Logger;
class JFrame;
namespace Operations
{
 class TrainManager;
 class TrainsTableFrame;
 class PrintTrainsAction : public PrintTrainAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintTrainsAction(QString actionName, JFrame* mframe, bool preview, JFrame* frame);
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = Control::max_len_string_train_name - 10;

 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);
 private:
  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  static /*final*/ QString TAB;// = "\t"; // NOI18N
  static /*final*/ QChar FORM_FEED;// = '\f'; // NOI18N
  TrainManager* trainManager;// = TrainManager.instance();
  TrainsTableFrame* panel;
  Logger* log;
  /*private*/ QString truncate(QString string);

 protected:
  /*protected*/ void printSummaryTrains(HardcopyWriter* writer, QList<Train*> trains);

 };
}
#endif // PRINTTRAINSACTION_H
