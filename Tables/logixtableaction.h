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
#include "actionlistener.h"
#include "jfilechooser.h"
#include "conditionaleditbase.h"
#include <QCloseEvent>

class LTAEditActionFrameWindowListener;
class ConditionalListEdit;
class ConditionalTreeEdit;
class JFileChooser;
class HtmlTextEdit;
class SelectionMode;
class AddLogixFrameWindowListener;
class EditLogixFrameWindowListener;
//class VariableSignalTestStateListener;
//class VariableSignalHeadNameListener;
//class ActionSignalHeadNameListener;
//class ActionTypeListener;
class Light;
class LogixTableModel;
class QTableView;
class UserPreferencesManager;
class QCheckBox;
class UserPreferencesManager;
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
class JTextField;
class JmriJFrame;
class PickFrame;
class LogixManager;
class JActionEvent;
class ConditionalManager;
class LIBTABLESSHARED_EXPORT LogixTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    //explicit LogixTableAction(QObject *parent = 0);
    Q_INVOKABLE /*public*/ LogixTableAction(QString s = "Logix Table", QObject *parent = nullptr);
    ~LogixTableAction() {}
    LogixTableAction(const LogixTableAction&);
    /*public*/ static QString formatTime(int hour, int minute);
    /*public*/ void setEnabled(bool newValue);
    void OpenPickListTable();
    void editPressed(QString sName);
    bool checkFlags(QString sName);
    void messageDuplicateConditionalUserName(QString svName);
    void makeAntecedent();
    bool alreadyEditingActionOrVariable();
    void cleanUpVariable();
    QWidget* makeTopPanel(QWidget* frame, QString title, int width, int height);
    void cleanUpAction();
//    void editConditionalPressed(int rx);
//    QWidget* makeEditPanel(QWidget* comp, QString label, QString hint);
    void copyPressed(QString sName);
    void copyConditionalToLogix(QString cSysName, Logix* srcLogix, Logix* targetLogix);
    bool checkLogixUserName(QString uName);
    bool checkLogixSysName();
    void deletePressed(QString sName);
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
    QWidget* makeAddLogixFrame(QString titleId, QString messageId1, QString messageId2="");
    Q_INVOKABLE /*public*/ QString getClassDescription();
    void editVariableFrameWindowClosing();
    void makeEditActionWindow(int row);
//    static QString getName();
    /*public*/ void setMenuBar(BeanTableFrame* f);
    /**
     * Input selection names.
     *
     * @since 4.7.3
     */
    /*public*/ enum SelectionMode {
        /**
         * Use the traditional text field, with the tabbed Pick List available
         * for drag-n-drop
         */
        USEMULTI,
        /**
         * Use the traditional text field, but with a single Pick List that
         * responds with a click
         */
        USESINGLE,
        /**
         * Use combo boxes to select names instead of a text field.
         */
        USECOMBO
    };
    /**
     * Conditional edit view mode
     *
     * @since 4.9.x
     */
    /*public*/ enum EditMode {
        /**
         * Use the traditional table list mode for editing conditionals
         */
        LISTEDIT,
        /**
         * Use the tree based mode for editing condtiionals
         */
        TREEEDIT
    };

signals:
    void propertyChange(QString, QVariant, QVariant);
public slots:
//    void editConditional(int);
//    void makeEditVariableWindow(int row);
//    void deleteVariablePressed();
//    void deleteVariablePressed(int row);
    void copyLogixPressed(ActionEvent* e = 0);
    void deletePressed(ActionEvent* e = 0);
//    void newConditionalPressed(ActionEvent* e = 0);
    void createPressed(ActionEvent *e = 0);
    void cancelAddPressed(ActionEvent* e = 0);
    void autoSystemName();
    void findEmptyPressed(ActionEvent* e = 0);
    void findOrphansPressed(ActionEvent* e = 0);
    void crossReference_requested();
//    void itemStateChanged(int);
//    void cancelEditVariablePressed();
//    void updateActionPressed();
//    void updateVariablePressed();
//    void cancelEditActionPressed();
//    void on_actionSetButton_Pressed();
//    void deleteActionPressed(int row);
//    /*public*/ void actionSignalHeadNameListener(ActionEvent* e = 0) ;
//    /*public*/ void variableSignalTestStateListener(ActionEvent* e = 0);
//    /*public*/ void variableSignalHeadNameListener(ActionEvent* e = 0);
//    void variableItemStateChanged(int);
//    void variableSignalMastNameListener(); // SLOT[]
//    void _actionTypeListener(int type); // SLOT[]
//    void on_actionItemType_changed(int);
//    void deleteActionPressed();
    void enableAll(bool enable);
    virtual void showSaveReminder();
    void on_noButtonClicked();
    void on_yesButtonClicked();

