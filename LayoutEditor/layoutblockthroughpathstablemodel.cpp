#include "layoutblockthroughpathstablemodel.h"
#include "manager.h"
#include "instancemanager.h"
#include "layoutblock.h"

//LayoutBlockThroughPathsTableModel::LayoutBlockThroughPathsTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
/**
 * Table data model for display the through path of a layoutblock
 * <P>
 * Any desired ordering, etc, is handled outside this class.
 *
 * @author Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 28746 $
 */
///*public*/ class LayoutBlockThroughPathsTableModel extends table.AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 4544331372118349150L;

//static final ResourceBundle rb = ResourceBundle.getBundle("jmrit.display.layoutEditor.LayoutEditorBundle");


/*static*/ /*final*/ int LayoutBlockThroughPathsTableModel::NUMCOL = 2 + 1;

LayoutBlockThroughPathsTableModel::
/*public*/ LayoutBlockThroughPathsTableModel(bool editable, LayoutBlock* lBlock, QObject *parent) :
    AbstractTableModel(parent)
{
 log = new Logger("LayoutBlockThroughPathsTableModel");
 this->editable = editable;
 this->lBlock = lBlock;
 lBlock->addPropertyChangeListener((PropertyChangeListener*)this);
 //connect(lBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ int LayoutBlockThroughPathsTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return lBlock->getNumberOfThroughPaths();
}

/*public*/ int LayoutBlockThroughPathsTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return NUMCOL;
}

//@Override
/*public*/ QVariant LayoutBlockThroughPathsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
   case SOURCECOL:
       return tr("Source");
   case DESTINATIONCOL:
       return tr("Destination");
   case ACTIVECOL:
       return tr("Active");

   default:
       return "<UNKNOWN>";
  }
 }
 return QVariant();
}

//@Override
///*public*/ Class<?> getColumnClass(int col) {
//    return String.class;
//}

/**
 * Editable state must be set in ctor.
 */
//@Override
/*public*/ Qt::ItemFlags LayoutBlockThroughPathsTableModel::flags(const QModelIndex &/*index*/) const
{
 if(editable)
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ void LayoutBlockThroughPathsTableModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  fireTableDataChanged();
 } else if (e->getPropertyName()==("through-path-removed"))
 {
  fireTableDataChanged();
 } else if (e->getPropertyName()==("through-path-added"))
 {
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

/*protected*/ bool LayoutBlockThroughPathsTableModel::matchPropertyName(PropertyChangeEvent* e)
{
 return (e->getPropertyName().indexOf("path") >= 0);
}

/**
 * Provides the empty String if attribute doesn't exist.
 */
/*public*/ QVariant LayoutBlockThroughPathsTableModel::data(const QModelIndex &index, int role) const
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
   case SOURCECOL:
       return lBlock->getThroughPathSource(row)->getDisplayName();
   case ACTIVECOL:
   {
    bool mutual = lBlock->isThroughPathActive(row);
    if (mutual)
    {
     return tr("Yes");
    }
    return tr("No");
   }
   case DESTINATIONCOL:
   {
    return lBlock->getThroughPathDestination(row)->getDisplayName();
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
/*public*/ bool LayoutBlockThroughPathsTableModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
 return false;
}

/*public*/ int LayoutBlockThroughPathsTableModel::getPreferredWidth(int column)
{
 int retval = 20; // always take some width
 retval =qMax(retval,  JLabel(getColumnName(column)).sizeHint().width() + 15);  // leave room for sorter arrow
 for (int row = 0; row < rowCount(QModelIndex()); row++)
 {
//        if (getColumnClass(column)==(String.class)) {
//            retval =qMax(retval, new JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        } else if (getColumnClass(column)==(Integer.class)) {
//            retval =qMax(retval, new JLabel(getValueAt(row, column).toString()).getPreferredSize().width);
//        }
 }
 return retval + 5;
}

// drop listeners
/*public*/ void LayoutBlockThroughPathsTableModel::dispose() {
}

/*public*/ Manager* LayoutBlockThroughPathsTableModel::getManager() {
 return (Manager*)InstanceManager::getDefault("LayoutBlockManager");
}

