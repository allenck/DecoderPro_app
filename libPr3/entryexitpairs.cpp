#include "entryexitpairs.h"
#include "../LayoutEditor/layoutblockconnectivitytools.h"
#include "instancemanager.h"
#include "pointdetails.h"
#include "../LayoutEditor/layouteditor.h"
#include "../LayoutEditor/panelmenu.h"
#include "signalmastlogicmanager.h"
#include "destinationpoints.h"
#include "signalmast.h"
#include "sensor.h"
#include "signalhead.h"
#include "abstractsensor.h"
#include "../LayoutEditor/configxmlmanager.h"
#include "layoutblock.h"
#include <QList>
#include "source.h"
#include "stacknxpanel.h"
#include "defaultconditional.h"
#include "logix.h"
#include "conditionalvariable.h"
#include "conditionalaction.h"
#include "joptionpane.h"
#include "vetoablechangesupport.h"

//EntryExitPairs::EntryExitPairs(QObject *parent) :
//    Manager(parent)
//{
//}
/**
 * Implements an Entry Exit based method of setting turnouts, setting up signal logic and the
 * allocation of blocks through based upon the layout editor.
 * <p>
 * The route is based upon having a sensor assigned at a known location on the panel
 * (set at the boundary of two different blocks) through to a sensor at a remote location
 * on the same panel.  Using the layout block routing, a path can then be set between the
 * two sensors so long as one existings and that no section of tra ck is set occupied.
 * If possible an alternative route will be used.
 * <p>
 * Initial implementation only handles the setting up of turnouts on a path.

 * @author Kevin Dickerson  Copyright (C) 2011
 * @version			$Revision: 19923 $
 */
///*public*/ class EntryExitPairs implements jmri.Manager{

//	ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");
    //static volatile EntryExitPairs _instance = NULL;


/*final*/ /*static*/ int EntryExitPairs::HOPCOUNT = LayoutBlockConnectivityTools::HOPCOUNT;
/*final*/ /*static*/ int EntryExitPairs::METRIC = LayoutBlockConnectivityTools::METRIC;

///*public*/ /*final*/ /*static*/ int EntryExitPairs::NXBUTTONSELECTED = 0x08;
///*public*/ /*final*/ /*static*/ int EntryExitPairs::NXBUTTONACTIVE = Sensor::ACTIVE;
///*public*/ /*final*/ /*static*/ int EntryExitPairs::NXBUTTONINACTIVE = Sensor::INACTIVE;

/*public*/ int EntryExitPairs::getSettingTimer() {
    return settingTimer;
}

/*public*/ void EntryExitPairs::setSettingTimer(int i) {
    settingTimer = i;
}

/*public*/ bool EntryExitPairs::useDifferentColorWhenSetting() {
return (settingRouteColor == QColor() ? false : true);
}

/*public*/ QColor EntryExitPairs::getSettingRouteColor() {
    return settingRouteColor;
}

/*public*/ void EntryExitPairs::setSettingRouteColor(QColor col) {
    settingRouteColor = col;
}

/**
* Constant value to represent that the entryExit will only set up the
* turnouts between two different points
*/
/*public*/ /*final*/ /*static*/ int EntryExitPairs::SETUPTURNOUTSONLY = 0x00;

/**
* Constant value to represent that the entryExit will set up the
* turnouts between two different points and configure the signalmast logic
* to use the correct blocks.
*/
/*public*/ /*final*/ /*static*/ int EntryExitPairs::SETUPSIGNALMASTLOGIC = 0x01;

/**
* Constant value to represent that the entryExit will do full interlocking
* it will set the turnouts and "reserve" the blocks.
*/
/*public*/ /*final*/ /*static*/ int EntryExitPairs::FULLINTERLOCK = 0x02;

///*public*/ /*final*/ /*static*/ int EntryExitPairs::PROMPTUSER = 0x00;
///*public*/ /*final*/ /*static*/ int EntryExitPairs::AUTOCLEAR = 0x01;
///*public*/ /*final*/ /*static*/ int EntryExitPairs::AUTOCANCEL = 0x02;

/*static*/ QWidget* EntryExitPairs::glassPane = NULL; //new QWidget();

/*public*/ EntryExitPairs::EntryExitPairs(QObject */*parent*/)
{
 setObjectName("EntryExitPairs");
 setProperty("JavaClassName", "jmri.jmrit.entryexit.EntryExitPairs");
 routingMethod = LayoutBlockConnectivityTools::METRIC;
 routeClearOption = PROMPTUSER;
 turnoutSetDelay = 0;
 log = new Logger("EntryExitPairs");
 destinationList = QObjectList();
 smlm = (SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager");
 runWhenStablised = false;
 settingTimer = 2000;
 settingRouteColor = QColor();
 allocateToDispatcher = false;
 setProperty("InstanceManagerAutoDefault", "yes");
 routesToSet = QList<SourceToDest*>();
 destinationList = QObjectList();
 stackList = QList<StackDetails*>();
 checkTimer = new QTimer();
 checkTimer->setInterval(10000);
 connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkRoute()));
 deletePairList = QList<DeletePair*>();
 nxpair = QHash<PointDetails*, Source*>();
 vcs = new VetoableChangeSupport(this);
 listeners = QVector</*ManagerDataListener*/QObject*>();
 pcs = new PropertyChangeSupport(this);

 memo = (SystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo");
 if(InstanceManager::getDefault("ConfigureManager")!=NULL)
   static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerUser(this);
 ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->addPropertyChangeListener(/*propertyBlockManagerListener*/(PropertyChangeListener*)this);
 //connect(lbm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));

//    glassPane.setOpaque(false);
//    glassPane.setLayout(NULL);
//    glassPane.addMouseListener(new MouseAdapter() {
//      /*public*/ void mousePressed(MouseEvent e) {
//        e.consume();
//      }
//    });
}

/*public*/ void EntryExitPairs::setDispatcherIntegration(bool boo) {
    allocateToDispatcher = boo;
}

/*public*/ bool EntryExitPairs::getDispatcherIntegration() {
    return allocateToDispatcher;
}

/*public*/ QWidget* EntryExitPairs::getGlassPane(){
    return glassPane;
}


/*public*/ void EntryExitPairs::addNXSourcePoint(LayoutBlock* facing, QList<LayoutBlock*> protecting, NamedBean* loc, LayoutEditor* panel){
    PointDetails* point = providePoint(facing, protecting, panel);
    point->setRefObject(loc);
}

