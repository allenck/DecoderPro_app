#include "rostertablemodel.h"
#include "roster.h"
#include "rosterentry.h"
#include "rostergroupselector.h"
#include "xtablecolumnmodel.h"
#include "rostericonfactory.h"
#include <QLabel>
#include "imageicon.h"
#include "logger.h"
#include "vptr.h"
#include "QImage"

//RosterTableModel::RosterTableModel()
//{

//}
/**
 * Table data model for display of Roster variable values.
 * <P>
 * Any desired ordering, etc, is handled outside this class.
 * <P>
 * The initial implementation doesn't automatically update when roster entries
 * change, doesn't allow updating of the entries, and only shows some of the
 * fields. But it's a start....
 *
 * @author Bob Jacobsen Copyright (C) 2009, 2010
 * @since 2.7.5
 */
// /*public*/ class RosterTableModel extends DefaultTableModel implements PropertyChangeListener {


/*public*/ RosterTableModel::RosterTableModel(QObject* parent)
 : DefaultTableModel( parent)
{
 common();

 //this(false);
 this->editable = false;
}

 /*public*/ RosterTableModel::RosterTableModel(bool editable, QObject* parent)
 : DefaultTableModel(parent)
{
 common();

 this->editable = editable;
 //Roster.instance().addPropertyChangeListener(this);
 connect(Roster::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*) ));
}

void RosterTableModel::common()
{
 NUMCOL = PROTOCOL + 1;
 rosterGroup = "";
 editable = false;
 _tcm = NULL;
 iconFactory = NULL;
 log = new Logger("RosterTableModel");
}

//@Override
 /*public*/ void RosterTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == (Roster::ADD)) {
        fireTableDataChanged();
    }
    else if (e->getPropertyName() == (Roster::REMOVE))
    {
        fireTableDataChanged();
    }
    else if (e->getPropertyName() == (Roster::SAVED))
    {
        //TODO This really needs to do something like find the index of the roster entry here
        //if (e.getSource() instanceof RosterEntry)
     if(qobject_cast<RosterEntry*>(e->getSource()) != NULL)
        {
            int row = Roster::instance()->getGroupIndex(rosterGroup, (RosterEntry*) e->getSource());
            fireTableRowsUpdated(row, row);
        } else {
            fireTableDataChanged();
        }
    }
    else if (e->getPropertyName() == (RosterGroupSelector::SELECTED_ROSTER_GROUP)) {
        setRosterGroup((e->getNewValue() != QVariant()) ? e->getNewValue().toString() : "");
    }
    else if (e->getPropertyName().startsWith("attribute") && qobject_cast<RosterEntry*>(e->getSource() ))
    { // NOI18N
        int row = Roster::instance()->getGroupIndex(rosterGroup, (RosterEntry*) e->getSource());
        fireTableRowsUpdated(row, row);
    } else if (e->getPropertyName() == (Roster::ROSTER_GROUP_ADDED) && e->getNewValue().toString() == (rosterGroup)) {
        fireTableDataChanged();
    }
}

//@Override
 /*public*/ int RosterTableModel::rowCount(const QModelIndex &parent) const
{
    return Roster::instance()->numGroupEntries(rosterGroup);
}

//@Override
 /*public*/ void RosterTableModel::addColumn(QVariant c) {
    NUMCOL++;
    DefaultTableModel::addColumn(c); // not yet inplemented in DefaultTableModel
}

//@Override
 /*public*/ int RosterTableModel::columnCount(const QModelIndex &parent) const {
    return NUMCOL;
}

//The table columnModel is added to here to assist with getting the details of user generated roster attributes.
 /*public*/ void RosterTableModel::setColumnModel(XTableColumnModel* tcm) {
    _tcm = tcm;
}

//@Override
 /*public*/ QVariant RosterTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case IDCOL:
            return tr("ID");
        case ADDRESSCOL:
            return tr("DCC Address");
        case DECODERCOL:
            return tr("Decoder Model");
        case MODELCOL:
            return tr("Model");
        case ROADNAMECOL:
            return tr("Road Name");
        case ROADNUMBERCOL:
            return tr("Road Number");
        case MFGCOL:
            return tr("Manufacturer");
        case ICONCOL:
            return tr("Icon");
        case OWNERCOL:
            return tr("Owner");
        case DATEUPDATECOL:
            return tr("Date Updated");
        case PROTOCOL:
            return tr("Protocol");
        default:
            break;
    }
    if (_tcm != NULL) {
        TableColumn* tc = _tcm->getColumnByModelIndex(section);
        if (tc != NULL) {
            return tc->getHeaderValue().toString();
        }
    }
    return "<UNKNOWN>"; // NOI18N
 }
 return QVariant();
}

//@Override
// /*public*/ Class<?> getColumnClass(int col) {
//    if (col == ADDRESSCOL) {
//        return Integer.class;
//    }
//    if (col == ICONCOL) {
//        return ImageIcon.class;
//    }
//    return String.class;
//}

/**
 * Editable state must be set in ctor.
 */
