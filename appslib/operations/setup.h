#ifndef SETUP_H
#define SETUP_H

#include <QObject>
#include <QtXml>
#include "propertychangesupport.h"

class QComboBox;
namespace Operations
{
 class Control;
 class Setup : public QObject
 {
  Q_OBJECT
 public:
  explicit Setup(QObject *parent = 0);
  /*public*/ static bool isMainMenuEnabled();
  /*public*/ static void setMainMenuEnabled(bool enabled);
  /*public*/ static bool isCloseWindowOnSaveEnabled();
  /*public*/ static void setCloseWindowOnSaveEnabled(bool enabled);
  /*public*/ static bool isAutoSaveEnabled() ;
  /*public*/ static void setAutoSaveEnabled(bool enabled);
  /*public*/ static bool isAutoBackupEnabled() ;
  /*public*/ static void setAutoBackupEnabled(bool enabled);
  /*public*/ static bool isValueEnabled();
  /*public*/ static void setValueEnabled(bool enabled);
  /*public*/ static QString getValueLabel() ;
  /*public*/ static void setValueLabel(QString label);
  /*public*/ static bool isRfidEnabled();
  /*public*/ static void setRfidEnabled(bool enabled);
  /*public*/ static QString getRfidLabel();
  /*public*/ static void setRfidLabel(QString label);
  /*public*/ static bool isCarRoutingEnabled();
  /*public*/ static void setCarRoutingEnabled(bool enabled);
  /*public*/ static bool isCarRoutingViaYardsEnabled() ;
  /*public*/ static void setCarRoutingViaYardsEnabled(bool enabled);
  /*public*/ static bool isCarRoutingViaStagingEnabled() ;
  /*public*/ static void setCarRoutingViaStagingEnabled(bool enabled) ;
  /*public*/ static bool isForwardToYardEnabled();
  /*public*/ static void setForwardToYardEnabled(bool enabled) ;
  /*public*/ static bool isOnlyActiveTrainsEnabled() ;
  /*public*/ static void setOnlyActiveTrainsEnabled(bool enabled);
  /*public*/ static bool isCheckCarDestinationEnabled();
  /*public*/ static void setCheckCarDestinationEnabled(bool enabled);
  /*public*/ static bool isBuildAggressive() ;
  /*public*/ static void setBuildAggressive(bool enabled);
  /*public*/ static int getNumberPasses();
  /*public*/ static void setNumberPasses(int number);
  /*public*/ static bool isLocalInterchangeMovesEnabled() ;
  /*public*/ static void setLocalInterchangeMovesEnabled(bool enabled);
  /*public*/ static bool isLocalYardMovesEnabled() ;
  /*public*/ static void setLocalYardMovesEnabled(bool enabled) ;
  /*public*/ static bool isLocalSpurMovesEnabled() ;
  /*public*/ static void setLocalSpurMovesEnabled(bool enabled) ;
  /*public*/ static bool isTrainIntoStagingCheckEnabled() ;
  /*public*/ static void setTrainIntoStagingCheckEnabled(bool enabled);
  /*public*/ static bool isStagingTrackImmediatelyAvail() ;
  /*public*/ static void setStagingTrackImmediatelyAvail(bool enabled);
  /*public*/ static bool isAllowReturnToStagingEnabled() ;
  /*public*/ static void setAllowReturnToStagingEnabled(bool enabled) ;
  /*public*/ static bool isPromptFromStagingEnabled() ;
  /*public*/ static void setPromptFromStagingEnabled(bool enabled);
  /*public*/ static bool isPromptToStagingEnabled() ;
  /*public*/ static void setPromptToStagingEnabled(bool enabled) ;
  /*public*/ static bool isGenerateCsvManifestEnabled();
  /*public*/ static void setGenerateCsvManifestEnabled(bool enabled);
  /*public*/ static bool isGenerateCsvSwitchListEnabled();
  /*public*/ static void setGenerateCsvSwitchListEnabled(bool enabled) ;
  /*public*/ static bool isVsdPhysicalLocationEnabled();
  /*public*/ static void setVsdPhysicalLocationEnabled(bool enabled);
  /*public*/ static QString getHazardousMsg();
  /*public*/ static void setHazardousMsg(QString message);
  /*public*/ static QString getMiaComment();
  /*public*/ static void setMiaComment(QString comment) ;
  /*public*/ static void setTrainDirection(int direction) ;
  /*public*/ static int getTrainDirection() ;
  /*public*/ static void setMaxTrainLength(int length);
  /*public*/ static int getMaxTrainLength();
  /*public*/ static void setMaxNumberEngines(int value);
  /*public*/ static int getMaxNumberEngines() ;
  /*public*/ static void setHorsePowerPerTon(int value);
  /*public*/ static int getHorsePowerPerTon() ;
  /*public*/ static void setCarMoves(int moves);
  /*public*/ static int getCarMoves() ;
  /*public*/ static QString getPanelName();
  /*public*/ static void setPanelName(QString name);
  /*public*/ static QString getLengthUnit();
  /*public*/ static void setLengthUnit(QString unit) ;
  /*public*/ static QString getYearModeled();
  /*public*/ static void setYearModeled(QString year);
  /*public*/ static QString getCarTypes();
  /*public*/ static void setCarTypes(QString types) ;
  /*public*/ static void setTrainIconCordEnabled(bool enable);
  /*public*/ static bool isTrainIconCordEnabled();
  /*public*/ static void setTrainIconAppendEnabled(bool enable) ;
  /*public*/ static bool isTrainIconAppendEnabled();
  /*public*/ static void setBuildReportLevel(QString  level);
  /*public*/ static QString  getBuildReportLevel();
  /*public*/ static void setRouterBuildReportLevel(QString  level);
  /*public*/ static QString  getRouterBuildReportLevel() ;
  /*public*/ static void setManifestEditorEnabled(bool enable);
  /*public*/ static bool isManifestEditorEnabled();
  /*public*/ static void setBuildReportEditorEnabled(bool enable);
  /*public*/ static bool isBuildReportEditorEnabled() ;
  /*public*/ static void setBuildReportIndentEnabled(bool enable);
  /*public*/ static bool isBuildReportIndentEnabled() ;
  /*public*/ static void setBuildReportAlwaysPreviewEnabled(bool enable);
  /*public*/ static bool isBuildReportAlwaysPreviewEnabled();
  /*public*/ static void setSwitchListFormatSameAsManifest(bool b);
  /*public*/ static bool isSwitchListFormatSameAsManifest();
  /*public*/ static void setTrackSummaryEnabled(bool b);
  /*public*/ static bool isTrackSummaryEnabled();
  /*public*/ static void setSwitchListRouteLocationCommentEnabled(bool b);
  /*public*/ static bool isSwitchListRouteLocationCommentEnabled();
  /*public*/ static void setSwitchListRealTime(bool b);
  /*public*/ static bool isSwitchListRealTime();
  /*public*/ static void setSwitchListAllTrainsEnabled(bool b);
  /*public*/ static bool isSwitchListAllTrainsEnabled();
  /*public*/ static void setSwitchListPageFormat(QString  format);
  /*public*/ static QString  getSwitchListPageFormat() ;
  /*public*/ static void setTruncateManifestEnabled(bool b);
  /*public*/ static bool isTruncateManifestEnabled();
  /*public*/ static void setUseDepartureTimeEnabled(bool b);
  /*public*/ static bool isUseDepartureTimeEnabled();
  /*public*/ static void setPrintLocationCommentsEnabled(bool enable);
  /*public*/ static bool isPrintLocationCommentsEnabled();
  /*public*/ static void setPrintRouteCommentsEnabled(bool enable);
  /*public*/ static bool isPrintRouteCommentsEnabled();
  /*public*/ static void setPrintLoadsAndEmptiesEnabled(bool enable);
  /*public*/ static bool isPrintLoadsAndEmptiesEnabled();
  /*public*/ static void setPrintTimetableNameEnabled(bool enable);
  /*public*/ static bool isPrintTimetableNameEnabled();
  /*public*/ static void set12hrFormatEnabled(bool enable);
  /*public*/ static bool is12hrFormatEnabled();
  /*public*/ static void setPrintValidEnabled(bool enable);
  /*public*/ static bool isPrintValidEnabled();
  /*public*/ static void setSortByTrackEnabled(bool enable);
  /*public*/ static bool isSortByTrackEnabled();
  /*public*/ static void setPrintHeadersEnabled(bool enable) ;
  /*public*/ static bool isPrintHeadersEnabled() ;
  /*public*/ static void setPrintCabooseLoadEnabled(bool enable);
  /*public*/ static bool isPrintCabooseLoadEnabled();
  /*public*/ static void setPrintPassengerLoadEnabled(bool enable);
  /*public*/ static bool isPrintPassengerLoadEnabled();
  /*public*/ static void setSwitchTime(int  minutes);
  /*public*/ static int  getSwitchTime();
  /*public*/ static void setTravelTime(int  minutes) ;
  /*public*/ static int  getTravelTime();
  /*public*/ static void setTrainIconColorNorth(QString  color);
  /*public*/ static QString  getTrainIconColorNorth();
  /*public*/ static void setTrainIconColorSouth(QString  color);
  /*public*/ static QString  getTrainIconColorSouth() ;
  /*public*/ static void setTrainIconColorEast(QString  color);
  /*public*/ static QString  getTrainIconColorEast() ;
  /*public*/ static void setTrainIconColorWest(QString  color);
  /*public*/ static QString  getTrainIconColorWest();
  /*public*/ static void setTrainIconColorLocal(QString  color);
  /*public*/ static QString  getTrainIconColorLocal();
  /*public*/ static void setTrainIconColorTerminate(QString  color);
  /*public*/ static QString  getTrainIconColorTerminate();
  /*public*/ static QString  getFontName();
  /*public*/ static void setFontName(QString  name);
  /*public*/ static int  getManifestFontSize();
  /*public*/ static void setManifestFontSize(int  size) ;
  /*public*/ static int  getBuildReportFontSize() ;
  /*public*/ static void setBuildReportFontSize(int  size);
  /*public*/ static QString  getManifestOrientation();
  /*public*/ static void setManifestOrientation(QString  orientation) ;
  /*public*/ static QString  getSwitchListOrientation();
  /*public*/ static void setSwitchListOrientation(QString  orientation);
  /*public*/ static bool isTabEnabled();
  /*public*/ static void setTabEnabled(bool enable);
  /*public*/ static int  getTab1Length();
  /*public*/ static void setTab1length(int  length);
  /*public*/ static int  getTab2Length() ;
  /*public*/ static void setTab2length(int  length);
  /*public*/ static int  getTab3Length() ;
  /*public*/ static void setTab3length(int  length);
  /*public*/ static QString  getManifestFormat();
  /*public*/ static void setManifestFormat(QString  format);
  /*public*/ static bool isCarLoggerEnabled();
  /*public*/ static void setCarLoggerEnabled(bool enable);
  /*public*/ static bool isEngineLoggerEnabled();
  /*public*/ static void setEngineLoggerEnabled(bool enable);
  /*public*/ static bool isTrainLoggerEnabled() ;
  /*public*/ static void setTrainLoggerEnabled(bool enable);
  /*public*/ static QString  getPickupEnginePrefix();
  /*public*/ static void setPickupEnginePrefix(QString  prefix);
  /*public*/ static QString  getDropEnginePrefix() ;
  /*public*/ static void setDropEnginePrefix(QString  prefix);
  /*public*/ static QString  getPickupCarPrefix();
  /*public*/ static void setPickupCarPrefix(QString  prefix);
  /*public*/ static QString  getDropCarPrefix();
  /*public*/ static void setDropCarPrefix(QString  prefix);
  /*public*/ static QString  getLocalPrefix() ;
  /*public*/ static void setLocalPrefix(QString  prefix);
  /*public*/ static int  getManifestPrefixLength() ;
  /*public*/ static QString  getSwitchListPickupCarPrefix();
  /*public*/ static void setSwitchListPickupCarPrefix(QString  prefix) ;
  /*public*/ static QString  getSwitchListDropCarPrefix();
  /*public*/ static void setSwitchListDropCarPrefix(QString  prefix);
  /*public*/ static QString  getSwitchListLocalPrefix();
  /*public*/ static void setSwitchListLocalPrefix(QString  prefix);
  /*public*/ static int  getSwitchListPrefixLength();
  /*public*/ static QStringList getEngineAttributes();
  /*public*/ static QStringList getPickupEngineMessageFormat();
  /*public*/ static void setPickupEngineMessageFormat(QStringList format);
  /*public*/ static QStringList getDropEngineMessageFormat();
  /*public*/ static void setDropEngineMessageFormat(QStringList format);
  /*public*/ static QStringList getCarAttributes();
  /*public*/ static QStringList getPickupManifestMessageFormat();
  /*public*/ static void setPickupManifestMessageFormat(QStringList format) ;
  /*public*/ static QStringList getDropManifestMessageFormat() ;
  /*public*/ static void setDropManifestMessageFormat(QStringList format);
  /*public*/ static QStringList getLocalManifestMessageFormat();
  /*public*/ static void setLocalManifestMessageFormat(QStringList format);
  /*public*/ static QStringList getMissingCarMessageFormat();
  /*public*/ static void setMissingCarMessageFormat(QStringList format);
  /*public*/ static QStringList getPickupSwitchListMessageFormat();
  /*public*/ static void setPickupSwitchListMessageFormat(QStringList format) ;
  /*public*/ static QStringList getDropSwitchListMessageFormat() ;
  /*public*/ static void setDropSwitchListMessageFormat(QStringList format);
  /*public*/ static QStringList getLocalSwitchListMessageFormat() ;
  /*public*/ static void setLocalSwitchListMessageFormat(QStringList format);
  /*public*/ static QStringList getPickupUtilityManifestMessageFormat();
  /*public*/ static QStringList getDropUtilityManifestMessageFormat();
  /*public*/ static QStringList getLocalUtilityManifestMessageFormat();
  /*public*/ static QStringList getPickupUtilitySwitchListMessageFormat();
  /*public*/ static QStringList getDropUtilitySwitchListMessageFormat();
  /*public*/ static QStringList getLocalUtilitySwitchListMessageFormat();
  /*private*/ static QStringList createUitlityCarMessageFormat(QStringList format) ;
  /*public*/ static QStringList getPickupTruncatedManifestMessageFormat();
  /*public*/ static QStringList getDropTruncatedManifestMessageFormat();
  /*private*/ static QStringList createTruncatedManifestMessageFormat(QStringList format) ;
  /*public*/ static QStringList getPickupTwoColumnByTrackManifestMessageFormat();
  /*public*/ static QStringList getPickupTwoColumnByTrackSwitchListMessageFormat() ;
  /*public*/ static QStringList getPickupTwoColumnByTrackUtilityManifestMessageFormat();
  /*public*/ static QStringList getPickupTwoColumnByTrackUtilitySwitchListMessageFormat();
  /*private*/ static QStringList createTwoColumnByTrackPickupMessageFormat(QStringList format);
  /*public*/ static QStringList getDropTwoColumnByTrackManifestMessageFormat();
  /*public*/ static QStringList getDropTwoColumnByTrackSwitchListMessageFormat();
  /*public*/ static QStringList getDropTwoColumnByTrackUtilityManifestMessageFormat() ;
  /*public*/ static QStringList getDropTwoColumnByTrackUtilitySwitchListMessageFormat();
  /*private*/ static QStringList createTwoColumnByTrackDropMessageFormat(QStringList format);
  /*public*/ static QString  getDropTextColor();
  /*public*/ static void setDropTextColor(QString  color);
  /*public*/ static QString  getPickupTextColor();
  /*public*/ static void setPickupTextColor(QString  color);
  /*public*/ static QString  getLocalTextColor();
  /*public*/ static void setLocalTextColor(QString  color);
  /*public*/ static QColor getPickupColor();
  /*public*/ static QColor getDropColor();
  /*public*/ static QColor getLocalColor();
  /*public*/ static QColor getColor(QString  colorName) ;
  /*public*/ static QString  getManifestLogoURL() ;
  /*public*/ static void setManifestLogoURL(QString  pathName) ;
  /*public*/ static QString  getOwnerName();
  /*public*/ static void setOwnerName(QString  name);
  /*public*/ static int  getScaleRatio() ;
  /*public*/ static int  getScaleTonRatio();
  /*public*/ static int  getInitalWeight();
  /*public*/ static int  getAddWeight();
  /*public*/ static int  getScale() ;
  /*public*/ static void setScale(int  s);
  /*public*/ static QComboBox* getManifestFormatComboBox();
  /*public*/ static  QComboBox* getOrientationComboBox();
  /*public*/ static  QComboBox* getSwitchListPageFormatComboBox() ;
  /*public*/ static  QComboBox* getPrintColorComboBox();
  /*public*/ static  QComboBox* getEngineMessageComboBox();
  /*public*/ static  QComboBox* getCarMessageComboBox();
  /*public*/ static  QComboBox* getTrainDirectionComboBox();
  /*public*/ static QVector<QString> getTrainDirectionList();
  /*public*/ static QString  getDirectionString(int  direction);
  /*public*/ static QStringList getDirectionStrings(int  directions) ;
  /*public*/ static int  getDirectionInt(QString  direction);
  /*public*/ static /*final*/ QString EAST_DIR;// Bundle.getMessage("East");
  /*public*/ static /*final*/ QString WEST_DIR;// Bundle.getMessage("West");
  /*public*/ static /*final*/ QString NORTH_DIR;// Bundle.getMessage("North");
  /*public*/ static /*final*/ QString SOUTH_DIR;// Bundle.getMessage("South");

