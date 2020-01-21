#ifndef TRAINSSCHEDULEEDITFRAME_H
#define TRAINSSCHEDULEEDITFRAME_H

#include "operationsframe.h"
class JTextField;
namespace Operations
{
 class TrainScheduleManager;
 class TrainsScheduleEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainsScheduleEditFrame(QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:// text box
  Logger* log;
  JTextField* addTextBox;// = new JTextField(Control.max_len_string_attibute);

  // combo box
  QComboBox* comboBox;

  // major buttons
  QPushButton* addButton;// = new JButton(Bundle.getMessage("Add"));
  QPushButton* deleteButton;// = new JButton(Bundle.getMessage("Delete"));
  QPushButton* replaceButton;// = new JButton(Bundle.getMessage("Replace"));

  QPushButton* restoreButton;// = new JButton(Bundle.getMessage("Restore"));

  TrainScheduleManager* trainScheduleManager;// = TrainScheduleManager.instance();
 };
}
#endif // TRAINSSCHEDULEEDITFRAME_H
