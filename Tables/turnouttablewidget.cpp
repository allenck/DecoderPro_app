#include "turnouttablewidget.h"
#include "ui_turnouttablewidget.h"
#include "instancemanager.h"
#include "abstractturnout.h"
#include <QTableWidgetItem>
#include "abstractsensor.h"
#include "addeditdialog.h"
#include "lnturnout.h"
#include "turnoutoperation.h"
#include "turnoutwidget.h"
#include "../LayoutEditor/systemnamecomparator.h"
#include "rosterentry.h"

TurnoutTableWidget::TurnoutTableWidget(int mgrIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnoutTableWidget)
{
 ui->setupUi(this);
 this->mgrIndex = mgrIndex;
 ui->tableWidget->clearContents();
 ui->tableWidget->verticalHeader()->setHidden(true);
 rows.clear();
 deleteMapper = new QSignalMapper(this);
 editMapper = new QSignalMapper(this);
 statemapper = new QSignalMapper(this);
 invertedMapper = new QSignalMapper(this);
 lockedMapper = new QSignalMapper(this);
 modeMapper = new QSignalMapper(this);
 sensor1Mapper = new QSignalMapper(this);
 sensor2Mapper = new QSignalMapper(this);
 automateMapper = new QSignalMapper(this);
 lockModeMapper = new QSignalMapper(this);
 decoderMapper = new QSignalMapper(this);
 closedSpeedMapper = new QSignalMapper(this);
 thrownSpeedMapper = new QSignalMapper(this);
 log = new Logger("TurnoutTableWidget");

 sensorManager = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 AbstractProxyManager* aspm = (AbstractProxyManager*)InstanceManager::sensorManagerInstance();
 connect(aspm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(updateSensors(PropertyChangeEvent*)));
 connect(sensorManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(updateSensors(PropertyChangeEvent*)));

 turnManager = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();

 defaultThrownSpeedText = ("Use Global " + turnManager->getDefaultThrownSpeed());
 defaultClosedSpeedText = ("Use Global " + turnManager->getDefaultClosedSpeed());
 //This following must contain the word Block for a correct match in the abstract turnout
 speedListClosed = /*new QVector<QString>()*/((TurnoutWidget*)parent)->getSpeedListClosed();
 speedListThrown = /*new QVector<QString>()*/((TurnoutWidget*)parent)->getSpeedListThrown();

 if(mgrIndex == -1)
 {
  for(int i=0; i < turnManager->nMgrs(); i++)
  {
   AbstractTurnoutManager* toMgr = (AbstractTurnoutManager*)turnManager->getMgr(i);
   connect(toMgr, SIGNAL(newTurnoutCreated(AbstractTurnoutManager*,Turnout*)), this, SLOT(on_newTurnoutCreated(AbstractTurnoutManager*,Turnout*)));
   //fillTable(toMgr);
   connect(toMgr, SIGNAL(beanDeleted(NamedBean*)), this, SLOT(on_namedBeanDeleted(NamedBean*)));
  }
  fillTable(turnManager->getSystemNameList());
 }
 else
 {
  // Internal only
  AbstractTurnoutManager* toMgr = (AbstractTurnoutManager*)turnManager->getMgr(mgrIndex);
  connect(toMgr, SIGNAL(newTurnoutCreated(AbstractTurnoutManager*,Turnout*)), this, SLOT(on_newTurnoutCreated(AbstractTurnoutManager*,Turnout*)));
  fillTable(toMgr->getSystemNameList());
  connect(toMgr, SIGNAL(beanDeleted(NamedBean*)), this, SLOT(on_namedBeanDeleted(NamedBean*)));
 }
}

