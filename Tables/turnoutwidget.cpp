#include "turnoutwidget.h"
#include "ui_turnoutwidget.h"
#include <QTabWidget>
#include "addeditdialog.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "signalspeedmap.h"
#include "../LayoutEditor/turnoutoperationframe.h"
#include "defaultusermessagepreferences.h"
#include "connectionnamefromsystemname.h"
#include "jtextfield.h"
#include "addnewhardwaredevicepanel.h"
#include "../LayoutEditor/jmrijframe.h"
#include <QLabel>
#include "defaultusermessagepreferences.h"

TurnoutWidget::TurnoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnoutWidget)
{
 ui->setupUi(this);
 ui->tabWidget->clear(); // remove default tabs
 useBlockSpeed = "Use Block Speed";
 speedListClosed = new QVector<QString>();
 speedListClosed->append(defaultClosedSpeedText);
 speedListThrown = new QVector<QString>();
 speedListThrown->append(defaultThrownSpeedText);
 speedListClosed->append(useBlockSpeed);
 speedListThrown->append(useBlockSpeed);
_speedMap = SignalSpeedMap::getMap()->getValidSpeedNames();
 for(int i = 0; i<_speedMap.size(); i++)
 {
  if (!speedListClosed->contains(_speedMap.at(i)))
  {
   speedListClosed->append(_speedMap.at(i));
  }
  if (!speedListThrown->contains(_speedMap.at(i)))
  {
   speedListThrown->append(_speedMap.at(i));
  }
 }
 p = (DefaultUserMessagePreferences*) InstanceManager::getDefault("UserPreferencesManager");

 tableWidget1 = new TurnoutTableWidget(-1, this); // ALL
 ui->tabWidget->addTab(tableWidget1,tr("All"));
 tableWidget2 = new TurnoutTableWidget(0, this); // LocoNet only
 ui->tabWidget->addTab(tableWidget2, tr("LocoNet"));
 tableWidget3 = new TurnoutTableWidget(1, this); // Internal only
 ui->tabWidget->addTab(tableWidget3, tr("Internal"));
 //ui->chkFeedback->setChecked(false);
 ui->chkAuto->setChecked(TurnoutOperationManager::getInstance()->getDoOperations());
 showFeedbackInfo = QString(this->metaObject()->className()) + ":+" + "showFeedbackInfo";
 showLockInfo  = QString(this->metaObject()->className()) + ":" +"showLockInfo";
 autoRetry = QString(this->metaObject()->className()) + ":" +"autoRetry";
 showSpeedDetails = QString(this->metaObject()->className()) + ":" +"showLockInfo";
 ui->chkFeedback->setChecked(p->getSimplePreferenceState(showFeedbackInfo));
 ui->chkFeedback->setChecked(p->getSimplePreferenceState(showLockInfo));
 ui->chkFeedback->setChecked(p->getSimplePreferenceState(autoRetry));
 ui->chkFeedback->setChecked(p->getSimplePreferenceState(showSpeedDetails));


 setWindowTitle("Turnouts");
 on_chkFeedback_toggled(ui->chkFeedback->isChecked());
 on_chkLockInfo_toggled(ui->chkLockInfo->isChecked());
 on_chkSpeedDetails_toggled(ui->chkSpeedDetails->isChecked());
 on_chkAuto_toggled(ui->chkAuto->isChecked());
 turnManager = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
 defaultThrownSpeedText = ("Use Global " + turnManager->getDefaultThrownSpeed());
 defaultClosedSpeedText = ("Use Global " + turnManager->getDefaultClosedSpeed());
 //This following must contain the word Block for a correct match in the abstract turnout

 connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addPressed()));
 addFrame = NULL;
 sysName = new JTextField(40);
 userName = new JTextField(40);
 range = new QCheckBox(tr("Add a range"));
 numberToAdd = new JTextField(5);
 numberToAdd->setValidator(new QIntValidator(1,100));
 log = new Logger("TurnoutWidget");
 noWarn = false;
 systemSelectionCombo = QString(this->metaObject()->className())+".SystemSelected";
 userNameError = QString(this->metaObject()->className())+".DuplicateUserName";
 prefixBox = new QComboBox();
}

