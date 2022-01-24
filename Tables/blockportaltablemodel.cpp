#include "blockportaltablemodel.h"
#include "propertychangeevent.h"
#include "jtextfield.h"
#include "namedbean.h"
#include "oblocktablemodel.h"
#include <oblock.h>
#include "portal.h"
#include "loggerfactory.h"

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
        case OPPOSING_BLOCK_NAME:
            return tr("Opposing Block");
        default:
            log->warn(tr("Unhandled column name: %1").arg(section));
            break;}
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
   if (col == PORTAL_NAME_COLUMN) {
       return block->getPortals().value(idx)->getName();
   }
   if (col == OPPOSING_BLOCK_NAME) {
       Portal* portal = block->getPortals().value(idx);
       OBlock* oppBlock = portal->getOpposingBlock(block);
       if (oppBlock != nullptr) {
           return oppBlock->getDisplayName();
       }
   }
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

/*public*/ QString BlockPortalTableModel::getColumnClass(int col) {
    return "String";
}

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

/*private*/ /*final*/ /*static*/ Logger* BlockPortalTableModel::log = LoggerFactory::getLogger("BlockPortalTableModel");
