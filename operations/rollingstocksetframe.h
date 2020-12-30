#ifndef ROLLINGSTOCKSETFRAME_H
#define ROLLINGSTOCKSETFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"
#include "jcombobox.h"

class JActionEvent;
class QGroupBox;
class QScrollArea;
class QCheckbox;
class QPushButton;
class QLabel;
namespace Operations
{
 class Train;
 class RouteLocation;
 class LocationManager;
 class TrainManager;
 class RollingStock;
 class RollingStockManager;
 class APPSLIBSHARED_EXPORT RollingStockSetFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ RollingStockSetFrame(QWidget* parent= 0);
  /*public*/ RollingStockSetFrame(QString title, QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ void load(RollingStock* rs);
 public slots:
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void dispose();
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  RollingStockManager* manager;
  /*private*/ static bool autoTrackCheckBoxSelected;//= false;
  /*private*/ static bool autoDestinationTrackCheckBoxSelected;//= false;
  /*private*/ static bool autoFinalDestTrackCheckBoxSelected;//= false;
  /*private*/ static bool autoTrainCheckBoxSelected;//= false;
  void common();
  Logger* log;

  RollingStock* _rs;
  // change(RollingStock rs) will load the route location and the route destination if possible
  RouteLocation* rl;
  RouteLocation* rd;
  /*private*/ bool changeLocation(RollingStock* rs);
  /*private*/ void loadTrain(RollingStock* rs);
  /*private*/ bool changeDestination(RollingStock* rs);

 protected:
  /*protected*/ LocationManager* locationManager;// = LocationManager.instance();
  /*protected*/ TrainManager* trainManager;// = TrainManager.instance();

  /*protected*/ bool _disableComboBoxUpdate;//= false;

  // labels
  QLabel* textRoad;// = new JLabel();
  QLabel* textType;// = new JLabel();

  // major buttons
  /*protected*/ QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));
  /*protected*/ QPushButton* ignoreAllButton;// = new JButton(Bundle.getMessage("IgnoreAll"));

  // combo boxes
  /*protected*/ JComboBox* locationBox;//= LocationManager.instance().getComboBox();
  /*protected*/ JComboBox* trackLocationBox;//= new JComboBox<>();
  /*protected*/ JComboBox* destinationBox;//= LocationManager.instance().getComboBox();
  /*protected*/ JComboBox* trackDestinationBox;//= new JComboBox<>();
  /*protected*/ JComboBox* finalDestinationBox;//= LocationManager.instance().getComboBox();
  /*protected*/ JComboBox* finalDestTrackBox;//= new JComboBox<>();
  /*protected*/ JComboBox* trainBox;//= TrainManager.instance().getTrainComboBox();

  // check boxes
  /*protected*/ QCheckBox* autoTrackCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  /*protected*/ QCheckBox* autoDestinationTrackCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  /*protected*/ QCheckBox* autoFinalDestTrackCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  /*protected*/ QCheckBox* autoTrainCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));

  /*protected*/ QCheckBox* locationUnknownCheckBox;//= new JCheckBox(Bundle.getMessage("LocationUnknown"));
  /*protected*/ QCheckBox* outOfServiceCheckBox;//= new JCheckBox(Bundle.getMessage("OutOfService"));

  /*protected*/ QCheckBox* ignoreStatusCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* ignoreLocationCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* ignoreDestinationCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* ignoreFinalDestinationCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* ignoreTrainCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));

  // optional panels
  /*protected*/ QGroupBox* pOptional;//= new JPanel();
  /*protected*/ QScrollArea* paneOptional;//= new JScrollPane(pOptional);
  /*protected*/ QGroupBox* pFinalDestination;//= new JPanel();
  /*protected*/ void updateComboBoxes();
  /*protected*/ void updateLocationComboBoxes();
  /*protected*/ void updateLocationTrackComboBox();
  /*protected*/ void updateTrainComboBox();
  /*protected*/ void packFrame();
  /*protected*/ void enableComponents(bool enabled);
  /*protected*/ void updateDestinationComboBoxes();
  /*protected*/ void updateDestinationTrackComboBox();
  /*protected*/ virtual bool save();
  /*protected*/ bool change(RollingStock* rs);
  /*protected*/ void checkTrain(RollingStock* rs);
  /*protected*/ void setRouteLocationAndDestination(RollingStock* rs, Train* train, RouteLocation* rl,
 RouteLocation* rd);
  /*protected*/ bool updateGroup(QList<RollingStock*> list);

 };
}
#endif // ROLLINGSTOCKSETFRAME_H
