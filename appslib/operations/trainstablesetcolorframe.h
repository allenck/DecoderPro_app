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
  QComboBox* trainBox;// = TrainManager.instance().getTrainComboBox();
  QComboBox* colorBox;// = TrainManager.instance().getRowColorComboBox();

  QComboBox* colorBuiltBox;// = TrainManager.instance().getRowColorComboBox();
  QComboBox* colorBuildFailedBox;// = TrainManager.instance().getRowColorComboBox();
  QComboBox* colorTrainEnRouteBox;// = TrainManager.instance().getRowColorComboBox();
  QComboBox* colorTerminatedBox;// = TrainManager::instance().getRowColorComboBox();

  // display panels based on which option is selected
  QGroupBox* pTrains;
  QGroupBox* pColor;

  QGroupBox* pColorBuilt;
  QGroupBox* pColorBuildFailed;
  QGroupBox* pColorTrainEnRoute;
  QGroupBox* pColorTerminated;
  /*private*/ void makePanelsVisible();
  Logger* log;

 };
}
#endif // TRAINSTABLESETCOLORFRAME_H
