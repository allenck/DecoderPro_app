#include "logixtableaction.h"
#include "instancemanager.h"
#include "defaultlogix.h"
#include "pickframe.h"
#include "instancemanager.h"
#include "defaultconditionalmanager.h"
#include "conditional.h"
#include "logix.h"
#include "defaultconditional.h"
#include "jtextfield.h"
#include <QMessageBox>
#include "runnable.h"
#include "../LayoutEditor/sensorgroupframe.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QGroupBox>
#include "conditionalvariable.h"
#include "conditionalaction.h"
#include <QComboBox>
#include <QButtonGroup>
#include <QFont>
#include "defaultusermessagepreferences.h"
#include <QCheckBox>
#include "gridbagconstraints.h"
#include "../LayoutEditor/inputdialog.h"
#include "../LayoutEditor/maintenance.h"
#include "logixwidget.h"
#include "lroutetableaction.h"
#include <QPushButton>
#include "abstractsignalhead.h"
#include "signalmast.h"
#include "abstractsignalmast.h"
#include "defaultsignalmastmanager.h"
#include "abstractlight.h"
#include "defaultconditionalaction.h"
#include "abstractmemorymanager.h"
#include "abstractlightmanager.h"
#include "defaultconditionalmanager.h"
#include "defaultroutemanager.h"
#include <QStringList>
#include "defaultlogixmanager.h"
#include "abstractsignalheadmanager.h"
#include "proxylightmanager.h"
#include "defaultusermessagepreferences.h"
#include "oblock.h"
#include <QLabel>
#include "pushbuttondelegate.h" // for PushButtonItemDelegate

//LogixTableAction::LogixTableAction(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Swing action to create and register a Logix Table.
 * <P>
 * Also contains the windows to create, edit, and delete a Logix. Also contains
 * the window to define and edit a Conditional::
 * <P>
 * Most of the text used in this GUI is in LogixTableBundle.properties, accessed
 * via rbx, and the remainder of the text is in BeanTableBundle.properties,
 * accessed via rb.
 *
 * Methods and Members for 'state variables' and 'actions' removed to become their
 * own objects - 'ConditionalVariable' and 'ConditionalAction' in jmri package.
 * Two more types of logic for a Conditional to use in its antecedent have been added
 * to the original 'AND'ing all statevariables - 'OR' (i.e. all OR's) and 'MIXED'
 * (i.e. general bool statement with any mixture of bool operations).
 * The 'OR's an 'AND's types are unambiguous and do not require parentheses.
 * The 'Mixed' type uses a TextField for the user to insert parenthees.
 * Jan 22, 2009 - Pete Cressman
 *
 * Conditionals now have two policies to trigger execution of their action lists.
 * 1. the previous policy - Trigger on change of state only
 * 2. the new default - Trigger on any enabled state calculation
 * Jan 15, 2011 - Pete Cressman
 *
 * @author Dave Duchamp Copyright (C) 2007
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011
 * @author Matthew Harris  copyright (c) 2009
 * @version $Revision: 22539 $
 */

///*public*/ class LogixTableAction extends AbstractTableAction {

    /**
     * Create an action with a specific title.
     * <P>
     * Note that the argument is the Action title, not the title of the
     * resulting frame. Perhaps this should be changed?
     *
     * @param s
     */
/*public*/ LogixTableAction::LogixTableAction(QString s, QObject *parent) : AbstractTableAction(s, parent)
{
        //super(s);
  log = new Logger("LogixTableAction");
 _conditionalManager = NULL; // set when LogixAction is created
 _logixManager = NULL; // set when LogixAction is created
 _showReminder = false;
 _suppressReminder = false;
 _suppressIndirectRef = false;
 _pickTables = NULL;

 // current focus variables
 _curLogix = NULL;
 numConditionals = 0;
 conditionalRowNumber = 0;
 _curConditional = NULL;

 if(parent == NULL)
  return;

 // Edit variables
 editLogixFrame = NULL;
 inEditMode = false;
 inCopyMode = false;
 _inReorderMode = false;
 _nextInOrder = 0;
 editUserName = new JTextField(20);
 conditionalTableModel = NULL;
 status = new QLabel(" ");

 // Add Logix Variables
 addLogixFrame = NULL;
 _systemName = new JTextField(10);
 _addUserName = new JTextField(10);
 _autoSystemName = new QCheckBox(tr("Automatically Generate System Name"));
 _sysNameLabel = new QLabel(tr("Logix System Name"));
 _userNameLabel = new QLabel(tr("Logix User Name"));
 prefMgr = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 systemNameAuto = QString(this->metaObject()->className())+".AutoSystemName";

 // Edit Conditional Variables
 inEditConditionalMode = false;
 editConditionalFrame = NULL;
 conditionalUserName = new JTextField(22);
 _actionTableModel = NULL;
 _variableTableModel = NULL;
 _logicType = Conditional::ALL_AND;
 _antecedent = "";
 _newItem = false;   // marks a new Action or Variable object added

 _editActionFrame = NULL;
 _editVariableFrame = NULL;
 //_actionTypeListener = new ActionTypeListener(this);
 //actionSignalHeadNameListener = new ActionSignalHeadNameListener(this);
 //variableSignalHeadNameListener = new VariableSignalHeadNameListener(this);
 //variableSignalTestStateListener = new VariableSignalTestStateListener(this);

 // set up managers - no need to use InstanceManager since both managers are
 // Default only (internal). We use InstanceManager to get managers for
 // compatibility with other facilities.
 _logixManager = InstanceManager::logixManagerInstance();
 _conditionalManager = InstanceManager::conditionalManagerInstance();
 // disable ourself if there is no Logix manager or no Conditional manager available
 if ((_logixManager == NULL) || (_conditionalManager == NULL))
 {
  setEnabled(false);
 }
}

LogixTableAction::LogixTableAction(const LogixTableAction & that) : AbstractTableAction(that.text(), that.parent())
{}
//	/*public*/ LogixTableAction() {
//		this("Logix Table");
//	}

//	static final ResourceBundle rbx = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.LogixTableBundle");

// *********** Methods for Logix Table Window ********************

/**
 * Create the JTable DataModel, along with the changes (overrides of
 * BeanTableDataModel) for the specific case of a Logix table. Note: Table
 * Models for the Conditional table in the Edit Logix window, and the State
 * Variable table in the Edit Conditional window are at the end of this
 * module.
 */
/*protected*/ void LogixTableAction::createModel()
{
 m = new LogixTableModel(this);
 AbstractManager* manager = (AbstractManager*)m->getManager();
 connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), m, SLOT(propertyChange(PropertyChangeEvent*)));
}

// overlay the state column with the edit column
LogixTableModel::LogixTableModel(LogixTableAction *self)
 : BeanTableDataModel(self)
{
 this->self = self;
 enabledString = tr("Enabled");
 //updateNameList();
 init();
}

/*public*/ QVariant LogixTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    if (section == EDITCOL)
        return ""; // no heading on "Edit"
    if (section == ENABLECOL)
        return enabledString;
 }
 return BeanTableDataModel::headerData(section,orientation, role);
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == EDITCOL)
//        return String.class;
//    if (col == ENABLECOL)
//        return Boolean.class;
//    else
//        return super.getColumnClass(col);
//}

/*public*/ int LogixTableModel::getPreferredWidth(int col) {
    // override default value for SystemName and UserName columns
    if (col == SYSNAMECOL)
                  return  JTextField(12).getPreferredSize().width();
    if (col == USERNAMECOL)
                  return  JTextField(17).getPreferredSize().width();
    if (col == EDITCOL)
                  return  JTextField(12).getPreferredSize().width();
    if (col == ENABLECOL)
                  return  JTextField(5).getPreferredSize().width();
    else
        return BeanTableDataModel::getPreferredWidth(col);
}

/*public*/ Qt::ItemFlags LogixTableModel::flags(const QModelIndex &index) const
{
 if(!index.isValid()) return Qt::NoItemFlags;
 if (index.column() == EDITCOL)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 if (index.column() == ENABLECOL)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
 else
  return BeanTableDataModel::flags(index);
}

/*public*/ QVariant LogixTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  if (index.column() == EDITCOL)
  {
   return tr("Select");
  }
  else return BeanTableDataModel::data(index, role);
 }
 else
 {
  if(role == Qt::CheckStateRole)
  {
   if (index.column() == ENABLECOL)
   {
    Logix* logix = (Logix*) getBySystemName(data(createIndex(index.row(), SYSNAMECOL),Qt::DisplayRole).toString());
    if (logix == NULL)
    {
     return QVariant();
    }
    return ((DefaultLogix*)logix)->getEnabled()?Qt::Checked:Qt::Unchecked;
   }
   //else return BeanTableDataModel::data(index, role);
  }
 }
 return QVariant();
}

/*public*/ bool LogixTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  if (index.column() == EDITCOL)
  {
   // set up to edit
    QString sName = sysNameList.at(index.row());
    if ( tr("Edit")==(value) )
    {
        self->editPressed(sName);
    } else if (tr("Copy")==(value) )
    {
        self->copyPressed(sName);
    } else if ( tr("Delete")==(value) )
    {
        self->deletePressed(sName);
    }
    return true;
  }
  else
   BeanTableDataModel::setData(index, value, role);
 }
 if(role == Qt::CheckStateRole)
 {
  if (index.column() == ENABLECOL)
  {
    // alternate
   Logix* x = (Logix*) getBySystemName(sysNameList.at(index.row()));
   bool v = ((DefaultLogix*)x)->getEnabled();
   ((DefaultLogix*)x)->setEnabled(!v);
   return true;
  }
  else
   BeanTableDataModel::setData(index, value, role);
 }
 return false;
}

/**
 * Delete the bean after all the checking has been done.
 * <P>
 * Deactivate the Logix and remove it's conditionals
 */
void LogixTableModel::doDelete(NamedBean* bean)
{
    Logix* l = (Logix*) bean;
    ((DefaultLogix*)l)->deActivateLogix();
    // delete the Logix and all its Conditionals
    ((DefaultLogixManager*)self->_logixManager)->deleteLogix(l);
}

/*protected*/ bool LogixTableModel::matchPropertyName(PropertyChangeEvent* e) {
    if (e->getPropertyName()==(enabledString))
        return true;
    else
        return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ Manager* LogixTableModel::getManager()
{
 return (DefaultLogixManager*)InstanceManager::logixManagerInstance();
 //return self->_logixManager;

}

/*public*/ NamedBean* LogixTableModel::getBySystemName(QString name) const {
    return ((DefaultLogixManager*)InstanceManager::logixManagerInstance())->getBySystemName(
            name);
}

/*public*/ NamedBean* LogixTableModel::getByUserName(QString name) {
    return ((DefaultLogixManager*)InstanceManager::logixManagerInstance())->getByUserName(
            name);
}
/*public*/ int LogixTableModel::getDisplayDeleteMsg()
{
 return ((DefaultUserMessagePreferences*)  InstanceManager::getDefault("UserPreferencesManager"))->getMultipleChoiceOption(self->getClassName(),"deleteInUse");
}
/*public*/ void LogixTableModel::setDisplayDeleteMsg(int boo)
{
 ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption(self-> getClassName(), "deleteInUse", boo);
}
/*protected*/ QString LogixTableModel::getMasterClassName() { return self->getClassName(); }


/*public*/ void LogixTableModel::configureTable(JTable* table) {

//    table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
    BeanTableDataModel::configureTable(table);

}

/**
* Replace delete button with comboBox
*/
/*protected*/ void LogixTableModel::configDeleteColumn(QTableView* table) {
//    JComboBox editCombo = new JComboBox();
//    editCombo->layout()->addWidget(new QLabel("ButtonSelect"));
//    editCombo->layout()->addWidget(new QLabel("ButtonEdit"));
//    editCombo->layout()->addWidget(new QLabel("ButtonCopy"));
//    editCombo->layout()->addWidget(new QLabel("ButtonDelete"));
//    TableColumn col = table.getColumnModel().getColumn(BeanTableDataModel.DELETECOL);
//    col.setCellEditor(new DefaultCellEditor(editCombo));
 QStringList items = QStringList() << tr("Select") << tr("Edit") << tr("Copy") << tr("Delete");
 table->setItemDelegateForColumn(BeanTableDataModel::DELETECOL, new ItemDelegate(items, this));
}

// Not needed - here for interface compatibility
/*public*/ void LogixTableModel::clickOn(NamedBean* /*t*/) {
}

/*public*/ QString LogixTableModel::getValue(QString /*s*/) {
    return "";
}

/*protected*/ QString LogixTableModel::getBeanType(){
    return tr("BeanNameLogix");
}
//    };
//}
#if 0
// set title for Logix table
protected void setTitle() {
    f.setTitle(f.rb.getString("TitleLogixTable"));
}
/*
/*public*/ void addToFrame(BeanTableFrame f) {
    // Hack into Logix frame to add my junk. (pwc)
    f->layout()->addWidgetToBottomBox(extraPanel, this.getClass().getName());
}

*/    /*public*/ void setMenuBar(BeanTableFrame f){
    JMenu menu = new JMenu(tr("OptionsMenu"));
    menu.setMnemonic(KeyEvent.VK_O);
    javax.swing.JMenuBar menuBar = f.getJMenuBar();
    /*
    if (InstanceManager::getDefault(jmri.UserPreferencesManager.class) != NULL)
        _suppressReminder = InstanceManager::getDefault(jmri.UserPreferencesManager.class).
                           getPreferenceState("beantable.LRouteTableAction.remindRoute");
    */
    ButtonGroup enableButtonGroup = new ButtonGroup();
    JRadioButtonMenuItem r = new JRadioButtonMenuItem(tr("EnableAll"));
    r->layout()->addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) { enableAll(true); }
    });
    enableButtonGroup->layout()->addWidget(r);
    r.setSelected(true);
    menu->layout()->addWidget(r);
    r = new JRadioButtonMenuItem(tr("DisableAll"));
    r->layout()->addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) { enableAll(false); }
    });
    enableButtonGroup->layout()->addWidget(r);
    menu->layout()->addWidget(r);
    menuBar->layout()->addWidget(menu);

    menu = new JMenu(tr("ToolsMenu"));
    menu.setMnemonic(KeyEvent.VK_T);

    JMenuItem item = new JMenuItem(tr("OpenPickListTables"));
    item->layout()->addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            OpenPickListTable();
        }
    });
    menu->layout()->addWidget(item);

    item = new JMenuItem(tr("FindOrphans"));
    item->layout()->addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            findOrphansPressed(e);
        }
    });
    menu->layout()->addWidget(item);

    item = new JMenuItem(tr("EmptyConditionals"));
    item->layout()->addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            findEmptyPressed(e);
        }
    });
    menu->layout()->addWidget(item);

    item = new JMenuItem(tr("CrossReference"));
    item->layout()->addActionListener(new ActionListener() {
            BeanTableFrame parent;
        /*public*/ void actionPerformed(ActionEvent e) {
            new RefDialog(parent);
        }

        ActionListener init(BeanTableFrame f) {
            parent = f;
            return this;
        }
    }.init(f));
    menu->layout()->addWidget(item);
    menuBar->layout()->addWidget(menu);
}
#endif
void LogixTableAction::crossReference_requested()
{
 RefDialog* dlg = new RefDialog(this);
 dlg->exec();
}

void LogixTableAction::OpenPickListTable() {
    if (_pickTables==NULL) {
        _pickTables = new PickFrame(tr("Pick List"));
    } else {
        _pickTables->setVisible(true);
    }
    //_pickTables->toFront();
    _pickTables->setWindowState(Qt::WindowActive) ;
}
#if 1
void LogixTableAction::findEmptyPressed(ActionEvent* /*e*/) {
            Maintenance::findEmptyPressed((QWidget*)parent());
}
void LogixTableAction::findOrphansPressed(ActionEvent* /*e*/) {
            Maintenance::findOrphansPressed((QWidget*)parent());
}
//class RefDialog extends JDialog {

RefDialog::RefDialog(LogixTableAction* parent) : JDialog()
{
 //super(frame, tr("CrossReference"), true);
 _parent = parent;
 QWidget* extraPanel = new QWidget();
 extraPanel->setLayout(new QVBoxLayout(extraPanel));
 _devNameField = new JTextField(30);
 QWidget* panel = _parent->makeEditPanel(_devNameField, "Element Name", "System or User name of an element to find where it is referenced.");
 QPushButton* referenceButton = new QPushButton(tr("Get References"));
 panel->layout()->addWidget(referenceButton);
// referenceButton->layout()->addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            deviceReportPressed(e);
//        }
//    });
 connect(referenceButton, SIGNAL(clicked()), this, SLOT(deviceReportPressed()));
 panel->layout()->addWidget(referenceButton);
 extraPanel->layout()->addWidget(panel);
    //setContentPane(extraPanel);
 setLayout(new QVBoxLayout());
 layout()->addWidget(extraPanel);
 adjustSize();
//            setLocationRelativeTo((java.awt.Component)_pos);
 setVisible(true);
 exec();
}

void RefDialog::deviceReportPressed(ActionEvent* /*e*/)
{
 Maintenance::deviceReportPressed(_devNameField->text(), NULL);
    //dispose();
 close();
}
//};
#endif
void LogixTableAction::enableAll(bool enable) {
    QStringList sysNameList = ((DefaultLogixManager*)_logixManager)->getSystemNameList();
    for (int i=0; i<sysNameList.size(); i++) {
        Logix* x = ((DefaultLogixManager*)_logixManager)->getBySystemName(sysNameList.at(i));
        ((DefaultLogix*)x)->setEnabled(enable);
    }
}
#if 0
protected String helpTarget() {
    return "package.jmri.jmrit.beantable.LogixTable";
}

// *********** variable definitions ********************



// Add Logix Variables
JmriJFrame addLogixFrame = NULL;
JTextField _systemName = new JTextField(10);
JTextField _addUserName = new JTextField(10);
JCheckBox _autoSystemName = new JCheckBox(rb.getString("LabelAutoSysName"));
QLabel* _sysNameLabel = new QLabel(tr"LogixSystemName"));
QLabel* _userNameLabel = new QLabel(tr"LogixUserName"));
jmri.UserPreferencesManager prefMgr = jmri.InstanceManager::getDefault(jmri.UserPreferencesManager.class);
String systemNameAuto = this.getClass().getName()+".AutoSystemName";
QPushButton create;



// Edit Conditional Variables
bool inEditConditionalMode = false;
JmriJFrame editConditionalFrame = NULL;
JTextField conditionalUserName = new JTextField(22);
private JRadioButton _triggerOnChangeButton;

private ActionTableModel _actionTableModel = NULL;
private VariableTableModel _variableTableModel = NULL;
private JComboBox _operatorBox;
private JComboBox _andOperatorBox;
private JComboBox _notOperatorBox;
private JTextField _antecedentField;
private QWidget* _antecedentPanel;
private int _logicType = Conditional::ALL_AND;
private String _antecedent = NULL;
private bool _newItem = false;   // marks a new Action or Variable object added



#endif
#if 0
/* Listener for _actionTypeBox
*/
//class ActionTypeListener implements ActionListener {
ActionTypeListener::ActionTypeListener(LogixTableAction *self)
{
 this->self = self;
}
/*public*/ void ActionTypeListener::actionPerformed(ActionEvent* e) {
    int select1 = self->_actionItemTypeBox->currentIndex();
    int select2 = self->_actionTypeBox->currentIndex()-1;
    if (self->log->isDebugEnabled()) self->log->debug("ActionTypeListener: actionItemType= "+QString::number(select1)+", _itemType= "
                                        +QString::number(_itemType)+", action= "+QString::number(select2));
    if (select1 != _itemType) {
        if (self->log->isDebugEnabled()) self->log->error("ActionTypeListener actionItem selection ("+QString::number(select1)+
                                            ") != expected actionItem ("+QString::number(_itemType)+")");
    }
    if (self->_curAction!=NULL) {
        if (select1 > 0 && _itemType==select1) {
                ((ConditionalAction*)self->_curAction)->setType(self->getActionTypeFromBox(_itemType, select2));
                if (select1 == _itemType) {
                    QString text = self->_actionNameField->text();
                    if (text != NULL && text.length()>0) {
                        ((ConditionalAction*)self->_curAction)->setDeviceName(text);
                    }
                }
                self->actionItemChanged(_itemType);
                self->initializeActionVariables();
        }
    }
}
/*public*/ void ActionTypeListener::setItemType(int type) {
    _itemType = type;
}
#endif
//};
void LogixTableAction::_actionTypeListener(int type) // SLOT[]
{
 int select1 = type;
 int select2 = type-1;
 if (log->isDebugEnabled()) log->debug("ActionTypeListener: actionItemType= "+QString::number(select1)+", _itemType= "
                                        +QString::number(itemType)+", action= "+QString::number(select2));
 if (select1 != itemType)
 {
  if (log->isDebugEnabled())log->error("ActionTypeListener actionItem selection ("+QString::number(select1)+
                                            ") != expected actionItem ("+QString::number(itemType)+")");
 }
 if (_curAction!=NULL)
 {
  if (select1 > 0 && itemType==select1)
  {
   ((ConditionalAction*)_curAction)->setType(getActionTypeFromBox(itemType, select2));
   if (select1 == itemType)
   {
    QString text = _actionNameField->text();
    if (text != NULL && text.length()>0)
    {
     ((ConditionalAction*)_curAction)->setDeviceName(text);
    }
   }
   actionItemChanged(itemType);
   initializeActionVariables();
  }
 }
}

#if 0

static final int STRUT = 10;
#endif
// *********** Methods for Add Logix Window ********************

/**
 * Responds to the Add button in Logix table Creates and/or initializes the
 * Add Logix window
 */
/*protected*/ void LogixTableAction::addPressed(ActionEvent* /*e*/)
{
 // possible change
 if (!checkFlags(NULL))
 {
  return;
 }
 _showReminder = true;
 // make an Add Logix Frame
 if (addLogixFrame == NULL)
 {
  QWidget* panel5 = makeAddLogixFrame("Add Logix", "Please enter system name and user name, then","click Create Logix, then add Conditionals.");
  // Create Logix
  create = new QPushButton(tr("Create Logix"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setWidthForHeight(create->sizePolicy().hasHeightForWidth());
  create->setSizePolicy(sizePolicy);
  panel5->layout()->addWidget(create);
  //        create->layout()->addActionListener(new ActionListener() {
  //            /*public*/ void actionPerformed(ActionEvent e) {
  //                createPressed(e);
  //            }
  //        });
  connect(create, SIGNAL(clicked()), this, SLOT(createPressed()));
  create->setToolTip(tr("Press to create a new Logix"));
 }
 addLogixFrame->adjustSize();
 addLogixFrame->setVisible(true);
 _autoSystemName->setChecked(false);
 if(((DefaultUserMessagePreferences*) prefMgr)->getSimplePreferenceState(systemNameAuto))
 _autoSystemName->setChecked(true);
}

/**
*  shared method for window to create or copy Logix
* Returns the button panel
*/
QWidget* LogixTableAction::makeAddLogixFrame(QString titleId, QString messageId1,QString messageId2)
{
 addLogixFrame = new JmriJFrame(titleId,true,true);
 addLogixFrame->addHelpMenu(
            "package.jmri.jmrit.beantable.LogixAddEdit", true);
 addLogixFrame->setLocation(50, 30);
 if(addLogixFrame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget();
  centralWidget->setLayout(new QVBoxLayout);
  addLogixFrame->setCentralWidget(centralWidget);
 }
 QWidget* contentPane = addLogixFrame->centralWidget();
 contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));

 QWidget* p;
 p = new QWidget();
 //p->setLayout(new QHBoxLayout());
 QGridLayout* g;
 p->setLayout(g = new QGridLayout());
 GridBagConstraints* c = new GridBagConstraints();
 c->gridwidth  = 1;
 c->gridheight = 1;
 c->gridx = 0;
 c->gridy = 0;
 c->anchor = GridBagConstraints::EAST;
 g->addWidget(_sysNameLabel,c->gridy, c->gridx, c->rowSpan(),c->colSpan());
 c->gridy = 1;
 g->addWidget(_userNameLabel,c->gridy, c->gridx, c->rowSpan(),c->colSpan());
 c->gridx = 1;
 c->gridy = 0;
 c->anchor = GridBagConstraints::WEST;
 c->weightx = 1.0;
 c->fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 g->addWidget(_systemName,c->gridy,c->gridx, c->rowSpan(),c->colSpan());
 c->gridy = 1;
 g->addWidget(_addUserName,c->gridy,c->gridx, c->rowSpan(),c->colSpan());
 c->gridx = 2;
 c->gridy = 1;
 c->anchor = GridBagConstraints::WEST;
 c->weightx = 1.0;
 c->fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 c->gridy = 0;
 g->addWidget(_autoSystemName,c->gridy,c->gridx, c->rowSpan(),c->colSpan());
 _addUserName->setToolTip(tr("Enter user name for new Logix, e.g. Signal 2 Control"));
 _systemName->setToolTip(tr("Enter system name for new Logix, e.g.IX13"));
 contentPane->layout()->addWidget(p);
    // set up message
 QWidget* panel3 = new QWidget();
 panel3->setLayout(new QVBoxLayout(panel3/*, BoxLayout.Y_AXIS*/));
 QWidget* panel31 = new QWidget();
 panel31->setLayout(new QHBoxLayout());
 QLabel* message1 = new QLabel(messageId1);
 panel31->layout()->addWidget(message1);
 QWidget* panel32 = new QWidget();
 panel32->setLayout(new QHBoxLayout());
 QLabel* message2 = new QLabel(messageId2);
 panel32->layout()->addWidget(message2);
 panel3->layout()->addWidget(panel31);
 panel3->layout()->addWidget(panel32);
 contentPane->layout()->addWidget(panel3);

    // set up create and cancel buttons
 QWidget* panel5 = new QWidget();
 panel5->setLayout(new QHBoxLayout());
 // Cancel
 QPushButton* cancel = new QPushButton(tr("Cancel"));
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(cancel->sizePolicy().hasHeightForWidth());
 cancel->setSizePolicy(sizePolicy);
 panel5->layout()->addWidget(cancel);
// cancel->layout()->addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelAddPressed(e);
//        }
//    });
 connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAddPressed()));
 cancel->setToolTip(tr("Press to return to Logix Table without any changes"));
