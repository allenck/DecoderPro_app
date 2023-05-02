#include "turnouttableaction.h"
#include "turnoutmanager.h"
#include "turnout.h"
#include "instancemanager.h"
#include  "jcombobox.h"
#include "signalspeedmap.h"
#include "userpreferencesmanager.h"
#include "../LayoutEditor/beantableframe.h"
#include "jtextfield.h"
#include <QLabel>
#include "jmrijframe.h"
#include <QBoxLayout>
#include "connectionnamefromsystemname.h"
#include "joptionpane.h"
#include <QCheckBox>
#include "addnewhardwaredevicepanel.h"
#include <QPushButton>
#include "runnable.h"
#include "jtable.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QSignalMapper>
#include <QMenu>
#include <QMenuBar>
#include "turnoutoperationframe.h"
#include "abstracttabletabaction.h"
#include "jmrijframe.h"
#include "lnturnoutmanager.h"
#include "abstractsensor.h"
#include "turnoutoperationconfig.h"
#include "inputdialog.h"
#include "xtablecolumnmodel.h"
#include "turnouteditaction.h"
#include "systemnamecomparator.h"
#include <QSpinBox>
#include "colorutil.h"
#include "proxymanager.h"
#include "proxylightmanager.h"
#include "vptr.h"
#include "systemconnectionmemomanager.h"
#include "guilafpreferencesmanager.h"
#include "bufferedimage.h"
#include "imageio.h"
#include <QPixmap>
#include "file.h"
#include "fileutil.h"
#include "namedbeancombobox.h"
#include "sensortabledatamodel.h"
#include "loggerfactory.h"
#include <QHeaderView>
#include "systemnamevalidator.h"
#include "turnouttabledatamodel.h"
#include "jmriexception.h"

TurnoutTableAction::TurnoutTableAction(QObject *parent) :
    AbstractTableAction("Turnout Table", parent)
{
 common();
}
/**
 * Swing action to create and register a
 * TurnoutTable GUI.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2004, 2007
 * @version     $Revision: 28161 $
 */

// /*public*/ class TurnoutTableAction extends AbstractTableAction {

/**
 *
 */
///*private*/ static /*final*/ long serialVersionUID = -8221584673872246104L;

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param actionName
 */
/*public*/ TurnoutTableAction::TurnoutTableAction(QString actionName, QObject *parent)
    : AbstractTableAction(actionName, parent)
{
 //super(actionName);
 common();
}

// /*public*/ TurnoutTableAction() { this("Turnout Table");}

void TurnoutTableAction::common()
{
 setObjectName("TurnoutTableAction");
// useBlockSpeed = "Use Block Speed";
// bothText = "Both";
// cabOnlyText = "Cab only";
// pushbutText = "Pushbutton only";
// noneText = "None";
// lockOperations = QStringList();
// lockOperations  << bothText << cabOnlyText << pushbutText<< noneText;
// speedListClosed =  QVector<QString>();
// speedListThrown =  QVector<QString>();
 noWarn = false;
 if(parent() == NULL)
  return;

 addFrame = NULL;
 userNameTextField = new JTextField(40);
 hardwareAddressTextField = new JTextField(20);
 statusBarLabel = new JLabel(tr("Enter a Hardware Address and (optional) User Name."));
 sysNameLabel = new QLabel("Hardware Address");
 userNameLabel = new QLabel(tr("User Name"));
 systemSelectionCombo = this->getName()+".SystemSelected";
 userNameError = this->getName()+".DuplicateUserName";

// showFeedbackBox = new QCheckBox("Show feedback information");
 //showFeedbackBox->setObjectName("showFeedbackBox");
// showLockBox = new QCheckBox("Show lock information");
// showTurnoutSpeedBox = new QCheckBox("Show Turnout Speed Details");
// doAutomationBox = new QCheckBox("Automatic retry");
 connectionChoice = "";

 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 // disable ourself if there is no primary turnout manager available
 if (turnoutManager==NULL) {
     setEnabled(false);
 }
// const char s[] = "Turnout\0";
// InstanceManager::myclass<Turnout*, s> test;

 //This following must contain the word Global for a correct match in the abstract turnout
// if(qobject_cast<ProxyTurnoutManager*>(turnoutManager)!=NULL)
// {
//  defaultThrownSpeedText = ("Use Global " + ((ProxyTurnoutManager*)turnoutManager)->getDefaultThrownSpeed());
//  defaultClosedSpeedText = ("Use Global " + ((ProxyTurnoutManager*)turnoutManager)->getDefaultClosedSpeed());
// }
// else
// {
//  defaultThrownSpeedText = ("Use Global " + turnoutManager->getDefaultThrownSpeed());
//  defaultClosedSpeedText = ("Use Global " + turnoutManager->getDefaultClosedSpeed());
// }
 //This following must contain the word Block for a correct match in the abstract turnout
// useBlockSpeed = "Use Block Speed";

// speedListClosed.append(defaultClosedSpeedText);
// speedListThrown.append(defaultThrownSpeedText);
// speedListClosed.append(useBlockSpeed);
// speedListThrown.append(useBlockSpeed);
// QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
// for(int i = 0; i<_speedMap.size(); i++)
// {
//  if (!speedListClosed.contains(_speedMap.at(i)))
//  {
//   speedListClosed.append(_speedMap.at(i));
//  }
//  if (!speedListThrown.contains(_speedMap.at(i)))
//  {
//   speedListThrown.append(_speedMap.at(i));
//  }
// }

}

