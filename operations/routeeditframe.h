#ifndef ROUTEEDITFRAME_H
#define ROUTEEDITFRAME_H
#include "operationsframe.h"
#include <QMenu>

class JComboBox;
class QGroupBox;
class JTextField;
class QButtonGroup;
class PropertyChangeEvent;
namespace Operations
{
 class Train;
 class Route;
 class RouteLocation;
 class RouteManager;
 class RouteManagerXml;
 class LocationManager;
 class RouteEditTableModel;
 class RouteEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  RouteEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString NAME;// = Bundle.getMessage("Name");
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void initComponents(Route* route, Train* train);
  /*public*/ void initComponents(Route* route);
  /*public*/ void dispose();
  /*public*/ QString getClassName();


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);

 private:
  RouteEditTableModel* routeModel;// = new RouteEditTableModel();
  JTable* routeTable;// = new JTable(routeModel);
  JPanel* routePane;

  RouteManager* routeManager;
  RouteManagerXml* managerXml;
  LocationManager* locationManager;// = LocationManager.instance();

  Route* _route;// = null;
  RouteLocation* _routeLocation;// = null;
  Train* _train;// = null;

  // major buttons
  JButton* addLocationButton;// =  new JButton(Bundle.getMessage("AddLocation"));
  JButton* saveRouteButton;// =  new JButton(Bundle.getMessage("SaveRoute"));
  JButton* deleteRouteButton;// =  new JButton(Bundle.getMessage("DeleteRoute"));
  JButton* addRouteButton;// =  new JButton(Bundle.getMessage("AddRoute"));

  // check boxes
  QCheckBox* checkBox;

  // radio buttons
  QRadioButton* addLocAtTop;// =  new JRadioButton(Bundle.getMessage("Top"));
  QRadioButton* addLocAtBottom;// =  new JRadioButton(Bundle.getMessage("Bottom"));
  QButtonGroup* group;// =  new ButtonGroup();

  QRadioButton* showWait;// =  new JRadioButton(Bundle.getMessage("Wait"));
  QRadioButton* showDepartTime;// =  new JRadioButton(Bundle.getMessage("DepartTime"));
  QButtonGroup* groupTime;// =  new ButtonGroup();

  // text field
  JTextField* routeNameTextField;// =  new JTextField(Control.max_len_string_route_name);
  JTextField* commentTextField;// =  new JTextField(35);

  // combo boxes
  JComboBox* locationBox;// =  LocationManager.instance().getComboBox();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void updateComboBoxes();
  Logger* log;
  /*private*/ void setTimeWaitRadioButtons();
  /*private*/ void addNewRouteLocation();
  /*private*/ void saveNewRoute();
  /*private*/ void saveRoute();
  /*private*/ bool checkName(QString s);
  /*private*/ void reportRouteExists(QString s);
  QMenu* toolMenu = new QMenu(tr("Tools"));
  /*private*/ void loadToolMenu();

 };
}
#endif // ROUTEEDITFRAME_H
