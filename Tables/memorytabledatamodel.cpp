#include "memorytabledatamodel.h"
#include "loggerfactory.h"
#include "memorymanager.h"
#include "instancemanager.h"
#include "vptr.h"
#include "reportable.h"

/**
 * TableDataModel for the Memory Table.
 *
 * Split from {@link MemoryTableAction}
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class MemoryTableDataModel : public BeanTableDataModel/*<Memory>*/ {

    /**
     * Create a new Memory Table Data Model.
     * @param mgr Memory manager to use in the model, default MemoryManager always used.
//     */
    /*public*/ MemoryTableDataModel::MemoryTableDataModel(Manager/*<Memory>*/* mgr, QObject *parent) : BeanTableDataModel(parent){
//        super();
        setManager((AbstractManager*)mgr->mself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString MemoryTableDataModel::getValue(QString name) {
        Memory* mem = ((MemoryManager*)InstanceManager::getDefault("MemoryManager"))->getBySystemName(name);
        if (mem == nullptr) {
            return "?";
        }
        QVariant m = mem->getValue();
        if (m != QVariant()) {
            if (VPtr<Reportable>::asPtr(m)) {
                return VPtr<Reportable>::asPtr(m)->toReportString();
            }
            else {
                return m.toString();
            }
        } else {
            return "";
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*Manager<Memory>*/AbstractManager* MemoryTableDataModel::getManager() {
        return (AbstractManager*)InstanceManager::getDefault("MemoryManager");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* MemoryTableDataModel::getBySystemName(/*@Nonnull*/ QString name) const{
        return ((MemoryManager*)InstanceManager::getDefault("MemoryManager"))->getBySystemName(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* MemoryTableDataModel::getByUserName(/*@Nonnull*/ QString name) {
        return ((MemoryManager*)InstanceManager::getDefault("MemoryManager"))->getByUserName(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*protected*/ QString MemoryTableDataModel::getMasterClassName() {
     return "jmri.jmrit.beantable.MemoryTableAction";

    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void MemoryTableDataModel::clickOn(NamedBean* /*t*/) {
        // don't do anything on click; not used in this class, because
        // we override setValueAt
    }

    /** {@inheritDoc} */
    //@Override
//    /*public*/ void setValueAt(Object value, int row, int col) {
    /*public*/ bool MemoryTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     int col = index.column();
     int row = index.row();
     if(role == Qt::EditRole)
     {
        if (col == VALUECOL) {
            ((Memory*)getBySystemName(sysNameList.at(row))->self())->setValue(value);
            fireTableRowsUpdated(row, row);
        } else {
            //super.setValueAt(value, row, col);
        }
      BeanTableDataModel::setData(index, value, role);
     }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString MemoryTableDataModel::getColumnName(int col) const {
        if (col == VALUECOL) {
            return tr("Value");
        }
        return BeanTableDataModel::getColumnName(col);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString MemoryTableDataModel::getColumnClass(int col) const {
        if (col == VALUECOL) {
            return "String";
        } else {
            return BeanTableDataModel::getColumnClass(col);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void MemoryTableDataModel::configValueColumn(JTable* /*table*/) {
        // value column isn't button, so config is null
    }

    /** {@inheritDoc} */
    //@Override
    /*protected*/ bool MemoryTableDataModel::matchPropertyName(PropertyChangeEvent* /*e*/) {
        return true;
        // return (e.getPropertyName().indexOf("alue")>=0);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QPushButton* MemoryTableDataModel::configureButton() {
        log->error("configureButton should not have been called");
        return nullptr;
    }

    /*private*/ /*static*/ /*final*/ Logger* MemoryTableDataModel::log = LoggerFactory::getLogger("MemoryTableDataModel");
