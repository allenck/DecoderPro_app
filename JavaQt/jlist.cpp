#include "jlist.h"

JList::JList(QWidget* parent) : QListView(parent)
{

}

QModelIndexList JList::getSelectedValues()
{
 QModelIndexList list = QListView::selectedIndexes();
 return list;
}