//@Override
/*public*/ void TurnoutTableAction::setManager(Manager* man)
{
// log->debug(tr("setting manager of TTAction %1 to %2").arg(this->objectName(),man->self()->metaObject->classname()));
 turnoutManager = qobject_cast<TurnoutManager*>(man->mself());
 if (m!=nullptr){ // also update Table Model
     m->setManager(man);
 }
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Turnouts
 */
/*protected*/ void TurnoutTableAction::createModel()
{
 m = new TurnoutTableDataModel(turnoutManager);
}

/*protected*/ void TurnoutTableAction::setTitle() {
    f->setTitle(tr("Turnout Table"));
}

//@Override
/*protected*/ QString TurnoutTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TurnoutTable";
}

/*protected*/ void TurnoutTableAction::addPressed(JActionEvent */*e*/)
{
 //p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

 if (addFrame==NULL)
 {
  addFrame = new JmriJFrameX(tr("Add Turnout"), false, true);
  addFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  addFrame->addHelpMenu("package.jmri.jmrit.beantable.TurnoutAddEdit", true);
  QWidget* centralWidget = new QWidget;
  centralWidget->resize(600,300);
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  addFrame->setCentralWidget(centralWidget);

//        ActionListener listener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    okPressed(e);
//                }
//            };
  OkListener* listener = new OkListener(this);
  ToCancelActionListener* cancelListener = new ToCancelActionListener(this);

//        ActionListener rangeListener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    canAddRange(e);
//                }
//            };
  RangeListener* rangeListener = new RangeListener(this);

  /* We use the proxy manager in this instance so that we can deal with
  duplicate usernames in multiple classes */
  configureManagerComboBox(prefixBox, turnoutManager, "TurnoutManager");
  userNameTextField->setName("userNameTextField"); // NOI18N
  prefixBox->setObjectName("prefixBox"); // NOI18N
  // set up validation, zero text = false
  addButton = new JButton(tr("Create"));
  //addButton->addActionListener(createListener);
  connect(addButton, &QPushButton::clicked, [=]{createPressed();});
  // create panel

  if (hardwareAddressValidator==nullptr){
      hardwareAddressValidator = new SystemNameValidator(hardwareAddressTextField, /*Objects.requireNonNull*/(prefixBox->getSelectedItem()), true);
  } else {
      hardwareAddressValidator->setManager(prefixBox->getSelectedItem());
  }

  centralWidget->layout()->addWidget(new AddNewHardwareDevicePanel(hardwareAddressTextField, hardwareAddressValidator, userNameTextField, prefixBox,
          numberToAddSpinner, rangeBox, addButton, cancelListener, rangeListener, statusBarLabel));
  // tooltip for hardwareAddressTextField will be assigned next by canAddRange()
  canAddRange(nullptr);
 }
 hardwareAddressTextField->setName("hwAddressTextField"); // for GUI test NOI18N
 addButton->setName("createButton"); // for GUI test NOI18N
 // reset statusBarLabel text
 statusBarLabel->setText(tr("Enter a Hardware Address and (optional) User Name."));
 statusBarLabel->setForeground(Qt::gray);

 addFrame->pack();
 addFrame->setVisible(true);
}

/*public*/ void TurnoutTableAction::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
 QString property = propertyChangeEvent->getPropertyName();
 if ("background"==(property))
 {
  if ( propertyChangeEvent->getNewValue().value<QColor>() == QColor(Qt::white)) { // valid entry
      addButton->setEnabled(true);
  } else { // invalid
      addButton->setEnabled(false);
  }
 }
}


OkListener::OkListener(TurnoutTableAction *tta)
{
 this->tta = tta;
}
void OkListener::actionPerformed(JActionEvent */*e*/)
{
 tta->createPressed();
}
ToCancelActionListener::ToCancelActionListener(TurnoutTableAction *tta) { this->tta = tta;}
void ToCancelActionListener::actionPerformed(JActionEvent */*e*/ )
{
 tta->cancelPressed();
}

