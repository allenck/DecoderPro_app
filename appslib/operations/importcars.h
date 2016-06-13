#ifndef IMPORTCARS_H
#define IMPORTCARS_H
#include "importrollingstock.h"

class Logger;
namespace Operations
{
 class CarManager;
 class ImportCars : public ImportRollingStock
 {
 public:
  ImportCars();
 public slots:
  void process();

 signals:
  void finished();
  void status(QString);
  void msg(QString, QString);

 private:
  CarManager* manager;//= CarManager.instance();

  /*private*/ int weightResults;//= JOptionPane.NO_OPTION; // Automatically calculate weight for car if weight entry is not
  // found
  /*private*/ bool autoCalculate;//= true;
  /*private*/ bool askAutoCreateTypes;//= true;
  /*private*/ bool askAutoCreateLocations;//= true;
  /*private*/ bool askAutoCreateTracks;//= true;
  /*private*/ bool askAutoLocationType;//= true;
  /*private*/ bool askAutoIncreaseTrackLength;//= true;
  /*private*/ bool askAutoForceCar;//= true;

  /*private*/ bool autoCreateTypes;//= false;
  /*private*/ bool autoCreateLocations;//= false;
  /*private*/ bool autoCreateTracks;//= false;
  /*private*/ bool autoAdjustLocationType;//= false;
  /*private*/ bool autoAdjustTrackLength;//= false;
  /*private*/ bool autoForceCar;//= false;

  /*private*/ bool autoCreateRoads;//= true;
  /*private*/ bool autoCreateLengths;//= true;
  /*private*/ bool autoCreateColors;//= true;
  /*private*/ bool autoCreateOwners;//= true;
  enum VALUES
  {
   CAR_NUMBER = 0,
   CAR_ROAD = 1,
   CAR_TYPE = 2,
   CAR_LENGTH = 3,
   CAR_WEIGHT = 4,
   CAR_COLOR = 5,
   CAR_OWNER = 6,
   CAR_BUILT = 7,
   CAR_LOCATION = 8,
   CAR_LOCATION_TRACK_SEPARATOR = 9,
//    CAR_TRACK = 10,

   // only for CSV files
   CAR_LOAD = 11,
   CAR_KERNEL = 12,
   CAR_MOVES = 13,
   CAR_VALUE = 14,
   CAR_COMMENT = 15,
//    CAR_MISCELLANEOUS = 16,
   CAR_EXTENSIONS = 17,

   MAXIMUM_NUMBER_FIELDS = CAR_EXTENSIONS - 1

  };
  Logger* log;
 };
}
#endif // IMPORTCARS_H
