#ifndef ROUTETABLEACTION_H
#define ROUTETABLEACTION_H

#include <QObject>
#include "logger.h"
#include <QCheckBox>
#include <QScrollArea>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QAbstractTableModel>
#include "sensor.h"
#include "turnout.h"
#include "../libPr3/route.h"
#include <QHBoxLayout>
#include <QItemDelegate>
#include "windowlistener.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "runnable.h"
#include "jtextfield.h"
#include "abstracttableaction.h"
#include "libtables_global.h"

class RouteTableDataModel;
class AddFrameWindowListener2;
class Logix;
class ConditionalAction;
class ConditionalVariable;
class QTableView;
//class Route;
class Turnout;
class JTextField;
class JmriJFrame;
class JmriBeanComboBox;
class JActionEvent;
class RouteTurnout;
class RouteSensor;
//class RouteOutputModel;
class RouteTurnoutModel;
class RouteSensorModel;
class PropertyChangeEvent;
class Sensor;
class UserPreferencesManager;
class LIBTABLESSHARED_EXPORT RouteTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RouteTableAction(QObject *parent = 0);
    Q_INVOKABLE/*public*/ RouteTableAction(QString s, QObject *parent);
    ~RouteTableAction() {}
    RouteTableAction(const RouteTableAction&);
    /*public*/ /*final*/ static QString LOGIX_SYS_NAME;// = "RTX";
    /*public*/ /*final*/ static QString CONDITIONAL_SYS_PREFIX;// = LOGIX_SYS_NAME+"C";
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
    Q_INVOKABLE /*public*/ QString getClassDescription();
    ConditionalVariable* makeCtrlSensorVar(JmriBeanComboBox* jmriBox, QComboBox* sensorbox,
                                           bool makeVeto, bool onChange);
    enum COLUMNS
    {
     SYSNAMECOL,
     USERNAMECOL,
     VALUECOL,
     COMMENTCOL,
     DELETECOL,
     ENABLECOL = 5,
     LOCKCOL = 6,
     SETCOL = 7
    };
    bool removeConditionals(QString cSystemName, Logix* logix) ;
    int makeSensorConditional(JmriBeanComboBox* jmriBox, QComboBox* sensorbox, int numConds,
                        bool onChange, QList<ConditionalAction*>* actionList,
                        QList<ConditionalVariable*>* vetoList, Logix* logix, QString prefix, QString uName);
    ConditionalVariable* makeCtrlTurnoutVar(JmriBeanComboBox* jmriBox, QComboBox* box,
                                            bool makeVeto, bool onChange);
    int makeTurnoutConditional(JmriBeanComboBox* jmriBox, QComboBox* box, int numConds,
                        bool onChange, QList<ConditionalAction*>* actionList,
                        QList<ConditionalVariable*>* vetoList, Logix* logix, QString prefix, QString uName);
    ConditionalVariable* cloneVariable(ConditionalVariable* v);
    QList<ConditionalAction*>* cloneActionList(QList<ConditionalAction*>* actionList, int option);
    static QString getName();

signals:

