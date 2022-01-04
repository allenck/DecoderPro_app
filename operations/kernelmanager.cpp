#include "kernelmanager.h"
#include "loggerfactory.h"
#include "xml.h"
#include "car.h"
#include "kernel.h"
#include "instancemanager.h"
#include "carmanagerxml.h"

namespace Operations {

 /**
  * Manages Kernels.
  *
  * @author Daniel Boudreau Copyright (C) 2021
  */
 // /*public*/  class KernelManager extends RollingStockGroupManager implements InstanceManagerAutoDefault {

     /*public*/  KernelManager::KernelManager(QObject* parent) : RollingStockGroupManager(parent) {
     }

     /**
      * Create a new Kernel
      *
      * @param name string name for this Kernel
      *
      * @return Kernel
      */
     /*public*/  Kernel* KernelManager::newKernel(QString name) {
         Kernel*kernel = getKernelByName(name);
         if (kernel == nullptr && name!=(NONE)) {
             kernel = new Kernel(name);
             int oldSize = _groupHashTable.size();
             _groupHashTable.insert(name, kernel);
             setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, _groupHashTable
                     .size());
         }
         return kernel;
     }

     /**
      * Delete a Kernel by name
      *
      * @param name string name for the Kernel
      *
      */
     /*public*/  void KernelManager::deleteKernel(QString name) {
         Kernel* kernel = getKernelByName(name);
         if (kernel != nullptr) {
             kernel->dispose();
             int oldSize = (_groupHashTable.size());
             _groupHashTable.remove(name);
             setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_groupHashTable
                     .size()));
         }
     }

     /**
      * Get a Kernel by name
      *
      * @param name string name for the Kernel
      *
      * @return named Kernel
      */
     /*public*/  Kernel* KernelManager::getKernelByName(QString name) {
         return (Kernel*) _groupHashTable.value(name);
     }

     /*public*/  void KernelManager::replaceKernelName(QString oldName, QString newName) {
         Kernel* oldKernel = getKernelByName(oldName);
         if (oldKernel != nullptr) {
             Kernel* _newKernel = newKernel(newName);
             // keep the lead car
             Car* leadCar =( Car*)oldKernel->getLead();
             if (leadCar != nullptr) {
                 leadCar->setKernel(_newKernel);
             }
             for (Car* car : oldKernel->getCars()) {
                 car->setKernel(_newKernel);
             }
         }
     }


     /*public*/  void KernelManager::load(QDomElement root) {
         // new format using elements starting version 3.3.1
         if (root.firstChildElement(Xml::NEW_KERNELS) != QDomElement()) {
             QDomNodeList eKernels = root.firstChildElement(Xml::NEW_KERNELS).elementsByTagName(Xml::KERNEL);
             log->debug(tr("Kernel manager sees %1 kernels").arg(eKernels.size()));
             QString a;
             for (int i=0; i < eKernels.size(); i++)
             {
              QDomElement eKernel = eKernels.at(i).toElement();
                 if ((a = eKernel.attribute(Xml::NAME)) != "") {
                     newKernel(a);
                 }
             }
         } // old format
         else if (root.firstChildElement(Xml::KERNELS) != QDomElement()) {
             QString names = root.firstChildElement(Xml::KERNELS).text();
             if (!names.isEmpty()) {
                 QStringList kernelNames = names.split("%%"); // NOI18N
                 log->debug(tr("kernels: %1").arg(names));
                 for (QString name : kernelNames) {
                     newKernel(name);
                 }
             }
         }
     }

     /**
      * Create an XML element to represent this Entry. This member has to remain
      * synchronized with the detailed DTD in operations-cars.dtd.
      *
      * @param root The common Element for operations-cars.dtd.
      */
     /*public*/  void KernelManager::store(QDomElement root, QDomDocument doc) {
         QList<QString> names = getNameList();
         QDomElement kernels = doc.createElement(Xml::NEW_KERNELS);
         for (QString name : names) {
             QDomElement kernel = doc.createElement(Xml::KERNEL);
             kernel.setAttribute(Xml::NAME, name);
             kernels.appendChild(kernel);
         }
         root.appendChild(kernels);
     }

     /*protected*/ void KernelManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
         // Set dirty
         ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
         PropertyChangeSupport::firePropertyChange(p, old, n);
     }

     /*private*/ /*final*/ /*static*/ Logger* KernelManager::log = LoggerFactory::getLogger("KernelManager");

} // namespace Operations
