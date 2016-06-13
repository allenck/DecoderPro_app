#ifndef LAYOUTEDITOR_H
#define LAYOUTEDITOR_H
#include "paneleditor.h"
#include "layoutblock.h"
#include <QButtonGroup>
#include <QLineEdit>
#include <QPointF>
#include "levelxing.h"
#include "connectivityutil.h"
#include "layouteditorauxtools.h"
#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include "exceptions.h"

class LayoutBlock;
class TrackSegment;
class LayoutTurnout;
class PositionablePoint;
class ConnectivityUtil;
class LayoutEditorAuxTools;
class LayoutEditor : public PanelEditor
{
 friend class ConnectivityUtil;
    Q_OBJECT
public:
    explicit LayoutEditor(QString name = "myLayout", QObject *parent = 0);
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
    /*public*/ bool validateSensor(QString sensorName, LayoutBlock* blk, Component* openFrame);

#if 0
    /*public*/ QVector<PositionableLabel>* backgroundImage = new QVector<PositionableLabel>();  // background images
    /*public*/ QVector<SensorIcon>* sensorImage = new QVector<SensorIcon>();  // sensor images
    /*public*/ QVector<SignalHeadIcon>* signalHeadImage = new QVector<SignalHeadIcon>();  // signal head images
    /*public*/ QVector<SignalMastIcon>* signalMastImage = new QVector<SignalMastIcon>();  // signal mast images
    /*public*/ QVector<LocoIcon>* markerImage = new QVector<LocoIcon>(); // marker images
    /*public*/ QVector<PositionableLabel>* labelImage = new QVector<PositionableLabel>(); // layout positionable label images
    /*public*/ QVector<AnalogClock2Display>* clocks = new QVector<AnalogClock2Display>();  // fast clocks
    /*public*/ QVector<MultiSensorIcon>* multiSensors = new QVector<MultiSensorIcon>(); // multi-sensor images
#endif
    /*public*/ LayoutEditorAuxTools* auxTools;// = NULL;
    /*protected*/ void init(QString name);
    /*public*/ void initView();
    /*public*/ void setSize(int w, int h);
    /*public*/ void setCurrentPositionAndSize() ;
    void addBackgroundColorMenuEntry(/*JMenu*/QMenu menu,  QString name, QColor color);
    void addTrackColorMenuEntry(/*JMenu*/QMenu menu,  QString name, QColor color);
    void addTrackOccupiedColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  QColor color);
    void addTrackAlternativeColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  QColor color);
    void addTextColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  QColor color);
    /*public*/ void setScroll(int state);
    /**
     * Add a layout turntable at location specified
     */
    /*public*/ void addTurntable(QPointF pt);
    /**
     * Allow external trigger of re-draw
     */
    /*public*/ void redrawPanel();
    /**
     * Allow external set/reset of awaitingIconChange
     */
    /*public*/ void setAwaitingIconChange();
    /*public*/ void resetAwaitingIconChange() ;
    /**
     * Allow external reset of dirty bit
     */
    /*public*/ void resetDirty();

    /**
     * Allow external set of dirty bit
     */
    /*public*/ void setDirty(bool val);
    /*public*/ void setDirty();
    /**
     * Check the dirty state
     */
    /*public*/ bool isDirty();
    /**
     * Handle a mouse pressed event
     */
    /*public*/ void mousePressed(MouseEvent* event);
    /*public*/ QPointF getEndCoords(QObject* o, int type);
    /*public*/ void mouseReleased(MouseEvent* event);
    /*public*/ void mouseClicked(MouseEvent* event);
    /*public*/ void alignSelection(bool alignX);
    /* Offer actions to align the selected Positionable items either
    * Horizontally (at avearage y coord) or Vertically (at avearage x coord).
    */
    /*public*/ bool setShowAlignmentMenu(JPopupMenu* popup);
    /*public*/ void keyPressed(KeyEvent* e);
    /*public*/ void mouseMoved(MouseEvent* event);
    /*public*/ void mouseDragged(MouseEvent* event);
    /**
     * Add an Anchor point.
     */
    /*public*/ void addAnchor();
    /**
     * Add an End Bumper point.
     */
    /*public*/ void addEndBumper();
    /**
     * Add a Track Segment
     */
    /*public*/ void addTrackSegment();
    /**
     * Add a Level Crossing
     */
    /*public*/ void addLevelXing();
    /**
     * Add a LayoutSlip
     */
    /*public*/ void addLayoutSlip(int type);
    /**
     * Add a Layout Turnout
     */
    /*public*/ void addLayoutTurnout(int type);
    /**
     * Validates that a physical turnout exists and is unique among Layout Turnouts
     *    Returns true if valid turnout was entered, false otherwise
     */
    /*public*/ bool validatePhysicalTurnout(QString turnoutName, Component* openPane);



    /**
     * Return a layout block with the given name if one exists.
     * Registers this LayoutEditor with the layout block.
     * This method is designed to be used when a panel is loaded. The calling
     *		method must handle whether the use count should be incremented.
     */
    /*public*/ LayoutBlock* getLayoutBlock(QString blockID) ;

    /**
     * Remove object from all Layout Editor temmporary lists of items not part of track schematic
     */
    /*protected*/ bool remove(QObject* s) ;

