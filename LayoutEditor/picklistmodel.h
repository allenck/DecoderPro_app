#ifndef PICKLISTMODEL_H
#define PICKLISTMODEL_H

#include <QAbstractTableModel>
#include "jtable.h"
#include "logger.h"
#include "abstractnamedbean.h"
#include "abstracttablemodel.h"
#include "entryexitpairs.h"
#include "liblayouteditor_global.h"

class QSortFilterProxyModel;
class AbstractReporterManager;
class AbstractLightManager;
class AbstractLight;
class Reporter;
class Memory;
class DefaultSignalMastManager;
class AbstractSignalMast;
class AbstractSignalHead;
class AbstractMemoryManager;
class AbstractSignalHeadManager;
class AbstractSensorManager;
class AbstractTurnoutManager;
class Turnout;
class EntryExitPairs;
class WarrantManager;
class OBlockManager;
class ConditionalManager;
//class PickListTableModel;
class TurnoutManager;
class Manager;
class SensorManager;
class SignalHeadManager;
class SignalMastManager;
class MemoryManager;
class ReporterManager;
class LightManager;
class PropertyChangeEvent;
class LIBLAYOUTEDITORSHARED_EXPORT PickListModel : public /*AbstractNamedBean*/AbstractTableModel
{
    Q_OBJECT
public:
    explicit PickListModel(QObject *parent = 0);
enum Columns
{
 SNAME_COLUMN = 0,
 UNAME_COLUMN = 1,
 POSITION_COL = 2
};
static /*public*/ int getNumInstances(QString type);
/*public*/ void init() ;
/*public*/ NamedBean* getBeanAt(int index);
/*public*/ int getIndexOf(NamedBean* bean) ;
/*public*/ QList <NamedBean*>* getBeanList();
/*abstract*/ virtual /*public*/ Manager* getManager() {return NULL;}
/*abstract*/ virtual /*public*/ NamedBean* getBySystemName(QString /*name*/) {return NULL;}
/*abstract*/ virtual /*public*/ NamedBean* addBean(QString /*name*/) {return NULL;}
/*abstract*/ virtual /*public*/ NamedBean* addBean(QString /*sysName*/, QString /*userName*/) {return NULL;}
/*abstract*/ virtual /*public*/ bool canAddBean() {return false;}
///*public*/ QString getColumnClass(int c);
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ QString getName() ;
///*public*/ void propertyChange(PropertyChangeEvent* e); // is slot!
/*public*/ JTable* makePickTable();
/*public*/ void makeSorter(JTable* table);
/*public*/ JTable* getTable() ;
/*public*/ void dispose();
/*public*/ static PickListModel* turnoutPickModelInstance();
/*public*/ static PickListModel* sensorPickModelInstance();
/*public*/ static PickListModel* multiSensorPickModelInstance();
/*public*/ static PickListModel* signalHeadPickModelInstance();
/*public*/ static PickListModel* signalMastPickModelInstance() ;
/*public*/ static PickListModel* memoryPickModelInstance();
/*public*/ static PickListModel* reporterPickModelInstance();
/*public*/ static PickListModel* lightPickModelInstance() ;
/*public*/ static PickListModel* oBlockPickModelInstance();
/*public*/ static PickListModel* warrantPickModelInstance();
/*public*/ static PickListModel* conditionalPickModelInstance();
/*public*/ static PickListModel* entryExitPickModelInstance();
//void fireTableDataChanged();
//void fireTableRowsUpdated(int, int);

int getState() {return 0;}
void setState(int /*s*/) {}
//PickListModel *model();
QStringList mimeTypes() const;
QMimeData* mimeData(const QModelIndexList &indexes) const;
signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e);
virtual void tableClicked(QModelIndex) {}
private:
    /*private*/ JTable*  _table;       // table using this model

//    /*public*/ static /*final*/ ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");

    static QMap<QString,int>* _listMap;// = new QMap<QString,int>();
    Logger* log;
    /*private*/ void makePickList();
 //PickListModel* _tableModel;
