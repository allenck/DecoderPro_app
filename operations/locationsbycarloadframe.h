#ifndef LOCATIONSBYCARLOADFRAME_H
#define LOCATIONSBYCARLOADFRAME_H

#include "operationsframe.h"

class PropertyChangeEvent;
namespace Operations
{
 class TrackLoadEditFrame;
 class LocationManager;
 class Location;
 class LocationsByCarLoadFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  LocationsByCarLoadFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location);
  /*public*/ void initComponents();
  /*public*/ void dispose();
  /*public*/ QString getClassName();


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  LocationManager* locationManager;

  // checkboxes track id as the checkbox name
  QList<QCheckBox*> trackCheckBoxList;//= new ArrayList<JCheckBox>();
  JPanel* locationCheckBoxes;//= new JPanel();

  // panels
  JPanel* pLocations;

  // major buttons
  JButton* clearButton;//= new JButton(Bundle.getMessage("Clear"));
  JButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  JButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // check boxes
  // JCheckBox copyCheckBox;//= new JCheckBox(Bundle.getMessage("Copy"));
  QCheckBox* loadAndTypeCheckBox;//= new JCheckBox(Bundle.getMessage("TypeAndLoad"));

  // radio buttons
  // text field
  // combo boxes
  JComboBox* typeComboBox;//= CarTypes.instance().getComboBox();
  JComboBox* loadComboBox;//= CarLoads.instance().getComboBox(null);

  // selected location
  Location* _location;
  Logger* log;
  TrackLoadEditFrame* tlef; // if there's an issue bring up the load edit window
  /*private*/ void updateLocations();
  /*private*/ void updateTypeComboBox();
  /*private*/ void updateLoadComboBox();
  /*private*/ void selectCheckboxes(bool select);
  /*private*/ void removePropertyChangeLocations();
  /*private*/ void save();

 };
}
#endif // LOCATIONSBYCARLOADFRAME_H
