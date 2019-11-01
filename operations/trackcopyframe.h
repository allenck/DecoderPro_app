#ifndef TRACKCOPYFRAME_H
#define TRACKCOPYFRAME_H

#include "operationsframe.h"

class JTextField;
namespace Operations
{
 class LocationEditFrame;
 class Location;
 class TrackCopyFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrackCopyFrame(LocationEditFrame* lef);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  // text field
  JTextField* trackNameTextField;// =new JTextField(Control.max_len_string_track_name);

  // major buttons
  QPushButton* copyButton;// =new JButton(Bundle.getMessage("Copy"));
  QPushButton* saveButton;// =new JButton(Bundle.getMessage("Save"));

  // combo boxes
  QComboBox* locationBox;// =LocationManager.instance().getComboBox();
  QComboBox* trackBox;// =new JComboBox<>();

  // checkboxes
  QCheckBox* sameNameCheckBox;// =new JCheckBox(Bundle.getMessage("SameName"));
  QCheckBox* moveRollingStockCheckBox;// =new JCheckBox(Bundle.getMessage("MoveRollingStock"));
  QCheckBox* deleteTrackCheckBox;// =new JCheckBox(Bundle.getMessage("DeleteCopiedTrack"));

  Location* _location;	// Copy the track to this location
  static bool sameName;// =false;
  static bool moveRollingStock;// =false;
  static bool deleteTrack;// =false;
  Logger * log;

 protected slots:
  /*protected*/ void comboBoxActionPerformed(QWidget* ae);
 protected:
  /*protected*/ void updateTrackComboBox();
  /*protected*/ void updateTrackName();
  /*protected*/ void updateComboBoxes();

 };
}
#endif // TRACKCOPYFRAME_H
