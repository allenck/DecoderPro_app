#ifndef TRAINCSVMANIFEST_H
#define TRAINCSVMANIFEST_H
#include "traincsvcommon.h"

namespace Operations
{
 class TrainCsvManifest : public TrainCsvCommon
 {
 public:
  TrainCsvManifest();
  /*public*/ TrainCsvManifest(Train* train);


 private:
  EngineManager* engineManager;// = EngineManager.instance();
  CarManager* carManager;// = CarManager.instance();
  LocationManager* locationManager;// = LocationManager.instance();
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TrainCsvManifest.class);

 };
}
#endif // TRAINCSVMANIFEST_H