TurnoutTableWidget::~TurnoutTableWidget()
{
    delete ui;
}
void TurnoutTableWidget::fillTable(QStringList list)
{
 int row = ui->tableWidget->rowCount();

 ui->tableWidget->setRowCount(row + list.count());
 ui->tableWidget->setAlternatingRowColors(true);
 ui->tableWidget->resizeColumnsToContents();

 foreach (QString sysName, list)
 {
  AbstractTurnout* t = (AbstractTurnout*)turnManager->getBySystemName(sysName);
  createRow(row, t);
  rows.append(t);
  //PropertyChangeListener* listener;
  //t->addPropertyChangeListener(listener = new PropertyChangeListener());
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  row++;
 }
 ui->tableWidget->resizeColumnsToContents();
#if QT_VERSION >= 0x04FF00
 ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setSectionResizeMode(12,QHeaderView::Fixed);
#else
 ui->tableWidget->horizontalHeader()->setResizeMode(2,QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setResizeMode(4,QHeaderView::Fixed);
 ui->tableWidget->horizontalHeader()->setResizeMode(12,QHeaderView::Fixed);
#endif
 connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
 connect(statemapper, SIGNAL(mapped(QObject*)), this, SLOT(on_stateMapper_clicked(QObject*)));
 connect(deleteMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_deleteMapper_clicked(QObject*)));
 connect(editMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_editMapper_clicked(QObject*)));
 connect(invertedMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_invertedMapper_toggled(QObject*)));
 connect(lockedMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_lockedMapper_toggled(QObject*)));
 connect(modeMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_modeMapper_indexChanged(QObject*)));
 connect(sensor1Mapper, SIGNAL(mapped(QObject*)), this, SLOT(on_sensor1Mapper_indexChanged(QObject*)));
 connect(sensor2Mapper, SIGNAL(mapped(QObject*)), this, SLOT(on_sensor2Mapper_indexChanged(QObject*)));
 connect(automateMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_automateMapper_indexChanged(QObject*)));
 connect(lockModeMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_lockedMapper_toggled(QObject*)));
 connect(decoderMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_decoderMapper_indexChanged(QObject*)));
 connect(closedSpeedMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_closedSpeedMapper_indexChanged(QObject*)));
 connect(thrownSpeedMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_thrownSpeedMapper_indexChanged(QObject*)));
}
void TurnoutTableWidget::createRow(int row, AbstractTurnout* t)
{
 QTableWidgetItem* sn = new QTableWidgetItem(t->getSystemName());
 sn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
 ui->tableWidget->setItem(row, SYSNAMECOL,sn);
 QTableWidgetItem* un = new QTableWidgetItem(t->getUserName());
 ui->tableWidget->setItem(row, USERNAMECOL, un);
 QPushButton* btnCommandState = new QPushButton();
 connect(btnCommandState, SIGNAL(clicked()), statemapper, SLOT(map()));
 statemapper->setMapping(btnCommandState, t);
 ui->tableWidget->setCellWidget(row, VALUECOL, btnCommandState);
 switch(t->getCommandedState())
 {
  default:
  case Turnout::UNKNOWN:
   btnCommandState->setText(tr("Unknown"));
   break;
  case Turnout::CLOSED:
   btnCommandState->setText(tr("Closed"));
   break;
  case Turnout::THROWN:
   btnCommandState->setText(tr("Thrown"));
   break;
 case Turnout::INCONSISTENT:
   btnCommandState->setText(tr("InConsistent"));
 }
// int state = t->getCommandedState();
// if (state==Turnout::CLOSED) (t->setCommandedState(Turnout::THROWN));
// else t->setCommandedState(Turnout::CLOSED);

 QTableWidgetItem* cmt = new QTableWidgetItem(t->getComment());
 ui->tableWidget->setItem(row, COMMENTCOL, cmt);
 //connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 QPushButton* btnDelete = new QPushButton();
 connect(btnDelete, SIGNAL(clicked()), deleteMapper, SLOT(map()));
 deleteMapper->setMapping(btnDelete,t);
 btnDelete->setText(tr("Delete"));
 ui->tableWidget->setCellWidget(row,DELETECOL,btnDelete);

 QCheckBox* chkInverted = new QCheckBox();
 if(t->canInvert())
 {
  chkInverted->setChecked(t->getInverted());
  connect(chkInverted, SIGNAL(toggled(bool)), invertedMapper, SLOT(map()));
  invertedMapper->setMapping(chkInverted, t);
 }
 else
  chkInverted->setEnabled(false);
 ui->tableWidget->setCellWidget(row,INVERTCOL,chkInverted);

 QCheckBox* chkLocked = new QCheckBox();
 chkLocked->setChecked(t->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT));
 connect(chkLocked, SIGNAL(toggled(bool)), lockedMapper, SLOT(map()));
 lockedMapper->setMapping(chkLocked, t);
 ui->tableWidget->setCellWidget(row,LOCKCOL,chkLocked);

 // Show feedback information
 QString commandedState;
 switch(t->getCommandedState())
 {
 case Turnout::THROWN:
  commandedState = tr("Thrown");
  break;
 case Turnout::CLOSED:
  commandedState = tr("Closed");
  break;
 case Turnout::INCONSISTENT:
  commandedState = tr("Inconsistent");
  break;
 default:
  commandedState = tr("Unknown");
  break;
 }

 QTableWidgetItem* feedback = new QTableWidgetItem(commandedState);
 ui->tableWidget->setItem(row, KNOWNCOL, feedback);

 ui->tableWidget->setCellWidget(row, MODECOL, cbMode(t));

 ui->tableWidget->setCellWidget(row,SENSOR1COL,cbSensor(t,0));

 ui->tableWidget->setCellWidget(row,SENSOR2COL,cbSensor(t,1));

 ui->tableWidget->setCellWidget(row, OPSONOFFCOL, cbAutomate(t));

 QPushButton* btnEdit = new QPushButton("Edit");
 connect(btnEdit, SIGNAL(clicked()), editMapper, SLOT(map()));
 editMapper->setMapping(btnEdit, t);
 ui->tableWidget->setCellWidget(row, OPSEDITCOL, btnEdit);

 // Lock information
 QStringList lockList;
 lockList << tr("Both") << tr("Cab only") << tr("Pushbutton") << tr("None");
 QComboBox* cbLock = new QComboBox();
 cbLock->addItems(lockList);
 if (t->canLock(Turnout::CABLOCKOUT) && t->canLock(Turnout::PUSHBUTTONLOCKOUT))
 {
  cbLock->setCurrentIndex(0);
 }
 else if (t->canLock(Turnout::PUSHBUTTONLOCKOUT))
 {
  cbLock->setCurrentIndex(2);
 }
 else if (t->canLock(Turnout::CABLOCKOUT))
 {
  cbLock->setCurrentIndex(1);
 }
 else
 {
  cbLock->setCurrentIndex(3);
 }
 connect(cbLock, SIGNAL(currentIndexChanged(int)), lockModeMapper, SLOT(map()));
 lockModeMapper->setMapping(cbLock, t);
 ui->tableWidget->setCellWidget(row,LOCKOPRCOL,cbLock);

 QStringList decoderList = t->getValidDecoderNames();
 //decoderList << tr("None") << tr("NCE_RevC") << tr("CVP_AD4_1")<< tr("CVP_AD4_2");
 QComboBox* cbDecoder = new QComboBox();
 cbDecoder->addItems(decoderList);
 cbDecoder->setCurrentIndex(cbDecoder->findText(t->getDecoderName()));
 connect(cbDecoder, SIGNAL(currentIndexChanged(int)), decoderMapper, SLOT(map()));
 decoderMapper->setMapping(cbDecoder, t);
 QString decoderName = t->getDecoderName();
 cbDecoder->setCurrentIndex(cbDecoder->findText(decoderName));
 ui->tableWidget->setCellWidget(row,LOCKDECCOL,cbDecoder);

 // Turnout speed details
 ui->tableWidget->setCellWidget(row, STRAIGHTCOL, cbSpeed(t, true));

 ui->tableWidget->setCellWidget(row, DIVERGCOL, cbSpeed(t, false));
}
void TurnoutTableWidget::updateRow(int row, AbstractTurnout* t)
{
 QPushButton* btnCommandState = (QPushButton*)ui->tableWidget->cellWidget(row, VALUECOL);
 QTableWidgetItem* feedback = (QTableWidgetItem*)ui->tableWidget->item(row, KNOWNCOL);
 int knownState = t->getKnownState();
 switch(knownState)
 {
  default:
  case Turnout::UNKNOWN:
   feedback->setText(tr("Unknown"));
   break;
  case Turnout::CLOSED:
   feedback->setText(tr("Closed"));
   break;
  case Turnout::THROWN:
   feedback->setText(tr("Thrown"));
   break;
 case Turnout::INCONSISTENT:
   feedback->setText(tr("InConsistent"));
   break;
 }

 int commandedState = t->getCommandedState();
 switch(commandedState)
 {
  default:
  case Turnout::UNKNOWN:
   btnCommandState->setText(tr("Unknown"));
   break;
  case Turnout::CLOSED:
   btnCommandState->setText(tr("Closed"));
   break;
  case Turnout::THROWN:
   btnCommandState->setText(tr("Thrown"));
   break;
 }

 QTableWidgetItem* cmt = ui->tableWidget->item(row, COMMENTCOL);
 cmt->setText(t->getComment());

 QCheckBox* chkInverted = (QCheckBox*)ui->tableWidget->cellWidget(row, INVERTCOL);
 chkInverted->setChecked(t->getInverted());

 QCheckBox* chkLocked = (QCheckBox*)ui->tableWidget->cellWidget(row, LOCKCOL);
 chkLocked->setChecked(t->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT));

 QComboBox* cbClosed = (QComboBox*)ui->tableWidget->cellWidget(row, STRAIGHTCOL);
 cbClosed->clear();
 cbClosed->addItems(speedListClosed->toList());
 QString s = t->getStraightSpeed();
 for(int i = 0; i < speedListClosed->count(); i++)
 {
  if(speedListClosed->at(i).contains(s))
  {
   cbClosed->setCurrentIndex(i);
   break;
  }
 }

 QComboBox* cbThrown = (QComboBox*)ui->tableWidget->cellWidget(row, DIVERGCOL);
 cbThrown->clear();
 cbThrown->addItems(speedListThrown->toList());
 s = t->getDivergingSpeed();
 for(int i = 0; i < speedListThrown->count(); i++)
 {
  if(speedListThrown->at(i).contains(s))
  {
   cbThrown->setCurrentIndex(i);
   break;
  }
 }

 QComboBox* cbAutomate = (QComboBox*)ui->tableWidget->cellWidget(row,OPSONOFFCOL);

 QComboBox* cbMode =(QComboBox*)ui->tableWidget->cellWidget(row, MODECOL);
 cbMode->clear();
 cbMode->addItems(t->getValidFeedbackNames());
 int index = cbMode->findText(t->getFeedbackModeName());
 if(index > -1)
  cbMode->setCurrentIndex(index);

 QStringList list = sensorManager->getSystemNameList();
 qSort(list.begin(), list.end(), SystemNameComparator::compare);
 QComboBox* cbSensor1 =(QComboBox*)ui->tableWidget->cellWidget(row, SENSOR1COL);
 cbSensor1->clear();
 cbSensor1->addItem("");
 cbSensor1->addItems(list);
 Sensor* sensor;
 int mode = t->getFeedbackMode();
 sensor = t->getFirstSensor();
 if(mode == Turnout::ONESENSOR)
 {
  if(sensor != NULL)
   cbSensor1->setCurrentIndex(cbSensor1->findText(((AbstractSensor*)sensor)->getSystemName()));
 }
 else
  cbSensor1->setEnabled(false);

 QComboBox* cbSensor2 =(QComboBox*)ui->tableWidget->cellWidget(row, SENSOR2COL);
 cbSensor2->clear();
 cbSensor2->addItem("");
 cbSensor2->addItems(list);
 //Sensor* sensor;
 mode = t->getFeedbackMode();
 sensor = t->getFirstSensor();
 if( mode == Turnout::TWOSENSOR)
 {
  if(sensor != NULL)
   cbSensor2->setCurrentIndex(cbSensor2->findText(((AbstractSensor*)sensor)->getSystemName()));
 }
 else
  cbSensor2->setEnabled(false);

 QComboBox* cbLock =(QComboBox*)ui->tableWidget->cellWidget(row, LOCKOPRCOL);

 QComboBox* cbDecoder =(QComboBox*)ui->tableWidget->cellWidget(row, LOCKDECCOL);
 cbDecoder->setCurrentIndex(cbDecoder->findText(t->getDecoderName()));

}

