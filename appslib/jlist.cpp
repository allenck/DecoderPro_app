#include "jlist.h"
#include "jlisttablemodel.h"
#include <QMenu>

JList::JList(QWidget* parent) : QListView(parent)
{

}
JList::JList(QAbstractListModel* model, QWidget* parent) : QListView(parent)
{
 setModel(model);
}

QAbstractListModel* JList::getModel() {return(QAbstractListModel*) model();}

JList::JList(QList<QString> list, QWidget *parent) : QListView(parent)
{
 setModel(new JListTableModel(list));
}

QModelIndexList JList::getSelectedValues()
{
 QModelIndexList list = QListView::selectedIndexes();
 return list;
}

/*public*/ bool JList::isSelectionEmpty()
{
    return getSelectedValues().isEmpty();
}

/**
 * Selects the specified object from the list.
 *
 * @param anObject      the object to select
 * @param shouldScroll  {@code true} if the list should scroll to display
 *                      the selected object, if one exists; otherwise {@code false}
 */
/*public*/ void JList::setSelectedValue(QString anObject, bool shouldScroll)
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
 if(anObject == nullptr)
  setCurrentIndex(QModelIndex());
 else
 {
  QAbstractItemModel* _model = model();
  for(int row=0; row < _model->rowCount();row++)
  {
   QModelIndex ix;
   if(anObject == _model->data(ix = _model->index(row,0)).toString())
   {
    setCurrentIndex(ix);
    if(shouldScroll)
     scrollTo(ix);
    break;
   }
  }
 }
}
#if 0
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
#endif
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

/**
 * Selects a single cell. Does nothing if the given index is greater
 * than or equal to the model size. This is a convenience method that uses
 * {@code setSelectionInterval} on the selection model. Refer to the
 * documentation for the selection model class being used for details on
 * how values less than {@code 0} are handled.
 *
 * @param index the index of the cell to select
 * @see ListSelectionModel#setSelectionInterval
 * @see #isSelectedIndex
 * @see #addListSelectionListener
 * @beaninfo
 * description: The index of the selected cell.
 */
/*public*/ void JList::setSelectedIndex(int index) {
    if (index >= model()->rowCount()) {
        return;
    }
    //getSelectionModel().setSelectionInterval(index, index);
    selectionModel()->setCurrentIndex(model()->index(index,0), QItemSelectionModel::ClearAndSelect);
}

/**
 * Scrolls the list within an enclosing viewport to make the specified
 * cell completely visible. This calls {@code scrollRectToVisible} with
 * the bounds of the specified cell. For this method to work, the
 * {@code JList} must be within a <code>JViewport</code>.
 * <p>
 * If the given index is outside the list's range of cells, this method
 * results in nothing.
 *
 * @param index  the index of the cell to make visible
 * @see JComponent#scrollRectToVisible
 * @see #getVisibleRect
 */
/*public*/ void JList::ensureIndexIsVisible(int index) {
//    Rectangle cellBounds = getCellBounds(index, index);
//    if (cellBounds != null) {
//        scrollRectToVisible(cellBounds);
//    }
 scrollTo(model()->index(index,0), QAbstractItemView::EnsureVisible);
}

/*public*/void JList::addListSelectionListener(ListSelectionListener* l)
{
 // TODO:

}

/*public*/ void JList::setVisibleRowCount(int count)
{
 visibleRowCount = count;
}

/*public*/ void JList::setComponentPopupMenu(QMenu* menu)
{
 setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
 this->menu = menu;
 connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_menu(QPoint)));
}

void JList::on_menu(QPoint pos)
{
 if(this->menu)
 {
  this->menu->exec(pos);
 }
}