//    addLogixFrame->addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            cancelAddPressed(NULL);
//        }
//    });
 addLogixFrame->addWindowListener(addLogixFrameWindowListener = new AddLogixFrameWindowListener(this));
  contentPane->layout()->addWidget(panel5);

//  _autoSystemName->layout()->addWidgetItemListener(
//        new ItemListener() {
//            /*public*/ void itemStateChanged(ItemEvent e){
//                autoSystemName();
//            }
//    });
  connect(_autoSystemName, SIGNAL(toggled(bool)), this, SLOT(autoSystemName()));
    return panel5;
}
AddLogixFrameWindowListener::AddLogixFrameWindowListener(LogixTableAction *self)
{
 this->self = self;
}
void AddLogixFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelAddPressed(NULL);
}

void LogixTableAction::autoSystemName(){
    if (_autoSystemName->isChecked()){
        _systemName->setEnabled(false);
        _sysNameLabel->setEnabled(false);
    }
    else {
        _systemName->setEnabled(true);
        _sysNameLabel->setEnabled(true);
    }
}

/**
 * Responds to the Cancel button in Add Logix window Note: Also get there if
 * the user closes the Add Logix window
 */
void LogixTableAction::cancelAddPressed(ActionEvent* /*e*/) {
        addLogixFrame->setVisible(false);
        addLogixFrame->dispose();
        addLogixFrame = NULL;
        inCopyMode = false;
//        if (f!=NULL)
//            f->setVisible(true);
}

void LogixTableAction::copyPressed(QString sName)
{
 if (!checkFlags(sName))
 {
  return;
 }
//    Thread t = new Thread() {
//            /*public*/ void run() {
//                //Thread.yield();
 QWidget* panel5 = makeAddLogixFrame(tr("Copy Logix", "Please enter system name and user name"), tr("of target Logix, then click Copy"));
 // Create Logix
 QPushButton* create = new QPushButton(tr("Copy"));
 panel5->layout()->addWidget(create);
//                create->layout()->addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        copyLogixPressed(e);
//                    }
//                });
 addLogixFrame->adjustSize();
 addLogixFrame->setVisible(true);
 _autoSystemName->setChecked(false);
 if(((DefaultUserMessagePreferences*)prefMgr)->getSimplePreferenceState(systemNameAuto))
 _autoSystemName->setChecked(true);
//                }
//            };
if (log->isDebugEnabled()) log->debug("copyPressed Thread started for " + sName);
    //javax.swing.SwingUtilities.invokeLater(t);
    //t.start();
 inCopyMode = true;
 _logixSysName = sName;
}


