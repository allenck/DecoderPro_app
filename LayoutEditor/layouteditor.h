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
#include "lememoryicon.h"
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
//#include "jmribeancombobox.h"
#include <QPen>
#include "borderlayout.h"
#include "mathutil.h"
#include "jtextfield.h"
#include "layouttrack.h"

namespace Ui {
class LayoutEditor;
}

class ToolBarSide;
class EditToolBarContainerPanel;
class NamedBeanComboBox;
class LEBlockContentsIcon;
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
class LayoutEditorToolBarPanel;
class LayoutShape;
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
    /*public*/ LayoutEditorToolBarPanel* getLayoutEditorToolBarPanel();

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

    enum TOOLBARSIDES
    {
       eTOP, //("top"),
       eLEFT, //("left"),
       eBOTTOM, //("bottom"),
       eRIGHT, //("right"),
       eFLOAT //("float");
    };

    /*public*/ void addAnchor();
    /*public*/ void addEndBumper();
    /*public*/ void addTrackSegment();
    /*public*/ void addLevelXing();
    /*public*/ void addLayoutSlip(int type);
    /*public*/ void addLayoutTurnout(int type);
    LayoutTurnout* addLayoutTurnout(QString name, int type, double rot, QPointF currentPoint);
    /*public*/ bool validatePhysicalTurnout(QString inTurnoutName, QWidget* openPane = 0);
    /*public*/ QVector<SensorIcon*>* sensorImage;// = new QVector<SensorIcon*>();  // sensor images
    /*public*/ QVector<LayoutTurntable*>* turntableList;// = new QVector<LayoutTurntable>(); // Turntable list
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
    /*public*/ QString getDefaultTrackColor();
    /*public*/ QString getDefaultOccupiedTrackColor();
    /*public*/ QString getDefaultAlternativeTrackColor();
    /*public*/ QString getDefaultTextColor();
    /*public*/ QString getTurnoutCircleColor();
    /*public*/ QString getTurnoutCircleThrownColor();
    /*public*/ bool isTurnoutFillControlCircles();


    /*public*/ int getTurnoutCircleSize();
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
    /*public*/ QVector<LEMemoryIcon*>* memoryLabelList;// = new QVector<MemoryIcon*>(); // Memory Label List
    /*public*/ /*transient*/ QVector<LEBlockContentsIcon*>* blockContentsLabelList;// = new ArrayList<>(); //BlockContentsIcon Label List

    void repaint();
    /*public*/ bool isEditable();
    /**
    *  Control whether target panel items are controlling layout items.
    *  Does this by invoke the {@link Positionable#setControlling} function of
    *  each item on the target panel. This also controls the relevant pop-up menu items.
    * @param state true for controlling.
    */
    /*public*/ bool isAnimating();
    /*public*/ int getLayoutWidth() ;
    /*public*/ int getLayoutHeight() ;
    /*public*/ int getWindowWidth() ;
    /*public*/ int getWindowHeight() ;
    /*public*/ int getUpperLeftX() ;
    /*public*/ int getUpperLeftY() ;
    QT_DEPRECATED /*public*/ bool getScroll();
    /*public*/ int setGridSize(int newSize);
    /*public*/ int getGridSize();
    /*public*/ int setGridSize2nd(int newSize);
    /*public*/ int getGridSize2nd();
    /*public*/ /*const*/ int getAnchorX();
    /*public*/ /*const*/ int getAnchorY();
//    /*public*/ bool allPositionable();
    /*public*/ bool allControlling() ;
    /*public*/ bool setShowAlignmentMenu(QMenu* popup);
    /*public*/ bool deletePanel();

    QGraphicsView* panel();
    /**
    * Add a label to the Draw Panel
    */
    void addLabel();
    void drawLabelImages(EditScene* g2);
    /*public*/ void putItem(Positionable *l);
    EditScene* getScene() {return editScene;}
    /*public*/ void putSensor(SensorIcon* l);
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
    LEMemoryIcon* addMemory(QString text);
    void addBlockContents();

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
    void addReporter(Reporter *textReporter, int xx, int yy);
