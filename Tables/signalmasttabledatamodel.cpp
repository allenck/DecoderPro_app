#include "signalmasttabledatamodel.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "turnoutsignalmast.h"
#include "jtextfield.h"
#include "signallingsourceaction.h"
#include "addsignalmastjframe.h"
#include "xtablecolumnmodel.h"

SignalMastTableDataModel::SignalMastTableDataModel(QObject* parent) : BeanTableDataModel(parent)
{
 init();
}
/**
 * Data model for a SignalMastTable
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2009
 * @version $Revision$
 */
///*public*/ class SignalMastTableDataModel extends BeanTableDataModel {

/**
 *
 */
//private static final long serialVersionUID = 2753901812548953185L;

/*public*/ QString SignalMastTableDataModel::getValue(QString name) const {
    return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name)->getAspect();
}

/*public*/ int SignalMastTableDataModel::columnCount(const QModelIndex &parent) const
{
    return NUMCOLUMN + 4;
}

/*public*/ QVariant SignalMastTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 int col = section;
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (col == VALUECOL) {
        return tr("Aspect Type");
    } else if (col == EDITMASTCOL) {
        return ""; // override default, no title for Edit column
    } else if (col == EDITLOGICCOL) {
        return ""; // override default, no title for Edit Logic column
    } else if (col == LITCOL) {
        return tr("Lit");
    } else if (col == HELDCOL) {
        return tr("Held");
    }
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}

/*public*/ QString SignalMastTableDataModel::getColumnClass(int col) {
    if (col == VALUECOL) {
        return "JComboBox";
    } else if (col == EDITMASTCOL) {
        return "JButton";
    } else if (col == EDITLOGICCOL) {
        return "JButton";
    } else if (col == LITCOL) {
        return "Boolean";
    } else if (col == HELDCOL) {
        return "Boolean";
    } else {
        return BeanTableDataModel::getColumnClass(col);
    }
}

/*public*/ int SignalMastTableDataModel::getPreferredWidth(int col) {
    if (col == LITCOL) {
        return  JTextField(4).sizeHint().width();;
    } else if (col == HELDCOL) {
        return  JTextField(4).sizeHint().width();;
    } else if (col == EDITLOGICCOL) {
        return  JTextField(8).sizeHint().width();;
    } else if (col == EDITMASTCOL) {
        return  JTextField(8).sizeHint().width();;
    } else {
        return BeanTableDataModel::getPreferredWidth(col);
    }
}

/*public*/ void SignalMastTableDataModel::configureTable(JTable *table)
{
 setColumnToHoldButton(table, EDITMASTCOL);
 setColumnToHoldButton(table, EDITLOGICCOL);
 BeanTableDataModel::configureTable(table);
}

/*public*/ Qt::ItemFlags SignalMastTableDataModel::flags(const QModelIndex &index) const
{
    int col = index.column();
    int row = index.row();
    if (col == LITCOL)
    {
     return  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }
    else if (col == EDITLOGICCOL) {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
    else if (col == EDITMASTCOL)
    {
        QString name = sysNameList.at(row);
        SignalMast* s = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name);
        //if (s instanceof jmri.implementation.TurnoutSignalMast) {
        if(qobject_cast<TurnoutSignalMast*>(s)!= NULL)
        {
         return Qt::ItemIsEditable | Qt::ItemIsEnabled;
        }
        else
        {
         return Qt::ItemIsEditable | Qt::ItemIsEnabled;
        }
    }
    else if (col == HELDCOL) {
        return  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }
    else
    {
     return BeanTableDataModel::flags(index);
    }
}

/*protected*/ Manager* SignalMastTableDataModel::getManager() {
    return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
}

/*protected*/ NamedBean* SignalMastTableDataModel::getBySystemName(QString name)  const
{
 return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name);
}

/*protected*/ NamedBean* SignalMastTableDataModel::getByUserName(QString name) {
    return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getByUserName(name);
}

/*protected*/ QString SignalMastTableDataModel::getMasterClassName() {
    return getClassName();
}

/*protected*/ void SignalMastTableDataModel::clickOn(NamedBean* t) {

}

