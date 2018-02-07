#include "locoioframe.h"
#include "ui_locoioframe.h"
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QMessageBox>
#include "specialport.h"
#include <QStringList>
#include <QMenu>
#include "commentsdialog.h"
#include "locoiomodules.h"
#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include <QMenuBar>
#include "windowmenu.h"
#include <QStatusBar>
#include "menu.h"

LocoIOFrame::LocoIOFrame(LocoIOAddress* address, LnTrafficController* tc, bool /*bHex*/, Sql* sql, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LocoIOFrame)
{
    ui->setupUi(this);

    createActions();

    ui->btnSave->setEnabled(false);
    actSaveModule->setEnabled(false);

    ui->btnChangeAddress->setEnabled(false);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableCustomContextMenuRequested(QPoint)));
    log = new Logger("LocoIOFrame", this);
    msg = new QStringList();
    bIsBooster = false;
    bIsServo = false;
    bLoadCB = false;
    bReadingAll = bWritingAll = false;
    cfg = 0;
    for(int i =0; i < 16; i++)
     *msg << "";
    labels <<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<tr("Port Definition");
    servoLabels <<"1"<<"2"<<"3"<<"4"<<"Servo"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<tr("Port Definition");
    boosterLabels <<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"Booster"<<tr("Port Definition");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    rxHex.setPattern("^[0-9a-f]{1,2}\\/[0-9a-f]{1,2}");
    rxHex.setCaseSensitivity(Qt::CaseInsensitive);
    rxDec.setPattern("^[0-9]{1,3}\\/[0-9]{1,3}");
    rv = new  AddressValidator(rxHex);
    ui->edNewAddr->setValidator(rv);
    connect(ui->edNewAddr, SIGNAL(textEdited(QString)), this, SLOT(on_edNewAddr_editTextChanged(QString)));
    connect(ui->edNewAddr, SIGNAL(editingFinished()), this, SLOT(on_edNewAddr_editingFinished()));
    //this->locobufferadapter = locobufferadapter;
    this->tc = tc;
    this->sql = sql;
    _address = address;
    locoIOModules = LocoIOModules::instance();
    p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");
    displayHexCheck = QString(this->metaObject()->className())+".HexCheck";
    allowEdits = QString(this->metaObject()->className())+".AllowEdit";


    connect(locoIOModules, SIGNAL(probeCompleted(QList<LocoIOAddress*>)), this, SLOT(onProbeCompleted(QList<LocoIOAddress*>)));
   // if(data == NULL)
   //  this->data = new LocoIOData(0x51, 0x1,/*(LnTrafficController*)this->locobufferadapter->packetizer()*/tc);
   // else
   //  //this->data = new LocoIOData(data->getUnitAddress(), data->getUnitSubAddress(), data->getTrafficController());
   //  this->data = new LocoIOData(*data);
    this->data = new LocoIOData(_address, this->tc);
    if(this->sql == NULL)\
    {
     this->sql = new Sql(data, this);
     connect(this->sql, SIGNAL(error(QString)),this, SLOT(error(QString)));
    }
    servoWidget =NULL;
    servoRegistersWidget = NULL;
    setWindowTitle(createTitle());
   //    unitAddr = 0x151;
   //    unitSubAddr = 1;

   // unitAddr = this->data->getUnitAddress();
   // unitSubAddr = this->data->getUnitSubAddress();
    ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(), 0, 16));
    //setupCbAddr();
    //ui->chkHex->setChecked(bHex);
    ui->chkHex->setChecked(p->getSimplePreferenceState(displayHexCheck));
    on_chkHex_toggled(ui->chkHex->isChecked());
    ui->chkAllowEdit->setChecked(p->getSimplePreferenceState(displayHexCheck));
    on_chkAllowEdit_toggled(ui->chkAllowEdit->isChecked());


    bDirty = false;

    connect(this->data, SIGNAL(notifyPropertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
    connect(this->data, SIGNAL(dirtyChanged(bool)), this, SLOT(setDirty(bool)));
    connect(this->data, SIGNAL(IOComplete(QList<int>*)),this, SLOT(onIOComplete(QList<int>*)));
    connect(this->data, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(onIOCompleteX2(QList<int>*)));
    connect(this->data, SIGNAL(IOCompleteServo()), this, SLOT(onIOCompleteServo()));
    connect(this->data, SIGNAL(readAllComplete()), this, SLOT(onReadWriteAllComplete()));
    connect(this->data, SIGNAL(writeAllComplete()),this, SLOT(onReadWriteAllComplete()));
    connect(this->tc,SIGNAL(messageProcessed(LocoNetMessage*,bool)),this, SLOT(onMessageReceived(LocoNetMessage*,bool)));
    connect(this->data, SIGNAL(configRead(int)), this, SLOT(onConfigRead(int)));
    this->data->getConfig();
    connect(this->data, SIGNAL(probeCompleted(QList<LocoIOAddress*>)), this, SLOT(onProbeCompleted(QList<LocoIOAddress*>)));
    connect(this->data, SIGNAL(ioAborted()), this, SLOT(onIOAborted()));
   //    on_btnProbe_clicked();
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenuRequested(QPoint)));
    connect(this->data, SIGNAL(IOComplete7D()), this, SLOT(onIOCompleted7D()));
    QSignalMapper* mapper = new QSignalMapper;
    mapper->setMapping(ui->rbCheckAll, 0);
    connect(ui->rbCheckAll, SIGNAL(toggled(bool)), mapper, SLOT(map()));
    mapper->setMapping(ui->rbCheckBlockAndPoints,1);
    connect(ui->rbCheckBlockAndPoints, SIGNAL(toggled(bool)), mapper, SLOT(map()));
    mapper->setMapping(ui->rbCheckBlock,2);
    connect(ui->rbCheckBlock, SIGNAL(toggled(bool)), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(onInputStatusRbChanged(int)));
    connect(this->data, SIGNAL(optionByte(int,int)), this, SLOT(onOptionByte(int,int)));
    ui->btnChangeAddress->setEnabled(false);

    createMenus();

    // status bar
    statusBar()->addWidget(ui->lblStatus);
}

LocoIOFrame::~LocoIOFrame()
{
    delete ui;
}

void LocoIOFrame::createActions()
{
 actSaveModule = new QAction(tr("Save Module..."), this);
 actSaveModule->setToolTip(tr("Save the configuration for this module so it can be restored later."));
 actRestoreModule = new QAction(tr("Restore Module"), this);
 actProbe = new QAction(tr("Probe Modules"), this);
 actCapture = new QAction(tr("Capture"), this);
 actSetDefaults = new QAction(tr("Set defaults"), this);
 actDisplayHex = new QAction(tr("Display values in hex."), this);
 actDisplayHex->setToolTip("Display CV and addresses as decimal or hexadecimal");
 actDisplayHex->setCheckable(true);
 actAllowEdits = new QAction(tr("Allow edits"));
 actAllowEdits->setCheckable(true);

}