void LogixTableAction::copyLogixPressed(ActionEvent* /*e*/)
{
 QString uName = _addUserName->text().trimmed();
 if (uName.length()==0)
 {
     uName = "";
 }
 Logix* targetLogix;
 if(_autoSystemName->isChecked())
 {
  if (!checkLogixUserName(uName))
   return;
  targetLogix = ((DefaultLogixManager*)_logixManager)->createNewLogix(uName);
 }
 else
 {
  if (!checkLogixSysName())
  {
   return;
  }
  QString sName = _systemName->text().trimmed();
  // check if a Logix with this name already exists
  bool createLogix = true;
  targetLogix = ((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
  if (targetLogix != NULL)
  {
//   int result = JOptionPane.showConfirmDialog(f, java.text.MessageFormat.format(
//                                                tr("ConfirmLogixDuplicate"),
//                                                new Object[] {sName, _logixSysName}),
//                                                tr("ConfirmTitle"), JOptionPane.YES_NO_OPTION,
//                                                JOptionPane.QUESTION_MESSAGE);
   if (QMessageBox::question(0, tr("Question"), tr("Logix \"%1\" already exists. Do you want copy\nthe Conditionals of Logix \"%2\" into \"%1\"?").arg(sName).arg(_logixSysName),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
    return;
   }
   createLogix = false;
   QString userName = ((DefaultLogix*)targetLogix)->getUserName();
   if (userName.length() > 0)
   {
    _addUserName->setText(userName);
    uName = userName;
   }
  }
  else if (!checkLogixUserName(uName))
  {
   return;
  }
  if (createLogix)
  {
   // Create the new Logix
   targetLogix = ((DefaultLogixManager*)_logixManager)->createNewLogix(sName, uName);
   if (targetLogix == NULL)
   {
    // should never get here unless there is an assignment conflict
    log->error("Failure to create Logix with System Name: " + sName);
    return;
   }
  }
  else if (targetLogix == NULL)
  {
   log->error("Error targetLogix is NULL!");
   return;
  }
  else
  {
   ((DefaultLogix*)targetLogix)->setUserName(uName);
  }
 }
 Logix* srcLogic = ((DefaultLogixManager*)_logixManager)->getBySystemName(_logixSysName);
 for (int i=0; i< ((DefaultLogix*)srcLogic)->getNumConditionals(); i++)
 {
  QString cSysName = ((DefaultLogix*)srcLogic)->getConditionalByNumberOrder(i);
  copyConditionalToLogix(cSysName, srcLogic, targetLogix);
 }
 cancelAddPressed(NULL);
}

void LogixTableAction::copyConditionalToLogix(QString cSysName, Logix* /*srcLogix*/, Logix* targetLogix)
{
 Conditional* cOld = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cSysName);
 if (cOld == NULL)
 {
  log->error("Failure to find Conditional with System Name: " + cSysName);
  return;
 }
 QString cOldSysName = ((DefaultConditional*)cOld)->getSystemName();
 QString cOldUserName = ((DefaultConditional*)cOld)->getUserName();

 // make system name for new conditional
 int num = ((DefaultLogix*)targetLogix)->getNumConditionals()+1;
 QString cNewSysName = ((DefaultLogix*)targetLogix)->getSystemName() + "C" + QString::number(num);
 // add to Logix at the end of the calculate order
 QString cNewUserName = tr("Copy of %1").arg(cOldUserName);
 if (cOldUserName.length() == 0)
 {

  cNewUserName += "C"+QString::number(num);
 }
 do
 {
//        cNewUserName = JOptionPane.showInputDialog(f, java.text.MessageFormat.format(
//                                                tr("NameConditionalCopy"), new Object[] {
//                                                cOldUserName, cOldSysName, _logixSysName,
//                                                targetLogix.getUserName(), targetLogix.getSystemName()}),
//                                                cNewUserName);
  QString msg = tr("Rename the copy of Conditional \"%1\" (%2)\nin Logix %3 being copied into Logix \"%4\" (%5).\nPress Cancel if you don't want to copy this conditional.").arg(cOldUserName).arg(cOldSysName).arg(((DefaultLogix*)targetLogix)->getUserName()).arg(((DefaultLogix*)targetLogix)->getSystemName()).arg(cNewUserName);
  InputDialog* dlg = new InputDialog(msg,cNewUserName);
  if(dlg->exec() == QDialog::Accepted)
  {
   cNewUserName = dlg->value();
   if (cNewUserName == NULL || cNewUserName.length()==0)
   {
    return;
   }
  }
 } while (!checkConditionalUserName(cNewUserName, targetLogix) );

    while (!checkConditionalSystemName(cNewSysName))
    {
     cNewSysName = ((DefaultLogix*)targetLogix)->getSystemName() + "C" + QString::number(++num);
    }

    Conditional* cNew = ((DefaultConditionalManager*)_conditionalManager)->createNewConditional(cNewSysName, cNewUserName);
    if (cNew == NULL)
    {
        // should never get here unless there is an assignment conflict
        log->error("Failure to create Conditional with System Name: \""
                + cNewSysName+"\" and User Name: \""+ cNewUserName+"\"");
        return;
    }
    ((DefaultConditional*)cNew)->setLogicType(((DefaultConditional*)cOld)->getLogicType(), ((DefaultConditional*)cOld)->getAntecedentExpression());
    ((DefaultConditional*)cNew)->setStateVariables(((DefaultConditional*)cOld)->getCopyOfStateVariables());
    ((DefaultConditional*)cNew)->setAction(((DefaultConditional*)cOld)->getCopyOfActions());
    ((DefaultLogix*)targetLogix)->addConditional(cNewSysName, -1);
}

bool LogixTableAction::checkLogixUserName(QString uName)
{
 // check if a Logix with the same user name exists
 if (uName!=NULL && uName.trimmed().length() > 0)
 {
  Logix* x = ((DefaultLogixManager*)_logixManager)->getByUserName(uName);
  if (x != NULL)
  {
//            // Logix with this user name already exists
//            javax.swing.JOptionPane.showMessageDialog(addLogixFrame,
//                    tr("Error3"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(addLogixFrame, tr("Error"), tr("A Logix with this user name already exists.\nPlease change user name and try again."));
            return false;
  }
 }
 return true;
}

bool LogixTableAction::checkLogixSysName()
{
 // check validity of Logix system name
 QString sName = _systemName->text().trimmed();
 if ( (sName.length() < 1))
 {
  // Entered system name is blank or too short
//  javax.swing.JOptionPane.showMessageDialog(addLogixFrame,
//                 tr("Error8"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(addLogixFrame, tr("Error"), tr("Invalid system name, or system name not entered./nPlease enter a valid Logix system name (e.g. IX3) and try again."));
  return false;
 }
 if ((sName.length() < 2) || (sName.at(0) != 'I')
            || (sName.at(1) != 'X'))
 {
  // System name does not begin with IX, prefix IX to it
  QString s = sName;
  sName = "IX" + s;
 }
 _systemName->setText(sName);
 return true;
}


bool LogixTableAction::checkFlags(QString sName) {
    if (inEditMode) {
        // Already editing a Logix, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Error32"),
//                new Object[] { _curLogix.getSystemName() }), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLogixFrame, tr("Error"), tr("Cannot edit two Logixs at the same time. Please complete edit of Logix \"%1\" and try again.").arg( ((DefaultLogix*)_curLogix)->getSystemName()));
        return false;
    }
    if (inCopyMode) {
        // Already editing a Logix, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Error31"),
//                new Object[] { _logixSysName }), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLogixFrame,tr("Error"), tr("Copy of Logix \"{0}\" in progress.  Please complete and try again.").arg(_logixSysName) );
        return false;
    }
    if (sName != NULL) {
        // check if a Logix with this name exists
        Logix* x = ((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
        if (x == NULL) {
            // Logix does not exist, so cannot be edited
            log->error("No Logix with system name: " + sName);
//            javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
//                    .getString("Error5"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(editLogixFrame,tr("Error"), tr("Cannot find a Logix with that system name."));
            if (editLogixFrame != NULL) {
                editLogixFrame->setVisible(false);
            }
            return false;
        }
    }
    return true;
}


/**
 * Responds to the Create Logix button in Add Logix window
 */
void LogixTableAction::createPressed(ActionEvent* /*e*/)
{
 // possible change
 _showReminder = true;
 QString uName = _addUserName->text().trimmed();
 if (uName.length()==0)
 {
  uName = "";
 }
 QString sName = _systemName->text().trimmed();
 if(_autoSystemName->isChecked())
 {
  if (!checkLogixUserName(uName))
  {
   return;
  }
  _curLogix = ((DefaultLogixManager*)_logixManager)->createNewLogix(uName);
 }
 else
 {
  if (!checkLogixSysName())
  {
   return;
  }
  // check if a Logix with this name already exists
  Logix* x = ((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
  if (x != NULL)
  {
            // Logix already exists
//            javax.swing.JOptionPane.showMessageDialog(addLogixFrame, rbx
//                    .getString("Error1"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(addLogixFrame, tr("Error"), tr("A Logix with this system name already exists.\nPlease change system name and try again."));
   return;
  }
  if (!checkLogixUserName(uName))
  {
   return;
  }
  // Create the new Logix
  _curLogix = ((DefaultLogixManager*)_logixManager)->createNewLogix(sName, uName);
  if (_curLogix == NULL)
  {
   // should never get here unless there is an assignment conflict
   log->error("Failure to create Logix with System Name: " + sName);
   return;
  }
 }
 numConditionals = 0;
 cancelAddPressed(NULL);
 // create the Edit Logix Window
 makeEditLogixWindow();
 ((DefaultUserMessagePreferences*) prefMgr)->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
}

// *********** Methods for Edit Logix Window ********************
#if 1
/**
 * Responds to the Edit button pressed in Logix table
 */
void LogixTableAction::editPressed(QString sName) {
    if (!checkFlags(sName)) {
        return;
    }
    // Logix was found, initialize for edit
    _curLogix =  ((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
    numConditionals = ((DefaultLogix*)_curLogix)->getNumConditionals();
    // create the Edit Logix Window
#if 0
    // Use separate Thread so window is created on top
    //QThread t = new QThread()
    class MyThread : public QThread
    {
     LogixTableAction* self;

    public:
        MyThread(LogixTableAction* self)
        {
          this->self = self;
        }
        /*public*/ void run()
        {
                //Thread.yield();
         self->makeEditLogixWindow();
        }
    };
    MyThread* myThread = new MyThread(this);
    myThread->start();
#else
    makeEditLogixWindow();
#endif
    if (log->isDebugEnabled()) log->debug("editPressed Thread started for " + sName);
    //javax.swing.SwingUtilities.invokeLater(t);
}

/**
 * creates and/or initializes the Edit Logix window
 */
void LogixTableAction::makeEditLogixWindow() {
    //if (log->isDebugEnabled()) log->debug("makeEditLogixWindow ");
    editUserName->setText(((DefaultLogix*)_curLogix)->getUserName());
    // clear conditional table if needed
    if (conditionalTableModel != NULL)
    {
//        conditionalTableModel->fireTableStructureChanged();
    }
    inEditMode = true;
    if (editLogixFrame == NULL)
    {
     editLogixFrame = new JmriJFrame(tr("Edit Logix"), false, false);
     editLogixFrame->addHelpMenu(
                "package.jmri.jmrit.beantable.LogixAddEdit", true);
     editLogixFrame->setLocation(100, 30);
     QWidget* contentPane = editLogixFrame->centralWidget();
     if(contentPane == NULL)
     {
      editLogixFrame->setCentralWidget(contentPane = new QWidget());
     }
     contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
     QWidget* panel1 = new QWidget();
     panel1->setLayout(new QHBoxLayout());
     QLabel* systemNameLabel = new QLabel(tr("System Name"));
     panel1->layout()->addWidget(systemNameLabel);
     QLabel* fixedSystemName = new QLabel(((DefaultLogix*)_curLogix)->getSystemName());
     panel1->layout()->addWidget(fixedSystemName);
     contentPane->layout()->addWidget(panel1);
     QWidget* panel2 = new QWidget();
     panel2->setLayout(new QHBoxLayout());
     QLabel* userNameLabel = new QLabel(tr("User Name"));
     panel2->layout()->addWidget(userNameLabel);
     panel2->layout()->addWidget(editUserName);
     editUserName->setToolTip(tr("Enter new user name for Logix, e.g. Signal 2 Control"));
     contentPane->layout()->addWidget(panel2);
     // add table of Conditionals
     QWidget* pctSpace = new QWidget();
     pctSpace->setLayout(new QHBoxLayout());
     pctSpace->layout()->addWidget(new QLabel("   "));
     contentPane->layout()->addWidget(pctSpace);
     QWidget* pTitle = new QWidget();
     pTitle->setLayout(new QHBoxLayout());
     pTitle->layout()->addWidget(new QLabel(tr("Conditionals (in Order of Calculation)")));
     contentPane->layout()->addWidget(pTitle);
     // initialize table of conditionals
     conditionalTableModel = new ConditionalTableModel(this);
     QTableView* conditionalTable = new QTableView();
     conditionalTable->setModel(conditionalTableModel);
     conditionalTable->resizeColumnToContents(1);
     conditionalTable->setItemDelegateForColumn(ConditionalTableModel::BUTTON_COLUMN, new PushButtonDelegate());
     //conditionalTable.setRowSelectionAllowed(false);
//     TableColumnModel conditionalColumnModel = conditionalTable
//             .getColumnModel();
//     TableColumn sNameColumn = conditionalColumnModel
//             .getColumn(ConditionalTableModel.SNAME_COLUMN);
//     sNameColumn.setResizable(true);
//     sNameColumn.setMinWidth(100);
//     sNameColumn.setPreferredWidth(130);
//     TableColumn uNameColumn = conditionalColumnModel
//             .getColumn(ConditionalTableModel.UNAME_COLUMN);
//     uNameColumn.setResizable(true);
//     uNameColumn.setMinWidth(210);
//     uNameColumn.setPreferredWidth(260);
//     TableColumn stateColumn = conditionalColumnModel
//             .getColumn(ConditionalTableModel.STATE_COLUMN);
//     stateColumn.setResizable(true);
//     stateColumn.setMinWidth(50);
//     stateColumn.setMaxWidth(100);
//     TableColumn buttonColumn = conditionalColumnModel
//             .getColumn(ConditionalTableModel.BUTTON_COLUMN);
 #if 0
     // install button renderer and editor
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     conditionalTable.setDefaultRenderer(QPushButton.class, buttonRenderer);
     TableCellEditor buttonEditor = new ButtonEditor(new QPushButton());
     conditionalTable.setDefaultEditor(QPushButton.class, buttonEditor);
     QPushButton testButton = new QPushButton("XXXXXX");
     conditionalTable.setRowHeight(testButton.getPreferredSize().height);
     buttonColumn.setMinWidth(testButton.getPreferredSize().width);
     buttonColumn.setMaxWidth(testButton.getPreferredSize().width);
     buttonColumn.setResizable(false);
 #endif
     //JScrollPane conditionalTableScrollPane = new JScrollPane(conditionalTable);
     QSize dim = conditionalTable->size();
     dim.setHeight(450);
     //conditionalTableScrollPane.getViewport().setPreferredSize(dim);
     contentPane->layout()->addWidget(/*conditionalTableScrollPane*/conditionalTable);

     // add message area between table and buttons
     QWidget* panel4 = new QWidget();
     panel4->setLayout(new QVBoxLayout(panel4/*, BoxLayout.Y_AXIS*/));
     QWidget* panel41 = new QWidget();
     panel41->setLayout(new QHBoxLayout());
     panel41->layout()->addWidget(status);
     panel4->layout()->addWidget(panel41);
     QFrame* panel42 = new QFrame();
     panel42->setFrameStyle(QFrame::Box | QFrame::Raised);
     panel42->setLineWidth(2);
     panel42->setLayout(new QHBoxLayout());
     // Conditional panel buttons - New Conditional
     QPushButton* newConditionalButton = new QPushButton(tr("New Conditional"));
     QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     sizePolicy.setHorizontalStretch(0);
     sizePolicy.setVerticalStretch(0);
     sizePolicy.setHeightForWidth(newConditionalButton->sizePolicy().hasHeightForWidth());
     newConditionalButton->setSizePolicy(sizePolicy);
     panel42->layout()->addWidget(newConditionalButton);
//     newConditionalButton->layout()->addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             newConditionalPressed(e);
//         }
//     });
     connect(newConditionalButton, SIGNAL(clicked()), this, SLOT(newConditionalPressed()));
     newConditionalButton->setToolTip(tr("Press for window to create a new Conditional"));
     // Conditional panel buttons - Reorder
     QPushButton* reorderButton = new QPushButton(tr("Reorder"));
     reorderButton->setSizePolicy(sizePolicy);
     panel42->layout()->addWidget(reorderButton);
//     reorderButton->layout()->addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             reorderPressed(e);
//         }
//     });
     connect(reorderButton, SIGNAL(clicked()), this, SLOT(reorderPressed()));
     reorderButton->setToolTip(tr("Press then click in right column in order desired"));
     // Conditional panel buttons - Calculate
     QPushButton* calculateButton = new QPushButton(tr("Calculate"));
     calculateButton->setSizePolicy(sizePolicy);
     panel42->layout()->addWidget(calculateButton);
//     calculateButton->layout()->addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             calculatePressed(e);
//         }
//     });
     connect(calculateButton, SIGNAL(clicked()), this, SLOT(calculatePressed()));
     calculateButton->setToolTip(tr("Press to calculate Conditional states without action"));
     panel4->layout()->addWidget(panel42);
     //Border panel4Border = BorderFactory.createEtchedBorder();
     QGroupBox* panel4Border = new QGroupBox();
     QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
     panel4Border->setStyleSheet(gbStyleSheet);
     //panel4.setBorder(panel4Border);
     contentPane->layout()->addWidget(panel4);
     // add buttons at bottom of window
     QWidget* panel5 = new QWidget();
     panel5->setLayout(new QHBoxLayout());
     // Bottom Buttons - Done Logix
     QPushButton* done = new QPushButton(tr("Done"));
     done->setSizePolicy(sizePolicy);
     panel5->layout()->addWidget(done);
//     done->layout()->addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             donePressed(e);
//         }
//     });
     connect(done, SIGNAL(clicked()), this, SLOT(donePressed()));
     done->setToolTip(tr("Press to save any user name changes and return to Logix Table"));
     // Delete Logix
     QPushButton* deleteButton = new QPushButton(tr("Delete Logix"));
     deleteButton->setSizePolicy(sizePolicy);
     panel5->layout()->addWidget(deleteButton);
//     delete->layout()->addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             deletePressed(e);
//         }
//     });
     connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
     deleteButton->setToolTip(tr("Press to delete this Logix and all its Conditionals"));
     contentPane->layout()->addWidget(panel5);
    }

//    editLogixFrame->addWindowListener(new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    if (inEditMode) {
//                        donePressed(NULL);
//                    } else {
//                        finishDone();
//                    }
//                }
//            });
    editLogixFrame->addWindowListener(editLogixFrameWindowListener = new EditLogixFrameWindowListener(this));
    editLogixFrame->adjustSize();
    editLogixFrame->setVisible(true);
}
#endif
EditLogixFrameWindowListener::EditLogixFrameWindowListener(LogixTableAction *self)
{
 this->self = self;
}
void EditLogixFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 if (self->inEditMode)
 {
  self->donePressed(NULL);
 }
 {
  self->finishDone();
 }
}

/**
 * Display reminder to save
 */
void LogixTableAction::showSaveReminder() {
    /*if (_showReminder && !_suppressReminder) {
        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
                .getString("Reminder1"),
                tr("ReminderTitle"),
                javax.swing.JOptionPane.INFORMATION_MESSAGE);
    }*/
    if (_showReminder){
        if (InstanceManager::getDefault("UserPreferencesManager") != NULL)
            ((DefaultUserMessagePreferences*) InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage(tr("ReminderTitle"),tr("Reminder1"),getClassName(), "remindSaveLogix");
    }
}

/**
 * Responds to the Reorder Button in the Edit Logix window
 */
void LogixTableAction::reorderPressed(ActionEvent* /*e*/) {
    if (checkEditConditional())
        return;
    // Check if reorder is reasonable
    _showReminder = true;
    _nextInOrder = 0;
    _inReorderMode = true;
    status->setText(tr("Please press First, then Next, Next,... in desired order."));
    conditionalTableModel->fireTableDataChanged();
}

/**
 * Responds to the First/Next (Delete) Button in the Edit Logix window
 */
void LogixTableAction::swapConditional(int row) {
    ((DefaultLogix*)_curLogix)->swapConditional(_nextInOrder, row);
    _nextInOrder++;
    if (_nextInOrder >= numConditionals)
    {
        _inReorderMode = false;
    }
    //status->setText("");
    conditionalTableModel->fireTableDataChanged();
}

/**
 * Responds to the Calculate Button in the Edit Logix window
 */
void LogixTableAction::calculatePressed(ActionEvent* /*e*/)
{
 if (checkEditConditional())
  return;
 // are there Conditionals to calculate?
 if (numConditionals > 0)
 {
  // There are conditionals to calculate
  QString cName = "";
  Conditional* c = NULL;
  for (int i = 0; i < numConditionals; i++)
  {
   cName = ((DefaultLogix*)_curLogix)->getConditionalByNumberOrder(i);
   if (cName != NULL)
   {
    c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cName);
    if (c == NULL)
    {
     log->error("Invalid conditional system name when calculating - " + cName);
    }
    else
    {
     // calculate without taking any action
     ((DefaultConditional*)c)->calculate(false, NULL);
    }
   }
   else
   {
    log->error("NULL conditional system name when calculating");
   }
  }
  // force the table to update
  conditionalTableModel->fireTableDataChanged();
 }
}

/**
 * Responds to the Done button in the Edit Logix window Note: also get here
 * if the Edit Logix window is dismissed, or if the Add button is pressed in
 * the Logic Table with an active Edit Logix window.
 */
void LogixTableAction::donePressed(ActionEvent* /*e*/)
{
 if (_curLogix == NULL)
 {
  log->error("NULL pointer to _curLogix in donePressed method");
  finishDone();
  return;
 }
 if (checkEditConditional())
 {
  return;
 }
 if (((DefaultLogix*)_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName))
 {
  finishDone();
  return;
 }
 // Check if the User Name has been changed
 QString uName = editUserName->text().trimmed();
 if (!(uName==(((DefaultLogix*)_curLogix)->getUserName())))
 {
  // user name has changed - check if already in use
  if (uName.length()>0)
  {
   Logix* p = ((DefaultLogixManager*)_logixManager)->getByUserName(uName);
   if (p != NULL)
   {
    // Logix with this user name already exists
    log->error("Failure to update Logix with Duplicate User Name: "
                    + uName);
//    javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//            tr("Error6"), rbx
//                    .getString("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(editLogixFrame, tr("Error"), tr("New user name is already in use. Cannot update this Logix. Please change user name and try again."));
    return;
   }
  }
  // user name is unique, change it
  ((DefaultLogix*)_curLogix)->setUserName(uName);
  m->fireTableDataChanged();
 }
 // complete update and activate Logix
 finishDone();
}  /* donePressed */

void LogixTableAction::finishDone()
{
 showSaveReminder();
 inEditMode = false;
 if (editLogixFrame!=NULL)
 {
  editLogixFrame->setVisible(false);
  editLogixFrame->dispose();
  editLogixFrame = NULL;
 }
 // bring Logix Table to front
// if (f!=NULL)
//  f->setVisible(true);
}

/*public*/ void LogixTableAction::setMessagePreferencesDetails()
{
 QMap<int,QString> options = QMap< int,QString>(/*3*/);
 options.insert(0x00, tr("Always Ask"));
 options.insert(0x01, tr("Never Delete"));
 options.insert(0x02, tr("Delete Without Prompting"));
 ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->messageItemDetails(getClassName(), "delete", tr("When Deleting the logix"), options, 0x00);
 ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->preferenceItemDetails(getClassName(), "remindSaveLogix", tr("Suppress Save Reminders"));
 AbstractTableAction::setMessagePreferencesDetails();
}

/**
 * Responds to the Delete combo selection Logix window
 */
void LogixTableAction::deletePressed(QString sName)
{
 if (!checkFlags(sName))
 {
  return;
 }
 /*final*/ x = ((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
 ///*final*/ DefaultUserMessagePreferences* p;
 p = (DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager");
 if (p != NULL && p->getMultipleChoiceOption(getClassName(), "delete")==0x02)
 {
  if (x != NULL)
  {
   ((DefaultLogixManager*)_logixManager)->deleteLogix(x);
  }
 }
 else
 {
  /*final*/ dialog = new QDialog();
  QString msg;
  dialog->setWindowTitle(tr("Question"));
//  dialog->setLocationRelativeTo(NULL);
//  dialog->setDefaultCloseOperation(javax.swing.JFrame.DISPOSE_ON_CLOSE);
  QWidget* container = new QWidget();
  //container.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
  container->setLayout(new QVBoxLayout(container/*, BoxLayout.Y_AXIS*/));
  msg = tr("Are you sure you want to delete Logix \"%1\"?").arg( sName);
  QLabel* question = new QLabel(msg);
  //question.setAlignmentX(Component.CENTER_ALIGNMENT);
  container->layout()->addWidget(question);

  /*final*/ remember = new QCheckBox("Remember this setting for next time?");
  QFont f = remember->font();
  f.setPointSize(10);
  remember->setFont(f);
  //remember.setAlignmentX(Component.CENTER_ALIGNMENT);

  QPushButton* yesButton = new QPushButton("Yes");
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(yesButton->sizePolicy().hasHeightForWidth());
  yesButton->setSizePolicy(sizePolicy);
  QPushButton* noButton = new QPushButton("No");
  noButton->setSizePolicy(sizePolicy);
  QWidget* button = new QWidget();
  button->setLayout(new QHBoxLayout());
  button->setSizePolicy(sizePolicy);
  //button.setAlignmentX(Component.CENTER_ALIGNMENT);
  button->layout()->addWidget(yesButton);
  button->layout()->addWidget(noButton);
  container->layout()->addWidget(button);

//  noButton->layout()->addActionListener(new ActionListener(){
//    /*public*/ void actionPerformed(ActionEvent e) {
//        //there is no point in remebering this the user will never be
//        //able to delete a bean!
//        /*if(remember.isSelected()){
//            setDisplayDeleteMsg(0x01);
//        }*/
//        dialog->dispose();
//    }
//  });
  connect(noButton, SIGNAL(clicked()), dialog, SLOT(close()));

//  yesButton->layout()->addActionListener(new ActionListener(){
//    /*public*/ void actionPerformed(ActionEvent e) {
//        if(p != NULL && remember.isSelected()) {
//           p.setMultipleChoiceOption(getClassName(), "delete", 0x02);
//        }
//        if (x != NULL) {
//            _logixManager.deleteLogix(x);
//        }
//        dialog->dispose();
//    }
//  });
  connect(yesButton, SIGNAL(clicked()), this, SLOT(yesButtonPressed()));
  container->layout()->addWidget(remember);
  //container.setAlignmentX(Component.CENTER_ALIGNMENT);
  //container.setAlignmentY(Component.CENTER_ALIGNMENT);
  dialog->setLayout(new QVBoxLayout);
  dialog->layout()->addWidget(container);
//  dialog->pack();
//  dialog->setModal(true);
//  dialog->setVisible(true);
  dialog->exec();
 }

    /*if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(f, java.text.MessageFormat.format(
                                            tr("ConfirmLogixDelete"), sName),
                                            tr("ConfirmTitle"), JOptionPane.YES_NO_OPTION,
                                            JOptionPane.QUESTION_MESSAGE) )
    {
        Logix x = _logixManager.getBySystemName(sName);
        if (x != NULL) {
            _logixManager.deleteLogix(x);
        }
    }*/
 //f->setVisible(true);
}
void LogixTableAction::yesButtonPressed()
{
 if(p != NULL && remember->isChecked())
 {
   p->setMultipleChoiceOption(getClassName(), "delete", 0x02);
 }
 if (x != NULL) {
    ((DefaultLogixManager*)_logixManager)->deleteLogix(x);
 }
 dialog->close();
}

/**
 * Responds to the Delete button in the Edit Logix window
 */
void LogixTableAction::deletePressed(ActionEvent* /*e*/)
{
 if (checkEditConditional())
  return;
_showReminder = true;
 Logix* x = _curLogix;
 // delete this Logix
 ((DefaultLogixManager*)_logixManager)->deleteLogix(x);
 _curLogix = NULL;
 finishDone();
}

/**
 * Responds to the New Conditional Button in Edit Logix Window
 */
void LogixTableAction::newConditionalPressed(ActionEvent* /*e*/)
{
 if (checkEditConditional())
  return;
 if (((DefaultLogix*)_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName))
 {
//  javax.swing.JOptionPane.showMessageDialog(
//        editLogixFrame, java.text.MessageFormat.format(tr("Warn8"),
//            new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName }),
//        rbx .getString("WarnTitle"),
//        javax.swing.JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(editLogixFrame, tr("Warning"), tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName ));
  return;
 }
 // make system name for new conditional
 int num = ((DefaultLogix*)_curLogix)->getNumConditionals()+1;
 _curConditional = NULL;
 QString cName = NULL;
 while (_curConditional == NULL)
 {
  cName = ((DefaultLogix*)_curLogix)->getSystemName() + "C" + QString::number(num);
  _curConditional = ((DefaultConditionalManager*)_conditionalManager)->createNewConditional(cName, "");
  num++;
  if (num==1000) break;
 }
 if (_curConditional == NULL)
 {
  // should never get here unless there is an assignment conflict
  log->error("Failure to create Conditional with System Name: "
                + cName);
  return;
 }
 // add to Logix at the end of the calculate order
 ((DefaultLogix*)_curLogix)->addConditional(cName, -1);
  conditionalTableModel->fireTableRowsInserted(numConditionals, numConditionals);
  conditionalRowNumber = numConditionals;
  numConditionals++;
 _showReminder = true;
  // clear action items
  _actionList = new QList <ConditionalAction*>();
  _variableList = new  QList <ConditionalVariable*>();
 makeEditConditionalWindow();
}

/**
 * Responds to Edit Button in the Conditional table of the Edit Logix Window
 */
void LogixTableAction::editConditionalPressed(int rx)
{
 if (inEditConditionalMode)
 {
        // Already editing a Conditional, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                java.text.MessageFormat.format(tr("Error34"),
//                        new Object[] { _curConditional::getSystemName() }),
//                tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Cannot edit two Conditionals at the same time. Please complete edit of Conditional \"%1\" and try again.").arg( _curConditional->getSystemName()));
        return;
    }
    // get Conditional to edit
    _curConditional = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(((DefaultLogix*)_curLogix)->getConditionalByNumberOrder(rx));
    if (_curConditional == NULL) {
        log->error("Attempted edit of non-existant conditional.");
        return;
    }
    _variableList = ((DefaultConditional*)_curConditional)->getCopyOfStateVariables();
    conditionalRowNumber = rx;
    // get action variables
    _actionList = ((DefaultConditional*)_curConditional)->getCopyOfActions();
    makeEditConditionalWindow();
}  /* editConditionalPressed */

/**
 * Checks if edit of a conditional is in progress Returns true after sending
 * message if this is the case
 */
bool LogixTableAction::checkEditConditional()
{
 if (inEditConditionalMode)
 {
  // Already editing a Conditional, ask for completion of that edit
//  javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                java.text.MessageFormat.format(tr("Error35"),
//                        new Object[] { _curConditional::getSystemName() }),
//                tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Edit conditional in progress. Please complete edit of Conditional \"%1\" and try again.").arg(_curConditional->getSystemName()));
  return true;
 }
 return false;
}

bool LogixTableAction::checkConditionalUserName(QString uName, Logix* logix)
{
 if ((uName != NULL) && (!(uName==(""))))
 {
  Conditional* p = ((DefaultConditionalManager*)_conditionalManager)->getByUserName(logix, uName);
  if (p != NULL)
  {
   // Conditional with this user name already exists
   log->error("Failure to update Conditional with Duplicate User Name: "
                    + uName);
//   javax.swing.JOptionPane.showMessageDialog(
//            editConditionalFrame, tr("Error10"), rbx
//                    .getString("Error"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(editConditionalFrame, tr("Error"), tr("New user name is already in use. Cannot update this Conditional::\nPlease change user name and try again."));
   return false;
  }
 } // else return false;
 return true;
}
bool LogixTableAction::checkConditionalSystemName(QString sName)
{
 if ((sName != NULL) && (!(sName==(""))))
 {
  Conditional* p = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(sName);
  if (p != NULL) return false;
 }
 else return false;
 return true;
}

/*********************** Edit Conditional Window and Methods********************/

/**
 * Creates and/or initializes the Edit Conditional window Note: you can get
 * here via the New Conditional button (newConditionalPressed) or via an
 * Edit button in the Conditional table of the Edit Logix window.
 */
void LogixTableAction::makeEditConditionalWindow()
{
 // deactivate this Logix
 ((DefaultLogix*)_curLogix)->deActivateLogix();
 conditionalUserName->setText(_curConditional->getUserName());
 if (editConditionalFrame == NULL)
 {
  editConditionalFrame = new JmriJFrame(tr("Edit Conditional"), false, false);
  editConditionalFrame->addHelpMenu(
        "package.jmri.jmrit.beantable.ConditionalAddEdit", true);
  if(editConditionalFrame->centralWidget() == NULL)
  {
   QWidget* centralWidget = new QWidget();
   editConditionalFrame->setCentralWidget(centralWidget);
  }
  editConditionalFrame->resize(400, 667);
  QFont font;
  font.setPointSize(9);
  editConditionalFrame->setFont(font);
  QWidget* contentPane = editConditionalFrame->centralWidget();
  contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
  QWidget* panel1 = new QWidget();
  QVBoxLayout* verticalLayout1;
  panel1->setLayout(verticalLayout1 = new  QVBoxLayout());
  QHBoxLayout* p1HBoxLayout1 = new QHBoxLayout();
  p1HBoxLayout1->addWidget(new QLabel(tr("Conditional System Name")));
  p1HBoxLayout1->addWidget(new QLabel(_curConditional->getSystemName()));
  verticalLayout1->addLayout(p1HBoxLayout1);
  QHBoxLayout* p1HBoxLayout2 = new QHBoxLayout();
  p1HBoxLayout2->setObjectName(QString::fromUtf8("p1HBoxLayout2"));
  p1HBoxLayout2->addWidget(new QLabel(tr("ConditionalUserName")));
  p1HBoxLayout2->addWidget(conditionalUserName);
  conditionalUserName->setToolTip(tr("Enter user name for Conditional, e.g. Signal 2 Red"));
  verticalLayout1->addLayout(p1HBoxLayout2);
  contentPane->layout()->addWidget(panel1);
  QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
  // add Logical Expression Section
  QGroupBox* logicPanel = new QGroupBox(tr("Logical Expression"));
  logicPanel->setLayout(new QVBoxLayout(logicPanel/*, BoxLayout.Y_AXIS)*/));
  logicPanel->setStyleSheet(gbStyleSheet);
  // add Antecedent Expression Panel -ONLY appears for MIXED operator statements
  _antecedent = ((DefaultConditional*)_curConditional)->getAntecedentExpression();
  _logicType = ((DefaultConditional*)_curConditional)->getLogicType();
  _antecedentField = new JTextField(65);
  _antecedentField->setFont( QFont("SansSerif", 14, QFont::Bold));
  _antecedentField->setText(_antecedent);
  _antecedentPanel = makeEditPanel(_antecedentField, "Antecedent Expression (the 'if' part of the Conditional)", "Insert parenthesis so the statement satisfies the logic you want");

  QPushButton* helpButton = new QPushButton(tr("Help"));
  _antecedentPanel->layout()->addWidget(helpButton);
//  helpButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        helpPressed(e);
//    }
//  });
  connect(helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()));
  _antecedentPanel->layout()->addWidget(helpButton);
  _antecedentPanel->setVisible(_logicType == Conditional::MIXED);
  logicPanel->layout()->addWidget(_antecedentPanel);

  // add state variable table title
  QWidget* varTitle = new QWidget();
  varTitle->setLayout(new QHBoxLayout());
  QFont font2 = varTitle->font();
  font2.setBold(true);
  varTitle->setFont(font2);
  varTitle->layout()->addWidget(new QLabel(tr("Antecedent Variables (the 'if' part)")));
  varTitle->layout()->setAlignment(Qt::AlignHCenter);
  logicPanel->layout()->addWidget(varTitle);
  // set up state variables table
  // initialize and populate Combo boxes for table of state variables
  _notOperatorBox = new QComboBox();
  _notOperatorBox->addItem(" ");
  _notOperatorBox->addItem(tr("NOT"));

  _andOperatorBox = new QComboBox();
  _andOperatorBox->addItem(tr(" AND"));
  _andOperatorBox->addItem(tr(" OR"));
  // initialize table of state variables
  _variableTableModel = new LVariableTableModel(this);
  QTableView* variableTable = new QTableView();
  variableTable->setModel(_variableTableModel);
  variableTable->setItemDelegateForColumn(LVariableTableModel::EDIT_COLUMN,new PushButtonDelegate());
  variableTable->setItemDelegateForColumn(LVariableTableModel::DELETE_COLUMN,new PushButtonDelegate());
  //variableTable.setRowHeight(_notOperatorBox.getPreferredSize().height);
  //variableTable.setRowSelectionAllowed(false);
  int rowHeight = variableTable->rowHeight(0);
#if 0
TableColumnModel variableColumnModel = variableTable.getColumnModel();

TableColumn rowColumn = variableColumnModel.getColumn(VariableTableModel.ROWNUM_COLUMN);
rowColumn.setResizable(false);
rowColumn.setMaxWidth(new JTextField(3).getPreferredSize().width);

TableColumn andColumn = variableColumnModel.getColumn(VariableTableModel.AND_COLUMN);
andColumn.setResizable(false);
andColumn.setCellEditor(new DefaultCellEditor(_andOperatorBox));
andColumn.setMaxWidth(_andOperatorBox.getPreferredSize().width - 5);

TableColumn notColumn = variableColumnModel.getColumn(VariableTableModel.NOT_COLUMN);
notColumn.setCellEditor(new DefaultCellEditor(_notOperatorBox));
notColumn.setMaxWidth(_notOperatorBox.getPreferredSize().width - 5);
notColumn.setResizable(false);

TableColumn descColumn = variableColumnModel.getColumn(VariableTableModel.DESCRIPTION_COLUMN);
descColumn.setPreferredWidth(300);
descColumn.setMinWidth(200);
descColumn.setResizable(true);

TableColumn stateColumn = variableColumnModel.getColumn(VariableTableModel.STATE_COLUMN);
stateColumn.setResizable(true);
stateColumn.setMinWidth(50);
stateColumn.setMaxWidth(80);

TableColumn triggerColumn = variableColumnModel.getColumn(VariableTableModel.TRIGGERS_COLUMN);
triggerColumn.setResizable(true);
triggerColumn.setMinWidth(30);
triggerColumn.setMaxWidth(80);

TableColumn editColumn = variableColumnModel.getColumn(VariableTableModel.EDIT_COLUMN);
ButtonRenderer buttonRenderer = new ButtonRenderer();
variableTable.setDefaultRenderer(QPushButton.class, buttonRenderer);
TableCellEditor buttonEditor = new ButtonEditor(new QPushButton());
variableTable.setDefaultEditor(QPushButton.class, buttonEditor);
QPushButton testButton = new QPushButton("XXXXXX");
variableTable.setRowHeight(testButton.getPreferredSize().height);
editColumn.setMinWidth(testButton.getPreferredSize().width);
editColumn.setMaxWidth(testButton.getPreferredSize().width);
editColumn.setResizable(false);

TableColumn deleteColumn = variableColumnModel.getColumn(VariableTableModel.DELETE_COLUMN);
// ButtonRenderer and TableCellEditor already set
deleteColumn.setMinWidth(testButton.getPreferredSize().width);
deleteColumn.setMaxWidth(testButton.getPreferredSize().width);
deleteColumn.setResizable(false);
// add a scroll pane
JScrollPane variableTableScrollPane = new JScrollPane(variableTable);
#endif
  QSize dim = variableTable->size();
  dim.setHeight(7*rowHeight);
  //variableTableScrollPane.getViewport().setPreferredSize(dim);

  logicPanel->layout()->addWidget(variableTable);

  // set up state variable buttons and logic
  QWidget* panel42 = new QWidget();
  panel42->setLayout(new QHBoxLayout());
        //  Add State Variable
  QPushButton*  addVariableButton = new QPushButton(tr("Add State Variable"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(addVariableButton->sizePolicy().hasHeightForWidth());
  panel42->layout()->addWidget(addVariableButton);
  addVariableButton->setSizePolicy(sizePolicy);
//  addVariableButton->layout()->addActionListener(new ActionListener(){
//    /*public*/ void actionPerformed(ActionEvent e) {
//        addVariablePressed(e);
//    }
//});
  connect(addVariableButton, SIGNAL(clicked()), this, SLOT(addVariablePressed()));

  QPushButton* checkVariableButton = new QPushButton(tr("Check State Variables"));
  checkVariableButton->setSizePolicy(sizePolicy);
  panel42->layout()->addWidget(checkVariableButton);
//checkVariableButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        checkVariablePressed(e);
//    }
//});
  connect(checkVariableButton, SIGNAL(clicked()), this, SLOT(checkVariablePressed()));
  checkVariableButton->setToolTip(tr("Press to evaluate current state of the Variables"));
  logicPanel->layout()->addWidget(panel42);

  // logic type area
  QStringList l = QStringList() << tr("AND") <<
          tr("OR") <<
          tr("Mixed");
 _operatorBox = new QComboBox();
 _operatorBox->addItems(l);
 QWidget* typePanel = makeEditPanel(_operatorBox, "Logic Operator", "Choose logic operator joining state variables for the antecedent ('if' part) of this conditional");
// _operatorBox->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        logicTypeChanged(e);
//    }
//});
 connect(_operatorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(logicTypeChanged()));
 _operatorBox->setCurrentIndex(_logicType-1);
 logicPanel->layout()->addWidget(typePanel);
 //logicPanel->layout()->addWidget(Box.createHorizontalStrut(STRUT));

//Border logicPanelBorder = BorderFactory.createEtchedBorder();
//Border logicPanelTitled = BorderFactory.createTitledBorder(
//        logicPanelBorder, tr("TitleLogicalExpression"));
 //logicPanel.setBorder(logicPanelTitled);
  //logicPanel->layout()->addWidget(logicPanelBorder);
 contentPane->layout()->addWidget(logicPanel);
 // End of Logic Expression Section

 _actionTableModel = new ActionTableModel(this);

  QWidget* triggerPanel = new QWidget();
  triggerPanel->setLayout(new QVBoxLayout(triggerPanel/*, BoxLayout.Y_AXIS*/));
  QButtonGroup* tGroup = new QButtonGroup();
  _triggerOnChangeButton = new QRadioButton(tr("Execute actions on change of state only"));
//  _triggerOnChangeButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        _actionTableModel.fireTableDataChanged();
//    }
//});
  connect(_triggerOnChangeButton, SIGNAL(toggled(bool)), _actionTableModel, SLOT(fireTableDataChanged()));
  tGroup->addButton(_triggerOnChangeButton);
  triggerPanel->layout()->addWidget(_triggerOnChangeButton);
  QRadioButton* triggerOnAny = new QRadioButton(tr("Execute Actions whenever triggered"));
//  triggerOnAny->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        _actionTableModel.fireTableDataChanged();
//    }
//});
  connect(_triggerOnChangeButton, SIGNAL(toggled(bool)), _actionTableModel, SLOT(fireTableDataChanged()));
  tGroup->addButton(triggerOnAny);
  triggerPanel->layout()->addWidget(triggerOnAny);
  triggerOnAny->setChecked(true);
  QWidget* trigPanel = new QWidget();
  trigPanel->setLayout(new QVBoxLayout());
  trigPanel->layout()->addWidget(triggerPanel);
  contentPane->layout()->addWidget(trigPanel);
  _triggerOnChangeButton->setChecked(((DefaultConditional*)_curConditional)->getTriggerOnChange());

  // add Action Consequents Section
  QGroupBox* consequentPanel = new QGroupBox(tr("Actions"));
  consequentPanel->setLayout(new QVBoxLayout(consequentPanel/*, BoxLayout.Y_AXIS*/));
 consequentPanel->setStyleSheet(gbStyleSheet);

  QWidget* actTitle = new QWidget();
  actTitle->setLayout(new QHBoxLayout());
  QFont font3 = actTitle->font();
  font3.setBold(true);
  actTitle->setFont(font3);
  actTitle->layout()->addWidget(new QLabel(tr("Consequent Actions (the 'then' part) ")));
  actTitle->layout()->setAlignment(Qt::AlignHCenter);

  consequentPanel->layout()->addWidget(actTitle);

  // set up action consequents table
  //_actionTableModel = new ActionTableModel(this);
  QTableView* actionTable = new QTableView();
  actionTable->setModel(_actionTableModel);
  //actionTable.setRowSelectionAllowed(false);
  //actionTable.setRowHeight(testButton.getPreferredSize().height);
//  QWidget* actionPanel = new QWidget();
//  actionPanel->setLayout(new QVBoxLayout(actionPanel/*, BoxLayout.Y_AXIS*/));
//  QWidget* actionTitle = new QWidget();
//  actionTitle->setLayout(new QHBoxLayout());
//  consequentPanel->layout()->addWidget(actionPanel);
  consequentPanel->layout()->addWidget(actionTable);
  actionTable->setColumnWidth(ActionTableModel::DESCRIPTION_COLUMN, 300);
#if 0
TableColumnModel actionColumnModel = actionTable.getColumnModel();

TableColumn descriptionColumn = actionColumnModel.getColumn(
    ActionTableModel.DESCRIPTION_COLUMN);
descriptionColumn.setResizable(true);
descriptionColumn.setPreferredWidth(600);
descriptionColumn.setMinWidth(300);
//descriptionColumn.setMaxWidth(760);

TableColumn actionEditColumn = actionColumnModel.getColumn(ActionTableModel.EDIT_COLUMN);
// ButtonRenderer already exists
actionTable.setDefaultRenderer(QPushButton.class, buttonRenderer);
TableCellEditor editButEditor = new ButtonEditor(new QPushButton());
actionTable.setDefaultEditor(QPushButton.class, editButEditor);
actionEditColumn.setMinWidth(testButton.getPreferredSize().width);
actionEditColumn.setMaxWidth(testButton.getPreferredSize().width);
actionEditColumn.setResizable(false);

TableColumn actionDeleteColumn = actionColumnModel.getColumn(ActionTableModel.DELETE_COLUMN);
// ButtonRenderer and TableCellEditor already set
actionDeleteColumn.setMinWidth(testButton.getPreferredSize().width);
actionDeleteColumn.setMaxWidth(testButton.getPreferredSize().width);
actionDeleteColumn.setResizable(false);
// add a scroll pane
JScrollPane actionTableScrollPane = new JScrollPane(actionTable);
#endif

//dim = actionTableScrollPane.getPreferredSize();
//dim.height = 7*rowHeight;
//actionTableScrollPane.getViewport().setPreferredSize(dim);
  consequentPanel->layout()->addWidget(actionTable);

  // add action buttons to Action Section
  QWidget* panel43 = new QWidget();
  panel43->setLayout(new QHBoxLayout());
  QPushButton* addActionButton = new QPushButton(tr("Add Action"));
  QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addActionButton->sizePolicy().hasHeightForWidth());
  addActionButton->setSizePolicy(sizePolicy1);
  panel43->layout()->addWidget(addActionButton);
//  addActionButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        addActionPressed(e);
//    }
//  });
  connect(addActionButton, SIGNAL(clicked()), this, SLOT(addActionPressed()));

  addActionButton->setToolTip(tr("Press to add a new row to Action Table"));
  consequentPanel->layout()->addWidget(panel43);
  //  - Reorder action button
  QPushButton* reorderButton = new QPushButton(tr("ReorderButton"));
  reorderButton->setSizePolicy(sizePolicy);
  panel43->layout()->addWidget(reorderButton);
//  reorderButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        reorderActionPressed(e);
//    }
//  });
  connect(reorderButton, SIGNAL(clicked()), this, SLOT(reorderActionPressed()));
  reorderButton->setToolTip(tr("Press then click in right column in order desired"));
  consequentPanel->layout()->addWidget(panel43);

//  Border conseqentPanelBorder = BorderFactory.createEtchedBorder();
//  Border conseqentPanelTitled = BorderFactory.createTitledBorder(
//        conseqentPanelBorder, tr("TitleAction"));
//  conseqentPanel.setBorder(conseqentPanelTitled);
//  consequentPanel->setFrameStyle(QFrame::Box | QFrame::Raised);
//  consequentPanel->setLineWidth(2);
  contentPane->layout()->addWidget(consequentPanel);
  // End of Action Consequents Section

  // Bottom Buttons - Update Conditional
  QWidget* panel5 = new QWidget();
  panel5->setLayout(new QHBoxLayout());
  QPushButton* updateConditional = new QPushButton(tr("UpdateConditionalButton"));
  panel5->layout()->addWidget(updateConditional);
//  updateConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        updateConditionalPressed(e);
//    }
//  });
  connect(updateConditional, SIGNAL(clicked()), this, SLOT(updateConditionalPressed()));
  updateConditional->setToolTip(tr("Press to keep changes and return to Edit Logix"));
  // Cancel
  QPushButton* cancelConditional = new QPushButton(tr("CancelButton"));
  panel5->layout()->addWidget(cancelConditional);
//  cancelConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        cancelConditionalPressed(e);
//    }
//  });
  connect(cancelConditional, SIGNAL(clicked()), this, SLOT(cancelConditionalPressed()));
  cancelConditional->setToolTip(tr("Press to return to Edit Logix without any changes"));
  // Delete Conditional
  QPushButton* deleteConditional = new QPushButton(tr("DeleteConditionalButton"));
  panel5->layout()->addWidget(deleteConditional);
//  deleteConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        deleteConditionalPressed(NULL);
//    }
//  });
  connect(deleteConditional, SIGNAL(clicked()), this, SLOT(deleteConditionalPressed()));
  deleteConditional->setToolTip(tr("Press to delete this Conditional and return to Edit Logix"));

  contentPane->layout()->addWidget(panel5);
 }
//    // setup window closing listener
//    editConditionalFrame->layout()->addWidgetWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelConditionalPressed(NULL);
//                }
//            });
 // initialize state variable table
 _variableTableModel->fireTableDataChanged();
 // initialize action variables
 _actionTableModel->fireTableDataChanged();
 editConditionalFrame->adjustSize();
 editConditionalFrame->setVisible(true);
 inEditConditionalMode = true;
 checkVariablePressed(NULL);     // update variables to their current states
}   /* makeEditConditionalWindow */
#if 1
/**
 * Responds to the Add State Variable Button in the Edit Conditional window
 */
void LogixTableAction::addVariablePressed(ActionEvent* /*e*/)
{
 if (alreadyEditingActionOrVariable())
 {
  return;
 }
 if (LRouteTableAction::LOGIX_INITIALIZER==(((DefaultLogix*)_curLogix)->getSystemName()))
 {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Error49"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(editConditionalFrame, tr("Error"), tr("LRoute Initializer antecedent cannot be edited.  (The actions may be edited)"));
  return;
 }
 _showReminder = true;
 ConditionalVariable* variable = new ConditionalVariable();
 _variableList->append(variable);
 _newItem = true;
 int size = _variableList->size();
 // default of operator for postion 0 (row 1) is Conditional::OPERATOR_NONE
 if (size > 1)
 {
  if (_logicType == Conditional::ALL_OR)
   variable->setOpern(Conditional::OPERATOR_OR);
  else
   variable->setOpern(Conditional::OPERATOR_AND);
 }
 size--;
 _variableTableModel->fireTableRowsInserted(size, size);
 makeEditVariableWindow(size);
 appendToAntecedent(variable);
}
#endif
/**
 * Responds to the Check State Variable Button in the Edit Conditional window
 */
void LogixTableAction::checkVariablePressed(ActionEvent* /*e*/) {
    for (int i=0; i<_variableList->size(); i++)
    {
        _variableList->at(i)->evaluate();
    }
    _variableTableModel->fireTableDataChanged();
}

/**
 * Responds to the Negation column in the Edit Conditional window
 */
void LogixTableAction::variableNegationChanged(int row, QString oper) {
    ConditionalVariable* variable = _variableList->at(row);
    bool state = variable->isNegated();
    if (oper == NULL)
        variable->setNegation(false);
    else
        variable->setNegation(oper==(tr("NOT")));
    if (variable->isNegated() != state )
        makeAntecedent();
}

/**
 * Responds to the Operator column in the Edit Conditional window
 */
void LogixTableAction::variableOperatorChanged(int row, QString oper) {
    ConditionalVariable* variable = _variableList->at(row);
    int oldOper = variable->getOpern();
    if (row > 0)
    {
        if (oper==(tr("OR")))
            variable->setOpern(Conditional::OPERATOR_OR);
        else
            variable->setOpern(Conditional::OPERATOR_AND);
    }
    else
        variable->setOpern(Conditional::OPERATOR_NONE);
    if (variable->getOpern() != oldOper )
        makeAntecedent();

}
#if 1
/*
* Responds to Add action button in the EditConditional window
*/
void LogixTableAction::addActionPressed(ActionEvent* /*e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _showReminder = true;
    _actionList->append(new DefaultConditionalAction());
    _newItem = true;
    _actionTableModel->fireTableRowsInserted(_actionList->size(),
            _actionList->size());
    makeEditActionWindow(_actionList->size() - 1);
    _pickTables->setWindowState(Qt::WindowActive);
}

/**
 * Responds to the Reorder Button in the Edit Conditional window
 */
void LogixTableAction::reorderActionPressed(ActionEvent* /*e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _showReminder = true;
    // Check if reorder is reasonable
    if (_actionList->size() <= 1) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
//                .getString("Error46"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLogixFrame, tr("Error"), tr("At least two Actions are needed to reorder Actions."));
        return;
    }
    _nextInOrder = 0;
    _inReorderMode = true;
    //status->setText(tr("ReorderMessage"));
    _actionTableModel->fireTableDataChanged();
}
#endif
/**
 * Responds to the First/Next (Delete) Button in the Edit Conditional window
 */
void LogixTableAction::swapActions(int row) {
    ConditionalAction* temp = _actionList->at(row);
    for (int i = row; i > _nextInOrder; i--)
    {
        _actionList->replace(i, _actionList->at(i-1));
    }
    _actionList->replace(_nextInOrder, temp);
    _nextInOrder++;
    if (_nextInOrder >= _actionList->size())
    {
        _inReorderMode = false;
    }
    //status->setText("");
    _actionTableModel->fireTableDataChanged();
}
#if 1
/**
* Responds to the Update Conditional Button in the Edit Conditional window
*/
void LogixTableAction::updateConditionalPressed(ActionEvent* /*e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    // clean up empty variable and actions
    if (LRouteTableAction::LOGIX_INITIALIZER!=(((DefaultLogix*)_curLogix)->getSystemName())) {
        for (int i=0; i<_variableList->size(); i++) {
            if (_variableList->at(i)->getType() == Conditional::TYPE_NONE) {
                _variableList->removeAt(i);
                _variableTableModel->fireTableRowsDeleted(i, i);
            }
        }
    }
    for (int i=0; i<_actionList->size(); i++) {
        if (_actionList->at(i)->getType() == Conditional::ACTION_NONE) {
            _actionList->removeAt(i);
            _actionTableModel->fireTableRowsDeleted(i, i);
        }
    }

    if (_variableList->size() <= 0 && _actionList->size() <= 0) {
        deleteConditionalPressed(NULL);
        return;
    }
  /*  if (_curConditional==NULL) {
        return;
    } */
    if (((DefaultLogix*)_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName)) {
//        javax.swing.JOptionPane.showMessageDialog(
//                editConditionalFrame, java.text.MessageFormat.format(tr("Warn8"),
//                    new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName})+
//                    java.text.MessageFormat.format(tr("Warn11"),
//                    new Object[] {_curConditional::getUserName(), _curConditional::getSystemName() }),
//                    rbx .getString("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(editConditionalFrame, tr("Warning"),tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName));
        cancelConditionalPressed(NULL);
        return;
    }
    // Check if the User Name has been changed
    QString uName = conditionalUserName->text().trimmed();
    if (uName!=NULL && !(uName==(_curConditional->getUserName()))) {
        // user name has changed - check if already in use
        if (!checkConditionalUserName(uName, _curLogix)) {
            return;
        }
        // user name is unique or blank, change it
        _curConditional->setUserName(uName);
        conditionalTableModel->fireTableDataChanged();
    }
    if (_variableList->size() <= 0 && !_suppressReminder) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Warn5"),
//                        new Object[] {_curConditional::getUserName(), _curConditional::getSystemName() }),
//                         tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(editLogixFrame, tr("Warning"), tr("The Conditional %1 (%2) has no State Variables.\nA Conditional must have at least one State Variable to do anything useful.").arg(_curConditional->getUserName()).arg(_curConditional->getSystemName()));
    }

    if (!validateAntecedent()) {
        return;
    }
    // complete update
    ((DefaultConditional*)_curConditional)->setStateVariables(_variableList);
    ((DefaultConditional*)_curConditional)->setAction(_actionList);
    ((DefaultConditional*)_curConditional)->setLogicType(_logicType, _antecedent);
    ((DefaultConditional*)_curConditional)->setTriggerOnChange(_triggerOnChangeButton->isChecked());
    cancelConditionalPressed(NULL);
}

/**
 * Responds to the Cancel button in the Edit Conditional frame
 * Does the cleanup from deleteConditionalPressed, updateConditionalPressed
 * and editConditionalFrame window closer.
 */
void LogixTableAction::cancelConditionalPressed(ActionEvent* /*e*/) {
    if (_pickTables!=NULL) {
        _pickTables->dispose();
        _pickTables = NULL;
    }
    if (_editActionFrame != NULL) {
        cleanUpAction();
    }
    if (_editVariableFrame != NULL) {
        cleanUpVariable();
    }
    try {
        ((DefaultLogix*)_curLogix)->activateLogix();
    } catch (NumberFormatException nfe) {
        if (log->isDebugEnabled()) log->error("NumberFormatException on activation of Logix "+nfe.getMessage());
        //nfe.printStackTrace();
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                tr("Error4")+nfe.toString()+tr("Error7"),
//                tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLogixFrame, tr("Error"), tr("The following error occurred when activating this Logix.")+nfe.getMessage()+tr("Please correct the reference or delete the offending Conditional or Logix."));
    }
    // when user uses the escape key and returns to editing, interaction with
    // window closing event create strange environment
    inEditConditionalMode = false;
    if (editConditionalFrame != NULL) {
        //editConditionalFrame->setVisible(false);
        editConditionalFrame->dispose();
        editConditionalFrame = NULL;
    }
    if (editLogixFrame !=NULL) {
        editLogixFrame->setVisible(true);
    }
}

/**
 * Responds to the Delete Conditional Button in the Edit Conditional window
 */
void LogixTableAction::deleteConditionalPressed(QString sName) {
    if (_curConditional==NULL) {
        return;
    }
    // delete this Conditional - this is done by the parent Logix
    if (sName == "") {
        sName = _curConditional->getSystemName();
    }
    if (sName == NULL) {
        if (log->isDebugEnabled()) log->error("Unable to delete Conditional, NULL system name");
        return;
    }
    _showReminder = true;
    _curConditional = NULL;
    numConditionals--;
    QStringList* msgs = ((DefaultLogix*)_curLogix)->deleteConditional(sName);
    if (msgs != NULL) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Error11"), (Object[])msgs),
//                tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLogixFrame, tr("Error"), tr("Conditional \"%1\" (%2) is a Conditional Variable in the Conditional,\n\"%3\" (%4), of Logix, \"%5\" (%6).\n                                                          Please remove that variable first.").arg(msgs->at(0)).arg(msgs->at(1)).arg(msgs->at(2)).arg(msgs->at(3)).arg(msgs->at(4)).arg(msgs->at(5)));
    }
    // complete deletion
    cancelConditionalPressed(NULL);
    conditionalTableModel->fireTableRowsDeleted(conditionalRowNumber,
            conditionalRowNumber);
    if (numConditionals < 1 && !_suppressReminder) {
        // warning message - last Conditional deleted
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
//                .getString("Warn1"), tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(editLogixFrame, tr("Warning"), tr("The last Conditional has been deleted from this Logix."));
    }
}


//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
bool LogixTableAction::logicTypeChanged(ActionEvent* /*e*/) {
    int type = _operatorBox->currentIndex() + 1;
    if (type == _logicType) {
            return false;
    }
    makeAntecedent();
    int oper = Conditional::OPERATOR_OR;
    switch (type) {
        case Conditional::ALL_AND:
            oper = Conditional::OPERATOR_AND;
            // fall through
        case Conditional::ALL_OR:
            for (int i=1; i<_variableList->size(); i++)
            {
                _variableList->at(i)->setOpern(oper);
            }
            _antecedentPanel->setVisible(false);
            break;
        case Conditional::MIXED:
            _antecedentPanel->setVisible(true);
        default : break;
    }
    _logicType = type;
    _variableTableModel->fireTableDataChanged();
    //editConditionalFrame.repaint();
    return true;
}

void LogixTableAction::helpPressed(ActionEvent* /*e*/) {
#if 0
    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
            new String[] {
                tr("LogicHelpText1"),
                tr("LogicHelpText2"),
                tr("LogicHelpText3"),
                tr("LogicHelpText4"),
                tr("LogicHelpText5"),
                tr("LogicHelpText6"),
                tr("LogicHelpText7")
            },
    tr("HelpButton"), javax.swing.JOptionPane.INFORMATION_MESSAGE);
#endif
}
#endif
/**
* build the antecedent statement
*/
void LogixTableAction::makeAntecedent()
{
 QString str = "";
 if (_variableList->size()!=0)
 {
        QString _not = tr("NOT").toLower();
        QString row = tr("R");
        QString _and = " " + tr("AND").toLower() + " ";
        QString _or = " " + tr("OR").toLower() + " ";
        if (_variableList->at(0)->isNegated())
        {
            str = _not+ " ";
        }
        str = str + row + "1";
        for (int i=1; i<_variableList->size(); i++) {
            ConditionalVariable* variable = _variableList->at(i);
            switch (variable->getOpern() ) {
                case Conditional::OPERATOR_AND:
                    str = str + _and;
                    break;
                case Conditional::OPERATOR_OR:
                    str = str + _or;
                    break;
                default : break;
            }
            if (variable->isNegated())
            {
                str = str + _not;
            }
            str = str + row + (i+1);
            if (i>0 && i+1<_variableList->size()) {
                str = "(" + str  + ")";
            }
        }
    }
    _antecedent = str;
    _antecedentField->setText(_antecedent);
    _showReminder = true;
}

void LogixTableAction::appendToAntecedent(ConditionalVariable* /*variable*/)
{
 if (_variableList->size() > 1)
 {
  if (_logicType == Conditional::OPERATOR_OR)
  {
   _antecedent = _antecedent + " " + tr("OR").toLower() + " ";
  }
  else
  {
   _antecedent = _antecedent + " " + tr("AND").toLower() + " ";
  }
 }
  _antecedent = _antecedent + tr("R") + _variableList->size();
  _antecedentField->setText(_antecedent);
}

/**
*  Check the antecedent and logic type
*/
bool LogixTableAction::validateAntecedent()
{
 if (_logicType !=Conditional::MIXED || LRouteTableAction::LOGIX_INITIALIZER==(((DefaultLogix*)_curLogix)->getSystemName()))
 {
  return true;
 }
 _antecedent = _antecedentField->text();
 if (_antecedent == "" || _antecedent.trimmed().length() == 0)
 {
  makeAntecedent();
 }
 QString message = ((DefaultConditional*)_curConditional)->validateAntecedent(_antecedent, _variableList);
 if (message != "")
 {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                message+tr("ParseError8"),  tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(editConditionalFrame, tr("Error"), tr("If the above message is 'String index out of range:', the following number is the position in the antecedent where the error occurred."));
  return false;
 }
 return true;
}

/************************* Methods for Edit Variable Window ********************/

bool LogixTableAction::alreadyEditingActionOrVariable()
{
 OpenPickListTable();
 if (_editActionFrame != NULL)
 {
        // Already editing an Action, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(_editActionFrame,
//                tr("Error48"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editActionFrame, tr("Error"), tr("Edit of Action in progress. Please complete edit and try again."));
  _editActionFrame->setVisible(true);
  return true;
 }
 if (_editVariableFrame != NULL)
 {
        // Already editing a state variable, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(_editVariableFrame,
//                tr("Error47"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editActionFrame, tr("Error"), tr("Edit of State Variable in progress. Please complete and try again."));
  _editVariableFrame->setVisible(true);
  return true;
 }
 return false;
}

/**
 * Creates and/or initializes the Edit a Variable window Note: you can get
 * here via the New Variable button (addVariablePressed) or via an
 * Edit button in the Variable table of the EditConditional window.
 */
void LogixTableAction::makeEditVariableWindow(int row)
{
 if (alreadyEditingActionOrVariable())
 {
  return;
 }
 _curVariableRowNumber = row;
 _curVariable = _variableList->at(row);
 _editVariableFrame = new JmriJFrame(tr("Edit Variable"), true, true);
 //_editVariableFrame->setLocation(10, 100);
 QWidget* topPanel = makeTopPanel(_editVariableFrame, "Antecedent Variable", 500, 120);
 _editVariableFrame->setAcceptDrops(true);
//    Box panel1 = Box.createHorizontalBox();
//    panel1->layout()->addWidget(Box.createHorizontalGlue());
//    panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// QFrame* panel1 = new QFrame();
// panel1->setLayout(new QHBoxLayout());
 QHBoxLayout* panel1HLayout = new QHBoxLayout();
 ((QVBoxLayout*)topPanel->layout())->addLayout(panel1HLayout);
// Item Type
 _variableTypeBox = new QComboBox();
 _variableTypeBox->setLayout(new QVBoxLayout());
 for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_STATE_VAR; i++)
 {
  _variableTypeBox->addItem(ConditionalVariable::getItemTypeString(i));
 }
 panel1HLayout->addWidget(makeEditPanel(_variableTypeBox, tr("Variable Type"), tr("Select type of state variable for Conditional to test")));
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
 panel1HLayout->addStrut(50);
// Item Name
 _variableNameField = new JTextField(30);
 _variableNameField->setMinimumWidth(150);

 _variableNamePanel = makeEditPanel(_variableNameField, "System / User Name", "");
 _variableNamePanel->setMinimumSize(
              QSize(50, _variableNamePanel->size().height()));
 _variableNamePanel->setVisible(false);
  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHorizontalStretch(1);
  sizePolicy.setHeightForWidth(_variableNamePanel->sizePolicy().hasHeightForWidth());
  _variableNamePanel->setSizePolicy(sizePolicy);
 panel1HLayout->addWidget(_variableNamePanel);
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// State Box
 _variableStateBox = new QComboBox();
 _variableStateBox->addItem("XXXXXXX");
 _variableStatePanel = makeEditPanel(_variableStateBox, tr("Variable State"), tr("Select the state of the variable to test"));
 _variableStatePanel->setVisible(false);
 panel1HLayout->addWidget(_variableStatePanel);
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
 // Aspects
 _variableSignalBox = new QComboBox();
 _variableSignalBox->addItem("XXXXXXXXX");
 _variableSignalPanel = makeEditPanel(_variableSignalBox, tr("Variable Aspect"), tr("Select the Aspect of the Signal to test"));
 _variableSignalPanel->setVisible(false);
 panel1HLayout->addWidget(_variableSignalPanel);
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// Compare operator
 _variableComparePanel = new QWidget();
 _variableComparePanel->setLayout(new QHBoxLayout(_variableComparePanel/*, BoxLayout.X_AXIS*/));
 _variableCompareOpBox = new QComboBox();
 for (int i = 1; i <= ConditionalVariable::NUM_COMPARE_OPERATIONS; i++)
 {
  _variableCompareOpBox->addItem(ConditionalVariable::getCompareOperationString(i));
 }
 _variableComparePanel->layout()->addWidget(makeEditPanel(_variableCompareOpBox, tr("Comparison Operator"), tr("Select an operator to compare memory values")));
 //_variableComparePanel->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// Compare type
_variableCompareTypeBox = new QComboBox();
 for (int i = 0; i < Conditional::ITEM_TO_MEMORY_TEST.length(); i++)
 {
     _variableCompareTypeBox->addItem(ConditionalVariable::getStateString(Conditional::ITEM_TO_MEMORY_TEST.at(i)));
 }
 _variableComparePanel->layout()->addWidget(makeEditPanel(_variableCompareTypeBox, tr("Compare as"), tr("Select either a literal value or the value in a memory location")));
 _variableComparePanel->setVisible(false);
//    _variableCompareTypeBox->layout()->addWidgetItemListener(new ItemListener() {
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            compareTypeChanged(_variableCompareTypeBox->currentIndex());
//            _editVariableFrame.pack();
//        }
//    });
 connect(_variableCompareTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(itemStateChanged(int)));
 panel1HLayout->addWidget(_variableComparePanel);
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// Data 1
 _variableData1Field = new JTextField(30);
 _variableData1Panel = makeEditPanel(_variableData1Field, tr("Start Time"), tr("Enter time (hh:mm) for a 24-hour clock"));
 _variableData1Panel->setMaximumSize(
              QSize(45, _variableData1Panel->size().height()));
 _variableData1Panel->setVisible(false);
 panel1HLayout->addWidget(_variableData1Panel);
 //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));
// Data 2
 _variableData2Field = new JTextField(30);
 _variableData2Panel = makeEditPanel(_variableData2Field, tr("End Time"), tr("Enter time (hh:mm) for a 24-hour clock"));
 _variableData2Panel->setMaximumSize(
             QSize(45, _variableData2Panel->size().height()));
 _variableData2Panel->setVisible(false);
 panel1HLayout->addWidget(_variableData2Panel);
// panel1VLayout->addWidget(Box.createHorizontalStrut(STRUT));
// panel1->layout()->addWidget(Box.createHorizontalGlue());
 //topPanel->layout()->addWidget(panel1);

// ActionListener updateListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updateVariablePressed();
//            }
//        };
 QPushButton* updateListener = new QPushButton();
 connect(updateListener, SIGNAL(clicked()), this, SLOT(updateVariablePressed()));
//   ActionListener cancelListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               cancelEditVariablePressed();
//           }cancelListener
//       };
 QPushButton* cancelListener = new QPushButton();
 connect(cancelListener, SIGNAL(clicked()), this, SLOT(cancelEditVariablePressed()));

//   ActionListener deleteListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               deleteVariablePressed();
//           }
//       };
 QPushButton* deleteListener = new QPushButton();
 connect(deleteListener, SIGNAL(clicked()), this, SLOT(deleteVariablePressed()));

 QWidget* panel = makeButtonPanel(updateListener, cancelListener, deleteListener);
 topPanel->layout()->addWidget(panel);
 //topPanel->layout()->addWidget(Box.createVerticalGlue());

 if(_editVariableFrame->centralWidget()== NULL)
 {
     QWidget* centralWidget = new QWidget();
     centralWidget->setLayout(new QVBoxLayout);
     _editVariableFrame->setCentralWidget(centralWidget);
 }
 QWidget* contentPane = _editVariableFrame->centralWidget();
 contentPane->layout()->addWidget(topPanel);
 // note - this listener cannot be added before other action items
 // have been created
// _variableTypeBox->addItemListener(new ItemListener() {
//       /*public*/ void itemStateChanged(ItemEvent e) {
//            variableTypeChanged(_variableTypeBox->currentIndex());
//            _editVariableFrame.pack();
//        }
//    });
 connect(_variableTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(variableItemStateChanged(int)));
    // setup window closing listener
//    _editVariableFrame->addWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelEditVariablePressed();
//                }
//            });
 _editVariableFrame->addWindowListener(editVariableFrameWindowListener = new EditVariableFrameWindowListener(this));
 initializeStateVariables();
 _editVariableFrame->setMinimumSize(300,400);
 _editVariableFrame->adjustSize();
 _editVariableFrame->setVisible(true);
}

EditVariableFrameWindowListener::EditVariableFrameWindowListener(LogixTableAction *self)
{
 this->self = self;
}

void EditVariableFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelEditVariablePressed();
}

void LogixTableAction::itemStateChanged(int index)
{
 compareTypeChanged(index);
 _editVariableFrame->adjustSize();
}
void LogixTableAction::variableItemStateChanged(int index)
{
 variableTypeChanged(index);
 _editVariableFrame->adjustSize();
}

/***************************** Edit Action Window and methods ***********************/

/**
 * Creates and/or initializes the Edit Action window Note: you can get
 * here via the New Action button (addActionPressed) or via an
 * Edit button in the Action table of the EditConditional window.
 */
void LogixTableAction::makeEditActionWindow(int row)
{
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _curActionRowNumber = row;
    _curAction = _actionList->at(row);
    _editActionFrame = new JmriJFrame(tr("Edit Action"), true, true);
#if 1
//        _editActionFrame.setLocation(10, 300);
    QWidget* topPanel = makeTopPanel(_editActionFrame, "Consequent Action ", 600, 160);

//    Box panel1 = Box.createHorizontalBox();
//    panel1->layout()->addWidget(Box.createHorizontalGlue());
    QWidget* panel1 = new QWidget();
    panel1->setLayout(new QHBoxLayout());

    _actionItemTypeBox = new QComboBox();
    for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_ACTION; i++) {
        _actionItemTypeBox->addItem(DefaultConditionalAction::getItemTypeString(i));
    }
    panel1->layout()->addWidget(makeEditPanel(_actionItemTypeBox, "Action Group", "Select action item for Conditional to execute"));
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionNameField = new JTextField(30);
    _actionNameField->setMinimumWidth(80);
    _namePanel = makeEditPanel(_actionNameField, "System / User Name", NULL);
    _namePanel->setMaximumSize(
                QSize(50, _namePanel->size().height()));
    _namePanel->setVisible(false);
    panel1->layout()->addWidget(_namePanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionTypeBox = new QComboBox();
    _actionTypeBox->addItem("");
    _actionTypePanel = makeEditPanel(_actionTypeBox, "Action Type", "Select type of action, or select None if no action is needed.");
    _actionTypePanel->setVisible(false);
    panel1->layout()->addWidget(_actionTypePanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionBox = new QComboBox();
    _actionBox->addItem("");
    _actionPanel = makeEditPanel(_actionBox, "Action Type", "Select type of action, or select None if no action is needed.");
    _actionPanel->setVisible(false);
    panel1->layout()->addWidget(_actionPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _shortActionString = new JTextField(15);
    _shortTextPanel = makeEditPanel(_shortActionString, "Action Data", NULL);
    _shortTextPanel->setMaximumSize(
                QSize(25, _shortTextPanel->size().height()));
    //_shortTextPanel->layout()->addWidget(Box.createVerticalGlue());
    _shortTextPanel->setVisible(false);
    panel1->layout()->addWidget(_shortTextPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionOptionBox = new QComboBox();
    for (int i = 1; i <= Conditional::NUM_ACTION_OPTIONS; i++) {
        _actionOptionBox->addItem(DefaultConditionalAction::getOptionString(i,_triggerOnChangeButton->isChecked()));
    }
    _optionPanel = makeEditPanel(_actionOptionBox, "Change Option", "Select when action should occur");
    _optionPanel->setVisible(false);
    panel1->layout()->addWidget(_optionPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    //panel1->layout()->addWidget(Box.createHorizontalGlue());
    topPanel->layout()->addWidget(panel1);
    //topPanel->layout()->addWidget(Box.createVerticalStrut(5));
    //topPanel->layout()->addWidget(Box.createVerticalGlue());

//    Box panel2 = Box.createHorizontalBox();
//    panel2->layout()->addWidget(Box.createHorizontalGlue());
    QGroupBox* panel2 = new QGroupBox();
    panel2->setLayout(new QVBoxLayout());

    _setPanel = new QWidget();
    _setPanel->setLayout(new QVBoxLayout(_setPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* p = new QWidget();
    p->setLayout(new QVBoxLayout());
    p->layout()->addWidget(new QLabel(tr("Set File")));
    _setPanel->layout()->addWidget(p);
    _actionSetButton = new QPushButton(tr("File"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_actionSetButton->sizePolicy().hasHeightForWidth());
    _actionSetButton->setSizePolicy(sizePolicy);
//    _actionSetButton->layout()->addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                validateAction();
//                setFileLocation(e);
//            }
//        });
    connect(_actionSetButton, SIGNAL(clicked()), this, SLOT(on_actionSetButton_Pressed()));
    _actionSetButton->setMaximumSize(_actionSetButton->size());
    _setPanel->layout()->addWidget(_actionSetButton);
    //_setPanel->layout()->addWidget(Box.createVerticalGlue());
    _setPanel->setVisible(false);
    panel2->layout()->addWidget(_setPanel);
    //panel2->layout()->addWidget(Box.createHorizontalStrut(5));

    _longActionString = new JTextField(50);
    _textPanel = makeEditPanel(_longActionString, "LabelActionText", NULL);
    _textPanel->setMaximumSize(
                 QSize(80, _textPanel->size().height()));
    //_textPanel->layout()->addWidget(Box.createVerticalGlue());
    _textPanel->setVisible(false);
    panel2->layout()->addWidget(_textPanel);
    //panel2->layout()->addWidget(Box.createHorizontalGlue());
    topPanel->layout()->addWidget(panel2);
//    topPanel->layout()->addWidget(Box.createVerticalStrut(5));
//    topPanel->layout()->addWidget(Box.createVerticalGlue());

//    ActionListener updateListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updateActionPressed();
//            }
//        };
    QPushButton* updateButton = new QPushButton();
    updateButton->setSizePolicy(sizePolicy);
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateActionPressed()));
//   ActionListener cancelListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               cancelEditActionPressed();
//           }
//       };
    QPushButton* cancelButton = new QPushButton();
    cancelButton->setSizePolicy(sizePolicy);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelEditActionPressed()));
//   ActionListener deleteListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               deleteActionPressed();
//           }
//       };
    QPushButton* deleteButton = new QPushButton();
    deleteButton->setSizePolicy(sizePolicy);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteActionPressed()));
    QWidget* panel = makeButtonPanel(updateButton, cancelButton, deleteButton);
    topPanel->layout()->addWidget(panel);
    //topPanel->layout()->addWidget(Box.createVerticalGlue());

    if(_editActionFrame->centralWidget() == NULL)
    {
        QWidget* centralWidget = new QWidget();
        centralWidget->setLayout(new QVBoxLayout());
        _editActionFrame->setCentralWidget(centralWidget);
    }
    QWidget* contentPane = _editActionFrame->centralWidget();
    contentPane->layout()->addWidget(topPanel);
    // note - this listener cannot be added until all items are entered into _actionItemTypeBox
//    _actionItemTypeBox->addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            int select = _actionItemTypeBox->currentIndex();
//            if (log->isDebugEnabled()) log->debug("_actionItemTypeBoxListener: select= "+select);
//            actionItemChanged(select);
//            _editActionFrame.pack();
//        }
//    });
    connect(_actionItemTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_actionItemType_changed(int)));
//    // setup window closing listener
//    _editActionFrame->addWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelEditActionPressed();
//                }
//            });
    _editActionFrame->addWindowListener(editActionFrameWindowListener = new EditActionFrameWindowListener(this));
    actionItemChanged(Conditional::TYPE_NONE);
    initializeActionVariables();
    _editActionFrame->setVisible(true);
    _editActionFrame->adjustSize();
#endif
} /* makeEditActionWindow */

EditActionFrameWindowListener::EditActionFrameWindowListener(LogixTableAction *self)
{
 this->self = self;
}
void EditActionFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelEditActionPressed();
}

void LogixTableAction::on_actionItemType_changed(int select)
{
 if (log->isDebugEnabled()) log->debug("_actionItemTypeBoxListener: select= "+select);
  actionItemChanged(select);
  _editActionFrame->adjustSize();
}

void LogixTableAction::on_actionSetButton_Pressed()
{
  validateAction();
  setFileLocation(/*e*/);

}

/******* Methods shared by Edit Variable and Edit Action Windows **********/

/**
* Utility for making Variable and Action editing Windows
*/
QWidget* LogixTableAction::makeTopPanel(QWidget* /*frame*/, QString title, int /*width*/, int /*height*/) {
//    Container contentPane = frame.getContentPane();
//    contentPane->setLayout(new BoxLayout(contentPane, BoxLayout.X_AXIS));
//    contentPane->layout()->addWidget(Box.createRigidArea(new Dimension(0, height)));
    QGroupBox* topPanel = new QGroupBox(title);
    topPanel->setLayout(new QVBoxLayout(topPanel/*, BoxLayout.Y_AXIS*/));
//    Border panelBorder = BorderFactory.createEtchedBorder();
//    Border panelTitled = BorderFactory.createTitledBorder(panelBorder, tr(title));
//    topPanel.setBorder(panelTitled);
//    topPanel->layout()->addWidget(Box.createRigidArea(new Dimension(width, 0)));
//    topPanel->layout()->addWidget(Box.createVerticalGlue());
    return topPanel;
}

/**
* Utility for making Variable and Action editing Windows
*/
QWidget* LogixTableAction::makeEditPanel(QWidget* comp, QString label, QString hint)
{
    QWidget* panel = new QWidget();
    panel->setObjectName("panel");
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(0);
    panel->setSizePolicy(sizePolicy);
    QVBoxLayout* editPanelVerticalLayout;
    panel->setLayout(editPanelVerticalLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    editPanelVerticalLayout->setObjectName("editPanelVerticalLayout");
    //QWidget* p = new QWidget();

    QLabel* l = new QLabel(label);
    QFont font1;
    font1.setBold(true);
    font1.setWeight(75);
    l->setFont(font1);
    l->setFrameShape(QFrame::NoFrame);
    l->setAlignment(Qt::AlignCenter);
    editPanelVerticalLayout->addWidget(l);
    l->setObjectName("panelWidgetLabel");
    //editPanelVerticalLayout->addWidget(l);
    if (hint != "")
    {
     panel->setToolTip(hint);
    }
    panel->setMinimumSize(comp->size());  // override for  text fields
    editPanelVerticalLayout->addWidget(comp);
    editPanelVerticalLayout->setAlignment(Qt::AlignHCenter);

    //panel->layout()->addWidget(Box.createVerticalGlue());
    return panel;
}

/**
* Utility for making Variable and Action editing Windows
*/
QWidget* LogixTableAction::makeButtonPanel(QPushButton* updateAction,
                       QPushButton*  cancelAction,
                       QPushButton*  deleteAction)
{
    QWidget* panel3 = new QWidget();
    panel3->setLayout(new QHBoxLayout(panel3/*, BoxLayout.X_AXIS*/));
    //QPushButton updateAction = new QPushButton(tr("UpdateButton"));
    updateAction->setText(tr("Update"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(updateAction->sizePolicy().hasHeightForWidth());
    updateAction->setSizePolicy(sizePolicy);
    panel3->layout()->addWidget(updateAction);
    //panel3->layout()->addWidget(Box.createHorizontalStrut(STRUT));
    //updateAction->layout()->addActionListener(updateListener);
    updateAction->setToolTip(tr("Press to keep changes and return to Edit Conditional"));

    //QPushButton cancelAction = new QPushButton(tr("CancelButton"));
    cancelAction->setText(tr("Cancel"));
    cancelAction->setSizePolicy(sizePolicy);
    panel3->layout()->addWidget(cancelAction);
    //panel3->layout()->addWidget(Box.createHorizontalStrut(STRUT));
    //cancelAction->layout()->addActionListener(cancelListener);
    cancelAction->setToolTip(tr("Press to return to Edit Conditional without any changes"));

    //QPushButton deleteAction = new QPushButton(tr("DeleteButton"));
    deleteAction->setText(tr("Delete"));
    deleteAction->setSizePolicy(sizePolicy);
    panel3->layout()->addWidget(deleteAction);
    //deleteAction->layout()->addActionListener(deleteListener);
    deleteAction->setToolTip(tr("Press to delete and return to Edit Conditional "));
    return panel3;
}

/************* Responses for Edit Action and Edit Variable Buttons ***********/
/*
* Responds to Update action button in the Edit Action window
*/
void LogixTableAction::updateActionPressed() {
    if (!validateAction() ) {
//        _editActionFrame->toFront();
        return;
    }
    _actionTableModel->fireTableRowsUpdated(_curActionRowNumber, _curActionRowNumber);
    cleanUpAction();
    if (editConditionalFrame!=NULL) {
        editConditionalFrame->setVisible(true);
    }
}

/*
* Responds to Update action button in the Edit Action window
*/
void LogixTableAction::updateVariablePressed() {
    if (!validateVariable() ) {
//        _editVariableFrame->toFront();
        return;
    }
    _variableTableModel->fireTableRowsUpdated(_curVariableRowNumber, _curVariableRowNumber);
    cleanUpVariable();
    if (editConditionalFrame!=NULL) {
        editConditionalFrame->setVisible(true);
    }
}

/*
* Responds to Cancel action button and window closer of the
* Edit Action window.  Also does cleanup of Update and Delete
* buttons.
*/
void LogixTableAction::cancelEditActionPressed() {
    if (_newItem) {
        deleteActionPressed(_curActionRowNumber);
    } else {
        cleanUpAction();
    }
    if (editConditionalFrame!=NULL) {
        editConditionalFrame->setVisible(true);
    }
}

void LogixTableAction::cleanUpAction()
{
 _newItem = false;
 if (_editActionFrame != NULL)
 {
  //_actionTypeBox->removeActionListener(_actionTypeListener);
  disconnect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(_actionTypeListener(int)));

  _editActionFrame->setVisible(false);
  _editActionFrame->dispose();
  _editActionFrame = NULL;
 }
 _curActionRowNumber = -1;
}
#if 1
/*
* Responds to Cancel action button and window closer of the
* Edit Variable window.  Also does cleanup of Update and Delete
* buttons.
*/
void LogixTableAction::cancelEditVariablePressed()
{
 if (_newItem)
 {
  deleteVariablePressed(_curVariableRowNumber);
 }
 else
 {
  cleanUpVariable();
 }
 if (editConditionalFrame!=NULL)
 {
  editConditionalFrame->setVisible(true);
 }
}
#endif
void LogixTableAction::cleanUpVariable()
{
 _newItem = false;
 if (_editVariableFrame != NULL)
 {
  _editVariableFrame->setVisible(false);
  _editVariableFrame->dispose();
  _editVariableFrame = NULL;
 }
 _curVariableRowNumber = -1;
}

/*
* Responds to Delete action button in the Edit Action window
*/
void LogixTableAction::deleteActionPressed() {
    deleteActionPressed(_curActionRowNumber);
}

/*
* Responds to Delete action button in an action row of the
* Edit Conditional window
*/
void LogixTableAction::deleteActionPressed(int row) {
    if (row != _curActionRowNumber && alreadyEditingActionOrVariable()) {
        return;
    }
    _actionList->removeAt(row);
    _actionTableModel->fireTableRowsDeleted(row, row);
    cleanUpAction();
    if (editConditionalFrame!=NULL) {
        editConditionalFrame->setVisible(true);
    }
    _showReminder = true;
}

/*
* Responds to Delete action button in the Edit Variable window
*/
void LogixTableAction::deleteVariablePressed() {
    deleteVariablePressed(_curVariableRowNumber);
}

/**
 * Responds to the Delete Button in the State Variable Table of the Edit
 * Conditional window
 */
void LogixTableAction::deleteVariablePressed(int row)
{
 if (row != _curVariableRowNumber && alreadyEditingActionOrVariable())
 {
  return;
 }
    if (_variableList->size() < 1 && !_suppressReminder) {
        // warning message - last State Variable deleted
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Warn3"), tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(editConditionalFrame, tr("Warning"), tr("A Conditional must have at least one State Variable to do anything useful."));
    }
    // move remaining state variables if needed
    _variableList->removeAt(row);
    _variableTableModel->fireTableRowsDeleted(row, row);
    makeAntecedent();
    cleanUpVariable();
    if (editConditionalFrame!=NULL) {
        editConditionalFrame->setVisible(true);
    }
    _showReminder = true;
}
#if 1
/**
* set display to show current state variable (curVariable) parameters
*/
void LogixTableAction::initializeStateVariables()
{
 int testType = (_curVariable)->getType();
 if (log->isDebugEnabled()) log->debug("initializeStateVariables: testType= "+QString::number(testType));
 if (testType==Conditional::TYPE_NONE)
 {
  return;
 }
 int itemType = Conditional::TEST_TO_ITEM.at(testType);
 if (log->isDebugEnabled()) log->debug("initializeStateVariables: itemType= "+QString::number(itemType)+", testType= "+QString::number(testType));
 // set type after call to variableTypeChanged - addItemListener action will call variableTypeChanged
 _variableTypeBox->setCurrentIndex(itemType);
 //variableTypeChanged(itemType);
 switch (itemType)
 {
  case Conditional::ITEM_TYPE_SENSOR:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_SENSOR_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  case Conditional::ITEM_TYPE_TURNOUT:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_TURNOUT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
 case Conditional::ITEM_TYPE_LIGHT:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_LIGHT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
  break;
 case Conditional::ITEM_TYPE_SIGNALHEAD:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                   Conditional::ITEM_TO_SIGNAL_HEAD_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   if ((Conditional::TYPE_SIGNAL_HEAD_RED<=testType && testType<=Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN)
            || Conditional::TYPE_SIGNAL_HEAD_LUNAR==testType
            || Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR==testType)
   {
    _variableStateBox->setCurrentIndex(_variableStateBox->findText( // index 1 = TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS
                                                                        ConditionalVariable::getStateString(Conditional::ITEM_TO_SIGNAL_HEAD_TEST.at(1))));
        loadJComboBoxWithSignalAspects(_variableSignalBox, _curVariable->getName());
        _variableSignalBox->setCurrentIndex(_variableSignalBox->findText(
                    ConditionalVariable::getStateString(_curVariable->getType())));
        _variableSignalPanel->setVisible(true);
   }
   break;
  case Conditional::ITEM_TYPE_SIGNALMAST:
   // set display to show current state variable (curVariable) parameters
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_SIGNAL_MAST_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   if (testType==Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS)
   {
    loadJComboBoxWithMastAspects(_variableSignalBox, _curVariable->getName());
    _variableSignalBox->setCurrentIndex(_variableSignalBox->findText(_curVariable->getDataString()));
    _variableSignalPanel->setVisible(true);
   }
   break;
  case Conditional::ITEM_TYPE_MEMORY:
  {
   _variableCompareTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_MEMORY_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   int num1 = _curVariable->getNum1()-1;
   if (num1==-1)
   {  // former code was only equals
    num1 = ConditionalVariable::EQUAL-1;
   }
   _variableCompareOpBox->setCurrentIndex(num1);
   _variableData1Field->setText(_curVariable->getDataString());
   break;
  }
  case Conditional::ITEM_TYPE_CONDITIONAL:
  {
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_CONDITIONAL_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  }
  case Conditional::ITEM_TYPE_WARRANT:
  {
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_WARRANT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  }
  case Conditional::ITEM_TYPE_CLOCK:
  {
   int time = _curVariable->getNum1();
   _variableData1Field->setText(formatTime(time / 60, time - ((time / 60) * 60)));
   time = _curVariable->getNum2();
   _variableData2Field->setText(formatTime(time / 60, time - ((time / 60) * 60)));
   _variableNameField->setText("");
   break;
  }

  case Conditional::ITEM_TYPE_OBLOCK:
  {
   _variableNameField->setText(_curVariable->getName());
   _variableStateBox->clear();
   QStringListIterator names = OBlock::getLocalStatusNames();
   while (names.hasNext())
   {
    _variableStateBox->addItem(names.next());
   }
   _variableStateBox->setCurrentIndex(_variableStateBox->findText(OBlock::getLocalStatusName(_curVariable->getDataString())));
   _variableStateBox->setVisible(true);
   break;
  }
#if 0
  case Conditional::ITEM_TYPE_ENTRYEXIT:
  {
   _variableNameField->setText(_curVariable->getBean().getUserName());
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_ENTRYEXIT_TEST, testType));
   _variableStateBox->setVisible(true);
   break;
  }
#endif
  default : break;
 }
 _editVariableFrame->adjustSize();
 //_editVariableFrame->transferFocusBackward();
}       /* initializeStateVariables */
#endif
#if 1
/*
String getConditionalUserName(String name) {
    Conditional c = _conditionalManager.getBySystemName(name);
    if (c != NULL) {
        return c.getUserName();
    }
    return name;
}

/**
* set display to show current action (curAction) parameters
*/
void LogixTableAction::initializeActionVariables() {
    int actionType = ((ConditionalAction*)_curAction)->getType();
    int itemType = Conditional::ACTION_TO_ITEM[actionType];
    if (log->isDebugEnabled()) log->debug("initializeActionVariables: itemType= "+QString::number(itemType)+", actionType= "+QString::number(actionType));
    if (actionType==Conditional::ACTION_NONE) {
        return;
    }
    _actionItemTypeBox->setCurrentIndex(itemType);
    _actionNameField->setText(((ConditionalAction*)_curAction)->getDeviceName());
    switch (itemType)
    {
        case Conditional::ITEM_TYPE_SENSOR:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SENSOR_ACTION, actionType)+1);
            if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                            (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
                _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            }
            if (actionType==Conditional::ACTION_SET_SENSOR ||
                    actionType==Conditional::ACTION_DELAYED_SENSOR ||
                    actionType==Conditional::ACTION_RESET_DELAYED_SENSOR ) {
                if (((ConditionalAction*)_curAction)->getActionData() == Sensor::ACTIVE) {
                    _actionBox->setCurrentIndex(0);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Sensor::INACTIVE) {
                    _actionBox->setCurrentIndex(1);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            }
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_TURNOUT_ACTION, actionType)+1);
            if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT) ) {
                _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            }
            if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                            (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT) ) {
                if (((ConditionalAction*)_curAction)->getActionData() == Turnout::CLOSED) {
                    _actionBox->setCurrentIndex(0);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Turnout::THROWN) {
                    _actionBox->setCurrentIndex(1);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if (actionType==Conditional::ACTION_LOCK_TURNOUT) {
                if (((ConditionalAction*)_curAction)->getActionData() == Turnout::UNLOCKED) {
                    _actionBox->setCurrentIndex(0);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Turnout::LOCKED) {
                    _actionBox->setCurrentIndex(1);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            }
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_LIGHT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_LIGHT) {
                if (((ConditionalAction*)_curAction)->getActionData() == Light::ON) {
                    _actionBox->setCurrentIndex(0);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Light::OFF) {
                    _actionBox->setCurrentIndex(1);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if ((actionType==Conditional::ACTION_SET_LIGHT_INTENSITY) ||
                       (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)) {
                _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            /*
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_HEAD_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                _actionBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            AbstractSignalHead.getDefaultValidStates(), ((ConditionalAction*)_curAction)->getActionData()));
            }
            */
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_HEAD_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                loadJComboBoxWithSignalAspects(_actionBox, _actionNameField->text().trimmed());
            }
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_MAST_ACTION, actionType)+1);
           break;
        case Conditional::ITEM_TYPE_CLOCK:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_CLOCK_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                int time = ((ConditionalAction*)_curAction)->getActionData();
                _shortActionString->setText(formatTime(time / 60, time - ((time / 60) * 60)));
                _actionNameField->setText("");
            }
            break;
        case Conditional::ITEM_TYPE_MEMORY:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_MEMORY_ACTION, actionType)+1);
            _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            break;
        case Conditional::ITEM_TYPE_LOGIX:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_LOGIX_ACTION, actionType)+1);
            break;
