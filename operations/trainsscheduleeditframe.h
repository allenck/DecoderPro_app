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
  JComboBox* comboBox;

  // major buttons
  JButton* addButton;// = new JButton(Bundle.getMessage("Add"));
  JButton* deleteButton;// = new JButton(Bundle.getMessage("Delete"));
  JButton* replaceButton;// = new JButton(Bundle.getMessage("Replace"));

  JButton* restoreButton;// = new JButton(Bundle.getMessage("Restore"));

  TrainScheduleManager* trainScheduleManager;// = TrainScheduleManager.instance();
 };
}
#endif // TRAINSSCHEDULEEDITFRAME_H
