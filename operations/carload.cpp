#include "carload.h"
#include "carloads.h"

//CarLoad::CarLoad(QObject *parent) : QObject(parent)
//{

//}
namespace Operations
{
/**
 * Represents a car load, includes pickup and drop comments.
 *
 * @author Daniel Boudreau (C) 2010
 *
 */
///*public*/ class CarLoad {

 /*public*/ /*static*/ /*final*/ QString CarLoad::NONE = "";

 /*public*/ /*static*/ /*final*/ QString CarLoad::PRIORITY_LOW = tr("Low");
 /*public*/ /*static*/ /*final*/ QString CarLoad::PRIORITY_HIGH = tr("High");

 /*public*/ /*static*/ /*final*/ QString CarLoad::LOAD_TYPE_EMPTY = tr("Empty");
 /*public*/ /*static*/ /*final*/ QString CarLoad::LOAD_TYPE_LOAD = tr("Load");

 /*public*/ /*static*/ /*final*/ QString CarLoad::SPLIT_CHAR = " & "; // used to combine car type and load in tracks and trains


 /*public*/ CarLoad::CarLoad(QString name, QObject* parent) : QObject(parent)
 {
  _priority = PRIORITY_LOW;
  _pickupComment = NONE;
  _dropComment = NONE;
  _loadType = LOAD_TYPE_LOAD;

  setName(name);
 }

 /*public*/ QString CarLoad::getName() {
     return _name;
 }

 /*public*/ void CarLoad::setName(QString name)
 {
  _name = name;
  if (name==(CarLoads::instance()->getDefaultEmptyName())) {
      setLoadType(LOAD_TYPE_EMPTY);
  }
 }

 /*public*/ QString CarLoad::getPriority() {
     return _priority;
 }

 /*public*/ void CarLoad::setPriority(QString priority) {
     _priority = priority;
 }

 /*public*/ QString CarLoad::getPickupComment() {
     return _pickupComment;
 }

 /*public*/ void CarLoad::setPickupComment(QString comment) {
     _pickupComment = comment;
 }

 /*public*/ QString CarLoad::getDropComment() {
     return _dropComment;
 }

 /*public*/ void CarLoad::setDropComment(QString comment) {
     _dropComment = comment;
 }

 /*public*/ QString CarLoad::getLoadType() {
     return _loadType;
 }

 /*public*/ void CarLoad::setLoadType(QString type) {
     _loadType = type;
 }

}
