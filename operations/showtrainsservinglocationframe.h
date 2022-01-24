#ifndef SHOWTRAINSSERVINGLOCATIONFRAME_H
#define SHOWTRAINSSERVINGLOCATIONFRAME_H

#include "operationsframe.h"

class JComboBox;
class QGroupBox;
namespace Operations
{
 class Location;
 class Track;
 class ShowTrainsServingLocationFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ShowTrainsServingLocationFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  /*public*/ void comboBoxActionPerformed(QWidget* ae);
  /*public*/ void dispose();
  /*public*/ void addPropertyChangeAllTrains();
  /*public*/ void removePropertyChangeAllTrains();

 private:
  Location* _location;// = null;
  Track* _track;// = null;

  // panels
  JPanel* pTrains;// = new JPanel();

  // radio buttons
  // for padding out panel
  // combo boxes
  JComboBox* typeComboBox;// = new JComboBox<>();

  // check boxes
  QCheckBox* showAllTrainsCheckBox;// = new JCheckBox(Bundle.getMessage("ShowAllTrains"));
  /*private*/ static bool isShowAllTrains;// = true;
  /*private*/ QString comboBoxSelect;
  /*private*/ void updateComboBox();
  /*private*/ void updateTrainPane();
  Logger* log;
 };

}

#endif // SHOWTRAINSSERVINGLOCATIONFRAME_H
