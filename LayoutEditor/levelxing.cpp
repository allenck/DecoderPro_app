#include "levelxing.h"
#include "instancemanager.h"
#include "editlevelxingdlg.h"
#include "signalmast.h"
#include "signalmastlogic.h"
#include "signalmastlogicmanager.h"
#include "signalmastmanager.h"
#include "layoutblockroutetableaction.h"
#include "mathutil.h"
#include "signallingguitools.h"
#include "layouteditorfinditems.h"
//#include "layouttrackeditors.h"
#include "layouteditortoolbarpanel.h"
#include "levelxingeditor.h"


//LevelXing::LevelXing(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A LevelXing is two track segment on a layout that cross at an angle.
 * <P>
 * A LevelXing has four connection points, designated A, B, C, and D.
 *		At the crossing, A-C and B-D are straight segments.  A train proceeds
 *		through the crossing on either of these segments.
 * <P>
 * Each straight segment carries Block information.  A-C and B-D may be in the
 *		same or different Layout Blocks.
 * <P>
 * For drawing purposes, each LevelXing carries a center point and displacements
 *		for A and B.  The displacements for C = - the displacement for A, and the
 *		displacement for D = - the displacement for B.  The center point and these
 *      displacements may be adjusted by the user when in edit mode.
 * <P>
 * When LevelXings are first created, there are no connections.  Block information
 *		and connections are added when available.
 * <P>
 * Signal Head names are saved here to keep track of where signals are. LevelXing
 *		only serves as a storage place for signal head names. The names are placed here
 *		by Set Signals at Level Crossing in Tools menu.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 20802 $
 */

///*public*/ class LevelXing
//{

    // Defined text resource
    //ResourceBundle rb = ResourceBundle.getBundle("jmrit.display.layoutEditor.LayoutEditorBundle");


/**
 * constructor method
 */
/*public*/ LevelXing::LevelXing(QString id, QPointF c, LayoutEditor* myPanel)
 : LayoutTrack(id, c, myPanel)
{
 blockAC = NULL;
 blockBD = NULL;
 instance = NULL;
 layoutEditor = NULL;
 item = NULL;
 rects = NULL;

 // persistent instances variables (saved between sessions)
 //ident = "";
 blockNameAC = "";
 blockNameBD = "";
 signalAName = "";  // signal at A track junction
 signalBName = "";  // signal at B track junction
 signalCName = "";  // signal at C track junction
 signalDName = "";  // signal at D track junction

 signalAMastName = "";  // signal at A track junction
 signalBMastName = "";  // signal at B track junction
 signalCMastName = "";  // signal at C track junction
 signalDMastName = "";  // signal at D track junction

 sensorAName = "";  // sensor at A track junction
 sensorBName = "";  // sensor at B track junction
 sensorCName = "";  // sensor at C track junction
 sensorDName = "";  // sensor at D track junction    */

 sensorANamed = NULL; // sensor at A track junction
 sensorBNamed = NULL; // sensor at B track junction
 sensorCNamed = NULL; // sensor at C track junction
 sensorDNamed = NULL; // sensor at D track junction

 signalAHeadNamed = NULL; // signal at A track junction
 signalBHeadNamed = NULL; // signal at B track junction
 signalCHeadNamed = NULL; // signal at C track junction
 signalDHeadNamed = NULL; // signal at D track junction

 signalAMastNamed = NULL; // signal at A track junction
 signalBMastNamed = NULL; // signal at B track junction
 signalCMastNamed = NULL; // signal at C track junction
 signalDMastNamed = NULL; // signal at D track junction


 connectA = NULL;
 connectB = NULL;
 connectC = NULL;
 connectD = NULL;
 center = QPointF(50.0,50.0);
 dispA =  QPointF(-20.0,0.0);
 dispB =  QPointF(-14.0,14.0);
 connectAName = "";
 connectBName = "";
 connectCName = "";
 connectDName = "";
 active = true;
 sml = new QVector<SignalMast*>();
 editAdditionalMenu = new QVector<QMenu*>(0);
 viewAdditionalMenu = new QVector<QMenu*>(0);

 editOpen = false;
 needsRedraw = false;
 needsBlockUpdate = false;
 popup = NULL;
 block1Name = new QLineEdit();
 block2Name = new QLineEdit();
 editLevelXingFrame = NULL;

 instance = this;
 layoutEditor = myPanel;
// ident = id;
// center = c;
 editor = new LevelXingEditor(layoutEditor);

}

/*
 * Accessor methods
 */
//@Nonnull
/*public*/ QString LevelXing::getBlockNameAC() {
    QString result = "";
    if (namedLayoutBlockAC != nullptr) {
        result = namedLayoutBlockAC->getName();
    }
    return ((result == nullptr) ? "" : result);
}

//@Nonnull
/*public*/ QString LevelXing::getBlockNameBD() {
    QString result = getBlockNameAC();
    if (namedLayoutBlockBD != nullptr) {
        result = namedLayoutBlockBD->getName();
    }
    return result;
}

/*public*/ SignalHead* LevelXing::getSignalHead(GEOMETRY loc) {
    NamedBeanHandle<SignalHead*>* namedBean = nullptr;
    switch (loc) {
        case POINTA:
            namedBean = signalAHeadNamed;
            break;
        case POINTB:
            namedBean = signalBHeadNamed;
            break;
        case POINTC:
            namedBean = signalCHeadNamed;
            break;
        case POINTD:
            namedBean = signalDHeadNamed;
            break;
        default:
            log.warn(tr("%1.getSignalHead(%2)").arg(getName()).arg(loc));
            break;
    }
    if (namedBean != nullptr) {
        return namedBean->getBean();
    }
    return nullptr;
}

/*public*/ SignalMast* LevelXing::getSignalMast(GEOMETRY loc) {
    NamedBeanHandle<SignalMast*>* namedBean = nullptr;
    switch (loc) {
        case POINTA:
            namedBean = signalAMastNamed;
            break;
        case POINTB:
            namedBean = signalBMastNamed;
            break;
        case POINTC:
            namedBean = signalCMastNamed;
            break;
        case POINTD:
            namedBean = signalDMastNamed;
            break;
        default:
            log.warn(tr("%1.getSignalMast(%2)").arg(getName()).arg(loc));
            break;
    }
    if (namedBean != nullptr) {
        return namedBean->getBean();
    }
    return nullptr;
}

/*public*/ Sensor* LevelXing::getSensor(GEOMETRY loc) {
    NamedBeanHandle<Sensor*>* namedBean = nullptr;
    switch (loc) {
        case POINTA:
            namedBean = sensorANamed;
            break;
        case POINTB:
            namedBean = sensorBNamed;
            break;
        case POINTC:
            namedBean = sensorCNamed;
            break;
        case POINTD:
            namedBean = sensorDNamed;
            break;
        default:
            log.warn(tr("%1.getSensor(%2)").arg(getName()).arg(loc));
            break;
    }
    if (namedBean != nullptr) {
        return namedBean->getBean();
    }
    return nullptr;
}

//@Nonnull
/*public*/ QString LevelXing::getSignalAName() {
    if (signalAHeadNamed != nullptr) {
        return signalAHeadNamed->getName();
    }
    return "";
}

