#ifndef JLIST_H
#define JLIST_H

#include <QListView>
#include "javaqt_global.h"
#include "abstracttablemodel.h"

class JAVAQTSHARED_EXPORT JList : public QListView
{
public:
 JList( QWidget* parent = 0);
 JList(QList<QString>, QWidget* parent = 0);
 QModelIndexList getSelectedValues();
 QModelIndex locationToIndex(QPoint);
 /*public*/ int getSelectedIndex();

private:
 void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

class JAVAQTSHARED_EXPORT JListTableModel : public AbstractTableModel
{
 Q_OBJECT
 QList<QString> list;
public:
 JListTableModel(QList<QString>);
 int rowCount(const QModelIndex &parent) const;
 int columnCount(const QModelIndex &parent) const;
 QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 Qt::ItemFlags flags(const QModelIndex &index) const;
 QVariant data(const QModelIndex &index, int role) const;
};

#endif // JLIST_H