//    /*public*/ PositionableLabel* setUpBackground(QString name);
    QT_DEPRECATED void setDefaultTextColor(QString sColor);
    void setDefaultTextColor(QColor sColor);
    /*public*/ void setDefaultBackgroundColor(QString color);
    /*public*/ QString getLayoutName();
    /*public*/ bool getShowHelpBar();
    QT_DEPRECATED bool getDrawGrid();
    QT_DEPRECATED bool getSnapOnAdd();
    QT_DEPRECATED bool getSnapOnMove();
    bool getAntialiasingOn();
    /*public*/ bool getHighlightSelectedBlock();
    /*public*/ void setLayoutName(QString name);
    void setDrawGrid(bool state);
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
    /*public*/ MultiIconEditor* signalIconEditor = nullptr;
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
    /*public*/ bool getDirectTurnoutControl();
    /*public*/ void setMainlineTrackWidth(int w);
    /*public*/ void setSideTrackWidth(int w);
    QT_DEPRECATED/*public*/ void setTurnoutCircleColor(QString color);
    /*public*/ void setTurnoutCircleColor(QColor color);
    /*public*/ void setTurnoutCircleThrownColor(/*@CheckForNull*/ QColor color);
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
    /*public*/ void setSnapOnAdd(bool state);
    /*public*/ void setSnapOnMove(bool state);
    /*public*/ void setAntialiasingOn(bool state);
    /*public*/ void setAutoBlockAssignment(bool boo);
    /*public*/ void setScroll(int state);
    /*public*/ void setConnections();
    /*public*/ /*@Nonnull*/ QRectF layoutEditorControlRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ /*@Nonnull*/ QRectF layoutEditorControlCircleRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ LayoutEditorFindItems* finder;// = new LayoutEditorFindItems(this);
    /*public*/ LayoutEditorFindItems* getFinder();
    void setDirty(bool b = true);
    /*public*/ void addTurntable(QPointF pt);
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
    /*public*/ LayoutTrackDrawingOptions* getLayoutTrackDrawingOptions();
    /*public*/ void setLayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo);
    /*public*/ static void setupComboBox(/*@Nonnull*/ NamedBeanComboBox *inComboBox, bool inValidateMode, bool inEnable);
    /*public*/ static void setupComboBox(/*@Nonnull*/ NamedBeanComboBox* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank);
    /*public*/ QRectF unionToPanelBounds(/*@Nonnull*/ QRectF bounds);
    /*public*/ QRectF getPanelBounds();
    /*public*/ bool highlightBlock(/*@Nullable*/ Block* inBlock);
    /*public*/ void setPanelBounds(QRectF newBounds);
    /*public*/ double setZoom(double zoomFactor);
    /*public*/ double getZoom();
    ///*public*/ static QPointF zeroPoint2D();
    /*public*/ QVector<SignalHeadIcon*>* signalList;// = new QVector<SignalHeadIcon*>();  // Signal Head Icons
    /*public*/ QVector<SignalMastIcon*>* signalMastList;// = new QVector<SignalMastIcon*>();  // Signal Head Icons
    /*private*/ /*transient*/ QList<LayoutShape*>* layoutShapes;// = new ArrayList<>();               // LayoutShap list

    /*public*/ QVector<MultiSensorIcon*>* multiSensors; // = new QVector<MultiSensorIcon*>(); // MultiSensor Icons
    /*public*/ void dispose();
    /*public*/ QList<PositionablePoint *> getPositionablePoints();
    /*public*/ QList<LayoutSlip *> getLayoutSlips();
    /*public*/ QList<TrackSegment *> getTrackSegments();
    /*public*/ QList<LayoutTurnout *> getLayoutTurnouts();
    /*public*/ QList<LayoutTurntable *> getLayoutTurntables();
    /*public*/ QList<LevelXing*> getLevelXings();
    /*public*/ QList<LayoutTrack*>* getLayoutTracks();
    /*public*/ QList<LayoutTurnout*>* getLayoutTurnoutsAndSlips();
    /*public*/ /*@Nonnull*/ QList<LayoutShape *> *getLayoutShapes();
    /*public*/ void sortLayoutShapesByLevel();
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
    /*public*/ void rotateSelection90();
    /*public*/ void rotateLayout90();
    /*public*/ void alignLayoutToGrid();
    /*public*/ void alignSelectionToGrid() ;
    /*public*/ void translate(float xTranslation, float yTranslation);


public slots:
    /*public*/ void on_setIncludedTurnoutSkipped(bool boo);
    void on_locationItem();
    /*public*/ void on_setTurnoutAnimation(bool state) ;
    /*public*/ void on_setDirectTurnoutControl(bool boo);
    /**
    *  Control whether target panel items are editable.
    *  Does this by invoke the {@link Positionable#setEditable(bool)} function of
    *  each item on the target panel. This also controls the relevant pop-up menu items
    *  (which are the primary way that items are edited).
    * @param state true for editable.
    */
    /*public*/ void setAllEditable(bool editable);
    /*public*/ void on_setAllEditable(bool state);
    /*public*/ void setShowHelpBar(bool state);
    void on_deletePanel();
    void on_colorBackgroundMenuItemSelected();
    void on_editTitle();

