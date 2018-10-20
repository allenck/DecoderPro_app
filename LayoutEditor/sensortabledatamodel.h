#ifndef SENSORTABLEDATAMODEL_H
#define SENSORTABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "liblayouteditor_global.h"

class QSignalMapper;
class SensorManager;
class AbstractSensorManager;
class QTableView;
class LIBLAYOUTEDITORSHARED_EXPORT SensorTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
public:
    explicit SensorTableDataModel(QObject *parent = nullptr);
enum COLUMNS
{
  INVERTCOL = NUMCOLUMN,            // 5
  USEGLOBALDELAY = INVERTCOL+1,     // 6
  ACTIVEDELAY = USEGLOBALDELAY+1,
  INACTIVEDELAY = ACTIVEDELAY+1
};
/*public*/ SensorTableDataModel(SensorManager* manager, QObject *parent);
/*public*/ QString getValue(QString name) const;
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ int getPreferredWidth(int col);
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ void configureTable(JTable* table);
/*public*/ void showDebounce(bool show);
/*public*/ QString getClassDescription() ;

signals:

public slots:
 void OnDelete(int);
private:
 Manager* senManager;// = InstanceManager.sensorManagerInstance();
 void common();
 Logger * log;
 QSignalMapper* deleteMapper;

protected:
 /*protected*/ JTable* table;
 /*protected*/ void setManager(Manager* manager);
 /*protected*/ Manager* getManager();
 /*protected*/ virtual NamedBean* getBySystemName(QString name) const;
 /*protected*/ NamedBean* getByUserName(QString name);

 /*protected*/ QString getMasterClassName();
 /*protected*/ void clickOn(NamedBean* t);
 /*protected*/ QString getBeanType();
 /*protected*/ QString getClassName();
// /*protected*/ /*synchronized*/ void updateNameList();

protected slots:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
friend class SensorTableAction;
friend class SensorTableWidget;
};

#endif // SENSORTABLEDATAMODEL_H