void LocoIOFrame::createMenus()
{
 QMenuBar* menubar = menuBar();
 Menu* fileMenu = new Menu(tr("File")); // note: sub-classed QMenu that displays tooltips.
 menubar->addMenu(fileMenu);
 fileMenu->addAction(actSaveModule);
 connect(actSaveModule, SIGNAL(triggered(bool)), this, SLOT(on_btnSave_clicked()));
 fileMenu->addAction(actRestoreModule);
 connect(actRestoreModule, SIGNAL(triggered(bool)), this, SLOT(on_btnRestore_clicked()));
 fileMenu->addAction(actProbe);
 connect(actProbe, SIGNAL(triggered(bool)), this, SLOT(on_btnProbe_clicked()));
 fileMenu->addAction(actCapture);
 connect(actCapture, SIGNAL(triggered(bool)), this, SLOT(on_btnCapture_clicked()));
 fileMenu->addAction(actSetDefaults);
 connect(actSetDefaults, SIGNAL(triggered(bool)), this, SLOT(on_btnSetDefaults_clicked()));

 Menu* optionMenu = new Menu(tr("Options"));
 menubar->addMenu(optionMenu);
 actDisplayHex->setChecked(bDisplayHex);
 optionMenu->addAction(actDisplayHex);
 connect(actDisplayHex, SIGNAL(triggered(bool)), this, SLOT(on_chkHex_toggled(bool)));
 optionMenu->addAction(actAllowEdits);
 connect(actAllowEdits, SIGNAL(triggered(bool)), this, SLOT(on_chkAllowEdit_toggled(bool)));

 menubar->addMenu(new WindowMenu((WindowInterface*)this,this));
}
void LocoIOFrame::setupTable()
{
 bLoading = true;
// bool bServo = ui->chkServoIO->isChecked();
// bool bBooster = ui->chkBooster->isChecked();
 if(bIsServo || bIsBooster)
 {
  ui->rbCheckAll->setVisible(true);
  ui->rbCheckBlockAndPoints->setVisible(true);
  ui->rbCheckBlock->setVisible(true);
  ui->lblJP1->setVisible(false);
 }
 else
 {
  ui->rbCheckAll->setVisible(false);
  ui->rbCheckBlockAndPoints->setVisible(false);
  ui->rbCheckBlock->setVisible(false);
  ui->lblJP1->setVisible(true);
 }

 ui->tableWidget->clear();
 ui->tableWidget->setColumnCount(17);
 for(int i=0; i<ui->tableWidget->columnCount(); i++)
  ui->tableWidget->setColumnHidden(i,false);
 if(bIsServo)
  ui->tableWidget->setHorizontalHeaderLabels(servoLabels);
 else
  if(bIsBooster)
   ui->tableWidget->setHorizontalHeaderLabels(boosterLabels);
 else
  ui->tableWidget->setHorizontalHeaderLabels(labels);
 if(bIsServo)
 {
  if(servoWidget == NULL)
  {
   servoWidget = new ServoWidget(data, /*locobufferadapter->packetizer()*/tc, ui->tableWidget);
   connect(this, SIGNAL(retranslateControls()), servoWidget, SLOT(retranslateControls()));
   servoRegistersWidget = new ServoRegistersWidget(this);
   connect(this, SIGNAL(retranslateControls()), servoRegistersWidget, SLOT(retranslateControls()));
   for(int col=4; col < 12; col++)
   {
    RegistersWidget* rw = new RegistersWidget(data, col+1,RegistersWidget::SERVO,this);
    connect(this, SIGNAL(retranslateControls()), rw, SLOT(retranslateControls()));
    connect(this, SIGNAL(displayFormat(bool)), rw, SLOT(setHexDisplay(bool)));
    connect(this, SIGNAL(allowEdit(bool)), rw, SLOT(onAllowEdit(bool)));
    //connect(ui->chkServoIO, SIGNAL(toggled(bool)), rw, SLOT(setServo(bool)));
    servoRegistersWidget->addWidget(rw);
    connect(rw, SIGNAL(name(int,QString)), this, SLOT(setName(int, QString)));
    connect(rw, SIGNAL(name(int,QString)), servoWidget, SLOT(setName(int,QString)));
   }
  }
  on_chk4PosServo_toggled((cfg & 0x12) == 0x12);
 }
 if(bIsBooster)
  ui->tableWidget->setColumnCount(9);
 else
  ui->tableWidget->setColumnCount(17);
 for(int col=0; col < data->numRows(); col++)
 {
  if(bIsBooster)
  {

   if(col == 4 || col == 5)
   {
    BoosterInputWidget* biw = new BoosterInputWidget(data, col+1, /*locobufferadapter->packetizer()*/tc, this);
    connect(this, SIGNAL(retranslateControls()), biw, SLOT(retranslateControls()));
    ui->tableWidget->setCellWidget(0, col, biw);
    ExtraOpcodeWidget* extra1 = new ExtraOpcodeWidget(data,col+1, 1,this);
    connect(this, SIGNAL(retranslateControls()), extra1, SLOT(retranslateControls()));
    connect(this, SIGNAL(displayFormat(bool)), extra1, SLOT(setHexDisplay(bool)));
    connect(this, SIGNAL(allowEdit(bool)), extra1, SLOT(onAllowEdit(bool)));
    ui->tableWidget->setCellWidget(2,col,extra1);
    ExtraOpcodeWidget* extra2 = new ExtraOpcodeWidget(data,col+1, 2,this);
    connect(this, SIGNAL(retranslateControls()), extra2, SLOT(retranslateControls()));
    connect(this, SIGNAL(allowEdit(bool)), extra2, SLOT(onAllowEdit(bool)));
    connect(this, SIGNAL(displayFormat(bool)), extra2, SLOT(setHexDisplay(bool)));
    ui->tableWidget->setCellWidget(3,col,extra2);

    RegistersWidget* rw = new RegistersWidget(data, col+1,RegistersWidget::BOOSTER_IN,this);
    connect(this, SIGNAL(retranslateControls()), rw, SLOT(retranslateControls()));
    connect(this, SIGNAL(displayFormat(bool)), rw, SLOT(setHexDisplay(bool)));
    connect(this, SIGNAL(allowEdit(bool)), rw, SLOT(onAllowEdit(bool)));
    //connect(ui->chkServoIO, SIGNAL(toggled(bool)), rw, SLOT(setServo(bool)));
    connect(this, SIGNAL(specialPorts()), rw, SLOT(setSpecialPort()));
    ui->tableWidget->setCellWidget(4, col,rw);
    connect(rw, SIGNAL(name(int,QString)), this, SLOT(setName(int, QString)));

    continue;
   }
   if(col == 6)
   {
    BoosterOutputWidget* bow = new BoosterOutputWidget(data, col+1, /*locobufferadapter->packetizer()*/tc, this);
    connect(this, SIGNAL(retranslateControls()), bow, SLOT(retranslateControls()));
    ui->tableWidget->setCellWidget(1, col, bow);
    ExtraOpcodeWidget* extra1 = new ExtraOpcodeWidget(data,col+1, 1,this);
    connect(this, SIGNAL(retranslateControls()), extra1, SLOT(retranslateControls()));
    connect(this, SIGNAL(displayFormat(bool)), extra1, SLOT(setHexDisplay(bool)));
    connect(this, SIGNAL(allowEdit(bool)), extra1, SLOT(onAllowEdit(bool)));
    ui->tableWidget->setCellWidget(2,col,extra1);
    ExtraOpcodeWidget* extra2 = new ExtraOpcodeWidget(data,col+1, 2,this);
    connect(this, SIGNAL(retranslateControls()), extra2, SLOT(retranslateControls()));
    connect(this, SIGNAL(allowEdit(bool)), extra2, SLOT(onAllowEdit(bool)));
    connect(this, SIGNAL(displayFormat(bool)), extra2, SLOT(setHexDisplay(bool)));
    ui->tableWidget->setCellWidget(3,col,extra2);

    RegistersWidget* rw = new RegistersWidget(data, col+1,RegistersWidget::BOOSTER_OUT, this);
    connect(this, SIGNAL(retranslateControls()), rw, SLOT(retranslateControls()));
    connect(this, SIGNAL(displayFormat(bool)), rw, SLOT(setHexDisplay(bool)));
    connect(this, SIGNAL(allowEdit(bool)), rw, SLOT(onAllowEdit(bool)));
    //connect(ui->chkServoIO, SIGNAL(toggled(bool)), rw, SLOT(setServo(bool)));
    connect(this, SIGNAL(specialPorts()), rw, SLOT(setSpecialPort()));
    ui->tableWidget->setCellWidget(4, col,rw);
    connect(rw, SIGNAL(name(int,QString)), this, SLOT(setName(int, QString)));

    continue;
   }
   if(col == 7)
   {
    BoosterPanel* bp = new BoosterPanel(this);
    connect(this, SIGNAL(retranslateControls()), bp, SLOT(retranslateControls()));
    ui->tableWidget->setCellWidget(0,col, bp);
    break;
   }
  }
  if(bIsServo && col > 3 && col <= 11)
  {
   if(col == 4)
   {
    ui->tableWidget->setCellWidget(0,col,servoWidget);
    ui->tableWidget->setCellWidget(4,col,servoRegistersWidget);
   }
   else
    ui->tableWidget->hideColumn(col);
  }
  else
  {
   ui->tableWidget->showColumn(col);
   QButtonGroup* group = new QButtonGroup(this);
   InputWidget* iw = new InputWidget(data, col+1,/*locobufferadapter->packetizer()*/tc,group, this);
   connect(this, SIGNAL(retranslateControls()), iw, SLOT(retranslateControls()));
   OutputWidget* ow = new OutputWidget(data, col+1, /*locobufferadapter->packetizer()*/tc,group, this);
   connect(this, SIGNAL(retranslateControls()), ow, SLOT(retranslateControls()));
   ui->tableWidget->setCellWidget(0, col,iw);
   ui->tableWidget->setCellWidget(1, col,ow);
   ExtraOpcodeWidget* extra1 = new ExtraOpcodeWidget(data,col+1, 1,this);
   connect(this, SIGNAL(retranslateControls()), extra1, SLOT(retranslateControls()));
   connect(this, SIGNAL(displayFormat(bool)), extra1, SLOT(setHexDisplay(bool)));
   connect(this, SIGNAL(allowEdit(bool)), extra1, SLOT(onAllowEdit(bool)));
   ui->tableWidget->setCellWidget(2,col,extra1);
   ExtraOpcodeWidget* extra2 = new ExtraOpcodeWidget(data,col+1, 2,this);
   connect(this, SIGNAL(retranslateControls()), extra2, SLOT(retranslateControls()));
   connect(this, SIGNAL(allowEdit(bool)), extra2, SLOT(onAllowEdit(bool)));
   connect(this, SIGNAL(displayFormat(bool)), extra2, SLOT(setHexDisplay(bool)));
   ui->tableWidget->setCellWidget(3,col,extra2);

   RegistersWidget* rw = new RegistersWidget(data, col+1,RegistersWidget::NORMAL, this);
   connect(this, SIGNAL(retranslateControls()), rw, SLOT(retranslateControls()));
   connect(this, SIGNAL(displayFormat(bool)), rw, SLOT(setHexDisplay(bool)));
   connect(this, SIGNAL(allowEdit(bool)), rw, SLOT(onAllowEdit(bool)));
   //connect(ui->chkServoIO, SIGNAL(toggled(bool)), rw, SLOT(setServo(bool)));
   //connect(this, SIGNAL(specialPorts()), rw, SLOT(setSpecialPort()));
   ui->tableWidget->setCellWidget(4, col,rw);
   connect(rw, SIGNAL(name(int,QString)), this, SLOT(setName(int, QString)));

  }
 }
 int maxCol;
 if(bIsBooster)
  maxCol = 8;
 else
  maxCol = 16;
 InPortDefinitionWidget* idw = new InPortDefinitionWidget(this);
 ui->tableWidget->setCellWidget(0,maxCol,idw);
 connect(this, SIGNAL(retranslateControls()), idw, SLOT(retranslateControls()));
 OutPortDefinitionWidget* opdw = new OutPortDefinitionWidget(data, this);
 connect(this, SIGNAL(retranslateControls()), opdw, SLOT(retranslateControls()));
 ui->tableWidget->setCellWidget(1,maxCol, opdw);
 ExtraOpcodeDefinitionWidget* ex1 = new ExtraOpcodeDefinitionWidget(1,this);
 connect(this, SIGNAL(retranslateControls()), ex1, SLOT(retranslateControls()));
 ui->tableWidget->setCellWidget(2,maxCol,ex1);
 ExtraOpcodeDefinitionWidget* ex2 = new ExtraOpcodeDefinitionWidget(1,this);
 connect(this, SIGNAL(retranslateControls()), ex2, SLOT(retranslateControls()));
 ui->tableWidget->setCellWidget(3,maxCol,ex2);
 AddressPortDefinitionWidget* apdw = new AddressPortDefinitionWidget(data, this);
 connect(this, SIGNAL(retranslateControls()), apdw, SLOT(retranslateControls()));
 if(bIsServo)
 {
  idw->setServoOpt();
  ui->chkModule->setChecked(true);
 }
 ui->tableWidget->setCellWidget(4,maxCol, apdw);
 ui->tableWidget->resizeColumnsToContents();
 ui->tableWidget->resizeRowsToContents();
 ui->tableWidget->horizontalHeader()->stretchLastSection();
 ui->tableWidget->setRowHidden(2,true);
 ui->tableWidget->setRowHidden(3,true);

 bLoading = false;
}