private:
    // Multi use variables
    ConditionalManager* _conditionalManager;// = NULL; // set when LogixAction is created

    LogixManager* _logixManager;// = null; // set when LogixAction is created
    bool _showReminder;// = false;
    //bool _suppressReminder;// = false;
    //bool _suppressIndirectRef;// = false;
    //bool enabled;
    QString _logixSysName;
    PickFrame* _pickTables;

    // current focus variables
    Logix* _curLogix;// = null;
    //int numConditionals;// = 0;
    int conditionalRowNumber;// = 0;
    //Conditional* _curConditional;// = null;

    // Edit Logix Variables
//    JmriJFrame* editLogixFrame;// = NULL;
    bool _inEditMode;// = false;
    bool _inCopyMode;// = false;
//    bool _inReorderMode;// = false;
//    int _nextInOrder;// = 0;
//    JTextField* editUserName;// = new JTextField(20);
//    QLabel* status;// = new QLabel(" ");

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
//    bool inEditConditionalMode;// = false;
//    JmriJFrame* editConditionalFrame;// = NULL;
//    JTextField* conditionalUserName;// = new JTextField(22);
//    /*private*/ QRadioButton* _triggerOnChangeButton;

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
     UserPreferencesManager* p;
     void initializeStateVariables();
     QWidget* makeButtonPanel(QPushButton* updateListener,
                            QPushButton*  cancelListener,
                            QPushButton*  deleteListener);
//     /*private*/ void compareTypeChanged(int selection);
//     void loadJComboBoxWithSignalAspects(QComboBox* box, QString signalName);
//     void loadJComboBoxWithMastAspects(QComboBox* box, QString mastName);
//     bool validateAction();
//     bool validateVariable();
//     QString validateSensorReference(QString name);
//     QString validateLightReference(QString name);
//     QString validateConditionalReference(QString name);
//     QString validateLogixReference(QString name);
//     QString validateRouteReference(QString name);
//     QString validateMemoryReference(QString name);
//     QString validateTurnoutReference(QString name);
//     QString validateSignalHeadReference(QString name);
//     QString validateSignalMastReference(QString name);
//     bool validateIntegerReference(int actionType, QString intReference);
//     bool validateInteger(int actionType, int time);
//     void displayBadIntegerReference(int actionType);
//     Light* getLight(QString name);
//     int parseTime(QString s);
     void messageInvalidSignalHeadAppearance(QString name, QString appearance) ;
     void messageInvalidActionItemName(QString name, QString itemType);
     int getActionTypeFromBox(int itemType, int actionTypeSelection);
     void initializeActionVariables();
//     void actionItemChanged(int type);
     int itemType;
     /*private*/ void variableTypeChanged(int itemType);
     AddLogixFrameWindowListener* addLogixFrameWindowListener;
     LTAEditActionFrameWindowListener* editActionFrameWindowListener;
     void loadSelectionMode();
     void setSelectionMode(SelectionMode newMode);
     bool checkConditionalUserName(QString uName, Logix* logix);
     bool checkConditionalSystemName(QString sName);

     Logger* log;
     QCheckBox* remember;
     Logix* x;
     QDialog* dialog ;
      //LogixTableModel* m;
     EditMode _editMode;
     // Save conditional reference target names before updating
     /*private*/ QSet<QString> _saveTargetNames;// = TreeSet<String>();
     /*private*/ QMap<QString, QList<QString> > _saveTargetList;// = new HashMap<>();
     SelectionMode _selectionMode;
     void loadEditorMode();
     void setEditorMode(EditMode newMode);
     QStringList selectionModes;
     QStringList editModes;
     static /*final*/ int STRUT;// = 10;
     HtmlTextEdit* buildWhereUsedListing();
     QString getWhereUsedName(QString cName);
     void browserPressed(QString sName);
     void makeBrowserWindow();
     JFileChooser* userFileChooser;// = new JFileChooser(FileUtil.getUserFilesPath());
     HtmlTextEdit* buildConditionalListing();
     JmriJFrame* condBrowserFrame;
     void handleCreateException(QString sysName);
     void loadReferenceNames(QList<ConditionalVariable*> varList, QStringList treeSet);
      ConditionalListEdit* _listEdit;// = null;
      ConditionalTreeEdit* _treeEdit;
      bool checkConditionalReferences(QString logixName);
      void deleteSourceWhereUsed();
      void updateWhereUsed(QSet<QString> newTargetNames, QString refName);
      QWidget* makeEditPanel(QWidget* comp, QString label, QString hint);

