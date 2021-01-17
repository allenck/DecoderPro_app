#include "signalgrouptableaction.h"
#include "instancemanager.h"
#include "signalgroupmanager.h"
#include "signalgroup.h"
#include "signalhead.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "singleturnoutsignalhead.h"
#include "runnable.h"
#include "jtextfield.h"
#include <QComboBox>
#include "stringutil.h"
#include "jmribeancombobox.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include "flowlayout.h"
#include <QTableView>
#include <QGroupBox>
#include "signalmastmanager.h"
#include "signalgroupsubtableaction.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalgroup.h"
#include "defaultsignalgroupmanager.h"
#include "defaultsignalmastmanager.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QHeaderView>
#include "../LayoutEditor/jmrijframe.h"
#include <QLabel>
#include <QPushButton>

//SignalGroupTableAction::SignalGroupTableAction(QObject *parent) :
//    QObject(parent)
//{
//}

/*private*/ /*static*/ int SignalGroupTableAction::ROW_HEIGHT = 0;

/*private*/ /*static*/ QStringList SignalGroupTableAction::COLUMN_NAMES = QStringList() << tr("System Name") <<
                                        tr("User Name") <<
                                        tr("Include") <<
                                        tr("Set State"); // used in class SignalGroupOutputModel (Turnouts and Sensors)
/*private*/ /*static*/ QStringList SignalGroupTableAction::COLUMN_SIG_NAMES = QStringList() << tr("System Name") <<
                                        tr("User Name") <<
                                        tr("Include") <<
                                        tr("On State") << tr("Off State") << tr("Edit"); // used in class SignalGroupSignalHeadModel

/*private*/ /*static*/ QVector<QString> SignalGroupTableAction::signalStates =  QVector<QString>()  << tr("Dark") <<  tr("Red") << tr("Yellow") << tr("Green") << tr("Lunar");
/*private*/ /*static*/ QVector<int> SignalGroupTableAction::signalStatesValues =  QVector<int>() << SignalHead::DARK << SignalHead::RED << SignalHead::YELLOW << SignalHead::GREEN << SignalHead::LUNAR;

/**
 * Swing action to create and register a SignalGroup Table

 * Based in part on RouteTableAction.java by Bob Jacobsen
 *
 * @author	Kevin Dickerson    Copyright (C) 2010
 *
 * @version     $Revision: 19870 $
 */

// /*public*/ class SignalGroupTableAction extends AbstractTableAction implements PropertyChangeListener {

//	static final ResourceBundle rbx = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.LogixTableBundle");

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param s
 */
/*public*/ SignalGroupTableAction::SignalGroupTableAction(QString s, QObject *parent) : AbstractTableAction(s, parent)
{
 //super(s);
    common();
    name = s;
}
void SignalGroupTableAction::common()
{
 log = new Logger("SignalGroupTableAction");

 showAll = true;
 _systemName = new JTextField(10);
 _userName = new JTextField(22);

 addFrame = NULL;

 selGroup = NULL;
 allButton = NULL;
 includedButton = NULL;

 nameLabel = new QLabel("SignalGroup System Name:");
 userLabel = new QLabel("SignalGroup User Name:");
 fixedSystemName = new QLabel("xxxxxxxxxxx");

 deleteButton = new QPushButton("Delete SignalGroup");
 updateButton = new QPushButton("Done");

 p2xs = NULL;   // SignalHead list table
 p2xsi = NULL;   // SignalHead list table
 p3xsi = NULL;

 curSignalGroup = NULL;
 SignalGroupDirty = false;  // true to fire reminder to save work
 editMode = false;
 signalEditFrame = NULL;

 // disable ourself if there is no primary SignalGroup manager available
 if (InstanceManager::getDefault("SignalGroupManager")==NULL)
 {
  setEnabled(false);
 }
}
void SignalGroupTableAction::setEnabled(bool b) { bEnabled = b;}

/*public*/ SignalGroupTableAction::SignalGroupTableAction(QObject *parent) : AbstractTableAction(tr("Signal Group Table"), parent)
{
 common();
 name = (tr("Signal Group Table"));
}


/*public*/ void SignalGroupTableAction::propertyChange(PropertyChangeEvent* e)
{
#if 1
 if (e->getPropertyName()==("UpdateCondition"))
 {
  for (int i=_signalList.size()-1; i>=0; i--)
  {
   SignalGroupSignal* signal = _signalList.at(i);
    //String tSysName = signal.getSysName();
   SignalHead* sigBean = signal->getBean();
    if (curSignalGroup->isSignalIncluded(sigBean) ) {
        signal->setIncluded(true);
        signal->setOnState(curSignalGroup->getSignalHeadOnState(sigBean));
        signal->setOffState(curSignalGroup->getSignalHeadOffState(sigBean));
    } else {
        signal->setIncluded(false);
    }
}
    }
#endif
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of SignalGroups
 */
/*protected*/ void SignalGroupTableAction::createModel()
{
 SGBeanTableDataModel* mm = new SGBeanTableDataModel(this);
 m = (BeanTableDataModel*)mm;
}

SGBeanTableDataModel::SGBeanTableDataModel(SignalGroupTableAction *act)
 : BeanTableDataModel(act)
{
 this->act = act;
 DefaultSignalGroupManager* mgr = (DefaultSignalGroupManager*)getManager();
 connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //updateNameList();
 init();
}

/*public*/ int SGBeanTableDataModel::columnCount(const QModelIndex &/*parent*/) const { return 6;}

/*public*/ QVariant SGBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
  if (col==SETCOL) return "";    // no heading on "Edit"
  if (col==ENABLECOL) return "Enabled";
  if (col==COMMENTCOL) return "Comment";
  if (col==DELETECOL) return "";
  else return BeanTableDataModel::headerData(section,orientation,role);
 }
 return QVariant();
}
// /*public*/ Class<?> getColumnClass(int col) {
//    if (col==SETCOL) return JButton.class;
//    if (col==ENABLECOL) return Boolean.class;
//    if (col==DELETECOL) return JButton.class;
//    if (col==COMMENTCOL) return String.class;
//    else return super.getColumnClass(col);
//}

/*public*/ int SGBeanTableDataModel::getPreferredWidth(int col) {
    if (col==SETCOL) return  JTextField(6).getPreferredSize().width();
    if (col==ENABLECOL) return  JTextField(6).getPreferredSize().width();
    if (col==COMMENTCOL) return  JTextField(15).getPreferredSize().width();
    if (col==DELETECOL) return  JTextField(22).getPreferredSize().width();
    else return BeanTableDataModel::getPreferredWidth(col);
}

/*public*/ Qt::ItemFlags SGBeanTableDataModel::flags(const QModelIndex &index) const
{
 int col = index.column();
    if (col==COMMENTCOL) return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (col==SETCOL) return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (col==ENABLECOL) return  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    if (col==DELETECOL) return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else return BeanTableDataModel::flags(index);
}

