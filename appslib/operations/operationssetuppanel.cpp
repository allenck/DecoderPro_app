#include "operationssetuppanel.h"
#include "operationssetupxml.h"
#include "setup.h"
#include <QBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include "jtextarea.h"
#include "QComboBox"
#include "QGridLayout"
#include <QGroupBox>
#include "jtextfield.h"
#include <QCheckBox>
#include "control.h"
#include "locoicon.h"
#include "flowlayout.h"
#include <QMessageBox>
#include "autobackup.h"
#include "exceptions.h"
#include <route.h>
#include "operationssetupframe.h"
#include "routemanager.h"
#include "routelocation.h"
#include "route.h"
#include "routemanagerxml.h"
#include <QValidator>
#include "cartypes.h"
#include "backupdialog.h"
#include "restoredialog.h"
#include "webserverpreferences.h"
#include "joptionpane.h"

//OperationsSetupPanel::OperationsSetupPanel(QWidget *parent) :
//  OperationsPreferencesPanel(parent)
//{
//}
namespace Operations
{
/**
 * Frame for user edit of operation parameters
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012
 * @version $Revision: 28746 $
 */
///*public*/ class OperationsSetupPanel extends OperationsPreferencesPanel implements PropertyChangeListener {



 /*public*/ OperationsSetupPanel::OperationsSetupPanel(QWidget *parent) :
OperationsPreferencesPanel(parent)
 {
  //super();
  /**
   *
   */

  // labels
  textIconNorth = new QLabel(tr("Northbound Train Icon Color"));
  textIconSouth = new QLabel(tr("Southbound Train Icon Color"));
  textIconEast = new QLabel(tr("Eastbound Train Icon Color"));
  textIconWest = new QLabel(tr("Westbound Train Icon Color"));
  textIconLocal = new QLabel(tr("Switcher Icon Color"));
  textIconTerminate = new QLabel(tr("Terminated Train Icon Color"));
  // QLabel textComment = new QLabel(tr("Comment"));

  // major buttons
  backupButton = new QPushButton(tr("Backup"));
  restoreButton = new QPushButton(tr("Restore"));
  saveButton = new QPushButton(tr("Save"));

  // radio buttons
  scaleZ = new QRadioButton("Z"); // NOI18N
  scaleN = new QRadioButton("N"); // NOI18N
  scaleTT = new QRadioButton("TT"); // NOI18N
  scaleHOn3 = new QRadioButton("HOn3"); // NOI18N
  scaleOO = new QRadioButton("OO"); // NOI18N
  scaleHO = new QRadioButton("HO"); // NOI18N
  scaleSn3 = new QRadioButton("Sn3"); // NOI18N
  scaleS = new QRadioButton("S"); // NOI18N
  scaleOn3 = new QRadioButton("On3"); // NOI18N
  scaleO = new QRadioButton("O"); // NOI18N
  scaleG = new QRadioButton("G"); // NOI18N

  typeDesc = new QRadioButton(tr("Descriptive"));
  typeAAR = new QRadioButton(tr("AAR"));

  feetUnit = new QRadioButton(tr("Feet"));
  meterUnit = new QRadioButton(tr("Meter"));

  // check boxes
  eastCheckBox = new QCheckBox(tr("East/West"));
  northCheckBox = new QCheckBox(tr("North/South"));
  mainMenuCheckBox = new QCheckBox(tr("Add Operations Menu to Main Menu"));
  closeOnSaveCheckBox = new QCheckBox(tr("Close Windows on Save"));
  autoSaveCheckBox = new QCheckBox(tr("Auto Save"));
  autoBackupCheckBox = new QCheckBox(tr("Auto Backup"));
  iconCheckBox = new QCheckBox(tr("Enable Icon SetX&Y"));
  appendCheckBox = new QCheckBox(tr("Append Loco Number"));
// rfidCheckBox = new QCheckBox(tr("EnableRfid"));

  // text field
  // ownerTextField = new JTextField(10);
  panelTextField = new JTextField(30);
  railroadNameTextField = new JTextField(35);
  maxLengthTextField = new JTextField(5);
  maxEngineSizeTextField = new JTextField(3);
  maxEngineSizeTextField->setValidator(new QIntValidator(1,6));
  hptTextField = new JTextField(3);
  hptTextField->setValidator(new QIntValidator);
  switchTimeTextField = new JTextField(3);
  switchTimeTextField->setValidator(new QIntValidator);
  travelTimeTextField = new JTextField(3);
  travelTimeTextField->setValidator(new QIntValidator);
  yearTextField = new JTextField(4);
  yearTextField->setValidator(new QIntValidator);

  // combo boxes
  northComboBox = new QComboBox();
  southComboBox = new QComboBox();
  eastComboBox = new QComboBox();
  westComboBox = new QComboBox();
  localComboBox = new QComboBox();
  terminateComboBox = new QComboBox();

  // text area
  commentTextArea = new JTextArea(2, 80);

  // the following code sets the frame's initial state
  // create manager to load operation settings
  OperationsSetupXml::instance();

  // load fields
  maxLengthTextField->setText(QString::number(Setup::getMaxTrainLength()));
  maxEngineSizeTextField->setText(QString::number(Setup::getMaxNumberEngines()));
  hptTextField->setText(QString::number(Setup::getHorsePowerPerTon()));
  switchTimeTextField->setText(QString::number(Setup::getSwitchTime()));
  travelTimeTextField->setText(QString::number(Setup::getTravelTime()));
  panelTextField->setText(Setup::getPanelName());
  yearTextField->setText(Setup::getYearModeled());
  commentTextArea->setText(Setup::getComment());

  // load checkboxes
  mainMenuCheckBox->setChecked(Setup::isMainMenuEnabled());
  closeOnSaveCheckBox->setChecked(Setup::isCloseWindowOnSaveEnabled());
  autoSaveCheckBox->setChecked(Setup::isAutoSaveEnabled());
  autoBackupCheckBox->setChecked(Setup::isAutoBackupEnabled());
  iconCheckBox->setChecked(Setup::isTrainIconCordEnabled());
  appendCheckBox->setChecked(Setup::isTrainIconAppendEnabled());

  // add tool tips
  backupButton->setToolTip(tr("Creates operations backup files "));
  restoreButton->setToolTip(tr("Restores operations files using backup files "));
  saveButton->setToolTip(tr("Writes this window's settings to file"));
  panelTextField->setToolTip(tr("Enter the panel's name"));
  yearTextField->setToolTip(tr("Optionally enter four digits representing the year that your are modeling"));
  autoSaveCheckBox->setToolTip(tr("When selected, operations files are automatically saved after a change is made"));
  autoBackupCheckBox->setToolTip(tr("When selected, a backup copy of your operation files is created at startup"));
  maxLengthTextField->setToolTip(tr("Enter the maximum scale length of your trains"));
  maxEngineSizeTextField->setToolTip(tr("Enter the maximum number of locos that can be assigned to a train"));
  hptTextField->setToolTip(tr("HPperTonTip"));
  switchTimeTextField->setToolTip(tr("Enter in minutes the average time it takes to pull or spot a car"));
  travelTimeTextField->setToolTip(tr("Enter in minutes the average time it takes to travel between locations"));
  railroadNameTextField->setToolTip(tr("To change the railroad name, go to Edit->Preferences->Railroad Name"));
  commentTextArea->setToolTip(tr("Comment for backup and restoring files. Also shown on train build reports"));

  // Layout the panel by rows
  //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(this);

  QWidget* panel = new QWidget();
  QVBoxLayout* panelLayout = new QVBoxLayout(panel);
  panelLayout->setObjectName("panelLayout");

  QScrollArea* panelPane = new QScrollArea(/*panel*/);
  //panelPane->setWidget(panel);
  //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
  //panelPane.setBorder(BorderFactory.createTitledBorder(""));

  // row 1a
  QWidget* p1 = new QWidget();
  p1->setObjectName("p1");
  //p1.setLayout(new BoxLayout(p1, BoxLayout.X_AXIS));
  QHBoxLayout* p1Layout = new QHBoxLayout(p1);
  p1Layout->setObjectName("p1Layout");
  QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 5px; margin-top: 1ex; /* leave space at the top for the title */} "
                 "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  QGroupBox* pRailroadName = new QGroupBox();
  pRailroadName->setLayout(new QGridLayout());
  //pRailroadName.setBorder(BorderFactory.createTitledBorder(tr("RailroadName")));
  pRailroadName->setStyleSheet(gbStyleSheet);
  pRailroadName->setTitle(tr("Railroad Name"));
  addItem(pRailroadName, railroadNameTextField, 0, 0);
  p1Layout->addWidget(pRailroadName);

