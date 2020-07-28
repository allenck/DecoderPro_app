#ifndef TRAINBYCARTYPEFRAME_H
#define TRAINBYCARTYPEFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class Track;
 class Car;
 class Train;
 class LocationManager;
 class TrainByCarTypeFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainByCarTypeFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Train* train);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
 private:
  // train
  Train* _train;

  LocationManager* locationManager;// = LocationManager.instance();

  // panels
  QWidget* pRoute;// = new JPanel();

  // radio buttons
  // combo boxes
  JComboBox* trainsComboBox;// = TrainManager.instance().getTrainComboBox();
  JComboBox* typeComboBox;// = CarTypes.instance().getComboBox();
  JComboBox* carsComboBox;// = new JComboBox<>();

  // The car currently selected
  Car* _car;
  Logger* log;
  /*private*/ void updateRoute();
  /*private*/ static /*final*/ QString ROAD;// = "road"; // NOI18N
  /*private*/ static /*final*/ QString LOAD;// = "load"; // NOI18N
  /*private*/ static /*final*/ QString TIMETABLE;// = "timetable"; // NOI18N
  /*private*/ static /*final*/ QString TYPE;// = "type"; // NOI18N
  /*private*/ static /*final*/ QString ALL;// = "all"; // NOI18N

  /*private*/ bool checkScheduleAttribute(QString attribute, QString carType, Car* car, Track* track);
  /*private*/ void updateComboBox();
  /*private*/ void updateCarsComboBox();
  /*private*/ void adjustCarsComboBoxSize();
  /*private*/ void addLocationAndTrackPropertyChange();
  /*private*/ void removeLocationAndTrackPropertyChange();

 };
}
#endif // TRAINBYCARTYPEFRAME_H