protected:
 /*protected*/ QList <NamedBean*>* _pickList;
 /*protected*/ QString _name;
 /*protected*/ QSortFilterProxyModel* _sorter;

 friend class TurnoutPickModel;
};
class TurnoutPickModel : public  PickListModel
{
 Q_OBJECT
    TurnoutManager* manager;
public:
    TurnoutPickModel (QObject *parent=0);
    /*public*/ Manager* getManager() ;
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name) ;
    /*public*/ NamedBean* addBean(QString sysName, QString userName) ;
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex);
    void newTurnoutCreated(AbstractTurnoutManager*,Turnout*);

};

class SensorPickModel : public PickListModel
{
    Q_OBJECT
public:
    SensorManager* manager;
    SensorPickModel (QObject *parent =  0) ;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex index);
    void newSensorCreated(NamedBean *t);
};

class MultiSensorPickModel : public SensorPickModel
{
    Q_OBJECT
public:
    /*private*/ QMap <int, QString>* _position;// = new QMap <int, QString> ();
    MultiSensorPickModel(QObject *parent = 0) ;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) const;
    void tableClicked(QModelIndex index);
};

class SignalHeadPickModel : public PickListModel
{
    Q_OBJECT
    SignalHeadManager* manager;
public:
    SignalHeadPickModel (QObject *parent= 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName) ;
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex index);
    void newSignalHeadCreated(NamedBean *t);
};

class SignalMastPickModel : public PickListModel
{
    Q_OBJECT
    SignalMastManager* manager;
public:
    SignalMastPickModel (QObject *parent = 0) ;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex);
    void newSignalMastCreated( NamedBean *t);
};

class MemoryPickModel : public  PickListModel
{
    Q_OBJECT
    MemoryManager* manager;
public:
    MemoryPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) ;
    /*public*/ NamedBean* addBean(QString name) ;
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex index);
    void newMemoryCreated( Memory *t);
};

class ReporterPickModel : public PickListModel {
    Q_OBJECT
    ReporterManager* manager;
public:
    ReporterPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex index);
    void newReporterCreated(NamedBean *t);
};

class LightPickModel : public PickListModel {
    Q_OBJECT
    LightManager* manager;
public:
    LightPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
public slots:
    void tableClicked(QModelIndex index);
    void newLightCreated(NamedBean*);
};
#if 1
class OBlockPickModel : public PickListModel
{
    Q_OBJECT
public:
    OBlockManager* manager;
    OBlockPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) ;
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
};

class WarrantPickModel : public PickListModel {
    Q_OBJECT
public:
    WarrantManager* manager;
    WarrantPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
};
#endif
class ConditionalPickModel : public PickListModel {
    Q_OBJECT
public:
    ConditionalManager* manager;
    ConditionalPickModel (QObject *parent = 0) ;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name) ;
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
#if 0
    /*public*/ JTable makePickTable() {
        JTable table = super.makePickTable();
        TableColumn column = new TableColumn(PickListModel.POSITION_COL);
        column.setResizable(true);
        column.setMinWidth(100);
        column.setHeaderValue("Logix");
        table.addColumn(column);
        return table;
    }

    /*public*/ Object getValueAt (int r, int c) {
        if (c==POSITION_COL) {
            jmri.Logix l = manager.getParentLogix(_pickList.get(r).getSystemName());
            if (l!=NULL) {
                return l.getDisplayName();
            }
        }
        return super.getValueAt(r, c);
    }
#endif
};

class EntryExitPickModel : public PickListModel {
    Q_OBJECT
public:

    EntryExitPairs* manager;
    EntryExitPickModel (QObject *parent = 0);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* addBean(QString name);
    /*public*/ NamedBean* addBean(QString sysName, QString userName);
    /*public*/ bool canAddBean();
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
#endif // PICKLISTMODEL_H