/*public*/ QVariant SignalMastTableDataModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();
 QString name = sysNameList.at(row);
 SignalMast* s = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name);

 if(role == Qt::CheckStateRole)
 {
  if (col == HELDCOL) {
         bool val = s->getHeld();
         return (val)?Qt::Checked : Qt::Unchecked;
     }
  if (col == LITCOL) {
      bool val = s->getLit();
      return (val)?Qt::Checked : Qt::Unchecked;
  }
 }
 if(role == Qt::DisplayRole)
 {
    // some error checking
    if (row >= sysNameList.size()) {
        log->debug("row is greater than name list");
        return "error";
    }
    if (s == NULL) {
        return (false); // if due to race condition, the device is going away
    }
    else if (col == EDITLOGICCOL) {
        return tr("Edit Signal Logic");
    }
    else if (col == EDITMASTCOL)
    {
        //if (s instanceof jmri.implementation.TurnoutSignalMast) {
        if(qobject_cast<TurnoutSignalMast*>(s) != NULL)
        {
            return tr("Edit");
        }
        return tr("Edit");
    }
 }
 return BeanTableDataModel::data(index, role);
}

/*public*/ bool SignalMastTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 QString name = sysNameList.at(row);
 SignalMast* s = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name);
 if (s == NULL) {
     return false;  // device is going away anyway
 }
 if(role == Qt::EditRole)
 {
  if (col == VALUECOL)
  {
    if ( value.toString() != NULL)
    {
        s->setAspect( value.toString());
        fireTableRowsUpdated(row, row);
        return true;
    }
  }
  else if (col == EDITLOGICCOL)
  {
        editLogic(row, col);
  }
  else if (col == EDITMASTCOL)
  {
   editMast(row, col);
  }
  return true;
 }
 if(role == Qt::CheckStateRole)
 {
  if (col == LITCOL)
  {
   bool b = value.toBool();
   s->setLit(b);
   return true;
  }
  else if (col == HELDCOL)
  {
   bool b = value.toBool();
   s->setHeld(b);
   return true;
  }
 }
 BeanTableDataModel::setData(index, value, role);
}

void SignalMastTableDataModel::editLogic(int row, int col) {
//    class WindowMaker implements Runnable {

//        int row;

//        WindowMaker(int r) {
//            row = r;
//        }

//        /*public*/ void run() {
            SignallingSourceAction* action = new SignallingSourceAction(tr("Signal Mast Logic Table"), (SignalMast*) getBySystemName(sysNameList.at(row)));
            action->actionPerformed(NULL);
//        }
//    }
//    WindowMaker t = new WindowMaker(row);
//    javax.swing.SwingUtilities.invokeLater(t);
}

void SignalMastTableDataModel::editMast(int row, int col) {
//    class WindowMaker implements Runnable {

//        int row;

//        WindowMaker(int r) {
//            row = r;
//        }

//        /*public*/ void run() {
            AddSignalMastJFrame* editFrame = new AddSignalMastJFrame((SignalMast*) getBySystemName(sysNameList.at(row)));
            editFrame->setVisible(true);
//        }
//    }
//    WindowMaker t = new WindowMaker(row);
//    javax.swing.SwingUtilities.invokeLater(t);
}

/*public*/ JTable* SignalMastTableDataModel::makeJTable(QSortFilterProxyModel* srtr) {
    this->sorter = srtr;
    table = new SignalMastJTable(sorter);

    //table->getTableHeader().setReorderingAllowed(true);
    table->setColumnModel(new XTableColumnModel(/*(AbstractTableModel*)sorter->sourceModel()*/table));
    table->createDefaultColumnsFromModel();

    addMouseListenerToHeader(table);
    return table;
}


//The JTable is extended so that we can reset the available aspect in the drop down when required
//class SignalMastJTable extends JTable {

    /**
     *
     */
   // private static final long serialVersionUID = 7888512352829953819L;

    /*public*/ SignalMastJTable::SignalMastJTable(QSortFilterProxyModel* sorter) : JTable(sorter)
    {
        //super(srtr);
    }

    /*public*/ void SignalMastJTable::clearAspectVector(int row) {
        //Clear the old aspect combobox and forces it to be rebuilt
#if 0 // TODO:
        boxMap.remove(sorter.getValueAt(row, SYSNAMECOL));
        editorMap.remove(sorter.getValueAt(row, SYSNAMECOL));
        rendererMap.remove(sorter.getValueAt(row, SYSNAMECOL));
#endif
    }
