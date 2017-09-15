#ifndef LOGIXTABLEACTION_H
#define LOGIXTABLEACTION_H

#include <QObject>
#include <QVariant>
#include <QAbstractTableModel>
#include <QMutex>
#include "logger.h"
#include <QItemDelegate>
#include <QSignalMapper>
#include <QRadioButton>
#include "jdialog.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "windowlistener.h"
#include "libtables_global.h"
#include "abstracttableaction.h"

class EditActionFrameWindowListener;
class AddLogixFrameWindowListener;
class EditLogixFrameWindowListener;
class EditVariableFrameWindowListener;
//class VariableSignalTestStateListener;
//class VariableSignalHeadNameListener;
//class ActionSignalHeadNameListener;
//class ActionTypeListener;
class Light;
class LogixTableModel;
class QTableView;
class UserPreferencesManager;
class QCheckBox;
class DefaultUserMessagePreferences;
class QPushButton;
class ConditionalAction;
class ConditionalVariable;
class LVariableTableModel;
class ActionTableModel;
class QComboBox;
class QRadioButton;
class Logix;
class Conditional;
class PropertyChangeEvent;
class QLabel;
class ConditionalTableModel;
class JTextField;
class JmriJFrame;
class PickFrame;
class LogixManager;
class ActionEvent;
class ConditionalManager;
class LIBTABLESSHARED_EXPORT LogixTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    //explicit LogixTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ LogixTableAction(QString s = "Logix Table", QObject *parent = 0);
    ~LogixTableAction() {}
    LogixTableAction(const LogixTableAction&);
    /*public*/ static QString formatTime(int hour, int minute);
    /*public*/ void setEnabled(bool newValue);
    void enableAll(bool enable);
    void OpenPickListTable();
    void editPressed(QString sName);
    bool checkFlags(QString sName);
    void makeEditLogixWindow();
    void swapConditional(int row);
    void messageDuplicateConditionalUserName(QString svName);
    void variableNegationChanged(int row, QString oper);
    void variableOperatorChanged(int row, QString oper);
    void makeAntecedent();
    bool alreadyEditingActionOrVariable();
    void cleanUpVariable();
    QWidget* makeTopPanel(QWidget* frame, QString title, int width, int height);
    void swapActions(int row);
    void cleanUpAction();
    void editConditionalPressed(int rx);
    void makeEditConditionalWindow();
    QWidget* makeEditPanel(QWidget* comp, QString label, QString hint);
    void copyPressed(QString sName);
    void copyConditionalToLogix(QString cSysName, Logix* srcLogix, Logix* targetLogix);
    bool checkLogixUserName(QString uName);
    bool checkLogixSysName();
    void deletePressed(QString sName);
    bool checkEditConditional();
    bool checkConditionalUserName(QString uName, Logix* logix);
    bool checkConditionalSystemName(QString sName);
    void finishDone();
    /*public*/ void setMessagePreferencesDetails();
    QWidget* makeAddLogixFrame(QString titleId, QString messageId1, QString messageId2="");
    /*public*/ QString getClassDescription();
    void editVariableFrameWindowClosing();
    void makeEditActionWindow(int row);
    static QString getName();


signals:
    void propertyChange(QString, QVariant, QVariant);
public slots:
    void editConditional(int);
    void makeEditVariableWindow(int row);
    void deleteVariablePressed();
    void deleteVariablePressed(int row);
    void checkVariablePressed(ActionEvent* e = 0);
    void copyLogixPressed(ActionEvent* e = 0);
    void deletePressed(ActionEvent* e = 0);
    void newConditionalPressed(ActionEvent* e = 0);
    void calculatePressed(ActionEvent* e = 0);
    void donePressed(ActionEvent* e = 0);
    void yesButtonPressed();
    void createPressed(ActionEvent *e = 0);
    void cancelAddPressed(ActionEvent* e = 0);
    void autoSystemName();
    void reorderPressed(ActionEvent* e = 0);
    void findEmptyPressed(ActionEvent* e = 0);
    void findOrphansPressed(ActionEvent* e = 0);
    void crossReference_requested();
    void addVariablePressed(ActionEvent* e = 0);
    void itemStateChanged(int);
    void cancelEditVariablePressed();
    void updateActionPressed();
    void updateVariablePressed();
    void cancelEditActionPressed();
    bool logicTypeChanged(ActionEvent* e = 0);
    void helpPressed(ActionEvent* e = 0);
    void addActionPressed(ActionEvent* e = 0);
    void reorderActionPressed(ActionEvent* e = 0);
    void updateConditionalPressed(ActionEvent* e = 0);
    void cancelConditionalPressed(ActionEvent* e = 0);
    void deleteConditionalPressed(QString sName = "");
    void on_actionSetButton_Pressed();
    void deleteActionPressed(int row);
    void setFileLocation(ActionEvent* e = 0);
    /*public*/ void actionSignalHeadNameListener(ActionEvent* e = 0) ;
    /*public*/ void variableSignalTestStateListener(ActionEvent* e = 0);
    /*public*/ void variableSignalHeadNameListener(ActionEvent* e = 0);
    void variableItemStateChanged(int);
    void variableSignalMastNameListener(); // SLOT[]
    void actionSignalMastNameListener(); // SLOT[]
    void _actionTypeListener(int type); // SLOT[]
    void on_actionItemType_changed(int);
    void deleteActionPressed();


