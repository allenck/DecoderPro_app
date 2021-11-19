#ifndef LAYOUTEDITOR_H
#define LAYOUTEDITOR_H

#include "editor.h"
#include <QButtonGroup>
#include <QGraphicsView>
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
#include <QPen>
#include "borderlayout.h"
#include "mathutil.h"
#include "jtextfield.h"
#include "layouttrack.h"
#include "layouteditorviewcontext.h"
#include "jcheckboxmenuitem.h"
#include "storexmluseraction.h"
#include "layouteditorfinditems.h"
#include "jradiobuttonmenuitem.h"
#include "popupmenulistener.h"
#include "popupmenuevent.h"
#include "namedbeancombobox.h"
//#include "layoutmodels.h"
#include "layoutslipview.h"
#include "layouteditorviewcontext.h"
#include "levelxing.h"
#include "tracksegmentview.h"
#include "layoutturntableview.h"
#include "levelxingview.h"
#include "path.h"

enum TOOLBARSIDES
{
   eTOP, //("top"),
   eLEFT, //("left"),
   eBOTTOM, //("bottom"),
   eRIGHT, //("right"),
   eFLOAT //("float");
};

/*private*/ /*enum*/class ToolBarSide  : public QObject
{

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

class TurnoutComboBoxPopupMenuListener;
class LayoutEditorComponent;
class PositionablePointView;
class LayoutTrackView;
class AddEntryExitPairAction;
//class ToolBarSide;
class EditToolBarContainerPanel;
class NamedBeanComboBox;
class LEBlockContentsIcon;
class LayoutEditorChecks;
//class LayoutTrackEditors;
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
class TrackSegmentView;
class PositionablePoint;
class LevelXing;
class LevelXingView;
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

class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditor : public PanelEditor//, public LayoutModels
{
 Q_OBJECT
 //Q_INTERFACES(LayoutModels)
    friend class LayoutTurnout;
    friend class LayoutEditorAuxTools;
    friend class LevelXing;
    friend class LayoutBlock;
public:
 explicit LayoutEditor(QString name = "My Layout", QWidget *parent = 0);
//    LayoutEditor(LocoNetSystemConnectionMemo* memo, QString name = "My Layout", bool bTest = false, QWidget *parent=0);
 ~LayoutEditor();
    LayoutEditor(const LayoutEditor&) : PanelEditor() {}
    /*public*/ void newPanelDefaults() override;
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
    /*public*/ /*final*/ LayoutEditorViewContext* gContext = new LayoutEditorViewContext(); // public for now, as things work access changes
    /*public*/ QList<PositionableLabel*> getLabelImageList();
    /*public*/ void addAnchor();
    /*public*/ void addEndBumper();
    /*public*/ void addTrackSegment();
    /*public*/ void addLevelXing();
    /*public*/ void addLayoutSlip(LayoutTurnout::TurnoutType type);
    /*public*/ void addLayoutTurnout(LayoutTurnout::TurnoutType type);
    /*public*/ bool validatePhysicalTurnout(QString inTurnoutName, QWidget* openPane = 0);
    /*public*/ QVector<SensorIcon*>* sensorImage = new QVector<SensorIcon*>();  // sensor images
    /*public*/ QVector<LayoutTurntable*>* turntableList = new QVector<LayoutTurntable*>(); // Turntable list
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
    /*public*/ bool validateSensor(QString sensorName, LayoutBlock* blk, QWidget *openFrame);
    /*public*/ void setTooltipsNotEdit(bool state);
    /*public*/ void setTooltipsInEdit(bool state);

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
    /*public*/ QString getDefaultTrackColor();
    /*public*/ QColor getDefaultTrackColorColor();
    /*public*/ QString getDefaultOccupiedTrackColor();
    /*public*/ QColor getDefaultOccupiedTrackColorColor();
    /*public*/ QString getDefaultAlternativeTrackColor();
    /*public*/ QColor getDefaultAlternativeTrackColorColor();
    /*public*/ QString getDefaultTextColor();
    /*public*/ QString getTurnoutCircleColor();
    /*public*/ QString getTurnoutCircleThrownColor();
    /*public*/ bool isTurnoutFillControlCircles();

    /*public*/ int getTurnoutCircleSize();
    /*public*/ bool isTurnoutDrawUnselectedLeg();

    /*public*/ LayoutBlock* getAffectedBlock(QObject* o, int type);
    /*public*/ QVector<LEMemoryIcon*>* memoryLabelList = new QVector<LEMemoryIcon*>(); // Memory Label List
    /*public*/ /*transient*/ QVector<LEBlockContentsIcon*>* blockContentsLabelList = new QVector<LEBlockContentsIcon*>(); //BlockContentsIcon Label List

    void repaint() override;
    /*public*/ bool isEditable();
    /**
    *  Control whether target panel items are controlling layout items.
    *  Does this by invoke the {@link Positionable#setControlling} function of
    *  each item on the target panel. This also controls the relevant pop-up menu items.
    * @param state true for controlling.
    */
    /*public*/ bool isAnimating();
    QT_DEPRECATED /*public*/ bool getScroll();
    /*public*/ /*const*/ int getAnchorX();
    /*public*/ /*const*/ int getAnchorY();
    /*public*/ bool allControlling() ;
    /*public*/ bool setShowAlignmentMenu(QMenu* popup);
    /*public*/ bool deletePanel();

    /**
    * Add a label to the Draw Panel
    */
    void addLabel();
    /*public*/ void putItem(Positionable *l) override;
    EditScene* getScene() {return editScene;}
    /*public*/ void putSensor(SensorIcon* l);
    void redrawPanel() override { paintTargetPanel(editScene);}
    /**
    * Display the X & Y coordinates of the Positionable item and provide a
    * dialog memu item to edit them.
    */
    /*public*/ QVector<SensorIcon*>* sensorList = new QVector<SensorIcon*>();  // Sensor Icons
    /*public*/ QVector<LocoIcon*>* markerImage = new QVector<LocoIcon*>(); // marker images
    /*public*/ void setAllPositionable(bool state);
    /*public*/ void setLayoutDimensions(int windowWidth, int windowHeight, int windowX, int windowY, int panelWidth, int panelHeight);
    /*public*/ void setLayoutDimensions(int windowW, int windowH, int x, int y, int panelW, int panelH, bool merge);

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
    /**
     * Add a Reporter Icon to the panel
     */
    void addReporter(Reporter *textReporter, int xx, int yy);
    void setDefaultTextColor(QColor sColor);
    /*public*/ void setDefaultBackgroundColor(QColor color);
    /*public*/ QString getLayoutName();
    /*public*/ bool getShowHelpBar();
    QT_DEPRECATED bool getDrawGrid();
    QT_DEPRECATED bool getSnapOnAdd();
    QT_DEPRECATED bool getSnapOnMove();
    bool getAntialiasingOn();
    /*public*/ bool isDrawLayoutTracksLabel();
    /*public*/ bool getHighlightSelectedBlock();
    /*public*/ bool getTurnoutCircles();
    /*public*/ bool getTooltipsNotEdit();
    /*public*/ bool getTooltipsInEdit();
    /*public*/ bool getAutoBlockAssignment();
    /*public*/ void setLayoutName(QString name);
    void setDrawGrid(bool state);
    void addSignalHead();
    /*public*/ void putSignal(SignalHeadIcon* l);
    SignalHead* getSignalHead(QString name) ;
    void addSignalMast() ;
    /*public*/ void putSignalMast(SignalMastIcon* l) ;
    SignalMast* getSignalMast(QString name);
    /*public*/ bool containsSignalMast(/*@Nonnull*/ SignalMast* mast);
    /*public*/ ConnectivityUtil* getConnectivityUtil();
    /*public*/ LayoutEditorTools* getLETools();
    /*public*/ LayoutEditorAuxTools* getLEAuxTools();
    /*public*/ LayoutEditorChecks* getLEChecks();
    /*public*/ void addToPopUpMenu(NamedBean* nb, QMenu* item, int menu);
    QString toString();
    /*public*/ void vetoableChange(
            /*@Nonnull*/ PropertyChangeEvent* evt) override
            /*throw (PropertyVetoException)*/;
    /*public*/ void addMultiSensor(MultiSensorIcon* l);
    /*public*/ void setNextLocation(/*@Nonnull*/ Positionable* obj) override;
    /*public*/ void setSize(int w, int h);
    /*public*/ LocoIcon* addLocoIcon (QString name);
    /*public*/ void putLocoIcon(LocoIcon* l, QString name);
    /*public*/ void setCurrentPositionAndSize();
    /*public*/ bool getDirectTurnoutControl();
    /*public*/ void setTurnoutCircleColor(QColor color);
    /*public*/ void setTurnoutCircleThrownColor(/*@CheckForNull*/ QColor color);
    /*public*/ void setTurnoutFillControlCircles(bool state);
    /*public*/ void setTurnoutCircleSize(int size);
    /*public*/ void setTurnoutDrawUnselectedLeg(bool state);
    /*public*/ QVector<AnalogClock2Display*>* clocks = new QVector<AnalogClock2Display*>();  // fast clocks
    /*public*/ QVector<SignalHeadIcon*>* signalHeadImage = new QVector<SignalHeadIcon*>();  // signal head images
    /*public*/ QVector<SignalMastIcon*>* signalMastImage = new QVector<SignalMastIcon*>();  // signal mast images
    /*public*/ QVector<PositionableLabel*>* _labelImage = new QVector<PositionableLabel*>(); // layout positionable label images
    /*public*/ QVector<PositionableLabel*>* backgroundImage = new QVector<PositionableLabel*>();  // background images
    /*public*/ /*transient*/ QList<PositionableLabel*> labelImage = QList<PositionableLabel*>();         //positionable label images
    /*public*/ void setXScale(double xSc) ;
    /*public*/ void setYScale(double ySc);
    /*public*/ void setTurnoutCircles(bool state);
    /*public*/ void setSnapOnAdd(bool state);
    /*public*/ void setSnapOnMove(bool state);
    /*public*/ void setAntialiasingOn(bool state);
    /*public*/ void setDrawLayoutTracksLabel(bool state);
    /*public*/ void setAutoBlockAssignment(bool boo);
    /*public*/ void setScroll(int state);
    /*public*/ void setConnections();
    /*public*/ /*@Nonnull*/ QRectF layoutEditorControlRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ /*@Nonnull*/ QRectF layoutEditorControlCircleRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ QList<SensorIcon*> getSensorList();
    /*public*/ QList<LEBlockContentsIcon *> getBlockContentsLabelList();
    /*public*/ QList<LEMemoryIcon *> getMemoryLabelList();
    /*public*/ QList<SignalHeadIcon*> getSignalList();
    /*public*/ QList<SignalMastIcon*> getSignalMastList();
    /*public*/ LayoutEditorFindItems* finder = new LayoutEditorFindItems(this);
    /*public*/ LayoutEditorFindItems* getFinder();
    void setDirty(bool b );
    /*public*/ void setDirty() /*override*/;
    /*public*/ void addTurntable(QPointF pt);
    /*public*/ bool containsSignalHead(SignalHead* head) ;
    /*public*/ void removeSignalHead(SignalHead* head);
    /*public*/ void addBackground();
    /*public*/ void setDefaultTrackColor(QColor color);
    /*public*/ void setDefaultOccupiedTrackColor(QColor color);
    /*public*/ void setDefaultAlternativeTrackColor(QColor color);
    /*public*/ QString getClassName();
    /*public*/ LayoutTrackDrawingOptions* getLayoutTrackDrawingOptions();
    /*public*/ void setLayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo);
    /*public*/ static void setupComboBox(/*@Nonnull*/ NamedBeanComboBox* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank);
    /*public*/ QRectF unionToPanelBounds(/*@Nonnull*/ QRectF bounds);
    /*public*/ QRectF getPanelBounds();
    /*public*/ bool highlightBlock(/*@Nullable*/ Block* inBlock);
    /*public*/ bool highlightLayoutBlock(/*@Nonnull*/ LayoutBlock* inLayoutBlock);
    /*public*/ void setPanelBounds(QRectF newBounds);
    /*public*/ double setZoom(double zoomFactor);
    /*public*/ double getZoom();
    /*public*/ QVector<SignalHeadIcon*>* signalList = new QVector<SignalHeadIcon*>();  // Signal Head Icons
    /*public*/ QVector<SignalMastIcon*>* signalMastList = new QVector<SignalMastIcon*>();  // Signal Head Icons
    /*private*/ /*transient*/ QList<LayoutShape*> layoutShapes = QList<LayoutShape*>();               // LayoutShap list
    /*public*/ QVector<MultiSensorIcon*>* multiSensors = new QVector<MultiSensorIcon*>(); // MultiSensor Icons
    /*public*/ void dispose();
    /*public*/ QList<PositionablePoint *> getPositionablePoints() /*override*/;
    /*public*/ /*@Nonnull*/ QList<LayoutSlipView*> getLayoutSlipViews();
    /*public*/ QList<LayoutSlip *> getLayoutSlips()/*override*/;
    /*public*/ /*QNonnull*/ QList<TrackSegmentView*> getTrackSegmentViews() /*override*/;
    /*public*/ QList<TrackSegment *> getTrackSegments() /*override*/;
    /*public*/ /*@Nonnull*/ QList<LayoutTurnoutView*> getLayoutTurnoutViews(); // this specifically does not include slips
    /*public*/ QList<LayoutTurnout *> getLayoutTurnouts() /*override*/;
    /*public*/ QList<LayoutTurntable *> getLayoutTurntables()/*override*/;
    /*public*/ QList<LevelXing*> getLevelXings() /*override*/;
    /*public*/ QList<LevelXingView*> getLevelXingViews() /*override*/;

    /*final*/ /*public*/ void addLayoutTrack(/*@Nonnull*/ LayoutTrack* trk, LayoutTrackView *v);
    /*public*/ QList<LayoutTrack *> getLayoutTracks() /*override*/;
    /*public*/ /*@Nonnull*/ QList<LayoutTurnoutView*> getLayoutTurnoutAndSlipViews();
    /*public*/ /*@Nonnull*/QList<LayoutTurnout*> getLayoutTurnoutsAndSlips() /*override*/;
    /*final*/ /*public*/ QList<LayoutTrackView*> getLayoutTrackViews() /*override*/;
    /*final*/ /*public*/ LayoutTrackView* getLayoutTrackView(LayoutTrack* trk) /*override*/;
    /*final*/ /*public*/ LevelXingView* getLevelXingView(LevelXing* xing) /*override*/;
    /*final*/ /*public*/ LayoutTurnoutView* getLayoutTurnoutView(LayoutTurnout* to) /*override*/;
    /*final*/ /*public*/ LayoutTurntableView* getLayoutTurntableView(LayoutTurntable* to) /*override*/;
    /*final*/ /*public*/ LayoutSlipView* getLayoutSlipView(LayoutSlip* to);
    /*final*/ /*public*/ TrackSegmentView* getTrackSegmentView(TrackSegment* to) /*override*/;
    /*final*/ /*public*/ PositionablePointView* getPositionablePointView(const PositionablePoint *to) /*override*/;

    /*public*/ /*@Nonnull*/ QList<LayoutShape *> getLayoutShapes()/*override*/;
    /*public*/ void sortLayoutShapesByLevel();
    /*public*/ int computeDirection(LayoutTrack* trk1, HitPointType::TYPES h1, LayoutTrack* trk2, HitPointType::TYPES h2) /*override*/;
    /*public*/ int computeDirectionToCenter(/*@Nonnull*/ LayoutTrack* trk1, /*@Nonnull*/ HitPointType::TYPES h1, /*@Nonnull*/ PositionablePoint* p) /*override*/;
    /*public*/ int computeDirectionFromCenter(/*@Nonnull*/ const PositionablePoint *p, /*@Nonnull*/ LayoutTrack* trk1, /*@Nonnull*/ HitPointType::TYPES h1) /*override*/;
    /*public*/ bool removeFromContents(Positionable* l);
    /*public*/ QPointF getCoords(/*@Nonnull*/ LayoutTrack* layoutTrack, HitPointType::TYPES connectionType);
    /*public*/ QPointF getCoords(/*@Nonnull*/ LayoutTrackView* trkv, HitPointType::TYPES connectionType);
    /*public*/ QRectF trackEditControlRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ QRectF trackControlCircleRectAt(/*@Nonnull*/ QPointF inPoint);
    /*public*/ void setSelectionRect(/*@Nonnull*/ QRectF selectionRect);
    /*private*/ void drawSelectionRect(EditScene* g2);
    /*public*/ void addEdgeConnector() ;
    const QIcon getColourIcon(QColor color);
    /*public*/ bool isIncludedTurnoutSkipped();
    QT_DEPRECATED /*public*/ bool getOpenDispatcherOnLoad();
    /*public*/ void setOpenDispatcherOnLoad(bool boo);
    /*public*/ void setHighlightSelectedBlock(bool state);
    /*public*/ void rotateSelection90();
    /*public*/ void rotateLayout90();
    /*public*/ void alignLayoutToGrid();
    /*public*/ void alignSelectionToGrid() ;
    /*public*/ void translate(float xTranslation, float yTranslation);
    /*public*/ void setTurnoutAnimation(bool state);
    /*public*/ void setDirectTurnoutControl(bool boo);
    /*public*/ void setIncludedTurnoutSkipped(bool boo);
    /*public*/ void setAllEditable(bool editable) override;
    /*public*/ void setShowHelpBar(bool state);
    /*public*/ bool translateTrack(float xDel, float yDel);
    /*public*/ int setAllTracksToDefaultColors();
    /*public*/ bool scaleTrack(float xFactor, float yFactor);
    /*public*/ void clearSelectionGroups();
    /*public*/ void keyPressEvent(QKeyEvent *event) override;
    /*protected*/ void paintTargetPanel(EditScene* g2);
    /*private*/ QRectF getSelectionRect();
    /*public*/ QList<PositionablePointView*> getPositionablePointViews() /*override*/;
    /*final*/ /*public*/ bool removeLayoutTrackAndRedraw(/*@Nonnull*/ LayoutTrack* trk);
    /*final*/ /*public*/ void removeLayoutTrack(/*@Nonnull */LayoutTrack* trk) /*override*/;
    /*public*/ ToolBarSide *getToolBarSide();
    /*public*/ void setToolBarSide(ToolBarSide* newToolBarSide);
    /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean);
    /*public*/ TurnoutComboBoxPopupMenuListener* newTurnoutComboBoxPopupMenuListener(NamedBeanComboBox/*<Turnout>*/* comboBox);
    /*public*/ TurnoutComboBoxPopupMenuListener* newTurnoutComboBoxPopupMenuListener(NamedBeanComboBox/*<Turnout>*/* comboBox, QList<Turnout*> currentTurnouts);
    /*public*/ void init(QString name) override;
    /*public*/ void initView() override;
    /*public*/ double getMinZoom();
    /*public*/ double getMaxZoom();
    /*public*/ void setAwaitingIconChange();
    /*public*/ void resetAwaitingIconChange();
    /*public*/ LayoutTrackView* foundTrackView = nullptr;                 // found view object, null if nothing found

    /*public*/ QList<Positionable*>* _positionableSelection = new QList<Positionable*>();
    /*public*/ QList<LayoutTrack*> _layoutTrackSelection = QList<LayoutTrack*>();
    /*public*/ QList<LayoutShape*> _layoutShapeSelection = QList<LayoutShape*>();

    // LayoutModels stuff
    /*default*/ /*public*/ virtual int computeDirectionAB( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsB());
    }

    /*default*/ /*public*/ virtual int computeDirectionAC( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsC());
    }

    /*default*/ /*public*/ virtual int computeDirectionAD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsD());
    }

    /*default*/ /*public*/ virtual int computeDirectionBC( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsB(), tv->getCoordsC());
    }

    /*default*/ /*public*/ virtual int computeDirectionBD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsB(), tv->getCoordsD());
    }

    /*default*/ /*public*/ virtual int computeDirectionCD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsC(), tv->getCoordsD());
    }

    /**
     * Invoked to display a warning about removal.
     * Lists the attached items that prevent removing the layout track item.
     * <p>
     * The default implementation refers this to a View object for displaying a Dialog.
     *
     * @param track The involved track
     * @param itemList A list of the attached heads, masts and/or sensors.
     * @param typeKey  The object type such as Turnout, Level Crossing, etc.
     */
    /*default*/ /*public*/ virtual void displayRemoveWarning(LayoutTrack* track, QList<QString> itemList, QString typeKey) {
        getLayoutTrackView(track)->displayRemoveWarningDialog(itemList, typeKey);
    }
    /*public*/ QList<Positionable *> *getPositionalSelection();
    /*public*/ QList<LayoutTrack*> getLayoutTrackSelection();
    /*public*/ QList<LayoutShape*> getLayoutShapeSelection();

    // use turnoutCircleSize when you need an int and these when you need a double
    // note: these only change when setTurnoutCircleSize is called
    // using these avoids having to call getTurnoutCircleSize() and
    // the multiply (x2) and the int -> double conversion overhead
    /*public*/ /*transient*/ double circleRadius = SIZE * getTurnoutCircleSize();
    /*public*/ /*transient*/ double circleDiameter = 2.0 * circleRadius;
    /*public*/ void alignSelection(bool alignX);


 public slots:
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event) override;
    /**
     * Handle a mouse pressed event
     */
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseWheelMoved(/*@Nonnull*/ QGraphicsSceneWheelEvent* event);