  /*public*/ static /*final*/ QString DESCRIPTIVE;// Bundle.getMessage("Descriptive"); // Car types
  /*public*/ static /*final*/ QString AAR;// Bundle.getMessage("ArrCodes"); // Car types

  /*public*/ static /*final*/ QString MONOSPACED;// Bundle.getMessage("Monospace"); // default printer font

  /*public*/ static /*final*/ QString STANDARD_FORMAT;// Bundle.getMessage("StandardFormat");
  /*public*/ static /*final*/ QString TWO_COLUMN_FORMAT;// Bundle.getMessage("TwoColumnFormat");
  /*public*/ static /*final*/ QString TWO_COLUMN_TRACK_FORMAT;// Bundle.getMessage("TwoColumnTrackFormat");

  /*public*/ static /*final*/ QString PORTRAIT;// Bundle.getMessage("Portrait");
  /*public*/ static /*final*/ QString LANDSCAPE;// Bundle.getMessage("Landscape");
  /*public*/ static /*final*/ QString HALFPAGE;// Bundle.getMessage("HalfPage");
  /*public*/ static /*final*/ QString HANDHELD;// Bundle.getMessage("HandHeld");

  /*public*/ static /*final*/ QString PAGE_NORMAL;// Bundle.getMessage("PageNormal");
  /*public*/ static /*final*/ QString PAGE_PER_TRAIN;// Bundle.getMessage("PagePerTrain");
  /*public*/ static /*final*/ QString PAGE_PER_VISIT;// Bundle.getMessage("PagePerVisit");

