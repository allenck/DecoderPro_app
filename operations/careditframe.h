#ifndef CAREDITFRAME_H
#define CAREDITFRAME_H

#include <QObject>
#include "operationsframe.h"
#include "appslib_global.h"

class QGroupBox;
class QPushButton;
class QLabel;
class JComboBox;
class QCheckBox;
class JTextField;

namespace Operations
{
 class CarAttributeEditFrame;
 class CarManagerXml;
 class CarManager;
 class LocationManager;
 class Car;
 class CarLoadEditFrame;
 class APPSLIBSHARED_EXPORT CarEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  CarEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString ROAD;//= tr("Road");
  /*public*/ static /*final*/ QString TYPE;//= tr("Type");
  /*public*/ static /*final*/ QString COLOR;//= tr("Color");
  /*public*/ static /*final*/ QString LENGTH;//= tr("Length");
  /*public*/ static /*final*/ QString OWNER;//= tr("Owner");
  /*public*/ static /*final*/ QString KERNEL;//= tr("Kernel");
  /*public*/ void initComponents();
  /*public*/ void dispose();
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void loadCar(Car* car);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonEditActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);

 private:
  /**
   *
   */
  ///*private*/ static /*final*/ long serialVersionUID = 4399065932806496248L;
  CarManager* carManager;//= CarManager.instance();
  CarManagerXml* managerXml;//= CarManagerXml.instance();
  LocationManager* locationManager;//= LocationManager.instance();

  Car* _car;

  // labels
  QLabel* textWeightOz;//= new JLabel(Bundle.getMessage("WeightOz"));
  QLabel* textWeightTons;//= new JLabel(Bundle.getMessage("WeightTons"));

  // major buttons
  QPushButton* editRoadButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* clearRoadNumberButton;//= new JButton(Bundle.getMessage("Clear"));
  QPushButton* editTypeButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* editColorButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* editLengthButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* fillWeightButton;//= new JButton(Bundle.getMessage("Calculate"));
  QPushButton* editLoadButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* editKernelButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* editOwnerButton;//= new JButton(Bundle.getMessage("Edit"));

  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));
  QPushButton* deleteButton;//= new JButton(Bundle.getMessage("Delete"));
  QPushButton* addButton;//= new JButton(Bundle.getMessage("Add"));

  // check boxes
  QCheckBox* autoCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  QCheckBox* autoTrackCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  QCheckBox* passengerCheckBox;//= new JCheckBox(Bundle.getMessage("Passenger"));
  QCheckBox* cabooseCheckBox;//= new JCheckBox(Bundle.getMessage("Caboose"));
  QCheckBox* fredCheckBox;//= new JCheckBox(Bundle.getMessage("Fred"));
  QCheckBox* utilityCheckBox;//= new JCheckBox(Bundle.getMessage("Utility"));
  QCheckBox* hazardousCheckBox;//= new JCheckBox(Bundle.getMessage("Hazardous"));

  // text field
  JTextField* roadNumberTextField;//= new JTextField(Control.max_len_string_road_number);
  JTextField* blockingTextField;//= new JTextField(4);
  JTextField* builtTextField;//= new JTextField(Control.max_len_string_built_name + 3);
  JTextField* weightTextField;//= new JTextField(Control.max_len_string_weight_name);
  JTextField* weightTonsTextField;//= new JTextField(Control.max_len_string_weight_name);
  JTextField* commentTextField;//= new JTextField(35);
  JTextField* valueTextField;//= new JTextField(8);

  // combo boxes
  JComboBox* roadComboBox;//= CarRoads::instance().getComboBox();
  JComboBox* typeComboBox;//= CarTypes.instance().getComboBox();
  JComboBox* colorComboBox;//= CarColors.instance().getComboBox();
  JComboBox* lengthComboBox;//= CarLengths.instance().getComboBox();
  JComboBox* ownerComboBox;//= CarOwners.instance().getComboBox();
  JComboBox* locationBox;//= locationManager.getComboBox();
  JComboBox* trackLocationBox;//= new JComboBox<>();
  JComboBox* loadComboBox;//= CarLoads::instance().getComboBox(NULL);
  JComboBox* kernelComboBox;//= carManager.getKernelComboBox();
  JComboBox* rfidComboBox;//= new JComboBox<IdTag>();

  // panels
  QGroupBox* pBlocking;//= new JPanel();

  CarLoadEditFrame* lef;//= NULL;
  /*private*/ void addEditButtonAction(QPushButton* b);
  Logger* log;
  /*private*/ void updateTrackLocationBox();
  /*private*/ bool editActive;// = false;
  CarAttributeEditFrame* f;
  /*private*/ void removePropertyChangeListeners();
  QSignalMapper* editButtonMapper;
  /*private*/ void calculateWeight();
  /*private*/ void saveCar(bool isSave);
  /*private*/ void setLocation(Car* car);
  /*private*/ void writeFiles();
  /*private*/ bool checkCar(Car* c);

 };
}
#endif // CAREDITFRAME_H