/*public*/ void EntryExitPairs::addNXSourcePoint(NamedBean* source){
    PointDetails* point = NULL;
    QList<LayoutEditor*>* layout = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
    for(int i = 0; i<layout->size(); i++){
        point = providePoint(source, layout->at(i));
    }
    if(point==NULL){
        log->error("Unable to find a location on any panel for item " + source->getDisplayName());
        return;
    }
}

/*public*/ void EntryExitPairs::addNXSourcePoint(NamedBean* source, LayoutEditor* panel){
    if(source==NULL){
        log->error("source bean supplied is NULL");
        return;
    }
    if(panel==NULL){
        log->error("panel supplied is NULL");
        return;
    }
    PointDetails* point;
    point = providePoint(source, panel);
    if(point==NULL){
        log->error("Unable to find a location on the panel " + panel->getLayoutName() + " for item " + source->getDisplayName());
        return;
    }
}

/*public*/ QObject* EntryExitPairs::getEndPointLocation(NamedBean* source, LayoutEditor* panel){
    if(source==NULL){
        log->error("Source bean past is NULL");
        return NULL;
    }
    if(panel==NULL){
        log->error("panel past is NULL");
        return NULL;
    }
    PointDetails* sourcePoint = getPointDetails(source, panel);
    if(sourcePoint==NULL){
        log->error("Point is not located");
        return NULL;
    }
    return sourcePoint->getRefLocation();
}

/*public*/ int EntryExitPairs::getXMLOrder()const{
    return ENTRYEXIT;
}