/*public*/ void LevelXing::setSignalAName(QString signalHead) {
    if (signalHead == nullptr || signalHead.isEmpty()) {
        signalAHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalAHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalAHeadNamed = nullptr;
    }
}

//@Nonnull
/*public*/ QString LevelXing::getSignalBName() {
    if (signalBHeadNamed != nullptr) {
        return signalBHeadNamed->getName();
    }
    return "";
}

/*public*/ void LevelXing::setSignalBName(QString signalHead) {
    if (signalHead == nullptr || signalHead.isEmpty()) {
        signalBHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalBHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalBHeadNamed = nullptr;
    }
}

//@Nonnull
/*public*/ QString LevelXing::getSignalCName() {
    if (signalCHeadNamed != nullptr) {
        return signalCHeadNamed->getName();
    }
    return "";
}

/*public*/ void LevelXing::setSignalCName(QString signalHead) {
    if (signalHead == nullptr || signalHead.isEmpty()) {
        signalCHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalCHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalCHeadNamed = nullptr;
    }
}

//@Nonnull
/*public*/ QString LevelXing::getSignalDName() {
    if (signalDHeadNamed != nullptr) {
        return signalDHeadNamed->getName();
    }
    return "";
}

/*public*/ void LevelXing::setSignalDName(QString signalHead) {
    if (signalHead == nullptr || signalHead.isEmpty()) {
        signalDHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalDHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalDHeadNamed = nullptr;
    }
}

/*public*/ void LevelXing::removeBeanReference(NamedBean* nb) {
    if (nb == nullptr) {
        return;
    }
    if (qobject_cast<SignalMast*>(nb)) {
        if (nb->equals(getSignalAMast())) {
            setSignalAMast("");
            return;
        }
        if (nb->equals(getSignalBMast())) {
            setSignalBMast("");
            return;
        }
        if (nb->equals(getSignalCMast())) {
            setSignalCMast("");
            return;
        }
        if (nb->equals(getSignalDMast())) {
            setSignalDMast("");
            return;
        }
    }
    if (qobject_cast<Sensor*>(nb)) {
        if (nb->equals(getSensorA())) {
            setSensorAName("");
            return;
        }
        if (nb->equals(getSensorB())) {
            setSensorBName("");
            return;
        }
        if (nb->equals(getSensorC())) {
            setSensorCName("");
            return;
        }
        if (nb->equals(getSensorD())) {
            setSensorDName("");
            return;
        }
    }
    if (qobject_cast<SignalHead*>(nb)) {
        if (nb->equals(getSignalHead(POINTA))) {
            setSignalAName("");
            return;
        }
        if (nb->equals(getSignalHead(POINTB))) {
            setSignalBName("");
            return;
        }
        if (nb->equals(getSignalHead(POINTC))) {
            setSignalCName("");
            return;
        }
        if (nb->equals(getSignalHead(POINTD))) {
            setSignalDName("");
            return;
        }
    }
}

/*public*/ QString LevelXing::getSignalAMastName() {
    if (signalAMastNamed != nullptr) {
        return signalAMastNamed->getName();
    }
    return "";
}

/*public*/ SignalMast* LevelXing::getSignalAMast()
{
 if (signalAMastNamed != NULL)
 {
     return signalAMastNamed->getBean();
 }
 return NULL;
}

/*public*/ SignalHead* LevelXing::getSignalHead(int loc) {
    NamedBeanHandle<SignalHead*>* namedBean = nullptr;
    switch (loc) {
        case POINTA:
            namedBean = signalAHeadNamed;
            break;
        case POINTB:
            namedBean = signalBHeadNamed;
            break;
        case POINTC:
            namedBean = signalCHeadNamed;
            break;
        case POINTD:
            namedBean = signalDHeadNamed;
            break;
        default:
            log.warn(tr("Unhandled loc: %1").arg(loc));
            break;
    }
    if (namedBean != nullptr) {
        return namedBean->getBean();
    }
    return nullptr;
}

/*public*/ void LevelXing::setSignalAMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalAMastNamed = NULL;
        return;
    }

    SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMast);
    if (mast != NULL) {
     signalAMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalAMastNamed = NULL;
    }
}


/*public*/ SignalMast* LevelXing::getSignalBMast() {
    if (signalBMastNamed != NULL) {
        return signalBMastNamed->getBean();
    }
    return NULL;
}

/*public*/ void LevelXing::setSignalBMast(QString signalMast)
{
    if (signalMast == NULL || signalMast==("")) {
        signalBMastNamed = NULL;
        return;
    }

    SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalBMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalBMastNamed = NULL;
    }
}

/*public*/ SignalMast* LevelXing::getSignalCMast() {
    if (signalCMastNamed != NULL) {
        return signalCMastNamed->getBean();
    }
    return NULL;
}

/*public*/ void LevelXing::setSignalCMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalCMastNamed = NULL;
        return;
    }

    SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalCMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalCMastNamed = NULL;
    }
}


/*public*/ SignalMast* LevelXing::getSignalDMast() {
    if (signalDMastNamed != NULL) {
        return signalDMastNamed->getBean();
    }
    return NULL;
}

/*public*/ void LevelXing::setSignalDMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalDMastNamed = NULL;
        return;
    }

    SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalDMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalDMastNamed = NULL;
    }
}

/*public*/ QString LevelXing::getSensorAName() {
    if(sensorANamed!=NULL)
        return sensorANamed->getName();
    return "";
}

/*public*/ Sensor* LevelXing::getSensorA() {
        if (sensorANamed != nullptr) {
            return sensorANamed->getBean();
        }
        return nullptr;
    }
/*public*/ void LevelXing::setSensorAName(QString sensorName)
{
 if(sensorName==NULL || sensorName==(""))
 {
  sensorANamed=NULL;
  return;
 }

 Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
 if (sensor != NULL)
 {
     sensorANamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
 }
 else
 {
  sensorANamed=NULL;
 }
}

/*public*/ QString LevelXing::getSensorBName() {
    if(sensorBNamed!=NULL)
        return sensorBNamed->getName();
    return "";
}

/*public*/ Sensor* LevelXing::getSensorB() {
    if (sensorBNamed != nullptr) {
        return sensorBNamed->getBean();
    }
    return nullptr;
}

/*public*/ void LevelXing::setSensorBName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorBNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorBNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorBNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorCName() {
    if(sensorCNamed!=NULL)
        return sensorCNamed->getName();
    return "";
}

/*public*/ Sensor* LevelXing::getSensorC() {
    if (sensorCNamed != nullptr) {
        return sensorCNamed->getBean();
    }
    return nullptr;
}

/*public*/ void LevelXing::setSensorCName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorCNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorCNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorCNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorDName() {
    if(sensorDNamed!=NULL)
        return sensorDNamed->getName();
    return "";
}

/*public*/ Sensor* LevelXing::getSensorD() {
    if (sensorDNamed != nullptr) {
        return sensorDNamed->getBean();
    }
    return nullptr;
}

/*public*/ void LevelXing::setSensorDName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorDNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorDNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorDNamed=NULL;
    }
}

/*public*/ LayoutTrack *LevelXing::getConnection(int location) throw (JmriException)
{
    switch (location) {
        case LEVEL_XING_A:
            return connectA;
        case LEVEL_XING_B:
            return connectB;
        case LEVEL_XING_C:
            return connectC;
        case LEVEL_XING_D:
            return connectD;
    }
    log.error("Invalid Point Type " + QString::number(location)); //I18IN
    throw JmriException("Invalid Point");
}

