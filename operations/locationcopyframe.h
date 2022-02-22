#ifndef LOCATIONCOPYFRAME_H
#define LOCATIONCOPYFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"

class JComboBox;
class JTextField;
namespace Operations
{
 class RollingStockManager;
 class Track;
 class LocationManager;
 class LocationCopyFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  LocationCopyFrame(QWidget* parent = 0);
  /*public*/ void dispose()override;
  /*public*/ QString getClassName()override;
  QObject* pself() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
 private:
  LocationManager* locationManager;//= LocationManager.instance();

  // text field
  JTextField* locationNameTextField;//= new javax.swing.JTextField(Control.max_len_string_location_name);

  // major buttons
  JButton* copyButton;//= new javax.swing.JButton(Bundle.getMessage("Copy"));
  JButton* saveButton;//= new javax.swing.JButton(Bundle.getMessage("Save"));

  // combo boxes
  JComboBox* locationBox;//= locationManager.getComboBox();

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