/*public*/ DestinationPoints* EntryExitPairs::getBySystemName(QString systemName) const
{
 foreach(Source* e,   nxpair.values())
 {
     DestinationPoints* pd = e->getByUniqueId(systemName);
     if(pd!=NULL)
         return pd;
 }
 return NULL;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*DestinationPoints*/DestinationPoints *EntryExitPairs::getByUserName(/*@Nonnull*/ QString userName) const {
 if(userName=="")
  throw NullPointerException(tr("userName is marked NonNull but is null"));

  for (Source* e : nxpair.values()) {
      DestinationPoints* pd = (DestinationPoints*)e->getByUserName(userName);
      if (pd != nullptr) {
          return pd;
      }
  }
  return nullptr;
}
#if 0
/*public*/ NamedBean* EntryExitPairs::getBeanBySystemName(QString systemName) const{
    return getBySystemName(systemName);
}

/*public*/ NamedBean* EntryExitPairs::getBeanByUserName(QString userName) const{
    foreach(Source* e,  nxpair.values()){
        DestinationPoints* pd = e->getByUserName(userName);
        if(pd!=NULL)
            return pd;
    }
    return NULL;
}
#endif
/*public*/ NamedBean* EntryExitPairs::getNamedBean(QString name) const{
    NamedBean* b = getByUserName(name);
    if(b!=NULL) return b;
    return getBySystemName(name);
}
#if 0
//@Deprecated
/*public*/ char EntryExitPairs::systemLetter()const {
    throw  UnsupportedOperationException("Not supported yet.");
}
#endif
/** {@inheritDoc} */
//@Nonnull
//@Override
/*public*/ SystemConnectionMemo* EntryExitPairs::getMemo() const {
    return memo;
}
/*public*/ QString EntryExitPairs::getSystemPrefix() const{
 return memo->getSystemPrefix();
}

/*public*/ char EntryExitPairs::typeLetter() const {
    throw  UnsupportedOperationException("Not supported yet.");
}

//@Override
//@Nonnull
/*public*/ QString EntryExitPairs::makeSystemName(QString /*s*/)const {
    throw UnsupportedOperationException("Not supported yet.");
}

/** {@inheritDoc} */
//@Override
//@CheckReturnValue
/*public*/ int EntryExitPairs::getObjectCount() {
    return getNamedBeanList()->size(); // not efficient
}

///*public*/ QStringList EntryExitPairs::getSystemNameArray() {
//    throw new UnsupportedOperationException("Not supported yet.");
//}

/*public*/ QStringList EntryExitPairs::getSystemNameList() {
    return getEntryExitList();
}
#if 0
/**
 * Implemented to support the Conditional combo box name list
 * @since 4.9.3
 * @return a list of Destination Point beans
 */
@Override
@Nonnull
@Deprecated  // will be removed when superclass method is removed due to @Override
public List<DestinationPoints> getNamedBeanList() {
    List<DestinationPoints> beanList = new ArrayList<>();
    for (Source e : nxpair.values()) {
        List<String> uidList = e.getDestinationUniqueId();
        for (String uid : uidList) {
            beanList.add(e.getByUniqueId(uid));
        }
    }
    return beanList;
}
#endif

/**
 * Implemented to support the Conditional combo box name list
 * @since 4.9.3
 * @return a list of Destination Point beans
 */
//@Override
//@Nonnull
/*public*/ QSet<NamedBean*> EntryExitPairs::getNamedBeanSet() {
    QSet<NamedBean*> beanList = QSet<NamedBean*>();//new TreeSet<>(new jmri.util.NamedBeanComparator());
    for (Source* e :  nxpair.values()) {
        QStringList uidList = e->getDestinationUniqueId();
        for (QString uid : uidList) {
            beanList.insert(e->getByUniqueId(uid)); //DestinationPoints
        }
    }
    return beanList;
}

/*public*/ void EntryExitPairs::Register(/*@Nonnull*/ NamedBean* /*n*/)const {
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ void EntryExitPairs::deregister(/*@Nonnull*/NamedBean* /*n*/)const {
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ void EntryExitPairs::setClearDownOption(int i){
    routeClearOption = i;
}

/*public*/ int EntryExitPairs::getClearDownOption(){
    return routeClearOption;
}

/** {@inheritDoc} */
//@Override
/*public*/ void EntryExitPairs::dispose(){ }

/**
 * Generate the point details, given a known source and a
 * Layout Editor panel.
 *
 * @param source Origin of movement
 * @param panel  A Layout Editor panel
 * @return A PointDetails object
 */
/*private*/ PointDetails* EntryExitPairs::providePoint(NamedBean* source, LayoutEditor* panel){
    PointDetails* sourcePoint = getPointDetails(source, panel);
    if(sourcePoint==NULL)
    {
     LayoutBlock* facing = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getFacingBlockByNamedBean(source, nullptr);
     QList<LayoutBlock*> protecting = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getProtectingBlocksByNamedBean(source, nullptr);
//             log.info("facing = {}, protecting = {}", facing, protecting);
     if (facing == nullptr && protecting.size() == 0) {
         log->error("Unable to find facing and protecting blocks");  // NOI18N
         return nullptr;
     }
     sourcePoint = providePoint(facing, protecting, panel);
     sourcePoint->setRefObject(source);
    }
    return sourcePoint;
}

/**
 * Return a list of all source (origin) points on a given
 * Layout Editor panel.
 *
 * @param panel  A Layout Editor panel
 * @return A list of source objects
 */
/*public*/ QObjectList* EntryExitPairs::getSourceList(LayoutEditor* panel){
    QObjectList* list = new QObjectList();

    //for(Entry<PointDetails*, Source*> e :  nxpair.entrySet()){
    QHashIterator<PointDetails*, Source*> e(nxpair);
    while(e.hasNext())
    {
     e.next();
        //QObject* obj = (e.getKey()).getRefObject();
     QObject* obj = e.key()->getRefObject();
     LayoutEditor* pan = e.key()->getPanel();
     if(pan==panel)
     {
      if (!list->contains(obj))
       list->append(obj);
     } // end while
    }
    return list;
}

/*public*/ Source* EntryExitPairs::getSourceForPoint(PointDetails* pd) {
    return  nxpair.value(pd);
}

/*public*/ int EntryExitPairs::getNxPairNumbers(LayoutEditor* panel){
    int total=0;
    //for(Entry<PointDetails, Source> e :  nxpair.entrySet()){
    QHashIterator<PointDetails*, Source*> e(nxpair);
    while(e.hasNext())
    {
     e.next();
        PointDetails* key = e.key();
        LayoutEditor* pan = key->getPanel();
        if(pan==panel){
            total = total+e.value()->getNumberOfDestinations();
        } // end while
    }

    return total;
}

/**
 * Set the route between the two points represented by the Destination Point name.
 *
 * @since 4.11.1
 * @param nxPair The system or user name of the destination point.
 */
/*public*/ void EntryExitPairs::setSingleSegmentRoute(QString nxPair) {
    DestinationPoints* dp = ( DestinationPoints*)getNamedBean(nxPair);
    if (dp != nullptr) {
        QString destUUID = dp->getUniqueId();
        // nxpair.forEach((pd, src) ->
        QHashIterator<PointDetails*, Source*> iter(nxpair);
        while(iter.hasNext())
        {
         iter.next();
         PointDetails* pd = iter.key();
         Source* src = iter.value();
            for (QString srcUUID : src->getDestinationUniqueId()) {
                if (destUUID == (srcUUID)) {
                    log->debug(tr("Found the correct source: src = %1, dest = %2").arg(
                             pd->getSensor()->getDisplayName()).arg(dp->getDestPoint()->getSensor()->getDisplayName()));
                    setMultiPointRoute(pd, dp->getDestPoint());
                    return;
                }
            }
        }//);
    }
}

/*public*/ void EntryExitPairs::setMultiPointRoute(PointDetails* requestpd, LayoutEditor* /*panel*/) {
    for (PointDetails* pd : *pointDetails) {
        if (pd != requestpd) {
            if (pd->getNXState() == NXBUTTONSELECTED) {
                setMultiPointRoute(pd, requestpd);
                return;
            }
        }
    }
}

/*private*/ void EntryExitPairs::setMultiPointRoute(PointDetails* fromPd, PointDetails* toPd)
{
 bool cleardown = false;
 if (fromPd->isRouteFromPointSet() && toPd->isRouteToPointSet()) {
     cleardown = true;
 }
 for (LayoutBlock* pro : fromPd->getProtecting())
 {
  try
  {
   LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>( InstanceManager::getDefault("LayoutBlockManager"));
   LayoutBlock* toProt = nullptr;
   if (!toPd->getProtecting().isEmpty()) {
       toProt = toPd->getProtecting().at(0);
   }
   bool result = lbm->getLayoutBlockConnectivityTools()->checkValidDest(fromPd->getFacing(), pro, toPd->getFacing(), toProt, LayoutBlockConnectivityTools::SENSORTOSENSOR);
   if (result)
   {
    QList<LayoutBlock*> blkList = lbm->getLayoutBlockConnectivityTools()->getLayoutBlocks(fromPd->getFacing(), toPd->getFacing(), pro, cleardown, LayoutBlockConnectivityTools::NONE);
    if (!blkList.isEmpty())
    {
     if (log->isDebugEnabled())
     {
      for (LayoutBlock* blk : blkList)
      {
          log->debug(tr("blk = %1").arg(blk->getDisplayName()));
      }
    }
    QList<NamedBean*> beanList = lbm->getLayoutBlockConnectivityTools()->getBeansInPath(blkList, nullptr, "Sensor");
     PointDetails* fromPoint = fromPd;
     refCounter++;
     if (!beanList.isEmpty()) {
         if (log->isDebugEnabled()) {
             for (NamedBean* xnb : beanList) {
                 log->debug(tr("xnb = %1").arg(xnb->getDisplayName()));
             }
         }
         for (int i = 1; i < beanList.size(); i++) {
             NamedBean* nb = beanList.at(i);
             PointDetails* cur = getPointDetails(nb, fromPd->getPanel());
             Source* s =  nxpair.value(fromPoint);
             if (s != nullptr) {
                 routesToSet.append(new SourceToDest(s, s->getDestForPoint(cur), false, refCounter));
             }
             fromPoint = cur;
         }
     }
     Source* s =  nxpair.value(fromPoint);
     if (s != nullptr) {
         if (s->getDestForPoint(toPd) != nullptr) {
             routesToSet.append(new SourceToDest(s, s->getDestForPoint(toPd), false, refCounter));
         }
     }
     processRoutesToSet();
     return;
    }
   }
  }
  catch (JmriException e) {
      //Can be considered normal if route is blocked
  }
 }
 fromPd->setNXButtonState(NXBUTTONINACTIVE);
 toPd->setNXButtonState(NXBUTTONINACTIVE);
}

/**
 * Activate each SourceToDest set in routesToSet
 */
/*synchronized*/ void EntryExitPairs::processRoutesToSet() {
    if (log->isDebugEnabled()) {
        for (SourceToDest* sd : routesToSet) {
            QString dpName = (sd->dp == nullptr) ? "- null -" : sd->dp->getDestPoint()->getSensor()->getDisplayName();
            log->debug(tr("processRoutesToSet: %1 -- %2 -- %3").arg(sd->s->getPoint()->getSensor()->getDisplayName()).arg( dpName).arg(sd->ref));
        }
    }

    if (routesToSet.isEmpty()) {
        return;
    }
    Source* s = routesToSet.at(0)->s;
    DestinationPoints* dp = routesToSet.at(0)->dp;
    bool dir = routesToSet.at(0)->direction;
    currentDealing = routesToSet.at(0)->ref;
    routesToSet.removeAt(0);

    //dp->addPropertyChangeListener(propertyDestinationListener);
    connect(dp->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyDestinationPropertyChange(PropertyChangeEvent*)));
    s->activeBean(dp, dir);
}

/**
 * Remove remaining SourceToDest sets in routesToSet
 */
/*synchronized*/ void EntryExitPairs::removeRemainingRoute() {
    QList<SourceToDest*> toRemove = QList<SourceToDest*>();
    for (SourceToDest* rts : routesToSet) {
        if (rts->ref == currentDealing) {
            toRemove.append(rts);
            rts->dp->getDestPoint()->setNXButtonState(NXBUTTONINACTIVE);
        }
    }
    for (SourceToDest* rts : toRemove) {
        routesToSet.removeOne(rts);
    }
}

//protected PropertyChangeListener propertyDestinationListener = new PropertyChangeListener() {
//    @Override
/*public*/ void EntryExitPairs::propertyDestinationPropertyChange(PropertyChangeEvent* e) {
    //((DestinationPoints*) e->getSource()).removePropertyChangeListener(this);
 disconnect(((DestinationPoints*) e->getSource())->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyDestinationPropertyChange(PropertyChangeEvent*)));
    if (e->getPropertyName()==("active")) {
        processRoutesToSet();
    } else if (e->getPropertyName() == ("stacked") || e->getPropertyName() == ("failed") || e->getPropertyName() == ("noChange")) {  // NOI18N
        removeRemainingRoute();
    }
}
//};

//Need to sort out the presentation of the name here rather than using the point id
//This is used for the creation and display of information in the table
//The presentation of the name might have to be done at the table level.
/*public*/ QObjectList EntryExitPairs::getNxSource(LayoutEditor* panel)
{
 QObjectList source = QObjectList();
 destinationList = QObjectList();

 //for(Entry<PointDetails, Source> e :  nxpair.entrySet()){
 QHashIterator<PointDetails*, Source*> e(nxpair);
 while( e.hasNext())
 {
  e.next();
  PointDetails* key = e.key();
  LayoutEditor* pan = key->getPanel();
  if(pan == panel)
  {
   QList<PointDetails*> dest =  nxpair.value(key)->getDestinationPoints();
   for(int i = 0; i<dest.size(); i++)
   {
    destinationList.append(dest.value(i)->getRefObject());
    source.append(key->getRefObject());
   }
  }
 }
 return source;
}

/*public*/ QObjectList EntryExitPairs::getNxDestination(){
    return destinationList;
}

/*public*/ QList<LayoutEditor*> EntryExitPairs::getSourcePanelList(){
    QList<LayoutEditor*> list =  QList<LayoutEditor*>();

    //for(Entry<PointDetails, Source> e :  nxpair.entrySet()){
    QHashIterator<PointDetails*, Source*> e(nxpair);
    while( e.hasNext())
    {
        e.next();
        PointDetails* key = e.key();
        LayoutEditor* pan = key->getPanel();
       if (!list.contains(pan))
            list.append(pan);
    }
    return list;
}

/**
* Returns a point if already exists, or creates a new one if not.
*/
/*private*/ PointDetails* EntryExitPairs::providePoint(LayoutBlock* source, QList<LayoutBlock*> protecting, LayoutEditor* panel){
    PointDetails* sourcePoint = getPointDetails(source, protecting, panel);
    if(sourcePoint==NULL){
        sourcePoint = new PointDetails(source, protecting);
        sourcePoint->setPanel(panel);
    }
    return sourcePoint;
}

/*public*/ void EntryExitPairs::addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel)
{
 addNXDestination(source, destination, panel, QString());
}

