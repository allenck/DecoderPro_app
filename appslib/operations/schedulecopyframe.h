#ifndef SCHEDULECOPYFRAME_H
#define SCHEDULECOPYFRAME_H

#include "operationsframe.h"

class JTextField;
class QPushButton;
namespace Operations
{
 class Schedule;
 class ScheduleManager;
 class ScheduleCopyFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ScheduleCopyFrame(QWidget* parent = 0);
  /*public*/ ScheduleCopyFrame(Schedule* schedule, QWidget* parent  = 0);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*protected*/ void buttonActionPerformed(QWidget* ae);

 private:
  ScheduleManager* scheduleManager;//= ScheduleManager.instance();

  // text field
  JTextField* scheduleNameTextField;//= new javax.swing.JTextField(Control.max_len_string_location_name);

  // major buttons
  QPushButton* copyButton;//= new javax.swing.JButton(Bundle.getMessage("Copy"));

  // combo boxes
  QComboBox* scheduleBox;//= scheduleManager.getComboBox();
  Logger* log;
  void common(Schedule* );

 protected:
  /*protected*/ void updateComboBoxes();
  /*protected*/ bool checkName();

 };
}
#endif // SCHEDULECOPYFRAME_H