//@Override
 /*public*/ Qt::ItemFlags RosterTableModel::flags(const QModelIndex &index) const
{
 int col = index.column();
 int row = index.row();

    if (col == ADDRESSCOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (col == PROTOCOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (col == DECODERCOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (col == ICONCOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (col == DATEUPDATECOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (editable) {
        RosterEntry* re = Roster::instance()->getGroupEntry(rosterGroup, row);
        if (re != NULL)
        {
            //return (!re->isOpen());
         if(!re->isOpen())
          return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
          else
          return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;

        }
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

ImageIcon* RosterTableModel::getIcon(RosterEntry* re)
{
    // defer image handling to RosterIconFactory
    if (iconFactory == NULL)
    {
     iconFactory = new RosterIconFactory(qMax(19,  QLabel(getColumnName(0)).sizeHint().height()));
    }
    return iconFactory->getIcon(re);
}

/**
 * Provides the empty String if attribute doesn't exist.
 */
//@Override
/*public*/ QVariant RosterTableModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();
 if(role == Qt::DisplayRole)
 {
    // get roster entry for row
    RosterEntry* re = Roster::instance()->getGroupEntry(rosterGroup, row);
    if (re == NULL) {
        log->debug("roster entry is NULL!");
        return QVariant();
    }
    switch (col) {
        case IDCOL:
            return re->getId();
        case ADDRESSCOL:
            return re->getDccLocoAddress()->getNumber();
        case DECODERCOL:
            return re->getDecoderModel();
        case MODELCOL:
            return re->getModel();
        case ROADNAMECOL:
            return re->getRoadName();
        case ROADNUMBERCOL:
            return re->getRoadNumber();
        case MFGCOL:
            return re->getMfg();
        case ICONCOL:
            return  row;
    case OWNERCOL:
            return re->getOwner();
        case DATEUPDATECOL:
            return re->getDateUpdated();
        case PROTOCOL:
            return re->getProtocolAsString();
        default:
            break;
    }
    QString value = re->getAttribute(getColumnName(col).replace("\\s", "")); // NOI18N
    if (value != NULL) {
        return value;
    }
    return "";
 }
 return QVariant();
}

//@Override
 /*public*/ bool RosterTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 if(role == Qt::EditRole)
 {
    // get roster entry for row
    RosterEntry* re = Roster::instance()->getGroupEntry(rosterGroup, row);
    if (re == NULL) {
        log->warn("roster entry is NULL!");
        return false;
    }
    if (re->isOpen()) {
        log->warn("Entry is already open");
        return false;
    }
    QString valueToSet =  value.toString();
    switch (col) {
        case IDCOL:
            if (re->getId() == (valueToSet)) {
                return false;
            }
            re->setId(valueToSet);
            break;
        case ROADNAMECOL:
            if (re->getRoadName() == (valueToSet)) {
                return false;
            }
            re->setRoadName(valueToSet);
            break;
        case ROADNUMBERCOL:
            if (re->getRoadNumber() == (valueToSet)) {
                return false;
            }
            re->setRoadNumber(valueToSet);
            break;
        case MFGCOL:
            if (re->getMfg() == (valueToSet)) {
                return false;
            }
            re->setMfg(valueToSet);
            break;
        case MODELCOL:
            if (re->getModel() == (valueToSet)) {
                return false;
            }
            re->setModel(valueToSet);
            break;
        case OWNERCOL:
            if (re->getOwner() == (valueToSet)) {
                return false;
            }
            re->setOwner(valueToSet);
            break;
        default:
            QString attributeName = (getColumnName(col)).replace("\\s", "");
            if (re->getAttribute(attributeName) != NULL && re->getAttribute(attributeName) == (valueToSet)) {
                return false;
            }
            if ((valueToSet == NULL) || valueToSet.isEmpty()) {
                re->deleteAttribute(attributeName);
            } else {
                re->putAttribute(attributeName, valueToSet);
            }
            break;
    }
    // need to mark as updated
    re->changeDateUpdated();
    re->updateFile();
    return true;
 }
 return false;
}

 /*public*/ int RosterTableModel::getPreferredWidth(int column) {
    int retval = 20; // always take some width
    retval = qMax(retval,  QLabel(getColumnName(column)).sizeHint().width() + 15);  // leave room for sorter arrow
    for (int row = 0; row < getRowCount(); row++)
    {
#if 0
        if (getColumnClass(column) == (String.class)) {
            retval = qMax(retval, QLabel(getValueAt(row, column).toString()).sizeHint().width());
        } else if (getColumnClass(column) == (Integer.class)) {
            retval = qMax(retval, QLabel(getValueAt(row, column).toString()).sizeHint().width());
        } else if (getColumnClass(column) == (ImageIcon.class)) {
            retval = qMax(retval, QLabel((Icon) getValueAt(row, column)).sizeHint().width());
        }
#endif
    }
    return retval + 5;
}

 /*public*/ /*final*/ void RosterTableModel::setRosterGroup(QString rosterGroup)
{
    foreach (RosterEntry*re, Roster::instance()->getEntriesInGroup(rosterGroup))
    {
        //re->removePropertyChangeListener(this);
     disconnect(re, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    this->rosterGroup = rosterGroup;
    foreach (RosterEntry* re, Roster::instance()->getEntriesInGroup(rosterGroup))
    {
        //re->addPropertyChangeListener(this);
     connect(re, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    fireTableDataChanged();
}

 /*public*/ /*final*/ QString RosterTableModel::getRosterGroup() {
    return this->rosterGroup;
}

// drop listeners
 /*public*/ void RosterTableModel::dispose() {
}
//    private final static Logger log = LoggerFactory.getLogger(RosterTableModel.class.getName());
//}
