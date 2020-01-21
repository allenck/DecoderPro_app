#ifndef TRAINEDITFRAME_H
#define TRAINEDITFRAME_H

#include "operationsframe.h"

class HtmlTextEdit;
class propertyChange;
class JTextField;
class QButtonGroup;
class QLabel;
class QCheckBox;
namespace Operations
{
 class RouteEditFrame;
 class Train;
 class TrainManager;
 class RouteManager;
 class TrainEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ TrainEditFrame(Train* train, QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void setChildFrame(JmriJFrame* frame);
  /*public*/ void dispose();
  /*public*/ QString getClassName();


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void locationCheckBoxActionPerformed(QWidget* ae);
  /*public*/ void typeCheckBoxActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);

 private:
  TrainManager* trainManager;
  RouteManager* routeManager;

  Train* _train;//= null;
  QList<QCheckBox*> typeCarCheckBoxes;//= new ArrayList<JCheckBox>();
  QList<QCheckBox*> typeEngineCheckBoxes;//= new ArrayList<JCheckBox>();
  QList<QCheckBox*> locationCheckBoxes;//= new ArrayList<JCheckBox>();
  QWidget* typeCarPanelCheckBoxes;//= new JPanel();
  QWidget* typeEnginePanelCheckBoxes;//= new JPanel();
  QWidget* roadAndLoadStatusPanel;//= new JPanel();
  QWidget* locationPanelCheckBoxes;//= new JPanel();
  QScrollArea* typeCarPane;
  QScrollArea* typeEnginePane;
  QScrollArea* locationsPane;

  // labels
  QLabel* textRouteStatus;//= new JLabel();
  QLabel* loadOption;//= new JLabel();
  QLabel* roadOption;//= new JLabel();
  QLabel* textModel;//= new JLabel(Bundle.getMessage("Model"));
  QLabel* textRoad2;//= new JLabel(Bundle.getMessage("Road"));
  QLabel* textRoad3;//= new JLabel(Bundle.getMessage("Road"));
  QLabel* textEngine;//= new JLabel(Bundle.getMessage("Engines"));

  // major buttons
  QPushButton* editButton;//= new JButton(Bundle.getMessage("Edit"));	// edit route
  QPushButton* clearButton;//= new JButton(Bundle.getMessage("Clear"));
  QPushButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  QPushButton* resetButton;//= new JButton(Bundle.getMessage("ResetTrain"));
  QPushButton* saveTrainButton;//= new JButton(Bundle.getMessage("SaveTrain"));
  QPushButton* deleteTrainButton;//= new JButton(Bundle.getMessage("DeleteTrain"));
  QPushButton* addTrainButton;//= new JButton(Bundle.getMessage("AddTrain"));

  // radio buttons
  QRadioButton* noneRadioButton;//= new JRadioButton(Bundle.getMessage("None"));
  QRadioButton* cabooseRadioButton;//= new JRadioButton(Bundle.getMessage("Caboose"));
  QRadioButton* fredRadioButton;//= new JRadioButton(Bundle.getMessage("FRED"));
  QButtonGroup* group;//= new ButtonGroup();

  // text field
  JTextField* trainNameTextField;//= new JTextField(Control.max_len_string_train_name - 5); // make slightly smaller
  JTextField* trainDescriptionTextField;//= new JTextField(30);

  // text area
  HtmlTextEdit* commentTextArea;//= new JTextArea(2, 70);
//  QScrollArea* commentScroller;//= new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//          JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // for padding out panel
  QLabel* space1;//= new JLabel("       ");
  QLabel* space2;//= new JLabel("       "); // between hour and minute
  QLabel* space3;//= new JLabel("       ");
  QLabel* space4;//= new JLabel("       ");
  QLabel* space5;//= new JLabel("       ");

  // combo boxes
  QComboBox* hourBox;//= new JComboBox<>();
  QComboBox* minuteBox;//= new JComboBox<>();
  QComboBox* routeBox;//= RouteManager.instance().getComboBox();
  QComboBox* roadCabooseBox;//= new JComboBox<>();
  QComboBox* roadEngineBox;//= new JComboBox<>();
  QComboBox* modelEngineBox;//= EngineModels.instance().getComboBox();
  QComboBox* numEnginesBox;//= new JComboBox<>();
  /*private*/ void packFrame();
  QList<JmriJFrame*> children;// = new ArrayList<Frame>();
  /*private*/ void updateDepartureTime();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void selectCheckboxes(bool enable);
  /*private*/ void updateLocationCheckboxes();
  RouteEditFrame* ref;
  /*private*/ void enableCheckboxes(bool enable);
  /*private*/ void addLocationCheckBoxAction(QCheckBox* b);
  QSignalMapper* boxMapper;
  QSignalMapper* typeCheckBoxMapper;
  Logger*log;
  /*private*/ void updateRoadAndLoadStatus();
  /*private*/ void updateRouteComboBox();
  /*private*/ void updateCarTypeCheckboxes();
  /*private*/ void loadCarTypes();
  /*private*/ void updateEngineTypeCheckboxes();
  /*private*/ void loadEngineTypes();
  /*private*/ void updateRoadComboBoxes();
  /*private*/ void updateCabooseRoadComboBox();
  /*private*/ void updateEngineRoadComboBox();
  /*private*/ void addTypeCheckBoxAction(QCheckBox* b);
  /*private*/ void saveNewTrain();
  /*private*/ void saveTrain();
  /*private*/ bool checkName(QString s);
  /*private*/ bool checkModel();
  /*private*/ bool checkEngineRoad();
  /*private*/ bool checkRoute();
  /*private*/ void reportTrainExists(QString s);
  /*private*/ void editAddRoute();
 friend class PrintTrainAction;
 friend class PrintTrainManifestAction;
 friend class PrintTrainBuildReportAction;
 friend class TrainEditBuildOptionsFrame;
 friend class TrainLoadOptionsFrame;
 friend class TrainRoadOptionsFrame;
 friend class TrainManifestOptionFrame;
 friend class TrainScriptFrame;
 };
}
#endif // TRAINEDITFRAME_H