//    /*public*/ bool removeFromContents(Positionable* l) ;

    bool noWarnPositionablePoint;// = false;

    /**
     * Remove a PositionablePoint -- an Anchor or an End Bumper.
     */
    /*protected*/ bool removePositionablePoint(PositionablePoint* o) ;

    bool noWarnLayoutTurnout;// = false;

    /**
     * Remove a LayoutTurnout
     */
    /*protected*/ bool removeLayoutTurnout(LayoutTurnout* o) ;
    bool noWarnLevelXing;// = false;

    /**
     * Remove a Level Crossing
     */
    /*protected*/ bool removeLevelXing (LevelXing* o) ;

    bool noWarnSlip;// = false;

    /*protected*/ bool removeLayoutSlip (LayoutTurnout* o) ;

    bool noWarnTurntable;// = false;

    /*private*/ void disconnect(QObject* o, int type) ;
    /*public*/ LayoutBlock getAffectedBlock(QObject* o, int type) ;
    /**
     * Add a sensor indicator to the Draw Panel
     */
    void addSensor();
//    /*public*/ void putSensor(SensorIcon* l);
    /**
     * Add a signal head to the Panel
     */
    void addSignalHead() ;
//    /*public*/ void putSignal(SignalHeadIcon* l) ;
    SignalHead* getSignalHead(QString name) ;
    void addSignalMast() ;
//    /*public*/ void putSignalMast(SignalMastIcon* l) ;
    SignalMast* getSignalMast(QString name) ;
    /**
     * Add a label to the Draw Panel
     */
    void addLabel() ;
//    /*public*/ void putItem(Positionable l) ;

     /**
     * Add a memory label to the Draw Panel
     */
    void addMemory() ;

    /**
     * Add a Reporter Icon to the panel
     */
    void addReporter(QString textReporter,int xx,int yy) ;

    /**
     * Add an icon to the target
     */
    void addIcon() ;

    /**
     * Add a loco marker to the target
     */
//    /*public*/ LocoIcon* addLocoIcon (QString name);

//    /*public*/ void putLocoIcon(LocoIcon* l, QString name) ;

