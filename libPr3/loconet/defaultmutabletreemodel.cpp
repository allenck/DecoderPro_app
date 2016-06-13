#include "defaultmutabletreemodel.h"
#include "logger.h"
#include <QStringList>
#include "sdfmacroeditor.h"
#include "sdfmacro.h"

DefaultMutableTreeModelItem::DefaultMutableTreeModelItem(const QList<QVariant> &data, SdfMacroEditor* macroEditor, DefaultMutableTreeModelItem *parent)
{
 parentItem = parent;
 itemData = data;
 this->macroEditor = macroEditor;
}
DefaultMutableTreeModelItem::~DefaultMutableTreeModelItem()
{
 qDeleteAll(childItems);
}
void DefaultMutableTreeModelItem::appendChild(DefaultMutableTreeModelItem *item)
{
 childItems.append(item);
}
void DefaultMutableTreeModelItem::clear()
{
 childItems.clear();
}
DefaultMutableTreeModelItem *DefaultMutableTreeModelItem::child(int row)
{
 return childItems.value(row);
}
int DefaultMutableTreeModelItem::childCount() const
{
 return childItems.count();
}
int DefaultMutableTreeModelItem::row() const
{
 if (parentItem)
  return parentItem->childItems.indexOf(const_cast<DefaultMutableTreeModelItem*>(this));
 return 0;
}
int DefaultMutableTreeModelItem::columnCount() const
{
 return itemData.count();
}
QVariant DefaultMutableTreeModelItem::data(int column) const
{
 return QVariant(itemData.value(column));
}
DefaultMutableTreeModelItem *DefaultMutableTreeModelItem::parent()
{
 return parentItem;
}

// *************************************************

DefaultMutableTreeModel::DefaultMutableTreeModel(QObject *parent) :
  QAbstractItemModel(parent)
{
 log  = new Logger("DefaultMutableTreeModel");
 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData<<"Name";
 rootItem = new DefaultMutableTreeModelItem(rootData, NULL, NULL);
}
DefaultMutableTreeModel::~DefaultMutableTreeModel()
{
 delete rootItem;
 delete log;
}
QModelIndex DefaultMutableTreeModel::index(int row,int column,const QModelIndex &parent)  const
{
 if (!hasIndex(row,column,parent))
  return QModelIndex();
 DefaultMutableTreeModelItem *parentItem;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DefaultMutableTreeModelItem*>(parent.internalPointer());
 DefaultMutableTreeModelItem *childItem = parentItem->child(row);
 if (childItem)
  return createIndex(row,column,childItem);
 else
  return QModelIndex();
}
QModelIndex DefaultMutableTreeModel::parent(const QModelIndex &index) const
{
 if (!index.isValid())
  return QModelIndex();
 DefaultMutableTreeModelItem *childItem = static_cast<DefaultMutableTreeModelItem*>(index.internalPointer());
 DefaultMutableTreeModelItem *parentItem = childItem->parent();
 if (parentItem == rootItem)
  return QModelIndex();
 return createIndex(parentItem->row(),0,parentItem);
}
int DefaultMutableTreeModel::rowCount(const QModelIndex &parent) const
{
 DefaultMutableTreeModelItem *parentItem;
 if (parent.column() > 0)
  return 0;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DefaultMutableTreeModelItem*>(parent.internalPointer());
 return parentItem->childCount();
}
int DefaultMutableTreeModel::columnCount(const QModelIndex &parent) const
{
 if (parent.isValid())
  return static_cast<DefaultMutableTreeModelItem*>(parent.internalPointer())->columnCount();
 else
  return rootItem->columnCount();
}
QVariant DefaultMutableTreeModel::data(const QModelIndex &index,int role) const
{
 if (!index.isValid())
  return QVariant();
 if (role != Qt::DisplayRole)
  return QVariant();
 DefaultMutableTreeModelItem *item = static_cast<DefaultMutableTreeModelItem*>(index.internalPointer());
 return item->data(index.column());
}
Qt::ItemFlags DefaultMutableTreeModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

 if (index.isValid())
  return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
 else
  return Qt::ItemIsDropEnabled | defaultFlags;
}
QVariant DefaultMutableTreeModel::headerData(int section,Qt::Orientation orientation,
int role) const
{
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  return rootItem->data(section);
 return QVariant();
}
DefaultMutableTreeModelItem*  DefaultMutableTreeModel::createNewNode(QString title, SdfMacroEditor* macroEditor)
{
// if(!dir.exists())
//     return false;
 QList<QVariant> data;
 data << QVariant(title);
 DefaultMutableTreeModelItem* item = new DefaultMutableTreeModelItem(data, macroEditor, rootItem);
 rootItem->appendChild(item);
 //processChildNode(macroEditor,item);
 //resetModel();
 return item;
}
void DefaultMutableTreeModel::processChildNode(SdfMacroEditor* macroEditor, DefaultMutableTreeModelItem* parent)
{
#if 0
 QFileInfoList list =dir.entryInfoList();
 foreach(QFileInfo info, list)
 {
  QString dirName = info.fileName();
  if(dirName == "." || dirName == "..") continue;
  if(info.isFile()) continue;
  QList<QVariant> data;
  data << QVariant(dirName) << "";
  DefaultMutableTreeModelItem* item = new DefaultMutableTreeModelItem(data, path+dirName, parent);
  parent->appendChild(item);
  processChildNode(path+dirName+QDir::separator(),item);
 }
#endif
 if(macroEditor->getMacro() == NULL) return;
 QList<SdfMacro*>* children = macroEditor->getMacro()->getChildren();
 if (children == NULL) {
     return;
 }
 for (int i = 0; i < children->size(); i++)
 {
  QList<QVariant> data;
  SdfMacroEditor* macroEditor = SdfMacroEditor::attachEditor(children->at(i));
  data << QVariant(children->at(i)->name()) << "";
  DefaultMutableTreeModelItem* item = new DefaultMutableTreeModelItem(data, macroEditor, parent);
  parent->appendChild(item);
 }
}
void DefaultMutableTreeModel::resetModel()
{
 beginResetModel();
 endResetModel();
}
QList<DefaultMutableTreeModelItem*> DefaultMutableTreeModelItem::children() { return childItems;}

void DefaultMutableTreeModel::removeNode(DefaultMutableTreeModelItem *parent)
{
 beginResetModel();
 QListIterator<DefaultMutableTreeModelItem*> it(parent->children());
 while(it.hasNext())
 {
  DefaultMutableTreeModelItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
 endResetModel();
}
/*private*/ void DefaultMutableTreeModel::removeChild(DefaultMutableTreeModelItem *parent)
{
 QListIterator<DefaultMutableTreeModelItem*> it(parent->children());
 while(it.hasNext())
 {
  DefaultMutableTreeModelItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
}