RangeListener::RangeListener(TurnoutTableAction *tta)
{
 this->tta = tta;
}
void RangeListener::actionPerformed(JActionEvent */*e*/)
{
 tta->canAddRange();
}


/**
 * Add the content and make the appropriate selection to a combox box for a turnout's
 * automation choices
 * @param t	turnout
 * @param cb	the JComboBox
 */
/*public*/ /*static*/ void TurnoutTableAction::updateAutomationBox(Turnout* t, JComboBox* cb)
{
 //log->setDebugEnabled(true);
 QList<TurnoutOperation*> ops = TurnoutOperationManager::getInstance()->getTurnoutOperations();
 cb->clear();
 QVector<QString> strings =  QVector<QString>(/*20*/);
 QVector<QString> defStrings =  QVector<QString>(/*20*/);
 log->debug(tr("opsCombo start %1").arg(ops.length()));
 for (TurnoutOperation* op : ops) {
  if(log->isDebugEnabled()) log->debug(QString("isDef ")+(op->isDefinitive()?"true":"false")+ " mFMM "+(op->matchFeedbackMode(t->getFeedbackMode())?"true":"false")+ " isNonce "+(op->isNonce()?"true":"false"));
  if (!op->isDefinitive()
            && op->matchFeedbackMode(t->getFeedbackMode())
            && !op->isNonce())
  {
   strings.append(op->getName());
  }
 }
 log->debug("opsCombo end");
for (TurnoutOperation* op : ops)  {
  if (op->isDefinitive()
      && op->matchFeedbackMode(t->getFeedbackMode())) {
      defStrings.append(op->getName());
  }
 }
//    java.util.Collections.sort(strings);
qSort(strings.begin(), strings.end());
//    java.util.Collections.sort(defStrings);
qSort(defStrings.begin(), defStrings.end());
 strings.insert(0, tr("Off"));
 strings.insert(1,tr("Use Global Default "));
 for (int i=0; i<defStrings.size(); ++i) {
  try {
      strings.insert(i+2,defStrings.at(i));
  } catch(ArrayIndexOutOfBoundsException* obe){
   // just catch it
  }
 }
 for (int i=0; i<strings.size(); ++i)
 {
  cb->addItem(strings.at(i));
 }

 if (t->getInhibitOperation()) {
     cb->setSelectedIndex(0);
 } else {
  TurnoutOperation* turnOp = t->getTurnoutOperation();
  if (turnOp == nullptr) {
      cb->setSelectedIndex(1);
  } else {
      if (turnOp->isNonce()) {
          cb->setSelectedIndex(2);
      } else {
          cb->setSelectedItem(turnOp->getName());
      }
  }
 }
}

/*protected*/ void TurnoutTableAction::setDefaultSpeeds(JFrame* _who)
{
    JComboBox* thrownCombo = new JComboBox();
    thrownCombo->addItems((( TurnoutTableDataModel*)m)->speedListThrown.toList());
    JComboBox* closedCombo = new JComboBox();
    closedCombo->addItems((( TurnoutTableDataModel*)m)->speedListClosed.toList());
    thrownCombo->setEditable(true);
    closedCombo->setEditable(true);

    QWidget* thrown = new QWidget();
    QHBoxLayout* thrownLayout = new QHBoxLayout;
    thrown->setLayout(thrownLayout);
    thrownLayout->addWidget(new QLabel("Thrown Speed"));
    thrownLayout->addWidget(thrownCombo);

    QWidget* closed = new QWidget();
    QHBoxLayout* closedLayout = new QHBoxLayout;
    closed->setLayout(closedLayout);
    closedLayout->addWidget(new QLabel("Closed Speed"));
    closedLayout->addWidget(closedCombo);

    thrownCombo->removeItem(thrownCombo->findText((( TurnoutTableDataModel*)m)->defaultThrownSpeedText));
    closedCombo->removeItem(closedCombo->findText((( TurnoutTableDataModel*)m)->defaultClosedSpeedText));

    thrownCombo->setCurrentIndex(thrownCombo->findText(turnoutManager->getDefaultThrownSpeed()));
    closedCombo->setCurrentIndex(closedCombo->findText(turnoutManager->getDefaultClosedSpeed()));

    int retval = JOptionPane::showOptionDialog(_who,
                                      tr("Select the default values for the speed through the turnout") , tr("Turnout Speeds"),
                                      0, JOptionPane::INFORMATION_MESSAGE, QIcon(),
                                      QVariantList({"Cancel", "OK", "Thrown Speed", "Closed Speed"}), QVariant() );
    if (retval != 1) {
        return;
    }
    QString closedValue =  closedCombo->currentText();
    QString thrownValue =  thrownCombo->currentText();
    //We will allow the turnout manager to handle checking if the values have changed
    try {
        turnoutManager->setDefaultThrownSpeed(thrownValue);
    } catch (JmriException* ex) {
//        JOptionPane.showMessageDialog(NULL, ex->getMessage() + "\n" + thrownValue);
    }

    try {
        turnoutManager->setDefaultClosedSpeed(closedValue);
    } catch (JmriException* ex) {
//        JOptionPane.showMessageDialog(NULL, ex->getMessage() + "\n" + closedValue);
    }
}

