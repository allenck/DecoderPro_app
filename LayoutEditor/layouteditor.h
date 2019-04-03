#ifndef LAYOUTEDITOR_H
#define LAYOUTEDITOR_H

#include "editor.h"
//#include <QMainWindow>
#include <QButtonGroup>
#include <QGraphicsView>
//#include "editscene.h"
#include "layoutturnout.h"
#include "levelxing.h"
#include "positionable.h"
#include "layouteditorauxtools.h"
#include "layoutblockmanager.h"
#include "blockmanager.h"
#include "memoryicon.h"
#include "loconetsystemconnectionmemo.h"
#include "sensoricon.h"
#include "multiiconeditor.h"
#include "locoicon.h"
#include "reportericon.h"
#include "layoutslip.h"
#include <QFormLayout>
#include "Roster/rosterentryselectorpanel.h"
#include "fileutil.h"
#include "liblayouteditor_global.h"
#include "signalheadicon.h"
#include "paneleditor.h"
#include "colorutil.h"
#include "component.h"
#include "jmribeancombobox.h"
#include <QPen>

namespace Ui {
class LayoutEditor;
}

class LayoutEditorChecks;
class LayoutTrackEditors;
class LayoutTrackDrawingOptions;
class StoreXmlUserAction;
class TurnoutSelection;
class LayoutEditorFindItems;
class LayoutTurntable;
class ConnectivityUtil;
class MultiSensorIconFrame;
class MultiSensorIcon;
class InternalSensorManager;
class LnSensorManager;
class LayoutSlip;
class LayoutTurnout;
class TrackSegment;
class PositionablePoint;
class LevelXing;
class Positionable;
class PositionableLabel;
class LayoutEditorAuxTools;
class LayoutBlockManager;
class SignalHeadIcon;
class SignalMastIcon;
class AnalogClock2Display;
class JmriJFrame;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditor : public PanelEditor
{
 Q_OBJECT
    friend class LayoutTurnout;
    friend class LayoutEditorAuxTools;
    friend class LevelXing;
    friend class LayoutBlock;
public:
 explicit LayoutEditor(QString name = "My Layout", QWidget *parent = 0);
//    LayoutEditor(LocoNetSystemConnectionMemo* memo, QString name = "My Layout", bool bTest = false, QWidget *parent=0);
 ~LayoutEditor();
    LayoutEditor(const LayoutEditor&) : PanelEditor() {}
    /*public*/ void newPanelDefaults();

    // connection types
    static const  int NONE = 0;
    static const  int POS_POINT = 1;
    static const  int TURNOUT_A = 2;  // throat for RH, LH, and WYE turnouts
    static const  int TURNOUT_B = 3;  // continuing route for RH or LH turnouts
    static const  int TURNOUT_C = 4;  // diverging route for RH or LH turnouts
    static const  int TURNOUT_D = 5;  // double-crossover or single crossover only
    static const  int LEVEL_XING_A = 6;
    static const  int LEVEL_XING_B = 7;
    static const  int LEVEL_XING_C = 8;
    static const  int LEVEL_XING_D = 9;
    static const  int TRACK = 10;
    static const  int TURNOUT_CENTER = 11; // non-connection points should be last
    static const  int LEVEL_XING_CENTER = 12;
    static const  int TURNTABLE_CENTER = 13;
    static const  int LAYOUT_POS_LABEL = 14;
    static const  int LAYOUT_POS_JCOMP = 15;
    static const  int MULTI_SENSOR = 16;
    static const  int MARKER = 17;
    static const  int TRACK_CIRCLE_CENTRE = 18;
    static const  int SLIP_CENTER = 20; //
    static const  int SLIP_A = 21; // offset for slip connection points
    static const  int SLIP_B = 22; // offset for slip connection points
    static const  int SLIP_C = 23; // offset for slip connection points
    static const  int SLIP_D = 24; // offset for slip connection points
    static const  int TURNTABLE_RAY_OFFSET = 50; // offset for turntable connection points
    const /*public*/ static int BKG       = 1;
    const /*public*/ static int TEMP      = 2;
    const /*public*/ static int ICONS     = 3;
    const /*public*/ static int LABELS    = 4;
    const /*public*/ static int MEMORIES  = 5;
    const /*public*/ static int REPORTERS = 5;
    const /*public*/ static int SECURITY  = 6;
    const /*public*/ static int TURNOUTS  = 7;
    const /*public*/ static int LIGHTS    = 8;
    const /*public*/ static int SIGNALS   = 9;
    const /*public*/ static int SENSORS   = 10;
    const /*public*/ static int CLOCK     = 10;
    const /*public*/ static int MARKERS   = 10;
    const /*public*/ static int NUM_LEVELS= 10;

    const /*public*/ static int SCROLL_NONE       = 0;
    const /*public*/ static int SCROLL_BOTH       = 1;
    const /*public*/ static int SCROLL_HORIZONTAL = 2;
    const /*public*/ static int SCROLL_VERTICAL   = 3;
    const /*public*/ static int OPTION_POSITION = 1;
    const /*public*/ static int OPTION_CONTROLS = 2;
    const /*public*/ static int OPTION_HIDDEN = 3;
    const /*public*/ static int OPTION_TOOLTIP= 4;


    /*public*/ void addAnchor();
    /*public*/ void addEndBumper();
    /*public*/ void addTrackSegment();
    /*public*/ void addLevelXing();
    /*public*/ void addLayoutSlip(int type);
    /*public*/ void addLayoutTurnout(int type);
    LayoutTurnout* addLayoutTurnout(QString name, int type, double rot, QPointF currentPoint);
    /*public*/ bool validatePhysicalTurnout(QString inTurnoutName, QWidget* openPane = 0);
    // Lists of items that describe the Layout, and allow it to be drawn
    //		Each of the items must be saved to disk over sessions
    ///*public*/ QVector<LayoutTurnout*>* turnoutList;// = new QVector<LayoutTurnout>();  // LayoutTurnouts
    /*public*/ QList<LayoutTrack*>* layoutTrackList;// = new QVector<TrackSegment>();  // TrackSegment list
    ///*public*/ QVector<PositionablePoint*>* pointList;// = new QVector<PositionablePoint>();  // PositionablePoint list
    /*public*/ QVector<SensorIcon*>* sensorImage;// = new QVector<SensorIcon*>();  // sensor images

    ///*public*/ QVector<LevelXing*>* xingList;// = new QVector<LevelXing>();  // LevelXing list
    ///*public*/ QVector<LayoutSlip*>* slipList;// = new QVector<LayoutSlip>();  // Layout slip list
    /*public*/ QVector<LayoutTurntable*>* turntableList;// = new QVector<LayoutTurntable>(); // Turntable list

   ///*public*/ PositionablePoint* findPositionablePointByName(QString name);
    ///*public*/ PositionablePoint* findPositionablePointAtTrackSegments(TrackSegment* tr1, TrackSegment* tr2);
    /*public*/ TrackSegment* findTrackSegmentByName(QString name);
    /**
     * Return a layout block with the entered name, creating a new one if needed.
     *   Note that the entered name becomes the user name of the LayoutBlock, and
     *		a system name is automatically created by LayoutBlockManager if needed.
     */
    /*public*/ LayoutBlock* provideLayoutBlock(QString s);
    /**
    * Validates that the supplied occupancy sensor name corresponds to an existing sensor
    *   and is unique among all blocks.  If valid, returns true and sets the block sensor
    *   name in the block.  Else returns false, and does nothing to the block.
    */
    /*public*/ bool validateSensor(QString sensorName, LayoutBlock* blk, Component *openFrame);
//    /*public*/ LevelXing* findLevelXingByName(QString name) ;
//    /*public*/ LayoutSlip* findLayoutSlipByName(QString name);
//    /*public*/ LayoutTurnout* findLayoutTurnoutByName(QString name);
//    /*public*/ LayoutTurnout* findLayoutTurnoutByTurnoutName(QString name);
    /*public*/ QList <Positionable*> getContents();
    // accessor routines for turnout size parameters
    /*public*/ void setTurnoutBX(double bx);
    /*public*/ double getTurnoutBX();
    /*public*/ void setTurnoutCX(double cx);
    /*public*/ double getTurnoutCX();
    /*public*/ void setTurnoutWid(double wid);
    /*public*/ double getTurnoutWid();
    /*public*/ void setXOverLong(double lg) ;
    /*public*/ double getXOverLong();
    /*public*/ void setXOverHWid(double hwid);
    /*public*/ double getXOverHWid();
    /*public*/ void setXOverShort(double sh);
    /*public*/ double getXOverShort();
    // reset turnout sizes to program defaults
    /*public*/ double getXScale();
    /*public*/ double getYScale();
    /*public*/ QColor getDefaultBackgroundColor();
    /*public*/ QString getDefaultTrackColor();
    /*public*/ QString getDefaultOccupiedTrackColor();
    /*public*/ QString getDefaultAlternativeTrackColor();
    /*public*/ QString getDefaultTextColor();
    /*public*/ QString getTurnoutCircleColor();
    /*public*/ int getTurnoutCircleSize();
    QT_DEPRECATED/*public*/ bool getTurnoutDrawUnselectedLeg();
    /*public*/ bool isTurnoutDrawUnselectedLeg();

