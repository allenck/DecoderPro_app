#ifndef ENGINEEDITFRAME_H
#define ENGINEEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

class Logger;
class QSignalMapper;
class JTextField;
class QComboBox;
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
 class APPSLIBSHARED_EXPORT EngineEditFrame : public OperationsFrame
 {
   Q_OBJECT
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
  /*public*/ void initComponents();
  /*public*/ void dispose();
  /*public*/ void loadEngine(Engine* engine);

  signals:

  public slots:
  /*public*/ void buttonEditActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);


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
  QComboBox* roadComboBox; //=CarRoads.instance().getComboBox();
  QComboBox* modelComboBox; //=engineModels.getComboBox();
  QComboBox* typeComboBox; //=engineTypes.getComboBox();
  QComboBox* lengthComboBox; //=engineLengths.getComboBox();
  QComboBox* ownerComboBox; //=CarOwners.instance().getComboBox();
  QComboBox* locationBox; //=locationManager.getComboBox();
  QComboBox* trackLocationBox; //=new JComboBox<>();
  QComboBox* consistComboBox; //=manager.getConsistComboBox();
  QComboBox* rfidComboBox; //=new JComboBox<IdTag>();
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