//    JFileChooser* inputFileChooser;

    /**
     * Add a background image
     */
    /*public*/ void addBackground() ;


    /**
     * Invoke a window to allow you to add a MultiSensor indicator to the target
     */
    void startMultiSensor() ;
    /**
     * Set object location and size for icon and label object as it is created.
     * Size comes from the preferredSize; location comes
     * from the fields where the user can spec it.
     */
    /*protected*/ void setNextLocation(Positionable* obj) ;
    /*public*/ ConnectivityUtil* getConnectivityUtil();
    /*public*/ LayoutEditorTools* getLETools();
    /**
     * Invoked by DeletePanel menu item
     *     Validate user intent before deleting
     */
    /*public*/ bool deletePanel();
    /**
     *  Control whether target panel items are editable.
     *  Does this by invoke the {@link Editor#setAllEditable} function of
     *  the parent class. This also controls the relevant pop-up menu items
     *  (which are the primary way that items are edited).
     * @param editable true for editable.
     */
    /*public*/ void setAllEditable(bool editable);
    /**
     *  Control whether panel items are positionable.
     *  Markers are always positionable.
     * @param state true for positionable.
     */
    /*public*/ void setAllPositionable(bool state);

    /**
     *  Control whether target panel items are controlling layout items.
     *  Does this by invoke the {@link Positionable#setControlling} function of
     *  each item on the target panel. This also controls the relevant pop-up menu items.
     * @param state true for controlling.
     */
    /*public*/ void setTurnoutAnimation(bool state);
    /*public*/ bool isAnimating();
    /*public*/ int getLayoutWidth();
    /*public*/ int getLayoutHeight();
    /*public*/ int getWindowWidth();
    /*public*/ int getWindowHeight();
    /*public*/ int getUpperLeftX();
    /*public*/ int getUpperLeftY();
    /*public*/ bool getScroll();
    /*public*/ int getMainlineTrackWidth() ;
    /*public*/ int getSideTrackWidth();
    /*public*/ double getXScale();
    /*public*/ double getYScale();
    /*public*/ QString getDefaultTrackColor();
    /*public*/ QString getDefaultOccupiedTrackColor();
    /*public*/ QString getDefaultAlternativeTrackColor();
    /*public*/ QString getDefaultTextColor();
    /*public*/ QString getTurnoutCircleColor();
    /*public*/ int getTurnoutCircleSize();
    /*public*/ bool getTurnoutDrawUnselectedLeg();
    /*public*/ QString getLayoutName();
    /*public*/ bool getShowHelpBar();
    /*public*/ bool getDrawGrid();
    /*public*/ bool getSnapOnAdd();
    /*public*/ bool getSnapOnMove();
    /*public*/ bool getAntialiasingOn();
    /*public*/ bool getTurnoutCircles();
    /*public*/ bool getTooltipsNotEdit() ;
    /*public*/ bool getTooltipsInEdit();
    /*public*/ bool getAutoBlockAssignment();
    /*public*/ void setLayoutDimensions(int windowW, int windowH, int x, int y, int panelW, int panelH);
    /*public*/ void setMainlineTrackWidth(int w);
    /*public*/ void setSideTrackWidth(int w);
    /*public*/ void setDefaultTrackColor(QString color) ;
    /*public*/ void setDefaultOccupiedTrackColor(QString color);
    /*public*/ void setDefaultAlternativeTrackColor(QString color);
    /*public*/ void setTurnoutCircleColor(QString color);
    /*public*/ void setTurnoutCircleSize(int size);
    /*public*/ void setTurnoutDrawUnselectedLeg(bool state);
    /*public*/ void setDefaultTextColor(QString color);
    /*public*/ void setDefaultBackgroundColor(QString color);
    /*public*/ void setXScale(double xSc);
    /*public*/ void setYScale(double ySc);
    /*public*/ void setLayoutName(QString name);
    /*public*/ void setShowHelpBar(bool state);
    /*public*/ void setDrawGrid(bool state);
    /*public*/ void setSnapOnAdd(bool state);
    /*public*/ void setSnapOnMove(bool state);
    /*public*/ void setAntialiasingOn(bool state);
    /*public*/ void setTurnoutCircles(bool state);
    /*public*/ void setAutoBlockAssignment(bool boo);
    /*public*/ void setTooltipsNotEdit(bool state);
    /*public*/ void setTooltipsInEdit(bool state);

    // accessor routines for turnout size parameters
    /*public*/ void setTurnoutBX(double bx);
    /*public*/ double getTurnoutBX();
    /*public*/ void setTurnoutCX(double cx);
    /*public*/ double getTurnoutCX();
    /*public*/ void setTurnoutWid(double wid);
    /*public*/ double getTurnoutWid();
    /*public*/ void setXOverLong(double lg);
    /*public*/ double getXOverLong();
    /*public*/ void setXOverHWid(double hwid);
    /*public*/ double getXOverHWid() {return xOverHWid;}
    /*public*/ void setXOverShort(double sh);
    /*public*/ double getXOverShort();

    /*public*/ PositionablePoint* findPositionablePointByEastBoundSensor(QString sensorName);
    /*public*/ PositionablePoint* findPositionablePointByWestBoundSensor(QString sensorName);
    /*public*/ LayoutTurnout* findLayoutTurnoutByName(QString name);
    /*public*/ LayoutTurnout* findLayoutTurnoutByTurnoutName(QString name);
    /*public*/ LevelXing* findLevelXingByName(QString name);
    // final initialization routine for loading a LayoutEditor
    /*public*/ void setConnections();
    // utility routines
    /*public*/ static QString colorToQString(QColor color);
    /*public*/ static QColor stringToColor(QString string);
    /*public*/ TrackSegment* findTrackSegmentByName(QString name);
    /*public*/ PositionablePoint* findPositionablePointByName(QString name);
    /*public*/ PositionablePoint* findPositionablePointAtTrackSegments(TrackSegment tr1, TrackSegment tr2) ;
    /**
    * Returns an array list of track segments matching the block name.
    */
    /*public*/ QVector<TrackSegment*> findTrackSegmentByBlock(QString name) ;
    /*public*/ PositionablePoint* findPositionablePointByEastBoundSignal(QString signalName);

    /*public*/ PositionablePoint* findPositionablePointByWestBoundSignal(QString signalName);

    /*public*/ PositionablePoint* findPositionablePointByEastBoundSignalMast(QString signalMastName);

    /*public*/ PositionablePoint* findPositionablePointByWestBoundSignalMast(QString signalMastName);

    /*public*/ LayoutTurnout* findLayoutTurnoutBySignalMast(QString signalMastName);

    /*public*/ LayoutTurnout* findLayoutTurnoutBySensor(QString sensorName);

    /*public*/ LevelXing* findLevelXingBySignalMast(QString signalMastName);

    /*public*/ LevelXing* findLevelXingBySensor(QString sensorName);

//    /*public*/ LayoutSlip* findLayoutSlipBySignalMast(QString signalMastName);

//    /*public*/ LayoutSlip* findLayoutSlipBySensor(QString sensorName);

signals:
    
public slots:
    