/*public*/ QVariant SGBeanTableDataModel::data(const QModelIndex &mindex, int role) const
{
 int col = mindex.column();
 int row = mindex.row();
 NamedBean* b;
 if(role == Qt::CheckStateRole)
 {
  if(col == ENABLECOL)
  {
   if(((SignalGroup*)getBySystemName(data(index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString()))->getEnabled())
    return Qt::Checked;
   else
    return Qt::Unchecked;
  }
 }
 if(role == Qt::DisplayRole)
 {
  if (col==SETCOL)
  {
   return "Edit";
  }
  else if (col==ENABLECOL)
  {
//   return ((SignalGroup*)getBySystemName(data(index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString()))->getEnabled();
//        //return true;
   return "";
  }
  else if (col==COMMENTCOL)
  {
   b = getBySystemName(sysNameList.at(row));
   return (b!=NULL) ? b->getComment() : "";
  }
  else if (col==DELETECOL)  //
   return tr("Delete");
 }
 return BeanTableDataModel::data(mindex, role);
}

/*public*/ bool SGBeanTableDataModel::setData(const QModelIndex &mindex, const QVariant &value, int role)
{
 int col = mindex.column();
 int row = mindex.row();
 if(role == Qt::CheckStateRole)
 {
   if (col==ENABLECOL)
   {
     // alternate
     SignalGroup* r = (SignalGroup*)getBySystemName(data(index(row, SYSNAMECOL),Qt::DisplayRole).toString());
     bool v = r->getEnabled();
     r->setEnabled(!v);
     return true;
   }
 }
 if(role == Qt::EditRole)
 {
  if (col==SETCOL)
  {
   // set up to edit. Use separate Thread so window is created on top
        class WindowMaker : public  Runnable {
            int row;
            SignalGroupTableAction* _act;
            SGBeanTableDataModel* _model;
        public:
            WindowMaker(int r,SGBeanTableDataModel* model){
                row = r;
                _model = model;
                _act= model->act;
            }
            /*public*/ void run() {
                    //Thread.yield();
                    _act->addPressed(NULL);
                    _act->_systemName->setText(_model->data(_model->index(row, SYSNAMECOL),Qt::DisplayRole).toString());
                    _act->editPressed(NULL); // don't really want to stop SignalGroup w/o user action
                }
            };
        WindowMaker* t = new WindowMaker(row, this);
//        /*javax.swing.SwingUtilities.*/invokeLater(t);
        t->start();
    }
    else if (col==COMMENTCOL) {
        getBySystemName(sysNameList.at(row))->setComment(
                 value.toString());
        fireTableRowsUpdated(row, row);
            }
    else if (col==DELETECOL) {
        // button fired, delete Bean
        deleteBean(row, col);
    }
  return true;
 }
 BeanTableDataModel::setData(mindex,value, role);
}

/*public*/ void SGBeanTableDataModel::configureTable(JTable* table)
{
//      table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//      table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//      table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
    setColumnToHoldButton(table, SETCOL);
    //setColumnToHoldButton(table, DELETECOL);
    table->hideColumn(VALUECOL);
    setColumnToHoldButton(table, DELETECOL, new QPushButton(tr("Delete")));
 BeanTableDataModel::configureTable(table);
}

/*protected*/ void SGBeanTableDataModel::configDeleteColumn(JTable* table)
{
 // have the delete column hold a button
 //act->setColumnToHoldButton(table, DELETECOL, new QPushButton(tr("Delete")));

}

/**
 * Delete the bean after all the checking has been done.
 * <P>
 * Deactivate the light, then use the superclass to delete it.
 */
void SGBeanTableDataModel::doDelete(NamedBean* bean) {
    //((SignalGroup)bean).deActivateSignalGroup();
    BeanTableDataModel::doDelete(bean);
}

// want to update when enabled parameter changes
/*protected*/ bool SGBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("Enabled")) return true;
    //if (e.getPropertyName()==("Locked")) return true;
    else return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ Manager* SGBeanTableDataModel::getManager()
{
 //return static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"));
 return (Manager*)InstanceManager::getNullableDefault("SignalGroupManager");
}

/*public*/ NamedBean* SGBeanTableDataModel::getBySystemName(QString name) const
{
 return ((SignalGroupManager*)InstanceManager::getNullableDefault("SignalGroupManager"))->getBySystemName(name);
}
/*public*/ NamedBean* SGBeanTableDataModel::getByUserName(QString name) {
    return ((SignalGroupManager*)InstanceManager::getNullableDefault("SignalGroupManager"))->getByUserName(name);
}

/*public*/ int SGBeanTableDataModel::getDisplayDeleteMsg() { return 0x00;/*return InstanceManager.getDefault(jmri.UserPreferencesManager.class).getWarnDeleteSignalGroup();*/ }
/*public*/ void SGBeanTableDataModel::setDisplayDeleteMsg(int /*boo*/) { /*InstanceManager.getDefault(jmri.UserPreferencesManager.class).setWarnDeleteSignalGroup(boo); */}
/*protected*/ QString SGBeanTableDataModel::getMasterClassName() { return act->getClassName(); }

/*public*/ void SGBeanTableDataModel::clickOn(NamedBean* /*t*/) {
   //((SignalGroup)t).setSignalGroup();
}
/*public*/ QString SGBeanTableDataModel::getValue(QString /*s*/) const{
    return "Set";
}
/*public*/ QPushButton* SGBeanTableDataModel::configureButton() {
    return new QPushButton(" Set ");
}

/*protected*/ QString SGBeanTableDataModel::getBeanType(){
    return "Signal Group";
}



/*protected*/ void SignalGroupTableAction::setTitle() {
    f->setTitle("Signal Group Table");
}

/*protected*/ QString SignalGroupTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SignalGroupTable";
}

int SignalGroupTableAction::signalStateFromBox(QComboBox* box) {
    QString mode = box->currentText();
    int result = StringUtil::getStateFromName(mode, signalStatesValues, signalStates);

    if (result<0) {
        log->warn("unexpected mode string in sensorMode: "+mode);
        throw new IllegalArgumentException();
    }
    return result;
}

void SignalGroupTableAction::setSignalStateBox(int mode, QComboBox* box) {
    QString result = StringUtil::getNameFromState(mode, signalStatesValues, signalStates.toList());
    box->setCurrentIndex(box->findText(result));
}


