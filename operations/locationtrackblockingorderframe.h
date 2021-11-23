#ifndef LOCATIONTRACKBLOCKINGORDERFRAME_H
#define LOCATIONTRACKBLOCKINGORDERFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"
class QLabel;
namespace Operations
{
 class LocationTrackBlockingOrderTableModel;
 class LocationManager;
 class Location;
 class LocationTrackBlockingOrderFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  LocationTrackBlockingOrderFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location);
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  Logger* log;
  LocationTrackBlockingOrderTableModel* trackModel;// = new LocationTrackBlockingOrderTableModel();
  JTable* trackTable;// = new JTable(trackModel);
  //QScrollArea* trackPane;// = new JScrollPane(trackTable);

  LocationManager* locationManager;// = LocationManager.instance();

  Location* _location;// = null;

  QLabel* locationName;// = new JLabel();

  // major buttons
  JButton* saveButton;// = new JButton(Bundle.getMessage("Save"));
  JButton* resetButton;//; = new JButton(Bundle.getMessage("Reset"));
  /*private*/ void enableButtons(bool enabled);

 };
}
#endif // LOCATIONTRACKBLOCKINGORDERFRAME_H
