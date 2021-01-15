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
//#include "defaultusermessagepreferences.h"
#include <QCheckBox>
#include "gridbagconstraints.h"
#include "../LayoutEditor/inputdialog.h"
#include "../LayoutEditor/maintenance.h"
//#include "logixwidget.h"
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
#include "jmriuserpreferencesmanager.h"
#include "oblock.h"
#include <QLabel>
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QApplication>
#include <QMenuBar>
#include "flowlayout.h"
#include "htmltextedit.h"
#include <QScrollArea>
#include "joptionpane.h"
#include "fileutil.h"
#include "conditionaltreeedit.h"
#include "conditionallistedit.h"
#include "conditional.h"
#include "box.h"

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
// _suppressReminder = false;
// _suppressIndirectRef = false;
 _pickTables = NULL;

 // current focus variables
 _curLogix = NULL;
// numConditionals = 0;
 conditionalRowNumber = 0;
 //_curConditional = NULL;

 if(parent == NULL)
  return;

 // Edit variables
// editLogixFrame = NULL;
 _inEditMode = false;
 _inCopyMode = false;
// _inReorderMode = false;
// _nextInOrder = 0;
// editUserName = new JTextField(20);
// status = new QLabel(" ");

 // Add Logix Variables
 addLogixFrame = NULL;
 _systemName = new JTextField(10);
 _addUserName = new JTextField(10);
 _addUserName->setMinimumSize(_addUserName->sizeHint());
 _autoSystemName = new QCheckBox(tr("Automatically Generate System Name"));
 _sysNameLabel = new QLabel(tr("Logix System Name"));
 _userNameLabel = new QLabel(tr("Logix User Name"));
 prefMgr = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 systemNameAuto = QString(getClassName())+".AutoSystemName";

 // Edit Conditional Variables
// inEditConditionalMode = false;
// editConditionalFrame = NULL;
// conditionalUserName = new JTextField(22);
 _actionTableModel = NULL;
 _variableTableModel = NULL;
 _logicType = Conditional::ALL_AND;
 _antecedent = "";
 _newItem = false;   // marks a new Action or Variable object added
 selectionModes = QStringList();
 selectionModes << QString("USEMULTI") << QString("USESINGLE") << QString("USECOMBO");
 editModes = QStringList();
 editModes << QString("LISTEDIT") << QString("TREEEDIT");
 _conditionalManager = NULL; // set when LogixAction is created
 userFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
 _inEditMode = false;
 _listEdit = NULL;
 _treeEdit = NULL;

 _editActionFrame = NULL;
 _editVariableFrame = NULL;

 //_actionTypeListener = new ActionTypeListener(this);
 //actionSignalHeadNameListener = new ActionSignalHeadNameListener(this);
 //variableSignalHeadNameListener = new VariableSignalHeadNameListener(this);
 //variableSignalTestStateListener = new VariableSignalTestStateListener(this);

 // set up managers - no need to use InstanceManager since both managers are
 // Default only (internal). We use InstanceManager to get managers for
 // compatibility with other facilities.
 _logixManager = (LogixManager*)InstanceManager::getNullableDefault("LogixManager");
 _conditionalManager = (ConditionalManager*)InstanceManager::getNullableDefault("ConditionalManager");
 // disable ourself if there is no Logix manager or no Conditional manager available
 if ((_logixManager == NULL) || (_conditionalManager == NULL))
 {
  setEnabled(false);
 }

 _saveTargetNames = QSet<QString>();
 _saveTargetList = QMap<QString, QList<QString> >();

}

LogixTableAction::LogixTableAction(const LogixTableAction & that) : AbstractTableAction(that.text(), that.parent())
{}
//	/*public*/ LogixTableAction() {
//		this("Logix Table");
//	}

//	static /*final*/ ResourceBundle rbx = ResourceBundle
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
 connect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), m, SLOT(propertyChange(PropertyChangeEvent*)));
}

// overlay the state column with the edit column
LogixTableModel::LogixTableModel(LogixTableAction *self)
 : BeanTableDataModel(self)
{
 this->self = self;
 enabledString = tr("Enabled");
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
  return  Qt::ItemIsEnabled |  Qt::ItemIsUserCheckable;
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
  }
 }
 return BeanTableDataModel::data(index, role);

}

/*public*/ bool LogixTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  if (index.column() == EDITCOL)
  {
   // set up to edit
    QString sName = sysNameList.at(index.row());
    if ( tr("Edit")==(value.toString()) )
    {
        self->editPressed(sName);
    }
    else if (tr("Browser")== (value.toString()))
    {  // NOI18N
        self->conditionalRowNumber = index.row();
        self->browserPressed(sName);
    }
    else if (tr("Copy")==(value.toString()) )
    {
        self->copyPressed(sName);
    }
    else if ( tr("Delete")==(value.toString()) )
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
 return (LogixManager*)InstanceManager::getDefault("LogixManager");
 //return self->_logixManager;

}

/*public*/ NamedBean* LogixTableModel::getBySystemName(QString name) const {
    return ((LogixManager*)InstanceManager::getDefault("LogixManager"))->getBySystemName(
            name);
}