  /*public*/ static /*final*/ QString LENGTHABV;// Bundle.getMessage("LengthSymbol");

  /*public*/ static /*final*/ QString BUILD_REPORT_MINIMAL;// "1";
  /*public*/ static /*final*/ QString BUILD_REPORT_NORMAL;// "3";
  /*public*/ static /*final*/ QString BUILD_REPORT_DETAILED;// "5";
  /*public*/ static /*final*/ QString BUILD_REPORT_VERY_DETAILED;// "7";

  /*public*/ static /*final*/ QString ROAD;// Bundle.getMessage("Road"); // the supported message format options
  /*public*/ static /*final*/ QString NUMBER;// Bundle.getMessage("Number");
  /*public*/ static /*final*/ QString TYPE;// Bundle.getMessage("Type");
  /*public*/ static /*final*/ QString MODEL;// Bundle.getMessage("Model");
  /*public*/ static /*final*/ QString LENGTH;// Bundle.getMessage("Length");
  /*public*/ static /*final*/ QString LOAD;// Bundle.getMessage("Load");
  /*public*/ static /*final*/ QString COLOR;// Bundle.getMessage("Color");
  /*public*/ static /*final*/ QString TRACK;// Bundle.getMessage("Track");
  /*public*/ static /*final*/ QString DESTINATION;// Bundle.getMessage("Destination");
  /*public*/ static /*final*/ QString DEST_TRACK;// Bundle.getMessage("Dest&Track");
  /*public*/ static /*final*/ QString FINAL_DEST;// Bundle.getMessage("Final_Dest");
  /*public*/ static /*final*/ QString FINAL_DEST_TRACK;// Bundle.getMessage("FD&Track");
  /*public*/ static /*final*/ QString LOCATION;// Bundle.getMessage("Location");
  /*public*/ static /*final*/ QString CONSIST;// Bundle.getMessage("Consist");
  /*public*/ static /*final*/ QString KERNEL;// Bundle.getMessage("Kernel");
  /*public*/ static /*final*/ QString KERNEL_SIZE;// Bundle.getMessage("Kernel_Size");
  /*public*/ static /*final*/ QString OWNER;// Bundle.getMessage("Owner");
  /*public*/ static /*final*/ QString RWE;// Bundle.getMessage("RWE");
  /*public*/ static /*final*/ QString COMMENT;// Bundle.getMessage("Comment");
  /*public*/ static /*final*/ QString DROP_COMMENT;// Bundle.getMessage("SetOut_Msg");
  /*public*/ static /*final*/ QString PICKUP_COMMENT;// Bundle.getMessage("PickUp_Msg");
  /*public*/ static /*final*/ QString HAZARDOUS;// Bundle.getMessage("Hazardous");
  /*public*/ static /*final*/ QString BLANK;// " "; // blank has be a character or a space
  /*public*/ static /*final*/ QString TAB;// Bundle.getMessage("Tab"); // used to tab out in tabular mode
  /*public*/ static /*final*/ QString TAB2;// Bundle.getMessage("Tab2");
  /*public*/ static /*final*/ QString TAB3;// Bundle.getMessage("Tab3");
  /*public*/ static /*final*/ QString BOX;// " [ ] "; // NOI18N

