#ifndef SCHEDULEOPTIONSFRAME_H
#define SCHEDULEOPTIONSFRAME_H

#include "operationsframe.h"

class JTextField;
namespace Operations
{
 class Track;
 class ScheduleEditFrame;
 class ScheduleOptionsFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ScheduleOptionsFrame(ScheduleEditFrame* parent = 0);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // text field
  JTextField* factorTextField;// = new JTextField(5);

  // combo boxes
  JComboBox* trackBox;// = new JComboBox<>();

  // radio buttons
  // major buttons
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  Track* _track;
 };
}
#endif // SCHEDULEOPTIONSFRAME_H
