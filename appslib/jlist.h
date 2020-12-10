#ifndef JLIST_H
#define JLIST_H

#include <QListView>
#include "javaqt_global.h"
#include "abstracttablemodel.h"
#include "listselectionlistener.h"

class JListTableModel;
class JAVAQTSHARED_EXPORT JList : public QListView
{
 Q_OBJECT
public:
 JList( QWidget* parent = 0);
 JList(QAbstractListModel* model, QWidget* parent = 0);
 JList(QList<QString>, QWidget* parent = 0);
 QModelIndexList getSelectedValues();
 QModelIndex locationToIndex(QPoint);
 /*public*/ int getSelectedIndex();
 /*public*/ void setSelectedValue(QString anObject, bool shouldScroll);
 /*public*/ QVariant getSelectedValue();
 /*public*/ void setSelectedIndex(int index);
 /*public*/ void ensureIndexIsVisible(int index);
 /*public*/ void addListSelectionListener(ListSelectionListener*l);
 /*public*/ void setVisibleRowCount(int count);
 QAbstractListModel *getModel();
 /*public*/ void setComponentPopupMenu(QMenu *menu);
 /*public*/ bool isSelectionEmpty();

public slots:
 void on_menu(QPoint pos);

private:
 void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
 /*private*/ int visibleRowCount;
 QMenu* menu = nullptr;
};
#if 0
class JAVAQTSHARED_EXPORT JListTableModel : public AbstractTableModel
{
 Q_OBJECT
 QList<QString> list;
public:
 JListTableModel(QList<QString>);
 int rowCount(const QModelIndex &parent) const override;
 int columnCount(const QModelIndex &parent) const override;
 QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 Qt::ItemFlags flags(const QModelIndex &index) const override;
 QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ int getRowCount() {return rowCount(QModelIndex());}
 /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

};
#endif
#endif // JLIST_H