#if 0
        case Conditional::ITEM_TYPE_WARRANT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_WARRANT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
                if (((ConditionalAction*)_curAction)->getActionData() == Warrant.HALT) {
                    _actionBox->setCurrentIndex(0);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Warrant.RESUME) {
                    _actionBox->setCurrentIndex(1);
                } else if (((ConditionalAction*)_curAction)->getActionData() == Warrant.ABORT) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                            actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                            actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_OBLOCK_ACTION, actionType)+1);
            break;
        case Conditional::ITEM_TYPE_AUDIO:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_AUDIO_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_PLAY_SOUND) {
                _longActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            } else if (actionType==Conditional::ACTION_CONTROL_AUDIO) {
                switch (((ConditionalAction*)_curAction)->getActionData()) {
                    case Audio.CMD_PLAY:
                        _actionBox->setCurrentIndex(0);
                        break;
                    case Audio.CMD_STOP:
                        _actionBox->setCurrentIndex(1);
                        break;
                    case Audio.CMD_PLAY_TOGGLE:
                        _actionBox->setCurrentIndex(2);
                        break;
                    case Audio.CMD_PAUSE:
                        _actionBox->setCurrentIndex(3);
                        break;
                    case Audio.CMD_RESUME:
                        _actionBox->setCurrentIndex(4);
                        break;
                    case Audio.CMD_PAUSE_TOGGLE:
                        _actionBox->setCurrentIndex(5);
                        break;
                    case Audio.CMD_REWIND:
                        _actionBox->setCurrentIndex(6);
                        break;
                    case Audio.CMD_FADE_IN:
                        _actionBox->setCurrentIndex(7);
                        break;
                    case Audio.CMD_FADE_OUT:
                        _actionBox->setCurrentIndex(8);
                        break;
                    case Audio.CMD_RESET_POSITION:
                        _actionBox->setCurrentIndex(9);
                        break;
                }
            }
            break;
