#ifndef ROLLINGSTOCKEDITFRAME_H
#define ROLLINGSTOCKEDITFRAME_H

#include "operationsframe.h"
#include "rollingstock.h"
#include "instancemanager.h"
#include "locationmanager.h"
#include "jlabel.h"
#include "jbutton.h"
#include "jcheckbox.h"
#include "jtextfield.h"
#include "control.h"
#include "jtextarea.h"
#include "jcombobox.h"
#include "carroads.h"
#include "carowners.h"
#include "namedbeancombobox.h"
#include "rollingstockmanager.h"

namespace Operations
{
 class RollingStockEditFrame : public OperationsFrame, public PropertyChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
  public:
   RollingStockEditFrame(QString title, QObject* parent = nullptr);
   // major buttons
   /*public*/ JButton* editRoadButton = new JButton(tr("Edit"));
   /*public*/ JButton* clearRoadNumberButton = new JButton(tr("Clear"));
   /*public*/ JButton* editTypeButton = new JButton(tr("Edit"));
   /*public*/ JButton* editLengthButton = new JButton(tr("Edit"));
   /*public*/ JButton* editGroupButton = new JButton(tr("Edit"));
   /*public*/ JButton* editOwnerButton = new JButton(tr("Edit"));

   /*public*/ JButton* saveButton = new JButton(tr("Save"));
   /*public*/ JButton* deleteButton = new JButton(tr("Delete"));
   /*public*/ JButton* addButton = new JButton(tr("Add")); // TODO have button state item to add

   // check boxes
   /*public*/ JCheckBox *autoTrackCheckBox = new JCheckBox(tr("Auto"));

   // text field
   /*public*/ JTextField* roadNumberTextField = new JTextField(Control::max_len_string_road_number);
   /*public*/ JTextField* builtTextField = new JTextField(Control::max_len_string_built_name + 3);
   /*public*/ JTextField* blockingTextField = new JTextField(4);
   /*public*/ JTextField* weightTextField = new JTextField(Control::max_len_string_weight_name);
   /*public*/ JTextField* weightTonsTextField = new JTextField(Control::max_len_string_weight_name);
   /*public*/ JTextField* commentTextField = new JTextField(35);

   // text area
   /*public*/ JTextArea* valueTextArea = new JTextArea(3, 35);
//   QScrollArea* valueScroller = new JScrollPane(valueTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//           JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

   // combo boxes
   /*public*/ JComboBox* roadComboBox = ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getComboBox();
   /*public*/ JComboBox* typeComboBox = getTypeManager()->getComboBox();
   /*public*/ JComboBox* lengthComboBox = getLengthManager()->getComboBox();
   /*public*/ JComboBox* ownerComboBox = ((CarOwners*)InstanceManager::getDefault("CarOwners"))->getComboBox();
   /*public*/ JComboBox* groupComboBox;
   /*public*/ JComboBox* modelComboBox; // for engines
   /*public*/ JComboBox/*<Location>*/* locationBox = locationManager->getComboBox();
   /*public*/ JComboBox/*<Track>*/* trackLocationBox = new JComboBox();

   /*public*/ NamedBeanComboBox/*<IdTag>*/* rfidComboBox;

   // panels
   /*public*/ JPanel* pTypeOptions = new JPanel(); // options dependent on car or engine
   /*public*/ JPanel* pGroup = new JPanel(); // Kernel or Consist

   // panels for car edit
   /*public*/ JPanel* pBlocking = new JPanel();
   /*public*/ JPanel* pColor = new JPanel();
   /*public*/ JPanel* pLoad = new JPanel();
   /*public*/ JPanel* pWeightOz = new JPanel();

   // panels for engine edit
   /*public*/ JPanel* pModel = new JPanel();
   /*public*/ JPanel* pHp = new JPanel();
   /*public*/ void initComponents() override;
   /*public*/ void dispose() override;

  public slots:
   /*public*/ void comboBoxActionPerformed(QWidget* ae)override;
   /*public*/ void checkBoxActionPerformed(QWidget* ae) override;
   /*public*/ void buttonActionPerformed(QWidget* ae) override;
   /*public*/ void propertyChange(PropertyChangeEvent* e) override;

  private:
   static Logger* log;
   JLabel* textWeightTons = new JLabel(tr("Tons"));
   JLabel* textRfidSystemName = new JLabel();

  protected:
   /*protected*/ static /*final*/ bool IS_SAVE;// = true;
   /*protected*/ RollingStock* _rs;

   /*protected*/ LocationManager* locationManager = (LocationManager*)InstanceManager::getDefault("LocationManager");
   /*protected*/ RollingStockAttribute* getTypeManager();

   /*abstract*/ virtual /*protected*/ RollingStockAttribute* getLengthManager() = 0;

   /*abstract*/ virtual /*protected*/ void buttonEditActionPerformed(QWidget* ) = 0;

   /*abstract*/ virtual /*protected*/ ResourceBundle* getRb() =0;

   /*abstract*/ virtual /*protected*/ void save(bool isSave) =0;

   /*abstract*/ virtual /*protected*/ void _delete() =0;
   /*protected*/ void load(RollingStock* rs);
   /*protected*/ void updateTrackLocationBox();
   /*protected*/ bool check(RollingStock* rs);
   /*protected*/ /*<T extends RollingStock> */void save(RollingStockManager/*<T>*/* manager, bool isSave);
   /*protected*/ void setLocationAndTrack(RollingStock* rs);
   /*protected*/ void addEditButtonAction(JButton* b);
   /*protected*/ void addPropertyChangeListeners();
   /*protected*/ void removePropertyChangeListeners();


 };
}
#endif // ROLLINGSTOCKEDITFRAME_H
