#ifndef ABSTRACTROUTEADDEDITFRAME_H
#define ABSTRACTROUTEADDEDITFRAME_H
#include "jmrijframe.h"
#include "routemanager.h"
#include "jtextfield.h"
#include "jcheckbox.h"
#include "namedbeancombobox.h"
#include "jspinner.h"
#include "jlabel.h"
#include <QScrollArea>
#include "jfilechooser.h"
#include "routeturnout.h"
#include "routesensor.h"
#include <QRadioButton>
#include "windowadapter.h"

class RouteTurnoutModel;
class RouteSensorModel;
class AbstractRouteAddEditFrame : public JmriJFrameX
{
 public:
  AbstractRouteAddEditFrame(QString name, bool saveSize, bool savePosition, QWidget *parent = nullptr);
  /*public*/ void initComponents() override;

  /*public*/ bool isShowAll();

 private:
  static /*final*/ QStringList COLUMN_NAMES;// = {Bundle.getMessage("ColumnSystemName"),
//          Bundle.getMessage("ColumnUserName"),
//          Bundle.getMessage("Include"),
//          Bundle.getMessage("ColumnLabelSetState")};
  /*private*/ static /*final*/ QString SET_TO_ACTIVE;// = Bundle.getMessage("Set") + " " + Bundle.getMessage("SensorStateActive");
  /*private*/ static /*final*/ QString SET_TO_INACTIVE;// = Bundle.getMessage("Set") + " " + Bundle.getMessage("SensorStateInactive");
  static /*final*/ QString SET_TO_TOGGLE;// = Bundle.getMessage("Set") + " " + Bundle.getMessage("Toggle");
  /*private*/ static /*final*/ QStringList sensorInputModes;// = new String[]{
//          Bundle.getMessage("OnCondition") + " " + Bundle.getMessage("SensorStateActive"),
//          Bundle.getMessage("OnCondition") + " " + Bundle.getMessage("SensorStateInactive"),
//          Bundle.getMessage("OnConditionChange"),
//          "Veto " + Bundle.getMessage("WhenCondition") + " " + Bundle.getMessage("SensorStateActive"),
//          "Veto " + Bundle.getMessage("WhenCondition") + " " + Bundle.getMessage("SensorStateInactive")
//  };
  /*private*/ static /*final*/ QVector<int> sensorInputModeValues;// = {Route::ONACTIVE, Route::ONINACTIVE, Route::ONCHANGE,
//          Route::VETOACTIVE, Route::VETOINACTIVE};

  // safe methods to set the above 4 static field values
  /*private*/ static /*final*/ QVector<int> turnoutInputModeValues;// = {Route::ONCLOSED, Route::ONTHROWN, Route::ONCHANGE,
//          Route::VETOCLOSED, Route::VETOTHROWN};

  /*private*/ static /*final*/ Logger* log;
  static int ROW_HEIGHT;
  // This group will get runtime updates to system-specific contents at
  // the start of buildModel() above.  This is done to prevent
  // invoking the TurnoutManager at class construction time,
  // when it hasn't been configured yet
  static QString SET_TO_CLOSED;// = tr("Set") + " "
//          + tr("TurnoutStateClosed");
  static QString SET_TO_THROWN;// = tr("Set") + " "
//          + tr("TurnoutStateThrown");
  /*private*/ static QStringList turnoutInputModes;// = new String[]{
//          tr("OnCondition") + " " + tr("TurnoutStateClosed"),
//          tr("OnCondition") + " " + tr("TurnoutStateThrown"),
//          tr("OnConditionChange"),
//          "Veto " + tr("WhenCondition") + " " + tr("TurnoutStateClosed"),
//          "Veto " + tr("WhenCondition") + " " + tr("TurnoutStateThrown")
//  };
  /*private*/ static QStringList lockTurnoutInputModes;// = new String[]{
//          tr("OnCondition") + " " + tr("TurnoutStateClosed"),
//          tr("OnCondition") + " " + tr("TurnoutStateThrown"),
//          tr("OnConditionChange")
//  };
  /*final*/ JTextField* _systemName = new JTextField(10);
  /*final*/ JTextField* _userName = new JTextField(22);
  /*final*/ JCheckBox* _autoSystemName = new JCheckBox(tr("LabelAutoSysName"));
  /*final*/ JTextField* soundFile = new JTextField(20);
  /*final*/ JTextField* scriptFile = new JTextField(20);
  /*final*/ JComboBox* sensor1mode = new JComboBox(sensorInputModes);
  /*final*/ JComboBox* sensor2mode = new JComboBox(sensorInputModes);
  /*final*/ JComboBox* sensor3mode = new JComboBox(sensorInputModes);
  /*final*/ JSpinner* timeDelay = new JSpinner();
  /*final*/ JComboBox* cTurnoutStateBox = new JComboBox(turnoutInputModes);
  /*final*/ JComboBox* cLockTurnoutStateBox = new JComboBox(lockTurnoutInputModes);
  /*final*/ JLabel* nameLabel = new JLabel(tr("LabelSystemName"));
  /*final*/ JLabel* userLabel = new JLabel(tr("LabelUserName"));
  /*final*/ JLabel* status1 = new JLabel();
  /*final*/ JLabel* status2 = new JLabel();

