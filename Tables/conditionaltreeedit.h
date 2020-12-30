#ifndef CONDITIONALTREEEDIT_H
#define CONDITIONALTREEEDIT_H
#include "conditionaleditbase.h"
#include <QPushButton>
#include <jtree.h>
#include "defaulttreemodel.h"
#include "defaultmutabletreenode.h"
#include <QLabel>
#include <QCheckBox>
#include "jtextfield.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "treeselectionevent.h"
#include "treeexpansionevent.h"
#include "treeexpansionlistener.h"
#include "treeselectionlistener.h"

class JFileChooser;
class CompareTypeBoxListener;
class SelectConditionalBoxListener;
class SelectLogixBoxListener;
class CTEVariableSignalTestStateListener;
class VariableSignalMastNameListener;
class VariableSignalHeadNameListener;
class GridBagLayout;
class GridBagConstraints;
class ConditionalTreeEdit;
class CTEActionTypeListener;
class ActionSignalHeadNameListener;
class ActionSignalMastNameListener;
class ConditionalTreeNode;
class ConditionalTreeEdit : public ConditionalEditBase
{
 Q_OBJECT
public:
 explicit ConditionalTreeEdit(QObject* parent = NULL);
 ConditionalTreeEdit(QString sName, QObject* parent = NULL);
 /*public*/ void bringToFront();


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConditionalTreeEdit");
  JmriJFrame* _editLogixFrame;// =  NULL;
  QWidget* _curDetailPanel;// = new JPanel();
 JTextField* _editLogixUserName;// = new JTextField(20);   // Logix User Name field

 // ------------ Edit detail components ------------
  QWidget* _detailGrid;// = new JPanel();
  QWidget* _detailFooter;// = new JPanel();
  QVBoxLayout* _detailFooterLayout;
  QWidget* _gridPanel;  // Child of _detailGrid, contains the current grid labels and fields
 JTextField* _editConditionalUserName;
 JTextField* _editAntecedent;
  QComboBox* _editOperatorMode;
 bool _editActive;// = false;
  QPushButton* _cancelAction;
  QPushButton* _updateAction;
 QString _pickCommand;// =  NULL;
 int _pickItem;// = 0;

 // ------------ Tree variables ------------
 JTree* _cdlTree;
 DefaultTreeModel* _cdlModel;
 DefaultMutableTreeNode* _cdlRoot;
 TreeSelectionListener* _cdlListener;
 TreePath* _curTreePath;// =  NULL;

 // ------------ Tree components ------------
 ConditionalTreeNode* _cdlNode;// =  NULL;
 ConditionalTreeNode* _varHead;// =  NULL;
 ConditionalTreeNode* _varNode;// =  NULL;
 ConditionalTreeNode* _actHead;// =  NULL;
 ConditionalTreeNode* _actNode;// =  NULL;
 ConditionalTreeNode* _leafNode;// =  NULL;

 // ------------ Current tree node variables ------------
 ConditionalTreeNode* _curNode;// =  NULL;
 QString _curNodeName;// =  NULL;
 QString _curNodeType;// =  NULL;
 QString _curNodeText;// =  NULL;
 int _curNodeRow;// = -1;

 // ------------ Button bar components ------------
  QWidget* _leftButtonBar;
  QWidget* _labelPanel;
  FlowLayout* _labelPanelLayout;
  QWidget* _addButtonPanel;
  QWidget* _toggleButtonPanel;
  QWidget* _checkButtonPanel;
  QWidget* _moveButtonPanel;
  QWidget* _deleteButtonPanel;
  QWidget* _helpButtonPanel;
 QLabel* _conditionalLabel;// = new JLabel(Bundle.getMessage("LabelConditionalActions"));  // NOI18N
 QLabel* _antecedentLabel;// = new JLabel(Bundle.getMessage("LabelAntecedentActions"));  // NOI18N
 QLabel* _logicTypeLabel;// = new JLabel(Bundle.getMessage("LabelLogicTypeActions"));  // NOI18N
 QLabel* _triggerModeLabel;// = new JLabel(Bundle.getMessage("LabelTriggerModeActions"));  // NOI18N
 QLabel* _variablesLabel;// = new JLabel(Bundle.getMessage("LabelVariablesActions"));  // NOI18N
 QLabel* _variableLabel;// = new JLabel(Bundle.getMessage("LabelVariableActions"));  // NOI18N
 QLabel* _actionsLabel;// = new JLabel(Bundle.getMessage("LabelActionsActions"));  // NOI18N
 QLabel* _actionLabel;// = new JLabel(Bundle.getMessage("LabelActionActions"));  // NOI18N

