#include "throttlestablemodel.h"
#include "propertychangeevent.h"
#include "throttlewindow.h"
#include "dcclocoaddress.h"
#include "locoaddress.h"
#include "instancemanager.h"
#include "abstractthrottlemanager.h"

ThrottlesTableModel::ThrottlesTableModel(QObject *parent) :
    AbstractTableModel(parent)
{
 throttleFrames =  QList<ThrottleWindow*>(/*5*/);
}
// /*public*/ class ThrottlesTableModel extends AbstractTableModel implements AddressListener, java.beans.PropertyChangeListener {

/*public*/ int ThrottlesTableModel::rowCount(const QModelIndex& /*index*/) const
{
    return throttleFrames.size();
}

/*public*/ int ThrottlesTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

/*public*/ QVariant ThrottlesTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  return VPtr<ThrottleWindow>::asQVariant(throttleFrames.at(index.row()));
 }
 return QVariant();
}

/*public*/ QListIterator<ThrottleWindow*> ThrottlesTableModel::iterator()
{
 QListIterator<ThrottleWindow*> iter(throttleFrames);
 return iter;
}

/*public*/ void ThrottlesTableModel::addThrottleFrame(ThrottleWindow* tf) {
    throttleFrames.append(tf);
    fireTableDataChanged();
}

/*public*/ void ThrottlesTableModel::removeThrottleFrame(ThrottleWindow* tf, DccLocoAddress* la) {
    throttleFrames.removeAt(throttleFrames.indexOf(tf));
    if(la!=NULL)
        ((AbstractThrottleManager*)InstanceManager::throttleManagerInstance())->removeListener(la, (PropertyChangeListener*)this);
    fireTableDataChanged();
}

/*public*/ void ThrottlesTableModel::notifyAddressChosen(LocoAddress* la) {
}

/*public*/ void ThrottlesTableModel::notifyAddressReleased(LocoAddress* addr) {
    DccLocoAddress* la = (DccLocoAddress*)addr;
    fireTableDataChanged();
    ((AbstractThrottleManager*)InstanceManager::throttleManagerInstance())->removeListener(la, (PropertyChangeListener*)this);
}

/*public*/ void ThrottlesTableModel::notifyAddressThrottleFound(DccThrottle* throttle) {
    fireTableDataChanged();
    throttle->addPropertyChangeListener((PropertyChangeListener*)this);
}

/*public*/ void ThrottlesTableModel::notifyConsistAddressChosen(int /*newAddress*/, bool /*isLong*/) {
}

/*public*/ void ThrottlesTableModel::notifyConsistAddressReleased(int /*address*/, bool /*isLong*/) {
}

/*public*/ void ThrottlesTableModel::notifyConsistAddressThrottleFound(DccThrottle* /*throttle*/) {
}

/*public*/ void ThrottlesTableModel::propertyChange(PropertyChangeEvent* e)
{
 if ((e->getPropertyName()==("SpeedSetting")) || (e->getPropertyName()==("SpeedSteps")) || (e->getPropertyName()==("IsForward")))
 {
  fireTableDataChanged();
 }
}
//}