public slots:
private:
    Logger* log;
    void init();
    JTextField* _systemName;// = new JTextField(12);
    JTextField* _userName;// = new JTextField(22);
    QCheckBox* _autoSystemName;// = new QCheckBox(trg("LabelAutoSysName"));
    QString systemNameAuto;// = this.getClass().getName()+".AutoSystemName";
    UserPreferencesManager* pref;
    
    JmriJFrame* addFrame;// = NULL;
    AddFrameWindowListener2* addFrameWindowListener;
    QWidget* centralWidget;
    QHBoxLayout* horizontalLayout_systemName;
    QHBoxLayout* horizontalLayout_userName;
    QHBoxLayout* horizontalLayout_show;
    QVBoxLayout* verticalLayout;
    QVBoxLayout* verticalLayout_2;
    QHBoxLayout* horizontalLayout_sound_script;
    QHBoxLayout* p31;
    QVBoxLayout* verticalLayout_3;
    QHBoxLayout* P32;
    QHBoxLayout* horizontalLayout_8;
    QHBoxLayout* horizontalLayout_7;
    QHBoxLayout* horizontalLayout_10;
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout_4;
    QHBoxLayout* horizontalLayout_2;
    QVBoxLayout* verticalLayout_5;
    QHBoxLayout* horizontalLayout_3;
    QVBoxLayout* verticalLayout_6;
    QHBoxLayout* horizontalLayout_4;
    QHBoxLayout* horizontalLayout_9;
    QHBoxLayout* horizontalLayout_11;
    QHBoxLayout* horizontalLayout_12;
    QHBoxLayout* horizontalLayout_13;
    RouteTurnoutModel* _routeTurnoutModel;
    QTableView* routeTurnoutTable;
    QScrollArea* _routeTurnoutScrollPane;
    RouteSensorModel* _routeSensorModel;
    QTableView* routeSensorTable;
    JTextField* soundFile;// = new JTextField(20);
    JTextField* scriptFile;// = new JTextField(20);
    JmriBeanComboBox* turnoutsAlignedSensor;
    
    JmriBeanComboBox* sensor1;
    
    QComboBox*  sensor1mode;// = new JComboBox(sensorInputModes);
    JmriBeanComboBox* sensor2;
    QComboBox*  sensor2mode;// = new JComboBox(sensorInputModes);
    JmriBeanComboBox* sensor3;
    QComboBox*  sensor3mode;// = new JComboBox(sensorInputModes);
    
    JmriBeanComboBox* cTurnout;
    JmriBeanComboBox* cLockTurnout;
    JTextField* timeDelay;// = new JTextField(5);
    
    QComboBox* cTurnoutStateBox;// = new JComboBox(turnoutInputModes);
    QComboBox* cLockTurnoutStateBox;// = new JComboBox(lockTurnoutInputModes);
    
    QButtonGroup* selGroup;// = NULL;
    QRadioButton* allButton;// = NULL;
    QRadioButton* includedButton;// = NULL;
      
    QLabel* nameLabel;// = new QLabel("Route System Name:");
    QLabel* userLabel;// = new QLabel("Route User Name:");
    QLabel* fixedSystemName;// = new QLabel("xxxxxxxxxxx");
    QLabel* label;
    QLabel* label_2;
    QLabel* label_3;
    QLabel* label_4;
    QLabel* label_5;
    QLabel* label_6;
    QLabel* label_7;
    QLabel* label_8;
    QLabel* label_9;
    QLabel* label_10;
    QLabel* label_11;
    QLabel* label_12;
    QLabel* label_13;
    QLabel* label_14;
    QLabel* label_15;
    QLabel* label_16;
    QLabel* label_17;
    QLabel* label_18;
    QLabel* label_19;
    QLabel* label_20;
    QLabel* label_21;
    QLabel* label_22;
    QLabel* label_23;
    QLabel* label_24;
    QLabel* p2xtSpace;
    QLabel* p2xsSpace;

    QLabel* sensorThatActivates;
    QLabel* sensorsThatTrigger;
    QLabel* lblEditInst;
    QLabel* lblCreateInst;
    QPushButton* setSound;
    QPushButton* setScript;
    QPushButton* createButton;// = new QPushButton("Add Route");
    QPushButton* editButton;// = new QPushButton("Edit Route");
    QPushButton* deleteButton;// = new QPushButton("Delete Route");
    QPushButton* updateButton;// = new QPushButton("Update Route");
    QPushButton* cancelButton;// = new QPushButton("Cancel");
    QPushButton* exportButton;// = new QPushButton("Export to Logix");
    
    static QString createInst;// = "To create a new Route, enter definition, then click 'Add Route'.";
    static QString editInst;// = "To edit an existing Route, enter system name, then click 'Edit Route'.";
    static QString updateInst;// = "To change this Route, make changes above, then click 'Update Route'.";
    static QString cancelInst;// = "To leave Edit mode, without changing this Route, click 'Cancel',";
    
    QVBoxLayout* centralWidgetLayout;
    QLabel* status1;// = new QLabel(createInst);
    QLabel* status2;// = new QLabel(editInst);
    
    QHBoxLayout* p2xt;// = NULL;   // Turnout list table
    QHBoxLayout* p2xs;// = NULL;   // Sensor list table
    
    QFrame* ps;
    QFrame* frame;
    QFrame* frame_2;
    QFrame* frame_3;
    QFrame* frame_4;
    Route* curRoute;// = NULL;
    bool routeDirty;// = false;  // true to fire reminder to save work
    bool editMode;// = false;
    /*private*/ bool showAll;// = true;   // false indicates show only included Turnouts
    
    /*private*/ static int ROW_HEIGHT;
    /*private*/ static QStringList COLUMN_NAMES;// = QStringList() << tr("System Name") <<
