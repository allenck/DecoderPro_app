#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include "operationspreferencespanel.h"
#include "jcheckbox.h"

class JTextField;
namespace Operations
{
 class OptionPanel : public OperationsPreferencesPanel
 {
 public:
  OptionPanel(QWidget* parent = 0);
  /*public*/ QString getTabbedPreferencesTitle();
  /*public*/ QString getPreferencesTooltip();
  /*public*/ void savePreferences();
  /*public*/ bool isDirty();
  /*public*/ QString className() override {return "jmri.jmrit.operations.OptionPanel";}

 public slots:
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // labels
  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // radio buttons
  QRadioButton* buildNormal;//= new JRadioButton(Bundle.getMessage("Normal"));
  QRadioButton* buildAggressive;//= new JRadioButton(Bundle.getMessage("Aggressive"));

  // check boxes
  JCheckBox* routerCheckBox = new JCheckBox("Car Routing");
  JCheckBox* routerYardCheckBox = new JCheckBox(tr("Enable Car Routing via Yards"));
  JCheckBox* routerStagingCheckBox = new JCheckBox(tr("Enable Car Routing through Staging"));
  JCheckBox* routerAllTrainsBox  = new JCheckBox(tr("Use all Trains when Routing"));
  JCheckBox* routerRestrictBox= new JCheckBox(tr("Enable Track Destination Restrictions when Routing"));

  JCheckBox* valueCheckBox= new JCheckBox(tr("Enable Value Fields"));
  JCheckBox* rfidCheckBox;//= new JCheckBox(Bundle.getMessage("EnableRfid"));
  JCheckBox* carLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableCarLogging"));
  JCheckBox* engineLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableEngineLogging"));
  JCheckBox* trainLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableTrainLogging"));

  JCheckBox* localInterchangeCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalInterchange"));
  JCheckBox* localSpurCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalSpur"));
  JCheckBox* localYardCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalYard"));

  JCheckBox* trainIntoStagingCheckBox;//= new JCheckBox(Bundle.getMessage("TrainIntoStaging"));
  JCheckBox* stagingAvailCheckBox;//= new JCheckBox(Bundle.getMessage("StagingAvailable"));
  JCheckBox* stagingTurnCheckBox;//= new JCheckBox(Bundle.getMessage("AllowCarsToReturn"));
  JCheckBox* promptFromTrackStagingCheckBox;//= new JCheckBox(Bundle.getMessage("PromptFromStaging"));
  JCheckBox* promptToTrackStagingCheckBox;//= new JCheckBox(Bundle.getMessage("PromptToStaging"));
  JCheckBox* tryNormalStagingCheckBox = new JCheckBox(tr("Try Normal Mode if Build Failure from Staging"));

  JCheckBox* generateCvsManifestCheckBox;//= new JCheckBox(Bundle.getMessage("GenerateCsvManifest"));
  JCheckBox* generateCvsSwitchListCheckBox;//= new JCheckBox(Bundle.getMessage("GenerateCsvSwitchList"));

  JCheckBox* enableVsdCheckBox;//= new JCheckBox(Bundle.getMessage("EnableVSD"));
  JCheckBox* saveTrainManifestCheckBox = new JCheckBox(tr("Save Manifests"));

  // text field
  JTextField* rfidTextField;//= new JTextField(10);
  JTextField* valueTextField;//= new JTextField(10);

  // combo boxes
  JComboBox* numberPassesComboBox;// = new JComboBox();
  /*private*/ void setBuildOption();
  Logger* log;
  /*private*/ void setRouterCheckBoxesEnabled();
  /*private*/ void enableComponents();

 protected slots:
  /*protected*/ void checkBoxActionPerformed(QWidget* ae);

 };
}
#endif // OPTIONPANEL_H
