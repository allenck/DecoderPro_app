#include "trainmanifesttext.h"
#include "xml.h"
#include <QString>
#include <QtXml>

namespace Operations
{
/**
 * Loads and stores the manifest text strings.
 *
 * @author Daniel Boudreau Copyright (C) 2013
 *
 */
///*public*/ class TrainManifestText {

    /*private*/ /*static*/ QString TrainManifestText::manifestForTrain =  "Manifest for train (%1) %2";
    /*private*/ /*static*/ QString TrainManifestText::valid =  "Valid %1";
    /*private*/ /*static*/ QString TrainManifestText::scheduledWorkAt =  "Scheduled work at %1";
    /*private*/ /*static*/ QString TrainManifestText::departureTime =  "Scheduled work at %1, departure time %2";
    /*private*/ /*static*/ QString TrainManifestText::arrivalTime =  "Scheduled work at %1, arrival time %2";
    /*private*/ /*static*/ QString TrainManifestText::noScheduledWorkAt =  "No work at %1";
    /*private*/ /*static*/ QString TrainManifestText::noScheduledWorkAtRouteComment =  "%1, %2";
    /*private*/ /*static*/ QString TrainManifestText::departTime =  ", departure time %1";	// this get's appended to "no scheduled work at"
    /*private*/ /*static*/ QString TrainManifestText::trainDepartsCars =  "Train departs %1 %2bound with %3 cars, %4 %5, %6 tons";
    /*private*/ /*static*/ QString TrainManifestText::trainDepartsLoads =  "Train departs %1 %2bound with %3 loads, %4 empties, %5 %6, %7 tons";
    /*private*/ /*static*/ QString TrainManifestText::trainTerminatesIn =  "Train terminates in %1";

    /*private*/ /*static*/ QString TrainManifestText::destination =  "destination";
    /*private*/ /*static*/ QString TrainManifestText::from =  "from";
    /*private*/ /*static*/ QString TrainManifestText::to =  "to";

    /*private*/ /*static*/ QString TrainManifestText::fd =  "FD";
    /*private*/ /*static*/ QString TrainManifestText::dest =  "dest";

    /*private*/ /*static*/ QString TrainManifestText::addHelpersAt =  "Add helpers at %1";
    /*private*/ /*static*/ QString TrainManifestText::removeHelpersAt =  "Remove helpers at %1";
    /*private*/ /*static*/ QString TrainManifestText::locoChangeAt =  "Locomotive change at %1";
    /*private*/ /*static*/ QString TrainManifestText::cabooseChangeAt =  "Caboose change at %1";
    /*private*/ /*static*/ QString TrainManifestText::locoAndCabooseChangeAt =  "Locomotive and caboose change at %1";