QComboBox* TurnoutTableWidget::cbMode(AbstractTurnout* t)
{
 QComboBox* cbMode = new QComboBox();
 //QStringList list;
 cbMode->addItems(t->getValidFeedbackNames());
 cbMode->setCurrentIndex(cbMode->findText(t->getFeedbackModeName()));
 connect(cbMode, SIGNAL(currentIndexChanged(int)), modeMapper, SLOT(map()));
 modeMapper->setMapping(cbMode, t);
 return cbMode;
}

QComboBox* TurnoutTableWidget::cbSensor(AbstractTurnout* t, int index)
{
 QComboBox* cbSensor = new QComboBox();
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 QStringList list = mgr->getSystemNameList();
 cbSensor->addItem("");
 cbSensor->addItems(list);
 Sensor* sensor;
 int mode = t->getFeedbackMode();
 if(index == 0)
 {
  sensor = t->getFirstSensor();
  connect(cbSensor, SIGNAL(currentIndexChanged(int)), sensor1Mapper, SLOT(map()));
  sensor1Mapper->setMapping(cbSensor, t);
 }
 else
 {
  sensor = t->getSecondSensor();
  connect(cbSensor, SIGNAL(currentIndexChanged(int)), sensor2Mapper, SLOT(map()));
  sensor2Mapper->setMapping(cbSensor, t);
 }

 if((mode == Turnout::ONESENSOR && index == 0 || mode == Turnout::TWOSENSOR && index == 1)|| mode == Turnout::INDIRECT)
 {
  if(sensor != NULL)
   cbSensor->setCurrentIndex(cbSensor->findText(((AbstractSensor*)sensor)->getSystemName()));
 }
 else
  cbSensor->setEnabled(false);
 return cbSensor;
}

