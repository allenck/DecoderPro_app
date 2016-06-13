#include "blockportaltablemodel.h"
#include "propertychangeevent.h"
#include "jtextfield.h"
#include "namedbean.h"
#include "oblocktablemodel.h"
#include <oblock.h>
#include "portal.h"

//BlockPortalTableModel::BlockPortalTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
//class BlockPortalTableModel extends AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//private static /*final*/ long serialVersionUID = -6547843920072979055L;
//static /*final*/ ResourceBundle rbo = ResourceBundle.getBundle("jmri.jmrit.beantable.OBlockTableBundle");


/*public*/ BlockPortalTableModel::BlockPortalTableModel(OBlockTableModel* oBlockModel) {
    //super();
    _oBlockModel = oBlockModel;
}
#if 1
/*public*/ int BlockPortalTableModel::columnCount(const QModelIndex &parent) const
{
    return NUMCOLS;
}

/*public*/ int BlockPortalTableModel::rowCount(const QModelIndex &parent) const
{
    int count = 0;
    QList<NamedBean*> list = _oBlockModel->getBeanList();
    for (int i = 0; i < list.size(); i++) {
        count += ((OBlock*) list.at(i))->getPortals().size();
    }
    return count;
}

/*public*/ QVariant BlockPortalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case BLOCK_NAME_COLUMN:
            return tr("Block Name");
        case PORTAL_NAME_COLUMN:
            return tr("Portal Name");
    }
    return "";
 }
 return QVariant();
}

/*public*/ QVariant BlockPortalTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();

  QList<NamedBean*> list = _oBlockModel->getBeanList();
  if (list.size() > 0)
  {
   int count = 0;
   int idx = 0;		//accumulated row count
   OBlock* block = NULL;
   QVector<NamedBean*> array = QVector<NamedBean*>(list.size());
   //array = list.toArray(array);
   array =  list.toVector();
  //        Arrays.sort(array, new jmri.util.NamedBeanComparator());
   while (count <= row)
   {
    count += ((OBlock*) array[idx++])->getPortals().size();
   }
   block = (OBlock*) array[--idx];
   idx = row - (count - block->getPortals().size());
   if (col == BLOCK_NAME_COLUMN)
   {
    if (idx == 0)
    {
        return block->getDisplayName();
    }
    return "";
   }
   return block->getPortals().at(idx)->getName();
   /*
    while (count <= row)  {
    count += ((OBlock)list.get(idx++)).getPortals().size();
    }
    block = (OBlock)list.get(--idx);
    idx = row - (count - block.getPortals().size());
    if (col==BLOCK_NAME_COLUMN) {
    if (idx==0) {
    return block.getDisplayName();
    }
    return "";
    }
    return block.getPortals().get(idx).getName();
    */
  }
  //return NULL;
 }
 return QVariant();
}

/*public*/ bool BlockPortalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 return false;
}

/*public*/ Qt::ItemFlags BlockPortalTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

///*public*/ Class<?> getColumnClass(int col) {
//    return String.class;
//}

/*public*/ int BlockPortalTableModel::getPreferredWidth(int col) {
 return  JTextField(15).sizeHint().width();
}
#endif
/*public*/ void BlockPortalTableModel::propertyChange(PropertyChangeEvent* e) {
    QString property = e->getPropertyName();
    if (property==("length") || property==("UserName")) {
        fireTableDataChanged();
    }
}