//                                            tr("ColumnLabelUserName") <<
//                                            tr("ColumnLabelInclude") <<
//                                            tr("ColumnLabelSetState");
    /*private*/ static QString SET_TO_ACTIVE;// = rbx.getString("Set")+" "+rbx.getString("SensorActive");
    /*private*/ static QString SET_TO_INACTIVE;// = rbx.getString("Set")+" "+rbx.getString("SensorInactive");
    /*private*/ static QString SET_TO_CLOSED;// = rbx.getString("Set")+" "+
//                                            InstanceManager.turnoutManagerInstance().getClosedText();
    /*private*/ static QString SET_TO_THROWN;// = rbx.getString("Set")+" "+
//                                            InstanceManager.turnoutManagerInstance().getThrownText();
    /*private*/ static QString SET_TO_TOGGLE;// = rbx.getString("Set")+" "+rbx.getString("Toggle");
    /*private*/ static QStringList sensorInputModes;// = new QStringList(){"On Active", "On Inactive", "On Change", "Veto Active", "Veto Inactive"};
    /*private*/ static QList<int> sensorInputModeValues;// =  QList<int>() <<Route::ONACTIVE << Route::ONINACTIVE << Route::ONCHANGE << Route::VETOACTIVE << Route::VETOINACTIVE;
        
    /*private*/ static QStringList turnoutInputModes;// = QStringList() << "On "+InstanceManager::turnoutManagerInstance().getClosedText(),
//                                            "On "+InstanceManager.turnoutManagerInstance().getThrownText(),
//                                            "On Change", "Veto Closed", "Veto Thrown"};
    /*private*/ static QList<int> turnoutInputModeValues;// = new int[]{Route::ONCLOSED, Route::ONTHROWN, Route::ONCHANGE,
//                                            Route::VETOCLOSED, Route::VETOTHROWN};
    
    /*private*/ static QStringList lockTurnoutInputModes;// =  QStringList() << "On "+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText(),
//                                            "On "+InstanceManager.turnoutManagerInstance().getThrownText(),
//                                            "On Change"};
    ///*private*/ static int[] lockTurnoutInputModeValues = new int[]{Route::ONCLOSED, Route::ONTHROWN, Route::ONCHANGE};    
    
    /*private*/ QList <RouteTurnout*>* _turnoutList;      // array of all Turnouts
    /*private*/ QList <RouteTurnout*>* _includedTurnoutList;
    
    /*private*/ QList <RouteSensor*>* _sensorList;        // array of all Sensorsy
    /*private*/ QList <RouteSensor*>* _includedSensorList;
    void initializeIncludedList();
    bool checkNewNamesOK();
    Route* checkNamesOK();
    int setTurnoutInformation(Route* g);
    int setSensorInformation(Route* g);
    void setControlInformation(Route* g);
//    JFileChooser soundChooser = NULL;
    void finishUpdate();
    void clearPage();
    void cancelEdit();
    void cancelIncludedOnly();
    int sensorModeFromBox(QComboBox* box);
    void setSensorModeBox(int mode, QComboBox* box);
    int turnoutModeFromBox(QComboBox* box);
    void setTurnoutModeBox(int mode, QComboBox* box);
    void retranslateUi(JmriJFrame *addFrame);
    //QMenu* windowMenu;
    JmriJFrame* f;

