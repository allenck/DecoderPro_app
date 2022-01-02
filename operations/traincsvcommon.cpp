#include "traincsvcommon.h"
#include "loggerfactory.h"
#include "track.h"
#include "location.h"
#include "car.h"
#include "engine.h"
#include "train.h"
#include "routelocation.h"
#include "carmanager.h"
#include "setup.h"
#include "instancemanager.h"

using namespace Operations;

TrainCsvCommon::TrainCsvCommon()
{

}
/**
 * Contains the csv operators for manifests and switch lists
 *
 * @author Daniel Boudreau Copyright (C) 2011, 2013, 2015
 *
 *
 */
// /*public*/ class TrainCsvCommon extends TrainCommon {

/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::DEL = ","; // delimiter // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::ESC = "\""; // escape // NOI18N

/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::HEADER = tr("Operator") + TrainCsvCommon::DEL + tr("csvDescription")
        + TrainCsvCommon::DEL + tr("csvParameters");

/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::AH = "AH" + TrainCsvCommon::DEL + tr("csvAddHelpers"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::AT = "AT" + TrainCsvCommon::DEL + tr("csvArrivalTime") + DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::CC = "CC" + TrainCsvCommon::DEL + tr("csvChangeCaboose"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::CL = "CL" + TrainCsvCommon::DEL + tr("csvChangeLocos"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::DT = "DT" + TrainCsvCommon::DEL + tr("csvDepartureTime") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::DTR = "DTR" + TrainCsvCommon::DEL + tr("csvDepartureTimeRoute") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::EDT = "EDT" + TrainCsvCommon::DEL + tr("csvEstimatedDepartureTime") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::LC = "LC" +TrainCsvCommon:: DEL + tr("csvLocationComment") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::LN = "LN" + TrainCsvCommon::DEL + tr("csvLocationName") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::LOGO = "LOGO" + TrainCsvCommon::DEL + tr("csvLogoFilePath") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::NW = "NW" + TrainCsvCommon::DEL + tr("csvNoWork"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::PC = "PC" + TrainCsvCommon::DEL + tr("csvPickUpCar"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::PL = "PL" + TrainCsvCommon::DEL + tr("csvPickUpLoco"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::PRNTR = "PRNTR" + TrainCsvCommon::DEL + tr("csvPrinterName") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::RC = "RC" + TrainCsvCommon::DEL + tr("csvRouteComment") +TrainCsvCommon:: DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::RLC = "RLC" + TrainCsvCommon::DEL + tr("csvRouteLocationComment") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::RH = "RH" + TrainCsvCommon::DEL + tr("csvRemoveHelpers"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::RN = "RN" + TrainCsvCommon::DEL + tr("csvRailroadName") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SC = "SC" +TrainCsvCommon::DEL + tr("csvSetOutCar"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SL = "SL" + TrainCsvCommon::DEL + tr("csvSetOutLoco"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SMC = "SMC" + TrainCsvCommon::DEL + tr("csvSearchMissingCar"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SMCM = "SMCM" + TrainCsvCommon::DEL + tr("csvSearchMiaMessage") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TKCB = "TKCB" + TrainCsvCommon::DEL + tr("csvTrackCommentBoth") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TKCP = "TKCP" + TrainCsvCommon::DEL + tr("csvTrackCommentPickUp") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TKCS = "TKCS" + TrainCsvCommon::DEL + tr("csvTrackCommentSetOut") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TC = "TC" + TrainCsvCommon::DEL + tr("csvTrainComment") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TD = "TD" + TrainCsvCommon::DEL + tr("csvTrainDeparts") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TL = "TL" + TrainCsvCommon::DEL + tr("csvTrainLengthEmptiesCars") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TM = "TM" + TrainCsvCommon::DEL + tr("csvTrainManifestDescription") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TN = "TN" + TrainCsvCommon::DEL + tr("csvTrainName") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TRUN = "TRUN" + TrainCsvCommon::DEL + tr("csvTruncate"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TW = "TW" + TrainCsvCommon::DEL + tr("csvTrainWeight") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TT = "TT" +TrainCsvCommon:: DEL + tr("csvTrainTerminates") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::VT = "VT" + TrainCsvCommon::DEL + tr("csvValid") + TrainCsvCommon::DEL; // NOI18N

// switch list specific operators
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::DL = "DL" + TrainCsvCommon::DEL + tr("csvDepartureLocationName") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::END = "END" + TrainCsvCommon::DEL + tr("csvEnd"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::ETA = "ETA" + TrainCsvCommon::DEL + tr("csvExpectedTimeArrival") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::ETE = "ETE" + TrainCsvCommon::DEL + tr("csvEstimatedTimeEnroute") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::HOLD = "HOLD" +TrainCsvCommon:: DEL + tr("csvHoldCar"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::NCPU = "NCPU" + TrainCsvCommon::DEL + tr("csvNoCarPickUp"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::NCSO = "NCSO" + TrainCsvCommon::DEL + tr("csvNoCarSetOut"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SWL = "SWL" + TrainCsvCommon::DEL + tr("csvSwitchList") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::SWLC = "SWLC" + TrainCsvCommon::DEL + tr("csvSwitchListComment") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TA = "TA" + TrainCsvCommon::DEL + tr("csvTrainArrives") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TDC = "TDC" + TrainCsvCommon::DEL + tr("csvTrainChangesDirection") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TIR = "TIR" + TrainCsvCommon::DEL + tr("csvTrainEnRoute"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TDONE = "TDONE" + TrainCsvCommon::DEL + tr("csvTrainHasAlreadyServiced"); // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::TEND = "TEND" + TrainCsvCommon::DEL + tr("csvTrainEnd") + TrainCsvCommon::DEL; // NOI18N
/*protected*/ /*final*/ /*static*/ QString TrainCsvCommon::VN = "VN" + TrainCsvCommon::DEL + tr("csvVisitNumber") + TrainCsvCommon::DEL; // NOI18N

/*private*/ /*final*/ /*static*/ Logger* TrainCsvCommon::log = LoggerFactory::getLogger("TrainCsvCommon");

/*protected*/ void TrainCsvCommon::fileOutCsvCar(PrintWriter* fileOut, Car* car, QString operation, int count) {
    // check for delimiter in names
    QString carRoad = car->getRoadName();
    if (carRoad.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in road field: " + carRoad);
        carRoad = ESC + carRoad + ESC;
    }
    QString carType = car->getTypeName();
    if (carType.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in type field: " + carType);
        carType = ESC + carType + ESC;
    }
    QString carLoad = car->getLoadName();
    if (carLoad.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in load field: " + carLoad);
        carLoad = ESC + carLoad + ESC;
    }
    QString carColor = car->getColor();
    if (carColor.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in color field: " + carColor);
        carColor = ESC + carColor + ESC;
    }
    QString carLocationName = car->getLocationName();
    if (carLocationName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in location field: " + carLocationName);
        carLocationName = ESC + carLocationName + ESC;
    }
    QString carTrackName = car->getTrackName();
    if (carTrackName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in track field: " + carTrackName);
        carTrackName = ESC + carTrackName + ESC;
    }
    QString carDestName = car->getDestinationName();
    if (carDestName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in destination field: " + carDestName);
        carDestName = ESC + carDestName + ESC;
    }
    QString carDestTrackName = car->getDestinationTrackName();
    if (carDestTrackName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in destination track field: " + carDestTrackName);
        carDestTrackName = ESC + carDestTrackName + ESC;
    }
    QString carOwner = car->getOwner();
    if (carOwner.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in owner field: " + carOwner);
        carOwner = ESC + carOwner + ESC;
    }
    QString carKernelName = car->getKernelName();
    if (carKernelName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in kernel name field: " + carKernelName);
        carKernelName = ESC + carKernelName + ESC;
    }
    QString carRWEDestName = car->getReturnWhenEmptyDestinationName();
    if (carRWEDestName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in RWE destination field: " + carRWEDestName);
        carRWEDestName = ESC + carRWEDestName + ESC;
    }
    QString carRWETrackName = car->getReturnWhenEmptyDestTrackName();
    if (carRWETrackName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in RWE destination track field: " + carRWETrackName);
        carRWETrackName = ESC + carRWETrackName + ESC;
    }
    QString carFinalDestinationName = car->getFinalDestinationName();
    if (carFinalDestinationName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in /*final*/ destination field: "
                + carFinalDestinationName);
        carFinalDestinationName = ESC + carFinalDestinationName + ESC;
    }
    QString carFinalDestinationTrackName = car->getFinalDestinationTrackName();
    if (carFinalDestinationTrackName.contains(DEL)) {
        log->debug("Car (" + car->toString() + ") has delimiter in /*final*/ destination track field: "
                + carFinalDestinationTrackName);
        carFinalDestinationTrackName = ESC + carFinalDestinationTrackName + ESC;
    }

    addLine(fileOut, operation + DEL + carRoad + DEL + car->getNumber() + DEL + carType + DEL + car->getLength()
            + DEL + carLoad + DEL + carColor + DEL + carLocationName + DEL + carTrackName + DEL + carDestName + DEL
            + carDestTrackName + DEL + carOwner + DEL + carKernelName + DEL + ESC + car->getComment() + ESC + DEL
            + ESC + car->getPickupComment() + ESC + DEL + ESC + car->getDropComment() + ESC + DEL
            + (car->isCaboose() ? "C" : "") + DEL + (car->hasFred() ? "F" : "") + DEL
            + (car->isHazardous() ? "H" : "") + DEL + ESC + car->getRfid() + ESC + DEL + carRWEDestName + DEL
            + carRWETrackName + DEL + (car->isUtility() ? "U" : "") + DEL + count + DEL + carFinalDestinationName
            + DEL + carFinalDestinationTrackName);
}

/*protected*/ void TrainCsvCommon::fileOutCsvEngine(PrintWriter* fileOut, Engine* engine, QString operation) {
    // check for delimiter in names
    QString engineRoad = engine->getRoadName();
    if (engineRoad.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in road field: " + engineRoad);
        engineRoad = ESC + engineRoad + ESC;
    }
    QString engineModel = engine->getModel();
    if (engineModel.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in model field: " + engineModel);
        engineModel = ESC + engineModel + ESC;
    }
    QString engineType = engine->getTypeName();
    if (engineType.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in type field: " + engineType);
        engineType = ESC + engineType + ESC;
    }
    QString engineLocationName = engine->getLocationName();
    if (engineLocationName.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in location field: " + engineLocationName);
        engineLocationName = ESC + engine->getLocationName() + ESC;
    }
    QString engineTrackName = engine->getTrackName();
    if (engineTrackName.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in track field: " + engineTrackName);
        engineTrackName = ESC + engine->getTrackName() + ESC;
    }
    QString engineDestName = engine->getDestinationName();
    if (engineDestName.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in destination field: " + engineDestName);
        engineDestName = ESC + engine->getDestinationName() + ESC;
    }
    QString engineDestTrackName = engine->getDestinationTrackName();
    if (engineDestTrackName.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in destination track field: "
                + engineDestTrackName);
        engineDestTrackName = ESC + engine->getDestinationTrackName() + ESC;
    }
    QString engineOwner = engine->getOwner();
    if (engineOwner.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in owner field: " + engineOwner);
        engineOwner = ESC + engineOwner + ESC;
    }
    QString engineConsistName = engine->getConsistName();
    if (engineConsistName.contains(DEL)) {
        log->debug("Engine (" + engine->toString() + ") has delimiter in consist name field: " + engineConsistName);
        engineConsistName = ESC + engineConsistName + ESC;
    }
    QString engineIsLead = "";
    if (engine->getConsist() != NULL && engine->getConsist()->isLead(engine)) {
        engineIsLead = "Lead loco"; // NOI18N
    }
    addLine(fileOut, operation + DEL + engineRoad + DEL + engine->getNumber() + DEL + engineModel + DEL
            + engine->getLength() + DEL + engineType + DEL + engine->getHp() + DEL + engineLocationName + DEL
            + engineTrackName + DEL + engineDestName + DEL + engineDestTrackName + DEL + engineOwner + DEL
            + engineConsistName + DEL + engineIsLead + DEL + ESC + engine->getComment() + ESC + DEL + ESC
            + engine->getRfid() + ESC);
}

/*protected*/ void TrainCsvCommon::checkForEngineOrCabooseChange(PrintWriter* fileOut, Train* train, RouteLocation* rl) {
    if (train->getSecondLegOptions() != Train::NO_CABOOSE_OR_FRED) {
        if (rl == train->getSecondLegStartLocation()) {
            engineCsvChange(fileOut, rl, train->getSecondLegOptions());
        }
        if (rl == train->getSecondLegEndLocation()) {
            addLine(fileOut, RH);
        }
    }
    if (train->getThirdLegOptions() != Train::NO_CABOOSE_OR_FRED) {
        if (rl == train->getThirdLegStartLocation()) {
            engineCsvChange(fileOut, rl, train->getThirdLegOptions());
        }
        if (rl == train->getThirdLegEndLocation()) {
            addLine(fileOut, RH);
        }
    }
}

/*protected*/ void TrainCsvCommon::engineCsvChange(PrintWriter* fileOut, RouteLocation* rl, int legOptions)
{
 if ((legOptions & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
     addLine(fileOut, AH);
 }
 if ((legOptions & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
         || (legOptions & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
     addLine(fileOut, CC);
 }
 if ((legOptions & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
     addLine(fileOut, CL);
 }
}

/*protected*/ void TrainCsvCommon::printTrackComments(PrintWriter* fileOut, RouteLocation* rl, QList<Car*>* carList) {
    Location* location = rl->getLocation();
    if (location != NULL) {
        QList<Track*> tracks = location->getTracksByNameList(NULL);
        for (Track* track : tracks) {
            // any pick ups or set outs to this track?
            bool pickup = false;
            bool setout = false;
            for (Car* car : *carList) {
                if (car->getRouteLocation() == rl && car->getTrack() != NULL && car->getTrack() == track) {
                    pickup = true;
                }
                if (car->getRouteDestination() == rl && car->getDestinationTrack() != NULL
                        && car->getDestinationTrack() == track) {
                    setout = true;
                }
            }
            // print the appropriate comment if there's one
            // each comment can have multiple lines
            if (pickup && setout && track->getCommentBoth() != ( Track::NONE)) {
                QStringList comments = track->getCommentBoth().split(NEW_LINE);
                for (QString comment : comments) {
                    addLine(fileOut, TKCB + comment);
                }
            } else if (pickup && !setout && track->getCommentPickup() != ( Track::NONE)) {
                QStringList comments = track->getCommentPickup().split(NEW_LINE);
                for (QString comment : comments) {
                    addLine(fileOut, TKCP + comment);
                }
            } else if (!pickup && setout && track->getCommentSetout() != ( Track::NONE)) {
                QStringList comments = track->getCommentSetout().split(NEW_LINE);
                for (QString comment : comments) {
                    addLine(fileOut, TKCS + comment);
                }
            }
        }
    }
}

/*protected*/ void TrainCsvCommon::listCarsLocationUnknown(PrintWriter* fileOut) {
    QList<Car*>* cars = ((CarManager*)InstanceManager::getDefault("CarManager"))->getCarsLocationUnknown();
    if (cars->size() == 0) {
        return; // no cars to search for!
    }
    addLine(fileOut, SMCM + ESC + Setup::getMiaComment() + ESC);
    for (Car* car : *cars) {
        fileOutCsvCar(fileOut, car, SMC, 0);
    }
}

