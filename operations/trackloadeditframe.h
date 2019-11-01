#ifndef TRACKLOADEDITFRAME_H
#define TRACKLOADEDITFRAME_H

#include "operationsframe.h"
class QLabel;
class QGroupBox;
class QMenu;
namespace Operations
{
 class Location;
 class Track;
 class TrackLoadEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ TrackLoadEditFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ static /*final*/ QString DISPOSE;//= "dispose"; // NOI18N
  /*public*/ static /*final*/ int MAX_NAME_LENGTH;//= Control.max_len_string_track_name;
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);

 private:
  ///*private*/ static /*final*/ long serialVersionUID = -5231003531264725867L;
  /*private*/ static bool loadAndType;// = false;
  /*private*/ static bool shipLoadAndType;// = false;
  Location* _location;//= null;
  Track* _track;//= null;
  QString _type;//= "";
  QMenu* _toolMenu;//= null;

  // panels
  QWidget* pLoadControls;//= new JPanel();
  QWidget* panelLoads;//= new JPanel();
  QScrollArea* paneLoads;//= new JScrollPane(panelLoads);

  QGroupBox* pShipLoadControls;//= new JPanel();
  QGroupBox* panelShipLoads;//= new JPanel();
  QScrollArea* paneShipLoadControls;
  QScrollArea* paneShipLoads;//= new JScrollPane(panelShipLoads);

  // major buttons
  QPushButton* saveTrackButton;//= new JButton(Bundle.getMessage("SaveTrack"));

  QPushButton* addLoadButton;//= new JButton(Bundle.getMessage("AddLoad"));
  QPushButton* deleteLoadButton;//= new JButton(Bundle.getMessage("DeleteLoad"));
  QPushButton* deleteAllLoadsButton;//= new JButton(Bundle.getMessage("DeleteAll"));

  QPushButton* addShipLoadButton;//= new JButton(Bundle.getMessage("AddLoad"));
  QPushButton* deleteShipLoadButton;//= new JButton(Bundle.getMessage("DeleteLoad"));
  QPushButton* deleteAllShipLoadsButton;//= new JButton(Bundle.getMessage("DeleteAll"));

  // check boxes
  QCheckBox* loadAndTypeCheckBox;//= new JCheckBox(Bundle.getMessage("TypeAndLoad"));
  QCheckBox* shipLoadAndTypeCheckBox;//= new JCheckBox(Bundle.getMessage("TypeAndLoad"));

  // radio buttons
  QRadioButton* loadNameAll;//= new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* loadNameInclude;//= new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* loadNameExclude;//= new JRadioButton(Bundle.getMessage("Exclude"));

  QRadioButton* shipLoadNameAll;//= new JRadioButton(Bundle.getMessage("ShipAll"));
  QRadioButton* shipLoadNameInclude;//= new JRadioButton(Bundle.getMessage("ShipOnly"));
  QRadioButton* shipLoadNameExclude;//= new JRadioButton(Bundle.getMessage("Exclude"));

  // combo box
  QComboBox* comboBoxLoads;//= CarLoads.instance().getComboBox(null);
  QComboBox* comboBoxShipLoads;//= CarLoads.instance().getComboBox(null);
  QComboBox* comboBoxTypes;//= CarTypes.instance().getComboBox();
  QComboBox* comboBoxShipTypes;//= CarTypes.instance().getComboBox();

  // labels
  QLabel* trackName;//= new JLabel();
  Logger* log;
  /*private*/ void updateLoadComboBoxes();
  /*private*/ void updateLoadNames();
  /*private*/ void updateShipLoadNames();
  /*private*/ void deleteAllLoads();
  /*private*/ void deleteAllShipLoads();
  /*private*/ void updateTypeComboBoxes();
  /*private*/ void checkForErrors();

  protected:
  /*protected*/ void save();
  /*protected*/ void updateButtons(bool enabled);

 };
}
#endif // TRACKLOADEDITFRAME_H