protected:
     /*protected*/ QString getClassName();
     /*protected*/ void createModel();
     /*protected*/ void setTitle();
     /*protected*/ QString helpTarget();


protected slots:
 /*protected*/ void addPressed(ActionEvent* e = 0);
 void on_useMulti_triggered();
 void on_useSingle_triggered();
 void on_useComboNameBoxes_triggered();
 void on_listEdit_triggered();
 void on_treeEdit_triggered();
 void makeWhereUsedWindow();
 void openPickListTable();
 void on_helpBrowse_triggered();
 void saveBrowserPressed();

    friend class LVariableTableModel;
    friend class ActionTableModel;
    friend class LogixTableModel;
    friend class LogixWidget;
    //friend class ActionTypeListener;
    friend class VariableSignalTestStateListener;
    friend class ActionSignalHeadNameListener;
    //friend class EditLogixFrameWindowListener;
    friend class LTALogixEventListener;
    friend class LTALogixEventListener1;
    friend class RefDialog;
};
Q_DECLARE_METATYPE(LogixTableAction)

class LIBTABLESSHARED_EXPORT RefDialog : public JDialog
{
 Q_OBJECT
    JTextField* _devNameField;
    LogixTableAction* action;
    BeanTableFrame* frame;
public:
    RefDialog(BeanTableFrame* frame, LogixTableAction* action);
public slots:
    void deviceReportPressed(JActionEvent* e = 0);
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
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ int getPreferredWidth(int col) override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 void doDelete(NamedBean* bean) override;
 /*public*/ Manager* getManager()override;
 /*public*/ NamedBean* getBySystemName(QString name) const override;
 /*public*/ NamedBean* getByUserName(QString name) override;
 /*public*/ int getDisplayDeleteMsg();
 /*public*/ void setDisplayDeleteMsg(int boo);
 /*public*/ void configureTable(JTable* table)override;
 /*public*/ QString getValue(QString s) const override;
 // Not needed - here for interface compatibility
 /*public*/ void clickOn(NamedBean* t) ;

private:
LogixTableAction* self;

protected:
 /*protected*/ QString enabledString;// = tr("Enabled");
 /*protected*/ QString getBeanType() override;
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
 /*protected*/ QString getMasterClassName() override;
 /*protected*/ void configDeleteColumn(JTable* table) override;
 /*protected*/ void configValueColumn(JTable *table) override;

};
#if 0




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


class AddLogixFrameWindowListener : public WindowListener
{
  Q_OBJECT
 LogixTableAction* self;
public:
 AddLogixFrameWindowListener(LogixTableAction* self);
 void windowClosing(QCloseEvent *e) override;
 void windowDeiconified(QResizeEvent *) override{}
 void windowIconified(QResizeEvent *) override{}
};


//class ItemDelegate : public QAbstractItemDelegate
//{
//  Q_OBJECT
// public:
//  ItemDelegate(QStringList items, QObject *parent);
//  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override ;
//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//private:
//  QStringList Items;
//  //int row;
//signals:
//private slots:
//};

class CrossReferenceActionListener : public ActionListener
{
 Q_OBJECT
 BeanTableFrame* frame;
 LogixTableAction* parent;
public:
 CrossReferenceActionListener(BeanTableFrame* frame, LogixTableAction* parent);

public slots:
 void actionPerformed() ;
};

class LTALogixEventListener : public LogixEventListener
{
 Q_OBJECT
 LogixTableAction* lta;
 QString sName;

public:
 /*public*/ LTALogixEventListener(QString sName, LogixTableAction* lta);
 /*public*/ void logixEventOccurred() override;
 QObject* self() {return (QObject*)this;}
};

class LTALogixEventListener1 : public LogixEventListener
{
 Q_OBJECT
 QString sName;
 LogixTableAction* lta;
public:
 /*public*/ LTALogixEventListener1(QString sName, LogixTableAction* lta);
 /*public*/ void logixEventOccurred() override;
 QObject* self() {return (QObject*)this;}
};

class LTAEditActionFrameWindowListener : public WindowListener
{
 Q_OBJECT
 LogixTableAction* lta;
public:
 LTAEditActionFrameWindowListener(LogixTableAction* lta);
 void windowClosing(QCloseEvent */*e*/) override;

};
#endif // LOGIXTABLEACTION_H