TurnoutWidget::~TurnoutWidget()
{
 delete ui;
}
QVector<QString>* TurnoutWidget::getSpeedListClosed() { return speedListClosed;}
QVector<QString>* TurnoutWidget::getSpeedListThrown() { return speedListThrown;}

void TurnoutWidget::on_chkFeedback_toggled(bool bState)
{
 tableWidget1->showFeedbackInfo(bState);
 tableWidget2->showFeedbackInfo(bState);
 tableWidget3->showFeedbackInfo(bState);
 p->setSimplePreferenceState(showFeedbackInfo, bState);
}

void TurnoutWidget::on_chkLockInfo_toggled(bool bState)
{
 tableWidget1->showLockInformation(bState);
 tableWidget2->showLockInformation(bState);
 tableWidget3->showLockInformation(bState);
 p->setSimplePreferenceState(showLockInfo, bState);
}

void TurnoutWidget::on_chkSpeedDetails_toggled(bool bState)
{
 tableWidget1->showTurnoutSpeedDetails(bState);
 tableWidget2->showTurnoutSpeedDetails(bState);
 tableWidget3->showTurnoutSpeedDetails(bState);
 p->setSimplePreferenceState(showSpeedDetails, bState);
}

void TurnoutWidget::on_chkAuto_toggled(bool bState)
{
 TurnoutOperationManager::getInstance()->setDoOperations(bState);
 p->setSimplePreferenceState(autoRetry,bState);
}

