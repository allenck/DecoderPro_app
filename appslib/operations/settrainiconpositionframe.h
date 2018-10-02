#ifndef SETTRAINICONPOSITIONFRAME_H
#define SETTRAINICONPOSITIONFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"

class QLabel;
class TrainIcon;
namespace Operations
{
 class Location;
 class RouteManager;
 class APPSLIBSHARED_EXPORT SetTrainIconPositionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  SetTrainIconPositionFrame(QWidget* parent = 0);
  /*public*/ void updateTrainIconCoordinates(Location* l);
  /*public*/ void dispose();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void spinnerChangeEvent(QWidget* ae);

 private:
  RouteManager* routeManager;// = RouteManager.instance();

  // labels
  QLabel* textEastX;// = new JLabel("   X  ");
  QLabel* textEastY;// = new JLabel("   Y  ");
  QLabel* textWestX;// = new JLabel("   X  ");
  QLabel* textWestY;// = new JLabel("   Y  ");
  QLabel* textNorthX;// = new JLabel("   X  ");
  QLabel* textNorthY;// = new JLabel("   Y  ");
  QLabel* textSouthX;// = new JLabel("   X  ");
  QLabel* textSouthY;// = new JLabel("   Y  ");

  // text field
  // check boxes
  // major buttons
  QPushButton* placeButton;// = new JButton(Bundle.getMessage("PlaceTestIcon"));
  QPushButton* applyButton;// = new JButton(Bundle.getMessage("UpdateRoutes"));
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  // combo boxes
  QComboBox* locationBox;// = LocationManager.instance().getComboBox();

  //Spinners
  QSpinBox* spinTrainIconEastX;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconEastY;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconWestX;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconWestY;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconNorthX;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconNorthY;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconSouthX;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconSouthY;// = new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));

  // Four test train icons
  TrainIcon* _tIonEast;
  TrainIcon* _tIonWest;
  TrainIcon* _tIonNorth;
  TrainIcon* _tIonSouth;
  /*private*/ void spinnersEnable(bool enable);
  /*private*/ void removeIcons();
  /*private*/ void resetSpinners() ;
  /*private*/ void loadSpinners(Location* l);
  /*private*/ void saveSpinnerValues(Location* l);
  /*private*/ void placeTestIcons();
  Logger* log;
  /*private*/ void addIconListener(TrainIcon* tI);

 protected:
//  /*protected*/ void trainIconMoved(ComponentEvent* ae);
 };
}
#endif // SETTRAINICONPOSITIONFRAME_H
