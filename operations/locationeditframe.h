#ifndef LOCATIONEDITFRAME_H
#define LOCATIONEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"
#include "propertychangelistener.h"
#include "divisionmanager.h"
#include "instancemanager.h"
#include "jcolorchooser.h"
#include "jbutton.h"

class QGroupBox;
class JTextArea;
class JTextField;
class JButton;
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
 class APPSLIBSHARED_EXPORT LocationEditFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  /*public*/ LocationEditFrame(Location* location, QWidget* parent= 0);
  /*public*/ static /*final*/ QString NAME;// = Bundle.getMessage("Name");
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = Control.max_len_string_location_name;
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void dispose()override;
  /*public*/ QString getClassName()override;
   QObject* self() override {return (QObject*)this; }


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override;
  /*public*/ void buttonActionPerformed(QWidget* ae)override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae)override;
  /*public*/ void radioButtonActionPerformed(QWidget* ae)override;


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
  JPanel* panelCheckBoxes;// = new JPanel();
  JPanel* typePane;
  JPanel* directionPanel;// = new JPanel();

  // major buttons
  JButton* clearButton;// = new JButton(Bundle.getMessage("Clear"));
  JButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  JButton* autoSelectButton;// = new JButton(Bundle.getMessage("AutoSelect"));
  JButton* editDivisionButton = new JButton(tr("Edit"));
  JButton* saveLocationButton;// = new JButton(Bundle.getMessage("SaveLocation"));
  JButton* deleteLocationButton;// = new JButton(Bundle.getMessage("DeleteLocation"));
  JButton* addLocationButton;// = new JButton(Bundle.getMessage("AddLocation"));
  JButton* addYardButton;// = new JButton(Bundle.getMessage("AddYard"));
  JButton* addSpurButton;// = new JButton(Bundle.getMessage("AddSpur"));
  JButton* addInterchangeButton;// = new JButton(Bundle.getMessage("AddInterchange"));
  JButton* addStagingButton;// = new JButton(Bundle.getMessage("AddStaging"));

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
  JColorChooser* commentColorChooser = new JColorChooser();
  /*private*/ void setDivisionButtonText();

 private slots:
  /*private*/ void checkBoxActionTrainPerformed(QWidget* ae);

 protected:
  /*protected*/ JComboBox/*<Division>*/* divisionComboBox = ((DivisionManager*)InstanceManager::getDefault("Operations::DivisionManager"))->getComboBox();
  /*protected*/ void updateDivisionComboBox();


friend class LocationsTableModel;
friend class ChangeTracksFrame;
friend class TrackCopyFrame;
 };
}
#endif // LOCATIONEDITFRAME_H