private:
// size of point boxes
 /*private*/ static const double SIZE = 3.0;
 /*private*/ static const double SIZE2 = 6.0;  // must be twice SIZE
 /*private*/ LayoutEditor* thisPanel;// = null;
 /*private*/ QDialog topEditBar;// = null;
 /*private*/ QDialog helpBar;// = null;
protected:
 /*protected*/ bool skipIncludedTurnout;// = false;
    // dashed line parameters
    ///*private*/ static int minNumDashes = 3;
    ///*private*/ static double maxDashLength = 10;

    // Operational instance variables - not saved to disk
    ///*private*/ jmri.TurnoutManager tm = NULL;
//    /*private*/ ConnectivityUtil conTools = NULL;

/*private*/ QButtonGroup* itemGroup;// = NULL;
    /*private*/ QLineEdit* blockIDField;// = new QLineEdit(8);
    /*private*/ QLineEdit* blockSensor;// = new QLineEdit(5);

    /*private*/ QCheckBox* turnoutRHBox;// = new QCheckBox(tr("RightHandAbbreviation"));
    /*private*/ QCheckBox* turnoutLHBox;// = new QCheckBox(tr("LeftHandAbbreviation"));
    /*private*/ QCheckBox* turnoutWYEBox;// = new QCheckBox(tr("WYEAbbreviation"));
    /*private*/ QCheckBox* doubleXoverBox;// = new QCheckBox(tr("DoubleCrossOver"));
    /*private*/ QCheckBox* rhXoverBox;// = new QCheckBox(tr("RHCrossOver"));
    /*private*/ QCheckBox* lhXoverBox;// = new QCheckBox(tr("LHCrossOver"));
    /*private*/ QDialog* rotationPanel;// = new QDialog();
    /*private*/ QLineEdit* rotationField;// = new QLineEdit(3);
    /*private*/ QLineEdit* nextTurnout;// = new QLineEdit(5);
    /*private*/ QDialog* extraTurnoutPanel;// = new QDialog();
    /*private*/ QLineEdit* extraTurnout;// = new QLineEdit(5);

    /*private*/ QCheckBox* levelXingBox;// = new QCheckBox(tr("LevelCrossing"));
    /*private*/ QCheckBox* layoutSingleSlipBox;// = new QCheckBox(tr("LayoutSingleSlip"));
    /*private*/ QCheckBox* layoutDoubleSlipBox;// = new QCheckBox(tr("LayoutDoubleSlip"));
    /*private*/ QCheckBox* endBumperBox;// = new QCheckBox(tr("EndBumper"));
    /*private*/ QCheckBox* anchorBox;// = new QCheckBox(tr("Anchor"));
    /*private*/ QCheckBox* trackBox;// = new QCheckBox(tr("TrackSegment"));

    /*private*/ QCheckBox* dashedLine;// = new QCheckBox(tr("Dashed"));
    /*private*/ QCheckBox* mainlineTrack;// = new QCheckBox(tr("MainlineBox"));

    /*private*/ QCheckBox* sensorBox;// = new QCheckBox(tr("SensorIcon"));
    /*private*/ QLineEdit* nextSensor;// = new QLineEdit(5);
//    /*public*/ MultiIconEditor sensorIconEditor;// = NULL;
//    /*public*/ JFrame* sensorFrame;

    /*private*/ QCheckBox* signalBox;// = new QCheckBox(tr("SignalIcon"));
    /*private*/ QLineEdit* nextSignalHead;// = new QLineEdit(5);
//    /*public*/ MultiIconEditor signalIconEditor;// = NULL;
//    /*public*/ JFrame* signalFrame;

    /*private*/ QCheckBox* signalMastBox;// = new QCheckBox(tr("SignalMastIcon"));
    /*private*/ QLineEdit* nextSignalMast;// = new QLineEdit(5);

    /*private*/ QCheckBox* textLabelBox;// = new QCheckBox(tr("TextLabel"));
    /*private*/ QLineEdit* textLabel;// = new QLineEdit(8);

    /*private*/ QCheckBox* memoryBox;// = new QCheckBox(tr("Memory"));
    /*private*/ QLineEdit textMemory;// = new QLineEdit(8);

    /*private*/ QCheckBox* iconLabelBox;// = new QCheckBox(tr("IconLabel"));
//    /*private*/ MultiIconEditor iconEditor;// = NULL;
//    /*private*/ JFrame* iconFrame;// = NULL;

    /*private*/ QCheckBox* multiSensorBox;// = new QCheckBox(tr("MultiSensor")+"...");
