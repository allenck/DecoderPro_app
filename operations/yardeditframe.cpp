#include "yardeditframe.h"
#include "track.h"
#include <QGroupBox>
#include <QPushButton>
#include "showcarsbylocationaction.h"
#include "showtrainsservinglocationaction.h"
#include "location.h"
#include <QMenu>
#include "changetracktypeaction.h"
namespace Operations
{
/**
 * Frame for user edit of a yard
 *
 * @author Dan Boudreau Copyright (C) 2008
 * @version $Revision: 29665 $
 */
///*public*/ class YardEditFrame extends TrackEditFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 3353058611424628644L;

 /*public*/ YardEditFrame::YardEditFrame(QWidget* parent) : TrackEditFrame(parent) {
    // super();
 }

 /*public*/ void YardEditFrame::initComponents(Location* location, Track* track)
 {
     _type = Track::YARD;
     TrackEditFrame::initComponents(location, track);
     _toolMenu->addAction(new ChangeTrackTypeAction(this));
     _toolMenu->addAction(new ShowTrainsServingLocationAction(tr("Show Trains Serving this Track"), _location, _track,this));
     _toolMenu->addAction(new ShowCarsByLocationAction(false, location->getName(), _trackName, this));

     addHelpMenu("package.jmri.jmrit.operations.Operations_Yards", true); // NOI18N

     // override text strings for tracks
     //panelTrainDir.setBorder(BorderFactory.createTitledBorder(tr("TrainYard")));
     panelTrainDir->setStyleSheet(gbStyleSheet);
     panelTrainDir->setTitle(tr("Train Yard"));
     //paneCheckBoxes.setBorder(BorderFactory.createTitledBorder(tr("TypesYard")));
     //paneCheckBoxes->setStyleSheet()
     deleteTrackButton->setText(tr("Delete Yard Track"));
     addTrackButton->setText(tr("Add Yard track"));
     saveTrackButton->setText(tr("Save Yard"));
     // finish
     dropPanel->setVisible(false); // don't show drop and pick up panel
     pickupPanel->setVisible(false);
     adjustSize();
     setVisible(true);
 }
 /*public*/ QString YardEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.YardEditFrame";
 }
}
