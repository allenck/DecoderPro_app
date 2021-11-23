#ifndef PRINTLOCATIONSACTION_H
#define PRINTLOCATIONSACTION_H

#include "abstractaction.h"
#include "operationsframe.h"

class HardcopyWriter;
namespace Operations
{
 class Track;
 class LocationPrintOptionFrame;
 class Location;
 class LocationManager;
 class PrintLocationsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintLocationsAction(QString actionName, bool isPreview, QObject* parent);
  /*public*/ PrintLocationsAction(QString actionName, bool isPreview, Location* location, QObject* parent);
  /*public*/ void printLocations();

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  static /*final*/ QString NEW_LINE;//= "\n"; // NOI18N
  static /*final*/ QString FORM_FEED;//= "\f"; // NOI18N
  static /*final*/ QString TAB;//= "\t"; // NOI18N
  static /*final*/ int TAB_LENGTH;//= 10;
  static /*final*/ QString SPACE;//= "   ";

  static /*final*/ int MAX_NAME_LENGTH;//= Control::max_len_string_location_name;
  LocationManager* manager;//= LocationManager::instance();
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool _isPreview;
  Location* _location;//= NULL;
  HardcopyWriter* writer;
  LocationPrintOptionFrame* lpof;//= NULL;
  Logger* log;
  /*private*/ int charactersPerLine;// = 70;
  QCheckBox* _printLocations;//= new JCheckBox(tr("PrintLocations"));
  QCheckBox* printSchedules;//= new JCheckBox(tr("PrintSchedules"));
  QCheckBox* printComments;//= new JCheckBox(tr("PrintComments"));
  QCheckBox* printDetails;//= new JCheckBox(tr("PrintDetails"));
  QCheckBox* printAnalysis;//= new JCheckBox(tr("PrintAnalysis"));

  JButton* okayButton;//= new JButton(tr("ButtonOkay"));
  void common();
  /*private*/ void printLocationsSelected();// //throws IOException
  /*private*/ void printSchedulesSelected();// //throws IOException
  /*private*/ void printCommentsSelected();// //throws IOException
  /*private*/ void printDetailsSelected(); //throws IOException
  /*private*/ void printAnalysisSelected(); //throws IOException
  /*private*/ /*final*/ bool showStaging;// = false;
  /*private*/ QString getDirection(int dir);
  /*private*/ void printTrackInfo(Location* location, QList<Track*> tracks);
  /*private*/ int getTrackLengthAcceptType(QList<Location*> locations, QString carType, QString trackType); //throws IOException
  /*private*/ QString getTrackString(Track* track);
  /*private*/ QString getLocationTypes(Location* location);
  /*private*/ QString getTrackTypes(Location* location, Track* track);
  /*private*/ QString getTrackRoads(Track* track);
  /*private*/ QString getTrackLoads(Track* track);
  /*private*/ QString getTrackShipLoads(Track* track);
  /*private*/ QString getCarOrder(Track* track);
  /*private*/ QString getSetOutTrains(Track* track);
  /*private*/ QString getPickUpTrains(Track* track);
  /*private*/ QString getDestinations(Track* track);
  /*private*/ QString getSchedule(Track* track) ;
  /*private*/ QString padOutString(QString s, int length);
 friend class LocationPrintOptionFrame;
 };

 /*public*/ class LocationPrintOptionFrame : public OperationsFrame
 {
  Q_OBJECT
  PrintLocationsAction* pla;
public:
  /*public*/ LocationPrintOptionFrame(PrintLocationsAction* pla);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
 };

}
#endif // PRINTLOCATIONSACTION_H
