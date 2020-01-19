#ifndef SENSORTABLEDATAMODEL_H
#define SENSORTABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "liblayouteditor_global.h"
#include <QPixmap>

class ImageIconRenderer;
class Component;
class QLabel;
class BufferedImage;
class QImage;
class QPixmap;
class QSignalMapper;
class SensorManager;
class AbstractSensorManager;
class QTableView;
class LIBLAYOUTEDITORSHARED_EXPORT SensorTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
public:
    explicit SensorTableDataModel(QObject *parent = nullptr);
 ~SensorTableDataModel() {}
 SensorTableDataModel(const SensorTableDataModel&) : BeanTableDataModel() {}
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
Q_INVOKABLE /*public*/ QString getClassDescription() ;

signals:

public slots:
 void OnDelete(int);
private:
 SensorManager* senManager;// = InstanceManager.sensorManagerInstance();
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
 // for icon state col
 /*protected*/ bool _graphicState = false; // updated from prefs
 ImageIconRenderer* renderer = nullptr;

protected slots:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
friend class SensorTableAction;
friend class SensorTableWidget;
};
Q_DECLARE_METATYPE(SensorTableDataModel)

class ImageIconRenderer : public QObject //extends AbstractCellEditor implements TableCellEditor, TableCellRenderer {
{
 Q_OBJECT
 static Logger* log;
protected:
    /*protected*/ QLabel* label;
    /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
    /*protected*/ char beanTypeChar;// = 'S'; // for Sensor
    /*protected*/ QString onIconPath;// = rootPath + beanTypeChar + "-on-s.png";
    /*protected*/ QString offIconPath;// = rootPath + beanTypeChar + "-off-s.png";
    /*protected*/ BufferedImage* onImage;
    /*protected*/ BufferedImage* offImage;
    /*protected*/ QPixmap onIcon;
    /*protected*/ QPixmap offIcon;
    /*protected*/ int iconHeight = -1;
public:
 /*public*/ ImageIconRenderer();
#if 0
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Component* getTableCellRendererComponent(
            JTable* table, QVariant value, bool isSelected,
            bool hasFocus, int row, int column);
    /*public*/ Component* getTableCellEditorComponent(
            JTable* table, QVariant value, bool isSelected,
            int row, int column);
    /*public*/ QLabel* updateLabel(QString value, int row);
    /*public*/ QVariant getCellEditorValue();
#endif
protected:
    /*protected*/ void loadIcons();
 friend class SensorTableDataModel;
}; // end of ImageIconRenderer class

#endif // SENSORTABLEDATAMODEL_H