/*public*/ void EntryExitPairs::addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel, QString id)
{
 if (source==NULL)
 {
  log->error("no source Object provided");
  throw NullPointerException("no source Object provided");
  //return;
 }
 if(destination==NULL)
 {
  log->error("no destination Object provided");
  throw NullPointerException("no destination Object provided");
  //return;
 }
 PointDetails* sourcePoint = providePoint(source, panel);
 if(sourcePoint==NULL)
 {
  log->error("source point for " + source->getDisplayName() + " not created addNXDes");
  throw NullPointerException("source point for " + source->getDisplayName() + " not created addNXDes");
  //return;
 }

 sourcePoint->setPanel(panel);
 sourcePoint->setRefObject(source);
 PointDetails* destPoint = providePoint(destination, panel);
 if (destPoint != nullptr)
 {
    destPoint->setPanel(panel);
    destPoint->setRefObject(destination);
    destPoint->getSignal();
    if (!nxpair.contains(sourcePoint)) {
        Source* sp = new Source(sourcePoint) ;
        nxpair.insert(sourcePoint, sp);
        sp->removePropertyChangeListener((PropertyChangeListener*)this);
        sp->addPropertyChangeListener((PropertyChangeListener*)this);
    }
    nxpair.value(sourcePoint)->addDestination(destPoint, id);
}

 firePropertyChange("length", QVariant(), QVariant());
}

/*public*/ QObjectList* EntryExitPairs::getDestinationList(QObject* obj, LayoutEditor* panel){
    QObjectList* list = new QObjectList();
    if( nxpair.contains(getPointDetails(obj, panel)))
    {
     QList<PointDetails*> from =  nxpair.value(getPointDetails(obj, panel))->getDestinationPoints();
     for(int i = 0; i<from.size(); i++){
         list->append(from.at(i)->getRefObject());
     }
    }

    return list;
}

/*public*/ void EntryExitPairs::removeNXSensor(Sensor* sensor) {
    log->info(tr("panel maintenance has resulting in the request to remove a sensor: %1").arg(sensor->getDisplayName()));
}

/**
 * Entry point to delete all of the NX pairs for a specific sensor.
 * 1) Build a list of affected NX pairs.
 * 2) Check for Conditional references.
 * 3) If no references, do the delete process with user approval.
 * <p>
 * @since 4.11.2
 * @param sensor The sensor whose pairs should be deleted.
 * @return true if the delete was successful. False if prevented by
 * Conditional references or user choice.
 */