//    /*private*/ MultiSensorIconFrame* multiSensorFrame;// = NULL;

    /*private*/ QLabel* xLabel;// = new JLabel("00");
    /*private*/ QLabel* yLabel;// = new JLabel("00");

    /*private*/ bool delayedPopupTrigger;// = false;
    /*private*/ /*transient*/ QPointF currentPoint;// = new QPointF(100.0,100.0);
    /*private*/ /*transient*/ QPointF dLoc;// = new QPointf(0.0,0.0);
    ///*private*/ int savedMSX = 0;
    ///*private*/ int savedMSY = 0;
    /*private*/ int height;// = 100;
    /*private*/ int width;// = 100;
    ///*private*/ int numTurnouts = 0;
    /*private*/ TrackSegment* newTrack;// = NULL;
    /*private*/ bool panelChanged;// = false;

    // selection variables
    /*private*/ bool selectionActive;// = false;
    /*private*/ double selectionX;// = 0.0;
    /*private*/ double selectionY;// = 0.0;
    /*private*/ double selectionWidth;// = 0.0;
    /*private*/ double selectionHeight;// = 0.0;

    // Option menu items
#if 0
    /*private*/ JCheckBoxMenuItem editModeItem = NULL;
    /*private*/ QCheckBoxMenuItem positionableItem = NULL;
    /*private*/ QCheckBoxMenuItem controlItem = NULL;
    /*private*/ QCheckBoxMenuItem animationItem = NULL;
    /*private*/ QCheckBoxMenuItem showHelpItem = NULL;
    /*private*/ QCheckBoxMenuItem showGridItem = NULL;
    /*private*/ QCheckBoxMenuItem autoAssignBlocksItem = NULL;
    /*private*/ JMenu scrollMenu = NULL;
    /*private*/ JRadioButtonMenuItem scrollBoth = NULL;
    /*private*/ JRadioButtonMenuItem scrollNone = NULL;
    /*private*/ JRadioButtonMenuItem scrollHorizontal = NULL;
    /*private*/ JRadioButtonMenuItem scrollVertical = NULL;
    /*private*/ JMenu tooltipMenu = NULL;
    /*private*/ JRadioButtonMenuItem tooltipAlways = NULL;
    /*private*/ JRadioButtonMenuItem tooltipNone = NULL;
    /*private*/ JRadioButtonMenuItem tooltipInEdit = NULL;
    /*private*/ JRadioButtonMenuItem tooltipNotInEdit = NULL;
    /*private*/ QCheckBoxMenuItem snapToGridOnAddItem = NULL;
    /*private*/ QCheckBoxMenuItem snapToGridOnMoveItem = NULL;
    /*private*/ QCheckBoxMenuItem antialiasingOnItem = NULL;
    /*private*/ QCheckBoxMenuItem turnoutCirclesOnItem = NULL;
    /*private*/ QCheckBoxMenuItem skipTurnoutItem = NULL;
    /*private*/ QCheckBoxMenuItem turnoutDrawUnselectedLegItem = NULL;
#endif
    /*private*/ QButtonGroup trackColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup trackOccupiedColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup trackAlternativeColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup textColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup backgroundColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup turnoutCircleColorButtonGroup;// = NULL;
    /*private*/ QButtonGroup turnoutCircleSizeButtonGroup;// = NULL;
#if 0
    /*private*/ Color[] trackColors = new Color[13];
    /*private*/ Color[] trackOccupiedColors = new Color[13];
    /*private*/ Color[] trackAlternativeColors = new Color[13];
    /*private*/ Color[] textColors = new Color[13];
    /*private*/ Color[] backgroundColors = new Color[13];
    /*private*/ Color[] turnoutCircleColors = new Color[14];
    /*private*/ int[] turnoutCircleSizes = new int[8];
    /*private*/ JRadioButtonMenuItem[] trackColorMenuItems = new JRadioButtonMenuItem[13];
    /*private*/ JRadioButtonMenuItem[] trackOccupiedColorMenuItems = new JRadioButtonMenuItem[13];
    /*private*/ JRadioButtonMenuItem[] trackAlternativeColorMenuItems = new JRadioButtonMenuItem[13];
    /*private*/ JRadioButtonMenuItem[] backgroundColorMenuItems = new JRadioButtonMenuItem[13];
    /*private*/ JRadioButtonMenuItem[] textColorMenuItems = new JRadioButtonMenuItem[13];
    /*private*/ JRadioButtonMenuItem[] turnoutCircleColorMenuItems = new JRadioButtonMenuItem[14];
    /*private*/ JRadioButtonMenuItem[] turnoutCircleSizeMenuItems = new JRadioButtonMenuItem[8];