  // these are for the utility printing when using tabs
  /*public*/ static /*final*/ QString NO_ROAD;// "NO_ROAD"; // NOI18N
  /*public*/ static /*final*/ QString NO_NUMBER;// "NO_NUMBER"; // NOI18N
  /*public*/ static /*final*/ QString NO_COLOR;// "NO_COLOR"; // NOI18N

  // truncated manifests
  /*public*/ static /*final*/ QString NO_DESTINATION;// "NO_DESTINATION"; // NOI18N
  /*public*/ static /*final*/ QString NO_DEST_TRACK;// "NO_DEST_TRACK"; // NOI18N
  /*public*/ static /*final*/ QString NO_LOCATION;// "NO_LOCATION"; // NOI18N
  /*public*/ static /*final*/ QString NO_TRACK;// "NO_TRACK"; // NOI18N

  // the supported colors for printed text
  /*public*/ static /*final*/ QString BLACK;// Bundle.getMessage("Black");
  /*public*/ static /*final*/ QString RED;// Bundle.getMessage("Red");
  /*public*/ static /*final*/ QString ORANGE;// Bundle.getMessage("Orange");
  /*public*/ static /*final*/ QString YELLOW;// Bundle.getMessage("Yellow");
  /*public*/ static /*final*/ QString GREEN;// Bundle.getMessage("Green");
  /*public*/ static /*final*/ QString BLUE;// Bundle.getMessage("Blue");
  /*public*/ static /*final*/ QString GRAY;// Bundle.getMessage("Gray");
  /*public*/ static /*final*/ QString PINK;// Bundle.getMessage("Pink");
  /*public*/ static /*final*/ QString CYAN;// Bundle.getMessage("Cyan");
  /*public*/ static /*final*/ QString MAGENTA;// Bundle.getMessage("Magenta");

