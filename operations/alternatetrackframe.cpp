#include "alternatetrackframe.h"
#include "track.h"
#include <QPushButton>
#include "jcombobox.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "trackeditframe.h"
#include <QGroupBox>
#include "location.h"
#include "vptr.h"
#include "flowlayout.h"
#include "control.h"
#include "operationsxml.h"
#include "setup.h"

namespace Operations
{
 /**
  * Action to launch selection of alternate track.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @version $Revision: 17977 $
  */
 //class AlternateTrackFrame extends OperationsFrame {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -9027155799954540567L;


 /*public*/ AlternateTrackFrame::AlternateTrackFrame(TrackEditFrame* tef, QWidget* parent) : OperationsFrame(parent){
     //super();
 trackBox = new JComboBox();

 saveButton = new QPushButton(tr("Save"));


     // the following code sets the frame's initial state
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     _track = tef->_track;

     // load the panel
     // row 2
     QGroupBox* pAlternate = new QGroupBox();
     pAlternate->setLayout(new GridBagLayout());
     //pAlternate.setBorder(BorderFactory.createTitledBorder(""));
     pAlternate->setStyleSheet(gbStyleSheet);
     addItem(pAlternate, trackBox, 0, 0);

     _track->getLocation()->updateComboBox(trackBox);
     trackBox->removeItem(trackBox->findData(VPtr<Track>::asQVariant(_track)));	// remove this track from consideration
     trackBox->setCurrentIndex(trackBox->findData(VPtr<Track>::asQVariant(_track->getAlternateTrack())));

     QWidget* pControls = new QWidget();
     pControls->setLayout(new FlowLayout);
     pControls->layout()->addWidget(saveButton);

     // button action
     addButtonAction(saveButton);

     thisLayout->addWidget(pAlternate);
     thisLayout->addWidget(pControls);

     setTitle(tr("Alternate Track"));
     adjustSize();
     setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight100));
     setVisible(true);
 }

 /*public*/ void AlternateTrackFrame::buttonActionPerformed(JActionEvent* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         _track->setAlternateTrack((Track*) VPtr<Track>::asPtr(trackBox->currentData()));
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 /*public*/ QString AlternateTrackFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.AlternateTrackFrame";
 }

}
