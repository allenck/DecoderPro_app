#include "turnouteditaction.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "jmribeancombobox.h"
#include <QCheckBox>
#include <QComboBox>
#include "turnoutoperationconfig.h"
#include "turnout.h"
#include "turnoutoperation.h"
#include "rawturnoutoperation.h"
#include "flowlayout.h"
#include "beanitempanel.h"
#include "jtextfield.h"
#include <QMessageBox>
#include "turnouttableaction.h"
#include "signalspeedmap.h"
#include "beanedititem.h"


TurnoutEditAction::TurnoutEditAction(QModelIndex index, QObject* parent) : BeanEditAction(parent)
{
 useCurrent = new QCheckBox();
 inverted = new QCheckBox();
 useBlockSpeed = "Use Block Speed";//IN18N
 turnoutOperation = new QWidget();
 turnoutOperation->setLayout(turnoutOperationLayout = new FlowLayout);
 userDefinedOperation = "";
 operationsName = new JTextField(10);
 automationSelectionListener = new AutomationSelectionListener(this);
 bothText = "Both";
 cabOnlyText = "Cab only";
 pushbutText = "Pushbutton only";
 noneText = "None";
 speedListClosed =  QVector<QString>();
 speedListThrown =  QVector<QString>();
 lockBox = NULL;
 modeBox = NULL;
 this->index = index;
}
/**
 * Provides an edit panel for a block object
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 19923 $
 */
///*public*/ class TurnoutEditAction extends BeanEditAction {

/**
 *
 */
// private static final long serialVersionUID = 3432794348005461234L;

/*public*/ QString TurnoutEditAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TurnoutTable";
} //IN18N

//@Override
/*public*/ void TurnoutEditAction::actionPerformed(JActionEvent *e)
{
 oldAutomationSelection = ((Turnout*) bean)->getTurnoutOperation();
 oldModeSelection = ((Turnout*) bean)->getFeedbackModeName();
 BeanEditAction::actionPerformed(e);
}

//@Override
/*protected*/ void TurnoutEditAction::initPanels()
{
 BeanEditAction::initPanels();
 feedback();
 lock();
 speed();
}

/*public*/ QString TurnoutEditAction::getBeanType() {
    return tr("Turnout");
}

/*public*/ NamedBean* TurnoutEditAction::getByUserName(QString name)
{
 return InstanceManager::turnoutManagerInstance()->getByUserName(name);
}

//@Override
BeanItemPanel* TurnoutEditAction::basicDetails()
{
 BeanItemPanel* basic = BeanEditAction::basicDetails();

 basic->addItem(new BeanEditItem(inverted, tr("Inverted"), tr("When checked, the turnout command\nand status to and from the layout is inverted.")));

 return basic;
}

//@Override
/*protected*/ void TurnoutEditAction::saveBasicItems(ActionEvent* e)
{
    BeanEditAction::saveBasicItems(e);
    Turnout* turn = (Turnout*) bean;
    turn->setInverted(inverted->isChecked());
}

//@Override
/*protected*/ void TurnoutEditAction::resetBasicItems(ActionEvent* e)
{
 BeanEditAction::resetBasicItems(e);
 Turnout* turn = (Turnout*) bean;
 if (turn->canInvert())
 {
  inverted->setChecked(turn->getInverted());
 }
 inverted->setEnabled(turn->canInvert());
}



