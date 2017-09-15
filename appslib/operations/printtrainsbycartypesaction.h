#ifndef PRINTTRAINSBYCARTYPESACTION_H
#define PRINTTRAINSBYCARTYPESACTION_H

#include "abstractaction.h"

class HardcopyWriter;
class JFrame;
namespace Operations
{
 class TrainManager;
 class PrintTrainsByCarTypesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  PrintTrainsByCarTypesAction(QString actionName, JFrame* frame, bool preview, QWidget* pWho);
/*public*/ static /*final*/ int MAX_NAME_LENGTH;// = 25;
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);
 private:
  static /*final*/ QString NEW_LINE;// = "\n";	// NOI18N
  static /*final*/ QString TAB;// = "\t"; // NOI18N
  TrainManager* trainManager;// = TrainManager.instance();
  /**
  * Frame hosting the printing
  */
  JFrame* mFrame;
  /**
  * Variable to set whether this is to be printed or previewed
  */
  bool isPreview;
  HardcopyWriter* writer;

 };
}
#endif // PRINTTRAINSBYCARTYPESACTION_H