#endif
    /*private*/ int trackColorCount;// = 0;
    /*private*/ int trackOccupiedColorCount;// = 0;
    /*private*/ int trackAlternativeColorCount;// = 0;
    /*private*/ int textColorCount;// = 0;
    /*private*/ int turnoutCircleColorCount;// = 0;
    /*private*/ int turnoutCircleSizeCount;// = 0;
    /*private*/ bool turnoutDrawUnselectedLeg;// = true;
    /*private*/ int backgroundColorCount;// = 0;
    /*private*/ bool autoAssignBlocks;// = false;

    // Selected point information
    ///*private*/ final static int TURNOUT = 1;      // possible object types
    ///*private*/ final static int LEVEL_XING = 2;
    ///*private*/ final static int POINT = 3;
    /*private*/ /*transient*/ QPointF startDel;// = new QPointF(0.0,0.0); // starting delta coordinates
    /*private*/ QObject* selectedObject;// = NULL; // selected object, NULL if nothing selected
    /*private*/ QObject* prevSelectedObject;// = NULL; // previous selected object, for undo
    /*private*/ int selectedPointType;// = 0;   // connection type within the selected object
    ///*private*/ bool selectedNeedsConnect = false; // true if selected object is unconnected

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SE_TRANSIENT_FIELD_NOT_RESTORED") // no Serializable support at present
    /*private*/ QObject* foundObject;// = NULL; // found object, NULL if nothing found

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SE_TRANSIENT_FIELD_NOT_RESTORED") // no Serializable support at present
    /*private*/ /*transient*/ QPointF foundLocation;// = new QPointF(0.0,0.0);  // location of found object

    /*private*/ int foundPointType;// = 0;   // connection type within the found object

    //@SuppressWarnings("unused")
    /*private*/ bool foundNeedsConnect;// = false; // true if found point needs a connection
    /*private*/ QObject* beginObject;// = NULL; // begin track segment connection object, NULL if none
    /*private*/ /*transient*/ QPointF beginLocation;// = new QPointF(0.0,0.0);  // location of begin object
    /*private*/ int beginPointType;// = 0;   // connection type within begin connection object
    /*private*/ /*transient*/ QPointF* currentLocation;// = new QPointF(0.0,0.0); // current location

    // program default turnout size parameters
    /*private*/ double turnoutBXDefault;// = 20.0;  // RH, LH, WYE
    /*private*/ double turnoutCXDefault;// = 20.0;
    /*private*/ double turnoutWidDefault;// = 10.0;
    /*private*/ double xOverLongDefault;// = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
    /*private*/ double xOverHWidDefault;// = 10.0;
    /*private*/ double xOverShortDefault;// = 10.0;

    // Lists of items that describe the Layout, and allow it to be drawn
    //		Each of the items must be saved to disk over sessions
    /*public*/ QVector<LayoutTurnout*>* turnoutList;// = new QVector<LayoutTurnout>();  // LayoutTurnouts
    /*public*/ QVector<TrackSegment*>* trackList;// = new QVector<TrackSegment>();  // TrackSegment list
    /*public*/ QVector<PositionablePoint*>* pointList;// = new QVector<PositionablePoint>();  // PositionablePoint list
    /*public*/ QVector<LevelXing*> xingList;// = new QVector<LevelXing>();  // LevelXing list
//    /*public*/ QVector<LayoutSlip> slipList = new QVector<LayoutSlip>();  // Layout slip list
//    /*public*/ QVector<LayoutTurntable> turntableList = new QVector<LayoutTurntable>(); // Turntable list
    // counts used to determine unique internal names
    /*private*/ int numAnchors;// = 0;
    /*private*/ int numEndBumpers;// = 0;
    /*private*/ int numTrackSegments;// = 0;
    /*private*/ int numLevelXings;// = 0;
    /*private*/ int numLayoutSlips;// = 0;
    /*private*/ int numLayoutTurnouts;// = 0;
    /*private*/ int numLayoutTurntables;// = 0;
    // Lists of items that facilitate tools and drawings