private:
 //Operational instance variables - not saved to disk
 /*private*/ /*transient*/ JmriJFrame* floatingEditToolBoxFrame = nullptr;
 /*private*/ /*transient*/ QScrollArea* floatingEditContentScrollPane = nullptr;
 /*private*/ /*transient*/ JPanel* floatEditHelpPanel = nullptr;
 /*private*/ /*transient*/ EditToolBarContainerPanel* editToolBarContainerPanel = nullptr;
 /*private*/ /*transient*/ QScrollArea* editToolBarScrollPane = nullptr;
 /*private*/ /*transient*/ JPanel* helpBarPanel = new JPanel();
    JPanel* helpBar = new JPanel();
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

 /*private*/ /*transient*/ double selectionX = 0.0;
 /*private*/ /*transient*/ double selectionY = 0.0;

 //Option menu items
 /*private*/ /*transient*/ QAction* editModeCheckBoxMenuItem = nullptr;

 /*private*/ /*transient*/ QAction* toolBarSideTopButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideLeftButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideBottomButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideRightButton = nullptr;
 /*private*/ /*transient*/ QAction* toolBarSideFloatButton = nullptr;

 /*private*/ /*transient*/ JCheckBoxMenuItem* wideToolBarCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Wide ToolBar"),this);

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

 /*private*/ JCheckBoxMenuItem* pixelsCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Pixels"),this);
 /*private*/ JCheckBoxMenuItem* metricCMCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Metric CM's"),this);
 /*private*/ JCheckBoxMenuItem* englishFeetInchesCheckBoxMenuItem = new JCheckBoxMenuItem(tr("English ft/in/16th's"), this);

 /*private*/ /*transient*/ QAction* snapToGridOnAddCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* snapToGridOnMoveCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* antialiasingOnCheckBoxMenuItem = nullptr;
 /*private*/ JCheckBoxMenuItem* drawLayoutTracksLabelCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* turnoutCirclesOnCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* turnoutDrawUnselectedLegCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* hideTrackSegmentConstructionLinesCheckBoxMenuItem = nullptr;
 /*private*/ /*transient*/ QAction* useDirectTurnoutControlCheckBoxMenuItem = nullptr;
 QActionGroup* turnoutCircleSizeButtonGroup;

 /*private*/ /*transient*/ bool turnoutDrawUnselectedLeg = true;
 /*private*/ /*transient*/ bool autoAssignBlocks = false;

 //Tools menu items
 /*private*/ /*transient*/ QMenu* zoomMenu = new QMenu(tr("Zoom"));
 /*private*/ /*transient*/ QAction* zoom025Item = nullptr;// = new JRadioButtonMenuItem("x 0.25");
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

 /*private*/ /*transient*/ QMenu* undoTranslateSelectionMenuItem = new QMenu(tr("Undo Translate Selection"));
 /*private*/ /*transient*/ QMenu* assignBlockToSelectionMenuItem = new QMenu(tr("Assign Block To Selection") + "...");

 QPointF startDelta;
 /*private*/ /*transient*/ HitPointType::TYPES selectedHitPointType;// = 0;         //hit point type within the selected object

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
// /*private*/ /*transient*/ double xScale = 1.0;
// /*private*/ /*transient*/ double yScale = 1.0;
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
 /*private*/ /*transient*/ ToolBarSide* toolBarSide = new ToolBarSide("top");
 /*private*/ double returnDeltaPositionX(/*@Nonnull*/ QKeyEvent* event);
 /*private*/ double returnDeltaPositionY(/*@Nonnull*/ QKeyEvent* event);
 /*private*/ void clearLayoutTracks();
 /*private*/ void resetTargetSize();


 QButtonGroup* buttonGroup;

 int xLoc, yLoc;
 /*private*/ /*transient*/ /*final*/ static Logger* log;

 /*private*/ QPointF calcLocation(QGraphicsSceneMouseEvent *event, int dX, int dY);
 /*private*/ QPointF calcLocation(QGraphicsSceneMouseEvent* event);

 bool bIsEditable = true;
 /*private*/ void createSelectionGroups();
 bool isDragging = false;
 StoreXmlUserAction* savePanels = new StoreXmlUserAction(tr("Save Panels..."), this);
 //bool bDirty;
 bool isDirty();
 void resetDirty();
 ///*private*/ QObject* beginObject;// = nullptr; // begin track segment connection object, NULL if none
 /*private*/ void setLink(QObject* fromObject, HitPointType::TYPES fromPointType, QObject* toObject, HitPointType::TYPES toPointType);
 LayoutEditorAuxTools* auxTools = nullptr;
 // selection variables
 /*private*/ QVector<LayoutTurnout*>* _turnoutSelection = nullptr; //new QVector<LayoutTurnout>();  // LayoutTurnouts
 /*private*/ QVector<LevelXing*>* _xingSelection = nullptr; //new QVector<LevelXing>();  // LevelXing list
 /*private*/ QVector<LayoutSlip*>* _slipSelection = nullptr; //new QVector<LayoutSlip*>();  // LayoutSlip list
 /*private*/ QVector<LayoutTurntable*>* _turntableSelection = nullptr; //new ArrayList<LayoutTurntable>(); // Turntable list
 /*private*/ QVector<PositionablePoint*>* _pointSelection = nullptr; //new QVector<PositionablePoint>();  // PositionablePoint list
 QVector<PositionableLabel*>* _labelSelection; //new QVector<PositionableLabel>();  // PositionableLabel list
 /*private*/ QList<LayoutTrack *> getLayoutTracksOfClass(QString type);
 /*private*/ void selectLocationFormatCheckBoxMenuItem();

  bool isDrawing = false;

 /*private*/ void amendSelectionGroup(Positionable* p);
 /*private*/ void amendSelectionGroup(LayoutTurnout* p);
 /*private*/ void amendSelectionGroup(PositionablePoint* p);
 /*private*/ void amendSelectionGroup(LevelXing* p);
 /*private*/ void amendSelectionGroup(LayoutTrack *p);
 bool main = true;
 bool _editable = false;
 friend class SensorIcon;
 int _scrollState;
 int _anchorX = 0, _anchorY = 0;
 int _lastX, _lastY;
 /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event) override;
 bool _controlLayout= true;
 bool noWarnPositionablePoint = false;
 bool noWarnSlip = false;
 /*private*/ void disconnect(QObject* o, int type);
 /**
 * Add a sensor indicator to the Draw Panel
 */
 void addSensor();

 bool bDirty = false;
 InstanceManager* instanceManager;
 /*private*/ bool _showCoordinates = true;
 Positionable* saveP;
 /*private*/ LocoIcon* checkMarkers(QPointF loc);
 QGraphicsItemGroup* panelGridGroup = nullptr;
 QGraphicsItem* trackInProgress = nullptr;
 /*private*/ bool _globalSetsLocal = true;    // pre 2.9.6 behavior
 /*private*/ bool _useGlobalFlag = false;     // pre 2.9.6 behavior
 QGraphicsRectItem *rectItem = nullptr; // selection rect.
 QGraphicsItemGroup* highlightRect = nullptr;

 /*private*/ QRectF clipBounds = QRectF();
 bool noWarnGlobalDelete = false;
 bool noWarnLevelXing = false;
 bool noWarnLayoutTurnout;
 bool noWarnTurntable = false;
 QString _defaultToolTip = "";
 Positionable* currComp;
 LEMemoryIcon* checkMemoryMarkerIcons(QPointF loc);
 JFileChooser* inputFileChooser;
 bool _debug = true;
 bool _ignore = false;
 NamedIcon* _newIcon = nullptr;
 bool _delete = false;
 RosterEntrySelectorPanel* rosterBox;
 QString layoutFile;
 int _prevNumSel;
 LayoutEditorTools* tools = nullptr;
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
 /*private*/ void checkPointOfPositionable(PositionablePoint* p);
 /*private*/ void rotateTurnout(LayoutTurnout* t);
 /*private*/ JRadioButtonMenuItem* addButtonGroupMenuEntry(/*@Nonnull*/ QMenu* inMenu,
             QActionGroup *inButtonGroup,
             /*final*/ QString inName,
             bool inSelected,
             ActionListener* inActionListener);
 void addTurnoutCircleSizeMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ int size);
 /*private*/ void setOptionMenuTurnoutCircleSize();
 /*private*/ /*transient*/ LayoutTrackDrawingOptions* layoutTrackDrawingOptions = nullptr;
 /*private*/ /*transient*/ JFrame* iconFrame = nullptr;
 /*private*/ bool highlightBlockInComboBox(/*@Nonnull*/ NamedBeanComboBox *inComboBox);
 /*private*/ QRectF calculateMinimumLayoutBounds();
 /*private*/ QRectF resizePanelBounds(bool forceFlag);
 QLabel* zoomLabel;
 /*private*/ void selectZoomMenuItem(double zoomFactor);

 //grid size in pixels
 /*private*/ QString findBeanUsage(NamedBean* sm);
 /*private*/ bool removeAttachedBean(/*@Nonnull*/ NamedBean* bean);
 /*private*/ void removeBeanRefs(NamedBean* sm);
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
 /*private*/ /*transient*/ LayoutEditorChecks* layoutEditorChecks = nullptr;
 //operational variables for enter track width pane
 /*private*/ /*transient*/ JmriJFrame* enterTrackWidthFrame = nullptr;
 /*private*/ bool enterTrackWidthOpen = false;
 /*private*/ bool trackWidthChange = false;
 /*private*/ /*transient*/ QPushButton* trackWidthDone;
 /*private*/ /*transient*/ QPushButton* trackWidthCancel;
 //operational variables for enter grid sizes pane
 /*private*/ /*transient*/ JmriJFrame* enterGridSizesFrame = nullptr;
 /*private*/ bool enterGridSizesOpen = false;
 /*private*/ bool gridSizesChange = false;
 /*private*/ /*transient*/ QPushButton* gridSizesDone = nullptr;
 /*private*/ /*transient*/ QPushButton* gridSizesCancel = nullptr;
 //operational variables for enter reporter pane
 /*private*/ /*transient*/ JmriJFrame* enterReporterFrame = nullptr;
 /*private*/ bool reporterOpen = false;
 /*private*/ /*transient*/ QPushButton* reporterDone;
 /*private*/ /*transient*/ QPushButton* reporterCancel;
 //operational variables for scale/translate track diagram pane
 /*private*/ /*transient*/ JmriJFrame* scaleTrackDiagramFrame = nullptr;
 /*private*/ bool scaleTrackDiagramOpen = false;
 /*private*/ /*transient*/ QPushButton* scaleTrackDiagramDone = nullptr;
 /*private*/ /*transient*/ QPushButton* scaleTrackDiagramCancel =nullptr;
 /*private*/ void showEditPopUps(/*@Nonnull */QGraphicsSceneMouseEvent* event);
 /*private*/ void hitPointCheckLayoutTurnouts(/*@Nonnull*/ LayoutTurnout* lt);
 /*private*/ void hitPointCheckLayoutTurnoutSubs(/*@Nonnull*/ QPointF dLoc);
 QPen drawingStroke;
 LayoutEditorComponent* layoutEditorComponent = nullptr;
 //operational variables for move selection pane
 /*private*/ /*transient*/ JmriJFrame* moveSelectionFrame = nullptr;
 /*private*/ bool moveSelectionOpen = false;
 /*private*/ /*transient*/ QPushButton* moveSelectionDone;
 /*private*/ /*transient*/ QPushButton* moveSelectionCancel;
 /*private*/ bool canUndoMoveSelection = false;
 /*private*/ QPointF undoDelta = MathUtil::zeroPoint2D;
 /*private*/ double undoDeltaX = 0.0;
 /*private*/ double undoDeltaY = 0.0;
 /*private*/ /*transient*/ QRectF undoRect;
 QAction* skipTurnoutCheckBoxMenuItem;
 /*private*/ AddEntryExitPairAction* addEntryExitPairAction = nullptr;
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
 BorderLayout* borderLayout = nullptr;
 /*private*/ void alignToGrid(QList<Positionable *> positionables, QList<LayoutTrack*> tracks, QList<LayoutShape*> shapes);
 /*private*/ qint64 whenReleased = 0; //used to identify event that was popup trigger
 /*private*/ bool awaitingIconChange = false;

 /*private*/ /*transient*/ bool toolBarIsWide = true;
 /*private*/ void setToolBarSide(QString);
 /*private*/ void setupMenuBar();
 /*private*/ /*final*/ QList<LayoutTrack*> layoutTrackList = QList<LayoutTrack*>();
 /*private*/ /*final*/ QList<LayoutTrackView*> layoutTrackViewList =  QList<LayoutTrackView*>();
 /*private*/ /*final*/ QMap<LayoutTrack*, LayoutTrackView*> trkToView = QMap<LayoutTrack*, LayoutTrackView*>();
 /*private*/ /*final*/ QMap<LayoutTrackView*, LayoutTrack*> viewToTrk = QMap<LayoutTrackView*, LayoutTrack*>();
 QList<NamedBeanUsageReport*> usageReport;
 void findTurnoutUsage(NamedBean* bean);
 void findPositionalUsage(NamedBean* bean);
 void findSegmentWhereUsed(NamedBean* bean);
 void findXingWhereUsed(NamedBean* bean);
 QString getUsageData(LayoutTrack* track);
 bool isLBLockUsed(NamedBean* bean, LayoutBlock* lblock);
 bool isUsedInXing(NamedBean* bean, LevelXing* xing, int point);
 /*private*/ void setTooltipSubMenu();

