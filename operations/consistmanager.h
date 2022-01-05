#ifndef OPERATIONS_CONSISTMANAGER_H
#define OPERATIONS_CONSISTMANAGER_H

#include "rollingstockgroupmanager.h"
#include "instancemanagerautodefault.h"
#include <QtXml>
#include "consist.h"

namespace Operations {

 class ConsistManager : public RollingStockGroupManager, public InstanceManagerAutoDefault
 {
   Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
  public:
   explicit ConsistManager(QObject *parent = nullptr);
   ~ConsistManager() {}
   ConsistManager(const ConsistManager&) : RollingStockGroupManager() {}
   /*public*/  Consist* newConsist(QString name);
   /*public*/  void deleteConsist(QString name);
   /*public*/  Consist* getConsistByName(QString name) ;
   /*public*/  void replaceConsistName(QString oldName, QString newName) ;
   /*public*/  void load(QDomElement root);
   /*public*/  void store(QDomElement root, QDomDocument doc);

  private:
   static Logger* log;

  protected:
   /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
} // namespace Operations
Q_DECLARE_METATYPE(Operations::ConsistManager)

#endif // OPERATIONS_CONSISTMANAGER_H
