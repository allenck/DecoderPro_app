#include "metatypes.h"
#include "locationmanager.h"
#include "routemanager.h"
#include "routemanagerxml.h"
#include "carcolors.h"
#include "carlengths.h"
#include "carloads.h"
#include "enginelengths.h"
#include "enginemodels.h"
#include "enginetypes.h"
#include "transitmanager.h"
#include "dispatcherframe.h"
#include "cartypes.h"
#include "carowners.h"
#include "enginemanager.h"
#include "carmanager.h"
#include "carmanagerxml.h"
#include "operationssetupxml.h"
#include "enginemanagerxml.h"
#include "trainschedulemanager.h"
#include "trainmanagerxml.h"
#include "trainmanifesttext.h"
#include "locationmanagerxml.h"
#include "trainmanager.h"
#include "schedulemanager.h"
#include "operationsmanager.h"
#include "carroads.h"
#include "divisionmanager.h"
#include "kernelmanager.h"
#include "consistmanager.h"

namespace Operations
{
bool Metatypes::done = false;
int id;
 Metatypes::Metatypes(QObject *parent) : QObject(parent)
 {
  // operations
  qRegisterMetaType<RouteManager>("Operations::RouteManager");
  id = qRegisterMetaType<RouteManagerXml>("RouteManagerXml");
  qRegisterMetaType<CarColors>("CarColors");
  qRegisterMetaType<CarLengths>("CarLengths");
  qRegisterMetaType<CarLoads>("Operations::CarLoads");
  qRegisterMetaType<CarRoads>("CarRoads");
  qRegisterMetaType<EngineLengths>("EngineLengths");
  qRegisterMetaType<EngineModels>("EngineModels");
  qRegisterMetaType<EngineTypes>("EngineTypes");
  qRegisterMetaType<LocationManager>("LocationManager");
  qRegisterMetaType<TransitManager>("TransitManager");
  qRegisterMetaType<DispatcherFrame>("DispatcherFrame");
  qRegisterMetaType<CarTypes>("CarTypes");
  qRegisterMetaType<CarOwners>("CarOwners");
  qRegisterMetaType<EngineManager>("EngineManager");
  qRegisterMetaType<CarManager>("CarManager");
  qRegisterMetaType<CarManagerXml>("CarManagerXml");
  qRegisterMetaType<OperationsSetupXml>("OperationsSetupXml");
  qRegisterMetaType<EngineManagerXml>("EngineManagerXml");
  qRegisterMetaType<TrainScheduleManager>("TrainScheduleManager");
  qRegisterMetaType<TrainManager>("TrainManager");
  qRegisterMetaType<TrainManagerXml>("TrainManagerXml");
  qRegisterMetaType<Operations::TrainManifestText>("TrainManifestText");
  qRegisterMetaType<LocationManagerXml>("LocationManagerXml");
  qRegisterMetaType<ScheduleManager>("ScheduleManager");
  qRegisterMetaType<OperationsManager>("OperationsManager");
  qRegisterMetaType<DivisionManager>("DivisionManager");
  qRegisterMetaType<KernelManager>("KernelManager");
  qRegisterMetaType<ConsistManager>("ConsistManager");

  Metatypes::done = true;
 }
}
