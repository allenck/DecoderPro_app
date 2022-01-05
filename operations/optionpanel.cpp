#include "optionpanel.h"
#include "setup.h"
#include <QPushButton>
#include <QButtonGroup>
#include "jcombobox.h"
#include <QBoxLayout>
#include "jtextfield.h"
#include <QRadioButton>
#include <QScrollArea>
#include <QGroupBox>
#include "gridbaglayout.h"
#include "trainmanager.h"
#include "logger.h"
#include <QMessageBox>
#include "operationssetupxml.h"
#include "instancemanager.h"
#include "jpanel.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame for user edit of setup options
 *
 * @author Dan Boudreau Copyright (C) 2010, 2011, 2012, 2013
 * @version $Revision: 29350 $
 */
///*public*/ class OptionPanel extends OperationsPreferencesPanel {

 /**
  *
  */
 //private static final long serialVersionUID = -5466426954499681092L;


 /*public*/ OptionPanel::OptionPanel(QWidget* parent) : OperationsPreferencesPanel(parent) {
 log = new Logger("OptionPanel");
 // labels
 // major buttons
 saveButton = new QPushButton(tr("Save"));

 // radio buttons
 buildNormal = new QRadioButton(tr("Normal"));
 buildAggressive = new QRadioButton(tr("Aggressive"));

 // check boxes

 valueCheckBox = new JCheckBox(tr("Enable Value Fields"));
 rfidCheckBox = new JCheckBox(tr("Identification Tag Fields"));
 carLoggerCheckBox = new JCheckBox(tr("Enable Car Logging"));
 engineLoggerCheckBox = new JCheckBox(tr("Enable Engine Logging"));
 trainLoggerCheckBox = new JCheckBox(tr("Enable Train Logging"));

 localInterchangeCheckBox = new JCheckBox(tr("Allow Local Classification/Interchange to C/I Moves"));
 localSpurCheckBox = new JCheckBox(tr("Allow Local Spur to Spur Moves"));
 localYardCheckBox = new JCheckBox(tr("Allow Local Yard to Yard Moves"));

 trainIntoStagingCheckBox = new JCheckBox(tr("Enable Type, Road and Load Restrictions into Staging"));
 stagingAvailCheckBox = new JCheckBox(tr("Make departure track available after train is built"));
 stagingTurnCheckBox = new JCheckBox(tr("Allow cars to return to staging"));
 promptFromTrackStagingCheckBox = new JCheckBox(tr("Prompt for Departure Track from Staging"));
 promptToTrackStagingCheckBox = new JCheckBox(tr("Prompt for Arrival Track into Staging"));
 tryNormalStagingCheckBox->setChecked(Setup::isStagingTryNormalBuildEnabled());

 generateCvsManifestCheckBox = new JCheckBox(tr("Generate CSV Manifest"));
 generateCvsSwitchListCheckBox = new JCheckBox(tr("Generate CSV Switch List"));

 enableVsdCheckBox = new JCheckBox(tr("Enable physical locations for Virtual Sound Decoder"));

 // text field
 rfidTextField = new JTextField(10);
 valueTextField = new JTextField(10);

 // combo boxes
 numberPassesComboBox = new JComboBox();

  // load checkboxes
  localInterchangeCheckBox->setChecked(Setup::isLocalInterchangeMovesEnabled());
  localSpurCheckBox->setChecked(Setup::isLocalSpurMovesEnabled());
  localYardCheckBox->setChecked(Setup::isLocalYardMovesEnabled());

  // staging options
  trainIntoStagingCheckBox->setChecked(Setup::isTrainIntoStagingCheckEnabled());
  stagingAvailCheckBox->setChecked(Setup::isStagingTrackImmediatelyAvail());
  stagingTurnCheckBox->setChecked(Setup::isAllowReturnToStagingEnabled());
  promptToTrackStagingCheckBox->setChecked(Setup::isPromptToStagingEnabled());
  promptFromTrackStagingCheckBox->setChecked(Setup::isPromptFromStagingEnabled());
  tryNormalStagingCheckBox->setChecked(Setup::isStagingTryNormalBuildEnabled());

  // router
  routerCheckBox->setChecked(Setup::isCarRoutingEnabled());
  routerYardCheckBox->setChecked(Setup::isCarRoutingViaYardsEnabled());
  routerStagingCheckBox->setChecked(Setup::isCarRoutingViaStagingEnabled());
  routerAllTrainsBox->setChecked(!Setup::isOnlyActiveTrainsEnabled());
  routerRestrictBox->setChecked(Setup::isCheckCarDestinationEnabled());
  // logging options
  carLoggerCheckBox->setChecked(Setup::isCarLoggerEnabled());
  engineLoggerCheckBox->setChecked(Setup::isEngineLoggerEnabled());
  trainLoggerCheckBox->setChecked(Setup::isTrainLoggerEnabled());
  // save manifests
  saveTrainManifestCheckBox->setChecked(Setup::isSaveTrainManifestsEnabled());

  generateCvsManifestCheckBox->setChecked(Setup::isGenerateCsvManifestEnabled());
  generateCvsSwitchListCheckBox->setChecked(Setup::isGenerateCsvSwitchListEnabled());
  valueCheckBox->setChecked(Setup::isValueEnabled());
  rfidCheckBox->setChecked(Setup::isRfidEnabled());
  enableVsdCheckBox->setChecked(Setup::isVsdPhysicalLocationEnabled());

  // load text fields
  rfidTextField->setText(Setup::getRfidLabel());
  valueTextField->setText(Setup::getValueLabel());

  // add tool tips
  saveButton->setToolTip(tr("Writes this window's settings to file"));
  rfidTextField->setToolTip(tr("Enter the name you want for the Id Tag field"));
  valueTextField->setToolTip(tr("Enter the name you want for the value field"));
  stagingTurnCheckBox->setToolTip(tr("This option is also available per train"));

  // load combobox, allow 2 to 4 passes
  for (int x = 2; x < 5; x++) {
      numberPassesComboBox->addItem(QString::number(x), x);
  }

  numberPassesComboBox->setCurrentIndex(numberPassesComboBox->findData(Setup::getNumberPasses()));

  setLayout(new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

  QWidget* panel = new QWidget();
  panel->setLayout(new QVBoxLayout); //(panel, BoxLayout.Y_AXIS));
  QScrollArea* panelPane = new QScrollArea(/*panel*/);
  panelPane->setWidgetResizable(true);

  // Build Options panel
  JPanel* pBuild = new JPanel();
  pBuild->setLayout(new GridBagLayout); //(pBuild, BoxLayout.Y_AXIS));
  pBuild->setBorder(BorderFactory::createTitledBorder(tr("Build Options")));
  JPanel* pOpt = new JPanel();
  pOpt->setLayout(new GridBagLayout());

  addItem(pOpt, buildNormal, 1, 0);
  addItem(pOpt, buildAggressive, 2, 0);
  addItem(pBuild, pOpt, 1, 0);

  JPanel* pPasses = new JPanel();
  pPasses->setLayout(new GridBagLayout());
  pPasses->setBorder(BorderFactory::createTitledBorder(tr("Number of Passes During Build")));
  addItem(pPasses, numberPassesComboBox, 0, 0);
  addItem(pBuild, pPasses, 1, 1);

  // Switcher Service
  JPanel* pSwitcher = new JPanel();
  pSwitcher->setLayout(new GridBagLayout());
     pSwitcher->setBorder(BorderFactory
             ::createTitledBorder(tr("Switcher Service")));

  addItemLeft(pSwitcher, localInterchangeCheckBox, 1, 1);
  addItemLeft(pSwitcher, localSpurCheckBox, 1, 2);
  addItemLeft(pSwitcher, localYardCheckBox, 1, 3);
  addItemLeft(pBuild, pSwitcher, 1, 2);

  // Staging
  JPanel* pStaging = new JPanel();
  pStaging->setLayout(new GridBagLayout());
  pStaging->setBorder(BorderFactory::createTitledBorder(tr("Build Options")));

  addItemLeft(pStaging, trainIntoStagingCheckBox, 1, 4);
  addItemLeft(pStaging, stagingAvailCheckBox, 1, 5);
  addItemLeft(pStaging, stagingTurnCheckBox, 1, 6);
  addItemLeft(pStaging, promptFromTrackStagingCheckBox, 1, 7);
  addItemLeft(pStaging, promptToTrackStagingCheckBox, 1, 8);
  addItemLeft(pBuild, pStaging, 1, 3);

  // Router panel
  JPanel* pRouter = new JPanel();
  pRouter->setLayout(new GridBagLayout());
  pRouter->setBorder(BorderFactory::createTitledBorder(tr("Car Routing Options")));
  addItemLeft(pRouter, routerCheckBox, 1, 0);
  addItemLeft(pRouter, routerYardCheckBox, 1, 1);
  addItemLeft(pRouter, routerStagingCheckBox, 1, 2);
  addItemLeft(pRouter, routerAllTrainsBox, 1, 3);
  addItemLeft(pRouter, routerRestrictBox, 1, 4);

  // Logger panel
  JPanel* pLogger = new JPanel();
  pLogger->setLayout(new GridBagLayout());
  pLogger->setBorder(BorderFactory::createTitledBorder(tr("Logging Options")));
  addItemLeft(pLogger, engineLoggerCheckBox, 1, 0);
  addItemLeft(pLogger, carLoggerCheckBox, 1, 1);
  addItemLeft(pLogger, trainLoggerCheckBox, 1, 2);

  // Custom Manifests and Switch Lists
  JPanel* pCustom = new JPanel();
  pCustom->setLayout(new GridBagLayout());
  pCustom->setBorder(BorderFactory::createTitledBorder(tr("Custom Manifest and Switch Lists")));
  addItemLeft(pCustom, generateCvsManifestCheckBox, 1, 0);
  addItemLeft(pCustom, generateCvsSwitchListCheckBox, 1, 1);

  // Options
  JPanel* pOption = new JPanel();
  pOption->setLayout(new GridBagLayout());
  pOption->setBorder(BorderFactory::createTitledBorder(tr("Options")));
  addItemLeft(pOption, saveTrainManifestCheckBox, 1, 1);
  addItemLeft(pOption, valueCheckBox, 1, 2);
  addItemLeft(pOption, valueTextField, 2, 2);
  addItemLeft(pOption, rfidCheckBox, 1, 3);
  addItemLeft(pOption, rfidTextField, 2, 3);
  addItemLeft(pOption, enableVsdCheckBox, 1, 4);

  // row 11
  JPanel* pControl = new JPanel();
  pControl->setLayout(new GridBagLayout());
  addItem(pControl, saveButton, 3, 9);

  panel->layout()->addWidget(pBuild);
  panel->layout()->addWidget(pRouter);
  panel->layout()->addWidget(pLogger);
  panel->layout()->addWidget(pCustom);
  panel->layout()->addWidget(pOption);
  panel->layout()->addWidget(pControl);

  panelPane->setWidget(panel);
  layout()->addWidget(panelPane);

  // setup buttons
  addButtonAction(saveButton);

  // radio buttons
  QButtonGroup* buildGroup = new QButtonGroup();
  buildGroup->addButton(buildNormal);
  buildGroup->addButton(buildAggressive);
  addRadioButtonAction(buildNormal);
  addRadioButtonAction(buildAggressive);

  // check boxes
  addCheckBoxAction(routerCheckBox);
  setRouterCheckBoxesEnabled();

  setBuildOption();

  // disable staging option if normal mode
  stagingAvailCheckBox->setEnabled(buildAggressive->isChecked());
  numberPassesComboBox->setEnabled(buildAggressive->isChecked());

  initMinimumSize();
 }

 /*private*/ void OptionPanel::setBuildOption()
 {
  buildNormal->setChecked(!Setup::isBuildAggressive());
  buildAggressive->setChecked(Setup::isBuildAggressive());
 }

 /*private*/ void OptionPanel::enableComponents() {
     // disable staging option if normal mode
     stagingAvailCheckBox->setEnabled(buildAggressive->isChecked());
     numberPassesComboBox->setEnabled(buildAggressive->isChecked());
     tryNormalStagingCheckBox->setEnabled(buildAggressive->isChecked());
 }

 //@Override
 /*public*/ void OptionPanel::radioButtonActionPerformed(QWidget* ae)
 {
  log->debug("radio button selected");
  // can't change the build option if there are trains built
  if (((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->isAnyTrainBuilt()) {
      setBuildOption(); // restore the correct setting
//         JOptionPane.showMessageDialog(this, tr("CanNotChangeBuild"), Bundle
//                 .getMessage("MustTerminateOrReset"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Must terminate or reset all trains"), tr("Can not change build option when there is a built train!"));
  }
  // disable staging option if normal mode
  stagingAvailCheckBox->setEnabled(buildAggressive->isChecked());
  numberPassesComboBox->setEnabled(buildAggressive->isChecked());
 }

 // Save button
 //@Override
 /*public*/ void OptionPanel::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
  if (source == saveButton)
  {
   this->savePreferences();
   if (Setup::isCloseWindowOnSaveEnabled())
   {
    dispose();
   }
  }
 }

 //@Override
 /*protected*/ void OptionPanel::checkBoxActionPerformed(QWidget* ae)
 {
  if ((JCheckBox*)ae == routerCheckBox)
  {
   setRouterCheckBoxesEnabled();
  }
 }

 /*private*/ void OptionPanel::setRouterCheckBoxesEnabled()
 {
  routerYardCheckBox->setEnabled(routerCheckBox->isChecked());
  routerStagingCheckBox->setEnabled(routerCheckBox->isChecked());
  routerAllTrainsBox->setEnabled(routerCheckBox->isChecked());
  routerRestrictBox->setEnabled(routerCheckBox->isChecked());
 }

 //@Override
 /*public*/ QString OptionPanel::getTabbedPreferencesTitle()
 {
  return tr("Options");
 }

// @Override
 /*public*/ QString OptionPanel::getPreferencesTooltip() {
     return "";
 }

 //@Override
 /*public*/ void OptionPanel::savePreferences()
 {
  // build option
  Setup::setBuildAggressive(buildAggressive->isChecked());
  Setup::setNumberPasses(numberPassesComboBox->currentData().toInt());
  // Local moves?
  Setup::setLocalInterchangeMovesEnabled(localInterchangeCheckBox->isChecked());
  Setup::setLocalSpurMovesEnabled(localSpurCheckBox->isChecked());
  Setup::setLocalYardMovesEnabled(localYardCheckBox->isChecked());
  // Staging options
  Setup::setTrainIntoStagingCheckEnabled(trainIntoStagingCheckBox->isChecked());
  Setup::setStagingTrackImmediatelyAvail(stagingAvailCheckBox->isChecked());
  Setup::setAllowReturnToStagingEnabled(stagingTurnCheckBox->isChecked());
  Setup::setStagingPromptFromEnabled(promptFromTrackStagingCheckBox->isChecked());
  Setup::setStagingPromptToEnabled(promptToTrackStagingCheckBox->isChecked());
  Setup::setStagingTryNormalBuildEnabled(tryNormalStagingCheckBox->isSelected());

  // Car routing enabled?
  Setup::setCarRoutingEnabled(routerCheckBox->isChecked());
  Setup::setCarRoutingViaYardsEnabled(routerYardCheckBox->isChecked());
  Setup::setCarRoutingViaStagingEnabled(routerStagingCheckBox->isChecked());
  Setup::setOnlyActiveTrainsEnabled(!routerAllTrainsBox->isChecked());
  Setup::setCheckCarDestinationEnabled(routerRestrictBox->isChecked());
  // Options
  Setup::setGenerateCsvManifestEnabled(generateCvsManifestCheckBox->isChecked());
  Setup::setGenerateCsvSwitchListEnabled(generateCvsSwitchListCheckBox->isChecked());
  Setup::setValueEnabled(valueCheckBox->isChecked());
  Setup::setValueLabel(valueTextField->text());
  Setup::setRfidEnabled(rfidCheckBox->isChecked());
  Setup::setRfidLabel(rfidTextField->text());
  // Logging enabled?
  Setup::setEngineLoggerEnabled(engineLoggerCheckBox->isChecked());
  Setup::setCarLoggerEnabled(carLoggerCheckBox->isChecked());
  Setup::setTrainLoggerEnabled(trainLoggerCheckBox->isChecked());
  // VSD
  Setup::setVsdPhysicalLocationEnabled(enableVsdCheckBox->isChecked());
  // write the file
  ((Operations::OperationsSetupXml*)InstanceManager::getDefault("OperationsSetupXml"))->writeOperationsFile();
 }

 //@Override
 /*public*/ bool OptionPanel::isDirty()
 {
  return !( // build option
   Setup::isBuildAggressive() == buildAggressive->isChecked() &&
    Setup::getNumberPasses() == (int) numberPassesComboBox->currentText().toInt()
    // Local moves?
    &&
    Setup::isLocalInterchangeMovesEnabled() == localInterchangeCheckBox->isSelected() &&
    Setup::isLocalSpurMovesEnabled() == localSpurCheckBox->isSelected() &&
    Setup::isLocalYardMovesEnabled() == localYardCheckBox->isSelected()
    // Staging options
    &&
    Setup::isStagingTrainCheckEnabled() == trainIntoStagingCheckBox->isSelected() &&
    Setup::isStagingTrackImmediatelyAvail() == stagingAvailCheckBox->isSelected() &&
    Setup::isStagingAllowReturnEnabled() == stagingTurnCheckBox->isSelected() &&
    Setup::isStagingPromptFromEnabled() == promptFromTrackStagingCheckBox->isSelected() &&
    Setup::isStagingPromptToEnabled() == promptToTrackStagingCheckBox->isSelected() &&
    Setup::isStagingTryNormalBuildEnabled() == tryNormalStagingCheckBox->isSelected()
    // Car routing enabled?
    &&
    Setup::isCarRoutingEnabled() == routerCheckBox->isSelected() &&
    Setup::isCarRoutingViaYardsEnabled() == routerYardCheckBox->isSelected() &&
    Setup::isCarRoutingViaStagingEnabled() == routerStagingCheckBox->isSelected() &&
    Setup::isOnlyActiveTrainsEnabled() == !routerAllTrainsBox->isSelected() &&
    Setup::isCheckCarDestinationEnabled() == routerRestrictBox->isSelected()
    // Options
    &&
    Setup::isGenerateCsvManifestEnabled() == generateCvsManifestCheckBox->isSelected() &&
    Setup::isGenerateCsvSwitchListEnabled() == generateCvsSwitchListCheckBox->isSelected() &&
    Setup::isValueEnabled() == valueCheckBox->isSelected() &&
    Setup::getValueLabel() ==(valueTextField->text()) &&
    Setup::isRfidEnabled() == rfidCheckBox->isSelected() &&
    Setup::getRfidLabel() == (rfidTextField->text()) &&
    Setup::isSaveTrainManifestsEnabled() == saveTrainManifestCheckBox->isSelected()
    // Logging enabled?
    &&
    Setup::isEngineLoggerEnabled() == engineLoggerCheckBox->isSelected() &&
    Setup::isCarLoggerEnabled() == carLoggerCheckBox->isSelected() &&
    Setup::isTrainLoggerEnabled() == trainLoggerCheckBox->isSelected()
    // VSD
    &&
    Setup::isVsdPhysicalLocationEnabled() == enableVsdCheckBox->isSelected());
  }
 }