void LocoIOFrame::setName(int col, QString s)
{
 if(bIsServo &&(col > 3 || col <12)) return;
 ui->tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(s));
}

void LocoIOFrame::on_btnProbe_clicked()
{
 data->setLIOVersion("<Not found>");
 //LocoIO::probeLocoIOs(pr3);
 //data->startProbe();
 locoIOModules->startProbe();
}
void LocoIOFrame::on_btnReadAll_clicked()
{
 enableUi(false);
//  bReadingAll = true;
//  bWritingAll = false;
//  data->readAll();
//  for(int row=0; row < data->numRows()*2; row++)
//   data->setDirty(row,false);
 data->readAllCVs();
}
void LocoIOFrame::onPropertyChange(PropertyChangeEvent* evt)
{
 //log->debug(QString("Property change %1 oldVal='%2' newVal='%3'").arg(propertyName).arg(oldVal.toString()).arg(newVal.toString()));

 if(evt->getPropertyName() == "StatusChange")
     ui->lblStatus->setText( evt->getNewValue().toString());
 if(evt->getPropertyName() == "StatusChange" && evt->getNewValue().toString()== "OK")
 {
  for(int channel =0; channel < data->numRows(); channel++)
  {
   data->setLIM(channel);
   int config = data->getSV(channel);
   if(!(config & 0x80))
   { // input or not used
    InputWidget* inWidget = (InputWidget*)ui->tableWidget->cellWidget(0, channel);
    if(inWidget != NULL)
     inWidget->setToolTip(data->getMode(channel));
   }
   else
   {
    OutputWidget* outWidget = (OutputWidget*)ui->tableWidget->cellWidget(1, channel);
    if(outWidget != NULL)
     outWidget->setToolTip(data->getMode(channel));
    if(channel > 3 && channel < 8 && bIsServo)
    {
     servoWidget->onSVChanged(channel, 0, config, data->ssGreen);
    }
   }
   RegistersWidget* registersWidget = (RegistersWidget*)ui->tableWidget->cellWidget(2, channel);
   if(registersWidget != NULL)
    registersWidget->setToolTip(data->getMode(channel));
  }
 }
 if(evt->getPropertyName() == "PortChange")
 {
  int channel = evt->getNewValue().toInt();
  int config = data->getSV(channel);
  if(bLoading)
   return;
  if(channel == 0 && config == 44)
  {
   ui->chkSpecialPorts->setChecked(true);
   emit specialPorts();
  }
//  sql->setData(data);
//  if(sql->commentRecordExists(channel+1))
//   sql->updateBasicComments(channel+1, data->getModuleType());
 }
 if (evt->getPropertyName() == "UnitAddress")
 {
  //unitAddr = newVal.toInt() & 0xFF;
  _address->setUnitAddress(evt->getNewValue().toInt() & 0xFF);
  //setupCbAddr();
 }
 if (evt->getPropertyName() == "UnitSubAddress")
 {
  _address->setUnitSubAddress(evt->getNewValue().toInt());
  //setupCbAddr();
  enableUi(true);
 }
 if (evt->getPropertyName() =="LBVersionChange") {
  QString v = (QString)evt->getNewValue().toString();
  ui->lblLocoBuffer->setText(v);
 }
 if (evt->getPropertyName() == "LIOVersionChange")
 {
  ui->lblFirmware->setText(evt->getNewValue().toString());
 }
 if(evt->getPropertyName() == "UnitConfig")
 {
  LocoNetMessage* msg = LocoIO::writeCV(_address->unitAddress() | 0x100, _address->unitSubAddress(), 0, evt->getNewValue().toInt());
  //locobufferadapter->packetizer()->sendLocoNetMessage(msg);
  tc->sendLocoNetMessage(msg);
  QString v = QString("Unit config changed: Blink Rate = 0x%1, LocoServo =%2").arg((evt->getNewValue().toInt()& 0xF0)>>4, 0, 16).arg((evt->getNewValue().toInt() & 0x80)>>3);
  ui->lblStatus->setText(v);
 }
}
void LocoIOFrame::on_btnCapture_clicked()
{
 enableUi(false);
 for(int channel = 0; channel<data->numRows()*3; channel++)
 {
  QCheckBox* checkbox = (QCheckBox*)ui->tableWidget->cellWidget(channel, 0);
  if(checkbox != NULL && checkbox->isChecked())
  {
   LocoIO::readCV(_address->unitAddress() | 0x100, _address->unitSubAddress(), channel*3+4);
   connect(/*locobufferadapter->packetizer()*/tc,SIGNAL(messageProcessed(LocoNetMessage*,bool)), data, SLOT(message(LocoNetMessage*)));
  }
 }
}
void LocoIOFrame::on_btnWriteAll_clicked()
{
 enableUi(false);
// bWritingAll=true;
// data->writeAll();
// setDirty(false);
 data->writeAllCVs();
}

