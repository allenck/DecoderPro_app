#ifndef ABSTRACTTABLEMODEL_H
#define ABSTRACTTABLEMODEL_H
#include "eventlistener.h"
#include "tablemodel.h"
#include <QVariant>
#include "javaqt_global.h"

class QItemDelegate;
class QPushButton;
class JTable;
class TableModelListener;
class TableModelEvent;
class JAVAQTSHARED_EXPORT AbstractTableModel : public TableModel
{
    Q_OBJECT
public:
    explicit AbstractTableModel(QObject *parent = 0);
    virtual /*public*/ QString getColumnName(int column) const;
    virtual /*public*/ int findColumn(QString columnName);
    virtual /*public*/ QString getColumnClass(int columnIndex){return QString();}
    virtual /*public*/ bool isCellEditable(int rowIndex, int columnIndex) const;
    virtual /*public*/ void setValueAt(QVariant aValue, int rowIndex, int columnIndex);
    /*public*/ virtual void addTableModelListener(TableModelListener* l);
    /*public*/ virtual void removeTableModelListener(TableModelListener* l);
    /*public*/ virtual QList<TableModelListener*>* getTableModelListeners();
    /*public*/ virtual void fireTableStructureChanged();
    /*public*/ virtual void fireTableRowsInserted(int firstRow, int lastRow);
    /*public*/ virtual void fireTableRowsUpdated(int firstRow, int lastRow);
    /*public*/ virtual void fireTableRowsDeleted(int firstRow, int lastRow);
    /*public*/ virtual void fireTableCellUpdated(int row, int column);
    /*public*/ virtual void fireTableChanged(TableModelEvent* e = 0);
    virtual /*public*/ int getRowCount() const {return rowCount(QModelIndex());}
    virtual /*public*/ int getColumnCount() const {return columnCount(QModelIndex());}
    virtual /*public*/ QVariant getValueAt(int row, int col) const;
    virtual /*public*/ QString getColumnClass(int col) const;
    virtual /*public*/ QVariant getToolTip(int /*col*/)const { return QString();}
    void setTable(JTable*);
//    void setPersistentButtons();
    JTable* table();
    virtual QString toString() {return metaObject()->className();}

signals:

public slots:
 /*public*/ virtual void fireTableDataChanged();

private:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    JTable* _table = nullptr;
//    QList<int> buttonMap;

protected:
    /** List of listeners */
    //protected EventListenerList* listenerList = new EventListenerList();
    QList<EventListener*>* listenerList;
    /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/= 0);
    void setColumnToHoldDelegate(JTable *table, int column, QItemDelegate *delegate);

    friend class CvTableModel;
    friend class BeanTableDataModel;
    friend class WarrantTableFrame;
    friend class TableFrames;
    friend class BlockTableDataModel;
    friend class TurnoutTableDataModel;
    friend class LightTableAction;
    friend class SignalMastTableAction;
    friend class SignallingPanel;
    friend class RouteFilterModel;
    friend class JTable;
    friend class CabSignalTableModel;
};

#endif // ABSTRACTTABLEMODEL_H
