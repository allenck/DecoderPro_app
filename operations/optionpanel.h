#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include "operationspreferencespanel.h"

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
  QCheckBox* routerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableCarRouting"));
  QCheckBox* routerYardCheckBox;//= new JCheckBox(Bundle.getMessage("EnableCarRoutingYard"));
  QCheckBox* routerStagingCheckBox;//= new JCheckBox(Bundle.getMessage("EnableCarRoutingStaging"));
  QCheckBox* routerAllTrainsBox;//= new JCheckBox(Bundle.getMessage("AllTrains"));
  QCheckBox* routerRestrictBox;//= new JCheckBox(Bundle.getMessage("EnableTrackDestinationRestrications"));

  QCheckBox* valueCheckBox;//= new JCheckBox(Bundle.getMessage("EnableValue"));
  QCheckBox* rfidCheckBox;//= new JCheckBox(Bundle.getMessage("EnableRfid"));
  QCheckBox* carLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableCarLogging"));
  QCheckBox* engineLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableEngineLogging"));
  QCheckBox* trainLoggerCheckBox;//= new JCheckBox(Bundle.getMessage("EnableTrainLogging"));

  QCheckBox* localInterchangeCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalInterchange"));
  QCheckBox* localSpurCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalSpur"));
  QCheckBox* localYardCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalYard"));

  QCheckBox* trainIntoStagingCheckBox;//= new JCheckBox(Bundle.getMessage("TrainIntoStaging"));
  QCheckBox* stagingAvailCheckBox;//= new JCheckBox(Bundle.getMessage("StagingAvailable"));
  QCheckBox* stagingTurnCheckBox;//= new JCheckBox(Bundle.getMessage("AllowCarsToReturn"));
  QCheckBox* promptFromTrackStagingCheckBox;//= new JCheckBox(Bundle.getMessage("PromptFromStaging"));
  QCheckBox* promptToTrackStagingCheckBox;//= new JCheckBox(Bundle.getMessage("PromptToStaging"));

  QCheckBox* generateCvsManifestCheckBox;//= new JCheckBox(Bundle.getMessage("GenerateCsvManifest"));
  QCheckBox* generateCvsSwitchListCheckBox;//= new JCheckBox(Bundle.getMessage("GenerateCsvSwitchList"));

  QCheckBox* enableVsdCheckBox;//= new JCheckBox(Bundle.getMessage("EnableVSD"));

  // text field
  JTextField* rfidTextField;//= new JTextField(10);
  JTextField* valueTextField;//= new JTextField(10);

  // combo boxes
  JComboBox* numberPassesComboBox;// = new JComboBox();
  /*private*/ void setBuildOption();
  Logger* log;
  /*private*/ void setRouterCheckBoxesEnabled();
 protected slots:
  /*protected*/ void checkBoxActionPerformed(QWidget* ae);

 };
}
#endif // OPTIONPANEL_H
