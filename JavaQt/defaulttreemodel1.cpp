#include "defaulttreemodel1.h"
#include <QDir>
#include <QMimeData>
#include "file.h"
#include "jtree.h"

// Note: used by UsbTreeModel

DefaultTreeItem::DefaultTreeItem(const QList<QVariant> &data, QVariant userData, DefaultTreeItem *parent) : QObject()
{
 parentItem = parent;
 itemData = data;
 this->userData = userData;
}

DefaultTreeItem::~DefaultTreeItem()
{
 qDeleteAll(childItems);
}

void DefaultTreeItem::appendChild(DefaultTreeItem *item)
{
 childItems.append(item);
}

void DefaultTreeItem::clear()
{
 childItems.clear();
}

DefaultTreeItem *DefaultTreeItem::child(int row)
{
 return childItems.value(row);
}

int DefaultTreeItem::childCount() const
{
 return childItems.count();
}

int DefaultTreeItem::row() const
{
 if (parentItem)
  return parentItem->childItems.indexOf(const_cast<DefaultTreeItem*>(this));
 return 0;
}

int DefaultTreeItem::columnCount() const
{
 return itemData.count();
}

QVariant DefaultTreeItem::data(int column) const
{
 return QVariant(itemData.value(column));
}

DefaultTreeItem *DefaultTreeItem::parent()
{
 return parentItem;
}

void DefaultTreeItem::setIcon(QString path)
{
 if(File(path).exists())
 {
  iconPixmap = QPixmap(path).scaledToHeight(25);
  if(!iconPixmap.isNull())
    iconPath = path;
 }
}

QString DefaultTreeItem::icon()
{
 return iconPath;
}

QPixmap DefaultTreeItem::getPixmap()
{
 return iconPixmap;
}

bool DefaultTreeItem::removeChild(DefaultTreeItem* item)
{
 if(childItems.contains(item))
 {
  childItems.removeOne(item);
  return true;
 }
 return false;
}

// *************************************************


DefaultTreeModel1::DefaultTreeModel1(bool bShowFiles, QObject *parent) :
    QAbstractItemModel(parent)
{
 Q_UNUSED(parent);
 log  = new Logger("DefaultTreeModel1");
 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData << "Name" << "Manufacturer" << "Product";
 rootItem = new DefaultTreeItem(rootData, "", NULL);
 //filter = QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::Hidden;
 this->bShowFiles = bShowFiles;
// if(bShowFiles)
// {
//  filter |= QDir::Files;
//  nameFilters << "*.png" << "*.gif" << "*.jpg";
// }
 //setSupportedDragActions(Qt::DropAction);
}

DefaultTreeModel1::~DefaultTreeModel1()
{
 delete rootItem;
 delete log;
}
QModelIndex DefaultTreeModel1::index(int row,int column,const QModelIndex &parent)  const
{
 if (!hasIndex(row,column,parent))
  return QModelIndex();
 DefaultTreeItem *parentItem;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DefaultTreeItem*>(parent.internalPointer());
 DefaultTreeItem *childItem = parentItem->child(row);
 if (childItem)
  return createIndex(row,column,childItem);
 else
  return QModelIndex();
}

QModelIndex DefaultTreeModel1::parent(const QModelIndex &index) const
{
 if (!index.isValid())
  return QModelIndex();
 DefaultTreeItem *childItem = static_cast<DefaultTreeItem*>(index.internalPointer());
 DefaultTreeItem *parentItem = childItem->parent();
 if (parentItem == rootItem)
  return QModelIndex();
 return createIndex(parentItem->row(),0,parentItem);
}

int DefaultTreeModel1::rowCount(const QModelIndex &parent) const
{
 DefaultTreeItem *parentItem;
 if (parent.column() > 0)
  return 0;
 if (!parent.isValid())
  parentItem = rootItem;
 else
  parentItem = static_cast<DefaultTreeItem*>(parent.internalPointer());
 return parentItem->childCount();
}

int DefaultTreeModel1::columnCount(const QModelIndex &parent) const
{
 if (parent.isValid())
  return static_cast<DefaultTreeItem*>(parent.internalPointer())->columnCount();
 else
  return rootItem->columnCount();
}

