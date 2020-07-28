#ifndef TRAINROADOPTIONSFRAME_H
#define TRAINROADOPTIONSFRAME_H

#include "operationsframe.h"
class QGroupBox;
class QLabel;
class QButtonGroup;
namespace Operations
{
 class TrainEditFrame;
 class Train;
 class TrainRoadOptionsFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainRoadOptionsFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;// ="dispose"; // NOI18N
  /*public*/ void initComponents(TrainEditFrame* parent);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
private:
  Logger* log;
  Train* _train;// =null;

  QWidget* pRoadControls;// =new QWidget();
  QGroupBox* panelRoads;// =new QWidget();
  QScrollArea* paneRoads;// =new JScrollPane(panelRoads);

  // labels
  QLabel* trainName;// =new JLabel();
  QLabel* trainDescription;// =new JLabel();

  // major buttons
  QPushButton* addRoadButton;// =new JButton(Bundle.getMessage("AddRoad"));
  QPushButton* deleteRoadButton;// =new JButton(Bundle.getMessage("DeleteRoad"));
  QPushButton* deleteAllRoadsButton;// =new JButton(Bundle.getMessage("DeleteAll"));
  QPushButton* saveTrainButton;// =new JButton(Bundle.getMessage("SaveTrain"));

  // radio buttons
  QRadioButton* roadNameAll;// =new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* roadNameInclude;// =new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* roadNameExclude;// =new JRadioButton(Bundle.getMessage("Exclude"));

  QButtonGroup* roadGroup;// =new ButtonGroup();

  // check boxes
  // text field
  // combo boxes
  JComboBox* comboBoxRoads;// =CarRoads.instance().getComboBox();
  /*private*/ static /*final*/ int NUMBER_ROADS_PER_LINE;// = 6;
  /*private*/ void updateRoadNames();
  /*private*/ void deleteAllRoads();
  /*private*/ void saveTrain();
  /*private*/ void updateRoadComboBoxes();

 protected:
  /*protected*/ void updateButtons(bool enabled);

 };
}
#endif // TRAINROADOPTIONSFRAME_H