/*protected*/ void SignalGroupTableAction::addPressed(ActionEvent* /*e*/)
{
    /*if (editMode) {
        cancelEdit();
    }*/

 TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
 QStringList systemNameList = ((ProxyTurnoutManager*)tm)->getSystemNameList();
 _mastAppearancesList = QList <SignalMastAspect*>();

 SignalHeadManager* shm = static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
 systemNameList = ((AbstractSignalHeadManager*)shm)->getSystemNameList();
 _signalList = QList <SignalGroupSignal*> (/*systemNameList.size()*/);

 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  if (QString(((AbstractSignalHeadManager*)shm)->getBySystemName(systemName)->metaObject()->className()).contains("SingleTurnoutSignalHead"))
  {
   QString userName = ((AbstractSignalHeadManager*)shm)->getBySystemName(systemName)->getUserName();
   _signalList.append(new SignalGroupSignal(systemName, userName));
  }
  else log->debug ("Signal Head " + systemName + " is not a single Turnout Controlled Signal Head");
 }

 // Set up window
 if (addFrame==NULL)
 {
  mainSignal = new JmriBeanComboBox((Manager*)InstanceManager::getDefault("SignalMastManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
  mainSignal->setFirstItemBlank(true);
  addFrame = new JmriJFrameX("Add/Edit SignalGroup", false, true);
  addFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalGroupAddEdit", true);
  addFrame->setLocation(100,30);
  addFrame->resize(400,700);
  QVBoxLayout* contentPaneLayout;
  if(addFrame->getContentPane()->layout() == NULL)
  {
   addFrame->getContentPane()->setLayout(contentPaneLayout = new QVBoxLayout(addFrame->getContentPane()/*, BoxLayout.Y_AXIS*/));
  }
  else contentPaneLayout = (QVBoxLayout*)addFrame->getContentPane()->layout();
  QWidget* contentPane = addFrame->getContentPane();
  contentPane->setObjectName("signalgrouptableactioncontent");
  // add system name
  //QWidget* ps = new QWidget();
  FlowLayout* psFlowLayout = new FlowLayout;
  //ps->setLayout(psFlowLayout);
  psFlowLayout->addWidget(nameLabel);
  psFlowLayout->addWidget(_systemName);
  _systemName->setToolTip("Enter system name for new SignalGroup, e.g. R12.");
  psFlowLayout->addWidget(fixedSystemName);
  fixedSystemName->setVisible(false);
  //contentPaneLayout->addWidget(ps);
  contentPaneLayout->addLayout(psFlowLayout);
  // add user name
  //QWidget* p = new QWidget();
  FlowLayout* pFlowLayout = new FlowLayout;
  //p->setLayout(pFlowLayout);
  pFlowLayout->addWidget(userLabel);
  pFlowLayout->addWidget(_userName);
  _userName->setToolTip("Enter user name for new SignalGroup, e.g. Junction Indicator on Signal 1.");

  //contentPaneLayout->addWidget(p);
  contentPaneLayout->addLayout(pFlowLayout);
  // add Turnout Display Choice
  //QWidget* py = new QWidget();
  FlowLayout* pyFlowLayout = new FlowLayout;
  //py->setLayout(new FlowLayout);
  pyFlowLayout->addWidget(new QLabel("Show "));
  selGroup = new QButtonGroup();
  allButton = new QRadioButton("All"/*,true*/);
  allButton->setChecked(true);
  selGroup->addButton(allButton);
  pyFlowLayout->addWidget(allButton);
//    allButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                if (!showAll) {
//                    showAll = true;
//                      _SignalGroupSignalModel.fireTableDataChanged();
//                      _AppearanceModel.fireTableDataChanged();
//                }
//            }
//        });
  connect(allButton, SIGNAL(clicked()), this, SLOT(on_allButton_clicked()));
  includedButton = new QRadioButton("Included"/*,false*/);
  selGroup->addButton(includedButton);
  pyFlowLayout->addWidget(includedButton);
//    includedButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of included Turnouts only, if needed
//                if (showAll) {
//                    showAll = false;
//                    initializeIncludedList();
//                    _SignalGroupSignalModel.fireTableDataChanged();
//                    _AppearanceModel.fireTableDataChanged();

//                }
//            }
//        });
  connect(includedButton, SIGNAL(clicked()), this, SLOT(on_includedButton_clicked()));
  pyFlowLayout->addWidget(new QLabel("  Mast Appearances and Signals"));
  //contentPaneLayout->addWidget(py);
  contentPaneLayout->addLayout(pyFlowLayout);

  // add control sensor table
  QFrame* p3 = new QFrame();
  p3->setFrameStyle(QFrame::StyledPanel);
  p3->setFrameShadow(QFrame::Raised);
  p3->setLineWidth(2);
  QVBoxLayout* p3VLayout = new QVBoxLayout;
  p3->setLayout(p3VLayout);
  QWidget* p31 = new QWidget();
  p31->setLayout(new FlowLayout);
  p31->layout()->addWidget(new QLabel("Enter the Signal Mast that this group is attached to"));
  p3VLayout->addWidget(p31);
  QWidget* p32 = new QWidget();
  p32->setLayout(new FlowLayout);
  p32->layout()->addWidget(new QLabel("Signal Mast: "));
  p32->layout()->addWidget(mainSignal);
  //p32.add(new QLabel("Appearance Logic"));
  //p32.add(mainSignalOperation);
//            mainSignal.setText("");
  p3VLayout->addWidget(p32);

  p3xsi = new QWidget();
  QHBoxLayout* p3xsiLayout;
  p3xsi->setLayout(p3xsiLayout = new QHBoxLayout);
  QWidget* p3xsiSpace = new QWidget();
  p3xsiSpace->setLayout(new QVBoxLayout(p3xsiSpace/*, BoxLayout.Y_AXIS*/));
  p3xsiSpace->layout()->addWidget(new QLabel(" "));
  p3xsi->layout()->addWidget(p3xsiSpace);

  //QWidget* p31si = new QWidget();
  QVBoxLayout* p31siLayout = new QVBoxLayout;
  //p31si->setLayout(new QVBoxLayout(p31si/*, BoxLayout.Y_AXIS*/));
  p31siLayout->addWidget(new QLabel(" Select the Mast "));
  p31siLayout->addWidget(new QLabel(" Appearances that"));
  p31siLayout->addWidget(new QLabel(" can trigger this"));
  p31siLayout->addWidget(new QLabel(" Group."));
  //p3xsi->layout()->addWidget(p31si);
  p3xsiLayout->addLayout(p31siLayout);
  _AppearanceModel = new ATSignalMastAppearanceModel(this);
  //JTable SignalAppearanceTable = JTableUtil.sortableDataModel(_AppearanceModel);
  QTableView* signalAppearanceTable = new QTableView();
  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(signalAppearanceTable->sizePolicy().hasWidthForHeight());
  signalAppearanceTable->setSizePolicy(sizePolicy);
  signalAppearanceTable->setModel(_AppearanceModel);
  signalAppearanceTable->resizeColumnsToContents();
  signalAppearanceTable->verticalHeader()->setVisible(false);
//    try {
//        TableSorter tmodel = ((jmri.util.com.sun.TableSorter)SignalAppearanceTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(SignalGroupTableAction.ATSignalMastAppearanceModel.APPEAR_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
//    SignalAppearanceTable.setRowSelectionAllowed(false);
//    SignalAppearanceTable.setPreferredScrollableViewportSize(QSize(200,80));
//    TableColumnModel SignalAppearanceColumnModel = SignalAppearanceTable.getColumnModel();
//    TableColumn includeColumnA = SignalAppearanceColumnModel.
//                                        getColumn(SignalGroupTableAction.ATSignalMastAppearanceModel.INCLUDE_COLUMN);
//    includeColumnA.setResizable(false);
//    includeColumnA.setMinWidth(30);
//    includeColumnA.setMaxWidth(60);
//    //@SuppressWarnings("static-access")
//    TableColumn sNameColumnA = SignalAppearanceColumnModel.
//                                        getColumn(_AppearanceModel.APPEAR_COLUMN);
//    sNameColumnA.setResizable(true);
//    sNameColumnA.setMinWidth(75);
//    sNameColumnA.setMaxWidth(140);

//    _SignalAppearanceScrollPane = new JScrollPane(SignalAppearanceTable);
  ((QVBoxLayout*)p3xsi->layout())->addWidget(signalAppearanceTable/*,BorderLayout.CENTER)*/,0,Qt::AlignCenter);
  p3VLayout->addWidget(p3xsi);
  p3xsi->setVisible(true);

//    mainSignal.addFocusListener(
//        new FocusListener() {
//        /*public*/ void focusGained(FocusEvent e){}
//        /*public*/ void focusLost(FocusEvent e) {
//            if(curSignalGroup==NULL)
//                setValidSignalAppearances();
//            else if (mainSignal.getSelectedBean()!=curSignalGroup.getSignalMast())
//                setValidSignalAppearances();
//        }
//    }
//    );
  connect(mainSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(On_mainSignal_currentIndexChanged()));
        // complete this panel
//        Border p3Border = BorderFactory.createEtchedBorder();
//        p3.setBorder(p3Border);
  contentPaneLayout->addWidget(p3);
    //contentPaneLayout->addLayout(p3VLayout);

  p2xsi = new QWidget();
  QHBoxLayout* p2xsiLayout = new QHBoxLayout;
  p2xsi->setLayout(p2xsiLayout);
  QWidget* p2xsiSpace = new QWidget();
  p2xsiSpace->setLayout(new QVBoxLayout(p2xsiSpace/*, BoxLayout.Y_AXIS*/));
  p2xsiSpace->layout()->addWidget(new QLabel("XXX"));
  p2xsiLayout->addWidget(p2xsiSpace);

//  QWidget* p21si = new QWidget();
//  p21si->setLayout(new QVBoxLayout(p21si/*, BoxLayout.Y_AXIS*/));
  QVBoxLayout* p21siLayout = new QVBoxLayout;
  p21siLayout->addWidget(new QLabel("Please select "));
  p21siLayout->addWidget(new QLabel(" Signals to "));
  p21siLayout->addWidget(new QLabel(" be included "));
  p21siLayout->addWidget(new QLabel(" in this Group."));
  //p2xsiLayout->addWidget(p21si);
  p2xsiLayout->addLayout(p21siLayout);
  _signalGroupSignalModel = new SignalGroupSignalHeadModel(this);
 //JTable SignalGroupSignalTable = jmri.util.JTableUtil.sortableDataModel(_SignalGroupSignalModel);
  QTableView* signalGroupSignalTable = new QTableView();
  signalGroupSignalTable->setModel(_signalGroupSignalModel);
  signalGroupSignalTable->resize(480,160);
  signalGroupSignalTable->setItemDelegateForColumn(SignalGroupSignalHeadModel::EDIT_COLUMN, new PushButtonDelegate());
//        try {
//            jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)SignalGroupSignalTable.getModel());
//            tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//            tmodel.setSortingStatus(SignalGroupSignalModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//        } catch (ClassCastException e3) {}  // if not a sortable table model
//        SignalGroupSignalTable.setRowSelectionAllowed(false);
//        SignalGroupSignalTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,160));
//        TableColumnModel SignalGroupSignalColumnModel = SignalGroupSignalTable.getColumnModel();
//        TableColumn includeColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.INCLUDE_COLUMN);
//        includeColumnSi.setResizable(false);
//        includeColumnSi.setMinWidth(30);
//        includeColumnSi.setMaxWidth(60);
//        TableColumn sNameColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.SNAME_COLUMN);
//        sNameColumnSi.setResizable(true);
//        sNameColumnSi.setMinWidth(75);
//        sNameColumnSi.setMaxWidth(95);
//        TableColumn uNameColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.UNAME_COLUMN);
//        uNameColumnSi.setResizable(true);
//        uNameColumnSi.setMinWidth(100);
//        uNameColumnSi.setMaxWidth(260);
//        TableColumn stateColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.STATE_ON_COLUMN);
//        stateColumnSi.setResizable(false);
//        stateColumnSi.setMinWidth(50);
//        stateColumnSi.setMaxWidth(100);

//        TableColumn stateOffColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.STATE_OFF_COLUMN);
//        stateOffColumnSi.setResizable(false);
//        stateOffColumnSi.setMinWidth(50);
//        stateOffColumnSi.setMaxWidth(100);
//        JButton editButton = new JButton("Edit");
//        TableColumn editColumnSi = SignalGroupSignalColumnModel.
//                                            getColumn(SignalGroupSignalModel.EDIT_COLUMN);
//        editColumnSi.setResizable(false);
//        editColumnSi.setMinWidth(50);
//        editColumnSi.setMaxWidth(100);
//        setColumnToHoldButton(SignalGroupSignalTable, SignalGroupSignalModel.EDIT_COLUMN, editButton);

//        _SignalGroupSignalScrollPane = new JScrollPane(SignalGroupSignalTable);
  ((QHBoxLayout*)p2xsiLayout)->addWidget(signalGroupSignalTable,0, Qt::AlignCenter);
  contentPaneLayout->addWidget(p2xsi);
  p2xsi->setVisible(true);


  // add notes panel
  QGroupBox* pa = new QGroupBox();
  pa->setLayout(new QVBoxLayout(pa/*, BoxLayout.Y_AXIS*/));

    //Border pBorder = BorderFactory.createEtchedBorder();
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
        //pa.setBorder(pBorder);
  pa->setStyleSheet(gbStyleSheet);
  contentPaneLayout->addWidget(pa);
  QWidget* pb = new QWidget();
  pb->setLayout(new FlowLayout());
  pb->layout()->addWidget(deleteButton);
//        deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deletePressed(e);
//            }
//        });
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
  deleteButton->setToolTip(tr("Delete the SignalGroup in System Name"));
        // Update SignalGroup button
  pb->layout()->addWidget(updateButton);
//        updateButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updatePressed(e, false, true);
//            }
//        });
  connect(updateButton, SIGNAL(clicked()), this, SLOT(on_updateButton_clicked()));
  updateButton->setToolTip("Change this SignalGroup and leave Edit mode");
  updateButton->setVisible(true);
  contentPaneLayout->addWidget(pb);
  // pack and release space
  addFrame->pack();
  p2xsiSpace->setVisible(false);
 }
    // set listener for window closing
 else
 {
  mainSignal->setSelectedBean(NULL);
 }
//    addFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                // remind to save, if SignalGroup was created or edited
//                if (SignalGroupDirty) {
//                    InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                        showInfoMessage("Reminder","Remember to save your SignalGroup information.","beantable.SignalGroupTableAction", "remindSignalGroup");
//                    SignalGroupDirty = false;
//                }
//                // hide addFrame
//                addFrame->setVisible(false);
//                finishUpdate();
//                _SignalGroupSignalModel.dispose();
//                _AppearanceModel.dispose();

//            }
//        });
    // display the window
 addFrame->setVisible(true);
}

void SignalGroupTableAction::setColumnToHoldButton(JTable* /*table*/, int /*column*/, QPushButton* /*sample*/) {
    //TableColumnModel tcm = table.getColumnModel();
    // install a button renderer & editor
//    ButtonRenderer buttonRenderer = new ButtonRenderer();
//    table.setDefaultRenderer(JButton.class,buttonRenderer);
//    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//    table.setDefaultEditor(JButton.class,buttonEditor);
//    // ensure the table rows, columns have enough room for buttons
//    table.setRowHeight(sample.getPreferredSize().height);
//    table.getColumnModel().getColumn(column)
//        .setPreferredWidth((sample.getPreferredSize().width)+4);
}

/**
 * Initialize list of included turnout positions
 */
void SignalGroupTableAction::initializeIncludedList()
{
 _includedMastAspectsList =  QList<SignalMastAspect*>();
 for (int i=0; i<_mastAppearancesList.size();i++)
 {
  if (_mastAppearancesList.at(i)->isIncluded())
  {
   _includedMastAspectsList.append(_mastAppearancesList.at(i));
  }

 }
 _includedSignalList =  QList <SignalGroupSignal*> ();
 for (int i=0; i<_signalList.size(); i++)
 {
  if (_signalList.at(i)->isIncluded())
  {
   _includedSignalList.append(_signalList.at(i));
  }
 }
}

bool SignalGroupTableAction::checkNewNamesOK() {
    // Get system name and user name
    QString sName = _systemName->text().toUpper();
    QString uName = _userName->text();
    if (sName.length()==0) {
//        javax.swing.JOptionPane.showMessageDialog(NULL,"System Name field can not be left blank","System Name Error",javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(NULL, tr("Warning"), tr("System Name field can not be left blank"));
        return false;
    }
    SignalGroup* g = NULL;
    // check if a SignalGroup with the same user name exists
    if (uName!=("")) {
        g = static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"))->getByUserName(uName);
        if (g!=NULL) {
            // SignalGroup with this user name already exists
//            javax.swing.JOptionPane.showMessageDialog(NULL,"Signal Group with this username already exists","User Name Error",javax.swing.JOptionPane.WARNING_MESSAGE);
            QMessageBox::warning(NULL, tr("Warning"), tr("Signal Group with this username already exists"));
             return false;
        }
        else {
            return true;
        }
    }
    // check if a SignalGroup with this system name already exists
    g = static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"))->getBySystemName(sName);
    if (g!=NULL) {
        // SignalGroup already exists
//        javax.swing.JOptionPane.showMessageDialog(NULL,"A SignalGroup with this system name already exists","System Name Error",javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(NULL, tr("Warning"), tr("A SignalGroup with this system name already exists"));
        return false;
    }
    return true;
}

bool SignalGroupTableAction::checkValidSignalMast()
{
 SignalMast* mMast = (SignalMast*) mainSignal->getSelectedBean();
 if (mMast == NULL)
 {
  log->warn("Signal Mast not selected");
//        javax.swing.JOptionPane.showMessageDialog(NULL,"SignalMast not selected.","Error",javax.swing.JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("Signal Mast not selected"));
  return false;
 }
 return true;
}

SignalGroup* SignalGroupTableAction::checkNamesOK() {
    // Get system name and user name
    QString sName = _systemName->text().toUpper();
    QString uName = _userName->text();
    if (sName.length()==0) {
//        javax.swing.JOptionPane.showMessageDialog(NULL,"Please enter a system name and user name.","Error",javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(NULL, tr("Warning"),tr("Please enter a system name and user name."));
        return NULL;
    }
    SignalGroup* g = ((DefaultSignalGroupManager*) static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager")))->provideSignalGroup(sName, uName);
    if (g==NULL) {
        // should never get here
        log->error("Unknown failure to create SignalGroup with System Name: "+sName);
    }
    return g;
}

int SignalGroupTableAction::setSignalInformation(SignalGroup* g) {
    for (int i=0; i<g->getNumSignalHeadItems(); i++) {
        SignalHead* sig = g->getSignalHeadItemBeanByIndex(i);
        bool valid = false;
        for (int x = 0; x<_includedSignalList.size(); x++) {
            SignalGroupSignal* s = _includedSignalList.at(x);
            //String si = s.getBean();
            if (sig==s->getBean()){
                valid = true;
                break;
            }
        }
        if (!valid){
            g->deleteSignalHead(sig);
        }
    }

    for (int i=0; i<_includedSignalList.size(); i++){
        SignalGroupSignal* s = _includedSignalList.at(i);
        SignalHead* sig = s->getBean();
        if (!g->isSignalIncluded(sig)){
            g->addSignalHead(sig);
            g->setSignalHeadOnState(sig, s->getOnStateInt());
            g->setSignalHeadOffState(sig, s->getOffStateInt());
        }
    }

    return _includedSignalList.size();
}

void SignalGroupTableAction::setMastAspectInformation(SignalGroup* g) {
    ((DefaultSignalGroup*)g)->clearSignalMastAspect();
    for (int x = 0; x<_includedMastAspectsList.size(); x++) {
        ((DefaultSignalGroup*)g)->addSignalMastAspect(_includedMastAspectsList.at(x)->getAspect());
    }
}

/**
 * Sets the Sensor, Turnout, and delay control information for adding or editting if any
 */
/*void setControlInformation(SignalGroup g) {
    // Get sensor control information if any
    //Not sure about this...
    String signalSystemName = mainSignal.getSelectedBean();
    if(
    if (signalSystemName.length() > 0) {
        SignalHead s1 = InstanceManager.signalHeadManagerInstance().getSignalHead(signalSystemName);
        if (s1!=NULL)
            g.setSignalMast(signalSystemName);
    }
}*/

void SignalGroupTableAction::setValidSignalAspects()
{
 SignalMast* sh = (SignalMast*) mainSignal->getSelectedBean();
 if (sh==NULL)
   return;
 QVector<QString> appear = sh->getValidAspects();

 _mastAppearancesList =  QList <SignalMastAspect*> (/*appear.size()*/);
 for(int i = 0; i<appear.size(); i++)
 {
  _mastAppearancesList.append(new SignalMastAspect(appear.at(i)));
 }
 _AppearanceModel->fireTableDataChanged();
}

/**
 * Responds to the Edit button
 */
void SignalGroupTableAction::editPressed(ActionEvent* /*e*/) {
    // identify the SignalGroup with this name if it already exists
    QString sName = _systemName->text().toUpper();
    SignalGroup* g = static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"))->getBySystemName(sName);
    if (g==NULL) {
        // SignalGroup does not exist, so cannot be edited
        return;
    }
    g->addPropertyChangeListener((PropertyChangeListener*)this);
    SignalGroupManager* mgr = static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"));
    connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));


    // SignalGroup was found, make its system name not changeable
    curSignalGroup = g;

    SignalMast* sh = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(((DefaultSignalGroup*)g)->getSignalMastName());
    QVector<QString> appear = sh->getValidAspects();

    _mastAppearancesList =  QList <SignalMastAspect*> (/*appear.size()*/);

    for(int i = 0; i<appear.size(); i++){
        _mastAppearancesList.append(new SignalMastAspect(appear.at(i)));
    }

    fixedSystemName->setText(sName);
    fixedSystemName->setVisible(true);
    _systemName->setVisible(false);
    //mainSignal.setText(g.getSignalMastName());
    mainSignal->setSelectedBean(g->getSignalMast());

    _userName->setText(g->getUserName());
    int setRow = 0;

     for (int i=_signalList.size()-1; i>=0; i--) {
        SignalGroupSignal* signal = _signalList.at(i);
        //String tSysName = signal.getSysName();
        SignalHead* sigBean = signal->getBean();
        if (g->isSignalIncluded(sigBean) ) {
            signal->setIncluded(true);
            signal->setOnState(g->getSignalHeadOnState(sigBean));
            signal->setOffState(g->getSignalHeadOffState(sigBean));
            setRow = i;
        } else {
            signal->setIncluded(false);
            //signal.setOnState(SignalHead::DARK);
            //signal.setOffState(SignalHead::DARK);
        }
    }
    //_SignalGroupSignalScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    _signalGroupSignalModel->fireTableDataChanged();

    for (int i=0; i<_mastAppearancesList.size(); i++){
        SignalMastAspect* appearance = _mastAppearancesList.at(i);
        QString app = appearance->getAspect();
        if (g->isSignalMastAspectIncluded(app)){
            appearance->setIncluded(true);
            setRow = i;
        } else {
            appearance->setIncluded(false);
        }

    }
//    _SignalAppearanceScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);

    _AppearanceModel->fireTableDataChanged();
    initializeIncludedList();

    updateButton->setVisible(true);
    fixedSystemName->setVisible(true);
    _systemName->setVisible(false);
    editMode = true;
}

