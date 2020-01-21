#ifndef LOCATIONCOPYFRAME_H
#define LOCATIONCOPYFRAME_H

#include "operationsframe.h"

class JTextField;
namespace Operations
{
 class RollingStockManager;
 class Track;
 class LocationManager;
 class LocationCopyFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  LocationCopyFrame(QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
 private:
  LocationManager* locationManager;//= LocationManager.instance();

  // text field
  JTextField* locationNameTextField;//= new javax.swing.JTextField(Control.max_len_string_location_name);

  // major buttons
  QPushButton* copyButton;//= new javax.swing.JButton(Bundle.getMessage("Copy"));
  QPushButton* saveButton;//= new javax.swing.JButton(Bundle.getMessage("Save"));

  // combo boxes
  QComboBox* locationBox;//= locationManager.getComboBox();

  // checkboxes
  QCheckBox* moveRollingStockCheckBox;//= new JCheckBox(Bundle.getMessage("MoveRollingStock"));
  QCheckBox* deleteTrackCheckBox;//= new JCheckBox(Bundle.getMessage("DeleteCopiedTrack"));
  static bool _moveRollingStock;// = false;
  static bool deleteTrack;// = false;
  Logger* log;
  /*private*/ void moveRollingStock(Track* fromTrack, Track* toTrack, RollingStockManager* manager);

 protected:
  /*protected*/ void updateComboBoxes();
  /*protected*/ bool checkName();
  /*protected*/ void moveRollingStock(Track* fromTrack, Track* toTrack) ;


 protected slots:
  /*protected*/ void buttonActionPerformed(QWidget* ae);
  /*protected*/ void checkBoxActionPerformed(QWidget* ae);

 };
}
#endif // LOCATIONCOPYFRAME_H