//void TurnoutWidget::on_btnAdd_clicked()
//{
// AddEditDialog dlg(tr("Turnouts"), NULL, this);
// if(dlg.exec() == QDialog::Accepted)
// {
//  ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
//  QString sysName;
//  QString system = dlg.system();
//  QString userName = dlg.userName();
//  int iMgr =mgr->nMgrs()-1;
//  if(system != tr("Internal")) iMgr= 0;
//  AbstractTurnoutManager* tmgr = (AbstractTurnoutManager*)mgr->getMgr(iMgr);
//  QString sPrefix = tmgr->getSystemPrefix()+ tmgr->typeLetter();
//  if(dlg.isAddRange())
//  {
//   int count = dlg.numToAdd();
//   int addr = dlg.systemName().toInt();
//   for(int iAddr = addr; iAddr < addr + count; iAddr++)
//   {
//    sysName = sPrefix+QString("%1").arg(iAddr);
//    mgr->newTurnout(sysName, userName+QString("%1").arg(iAddr));
//   }
//  }
//  else
//  {
//   sysName = sPrefix+dlg.systemName();
//   mgr->newTurnout(sysName, userName);
//  }
// }
//}
/*protected*/ void TurnoutWidget::addPressed(ActionEvent* /*e*/)
{
  //p = (DefaultUserMessagePreferences*) InstanceManager::getDefault("UserPreferencesManager");

  if (addFrame==NULL)
  {
   addFrame = new JmriJFrame(tr("Add Turnout"), false, true);
   addFrame->setObjectName("AddTurnoutFrame");
   addFrame->addHelpMenu("package.jmri.jmrit.beantable.TurnoutAddEdit", true);
   QVBoxLayout* contentFrameLayout;
   if(addFrame->getContentPane()->layout() == NULL)
    addFrame->getContentPane()->setLayout(contentFrameLayout = new QVBoxLayout(addFrame->getContentPane()/*, BoxLayout.Y_AXIS*/));
   else
    contentFrameLayout = (QVBoxLayout*)addFrame->getContentPane()->layout();
   addFrame-> setMinimumSize(300,100);

//        ActionListener listener = new ActionListener() {
//                public void actionPerformed(ActionEvent e) {
//                    okPressed(e);
//                }
//            };
   OkButtonActionListener* listener = new OkButtonActionListener(this);

//        ActionListener rangeListener = new ActionListener() {
//                public void actionPerformed(ActionEvent e) {
//                    canAddRange(e);
//                }
//            };
   RangeActionListener* rangeListener = new RangeActionListener(this);
        /* We use the proxy manager in this instance so that we can deal with
        duplicate usernames in multiple classes */
        if (qobject_cast<AbstractProxyManager*>(InstanceManager::turnoutManagerInstance()) != NULL)
        {
            ProxyTurnoutManager* proxy = (ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance();
            QList<Manager*> managerList = proxy->getManagerList();
            for(int x = 0; x<managerList.size(); x++){
                QString manuName = ConnectionNameFromSystemName::getConnectionName(managerList.at(x)->getSystemPrefix());
                bool addToPrefix = true;
                //Simple test not to add a system with a duplicate System prefix
                for (int i = 0; i<prefixBox->count(); i++){
                    if((prefixBox->itemText(i))==(manuName))
                        addToPrefix=false;
                }
                if (addToPrefix)
                    prefixBox->addItem(manuName);
            }
            if(p->getComboBoxLastSelection(systemSelectionCombo)!=NULL)
                prefixBox->setCurrentIndex(prefixBox->findText(p->getComboBoxLastSelection(systemSelectionCombo)));
        }
        else {
            prefixBox->addItem(ConnectionNameFromSystemName::getConnectionName(turnManager->getSystemPrefix()));
        }
        sysName->setObjectName("sysName");
        userName->setObjectName("userName");
        prefixBox->setObjectName("prefixBox");
        contentFrameLayout->addWidget(new AddNewHardwareDevicePanel(sysName, userName, prefixBox, numberToAdd, range, tr("OK"), listener, rangeListener));
        canAddRange(NULL);
    }
    addFrame->pack();
    addFrame->setVisible(true);
}
OkButtonActionListener::OkButtonActionListener(TurnoutWidget *widget)
{
 this->widget = widget;
}
void OkButtonActionListener::actionPerformed(ActionEvent* /*e*/)
{
 widget->okPressed();
}
RangeActionListener::RangeActionListener(TurnoutWidget *widget)
{
 this->widget = widget;
}
void RangeActionListener::actionPerformed(ActionEvent* /*e*/)
{
 widget->canAddRange();
}

#if 1
/*protected*/ void TurnoutWidget::setDefaultSpeeds(QWidget* _who)
{
 QComboBox* thrownCombo = new QComboBox(/*speedListThrown*/);
 thrownCombo->addItems(speedListThrown->toList());
 QComboBox* closedCombo = new QComboBox(/*speedListClosed*/);
 closedCombo->addItems(speedListClosed->toList());
 thrownCombo->setEditable(true);
 closedCombo->setEditable(true);

 QWidget* thrown = new QWidget();
 thrown->setLayout(new QHBoxLayout);
 thrown->layout()->addWidget(new QLabel(tr("Thrown Speed")));
 thrown->layout()->addWidget(thrownCombo);

 QWidget* closed = new QWidget();
 closed->setLayout(new QHBoxLayout);
 closed->layout()->addWidget(new QLabel(tr("Closed Speed")));
 closed->layout()->addWidget(closedCombo);

 thrownCombo->removeItem(thrownCombo->findText(defaultThrownSpeedText));
 closedCombo->removeItem(closedCombo->findText(defaultClosedSpeedText));

 thrownCombo->setCurrentIndex(thrownCombo->findText(turnManager->getDefaultThrownSpeed()));
 closedCombo->setCurrentIndex(closedCombo->findText(turnManager->getDefaultClosedSpeed()));

// int retval = JOptionPane.showOptionDialog(_who,
//                                      rb.getString("TurnoutGlobalSpeedMessage") , rb.getString("TurnoutGlobalSpeedMessageTitle"),
//                                      0, JOptionPane.INFORMATION_MESSAGE, null,
//                                      new Object[]{"Cancel", "OK", thrown, closed}, null );
//    if (retval != 1) {
//        return;
//    }
 QMessageBox* box = new QMessageBox(QMessageBox::Information, tr("Turnout Speeds"),tr("Select the default values for the speed through the turnout"),QMessageBox::Cancel | QMessageBox::Ok,_who);
 box->layout()->addWidget(thrown);
 box->layout()->addWidget(closed);
 int retval = box->exec();
 if(retval != QMessageBox::Ok)
  return;

 QString closedValue = closedCombo->currentText();
 QString thrownValue = thrownCombo->currentText();
    //We will allow the turnout manager to handle checking if the values have changed
//    try {
        turnManager->setDefaultThrownSpeed(thrownValue);
//    }
// catch (JmriException ex) {
//        JOptionPane.showMessageDialog(null, ex.getMessage() + "\n" + thrownValue);
//    }

//    try {
        turnManager->setDefaultClosedSpeed(closedValue);
//    }
// catch (JmriException ex) {
//        JOptionPane.showMessageDialog(null, ex.getMessage() + "\n" + closedValue);
//    }
}
#endif
void TurnoutWidget::on_defaultSpeeds_triggered()
{
 qApp->processEvents();
 setDefaultSpeeds(this);
}
void TurnoutWidget::on_automation_triggered()
{
 qApp->processEvents();
 TurnoutOperationFrame* dlg = new TurnoutOperationFrame(this);
 dlg->exec();
}
/*private*/ void TurnoutWidget::canAddRange(ActionEvent* /*e*/)
{
 range->setEnabled(false);
 range->setChecked(false);
 //if (turnManager->getClass().getName().contains("ProxyTurnoutManager"))
 if(QString(turnManager->metaObject()->className()).contains("ProxyTurnoutManager"))
 {
  ProxyTurnoutManager* proxy = (ProxyTurnoutManager*) turnManager;
  QList<Manager*> managerList = proxy->getManagerList();
  QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText());
  for(int x = 0; x<managerList.size(); x++)
  {
   AbstractTurnoutManager* mgr = (AbstractTurnoutManager*) managerList.at(x);
   if (mgr->getSystemPrefix()==(systemPrefix) && mgr->allowMultipleAdditions(systemPrefix))
   {
    range->setEnabled(true);
    return;
   }
  }
 }
 else if (turnManager->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText())))
 {
  range->setEnabled(true);
 }
}

