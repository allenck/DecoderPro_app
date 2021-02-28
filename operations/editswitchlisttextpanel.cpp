#include "editswitchlisttextpanel.h"
#include <QPushButton>
#include "jtextfield.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "operationssetupxml.h"
#include <QGroupBox>
#include <QScrollArea>
#include "trainswitchlisttext.h"
#include "setup.h"
#include "instancemanager.h"

namespace Operations
{

 /**
  * Frame for user edit of switch list text strings
  *
  * @author Dan Boudreau Copyright (C) 2013
  * @version $Revision: 21846 $
  */
 ///*public*/ class EditSwitchListTextPanel extends OperationsPreferencesPanel {

 /**
  *
  */
 //private static final long serialVersionUID = -1972541065567773705L;
//    private static final Logger log = LoggerFactory.getLogger(EditSwitchListTextPanel.class);

// protected static final ResourceBundle rb = ResourceBundle
//         .getBundle("jmri.jmrit.operations.trains.JmritOperationsTrainsBundle");


 /*public*/ EditSwitchListTextPanel::EditSwitchListTextPanel(QWidget* parent)
   : OperationsPreferencesPanel(parent)
 {
  // major buttons
  saveButton = new QPushButton(tr("Save"));
  resetButton = new QPushButton(tr("Reset"));

  // text fields
  switchListForTextField = new JTextField(60);
  scheduledWorkTextField = new JTextField(60);

  departsAtTextField = new JTextField(60);
  departsAtExpectedArrivalTextField = new JTextField(60);
  departedExpectedTextField = new JTextField(60);

  visitNumberTextField = new JTextField(60);
  visitNumberDepartedTextField = new JTextField(60);
  visitNumberTerminatesTextField = new JTextField(60);
  visitNumberTerminatesDepartedTextField = new JTextField(60);
  visitNumberDoneTextField = new JTextField(60);

  trainDirectionChangeTextField = new JTextField(60);
  noCarPickUpsTextField = new JTextField(60);
  noCarDropsTextField = new JTextField(60);
  trainDoneTextField = new JTextField(60);
  trainDepartsCarsTextField = new JTextField(60);
  trainDepartsLoadsTextField = new JTextField(60);

  switchListByTrackTextField = new JTextField(60);
  holdCarTextField = new JTextField(60);

  // the following code sets the frame's initial state
  setLayout(new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

  // manifest text fields
  QGroupBox* pSwitchListFrame = new QGroupBox;
  QWidget* pSwitchList = new QWidget();
  QScrollArea* pSwitchListPane = new QScrollArea(/*pSwitchList*/);
  //pSwitchListPane->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutSwitchList")));
  pSwitchListFrame->setStyleSheet(gbStyleSheet);
  pSwitchListFrame->setTitle(tr("Switch List Text"));
  pSwitchListPane->setWidgetResizable(true);
  pSwitchListFrame->setLayout(new QVBoxLayout);
  pSwitchListFrame->layout()->addWidget(pSwitchListPane);
  pSwitchList->setLayout(new QHBoxLayout);//(pSwitchList, BoxLayout.Y_AXIS));

  QGroupBox* pSwitchListForTextField = new QGroupBox();
//  pSwitchListForTextField->setBorder(BorderFactory.createTitledBorder(rb
//          .getString("SwitchListFor")));
  pSwitchListForTextField->setStyleSheet(gbStyleSheet);
  pSwitchListForTextField->setTitle(tr("Switch List for %0").arg("%0"));
  pSwitchListForTextField->layout()->addWidget(switchListForTextField);
  switchListForTextField->setText(TrainSwitchListText::getStringSwitchListFor());
  switchListForTextField->setToolTip(tr("1 = Location name."));
  pSwitchList->layout()->addWidget(pSwitchListForTextField);

  QGroupBox* pScheduledWorkTextField = new QGroupBox();
  //pScheduledWorkTextField->setBorder(BorderFactory.createTitledBorder(tr("ScheduledWork")));
  pScheduledWorkTextField->setStyleSheet(gbStyleSheet);
  pScheduledWorkTextField->setTitle(tr("Scheduled work for train (%1) %2").arg("%1").arg("%2"));
  pScheduledWorkTextField->layout()->addWidget(scheduledWorkTextField);
  scheduledWorkTextField->setText(TrainSwitchListText::getStringScheduledWork());
  scheduledWorkTextField->setToolTip(tr("1 = Train name. 2 = Train description."));
  pSwitchList->layout()->addWidget(pScheduledWorkTextField);

  QGroupBox* pDepartsAtTextField = new QGroupBox();
//  pDepartsAtTextField->setBorder(BorderFactory.createTitledBorder(rb
//          .getString("DepartsAt")));
  pDepartsAtTextField->setStyleSheet(gbStyleSheet);
  pDepartsAtTextField->setTitle(tr("Departs %1 %2bound at %3").arg("%1").arg("%2").arg("%3"));
  pDepartsAtTextField->layout()->addWidget(departsAtTextField);
  departsAtTextField->setText(TrainSwitchListText::getStringDepartsAt());
  departsAtTextField->setToolTip(tr("1 = Location name. 2 = Train direction. 3 = Time."));
  pSwitchList->layout()->addWidget(pDepartsAtTextField);

  QGroupBox* pDepartsAtExpectedArrivalTextField = new QGroupBox();
//  pDepartsAtExpectedArrivalTextField
//          ->setBorder(BorderFactory.createTitledBorder(tr("DepartsAtExpectedArrival")));
  pDepartsAtExpectedArrivalTextField->setStyleSheet(gbStyleSheet);
  pDepartsAtExpectedArrivalTextField->setTitle(tr("Departs %1 at %2 expected arrival %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4"));
  pDepartsAtExpectedArrivalTextField->layout()->addWidget(departsAtExpectedArrivalTextField);
  departsAtExpectedArrivalTextField->setText(TrainSwitchListText::getStringDepartsAtExpectedArrival());
  pSwitchList->layout()->addWidget(pDepartsAtExpectedArrivalTextField);

  QGroupBox* pDepartedExpectedTextField = new QGroupBox();
//  pDepartedExpectedTextField->setBorder(BorderFactory.createTitledBorder(rb
//          .getString("DepartedExpected")));
  pDepartedExpectedTextField->setStyleSheet(gbStyleSheet);
  pDepartedExpectedTextField->setTitle(tr("Departed %1, expect to arrive in %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4"));
  pDepartedExpectedTextField->layout()->addWidget(departedExpectedTextField);
  departedExpectedTextField->setText(TrainSwitchListText::getStringDepartedExpected());
  pSwitchList->layout()->addWidget(pDepartedExpectedTextField);

  QGroupBox* pVisitNumber = new QGroupBox();
//  pVisitNumber->setBorder(BorderFactory.createTitledBorder(tr("VisitNumber")));
  pVisitNumber->setStyleSheet(gbStyleSheet);
  pVisitNumber->setTitle(tr("Visit number %1 for train (%2) expected arrival %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4"));
  pVisitNumber->layout()->addWidget(visitNumberTextField);
  visitNumberTextField->setText(TrainSwitchListText::getStringVisitNumber());
  visitNumberTextField->setToolTip(tr("1 = Visit Number. 2 = Train name. 3 = Time. 4 = Train direction. 5 = Train description."));
  pSwitchList->layout()->addWidget(pVisitNumber);

  QGroupBox* pVisitNumberDeparted = new QGroupBox();
  //pVisitNumberDeparted->setBorder(BorderFactory.createTitledBorder(tr("VisitNumberDeparted")));
  pVisitNumberDeparted->setStyleSheet(gbStyleSheet);
  pVisitNumberDeparted->setTitle(tr("Visit number %1 for train (%2) expect to arrive in %3, arrives %4bound"));
  pVisitNumberDeparted->layout()->addWidget(visitNumberDepartedTextField);
  visitNumberDepartedTextField->setText(TrainSwitchListText::getStringVisitNumberDeparted());
  visitNumberDepartedTextField->setToolTip(tr("1 = Visit Number. 2 = Train name. 3 = Time. 4 = Train direction. 5 = Train description."));
  pSwitchList->layout()->addWidget(pVisitNumberDeparted);

  QGroupBox* pVisitNumberTerminates = new QGroupBox();
  //pVisitNumberTerminates->setBorder(BorderFactory.createTitledBorder(tr("VisitNumberTerminates")));
  pVisitNumberTerminates->setStyleSheet(gbStyleSheet);
  pVisitNumberTerminates->setTitle(tr("Visit number %1 for train (%2) expected arrival %3, terminates %4"));
  pVisitNumberTerminates->layout()->addWidget(visitNumberTerminatesTextField);
  visitNumberTerminatesTextField->setText(TrainSwitchListText::getStringVisitNumberTerminates());
  pSwitchList->layout()->addWidget(pVisitNumberTerminates);

  QGroupBox* pVisitNumberTerminatesDepartedTextField = new QGroupBox();
//  pVisitNumberTerminatesDepartedTextField->setBorder(BorderFactory.createTitledBorder(rb
//          .getString("VisitNumberTerminatesDeparted")));
  pVisitNumberTerminatesDepartedTextField->layout()->addWidget(visitNumberTerminatesDepartedTextField);
  visitNumberTerminatesDepartedTextField->setText(TrainSwitchListText::getStringVisitNumberTerminatesDeparted());
  pSwitchList->layout()->addWidget(pVisitNumberTerminatesDepartedTextField);

  QGroupBox* pVisitNumberDone = new QGroupBox();
  //pVisitNumberDone->setBorder(BorderFactory.createTitledBorder(tr("VisitNumberDone")));
  pVisitNumberDone->layout()->addWidget(visitNumberDoneTextField);
  visitNumberDoneTextField->setText(TrainSwitchListText::getStringVisitNumberDone());
  pSwitchList->layout()->addWidget(pVisitNumberDone);

  QGroupBox* pTrainDirectionChange = new QGroupBox();
  //pTrainDirectionChange->setBorder(BorderFactory.createTitledBorder(tr("TrainDirectionChange")));
  pTrainDirectionChange->setStyleSheet(gbStyleSheet);
  pTrainDirectionChange->setTitle(tr("Train (%1) direction change, departs %2bound").arg("%1").arg("%2"));
  pTrainDirectionChange->layout()->addWidget(trainDirectionChangeTextField);
  trainDirectionChangeTextField->setText(TrainSwitchListText::getStringTrainDirectionChange());
  trainDirectionChangeTextField->setToolTip(tr("1 = Train name. 2 = Train direction. 3 = Train description. 4 = Terminal name."));
  pSwitchList->layout()->addWidget(pTrainDirectionChange);

  QGroupBox* pNoCarPickUps = new QGroupBox();
  //pNoCarPickUps->setBorder(BorderFactory.createTitledBorder(tr("NoCarPickUps")));
  pNoCarPickUps->setStyleSheet(gbStyleSheet);
  pNoCarPickUps->setTitle(tr("No car pick ups for train (%1) at this location").arg("%1"));
  pNoCarPickUps->layout()->addWidget(noCarPickUpsTextField);
  noCarPickUpsTextField->setText(TrainSwitchListText::getStringNoCarPickUps());
  noCarPickUpsTextField->setToolTip(tr("1 = Train name. 2 = Train description. 3 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pNoCarPickUps);

  QGroupBox* pNoCarDrops = new QGroupBox();
  //pNoCarDrops->setBorder(BorderFactory.createTitledBorder(tr("NoCarDrops")));
  pNoCarDrops->setStyleSheet(gbStyleSheet);
  pNoCarDrops->setTitle(tr(""));
  pNoCarDrops->layout()->addWidget(noCarDropsTextField);
  noCarDropsTextField->setText(TrainSwitchListText::getStringNoCarDrops());
  noCarDropsTextField->setToolTip(tr("0 = Train name. 1 = Train description. 2 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pNoCarDrops);

  QGroupBox* pTrainDone = new QGroupBox();
  //pTrainDone->setBorder(BorderFactory.createTitledBorder(tr("TrainDone")));
  pTrainDone->setStyleSheet(gbStyleSheet);
  pTrainDone->setTitle(tr(""));
  pTrainDone->layout()->addWidget(trainDoneTextField);
  trainDoneTextField->setText(TrainSwitchListText::getStringTrainDone());
  trainDoneTextField->setToolTip(tr("0 = Train name. 1 = Train description. 2 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pTrainDone);

  QGroupBox* pTrainDepartsCars = new QGroupBox();
  //pTrainDepartsCars->setBorder(BorderFactory.createTitledBorder(tr("TrainDepartsCars")));
  pTrainDepartsCars->setStyleSheet(gbStyleSheet);
  pTrainDepartsCars->setTitle(tr(""));
  pTrainDepartsCars->layout()->addWidget(trainDepartsCarsTextField);
  trainDepartsCarsTextField->setText(TrainSwitchListText::getStringTrainDepartsCars());
  trainDepartsCarsTextField->setToolTip(tr("1 = Location name. 2 = Train direction. 4 = Train length. 5 = feet or meters. 6 = Train weight. 7 = Terminal name. 8 = Train name."));
  pSwitchList->layout()->addWidget(pTrainDepartsCars);

  QGroupBox* pTrainDepartsLoadsTextField = new QGroupBox();
  //pTrainDepartsLoadsTextField->setBorder(BorderFactory.createTitledBorder(tr("TrainDepartsLoads")));
  pTrainDepartsLoadsTextField->setStyleSheet(gbStyleSheet);
  pTrainDepartsLoadsTextField->setTitle(tr(""));
  pTrainDepartsLoadsTextField->layout()->addWidget(trainDepartsLoadsTextField);
  trainDepartsLoadsTextField->setText(TrainSwitchListText::getStringTrainDepartsLoads());
  trainDepartsLoadsTextField->setToolTip(tr("0 = Location name. 1 = Train direction. 4 = Train length. 5 = feet or meters. 6 = Train weight. 7 = Terminal name. 8 = Train name."));
  pSwitchList->layout()->addWidget(pTrainDepartsLoadsTextField);

  QGroupBox* pSwitchListByTrackTextField = new QGroupBox();
  //pSwitchListByTrackTextField->setBorder(BorderFactory.createTitledBorder(tr("SwitchListByTrack")));
  pSwitchListByTrackTextField->setStyleSheet(gbStyleSheet);
  pSwitchListByTrackTextField->setTitle(tr(""));
  pSwitchListByTrackTextField->layout()->addWidget(switchListByTrackTextField);
  switchListByTrackTextField->setText(TrainSwitchListText::getStringSwitchListByTrack());
  switchListByTrackTextField->setToolTip(tr("1 = Location name."));
  pSwitchList->layout()->addWidget(pSwitchListByTrackTextField);

  QGroupBox* pHoldCarTextField = new QGroupBox();
  //pHoldCarTextField->setBorder(BorderFactory.createTitledBorder(tr("HoldCar")));
  pHoldCarTextField->setStyleSheet(gbStyleSheet);
  pHoldCarTextField->setTitle(tr("Hold %1 %2 %3").arg("%1").arg("%2").arg("%3").arg("%4"));
  pHoldCarTextField->layout()->addWidget(holdCarTextField);
  holdCarTextField->setText(TrainSwitchListText::getStringHoldCar());
  holdCarTextField->setToolTip(tr("1 = Road. 2 = Number. 3 = Type. 4 = Length. 5 = Load. 6 = Track name. 7 = Color."));
  pSwitchList->layout()->addWidget(pHoldCarTextField);

  // add tool tips
  saveButton->setToolTip(tr("Writes this window's settings to file"));

  // row 11
  QGroupBox* pControl = new QGroupBox();
  //pControl->setBorder(BorderFactory.createTitledBorder(""));
  pControl->setStyleSheet(gbStyleSheet);
  pControl->setLayout(new GridBagLayout());
  addItem(pControl, resetButton, 0, 0);
  addItem(pControl, saveButton, 1, 0);

  pSwitchListPane->setWidget(pSwitchList);
  layout()->addWidget(/*pSwitchListPane*/pSwitchListFrame);
  layout()->addWidget(pControl);

  // setup buttons
  addButtonAction(resetButton);
  addButtonAction(saveButton);

  initMinimumSize();
 }

 // Save buttons
 //@Override
 /*public*/ void EditSwitchListTextPanel::buttonActionPerformed(QWidget* ae)
 {
 QPushButton* source = (QPushButton*)ae;
  if (source == resetButton) {
      switchListForTextField->setText(tr("Switch List for %1").arg("%1"));
      scheduledWorkTextField->setText(tr("Scheduled work for train (%1) %2").arg("%1").arg("%2"));

      departsAtTextField->setText(tr("Departs %1 %2bound at %3").arg("%1").arg("%2").arg("%3"));
      departsAtExpectedArrivalTextField->setText(tr("Departs %1 at %2 expected arrival %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4"));
      departedExpectedTextField->setText(tr("Departed %1, expect to arrive in %2, arrives %3bound").arg("%1").arg("%2").arg("%3"));

      visitNumberTextField->setText(tr("VisitNumber"));
      visitNumberDepartedTextField->setText(tr("Visit number %1 for train (%2) expect to arrive in%3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4"));
      visitNumberTerminatesTextField->setText(tr("Visit number %1 for train (%2) expected arrival %3, terminates %4").arg("%1").arg("%2").arg("%3").arg("%4"));
      visitNumberTerminatesDepartedTextField->setText(tr("Visit number %1 for train (%2) expect to arrive in %3, terminates %4").arg("%1").arg("%2").arg("%3").arg("%4"));
      visitNumberDoneTextField->setText(tr("Visit number %1 for train (%2)").arg("%1").arg("%2"));

      trainDirectionChangeTextField->setText(tr("Visit number %1 for train (%2)").arg("%1").arg("%2"));
      noCarPickUpsTextField->setText(tr("No car pick ups for train (%1) at this location"));
      noCarDropsTextField->setText(tr("No car set outs for train (%1) at this location").arg("%1"));
      trainDoneTextField->setText(tr("Train (%1) has serviced this location"));
      trainDepartsCarsTextField->setText(tr("Train departs %1 %2bound with %3 cars, %4 %5, %6 tons").arg("%1").arg("%2").arg("%3").arg("%4").arg("%5").arg("%6"));
      trainDepartsLoadsTextField->setText(tr("Train departs %1 %2bound with %3 loads, %4 empties, %5 %6, %7 tons").arg("%1").arg("%2").arg("%3").arg("%4").arg("%5").arg("%6").arg("%7"));

      switchListByTrackTextField->setText(tr("Switch List by Track"));
      holdCarTextField->setText(tr("Hold %1 %2 %3").arg("%1").arg("%2").arg("%3"));
  }
  if (source == saveButton) {
      this->savePreferences();
      if (Setup::isCloseWindowOnSaveEnabled()) {
          dispose();
      }
  }
}
//@Override
/*public*/ QString EditSwitchListTextPanel::getTabbedPreferencesTitle() {
  return tr("Switch List Text");
}

//@Override
/*public*/ QString EditSwitchListTextPanel::getPreferencesTooltip() {
  return NULL;
}

//@Override
/*public*/ void EditSwitchListTextPanel::savePreferences() {
  TrainSwitchListText::setStringSwitchListFor(switchListForTextField->text());
  TrainSwitchListText::setStringScheduledWork(scheduledWorkTextField->text());

  TrainSwitchListText::setStringDepartsAt(departsAtTextField->text());
  TrainSwitchListText::setStringDepartsAtExpectedArrival(departsAtExpectedArrivalTextField->text());
  TrainSwitchListText::setStringDepartedExpected(departedExpectedTextField->text());

  TrainSwitchListText::setStringVisitNumber(visitNumberTextField->text());
  TrainSwitchListText::setStringVisitNumberDeparted(visitNumberDepartedTextField->text());
  TrainSwitchListText::setStringVisitNumberTerminates(visitNumberTerminatesTextField->text());
  TrainSwitchListText::setStringVisitNumberTerminatesDeparted(visitNumberTerminatesDepartedTextField->text());
  TrainSwitchListText::setStringVisitNumberDone(visitNumberDoneTextField->text());

  TrainSwitchListText::setStringTrainDirectionChange(trainDirectionChangeTextField->text());
  TrainSwitchListText::setStringNoCarPickUps(noCarPickUpsTextField->text());
  TrainSwitchListText::setStringNoCarDrops(noCarDropsTextField->text());
  TrainSwitchListText::setStringTrainDone(trainDoneTextField->text());
  TrainSwitchListText::setStringTrainDepartsCars(trainDepartsCarsTextField->text());
  TrainSwitchListText::setStringTrainDepartsLoads(trainDepartsLoadsTextField->text());

  TrainSwitchListText::setStringSwitchListByTrack(switchListByTrackTextField->text());
  TrainSwitchListText::setStringHoldCar(holdCarTextField->text());

  ((Operations::OperationsSetupXml*)InstanceManager::getDefault("OperationsSetupXml"))->writeOperationsFile();
 }

 //@Override
 /*public*/ bool EditSwitchListTextPanel::isDirty() {
     return (TrainSwitchListText::getStringSwitchListFor()==(switchListForTextField->text())
             || TrainSwitchListText::getStringScheduledWork()==(scheduledWorkTextField->text())
             || TrainSwitchListText::getStringDepartsAt()==(departsAtTextField->text())
             || TrainSwitchListText::getStringDepartsAtExpectedArrival()==(departsAtExpectedArrivalTextField->text())
             || TrainSwitchListText::getStringDepartedExpected()==(departedExpectedTextField->text())
             || TrainSwitchListText::getStringVisitNumber()==(visitNumberTextField->text())
             || TrainSwitchListText::getStringVisitNumberDeparted()==(visitNumberDepartedTextField->text())
             || TrainSwitchListText::getStringVisitNumberTerminates()==(visitNumberTerminatesTextField->text())
             || TrainSwitchListText::getStringVisitNumberTerminatesDeparted()==(visitNumberTerminatesDepartedTextField->text())
             || TrainSwitchListText::getStringVisitNumberDone()==(visitNumberDoneTextField->text())
             || TrainSwitchListText::getStringTrainDirectionChange()==(trainDirectionChangeTextField->text())
             || TrainSwitchListText::getStringNoCarPickUps()==(noCarPickUpsTextField->text())
             || TrainSwitchListText::getStringNoCarDrops()==(noCarDropsTextField->text())
             || TrainSwitchListText::getStringTrainDone()==(trainDoneTextField->text()))
             || TrainSwitchListText::getStringTrainDepartsCars()==(trainDepartsCarsTextField->text())
             || TrainSwitchListText::getStringTrainDepartsLoads()==(trainDepartsLoadsTextField->text())
             || TrainSwitchListText::getStringSwitchListByTrack()==(switchListByTrackTextField->text())
             || TrainSwitchListText::getStringHoldCar()==(holdCarTextField->text())
             ;
 }

}
