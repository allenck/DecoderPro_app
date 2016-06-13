#include "catalogtreemodel.h"
#include <QDir>
#include <QMimeData>
#include "fileutil.h"

CatalogTreeItem::CatalogTreeItem(const QList<QVariant> &data, QString path, CatalogTreeItem *parent)
{
 parentItem = parent;
 itemData = data;
 this->path = path;
}
CatalogTreeItem::~CatalogTreeItem()
{
 qDeleteAll(childItems);
}
void CatalogTreeItem::appendChild(CatalogTreeItem *item)
{
 childItems.append(item);
}
void CatalogTreeItem::clear()
{
 childItems.clear();
}
CatalogTreeItem *CatalogTreeItem::child(int row)
{
 return childItems.value(row);
}
int CatalogTreeItem::childCount() const
{
 return childItems.count();
}
int CatalogTreeItem::row() const
{
 if (parentItem)
  return parentItem->childItems.indexOf(const_cast<CatalogTreeItem*>(this));
 return 0;
}
int CatalogTreeItem::columnCount() const
{
 return itemData.count();
}
QVariant CatalogTreeItem::data(int column) const
{
 return QVariant(itemData.value(column));
}
CatalogTreeItem *CatalogTreeItem::parent()
{
 return parentItem;
}

// *************************************************


CatalogTreeModel::CatalogTreeModel(bool bShowFiles, QObject *parent) :
    QAbstractItemModel(parent)
{
 Q_UNUSED(parent);
 log  = new Logger("CatalogTreeModel");
 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData<<"Name";
 rootItem = new CatalogTreeItem(rootData, "", NULL);
 filter = QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::Hidden;
 this->bShowFiles = bShowFiles;
 if(bShowFiles)
 {
  filter |= QDir::Files;
  nameFilters << "*.png" << "*.gif" << "*.jpg";
 }
 //setSupportedDragActions(Qt::DropAction);
}
CatalogTreeModel::~CatalogTreeModel()
{
 delete rootItem;
 delete log;
}
QModelIndex CatalogTreeModel::index(int row,int column,const QModelIndex &parent)  const
{
 if (!hasIndex(row,column,parent))
  return QModelIndex();
 CatalogTreeItem *parentItem;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<CatalogTreeItem*>(parent.internalPointer());
 CatalogTreeItem *childItem = parentItem->child(row);
 if (childItem)
  return createIndex(row,column,childItem);
 else
  return QModelIndex();
}
QModelIndex CatalogTreeModel::parent(const QModelIndex &index) const
{
 if (!index.isValid())
  return QModelIndex();
 CatalogTreeItem *childItem = static_cast<CatalogTreeItem*>(index.internalPointer());
 CatalogTreeItem *parentItem = childItem->parent();
 if (parentItem == rootItem)
  return QModelIndex();
 return createIndex(parentItem->row(),0,parentItem);
}
int CatalogTreeModel::rowCount(const QModelIndex &parent) const
{
 CatalogTreeItem *parentItem;
 if (parent.column() > 0)
  return 0;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<CatalogTreeItem*>(parent.internalPointer());
 return parentItem->childCount();
}
int CatalogTreeModel::columnCount(const QModelIndex &parent) const
{
 if (parent.isValid())
  return static_cast<CatalogTreeItem*>(parent.internalPointer())->columnCount();
 else
  return rootItem->columnCount();
}
QVariant CatalogTreeModel::data(const QModelIndex &index,int role) const
{
 if (!index.isValid())
  return QVariant();
 if (role != Qt::DisplayRole)
  return QVariant();
 CatalogTreeItem *item = static_cast<CatalogTreeItem*>(index.internalPointer());
 return item->data(index.column());
}
Qt::ItemFlags CatalogTreeModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

 if (index.isValid())
  return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
 else
  return Qt::ItemIsDropEnabled | defaultFlags;
}
QVariant CatalogTreeModel::headerData(int section,Qt::Orientation orientation,
int role) const
{
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  return rootItem->data(section);
 return QVariant();
}
bool CatalogTreeModel::createNewNode(QString title, QString path)
{
 QDir dir(path);
// if(!dir.exists())
//     return false;
 dir.setFilter(filter);
 dir.setNameFilters(nameFilters);
 if(dir.dirName() == "." || dir.dirName() == "..") return false;
 QList<QVariant> data;
 data << QVariant(title);
 CatalogTreeItem* item = new CatalogTreeItem(data, path, rootItem);
 rootItem->appendChild(item);
 processChildNode(path,item);
 //resetModel();
 return true;
}
void CatalogTreeModel::processChildNode(QString path, CatalogTreeItem* parent)
{
 QDir dir(path);
// if(!dir.exists())
//  return;
 dir.setFilter(QDir::AllDirs);
 dir.setNameFilters(nameFilters);
 QFileInfoList list =dir.entryInfoList();
 foreach(QFileInfo info, list)
 {
  QString dirName = info.fileName();
  if(dirName == "." || dirName == "..") continue;
  if(info.isFile()) continue;
  QList<QVariant> data;
  data << QVariant(dirName) << "";
  CatalogTreeItem* item = new CatalogTreeItem(data, path+dirName, parent);
  parent->appendChild(item);
  processChildNode(path+dirName+QDir::separator(),item);
 }
}
void CatalogTreeModel::setFilter(QDir::Filters filter)
{
 beginResetModel();
 this->filter = filter;
 endResetModel();
}
void CatalogTreeModel::resetModel()
{
 beginResetModel();
 endResetModel();
}
QStringList CatalogTreeModel::getFilter() { return nameFilters;}
QList<CatalogTreeItem*> CatalogTreeItem::children() { return childItems;}

