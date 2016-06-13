#include "kernel.h"
#include "car.h"
#include "logger.h"

//Kernel::Kernel(QObject *parent) :
//  RollingStockGroup(parent)
//{
//}
namespace Operations
{
 /**
  * A Kernel is a group of cars that is managed as one car.
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class Kernel extends RollingStockGroup {

 /*public*/ Kernel::Kernel(QString name,QObject *parent) :
  RollingStockGroup(name,parent)
 {
  //super(name);
  log = new Logger("Kernel");
  log->debug(tr("New Kernel (%1)").arg(name));
 }

 /*public*/ QList<Car*> Kernel::getCars() {
     QList<Car*> cars = QList<Car*>();
     foreach (RollingStock* rs, getGroup()) {
         cars.append((Car*) rs);
     }
     return cars;
 }

 /*public*/ void Kernel::dispose()
 {
     while (getGroup().size() > 0) {
         Car* car = (Car*) getGroup().at(0);
         if (car != NULL) {
             car->setKernel(NULL);
         }
     }
     RollingStockGroup::dispose();
 }
}
