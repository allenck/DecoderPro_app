#ifndef TRAINEDITBUILDOPTIONSFRAME_H
#define TRAINEDITBUILDOPTIONSFRAME_H

#include "operationsframe.h"
class QGroupBox;
class JTextField;
class QLabel;
class QButtonGroup;
namespace Operations
{
 class TrainEditFrame;
 class Train;
 class TrainEditBuildOptionsFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ TrainEditBuildOptionsFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;//= "dispose"; // NOI18N
  /*public*/ void initComponents(TrainEditFrame* parent);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
 private:
  Logger* log;
  Train* _train;//= null;

  JPanel* panelOwnerNames;//= new JPanel();
  JPanel* panelBuilt;//= new JPanel();
  JPanel* panelTrainReq1;//= new JPanel();
  JPanel*  panelTrainReq2;//= new JPanel();

  QScrollArea* ownerPane;
  QScrollArea* builtPane;
  QScrollArea* trainReq1Pane;
  QScrollArea* trainReq2Pane;

  JPanel*  engine1Option;//= new JPanel();
  JPanel*  engine1DropOption;//= new JPanel();
  JPanel*  engine1caboose;//= new JPanel();

  JPanel*  engine2Option;//= new JPanel();
  JPanel*  engine2DropOption;//= new JPanel();
  JPanel*  engine2caboose;//= new JPanel();

  // labels
  QLabel* trainName;//= new JLabel();
  QLabel* trainDescription;//= new JLabel();
  QLabel* before;//= new JLabel(Bundle.getMessage("Before"));
  QLabel* after;//= new JLabel(Bundle.getMessage("After"));

  // major buttons
  JButton* addOwnerButton;//= new JButton(Bundle.getMessage("AddOwner"));
  JButton* deleteOwnerButton;//= new JButton(Bundle.getMessage("DeleteOwner"));
  JButton* saveTrainButton;//= new JButton(Bundle.getMessage("SaveTrain"));

  // radio buttons
  QRadioButton* ownerNameAll;//= new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* ownerNameInclude;//= new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* ownerNameExclude;//= new JRadioButton(Bundle.getMessage("Exclude"));

  QRadioButton* builtDateAll;//= new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* builtDateAfter;//= new JRadioButton(Bundle.getMessage("After"));
  QRadioButton* builtDateBefore;//= new JRadioButton(Bundle.getMessage("Before"));
  QRadioButton* builtDateRange;//= new JRadioButton(Bundle.getMessage("Range"));

  QButtonGroup* ownerGroup;//= new ButtonGroup();
  QButtonGroup* builtGroup;//= new ButtonGroup();

  // train requirements 1st set
  QRadioButton* none1;//= new JRadioButton(Bundle.getMessage("None"));
  QRadioButton* change1Engine;//= new JRadioButton(Bundle.getMessage("EngineChange"));
  QRadioButton* modify1Caboose;//= new JRadioButton(Bundle.getMessage("ChangeCaboose"));
  QRadioButton* helper1Service;//= new JRadioButton(Bundle.getMessage("HelperService"));
  QRadioButton* remove1Caboose;//= new JRadioButton(Bundle.getMessage("RemoveCaboose"));
  QRadioButton* keep1Caboose;//= new JRadioButton(Bundle.getMessage("KeepCaboose"));
  QRadioButton* change1Caboose;//= new JRadioButton(Bundle.getMessage("ChangeCaboose"));

  QButtonGroup* trainReq1Group;//= new ButtonGroup();
  QButtonGroup* cabooseOption1Group;//= new ButtonGroup();

  // train requirements 2nd set
  QRadioButton* none2;//= new JRadioButton(Bundle.getMessage("None"));
  QRadioButton* change2Engine;//= new JRadioButton(Bundle.getMessage("EngineChange"));
  QRadioButton* modify2Caboose;//= new JRadioButton(Bundle.getMessage("ChangeCaboose"));
  QRadioButton* helper2Service;//= new JRadioButton(Bundle.getMessage("HelperService"));
  QRadioButton* remove2Caboose;//= new JRadioButton(Bundle.getMessage("RemoveCaboose"));
  QRadioButton* keep2Caboose;//= new JRadioButton(Bundle.getMessage("KeepCaboose"));
  QRadioButton* change2Caboose;//= new JRadioButton(Bundle.getMessage("ChangeCaboose"));

  QButtonGroup* trainReq2Group;//= new ButtonGroup();
  QButtonGroup* cabooseOption2Group;//= new ButtonGroup();

  // check boxes
  QCheckBox* buildNormalCheckBox;//= new JCheckBox(Bundle.getMessage("NormalModeWhenBuilding"));
  QCheckBox* sendToTerminalCheckBox;//= new JCheckBox();
  QCheckBox* returnStagingCheckBox;//= new JCheckBox(Bundle.getMessage("AllowCarsToReturn"));
  QCheckBox* allowLocalMovesCheckBox;//= new JCheckBox(Bundle.getMessage("AllowLocalMoves"));
  QCheckBox* allowThroughCarsCheckBox;//= new JCheckBox(Bundle.getMessage("AllowThroughCars"));
  QCheckBox* serviceAllCarsCheckBox;//= new JCheckBox(Bundle.getMessage("ServiceAllCars"));
  QCheckBox* sendCustomStagngCheckBox;//= new JCheckBox(Bundle.getMessage("SendCustomToStaging"));
  QCheckBox* buildConsistCheckBox;//= new JCheckBox(Bundle.getMessage("BuildConsist"));

  // text field
  JTextField* builtAfterTextField;//= new JTextField(10);
  JTextField* builtBeforeTextField;//= new JTextField(10);

  // combo boxes
  JComboBox* ownerBox;//= CarOwners.instance().getComboBox();

  // train requirements 1st set
  JComboBox* routePickup1Box;//= new JComboBox<>();
  JComboBox* routeDrop1Box;//= new JComboBox<>();
  JComboBox* roadCaboose1Box;//= new JComboBox<>();
  JComboBox* roadEngine1Box;//= CarRoads.instance().getComboBox();
  JComboBox* modelEngine1Box;//= EngineModels.instance().getComboBox();
  JComboBox* numEngines1Box;//= new JComboBox<>();

  // train requirements 2nd set
  JComboBox* routePickup2Box;//= new JComboBox<>();
  JComboBox* routeDrop2Box;//= new JComboBox<>();
  JComboBox* roadCaboose2Box;//= new JComboBox<>();
  JComboBox* roadEngine2Box;//= CarRoads.instance().getComboBox();
  JComboBox* modelEngine2Box;//= EngineModels.instance().getComboBox();
  JComboBox* numEngines2Box;//= new JComboBox<>();
  /*private*/ void updateOwnerNames();
  /*private*/ void setBuiltRadioButton();
  /*private*/ void updateBuilt();
  /*private*/ void updateTrainRequires1Option();
  /*private*/ void updateTrainRequires2Option();
  /*private*/ void saveTrain();
  /*private*/ bool checkInput();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void updateModelComboBoxes();
  /*private*/ void updateOwnerComboBoxes();
  /*private*/ void updateCabooseRoadComboBox(JComboBox* box);
  /*private*/ void updateEngineRoadComboBox(JComboBox*box, QString engineModel);
  /*private*/ void createEngine1Panel();
  /*private*/ void createEngine2Panel();
  /*private*/ void createCaboose1Panel(bool withCombox);
  /*private*/ void createCaboose2Panel(bool withCombox);

 };
}
#endif // TRAINEDITBUILDOPTIONSFRAME_H
