#include "printtrainaction.h"
#include "hardcopywriter.h"
#include "train.h"
#include "traineditframe.h"
#include "control.h"
#include "route.h"
#include "routelocation.h"
#include <QLabel>
#include <QPixmap>

namespace Operations
{
/**
  *
  */
 //private static /*final*/ long serialVersionUID = -571267253370599017L;
 /*static*/ /*final*/ QString PrintTrainAction::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ QString PrintTrainAction::TAB = "\t"; // NOI18N

 /*public*/ PrintTrainAction::PrintTrainAction(QString actionName, JFrame* mFrame, bool isPreview, JFrame* frame)
     : AbstractAction(actionName, frame)
 {
     //super(actionName);
     this->mFrame = mFrame;
     this->isPreview = isPreview;
     this->frame = frame;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintTrainAction::actionPerformed(ActionEvent* /*e*/)
 {
     TrainEditFrame* f = (TrainEditFrame*) frame;
     Train* train = f->_train;
     if (train == NULL) {
         return;
     }

     // obtain a HardcopyWriter to do this
     HardcopyWriter* writer = NULL;
     // {
         writer = new HardcopyWriter(mFrame, tr("Train %1").arg(train->getName()), Control::reportFontSize, .5, .5, .5, .5, isPreview);
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log.debug("Print cancelled");
//         return;
//     }
     connect(writer, SIGNAL(printCancelled(QString)), this, SLOT(on_PrintCancelled(QString)));
     if(writer->isCancelled())
      return;

     printTrain(writer, train);

     // and force completion of the printing
     writer->close();
 }

void PrintTrainAction::on_PrintCancelled(QString msg)
{
 Logger::error(msg);
}
 // 7 lines of header and another 3 lines for possible comments
 /*protected*/ /*static*/ /*final*/ int PrintTrainAction::NUMBER_OF_HEADER_LINES = 10;

 /*protected*/ void PrintTrainAction::printTrain(HardcopyWriter* writer, Train* train) {
//     try {
         QString s = tr("Name") + ": " + train->getName() + NEW_LINE;
         writer->write(s, 0, s.length());
         s = tr("Description") + ": " + train->getDescription() + NEW_LINE;
         writer->write(s, 0, s.length());
         s = tr("Departs") + ": " + train->getTrainDepartsName() + NEW_LINE;
         writer->write(s, 0, s.length());
         s = tr("DepartTime") + ": " + train->getDepartureTime() + NEW_LINE;
         writer->write(s, 0, s.length());
         s = tr("Terminates") + ": " + train->getTrainTerminatesName() + NEW_LINE;
         writer->write(s, 0, s.length());
         s = NEW_LINE;
         writer->write(s, 0, s.length());
         s = tr("Route") + ": " + train->getTrainRouteName() + NEW_LINE;
         writer->write(s, 0, s.length());
         Route* route = train->getRoute();
         if (route != NULL) {
             foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
                 s = TAB + rl->getName() + NEW_LINE;
                 writer->write(s, 0, s.length());
             }
         }
         if (train->getComment()!=(Train::NONE)) {
             s = tr("Comment") + ": " + train->getComment() + NEW_LINE;
             writer->writeHtml(s);
         }
//     } catch (IOException we) {
//         logerror("Error printing train report");
//     }
 }

}
