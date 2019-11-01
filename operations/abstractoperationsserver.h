#ifndef ABSTRACTOPERATIONSSERVER_H
#define ABSTRACTOPERATIONSSERVER_H

#include <QObject>
#include "propertychangelistener.h"

class Logger;
namespace Operations
{
 class Train;
 class TrainManager;
 class LocationManager;
 class TrainListener;
 class AbstractOperationsServer : public QObject
 {
  Q_OBJECT
 public:
  explicit AbstractOperationsServer(QObject *parent = 0);
  /*public*/ /*abstract*/ virtual void sendTrainList();
  /*public*/ /*abstract*/ virtual void sendLocationList();
  /*public*/ QString constructTrainStatus(QString trainName); //throws IOException
  /*public*/ QString constructTrainLocation(QString trainName); //throws IOException
  /*public*/ QString setTrainLocation(QString trainName, QString locationName);
  /*public*/ static void setExactLocationName(bool enabled);
  /*public*/ static bool isExactLoationNameEnabled();
  /*public*/ QString constructTrainLength(QString trainName); //throws IOException ;
  /*public*/ QString constructTrainWeight(QString trainName); //throws IOException
  /*public*/ QString constructTrainNumberOfCars(QString trainName); //throws IOException
  /*public*/ QString constructTrainLeadLoco(QString trainName); //throws IOException
  /*public*/ QString constructTrainCaboose(QString trainName); //throws IOException
  /*public*/ QString terminateTrain(QString trainName); //throws IOException
  /*public*/ /*abstract*/ virtual void sendFullStatus(Train* train);  //throws IOException;
  /*public*/ void dispose();
  /*abstract*/ /*public*/ virtual void sendMessage(QList<QString> contents); //throws IOException;
  /*abstract*/ /*public*/ virtual void sendErrorStatus(QString errorStatus); //throws IOException;
  /*abstract*/ /*public*/ virtual void parseStatus(QString statusString); //throws JmriException, IOException;

 signals:

 public slots:
  /*public*/ /*abstract*/ virtual void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  /*private*/ static bool exactLocationName;// = true;
  /*private*/ void addPropertyChangeListeners();
  /*private*/ void removePropertyChangeListeners();

 protected:
  /*protected*/ /*final*/ TrainManager* tm;
  /*protected*/ /*final*/ LocationManager* lm;
  /*protected*/ /*final*/ QMap<QString, TrainListener*> trains;
  /*synchronized*/ /*protected*/ void addTrainToList(QString trainId);
  /*synchronized*/ /*protected*/ void removeTrainFromList(QString trainId);
  /*protected*/ TrainListener* getListener(QString trainId);
  friend class TrainListener;
 };
 /*protected*/ class TrainListener : public PropertyChangeListener
 {
  Q_OBJECT
     /*private*/ /*final*/ Train* train;
  AbstractOperationsServer* parent;
  Logger* log;
  protected:
     /*protected*/ TrainListener(QString trainId, AbstractOperationsServer* parent);
  public slots:
     /*public*/ void propertyChange(PropertyChangeEvent* e);
  friend class AbstractOperationsServer;
 };

}
#endif // ABSTRACTOPERATIONSSERVER_H