  // row 1b
  QGroupBox* pTrainDir = new QGroupBox();
  pTrainDir->setLayout(new QGridLayout());
  //pTrainDir.setBorder(BorderFactory.createTitledBorder(tr("direction")));
  pTrainDir->setStyleSheet(gbStyleSheet);
  pTrainDir->setTitle(tr("direction"));
  addItemLeft(pTrainDir, northCheckBox, 1, 2);
  addItemLeft(pTrainDir, eastCheckBox, 2, 2);
  p1Layout->addWidget(pTrainDir);

  setDirectionCheckBox(Setup::getTrainDirection());

  // row 3a
  QWidget* p3 = new QWidget();
  p3->setObjectName("p3");
  //p3.setLayout(new BoxLayout(p3, BoxLayout.X_AXIS));
  QHBoxLayout* p3Layout = new QHBoxLayout(p3);

  QGroupBox* pTrainLength = new QGroupBox();
  //pTrainLength->setLayout(new QGridLayout);
  // /pTrainLength.setBorder(BorderFactory.createTitledBorder(tr("MaxLength")));
  pTrainLength->setStyleSheet(gbStyleSheet);
  pTrainLength->setTitle(tr("Maximum Train Length"));
  addItem(pTrainLength, maxLengthTextField, 0, 0);
  p3Layout->addWidget(pTrainLength);

  // row 3b
  QGroupBox* pMaxEngine = new QGroupBox();
  //pMaxEngine->setLayout(new QGridLayout);
  //pMaxEngine.setBorder(BorderFactory.createTitledBorder(tr("MaxEngine")));
  pMaxEngine->setStyleSheet(gbStyleSheet);
  pMaxEngine->setTitle(tr("Max Locos per Train"));
  addItem(pMaxEngine, maxEngineSizeTextField, 0, 0);
  p3Layout->addWidget(pMaxEngine);

