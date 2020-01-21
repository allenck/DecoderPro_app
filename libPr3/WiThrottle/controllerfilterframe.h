#ifndef CONTROLLERFILTERFRAME_H
#define CONTROLLERFILTERFRAME_H
#include "jmrijframe.h"
#include "abstracttablemodel.h"

class RouteManager;
class TurnoutManager;
class TableModelEvent;
class JTable;
class Logger;
class ControllerFilterFrame : public JmriJFrame
{
 Q_OBJECT
public:
 ControllerFilterFrame(QWidget* parent = 0);
 /*public*/ void initComponents() throw (Exception);
 /*public*/ void tableChanged(TableModelEvent* e);
 /*public*/ QString getClassName();

public slots:
 void dispose();
 void on_save();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ControllerFilterFrame.class.getName());
 /*private*/ static QStringList COLUMN_NAMES;// = {Bundle.getMessage("ColumnSystemName"),
//         Bundle.getMessage("ColumnUserName"),
//         Bundle.getMessage("Include")};
 /*private*/ QWidget* addTurnoutPanel();
 /*private*/ QWidget* addRoutePanel();
 /*private*/ void buildTable(JTable* table);
// /*private*/ QWidget* getIncludeButtonsPanel(/*final*/ AbstractFilterModel fm);
 /*private*/ QWidget* addCancelSavePanel();

protected:
 /*protected*/ void storeValues();

};
#if 1
/*public*/ /*abstract*/ class AbstractFilterModel : public  AbstractTableModel //implements PropertyChangeListener
{
  Q_OBJECT
    QStringList sysNameList;// = nullptr;
    bool isDirty;
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
public:
    enum COLS
    {
     SNAMECOL = 0,
     UNAMECOL = 1,
     INCLUDECOL = 2
    };

    /*public*/ void dispose();
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*abstract*/ virtual void setIncludeColToValue(bool value) = 0;
    /*abstract*/ virtual void SetIncludeToUserNamed() =0;
friend class TurnoutFilterModel;
friend class RouteFilterModel;
};
#endif
#if 0
class TurnoutFilterModel : public AbstractFilterModel {
Q_OBJECT

    TurnoutManager* mgr;// = InstanceManager.turnoutManagerInstance();
public:
    TurnoutFilterModel();
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ void setIncludeColToValue(bool value);
    /*public*/ void SetIncludeToUserNamed();
private:
    static Logger* log;
};
#endif
#if 0
class RouteFilterModel : public AbstractFilterModel {
Q_OBJECT
    RouteManager* mgr;// = InstanceManager.getDefault(jmri.RouteManager.class);
public:
    RouteFilterModel();

    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ void setIncludeColToValue(bool value);
    /*public*/ void SetIncludeToUserNamed();
};
#endif
#endif // CONTROLLERFILTERFRAME_H
