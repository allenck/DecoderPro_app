#ifndef LOCATIONSBYCARTYPEFRAME_H
#define LOCATIONSBYCARTYPEFRAME_H

#include "operationsframe.h"
#include <QList>
#include "appslib_global.h"
#include "jcombobox.h"

class QGroupBox;
class QCheckBox;
class QLabel;
namespace Operations
{
 class LocationManager;
 class Location;
 class APPSLIBSHARED_EXPORT LocationsByCarTypeFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  LocationsByCarTypeFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ void initComponents(Location* location);
  /*public*/ void initComponents(Location* location, QString carType) ;
  /*public*/ void initComponents(QString carType);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  LocationManager* manager;
  QString Empty; // = "            ";

  // checkboxes have the location id or track id as the checkbox name
  QList<QCheckBox*> locationCheckBoxList;// = new ArrayList<QCheckBox>();
  QList<QCheckBox*> trackCheckBoxList;// = new ArrayList<QCheckBox>();
  QWidget* locationCheckBoxes;// = new JPanel();

  // panels
  JPanel* pLocations;
  QScrollArea* locationPane;

  // major buttons
  JButton* clearButton;// = new JButton(Bundle.getMessage("Clear"));
  JButton* setButton;// = new JButton(Bundle.getMessage("Select"));
  JButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  // check boxes
  QCheckBox* copyCheckBox;// = new QCheckBox(Bundle.getMessage("Copy"));

  // text field
  QLabel* textCarType;// = new JLabel(Empty);

  // combo boxes
  JComboBox* typeComboBox;// = CarTypes.instance().getComboBox();

  // selected location
  Location* location;
  Logger* log;
  /*private*/ void updateLocations();
  /*private*/ void updateComboBox();
  /*private*/ void removePropertyChangeLocations();
  /*private*/ void save();
  /*private*/ void selectCheckboxes(bool select);


 };
}
#endif // LOCATIONSBYCARTYPEFRAME_H
