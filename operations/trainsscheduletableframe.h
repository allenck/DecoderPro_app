#ifndef TRAINSSCHEDULETABLEFRAME_H
#define TRAINSSCHEDULETABLEFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"
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
 class TrainsScheduleTableFrame : public OperationsFrame, public PropertyChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  TrainsScheduleTableFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString NAME;// = Bundle.getMessage("Name"); // Sort by choices
  /*public*/ static /*final*/ QString TIME;// = Bundle.getMessage("Time");
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void radioButtonActionPerformed(QWidget* ae) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;

 private:
  Logger* log;
  TrainManager* trainManager;// TrainManager.instance();
  TrainScheduleManager* trainScheduleManager;// TrainScheduleManager.instance();
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
  JButton* selectButton;// new JButton(tr("Select"));
  JButton* clearButton;// new JButton(tr("Clear"));

  JButton* applyButton;// new JButton(tr("Apply"));
  JButton* buildButton;// new JButton(tr("Build"));
  JButton* printButton;// new JButton(tr("Print"));
  JButton* switchListsButton;// new JButton();
  JButton* terminateButton;// new JButton(tr("Terminate"));

  JButton* activateButton;// new JButton(tr("Activate"));
  JButton* saveButton;// new JButton(tr("Save"));

  // check boxes
  // panel
  JPanel* schedule;// new JPanel();
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
