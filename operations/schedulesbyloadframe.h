#ifndef SCHEDULESBYLOADFRAME_H
#define SCHEDULESBYLOADFRAME_H

#include "operationsframe.h"

namespace Operations
{
 class LocationManager;
 class SchedulesByLoadFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  SchedulesByLoadFrame(QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  Logger* log;
  // combo box
  JComboBox* typesComboBox;//= CarTypes.instance().getComboBox();
  JComboBox* loadsComboBox;//= new JComboBox<>();

  // panels
  JPanel* locationsPanel;

  // checkbox
  QCheckBox* allLoadsCheckBox;//= new JCheckBox(Bundle.getMessage("allLoads"));

  // managers'
  LocationManager* locationManager;//= LocationManager.instance();
  /*private*/ void updateLoadComboBox();
  /*private*/ void updateLocations();

 };
}
#endif // SCHEDULESBYLOADFRAME_H
