#ifndef LOCATIONTRACKBLOCKINGORDERFRAME_H
#define LOCATIONTRACKBLOCKINGORDERFRAME_H

#include "operationsframe.h"
class QLabel;
namespace Operations
{
 class LocationTrackBlockingOrderTableModel;
 class LocationManager;
 class Location;
 class LocationTrackBlockingOrderFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  LocationTrackBlockingOrderFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location);
  /*public*/ void dispose();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  LocationTrackBlockingOrderTableModel* trackModel;// = new LocationTrackBlockingOrderTableModel();
  JTable* trackTable;// = new JTable(trackModel);
  //QScrollArea* trackPane;// = new JScrollPane(trackTable);

  LocationManager* locationManager;// = LocationManager.instance();

  Location* _location;// = null;

  QLabel* locationName;// = new JLabel();

  // major buttons
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));
  QPushButton* resetButton;//; = new JButton(Bundle.getMessage("Reset"));
  /*private*/ void enableButtons(bool enabled);

 };
}
#endif // LOCATIONTRACKBLOCKINGORDERFRAME_H