#endif
        case Conditional::ITEM_TYPE_SCRIPT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SCRIPT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_RUN_SCRIPT) {
                _longActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
                _shortActionString->setText(((ConditionalAction*)_curAction)->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_OTHER:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_OTHER_ACTION, actionType)+1);
            // ACTION_TRIGGER_ROUTE
            break;
    }
    _actionOptionBox->setCurrentIndex(((ConditionalAction*)_curAction)->getOption() - 1);
    _editActionFrame->adjustSize();
   // _editActionFrame->transferFocusBackward();
}   /* initializeActionVariables */

#if 0
JFileChooser sndFileChooser = NULL;
JFileChooser scriptFileChooser = NULL;
JFileChooser defaultFileChooser = NULL;
#endif

/**
 * Responds to the Set button in the Edit Action window action section.
 */
void LogixTableAction::setFileLocation(ActionEvent* /*e*/) {
#if 0
    ConditionalAction action = _actionList.get(_curActionRowNumber);
    JFileChooser currentChooser;
    int actionType = action.getType();
    if (actionType == Conditional::ACTION_PLAY_SOUND) {
        if (sndFileChooser == NULL) {
            sndFileChooser = new JFileChooser(System.getProperty("user.dir")+
                                              java.io.File.separator+"resources"+
                                              java.io.File.separator+"sounds");
            jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("wav sound files");
            filt->layout()->addWidgetExtension("wav");
            sndFileChooser.setFileFilter(filt);
        }
        currentChooser = sndFileChooser;
    } else if (actionType == Conditional::ACTION_RUN_SCRIPT) {
        if (scriptFileChooser == NULL) {
            scriptFileChooser = new JFileChooser(System.getProperty("user.dir")+
                                                 java.io.File.separator+"jython");
            jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Python script files");
            filt->layout()->addWidgetExtension("py");
            scriptFileChooser.setFileFilter(filt);
        }
        currentChooser = scriptFileChooser;
    } else {
        log->warn("Unexpected actionType["+actionType+"] = "+DefaultConditionalAction::getActionTypeString(actionType));
        if (defaultFileChooser == NULL) {
            defaultFileChooser = new JFileChooser(FileUtil.getUserFilesPath());
            defaultFileChooser.setFileFilter(new jmri.util.NoArchiveFileFilter());
        }
        currentChooser = defaultFileChooser;
    }

    currentChooser.rescanCurrentDirectory();
    int retVal = currentChooser.showOpenDialog(NULL);
    // handle selection or cancel
    if (retVal == JFileChooser.APPROVE_OPTION) {
    // set selected file location in data string
        try {
            _longActionString->setText(currentChooser.getSelectedFile().getCanonicalPath());
        } catch (java.io.IOException ex) {
            if (log->isDebugEnabled()) log->error("exception setting file location: " + ex);
            _longActionString->setText("");
        }
    }
#endif
}

