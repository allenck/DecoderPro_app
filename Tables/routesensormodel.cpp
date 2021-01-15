#include "routesensormodel.h"
#include "loggerfactory.h"
#include "instancemanager.h"

/**
 * Set up table for selecting Sensors and Sensor State.
 *
 * Split from {@link jmri.jmrit.beantable.RouteTableAction}
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 * @author Egbert Broerse Copyright (C) 2016
 * @author Paul Bender Copyright (C) 2020
 */
//class RouteSensorModel extends RouteOutputModel {


    RouteSensorModel::RouteSensorModel(AbstractRouteAddEditFrame* routeAddFrame, QObject* parent) : RouteOutputModel(parent) {
        this->routeAddFrame = routeAddFrame;
        InstanceManager::sensorManagerInstance()->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    //@Override
    /*public*/ int RouteSensorModel::getRowCount() const {
        if (routeAddFrame->isShowAll()) {
            return routeAddFrame->get_sensorList().size();
        } else {
            return routeAddFrame->get_includedSensorList().size();
        }
    }

    //@Override
    /*public*/ QVariant RouteSensorModel::data(const QModelIndex &index, int role) const {
        QList<RouteSensor*> sensorList;
        if (routeAddFrame->isShowAll()) {
            sensorList = routeAddFrame->get_sensorList();
        } else {
            sensorList = routeAddFrame->get_includedSensorList();
        }
        // some error checking
        if (index.row() >= sensorList.size()) {
            log->debug("row is greater than turnout list size");
            return QVariant();
        }
        if(role == Qt::CheckStateRole)
         switch (index.column()) {
            case INCLUDE_COLUMN:
                return sensorList.value(index.row())->isIncluded()?Qt::Checked:Qt::Unchecked;
        default:
            return QVariant();
        }
        if(role == Qt::EditRole)
         switch (index.column()) {

            case SNAME_COLUMN:  // slot number
                return sensorList.value(index.row())->getSysName();
            case UNAME_COLUMN:  //
                return sensorList.value(index.row())->getUserName();
            case STATE_COLUMN:  //
                return sensorList.value(index.row())->getSetToState();
            default:
                return QVariant();
        }
    }

    //@Override
    /*public*/ bool RouteSensorModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        QList<RouteSensor*> sensorList;
        if (routeAddFrame->isShowAll()) {
            sensorList = routeAddFrame->get_sensorList();
        } else {
            sensorList = routeAddFrame->get_includedSensorList();
        }
        if(role == Qt::CheckStateRole)
        {
         switch (index.column()) {
             case INCLUDE_COLUMN:
                 sensorList.value(index.row())->setIncluded(( value.toBool()));
                 return true;
         default:
          break;
         }
        }
        if(role == Qt::EditRole)
        {
         switch (index.column()) {
            case STATE_COLUMN:
                sensorList.value(index.row())->setSetToState( value.toString());
                return true;
            default:
                break;
                //log->error(tr("RouteSensorModel.setValueAt should not be called on column %1").arg(c));
         }
        }
        return false;
    }

    /*private*/ /*static*/ /*final*/ Logger* RouteSensorModel::log = LoggerFactory::getLogger("RouteSensorModel");
#if 0
/**
 * Set up table for selecting Sensors and Sensor State
 */
//class RouteSensorModel : public RouteOutputModel
//{
RouteSensorModel::RouteSensorModel(RouteTableAction* self) : QAbstractTableModel(self)
{
 //InstanceManager.sensorManagerInstance().addPropertyChangeListener(this);
    log = new Logger("RouteSensorModel");
    this->self = self;
}
int RouteSensorModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

/*public*/ int RouteSensorModel::rowCount (const QModelIndex &parent) const
{
 if(parent.isValid()) return 0;

 if (self->showAll)
  return self->_sensorList->size();
 else
  return self->_includedSensorList->size();
}

/*public*/ QVariant RouteSensorModel::data (const QModelIndex &index, int role) const
{
 if(!index.isValid()) return QVariant();
 int c = index.column();
 int r = index.row();
 QList <RouteSensor*>* sensorList = NULL;
 if (self->showAll)
 {
  sensorList = self->_sensorList;
 }
 else
 {
  sensorList = self->_includedSensorList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
   return sensorList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
 }
 if (role == Qt::DisplayRole || role == Qt::EditRole)
 {
  // some error checking
  if (r >= sensorList->size())
  {
   log->debug("row is greater than turnout list size");
   return QVariant();
  }
  switch (c)
  {
    case INCLUDE_COLUMN:
        break;
    case SNAME_COLUMN:  // slot number
        return sensorList->at(r)->getSysName();
    case UNAME_COLUMN:  //
        return sensorList->at(r)->getUserName();
    case STATE_COLUMN:  //
        return sensorList->at(r)->getSetToState();
    default:
      return QVariant();
  }
 }
 return QVariant();
}

/*public*/ bool RouteSensorModel::setData(const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/)
{
 int c = index.column();
 int r = index.row();
 QList <RouteSensor*>* sensorList = NULL;
 if (self->showAll)
 {
   sensorList = self->_sensorList;
 }
 else
 {
  sensorList = self->_includedSensorList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
   sensorList->at(r)->setIncluded(value.toBool());
   return true;
 }
 if(role == Qt::EditRole)
 {
  switch (c)
  {
//    case INCLUDE_COLUMN:
//        sensorList->at(r)->setIncluded(value.toBool());
//        break;
    case STATE_COLUMN:
        sensorList->at(r)->setSetToState(value.toString());
        break;
  }
  return true;
 }
 return false;
}

QVariant RouteSensorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
  return QVariant();
 if (orientation == Qt::Horizontal)
 {
  return self->COLUMN_NAMES.at(section);
 }
 return QVariant();
}

Qt::ItemFlags RouteSensorModel::flags(const QModelIndex &index) const
{
 if (!index.isValid())
  return Qt::ItemIsEnabled;
 Qt::ItemFlags flags = QAbstractTableModel::flags(index);
 switch(index.column())
 {
  case INCLUDE_COLUMN:
   flags |= Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
   break;
 case STATE_COLUMN:
 case UNAME_COLUMN:
   flags |= Qt::ItemIsEditable;
   break;
 }
 // all other columns non-editable
 return flags;
}

void RouteSensorModel::reset()
{
 //QAbstractTableModel::reset();
 beginResetModel();
 endResetModel();
}

#endif
