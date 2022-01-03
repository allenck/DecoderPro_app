#ifndef TRACKCOPYFRAME_H
#define TRACKCOPYFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"
#include "jcheckbox.h"
#include "control.h"
#include "jtextfield.h"
#include "jbutton.h"

class JTextField;
namespace Operations
{
 class RollingStockManager;
 class Track;
 class LocationEditFrame;
 class Location;
 class TrackCopyFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  TrackCopyFrame(LocationEditFrame* lef, QWidget *parent = nullptr);
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  // text field
  JTextField* trackNameTextField =new JTextField(Control::max_len_string_track_name);

  // major buttons
  JButton* copyButton = new JButton(tr("Copy"));
  JButton* saveButton = new JButton(tr("Save"));

  // combo boxes
  JComboBox* locationBox;// =LocationManager.instance().getComboBox();
  JComboBox* trackBox;// =new JComboBox<>();

  // checkboxes
  JCheckBox* sameNameCheckBox =new JCheckBox(tr("Same name"));
  JCheckBox* moveRollingStockCheckBox =new JCheckBox(tr("Move Rolling Stock to New Track"));
  JCheckBox* deleteTrackCheckBox =new JCheckBox(tr("Delete Copied Track"));

  Location* _location=nullptr;	// Copy the track to this location
  Location* _destination = nullptr;  // copy the track to this location
  static bool sameName;// =false;
  static bool _moveRollingStock;// =false;
  static bool deleteTrack;// =false;
  Logger * log;
  /*private*/ void moveRollingStock(Track* fromTrack, Track* toTrack, RollingStockManager* manager);

 protected slots:
  /*protected*/ void comboBoxActionPerformed(QWidget* ae) override;
  /*protected*/ void buttonActionPerformed(QWidget* ae)override;
  /*protected*/ void checkBoxActionPerformed(QWidget* ae)override;

 protected:
  /*protected*/ void updateTrackComboBox();
  /*protected*/ void updateTrackName();
  /*protected*/ void updateComboBoxes();
  /*protected*/ bool checkName();
  /*protected*/ void moveRollingStock(Track* fromTrack, Track* toTrack);

 };
}
#endif // TRACKCOPYFRAME_H
