#include "routetabledatamodel.h"
#include "instancemanager.h"
#include "route.h"
#include "routemanager.h"
#include "jtextfield.h"
#include "vptr.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "jtable.h"

/**
 * TableDataModel for the Route Table.
 *
 * Split from {@link RouteTableAction}
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 * @author Egbert Broerse Copyright (C) 2016
 * @author Paul Bender Colyright (C) 2020
 */
///*public*/ class RouteTableDataModel extends BeanTableDataModel<Route> {

RouteTableDataModel::RouteTableDataModel(QObject *parent) : BeanTableDataModel(parent)
{
 init();
}

//@Override
/*public*/ int RouteTableDataModel::columnCount(const QModelIndex &parent) const{
    return NUMCOLUMN + 3;
}

//@Override
/*public*/ QVariant  RouteTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col= section;
    if (col == VALUECOL) {
        return "";  // no heading on "Set"
    }
    if (col == SETCOL) {
        return "";  // no heading on "Edit"
    }
    if (col == ENABLECOL) {
        return tr("Enabled");
    }
    if (col == LOCKCOL) {
        return tr("Locked");
    }
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}

//@Override
/*public*/ QString RouteTableDataModel::getColumnClass(int col) const{
    if (col == SETCOL) {
        return "JButton";
    }
    if (col == ENABLECOL) {
        return "Boolean";
    }
    if (col == LOCKCOL) {
        return "Boolean";
    } else {
        return BeanTableDataModel::getColumnClass(col);
    }
}

//@Override
/*public*/ int RouteTableDataModel::getPreferredWidth(int col) {
    if (col == SETCOL) {
        return JTextField(6).getPreferredSize().width();
    }
    if (col == ENABLECOL) {
        return  JTextField(6).getPreferredSize().width();
    }
    if (col == LOCKCOL) {
        return  JTextField(6).getPreferredSize().width();
    } else {
        return BeanTableDataModel::getPreferredWidth(col);
    }
}

