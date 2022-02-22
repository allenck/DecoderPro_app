#ifndef CAREDITFRAME_H
#define CAREDITFRAME_H

#include <QObject>
#include "rollingstockeditframe.h"
#include "appslib_global.h"
#include "propertychangelistener.h"
#include "resourcebundle.h"

class QGroupBox;
class JButton;
class QLabel;
class JComboBox;
class QCheckBox;
class JTextField;

namespace Operations
{
 class CarResourceBundle : public ResourceBundle
 {
  public:
   CarResourceBundle();
   QString getString(QString key)
   {
    return map.value(key);
   }
  private:
   QMap<QString, QString> map = QMap<QString, QString>();
 };
 class CarAttributeEditFrame;
 class CarManagerXml;
 class CarManager;
 class LocationManager;
 class Car;
 class CarLoadEditFrame;
 class APPSLIBSHARED_EXPORT CarEditFrame : public RollingStockEditFrame//, public  PropertyChangeListener
 {
  Q_OBJECT
 //Q_INTERFACES(PropertyChangeListener)
  public:
  CarEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString ROAD;//= tr("Road");
  /*public*/ static /*final*/ QString TYPE;//= tr("Type");
  /*public*/ static /*final*/ QString COLOR;//= tr("Color");
  /*public*/ static /*final*/ QString LENGTH;//= tr("Length");
  /*public*/ static /*final*/ QString OWNER;//= tr("Owner");
  /*public*/ static /*final*/ QString KERNEL;//= tr("Kernel");
  /*public*/ void initComponents() override;
  /*public*/ void dispose() override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae) override;
  /*public*/ void load(Car* car);
  /*public*/ QString getClassName() override;
  QObject* pself() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void buttonEditActionPerformed(QWidget* ae) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void comboBoxActionPerformed(QWidget* ae) override;

 private:
  /**
   *
   */
  ///*private*/ static /*final*/ long serialVersionUID = 4399065932806496248L;
  CarManager* carManager;//= CarManager.instance();
  CarManagerXml* managerXml;//= CarManagerXml.instance();
  LocationManager* locationManager;//= LocationManager.instance();
  CarAttributeEditFrame* carAttributeEditFrame = nullptr;
  Car* _car;

  // labels
  QLabel* textWeightOz;//= new JLabel(Bundle.getMessage("WeightOz"));
  QLabel* textWeightTons;//= new JLabel(Bundle.getMessage("WeightTons"));

  // major buttons
  JButton* editRoadButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* clearRoadNumberButton;//= new JButton(Bundle.getMessage("Clear"));
  JButton* editTypeButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* editColorButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* editLengthButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* fillWeightButton;//= new JButton(Bundle.getMessage("Calculate"));
  JButton* editLoadButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* editKernelButton;//= new JButton(Bundle.getMessage("Edit"));
  JButton* editOwnerButton;//= new JButton(Bundle.getMessage("Edit"));

  JButton* saveButton;//= new JButton(Bundle.getMessage("Save"));
  JButton* deleteButton;//= new JButton(Bundle.getMessage("Delete"));
  JButton* addButton;//= new JButton(Bundle.getMessage("Add"));

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
  JPanel* pBlocking;//= new JPanel();

  CarLoadEditFrame* carLoadEditFrame = nullptr;
  Logger* log;
  /*private*/ void updateTrackLocationBox();
  /*private*/ bool editActive;// = false;
  /*private*/ void removePropertyChangeListeners();
  /*private*/ void calculateWeight();
  /*private*/ void save(bool isSave)override;
  /*private*/ void setLocation(Car* car);
  /*private*/ void writeFiles();
  ResourceBundle* rb = new CarResourceBundle();
  protected:
  /*protected*/ void addPropertyChangeListeners();
  /*protected*/ ResourceBundle* getRb() override;
  /*protected*/ RollingStockAttribute* getTypeManager() override;
  /*protected*/ RollingStockAttribute* getLengthManager()override;
  /*protected*/ void _delete()override;
  /*private*/ bool check(RollingStock* c) override;

 };


}
#endif // CAREDITFRAME_H
