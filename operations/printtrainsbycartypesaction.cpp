#include "printtrainsbycartypesaction.h"
#include "hardcopywriter.h"
#include "trainmanager.h"
#include "train.h"
#include "car.h"
#include "cartypes.h"
#include "control.h"

namespace Operations
{
 /**
  * Action to print a summary of trains that service specific car types.
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * Macintosh MRJ
  *
  * @author	Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28795 $
  */
 ///*public*/ class PrintTrainsByCarTypesAction extends AbstractAction {

 /**
 *
 */
 //private static final long serialVersionUID = -2653744210816739088L;
 /*static*/ /*final*/ QString PrintTrainsByCarTypesAction::NEW_LINE = "\n";	// NOI18N
 /*static*/ /*final*/ QString PrintTrainsByCarTypesAction::TAB = "\t"; // NOI18N

 /*public*/ PrintTrainsByCarTypesAction::PrintTrainsByCarTypesAction(QString actionName, JFrame* frame, bool preview, QWidget* pWho)
    : AbstractAction(actionName, pWho)
 {
  //super(actionName);
  mFrame = frame;
  isPreview = preview;
 }

 /*public*/ /*static*/ /*final*/ int PrintTrainsByCarTypesAction::MAX_NAME_LENGTH = 25;

 /*public*/ void PrintTrainsByCarTypesAction::actionPerformed(ActionEvent* /*e*/)
 {
  // obtain a HardcopyWriter
  //try {
      writer = new HardcopyWriter(mFrame, tr("Trains By Type"), Control::reportFontSize, .5, .5, .5, .5,
              isPreview);
//  } catch (HardcopyWriter.PrintCanceledException ex) {
//      log->debug("Print cancelled");
//      return;
//  }

  // Loop through the car types showing which locations and tracks will
  // service that car type
  QStringList carTypes = CarTypes::instance()->getNames();

  QList<Train*> trains = trainManager->getTrainsByNameList();

  //try {
      // title line
      QString s = tr("Type") + TAB + tr("Trains")
              + TAB + TAB + TAB + tr("Description") + NEW_LINE;
      writer->write(s);
      // car types
      foreach (QString type, carTypes) {
          s = type + NEW_LINE;
          writer->write(s);
          // trains
          foreach (Train* train, trains) {
              if (train->acceptsTypeName(type)) {
                  QString sb = "";//new StringBuilder();
                  QString name = train->getName();
                  sb.append(TAB + name + " ");
                  int j = MAX_NAME_LENGTH - name.length();
                  while (j > 0) {
                      j--;
                      sb.append(" ");
                  }
                  sb.append(train->getDescription() + NEW_LINE);
                  writer->write(sb/*.toString()*/);
              }
          }
      }
      // and force completion of the printing
      writer->close();
//  } catch (IOException we) {
//      log->error("Error printing PrintLocationAction: " + we);
//  }
 }
}
