#ifndef TRACKROADEDITFRAME_H
#define TRACKROADEDITFRAME_H

#include "operationsframe.h"

class QLabel;
class QGroupBox;
namespace Operations
{
 class Location;
 class Track;
 class TrackRoadEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrackRoadEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = Control::max_len_string_track_name;

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void dispose();

 private:
  Location* _location;//= null;
  Track* _track;//= null;

  // panels
  QGroupBox* pRoadControls;//= new JPanel();
  QWidget* panelRoads;//= new JPanel();
  QScrollArea* paneRoads;//= new JScrollPane(panelRoads);

  // major buttons
  QPushButton* saveTrackButton;//= new JButton(Bundle.getMessage("SaveTrack"));
  QPushButton* addRoadButton;//= new JButton(Bundle.getMessage("AddRoad"));
  QPushButton* deleteRoadButton;//= new JButton(Bundle.getMessage("DeleteRoad"));
  QPushButton* deleteAllRoadsButton;//= new JButton(Bundle.getMessage("DeleteAll"));

  // radio buttons
  QRadioButton* roadNameAll;//= new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* roadNameInclude;//= new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* roadNameExclude;//= new JRadioButton(Bundle.getMessage("Exclude"));

  // combo box
  QComboBox* comboBoxRoads;//= CarRoads.instance().getComboBox();

  // labels
  QLabel* trackName;//= new JLabel();
  Logger* log;
  /*private*/ void updateRoadComboBox();
  /*private*/ void updateRoadNames();
  /*private*/ void deleteAllRoads();
  /*private*/ void checkForErrors();

 protected:
  /*protected*/ void enableButtons(bool enabled);

 };
}
#endif // TRACKROADEDITFRAME_H
