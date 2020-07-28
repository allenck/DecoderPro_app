#include "scheduleoptionsframe.h"
#include "operationsxml.h"
#include "setup.h"
#include "schedule.h"
#include <jtextfield.h>
#include "jcombobox.h"
#include <QBoxLayout>
#include <QPushButton>
#include "track.h"
#include "scheduleeditframe.h"
#include <QGroupBox>
#include "gridbaglayout.h"
#include "location.h"
#include "flowlayout.h"
#include "control.h"
#include <QIntValidator>
#include <QMessageBox>
#include <vptr.h>

namespace Operations
{
 /**
  * Action to launch schedule options.
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2011
  * @version $Revision: 28746 $
  */
 //class ScheduleOptionsFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -4111002798586670354L;


 /*public*/ ScheduleOptionsFrame::ScheduleOptionsFrame(ScheduleEditFrame* sef)
     : OperationsFrame(sef)
 {
  //super();
  // text field
  factorTextField = new JTextField(5);
  factorTextField->setValidator(new QIntValidator(0,1000));
  // combo boxes
  trackBox = new JComboBox();

  // radio buttons
  // major buttons
  saveButton = new QPushButton(tr("Save"));

  // the following code sets the frame's initial state
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  _track = sef->_track;

  // load the panel
  // row 1
  QGroupBox* pFactor = new QGroupBox();
  pFactor->setLayout(new GridBagLayout());
  //pFactor.setBorder(BorderFactory.createTitledBorder(tr("ScheduleFactor")));
  pFactor->setStyleSheet(gbStyleSheet);
  pFactor->setTitle("Schedule Factor");
  addItem(pFactor, factorTextField, 0, 0);

  factorTextField->setToolTip(tr("Default is 100% of custom loads from staging"));
  factorTextField->setText(QString::number(_track->getReservationFactor()));

  // row 2
  QGroupBox* pAlternate = new QGroupBox();
  pAlternate->setLayout(new GridBagLayout());
  //pAlternate.setBorder(BorderFactory.createTitledBorder(tr("AlternateTrack")));
  pAlternate->setStyleSheet(gbStyleSheet);
  pAlternate->setTitle("Alternate Track");
  addItem(pAlternate, trackBox, 0, 0);

  _track->getLocation()->updateComboBox(trackBox);
  trackBox->removeItem(trackBox->findText(_track->toString())); // remove this track from consideration
  trackBox->setCurrentIndex(trackBox->findText(_track->getAlternateTrack()->toString()));

  QWidget* pControls = new QWidget();
  pControls->setLayout(new FlowLayout);
  pControls->layout()->addWidget(saveButton);

  // button action
  addButtonAction(saveButton);

  thisLayout->addWidget(pFactor);
  thisLayout->addWidget(pAlternate);
  thisLayout->addWidget(pControls);

  setTitle(tr("Schedule Options"));
  adjustSize();
  setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight200));
  setVisible(true);
 }

 /*public*/ void ScheduleOptionsFrame::buttonActionPerformed(QWidget* ae)
{
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         // confirm that factor is between 0 and 1000
         bool ok;
             int factor = factorTextField->text().toInt(&ok);
             if (factor < 0 || factor > 1000) {
//                 JOptionPane.showMessageDialog(this, tr("FactorMustBeNumber"),
//                         tr("ErrorFactor"), JOptionPane.ERROR_MESSAGE);
                 return;
             }
         if(!ok) {
//             JOptionPane.showMessageDialog(this, tr("FactorMustBeNumber"),
//                     tr("ErrorFactor"), JOptionPane.ERROR_MESSAGE);
             return;
         }
         _track->setReservationFactor(factorTextField->text().toInt());
         if (trackBox->currentText() != NULL && trackBox->currentText()!=(Location::NONE)) {
             _track->setAlternateTrack((Track*) VPtr<Track>::asPtr(trackBox->currentData()));
         } else {
             _track->setAlternateTrack(NULL);
         }
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }
/*public*/ QString ScheduleOptionsFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.schedules.ScheduleOptionsFrame";
}

}