//@Override
/*public*/ Qt::ItemFlags RouteTableDataModel::flags(const QModelIndex &index) const
{
  int col = index.column();
  if (col == USERNAMECOL) {
      return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == SETCOL) {
   return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == ENABLECOL) {
   return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
  }
  // Route lock is available if turnouts are lockable
  if (col == LOCKCOL) {
      Route* r = (Route*)getBySystemName(data(this->index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
      return r->canLock()?(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable):(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  } else {
      return BeanTableDataModel::flags(index);
  }
}

//@Override
/*public*/ QVariant RouteTableDataModel::data(const QModelIndex &index, int role) const {
 int row = index.row();

   if(role == Qt::DisplayRole)
   {
    switch (index.column())
    {
    case SETCOL:
        return tr("Edit");
    default:
     break;
    }
   }
   if(role == Qt::CheckStateRole)
   {
     switch (index.column()) {
        case ENABLECOL:
        {
            Route* r = (Route*)getBySystemName(data(this->index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
            return r->getEnabled()? Qt::Checked:Qt::Unchecked;
        }
        case LOCKCOL:
        {
            Route* r = (Route*)getBySystemName(data(this->index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
            if (r->canLock()) {
                return r->getLocked()? Qt::Checked:Qt::Unchecked;
            } else {
                // this covers the case when route was locked and lockable turnouts were removed from the route
                r->setLocked(false);
                return Qt::Unchecked;
            }
        }
        default:
         break;
     }
    }
    return BeanTableDataModel::data(index, role);
}

//@Override
/*public*/ bool RouteTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if( role == Qt::CheckStateRole)
    {

     switch(index.column())
     {
      case ENABLECOL: {
          // alternate
          Route* r = (Route*)getBySystemName(data(this->index(index.row(), (int)SYSNAMECOL),Qt::DisplayRole).toString());

          bool v = r->getEnabled();
          r->setEnabled(!v);
          break;
      }
      case LOCKCOL: {
          // alternate
          Route* r = (Route*)getBySystemName(data(this->index(index.row(), (int)SYSNAMECOL),Qt::DisplayRole).toString());

          bool v = r->getLocked();
          r->setLocked(!v);
          break;
        }
     default:
      break;
     }
    }
    if(role == Qt::EditRole)
    {
     switch(index.column())
     {
        case USERNAMECOL:
        {
            // Directly changing the username should only be possible if the username was previously null or ""
            // check to see if user name already exists
            if (value == QVariant()) {
//                value = " ";
            } else {
                NamedBean* nB = getByUserName( value.toString());
                if (nB != nullptr) {
                    log->error(tr("User Name is not unique %1").arg(value.toString()));
                    QString msg;
                    msg = tr("User Name is not unique %1").arg(value.toString());
                    JOptionPane::showMessageDialog(nullptr, msg, tr("Warning"), JOptionPane::ERROR_MESSAGE);
                    return true;
                }
            }
            NamedBean* nBean = getBySystemName(sysNameList.at(index.row()));
            nBean->setUserName(value.toString());
            fireTableRowsUpdated(index.row(), index.row());
            break;
        }
        case SETCOL:
        {
//            // set up to edit. Use separate Runnable so window is created on top
//            class WindowMaker implements Runnable {

//                int row;

//                WindowMaker(int r) {
//                    row = r;
//                }

//                //@Override
//                /*public*/ void run() {
//                    JmriJFrame* editFrame = new RouteEditFrame( VPtr<NamedBean>::asPtr(getValueAt(index.row(), SYSNAMECOL))->getSystemName());
//                    editFrame->setVisible(true);
//                }

//            }
            WindowMaker* t = new WindowMaker(index.row(), this);
//            javax.swing.SwingUtilities.invokeLater(t);
            t->run();
            break;
        }
        default:
            break;
    }
  }
   return BeanTableDataModel::setData(index, value, role);
}

//@Override
/*public*/ void RouteTableDataModel::configureTable(JTable* table) {
//    table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
 setColumnToHoldButton(table, SETCOL);
    BeanTableDataModel::configureTable(table);
}

/**
 * Delete the bean after all the checking has been done.
 * <p>
 * Deactivate the Route, then use the superclass to delete it.
 */
//@Override
/*protected*/ void RouteTableDataModel::doDelete(NamedBean *bean) {
    ((Route*)bean)->deActivateRoute();
    BeanTableDataModel::doDelete(bean);
}

// want to update when enabled parameter changes
//@Override
/*protected*/ bool RouteTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("Enabled")) { // NOI18N
        return true;
    }
    if (e->getPropertyName() == ("Locked")) { // NOI18N
        return true;
    } else {
        return BeanTableDataModel::matchPropertyName(e);
    }
}

//@Override
/*public*/ Manager *RouteTableDataModel::getManager() {
    return (RouteManager*)InstanceManager::getDefault("RouteManager");
}

//@Override
/*public*/ NamedBean* RouteTableDataModel::getBySystemName(QString name) const {
    return (NamedBean*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getBySystemName(name);
}

//@Override
/*public*/ NamedBean* RouteTableDataModel::getByUserName(QString name) {
    return (NamedBean*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getByUserName(name);
}

//@Override
/*protected*/ QString RouteTableDataModel::getMasterClassName() {
    return /*this.getClass().getName()*/ "jmri.jmrit.beantable.RouteTableDataModel";
}

//@Override
/*public*/ void RouteTableDataModel::clickOn(NamedBean* t) {
    ((Route*)t)->setRoute();
}

//@Override
/*public*/ QString RouteTableDataModel::getValue(QString s) const {
    return tr("Set");
    //Title of Set button in Route table
}

//@Override
/*protected*/ QString RouteTableDataModel::getBeanType(){
    return tr("Route");
}

/*private*/ /*static*/ /*final*/ Logger* RouteTableDataModel::log = LoggerFactory::getLogger("RouteTableDataModel");
