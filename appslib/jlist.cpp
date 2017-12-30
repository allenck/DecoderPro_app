#include "jlist.h"

JList::JList(QWidget* parent) : QListView(parent)
{

}

JList::JList(QList<QString> list, QWidget *parent) : QListView(parent)
{
 setModel(new JListTableModel(list));
}

QModelIndexList JList::getSelectedValues()
{
 QModelIndexList list = QListView::selectedIndexes();
 return list;
}

/**
 * Selects the specified object from the list.
 *
 * @param anObject      the object to select
 * @param shouldScroll  {@code true} if the list should scroll to display
 *                      the selected object, if one exists; otherwise {@code false}
 */
/*public*/ void JList::setSelectedValue(QVariant anObject, bool shouldScroll)
{
#if 0 // TODO:
    if(anObject == NULL)
        setSelectedIndex(-1);
    else if(!anObject.equals(getSelectedValue())) {
        int i,c;
        ListModel<E> dm = getModel();
        for(i=0,c=dm.getSize();i<c;i++)
            if(anObject.equals(dm.getElementAt(i))){
                setSelectedIndex(i);
                if(shouldScroll)
                    ensureIndexIsVisible(i);
                repaint();  /** FIX-ME setSelectedIndex does not redraw all the time with the basic l&f**/
                return;
            }
        setSelectedIndex(-1);
    }
    repaint(); /** FIX-ME setSelectedIndex does not redraw all the time with the basic l&f**/
#endif
 if(anObject == QVariant())
  setCurrentIndex(QModelIndex());
 else
 {
  QAbstractItemModel* _model = model();
  for(int row=0; row < _model->rowCount();row++)
  {
   QModelIndex ix;
   if(anObject == _model->data(ix = _model->index(row,0)))
   {
    setCurrentIndex(ix);
    if(shouldScroll)
     scrollTo(ix);
    break;
   }
  }
 }
}

JListTableModel::JListTableModel(QList<QString> list)
{
 this->list = list;

}

int JListTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 1;
}

int JListTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return list.count();
}

QVariant JListTableModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
 return QVariant();
}

Qt::ItemFlags JListTableModel::flags(const QModelIndex &/*index*/) const
{
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant JListTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
  return list.at(index.row());
 return QVariant();
}

QModelIndex JList::locationToIndex(QPoint p)
{
 return indexAt(p);
}

/*public*/ int JList::getSelectedIndex()
{
 QModelIndexList list = QListView::selectedIndexes();
 if(list.isEmpty()) return -1;
 return list.at(0).row();
}

/*private*/ void JList::selectionChanged(const QItemSelection &/*selected*/, const QItemSelection &/*deselected*/)
{

}

/*public*/ QVariant JList::getSelectedValue()
{
 QModelIndexList list = QListView::selectedIndexes();
 if(list.isEmpty()) return -1;
 return model()->data(list.at(0));
}
