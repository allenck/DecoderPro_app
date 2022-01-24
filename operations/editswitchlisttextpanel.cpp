#include "editswitchlisttextpanel.h"
#include <QPushButton>
#include "jtextfield.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "operationssetupxml.h"
#include "jpanel.h"
#include <QScrollArea>
#include "trainswitchlisttext.h"
#include "setup.h"
#include "instancemanager.h"
#include "borderfactory.h"

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
  JPanel* pSwitchListFrame = new JPanel;
  QWidget* pSwitchList = new QWidget();
  QScrollArea* pSwitchListPane = new QScrollArea(/*pSwitchList*/);
  pSwitchListFrame->setBorder(BorderFactory::createTitledBorder(tr("Switch List Text")));
  pSwitchListPane->setWidgetResizable(true);
  pSwitchListFrame->setLayout(new QVBoxLayout);
  pSwitchListFrame->layout()->addWidget(pSwitchListPane);
  pSwitchList->setLayout(new QHBoxLayout);//(pSwitchList, BoxLayout.Y_AXIS));

  JPanel* pSwitchListForTextField = new JPanel();
  pSwitchListForTextField->setBorder(BorderFactory::createTitledBorder(tr("Switch List for %0").arg("%0")));
  pSwitchListForTextField->layout()->addWidget(switchListForTextField);
  switchListForTextField->setText(TrainSwitchListText::getStringSwitchListFor());
  switchListForTextField->setToolTip(tr("1 = Location name."));
  pSwitchList->layout()->addWidget(pSwitchListForTextField);

  JPanel* pScheduledWorkTextField = new JPanel();
  pScheduledWorkTextField->setBorder(BorderFactory::createTitledBorder(tr("Scheduled work for train (%1) %2").arg("%1").arg("%2")));
  pScheduledWorkTextField->layout()->addWidget(scheduledWorkTextField);
  scheduledWorkTextField->setText(TrainSwitchListText::getStringScheduledWork());
  scheduledWorkTextField->setToolTip(tr("1 = Train name. 2 = Train description."));
  pSwitchList->layout()->addWidget(pScheduledWorkTextField);

  JPanel* pDepartsAtTextField = new JPanel();
  pDepartsAtTextField->setBorder(BorderFactory::createTitledBorder(tr("Departs %1 %2bound at %3").arg("%1").arg("%2").arg("%3")));
  pDepartsAtTextField->layout()->addWidget(departsAtTextField);
  departsAtTextField->setText(TrainSwitchListText::getStringDepartsAt());
  departsAtTextField->setToolTip(tr("1 = Location name. 2 = Train direction. 3 = Time."));
  pSwitchList->layout()->addWidget(pDepartsAtTextField);

  JPanel* pDepartsAtExpectedArrivalTextField = new JPanel();
  pDepartsAtExpectedArrivalTextField->setBorder(BorderFactory::createTitledBorder(tr("Departs %1 at %2 expected arrival %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4")));
  pDepartsAtExpectedArrivalTextField->layout()->addWidget(departsAtExpectedArrivalTextField);
  departsAtExpectedArrivalTextField->setText(TrainSwitchListText::getStringDepartsAtExpectedArrival());
  pSwitchList->layout()->addWidget(pDepartsAtExpectedArrivalTextField);

  JPanel* pDepartedExpectedTextField = new JPanel();
  pDepartedExpectedTextField->setBorder(BorderFactory::createTitledBorder(tr("Departed %1, expect to arrive in %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4")));
  pDepartedExpectedTextField->layout()->addWidget(departedExpectedTextField);
  departedExpectedTextField->setText(TrainSwitchListText::getStringDepartedExpected());
  pSwitchList->layout()->addWidget(pDepartedExpectedTextField);

  JPanel* pVisitNumber = new JPanel();
  pVisitNumber->setBorder(BorderFactory::createTitledBorder(tr("Visit number %1 for train (%2) expected arrival %3, arrives %4bound").arg("%1").arg("%2").arg("%3").arg("%4")));
  pVisitNumber->layout()->addWidget(visitNumberTextField);
  visitNumberTextField->setText(TrainSwitchListText::getStringVisitNumber());
  visitNumberTextField->setToolTip(tr("1 = Visit Number. 2 = Train name. 3 = Time. 4 = Train direction. 5 = Train description."));
  pSwitchList->layout()->addWidget(pVisitNumber);

  JPanel* pVisitNumberDeparted = new JPanel();
  pVisitNumberDeparted->setBorder(BorderFactory::createTitledBorder(tr("Visit number %1 for train (%2) expect to arrive in %3, arrives %4bound")));
  pVisitNumberDeparted->layout()->addWidget(visitNumberDepartedTextField);
  visitNumberDepartedTextField->setText(TrainSwitchListText::getStringVisitNumberDeparted());
  visitNumberDepartedTextField->setToolTip(tr("1 = Visit Number. 2 = Train name. 3 = Time. 4 = Train direction. 5 = Train description."));
  pSwitchList->layout()->addWidget(pVisitNumberDeparted);

  JPanel* pVisitNumberTerminates = new JPanel();
  pVisitNumberTerminates->setBorder(BorderFactory::createTitledBorder(tr("Visit number %1 for train (%2) expected arrival %3, terminates %4")));
  pVisitNumberTerminates->layout()->addWidget(visitNumberTerminatesTextField);
  visitNumberTerminatesTextField->setText(TrainSwitchListText::getStringVisitNumberTerminates());
  pSwitchList->layout()->addWidget(pVisitNumberTerminates);

  JPanel* pVisitNumberTerminatesDepartedTextField = new JPanel();
  pVisitNumberTerminatesDepartedTextField->setBorder(BorderFactory::createTitledBorder(tr("Visit number %1 for train (%2) expect to arrive in %3, terminates %4")));
  pVisitNumberTerminatesDepartedTextField->layout()->addWidget(visitNumberTerminatesDepartedTextField);
  visitNumberTerminatesDepartedTextField->setText(TrainSwitchListText::getStringVisitNumberTerminatesDeparted());
  pSwitchList->layout()->addWidget(pVisitNumberTerminatesDepartedTextField);

  JPanel* pVisitNumberDone = new JPanel();
  pVisitNumberDone->setBorder(BorderFactory::createTitledBorder(tr("Visit number %1 for train (%2)")));
  pVisitNumberDone->layout()->addWidget(visitNumberDoneTextField);
  visitNumberDoneTextField->setText(TrainSwitchListText::getStringVisitNumberDone());
  pSwitchList->layout()->addWidget(pVisitNumberDone);

  JPanel* pTrainDirectionChange = new JPanel();
  pTrainDirectionChange->setBorder(BorderFactory::createTitledBorder(tr("Train (%1) direction change, departs %2bound").arg("%1").arg("%2")));
  pTrainDirectionChange->layout()->addWidget(trainDirectionChangeTextField);
  trainDirectionChangeTextField->setText(TrainSwitchListText::getStringTrainDirectionChange());
  trainDirectionChangeTextField->setToolTip(tr("1 = Train name. 2 = Train direction. 3 = Train description. 4 = Terminal name."));
  pSwitchList->layout()->addWidget(pTrainDirectionChange);

  JPanel* pNoCarPickUps = new JPanel();
  pNoCarPickUps->setBorder(BorderFactory::createTitledBorder(tr("No car pick ups for train (%1) at this location").arg("%1")));
  pNoCarPickUps->layout()->addWidget(noCarPickUpsTextField);
  noCarPickUpsTextField->setText(TrainSwitchListText::getStringNoCarPickUps());
  noCarPickUpsTextField->setToolTip(tr("1 = Train name. 2 = Train description. 3 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pNoCarPickUps);

  JPanel* pNoCarDrops = new JPanel();
  pNoCarDrops->setBorder(BorderFactory::createTitledBorder(tr("No car set outs for train (%1) at this location")));
  pNoCarDrops->layout()->addWidget(noCarDropsTextField);
  noCarDropsTextField->setText(TrainSwitchListText::getStringNoCarDrops());
  noCarDropsTextField->setToolTip(tr("0 = Train name. 1 = Train description. 2 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pNoCarDrops);

  JPanel* pTrainDone = new JPanel();
  pTrainDone->setBorder(BorderFactory::createTitledBorder(tr("Train ({0}) has serviced this location")));
  pTrainDone->layout()->addWidget(trainDoneTextField);
  trainDoneTextField->setText(TrainSwitchListText::getStringTrainDone());
  trainDoneTextField->setToolTip(tr("0 = Train name. 1 = Train description. 2 = Location name.").arg("%1").arg("%2").arg("%3"));
  pSwitchList->layout()->addWidget(pTrainDone);

  JPanel* pTrainDepartsCars = new JPanel();
  pTrainDepartsCars->setBorder(BorderFactory::createTitledBorder(tr("Train departs %1 %2 with %3 cars, %4 %5, %6 tons")));
  pTrainDepartsCars->layout()->addWidget(trainDepartsCarsTextField);
  trainDepartsCarsTextField->setText(TrainSwitchListText::getStringTrainDepartsCars());
  trainDepartsCarsTextField->setToolTip(tr("1 = Location name. 2 = Train direction. 4 = Train length. 5 = feet or meters. 6 = Train weight. 7 = Terminal name. 8 = Train name."));
  pSwitchList->layout()->addWidget(pTrainDepartsCars);

  JPanel* pTrainDepartsLoadsTextField = new JPanel();
  pTrainDepartsLoadsTextField->setBorder(BorderFactory::createTitledBorder(tr("Train departs %1 %2 with %3 loads, %4 %5, %6 tons")));
  pTrainDepartsLoadsTextField->layout()->addWidget(trainDepartsLoadsTextField);
  trainDepartsLoadsTextField->setText(TrainSwitchListText::getStringTrainDepartsLoads());
  trainDepartsLoadsTextField->setToolTip(tr("0 = Location name. 1 = Train direction. 4 = Train length. 5 = feet or meters. 6 = Train weight. 7 = Terminal name. 8 = Train name."));
  pSwitchList->layout()->addWidget(pTrainDepartsLoadsTextField);

  JPanel* pSwitchListByTrackTextField = new JPanel();
  pSwitchListByTrackTextField->setBorder(BorderFactory::createTitledBorder(tr("Switch List by Track")));
  pSwitchListByTrackTextField->layout()->addWidget(switchListByTrackTextField);
  switchListByTrackTextField->setText(TrainSwitchListText::getStringSwitchListByTrack());
  switchListByTrackTextField->setToolTip(tr("1 = Location name."));
  pSwitchList->layout()->addWidget(pSwitchListByTrackTextField);

  JPanel* pHoldCarTextField = new JPanel();
  pHoldCarTextField->setBorder(BorderFactory::createTitledBorder(tr("Hold %1 %2 %3").arg("%1").arg("%2").arg("%3").arg("%4")));
  pHoldCarTextField->layout()->addWidget(holdCarTextField);
  holdCarTextField->setText(TrainSwitchListText::getStringHoldCar());
  holdCarTextField->setToolTip(tr("1 = Road. 2 = Number. 3 = Type. 4 = Length. 5 = Load. 6 = Track name. 7 = Color."));
  pSwitchList->layout()->addWidget(pHoldCarTextField);

  // add tool tips
  saveButton->setToolTip(tr("Writes this window's settings to file"));

  // row 11
  JPanel* pControl = new JPanel();
  pControl->setBorder(BorderFactory::createTitledBorder(""));
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