void LocoIOFrame::on_btnChangeAddress_clicked()
{
  enableUi(false);
  if(val == 0)
  {
   //qDebug() << QString(" val = %1, index = %2").arg(val).arg(ui->cbAddr->currentIndex());
   return;
  }
  int oldAddr = data->getUnitAddress();
  int oldSubAddr = data->getUnitSubAddress();
  int newAddr = val >> 16;
  int newSubAddr = val & 0xffff;
  if ((newAddr&0x7FFF) == 0x080)
  {
   log->warn(tr("Only a LocoBuffer can use address 0x80"));
   enableUi(true);
   return;
  }

  if (newSubAddr > 126 || newSubAddr < 1)
  {
   log->warn(tr("subAddress must be [1..126], was %1").arg( newSubAddr));
   QMessageBox::warning(this, tr("Invalid subAddress"),tr("subAddress must be [1..126], was %1").arg( newSubAddr));
   return;
  }

  newAddr    = 0x0100 | (newAddr&0x07F);  // range is [1..79, 81..127]
  newSubAddr = newSubAddr & 0x07F;	// range is [1..126]
  ui->btnChangeAddress->setEnabled(false);
  if((oldAddr & 0xFF) == 0)
  {
   switch(QMessageBox::warning(this, tr("Warning"), tr("This will set the address of all attached LocoIO, LocoServo and LocoBooster boards"),QMessageBox::Ok | QMessageBox::Cancel))
   {
   case QMessageBox::Ok:
    break;
   default:
   case QMessageBox::Cancel:
    return;
   }
  }
  else
  {
   switch(QMessageBox::warning(this, tr("Warning"), tr("This will change the address of %1 board 0x%2/%3 to 0x%4/%5").arg(data->getModuleType()).arg(oldAddr & 0xFF).arg(oldSubAddr).arg(newAddr&0xFF).arg(newSubAddr),QMessageBox::Ok | QMessageBox::Cancel))
   {
   case QMessageBox::Ok:
    break;
   default:
   case QMessageBox::Cancel:
    return;
   }

  }
  data->changeUnitAddress(newAddr | 0x100, newSubAddr);
  //unitAddr = data->getUnitAddress();
  _address->setUnitAddress(data->getUnitAddress());
  //unitSubAddr = data->getUnitSubAddress();
  _address->setUnitSubAddress(data->getUnitSubAddress());
  if(ui->chkHex->isChecked())
  {
   ui->lblUnitAddr->setText(tr("New Unit Address 0x"));
   rv->setRegExp(rxHex);
   ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(),0,16));
  }
  else
  {
   ui->lblUnitAddr->setText(tr("New Unit Address"));
   rv->setRegExp(rxDec);
   ui->lblCurrentAddress->setText(tr("Current address: %1/%2").arg(_address->unitAddress(),0,10).arg(_address->unitSubAddress(),0,10));
  }
  enableUi(true);
  sql->changeAddress(oldAddr, oldSubAddr, _address->unitAddress(), _address->unitSubAddress());
  //on_btnProbe_clicked();
}