/*private*/ void TurnoutTableAction::initCheckBoxes(){
    doAutomationBox->setChecked(((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->getDoOperations());
    doAutomationBox->setToolTip(tr("Enable automatic retry setting for all Turnouts"));
    //doAutomationBox.addActionListener(e -> InstanceManager.getDefault(TurnoutOperationManager.class).setDoOperations(doAutomationBox.isSelected()));
    connect(doAutomationBox, &QCheckBox::clicked, [=]{((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->setDoOperations(doAutomationBox->isChecked());});
    showFeedbackBox->setToolTip(tr("Show extra columns for configuring turnout feedback"));
    showLockBox->setToolTip(tr("Show extra columns for configuring turnout lock"));
    showTurnoutSpeedBox->setToolTip(tr("Show extra columns for configuring turnout Speeds, when used with Signaling"));
    showStateForgetAndQueryBox->setToolTip(tr("Displays columns for clearing and querying state"));
}

//@Override
/*protected*/ void TurnoutTableAction::configureTable(JTable* table){
    AbstractTableAction::configureTable(table);
    //showStateForgetAndQueryBox.addActionListener(e ->
    connect(showStateForgetAndQueryBox, &TriStateJCheckBox::toggled, [=]{
        ((TurnoutTableDataModel*) m)->showStateForgetAndQueryChanged(showStateForgetAndQueryBox->isSelected(),table);});
    //showTurnoutSpeedBox.addActionListener(e ->
    connect(showTurnoutSpeedBox, &TriStateJCheckBox::toggled, [=]{
        ((TurnoutTableDataModel*) m)->showTurnoutSpeedChanged(showTurnoutSpeedBox->isSelected(),table);});
    //showFeedbackBox.addActionListener(e ->
    connect(showFeedbackBox, &TriStateJCheckBox::toggled, [=]{
        ((TurnoutTableDataModel*) m)->showFeedbackChanged(showFeedbackBox->isSelected(), table);});
    //showLockBox.addActionListener(e ->
    connect(showLockBox, &TriStateJCheckBox::toggled, [=]{
        ((TurnoutTableDataModel*) m)->showLockChanged(showLockBox->isSelected(),table);});
}

/**
 * Add the check box and Operations menu item
 */
//@Override
/*public*/ void TurnoutTableAction::addToFrame(BeanTableFrame* f)
{
 initCheckBoxes();
 f->addToBottomBox(doAutomationBox, this->getClassName());
 f->addToBottomBox(showFeedbackBox, this->getClassName());
 f->addToBottomBox(showLockBox, this->getClassName());
 f->addToBottomBox(showTurnoutSpeedBox, this->getClassName());
 f->addToBottomBox(showStateForgetAndQueryBox, this->getClassName());
}

//@Override
/*public*/ void TurnoutTableAction::addToPanel(AbstractTableTabAction* f)
{
 QString connectionName = turnoutManager->getMemo()->getUserName();
 if (QString(turnoutManager->mself()->metaObject()->className()).contains("ProxyTurnoutManager")) {
     connectionName = "All"; // NOI18N
 }
 initCheckBoxes();
 f->addToBottomBox(doAutomationBox, connectionName);
 f->addToBottomBox(showFeedbackBox, connectionName);
 f->addToBottomBox(showLockBox, connectionName);
 f->addToBottomBox(showTurnoutSpeedBox, connectionName);
 f->addToBottomBox(showStateForgetAndQueryBox, connectionName);
}

/**
 * Override to update column select checkboxes.
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TurnoutTableAction::columnsVisibleUpdated(QVector<bool> colsVisible){
    log->debug(tr("columns updated %1").arg(colsVisible.count()));
    showFeedbackBox->setState(QVector<bool>{
        colsVisible[TurnoutTableDataModel::KNOWNCOL],
        colsVisible[TurnoutTableDataModel::MODECOL],
        colsVisible[TurnoutTableDataModel::SENSOR1COL],
        colsVisible[TurnoutTableDataModel::SENSOR2COL],
        colsVisible[TurnoutTableDataModel::OPSONOFFCOL],
        colsVisible[TurnoutTableDataModel::OPSEDITCOL]});

    showLockBox->setState(QVector<bool>{
        colsVisible[TurnoutTableDataModel::LOCKDECCOL],
        colsVisible[TurnoutTableDataModel::LOCKOPRCOL]});

    showTurnoutSpeedBox->setState(QVector<bool>{
        colsVisible[TurnoutTableDataModel::STRAIGHTCOL],
        colsVisible[TurnoutTableDataModel::DIVERGCOL]});

    showStateForgetAndQueryBox->setState(QVector<bool>{
        colsVisible[TurnoutTableDataModel::FORGETCOL],
        colsVisible[TurnoutTableDataModel::QUERYCOL]});

}

//void TurnoutTableAction::On_doAutomationBox_toggled(bool b)
//{
// TurnoutOperationManager::getInstance()->setDoOperations(doAutomationBox->isChecked());
// pref->setSimplePreferenceState(this->getClassName()+".doAutomation", b);
//}

//void TurnoutTableAction::showFeedbackChanged()
//{
// bool showFeedback = showFeedbackBox->isChecked();
// XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
// TableColumn* column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::KNOWNCOL);
// columnModel->setColumnVisible(column, showFeedback);
// column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::MODECOL);
// columnModel->setColumnVisible(column, showFeedback);
// column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::SENSOR1COL);
// columnModel->setColumnVisible(column, showFeedback);
// column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::SENSOR2COL);
// columnModel->setColumnVisible(column, showFeedback);
// column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::OPSONOFFCOL);
// columnModel->setColumnVisible(column, showFeedback);
// column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::OPSEDITCOL);
// columnModel->setColumnVisible(column, showFeedback);
// pref->setSimplePreferenceState(this->getClassName()+".showFeedback", showFeedback);

//}

//void TurnoutTableAction::showLockChanged()
//{
// bool showLock = showLockBox->isChecked();
//    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
//    TableColumn* column  = ((XTableColumnModel*)table->getColumnModel())->getColumnByModelIndex(TurnoutTableDataModel::LOCKDECCOL);
//    columnModel->setColumnVisible(column, showLock);
//    column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::LOCKOPRCOL);
//    columnModel->setColumnVisible(column, showLock);
//    pref->setSimplePreferenceState(this->getClassName()+".showLockBox", showLock);
//}

////bool showTurnoutSpeed = false;
///*public*/ void TurnoutTableAction::showTurnoutSpeedChanged()
//{
//    bool showTurnoutSpeed = showTurnoutSpeedBox->isChecked();
//    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
//    TableColumn* column  = ((XTableColumnModel*)table->getColumnModel())->getColumnByModelIndex(TurnoutTableDataModel::STRAIGHTCOL);
//    columnModel->setColumnVisible(column, showTurnoutSpeed);
//    column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::DIVERGCOL);
//    columnModel->setColumnVisible(column, showTurnoutSpeed);
//    pref->setSimplePreferenceState(this->getClassName()+".showTurnoutSpeed", showTurnoutSpeed);
//}

//@Override
/*public*/ void TurnoutTableAction::setMenuBar(BeanTableFrame* f)
{
 /*final*/ JmriJFrame* /*final*/F = f;			// needed for anonymous ActionListener class
 QMenuBar* menuBar = f->menuBar();
 QList<QAction*> ol = menuBar->actions();
 QMenu* opsMenu = NULL;
 QMenu* speedMenu = NULL;
 for(int i=0; i < ol.count(); i++)
 {
  if(qobject_cast<QAction*>(ol.at(i))!= NULL )
  {
   QString title = ol.at(i)->text();
   QMenu* m = (QMenu*)ol.at(i);
   if(title == tr("Automation"))
   {
    opsMenu = ol.at(i)->menu();
    opsMenu->clear();
   }
   if(title == tr("Speeds"))
   {
    speedMenu = ol.at(i)->menu();
    speedMenu->clear();
   }
  }
 }
 if(opsMenu == NULL)
 {
  opsMenu = new QMenu(tr("Automation"));
  menuBar->addMenu(opsMenu);
 }
 QAction* item = new QAction("Edit...", this);
 opsMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//               new Tur noutOperationFrame(/*final*/F);
//        }
//        });
 ItemListener1* itemListener = new ItemListener1(F);
 //connect(item, SIGNAL(triggered()), itemListener->self(), SLOT(actionPerformed()));
 connect(item, &QAction::triggered, [=]{itemListener->actionPerformed();});
 menuBar->addMenu(opsMenu);

 if(speedMenu == NULL)
 {
  speedMenu = new QMenu(tr("Speeds"));
  menuBar->addMenu(speedMenu);
 }
 item = new QAction("Defaults...", this);
 speedMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                setDefaultSpeeds(/*final*/F);
//        }
//        });
 ItemListener2* itemListener2 = new ItemListener2(F,this);
 connect(item, SIGNAL(triggered()), itemListener2->self(), SLOT(actionPerformed()));
}

ItemListener1::ItemListener1(JmriJFrame *F)
{
 this->F = F;
}

void ItemListener1::actionPerformed(JActionEvent */*e*/)
{
   new TurnoutOperationFrame(/*final*/F);
}
ItemListener2::ItemListener2(JmriJFrame *F, TurnoutTableAction* tta)
{
 this->F = F;
 this->tta = tta;
}
void ItemListener2::actionPerformed(JActionEvent */*e*/)
{
 tta->setDefaultSpeeds(/*final*/F);
}

void TurnoutTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void TurnoutTableAction::createPressed(ActionEvent* /*e*/)
{
 // Test if bit already in use as a light
 //int iName=0;
 int numberOfTurnouts = 1;

 if (rangeBox->isChecked()) {
     numberOfTurnouts =  numberToAddSpinner->getValue();
 }
 if (numberOfTurnouts >= 65)
 {// limited by JSpinnerModel to 100
  if(JOptionPane::showConfirmDialog(addFrame, "You are about to add " + QString::number(numberOfTurnouts) + " Turnouts into the configuration\nAre you sure?","Warning", JOptionPane::YES_NO_OPTION)==1)
   return;
 }

 QString sName = "";
 //QString prefix = prefixBox.getSelectedItem().getSystemPrefix();
 QString prefix;
 QVariant currData = prefixBox->getItemAt(prefixBox->currentIndex());//prefixBox->currentData(Qt::UserRole);
 QString currText = prefixBox->currentText();
 Manager* mgr = VPtr<Manager>::asPtr(currData);
 prefix = ((TurnoutManager*)mgr->mself())->getSystemPrefix();
 QString curAddress = hardwareAddressTextField->text();
 // initial check for empty entry
 if (curAddress.length() < 1)
 {
   statusBarLabel->setText(tr("You must provide a Hardware Address to start."));
   statusBarLabel->setStyleSheet("QLabel { color: red}");
   hardwareAddressTextField->setStyleSheet("QLabel { background-color: red}");
   addButton->setEnabled(false);
   return;
 }
 else
 {
  hardwareAddressTextField->setStyleSheet("QLabel { background-color: white}");
  addButton->setEnabled(true);
 }

 QString uName = userNameTextField->text();
 if (uName.isEmpty()) {
     uName = QString();
 }

 // Add some entry pattern checking, before assembling sName and handing it to the turnoutManager
 QString statusMessage = tr("New %1(s) added:").arg(tr("Turnout"));
 QString errorMessage = "";

 QString lastSuccessfulAddress = tr("NONE");

 int iType = 0;
 int iNum=1;
 bool useLastBit = false;
 bool useLastType = false;

 for (int x = 0; x < numberOfTurnouts; x++)
 {
  try
  {
   curAddress = InstanceManager::turnoutManagerInstance()->getNextValidAddress(curAddress, prefix);
  }
  catch (JmriException* ex)
  {
   ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                   showErrorMessage("Error","Unable to convert '" + curAddress + "' to a valid Hardware Address",""+ex->getMessage(), "",true, false);
   // directly add to statusBar (but never called?)
   statusBarLabel->setText(tr("Error Converting HW address %1").arg(curAddress));
   statusBarLabel->setStyleSheet("QLabel { color: red}");
   return;
  }
  if (curAddress=="")
  {
   //The next address is already in use, therefore we stop.
   log->debug(tr("Error converting HW or getNextValidAddress"));
   errorMessage = (tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip)."));
   statusBarLabel->setStyleSheet("QLabel { color: red}");
   // The next address returned an error, therefore we stop this attempt and go to the next address.
   break;
  }
  //We have found another turnout with the same address, therefore we need to go onto the next address.
  sName=prefix+InstanceManager::turnoutManagerInstance()->typeLetter()+curAddress;
  QString testSN = prefix+"L"+curAddress;
  Light* testLight = nullptr;
  NamedBean* nb = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->
                  AbstractProxyManager::getBySystemName(testSN);
  if(nb)
   testLight =(Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->
          AbstractProxyManager::getBySystemName(testSN)->self();
  if (testLight != NULL)
  {
   // Address is already used as a Light
   log->warn("Requested Turnout "+sName+" uses same address as Light "+testSN);
   if (!noWarn)
   {
    int selectedValue = JOptionPane::showOptionDialog(addFrame,
                                    tr("Warning - Requested Turnout")+" "+sName+" "+tr("uses same address as Light")+" "+ testSN+".\n   " +tr("Do you still want to add this Turnout?"),tr("Warning"),
                                    JOptionPane::YES_NO_CANCEL_OPTION,JOptionPane::QUESTION_MESSAGE,QIcon(),
                                    QVariantList({tr("Yes"),tr("No"),
                                                tr("Yes - Stop Warnings")}),tr("No"));
    if (selectedValue == 1)
    {
     // Show error message in statusBar
     errorMessage = tr("Turnout \"%1\" not created as name matched a Light").arg(sName);
     statusBarLabel->setText(errorMessage);
     statusBarLabel->setStyleSheet("QLabel { color: gray}");
     return;   // return without creating if "No" response
    }
    if (selectedValue == 2)
    {
     // Suppress future warnings, and continue
     noWarn = true;
    }
   }
  }
  // Ask about two bit turnout control if appropriate

  if(!useLastBit)
  {
   iNum = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->askNumControlBits(sName);
   if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isNumControlBitsSupported(sName)) && (rangeBox->isChecked()))
   {
    if(JOptionPane::showConfirmDialog(addFrame,
                                 "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
                                 JOptionPane::YES_NO_OPTION)==0)
           useLastBit=true;
       // Add a pop up here asking if the user wishes to use the same value for all
   }
   else
   {
   //as isNumControlBits is not supported, then we will always use the same value.
       useLastBit=true;
   }
  }
  if (iNum==0)
  {
   // User specified more bits, but bits are not available - return without creating
   // Display message in statusBar
   errorMessage = tr("2 Bits requested but not supported. Stopped after \"%1\".").arg( lastSuccessfulAddress);
   statusBarLabel->setText(errorMessage);
   statusBarLabel->setStyleSheet("QLabel { color: red}");
   return;
  }
  else
  {
   // Create the new turnout
   Turnout* t;
   try
   {
    t = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout(sName);
   }
   catch (IllegalArgumentException* ex)
   {
    // user input no good
    handleCreateException(sName);
    // add to statusBar as well
    errorMessage = tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip).");
    statusBarLabel->setText(errorMessage);
    statusBarLabel->setStyleSheet("QLabel { color: red}");
    return; // without creating
   }

   if (t != NULL)
   {
    if ((!uName.isNull()) && !uName.isEmpty())
    {
     if (((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getByUserName(uName) == nullptr)
     {
      t->setUserName(uName);
     }
     else if (!pref->getPreferenceState(getClassName(), "duplicateUserName"))
     {
         ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                 showErrorMessage(tr("Error"),
                         tr("The specified user name \"%1\" is already in use and therefore will not be set.").arg(uName),
                         getClassName(), "duplicateUserName", false, true);
     }
    }

    t->setNumberOutputBits(iNum);
    // Ask about the type of turnout control if appropriate
    if(!useLastType)
    {
     iType = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->askControlType(sName);
     if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isControlTypeSupported(sName)) && (rangeBox->isChecked()))
     {
      if (JOptionPane::showConfirmDialog(addFrame,
                           "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
                           JOptionPane::YES_NO_OPTION)==0)// Add a pop up here asking if the user wishes to use the same value for all
       useLastType=true;
     }
     else
     {
      useLastType = true;
     }
    }
    t->setControlType(iType);
   }
  }
 }
 // provide feedback to user
 if (errorMessage == "") {
     statusBarLabel->setText(statusMessage);
     statusBarLabel->setStyleSheet("QLabel { color: gray}");
 }
 else
 {
  statusBarLabel->setText(errorMessage);
     // statusBar.setForeground(Color.red); // handled when errorMassage is set, to differentiate in urgency
 }

 pref->setComboBoxLastSelection(systemSelectionCombo,
                                prefixBox->getSelectedItem()->getMemo()->getUserName()); // store user pref
 addFrame->setVisible(false);
 addFrame->dispose();
 addFrame = nullptr;
}

/*private*/ void TurnoutTableAction::canAddRange(JActionEvent* /*e*/){
 rangeBox->setEnabled(false);
 log->debug("T Add box disabled");
 rangeBox->setSelected(false);
 if (prefixBox->getSelectedIndex() == -1) {
     prefixBox->setSelectedIndex(0);
 }
 TurnoutManager* manager = (AbstractTurnoutManager*)prefixBox->getSelectedItem()->mself();
 Q_ASSERT( manager != nullptr);
 QString systemPrefix = manager->getSystemPrefix();
 //rangeBox->setEnabled(((AbstractTurnoutManager*)manager->mself())->allowMultipleAdditions(systemPrefix));
 rangeBox->setEnabled(manager->allowMultipleAdditions(systemPrefix));
 addEntryToolTip = manager->getEntryToolTip();
 // show sysName (HW address) field tooltip in the Add Turnout pane that matches system connection selected from combobox
 hardwareAddressTextField->setToolTip(
         tr("<html>%1 %2 use one of these patterns:<br>%3</html>").arg(
                 manager->getMemo()->getUserName(),
                 tr("Turnouts"),
                 addEntryToolTip));
// hardwareAddressValidator->setTooltip(hardwareAddressTextField->toolTip());
 hardwareAddressValidator->verify(hardwareAddressTextField);
}

void TurnoutTableAction::handleCreateException(QString sysName)
{
    JOptionPane::showMessageDialog(addFrame,
            tr("Could not create turnout \"%1\" to add it. Check that number/name is OK.").arg(sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}


/*protected*/ QString TurnoutTableAction::getClassName() { return "jmri.jmrit.beantable.TurnoutTableAction"; }

//@Override
/*public*/ void TurnoutTableAction::setMessagePreferencesDetails()
{
    ((UserPreferencesManager*)   InstanceManager::getDefault("UserPreferencesManager"))->setPreferenceItemDetails(getClassName(), "duplicateUserName", tr("Hide Duplicate User Name Warning Message"));
    AbstractTableAction::setMessagePreferencesDetails();
}

//@Override
/*public*/ QString TurnoutTableAction::getClassDescription() { return tr("Turnout Table"); }
#if 0
static class BeanBoxRenderer extends JmriBeanComboBox implements TableCellRenderer {
    /**
     *
     */
    /*private*/ static /*final*/ long serialVersionUID = 7351045146446284915L;

    /*public*/ BeanBoxRenderer() {
        super(InstanceManager::sensorManagerInstance());
        setFirstItemBlank(true);
    }

    /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
        bool isSelected, bool hasFocus, int row, int column) {
        if (isSelected) {
            setForeground(table.getSelectionForeground());
            super.setBackground(table.getSelectionBackground());
        } else {
            setForeground(table.getForeground());
            setBackground(table.getBackground());
        }
        if(value instanceof NamedBean)
            setSelectedBean((NamedBean)value);
        else
            setSelectedBean(NULL);
        return this;
    }
}

static class BeanComboBoxEditor extends DefaultCellEditor {
    /**
     *
     */
    /*private*/ static /*final*/ long serialVersionUID = 1705620352249335223L;

    /*public*/ BeanComboBoxEditor(JmriBeanComboBox beanBox) {
        super(beanBox);
    }
}
#endif
QString TurnoutTableAction::getName() { return "jmri.jmrit.beantable.TurnoutTableAction";}



TTAValidator::TTAValidator(JTextField *fld, TurnoutTableAction *act)
{
 this->fld = fld;
 this->act = act;
 connect(act->prefixBox, SIGNAL(currentTextChanged(QString)), this, SLOT(prefixBoxChanged(QString)));
 prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
 mark = ColorUtil::stringToColor("orange");
}

QValidator::State TTAValidator::validate(QString& s, int& pos) const
{
 QString value = s.trimmed();
 if ((value.length() < 1) && (allow0Length == false)) {
     return QValidator::Invalid;
 } else if ((allow0Length == true) && (value.length() == 0)) {
     return QValidator::Acceptable;
 } else {
  bool bok;
  int num = s.toInt(&bok);
  if(!bok )
   return QValidator::Invalid;
  else if(num == 0)
   return QValidator::Intermediate;
  else if(!(num > 0 && num <= 2047 ))
   return QValidator::Invalid;
 }
// if(prefix == "")
// {
//  QString txt = act->prefixBox->currentText();
//  this->prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
// }
 bool validFormat = false;
 // try {
 validFormat = qobject_cast<LightManager*>(InstanceManager::getDefault("LightManager"))->validSystemNameFormat(prefix + "L" + value) == Manager::NameValidity::VALID;
 // } catch (jmri.JmriException e) {
 // use it for the status bar?
 // }
 if (validFormat) {
  act->addButton->setEnabled(true); // directly update Create button
  fld->setBackground(QColor(Qt::white));
  return QValidator::Acceptable;
 } else {
  act->addButton->setEnabled(false); // directly update Create button
  fld->setBackground(mark);
  return QValidator::Invalid;
 }
}

void TTAValidator::setPrefix(QString prefix) { this->prefix = prefix;}

void TTAValidator::prefixBoxChanged(QString txt)
{
 prefix = ConnectionNameFromSystemName::getPrefixFromName(txt);
}


/*private*/ /*final*/ /*static*/ Logger* TurnoutTableAction::log = LoggerFactory::getLogger("TurnoutTableAction");