    /* Return a layout block with the given name if one exists.
    * Registers this LayoutEditor with the layout block.
    * This method is designed to be used when a panel is loaded. The calling
    *		method must handle whether the use count should be incremented.
    */
    /*public*/ LayoutBlock* getLayoutBlock(QString blockID);
    LayoutBlockManager* layoutBlockManager;
    BlockManager* blockManger;
    QT_DEPRECATED /*public*/ QObject* findObjectByTypeAndName(int type,QString name);
    /*public*/ LayoutBlock* getAffectedBlock(QObject* o, int type);
    /**
    * Returns an array list of track segments matching the block name.
    */
    /*public*/ QVector<TrackSegment*>* findTrackSegmentByBlock(QString name);
    /*public*/ QVector<MemoryIcon*>* memoryLabelList;// = new QVector<MemoryIcon*>(); // Memory Label List
    /*public*/ /*transient*/ QVector<BlockContentsIcon*>* blockContentsLabelList;// = new ArrayList<>(); //BlockContentsIcon Label List

    void repaint();
    /**
    *  Control whether target panel items are editable.
    *  Does this by invoke the {@link Positionable#setEditable(bool)} function of
    *  each item on the target panel. This also controls the relevant pop-up menu items
    *  (which are the primary way that items are edited).
    * @param state true for editable.
    */
    /*public*/ void setAllEditable(bool state);
    /*public*/ bool isEditable();
    /**
    *  Control whether target panel items are controlling layout items.
    *  Does this by invoke the {@link Positionable#setControlling} function of
    *  each item on the target panel. This also controls the relevant pop-up menu items.
    * @param state true for controlling.
    */
    /*public*/ void setTurnoutAnimation(bool state) ;
    /*public*/ bool isAnimating();
    /*public*/ int getLayoutWidth() ;
    /*public*/ int getLayoutHeight() ;
    /*public*/ int getWindowWidth() ;
    /*public*/ int getWindowHeight() ;
    /*public*/ int getUpperLeftX() ;
    /*public*/ int getUpperLeftY() ;
    /*public*/ bool getScroll();
    /*public*/ /*const*/ int getAnchorX();
    /*public*/ /*const*/ int getAnchorY();
//    /*public*/ bool allPositionable();
    /*public*/ bool allControlling() ;
    /*public*/ bool setShowAlignmentMenu(QMenu* popup);
    /*public*/ QPointF getEndCoords(QObject* o, int type);
    QGraphicsView* panel();
    /**
    * Add a label to the Draw Panel
    */
    void addLabel();
    void drawLabelImages(EditScene* g2);
//    /*public*/ bool removeFromContents(Positionable* l);
    /*public*/ void putItem(Positionable *l);
//    /*public*/ void super_putItem(Positionable* l);
    EditScene* getScene() {return editScene;}
    /*public*/ void putSensor(SensorIcon* l);
    //void setDirty() { bDirty = true;}
    void redrawPanel() { paintTargetPanel(editScene);}
    /**
    * Display the X & Y coordinates of the Positionable item and provide a
    * dialog memu item to edit them.
    */
//    /*public*/ bool setShowCoordinatesMenu(Positionable* p, QMenu* popup);
//    /*public*/ void displayLevelChange(Positionable* l);
//    /*public*/ void setDisplayLevelMenu(Positionable* p, QMenu* popup);
//    /*public*/ void setPositionableMenu(Positionable* p, QMenu* popup);
//    /*public*/ void setShowCoordinates(bool state);
//    /*public*/ bool showCoordinates();
    /*public*/ QVector<SensorIcon*>* sensorList;// = new QVector<SensorIcon*>();  // Sensor Icons
    /*public*/ void setRemoveMenu(Positionable* p, QMenu* popup);
    /*public*/ QVector<LocoIcon*>* markerImage;// = new QVector<LocoIcon*>(); // marker images
    /*public*/ void setAllPositionable(bool state);
    /*public*/ void setLayoutDimensions(int windowW, int windowH, int x, int y, int panelW, int panelH, bool merge = false);

//    /*public*/ void superPutLocoIcon(LocoIcon* l, QString name);
    /**
    * Add a memory label to the Draw Panel
    */
    void addMemory() ;
    MemoryIcon* addMemory(QString text);

    /**
    * Add an icon to the target
    */
    void addIcon();
//    /*public*/ void setAllControlling(bool state);
    /**
    * Does global flag sets Positionable and Control for individual items
    */
    /*public*/ void setGlobalSetsLocalFlag(bool set);
    /*public*/ void setHiddenMenu(Positionable* p, QMenu* popup);
    /**
     * Add a Reporter Icon to the panel
     */
    void addReporter(QString textReporter,int xx,int yy);
//    /*public*/ PositionableLabel* setUpBackground(QString name);
    QT_DEPRECATED void setDefaultTextColor(QString sColor);
    void setDefaultTextColor(QColor sColor);
    /*public*/ void setDefaultBackgroundColor(QString color);
    /*public*/ QString getLayoutName();
    /*public*/ bool getShowHelpBar();
    /*public*/ void setLayoutName(QString name);
    bool getDrawGrid() {return drawGrid;}
    void setDrawGrid(bool state);
    bool getSnapOnAdd(){return snapToGridOnAdd;}
    bool getSnapOnMove(){return snapToGridOnMove;}
    bool getAntialiasingOn(){return antialiasingOn;}
    bool getTurnoutCircles(){return turnoutCirclesWithoutEditMode;}
    bool getTooltipsNotEdit() {return tooltipsWithoutEditMode;}
/*public*/ bool getTooltipsInEdit() {return tooltipsInEditMode;}
    float getMainlineTrackWidth(){return mainlineTrackWidth;}
    float getSideTrackWidth(){return sidelineTrackWidth;}
    bool getAutoBlockAssignment(){return autoAssignBlocks;}
    QColor getBackgroundColor();
    /*public*/ void loadFailed();
    /*public*/ NamedIcon* loadFailed(QString msg, QString url);
//    int getTurnoutType(QString name);
//    /*public*/ PositionablePoint* findPositionablePointByEastBoundSignal(QString signalName);
//    /*public*/ PositionablePoint* findPositionablePointByWestBoundSignal(QString signalName);
//    /*public*/ PositionablePoint* findPositionablePointByEastBoundSignalMast(QString signalMastName);
//    /*public*/ PositionablePoint* findPositionablePointByWestBoundSignalMast(QString signalMastName);
//    /*public*/ LayoutTurnout* findLayoutTurnoutBySignalMast(QString signalMastName);
//    /*public*/ LayoutTurnout* findLayoutTurnoutBySensor(QString sensorName);
//    /*public*/ LevelXing* findLevelXingBySignalMast(QString signalMastName);
//    /*public*/ LevelXing* findLevelXingBySensor(QString sensorName);
//    /*public*/ LayoutSlip* findLayoutSlipBySignalMast(QString signalMastName);
//    /*public*/ LayoutSlip* findLayoutSlipBySensor(QString sensorName);
//    /*public*/ PositionablePoint* findPositionablePointByEastBoundSensor(QString sensorName);
//    /*public*/ PositionablePoint* findPositionablePointByWestBoundSensor(QString sensorName);
    void addSignalHead();
    /*public*/ void putSignal(SignalHeadIcon* l);
    SignalHead* getSignalHead(QString name) ;
    void addSignalMast() ;
    /*public*/ void putSignalMast(SignalMastIcon* l) ;
    SignalMast* getSignalMast(QString name);
    /*public*/ MultiIconEditor* signalIconEditor;// = nullptr;
    /*public*/ ConnectivityUtil* getConnectivityUtil();
    /*public*/ LayoutEditorTools* getLETools();
    /*public*/ LayoutEditorAuxTools* getLEAuxTools();
    /*public*/ LayoutTrackEditors* getLayoutTrackEditors();
    /*public*/ LayoutEditorChecks* getLEChecks();


