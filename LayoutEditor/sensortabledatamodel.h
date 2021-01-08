#ifndef SENSORTABLEDATAMODEL_H
#define SENSORTABLEDATAMODEL_H
#include "beantabledatamodel.h"
#include "liblayouteditor_global.h"
#include <QPixmap>
#include "tablecelleditor.h"
#include "tablecellrenderer.h"

class Sensor;
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
 ~SensorTableDataModel()override {}
 SensorTableDataModel(const SensorTableDataModel&) : BeanTableDataModel() {}
enum COLUMNS
{
  INVERTCOL = NUMCOLUMN,            // 5
  EDITCOL = INVERTCOL + 1,
  USEGLOBALDELAY = EDITCOL+1,     // 6
  ACTIVEDELAY = USEGLOBALDELAY+1,
  INACTIVEDELAY = ACTIVEDELAY+1,
  PULLUPCOL = INACTIVEDELAY + 1,
  FORGETCOL = PULLUPCOL + 1,
  QUERYCOL = FORGETCOL + 1
};
/*public*/ SensorTableDataModel(SensorManager* manager, QObject *parent);
/*public*/ QString getValue(QString name) const override;
/*public*/ int columnCount(const QModelIndex &parent) const override;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
/*public*/ int getPreferredWidth(int col) override;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
/*public*/ QVariant data(const QModelIndex &index, int role) const override;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
/*public*/ void configureTable(JTable* table) override;
/*public*/ void showDebounce(bool show);
Q_INVOKABLE /*public*/ QString getClassDescription() ;
/*public*/ QString getColumnClass(int col) const override;

signals:

public slots:
 void OnDelete(int);
private:
 SensorManager* senManager;// = InstanceManager.sensorManagerInstance();
 void common();
 Logger * log;
 QSignalMapper* deleteMapper;
 void editButton(Sensor* s);

protected:
 /*protected*/ JTable* table;
 /*protected*/ void setManager(Manager* manager) override;
 /*protected*/ Manager* getManager() override;
 /*protected*/ virtual NamedBean* getBySystemName(QString name) const override;
 /*protected*/ NamedBean* getByUserName(QString name) override;

 /*protected*/ QString getMasterClassName() override;
 /*protected*/ void clickOn(NamedBean* t) override;
 /*protected*/ QString getBeanType() override;
 /*protected*/ QString getClassName();
// /*protected*/ /*synchronized*/ void updateNameList();
 // for icon state col
 /*protected*/ bool _graphicState = false; // updated from prefs
 /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
 /*protected*/ char beanTypeChar;// = 'S'; // for Sensor
 /*protected*/ QString onIconPath;// = rootPath + beanTypeChar + "-on-s.png";
 /*protected*/ QString offIconPath;// = rootPath + beanTypeChar + "-off-s.png";
 /*protected*/ BufferedImage* onImage = nullptr;
 /*protected*/ BufferedImage* offImage = nullptr;
 /*protected*/ QPixmap onIcon;
 /*protected*/ QPixmap offIcon;
 /*protected*/ int iconHeight = -1;
 /*protected*/ void loadIcons();
 /*protected*/ void configValueColumn(JTable* table);


protected slots:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
friend class SensorTableAction;
friend class SensorTableWidget;
};
Q_DECLARE_METATYPE(SensorTableDataModel)

#if 0
class ImageIconRenderer : public QItemDelegate , public TableCellEditor, public TableCellRenderer
{
 Q_OBJECT
  Q_INTERFACES(TableCellEditor TableCellRenderer)
 static Logger* log;
 QObject* self() {return (QObject*)this;}
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
#endif
#endif // SENSORTABLEDATAMODEL_H