void LocoIOFrame::onAddrChanged(const QString &position)
{
 QStringList coordinates = position.split("-");
 int row = coordinates[0].toInt();
 int col = coordinates[1].toInt();
 QLineEdit* editAddr=(QLineEdit*)ui->tableWidget->cellWidget(row, col);
 QString value = editAddr->text();
//    data->setAddr(row, editAddr->text().toInt(0,16));
 int a = decodeText(editAddr);

 if (a < 1)
  { a = 1; }
 if (a > 0xFFF)
 { a = 0xFFF; }
 data->setAddr(row, a,data->ssGreen);
 data->setDirty(row,true);
 if (!("<none>"== data->getMode(row)))
 {
  LocoIOMode* l = data->getLIM(row);
  data->setV1(row, l, a);
  data->setV2(row, l, a);

  int opcode = (l == NULL) ? 0 : l->getOpcode();
  msg->replace(row, "Packet: " + LnConstants::OPC_NAME(opcode) +
               " "        + QString("%1").arg(data->getV1(row),0,16) +
               " "        + QString("%1").arg(data->getV2(row),0,16) +
               " <CHK>");

//    if (status!=null) status.setText(msg[row]);
  ui->lblStatus->setText(msg->at(row));

  QLineEdit* editAddr = (QLineEdit*)ui->tableWidget->cellWidget(row, 2); // address
  QString val = QString("%1").arg(data->getAddr(row),0,16);
  editAddr->setText(val);
  QLabel* label = (QLabel*)ui->tableWidget->cellWidget(row, 3);    // configuration
  val = QString("%1").arg(data->getSV(row),0,16);
  label->setText(val);
  label = (QLabel*)ui->tableWidget->cellWidget(row, 4);    // value 1
  val = QString("%1").arg(data->getV1(row),0,16);
  label->setText(val);
  label = (QLabel*)ui->tableWidget->cellWidget(row, 5);    // value 2
  val = QString("%1").arg(data->getV2(row),0,16);
  label->setText(val);
 }
}

void LocoIOFrame::on_btnHide_clicked()
{
 close();
}

void LocoIOFrame::on_btnSetDefaults_clicked()
{
 enableUi(false);
 data->setDefaults();
}

