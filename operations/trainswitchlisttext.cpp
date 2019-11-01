#include "trainswitchlisttext.h"
#include "xml.h"
#include <QtXml>

namespace Operations
{
 /**
  * Loads and stores the switch list text strings.
  *
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 21846 $
  *
  */
 ///*public*/ class TrainSwitchListText {
 /*private static*/ QString TrainSwitchListText:: switchListFor = tr("Switch List for %1");
 /*private static*/ QString TrainSwitchListText:: scheduledWork = tr("Scheduled work for train (%1) %2");

 /*private static*/ QString TrainSwitchListText:: departsAt = tr("Departs %1 %2bound at %3");
 /*private static*/ QString TrainSwitchListText:: departsAtExpectedArrival = tr("DepDeparted %1, expect to arrive in %2, arrives %3boundarts %1 at %2 expected arrival %3, arrives %4bound");
 /*private static*/ QString TrainSwitchListText:: departedExpected = tr("DepartedExpected");

 /*private static*/ QString TrainSwitchListText:: visitNumber = tr("Visit number %1 for train (%2) expected arrival %3, arrives %4bound");
 /*private static*/ QString TrainSwitchListText:: visitNumberDeparted = tr("VisitNumberDeparted");	// this get's appended to "no scheduled work at"
 /*private static*/ QString TrainSwitchListText:: visitNumberTerminates = tr("VisitNumberTerminates");
 /*private static*/ QString TrainSwitchListText:: visitNumberTerminatesDeparted = tr("VisitNumberTerminatesDeparted");
 /*private static*/ QString TrainSwitchListText:: visitNumberDone = tr("VisitNumberDone");

 /*private static*/ QString TrainSwitchListText:: trainDirectionChange = tr("Train (%1) direction change, departs %2bound");
 /*private static*/ QString TrainSwitchListText:: noCarPickUps = tr("No car pick ups for train (%1) at this location");
 /*private static*/ QString TrainSwitchListText:: noCarDrops = tr("No car set outs for train (%1) at this location");
 /*private static*/ QString TrainSwitchListText:: trainDone = tr("Train (%1) has serviced this location");

 /*private static*/ QString TrainSwitchListText:: trainDepartsCars = tr("Train departs %1 %2bound with %3 cars, %4 %5, %6 tons");
 /*private static*/ QString TrainSwitchListText:: trainDepartsLoads = tr("Train departs %1 %2bound with %3 loads, %4 empties, %5 %6, %7 tons");

 /*private static*/ QString TrainSwitchListText:: switchListByTrack = tr("Switch List by Track");
 /*private static*/ QString TrainSwitchListText:: holdCar = tr("Hold %1 %2 %3");



