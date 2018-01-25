#ifndef TRAINCSVCOMMON_H
#define TRAINCSVCOMMON_H
#include "traincommon.h"

namespace Operations
{
 class TrainCsvCommon : public TrainCommon
 {
 public:
  TrainCsvCommon();

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TrainCsvCommon.class);


 protected:
  /*protected*/ /*final*/ static QString DEL;// = ","; // delimiter // NOI18N
  /*protected*/ /*final*/ static QString ESC;// = "\""; // escape // NOI18N

  /*protected*/ /*final*/ static QString HEADER;// = tr("Operator") + DEL + tr("csvDescription")
//          + DEL + tr("csvParameters");
  /*protected*/ /*final*/ static QString AH;// = "AH" + DEL + tr("csvAddHelpers"); // NOI18N
  /*protected*/ /*final*/ static QString AT;// = "AT" + DEL + tr("csvArrivalTime") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString CC;// = "CC" + DEL + tr("csvChangeCaboose"); // NOI18N
  /*protected*/ /*final*/ static QString CL;// = "CL" + DEL + tr("csvChangeLocos"); // NOI18N
  /*protected*/ /*final*/ static QString DT;// = "DT" + DEL + tr("csvDepartureTime") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString DTR;// = "DTR" + DEL + tr("csvDepartureTimeRoute") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString EDT;// = "EDT" + DEL + tr("csvEstimatedDepartureTime") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString LC;// = "LC" + DEL + tr("csvLocationComment") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString LN;// = "LN" + DEL + tr("csvLocationName") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString LOGO;// = "LOGO" + DEL + tr("csvLogoFilePath") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString NW;// = "NW" + DEL + tr("csvNoWork"); // NOI18N
  /*protected*/ /*final*/ static QString PC;// = "PC" + DEL + tr("csvPickUpCar"); // NOI18N
  /*protected*/ /*final*/ static QString PL;// = "PL" + DEL + tr("csvPickUpLoco"); // NOI18N
  /*protected*/ /*final*/ static QString PRNTR;// = "PRNTR" + DEL + tr("csvPrinterName") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString RC;// = "RC" + DEL + tr("csvRouteComment") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString RLC;// = "RLC" + DEL + tr("csvRouteLocationComment") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString RH;// = "RH" + DEL + tr("csvRemoveHelpers"); // NOI18N
  /*protected*/ /*final*/ static QString RN;// = "RN" + DEL + tr("csvRailroadName") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString SC;// = "SC" + DEL + tr("csvSetOutCar"); // NOI18N
  /*protected*/ /*final*/ static QString SL;// = "SL" + DEL + tr("csvSetOutLoco"); // NOI18N
  /*protected*/ /*final*/ static QString SMC;// = "SMC" + DEL + tr("csvSearchMissingCar"); // NOI18N
  /*protected*/ /*final*/ static QString SMCM;// = "SMCM" + DEL + tr("csvSearchMiaMessage") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TKCB;// = "TKCB" + DEL + tr("csvTrackCommentBoth") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TKCP;// = "TKCP" + DEL + tr("csvTrackCommentPickUp") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TKCS;// = "TKCS" + DEL + tr("csvTrackCommentSetOut") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TC;// = "TC" + DEL + tr("csvTrainComment") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TD;// = "TD" + DEL + tr("csvTrainDeparts") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TL;// = "TL" + DEL + tr("csvTrainLengthEmptiesCars") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TM;// = "TM" + DEL + tr("csvTrainManifestDescription") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TN;// = "TN" + DEL + tr("csvTrainName") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TRUN;// = "TRUN" + DEL + tr("csvTruncate"); // NOI18N
  /*protected*/ /*final*/ static QString TW;// = "TW" + DEL + tr("csvTrainWeight") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TT;// = "TT" + DEL + tr("csvTrainTerminates") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString VT;// = "VT" + DEL + tr("csvValid") + DEL; // NOI18N
  // switch list specific operators
  /*protected*/ /*final*/ static QString DL;// = "DL" + DEL + tr("csvDepartureLocationName") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString END;// = "END" + DEL + tr("csvEnd"); // NOI18N
  /*protected*/ /*final*/ static QString ETA;// = "ETA" + DEL + tr("csvExpectedTimeArrival") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString ETE;// = "ETE" + DEL + tr("csvEstimatedTimeEnroute") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString HOLD;// = "HOLD" + DEL + tr("csvHoldCar"); // NOI18N
  /*protected*/ /*final*/ static QString NCPU;// = "NCPU" + DEL + tr("csvNoCarPickUp"); // NOI18N
  /*protected*/ /*final*/ static QString NCSO;// = "NCSO" + DEL + tr("csvNoCarSetOut"); // NOI18N
  /*protected*/ /*final*/ static QString SWL;// = "SWL" + DEL + tr("csvSwitchList") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString SWLC;// = "SWLC" + DEL + tr("csvSwitchListComment") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TA;// = "TA" + DEL + tr("csvTrainArrives") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TDC;// = "TDC" + DEL + tr("csvTrainChangesDirection") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString TIR;// = "TIR" + DEL + tr("csvTrainEnRoute"); // NOI18N
  /*protected*/ /*final*/ static QString TDONE;// = "TDONE" + DEL + tr("csvTrainHasAlreadyServiced"); // NOI18N
  /*protected*/ /*final*/ static QString TEND;// = "TEND" + DEL + tr("csvTrainEnd") + DEL; // NOI18N
  /*protected*/ /*final*/ static QString VN;// = "VN" + DEL + tr("csvVisitNumber") + DEL; // NOI18N
  /*protected*/ void printTrackComments(PrintWriter* fileOut, RouteLocation* rl, QList<Car*>* carList);
  /*protected*/ void checkForEngineOrCabooseChange(PrintWriter* fileOut, Train* train, RouteLocation* rl);
  /*protected*/ void engineCsvChange(PrintWriter* fileOut, RouteLocation* rl, int legOptions);
  /*protected*/ void fileOutCsvEngine(PrintWriter* fileOut, Engine* engine, QString operation);
  /*protected*/ void fileOutCsvCar(PrintWriter* fileOut, Car* car, QString operation, int count);
  /*protected*/ void listCarsLocationUnknown(PrintWriter* fileOut);

 };
}
#endif // TRAINCSVCOMMON_H