  // Unit of Length
  /*public*/ static /*final*/ QString FEET;// Bundle.getMessage("Feet");
  /*public*/ static /*final*/ QString METER;// Bundle.getMessage("Meter");
  enum COMPASS
  {
   EAST =  1, // train direction serviced by this location
   WEST =  2,
   NORTH =  4,
   SOUTH =  8
  };
  /*public*/ static /*final*/ QString NONE;// "";
  /*public*/ static void load(QDomElement e);
  /*public*/ static QString getRailroadName();
  /*public*/ static void setRailroadName(QString name);
  /*public*/ static void setComment(QString comment);
  /*public*/ static QString getComment();
  /*public*/ static /*final*/ QString SWITCH_LIST_CSV_PROPERTY_CHANGE;// = "setupSwitchListCSVChange"; //  NOI18N
  /*public*/ static /*final*/ QString MANIFEST_CSV_PROPERTY_CHANGE;// = "setupManifestCSVChange"; //  NOI18N
  /*public*/ static /*final*/ QString REAL_TIME_PROPERTY_CHANGE;// = "setupSwitchListRealTime"; //  NOI18N
  /*public*/ static QDomElement store();
  enum SCALE
  {
   Z_SCALE =  1,
   N_SCALE =  2,
   TT_SCALE =  3,
   HOn3_SCALE =  4,
   OO_SCALE =  5,
   HO_SCALE =  6,
   Sn3_SCALE =  7,
   S_SCALE =  8,
   On3_SCALE =  9,
   O_SCALE =  10,
   G_SCALE =  11 // NMRA #1
  };
  /*public*/ static void setDoc(QDomDocument doc);
  PropertyChangeSupport* pcs;
  static Setup* instance();