BeanItemPanel* TurnoutEditAction::feedback() {
    _feedback = new BeanItemPanel();
    _feedback->setName(tr("Feedback"));

    modeBox = new JComboBox();
    modeBox->addItems(((Turnout*) bean)->getValidFeedbackNames().toList());
    oldModeSelection = ((Turnout*) bean)->getFeedbackModeName();
    modeBox->setCurrentIndex(modeBox->findText(oldModeSelection));

//    modeBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            updateFeedbackOptions();
//        }
//    });
    connect(modeBox, SIGNAL(currentIndexChanged(QString)),this, SLOT(updateFeedbackOptions()));
    _feedback->addItem(new BeanEditItem(NULL, NULL, tr("This panel allows you to configure up the methods of feedback used to control and determine the state of a turnout")));
    _feedback->addItem(new BeanEditItem(modeBox, tr("Feedback Mode"), tr("Select the method of operation for a turnout")));

    sensorFeedBack1Field = new JmriBeanComboBox(InstanceManager::sensorManagerInstance(), ((Turnout*) bean)->getFirstSensor(), JmriBeanComboBox::DISPLAYNAME);
    sensorFeedBack1Field->setFirstItemBlank(true);
    _feedback->addItem(new BeanEditItem(sensorFeedBack1Field, tr("Feedback Sensor 1"), tr("Optional sensor that provides the feedback for a turnouts state")));

    sensorFeedBack2Field = new JmriBeanComboBox(InstanceManager::sensorManagerInstance(), ((Turnout*) bean)->getSecondSensor(), JmriBeanComboBox::DISPLAYNAME);
    sensorFeedBack2Field->setFirstItemBlank(true);
    _feedback->addItem(new BeanEditItem(sensorFeedBack2Field, tr("Feedback Sensor 2"), tr("Optional sensor that provides the feedback for a turnouts state")));

    QStringList str = QStringList();
    str << "empty";
    automationBox = new JComboBox();
    automationBox->addItems(str);

    _feedback->addItem(new BeanEditItem(automationBox, tr("Turnout Automation"), tr("Method used to retry the setting of the turnout")));

    oldAutomationSelection = ((Turnout*) bean)->getTurnoutOperation();
    if (oldAutomationSelection != NULL) {
        config = TurnoutOperationConfig::getConfigPanel(oldAutomationSelection);
    } else {
        config = TurnoutOperationConfig::getConfigPanel(new RawTurnoutOperation());
        config->setEnabled(false);
        foreach (QObject* j, config->children())
        {
         if(qobject_cast<QWidget*>(j)!= NULL)
            ((QWidget*)j)->setEnabled(false);
        }
    }

    turnoutOperationLayout->addWidget(config);
    _feedback->addItem(new BeanEditItem(turnoutOperation, tr("FeedbackOperation"), tr("FeedbackOperationToolTip")));
    _feedback->addItem(new BeanEditItem(operationsName, tr("FeedbackNameSet"), tr("FeedbackNameSetToolTip")));

//    _feedback->setSaveItem(new ActionListener() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 2969190372668700931L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;
//            String modeName =  modeBox.getSelectedItem();
//            t.setFeedbackMode(modeName);
//            String newName = operationsName.getText();
//            if (currentOperation != NULL && newName != NULL && !newName==("")) {
//                if (!currentOperation.rename(newName)) {
//                    JOptionPane.showMessageDialog(NULL, "This name '" + newName + "' is already in use",
//                            "Name already in use", JOptionPane.ERROR_MESSAGE);
//                } else {
//                    automationBox.addItem(newName);
//                    automationBox.setSelectedItem(newName);
//                }
//                t.setTurnoutOperation(NULL);
//                t.setTurnoutOperation(currentOperation);

//            }
//            config.endConfigure();
//            switch (automationBox.getSelectedIndex()) {
//                case 0:			// Off
//                    t.setInhibitOperation(true);
//                    t.setTurnoutOperation(NULL);
//                    break;
//                case 1:			// Default
//                    t.setInhibitOperation(false);
//                    t.setTurnoutOperation(NULL);
//                    break;
//                default:		// named operation
//                    t.setInhibitOperation(false);
//                    t.setTurnoutOperation(TurnoutOperationManager.getInstance().
//                            getOperation(( automationBox.getSelectedItem())));
//                    break;
//            }
//            oldAutomationSelection = ((Turnout) bean).getTurnoutOperation();
//            oldModeSelection = ((Turnout) bean).getFeedbackModeName();
//            try {
//                t.provideFirstFeedbackSensor(sensorFeedBack1Field->getSelectedDisplayName());
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.toString());
//            }
//            try {
//                t.provideSecondFeedbackSensor(sensorFeedBack2Field->getSelectedDisplayName());
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.toString());
//            }
//            if (config.isEnabled()) {

//            }
//        }
//    });
    _feedback->setSaveItem(new FeedbackSaveItemListener(this));
//    feedback->setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -6958613309056965212L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;

//            sensorFeedBack1Field->setSelectedBean(t.getFirstSensor());
//            sensorFeedBack2Field->setSelectedBean(t.getSecondSensor());
//            automationBox.removeActionListener(automationSelectionListener);
//            jmri.jmrit.beantable.TurnoutTableAction.updateAutomationBox(t, automationBox);
//            automationBox.addActionListener(automationSelectionListener);

//            t.setFeedbackMode(oldModeSelection);

