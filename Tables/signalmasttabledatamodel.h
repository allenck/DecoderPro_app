#ifndef SIGNALMASTTABLEDATAMODEL_H
#define SIGNALMASTTABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "jtable.h"

class SignalMastJTable;
class SignalMastTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
public:
    SignalMastTableDataModel(QObject* parent = 0);
    enum COLUMN
    {
     EDITMASTCOL = NUMCOLUMN,
     EDITLOGICCOL = EDITMASTCOL + 1,
     LITCOL = EDITLOGICCOL + 1,
     HELDCOL = LITCOL + 1
    };
    /*public*/ QString getValue(QString name) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ QString getColumnClass(int col);
    /*public*/ int getPreferredWidth(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE /*public*/ QString getClassDescription();
    /*public*/ void configureTable(JTable *table);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    Logger* log;
    void editLogic(int row, int col);
    void editMast(int row, int col);
    QSortFilterProxyModel* sorter;

protected:
    /*protected*/ Manager* getManager() ;
    /*protected*/ NamedBean* getBySystemName(QString name) const;
    /*protected*/ NamedBean* getByUserName(QString name);
    /*protected*/ QString getMasterClassName();
    /*protected*/ void clickOn(NamedBean* t);
    /*public*/ JTable* makeJTable(QSortFilterProxyModel* srtr);
    SignalMastJTable* table;
    /*protected*/ QString getBeanType() ;
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
    /*protected*/ QString getClassName();

};

//The JTable is extended so that we can reset the available aspect in the drop down when required
class SignalMastJTable : public JTable
{
 Q_OBJECT
    /**
     *
     */
    //private static final long serialVersionUID = 7888512352829953819L;
public:
    /*public*/ SignalMastJTable(QSortFilterProxyModel* srtr);
    /*public*/ void clearAspectVector(int row);
    /*public*/ bool editCellAt(int row, int column, QEvent* e);
//        /*public*/ TableCellRenderer getCellRenderer(int row, int column);
//        /*public*/ TableCellEditor getCellEditor(int row, int column);
    //TableCellRenderer getRenderer(int row) ;

};
#endif // SIGNALMASTTABLEDATAMODEL_H