void TurnoutWidget::okPressed(ActionEvent* /*e*/)
{
 // Test if bit already in use as a light
 //int iName=0;
 int numberOfTurnouts = 1;

 if(range->isChecked())
 {
//  try {
  bool bOk;
  numberOfTurnouts = numberToAdd->text().toInt(&bOk);
//    } catch (NumberFormatException ex) {
  if(!bOk)
  {
   log->error("Unable to convert " + numberToAdd->text() + " to a number");
   ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->
                        showInfoMessage("Error","Number to turnouts to Add must be a number!",""/*+ex*/, "",true, false, Level::_ERROR);
   return;
  }
 }
 if (numberOfTurnouts>=65)
 {
//  if(JOptionPane.showConfirmDialog(addFrame,"You are about to add " + numberOfTurnouts + " Turnouts into the configuration\nAre you sure?","Warning", JOptionPane.YES_NO_OPTION)==1)
  if( QMessageBox::warning(this, tr("Warning"), tr("You are about to add ") + QString::number(numberOfTurnouts) + tr(" Turnouts into the configuration\nAre you sure?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
  return;
 }

 QString sName = "";
 QString curAddress = sysName->text();
        //String[] turnoutList = turnManager.formatRangeOfAddresses(sysName.getText(), numberOfTurnouts, getTurnoutPrefixFromName());
        //if (turnoutList == null)
        //    return;
 int iType = 0;
 int iNum=1;
 bool useLastBit = false;
 bool useLastType = false;
 QString prefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText());
 for (int x = 0; x < numberOfTurnouts; x++)
 {
  try
  {
   curAddress = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getNextValidAddress(curAddress, prefix);
  }
  catch (JmriException ex)
  {
   ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->
                    showInfoMessage("Error","Unable to convert '" + curAddress + "' to a valid Hardware Address",""/*+ex*/, "",true, false, Level::_ERROR);
   return;
  }
  if (curAddress=="")
  {
    //The next address is already in use, therefore we stop.
    break;
  }
  //We have found another turnout with the same address, therefore we need to go onto the next address.
  sName=prefix+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->typeLetter()+curAddress;
  QString testSN = prefix+"L"+curAddress;
  Light* testLight = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->
        getBySystemName(testSN);
  if (testLight != NULL)
  {
   // Address is already used as a Light
   log->warn("Requested Turnout "+sName+" uses same address as Light "+testSN);
   if (!noWarn)
   {
//    int selectedValue = JOptionPane.showOptionDialog(addFrame,
//                                        rb.getString("TurnoutWarn1")+" "+sName+" "+rb.getString("TurnoutWarn2")+" "+
//                                        testSN+".\n   "+rb.getString("TurnoutWarn3"),rb.getString("WarningTitle"),
//                                        JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,null,
//                                        new Object[]{rb.getString("ButtonYes"),rb.getString("ButtonNo"),
//                                                    rb.getString("ButtonYesPlus")},rb.getString("ButtonNo"));
    QMessageBox* msgBox = new QMessageBox(tr("Warning"), tr("Warning - Requested Turnout")+" "+sName+" "+tr("uses same address as Light")+" "+ testSN+".\n   " +tr("Do you still want to add this Turnout?"),QMessageBox::Warning,QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    QPushButton* buttonYesPlus = new QPushButton(tr("Yes - Stop Warnings"));
    msgBox->addButton(buttonYesPlus, QMessageBox::ActionRole);
    int selectedValue= msgBox->exec();
    if (selectedValue == QMessageBox::No) return;   // return without creating if "No" response
    if (msgBox->clickedButton() == buttonYesPlus)
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
    if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isNumControlBitsSupported(sName)) && (range->isChecked()))
    {
//        if(JOptionPane.showConfirmDialog(addFrame,
//                                     "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
//                                     JOptionPane.YES_NO_OPTION)==0)
      if(QMessageBox::question(this, tr("Use Setting"), tr("Do you want to use the last setting for all turnouts in this range? "),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            useLastBit=true;
        // Add a pop up here asking if the user wishes to use the same value for all
    } else {
    //as isNumControlBits is not supported, then we will always use the same value.
        useLastBit=true;
    }
}
if (iNum==0) {
    // User specified more bits, but bits are not available - return without creating
    return;
}
else {

    // Create the new turnout
    Turnout* t;
    try
    {
     t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(sName);
    } catch (IllegalArgumentException ex)
    {
     // user input no good
     handleCreateException(sName);
     return; // without creating
    }

    if (t != NULL)
    {
     QString user = userName->text();
     if ((x!=0) && user != "" && user!=(""))
       user = user+":"+x;
     if (user != "" && user!=("") && (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getByUserName(user)==NULL)) t->setUserName(user);

     else if (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getByUserName(user)!=NULL && !p->getPreferenceState("TurnoutWidget", "duplicateUserName"))
     {
      ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->
                 showInfoMessage("Duplicate UserName","The username " + user + " specified is already in use and therefore will not be set", "TurnoutWidget", "duplicateUserName", false, true, Level::_ERROR);
            //p.showInfoMessage("Duplicate UserName", "The username " + user + " specified is already in use and therefore will not be set", userNameError, "", false, true, org.apache.log4j.Level.ERROR);
     }
     ((AbstractTurnout*)t)->setNumberOutputBits(iNum);
     // Ask about the type of turnout control if appropriate
     if(!useLastType)
     {
      iType = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->askControlType(sName);
      if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isControlTypeSupported(sName)) && (range->isChecked()))
      {
//       if (JOptionPane.showConfirmDialog(addFrame,
//                                     "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
//                                     JOptionPane.YES_NO_OPTION)==0)// Add a pop up here asking if the user wishes to use the same value for all
//          JOptionPane.YES_NO_OPTION)==0)
       if(QMessageBox::question(this, tr("Use Setting"), tr("Do you want to use the last setting for all turnouts in this range? "),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
      useLastType=true;
     }
     else
     {
      useLastType = true;
     }
    }
    ((AbstractTurnout*)t)->setControlType(iType);
   }
  }
 }
 p->addComboBoxLastSelection(systemSelectionCombo,  prefixBox->currentText());
}
void TurnoutWidget::handleCreateException(QString sysName)
{
//    javax.swing.JOptionPane.showMessageDialog(addFrame,
//            java.text.MessageFormat.format(
//                rb.getString("ErrorTurnoutAddFailed"),
//                new Object[] {sysName}),
//            rb.getString("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Error"), tr("Could not create turnout \"%1\" to add it. Check that number/name is OK.").arg(sysName));
}
