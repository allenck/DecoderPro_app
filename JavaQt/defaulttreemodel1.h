#ifndef DEFAULTTREEMODEL1_H
#define DEFAULTTREEMODEL1_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QDir>
#include "logger.h"
#include <QPixmap>
#include "jtree.h"

//class JTree;
class DefaultTreeItem : public QObject
{
public:
    DefaultTreeItem(const QList<QVariant> &data, QVariant userData, DefaultTreeItem *parent = 0);
    ~DefaultTreeItem();
    void appendChild(DefaultTreeItem *child);
    void clear();
    DefaultTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    DefaultTreeItem *parent();
    int tag;
    QVariant userData;
    QList<DefaultTreeItem*> children();
    void setIcon(QString path);
    QString icon();
    QPixmap getPixmap();
    bool removeChild(DefaultTreeItem*);


   private:
    QList<DefaultTreeItem*> childItems;
    QList<QVariant> itemData;
    DefaultTreeItem *parentItem;
    QString iconPath;
    QPixmap iconPixmap;
};

class DefaultTreeModel1 : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DefaultTreeModel1(bool bShowFiles = false, QObject *parent = 0);
    ~DefaultTreeModel1();
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
    void processChildNode(QVariant userData, DefaultTreeItem* parent);
//    void setFilter(QDir::Filters filter);
    void resetModel();
//    QStringList getFilter();
    void removeNode(DefaultTreeItem* parent);
#if 0
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
#endif
    DefaultTreeItem* getRoot();
    void expandAll();

signals:
public slots:
private:
    DefaultTreeItem* rootItem;
    QList<DefaultTreeItem*> parents;
    //QDir::Filters filter;
    bool bShowFiles;
    //QStringList nameFilters;
    /*private*/ void removeChild(DefaultTreeItem *parent);
    Logger* log;
    JTree* tree;


 friend class UsbTreeModel;
};

#endif // DEFAULTTREEMODEL1_H