 // ------------ Current conditional components ------------
 Conditional* _curConditional;
 QList<ConditionalVariable*>* _variableList;   // Current Variable List
 QList<ConditionalAction*>* _actionList;       // Current Action List
 ConditionalVariable* _curVariable;               // Current Variable
 ConditionalAction* _curAction;                   // Current Action
 int _curVariableItem;// = 0;
 int _curActionItem;// = 0;
 QString _curConditionalName;// = "";
 QString _antecedent;
 int _logicType;
 bool _triggerMode;
 bool _newActionItem;// = false;
 bool _newVariableItem;// = false;
 QSet<QString>* _oldTargetNames;// = new TreeSet<>();

 // ------------ Select Conditional Variables ------------
  QComboBox* _selectLogixBox;// = new JComboBox<QString>();
  QComboBox* _selectConditionalBox;// = new JComboBox<QString>();
 QList<QString>* _selectLogixList;// = new ArrayList<String>();
 QList<QString>* _selectConditionalList;// = new ArrayList<String>();

 // ------------ Components of Edit Variable pane ------------
  QComboBox* _variableItemBox;
  QComboBox* _variableStateBox;
  QComboBox* _variableOperBox;
 QCheckBox* _variableNegated;
 QCheckBox* _variableTriggerActions;
 JTextField* _variableNameField;
 QLabel* _variableNameLabel;// = new JLabel(Bundle.getMessage("LabelItemName"));  // NOI18N
  QComboBox* _variableCompareOpBox;
  QComboBox* _variableSignalBox;
  QComboBox* _variableCompareTypeBox;
 QLabel* _variableMemoryValueLabel;// = new JLabel("");
 JTextField* _variableData1Field;
 JTextField* _variableData2Field;

 // ------------ Components of Edit Action pane ------------
  QComboBox* _actionItemBox;
  QComboBox* _actionTypeBox;
 QLabel* _actionTypeLabel;// = new JLabel("Type");  // NOI18N
 JTextField* _actionNameField;
 QLabel* _actionNameLabel;// = new JLabel("Name");  // NOI18N
  QComboBox* _actionBox;
 QLabel* _actionBoxLabel;// = new JLabel("Box");  // NOI18N
 JTextField* _longActionString;
 QLabel* _longActionLabel;// = new JLabel("Long");  // NOI18N
 JTextField* _shortActionString;
 QLabel* _shortActionLabel;// = new JLabel("Short");  // NOI18N
  QComboBox* _actionOptionBox;
  QPushButton* _actionSetButton;

  CTEActionTypeListener* _actionTypeListener;// = new ActionTypeListener();
  ActionSignalHeadNameListener* actionSignalHeadNameListener;
  ActionSignalMastNameListener* actionSignalMastNameListener;
  VariableSignalHeadNameListener* variableSignalHeadNameListener;
  VariableSignalMastNameListener* variableSignalMastNameListener;
  CTEVariableSignalTestStateListener* variableSignalTestStateListener;
  SelectLogixBoxListener* selectLogixBoxListener;
  SelectConditionalBoxListener* selectConditionalBoxListener;
  CompareTypeBoxListener* compareTypeBoxListener;

  JFileChooser* sndFileChooser;// =  NULL;
  JFileChooser* scriptFileChooser;// =  NULL;
  JFileChooser* defaultFileChooser;// =  NULL;