private slots:
    void autoSystemName(); // SLOT[]
    void on_allButton_toggled(bool);
    void exportPressed();  // SLOT[]
    void createPressed(/*ActionEvent e*/);
    void editPressed(/*ActionEvent e*/); // SLOT[]
    void deletePressed(/*ActionEvent e*/); // [slot]
    void updatePressed(/*ActionEvent* e,*/ bool newRoute = false);// // [slot]
    void cancelPressed(/*ActionEvent e*/); // [slot]
    void on_includedButton_toggled();
    void setSoundPressed();
    //void on_windowMenu_aboutToShow();

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);
protected:
    /*protected*/ QString getClassName();
    //RouteTableDataModel* m;
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();


friend class RouteElement;
friend class RouteSensor;
friend class RouteTurnout;
friend class RouteTurnoutModel;
friend class RouteSensorModel;
friend class RouteOutputModel;
friend class RouteWidget;
friend class ComboBoxDelegate;
friend class AddFrameWindowListener2;
friend class WindowMaker;
friend class RouteTableDataModel;
};
Q_DECLARE_METATYPE(RouteTableAction)
///*public*/ /*abstract*/ class RouteOutputModel : public QAbstractTableModel //implements PropertyChangeListener

//{
//    Q_OBJECT
// public:
// enum COLUMNS
// {
//  SNAME_COLUMN = 0,
//  UNAME_COLUMN = 1,
//  INCLUDE_COLUMN = 2,
//  STATE_COLUMN = 3
// };
// RouteOutputModel(RouteTableAction* self);

//// /*public*/ QString getColumnClass(int c);
// /*public*/ void propertyChange(PropertyChangeEvent* e);
// /*public*/ void dispose();
//// /*public*/ QString getColumnName(int c);
// /*public*/ int columnCount (const QModelIndex &parent) const;
// ///*public*/ bool isCellEditable(int r,int c);
// //virtual int rowCount(const QModelIndex &parent) const;
// virtual QVariant data(const QModelIndex &index, int role) const=0;
// virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
// virtual Qt::ItemFlags flags(const QModelIndex &index) const;
// virtual bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) =0;
// RouteTableAction* self;
//};
class RouteTurnoutModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum COLUMNS
    {
     SNAME_COLUMN = 0,
     UNAME_COLUMN = 1,
     INCLUDE_COLUMN = 2,
     STATE_COLUMN = 3
    };
    RouteTurnoutModel(RouteTableAction* self);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    void reset();

private:
    Logger* log;
    RouteTableAction* self;

};

class RouteSensorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum COLUMNS
    {
     SNAME_COLUMN = 0,
     UNAME_COLUMN = 1,
     INCLUDE_COLUMN = 2,
     STATE_COLUMN = 3
    };
    RouteSensorModel(RouteTableAction* self);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    void reset();

