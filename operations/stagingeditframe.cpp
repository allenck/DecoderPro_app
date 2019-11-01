#include "stagingeditframe.h"
#include <QBoxLayout>
#include "location.h"
#include "track.h"
#include <QGroupBox>
#include <QCheckBox>
#include "gridbaglayout.h"
#include <QPushButton>
#include "showcarsbylocationaction.h"
#include "showtrainsservinglocationaction.h"
#include <QMenu>
#include "trackdestinationeditaction.h"

namespace Operations
{
/**
 * Frame for user edit of a staging track
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011
 * @version $Revision: 29665 $
 */
///*public*/ class StagingEditFrame extends TrackEditFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 1540001164578122992L;

 /*public*/ StagingEditFrame::StagingEditFrame(QWidget* parent) : TrackEditFrame(parent) {
     //super();
  // check boxes
  swapLoadsCheckBox = new QCheckBox(tr("Swap default loads and empties"));
  emptyCheckBox = new QCheckBox(tr("Empty cars with default loads"));
  emptyCustomCheckBox = new QCheckBox(tr("Empty cars with custom loads"));
  loadCheckBox = new QCheckBox(tr("Generate custom loads for spurs serviced by this train"));
  loadAnyCheckBox = new QCheckBox(tr("Generate custom loads for any spur (multiple trains)"));
  loadAnyStagingCheckBox = new QCheckBox(tr("Generate custom loads for any staging track"));
  blockCarsCheckBox = new QCheckBox(tr("Block cars by pick up location"));

  panelLoad = panelOpt4;
 }

 /*public*/ void StagingEditFrame::initComponents(Location* location, Track* track)
 {

     // setup the optional panel with staging stuff
     //panelLoad->setLayout(panelLoad, BoxLayout.X_AXIS));
  QHBoxLayout* panelLoadLayout = new QHBoxLayout(panelLoad);

     QGroupBox* p1 = new QGroupBox();
     p1->setLayout(new GridBagLayout());
     //p1->setBorder(BorderFactory.createTitledBorder(tr("OptionalLoads")));
     p1->setStyleSheet(gbStyleSheet);
     p1->setTitle(tr("Optional car load controls"));
     addItemLeft(p1, swapLoadsCheckBox, 0, 0);
     addItemLeft(p1, emptyCheckBox, 0, 1);

     QGroupBox* p2 = new QGroupBox();
     p2->setLayout(new GridBagLayout());
     //p2->setBorder(BorderFactory.createTitledBorder(tr("OptionalCustomLoads")));
     p2->setStyleSheet(gbStyleSheet);
     p2->setTitle(tr("Optional custom car load controls"));
     addItemLeft(p2, emptyCustomCheckBox, 0, 0);
     addItemLeft(p2, loadCheckBox, 0, 1);
     addItemLeft(p2, loadAnyCheckBox, 0, 2);
     addItemLeft(p2, loadAnyStagingCheckBox, 0, 3);

     QGroupBox* p3 = new QGroupBox();
     p3->setLayout(new GridBagLayout());
     //p3->setBorder(BorderFactory.createTitledBorder(tr("OptionalBlocking")));
     p3->setStyleSheet(gbStyleSheet);
     p3->setTitle(tr("Optional Car Blocking"));
     addItemLeft(p3, blockCarsCheckBox, 0, 0);

     // load tool tips
     loadCheckBox->setToolTip(tr("This option ignores the schedule's alternate track"));
     blockCarsCheckBox->setToolTip(tr("Block cars out of staging based on where they were picked up "));

     panelLoadLayout->addWidget(p1);
     panelLoadLayout->addWidget(p2);
     panelLoadLayout->addWidget(p3);

     TrackEditFrame::initComponents(location, track);
     _type = Track::STAGING;
     _toolMenu->addAction(new TrackDestinationEditAction(this));
     _toolMenu->addAction(new ShowTrainsServingLocationAction(tr("Show Trains Serving this Track"), _location, _track,this));
     _toolMenu->addAction(new ShowCarsByLocationAction(false, location->getName(), _trackName, this));

     addHelpMenu("package.jmri.jmrit.operations.Operations_Staging", true); // NOI18N

     // override text strings for tracks
     //panelTrainDir->setBorder(BorderFactory.createTitledBorder(tr("TrainStaging")));
     panelTrainDir->setTitle(tr("This staging track is serviced by trains traveling"));
     //paneCheckBoxes
//             ->setBorder(BorderFactory.createTitledBorder(tr("TypesStaging")));
     checkBoxesGroupBox->setTitle(tr("Select the rolling stock serviced by this staging track"));
     //dropPanel
//             ->setBorder(BorderFactory.createTitledBorder(tr("SelectTrainArrival")));
     dropPanel->setTitle(tr("Select trains or routes for arrivals"));
//     pickupPanel->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("SelectTrainDeparture")));
     pickupPanel->setTitle(tr("SelectTrainDeparture"));
     deleteTrackButton->setText(tr("Delete Staging"));
     addTrackButton->setText(tr("Add Staging"));
     saveTrackButton->setText(tr("Save Staging"));

     // setup the check boxes
     if (_track != NULL) {
         swapLoadsCheckBox->setChecked(_track->isLoadSwapEnabled());
         emptyCheckBox->setChecked(_track->isLoadEmptyEnabled());
         emptyCustomCheckBox->setChecked(_track->isRemoveCustomLoadsEnabled());
         loadCheckBox->setChecked(_track->isAddCustomLoadsEnabled());
         loadAnyCheckBox->setChecked(_track->isAddCustomLoadsAnySpurEnabled());
         loadAnyStagingCheckBox->setChecked(_track->isAddCustomLoadsAnyStagingTrackEnabled());
         pShipLoadOption->setVisible(loadCheckBox->isChecked()
                 || loadAnyCheckBox->isChecked() || loadAnyStagingCheckBox->isChecked());	// show which loads this track can ship
         blockCarsCheckBox->setChecked(_track->isBlockCarsEnabled());
         if (loadCheckBox->isChecked() || loadAnyCheckBox->isChecked()
                 || loadAnyStagingCheckBox->isChecked()) {
             blockCarsCheckBox->setChecked(false);
             blockCarsCheckBox->setEnabled(false);
         }
     }

     addCheckBoxAction(swapLoadsCheckBox);
     addCheckBoxAction(emptyCheckBox);
     addCheckBoxAction(loadCheckBox);
     addCheckBoxAction(loadAnyCheckBox);
     addCheckBoxAction(loadAnyStagingCheckBox);

     // finish
     panelOrder->setVisible(false); // Car order out of staging isn't necessary
     adjustSize();
     setVisible(true);
 }