private:
 Ui::LayoutEditor *ui;
 //Operational instance variables - not saved to disk
 /*private*/ /*transient*/ JmriJFrame* floatingEditToolBoxFrame = nullptr;
 /*private*/ /*transient*/ QScrollArea* floatingEditContentScrollPane = nullptr;
 /*private*/ /*transient*/ JPanel* floatEditHelpPanel = nullptr;
 /*private*/ /*transient*/ EditToolBarContainerPanel* editToolBarContainerPanel = nullptr;
 /*private*/ /*transient*/ QScrollArea* editToolBarScrollPane = nullptr;
 /*private*/ /*transient*/ JPanel* helpBarPanel = nullptr;
 // /*private*/ /*transient*/ JPanel* helpBar;// = new JPanel();
 /*private*/ /*transient*/ bool editorUseOldLocSize;
 /*private*/ /*transient*/ LayoutEditorToolBarPanel* leToolBarPanel = nullptr;

 //end of main panel controls
 /*private*/ /*transient*/ bool delayedPopupTrigger = false;
 /*private*/ /*transient*/ QPointF currentPoint;// = new Point2D.Double(100.0, 100.0);
 /*private*/ /*transient*/ QPointF dLoc;// = new Point2D.Double(0.0, 0.0);

 /*private*/ /*transient*/ int toolbarHeight = 100;
 /*private*/ /*transient*/ int toolbarWidth = 100;

 /*private*/ /*transient*/ TrackSegment* newTrack = nullptr;
 /*private*/ /*transient*/ bool panelChanged = false;

 /*private*/ /*transient*/ int gridSize1st = 10;    //grid size in pixels
 /*private*/ /*transient*/ int gridSize2nd = 10;    // secondary grid

 /*private*/ /*transient*/ double selectionX = 0.0;
 /*private*/ /*transient*/ double selectionY = 0.0;

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
 QActionGroup* turnoutCircleSizeButtonGroup;

 /*private*/ /*transient*/ bool turnoutDrawUnselectedLeg = true;
 /*private*/ /*transient*/ bool autoAssignBlocks = false;

 //Tools menu items
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

 /*private*/ /*transient*/ QMenu* undoTranslateSelectionMenuItem;// = new JMenuItem(Bundle.getMessage("UndoTranslateSelection"));
 /*private*/ /*transient*/ QMenu* assignBlockToSelectionMenuItem;// = new JMenuItem(Bundle.getMessage("AssignBlockToSelectionTitle") + "...");

 QPointF startDelta;
 /*private*/ /*transient*/ int selectedHitPointType = 0;         //hit point type within the selected object

 /*private*/ /*transient*/ QList<LayoutTrack*>* layoutTrackList;// = new ArrayList<>();         // LayoutTrack list

 // counts used to determine unique internal names
 /*private*/ /*transient*/ int numAnchors = 0;
 /*private*/ /*transient*/ int numEndBumpers = 0;
 /*private*/ /*transient*/ int numEdgeConnectors = 0;
 /*private*/ /*transient*/ int numTrackSegments = 0;
 /*private*/ /*transient*/ int numLevelXings = 0;
 /*private*/ /*transient*/ int numLayoutSlips = 0;
 /*private*/ /*transient*/ int numLayoutTurnouts = 0;
 /*private*/ /*transient*/ int numLayoutTurntables = 0;
 /*private*/ /*transient*/ int numShapes = 0;

 //persistent instance variables - saved to disk with Save Panel
 /*private*/ /*transient*/ int upperLeftX = 0; // Note: These are _WINDOW_ upper left x & y
 /*private*/ /*transient*/ int upperLeftY = 0; // (not panel)

 /*private*/ /*transient*/ int windowWidth = 0;
 /*private*/ /*transient*/ int windowHeight = 0;

 /*private*/ /*transient*/ QColor defaultTextColor = QColor(Qt::black);

 /*private*/ /*transient*/ QString layoutName = "";
 /*private*/ /*transient*/ double xScale = 1.0;
 /*private*/ /*transient*/ double yScale = 1.0;
 /*private*/ /*transient*/ bool animatingLayout = true;
 /*private*/ /*transient*/ bool showHelpBar = true;
 /*private*/ /*transient*/ bool drawGrid = true;

 /*private*/ /*transient*/ bool snapToGridOnAdd = false;
 /*private*/ /*transient*/ bool snapToGridOnMove = false;
 /*private*/ /*transient*/ bool snapToGridInvert = false;

 /*private*/ /*transient*/ bool tooltipsWithoutEditMode = false;
 /*private*/ /*transient*/ bool tooltipsInEditMode = true;

 //turnout size parameters - saved with panel
 /*private*/ /*transient*/ double turnoutBX = LayoutTurnout::turnoutBXDefault; //RH, LH, WYE
 /*private*/ /*transient*/ double turnoutCX = LayoutTurnout::turnoutCXDefault;
 /*private*/ /*transient*/ double turnoutWid = LayoutTurnout::turnoutWidDefault;
 /*private*/ /*transient*/ double xOverLong = LayoutTurnout::xOverLongDefault; //DOUBLE_XOVER, RH_XOVER, LH_XOVER
 /*private*/ /*transient*/ double xOverHWid = LayoutTurnout::xOverHWidDefault;
 /*private*/ /*transient*/ double xOverShort = LayoutTurnout::xOverShortDefault;
 /*private*/ /*transient*/ bool useDirectTurnoutControl = false; //Uses Left click for closing points, Right click for throwing.

 //saved state of options when panel was loaded or created
 /*private*/ /*transient*/ bool savedEditMode = true;
 /*private*/ /*transient*/ bool savedPositionable = true;
 /*private*/ /*transient*/ bool savedControlLayout = true;
 /*private*/ /*transient*/ bool savedAnimatingLayout = true;
 /*private*/ /*transient*/ bool savedShowHelpBar = true;

 //zoom
 /*private*/ /*transient*/ double minZoom = 0.25;
 /*private*/ /*transient*/ double maxZoom = 8.0;
 /*private*/ /*enum*/class ToolBarSide {

  TOOLBARSIDES type;
  /*private*/ /*transient*/ QString name;

 public:
     ToolBarSide(QString name) {
         this->name = name;
      this->type = getName(name);
     }
     ToolBarSide(TOOLBARSIDES type)
     {
      this->type = type;
      switch (type) {
      case eTOP:
       name = "top";
       break;
      case eLEFT:
       name = "left";
       break;
      case eRIGHT:
       name = "right";
       break;
      case eBOTTOM:
       name = "bottom";
       break;
      case eFLOAT:
      default:
       name = "float";
       break;
      }
     }

//     //Build an immutable map of String name to enum pairs.
//     static {
//         Map<String, ToolBarSide> map = new ConcurrentHashMap<>();

//         for (ToolBarSide instance : ToolBarSide.values()) {
//             map.put(instance.getName(), instance);
//         }
//         ENUM_MAP = Collections.unmodifiableMap(map);
//     }

     /*public*/ static TOOLBARSIDES getName(/*@Nullable*/ QString name) {
      if(name.toLower() == "top")
       return eTOP;
      else if (name.toLower() == "left")
       return eLEFT;
      else if (name.toLower() == "bottom")
       return eBOTTOM;
      else if (name.toLower() == "right")
       return eRIGHT;
      else //if (name == "float")
       return eFLOAT;
     }

     /*public*/ QString getName() {
         return name;
     }
     TOOLBARSIDES getType()
     {
      return type;
     }
 };
 /*private*/ /*transient*/ ToolBarSide toolBarSide = ToolBarSide("top");


 QButtonGroup* buttonGroup;

 // /*private*/ /*final*/ LayoutEditorComponent* layoutEditorComponent = new LayoutEditorComponent(this);


 int xLoc, yLoc;
 /*private*/ /*transient*/ /*final*/ static Logger* log;

 /*private*/ void calcLocation(QPointF pos, int dX, int dY);
 bool bIsEditable = true;
 /*private*/ void createSelectionGroups();
 bool isDragging = false;
 StoreXmlUserAction* savePanels;
 //bool bDirty;
 bool isDirty();
 void resetDirty();
 ///*private*/ QObject* beginObject;// = nullptr; // begin track segment connection object, NULL if none
 /*private*/ void setLink(QObject* fromObject,int fromPointType, QObject* toObject,int toPointType);
 LayoutEditorAuxTools* auxTools;
 // selection variables
 /*private*/ QVector<Positionable*>* _positionableSelection = nullptr;

 /*private*/ QVector<LayoutTurnout*>* _turnoutSelection = nullptr; //new QVector<LayoutTurnout>();  // LayoutTurnouts
 /*private*/ QVector<LevelXing*>* _xingSelection = nullptr; //new QVector<LevelXing>();  // LevelXing list
 /*private*/ QVector<LayoutSlip*>* _slipSelection = nullptr; //new QVector<LayoutSlip*>();  // LayoutSlip list
 /*private*/ QVector<LayoutTurntable*>* _turntableSelection = nullptr; //new ArrayList<LayoutTurntable>(); // Turntable list
 /*private*/ QVector<PositionablePoint*>* _pointSelection = nullptr; //new QVector<PositionablePoint>();  // PositionablePoint list
 QVector<PositionableLabel*>* _labelSelection; //new QVector<PositionableLabel>();  // PositionableLabel list