 /*public*/ /*static*/ QString TrainSwitchListText::getStringSwitchListFor() {
     return switchListFor;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringSwitchListFor(QString s) {
     switchListFor = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringScheduledWork() {
     return scheduledWork;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringScheduledWork(QString s) {
     scheduledWork = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringDepartsAt() {
     return departsAt;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringDepartsAt(QString s) {
     departsAt = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringDepartsAtExpectedArrival() {
     return departsAtExpectedArrival;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringDepartsAtExpectedArrival(QString s) {
     departsAtExpectedArrival = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringDepartedExpected() {
     return departedExpected;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringDepartedExpected(QString s) {
     departedExpected = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringVisitNumber() {
     return visitNumber;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringVisitNumber(QString s) {
     visitNumber = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringVisitNumberDeparted() {
     return visitNumberDeparted;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringVisitNumberDeparted(QString s) {
     visitNumberDeparted = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringVisitNumberTerminates() {
     return visitNumberTerminates;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringVisitNumberTerminates(QString s) {
     visitNumberTerminates = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringVisitNumberTerminatesDeparted() {
     return visitNumberTerminatesDeparted;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringVisitNumberTerminatesDeparted(QString s) {
     visitNumberTerminatesDeparted = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringVisitNumberDone() {
     return visitNumberDone;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringVisitNumberDone(QString s) {
     visitNumberDone = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringTrainDirectionChange() {
     return trainDirectionChange;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringTrainDirectionChange(QString s) {
     trainDirectionChange = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringNoCarPickUps() {
     return noCarPickUps;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringNoCarPickUps(QString s) {
     noCarPickUps = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringNoCarDrops() {
     return noCarDrops;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringNoCarDrops(QString s) {
     noCarDrops = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringTrainDone() {
     return trainDone;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringTrainDone(QString s) {
     trainDone = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringTrainDepartsCars() {
     return trainDepartsCars;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringTrainDepartsCars(QString s) {
     trainDepartsCars = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringTrainDepartsLoads() {
     return trainDepartsLoads;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringTrainDepartsLoads(QString s) {
     trainDepartsLoads = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringSwitchListByTrack() {
     return switchListByTrack;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringSwitchListByTrack(QString s) {
     switchListByTrack = s;
 }

 /*public*/ /*static*/ QString TrainSwitchListText::getStringHoldCar() {
     return holdCar;
 }

 /*public*/ /*static*/ void TrainSwitchListText::setStringHoldCar(QString s) {
     holdCar = s;
 }

 // must synchronize changes with operation-config.dtd
 /*public*/ /*static*/ QDomElement TrainSwitchListText::store(QDomDocument doc) {
     QDomElement values;
     QDomElement e = doc.createElement(Xml::SWITCH_LIST_TEXT_STRINGS);
     // only save strings that have been modified
     if (getStringSwitchListFor()!=(tr("SwitchListFor"))) {
         e.appendChild(values = doc.createElement(Xml::SWICH_LIST_FOR));
         values.setAttribute(Xml::TEXT, getStringSwitchListFor());
     }
     if (getStringScheduledWork()!=(tr("ScheduledWork"))) {
         e.appendChild(values = doc.createElement(Xml::SCHEDULED_WORK_TRAIN));
         values.setAttribute(Xml::TEXT, getStringScheduledWork());
     }

     if (getStringDepartsAt()!=(tr("DepartsAt"))) {
         e.appendChild(values = doc.createElement(Xml::DEPARTS_AT));
         values.setAttribute(Xml::TEXT, getStringDepartsAt());
     }
     if (getStringDepartsAtExpectedArrival()!=(tr("DepartsAtExpectedArrival"))) {
         e.appendChild(values = doc.createElement(Xml::DEPARTS_EXPECTED_ARRIVAL));
         values.setAttribute(Xml::TEXT, getStringDepartsAtExpectedArrival());
     }
     if (getStringDepartedExpected()!=(tr("DepartedExpected"))) {
         e.appendChild(values = doc.createElement(Xml::DEPARTED_EXPECTED));
         values.setAttribute(Xml::TEXT, getStringDepartedExpected());
     }

     if (getStringVisitNumber()!=(tr("VisitNumber"))) {
         e.appendChild(values = doc.createElement(Xml::VISIT_NUMBER));
         values.setAttribute(Xml::TEXT, getStringVisitNumber());
     }
     if (getStringVisitNumberDeparted()!=(tr("VisitNumberDeparted"))) {
         e.appendChild(values = doc.createElement(Xml::VISIT_NUMBER_DEPARTED));
         values.setAttribute(Xml::TEXT, getStringVisitNumberDeparted());
     }
     if (getStringVisitNumberTerminates()!=(tr("VisitNumberTerminates"))) {
         e.appendChild(values = doc.createElement(Xml::VISIT_NUMBER_TERMINATES));
         values.setAttribute(Xml::TEXT, getStringVisitNumberTerminates());
     }
     if (getStringVisitNumberTerminatesDeparted()!=(tr("VisitNumberTerminatesDeparted"))) {
         e.appendChild(values = doc.createElement(Xml::VISIT_NUMBER_TERMINATES_DEPARTED));
         values.setAttribute(Xml::TEXT, getStringVisitNumberTerminatesDeparted());
     }
     if (getStringVisitNumberDone()!=(tr("VisitNumberDone"))) {
         e.appendChild(values = doc.createElement(Xml::VISIT_NUMBER_DONE));
         values.setAttribute(Xml::TEXT, getStringVisitNumberDone());
     }

     if (getStringTrainDirectionChange()!=(tr("TrainDirectionChange"))) {
         e.appendChild(values = doc.createElement(Xml::TRAIN_DIRECTION_CHANGE));
         values.setAttribute(Xml::TEXT, getStringTrainDirectionChange());
     }
     if (getStringNoCarPickUps()!=(tr("NoCarPickUps"))) {
         e.appendChild(values = doc.createElement(Xml::NO_CAR_PICK_UPS));
         values.setAttribute(Xml::TEXT, getStringNoCarPickUps());
     }
     if (getStringNoCarDrops()!=(tr("NoCarDrops"))) {
         e.appendChild(values = doc.createElement(Xml::NO_CAR_SET_OUTS));
         values.setAttribute(Xml::TEXT, getStringNoCarDrops());
     }
     if (getStringTrainDone()!=(tr("TrainDone"))) {
         e.appendChild(values = doc.createElement(Xml::TRAIN_DONE));
         values.setAttribute(Xml::TEXT, getStringTrainDone());
     }
     if (getStringTrainDepartsCars()!=(tr("TrainDepartsCars"))) {
         e.appendChild(values = doc.createElement(Xml::TRAIN_DEPARTS_CARS));
         values.setAttribute(Xml::TEXT, getStringTrainDepartsCars());
     }
     if (getStringTrainDepartsLoads()!=(tr("TrainDepartsLoads"))) {
         e.appendChild(values = doc.createElement(Xml::TRAIN_DEPARTS_LOADS));
         values.setAttribute(Xml::TEXT, getStringTrainDepartsLoads());
     }
     if (getStringSwitchListByTrack()!=(tr("SwitchListByTrack"))) {
         e.appendChild(values = doc.createElement(Xml::SWITCH_LIST_TRACK));
         values.setAttribute(Xml::TEXT, getStringSwitchListByTrack());
     }
     if (getStringHoldCar()!=(tr("HoldCar"))) {
         e.appendChild(values = doc.createElement(Xml::HOLD_CAR));
         values.setAttribute(Xml::TEXT, getStringHoldCar());
     }

     return e;
 }

 /*public*/ /*static*/ void TrainSwitchListText::load(QDomElement e) {
     QDomElement emts = e.firstChildElement(Xml::SWITCH_LIST_TEXT_STRINGS);
     if (emts == QDomElement()) {
         return;
     }
     QString a;
     if (emts.firstChildElement(Xml::SWICH_LIST_FOR) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::SWICH_LIST_FOR).attribute(Xml::TEXT)) != NULL) {
             setStringSwitchListFor(a);
         }
     }
     if (emts.firstChildElement(Xml::SCHEDULED_WORK_TRAIN) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::SCHEDULED_WORK_TRAIN).attribute(Xml::TEXT)) != NULL) {
             setStringScheduledWork(a);
         }
     }

     if (emts.firstChildElement(Xml::DEPARTS_AT) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DEPARTS_AT).attribute(Xml::TEXT)) != NULL) {
             setStringDepartsAt(a);
         }
     }
     if (emts.firstChildElement(Xml::DEPARTS_EXPECTED_ARRIVAL) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DEPARTS_EXPECTED_ARRIVAL).attribute(Xml::TEXT)) != NULL) {
             setStringDepartsAtExpectedArrival(a);
         }
     }
     if (emts.firstChildElement(Xml::DEPARTED_EXPECTED) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::DEPARTED_EXPECTED).attribute(Xml::TEXT)) != NULL) {
             setStringDepartedExpected(a);
         }
     }

     if (emts.firstChildElement(Xml::VISIT_NUMBER) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::VISIT_NUMBER).attribute(Xml::TEXT)) != NULL) {
             setStringVisitNumber(a);
         }
     }
     if (emts.firstChildElement(Xml::VISIT_NUMBER_DEPARTED) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::VISIT_NUMBER_DEPARTED).attribute(Xml::TEXT)) != NULL) {
             setStringVisitNumberDeparted(a);
         }
     }
     if (emts.firstChildElement(Xml::VISIT_NUMBER_TERMINATES) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::VISIT_NUMBER_TERMINATES).attribute(Xml::TEXT)) != NULL) {
             setStringVisitNumberTerminates(a);
         }
     }
     if (emts.firstChildElement(Xml::VISIT_NUMBER_TERMINATES_DEPARTED) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::VISIT_NUMBER_TERMINATES_DEPARTED).attribute(Xml::TEXT)) != NULL) {
             setStringVisitNumberTerminatesDeparted(a);
         }
     }
     if (emts.firstChildElement(Xml::VISIT_NUMBER_DONE) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::VISIT_NUMBER_DONE).attribute(Xml::TEXT)) != NULL) {
             setStringVisitNumberDone(a);
         }
     }

     if (emts.firstChildElement(Xml::TRAIN_DIRECTION_CHANGE) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TRAIN_DIRECTION_CHANGE).attribute(Xml::TEXT)) != NULL) {
             setStringTrainDirectionChange(a);
         }
     }
     if (emts.firstChildElement(Xml::NO_CAR_PICK_UPS) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::NO_CAR_PICK_UPS).attribute(Xml::TEXT)) != NULL) {
             setStringNoCarPickUps(a);
         }
     }
     if (emts.firstChildElement(Xml::NO_CAR_SET_OUTS) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::NO_CAR_SET_OUTS).attribute(Xml::TEXT)) != NULL) {
             setStringNoCarDrops(a);
         }
     }
     if (emts.firstChildElement(Xml::TRAIN_DONE) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TRAIN_DONE).attribute(Xml::TEXT)) != NULL) {
             setStringTrainDone(a);
         }
     }
     if (emts.firstChildElement(Xml::TRAIN_DEPARTS_CARS) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TRAIN_DEPARTS_CARS).attribute(Xml::TEXT)) != NULL) {
             setStringTrainDepartsCars(a);
         }
     }
     if (emts.firstChildElement(Xml::TRAIN_DEPARTS_LOADS) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::TRAIN_DEPARTS_LOADS).attribute(Xml::TEXT)) != NULL) {
             setStringTrainDepartsLoads(a);
         }
     }
     if (emts.firstChildElement(Xml::SWITCH_LIST_TRACK) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::SWITCH_LIST_TRACK).attribute(Xml::TEXT)) != NULL) {
             setStringSwitchListByTrack(a);
         }
     }
     if (emts.firstChildElement(Xml::HOLD_CAR) != QDomElement()) {
         if ((a = emts.firstChildElement(Xml::HOLD_CAR).attribute(Xml::TEXT)) != NULL) {
             setStringHoldCar(a);
         }
     }
 }
}