 /*protected*/ void StagingEditFrame::saveTrack(Track* track) {
     track->setLoadSwapEnabled(swapLoadsCheckBox->isChecked());
     track->setLoadEmptyEnabled(emptyCheckBox->isChecked());
     track->setRemoveCustomLoadsEnabled(emptyCustomCheckBox->isChecked());
     track->setAddCustomLoadsEnabled(loadCheckBox->isChecked());
     track->setAddCustomLoadsAnySpurEnabled(loadAnyCheckBox->isChecked());
     track->setAddCustomLoadsAnyStagingTrackEnabled(loadAnyStagingCheckBox->isChecked());
     track->setBlockCarsEnabled(blockCarsCheckBox->isChecked());
     TrackEditFrame::saveTrack(track);
 }

 /*protected*/ void StagingEditFrame::enableButtons(bool enabled) {
     swapLoadsCheckBox->setEnabled(enabled);
     emptyCheckBox->setEnabled(enabled);
     emptyCustomCheckBox->setEnabled(enabled);
     loadCheckBox->setEnabled(enabled);
     loadAnyCheckBox->setEnabled(enabled);
     loadAnyStagingCheckBox->setEnabled(enabled);
     if (!loadCheckBox->isChecked() && !loadAnyCheckBox->isChecked()
             && !loadAnyStagingCheckBox->isChecked() && enabled) {
         blockCarsCheckBox->setEnabled(true);
         pShipLoadOption->setVisible(false);
     } else {
         blockCarsCheckBox->setEnabled(false);
         pShipLoadOption->setVisible(true);
     }
     TrackEditFrame::enableButtons(enabled);
 }

 /*public*/ void StagingEditFrame::checkBoxActionPerformed(QWidget* ae) {
 QCheckBox* source = (QCheckBox*)ae;
     if (source == swapLoadsCheckBox) {
         if (swapLoadsCheckBox->isChecked()) {
             emptyCheckBox->setChecked(false);
         }
     } else if (source == emptyCheckBox) {
         if (emptyCheckBox->isChecked()) {
             swapLoadsCheckBox->setChecked(false);
         }
     } else if (source == loadCheckBox) {
         if (loadCheckBox->isChecked()) {
             loadAnyCheckBox->setChecked(false);
             blockCarsCheckBox->setChecked(false);
             blockCarsCheckBox->setEnabled(false);
         } else if (!loadAnyCheckBox->isChecked() && !loadAnyStagingCheckBox->isChecked()) {
             blockCarsCheckBox->setEnabled(true);
         }
     } else if (source == loadAnyCheckBox) {
         if (loadAnyCheckBox->isChecked()) {
             loadCheckBox->setChecked(false);
             blockCarsCheckBox->setChecked(false);
             blockCarsCheckBox->setEnabled(false);
         } else if (!loadCheckBox->isChecked() && !loadAnyStagingCheckBox->isChecked()) {
             blockCarsCheckBox->setEnabled(true);
         }
     } else if (source == loadAnyStagingCheckBox) {
         if (loadAnyStagingCheckBox->isChecked()) {
             blockCarsCheckBox->setEnabled(false);
         } else if (!loadCheckBox->isChecked() && !loadAnyCheckBox->isChecked()) {
             blockCarsCheckBox->setEnabled(true);
         }
     } else {
         TrackEditFrame::checkBoxActionPerformed(ae);
     }
 }
}
