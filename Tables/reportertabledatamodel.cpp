#include "reportertabledatamodel.h"
#include "loggerfactory.h"
#include "vptr.h"
#include "instancemanager.h"

/**
 * Data model for a Reporter Table.
 * Code originally within ReporterTableAction.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class ReporterTableDataModel extends BeanTableDataModel<Reporter> {

    /*public*/ /*static*/ /*final*/ const int ReporterTableDataModel::LASTREPORTCOL = NUMCOLUMN;

    /*public*/ ReporterTableDataModel::ReporterTableDataModel(/*Manager<Reporter>*/AbstractManager* mgr, QObject* parent) : BeanTableDataModel(parent){
        //super();
        setManager(mgr);
    }


    /**
     * {@inheritDoc}
     */
    //@Override
    //@CheckForNull
    /*public*/ QString ReporterTableDataModel::getValue(QString name) {
        QVariant value;
        Reporter* r = (Reporter*)getManager()->getBySystemName(name);
        if (r == nullptr) {
            return "";
        }
        value = r->getCurrentReport();
        if (value == QVariant()) {
            return "";
        } else if (VPtr<Reportable>::asPtr(value)) {
            return VPtr<Reportable>::asPtr(value)->toReportString();
        } else {
            return value.toString();
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ /*final*/ void ReporterTableDataModel::setManager(/*Manager<Reporter>*/Manager *rm) {
        if (!(qobject_cast<ReporterManager*>(rm->self()))) {
            return;
        }
        getManager()->removePropertyChangeListener(this);
        if (!sysNameList.isEmpty()) {
            for (int i = 0; i < sysNameList.size(); i++) {
                // if object has been deleted, it's not here; ignore it
                NamedBean* b = getBySystemName(sysNameList.at(i));
                if (b != nullptr) {
                    b->removePropertyChangeListener(this);
                }
            }
        }
        reporterManager = (ReporterManager*) rm;
        getManager()->addPropertyChangeListener(this);
        updateNameList();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Manager *ReporterTableDataModel::getManager() {
        return ( reporterManager == nullptr ? (ProxyReporterManager*)InstanceManager::getDefault("ReporterManager"): reporterManager);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ NamedBean* ReporterTableDataModel::getBySystemName(/*@Nonnull*/ QString name) const{
        return ((ProxyReporterManager*)reporterManager)->AbstractProxyManager::getBySystemName(name);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Reporter* ReporterTableDataModel::getByUserName(/*@Nonnull*/ QString name) {
        return (Reporter*)((ProxyReporterManager*)getManager()->self())->AbstractProxyManager::getByUserName(name);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ QString ReporterTableDataModel::getMasterClassName() {
        return "jmri.jmrit.beantable.ReporterTableAction";
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void ReporterTableDataModel::clickOn(NamedBean* t) {
        // don't do anything on click; not used in this class, because
        // we override setValueAt
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    // /*public*/ void setValueAt(Object value, int row, int col)
    /*public*/ bool ReporterTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     if(role == Qt::EditRole)
     {
      int col = index.column();
      int row = index.row();
        switch (col) {
            case VALUECOL:
                ((Reporter*)getBySystemName(sysNameList.at(row)))->setReport(value);
                fireTableRowsUpdated(row, row);
                break;
            case LASTREPORTCOL: // do nothing
                break;
            default:
         break;
        }
      }
      BeanTableDataModel::setData(index, value, role);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    // /*public*/ int getColumnCount() {
    /*public*/ int ReporterTableDataModel::columnCount(const QModelIndex& /*index*/) const
    {
        return LASTREPORTCOL + getPropertyColumnCount() +1;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QVariant ReporterTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     int col = section;
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        if (col == VALUECOL) {
            return tr("Report");
        }
        if (col == LASTREPORTCOL) {
            return tr("Last Report");
        }
      }
    }


    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ReporterTableDataModel::getColumnClass(int col) const
    {
        switch (col) {
            case VALUECOL:
            case LASTREPORTCOL:
                return "String";
            default:
                return BeanTableDataModel::getColumnClass(col);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Qt::ItemFlags ReporterTableDataModel::flags(const QModelIndex &index) const
    {
     int col = index.column();
        if (col == LASTREPORTCOL) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        return BeanTableDataModel::flags(index);
    }


    /**
     * {@inheritDoc}
     */
    //@Override
   /*public*/ QVariant ReporterTableDataModel::data(const QModelIndex &index, int role) const
   {
    if(role == Qt::DisplayRole)
    {
     int col = index.column();
     int row = index.row();
       if (col == LASTREPORTCOL) {
           Reporter* t = (Reporter*) getBySystemName(sysNameList.at(row));
           return t->getLastReport();
       }
    }
       return BeanTableDataModel::data(index, role);
   }


    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ int ReporterTableDataModel::getPreferredWidth(int col) {
        if (col == LASTREPORTCOL) {
            return BeanTableDataModel::getPreferredWidth(VALUECOL);
        } else
        return BeanTableDataModel::getPreferredWidth(col);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void ReporterTableDataModel::configValueColumn(JTable* /*table*/) {
        // value column isn't button, so config is null
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ bool ReporterTableDataModel::matchPropertyName(PropertyChangeEvent* /*e*/) {
        return true;
        // return (e.getPropertyName().indexOf("Report")>=0);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QPushButton* ReporterTableDataModel::configureButton() {
        log->error("configureButton should not have been called");
        return nullptr;
    }

    /*private*/ /*final*/ /*static*/ Logger* ReporterTableDataModel::log = LoggerFactory::getLogger("ReporterTableDataModel");