private:
    // Multi use variables
    ConditionalManager* _conditionalManager;// = NULL; // set when LogixAction is created

    LogixManager* _logixManager;// = null; // set when LogixAction is created
    bool _showReminder;// = false;
    bool _suppressReminder;// = false;
    bool _suppressIndirectRef;// = false;
    bool enabled;
    QString _logixSysName;
    PickFrame* _pickTables;

    // current focus variables
    Logix* _curLogix;// = null;
    int numConditionals;// = 0;
    int conditionalRowNumber;// = 0;
    Conditional* _curConditional;// = null;

    // Edit Logix Variables
    JmriJFrame* editLogixFrame;// = NULL;
    bool inEditMode;// = false;
    bool inCopyMode;// = false;
    bool _inReorderMode;// = false;
    int _nextInOrder;// = 0;
    JTextField* editUserName;// = new JTextField(20);
    ConditionalTableModel* conditionalTableModel;// = NULL;
    QLabel* status;// = new QLabel(" ");

    // Add Logix Variables
    JmriJFrame* addLogixFrame;// = NULL;
    JTextField* _systemName;// = new JTextField(10);
    JTextField* _addUserName;// = new JTextField(10);
    QCheckBox* _autoSystemName;// = new QCheckBox(rb.getString("LabelAutoSysName"));
    QLabel* _sysNameLabel;// = new QLabel(tr("LogixSystemName"));
    QLabel* _userNameLabel;// = new QLabel(tr("LogixUserName"));
    UserPreferencesManager* prefMgr;// = InstanceManager.getDefault("UserPreferencesManager");
    QString systemNameAuto;// = this.getClass().getName()+".AutoSystemName";
    QPushButton* create;

    // Edit Conditional Variables
    bool inEditConditionalMode;// = false;
    JmriJFrame* editConditionalFrame;// = NULL;
    JTextField* conditionalUserName;// = new JTextField(22);
    /*private*/ QRadioButton* _triggerOnChangeButton;

    /*private*/ ActionTableModel* _actionTableModel;// = NULL;
    /*private*/ LVariableTableModel* _variableTableModel;// = NULL;
    /*private*/ QComboBox* _operatorBox;
    /*private*/ QComboBox* _andOperatorBox;
    /*private*/ QComboBox* _notOperatorBox;
    /*private*/ JTextField* _antecedentField;
    /*private*/ QWidget* _antecedentPanel;
    /*private*/ int _logicType;// = Conditional::ALL_AND;
    /*private*/ QString _antecedent;// = "";
    /*private*/ bool _newItem;// = false;   // marks a new Action or Variable object added

    /***  Conponents of Edit Action Windows */
    JmriJFrame* _editActionFrame;// = NULL;
    QComboBox* _actionItemTypeBox;
    QComboBox* _actionTypeBox;
    QComboBox* _actionBox;
    JTextField* _actionNameField;
    JTextField* _longActionString;
    JTextField* _shortActionString;
    QComboBox* _actionOptionBox;
    QWidget* _actionPanel;
    QWidget* _actionTypePanel;
    QWidget* _namePanel;
    QWidget* _shortTextPanel;
    QWidget* _optionPanel;

    QPushButton* _actionSetButton;
    QWidget* _setPanel;
    QWidget* _textPanel;

    /***  Conponents of Edit Variable Windows */
    JmriJFrame* _editVariableFrame;// = NULL;
    QComboBox* _variableTypeBox;
    JTextField* _variableNameField;
    QComboBox* _variableStateBox;
    QComboBox* _variableCompareOpBox;
    QComboBox* _variableSignalBox;
    QComboBox* _variableCompareTypeBox;
    JTextField* _variableData1Field;
    JTextField* _variableData2Field;
    QWidget* _variableNamePanel;
    QWidget* _variableStatePanel;
    QWidget* _variableComparePanel;
    QWidget* _variableSignalPanel;
    QWidget* _variableData1Panel;
    QWidget* _variableData2Panel;



    // Current Variable Information
    /*private*/ QList <ConditionalVariable*>* _variableList;
    /*private*/ ConditionalVariable* _curVariable;
     int _curVariableRowNumber;
    /*private*/
    // Current Action Information
    /*private*/ QList <ConditionalAction*>* _actionList;
    /*private*/ ConditionalAction* _curAction;
    /*private*/ int _curActionRowNumber;
     DefaultUserMessagePreferences* p;
     void appendToAntecedent(ConditionalVariable* variable);
     bool validateAntecedent();
     void initializeStateVariables();
     QWidget* makeButtonPanel(QPushButton* updateListener,
                            QPushButton*  cancelListener,
                            QPushButton*  deleteListener);
     /*private*/ void compareTypeChanged(int selection);
     void loadJComboBoxWithSignalAspects(QComboBox* box, QString signalName);
     void loadJComboBoxWithMastAspects(QComboBox* box, QString mastName);
     bool validateAction();
     bool validateVariable();
     QString validateSensorReference(QString name);
     QString validateLightReference(QString name);
     QString validateConditionalReference(QString name);
     QString validateLogixReference(QString name);
     QString validateRouteReference(QString name);
     QString validateMemoryReference(QString name);
     QString validateTurnoutReference(QString name);
     QString validateSignalHeadReference(QString name);
     QString validateSignalMastReference(QString name);
     bool validateIntegerReference(int actionType, QString intReference);
     bool validateInteger(int actionType, int time);
     void displayBadIntegerReference(int actionType);
     Light* getLight(QString name);
     int parseTime(QString s);
     void messageInvalidSignalHeadAppearance(QString name, QString appearance) ;
     void messageInvalidActionItemName(QString name, QString itemType);
     int getActionTypeFromBox(int itemType, int actionTypeSelection);
     void initializeActionVariables();
     void actionItemChanged(int type);
     int itemType;
     //ActionTypeListener* _actionTypeListener;
     /*private*/ void variableTypeChanged(int itemType);
     EditVariableFrameWindowListener* editVariableFrameWindowListener;
     AddLogixFrameWindowListener* addLogixFrameWindowListener;
     EditLogixFrameWindowListener* editLogixFrameWindowListener;
     EditActionFrameWindowListener* editActionFrameWindowListener;