/*public*/ void LevelXing::setConnection(int location, LayoutTrack* o, int type) throw (JmriException) {
    if ((type != TRACK) && (type != NONE)) {
        log.error("unexpected type of connection to layoutturnout - " + QString::number(type));
        throw JmriException("unexpected type of connection to layoutturnout - " + QString::number(type));
    }
    switch (location) {
        case LEVEL_XING_A:
            connectA = o;
            break;
        case LEVEL_XING_B:
            connectB = o;
            break;
        case LEVEL_XING_C:
            connectC = o;
            break;
        case LEVEL_XING_D:
            connectD = o;
            break;
        default:
            log.error("Invalid Point Type " + QString::number(location)); //I18IN
            throw JmriException("Invalid Point");
    }
}

/*public*/ void LevelXing::setConnectA(LayoutTrack* o,int type) {
    connectA = o;
    if ( (connectA!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of A connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectB(LayoutTrack* o,int type) {
    connectB = o;
    if ( (connectB!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of B connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectC(LayoutTrack *o, int type) {
    connectC = o;
    if ( (connectC!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of C connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectD(LayoutTrack* o,int type) {
    connectD = o;
    if ( (connectD!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of D connection to levelXing - "+type);
    }
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockAC() {
    if ( (blockAC==NULL) && (blockNameAC.length()>0) ) {
        blockAC = layoutEditor->provideLayoutBlock(blockNameAC);
        if ( (blockAC!=NULL) && (blockAC==blockBD) )
                blockAC->decrementUse();
    }
    return blockAC;
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockBD() {
    if ( (blockBD==NULL) && (blockNameBD.length()>0) ) {
        blockBD = layoutEditor->provideLayoutBlock(blockNameBD);
        if ( (blockBD!=NULL) && (blockAC==blockBD) )
                blockBD->decrementUse();
    }
    return blockBD;
}
/*public*/ QPointF LevelXing::getCoordsCenter() {return center;}
/*public*/ QPointF  LevelXing::getCoordsA() {
    double x = center.x() + dispA.x();
    double y = center.y() + dispA.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsB() {
    double x = center.x() + dispB.x();
    double y = center.y() + dispB.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsC() {
    double x = center.x() - dispA.x();
    double y = center.y() - dispA.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsD() {
    double x = center.x() - dispB.x();
    double y = center.y() - dispB.y();
    return  QPointF(x,y);
}

/**
 * Add Layout Blocks
 */
/*public*/ void LevelXing::setLayoutBlockAC (LayoutBlock* newLayoutBlock) {
 LayoutBlock* blockAC = getLayoutBlockAC();
 LayoutBlock* blockBD = getLayoutBlockBD();
 if (blockAC != newLayoutBlock) {
     // block 1 has changed, if old block exists, decrement use
     if ((blockAC != nullptr) && (blockAC != blockBD)) {
         blockAC->decrementUse();
     }
     blockAC = newLayoutBlock;
     if (newLayoutBlock != nullptr) {
         namedLayoutBlockAC = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
     } else {
         namedLayoutBlockAC = nullptr;
     }

     // decrement use if block was previously counted
     if ((blockAC != nullptr) && (blockAC == blockBD)) {
         blockAC->decrementUse();
     }
 }
}

/*public*/ void LevelXing::setLayoutBlockBD (LayoutBlock* newLayoutBlock) {
 LayoutBlock* blockAC = getLayoutBlockAC();
 LayoutBlock* blockBD = getLayoutBlockBD();
 if (blockBD != newLayoutBlock) {
     // block 1 has changed, if old block exists, decrement use
     if ((blockBD != nullptr) && (blockBD != blockAC)) {
         blockBD->decrementUse();
     }
     blockBD = newLayoutBlock;
     if (newLayoutBlock != nullptr) {
         namedLayoutBlockBD = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
     } else {
         namedLayoutBlockBD = nullptr;
     }
     // decrement use if block was previously counted
     if ((blockBD != nullptr) && (blockBD == blockAC)) {
         blockBD->decrementUse();
     }
 }
}

/*private*/ void LevelXing::updateBlockInfo() {
    LayoutBlock* b1 = NULL;
    LayoutBlock* b2 = NULL;
    if (blockAC!=NULL) blockAC->updatePaths();
    if (connectA!=NULL) {
        b1 = ((TrackSegment*)connectA)->getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockAC)) b1->updatePaths();
    }
    if (connectC!=NULL) {
        b2 = ((TrackSegment*)connectC)->getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockAC)&&(b2!=b1)) b2->updatePaths();
    }
    if (blockBD!=NULL) blockBD->updatePaths();
    if (connectB!=NULL) {
        b1 = ((TrackSegment*)connectB)->getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockBD)) b1->updatePaths();
    }
    if (connectD!=NULL) {
        b2 = ((TrackSegment*)connectD)->getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockBD)&&(b2!=b1)) b2->updatePaths();
    }
    reCheckBlockBoundary();
}

void LevelXing::removeSML(SignalMast* signalMast) {
    if (signalMast == nullptr) {
        return;
    }
    if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled() && ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->isSignalMastUsed(signalMast)) {
        SignallingGuiTools::removeSignalMastLogic(nullptr, signalMast);
    }
}

/**
 * Methods to test if mainline track or not
 *  Returns true if either connecting track segment is mainline
 *  Defaults to not mainline if connecting track segments are missing
 */
/*public*/ bool LevelXing::isMainlineAC() {
    if ( ((connectA != NULL) && (((TrackSegment*)connectA)->isMainline())) ||
        ((connectB != NULL) && (((TrackSegment*)connectB)->isMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}
/*public*/ bool LevelXing::isMainlineBD() {
    if ( ((connectB != NULL) && (((TrackSegment*)connectB)->isMainline())) ||
        ((connectD != NULL) && (((TrackSegment*)connectD)->isMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * draw this level crossing
 *
 * @param g2 the graphics port to draw to
 */
//@Override
/*protected*/ void LevelXing::draw1(EditScene* g2, bool isMain, bool isBlock) {


 invalidateItem(g2,itemGroup);
 if(itemGroup == nullptr)
 {
  itemGroup = new QGraphicsItemGroup();
  itemGroup->setZValue(Editor::HANDLES+1);
  g2->addItem(itemGroup);
 }

 if (isMain == isMainlineAC()) {
  if (isBlock) {
      layoutEditor->drawingStroke.setColor(setColorForTrackBlock(g2, getLayoutBlockAC()));
  }
  //g2.draw(new Line2D.Double(getCoordsA(), getCoordsC()));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(getCoordsA().x(), getCoordsA().y(), getCoordsC().x(), getCoordsC().y());
  lineItem->setPen(layoutEditor->drawingStroke);
  itemGroup->addToGroup(lineItem);
 }
 if (isMain == isMainlineBD())
 {
  if (isBlock) {
      layoutEditor->drawingStroke.setColor(setColorForTrackBlock(g2, getLayoutBlockBD()));
  }
  //g2.draw(new Line2D.Double(getCoordsB(), getCoordsD()));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(getCoordsB().x(), getCoordsB().y(), getCoordsD().x(), getCoordsD().y());
  lineItem->setPen(layoutEditor->drawingStroke);
  itemGroup->addToGroup(lineItem);
 }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LevelXing::draw2(EditScene* g2, bool isMain, float railDisplacement) {
    QPointF pA = getCoordsA();
    QPointF pB = getCoordsB();
    QPointF pC = getCoordsC();
    QPointF pD = getCoordsD();
    QPointF pM = getCoordsCenter();

    QPointF vAC = MathUtil::normalize(MathUtil::subtract(pC, pA), railDisplacement);
    double dirAC_DEG = MathUtil::computeAngleDEG(pA, pC);
    QPointF vACo = MathUtil::orthogonal(vAC);
    QPointF pAL = MathUtil::subtract(pA, vACo);
    QPointF pAR = MathUtil::add(pA, vACo);
    QPointF pCL = MathUtil::subtract(pC, vACo);
    QPointF pCR = MathUtil::add(pC, vACo);

    QPointF vBD = MathUtil::normalize(MathUtil::subtract(pD, pB), railDisplacement);
    double dirBD_DEG = MathUtil::computeAngleDEG(pB, pD);
    QPointF vBDo = MathUtil::orthogonal(vBD);
    QPointF pBL = MathUtil::subtract(pB, vBDo);
    QPointF pBR = MathUtil::add(pB, vBDo);
    QPointF pDL = MathUtil::subtract(pD, vBDo);
    QPointF pDR = MathUtil::add(pD, vBDo);

    double deltaDEG = MathUtil::absDiffAngleDEG(dirAC_DEG, dirBD_DEG);
    double deltaRAD = qDegreesToRadians(deltaDEG);

    double hypotK = railDisplacement / qCos((M_PI - deltaRAD) / 2.0);
    double hypotV = railDisplacement / qCos(deltaRAD / 2.0);

    log.debug(tr("dir AC: %1, BD: %2, diff: %3").arg(dirAC_DEG).arg(dirBD_DEG).arg(deltaDEG));

    QPointF vDisK = MathUtil::normalize(MathUtil::add(vAC, vBD), hypotK);
    QPointF vDisV = MathUtil::normalize(MathUtil::orthogonal(vDisK), hypotV);
    QPointF pKL = MathUtil::subtract(pM, vDisK);
    QPointF pKR = MathUtil::add(pM, vDisK);
    QPointF pVL = MathUtil::subtract(pM, vDisV);
    QPointF pVR = MathUtil::add(pM, vDisV);

    invalidateItem(g2,itemGroup);
    if(itemGroup == nullptr)
    {
     itemGroup = new QGraphicsItemGroup();
     itemGroup->setZValue(Editor::HANDLES+1);
     g2->addItem(itemGroup);
    }

    if (isMain == isMainlineAC()) {
        // this is the *2.0 vector (rail gap) for the AC diamond parts
        QPointF vAC2 = MathUtil::normalize(vAC, 2.0);
        // KL toward C, VR toward A, VL toward C and KR toward A
        QPointF pKLtC = MathUtil::add(pKL, vAC2);
        QPointF pVRtA = MathUtil::subtract(pVR, vAC2);
        QPointF pVLtC = MathUtil::add(pVL, vAC2);
        QPointF pKRtA = MathUtil::subtract(pKR, vAC2);

        // draw right AC rail: AR====KL == VR====CR
        //g2.draw(new Line2D.Double(pAR, pKL));
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pKL.x(), pKL.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pKLtC, pVRtA));
        lineItem = new QGraphicsLineItem(pKLtC.x(), pKLtC.y(), pVRtA.x(), pVRtA.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pVR, pCR));
        lineItem = new QGraphicsLineItem(pVR.x(), pVR.y(), pCR.x(), pCR.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);

        // draw left AC rail: AL====VL == KR====CL
        //g2.draw(new Line2D.Double(pAL, pVL));
        lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pVL.x(), pVL.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pVLtC, pKRtA));
        lineItem = new QGraphicsLineItem(pVLtC.x(), pVLtC.y(), pKRtA.x(), pKRtA.y());
        //g2.draw(new Line2D.Double(pKR, pCL));
    lineItem = new QGraphicsLineItem(pKR.x(), pKR.y(), pCL.x(), pCL.y());
    }
    if (isMain == isMainlineBD())
    {
     // this is the *2.0 vector (rail gap) for the BD diamond parts
     QPointF vBD2 = MathUtil::normalize(vBD, 2.0);
     // VR toward D, KR toward B, KL toward D and VL toward B
     QPointF pVRtD = MathUtil::add(pVR, vBD2);
     QPointF pKRtB = MathUtil::subtract(pKR, vBD2);
     QPointF pKLtD = MathUtil::add(pKL, vBD2);
     QPointF pVLtB = MathUtil::subtract(pVL, vBD2);

     // draw right BD rail: BR====VR == KR====DR
     //g2.draw(new Line2D.Double(pBR, pVR));
     QGraphicsLineItem* lineItem = new QGraphicsLineItem(pBR.x(), pBR.y(), pVR.x(), pVR.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
     //g2.draw(new Line2D.Double(pVRtD, pKRtB));
     lineItem = new QGraphicsLineItem(pVRtD.x(), pVRtD.y(), pKRtB.x(), pKRtB.y());
     //g2.draw(new Line2D.Double(pKR, pDR));
     lineItem = new QGraphicsLineItem(pKR.x(), pKR.y(), pDR.x(), pDR.y());

     // draw left BD rail: BL====KL == VL====DL
     //g2.draw(new Line2D.Double(pBL, pKL));
     lineItem = new QGraphicsLineItem(pBL.x(), pBL.y(), pKL.x(), pKL.y());
     //g2.draw(new Line2D.Double(pKLtD, pVLtB));
     lineItem = new QGraphicsLineItem(pKLtD.x(), pKLtD.y(), pVLtB.x(), pVLtB.y());
     //g2.draw(new Line2D.Double(pVL, pDL));
     lineItem = new QGraphicsLineItem(pVL.x(), pVL.y(), pDL.x(), pDL.y());
    }
//    if(isMain)
//    {
//     itemMain = itemGroup;
//     g2->addItem(itemMain);
//    }
//    else
//    {
//     itemSide = itemGroup;
//     g2->addItem(itemSide);
//    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LevelXing::highlightUnconnected(EditScene* g2, int specificType)
{
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
  QPen stroke = QPen(defaultTrackColor, 1);

    if (((specificType == NONE) || (specificType == LEVEL_XING_A))
            && (getConnectA() == nullptr)) {
        //g2.fill(layoutEditor.trackControlCircleAt(getCoordsA()));
     QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsA());
     ellipseItem->setPen(stroke);
     itemGroup->addToGroup(ellipseItem);
    }

    if (((specificType == NONE) || (specificType == LEVEL_XING_B))
            && (getConnectB() == nullptr)) {
        //g2.fill(layoutEditor.trackControlCircleAt(getCoordsB()));
     QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsB());
     ellipseItem->setPen(stroke);
     itemGroup->addToGroup(ellipseItem);
    }

    if (((specificType == NONE) || (specificType == LEVEL_XING_C))
            && (getConnectC() == nullptr)) {
        //g2.fill(layoutEditor.trackControlCircleAt(getCoordsC()));
     QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsC());
     ellipseItem->setPen(stroke);
     itemGroup->addToGroup(ellipseItem);
    }

    if (((specificType == NONE) || (specificType == LEVEL_XING_D))
            && (getConnectD() == nullptr)) {
        //g2.fill(layoutEditor.trackControlCircleAt(getCoordsD()));
     QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsD());
     ellipseItem->setPen(stroke);
     itemGroup->addToGroup(ellipseItem);
    }

    ((QGraphicsItemGroup*)item)->addToGroup(itemGroup);
}

//@Override
/*protected*/ void LevelXing::drawEditControls(EditScene* g2)
{
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 if(rects!=nullptr && rects->scene()!=nullptr)
 {
  g2->removeItem(rects);
  rects = nullptr;
 }
    //g2.setColor(defaultTrackColor);
 QPen stroke = layoutEditor->drawingStroke;

    //TODO:uncomment this line g2.draw(layoutEditor.trackEditControlCircleAt(getCoordsCenter()));

    if (getConnectA() == nullptr) {
        //g2.setColor(Color.magenta);
     stroke.setColor(Qt::magenta);
    } else {
        //g2.setColor(Color.blue);
     stroke.setColor(Qt::blue);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(getCoordsA()));
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsA()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectB() == nullptr) {
        //g2.setColor(Color.red);
    stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(getCoordsB()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsB()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectC() == nullptr) {
        //g2.setColor(Color.red);
     stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(getCoordsC()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsC()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectD() == nullptr) {
        //g2.setColor(Color.red);
     stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(getCoordsD()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsB()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    rects = itemGroup;
    g2->addItem(rects);
}

//@Override
/*protected*/ void LevelXing::drawTurnoutControls(EditScene* g2) {
    // LevelXings don't have turnout controls...
    // nothing to see here... move along...
}
//@Override
/*public*/ void LevelXing::reCheckBlockBoundary() const {
    // nothing to see here... move along...
}


/**
 * Modify coordinates methods
 */
/*public*/ void LevelXing::setCoordsCenter(QPointF p) {
    center = p;
}
/*public*/ void LevelXing::setCoordsA(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispA = QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsB(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB = QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsC(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispA =  QPointF(x,y);
}
/*public*/ void LevelXing::setCoordsD(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(x,y);
}
/*public*/ void LevelXing::scaleCoords(double xFactor, double yFactor) {
    QPointF pt (round(center.x()*xFactor),
                                    round(center.y()*yFactor));
    center = pt;
    pt =  QPointF(round(dispA.x()*xFactor),
                                    round(dispA.y()*yFactor));
    dispA = pt;
    pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
}
double LevelXing::round (double x) {
    int i = (int)(x+0.5);
    return i;
}

/**
 * translate this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to translate X coordinates
 * @param yFactor the amount to translate Y coordinates
 */
//@Override
/*public*/ void LevelXing::translateCoords(double xFactor, double yFactor) {
    QPointF factor =  QPointF(xFactor, yFactor);
    center = MathUtil::add(center, factor);
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ int LevelXing::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    int result = NONE;  // assume point not on connection
    //note: optimization here: instead of creating rectangles for all the
    // points to check below, we create a rectangle for the test point
    // and test if the points below are in that rectangle instead.
    QRectF r = layoutEditor->trackControlCircleRectAt(hitPoint);
    QPointF p, minPoint = MathUtil::zeroPoint2D;

    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double distance, minDistance = std::numeric_limits<double>::infinity();//POSITIVE_INFINITY;

    //check the center point
    if (!requireUnconnected) {
        p = getCoordsCenter();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = LEVEL_XING_CENTER;
        }
    }

    //check the A connection point
    if (!requireUnconnected || (getConnectA() == nullptr)) {
        p = getCoordsA();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = LEVEL_XING_A;
        }
    }

    //check the B connection point
    if (!requireUnconnected || (getConnectB() == nullptr)) {
        p = getCoordsB();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = LEVEL_XING_B;
        }
    }

    //check the C connection point
    if (!requireUnconnected || (getConnectC() == nullptr)) {
        p = getCoordsC();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = LEVEL_XING_C;
        }
    }

    //check the D connection point
    if (!requireUnconnected || (getConnectD() == nullptr)) {
        p = getCoordsD();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = LEVEL_XING_D;
        }
    }
    if ((useRectangles && !r.contains(minPoint))
            || (!useRectangles && (minDistance > circleRadius))) {
        result = NONE;
    }
    return result;
}   // findHitPointType

/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LevelXing::setObjects(LayoutEditor* p) {
    connectA = p->getFinder()->findTrackSegmentByName(connectAName);
    connectB = p->getFinder()->findTrackSegmentByName(connectBName);
    connectC = p->getFinder()->findTrackSegmentByName(connectCName);
    connectD = p->getFinder()->findTrackSegmentByName(connectDName);

    LayoutBlock* lb;
    if (!tLayoutBlockNameAC.isEmpty()) {
        lb = p->provideLayoutBlock(tLayoutBlockNameAC);
        QString userName = lb->getUserName();
        if (userName != nullptr) {
            namedLayoutBlockAC = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
            if (namedLayoutBlockBD != namedLayoutBlockAC) {
                lb->incrementUse();
            }
        } else {
            log.error(tr("LevelXing.setObjects(); bad blockname AC ''%1''").arg(tLayoutBlockNameAC));
            namedLayoutBlockAC = nullptr;
        }
        tLayoutBlockNameAC = nullptr; //release this memory
    }

    if (!tLayoutBlockNameBD.isEmpty()) {
        lb = p->provideLayoutBlock(tLayoutBlockNameBD);
        QString userName = lb->getUserName();
        if (userName != nullptr) {
            namedLayoutBlockBD = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
            if (namedLayoutBlockBD != namedLayoutBlockAC) {
                lb->incrementUse();
            }
        } else {
            log.error(tr("%1.setObjects(); bad blockname BD ''%2''").arg(this->metaObject()->className()).arg(tLayoutBlockNameBD));
            namedLayoutBlockBD = nullptr;
        }
        tLayoutBlockNameBD = nullptr; //release this memory
    }
}


/**
 * Display popup menu for information and editing
 */
/*protected*/ QMenu *LevelXing::showPopup(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }

 AbstractAction* act;

 if(layoutEditor->isEditable())
 {
  QAction* jmi = popup->addSection(tr("Level Crossing"));
  bool blockACAssigned = false;
  bool blockBDAssigned = false;
  if (getLayoutBlockAC() == nullptr)
  {
   popup->addAction(new QAction(tr("Block %1 Not Set").arg("AC"),this));
  }
  else
  {
   jmi = popup->addSection( tr("Block %1").arg("AC") + getLayoutBlockAC()->getDisplayName());
   blockACAssigned = true;
  }
  jmi->setEnabled(false);

  if (getLayoutBlockBD() == nullptr) {
   jmi = popup->addSection(tr("Block %1 Not Set").arg("BD"));
  }
  else
  {
   jmi = popup->addSection(tr("Block %1").arg("BD") + getLayoutBlockBD()->getDisplayName());
   blockBDAssigned = true;
  }
  jmi->setEnabled(false);

  // if there are any track connections
  if ((connectA != nullptr) || (connectB != nullptr)
          || (connectC != nullptr) || (connectD != nullptr))
  {
   QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
   if (connectA != nullptr)
   {
       connectionsMenu->addAction(act = new AbstractAction( "A" + connectA->getName(),this));
//        {
//            @Override
//            public void actionPerformed(ActionEvent e) {
       connect(act, &QAction::triggered, [=]{
               LayoutEditorFindItems* lf = layoutEditor->getFinder();
               LayoutTrack* lt = lf->findObjectByName(connectA->getName());
               // this shouldn't ever be null... however...
               if (lt != nullptr) {
                   layoutEditor->setSelectionRect(lt->getBounds());
                   lt->showPopup();
               }
//            }
       });
   }
   if (connectB != nullptr) {
       connectionsMenu->addAction(act = new AbstractAction( "B" + connectB->getName(), this));
//        {
//            @Override
//            public void actionPerformed(ActionEvent e) {
       connect(act, &QAction::triggered, [=]{
               LayoutEditorFindItems* lf = layoutEditor->getFinder();
               LayoutTrack* lt = lf->findObjectByName(connectB->getName());
               // this shouldn't ever be null... however...
               if (lt != nullptr) {
                   layoutEditor->setSelectionRect(lt->getBounds());
                   lt->showPopup();
               }
//            }
       });
   }
   if (connectC != nullptr) {
       connectionsMenu->addAction(new AbstractAction("C" + connectC->getName(),this));
//        {
//            @Override
//            public void actionPerformed(ActionEvent e) {
       connect(act, &QAction::triggered, [=]{
               LayoutEditorFindItems* lf = layoutEditor->getFinder();
               LayoutTrack* lt = lf->findObjectByName(connectC->getName());
               // this shouldn't ever be null... however...
               if (lt != nullptr) {
                   layoutEditor->setSelectionRect(lt->getBounds());
                   lt->showPopup();
               }
//            }
       });
   }
   if (connectD != nullptr) {
       connectionsMenu->addAction(act = new AbstractAction("D" + connectD->getName(), this));
//        {
//            @Override
//            public void actionPerformed(ActionEvent e) {
       connect(act, &QAction::triggered, [=]{
               LayoutEditorFindItems* lf = layoutEditor->getFinder();
               LayoutTrack* lt = lf->findObjectByName(connectD->getName());
               // this shouldn't ever be null... however...
               if (lt != nullptr) {
                   layoutEditor->setSelectionRect(lt->getBounds());
                   lt->showPopup();
               }
//            }
       });
   }
   popup->addMenu(connectionsMenu);
  }

  popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));

  QAction* hiddenCheckBoxMenuItem = new QAction(tr("Hidden"), this);
  hiddenCheckBoxMenuItem->setCheckable(true);
  hiddenCheckBoxMenuItem->setChecked(hidden);
  popup->addAction(hiddenCheckBoxMenuItem);
  //hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(hiddenCheckBoxMenuItem, &QAction::triggered, [=]{
      setHidden(hiddenCheckBoxMenuItem->isChecked());
  });

  popup->addAction(act = new AbstractAction(tr("Edit"), this));
//  {
//      @Override
//      public void actionPerformed(ActionEvent e) {
  connect(act, &QAction::triggered, [=]{
//          layoutEditor->getLayoutTrackEditors()->editLevelXing(this);
      editor->editLayoutTrack(this);
//      }
  });
  popup->addAction(act = new AbstractAction(tr("Delete"),this));
//  {
//      @Override
//      public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
          if (canRemove() && layoutEditor->removeLevelXing(this)) {
              // Returned true if user did not cancel
              remove();
              dispose();
          }
//      }
  });
  if (blockACAssigned && blockBDAssigned) {
      AbstractAction* ssaa = new AbstractAction(tr("Set Signal Heads..."), this);
//      {
//          @Override
//          public void actionPerformed(ActionEvent e) {
      connect(ssaa, &AbstractAction::triggered, [=]{
              // bring up signals at level crossing tool dialog
              LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
              layoutEditor->getLETools()->
                      setSignalsAtLevelXingFromMenu(this,
                              letbp->signalIconEditor,
                              letbp->signalFrame);
//          }
      });
      QMenu* jm = new QMenu(tr("Signal Heads"));
      if (layoutEditor->getLETools()->
              addLevelXingSignalHeadInfoToMenu(this, jm)) {
          jm->addAction(ssaa);
          popup->addMenu(jm);
      } else {
          popup->addAction(ssaa);
      }
  }

  /*final*/ QVector<QString>* boundaryBetween = getBlockBoundaries();
  bool blockBoundaries = false;
  if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
  {
      if (blockACAssigned && !blockBDAssigned) {
          popup->addAction(act = new AbstractAction(tr("View Block Routing"), this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
                  routeTableAction->actionPerformed(/*e*/);
//              }
          });
      } else if (!blockACAssigned && blockBDAssigned) {
          popup->addAction(act = new AbstractAction(tr("View Block Routing"), this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockBD());
                  routeTableAction->actionPerformed(/*e*/);
//              }
          });
      } else if (blockACAssigned && blockBDAssigned) {
          QMenu* viewRouting = new QMenu(tr("View Block Routing"));
          viewRouting->addAction(act = new AbstractAction(getLayoutBlockAC()->getDisplayName(), this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  AbstractAction* routeTableAction = new LayoutBlockRouteTableAction(getLayoutBlockAC()->getDisplayName(), getLayoutBlockAC());
                  routeTableAction->actionPerformed(/*e*/);
//              }
          });

          viewRouting->addAction(act = new AbstractAction(getLayoutBlockBD()->getDisplayName(), this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  AbstractAction* routeTableAction = new LayoutBlockRouteTableAction(getLayoutBlockBD()->getDisplayName(), getLayoutBlockBD());
                  routeTableAction->actionPerformed(/*e*/);
//              }
          });

          popup->addMenu(viewRouting);
      }
  }

  for (int i = 0; i < 4; i++) {
      if (boundaryBetween->at(i) != "") {
          blockBoundaries = true;
      }
  }
  if (blockBoundaries) {
      popup->addAction(act = new AbstractAction(tr("Set Signal Masts..."), this));
//      {
//          @Override
//          public void actionPerformed(ActionEvent e) {
      connect(act, &QAction::triggered, [=]{
              LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
              layoutEditor->getLETools()->
                      setSignalMastsAtLevelXingFromMenu(
                              this, boundaryBetween,
                              letbp->signalFrame);
//          }
      });
      popup->addAction(act = new AbstractAction(tr("Set Sensors..."), this));
//      {
//          @Override
//          public void actionPerformed(ActionEvent e) {
      connect(act, &QAction::triggered, [=]{
              LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
              layoutEditor->getLETools()->setSensorsAtLevelXingFromMenu(
                      this, boundaryBetween,
                      letbp->sensorIconEditor,
                      letbp->sensorFrame);
//          }
      });
  }

  layoutEditor->setShowAlignmentMenu(popup);
  //popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
  popup->exec(QCursor::pos());
 } else if (!viewAdditionalMenu->isEmpty()) {
    setAdditionalViewPopUpMenu(popup);
    //popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
    popup->exec(QCursor::pos());
 }
 return popup;
}   // showPopup

