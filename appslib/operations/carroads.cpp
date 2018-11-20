#include "carroads.h"
#include "control.h"
#include "xml.h"
#include "carmanagerxml.h"

//CarRoads::CarRoads(QObject *parent) :
//  RollingStockAttribute(parent)
//{
//}
namespace Operations {
/**
 * Represents the road names that cars can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarRoads extends RollingStockAttribute {

 /*private*/ /*static*/ /*final*/ QString CarRoads::ROADS = tr("AA,ACL,ADCX,ADMX,AESX,ALTON,ATM,ATR,ATSF,ATW,B&O,BAR,BCK,BM,BN,BR,BR&S,BREX,BWCX,C&EI,C&IM,C&O,CACX,CB&Q,CCBX,CDLX,CG,CG&W,CM,CMSF,CMWX,CN,CNJ,CNW,CONX,COPR,CP,CRR,CTSE,CTT,CTTX,CV,D&H,D&M,D&RGW,EJ&E,ERIE,FCX,FDD&S,FEC,FW&D,G&F,GAT,GATX,GCR,GM&O,GN,GPEX,GRC,GRCX,GTW,IC,IGN,IN,KCS,KOT,KOTX,LN,LNE,LS&I,LV,MEC,MILW,MKT,MNS,MP,MPA,MRL,MSL,N&W,NC&SL,NH,NKP,NP,NYC,OTT,OTTX,PC,PFE,PM,PRR,PS&N,RDG,RE,REX,RF&P,RI,RP,RPX,RTC,RTCX,RUT,SAL,SDW,SDWX,SHP,SHPX,SLSF,SOO,SOU,SP,SSW,SUNX,T&P,TC,TP&W,UOCX,UP,UTL,UTLX,VGN,VN,VTR,W&LE,W&LG,WA,WAB,WDL,WDLX,WFEX,WM,WP,WRNX");
 /*public*/ /*static*/ /*final*/ QString CarRoads::CARROADS_CHANGED_PROPERTY = "CarRoads Length"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarRoads::CARROADS_NAME_CHANGED_PROPERTY = "CarRoads Name"; // NOI18N

 /*public*/ CarRoads::CarRoads(QObject *parent)
     :  RollingStockAttribute(parent)
 {
  log = new Logger("CarRoads");
  maxNameLengthSubType = 0;
  setProperty("InstanceManagerAutoDefault", "yes");

 }

 /**
  * record the single instance *
  */
 /*private*/ /*static*/ CarRoads* CarRoads::_instance = NULL;

 /*public*/ /*static*/ /*synchronized*/ CarRoads* CarRoads::instance() {
Logger*  log = new Logger("CarRoads");

     if (_instance == NULL) {
         if (log->isDebugEnabled()) {
             log->debug("CarRoads creating instance");
         }
         // create and load
         _instance = new CarRoads();
     }
     if (Control::showInstance) {
         log->debug(tr("CarRoads returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

    /*protected*/ QString CarRoads::getDefaultNames() {
        return ROADS;
    }

    /*public*/ void CarRoads::addName(QString road) {
        RollingStockAttribute::addName(road);
        setDirtyAndFirePropertyChange(CARROADS_CHANGED_PROPERTY, QVariant(), road);
    }

    /*public*/ void CarRoads::deleteName(QString road) {
        RollingStockAttribute::deleteName(road);
        setDirtyAndFirePropertyChange(CARROADS_CHANGED_PROPERTY, road, QVariant());
    }

    /*public*/ void CarRoads::replaceName(QString oldName, QString newName) {
        RollingStockAttribute::addName(newName);
        setDirtyAndFirePropertyChange(CARROADS_NAME_CHANGED_PROPERTY, oldName, newName);
        RollingStockAttribute::deleteName(oldName);
        if (newName == NULL) {
            setDirtyAndFirePropertyChange(CARROADS_CHANGED_PROPERTY, list.size() + 1, list.size());
        }
    }

    /**
     * Get the maximum character length of a road name when printing on a
     * manifest or switch list. Characters after the "-" are ignored.
     *
     * @return the maximum character length of a car type
     */
    /*public*/ int CarRoads::getMaxNameLength() {
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
            log->info(tr("Max road name (%1) length %2").arg(maxName).arg( maxNameLengthSubType));
        }
        return maxNameLengthSubType;
    }


    /**
     * Create an XML element to represent this Entry. This member has to remain
     * synchronized with the detailed DTD in operations-cars.dtd.
     *
     */    /*public*/ void CarRoads::store(QDomElement root, QDomDocument doc) {
 RollingStockAttribute::store(root, Xml::ROADS, Xml::ROAD, Xml::ROAD_NAMES, doc);
}

/*public*/ void CarRoads::load(QDomElement root) {

        RollingStockAttribute::load(root, Xml::ROADS, Xml::ROAD, Xml::ROAD_NAMES);
    }

    /*protected*/ void CarRoads::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
        // Set dirty
        CarManagerXml::instance()->setDirty(true);
        RollingStockAttribute::firePropertyChange(p, old, n);
    }
}
