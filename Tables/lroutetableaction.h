#ifndef LROUTETABLEACTION_H
#define LROUTETABLEACTION_H

#include <QObject>
#include "../LayoutEditor/beantabledatamodel.h"
#include <QItemDelegate>
#include "windowlistener.h"
#include "abstracttableaction.h"
#include "libtables_global.h"

class JFileChooser;
class AddFrameWindowListener;
class ConditionalVariable;
class ConditionalAction;
class RouteInputModel;
class RouteOutputModelX;
class LAlignElement;
class AlignmentModel;
class QComboBox;
class LRouteOutputElement;
class LRouteInputElement;
class Logix;
class QPushButton;
class QCheckBox;
class QRadioButton;
class QFrame;
class JActionEvent;
class LBeanTableDataModel;
class JTable;
class JmriJFrame;
class LogixManager;
class JTextField;
class ConditionalManager;
class LIBTABLESSHARED_EXPORT LRouteTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LRouteTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ LRouteTableAction(QString s, QObject *parent = 0);
    ~LRouteTableAction() {}
    LRouteTableAction(const LRouteTableAction&);
    /*public*/ void setEnabled(bool newValue);
    /*protected*/ void createModel();
    static /*public*/ /*final*/ int ENABLECOL;// = VALUECOL;
    static /*public*/ /*final*/ int EDITCOL;// = DELETECOL;

    /*public*/ /*final*/ static QString LOGIX_SYS_NAME;// = "RTX";
    /*public*/ /*final*/ static QString LOGIX_INITIALIZER;// = LOGIX_SYS_NAME+"INITIALIZER";
    /*public*/ /*final*/ static QString CONDITIONAL_SYS_PREFIX;// = LOGIX_SYS_NAME+"C";
    /*public*/ /*final*/ static QString CONDITIONAL_USER_PREFIX;// = "Route ";

    enum TYPES
    {
     SENSOR_TYPE     = 1,
     TURNOUT_TYPE    = 2,
     LIGHT_TYPE      = 3,
     SIGNAL_TYPE     = 4,
     CONDITIONAL_TYPE = 5,
     ALL_TYPE        = 6
    };
    void setupEdit(ActionEvent* /*e*/);
    void showMessage(QString msg);
    QFrame*  makeShowButtons(QRadioButton* allButton, QRadioButton* includeButton,
                       QRadioButton* extraButton, QString msg);
    void getLockConditions(QString cSysName);
    // Should not conflict with state variable types
    /*public*/ /*final*/ static int VETO;//            = 0x80;
    // due to the unecessary bit assignments in SignalHead for appearances,
    // offset the following
    /*public*/ static /*final*/ int OFFSET;//  = 0x30;
    /*public*/ static /*final*/ int SET_SIGNAL_HELD;// = Conditional.ACTION_SET_SIGNAL_HELD + OFFSET;
    /*public*/ static /*final*/ int CLEAR_SIGNAL_HELD;// = Conditional.ACTION_CLEAR_SIGNAL_HELD + OFFSET;
    /*public*/ static /*final*/ int SET_SIGNAL_DARK;// = Conditional.ACTION_SET_SIGNAL_DARK + OFFSET;
    /*public*/ static /*final*/ int SET_SIGNAL_LIT;//  = Conditional.ACTION_SET_SIGNAL_LIT + OFFSET;
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
    Q_INVOKABLE /*public*/ QString getClassDescription();
    void initializeIncludedInputList();
    void initializeIncludedOutputList();
    void  initializeIncludedAlignList();
    QList <LRouteOutputElement*>* makeTurnoutLockList();
    void finishUpdate();
    void cancelIncludedOnly();
    void clearPage();
    char getRouteConditionalType(QString logixSysName, QString cSysName);
    void getControlsAndActions(QString cSysName);
    void getAlignmentSensors(QString cSysName);
    bool removeConditionals(QString cSystemName, Logix* logix);
    int makeRouteConditional(int numConds, /*boolean onChange,*/ QList<ConditionalAction*>* actionList,
                    QList<ConditionalVariable*>* triggerList, QList<ConditionalVariable*>* vetoList,
                            Logix* logix, QString sName, QString uName, QString type);
    int makeAlignConditional(int numConds, QList<ConditionalAction*>* actionList,
                            QList<ConditionalVariable*>* triggerList,
                            Logix* logix, QString sName, QString uName);
    QList<ConditionalAction*>* cloneActionList(QList<ConditionalAction*>* actionList, int option);
    bool checkNewNamesOK();
    AddFrameWindowListener* addFrameWindowListener;
    static QString getName();