/**
 * Responds to a change in an Action Type Box of Edit Action Window
 * Set components visible for the selected type
 */
void LogixTableAction::actionItemChanged(int type)
{
 int actionType = ((DefaultConditionalAction*)_curAction)->getType();
 if (log->isDebugEnabled()) log->debug("actionItemChanged: itemType= "+QString::number(type)+", actionType= "+QString::number(actionType));
 //_actionTypeBox->removeActionListener(_actionTypeListener);
 disconnect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(_actionTypeListener(int)));

 _actionTypePanel->setVisible(false);
 _setPanel->setVisible(false);
 _shortTextPanel->setVisible(false);
 _shortActionString->setText("");
 _textPanel->setVisible(false);
 _longActionString->setText("");
 _namePanel->setVisible(false);
 _actionPanel->setVisible(false);
 _optionPanel->setVisible(false);
 int itemType = Conditional::ACTION_TO_ITEM.at(actionType);
 if (type==Conditional::TYPE_NONE && itemType==Conditional::TYPE_NONE) {
    return;
 }
 _actionTypePanel->setVisible(true);
 _actionTypeBox->clear();
 _actionBox->clear();
 if (type!=Conditional::TYPE_NONE) {  // actionItem listener choice overrides current item
    itemType = type;
 }
 if (itemType!=Conditional::ACTION_TO_ITEM.at(actionType)) {
    actionType = Conditional::ACTION_NONE;    // chosen item type does not support action type
 }
 if (actionType != Conditional::ACTION_NONE) {
    _optionPanel->setVisible(true);    // item type compatible with action type
 }
 _actionTypeBox->addItem("");
//    _actionNameField.removeActionListener(actionSignalHeadNameListener);
//    _actionNameField.removeActionListener(actionSignalMastNameListener);
//    _actionNameField.removeActionListener(actionOBlockPathListener);

 switch (itemType)
 {
  case Conditional::ITEM_TYPE_TURNOUT:
  {
   for(int i=0; i<Conditional::ITEM_TO_TURNOUT_ACTION.length(); i++)
   {
    _actionTypeBox->addItem(
            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_TURNOUT_ACTION.at(i)));
   }
   if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                    (actionType==Conditional::ACTION_DELAYED_TURNOUT))
   {
    //QWidget* p = (JPanel)_shortTextPanel.getComponent(0);
    QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
    //QLabel* l = (JLabel)p.getComponent(0);
    QLabel* l = (QLabel*)p->children().at(1);
    l->setText(tr("Delay Time"));
    _shortTextPanel->setToolTip(tr("Enter time (seconds) to wait before setting turnout"));
    _shortTextPanel->setVisible(true);
   }
   QWidget* panel = (QWidget*)_actionPanel->children().at(1);
   QLabel* label = (QLabel*)panel->children().at(1);
   if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                    (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT)  ||
                    (actionType==Conditional::ACTION_DELAYED_TURNOUT))
   {
    label->setText(tr("Turnout Position"));
    _actionBox->addItem(tr("Closed"));
    _actionBox->addItem(tr("Thrown"));
    _actionBox->addItem( tr("Toggle"));
    _actionPanel->setToolTip(tr("Select Closed or Thrown depending upon how Turnout is to be set"));
    _actionPanel->setVisible(true);
   }
   else if (actionType==Conditional::ACTION_LOCK_TURNOUT)
   {
    label->setText(tr("Lock State"));
    _actionBox->addItem(tr("Unlock"));
    _actionBox->addItem(tr("Lock"));
    _actionBox->addItem( tr("Toggle"));
    _actionPanel->setToolTip(tr("Select Lock or Unlock"));
    _actionPanel->setVisible(true);
   }
   _namePanel->setToolTip(tr("Enter Name (system or user) for Turnout (e.g. LT12)"));
   _namePanel->setVisible(true);
   break;
   }
   case Conditional::ITEM_TYPE_SENSOR:
   {
    for(int i=0; i<Conditional::ITEM_TO_SENSOR_ACTION.length(); i++)
    {
     _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SENSOR_ACTION.at(i)));
    }
    if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                    (actionType==Conditional::ACTION_DELAYED_SENSOR))
    {
     QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     l->setText(tr("Delay Time"));
     _shortTextPanel->setToolTip(tr("Enter time (seconds) to wait before setting turnout"));
     _shortTextPanel->setVisible(true);
    }
    if ((actionType==Conditional::ACTION_SET_SENSOR) ||
                (actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                (actionType==Conditional::ACTION_DELAYED_SENSOR) )
    {
     QWidget* p = (QWidget*)_actionPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     l->setText(tr("Sensor State"));
     _actionBox->addItem(tr("Active"));
     _actionBox->addItem(tr("Inactive"));
     _actionBox->addItem( tr("Toggle"));
     _actionPanel->setToolTip(tr("Select Active or Inactive depending upon how Sensor is to be set"));
     _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Sensor (e.g. CS2)"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_SIGNALHEAD:
    {
     //_actionNameField->layout()->addActionListener(actionSignalHeadNameListener);
     connect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalHeadNameListener()));

     for(int i=0; i<Conditional::ITEM_TO_SIGNAL_HEAD_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_HEAD_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("LabelActionSignal"));

      loadJComboBoxWithSignalAspects(_actionBox,_actionNameField->text().trimmed());

      _actionPanel->setToolTip(tr("Select Signal Head Appearance to set"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Signal Head (e.g. IH34)"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_SIGNALMAST:
    {
     //_actionNameField->layout()->addActionListener(actionSignalMastNameListener);
     connect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalHeadNameListener()));

     for(int i=0; i<Conditional::ITEM_TO_SIGNAL_MAST_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(
        DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_MAST_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_SIGNALMAST_ASPECT)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("LabelSignalAspect"));

      loadJComboBoxWithMastAspects(_actionBox,_actionNameField->text().trimmed());

      _actionPanel->setToolTip(tr("Select Signal Mast Aspect to set and hit Enter/Return to load aspects"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Signal Mast and hit Enter/Return to load aspects"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_LIGHT:
    {
     for(int i=0; i<Conditional::ITEM_TO_LIGHT_ACTION.length(); i++)
     {
     _actionTypeBox->addItem(
            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LIGHT_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_LIGHT_INTENSITY)
     {
      QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("LabelLightIntensity"));
     _shortTextPanel->setToolTip(tr("Enter intensity percentage as an integer 0 to 100."));
       _shortTextPanel->setVisible(true);
     }
     else if (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)
     {
      QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Transition Time"));
      _shortTextPanel->setToolTip(tr("Enter number of fast clock minutes to transition between 0% and 100%."));
      _shortTextPanel->setVisible(true);
     }
     else if (actionType==Conditional::ACTION_SET_LIGHT)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Light State"));
      _actionBox->addItem(tr("On"));
      _actionBox->addItem(tr("Off"));
      _actionBox->addItem( tr("Toggle"));
      _actionPanel->setToolTip(tr("Select On or Off depending upon how Light is to be set"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("NameHintLight"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_MEMORY:
    {
     for(int i=0; i<Conditional::ITEM_TO_MEMORY_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_MEMORY_ACTION.at(i)));
     }
     QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     if (actionType==Conditional::ACTION_COPY_MEMORY)
     {
      _shortTextPanel->setToolTip(tr("Enter name (system or user) of Memory to receive the copied value"));
      l->setText(tr("Memory Name"));
     }
     else
     {
      _shortTextPanel->setToolTip(tr("Enter name (system or user) of Memory to receive the copied value"));
      l->setText(tr("Value"));
     }
     _shortTextPanel->setVisible(true);
     _namePanel->setToolTip(tr("Enter name (system or user) of Memory"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_CLOCK:
    {
        for(int i=0; i<Conditional::ITEM_TO_CLOCK_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_CLOCK_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                QWidget* p = (QWidget*)_textPanel->children().at(1);
                QLabel* l = (QLabel*)p->children().at(1);
                l->setText(tr("Set Time"));
                _textPanel->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));
                _textPanel->setVisible(true);
            }
            break;
    }
        case Conditional::ITEM_TYPE_LOGIX:
    {
        for(int i=0; i<Conditional::ITEM_TO_LOGIX_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LOGIX_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("Enter name (system or user) of Logix"));
            _namePanel->setVisible(true);
            break;
    }
#if 0
        case Conditional::ITEM_TYPE_WARRANT:
            for(int i=0; i<Conditional::ITEM_TO_WARRANT_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_WARRANT_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("NameHintWarrant"));
            _namePanel->setVisible(true);
            if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
                p = (JPanel)_actionPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                _actionBox->layout()->addWidget(new QLabel("WarrantHalt"));
                _actionBox->layout()->addWidget(new QLabel("WarrantResume"));
                _actionBox->layout()->addWidget(new QLabel("WarrantAbort"));
                l->setText(tr("LabelControlTrain"));
               _actionPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                            actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                            actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                p = (JPanel)_shortTextPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                if (actionType==Conditional::ACTION_SET_TRAIN_ID) {
                    _shortTextPanel->setToolTip(tr("DataHintTrainId"));
                    l->setText(tr("LabelTrainId"));
                } else if (actionType==Conditional::ACTION_SET_TRAIN_NAME) {
                    _shortTextPanel->setToolTip(tr("DataHintTrainName"));
                    l->setText(tr("LabelTrainName"));
                } else if (actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                    _shortTextPanel->setToolTip(tr("DataHintThrottleFactor"));
                    l->setText(tr("LabelThrottleFactor"));
                }
                _shortTextPanel->setVisible(true);
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            _actionNameField->layout()->addActionListener(actionOBlockPathListener);

            for(int i=0; i<Conditional::ITEM_TO_OBLOCK_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OBLOCK_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("NameHintOBlock"));
            _namePanel->setVisible(true);
/*
            if (actionType==Conditional::ACTION_ALLOCATE_BLOCK_PATH ||
                    actionType==Conditional::ACTION_SET_BLOCK_PATH_TURNOUTS) {
                p = (JPanel)_actionPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("LabelBlockPaths"));

                loadJComboBoxWithBlockPaths(_actionBox,_actionNameField->text().trimmed());

                _actionPanel->setToolTip(tr("BlockPathsSetHint"));
                _actionPanel->setVisible(true);
            } else {
            }
*/
            break;
        case Conditional::ITEM_TYPE_AUDIO:
            for(int i=0; i<Conditional::ITEM_TO_AUDIO_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_AUDIO_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_PLAY_SOUND) {
                p = (JPanel)_textPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("LabelSetFile"));
                _textPanel->setToolTip(tr("SetHintSound"));
                _textPanel->setVisible(true);
                _setPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_CONTROL_AUDIO) {
                p = (JPanel)_actionPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("LabelActionAudio"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePlay"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceStop"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePlayToggle"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePause"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceResume"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePauseToggle"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceRewind"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceFadeIn"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceFadeOut"));
                _actionBox->layout()->addWidget(new QLabel("AudioResetPosition"));
                _actionPanel->setToolTip(tr("SetHintAudio"));
                _actionPanel->setVisible(true);
                _namePanel->setToolTip(tr("NameHintAudio"));
                _namePanel->setVisible(true);
            }
            break;
        case Conditional::ITEM_TYPE_SCRIPT:
            for(int i=0; i<Conditional::ITEM_TO_SCRIPT_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SCRIPT_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_RUN_SCRIPT) {
                p = (JPanel)_textPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("LabelSetFile"));
                _textPanel->setToolTip(tr("SetHintScript"));
                _textPanel->setVisible(true);
                _setPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
                p = (JPanel)_shortTextPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("LabelScriptCommand"));
                _shortTextPanel->setToolTip(tr("SetHintJythonCmd"));
                _shortTextPanel->setVisible(true);
            }
            break;
#endif
        case Conditional::ITEM_TYPE_OTHER:
    {
            for(int i=0; i<Conditional::ITEM_TO_OTHER_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OTHER_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_TRIGGER_ROUTE) {
                _namePanel->setToolTip(tr("Enter name (system or user) of Route"));
                _namePanel->setVisible(true);
            }
            break;
    }
        default :
    {
        break;
    }
    }
    _actionTypeBox->setMaximumSize(_actionTypeBox->size());
    _actionBox->setMaximumSize(_actionBox->size());
    //_actionTypeListener->setItemType(itemType);
    this->itemType = itemType;
    //_actionTypeBox->addActionListener(_actionTypeListener);
    connect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(_actionTypeListener(int)));
    if (log->isDebugEnabled()) log->debug("Exit actionItemChanged size: "+QString::number(_editActionFrame->width())+
                                        " X "+QString::number(_editActionFrame->height()));
} /* actionItemChanged */
#endif
/*private*/ void LogixTableAction::compareTypeChanged(int selection)
{
 QObjectList ol = _variableData1Panel->children();
 QWidget* p = (QWidget*)ol.at(1);
 QLabel* l = (QLabel*)p->children().at(1);
 int testType = Conditional::ITEM_TO_MEMORY_TEST.at(selection);
 if ((testType==Conditional::TYPE_MEMORY_COMPARE) ||
                (testType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE))
 {
  l->setText(tr("Memory Value"));
  _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
 }
 else
 {
  l->setText(tr("Literal Value"));
  _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
 }
}
#if 1
/*public*/ void LogixTableAction::variableSignalTestStateListener(ActionEvent* /*e*/) {
    log->debug("variableSignalTestStateListener fires; _variableTypeBox->currentIndex()= "+
              QString::number(_variableTypeBox->currentIndex())+
              "\" _variableStateBox->currentIndex()= \""+QString::number(_variableStateBox->currentIndex())+"\"");

    int itemType = _variableTypeBox->currentIndex();
    if (itemType==Conditional::ITEM_TYPE_SIGNALHEAD || itemType==Conditional::ITEM_TYPE_SIGNALMAST) {
        // index 1 is Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS or Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS
        if (_variableStateBox->currentIndex()==1) {
            loadJComboBoxWithMastAspects(_variableSignalBox,_variableNameField->text().trimmed());
            _variableSignalPanel->setVisible(true);
        } else {
            _variableSignalPanel->setVisible(false);
        }
    } else {
        _variableSignalPanel->setVisible(false);
    }
    _variableSignalBox->setMaximumSize(_variableSignalBox->size());
    if (_editVariableFrame!=NULL)
    {
        _editVariableFrame->adjustSize();
    }
}


/*public*/ void LogixTableAction::variableSignalHeadNameListener(ActionEvent* /*e*/) {
        // fired when signal mast name changes, but only
        // while in signal mast mode
        log->debug("variableSignalHeadNameListener fires; _variableNameField : "+_variableNameField->text().trimmed());
        loadJComboBoxWithSignalAspects(_variableSignalBox,_variableNameField->text().trimmed());
    }
//};

/*public*/ void LogixTableAction::actionSignalHeadNameListener(ActionEvent* /*e*/) {
    // fired when signal mast name changes, but only
    // while in signal mast mode
    log->debug("actionSignalHeadNameListener fires; _actionNameField : "+_actionNameField->text().trimmed());
    loadJComboBoxWithSignalAspects(_actionBox,_actionNameField->text().trimmed());
}
#endif
void LogixTableAction::loadJComboBoxWithSignalAspects(QComboBox* box, QString signalName)
{
 box->clear();
 log->debug("loadJComboBoxWithSignalAspects called with name: "+signalName);
 SignalHead* h = ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getSignalHead(signalName);
 if (h == NULL)
 {
  box->addItem(tr("(Type signal name and hit Enter)"));
 }
 else
 {
  QVector<QString> v = ((AbstractSignalHead*)h)->getValidStateNames();
  for (int i = 0; i<v.size(); i++)
  {
   box->addItem(v.at(i));
  }
  box->setCurrentIndex(box->findText(((AbstractSignalHead*)h)->getAppearanceName()));
 }
}
#if 1
//transient ActionListener variableSignalMastNameListener = new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
void LogixTableAction::variableSignalMastNameListener() // SLOT[]
{
 // fired when signal mast name changes, but only
 // while in signal mast mode
 log->debug("variableSignalMastNameListener fires; _variableNameField : "+_variableNameField->text().trimmed());
 loadJComboBoxWithMastAspects(_variableSignalBox,_variableNameField->text().trimmed());
}
//};

//transient ActionListener actionSignalMastNameListener = new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
void LogixTableAction::actionSignalMastNameListener() // SLOT[]
{
 // fired when signal mast name changes, but only
 // while in signal mast mode
 log->debug("actionSignalMastNameListener fires; _actionNameField : "+_actionNameField->text().trimmed());
 loadJComboBoxWithMastAspects(_actionBox,_actionNameField->text().trimmed());
}
//};
#endif
void LogixTableAction::loadJComboBoxWithMastAspects(QComboBox* box, QString mastName)
{
 box->clear();
 log->debug("loadJComboBoxWithMastAspects called with name: "+mastName);
 SignalMast* m = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(mastName);
 if (m == NULL)
 {
  box->layout()->addWidget(new QLabel("(Type mast name and hit Enter)"));
 }
 else
 {
  QVector<QString> v = ((AbstractSignalMast*)m)->getValidAspects();
  for (int i = 0; i<v.size(); i++)
  {
   box->addItem(v.at(i));
  }
 box->setCurrentIndex(box->findText(((AbstractSignalMast*)m)->getAspect()));
 }
}
#if 0
transient ActionListener actionOBlockPathListener = new ActionListener() {
    /*public*/ void actionPerformed(ActionEvent e) {
        // fired when oblock name changes
        log->debug("actionOBlockPathListener fires; _actionNameField : "+_actionNameField->text().trimmed());
        loadJComboBoxWithBlockPaths(_actionBox,_actionNameField->text().trimmed());
    }
};

void loadJComboBoxWithBlockPaths(JComboBox box, String blockName) {
    box.removeAllItems();
    log->debug("loadJComboBoxWithBlockPaths called with name: "+blockName);
    OBlock b = InstanceManager::oBlockManagerInstance().getOBlock(blockName);
    if (b == NULL) {
        box->layout()->addWidget(new QLabel("PromptLoadOBlockName"));
    } else {
        List<Path> l = b.getPaths();
        for (int i = 0; i<l.size(); i++) {
            box->addItem(((OPath)l.get(i)).getName());
        }
        box.setSelectedItem(b.getAllocatedPathName());
    }
}
#endif
/**
 * Responds to change in variable type in State Variable Table in the Edit
 * Conditional window Also used to set up for Edit of a Conditional with
 * state variables.
 */
/*private*/ void LogixTableAction::variableTypeChanged(int itemType)
{
 int testType = _curVariable->getType();
 if (log->isDebugEnabled()) log->debug("variableTypeChanged: itemType= "+QString::number(itemType)+", testType= "+QString::number(testType));
 _variableNamePanel->setVisible(false);
 _variableStatePanel->setVisible(false);
 _variableComparePanel->setVisible(false);
 _variableSignalPanel->setVisible(false);
 _variableData1Panel->setVisible(false);
 _variableData2Panel->setVisible(false);
 _variableStateBox->clear();
// _variableNameField->removeActionListener(variableSignalHeadNameListener);
// _variableNameField->removeActionListener(variableSignalMastNameListener);
 disconnect(_variableNameField, SIGNAL(editingFinished()), this, SLOT(variableSignalMastNameListener()));

// _variableStateBox->removeActionListener(variableSignalTestStateListener);
 disconnect(_variableStateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(variableSignalTestStateListener()));
 switch (itemType)
 {
  case Conditional::TYPE_NONE:
   return;
  case Conditional::ITEM_TYPE_SENSOR:
   _variableNamePanel->setToolTip(tr("Enter Name (system or user) for Sensor (e.g. CS2)"));
   for (int i=0; i<Conditional::ITEM_TO_SENSOR_TEST.length(); i++)
   {
    _variableStateBox->addItem(
    ConditionalVariable::getStateString(Conditional::ITEM_TO_SENSOR_TEST.at(i)));
   }
   _variableStatePanel->setVisible(true);
   _variableNamePanel->setVisible(true);
   break;
  case Conditional::ITEM_TYPE_TURNOUT:
   _variableNamePanel->setToolTip(tr("Enter Name (system or user) for Turnout (e.g. LT12)"));
   for (int i=0; i<Conditional::ITEM_TO_LIGHT_TEST.length(); i++)
   {
    _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_TURNOUT_TEST.at(i)));
   }
    _variableNamePanel->setVisible(true);
    _variableStatePanel->setVisible(true);
    break;
  case Conditional::ITEM_TYPE_LIGHT:
   _variableNamePanel->setToolTip(tr("Enter Name (system or user) for Light (e.g. CL21)"));
   for (int i=0; i<Conditional::ITEM_TO_LIGHT_TEST.length(); i++)
   {
    _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_LIGHT_TEST.at(i)));
   }
   _variableStatePanel->setVisible(true);
   _variableNamePanel->setVisible(true);
   break;
  case Conditional::ITEM_TYPE_SIGNALHEAD:
//   _variableNameField->layout()->addActionListener(variableSignalHeadNameListener);
//   _variableStateBox->layout()->addActionListener(variableSignalTestStateListener);
   loadJComboBoxWithSignalAspects(_variableSignalBox,_variableNameField->text().trimmed());

   for (int i=0; i<Conditional::ITEM_TO_SIGNAL_HEAD_TEST.length(); i++)
   {
    _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_SIGNAL_HEAD_TEST.at(i)));
   }
   _variableNamePanel->setToolTip(tr("Enter Name (system or user) for Signal Head (e.g. IH34)"));
   _variableNamePanel->setVisible(true);
   _variableStatePanel->setVisible(true);
   if (testType==Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS)
   {
    _variableSignalPanel->setVisible(true);
   }
   else
   {
    _variableSignalPanel->setVisible(false);
   }
   break;
  case Conditional::ITEM_TYPE_SIGNALMAST:
//   _variableNameField->layout()->addActionListener(variableSignalMastNameListener);
     connect(_variableNameField, SIGNAL(editingFinished()), this, SLOT(variableSignalMastNameListener()));
