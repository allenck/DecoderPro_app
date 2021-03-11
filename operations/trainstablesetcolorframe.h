#ifndef TRAINSTABLESETCOLORFRAME_H
#define TRAINSTABLESETCOLORFRAME_H

#include "operationsframe.h"
class QGroupBox;
namespace Operations
{
 class Train;
 class TrainManager;
 class TrainsTableSetColorFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainsTableSetColorFrame(Train* train, QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
 private:
  TrainManager* trainManager;// = TrainManager.instance();

  // labels
  // text field
  // radio buttons
  QRadioButton* manualRadioButton;// = new JRadioButton(Bundle.getMessage("Manual"));
  QRadioButton* autoRadioButton;// = new JRadioButton(Bundle.getMessage("Auto"));

  // major buttons
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  // combo boxes
  JComboBox* trainBox;// = TrainManager.instance().getTrainComboBox();
  JComboBox* colorBox;// = TrainManager.instance().getRowColorComboBox();

  JComboBox* colorBuiltBox;// = TrainManager.instance().getRowColorComboBox();
  JComboBox* colorBuildFailedBox;// = TrainManager.instance().getRowColorComboBox();
  JComboBox* colorTrainEnRouteBox;// = TrainManager.instance().getRowColorComboBox();
  JComboBox* colorTerminatedBox;// = TrainManager::instance().getRowColorComboBox();

  // display panels based on which option is selected
  JPanel* pTrains;
  JPanel* pColor;

  JPanel* pColorBuilt;
  JPanel* pColorBuildFailed;
  JPanel* pColorTrainEnRoute;
  JPanel* pColorTerminated;
  /*private*/ void makePanelsVisible();
  Logger* log;

 };
}
#endif // TRAINSTABLESETCOLORFRAME_H