/*public*/ bool EntryExitPairs::deleteNxPair(NamedBean* sensor) {
    if (sensor == nullptr) {
        log->error("deleteNxPair: sensor is null");  // NOI18N
        return false;
    }
    createDeletePairList(sensor);
    if (checkNxPairs()) {
        // No Conditional references.
        if (confirmDeletePairs()) {
            deleteNxPairs();
            return true;
        }
    }
    return false;
}

/*public*/ bool EntryExitPairs::deleteNxPair(NamedBean* entrySensor, NamedBean* exitSensor, LayoutEditor* panel){
 if (entrySensor == nullptr || exitSensor == nullptr || panel == nullptr) {
     log->error("deleteNxPair: One or more null inputs");  // NOI18N
     return false;
 }
 deletePairList.clear();
 deletePairList.append(new DeletePair(entrySensor, exitSensor, panel, this));
 if (checkNxPairs()) {
     // No Conditional references.
     deleteNxPairs();  // Delete with no prompt
     return true;
 }
 return false;
}

/**
 * Find Logix Conditionals that have Variables or Actions for the affected NX Pairs
 * If any are found, display a dialog box listing the Conditionals and return false.
 * <p>
 * @since 4.11.2
 * @return true if there are no references.
 */
/*private*/ bool EntryExitPairs::checkNxPairs()
{
 LogixManager* mgr = static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"));
 QList<QString> conditionalReferences = QList<QString> ();
 for (DeletePair* dPair : deletePairList)
 {
  if (dPair->dp == nullptr) {
      continue;
  }
  for (NamedBean* nb : mgr->getNamedBeanSet())
  {
   Logix* lgx = (Logix*)nb;
   for (int i = 0; i < lgx->getNumConditionals(); i++)
   {
    QString cdlName = lgx->getConditionalByNumberOrder(i);
    DefaultConditional* cdl = (DefaultConditional*) lgx->getConditional(cdlName);
    QString cdlUserName = (cdl->getUserName() == nullptr) ? "" : cdl->getUserName();
    if (cdlUserName.isNull())
    {
     cdlUserName = "";
    }
    for (ConditionalVariable* var : *cdl->getStateVariableList())
    {
     if (var->getBean() == dPair->dp)
     {
      QString refName = (cdlUserName == ("")) ? cdlName : cdlName + "  ( " + cdlUserName + " )";
      if (!conditionalReferences.contains(refName)) {
          conditionalReferences.append(refName);
      }
     }
    }
    for (ConditionalAction* act : cdl->getActionList())
    {
     if (act->getBean() == dPair->dp) {
         QString refName = (cdlUserName == ("")) ? cdlName : cdlName + "  ( " + cdlUserName + " )";
         if (!conditionalReferences.contains(refName)) {
             conditionalReferences.append(refName);
         }
     }
    }
   }
  }
 }
 if (conditionalReferences.isEmpty()) {
     return true;
 }

 //conditionalReferences.sort(nullptr);
 qSort(conditionalReferences);
 QString msg = tr("The following Logix Conditionals have NX Pair references.\nThis will prevent the NX Pair deletions.");
 for (QString ref : conditionalReferences) {
     msg.append("\n    " + ref);  // NOI18N
 }
 JOptionPane::showMessageDialog(nullptr,
         msg,
         tr("Warning"),  // NOI18N
         JOptionPane::WARNING_MESSAGE);

 return false;
}

/**
 * Display a list of pending deletes and ask for confirmation.
 * @since 4.11.2
 * @return true if deletion confirmation is Yes.
 */