  // row 3c
  QGroupBox* pHPT = new QGroupBox();
  //pHPT->setLayout(new QGridLayout);
  //pHPT.setBorder(BorderFactory.createTitledBorder(tr("HPT")));
  pHPT->setStyleSheet(gbStyleSheet);
  pHPT->setTitle(tr("Horsepower per Ton"));
  addItem(pHPT, hptTextField, 0, 0);
  p3Layout->addWidget(pHPT);

  QGroupBox* pSwitchTime = new QGroupBox();
  //pSwitchTime->setLayout(new QGridLayout);
  //pSwitchTime.setBorder(BorderFactory.createTitledBorder(tr("MoveTime")));
  pSwitchTime->setStyleSheet(gbStyleSheet);
  pSwitchTime->setTitle(tr("Switch Time (minutes)"));
  addItem(pSwitchTime, switchTimeTextField, 0, 0);
  p3Layout->addWidget(pSwitchTime);

  // row 3d
  QGroupBox* pTravelTime = new QGroupBox();
  //pTravelTime.setBorder(BorderFactory.createTitledBorder(tr("TravelTime")));
  pTravelTime->setStyleSheet(gbStyleSheet);
  pTravelTime->setTitle(tr("Travel Time (minutes)"));
  addItem(pTravelTime, travelTimeTextField, 0, 0);
  p3Layout->addWidget(pTravelTime);

  // row 2
  QGroupBox* pScale = new QGroupBox();
  pScale->setObjectName("pScale");
  FlowLayout* pScaleLayout = new FlowLayout(pScale);
  //pScale.setBorder(BorderFactory.createTitledBorder(tr("Scale")));
  pScale->setStyleSheet(gbStyleSheet);
  pScale->setTitle(tr("Scale)"));


  QButtonGroup* scaleGroup = new QButtonGroup();
  scaleGroup->addButton(scaleZ);
  scaleGroup->addButton(scaleN);
  scaleGroup->addButton(scaleTT);
  scaleGroup->addButton(scaleHOn3);
  scaleGroup->addButton(scaleOO);
  scaleGroup->addButton(scaleHO);
  scaleGroup->addButton(scaleSn3);
  scaleGroup->addButton(scaleS);
  scaleGroup->addButton(scaleOn3);
  scaleGroup->addButton(scaleO);
  scaleGroup->addButton(scaleG);

  pScaleLayout->addWidget(scaleZ);
  pScaleLayout->addWidget(scaleN);
  pScaleLayout->addWidget(scaleTT);
  pScaleLayout->addWidget(scaleHOn3);
  pScaleLayout->addWidget(scaleOO);
  pScaleLayout->addWidget(scaleHO);
  pScaleLayout->addWidget(scaleSn3);
  pScaleLayout->addWidget(scaleS);
  pScaleLayout->addWidget(scaleOn3);
  pScaleLayout->addWidget(scaleO);
  pScaleLayout->addWidget(scaleG);
  setScale();
  // row 4a
  QWidget* p9 = new QWidget();
  p9->setObjectName("p9");
  //p9.setLayout(new BoxLayout(p9, BoxLayout.X_AXIS));
  QHBoxLayout* p9Layout = new QHBoxLayout(p9);


  QGroupBox* pCarTypeButtons = new QGroupBox();
  //pCarTypeButtons.setBorder(BorderFactory.createTitledBorder(tr("CarTypes")));
  QHBoxLayout* pCarTypeButtonsLayout = new QHBoxLayout(pCarTypeButtons);
  pCarTypeButtons->setStyleSheet(gbStyleSheet);
  pCarTypeButtons->setTitle(tr("Optional Year Modeled"));
  QButtonGroup* carTypeGroup = new QButtonGroup();
  carTypeGroup->addButton(typeDesc);
  carTypeGroup->addButton(typeAAR);
  pCarTypeButtonsLayout->addWidget(typeDesc);
  pCarTypeButtonsLayout->addWidget(typeAAR);
  p9Layout->addWidget(pCarTypeButtons);
  setCarTypes();

  // row 4b
  QGroupBox* pLengthUnit = new QGroupBox();
  QHBoxLayout* pLengthUnitLayout = new QHBoxLayout(pLengthUnit);
  //pLengthUnit.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutLength")));
  QButtonGroup* lengthUnitGroup = new QButtonGroup();
  lengthUnitGroup->addButton(feetUnit);
  lengthUnitGroup->addButton(meterUnit);
  pLengthUnitLayout->addWidget(feetUnit);
  pLengthUnitLayout->addWidget(meterUnit);
  p9Layout->addWidget(pLengthUnit);
  setLengthUnit();

  // row 4c
  QGroupBox* pYearModeled = new QGroupBox();
  QHBoxLayout* pYearModeledLayout = new QHBoxLayout(pYearModeled);
  //pYearModeled.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutYearModeled")));
  pYearModeled->setStyleSheet(gbStyleSheet);
  pYearModeled->setTitle(tr("Optional Year Modeled"));
  pYearModeledLayout->addWidget(yearTextField);

  p9Layout->addWidget(pYearModeled);

