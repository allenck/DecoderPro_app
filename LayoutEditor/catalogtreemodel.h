#ifndef CATALOGTREEMODEL_H
#define CATALOGTREEMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QDir>
#include "logger.h"

class CatalogTreeItem
{
public:
    CatalogTreeItem(const QList<QVariant> &data, QString path, CatalogTreeItem *parent = 0);
    ~CatalogTreeItem();
    void appendChild(CatalogTreeItem *child);
    void clear();
    CatalogTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    CatalogTreeItem *parent();
    int tag;
    QString path;
    QList<CatalogTreeItem*> children();

   private:
    QList<CatalogTreeItem*> childItems;
    QList<QVariant> itemData;
    CatalogTreeItem *parentItem;
};

class CatalogTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CatalogTreeModel(bool bShowFiles = false, QObject *parent = 0);
    ~CatalogTreeModel();
    QVariant data(const QModelIndex &index,int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section,Qt::Orientation orientation,
    int role = Qt::DisplayRole) const;
    QModelIndex index(int row,int column,
    const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool createNewNode(QString title, QString path);
    void processChildNode(QString path, CatalogTreeItem* parent);
    void setFilter(QDir::Filters filter);
    void resetModel();
    QStringList getFilter();
    void removeNode(CatalogTreeItem* parent);
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
signals:
public slots:
private:
    CatalogTreeItem* rootItem;
    QList<CatalogTreeItem*> parents;
    QDir::Filters filter;
    bool bShowFiles;
    QStringList nameFilters;
    /*private*/ void removeChild(CatalogTreeItem *parent);
    Logger* log;
};

#endif // CATALOGTREEMODEL_H
