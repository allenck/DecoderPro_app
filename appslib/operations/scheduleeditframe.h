#ifndef SCHEDULEEDITFRAME_H
#define SCHEDULEEDITFRAME_H

#include "operationsframe.h"

class JTextField;
namespace Operations
{
 class ScheduleManager;
 class ScheduleTableModel;
 class LocationManagerXml;
 class Schedule;
 class ScheduleItem;
 class Location;
 class Track;
 class ScheduleEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ ScheduleEditFrame(Schedule* schedule, Track* track, QWidget* parent = 0);
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;//= Control.max_len_string_location_name;
  /*public*/ static /*final*/ QString NAME;//= Bundle.getMessage("Name");
  /*public*/ static /*final*/ QString DISPOSE;//= "dispose"; // NOI18N
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);

 private:
  ScheduleTableModel* scheduleModel;//= new ScheduleTableModel();
  JTable* scheduleTable;//= new JTable(scheduleModel);
  //JScrollPane schedulePane;

  ScheduleManager* manager;
  LocationManagerXml* managerXml;

  Schedule* _schedule;//= null;
  ScheduleItem* _scheduleItem;//= null;
  Location* _location;//= null;
  Track* _track;//= null;

  // labels
  // major buttons
  QPushButton* addTypeButton;//= new JButton(Bundle.getMessage("AddType"));
  QPushButton* saveScheduleButton;//= new JButton(Bundle.getMessage("SaveSchedule"));
  QPushButton* deleteScheduleButton;//= new JButton(Bundle.getMessage("DeleteSchedule"));
  QPushButton* addScheduleButton;//= new JButton(Bundle.getMessage("AddSchedule"));

  // check boxes
  QCheckBox* checkBox;

  // radio buttons
  QRadioButton* addLocAtTop;//= new JRadioButton(Bundle.getMessage("Top"));
  QRadioButton* addLocAtBottom;//= new JRadioButton(Bundle.getMessage("Bottom"));
  QRadioButton* sequentialRadioButton;//= new JRadioButton(Bundle.getMessage("Sequential"));
  QRadioButton* matchRadioButton;//= new JRadioButton(Bundle.getMessage("Match"));

  // text field
  JTextField* scheduleNameTextField;//= new JTextField(20);
  JTextField* commentTextField;//= new JTextField(35);

  // combo boxes
  QComboBox* typeBox;//= new JComboBox<>();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void loadTypeComboBox();
  Logger* log;
  /*private*/ void addNewScheduleItem();
  /*private*/ void saveNewSchedule();
   /*private*/ void saveSchedule();
   /*private*/ bool checkName(QString s);
   /*private*/ void reportScheduleExists(QString s);
 friend class ScheduleOptionsFrame;
 };
}
#endif // SCHEDULEEDITFRAME_H