Logger* log;
void showSaveReminder();
QCheckBox* remember;
Logix* x;
QDialog* dialog ;
 //LogixTableModel* m;
protected:
/*protected*/ QString getClassName();
/*protected*/ void createModel();
protected slots:
 /*protected*/ void addPressed(ActionEvent* e = 0);


    friend class ConditionalTableModel;
    friend class LVariableTableModel;
    friend class ActionTableModel;
    friend class LogixTableModel;
    friend class LogixWidget;
    //friend class ActionTypeListener;
    friend class VariableSignalTestStateListener;
    friend class ActionSignalHeadNameListener;
    friend class EditLogixFrameWindowListener;
};
Q_DECLARE_METATYPE(LogixTableAction)

class LIBTABLESSHARED_EXPORT RefDialog : public JDialog
{
 Q_OBJECT
    JTextField* _devNameField;
    LogixTableAction* _parent;
public:
    RefDialog(LogixTableAction* parent);
public slots:
    void deviceReportPressed(ActionEvent* e = 0);
};
class LIBTABLESSHARED_EXPORT LogixTableModel : public BeanTableDataModel
{
 Q_OBJECT
public:
 enum COLS
 {
  ENABLECOL = VALUECOL,
  EDITCOL = DELETECOL
 };
 LogixTableModel(LogixTableAction* self);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int getPreferredWidth(int col) ;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) ;
 void doDelete(NamedBean* bean);
 /*public*/ Manager* getManager();
 /*public*/ NamedBean* getBySystemName(QString name) const;
 /*public*/ NamedBean* getByUserName(QString name);
 /*public*/ int getDisplayDeleteMsg();
 /*public*/ void setDisplayDeleteMsg(int boo);
 /*public*/ void configureTable(JTable* table);
 /*public*/ QString getValue(QString s) const;
 // Not needed - here for interface compatibility
 /*public*/ void clickOn(NamedBean* t) ;

private:
LogixTableAction* self;

protected:
 /*protected*/ QString enabledString;// = tr("Enabled");
/*protected*/ QString getBeanType();
/*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
/*protected*/ QString getMasterClassName();
/*protected*/ void configDeleteColumn(QTableView* table) ;
 friend class LogixWidget;
};

