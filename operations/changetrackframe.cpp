#include "changetrackframe.h"
#include "operationsxml.h"
#include <QBoxLayout>
#include "control.h"
#include "setup.h"
#include <QRadioButton>
#include <QButtonGroup>
#include "trackeditframe.h"
#include "track.h"
#include <QGroupBox>
#include <QPushButton>
#include "gridbaglayout.h"

namespace Operations
{
 /**
  * Action to change the type of track. Track types are Spurs, Yards,
  * Interchanges and Staging.
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 //class ChangeTrackFrame extends OperationsFrame {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 6928159706916403497L;


 /*public*/ ChangeTrackFrame::ChangeTrackFrame(TrackEditFrame* tef)
   : OperationsFrame()
 {
   //super();
  log = new Logger("ChangeTrackFrame");
  // radio buttons
  spurRadioButton = new QRadioButton(tr("Spur"));
  yardRadioButton = new QRadioButton(tr("Yard"));
  interchangeRadioButton = new QRadioButton(tr("Interchange"));
  group = new QButtonGroup();

  // major buttons
  saveButton = new QPushButton(tr("Save"));

  _trackType = "";
  // the following code sets the frame's initial state
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  _tef = tef;
  if (_tef->_track == NULL) {
      log->debug("track is null, change track not possible");
      return;
  }
  QString trackName = _tef->_track->getName();

  // load the panel
  // row 1a
  QGroupBox* p1 = new QGroupBox();
  p1->setLayout(new GridBagLayout());
  //p1.setBorder(BorderFactory.createTitledBorder(MessageFormat.format(tr("TrackType"), new Object[]{trackName})));
  p1->setStyleSheet(gbStyleSheet);
  addItem(p1, spurRadioButton, 0, 0);
  addItem(p1, yardRadioButton, 1, 0);
  addItem(p1, interchangeRadioButton, 2, 0);
  addItem(p1, saveButton, 1, 1);

  // group and set current track type
  _trackType = tef->_track->getTrackType();
  group->addButton(spurRadioButton);
  group->addButton(yardRadioButton);
  group->addButton(interchangeRadioButton);

  spurRadioButton->setChecked(_trackType==(Track::SPUR));
  yardRadioButton->setChecked(_trackType==(Track::YARD));
  interchangeRadioButton->setChecked(_trackType==(Track::INTERCHANGE));

  // Can not change staging tracks!
  saveButton->setEnabled(_trackType!=(Track::STAGING));

  // button action
  addButtonAction(saveButton);

  thisLayout->addWidget(p1);
  setTitle(tr("MenuItemChangeTrackType"));
  adjustSize();
  setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight100));
  setVisible(true);
 }

 /*public*/ void ChangeTrackFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         // check to see if button has changed
         if (spurRadioButton->isChecked() && _trackType!=(Track::SPUR)) {
             changeTrack(Track::SPUR);
         } else if (yardRadioButton->isChecked() && _trackType!=(Track::YARD)) {
             changeTrack(Track::YARD);
         } else if (interchangeRadioButton->isChecked() && _trackType!=(Track::INTERCHANGE)) {
             changeTrack(Track::INTERCHANGE);
         }
     }
 }

 /*private*/ void ChangeTrackFrame::changeTrack(QString type) {
     log->debug(tr("change track to %1").arg(type));
     _tef->_track->setTrackType(type);
     OperationsXml::save();
     _tef->dispose();
     dispose();
 }
/*public*/ QString ChangeTrackFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.ChangeTrackFrame";
}

}
