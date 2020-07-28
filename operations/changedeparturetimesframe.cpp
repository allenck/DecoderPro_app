#include "changedeparturetimesframe.h"
#include "schedule.h"
#include <QPushButton>
#include "jcombobox.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "gridbaglayout.h"
#include "flowlayout.h"
#include "control.h"
#include "train.h"
#include "trainmanager.h"
#include "routelocation.h"
#include "route.h"

namespace Operations
{
 /**
  * Change Departure Time frame for operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 17977 $
  */
 ///*public*/ class ChangeDepartureTimesFrame extends OperationsFrame {

 // labels
 // text field
 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -3038840373591772138L;

 // major buttons

 /*public*/ ChangeDepartureTimesFrame::ChangeDepartureTimesFrame(QWidget* parent)
: OperationsFrame(parent)
{
 changeButton = new QPushButton(tr("Change"));

// combo boxes
 hourBox = new JComboBox();
 log = new Logger("ChangeDepartureTimesFrame");
     // general GUI config

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Set up the panels
     // Layout the panel by rows
     for (int i = 1; i < 24; i++) {
         hourBox->addItem(QString::number(i));
     }

     // row 2
     QGroupBox* pHour = new QGroupBox();
     pHour->setLayout(new GridBagLayout());
     //pHour.setBorder(BorderFactory.createTitledBorder(tr("SelectHours")));
     pHour->setStyleSheet(gbStyleSheet);
     pHour->setTitle(tr("Select the hours to add to each train's departure time"));
     addItem(pHour, hourBox, 0, 0);

     // row 4
     QWidget* pButton = new QWidget();
     pButton->setLayout(new FlowLayout);
     pButton->layout()->addWidget(changeButton);

     thisLayout->addWidget(pHour);
     thisLayout->addWidget(pButton);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_ChangeTrainDepartureTimes", true); // NOI18N

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight200));

     setTitle(tr("TitleChangeDepartureTime"));

     // setup buttons
     addButtonAction(changeButton);
 }

 /*public*/ void ChangeDepartureTimesFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == changeButton) {
         log->debug("change button activated");
         TrainManager* trainManager = TrainManager::instance();
         QList<Train*> trains = trainManager->getTrainsByIdList();
         foreach (Train* train, trains) {
             train->setDepartureTime(adjustHour(train->getDepartureTimeHour()), train->getDepartureTimeMinute());
             // now check the train's route to see if there are any departure times that need to be modified
             if (train->getRoute() == NULL)
                 continue;
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 if (rl->getDepartureTime()!=(RouteLocation::NONE))
                     rl->setDepartureTime(adjustHour(rl->getDepartureTimeHour()), rl->getDepartureTimeMinute());
             }
         }
     }
 }

 /*private*/ QString ChangeDepartureTimesFrame::adjustHour(QString time) {
     int hour =  hourBox->currentText().toInt() + time.toInt();
     if (hour > 23) {
         hour = hour - 24;
     }
     return QString::number(hour);
 }
/*public*/ QString ChangeDepartureTimesFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.ChangeDepartureTimesFrame";
}

}
