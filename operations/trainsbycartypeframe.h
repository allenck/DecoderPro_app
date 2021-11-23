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
  /*public*/ void buttonActionPerformed(JButton* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  TrainManager* manager;
  QString Empty;//= "            ";

  QList<QCheckBox*> trainList;//= new ArrayList<JCheckBox>();
  JPanel* trainCheckBoxes;//= new JPanel();

  // panels
  JPanel* pTrains;

  // major buttons
  JButton* clearButton;//= new JButton(Bundle.getMessage("Clear"));
  JButton* setButton;//= new JButton(Bundle.getMessage("Select"));
  JButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

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
