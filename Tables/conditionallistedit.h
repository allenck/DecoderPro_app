#ifndef CONDITIONALLISTEDIT_H
#define CONDITIONALLISTEDIT_H
#include "conditionaleditbase.h"
#include "jtextfield.h"
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include "conditionalvariable.h"
#include "actionevent.h"
#include "abstracttablemodel.h"

class CLESelectLogixBoxListener;
class CLESelectConditionalBoxListener;
class ActionSignalMastNameListener;
class ActionSignalHeadNameListener;
class EditActionFrameWindowListener;
class EditVariableFrameWindowListener;
class LVariableTableModel;
class EditLogixFrameWindowListener;
class ActionTypeListener;
class JFileChooser;
class VariableTableModel;
class ActionTableModel;
class ConditionalTableModel;
class ConditionalListEdit : public ConditionalEditBase
{
 Q_OBJECT
public:
 ConditionalListEdit(QObject* parent = 0);
 /*public*/ ConditionalListEdit(QString sName, QObject* parent = 0);

public slots:
 void calculatePressed(JActionEvent* e = 0);
 void donePressed(JActionEvent* e = 0);
 void deletePressed(JActionEvent* e = 0);
 /*public*/ void variableSignalTestStateListener(JActionEvent* /*e*/ = 0);
 /*public*/ void variableSignalHeadNameListener(JActionEvent* /*e*/ = 0);
 /*public*/ void bringToFront();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConditionalListEdit");
 void common();
 // ------------ Logix Variables ------------
 JmriJFrame* _editLogixFrame;// = null;
 JTextField* editUserName;// = new JTextField(20);
 QLabel* status;// = new JLabel(" ");

 // ------------ Conditional Variables ------------
 ConditionalTableModel* conditionalTableModel;// = null;
 Conditional* _curConditional;// = null;
 int _conditionalRowNumber;// = 0;
 bool _inReorderMode;// = false;
 bool _inActReorder;// = false;
 bool _inVarReorder;// = false;
 int _nextInOrder;// = 0;

 // ------------ Select Logix/Conditional Variables ------------
 QWidget* _selectLogixPanel;// = null;
 QWidget* _selectConditionalPanel;// = null;
 QComboBox* _selectLogixBox;// = new QComboBox();
 QComboBox* _selectConditionalBox;// = new QComboBox();
 QList<QString> _selectLogixList;// = new QList<QString>();
 QList<QString> _selectConditionalList;// = new QList<QString>();

 // ------------ Edit Conditional Variables ------------
 bool _inEditConditionalMode;// = false;
 JmriJFrame* _editConditionalFrame;// = null;
 JTextField* _conditionalUserName;// = new JTextField(22);
 QRadioButton* _triggerOnChangeButton;

 ActionTableModel* _actionTableModel;// = null;
 LVariableTableModel* _variableTableModel;// = null;
 QComboBox* _operatorBox;
 QComboBox* _andOperatorBox;
 QComboBox* _notOperatorBox;
 JTextField* _antecedentField;
 QWidget* _antecedentPanel;
 int _logicType;// = Conditional.ALL_AND;
 QString _antecedent;// = null;
 bool _newItem = false; // marks a new Action or Variable object was added

 // ------------ Components of Edit Variable panes ------------
 JmriJFrame* _editVariableFrame;// = null;
 QComboBox* _variableItemBox;
 QComboBox* _variableStateBox;
 JTextField* _variableNameField;
 QComboBox* _variableCompareOpBox;
 QComboBox* _variableSignalBox;
 QComboBox* _variableCompareTypeBox;
 JTextField* _variableData1Field;
 JTextField* _variableData2Field;
 QPushButton* _reorderVarButton;
 QWidget* _variableNamePanel;
 QWidget* _variableStatePanel;
 QWidget* _variableComparePanel;
 QWidget* _variableSignalPanel;
 QWidget* _variableData1Panel;
 QWidget* _variableData2Panel;
 QWidget* _variableComboNamePanel;

 // ------------ Components of Edit Action panes ------------
 JmriJFrame* _editActionFrame;// = null;
 QComboBox* _actionItemBox = nullptr;
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
 QWidget* _actionComboNamePanel;

 QPushButton* _actionSetButton;
 QWidget* _setPanel;
 QWidget* _textPanel;

