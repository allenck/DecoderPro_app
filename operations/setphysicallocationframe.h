#ifndef OPERATIONS_SETPHYSICALLOCATIONFRAME_H
#define OPERATIONS_SETPHYSICALLOCATIONFRAME_H

#include "operationsframe.h"
#include "instancemanager.h"
#include "locationmanager.h"
#include "jbutton.h"
#include  "jcombobox.h"
#include "location.h"

class PhysicalLocationPanel;

namespace Operations {

 class SetPhysicalLocationFrame : public OperationsFrame
 {
  public:
   SetPhysicalLocationFrame(Location* l, QWidget* parent = nullptr);
   ~SetPhysicalLocationFrame() {}
   SetPhysicalLocationFrame(const SetPhysicalLocationFrame&) : OperationsFrame() {}

  public slots:
   /*public*/  void saveButtonActionPerformed(QWidget * ae);
   /*public*/  void closeButtonActionPerformed(QWidget * /*ae*/);
   /*public*/  void comboBoxActionPerformed(QWidget*ae) override;
   /*public*/  void spinnerChangeEvent(QWidget* ae)override;
   /*public*/  void dispose()override;
   /*public*/ QString getClassName() override {return "jmri.jmrit.operations.locations.tools.SetPhysicalLocationFrame";}
  private:
   static Logger* log;
   LocationManager* locationManager = (LocationManager*)InstanceManager::getDefault("Operations::LocationManager");

   Location* _location;

   // labels
   // text field
   // check boxes
   // major buttons
   JButton* saveButton = new JButton(tr("Save"));
   JButton* closeButton = new JButton(tr("Close"));

   // combo boxes
   JComboBox/*<Location>*/* locationBox = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getComboBox();

   // Spinners
   PhysicalLocationPanel* physicalLocation;
   /*private*/ void resetSpinners();
   /*private*/ void loadSpinners(Location* l);
   /*private*/ void saveSpinnerValues(Location* l);

 };

} // namespace Operations
//Q_DECLARE_METATYPE(Operations::SetPhysicalLocationFrame)
#endif // OPERATIONS_SETPHYSICALLOCATIONFRAME_H