//    /*public*/ QVector<SignalHeadIcon> signalList = new QVector<SignalHeadIcon>();  // Signal Head Icons
//    /*public*/ QVector<MemoryIcon> memoryLabelList = new QVector<MemoryIcon>(); // Memory Label List
//    /*public*/ QVector<SensorIcon> sensorList = new QVector<SensorIcon>();  // Sensor Icons
//    /*public*/ QVector<SignalMastIcon> signalMastList = new QVector<SignalMastIcon>();  // Signal Head Icons

    // persistent instance variables - saved to disk with Save Panel
    /*private*/ int windowWidth; //0;
    /*private*/ int windowHeight; //0;
    /*private*/ int panelWidth; //0;
    /*private*/ int panelHeight; //0;
    /*private*/ int upperLeftX; //0;
    /*private*/ int upperLeftY; //0;
    /*private*/ float mainlineTrackWidth; //4.0F;
    /*private*/ float sideTrackWidth; //2.0F;
    /*private*/ QColor defaultTrackColor; //QColor::black();
    /*private*/ QColor defaultOccupiedTrackColor; //QColor.black;
    /*private*/ QColor defaultAlternativeTrackColor; //QColor.black;
    /*private*/ QColor defaultBackgroundColor; //QColor::lightGray;
    /*private*/ QColor defaultTextColor; //QColor.black;
    /*private*/ QColor turnoutCircleColor; //defaultTrackColor; //matches earlier versions
    /*private*/ int   turnoutCircleSize; //2;  //matches earlier versions
    /*private*/ QString layoutName; //"";
    /*private*/ double xScale; //1.0;
    /*private*/ double yScale; //1.0;
    /*private*/ bool animatingLayout; //true;
    /*private*/ bool showHelpBar; //true;
    /*private*/ bool drawGrid; //false;
    /*private*/ bool snapToGridOnAdd; //false;
    /*private*/ bool snapToGridOnMove; //false;
    /*private*/ bool antialiasingOn; //false;
    /*private*/ bool turnoutCirclesWithoutEditMode; //false;
    /*private*/ bool tooltipsWithoutEditMode; //false;
    /*private*/ bool tooltipsInEditMode; //true;
    // turnout size parameters - saved with panel
    /*private*/ double turnoutBX; //turnoutBXDefault;  // RH, LH, WYE
    /*private*/ double turnoutCX; //turnoutCXDefault;
    /*private*/ double turnoutWid; //turnoutWidDefault;
    /*private*/ double xOverLong; //xOverLongDefault;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
    /*private*/ double xOverHWid; //xOverHWidDefault;
    /*private*/ double xOverShort; //xOverShortDefault;

    // saved state of options when panel was loaded or created
    /*private*/ bool savedEditMode; //true;
    /*private*/ bool savedPositionable; //true;
    /*private*/ bool savedControlLayout; //true;
    /*private*/ bool savedAnimatingLayout; //true;
    /*private*/ bool savedShowHelpBar; //false;
    // Antialiasing rendering
//    /*private*/ static final RenderingHints antialiasing = new RenderingHints(
//            RenderingHints.KEY_ANTIALIASING,
//            RenderingHints.VALUE_ANTIALIAS_ON);
 QWidget* centralWidget;
 /*private*/ void setTooltipSubMenu();
 /*private*/ int multiLocX;
 /*private*/ int multiLocY;
 LayoutEditorTools tools = NULL;
 AddEntryExitPairAction entryExit = NULL;
 /*private*/ void setZoom(double factor) ;
 /*private*/ QPointF* windowCenter();
 /*private*/ void setupMarkerMenu(QMenuBar* menuBar);
 /*private*/ void setupZoomMenu(QMenuBar* menuBar);
 // operational variables for enter track width pane
 /*private*/ JmriJFrame enterTrackWidthFrame = NULL;
 /*private*/ bool enterWidthOpen = false;
 /*private*/ bool trackWidthChange = false;
 /*private*/ JTextField sideWidthField = new JTextField(6);
 /*private*/ JTextField mainlineWidthField = new JTextField(6);
 /*private*/ JButton trackWidthDone;
 /*private*/ JButton trackWidthCancel;
 // operational variables for enter reporter pane
 /*private*/ JmriJFrame enterReporterFrame = NULL;
 /*private*/ bool reporterOpen = false;
 /*private*/ JTextField xPositionField = new JTextField(6);
 /*private*/ JTextField yPositionField = new JTextField(6);
 /*private*/ JTextField reporterNameField = new JTextField(6);
 /*private*/ JButton reporterDone;
 /*private*/ JButton reporterCancel;
 // operational variables for scale/translate track diagram pane
 /*private*/ JmriJFrame scaleTrackDiagramFrame = NULL;
 /*private*/ bool scaleTrackDiagramOpen = false;
 /*private*/ JTextField xFactorField = new JTextField(6);
 /*private*/ JTextField yFactorField = new JTextField(6);
 /*private*/ JTextField xTranslateField = new JTextField(6);
 /*private*/ JTextField yTranslateField = new JTextField(6);
 /*private*/ JButton scaleTrackDiagramDone;
 /*private*/ JButton scaleTrackDiagramCancel;
 // operational variables for move selection pane
 /*private*/ JmriJFrame moveSelectionFrame = NULL;
 /*private*/ bool moveSelectionOpen = false;
 /*private*/ JTextField xMoveField = new JTextField(6);
 /*private*/ JTextField yMoveField = new JTextField(6);
 /*private*/ JButton moveSelectionDone;
 /*private*/ JButton moveSelectionCancel;
 /*private*/ bool canUndoMoveSelection = false;
 /*private*/ double undoDeltaX = 0.0;
 /*private*/ double undoDeltaY = 0.0;
 /*private*/ Rectangle2D undoRect;
 /*
  * Get mouse coordinates and adjust for zoom
  */
 /*private*/ void calcLocation(MouseEvent* event, int dX, int dY);
 /*private*/ bool checkSelect(QPointf loc, bool requireUnconnected);
 /*private*/ TrackSegment* checkTrackSegments(QPointF loc);
 /*private*/ PositionableLabel* checkBackgrounds(QPointF loc);
 /*private*/ SensorIcon* checkSensorIcons(QPointF loc);
 /*private*/ SignalHeadIcon* checkSignalHeadIcons(QPointF loc);
 /*private*/ SignalMastIcon checkSignalMastIcons(QPointF loc);
 /*private*/ PositionableLabel* checkLabelImages(QPointF loc);
 /*private*/ AnalogClock2Display* checkClocks(QPointF loc);
 /*private*/ MultiSensorIcon* checkMultiSensors(QPointF loc);
 /*private*/ LocoIcon* checkMarkers(QPointF loc);
 /*private*/ void checkPopUp(MouseEvent* event);
 /*private*/ long whenReleased = 0;  // used to identify event that was popup trigger
 /*private*/ bool awaitingIconChange = false;
 /*private*/ QVector<LayoutTurnout*> _turnoutSelection = NULL; //new QVector<LayoutTurnout>();  // LayoutTurnouts
 /*private*/ QVector<PositionablePoint*> _pointSelection = NULL; //new QVector<PositionablePoint>();  // PositionablePoint list
 /*private*/ QVector<LevelXing*> _xingSelection = NULL; //new QVector<LevelXing>();  // LevelXing list
 /*private*/ QVector<LayoutSlip*> _slipSelection = NULL; //new QVector<LevelXing>();  // LayoutSlip list
 /*private*/ QVector<LayoutTurntable*> _turntableSelection = NULL; //new QVector<LayoutTurntable>(); // Turntable list
 /*private*/ QVector<Positionable*> _positionableSelection = NULL;
 /*private*/ void highLightSelection(Graphics2D* g);
 /*private*/ void deleteSelectedItems();
 bool noWarnGlobalDelete = false;
 /*private*/ void amendSelectionGroup(Positionable* p);
 /*private*/ void amendSelectionGroup(LayoutTurnout* p);
 /*private*/ void amendSelectionGroup(PositionablePoint* p);

 /*private*/ void amendSelectionGroup(LevelXing* p);

 /*private*/ void amendSelectionGroup(LayoutSlip* p);
 /*private*/ void amendSelectionGroup(LayoutTurntable* p);
 /*private*/ double returnNewXPostition(KeyEvent* e, double val);
 /*private*/ double returnNewYPostition(KeyEvent* e, double val);
 int _prevNumSel = 0;
 /*private*/ bool isDragging = false;
 /*private*/ void updateLocation(QObject* o,int pointType,QPointF newPos);
 /**
  * Adds a link in the 'to' object to the 'from' object
  */
 /*private*/ void setLink(QObject* fromObject,int fromPointType,
                                         QObject* toObject,int toPointType);

 protected:
 /**
  * Remove a background image from the list of background images
  */