private slots:
 void on_scenePos(QGraphicsSceneMouseEvent*event);
 /*private*/ void deleteSelectedItems(); // SLOT[]
 double zoomToFit();
 /*private*/ void resetTurnoutSize();
 /*private*/ void setToolBarWide(bool newToolBarIsWide);
 void trigger_menu();


protected:
 /*protected*/  void common();

 //size of point boxes
 /*protected*/ static /*final*/ const double SIZE;// = 3.0;
 /*protected*/ static /*final*/ const double SIZE2;// = SIZE * 2.; //must be twice SIZE

 /*protected*/ QColor turnoutCircleColor = QColor(Qt::black); //matches earlier versions
 /*protected*/ QColor turnoutCircleThrownColor= QColor(Qt::black);
 /*protected*/ bool turnoutFillControlCircles = false;
 /*protected*/ int turnoutCircleSize = 4; //matches earlier versions

 //selection variables
 /*protected*/ /*transient*/ bool selectionActive = false;
 /*protected*/ /*transient*/ double selectionWidth = 0.0;
 /*protected*/ /*transient*/ double selectionHeight = 0.0;

 /*protected*/ /*transient*/ QObject* selectedObject = nullptr;       //selected object, null if nothing selected
 /*protected*/ /*transient*/ QObject* prevSelectedObject = nullptr;   //previous selected object, for undo

 /*protected*/ /*transient*/ LayoutTrack* foundTrack = nullptr;      //found object, null if nothing found
 /*protected*/ /*transient*/ QPointF foundLocation;// = new Point2D.Double(0.0, 0.0); //location of found object
 /*protected*/ /*transient*/ HitPointType::TYPES foundHitPointType;// = 0;          //connection type within the found object
 /*protected*/ /*transient*/ LayoutTrack* beginTrack = nullptr;      //begin track segment connection object, null if none
 /*protected*/ /*transient*/ QPointF beginLocation = QPointF(0.0, 0.0); //location of begin object
 /*protected*/ /*transient*/ HitPointType::TYPES beginHitPointType = HitPointType::NONE; //connection type within begin connection object

 /*protected*/ /*transient*/ QPointF currentLocation;// = new Point2D.Double(0.0, 0.0); //current location

 /*protected*/ /*transient*/ QColor mainlineTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor sidelineTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor defaultTrackColor = QColor(Qt::darkGray);
 /*protected*/ /*transient*/ QColor defaultOccupiedTrackColor = QColor(Qt::red);
 /*protected*/ /*transient*/ QColor defaultAlternativeTrackColor = QColor(Qt::white);

 /*protected*/ /*transient*/ bool antialiasingOn = false;
 /*private*/ bool drawLayoutTracksLabel = false;
 /*protected*/ /*transient*/ bool highlightSelectedBlockFlag = false;

 /*protected*/ /*transient*/ bool turnoutCirclesWithoutEditMode = false;

 /**
 * Return a List of all items whose bounding rectangle contain the mouse position.
 * ordered from top level to bottom
 */
