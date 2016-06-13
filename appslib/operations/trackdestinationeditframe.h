#ifndef TRACKDESTINATIONEDITFRAME_H
#define TRACKDESTINATIONEDITFRAME_H

#include "operationsframe.h"
class QGroupBox;
class QLabel;
namespace Operations
{
 class Track;
 class LocationManager;
 class TrackDestinationEditFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrackDestinationEditFrame(QWidget* parent = 0);
  /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
  /*public*/ void initComponents(Track* track);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void radioButtonActionPerformed(QWidget* ae);
  /*public*/ void checkBoxActionPerformed(QWidget* ae);
  void on_msg(QString msg);

 private:
  Track* _track;//= null;

  LocationManager* locationManager;//= LocationManager.instance();

  // panels
  QWidget* pControls;//= new JPanel();
  QWidget* panelDestinations;//= new JPanel();
  QScrollArea* paneDestinations;//= new JScrollPane(panelDestinations);

  // major buttons
  QPushButton* saveTrackButton;//= new JButton(Bundle.getMessage("SaveTrack"));
  QPushButton* checkDestinationsButton;//= new JButton(Bundle.getMessage("CheckDestinations"));

  // radio buttons
  QRadioButton* destinationsAll;//= new JRadioButton(Bundle.getMessage("AcceptAll"));
  QRadioButton* destinationsInclude;//= new JRadioButton(Bundle.getMessage("AcceptOnly"));
  QRadioButton* destinationsExclude;//= new JRadioButton(Bundle.getMessage("Exclude"));

  // labels
  QLabel* trackName;//= new JLabel();
  Logger* log;
  /*private*/ void updateDestinations();
  /*private*/ void checkDestinationsValid();
  /*private*/ bool checkLocationsLoop();

 protected:
  /*protected*/ void enableButtons(bool enabled);
 friend class CheckLocations;
 };

 class CheckLocations : public QObject
 {
  Q_OBJECT
  TrackDestinationEditFrame* frame;
 public:
  CheckLocations(TrackDestinationEditFrame* frame);
 public slots:
  void process();
 signals:
  void finished();
  void msg(QString);
 };
}
#endif // TRACKDESTINATIONEDITFRAME_H