/**
 * Responds to the Delete button
 */
void SignalGroupTableAction::deletePressed(ActionEvent* /*e*/) {
    static_cast<SignalGroupManager*>(InstanceManager::getDefault("SignalGroupManager"))->deleteSignalGroup(curSignalGroup);
    curSignalGroup = NULL;
    finishUpdate();
}

/**
 * Responds to the Update button - update to SignalGroup Table
 */
void SignalGroupTableAction::updatePressed(ActionEvent* /*e*/, bool newSignalGroup, bool close)
{
 // Check if the User Name has been changed
 if (curSignalGroup == NULL)
 {
  if (!checkNewNamesOK())
  {
   return;
  }
 }
 if (!checkValidSignalMast())
  return;
 QString uName = _userName->text();
 SignalGroup* g = checkNamesOK();
 if (g == NULL)
 {
  return;
 }
 curSignalGroup = g;
 // user name is unique, change it
 g->setUserName(uName);
    initializeIncludedList();
    setSignalInformation(g);
    setMastAspectInformation(g);

    ((DefaultSignalGroup*)g)->setSignalMast((SignalMast*)mainSignal->getSelectedBean(), mainSignal->getSelectedDisplayName());
    if(close)
        finishUpdate();
}

void SignalGroupTableAction::finishUpdate() {
    if(curSignalGroup!=NULL)
        curSignalGroup->removePropertyChangeListener((PropertyChangeListener*)this);
    _systemName->setVisible(true);
    fixedSystemName->setVisible(false);
    _systemName->setText("");
    _userName->setText("");
    mainSignal->setSelectedBean(NULL);
    for (int i=_signalList.size()-1; i>=0; i--) {
        _signalList.at(i)->setIncluded(false);
    }
    for (int i=_mastAppearancesList.size()-1; i>=0; i--) {
        _mastAppearancesList.at(i)->setIncluded(false);
    }
   // mainSignal.setText("");
    curSignalGroup=NULL;
    addFrame->setVisible(false);

}
#if 1
///*public*/ class ATSignalMastAppearanceModel extends AbstractTableModel implements PropertyChangeListener
//{
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == INCLUDE_COLUMN) {
//            return Boolean.class;
//        }
//        else {
//            return String.class;
//        }
//    }
ATSignalMastAppearanceModel::ATSignalMastAppearanceModel(SignalGroupTableAction *act)
{
 this->act = act;
}

/*public*/ QVariant ATSignalMastAppearanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
  if (col==INCLUDE_COLUMN) return tr("Include");
  if (col==APPEAR_COLUMN) return tr("Mast Appearance");
 }
 //return AbstractTableModel::headerData(section,orientation, role);
 return QVariant();
}

    /*public*/ void ATSignalMastAppearanceModel::dispose()
{
 static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->removePropertyChangeListener((PropertyChangeListener*)this);
}

/*public*/ void ATSignalMastAppearanceModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  // a new NamedBean is available in the manager
  fireTableDataChanged();
 }
}


/*public*/ int ATSignalMastAppearanceModel::columnCount(const QModelIndex &/*parent*/) const{return 2;}

/*public*/ Qt::ItemFlags ATSignalMastAppearanceModel::flags(const QModelIndex &index) const
{
 //return ( (c==INCLUDE_COLUMN) );
    if(index.column() == INCLUDE_COLUMN)
     return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
 return QAbstractTableModel::flags(index);
}

/*public*/ void ATSignalMastAppearanceModel::setSetToState(QString /*x*/){}

/*public*/ int ATSignalMastAppearanceModel::rowCount(const QModelIndex &/*parent*/) const
{
        if (act->_mastAppearancesList.isEmpty())
            return 0;
        if (act->showAll)
            return act->_mastAppearancesList.size();
        else
            return act->_includedMastAspectsList.size();
    }

/*public*/ QVariant  ATSignalMastAppearanceModel::data (const QModelIndex &index, int role) const
{
 int r = index.row();
 int c = index.column();
 if(role == Qt::DisplayRole)
 {
  QList <SignalGroupTableAction::SignalMastAspect*> appearList = QList <SignalGroupTableAction::SignalMastAspect*>();
  if (act->showAll)
  {
   appearList = act->_mastAppearancesList;
  }
  else
  {
   appearList = act->_includedMastAspectsList;
  }
  // some error checking
  if (r >= appearList.size())
  {
   act->log->debug("row is greater than turnout list size");
   return QVariant();
  }
  switch (c)
  {
//            case INCLUDE_COLUMN:
//                return Boolean.valueOf(appearList.get(r).isIncluded());
   case APPEAR_COLUMN:  // slot number
     return appearList.at(r)->getAspect();
    default:
      return QVariant();
  }
 }
 if(role == Qt::CheckStateRole)
 {
  QList <SignalGroupTableAction::SignalMastAspect*> appearList = QList <SignalGroupTableAction::SignalMastAspect*>();
  if (act->showAll)
  {
   appearList = act->_mastAppearancesList;
  }
  else
  {
   appearList = act->_includedMastAspectsList;
  }
  if(c == INCLUDE_COLUMN)
  {
   if (appearList.at(r)->isIncluded())
    return  Qt::Checked;
   else
    return Qt::Unchecked;
  }
 }
 return QVariant();
}