//   _variableStateBox->layout()->addActionListener(variableSignalTestStateListener);
     connect(_variableStateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(variableSignalTestStateListener()));
   loadJComboBoxWithMastAspects(_variableSignalBox,_variableNameField->text().trimmed());

   for (int i=0; i<Conditional::ITEM_TO_SIGNAL_MAST_TEST.length(); i++)
   {
    _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_SIGNAL_MAST_TEST.at(i)));
   }
   _variableNamePanel->setToolTip(tr("Enter Name (system or user) for Signal Mast and hit Enter/Return to load aspects"));
   _variableNamePanel->setVisible(true);
   _variableStatePanel->setVisible(true);
   if (testType==Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS)
   {
    _variableSignalPanel->setVisible(true);
   }
   else
   {
    _variableSignalPanel->setVisible(false);
   }
   break;
  case Conditional::ITEM_TYPE_MEMORY:
  {
   QWidget* p = (QWidget*)_variableData1Panel->children().at(1);
   QLabel* l = (QLabel*)p->children().at(1);
   if ((testType==Conditional::TYPE_MEMORY_COMPARE) ||
                    (testType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE))
   {
    l->setText(tr("Memory Value"));
        _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
   }
   else
   {
    l->setText(tr("Literal Value"));
    _variableData1Panel->setToolTip(tr("Enter Value is to be compared"));
   }
   _variableNamePanel->setToolTip(tr("Enter name (system or user) of Memory"));
   _variableNamePanel->setVisible(true);
   _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
   _variableData1Panel->setVisible(true);
   _variableComparePanel->setVisible(true);
   break;
  }
  case Conditional::ITEM_TYPE_CONDITIONAL:
  {
   _variableNamePanel->setToolTip(tr("NameHintConditional"));
   for (int i=0; i<Conditional::ITEM_TO_CONDITIONAL_TEST.length(); i++)
   {
    _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_CONDITIONAL_TEST.at(i)));
   }
   _variableNamePanel->setVisible(true);
   _variableStatePanel->setVisible(true);
   break;
  }
  case Conditional::ITEM_TYPE_WARRANT:
  {
   _variableNamePanel->setToolTip(tr("Enter name (system or user) of Warrant"));
   for (int i=0; i<Conditional::ITEM_TO_WARRANT_TEST.length(); i++) {
        _variableStateBox->addItem(
            ConditionalVariable::getStateString(Conditional::ITEM_TO_WARRANT_TEST.at(i)));
   }
   _variableNamePanel->setVisible(true);
   _variableStatePanel->setVisible(true);
   break;
  }
  case Conditional::ITEM_TYPE_CLOCK:
  {
   QWidget*p = (QWidget*)_variableData1Panel->children().at(1);
   QLabel* l = (QLabel*)p->children().at(1);
   l->setText(tr("LabelStartTime"));
   _variableData1Panel->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));
   _variableData1Panel->setVisible(true);
   _variableData2Panel->setVisible(true);
   break;
  }
#if 0
  case Conditional::ITEM_TYPE_OBLOCK:
    _variableNamePanel->setToolTip(tr("Enter name (system or user) of OBlock"));
    _variableNamePanel->setVisible(true);
    _variableStateBox.removeAllItems();
    Enumeration<String> names = OBlock.getLocalStatusNames();
    while (names.hasMoreElements()) {
        _variableStateBox->addItem(names.nextElement());
   }
   _variableStatePanel->setVisible(true);
   break;
  case Conditional::ITEM_TYPE_ENTRYEXIT:
   _variableNameField->setText(_curVariable->getName());
   for (int i=0; i<Conditional::ITEM_TO_ENTRYEXIT_TEST.length(); i++)
   {
    _variableStateBox->addItem(
    ConditionalVariable::getStateString(Conditional::ITEM_TO_ENTRYEXIT_TEST.at(i)));
   }
   variableStatePanel->setVisible(true);
   _variableNamePanel->setVisible(true);
   break;
#endif
  default :
   break;
 }
 _variableStateBox->setMaximumSize(_variableStateBox->size());
} /* variableTypeChanged */


/**
 * Validates Variable data from Edit Variable Window, and transfers it to
 * current action object as appropriate
 * <P>
 * Returns true if all data checks out OK, otherwise false.
 * <P>
 * Messages are sent to the user for any errors found. This routine returns
 * false immediately after finding an error, even if there might be more
 * errors.
 */
bool LogixTableAction::validateVariable() {
    QString name = _variableNameField->text().trimmed();
    _variableNameField->setText(name);
    _curVariable->setDataString("");
    _curVariable->setNum1(0);
    _curVariable->setNum2(0);
    int itemType = _variableTypeBox->currentIndex();
    int testType = 0;
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
            testType = Conditional::ITEM_TO_SENSOR_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            testType = Conditional::ITEM_TO_TURNOUT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            testType = Conditional::ITEM_TO_LIGHT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            testType = Conditional::ITEM_TO_SIGNAL_HEAD_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:
            testType = Conditional::ITEM_TO_SIGNAL_MAST_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_MEMORY:
            testType = Conditional::ITEM_TO_MEMORY_TEST[_variableCompareTypeBox->currentIndex()];
            break;
        case Conditional::ITEM_TYPE_CONDITIONAL:
            testType = Conditional::ITEM_TO_CONDITIONAL_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_WARRANT:
            testType = Conditional::ITEM_TO_WARRANT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_CLOCK:
            testType =Conditional::TYPE_FAST_CLOCK_RANGE;
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            testType =Conditional::TYPE_BLOCK_STATUS_EQUALS;
            break;
        case Conditional::ITEM_TYPE_ENTRYEXIT:
            testType = Conditional::ITEM_TO_ENTRYEXIT_TEST.at(_variableStateBox->currentIndex());
            break;
        default:
//            javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                    tr("ErrorVariableType"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Select a Variable Type or Cancel."));
            return false;
    }
    _curVariable->setType(testType);
    if (log->isDebugEnabled()) log->debug("validateVariable: itemType= "+QString::number(itemType)+", testType= "+QString::number(testType));
    switch ( itemType ) {
        case Conditional::ITEM_TYPE_SENSOR:
            name = validateSensorReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            name = validateTurnoutReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_CONDITIONAL:
            name = validateConditionalReference(name);
            if (name == NULL) {
                return false;
            }
            _curVariable->setName(name);
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            name = validateLightReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_MEMORY:
    {
            name = validateMemoryReference(name);
            if (name == NULL) {
                return false;
            }
            QString name2 = _variableData1Field->text();
            if ((testType==Conditional::TYPE_MEMORY_COMPARE) ||
                    (testType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
                name2 = validateMemoryReference(name2);
                if (name2 == NULL) {
                    return false;
                }
            }
            _curVariable->setDataString(name2);
            _curVariable->setNum1(_variableCompareOpBox->currentIndex() + 1);
            break;
    }
        case Conditional::ITEM_TYPE_CLOCK:
    {
            int beginTime = parseTime(_variableData1Field->text());
            if (beginTime < 0) {
                // parse error occurred - message has been sent
                return (false);
            }
            int endTime = parseTime(_variableData2Field->text());
            if (endTime < 0) {
                return (false);
            }
            // set beginning and end time (minutes since midnight)
            _curVariable->setNum1(beginTime);
            _curVariable->setNum2(endTime);
            name = "Clock";
            break;
    }
        case Conditional::ITEM_TYPE_SIGNALHEAD:
    {
            name = validateSignalHeadReference(name);
            if (name == NULL) {
                return false;
            }
            if (testType==Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS) {
                QString appStr = _variableSignalBox->currentText();
                int type = ConditionalVariable::stringToVariableTest(appStr);
                if (type<0) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            tr("ErrorAppearance"), tr("ErrorTitle"),
//                            javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Select an appearance.  You must hit the Enter/Return key\nafter entering a name with the cursor in the name field."));
                    return false;
                }
                _curVariable->setType(type);
                _curVariable->setDataString(appStr);
                if (log->isDebugEnabled()) log->debug("SignalHead \""+name+"\"of type '"+testType+
                                                    "' _variableSignalBox->currentText()= "+
                                                    _variableSignalBox->currentText());
            }
            break;
    }
        case Conditional::ITEM_TYPE_SIGNALMAST:
    {
            name = validateSignalMastReference(name);
            if (name == NULL) {
                return false;
            }
            if (testType==Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                if (_variableSignalBox->currentIndex()<0) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            tr("ErrorAspect"), tr("ErrorTitle"),
//                            javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Select an aspect.  You may need to hit the Enter/Return key\nwith the cursor in the name field."));
                    return false;
                }
                // save the selected aspect for comparison
                _curVariable->setDataString(_variableSignalBox->currentText());
//                _curVariable->setType(ConditionalVariable::stringToVariableTest(appStr));
            }
            break;
    }
#if 0
        case Conditional::ITEM_TYPE_WARRANT:
            name = validateWarrantReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            name = validateOBlockReference(name);
            if (name == NULL) {
                return false;
            }
            String str = _variableStateBox->currentText();
            _curVariable->setDataString(OBlock.getSystemStatusName(str));
            if (log->isDebugEnabled()) log->debug("OBlock \""+name+"\"of type '"+testType+
                                                "' _variableStateBox->currentText()= "+
                                                _variableStateBox->currentText());
            break;
        case Conditional::ITEM_TYPE_ENTRYEXIT:
            name = validateEntryExitReference(name);
            if (name == NULL) {
                return false;
            }
            break;
#endif
        default:
//            javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                    tr("ErrorVariableType"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Select a Variable Type or Cancel."));
            return false;
    }
    _curVariable->setName(name);
    bool result = _curVariable->evaluate();
    if (log->isDebugEnabled()) log->debug("State Variable \""+name+"\"of type '"+
                                        ConditionalVariable::getTestTypeString(testType)+
                                          "' state= "+ (result?"true":"false")+" type= "+QString::number(_curVariable->getType()));
    if (_curVariable->getType()==Conditional::TYPE_NONE) {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("ErrorVariableState"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Select a state for this variable."));

        return false;
    }
    return (true);
}   /* validateVariable */

/**
 * Validates Action data from Edit Action Window, and transfers it to
 * current action object as appropriate
 * <P>
 * Returns true if all data checks out OK, otherwise false.
 * <P>
 * Messages are sent to the user for any errors found. This routine returns
 * false immediately after finding an error, even if there might be more
 * errors.
 */
bool LogixTableAction::validateAction() {
    int itemType = _actionItemTypeBox->currentIndex();
    int actionType = Conditional::ACTION_NONE;
    int selection = _actionTypeBox->currentIndex();
    if (selection==0)
    {
//        javax.swing.JOptionPane.showMessageDialog(
//           editConditionalFrame, tr("makeSelection"),
//                    tr("WarnTitle"), javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(editConditionalFrame, tr("Warning"), tr("Please select an action type."));
        return false;
    }
    QString name = _actionNameField->text().trimmed();
    QString actionString = _shortActionString->text().trimmed();
    ((ConditionalAction*)_curAction)->setActionString("");
    ((ConditionalAction*)_curAction)->setActionData(-1);
    bool referenceByMemory = false;
    if (name.length() > 0 && name.at(0)== '@') {
        QString memName = name.mid(1);
        if (!_suppressIndirectRef)
        {
//            int response = JOptionPane.showConfirmDialog(_editActionFrame, java.text.MessageFormat.format(
//                                                tr("ConfirmIndirectReference"), memName),
//                                                tr("ConfirmTitle"), JOptionPane.YES_NO_CANCEL_OPTION,
//                                                JOptionPane.QUESTION_MESSAGE);
         int response =QMessageBox::question(_editActionFrame, tr("Question"), tr("Press \"YES\" if at run time Memory location \"%1\" will contain a valid item name for this action.\n                                                                        Press \"NO\" if you want to enter the item name directly.\n                                                                        Press \"CANCEL\" if you want to suppress this warning.\n"),QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            if (response==QMessageBox::No) {
                return false;
            } else if (response==QMessageBox::Cancel) {
                _suppressIndirectRef = true;
            }
        }
        memName = validateMemoryReference(memName);
        if (memName == "") {
            return false;
        }
        referenceByMemory = true;
    }
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
            if (!referenceByMemory){
                name = validateSensorReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_SENSOR_ACTION.at(selection-1);
            if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                            (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
                if (!validateIntegerReference(actionType, actionString))
                {
                    return (false);
                }
                ((ConditionalAction*)_curAction)->setActionString(actionString);
            }
            if ((actionType==Conditional::ACTION_SET_SENSOR) ||
                            (actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                            (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
                if (_actionBox->currentIndex() == 0)
                    ((ConditionalAction*)_curAction)->setActionData(Sensor::ACTIVE);
                else if (_actionBox->currentIndex() == 1)
                    ((ConditionalAction*)_curAction)->setActionData(Sensor::INACTIVE);
                else
                    ((ConditionalAction*)_curAction)->setActionData(Route::TOGGLE);
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            if (!referenceByMemory){
                name = validateTurnoutReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_TURNOUT_ACTION[selection-1];
            if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT)) {
                if (!validateIntegerReference(actionType, actionString))
                {
                    return (false);
                }
                ((ConditionalAction*)_curAction)->setActionString(actionString);
            }
            if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                            (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT)) {
                if (_actionBox->currentIndex() == 0)
                    ((ConditionalAction*)_curAction)->setActionData(Turnout::CLOSED);
                else if (_actionBox->currentIndex() == 1)
                    ((ConditionalAction*)_curAction)->setActionData(Turnout::THROWN);
                else
                    ((ConditionalAction*)_curAction)->setActionData(Route::TOGGLE);
            } else if (actionType==Conditional::ACTION_LOCK_TURNOUT) {
                if (_actionBox->currentIndex() == 0)
                    ((ConditionalAction*)_curAction)->setActionData(Turnout::UNLOCKED);
                else if (_actionBox->currentIndex() == 1)
                    ((ConditionalAction*)_curAction)->setActionData(Turnout::LOCKED);
                else
                    ((ConditionalAction*)_curAction)->setActionData(Route::TOGGLE);
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            if (!referenceByMemory){
                name = validateLightReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_LIGHT_ACTION[selection-1];
            if (actionType==Conditional::ACTION_SET_LIGHT_INTENSITY) {
                Light* lgtx = getLight(name);
                // check if light user name was entered
                if (lgtx == NULL) {
                    return false;
                }
                if (!lgtx->isIntensityVariable()) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            java.text.MessageFormat.format(
//                            tr("Error45"), new Object[] { name }),
//                            tr("ErrorTitle"),  javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Light - %1 - does not have variable intensity.\nPlease enter a light with variable intensity or change action type, and try again.").arg(name));
                    return (false);
                }
                if (!validateIntegerReference(actionType, actionString))
                {
                    return (false);
                }
                ((ConditionalAction*)_curAction)->setActionString(actionString);
            } else if (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME) {
                Light* lgtx = getLight(name);
                // check if light user name was entered
                if (lgtx == NULL) {
                    return false;
                }
                if (!((AbstractLight*)lgtx)->isTransitionAvailable()) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            java.text.MessageFormat.format(
//                            tr("Error40"), new Object[] { name }),
//                            tr("ErrorTitle"),  javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Light - {0} - does not support transition time.\n                                                                                Please enter a light with Transition Time or change action type, and try again.").arg(name));
                    return (false);
                }
                if (!validateIntegerReference(actionType, actionString))
                {
                    return (false);
                }
                ((ConditionalAction*)_curAction)->setActionString(actionString);
            } else if (actionType==Conditional::ACTION_SET_LIGHT) {
                if (_actionBox->currentIndex() == 0)
                    ((ConditionalAction*)_curAction)->setActionData(Light::ON);
                else if (_actionBox->currentIndex() == 1)
                    ((ConditionalAction*)_curAction)->setActionData(Light::OFF);
                else
                    ((ConditionalAction*)_curAction)->setActionData(Route::TOGGLE);
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            if (!referenceByMemory){
                name = validateSignalHeadReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[selection-1];
            if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                QString appStr = (QString)_actionBox->currentText();
                ((ConditionalAction*)_curAction)->setActionData(DefaultConditionalAction::stringToActionData(appStr));
                ((ConditionalAction*)_curAction)->setActionString(appStr);
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:
            if (!referenceByMemory){
                name = validateSignalMastReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_SIGNAL_MAST_ACTION[selection-1];
            if (actionType==Conditional::ACTION_SET_SIGNALMAST_ASPECT) {
                ((ConditionalAction*)_curAction)->setActionString(_actionBox->currentText());
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
        case Conditional::ITEM_TYPE_MEMORY:
            if (referenceByMemory){
//                javax.swing.JOptionPane.showMessageDialog(_editActionFrame, tr("Warn6"), tr("WarnTitle"),
//                        javax.swing.JOptionPane.WARNING_MESSAGE);
                QMessageBox::warning(_editActionFrame, tr("Warning"), tr("A Memory action cannot be referred to indirectly through a memory location."));
                return false;
            }
            name = validateMemoryReference(name);
            if (name == NULL) {
                return false;
            }
            actionType = Conditional::ITEM_TO_MEMORY_ACTION[selection-1];
            if (actionType==Conditional::ACTION_COPY_MEMORY) {
                actionString = validateMemoryReference(actionString);
                if (actionString == "") {
                    return false;
                }
            }
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            ((ConditionalAction*)_curAction)->setActionString(actionString);
            break;
        case Conditional::ITEM_TYPE_LOGIX:
            if (!referenceByMemory){
                name = validateLogixReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_LOGIX_ACTION[selection-1];
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            break;
#if 0
        case Conditional::ITEM_TYPE_WARRANT:
            if (!referenceByMemory){
                name = validateWarrantReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_WARRANT_ACTION[selection-1];
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
            if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
                if (_actionBox->currentIndex() == 0)
                    ((ConditionalAction*)_curAction)->setActionData(Warrant.HALT);
                else if (_actionBox->currentIndex() == 1)
                    ((ConditionalAction*)_curAction)->setActionData(Warrant.RESUME);
                else
                    ((ConditionalAction*)_curAction)->setActionData(Warrant.ABORT);
            } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                            actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                            actionType==Conditional::ACTION_THROTTLE_FACTOR ) {
                ((ConditionalAction*)_curAction)->setActionString(actionString);
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            if (!referenceByMemory){
                name = validateOBlockReference(name);
                if (name == NULL) {
                    return false;
                }
            }
            actionType = Conditional::ITEM_TO_OBLOCK_ACTION[selection-1];
            _actionNameField->setText(name);
            ((ConditionalAction*)_curAction)->setDeviceName(name);
/*                if (actionType==Conditional::ACTION_ALLOCATE_BLOCK_PATH ||
                        actionType==Conditional::ACTION_SET_BLOCK_PATH_TURNOUTS) {
                ((ConditionalAction*)_curAction)->setActionString(_actionBox->currentText());
            }*/
            break;
#endif
        case Conditional::ITEM_TYPE_CLOCK:
            actionType = Conditional::ITEM_TO_CLOCK_ACTION[selection-1];
            if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                int time = parseTime(actionString);
                if ( time<0 ) {
                    return (false);
                }
                ((ConditionalAction*)_curAction)->setActionData(time);
            }
            break;
#if 0
        case Conditional::ITEM_TYPE_AUDIO:
            actionType = Conditional::ITEM_TO_AUDIO_ACTION[selection-1];
            if (actionType==Conditional::ACTION_PLAY_SOUND) {
                ((ConditionalAction*)_curAction)->setActionString(_longActionString->text().trimmed());
            } else if (actionType==Conditional::ACTION_CONTROL_AUDIO) {
                if (!referenceByMemory){
                    name = validateAudioReference(name);
                    if (name == NULL) {
                        return false;
                    }
                }
                _actionNameField->setText(name);
                ((ConditionalAction*)_curAction)->setDeviceName(name);
                switch (_actionBox->currentIndex()) {
                    case 0:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_PLAY);
                        break;
                    case 1:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_STOP);
                        break;
                    case 2:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_PLAY_TOGGLE);
                        break;
                    case 3:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_PAUSE);
                        break;
                    case 4:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_RESUME);
                        break;
                    case 5:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_PAUSE_TOGGLE);
                        break;
                    case 6:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_REWIND);
                        break;
                    case 7:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_FADE_IN);
                        break;
                    case 8:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_FADE_OUT);
                        break;
                    case 9:
                        ((ConditionalAction*)_curAction)->setActionData(Audio.CMD_RESET_POSITION);
                        break;
                }
            }
            break;
        case Conditional::ITEM_TYPE_SCRIPT:
            actionType = Conditional::ITEM_TO_SCRIPT_ACTION[selection-1];
            if (actionType==Conditional::ACTION_RUN_SCRIPT) {
                ((ConditionalAction*)_curAction)->setActionString(_longActionString->text().trimmed());
            } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
                ((ConditionalAction*)_curAction)->setActionString(_shortActionString->text().trimmed());
            }
            break;
#endif
        case Conditional::ITEM_TYPE_OTHER:
            actionType = Conditional::ITEM_TO_OTHER_ACTION[selection-1];
            if (actionType==Conditional::ACTION_TRIGGER_ROUTE) {
                if (!referenceByMemory){
                    name = validateRouteReference(name);
                    if (name == NULL) {
                        return false;
                    }
                }
                _actionNameField->setText(name);
                ((ConditionalAction*)_curAction)->setDeviceName(name);
            }
            break;
        default : break;
    }
    ((ConditionalAction*)_curAction)->setType(actionType);
    if (actionType != Conditional::ACTION_NONE) {
        ((ConditionalAction*)_curAction)->setOption(_actionOptionBox->currentIndex() + 1);
    }
    else {
        ((ConditionalAction*)_curAction)->setOption(0);
    }
    _editActionFrame->adjustSize();
    return (true);
}

int LogixTableAction::getActionTypeFromBox(int itemType, int actionTypeSelection) {
    if (itemType < 0 || actionTypeSelection < 0) {
        return Conditional::ACTION_NONE;
    }
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
            return Conditional::ITEM_TO_SENSOR_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_TURNOUT:
            return Conditional::ITEM_TO_TURNOUT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_LIGHT:
            return Conditional::ITEM_TO_LIGHT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            return Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SIGNALMAST:
            return Conditional::ITEM_TO_SIGNAL_MAST_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_MEMORY:
            return Conditional::ITEM_TO_MEMORY_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_LOGIX:
            return Conditional::ITEM_TO_LOGIX_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_WARRANT:
            return Conditional::ITEM_TO_WARRANT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_OBLOCK:
            return Conditional::ITEM_TO_OBLOCK_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_CLOCK:
            return Conditional::ITEM_TO_CLOCK_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_AUDIO:
            return Conditional::ITEM_TO_AUDIO_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SCRIPT:
            return Conditional::ITEM_TO_SCRIPT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_OTHER:
            return Conditional::ITEM_TO_OTHER_ACTION[actionTypeSelection];
    }
    return Conditional::ACTION_NONE;
}

// *********** Utility Methods ********************

/**
* Checks if String is an integer or references an integer
*/
bool LogixTableAction::validateIntegerReference(int actionType, QString intReference) {
    if (intReference == NULL || intReference.trimmed().length() == 0) {
        displayBadIntegerReference(actionType);
        return false;
    }
    try {
        return validateInteger(actionType, (intReference).toInt());
    } catch (NumberFormatException e) {
        intReference = validateMemoryReference(intReference);
        if (intReference != NULL)		// memory named 'intReference' exits
        {
            Memory* m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getByUserName(intReference);
            if (m == NULL) {
                m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getBySystemName(intReference);
            }
            try {
                return validateInteger(actionType, m->getValue().toInt());
            } catch (NumberFormatException ex) {
//                javax.swing.JOptionPane.showMessageDialog(
//                   editConditionalFrame, java.text.MessageFormat.format(tr("Error24"),
//                   intReference), tr("WarnTitle"), javax.swing.JOptionPane.WARNING_MESSAGE);
                QMessageBox::warning(editConditionalFrame, tr("Warning"), tr("Memory variable \"%1\" currently does not contain an integer value.\nThe action cannot be performed until this value is corrected! ").arg(intReference));

                return true;
            }
        }
        displayBadIntegerReference(actionType);
    }
    return false;
}

/**
* Checks text represents an integer suitable for timing
* throws NumberFormatException
*/
bool LogixTableAction::validateInteger(int actionType, int time) {
    int maxTime = 3600;     // more than 1 hour
    int minTime = 1;
    if (actionType == Conditional::ACTION_SET_LIGHT_INTENSITY)
    {
        maxTime = 100;
        minTime = 0;

    }
    if (time < minTime || time > maxTime) {
        QString errorNum = " ";
        switch(actionType) {
            case Conditional::ACTION_DELAYED_TURNOUT:
                errorNum = "Error39";
                break;
            case Conditional::ACTION_RESET_DELAYED_TURNOUT:
                errorNum = "Error41";
                break;
            case Conditional::ACTION_DELAYED_SENSOR:
                errorNum = "Error23";
                break;
            case Conditional::ACTION_RESET_DELAYED_SENSOR:
                errorNum = "Error27";
                break;
            case Conditional::ACTION_SET_LIGHT_INTENSITY:
                errorNum = "Error42";
                break;
            case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
                errorNum = "Error29";
                break;
            default : break;
        }
//        javax.swing.JOptionPane.showMessageDialog(
//                editConditionalFrame, java.text.MessageFormat.format(tr("Error38"),
//                time, tr(errorNum)), tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Please enter a positive number of seconds less than 1 hour, and try again."));

        return false;
    }
    return true;
}

void LogixTableAction::displayBadIntegerReference(int actionType)
{
    QString errorNum = " ";
    switch(actionType) {
        case Conditional::ACTION_DELAYED_TURNOUT:
            errorNum = "Error39";
            break;
        case Conditional::ACTION_RESET_DELAYED_TURNOUT:
            errorNum = "Error41";
            break;
        case Conditional::ACTION_DELAYED_SENSOR:
            errorNum = "Error23";
            break;
        case Conditional::ACTION_RESET_DELAYED_SENSOR:
            errorNum = "Error27";
            break;
        case Conditional::ACTION_SET_LIGHT_INTENSITY:
//            javax.swing.JOptionPane.showMessageDialog(
//                    editConditionalFrame, tr("Error43"),
//                    tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Enter an integer (digits only) or a Memory variable containing\nan integer to Set Light Intensity."));
            return;
        case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
            errorNum = "Error29";
            break;
    }
//    javax.swing.JOptionPane.showMessageDialog(
//            editConditionalFrame, java.text.MessageFormat.format(tr("Error9"),
//            tr(errorNum)), tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Enter an integer (digits only) or a Memory variable containing\nan integer for the number of seconds to %1 .").arg(errorNum));

}

