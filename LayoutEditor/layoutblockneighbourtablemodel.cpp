#include "layoutblockneighbourtablemodel.h"
#include "layoutblock.h"
#include "instancemanager.h"
#include "path.h"

//LayoutBlockNeighbourTableModel::LayoutBlockNeighbourTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
/**
 * Table data model for display of Neighbouring layout blocks.
 * <P>
 * Any desired ordering, etc, is handled outside this class.
 *
 * @author Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 28746 $
 */
///*private*/ class LayoutBlockNeighbourTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = -4104722631566472444L;

//static final ResourceBundle rb = ResourceBundle.getBundle("jmrit.display.layoutEditor.LayoutEditorBundle");



/*static*/ /*final*/ int LayoutBlockNeighbourTableModel::NUMCOL = 4 + 1;


/*private*/ LayoutBlockNeighbourTableModel::LayoutBlockNeighbourTableModel(bool editable, LayoutBlock* lBlock, QObject *parent) :
  AbstractTableModel(parent)
{
 log = new Logger("LayoutBlockNeighbourTableModel");
 this->editable = editable;
 this->lBlock = lBlock;
 lBlock->addPropertyChangeListener((PropertyChangeListener*)this);
 //connect(this->lBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*private*/ int LayoutBlockNeighbourTableModel::rowCount(const QModelIndex &/*parent*/) const
{
return lBlock->getNumberOfNeighbours();
}

/*private*/ int LayoutBlockNeighbourTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return NUMCOL;
}

//@Override
/*private*/ QVariant LayoutBlockNeighbourTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
   case NEIGHBOURCOL:
       return tr("Neighbour");
   case DIRECTIONCOL:
       return tr("Direction");
   case MUTUALCOL:
       return tr("Mutual");
   case RELATCOL:
       return tr("Traffic Flow");
   case METRICCOL:
       return tr("Metric");

   default:
       return "<UNKNOWN>";
  }
 }
 return QVariant();
}

//@Override
/*private*/ QString LayoutBlockNeighbourTableModel::getColumnClass(int col) {
    if (col == METRICCOL) {
        return "Integer";
    } else {
        return "String";
    }
}

/**
 * Editable state must be set in ctor.
 */
//@Override
/*private*/ Qt::ItemFlags LayoutBlockNeighbourTableModel::flags(const QModelIndex &/*index*/) const
{
 if(editable)
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*private*/ void LayoutBlockNeighbourTableModel::propertyChange(PropertyChangeEvent* e) {
 if (e->getPropertyName()==("length"))
 {
  // a new NamedBean is available in the manager
  //updateNameList();
  //log->debug("Table changed length to "+sysNameList.size());
  fireTableDataChanged();
 }
 else if (matchPropertyName(e))
 {
  // a value changed.  Find it, to avoid complete redraw
  int row;
  row = e->getNewValue().toInt();
  // since we can add columns, the entire row is marked as updated
  //int row = sysNameList.indexOf(name);
  fireTableRowsUpdated(row, row);
 }
}

/*protected*/ bool LayoutBlockNeighbourTableModel::matchPropertyName(PropertyChangeEvent* e)
{
 return (e->getPropertyName().indexOf("neighbourmetric") >= 0 || e->getPropertyName().indexOf("neighbourpacketflow") >= 0);
}

/**
 * Provides the empty String if attribute doesn't exist.
 */
/*private*/ QVariant LayoutBlockNeighbourTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int col = index.column();
  int row = index.row();

  // get roster entry for row
  if (lBlock == NULL) {
      log->debug("layout Block is NULL!");
      return "Error";
  }
  switch (col)
  {
   case NEIGHBOURCOL:
           return lBlock->getNeighbourAtIndex(row)->getDisplayName();
   case MUTUALCOL:
   {
    bool mutual = lBlock->isNeighbourMutual(row);
    if (mutual)
    {
     return tr("Yes");
    }
    return tr("No");
   }
   case DIRECTIONCOL:
   {
    return Path::decodeDirection(lBlock->getNeighbourDirection(row));
   }
   case METRICCOL:
   {
    return lBlock->getNeighbourMetric(row);
   }
   case RELATCOL:
   {
   return lBlock->getNeighbourPacketFlowAsString(row);
   }
   default:
   {
   return "<UNKNOWN>";
   }
  }
 }
 return QVariant();
}

//@Override
/*private*/ bool LayoutBlockNeighbourTableModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/) {
    return false;
}

/*private*/ int LayoutBlockNeighbourTableModel::getPreferredWidth(int /*column*/) {
    int retval = 20; // always take some width
//    retval = qMax(retval, new JLabel(getColumnName(column)).getPreferredSize().width + 15);  // leave room for sorter arrow
//    for (int row = 0; row < getRowCount(); row++) {
//        if (getColumnClass(column)==(String.class)) {
//            retval = qMax(retval, new javax.swing.JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        } else if (getColumnClass(column)==(Integer.class)) {
//            retval = qMax(retval, new javax.swing.JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        }
//    }
    return retval + 5;
}

// drop listeners
/*private*/ void LayoutBlockNeighbourTableModel::dispose() {
}

/*private*/ Manager* LayoutBlockNeighbourTableModel::getManager()
{
 return (Manager*)InstanceManager::getDefault("LayoutBlockManager");
}

