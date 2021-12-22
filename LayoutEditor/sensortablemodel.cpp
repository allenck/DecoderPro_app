#include "sensortablemodel.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "logger.h"

//SensorTableModel::SensorTableModel(QObject *parent) :
//  BeanTableModel(parent)
//{
//}
/**
 * Model for a simple Sensor JTable
 *
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Pete Cressman Copyright (C) 2009
 *
 * @version $Revision: 28746 $
 */
///*public*/ class SensorTableModel extends BeanTableModel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = -3536564177611715912L;

/*public*/ SensorTableModel::SensorTableModel(QObject *parent) :
  BeanTableModel(parent) {
 log = new Logger("SensorTableModel");

    init();
    ((AbstractManager*)getManager()->self())->PropertyChangeSupport::addPropertyChangeListener((PropertyChangeListener*)this);
//    ProxySensorManager* a = (ProxySensorManager*)getManager();
//    connect(a->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*private*/ void SensorTableModel::init()
{
    _sysNameList = getManager()->getSystemNameArray();

    _includedSensors = QList<bool>();
    for (int i = 0; i < _sysNameList.length(); i++)
    {
       //_includedSensors[i] = Boolean.FALSE;
     _includedSensors.append(false);
    }
}

/*public*/ void SensorTableModel::dispose() {
 ((AbstractManager*)getManager()->self())->PropertyChangeSupport::removePropertyChangeListener((PropertyChangeListener*)this);
// ProxySensorManager* a = (ProxySensorManager*)getManager();
// disconnect(a->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ Manager* SensorTableModel::getManager() const {
    return InstanceManager::sensorManagerInstance();
}

/*public*/ int SensorTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return _sysNameList.length();
}

/*public*/ QVariant SensorTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int r = index.row();
  int c = index.column();
  if (r >= _sysNameList.length())
  {
     return QVariant();
    }
    switch (c) {
        case INCLUDE_COLUMN:  // expect to be overriden
            return _includedSensors[r];
        case SNAME_COLUMN:
            return _sysNameList[r];
        case UNAME_COLUMN:
            return InstanceManager::sensorManagerInstance()->provideSensor(_sysNameList[r])->getUserName();
        default:
     return BeanTableModel::data(index, role);
    }
 }
 return QVariant();
}

/*public*/ bool SensorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int r = index.row();
  int c = index.column();
  if (r > _sysNameList.length()) {
        return false;
    }
    switch (c) {
        case INCLUDE_COLUMN:
            _includedSensors.replace(r, value.toBool());
            return true;
        default:
            log->warn("default hit in setValueAt");
    }
 }
 return false;
}

/*public*/ void SensorTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new NamedBean is available in the manager
        init();
        fireTableDataChanged();
    }
}