/*public*/ NamedBean* LogixTableModel::getByUserName(QString name) {
    return ((LogixManager*)InstanceManager::getDefault("LogixManager"))->getByUserName(
            name);
}
/*public*/ int LogixTableModel::getDisplayDeleteMsg()
{
 return ((UserPreferencesManager*)  InstanceManager::getDefault("UserPreferencesManager"))->getMultipleChoiceOption(self->getClassName(),"deleteInUse");
}
/*public*/ void LogixTableModel::setDisplayDeleteMsg(int boo)
{
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption(self-> getClassName(), "deleteInUse", boo);
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
/*protected*/ void LogixTableModel::configDeleteColumn(JTable* table) {
//    JComboBox editCombo = new JComboBox();
//    editCombo->layout()->addWidget(new QLabel("ButtonSelect"));
//    editCombo->layout()->addWidget(new QLabel("ButtonEdit"));
//    editCombo->layout()->addWidget(new QLabel("ButtonCopy"));
//    editCombo->layout()->addWidget(new QLabel("ButtonDelete"));
//    TableColumn col = table.getColumnModel().getColumn(BeanTableDataModel.DELETECOL);
//    col.setCellEditor(new DefaultCellEditor(editCombo));
 QStringList items = QStringList() << tr("Select") << tr("Edit") << tr("Browser") << tr("Copy") << tr("Delete");
 table->setItemDelegateForColumn(BeanTableDataModel::DELETECOL, new JComboBoxEditor(items, this));
}

/*protected*/ void LogixTableModel::configValueColumn(JTable */*table*/)
{
 // do nothing but override BeanTableDataModel::configValueColumn
}

// Not needed - here for interface compatibility
/*public*/ void LogixTableModel::clickOn(NamedBean* /*t*/) {
}

/*public*/ QString LogixTableModel::getValue(QString /*s*/) const
{
    return "";
}

/*protected*/ QString LogixTableModel::getBeanType(){
    return tr("Logix");
}
//    };
//}

// set title for Logix table
/*protected*/ void LogixTableAction::setTitle() {
    f->setTitle(tr("Logix Table"));
}

/**
 * Insert 2 table specific menus.
 * <p>
 * Accounts for the Window and Help menus, which are already added to the
 * menu bar as part of the creation of the JFrame, by adding the new menus 2
 * places earlier unless the table is part of the ListedTableFrame, which
 * adds the Help menu later on.
 *
 * @param f the JFrame of this table
 */
//@Override
/*public*/ void LogixTableAction::setMenuBar(BeanTableFrame* f) {
    loadSelectionMode();
    loadEditorMode();

    QMenu* menu = new QMenu(tr("Options"));  // NOI18N
//    menu.setMnemonic(KeyEvent.VK_O);
    QMenuBar* menuBar = f->menuBar();
    QList<QAction*> actions = menuBar->actions();
      int pos = menuBar->actions().count() - 1; // count the number of menus to insert the TableMenus before 'Window' and 'Help'
    int offset = 1;
    log->debug("setMenuBar number of menu items = " + QString::number(pos));  // NOI18N
    for (int i = 0; i <= pos; i++)
    {
        //if (menuBar.getComponent(i) instanceof JMenu)
     if(qobject_cast<QMenu*>(menuBar->actions().at(i)))
        {
            if (((QMenu*) menuBar->actions().at(i))->title() == (tr("Help")))
            {  // NOI18N
                offset = -1; // correct for use as part of ListedTableAction where the Help Menu is not yet present
            }
        }
    }

    QActionGroup* enableButtonGroup = new QActionGroup(this);
    QAction* r = new QAction(tr("Enable All Logix"),this);  // NOI18N
    r->setCheckable(true);
//    r.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            enableAll(true);
//        }
//    });
    connect(r, SIGNAL(triggered(bool)), this, SLOT(enableAll(bool)));
    enableButtonGroup->addAction(r);
    r->setChecked(true);
    menu->addAction(r);

    r = new QAction(tr("Disable All Logix"),this);  // NOI18N
//    r.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            enableAll(false);
//        }
//    });
    connect(r, SIGNAL(triggered(bool)), this, SLOT(enableAll(bool)));
    enableButtonGroup->addAction(r);
    menu->addAction(r);

    menu->addSeparator();

    QActionGroup* modeButtonGroup = new QActionGroup(this);
    r = new QAction(tr("Use Traditional  Pick Lists"), this);  // NOI18N
    r->setCheckable(true);
//    r.addItemListener(new ItemListener() {
//        @Override
//        public void itemStateChanged(ItemEvent e) {
//            setSelectionMode(SelectionMode.USEMULTI);
//        }
//    });
    connect(r, SIGNAL(triggered(bool)), this, SLOT(on_useMulti_triggered()));
    modeButtonGroup->addAction(r);
    menu->addAction(r);
    r->setChecked(_selectionMode == SelectionMode::USEMULTI);

    r = new QAction(tr("Use Single Pick Lists"),this);  // NOI18N
    r->setCheckable(true);
//    r.addItemListener(new ItemListener() {
//        @Override
//        public void itemStateChanged(ItemEvent e) {
//            setSelectionMode(SelectionMode.USESINGLE);
//        }
//    });
    connect(r, SIGNAL(triggered()), this , SLOT(on_useSingle_triggered()));
    modeButtonGroup->addAction(r);
    menu->addAction(r);
    r->setChecked(_selectionMode == SelectionMode::USESINGLE);

    r = new QAction(tr("Use Combo Name Boxes"), this);  // NOI18N
    r->setCheckable(true);
//    r.addItemListener(new ItemListener() {
//        @Override
//        public void itemStateChanged(ItemEvent e) {
//            setSelectionMode(SelectionMode.USECOMBO);
//        }
//    });
    connect(r, SIGNAL(triggered()), this, SLOT(on_useComboNameBoxes_triggered()));
    modeButtonGroup->addAction(r);
    menu->addAction(r);
    r->setChecked(_selectionMode == SelectionMode::USECOMBO);

    menu->addSeparator();

    QActionGroup* viewButtonGroup = new QActionGroup(this);
    r = new QAction(tr("List Edit"),this);  // NOI18N
    r->setCheckable(true);
//    r.addItemListener(new ItemListener() {
//        @Override
//        public void itemStateChanged(ItemEvent e) {
//            setEditorMode(EditMode.LISTEDIT);
//        }
//    });
    connect(r, SIGNAL(triggered()), this, SLOT(on_listEdit_triggered()));
    viewButtonGroup->addAction(r);
    menu->addAction(r);
    r->setChecked(_editMode == EditMode::LISTEDIT);

    r = new QAction(tr("Tree Edit"), this);  // NOI18N
    r->setCheckable(true);
//    r.addItemListener(new ItemListener() {
//        @Override
//        public void itemStateChanged(ItemEvent e) {
//            setEditorMode(EditMode.TREEEDIT);
//        }
//    });
    connect(r, SIGNAL(triggered()), this, SLOT(on_treeEdit_triggered()));
    viewButtonGroup->addAction(r);
    menu->addAction(r);
    r->setChecked(_editMode == EditMode::TREEEDIT);

    menuBar->insertMenu(actions.at(pos+offset -1), menu);//menu, pos + offset);

    menu = new QMenu(tr("Tools"));  // NOI18N
//    menu.setMnemonic(KeyEvent.VK_T);

    QAction* item = new QAction(tr("Open PickList Tables"), this);  // NOI18N
//    item.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            openPickListTable();
//        }
//    });
    connect(item, SIGNAL(triggered()), this, SLOT(openPickListTable()));
    menu->addAction(item);

    item = new QAction(tr("Find Orphans"), this);  // NOI18N
//    item.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            findOrphansPressed(e);
//        }
//    });
    connect(item, SIGNAL(triggered()),this, SLOT(findOrphansPressed()));
    menu->addAction(item);

    item = new QAction(tr("Empty Conditionals"), this);  // NOI18N
//    item.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            findEmptyPressed(e);
//        }
//    });
    connect(item, SIGNAL(triggered()),this, SLOT(findEmptyPressed()));
    menu->addAction(item);

    item = new QAction(tr("Cross Reference"), this);  // NOI18N
//    item.addActionListener(new ActionListener() {
//        BeanTableFrame parent;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            new RefDialog(parent);
//        }

//        ActionListener init(BeanTableFrame f) {
//            parent = f;
//            return this;
//        }
//    }.init(f));
    CrossReferenceActionListener* listener = new CrossReferenceActionListener(f, this);
    connect(item, SIGNAL(triggered()), listener, SLOT(actionPerformed()));
    menu->addAction(item);

    item = new QAction(tr("Display Where Used"), this);  // NOI18N
//    item.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            makeWhereUsedWindow();
//        }
//    });
    connect(item, SIGNAL(triggered()), this, SLOT(makeWhereUsedWindow()));
    menu->addAction(item);

    //menuBar->addMenu(menu, pos + offset + 1); // add this menu to the right of the previous
    //menu->insertMenu(actions.at(pos+offset-1), menu);
    menuBar->addMenu(menu);
}

CrossReferenceActionListener::CrossReferenceActionListener(BeanTableFrame* frame, LogixTableAction* parent)
{
 this->frame = frame;
 this->parent = parent;
}
void CrossReferenceActionListener::actionPerformed()
{
  new RefDialog(frame, parent);
}

void LogixTableAction::on_useMulti_triggered()
{
 setSelectionMode(SelectionMode::USEMULTI);
}

void LogixTableAction::on_useSingle_triggered()
{
 setSelectionMode(SelectionMode::USESINGLE);
}

void LogixTableAction::on_useComboNameBoxes_triggered()
{
 setSelectionMode(SelectionMode::USECOMBO);
}

void LogixTableAction::on_listEdit_triggered()
{
 setEditorMode(EditMode::LISTEDIT);
}

void LogixTableAction::on_treeEdit_triggered()
{
 setEditorMode(EditMode::TREEEDIT);
}

/**
 * Get the saved mode selection, default to the tranditional tabbed pick
 * list.
 * <p>
 * During the menu build process, the corresponding menu item is set to
 * selected.
 *
 * @since 4.7.3
 */
void LogixTableAction::loadSelectionMode()
{
 QVariant modeName = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            getProperty(getClassName(), "Selection Mode");      // NOI18N
 if (modeName == QVariant()) {
     _selectionMode = SelectionMode::USEMULTI;
 } else {
     QString currentMode =  modeName.toString();
     if (currentMode== "USEMULTI")        // NOI18N
             _selectionMode = SelectionMode::USEMULTI;
     else if(currentMode == "USESINGLE")       // NOI18N
             _selectionMode = SelectionMode::USESINGLE;
       else if(currentMode == "USECOMBO")        // NOI18N
             _selectionMode = SelectionMode::USECOMBO;
      else
               log->warn(tr("Invalid Logix conditional selection mode value, '%1', returned").arg(currentMode));  // NOI18N
             _selectionMode = SelectionMode::USEMULTI;
 }
}

/**
 * Save the mode selection. Called by menu item change events.
 *
 * @since 4.7.3
 * @param newMode The SelectionMode enum constant
 */
void LogixTableAction::setSelectionMode(SelectionMode newMode) {
    _selectionMode = newMode;
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setProperty(getClassName(), "Selection Mode", /*newMode->toString()*/selectionModes.at((int)newMode));  // NOI18N
}

/**
 * Get the saved mode selection, default to the tranditional conditional
 * list editor
 * <p>
 * During the menu build process, the corresponding menu item is set to
 * selected.
 *
 * @since 4.9.x
 */
void LogixTableAction::loadEditorMode() {
    QVariant modeName = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            getProperty(getClassName(), "Edit Mode");      // NOI18N
    if (modeName == QVariant()) {
        _editMode = EditMode::LISTEDIT;
    } else {
        QString currentMode = modeName.toString();
        if (currentMode == "LISTEDIT")        // NOI18N
                _editMode = EditMode::LISTEDIT;
         else if (currentMode ==  "TREEEDIT")       // NOI18N
                _editMode = EditMode::TREEEDIT;
         else
        {
         log->warn(tr("Invalid conditional edit mode value, '%1', returned").arg(currentMode));  // NOI18N
         _editMode = EditMode::LISTEDIT;
        }
    }
}

/**
 * Save the view mode selection. Called by menu item change events.
 *
 * @since 4.9.x
 * @param newMode The ViewMode enum constant
 */
void LogixTableAction::setEditorMode(EditMode newMode) {
    _editMode = newMode;
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setProperty(getClassName(), "Edit Mode", editModes.at((int)newMode));  // NOI18N
}

/**
 * Open a new Pick List to drag Actions from to form Logix Conditionals.
 */
void LogixTableAction::openPickListTable() {
    if (_pickTables == nullptr) {
        _pickTables = new PickFrame(tr("Pick List"));  // NOI18N
    } else {
        _pickTables->setVisible(true);
    }
    _pickTables->toFront();
}

void LogixTableAction::crossReference_requested()
{
 RefDialog* dlg = new RefDialog(f,this);
 dlg->exec();
}


void LogixTableAction::findEmptyPressed(ActionEvent* /*e*/) {
            Maintenance::findEmptyPressed(f);
}
void LogixTableAction::findOrphansPressed(ActionEvent* /*e*/) {
            Maintenance::findOrphansPressed(f);
}
//class RefDialog extends JDialog {

RefDialog::RefDialog(BeanTableFrame *frame, LogixTableAction* action) : JDialog(frame, tr("CrossReference"), true)
{
 //super(frame, tr("CrossReference"), true);
 this->action = action;
 QWidget* extraPanel = new QWidget();
 extraPanel->setLayout(new QVBoxLayout(extraPanel));
 _devNameField = new JTextField(30);
 QWidget* panel = action->makeEditPanel(_devNameField, "Element Name", "System or User name of an element to find where it is referenced.");
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

void RefDialog::deviceReportPressed(JActionEvent* /*e*/)
{
 Maintenance::deviceReportPressed(_devNameField->text(), NULL);
    //dispose();
 close();
}
//};

void LogixTableAction::enableAll(bool enable) {
    QStringList sysNameList = ((DefaultLogixManager*)_logixManager)->getSystemNameList();
    for (int i=0; i<sysNameList.size(); i++) {
        Logix* x = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(sysNameList.at(i));
        ((DefaultLogix*)x)->setEnabled(enable);
    }
}

/*protected*/ QString LogixTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.LogixTable";
}

// /*static*/ /*final*/ int LogixTableAction::STRUT = 10;

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
  QWidget* panel5 = makeAddLogixFrame(tr("Add Logix"), tr("Please enter system name and user name, then","click Create Logix, then add Conditionals."));
  // Create Logix
  create = new QPushButton(tr("Create Logix"));
//  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//  sizePolicy.setVerticalStretch(0);
//  sizePolicy.setHorizontalStretch(0);
//  sizePolicy.setWidthForHeight(create->sizePolicy().hasHeightForWidth());
//  create->setSizePolicy(sizePolicy);
  panel5->layout()->addWidget(create);
  //        create->layout()->addActionListener(new ActionListener() {
  //            /*public*/ void actionPerformed(ActionEvent e) {
  //                createPressed(e);
  //            }
  //        });
  connect(create, SIGNAL(clicked()), this, SLOT(createPressed()));
  create->setToolTip(tr("Press to create a new Logix"));
 }
 addLogixFrame->pack();
 addLogixFrame->setVisible(true);
 _autoSystemName->setChecked(false);
 if(((UserPreferencesManager*) prefMgr)->getSimplePreferenceState(systemNameAuto))
 _autoSystemName->setChecked(true);
}