  // Option panel
  QGroupBox* options = new QGroupBox();
  options->setLayout(new QGridLayout());
  //options.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutOptions")));
  options->setStyleSheet(gbStyleSheet);
  options->setTitle(tr("Options"));

  addItem(options, mainMenuCheckBox, 0, 0);
  addItem(options, closeOnSaveCheckBox, 1, 0);
  addItem(options, autoSaveCheckBox, 2, 0);
  addItem(options, autoBackupCheckBox, 3, 0);

  // p9.add(options);
  // 1st scroll panel
  panelLayout->addWidget(p1);
  panelLayout->addWidget(pScale);
  panelLayout->addWidget(p3);
  panelLayout->addWidget(p9);

  QGroupBox* pIcon = new QGroupBox();
  //pIcon.setLayout(new BoxLayout(pIcon, BoxLayout.Y_AXIS));
  QVBoxLayout* pIconLayout = new QVBoxLayout(pIcon);
  QScrollArea* pIconPane = new QScrollArea(/*pIcon*/);
 // pIconPane->setWidget(pIcon);
  //pIconPane.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutPanelOptions")));
  pIconPane->setWidgetResizable(true);
  // row 1 Icon panel
  QWidget* p1Icon = new QWidget();
  //p1Icon.setLayout(new BoxLayout(p1Icon, BoxLayout.X_AXIS));
  QHBoxLayout* p1IconLayout = new QHBoxLayout(p1Icon);

  QGroupBox* pPanelName = new QGroupBox();
  //pPanelName->setLayout(new QGridLayout());
  //pPanelName.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutPanelName")));
  pPanelName->setStyleSheet(gbStyleSheet);
  pPanelName->setTitle(tr("Panel Name"));
  addItem(pPanelName, panelTextField, 0, 0);
  p1IconLayout->addWidget(pPanelName);

  QGroupBox* pIconControl = new QGroupBox();
  //pIconControl->setLayout(new QGridLayout());
  //pIconControl.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutIconOptions")));
  pIconControl->setStyleSheet(gbStyleSheet);
  pIconControl->setTitle(tr("Icon Options"));
  addItem(pIconControl, appendCheckBox, 0, 0);
  addItem(pIconControl, iconCheckBox, 1, 0);
  p1IconLayout->addWidget(pIconControl);

  pIconLayout->addWidget(p1Icon );

  QGroupBox* pIconColors = new QGroupBox();
  //pIconColors->setLayout(new QGridLayout());
  //pIconColors.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutIconColors")));
  pIconColors->setStyleSheet(gbStyleSheet);
  pIconColors->setTitle(tr("Icon Colors"));

  addItem(pIconColors, textIconNorth, 0, 4);
  addItemLeft(pIconColors, northComboBox, 1, 4);
  addItem(pIconColors, textIconSouth, 0, 5);
  addItemLeft(pIconColors, southComboBox, 1, 5);
  addItem(pIconColors, textIconEast, 0, 8);
  addItemLeft(pIconColors, eastComboBox, 1, 8);
  addItem(pIconColors, textIconWest, 0, 9);
  addItemLeft(pIconColors, westComboBox, 1, 9);
  addItem(pIconColors, textIconLocal, 0, 10);
  addItemLeft(pIconColors, localComboBox, 1, 10);
  addItem(pIconColors, textIconTerminate, 0, 11);
  addItemLeft(pIconColors, terminateComboBox, 1, 11);

  pIconLayout->addWidget(pIconColors);

  loadIconComboBox(northComboBox);
  loadIconComboBox(southComboBox);
  loadIconComboBox(eastComboBox);
  loadIconComboBox(westComboBox);
  loadIconComboBox(localComboBox);
  loadIconComboBox(terminateComboBox);
  northComboBox->setCurrentIndex(northComboBox->findText(Setup::getTrainIconColorNorth()));
  southComboBox->setCurrentIndex(southComboBox->findText(Setup::getTrainIconColorSouth()));
  eastComboBox->setCurrentIndex(eastComboBox->findText(Setup::getTrainIconColorEast()));
  westComboBox->setCurrentIndex(westComboBox->findText(Setup::getTrainIconColorWest()));
  localComboBox->setCurrentIndex(localComboBox->findText(Setup::getTrainIconColorLocal()));
  terminateComboBox->setCurrentIndex(terminateComboBox->findText(Setup::getTrainIconColorTerminate()));

  // comment
  QGroupBox* pC = new QGroupBox();
  //pC->setLayout(new QGridLayout());
  //pC.setBorder(BorderFactory.createTitledBorder(tr("Comment")));
  pC->setStyleSheet(gbStyleSheet);
  pC->setTitle(tr("Comment"));
  //JScrollPane commentScroller = new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  //QScrollArea* commentScroller = new
  addItem(pC, /*commentScroller*/commentTextArea, 0, 0);

  pIconLayout->addWidget(pC);

  // adjust text area width based on window size
  adjustTextAreaColumnWidth(pC, commentTextArea);

  // row 15
  QWidget* pControl = new QWidget();
  pControl->setLayout(new QGridLayout());
  addItem(pControl, restoreButton, 0, 9);
  addItem(pControl, backupButton, 1, 9);
  addItem(pControl, saveButton, 3, 9);