/*private*/ QList<LayoutTrack*>* getLayoutTracksOfClass(QString type);

  bool isDrawing = false;

 /*private*/ void clearSelectionGroups();
 QWidget* openFrame = this;

 /*private*/ void drawXings(EditScene* g2);

 // /*protected*/ void draw(EditScene* g2);
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
 /*private*/ void drawShapes(EditScene* g2, bool isBackground);
 /*private*/ void drawTrackSegmentInProgress(EditScene* g2);
 /*private*/ void drawShapeInProgress(EditScene* g2);
 /*private*/ void drawLayoutTrackEditControls(EditScene* g2);
 /*private*/ void drawShapeEditControls(EditScene* g2);
 /*private*/ void drawTurnoutControls(EditScene* g2);
 /*private*/ QRectF getSelectionRect();
 /*private*/ void drawSelectionRect(EditScene* g2);
 /*private*/ void drawMemoryRects(EditScene* g2);
 /*private*/ void drawBlockContentsRects(EditScene* g2);
 /*private*/ void amendSelectionGroup(Positionable* p);
 /*private*/ void amendSelectionGroup(LayoutTurnout* p);
 /*private*/ void amendSelectionGroup(PositionablePoint* p);
 /*private*/ void amendSelectionGroup(LevelXing* p);
 /*private*/ void amendSelectionGroup(LayoutTrack *p);
 bool main = true;
 bool _editable = false;
 friend class SensorIcon;
 InternalSensorManager* internalSensorManager;
 /*private*/ QPointF midpoint (QPointF p1,QPointF p2) ;
 /*protected*/ QPointF third (QPointF p1,QPointF p2) ;
 /*private*/ QPointF fourth (QPointF p1,QPointF p2);
 int _scrollState;
 int _anchorX = 0, _anchorY = 0;
 bool _positionable = false;
 int _lastX, _lastY;
 /*private*/ void drawPanelGrid(EditScene* g2);