private:
    /*private*/ static QString ALIGN_SENSOR      ;//= tr("AlignSensor");
    /*private*/ static QString ALIGN_TURNOUT     ;//= tr("AlignTurnout");
    /*private*/ static QString ALIGN_LIGHT       ;//= tr("AlignLight");
    /*private*/ static QString ALIGN_SIGNAL      ;//= tr("AlignSignal");
    /*private*/ static QString ALIGN_ALL         ;//= tr("AlignAll");

    /*private*/ static QString ON_CHANGE         ;//= tr("OnChange");
    /*private*/ static QString ON_ACTIVE         ;//= tr("OnActive");
    /*private*/ static QString ON_INACTIVE       ;//= tr("OnInactive");
    /*private*/ static QString VETO_ON_ACTIVE    ;//= tr("VetoActive");
    /*private*/ static QString VETO_ON_INACTIVE  ;//= tr("VetoInactive");
    /*private*/ static QString ON_THROWN         ;//= tr("OnThrown");
    /*private*/ static QString ON_CLOSED         ;//= tr("OnClosed");
    /*private*/ static QString VETO_ON_THROWN    ;//= tr("VetoThrown");
    /*private*/ static QString VETO_ON_CLOSED    ;//= tr("VetoClosed");
    /*private*/ static QString ON_LIT            ;//= tr("OnLit");
    /*private*/ static QString ON_UNLIT          ;//= tr("OnUnLit");
    /*private*/ static QString VETO_ON_LIT       ;//= tr("VetoLit");
    /*private*/ static QString VETO_ON_UNLIT     ;//= tr("VetoUnLit");
    /*private*/ static QString ON_RED            ;//= tr("OnRed");
    /*private*/ static QString ON_FLASHRED       ;//= tr("OnFlashRed");
    /*private*/ static QString ON_YELLOW         ;//= tr("OnYellow");
    /*private*/ static QString ON_FLASHYELLOW    ;//= tr("OnFlashYellow");
    /*private*/ static QString ON_GREEN          ;//= tr("OnGreen");
    /*private*/ static QString ON_FLASHGREEN     ;//= tr("OnFlashGreen");
    /*private*/ static QString ON_DARK           ;//= tr("OnDark");
    /*private*/ static QString ON_SIGNAL_LIT     ;//= tr("OnLit");
    /*private*/ static QString ON_SIGNAL_HELD    ;//= tr("OnHeld");
    /*private*/ static QString VETO_ON_RED       ;//= tr("VetoOnRed");
    /*private*/ static QString VETO_ON_FLASHRED  ;//= tr("VetoOnFlashRed");
    /*private*/ static QString VETO_ON_YELLOW    ;//= tr("VetoOnYellow");
    /*private*/ static QString VETO_ON_FLASHYELLOW ;//= tr("VetoOnFlashYellow");
    /*private*/ static QString VETO_ON_GREEN       ;//= tr("VetoOnGreen");
    /*private*/ static QString VETO_ON_FLASHGREEN  ;//= tr("VetoOnFlashGreen");
    /*private*/ static QString VETO_ON_DARK        ;//= tr("VetoOnDark");
    /*private*/ static QString VETO_ON_SIGNAL_LIT  ;//= tr("VetoOnLit");
    /*private*/ static QString VETO_ON_SIGNAL_HELD ;//= tr("VetoOnHeld");

    /*private*/ static QString SET_TO_ACTIVE     ;//= tr("SetActive");
    /*private*/ static QString SET_TO_INACTIVE   ;//= tr("SetInactive");
    /*private*/ static QString SET_TO_CLOSED     ;//= tr("SetClosed");
    /*private*/ static QString SET_TO_THROWN     ;//= tr("SetThrown");
    /*private*/ static QString SET_TO_TOGGLE     ;//= tr("SetToggle");
    /*private*/ static QString SET_TO_ON         ;//= tr("SetLightOn");
    /*private*/ static QString SET_TO_OFF        ;//= tr("SetLightOff");
    /*private*/ static QString SET_TO_DARK       ;//= tr("SetDark");
    /*private*/ static QString SET_TO_LIT        ;//= tr("SetLit");
    /*private*/ static QString SET_TO_HELD       ;//= tr("SetHeld");
    /*private*/ static QString SET_TO_CLEAR      ;//= tr("SetClear");
    /*private*/ static QString SET_TO_RED        ;//= tr("SetRed");
    /*private*/ static QString SET_TO_FLASHRED   ;//= tr("SetFlashRed");
    /*private*/ static QString SET_TO_YELLOW     ;//= tr("SetYellow");
    /*private*/ static QString SET_TO_FLASHYELLOW ;//= tr("SetFlashYellow");
    /*private*/ static QString SET_TO_GREEN      ;//= tr("SetGreen");
    /*private*/ static QString SET_TO_FLASHGREEN ;//= tr("SetFlashGreen");

    /*private*/ static QStringList ALIGNMENT_STATES    ;//= new String[] {ALIGN_SENSOR, ALIGN_TURNOUT, ALIGN_LIGHT, ALIGN_SIGNAL, ALIGN_ALL};
    /*private*/ static QStringList INPUT_SENSOR_STATES ;//= new String[] {ON_ACTIVE, ON_INACTIVE, ON_CHANGE, VETO_ON_ACTIVE, VETO_ON_INACTIVE};
    /*private*/ static QStringList INPUT_TURNOUT_STATES;//= new String[] {ON_THROWN ,ON_CLOSED, ON_CHANGE, VETO_ON_THROWN, VETO_ON_CLOSED};
    /*private*/ static QStringList INPUT_LIGHT_STATES  ;//= new String[] {ON_LIT, ON_UNLIT, ON_CHANGE, VETO_ON_LIT, VETO_ON_UNLIT};
    /*private*/ static QStringList INPUT_SIGNAL_STATES ;//= new String[] {ON_RED, ON_FLASHRED ,ON_YELLOW, ON_FLASHYELLOW, ON_GREEN,