  panelPane->setWidget(panel);
  panelPane->setWidgetResizable(true);
  panelPane->setVisible(true);
  QObjectList ol = panelPane->widget()->children();
  QObjectList oll = panelLayout->children();
  thisLayout->addWidget(panelPane /*panel*/);

  thisLayout->addWidget(options);

  pIconPane->setWidget(pIcon);
  thisLayout->addWidget(pIconPane /*pIcon*/);
//        add(pC);
  thisLayout->addWidget(pControl);

  // setup buttons
  addButtonAction(backupButton);
  addButtonAction(restoreButton);
  addButtonAction(saveButton);
  addCheckBoxAction(eastCheckBox);
  addCheckBoxAction(northCheckBox);

  initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight500));

  // now provide the railroad name
  railroadNameTextField->setText(Setup::getRailroadName()); // default
//        if (Setup::getRailroadName()==(WebServerManager.getWebServerPreferences().getRailRoadName())) {
//            railroadNameTextField.setEnabled(false);
//        }
  createShutDownTask();
  adjustSize();
 }

  // Save, Delete, Add buttons
// @Override
/*public*/ void OperationsSetupPanel::buttonActionPerformed(QWidget* ae)
{
 QPushButton* source = (QPushButton*)ae;

 if (source == backupButton)
 {
  // Backup and Restore dialogs are now modal. so no need to check for an existing instance
  BackupDialog* bd = new BackupDialog();
  bd->adjustSize();
//          bd.setLocationRelativeTo(null);
  bd->setVisible(true);
  bd->exec();
 }

 if (source == restoreButton)
 {
  RestoreDialog* rd = new RestoreDialog();
  rd->adjustSize();
//          rd.setLocationRelativeTo(null);
  rd->setVisible(true);
 }

 if (source == saveButton)
 {
  save();
 }
}

