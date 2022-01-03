#include "printtrainsaction.h"
#include "trainmanager.h"
#include "setup.h"
#include "control.h"
#include "trainstableframe.h"
#include "hardcopywriter.h"
#include "routelocation.h"
#include "train.h"
#include <QCheckBox>
#include "route.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  *
  */
// /*private*/ static /*final*/ long serialVersionUID = 4793759654485486345L;
 /*static*/ /*final*/ QString PrintTrainsAction::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ QString PrintTrainsAction::TAB = "\t"; // NOI18N
 /*static*/ /*final*/ QChar PrintTrainsAction::FORM_FEED = '\f'; // NOI18N


 /*public*/ /*static*/ /*final*/ int PrintTrainsAction::MAX_NAME_LENGTH = Control::max_len_string_train_name - 10;

 /*public*/ PrintTrainsAction::PrintTrainsAction(QString actionName, JFrame* mframe, bool preview, JFrame* frame)
     : PrintTrainAction(actionName, mframe, preview, frame)
 {
     trainManager = ((TrainManager*)InstanceManager::getDefault("OperationsTrainManager"));
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void PrintTrainsAction::actionPerformed(ActionEvent* /*e*/) {

     // obtain a HardcopyWriter to do this
     HardcopyWriter* writer = NULL;
     //try {
         writer = new HardcopyWriter(mFrame, tr("Trains Table"), Control::reportFontSize, .5, .5, .5, .5, isPreview);
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log->debug("Print cancelled");
//         return;
//     }

     panel = (TrainsTableFrame*) frame;
     QList<Train*> trains = panel->getSortByList();

     printSummaryTrains(writer, trains);

     try {

         writer->write(FORM_FEED); // new page
         int numberOfLines = writer->getLinesPerPage();

         // now do the details for each train
         foreach (Train* train, trains)
         {
          if ((train->isBuildEnabled() || panel->showAllBox->isChecked()) && train->getRoute() != NULL)
          {
           QList<RouteLocation*>* route = train->getRoute()->getLocationsBySequenceList();
           // determine if another detailed summary can fit on the same page
           if (numberOfLines - writer->getCurrentLineNumber() < route->size() + NUMBER_OF_HEADER_LINES)
           {
               writer->write(FORM_FEED);
           } else if (writer->getCurrentLineNumber() > 0) {
               writer->write(NEW_LINE);
           }
           printTrain(writer, train);
          }
         }
     } catch (IOException* e1) {
         log->error("Exception in print train details");
     }

     // and force completion of the printing
     writer->close();
 }

 /*protected*/ void PrintTrainsAction::printSummaryTrains(HardcopyWriter* writer, QList<Train*> trains)
 {
  //try {
  QString s = tr("Name") + TAB + TAB + tr("Description") + TAB
          + tr("Route") + TAB + TAB + tr("Departs") + TAB + TAB
          + tr("Time") + "  " + tr("Terminates") + TAB + NEW_LINE;
  writer->write(s, 0, s.length());
  foreach (Train* train, trains)
  {
   if (train->isBuildEnabled() || panel->showAllBox->isChecked())
   {
    QString name = train->getName();
    name = truncate(name);
    QString desc = train->getDescription();
    desc = truncate(desc);
    QString route = train->getTrainRouteName();
    route = truncate(route);
    QString departs = train->getTrainDepartsName();
    departs = truncate(departs);
    QString terminates = train->getTrainTerminatesName();
    terminates = truncate(terminates);

    s = name + " " + desc + " " + route + " " + departs + " " + train->getDepartureTime() + " "
            + terminates + NEW_LINE;
    writer->write(s, 0, s.length());
   }
  }
//     } catch (IOException* we) {
//         log->error("Error printing trains summary");
//     }
 }

 /*private*/ QString PrintTrainsAction::truncate(QString string) {
     string = string.trimmed();
     if (string.length() > MAX_NAME_LENGTH) {
         string = string.mid(0, MAX_NAME_LENGTH);
     }
     // pad out the string
     QString buf = ""; //new StringBuffer(string);
     for (int j = string.length(); j < MAX_NAME_LENGTH; j++) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }
}
