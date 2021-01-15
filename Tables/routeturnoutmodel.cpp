#include "routeturnoutmodel.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "routeturnout.h"
#include "loggerfactory.h"
#if 1
/**
 * Table model for selecting Turnouts and Turnout State.
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
//class RouteTurnoutModel extends RouteOutputModel {


    RouteTurnoutModel::RouteTurnoutModel(AbstractRouteAddEditFrame* routeAddFrame, QObject* parent) : RouteOutputModel(parent){
        this->routeAddFrame = routeAddFrame;
        InstanceManager::turnoutManagerInstance()->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    //@Override
    /*public*/ int RouteTurnoutModel::rowCount(const QModelIndex &parent) const {
        if (routeAddFrame->isShowAll()) {
            return routeAddFrame->get_turnoutList().size();
        } else {
            return routeAddFrame->get_includedTurnoutList().size();
        }
    }

    //@Override
    /*public*/ QVariant RouteTurnoutModel::data(const QModelIndex &index, int role) const {
     if(role == Qt::DisplayRole)
     {
        QList<RouteTurnout*> turnoutList;
        if (routeAddFrame->isShowAll()) {
            turnoutList = routeAddFrame->get_turnoutList();
        } else {
            turnoutList = routeAddFrame->get_includedTurnoutList();
        }
        // some error checking
        if (index.row() >= turnoutList.size()) {
            log->debug("row is greater than turnout list size");
            return QVariant();
        }
        if(role == Qt::CheckStateRole)
        {
          switch (index.column()) {
              case INCLUDE_COLUMN:
                  return turnoutList.value(index.row())->isIncluded()?Qt::Checked: Qt::Unchecked;
          default:
              return QVariant();
          }
         }
         if(role == Qt::DisplayRole)
         {
          switch (index.column()) {
            case SNAME_COLUMN:  // slot number
              return turnoutList.value(index.row())->getSysName();
            case UNAME_COLUMN:  //
                return turnoutList.value(index.row())->getUserName();
            case STATE_COLUMN:  //
                return turnoutList.value(index.row())->getSetToState();
            default:
                return QVariant();
          }
         }
     }
    }

    //@Override
    /*public*/ bool RouteTurnoutModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        QList<RouteTurnout*> turnoutList;
        if (routeAddFrame->isShowAll())
        {
            turnoutList = routeAddFrame->get_turnoutList();
        } else {
            turnoutList = routeAddFrame->get_includedTurnoutList();
        }
        if(role == Qt::CheckStateRole)
        {
         switch (index.column())
         {
            case INCLUDE_COLUMN:
                turnoutList.value(index.row())->setIncluded( value.toBool());
                return true;
            default:
             break;
         }
        }
        if(role == Qt::EditRole)
        {
         switch (index.column()) {
            case STATE_COLUMN:
                turnoutList.value(index.row())->setSetToState(value.toString());
                return true;
            default:
                log->error(tr("RouteTurnoutModel.setValueAt should not be called on column %1").arg(index.column()));
         }
        }
        return false;
     }


    /*private*/ /*static*/ /*final*/ Logger* RouteTurnoutModel::log = LoggerFactory::getLogger("RouteTurnoutModel");
#else
/**
 * Table model for selecting Turnouts and Turnout State
 */
//class RouteTurnoutModel : public RouteOutputModel
//{
RouteTurnoutModel::RouteTurnoutModel(AbstractRouteAddEditFrame *routeAddFrame) : QAbstractTableModel()
{
 this->routeAddFrame = routeAddFrame;

 ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
 Q_UNUSED(mgr);
 //InstanceManager::turnoutManagerInstance().addPropertyChangeListener(this);
 //connect(mgr, SIGNAL())
 log = new Logger("RouteTurnoutModel");
}

/*public*/ int RouteTurnoutModel::rowCount (const QModelIndex &parent) const
{
 if (routeAddFrame->isShowAll()) {
             return routeAddFrame.get_turnoutList().size();
         } else {
             return routeAddFrame.get_includedTurnoutList().size();
         }
}

int RouteTurnoutModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

QVariant RouteTurnoutModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
  return QVariant();
 if (orientation == Qt::Horizontal)
 {
  return self->COLUMN_NAMES.at(section);
 }
 return QVariant();
}

Qt::ItemFlags RouteTurnoutModel::flags(const QModelIndex &index) const
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
/*public*/ QVariant RouteTurnoutModel::data (const QModelIndex &index, int role) const
{
 if (!index.isValid())
  return QVariant();
 int r = index.row();
 int c = index.column();
 QList <RouteTurnout*>* turnoutList = NULL;
 if (self->showAll)
 {
  turnoutList = self->_turnoutList;
 }
 else
 {
  turnoutList = self->_includedTurnoutList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
  {
   return turnoutList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
  }
 }
 if (role == Qt::DisplayRole || role == Qt::EditRole)
 {
  QList <RouteTurnout*>* turnoutList = NULL;
  if (self->showAll)
  {
   turnoutList = self->_turnoutList;
  }
  else
  {
   turnoutList = self->_includedTurnoutList;
  }
  // some error checking
  if (r >= turnoutList->size())
  {
   log->debug("row is greater than turnout list size");
   return QVariant();
  }
  switch (c)
  {
//  case INCLUDE_COLUMN:
//        break;
  case SNAME_COLUMN:  // slot number
        return turnoutList->at(r)->getSysName();
  case UNAME_COLUMN:  //
        return turnoutList->at(r)->getUserName();
  case STATE_COLUMN:  //
  {
   return turnoutList->at(r)->getSetToState();
  }
  default:
   break;
  }
 }
 return QVariant();
}
/*public*/ bool RouteTurnoutModel::setData(const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/)
{
 int c = index.column();
 int r = index.row();
 QList <RouteTurnout*>* turnoutList = NULL;
 if (self->showAll)
  turnoutList = self->_turnoutList;
 else
  turnoutList = self->_includedTurnoutList;
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
  {
   turnoutList->at(r)->setIncluded(value.toBool());
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  switch (c)
  {
//  case INCLUDE_COLUMN:
//   turnoutList->at(r)->setIncluded(value.toBool());
//   break;
  case STATE_COLUMN:
   {
    turnoutList->at(r)->setSetToState(value.toString());
   break;;
   }
  }
  return true;
 }
 return false;
}

void RouteTurnoutModel::reset()
{
 //QAbstractTableModel::reset();
 beginResetModel();
 endResetModel();
}
#endif
