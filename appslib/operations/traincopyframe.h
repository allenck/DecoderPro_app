#ifndef TRAINCOPYFRAME_H
#define TRAINCOPYFRAME_H

#include "operationsframe.h"
class JTextField;
class QComboBox;
namespace Operations
{
 class Train;
 class TrainManager;
 class TrainCopyFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainCopyFrame(Train* train, QWidget* parent = 0);
  /*public*/ void dispose();
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  TrainManager* trainManager;// = TrainManager.instance();

  // labels
  // text field
  JTextField* trainNameTextField;// = new javax.swing.JTextField(Control.max_len_string_train_name);

  // major buttons
  QPushButton* copyButton;// = new javax.swing.JButton(Bundle.getMessage("Copy"));

  // combo boxes
  QComboBox* trainBox;// = TrainManager.instance().getTrainComboBox();
  Logger* log;
  /*private*/ void reportTrainExists();
  /*private*/ void reportTrainDoesNotExist();
  /*private*/ bool checkName();

 };
}
#endif // TRAINCOPYFRAME_H
