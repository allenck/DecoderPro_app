#ifndef TRAINLOADOPTIONSFRAME_H
#define TRAINLOADOPTIONSFRAME_H

#include "operationsframe.h"
class QButtonGroup;
class QRadioButton;
class QLabel;
namespace Operations
{
 class TrainEditFrame;
 class Train;
 class TrainLoadOptionsFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainLoadOptionsFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE; // ="dispose"; // NOI18N
  /*public*/ void initComponents(TrainEditFrame* parent);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget*ae);
 private:
  Logger* log;
  /*private*/ static bool loadAndType;// =false;

  Train* _train;// = null;

  QWidget* pLoadControls;// =new JPanel();
  QWidget* panelLoads;// =new JPanel();
  QScrollArea* paneLoads;// =new JScrollPane(panelLoads);

  // labels
  QLabel* trainName;// =new JLabel();
  QLabel* trainDescription;// =new JLabel();

  // major buttons
  QPushButton* addLoadButton;// =new JButton(Bundle.getMessage("AddLoad"));
  QPushButton* deleteLoadButton;// =new JButton(Bundle.getMessage("DeleteLoad"));
  QPushButton* deleteAllLoadsButton;// =new JButton(Bundle.getMessage("DeleteAll"));
  QPushButton* saveTrainButton;// =new JButton(Bundle.getMessage("SaveTrain"));

  // radio buttons
  QRadioButton* loadNameAll;// =new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* loadNameInclude;// =new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* loadNameExclude;// =new JRadioButton(Bundle.getMessage("Exclude"));

  QButtonGroup* loadGroup;// =new ButtonGroup();

  // check boxes
  QCheckBox* loadAndTypeCheckBox;// =new JCheckBox(Bundle.getMessage("TypeAndLoad"));

  // text field
  // combo boxes
  QComboBox* comboBoxTypes;// =CarTypes.instance().getComboBox();
  QComboBox* comboBoxLoads;// =CarLoads.instance().getComboBox(null);
  /*private*/ void updateLoadNames();
  /*private*/ void deleteAllLoads();
  /*private*/ void saveTrain();
  /*private*/ void updateTypeComboBoxes();
  /*private*/ void updateLoadComboBoxes();

protected:
  /*protected*/ void updateButtons(bool enabled);

 };
}
#endif // TRAINLOADOPTIONSFRAME_H
