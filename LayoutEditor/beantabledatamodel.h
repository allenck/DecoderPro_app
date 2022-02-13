#ifndef BEANTABLEDATAMODEL_H
#define BEANTABLEDATAMODEL_H

#include "abstracttablemodel.h"
#include <QStringList>
#include "logger.h"
#include "liblayouteditor_global.h"
#include <QItemDelegate>
#include "propertychangelistener.h"
#include "abstractmanager.h"

class NamedBeanPropertyDescriptor;
class RowSorter;
class QMenu;
class QTableView;
class QSortFilterProxyModel;
class HardcopyWriter;
class QPushButton;
class JTable;
class NamedBeanHandleManager;
class QCheckBox;
class QDialog;
class PropertyChangeEvent;
class NamedBean;
class Manager;
class LIBLAYOUTEDITORSHARED_EXPORT BeanTableDataModel : public AbstractTableModel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    explicit BeanTableDataModel(QObject *parent = 0);
 enum COLUMNS
 {
  SYSNAMECOL  = 0,
  USERNAMECOL = 1,
  VALUECOL = 2,
  COMMENTCOL = 3,
  DELETECOL = 4,
  NUMCOLUMN = 5
 };
 Q_ENUM(COLUMNS)
 //static /*public*/ /*final*/ int NUMCOLUMN;// = 5;
 /*abstract*/ /*public*/ virtual QString getValue(QString systemName) const;
 ~BeanTableDataModel();
 /*public*/ int rowCount(const QModelIndex &parent) const override;
 /*public*/ int columnCount(const QModelIndex &parent) const override;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ QString getColumnClass(int col) const override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 virtual /*public*/ int getPreferredWidth(int col) ;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 /*abstract*/ /*public*/ virtual QString getValue(QString systemName) {return QString();}

// virtual void fireTableDataChanged();
// virtual void fireTableRowsUpdated(int, int);
 /*public*/ int getDisplayDeleteMsg();
 /*public*/ void setDisplayDeleteMsg(int boo);
 virtual /*public*/ void configureTable(JTable* table);
 virtual /*synchronized*/ /*public*/ void dispose();
 virtual /*public*/ QPushButton* configureButton();
// /*public*/ void saveTableColumnDetails(JTable* table);
// QT_DEPRECATED/*public*/ void saveTableColumnDetails(JTable* table, QString beantableref);
 /*public*/ void persistTable(/*@Nonnull*/ JTable* table);// throws NullPointerException
 /*public*/ void stopPersistingTable(/*@Nonnull*/ JTable* table); //throws NullPointerException  QT_DEPRECATED
// /*public*/ void loadTableColumnDetails(JTable* table);
// QT_DEPRECATED/*public*/ void loadTableColumnDetails(JTable* table, QString beantableref);
 /*public*/ void printTable(HardcopyWriter* w);
 /*public*/ virtual JTable* makeJTable(/*@Nonnull */QString name, /*@Nonnull */TableModel* model, /*@Nullable*/ RowSorter* /*<? extends TableModel>*/ sorter);
 // QT_DEPRECATED/*public*/ JTable* makeJTable(QSortFilterProxyModel* sorter);
 /*public*/ void copyName(int);
 /*public*/ void renameBean(int);
 /*public*/ void removeName(int);
 /*public*/ void moveBean(int, int col);
 virtual /*public*/ void addToPopUp(QMenu* popup);
 /*public*/ void setPropertyColumnsVisible(JTable* table, bool visible);
 QObject* self() override {return (QObject*)this;}
 /*public*/ void editComment(int row, int column);
 /*public*/ QString getCellToolTip(JTable* table, int row, int col) const override;


signals:
 void buttonClicked(QModelIndex*, QString);

public slots:
 void on_yesButton_clicked();
 void on_noButton_clicked();
 /*public*/ virtual void propertyChange(PropertyChangeEvent* e)override;
 void OnButtonClicked(QObject*);
 void On_copyName_triggered();
 void On_renameBean_triggered();
 void On_removeName_triggered();
 virtual void /*public*/ init();