/*private*/ bool EntryExitPairs::confirmDeletePairs()
{
    if (deletePairList.size() > 0)
    {
        QString msg = tr("The following Entry/Exit pairs will be deleted\ndue to Layout Editor panel changes.");  // NOI18N
        for (DeletePair* dPair : deletePairList)
        {
            if (dPair->dp != nullptr) {
                msg.append("\n    " + dPair->dp->getDisplayName());  // NOI18N
            }
        }
        msg.append("\n" + tr("Continue?"));  // NOI18N
        int resp = JOptionPane::showConfirmDialog(nullptr,
                msg,
                tr("Warning"),  // NOI18N
                JOptionPane::YES_NO_OPTION,
                JOptionPane::QUESTION_MESSAGE);
        if (resp != 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * Delete the pairs in the delete pair list.
 * @since 4.11.2
 */
/*private*/ void EntryExitPairs::deleteNxPairs() {
    for (DeletePair* dp : deletePairList) {
        PointDetails* sourcePoint = getPointDetails(dp->src, dp->pnl);
        PointDetails* destPoint = getPointDetails(dp->dest, dp->pnl);
         nxpair.value(sourcePoint)->removeDestination(destPoint);
        firePropertyChange("length", 0, 0);  // NOI18N
        if ( nxpair.value(sourcePoint)->getDestinationPoints().isEmpty())
        {
         nxpair.value(sourcePoint)->removePropertyChangeListener((PropertyChangeListener*)this);
         nxpair.remove(sourcePoint);
        }
    }
}




/**
 * Rebuild the delete pair list based on the supplied sensor.
 * Find all of the NX pairs that use this sensor as either a source or
 * destination.  They will be candidates for deletion.
 * <p>
 * @since 4.11.2
 * @param sensor The sensor being deleted,
 */
void EntryExitPairs::createDeletePairList(NamedBean* sensor) {
    deletePairList.clear();
    //nxpair.forEach((pdSrc, src) ->
    QHashIterator<PointDetails*, Source*> iter(nxpair);
    while(iter.hasNext())
    {
     iter.next();
     PointDetails* pdSrc = iter.key();
     Source* src = iter.value();
        Sensor* sBean = pdSrc->getSensor();
        LayoutEditor* sPanel = pdSrc->getPanel();
        for (PointDetails* pdDest : src->getDestinationPoints()) {
            Sensor* dBean = pdDest->getSensor();
            if (sensor == sBean || sensor == dBean) {
                log->debug(tr("Delete pair: %1 to %2, panel = %3").arg(  // NOI18N
                        sBean->getDisplayName()).arg(dBean->getDisplayName()).arg(sPanel->getLayoutName()));
                deletePairList.append(new DeletePair(sBean, dBean, sPanel, this));
            }
        }
    }//);
}

// ============ End NX Pair Delete Methods ============
/**
 * Create a list of sensors that have the layout block as either
 * facing or protecting.
 * Called by {@link jmri.jmrit.display.layoutEditor.LayoutTrackEditors#hasNxSensorPairs}.
 * @since 4.11.2
 * @param layoutBlock The layout block to be checked.
 * @return the a list of sensors affected by the layout block or an empty list.
 */
/*public*/ QList<QString> EntryExitPairs::layoutBlockSensors(/*@Nonnull*/ LayoutBlock* layoutBlock)
{
 if(layoutBlock==nullptr)
  throw NullPointerException(tr("layoutBlock is marked NonNull but is null"));

 log->debug(tr("layoutBlockSensors: %1").arg(layoutBlock->getDisplayName()));
 QList<QString> blockSensors = QList<QString>();
 //nxpair.forEach((pdSrc, src) ->
 QHashIterator<PointDetails*, Source*> iter(nxpair);
 while(iter.hasNext())
 {
  iter.next();
  PointDetails* pdSrc = iter.key();
  Source* src = iter.value();
  Sensor* sBean = pdSrc->getSensor();
  for (LayoutBlock* sProtect : pdSrc->getProtecting())
  {
   if (layoutBlock == pdSrc->getFacing() || layoutBlock == sProtect)
   {
    log->debug(tr("  Source = '%1', Facing = '%2', Protecting = '%3'         ").arg(
            sBean->getDisplayName()).arg(pdSrc->getFacing()->getDisplayName()).arg(sProtect->getDisplayName()));
    blockSensors.append(sBean->getDisplayName());
   }
  }

  for (PointDetails* pdDest : src->getDestinationPoints())
  {
   Sensor* dBean = pdDest->getSensor();
   for (LayoutBlock* dProtect : pdDest->getProtecting())
   {
    if (layoutBlock == pdDest->getFacing() || layoutBlock == dProtect) {
        log->debug(tr("    Destination = '%1', Facing = '%2', Protecting = '%2'     ").arg(
                dBean->getDisplayName()).arg(pdDest->getFacing()->getDisplayName()).arg(dProtect->getDisplayName()));
        blockSensors.append(dBean->getDisplayName());
    }
   }
  }
 }//);
 return blockSensors;
}

/*public*/ bool EntryExitPairs::isDestinationValid(QObject* source, QObject* dest, LayoutEditor* panel){
 if( nxpair.contains(getPointDetails(source, panel)))
  return  nxpair.value(getPointDetails(source, panel))->isDestinationValid(getPointDetails(dest, panel));
 return false;
}

/*public*/ bool EntryExitPairs::isUniDirection(QObject* source, LayoutEditor* panel, QObject* dest){
 if( nxpair.contains(getPointDetails(source, panel)))
  return  nxpair.value(getPointDetails(source, panel))->getUniDirection(dest, panel);
 return false;
}

/*public*/ void EntryExitPairs::setUniDirection(QObject* source, LayoutEditor* panel, QObject* dest, bool set){
 if( nxpair.contains(getPointDetails(source, panel)))
  nxpair.value(getPointDetails(source, panel))->setUniDirection(dest, panel, set);
}

/*public*/ bool EntryExitPairs::canBeBiDirectional(QObject* source, LayoutEditor* panel, QObject* dest){
 if( nxpair.contains(getPointDetails(source, panel)))
   return  nxpair.value(getPointDetails(source, panel))->canBeBiDirection(dest, panel);
 return false;
}

/*public*/ bool EntryExitPairs::isEnabled(QObject* source, LayoutEditor* panel, QObject* dest)
{
 if( nxpair.contains(getPointDetails(source, panel)))
  return  nxpair.value(getPointDetails(source, panel))->isEnabled(dest, panel);
 return false;
}

/*public*/ void EntryExitPairs::setEnabled(QObject* source, LayoutEditor* panel, QObject* dest, bool set){
 if( nxpair.contains(getPointDetails(source, panel)))
  nxpair.value(getPointDetails(source, panel))->setEnabled(dest, panel, set);
}

/*public*/ void EntryExitPairs::setEntryExitType(QObject* source, LayoutEditor* panel, QObject* dest, int set){
 if( nxpair.contains(getPointDetails(source, panel)))
 {
  nxpair.value(getPointDetails(source, panel))->setEntryExitType(dest, panel, set);
  return;
 }
}

/*public*/ int EntryExitPairs::getEntryExitType(QObject* source, LayoutEditor* panel, QObject* dest){
 if( nxpair.contains(getPointDetails(source, panel)))
  return  nxpair.value(getPointDetails(source, panel))->getEntryExitType(dest, panel);
 return 0x00;
}

/*public*/ QString EntryExitPairs::getUniqueId(QObject* source, LayoutEditor* panel, QObject* dest){
 if( nxpair.contains(getPointDetails(source, panel)))
  return  nxpair.value(getPointDetails(source, panel))->getUniqueId(dest, panel);
 return QString();
}

/*public*/ QStringList EntryExitPairs::getEntryExitList(){
    QStringList destlist =  QStringList();
    foreach(Source* e,  nxpair.values()){
        destlist.append(e->getDestinationUniqueId());
    }
    return destlist;
}

//protecting helps us to determine which direction we are going in.
//validateOnly flag is used, if all we are doing is simply checking to see if the source/destpoints are valid, when creating the pairs in the user GUI

/*public*/ bool EntryExitPairs::isPathActive(QObject* sourceObj, QObject* destObj, LayoutEditor* panel)
{
    PointDetails* pd = getPointDetails(sourceObj, panel);
 if( nxpair.contains(pd))
 {
  Source* source =  nxpair.value(pd);
  return source->isRouteActive(getPointDetails(destObj, panel));
 }
 return false;
}

/*public*/ void EntryExitPairs::cancelInterlock(QObject* source, LayoutEditor* panel, QObject* dest){
if( nxpair.contains(getPointDetails(source, panel)))
{
 nxpair.value(getPointDetails(source, panel))->cancelInterlock(dest, panel);
 return;
}
}


/*public*/ /*final*/ /*static*/ int EntryExitPairs::CANCELROUTE = 0;
/*public*/ /*final*/ /*static*/ int EntryExitPairs::CLEARROUTE = 1;
/*public*/ /*final*/ /*static*/ int EntryExitPairs::EXITROUTE = 2;
/*public*/ /*final*/ /*static*/ int EntryExitPairs::STACKROUTE = 4;


#if 0
/*/*public*/ /*static*/ void EntryExitPairs::flashSensor(PointDetails* pd){
    foreach(SensorIcon* si, *pd->getPanel()->sensorList){
        if(si->getSensor()==pd->getSensor()){
            si->flashSensor(2, Sensor::ACTIVE, Sensor::INACTIVE);
        }
    }
}

/*public*/ /*static*/ void EntryExitPairs::stopFlashSensor(PointDetails* pd){
    foreach(SensorIcon* si, *pd->getPanel()->sensorList){
        if(si->getSensor()==pd->getSensor()){
            si->stopFlash();
        }
    }
}
#endif
/*synchronized*/ /*public*/ void EntryExitPairs::setNXButtonState(PointDetails* nxPoint, int state)
{
    QMutexLocker locker(&mutex);
    if(nxPoint->getSensor()==NULL)
        return;
    if(state==NXBUTTONINACTIVE){
        //If a route is set to or from out point then we need to leave/set the sensor to ACTIVE
        if(nxPoint->isRouteToPointSet()){
            state=NXBUTTONACTIVE;
        } else if(nxPoint->isRouteFromPointSet()){
            state=NXBUTTONACTIVE;
        }
    }
    nxPoint->setNXState(state);
    int sensorState = Sensor::UNKNOWN;
    switch(state){
        case NXBUTTONINACTIVE : sensorState = Sensor::INACTIVE;
                                break;
        case NXBUTTONACTIVE   : sensorState = Sensor::ACTIVE;
                                break;
        case NXBUTTONSELECTED : sensorState = Sensor::ACTIVE;
                                break;
        default               : sensorState = Sensor::UNKNOWN;
                                break;
    }

    //Might need to clear listeners at the stage and then reapply them after.
    if(((AbstractSensor*)nxPoint->getSensor())->getKnownState()!=sensorState){
        nxPoint->removeSensorList();
        try {
            nxPoint->getSensor()->setKnownState(sensorState);
        } catch (JmriException ex){
            log->error(ex.getMessage());
        }
        nxPoint->addSensorList();
    }
}

/*public*/ PointDetails* EntryExitPairs::getPointDetails(QObject* obj, LayoutEditor* panel)
{
  for (int i = 0; i<pointDetails->size(); i++)
  {
   if ((pointDetails->at(i)->getRefObject()==obj)
       && (pointDetails->at(i)->getPanel()==panel))
   {
    return pointDetails->at(i);
   }
  }
  return NULL;
}

/*
* Returns either an existing point, or creates a new one as required.
*/
PointDetails* EntryExitPairs::getPointDetails(LayoutBlock* source, QList<LayoutBlock*> destination, LayoutEditor* panel)
{
 PointDetails* newPoint = new PointDetails(source, destination);
 newPoint->setPanel(panel);
 for (int i = 0; i<pointDetails->size(); i++)
 {
  if (pointDetails->at(i)->equals(newPoint))
  {
   return pointDetails->at(i);
  }
 }
 //Not found so will add
 pointDetails->append(newPoint);
 return newPoint;
}

//No point in have multiple copies of what is the same thing.
/*static*/ QList<PointDetails*>* EntryExitPairs::pointDetails = new QList<PointDetails*>();

/*public*/QString EntryExitPairs::getPointAsString(NamedBean* obj, LayoutEditor* panel)
{
 if (obj==nullptr)
     return "null";
 PointDetails* valid = getPointDetails(obj, panel);  //was just plain getPoint
 if(valid != nullptr){
     return valid->getDisplayName();
 }
 return "empty";
}

/**
 * If a route is requested but is currently blocked, ask user
 * if it should be added to stackList.
 *
 * @param dp DestinationPoints object
 * @param reverse true for a reversed running direction, mostly false
 */
/*synchronized*/ /*public*/ void EntryExitPairs::stackNXRoute(DestinationPoints* dp, bool reverse) {
    if (isRouteStacked(dp, reverse)) {
        return;
    }
    stackList.append(new StackDetails(dp, reverse));
    checkTimer->start();
    if (stackPanel == nullptr) {
        stackPanel = new StackNXPanel();
    }
    if (stackDialog == nullptr) {
        stackDialog = new JDialog();
        QVBoxLayout* stackDialogLayout = new QVBoxLayout(stackDialog);
        stackDialog->setTitle(tr("Stacked Routes"));  // NOI18N
        stackDialogLayout->addWidget(stackPanel);
    }
    stackPanel->updateGUI();

    stackDialog->pack();
    stackDialog->setModal(false);
    stackDialog->setVisible(true);
}


/**
 * Get a list of all stacked routes from stackList.
 *
 * @return an List containing destinationPoint elements
 */
/*public*/ QList<DestinationPoints*> EntryExitPairs::getStackedInterlocks() {
    QList<DestinationPoints*> dpList = QList<DestinationPoints*>();
    for (StackDetails* st : stackList) {
        dpList.append(st->getDestinationPoint());
    }
    return dpList;
}

/**
 * Query if a stacked route is in stackList.
 *
 * @param dp DestinationPoints object
 * @param reverse true for a reversed running direction, mostly false
 * @return true if dp is in stackList
 */
/*public*/ bool EntryExitPairs::isRouteStacked(DestinationPoints* dp, bool reverse) {
    QListIterator<StackDetails*> iter(stackList);
    while (iter.hasNext()) {
        StackDetails* st = iter.next();
        if (st->getDestinationPoint() == dp && st->getReverse() == reverse) {
            return true;
        }
    }
    return false;
}

/**
 * Remove a stacked route from stackList.
 *
 * @param dp DestinationPoints object
 * @param reverse true for a reversed running direction, mostly false
 */
/*synchronized*/ /*public*/ void EntryExitPairs::cancelStackedRoute(DestinationPoints* dp, bool reverse) {
    QListIterator<StackDetails*> iter(stackList);
    while (iter.hasNext()) {
        StackDetails* st = iter.next();
        if (st->getDestinationPoint() == dp && st->getReverse() == reverse) {
            //iter.remove();
         stackList.removeOne(st);
        }
    }
    stackPanel->updateGUI();
    if (stackList.isEmpty()) {
        stackDialog->setVisible(false);
        checkTimer->stop();
    }
}

//QTimer* checkTimer = new javax.swing.Timer(10000, (java.awt.event.ActionEvent e) -> {
//    checkRoute();
//});

/**
 * Step through stackList and activate the first stacked route in line
 * if it is no longer blocked.
 */
/*synchronized*/ void EntryExitPairs::checkRoute() {
    checkTimer->stop();
//    QVector<StackDetails*> tmp = QVector<StackDetails*>(stackList.size());
//    stackList.toArray(tmp);
    QVector<StackDetails*> tmp = QVector<StackDetails*>(stackList.toVector());

    for (StackDetails* st : tmp) {
        if (!st->getDestinationPoint()->isActive()) {
            // If the route is not already active, then check.
            // If the route does get set, then the setting process will remove the route from the stack.
            st->getDestinationPoint()->setInterlockRoute(st->getReverse());
        }
    }

    if (!stackList.isEmpty()) {
        checkTimer->start();
    } else {
        stackDialog->setVisible(false);
    }
}

///*public*/ void removePropertyChangeListener(PropertyChangeListener list, NamedBean* obj, LayoutEditor* panel){
//    if (obj==NULL)
//        return;
//    PointDetails* valid = getPointDetails(obj, panel);
//    if(valid!=NULL){
//        valid.removePropertyChangeListener(list);
//    }
//}

//java.beans.PropertyChangeSupport pcs = new java.beans.PropertyChangeSupport(this);
/*public*/ /*synchronized*/ void EntryExitPairs::addPropertyChangeListener(PropertyChangeListener* /*l*/) {
    //pcs.addPropertyChangeListener(l);
    //disconnect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
}
/*public*/ /*synchronized*/ void EntryExitPairs::removePropertyChangeListener(PropertyChangeListener* /*l*/) {
    //pcs.removePropertyChangeListener(l);
}
/*protected*/ void EntryExitPairs::firePropertyChange(QString p, QVariant old, QVariant n)
{
 pcs->firePropertyChange(p,old,n);
 //emit propertyChange(new PropertyChangeEvent(this, p, old, n));
}


/**
* Discover all possible valid source and destination signalmasts past pairs
* on all layout editor panels.
*/
/*public*/ void EntryExitPairs::automaticallyDiscoverEntryExitPairs(LayoutEditor* editor, int interlockType) throw (JmriException)
{
 //This is almost a duplicate of that in the DefaultSignalMastLogicManager
 runWhenStablised=false;
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 if(!lbm->isAdvancedRoutingEnabled())
 {
  throw JmriException("advanced routing not enabled");
 }
 if(!lbm->routingStablised())
 {
  runWhenStablised=true;
  toUseWhenStable=editor;
  interlockTypeToUseWhenStable = interlockType;
  log->debug("Layout block routing has not yet stabilised, discovery will happen once it has");
  return;
 }

 QHash<NamedBean*, QList<NamedBean*> > validPaths = lbm->getLayoutBlockConnectivityTools()->discoverValidBeanPairs(editor, /*Sensor::_class*/"Sensor", LayoutBlockConnectivityTools::SENSORTOSENSOR);
 QListIterator<NamedBean*> en(validPaths.keys());
 EntryExitPairs* eep = this;
 while (en.hasNext())
 {
  NamedBean* key = en.next();
  QList<NamedBean*> validDestMast = validPaths.value(key);
  if(validDestMast.size()>0)
  {
   eep->addNXSourcePoint(key, editor);
   for(int i = 0; i<validDestMast.size(); i++)
   {
    if(!eep->isDestinationValid(key, validDestMast.at(i), editor))
    {
     eep->addNXDestination(key, validDestMast.at(i), editor);
     eep->setEntryExitType(key, editor, validDestMast.at(i), interlockType);
    }
   }
  }
 }

 firePropertyChange("autoGenerateComplete", QVariant(), QVariant());
}
// /*protected*/ PropertyChangeListener propertyBlockManagerListener = new PropertyChangeListener(){

/*public*/ void EntryExitPairs::propertyChange(PropertyChangeEvent* e)
{
 if(e->getPropertyName()==("topology"))
 {
  //bool newValue = new Boolean.parseBoolean(String.valueOf(e.getNewValue()));
  bool newValue = (bool) e->getNewValue().toBool();
  if(newValue)
  {
   if(runWhenStablised)
   {
    try
    {
     automaticallyDiscoverEntryExitPairs(toUseWhenStable, interlockTypeToUseWhenStable);
    }
    catch (JmriException je)
    {
      //Considered normal if routing not enabled
    }
   }
  }
 }
}

/*public*/ void EntryExitPairs::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) {

}


//@Override
/*public*/ /*synchronized*/ void EntryExitPairs::addVetoableChangeListener(VetoableChangeListener* l) {
    vcs->addVetoableChangeListener(l);
}

//@Override
/*public*/ /*synchronized*/ void EntryExitPairs::removeVetoableChangeListener(VetoableChangeListener* l) {
    vcs->removeVetoableChangeListener(l);
}


//@Override
/*public*/ void EntryExitPairs::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->addPropertyChangeListener(propertyName, listener);
}

//@Override
/*public*/ QVector<PropertyChangeListener*> EntryExitPairs::getPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners();
}