void LocoIOFrame::onMessageReceived(LocoNetMessage *m, bool)
{
 if(m->getElement(2) == (_address->unitAddress() & 0xff))
  data->message(m);
 switch(m->getOpCode())
 {
 case LnConstants::OPC_GPON:
  emit LnStatusChange(data->ssGreen);
  break;
 case LnConstants::OPC_IDLE:
  emit LnStatusChange(data->ssPink);
  break;
 case LnConstants::OPC_GPOFF:
  emit LnStatusChange(data->ssRed);
  break;
 default:
  break;
 }
}
void LocoIOFrame::setDirty(bool bDirty)
{
 this->bDirty = bDirty;
 setWindowTitle(createTitle());
}
QString LocoIOFrame::createTitle()
{
 return _address->moduleType() + (bDirty?"* ":" ") + _address->firmwareVersion() + QString(" 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(), 0, 16) +  QString(" (%1/%2)").arg(_address->unitAddress(),0,10).arg(_address->unitSubAddress(), 0, 10);
}
void LocoIOFrame::on_btnSave_clicked()
{
 //enableUi(false);
 //data->getCVs(); // initiate read of all cv's
 saveDlg = new SaveRestoreDialog(false, data, this);
 int rslt = saveDlg->exec();
 Q_UNUSED(rslt);
}
void LocoIOFrame::on_btnRestore_clicked()
{
 enableUi(false);
 saveDlg = new SaveRestoreDialog(false, data, this);
 int rslt = saveDlg->exec();
 if(rslt == QDialog::Accepted)
 {
  moduleName = saveDlg->getModuleName();
  data->setValues(saveDlg->getValues());
 }
 saveDlg = NULL;
}
void LocoIOFrame::enableUi(bool bEnable)
{
 ui->btnCapture->setEnabled(bEnable);
 ui->btnChangeAddress->setEnabled(bEnable);
 ui->btnProbe->setEnabled(bEnable);
 ui->btnReadAll->setEnabled(bEnable);
 ui->btnRestore->setEnabled(bEnable);
 actRestoreModule->setEnabled(bEnable);
 ui->btnSave->setEnabled(bEnable);
 actSaveModule->setEnabled(bEnable);
 ui->btnSetDefaults->setEnabled(bEnable);
 ui->btnWriteAll->setEnabled(bEnable);
}
void LocoIOFrame::onIOComplete(QList<int>* vals)
{
 Q_UNUSED(vals)
 //enableUi(true);
 if(bReadingAll )
  data->readAllX2();
 if(bWritingAll)
  data->writeAllX2();
}
void LocoIOFrame::onIOCompleteX2(QList<int>* vals)
{
 Q_UNUSED(vals)
 if(bIsServo)
 {
  if(bReadingAll )
   data->readAllServo();
  if(bWritingAll)  // TODO:
   data->writeAllServo();
  return;
 }
 bReadingAll = bWritingAll = false;
 enableUi(true);
}
void LocoIOFrame::onIOCompleteServo()
{
 bReadingAll = bWritingAll = false;
 enableUi(true);
}

//void LocoIOFrame::on_tableWidget_cellClicked(int row, int)
//{
//}
void LocoIOFrame::onConfigRead(int cfg) //SLOT
{
 this->cfg = cfg;
 //ui->sbBlinkRate->setValue((cfg&0xff)>>4);
// bool bServo = (data->getIsServo() == 1);
//bIsServo = data->getIsServo()==1?true:false;
//bIsBooster = data->getIsBooster()==1?true:false;
QString moduleType = _address->moduleType();
bIsServo = bIsBooster = false;
if(moduleType == "LocoServo")
{
 bIsServo = true;
}
else
 if(moduleType == "LocoBooster")
  bIsBooster = true;

// ui->chkServoIO->setChecked(bServo);
// ui->chkBooster->setChecked(false);
 ui->chkSpecialPorts->setChecked(false);
 ui->rbFixCodeForPBs->setChecked(data->getAltCodePBs()!=1);
 ui->rbAltCodeForPBs->setChecked(data->getAltCodePBs()==1);

 this->setWindowTitle(createTitle());
 setupTable();
 OutPortDefinitionWidget* opdw;
 if(bIsBooster)
  opdw = (OutPortDefinitionWidget*)ui->tableWidget->cellWidget(1,8);
 else
  opdw = (OutPortDefinitionWidget*)ui->tableWidget->cellWidget(1,16);

 opdw->setBlinkSb((cfg&0xff)>>4);
 if(bIsServo)
  on_chk4PosServo_toggled((cfg & 0x04 )== 0x04);


 on_btnReadAll_clicked();
}
int LocoIOFrame::decodeText(QLineEdit *ctl)
{
 QString text = ctl->text();
 bool bOk=false;
 int val;
 if(text.startsWith("0x",Qt::CaseInsensitive))
  val = text.mid(2).toInt(&bOk,16);
 else
  val = text.toInt(&bOk,10);
 if(!bOk)
  return -1;
 return val;
}
void LocoIOFrame::on_chkExtra1_toggled(bool bChecked)
{// row 2
 if(bChecked)
 {
  ui->chkExtra2->setChecked(false);
  ui->tableWidget->setRowHidden(1,true);
  ui->tableWidget->setRowHidden(2,false);
  ui->tableWidget->setRowHidden(3,true);
//  QFont font;
//  font.setPointSize(7);
//  ui->tableWidget->setFont(font);
 }
 else
 {
  if(!ui->chkExtra2->isChecked())
  {
   ui->tableWidget->setRowHidden(1,false);
   ui->tableWidget->setRowHidden(2,true);
   ui->tableWidget->setRowHidden(3,true);
  }
 }
}
void LocoIOFrame::on_chkExtra2_toggled(bool bChecked)
{ // row 3
 if(bChecked)
 {
  ui->chkExtra1->setChecked(false);
  ui->tableWidget->setRowHidden(1,true);
  ui->tableWidget->setRowHidden(2,true);
  ui->tableWidget->setRowHidden(3,false);
 }
 else
 {
  if(!ui->chkExtra2->isChecked())
  {
   ui->tableWidget->setRowHidden(1,false);
   ui->tableWidget->setRowHidden(2,true);
   ui->tableWidget->setRowHidden(3,true);
  }
 }
}
void LocoIOFrame::on_chkHex_toggled(bool bChecked)
{
 emit displayFormat(bChecked);
 if(bChecked)
 {
  ui->lblUnitAddr->setText(tr("New Unit Address 0x"));
  rv->setRegExp(rxHex);
  ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(),0,16));
 }
 else
 {
  ui->lblUnitAddr->setText(tr("New Unit Address"));
  rv->setRegExp(rxDec);
  ui->lblCurrentAddress->setText(tr("Current address: %1/%2").arg(_address->unitAddress(),0,10).arg(_address->unitSubAddress(),0,10));

 }
 //setupCbAddr();
 p->setSimplePreferenceState(displayHexCheck, ui->chkHex->isChecked());

}
void LocoIOFrame::on_chkAllowEdit_toggled(bool bChecked)
{
 emit allowEdit(bChecked);
 bAllowEdits = bChecked;
 p->setSimplePreferenceState("AllowEdit", bChecked);
}

//void LocoIOFrame::on_chkServoIO_toggled(bool bChecked)
//{
// if(bLoading)
//  return;
// int val = bChecked?1:0;
// data->setIsServo(val);
//  setupTable();
//  //onPropertyChange("StatusChange", QVariant(""), QVariant("OK"));
//  for(int i=4; i < 12; i++)
//   data->setSV(i, 0, data->ssWhite);
//  data->emitAll();
//  // }
//}
void LocoIOFrame::on_chk4PosServo_toggled(bool bChecked)
{
 servoWidget->set4PositionServo(bChecked);
 data->setIs4Pos(bChecked);
 data->setOption(0,cfg = data->getUnitConfig());
 ui->chk4PosServo->setChecked(bChecked);
}
void LocoIOFrame::onProbeCompleted(QList<LocoIOAddress* > list)
{
 foreach (LocoIOAddress* addr, list)
 {
  qDebug()<< QString("Probed module: %1 %2 %3").arg(addr->unitAddress()).arg(addr->unitSubAddress()).arg(addr->firmwareVersion());
 }
 //setupCbAddr();
}
void LocoIOFrame::on_chkSpecialPorts_toggled(bool bChecked)
{
 if(bLoading )
  return;
 for(int port=1; port < 5; port++)
 {
  int column = port - 1;
  RegistersWidget* rw = (RegistersWidget*)ui->tableWidget->cellWidget(4, column);

  if(bChecked)
  {
   SpecialPort* sp = new SpecialPort(data, port, this);
   if(port != 4)
   {
    ui->tableWidget->setCellWidget(0,column, sp);
    ui->tableWidget->removeCellWidget(1,column);

   }
   else
   { // ports 1-3
    ui->tableWidget->setCellWidget(1,column, sp);
    ui->tableWidget->removeCellWidget(0,column);
    connect(this, SIGNAL(LnStatusChange(QString)), sp, SLOT(setStatus(QString)));
   }
   rw->setPortType(RegistersWidget::SPECIAL);
  }
  else
  {
   QButtonGroup* group = new QButtonGroup(this);
   InputWidget* iw = new InputWidget(data, port,/*locobufferadapter->packetizer()*/tc,group, this);
   OutputWidget* ow = new OutputWidget(data, port, /*locobufferadapter->packetizer()*/tc,group, this);
   ui->tableWidget->setCellWidget(0, column,iw);
   ui->tableWidget->setCellWidget(1, column,ow);
   rw->setPortType(RegistersWidget::NORMAL);

   bLoading = true;
   for(int i = 0; i < 4; i++)
   {
    data->setSV(i, 0, data->ssWhite);
   }
   ui->chkSpecialPorts->setChecked(false);
   bLoading = false;
  }
 }
}
#if 0
void LocoIOFrame::setupCbAddr()
{
 bLoadCB = true;
 ui->cbAddr->clear();
 ui->cbAddr->addItem("New Address", 0);
 foreach(LocoIOAddress* addr, LocoIOModules::instance()->probedAddresses())
 {
  qint32 val = ((qint16)addr->unitAddress() << 16) + (qint16)addr->unitSubAddress();
//  if(ui->chkHex->isChecked())
//   ui->cbAddr->addItem(QString("%1/%2 %3").arg(addr->unitAddress(),0,16).arg(addr->unitSubAddress(),0,16).arg(addr->moduleType()), val);
//  else
//   ui->cbAddr->addItem(QString("%1/%2 %3").arg(addr->unitAddress(),0,10).arg(addr->unitSubAddress(),0,10).arg(addr->moduleType()), val);
  ui->cbAddr->addItem(QString("%1/%2 (0x%4/%5) %3").arg(addr->unitAddress(),0,10).arg(addr->unitSubAddress(),0,10).arg(addr->moduleType()).arg(addr->unitAddress(),0,16).arg(addr->unitSubAddress(),0,16));
 }
 for(int i=1; i < ui->cbAddr->count(); i++)
 {
  qint32 val = ui->cbAddr->itemData(i).toInt();
  int iUnitAddr = val >> 16;
  int iUnitSubAddr = val & 0xffff;
  if(_address->unitAddress() == iUnitAddr && _address->unitSubAddress() == iUnitSubAddr)
  {
   ui->cbAddr->setCurrentIndex(i);
   break;
  }
 }
 bLoadCB = false;
 ui->btnChangeAddress->setEnabled(false);
}
void LocoIOFrame::on_cbAddr_currentIndexChanged(int index)
{
 if(bLoadCB)
  return;
 if(index < 0)
  return;
 if(checkDirty())
  return;
 qint32 val = ui->cbAddr->itemData(index).toInt();
// unitAddr = val >>16;
// unitSubAddr = val & 0xffff;
 _address->setUnitAddress( val >>16);
 _address->setUnitSubAddress(val & 0xffff);
 if(ui->chkHex->isChecked())
 {
  ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(),0,16));
  ui->lblUnitAddr->setText(tr("Current address: 0x"));
 }
 else
 {
  ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(),0,10));
  ui->lblUnitAddr->setText(tr("Current address:"));
 }
 if(index == 0)
  return;
 bIsBooster = false;
 bIsServo = false;
 ui->tableWidget->setColumnCount(17);
 data->setUnitAddress(_address->unitAddress() );
 data->setUnitSubAddress(_address->unitSubAddress());