/**
*  shared method for window to create or copy Logix
* Returns the button panel
*/
QWidget* LogixTableAction::makeAddLogixFrame(QString titleId, QString messageId1,QString messageId2)
{
 addLogixFrame = new JmriJFrameX(titleId,true,true);
 addLogixFrame->addHelpMenu(
            "package.jmri.jmrit.beantable.LogixAddEdit", true);
 addLogixFrame->setLocation(50, 30);
 addLogixFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
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
// QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
// sizePolicy.setHorizontalStretch(0);
// sizePolicy.setVerticalStretch(0);
// sizePolicy.setHeightForWidth(cancel->sizePolicy().hasHeightForWidth());
// cancel->setSizePolicy(sizePolicy);
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
 ((QVBoxLayout*)contentPane->layout())->addWidget(panel5,0,Qt::AlignCenter);

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
void AddLogixFrameWindowListener::windowClosing(QCloseEvent * e)
{
 e->ignore();
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
        _inCopyMode = false;
        if (f!=NULL)
            f->setVisible(true);
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
 if(((UserPreferencesManager*)prefMgr)->getSimplePreferenceState(systemNameAuto))
 _autoSystemName->setChecked(true);
//                }
//            };
if (log->isDebugEnabled()) log->debug("copyPressed Thread started for " + sName);
    //javax.swing.SwingUtilities.invokeLater(t);
    //t.start();
 _inCopyMode = true;
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
  targetLogix = _logixManager->createNewLogix(uName);
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
  targetLogix = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
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
 Logix* srcLogic = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(_logixSysName);
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

    // Update where used with the copy results
    _saveTargetNames.clear();
    QSet<QString> newTargetNames = QSet<QString>();
    loadReferenceNames(*cOld->getCopyOfStateVariables(), newTargetNames.toList());
    updateWhereUsed(newTargetNames, cNewSysName);
}

bool LogixTableAction::checkLogixUserName(QString uName)
{
 // check if a Logix with the same user name exists
 if (uName!=NULL && uName.trimmed().length() > 0)
 {
  Logix* x = (Logix*)((DefaultLogixManager*)_logixManager)->getByUserName(uName);
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


bool LogixTableAction::checkFlags(QString sName)
{
 if (_inEditMode)
 {
  // Already editing a Logix, ask for completion of that edit
  JOptionPane::showMessageDialog(nullptr,
          tr("Cannot edit two Logixs at the same time. Please complete edit of Logix \"%1\" and try again.").arg(_curLogix->getSystemName()), tr("Error"),
          JOptionPane::ERROR_MESSAGE);
  if (_treeEdit != nullptr) {
      _treeEdit->bringToFront();
  } else if (_listEdit != nullptr) {
      _listEdit->bringToFront();
  }
  return false;
 }
 if (_inCopyMode) {
     // Already editing a Logix, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Error31"),
//                new Object[] { _logixSysName }), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(nullptr,tr("Error"), tr("Copy of Logix \"{0}\" in progress.  Please complete and try again.").arg(_logixSysName) );
     return false;
 }
 if (sName != "") {
  // check if a Logix with this name exists
  Logix* x = (Logix*)_logixManager->getBySystemName(sName);
  if (x == nullptr) {
      // Logix does not exist, so cannot be edited
      log->error("No Logix with system name: " + sName);
      JOptionPane::showMessageDialog(nullptr, tr("Cannot find a Logix with that system name."), tr("Error"), JOptionPane::ERROR_MESSAGE);
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
 QString sName = "";
 QString uName = _addUserName->text().trimmed();
 if (uName.length() == 0) {
     uName = "";
 }
 if (_autoSystemName->isChecked())
 {
     if (!checkLogixUserName(uName)) {
         return;
     }
     _curLogix = _logixManager->createNewLogix(uName);
     sName = _curLogix->getSystemName();
 }
 else
 {
     if (!checkLogixSysName()) {
         return;
     }
     // Get validated system name
     sName = _systemName->text();
     // check if a Logix with this name already exists
     Logix* x = NULL;
     try {
         x = (Logix*)_logixManager->getBySystemName(sName);
         if(x == NULL) throw Exception();
     } catch (Exception ex) {
         // user input no good
         handleCreateException(sName);
         return; // without creating
     }
     if (x != NULL) {
         // Logix already exists
         JOptionPane::showMessageDialog(addLogixFrame, tr("A Logix with this system name already exists.\nPlease change system name and try again."), tr("Error"), // NOI18N
                 JOptionPane::ERROR_MESSAGE);
         return;
     }
     if (!checkLogixUserName(uName)) {
         return;
     }
     // Create the new Logix
     _curLogix = _logixManager->createNewLogix(sName, uName);
     if (_curLogix == NULL) {
         // should never get here unless there is an assignment conflict
         log->error("Failure to create Logix with System Name: " + sName);  // NOI18N
         return;
     }
 }
 cancelAddPressed(NULL);
 // create the Edit Logix Window
 editPressed(sName);
 prefMgr = ((UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager"));
 if(prefMgr != NULL)
 {
     prefMgr->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
 };//);
}

void LogixTableAction::handleCreateException(QString sysName) {
        JOptionPane::showMessageDialog(addLogixFrame,
                tr("ErrorLogixAddFailed %1").arg( // NOI18N
                        sysName),
                tr("Error"), // NOI18N
                JOptionPane::ERROR_MESSAGE);
    }

// *********** Methods for Edit Logix Window ********************

/**
 * Responds to the Edit button pressed in Logix table
 *
 * @param sName system name of Logix to be edited
 */
void LogixTableAction::editPressed(QString sName) {
 _curLogix = (Logix*)_logixManager->getBySystemName(sName);
 if (!checkFlags(sName)) {
     return;
 }

 if (sName == (SensorGroupFrame::logixSysName)) {
     // Sensor group message
     JOptionPane::showMessageDialog(
             NULL, tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName), // NOI18N
             tr("Warning"), // NOI18N
             JOptionPane::WARNING_MESSAGE);
     return;
 }

 // Create a new conditional edit view, add the listener.
 if (_editMode == EditMode::TREEEDIT)
 {
     _treeEdit = new ConditionalTreeEdit(sName);
     _inEditMode = true;
     _treeEdit->addLogixEventListener(new LTALogixEventListener(sName, this));
//     {
//         //@Override
//         public void logixEventOccurred() {
//             String lgxName = sName;
//             _treeEdit.logixData.forEach((key, value) -> {
//                 if (key == ("Finish")) {                  // NOI18N
//                     _treeEdit = NULL;
//                     _inEditMode = false;
//                     _curLogix.activateLogix();
//                     f.setVisible(true);
//                 } else if (key == ("Delete")) {           // NOI18N
//                     deletePressed(value);
//                 } else if (key == ("chgUname")) {         // NOI18N
//                     Logix x = _logixManager.getBySystemName(lgxName);
//                     x.setUserName(value);
//                     m.fireTableDataChanged();
//                 }
//             });
//         }
//     });
 }
 else {
     _listEdit = new ConditionalListEdit(sName);
     _inEditMode = true;
     _listEdit->addLogixEventListener(new LTALogixEventListener1(sName, this));
//     {
//         //@Override
//         public void logixEventOccurred() {
//             String lgxName = sName;
//             _listEdit.logixData.forEach((key, value) -> {
//                 if (key == ("Finish")) {                  // NOI18N
//                     _listEdit = NULL;
//                     _inEditMode = false;
//                     _curLogix.activateLogix();
//                     f.setVisible(true);
//                 } else if (key == ("Delete")) {           // NOI18N
//                     deletePressed(value);
//                 } else if (key == ("chgUname")) {         // NOI18N
//                     Logix x = _logixManager.getBySystemName(lgxName);
//                     x.setUserName(value);
//                     m.fireTableDataChanged();
//                 }
//             });
//         }
//     });
 }
}

/*public*/ LTALogixEventListener::LTALogixEventListener(QString sName, LogixTableAction *lta) : LogixEventListener((ConditionalEditBase*)lta)
{
 this->sName = sName;
 this->lta = lta;
}

/*public*/ void LTALogixEventListener::logixEventOccurred() {
    QString lgxName = sName;
    //_treeEdit.logixData.forEach((key, value) ->
    QMapIterator<QString, QString> iter(*lta->_treeEdit->logixData);
    while(iter.hasNext())
    {
     iter.next();
     QString key = iter.key();
     QString value = iter.value();
        if (key == ("Finish")) {                  // NOI18N
            lta->_treeEdit = NULL;
            lta->_inEditMode = false;
            lta->_curLogix->activateLogix();
            lta->f->setVisible(true);
        } else if (key == ("Delete")) {           // NOI18N
            lta->deletePressed(value);
        } else if (key == ("chgUname")) {         // NOI18N
            Logix* x = (Logix*)lta->_logixManager->getBySystemName(lgxName);
            x->setUserName(value);
            lta->m->fireTableDataChanged();
        }
    };//);
}

/*public*/ LTALogixEventListener1::LTALogixEventListener1(QString sName, LogixTableAction *lta) : LogixEventListener((ConditionalEditBase*)lta)
{
 this->sName = sName;
 this->lta = lta;
}

//@Override
/*public*/ void LTALogixEventListener1::logixEventOccurred()
{
 QString lgxName = sName;
 //_listEdit.logixData.forEach((key, value) ->
 if(lta->_listEdit->logixData == nullptr) return;
 QMapIterator<QString, QString> iter(*lta->_listEdit->logixData);
 while(iter.hasNext())
 {
  iter.next();
  QString key = iter.key();
  QString value = iter.value();
     if (key == ("Finish")) {                  // NOI18N
         lta->_listEdit = NULL;
         lta->_inEditMode = false;
         lta->_curLogix->activateLogix();
         lta->f->setVisible(true);
     } else if (key == ("Delete")) {           // NOI18N
         lta->deletePressed(value);
     } else if (key == ("chgUname")) {         // NOI18N
         Logix* x = (Logix*)lta->_logixManager->getBySystemName(lgxName);
         x->setUserName(value);
         lta->m->fireTableDataChanged();
     }
 };//);
}

/**
 * Display reminder to save.
 */
void LogixTableAction::showSaveReminder() {
    if (_showReminder) {
        if (InstanceManager::getNullableDefault("UserPreferencesManager") != NULL) {
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage(tr("Reminder"), tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg("Logix"),(getClassName()),
                            "remindSaveLogix"); // NOI18N
        }
    }
}

/*public*/ void LogixTableAction::setMessagePreferencesDetails()
{
 QMap<int,QString>* options = new QMap< int,QString>(/*3*/);
 options->insert(0x00, tr("Always Ask"));
 options->insert(0x01, tr("Never Delete"));
 options->insert(0x02, tr("Delete Without Prompting"));
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMessageItemDetails(getClassName(), "delete", tr("When Deleting the logix"), options, 0x00);
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setPreferenceItemDetails(getClassName(), "remindSaveLogix", tr("Suppress Save Reminders"));
 AbstractTableAction::setMessagePreferencesDetails();
}

void LogixTableAction::deletePressed(ActionEvent */*e*/)
{
 deletePressed("");
}
/**
 * Respond to the Delete combo selection Logix window or conditional view
 * delete request.
 *
 * @param sName system name of bean to be deleted
 */
void LogixTableAction::deletePressed(QString sName) {
    if (!checkFlags(sName)) {
        return;
    }
    if (!checkConditionalReferences(sName)) {
        return;
    }
    /*final*/ Logix* x = (Logix*)_logixManager->getBySystemName(sName);
    UserPreferencesManager* p;
    p = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");
    if (p != NULL && p->getMultipleChoiceOption(getClassName(), "delete") == 0x02) {     // NOI18N
        if (x != NULL) {
            _logixManager->deleteLogix(x);
            deleteSourceWhereUsed();
        }
    } else {
        /*final*/ JDialog* dialog = new JDialog();
        QString msg;
        dialog->setTitle(tr("Confirm"));     // NOI18N
        dialog->setLocationRelativeTo(NULL);
        dialog->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
        QWidget* container = new QWidget();
        //container.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        QVBoxLayout* containerLayout;
        container->setLayout(containerLayout =new QVBoxLayout()); //container, BoxLayout.Y_AXIS));
        msg = tr("Are you sure you want to delete Logix \"%1\"?").arg(sName);    // NOI18N
        QLabel* question = new QLabel(msg);
        //question.setAlignmentX(Component.CENTER_ALIGNMENT);
        containerLayout->addWidget(question, 0, Qt::AlignCenter);

        QCheckBox* remember =  new QCheckBox(tr("MessageRememberSetting"));  // NOI18N
        //remember->setFont(remember->getFont().deriveFont(10f));
        QFont f = remember->font();
        f.setPointSizeF(10.);
        remember->setFont(f);
        //remember.setAlignmentX(Component.CENTER_ALIGNMENT);

        QPushButton* yesButton = new QPushButton(tr("Yes"));    // NOI18N
        QPushButton* noButton = new QPushButton(tr("No"));      // NOI18N
        QWidget* button = new QWidget();
        FlowLayout* buttonLayout = new FlowLayout(button);
        //button.setAlignmentX(Component.CENTER_ALIGNMENT);
        buttonLayout->addWidget(yesButton);
        buttonLayout->addWidget(noButton);
        containerLayout->addWidget(button);

//        noButton.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                //there is no point in remebering this the user will never be
//                //able to delete a bean!
//                /*if(remember.isSelected()){
//                 setDisplayDeleteMsg(0x01);
//                 }*/
//                dialog.dispose();
//            }
//        });
        connect(noButton, SIGNAL(clicked(bool)), this, SLOT(on_noButtonClicked()));

//        yesButton.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                if (p != NULL && remember.isSelected()) {
//                    p.setMultipleChoiceOption(getClassName(), "delete", 0x02);  // NOI18N
//                }
//                if (x != NULL) {
//                    _logixManager.deleteLogix(x);
//                    deleteSourceWhereUsed();
//                }
//                dialog.dispose();
//            }
//        });
        connect(yesButton, SIGNAL(clicked(bool)), this, SLOT(on_yesButtonClicked()));
        containerLayout->addWidget(remember);
//        container.setAlignmentX(Component.CENTER_ALIGNMENT);
//        container.setAlignmentY(Component.CENTER_ALIGNMENT);
        dialog->getContentPane()->layout()->addWidget(container);
        dialog->pack();
        dialog->setModal(true);
        dialog->setVisible(true);
    }

    f->setVisible(true);
}

void LogixTableAction::on_noButtonClicked()
{
 //there is no point in remebering this the user will never be
 //able to delete a bean!
 /*if(remember.isSelected()){
  setDisplayDeleteMsg(0x01);
  }*/
 //dialog->dispose();
 dialog->close();
}

void LogixTableAction::on_yesButtonClicked()
{
     if (p != NULL && remember->isChecked()) {
         p->setMultipleChoiceOption(getClassName(), "delete", 0x02);  // NOI18N
     }
     if (x != NULL) {
         _logixManager->deleteLogix(x);
         deleteSourceWhereUsed();
     }
     //dialog.dispose();
     dialog->close();
}

/**
 * Build a tree set from conditional references.
 *
 * @since 4.7.4
 * @param varList The ConditionalVariable list that might contain
 *                conditional references
 * @param treeSet A tree set to be built from the varList data
 */
void LogixTableAction::loadReferenceNames(QList<ConditionalVariable*> varList, QStringList treeSet) {
    treeSet.clear();
    for (ConditionalVariable* var : varList) {
        if (var->getType() == Conditional::TYPE_CONDITIONAL_TRUE || var->getType() == Conditional::TYPE_CONDITIONAL_FALSE) {
            treeSet.append(var->getName());
        }
    }
}

bool LogixTableAction::checkConditionalUserName(QString uName, Logix* logix) {
    if ((uName != NULL) && (!(uName == ("")))) {
        Conditional* p = _conditionalManager->getByUserName(logix, uName);
        if (p != NULL) {
            // Conditional with this user name already exists
            log->error("Failure to update Conditional with Duplicate User Name: " // NOI18N
                    + uName);
            JOptionPane::showMessageDialog(
                    NULL, tr("New user name is already in use. Cannot update this Conditional.\nPlease change user name and try again."), // NOI18N
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return false;
        }
    }
    return true;
}
/**
 * Check form of Conditional systemName.
 *
 * @param sName system name of bean to be checked
 * @return false if sName is empty string or NULL
 */
bool LogixTableAction::checkConditionalSystemName(QString sName) {
    if ((sName != NULL) && (!(sName == ("")))) {
        Conditional* p = _conditionalManager->getBySystemName(sName);
        if (p != NULL) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

/**
 * Check for conditional references
 *
 * @since 4.7.4
 * @param logixName The Logix under consideration
 * @return true if no references
 */
bool LogixTableAction::checkConditionalReferences(QString logixName) {
    _saveTargetList.clear();
    Logix* x = _logixManager->getLogix(logixName);
    int numConditionals = x->getNumConditionals();
    if (numConditionals > 0) {
        for (int i = 0; i < numConditionals; i++) {
            QString csName = x->getConditionalByNumberOrder(i);

            // If the conditional is a where used source, retain it for later
            QList<QString> targetList =((ConditionalManager*) InstanceManager::getDefault("ConditionalManager"))->getTargetList(csName);
            if (targetList.size() > 0) {
                _saveTargetList.insert(csName, targetList);
            }

            // If the conditional is a where used target, check scope
            QList<QString> refList =((ConditionalManager*) InstanceManager::getDefault("ConditionalManager"))->getWhereUsed(csName);
            if (!refList.isEmpty()) {
                for (QString refName : refList) {
                    Logix* xRef = _conditionalManager->getParentLogix(refName);
                    QString xsName = xRef->getSystemName();
                    if (logixName == (xsName)) {
                        // Member of the same Logix
                        continue;
                    }

                    // External references have to be removed before the Logix can be deleted.
                    Conditional* c = x->getConditional(csName);
                    Conditional* cRef = xRef->getConditional(refName);
                    QStringList msgs = QStringList() <<c->getUserName() << c->getSystemName() << cRef->getUserName() <<
                        cRef->getSystemName()<< xRef->getUserName()<< xRef->getSystemName();
                    JOptionPane::showMessageDialog(NULL,
                            tr("Conditional \"%1\" (%2) is a Conditional Variable in the Conditional,\n\"%3\" (%4), of Logix, \"%5\" (%6).\n Please remove that variable first.").arg(msgs.at(0)).arg(msgs.at(1)).arg(msgs.at(2)).arg(msgs.at(3)).arg(msgs.at(4)).arg(msgs.at(5)), // NOI18N
                           tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);    // NOI18N
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Remove target/source where used entries after a Logix delete
 *
 * @since 4.7.4
 */
void LogixTableAction::deleteSourceWhereUsed() {
   // _saveTargetList.forEach((refName, targetList) -> {
   foreach(QString refName, _saveTargetList.keys())
   {
    QList<QString> targetList = _saveTargetList.value(refName);
    for (QString targetName : targetList)
    {
     ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->removeWhereUsed(targetName, refName);
    }
   }//);
}

/**
 * Update the conditional reference where used.
 * <p>
 * The difference between the saved target names and new target names is
 * used to add/remove where used references.
 *
 * @since 4.7.4
 * @param newTargetNames The conditional target names after updating
 * @param refName        The system name for the referencing conditional
 */
void LogixTableAction::updateWhereUsed(QSet<QString> newTargetNames, QString refName) {
    QSet<QString> deleteNames = QSet<QString>(_saveTargetNames);
    //deleteNames.removeAll(newTargetNames);
    foreach (QString str, newTargetNames)
    {
     if(deleteNames.contains(str))
      deleteNames.remove(str);
    }
    for (QString deleteName : deleteNames)
    {
     ((ConditionalManager*)   InstanceManager::getDefault("ConditionalManager"))->removeWhereUsed(deleteName, refName);
    }

    QSet<QString> addNames = QSet<QString>(newTargetNames);
    //addNames.removeAll(_saveTargetNames);
    foreach (QString str, _saveTargetNames)
    {
     if(addNames.contains(str))
      addNames.remove(str);
    }
    for (QString addName : addNames) {
        ((ConditionalManager*)   InstanceManager::getDefault("ConditionalManager"))->addWhereUsed(addName, refName);
    }
}

/**
 * Create Variable and Action editing pane center part.
 *
 * @param comp  Field or comboBox to include on sub pane
 * @param label property key for label
 * @param hint  property key for tooltip for this sub pane
 * @return JPanel containing interface
 */
QWidget* LogixTableAction::makeEditPanel(QWidget* comp, QString label, QString hint) {
    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
      pLayout->addWidget(new QLabel(label));
    panelLayout->addWidget(p);
    if (hint != NULL) {
        panel->setToolTip(hint);
    }
//    comp->setMaximumSize(comp->sizeHint());  // override for text fields
    panelLayout->addWidget(comp);
    panelLayout->addWidget(Box::createVerticalGlue());
    return panel;
}

#if 0
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
#endif
/***************************** Edit Action Window and methods ***********************/



LTAEditActionFrameWindowListener::LTAEditActionFrameWindowListener(LogixTableAction * /*zlta*/)
{
 this->lta = lta;
}
void LTAEditActionFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 //lta->cancelEditActionPressed();
}
#if 0
void LogixTableAction::on_actionItemType_changed(int select)
{
 if (log->isDebugEnabled()) log->debug("_actionItemTypeBoxListener: select= "+select);
  actionItemChanged(select);
  _editActionFrame->adjustSize();
}

void LogixTableAction::on_actionSetButton_Pressed()
{
  validateAction();
//  setFileLocation(/*e*/);

}
#endif
/******* Methods shared by Edit Variable and Edit Action Windows **********/

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
#if 0
//	static /*final*/ org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LogixTableAction.class.getName());
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
#endif
//ItemDelegate::ItemDelegate(QStringList items, QObject *parent)
//: QAbstractItemDelegate(parent)
//{
// Items = items;
//}


//QWidget* ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & /*index*/ ) const
//{
//  QComboBox* editor = new QComboBox(parent);
//  editor->addItems(Items);
//  return editor;
//}

//void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//  QComboBox *comboBox = static_cast<QComboBox*>(editor);
//  int value = index.model()->data(index, Qt::EditRole).toUInt();
//  comboBox->setCurrentIndex(value);
//}

//void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//  QComboBox *comboBox = static_cast<QComboBox*>(editor);

//  model->setData(index, comboBox->currentText(), Qt::EditRole);
//}

//void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//  editor->setGeometry(option.rect);
//}
//void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//  QStyleOptionViewItemV4 myOption = option;
//  QString text = Items.at(index.row());

//  myOption.text = text;

//  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
//}
//QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
//{
// return QSize (80, 100);
//}

// ------------ Methods for Conditional References Window ------------
/**
 * Builds the conditional references window when the Conditional Variable
 * References menu item is selected.
 * <p>
 * This is a stand-alone window that can be closed at any time.
 *
 * @since 4.7.4
 */
void LogixTableAction::makeWhereUsedWindow() {

    JmriJFrame* referenceListFrame = new JmriJFrameX(tr("Conditional Variable References"), false, true);    // NOI18N
    QWidget* contentPane = referenceListFrame->getContentPane();
    QVBoxLayout* contentPaneLayout;
    contentPane->setLayout(contentPaneLayout = new QVBoxLayout()); //(contentPane, BoxLayout.Y_AXIS));

    // build header information
    QWidget* panel1 = new QWidget();
    FlowLayout* panel1Layout;
    panel1->setLayout(panel1Layout = new FlowLayout());//FlowLayout::LEFT, 10, 5));
    panel1Layout->addWidget(new QLabel(tr("Target")));    // NOI18N
    panel1Layout->addWidget(new QLabel(tr("Source")));    // NOI18N
    contentPaneLayout->addWidget(panel1);

    // Build the conditional references listing
    //QScrollArea* scrollPane = NULL;
    HtmlTextEdit* textContent = buildWhereUsedListing();
//    scrollPane = new QScrollArea(/*textContent*/);
//    scrollPane->setWidget(textContent);
    contentPaneLayout->addWidget(/*scrollPane*/textContent);

    referenceListFrame->pack();
    referenceListFrame->setVisible(true);
}

/**
 * Creates a component containing the conditional reference where used list.
 * The source is {@link jmri.ConditionalManager#getWhereUsedMap()}
 *
 * @return a TextArea, empty if reference is not used
 * @since 4.7.4
 */
HtmlTextEdit* LogixTableAction::buildWhereUsedListing() {
    HtmlTextEdit* condText = new HtmlTextEdit();
    condText->setText("");
    QMap<QString, QList<QString> > whereUsed = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getWhereUsedMap();
    //SortedSet<String> targets = new TreeSet<>(whereUsed.keySet());
    QStringList targets = whereUsed.keys();
    //targets.forEach((target) -> {
    foreach(QString target, targets)
    {
        condText->append("\n" + target + "\t" + getWhereUsedName(target) + "  \n");
        QList<QString> refNames = whereUsed.value(target);
        //refNames.forEach((refName) ->
        foreach(QString refName, refNames)
        {
            condText->append("\t\t" + refName + "\t" + getWhereUsedName(refName) + "  \n");
        }//);
    } //);
    //condText->setCaretPosition(0);
    condText->setTabStopWidth(2); //setTabSize(2);
    condText->setEditable(false);
    return condText;
}

QString LogixTableAction::getWhereUsedName(QString cName) {
    return _conditionalManager->getBySystemName(cName)->getUserName();
}

// ------------ Methods for Conditional Browser Window ------------
/**
 * Responds to the Browse button pressed in Logix table
 *
 * @param sName The selected Logix system name
 */
void LogixTableAction::browserPressed(QString sName) {
    // Logix was found, create the window
    _curLogix = (Logix*)_logixManager->getBySystemName(sName);
    makeBrowserWindow();
}

/**
 * creates and initializes the conditionals browser window
 */
void LogixTableAction::makeBrowserWindow() {
    condBrowserFrame = new JmriJFrameX(tr("Conditional Browser"), false, true);   // NOI18N
    condBrowserFrame->addHelpMenu("package.jmri.jmrit.beantable.LogixAddEdit", true);            // NOI18N

    QWidget* contentPane = condBrowserFrame->getContentPane();
    //contentPane.setLayout(new BorderLayout());
    QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);

    // LOGIX header information
    QWidget* topPanel = new QWidget();
    QHBoxLayout* topPanelLayout = new QHBoxLayout(topPanel);
    QString tStr = tr("BrowserLogix") + " " + _curLogix->getSystemName() + "    " // NOI18N
            + _curLogix->getUserName() + "    "
            + ((_curLogix->getEnabled())
                    ? tr("(Enabled)") // NOI18N
                    : tr("(Disabled)"));  // NOI18N
    topPanelLayout->addWidget(new QLabel(tStr));
    contentPaneLayout->addWidget(topPanel,0, Qt::AlignTop);//, BorderLayout.NORTH);

    // Build the conditionals listing
    QScrollArea* scrollPane = NULL;
    HtmlTextEdit* textContent = buildConditionalListing();
    scrollPane = new QScrollArea();//JScrollPane(textContent);
    scrollPane->setWidget(textContent);
    scrollPane->setWidgetResizable(true);
    contentPaneLayout->addWidget(scrollPane);

    QWidget* bottomPanel = new QWidget();
    //bottomPanel.setLayout(new BorderLayout());
    QHBoxLayout* bottomPanelLayout = new QHBoxLayout(bottomPanel);
    QPushButton* helpBrowse = new QPushButton(tr("Help"));   // NOI18N
    bottomPanelLayout->addWidget(helpBrowse, 0, Qt::AlignLeft);//BorderLayout.WEST);
//    helpBrowse.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            JOptionPane.showMessageDialog(condBrowserFrame,
//                    tr("BrowserHelpText"),   // NOI18N
//                    tr("BrowserHelpTitle"),  // NOI18N
//                    JOptionPane.INFORMATION_MESSAGE);
//        }
//    });
    connect(helpBrowse, SIGNAL(clicked()), this, SLOT(on_helpBrowse_triggered()));
    QPushButton* saveBrowse = new QPushButton(tr("Save to Text File"));   // NOI18N
    saveBrowse->setToolTip(tr("Save the browser content to a text file"));      // NOI18N
    bottomPanelLayout->addWidget(saveBrowse, 0, Qt::AlignRight);//BorderLayout.EAST);
//    saveBrowse.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            saveBrowserPressed();
//        }
//    });
    connect(saveBrowse, SIGNAL(clicked()), this, SLOT(saveBrowserPressed()));
    contentPaneLayout->addWidget(bottomPanel, 0, Qt::AlignBottom);//BorderLayout.SOUTH);

    condBrowserFrame->pack();
    condBrowserFrame->setVisible(true);
}  // makeBrowserWindow

void LogixTableAction::on_helpBrowse_triggered()
{
 JOptionPane::showMessageDialog(condBrowserFrame,
         tr("Trigger state variables are indicated by [x].\nThe text file format is based on using a monospace font."),   // NOI18N
         tr("Browser Help"),  // NOI18N
         JOptionPane::INFORMATION_MESSAGE);

}

/**
 * Save the Logix browser window content to a text file.
 */
void LogixTableAction::saveBrowserPressed() {
    userFileChooser->setApproveButtonText(tr("Save Content"));  // NOI18N
    userFileChooser->setDialogTitle(tr("Save Browser Content"));  // NOI18N
//    userFileChooser->rescanCurrentDirectory();
    // Default to logix system name.txt
    userFileChooser->setSelectedFile(new File(_curLogix->getSystemName() + ".txt"));  // NOI18N
    int retVal = userFileChooser->showSaveDialog(NULL);
    if (retVal != JFileChooser::APPROVE_OPTION) {
        log->debug("Save browser content stopped, no file selected");  // NOI18N
        return;  // give up if no file selected or cancel pressed
    }
    File* file = userFileChooser->getSelectedFile();
    log->debug(tr("Save browser content to '%1'").arg(file->toString()));  // NOI18N

    if (file->exists()) {
//        Object[] options = {tr("BrowserSaveDuplicateReplace"),  // NOI18N
//                tr("BrowserSaveDuplicateAppend"),  // NOI18N
//                tr("BrowserSaveDuplicateCancel")};  // NOI18N
     QVariantList options = QVariantList();
     options << "Replace" << "Append" << "Cancel";
        int selectedOption = JOptionPane::showOptionDialog(NULL,
                tr("File \"%1\" already exists, select Append or Replace").arg(  // NOI18N
                        file->getName()),
                tr("Duplicate File"),  // NOI18N
                JOptionPane::DEFAULT_OPTION,
                JOptionPane::WARNING_MESSAGE,
                QIcon(), options, options.at(0));
        if (selectedOption == 2 || selectedOption == -1) {
            log->debug("Save browser content stopped, file replace/append cancelled");  // NOI18N
            return; // Cancel selected or dialog box closed
        }
        if (selectedOption == 0) {
            FileUtil::_delete(file);  // Replace selected
        }
    }

    // Create the file content
    QString tStr = tr("BrowserLogix") + " " + _curLogix->getSystemName() + "    "  // NOI18N
            + _curLogix->getUserName() + "    "
            + ((_curLogix->getEnabled())
                    ? tr("(Enabled)")    // NOI18N
                    : tr("(Disabled)")); // NOI18N
    HtmlTextEdit* textContent = buildConditionalListing();
    try {
        // ADD Logix Header inforation first
        FileUtil::appendTextToFile(file, tStr);
        FileUtil::appendTextToFile(file, textContent->toPlainText());
    } catch (IOException e) {
        log->error(tr("Unable to write browser content to '%1', exception: '%2'").arg(file->toString()).arg(e.getMessage()));  // NOI18N
    }
}

/**
 * Builds a Component representing the current conditionals for the selected
 * Logix statement.
 *
 * @return a TextArea listing existing conditionals; will be empty if there
 *         are none
 */
HtmlTextEdit* LogixTableAction::buildConditionalListing() {
    QString showSystemName,
            showCondName,
            condName,
            operand,
            tStr;

    QList<ConditionalVariable*>* variableList;
    QList<ConditionalAction*>* actionList;
    ConditionalVariable* variable;
    ConditionalAction* action;
    QString _antecedent = "";

    HtmlTextEdit* condText = new HtmlTextEdit();
    condText->setFont(QFont("Monospace",12));//new Font(Font.MONOSPACED, Font.PLAIN, 12));
    condText->setText("");
    int numConditionals = _curLogix->getNumConditionals();
    for (int rx = 0; rx < numConditionals; rx++)
    {
     conditionalRowNumber = rx;
     Conditional* curConditional = _conditionalManager->getBySystemName(_curLogix->getConditionalByNumberOrder(rx));
     variableList = curConditional->getCopyOfStateVariables();
     _logixSysName = curConditional->getSystemName();
     actionList = curConditional->getCopyOfActions();

     showCondName = curConditional->getUserName();
     if (showCondName.isNull()) {
         showCondName = "";
     }
     showSystemName = curConditional->getSystemName();

     // If no user name for a conditional, create one using C + row number
     if (showCondName == ("")) {
         showCondName = "C" + QString::number(rx + 1);
     }
     condText->append("\n  " + showSystemName + "  " + showCondName + "   \n");
     if (curConditional->getLogicType() == Conditional::MIXED) {
         _antecedent = curConditional->getAntecedentExpression();
         condText->append("   " + tr("Antecedent:") + " " + _antecedent + "  \n");   // NOI18N
     }

     for (int i = 0; i < variableList->size(); i++) {
         variable = variableList->at(i);
         QString varTrigger = (variable->doTriggerActions())
                 ? "[x]" // NOI18N
                 : "[ ]";
         tStr = "    " + varTrigger + " ";
         tStr = tStr + " R" + QString::number(i + 1) + (i > 8 ? " " : "  ");  // Makes {Rx}bb or {Rxx}b
         condText->append(tStr);

         operand = variable->getOpernString();
         if (i == 0) { // add the IF to the first conditional
             condText->append(tr("IF") + " " + operand + " ");    // NOI18N
         } else {
             condText->append("  " + operand + " ");
         }
         if (variable->isNegated()) {
             condText->append(tr("NOT") + " ");     // NOI18N
         }
         condText->append(variable->toString() + "   \n");
     } // for _variableList

     if (actionList->size() > 0) {
         condText->append("             " + tr("THEN") + "   \n");  // NOI18N
         bool triggerType = curConditional->getTriggerOnChange();
         for (int i = 0; i < actionList->size(); i++) {
             action = actionList->value(i);
             condName = action->description(triggerType);
             condText->append("               " + condName + "   \n");
         }  // for _actionList
     } else {
         condText->append("             " + tr("<no action defined>") + "   \n\n");    // NOI18N
     }
    } // for numConditionals

    //condText->setCaretPosition(0);
    condText->setTabStopWidth(4);
    condText->setEditable(false);
    return condText;
}  // buildConditionalListing

