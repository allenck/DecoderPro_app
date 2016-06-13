#ifndef SCHEDULESTABLEFRAME_H
#define SCHEDULESTABLEFRAME_H

#include "operationsframe.h"

class QLabel;
class JTable;
namespace Operations
{
 class SchedulesTableModel;
 class SchedulesTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  SchedulesTableFrame(QWidget* parent = 0);
 public slots:
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void dispose();

 private:
  SchedulesTableModel* schedulesModel;//= new SchedulesTableModel();
  JTable* schedulesTable;//= new JTable(schedulesModel);
  //JScrollPane schedulesPane;

  // labels
  QLabel* textSort;//= new javax.swing.JLabel();
  QLabel* textSep;//= new javax.swing.JLabel();

  // radio buttons
  QRadioButton* sortByName;//= new javax.swing.JRadioButton(Bundle.getMessage("Name"));
  QRadioButton* sortById;//= new javax.swing.JRadioButton(Bundle.getMessage("Id"));
  Logger* log;
 };
}
#endif // SCHEDULESTABLEFRAME_H