/*private*/ void OperationsSetupPanel::save()
{
 // check input fields
 int maxTrainLength;
 //try {
 bool ok;
     maxTrainLength = maxLengthTextField->text().toInt(&ok);
     if(!ok) {
     //JOptionPane.showMessageDialog(this, tr("MaxLength"),
//                  tr("CanNotAcceptNumber"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Maximum Train Length"), tr("Can not accept number") );
     return;
 }

 //try {
     maxEngineSizeTextField->text().toInt(&ok);
     if(!ok) {
//          JOptionPane.showMessageDialog(this, tr("MaxEngine"),
//                  tr("CanNotAcceptNumber"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Max Locos per Train"), tr("Can not accept number") );
     return;
 }

 //try {
     hptTextField->text().toInt(&ok);
     if(!ok)
     {
//          JOptionPane.showMessageDialog(this, tr("HPT"), tr("CanNotAcceptNumber"),
//                  JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Horsepower per Ton"), tr("Can not accept number"));

     return;
     }

 //try {
     switchTimeTextField->text().toInt(&ok);
     if(!ok) {
//          JOptionPane.showMessageDialog(this, tr("MoveTime"), tr("CanNotAcceptNumber"),
//                  JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Switch Time (minutes)"), tr("Can not accept number"));
     return;
 }

 //try {
     travelTimeTextField->text().toInt(&ok);
 if(!ok)
 {
//          JOptionPane.showMessageDialog(this, tr("TravelTime"), Bundle
//                  .getMessage("CanNotAcceptNumber"), JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Travel Time (minutes)"), tr("CanNotAcceptNumber"));
     return;
 }

 //try {
     if (yearTextField->text().trimmed()!=(""))
     {
      yearTextField->text().trimmed().toInt(&ok);
     }
 if(!ok)
 {
//          JOptionPane.showMessageDialog(this, tr("BorderLayoutYearModeled"), Bundle
//                  .getMessage("CanNotAcceptNumber"), JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Optional Year Modeled"), tr("Can not accept number"));
     return;
 }

 // if max train length has changed, check routes
 checkRoutes();

 // set car types
 if (typeDesc->isChecked() && Setup::getCarTypes()!=(Setup::DESCRIPTIVE) || typeAAR->isChecked()
         && Setup::getCarTypes()!=(Setup::AAR))
 {

  // backup files before changing car type descriptions
  AutoBackup* backup = new AutoBackup();
  //try {
      backup->autoBackup();
//          } catch (Exception ex) {
//              UnexpectedExceptionContext context = new UnexpectedExceptionContext(ex,
//                      "Auto backup before changing Car types"); // NOI18N
//              new ExceptionDisplayFrame(context);
//          }

  if (typeDesc->isChecked()) {
      CarTypes::instance()->changeDefaultNames(Setup::DESCRIPTIVE);
      Setup::setCarTypes(Setup::DESCRIPTIVE);
  } else {
      CarTypes::instance()->changeDefaultNames(Setup::AAR);
      Setup::setCarTypes(Setup::AAR);
  }

  // save all the modified files
  OperationsXml::save();
 }
 // main menu enabled?
 Setup::setMainMenuEnabled(mainMenuCheckBox->isChecked());
 Setup::setCloseWindowOnSaveEnabled(closeOnSaveCheckBox->isChecked());
 Setup::setAutoSaveEnabled(autoSaveCheckBox->isChecked());
 Setup::setAutoBackupEnabled(autoBackupCheckBox->isChecked());

 // add panel name to setup
 Setup::setPanelName(panelTextField->text());

 // train Icon X&Y
 Setup::setTrainIconCordEnabled(iconCheckBox->isChecked());
 Setup::setTrainIconAppendEnabled(appendCheckBox->isChecked());

 // save train icon colors
 Setup::setTrainIconColorNorth( northComboBox->currentText());
 Setup::setTrainIconColorSouth( southComboBox->currentText());
 Setup::setTrainIconColorEast( eastComboBox->currentText());
 Setup::setTrainIconColorWest( westComboBox->currentText());
 Setup::setTrainIconColorLocal( localComboBox->currentText());
 Setup::setTrainIconColorTerminate( terminateComboBox->currentText());
 // set train direction
 int direction = 0;
 if (eastCheckBox->isChecked()) {
     direction = Setup::EAST + Setup::WEST;
 }
 if (northCheckBox->isChecked()) {
     direction += Setup::NORTH + Setup::SOUTH;
 }
 Setup::setTrainDirection(direction);
 Setup::setMaxNumberEngines(maxEngineSizeTextField->text().toInt());
 Setup::setHorsePowerPerTon(hptTextField->text().toInt());
 // set switch time
 Setup::setSwitchTime(switchTimeTextField->text().toInt());
 // set travel time
 Setup::setTravelTime(travelTimeTextField->text().toInt());
 // set scale
 if (scaleZ->isChecked()) {
     Setup::setScale(Setup::Z_SCALE);
 }
 if (scaleN->isChecked()) {
     Setup::setScale(Setup::N_SCALE);
 }
 if (scaleTT->isChecked()) {
     Setup::setScale(Setup::TT_SCALE);
 }
 if (scaleOO->isChecked()) {
     Setup::setScale(Setup::OO_SCALE);
 }
 if (scaleHOn3->isChecked()) {
     Setup::setScale(Setup::HOn3_SCALE);
 }
 if (scaleHO->isChecked()) {
     Setup::setScale(Setup::HO_SCALE);
 }
 if (scaleSn3->isChecked()) {
     Setup::setScale(Setup::Sn3_SCALE);
 }
 if (scaleS->isChecked()) {
     Setup::setScale(Setup::S_SCALE);
 }
 if (scaleOn3->isChecked()) {
     Setup::setScale(Setup::On3_SCALE);
 }
 if (scaleO->isChecked()) {
     Setup::setScale(Setup::O_SCALE);
 }
 if (scaleG->isChecked()) {
     Setup::setScale(Setup::G_SCALE);
 }
 Setup::setRailroadName(railroadNameTextField->text());

 if (Setup::getRailroadName() != (WebServerPreferences::getDefault()->getRailRoadName()))
 {
  Setup::setRailroadName(railroadNameTextField->text());
  int results = JOptionPane::showConfirmDialog(this, tr("Do you want the change your railroad name from \"%1\" to \"%2\"?").arg(           WebServerPreferences::getDefault()->getRailRoadName()).arg( Setup::getRailroadName()), tr("Change your JMRI railroad name?"), JOptionPane::YES_NO_OPTION);
  if (results == JOptionPane::OK_OPTION)
  {
   WebServerPreferences::getDefault()->setRailRoadName(Setup::getRailroadName());
   WebServerPreferences::getDefault()->save();
  }
 }

 // Set Unit of Length
 if (feetUnit->isChecked()) {
     Setup::setLengthUnit(Setup::FEET);
 }
 if (meterUnit->isChecked()) {
     Setup::setLengthUnit(Setup::METER);
 }
 Setup::setYearModeled(yearTextField->text().trimmed());
 // warn about train length being too short
 if (maxTrainLength != Setup::getMaxTrainLength())
 {
  if (maxTrainLength < 500 && Setup::getLengthUnit()==(Setup::FEET) || maxTrainLength < 160
          && Setup::getLengthUnit()==(Setup::METER))
  {
//              JOptionPane.showMessageDialog(this, MessageFormat.format(tr("LimitTrainLength"),
//                      new Object[]{maxTrainLength, Setup::getLengthUnit().toLowerCase()}), Bundle
//                      .getMessage("WarningTooShort"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this, tr("Warning train length might be too short!"), tr("Are you sure that you want to limit your trains to %1 scale %2?").arg(maxTrainLength).arg(Setup::getLengthUnit().toLower()));
  }
 }
 // set max train length
 Setup::setMaxTrainLength(maxLengthTextField->text().toInt());
 Setup::setComment(commentTextArea->toHtml());

 OperationsSetupXml::instance()->writeOperationsFile();
 if (Setup::isCloseWindowOnSaveEnabled() && qobject_cast<OperationsSetupFrame*>(this->getTopLevelAncestor()) ) {
     ((OperationsSetupFrame*) this->getTopLevelAncestor())->dispose();
 }
}

