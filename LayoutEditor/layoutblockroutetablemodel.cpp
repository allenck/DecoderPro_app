#include "layoutblockroutetablemodel.h"
#include "layoutblock.h"
#include "instancemanager.h"

//LayoutBlockRouteTableModel::LayoutBlockRouteTableModel(QObject *parent) :
//  AbstractTableModel(parent)
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
 * @version $Revision: 28746 $
 * @since 2.7.5
 */
///*public*/ class LayoutBlockRouteTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = -2084837727852885212L;

//static final ResourceBundle rb = ResourceBundle.getBundle("jmrit.display.layoutEditor.LayoutEditorBundle");


/*static*/ /*final*/ int LayoutBlockRouteTableModel::NUMCOL = 7 + 1;


/*public*/LayoutBlockRouteTableModel:: LayoutBlockRouteTableModel(bool editable, LayoutBlock* lBlock,QObject *parent) :
    AbstractTableModel(parent)
{
 log = new Logger("LayoutBlockRouteTableModel");
    this->editable = editable;
    this->lBlock = lBlock;
    //lBlock.addPropertyChangeListener(this);
 connect(this->lBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ int LayoutBlockRouteTableModel::rowCount(const QModelIndex &/*parent*/) const{
    return lBlock->getNumberOfRoutes();
}

/*public*/ int LayoutBlockRouteTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return NUMCOL;
}

//@Override
/*public*/ QVariant LayoutBlockRouteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
   case DESTCOL:
       return tr("Destination");
   case NEXTHOPCOL:
       return tr("Next Hop");
   case HOPCOUNTCOL:
       return tr("Hop Count");
   case DIRECTIONCOL:
       return tr("Direction");
   case METRICCOL:
       return tr("Metric");
   case LENGTHCOL:
       return tr("Length");
   case STATECOL:
       return tr("State");
   case VALIDCOL:
       return tr("Valid");

   default:
       return "<UNKNOWN>";
  }
 }
 return QVariant();
}

//@Override
///*public*/ Class<?> getColumnClass(int col) {
//    if (col == HOPCOUNTCOL) {
//        return Integer.class;
//    } else if (col == METRICCOL) {
//        return Integer.class;
//    } else if (col == LENGTHCOL) {
//        return Float.class;
//    } else {
//        return String.class;
//    }
//}

/**
 * Editable state must be set in ctor.
 */
//@Override
/*public*/ Qt::ItemFlags  LayoutBlockRouteTableModel::flags(const QModelIndex &/*index*/) const
{
 if(editable)
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ void LayoutBlockRouteTableModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  fireTableDataChanged();
 } else if (e->getPropertyName()==("routing"))
 {
  fireTableDataChanged();
 }
 else if (matchPropertyName(e))
 {
  // a value changed.  Find it, to avoid complete redraw
  int row =  e->getNewValue().toInt();
  // since we can add columns, the entire row is marked as updated
  fireTableRowsUpdated(row, row);
 }
}

/*protected*/ bool LayoutBlockRouteTableModel::matchPropertyName(PropertyChangeEvent* e)
{
 return (e->getPropertyName().indexOf("state") >= 0 || e->getPropertyName().indexOf("hop") >= 0
            || e->getPropertyName().indexOf("metric") >= 0 || e->getPropertyName().indexOf("valid") >= 0
            || e->getPropertyName().indexOf("neighbourmetric") >= 0);
}

/**
 * Provides the empty String if attribute doesn't exist.
 */
/*public*/ QVariant LayoutBlockRouteTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  // get roster entry for row
  if (lBlock == NULL)
  {
   log->debug("layout Block is NULL!");
   return "Error";
  }
  switch (col)
  {
   case DESTCOL:
    return lBlock->getRouteDestBlockAtIndex(row)->getDisplayName();
   case NEXTHOPCOL:
   {
    QString nextBlock = lBlock->getRouteNextBlockAtIndex(row)->getDisplayName();
    if (nextBlock==(lBlock->getDisplayName()))
    {
     nextBlock = tr("DirectConnect");
    }
    return nextBlock;
   }
   case HOPCOUNTCOL:
   {
    return (lBlock->getRouteHopCountAtIndex(row));
   }
   case DIRECTIONCOL:
   {
    return Path::decodeDirection((lBlock->getRouteDirectionAtIndex(row)));
   }
   case METRICCOL:
   {
    return (lBlock->getRouteMetric(row));
   }
   case LENGTHCOL:
   {
    return (lBlock->getRouteLengthAtIndex(row));
   }
   case STATECOL:
   {
    return lBlock->getRouteStateAsString(row);
   }
   case VALIDCOL:
   {
    QString value = "";
    if (lBlock->getRouteValid(row))
    {
     value = "*";
    }
    return value;
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
/*public*/ bool LayoutBlockRouteTableModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
 return false;
}

/*public*/ int LayoutBlockRouteTableModel::getPreferredWidth(int column)
{
 int retval = 20; // always take some width
 retval = qMax(retval,  JLabel(getColumnName(column)).sizeHint().width() + 15);  // leave room for sorter arrow
 for (int row = 0; row < rowCount(QModelIndex()); row++) {
//        if (getColumnClass(column)==(String.class)) {
//            retval = Math.max(retval, new javax.swing.JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        } else if (getColumnClass(column)==(Integer.class)) {
//            retval = Math.max(retval, new javax.swing.JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        }
 }
 return retval + 5;
}

// drop listeners
/*public*/ void LayoutBlockRouteTableModel::dispose() {}

/*public*/ Manager* LayoutBlockRouteTableModel::getManager()
{
 return (Manager*)InstanceManager::getDefault("LayoutBlockManager");
}