 // ------------ Current Variable Information ------------
 QList<ConditionalVariable*>* _variableList;
 ConditionalVariable* _curVariable;
 int _curVariableRowNumber;
 int _curVariableItem;// = 0;
 QStringList _oldTargetNames;// = new TreeSet<String>();

 // ------------ Current Action Information ------------
 QList<ConditionalAction*>* _actionList;
 ConditionalAction* _curAction = nullptr;
 int _curActionRowNumber;
 int _curActionItem;// = 0;
 static /*final*/ int STRUT;// = 10;
 JFileChooser* sndFileChooser;// = NULL;
 JFileChooser* scriptFileChooser;// = NULL;
 JFileChooser* defaultFileChooser;// = NULL;
 ActionTypeListener* _actionTypeListener;
 EditLogixFrameWindowListener* editLogixFrameWindowListener;
 EditVariableFrameWindowListener* editVariableFrameWindowListener;
 ActionSignalHeadNameListener* _actionSignalHeadNameListener;
 ActionSignalMastNameListener* _actionSignalMastNameListener;
 void makeEditLogixWindow();
 void showSaveReminder();
 bool checkEditConditional();
 bool checkConditionalUserName(QString uName, Logix* logix);
 bool checkConditionalSystemName(QString sName);
 void makeEditConditionalWindow();
 void makeAntecedent();
 void appendToAntecedent(ConditionalVariable* /*variable*/);
 bool validateAntecedent();
 bool alreadyEditingActionOrVariable();
 void loadJComboBoxWithHeadAppearances(QComboBox* box, QString signalHeadName);
 void loadJComboBoxWithMastAspects(QComboBox* box, QString mastName);
 void loadJComboBoxWithSignalAspects(QComboBox* box, QString signalName);
 QWidget* makeTopPanel(QWidget* /*frame*/, QString title, int /*width*/, int /*height*/);
 QWidget* makeEditPanel(QWidget* comp, QString label, QString hint);
 QWidget* makeButtonPanel(QPushButton* updateAction,
                        QPushButton*  cancelAction,
                        QPushButton*  deleteAction);
 void makeEditVariableWindow(int row);
 void initializeStateVariables();
 /*private*/ void variableItemChanged(int itemType);
 void setVariableNameBox(int itemType);
 void cleanUpVariable();
 /*private*/ void compareTypeChanged(int selection);
 void loadSelectLogixBox();
 void loadSelectConditionalBox(QString logixName);
 bool validateVariable();
 void makeEditActionWindow(int row);
 void initializeActionVariables();
 void actionItemChanged(int type);
 void setActionNameBox(int itemType);
 void cleanUpAction();
 void deleteActionPressed(int row);
 int getActionTypeFromBox(int itemType, int actionTypeSelection);
 void swapConditional(int row);
 void finishDone();
 void editVariableFrameWindowClosing();
 void deleteConditionalPressed(QString sName);
 bool validateAction();
 bool validateTimeReference(int actionType, QString ref);
 bool validateTime(int actionType, float time);
 EditActionFrameWindowListener *editActionFrameWindowListener;
CLESelectLogixBoxListener* selectLogixBoxListener = nullptr;
CLESelectConditionalBoxListener* selectConditionalBoxListener = nullptr;

private slots:
 void newConditionalPressed(JActionEvent* /*e*/ = 0);
 void editConditionalPressed(int rx);
 void addVariablePressed(JActionEvent* /*e*/ = 0);
 void checkVariablePressed(JActionEvent* /*e*/ = 0);
 void variableNegationChanged(int row, QString oper);
 void variableOperatorChanged(int row, QString oper);
 void addActionPressed(JActionEvent* /*e*/ = 0);
 void reorderActionPressed(JActionEvent* /*e*/ = 0);
 void swapActions(int row);
 void updateConditionalPressed();
 void cancelConditionalPressed(JActionEvent* /*e*/= 0);
 void on_deleteConditionalPressed();
 bool logicTypeChanged(JActionEvent* /*e*/= 0);
 void helpPressed(JActionEvent* /*e*/= 0);
 void updateVariablePressed();
 void cancelEditActionPressed();
 void deleteVariablePressed();
 void deleteVariablePressed(int row);
 void variableSignalMastNameListener(); // SLOT[]
 void updateActionPressed();
 void cancelEditVariablePressed();
 void setFileLocation(JActionEvent* e =0);
 //void actionTypeListener(int type); // SLOT[]
 void actionSignalMastNameListener(); // SLOT[]
 void reorderPressed(JActionEvent* /*e*/ =0);
 void variableItemStateChanged(int);
 void itemStateChanged(int);
 void deleteActionPressed();
 void on_actionItemType_changed(int);
 void on_actionSetButton_Pressed();
 void on_actionItemBox();

protected:
 /*protected*/ QString getClassName();