/**
* Checks Memory reference of text.
*/
QString LogixTableAction::validateMemoryReference(QString name) {
    Memory* m = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getByUserName(name);
            if (m != NULL) {
                return name;
            }
        }
        m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getBySystemName(name);
    }
    if (m == NULL) {
        messageInvalidActionItemName(name, "Memory");
        return NULL;
    }
    return name;
}

/**
* Checks Turnout reference of text.
*/
QString LogixTableAction::validateTurnoutReference(QString name) {
    Turnout* t = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getByUserName(name);
            if (t != NULL) {
                return name;
            }
        }
        t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getBySystemName(name);
    }
    if (t == NULL) {
        messageInvalidActionItemName(name, "Turnout");
        return NULL;
    }
    return name;
}

/**
* Checks SignalHead reference of text.
*/
QString LogixTableAction::validateSignalHeadReference(QString name) {
    SignalHead* h = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            h = ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getByUserName(name);
            if (h != NULL) {
                return name;
            }
        }
        h = ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getBySystemName(name);
    }
    if (h == NULL) {
        messageInvalidActionItemName(name, "SignalHead");
        return NULL;
    }
    return name;
}
/**
* Checks SignalMast reference of text.
*/
QString LogixTableAction::validateSignalMastReference(QString name) {
    SignalMast* h = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            h = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getByUserName(name);
            if (h != NULL) {
                return name;
            }
        }
        h = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->provideSignalMast(name);
    }
    if (h == NULL) {
        messageInvalidActionItemName(name, "SignalMast");
        return NULL;
    }
    return name;
}
#if 0
QString LogixTableAction::validateWarrantReference(QString name) {
    Warrant w = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            w = InstanceManager::warrantManagerInstance().getByUserName(name);
            if (w != NULL) {
                return name;
            }
        }
        w = InstanceManager::warrantManagerInstance().getBySystemName(name);
    }
    if (w == NULL) {
        messageInvalidActionItemName(name, "Warrant");
        return NULL;
    }
    return name;
}
QString LogixTableAction::validateOBlockReference(QString name) {
    OBlock b = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            b = InstanceManager::oBlockManagerInstance().getByUserName(name);
            if (b != NULL) {
                return name;
            }
        }
        b = InstanceManager::oBlockManagerInstance().getBySystemName(name);
    }
    if (b == NULL) {
        messageInvalidActionItemName(name, "OBlock");
        return NULL;
    }
    return name;
}
#endif
/**
* Checks Sensor reference of text.
*/
QString LogixTableAction::validateSensorReference(QString name) {
    Sensor* s = NULL;
    if (name != "") {
        name = name.trimmed();
        if (name.length()>0) {
            s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(name);
            if (s != NULL) {
                return name;
            }
        }
        s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getBySystemName(name);
    }
    s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getBySystemName(name);
    if (s == NULL) {
        messageInvalidActionItemName(name, "Sensor");
        return NULL;
    }
    return name;
}

/**
* Checks Light reference of text.
*/
QString LogixTableAction::validateLightReference(QString name) {
    Light* l = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            l = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getByUserName(name);
            if (l != NULL) {
                return name;
            }
        }
        l = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Light");
        return NULL;
    }
    return name;
}

/**
* Checks Conditional reference of text.
* Forces name to System name
*/
QString LogixTableAction::validateConditionalReference(QString name) {
    Conditional* c = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            c = ((DefaultConditionalManager*)_conditionalManager)->getByUserName(name);
            if (c != NULL) {
                return name;
            }
        }
        c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(name);
    }
    if (c == NULL) {
        messageInvalidActionItemName(name, "Conditional");
        return NULL;
    }
    return name;
}

/**
* Checks Logix reference of text.
*/
QString LogixTableAction::validateLogixReference(QString name) {
    Logix* l = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            l = ((DefaultLogixManager*)_logixManager)->getByUserName(name);
            if (l != NULL) {
                return name;
            }
        }
        l = ((DefaultLogixManager*)_logixManager)->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Logix");
        return NULL;
    }
    return name;
}
/**
* Checks Route reference of text.
*/
QString LogixTableAction::validateRouteReference(QString name) {
    Route* r = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            r = ((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getByUserName(name);
            if (r != NULL) {
                return name;
            }
        }
        r = ((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getBySystemName(name);
    }
    if (r == NULL) {
        messageInvalidActionItemName(name, "Route");
        return NULL;
    }
    return name;
}
#if 0
String validateAudioReference(String name) {
    Audio a = NULL;
    if (name != NULL) {
        name = name.trimmed();
        if (name.length()>0) {
            a = InstanceManager::audioManagerInstance().getByUserName(name);
            if (a != NULL) {
                return name;
            }
        }
        a = InstanceManager::audioManagerInstance().getBySystemName(name);
    }
    if (a == NULL || ( a.getSubType()!=Audio.SOURCE && a.getSubType()!=Audio.LISTENER) ) {
        messageInvalidActionItemName(name, "Audio");
        return NULL;
    }
    return name;
}

String validateEntryExitReference(String name) {
    NamedBean nb = NULL;
    if( name != NULL){
        name = name.trimmed();
        if (name.length()>0) {
            nb = jmri.InstanceManager::getDefault(jmri.jmrit.signalling.EntryExitPairs.class).getNamedBean(name);
            if (nb != NULL) {
                return nb.getSystemName();
            }
        }
    }
    messageInvalidActionItemName(name, "Entry Exit");
    return NULL;
}
#endif
/**
* get Light instance.
*/
Light* LogixTableAction::getLight(QString name) {
    if (name==NULL) {
        return NULL;
    }
    Light* l = NULL;
    name = name.trimmed();
    if (name.length()>0) {
        l = (Light*)((AbstractLightManager*)InstanceManager::lightManagerInstance())->getByUserName(name);
        if (l != NULL) {
            return l;
        }
        l = (Light*)((AbstractLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Light");
    }
    return l;
}

int LogixTableAction::parseTime(QString s) {
    int nHour = 0;
    int nMin = 0;
    bool error = false;
    int index = s.indexOf(':');
    QString hour = NULL;
    QString minute = NULL;
    try {
        if (index > 0)
        {
            hour = s.mid(0, index);
            if (index > 1)

                minute = s.mid(index+1);
            else
                minute = "0";
        } else if (index == 0)
        {
            hour = "0";
            minute = s.mid(index+1);
        } else {
            hour = s;
            minute = "0";
        }
    } catch (IndexOutOfBoundsException ioob ) {
        error = true;
    }
    if (!error)  {
        try {
            nHour = hour.toInt();
            if ((nHour < 0) || (nHour > 24)) {
                error = true;
            }
            nMin = minute.toInt();
            if ((nMin < 0) || (nMin > 59)) {
                error = true;
            }
        } catch (NumberFormatException e) {
            error = true;
        }
    }
    if (error) {
        // if unsuccessful, print error message
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                java.text.MessageFormat.format(tr("Error26"),
//                new Object[] { s }), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editConditionalFrame, tr("Error"), tr("for a 24-hour clock. Please reenter in correct format, and try again. "));
        return (-1);
    }
    // here if successful
    return ((nHour * 60) + nMin);
}

/**
 * Formats time to hh:mm given integer hour and minute
 */
/*public*/ /*static*/ QString LogixTableAction::formatTime(int hour, int minute) {
    QString s = "";
    QString t = QString::number(hour);
    if (t.length() == 2) {
        s = t + ":";
    } else if (t.length() == 1) {
        s = "0" + t + ":";
    }
    t = QString::number(minute);
    if (t.length() == 2) {
        s = s + t;
    } else if (t.length() == 1) {
        s = s + "0" + t;
    }
    if (s.length() != 5) {
        // input error
        s = "00:00";
    }
    return s;
}

/************************ Error Dialogs **********************************/

void LogixTableAction::messageInvalidSignalHeadAppearance(QString name, QString appearance) {
//    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//            java.text.MessageFormat.format(tr("Error21"),
//                    new Object[] { name,  appearance}), tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("\"%2\" is not a valid appearance for Signal Head \"%1\".").arg(appearance).arg(name));
}

void LogixTableAction::messageInvalidActionItemName(QString name, QString itemType) {
//    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//            java.text.MessageFormat.format(tr("Error22"),
//                    new Object[] { name, tr(itemType)}), tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("The name \"%1\" does not match an existing \"%2\"\nPlease correct or create as required, and try again.").arg(name).arg(itemType));
}

/**
 * Sends a duplicate Conditional user name message for Edit Logix window
 */
void LogixTableAction::messageDuplicateConditionalUserName(QString svName) {
//    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//            java.text.MessageFormat.format(tr("Error30"),
//                    new Object[] { svName }), tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(editConditionalFrame, tr("Error"), tr("Duplicate user name error. Entered user name is already in use by Conditional \"{0}\".\nPlease enter a different user name from others in this table.").arg(svName));
}

// *********** Special Table Models ********************

/**
 * Table model for Conditionals in Edit Logix window
 */
///*public*/ class ConditionalTableModel extends AbstractTableModel implements
//        PropertyChangeListener {


/*public*/ ConditionalTableModel::ConditionalTableModel(QObject* parent) : QAbstractTableModel(parent)
{
 //super();
 self = (LogixTableAction*)parent;

 ((DefaultConditionalManager*)self->_conditionalManager)->addPropertyChangeListener((PropertyChangeListener*)this);

 updateConditionalListeners();
}

/*synchronized*/ void ConditionalTableModel::updateConditionalListeners()
{
 // first, remove listeners from the individual objects
 QString sNam = "";
 Conditional* c = NULL;
 self->numConditionals = ((DefaultLogix*)self->_curLogix)->getNumConditionals();
 for (int i = 0; i < self->numConditionals; i++) {
     // if object has been deleted, it's not here; ignore it
     sNam = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(i);
     c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(sNam);
     if (c != NULL)
         ((DefaultConditional*)c)->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 // and add them back in
 for (int i = 0; i < self->numConditionals; i++) {
     sNam = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(i);
     c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(sNam);
     if (c != NULL)
         ((DefaultConditional*)c)->addPropertyChangeListener((PropertyChangeListener*)this);
     connect(((DefaultConditional*)c)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ void ConditionalTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new NamedBean is available in the manager
        updateConditionalListeners();
        fireTableDataChanged();
    } else if (matchPropertyName(e)) {
        // a value changed.
        fireTableDataChanged();
    }
}

/**
 * Is this property event announcing a change this table should display?
 * <P>
 * Note that events will come both from the NamedBeans and also from the
 * manager
 */
bool ConditionalTableModel::matchPropertyName(PropertyChangeEvent* e) {
    return (e->getPropertyName().indexOf("State") >= 0 || e
            ->getPropertyName().indexOf("Appearance") >= 0);
}

//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == BUTTON_COLUMN) {
//            return QPushButton.class;
//        } else {
//            return String.class;
//        }
//    }

/*public*/ int ConditionalTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

/*public*/ int ConditionalTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return (self->numConditionals);
}

/*public*/ Qt::ItemFlags ConditionalTableModel::flags(const QModelIndex &index) const
{
 if (!self->_inReorderMode)
 {
  if ((index.column() == UNAME_COLUMN) || (index.column() == BUTTON_COLUMN))
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

 }
 else if (index.column() == BUTTON_COLUMN)
 {
  if (index.row() >= self->_nextInOrder)
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
     else
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
 return Qt::NoItemFlags;
}

/*public*/ QVariant ConditionalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section)
    {
    case SNAME_COLUMN:
        return tr("System Name");
    case UNAME_COLUMN:
        return tr("User Name");
    case BUTTON_COLUMN:
        return ""; // no label
    case STATE_COLUMN:
        return tr("State");
    default:
        break;
   }
 }
 return QVariant();
}

///*public*/ int ConditionalTableModel::getPreferredWidth(int col) {
//    switch (col)
//    {
//    case SNAME_COLUMN:
//        return new JTextField(6).getPreferredSize().width();
//    case UNAME_COLUMN:
//        return new JTextField(17).getPreferredSize().width();
//    case BUTTON_COLUMN:
//        return new JTextField(6).getPreferredSize().width();
//    case STATE_COLUMN:
//        return new JTextField(12).getPreferredSize().width();
//    default:
//        return new JTextField(5).getPreferredSize().width();
//    }
//}

/*public*/ QVariant ConditionalTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int rx = index.row();
  if ((rx > self->numConditionals) || (self->_curLogix == NULL))
  {
   return QVariant();
  }
  switch (index.column())
  {
  case BUTTON_COLUMN:
   if (!self->_inReorderMode)
   {

    return tr("Edit");
   }
   else if (self->_nextInOrder == 0)
   {
    return tr("First");
   }
   else if (self->_nextInOrder <= index.row())
   {
    return tr("Next");
   }
   else
    return rx + 1;
  case SNAME_COLUMN:
    return ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx);
  case UNAME_COLUMN:
  {
            //log->debug("ConditionalTableModel: "+_curLogix.getConditionalByNumberOrder(rx));
   Conditional* c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
   ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx));
   if (c!=NULL) return ((DefaultConditional*)c)->getUserName();
   else return "";
  }
  case STATE_COLUMN:
  {
   Conditional* c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
            ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx));
    if (c != NULL)
    {
     int curState = ((DefaultConditional*)c)->getState();
     if (curState == Conditional::_TRUE)
        return tr("True");
     if (curState == Conditional::_FALSE)
        return tr("False");
    }
    return tr("Unknown");
   }
   default:
    return tr("Unknown");
  }
 }
 return QVariant();
}

/*public*/ bool  ConditionalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int rx = index.row();
  if ((rx > self->numConditionals) || (self->_curLogix == NULL))
  {
   return true;
  }
  if (index.column() == BUTTON_COLUMN)
  {
   if (self->_inReorderMode)
   {
       self->swapConditional(index.row());
   }
   else if (((DefaultLogix*)self->_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName))
   {
//            javax.swing.JOptionPane.showMessageDialog(
//                        editConditionalFrame, java.text.MessageFormat.format(tr("Warn8"),
//                        new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName}),
//                        rbx .getString("WarnTitle"), javax.swing.JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(self->editConditionalFrame, tr("Warning"), tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName));
   }
   else
   {
#if 0
    // Use separate Thread so window is created on top
    class WindowMaker : public Runnable
    {
     int row;
     WindowMaker(int index.row())
     {
      row = index.row();
     }
     /*public*/ void run()
     {
      //Thread.yield();
      self->editConditionalPressed(row);
     }
    };
    WindowMaker* t = new WindowMaker(rx);
    invokeLater(t);
#endif
    self->editConditionalPressed(index.row());
   }
  }
  else if (index.column() == UNAME_COLUMN)
  {
   QString uName =  value.toString();
   if ( self->_curLogix != NULL)
   {
    Conditional* cn = ((DefaultConditionalManager*)self->_conditionalManager)->getByUserName(self->_curLogix,
            uName.trimmed());
    if (cn == NULL)
    {
     ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
               ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx))
                ->setUserName(uName.trimmed());
     fireTableRowsUpdated(rx, rx);
    }
    else
    {
     QString svName = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx);
     if (cn != ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(svName))
     {
      self->messageDuplicateConditionalUserName(((DefaultConditional*)cn)->getSystemName());
     }
    }
   }
  }
  return true;
 }
 return false;
}

 void ConditionalTableModel::fireTableRowsUpdated(int /*r1*/, int /*r2*/)
 {
  beginResetModel();
  endResetModel();
 }
void ConditionalTableModel::fireTableDataChanged()
{
    beginResetModel();
    endResetModel();

}
void ConditionalTableModel::fireTableRowsInserted(int /*r1*/, int /*r2*/)
{
    beginResetModel();
    endResetModel();
}
void ConditionalTableModel::fireTableRowsDeleted(int /*r1*/, int /*r2*/)
{
    beginResetModel();
    endResetModel();
}

//};

/**
 * Table model for State Variables in Edit Conditional window
 */
///*public*/ class VariableTableModel extends AbstractTableModel {

LVariableTableModel::LVariableTableModel(QObject* parent) : QAbstractTableModel(parent)
{
  self = (LogixTableAction*) parent;
}

//    /*public*/ Class<?> getColumnClass(int c) {
//        switch (c)
//        {
//            case ROWNUM_COLUMN:
//                return String.class;
//            case AND_COLUMN:
//                return JComboBox.class;
//            case NOT_COLUMN:
//                return JComboBox.class;
//            case DESCRIPTION_COLUMN:
//                return String.class;
//            case STATE_COLUMN:
//                return String.class;
//            case TRIGGERS_COLUMN:
//                return Boolean.class;
//            case EDIT_COLUMN:
//                return QPushButton.class;
//            case DELETE_COLUMN:
//                return QPushButton.class;
//        }
//        return String.class;
//    }

/*public*/ int LVariableTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 8;
}

/*public*/ int LVariableTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return self->_variableList->size();
}

/*public*/ Qt::ItemFlags LVariableTableModel::flags(const QModelIndex &index) const
{
 switch (index.column()) {
        case ROWNUM_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case AND_COLUMN:
            if(self->_logicType == Conditional::MIXED )
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
            else
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case NOT_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        case DESCRIPTION_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case STATE_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case TRIGGERS_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
        case EDIT_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        case DELETE_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

/*public*/ QVariant LVariableTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
  case ROWNUM_COLUMN:
        return (tr("Row"));
  case AND_COLUMN:
        return (tr("Operator"));
  case NOT_COLUMN:
        return (tr("Not"));
  case DESCRIPTION_COLUMN:
        return (tr("Description"));
  case STATE_COLUMN:
        return (tr("State"));
  case TRIGGERS_COLUMN:
        return (tr("Triggers Calculation"));
  case EDIT_COLUMN:
        return "";
  case DELETE_COLUMN:
    return "";
  default:
            break;
    }
 }
 return QVariant();
}

///*public*/ int getPreferredWidth(int col) {
//    if (col == DESCRIPTION_COLUMN) {
//        return 500;
//    }
//    return 10;
//}

/*public*/ QVariant LVariableTableModel::data(const QModelIndex &index, int role) const
{
  int r = index.row();
  int c = index.column();
  if ( r >= self->_variableList->size() )
  {
   return QVariant();
  }
  ConditionalVariable* variable = self->_variableList->at(r);
  if(role == Qt::DisplayRole)
  {
   switch (c)
   {
        case ROWNUM_COLUMN:
            return (tr("R") + QString::number(r + 1));
        case AND_COLUMN:
            if (r==0 || self->_logicType==Conditional::MIXED) {
                return "";
            }
            return variable->getOpernString();
        case NOT_COLUMN:
            if (variable->isNegated())
                return tr("NOT");
            break;
        case DESCRIPTION_COLUMN:
            return variable->toString();
        case STATE_COLUMN:
            switch (variable->getState()) {
                case Conditional::_TRUE:
                    return tr("True");
                case Conditional::_FALSE:
                    return tr("False");
                case Conditional::UNKNOWN:
                    return tr("Unknown");
            }
            break;
        case EDIT_COLUMN:
            return tr("Edit");
        case DELETE_COLUMN:
            return tr("Delete");
        default : break;
    }
  }
  if(role == Qt::CheckStateRole)
  {
   if(index.column() == TRIGGERS_COLUMN)
    return variable->doTriggerActions()?Qt::Checked:Qt::Unchecked;
  }

 return QVariant();
}

/*public*/ bool LVariableTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  int r = index.row();
  int c = index.column();
  if ( r >= self->_variableList->size() )
  {
   return false;
  }
  ConditionalVariable* variable = self->_variableList->at(r);
  if(role == Qt::EditRole )
  {
   switch (c)
   {
    case AND_COLUMN:
     self->variableOperatorChanged(r,value.toString());
     break;
    case NOT_COLUMN:
     self->variableNegationChanged(r, value.toString());
     break;
    case STATE_COLUMN:
    {
     QString state = value.toString();
     if ( state==(tr("true").toUpper().trimmed()) ) {
        variable->setState(Conditional::_TRUE);
     } else  if ( state==(tr("false").toUpper().trimmed()) )  {
        variable->setState(Conditional::_FALSE);
     } else {
        variable->setState(Conditional::UNKNOWN);
     }
     break;
    }

    case TRIGGERS_COLUMN:
     variable->setTriggerActions(!(variable->doTriggerActions()));
     break;
    case EDIT_COLUMN:
    {
     if (/*LRouteTableAction::LOGIX_INITIALIZER*/"RTXINITIALIZER"==(((DefaultLogix*)self->_curLogix)->getSystemName()))
     {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Error49"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(self->editConditionalFrame,tr("Error"),  tr("LRoute Initializer antecedent cannot be edited.  (The actions may be edited)"));
        break;
    }
//    // Use separate Thread so window is created on top
//    class WindowMaker implements Runnable {
//        int row;
//        WindowMaker(int r){
//            row = r;
//        }
//        /*public*/ void run() {
//                //Thread.yield();
//                makeEditVariableWindow(row);
//            }
//        }
//    WindowMaker t = new WindowMaker(r);
//    javax.swing.SwingUtilities.invokeLater(t);
      self->makeEditVariableWindow(r);
      break;
     }
     case DELETE_COLUMN:
      self->deleteVariablePressed(r);
      break;
     default : break;
    }
   return true;
   }
   if(role == Qt::CheckStateRole)
   {
    if(index.column() == TRIGGERS_COLUMN)
    {
     variable->setTriggerActions(!(variable->doTriggerActions()));
     return true;
    }
   }
 return false;
}
void LVariableTableModel::fireTableRowsDeleted(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableRowsInserted(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableRowsUpdated(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
//}

/**
 * Table model for Actions in Edit Conditional window
 */
// /*public*/ class ActionTableModel extends AbstractTableModel {

ActionTableModel::ActionTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    this->self = (LogixTableAction*)parent;
}

//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == EDIT_COLUMN || c ==DELETE_COLUMN )
//        {
//            return QPushButton.class;
//        }
//        return super.getColumnClass(c);
//    }

/*public*/ int ActionTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

/*public*/ int ActionTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return self->_actionList->size();
}

/*public*/ Qt::ItemFlags ActionTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == DESCRIPTION_COLUMN)  {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    if ( self->_inReorderMode && (index.column() ==EDIT_COLUMN || index.row() < self->_nextInOrder) ) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

/*public*/ QVariant ActionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if ( section == DESCRIPTION_COLUMN)
    {
        return tr("Action Description");
    }
 }
 return QVariant();
}

//    /*public*/ int getPreferredWidth(int col) {
//        if (col == DESCRIPTION_COLUMN)
//        {
//            return 680;
//        }
//        return 20;
//    }

/*public*/ QVariant ActionTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  if (index.row() >= self->_actionList->size())
  {
   return QVariant();
  }
  switch (index.column())
  {
  case DESCRIPTION_COLUMN:
  {
   ConditionalAction* action = self->_actionList->at(index.row());
   return action->description(self->_triggerOnChangeButton->isChecked());
  }
        case EDIT_COLUMN:
            return tr("Edit");
        case DELETE_COLUMN:
            if (!self->_inReorderMode) {
                return tr("Delete");
            } else if (self->_nextInOrder == 0) {
                return tr("First");
            } else if (self->_nextInOrder <= index.row()) {
                return tr("Next");
            }
      return (index.row() + 1);
    }
 }
 return QVariant();
}

/*public*/ bool  ActionTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
    if (index.column() == EDIT_COLUMN) {
        // Use separate Thread so window is created on top
//        class WindowMaker implements Runnable {
//            int row;
//            WindowMaker(int r){
//                row = r;
//            }
//            /*public*/ void run() {
//                    //Thread.yield();
//                    makeEditActionWindow(row);
//                }
//            }
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
        self->makeEditActionWindow(index.row());
    }
    else if (index.column() == DELETE_COLUMN) {
        if (self->_inReorderMode)
            self->swapActions(index.row());
        else
            self->deleteActionPressed(index.row());
    }
 }
 return false;
}
void ActionTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsDeleted(int, int)
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsUpdated(int, int)
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsInserted(int, int)
{
 beginResetModel();
 endResetModel();
}

//}

/*public*/ QString LogixTableAction::getClassDescription() { return tr("Logix Table"); }

/*protected*/ QString LogixTableAction::getClassName() { return "jmri.jmrit.beantable.LogixTableAction"; }

// From AbstractAction
/**
   * Sets whether the {@code Action} is enabled. The default is {@code true}.
   *
   * @param newValue  {@code true} to enable the action, {@code false} to
   *                  disable it
   * @see Action#setEnabled
   */
/*public*/ void LogixTableAction::setEnabled(bool newValue)
{
 bool oldValue = this->enabled;

 if (oldValue != newValue)
 {
  this->enabled = newValue;
// firePropertyChange("enabled", Boolean.valueOf(oldValue), Boolean.valueOf(newValue));
  emit propertyChange("enabled", QVariant(oldValue), QVariant(newValue));
 }
}
//	static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LogixTableAction.class.getName());
//}
/* @(#)LogixTableAction.java */
void LogixTableAction::editConditional(int i )
{
 log->debug(tr("edit conditional row %1").arg(i));
 editConditionalPressed(i);
}
QString LogixTableAction::getName()
{
 return "jmri.jmrit.beantable.LogixTableAction";
}
