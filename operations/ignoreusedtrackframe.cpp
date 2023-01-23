#include "ignoreusedtrackframe.h"
#include "setup.h"
#include "control.h"
#include "operationsxml.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QRadioButton>
#include "jbutton.h"
#include <QButtonGroup>
#include "trackeditframe.h"
#include "track.h"
#include "logger.h"
#include "flowlayout.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Action to allow a user to define how much used track space is to be ignored
  * by the program when placing new rolling stock to a track.
  *
  * @author Daniel Boudreau Copyright (C) 2012
  * @version $Revision: 18559 $
  */
 //class IgnoreUsedTrackFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 8653916276049204803L;
 // radio buttons

 /*public*/ IgnoreUsedTrackFrame::IgnoreUsedTrackFrame(TrackEditFrame* tef) :OperationsFrame(tef){
     //super();
  setFrameRef(getClassName());
 log = new Logger("IgnoreUsedTrackFrame");
     zeroPercent = new QRadioButton(tr("Disabled"));
     twentyfivePercent = new QRadioButton("25%");	// NOI18N
     fiftyPercent = new QRadioButton("50%");		// NOI18N
     seventyfivePercent = new QRadioButton("75%");	// NOI18N
     hundredPercent = new QRadioButton("100%");		// NOI18N

     // major buttons
     saveButton = new JButton(tr("Save"));

     setTitle(tr("Planned Pickups"));

     _tef = tef;
     _track = _tef->_track;
     if (_track == NULL) {
         log->debug("track is null!");
         return;
     }

     // load the panel
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     JPanel* p1 = new JPanel();
     p1->setBorder(BorderFactory::createTitledBorder(tr("PrePlanned Pickups")));

     p1->layout()->addWidget(zeroPercent);
     p1->layout()->addWidget(twentyfivePercent);
     p1->layout()->addWidget(fiftyPercent);
     p1->layout()->addWidget(seventyfivePercent);
     p1->layout()->addWidget(hundredPercent);

     QButtonGroup* buttonGroup = new QButtonGroup();
     buttonGroup->addButton(zeroPercent);
     buttonGroup->addButton(twentyfivePercent);
     buttonGroup->addButton(fiftyPercent);
     buttonGroup->addButton(seventyfivePercent);
     buttonGroup->addButton(hundredPercent);

     // select the correct radio button
     int percentage = _track->getIgnoreUsedLengthPercentage();
     zeroPercent->setChecked(percentage >= 0);
     twentyfivePercent->setChecked(percentage >= 25);
     fiftyPercent->setChecked(percentage >= 50);
     seventyfivePercent->setChecked(percentage >= 75);
     hundredPercent->setChecked(percentage >= 100);

     thisLayout->addWidget(p1);
     thisLayout->addWidget(saveButton);

     addButtonAction(saveButton);

     adjustSize();
     setVisible(true);
 }

 /*public*/ void IgnoreUsedTrackFrame::buttonActionPerformed(QWidget* ae) {
     if ((JButton*)ae == saveButton) {
         // save percentage selected
         int percentage = 0;
         if (twentyfivePercent->isChecked()) {
             percentage = 25;
         } else if (fiftyPercent->isChecked()) {
             percentage = 50;
         } else if (seventyfivePercent->isChecked()) {
             percentage = 75;
         } else if (hundredPercent->isChecked()) {
             percentage = 100;
         }
         if (_track != NULL) {
             _track->setIgnoreUsedLengthPercentage(percentage);
         }
         // save location file
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }
/*public*/ QString IgnoreUsedTrackFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.IgnoreUsedTrackFrame";
}

}