// this should only be used for debugging
//@Override
/*public*/ QString LevelXing::toString() {
    return "LevelXing " + getName();
}

/*public*/ QVector<QString>* LevelXing::getBlockBoundaries()
{
  /*final*/ QVector<QString>* boundaryBetween = new QVector<QString>(4,"");
  if ( (blockNameAC!=NULL) && (blockNameAC!=("")) && (blockAC!=NULL) )
  {
     if (/*(connectA instanceof TrackSegment*) &&*/ (((TrackSegment*)connectA)->getLayoutBlock()!=blockAC)){
         try {
             boundaryBetween->replace(0,((TrackSegment*)connectA)->getLayoutBlock()->getDisplayName()+ " - " + blockAC->getDisplayName());
         } catch (NullPointerException* e){
             //Can be considered normal if tracksegement hasn't yet been allocated a block
             log.debug("TrackSegement at connection A doesn't contain a layout block");
         }
     }
     if (/*(connectC instanceof TrackSegment) &&*/ (((TrackSegment*)connectC)->getLayoutBlock()!=blockAC))
     {
      try {
          boundaryBetween->replace(2,(((TrackSegment*)connectC)->getLayoutBlock()->getDisplayName()+ " - " + blockAC->getDisplayName()));
      } catch (NullPointerException *e){
          //Can be considered normal if tracksegement hasn't yet been allocated a block
          log.debug("TrackSegement at connection C doesn't contain a layout block");
      }
     }
    }
    if ( (blockNameBD!=NULL) && (blockNameBD!=("")) && (blockBD!=NULL) )
    {
     if (/*(connectB instanceof TrackSegment) &&*/ (((TrackSegment*)connectB)->getLayoutBlock()!=blockBD)){
         try {
             boundaryBetween->replace(1,(((TrackSegment*)connectB)->getLayoutBlock()->getDisplayName()+ " - " + blockBD->getDisplayName()));
         } catch (NullPointerException* e){
             //Can be considered normal if tracksegement hasn't yet been allocated a block
             log.debug("TrackSegement at connection B doesn't contain a layout block");
         }
     }
     if (/*(connectD instanceof TrackSegment) &&*/ (((TrackSegment*)connectD)->getLayoutBlock()!=blockBD))
     {
      try {
          boundaryBetween->replace(3,(((TrackSegment*)connectD)->getLayoutBlock()->getDisplayName()+ " - " + blockBD->getDisplayName()));
      } catch (NullPointerException* e){
          //Can be considered normal if tracksegement hasn't yet been allocated a block
          log.debug("TrackSegement at connection D doesn't contain a layout block");
      }
     }
    }
    return boundaryBetween;
}