 signals:

 public slots:

 private:
  static Setup* _instance;

  // scale ratios from NMRA
  /*private*/ static /*final*/ int Z_RATIO;// 220;
  /*private*/ static /*final*/ int N_RATIO;// 160;
  /*private*/ static /*final*/ int TT_RATIO;// 120;
  /*private*/ static /*final*/ int OO_RATIO;// 76; // actual ratio 76.2
  /*private*/ static /*final*/ int HO_RATIO;// 87;
  /*private*/ static /*final*/ int S_RATIO;// 64;
  /*private*/ static /*final*/ int O_RATIO;// 48;
  /*private*/ static /*final*/ int G_RATIO;// 32; // NMRA #1

  // initial weight in milli ounces from NMRA
  /*private*/ static /*final*/ int Z_INITIAL_WEIGHT;// 364; // not specified by NMRA
  /*private*/ static /*final*/ int N_INITIAL_WEIGHT;// 500;
  /*private*/ static /*final*/ int TT_INITIAL_WEIGHT;// 750;
  /*private*/ static /*final*/ int HOn3_INITIAL_WEIGHT;// 750;
  /*private*/ static /*final*/ int OO_INITIAL_WEIGHT;// 750; // not specified by NMRA
  /*private*/ static /*final*/ int HO_INITIAL_WEIGHT;// 1000;
  /*private*/ static /*final*/ int Sn3_INITIAL_WEIGHT;// 1000;
  /*private*/ static /*final*/ int S_INITIAL_WEIGHT;// 2000;
  /*private*/ static /*final*/ int On3_INITIAL_WEIGHT;// 1500;
  /*private*/ static /*final*/ int O_INITIAL_WEIGHT;// 5000;
  /*private*/ static /*final*/ int G_INITIAL_WEIGHT;// 10000; // not specified by NMRA

  // additional weight in milli ounces from NMRA
  /*private*/ static /*final*/ int Z_ADD_WEIGHT;// 100; // not specified by NMRA
  /*private*/ static /*final*/ int N_ADD_WEIGHT;// 150;
  /*private*/ static /*final*/ int TT_ADD_WEIGHT;// 375;
  /*private*/ static /*final*/ int HOn3_ADD_WEIGHT;// 375;
  /*private*/ static /*final*/ int OO_ADD_WEIGHT;// 500; // not specified by NMRA
  /*private*/ static /*final*/ int HO_ADD_WEIGHT;// 500;
  /*private*/ static /*final*/ int Sn3_ADD_WEIGHT;// 500;
  /*private*/ static /*final*/ int S_ADD_WEIGHT;// 500;
  /*private*/ static /*final*/ int On3_ADD_WEIGHT;// 750;
  /*private*/ static /*final*/ int O_ADD_WEIGHT;// 1000;
  /*private*/ static /*final*/ int G_ADD_WEIGHT;// 2000; // not specified by NMRA

  // actual weight to tons conversion ratios (based on 40' boxcar at ~80 tons)
  /*private*/ static /*final*/ int Z_RATIO_TONS;// 130;
  /*private*/ static /*final*/ int N_RATIO_TONS;// 80;
  /*private*/ static /*final*/ int TT_RATIO_TONS;// 36;
  /*private*/ static /*final*/ int HOn3_RATIO_TONS;// 20;
  /*private*/ static /*final*/ int OO_RATIO_TONS;// 20;
  /*private*/ static /*final*/ int HO_RATIO_TONS;// 20; // 20 tons per ounce
  /*private*/ static /*final*/ int Sn3_RATIO_TONS;// 16;
  /*private*/ static /*final*/ int S_RATIO_TONS;// 14;
  /*private*/ static /*final*/ int On3_RATIO_TONS;// 8;
  /*private*/ static /*final*/ int O_RATIO_TONS;// 5;
  /*private*/ static /*final*/ int G_RATIO_TONS;// 2;

  /*private*/ static QDomDocument doc;


  /*private*/ static /*final*/ QStringList carAttributes;// {ROAD, NUMBER, TYPE, LENGTH, LOAD, HAZARDOUS, COLOR, KERNEL, KERNEL_SIZE, OWNER,
 //         TRACK, LOCATION, DESTINATION, DEST_TRACK, FINAL_DEST, FINAL_DEST_TRACK, COMMENT, DROP_COMMENT,
 //         PICKUP_COMMENT, RWE};
  /*private*/ static /*final*/ QStringList engineAttributes;// {ROAD, NUMBER, TYPE, MODEL, LENGTH, CONSIST, OWNER, TRACK,
 //         LOCATION, DESTINATION, COMMENT};