    /*public*/ void addToPopUpMenu(NamedBean* nb, QMenu* item, int menu);
    /*public*/ void addMultiSensor(MultiSensorIcon* l);
    /*public*/ void makeBackupFile(QString name);
    /*public*/ void setSize(int w, int h);
    /*public*/ MultiIconEditor* sensorIconEditor;// = nullptr;
    /*public*/ LocoIcon* addLocoIcon (QString name);
    /*public*/ void putLocoIcon(LocoIcon* l, QString name);
    /*public*/ void setCurrentPositionAndSize();
    /*public*/ void setDirectTurnoutControl(bool boo);
    /*public*/ bool getDirectTurnoutControl();
    /*public*/ void setMainlineTrackWidth(int w);
    /*public*/ void setSideTrackWidth(int w);
    QT_DEPRECATED/*public*/ void setTurnoutCircleColor(QString color);
    /*public*/ void setTurnoutCircleColor(QColor color);
    /*public*/ void setTurnoutCircleSize(int size);
    /*public*/ void setTurnoutDrawUnselectedLeg(bool state);
    /*public*/ QVector<AnalogClock2Display*>* clocks;// = new QVector<AnalogClock2Display>();  // fast clocks
    /*public*/ QVector<SignalHeadIcon*>* signalHeadImage;// = new QVector<SignalHeadIcon>();  // signal head images
    /*public*/ QVector<SignalMastIcon*>* signalMastImage;// = new QVector<SignalMastIcon>();  // signal mast images
    /*public*/ QVector<PositionableLabel*>* _labelImage;// = new QVector<PositionableLabel*>(); // layout positionable label images
    /*public*/ QVector<PositionableLabel*>* backgroundImage;// = new QVector<PositionableLabel*>();  // background images
    /*public*/ /*transient*/ QList<PositionableLabel*>* labelImage;// = new ArrayList<>();         //positionable label images
    /*public*/ void setXScale(double xSc) ;
    /*public*/ void setYScale(double ySc);
    /*public*/ void setTurnoutCircles(bool state);
//    /*public*/ static QColor stringToColor(QString string);
//    /*public*/ static QString colorToString(QColor color);
    /*public*/ void setShowHelpBar(bool state);
    /*public*/ void setSnapOnAdd(bool state);
    /*public*/ void setSnapOnMove(bool state);
    /*public*/ void setAntialiasingOn(bool state);
    /*public*/ void setAutoBlockAssignment(bool boo);
    /*public*/ void setScroll(int state);
    /*public*/ void setConnections();
    /*public*/ LayoutEditorFindItems* finder;// = new LayoutEditorFindItems(this);
    /*public*/ LayoutEditorFindItems* getFinder();
    void setDirty(bool b = true);
    /*public*/ void addTurntable(QPointF pt);
//    /*public*/ QT_DEPRECATED LayoutTurntable* findLayoutTurntableByName(QString name);
//    /*public*/ QMenu* setupTurnoutSubMenu();
    /*public*/ bool containsSignalHead(SignalHead* head) ;
    /*public*/ void removeSignalHead(SignalHead* head);
    /*public*/ QGraphicsEllipseItem* turnoutCircleAt(QPointF inPoint);
    /*public*/ void addBackground();
    QT_DEPRECATED/*public*/ void setDefaultTrackColor(QString color);
    /*public*/ void setDefaultTrackColor(QColor color);
    QT_DEPRECATED/*public*/ void setDefaultOccupiedTrackColor(QString color);
    /*public*/ void setDefaultOccupiedTrackColor(QColor color);
    QT_DEPRECATED/*public*/ void setDefaultAlternativeTrackColor(QString color);
    /*public*/ void setDefaultAlternativeTrackColor(QColor color);
    void setScale(double scaleX, double scaleY);
    /*public*/ QString getClassName();
    /*public*/ void setFilename(QString path);
    /*public*/ LayoutTrackDrawingOptions* getLayoutTrackDrawingOptions();
    /*public*/ void setLayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo);
    /*public*/ static void setupComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox, bool inValidateMode, bool inEnable);
    /*public*/ static void setupComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank);
    /*public*/ QRectF unionToPanelBounds(/*@Nonnull*/ QRectF bounds);
    /*public*/ QRectF getPanelBounds();
    /*public*/ bool highlightBlock(/*@Nullable*/ Block* inBlock);
    /*public*/ void setPanelBounds(QRectF newBounds);
    /*public*/ double setZoom(double zoomFactor);
    /*public*/ double getZoom();
    ///*public*/ static QPointF zeroPoint2D();
    /*public*/ QVector<SignalHeadIcon*>* signalList;// = new QVector<SignalHeadIcon*>();  // Signal Head Icons
    /*public*/ QVector<SignalMastIcon*>* signalMastList;// = new QVector<SignalMastIcon*>();  // Signal Head Icons
    /*public*/ QVector<MultiSensorIcon*>* multiSensors; // = new QVector<MultiSensorIcon*>(); // MultiSensor Icons
    /*public*/ void dispose();
    /*public*/ QList<PositionablePoint *> getPositionablePoints();
    /*public*/ QList<LayoutSlip *> getLayoutSlips();
    /*public*/ QList<TrackSegment *> getTrackSegments();
    /*public*/ QList<LayoutTurnout *> getLayoutTurnouts();
    /*public*/ QList<LayoutTurntable *> getLayoutTurntables();
    /*public*/ QList<LevelXing *> getLevelXings();
    /*public*/ QList<LayoutTrack *> *getLayoutTracks();
    /*public*/ QList<LayoutTurnout *> getLayoutTurnoutsAndSlips();
    /*public*/ bool removeFromContents(Positionable* l);
    /*public*/ static QPointF getCoords(/*@Nonnull*/ LayoutTrack* layoutTrack, int connectionType);
    /*public*/ QRectF trackEditControlRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ QRectF trackControlCircleRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ static QPointF zeroQPointF();
    /*public*/ void setSelectionRect(/*@Nonnull*/ QRectF selectionRect);
    /*public*/ void addEdgeConnector() ;
    const QIcon getColourIcon(QColor color);
    /*public*/ void windowClosing(QCloseEvent* event);
    /*public*/ bool isIncludedTurnoutSkipped();
    QT_DEPRECATED /*public*/ bool getOpenDispatcherOnLoad();
    /*public*/ void setOpenDispatcherOnLoad(bool boo);
    /*public*/ void setHighlightSelectedBlock(bool state);


public slots:
    /*public*/ void setIncludedTurnoutSkipped(bool boo);