// /*private*/ void drawTrackCircleCentre(EditScene* g2);
 double toRadians(double degrees);
 double toDegrees(double radians);
 /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event);
 bool _controlLayout= true;
 bool noWarnPositionablePoint = false;
 bool noWarnSlip = false;
 /*private*/ void disconnect(QObject* o, int type);
 ///*private*/ void drawMemoryRects(EditScene* g2);
 /**
 * Add a sensor indicator to the Draw Panel
 */
 void addSensor();

  bool bDirty = false;
  InstanceManager* instanceManager;
  /*private*/ bool _showCoordinates = true;
 Positionable* saveP;
 //bool selectedNeedsConnect;
 /*private*/ LocoIcon* checkMarkers(QPointF loc);
 /*private*/ MultiIconEditor* iconEditor;// = nullptr;
 QGraphicsItemGroup* panelGridGroup = nullptr;
 QGraphicsItem* trackInProgress = nullptr;
 /*private*/ bool _globalSetsLocal = true;    // pre 2.9.6 behavior
 /*private*/ bool _useGlobalFlag = false;     // pre 2.9.6 behavior
 QGraphicsRectItem *rectItem = nullptr; // selection rect.
 QGraphicsItemGroup* highlightRect = nullptr;

 /*private*/ void highLightSelection(EditScene* g);
 /*private*/ QRectF clipBounds = QRectF();
 bool noWarnGlobalDelete = false;
 bool noWarnLevelXing = false;
 bool noWarnLayoutTurnout;
 bool noWarnTurntable = false;
 QString _defaultToolTip = "";
 Positionable* currComp;
 LEMemoryIcon* checkMemoryMarkerIcons(QPointF loc);
 JFileChooser* inputFileChooser;
 bool _loadFailed = false;
 bool _debug = true;
 bool _ignore = false;
 QMap<QString, QString>* _urlMap;// = new QMap<QString, QString>();
 NamedIcon* _newIcon = nullptr;
 bool _delete = false;
 //QFormLayout* formLayout;
 RosterEntrySelectorPanel* rosterBox;
 //bool bTestMode;
 QString layoutFile;
 int _prevNumSel;
 LayoutEditorTools* tools = nullptr;
 JFrame* signalFrame;
 JFrame* sensorFrame;
 ConnectivityUtil* conTools;
 /*private*/ int multiLocX;
 /*private*/ int multiLocY;
 void startMultiSensor();
 MultiSensorIconFrame* multiSensorFrame = nullptr;
 void closeEvent(QCloseEvent *);
 bool openDispatcherOnLoad = false;
 JTextField* xMove;
 JTextField* yMove;
 /*private*/ void substituteAnchor(QPointF loc, QObject* o, TrackSegment* t);
 /*private*/ PositionablePoint* addAnchor(QPointF p);
 /*private*/ QPointF windowCenter();
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
 QSignalMapper* turnoutCircleSizeButtonMapper;
 QAction* turnoutDrawUnselectedLegItem;
 QAction* turnoutFillControlCirclesCheckBoxMenuItem = nullptr;
 QAction* useDirectTurnoutControlItem;
 /*private*/ int backgroundColorCount = 0;
 /*private*/ int trackColorCount = 0;
 /*private*/ int trackOccupiedColorCount = 0;
 /*private*/ int trackAlternativeColorCount = 0;
 /*private*/ int textColorCount = 0;
 /*private*/ int turnoutCircleColorCount = 0;
 /*private*/ int turnoutCircleSizeCount = 0;
 /*private*/ QVector<QColor>* backgroundColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackOccupiedColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* trackAlternativeColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* textColors = new QVector<QColor>(13);
 /*private*/ QVector<QColor>* turnoutCircleColors;// = new QVector<QColor>(14);
 /*private*/ QVector<int>* turnoutCircleSizes;// = new QVector<int>(10);
 /*private*/ void checkPointOfPositionable(PositionablePoint* p);
