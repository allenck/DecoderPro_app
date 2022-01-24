#include "printlocationsbycartypesaction.h"
#include "logger.h"
#include "hardcopywriter.h"
#include "locationmanager.h"
#include "control.h"
#include "cartypes.h"
#include "location.h"
#include "track.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Action to print a summary of locations and tracks that service specific car
  * types.
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * Macintosh MRJ
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28795 $
  */
 ///*public*/ class PrintLocationsByCarTypesAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 7757265502705876182L;
 /*static*/ /*final*/ QString PrintLocationsByCarTypesAction::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ QString PrintLocationsByCarTypesAction::TAB = "\t"; // NOI18N


 /*public*/ PrintLocationsByCarTypesAction::PrintLocationsByCarTypesAction(QString actionName, JFrame* frame, bool preview,
         QWidget* pWho) : AbstractAction(actionName, pWho)
{
  //super(actionName);
 log = new Logger("PrintLocationsByCarTypesAction");
 locManager = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));

  mFrame = frame;
  isPreview = preview;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintLocationsByCarTypesAction::actionPerformed(ActionEvent* /*e*/)
 {
     // obtain a HardcopyWriter
     //try {
  writer = new HardcopyWriter(mFrame, tr("Locations By Type"), Control::reportFontSize, .5,
                 .5, .5, .5, isPreview);
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log.debug("Print cancelled");
//         return;
//     }

  // Loop through the car types showing which locations and tracks will
  // service that car type
  QStringList carTypes = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames();

  QList<Location*> locations = locManager->getLocationsByNameList();

  //try {
      // title line
      QString s = tr("Type") + TAB + tr("Location") + TAB
              + tr("Track") + NEW_LINE;
      writer->write(s);
      // car types
      foreach (QString type, carTypes) {
          s = type + NEW_LINE;
          writer->write(s);
          // locations
          foreach (Location* location, locations) {
              if (location->acceptsTypeName(type)) {
                  s = TAB + location->getName() + NEW_LINE;
                  writer->write(s);
                  // tracks
                  QList<Track*> tracks = location->getTracksByNameList(NULL);
                  foreach (Track* track, tracks) {
                      if (track->acceptsTypeName(type)) {
                          s = TAB + TAB + TAB + track->getName() + NEW_LINE;
                          writer->write(s);
                      }
                  }
              }
          }
      }
      // and force completion of the printing
      writer->close();
//  } catch (IOException* we) {
//      log.error("Error printing PrintLocationAction: " + we);
//  }
 }

}