// /*protected*/ void removeBackground(PositionableLabel* b) ;
 /**
  * Remove a Layout Turntable
  */
// /*protected*/ bool removeTurntable (LayoutTurntable* o) ;
 /**
  * Remove a Track Segment
  */
 /*protected*/ void removeTrackSegment(TrackSegment* o) ;
 /*protected*/ void targetWindowClosingEvent(WindowEvent* e);
 void setupToolsMenu(QMenuBar* menuBar);
 /*protected*/ /*JMenu*/QMenu setupOptionMenu(QMenuBar* menuBar) ;
 /**
  * Remove marker icons from panel
  */
 /*protected*/ void removeMarkers();
 // display dialog for entering track widths
 /*protected*/ void enterTrackWidth();
 void trackWidthDonePressed(ActionEvent a);
 void trackWidthCancelPressed(ActionEvent a);
 // display dialog for entering Reporters
 /*protected*/ void enterReporter(int defaultX, int defaultY);
 void reporterDonePressed(ActionEvent a);
 void reporterCancelPressed(ActionEvent a);
 // display dialog for scaling the track diagram
 /*protected*/ void scaleTrackDiagram();
 void scaleTrackDiagramDonePressed(ActionEvent a);
 void scaleTrackDiagramCancelPressed(ActionEvent a) ;
 bool translateTrack (float xDel, float yDel);
 bool scaleTrack (float xFactor, float yFactor);
 // display dialog for translation a selection
 /*protected*/ void moveSelection();
 void moveSelectionDonePressed(ActionEvent a);
 void moveSelectionCancelPressed(ActionEvent a);
 void undoMoveSelection();
 /*protected*/ void setOptionMenuTrackColor();
 void addTurnoutCircleColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  Color color);
 void addTurnoutCircleSizeMenuEntry(/*JMenu*/QMenu menu,  QString name,  int size);
 /*protected*/ void setOptionMenuTurnoutCircleColor();
 /*protected*/ void setOptionMenuTurnoutCircleSize();
 /*protected*/ void setOptionMenuTextColor();
 /*protected*/ void setOptionMenuBackgroundColor();
 /**
 * Select the menu items to display for the Positionable's popup
 */
 /*protected*/ void showPopUp(Positionable* p, MouseEvent* event);

};

#endif // LAYOUTEDITOR_H