/*public*/ bool ATSignalMastAppearanceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int r = index.row();
 int c = index.column();

 QList <SignalGroupTableAction::SignalMastAspect*> appearList = QList <SignalGroupTableAction::SignalMastAspect*>();
  if (act->showAll)
  {
   appearList = act->_mastAppearancesList;
  }
  else
  {
   appearList = act->_includedMastAspectsList;
  }
  switch (c)
  {
   case INCLUDE_COLUMN:
    if(role == Qt::CheckStateRole)
    {
     appearList.at(r)->setIncluded(value.toBool());
     return true;
    }
    break;
   case APPEAR_COLUMN:
    if(role == Qt::EditRole)
    {
     appearList.at(r)->setAspect(value.toString());
    break;
   default: break;
  }
 }
 return false;
}
// };
#endif
/**
 * Base table model for selecting outputs
 */
// /*public*/ abstract class SignalGroupOutputModel extends AbstractTableModel implements PropertyChangeListener
//{
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == INCLUDE_COLUMN) {
//            return Boolean.class;
//        }
//        else {
//            return String.class;
//        }
//    }
SignalGroupOutputModel::SignalGroupOutputModel(SignalGroupTableAction *act)
{
this->act = act;
}

/*public*/ void SignalGroupOutputModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new NamedBean is available in the manager
        fireTableDataChanged();
    } else if(e->getPropertyName()==("UpdateCondition")){
        fireTableDataChanged();
    }
}

    /*public*/ QVariant SignalGroupOutputModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
      if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
       return SignalGroupTableAction::COLUMN_NAMES.at(section);
      return QVariant();
  }

  /*public*/ int SignalGroupOutputModel::columnCount(const QModelIndex &/*parent*/) const{return 4;}

  /*public*/ Qt::ItemFlags SignalGroupOutputModel::flags(const QModelIndex &index) const
  {
   //return ( (c==INCLUDE_COLUMN) || (c==STATE_COLUMN) );

   if(index.column() == INCLUDE_COLUMN)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
   if(index.column() == STATE_COLUMN)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
//};

//class SignalGroupSignalModel extends SignalGroupOutputModel
//{
SignalGroupSignalHeadModel::SignalGroupSignalHeadModel(SignalGroupTableAction *act) : SignalGroupOutputModel(act)
{
 static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->addPropertyChangeListener((PropertyChangeListener*)this);
 AbstractSignalHeadManager* mgr = (AbstractSignalHeadManager*)static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
 connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 editMapper = new QSignalMapper;
}

/*public*/ Qt::ItemFlags SignalGroupSignalHeadModel::flags(const QModelIndex &index) const
{
 //return ( (c==INCLUDE_COLUMN) || (c==STATE_ON_COLUMN) || (c==STATE_OFF_COLUMN) || (c==EDIT_COLUMN));
 switch(index.column())
 {
  case INCLUDE_COLUMN:
   return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
  case STATE_ON_COLUMN:
  case STATE_OFF_COLUMN:
  case EDIT_COLUMN:
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
  default:
   break;
  }
 return SignalGroupOutputModel::flags(index);
}

/*public*/ int SignalGroupSignalHeadModel::columnCount(const QModelIndex &/*parent*/) const {return 6;}


//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == INCLUDE_COLUMN) {
//            return Boolean.class;
//        } else if ( c == EDIT_COLUMN) {
//            return JButton.class;
//        }
//        else {
//            return String.class;
//        }
//    }

    /*public*/ QVariant SignalGroupSignalHeadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(Qt::DisplayRole == role && orientation == Qt::Horizontal)
    return SignalGroupTableAction::COLUMN_SIG_NAMES[section];
 return QVariant();
}