private:
 Ui::LayoutEditor *ui;
 QButtonGroup* buttonGroup;
 //QGraphicsView* editPanel;
 //EditScene* editScene;
 int xLoc, yLoc;
 //QPointF dLoc;
 double getPaintScale();
 double paintScale;
 /*private*/ /*transient*/ /*final*/ static Logger* log;

 QString layoutName;
 /*private*/ void calcLocation(QPointF pos, int dX, int dY);
 bool bIsEditable;
 /*private*/ /*transient*/ QPointF currentPoint;// = new QPointF(100.0,100.0);
 QObject* selectedObject;
 QObject* prevSelectedObject;
 int selectedPointType;
 /*private*/ void createSelectionGroups();
 bool isDragging;
 // counts used to determine unique internal names
 /*private*/ int numAnchors;// = 0;
 /*private*/ int numEndBumpers;// = 0;
 /*private*/ int numEdgeConnectors;//= 0;
 /*private*/ int numTrackSegments;// = 0;
 /*private*/ int numLevelXings;// = 0;
 /*private*/ int numLayoutSlips;// = 0;
 /*private*/ int numLayoutTurnouts;// = //0;
 /*private*/ int numLayoutTurntables;// = 0;
 StoreXmlUserAction* savePanels;
 //bool bDirty;
 bool isDirty();
 void resetDirty();
 /*private*/ QObject* beginObject;// = nullptr; // begin track segment connection object, NULL if none
 /*private*/ /*transient*/ QPointF beginLocation;// = new QPointF(0.0,0.0);  // location of begin object
 /*private*/ int beginPointType;// = 0;   // connection type within begin connection object
 /*private*/ /*transient*/ QPointF currentLocation;// = new QPointF(0.0,0.0); // current location
 /*private*/ LayoutTrack* foundObject;// = nullptr; // found object, NULL if nothing found
 /*private*/ /*transient*/ QPointF foundLocation;// = new QPointF(0.0,0.0);  // location of found object
 /*private*/ int foundPointType;// = 0;   // connection type within the found object
 /*private*/ TrackSegment* newTrack;// = nullptr;
 /*private*/ void setLink(QObject* fromObject,int fromPointType, QObject* toObject,int toPointType);
 LayoutEditorAuxTools* auxTools;
 /*private*/ double xScale; //1.0;
 /*private*/ double yScale; //1.0;
 // selection variables
 /*private*/ bool selectionActive;// = false;
 /*private*/ double selectionX;// = 0.0;
 /*private*/ double selectionY;// = 0.0;
 /*private*/ double selectionWidth;// = 0.0;
 /*private*/ double selectionHeight;// = 0.0;
 /*private*/ QVector<Positionable*>* _positionableSelection;// = nullptr;

 /*private*/ QVector<LayoutTurnout*>* _turnoutSelection;// = nullptr; //new QVector<LayoutTurnout>();  // LayoutTurnouts
 /*private*/ QVector<LevelXing*>* _xingSelection; //new QVector<LevelXing>();  // LevelXing list
 /*private*/ QVector<LayoutSlip*>* _slipSelection;// = nullptr; //new QVector<LayoutSlip*>();  // LayoutSlip list
 /*private*/ QVector<LayoutTurntable*>* _turntableSelection;// = nullptr; //new ArrayList<LayoutTurntable>(); // Turntable list
 /*private*/ QVector<PositionablePoint*>* _pointSelection; //new QVector<PositionablePoint>();  // PositionablePoint list
 QVector<PositionableLabel*>* _labelSelection; //new QVector<PositionableLabel>();  // PositionableLabel list
/*private*/ QList<LayoutTrack*> getLayoutTracksOfClass(QString type);

  bool isDrawing = false;

 /*private*/ void clearSelectionGroups();
 QWidget* openFrame;
 // turnout size parameters - saved with panel
 /*private*/ double turnoutBX; //turnoutBXDefault;  // RH, LH, WYE
 /*private*/ double turnoutCX; //turnoutCXDefault;
 /*private*/ double turnoutWid; //turnoutWidDefault;
 /*private*/ double xOverLong; //xOverLongDefault;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 /*private*/ double xOverHWid; //xOverHWidDefault;
 /*private*/ double xOverShort; //xOverShortDefault;
 // program default turnout size parameters
 /*private*/ double turnoutBXDefault;// = 20.0;  // RH, LH, WYE
 /*private*/ double turnoutCXDefault;// = 20.0;
 /*private*/ double turnoutWidDefault;// = 10.0;
 /*private*/ double xOverLongDefault;// = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 /*private*/ double xOverHWidDefault;// = 10.0;
 /*private*/ double xOverShortDefault;// = 10.0;
 /*private*/ QColor defaultTrackColor; //QColor::black();
 /*private*/ QColor defaultOccupiedTrackColor; //QColor.black;
 /*private*/ QColor defaultAlternativeTrackColor; //QColor.black;
 /*private*/ QColor defaultBackgroundColor; //QColor::lightGray;
 /*private*/ QColor defaultTextColor; //QColor.black;
 /*private*/ QColor turnoutCircleColor; //defaultTrackColor; //matches earlier versions
 /*private*/ int   turnoutCircleSize; //2;  //matches earlier versions

 /*private*/ void drawXings(EditScene* g2);
// /*private*/ void drawXingAC(EditScene* g2,LevelXing* x);
// /*private*/ void drawXingBD(EditScene* g2,LevelXing* x);
// /*private*/ void drawTurnoutCircles(EditScene* g2);
// /*private*/ void drawSlipCircles(EditScene* g2);
// /*private*/ void drawTurnoutRects(EditScene* g2);
// /*private*/ void drawXingRects(EditScene* g2);
 ///*private*/ void drawSelectionRect(EditScene* editScene);
// /*private*/ void drawPoints(EditScene* g2);
// /*private*/ void drawSlips(QGraphicsScene* g2);
// /*private*/ void drawTurntables(EditScene* g2);
// /*private*/ void drawMemoryRects(EditScene* editScene);

 /*protected*/ void draw(EditScene* g2);
 /*private*/ void drawLayoutTracksHidden(EditScene* g2);
 /*private*/ void drawTrackSegmentsDashed(EditScene* g2);
 /*private*/ void drawLayoutTracksBallast(EditScene* g2);
 /*private*/ void drawLayoutTracksTies(EditScene* g2);
 /*private*/ void drawLayoutTracksRails(EditScene* g2);
 /*private*/ void drawLayoutTracksBlockLines(EditScene* g2);
 /*private*/ void draw1(EditScene* g2,
         bool isMain,
         bool isBlock,
         bool isHidden, LayoutTrack::ITEMTYPE type);
 /*private*/ void draw1(EditScene* g2,
         bool isMain,
         bool isBlock, LayoutTrack::ITEMTYPE type);
 /*private*/ void draw1(EditScene* g2, bool isMain, LayoutTrack::ITEMTYPE type);
 /*private*/ void draw1(EditScene* g2,
         bool isMain,
         bool isBlock,
         bool isHidden,
         bool isDashed, LayoutTrack::ITEMTYPE itemType);
 /*private*/ void drawPositionablePoints(EditScene* g2, bool isMain);
 /*private*/ void draw2(EditScene* g2, bool isMain, float railDisplacement);
 /*private*/ void draw2(EditScene* g2, bool isMain, float railDisplacement, bool isDashed);
 /*private*/ void drawDecorations(EditScene* g2);
 /*private*/ void drawTrackSegmentInProgress(EditScene* g2);
 /*private*/ void drawLayoutTrackEditControls(EditScene* g2);
 /*private*/ void drawTurnoutControls(EditScene* g2);
 /*private*/ QRectF getSelectionRect();
 /*private*/ void drawSelectionRect(EditScene* g2);
 /*private*/ void drawMemoryRects(EditScene* g2);
 /*private*/ void drawBlockContentsRects(EditScene* g2);
// /*private*/ bool checkSelect(QPointF loc, bool requireUnconnected);
// /*private*/ bool checkSelect(QPointF loc, bool requireUnconnected, QObject* avoid);
 /*private*/ void amendSelectionGroup(Positionable* p);
 /*private*/ void amendSelectionGroup(LayoutTurnout* p);
 /*private*/ void amendSelectionGroup(PositionablePoint* p);
 /*private*/ void amendSelectionGroup(LevelXing* p);
 /*private*/ void amendSelectionGroup(LayoutTrack *p);
 /*private*/ bool foundNeedsConnect;// = false; // true if found point needs a connection
 /*private*/ static const double SIZE;// = 3.0;
 /*private*/ static const double SIZE2;// = 6.0;  // must be twice SIZE
 float mainlineTrackWidth;// = 4.0F;
 float sidelineTrackWidth;// = 2.0F;
 bool main;// = true;
 float trackWidth;// = sideTrackWidth;
 bool _editable;
 bool turnoutCirclesWithoutEditMode;// = false;