  /*private*/ static int scale;// HO_SCALE; // Default scale
  /*private*/ static int ratio;// HO_RATIO;
  /*private*/ static int ratioTons;// HO_RATIO_TONS;
  /*private*/ static int initWeight;// HO_INITIAL_WEIGHT;
  /*private*/ static int addWeight;// HO_ADD_WEIGHT;
  /*private*/ static QString railroadName;// NONE;
  /*private*/ static int traindir;// EAST + WEST + NORTH + SOUTH;
  /*private*/ static int maxTrainLength;// 1000; // maximum train length
  /*private*/ static int maxEngineSize;// 6; // maximum number of engines that can be assigned to a train
  /*private*/ static int horsePowerPerTon;// 1; // Horsepower per ton
  /*private*/ static int carMoves;// 5; // default number of moves when creating a route
  /*private*/ static QString carTypes;// DESCRIPTIVE;
  /*private*/ static QString ownerName;// NONE;
  /*private*/ static QString fontName;// MONOSPACED;
  /*private*/ static int manifestFontSize;// 10;
  /*private*/ static int buildReportFontSize;// 10;
  /*private*/ static QString manifestOrientation;// PORTRAIT;
  /*private*/ static QString switchListOrientation;// PORTRAIT;
  /*private*/ static QString pickupColor;// BLACK;
  /*private*/ static QString dropColor;// BLACK;
  /*private*/ static QString localColor;// BLACK;
  /*private*/ static  QStringList pickupEngineMessageFormat;// {ROAD, NUMBER, BLANK, MODEL, BLANK, BLANK, LOCATION, COMMENT};
  /*private*/ static  QStringList dropEngineMessageFormat;// {ROAD, NUMBER, BLANK, MODEL, BLANK, BLANK, DESTINATION, COMMENT};
  /*private*/ static  QStringList pickupManifestMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS, LOCATION,
 //         COMMENT, PICKUP_COMMENT};
  /*private*/ static  QStringList dropManifestMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS, DESTINATION,
 //         COMMENT, DROP_COMMENT};
  /*private*/ static  QStringList localManifestMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS, LOCATION,
 //         DESTINATION, COMMENT};
  /*private*/ static  QStringList pickupSwitchListMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS,
 //         LOCATION, COMMENT, PICKUP_COMMENT};
  /*private*/ static  QStringList dropSwitchListMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS,
 //         DESTINATION, COMMENT, DROP_COMMENT};
  /*private*/ static  QStringList localSwitchListMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, LOAD, HAZARDOUS,
 //         LOCATION, DESTINATION, COMMENT};
  /*private*/ static  QStringList missingCarMessageFormat;// {ROAD, NUMBER, TYPE, LENGTH, COLOR, COMMENT};
  /*private*/ static QString pickupEnginePrefix;// BOX + Bundle.getMessage("PickUpPrefix");
  /*private*/ static QString dropEnginePrefix;// BOX + Bundle.getMessage("SetOutPrefix");
  /*private*/ static QString pickupCarPrefix;// BOX + Bundle.getMessage("PickUpPrefix");
  /*private*/ static QString dropCarPrefix;// BOX + Bundle.getMessage("SetOutPrefix");
  /*private*/ static QString localPrefix;// BOX + Bundle.getMessage("LocalCarPrefix");
  /*private*/ static QString switchListPickupCarPrefix;// BOX + Bundle.getMessage("PickUpPrefix");
  /*private*/ static QString switchListDropCarPrefix;// BOX + Bundle.getMessage("SetOutPrefix");
  /*private*/ static QString switchListLocalPrefix;// BOX + Bundle.getMessage("LocalCarPrefix");
  /*private*/ static QString miaComment;// Bundle.getMessage("misplacedCars");
  /*private*/ static QString hazardousMsg;// "(" + Bundle.getMessage("Hazardous") + ")";
  /*private*/ static QString logoURL;// NONE;
  /*private*/ static QString panelName;// "Panel"; // NOI18N
  /*private*/ static QString buildReportLevel;// BUILD_REPORT_VERY_DETAILED;
  /*private*/ static QString routerBuildReportLevel;// BUILD_REPORT_NORMAL;
  /*private*/ static int carSwitchTime;// 3; // how long it takes to move a car in minutes
  /*private*/ static int travelTime;// 4; // how long it takes a train to move from one location to another in minutes
  /*private*/ static QString yearModeled;// NONE; // year being modeled
  /*private*/ static QString lengthUnit;// FEET;
  /*private*/ static QString iconNorthColor;// NONE;
  /*private*/ static QString iconSouthColor;// NONE;
  /*private*/ static QString iconEastColor;// NONE;
  /*private*/ static QString iconWestColor;// NONE;
  /*private*/ static QString iconLocalColor;// NONE;
  /*private*/ static QString iconTerminateColor;// NONE;

  /*private*/ static bool tab;// false; // when true, tab out manifest and switch lists
  /*private*/ static int tab1CharLength;// Control.max_len_string_attibute;
  /*private*/ static int tab2CharLength;// 6; // arbitrary lengths
  /*private*/ static int tab3CharLength;// 8;

  /*private*/ static QString manifestFormat;// STANDARD_FORMAT;
  /*private*/ static bool manifestEditorEnabled;// false; // when true use text editor to view build report
  /*private*/ static bool switchListSameManifest;// true; // when true switch list format is the same as the manifest
  /*private*/ static bool manifestTruncated;// false; // when true, manifest is truncated if switch list is available
  /*private*/ static bool manifestDepartureTime;// false; // when true, manifest shows train's departure time
  /*private*/ static bool switchListRouteComment;// true; // when true, switch list have route location comments
  /*private*/ static bool trackSummary;// true; // when true, print switch list track summary