void TurnoutTableWidget::showFeedbackInfo(bool bVisible)
{
 for(int col = 7; col <=12; col ++)
  ui->tableWidget->setColumnHidden(col,!bVisible);
}
void TurnoutTableWidget::showLockInformation(bool bVisible)
{
 for(int col = 13; col <=14; col ++)
  ui->tableWidget->setColumnHidden(col,!bVisible);
}
void TurnoutTableWidget::showTurnoutSpeedDetails(bool bVisible)
{
 for(int col =15; col <=16; col ++)
 ui->tableWidget->setColumnHidden(col,!bVisible);
}

QComboBox* TurnoutTableWidget::cbAutomate(AbstractTurnout* t)
{
 QComboBox* box = new QComboBox();
 QStringList list;
 list << tr("Off" )<< tr("Use Global Default") << tr("No Feedback");
 box->addItems(list);
 updateAutomationBox(t,box);
 connect(box, SIGNAL(currentIndexChanged(int)), automateMapper, SLOT(map()));
 automateMapper->setMapping(box, t);
 TurnoutOperation* turnoutOperation = t->getTurnoutOperation();
// if(turnoutOperation != NULL)
// {
//  QString toName = turnoutOperation->getName();
// }
 if (t->getInhibitOperation())
 {
  box->setCurrentIndex(0);
 }
 else if (turnoutOperation == NULL)
 {
  box->setCurrentIndex(0);
 }
 else if (turnoutOperation->isNonce())
 {
  box->setCurrentIndex(2);
 }
 else
 {
  box->setCurrentIndex(box->findText(turnoutOperation->getName()));
 }
 return box;
}
/**
 * Add the content and make the appropriate selection to a combox box for a turnout's
 * automation choices
 * @param t	turnout
 * @param cb	the JComboBox
 */