 friend class EditActionFrameWindowListener;
 friend class ECFWindowListener;
 friend class EditVariableFrameWindowListener;
 friend class ActionTableModel;
 friend class LVariableTableModel;
 friend class ConditionalTableModel;
 friend class ActionTypeListener;
 friend class EditLogixFrameWindowListener;
 friend class CLESelectConditionalBoxListener;
 friend class CLESelectLogixBoxListener;
};

/*public*/ class LIBTABLESSHARED_EXPORT ConditionalTableModel : public  AbstractTableModel //implements PropertyChangeListener
{
 Q_OBJECT
    QMutex mutex;
    ConditionalListEdit* self;
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
  /*public*/ QString getColumnClass(int c);
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

/*public*/ class LIBTABLESSHARED_EXPORT LVariableTableModel : public AbstractTableModel
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
    /*public*/ QString getColumnClass(int c);
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
    ConditionalListEdit* self;
};

/*public*/ class ActionTableModel : public AbstractTableModel
{
    Q_OBJECT
    ConditionalListEdit* self;
public:
    enum COLUMNS
    {
     DESCRIPTION_COLUMN = 0,
     EDIT_COLUMN = 1,
     DELETE_COLUMN = 2
    };
    ActionTableModel(QObject* parent);
    /*public*/ QString getColumnClass(int c);
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
class ECFWindowListener : public WindowListener
{
 Q_OBJECT
 ConditionalListEdit* self;
public:
 ECFWindowListener(ConditionalListEdit* self);
 void windowClosing(QCloseEvent *e);
};

class ActionTypeListener : public /*ActionListener*/ QObject
{
    Q_OBJECT
    ConditionalListEdit* self;
    int _itemType;

public:
    ActionTypeListener( ConditionalListEdit* self);
    /*public*/ void setItemType(int type);

public slots:
    /*public*/ void actionPerformed(/*ActionEvent* e = NULL*/);
    //void on_actionSetButton_Pressed();
};
//transient ActionListener variableSignalTestStateListener = new ActionListener() {
class VariableSignalTestStateListener : public QObject
{
 Q_OBJECT
    ConditionalListEdit* self;
public:
    VariableSignalTestStateListener(ConditionalListEdit* self);
    /*public*/ void actionPerformed(JActionEvent* e = 0) ;
};
class EditLogixFrameWindowListener : public WindowListener
{
  Q_OBJECT
 ConditionalListEdit* self;
public:
 EditLogixFrameWindowListener(ConditionalListEdit* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent *){}
 void windowIconified(QResizeEvent *){}
};

class EditActionFrameWindowListener : public WindowListener
{
    Q_OBJECT
   ConditionalListEdit* self;
  public:
   EditActionFrameWindowListener(ConditionalListEdit* self);
   void windowClosing(QCloseEvent *e);
   void windowDeiconified(QResizeEvent *){}
   void windowIconified(QResizeEvent *){}
};

class EditVariableFrameWindowListener : public WindowListener
{
  Q_OBJECT
 ConditionalListEdit* self;
public:
 EditVariableFrameWindowListener(ConditionalListEdit* self);
 void windowClosing(QCloseEvent *e);
 void windowDeiconified(QResizeEvent *){}
 void windowIconified(QResizeEvent *){}
};

class CLESelectLogixBoxListener : public ActionListener
{
 Q_OBJECT
 ConditionalListEdit* self;
public:
 CLESelectLogixBoxListener(ConditionalListEdit* self);
public slots:
 void actionPerformed();
};

class CLESelectConditionalBoxListener : public ActionListener
{
 Q_OBJECT
 ConditionalListEdit* self;
public:
 CLESelectConditionalBoxListener(ConditionalListEdit* self);
public slots:
 void actionPerformed();
};

#endif // CONDITIONALLISTEDIT_H