// LocoNetSystemConnectionMemo * memo;// = new LocoNetSystemConnectionMemo();
// LnSensorManager* lnSensorManager;
 friend class SensorIcon;
 InternalSensorManager* internalSensorManager;
 /*private*/ QPointF midpoint (QPointF p1,QPointF p2) ;
 /*protected*/ QPointF third (QPointF p1,QPointF p2) ;
 /*private*/ QPointF fourth (QPointF p1,QPointF p2);
 bool animatingLayout;
 /*private*/ bool showHelpBar = true;
 int panelWidth, panelHeight;
 int windowWidth, windowHeight;
 int upperLeftX, upperLeftY;
 int _scrollState;
 int _anchorX, _anchorY;
 QPointF startDel;
 bool _positionable;
 /*private*/ /*transient*/ bool snapToGridOnAdd = false;
 /*private*/ /*transient*/ bool snapToGridOnMove = false;
 /*private*/ /*transient*/ bool snapToGridInvert = false;
 bool delayedPopupTrigger;
 int _lastX, _lastY;
 /*private*/ void drawPanelGrid(EditScene* g2);
 /*private*/ bool drawGrid; //false;
// /*private*/ void drawTrackInProgress(EditScene* g2);
// /*private*/ void drawHiddenTrack(EditScene* g2);
// /*private*/ void drawDashedTrack(EditScene* g2, bool mainline);
// /*private*/ void drawSolidTrack(EditScene* g2, bool isMainline);
// /*private*/ void CalculateTrackSegmentAngle(TrackSegment* t);
// /*private*/ void drawTrackOvals(EditScene* g2);
 bool antialiasingOn;// = false;
// /*private*/ void checkPopUp(QGraphicsSceneMouseEvent* event);
// /*private*/ TrackSegment* checkTrackSegments(QPointF loc);

// /*private*/ void drawTrackCircleCentre(EditScene* g2);
 double toRadians(double degrees);
 double toDegrees(double radians);
 /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event);
 bool _controlLayout= true;
 bool noWarnPositionablePoint;
 bool noWarnSlip;
 /*private*/ void disconnect(QObject* o, int type);
 ///*private*/ void drawMemoryRects(EditScene* g2);
 /*private*/ PositionableLabel* checkLabelImages(QPointF loc);
 /**
 * Add a sensor indicator to the Draw Panel
 */
 void addSensor();

  bool bDirty;
  InstanceManager* instanceManager;
  /*private*/ bool _showCoordinates;// = true;
 Positionable* saveP;
 /*private*/ PositionableLabel* checkBackgrounds(QPointF loc);
 bool selectedNeedsConnect;
 /*private*/ MultiSensorIcon* checkMultiSensors(QPointF loc);
 /*private*/ LocoIcon* checkMarkers(QPointF loc);
 /*private*/ MultiIconEditor* iconEditor;// = nullptr;
 QGraphicsItemGroup* panelGridGroup = nullptr;
 QGraphicsItem* trackInProgress;
 /*private*/ bool _globalSetsLocal;// = true;    // pre 2.9.6 behavior
 /*private*/ bool _useGlobalFlag;// = false;     // pre 2.9.6 behavior
 QGraphicsRectItem *rectItem; // selection rect.
 QGraphicsItemGroup* highlightRect = nullptr;

 /*private*/ void highLightSelection(EditScene* g);
 bool noWarnGlobalDelete;
 bool noWarnLevelXing;
 bool noWarnLayoutTurnout;
 bool noWarnTurntable;// = false;
 QString _defaultToolTip;
 Positionable* currComp;
 MemoryIcon* checkMemoryMarkerIcons(QPointF loc);
 // /*private*/ int getNextBackgroundLeft();
 JFileChooser* inputFileChooser;
 //void setScale(double scaleX, double scaleY);
 //QStringList _Colors;
 //QList<QColor> _colors;
 bool tooltipsWithoutEditMode = false;
 bool tooltipsInEditMode = true;
 bool _loadFailed;// = false;
 bool _debug;
 bool _ignore;
 QMap<QString, QString>* _urlMap;// = new QMap<QString, QString>();
 NamedIcon* _newIcon;
 bool _delete;
 //QFormLayout* formLayout;
 RosterEntrySelectorPanel* rosterBox;
 //bool bTestMode;
 QString layoutFile;
 int _prevNumSel;
 /*private*/ SignalHeadIcon* checkSignalHeadIcons(QPointF loc);
 /*private*/ SignalMastIcon* checkSignalMastIcons(QPointF loc);
 /*private*/ AnalogClock2Display* checkClocks(QPointF loc);
 LayoutEditorTools* tools;
 JFrame* signalFrame;
 JFrame* sensorFrame;
 ConnectivityUtil* conTools;
 /*private*/ int multiLocX;
 /*private*/ int multiLocY;
 void startMultiSensor();
 MultiSensorIconFrame* multiSensorFrame;
 // saved state of options when panel was loaded or created
 /*private*/ bool savedEditMode;// = true;
 /*private*/ bool savedPositionable;// = true;
 /*private*/ bool savedControlLayout;// = true;
 /*private*/ bool savedAnimatingLayout;// = true;
 /*private*/ bool savedShowHelpBar;// = false;
 void closeEvent(QCloseEvent *);
 bool openDispatcherOnLoad;// = false;
 /*private*/ bool useDirectTurnoutControl;// = false; //Uses Left click for closing points, Right click for throwing.
 JTextField* xMove;
 JTextField* yMove;
 /*private*/ void substituteAnchor(QPointF loc, QObject* o, TrackSegment* t);
 /*private*/ PositionablePoint* addAnchor(QPointF p);
 /*private*/ QPointF windowCenter();
// /*private*/ void drawTurntableRects(EditScene* g2);
// /*private*/ void drawSlipRects(EditScene* g2);
 QAction* turnoutCirclesOnItem;
 QActionGroup* backgroundColorButtonGroup;
 QSignalMapper* backgroundColorButtonMapper;
 QActionGroup* trackColorButtonGroup;
 QSignalMapper* trackColorButtonMapper;
 QActionGroup* trackOccupiedColorButtonGroup;
 QSignalMapper* trackOccupiedColorButtonMapper;
 QActionGroup* trackAlternativeColorButtonGroup;
 QSignalMapper* trackAlternativeColorButtonMapper;
 QActionGroup* textColorButtonGroup;
 QSignalMapper* textColorButtonMapper;
 QActionGroup* turnoutCircleColorButtonGroup;
 QSignalMapper* turnoutCircleColorButtonMapper;
 QActionGroup* turnoutCircleSizeButtonGroup;
 QSignalMapper* turnoutCircleSizeButtonMapper;
 QAction* turnoutDrawUnselectedLegItem;
 QAction* useDirectTurnoutControlItem;
 /*private*/ int backgroundColorCount;// = 0;
 /*private*/ int trackColorCount;// = 0;
 /*private*/ int trackOccupiedColorCount;// = 0;
 /*private*/ int trackAlternativeColorCount;// = 0;
 /*private*/ int textColorCount;// = 0;
 /*private*/ int turnoutCircleColorCount;// = 0;
 /*private*/ int turnoutCircleSizeCount;// = 0;
 /*private*/ QVector<QColor>* backgroundColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackOccupiedColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackAlternativeColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* textColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* turnoutCircleColors;// = new QVector<QColor>(14);
 /*private*/ QVector<int>* turnoutCircleSizes;// = new QVector<int>(10);
 QAction* autoAssignBlocksItem;
 QAction* hideTrackSegmentConstructionLines;
 /*private*/ void checkPointOfPositionable(PositionablePoint* p);
