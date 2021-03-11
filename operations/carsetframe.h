#ifndef CARSETFRAME_H
#define CARSETFRAME_H
#include "rollingstocksetframe.h"
#include "appslib_global.h"
#include "jcombobox.h"

namespace Operations
{
 class CSResourceBundle : public ResourceBundle
 {
  public:
   CSResourceBundle();
   QString getMessage(QString key)
   {
    return map.value(key);
   }
  private:
   QMap<QString, QString> map = QMap<QString, QString>();
 };
 class CarAttributeEditFrame;
 class CarLoadEditFrame;
 class CarManager;
 class Car;
 class APPSLIBSHARED_EXPORT CarSetFrame : public RollingStockSetFrame
 {
  Q_OBJECT
 public:
  CarSetFrame(QWidget* parent = 0);
  /*public*/ void loadCar(Car* car);
  /*public*/ void initComponents();
  /*public*/ void setDestinationEnabled(bool enable);
  /*public*/ void dispose();
  /*public*/ QString getClassName();
  /*public*/ ResourceBundle* getRb();

 public slots:
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);


 private:
  CarManager* carManager;//= CarManager.instance();
  Car* _car;
  // Auto checkbox state
  /*private*/ static bool autoReturnWhenEmptyTrackCheckBoxSelected;//= false;
  CarLoadEditFrame* lef;//= null;
  /*private*/ static bool enableDestination;//= false;
  Logger* log;
  /*private*/ bool editActive;// = false;
  CarAttributeEditFrame* f;
  /*private*/ Car* getTestCar(Car* car);
  /*private*/ void enableDestinationFields(bool enabled);
  CSResourceBundle* rb = new CSResourceBundle();

 protected:
  // combo boxes
  /*protected*/ JComboBox* destReturnWhenEmptyBox;//= LocationManager.instance().getComboBox();
  /*protected*/ JComboBox* trackReturnWhenEmptyBox;//= new JComboBox<>();
  /*protected*/ JComboBox*loadReturnWhenEmptyBox;//= CarLoads.instance().getComboBox(null);
  JComboBox* loadComboBox;//= CarLoads.instance().getComboBox(null);
  JComboBox* kernelComboBox;//= carManager.getKernelComboBox();

  // buttons
  QPushButton* editLoadButton;//= new JButton(Bundle.getMessage("Edit"));
  QPushButton* editKernelButton;//= new JButton(Bundle.getMessage("Edit"));

  // check boxes
  /*protected*/ QCheckBox* ignoreRWECheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* autoReturnWhenEmptyTrackCheckBox;//= new JCheckBox(Bundle.getMessage("Auto"));
  /*protected*/ QCheckBox* ignoreLoadCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ QCheckBox* ignoreKernelCheckBox;//= new JCheckBox(Bundle.getMessage("Ignore"));
  /*protected*/ void updateLoadComboBox();
  /*protected*/ void updateKernelComboBox();
  /*protected*/ bool askKernelChange;// = true;
  /*protected*/ void updateTrainComboBox();
  /*protected*/ void updateFinalDestinationComboBoxes();
  /*protected*/ void updateFinalDestination();
  /*protected*/ void updateReturnWhenEmptyComboBoxes() ;
  /*protected*/ void updateReturnWhenEmpty();
  /*protected*/ void updateComboBoxes();
  /*protected*/ void enableComponents(bool enabled);
  /*protected*/ bool change(Car* car);
  /*protected*/ void updateComboBoxesLoadChange();
  /*protected*/ bool updateGroup(QList<RollingStock*> list);
  /*protected*/ bool save();
  friend class CarsSetFrame;
 };

}
#endif // CARSETFRAME_H