/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void LevelXing::dispose() {
    if (popup != NULL) popup->clear();
    popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void LevelXing::remove() {
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LevelXing::isActive() {
    return active;
}


/*public*/ void LevelXing::addSignalMastLogic(SignalMast* sm){
    if (sml->contains(sm))
        return;
    if(sml->isEmpty()){
        sml->append(sm);
        return;
    }
    SignalMastLogic* sl = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(sm);
    for(int i = 0; i<sml->size(); i++){
        SignalMastLogic* s = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(sml->at(i));
        if (s!=NULL){
            s->setConflictingLogic(sm, this);
        }
        sl->setConflictingLogic(sml->at(i), this);
    }
    sml->append(sm);
}

/*public*/ void LevelXing::removeSignalMastLogic(SignalMast* sm){
    if(!sml->contains(sm))
        return;
    sml->remove(sml->indexOf(sm));
    if(sml->isEmpty()){
        return;
    }
    for(int i = 0; i<sml->size(); i++){
        SignalMastLogic* s = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(sm);
        if (s!=NULL)
            s->removeConflictingLogic(sm, this);
    }
}


/*public*/ void LevelXing::addEditPopUpMenu(QMenu* menu){
    if(!editAdditionalMenu->contains(menu)){
        editAdditionalMenu->append(menu);
    }
}

/*public*/ void LevelXing::addViewPopUpMenu(QMenu* menu){
    if(!viewAdditionalMenu->contains(menu)){
        viewAdditionalMenu->append(menu);
    }
}

/*public*/ void LevelXing::setAdditionalEditPopUpMenu(QMenu* popup){
    if(editAdditionalMenu->isEmpty())
        return;
    popup->addSeparator();
//    foreach(QAction* mi, editAdditionalMenu){
//        popup->addAction(mi);
//    }
}

/*public*/ void LevelXing::setAdditionalViewPopUpMenu(QMenu* popup){
    if(viewAdditionalMenu->isEmpty())
        return;
    popup->addSeparator();
//    for(JMenuItem mi:viewAdditionalMenu){
//        popup.add(mi);
//    }
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LevelXing.class.getName());
void LevelXing::invalidate(QGraphicsScene* g2)
{
 if(item != NULL && item->scene() != 0)
 {
  Q_ASSERT(item->scene()!=0);
  g2->removeItem(item);
 }
 item = NULL;
 if(rects != NULL && rects->scene()!=0)
 {
  g2->removeItem(rects);
 }
 rects = NULL;
}
#if 0
void LevelXing::drawXings(LayoutEditor* editor, QGraphicsScene* g2)
{
// if(item != NULL)
// {
//  g2->removeItem(item);
// }
 item = new QGraphicsItemGroup();

 if ( isMainlineBD() && (!isMainlineAC()) )
 {
  drawXingAC(editor);
  drawXingBD(editor);
 }
 else
 {
  drawXingBD(editor);
  drawXingAC(editor);
 }
 g2->addItem(item);
}

/*private*/ void LevelXing::drawXingAC(LayoutEditor* editor)
{
  // set color - check for an AC block
  LayoutBlock* b = getLayoutBlockAC();
  QColor color;
  if (b!=NULL)
  {
   //g2.setColor(b->getBlockColor());
   color = b->getBlockColor();
  }
  else
  {
   //g2.setColor(defaultTrackColor);
   color = editor->defaultTrackColor;
  }
  // set track width for AC block
  editor->setTrackStrokeWidth(isMainlineAC());
  // draw AC segment
  //g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
  QGraphicsLineItem* line = new QGraphicsLineItem(getCoordsA().x(), getCoordsA().y(), getCoordsC().x(), getCoordsC().y(),0);
  line->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line);
  item->addToGroup(line);
}
/*private*/ void LevelXing::drawXingBD(LayoutEditor* editor)
{
  // set color - check for an BD block
  QColor color;
  LayoutBlock* b = getLayoutBlockBD();
  if (b!=NULL)
  {
   color = b->getBlockColor();
  }
  else
  {
   color= editor->defaultTrackColor;
  }
  Q_ASSERT(color.isValid());

  // set track width for BD block
  editor->setTrackStrokeWidth(isMainlineBD());
  // draw BD segment
  //g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
  QGraphicsLineItem* line = new QGraphicsLineItem(getCoordsB().x(), getCoordsB().y(), getCoordsD().x(), getCoordsD().y(),0);
  line->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line);
  item->addToGroup(line);
}
#endif
void LevelXing::drawXingRects(LayoutEditor* editor, QGraphicsScene* g2)
{
 QColor color;
 rects = new QGraphicsItemGroup();

 QPointF pt = getCoordsCenter();
//      g2.setColor(defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
 QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pt.x()-LayoutEditor::SIZE2, pt.y()-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, 0);
  ellipse->setPen(QPen(editor->defaultTrackColor, 1, Qt::SolidLine ) );
  //g2->addItem(ellipse);
  rects->addToGroup(ellipse);
  pt = getCoordsA();
 if (getConnectA()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem1 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem1->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem1);
 rects->addToGroup(rectItem1);
 pt = getCoordsB();
 if (getConnectB()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
         //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem2 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem2->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem2);
 rects->addToGroup(rectItem2);
 pt = getCoordsC();
 if (getConnectC()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem3 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem3->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem3);
 rects->addToGroup(rectItem3);
 pt = getCoordsD();
 if (getConnectD()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else
 {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem4 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem4->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem4);
 rects->addToGroup(rectItem4);

 g2->addItem(rects);
}

/**
 * return the coordinates for a specified connection type
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
//@Override
/*public*/ QPointF LevelXing::LevelXing::LevelXing::getCoordsForConnectionType(int connectionType) {
    QPointF result = center;
    switch (connectionType) {
        case LEVEL_XING_CENTER:
            break;
        case LEVEL_XING_A:
            result = getCoordsA();
            break;
        case LEVEL_XING_B:
            result = getCoordsB();
            break;
        case LEVEL_XING_C:
            result = getCoordsC();
            break;
        case LEVEL_XING_D:
            result = getCoordsD();
            break;
        default:
            log.error("Invalid connection type " + QString::number(connectionType)); //I18IN
    }
    return result;
}

/**
 * @return the bounds of this crossing
 */
//@Override
/*public*/ QRectF LevelXing::getBounds() {
 QRectF result;

 QPointF pointA = getCoordsA();
 result = QRectF(pointA.x(), pointA.y(), 0, 0);
 result = MathUtil::add(result,getCoordsB());
 result = MathUtil::add(result,getCoordsC());
 result = MathUtil::add(result,getCoordsD());
 return result;
}

/*
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity*>* LevelXing::getLayoutConnectivity() {
    // nothing to see here... move along...
    return nullptr;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QList<int> LevelXing::checkForFreeConnections() {
    QList<int> result = QList<int>();

    //check the A connection point
    if (getConnectA() == nullptr) {
        result.append((LEVEL_XING_A));
    }

    //check the B connection point
    if (getConnectB() == nullptr) {
        result.append((LEVEL_XING_B));
    }

    //check the C connection point
    if (getConnectC() == nullptr) {
        result.append((LEVEL_XING_C));
    }

    //check the D connection point
    if (getConnectD() == nullptr) {
        result.append((LEVEL_XING_D));
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool LevelXing::checkForUnAssignedBlocks() {
    return ((getLayoutBlockAC() != nullptr) && (getLayoutBlockBD() != nullptr));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LevelXing::checkForNonContiguousBlocks(
        /*@Nonnull*/ QMap<QString, QList<QSet<QString>* >* >* blockNamesToTrackNameSetsMap) {
    /*
     * For each (non-null) blocks of this track do:
     * #1) If it's got an entry in the blockNamesToTrackNameSetMap then
     * #2) If this track is already in the TrackNameSet for this block
     *     then return (done!)
     * #3) else add a new set (with this block/track) to
     *     blockNamesToTrackNameSetMap and check all the connections in this
     *     block (by calling the 2nd method below)
     * <p>
     *     Basically, we're maintaining contiguous track sets for each block found
     *     (in blockNamesToTrackNameSetMap)
     */

    // We're only using a map here because it's convient to
    // use it to pair up blocks and connections
    QMap<LayoutTrack*, QString> blocksAndTracksMap =QMap<LayoutTrack*, QString>();
    if ((getLayoutBlockAC() != nullptr) && (connectA != nullptr)) {
        blocksAndTracksMap.insert(connectA, getLayoutBlockAC()->getDisplayName());
    }
    if ((getLayoutBlockAC() != nullptr) && (connectC != nullptr)) {
        blocksAndTracksMap.insert(connectC, getLayoutBlockAC()->getDisplayName());
    }
    if ((getLayoutBlockBD() != nullptr) && (connectB != nullptr)) {
        blocksAndTracksMap.insert(connectB, getLayoutBlockBD()->getDisplayName());
    }
    if ((getLayoutBlockBD() != nullptr) && (connectD != nullptr)) {
        blocksAndTracksMap.insert(connectD, getLayoutBlockBD()->getDisplayName());
    }

    QList<QSet<QString>*>* TrackNameSets = nullptr;
    QSet<QString>* TrackNameSet = nullptr;
    //for (Map.Entry<LayoutTrack*, QString> entry : blocksAndTracksMap.entrySet())
    QMapIterator<LayoutTrack*, QString> entry(blocksAndTracksMap);
    while(entry.hasNext())
    {
     entry.next();
        LayoutTrack* theConnect = entry.key();
        QString theBlockName = entry.value();

        TrackNameSet = nullptr;    // assume not found (pessimist!)
        TrackNameSets = blockNamesToTrackNameSetsMap->value(theBlockName);
        if (TrackNameSets != nullptr) { // (#1)
            for (QSet<QString>* checkTrackNameSet : *TrackNameSets) {
                if (checkTrackNameSet->contains(getName())) { // (#2)
                    TrackNameSet = checkTrackNameSet;
                    break;
                }
            }
        } else {    // (#3)
            log.debug(tr("*New block ('%1') trackNameSets").arg(theBlockName));
            TrackNameSets = new QList<QSet<QString>*>();
            blockNamesToTrackNameSetsMap->insert(theBlockName, TrackNameSets);
        }
        if (TrackNameSet == nullptr) {
            TrackNameSet = new QSet<QString>();
            TrackNameSets->append(TrackNameSet);
        }
//        if (TrackNameSet->insert(getName())) {
//            log.debug(tr("*    Add track ''%1'' to trackNameSet for block ''%2''").arg(getName()).arg(theBlockName));
//        }
        TrackNameSet->insert(getName());
        theConnect->collectContiguousTracksNamesInBlockNamed(theBlockName, TrackNameSet);
    }
}   // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LevelXing::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
        /*@Nonnull*/ QSet<QString>* TrackNameSet) {
    if (!TrackNameSet->contains(getName())) {
        // check all the matching blocks in this track and...
        //  #1) add us to TrackNameSet and...
        //  #2) flood them
        //check the AC blockName
        if (getBlockNameAC()==(blockName)) {
            // if we are added to the TrackNameSet
            TrackNameSet->insert(getName());
            if (TrackNameSet->contains(getName())) {
                log.debug(tr("*    Add track ''%1'for block ''%2''").arg(getName()).arg(blockName));
            }
            // it's time to play... flood your neighbours!
            if (connectA != nullptr) {
                connectA->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
            }
            if (connectC != nullptr) {
                connectC->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
            }
        }
        //check the BD blockName
        if (getBlockNameBD() == (blockName)) {
            // if we are added to the TrackNameSet
         TrackNameSet->insert(getName());
            if (TrackNameSet->contains(getName())) {
                log.debug(tr("*    Add track ''%1''for block ''%2''").arg(getName()).arg(blockName));
            }
            // it's time to play... flood your neighbours!
            if (connectB != nullptr) {
                connectB->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
            }
            if (connectD != nullptr) {
                connectD->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
            }
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LevelXing::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    setLayoutBlockAC(layoutBlock);
    setLayoutBlockBD(layoutBlock);
}