private:
 static Logger* log;
 bool noWarnDelete = false;
 virtual void doDelete(NamedBean* bean);
 QDialog* dialog = nullptr;
 QCheckBox* remember = nullptr;
 NamedBeanHandleManager* nbMan;// = InstanceManager.getDefault("NamedBeanHandleManager");
 NamedBean* t = nullptr;
 //QList<int> buttonMap;
 //JTable* _table = nullptr;
 int row;
 //void setPersistentButtons();
 QString formatToolTip(QString comment) const;

protected:
 /*abstract*/ /*protected*/ virtual Manager* getManager();
 /*protected*/ virtual void setManager(Manager* /*man*/);

 /*abstract*/ /*protected*/ virtual  NamedBean* getBySystemName(QString name) const ;
 /*abstract*/ /*protected*/ virtual  NamedBean* getByUserName(QString name);
 /*abstract*/ /*protected*/ virtual void clickOn(NamedBean* /*t*/) {}
 /*protected*/ QStringList sysNameList;// = NULL;
 virtual /*protected*/ /*synchronized*/ void updateNameList();
// /*protected*/ BeanTableDataModel* m;
 /*protected*/ void deleteBean(int row, int col);
/*abstract*/ /*protected*/ virtual QString getBeanType();
/*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* sample = NULL);
/*protected*/ virtual void configValueColumn(JTable* table);
 virtual /*protected*/ void configDeleteColumn(JTable* table);
 virtual /*abstract*/ /*protected*/ QString getMasterClassName();
 virtual /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 /*protected*/ void printColumns(HardcopyWriter* w, QStringList columnStrings, int columnSize);
 /*protected*/ void addMouseListenerToHeader(JTable* table);
 /*protected*/ void showTableHeaderPopup(QMouseEvent* e, JTable* table);
 /*protected*/ int getPropertyColumnCount() const;
 /*protected*/ /*final*/ QList<NamedBeanPropertyDescriptor*>* propertyColumns = nullptr;
 /*protected*/ NamedBeanPropertyDescriptor *getPropertyColumnDescriptor(int column);
 /*protected*/ JTable* configureJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ JTable* table, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter);
 virtual /*protected*/ void setColumnIdentities(JTable* table);

protected slots:
 void On_itemClicked(QModelIndex);
 /*protected*/ void showPopup(QPoint p);
 /*protected*/ void showTableHeaderPopup(const QPoint&);
 void onColumnSelected(QObject* obj);


friend class LogixTableAction;
friend class RouteTableDataModel;
friend class SGBeanTableDataModel;
friend class SensorTableAction;
friend class SensorTableWidget;
friend class SectionTableAction;
friend class SectionWidget;
friend class TabbedTableItem;
friend class AudioSourceTableDataModel;
friend class WarrantTableModel;
friend class WarrantTableFrame;
friend class JInternalFrame;
friend class TableFrames;
friend class LogixWidget;
friend class LTFTabbedTableItem;
friend class AbstractTableAction;
friend class TurnoutTableDataModel;
friend class SignalMastTableAction;
friend class OBlockTableAction;
friend class TTComboBoxDelegate;
friend class SensorTableDataModel;
friend class DeleteBeanWorker;
friend class TurnoutTableAction;
friend class LightTableDataModel;
friend class LightTableAction;
friend class ReporterTableAction;
friend class IdTagTableAction;
};

class DeleteBeanWorker : public QObject//extends SwingWorker<Void, Void>
{
Q_OBJECT
/*private*/ /*final*/ NamedBean* t;
BeanTableDataModel *model;

public:
/*public*/ DeleteBeanWorker(NamedBean* bean, BeanTableDataModel *model);

 signals:
  void finished();

 public slots:
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void *doInBackground();
 protected:

/*protected*/ void done();
};

#endif // BEANTABLEDATAMODEL_H