QVariant DefaultTreeModel1::data(const QModelIndex &index,int role) const
{
 if (!index.isValid())
  return QVariant();
 DefaultTreeItem *item = static_cast<DefaultTreeItem*>(index.internalPointer());

 if(role == Qt::DecorationRole && !item->getPixmap().isNull() && index.column() == 0)
 {
  return item->getPixmap();
 }
 if (role != Qt::DisplayRole)
  return QVariant();
 return item->data(index.column());
}

Qt::ItemFlags DefaultTreeModel1::flags(const QModelIndex &index) const
{
 Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

 if (index.isValid())
  return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
 else
  return Qt::ItemIsDropEnabled | defaultFlags;
}

QVariant DefaultTreeModel1::headerData(int section,Qt::Orientation orientation,
int role) const
{
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  return rootItem->data(section);
 return QVariant();
}

bool DefaultTreeModel1::createNewNode(QString title, QString path)
{
// QDir dir(path);
// if(!dir.exists())
//     return false;
// dir.setFilter(filter);
// dir.setNameFilters(nameFilters);
// if(dir.dirName() == "." || dir.dirName() == "..") return false;
 QList<QVariant> data;
 data << QVariant(title);
 DefaultTreeItem* item = new DefaultTreeItem(data, path, rootItem);
 rootItem->appendChild(item);
 processChildNode(path,item);
 //resetModel();
 return true;
}

void DefaultTreeModel1::processChildNode(QVariant userData, DefaultTreeItem* parent)
{
// QDir dir(path);
// if(!dir.exists())
//  return;
// dir.setFilter(QDir::AllDirs);
// dir.setNameFilters(nameFilters);
// QFileInfoList list =dir.entryInfoList();
// foreach(QFileInfo info, list)
// {
//  QString dirName = info.fileName();
//  if(dirName == "." || dirName == "..") continue;
//  if(info.isFile()) continue;
  QList<QVariant> data;
  data << QVariant(userData.toString()) << "";
  DefaultTreeItem* item = new DefaultTreeItem(data, userData, parent);
  parent->appendChild(item);
  processChildNode(userData,item);
// }
}

#if 0
void DefaultTreeModel1::setFilter(QDir::Filters filter)
{
 beginResetModel();
 this->filter = filter;
 endResetModel();
}
#endif
void DefaultTreeModel1::resetModel()
{
 beginResetModel();
 endResetModel();
}

//QStringList DefaultTreeModel1::getFilter() { return nameFilters;}

QList<DefaultTreeItem*> DefaultTreeItem::children() { return childItems;}

void DefaultTreeModel1::removeNode(DefaultTreeItem *parent)
{
 beginResetModel();
 QListIterator<DefaultTreeItem*> it(parent->children());
 while(it.hasNext())
 {
  DefaultTreeItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
 endResetModel();
}

/*private*/ void DefaultTreeModel1::removeChild(DefaultTreeItem *parent)
{
 QListIterator<DefaultTreeItem*> it(parent->children());
 while(it.hasNext())
 {
  DefaultTreeItem* item = it.next();
  if(item != NULL)
   removeChild(item);
 }
}
#if 0
bool DefaultTreeModel1::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
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
      QList<DefaultTreeItem1*> l = rootItem->children();
      QString path = pair.at(1);
      if(path.startsWith("preference:"))
          path = FileUtil::getUserFilesPath()+path.mid(11);
      DefaultTreeItem1* item = new DefaultTreeItem1(data, path, l.at(0));
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

Qt::DropActions DefaultTreeModel1::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QStringList DefaultTreeModel1::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list" << "text/plain";
    return types;
}

QMimeData *DefaultTreeModel1::mimeData(const QModelIndexList &indexes) const
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
#endif
DefaultTreeItem* DefaultTreeModel1::getRoot() { return rootItem;}

void DefaultTreeModel1::expandAll()
{
 QModelIndexList indexes = match(index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
 foreach (QModelIndex index, indexes)
  tree->expand(index);
}

