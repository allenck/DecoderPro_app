#include "cartypes.h"
#include "xml.h"
#include "control.h"
#include "setup.h"
#include "carmanagerxml.h"
#include "instancemanager.h"

//CarTypes::CarTypes(QObject *parent) :
//  RollingStockAttribute(parent)
//{
//}
namespace Operations
{
/**
 * Represents the types of cars a railroad can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarTypes extends RollingStockAttribute {

/*private*/ /*static*/ /*final*/ QString CarTypes::TYPES = tr("Baggage,Boxcar,Caboose,Coal,Coilcar,FlatBulkHead,FlatBHPaper,FlatBHWood,FlatTimber,FlatTrailer,FlatWood,Flatcar,Gon-scrap,Gondola,HopChem,HopCmnt,HopCoal,HopCoal-Ety,HopGrain,HopSand,Hopper,MOW,MOWBox,Passenger,ReefMech,Reefer,ReeferIce,Stock,Tank Food,Tank Gas,Tank Kero,Tank Oil,Tank Veg");
/*private*/ /*static*/ /*final*/ QString CarTypes::CONVERT_TYPES = tr("BE,XM,NE,HT,FD-coil,FB,FB-paper,FB-wood,FL,FC,FM-wood,FM,GB-scrap,GA,HMR-chem,HMR-cmnt,HF-coal,HF-coalEty,HMR-grain,HMR-sand,HT,MWB,MWT,PA,RP,RB,RS,SA,TG,TM-gas,TM-kero,TM-oil,TG-veg"); // Used to convert from ARR to
// Descriptive
/*private*/ /*static*/ /*final*/ QString CarTypes::ARR_TYPES = tr("BE,BR,CA,CS,DA,DB,DL,FA,FB,FC,FCA,FD,FL,FM,FW,GA,GB,GD,GH,GS,GT,GW,HFA,HK,HM,HMR,HT,HTA,LC,LF,LG,LM,LO,LP,LS,LU,MA,MB,MWB,MWC,MWT,MMA,NE,PA,PAS,PC,PL,PO,PS,PT,PV,RA,RB,RP,RS,SA,SC,SM,ST,T,TA,TG,THI,TL,TM,TMU,TP,TPA,TRGA,TVI,TW,XC,XF,XL,XM,XP,XT");
/*public*/ /*static*/ /*final*/ QString CarTypes::CARTYPES_CHANGED_PROPERTY = "CarTypes Length"; // NOI18N
/*public*/ /*static*/ /*final*/ QString CarTypes::CARTYPES_NAME_CHANGED_PROPERTY = "CarTypes Name"; // NOI18N

/*private*/ /*static*/ CarTypes* CarTypes::_instance = NULL;


 /*public*/ CarTypes::CarTypes(QObject *parent)
     : RollingStockAttribute(parent)
 {
  log = new Logger("CarTypes");
  maxNameLengthSubType = 0;
  setProperty("InstanceManagerAutoDefault", "yes");

 }

 /*protected*/ QString CarTypes::getDefaultNames() {
     if (Setup::getCarTypes()==(Setup::AAR)) {
         return ARR_TYPES;
     }
     return TYPES;
 }

 /**
  * Changes the car types from descriptive to AAR, or the other way. Only
  * removes the default car type names from the list
  */
 /*public*/ void CarTypes::changeDefaultNames(QString type) {
     QStringList convert = CONVERT_TYPES.split(","); // NOI18N
     QStringList types = TYPES.split(","); // NOI18N
     if (convert.length() != types.length()) {
      log->error(tr(
                  "Properties file doesn't have equal length conversion strings, carTypeNames %1, carTypeConvert %2").arg(
                  types.length()).arg(convert.length()));
         return;
     }
     if (type==(Setup::DESCRIPTIVE)) {
         // first replace the types
      for (int i = 0; i < convert.length(); i++) {
             replaceName(convert[i], types[i]);
         }
         // remove AAR types
         QStringList aarTypes = ARR_TYPES.split(","); // NOI18N
         for (int i = 0; i < aarTypes.length(); i++) {
             list.removeOne(aarTypes[i]);
         }
         // add descriptive types
         for (int i = 0; i < types.length(); i++) {
             if (!list.contains(types[i])) {
                 list.append(types[i]);
             }
         }
     } else {
         // first replace the types
      for (int i = 0; i < convert.length(); i++) {
             replaceName(types[i], convert[i]);
         }
         // remove descriptive types
      for (int i = 0; i < types.length(); i++) {
             list.removeOne(types[i]);
         }
         // add AAR types
         types = ARR_TYPES.split(","); // NOI18N
         for (int i = 0; i < types.length(); i++) {
             if (!list.contains(types[i])) {
                 list.append(types[i]);
             }
         }
     }
 }

 /*public*/ void CarTypes::addName(QString type) {
     RollingStockAttribute::addName(type);
     maxNameLengthSubType = 0; // reset
     setDirtyAndFirePropertyChange(CARTYPES_CHANGED_PROPERTY, QVariant(), type);
 }

 /*public*/ void CarTypes::deleteName(QString type) {
     RollingStockAttribute::deleteName(type);
     maxNameLengthSubType = 0; // reset
     setDirtyAndFirePropertyChange(CARTYPES_CHANGED_PROPERTY, type, QVariant());
 }

 /*public*/ void CarTypes::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     maxNameLengthSubType = 0; // reset
     setDirtyAndFirePropertyChange(CARTYPES_NAME_CHANGED_PROPERTY, oldName, newName);
     // need to keep old name so location manager can replace properly
     RollingStockAttribute::deleteName(oldName);
 }

 /**
  * Get the maximum character length of a car type when printing on a
  * manifest or switch list. Car subtypes or characters after the "-" are
  * ignored.
  *
  * @return the maximum character length of a car type
  */
 /*public*/ int CarTypes::getMaxNameLength() {
     if (maxNameLengthSubType == 0) {
         QString maxName = "";
         maxNameLengthSubType = MIN_NAME_LENGTH;
         foreach (QString name, getNames()) {
             QStringList subString = name.split("-");
             if (subString[0].length() > maxNameLengthSubType) {
                 maxName = name;
                 maxNameLengthSubType = subString[0].length();
             }
         }
         log->info(tr("Max car type name (%1) length %2").arg(maxName).arg(maxNameLengthSubType));
     }
     return maxNameLengthSubType;
 }

 /**
  * Get the maximum character length of a car type including the sub type
  * characters.
  *
  * @return the maximum character length of a car type
  */
 /*public*/ int CarTypes::getMaxFullNameLength() {
     return RollingStockAttribute::getMaxNameLength();
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void CarTypes::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::TYPES, Xml::TYPE, Xml::CAR_TYPES, doc);
 }

 /*public*/ void CarTypes::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::TYPES, Xml::TYPE, Xml::CAR_TYPES);
 }

 /*protected*/ void CarTypes::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }

}