/*public*/ class LIBTABLESSHARED_EXPORT ConditionalTableModel : public  QAbstractTableModel //implements PropertyChangeListener
{
 Q_OBJECT
    QMutex mutex;
    LogixTableAction* self;
public:
  enum COLUMNS
  {
   SNAME_COLUMN = 0,
   UNAME_COLUMN = 1,
   STATE_COLUMN = 2,
   BUTTON_COLUMN = 3
  };
  /*public*/ ConditionalTableModel(QObject* parent) ;
  /*synchronized*/ void updateConditionalListeners();
  bool matchPropertyName(PropertyChangeEvent* e);
  ///*public*/ Class<?> getColumnClass(int c);
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//  /*public*/ int getPreferredWidth(int col) ;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ bool  setData(const QModelIndex &index, const QVariant &value, int role);
  void fireTableRowsUpdated(int r1, int r2);
  void fireTableDataChanged();
  void fireTableRowsInserted(int r1, int r2);
  void fireTableRowsDeleted(int r1, int r2);
public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

  friend class WindowMaker;
};
/*public*/ class LIBTABLESSHARED_EXPORT LVariableTableModel : public QAbstractTableModel
{
 Q_OBJECT
public:
    enum COLUMNS
    {
     ROWNUM_COLUMN = 0,
     AND_COLUMN = 1,
     NOT_COLUMN = 2,
     DESCRIPTION_COLUMN = 3,
     STATE_COLUMN = 4,
     TRIGGERS_COLUMN = 5,
     EDIT_COLUMN = 6,
     DELETE_COLUMN = 7
    };
    LVariableTableModel(QObject* parent);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    void fireTableRowsDeleted(int row1, int row2);
    void fireTableDataChanged();
    void fireTableRowsInserted(int, int);
    void fireTableRowsUpdated(int, int);

private:
    LogixTableAction* self;
};
/*public*/ class ActionTableModel : public QAbstractTableModel
{
    Q_OBJECT
    LogixTableAction* self;
public:
    enum COLUMNS
    {
     DESCRIPTION_COLUMN = 0,
     EDIT_COLUMN = 1,
     DELETE_COLUMN = 2
    };
    ActionTableModel(QObject* parent);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    void fireTableRowsDeleted(int, int);
public slots:
    void fireTableDataChanged();
    void fireTableRowsUpdated(int, int);
    void fireTableRowsInserted(int, int);
};
#if 0
class ActionTypeListener : public /*ActionListener*/ QObject
{
    Q_OBJECT
    LogixTableAction* self;
    int _itemType;

public:
    ActionTypeListener(LogixTableAction* self);
    /*public*/ void actionPerformed(ActionEvent* e = NULL);
    /*public*/ void setItemType(int type);

};
//transient ActionListener variableSignalTestStateListener = new ActionListener() {
class VariableSignalTestStateListener : public QObject
{
 Q_OBJECT
    LogixTableAction* self;
public:
    VariableSignalTestStateListener(LogixTableAction* self);
    /*public*/ void actionPerformed(ActionEvent* e = 0) ;
};

//transient ActionListener variableSignalHeadNameListener = new ActionListener() {
class VariableSignalHeadNameListener :  public QObject
{
    Q_OBJECT
    LogixTableAction* self;
   public:
    VariableSignalHeadNameListener(LogixTableAction* self);
    /*public*/ void actionPerformed(ActionEvent e);
};
#endif
class EditVariableFrameWindowListener : public WindowListener
{
  Q_OBJECT
 LogixTableAction* self;
public:
 EditVariableFrameWindowListener(LogixTableAction* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent *){}
 void windowIconified(QResizeEvent *){}
};
class AddLogixFrameWindowListener : public WindowListener
{
  Q_OBJECT
 LogixTableAction* self;
public:
 AddLogixFrameWindowListener(LogixTableAction* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent *){}
 void windowIconified(QResizeEvent *){}
};
class EditLogixFrameWindowListener : public WindowListener
{
  Q_OBJECT
 LogixTableAction* self;
public:
 EditLogixFrameWindowListener(LogixTableAction* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent *){}
 void windowIconified(QResizeEvent *){}
};
class EditActionFrameWindowListener : public WindowListener
{
    Q_OBJECT
   LogixTableAction* self;
  public:
   EditActionFrameWindowListener(LogixTableAction* self);
   void windowClosing(QCloseEvent *e);
   void windowDeiconified(QResizeEvent *){}
   void windowIconified(QResizeEvent *){}
};

#endif // LOGIXTABLEACTION_H
