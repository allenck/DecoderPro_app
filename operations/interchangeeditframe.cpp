#include "interchangeeditframe.h"
#include "location.h"
#include "track.h"
#include <QGroupBox>
#include "jbutton.h"
#include "showcarsbylocationaction.h"
#include "showtrainsservinglocationaction.h"
#include <QMenu>
#include "ignoreusedtrackaction.h"
#include "changetracktypeaction.h"
#include "trackdestinationeditaction.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame for user edit of a classification/interchange track. Adds two panels to
 * TrackEditFrame for train/route car drops and pulls.
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011, 2012
 * @version $Revision: 29665 $
 */
///*public*/ class InterchangeEditFrame extends TrackEditFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 5077272536994978975L;

 /*public*/ InterchangeEditFrame::InterchangeEditFrame(QWidget* parent) : TrackEditFrame(parent) {
     //super();
 }

 /*public*/ void InterchangeEditFrame::initComponents(Location* location, Track* track) {
     _type = Track::INTERCHANGE;

     TrackEditFrame::initComponents(location, track);

     _toolMenu->addAction(new IgnoreUsedTrackAction(this));
     _toolMenu->addAction(new TrackDestinationEditAction(this));
     _toolMenu->addAction(new ChangeTrackTypeAction(this));
     _toolMenu->addAction(new ShowTrainsServingLocationAction(tr("Show Trains Serving this Track"), _location, _track,this));
     _toolMenu->addAction(new ShowCarsByLocationAction(false, location->getName(), _trackName, this));

     addHelpMenu("package.jmri.jmrit.operations.Operations_Interchange", true); // NOI18N

     // override text strings for tracks
     panelTrainDir->setBorder(BorderFactory::createTitledBorder(tr("Select trains or routes for departures")));
     panelCheckBoxes->setBorder(BorderFactory::createTitledBorder(tr("Select the rolling stock serviced by this classification/interchange track")));
     //deleteTrackButton.setText(tr("DeleteInterchange"));
     addTrackButton->setText(tr("Add Interchange"));
     saveTrackButton->setText(tr("Save Interchange"));

     // finish
     adjustSize();
     setVisible(true);
 }

 /*public*/ QString InterchangeEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.InterchangeEditFrame";
 }

}
