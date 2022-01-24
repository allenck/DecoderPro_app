#ifndef SETTRAINICONROUTEFRAME_H
#define SETTRAINICONROUTEFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"

class TrainIcon;
class QLabel;
namespace Operations
{
 class RouteManager;
 class Route;
 class RouteLocation;
 class APPSLIBSHARED_EXPORT SetTrainIconRouteFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  SetTrainIconRouteFrame(Route* route, QWidget* parent = 0);
  ~SetTrainIconRouteFrame() {}
  SetTrainIconRouteFrame(const SetTrainIconRouteFrame&) : OperationsFrame() {}
  /*public*/ QString getClassName()override;
  QObject* self() override {return (QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override;
  /*public*/ void buttonActionPerformed(QWidget* ae)override;
  /*public*/ void spinnerChangeEvent(QWidget* ae)override;

 private:
  RouteManager* routeManager;//= RouteManager.instance();

  // labels
  QLabel* textX;//= new JLabel("   X  ");
  QLabel* textY;//= new JLabel("   Y  ");

  QLabel* routeLocationName;//= new JLabel();

  // text field
  // check boxes
  // major buttons
  JButton* previousButton;//= new JButton(Bundle.getMessage("Previous"));
  JButton* nextButton;//= new JButton(Bundle.getMessage("Next"));
  JButton* placeButton;//= new JButton(Bundle.getMessage("PlaceTestIcon"));
  JButton* applyButton;//= new JButton(Bundle.getMessage("Apply"));
  JButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // combo boxes
  // Spinners
  QSpinBox* spinTrainIconX;//= new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));
  QSpinBox* spinTrainIconY;//= new JSpinner(new SpinnerNumberModel(0, 0, 10000, 1));

  Route* _route;
  RouteLocation* _rl;
  int _routeIndex;//= 0;
  QList<RouteLocation*>* _routeList;

  // test train icon
  TrainIcon* _tIon;
  Logger* log;
  int value;// = JOptionPane.NO_OPTION;
  /*private*/ int FORWARD;// = 1;
  /*private*/ int BACK;// = -1;
  /*private*/ int NONE;// = 0;
  /*private*/ void updateRoute();
  /*private*/ void updateRouteLocation(int direction);
  /*private*/ void loadSpinners(RouteLocation* rl);
  /*private*/ void setTrainIconNameAndColor();
  /*private*/ void updateTrainIconCoordinates();
  /*private*/ void placeTestIcons();
  /*private*/ void addIconListener(TrainIcon* tI);

 };
}
//Q_DECLARE_METATYPE(Operations::SetTrainIconRouteFrame)

#endif // SETTRAINICONROUTEFRAME_H