/*public*/ void SignalGroupSignalHeadModel::setSetToState(QString /*x*/){}

/*public*/ int SignalGroupSignalHeadModel::rowCount(const QModelIndex &/*parent*/) const
{
 if (act->showAll)
  return act->_signalList.size();
 else
  return act->_includedSignalList.size();
 }

/*public*/ QVariant SignalGroupSignalHeadModel::data(const QModelIndex &index, int role) const
{
    QList <SignalGroupTableAction::SignalGroupSignal*> signalList = QList <SignalGroupTableAction::SignalGroupSignal*>();
 int c = index.column();
 int r =index.row();
 if (act->showAll)
 {
  signalList = act->_signalList;
 }
 else
 {
  signalList = act->_includedSignalList;
 }
 // some error checking
 if (r >= signalList.size())
 {
  act->log->debug("row is greater than turnout list size");
  return QVariant();
 }
 if(role == Qt::DisplayRole)
 {
  switch (c)
  {
// case INCLUDE_COLUMN:
//    return Boolean.valueOf(signalList.get(r).isIncluded());
  case SNAME_COLUMN:  // slot number
    return signalList.at(r)->getSysName();
  case UNAME_COLUMN:  //
    return signalList.at(r)->getUserName();
  case STATE_ON_COLUMN:  //
    return signalList.at(r)->getOnState();
  case STATE_OFF_COLUMN:  //
    return signalList.at(r)->getOffState();
  case EDIT_COLUMN:
    return ("edit");
  default:
   return QVariant();
  }
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
  {
   if(signalList.at(r)->isIncluded())
    return Qt::Checked;
    else
   return Qt::Unchecked;
  }
 }
 return QVariant();
}

/*public*/ QString SignalGroupSignalHeadModel::getDisplayName(int r)
{
 if ((data(index(r, UNAME_COLUMN),Qt::DisplayRole).toString()!="")&&(!( data(index(r, UNAME_COLUMN),Qt::DisplayRole).toString()==(""))))
 {
  return data(index(r, UNAME_COLUMN),Qt::DisplayRole).toString();
 }
 else
 {
  return data(index(r, SNAME_COLUMN),Qt::DisplayRole).toString();
 }
}

/*public*/ SignalHead* SignalGroupSignalHeadModel::getBean(int r)
{
        return static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(data(index(r, SNAME_COLUMN),Qt::DisplayRole).toString());
    }

/*public*/ bool  SignalGroupSignalHeadModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 QList <SignalGroupTableAction::SignalGroupSignal*> signalList = QList <SignalGroupTableAction::SignalGroupSignal*>();
 int r = index.row();
 if (act->showAll)
 {
  signalList = act->_signalList;
  }
  else
  {
   signalList = act->_includedSignalList;
  }
 if(role == Qt::CheckStateRole)
 {
  if(index.column() == INCLUDE_COLUMN)
  {
   signalList.at(r)->setIncluded(value.toBool());
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  switch (index.column())
 {
//            case INCLUDE_COLUMN:
//                signalList.get(r).setIncluded(((Boolean)type).boolValue());
//                break;
    case STATE_ON_COLUMN:
        signalList.at(r)->setSetOnState(value.toString());
        break;
    case STATE_OFF_COLUMN:
        signalList.at(r)->setSetOffState(value.toString());
        break;
    case EDIT_COLUMN:
        signalList.at(r)->setIncluded(true);
//        class WindowMaker implements Runnable {
//        final int row;
//        WindowMaker(int r){
//            row = r;
//        }
//        /*public*/ void run() {
//                //Thread.yield();
        act->signalEditPressed(index.row());
//                //_systemName.setText((String)getValueAt(row, SYSNAMECOL));
//                //editPressed(NULL);
//            }
//        };
//        WindowMaker t = new WindowMaker(r);
//        javax.swing.SwingUtilities.invokeLater(t);
        break;
    default: break;
   }
  return true;
  }
 return false;
}
    /*public*/ void SignalGroupSignalHeadModel::dispose() {
        static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->removePropertyChangeListener((PropertyChangeListener*)this);
    }
//};


void SignalGroupTableAction::signalEditPressed(int row)
{
 if(curSignalGroup==NULL)
 {
  if (!checkNewNamesOK())
  {
   return;
  }
  if (!checkValidSignalMast())
   return;
  updatePressed(NULL, true, false);
 }
 if(!((DefaultSignalGroup*)curSignalGroup)->isSignalIncluded(_signalGroupSignalModel->getBean(row)))
 {
  ((DefaultSignalGroup*)curSignalGroup)->addSignalHead( _signalGroupSignalModel->getBean(row));
 }
 _signalGroupSignalModel->fireTableDataChanged();
 SignalGroupSubTableAction* editSignalHead = new SignalGroupSubTableAction();
 editSignalHead->editSignal(curSignalGroup, _signalGroupSignalModel->getDisplayName(row));
}


///*private*/ /*static*/ class SignalGroupSignal
//{

//    //String _sysName=NULL;
//    //String _userName=NULL;
//    SignalHead _signal = NULL;
//    bool _included;