/*public*/ /*static*/ void TurnoutTableWidget::updateAutomationBox(AbstractTurnout* t, QComboBox* cb)
{
 Logger* log = new Logger("TurnoutTableWidget::updateAutomationBox");
 //log->setDebugEnabled(true);
 QList<TurnoutOperation*> ops = TurnoutOperationManager::getInstance()->getTurnoutOperations();
 cb->clear();
 QVector<QString>* strings = new QVector<QString>(/*20*/);
 QVector<QString>* defStrings = new QVector<QString>(/*20*/);
 if(log->isDebugEnabled()) log->debug("start "+QString::number(ops.length()));
 for (int i=0; i<ops.length(); ++i)
 {
  if(log->isDebugEnabled()) log->debug(tr("isDef ")+(ops.at(i)->isDefinitive()?"Yes":"No")+
                                           " mFMM "+(ops.at(i)->matchFeedbackMode(t->getFeedbackMode())?"Yes":"No")+
                                           " isNonce "+(ops.at(i)->isNonce()?"Yes":"No"));
  if (!ops.at(i)->isDefinitive()
            && ops.at(i)->matchFeedbackMode(t->getFeedbackMode())
            && !ops.at(i)->isNonce())
  {
   strings->append(ops.at(i)->getName());
  }
 }
 if(log->isDebugEnabled()) log->debug("end");
 for (int i=0; i<ops.length(); ++i)
 {
  if (ops.at(i)->isDefinitive()
            && ops.at(i)->matchFeedbackMode(t->getFeedbackMode()))
  {
   defStrings->append(ops.at(i)->getName());
  }
 }
//    java.util.Collections.sort(strings);
//    java.util.Collections.sort(defStrings);
 strings->insert(0,tr("Off"));
 strings->insert(1,tr("Use Global Default"));
 for (int i=0; i<defStrings->size(); ++i)
 {
  try
  {
   strings->append(defStrings->at(i));
  }
  catch(ArrayIndexOutOfBoundsException obe)
  {
            //	           strings.insertElementAt(defStrings.elementAt(i),i+2);
  }
 }
 for (int i=0; i<strings->size(); ++i)
 {
  cb->addItem(strings->at(i));
 }
 if (t->getInhibitOperation())
 {
  cb->setCurrentIndex(0);
 }
 else if (t->getTurnoutOperation() == NULL)
 {
  cb->setCurrentIndex(0);
 }
 else if (t->getTurnoutOperation()->isNonce())
 {
  cb->setCurrentIndex(2);
 }
 else
 {
  cb->setEditText(t->getTurnoutOperation()->getName());
 }
}

