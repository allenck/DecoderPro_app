#ifndef TRAINMANIFESTTEXT_H
#define TRAINMANIFESTTEXT_H
#include <QObject>

class QDomDocument;
class QDomElement;
class QString;
namespace Operations
{
 class TrainManifestText : public QObject
 {
  Q_OBJECT
 public:
  TrainManifestText() {}
  ~TrainManifestText() {}
  TrainManifestText(const TrainManifestText&){}
  /*public*/ static QString getStringManifestForTrain();
  /*public*/ static void setStringManifestForTrain(QString s);
  /*public*/ static QString getStringValid();
  /*public*/ static void setStringValid(QString s);
  /*public*/ static QString getStringScheduledWork();
  /*public*/ static void setStringScheduledWork(QString s);
  /*public*/ static QString getStringWorkDepartureTime();
  /*public*/ static void setStringWorkDepartureTime(QString s);
  /*public*/ static QString getStringWorkArrivalTime();
  /*public*/ static void setStringWorkArrivalTime(QString s);
  /*public*/ static QString getStringNoScheduledWork();
  /*public*/ static void setStringNoScheduledWork(QString s);
  /*public*/ static QString getStringNoScheduledWorkWithRouteComment();
  /*public*/ static void setStringNoScheduledWorkWithRouteComment(QString s);
  /*public*/ static QString getStringDepartTime() ;
  /*public*/ static void setStringDepartTime(QString s);
  /*public*/ static QString getStringTrainDepartsCars() ;
  /*public*/ static void setStringTrainDepartsCars(QString s);
  /*public*/ static QString getStringTrainDepartsLoads();
  /*public*/ static void setStringTrainDepartsLoads(QString s);
  /*public*/ static QString getStringTrainTerminates();
  /*public*/ static void setStringTrainTerminates(QString s);
  /*public*/ static QString getStringDestination();
  /*public*/ static void setStringDestination(QString s);
  /*public*/ static QString getStringFrom();
  /*public*/ static void setStringFrom(QString s);
  /*public*/ static QString getStringTo();
  /*public*/ static void setStringTo(QString s);
  /*public*/ static QString getStringDest();
  /*public*/ static void setStringDest(QString s) ;
  /*public*/ static QString getStringFinalDestination() ;
  /*public*/ static void setStringFinalDestination(QString s);
  /*public*/ static QString getStringAddHelpers();
  /*public*/ static void setStringAddHelpers(QString s);
  /*public*/ static QString getStringRemoveHelpers();
  /*public*/ static void setStringRemoveHelpers(QString s);
  /*public*/ static QString getStringLocoChange();
  /*public*/ static void setStringLocoChange(QString s);
  /*public*/ static QString getStringCabooseChange();
  /*public*/ static void setStringCabooseChange(QString s);
  /*public*/ static QString getStringLocoAndCabooseChange();
  /*public*/ static void setStringLocoAndCabooseChange(QString s);
  /*public*/ static QDomElement store(QDomDocument doc);
  /*public*/ static void load(QDomElement e);

 private:

  /*private*/ static QString manifestForTrain;//= tr("ManifestForTrain");
  /*private*/ static QString valid;//= tr("Valid");
  /*private*/ static QString scheduledWorkAt;//= tr("ScheduledWorkAt");
  /*private*/ static QString departureTime;//= tr("WorkDepartureTime");
  /*private*/ static QString arrivalTime;//= tr("WorkArrivalTime");
  /*private*/ static QString noScheduledWorkAt;//= tr("NoScheduledWorkAt");
  /*private*/ static QString noScheduledWorkAtRouteComment;//= tr("NoScheduledWorkAtWithRouteComment");
  /*private*/ static QString departTime;//= tr("departureTime");	// this get's appended to "no scheduled work at"
  /*private*/ static QString trainDepartsCars;//= tr("TrainDepartsCars");
  /*private*/ static QString trainDepartsLoads;//= tr("TrainDepartsLoads");
  /*private*/ static QString trainTerminatesIn;//= tr("TrainTerminatesIn");

  /*private*/ static QString destination;//= tr("destination");
  /*private*/ static QString from;//= tr("from");
  /*private*/ static QString to;//= tr("to");

  /*private*/ static QString fd;//= tr("FD");
  /*private*/ static QString dest;//= tr("dest");

  /*private*/ static QString addHelpersAt;//= tr("AddHelpersAt");
  /*private*/ static QString removeHelpersAt;//= tr("RemoveHelpersAt");
  /*private*/ static QString locoChangeAt;//= tr("LocoChangeAt");
  /*private*/ static QString cabooseChangeAt;//= tr("CabooseChangeAt");
  /*private*/ static QString locoAndCabooseChangeAt;//= tr("LocoAndCabooseChangeAt");

 };

}
Q_DECLARE_METATYPE(Operations::TrainManifestText)
#endif // TRAINMANIFESTTEXT_H
