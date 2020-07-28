#ifndef LOCATIONEDITFRAME_H
#define LOCATIONEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class QGroupBox;
class JTextArea;
class JTextField;
class QPushButton;
class QScrollArea;
namespace Operations
{
 class LocationsByCarTypeFrame;
 class YardEditFrame;
 class SpurEditFrame;
 class InterchangeEditFrame;
 class StagingEditFrame;

 class Location;
 class LocationManager;
 class StagingTableModel;
 class InterchangeTableModel;
 class YardTableModel;
 class SpurTableModel;
 class APPSLIBSHARED_EXPORT LocationEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ LocationEditFrame(Location* location, QWidget* parent= 0);
  /*public*/ static /*final*/ QString NAME;// = Bundle.getMessage("Name");
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = Control.max_len_string_location_name;
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void dispose();
  /*public*/ QString getClassName();


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);


 private:
  YardTableModel* yardModel;// = new YardTableModel();
  JTable* yardTable;// = new JTable(yardModel);
  //JScrollPane yardPane;
  SpurTableModel* spurModel;// = new SpurTableModel();
  JTable* spurTable;// = new JTable(spurModel);
  //JScrollPane spurPane;
  InterchangeTableModel* interchangeModel;// = new InterchangeTableModel();
  JTable* interchangeTable;// = new JTable(interchangeModel);
  //JScrollPane interchangePane;
  StagingTableModel* stagingModel;// = new StagingTableModel();
  JTable* stagingTable;// = new JTable(stagingModel);
  //JScrollPane stagingPane;

  LocationManager* locationManager;// = LocationManager.instance();

  Location* _location;// = null;
  QList<QCheckBox*> checkBoxes;// = new ArrayList<JCheckBox>();
  QWidget* panelCheckBoxes;// = new JPanel();
  QGroupBox* typePane;
  QGroupBox* directionPanel;// = new JPanel();

  // major buttons
  QPushButton* clearButton;// = new JButton(Bundle.getMessage("Clear"));
  QPushButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  QPushButton* autoSelectButton;// = new JButton(Bundle.getMessage("AutoSelect"));
  QPushButton* saveLocationButton;// = new JButton(Bundle.getMessage("SaveLocation"));
  QPushButton* deleteLocationButton;// = new JButton(Bundle.getMessage("DeleteLocation"));
  QPushButton* addLocationButton;// = new JButton(Bundle.getMessage("AddLocation"));
  QPushButton* addYardButton;// = new JButton(Bundle.getMessage("AddYard"));
  QPushButton* addSpurButton;// = new JButton(Bundle.getMessage("AddSpur"));
  QPushButton* addInterchangeButton;// = new JButton(Bundle.getMessage("AddInterchange"));
  QPushButton* addStagingButton;// = new JButton(Bundle.getMessage("AddStaging"));

  // check boxes
  QCheckBox* northCheckBox;// = new JCheckBox(Bundle.getMessage("North"));
  QCheckBox* southCheckBox;// = new JCheckBox(Bundle.getMessage("South"));
  QCheckBox* eastCheckBox;// = new JCheckBox(Bundle.getMessage("East"));
  QCheckBox* westCheckBox;// = new JCheckBox(Bundle.getMessage("West"));

  // radio buttons
  QRadioButton* stageRadioButton;// = new JRadioButton(Bundle.getMessage("StagingOnly"));
  QRadioButton* interchangeRadioButton;// = new JRadioButton(Bundle.getMessage("Interchange"));
  QRadioButton* yardRadioButton;// = new JRadioButton(Bundle.getMessage("Yards"));
  QRadioButton* spurRadioButton;// = new JRadioButton(Bundle.getMessage("Spurs"));

  // text field
  JTextField* locationNameTextField;// = new JTextField(Control.max_len_string_location_name);

  // text area
  JTextArea* commentTextArea;// = new JTextArea(2, 60);
  //JScrollPane commentScroller = new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//          JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // Reader selection dropdown.
  JComboBox* readerSelector;// = new JComboBox<String>();
  Logger* log;
  /*private*/ void updateCheckboxes();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void setTrainDirectionBoxes();
  /*private*/ void setVisibleLocations();
  /*private*/ void setEnabledLocations();
  /*private*/ void addCheckBoxTrainAction(QCheckBox* b);
  QSignalMapper* chkBoxMapper;
  YardEditFrame* yef;// = NULL;
  SpurEditFrame* sef;// = NULL;
  InterchangeEditFrame* ief;// = NULL;
  StagingEditFrame* stef;// = NULL;
  /*private*/ void saveNewLocation();
  /*private*/ void saveLocation();
  /*private*/ bool checkName(QString s);
  /*private*/ void setLocationOps();
  /*private*/ void reportLocationExists(QString s);
  /*private*/ void enableCheckboxes(bool enable);
  /*private*/ void selectCheckboxes(bool select);
  int x;// = 0;
  int y;// = 0; // vertical position in panel
  /*private*/ void autoSelectCheckboxes();
  /*private*/ void loadTypes(QStringList types);
  LocationsByCarTypeFrame* lctf;// = NULL;

 private slots:
  /*private*/ void checkBoxActionTrainPerformed(QWidget* ae);

friend class LocationsTableModel;
friend class ChangeTracksFrame;
friend class TrackCopyFrame;
 };
}
#endif // LOCATIONEDITFRAME_H