// /*private*/ void checkPointsOfTurnout(LayoutTurnout* lt);
// /*private*/ void checkPointsOfTurnoutSub(QPointF dLoc);
 /*private*/ void rotateTurnout(LayoutTurnout* t);
// void addBackgroundColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color);
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

 /*private*/ /*transient*/ LayoutTrackDrawingOptions* layoutTrackDrawingOptions = nullptr;
 /*private*/ /*transient*/ JFrame* iconFrame = nullptr;
 /*private*/ bool highlightBlockInComboBox(/*@Nonnull*/ NamedBeanComboBox *inComboBox);
 /*private*/ QRectF calculateMinimumLayoutBounds();
 /*private*/ QRectF resizePanelBounds(bool forceFlag);
 QLabel* zoomLabel;
 /*private*/ void selectZoomMenuItem(double zoomFactor);

 //grid size in pixels
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
 /*private*/ LayoutShape* checkLayoutShapePopUps(/*@Nonnull*/ QPointF loc);
 /*private*/ /*transient*/ LayoutTrackEditors* layoutTrackEditors = nullptr;
 /*private*/ /*transient*/ LayoutEditorChecks* layoutEditorChecks = nullptr;
 //operational variables for enter track width pane
 /*private*/ /*transient*/ JmriJFrame* enterTrackWidthFrame = nullptr;
 /*private*/ bool enterTrackWidthOpen = false;
 /*private*/ bool trackWidthChange = false;
 /*private*/ /*transient*/ JTextField* sidelineTrackWidthField = new JTextField(6);
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
 /*private*/ /*transient*/ NamedBean::DisplayOptions gDDMDO ;//= JmriBeanComboBox.DisplayOptions.DISPLAYNAME;
 /*private*/ /*transient*/ QList<LayoutTrack*> _layoutTrackSelection;// = new ArrayList<>();

 // /*private*/ void updateComboBoxDropDownListDisplayOrderFromPrefs(/*@Nonnull*/ Component* inComponent);
 // /*private*/ void updateDropDownMenuDisplayOrderMenu();
 ///*private*/ void updateAllComboBoxesDropDownListDisplayOrderFromPrefs();
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
 /*private*/ QPointF undoDelta = MathUtil::zeroPoint2D;

 /*private*/ double undoDeltaX = 0.0;
 /*private*/ double undoDeltaY = 0.0;
 /*private*/ /*transient*/ QRectF undoRect;
 QAction* skipTurnoutCheckBoxMenuItem;
 /*private*/ bool includedTurnoutSkipped = false;
 /*private*/ void setupMarkerMenu(/*@Nonnull*/ QMenuBar *menuBar);
 /*private*/ void setupDispatcherMenu(/*@Nonnull*/ QMenuBar* menuBar);
 /*private*/ void setupZoomMenu(QMenuBar* menuBar);



 /*private*/ float toolBarFontSize = 12.0;

 /*private*/ void setupToolBar();
 /*private*/ void createfloatingEditToolBoxFrame();
 /*private*/ void deletefloatingEditToolBoxFrame();
 /*private*/ void createFloatingHelpPanel();
 /*private*/ void setScrollbarScale(double ratio);

 //QHBoxLayout* editPanelLayout;
 BorderLayout* borderLayout = nullptr;
 /*private*/ void alignToGrid(QVector<Positionable *> positionables, QList<LayoutTrack*> tracks, QList<LayoutShape*> shapes);
 /*private*/ long whenReleased = 0; //used to identify event that was popup trigger
 /*private*/ bool awaitingIconChange = false;

 /*private*/ /*transient*/ bool toolBarIsWide = true;
 /*private*/ void on_setToolBarSide(QString);
 /*private*/ void setupMenuBar();