// /*protected*/ QList <Positionable*> getSelectedItems(QGraphicsSceneMouseEvent* event);
 /*protected*/ double _paintScale = 1.0;   // scale for _targetPanel drawing
 /**
 * Select the menu items to display for the Positionable's popup
 */
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

 /*public*/ LayoutBlock* getLayoutBlock(/*@Nonnull*/ QString blockID);
 /**
 * Remove object from all Layout Editor temmporary lists of items not part of track schematic
 */
 /*protected*/ bool remove(QObject* s);
 /*protected*/ void setSelectionsScale(double s, Positionable* p);
 /*protected*/ bool removeLayoutSlip (LayoutTurnout* o);
 /*protected*/ bool skipIncludedTurnout = false;
 /*protected*/ void targetWindowClosingEvent(/*WindowEvent*/ QCloseEvent* e);
 /**
 * Remove marker icons from panel
 */
 /*protected*/ void removeMarkers();
 /*protected*/ void removeBackground(PositionableLabel* b);
 /*protected*/ void drawTurnouts(EditScene* g2);
 /*protected*/ void setupToolsMenu(/*@Nonnull*/ QMenuBar* menuBar);
 /*protected*/ void showPopUp(/*@Nonnull*/ Positionable* p, /*@Nonnull */QGraphicsSceneMouseEvent* event);
 /*protected*/ QMenu* setupOptionMenu(/*@Nonnull*/ QMenuBar* menuBar);
 /*protected*/ LayoutShape* addLayoutShape(/*@Nonnull*/ QPointF p);
 /*protected*/ bool removeLayoutShape(/*@Nonnull*/ LayoutShape* s);
 /*protected*/ void amendSelectionGroup(/*@Nonnull*/ LayoutShape* ls);

