#ifndef CARMANAGER_H
#define CARMANAGER_H
#include "rollingstockmanager.h"
#include <QtXml>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

//class QDomElement;
class JComboBox;
class Logger;
namespace Operations
{
 class Car;
 class Kernel;
 class APPSLIBSHARED_EXPORT CarManager : public RollingStockManager, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit CarManager(QObject *parent = 0);
     ~CarManager() {}
     CarManager(const CarManager&) : RollingStockManager() {}
  /*public*/ static /*final*/ QString KERNEL_LISTLENGTH_CHANGED_PROPERTY;// = "KernelListLength"; // NOI18N
  /*public*/ RollingStock* newRS(QString road, QString number)override;
  /*public*/ void deregister(RollingStock* car)override;
  /*public*/ Car* getById(QString id);
  /*public*/ Car* getByRoadAndNumber(QString road, QString number);
  /*public*/ Car* getByTypeAndRoad(QString type, QString road);

  /*public*/ Kernel* newKernel(QString name);
  /*public*/ void deleteKernel(QString name);
  /*public*/ Kernel* getKernelByName(QString name);
  /*public*/ void replaceKernelName(QString oldName, QString newName);
  /*public*/ JComboBox* getKernelComboBox();
  /*public*/ void updateKernelComboBox(JComboBox* box);
  /*public*/ QStringList getKernelNameList();
  /*public*/ int getKernelMaxNameLength() ;

  /*public*/ QList<RollingStock*>* getByLocationList() override;
  /*public*/ QList<RollingStock*>* getByKernelList() ;
  /*public*/ QList<RollingStock*>* getByLoadList();
  /*public*/ QList<RollingStock*>* getByRweList();
  /*public*/ QList<RollingStock*>* getByFinalDestinationList() ;
  /*public*/ QList<RollingStock*>* getByWaitList();
  /*public*/ QList<RollingStock*>* getByPickupList();
  /*public*/ QList<Car*>* getAvailableTrainList(Train* train);
  /*protected*/ QList<RollingStock*>* sortByPriority(QList<RollingStock*>* list);
  /*public*/ QList<Car*>* getByTrainDestinationList(Train* train);
  /*public*/ QStringList getCabooseRoadNames();
  /*public*/ QStringList getFredRoadNames();
  /*public*/ void replaceLoad(QString type, QString oldLoadName, QString newLoadName) ;
  /*public*/ QList<Car*>* getCarsLocationUnknown() ;
  /*public*/ void load(QDomElement root) ;
  /*public*/ void store(QDomElement root, QDomDocument doc);
  Q_INVOKABLE/*public*/ void initialize()override;

  /*public*/ void sortOut(QList<RollingStock*>*, SORTBY attribute)override;

 private:
  // /*private*/ static CarManager* _instance;// = NULL;
  Logger* log;
//  enum SORTBY
//  {
//   // The special sort options for cars
//   BY_LOAD = 4,
//   BY_KERNEL = 5,
//   BY_RWE = 13, // Return When Empty
//   BY_FINAL_DEST = 14,
//   BY_WAIT = 16,
//   BY_PICKUP = 19
//  };
  QDomDocument doc;
 protected:
  // stores Kernels
  /*protected*/ QHash<QString, Kernel*> _kernelHashTable;// = QHash<QString, Kernel*>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n)override;
  /*static*/ bool lessthan(RollingStock* r1, RollingStock* r2, SORTBY attribute);

#if 0
  /*protected*/ Comparator<RollingStock*> getComparator(int attribute);
#endif
 signals:

 public slots:

 };
}
Q_DECLARE_METATYPE(Operations::CarManager)
#endif // CARMANAGER_H
