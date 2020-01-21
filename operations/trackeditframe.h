#ifndef TRACKEDITFRAME_H
#define TRACKEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class QGridLayout;
class GridBagLayout;
class FlowLayout;
class QGroupBox;
class JTextArea;
class JTextField;
class QScrollArea;
class QLabel;
namespace Operations
{
 class Route;
 class TrainManager;
 class RouteManager;
 class Location;
 class Track;
 class APPSLIBSHARED_EXPORT TrackEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrackEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = Control.max_len_string_track_name;
  /*public*/ virtual void initComponents(Location* location, Track* track);
  QString     gbStyleSheet;
  /*public*/ QString getClassName();

 public slots:
  /*public*/ virtual void propertyChange(PropertyChangeEvent* e);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ virtual void dispose();

 private:
  Logger* log;
  TrainManager* trainManager;//= TrainManager::instance();
  RouteManager* routeManager;//= RouteManager::instance();

  Location* _location;//= NULL;
  Track* _track;//= NULL;
  QString _trackName;//= NULL; // track name for tools menu
  QString _type;//= "";
  QMenu* _toolMenu;//= NULL;

  QList<QCheckBox*> checkBoxes;//= new ArrayList<JCheckBox>();

  // panels
  QWidget* panelCheckBoxes;//= new JPanel();
  QGroupBox* checkBoxesGroupBox;//= new JScrollPane(panelCheckBoxes);
  QGroupBox* panelTrainDir;//= new JPanel();
  QGroupBox* pShipLoadOption;//= new JPanel();
  QGroupBox* pDestinationOption;//= new JPanel();
  QGroupBox* panelOrder;//= new JPanel();
  QScrollArea* paneCheckBoxesScroll;

  // labels
  QLabel* loadOption;//= new JLabel();
  QLabel* shipLoadOption;//= new JLabel();
  QLabel* roadOption;//= new JLabel(tr("AcceptsAllRoads"));
  QLabel* destinationOption;//= new JLabel();

  // major buttons
  QPushButton* clearButton;//= new JButton(tr("Clear"));
  QPushButton* setButton;//= new JButton(tr("Select"));
  QPushButton* saveTrackButton;//= new JButton(tr("SaveTrack"));
  QPushButton* deleteTrackButton;//= new JButton(tr("DeleteTrack"));
  QPushButton* addTrackButton;//= new JButton(tr("AddTrack"));

  QPushButton* deleteDropButton;//= new JButton(tr("Delete"));
  QPushButton* addDropButton;//= new JButton(tr("Add"));
  QPushButton* deletePickupButton;//= new JButton(tr("Delete"));
  QPushButton* addPickupButton;//= new JButton(tr("Add"));

  // check boxes
  QCheckBox* northCheckBox;//= new JCheckBox(tr("North"));
  QCheckBox* southCheckBox;//= new JCheckBox(tr("South"));
  QCheckBox* eastCheckBox;//= new JCheckBox(tr("East"));
  QCheckBox* westCheckBox;//= new JCheckBox(tr("West"));
  QCheckBox* autoDropCheckBox;//= new JCheckBox(tr("Auto"));
  QCheckBox* autoPickupCheckBox;//= new JCheckBox(tr("Auto"));

  // car pick up order controls
  QRadioButton* orderNormal;//= new JRadioButton(tr("Normal"));
  QRadioButton* orderFIFO;//= new JRadioButton(tr("DescriptiveFIFO"));
  QRadioButton* orderLIFO;//= new JRadioButton(tr("DescriptiveLIFO"));

  QRadioButton* anyDrops;//= new JRadioButton(tr("Any"));
  QRadioButton* trainDrop;//= new JRadioButton(tr("Trains"));
  QRadioButton* routeDrop;//= new JRadioButton(tr("Routes"));
  QRadioButton* excludeTrainDrop;//= new JRadioButton(tr("ExcludeTrains"));
  QRadioButton* excludeRouteDrop;//= new JRadioButton(tr("ExcludeRoutes"));

  QRadioButton* anyPickups;//= new JRadioButton(tr("Any"));
  QRadioButton* trainPickup;//= new JRadioButton(tr("Trains"));
  QRadioButton* routePickup;//= new JRadioButton(tr("Routes"));
  QRadioButton* excludeTrainPickup;//= new JRadioButton(tr("ExcludeTrains"));
  QRadioButton* excludeRoutePickup;//= new JRadioButton(tr("ExcludeRoutes"));

  QComboBox* comboBoxDropTrains;//= trainManager.getTrainComboBox();
  QComboBox* comboBoxDropRoutes;//= routeManager.getComboBox();
  QComboBox* comboBoxPickupTrains;//= trainManager.getTrainComboBox();
  QComboBox* comboBoxPickupRoutes;//= routeManager.getComboBox();

  // text field
  JTextField* trackNameTextField;//= new JTextField(Control.max_len_string_track_name);
  JTextField* trackLengthTextField;//= new JTextField(Control.max_len_string_track_length_name);

  // text area
  HtmlTextEdit* commentTextArea;//= new JTextArea(2, 60);
  //QScrollArea* commentScroller;//= new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//          JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // optional panel for spurs, staging, and interchanges
  QGroupBox* dropPanel;//= new JPanel();
  GridBagLayout* dropPanelLayout;
  QGroupBox* pickupPanel;//= new JPanel();
  FlowLayout* pickupPanelLayout;
  QWidget* panelOpt3;//= new JPanel(); // not currently used
  QGroupBox* panelOpt4;//= new JPanel();
  /*private*/ void updateCheckboxes();
  GridBagLayout* pcbLayout;

  int x;// = 0;
  int y;// = 0; // vertical position in panel
  /*private*/ void loadTypes(QStringList types);
  /*private*/ void enableCheckboxes(bool enable);
  /*private*/ void updateDropOptions();
  /*private*/ void updatePickupOptions();
  /*private*/ void updateTrainComboBox();
  /*private*/ void autoTrainComboBox(QComboBox* box);
  /*private*/ void updateRouteComboBox();
  /*private*/ void autoRouteComboBox(QComboBox* box);
  /*private*/ bool checkRoute(Route* route);
  /*private*/ void reportTrackExists(QString s);
  /*private*/ bool checkUserInputs(Track* track);
  /*private*/ bool checkName(QString s);
  /*private*/ bool checkLength(Track* track);
  /*private*/ bool checkService(Track* track);
  /*private*/ void selectCheckboxes(bool enable);
  /*private*/ void updateTrainDir();
  /*private*/ void updateRoadOption();
  /*private*/ void updateLoadOption();
  /*private*/ void updateCarOrder();

 protected:
  /*protected*/ virtual void enableButtons(bool enabled);
  /*protected*/ virtual void saveTrack(Track* track);
  /*protected*/ virtual void addNewTrack();
  /*protected*/ void updateDestinationOption();

friend class YardEditFrame;
friend class SpurEditFrame;
friend class InterchangeEditFrame;
friend class StagingEditFrame;
friend class TrackEditCommentsFrame;
friend class TrackEditCommentsAction;
friend class TrackRoadEditAction;
friend class TrackLoadEditAction;
friend class ChangeTrackFrame;
friend class IgnoreUsedTrackFrame;
friend class TrackDestinationEditAction;
friend class PoolTrackAction;
friend class PoolTrackFrame;
friend class AlternateTrackFrame;
 };
}
#endif // TRACKEDITFRAME_H
