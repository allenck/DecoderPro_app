#ifndef ALTERNATETRACKFRAME_H
#define ALTERNATETRACKFRAME_H

#include "operationsframe.h"
class JActionEvent;
namespace Operations
{
 class Track;
 class TrackEditFrame;
 class AlternateTrackFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  AlternateTrackFrame(TrackEditFrame* tef, QWidget* parent = 0);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(JActionEvent* ae = 0);
 private:
  Logger* log;
  // combo boxes
  JComboBox* trackBox;// = new JComboBox<>();

  // radio buttons
  // major buttons
  QPushButton *saveButton;// = new JButton(Bundle.getMessage("Save"));

  Track* _track;

 };
}
#endif // ALTERNATETRACKFRAME_H