  void loadJComboBoxWithHeadAppearances(QComboBox* box, QString signalHeadName);
  void loadJComboBoxWithMastAspects(QComboBox* box, QString mastName);
  static int getActionTypeFromBox(int itemType, int actionTypeSelection);
  void initializeActionVariables();
  void actionItemChanged(int type);
  void setActionNameBox(int itemType);
  void setFocusListeners();
  void setEditMode(bool active);
  void setPickWindow(QString cmd, int item);
  void doPickList();
  void doPickSingle();
  void setMoveButtons();
  void makeDetailGrid(QString gridType);
  void makeEmptyGrid(GridBagConstraints c);
  void makeConditionalGrid(GridBagConstraints c);
  void makeAntecedentGrid(GridBagConstraints c);
  void makeLogicTypeGrid(GridBagConstraints c);
  GridBagLayout* _gridPanelLayout;
  QVBoxLayout* _detailGridLayout;
  void makeEmptyVariableGrid(GridBagConstraints c);
  void makeOptionsVariableGrid(GridBagConstraints c);
  void makeStandardVariableGrid(GridBagConstraints c);
  void makeSignalAspectVariableGrid(GridBagConstraints c);
  void makeConditionalVariableGrid(GridBagConstraints c);
  void makeMemoryVariableGrid(GridBagConstraints c);
  void makeFastClockVariableGrid(GridBagConstraints c);
  void initializeStateVariables();
  void makeEmptyActionGrid(GridBagConstraints c);
  void makeNameTypeActionGrid(GridBagConstraints c,bool finalRow);
  void makeTypeActionGrid(GridBagConstraints c,bool finalRow);
  void makeStandardActionGrid(GridBagConstraints c,bool finalRow);
  void makeShortFieldActionGrid(GridBagConstraints c,bool includeBox);
  void makeTypeShortActionGrid(GridBagConstraints c);
  void makeFileActionGrid(GridBagConstraints c);
  void makeChangeTriggerActionGrid(GridBagConstraints c);
  /*private*/ void variableTypeChanged(int itemType);
  void setVariableNameBox(int itemType);
  /*private*/ void compareTypeChanged(int testType);
  void loadSelectLogixBox();
  void loadSelectConditionalBox(QString logixName);
  bool validateVariable();
  void updateVariableOperator();
  void updateVariableNegation();
  void updateVariableList();
  void makeAntecedent();
  void appendToAntecedent(ConditionalVariable* variable);
  QString buildNodeText(QString nodeType, QObject* component, int idx);
  void showNodeEditMessage();
  void newVariable();
  void newAction();
  void cancelEditVariable();
  void cleanUpVariable();
  void updateVariable();
  void buildConditionalComponents();
  void buildActionComponents();
  void buildVariableComponents();
  void makeEditLogixWindow();
  JTree* buildConditionalTree();
  void createConditionalContent();
  void upPressed();
  void downPressed();
  QPushButton* downButton;
  QPushButton* upButton;
  void moveTreeNode(QString direction);
  void removeActionTimers();
  void updateActionList();
  void cancelEditAction();
  void cleanUpAction();
  void antecedentChanged(QString newAntecedent);
  bool validateAntecedent();
  void updateAction();
  bool validateAction();
  void setFileLocation();
  void userNameChanged(QString newName);
  void treeRowSelected(ConditionalTreeNode* selectedNode);
  void clearLayout(QLayout* layout, bool deleteWidgets = true);
  bool eventFilter(QObject *watched, QEvent *event);

private slots:
  void addPressed();
  void cancelPressed();
  void on_actionItemBox_currentIndexChanged();
  void on_actionSetButton_clicked();
  void on_variableItemBox_currentIndexChanged();
  void on_editLogixUserName_editingFinished();
  void on_upButton_clicked();
  void on_downButton_clicked();
  void deletePressed();
  void donePressed();
  void editPressed();
  void updatePressed();
  void logicTypeChanged(int newType);
  void helpPressed();
  void togglePressed();
  void checkPressed();


protected:
  /*protected*/ QString getClassName();
 friend class ActionSignalHeadNameListener;
 friend class ActionSignalMastNameListener;
 friend class CTEActionTypeListener;
 friend class VariableSignalHeadNameListener;
 friend class VariableSignalMastNameListener;
 friend class CTEVariableSignalTestStateListener;
 friend class SelectLogixBoxListener;
 friend class SelectConditionalBoxListener;
 friend class CompareTypeBoxListener;
 friend class CTEWindowListener;
 friend class CDLTreeSelectionListener;
 friend class CDLTreeExpansionListener;
};
// ------------ Action detail listeners ------------
/**
 * Listener for _actionTypeBox.
 */