  /*private*/ static bool switchListRealTime;// true; // when true switch list only show work for built trains
  /*private*/ static bool switchListAllTrains;// true; // when true show all trains that visit the location
  /*private*/ static QString switchListPageFormat;// PAGE_NORMAL; // how switch lists pages are printed

  /*private*/ static bool buildReportEditorEnabled;// false; // when true use text editor to view build report
  /*private*/ static bool buildReportIndentEnabled;// true; // when true use text editor to view build report
  /*private*/ static bool buildReportAlwaysPreviewEnabled;// false; // when true use text editor to view build report

  /*private*/ static bool enableTrainIconXY;// true;
  /*private*/ static bool appendTrainIcon;// false; // when true, append engine number to train name
  /*private*/ static QString setupComment;// NONE;
  /*private*/ static bool mainMenuEnabled;//;// false; // when true add operations menu to main menu bar
   /*private*/ static bool closeWindowOnSave ;// false; // when true, close window when save button is activated
  /*private*/ static bool autoSave;// true; // when true, automatically save files if modified
  /*private*/ static bool autoBackup;// true; // when true, automatically backup files
  /*private*/ static bool enableValue;// false; // when true show value fields for rolling stock
  /*private*/ static QString labelValue;// tr("Value");
  /*private*/ static bool enableRfid;// false; // when true show RFID fields for rolling stock
  /*private*/ static QString labelRfid;// tr("RFID");

  /*private*/ static bool carRoutingEnabled;// true; // when true enable car routing
  /*private*/ static bool carRoutingYards;// true; // when true enable car routing via yard tracks
  /*private*/ static bool carRoutingStaging;// false; // when true staging tracks can be used for car routing
  /*private*/ static bool forwardToYardEnabled;// true; // when true forward car to yard if track is full
  /*private*/ static bool onlyActiveTrains;// false; // when true only active trains are used for routing
  /*private*/ static bool checkCarDestination;// false; // when true check car's track for valid destination

  /*private*/ static bool carLogger;// false; // when true car logger is enabled
  /*private*/ static bool engineLogger;// false; // when true engine logger is enabled
  /*private*/ static bool trainLogger;// false; // when true train logger is enabled

  /*private*/ static bool aggressiveBuild;// false; // when true subtract car length from track reserve length
  /*private*/ static int numberPasses;// 2; // the number of passes in train builder
  /*private*/ static bool allowLocalInterchangeMoves;// false; // when true local C/I to C/I moves are allowed
  /*private*/ static bool allowLocalYardMoves;// false; // when true local yard to yard moves are allowed
  /*private*/ static bool allowLocalSpurMoves;// false; // when true local spur to spur moves are allowed

  /*private*/ static bool trainIntoStagingCheck;// true; // staging track must accept train's rolling stock types and roads
  /*private*/ static bool trackImmediatelyAvail;// false; // when true staging track is available for other trains
  /*private*/ static bool allowCarsReturnStaging;// false; // allow cars on a turn to return to staging if necessary (prevent build failure)
  /*private*/ static bool promptFromStaging;// false; // prompt user to specify which departure staging track to use
  /*private*/ static bool promptToStaging;// false; // prompt user to specify which arrival staging track to use

  /*private*/ static bool generateCsvManifest;// false; // when true generate csv manifest
  /*private*/ static bool generateCsvSwitchList;// false; // when true generate csv switch list
  /*private*/ static bool enableVsdPhysicalLocations;// false;

  /*private*/ static bool printLocationComments;// false; // when true print  location comments on the manifest
  /*private*/ static bool printRouteComments;// false; // when true print  route comments on the manifest
  /*private*/ static bool printLoadsAndEmpties;// false; // when true print  Loads and Empties on the manifest
  /*private*/ static bool printTimetableName;// false; // when true print  timetable name on manifests and switch lists
  /*private*/ static bool use12hrFormat;// false; // when true use 12hr rather than 24hr format
  /*private*/ static bool printValid;// true; // when true print  out the valid time and date
  /*private*/ static bool sortByTrack;// false; // when true manifest work is sorted by track names
  /*private*/ static bool printHeaders;// false; // when true add headers to manifest and switch lists

  /*private*/ static bool printCabooseLoad;// false; // when true print  caboose load
  /*private*/ static bool printPassengerLoad;// false; // when true print  passenger car load

 private:
  /*private*/ static void storeXmlMessageFormat(QDomElement values, QString prefix, QStringList messageFormat);
  //static PropertyChangeSupport* pcs;// = new PropertyChangeSupport("Setup");
  /*private*/ static void stringToKeyConversion(QStringList strings);
  /*private*/ static void replaceOldFormat(QStringList format);
  /*private*/ static void keyToStringConversion(QStringList keys);
  /*private*/  static /*final*/ QStringList attributtes;// = {"Road", "Number", "Type", "Model", "Length", "Load", "Color",
//          "Track", "Destination", "Dest&Track", "Final_Dest", "FD&Track", "Location", "Consist", "Kernel", "Kernel_Size", "Owner",
//          "RWE", "Comment", "SetOut_Msg", "PickUp_Msg", "Hazardous", "Tab"};
///*private*/  /*static final*/ QStringList trAttr;
 protected:
  /*protected*/ static void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

  friend class OperationsSetupXml;
 };
}
#endif // SETUP_H
