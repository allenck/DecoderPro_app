#ifndef OPERATIONS_KERNELMANAGER_H
#define OPERATIONS_KERNELMANAGER_H

#include "rollingstockgroupmanager.h"
#include <QMainWindow>
#include "kernel.h"
#include <QtXml>
#include "instancemanagerautodefault.h"
namespace Operations {

 class KernelManager : public RollingStockGroupManager, public InstanceManagerAutoDefault
 {
   Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
  public:
   Q_INVOKABLE explicit KernelManager(QObject *parent = nullptr);
   ~KernelManager() {}
   KernelManager(const KernelManager&): RollingStockGroupManager() {}
   /*public*/  Kernel* newKernel(QString name);
   /*public*/  void deleteKernel(QString name);
   /*public*/  Kernel* getKernelByName(QString name);
   /*public*/  void replaceKernelName(QString oldName, QString newName);
   /*public*/  void load(QDomElement root);
   /*public*/  void store(QDomElement root, QDomDocument doc);

   private:
   static Logger* log;

  protected:
   /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };

} // namespace Operations
Q_DECLARE_METATYPE(Operations::KernelManager)
#endif // OPERATIONS_KERNELMANAGER_H