    /*public*/ /*static*/ QString TrainManifestText::getStringManifestForTrain() {
        return manifestForTrain;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringManifestForTrain(QString s) {
        manifestForTrain = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringValid() {
        return valid;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringValid(QString s) {
        valid = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringScheduledWork() {
        return scheduledWorkAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringScheduledWork(QString s) {
        scheduledWorkAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringWorkDepartureTime() {
        return departureTime;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringWorkDepartureTime(QString s) {
        departureTime = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringWorkArrivalTime() {
        return arrivalTime;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringWorkArrivalTime(QString s) {
        arrivalTime = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringNoScheduledWork() {
        return noScheduledWorkAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringNoScheduledWork(QString s) {
        noScheduledWorkAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringNoScheduledWorkWithRouteComment() {
        return noScheduledWorkAtRouteComment;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringNoScheduledWorkWithRouteComment(QString s) {
        noScheduledWorkAtRouteComment = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringDepartTime() {
        return departTime;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringDepartTime(QString s) {
        departTime = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringTrainDepartsCars() {
        return trainDepartsCars;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringTrainDepartsCars(QString s) {
        trainDepartsCars = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringTrainDepartsLoads() {
        return trainDepartsLoads;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringTrainDepartsLoads(QString s) {
        trainDepartsLoads = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringTrainTerminates() {
        return trainTerminatesIn;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringTrainTerminates(QString s) {
        trainTerminatesIn = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringDestination() {
        return destination;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringDestination(QString s) {
        destination = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringFrom() {
        return from;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringFrom(QString s) {
        from = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringTo() {
        return to;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringTo(QString s) {
        to = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringDest() {
        return dest;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringDest(QString s) {
        dest = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringFinalDestination() {
        return fd;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringFinalDestination(QString s) {
        fd = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringAddHelpers() {
        return addHelpersAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringAddHelpers(QString s) {
        addHelpersAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringRemoveHelpers() {
        return removeHelpersAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringRemoveHelpers(QString s) {
        removeHelpersAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringLocoChange() {
        return locoChangeAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringLocoChange(QString s) {
        locoChangeAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringCabooseChange() {
        return cabooseChangeAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringCabooseChange(QString s) {
        cabooseChangeAt = s;
    }

    /*public*/ /*static*/ QString TrainManifestText::getStringLocoAndCabooseChange() {
        return locoAndCabooseChangeAt;
    }

    /*public*/ /*static*/ void TrainManifestText::setStringLocoAndCabooseChange(QString s) {
        locoAndCabooseChangeAt = s;
    }

    // must synchronize changes with operation-config.dtd
    /*public*/ /*static*/ QDomElement TrainManifestText::store(QDomDocument doc) {
        QDomElement values;
        QDomElement e = doc.createElement(Xml::MANIFEST_TEXT_STRINGS);
        // only save strings that have been modified
        if (getStringManifestForTrain()!=( "ManifestForTrain")) {
            e.appendChild(values = doc.createElement(Xml::MANIFEST_FOR_TRAIN));
            values.setAttribute(Xml::TEXT, getStringManifestForTrain());
        }
        if (getStringValid()!=( "Valid")) {
            e.appendChild(values = doc.createElement(Xml::VALID));
            values.setAttribute(Xml::TEXT, getStringValid());
        }
        if (getStringScheduledWork()!=( "ScheduledWorkAt")) {
            e.appendChild(values = doc.createElement(Xml::SCHEDULED_WORK));
            values.setAttribute(Xml::TEXT, getStringScheduledWork());
        }
        if (getStringWorkDepartureTime()!=( "WorkDepartureTime")) {
            e.appendChild(values = doc.createElement(Xml::WORK_DEPARTURE_TIME));
            values.setAttribute(Xml::TEXT, getStringWorkDepartureTime());
        }
        if (getStringWorkArrivalTime()!=( "WorkArrivalTime")) {
            e.appendChild(values = doc.createElement(Xml::WORK_ARRIVAL_TIME));
            values.setAttribute(Xml::TEXT, getStringWorkArrivalTime());
        }
        if (getStringNoScheduledWork()!=( "NoScheduledWorkAt")) {
            e.appendChild(values = doc.createElement(Xml::NO_SCHEDULED_WORK));
            values.setAttribute(Xml::TEXT, getStringNoScheduledWork());
        }
        if (getStringNoScheduledWorkWithRouteComment()!=( "NoScheduledWorkAtWithRouteComment")){
            e.appendChild(values = doc.createElement(Xml::NO_SCHEDULED_WORK_ROUTE_COMMENT));
            values.setAttribute(Xml::TEXT, getStringNoScheduledWorkWithRouteComment());
        }
        if (getStringDepartTime()!=( "departureTime")) {
            e.appendChild(values = doc.createElement(Xml::DEPART_TIME));
            values.setAttribute(Xml::TEXT, getStringDepartTime());
        }
        if (getStringTrainDepartsCars()!=( "TrainDepartsCars")) {
            e.appendChild(values = doc.createElement(Xml::TRAIN_DEPARTS_CARS));
            values.setAttribute(Xml::TEXT, getStringTrainDepartsCars());
        }
        if (getStringTrainDepartsLoads()!=( "TrainDepartsLoads")) {
            e.appendChild(values = doc.createElement(Xml::TRAIN_DEPARTS_LOADS));
            values.setAttribute(Xml::TEXT, getStringTrainDepartsLoads());
        }
        if (getStringTrainTerminates()!=( "TrainTerminatesIn")) {
            e.appendChild(values = doc.createElement(Xml::TRAIN_TERMINATES));
            values.setAttribute(Xml::TEXT, getStringTrainTerminates());
        }
        if (getStringDestination()!=( "destination")) {
            e.appendChild(values = doc.createElement(Xml::DESTINATION));
            values.setAttribute(Xml::TEXT, getStringDestination());
        }
        if (getStringFrom()!=( "from")) {
            e.appendChild(values = doc.createElement(Xml::FROM));
            values.setAttribute(Xml::TEXT, getStringFrom());
        }
        if (getStringTo()!=( "to")) {
            e.appendChild(values = doc.createElement(Xml::TO));
            values.setAttribute(Xml::TEXT, getStringTo());
        }
        if (getStringDest()!=( "dest")) {
            e.appendChild(values = doc.createElement(Xml::DEST));
            values.setAttribute(Xml::TEXT, getStringDest());
        }
        if (getStringFinalDestination()!=( "FD")) {
            e.appendChild(values = doc.createElement(Xml::FINAL_DEST));
            values.setAttribute(Xml::TEXT, getStringFinalDestination());
        }
        if (getStringAddHelpers()!=( "AddHelpersAt")) {
            e.appendChild(values = doc.createElement(Xml::ADD_HELPERS));
            values.setAttribute(Xml::TEXT, getStringAddHelpers());
        }
        if (getStringRemoveHelpers()!=( "RemoveHelpersAt")) {
            e.appendChild(values = doc.createElement(Xml::REMOVE_HELPERS));
            values.setAttribute(Xml::TEXT, getStringRemoveHelpers());
        }
        if (getStringLocoChange()!=( "LocoChangeAt")) {
            e.appendChild(values = doc.createElement(Xml::LOCO_CHANGE));
            values.setAttribute(Xml::TEXT, getStringLocoChange());
        }
        if (getStringCabooseChange()!=( "CabooseChangeAt")) {
            e.appendChild(values = doc.createElement(Xml::CABOOSE_CHANGE));
            values.setAttribute(Xml::TEXT, getStringCabooseChange());
        }
        if (getStringLocoAndCabooseChange()!=( "LocoAndCabooseChangeAt")) {
            e.appendChild(values = doc.createElement(Xml::LOCO_CABOOSE_CHANGE));
            values.setAttribute(Xml::TEXT, getStringLocoAndCabooseChange());
        }

        return e;
    }

    /*public*/ /*static*/ void TrainManifestText::load(QDomElement e) {
        QDomElement emts = e.firstChildElement(Xml::MANIFEST_TEXT_STRINGS);
        if (emts.isNull()) {
            return;
        }
        QString a;
        if (emts.firstChildElement(Xml::MANIFEST_FOR_TRAIN) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::MANIFEST_FOR_TRAIN).attribute(Xml::TEXT)) != "") {
                setStringManifestForTrain(a);
            }
        }
        if (emts.firstChildElement(Xml::VALID) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::VALID).attribute(Xml::TEXT)) != NULL) {
                setStringValid(a);
            }
        }
        if (emts.firstChildElement(Xml::SCHEDULED_WORK) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::SCHEDULED_WORK).attribute(Xml::TEXT)) != NULL) {
                setStringScheduledWork(a);
            }
        }
        if (emts.firstChildElement(Xml::WORK_DEPARTURE_TIME) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::WORK_DEPARTURE_TIME).attribute(Xml::TEXT)) != NULL) {
                setStringWorkDepartureTime(a);
            }
        }
        if (emts.firstChildElement(Xml::WORK_ARRIVAL_TIME) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::WORK_ARRIVAL_TIME).attribute(Xml::TEXT)) != NULL) {
                setStringWorkArrivalTime(a);
            }
        }
        if (emts.firstChildElement(Xml::NO_SCHEDULED_WORK) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::NO_SCHEDULED_WORK).attribute(Xml::TEXT)) != NULL) {
                setStringNoScheduledWork(a);
            }
        }
        if (emts.firstChildElement(Xml::NO_SCHEDULED_WORK_ROUTE_COMMENT) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::NO_SCHEDULED_WORK_ROUTE_COMMENT).attribute(Xml::TEXT)) != NULL) {
                setStringNoScheduledWorkWithRouteComment(a);
            }
        }
        if (emts.firstChildElement(Xml::DEPART_TIME) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::DEPART_TIME).attribute(Xml::TEXT)) != NULL) {
                setStringDepartTime(a);
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
        if (emts.firstChildElement(Xml::TRAIN_TERMINATES) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::TRAIN_TERMINATES).attribute(Xml::TEXT)) != NULL) {
                setStringTrainTerminates(a);
            }
        }

        if (emts.firstChildElement(Xml::DESTINATION) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::DESTINATION).attribute(Xml::TEXT)) != NULL) {
                setStringDestination(a);
            }
        }
        if (emts.firstChildElement(Xml::TO) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::TO).attribute(Xml::TEXT)) != NULL) {
                setStringTo(a);
            }
        }
        if (emts.firstChildElement(Xml::FROM) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::FROM).attribute(Xml::TEXT)) != NULL) {
                setStringFrom(a);
            }
        }
        if (emts.firstChildElement(Xml::DEST) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::DEST).attribute(Xml::TEXT)) != NULL) {
                setStringDest(a);
            }
        }
        if (emts.firstChildElement(Xml::FINAL_DEST) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::FINAL_DEST).attribute(Xml::TEXT)) != NULL) {
                setStringFinalDestination(a);
            }
        }
        if (emts.firstChildElement(Xml::ADD_HELPERS) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::ADD_HELPERS).attribute(Xml::TEXT)) != NULL) {
                setStringAddHelpers(a);
            }
        }
        if (emts.firstChildElement(Xml::REMOVE_HELPERS) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::REMOVE_HELPERS).attribute(Xml::TEXT)) != NULL) {
                setStringRemoveHelpers(a);
            }
        }
        if (emts.firstChildElement(Xml::LOCO_CHANGE) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::LOCO_CHANGE).attribute(Xml::TEXT)) != NULL) {
                setStringLocoChange(a);
            }
        }
        if (emts.firstChildElement(Xml::CABOOSE_CHANGE) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::CABOOSE_CHANGE).attribute(Xml::TEXT)) != NULL) {
                setStringCabooseChange(a);
            }
        }
        if (emts.firstChildElement(Xml::LOCO_CABOOSE_CHANGE) != QDomElement()) {
            if ((a = emts.firstChildElement(Xml::LOCO_CABOOSE_CHANGE).attribute(Xml::TEXT)) != NULL) {
                setStringLocoAndCabooseChange(a);
            }
        }
    }
}