protected slots:
 /*protected*/ void assignBlockToSelection();
 void undoMoveSelection();

 friend class CoordinateEdit;
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
 friend class LayoutEditorComponent;
 friend class TurnoutComboBoxPopupMenuListener;
 friend class LayoutTrack;
 friend class LayoutTurnoutView;
 friend class LayoutTrackView;
 friend class TrackSegmentView;
 friend class LayoutSlipView;
 friend class LevelXingView;
 friend class LayoutTurntableView;
 friend class PositionablePointView;

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
   switch (editor->toolBarSide->getType()) {
    case eTOP:
     editor->borderLayout->addWidget(this, BorderLayout::North);
     break;
    case eBOTTOM:
     editor->borderLayout->addWidget(this, BorderLayout::South);
     break;
    case eLEFT:
     editor->borderLayout->addWidget(this, BorderLayout::West);
     break;
    case eRIGHT:
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

class AddTurnoutCircleSizeMenuEntryCactionListener : public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
  LayoutEditor* layoutEditor;
  int inSize;
 public:
  AddTurnoutCircleSizeMenuEntryCactionListener(int inSize, LayoutEditor* layoutEditor)
  {
   this->inSize = inSize;
   this->layoutEditor = layoutEditor;
  }
 public slots:
  void actionPerformed()
  {
   if (layoutEditor->getTurnoutCircleSize() != inSize) {
       layoutEditor->setTurnoutCircleSize(inSize);
       layoutEditor->setDirty();
       layoutEditor->redrawPanel();
   }

  }
};