#if 0
    /*public*/ boolean editCellAt(int row, int column, java.util.EventObject e) {
        boolean res = super.editCellAt(row, column, e);
        java.awt.Component c = this.getEditorComponent();
        if (c instanceof javax.swing.JTextField) {
            ((JTextField) c).selectAll();
        }
        return res;
    }

    /*public*/ TableCellRenderer getCellRenderer(int row, int column) {
        if (column == VALUECOL) {
            return getRenderer(row);
        } else {
            return super.getCellRenderer(row, column);
        }
    }

    /*public*/ TableCellEditor getCellEditor(int row, int column) {
        if (column == VALUECOL) {
            return getEditor(row);
        } else {
            return super.getCellEditor(row, column);
        }
    }

    TableCellRenderer getRenderer(int row) {
        TableCellRenderer retval = rendererMap.get(sorter.getValueAt(row, SYSNAMECOL));
        if (retval == NULL) {
            // create a new one with right aspects
            retval = new MyComboBoxRenderer(getAspectVector(row));
            rendererMap.put(sorter.getValueAt(row, SYSNAMECOL), retval);
        }
        return retval;
    }
    Hashtable<Object, TableCellRenderer> rendererMap = new Hashtable<Object, TableCellRenderer>();

    TableCellEditor getEditor(int row) {
        TableCellEditor retval = editorMap.get(sorter.getValueAt(row, SYSNAMECOL));
        if (retval == NULL) {
            // create a new one with right aspects
            retval = new MyComboBoxEditor(getAspectVector(row));
            editorMap.put(sorter.getValueAt(row, SYSNAMECOL), retval);
        }
        return retval;
    }
    Hashtable<Object, TableCellEditor> editorMap = new Hashtable<Object, TableCellEditor>();

    Vector<String> getAspectVector(int row) {
        Vector<String> retval = boxMap.get(sorter.getValueAt(row, SYSNAMECOL));
        if (retval == NULL) {
            // create a new one with right aspects
            Vector<String> v = InstanceManager.signalMastManagerInstance()
                    .getSignalMast((String) sorter.getValueAt(row, SYSNAMECOL)).getValidAspects();
            retval = v;
            boxMap.put(sorter.getValueAt(row, SYSNAMECOL), retval);
        }
        return retval;
    }

    Hashtable<Object, Vector<String>> boxMap = new Hashtable<Object, Vector<String>>();
}
#endif
/*protected*/ QString SignalMastTableDataModel::getBeanType() {
    return tr("BeanNameSignalMast");
}

/*public*/ void SignalMastTableDataModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName().indexOf("aspectEnabled") >= 0 || e->getPropertyName().indexOf("aspectDisabled") >= 0) {
        //if (e->getSource() instanceof NamedBean) {
        if(qobject_cast<NamedBean*>(e->getSource()) != NULL)
        {
            QString name = ((NamedBean*) e->getSource())->getSystemName();
            if (log->isDebugEnabled()) {
                log->debug("Update cell " + QString::number(sysNameList.indexOf(name)) + ","
                        + QString::number(VALUECOL) + " for " + name);
            }
            // since we can add columns, the entire row is marked as updated
            int row = sysNameList.indexOf(name);
            table->clearAspectVector(row);
        }
    }
    BeanTableDataModel::propertyChange(e);
}

/*protected*/ bool SignalMastTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    if (e->getPropertyName().indexOf("Aspect") >= 0 || e->getPropertyName().indexOf("Lit") >= 0
            || e->getPropertyName().indexOf("Held") >= 0 || e->getPropertyName().indexOf("aspectDisabled") >= 0
            || e->getPropertyName().indexOf("aspectEnabled") >= 0) {

        return true;
    }
    return BeanTableDataModel::matchPropertyName(e);
}

/*protected*/ QString SignalMastTableDataModel::getClassName() {
    return "jmri.jmrit.beantable.SignalMastTableAction";
}

/*public*/ QString SignalMastTableDataModel::getClassDescription() {
    return tr("Signal Mast Table");
}