QComboBox* TurnoutTableWidget::cbSpeed(AbstractTurnout* t, bool bClosed)
{
 QComboBox* box = new QComboBox();
// QStringList list;
// list << tr("Use Global Normal") << tr("Use Block Speed") << tr("Maximum") << tr("Normal") << tr("Limited") << tr("Medium") << tr("Slow") << tr("Restricted");
// box->addItems(list);
 if(bClosed)
  box->addItems(speedListClosed->toList());
 else
  box->addItems(speedListThrown->toList());
 QString s = bClosed?t->getStraightSpeed():t->getDivergingSpeed();
 box->setCurrentIndex(box->findText(s));
 if(bClosed)
 {
  connect(box, SIGNAL(currentIndexChanged(int)), closedSpeedMapper, SLOT(map()));
  closedSpeedMapper->setMapping(box, t);
 }
 else
 {
  connect(box, SIGNAL(currentIndexChanged(int)), thrownSpeedMapper, SLOT(map()));
  thrownSpeedMapper->setMapping(box, t);
 }
 return box;
}
void TurnoutTableWidget::propertyChange(PropertyChangeEvent *e)
{
 log->debug("property change received" + e->toString());
 AbstractTurnout* tTarget = qobject_cast<AbstractTurnout*>(e->source);
 for(int row =0; row<rows.count(); row++)
 {
  AbstractTurnout* t = rows.at(row);
  if(t == tTarget)
  {
   if (e->getPropertyName()==("DefaultTurnoutClosedSpeedChange"))
   {
    updateClosedList();
   }
   else if (e->getPropertyName()==("DefaultTurnoutThrownSpeedChange"))
   {
    updateThrownList();
   }
   else
   {
    if(e->getPropertyName() == "feedbackchange")
    {
     QString s = t->getFeedbackModeName();
     QComboBox* cbMode = (QComboBox*)ui->tableWidget->cellWidget(row, MODECOL);
     cbMode->setCurrentIndex(cbMode->findText(s));
    }\
    else if(e->getPropertyName() == "KnownState")
    {
     //QTableWidgetItem* feedback = ui->tableWidget->item(row, VALUECOL);
     QPushButton* feedback = (QPushButton*)ui->tableWidget->cellWidget(row, VALUECOL);
     switch(e->getNewValue().toInt())
     {
      default:
      case Turnout::UNKNOWN:
       feedback->setText(tr("Unknown"));
       break;
      case Turnout::CLOSED:
       feedback->setText(tr("Closed"));
       break;
      case Turnout::THROWN:
       feedback->setText(tr("Thrown"));
       break;
     case Turnout::INCONSISTENT:
       feedback->setText(tr("InConsistent"));
       break;
     }
    }
    else if(e->getPropertyName() == "CommandedState")
    {
     QPushButton* btnCommandState = (QPushButton*)ui->tableWidget->cellWidget(row, VALUECOL);
     switch(e->getNewValue().toInt())
     {
      default:
      case Turnout::UNKNOWN:
       btnCommandState->setText(tr("Unknown"));
       break;
      case Turnout::CLOSED:
       btnCommandState->setText(tr("Closed"));
       break;
      case Turnout::THROWN:
       btnCommandState->setText(tr("Thrown"));
       break;
     }
    }
    else if(e->getPropertyName() == "locked")
    {
     QCheckBox* chkLock = (QCheckBox*)ui->tableWidget->cellWidget(row, LOCKCOL);
     chkLock->setChecked(e->getNewValue().toBool());
    }
    else if(e->getPropertyName() == "inverted")
    {
     QCheckBox* chkInverted = (QCheckBox*)ui->tableWidget->cellWidget(row, INVERTCOL);
     chkInverted->setChecked(e->getNewValue().toBool());
    }
    else if(e->getPropertyName() == "TurnoutOperationState")
    {
     QComboBox* cbAutomate = (QComboBox*)ui->tableWidget->cellWidget(row, OPSONOFFCOL);
     TurnoutOperation* top = VPtr<TurnoutOperation>::asPtr(e->getNewValue());
     //qDebug() << "top = "+ top->getName();
     if (t->getInhibitOperation())
     {
      cbAutomate->setCurrentIndex(0);
     }
     else if (top == NULL)
     {
      cbAutomate->setCurrentIndex(0);
     }
     else if (top->isNonce())
     {
      cbAutomate->setCurrentIndex(2);
     }
     else
     {
      cbAutomate->setCurrentIndex(cbAutomate->findText(top->getName()));
     }
    }
    else if (e->getPropertyName() == "TurnoutStraightSpeedChange")
    {
     QComboBox* cbStraightSpeed = (QComboBox*)ui->tableWidget->cellWidget(row, STRAIGHTCOL);
     cbStraightSpeed->setCurrentIndex(cbStraightSpeed->findText(e->getNewValue().toString()));
    }
    else if (e->getPropertyName() == "TurnoutDivergingSpeedChange")
    {
     QComboBox* cbDivergingSpeed = (QComboBox*)ui->tableWidget->cellWidget(row, DIVERGCOL);
     cbDivergingSpeed->setCurrentIndex(cbDivergingSpeed->findText(e->getNewValue().toString()));
    }
    else if(e->getPropertyName() == "Comment")
    {
     QTableWidgetItem* comment = ui->tableWidget->item(row, COMMENTCOL);
     comment->setText(e->getNewValue().toString());
    }
    else if(e->getPropertyName() == "UserName")
    {
     QTableWidgetItem* userName = ui->tableWidget->item(row, USERNAMECOL);
     userName->setText(e->getNewValue().toString());
    }
    else
     updateRow(row, t);
    break;
   }
  }
 }
}
void TurnoutTableWidget::on_newTurnoutCreated(AbstractTurnoutManager* tMgr,Turnout *t)
{
 if(mgrIndex < 0)
 {
  for(int i=0; i < turnManager->nMgrs(); i++)
  {
   if(turnManager->getMgr(i) == tMgr)
   {
    int row = rows.count();
    ui->tableWidget->setRowCount(row + 1);
    createRow(row, (AbstractTurnout*)t);
    ui->tableWidget->setRowHidden(row,false);
    rows.append((AbstractTurnout*)t);
   }
  }
 }
 else
 {
  if(tMgr == turnManager->getMgr(mgrIndex))
  {
   int row = rows.count();
   ui->tableWidget->setRowCount(row + 1);
   createRow(row, (AbstractTurnout*)t);
   ui->tableWidget->setRowHidden(row,false);
   rows.append((AbstractTurnout*)t);
  }
 }
}
void TurnoutTableWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(rows.isEmpty()) return;
 if(row == rows.count()) return;
 AbstractTurnout* t = rows.at(row);
 switch(col)
 {
  case USERNAMECOL: // user name
   t->setUserName(ui->tableWidget->item(row,col)->text());
   break;
  case COMMENTCOL:
   t->setComment(ui->tableWidget->item(row,col)->text());
   break;
 case KNOWNCOL:
     // Show feedback information
     QString commandedState;
     switch(t->getCommandedState())
     {
     case Turnout::THROWN:
      commandedState = tr("Thrown");
      break;
     case Turnout::CLOSED:
      commandedState = tr("Closed");
      break;
     case Turnout::INCONSISTENT:
      commandedState = tr("Inconsistent");
      break;
     default:
      commandedState = tr("Unknown");
      break;
     }
     ui->tableWidget->item(row,col)->setText(commandedState);
 }
}
void TurnoutTableWidget::on_stateMapper_clicked(QObject* o) // clickOn
{
 LnTurnout* t = (LnTurnout*)o;
 int state = t->getCommandedState();
 if(state == Turnout::CLOSED) // 0x02
  t->setCommandedState(Turnout::THROWN); // 0x04
 else
  t->setCommandedState(Turnout::CLOSED);
}
void TurnoutTableWidget::on_deleteMapper_clicked(QObject *o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  rows.remove(row);
  ui->tableWidget->removeRow(row);
  turnManager->deregister(t);
 }
}
void TurnoutTableWidget::on_namedBeanDeleted(NamedBean *b)
{
 if(rows.contains((AbstractTurnout*)b))
 {
  int row = rows.indexOf((AbstractTurnout*)b);
  if(row >= 0)
  {
   rows.remove(row);
   ui->tableWidget->removeRow(row);
  }
 }
}
void TurnoutTableWidget::on_invertedMapper_toggled(QObject *o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  if(t->canInvert())
   t->setInverted(((QCheckBox*)ui->tableWidget->cellWidget(row,INVERTCOL))->isChecked());
 }
}
void TurnoutTableWidget::on_lockedMapper_toggled(QObject *o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  bool b =((QCheckBox*)ui->tableWidget->cellWidget(row,LOCKCOL))->isChecked();
  t->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT,	b);
 }
}
void TurnoutTableWidget::on_editMapper_clicked(QObject *o)
{
 AddEditDialog* dlg = new AddEditDialog("Turnouts", o, this);
 dlg->exec();
}