// /*private*/ void checkPointsOfTurnout(LayoutTurnout* lt);
// /*private*/ void checkPointsOfTurnoutSub(QPointF dLoc);
 /*private*/ void rotateTurnout(LayoutTurnout* t);
 void addBackgroundColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTrackColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTrackOccupiedColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTrackAlternativeColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTextColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTurnoutCircleColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
 void addTurnoutCircleSizeMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ int size);

 /*private*/ QVector<QAction*>* trackColorMenuItems;// = new QVector<QAction*>(13);
 /*private*/ QVector<QAction*>* trackOccupiedColorMenuItems;// = new QVector<QAction*>(13);
 /*private*/ QVector<QAction*>* trackAlternativeColorMenuItems;// = new QVector<QAction*>(13);
 /*private*/ QVector<QAction*>* backgroundColorMenuItems;// = new QVector<QAction*>(13);
 /*private*/ QVector<QAction*>* textColorMenuItems;// = new QVector<QAction*>(13);
 /*private*/ QVector<QAction*>* turnoutCircleColorMenuItems;// = new QVector<QAction*>(14);
 /*private*/ QVector<QAction*>* turnoutCircleSizeMenuItems;// = new QVector<QAction*>(10);

 /*private*/ double circleRadius;// = SIZE * getTurnoutCircleSize();
 /*private*/ double circleDiameter;// = 2.0 * circleRadius;
 /*private*/ /*transient*/ LayoutTrackDrawingOptions* layoutTrackDrawingOptions = nullptr;
 /*private*/ /*transient*/ JFrame* iconFrame = nullptr;
 /*private*/ /*transient*/ bool highlightSelectedBlockFlag = false;
 /*private*/ bool highlightBlockInComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox);
 /*private*/ QRectF calculateMinimumLayoutBounds();
 /*private*/ QRectF resizePanelBounds(bool forceFlag);
 //zoom
 /*private*/ /*transient*/ double minZoom;// = 0.25;
 /*private*/ /*transient*/ double maxZoom;// = 8.0;
 // /*private*/ void adjustScrollBars();
 QLabel* zoomLabel;
 /*private*/ void selectZoomMenuItem(double zoomFactor);
 /*private*/ /*transient*/ QMenu* zoomMenu;// = new JMenu(Bundle.getMessage("MenuZoom"));
 /*private*/ /*transient*/ QAction* zoom025Item;// = new JRadioButtonMenuItem("x 0.25");
 /*private*/ /*transient*/ QAction* zoom05Item;// = new JRadioButtonMenuItem("x 0.5");
 /*private*/ /*transient*/ QAction* zoom075Item;// = new JRadioButtonMenuItem("x 0.75");
 /*private*/ /*transient*/ QAction* noZoomItem;// = new JRadioButtonMenuItem(Bundle.getMessage("NoZoom"));
 /*private*/ /*transient*/ QAction* zoom15Item;// = new JRadioButtonMenuItem("x 1.5");
 /*private*/ /*transient*/ QAction* zoom20Item;// = new JRadioButtonMenuItem("x 2.0");
 /*private*/ /*transient*/ QAction* zoom30Item;// = new JRadioButtonMenuItem("x 3.0");
 /*private*/ /*transient*/ QAction* zoom40Item;// = new JRadioButtonMenuItem("x 4.0");
 /*private*/ /*transient*/ QAction* zoom50Item;// = new JRadioButtonMenuItem("x 5.0");
 /*private*/ /*transient*/ QAction* zoom60Item;// = new JRadioButtonMenuItem("x 6.0");
 /*private*/ /*transient*/ QAction* zoom70Item;// = new JRadioButtonMenuItem("x 7.0");
 /*private*/ /*transient*/ QAction* zoom80Item;// = new JRadioButtonMenuItem("x 8.0");
 //grid size in pixels
 /*private*/ /*transient*/ int gridSize1st = 10;
 // secondary grid
 /*private*/ /*transient*/ int gridSize2nd = 10;
 /*private*/ QString findBeanUsage(NamedBean* sm);
 /*private*/ void removeBeanRefs(NamedBean* sm);
 /*private*/ bool removeSignalMast(SignalMastIcon* si);
 /*private*/ void checkControls(bool useRectangles);
 /*private*/ bool findLayoutTracksHitPoint(/*@Nonnull*/ QPointF loc, bool requireUnconnected);
 /*private*/ bool findLayoutTracksHitPoint(/*@Nonnull*/ QPointF loc);
 /*private*/ bool findLayoutTracksHitPoint(/*@Nonnull*/ QPointF loc,
         bool requireUnconnected, /*@Nullable*/ LayoutTrack* avoid);
 /*private*/ TrackSegment* checkTrackSegmentPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ PositionableLabel* checkBackgroundPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ SensorIcon* checkSensorIconPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ SignalHeadIcon* checkSignalHeadIconPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ SignalMastIcon* checkSignalMastIconPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ PositionableLabel* checkLabelImagePopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ AnalogClock2Display* checkClockPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ MultiSensorIcon* checkMultiSensorPopUps(/*@Nonnull */QPointF loc);
 /*private*/ LocoIcon* checkMarkerPopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ /*transient*/ LayoutTrackEditors* layoutTrackEditors = nullptr;
 /*private*/ /*transient*/ LayoutEditorChecks* layoutEditorChecks = nullptr;
 //operational variables for enter track width pane
 /*private*/ /*transient*/ JmriJFrame* enterTrackWidthFrame = nullptr;
 /*private*/ bool enterTrackWidthOpen = false;
 /*private*/ bool trackWidthChange = false;
 /*private*/ /*transient*/ JTextField* sidelineTrackWidthField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* mainlineTrackWidthField;// = new JTextField(6);
 /*private*/ /*transient*/ QPushButton* trackWidthDone;
 /*private*/ /*transient*/ QPushButton* trackWidthCancel;
 //operational variables for enter grid sizes pane
 /*private*/ /*transient*/ JmriJFrame* enterGridSizesFrame = nullptr;
 /*private*/ bool enterGridSizesOpen = false;
 /*private*/ bool gridSizesChange = false;
 /*private*/ /*transient*/ JTextField* primaryGridSizeField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* secondaryGridSizeField;// = new JTextField(6);
 /*private*/ /*transient*/ QPushButton* gridSizesDone = nullptr;
 /*private*/ /*transient*/ QPushButton* gridSizesCancel = nullptr;
 //operational variables for enter reporter pane
 /*private*/ /*transient*/ JmriJFrame* enterReporterFrame = nullptr;
 /*private*/ bool reporterOpen = false;
 /*private*/ /*transient*/ JTextField* xPositionField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* yPositionField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* reporterNameField;// = new JTextField(6);
 /*private*/ /*transient*/ QPushButton* reporterDone;
 /*private*/ /*transient*/ QPushButton* reporterCancel;
 //operational variables for scale/translate track diagram pane
 /*private*/ /*transient*/ JmriJFrame* scaleTrackDiagramFrame = nullptr;
 /*private*/ bool scaleTrackDiagramOpen = false;
 /*private*/ /*transient*/ JTextField* xFactorField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* yFactorField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* xTranslateField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* yTranslateField ;//= new JTextField(6);
 /*private*/ /*transient*/ QPushButton* scaleTrackDiagramDone = nullptr;
 /*private*/ /*transient*/ QPushButton* scaleTrackDiagramCancel =nullptr;
 /*private*/ /*transient*/ JmriBeanComboBox::DisplayOptions gDDMDO ;//= JmriBeanComboBox.DisplayOptions.DISPLAYNAME;
 /*private*/ /*transient*/ QList<LayoutTrack*> _layoutTrackSelection;// = new ArrayList<>();
 /*private*/ void updateComboBoxDropDownListDisplayOrderFromPrefs(/*@Nonnull*/ Component* inComponent);
 /*private*/ void updateDropDownMenuDisplayOrderMenu();
 /*private*/ void updateAllComboBoxesDropDownListDisplayOrderFromPrefs();
 /*private*/ void showEditPopUps(/*@Nonnull */QGraphicsSceneMouseEvent* event);
 /*private*/ void hitPointCheckLayoutTurnouts(/*@Nonnull*/ LayoutTurnout* lt);
 /*private*/ void hitPointCheckLayoutTurnoutSubs(/*@Nonnull*/ QPointF dLoc);
 QPen drawingStroke;

 //operational variables for move selection pane
 /*private*/ /*transient*/ JmriJFrame* moveSelectionFrame = nullptr;
 /*private*/ bool moveSelectionOpen = false;
 /*private*/ /*transient*/ JTextField* xMoveField;// = new JTextField(6);
 /*private*/ /*transient*/ JTextField* yMoveField;// = new JTextField(6);
 /*private*/ /*transient*/ QPushButton* moveSelectionDone;
 /*private*/ /*transient*/ QPushButton* moveSelectionCancel;
 /*private*/ bool canUndoMoveSelection = false;
 /*private*/ double undoDeltaX = 0.0;
 /*private*/ double undoDeltaY = 0.0;
 /*private*/ /*transient*/ QRectF undoRect;
 QAction* skipTurnoutCheckBoxMenuItem;
 /*private*/ bool includedTurnoutSkipped = false;
 /*private*/ void setupMarkerMenu(/*@Nonnull*/ QMenuBar *menuBar);
 /*private*/ void setupDispatcherMenu(/*@Nonnull*/ QMenuBar* menuBar);
 /*private*/ void setupZoomMenu(QMenuBar* menuBar);

 //Option menu items
 /*private*/ /*transient*/ QAction* editModeCheckBoxMenuItem = nullptr;

 /*private*/ /*transient*/ QAction* toolBarSideTopButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideLeftButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideBottomButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideRightButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideFloatButton = nullptr;

 /*private*/ /*transient*/ QMenu* toolBarFontSizeMenu;// = new JMenu(Bundle.getMessage("FontSize"));
 /*private*/ /*transient*/ QAction* wideToolBarCheckBoxMenuItem;// = new JCheckBoxMenuItem(Bundle.getMessage("ToolBarWide"));
 /*private*/ /*transient*/ QMenu* dropDownListsDisplayOrderMenu;// = new JMenu(Bundle.getMessage("DropDownListsDisplayOrder"));

 /*private*/ /*transient*/ QAction* positionableCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* controlCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* animationCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* showHelpCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* showGridCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* autoAssignBlocksCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QMenu* scrollMenu = nullptr;
 /*private*/ /*transient*/ QAction* scrollBothMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* scrollNoneMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* scrollHorizontalMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* scrollVerticalMenuItem = nullptr;
 /*private*/ /*transient*/ QMenu* tooltipMenu = nullptr;
 /*private*/ /*transient*/ QAction* tooltipAlwaysMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* tooltipNoneMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* tooltipInEditMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* tooltipNotInEditMenuItem = nullptr;

 /*private*/ /*transient*/ QAction* snapToGridOnAddCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* snapToGridOnMoveCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* antialiasingOnCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* turnoutCirclesOnCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* turnoutDrawUnselectedLegCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* hideTrackSegmentConstructionLinesCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* useDirectTurnoutControlCheckBoxMenuItem = nullptr;

 /*private*/ /*transient*/ bool turnoutDrawUnselectedLeg = true;
 /*private*/ /*transient*/ bool autoAssignBlocks = false;
 /*private*/ float toolBarFontSize = 12.0;
 /*private*/ /*enum*/class ToolBarSide {
 public:
  enum TOOLBARSIDES
  {
     eTOP, //("top"),
     eLEFT, //("left"),
     eBOTTOM, //("bottom"),
     eRIGHT, //("right"),
     eFLOAT //("float");
  };

     /*private*/ /*transient*/ QString name;
//     /*private*/ /*transient*/ static /*final*/ QMap<QString, ToolBarSide> ENUM_MAP;
public:
     ToolBarSide(QString name) {
         this->name = name;
     }

//     //Build an immutable map of String name to enum pairs.
//     static {
//         Map<String, ToolBarSide> map = new ConcurrentHashMap<>();

//         for (ToolBarSide instance : ToolBarSide.values()) {
//             map.put(instance.getName(), instance);
//         }
//         ENUM_MAP = Collections.unmodifiableMap(map);
//     }

     /*public*/ static ToolBarSide::TOOLBARSIDES getName(/*@Nullable*/ QString name) {
      if(name == "top")
       return eTOP;
      else if (name == "left")
       return eLEFT;
      else if (name == "bottom")
       return eBOTTOM;
      else if (name == "right")
       return eRIGHT;
      else //if (name == "float")
       return eFLOAT;
     }

     /*public*/ QString getName() {
         return name;
     }
 };
 /*private*/ /*transient*/ ToolBarSide toolBarSide = ToolBarSide("top");
 /*private*/ /*transient*/ bool toolBarIsWide = true;
 /*private*/ void setToolBarSide(ToolBarSide::TOOLBARSIDES newToolBarSide);
 /*private*/ void setToolBarWide(bool newToolBarIsWide);