// package protected
class TurnoutComboBoxPopupMenuListener : public PopupMenuListener {
Q_OBJECT
    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* comboBox;
    /*private*/ /*final*/ QList<Turnout*> currentTurnouts;
  LayoutEditor* layoutEditor;
public:
    /*public*/ TurnoutComboBoxPopupMenuListener(NamedBeanComboBox/*<Turnout>*/* comboBox, QList<Turnout*> currentTurnouts, LayoutEditor* layoutEditor) {
        this->comboBox = comboBox;
        this->currentTurnouts = currentTurnouts;
        this->layoutEditor = layoutEditor;
    }

    //@Override
    /*public*/ void popupMenuWillBecomeVisible(PopupMenuEvent* event) override{
        // This method is called before the popup menu becomes visible.
        layoutEditor->log->debug("PopupMenuWillBecomeVisible");
        QSet<NamedBean*> l = QSet<NamedBean*>();
        //comboBox->getManager()->getNamedBeanSet().forEach((turnout) ->
        foreach(NamedBean* nb, comboBox->getManager()->getNamedBeanSet())
        {
         Turnout* turnout = (Turnout*)nb;
            if (!currentTurnouts.contains(turnout)) {
                if (!layoutEditor->validatePhysicalTurnout(turnout->getDisplayName(), nullptr)) {
                    l.insert(nb);
                }
            }
        }//);
        comboBox->setExcludedItems(l);
    }

    //@Override
    /*public*/ void popupMenuWillBecomeInvisible(PopupMenuEvent* event) override {
        // This method is called before the popup menu becomes invisible
        layoutEditor->log->debug("PopupMenuWillBecomeInvisible");
    }

    //@Override
    /*public*/ void popupMenuCanceled(PopupMenuEvent* event) override{
        // This method is called when the popup menu is canceled
        layoutEditor->log->debug("PopupMenuCanceled");
    }
};
#endif // LAYOUTEDITOR_H