//            updateFeedbackOptions();
//        }
//    });
 _feedback->setResetItem(new FeedbackResetItemListener(this));
 return _feedback;
}

FeedbackSaveItemListener::FeedbackSaveItemListener(TurnoutEditAction *act)
{
 this->act = act;
}

/*public*/ void FeedbackSaveItemListener::actionPerformed(JActionEvent* /*e*/)
{
 Turnout* t = (Turnout*) act->bean;
 QString modeName = act->modeBox->currentText();
 t->setFeedbackMode(modeName);
 QString newName = act->operationsName->text();
 if (act->currentOperation != NULL && newName != NULL && newName!=(""))
 {
  if (!act->currentOperation->rename(newName))
  {
//      JOptionPane.showMessageDialog(NULL, "This name '" + newName + "' is already in use",
//              "Name already in use", JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(NULL, tr("Error"), tr("This name '") + newName + tr("' is already in use"));
  }
  else
  {
   act->automationBox->addItem(newName);
   act->automationBox->setCurrentIndex(act->automationBox->findText(newName));
  }
  t->setTurnoutOperation(NULL);
  t->setTurnoutOperation(act->currentOperation);

 }
 act->config->endConfigure();
 switch (act->automationBox->currentIndex())
 {
  case 0:			// Off
      t->setInhibitOperation(true);
      t->setTurnoutOperation(NULL);
      break;
  case 1:			// Default
      t->setInhibitOperation(false);
      t->setTurnoutOperation(NULL);
      break;
  default:		// named operation
      t->setInhibitOperation(false);
      t->setTurnoutOperation(TurnoutOperationManager::getInstance()->
              getOperation(( act->automationBox->currentText())));
      break;
 }
 act->oldAutomationSelection = ((Turnout*) act->bean)->getTurnoutOperation();
 act->oldModeSelection = ((Turnout*) act->bean)->getFeedbackModeName();
 try
 {
  t->provideFirstFeedbackSensor(act->sensorFeedBack1Field->getSelectedDisplayName());
 }
 catch (JmriException ex)
 {
     //JOptionPane.showMessageDialog(NULL, ex.toString());
  QMessageBox::information(NULL, tr("Information"), ex.getMessage());
 }
 try
 {
  t->provideSecondFeedbackSensor(act->sensorFeedBack2Field->getSelectedDisplayName());
 } catch (JmriException ex) {
//     JOptionPane.showMessageDialog(NULL, ex.toString());
  QMessageBox::information(NULL, tr("Information"), ex.getMessage());
 }
 if (act->config->isEnabled())
 {

 }
}
FeedbackResetItemListener::FeedbackResetItemListener(TurnoutEditAction *act)
{
 this->act = act;
}

/*public*/ void FeedbackResetItemListener::actionPerformed(JActionEvent* /*e*/)
{
 Turnout* t = (Turnout*) act->bean;

 act->sensorFeedBack1Field->setSelectedBean(t->getFirstSensor());
 act->sensorFeedBack2Field->setSelectedBean(t->getSecondSensor());
 //act->automationBox.removeActionListener(automationSelectionListener);
 disconnect(act->automationBox);
 QStringList* automationList = new QStringList;
 for(int i = 0; i < act->automationBox->count(); i++)
  automationList->append(act->automationBox->itemText(i));
 TurnoutTableAction::updateAutomationBox(t, act->automationBox);
 //automationBox.addActionListener(automationSelectionListener);
 connect(act->automationBox, SIGNAL(currentIndexChanged(int)), this, SLOT(actionPerformed()));

 t->setFeedbackMode(act->oldModeSelection);

 act->updateFeedbackOptions();
}

///*transient*/ ActionListener* automationSelectionListener = new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        updateAutomationOptions();
//    }
//};
AutomationSelectionListener::AutomationSelectionListener(TurnoutEditAction *act)
{
 this->act = act;
}
void AutomationSelectionListener::actionPerformed(JActionEvent *)
{
 act->updateAutomationOptions();
}

void TurnoutEditAction::updateFeedbackOptions()
{
 Turnout* t = (Turnout*) bean;
 sensorFeedBack1Field->setEnabled(false);
 sensorFeedBack2Field->setEnabled(false);

 if (modeBox->currentText()==("ONESENSOR"))
 {
  sensorFeedBack1Field->setEnabled(true);
 }
 else if (modeBox->currentText()==("TWOSENSOR"))
 {
  sensorFeedBack1Field->setEnabled(true);
  sensorFeedBack2Field->setEnabled(true);
 }

 t->setFeedbackMode(modeBox->currentText());

 //TurnoutTableAction::updateAutomationBox(t, automationBox);
 QStringList* automationList = new QStringList;
 for(int i = 0; i < automationBox->count(); i++)
  automationList->append(automationBox->itemText(i));
 TurnoutTableAction::updateAutomationBox(t, automationBox);
}

