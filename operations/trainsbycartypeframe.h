#ifndef TRAINSBYCARTYPEFRAME_H
#define TRAINSBYCARTYPEFRAME_H

#include "operationsframe.h"

class QLabel;
namespace Operations
{
 class TrainManager;
 class TrainsByCarTypeFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainsByCarTypeFrame(QWidget* parent = 0);
  /*public*/ void initComponents(QString carType);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QPushButton* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  TrainManager* manager;
  QString Empty;//= "            ";

  QList<QCheckBox*> trainList;//= new ArrayList<JCheckBox>();
  QWidget* trainCheckBoxes;//= new JPanel();

  // panels
  QWidget* pTrains;

  // major buttons
  QPushButton* clearButton;//= new JButton(Bundle.getMessage("Clear"));
  QPushButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // check boxes
  QCheckBox* copyCheckBox;//= new JCheckBox(Bundle.getMessage("Copy"));

  // radio buttons
  // text field
  QLabel* textCarType;//= new JLabel(Empty);

  // for padding out panel
  // combo boxes
  JComboBox* typeComboBox;//= CarTypes.instance().getComboBox();
  Logger* log;
  /*private*/ void save();
  /*private*/ void updateTrains();
  /*private*/ void updateComboBox();
  /*private*/ void selectCheckboxes(bool b);
  /*private*/ void removePropertyChangeTrains();

 };
}
#endif // TRAINSBYCARTYPEFRAME_H
