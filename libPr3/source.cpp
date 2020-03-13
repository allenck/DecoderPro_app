#include "source.h"
#include "entryexitpairs.h"
#include "destinationpoints.h"
#include "../LayoutEditor/layouteditor.h"
#include "pointdetails.h"
#include "instancemanager.h"
#include "signalmast.h"

//Source::Source(QQObject* *parent) :
//    QObject(parent)
//{
//}
// /*public*/ class Source {




/*public*/ bool Source::isEnabled(QObject* dest,LayoutEditor* panel){
    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        return pointToDest->value(lookingFor)->isEnabled();
    }
    return true;
}

/*public*/ void Source::setEnabled(QObject* dest, LayoutEditor* panel, bool boo){
    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        pointToDest->value(lookingFor)->setEnabled(boo);
    }
}

/*public*/ Source::Source(PointDetails* point, QObject* parent) : QObject(parent)
{
 entryExitPopUp = NULL;
 clear = NULL;
 cancel = NULL;

 sourceObject = NULL;
 sourceSignal = NULL;
 //String ref = "Empty";
 pd = NULL;
 pcs = new PropertyChangeSupport(this);

 manager = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");

 //Using QObject* here rather than sourceSensor, working on the basis that it might
 //one day be possible to have a signal icon selectable on a panel and
 //generate a propertychange, so hence do not want to tie it down at this stage.
 pointToDest = new QHash<PointDetails*, DestinationPoints*>();

 if(point->getSensor()!=NULL){
     addSourceObject(point->getSensor());
 } else {
     addSourceObject(point->getSignal());
 }
 point->setSource(this);
 sourceSignal = point->getSignal();
 pd = point;
 //createPopUpMenu();

 setObjectName(point->getDisplayName());
}

/**
 * @since 4.17.4
 */
/*public*/ void Source::addPropertyChangeListener(PropertyChangeListener* listener) {
    pcs->addPropertyChangeListener(listener);
}

/**
 * @since 4.17.4
 */
/*public*/ void Source::removePropertyChangeListener(PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(listener);
}

/**
 * @since 4.17.4
 */
//@Override
/*public*/ void Source::propertyChange(PropertyChangeEvent* evt) {
    pcs->firePropertyChange("active", evt->getOldValue(), evt->getNewValue());
}
#if 0
void Source::createPopUpMenu(){
    if(entryExitPopUp!=NULL)
        return;
    entryExitPopUp = new QMenu("Entry Exit");
    QAction* editClear = new QAction(tr("Clear Route"), this);
//    editClear.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelClearInterlockFromSource(EntryExitPairs.CLEARROUTE);
//        }
//    });
    connect(editClear, SIGNAL(triggered()), this, SLOT(on_editClear()));
    entryExitPopUp->addAction(editClear);
    QAction* editCancel = new QAction(tr("Cancel Route"),this);
//    editCancel.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelClearInterlockFromSource(EntryExitPairs.CANCELROUTE);
//        }
//    });
    connect(editCancel, SIGNAL(triggered()), this, SLOT(on_editCancel()));
    entryExitPopUp->addAction(editCancel);

    clear = new QAction(tr("Clear Route"),this);
//    clear.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelClearInterlockFromSource(EntryExitPairs.CLEARROUTE);
//        }
//    });
    connect(clear, SIGNAL(triggered()), this, SLOT(on_clear()));
    cancel = new QAction(tr("Cancel Route"),this);
//    cancel.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelClearInterlockFromSource(EntryExitPairs.CANCELROUTE);
//        }
//    });
    connect(cancel, SIGNAL(triggered()), this, SLOT(on_cancel()));
    pd->getPanel()->addToPopUpMenu(pd->getSensor(), entryExitPopUp, Editor::EDITPOPUPONLY);
    //
    QMenu item1;
    item1.addAction(clear);
    pd->getPanel()->addToPopUpMenu(pd->getSensor(), &item1, Editor::VIEWPOPUPONLY);

    QMenu item2;
    item2.addAction(cancel);
    pd->getPanel()->addToPopUpMenu(pd->getSensor(), &item2, Editor::VIEWPOPUPONLY);
    setMenuEnabled(false);
}

void Source ::on_editCancel()
{
  cancelClearInterlockFromSource(EntryExitPairs::CANCELROUTE);
}
void Source::on_clear()
{
 cancelClearInterlockFromSource(EntryExitPairs::CANCELROUTE);
}
void Source::on_editClear()
{
 cancelClearInterlockFromSource(EntryExitPairs::CLEARROUTE);
}
void Source::on_cancel()
{
 cancelClearInterlockFromSource(EntryExitPairs::CANCELROUTE);
}
#endif
void Source::cancelClearInterlockFromSource(int cancelClear){
    foreach(DestinationPoints* dp, pointToDest->values()){
        if(dp->isActive()){
            dp->cancelClearInterlock(cancelClear);
        }
    }
}

void Source::setMenuEnabled(bool boo){
//    if (entryExitPopUp!=NULL)
//        entryExitPopUp->setEnabled(boo);
    if (clear!=NULL)
        clear->setEnabled(boo);
    if (cancel!=NULL)
        cancel->setEnabled(boo);
    if (editClear != nullptr) {
        editClear->setEnabled(boo);
    }
    if (editCancel != nullptr) {
        editCancel->setEnabled(boo);
    }
    if (oneClick != nullptr) {
        oneClick->setEnabled(!boo);
    }
    if (editOneClick != nullptr) {
        editOneClick->setEnabled(!boo);
    }
}