void TurnoutEditAction::updateAutomationOptions() {

    if (userDefinedOperation != NULL && userDefinedOperation==(automationBox->currentText())) {
        return;
    }
    currentOperation = NULL;
    //automationBox.removeActionListener(automationSelectionListener);
    disconnect(automationBox);
    if (automationBox->currentIndex() > 1) {
        currentOperation = TurnoutOperationManager::getInstance()->
                getOperation(( automationBox->currentText()));
    }

    if (currentOperation != NULL) {
        turnoutOperation->layout()->removeWidget(config);
        if (!currentOperation->isNonce()) {
            currentOperation = currentOperation->makeNonce((Turnout*) bean);
        }
        config = TurnoutOperationConfig::getConfigPanel(currentOperation);
        operationsName->setEnabled(true);
        config->setEnabled(true);
        turnoutOperationLayout->addWidget(config);
//        _feedback->revalidate();
        _feedback->repaint();
    } else {

        operationsName->setEnabled(false);
        config->setEnabled(false);
        foreach (QObject* j, config->children())
        {
         if(qobject_cast<QWidget*>(j)!= NULL)
            ((QWidget*)j)->setEnabled(false);
        }
    }
    //automationBox.addActionListener(automationSelectionListener);
    connect(automationBox, SIGNAL(currentIndexChanged(QString)), automationSelectionListener, SLOT(actionPerformed()));
}

//@Override
/*protected*/ void TurnoutEditAction::cancelButtonAction(ActionEvent* e)
{
    Turnout* t = (Turnout*) bean;
    t->setFeedbackMode(oldModeSelection);
    t->setTurnoutOperation(oldAutomationSelection);
    BeanEditAction::cancelButtonAction(e);
}


BeanItemPanel* TurnoutEditAction::lock() {
    BeanItemPanel* lock = new BeanItemPanel();
    lock->setName(tr("Lock"));

    lock->addItem(new BeanEditItem(NULL, NULL, tr(" The lock can be set (locked) or unset (unlocked) from a checkbox in the Turnout Table, from a Route or Logix, or from scripts.")));

    QStringList lockOperations = QStringList()
     << bothText << cabOnlyText << pushbutText << noneText;

    lockOperationBox = new JComboBox;
    lockOperationBox->addItems(lockOperations);
    lock->addItem(new BeanEditItem(lockOperationBox, tr("LockMode"), tr("LockModeToolTip")));
//    lockOperationBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (lockOperationBox.getSelectedItem()==(noneText)) {
//                lockBox.setEnabled(false);
//            } else {
//                lockBox.setEnabled(true);
//            }
//        }
//    });
    connect(lockOperationBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_lockBox_currentIndex_changed(QString)));
    lockBox = new JComboBox;
    lockBox->addItems(((Turnout*) bean)->getValidDecoderNames());
    lock->addItem(new BeanEditItem(lockBox, tr("Accessory Decoder"), tr("JMRI needs to know what type of DCC decoder is in use so it can handle the lock properly.")));

//    lock.setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -275341435715029798L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;
//            String lockOpName =  lockOperationBox.getSelectedItem();
//            if (lockOpName==(bothText)) {
//                t.enableLockOperation(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
//            }
//            if (lockOpName==(cabOnlyText)) {
//                t.enableLockOperation(Turnout::CABLOCKOUT, true);
//                t.enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, false);
//            }
//            if (lockOpName==(pushbutText)) {
//                t.enableLockOperation(Turnout::CABLOCKOUT, false);
//                t.enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, true);
//            }

//            String decoderName =  lockBox.getSelectedItem();
//            t.setDecoderName(decoderName);

//        }
//    });
    lock->setSaveItem(new LockSaveItemListener(this));