private slots:
 void OnScenePos(QGraphicsSceneMouseEvent*);
 /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
 /**
  * Handle a mouse pressed event
  */
 /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event);

 void on_actionShow_grid_in_edit_mode_toggled(bool bChecked);
 void on_actionEnable_antialiasing_smoother_lines_toggled(bool bChecked);
 //void On_lockPosition_triggered(bool bChecked);
 void On_removeMenuAction_triggered();
 void on_actionAdd_loco_triggered();
 void on_actionAdd_loco_from_roster_triggered();
 void on_actionRemove_markers_triggered();
 void on_actionAllow_turnout_animation_toggled(bool bChecked);
 void on_actionAllow_repositioning_toggled(bool bChecked);
 void on_actionAllow_layout_control_toggled(bool bChecked);
 /*private*/ void deleteSelectedItems(); // SLOT[]
 void on_actionShow_turnout_circles_toggled(bool bState);
 void On_actionHidden_toggled(bool bState);
 void on_actionEdit_track_width_triggered();
 void on_colorBackgroundMenuItemSelected(int);
 void on_actionAdd_reporter_label_triggered();
 void on_actionAdd_background_image_2_triggered();
 //void on_actionLoad_XML_triggered();
 //void on_actionLoad_Other_XML_triggered();
 void on_actionSave_triggered();
 //void on_actionSave_as_triggered();
 //void on_newSensor(QString,int,int);
 void on_actionSnap_to_grid_when_adding_toggled(bool bState);
 void on_actionSnap_to_grid_when_moving_toggled(bool bState);
 void OnZoom_selected(QAction* act);
 void on_actionEdit_mode_toggled(bool bState);
 void OnDefaultTrackColorSelected(QAction * act);
 void OnDefaultTextColorSelected(int);
 void on_actionDelete_this_panel_triggered();
 void on_actionSkip_unsignalled_Internal_Turnouts_toggled(bool);
 void on_actionSet_Signals_at_Block_Boundary_triggered();
 void on_actionSet_Signals_at_Turnout_triggered();
 void on_actionSet_Signals_at_Crossover_triggered();
 void on_actionSet_Signals_at_Level_Crossing_triggered();
 //void locoMarkerFromRoster();
 //void on_rosterBoxSelectionChanged(QString propertyName,QObject* o,QObject* n);
 //void on_menuWindow_aboutToShow();
 void on_actionAdd_Fast_Clock_triggered();
 void onChangeIconsButton();
 void on_actionSet_Signals_at_Slip_triggered();
 void on_actionSet_Signals_at_Throat_to_Throat_Turnouts_triggered();
 void on_actionEntry_Exit_triggered();