//                                            ON_FLASHGREEN, ON_DARK, ON_SIGNAL_LIT, ON_SIGNAL_HELD, VETO_ON_RED,
//                                            VETO_ON_FLASHRED, VETO_ON_YELLOW, VETO_ON_FLASHYELLOW, VETO_ON_GREEN,
//                                            VETO_ON_FLASHGREEN, VETO_ON_DARK, VETO_ON_SIGNAL_LIT, VETO_ON_SIGNAL_HELD};
    /*private*/ static QStringList OUTPUT_SENSOR_STATES  ;//= new String[] {SET_TO_ACTIVE, SET_TO_INACTIVE, SET_TO_TOGGLE};
    /*private*/ static QStringList OUTPUT_TURNOUT_STATES ;//= new String[] {SET_TO_CLOSED, SET_TO_THROWN, SET_TO_TOGGLE};
    /*private*/ static QStringList OUTPUT_LIGHT_STATES   ;//= new String[] {SET_TO_ON, SET_TO_OFF, SET_TO_TOGGLE};
    /*private*/ static QStringList OUTPUT_SIGNAL_STATES ;//= new String[] {SET_TO_DARK, SET_TO_LIT, SET_TO_HELD, SET_TO_CLEAR,
//                                                        SET_TO_RED, SET_TO_FLASHRED, SET_TO_YELLOW,
//                                                        SET_TO_FLASHYELLOW, SET_TO_GREEN, SET_TO_FLASHGREEN};
    void buildLists();
    JFileChooser* soundChooser;// = NULL;


