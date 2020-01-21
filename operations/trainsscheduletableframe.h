#ifndef TRAINSSCHEDULETABLEFRAME_H
#define TRAINSSCHEDULETABLEFRAME_H

#include "operationsframe.h"

class QGroupBox;
class QButtonGroup;
class QLabel;
class JTable;
namespace Operations
{
 class Train;
 class TrainManager;
 class TrainScheduleManager;
 class LocationManager;
 class TrainsScheduleTableModel;
 class TrainsScheduleTableFrame : public OperationsFrame
 {
 public:
  TrainsScheduleTableFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString NAME;// = Bundle.getMessage("Name"); // Sort by choices
  /*public*/ static /*final*/ QString TIME;// = Bundle.getMessage("Time");
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  Logger* log;
  TrainManager* trainManager;// TrainManager.instance();
  TrainScheduleManager* scheduleManager;// TrainScheduleManager.instance();
  LocationManager* locationManager;// LocationManager.instance();

  TrainsScheduleTableModel* trainsScheduleModel;// new TrainsScheduleTableModel();
  JTable* trainsScheduleTable;// new javax.swing.JTable(trainsScheduleModel);
  //QScrollArea* trainsPane;

  // labels
  QLabel* textSort;// new JLabel(tr("SortBy"));

  // radio buttons
  QRadioButton* sortByName;// new JRadioButton(NAME);
  QRadioButton* sortByTime;// new JRadioButton(TIME);

  QRadioButton* noneButton;// new JRadioButton(tr("None"));

  // radio button groups
  QButtonGroup* schGroup;// new ButtonGroup();

  // major buttons
  QPushButton* selectButton;// new JButton(tr("Select"));
  QPushButton* clearButton;// new JButton(tr("Clear"));

  QPushButton* applyButton;// new JButton(tr("Apply"));
  QPushButton* buildButton;// new JButton(tr("Build"));
  QPushButton* printButton;// new JButton(tr("Print"));
  QPushButton* switchListsButton;// new JButton();
  QPushButton* terminateButton;// new JButton(tr("Terminate"));

  QPushButton* activateButton;// new JButton(tr("Activate"));
  QPushButton* saveButton;// new JButton(tr("Save"));

  // check boxes
  // panel
  QGroupBox* schedule;// new JPanel();
  /*private*/ void updateControlPanel();
  /*private*/ void updateCheckboxes(bool selected);
  /*private*/ void applySchedule();
  /*private*/ QString getSelectedScheduleId();
  /*private*/ void enableButtons(bool enable);
  /*private*/ QList<Train*> getSortByList();
  /*private*/ void setSwitchListButtonText();
  /*private*/ void setPrintButtonText();
  /*private*/ void buildSwitchList();
  /*private*/ void addPropertyChangeLocations();
  /*private*/ void removePropertyChangeLocations();
  /*private*/ void addPropertyChangeTrainSchedules();
  /*private*/ void updateSwitchListButton();
  /*private*/ void removePropertyChangeTrainSchedules();
 protected:
  /*protected*/ void storeValues();

 };
}
#endif // TRAINSSCHEDULETABLEFRAME_H
