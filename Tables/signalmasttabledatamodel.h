#ifndef SIGNALMASTTABLEDATAMODEL_H
#define SIGNALMASTTABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "jtable.h"
#include "propertychangelistener.h"

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
    /*public*/ QString getValue(QString name) const override;
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ QString getColumnClass(int col) const override;
    /*public*/ int getPreferredWidth(int col) override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Q_INVOKABLE /*public*/ QString getClassDescription();
    /*public*/ void configureTable(JTable *table) override;
    QObject* self() override {return (QObject*)this;}

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
    Logger* log;
    void editLogic(int row, int col);
    void editMast(int row, int col);
    QSortFilterProxyModel* sorter;

protected:
    /*protected*/ AbstractManager* getManager()  override;
    /*protected*/ NamedBean* getBySystemName(QString name) const override;
    /*protected*/ NamedBean* getByUserName(QString name) override;
    /*protected*/ QString getMasterClassName() override;
    /*protected*/ void clickOn(NamedBean* t) override;
    /*public*/ JTable* makeJTable(QSortFilterProxyModel* srtr);
    SignalMastJTable* table;
    /*protected*/ QString getBeanType()  override;
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
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