// void on_actionMoveLayout_triggered();
// void on_okMove_clicked();
 void on_actionAdd_Turntable_triggered();
 void On_turnoutCirclesOnItem_triggered(bool);
 void On_turnoutDrawUnselectedLegItem_triggered(bool);
 void On_turnoutCircleColorButtonMapper_triggered(int);
 void On_turnoutCircleSizeButtonMapper_triggered(int);
 void on_actionSet_Signals_at_Three_Way_Turnout();
 void on_autoAssignBlocksItem_triggered(bool b);
 void on_hideTrackSegmentConstructionLines_toggled(bool);
 void on_useDirectTurnoutControlItem_triggered(bool);
 void on_addTrackColorMenuEntry_triggered(int);
 void on_addTrackOccupiedColorMenuEntry_triggered(int);
 void on_addTrackAlternativeColorMenuEntry_triggered(int);
 void onChangeIcons();
 void onTurnoutProperties();
 void onSecondTurnoutProperties();
 void onTrackSegmentProperties();
 void onBlockProperties();
 void onMiscFields();
 void blockContentsComboBoxChanged();
 void onActionBoth_scrollbars();
 void onActionNo_scrollbars();
 void onActionHorizontal_scrollbars();
 void onActionVertical_scrollbars();
 void onCalculateBounds();
 void onZoomIn();
 void onZoomOut();
 /*private*/ double zoomIn();
 /*private*/ double zoomOut();
 double zoomToFit();
 void onLayoutTrackDrawingOptionsDialog();
 void On_clearTrack(); // for testing
 void onTranslateSelections();
 void moveSelectionCancelPressed();
 void moveSelectionDonePressed(/*@Nonnull ActionEvent event*/);
 void onNewTrain();
 void onZoom025Item();
 void onZoom05Item();
 void onZoom075Item();
 void onNoZoomItem();
 void onZoom15Item();
 void onZoom20Item();
 void onZoom30Item();
 void onZoom40Item();
 /*private*/ void resetTurnoutSize();
 void onTurnoutCircleColorMenuItem();
 void onTooltipNoneMenuItem();
 void onTooltipAlwaysMenuItem();
 void onTooltipInEditMenuItem();
 void onTooltipNotInEditMenuItem();
protected:
 /**
 * Return a List of all items whose bounding rectangle contain the mouse position.
 * ordered from top level to bottom
 */
 /*protected*/ QList <Positionable*> getSelectedItems(QGraphicsSceneMouseEvent* event);
 ///*protected*/ QVector <Positionable*>* _contents;// = new QVector<Positionable*>();
 void init();
 /*protected*/ double _paintScale;// = 1.0;   // scale for _targetPanel drawing
 /*protected*/ static QPointF getCoords(QObject* o, int type);
 /*public*/ QGraphicsEllipseItem* trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint);
 //compute the turnout circle at inPoint (used for drawing)
 /*public*/ QGraphicsEllipseItem* trackControlCircleAt(/*@Nonnull */QPointF inPoint);
 /**
 *  Special internal class to allow drawing of layout to a JLayeredPane
 *  This is the 'target' pane where the layout is displayed
 */
 /*protected*/ void paintTargetPanel(EditScene* g2);
 /*protected*/ void setTrackStrokeWidth(bool need);
 /**
 * Select the menu items to display for the Positionable's popup
 */
// /*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*protected*/ bool showAlignPopup();
 /**
 * Remove a PositionablePoint -- an Anchor or an End Bumper.
 */
 /*protected*/ bool removePositionablePoint(PositionablePoint* o);
 /**
 * Remove a Track Segment
 */
 /*protected*/ void removeTrackSegment(TrackSegment* o);
 /**
 * Remove a LayoutTurnout
 */
 /*protected*/ bool removeLayoutTurnout(LayoutTurnout* o);
 /**
 * Remove a Level Crossing
 */
 /*protected*/ bool removeLevelXing (LevelXing* o);
 /*protected*/ bool removeTurntable(LayoutTurntable* o);


 /**
 * Set object location and size for icon and label object as it is created.
 * Size comes from the preferredSize; location comes
 * from the fields where the user can spec it.
 */
 /*protected*/ void setNextLocation(Positionable *obj);
// /*protected*/ void setNextLocation(PositionableLabel* obj);

// /*protected*/ void addToTarget(Positionable* l);
 /**
 * Remove object from all Layout Editor temmporary lists of items not part of track schematic
 */
 /*protected*/ bool remove(QObject* s);
 /*private*/ SensorIcon* checkSensorIcons(QPointF loc);
 /*protected*/ void setSelectionsScale(double s, Positionable* p);
 /*protected*/ void setSelectionsRotation(int k, Positionable* p);
 friend class CoordinateEdit;
 /*protected*/ void removeSelections(Positionable* p);
 /*protected*/ void setSelectionsHidden(bool enabled, Positionable* p);
 ///*protected*/ void makeBackgroundColorMenu(QMenu* colorMenu);
 /*protected*/ void addBackgroundColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup, const QString name, QColor color);
 /*protected*/ bool removeLayoutSlip (LayoutTurnout* o);
// /*protected*/ LocoIcon* selectLoco(QString rosterEntryTitle);
// /*protected*/ LocoIcon* selectLoco(RosterEntry* entry);
 /*protected*/ bool skipIncludedTurnout;// = false;
 /*protected*/ void targetWindowClosingEvent(/*WindowEvent*/ QCloseEvent* e);
 /**
 * Remove marker icons from panel
 */
 /*protected*/ void removeMarkers();
 /*protected*/ void setOptionMenuTurnoutCircleSize();
 /*protected*/ void setOptionMenuTurnoutCircleColor();
 /*protected*/ void setOptionMenuTextColor();
 /*protected*/ void setOptionMenuBackgroundColor();
 /*protected*/ void setOptionMenuTrackColor();
 /*protected*/ void removeBackground(PositionableLabel* b);
 /*protected*/ void drawTurnouts(EditScene* g2);
 /*protected*/ void setupToolsMenu(/*@Nonnull*/ QMenuBar* menuBar);
 /*protected*/ void scaleTrackDiagram();
 /*protected*/ void enterTrackWidth();
 /*protected*/ void enterGridSizes();
 /*protected*/ void enterReporter(int defaultX, int defaultY);
 /*protected*/ void showPopUp(/*@Nonnull*/ Positionable* p, /*@Nonnull */QGraphicsSceneMouseEvent* event);
 /*protected*/ QMenu* setupOptionMenu(/*@Nonnull*/ QMenuBar* menuBar);

protected slots:
 /*protected*/ void assignBlockToSelection();
 void trackWidthDonePressed(/*ActionEvent evemt*/);
 void trackWidthCancelPressed(/*ActionEvent event*/);
 void gridSizesDonePressed(/*ActionEvent event*/);
 void gridSizesCancelPressed(/*ActionEvent event*/);
 void reporterDonePressed(/*@Nonnull ActionEvent event*/);
 void reporterCancelPressed();
 void scaleTrackDiagramDonePressed(/*ActionEvent event*/);
 void scaleTrackDiagramCancelPressed(/*ActionEvent event*/);
 /*protected*/ void moveSelection();
 void undoMoveSelection();


friend class TrackSegment;
friend class EditLevelXingDlg;
friend class LayoutSlip;
friend class SaveXml;
friend class PositionableLabel;
friend class LocoIconXml;
friend class LayoutBlockManager;
friend class LayoutEditorTools;
friend class EditTrackSegmentDlg;
friend class EditTurnout;
friend class LayoutEditorXml;
friend class LayoutTurntable;
friend class PositionablePoint;
friend class LoadXml;
friend class LayoutEditorChecks;
friend class EnterTrackWidthFrameWindowListener;
friend class EnterGridSizesFrameWindowListener;
};
Q_DECLARE_METATYPE(LayoutEditor)

/*static*/ class TurnoutSelection
{
    bool pointA = false;
    bool pointB = false;
    bool pointC = false;
    bool pointD = false;
public:
    TurnoutSelection() {}

    void setPointA(bool boo) {
        pointA = boo;
    }

    void setPointB(bool boo) {
        pointB = boo;
    }

    void setPointC(bool boo) {
        pointC = boo;
    }

    void setPointD(bool boo) {
        pointD = boo;
    }

    bool getPointA() {
        return pointA;
    }

    bool getPointB() {
        return pointB;
    }

    bool getPointC() {
        return pointC;
    }

    bool getPointD() {
        return pointD;
    }
};
class EnterTrackWidthFrameWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutEditor* layoutEditor;
public:
 EnterTrackWidthFrameWindowListener(LayoutEditor* layoutEditor) { this->layoutEditor = layoutEditor;}
 void windowClosing(QCloseEvent*) {layoutEditor->trackWidthCancelPressed();}
};
class EnterGridSizesFrameWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutEditor* layoutEditor;
public:
 EnterGridSizesFrameWindowListener(LayoutEditor* layoutEditor) { this->layoutEditor = layoutEditor;}
 void windowClosing(QCloseEvent*) {layoutEditor->gridSizesCancelPressed();}
};
#endif // LAYOUTEDITOR_H
