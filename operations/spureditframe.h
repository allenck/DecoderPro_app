#ifndef SPUREDITFRAME_H
#define SPUREDITFRAME_H
#include "trackeditframe.h"
#include "appslib_global.h"

namespace Operations {

 class ScheduleEditFrame;
 class APPSLIBSHARED_EXPORT SpurEditFrame : public TrackEditFrame
 {
  Q_OBJECT
 public:
  SpurEditFrame(QWidget* parent =0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void dispose();
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  QLabel* textSchedule;// = new JLabel(Bundle.getMessage("DeliverySchedule"));
  QLabel* textSchError;// = new JLabel();
  QPushButton* editScheduleButton;// = new JButton();
  QComboBox* comboBoxSchedules;// = ScheduleManager.instance().getComboBox();
  Logger* log;
  QGroupBox* panelSchedule;// = panelOpt4;
  /*private*/ void updateScheduleButtonText();
  ScheduleEditFrame* sef;// = null;
  /*private*/ void updateScheduleComboBox();
  /*private*/ void editAddSchedule();

 protected:
  /*protected*/ void addNewTrack();
  /*protected*/ void enableButtons(bool enabled);
  /*protected*/ void saveTrack(Track* track);

 };
}
#endif // SPUREDITFRAME_H