// if max train length has changed, check routes
/*private*/ void OperationsSetupPanel::checkRoutes()
{
  int maxLength = maxLengthTextField->text().toInt();
  if (maxLength > Setup::getMaxTrainLength()) {
//          JOptionPane.showMessageDialog(this, tr("RouteLengthNotModified"), MessageFormat.format(
//                  tr("MaxTrainLengthIncreased"), new Object[]{maxLength,
//                      Setup::getLengthUnit().toLowerCase()}), JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(this, tr("You''re increased the maximum train length to %1 %2.").arg(maxLength).arg("Setup::getLengthUnit().toLower()"), tr("You need to manually edit your train's routes if you want to use the longer length!"));
  }
  if (maxLength < Setup::getMaxTrainLength())
  {
   QString sb;// = new StringBuilder();
   RouteManager* routeManager = RouteManager::instance();
   QList<Route*> routes = routeManager->getRoutesByNameList();
   int count = 0;
   foreach (Route* route, routes)
   {
    foreach (RouteLocation* rl, *route->getLocationsBySequenceList())
    {
     if (rl->getMaxTrainLength() > maxLength)
     {
      QString s = tr("Route (%1) has a location (%2) with a maximum departure train length (%3) that exceeds the new maximum length (%4)").arg(route->getName()).arg(rl->getName()).arg(rl->getMaxTrainLength()).arg(maxLength);
      log->info(s);
      sb.append(s).append(NEW_LINE);
      count++;
      break;
     }
    }
   // maximum of 20 route warnings
  if (count > 20)
  {
   sb.append(tr("More")).append(NEW_LINE);
     break;
  }
 }
 if (sb.length() > 0)
 {
//              JOptionPane.showMessageDialog(this, sb.toString(), tr("YouNeedToAdjustRoutes"),
//                      JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(this, sb, tr("You need to adjust your routes! (You can also view this warning message using the JMRI system console) "));
//              if (JOptionPane.showConfirmDialog(null, MessageFormat.format(Bundle
//                      .getMessage("ChangeMaximumTrainDepartureLength"), new Object[]{maxLength}), Bundle
//                      .getMessage("ModifyAllRoutes"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
  if(QMessageBox::question(this, tr(""), tr(""), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
  {
#if 0 // TODO:
         routes.stream().forEach(
                 (route) -> {
                     route.getLocationsBySequenceList().stream().filter(
                             (rl) -> (rl.getMaxTrainLength() > maxLength)).map(
                             (rl) -> {
                                 log->debug("Setting route ({}) routeLocation ({}) max traim length to {}",
                                         route.getName(), rl.getName(), maxLength); // NOI18N
                                 return rl;
                             }).forEach((rl) -> {
                                 rl.setMaxTrainLength(maxLength);
                             });
                 });
         // save the route changes
         RouteManagerXml::instance().writeOperationsFile();
#endif
    }
   }
  }
 }

 //@Override
  /*public*/ void OperationsSetupPanel::checkBoxActionPerformed(QWidget* ae)
  {
 QCheckBox* source = (QCheckBox*)ae;
      if (source == northCheckBox) {
          if (!northCheckBox->isChecked()) {
              eastCheckBox->setChecked(true);
          }
      }
      if (source == eastCheckBox) {
          if (!eastCheckBox->isChecked()) {
              northCheckBox->setChecked(true);
          }
      }
      int direction = 0;
      if (eastCheckBox->isChecked()) {
          direction += Setup::EAST;
      }
      if (northCheckBox->isChecked()) {
          direction += Setup::NORTH;
      }
      setDirectionCheckBox(direction);
  }

  /*private*/ void OperationsSetupPanel::setScale() {
      int scale = Setup::getScale();
      switch (scale) {
          case Setup::Z_SCALE:
              scaleZ->setChecked(true);
              break;
          case Setup::N_SCALE:
              scaleN->setChecked(true);
              break;
          case Setup::TT_SCALE:
              scaleTT->setChecked(true);
              break;
          case Setup::HOn3_SCALE:
              scaleHOn3->setChecked(true);
              break;
          case Setup::OO_SCALE:
              scaleOO->setChecked(true);
              break;
          case Setup::HO_SCALE:
              scaleHO->setChecked(true);
              break;
          case Setup::Sn3_SCALE:
              scaleSn3->setChecked(true);
              break;
          case Setup::S_SCALE:
              scaleS->setChecked(true);
              break;
          case Setup::On3_SCALE:
              scaleOn3->setChecked(true);
              break;
          case Setup::O_SCALE:
              scaleO->setChecked(true);
              break;
          case Setup::G_SCALE:
              scaleG->setChecked(true);
              break;
          default:
              log->error("Unknown scale");
      }
  }

  /*private*/ void OperationsSetupPanel::setCarTypes() {
      typeDesc->setChecked(Setup::getCarTypes()==(Setup::DESCRIPTIVE));
      typeAAR->setChecked(Setup::getCarTypes()==(Setup::AAR));
  }

  /*private*/ void OperationsSetupPanel::setDirectionCheckBox(int direction) {
      eastCheckBox->setChecked((direction & Setup::EAST) > 0);
      textIconEast->setVisible((direction & Setup::EAST) > 0);
      eastComboBox->setVisible((direction & Setup::EAST) > 0);
      textIconWest->setVisible((direction & Setup::EAST) > 0);
      westComboBox->setVisible((direction & Setup::EAST) > 0);
      northCheckBox->setChecked((direction & Setup::NORTH) > 0);
      textIconNorth->setVisible((direction & Setup::NORTH) > 0);
      northComboBox->setVisible((direction & Setup::NORTH) > 0);
      textIconSouth->setVisible((direction & Setup::NORTH) > 0);
      southComboBox->setVisible((direction & Setup::NORTH) > 0);
  }

  /*private*/ void OperationsSetupPanel::setLengthUnit() {
      feetUnit->setChecked(Setup::getLengthUnit()==(Setup::FEET));
      meterUnit->setChecked(Setup::getLengthUnit()==(Setup::METER));
  }

  /*private*/ void OperationsSetupPanel::loadIconComboBox(QComboBox* comboBox) {
      foreach (QString color, LocoIcon::getLocoColors()) {
          comboBox->addItem(color);
      }
  }
#if 0
  @Override
  /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
      log->debug("propertyChange ({}), new: ({})", e.getPropertyName(), e.getNewValue());
  }

  @Override
  /*public*/ String getTabbedPreferencesTitle() {
      return tr("TitleOperationsSetup");
  }

  @Override
  /*public*/ String getPreferencesTooltip() {
      return null;
  }

  @Override
  /*public*/ void savePreferences() {
      this.save();
  }
  //@Override
  /*public*/ bool isDirty() {
      if (// set car types
              (typeDesc->isChecked() && !Setup::getCarTypes()==(Setup::DESCRIPTIVE))
              || (typeAAR->isChecked() && !Setup::getCarTypes()==(Setup::AAR))
              // main menu enabled?
              || Setup::isMainMenuEnabled() != mainMenuCheckBox->isChecked()
              || Setup::isCloseWindowOnSaveEnabled() != closeOnSaveCheckBox->isChecked()
              || Setup::isAutoSaveEnabled() != autoSaveCheckBox->isChecked()
              || Setup::isAutoBackupEnabled() != autoBackupCheckBox->isChecked()
              // add panel name to setup
              || !Setup::getPanelName()==(panelTextField.getText())
              // train Icon X&Y
              || Setup::isTrainIconCordEnabled() != iconCheckBox->isChecked()
              || Setup::isTrainIconAppendEnabled() != appendCheckBox->isChecked()
              // train Icon X&Y
              || Setup::isTrainIconCordEnabled() != iconCheckBox->isChecked()
              || Setup::isTrainIconAppendEnabled() != appendCheckBox->isChecked()
              // save train icon colors
              || !Setup::getTrainIconColorNorth()==(northComboBox->getSelectedItem())
              || !Setup::getTrainIconColorSouth()==(southComboBox->getSelectedItem())
              || !Setup::getTrainIconColorEast()==(eastComboBox->getSelectedItem())
              || !Setup::getTrainIconColorWest()==(westComboBox->getSelectedItem())
              || !Setup::getTrainIconColorLocal()==(localComboBox->getSelectedItem())
              || !Setup::getTrainIconColorTerminate()==(terminateComboBox->getSelectedItem())
              || Setup::getMaxNumberEngines() != Integer.parseInt(maxEngineSizeTextField.getText())
              || Setup::getHorsePowerPerTon() != Integer.parseInt(hptTextField.getText())
              // switch time
              || Setup::getSwitchTime() != Integer.parseInt(switchTimeTextField.getText())
              // travel time
              || Setup::getTravelTime() != Integer.parseInt(travelTimeTextField.getText())
              || !Setup::getYearModeled()==(yearTextField.getText().trim())
              || Setup::getMaxTrainLength() != Integer.parseInt(maxLengthTextField.getText())
              || !Setup::getComment()==(this.commentTextArea.getText())) {
          return true;
      }

      // set train direction
      int direction = 0;
      if (eastCheckBox->isChecked()) {
          direction = Setup::EAST + Setup::WEST;
      }
      if (northCheckBox->isChecked()) {
          direction += Setup::NORTH + Setup::SOUTH;
      }
      // set scale
      int scale = 0;
      if (scaleZ->isChecked()) {
          scale = Setup::Z_SCALE;
      }
      if (scaleN->isChecked()) {
          scale = Setup::N_SCALE;
      }
      if (scaleTT->isChecked()) {
          scale = Setup::TT_SCALE;
      }
      if (scaleOO->isChecked()) {
          scale = Setup::OO_SCALE;
      }
      if (scaleHOn3->isChecked()) {
          scale = Setup::HOn3_SCALE;
      }
      if (scaleHO->isChecked()) {
          scale = Setup::HO_SCALE;
      }
      if (scaleSn3->isChecked()) {
          scale = Setup::Sn3_SCALE;
      }
      if (scaleS->isChecked()) {
          scale = Setup::S_SCALE;
      }
      if (scaleOn3->isChecked()) {
          scale = Setup::On3_SCALE;
      }
      if (scaleO->isChecked()) {
          scale = Setup::O_SCALE;
      }
      if (scaleG->isChecked()) {
          scale = Setup::G_SCALE;
      }
      QString lengthUnit = "";
      // Set Unit of Length
      if (feetUnit->isChecked()) {
          lengthUnit = Setup::FEET;
      }
      if (meterUnit->isChecked()) {
          lengthUnit = Setup::METER;
      }
      return ( // train direction
              Setup::getTrainDirection() != direction
              // scale
              || Setup::getScale() != scale
              || !Setup::getRailroadName()==(this.railroadNameTextField.getText())
              // unit of length
              || !Setup::getLengthUnit()==(lengthUnit));
 }
#endif
/*private*/ QWidget* OperationsSetupPanel::getTopLevelAncestor()
{
 return window();
}

}