SignalGroupTableAction::SignalGroupSignal::SignalGroupSignal(QString sysName, QString /*userName*/)
{
        /*_sysName = sysName;
        _userName = userName;*/
 _signal = NULL;
 _included = false;
 _onState = 0x00;
 _offState = 0x00;

 SignalHead* head = (SignalHead*)((AbstractSignalHeadManager*)static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")))->getBySystemName(sysName);
 if (QString(head->metaObject()->className()).contains("SingleTurnoutSignalHead"))
 {
  SingleTurnoutSignalHead* signal = (SingleTurnoutSignalHead*) static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(sysName);
  _onState = signal->getOnAppearance();
  _offState = signal->getOffAppearance();
  _signal = (SignalHead*)signal;
 }
}

    SignalHead* SignalGroupTableAction::SignalGroupSignal::getBean(){
        return _signal;
    }

    QString SignalGroupTableAction::SignalGroupSignal::getSysName() {
        return _signal->getSystemName();
    }
    QString SignalGroupTableAction::SignalGroupSignal::getUserName() {
        return _signal->getUserName();
    }

    /*String getDisplayName(){
        return _signal.getDisplayName();
    }*/

    bool SignalGroupTableAction::SignalGroupSignal::isIncluded() {
        return _included;
    }
    void SignalGroupTableAction::SignalGroupSignal::setIncluded(bool include) {
        _included = include;
    }

    QString SignalGroupTableAction::SignalGroupSignal::getOnState() {
        switch (_onState) {
            case SignalHead::DARK:
                return tr("Dark");
            case SignalHead::RED:
                return tr("Red");
            case SignalHead::YELLOW:
                return tr("Yellow");
            case SignalHead::GREEN:
                return tr("Green");
            case SignalHead::LUNAR:
                return tr("Lunar");
            case SignalHead::FLASHRED:
                return tr("Flashing Red");
            case SignalHead::FLASHYELLOW:
                return tr("Flashing Yellow");
            case SignalHead::FLASHGREEN:
                return tr("Flashing Green");
            case SignalHead::FLASHLUNAR:
                return tr("Flashing Lunar");
        }
        return "";
    }
    QString SignalGroupTableAction::SignalGroupSignal::getOffState() {
        switch (_offState) {
            case SignalHead::DARK:
                return tr("Dark");
            case SignalHead::RED:
                return tr("Red");
            case SignalHead::YELLOW:
                return tr("Yellow");
            case SignalHead::GREEN:
                return tr("Green");
            case SignalHead::LUNAR:
                return tr("Lunar");
            case SignalHead::FLASHRED:
                return tr("Flashing Red");
            case SignalHead::FLASHYELLOW:
                return tr("Flashing Yellow");
            case SignalHead::FLASHGREEN:
                return tr("Flashing Green");
            case SignalHead::FLASHLUNAR:
                return tr("Flashing Lunar");
        }
        return "";
    }

    int SignalGroupTableAction::SignalGroupSignal::getOnStateInt(){ return _onState;}
    int SignalGroupTableAction::SignalGroupSignal::getOffStateInt(){ return _offState;}

    void SignalGroupTableAction::SignalGroupSignal::setSetOnState(QString state) {
        if (state==(tr("Dark"))) {
            _onState = SignalHead::DARK;
        } else if (state==(tr("Red"))) {
            _onState = SignalHead::RED;
        } else if (state==(tr("Yellow"))) {
            _onState = SignalHead::YELLOW;
        } else if (state==(tr("Green"))) {
            _onState = SignalHead::GREEN;
        } else if (state==(tr("Lunar"))) {
            _onState = SignalHead::LUNAR;
        } else if (state==(tr("Flashing Red"))) {
            _onState = SignalHead::FLASHRED;
        } else if (state==(tr("Flashing Yellow"))) {
            _onState = SignalHead::FLASHYELLOW;
        } else if (state==(tr("Flashing Green"))) {
            _onState = SignalHead::FLASHGREEN;
        } else if (state==(tr("Flashing Lunar"))) {
            _onState = SignalHead::FLASHLUNAR;
        }
    }

    void SignalGroupTableAction::SignalGroupSignal::setSetOffState(QString state) {
        if (state==(tr("Dark"))) {
            _offState = SignalHead::DARK;
        } else if (state==(tr("Red"))) {
            _offState = SignalHead::RED;
        } else if (state==(tr("Yellow"))) {
            _offState = SignalHead::YELLOW;
        } else if (state==(tr("Green"))) {
            _offState = SignalHead::GREEN;
        } else if (state==(tr("Lunar"))) {
            _offState = SignalHead::LUNAR;
        } else if (state==(tr("Flashing Red"))) {
            _offState = SignalHead::FLASHRED;
        } else if (state==(tr("Flashing Yellow"))) {
            _offState = SignalHead::FLASHYELLOW;
        } else if (state==(tr("Flashing Green"))) {
            _offState = SignalHead::FLASHGREEN;
        } else if (state==(tr("Flashing Lunar"))) {
            _offState = SignalHead::FLASHLUNAR;
        }
    }


    /*public*/ void SignalGroupTableAction::SignalGroupSignal::setOnState(int state){
        _onState = state;
    }
    /*public*/ void SignalGroupTableAction::SignalGroupSignal::setOffState(int state){
        _offState = state;
    }
//};

///*private*/ /*static*/ class SignalMastAppearances
//    {
     SignalGroupTableAction::SignalMastAspect::SignalMastAspect(QString aspect){
        _aspect=aspect;
    }

    void SignalGroupTableAction::SignalMastAspect::setIncluded(bool include) {
        _include = include;
    }

    bool SignalGroupTableAction::SignalMastAspect::isIncluded() {
        return _include;
    }

    void SignalGroupTableAction::SignalMastAspect::setAspect(QString app){
        _aspect = app;
    }

    QString SignalGroupTableAction::SignalMastAspect::getAspect(){
        return _aspect;
    }

//};

    /*protected*/ QString SignalGroupTableAction::getClassName() { return "jmri.jmrit.beantable.SignalGroupTableAction"; }

/*public*/ QString SignalGroupTableAction::getClassDescription() { return tr("Signal Group Table"); }

/*public*/ void SignalGroupTableAction::on_allButton_clicked(ActionEvent* /*e*/) {
    // Setup for display of all Turnouts, if needed
    if (!showAll) {
        showAll = true;
          _signalGroupSignalModel->fireTableDataChanged();
          _AppearanceModel->fireTableDataChanged();
    }
}
/*public*/ void SignalGroupTableAction::on_includedButton_clicked(ActionEvent* /*e*/)
{
 // Setup for display of included Turnouts only, if needed
 if (showAll)
 {
    showAll = false;
    initializeIncludedList();
    _signalGroupSignalModel->fireTableDataChanged();
    _AppearanceModel->fireTableDataChanged();
 }
}
void SignalGroupTableAction::on_updateButton_clicked()
{
    updatePressed(NULL, false, true);
}
SGBeanTableDataModel* SignalGroupTableAction::model() {return (SGBeanTableDataModel*) m;}
void SignalGroupTableAction::On_mainSignal_currentIndexChanged()
{
 if(curSignalGroup==NULL)
   setValidSignalAspects();
 else if (mainSignal->getSelectedBean()!=curSignalGroup->getSignalMast())
   setValidSignalAspects();
}