// foreach(probedAddress* addr, data->probedAddresses)
// {
//  int a1 = unitAddr&0xff;
//  int a2 = addr->unitAddr&0xff;
//  int s1 = unitSubAddr;
//  int s2 = addr->unitSubAddr;
//  if(a1 == a2 && s1 == s2)
//  {
//   data->setModuleType(addr->moduleType);
//   break;
//  }
// }
 data->getConfig();
}
#endif
void LocoIOFrame::on_edNewAddr_editingFinished()
{
 on_edNewAddr_editTextChanged(ui->edNewAddr->text());
}

void LocoIOFrame::on_edNewAddr_editTextChanged(QString text)
{
 int addr=0;
 int subAddr=0;
 int pos=0;
 bool bOk;
 if(bLoadCB)
  return;
 switch(rv->validate(text, pos))
 {
 case QValidator::Acceptable:
   break;
 case QValidator::Intermediate:
  return;
 case QValidator::Invalid:
   return;
 }

 int iBase = ui->chkHex->isChecked()?16:10;
 QStringList sl = text.split("/");
 addr = sl.at(0).toInt(&bOk,iBase);
 subAddr = sl.at(1).toInt(&bOk, iBase);
 val = (addr << 16) + subAddr;
 for(int i = 0; i<LocoIOModules::instance()->probedAddresses().count(); i++)
 {
  LocoIOAddress* a = LocoIOModules::instance()->probedAddresses().at(i);
  //if(ui->cbAddr->itemData(i).toInt()== val)
  if(a->unitAddress() == addr && a->unitSubAddress() == subAddr)
  {
   //bLoadCB = true;
   //ui->cbAddr->setCurrentIndex(i);
   //bLoadCB = false;
   ui->btnChangeAddress->setEnabled(false);
   return;
  }
  ui->btnChangeAddress->setEnabled(true);

 }
 bLoadCB = true;
 QString ntext = QString("%1/%2").arg(addr,0,iBase).arg(subAddr,0,iBase);
// ui->cbAddr->setItemText(0,ntext);
// ui->cbAddr->setItemData(0, val);
 //ui->cbAddr->addItem(text,val);
 //ui->cbAddr->addItem(text, val);
 //ui->cbAddr->setCurrentIndex(0);
 ui->edNewAddr->setText(ntext);
 ui->btnChangeAddress->setEnabled(true);
 bLoadCB = false;
}
void LocoIOFrame::onIOAborted()
{
 enableUi(true);
}
//void LocoIOFrame::on_chkBooster_toggled(bool bChecked)
//{
// if(bLoading)
//  return;
// if(!bChecked)
//  return;
// setupTable();
// for(int i=0; i < 7; i++)
//  data->setSV(i, 0, data->ssWhite);
// data->emitAll();
//}
void LocoIOFrame::on_rbFixCodeForPBs_toggled(bool bChecked)
{
 if(bLoading)
  return;
 int val = bChecked?1:0;
 data->setAltCodePBs(val);
}
void LocoIOFrame::customContextMenuRequested(QPoint)
{
 if(data->busy())
  return;
 QSignalMapper mapper;
 QMenu menu;
 QAction* actionLocoIO = new QAction("LocoIO", this);
 mapper.setMapping(actionLocoIO,0);
 connect(actionLocoIO, SIGNAL(triggered()), &mapper, SLOT(map()));
 menu.addAction(actionLocoIO);
 QAction* actionLocoBooster = new QAction("LocoBooster", this);
 mapper.setMapping(actionLocoBooster,1);
 connect(actionLocoBooster, SIGNAL(triggered()), &mapper, SLOT(map()));
 menu.addAction(actionLocoBooster);
 QAction* actionLocoServo = new QAction("LocoServo", this);
 mapper.setMapping(actionLocoServo,2);
 connect(actionLocoServo, SIGNAL(triggered()), &mapper, SLOT(map()));
 menu.addAction(actionLocoServo);
 connect(&mapper, SIGNAL(mapped(int)), this, SLOT(onChangeModuleType(int)));
 menu.exec(QCursor::pos());
}
void LocoIOFrame::onChangeModuleType(int iType)
{
 bIsBooster = false;
 bIsServo = false;
 ui->chkModule->setVisible(false);
 ui->chkModule->setText("LocoIO");
 ui->tableWidget->setHorizontalHeaderLabels(labels);
 if(iType == 1)
 {
  ui->chkModule->setVisible(true);
  ui->chkModule->setText("LocoBooster");
  ui->tableWidget->setHorizontalHeaderLabels(boosterLabels);
  bIsBooster = true;
  data->setIsBooster(1);
 }
 else
 if(iType == 2)
 {
  ui->chkModule->setVisible(true);
  ui->chkModule->setText("LocoServo");
  ui->tableWidget->setHorizontalHeaderLabels(servoLabels);
  bIsServo = true;
  data->setIsServo(1);
//  data->getOption(177);
//  return; // onOptionByte will run setup table, etc.
 }
 else
  data->setIsServo(0);
 setupTable();
 data->emitAll();
}
void LocoIOFrame::newAddress()
{
 this->data->getConfig();
}
bool LocoIOFrame::checkDirty()
{
 if(data->dirty() || data->x2Dirty() ||(data->servoDirty()))
 {
  switch(QMessageBox::warning(this,tr("Warning"),tr("Cv values have been changed and not written. Do you want to change your changes?"),QMessageBox::Save | QMessageBox::Cancel| QMessageBox::Discard))
  {
  case QMessageBox::Save:
//   data->writeAll();
//   data->writeAllX2();
//   data->writeAllServo();
   on_btnWriteAll_clicked();
   return true;
  case QMessageBox::Discard:
   break;
  default:
  case QMessageBox::Cancel:
   return true;
  }
 }
 return false;
}
void LocoIOFrame::setData(LocoIOData *data)
{
 this->data = data;
}
LocoIOData* LocoIOFrame::Data()
{ return this->data;}