void TurnoutTableWidget::on_modeMapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, MODECOL);
  if(cb != NULL)
  {
   QString feedbackMode = cb->currentText();
   if(feedbackMode.isEmpty())
    return;
   t->setFeedbackMode(feedbackMode);
   int mode = t->getFeedbackMode();
   QComboBox* cbSensor1 = (QComboBox*)ui->tableWidget->cellWidget(row,SENSOR1COL);
   QComboBox* cbSensor2 = (QComboBox*)ui->tableWidget->cellWidget(row,SENSOR2COL);
   if(mode == Turnout::DIRECT)
   {
    cbSensor1->setCurrentIndex(0);
    cbSensor1->setEnabled(false);
    cbSensor2->setCurrentIndex(0);
    cbSensor2->setEnabled(false);
   }
   else
   if(mode == Turnout::ONESENSOR)
   {
    cbSensor1->setEnabled(true);
    cbSensor2->setCurrentIndex(0);
    cbSensor2->setEnabled(false);
   }
   else
   {
    cbSensor1->setEnabled(true);
    cbSensor2->setEnabled(true);
   }
  }
 }
}

void TurnoutTableWidget::on_sensor1Mapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, SENSOR1COL);
  if(cb != NULL)
  {
   QString sensorName = cb->currentText();
   t->provideFirstFeedbackSensor(sensorName);
  }
 }
}

void TurnoutTableWidget::on_sensor2Mapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, SENSOR2COL);
  if(cb != NULL)
  {
   QString sensorName = cb->currentText();
   t->provideSecondFeedbackSensor(sensorName);
  }
 }
}

void TurnoutTableWidget::on_automateMapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, OPSONOFFCOL);
  if(cb != NULL)
  {
   //list << tr("Off" )<< tr("Use Global Default") << tr("No Feedback");
   setTurnoutOperation(t,cb);
  }
 }
}
/**
 * set the turnout's operation info based on the contents of the combo box
 * @param t	turnout
 * @param cb JComboBox
 */
