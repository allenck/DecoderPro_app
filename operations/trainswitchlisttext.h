#ifndef TRAINSWITCHLISTTEXT_H
#define TRAINSWITCHLISTTEXT_H

#include <QObject>

class QDomDocument;
class QDomElement;
namespace Operations
{
 class TrainSwitchListText : public QObject
 {
  Q_OBJECT
 public:
  explicit TrainSwitchListText(QObject *parent = 0);
  /*public*/ static QString getStringSwitchListFor() ;
  /*public*/ static void setStringSwitchListFor(QString s);
  /*public*/ static QString getStringScheduledWork();
  /*public*/ static void setStringScheduledWork(QString s) ;
  /*public*/ static QString getStringDepartsAt();
  /*public*/ static void setStringDepartsAt(QString s);
  /*public*/ static QString getStringDepartsAtExpectedArrival();
  /*public*/ static void setStringDepartsAtExpectedArrival(QString s);
  /*public*/ static QString getStringDepartedExpected();
  /*public*/ static void setStringDepartedExpected(QString s) ;
  /*public*/ static QString getStringVisitNumber();
  /*public*/ static void setStringVisitNumber(QString s);
  /*public*/ static QString getStringVisitNumberDeparted();
  /*public*/ static void setStringVisitNumberDeparted(QString s);
  /*public*/ static QString getStringVisitNumberTerminates();
  /*public*/ static void setStringVisitNumberTerminates(QString s);
  /*public*/ static QString getStringVisitNumberTerminatesDeparted();
  /*public*/ static void setStringVisitNumberTerminatesDeparted(QString s);
  /*public*/ static QString getStringVisitNumberDone();
  /*public*/ static void setStringVisitNumberDone(QString s);
  /*public*/ static QString getStringTrainDirectionChange();
  /*public*/ static void setStringTrainDirectionChange(QString s);
  /*public*/ static QString getStringNoCarPickUps();
  /*public*/ static void setStringNoCarPickUps(QString s);
  /*public*/ static QString getStringNoCarDrops() ;
  /*public*/ static void setStringNoCarDrops(QString s);
  /*public*/ static QString getStringTrainDone();
  /*public*/ static void setStringTrainDone(QString s);
  /*public*/ static QString getStringTrainDepartsCars();
  /*public*/ static void setStringTrainDepartsCars(QString s);
  /*public*/ static QString getStringTrainDepartsLoads();
  /*public*/ static void setStringTrainDepartsLoads(QString s);
  /*public*/ static QString getStringSwitchListByTrack();
  /*public*/ static void setStringSwitchListByTrack(QString s) ;
  /*public*/ static QString getStringHoldCar() ;
  /*public*/ static void setStringHoldCar(QString s);
  // must synchronize changes with operation-config.dtd
  /*public*/ static QDomElement store(QDomDocument doc);
  /*public*/ static void load(QDomElement e);

 signals:

 public slots:

 private:
  /*private*/ static QString switchListFor;// = Bundle.getMessage("SwitchListFor");
  /*private*/ static QString scheduledWork;// = Bundle.getMessage("ScheduledWork");

  /*private*/ static QString departsAt;// = Bundle.getMessage("DepartsAt");
  /*private*/ static QString departsAtExpectedArrival;// = Bundle.getMessage("DepartsAtExpectedArrival");
  /*private*/ static QString departedExpected;// = Bundle.getMessage("DepartedExpected");

  /*private*/ static QString visitNumber;// = Bundle.getMessage("VisitNumber");
  /*private*/ static QString visitNumberDeparted;// = Bundle.getMessage("VisitNumberDeparted");	// this get's appended to "no scheduled work at"
  /*private*/ static QString visitNumberTerminates;// = Bundle.getMessage("VisitNumberTerminates");
  /*private*/ static QString visitNumberTerminatesDeparted;// = Bundle.getMessage("VisitNumberTerminatesDeparted");
  /*private*/ static QString visitNumberDone;// = Bundle.getMessage("VisitNumberDone");

  /*private*/ static QString trainDirectionChange;// = Bundle.getMessage("TrainDirectionChange");
  /*private*/ static QString noCarPickUps;// = Bundle.getMessage("NoCarPickUps");
  /*private*/ static QString noCarDrops;// = Bundle.getMessage("NoCarDrops");
  /*private*/ static QString trainDone;// = Bundle.getMessage("TrainDone");

  /*private*/ static QString trainDepartsCars;// = Bundle.getMessage("TrainDepartsCars");
  /*private*/ static QString trainDepartsLoads;// = Bundle.getMessage("TrainDepartsLoads");

  /*private*/ static QString switchListByTrack;// = Bundle.getMessage("SwitchListByTrack");
  /*private*/ static QString holdCar;// = Bundle.getMessage("HoldCar");

 };
}
#endif // TRAINSWITCHLISTTEXT_H