//    lock.setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 7063263885175963245L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;
//            lockBox.setSelectedItem(t.getDecoderName());
//            lockBox.setEnabled(true);
//            if (t.canLock(Turnout::CABLOCKOUT) && t.canLock(Turnout::PUSHBUTTONLOCKOUT)) {
//                lockOperationBox.setSelectedItem(bothText);
//            } else if (t.canLock(Turnout::PUSHBUTTONLOCKOUT)) {
//                lockOperationBox.setSelectedItem(pushbutText);
//            } else if (t.canLock(Turnout::CABLOCKOUT)) {
//                lockOperationBox.setSelectedItem(cabOnlyText);
//            } else {
//                lockOperationBox.setSelectedItem(noneText);
//                lockBox.setEnabled(false);
//            }
//        }
//    });
 lock->setResetItem(new LockResetItemListener(this));

 bei.append(lock);
 return lock;
}
void TurnoutEditAction::On_lockBox_currentIndex_changed(QString)
{
 if (lockOperationBox->currentText()==(noneText))
 {
  lockBox->setEnabled(false);
 }
 else
 {
  lockBox->setEnabled(true);
 }
}

LockSaveItemListener::LockSaveItemListener(TurnoutEditAction *act)
{
 this->act = act;
}
/*public*/ void LockSaveItemListener::actionPerformed(JActionEvent* /*e*/) {
    Turnout* t = (Turnout*) act->bean;
    QString lockOpName =  act->lockOperationBox->currentText();
    if (lockOpName==(act->bothText)) {
        t->enableLockOperation(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
    }
    if (lockOpName==(act->cabOnlyText)) {
        t->enableLockOperation(Turnout::CABLOCKOUT, true);
        t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, false);
    }
    if (lockOpName==(act->pushbutText)) {
        t->enableLockOperation(Turnout::CABLOCKOUT, false);
        t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, true);
    }

    QString decoderName =  act->lockBox->currentText();
    t->setDecoderName(decoderName);

}
LockResetItemListener::LockResetItemListener(TurnoutEditAction *act)
{
 this->act = act;
}

/*public*/ void LockResetItemListener::actionPerformed(JActionEvent* /*e*/)
{
 Turnout* t = (Turnout*) act->bean;
 act->lockBox->setCurrentIndex(act->lockBox->findText(t->getDecoderName()));
 act->lockBox->setEnabled(true);
 if (t->canLock(Turnout::CABLOCKOUT) && t->canLock(Turnout::PUSHBUTTONLOCKOUT))
 {
  act->lockOperationBox->setCurrentIndex(act->lockOperationBox->findText(act->bothText));
 }
 else if (t->canLock(Turnout::PUSHBUTTONLOCKOUT))
 {
  act->lockOperationBox->setCurrentIndex(act->lockOperationBox->findText(act->pushbutText));
 }
 else if (t->canLock(Turnout::CABLOCKOUT))
 {
  act->lockOperationBox->setCurrentIndex(act->lockOperationBox->findText(act->cabOnlyText));
 }
 else
 {
  act->lockOperationBox->setCurrentIndex(act->lockOperationBox->findText(act->noneText));
  act->lockBox->setEnabled(false);
 }
}

BeanItemPanel* TurnoutEditAction::speed()
{
 BeanItemPanel* speed = new BeanItemPanel();
 speed->setName(tr("Speed"));

 speed->addItem(new BeanEditItem(NULL, NULL, tr("For use with Signalling, set the maximum speed permitted through the turnout.")));

 defaultThrownSpeedText = ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultThrownSpeed());
 defaultClosedSpeedText = ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultClosedSpeed());

 useBlockSpeed = "Use Block Speed";

 speedListClosed.append(defaultClosedSpeedText);
 speedListThrown.append(defaultThrownSpeedText);

 speedListClosed.append(useBlockSpeed);
 speedListThrown.append(useBlockSpeed);

 QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
 for (int i = 0; i < _speedMap.size(); i++)
 {
  if (!speedListClosed.contains(_speedMap.at(i)))
  {
   speedListClosed.append(_speedMap.at(i));
  }
  if (!speedListThrown.contains(_speedMap.at(i)))
  {
   speedListThrown.append(_speedMap.at(i));
  }
 }

 closedSpeedBox = new JComboBox;
 closedSpeedBox->addItems(speedListClosed.toList());
 closedSpeedBox->setEditable(true);

 speed->addItem(new BeanEditItem(closedSpeedBox, tr("Closed Speed"), tr("ClosedSpeedToolTip")));

 thrownSpeedBox = new JComboBox;
 thrownSpeedBox->addItems(speedListThrown.toList());
 thrownSpeedBox->setEditable(true);
 speed->addItem(new BeanEditItem(thrownSpeedBox, tr("Thrown Speed"), tr("The maximum Speed that a train is permited to run when the turnout is set thrown")));