private slots:
 void on_scenePos(QGraphicsSceneMouseEvent*);
 /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
 /**
  * Handle a mouse pressed event
  */
 /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event);

 void on_actionShow_grid_in_edit_mode_toggled(bool bChecked);
 void on_actionEnable_antialiasing_smoother_lines_toggled(bool bChecked);
 void on_removeMenuAction_triggered();
 void on_actionAllow_layout_control_toggled(bool bChecked);
 /*private*/ void deleteSelectedItems(); // SLOT[]
 void on_actionHidden_toggled(bool bState);
 void on_actionAdd_reporter_label_triggered();
 void on_actionAdd_background_image_2_triggered();
 void on_actionSnap_to_grid_when_adding_toggled(bool bState);
 void on_actionSnap_to_grid_when_moving_toggled(bool bState);
 void on_defaultTextColorSelected();
 void on_actionSet_Signals_at_Block_Boundary_triggered();
 void on_actionSet_Signals_at_Turnout_triggered();
 void on_actionSet_Signals_at_Crossover_triggered();
 void on_actionSet_Signals_at_Level_Crossing_triggered();
 void on_actionAdd_Fast_Clock_triggered();
 void on_actionSet_Signals_at_Slip_triggered();
 void on_actionSet_Signals_at_Throat_to_Throat_Turnouts_triggered();
 void on_actionEntry_Exit_triggered();
 void on_actionAdd_Turntable_triggered();
 void on_turnoutCirclesOnItem_triggered(bool);
 void on_turnoutDrawUnselectedLegItem_triggered(bool);
 void on_actionSet_Signals_at_Three_Way_Turnout();
 void on_autoAssignBlocksItem_triggered(bool b);
 void on_hideTrackSegmentConstructionLines_toggled(bool);
 //void on_useDirectTurnoutControlItem_triggered(bool);
 void on_addTrackColorMenuEntry_triggered();
 void on_addTrackOccupiedColorMenuEntry_triggered();
 void on_addTrackAlternativeColorMenuEntry_triggered(/*int*/);
 void on_actionBoth_scrollbars();
 void on_actionNo_scrollbars();
 void on_actionHorizontal_scrollbars();
 void on_actionVertical_scrollbars();
 /*private*/ double on_zoomIn();
 /*private*/ double on_zoomOut();
 double on_zoomToFit();
 void on_layoutTrackDrawingOptionsDialog();
 void on_clearTrack(); // for testing
 void on_translateSelections();
 void moveSelectionCancelPressed();
 void moveSelectionDonePressed(/*@Nonnull ActionEvent event*/);
 void on_NewTrain();
 void on_Zoom025Item();
 void on_Zoom05Item();
 void on_Zoom075Item();
 void on_NoZoomItem();
 void on_Zoom15Item();
 void on_Zoom20Item();
 void on_Zoom30Item();
 void on_Zoom40Item();
 /*private*/ void on_resetTurnoutSize();
 void on_TurnoutCircleColorMenuItem();
 void on_turnoutCircleThrownColorMenuItem();
 void on_TooltipNoneMenuItem();
 void on_TooltipAlwaysMenuItem();
 void on_TooltipInEditMenuItem();
 void on_TooltipNotInEditMenuItem();
 /*private*/ void on_setToolBarSide(QAction* act);
 /*private*/ void on_setToolBarWide(bool newToolBarIsWide);
 /*private*/ void on_turnoutFillControlCirclesCheckBoxMenuItem(bool checked);

protected:
 //size of point boxes
 /*protected*/ static /*final*/ const double SIZE;// = 3.0;
 /*protected*/ static /*final*/ const double SIZE2;// = SIZE * 2.; //must be twice SIZE

 /*protected*/ QColor turnoutCircleColor = QColor(Qt::black); //matches earlier versions
 /*protected*/ QColor turnoutCircleThrownColor= QColor(Qt::black);
 /*protected*/ bool turnoutFillControlCircles = false;
 /*protected*/ int turnoutCircleSize = 4; //matches earlier versions

 //use turnoutCircleSize when you need an int and these when you need a double
 //note: these only change when setTurnoutCircleSize is called
 //using these avoids having to call getTurnoutCircleSize() and
 //the multiply (x2) and the int -> double conversion overhead
 /*protected*/ /*transient*/ double circleRadius;// = SIZE * getTurnoutCircleSize();
 /*protected*/ /*transient*/ double circleDiameter;// = 2.0 * circleRadius;

 //selection variables
 /*protected*/ /*transient*/ bool selectionActive = false;
 /*protected*/ /*transient*/ double selectionWidth = 0.0;
 /*protected*/ /*transient*/ double selectionHeight = 0.0;

 /*protected*/ /*transient*/ QObject* selectedObject = nullptr;       //selected object, null if nothing selected
 /*protected*/ /*transient*/ QObject* prevSelectedObject = nullptr;   //previous selected object, for undo

 /*protected*/ /*transient*/ LayoutTrack* foundTrack = nullptr;      //found object, null if nothing found
 /*protected*/ /*transient*/ QPointF foundLocation;// = new Point2D.Double(0.0, 0.0); //location of found object
 /*protected*/ /*transient*/ int foundHitPointType = 0;          //connection type within the found object
 ///private transient boolean foundNeedsConnect = false;    //true if found point needs a connection

 /*protected*/ /*transient*/ LayoutTrack* beginTrack = nullptr;      //begin track segment connection object, null if none
 /*protected*/ /*transient*/ QPointF beginLocation = QPointF(0.0, 0.0); //location of begin object
 /*protected*/ /*transient*/ int beginHitPointType = LayoutTrack::NONE; //connection type within begin connection object

 /*protected*/ /*transient*/ QPointF currentLocation;// = new Point2D.Double(0.0, 0.0); //current location

 /*protected*/ /*transient*/ int panelWidth = 0;
 /*protected*/ /*transient*/ int panelHeight = 0;

 /*protected*/ /*transient*/ float mainlineTrackWidth = 4.0F;
 /*protected*/ /*transient*/ float sidelineTrackWidth = 2.0F;

 /*protected*/ /*transient*/ QColor mainlineTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor sidelineTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor defaultTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor defaultOccupiedTrackColor = QColor(Qt::red);
 /*protected*/ /*transient*/ QColor defaultAlternativeTrackColor = QColor(Qt::white);

 /*protected*/ /*transient*/ bool antialiasingOn = false;
 /*protected*/ /*transient*/ bool highlightSelectedBlockFlag = false;

 /*protected*/ /*transient*/ bool turnoutCirclesWithoutEditMode = false;

 /**
 * Return a List of all items whose bounding rectangle contain the mouse position.
 * ordered from top level to bottom
 */
 /*protected*/ QList <Positionable*> getSelectedItems(QGraphicsSceneMouseEvent* event);
 ///*protected*/ QVector <Positionable*>* _contents;// = new QVector<Positionable*>();
 void init();
 /*protected*/ double _paintScale = 1.0;   // scale for _targetPanel drawing
 #if 0
 /*protected*/ static QPointF getCoords(QObject* o, int type);