PointDetails*  Source::getPoint(){
    return pd;
}

LayoutBlock* Source::getStart(){
    return pd->getFacing();
}

QList<LayoutBlock*> Source::getSourceProtecting(){
    return pd->getProtecting();
}

NamedBean* Source::getSourceSignal(){
    if(sourceSignal==NULL){
        pd->getSignal();
    }
    return sourceSignal;
}

/*public*/ void Source::addDestination(PointDetails* dest, QString id){
    if(pointToDest->contains(dest)){
        return;
    }

    DestinationPoints* dstPoint = new DestinationPoints(dest, id, this);
    dest->setDestination(dstPoint, this);
    pointToDest->insert(dest, dstPoint);
    dstPoint->addPropertyChangeListener((PropertyChangeListener*)this);
}

/*public*/ void Source::removeDestination(PointDetails* dest){
    pointToDest->value(dest)->dispose();
    pointToDest->remove(dest);
    dest->removePropertyChangeListener((PropertyChangeListener*)this);
    if(pointToDest->size()==0){
        getPoint()->removeSource(this);
    }
}

void Source::addSourceObject(NamedBean* source){
    if (sourceObject==source)
        return;
    sourceObject = source;
}

QObject* Source::getSourceObject()
{
 return sourceObject;
}

/*public*/ QList<PointDetails*> Source::getDestinationPoints() {
    //ArrayList<PointDetails> rtn =
    return QList<PointDetails*>(pointToDest->keys());
}

/*public*/ bool Source::isDestinationValid(PointDetails* destPoint){
    return pointToDest->contains(destPoint);
}

/*public*/ bool Source::getUniDirection(QObject* dest, LayoutEditor* panel){
    //Work on the principle that if the source is uniDirection, then the destination has to be.
    PointDetails*  lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        return pointToDest->value(lookingFor)->getUniDirection();
    }
    return true;
}

/*public*/ void Source::setUniDirection(QObject* dest, LayoutEditor* panel, bool set){

    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        pointToDest->value(lookingFor)->setUniDirection(set);
    }
}

/*public*/ bool Source::canBeBiDirection(QObject* dest, LayoutEditor* panel){
    if(getSourceSignal()==NULL){
        return true;
    }
    //Work on the principle that if the source is uniDirection, then the destination has to be.
    PointDetails*  lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        return pointToDest->value(lookingFor)->getSignal()==NULL;
    }
    return false;
}

/*public*/ bool Source::isRouteActive(PointDetails*  endpoint){
    if(pointToDest->contains(endpoint)){
        return pointToDest->value(endpoint)->activeEntryExit;
    }
    return false;
}

void Source::activeBean(DestinationPoints* dest, bool reverseDirection){
    if (dest != nullptr) {
     dest->activeBean(reverseDirection);
 }

}

/*public*/ DestinationPoints* Source::getDestForPoint(PointDetails* dp) {
    return pointToDest->value(dp);
}

/*public*/ int Source::getNumberOfDestinations() {
 return pointToDest->size();
}

/*public*/ void Source::setEntryExitType(QObject* dest, LayoutEditor* panel, int type){
    PointDetails*  lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        pointToDest->value(lookingFor)->setEntryExitType(type);
    }
    if(type == EntryExitPairs::FULLINTERLOCK){
        //if (sourceSignal instanceof SignalMast)
        if(qobject_cast<SignalMast*>(sourceSignal)!= NULL)
        {
            ((SignalMast*) sourceSignal)->setHeld(true);
        }
    }
}

/*public*/ int Source::getEntryExitType(QObject* dest, LayoutEditor* panel){
    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        return pointToDest->value(lookingFor)->getEntryExitType();
    }

    return 0x00;
}

/*public*/ void Source::cancelInterlock(QObject* dest, LayoutEditor* panel){
    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        pointToDest->value(lookingFor)->cancelClearInterlock(EntryExitPairs::CANCELROUTE);
    }
}

/*public*/ QString Source::getUniqueId(QObject* dest, LayoutEditor* panel){
    PointDetails* lookingFor = manager->getPointDetails(dest, panel);
    if(pointToDest->contains(lookingFor)){
        return pointToDest->value(lookingFor)->getUniqueId();
    }
    return QString();
}

/*public*/ QStringList Source::getDestinationUniqueId(){
    QStringList rList =  QStringList();
    foreach(DestinationPoints* d, pointToDest->values()){
        rList.append(d->getUniqueId());
    }
    return rList;
}

/*public*/ DestinationPoints* Source::getByUniqueId(QString id){
    foreach(DestinationPoints* d, pointToDest->values()){
        if(d->getUniqueId() == (id))
            return d;
    }
    return nullptr;
}

/*public*/ DestinationPoints* Source::getByUserName(QString id){
    foreach(DestinationPoints* d, pointToDest->values()){
     QString uname = d->getUserName();
        if(uname != "" && uname == (id))
            return d;
    }
    return nullptr;
}
