#ifndef DEFAULTMUTABLETREEMODEL_H
#define DEFAULTMUTABLETREEMODEL_H

#include <QAbstractItemModel>

class SdfMacroEditor;
class Logger;
class DefaultMutableTreeModelItem
{
public:
    DefaultMutableTreeModelItem(const QList<QVariant> &data, SdfMacroEditor* macroEditor, DefaultMutableTreeModelItem *parent = 0);
    ~DefaultMutableTreeModelItem();
    void appendChild(DefaultMutableTreeModelItem *child);
    void clear();
    DefaultMutableTreeModelItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    DefaultMutableTreeModelItem *parent();
    int tag;
    SdfMacroEditor* macroEditor;
    QList<DefaultMutableTreeModelItem*> children();

   private:
    QList<DefaultMutableTreeModelItem*> childItems;
    QList<QVariant> itemData;
    DefaultMutableTreeModelItem *parentItem;
};

class DefaultMutableTreeModel : public QAbstractItemModel
{
 Q_OBJECT
public:
 explicit DefaultMutableTreeModel(QObject *parent = 0);
 ~DefaultMutableTreeModel();
 QVariant data(const QModelIndex &index,int role) const;
 Qt::ItemFlags flags(const QModelIndex &index) const;
 QVariant headerData(int section,Qt::Orientation orientation,
 int role = Qt::DisplayRole) const;
 QModelIndex index(int row,int column,
 const QModelIndex &parent = QModelIndex()) const;
 QModelIndex parent(const QModelIndex &index) const;
 int rowCount(const QModelIndex &parent = QModelIndex()) const;
 int columnCount(const QModelIndex &parent = QModelIndex()) const;
 DefaultMutableTreeModelItem*  createNewNode(QString title, SdfMacroEditor* macroEditor);
 Q_DECL_DEPRECATED void processChildNode(SdfMacroEditor* macroEditor, DefaultMutableTreeModelItem* parent);
 void resetModel();
 QStringList getFilter();
 void removeNode(DefaultMutableTreeModelItem* parent);
signals:

public slots:
private:
    DefaultMutableTreeModelItem* rootItem;
    QList<DefaultMutableTreeModelItem*> parents;
    /*private*/ void removeChild(DefaultMutableTreeModelItem *parent);
    Logger* log;
};

#endif // DEFAULTMUTABLETREEMODEL_H
