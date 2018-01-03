#ifndef CHANGEDEPARTURETIMESFRAME_H
#define CHANGEDEPARTURETIMESFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class ChangeDepartureTimesFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ChangeDepartureTimesFrame(QWidget* parent = 0);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  QPushButton* changeButton;// = new javax.swing.JButton(Bundle.getMessage("Change"));

  // combo boxes
  QComboBox* hourBox;// = new javax.swing.JComboBox<>();
  /*private*/ QString adjustHour(QString time);
  Logger* log;
 };
}
#endif // CHANGEDEPARTURETIMESFRAME_H