void CatalogTreeModel::removeNode(CatalogTreeItem *parent)
{
 beginResetModel();
 QListIterator<CatalogTreeItem*> it(parent->children());
 while(it.hasNext())
 {
  CatalogTreeItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
 endResetModel();
}
/*private*/ void CatalogTreeModel::removeChild(CatalogTreeItem *parent)
{
 QListIterator<CatalogTreeItem*> it(parent->children());
 while(it.hasNext())
 {
  CatalogTreeItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
}
bool CatalogTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
 QStringList l = data->formats();
 QString s_data = data->text();
 log->debug(s_data + " row= "+ QString::number(row)+ " column= "+QString::number(column));
 if(s_data.startsWith("DataFlavor["))
 {
  QString params=s_data.mid(11, s_data.length()-12);
  QStringList sl = params.split(";");
  foreach(QString s, sl)
  {
   QStringList pair = s.split("=");
   if(pair.at(0)=="path")
   {
    if(column == -1)
    {
      QFileInfo info(pair.at(1));
      QList<QVariant> data;
      beginResetModel();
      data << QVariant(info.baseName());
      QList<CatalogTreeItem*> l = rootItem->children();
      QString path = pair.at(1);
      if(path.startsWith("preference:"))
          path = FileUtil::getUserFilesPath()+path.mid(11);
      CatalogTreeItem* item = new CatalogTreeItem(data, path, l.at(0));
      l.at(0)->appendChild(item);
      processChildNode(pair.at(1),item);
      endResetModel();
    }
   }
  }
  return true;
 }
 return false;
}
Qt::DropActions CatalogTreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
QStringList CatalogTreeModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list" << "text/plain";
    return types;
}
QMimeData *CatalogTreeModel::mimeData(const QModelIndexList &indexes) const
{
 QMimeData *mimeData = new QMimeData();
 QByteArray encodedData;

 QDataStream stream(&encodedData, QIODevice::WriteOnly);

 foreach (const QModelIndex &index, indexes)
 {
  if (index.isValid())
  {
   QString text = data(index, Qt::DisplayRole).toString();
   stream << text;
  }
 }

 mimeData->setData("application/vnd.text.list", encodedData);
 return mimeData;
}