#endif
 /*public*/ QGraphicsEllipseItem* trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint);
 //compute the turnout circle at inPoint (used for drawing)
 /*public*/ QGraphicsEllipseItem* trackControlCircleAt(/*@Nonnull */QPointF inPoint);
 /**
 *  Special internal class to allow drawing of layout to a JLayeredPane
 *  This is the 'target' pane where the layout is displayed
 */
 /*protected*/ void paintTargetPanel(EditScene* g2);
 // /*protected*/ void setTrackStrokeWidth(bool need);
 /**
 * Select the menu items to display for the Positionable's popup
 */
// /*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*public*/ void alignSelection(bool alignX);
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
 /*protected*/ void setSelectionsScale(double s, Positionable* p);
 /*protected*/ void setSelectionsRotation(int k, Positionable* p);
 friend class CoordinateEdit;
 /*protected*/ void removeSelections(Positionable* p);
 /*protected*/ void setSelectionsHidden(bool enabled, Positionable* p);
 ///*protected*/ void makeBackgroundColorMenu(QMenu* colorMenu);
// /*protected*/ void addBackgroundColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup, const QString name, QColor color);
 /*protected*/ bool removeLayoutSlip (LayoutTurnout* o);
// /*protected*/ LocoIcon* selectLoco(QString rosterEntryTitle);
// /*protected*/ LocoIcon* selectLoco(RosterEntry* entry);
 /*protected*/ bool skipIncludedTurnout = false;
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
 /*protected*/ void enterReporter(int defaultX, int defaultY);
 /*protected*/ void showPopUp(/*@Nonnull*/ Positionable* p, /*@Nonnull */QGraphicsSceneMouseEvent* event);
 /*protected*/ QMenu* setupOptionMenu(/*@Nonnull*/ QMenuBar* menuBar);
// /*protected*/ /*final*/ void setPaintScale(double newScale);
 /*protected*/ LayoutShape* addLayoutShape(/*@Nonnull*/ QPointF p);
 /*protected*/ bool removeLayoutShape(/*@Nonnull*/ LayoutShape* s);
 /*protected*/ void amendSelectionGroup(/*@Nonnull*/ LayoutShape* ls);
 /*protected*/ /*transient*/ QList<LayoutShape*> _layoutShapeSelection;// = new ArrayList<>();

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

 /*protected*/ void enterGridSizes();

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
friend class LayoutEditorToolBarPanel;
friend class LayoutShape;
friend class EditToolBarContainerPanel;
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

class EditToolBarContainerPanel : public QWidget
{
 Q_OBJECT
 LayoutEditor* editor;
public:
 EditToolBarContainerPanel(LayoutEditor* editor, QWidget* parent = nullptr) : QWidget(parent)
 {
  this->editor = editor;
 }
 void setVisible(bool visible)
 {
  bool isVisible = QWidget::isVisible();
  QObject* p = parent();
  if(visible == isVisible)
   return;
  QWidget::setVisible(visible);
  if(visible && editor->borderLayout)
  {
   editor->borderLayout->removeWidget(this);
   switch (editor->toolBarSide.getType()) {
    case LayoutEditor::eTOP:
     editor->borderLayout->addWidget(this, BorderLayout::North);
     break;
    case LayoutEditor::eBOTTOM:
     editor->borderLayout->addWidget(this, BorderLayout::South);
     break;
    case LayoutEditor::eLEFT:
     editor->borderLayout->addWidget(this, BorderLayout::West);
     break;
    case LayoutEditor::eRIGHT:
     editor->borderLayout->addWidget(this, BorderLayout::East);
     break;
    default:
     break;
    }
   }
   else
    editor->borderLayout->removeWidget(this);
  }

};
#endif // LAYOUTEDITOR_H
