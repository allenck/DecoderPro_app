#ifndef ENGINEEDITFRAME_H
#define ENGINEEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"
#include "propertychangelistener.h"
class Logger;
class QSignalMapper;
class JTextField;
class JComboBox;
class QPushButton;
namespace Operations
{
 class EngineAttributeEditFrame;
 class Engine;
 class EngineManager;
 class EngineManagerXml;
 class EngineModels;
 class EngineTypes;
 class EngineLengths;
 class CarManagerXml;
 class LocationManager;
 class APPSLIBSHARED_EXPORT EngineEditFrame : public OperationsFrame, public PropertyChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
  public:
   explicit EngineEditFrame(QWidget *parent = 0);
  //private static final long serialVersionUID = 7527604846983933144L;
  /*public*/ static /*final*/ QString ROAD; //=Bundle.getMessage("Road");
  /*public*/ static /*final*/ QString MODEL; //=Bundle.getMessage("Model");
  /*public*/ static /*final*/ QString TYPE; //=Bundle.getMessage("Type");
  /*public*/ static /*final*/ QString COLOR; //=Bundle.getMessage("Color");
  /*public*/ static /*final*/ QString LENGTH; //=Bundle.getMessage("Length");
  /*public*/ static /*final*/ QString OWNER; //=Bundle.getMessage("Owner");
  /*public*/ static /*final*/ QString CONSIST; //=Bundle.getMessage("Consist");
  /*public*/ void initComponents() override;
  /*public*/ void dispose() override;
  /*public*/ void loadEngine(Engine* engine);
  /*public*/ QString getClassName() override;
   QObject* self() override {return (QObject*)this; }

  signals:

  public slots:
  /*public*/ void buttonEditActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void comboBoxActionPerformed(QWidget* ae) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae) override;


 private:
  EngineManager* manager;// = EngineManager.instance();
  EngineManagerXml* managerXml;// = EngineManagerXml.instance();
  EngineModels* engineModels;// = EngineModels.instance();
  EngineTypes* engineTypes;// = EngineTypes.instance();
  EngineLengths* engineLengths;// = EngineLengths.instance();
  CarManagerXml* carManagerXml;// = CarManagerXml.instance();
  LocationManager* locationManager;// = LocationManager.instance();

  Engine* _engine;

  // major buttons
  QPushButton* editRoadButton; //=new JButton(Bundle.getMessage("Edit"));
  QPushButton* clearRoadNumberButton; //=new JButton(Bundle.getMessage("Clear"));
  QPushButton* editModelButton; //=new JButton(Bundle.getMessage("Edit"));
  QPushButton* editTypeButton; //=new JButton(Bundle.getMessage("Edit"));
  QPushButton* editLengthButton; //=new JButton(Bundle.getMessage("Edit"));
  QPushButton* fillWeightButton; //=new JButton();
  QPushButton* editConsistButton; //=new JButton(Bundle.getMessage("Edit"));
  QPushButton* editOwnerButton; //=new JButton(Bundle.getMessage("Edit"));

  QPushButton* saveButton; //=new JButton(Bundle.getMessage("Save"));
  QPushButton* deleteButton; //=new JButton(Bundle.getMessage("Delete"));
  QPushButton* addButton; //=new JButton(Bundle.getMessage("Add"));

  // check boxes
  QCheckBox* bUnitCheckBox;// = new JCheckBox(Bundle.getMessage("BUnit"));

  // text field
  JTextField* roadNumberTextField; //=new JTextField(Control.max_len_string_road_number);
  JTextField* builtTextField; //=new JTextField(Control.max_len_string_built_name + 3);
  JTextField* hpTextField; //=new JTextField(8);
  JTextField* weightTextField; //=new JTextField(Control.max_len_string_weight_name);
  JTextField* commentTextField; //=new JTextField(35);
  JTextField* valueTextField; //=new JTextField(8);

  // combo boxes
  JComboBox* roadComboBox; //=CarRoads.instance().getComboBox();
  JComboBox* modelComboBox; //=engineModels.getComboBox();
  JComboBox* typeComboBox; //=engineTypes.getComboBox();
  JComboBox* lengthComboBox; //=engineLengths.getComboBox();
  JComboBox* ownerComboBox; //=CarOwners.instance().getComboBox();
  JComboBox* locationBox; //=locationManager.getComboBox();
  JComboBox* trackLocationBox; //=new JComboBox<>();
  JComboBox* consistComboBox; //=manager.getConsistComboBox();
  JComboBox* rfidComboBox; //=new JComboBox<IdTag>();
  /*private*/ bool editActive;// = false;
  EngineAttributeEditFrame* f;
  /*private*/ void addEditButtonAction(QPushButton* b);
  QSignalMapper* buttonEditMapper;
  /*private*/ void removePropertyChangeListeners();
  Logger* log;
  /*private*/ void addEngine();
  /*private*/ bool checkRoadNumber(QString roadNum);
  /*private*/ void saveEngine();

 };
}
#endif // ENGINEEDITFRAME_H