  /*private*/ QString getClassName() override;
  QList<RouteTurnout*> get_turnoutList();
  QList<RouteTurnout*> get_includedTurnoutList();
  QList<RouteSensor*> get_sensorList();
  QList<RouteSensor*> get_includedSensorList();


  /*protected*/ /*final*/ QString systemNameAuto = QString("jmri.jmrit.beantable.routetable.")+ metaObject()->className() + ".AutoSystemName";

  QList<RouteTurnout*> _turnoutList;      // array of all Turnouts
  QList<RouteSensor*> _sensorList;        // array of all Sensors
  RouteTurnoutModel* _routeTurnoutModel;
  //QScrollArea* _routeTurnoutScrollPane;
  RouteSensorModel* _routeSensorModel;
  //QScrollArea* _routeSensorScrollPane;
  NamedBeanComboBox/*<Sensor>*/*turnoutsAlignedSensor;
  NamedBeanComboBox/*<Sensor>*/*sensor1;
  NamedBeanComboBox/*<Sensor>*/*sensor2;
  NamedBeanComboBox/*<Sensor>*/*sensor3;
  NamedBeanComboBox/*<Turnout>*/*cTurnout;
  NamedBeanComboBox/*<Turnout>*/*cLockTurnout;
  Route* curRoute = nullptr;
  bool editMode = false;
  /*private*/ QRadioButton* allButton = nullptr;
  /*protected*/ bool routeDirty = false;  // true to fire reminder to save work
  /*private*/ bool showAll = true;   // false indicates show only included Turnouts
  /*private*/ JFileChooser* soundChooser = nullptr;
  /*private*/ JFileChooser* scriptChooser = nullptr;
  /*private*/ static /*synchronized*/ void setRowHeight(int newVal);
  /*private*/ JPanel* getNotesPanel();
  /*private*/ JPanel* getLockPanel();
  /*private*/ JPanel* getControlsPanel();
  /*private*/ JPanel* getAlignedSensorPanel();
  /*private*/ JPanel* getFileNamesPanel();
  /*private*/ JPanel* getTurnoutPanel();
  /*private*/ JPanel* getSensorPanel();
  /*private*/ void autoSystemName();
  /*private*/ int sensorModeFromBox(JComboBox* box);
  int sensorModeFromString(QString mode);
  void setSensorModeBox(int mode, JComboBox* box);
  /*private*/ int turnoutModeFromBox(JComboBox* box);
  void setTurnoutModeBox(int mode, JComboBox* box);
  /*private*/ void setSoundPressed();
  /*private*/ void setScriptPressed();
  /*private*/ void clearPage();
  /*private*/ void cancelIncludedOnly();
  /*private*/ Route* checkNamesOK();

 protected:
  /*protected*/ /*final*/ RouteManager* routeManager;
  /*protected*/ static void setClosedString(/*@Nonnull */QString newVal);
  /*protected*/ static void setThrownString(/*@Nonnull*/ QString newVal);
  /*protected*/ static void setTurnoutInputModes(/*@Nonnull*/ QStringList newArray);
  /*protected*/ static void setLockTurnoutModes(/*@Nonnull*/ QStringList newArray);
  /*protected*/ QList<RouteTurnout*> _includedTurnoutList;
  /*protected*/ QList<RouteSensor*> _includedSensorList;
  /*protected*/ UserPreferencesManager* pref;
  /*protected*/ /*abstract*/virtual JPanel* getButtonPanel() =0;
  /*protected*/ void setTurnoutInformation(Route* g);
  /*protected*/ void setSensorInformation(Route* g);
  /*protected*/ void setControlInformation(Route* g);
  /*protected*/ void finishUpdate();
  /*protected*/ void cancelEdit();
  /*protected*/ void updatePressed(bool newRoute);

  /*protected*/ void initializeIncludedList();
  /*protected*/ void showReminderMessage();

  /*protected*/ void closeFrame();

  friend class RouteEditFrame;
  friend class RouteTurnout;
  friend class RouteTurnoutModel;
  friend class RouteOutputModel;
  friend class ARAEFWindowListener;
  friend class RouteSensorModel;
  friend class RouteAddFrame;
};

class ARAEFWindowListener : public WindowAdapter
{
  Q_OBJECT
  AbstractRouteAddEditFrame* frame;
 public:
  ARAEFWindowListener(AbstractRouteAddEditFrame* frame) {this->frame = frame;}
  /*public*/ void windowClosing(QCloseEvent* e) {
      frame->closeFrame();
  }
};
#endif // ABSTRACTROUTEADDEDITFRAME_H