//    speed.setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 8189801856564109719L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;
//            String speed =  closedSpeedBox.getSelectedItem();
//            try {
//                t.setStraightSpeed(speed);
//                if ((!speedListClosed.contains(speed)) && !speed.contains("Global")) {
//                    speedListClosed.add(speed);
//                }
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
//            }
//            speed =  thrownSpeedBox.getSelectedItem();
//            try {
//                t.setDivergingSpeed(speed);
//                if ((!speedListThrown.contains(speed)) && !speed.contains("Global")) {
//                    speedListThrown.add(speed);
//                }
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
//            }
//        }
//    });
    speed->setSaveItem(new SpeedSaveItemListener(this));

//    speed.setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = 3766958497699526365L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            Turnout t = (Turnout) bean;

//            String speed = t.getDivergingSpeed();

//            speedListThrown.remove(defaultThrownSpeedText);
//            defaultThrownSpeedText = ("Use Global " + InstanceManager::turnoutManagerInstance()->getDefaultThrownSpeed());
//            speedListThrown.add(0, defaultThrownSpeedText);
//            if (!speedListThrown.contains(speed)) {
//                speedListThrown.add(speed);
//                thrownSpeedBox.addItem(speed);
//            }
//            thrownSpeedBox.setSelectedItem(speed);

//            speed = t.getStraightSpeed();

//            speedListClosed.remove(defaultClosedSpeedText);
//            defaultClosedSpeedText = ("Use Global " + InstanceManager::turnoutManagerInstance()->getDefaultClosedSpeed());
//            speedListClosed.add(0, defaultClosedSpeedText);
//            if (!speedListClosed.contains(speed)) {
//                speedListClosed.add(speed);
//                closedSpeedBox.addItem(speed);
//            }
//            closedSpeedBox.setSelectedItem(speed);
//        }
//    });
 speed->setResetItem(new SpeedResetItemListener(this));
 bei.append(speed);
 return speed;
}

SpeedSaveItemListener::SpeedSaveItemListener(TurnoutEditAction *act)
{
 this->act = act;
}
/*public*/ void SpeedSaveItemListener::actionPerformed(JActionEvent* /*e*/)
{
 Turnout* t = (Turnout*) act->bean;
 QString speed =  act->closedSpeedBox->currentText();
 try
 {
  t->setStraightSpeed(speed);
  if ((!act->speedListClosed.contains(speed)) && !speed.contains("Global")) {
      act->speedListClosed.append(speed);
  }
 } catch (JmriException ex)
 {
//     JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
 }
 speed =  act->thrownSpeedBox->currentText();
 try {
     t->setDivergingSpeed(speed);
     if ((!act->speedListThrown.contains(speed)) && !speed.contains("Global")) {
         act->speedListThrown.append(speed);
     }
 } catch (JmriException ex) {
//     JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
 }
}
SpeedResetItemListener::SpeedResetItemListener(TurnoutEditAction *act)
{
 this->act = act;
}
/*public*/ void SpeedResetItemListener::actionPerformed(JActionEvent* /*e*/)
{
 Turnout* t = (Turnout*) act->bean;

 QString speed = t->getDivergingSpeed();

 act->speedListThrown.remove(act->speedListThrown.indexOf(act->defaultThrownSpeedText));
 act->defaultThrownSpeedText = ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultThrownSpeed());
 act->speedListThrown.insert(0, act->defaultThrownSpeedText);
 if (!act->speedListThrown.contains(speed)) {
     act->speedListThrown.append(speed);
     act->thrownSpeedBox->addItem(speed);
 }
 act->thrownSpeedBox->setCurrentIndex(act->thrownSpeedBox->findText(speed));

 speed = t->getStraightSpeed();

 act->speedListClosed.remove(act->speedListClosed.indexOf(act->defaultClosedSpeedText));
 act->defaultClosedSpeedText = ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultClosedSpeed());
 act->speedListClosed.insert(0, act->defaultClosedSpeedText);
 if (!act->speedListClosed.contains(speed)) {
     act->speedListClosed.append(speed);
     act->closedSpeedBox->addItem(speed);
 }
 act->closedSpeedBox->setCurrentIndex(act->closedSpeedBox->findText(speed));
}