class CTEActionTypeListener : public ActionListener {
Q_OBJECT
    int _itemType;
 ConditionalTreeEdit* cte;
public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0) ;
public:
    CTEActionTypeListener(ConditionalTreeEdit* cte);
    /*public*/ void setItemType(int type) ;
};

class ActionSignalHeadNameListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 ActionSignalHeadNameListener(ConditionalTreeEdit* cte);
//transient ActionListener actionSignalHeadNameListener = new ActionListener() {
public slots:
    //@Override
    /*public*/ void actionPerformed(JActionEvent* e =0);
};

class ActionSignalMastNameListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
//transient ActionListener actionSignalMastNameListener = new ActionListener() {
public:
 ActionSignalMastNameListener(ConditionalTreeEdit* cte);
public slots:
    //@Override
    /*public*/ void actionPerformed(JActionEvent* e = 0) ;
};

// ============ Conditional Tree Node Definition ============
/*static*/ class ConditionalTreeNode : public DefaultMutableTreeNode {
Q_OBJECT
    /*private*/ QString cdlText;
    /*private*/ QString cdlType;
    /*private*/ QString cdlName;
    /*private*/ int cdlRow;
public:
    /*public*/ ConditionalTreeNode(QString nameText, QString type, QString sysName, int row) ;
    /*public*/ QString getType();
    /*public*/ QString getName() ;
    /*public*/ void setName(QString newName);
    /*public*/ int getRow();
    /*public*/ void setRow(int newRow);
    /*public*/ QString getText();
    /*public*/ void setText(QString newText);
    /*public*/ QString toString() ;
};

// ------------ Variable detail listeners ------------
//transient ActionListener variableSignalHeadNameListener = new ActionListener() {
class VariableSignalHeadNameListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 VariableSignalHeadNameListener(ConditionalTreeEdit* cfe);
    //@Override
public slots:
    /*public*/ void actionPerformed();
};

//transient ActionListener variableSignalMastNameListener = new ActionListener() {
class VariableSignalMastNameListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 VariableSignalMastNameListener(ConditionalTreeEdit* cte);
public slots:
    //@Override
    /*public*/ void actionPerformed() ;
};

//transient ActionListener variableSignalTestStateListener = new ActionListener() {
class CTEVariableSignalTestStateListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 CTEVariableSignalTestStateListener(ConditionalTreeEdit* cte);
public slots:
    //@Override
    /*public*/ void actionPerformed() ;
};

//transient ActionListener selectLogixBoxListener = new ActionListener() {
class SelectLogixBoxListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 SelectLogixBoxListener(ConditionalTreeEdit* cte);
public slots:
    //@Override
    /*public*/ void actionPerformed();
};

//transient ActionListener selectConditionalBoxListener = new ActionListener() {
class SelectConditionalBoxListener : public ActionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 SelectConditionalBoxListener(ConditionalTreeEdit*cte);
public slots:
     //@Override
    /*public*/ void actionPerformed();
};

//transient ActionListener compareTypeBoxListener = new ActionListener() {
class CompareTypeBoxListener : public ActionListener
{
  Q_OBJECT
  ConditionalTreeEdit* cte;
 public:
  CompareTypeBoxListener(ConditionalTreeEdit* cte);
    //@Override
    /*public*/ void actionPerformed() ;
};

class CTEWindowListener : public WindowListener
{
 ConditionalTreeEdit* cte;
public:
 CTEWindowListener(ConditionalTreeEdit* cte) {this->cte = cte;}
 /*public*/ void windowClosing(QCloseEvent* /*e*/) {
     cte->donePressed();
 }
};

class CDLTreeSelectionListener : public TreeSelectionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 CDLTreeSelectionListener(ConditionalTreeEdit* cte);
public slots:
 /*public*/ void valueChanged(TreeSelectionEvent* e = 0);
};

class CDLTreeExpansionListener : public TreeExpansionListener
{
 Q_OBJECT
 ConditionalTreeEdit* cte;
public:
 CDLTreeExpansionListener(ConditionalTreeEdit* cte);
 QObject* self() {return (QObject*)this;}
public slots:
 /*public*/ void treeExpanded(TreeExpansionEvent* e);

 /*public*/ void treeCollapsed(TreeExpansionEvent* e);

};
#endif // CONDITIONALTREEEDIT_H
