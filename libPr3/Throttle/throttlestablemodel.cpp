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
 if(role == Qt::UserRole)
 {
  return VPtr<ThrottleWindow>::asQVariant(throttleFrames.at(index.row()));
 }
 if(role == Qt::DisplayRole)
 {
  return throttleFrames.at(index.row())->getTitle();
 }
 return QVariant();
}

/*public*/ QListIterator<ThrottleWindow*> ThrottlesTableModel::iterator()
{
 QListIterator<ThrottleWindow*> iter(throttleFrames);
 return iter;
}

/*public*/ void ThrottlesTableModel::addThrottleFrame(ThrottleWindow* tf)
{
 beginInsertRows(QModelIndex(), throttleFrames.count(), throttleFrames.count());
 throttleFrames.append(tf);
 endInsertRows();
    fireTableDataChanged();
}

/*public*/ void ThrottlesTableModel::removeThrottleFrame(ThrottleWindow* tf, DccLocoAddress* la)
{
 int row = throttleFrames.indexOf(tf);
 beginRemoveRows(QModelIndex(), row, row);
 throttleFrames.removeAt(row);
 endRemoveRows();
 //setPersistentButtons();
 if(la!=NULL)
        ((AbstractThrottleManager*)InstanceManager::throttleManagerInstance())->removeListener(la, (PropertyChangeListener*)this);
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
    //throttle->addPropertyChangeListener((PropertyChangeListener*)this);
    connect((AbstractThrottle*)throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

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