//@Override
/*public*/ QVector<PropertyChangeListener*> EntryExitPairs::getPropertyChangeListeners(QString propertyName) {
    return pcs->getPropertyChangeListeners(propertyName);
}

//@Override
/*public*/ void EntryExitPairs::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(propertyName, listener);
}

//@Override
/*public*/ void EntryExitPairs::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    vcs->addVetoableChangeListener(propertyName, listener);
}

//@Override
/*public*/ QVector<VetoableChangeListener*> EntryExitPairs::getVetoableChangeListeners() {
    return vcs->getVetoableChangeListeners();
}

//@Override
/*public*/ QVector<VetoableChangeListener*> EntryExitPairs::getVetoableChangeListeners(QString propertyName) {
    return vcs->getVetoableChangeListeners(propertyName);
}

//@Override
/*public*/ void EntryExitPairs::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    vcs->removeVetoableChangeListener(propertyName, listener);
}

//@Override
/*public*/ void EntryExitPairs::deleteBean(DestinationPoints* bean, QString property) throw (PropertyVetoException) {

}

//@Override
/*public*/ QString EntryExitPairs::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "Transits" : "Transit");  // NOI18N
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString EntryExitPairs::getNamedBeanClass()const {
    return "DestinationPoints";
}

/** {@inheritDoc} */
//@Override
/*public*/ void EntryExitPairs::addDataListener(QObject *e) {
    if (e != nullptr) listeners.append(e);
}

/** {@inheritDoc} */
//@Override
/*public*/ void EntryExitPairs::removeDataListener(/*ManagerDataListener*/QObject *e)  {
    if (e != nullptr) listeners.removeOne(e);
}