/*private*/ void TurnoutTableWidget::setTurnoutOperation(AbstractTurnout* t, QComboBox* cb)
{
 switch (cb->currentIndex())
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
  t->setTurnoutOperation(TurnoutOperationManager::getInstance()->getOperation(cb->currentText()));
  break;
 }
}
void TurnoutTableWidget::on_lockModeMapper_indexChanged(QObject* o)
{
 // lockList << tr("Both") << tr("Cab only") << tr("Pushbutton") << tr("None");
 int turnoutLockout = 0;
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  turnoutLockout = getLockoutMode(row);
  bool bLocked = t->getLocked(turnoutLockout);
  QCheckBox* chk = (QCheckBox*)ui->tableWidget->cellWidget(row, LOCKCOL);
  chk->setChecked(bLocked);
  t->enableLockOperation(turnoutLockout,true);
 }
}
int TurnoutTableWidget::getLockoutMode(int row)
{
 int turnoutLockout = Turnout::CABLOCKOUT | Turnout::PUSHBUTTONLOCKOUT;;
 QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, LOCKOPRCOL);
 if(cb != NULL)
 {
  int index = cb->currentIndex();
  switch(index)
  {
  case 0: // both
   turnoutLockout = Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT;
   break;
  case 1:
   turnoutLockout = Turnout::CABLOCKOUT;
   break;
  case 2:
   turnoutLockout = Turnout::PUSHBUTTONLOCKOUT;
   break;
  default:
   turnoutLockout = 0;
   break;
  }
 }
 return turnoutLockout;
}

void TurnoutTableWidget::on_decoderMapper_indexChanged(QObject* o)
{
 //  decoderList << tr("None") << tr("NCE_RevC") << tr("CVP_AD4_1")<< tr("CVP_AD4_2");
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, 14);
  if(cb != NULL)
  {
   QString decoderName = cb->currentText();
   t->setDecoderName(decoderName);
  }
 }
}

void TurnoutTableWidget::on_closedSpeedMapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, 15);
  if(cb != NULL)
  {
   QString s = cb->currentText();
   if(!s.isEmpty())
    t->setStraightSpeed(s);
  }
 }
}
void TurnoutTableWidget::on_thrownSpeedMapper_indexChanged(QObject* o)
{
 AbstractTurnout* t = (AbstractTurnout*)o;
 int row = rows.indexOf(t);
 if(row >= 0)
 {
  QComboBox* cb = (QComboBox*)ui->tableWidget->cellWidget(row, 16);
  if(cb != NULL)
  {
   QString s = cb->currentText();
   if(!s.isEmpty())
    t->setDivergingSpeed(s);
  }
 }
}
/*private*/ void TurnoutTableWidget::updateClosedList()
{
 speedListClosed->remove(speedListClosed->indexOf(defaultClosedSpeedText));
 defaultClosedSpeedText = ("Use Global " + turnManager->getDefaultClosedSpeed());
 speedListClosed->insert(0, defaultClosedSpeedText);
//    m.fireTableDataChanged();
}

/*private*/ void TurnoutTableWidget::updateThrownList()
{
 speedListThrown->remove(speedListThrown->indexOf(defaultThrownSpeedText));
 defaultThrownSpeedText = ("Use Global " + turnManager->getDefaultThrownSpeed());
 speedListThrown->insert(0, defaultThrownSpeedText);
//    m.fireTableDataChanged();
}

/*private*/ void TurnoutTableWidget::updateSensors(PropertyChangeEvent* e)
{
 QStringList list = sensorManager->getSystemNameList();
 qSort(list.begin(), list.end(), SystemNameComparator::compare);

 for(int row = 0; row < ui->tableWidget->rowCount(); row++)
 {
  QComboBox* cbSensor1 = (QComboBox*)ui->tableWidget->cellWidget(row,SENSOR1COL);
  AbstractTurnout* t = rows.at(row);

  cbSensor1->clear();
  cbSensor1->addItem("");
  cbSensor1->addItems(list);
  Sensor* sensor;
  int mode = t->getFeedbackMode();
  sensor = t->getFirstSensor();
  if(mode == Turnout::ONESENSOR)
  {
   if(sensor != NULL)
    cbSensor1->setCurrentIndex(cbSensor1->findText(((AbstractSensor*)sensor)->getSystemName()));
  }
  else
   cbSensor1->setEnabled(false);

  QComboBox* cbSensor2 =(QComboBox*)ui->tableWidget->cellWidget(row, SENSOR2COL);
  cbSensor2->clear();
  cbSensor2->addItem("");
  cbSensor2->addItems(list);
  //Sensor* sensor;
  mode = t->getFeedbackMode();
  sensor = t->getFirstSensor();
  if( mode == Turnout::TWOSENSOR)
  {
   if(sensor != NULL)
    cbSensor2->setCurrentIndex(cbSensor2->findText(((AbstractSensor*)sensor)->getSystemName()));
  }
  else
   cbSensor2->setEnabled(false);
 }
}