public slots:
    void editPressed(QString sName);
    void makeEditWindow();
    Logix* checkNamesOK();
    void initializePressed();
    void newRoutePressed();
    void cancelPressed(ActionEvent* e = 0);
    void inputAllButtonPressed();
    void includedInputButtonPressed();
    void outputAllButtonPressed();
    void alignAllButtonPressed();
    void includedAlignButtonPressed();
    void includedOutputButtonPressed();
    void updatePressed();
    void createPressed(ActionEvent* e = 0);
    void deletePressed(ActionEvent* e = 0);

signals:

public slots:

private:
    void common();
    ConditionalManager* _conditionalManager;// = null;
    LogixManager* _logixManager;// = null;

    JTextField* _systemName;// = new JTextField(15);
    JTextField* _userName;// = new JTextField(25);

    JmriJFrame* _addFrame;// = NULL;

    RouteInputModel* _inputModel;
    //JScrollPane _inputScrollPane;
    QComboBox* _testStateCombo;
    QRadioButton* _inputAllButton;
    bool _showAllInput;

    RouteOutputModelX* _outputModel;
    //JScrollPane _outputScrollPane;
    QComboBox* _setStateCombo;
    QRadioButton* _outputAllButton;
    bool _showAllOutput;

    AlignmentModel* _alignModel;
    QComboBox* _alignCombo;
    QRadioButton* _alignAllButton;
    bool _showAllAlign;

    QCheckBox* _lockCheckBox;
    bool _lock;// = false;

    QFrame* _typePanel;
    QRadioButton* _newRouteButton;
    bool _newRouteType;// = true;
    QRadioButton* _initializeButton;
    bool _initialize;// = false;

    JTextField* soundFile;// = new JTextField(30);
    JTextField* scriptFile;// = new JTextField(30);

    QPushButton* createButton;// = new JButton(rbx.getString("ButtonCreate"));
    QPushButton* deleteButton;// = new JButton(rbx.getString("ButtonDelete"));
    QPushButton* updateButton;// = new JButton(rbx.getString("ButtonUpdate"));
    QPushButton* cancelButton;// = new JButton(rbx.getString("ButtonCancel"));

    bool routeDirty;// = false;  // true to fire reminder to save work

    QList <LRouteInputElement*>* _inputList;
    /*private*/ QMap <QString, LRouteInputElement*>* _inputMap;
    /*private*/ QMap <QString, LRouteInputElement*>* _inputUserMap;
    /*private*/ QList <LRouteInputElement*>* _includedInputList;

    QList <LRouteOutputElement*>* _outputList;
    /*private*/ QMap <QString, LRouteOutputElement*>* _outputMap;
    /*private*/ QMap <QString, LRouteOutputElement*>* _outputUserMap;
    /*private*/ QList <LRouteOutputElement*>* _includedOutputList;

    QList <LAlignElement*>* _alignList;
    /*private*/ QMap <QString, LAlignElement*>* _alignMap;
    /*private*/ QMap <QString, LAlignElement*>* _alignUserMap;
    /*private*/ QList <LAlignElement*>* _includedAlignList;

    bool enabled;
    JmriJFrame* f;

 Logger* log;
 /*private*/ QStringList getInputComboBoxItems(int type);
 /*private*/ QStringList getOutputComboBoxItems(int type);

    protected:
 ///*protected*/ LBeanTableDataModel* m;
 /*protected*/ QString getClassName();
