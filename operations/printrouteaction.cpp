#include "printrouteaction.h"
#include "hardcopywriter.h"
#include "route.h"
#include "routemanager.h"
#include "control.h"
#include "routelocation.h"

namespace Operations
{
 /**
  * Action to print a summary of a route->
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * Macintosh MRJ
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2009, 2012
  * @version $Revision: 28795 $
  */
 ///*public*/ class PrintRouteAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 9199448958901465687L;
 /*static*/ /*final*/ QString PrintRouteAction::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ QString PrintRouteAction::TAB = "\t"; // NOI18N
 /*private*/ /*static*/ /*final*/ int PrintRouteAction::MAX_NAME_LENGTH = Control::max_len_string_location_name - 5;

 /*public*/ PrintRouteAction::PrintRouteAction(QString actionName, bool preview, Route* route, QObject* parent)
    : AbstractAction(actionName, parent)
{
     //super(actionName);
     mFrame = new JFrame();
     isPreview = preview;
     this->route = route;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintRouteAction::actionPerformed(ActionEvent* /*e*/) {
     if (route == NULL) {
         return;
     }

     // obtain a HardcopyWriter to do this
     HardcopyWriter* writer = NULL;
     //try {
         writer = new HardcopyWriter(mFrame, tr("Route %1").arg(route->getName()), Control::reportFontSize, .5, .5, .5, .5, isPreview);
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log.debug("Print cancelled");
//         return;
//     }
     printRoute(writer, route);
     // and force completion of the printing
     writer->close();
 }

 /*protected*/ void PrintRouteAction::printRoute(HardcopyWriter* writer, Route* route)
 {
     //try {
  writer->write(route->getComment() + NEW_LINE);
  QString s = tr("Location") + TAB + "    " + tr("Direction") + " "
          + tr("Moves") + " " + tr("Pick ups?") + " "
          + tr("Set outs?") + " " + tr("Wait") + TAB + tr("Length")
          + TAB + tr("Grade") + TAB + tr("X") + "    " + tr("Y")
          + NEW_LINE;
  writer->write(s);
  QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
  foreach (RouteLocation* rl, *routeList)
  {
   QString name = rl->getName();
   name = truncate(name);
   QString pad = " ";
   if (rl->getTrainIconX() < 10)
   {
    pad = "    ";
   }
   else if (rl->getTrainIconX() < 100)
   {
    pad = "   ";
   }
   else if (rl->getTrainIconX() < 1000)
   {
    pad = "  ";
   }
   s = name + TAB + rl->getTrainDirectionString() + TAB + QString::number(rl->getMaxCarMoves()) + TAB
           + (rl->isPickUpAllowed() ? tr("yes") : tr("no")) + TAB
           + (rl->isDropAllowed() ? tr("yes") : tr("no")) + TAB
           + QString::number(rl->getWait()) + TAB + QString::number(rl->getMaxTrainLength()) + TAB + QString::number(rl->getGrade()) + TAB + QString::number(rl->getTrainIconX())
           + pad + QString::number(rl->getTrainIconY()) + NEW_LINE;
   writer->write(s);
  }
  s = NEW_LINE + tr("Location") + TAB + tr("Departure Time") + TAB
          + tr("Comment") + NEW_LINE;
  writer->write(s);
  foreach (RouteLocation* rl, *routeList)
  {
   QString name = rl->getName();
   name = truncate(name);
   s = name + TAB + rl->getDepartureTime() + TAB + rl->getComment() + NEW_LINE;
   writer->write(s);
  }
//     } catch (IOException* we) {
//         log.error("Error printing route");
//     }
 }

 /*private*/ QString PrintRouteAction::truncate(QString string) {
     string = string.trimmed();
     if (string.length() > MAX_NAME_LENGTH) {
         string = string.mid(0, MAX_NAME_LENGTH);
     }
     // pad out the string
     QString buf = "";//new StringBuffer(string);
     for (int j = string.length(); j < MAX_NAME_LENGTH; j++) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }

}