private:
    Logger* log;
    RouteTableAction* self;
};
/*private*/ /*abstract*/ class RouteElement : public QObject
{
    Q_OBJECT
public:
    QString _sysName;
    QString _userName;
    bool _included;
    int _setToState;

    RouteElement(QString sysName, QString userName) {
        _sysName = sysName;
        _userName = userName;
        _included = false;
        _setToState = Sensor::INACTIVE;
    }
    QString getSysName() {
        return _sysName;
    }
    QString getUserName() {
        return _userName;
    }
    bool isIncluded() {
        return _included;
    }

    QString getDisplayName(){
        QString name = getUserName();
        if (name != NULL && name.length() > 0) {
            return name;
        } else {
            return getSysName();
        }

    }
    void setIncluded(bool include) {
        _included = include;
    }
    /*abstract*/ virtual QString getSetToState() = 0;
    /*abstract*/ virtual void setSetToState(QString state) = 0;
    int getState() {
        return _setToState;
    }
    void setState(int state) {
        _setToState = state;
    }
};
/*private*/ class RouteTurnout : public RouteElement
{
    Q_OBJECT
public:
    RouteTurnout(QString sysName, QString userName) : RouteElement(sysName, userName)

    {
        //super(sysName, userName);SET_TO_TOGGLE
    }
    QString getSetToState()
    {
     switch (_setToState)
     {
     case Turnout::CLOSED:
        return RouteTableAction::SET_TO_CLOSED;
     case Turnout::THROWN:
        return RouteTableAction::SET_TO_THROWN;
     case Route::TOGGLE:
        return RouteTableAction::SET_TO_TOGGLE;
     }
     return "";
    }
    void setSetToState(QString state) {
        if (RouteTableAction::SET_TO_CLOSED==(state)) {
            _setToState = Turnout::CLOSED;
        } else if (RouteTableAction::SET_TO_THROWN==(state)) {
            _setToState = Turnout::THROWN;
        } else if (RouteTableAction::SET_TO_TOGGLE==(state)) {
            _setToState = Route::TOGGLE;
        }
    }
};
/*private*/ class RouteSensor : public  RouteElement
{
    Q_OBJECT
public:
    RouteSensor (QString sysName, QString userName) : RouteElement(sysName, userName)
    {
        //super(sysName, userName);
    }
    QString getSetToState() {
        switch (_setToState) {
            case Sensor::INACTIVE:
                return RouteTableAction::SET_TO_INACTIVE;
            case Sensor::ACTIVE:
                return RouteTableAction::SET_TO_ACTIVE;
            case Route::TOGGLE:
                return RouteTableAction::SET_TO_TOGGLE;
        }
        return "";
    }
    void setSetToState(QString state) {
        if (RouteTableAction::SET_TO_INACTIVE==(state)) {
            _setToState = Sensor::INACTIVE;
        } else if (RouteTableAction::SET_TO_ACTIVE==(state)) {
            _setToState = Sensor::ACTIVE;
        } else if (RouteTableAction::SET_TO_TOGGLE==(state)) {
            _setToState = Route::TOGGLE;
        }
    }
};
class ComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
  ComboBoxDelegate(QStringList items, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  QStringList Items;

};

class AddFrameWindowListener2 : public WindowListener
{
    Q_OBJECT
   RouteTableAction* self;
  public:
   AddFrameWindowListener2(RouteTableAction* self);
   void windowClosing(QCloseEvent *e);
   void windowDeiconified(QResizeEvent */*e*/){}
   void windowIconified(QResizeEvent */*e*/){}
};
class RouteTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    RouteTableAction* action;
    Logger* log;
public:
    enum COLUMNS
    {
     ENABLECOL = /*NUMCOLUMN*/5,
     LOCKCOL = ENABLECOL+1,
     SETCOL = ENABLECOL+2
    };

 RouteTableDataModel(RouteTableAction* parent);
 int columnCount(const QModelIndex &parent) const;
 QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int getPreferredWidth(int col);
 Qt::ItemFlags flags(const QModelIndex &index) const;
 QVariant data(const QModelIndex &index, int role) const;
 bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void configureTable(JTable* table);
 void doDelete(NamedBean* bean);
 /*public*/ Manager* getManager();
 /*public*/ NamedBean* getBySystemName(QString name) const;
 /*public*/ NamedBean* getByUserName(QString name) ;
 /*/*public*/ int getDisplayDeleteMsg();
 /*public*/ void clickOn(NamedBean* t);
 /*public*/ QString getValue(QString s) const;
 /*public*/ QPushButton* configureButton();
 /*protected*/ QString getBeanType();
 /*protected*/ void showPopup(QMouseEvent* e);
protected:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 /*protected*/ QString getMasterClassName();

};
class WindowMaker : public Runnable
{
 Q_OBJECT

    int row;
    RouteTableAction* action;
public:
    WindowMaker(int r, RouteTableAction* action){
        this->action = action;
        row = r;
    }
    /*public*/ void run() {
            //Thread.yield();
            action->addPressed(NULL);
            action->_systemName->setText(action->m->data(action->m->index(row, RouteTableDataModel::SYSNAMECOL),Qt::DisplayRole).toString());
            action->editPressed(); // don't really want to stop Route w/o user action
        }
    };

#endif // ROUTETABLEACTION_H