protected slots:
 /*protected*/ void addPressed(ActionEvent* e = 0);
 /*protected*/ void setTitle();
 /*protected*/ QString helpTarget();

    friend class LBeanTableDataModel;
    friend class RouteInputModel;
    friend class RouteOutputModelX;
    friend class AlignmentModel;
    friend class LRouteInputSensor;
    friend class LRouteInputTurnout;
    friend class LRouteOutputSensor;
    friend class LRouteOutputTurnout;
    friend class LAlignElement;
    friend class LRouteOutputLight;
    friend class LRouteOutputSignal;
    friend class LRouteInputLight;
    friend class LRouteInputSignal;
    friend class LRouteWidget;
    friend class LComboBoxDelegate;
    friend class AddFrameWindowListener;
};
Q_DECLARE_METATYPE(LRouteTableAction)

class LBeanTableDataModel : public BeanTableDataModel
{
    Q_OBJECT

public:
 static /*public*/ /*final*/ int ENABLECOL;// = VALUECOL;
 static /*public*/ /*final*/ int EDITCOL;// = DELETECOL;
 LBeanTableDataModel(QObject* parent);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
// /*public*/ int getPreferredWidth(int col);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ virtual Manager* getManager();
 /*public*/ virtual NamedBean* getBySystemName(QString name) const;
 /*public*/ virtual NamedBean* getByUserName(QString name);
 /*public*/ int getDisplayDeleteMsg() ;
 /*public*/ void setDisplayDeleteMsg(int boo);
 /*public*/ void configureTable(JTable* table) ;
 // Not needed - here for interface compatibility
 /*public*/ void clickOn(NamedBean* t) ;
 /*public*/ QString getValue(QString s) const;
 // ovewrdife to get right width
 void setupEdit(JActionEvent* e = 0);
 void finishUpdate() ;
 void clearPage();
 void cancelIncludedOnly();
 //QString getBeanType();

private:
 Logger* log;
 LRouteTableAction* self;
protected:
 /*protected*/ QString enabledString;// = tr("Enabled");
 /*protected*/ /*synchronized*/ void updateNameList();
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 /*protected*/ QString getMasterClassName();
 /*protected*/ void configDeleteColumn(JTable* table);
 /*protected*/ void configValueColumn(JTable* table);
 /*protected*/ QString getBeanType();
 void doDelete(NamedBean* bean);

friend class LRouteWidget;
};

