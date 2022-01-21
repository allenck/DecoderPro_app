#include "idtagtabledatamodel.h"
#include "loggerfactory.h"
#include "idtagmanager.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "rfid/proxyidtagmanager.h"
/**
 * TableDataModel for an IdTag Table.
 *
 * Split from {@link IdTagTableAction}
 *
 * @author  Bob Jacobsen Copyright (C) 2003
 * @author  Matthew Harris Copyright (C) 2011
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class IdTagTableDataModel extends BeanTableDataModel<IdTag> {

    /**
     * Create a new IdTag Table Data Model.
     * @param mgr IdTag manager to use in the model, default IdTag Manager always used.
     */
    /*public*/ IdTagTableDataModel::IdTagTableDataModel(Manager/*<IdTag>*/* mgr, QObject* parent) : BeanTableDataModel(parent){
        //super();
        setManager(mgr);
        setObjectName(QString("IdTagTableDataModel") + "_" + mgr->self()->metaObject()->className());
        init();
    }

    //@Override
    /*protected*/ /*final*/ void IdTagTableDataModel::setManager(/*Manager<IdTag>*/Manager* mgr){
        if ( static_cast<IdTagManager*>(mgr)){
            tagManager = (IdTagManager*)mgr;
        }
    }

    //@Override
    /*public*/ QString IdTagTableDataModel::getValue(QString name) {
        IdTag* tag = (IdTag*)getManager()->getBySystemName(name);
        if (tag == nullptr) {
            return "?";
        }
        return tag->getTagID();
    }

    //@Override
    /*public*/ /*Manager<IdTag>*/Manager* IdTagTableDataModel::getManager() {
        return  tagManager != nullptr ? tagManager : (ProxyIdTagManager*)InstanceManager::getDefault("IdTagManager");
    }

    //@Override
    /*public*/ NamedBean* IdTagTableDataModel::getBySystemName(/*@Nonnull*/ QString name)  const{
     return ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getBySystemName(name);
    }

    //@Override
    /*public*/ NamedBean* IdTagTableDataModel::getByUserName(/*@Nonnull */QString name) {
        return getManager()->getByUserName(name);
    }

    //@Override
    /*public*/ void IdTagTableDataModel::clickOn(NamedBean* t) {
        // don't do anything on click; not used in this class, because
        // we override setValueAt
    }

    //@Override
    ///*public*/ void setValueAt(Object value, int row, int col)
    /*public*/ bool IdTagTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     if(role == Qt::EditRole)
     {
      int col = index.column();
      int row = index.row();
      if (col == CLEARCOL) {
          NamedBean* t = getBySystemName(sysNameList.at(row));
          log->debug(tr("Clear where & when last seen for %1").arg(t->getSystemName()));
          ((IdTag*)t)->setWhereLastSeen(nullptr);
          fireTableRowsUpdated(row, row);
      }
      BeanTableDataModel::setData(index,value, role);
     }
    }

    //@Override
    /*public*/ int IdTagTableDataModel::columnCount(const QModelIndex &parent) const {
        return CLEARCOL + 1;
    }

    //@Override
    /*public*/ QString IdTagTableDataModel::getColumnName(int col) const{
        switch (col) {
            case VALUECOL:
                return tr("Tag ID");
            case WHERECOL:
                return tr("Where seen");
            case WHENCOL:
                return tr("When seen");
            case CLEARCOL:
                return "";
            default:
                return BeanTableDataModel::getColumnName(col);
        }
    }

    //@Override
    /*public*/ QString IdTagTableDataModel::getColumnClass(int col) const {
        switch (col) {
            case VALUECOL:
            case WHERECOL:
            case WHENCOL:
                return "String";
            case CLEARCOL:
                return "JButton";
            default:
                return BeanTableDataModel::getColumnClass(col);
        }
    }

    //@Override
    /*public*/ bool IdTagTableDataModel::isCellEditable(int row, int col) const{
        switch (col) {
            case VALUECOL:
            case WHERECOL:
            case WHENCOL:
                return false;
            case CLEARCOL:
                return true;
            default:
                return BeanTableDataModel::isCellEditable(row, col);
        }
    }

    //@Override
    ///*public*/ Object getValueAt(int row, int col)
    /*public*/ QVariant IdTagTableDataModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
      int col = index.column();
      int row = index.row();

        NamedBean* t;
        switch (col) {
            case WHERECOL:
                Reporter* r;
                t = getBySystemName(sysNameList.at(row));
                if ( t !=nullptr ){
                    r = ((IdTag*)t)->getWhereLastSeen();
                    if (r!=nullptr){
                        return r->getDisplayName();
                    }
                }
                return QVariant();
            case WHENCOL:
        {
             QDateTime d;
             t = (DefaultIdTag*) getBySystemName(sysNameList.at(row));
             return (t != NULL) ? (((d = ((IdTag*)t)->getWhenLastSeen()) != QDateTime())
                     ? /*DateFormat.getDateTimeInstance(DateFormat.SHORT*/ QDateTime::currentDateTime().toString(), /*DateFormat.MEDIUM).format(d)*/d.toString() : QVariant()) : QVariant();
        }
            case CLEARCOL:
                return tr("Clear");
            default:
         break;
        }
                //return super.getValueAt(row, col);
        BeanTableDataModel::data(index, role);
        }
    }

    //@Override
    /*public*/ int IdTagTableDataModel::getPreferredWidth(int col) {
        switch (col) {
            case SYSNAMECOL:
            case WHERECOL:
            case WHENCOL:
                return  JTextField(12).getPreferredSize().width();
            case VALUECOL:
                return  JTextField(10).getPreferredSize().width();
            case CLEARCOL:
                return  JButton(tr("Clear")).sizeHint().width() + 4;
            default:
                return BeanTableDataModel::getPreferredWidth(col);
        }
    }

    //@Override
    /*public*/ void IdTagTableDataModel::configValueColumn(JTable* table) {
        // value column isn't button, so config is null
    }

    //@Override
    /*protected*/ bool IdTagTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
        return true;
        // return (e.getPropertyName().indexOf("alue")>=0);
    }

    //@Override
    /*public*/ QPushButton* IdTagTableDataModel::configureButton() {
        log->error("configureButton should not have been called");
        return nullptr;
    }

    //@Override
    /*protected*/ QString IdTagTableDataModel::getMasterClassName() {
       // return IdTagTableAction.class.getName();
     return  "jmri.jmrit.beantable.IdTagTableAction";
    }

    /*private*/ /*static*/ /*final*/ Logger* IdTagTableDataModel::log = LoggerFactory::getLogger("IdTagTableDataModel");
