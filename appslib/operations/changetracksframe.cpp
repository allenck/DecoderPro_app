#include "changetracksframe.h"
#include "operationsxml.h"
#include "setup.h"
#include "control.h"
#include "track.h"
#include <QPushButton>
#include <QRadioButton>
#include "location.h"
#include "locationeditframe.h"
#include "logger.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "gridbaglayout.h"
#include <QButtonGroup>

namespace Operations
{
/**
 * Action to change all of tracks at a location to the same type of Track:: Track
 * types are Spurs, Yards, Interchanges and Staging.
 *
 * @author Daniel Boudreau Copyright (C) 2011
 * @version $Revision: 18559 $
 */
//class ChangeTracksFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 6478467506871775174L;


 /*public*/ ChangeTracksFrame::ChangeTracksFrame(LocationEditFrame* lef)
  : OperationsFrame(lef)
 {
     //super();
 log = new Logger("ChangeTracksFrame");
     // radio buttons
     spurRadioButton = new QRadioButton(tr("Spur"));
     yardRadioButton = new QRadioButton(tr("Yard"));
     interchangeRadioButton = new QRadioButton(tr("Interchange"));
     stagingRadioButton = new QRadioButton(tr("Staging"));

     // major buttons
     saveButton = new QPushButton(tr("Save"));


     // the following code sets the frame's initial state
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     getContentPane()->setLayout(new QVBoxLayout);
     _lef = lef;
     if (_lef->_location == NULL) {
         log->debug("location is NULL, change location track types not possible");
         return;
     }
     _location = _lef->_location;

     // load the panel
     // row 1a
     QGroupBox* p1 = new QGroupBox();
     p1->setLayout(new GridBagLayout());
     //p1.setBorder(BorderFactory.createTitledBorder(MessageFormat.format(tr("TrackType"),
//             new Object[]{_location.getName()})));
     p1->setStyleSheet(gbStyleSheet);
     p1->setTitle(tr("Select Desired Track Type for %1").arg(_location->getName()));
     addItem(p1, spurRadioButton, 0, 0);
     addItem(p1, yardRadioButton, 1, 0);
     addItem(p1, interchangeRadioButton, 2, 0);
     addItem(p1, stagingRadioButton, 3, 0);
     addItem(p1, saveButton, 2, 1);

     // group and set current track type
     QButtonGroup* group = new QButtonGroup();
     group->addButton(spurRadioButton);
     group->addButton(yardRadioButton);
     group->addButton(interchangeRadioButton);
     group->addButton(stagingRadioButton);

     // button action
     addButtonAction(saveButton);

     getContentPane()->layout()->addWidget(p1);
     setTitle(tr("Change Track Type"));
     adjustSize();
     setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight100));
     setVisible(true);
 }

 /*public*/ void ChangeTracksFrame::buttonActionPerformed(QWidget* ae) {
QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         // check to see if button has changed
         if (spurRadioButton->isChecked()) {
             changeTracks(Track::SPUR);
         } else if (yardRadioButton->isChecked()) {
             changeTracks(Track::YARD);
         } else if (interchangeRadioButton->isChecked()) {
             changeTracks(Track::INTERCHANGE);
         } else if (stagingRadioButton->isChecked()) {
             changeTracks(Track::STAGING);
         }
     }
 }

 /*private*/ void ChangeTracksFrame::changeTracks(QString type) {
     log->debug(tr("change tracks to %1").arg(type));
     QList<Track*> tracks = _location->getTrackByNameList(NULL);
     foreach (Track* track, tracks) {
         track->setTrackType(type);
     }
     if (type==(Track::STAGING)) {
         _location->setLocationOps(Location::STAGING);
     } else {
         _location->setLocationOps(Location::NORMAL);
     }
     OperationsXml::save();
     _lef->dispose();
     dispose();
 }

}