/*public*/ /*abstract*/ class RouteElementModel : public  QAbstractTableModel //implements PropertyChangeListener
{
 Q_OBJECT
  RouteElementModel(LRouteTableAction* self);
 public:
  enum COLUMNS
  {
   SNAME_COLUMN = 0,
   UNAME_COLUMN = 1,
   TYPE_COLUMN = 2,
   INCLUDE_COLUMN = 3,
   STATE_COLUMN = 4
  };

  virtual /*public*/ bool isInput();

  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ void dispose();
  void fireTableDataChanged();
  Logger* log;
public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
  LRouteTableAction* self;
  friend class RouteInputModel;
  friend class RouteOutputModelX;
  friend class AlignmentModel;
};
class RouteInputModel : public RouteElementModel
{
 Q_OBJECT

public:
 RouteInputModel(LRouteTableAction* self);
 /*public*/ bool isInput();
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};
class RouteOutputModelX : public RouteElementModel
{
    Q_OBJECT
public:
 RouteOutputModelX(LRouteTableAction* self);
 /*public*/ bool isInput();
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

class AlignmentModel : public RouteElementModel
{
    Q_OBJECT
 public:
    AlignmentModel(LRouteTableAction* self);
    /*public*/ bool isInput();
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

class LRouteElement :  public QObject
{
 Q_OBJECT
 QString _sysName;
 QString _userName;
 int _type;
 QString _typeString;
 bool _included;
 int _state;
public:
 LRouteElement(QString sysName, QString userName, int type, QObject* parent = 0);
 QString getSysName();
 QString getUserName();
 int getType();
 QString getTypeString();
 bool isIncluded();
 void setIncluded(bool include);
 int getState();
 void setState(int state) ;
 friend class LRouteInputSensor;
 friend class LRouteInputTurnout;
 friend class LRouteOutputSensor;
 friend class LRouteOutputTurnout;
 friend class LAlignElement;
 friend class LRouteOutputLight;
 friend class LRouteOutputSignal;
 friend class LRouteInputLight;
 friend class LRouteInputSignal;
};
/*abstract*/ class LRouteInputElement : public LRouteElement
{
 Q_OBJECT
public:
    LRouteInputElement(QString sysName, QString userName, int type, QObject* parent = 0);
    /*abstract*/ virtual QString getTestState();
    /*abstract*/ virtual void setTestState(QString state);
};

class LRouteInputSensor : public  LRouteInputElement
{
 Q_OBJECT
public:
 LRouteInputSensor (QString sysName, QString userName, QObject* parent = 0) ;
 QString getTestState();
 void setTestState(QString state);
};

class LRouteInputTurnout : public LRouteInputElement
{
 Q_OBJECT
public:
 LRouteInputTurnout (QString sysName, QString userName, QObject* parent = 0);
 QString getTestState();
 void setTestState(QString state);
};
class LRouteInputLight :  public LRouteInputElement
{
    Q_OBJECT
   public:
LRouteInputLight (QString sysName,QString userName, QObject* parent = 0);
QString getTestState() ;
void setTestState(QString state);
};

class LRouteInputSignal : public LRouteInputElement {
    Q_OBJECT
   public:
LRouteInputSignal (QString sysName, QString userName, QObject* parent = 0);
QString getTestState();
void setTestState(QString state);
};

/*abstract*/ class LRouteOutputElement : public LRouteElement
{
    Q_OBJECT
   public:
 LRouteOutputElement(QString sysName, QString userName, int type, QObject* parent = 0 );
/*abstract*/ virtual QString getSetToState();
/*abstract*/ virtual void setSetToState(QString state);
};

class LRouteOutputSensor : public LRouteOutputElement
{
 Q_OBJECT
public:
 LRouteOutputSensor (QString sysName, QString userName, QObject* parent = 0);
 QString getSetToState();
void setSetToState(QString state);
};

class LRouteOutputTurnout : public  LRouteOutputElement
{
 Q_OBJECT
public:
 LRouteOutputTurnout(QString sysName, QString userName, QObject* parent = 0);
 QString getSetToState();
 void setSetToState(QString state);
};
class LRouteOutputLight : public LRouteOutputElement
{
    Q_OBJECT
   public:
LRouteOutputLight(QString sysName, QString userName, QObject* parent = 0) ;
QString getSetToState() ;
void setSetToState(QString state);

};

class LRouteOutputSignal : public  LRouteOutputElement
{
    Q_OBJECT
   public:
LRouteOutputSignal(QString sysName, QString userName, QObject* parent = 0);
QString getSetToState();
void setSetToState(QString state);
};
class LAlignElement : public  LRouteElement {
    Q_OBJECT
   public:
LAlignElement(QString sysName, QString userName, QObject* parent = 0);
QString getAlignType();
void setAlignType(QString state);
};

class LComboBoxDelegate : public JComboBoxEditor
{
Q_OBJECT
public:
  LComboBoxDelegate(RouteElementModel* model, LRouteTableAction* self, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//  void setEditorData(QWidget *editor, const QModelIndex &index) const;
//  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  RouteElementModel* model;
  LRouteTableAction* self;
};

class AddFrameWindowListener : public WindowListener
{
  Q_OBJECT
 LRouteTableAction* self;
public:
 AddFrameWindowListener(LRouteTableAction* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent */*e*/){}
 void windowIconified(QResizeEvent */*e*/){}
};

#endif // LROUTETABLEACTION_H