void LocoIOFrame::setAddress(int unitAddress, int unitSubAddress)
{
 data->setUnitAddress(unitAddress | 0x100);
 data->setUnitSubAddress(unitSubAddress);
 //this->unitAddr = unitAddress | 0x100;
 _address->setAddress(unitAddress, unitSubAddress);
 if(ui->chkHex->isChecked())
  ui->lblCurrentAddress->setText(tr("Current address: 0x%1/%2").arg(_address->unitAddress(),0,16).arg(_address->unitSubAddress(), 0, 16));
 else
  ui->lblCurrentAddress->setText(tr("Current address: 0%1/%2").arg(_address->unitAddress(),0,10).arg(_address->unitSubAddress(), 0, 10));

 //setupCbAddr();
 this->data->getConfig();
}
void LocoIOFrame::onReadWriteAllComplete()
{
 enableUi(true);
}
void LocoIOFrame::onIOCompleted7D()
{
 int val = data->getSV7F();
 switch(val & 0x0F)
 {
 case 0x00:
  ui->chkInputStatus->setChecked(true);
  ui->rbCheckAll->setChecked(true);
  break;
 case 0x02:
  ui->chkInputStatus->setChecked(true);
  ui->rbCheckBlockAndPoints->setChecked(true);
  break;
 case 0x06:
  ui->chkInputStatus->setChecked(true);
  ui->rbCheckBlock->setChecked(true);
  break;
 case 0x01:
  ui->chkInputStatus->setChecked(false);
  ui->rbCheckAll->setChecked(true);
  break;
 case 0x03:
  ui->chkInputStatus->setChecked(false);
  ui->rbCheckBlockAndPoints->setChecked(true);
  break;
 case 0x07:
  ui->chkInputStatus->setChecked(false);
  ui->rbCheckBlock->setChecked(true);
  break;
 default:
  break;
 }
}
void LocoIOFrame::on_chkInputStatus_toggled(bool bChecked)
{
 if(bChecked)
 {
  if(ui->rbCheckAll->isChecked())
   data->setSV7F(0x00);
  if(ui->rbCheckBlockAndPoints->isChecked())
   data->setSV7F(0x02);
  if(ui->rbCheckBlock->isChecked())
   data->setSV7F(0x06);
 }
 else
 {
  if(ui->rbCheckAll->isChecked())
   data->setSV7F(0x01);
  if(ui->rbCheckBlockAndPoints->isChecked())
   data->setSV7F(0x03);
  if(ui->rbCheckBlock->isChecked())
   data->setSV7F(0x07);
 }
}
void LocoIOFrame::onInputStatusRbChanged(int )
{
 on_chkInputStatus_toggled(ui->chkInputStatus->isChecked());
}
void LocoIOFrame::tableCustomContextMenuRequested(QPoint pt)
{
 currPort = ui->tableWidget->columnAt(pt.x())+1;
 if(currPort == 5 && bIsServo)
 {
  currPort += servoWidget->getColumn(ui->tableWidget->width(), pt);
 }
 QAction* act = new QAction("Update comments",this);
 connect(act, SIGNAL(triggered()), this, SLOT(onUpdateComments()));
 QMenu menu;
 menu.addAction(act);
 menu.exec(QCursor::pos());
}
void LocoIOFrame::onUpdateComments()
{
 CommentsDialog dlg(currPort, data, sql);
 dlg.exec();
}
void LocoIOFrame::retranslate_Controls(/*QString s_locale*/)
{
// if (s_locale != "")
// {
//  QTranslator this_translator;
//  if (this_translator.load(":languages/loconetmonitor_"+s_locale+".qm"))
//  {
//   qApp->installTranslator(&this_translator);
//   qDebug()<< tr("-I-> LocoIOFrame::on_init_control_text : translation file for ")+"'"+s_locale+"'"+tr(" loaded");
   ui->retranslateUi(this);
   data->translateModeList();
   setWindowTitle(createTitle());
   emit retranslateControls();
   labels.clear();
   servoLabels.clear();
   boosterLabels.clear();
   labels <<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<tr("Port Definition");
   servoLabels <<"1"<<"2"<<"3"<<"4"<<"Servo"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<tr("Port Definition");
   boosterLabels <<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"Booster"<<tr("Port Definition");
   if(bIsServo)
    ui->tableWidget->setHorizontalHeaderLabels(servoLabels);
   else
    if(bIsBooster)
     ui->tableWidget->setHorizontalHeaderLabels(boosterLabels);
   else
    ui->tableWidget->setHorizontalHeaderLabels(labels);

//  }
//  else
//   qDebug()<< tr("-I-> LocoIOFrame::on_init_control_text : translation file for ")+"'"+s_locale+"'"+tr(" not loaded");
// }
}
void LocoIOFrame::onOptionByte(int cv, int val)
{
 log->debug(QString("option byte %1, value %2").arg(cv).arg(val));
 on_chk4PosServo_toggled((val & 0x04) == 0x04);

 setupTable();
 OutPortDefinitionWidget* opdw;
 if(bIsBooster)
  opdw = (OutPortDefinitionWidget*)ui->tableWidget->cellWidget(1,8);
 else
  opdw = (OutPortDefinitionWidget*)ui->tableWidget->cellWidget(1,16);

 opdw->setBlinkSb((cfg&0xff)>>4);

 on_btnReadAll_clicked();

}
LocoIOAddress* LocoIOFrame::address() { return _address;}
