#ifndef ENGINEEDITFRAME_H
#define ENGINEEDITFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"
#include "propertychangelistener.h"
#include "rollingstockeditframe.h"
#include "instancemanager.h"
#include "resourcebundle.h"

class Logger;
class QSignalMapper;
class JTextField;
class JComboBox;
class QPushButton;
namespace Operations
{
 class EngineResourceBundle : public ResourceBundle
 {
  public:
   EngineResourceBundle();
   QString getString(QString key);
  private:
   QMap<QString, QString> map = QMap<QString, QString>();
 };

 class EngineAttributeEditFrame;
 class Engine;
 class EngineManager;
 class EngineManagerXml;
 class EngineModels;
 class EngineTypes;
 class EngineLengths;
 class CarManagerXml;
 class LocationManager;
 class APPSLIBSHARED_EXPORT EngineEditFrame : public RollingStockEditFrame//, public PropertyChangeListener
 {
   Q_OBJECT
   //Q_INTERFACES(PropertyChangeListener)
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
  /*public*/ void load(Engine* engine);
  /*public*/ QString getClassName() override;
   QObject* self() override {return (QObject*)this; }

  signals:

  public slots:
  /*public*/ void buttonEditActionPerformed(QWidget* ae)override;
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void comboBoxActionPerformed(QWidget* ae) override;

 private:
  EngineManager* engineManager = (EngineManager*)InstanceManager::getDefault("EngineManager");
  EngineManagerXml* managerXml = (EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml");
  EngineModels* engineModels = (EngineModels*)InstanceManager::getDefault("EngineModels");

  JButton* editModelButton = new JButton(tr("Edit"));

  JCheckBox* bUnitCheckBox = new JCheckBox(tr("B Unit"));

  JTextField* hpTextField = new JTextField(8);

  EngineAttributeEditFrame* engineAttributeEditFrame = nullptr;

  QSignalMapper* buttonEditMapper;
  static Logger* log;
  /*private*/ void save(bool isSave)override;
  ResourceBundle* rb = new EngineResourceBundle();

  protected:
  /*protected*/ ResourceBundle* getRb()override;
  /*protected*/ RollingStockAttribute* getTypeManager() override;
  /*protected*/ RollingStockAttribute* getLengthManager() override;
  /*protected*/ void addPropertyChangeListeners();
  /*protected*/ void removePropertyChangeListeners();
  /*protected*/ void _delete()override;
  /*protected*/ bool check(RollingStock* engine) override;

 };

}
#endif // ENGINEEDITFRAME_H
