#include "layouteditor.h"
#include "ui_layouteditor.h"
#include <QGraphicsRectItem>
#include "instancemanager.h"
#include "QMessageBox"
#include "positionablepopuputil.h"
#include "coordinateedit.h"
#include "inputdialog.h"
#include "settrackwidthdlg.h"
#include "addreporterdlg.h"
#include <QFileDialog>
#include <QColor>
#include "memoryiconcoordinateedit.h"
#include "QFormLayout"
#include "abstractsensor.h"
#include "panelmenu.h"
#include "signalmasticon.h"
#include "signalheadicon.h"
#include "analogclock2display.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"
#include "multiiconeditor.h"
#include "defaultsignalmastmanager.h"
#include "layoutblockconnectivitytools.h"
#include "jmrijframe.h"
#include "layoutslip.h"
#include <QVector>
#include "connectivityutil.h"
#include "abstractsignalheadmanager.h"
#include "multisensoricon.h"
#include "multisensoriconframe.h"
#include "rfid/rfidsensormanager.h"
#include "helputil.h"
#include <QCloseEvent>
#include "layoutturntable.h"
#include "storexmluseraction.h"
#include "configxmlmanager.h"
#include "borderlayout.h"
#include "addentryexitpairaction.h"
#include "jtextfield.h"
#include "layouteditorfinditems.h"
#include "jmriconfigurationmanager.h"
#include "userpreferencesmanager.h"
#include "positionablejcomponent.h"
#include "colorutil.h"
#include <QSignalMapper>
#include "jfilechooser.h"
#include "system.h"
#include "layouttrackdrawingoptions.h"
#include "jmribeancombobox.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "mathutil.h"
#include <QScrollBar>
#include "jmricolorchooser.h"
#include "namedbean.h"
#include "signalmastlogicmanager.h"
#include "signalmastlogic.h"
#include "positionablepoint.h"
#include "optional.h"
#include <limits>
#include "layouttrackeditors.h"
#include "layouteditorchecks.h"
#include "leblockcontentsicon.h"
#include "layouttrackdrawingoptions.h"
#include "layouttrackdrawingoptionsdialog.h"
#include <QPointF>
#include "transitmanager.h"
#include "dispatcherframe.h"
#include "dispatcheraction.h"
#include "activatetrainframe.h"
#include "mathutil.h"
#include <QActionGroup>
#include "leblockcontentsicon.h"
#include "guilafpreferencesmanager.h"

/*private*/ /*static*/ const double LayoutEditor::SIZE = 3.0;
/*private*/ /*static*/ const double LayoutEditor::SIZE2 = 6.0;  // must be twice SIZE

LayoutEditor::LayoutEditor(QString name, QWidget *parent) :
    PanelEditor(name, parent),
    ui(new Ui::LayoutEditor)
{
 init();
 layoutName = name;
 setObjectName(name);
}

//LayoutEditor::LayoutEditor(LocoNetSystemConnectionMemo* memo, QString name,  bool bTest, QWidget *parent) :
//    PanelEditor(name, parent),
//    ui(new Ui::LayoutEditor)
//{
// setObjectName("LayoutEditor");
// ui->setupUi(this);
// this->bTestMode = bTest;
// this->memo = memo;
// layoutName = name;
// init();
//}

LayoutEditor::~LayoutEditor()
{
 delete ui;
}

//@Override
/*public*/ void LayoutEditor::newPanelDefaults()
{
 getLayoutTrackDrawingOptions()->setMainRailWidth(2);
 getLayoutTrackDrawingOptions()->setSideRailWidth(1);
 setBackgroundColor(defaultBackgroundColor);
 JmriColorChooser::addRecentColor(defaultTrackColor);
 JmriColorChooser::addRecentColor(defaultOccupiedTrackColor);
 JmriColorChooser::addRecentColor(defaultAlternativeTrackColor);
 JmriColorChooser::addRecentColor(defaultBackgroundColor);
 JmriColorChooser::addRecentColor(defaultTextColor);
}

void LayoutEditor::init()
{
 editorUseOldLocSize = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize();
 setSaveSize(true);

 ui->setupUi(this);
 setObjectName("LayoutEditor");
 JmriJFrame::initComponents();
 PanelEditor::init(layoutName);
 savePanels = new StoreXmlUserAction(tr("Save Panels..."), this);
 ui->menuFile->insertAction(ui->actionSave_panels,savePanels);
 ui->menuFile->removeAction(ui->actionSave_panels); // remove the old one.
 _contents = new QVector<Positionable*>();
 //pointList = new QVector<PositionablePoint*>();  // PositionablePoint list
 bIsEditable = true;
 ui->actionEdit_mode->setChecked(bIsEditable);
_globalSetsLocal = true;    // pre 2.9.6 behavior
_useGlobalFlag = false;     // pre 2.9.6 behavior
 ui->actionAllow_layout_control->setChecked(_controlLayout);
 snapToGridOnAdd = false;
 ui->actionSnap_to_grid_when_adding->setChecked(snapToGridOnAdd);
 snapToGridOnMove = false;
 ui->actionSnap_to_grid_when_moving->setChecked(snapToGridOnMove);
 numAnchors = 0;
 numEndBumpers = 0;
 numTrackSegments = 0;
 beginObject = nullptr; // begin track segment connection object, nullptr if none
 beginPointType = 0;   // connection type within begin connection object
 foundObject = nullptr; // found object, nullptr if nothing found
 foundPointType = 0;   // connection type within the found object
 newTrack = nullptr;
 numLevelXings = 0;
 numLayoutSlips = 0;
 numLayoutTurntables = 0;
 //zoom
 minZoom = 0.25;
 maxZoom = 8.0;
 toolBarSide = ToolBarSide("top");


 if(static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
 {
  log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }

 //HelpUtil::instance()->helpMenu(menuBar(), "package.jmri.jmrit.display.LayoutEditor", true);
 resetDirty();
 // establish link to LayoutEditorAuxTools
 auxTools = new LayoutEditorAuxTools(this);
 tools = nullptr;
 if (auxTools==nullptr) log->error("Unable to create link to LayoutEditorAuxTools");
 // counts used to determine unique internal names
 numAnchors = 0;
 numEndBumpers = 0;
 numEdgeConnectors = 0;
 numTrackSegments = 0;
 numLevelXings = 0;
 numLayoutSlips = 0;
 numLayoutTurnouts = 0;
 numLayoutTurntables = 0;

 xScale= 1.0;
 yScale = 1.0;
_contents = new QVector<Positionable*>();
 // selection variables
 selectionActive = false;
 selectionX = 0.0;
 selectionY = 0.0;
 selectionWidth = 0.0;
 selectionHeight = 0.0;
 _positionableSelection = nullptr;
 _turnoutSelection = nullptr; //new QVector<LayoutTurnout*>();  // LayoutTurnouts
 _xingSelection = nullptr; //new QVector<LevelXing*>();  // LevelXing list
 _slipSelection = nullptr; //new QVector<LayoutSlip*>();  // LayoutSlip list
 _turntableSelection = nullptr;
 _pointSelection = nullptr; //new QVector<PositionablePoint*>();  // PositionablePoint list
 //_labelSelection = nullptr; //new QVector<PositionableLabel*>(); // PositionalLabel list
 _paintScale = 1.0;   // scale for _targetPanel drawing
 openFrame = this;
 // program default turnout size parameters
 turnoutBXDefault = 20.0;  // RH, LH, WYE
 turnoutCXDefault = 20.0;
 turnoutWidDefault = 10.0;
 xOverLongDefault = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 xOverHWidDefault = 10.0;
 xOverShortDefault = 10.0;
 turnoutBX= turnoutBXDefault;  // RH, LH, WYE
 turnoutCX=turnoutCXDefault;
 turnoutWid=turnoutWidDefault;
 xOverLong=xOverLongDefault;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 xOverHWid=xOverHWidDefault;
 xOverShort=xOverShortDefault;
 prevSelectedObject = nullptr;
 _anchorX = 0;
 _anchorY = 0;
//layoutBlockManager = new LayoutBlockManager(this);
 layoutBlockManager = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 blockManger = new BlockManager(this);
 defaultTrackColor =  QColor(Qt::black);;
 defaultOccupiedTrackColor =  QColor(Qt::red);
 defaultAlternativeTrackColor =  QColor(Qt::white);

 defaultTextColor =  QColor(Qt::black);
 turnoutCircleColor = defaultTrackColor; //matches earlier versions
 turnoutCircleSize=2;  //matches earlier versions
 //turnoutList = new QVector<LayoutTurnout*>();  // LayoutTurnouts
 turntableList = new QVector<LayoutTurntable*>(); // Turntable list
 noWarnTurntable = false;

 _positionableSelection = nullptr;//new QVector<Positionable*>();
 //_turnoutSelection = nullptr;//new menuAdd_background_image<LayoutTurnout*>();  // LayoutTurnouts
 foundNeedsConnect = false; // true if found point needs a connection
 //xingList = new QVector<LevelXing*>();  // LevelXing list
 //slipList = new QVector<LayoutSlip*>();  // Layout slip list
 _editable = false;
 _controlLayout = true;
 _positionable = false;
 animatingLayout = true;
 showHelpBar = true;
 bDirty = false;
 noWarnLevelXing = false;
 noWarnSlip = false;
 selectedObject = nullptr;
 selectedPointType = 0;
 skipIncludedTurnout = false;
 mainlineTrackWidth = 4.0F;
 sidelineTrackWidth = 2.0F;
 main = true;
 trackWidth = sidelineTrackWidth;
 _selectionGroup = nullptr;
 turnoutCirclesWithoutEditMode = false;
 ui->actionShow_turnout_circles->setChecked(turnoutCirclesWithoutEditMode);
 isDragging = false;
 foundObject = nullptr;
 layoutTrackList = new QList<LayoutTrack*>();  // TrackSegment list
 drawGrid =false;
 ui->actionShow_grid_in_edit_mode->setChecked(drawGrid);
 antialiasingOn = false;
 noWarnPositionablePoint= false;
 memoryLabelList = new QVector<LEMemoryIcon*>(); // Memory Label List

//makeBackgroundColorMenu(ui->menuSet_Background_color);
 signalIconEditor = nullptr;
 clocks = new QVector<AnalogClock2Display*>();  // fast clocks
 markerImage = new QVector<LocoIcon*>(); // marker images
 multiSensors = new QVector<MultiSensorIcon*>(); // MultiSensor Icons
 backgroundImage = new QVector<PositionableLabel*>();  // background images
 labelImage = new QList<PositionableLabel*>();         //positionable label images
 blockContentsLabelList = new QVector<LEBlockContentsIcon*>(); //BlockContentsIcon Label List
 zoomMenu = new QMenu(tr("Zoom"));
 zoom025Item = new QAction("x 0.25");
 zoom025Item->setCheckable(true);
 zoom05Item = new QAction("x 0.5");
 zoom05Item->setCheckable(true);
 zoom075Item = new QAction("x 0.75");
 zoom075Item->setCheckable(true);
 noZoomItem = new QAction(tr("No Zoom"));
 noZoomItem->setCheckable(true);
 zoom15Item = new QAction("x 1.5");
 zoom15Item->setCheckable(true);
 zoom20Item = new QAction("x 2.0");
 zoom20Item->setCheckable(true);
 zoom30Item = new QAction("x 3.0");
 zoom30Item->setCheckable(true);
 zoom40Item = new QAction("x 4.0");
 zoom50Item = new QAction("x 5.0");
 zoom50Item->setCheckable(true);
 zoom60Item = new QAction("x 6.0");
 zoom60Item->setCheckable(true);
 zoom70Item = new QAction("x 7.0");
 zoom70Item->setCheckable(true);
 zoom80Item = new QAction("x 8.0");
 zoom80Item->setCheckable(true);

 _labelImage = new QVector<PositionableLabel*>(); // layout positionable label images
 sensorImage = new QVector<SensorIcon*>();  // sensor images
 signalHeadImage = new QVector<SignalHeadIcon*>();  // signal head images

 signalMastImage = new QVector<SignalMastIcon*>();  // signal mast images
 signalList = new QVector<SignalHeadIcon*>();  // Signal Head Icons
 signalMastList = new QVector<SignalMastIcon*>();  // Signal Head Icons
 skipIncludedTurnout = false;

 qApp->processEvents();
 panelGridGroup = nullptr;
 trackInProgress = nullptr;
 rectItem = nullptr;
 highlightRect = nullptr;
 noWarnGlobalDelete = false;
 multiSensorFrame = nullptr;
 openDispatcherOnLoad = false;
 useDirectTurnoutControl = false; // Uses Left click for closing points, Right click for throwing.
 turnoutDrawUnselectedLeg = true;

// if(memo==nullptr)
//  memo = new LocoNetSystemConnectionMemo();
// lnSensorManager = memo->getSensorManager();

 turnoutDrawUnselectedLeg = true;
 _showCoordinates = true;
 selectedNeedsConnect = false;
 sensorList = new QVector<SensorIcon*>();  // Sensor Icons
 delayedPopupTrigger = false;
 isDragging = false;
 _defaultToolTip = "";
 toolBarFontSizeMenu = new QMenu(tr("Font Size"));
 wideToolBarCheckBoxMenuItem = new QAction(("Wide ToolBar"), this);
 wideToolBarCheckBoxMenuItem->setCheckable(true);
 dropDownListsDisplayOrderMenu = new QMenu(tr("Drop Down Lists Display Order..."));


 ui->signalMastComboBox->setManager(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager")));
 ui->signalHeadComboBox->setManager(static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")));
 ui->sensorComboBox->setManager(static_cast<SensorManager*>(InstanceManager::getDefault("SensorManager")));
 ui->textMemoryComboBox->setManager(static_cast<MemoryManager*>(InstanceManager::getDefault("MemoryManager")));
 ui->blockSensorComboBox->setManager(static_cast<SensorManager*>(InstanceManager::getDefault("SensorManager")));
 ui->turnoutNameComboBox->setManager(static_cast<TurnoutManager*>(InstanceManager::getDefault("TurnoutManager")));
 ui->extraTurnoutNameComboBox->setManager(static_cast<TurnoutManager*>(InstanceManager::getDefault("TurnoutManager")));
 ui->blockIDComboBox->setManager(static_cast<BlockManager*>(InstanceManager::getDefault("BlockManager")));
 ui->blockContentsComboBox->setManager(static_cast<BlockManager*>(InstanceManager::getDefault("BlockManager")));

 setupComboBox(ui->turnoutNameComboBox, false, true);
 ui-> turnoutNameComboBox->setToolTip(tr("Enter name of physical turnout."));
// ui->turnoutNameComboBox->setEnabledColor(QColor(Qt::darkGreen));
// ui->turnoutNameComboBox->setDisabledColor(QColor(Qt::red));

 setupComboBox(ui->extraTurnoutNameComboBox, false, true);
 ui->extraTurnoutNameComboBox->setToolTip(tr("Enter name of second physical turnout."));

 //the blockPanel is enabled/disabled via selectionListAction above
 setupComboBox(ui->blockIDComboBox, false, true);
 ui->blockIDComboBox->setToolTip(tr("Enter name of Block for new turnout, level crossing, or track segment."));

 setupComboBox(ui->blockSensorComboBox, false, true);
 ui->blockSensorComboBox->setToolTip(tr("Enter name of occupancy sensor for this block; no entry means don't change."));

 setupComboBox(ui->textMemoryComboBox, true, false);
 ui->textMemoryComboBox->setToolTip(tr("Enter name of memory variable to be displayed in a new memory label."));

 ui->blockContentsButton->setToolTip(tr("Select to add a Block label when next clicking with shift down."));

 setupComboBox(ui->blockContentsComboBox, true, false);
 ui->blockContentsComboBox->setToolTip(tr("Select to add a Block label when next clicking with shift down."));
 connect(ui->blockContentsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(blockContentsComboBoxChanged()));

 ui->multiSensorButton->setToolTip(tr("Select to add a MultiSensor when next clicking with shift down."));

 //Signal Mast & text
 ui->signalMastButton->setToolTip(tr("Select to add a Signal Mast icon when next clicking with shift down."));
 setupComboBox(ui->signalMastComboBox, true, false);

 //sensor icon & text
 ui->sensorButton->setToolTip(tr("Select to add a Sensor icon when next clicking with shift down."));

 setupComboBox(ui->sensorComboBox, true, false);
 ui->sensorComboBox->setToolTip(tr("Enter name of Sensor represented by a new Sensor icon."));

 ui->signalButton->setToolTip(tr("Select to add a Signal Head icon when next clicking with shift down."));

 setupComboBox(ui->signalHeadComboBox, true, false);
 ui->signalHeadComboBox->setToolTip(tr("Enter name of Signal Head represented by a new signal head icon."));

 buttonGroup = new QButtonGroup(this);
 buttonGroup->addButton(ui->chkAnchorPoint);

 buttonGroup->addButton(ui->doubleXoverButton);
 buttonGroup->addButton(ui->chkEndBumper);
 buttonGroup->addButton(ui->iconLabelButton);
 buttonGroup->addButton(ui->levelXingButton);
 buttonGroup->addButton(ui->turnoutLHButton);
 buttonGroup->addButton(ui->lhXoverButton);
 buttonGroup->addButton(ui->memoryButton);
 buttonGroup->addButton(ui->multiSensorButton);
 buttonGroup->addButton(ui->turnoutRHButton);
 buttonGroup->addButton(ui->rhXoverButton);
 buttonGroup->addButton(ui->sensorButton);
 buttonGroup->addButton(ui->signalButton);
 buttonGroup->addButton(ui->signalMastButton);
 buttonGroup->addButton(ui->textLabelButton);
 buttonGroup->addButton(ui->trackButton);
 buttonGroup->addButton(ui->layoutDoubleSlipButton);
 buttonGroup->addButton(ui->layoutSingleSlipButton);
 buttonGroup->addButton(ui->turnoutWYEButton);
 //trkBtnGrp = new QButtonGroup(this);
 //trkBtnGrp->addButton(ui->chkDashed);
 //trkBtnGrp->addButton(ui->chkMainline);
 paintScale = 1.0;
 editPanel = new QGraphicsView(ui->centralWidget);
 editPanel->setObjectName("LayoutEditor_editPanel");
 ui->verticalLayout->removeWidget(ui->editPanel);
 ui->verticalLayout->removeWidget(ui->textEdit);
 ui->verticalLayout->addWidget(editPanel);
 ui->verticalLayout->addWidget(ui->textEdit);
 QActionGroup* zoomGroup = new QActionGroup(this);
 zoomGroup->setExclusive(true);
 zoomGroup->addAction(ui->actionNo_zoom);
 ui->actionNo_zoom->setData(1.0);
 if(xScale == 1.0)
  ui->actionNo_zoom->setChecked(true);
 zoomGroup->addAction(ui->actionX_1_5);
 ui->actionX_1_5->setData(1.5);
 if(xScale == 1.5)
  ui->actionX_1_5->setChecked(true);
 zoomGroup->addAction(ui->actionX_2_0);
 ui->actionX_2_0->setData(2.0);
 if(xScale == 2.0)
  ui->actionX_2_0->setChecked(true);
 zoomGroup->addAction(ui->actionX_3_0);
 ui->actionX_3_0->setData(3.0);
 if(xScale == 3.0)
  ui->actionX_3_0->setChecked(true);
 zoomGroup->addAction(ui->actionX_4_0);
 ui->actionX_4_0->setData(4.0);
 if(xScale == 4.0)
  ui->actionX_4_0->setChecked(true);
 connect(zoomGroup, SIGNAL(triggered(QAction*)), this, SLOT(OnZoom_selected(QAction*)));

 //use turnoutCircleSize when you need an int and these when you need a double
     //note: these only change when setTurnoutCircleSize is called
     //using these avoids having to call getTurnoutCircleSize() and
     //the multiply (x2) and the int -> double conversion overhead
 circleRadius = SIZE * getTurnoutCircleSize();
 circleDiameter = 2.0 * circleRadius;

 panelWidth = 600;
 panelHeight =400;

 //editScene = new EditScene(QRectF(-100, -100, 400, 400), this);
 editScene = new EditScene(QRectF(0, 0, panelWidth, panelHeight), this);
 editScene->setObjectName("LayoutEditor_editScene");
 //_targetPanel = editScene;
 defaultBackgroundColor =  editScene->backgroundBrush().color();//QColor(Qt::lightGray);

  // saved state of options when panel was loaded or created
  savedEditMode = true;
  savedPositionable = true;
  savedControlLayout = true;
  savedAnimatingLayout = true;
  savedShowHelpBar = false;
// }

 textColorCount = 0;
 trackColorCount = 0;
 trackOccupiedColorCount = 0;
 trackAlternativeColorCount = 0;
 textColorCount = 0;
 backgroundColorCount=0;
 turnoutCircleColorCount = 0;
 turnoutCircleSizeCount = 0;
 trackColors = new QVector<QColor>(13);
 trackOccupiedColors = new QVector<QColor>(13);
 trackAlternativeColors = new QVector<QColor>(13);
 textColors = new QVector<QColor>(13);
 backgroundColors = new QVector<QColor>(13);
 turnoutCircleColors = new QVector<QColor>(14);
 turnoutCircleSizes = new QVector<int>(10);
 trackColorMenuItems = new QVector<QAction*>(13);
 trackOccupiedColorMenuItems = new QVector<QAction*>(13);
 trackAlternativeColorMenuItems = new QVector<QAction*>(13);
 backgroundColorMenuItems = new QVector<QAction*>(13);
 textColorMenuItems = new QVector<QAction*>(13);
 turnoutCircleColorMenuItems = new QVector<QAction*>(14);
 turnoutCircleSizeMenuItems = new QVector<QAction*>(10);

#if 0
 //
 //background image menu item
 //
// QAction* backgroundItem = new JMenuItem(rb.getString("AddBackground") + "...");
 //optionMenu.add(backgroundItem);
// backgroundItem.addActionListener((ActionEvent event) -> {
//     addBackground();
//     setDirty(true);
//     repaint();
// });
 // TODO: move this to proper menu.
 // set track drawing options menu item
 QAction* jmi = new QAction(tr("SetTrackDrawingOptions"));
 //trackMenu.add(jmi);
 ui->menuOptions->addAction(jmi);
 jmi->setToolTip(tr("SetTrackDrawingOptionsToolTip"));
// jmi.addActionListener((ActionEvent event) -> {
//     LayoutTrackDrawingOptionsDialog ltdod
//             = new LayoutTrackDrawingOptionsDialog(
//                     this, true, getLayoutTrackDrawingOptions());
//     ltdod.setVisible(true);
// });
connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onLayoutTrackDrawingOptionsDialog()));
 //
 //background color menu item
 //
#endif
#if 0
 QMenu* backgroundColorMenu = ui->menuSet_Background_color;//new QMenu(tr("Set Background Color"));
 backgroundColorButtonGroup = new QActionGroup(this);
 backgroundColorButtonMapper = new QSignalMapper();
 connect(backgroundColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_colorBackgroundMenuItemSelected(int)));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Black"),     QColor(Qt::black));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("DarkGray"),  QColor(Qt::darkGray));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Gray"),      QColor(Qt::gray));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("LightGray"), QColor(Qt::lightGray));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("White"),     QColor(Qt::white));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Red"),       QColor(Qt::red));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Pink"),      QColor(255,192,203));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Orange"),    QColor(255, 170, 0));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Yellow"),    QColor(Qt::yellow));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Green"),     QColor(Qt::green));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Blue"),      QColor(Qt::blue));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Magenta"),   QColor(Qt::magenta));
 addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Cyan"),      QColor(Qt::cyan));
 ui->menuOptions->addMenu(backgroundColorMenu);
#endif
#if 0

 //
 //track colors item menu item
 //

 QMenu* trkColourMenu = new QMenu(tr("Default Track Colors"));
 ui->menuOptions->addMenu(trkColourMenu);
 QMenu* trackColorMenu = new QMenu(tr("Default Track Color"));
 trackColorButtonGroup = new QActionGroup(this);
 trackColorButtonMapper = new QSignalMapper();
 connect(trackColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackColorMenuEntry_triggered(int)));
 addTrackColorMenuEntry(trackColorMenu, tr("Black"),     QColor(Qt::black));
 addTrackColorMenuEntry(trackColorMenu, tr("DarkGray"),  QColor(Qt::darkGray));
 addTrackColorMenuEntry(trackColorMenu, tr("Gray"),      QColor(Qt::gray));
 addTrackColorMenuEntry(trackColorMenu, tr("LightGray"), QColor(Qt::lightGray));
 addTrackColorMenuEntry(trackColorMenu, tr("White"),     QColor(Qt::white));
 addTrackColorMenuEntry(trackColorMenu, tr("Red"),       QColor(Qt::red));
 addTrackColorMenuEntry(trackColorMenu, tr("Pink"),      QColor(255,192,203));
 addTrackColorMenuEntry(trackColorMenu, tr("Orange"),    QColor(255, 170, 0));
 addTrackColorMenuEntry(trackColorMenu, tr("Yellow"),    QColor(Qt::yellow));
 addTrackColorMenuEntry(trackColorMenu, tr("Green"),     QColor(Qt::green));
 addTrackColorMenuEntry(trackColorMenu, tr("Blue"),      QColor(Qt::blue));
 addTrackColorMenuEntry(trackColorMenu, tr("Magenta"),   QColor(Qt::magenta));
 addTrackColorMenuEntry(trackColorMenu, tr("Cyan"),      QColor(Qt::cyan));
 trkColourMenu->addMenu(trackColorMenu);
#endif
#if 0
 QMenu* trackOccupiedColorMenu = new QMenu(tr("Default Occupied Track Color"));
 trackOccupiedColorButtonGroup = new QActionGroup(this);
 trackOccupiedColorButtonMapper = new QSignalMapper();
 connect(trackOccupiedColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackOccupiedColorMenuEntry_triggered(int)));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Black"),     QColor(Qt::black));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("DarkGray"),  QColor(Qt::darkGray));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Gray"),      QColor(Qt::gray));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("LightGray"), QColor(Qt::lightGray));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("White"),     QColor(Qt::white));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Red"),       QColor(Qt::red));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Pink"),      QColor(255,192,203));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Orange"),    QColor(255, 170, 0));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Yellow"),    QColor(Qt::yellow));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Green"),     QColor(Qt::green));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Blue"),      QColor(Qt::blue));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Magenta"),   QColor(Qt::magenta));
 addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Cyan"),      QColor(Qt::cyan));
 trkColourMenu->addMenu(trackOccupiedColorMenu);
#endif
#if 0
 QMenu* trackAlternativeColorMenu = new QMenu(tr("Default Alternative Track Color"));
 trackAlternativeColorButtonGroup = new QActionGroup(this);
 trackAlternativeColorButtonMapper = new QSignalMapper();
 connect(trackAlternativeColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackAlternativeColorMenuEntry_triggered(int)));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Black"),     QColor(Qt::black));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("DarkGray"),  QColor(Qt::darkGray));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Gray"),      QColor(Qt::gray));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("LightGray"), QColor(Qt::lightGray));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("White"),     QColor(Qt::white));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Red"),       QColor(Qt::red));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Pink"),      QColor(255,192,203));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Orange"),    QColor(255, 170, 0));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Yellow"),    QColor(Qt::yellow));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Green"),     QColor(Qt::green));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Blue"),      QColor(Qt::blue));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Magenta"),   QColor(Qt::magenta));
 addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Cyan"),      QColor(Qt::cyan));
 trkColourMenu->addMenu(trackAlternativeColorMenu);
#endif
#if 0
 //
 //add text color menu item
 //
 QMenu* textColorMenu = new QMenu(tr("Default Text Color"));
 textColorButtonGroup = new QActionGroup(this);
 textColorButtonMapper = new QSignalMapper();
 connect(textColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(OnDefaultTextColorSelected(int)));
 addTextColorMenuEntry(textColorMenu,  tr("Black"),     QColor(Qt::black));
 addTextColorMenuEntry(textColorMenu,  tr("DarkGray"),  QColor(Qt::darkGray));
 addTextColorMenuEntry(textColorMenu,  tr("Gray"),      QColor(Qt::gray));
 addTextColorMenuEntry(textColorMenu,  tr("LightGray"), QColor(Qt::lightGray));
 addTextColorMenuEntry(textColorMenu,  tr("White"),     QColor(Qt::white));
 addTextColorMenuEntry(textColorMenu,  tr("Red"),       QColor(Qt::red));
 addTextColorMenuEntry(textColorMenu,  tr("Pink"),      QColor(255,192,203));
 addTextColorMenuEntry(textColorMenu,  tr("Orange"),    QColor(255, 170, 0));
 addTextColorMenuEntry(textColorMenu,  tr("Yellow"),    QColor(Qt::yellow));
 addTextColorMenuEntry(textColorMenu,  tr("Green"),     QColor(Qt::green));
 addTextColorMenuEntry(textColorMenu,  tr("Blue"),      QColor(Qt::blue));
 addTextColorMenuEntry(textColorMenu,  tr("Magenta"),   QColor(Qt::magenta));
 addTextColorMenuEntry(textColorMenu,  tr("Cyan"),      QColor(Qt::cyan));
 ui->menuOptions->addMenu(textColorMenu);
#endif

 editPanel->setMouseTracking(true);
 editPanel->setScene(editScene);
 _turnoutSelection = nullptr;


 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(OnScenePos(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)),this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
 // connect(editScene,SIGNAL(sceneDragMove(QGraphicsSceneDragDropEvent*)),this, SLOT(mouseDragged(QGraphicsSceneDragDropEvent*)));
 connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
// connect(trackColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(OnDefaultTrackColorSelected(QAction*)));
// connect(textColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(OnDefaultTextColorSelected(QAction*)));
// connect(backgroundColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_colorBackgroundMenuItemSelected(QAction*)));
 connect(ui->actionBoth_scrollbars, SIGNAL(triggered(bool)), this, SLOT(onActionBoth_scrollbars()));
 connect(ui->actionNo_scrollbars, SIGNAL(triggered(bool)), this, SLOT(onActionNo_scrollbars()));
 connect(ui->actionHorizontal_only, SIGNAL(triggered(bool)), this, SLOT(onActionHorizontal_scrollbars()));
 connect(ui->actionVertical_only, SIGNAL(triggered(bool)), this, SLOT(onActionVertical_scrollbars()));
 connect(ui->actionCalculate_bounds, SIGNAL(triggered(bool)), this, SLOT(onCalculateBounds()));
 connect(ui->actionZoom_Out, SIGNAL(triggered(bool)), this, SLOT(onZoomOut()));
 connect(ui->actionZoom_In, SIGNAL(triggered(bool)), this, SLOT(onZoomIn()));
 connect(ui->actionZoom_to_fit, SIGNAL(triggered(bool)), this, SLOT(zoomToFit()));


 sensorIconEditor = new MultiIconEditor(4);
 sensorIconEditor->setIcon(0, "Active:",":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
 sensorIconEditor->setIcon(1, "Inactive", ":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
 sensorIconEditor->setIcon(2, "Inconsistent:", ":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->setIcon(3, "Unknown:",":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->complete();

 //Signal icon & text
 ui->signalButton->setToolTip(tr("Select to add a Signal Head icon when next clicking with shift down."));

 setupComboBox(ui->signalHeadComboBox, true, false);
 ui->signalHeadComboBox->setToolTip(tr("Enter name of Signal Head represented by a new signal head icon."));

 signalIconEditor = new MultiIconEditor(10);
 signalIconEditor->setIcon(0, "Red:",":/resources/icons/smallschematics/searchlights/left-red-short.gif");
 signalIconEditor->setIcon(1, "Flash red:", ":/resources/icons/smallschematics/searchlights/left-flashred-short.gif");
 signalIconEditor->setIcon(2, "Yellow:", ":/resources/icons/smallschematics/searchlights/left-yellow-short.gif");
 signalIconEditor->setIcon(3, "Flash yellow:", ":/resources/icons/smallschematics/searchlights/left-flashyellow-short.gif");
 signalIconEditor->setIcon(4, "Green:",":/resources/icons/smallschematics/searchlights/left-green-short.gif");
 signalIconEditor->setIcon(5, "Flash green:",":/resources/icons/smallschematics/searchlights/left-flashgreen-short.gif");
 signalIconEditor->setIcon(6, "Dark:",":/resources/icons/smallschematics/searchlights/left-dark-short.gif");
 signalIconEditor->setIcon(7, "Held:",":/resources/icons/smallschematics/searchlights/left-held-short.gif");
 signalIconEditor->setIcon(8, "Lunar",":/resources/icons/smallschematics/searchlights/left-lunar-short-marker.gif");
 signalIconEditor->setIcon(9, "Flash Lunar",":/resources/icons/smallschematics/searchlights/left-flashlunar-short-marker.gif");
 signalIconEditor->complete();

 sensorFrame = new JFrame(tr("Edit Sensor Icons"));
 QWidget* sensorFrameContentPane = sensorFrame->getContentPane();
 //QVBoxLayout* sensorFrameLayout = new QVBoxLayout(sensorFrameContentPane);
 ((QVBoxLayout*)sensorFrameContentPane->layout())->addWidget(new QLabel("  "+tr("Select new file, then click on icon to change.")+"  ")/*,BorderLayout::North*/,0,Qt::AlignTop);
 // sensorFrame.getContentPane().add(sensorIconEditor);
 ((QVBoxLayout*)sensorFrameContentPane->layout())->addWidget(sensorIconEditor/*,BorderLayout::Center*/,0,Qt::AlignCenter);
 sensorFrame->pack();
 sensorFrame->setVisible(false);

 signalFrame = new JFrame(tr("Edit Signal Icons"));
 QWidget* centralWidget = signalFrame->getContentPane();
 //centralWidget->setLayout(new QVBoxLayout());
 centralWidget->layout()->addWidget(new QLabel("</html>Select new image from file,<br>then click an upper preview icon to change it.</html>"));
 centralWidget->layout()->addWidget(signalIconEditor);
 signalFrame->resize(600, 400);
 //signalFrame->setAllowInFrameServlet(false);
 signalFrame->pack();
 signalFrame->setVisible(false);

 //icon label
 ui->iconLabelButton->setToolTip(tr("Select to add a general purpose icon when next clicking with shift down."));

 //change icons...
 //this is enabled/disabled via selectionListAction above
// changeIconsButton.addActionListener((ActionEvent event) -> {
//     if (sensorButton->isChecked()) {
//         sensorFrame.setVisible(true);
//     } else if (signalButton->isChecked()) {
//         signalFrame.setVisible(true);
//     } else if (iconLabelButton->isChecked()) {
//         iconFrame.setVisible(true);
//     } else {
//         //explain to the user why nothing happens
//         JOptionPane.showMessageDialog(null, tr("ChangeIconNotApplied"),
//                 tr("ChangeIcons"), JOptionPane.INFORMATION_MESSAGE);
//     }
// });
 connect(ui->changeIconsButton, SIGNAL(clicked(bool)), this, SLOT(onChangeIconsButton()));

 iconEditor = new MultiIconEditor(1);
 iconEditor->setIcon(0, "",":/resources/icons/smallschematics/tracksegments/block.gif");
 iconEditor->complete();
 iconFrame = new JFrame(tr("Edit Icon"));
 QWidget* iconFrameCentralWidget = getContentPane();
 QVBoxLayout* iconFrameLayout = new QVBoxLayout(iconFrameCentralWidget);
 iconFrameLayout->addWidget(iconEditor);
 iconFrame->pack();

 // Turnout Properties
 connect(ui->turnoutRHButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->turnoutLHButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->turnoutWYEButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->doubleXoverButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->rhXoverButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->lhXoverButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->layoutSingleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->layoutDoubleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onTurnoutProperties()));
 connect(ui->layoutSingleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onSecondTurnoutProperties()));
 connect(ui->layoutDoubleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onSecondTurnoutProperties()));
 connect(ui->trackButton, SIGNAL(toggled(bool)), this, SLOT(onTrackSegmentProperties()));
 connect(ui->turnoutRHButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->turnoutLHButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->turnoutWYEButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->doubleXoverButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->rhXoverButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->lhXoverButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->layoutSingleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->layoutDoubleSlipButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->levelXingButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->trackButton, SIGNAL(toggled(bool)), this, SLOT(onBlockProperties()));
 connect(ui->signalMastButton, SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));
 connect(ui->sensorButton,SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));
 connect(ui->signalButton, SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));
 connect(ui->textLabelButton,SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));
 connect(ui->memoryButton,SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));
 connect(ui->blockContentsButton,SIGNAL(toggled(bool)), this, SLOT(onMiscFields()));

 onTrackSegmentProperties();
 onSecondTurnoutProperties();
 onTrackSegmentProperties();
 onBlockProperties();


 ui->changeIconsButton->setToolTip(tr("Select to change icons used to represent Sensors, Signal Heads or Label (whichever is checked at the right)."));
 ui->changeIconsButton->setEnabled(false);
connect(ui->sensorButton, SIGNAL(toggled(bool)), this, SLOT(onChangeIcons()));
connect(ui->signalButton, SIGNAL(toggled(bool)), this, SLOT(onChangeIcons()));
connect(ui->iconLabelButton, SIGNAL(toggled(bool)), this, SLOT(onChangeIcons()));


 autoAssignBlocks = true;
 tooltipsInEditMode = true;
 tooltipsWithoutEditMode = false;
 _loadFailed = false;
 _debug = true;
 _ignore = false;
 _urlMap = new QMap<QString, QString>();
 _newIcon = nullptr;
 _delete = false;
 finder = new LayoutEditorFindItems(this);
 //ui->menuOptions->addMenu( setupTurnoutSubMenu());

// register the resulting panel for later configuration
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");

 if (cm != nullptr) {
     cm->registerUser(this);
 }

 // confirm that panel hasn't already been loaded
 if (PanelMenu::instance()->isPanelNameUsed(name))
 {
  log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }
 //operational variables for enter track width pane
 enterTrackWidthFrame = nullptr;
 enterTrackWidthOpen = false;
 trackWidthChange = false;
 sidelineTrackWidthField = new JTextField(6);
 mainlineTrackWidthField = new JTextField(6);

 //operational variables for enter grid sizes pane
 enterGridSizesFrame = nullptr;
 enterGridSizesOpen = false;
 gridSizesChange = false;
 primaryGridSizeField = new JTextField(6);
 secondaryGridSizeField = new JTextField(6);

 //operational variables for enter reporter pane
 enterReporterFrame = nullptr;
 reporterOpen = false;
 xPositionField = new JTextField(6);
 yPositionField = new JTextField(6);
 reporterNameField = new JTextField(6);

 //operational variables for scale/translate track diagram pane
 scaleTrackDiagramFrame = nullptr;
 scaleTrackDiagramOpen = false;
 xFactorField = new JTextField(6);
 yFactorField = new JTextField(6);
 xTranslateField = new JTextField(6);
 yTranslateField = new JTextField(6);
 gDDMDO = JmriBeanComboBox::DisplayOptions::DISPLAYNAME;
 _positionableSelection = new QVector<Positionable*>();
 _layoutTrackSelection = QList<LayoutTrack*>();

 xMoveField = new JTextField(6);
 yMoveField = new JTextField(6);
 ui->menuBar->setVisible(true);
 setupOptionMenu(ui->menuBar);
 setupToolsMenu(ui->menuBar);
 setupZoomMenu(ui->menuBar);
 setupMarkerMenu(ui->menuBar);
 setupDispatcherMenu(ui->menuBar);
 //setup Help menu
 addHelpMenu("package.jmri.jmrit.display.LayoutEditor", true);

 //initialize preferences
 UserPreferencesManager* prefsMgr= static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
 if(prefsMgr)
 {
     QString windowFrameRef = getWindowFrameRef();

     QVariant prefsProp = prefsMgr->getProperty(windowFrameRef, "toolBarSide");
     //log.debug("{}.toolBarSide is {}", windowFrameRef, prefsProp);
     if (prefsProp != QVariant()) {
         ToolBarSide::TOOLBARSIDES newToolBarSide = ToolBarSide::getName( prefsProp.toString());
         setToolBarSide(newToolBarSide);
     }

     //Note: since prefs default to false and we want wide to be the default
     //we invert it and save it as thin
     bool prefsToolBarIsWide = prefsMgr->getSimplePreferenceState(windowFrameRef + ".toolBarThin");
     log->debug(tr("%1.toolBarThin is %2").arg(windowFrameRef).arg(prefsProp.toString()));
     setToolBarWide(prefsToolBarIsWide);

     bool prefsShowHelpBar = prefsMgr->getSimplePreferenceState(windowFrameRef + ".showHelpBar");
     //log.debug("{}.showHelpBar is {}", windowFrameRef, prefsShowHelpBar);
     setShowHelpBar(prefsShowHelpBar);

     bool prefsAntialiasingOn = prefsMgr->getSimplePreferenceState(windowFrameRef + ".antialiasingOn");
     //log.debug("{}.antialiasingOn is {}", windowFrameRef, prefsAntialiasingOn);
     setAntialiasingOn(prefsAntialiasingOn);

     bool prefsHighlightSelectedBlockFlag
             = prefsMgr->getSimplePreferenceState(windowFrameRef + ".highlightSelectedBlock");
     //log.debug("{}.highlightSelectedBlock is {}", windowFrameRef, prefsHighlightSelectedBlockFlag);
     setHighlightSelectedBlock(prefsHighlightSelectedBlockFlag);

     prefsProp = prefsMgr->getProperty(windowFrameRef, "toolBarFontSize");
     //log.debug("{} prefsProp toolBarFontSize is {}", windowFrameRef, prefsProp);
     //if (prefsProp != null) {
     //float toolBarFontSize = Float.parseFloat(prefsProp.toString());
     //setupToolBarFontSizes(toolBarFontSize);
     //}
     updateAllComboBoxesDropDownListDisplayOrderFromPrefs();
#if 0
     //this doesn't work as expected (1st one called messes up 2nd?)
     Point prefsWindowLocation = prefsMgr.getWindowLocation(windowFrameRef);
     Dimension prefsWindowSize = prefsMgr.getWindowSize(windowFrameRef);
     log.debug("prefsMgr.prefsWindowLocation({}) is {}", windowFrameRef, prefsWindowLocation);
     log.debug("prefsMgr.prefsWindowSize is({}) {}", windowFrameRef, prefsWindowSize);

     //Point prefsWindowLocation = null;
     //Dimension prefsWindowSize = null;
     //use this instead?
     if (true) { //(Nope, it's not working ether: prefsProp always comes back null)
         prefsProp = prefsMgr.getProperty(windowFrameRef, "windowRectangle2D");
         log.debug("prefsMgr.getProperty({}, \"windowRectangle2D\") is {}", windowFrameRef, prefsProp);

         if (prefsProp != null) {
             Rectangle2D windowRectangle2D = (Rectangle2D) prefsProp;
             prefsWindowLocation.setLocation(windowRectangle2D.getX(), windowRectangle2D.getY());
             prefsWindowSize.setSize(windowRectangle2D.getWidth(), windowRectangle2D.getHeight());
         }
     }

     if ((prefsWindowLocation != null) && (prefsWindowSize != null)
             && (prefsWindowSize.width >= 640) && (prefsWindowSize.height >= 480)) {
         //note: panel width & height comes from the saved (xml) panel (file) on disk
         setLayoutDimensions(prefsWindowSize.width, prefsWindowSize.height,
                 prefsWindowLocation.x, prefsWindowLocation.y,
                 panelWidth, panelHeight, true);
     }
#endif
 }//); //Inst

 ui->menuBar->setVisible(true);
}
 void LayoutEditor::onLayoutTrackDrawingOptionsDialog()
 {
  LayoutTrackDrawingOptionsDialog* ltdod
          = new LayoutTrackDrawingOptionsDialog(
                  this, true, getLayoutTrackDrawingOptions());
  ltdod->setVisible(true);

 }

 void LayoutEditor::onChangeIcons()
 {
  ui->changeIconsButton->setEnabled(ui->sensorButton->isChecked() || ui->signalButton->isChecked() || ui->iconLabelButton->isChecked());
  onMiscFields();
 }

 void LayoutEditor::onTurnoutProperties()
 {
  bool e = (ui->turnoutRHButton->isChecked()
            || ui->turnoutLHButton->isChecked()
            || ui->turnoutWYEButton->isChecked()
            || ui->doubleXoverButton->isChecked()
            || ui->rhXoverButton->isChecked()
            || ui->lhXoverButton->isChecked()
            || ui->layoutSingleSlipButton->isChecked()
            || ui->layoutDoubleSlipButton->isChecked());
  log->debug(tr("turnoutPropertiesPanel is %1").arg(e ? "enabled" : "disabled"));

              //  for (Component i : turnoutNamePanel.getComponents())
//  {
//      i.setEnabled(e);
//  }
  ui->turnoutNameComboBox->setEnabled(e);
  ui->turnoutNameLabel->setEnabled(e);

//  for (Component i : rotationPanel.getComponents()) {
//      i.setEnabled(e);
//  }
  ui->rotationComboBox->setEnabled(e);

  onMiscFields();

 }
 void LayoutEditor::onSecondTurnoutProperties()
 {
  //second turnout property
     bool e = (ui->layoutSingleSlipButton->isChecked() || ui->layoutDoubleSlipButton->isChecked());
     log->debug(tr("extraTurnoutPanel is %1").arg(e ? "enabled" : "disabled"));

//     for (Component i : extraTurnoutPanel.getComponents()) {
//         i.setEnabled(e);
//     }
     ui->extraTurnoutLabel->setEnabled(e);
     ui->extraTurnoutNameComboBox->setEnabled(e);
     onMiscFields();

 }
void LayoutEditor::onTrackSegmentProperties()
{
     //track Segment properties
    bool e = ui->trackButton->isChecked();
     log->debug(tr("trackSegmentPropertiesPanel is %1").arg(e ? "enabled" : "disabled"));

//     for (Component i : trackSegmentPropertiesPanel.getComponents()) {
//         i.setEnabled(e);
//     }
     ui->chkDashed->setEnabled(e);
     ui->chkMainline->setEnabled(e);
     ui->levelXingButton->setEnabled(e);
     onMiscFields();

}

void LayoutEditor::onBlockProperties()
{
     //block properties
     bool e = (ui->turnoutRHButton->isChecked()
             || ui->turnoutLHButton->isChecked()
             || ui->turnoutWYEButton->isChecked()
             || ui->doubleXoverButton->isChecked()
             || ui->rhXoverButton->isChecked()
             || ui->lhXoverButton->isChecked()
             || ui->layoutSingleSlipButton->isChecked()
             || ui->layoutDoubleSlipButton->isChecked()
             || ui->levelXingButton->isChecked()
             || ui->trackButton->isChecked());
     log->debug(tr("blockPanel is %1").arg(e ? "enabled" : "disabled"));

#if 0 //dock panel?
     if (ui->blockPropertiesPanel != null) {
         for (Component i : blockPropertiesPanel.getComponents()) {
             i.setEnabled(e);
         }

         if (e) {
             blockPropertiesPanel.setBackground(Color.lightGray);
         } else {
             blockPropertiesPanel.setBackground(new Color(238, 238, 238));
         }
     } else
#endif
     {
         ui->blockNameLabel->setEnabled(e);
//         blockIDComboBox.setEnabled(e);
         ui->blockSensorNameLabel->setEnabled(e);
//         ui->blockSensorLabel.setEnabled(e);
         ui->blockSensorComboBox->setEnabled(e);
     }
     onMiscFields();
}

void LayoutEditor::onMiscFields()
{
     //enable/disable text label, memory & block contents text fields
     ui->textLabel->setEnabled(ui->textLabelButton->isChecked());
     ui->textMemoryComboBox->setEnabled(ui->memoryButton->isChecked());
//     ui->blockContentsComboBox->setEnabled(ui->blockContentsButton->isChecked());

     //enable/disable signal mast, sensor & signal head text fields
     ui->signalMastComboBox->setEnabled(ui->signalMastButton->isChecked());
     ui->sensorComboBox->setEnabled(ui->sensorButton->isChecked());
     ui->signalHeadComboBox->setEnabled(ui->signalButton->isChecked());

}

void LayoutEditor::blockContentsComboBoxChanged()
{
 if (highlightSelectedBlockFlag) {
     highlightBlockInComboBox(ui->blockContentsComboBox);
 }

}
/*public*/ void LayoutEditor::setSize(int w, int h)
{
 log->debug("Frame size now w=" + QString::number(w) + ", h=" + QString::number(h));
 Editor::resize(w, h);
}
#if 0
/*public*/ QMenu* LayoutEditor::setupTurnoutSubMenu()
{
 //turnout options submenu
 QMenu* turnoutOptionsMenu = new QMenu(tr("Turnout Options"));
 //optionMenu.add(turnoutOptionsMenu);

 // circle on Turnouts
 turnoutCirclesOnItem = new QAction(tr("Show Turnout Circles"),this);
 turnoutCirclesOnItem->setCheckable(true);
 turnoutOptionsMenu->addAction(turnoutCirclesOnItem);
// turnoutCirclesOnItem.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         turnoutCirclesWithoutEditMode = turnoutCirclesOnItem->isChecked();
//         repaint();
//     }
// });
 connect(turnoutCirclesOnItem, SIGNAL(triggered(bool)), this, SLOT(On_turnoutCirclesOnItem_triggered(bool)));
 turnoutCirclesOnItem->setChecked(turnoutCirclesWithoutEditMode);

 // select turnout circle color
 QMenu* turnoutCircleColorMenu = new QMenu(tr("Set Turnout Circle Color"));
 turnoutCircleColorButtonGroup = new QActionGroup(this);
 turnoutCircleColorButtonMapper = new QSignalMapper(this);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Use Default Track Color"), defaultTrackColor);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Black"), Qt::black);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Dark Gray"), Qt::darkGray);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Gray"), Qt::gray);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Light Gray"), Qt::lightGray);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("White"), Qt::white);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Red"), Qt::red);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Pink"), QColor(255,192,203));
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Orange"), QColor(255, 165, 0));
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Yellow"), Qt::yellow);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Green"), Qt::green);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Blue"), Qt::blue);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Magenta"), Qt::magenta);
 addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, tr("Cyan"), Qt::cyan);
 turnoutOptionsMenu->addMenu(turnoutCircleColorMenu);
 connect(turnoutCircleColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(On_turnoutCircleColorButtonMapper_triggered(int)));

 // select turnout circle size
#if 0
 QMenu* turnoutCircleSizeMenu = new QMenu(tr("Turnout Circle Size"));
 turnoutCircleSizeButtonGroup = new QActionGroup(this);
 turnoutCircleSizeButtonMapper = new QSignalMapper(this);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "1", 1);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "2", 2);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "3", 3);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "4", 4);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "5", 5);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "6", 6);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "7", 7);
 addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "8", 8);
 turnoutOptionsMenu->addMenu(turnoutCircleSizeMenu);
 connect(turnoutCircleSizeButtonMapper, SIGNAL(mapped(int)), this, SLOT(On_turnoutCircleSizeButtonMapper_triggered(int)));
#endif
 // enable drawing of unselected leg (helps when diverging angle is small)
 turnoutDrawUnselectedLegItem = new QAction(tr("Draw Unselected Turnout Leg"),this);
 turnoutDrawUnselectedLegItem->setCheckable(true);
 turnoutOptionsMenu->addAction(turnoutDrawUnselectedLegItem);
// turnoutDrawUnselectedLegItem.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         turnoutDrawUnselectedLeg = turnoutDrawUnselectedLegItem->isChecked();
//         repaint();
//     }
// });
 connect(turnoutDrawUnselectedLegItem, SIGNAL(triggered(bool)), this, SLOT(On_turnoutDrawUnselectedLegItem_triggered(bool)));
 turnoutDrawUnselectedLegItem->setChecked(turnoutDrawUnselectedLeg);

 //add show grid menu item
  autoAssignBlocksItem = new QAction(tr("Automatically Assign Blocks to Track"), this);
  autoAssignBlocksItem->setCheckable(true);
  turnoutOptionsMenu->addAction(autoAssignBlocksItem);
//  autoAssignBlocksItem.addActionListener((ActionEvent event) -> {
//      autoAssignBlocks = autoAssignBlocksItem->isChecked();
//  });
  connect(autoAssignBlocksItem, SIGNAL(triggered(bool)), this, SLOT(on_autoAssignBlocksItem_triggered(bool)));
  autoAssignBlocksItem->setChecked(autoAssignBlocks);

  //
  //add hideTrackSegmentConstructionLines menu item
  //
  hideTrackSegmentConstructionLines = new QAction(tr("Hide Track Construction Lines"), this);
  hideTrackSegmentConstructionLines->setCheckable(true);
  ui->menuOptions->addAction(hideTrackSegmentConstructionLines);
 // hideTrackSegmentConstructionLines.addActionListener((ActionEvent event) -> {
//      int show = TrackSegment.SHOWCON;

//      if (hideTrackSegmentConstructionLines->isChecked()) {
//          show = TrackSegment.HIDECONALL;
//      }

//      for (TrackSegment t : trackList) {
//          t.hideConstructionLines(show);
//      }
//      repaint();
//  });
  connect(hideTrackSegmentConstructionLines, SIGNAL(toggled(bool)), this, SLOT(on_hideTrackSegmentConstructionLines_toggled(bool)));
  hideTrackSegmentConstructionLines->setChecked(autoAssignBlocks);

  //
  //add "use direct turnout control" menu item
  //
  useDirectTurnoutControlItem = new QAction(tr("Use Direct Turnout Control"), this);   //IN18N
  useDirectTurnoutControlItem->setCheckable(true);
  turnoutOptionsMenu->addAction(useDirectTurnoutControlItem);
//  useDirectTurnoutControlItem.addActionListener((ActionEvent event) -> {
//      useDirectTurnoutControl = false;

//      if (useDirectTurnoutControlItem->isChecked()) {
//          useDirectTurnoutControl = true;
//      }
//  });
  connect(useDirectTurnoutControlItem, SIGNAL(triggered(bool)), this, SLOT(on_useDirectTurnoutControlItem_triggered(bool)));
  useDirectTurnoutControlItem->setChecked(useDirectTurnoutControl);

 return turnoutOptionsMenu;
}
#endif
void LayoutEditor::On_turnoutCirclesOnItem_triggered(bool)
{
 turnoutCirclesWithoutEditMode = turnoutCirclesOnItem->isChecked();
 repaint();
}

void LayoutEditor::On_turnoutDrawUnselectedLegItem_triggered(bool)
{
 turnoutDrawUnselectedLeg = turnoutDrawUnselectedLegItem->isChecked();
 repaint();
}

void LayoutEditor::on_autoAssignBlocksItem_triggered(bool b)
{
 autoAssignBlocks = b;
}

void LayoutEditor::on_hideTrackSegmentConstructionLines_toggled(bool /*b*/)
{
  int show = TrackSegment::SHOWCON;

  if (hideTrackSegmentConstructionLines->isChecked()) {
      show = TrackSegment::HIDECONALL;
  }

  for (LayoutTrack* t : *layoutTrackList) {
      ((TrackSegment*)t)->hideConstructionLines(show);
  }
  repaint();
}

void LayoutEditor::on_useDirectTurnoutControlItem_triggered(bool)
{
 useDirectTurnoutControl = false;

 if (useDirectTurnoutControlItem->isChecked()) {
     useDirectTurnoutControl = true;
 }

}
void LayoutEditor::addTurnoutCircleColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color)
{
//        ActionListener a = new ActionListener() {
//            final Color desiredColor = color;

//            public void actionPerformed(ActionEvent e) {
//                turnoutCircleColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        };
 const QIcon icon = getColourIcon(color);
 QAction* r = new QAction(icon, name, this);
 r->setCheckable(true);
 //r->setData(_colors.indexOf(color));
 turnoutCircleColorButtonGroup->addAction(r);
 turnoutCircleColorButtonMapper->setMapping(r, turnoutCircleColorCount);
 //r.addActionListener(a);
 connect(r, SIGNAL(triggered()), turnoutCircleColorButtonMapper, SLOT(map()));
 if (turnoutCircleColor==(color)) {
     r->setChecked(true);
 } else {
     r->setChecked(false);
 }
 menu->addAction(r);
 turnoutCircleColorMenuItems->replace(turnoutCircleColorCount, r);
 turnoutCircleColors->replace(turnoutCircleColorCount, color);
 turnoutCircleColorCount++;
}

void LayoutEditor::On_turnoutCircleColorButtonMapper_triggered(int i)
{
 turnoutCircleColor = /*desiredColor*/turnoutCircleColors->at(i);
 setDirty(true);
 repaint();

}

void LayoutEditor::addTurnoutCircleSizeMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ int size)
{
//        ActionListener a = new ActionListener() {
//            final int desiredSize = size;

//            public void actionPerformed(ActionEvent e) {
//                if (turnoutCircleSize != desiredSize) {
//                    turnoutCircleSize = desiredSize;
//                    setDirty(true);
//                    repaint();
//                }
//            }
//        };

 QAction* r = new QAction(name, this);
 r->setCheckable(true);
 r->setData(size);
 //r.addActionListener(a);
 turnoutCircleSizeButtonGroup->addAction(r);
 turnoutCircleSizeButtonMapper->setMapping(r, size);
 connect(r, SIGNAL(triggered(bool)), turnoutCircleSizeButtonMapper, SLOT(map()));
 if (turnoutCircleSize == size) {
     r->setChecked(true);
 } else {
     r->setChecked(false);
 }
 menu->addAction(r);
 turnoutCircleSizeMenuItems->replace(turnoutCircleSizeCount, r);
 turnoutCircleSizes->replace(turnoutCircleSizeCount, size);
 turnoutCircleSizeCount++;
}

void LayoutEditor::On_turnoutCircleSizeButtonMapper_triggered(int size)
{
 int desiredSize = size;//act->data().toInt();
 if (turnoutCircleSize != desiredSize)
 {
  turnoutCircleSize = desiredSize;
  setDirty(true);
  repaint();
 }
}

/*protected*/ void  LayoutEditor::targetWindowClosingEvent(/*WindowEvent*/ QCloseEvent* /*e*/)
{
 bool save = (isDirty() || (savedEditMode != isEditable())
         || (savedPositionable != allPositionable())
         || (savedControlLayout != allControlling())
         || (savedAnimatingLayout != animatingLayout)
         || (savedShowHelpBar != showHelpBar));
 targetWindowClosing(save);
}

/**
 * Set up editable JmriBeanComboBoxes
 *
 * @param inComboBox     the editable JmriBeanComboBoxes to set up
 * @param inValidateMode bool: if true, valid text == green, invalid text
 *                       == red background; if false, valid text == green,
 *                       invalid text == yellow background
 * @param inEnable       bool to enable / disable the JmriBeanComboBox
 */
/*public*/ /*static*/ void LayoutEditor::setupComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox, bool inValidateMode, bool inEnable) {
    setupComboBox(inComboBox, inValidateMode, inEnable, !inValidateMode);
}

/**
 * Set up editable JmriBeanComboBoxes
 *
 * @param inComboBox     the editable JmriBeanComboBoxes to set up
 * @param inValidateMode bool: if true, valid text == green, invalid text
 *                       == red background; if false, valid text == green,
 *                       invalid text == yellow background
 * @param inEnable       bool to enable / disable the JmriBeanComboBox
 * @param inFirstBlank   bool to enable / disable the first item being
 *                       blank
 */
/*public*/ /*static*/ void LayoutEditor::setupComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank) {
    log->debug("LE setupComboBox called");

    inComboBox->setEnabled(inEnable);
    inComboBox->setEditable(true);
    inComboBox->setValidateMode(inValidateMode);
    inComboBox->setCurrentText("");

    // This has to be set before calling setupComboBoxMaxRows
    // (otherwise if inFirstBlank then the  number of rows will be wrong)
    inComboBox->setFirstItemBlank(inFirstBlank);

    // set the max number of rows that will fit onscreen
//    JComboBoxutil->setupComboBoxMaxRows(inComboBox);

    inComboBox->setCurrentIndex(-1);
}

void LayoutEditor::OnScenePos(QGraphicsSceneMouseEvent* e)
{
 calcLocation(e->scenePos(), 0,0);
 ui->xLabel->setText(QString("%1").arg(xLoc));
 ui->yLabel->setText(QString("%1").arg(yLoc));
 Qt::MouseButtons b = e->buttons();
 if (b == Qt::RightButton || e->modifiers()&Qt::ShiftModifier)
  mouseDragged(e);

}
/*
 * Get mouse coordinates and adjust for zoom
 */
/*private*/ void LayoutEditor::calcLocation(QPointF scenePos, int dX, int dY)
{
 xLoc = (int)((scenePos.x() + dX)/getPaintScale());
 yLoc = (int)((scenePos.y() + dY)/getPaintScale());
 dLoc = scenePos;
}
double LayoutEditor::getPaintScale()
{
 return paintScale;
}
/**
 * Handle a mouse pressed event
 */
/*public*/ void LayoutEditor::mousePressed(QGraphicsSceneMouseEvent* event)
{
 bool bMeta = event->modifiers()&Qt::MetaModifier;
 bool bAlt = event->modifiers()&Qt::AltModifier;
 bool bShift =  event->modifiers()&Qt::ShiftModifier;
 bool bPopupTrigger = event->button() & Qt::RightButton;
 bool bControl = event->modifiers()&Qt::ControlModifier;

 // initialize cursor position
 _anchorX = xLoc;
 _anchorY = yLoc;
 _lastX = _anchorX;
 _lastY = _anchorY;
 delayedPopupTrigger= false;
 isDragging = false;
 calcLocation(event->scenePos(),0,0);
 if (isEditable())
 {
  bool prevSelectionActive = selectionActive;
  selectionActive = false;
  ui->xLabel->setText(QString("%1").arg(xLoc));
  ui->yLabel->setText(QString("%1").arg(yLoc));
  if (/*event.isPopupTrigger()*/ bPopupTrigger)
  {
//   if (event.isMetaDown() || event.isAltDown())
//   {
//   if(event->modifiers()&Qt::MetaModifier || event->modifiers()&Qt::AltModifier)
//   {
    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
    delayedPopupTrigger = true;
//   }
//   else
//   {
//    // no possible conflict with moving, display the popup now
//    checkPopUp(event);
//   }
  }
  if (bMeta || (!bAlt && !bShift))
  {
   // if moving an item, identify the item for mouseDragging
   selectedObject = nullptr;
   selectedPointType = NONE;
   if (findLayoutTracksHitPoint(dLoc))
   {
    selectedObject = foundObject;
    selectedPointType = foundPointType;
    //selectedNeedsConnect = foundNeedsConnect;
    startDel = QPointF(foundLocation.x()-dLoc.x(), foundLocation.y()-dLoc.y());
    foundObject = nullptr;
   }
   else
   {
    selectedObject = checkMarkers(dLoc);
    if (selectedObject!=nullptr)
    {
     selectedPointType = MARKER;
     startDel= QPointF((((LocoIcon*)selectedObject)->x()-dLoc.y()),(((LocoIcon*)selectedObject)->y()-dLoc.y()));
     selectedNeedsConnect = false;
    }
    else
    {
     selectedObject = checkClocks(dLoc);
     if (selectedObject!=nullptr)
     {
      selectedPointType = LAYOUT_POS_JCOMP;
      //startDel.setLocation((((PositionableJComponent)selectedObject).getX()-dLoc.getX()),(((PositionableJComponent)selectedObject).getY()-dLoc.getY()));
      startDel= QPointF((((AnalogClock2Display*)selectedObject)->x()-dLoc.y()),(((AnalogClock2Display*)selectedObject)->x()-dLoc.y()));
      selectedNeedsConnect = false;
     }
     else
     {
      selectedObject = checkMultiSensors(dLoc);
      if (selectedObject!=nullptr)
      {
       selectedPointType = MULTI_SENSOR;
       startDel= QPointF((((MultiSensorIcon*)selectedObject)->x()-dLoc.y()), (((MultiSensorIcon*)selectedObject)->x()-dLoc.y()));
       //selectedNeedsConnect = false;
      }
     }
    }
    if (selectedObject==nullptr)
    {
     selectedObject = checkSensorIcons(dLoc);
     if (selectedObject==nullptr)
     {
      selectedObject = checkSignalHeadIcons(dLoc);
      if (selectedObject==nullptr)
      {
       selectedObject = checkLabelImages(dLoc);
       if(selectedObject==nullptr)
       {
        selectedObject = checkSignalMastIcons(dLoc);
       }
      }
     }
     if (selectedObject!=nullptr)
     {
      selectedPointType = LAYOUT_POS_LABEL;
      //startDel.setLocation((((PositionableLabel*)selectedObject)->getX()-dLoc.getX()),                     (((PositionableLabel*)selectedObject)->getY()-dLoc.getY()));
      startDel = QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),(((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
      //if (selectedObject instanceof MemoryIcon)
      if(qobject_cast<LEMemoryIcon*>(selectedObject)!= nullptr)
      {
       LEMemoryIcon* pm = (LEMemoryIcon*) selectedObject;
       if (pm->getPopupUtility()->getFixedWidth()==0)
       {
        //startDel.setLocation((pm->getOriginalX()-dLoc.getX()),                                (pm->getOriginalY()-dLoc.getY()));
        startDel = QPointF((pm->getOriginalX()-dLoc.y()),                                (pm->getOriginalY()-dLoc.y()));
       }
      }
     selectedNeedsConnect = false;
     }
     else
     {
      selectedObject = checkBackgrounds(dLoc);
      if (selectedObject!=nullptr)
      {
       selectedPointType = LAYOUT_POS_LABEL;
       //startDel.setLocation((((PositionableLabel)selectedObject).getX()-dLoc.x()),                            (((PositionableLabel)selectedObject).getY()-dLoc.y()));
       startDel = QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),
                          (((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
      selectedNeedsConnect = false;
      }
     }
    }
   }
  }
  else if (bShift && ui->trackButton->isChecked() /*&& (!event.isPopupTrigger()) */)
  {
   // starting a Track Segment, check for free connection point
   selectedObject = nullptr;
   if (findLayoutTracksHitPoint(dLoc))
   {
    // match to a free connection point
    beginObject = foundObject;
    beginPointType = foundPointType;
    beginLocation = foundLocation;
   }
   else {
    foundObject = nullptr;
    beginObject = nullptr;
   }
  }
  else if ( (!bShift) && (!bControl) /*&& (!event.isPopupTrigger())*/ && !bPopupTrigger)
  {
   // check if controlling a turnout in edit mode
    selectedObject = nullptr;
    if (allControlling())
    {
     checkControls(false);
    }
    // initialize starting selection - cancel any previous selection rectangle
    selectionActive = true;
    selectionX = dLoc.x();
    selectionY = dLoc.y();
    selectionWidth = 0.0;
    selectionHeight = 0.0;
   }
   if (prevSelectionActive) /*repaint();*/
    paintTargetPanel(editScene);
  } // isEditable

  else if (allControlling() && /*(!event.isMetaDown()) && (!event.isPopupTrigger()) &&*/
           (!(event->modifiers()&Qt::AltModifier)) &&(!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // not in edit mode - check if mouse is on a turnout (using wider search range)
   selectedObject = nullptr;
   checkControls(true);
 }
 else if ( (/*event.isMetaDown() ||*/ /*event.isAltDown()*/event->modifiers()&Qt::AltModifier) &&
              (!(/*event.isShiftDown()*/event->modifiers()&Qt::ShiftModifier)) && (!(/*event.isControlDown()*/event->modifiers()&Qt::ControlModifier)) )
 {
  // not in edit mode - check if moving a marker if there are any
  selectedObject = checkMarkers(dLoc);
  if (selectedObject!=nullptr)
  {
   selectedPointType = MARKER;
   startDel= QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),
                                            (((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
   //selectedNeedsConnect = false;
  }
 }
 else if ( /*event.isPopupTrigger() && */!/*event.isShiftDown()*/(event->modifiers()&Qt::ShiftModifier) )
 {
  // not in edit mode - check if a marker popup menu is being requested
  LocoIcon* lo = checkMarkers(dLoc);
  if (lo!=nullptr) delayedPopupTrigger = true;
 }
 if (/*!event.isPopupTrigger() &&*/ !isDragging)
 {
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  {
//   if(static_cast<SignalHeadIcon*>(selections.at(0))!=  nullptr)
//    ((SignalHeadIcon*)selections.at(0))->doMousePressed(event);
//   else
//   if(qobject_cast<SensorIcon*>(selection->self()s.at(0))!=  nullptr)
//    ((SensorIcon*)selections.at(0))->doMousePressed(event);
//   else
    selections.at(0)->doMousePressed(event);
  }
 }
 //thisPanel.setFocusable(true);
 //thisPanel.requestFocusInWindow();
 return;
}

/**
 * Called by {@link #mousePressed} to determine if the mouse click was in a turnout control location.
 * If so, update selectedPointType and selectedObject for use by {@link #mouseReleased}.
 * <p>
 * If there's no match, selectedObject is set to null and selectedPointType
 * is left referring to the results of the checking the last track on the list.
 * <p>
 * Refers to the current value of {@link #layoutTrackList) and {@link #dLoc}.
 *
 * @param useRectangles set true to use rectangle; false for circles.
 */
/*private*/ void LayoutEditor::checkControls(bool useRectangles) {
    selectedObject = nullptr;  // deliberate side-effect
    for (LayoutTrack* theTrack : *layoutTrackList)
    {
        selectedPointType = theTrack->findHitPointType(dLoc, useRectangles); // deliberate side-effect
        if (LayoutTrack::isControlHitType(selectedPointType)) {
            selectedObject = theTrack; // deliberate side-effect
            return;
        }
    }
}

// optional parameter avoid
/*private*/ bool LayoutEditor::findLayoutTracksHitPoint(
        /*@Nonnull*/ QPointF loc, bool requireUnconnected) {
    return findLayoutTracksHitPoint(loc, requireUnconnected, nullptr);
}

// optional parameter requireUnconnected
/*private*/ bool LayoutEditor::findLayoutTracksHitPoint(/*@Nonnull*/ QPointF loc) {
    return findLayoutTracksHitPoint(loc, false, nullptr);
}

/*private*/ bool LayoutEditor::findLayoutTracksHitPoint(/*@Nonnull*/ QPointF loc,
        bool requireUnconnected, /*@Nullable*/ LayoutTrack* avoid) {
    bool result = false; // assume failure (pessimist!)

    foundObject = nullptr;
    foundPointType = LayoutTrack::NONE;
#if 1
    Optional<LayoutTrack*> opt;// = layoutTrackList.stream().filter(layoutTrack ->
    for(LayoutTrack* layoutTrack : *layoutTrackList)
    {
        if ((layoutTrack != avoid) && (layoutTrack != selectedObject)) {
            foundPointType = layoutTrack->findHitPointType(loc, false, requireUnconnected);

//        return (LayoutTrack::NONE != foundPointType);
        if(LayoutTrack::NONE != foundPointType)
        {
         foundObject = layoutTrack;
         break;
        }
      }
    }//).findFirst();
    //opt.findFirst();

    LayoutTrack* layoutTrack = foundObject;
//    if (opt.isPresent()) {
//        layoutTrack = opt.get();
//    }
    if (layoutTrack != nullptr) {
        foundObject = layoutTrack;
        foundLocation = layoutTrack->getCoordsForConnectionType(foundPointType);
        foundNeedsConnect = layoutTrack->isDisconnected(foundPointType);
        result = true;
    }
#endif
    return result;
}

/*private*/ TrackSegment* LayoutEditor::checkTrackSegmentPopUps(/*@Nonnull*/ QPointF loc) {
    TrackSegment* result = nullptr;

    //NOTE: Rather than calculate all the hit rectangles for all
    // the points below and test if this location is in any of those
    // rectangles just create a hit rectangle for the location and
    // see if any of the points below are in it instead...
    QRectF r = trackControlCircleRectAt(loc);

    //check Track Segments, if any
    for (TrackSegment* ts : getTrackSegments()) {
        if (r.contains(ts->getCentreSeg())) {
            result = ts;
            break;
        }
    }
    return result;
}

/*private*/ PositionableLabel* LayoutEditor::checkBackgroundPopUps(/*@Nonnull*/ QPointF loc) {
    PositionableLabel* result = nullptr;
    //check background images, if any
    for (int i = backgroundImage->size() - 1; i >= 0; i--) {
        PositionableLabel* b = backgroundImage->at(i);
        QRectF r = b->getBounds();
        if (r.contains(loc)) {
            result = b;
            break;
        }
    }
    return result;
}

/*private*/ SensorIcon* LayoutEditor::checkSensorIconPopUps(/*@Nonnull*/ QPointF loc) {
    SensorIcon* result = nullptr;
    //check sensor images, if any
    for (int i = sensorImage->size() - 1; i >= 0; i--) {
        SensorIcon* s = sensorImage->at(i);
        QRectF r = s->getBounds();
        if (r.contains(loc)) {
            result = s;
        }
    }
    return result;
}

/*private*/ SignalHeadIcon* LayoutEditor::checkSignalHeadIconPopUps(/*@Nonnull*/ QPointF loc) {
    SignalHeadIcon* result = nullptr;
    //check signal head images, if any
    for (int i = signalHeadImage->size() - 1; i >= 0; i--) {
        SignalHeadIcon* s = signalHeadImage->at(i);
        QRectF r = s->getBounds();
        if (r.contains(loc)) {
            result = s;
            break;
        }
    }
    return result;
}

/*private*/ SignalMastIcon* LayoutEditor::checkSignalMastIconPopUps(/*@Nonnull*/ QPointF loc) {
    SignalMastIcon* result = nullptr;
    //check signal head images, if any
    for (int i = signalMastList->size() - 1; i >= 0; i--) {
        SignalMastIcon* s = signalMastList->at(i);
        QRectF r = s->getBounds();
        if (r.contains(loc)) {
            result = s;
            break;
        }
    }
    return result;
}

/*private*/ PositionableLabel* LayoutEditor::checkLabelImagePopUps(/*@Nonnull*/ QPointF loc) {
    PositionableLabel* result = nullptr;
    int level = 0;

    for (int i = labelImage->size() - 1; i >= 0; i--) {
        PositionableLabel* s = labelImage->at(i);
        double x = s->getX();
        double y = s->getY();
        double w = 10.0;
        double h = 5.0;

        if (s->isIcon() || s->isRotated() || s->getPopupUtility()->getOrientation() != PositionablePopupUtil::HORIZONTAL) {
            w = s->maxWidth();
            h = s->maxHeight();
        } else if (s->isText()) {
            h = s->getFont().pointSize();
            w = (h * 2 * (s->getText().length())) / 3;
        }

        QRectF r = QRectF(x, y, w, h);
        if (r.contains(loc)) {
            if (s->getDisplayLevel() >= level) {
                //Check to make sure that we are returning the highest level label.
                result = s;
                level = s->getDisplayLevel();
            }
        }
    }
    return result;
}

/*private*/ AnalogClock2Display* LayoutEditor::checkClockPopUps(/*@Nonnull*/ QPointF loc) {
    AnalogClock2Display* result = nullptr;
    //check clocks, if any
    for (int i = clocks->size() - 1; i >= 0; i--) {
        AnalogClock2Display* s = clocks->at(i);
        QRectF r = s->getBounds();
        if (r.contains(loc)) {
            result = s;
            break;
        }
    }
    return result;
}

/*private*/ MultiSensorIcon* LayoutEditor::checkMultiSensorPopUps(/*@Nonnull */QPointF loc) {
    MultiSensorIcon* result = nullptr;
    //check multi sensor icons, if any
    for (int i = multiSensors->size() - 1; i >= 0; i--) {
        MultiSensorIcon* s = multiSensors->at(i);
        QRectF r = s->getBounds();
        if (r.contains(loc)) {
            result = s;
            break;
        }
    }
    return result;
}

/*private*/ LocoIcon* LayoutEditor::checkMarkerPopUps(/*@Nonnull*/ QPointF loc) {
    LocoIcon* result = nullptr;
    //check marker icons, if any
    for (int i = markerImage->size() - 1; i >= 0; i--) {
        LocoIcon* l = markerImage->at(i);
        QRectF r = l->getBounds();
        if (r.contains(loc)) {
            //mouse was pressed in marker icon
            result = l;
            break;
        }
    }
    return result;
}

/**
 * get the coordinates for the connection type of the specified object
 *
 * @param layoutTrack    the object (Layout track subclass)
 * @param connectionType the type of connection
 * @return the coordinates for the connection type of the specified object
 */
//@Nonnull
/*public*/ /*static*/ QPointF LayoutEditor::getCoords(/*@Nonnull*/ LayoutTrack* layoutTrack, int connectionType) {
    QPointF result = MathUtil::zeroPoint2D;
    if (layoutTrack != nullptr) {
        result = layoutTrack->getCoordsForConnectionType(connectionType);
    } else {
        log->error(tr("Null connection point of type %1").arg(connectionType));
    }
    return result;
}


// mouse pressed and released.
/*public*/ void LayoutEditor::mouseClicked(QGraphicsSceneMouseEvent* event)
{
 Qt::MouseButtons buttons = event->buttons();
 Q_UNUSED(buttons);
 if ( /*(!event.isMetaDown()) &&*/ (!((event->buttons()&Qt::RightButton)==Qt::RightButton )) && !(event->modifiers()&Qt::AltModifier) &&
                    /*(!awaitingIconChange) && */(!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
 {
  calcLocation(event->scenePos(), 0, 0);
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  { // don't think this cast is needed as long as doMouseClicked is public
//   if(qobject_cast<SensorIcon*>(selections.at(0))!= nullptr)
//    ((SensorIcon*)selections.at(0))->doMouseClicked(event);
//   else
   //((PositionableLabel*)selections.at(0))->doMouseClicked(event);
   selections.at(0)->doMouseClicked(event);
  }
 }
 else if ( (event->buttons()&Qt::RightButton/*==Qt::RightButton*/ ) /*&& whenReleased != event.getWhen()*/)
 {
  calcLocation(event->scenePos(), 0, 0);
  if (isEditable())
  {
   selectedObject = nullptr;
   selectedPointType = NONE;
   showEditPopUps(event);
  }
  else
  {
   LocoIcon* lo = checkMarkers(dLoc);
   if (lo!=nullptr) showPopUp((Positionable*)lo, event);
  }
 }
 if ((event->modifiers()&Qt::ControlModifier) /*&&*/ /*!event.isPopupTrigger()*/)
 {
  if (findLayoutTracksHitPoint(dLoc))
  {
   // show popup menu
   switch (foundPointType)
   {
    case POS_POINT:
        amendSelectionGroup((PositionablePoint*)foundObject);
        break;
    case TURNOUT_CENTER:
        amendSelectionGroup((LayoutTurnout*)foundObject);
        break;
    case LEVEL_XING_CENTER:
        amendSelectionGroup((LevelXing*)foundObject);
        break;
    case SLIP_CENTER:
        amendSelectionGroup((LayoutSlip*)foundObject);
        break;
    case TURNTABLE_CENTER:
        amendSelectionGroup((LayoutTurntable*)foundObject);
        break;
    default: break;
   }
  }
  else
  {

   PositionableLabel* s = checkSensorIcons(dLoc);
   if (s!=nullptr)
   {
    amendSelectionGroup((Positionable*)s);
   }

   else
   {
    PositionableLabel* sh = checkSignalHeadIcons(dLoc);
    if (sh!=nullptr)
    {
     amendSelectionGroup((Positionable*)sh);
    }
    else
    {
     PositionableLabel* ms = checkMultiSensors(dLoc);
     if (ms!=nullptr)
     {
      amendSelectionGroup((Positionable*)ms);
     }
     else
     {
      PositionableLabel* lb = checkLabelImages(dLoc);
      if (lb!=nullptr)
      {
       amendSelectionGroup((Positionable*)lb);
      }
//      else
//      {
//       PositionableLabel* b = checkBackgrounds(dLoc);
//       if (b!=nullptr)
//       {
//        amendSelectionGroup(b);
//       }
       else
       {
        PositionableLabel* sm = checkSignalMastIcons(dLoc);
        if (sm!=nullptr)
        {
         amendSelectionGroup((Positionable*)sm);
        }
       }
//      }
     }
    }
   }
  }
 }
 else if(selectionWidth==0 || selectionHeight==0)
 {
  clearSelectionGroups();
 }
 //thisPanel.setFocusable(true);
 //thisPanel.requestFocusInWindow();
 return;
}

/*private*/ void LayoutEditor::checkPointOfPositionable(PositionablePoint* p)
{
 TrackSegment* t = p->getConnect1();

 if (t == nullptr) {
     t = p->getConnect2();
 }

 //Nothing connected to this bit of track so ignore
 if (t == nullptr) {
     return;
 }
 beginObject = p;
 beginPointType = LayoutTrack::POS_POINT;
 QPointF loc = p->getCoordsCenter();

 if (findLayoutTracksHitPoint(loc, true, p))
 {
  switch (foundPointType)
  {
   case LayoutTrack::POS_POINT:
   {
    PositionablePoint* p2 = (PositionablePoint*) foundObject;

    if ((p2->getType() == PositionablePoint::ANCHOR) && p2->setTrackConnection(t))
    {
     if (t->getConnect1() == p)
     {
        t->setNewConnect1(p2, LayoutTrack::POS_POINT);
     } else {
        t->setNewConnect2(p2, LayoutTrack::POS_POINT);
     }
     p->removeTrackConnection(t);

     if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr))
     {
        removePositionablePoint(p);
     }
    }
    break;
   }

   case LayoutTrack::TURNOUT_A:
   case LayoutTrack::TURNOUT_B:
   case LayoutTrack::TURNOUT_C:
   case LayoutTrack::TURNOUT_D:
   {
    LayoutTurnout* lt = (LayoutTurnout*) foundObject;
    try
    {
     if (lt->getConnection(foundPointType) == nullptr)
     {
      lt->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(lt, foundPointType);
      } else {
          t->setNewConnect2(lt, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr))
      {
          removePositionablePoint(p);
      }
     }
    } catch (JmriException e) {
       log->debug("Unable to set location");
    }
    break;
   }

   case LayoutTrack::LEVEL_XING_A:
   case LayoutTrack::LEVEL_XING_B:
   case LayoutTrack::LEVEL_XING_C:
   case LayoutTrack::LEVEL_XING_D:
   {
    LevelXing* lx = (LevelXing*) foundObject;
    try
    {
     if (lx->getConnection(foundPointType) == nullptr)
     {
      lx->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(lx, foundPointType);
      } else {
          t->setNewConnect2(lx, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr)) {
          removePositionablePoint(p);
      }
     }
    }
    catch (JmriException e) {
       log->debug("Unable to set location");
    }
    break;
   }

   case LayoutTrack::SLIP_A:
   case LayoutTrack::SLIP_B:
   case LayoutTrack::SLIP_C:
   case LayoutTrack::SLIP_D:
   {
    LayoutSlip* ls = (LayoutSlip*) foundObject;
    try
    {
     if (ls->getConnection(foundPointType) == nullptr)
     {
      ls->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(ls, foundPointType);
      } else {
          t->setNewConnect2(ls, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr)) {
          removePositionablePoint(p);
      }
     }
    } catch (JmriException e) {
       log->debug("Unable to set location");
   }
   break;
  }

  default:

   if (foundPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET)
   {
    LayoutTurntable* tt = (LayoutTurntable*) foundObject;
    int ray = foundPointType - LayoutTrack::TURNTABLE_RAY_OFFSET;

    if (tt->getRayConnectIndexed(ray) == nullptr)
    {
     tt->setRayConnect(t, ray);

     if (t->getConnect1() == p) {
         t->setNewConnect1(tt, foundPointType);
     } else {
         t->setNewConnect2(tt, foundPointType);
     }
     p->removeTrackConnection(t);

     if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr)) {
         removePositionablePoint(p);
     }
    }
   }
   else
   {
    log->debug("No valid point, so will quit");
    return;
   }
  }   //switch
  update();

  if (t->getLayoutBlock() != nullptr)
  {
   auxTools->setBlockConnectivityChanged();
  }
 }
 beginObject = nullptr;
 foundObject = nullptr;
}   //checkPointOfPositionable

#if 0
/*private*/ void LayoutEditor::checkPointsOfTurnout(LayoutTurnout* lt)
{
 beginObject = lt;

 if (lt->getConnectA() == nullptr) {
     beginPointType = LayoutTrack::TURNOUT_A;
     dLoc = lt->getCoordsA();
     checkPointsOfTurnoutSub(lt->getCoordsA());
 }

 if (lt->getConnectB() == nullptr) {
     beginPointType = LayoutTrack::TURNOUT_B;
     dLoc = lt->getCoordsB();
     checkPointsOfTurnoutSub(lt->getCoordsB());
 }

 if (lt->getConnectC() == nullptr) {
     beginPointType = LayoutTrack::TURNOUT_C;
     dLoc = lt->getCoordsC();
     checkPointsOfTurnoutSub(lt->getCoordsC());
 }

 if ((lt->getConnectD() == nullptr) && ((lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER) ||
                                    (lt->getTurnoutType() == LayoutTurnout::LH_XOVER) ||
                                    (lt->getTurnoutType() == LayoutTurnout::RH_XOVER))) {
     beginPointType = LayoutTrack::TURNOUT_D;
     dLoc = lt->getCoordsD();
     checkPointsOfTurnoutSub(lt->getCoordsD());
 }
 beginObject = nullptr;
 foundObject = nullptr;
}   //checkPointsOfTurnout

/*private*/ void LayoutEditor::checkPointsOfTurnoutSub(QPointF dLoc)
{
 if (checkSelect(dLoc, true))
 {
  switch (foundPointType)
  {
   case LayoutTrack::POS_POINT:
   {
    PositionablePoint* p2 = (PositionablePoint*) foundObject;

    if (((p2->getConnect1() == nullptr) && (p2->getConnect2() != nullptr)) ||
        ((p2->getConnect1() != nullptr) && (p2->getConnect2() == nullptr)))
    {
     TrackSegment* t = p2->getConnect1();

     if (t == nullptr) {
         t = p2->getConnect2();
     }

     if (t == nullptr) {
         return;
     }
     LayoutTurnout* lt = (LayoutTurnout*) beginObject;
     try
     {
      if (lt->getConnection(beginPointType) == nullptr)
      {
       lt->setConnection(beginPointType, t, LayoutTrack::TRACK);
       p2->removeTrackConnection(t);

       if (t->getConnect1() == p2) {
           t->setNewConnect1(lt, beginPointType);
       } else {
           t->setNewConnect2(lt, beginPointType);
       }
       removePositionablePoint(p2);
      }

      if (t->getLayoutBlock() != nullptr) {
          auxTools->setBlockConnectivityChanged();
      }
     } catch (JmriException e) {
         log->debug("Unable to set location");
     }
    }
    break;
   }

   case LayoutTrack::TURNOUT_A:
   case LayoutTrack::TURNOUT_B:
   case LayoutTrack::TURNOUT_C:
   case LayoutTrack::TURNOUT_D: {
       LayoutTurnout* ft = (LayoutTurnout*) foundObject;
       addTrackSegment();

       if ((ft->getTurnoutType() == LayoutTurnout::RH_TURNOUT) || (ft->getTurnoutType() == LayoutTurnout::LH_TURNOUT)) {
           rotateTurnout(ft);
       }
       break;
   }

   default: {
       log->warn(tr("Unexpected foundPointType %1  in checkPointsOfTurnoutSub").arg(foundPointType));
       break;
   }
  }   //switch
 }
}   //checkPointsOfTurnoutSub
#endif
// We just dropped a turnout... see if it will connect to anything
/*private*/ void LayoutEditor::hitPointCheckLayoutTurnouts(/*@Nonnull*/ LayoutTurnout* lt) {
    beginObject = lt;

    if (lt->getConnectA() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginPointType = LayoutTrack::SLIP_A;
        } else {
            beginPointType = LayoutTrack::TURNOUT_A;
        }
        dLoc = lt->getCoordsA();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }

    if (lt->getConnectB() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginPointType = LayoutTrack::SLIP_B;
        } else {
            beginPointType = LayoutTrack::TURNOUT_B;
        }
        dLoc = lt->getCoordsB();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }

    if (lt->getConnectC() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginPointType = LayoutTrack::SLIP_C;
        } else {
            beginPointType = LayoutTrack::TURNOUT_C;
        }
        dLoc = lt->getCoordsC();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }

    if ((lt->getConnectD() == nullptr) && ((lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
            || (lt->getTurnoutType() == LayoutTurnout::LH_XOVER)
            || (lt->getTurnoutType() == LayoutTurnout::RH_XOVER)
            || (lt->getTurnoutType() == LayoutTurnout::SINGLE_SLIP)
            || (lt->getTurnoutType() == LayoutTurnout::DOUBLE_SLIP))) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginPointType = LayoutTrack::SLIP_D;
        } else {
            beginPointType = LayoutTrack::TURNOUT_D;
        }
        dLoc = lt->getCoordsD();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }
    beginObject = nullptr;
    foundObject = nullptr;
}

/*private*/ void LayoutEditor::hitPointCheckLayoutTurnoutSubs(/*@Nonnull*/ QPointF dLoc) {
    if (findLayoutTracksHitPoint(dLoc, true)) {
        switch (foundPointType) {
            case LayoutTrack::POS_POINT: {
                PositionablePoint* p2 = (PositionablePoint*) foundObject;

                if (((p2->getConnect1() == nullptr) && (p2->getConnect2() != nullptr))
                        || ((p2->getConnect1() != nullptr) && (p2->getConnect2() == nullptr))) {
                    TrackSegment* t = p2->getConnect1();

                    if (t == nullptr) {
                        t = p2->getConnect2();
                    }

                    if (t == nullptr) {
                        return;
                    }
                    LayoutTurnout* lt = (LayoutTurnout*) beginObject;
                    try {
                        if (lt->getConnection(beginPointType) == nullptr) {
                            lt->setConnection(beginPointType, t, LayoutTrack::TRACK);
                            p2->removeTrackConnection(t);

                            if (t->getConnect1() == p2) {
                                t->setNewConnect1(lt, beginPointType);
                            } else {
                                t->setNewConnect2(lt, beginPointType);
                            }
                            removePositionablePoint(p2);
                        }

                        if (t->getLayoutBlock() != nullptr) {
                            getLEAuxTools()->setBlockConnectivityChanged();
                        }
                    } catch (JmriException e) {
                        log->debug("Unable to set location");
                    }
                }
                break;
            }

            case LayoutTrack::TURNOUT_A:
            case LayoutTrack::TURNOUT_B:
            case LayoutTrack::TURNOUT_C:
            case LayoutTrack::TURNOUT_D:
            case LayoutTrack::SLIP_A:
            case LayoutTrack::SLIP_B:
            case LayoutTrack::SLIP_C:
            case LayoutTrack::SLIP_D: {
                LayoutTurnout* ft = (LayoutTurnout*) foundObject;
                addTrackSegment();

                if ((ft->getTurnoutType() == LayoutTurnout::RH_TURNOUT) || (ft->getTurnoutType() == LayoutTurnout::LH_TURNOUT)) {
                    rotateTurnout(ft);
                }

                // Assign a block to the new zero length track segment.
                ft->setTrackSegmentBlock(foundPointType, true);
                break;
            }

            default: {
                log->warn(tr("Unexpected foundPointType %1 in hitPointCheckLayoutTurnoutSubs").arg(foundPointType));
                break;
            }
        }
    }
}

/*private*/ void LayoutEditor::rotateTurnout(LayoutTurnout* t) {
    LayoutTurnout* be = (LayoutTurnout*) beginObject;

    if (((beginPointType == LayoutTrack::TURNOUT_A) && ((be->getConnectB() != nullptr) || (be->getConnectC() != nullptr))) ||
        ((beginPointType == LayoutTrack::TURNOUT_B) && ((be->getConnectA() != nullptr) || (be->getConnectC() != nullptr))) ||
        ((beginPointType == LayoutTrack::TURNOUT_C) && ((be->getConnectB() != nullptr) || (be->getConnectA() != nullptr)))) {
        return;
    }

    if ((be->getTurnoutType() != LayoutTurnout::RH_TURNOUT) && (be->getTurnoutType() != LayoutTurnout::LH_TURNOUT)) {
        return;
    }

    double x2;
    double y2;

    QPointF c;
    QPointF diverg;

    if ((foundPointType == LayoutTrack::TURNOUT_C) && (beginPointType == LayoutTrack::TURNOUT_C)) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();
        x2 = be->getCoordsA().x() - be->getCoordsB().x();
        y2 = be->getCoordsA().y() - be->getCoordsB().y();
    } else if ((foundPointType == LayoutTrack::TURNOUT_C) &&
               ((beginPointType == LayoutTrack::TURNOUT_A) || (beginPointType == LayoutTrack::TURNOUT_B))) {
        c = t->getCoordsCenter();
        diverg = t->getCoordsC();

        if (beginPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsB().x() - be->getCoordsA().x();
            y2 = be->getCoordsB().y() - be->getCoordsA().y();
        } else {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        }
    } else if (foundPointType == LayoutTrack::TURNOUT_B) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();

        if (beginPointType == LayoutTrack::TURNOUT_B) {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        } else if (beginPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsB().x() - be->getCoordsA().x();
            y2 = be->getCoordsB().y() - be->getCoordsA().y();
        } else {    //(beginPointType==TURNOUT_C){
            x2 = be->getCoordsCenter().x() - be->getCoordsC().x();
            y2 = be->getCoordsCenter().y() - be->getCoordsC().y();
        }
    } else if (foundPointType == LayoutTrack::TURNOUT_A) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();

        if (beginPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        } else if (beginPointType == LayoutTrack::TURNOUT_B) {
            x2 = be->getCoordsB().x() - be->getCoordsA().x();
            y2 = be->getCoordsB().y() - be->getCoordsA().y();
        } else {    //(beginPointType==TURNOUT_C){
            x2 = be->getCoordsC().x() - be->getCoordsCenter().x();
            y2 = be->getCoordsC().y() - be->getCoordsCenter().y();
        }
    } else {
        return;
    }
    double x = diverg.x() - c.x();
    double y = diverg.y() - c.y();
    double radius = toDegrees(qAtan2(y, x));
    double eRadius = toDegrees(qAtan2(y2, x2));
    be->rotateCoords(radius - eRadius);

    QPointF conCord = be->getCoordsA();
    QPointF tCord = t->getCoordsC();

    if (foundPointType == LayoutTrack::TURNOUT_B) {
        tCord = t->getCoordsB();
    }

    if (foundPointType == LayoutTrack::TURNOUT_A) {
        tCord = t->getCoordsA();
    }

    if (beginPointType == LayoutTrack::TURNOUT_B) {
        conCord = be->getCoordsB();
    } else if (beginPointType == LayoutTrack::TURNOUT_C) {
        conCord = be->getCoordsC();
    } else if (beginPointType == LayoutTrack::TURNOUT_A) {
        conCord = be->getCoordsA();
    }
    x = conCord.x() - tCord.x();
    y = conCord.y() - tCord.y();
    QPointF offset = QPointF(be->getCoordsCenter().x() - x, be->getCoordsCenter().y() - y);
    be->setCoordsCenter(offset);
}   //rotateTurnout

/*public*/ void LayoutEditor::mouseReleased(QGraphicsSceneMouseEvent* event)
{
 bool isAltDown = event->modifiers()&Qt::AltModifier;
 bool isMetaDown = event->modifiers()&Qt::MetaModifier;
 bool bShift =  event->modifiers()&Qt::ShiftModifier;

 //super.setToolTip(nullptr);

 // initialize mouse position
 calcLocation(event->scenePos(), 0, 0);

 // if alt modifier is down invert the snap to grid behaviour
 snapToGridInvert = isAltDown;

 if (isEditable())
 {
  ui->xLabel->setText(QString("%1").arg(xLoc));
  ui->yLabel->setText(QString("%1").arg(yLoc));

  // !ALT and SHIFT_DOWN
  Qt::KeyboardModifiers k = event->modifiers();
  Q_UNUSED(k)
  if(delayedPopupTrigger && bShift)
   delayedPopupTrigger = false;

  // released the mouse with shift down... see what we're adding
  if (/*(!event.isPopupTrigger()) && (!event.isMetaDown()) &&*/ !delayedPopupTrigger && !isMetaDown && (!isAltDown) && bShift)
  {
   currentPoint = QPointF(xLoc, yLoc);
   if (snapToGridOnAdd)
   {
    xLoc = ((xLoc+4)/10)*10;
    yLoc = ((yLoc+4)/10)*10;
    //currentPoint.setLocation(xLoc,yLoc);
    currentPoint.setX(xLoc);
    currentPoint.setY(yLoc);
   }
   if (ui->turnoutRHButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_TURNOUT);
   }
   else if (ui->turnoutLHButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_TURNOUT);
   }
   else if (ui->turnoutWYEButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::WYE_TURNOUT);
   }
   else if (ui->doubleXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::DOUBLE_XOVER);
   }
   else if (ui->rhXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_XOVER);
   }
   else if (ui->lhXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_XOVER);
   }
   else if (ui->levelXingButton->isChecked())
   {
    addLevelXing();
   }
   else if (ui->layoutSingleSlipButton->isChecked())
   {
    addLayoutSlip(LayoutSlip::SINGLE_SLIP);
   }
   else if (ui->layoutDoubleSlipButton->isChecked())
   {
    addLayoutSlip(LayoutSlip::DOUBLE_SLIP);
   }
   else if (ui->chkEndBumper->isChecked())
   {
    addEndBumper();
   }
   else if (ui->chkAnchorPoint->isChecked())
   {
    addAnchor();
   }
   else if (ui->trackButton->isChecked())
   {
    if ( (beginObject!=nullptr) && (foundObject!=nullptr) &&
                (beginObject!=foundObject) )
    {
     if(trackInProgress != nullptr && trackInProgress->scene()!=0)
     {
      editScene->removeItem(trackInProgress);
      trackInProgress = nullptr;
     }
     addTrackSegment();
     setCursor(Qt::ArrowCursor);
    }
    beginObject = nullptr;
    foundObject = nullptr;
    }
   else if (ui->multiSensorButton->isChecked())
   {
    startMultiSensor();
   }
    else if (ui->sensorButton->isChecked())
    {
        addSensor();
    }
    else if (ui->signalButton->isChecked()) {
        addSignalHead();
    }
    else if (ui->textLabelButton->isChecked()) {
        addLabel();
    }
    else if (ui->memoryButton->isChecked()) {
        addMemory();
    }
   else if (ui->iconLabelButton->isChecked()) {
        addIcon();
    }
#if 1
    else if (ui->signalMastButton->isChecked()) {
        addSignalMast();
    }
#endif
   else
   {
    log->warn("No item selected in panel edit mode");
   }
   //resizePanelBounds(false);
   selectedObject = nullptr;
   //repaint();
   redrawPanel();
  }
  else if ( (/*event->isPopupTrigger() ||*/ delayedPopupTrigger)  && !isDragging)
  {
   selectedObject = nullptr;
   selectedPointType = LayoutTrack::NONE;
   //whenReleased = event.getWhen();
   showEditPopUps(event);
   delayedPopupTrigger = false;
  }
   // check if controlling turnouts
  else if ( ( selectedObject!=nullptr) && (selectedPointType==TURNOUT_CENTER)
             && allControlling() /*&& (!(event->modifiers()&Qt::ControlModifier))*/ /*&& (!(event->modifiers()&Qt::AltModifier)) *//*&& (!event.isPopupTrigger())*/
             && (!(event->modifiers()&Qt::ShiftModifier))
             && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
  else if ( ( selectedObject!=nullptr) && ((selectedPointType == LayoutTrack::SLIP_CENTER) ||
                                        (selectedPointType == LayoutTrack::SLIP_LEFT) ||
                                        (selectedPointType == LayoutTrack::SLIP_RIGHT))/* &&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleTurnout();
  }
  else if ( ( selectedObject!=nullptr) && (selectedPointType>=TURNTABLE_RAY_OFFSET) /*&&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurntable* t =  (LayoutTurntable*)selectedObject;
   t->setPosition(selectedPointType-TURNTABLE_RAY_OFFSET);
  }
  else if ((selectedObject != nullptr) && (selectedPointType == LayoutTrack::TURNOUT_CENTER) /*&&
                         allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
                         (!event.isShiftDown()) && (!event.isControlDown()) && isDragging)*/
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
        //controlling layout, in edit mode
        hitPointCheckLayoutTurnouts((LayoutTurnout*) selectedObject);
  }
  else if ((selectedObject != nullptr) && (selectedPointType == LayoutTrack::POS_POINT) /*&&
               allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
               (!event.isShiftDown()) && (!event.isControlDown()) && isDragging) */
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
    PositionablePoint* p = (PositionablePoint*) selectedObject;

    if ((p->getConnect1() == nullptr) || (p->getConnect2() == nullptr)) {
        checkPointOfPositionable(p);
    }
   }

   if ( (ui->trackButton->isChecked()) && (beginObject!=nullptr) && (foundObject!=nullptr) )
   {
    // user let up shift key before releasing the mouse when creating a track segment
    setCursor(Qt::ArrowCursor);
    beginObject = nullptr;
    foundObject = nullptr;
    //repaint();
    paintTargetPanel(editScene);
   }

   createSelectionGroups();
  }
  // check if controlling turnouts out of edit mode
  else if ( ( selectedObject!=nullptr) && (selectedPointType==TURNOUT_CENTER) /*&&
            allControlling() && (!event.isMetaDown())*/ && (!(event->modifiers()&Qt::AltModifier)) /*&& (!event.isPopupTrigger()) */&&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   // controlling layout, not in edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
    // check if controlling turnouts out of edit mode
    else if ( ( selectedObject!=nullptr) && ((selectedPointType == LayoutTrack::SLIP_CENTER) ||
                                          (selectedPointType == LayoutTrack::SLIP_LEFT) ||
                                          (selectedPointType == LayoutTrack::SLIP_RIGHT)) /*&&
            allControlling() && (!event.isMetaDown())*/ && (!(event->modifiers()&Qt::AltModifier))/* && (!event.isPopupTrigger())*/ &&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   // controlling layout, not in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleTurnout();
  }
#if 1
  else if ( ( selectedObject!=nullptr) && (selectedPointType>=TURNTABLE_RAY_OFFSET)/* &&
            allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier)) && (!event.isPopupTrigger())*/ &&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   LayoutTurntable*  t =  (LayoutTurntable*)selectedObject;
   t->setPosition(selectedPointType-TURNTABLE_RAY_OFFSET);
  }
#endif
   // check if requesting marker popup out of edit mode
   else if ( (/*event.isPopupTrigger() ||*/ delayedPopupTrigger) && (!isDragging) )
   {
    LocoIcon* lo = checkMarkers(dLoc);
    if (lo!=nullptr) showPopUp((Positionable*)lo, event);
    else
    {
     if (findLayoutTracksHitPoint(dLoc))
     {
      // show popup menu
      switch (foundPointType)
      {
       case TURNOUT_CENTER:
        ((LayoutTurnout*)foundObject)->showPopup(event);
        break;
       case LEVEL_XING_CENTER:
        ((LevelXing*)foundObject)->showPopup(event);
        break;
       case SLIP_CENTER:
        ((LayoutSlip*)foundObject)->showPopup(event);
        break;
       default: break;
      }
     }

     AnalogClock2Display* c = checkClocks(dLoc);
     if (c!=nullptr)
     {
       showPopUp((Positionable*)c, event);
     }
     else
     {
      SignalMastIcon* sm = checkSignalMastIcons(dLoc);
      if (sm!=nullptr)
      {
       showPopUp((Positionable*)sm, event);
      }
      else
      {
       PositionableLabel* im = checkLabelImages(dLoc);
       if(im!=nullptr)
       {
        showPopUp((Positionable*)im, event);
       }
//       }
//      }
    }
   }

   if (/*!event.isPopupTrigger() && */ !isDragging)
   {
    QList <Positionable*> selections = getSelectedItems(event);
    if (selections.size() > 0)
    {
       ((PositionableLabel*)selections.at(0))->doMouseReleased(event);
//            whenReleased = event->getWhen();
    }
   }
   if (selectedObject!=nullptr)
   {
    // An object was selected, deselect it
    prevSelectedObject = selectedObject;
    selectedObject = nullptr;
   }
   isDragging = false;
   delayedPopupTrigger = false;
//    thisPanel.requestFocusInWindow();
   return;
  }
 }
}

/*private*/ void LayoutEditor::showEditPopUps(/*@Nonnull */QGraphicsSceneMouseEvent* event)
{
  if (findLayoutTracksHitPoint(dLoc))
  {
   if ((foundPointType >= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN)
           && (foundPointType <= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MAX)) {
       ((TrackSegment*) foundObject)->showBezierPopUp(event, foundPointType);
   }
   else if (foundPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET) {
       LayoutTurntable* t = (LayoutTurntable*) foundObject;
       if (t->isTurnoutControlled()) {
           ((LayoutTurntable*) foundObject)->showRayPopUp(event, foundPointType - LayoutTrack::TURNTABLE_RAY_OFFSET);
       }
   }
   else if (LayoutTrack::isPopupHitType(foundPointType)) {
       foundObject->showPopup(event);
   }
   else if ((foundPointType >= LayoutTrack::TURNOUT_A)
           && (foundPointType <= LayoutTrack::TURNOUT_D)) {
       // don't curently have edit popup for these
   }
   else {
       log->warn("Unknown foundPointType:" + QString::number(foundPointType));
   }
  }
  else
  {
      do {
          TrackSegment* ts = checkTrackSegmentPopUps(dLoc);
          if (ts != nullptr) {
              ts->showPopup(event);
              break;
          }

          SensorIcon* s = checkSensorIconPopUps(dLoc);
          if (s != nullptr) {
              showPopUp(s, event);
              break;
          }

          LocoIcon* lo = checkMarkerPopUps(dLoc);
          if (lo != nullptr) {
              showPopUp(lo, event);
              break;
          }

          SignalHeadIcon* sh = checkSignalHeadIconPopUps(dLoc);
          if (sh != nullptr) {
              showPopUp(sh, event);
              break;
          }

          AnalogClock2Display* c = checkClockPopUps(dLoc);
          if (c != nullptr) {
              showPopUp(c, event);
              break;
          }

          MultiSensorIcon* ms = checkMultiSensorPopUps(dLoc);
          if (ms != nullptr) {
              showPopUp(ms, event);
              break;
          }

          PositionableLabel* lb = checkLabelImagePopUps(dLoc);
          if (lb != nullptr) {
              showPopUp(lb, event);
              break;
          }

          PositionableLabel* b = checkBackgroundPopUps(dLoc);
          if (b != nullptr) {
              showPopUp(b, event);
              break;
          }

          SignalMastIcon* sm = checkSignalMastIconPopUps(dLoc);
          if (sm != nullptr) {
              showPopUp(sm, event);
              break;
          }
      } while (false);
  }
}

/**
* Select the menu items to display for the Positionable's popup
*/
//@Override
/*protected*/ void LayoutEditor::showPopUp(/*@Nonnull*/ Positionable* p, /*@Nonnull */QGraphicsSceneMouseEvent* event) {
  //if (!((JComponent*) p)->isVisible()) {
//  if(p->self()->item && !p->item.isVisible())
//      return; //component must be showing on the screen to determine its location
//  }
  QMenu* popup = new QMenu();
#if 1

  if (p->isEditable()) {
      QAction* jmi = nullptr;
      if (showAlignPopup()) {
          setShowAlignmentMenu(popup);
//          popup.add(new AbstractAction(Bundle.getMessage("ButtonDelete")) {
//              @Override
//              public void actionPerformed(ActionEvent event) {
//                  deleteSelectedItems();
//              }
//          });
          AbstractAction* act = new AbstractAction(tr("Delete"), this);
          connect(act, SIGNAL(triggered(bool)), this, SLOT(deleteSelectedItems()));
      }
      else
      {
          if (p->doViemMenu())
          {
              QString objectType = p->self()->metaObject()->className();
              objectType = objectType.mid(objectType.lastIndexOf('.') + 1);
              jmi = popup->addSection(objectType);
              jmi->setEnabled(false);

              jmi = popup->addSection(p->getNameString());
              jmi->setEnabled(false);

              if (p->isPositionable()) {
                  setShowCoordinatesMenu(p, popup);
              }
              setDisplayLevelMenu(p, popup);
              setPositionableMenu(p, popup);
          }

          bool popupSet = false;
          popupSet |= p->setRotateOrthogonalMenu(popup);
          popupSet |= p->setRotateMenu(popup);
          if (popupSet) {
              popup->addSeparator();
              popupSet = false;
          }
          popupSet = p->setEditIconMenu(popup);
          popupSet = p->setTextEditMenu(popup);

          PositionablePopupUtil* util = p->getPopupUtility();

          if (util != nullptr) {
              util->setFixedTextMenu(popup);
              util->setTextMarginMenu(popup);
              util->setTextBorderMenu(popup);
              util->setTextFontMenu(popup);
              util->setBackgroundMenu(popup);
              util->setTextJustificationMenu(popup);
              util->setTextOrientationMenu(popup);
              popup->addSeparator();
              util->propertyUtil(popup);
              util->setAdditionalEditPopUpMenu(popup);
              popupSet = true;
          }

          if (popupSet) {
              popup->addSeparator();
              popupSet = false;
          }
          p->setDisableControlMenu(popup);
          setShowAlignmentMenu(popup);

          //for Positionables with unique settings
          p->showPopUp(popup);
          setShowToolTipMenu(p, popup);

          setRemoveMenu(p, popup);

          if (p->doViemMenu()) {
              setHiddenMenu(p, popup);
          }
      }
  } else {
      p->showPopUp(popup);
      PositionablePopupUtil* util = p->getPopupUtility();

      if (util != nullptr) {
          util->setAdditionalViewPopUpMenu(popup);
      }
  }
//  popup.show((Component) p, p.getWidth() / 2 + (int) ((getZoom() - 1.0) * p.getX()),
//          p.getHeight() / 2 + (int) ((getZoom() - 1.0) * p.getY()));
  popup->exec(QCursor::pos());
  /*popup.show((Component)pt, event.getX(), event.getY());*/
#endif
}
/*public*/ void LayoutEditor::mouseDragged(QGraphicsSceneMouseEvent* event)
{
 // initialize mouse position
 calcLocation(event->scenePos(), 0, 0);
 // ignore this event if still at the original point
 if ((!isDragging) && (xLoc == getAnchorX()) && (yLoc==getAnchorY())) return;

 // process this mouse dragged event
 if (isEditable())
 {
  ui->xLabel->setText(QString("%1").arg(xLoc));
  ui->yLabel->setText(QString("%1").arg(yLoc));
 }
 QPointF newPos = currentPoint = QPointF(dLoc.x() + startDel.y(), dLoc.y() + startDel.y());
 //don't allow negative placement, objects could become unreachable
 currentPoint = MathUtil::max(currentPoint, MathUtil::zeroPoint2D);

 if ((selectedObject!=nullptr) && (/*event.isMetaDown() ||*/ ((event->modifiers()&Qt::MetaModifier)!=0) || (selectedPointType==MARKER)))
  {
   // marker moves regardless of editMode or positionable
   PositionableLabel* pl = (PositionableLabel*)selectedObject;
   int xint = (int)newPos.x();
   int yint = (int)newPos.y();
   // don't allow negative placement, object could become unreachable
   if (xint<0) xint = 0;
   if (yint<0) yint = 0;
   ((Positionable*)pl)->setLocation(xint, yint);
   isDragging = true;
   //repaint();
   pl->updateScene();
   paintTargetPanel(editScene);
   return;
  }

  if (isEditable())
  {
   if ((selectedObject!=nullptr) && (/*event.isMetaDown() ||*/ !(event->modifiers()&Qt::AltModifier))|| allPositionable())
   {
    // moving a point
    if (snapToGridOnMove)
    {
     int xx = (((int)newPos.x()+4)/10)*10;
     int yy = (((int)newPos.y()+4)/10)*10;
     //newPos.setLocation(xx,yy);
     newPos.setX(xx);
     newPos.setY(yy);
    }
    if ((_positionableSelection && _positionableSelection->size() > 0)
           || (_layoutTrackSelection.size() > 0))
    {
       QPointF lastPoint = QPointF(_lastX, _lastY);
       QPointF offset = MathUtil::subtract(currentPoint, lastPoint);
       QPointF newPoint;

       for (Positionable* c : *_positionableSelection) {
           if ((qobject_cast< LEMemoryIcon*>(c->self())) && (c->getPopupUtility()->getFixedWidth() == 0)) {
               LEMemoryIcon* pm = (LEMemoryIcon*) c->self();
               newPoint = QPointF(pm->getOriginalX(), pm->getOriginalY());
           } else {
               newPoint = c->getLocation();
           }
           newPoint = MathUtil::add(newPoint, offset);
           //don't allow negative placement, objects could become unreachable
           newPoint = MathUtil::max(newPoint, MathUtil::zeroPoint2D);
           //c.setLocation(MathUtil.point2DToPoint(newPoint));
           c->setLocation(newPoint);
       }

       for (LayoutTrack* lt : _layoutTrackSelection) {
           QPointF center = lt->getCoordsCenter();
           newPoint = MathUtil::add(center, offset);
           //don't allow negative placement, objects could become unreachable
           newPoint = MathUtil::max(newPoint, MathUtil::zeroPoint2D);
           lt->setCoordsCenter(newPoint);
       }

       _lastX = xLoc;
       _lastY = yLoc;
    }
    else
    {
       switch (selectedPointType) {
           case LayoutTrack::POS_POINT: {
               ((PositionablePoint*) selectedObject)->setCoordsCenter(currentPoint);
               isDragging = true;
               break;
           }

           case LayoutTrack::TURNOUT_CENTER: {
            LayoutTurnout* t = ((LayoutTurnout*) selectedObject);
               t->setCoordsCenter(currentPoint);
//               if(t->connectA) t->connectA->invalidateItemType(editScene);
//               if(t->connectB) t->connectB->invalidateItemType(editScene);
//               if(t->connectC) t->connectC->invalidateItemType(editScene);
//               if(t->connectD) t->connectD->invalidateItemType(editScene);
               isDragging = true;
               break;
           }

           case LayoutTrack::TURNOUT_A: {
               ((LayoutTurnout*) selectedObject)->setCoordsA(currentPoint);
               break;
           }

           case LayoutTrack::TURNOUT_B: {
               ((LayoutTurnout*) selectedObject)->setCoordsB(currentPoint);
               break;
           }

           case LayoutTrack::TURNOUT_C: {
               ((LayoutTurnout*) selectedObject)->setCoordsC(currentPoint);
               break;
           }

           case LayoutTrack::TURNOUT_D: {
               ((LayoutTurnout*) selectedObject)->setCoordsD(currentPoint);
               break;
           }

           case LayoutTrack::LEVEL_XING_CENTER: {
               ((LevelXing*) selectedObject)->setCoordsCenter(currentPoint);
               isDragging = true;
               break;
           }

           case LayoutTrack::LEVEL_XING_A: {
               ((LevelXing*) selectedObject)->setCoordsA(currentPoint);
               break;
           }

           case LayoutTrack::LEVEL_XING_B: {
               ((LevelXing*) selectedObject)->setCoordsB(currentPoint);
               break;
           }

           case LayoutTrack::LEVEL_XING_C: {
               ((LevelXing*) selectedObject)->setCoordsC(currentPoint);
               break;
           }

           case LayoutTrack::LEVEL_XING_D: {
               ((LevelXing*) selectedObject)->setCoordsD(currentPoint);
               break;
           }

           case LayoutTrack::SLIP_LEFT:
           case LayoutTrack::SLIP_RIGHT: {
               ((LayoutSlip*) selectedObject)->setCoordsCenter(currentPoint);
               isDragging = true;
               break;
           }

           case LayoutTrack::SLIP_A: {
               ((LayoutSlip*) selectedObject)->setCoordsA(currentPoint);
               break;
           }

           case LayoutTrack::SLIP_B: {
               ((LayoutSlip*) selectedObject)->setCoordsB(currentPoint);
               break;
           }

           case LayoutTrack::SLIP_C: {
               ((LayoutSlip*) selectedObject)->setCoordsC(currentPoint);
               break;
           }

           case LayoutTrack::SLIP_D: {
               ((LayoutSlip*) selectedObject)->setCoordsD(currentPoint);
               break;
           }

           case LayoutTrack::TURNTABLE_CENTER: {
               ((LayoutTurntable*) selectedObject)->setCoordsCenter(currentPoint);
               isDragging = true;
               break;
           }

           case LayoutTrack::LAYOUT_POS_LABEL:
           case LayoutTrack::MULTI_SENSOR: {
               PositionableLabel* pl = (PositionableLabel*) selectedObject;

               if (pl->isPositionable()) {
                   pl->setLocation((int) currentPoint.x(), (int) currentPoint.y());
                   isDragging = true;
               }
               break;
           }

           case LayoutTrack::LAYOUT_POS_JCOMP: {
               PositionableJComponent* c = (PositionableJComponent*) selectedObject;

               if (c->isPositionable()) {
                   c->setLocation((int) currentPoint.x(), (int) currentPoint.y());
                   isDragging = true;
               }
               break;
           }

           case LayoutTrack::TRACK_CIRCLE_CENTRE: {
               TrackSegment* t = (TrackSegment*) selectedObject;
               t->reCalculateTrackSegmentAngle(currentPoint.x(), currentPoint.y());
               break;
           }

           default: {
               if ((foundPointType >= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN)
                       && (foundPointType <= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MAX)) {
                   int index = selectedPointType - LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN;
                   ((TrackSegment*) selectedObject)->setBezierControlPoint(currentPoint, index);
               } else if (selectedPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET) {
                   LayoutTurntable* turn = (LayoutTurntable*) selectedObject;
                   turn->setRayCoordsIndexed(currentPoint.x(), currentPoint.y(),
                           selectedPointType - LayoutTrack::TURNTABLE_RAY_OFFSET);
               }
               break;
           }
       }
   }
  }
  else if ( (beginObject!=nullptr) && event->modifiers()&Qt::ShiftModifier && ui->trackButton->isChecked() )
  {
   // dragging from first end of Track Segment
   currentLocation= QPointF(xLoc,yLoc);
   bool needResetCursor = (foundObject!=nullptr);
   if (findLayoutTracksHitPoint(currentLocation, true))
   {
   // have match to free connection point, change cursor
   //setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
    setCursor(Qt::PointingHandCursor);
   }
   else if (needResetCursor)
   {
    setCursor(Qt::ArrowCursor);
   }
   //repaint();
   paintTargetPanel(editScene);
  }
  else if ( selectionActive && (!event->modifiers()&Qt::ShiftModifier) && (!event->modifiers()&Qt::AltModifier) /*&& (!event.isMetaDown())*/ )
  {
   selectionWidth = xLoc - selectionX;
   selectionHeight = yLoc - selectionY;
   //repaint();
   paintTargetPanel(editScene);
  }
 }
 else
 {
  QRect r =  QRect(event->scenePos().x(), event->scenePos().y(), 1, 1);
      //((JComponent) event->getSource()).scrollRectToVisible(r);
  Q_UNUSED(r);
 }
 return;
}

/*public*/ void LayoutEditor::mouseMoved(QGraphicsSceneMouseEvent* event)
{
 calcLocation(event->scenePos(), 0, 0);
// if (isEditable())
//  {
//   xLabel.setText(Integer.toQString(xLoc));
//   yLabel.setText(Integer.toQString(yLoc));
//  }
 QList <Positionable*> selections = getSelectedItems(event);
 Positionable* selection = nullptr;
 int numSel = selections.size();
 if (numSel > 0)
 {
  selection = selections.at(0);
 }
// if (selection!=nullptr && selection.getDisplayLevel()>BKG && selection.showTooltip())
// {
//  showToolTip(selection, event);
// }
// else
// {
//  super.setToolTip(nullptr);
// }
 if (numSel != _prevNumSel)
 {
  //repaint();
  //highLightSelection(editScene);
  if(highlightRect != nullptr && highlightRect->scene() != 0)
  {
   editScene->removeItem(highlightRect);
  }
  highlightRect = new QGraphicsItemGroup();

  if(static_cast<PositionableLabel*>(selection) != nullptr)
  {
   PositionableLabel* l = (PositionableLabel*)selection;
   if(l == nullptr || l->_itemGroup == nullptr)
   {
   QGraphicsRectItem* item = new QGraphicsRectItem(l->_itemGroup->boundingRect());
   item->setPen(QPen(QBrush(_highlightColor),1,Qt::SolidLine));

   highlightRect->addToGroup(item);
   if(highlightRect && highlightRect->scene())
    log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
   editScene->addItem(highlightRect);
   }
  }
  else
  if(selection != nullptr && qobject_cast<LayoutTurnout*>(selection->self()) != nullptr)
  {
   LayoutTurnout* t = (LayoutTurnout*)selection;
   QGraphicsRectItem* item = new QGraphicsRectItem(t->item->boundingRect());
   highlightRect->addToGroup(item);
   if(highlightRect && highlightRect->scene())
    log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
   editScene->addItem(highlightRect);
  }
  _prevNumSel = numSel;
 }
}

bool LayoutEditor::isEditable() {return bIsEditable;}
/**
 * Add an Anchor point.
 */
/*public*/ void LayoutEditor::addAnchor()
{
 addAnchor(currentPoint);
}

/*private*/ PositionablePoint* LayoutEditor::addAnchor(QPointF p) {
    numAnchors++;
    // get unique name
    QString name = "";
    bool duplicate = true;
    while (duplicate) {
        name = "A" + numAnchors;
        if (finder->findPositionablePointByName(name) == nullptr) {
            duplicate = false;
        }
        if (duplicate) {
            numAnchors++;
        }
    }
    // create object
    PositionablePoint* o = new PositionablePoint(name,
            PositionablePoint::ANCHOR, p, this);
    //if (o!=nullptr) {
    layoutTrackList->append(o);
    unionToPanelBounds(o->getBounds());
    setDirty(true);
    //}
    return o;
}

//
//
//
/*private*/ void LayoutEditor::selectZoomMenuItem(double zoomFactor) {
    //this will put zoomFactor on 100% increments
    //(so it will more likely match one of these values)
    int newZoomFactor = ((int) qRound(zoomFactor)) * 100;
    noZoomItem->setChecked(newZoomFactor == 100);
    zoom20Item->setChecked(newZoomFactor == 200);
    zoom30Item->setChecked(newZoomFactor == 300);
    zoom40Item->setChecked(newZoomFactor == 400);
    zoom50Item->setChecked(newZoomFactor == 500);
    zoom60Item->setChecked(newZoomFactor == 600);
    zoom70Item->setChecked(newZoomFactor == 700);
    zoom80Item->setChecked(newZoomFactor == 800);

    //this will put zoomFactor on 50% increments
    //(so it will more likely match one of these values)
    newZoomFactor = ((int) (zoomFactor * 2)) * 50;
    zoom05Item->setChecked(newZoomFactor == 50);
    zoom15Item->setChecked(newZoomFactor == 150);

    //this will put zoomFactor on 25% increments
    //(so it will more likely match one of these values)
    newZoomFactor = ((int) (zoomFactor * 4)) * 25;
    zoom025Item->setChecked(newZoomFactor == 25);
    zoom075Item->setChecked(newZoomFactor == 75);
}

/*private*/ void LayoutEditor::setupZoomMenu(QMenuBar* menuBar) {
 QMenu* zoomMenu = ui->menuZoom;//new QMenu(tr("Zoom"));
 //menuBar.add(zoomMenu);
 QActionGroup* zoomButtonGroup = new QActionGroup(this);

 //add zoom choices to menu
 QAction* zoomInItem = new QAction(tr("Zoom In"),this);
 //zoomInItem.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("zoomInMnemonic")));
 QString zoomInAccelerator = tr("EQUALS");
 //log.debug("zoomInAccelerator: " + zoomInAccelerator);
 //zoomInItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(zoomInAccelerator), primary_modifier));
 zoomMenu->addAction(zoomInItem);
// zoomInItem.addActionListener((ActionEvent event) -> {
//     zoomIn();
// });
 connect(zoomInItem, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));

 QAction* zoomOutItem = new QAction(tr("Zoom Out"));
// zoomOutItem.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("zoomOutMnemonic")));
// String zoomOutAccelerator = Bundle.getMessage("zoomOutAccelerator");
 //log.debug("zoomOutAccelerator: " + zoomOutAccelerator);
// zoomOutItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(zoomOutAccelerator), primary_modifier));
 zoomMenu->addAction(zoomOutItem);
// zoomOutItem.addActionListener((ActionEvent event) -> {
//     zoomOut();
// });
 connect(zoomOutItem, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));

 QAction* zoomFitItem = new QAction(tr("Zoom To Fit"));
 zoomMenu->addAction(zoomFitItem);
// zoomFitItem.addActionListener((ActionEvent event) -> {
//     zoomToFit();
// });
 connect(zoomFitItem, SIGNAL(triggered(bool)), this, SLOT(zoomToFit()));
 zoomMenu->addSeparator();

 zoomButtonGroup->setExclusive(true);
 // add zoom choices to menu
 QAction* zoom025Item = new QAction("x 0.25", this);
 zoom025Item->setCheckable(true);
 zoomMenu->addAction(zoom025Item);
// zoom025Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(0.25);
//     }
// });
 connect(zoom025Item, SIGNAL(triggered(bool)), this, SLOT(onZoom025Item()));
 zoomButtonGroup->addAction(zoom025Item);
 QAction* zoom05Item = new QAction("x 0.5", this);
 zoom05Item->setCheckable(true);
 zoomMenu->addAction(zoom05Item);
// zoom05Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(0.5);
//     }
// });
 connect(zoom05Item, SIGNAL(triggered(bool)), this, SLOT(onZoom05Item()));
 zoomButtonGroup->addAction(zoom05Item);
 QAction* zoom075Item = new QAction("x 0.75", this);
 zoom075Item->setCheckable(true);
 zoomMenu->addAction(zoom075Item);
// zoom075Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(0.75);
//     }
// });
 connect(zoom075Item, SIGNAL(triggered(bool)), this, SLOT(onZoom075Item()));
 zoomButtonGroup->addAction(zoom075Item);
 QAction* noZoomItem = new QAction(tr("No Zoom"), this);
 noZoomItem->setCheckable(true);
 zoomMenu->addAction(noZoomItem);
// noZoomItem.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(1.0);
//     }
// });
 connect(noZoomItem, SIGNAL(triggered(bool)), this, SLOT(onNoZoomItem()));
 zoomButtonGroup->addAction(noZoomItem);
 QAction* zoom15Item = new QAction("x 1.5", this);
 zoom15Item->setCheckable(true);
 zoomMenu->addAction(zoom15Item);
// zoom15Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(1.5);
//     }
// });
 connect(zoom15Item, SIGNAL(triggered(bool)), this, SLOT(onZoom15Item()));
 zoomButtonGroup->addAction(zoom15Item);
 QAction* zoom20Item = new QAction("x 2.0",this);
 zoom20Item->setCheckable(true);
 zoomMenu->addAction(zoom20Item);
// zoom20Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(2.0);
//     }
// });
 connect(zoom20Item, SIGNAL(triggered(bool)), this, SLOT(onZoom20Item()));
 zoomButtonGroup->addAction(zoom20Item);
 QAction* zoom30Item = new QAction("x 3.0", this);
 zoomMenu->addAction(zoom30Item);
// zoom30Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(3.0);
//     }
// });
 connect(zoom30Item, SIGNAL(triggered(bool)), this, SLOT(onZoom30Item()));
 zoomButtonGroup->addAction(zoom30Item);
 QAction* zoom40Item = new QAction("x 4.0", this);
 zoomMenu->addAction(zoom40Item);
// zoom40Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
//         setZoom(4.0);
//     }
// });
 connect(zoom40Item, SIGNAL(triggered(bool)), this, SLOT(onZoom40Item()));
 zoomButtonGroup->addAction(zoom40Item);
 noZoomItem->setChecked(true);
}

void LayoutEditor::onZoom025Item()
{
 setZoom(0.25);
}
void LayoutEditor::onZoom05Item()
{
 setZoom(0.5);
}
void LayoutEditor::onZoom075Item()
{
 setZoom(0.75);
}
void LayoutEditor::onNoZoomItem()
{
 setZoom(1.0);
}

void LayoutEditor::onZoom15Item()
{
 setZoom(1.5);
}
void LayoutEditor::onZoom30Item()
{
 setZoom(3.0);
}
void LayoutEditor::onZoom40Item()
{
 setZoom(4.0);
}
void LayoutEditor::onZoom20Item()
{
 setZoom(2.0);
}

/*public*/ double LayoutEditor::setZoom(double zoomFactor) {
    //TODO: add code to re-calculate minZoom (so panel never smaller than view)
    double newZoom = MathUtil::pin(zoomFactor, minZoom, maxZoom);

    if (!MathUtil::equals(newZoom, getPaintScale())) {
        log->debug(tr("zoom: %1").arg(zoomFactor));
        setPaintScale(newZoom);
//        adjustScrollBars();

        //zoomLabel->setText(QString("x%1$,.2f").arg(newZoom));
        selectZoomMenuItem(newZoom);

        //save the window specific saved zoom user preference
        UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager")); //.ifPresent((prefsMgr) -> {
        if(prefsMgr)
            prefsMgr->setProperty(getWindowFrameRef(), "zoom", zoomFactor);
        //});
    }
    return getPaintScale();
}

/*public*/ double LayoutEditor::getZoom() {
    return getPaintScale();
}

/*private*/ double LayoutEditor::zoomIn() {
    return setZoom(getZoom() * 1.1);
}

/*private*/ double LayoutEditor::zoomOut() {
    return setZoom(getZoom() / 1.1);
}

void LayoutEditor::onZoomIn()
{
 //setPaintScale(getPaintScale()* 1.1);
 xScale = xScale*1.1;
 yScale = yScale*1.1;
 editPanel->scale(xScale, yScale);

}
void LayoutEditor::onZoomOut()
{
 //setPaintScale(getPaintScale()/ 1.1);
 xScale = xScale/1.1;
 yScale = yScale/1.1;
 editPanel->scale(xScale, yScale);

}

//
// TODO: make this public? (might be useful!)
//
/*private*/ QRectF LayoutEditor::calculateMinimumLayoutBounds() {

 return editScene->sceneRect();
}

void LayoutEditor::onCalculateBounds()
{
 QRectF bounds = calculateMinimumLayoutBounds();
 log->info(tr("calculated bounds = %1 %2 %3 %4").arg(bounds.x()).arg(bounds.y()).arg(bounds.width()).arg(bounds.height()));
 log->info(tr("scene bounds = %1 %2 %3 %4").arg(editScene->itemsBoundingRect().x()).arg(editScene->itemsBoundingRect().y()).arg(editScene->itemsBoundingRect().width()).arg(editScene->itemsBoundingRect().height()));
}

/**
 * resize panel bounds
 *
 * @param forceFlag if false only grow bigger
 * @return the new (?) panel bounds
 */
/*private*/ QRectF LayoutEditor::resizePanelBounds(bool forceFlag) {
    QRectF panelBounds = getPanelBounds();
    QRectF layoutBounds = calculateMinimumLayoutBounds();
    if (forceFlag) {
        panelBounds = layoutBounds;
    } else {
        panelBounds.united(layoutBounds);
    }

    // don't let origin go negative
    QRectF zeroToInfinityQRectF(0.0, 0.0, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    panelBounds = panelBounds.intersected(zeroToInfinityQRectF);

    // make sure it includes the origin
//    panelBounds.united(MathUtil::zeroQPointF());

    log->debug(tr("resizePanelBounds: %1, %2, %3, %4").arg(panelBounds.x()).arg(panelBounds.y()).arg(panelBounds.width()).arg(panelBounds.height()));

    setPanelBounds(panelBounds);

    return panelBounds;
}

/*private*/ double LayoutEditor::zoomToFit() {
    QRectF layoutBounds = resizePanelBounds(true);

    // calculate the bounds for the scroll pane
//    QScrollArea* scrollPane = getPanelScrollPane();
//    QRectF scrollBounds = QRectF(0,0, scrollPane->viewportSizeHint().x(), scrollPane->viewportSizeHint().y());//scrollPane->vgetViewportBorderBounds();
    QWidget* scrollPane = editPanel->viewport();
    QRectF scrollBounds = QRectF(0,0, scrollPane->sizeHint().width(), scrollPane->sizeHint().height());

    // don't let origin go negative
    QRectF zeroToInfinityQRectF(0.0, 0.0, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    scrollBounds = scrollBounds.intersected(zeroToInfinityQRectF);

    // calculate the horzontial and vertical scales
    double scaleWidth = scrollPane->width() / layoutBounds.width();
    double scaleHeight = scrollPane->height() / layoutBounds.height();

    // set the new zoom to the smallest of the two
    double result = setZoom(qMin(scaleWidth, scaleHeight));

//    // set the new zoom (return value may be different)
//    result = setZoom(result);

    // calculate new scroll bounds
//    scrollBounds = scrollBounds.adjust(0,0, result.x(), result.y());//MathUtil::scale(layoutBounds, result);

    // don't let origin go negative
//    scrollBounds = scrollBounds.intersected(MathUtil::zeroToInfinityQRectF());

    // and scroll to it
    //scrollPane->scrollRectToVisible(MathUtil::QRectFToRectangle(scrollBounds));
    //scrollPane->ensureVisible(scrollBounds.x(), scrollBounds.y());
    if(result == xScale)
     return result;
//    if(xScale > 1.0)
//     editPanel->scale(1.0/xScale, 1.0/yScale);

    editPanel->scale(result, result);
    xScale = yScale = result;
    return result;
}

/**
 * Add an End Bumper point.
 */
/*public*/ void LayoutEditor::addEndBumper() {
    numEndBumpers ++;
    // get unique name
    QString name = finder->uniqueName("EB", ++numEndBumpers);
    // create object
    PositionablePoint* o = new PositionablePoint(name,
                        PositionablePoint::END_BUMPER, currentPoint, this);
    layoutTrackList->append(o);
    unionToPanelBounds(o->getBounds());
    setDirty(true);
}

/**
 * Add an Edge Connector point.
 */
/*public*/ void LayoutEditor::addEdgeConnector()
{
 numEdgeConnectors++;
    //get unique name
 QString name = "";
 bool duplicate = true;
 while (duplicate) {
     name = "EC" + numEdgeConnectors;
     if (finder->findPositionablePointByName(name) == nullptr) {
         duplicate = false;
     }
     if (duplicate) {
         numEdgeConnectors++;
     }
 }

 //create object
 PositionablePoint* o = new PositionablePoint(name,
         PositionablePoint::EDGE_CONNECTOR, currentPoint, this);

 layoutTrackList->append(o);
 unionToPanelBounds(o->getBounds());
}

/**
 * Add a Track Segment
 */
/*public*/ void LayoutEditor::addTrackSegment()
{
 numTrackSegments ++;
 // get unique name
 QString name = "";
 bool duplicate = true;
 while (duplicate)
 {
  name = "T"+QString::number(numTrackSegments);
  if (findTrackSegmentByName(name)==nullptr) duplicate = false;
  if (duplicate) numTrackSegments ++;
 }
 // create object
 newTrack = new TrackSegment(name,(LayoutTrack*)beginObject,beginPointType,
                 (LayoutTrack*)foundObject,foundPointType,ui->chkDashed->isChecked(), ui->chkMainline->isChecked(),this);
 if (newTrack!=nullptr)
 {
  layoutTrackList->append(newTrack);
  unionToPanelBounds(newTrack->getBounds());
  setDirty(true);
  // link to connected objects
  setLink(newTrack,TRACK,beginObject,beginPointType);
  setLink(newTrack,TRACK,foundObject,foundPointType);
  // check on layout block
  LayoutBlock* b = provideLayoutBlock(ui->blockNameLabel->text().trimmed());
  if (b!=nullptr)
  {
   newTrack->setLayoutBlock(b);
   auxTools->setBlockConnectivityChanged();
   // check on occupancy sensor
   QString sensorName = (ui->blockSensorNameLabel->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b,(Component*)this))
    {
     b->setOccupancySensorName("");
    }
    else
    {
     ui->blockSensorNameLabel->setText( b->getOccupancySensorName() );
    }
   }
   newTrack->updateBlockInfo();
  }
 }
 else
 {
  log->error("Failure to create a new Track Segment");
 }
}

/**
 * Add a Level Crossing
 */
/*public*/ void LayoutEditor::addLevelXing()
{
 numLevelXings ++;
 // get unique name
 QString name = finder->uniqueName("X", ++numLevelXings);
 // create object
 LevelXing* o = new LevelXing(name,currentPoint,this);
 if (o!=nullptr)
 {
  //xingList->append(o);
  layoutTrackList->append(o);
  setDirty(true);
  // check on layout block
  LayoutBlock* b = provideLayoutBlock(ui->blockNameLabel->text().trimmed());
  if (b!=nullptr)
  {
   o->setLayoutBlockAC(b);
   o->setLayoutBlockBD(b);
   // check on occupancy sensor
   QString sensorName = (ui->blockSensorNameLabel->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b,(Component*)this))
    {
     b->setOccupancySensorName("");
    }
    else {
     ui->blockSensorNameLabel->setText( b->getOccupancySensorName() );
    }
   }
  }
 }
}

/**
 * Add a LayoutSlip
 */
/*public*/ void LayoutEditor::addLayoutSlip(int type)
{
 double rot = 0.0;
 QString s = ui->rotationComboBox->currentText().trimmed();
 if (s.length()<1)
 {
  rot = 0.0;
 }
 else
 {
  try
  {
   bool bOk = false;
   rot = s.toDouble(&bOk);
   if(!bOk) throw new Exception();
  }
  catch (Exception e)
  {
//            JOptionPane.showMessageDialog(this, rb.getQString("Error3")+" "+
//                    e,rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this,tr("Error"), tr("Error in rotation entry:"));
   return;
  }
 }
 numLayoutSlips ++;
 // get unique name
 QString name = finder->uniqueName("SL", ++numLayoutSlips);
 // create object
 LayoutSlip* o = new LayoutSlip(name,currentPoint, rot, this, type);
 layoutTrackList->append(o);
 setDirty();

 // check on layout block
 QString newName = ui->blockIDComboBox->currentText();
 LayoutBlock* b = provideLayoutBlock(ui->blockNameLabel->text().trimmed());
 if (b != nullptr)
 {
     o->setLayoutBlock(b);

     //check on occupancy sensor
     QString sensorName = ui->blockSensorComboBox->getDisplayName();

     if (!sensorName.isEmpty()) {
         if (!validateSensor(sensorName, b, (Component*)this)) {
             b->setOccupancySensorName("");
         } else {
             ui->blockSensorComboBox->setText(b->getOccupancySensorName());
         }
     }
 }

 QString turnoutName = ui->turnoutNameComboBox->currentText();

 if (validatePhysicalTurnout(turnoutName, this)) {
     //turnout is valid and unique.
     o->setTurnout(turnoutName);

     if (o->getTurnout()->getSystemName() == (turnoutName.toUpper())) {
         ui->turnoutNameComboBox->setText(turnoutName.toUpper());
     }
 } else {
     o->setTurnout("");
     ui->turnoutNameComboBox->setText("");
     ui->turnoutNameComboBox->setCurrentIndex(-1);
 }
 turnoutName = ui->extraTurnoutNameComboBox->getDisplayName();

 if (validatePhysicalTurnout(turnoutName, this)) {
     //turnout is valid and unique.
     o->setTurnoutB(turnoutName);

     if (o->getTurnoutB()->getSystemName()==(turnoutName.toUpper())) {
         ui->extraTurnoutNameComboBox->setText(turnoutName.toUpper());
     }
 } else {
     o->setTurnoutB("");
     ui->extraTurnoutNameComboBox->setText("");
     ui->extraTurnoutNameComboBox->setCurrentIndex(-1);
 }
}

/**
 * Add a Layout Turnout
 */
/*public*/ void LayoutEditor::addLayoutTurnout(int type)
{
 // get the rotation entry
 double rot = 0.0;
 QString s = ui->rotationComboBox->currentText().trimmed();
 if (s.length()<1)
 {
  rot = 0.0;
 }
 else
 {
  try
  {
   bool bOk = false;
   rot = /*Double.parseDouble(s)*/ s.toDouble(&bOk);
   if(!bOk) throw NumberFormatException();
  }
  catch (NumberFormatException* e)
  {
//            JOptionPane.showMessageDialog(this, tr("Error3")+" "+
//                    e,tr("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("Error in rotation entry:"));
   return;
  }
 }

 numLayoutTurnouts ++;
 // get unique name
 QString name = finder->uniqueName("TO", ++numLayoutTurnouts);
 addLayoutTurnout(name, type, rot, currentPoint);
}

LayoutTurnout* LayoutEditor::addLayoutTurnout(QString name, int type, double rot, QPointF currentPoint)
{
 // create object
 LayoutTurnout* o = new LayoutTurnout(name,type,                                   currentPoint,rot,xScale,yScale,this);
 //if (o!=nullptr) {
 //turnoutList->append(o);
 layoutTrackList->append(o);
 setDirty(true);
 // check on layout block
 LayoutBlock* b = provideLayoutBlock(ui->blockNameLabel->text().trimmed());
 if (b!=nullptr)
 {
  o->setLayoutBlock(b);
  // check on occupancy sensor
  QString sensorName = (ui->blockSensorNameLabel->text().trimmed());
  if (sensorName.length()>0)
  {
   if (!validateSensor(sensorName,b,(Component*)this))
   {
    b->setOccupancySensorName("");
   }
   else
   {
    ui->blockSensorNameLabel->setText( b->getOccupancySensorName() );
   }
  }
 }
 // set default continuing route Turnout State
 o->setContinuingSense(Turnout::CLOSED);
 // check on a physical turnout
 QString turnoutName = ui->turnoutNameComboBox->currentText().trimmed();
 if ( validatePhysicalTurnout(turnoutName/*, this*/) )
 {
  // turnout is valid and unique.
  o->setTurnout(turnoutName);
  if (o->getTurnout()->getSystemName()==(turnoutName.toUpper()))
  {
   ui->turnoutNameComboBox->setText(turnoutName.toUpper());
  }
 }
 else
 {
  o->setTurnout("");
  ui->turnoutNameComboBox->setText("");
 }
 return o;
}

/**
 * Validates that a physical turnout exists and is unique among Layout Turnouts
 *    Returns true if valid turnout was entered, false otherwise
 */
/*public*/ bool LayoutEditor::validatePhysicalTurnout(QString inTurnoutName, QWidget* inOpenPane)
{
 //check if turnout name was entered
 if (inTurnoutName.isEmpty()) {
     //no turnout entered
     return false;
 }

 //check that the unique turnout name corresponds to a defined physical turnout
 Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(inTurnoutName);
 if (t == nullptr) {
     //There is no turnout corresponding to this name
     if (inOpenPane != nullptr) {
         JOptionPane::showMessageDialog(inOpenPane,
                 tr("Error - Cannot assign turnout because there\nis no turnout defined for \"%1\".\nPlease enter turnout via the Turnout Table and try again.").arg(
                         inTurnoutName),
                 tr("Error"), JOptionPane::ERROR_MESSAGE);
     }
     return false;
 }

 log->debug(tr("validatePhysicalTurnout('%1')").arg(inTurnoutName));
 bool result = true;  // assume success (optimist!)

 //ensure that this turnout is unique among Layout Turnouts in this Layout
 for (LayoutTurnout* lt : getLayoutTurnouts()) {
     t = lt->getTurnout();
     if (t != nullptr) {
         QString sname = t->getSystemName();
         QString uname = t->getUserName();
         log->debug(tr("%1: Turnout tested '%2' and '%3'.").arg(lt->getName()).arg(sname).arg(uname));
         if ((sname == (inTurnoutName.toUpper()))
                 || ((uname != "") && (uname ==(inTurnoutName)))) {
             result = false;
             break;
         }
     }

     // Only check for the second turnout if the type is a double cross over
     // otherwise the second turnout is used to throw an additional turnout at
     // the same time.
     if (lt->getTurnoutType() >= LayoutTurnout::DOUBLE_XOVER) {
         t = lt->getSecondTurnout();
         if (t != nullptr) {
             QString sname = t->getSystemName();
             QString uname = t->getUserName();
             log->debug(tr("%1: 2nd Turnout tested '%2' and '%3'.").arg(lt->getName()).arg(sname).arg(uname));
             if ((sname ==(inTurnoutName.toUpper()))
                     || ((uname != "") && (uname ==(inTurnoutName)))) {
                 result = false;
                 break;
             }
         }
     }
 }

 if (result) {   // only need to test slips if we haven't failed yet...
     //ensure that this turnout is unique among Layout slips in this Layout
     for (LayoutSlip* sl : getLayoutSlips()) {
         t = sl->getTurnout();
         if (t != nullptr) {
             QString sname = t->getSystemName();
             QString uname = t->getUserName();
             log->debug(tr("%1: slip Turnout tested '%2' and '%3'.").arg(sl->getName()).arg(sname).arg(uname));
             if ((sname ==(inTurnoutName.toUpper()))
                     || ((uname != "") && (uname ==(inTurnoutName)))) {
                 result = false;
                 break;
             }
         }

         t = sl->getTurnoutB();
         if (t != nullptr) {
             QString sname = t->getSystemName();
             QString uname = t->getUserName();
             log->debug(tr("%1: slip Turnout B tested '%2' and '%3'.").arg(sl->getName()).arg( sname).arg(uname));
             if ((sname == (inTurnoutName.toUpper()))
                     || ((uname != "") && (uname ==(inTurnoutName)))) {
                 result = false;
                 break;
             }
         }
     }
 }
 if (!result && (inOpenPane != nullptr)) {
     JOptionPane::showMessageDialog(inOpenPane,
             tr("Error - Physical turnout \"%1\" is already linked to a different Panel Turnout.\nPlease enter another turnout name and try again.")
                     .arg(inTurnoutName),
             tr("Error"), JOptionPane::ERROR_MESSAGE);
 }
 return result;
}

/*private*/ void LayoutEditor::highLightSelection(EditScene* g)
{
  //java.awt.Stroke stroke = g.getStroke();
//  Color color = g.getColor();
//  g.setColor(new Color(204, 207, 88));
//  g.setStroke(new java.awt.BasicStroke(2.0f));
 QColor color = QColor(204,207,88);
 QPen pen(color,2.0);
 if(highlightRect != nullptr && highlightRect->scene() != 0)
 {
  g->removeItem(highlightRect);
 }
 highlightRect = new QGraphicsItemGroup();

 if (_positionableSelection!=nullptr)
 {
  for (int i = 0; i<_positionableSelection->size(); i++)
  {
   Positionable* c = _positionableSelection->at(i);
   //g.drawRect(c.getX(), c.getY(), c.maxWidth(), c.maxHeight());
   QGraphicsRectItem* item;
   SensorIcon* si;
   LocoIcon* li;
   LEMemoryIcon* mi;
   if((si = static_cast<SensorIcon*>(c))!=nullptr)
    item = new QGraphicsRectItem(QRectF(si->getX(), si->getY(), si->maxWidth(), si->maxHeight()));
   else if((li = static_cast<LocoIcon*>(c))!=nullptr)
    item = new QGraphicsRectItem(QRectF(li->getX(), li->getY(), li->maxWidth(), li->maxHeight()));
   else if((mi = static_cast<LEMemoryIcon*>(c))!=nullptr)
    item = new QGraphicsRectItem(QRectF(mi->getX(), mi->getY(), mi->maxWidth(), mi->maxHeight()));

   item->setPen(pen);
   highlightRect->addToGroup(item);
  }
 }
 // loop over all defined turnouts
 if (_turnoutSelection!=nullptr)
 {
  for (int i = 0; i<_turnoutSelection->size();i++)
  {
   LayoutTurnout* t = _turnoutSelection->at(i);
   int minx = (int) qMin(qMin(t->getCoordsA().x(), t->getCoordsB().x()),qMin(t->getCoordsC().x(), t->getCoordsD().x()));
   int miny = (int) qMin(qMin(t->getCoordsA().y(), t->getCoordsB().y()),qMin(t->getCoordsC().y(), t->getCoordsD().y()));
   int maxx = (int) qMax(qMax(t->getCoordsA().x(), t->getCoordsB().x()),qMax(t->getCoordsC().x(), t->getCoordsD().x()));
   int maxy = (int) qMax(qMax(t->getCoordsA().y(), t->getCoordsB().y()),qMax(t->getCoordsC().y(), t->getCoordsD().y()));
   int width = maxx-minx;
   int height = maxy-miny;
   int x = (int) t->getCoordsCenter().x()-(width/2);
   int y = (int) t->getCoordsCenter().y()-(height/2);
   //g.drawRect(x, y, width, height);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
   item->setPen(pen);
   highlightRect->addToGroup(item);
  }
 }
 if (_xingSelection!=nullptr)
 {
  // loop over all defined level crossings
  for (int i = 0; i<_xingSelection->size();i++)
  {
   LevelXing* xing = _xingSelection->at(i);
   int minx = (int) qMin(qMin(xing->getCoordsA().x(), xing->getCoordsB().x()),qMin(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int miny = (int) qMin(qMin(xing->getCoordsA().y(), xing->getCoordsB().y()),qMin(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int maxx = (int) qMax(qMax(xing->getCoordsA().x(), xing->getCoordsB().x()),qMax(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int maxy = (int) qMax(qMax(xing->getCoordsA().y(), xing->getCoordsB().y()),qMax(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int width = maxx-minx;
   int height = maxy-miny;
   int x = (int) xing->getCoordsCenter().x()-(width/2);
   int y = (int) xing->getCoordsCenter().y()-(height/2);
   //g.drawRect(x, y, width, height);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
   item->setPen(pen);
   highlightRect->addToGroup(item);
  }
 }
  if (_slipSelection!=nullptr)
  {
  // loop over all defined level crossings
   for (int i = 0; i<_slipSelection->size();i++)
  {
    LayoutSlip* xing = _slipSelection->at(i);
    int minx = (int) qMin(qMin(xing->getCoordsA().x(), xing->getCoordsB().x()),qMin(xing->getCoordsC().x(), xing->getCoordsD().x()));
    int miny = (int) qMin(qMin(xing->getCoordsA().y(), xing->getCoordsB().y()),qMin(xing->getCoordsC().y(), xing->getCoordsD().y()));
    int maxx = (int) qMax(qMax(xing->getCoordsA().x(), xing->getCoordsB().x()),qMax(xing->getCoordsC().x(), xing->getCoordsD().x()));
    int maxy = (int) qMax(qMax(xing->getCoordsA().y(), xing->getCoordsB().y()),qMax(xing->getCoordsC().y(), xing->getCoordsD().y()));
    int width = maxx-minx;
    int height = maxy-miny;
    int x = (int) xing->getCoordsCenter().x()-(width/2);
    int y = (int) xing->getCoordsCenter().y()-(height/2);
    //g->drawRect(x, y, width, height);
    QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
    item->setPen(pen);
    highlightRect->addToGroup(item);
   }
  }
  // loop over all defined turntables
  if (_turntableSelection!=nullptr)
  {
   for (int i = 0; i<_turntableSelection->size();i++)
   {
       LayoutTurntable* tt = _turntableSelection->at(i);
       QPointF center = tt->getCoordsCenter();
       int x = (int) center.x() - (int)tt->getRadius();
       int y = (int) center.y() - (int)tt->getRadius();
       //g.drawRect(x, y, ((int)tt->getRadius()*2), ((int)tt->getRadius()*2));
          QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width(), height()));
          item->setPen(pen);
          highlightRect->addToGroup(item);
   }
  }
  // loop over all defined Anchor Points and End Bumpers
  if (_pointSelection!=nullptr)
  {
   for (int i = 0; i<_pointSelection->size();i++)
   {
    PositionablePoint* p = _pointSelection->at(i);
    QPointF coord = p->getCoords();
    //g.drawRect((int)coord.getX()-4, (int)coord.getY()-4, 9, 9);
    QGraphicsRectItem* item = new QGraphicsRectItem(QRectF((int)coord.x()-4, (int)coord.y()-4, 9, 9));
    item->setPen(pen);
    highlightRect->addToGroup(item);
   }
  }
//  g.setColor(color);
//  g.setStroke(stroke);
  if(highlightRect && highlightRect->scene())
   log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
  g->addItem(highlightRect);
}

/*private*/ void LayoutEditor::createSelectionGroups()
{
  QList <Positionable*> contents = getContents();
  QRectF selectionRect(selectionX, selectionY, selectionWidth, selectionHeight);
  for (Positionable* o : contents)
  {
     if (selectionRect.contains(o->getLocation())) {
         if (!_positionableSelection->contains(o)) {
             _positionableSelection->append(o);
         }
     }
 }

 for (LayoutTrack* lt : *layoutTrackList) {
     QPointF center = lt->getCoordsCenter();
     if (selectionRect.contains(center)) {
         if (!_layoutTrackSelection.contains(lt)) {
             _layoutTrackSelection.append(lt);
         }
     }
 }
 redrawPanel();
}


/*private*/ void LayoutEditor::clearSelectionGroups(){
  _pointSelection=nullptr;
  _turntableSelection=nullptr;
  _xingSelection=nullptr;
  _slipSelection=nullptr;
  _turnoutSelection=nullptr;
  _positionableSelection=nullptr;
  //_labelSelection=nullptr;
}
/**
* Return a List of all items whose bounding rectangle contain the mouse position.
* ordered from top level to bottom
*/
/*protected*/ QList <Positionable*> LayoutEditor::getSelectedItems(QGraphicsSceneMouseEvent* event)
{
  double x = event->scenePos().x();
  double y = event->scenePos().y();
  QRectF rect;
  QVector <Positionable*>* selections = new QVector <Positionable*>();
  for (int i=0; i<_contents->size(); i++)
  {
   Positionable* p = _contents->at(i);
//            if (p instanceof PositionableShape && !(event->modifiers()&Qt::ShiftModifier)) {
//            	continue;
//            }

   rect= ((PositionableLabel*)p)->getBounds();
   //if (_debug && !_dragging) log->debug("getSelectedItems: rect= ("+rect.x+","+rect.y+
   //                      ") width= "+rect.width+", height= "+rect.height+
   //                                    " isPositionable= "+p.isPositionable());
   QRectF rect2D(rect.x()*_paintScale, rect.y()*_paintScale, rect.width()*_paintScale,                                                        rect.height()*_paintScale);
   if (rect2D.contains(x, y) && (((PositionableLabel*)p)->getDisplayLevel()>BKG || event->modifiers()&Qt::ControlModifier))
   {
    //qDebug() << tr("rect %1,%2,%3,%4 contains %5,%6").arg(rect2D.x()).arg(rect2D.y()).arg(rect2D.width()).arg(rect2D.height()).arg(x).arg(y);
    bool added =false;
    int level = ((PositionableLabel*)p)->getDisplayLevel();
    for (int k=0; k<selections->size(); k++)
    {
     if (level >= ((PositionableLabel*)selections->at(k))->getDisplayLevel())
     {
      selections->insert(k, p);
      added = true;       // OK to lie in the case of background icon
      break;
     }
    }
    if (!added)
    {
     selections->append(p);
    }
   }
  }
  //if (_debug)  log->debug("getSelectedItems at ("+x+","+y+") "+selections.size()+" found,");
  return selections->toList();
}

///*public*/ PositionablePoint* LayoutEditor::findPositionablePointByName(QString name) {
//  if (name.length()<=0) return nullptr;
//  for (int i = 0; i<pointList->size(); i++) {
//      PositionablePoint* p = pointList->at(i);
//      if (p->getID()==(name)) {
//          return p;
//      }
//  }
//  return nullptr;
//}
///*public*/ PositionablePoint* LayoutEditor::findPositionablePointAtTrackSegments(TrackSegment* tr1, TrackSegment* tr2) {
//  for (int i = 0; i<pointList->size(); i++) {
//      PositionablePoint* p = pointList->at(i);
//      if ( ( (p->getConnect1()==tr1) && (p->getConnect2()==tr2) ) ||
//              ( (p->getConnect1()==tr2) && (p->getConnect2()==tr1) ) ) {
//          return p;
//      }
//  }
//  return nullptr;
//}
void LayoutEditor::setDirty(bool b) {bDirty = b;}
bool LayoutEditor::isDirty() {return bDirty;}
/**
* Allow external reset of dirty bit
*/
/*public*/ void LayoutEditor::resetDirty()
{
  setDirty(false);
  savedEditMode = isEditable();
  savedPositionable = allPositionable();
  savedControlLayout = allControlling();
  savedAnimatingLayout = animatingLayout;
  savedShowHelpBar = showHelpBar;
}

/*public*/ TrackSegment* LayoutEditor::findTrackSegmentByName(QString name)
{
  if (name.length()<=0) return nullptr;
  for (TrackSegment* t : getTrackSegments()) {
      if (t->getID()==(name)) {
          return t;
      }
  }
  return nullptr;
}
/**
* Adds a link in the 'to' object to the 'from' object
*/
/*private*/ void LayoutEditor::setLink(QObject* fromObject,int fromPointType,
                                      QObject* toObject,int toPointType)
{
 switch (toPointType)
 {
  case POS_POINT:
   if (fromPointType==TRACK)
   {
    ((PositionablePoint*)toObject)->setTrackConnection((TrackSegment*)fromObject);
   }
   else
   {
    log->error("Attempt to set a non-TRACK connection to a Positionable Point");
   }
   break;
  case TURNOUT_A:
      ((LayoutTurnout*)toObject)->setConnectA((LayoutTrack*)fromObject,fromPointType);
      break;
  case TURNOUT_B:
      ((LayoutTurnout*)toObject)->setConnectB((LayoutTrack*)fromObject,fromPointType);
      break;
  case TURNOUT_C:
      ((LayoutTurnout*)toObject)->setConnectC((LayoutTrack*)fromObject,fromPointType);
      break;
  case TURNOUT_D:
      ((LayoutTurnout*)toObject)->setConnectD((LayoutTrack*)fromObject,fromPointType);
      break;
  case LEVEL_XING_A:
      ((LevelXing*)toObject)->setConnectA((LayoutTrack*)fromObject,fromPointType);
      break;
  case LEVEL_XING_B:
      ((LevelXing*)toObject)->setConnectB((LayoutTrack*)fromObject,fromPointType);
      break;
  case LEVEL_XING_C:
      ((LevelXing*)toObject)->setConnectC((LayoutTrack*)fromObject,fromPointType);
      break;
  case LEVEL_XING_D:
      ((LevelXing*)toObject)->setConnectD((LayoutTrack*)fromObject,fromPointType);
      break;
  case SLIP_A:
      ((LayoutSlip*)toObject)->setConnectA((LayoutTrack*)fromObject,fromPointType);
      break;
  case SLIP_B:
      ((LayoutSlip*)toObject)->setConnectB((LayoutTrack*)fromObject,fromPointType);
      break;
  case SLIP_C:
      ((LayoutSlip*)toObject)->setConnectC((LayoutTrack*)fromObject,fromPointType);
      break;
  case SLIP_D:
      ((LayoutSlip*)toObject)->setConnectD((LayoutTrack*)fromObject,fromPointType);
      break;
  case TRACK:
      // should never happen, Track Segment links are set in ctor
      log->error("Illegal request to set a Track Segment link");
      break;
  default:
      if ( (toPointType>=TURNTABLE_RAY_OFFSET) && (fromPointType==TRACK) )
      {
       ((LayoutTurntable*)toObject)->setRayConnect((TrackSegment*)fromObject,
                               toPointType-TURNTABLE_RAY_OFFSET);
      }
   break;
  }
}
/**
* Validates that the supplied occupancy sensor name corresponds to an existing sensor
*   and is unique among all blocks.  If valid, returns true and sets the block sensor
*   name in the block.  Else returns false, and does nothing to the block.
*/
/*public*/ bool LayoutEditor::validateSensor(QString sensorName, LayoutBlock* blk, Component* openFrame)
{
 // check if anything entered
 if (sensorName.length()<1)
 {
  // no sensor entered
  return false;
 }
 // get a validated sensor corresponding to this name and assigned to block
 Sensor* s = blk->validateSensor(sensorName,openFrame);
 if (s==nullptr)
 {
  // There is no sensor corresponding to this name
  return false;
 }
 return true;
}
///*public*/ LevelXing* LayoutEditor::findLevelXingByName(QString name)
// {
//  if (name.length()<=0) return nullptr;
//  for (int i = 0; i<xingList->size(); i++)
//  {
//   LevelXing* x = xingList->at(i);
//   if (x->getID()==(name))
//   {
//    return x;
//   }
//  }
//  return nullptr;
//}
///*public*/ LayoutSlip* LayoutEditor::findLayoutSlipByName(QString name)
//{
// if (name.length()<=0) return nullptr;
// for (int i = 0; i<slipList->size(); i++)
// {
//  LayoutSlip* x = slipList->at(i);
//  if (x->getName()==(name))
//  {
//   return x;
//  }
// }
// return nullptr;
//}
/**
 * @deprecated As of 3.9.2, ... use getFinder().find...
 */
////@Deprecated
///*public*/ LayoutTurntable* LayoutEditor::findLayoutTurntableByName(QString name) {
//    return finder->findLayoutTurntableByName(name);
//}

///*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByName(QString name)
//{
// if (name.length()<=0) return nullptr;
// for (int i = 0; i<turnoutList->size(); i++)
// {
//  LayoutTurnout* t = turnoutList->at(i);
//  if (t->getName()==(name))
//  {
//   return t;
//  }
// }
// return nullptr;
//}

///*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByTurnoutName(QString name)
//{
// if (name.length()<=0) return nullptr;
// for (int i = 0; i<turnoutList->size(); i++)
// {
//  LayoutTurnout* t = turnoutList->at(i);
//  if (t->getTurnoutName()==(name))
//  {
//   return t;
//  }
// }
// return nullptr;
//}
/*public*/ QList <Positionable*> LayoutEditor::getContents()
{
 return _contents->toList();
}
// accessor routines for turnout size parameters
/*public*/ void LayoutEditor::setTurnoutBX(double bx) {
  turnoutBX = bx;
  setDirty(true);
}
/*public*/ double LayoutEditor::getTurnoutBX() {return turnoutBX;}
/*public*/ void LayoutEditor::setTurnoutCX(double cx) {
  turnoutCX = cx;
  setDirty(true);
}
/*public*/ double LayoutEditor::getTurnoutCX() {return turnoutCX;}
/*public*/ void LayoutEditor::setTurnoutWid(double wid) {
  turnoutWid = wid;
  setDirty(true);
}
/*public*/ double LayoutEditor::getTurnoutWid() {return turnoutWid;}
/*public*/ void LayoutEditor::setXOverLong(double lg) {
  xOverLong = lg;
  setDirty(true);
}
/*public*/ double LayoutEditor::getXOverLong() {return xOverLong;}
/*public*/ void LayoutEditor::setXOverHWid(double hwid) {
  xOverHWid =  hwid;
  setDirty(true);
}
/*public*/ double LayoutEditor::getXOverHWid() {return xOverHWid;}
/*public*/ void LayoutEditor::setXOverShort(double sh) {
  xOverShort =  sh;
  setDirty(true);
}
/*public*/ double LayoutEditor::getXOverShort() {return xOverShort;}
// reset turnout sizes to program defaults
/*private*/ void LayoutEditor::resetTurnoutSize() {
  turnoutBX = turnoutBXDefault;
  turnoutCX = turnoutCXDefault;
  turnoutWid = turnoutWidDefault;
  xOverLong = xOverLongDefault;
  xOverHWid = xOverHWidDefault;
  xOverShort = xOverShortDefault;
  setDirty(true);
}

/*public*/ double LayoutEditor::getXScale() {return xScale;}

/*public*/ double LayoutEditor::getYScale() {return yScale;}

/*public*/ QColor LayoutEditor::getDefaultBackgroundColor() {
    return defaultBackgroundColor;
}

/*public*/ QString LayoutEditor::getDefaultTrackColor() {
    return ColorUtil::colorToColorName(defaultTrackColor);
}

/*public*/ QString LayoutEditor::getDefaultOccupiedTrackColor() {
    return ColorUtil::colorToColorName(defaultOccupiedTrackColor);
}

/*public*/ QString LayoutEditor::getDefaultAlternativeTrackColor() {
    return ColorUtil::colorToColorName(defaultAlternativeTrackColor);
}

/*public*/ QString LayoutEditor::getDefaultTextColor() {
    return ColorUtil::colorToColorName(defaultTextColor);
}

/*public*/ QString LayoutEditor::getTurnoutCircleColor() {
    return ColorUtil::colorToColorName(turnoutCircleColor);
}

/*public*/ int LayoutEditor::getTurnoutCircleSize() {
    return turnoutCircleSize;
}

/**
 * @deprecated since 4.11.2 use {@link #isTurnoutDrawUnselectedLeg()}
 * instead.
 */
//@Deprecated
/*public*/ bool LayoutEditor::getTurnoutDrawUnselectedLeg() {
    return turnoutDrawUnselectedLeg;
}

/*public*/ bool LayoutEditor::isTurnoutDrawUnselectedLeg() {
    return turnoutDrawUnselectedLeg;
}
/**
* Return a layout block with the given name if one exists.
* Registers this LayoutEditor with the layout block.
* This method is designed to be used when a panel is loaded. The calling
*		method must handle whether the use count should be incremented.
*/
/*public*/ LayoutBlock* LayoutEditor::getLayoutBlock(QString blockID)
{
 // check if this Layout Block already exists
//  LayoutBlock* blk = InstanceManager::layoutBlockManagerInstance().getByUserName(blockID);
 LayoutBlock* blk = (LayoutBlock*)layoutBlockManager->getByUserName(blockID);
 if (blk==nullptr)
 {
  log->error("LayoutBlock '"+blockID+"' not found when panel loaded");
  return nullptr;
 }
 blk->addLayoutEditor(this);
 return blk;
}
/*public*/ QObject* LayoutEditor::findObjectByTypeAndName(int type,QString name)
{
 return finder->findObjectByTypeAndName(type, name);
}

/*public*/ LayoutBlock* LayoutEditor::getAffectedBlock(QObject* o, int type) {
  if (o==nullptr)
   return nullptr;
  switch (type) {
      case TURNOUT_A:
          return ((LayoutTurnout*)o)->getLayoutBlock();
      case TURNOUT_B:
          return ((LayoutTurnout*)o)->getLayoutBlockB();
      case TURNOUT_C:
          return ((LayoutTurnout*)o)->getLayoutBlockC();
      case TURNOUT_D:
          return ((LayoutTurnout*)o)->getLayoutBlockD();
      case LEVEL_XING_A:
          return ((LevelXing*)o)->getLayoutBlockAC();
      case LEVEL_XING_B:
          return ((LevelXing*)o)->getLayoutBlockBD();
      case LEVEL_XING_C:
          return ((LevelXing*)o)->getLayoutBlockAC();
      case LEVEL_XING_D:
          return ((LevelXing*)o)->getLayoutBlockBD();
 #if 1
      case SLIP_A:
          return ((LayoutSlip*)o)->getLayoutBlock();
      case SLIP_B:
          return ((LayoutSlip*)o)->getLayoutBlock();
      case SLIP_C:
          return ((LayoutSlip*)o)->getLayoutBlock();
      case SLIP_D:
          return ((LayoutSlip*)o)->getLayoutBlock();
 #endif
      case TRACK:
          return ((TrackSegment*)o)->getLayoutBlock();
  }
  return nullptr;
}

/*static*/ /*protected*/ QPointF LayoutEditor::getCoords(QObject* o, int type)
{
 if (o != nullptr)
 {
  switch (type)
  {
  case POS_POINT:
      return ((PositionablePoint*)o)->getCoords();
  case TURNOUT_A:
      return ((LayoutTurnout*)o)->getCoordsA();
  case TURNOUT_B:
      return ((LayoutTurnout*)o)->getCoordsB();
  case TURNOUT_C:
      return ((LayoutTurnout*)o)->getCoordsC();
  case TURNOUT_D:
      return ((LayoutTurnout*)o)->getCoordsD();
  case LEVEL_XING_A:
      return ((LevelXing*)o)->getCoordsA();
  case LEVEL_XING_B:
      return ((LevelXing*)o)->getCoordsB();
  case LEVEL_XING_C:
      return ((LevelXing*)o)->getCoordsC();
  case LEVEL_XING_D:
      return ((LevelXing*)o)->getCoordsD();
  case SLIP_A:
      return ((LayoutSlip*)o)->getCoordsA();
  case SLIP_B:
      return ((LayoutSlip*)o)->getCoordsB();
  case SLIP_C:
      return ((LayoutSlip*)o)->getCoordsC();
  case SLIP_D:
      return ((LayoutSlip*)o)->getCoordsD();
  default:
      if (type>=TURNTABLE_RAY_OFFSET)
          return ((LayoutTurntable*)o)->getRayCoordsIndexed(type-TURNTABLE_RAY_OFFSET);
    break;
  }
 }
 else
 {
  log->error("nullptr connection point of type "+QString("%1").arg(type));
 }
 return ( QPointF(0.0,0.0));
}

/**
* Return a layout block with the entered name, creating a new one if needed.
*   Note that the entered name becomes the user name of the LayoutBlock, and
*		a system name is automatically created by LayoutBlockManager if needed.
*/
/*public*/ LayoutBlock* LayoutEditor::provideLayoutBlock(QString s)
{
 LayoutBlock* blk;
 if (s.length() < 1)
 {
  if(!autoAssignBlocks)
  {
   // nothing entered
   return nullptr;
  }
  else
  {
   //blk = InstanceManager::layoutBlockManagerInstance().createNewLayoutBlock();
   blk = layoutBlockManager->createNewLayoutBlock();
   if (blk == nullptr)
   {
    log->error("Unable to create a layout block");
    return nullptr;
   }
   // initialize the new block
   blk->initializeLayoutBlock();
   blk->initializeLayoutBlockRouting();
   blk->setBlockTrackColor(defaultTrackColor);
   blk->setBlockOccupiedColor(defaultOccupiedTrackColor);
   blk->setBlockExtraColor(defaultAlternativeTrackColor);
  }
 }
 else
 {
  // check if this Layout Block already exists
  //blk = InstanceManager::layoutBlockManagerInstance().getByUserName(s);
  blk = (LayoutBlock*)layoutBlockManager->getByUserName(s);
  if (blk == nullptr)
  {
   //blk = InstanceManager::layoutBlockManagerInstance().createNewLayoutBlock(nullptr,s);
   blk = layoutBlockManager->createNewLayoutBlock("",s);
   if (blk == nullptr)
   {
    log->error("Failure to create LayoutBlock '"+s+"'.");
    return nullptr;
   }
   else
   {
    // initialize the new block
    blk->initializeLayoutBlock();
    blk->initializeLayoutBlockRouting();
    blk->setBlockTrackColor(defaultTrackColor);
    blk->setBlockOccupiedColor(defaultOccupiedTrackColor);
    blk->setBlockExtraColor(defaultAlternativeTrackColor);
   }
  }
 }
 // set both new and previously existing block
 blk->addLayoutEditor(this);
 setDirty(true);
 blk->incrementUse();
 return blk;
}
/**
* Returns an array list of track segments matching the block name.
*/
/*public*/ QVector<TrackSegment*>* LayoutEditor::findTrackSegmentByBlock(QString name) {
  if (name.length()<=0) return nullptr;
  QVector<TrackSegment*>* ts = new QVector<TrackSegment*>();
  for (TrackSegment* t : getTrackSegments()) {
      if (t->getBlockName()==(name)) {
          ts->append(t);
      }
  }
  return ts;
}

//compute the turnout circle at inPoint (used for drawing)
/*public*/ QGraphicsEllipseItem* LayoutEditor::turnoutCircleAt(QPointF inPoint) {
    return new QGraphicsEllipseItem(inPoint.x() - circleRadius,
                                inPoint.y() - circleRadius, circleDiameter, circleDiameter);
}
//these are convenience methods to return rectangles
//to use when (hit point-in-rect testing
//
//compute the control point rect at inPoint
/*public*/ QRectF LayoutEditor::trackEditControlRectAt(/*@Nonnull*/ QPointF inPoint) {
    return QRectF(inPoint.x() - SIZE,
            inPoint.y() - SIZE, SIZE2, SIZE2);
}

//compute the turnout circle control rect at inPoint
/*public*/ QRectF LayoutEditor::trackControlCircleRectAt(/*@Nonnull*/ QPointF inPoint) {
    return QRectF(inPoint.x() - circleRadius,
            inPoint.y() - circleRadius, circleDiameter, circleDiameter);
}

//these are convenience methods to return circles used to draw onscreen
//
//compute the control point rect at inPoint; use the turnout circle size
/*public*/ QGraphicsEllipseItem* LayoutEditor::trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint) {
    return trackControlCircleAt(inPoint);
}

//compute the turnout circle at inPoint (used for drawing)
/*public*/ QGraphicsEllipseItem* LayoutEditor::trackControlCircleAt(/*@Nonnull */QPointF inPoint) {
    return new QGraphicsEllipseItem(inPoint.x() - circleRadius,
            inPoint.y() - circleRadius, circleDiameter, circleDiameter);
}

/**
*  Special internal class to allow drawing of layout to a JLayeredPane
*  This is the 'target' pane where the layout is displayed
*/
/*protected*/ void LayoutEditor::paintTargetPanel(EditScene* g2)
{
#if 0 //old draw routines
  //Graphics2D g2 = (Graphics2D)g;
  //g2->clear();
  //drawPositionableLabelBorder(g2);
  // Optional antialising, to eliminate (reduce) staircase on diagonal lines
  if(antialiasingOn) /*g2.setRenderingHints(antialiasing);*/
   editPanel->setRenderHint(QPainter::Antialiasing);
  //if (isEditable() && drawGrid)
  drawPanelGrid(g2);
  drawLabelImages(g2);
//  g2.setColor(defaultTrackColor);
  main = false;
//  g2.setStroke(new BasicStroke(sideTrackWidth,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
  drawHiddenTrack(g2);
  drawDashedTrack(g2,false); // side track
  drawDashedTrack(g2,true); // mainline
  drawSolidTrack(g2,false);
  drawSolidTrack(g2,true);
  drawTurnouts(g2);
  drawXings(g2);
  drawSlips(g2);
  drawTurntables(g2);
  drawTrackInProgress(g2);
//  g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
  drawPoints(g2);
  if (isEditable())
  {
   drawTurnoutRects(g2);
   drawXingRects(g2);
   drawSlipRects(g2);
   drawTrackOvals(g2);
   drawSelectionRect(g2);
   drawTurntableRects(g2);
   drawMemoryRects(g2);
   drawTrackCircleCentre(g2);
   drawTurnoutCircles(g2);
   highLightSelection(g2);
  }
  else if (turnoutCirclesWithoutEditMode)
  {
   drawTurnoutCircles(g2);
   drawSlipCircles(g2);
  }
#else // new draw routines
 draw(editScene);
#endif
}

//
// this is called by the layoutEditorComponent
//
/*protected*/ void LayoutEditor::draw(EditScene* g2) {
  if(isDrawing) return;
  isDrawing = true;
    //drawPositionableLabelBorder(g2);
    //Optional antialising, to eliminate (reduce) staircase on diagonal lines
    //if (antialiasingOn) {
        editPanel->setRenderHint(QPainter::Antialiasing, antialiasingOn);
    //}
#if 1
    // remove existing items from scene
    for(LayoutTrack* layoutTrack : *layoutTrackList)
    {
     layoutTrack->invalidate(g2);
    }
    QList<QGraphicsItem*> items = g2->items();
    foreach(QGraphicsItem* item, items)
    {
     if(item->zValue() == Editor::HANDLES+1)
     {
      g2->removeItem(item);
      delete item;
     }
    }

#endif
    // things that only get drawn in edit mode
    if (isEditable())
    {
     if (getDrawGrid())
     {
      drawPanelGrid(g2);
     }
     drawLayoutTracksHidden(g2);
    }

    drawTrackSegmentsDashed(g2);
    drawLayoutTracksBallast(g2);
    drawLayoutTracksTies(g2);
    drawLayoutTracksRails(g2);
    drawLayoutTracksBlockLines(g2);

    QPen stroke = drawingStroke;
    drawPositionablePoints(g2, false);
    drawPositionablePoints(g2, true);

    drawDecorations(g2);

    // things that only get drawn in edit mode
    if (isEditable()) {
        drawLayoutTrackEditControls(g2);

        drawMemoryRects(g2);
        drawBlockContentsRects(g2);

        if (allControlling()) {
            drawTurnoutControls(g2);
        }
        drawSelectionRect(g2);
        highLightSelection(g2);

        drawTrackSegmentInProgress(g2);
    } else if (turnoutCirclesWithoutEditMode) {
        if (allControlling()) {
            drawTurnoutControls(g2);
        }
    }
    isDrawing = false;
}   // draw

//
//  draw hidden layout tracks
//
/*private*/ void LayoutEditor::drawLayoutTracksHidden(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();
//    Stroke stroke = new BasicStroke(1.F);
    QPen stroke = QPen(ltdo->getSideRailColor(),1.0, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QVector<qreal> dashArray = QVector<qreal>() << 6.0 << 4.0;
//            BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//            new float[]{6.F, 4.F}, 0);

    QPen dashedStroke = QPen(ltdo->getMainRailColor(), 1.0, Qt::DashLine,Qt::RoundCap, Qt::RoundJoin);
    dashedStroke.setDashOffset(10.);
    dashedStroke.setDashPattern(dashArray);

    //setup for drawing hidden sideline rails
//    g2.setColor(ltdo->getSideRailColor());
    stroke.setColor(ltdo->getSideRailColor());
//    g2.setStroke(stroke);
    drawingStroke = stroke;
    bool main = false, block = false, hidden = true, dashed = false;
    draw1(g2, main, block, hidden, dashed,LayoutTrack::track);
    //g2.setStroke(dashedStroke);
    dashedStroke.setColor(ltdo->getSideRailColor());
    drawingStroke = dashedStroke;
    draw1(g2, main, block, hidden, dashed = true,LayoutTrack::track);

    //setup for drawing mainline rails
    main = true;
    //g2.setColor(ltdo->getMainRailColor());
    stroke.setColor(ltdo->getMainRailColor());
    //g2.setStroke(stroke);
    drawingStroke = stroke;
    draw1(g2, main, block, hidden, dashed = false, LayoutTrack::track);
    //g2.setStroke(dashedStroke);
    dashedStroke.setColor(ltdo->getMainRailColor());
    drawingStroke = dashedStroke;
    dashed = true;
    draw1(g2, main, block, hidden, dashed, LayoutTrack::track);
}

//
//  draw dashed track segments
//
/*private*/ void LayoutEditor::drawTrackSegmentsDashed(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();
    bool main = false, block = false, hidden = false, dashed = true;

    if (ltdo->getSideRailCount() > 0)
    {
        //setup for drawing dashed sideline rails
        int railWidth = ltdo->getSideRailWidth();
        //float[] dashArray = new float[]{6.F + railWidth, 4.F + railWidth};
        QVector<qreal> dashArray = QVector<qreal>() << 6.0 + railWidth << 4.0 + railWidth;
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
//        g2.setColor(ltdo->getSideRailColor());
        QPen stroke = QPen(ltdo->getSideRailColor(), railWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        stroke.setDashPattern(dashArray);
        stroke.setDashOffset(10.0);
        drawingStroke = stroke;
        if ((ltdo->getSideRailCount() & 1) == 1) {
            draw1(g2, main, block, hidden, LayoutTrack::dashed);
        }
        if (ltdo->getSideRailCount() >= 2) {
            float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
            draw2(g2, main, railDisplacement, LayoutTrack::dashed);
        }
    }

    if (ltdo->getMainRailCount() > 0) {
        //setup for drawing dashed mainline rails
        main = true;
        int railWidth = ltdo->getMainRailWidth();
        //float[] dashArray = new float[]{6.F + railWidth, 4.F + railWidth};
        QVector<qreal> dashArray = QVector<qreal>() << 6.0 + railWidth << 4.0 + railWidth;
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
//        g2.setColor(ltdo->getMainRailColor());
        QPen stroke = QPen(ltdo->getMainRailColor(), railWidth,  Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        stroke.setDashPattern(dashArray);
        stroke.setDashOffset(10.0);
        drawingStroke = stroke;
        if ((ltdo->getMainRailCount() & 1) == 1) {
            draw1(g2, main, block, hidden, dashed, LayoutTrack::dashed);
        }
        if (ltdo->getMainRailCount() >= 2) {
            float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
            draw2(g2, main, railDisplacement, LayoutTrack::dashed);
        }
    }
}   // drawTrackSegmentsDashed

//
// draw layout track ballast
//
/*private*/ void LayoutEditor::drawLayoutTracksBallast(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();
    bool main = false, block = false, hidden = false, dashed = false;

    //setup for drawing sideline ballast
    int ballastWidth = ltdo->getSideBallastWidth();
    if (ballastWidth > 0) {
//        g2.setStroke(new BasicStroke(ballastWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(ltdo->getSideBallastColor());
     QPen stroke = QPen(ltdo->getSideBallastColor(), ballastWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     drawingStroke = stroke;
        draw1(g2, main, block, hidden, dashed, LayoutTrack::ballast);
    }

    //setup for drawing mainline ballast
    ballastWidth = ltdo->getMainBallastWidth();
    if (ballastWidth > 0) {
//        g2.setStroke(new BasicStroke(ballastWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(ltdo->getMainBallastColor());
     QPen stroke = QPen(ltdo->getMainBallastColor(), ballastWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     drawingStroke = stroke;
        main = true;
        draw1(g2, main, block, hidden, dashed,LayoutTrack::ballast);
    }
}

//
// draw layout track ties
//
/*private*/ void LayoutEditor::drawLayoutTracksTies(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();

    // setup for drawing sideline ties
    int tieLength = ltdo->getSideTieLength();
    int tieWidth = ltdo->getSideTieWidth();
    int tieGap = ltdo->getSideTieGap();
    if ((tieLength > 0) && (tieWidth > 0) && (tieGap > 0)) {
//        g2.setStroke(new BasicStroke(tieLength,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//                new float[]{tieWidth, tieGap}, 0));
//        g2.setColor(ltdo->getSideTieColor());
     QPen stroke = QPen(ltdo->getSideTieColor(), tieLength, Qt::DashLine, Qt::FlatCap, Qt::BevelJoin);
     QVector<qreal> dashPattern = QVector<qreal>() << tieWidth << tieGap;
     stroke.setDashPattern(dashPattern);
     stroke.setDashOffset(10.);
     drawingStroke = stroke;
     draw1(g2, false, LayoutTrack::ties);  // main = false
    }

    // setup for drawing mainline ties
    tieLength = ltdo->getMainTieLength();
    tieWidth = ltdo->getMainTieWidth();
    tieGap = ltdo->getMainTieGap();
    if ((tieLength > 0) && (tieWidth > 0) && (tieGap > 0)) {
//        g2.setStroke(new BasicStroke(tieLength,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//                new float[]{tieWidth, tieGap}, 0));
//        g2.setColor(ltdo->getMainTieColor());
     QPen stroke = QPen(ltdo->getMainTieColor(), tieLength, Qt::DashLine, Qt::FlatCap, Qt::BevelJoin);
     QVector<qreal> dashPattern = QVector<qreal>() << tieWidth << tieGap;
     stroke.setDashPattern(dashPattern);
     stroke.setDashOffset(10.);
     drawingStroke = stroke;

        draw1(g2, true, LayoutTrack::ties); // main = true
    }
}

//
// draw layout track rails
//
/*private*/ void LayoutEditor::drawLayoutTracksRails(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();
    int railWidth = ltdo->getSideRailWidth();
    QColor railColor = ltdo->getSideRailColor();

    bool main = false, block = false, hidden = false, dashed = false;

    if (ltdo->getSideRailCount() > 1) {
        //setup for drawing sideline rails
        float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
//        g2.setStroke(new BasicStroke(railWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
        QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        drawingStroke = stroke;
        draw2(g2, main, railDisplacement, LayoutTrack::track);
    }

    if ((ltdo->getSideRailCount() & 1) == 1) {
        //setup for drawing sideline rails
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
     QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     drawingStroke = stroke;
     draw1(g2, main, block, hidden, dashed, LayoutTrack::track);
    }

    main = true;

    railWidth = ltdo->getMainRailWidth();
    railColor = ltdo->getMainRailColor();
    if (ltdo->getMainRailCount() > 1) {
        //setup for drawing mainline rails
        float railDisplacement = railWidth + (ltdo->getMainRailGap() / 2.F);
//        g2.setStroke(new BasicStroke(railWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
        QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        drawingStroke = stroke;
        draw2(g2, main, railDisplacement);
    }
    if ((ltdo->getMainRailCount() & 1) == 1) {
        //setup for drawing mainline rails
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
        dashed = false;
        QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        drawingStroke = stroke;
        draw1(g2, main, block, hidden, dashed, LayoutTrack::track);
    }

}   // drawLayoutTracksRails

//
// draw layout track block lines
//
/*private*/ void LayoutEditor::drawLayoutTracksBlockLines(EditScene* g2) {
    LayoutTrackDrawingOptions* ltdo = getLayoutTrackDrawingOptions();

    //setup for drawing sideline block lines
    int blockLineWidth = ltdo->getSideBlockLineWidth();
    //float[] dashArray = new float[]{6.F + blockLineWidth, 4.F + blockLineWidth};
    QVector<qreal> dashArray = QVector<qreal>() << 6.0 + blockLineWidth << 4.0 + blockLineWidth;

    //Stroke blockLineStroke = null;
    QPen blockLineStroke;
    QPen stroke;
    int dashPercentageX10 = ltdo->getSideBlockLineDashPercentageX10();
    if (dashPercentageX10 > 0)
    {
     //float[] blockLineDashArray = new float[]{
     QVector<qreal> blockLineDashArray = QVector<qreal>() <<
     dashPercentageX10 + blockLineWidth <<
            10.0 - dashPercentageX10 + blockLineWidth;
//        blockLineStroke = new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, blockLineDashArray, 0);
     //g2.setStroke(blockLineStroke);
        blockLineStroke = QPen(defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        blockLineStroke.setDashOffset(10.0);
        blockLineStroke.setDashPattern(blockLineDashArray);
        stroke = blockLineStroke;
    } else {
//        blockLineStroke = new BasicStroke(
//                ltdo->getSideBlockLineWidth(),
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
     blockLineStroke = QPen(defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//        g2.setStroke(new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
     stroke = QPen(defaultTrackColor, ltdo->getSideBlockLineWidth(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
     stroke.setDashPattern(dashArray);
     stroke.setDashOffset(10.0);
     drawingStroke = stroke;
    }

    //note: color is set in layout track's draw1 when isBlock is true
    bool main = false, block = true, hidden = false, dashed = true;
    draw1(g2, main, block, hidden, dashed, LayoutTrack::track);
    //g2.setStroke(blockLineStroke);
    drawingStroke = blockLineStroke;
    draw1(g2, main, block, hidden, dashed = false,LayoutTrack::track);

    //setup for drawing mainline block lines
    blockLineWidth = ltdo->getMainBlockLineWidth();
    //dashArray = new float[]{6.F + blockLineWidth, 4.F + blockLineWidth};
    dashArray = QVector<qreal>() << 6.0 + blockLineWidth << 4.0 + blockLineWidth;
    dashPercentageX10 = ltdo->getMainBlockLineDashPercentageX10();
    if (dashPercentageX10 > 0) {
//        float[] blockLineDashArray = new float[]{
//            dashPercentageX10 + blockLineWidth,
//            10 - dashPercentageX10 + blockLineWidth};
     QVector<qreal> blockLineDashArray = QVector<qreal>() << dashPercentageX10 + blockLineWidth << 10 - dashPercentageX10 + blockLineWidth;
//        blockLineStroke = new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, blockLineDashArray, 0);
     blockLineStroke = QPen(defaultTrackColor, blockLineWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
     blockLineStroke.setDashPattern(blockLineDashArray);
     blockLineStroke.setDashOffset(10.0);
//        g2.setStroke(blockLineStroke);
     drawingStroke = blockLineStroke;
    } else {
//        blockLineStroke = new BasicStroke(
//                ltdo->getMainBlockLineWidth(),
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
     blockLineStroke=QPen(defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        g2.setStroke(new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
     drawingStroke = QPen(defaultTrackColor, ltdo->getMainBlockLineWidth(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
     drawingStroke.setDashOffset(10.0);
    }
    //note: color is set in layout track's draw1 when isBlock is true
    draw1(g2, main = true, block, hidden, dashed = true,LayoutTrack::track);
    //g2.setStroke(blockLineStroke);
    drawingStroke = blockLineStroke;
    dashed = false;
    draw1(g2, main, block, hidden, dashed, LayoutTrack::track);
}

// isDashed defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden, LayoutTrack::ITEMTYPE type) {
    draw1(g2, isMain, isBlock, isHidden, false, type);
}

// isHidden defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock, LayoutTrack::ITEMTYPE type) {
    draw1(g2, isMain, isBlock, false, type);
}

// isBlock defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2, bool isMain, LayoutTrack::ITEMTYPE type) {
    draw1(g2, isMain, false, type);
}

// draw single line (ballast, ties & block lines)
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden,
        bool isDashed, LayoutTrack::ITEMTYPE itemType)
{
 for (LayoutTrack* layoutTrack : *layoutTrackList)
 {
  if (!(qobject_cast<PositionablePoint*>(layoutTrack)))
  {
   if (isHidden == layoutTrack->isHidden())
   {
    if ((qobject_cast<TrackSegment*>(layoutTrack)))
    {
     if (((TrackSegment*) layoutTrack)->isDashed() == isDashed)
     {
      layoutTrack->draw1(g2, isMain, isBlock, itemType);
     }
    }
    else if (!isDashed)
    {
     layoutTrack->draw1(g2, isMain, isBlock, itemType);
    }
   }
  }
 }
}

// draw positionable points
/*private*/ void LayoutEditor::drawPositionablePoints(EditScene* g2, bool isMain)
{
 for (LayoutTrack* layoutTrack : *layoutTrackList)
 {
  if (qobject_cast<PositionablePoint*>(layoutTrack)) {
      layoutTrack->draw1(g2, isMain, false, LayoutTrack::points);
  }
 }
}

// isDashed defaults to false
/*private*/ void LayoutEditor::draw2(EditScene* g2, bool isMain, float railDisplacement) {
    draw2(g2, isMain, railDisplacement, false);
}

// draw parallel lines (rails)
/*private*/ void LayoutEditor::draw2(EditScene* g2, bool isMain,
        float railDisplacement, bool isDashed)
{
 for (LayoutTrack* layoutTrack : *layoutTrackList)
 {
  if ((qobject_cast<TrackSegment*>(layoutTrack)))
  {
   if (((TrackSegment*) layoutTrack)->isDashed() == isDashed) {
       layoutTrack->draw2(g2, isMain, railDisplacement, LayoutTrack::dashed );
   }
  } else if (!isDashed) {
      layoutTrack->draw2(g2, isMain, railDisplacement, LayoutTrack::track );
  }
 }
}

// draw decorations
/*private*/ void LayoutEditor::drawDecorations(EditScene* g2) {
    for (LayoutTrack* tr : *layoutTrackList) {
        tr->drawDecorations(g2);
    }
}

// draw track segment (in progress)
/*private*/ void LayoutEditor::drawTrackSegmentInProgress(EditScene* g2) {
    //check for segment in progress
    if (isEditable() && (beginObject != nullptr) && ui->trackButton->isChecked()) {
//        g2.setColor(defaultTrackColor);
//        g2.setStroke(new BasicStroke(sidelineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
     QPen stroke = QPen(defaultTrackColor, 1, Qt::SolidLine,Qt::FlatCap, Qt::RoundJoin);
        //g2.draw(new Line2D.Double(beginLocation, currentLocation));
     QGraphicsLineItem* item = new QGraphicsLineItem(beginLocation.x(), beginLocation.y(), currentLocation.x(), currentLocation.y());
     item->setPen(stroke);

        // highlight unconnected endpoints of all tracks
        QColor highlightColor = ColorUtil::setAlpha(QColor(Qt::red), 0.25);
        QColor connectColor = ColorUtil::setAlpha(QColor(Qt::green), 0.5);
//        g2.setColor(highlightColor);
//        g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        stroke = QPen(highlightColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

        for (LayoutTrack* lt : *getLayoutTracks()) {
            if (lt != beginObject) {
                if (lt == foundObject) {
                    lt->highlightUnconnected(g2);
//                    g2.setColor(connectColor);
                    drawingStroke.setColor(connectColor);
                    lt->highlightUnconnected(g2, foundPointType);
//                    g2.setColor(highlightColor);
                    drawingStroke.setColor(highlightColor);
                } else {
                    lt->highlightUnconnected(g2);
                }
            }
        }
    }
}

// draw layout track edit controls
/*private*/ void LayoutEditor::drawLayoutTrackEditControls(EditScene* g2) {
    //g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 drawingStroke = stroke;
    for (LayoutTrack* tr : *layoutTrackList) {
        tr->drawEditControls(g2);
    }
}

// draw layout turnout controls
/*private*/ void LayoutEditor::drawTurnoutControls(EditScene* g2) {
//    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//    g2.setColor(turnoutCircleColor);
 QPen stroke = QPen(turnoutCircleColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 drawingStroke = stroke;
    // loop over all turnouts
    bool editable = isEditable();
    for (LayoutTrack* tr : *layoutTrackList) {
        if (qobject_cast<LayoutTurnout*>(tr)) {  //<== this includes LayoutSlips
            LayoutTurnout* lt = (LayoutTurnout*) tr;
            if (editable || !(lt->isHidden() || lt->isDisabled())) {
                lt->drawTurnoutControls(g2);
            }
        } else if (qobject_cast<LayoutTurntable*>(tr)) {
            LayoutTurntable* lt = (LayoutTurntable*) tr;
            if (editable || !lt->isHidden()) {
                lt->drawTurnoutControls(g2);
            }
        }
    }
}

// get selection rectangle
/*private*/ QRectF LayoutEditor::getSelectionRect() {
    double selX = qMin(selectionX, selectionX + selectionWidth);
    double selY = qMin(selectionY, selectionY + selectionHeight);
    QRectF result =QRectF(selX, selY,
            qAbs(selectionWidth), qAbs(selectionHeight));
    return result;
}

// set selection rectangle
/*public*/ void LayoutEditor::setSelectionRect(/*@Nonnull*/ QRectF selectionRect) {
    //selectionRect = selectionRect.createIntersection(Mathutil->zeroToInfinityRectangle2D);
    selectionX = selectionRect.x();
    selectionY = selectionRect.y();
    selectionWidth = selectionRect.width();
    selectionHeight = selectionRect.height();

    // There's already code in the super class (Editor) to draw
    // the selection rect... We just have to set _selectRect
    _selectRect = MathUtil::rectangle2DToRectangle(selectionRect);

    selectionRect = MathUtil::scale(selectionRect, getZoom());
#if 0 // TODO:
    JComponent* targetPanel = getTargetPanel()->views().at(0)->window();
    QRect targetRect = targetPanel->getVisibleRect();
    // this will make it the size of the targetRect
    // (effectively centering it onscreen)
    QRectF selRect2D = MathUtil::inset(selectionRect,
            (selectionRect.width() - targetRect.width()) / 2.0,
            (selectionRect.height() - targetRect.height()) / 2.0);
    // don't let the origin go negative
    selRect2D = selRect2D.createIntersection(MathUtil::zeroToInfinityRectangle2D);
    QRect selRect = MathUtil::rectangle2DToRectangle(selRect2D);
    if (!targetRect.contains(selRect)) {
        targetPanel->scrollRectToVisible(selRect);
    }
#endif
    clearSelectionGroups();
    selectionActive = true;
    createSelectionGroups();
    //redrawPanel(); // createSelectionGroups already calls this
}

/*private*/ void LayoutEditor::drawSelectionRect(EditScene* g2) {
    if (selectionActive && (selectionWidth != 0.0) && (selectionHeight != 0.0)) {
        // The Editor super class draws a dashed red selection rectangle...
        // We're going to also draw a non-dashed yellow selection rectangle...
        // This could be code stripped if the super-class implementation is "good enough"
//        Stroke stroke = g2.getStroke();
//        Color color = g2.getColor();

//        g2.setColor(new Color(204, 207, 88));
//        g2.setStroke(new BasicStroke(3.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
     QPen stroke = QPen(QColor(204, 207, 88), 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);


        //g2.draw(getSelectionRect());    // this sets _selectRect also
     QGraphicsRectItem* r = new QGraphicsRectItem(getSelectionRect());
     r->setPen(stroke);
     g2->addItem(r);

//        g2.setColor(color);
//        g2.setStroke(stroke);
    } else {
        _selectRect = QRectF(); // and clear it to turn it off
    }
}


/*private*/ void LayoutEditor::drawMemoryRects(EditScene* g2) {
//    g2.setColor(defaultTrackColor);
//    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

    for (LEMemoryIcon* l : *memoryLabelList) {
        //g2.draw(new Rectangle2D.Double(l.getX(), l.getY(), l.getSize().width, l.getSize().height));
     QGraphicsRectItem* r = new QGraphicsRectItem(QRectF(l->x(), l->y(), l->getSize().width(), l->getSize().height()));
     r->setPen(stroke);
     r->setPos(((Positionable*)l)->getLocation());
     g2->addItem(r);
    }
}

/*private*/ void LayoutEditor::drawBlockContentsRects(EditScene* g2) {
//    g2.setColor(defaultTrackColor);
//    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

    for (LEBlockContentsIcon* l : *blockContentsLabelList) {
        //g2.draw(new Rectangle2D.Double(l.getX(), l.getY(), l.getSize().width, l.getSize().height));
     QGraphicsRectItem* r = new QGraphicsRectItem(QRectF(l->x(), l->y(), l->getSize().width(), l->getSize().height()));
     r->setPen(stroke);
     r->setPos(((Positionable*)l)->getLocation());
     g2->addItem(r);
    }
}


#if 1
/*private*/ void LayoutEditor::drawPanelGrid(EditScene* g2)
{
  //Dimension dim = getSize();
  if(panelGridGroup != nullptr)
  {
   //Q_ASSERT(panelGridGroup->scene()!=0);
   g2->removeItem(panelGridGroup);
   delete panelGridGroup;
   //g2->destroyItemGroup(panelGridGroup);
  }
  if(!isEditable() || !drawGrid)
   return;
  panelGridGroup = new QGraphicsItemGroup();
  //g2->addItem(panelGridGroup);
  QSizeF dim = g2->sceneRect().size();
  double pix = 10.0;
  double maxX = dim.width();
  double maxY = dim.height();
  QPointF startPt = QPointF(0.0, 10.0);
  QPointF stopPt = QPointF(maxX, 10.0);
 //  BasicStroke narrow = new   BasicStroke(1.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
 //  BasicStroke wide = new BasicStroke(2.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
 //  g2.setColor(QColor::gray);
 //  g2.setStroke(narrow);
 QPen narrow = QPen(QColor(Qt::gray),1,  Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
 QPen wide = QPen(QColor(Qt::gray),2,  Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

 // draw horizontal lines
 while (pix<maxY)
 {
  startPt= QPointF(0,pix);
  stopPt = QPointF(maxX,pix);
  if ( (((int)pix) % 100) < 5.0)
  {
//  g2.setStroke(wide);
//  g2.draw(new Line2D.Double(startPt,stopPt));
//  g2.setStroke(narrow);
   //g2->addLine(QLineF(startPt, stopPt),wide);
   QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
   line->setPen(wide);
   panelGridGroup->addToGroup(line);
  }
  else
  {
//  g2.draw(new Line2D.Double(startPt,stopPt));
   //g2->addLine(QLineF(startPt, stopPt),narrow);
   QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
   line->setPen(narrow);
   panelGridGroup->addToGroup(line);
  }
  pix += 10.0;
 }
 // draw vertical lines
 pix = 10.0;
 while (pix<maxX)
 {
  startPt=QPointF(pix,0.0);
  stopPt= QPointF(pix,maxY);
  if ( (((int)pix) % 100) < 5.0)
  {
//  g2.setStroke(wide);
//  g2.draw(new Line2D.Double(startPt,stopPt));
//  g2.setStroke(narrow);
   //g2->addLine(QLineF(startPt, stopPt),wide);
   QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
   line->setPen(wide);
   panelGridGroup->addToGroup(line);
  }
  else
  {
  //g2.draw(new Line2D.Double(startPt,stopPt));
   //g2->addLine(QLineF(startPt, stopPt),narrow);
   QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
   line->setPen(narrow);
   panelGridGroup->addToGroup(line);
  }
  pix += 10.0;
 }
 if(panelGridGroup && panelGridGroup->scene())
  log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
 g2->addItem(panelGridGroup);
}
#endif
#if 0
/*private*/ Stream<LayoutTrack> getLayoutTracksOfClass(Class<? extends LayoutTrack> layoutTrackClass) {
    return layoutTrackList.stream()
            .filter(layoutTrackClass::isInstance)
            .map(layoutTrackClass::cast);
}
#else
/*private*/ QList<LayoutTrack*> LayoutEditor::getLayoutTracksOfClass(QString type)
{
 QList<LayoutTrack*> list = QList<LayoutTrack*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(QString(metaObject()->className()) == type)
   list.append(lt);
 }
 return list;
}
#endif
/*public*/ QList<PositionablePoint*> LayoutEditor::getPositionablePoints() {
    //return getLayoutTracksOfClass("PositionablePoint");
 QList<PositionablePoint*> list = QList<PositionablePoint*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  //if(QString(metaObject()->className()) == "PositionablePoint")
  if(qobject_cast<PositionablePoint*>(lt))
   list.append((PositionablePoint*)lt);
 }
 return list;
//    )
//            .map(PositionablePoint.class::cast)
//            .collect(Collectors.toCollection(ArrayList<PositionablePoint>::new));
}
/*protected*/ void LayoutEditor::setTrackStrokeWidth(bool need)
{
 if (main == need) return;
 main = need;
 // change track stroke width
 if ( main )
 {
  trackWidth = mainlineTrackWidth;
//      g2.setStroke(new BasicStroke(mainlineTrackWidth,BasicStroke.CAP_BUTT,                                                      BasicStroke.JOIN_ROUND));
 }
 else
 {
  trackWidth = sidelineTrackWidth;
//      g2.setStroke(new BasicStroke(sideTrackWidth,BasicStroke.CAP_BUTT,                                                      BasicStroke.JOIN_ROUND));
 }
}

/*protected*/ void LayoutEditor::drawTurnouts(EditScene* g2)
{
 //float trackWidth = sideTrackWidth;
 // loop over all defined turnouts
// for (int i = 0; i<lay->size();i++)
// {
//  LayoutTurnout* t = turnoutList->at(i);
//  t->invalidate(g2);
//  t->drawTurnouts(this, g2);
// }
}

/*private*/ QPointF LayoutEditor::midpoint (QPointF p1,QPointF p2) {
  return  QPointF((p1.x()+p2.x())/2.0,(p1.y()+p2.y())/2.0);
}

/*protected*/ QPointF LayoutEditor::third (QPointF p1,QPointF p2) {
  return  QPointF( p1.x()+((p2.x()-p1.x())/3.0),
                  p1.y()+((p2.y()-p1.y())/3.0) );
}

/*private*/ QPointF LayoutEditor::fourth (QPointF p1,QPointF p2) {
  return  QPointF( p1.x()+((p2.x()-p1.x())/4.0),
                  p1.y()+((p2.y()-p1.y())/4.0) );
}
/*private*/ void LayoutEditor::drawXings(EditScene* g2)
{
 // loop over all defined level crossings
// for (int i = 0; i<xingList->size();i++)
// {
//  LevelXing* x = xingList->at(i);
//  x->invalidate(g2);
//  x->drawXings(this, g2);
// }
}

///*private*/ void LayoutEditor::drawSlips(QGraphicsScene* g2)
//{
// for (int i = 0; i<slipList->size();i++)
// {
//  LayoutSlip* x = slipList->at(i);
//  LayoutBlock* b = x->getLayoutBlock();
//  setTrackStrokeWidth(x->isMainline());
//  QColor mainColour;
//  QColor subColour;
//  if (b!=nullptr)
//  {
//   mainColour = b->getBlockColor();
//   subColour = b->getBlockTrackColor();
//  }
//  else
//  {
//   mainColour = defaultTrackColor;
//   subColour = defaultTrackColor;
//  }
//  if(x->item != nullptr && x->item->scene()!=0)
//  {
//   g2->removeItem(x->item);
//   x->item = nullptr;
//  }
//  if(x->rects != nullptr)
//  {
//   Q_ASSERT(x->rects->scene()!=0);
//   g2->removeItem(x->rects);
//   x->rects = nullptr;
//  }
//  x->item = new QGraphicsItemGroup();

//  //g2.setColor(subColour);

////  g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsC())));
//  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsC())));
//  line1->setPen(QPen(subColour,trackWidth));
//  x->item->addToGroup(line1);

////  g2.draw(new Line2D.Double(x.getCoordsC(),
////          third(x.getCoordsC(),x.getCoordsA())));
//  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(),third(x->getCoordsC(),x->getCoordsA())));
//  line2->setPen(QPen(subColour,trackWidth));
//  x->item->addToGroup(line2);

////      g2.draw(new Line2D.Double(x.getCoordsB(),
////          third(x.getCoordsB(),x.getCoordsD())));
//  QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(),third(x->getCoordsB(),x->getCoordsD())));
//  line3->setPen(QPen(subColour,trackWidth));
//  x->item->addToGroup(line3);

////      g2.draw(new Line2D.Double(x.getCoordsD(),
////          third(x.getCoordsD(),x.getCoordsB())));
//  QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(),third(x->getCoordsD(),x->getCoordsB())));
//  line4->setPen(QPen(subColour,trackWidth));
//  x->item->addToGroup(line4);


//  if(x->getSlipType()==LayoutSlip::DOUBLE_SLIP)
//  {
//   if (x->getSlipState()==LayoutSlip::STATE_AC)
//   {
////          g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsD())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);

////          g2.draw(new Line2D.Double(x.getCoordsD(),
////              third(x.getCoordsD(),x.getCoordsA())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);

////          g2.draw(new Line2D.Double(x.getCoordsB(),
////              third(x.getCoordsB(),x.getCoordsC())));
//    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
//    line3->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line3);

////          g2.draw(new Line2D.Double(x.getCoordsC(),
////              third(x.getCoordsC(),x.getCoordsB())));
//    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
//    line4->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line4);

////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
//    QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
//    line5->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line5);

//   }
//   else if (x->getSlipState()==LayoutSlip::STATE_BD)
//   {
////          g2.draw(new Line2D.Double(x.getCoordsB(),
////              third(x.getCoordsB(),x.getCoordsC())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);

////          g2.draw(new Line2D.Double(x.getCoordsC(),
////              third(x.getCoordsC(),x.getCoordsB())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);


////          g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsD())));
//    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//    line3->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line3);

////          g2.draw(new Line2D.Double(x.getCoordsD(),
////              third(x.getCoordsD(),x.getCoordsA())));
//    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//    line4->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line4);

////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
//    QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
//    line5->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line5);

//   }
//   else if (x->getSlipState()==LayoutSlip::STATE_AD)
//   {
////          g2.draw(new Line2D.Double(x.getCoordsB(),
////              third(x.getCoordsB(),x.getCoordsC())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);

////          g2.draw(new Line2D.Double(x.getCoordsC(),
////              third(x.getCoordsC(),x.getCoordsB())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);

////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));
//    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsD()));
//    line3->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line3);

//   }
//   else if (x->getSlipState()==LayoutSlip::STATE_BC)
//   {
////          g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsD())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);


////          g2.draw(new Line2D.Double(x.getCoordsD(),
////              third(x.getCoordsD(),x.getCoordsA())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);

////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsC()));
//    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsC()));
//    line3->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line3);

//   }
//   else
//   {
////          g2.draw(new Line2D.Double(x.getCoordsB(),
////              third(x.getCoordsB(),x.getCoordsC())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);


////          g2.draw(new Line2D.Double(x.getCoordsC(),
////              third(x.getCoordsC(),x.getCoordsB())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);

////          g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsD())));
//    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//    line3->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line3);

////          g2.draw(new Line2D.Double(x.getCoordsD(),
////              third(x.getCoordsD(),x.getCoordsA())));
//    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//    line4->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line4);
//   }
//  }
//  else
//  {
////      g2.draw(new Line2D.Double(x.getCoordsA(),
////          third(x.getCoordsA(),x.getCoordsD())));
//   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//   line1->setPen(QPen(subColour,trackWidth));
//   x->item->addToGroup(line1);

////      g2.draw(new Line2D.Double(x.getCoordsD(),
////          third(x.getCoordsD(),x.getCoordsA())));
//   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//   line2->setPen(QPen(subColour,trackWidth));
//   x->item->addToGroup(line2);
//   if (x->getSlipState()==LayoutSlip::STATE_AD)
//   {
////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsD()));
//    line1->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line1);

//   }
//   else if (x->getSlipState()==LayoutSlip::STATE_BD)
//   {
////          g2.setColor(mainColour);
////          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
//    line1->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line1);

//    if(x->singleSlipStraightEqual())
//    {
////              g2.setColor(mainColour);
////              g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
//     QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
//       line1->setPen(QPen(mainColour,trackWidth));
//     x->item->addToGroup(line1);

//    }
//   }
//   else if (x->getSlipState()==LayoutSlip::STATE_AC)
//   {
//             //          g2.setColor(mainColour);
//             //          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
//       QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
//    line1->setPen(QPen(mainColour,trackWidth));
//    x->item->addToGroup(line1);

//    if(x->singleSlipStraightEqual())
//    {
////              g2.setColor(mainColour);
////              g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
//     QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
//     line1->setPen(QPen(mainColour,trackWidth));
//     x->item->addToGroup(line1);

//    }
//   }
//   else
//   {
////          g2.draw(new Line2D.Double(x.getCoordsA(),
////              third(x.getCoordsA(),x.getCoordsD())));
//    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
//    line1->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line1);

////          g2.draw(new Line2D.Double(x.getCoordsD(),
////              third(x.getCoordsD(),x.getCoordsA())));
//    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
//    line2->setPen(QPen(subColour,trackWidth));
//    x->item->addToGroup(line2);

//   }
//  }
//  if(x->item && x->item->scene())
//   log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
//  g2->addItem(x->item);
// }
//}

///*private*/ void LayoutEditor::drawTurnoutCircles(EditScene* g2)
//{
  // loop over all defined turnouts
//  for (int i = 0; i<turnoutList->size();i++)
//  {
//   LayoutTurnout* t = turnoutList->at(i);
//   if(!(t->getHidden() && !isEditable()))
//   {
//    t->drawTurnoutCircles(this, g2);
//   }
//  }
//} //drawTurnoutCircles

///*private*/ void LayoutEditor::drawSlipCircles(EditScene* g2)
//{
 //loop over all defined slips

// for (int i = 0; i<slipList->size();i++)
// {
//  LayoutSlip* sl = slipList->at(i);
//  if(!(sl->getHidden() && !isEditable()))
//  {
//   sl->drawSlipCircles(g2);
//  }
// }
//}  //drawSlipCircles

///*private*/ void LayoutEditor::drawTurnoutRects(EditScene* g2)
//{
  // loop over all defined turnouts
//  for (int i = 0; i<turnoutList->size();i++)
//  {
//   LayoutTurnout* t = turnoutList->at(i);
//   t->drawTurnoutRects(this, g2);
//  }
//  for(int i=0; i < slipList->count(); i++)
//  {
//   LayoutSlip* s = slipList->at(i);
//   s->drawTurnoutRects(this, g2);
//  }
//}
#if 0
/*private*/ void LayoutEditor::drawTurntables(EditScene* g2)
{
  // loop over all defined layout turntables
  if (turntableList->size()<=0) return;
  for (int i = 0; i<turntableList->size();i++)
  {
   LayoutTurntable* x = turntableList->at(i);
   if(x->item != nullptr && x->item->scene()!=0)
   {
    g2->removeItem(x->item);
    x->item = nullptr;
   }
   x->item = new QGraphicsItemGroup();

   // draw turntable circle - default track color, side track width
   setTrackStrokeWidth(/*g2,*/false);
   QPointF c = x->getCoordsCenter();
   double r = x->getRadius();
   //g2.setColor(defaultTrackColor);
//   g2.draw(new Ellipse2D.Double (
//       c.x()-r, c.y()-r, r+r, r+r));
   QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(c.x()-r, c.y()-r, r+r, r+r);
   circle->setPen(QPen(defaultTrackColor, sidelineTrackWidth));
   x->item->addToGroup(circle);

   // draw ray tracks
   QColor color;
   for (int j = 0; j<x->getNumberRays(); j++)
   {
    QPointF pt = x->getRayCoordsOrdered(j);
    TrackSegment* t = x->getRayConnectOrdered(j);
    if (t!=nullptr)
    {
     setTrackStrokeWidth(/*g2,*/t->getMainline());
     LayoutBlock* b = t->getLayoutBlock();
     if (b!=nullptr) color = (b->getBlockColor());
     else color = (defaultTrackColor);
    }
    else
    {
//              setTrackStrokeWidth(g2,false);
     color =(defaultTrackColor);
    }
//          g2.draw(new Line2D.Double(new QPointF.Double(
//                  pt.x()-((pt.x()-c.x())*0.2),
//                      pt.y()-((pt.y()-c.y())*0.2)), pt));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(QPointF(pt.x()-((pt.x()-c.x())*0.2),
                                                                                  pt.y()-((pt.y()-c.y())*0.2)), pt));
    line1->setPen(QPen(color,trackWidth));
    x->item->addToGroup(line1);
   }
   if(x->isTurnoutControlled() && x->getPosition()!=-1)
   {
    QPointF pt = x->getRayCoordsIndexed(x->getPosition());
//          g2.draw(new Line2D.Double(new QPointF.Double(
//                  pt.x()-((pt.x()-c.x())*1.8/*2*/),
//                      pt.y()-((pt.y()-c.y())*1.8/**2*/)), pt));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(QPointF( pt.x()-((pt.x()-c.x())*1.8/*2*/),
                                                                            pt.y()-((pt.y()-c.y())*1.8/**2*/)), pt));
    line1->setPen(QPen(color,trackWidth));
    x->item->addToGroup(line1);
   }
   if(x->item && x->item->scene())
    log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
   g2->addItem(x->item);
  }
}
#endif
///*private*/ void LayoutEditor::drawXingRects(EditScene* g2)
//{
 // loop over all defined level crossings
// for (int i = 0; i<xingList->size();i++)
// {
//  LevelXing* x = xingList->at(i);
//  x->drawXingRects(this, g2);
// }
//}
#if 0// see drawSlips.
///*private*/ void LayoutEditor::drawSlipRects(EditScene* /*g2*/)
//{
  // loop over all defined level crossings
//  for (int i = 0; i<slipList->size();i++)
//  {
//   QColor color;
//      LayoutSlip* x = slipList->at(i);
//      QPointF pt = x->getCoordsCenter();
////      g2.setColor(defaultTrackColor);
////      g2.draw(new Ellipse2D.Double (
////                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
//      QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2);
//      circle->setPen(QPen(defaultTrackColor,1));
//      x->item->addToGroup(circle);
//      pt = x->getCoordsA();
//      if (x->getConnectA()==nullptr) {
//          //g2.setColor(QColor::red);
//       color = Qt::red;
//      }
//      else {
//          //g2.setColor(QColor::green);
//       color = Qt::green;
//      }
////      g2.draw(new QRectF.Double (
////                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
//      QGraphicsRectItem* rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
//      rect->setPen(QPen(color, 1));
//      x->item->addToGroup(rect);
//      pt = x->getCoordsB();
//      if (x->getConnectB()==nullptr) {
//          //g2.setColor(QColor::red);
//       color = Qt::red;
//      }
//      else {
//          //g2.setColor(QColor::green);
//       color = Qt::green;
//      }
////      g2.draw(new QRectF.Double (
////                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
//      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
//      rect->setPen(QPen(color, 1));
//      x->item->addToGroup(rect);
//      pt = x->getCoordsC();
//      if (x->getConnectC()==nullptr) {
//          //g2.setColor(QColor::red);
//       color = Qt::red;
//      }
//      else {
//          //g2.setColor(QColor::green);
//       color = Qt::green;
//      }
////      g2.draw(new QRectF.Double (
////                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
//      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
//      rect->setPen(QPen(color, 1));
//      x->item->addToGroup(rect);
//      pt = x->getCoordsD();
//      if (x->getConnectD()==nullptr) {
//          //g2.setColor(QColor::red);
//       color = Qt::red;
//      }
//      else {
//          //g2.setColor(QColor::green);
//       color = Qt::green;
//      }
////      g2.draw(new QRectF.Double (
////                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
//      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
//      rect->setPen(QPen(color, 1));
//      x->item->addToGroup(rect);
//  }
//}
/*private*/ void LayoutEditor::drawTurntableRects(EditScene* /*g2*/)
{
  // loop over all defined turntables
  for (int i = 0; i<turntableList->size();i++) {
      LayoutTurntable* x = turntableList->at(i);
      QPointF pt = x->getCoordsCenter();
      //g2.setColor(defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
      QGraphicsEllipseItem* line1 = new QGraphicsEllipseItem(pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2);
      line1->setPen(QPen(defaultTrackColor,1));
      QColor color;
      x->item->addToGroup(line1);
      for (int j = 0; j<x->getNumberRays();j++)
      {
          pt = x->getRayCoordsOrdered(j);
          if (x->getRayConnectOrdered(j)==nullptr) {
              //g2.setColor(QColor::red);
           color = Qt::red;
          }
          else {
              //g2.setColor(QColor::green);
           color = Qt::green;
          }
//          g2.draw(new QRectF.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
          QGraphicsRectItem* rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
          rect->setPen(QPen(color, trackWidth));
          x->item->addToGroup(rect);
      }
  }
}

/*private*/ void LayoutEditor::drawHiddenTrack(EditScene* g2)
{
 for (int i = 0; i<layoutTrackList->size();i++)
 {
  LayoutTrack* t =layoutTrackList->at(i);
  if (isEditable() && t->getHidden())
  {
   //((TrackSegment*)t)->invalidate(g2);
   ((TrackSegment*)t)->drawHiddenTrack(this, g2);
  }
 }
}
#endif
void LayoutEditor::drawLabelImages(EditScene* /*g2*/)
{
 QColor color;
 for (int i = 0; i<_contents->size();i++)
 {
  PositionableLabel* l = (PositionableLabel*)_contents->at(i);
  //addToTarget((Positionable*)l);
  l->updateScene();
 }
// for(int i=0; i < markerImage->size(); i++)
// {
//   LocoIcon* l = markerImage->at(i) ;
//   if(l->item != nullptr)
//   {
//    g2->removeItem(l->item);
//    l->item = nullptr;
//   }
//   QPixmap pixmap = QPixmap::fromImage(QImage((l->getIcon()->getOriginalImage())));
//   l->item = g2->addPixmap(pixmap);
//   l->item->setPos(l->getX(), l->getY());
//   if(pixmap.isNull())
//    qDebug() << "No pixmap";
//   if(l->getDegrees() != 0)
//    //l->item->rotate(l->getDegrees());
//    l->item->setRotation(l->item->rotation()+ l->getDegrees());
// }
}

/*private*/ void LayoutEditor::amendSelectionGroup(Positionable* p)
{
 if (_positionableSelection==nullptr)
 {
   _positionableSelection = new QVector <Positionable*>();
 }
 bool removed = false;
 for(int i=0; i<_positionableSelection->size();i++)
 {
  if (_positionableSelection->at(i)==p)
  {
   _positionableSelection->remove(i);
   removed = true;
   break;
  }
 }
 if(!removed)
  _positionableSelection->append(p);
 if (_positionableSelection->isEmpty())
 {
  _positionableSelection=nullptr;
 }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(LayoutTurnout* p){
  if (_turnoutSelection==nullptr){
      _turnoutSelection = new QVector <LayoutTurnout*>();
  }
  bool removed = false;
  for(int i=0; i<_turnoutSelection->size();i++){
      if (_turnoutSelection->at(i)==p){
          _turnoutSelection->remove(i);
          removed = true;
          break;
      }
  }
  if(!removed)
      _turnoutSelection->append(p);
  if (_turnoutSelection->size()==0){
      _turnoutSelection=nullptr;
  }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(PositionablePoint* p){
  if (_pointSelection==nullptr){
      _pointSelection = new QVector <PositionablePoint*>();
  }
  bool removed = false;
  for(int i=0; i<_pointSelection->size();i++){
      if (_pointSelection->at(i)==p){
          _pointSelection->remove(i);
          removed = true;
          break;
      }
  }
  if(!removed)
      _pointSelection->append(p);
  if (_pointSelection->size()==0){
      _pointSelection=nullptr;
  }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(LevelXing* p){
  if (_xingSelection==nullptr){
      _xingSelection = new QVector <LevelXing*>();
  }
  bool removed = false;
  for(int i=0; i<_xingSelection->size();i++){
      if (_xingSelection->at(i)==p){
          _xingSelection->remove(i);
          removed = true;
          break;
      }
  }
  if(!removed)
      _xingSelection->append(p);
  if (_xingSelection->size()==0){
      _xingSelection=nullptr;
  }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(LayoutTrack* p){
 if (_layoutTrackSelection.contains(p)) {
     _layoutTrackSelection.removeOne(p);
 } else {
     _layoutTrackSelection.append(p);
 }
 redrawPanel();
  paintTargetPanel(editScene);
}

/************************ Options setup **********************/
/**
*  Control whether target panel items are editable.
*  Does this by invoke the {@link Positionable#setEditable(bool)} function of
*  each item on the target panel. This also controls the relevant pop-up menu items
*  (which are the primary way that items are edited).
* @param state true for editable.
*/
/*public*/ void LayoutEditor::setAllEditable(bool state)
{
  //_editable = state;
 Editor::setAllEditable(state);
  for (int i = 0; i<_contents->size(); i++)
  {
   _contents->at(i)->setEditable(state);
  }
  if (!_editable)
  {
//      _highlightcomponent = nullptr;
   _selectionGroup =new  QList<Positionable*>();
  }
}
/**
*  Control whether target panel items are controlling layout items.
*  Does this by invoke the {@link Positionable#setControlling} function of
*  each item on the target panel. This also controls the relevant pop-up menu items.
* @param state true for controlling.
*/
/*public*/ void LayoutEditor::setTurnoutAnimation(bool state) {
  if (ui->actionAllow_turnout_animation->isChecked()!=state) ui->actionAllow_turnout_animation->setChecked(state);
  animatingLayout = state;
  //repaint();
  paintTargetPanel(editScene);
}

/*public*/ bool LayoutEditor::isAnimating() {
  return animatingLayout;
}
/*public*/ int LayoutEditor::getLayoutWidth() {return panelWidth;}
/*public*/ int LayoutEditor::getLayoutHeight() {return panelHeight;}
/*public*/ int LayoutEditor::getWindowWidth()
{
 windowWidth = this->size().width();
 windowHeight= this->size().height();
 return windowWidth;
}
/*public*/ int LayoutEditor::getWindowHeight()
{
 windowWidth = this->size().width();
 windowHeight= this->size().height();
 return windowHeight;
}
/*public*/ int LayoutEditor::getUpperLeftX() {return upperLeftX;}
/*public*/ int LayoutEditor::getUpperLeftY() {return upperLeftY;}
/*public*/ bool LayoutEditor::getScroll() {
  // deprecated but kept to allow opening files
  // on version 2.5.1 and earlier
  if (_scrollState==SCROLL_NONE) return false;
  else return true;
}
/*public*/ /*const*/ int LayoutEditor::getAnchorX() {
  return _anchorX;
}

/*public*/ /*const*/ int LayoutEditor::getAnchorY()
{
  return _anchorY;
}

///*public*/ bool LayoutEditor::allPositionable() {
//  return _positionable;
//}
/*public*/ bool LayoutEditor::allControlling()
{
  return _controlLayout;
}
void LayoutEditor::on_actionShow_grid_in_edit_mode_toggled(bool bChecked)
{
 drawGrid = bChecked;
 ui->actionShow_grid_in_edit_mode->setChecked(bChecked);
 drawPanelGrid(editScene);
 paintTargetPanel(editScene);
}
void LayoutEditor::on_actionEdit_mode_toggled(bool bState)
{
 bIsEditable = bState;
 ui->actionEdit_mode->setChecked(bState);
 drawPanelGrid(editScene);
 paintTargetPanel(editScene);
}

double LayoutEditor::toDegrees(double radians)
{
 return (radians/M_PI)*180;
}
double LayoutEditor::toRadians(double degrees)
{
 return (degrees/180)*M_PI;
}
#if 0
/*private*/ void LayoutEditor::checkPopUp(QGraphicsSceneMouseEvent* event)
{
 if (checkSelect(dLoc, false))
 {
  // show popup menu
  switch (foundPointType)
  {
  case POS_POINT:
      ((PositionablePoint*)foundObject)->showPopUp(event);
      break;
  case LAYOUT_POS_LABEL:
   // TODO:
      break;
  case TURNOUT_CENTER:
      ((LayoutTurnout*)foundObject)->showPopUp(event, isEditable());
      break;
  case LEVEL_XING_CENTER:
     ((LevelXing*)foundObject)->showPopUp(event, isEditable());
      break;
  case SLIP_CENTER:
      ((LayoutSlip*)foundObject)->showPopUp(event, isEditable());
      break;
  case TURNTABLE_CENTER:
      ((LayoutTurntable*)foundObject)->showPopUp(event);
      break;
  default: break;
  }
  if(foundPointType>=TURNTABLE_RAY_OFFSET)
  {
   LayoutTurntable* t = (LayoutTurntable*)foundObject;
   if(t->isTurnoutControlled())
   {
     ((LayoutTurntable*)foundObject)->showRayPopUp(event, foundPointType-TURNTABLE_RAY_OFFSET);
   }
  }
 }
 else
 {
  TrackSegment* tr = checkTrackSegments(dLoc);
  if (tr!=nullptr)
  {
   tr->showPopUp(event);
  }
  else
  {
   SensorIcon* s = checkSensorIcons(dLoc);
   if (s!=nullptr)
   {
    showPopUp((Positionable*)s, event);
   }
   else
   {
    LocoIcon* lo = checkMarkers(dLoc);
    if (lo!=nullptr)
    {
     showPopUp((Positionable*)lo, event);
    }
    else
    {
     SignalHeadIcon* sh = checkSignalHeadIcons(dLoc);
     if (sh!=nullptr)
     {
      showPopUp((Positionable*)sh, event);
     }
     else
     {
      AnalogClock2Display* c = checkClocks(dLoc);
      if (c!=nullptr)
      {
       showPopUp((Positionable*)c, event);
      }
      else
      {
       MultiSensorIcon* ms = checkMultiSensors(dLoc);
       if (ms!=nullptr)
       {
        showPopUp((Positionable*)ms, event);
       }
       else
       {
        PositionableLabel* lb = checkLabelImages(dLoc);
        if (lb!=nullptr)
        {
         showPopUp((Positionable*)lb, event);
        }
        else
        {
         PositionableLabel* b = checkBackgrounds(dLoc);
         if (b!=nullptr)
         {
          showPopUp((Positionable*)b, event);
         }
         else
         {
          SignalMastIcon* sm = checkSignalMastIcons(dLoc);
          if (sm!=nullptr)
          {
            showPopUp((Positionable*)sm, event);
          }
          else
          {
           MemoryIcon* mi = checkMemoryMarkerIcons(dLoc);
           if(mi != nullptr)
            showPopUp((Positionable*)mi, event);
          }
         }
        }
       }
      }
     }
    }
   }
  }
 }
}
#endif
#if 0
/**
* Select the menu items to display for the Positionable's popup
*/
/*protected*/ void LayoutEditor::showPopUp(Positionable* p, QGraphicsSceneMouseEvent* /*event*/)
{
// if (!((JComponent)p).isVisible())
// {
//      return;     // component must be showing on the screen to determine its location
// }
 QMenu* popup = new QMenu();
 PositionableLabel* positionableLabel = static_cast<PositionableLabel*>(p);
 Q_ASSERT(positionableLabel != nullptr);
// SensorIcon* pSensor = qobject_cast<SensorIcon*>(p);
// LocoIcon* locoIcon = qobject_cast<LocoIcon*>(p);
// MemoryIcon* memoryIcon = qobject_cast<MemoryIcon*>(p);
// SignalHeadIcon* signalHeadIcon = qobject_cast<SignalHeadIcon*>(p);
// SignalMastIcon* signalMastIcon = qobject_cast<SignalMastIcon*>(p);
// ReporterIcon* rp = qobject_cast<ReporterIcon*>(p);
 if (positionableLabel->isEditable())
 {
  if(showAlignPopup())
  {
   setShowAlignmentMenu(popup);
   QAction* actRemove = new QAction(tr("Remove"),this);
   connect(actRemove, SIGNAL(triggered()), this, SLOT(deleteSelectedItems()));
   popup->addAction(actRemove);
  }
  else
  {
   if(positionableLabel->doViemMenu())
   {
    popup->addAction(new QAction(positionableLabel->getNameString(),this));
    if (positionableLabel->isPositionable())
    {
     setShowCoordinatesMenu(p, popup);
    }
    setDisplayLevelMenu(p, popup);
    setPositionableMenu(p, popup);
   }
   bool popupSet =false;
   popupSet |= ((PositionableLabel*)p)->setRotateOrthogonalMenu(popup);
   popupSet |= ((PositionableLabel*)p)->setRotateMenu(popup);

   if (popupSet)
   {
    popup->addSeparator();
    popupSet = false;
   }
   popupSet = positionableLabel->setEditIconMenu(popup);
   popupSet = positionableLabel->setTextEditMenu(popup);

   PositionablePopupUtil* util = ((PositionableLabel*)p)->getPopupUtility();
   if (util!=nullptr)
   {
    util->setFixedTextMenu(popup);
    util->setTextMarginMenu(popup);
    util->setTextBorderMenu(popup);
    util->setTextFontMenu(popup);
    util->setBackgroundMenu(popup);
    util->setTextJustificationMenu(popup);
    util->setTextOrientationMenu(popup);
    popup->addSeparator();
    util->propertyUtil(popup);
    util->setAdditionalEditPopUpMenu(popup);
    popupSet = true;
   }
   if (popupSet)
   {
    popup->addSeparator();
    popupSet = false;
   }
   ((PositionableLabel*)p)->setDisableControlMenu(popup);
   setShowAlignmentMenu(popup);
   positionableLabel->showPopUp(popup);
    //popup->exec(QCursor::pos());
   setShowToolTipMenu(p, popup);

   setRemoveMenu(p, popup);
   if (positionableLabel->doViemMenu())
   {
    setHiddenMenu(p, popup);
   }
  }
 }
 else
 { // icon is not editable
  positionableLabel->showPopUp(popup);
  PositionablePopupUtil* util = positionableLabel->getPopupUtility();
  if(util!=nullptr)
   util->setAdditionalViewPopUpMenu(popup);
 }
#if 0 // TODO:
 popup->show((Component)p, p.getWidth()/2+(int)((getPaintScale()-1.0)*p.getX()),
              p.getHeight()/2+(int)((getPaintScale()-1.0)*p.getY()));
  /*popup.show((Component)p, event.getX(), event.getY());*/
#endif
//  popup->exec(QPoint(p->getWidth()/2+(int)((getPaintScale()-1.0)*p->getX()),                        p->getHeight()/2+(int)((getPaintScale()-1.0)*p->getY())));
 popup->exec(QCursor::pos());
}

#endif
#if 0
/*private*/ TrackSegment* LayoutEditor::checkTrackSegments(QPointF loc)
{
 // check Track Segments, if any
 for (TrackSegment* tr : getTrackSegments()) {

  QObject* o = tr->getConnect1();
  int type = tr->getType1();
  // get coordinates of first end point
  QPointF pt1 = getEndCoords(o,type);
  o = tr->getConnect2();
  type = tr->getType2();
  // get coordinates of second end point
  QPointF pt2 = getEndCoords(o,type);
  // construct a detection rectangle
  double cX = (pt1.x() + pt2.x())/2.0;
  double cY = (pt1.y() + pt2.y())/2.0;
  QRectF r = QRectF(cX - SIZE2,cY - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
  // Test this detection rectangle
  if (r.contains(loc))
  {
   // mouse was pressed in detection rectangle
   return tr;
  }
 }
 return nullptr;
}
#endif



/*public*/ QList<LayoutSlip*> LayoutEditor::getLayoutSlips() {
//    return getLayoutTracksOfClass("LayoutSlip");
 QList<LayoutSlip*> list = QList<LayoutSlip*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<LayoutSlip*>(lt))
   list.append((LayoutSlip*)lt);
 }
 return list;
}

/*public*/ QList<TrackSegment*> LayoutEditor::getTrackSegments() {
//    return getLayoutTracksOfClass("TrackSegment");
 QList<TrackSegment*> list = QList<TrackSegment*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<TrackSegment*>(lt))
   list.append((TrackSegment*)lt);
 }
 return list;
}

/*public*/ QList<LayoutTurnout*> LayoutEditor::getLayoutTurnouts() {
//    return layoutTrackList.stream() // next line excludes LayoutSlips
//            .filter((o) -> (!(o instanceof LayoutSlip) && (o instanceof LayoutTurnout)))
//            .map(LayoutTurnout.class::cast).map(LayoutTurnout.class::cast)
//            .collect(Collectors.toCollection(ArrayList<LayoutTurnout>::new));
 QList<LayoutTurnout*> list = QList<LayoutTurnout*>();
 foreach (LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<LayoutSlip*>(lt))
   continue;
  if(qobject_cast<LayoutTurnout*>(lt))
  list.append((LayoutTurnout*)lt);
 }
 return list;
}

/*public*/ QList<LayoutTurntable*> LayoutEditor::getLayoutTurntables() {
//    return getLayoutTracksOfClass("LayoutTurntable");
 QList<LayoutTurntable*> list = QList<LayoutTurntable*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<LayoutTurntable*>(lt))
   list.append((LayoutTurntable*)lt);
 }
 return list;}

/*public*/ QList<LevelXing*> LayoutEditor::getLevelXings() {
    QList<LayoutTrack*> layoutTracks =  getLayoutTracksOfClass("LevelXing");
    QList<LevelXing*> l = QList<LevelXing*>();
    for(LayoutTrack* t : layoutTracks)
     l.append((LevelXing*)t);
  return l;
}

/*public*/ QList<LayoutTrack*>* LayoutEditor::getLayoutTracks() {
    return layoutTrackList;
}

/*public*/ QList<LayoutTurnout*> LayoutEditor::getLayoutTurnoutsAndSlips() {
//    return getLayoutTracksOfClass("LayoutTurnout");
 QList<LayoutTurnout*> list = QList<LayoutTurnout*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<LayoutTurnout*>(lt))
   list.append((LayoutTurnout*)lt);
 }
 return list;}

/*protected*/ bool LayoutEditor::showAlignPopup()
{
 if (_positionableSelection!=nullptr)
 {
  return true;
 }
 else if (_pointSelection!=nullptr)
 {
  return true;
 }
 else if (_turnoutSelection!=nullptr && !_turnoutSelection->isEmpty())
 {
     return true;
 }
 #if 1 // TODO:
 else if (_turntableSelection!=nullptr)
 {
     return true;
 }
 #endif
 else if (_xingSelection!=nullptr)
 {
     return true;
 }
 else if (_slipSelection!=nullptr && !_slipSelection->isEmpty())
 {
     return true;
 }
// else if(_labelSelection !=nullptr)
//  return true;
 return false;
}

 /**
* Offer actions to align the selected Positionable items either
* Horizontally (at avearage y coord) or Vertically (at avearage x coord).
*/
/*public*/ bool LayoutEditor::setShowAlignmentMenu(QMenu* popup)
{
 if (showAlignPopup())
 {
  /*JMenu*/QMenu* edit = new /*JMenu*/QMenu(tr("EditAlignment"));

//     edit.add(new AbstractAction(rb.getQString("AlignX")) {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             alignSelection(true);
//         }
//     });
  QAction* alignXAction = new QAction("AlignX",this);
  popup->addAction(alignXAction);
//     edit.add(new AbstractAction(rb.getQString("AlignY")) {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             alignSelection(false);
//         }
//     });
  QAction* alignYAction = new QAction("AlignY",this);
  popup->addAction(alignYAction);

  popup->addMenu(edit);
  return true;
 }
 return false;
}
/*public*/ QPointF LayoutEditor::getEndCoords(QObject* o, int type) {
             if(o == nullptr)
             return QPointF(0,0);
  switch (type) {
      case POS_POINT:
          return ((PositionablePoint*)o)->getCoords();
      case TURNOUT_A:
          return ((LayoutTurnout*)o)->getCoordsA();
      case TURNOUT_B:
          return ((LayoutTurnout*)o)->getCoordsB();
      case TURNOUT_C:
          return ((LayoutTurnout*)o)->getCoordsC();
      case TURNOUT_D:
          return ((LayoutTurnout*)o)->getCoordsD();
      case LEVEL_XING_A:
          return ((LevelXing*)o)->getCoordsA();
      case LEVEL_XING_B:
          return ((LevelXing*)o)->getCoordsB();
      case LEVEL_XING_C:
          return ((LevelXing*)o)->getCoordsC();
      case LEVEL_XING_D:
          return ((LevelXing*)o)->getCoordsD();
      case SLIP_A:
          return ((LayoutSlip*)o)->getCoordsA();
      case SLIP_B:
          return ((LayoutSlip*)o)->getCoordsB();
      case SLIP_C:
          return ((LayoutSlip*)o)->getCoordsC();
      case SLIP_D:
          return ((LayoutSlip*)o)->getCoordsD();
      default:
#if 1 // TODO:
          if (type>=TURNTABLE_RAY_OFFSET) {
              return ((LayoutTurntable*)o)->getRayCoordsIndexed(type-TURNTABLE_RAY_OFFSET);
          }
#endif
       break;
  }
  return (QPointF(0.0,0.0));
}
void LayoutEditor::on_actionEnable_antialiasing_smoother_lines_toggled(bool bChecked)
{
 antialiasingOn = bChecked;
 paintTargetPanel(editScene);
}
QGraphicsView* LayoutEditor::panel()
{
 return editPanel;
}
/**
* Remove a PositionablePoint -- an Anchor or an End Bumper.
*/
/*protected*/ bool LayoutEditor::removePositionablePoint(PositionablePoint* o)
{
  // First verify with the user that this is really wanted
  if (!noWarnPositionablePoint)
  {
//   int selectedValue = JOptionPane.showOptionDialog(this,
//              rb.getQString("Question2"),rb.getQString("WarningTitle"),
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,nullptr,
//              new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
//              rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
      int selectedValue = QMessageBox::warning(this, "Warning", "Do you want to delete this point? Ignore will suppress future warnings and continue.",QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore);
      if (selectedValue == QMessageBox::No) return(false);   // return without creating if "No" response
      if (selectedValue == QMessageBox::Ignore) {
          // Suppress future warnings, and continue
          noWarnPositionablePoint = true;
      }
  }
  // remove from selection information
  if (selectedObject==o) selectedObject = nullptr;
  if (prevSelectedObject==o) prevSelectedObject = nullptr;
  // remove connections if any
  TrackSegment* t = o->getConnect1();
  if (t!=nullptr) removeTrackSegment(t);
  t = o->getConnect2();
  if (t!=nullptr) removeTrackSegment(t);
  // delete from array
//  for (int i = 0; i<pointList->size();i++)
//  {
//   PositionablePoint* p = pointList->at(i);
//   if (p==o)
//   {
//    // found object
//    pointList->remove(i);
//    p->invalidate(editScene);
//    setDirty(true);
//    //repaint();
//    paintTargetPanel(editScene);
//    return(true);
//   }
//  }
  if (layoutTrackList->contains(o))
  {
      layoutTrackList->removeOne(o);
      setDirty();
      redrawPanel();
      return true;
  }
  return (false);
}
/**
* Remove a Track Segment
*/
/*protected*/ void LayoutEditor::removeTrackSegment(TrackSegment* o) {
  // save affected blocks
  LayoutBlock* block1 = nullptr;
  LayoutBlock* block2 = nullptr;
  LayoutBlock* block = o->getLayoutBlock();
  // remove any connections
  int type = o->getType1();
  if (type==POS_POINT) {
      PositionablePoint* p = (PositionablePoint*)(o->getConnect1());
      if (p!=nullptr) {
          p->removeTrackConnection(o);
          if (p->getConnect1()!=nullptr)
              block1 = p->getConnect1()->getLayoutBlock();
          else if (p->getConnect2()!=nullptr)
              block1 = p->getConnect2()->getLayoutBlock();
      }
  }
  else {
      block1 = getAffectedBlock(o->getConnect1(),type);
      disconnect(o->getConnect1(),type);
  }
  type = o->getType2();
  if (type==POS_POINT) {
      PositionablePoint* p = (PositionablePoint*)(o->getConnect2());
      if (p!=nullptr) {
          p->removeTrackConnection(o);
          if (p->getConnect1()!=nullptr)
              block2 = p->getConnect1()->getLayoutBlock();
          else if (p->getConnect2()!=nullptr)
              block2 = p->getConnect2()->getLayoutBlock();
      }
  }
  else {
      block2 = getAffectedBlock(o->getConnect2(),type);
      disconnect(o->getConnect2(),type);
  }
  // delete from array
  for (TrackSegment* t : getTrackSegments()) {
      if (t==o) {
          // found object
          layoutTrackList->removeOne(t);
      }
  }
  // update affected blocks
  if (block!=nullptr) {
      // decrement Block use count
      block->decrementUse();
      auxTools->setBlockConnectivityChanged();
      block->updatePaths();
  }
  if ( (block1!=nullptr) && (block1!=block) ) block1->updatePaths();
  if ( (block2!=nullptr) && (block2!=block) && (block2!=block1) ) block2->updatePaths();
  //
//  o->invalidateItemType(editScene);
  setDirty(true);
  //repaint();
  paintTargetPanel(editScene);
}
/**
 * Remove a Layout Turntable
 */
/*protected*/ bool LayoutEditor::removeTurntable(LayoutTurntable* o)
{
 // First verify with the user that this is really wanted
 if (!noWarnTurntable)
 {
//     int selectedValue = JOptionPane.showOptionDialog(this,
//             tr("Question4r"), tr("WarningTitle"),
//             JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, nullptr,
//             new Object[]{tr("ButtonYes"), tr("ButtonNo"),
//                 tr("ButtonYesPlus")}, tr("ButtonNo"));
  int selectedValue = QMessageBox::question(this, tr("Warning"), tr("Are you sure you want to remove this turntable from the panel?"),QMessageBox::Yes | QMessageBox::No);
     if (selectedValue == QMessageBox::No) {
         return (false);   // return without creating if "No" response
     }
     if (selectedValue == QMessageBox::Yes) {
         // Suppress future warnings, and continue
         noWarnTurntable = true;
     }
 }
 // remove from selection information
 if (selectedObject == o) {
     selectedObject = nullptr;
 }
 if (prevSelectedObject == o) {
     prevSelectedObject = nullptr;
 }
 // remove connections if any
 for (int j = 0; j < o->getNumberRays(); j++) {
     TrackSegment* t = o->getRayConnectOrdered(j);
     if (t != nullptr) {
         substituteAnchor(o->getRayCoordsIndexed(j), o, t);
     }
 }
 // delete from array
 for (int i = 0; i < turntableList->size(); i++) {
     LayoutTurntable* lx = turntableList->at(i);
     if (lx == o) {
         // found object
         turntableList->remove(i);
         o->remove();
         setDirty(true);
         repaint();
         return (true);
     }
 }
 return (false);
}
/*private*/ void LayoutEditor::disconnect(QObject* o, int type) {
  if (o==nullptr) return;
  switch (type) {
      case TURNOUT_A:
          ((LayoutTurnout*)o)->setConnectA(nullptr,NONE);
          break;
      case TURNOUT_B:
          ((LayoutTurnout*)o)->setConnectB(nullptr,NONE);
          break;
      case TURNOUT_C:
          ((LayoutTurnout*)o)->setConnectC(nullptr,NONE);
          break;
      case TURNOUT_D:
          ((LayoutTurnout*)o)->setConnectD(nullptr,NONE);
          break;
      case LEVEL_XING_A:
          ((LevelXing*)o)->setConnectA(nullptr,NONE);
          break;
      case LEVEL_XING_B:
          ((LevelXing*)o)->setConnectB(nullptr,NONE);
          break;
      case LEVEL_XING_C:
          ((LevelXing*)o)->setConnectC(nullptr,NONE);
          break;
      case LEVEL_XING_D:
          ((LevelXing*)o)->setConnectD(nullptr,NONE);
          break;
      case SLIP_A:
          ((LayoutSlip*)o)->setConnectA(nullptr,NONE);
          break;
      case SLIP_B:
          ((LayoutSlip*)o)->setConnectB(nullptr,NONE);
          break;
      case SLIP_C:
          ((LayoutSlip*)o)->setConnectC(nullptr,NONE);
          break;
      case SLIP_D:
          ((LayoutSlip*)o)->setConnectD(nullptr,NONE);
          break;
      default:
#if 1 // TODO:
          if (type>=TURNTABLE_RAY_OFFSET) {
              ((LayoutTurntable*)o)->setRayConnect(nullptr,type-TURNTABLE_RAY_OFFSET);
          }
#endif
   break;
  }
}
#if 1 // TODO:
/*private*/ SignalHeadIcon* LayoutEditor::checkSignalHeadIcons(QPointF loc)
{
 // check signal head images, if any
 for (int i=signalHeadImage->size()-1; i>=0; i--)
 {
  SignalHeadIcon* s = signalHeadImage->at(i);
  double x = ((Positionable*)s)->getX();
  double y = ((Positionable*)s)->getY();
  double w = s->maxWidth();
  double h = s->maxHeight();
  QRectF r =  QRectF(x ,y ,w ,h);
  if(s->getItem() == nullptr)
   return nullptr;
  QRectF r2 =s->getItem()->boundingRect();
  // Test this detection rectangle
  if (r.contains(loc))
  {
   // mouse was pressed in signal head image
   return s;
  }
  if (r2.contains(loc))
  {
   // mouse was pressed in signal head image
   return s;
  }
 }
 return nullptr;
}

/*private*/ SignalMastIcon* LayoutEditor::checkSignalMastIcons(QPointF loc) {
 // check signal head images, if any
 for (int i=signalMastImage->size()-1; i>=0; i--) {
     SignalMastIcon* s = signalMastImage->at(i);
     double x = ((Positionable*)s)->getX();
     double y = ((Positionable*)s)->getY();
     double w = s->maxWidth();
     double h = s->maxHeight();
     QRectF r = QRectF(x ,y ,w ,h);
     // Test this detection rectangle
     if (r.contains(loc)) {
         // mouse was pressed in signal head image
         return s;
     }
 }
 return nullptr;
}
#endif
/*private*/ PositionableLabel* LayoutEditor::checkLabelImages(QPointF loc)
{
 PositionableLabel* l =nullptr;
 int level = 0;
 for (int i=_contents->size()-1; i>=0; i--)
 {
  PositionableLabel* s = (PositionableLabel*)_contents->at(i);
  double x = ((Positionable*)s)->getX();
  double y = ((Positionable*)s)->getY();
  double w = 10.0;
  double h = 5.0;
  if (s->isIcon() || s->isRotated())
  {
   w = s->maxWidth();
   h = s->maxHeight();
  }
  else if (s->isText())
  {
   //h = s->getFont().getSize();
   h = s->getFont().pointSizeF();

   w = (h*2*(s->getUnRotatedText().length()))/3;
   if(s->getItem() != nullptr)
   {
    QPointF pt = s->getItem()->mapFromParent(loc);
    if(s->getItem()->contains(pt))
     return s;
   }
  }
  QRectF r =  QRectF(x ,y ,w ,h);
  // Test this detection rectangle
  if (r.contains(loc))
  {
   // mouse was pressed in label image
   if (s->getDisplayLevel()>=level)
   {
    //Check to make sure that we are returning the highest level label.
    l = s;
    level = s->getDisplayLevel();
   }
  }
 }
 return l;
}
 /*private*/ AnalogClock2Display* LayoutEditor::checkClocks(QPointF loc) {
     // check clocks, if any
     for (int i=clocks->size()-1; i>=0; i--) {
         AnalogClock2Display* s = clocks->at(i);
         double x = s->getX();
         double y = s->getY();
         double w = s->getFaceWidth();
         double h = s->getFaceHeight();
         QRectF r = QRectF(x ,y ,w ,h);
         // Test this detection rectangle
         if (r.contains(loc)) {
             // mouse was pressed in clock image
             return s;
         }
     }
     return nullptr;
}

LEMemoryIcon *LayoutEditor::checkMemoryMarkerIcons(QPointF loc)
{
 LEMemoryIcon* l =nullptr;
 int level = 0;
 for (int i=memoryLabelList->size()-1; i>=0; i--)
 {
  LEMemoryIcon* s = memoryLabelList->at(i);
  double x = ((Positionable*)s)->getX();
  double y = ((Positionable*)s)->getY();
  double w = 10.0;
  double h = 5.0;
  if (s->isIcon() || s->isRotated())
    {
     w = s->maxWidth();
     h = s->maxHeight();
    }
    else
    if (s->isText())
    {
     //h = s->getFont().getSize();
     h = s->getFont().pointSizeF();

     w = (h*2*(s->getText().length()))/3;
     if(s->getItem() != nullptr)
     {
      QPointF pt = s->getItem()->mapFromParent(loc);
      if(s->getItem()->contains(pt))
       return s;
     }
    }
    QRectF r =  QRectF(x ,y ,w ,h);
    // Test this detection rectangle
    if (r.contains(loc))
    {
     // mouse was pressed in label image
     if (s->getDisplayLevel()>=level)
     {
      //Check to make sure that we are returning the highest level label.
      l = s;
      level = s->getDisplayLevel();
     }
    }
   }
   return l;
  }
#if 0
/*public*/ PositionableLabel* LayoutEditor::setUpBackground(QString name)
{
  NamedIcon* icon = NamedIcon::getIconByName(name);
  PositionableLabel* l = new PositionableLabel(icon, (Editor*)this);
  l->setPopupUtility(nullptr);        // no text
  l->setPositionable(false);
  l->setShowTooltip(false);
  l->setSize(icon->getIconWidth(), icon->getIconHeight());
  l->setDisplayLevel(BKG);
  l->setLocation(getNextBackgroundLeft(),0);
  putItem((Positionable*)l);
  return l;
}
#endif
 /**
  * Add a signal head to the Panel
  */
 void LayoutEditor::addSignalHead() {
     // check for valid signal head entry
  QString newName = ui->signalHeadComboBox->getDisplayName();

     SignalHead* mHead = nullptr;
     if ( (newName!=("")) ) {
         mHead = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(newName);
         /*if (mHead == nullptr)
             mHead = InstanceManager.signalHeadManagerInstance().getByUserName(tName);
         else */
         ui->signalHeadComboBox->setCurrentText(newName);
     }
     if (mHead == nullptr) {
         // There is no signal head corresponding to this name
//         JOptionPane.showMessageDialog(thisPanel,
//                 java.text.MessageFormat.format(rb.getQString("Error9"),
//                 new Object[]{tName}),
//                 rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
             QMessageBox::critical(this, tr("Error"),tr("Error - Cannot create a signal head icon because there is no signal head defined for - \"%1\". Please enter the name of a Signal Head in\nthe Signal Table and try again.").arg(newName) );
         return;
     }
     // create and set up signal icon
     SignalHeadIcon* l = new SignalHeadIcon(this);
     l->setSignalHead(newName);
     l->setIcon(tr("Red"), signalIconEditor->getIcon(0));
     l->setIcon(tr("Flashing rea"), signalIconEditor->getIcon(1));
     l->setIcon(tr("Yellow"), signalIconEditor->getIcon(2));
     l->setIcon(tr("Flashing Yellow"), signalIconEditor->getIcon(3));
     l->setIcon(tr("Green "), signalIconEditor->getIcon(4));
     l->setIcon(tr("Flashing Green"), signalIconEditor->getIcon(5));
     l->setIcon(tr("Dark"), signalIconEditor->getIcon(6));
     l->setIcon(tr("Held"), signalIconEditor->getIcon(7));
     l->setIcon(tr("Lunar"), signalIconEditor->getIcon(8));
     l->setIcon(tr("Flashing Lunar"), signalIconEditor->getIcon(9));
     setNextLocation(l);
     setDirty(true);
     putSignal(l);

 }
 /*public*/ void LayoutEditor::putSignal(SignalHeadIcon* l) {
     putItem(l);
     l->updateSize();
     l->setDisplayLevel(SIGNALS);
 }

 SignalHead* LayoutEditor::getSignalHead(QString name) {
     SignalHead* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name);
     if (sh == nullptr) sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getByUserName(name);
     if (sh == nullptr) log->warn("did not find a SignalHead named "+name);
     return sh;
 }

 /*public*/ bool LayoutEditor::containsSignalHead(SignalHead* head) {
    for (SignalHeadIcon* h : *signalList) {
        if (h->getSignalHead() == head) {
            return true;
        }
    }
    return false;
}   //containsSignalHead

/*public*/ void LayoutEditor::removeSignalHead(SignalHead* head) {
    SignalHeadIcon* h = nullptr;
    int index = -1;

    for (int i = 0; (i < signalList->size()) && (index == -1); i++) {
        h = signalList->at(i);

        if (h->getSignalHead() == head) {
            index = i;
            break;
        }
    }

    if (index != (-1)) {
        signalList->remove(index);

        if (h != nullptr) {
            h->remove();
            h->dispose();
        }
        setDirty(true);
        repaint();
    }
}   //removeSignalHead

 void LayoutEditor::addSignalMast() {
     // check for valid signal head entry
     QString newName = ui->signalMastComboBox->getDisplayName();
     SignalMast* mMast = nullptr;
     if ( (newName!=("")) ) {
         mMast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(newName);
         ui->signalMastComboBox->setText(newName);
     }
     if (mMast == nullptr) {
         // There is no signal head corresponding to this name
//         JOptionPane.showMessageDialog(thisPanel,
//                 java.text.MessageFormat.format(rb.getQString("Error9"),
//                 new Object[]{tName}),
//                 rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
             QMessageBox::critical(0, tr("Error"),tr("Error - Cannot create a signal mast icon because there is no signal mast defined for - \"%1\". Please enter the name of a Signal mast in                                              the Signal Table and try again.").arg(newName) );
         return;
     }
     // create and set up signal icon
     SignalMastIcon* l = new SignalMastIcon(this);
     l->setSignalMast(newName);
     setNextLocation(l);
     setDirty(true);
     putSignalMast(l);
 }

 /*public*/ void LayoutEditor::putSignalMast(SignalMastIcon* l) {
     putItem((Positionable*)l);
     l->updateSize();
     l->setDisplayLevel(SIGNALS);
 }

 SignalMast* LayoutEditor::getSignalMast(QString name) {
     SignalMast* sh = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name);
     if (sh == nullptr) sh = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName(name);
     if (sh == nullptr) log->warn("did not find a SignalMast named "+name);
     return sh;
 }
/**
* Add a label to the Draw Panel
*/
void LayoutEditor::addLabel()
{
 PositionableLabel* l = Editor::addLabel(ui->textLabel->text().trimmed());
 setDirty(true);
 l->setForeground(defaultTextColor);
 ((Positionable*)l)->setLocation(dLoc.x(),dLoc.y());
}

/**
* Set object location and size for icon and label object as it is created.
* Size comes from the preferredSize; location comes
* from the fields where the user can spec it.
*/
/*protected*/ void LayoutEditor::setNextLocation(Positionable* obj) {
  obj->setLocation(xLoc,yLoc);
}
/*public*/ void LayoutEditor::putItem(Positionable* l)
{
 if(qobject_cast<PositionableLabel*>(l->self()))
 {
  ((JLabel*)l)->hide();
 }
 Editor::putItem(l);
 if (static_cast<SensorIcon*>(l)!= nullptr)
 {
  sensorImage->append((SensorIcon*)l);
  sensorList->append((SensorIcon*)l);
 }
 else if (static_cast<LocoIcon*>(l)!= nullptr)
 {
  markerImage->append((LocoIcon*)l);
 }
 else if (static_cast<SignalHeadIcon*>(l)!=nullptr)
 {
     signalHeadImage->append((SignalHeadIcon*)l);
     signalList->append((SignalHeadIcon*)l);
 }
 else if (static_cast<SignalMastIcon*>(l)!=nullptr)
 {
     signalMastImage->append((SignalMastIcon*)l);
     signalMastList->append((SignalMastIcon*)l);
 }
 else
  //if (l instanceof MemoryIcon*)
 if(static_cast<LEMemoryIcon*>(l)!= nullptr)
 {
  memoryLabelList->append((LEMemoryIcon*)l);
 }
 else if (static_cast<AnalogClock2Display*>(l)!=nullptr)
 {
  clocks->append((AnalogClock2Display*)l);
 }
 else if (static_cast<MultiSensorIcon*>(l) != nullptr)
 {
  multiSensors->append((MultiSensorIcon*)l);
 }
 else
 //if (l instanceof PositionableLabel*)
 if(qobject_cast<PositionableLabel*>(l->self())!= nullptr)
 {
  if ( !(((PositionableLabel*)l->self())->isBackground()) )
  {
   _labelImage->append((PositionableLabel*)l->self());
  }
  else
  {
   backgroundImage->append((PositionableLabel*)l->self());
  }
 }
}

/**
* Remove object from all Layout Editor temmporary lists of items not part of track schematic
*/
/*protected*/ bool LayoutEditor::remove(QObject* s)
{
  bool found = false;

  for (int i = 0; i<sensorImage->size();i++)
  {
   if (s == sensorImage->at(i))
   {
    sensorImage->remove(i);
    found = true;
    break;
   }
  }

  for (int i = 0; i<sensorList->size();i++)
  {
   if (s == sensorList->at(i))
   {
    sensorList->remove(i);
    found = true;
    break;
   }
  }

  for (int i = 0; i<backgroundImage->size();i++)
  {
   if (s == backgroundImage->at(i))
   {
    backgroundImage->remove(i);
    found = true;
    break;
   }
  }
  for (int i = 0; i<memoryLabelList->size();i++)
  {
   if (s == memoryLabelList->at(i))
   {
    memoryLabelList->remove(i);
    found = true;
    break;
   }
  }
  for (int i = 0; i < blockContentsLabelList->size(); i++)
  {
      if (s == (QObject*)blockContentsLabelList->at(i)) {
          blockContentsLabelList->remove(i);
          found = true;
          break;
      }
  }

  for (int i = 0; i<signalList->size();i++) {
      if (s == signalList->at(i)) {
          signalList->remove(i);
          found = true;
          break;
      }
  }
  for (int i = 0; i<signalMastList->size();i++) {
      if (s == signalMastList->at(i)) {
          signalMastList->remove(i);
          found = true;
          break;
      }
  }

  for (int i = 0; i<multiSensors->size();i++) {
      if (s == multiSensors->at(i)) {
          multiSensors->remove(i);
          found = true;
          break;
      }
  }

  for (int i = 0; i<clocks->size();i++) {
      if (s == clocks->at(i)) {
          clocks->remove(i);
          found = true;
          break;
      }
  }
//  for (int i = 0; i<signalMastImage->size();i++) {
//      if (s == signalMastImage->at(i)) {
//          signalMastImage->remove(i);
//          found = true;
//          break;
//      }
//  }
  for (int i = 0; i<signalHeadImage->size();i++) {
      if (s == signalHeadImage->at(i)) {
          signalHeadImage->remove(i);
          found = true;
          break;
      }
  }

  for (int i = 0; i<_labelImage->size(); i++)
  {
   if (s == _labelImage->at(i))
   {
    _labelImage->remove(i);
    found = true;
    break;
   }
  }
  Editor::removeFromContents((Positionable*)s);
  if (found)
  {
   setDirty(true);
   //repaint();
   paintTargetPanel(editScene);
  }
  return found;
}

/*public*/ bool LayoutEditor::removeFromContents(Positionable* l)
{
    return remove(l->self());
}
/*private*/ QString LayoutEditor::findBeanUsage(NamedBean* sm)
{
    PositionablePoint* pe;
    PositionablePoint* pw;
    LayoutTurnout* lt;
    LevelXing* lx;
    LayoutSlip* ls;
    bool found = false;
    QString sb;// = new StringBuilder();
    sb.append("This ");
    if (qobject_cast<SignalMast*>(sm)) {
        sb.append("Signal Mast");
        sb.append(" is linked to the following items<br> do you want to remove those references");
        if (InstanceManager::signalMastLogicManagerInstance()->isSignalMastUsed((SignalMast*) sm)) {
            SignalMastLogic* sml = qobject_cast<SignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic((SignalMast*) sm);
            //jmri.SignalMastLogic sml = InstanceManager.signalMastLogicManagerInstance().getSignalMastLogic((SignalMast)sm);
            if (sml != nullptr && sml->useLayoutEditor(sml->getDestinationList().at(0))) {
                sb.append(" and any SignalMast Logic associated with it");
            }
        }
    } else if (qobject_cast<Sensor*>(sm)) {
        sb.append("Sensor");
        sb.append(" is linked to the following items<br> do you want to remove those references");
    } else if (qobject_cast<SignalHead*>(sm)) {
        sb.append("SignalHead");
        sb.append(" is linked to the following items<br> do you want to remove those references");
    }

    if ((pw = finder->findPositionablePointByWestBoundBean(sm)) != nullptr) {
        sb.append("<br>Point of ");
        TrackSegment* t = pw->getConnect1();
        if (t != nullptr) {
            sb.append(t->getBlockName() + " and ");
        }
        t = pw->getConnect2();
        if (t != nullptr) {
            sb.append(t->getBlockName());
        }
        found = true;
    }
    if ((pe = finder->findPositionablePointByEastBoundBean(sm)) != nullptr) {
        sb.append("<br>Point of ");
        TrackSegment* t = pe->getConnect1();
        if (t != nullptr) {
            sb.append(t->getBlockName() + " and ");
        }
        t = pe->getConnect2();
        if (t != nullptr) {
            sb.append(t->getBlockName());
        }
        found = true;
    }
    if ((lt = finder->findLayoutTurnoutByBean(sm)) != nullptr) {
        sb.append("<br>Turnout " + lt->getTurnoutName());
        found = true;
    }
    if ((lx = finder->findLevelXingByBean(sm)) != nullptr) {
        sb.append("<br>Level Crossing " + lx->getID());
        found = true;
    }
    if ((ls = finder->findLayoutSlipByBean(sm)) != nullptr) {
        sb.append("<br>Slip " + ls->getTurnoutName());
        found = true;
    }
    if (!found) {
        return "";
    }
    return sb/*.toString()*/;
}

/*private*/ bool LayoutEditor::removeSignalMast(SignalMastIcon* si) {
        SignalMast* sm = si->getSignalMast();
        QString usage = findBeanUsage(sm);
        if (usage != "") {
            usage = "<html>" + usage + "</html>";
            QVariantList buttons = QVariantList() << tr("Yes") << tr("No") << tr("Cancel");
            int selectedValue = JOptionPane::showOptionDialog(this,
                    usage, tr("Warning"),
                    JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                    /*new Object[]{rb.getString("ButtonYes"), rb.getString("ButtonNo"), rb.getString("ButtonCancel")}, rb.getString("ButtonYes"))*/buttons);
            if (selectedValue == 1) {
                return (true); // return leaving the references in place but allow the icon to be deleted.
            }
            if (selectedValue == 2) {
                return (false); // do not delete the item
            }
            removeBeanRefs(sm);
        }
        return true;
    }

    /*private*/ void LayoutEditor::removeBeanRefs(NamedBean* sm) {
        PositionablePoint* pe;
        PositionablePoint* pw;
        LayoutTurnout* lt;
        LevelXing* lx;
        LayoutSlip* ls;

        if ((pw = finder->findPositionablePointByWestBoundBean(sm)) != nullptr) {
            pw->removeBeanReference(sm);
        }
        if ((pe = finder->findPositionablePointByEastBoundBean(sm)) != nullptr) {
            pe->removeBeanReference(sm);
        }
        if ((lt = finder->findLayoutTurnoutByBean(sm)) != nullptr) {
            lt->removeBeanReference(sm);
        }
        if ((lx = finder->findLevelXingByBean(sm)) != nullptr) {
            lx->removeBeanReference(sm);
        }
        if ((ls = finder->findLayoutSlipByBean(sm)) != nullptr) {
            ls->removeBeanReference(sm);
        }
    }
void LayoutEditor::repaint()
{
 paintTargetPanel(editScene);
}

/*private*/ SensorIcon* LayoutEditor::checkSensorIcons(QPointF loc)
{
 // check sensor images, if any
 for (int i=sensorImage->size()-1; i>=0; i--)
 {
  SensorIcon* s =static_cast<SensorIcon*>(sensorImage->at(i));
  if(s == nullptr)
   continue;
  double x = s->getX();
  double y = s->getY();
  double w = s->maxWidth();
  double h = s->maxHeight();
  QRectF r =  QRectF(x ,y ,w ,h);
  // Test this detection rectangle
  if (r.contains(loc)) {
      // mouse was pressed in sensor icon image
      return s;
  }
 }
 return nullptr;
}
/**
* Add a sensor indicator to the Draw Panel
*/
void LayoutEditor::addSensor()
{
 QString newName = ui->sensorComboBox->getDisplayName();
  if (newName.isEmpty())
  {
//      JOptionPane.showMessageDialog(this,rb.getQString("Error10"),
//                  rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(0, "Error", "Sensor name must be specified!");
   return;
  }

  SensorIcon* l = new SensorIcon(new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",                                              ":/resources/icons/smallschematics/tracksegments/circuit-error.gif"),this);
//        l.setActiveIcon(sensorIconEditor.getIcon(0));
//        l.setInactiveIcon(sensorIconEditor.getIcon(1));
//        l.setInconsistentIcon(sensorIconEditor.getIcon(2));
//        l.setUnknownIcon(sensorIconEditor.getIcon(3));
  l->setIcon("SensorStateActive", sensorIconEditor->getIcon(0));
  l->setIcon("SensorStateInactive", sensorIconEditor->getIcon(1));
  l->setIcon("BeanStateInconsistent", sensorIconEditor->getIcon(2));
  l->setIcon("BeanStateUnknown", sensorIconEditor->getIcon(3));
  l->setSensor(name);
  l->setDisplayLevel(SENSORS);
  //Sensor xSensor = l.getSensor();
  if (l->getSensor() != nullptr)
  {
   if (newName != (l->getNamedSensor()->getName()))
   {
       ui->sensorComboBox->setText(l->getNamedSensor()->getName());
   }
  }
  NamedBeanHandle<Sensor*>* s = l->getNamedSensor();
  QString sensorName = "";
  if(s != nullptr)
   sensorName = s->getName();
  ui->sensorComboBox->setText(sensorName);
  if(l->getNamedBean() != nullptr)
   l->setToolTip(l->getNamedBean()->getSystemName());
  setNextLocation(l);
  setDirty(true);
  putItem((Positionable*)l);
}

/*public*/ void LayoutEditor::putSensor(SensorIcon* l){
  putItem((Positionable*)l);
  l->updateSize();
  l->setDisplayLevel(SENSORS);
}
/*private*/ PositionableLabel* LayoutEditor::checkBackgrounds(QPointF loc)
{
 // check background images, if any
 for (int i=backgroundImage->size()-1; i>=0; i--)
 {
  PositionableLabel* b = backgroundImage->at(i);
  double x = b->getX();
  double y = b->getY();
  double w = b->maxWidth();
  double h = b->maxHeight();
  QRectF r = QRectF(x ,y ,w ,h);
  // Test this detection rectangle
  if (r.contains(loc))
  {
   // mouse was pressed in background image
   return b;
  }
 }
 return nullptr;
}
/*protected*/ void LayoutEditor::setSelectionsScale(double s, Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p->self());
 Q_ASSERT(pl != nullptr);
 if (_selectionGroup!=nullptr && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i)->self())->setScale(s);
  }
 }
 else
 {
  pl->setScale(s);
 }
}

/*protected*/ void LayoutEditor::setSelectionsRotation(int k, Positionable* p)
{
  PositionableLabel* pl = qobject_cast<PositionableLabel*>(p->self());
  Q_ASSERT(pl != nullptr);
  if (_selectionGroup!=nullptr && _selectionGroup->contains(p))
  {
   for (int i=0; i<_selectionGroup->size(); i++)
   {
    ((PositionableLabel*)_selectionGroup->at(i)->self())->rotate(k);
   }
  } else
  {
   ((PositionableLabel*)p)->rotate(k);
  }
}
/**
* Add an action to remove the Positionable item.
*/
/*public*/ void LayoutEditor::setRemoveMenu(Positionable* p, QMenu* popup)
{
//  popup.add(new AbstractAction(tr("Remove")) {
//      Positionable comp;
//      /*public*/ void actionPerformed(ActionEvent e) {
//          comp.remove();
//          removeSelections(comp);
//      }
//      AbstractAction init(Positionable pos) {
//          comp = pos;
//          return this;
//      }
//  }.init(p));
 currComp = p;
 QAction* removeMenuAction = new QAction("Remove", this);
 connect(removeMenuAction, SIGNAL(triggered()), this, SLOT(On_removeMenuAction_triggered()));
 popup->addAction(removeMenuAction);
}

void LayoutEditor::On_removeMenuAction_triggered()
{
 Positionable* comp = currComp;
 //comp->remove();
 SensorIcon* si = qobject_cast<SensorIcon*>(comp->self());
 if(si != nullptr)
 {
  Q_ASSERT(si->_itemGroup->scene()!=0);
  editScene->removeItem(si->_itemGroup);
  si->_itemGroup = nullptr;
  si->remove();
 }
 LocoIcon* li = qobject_cast<LocoIcon*>(comp->self());
 if(li != nullptr)
 {
  Q_ASSERT(li->_itemGroup->scene()!=0);
  editScene->removeItem(li->_itemGroup);
  li->_itemGroup = nullptr;
  li->remove();
 }
 LEMemoryIcon* mi = qobject_cast<LEMemoryIcon*>(comp->self());
 if(mi != nullptr)
 {
  Q_ASSERT(mi->_itemGroup->scene()!=0);
  editScene->removeItem(mi->_itemGroup);
  mi->_itemGroup = nullptr;
  mi->remove();
 }
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(comp->self());
 if(pl != nullptr)
 {
  Q_ASSERT(pl->_itemGroup->scene()!=0);
  editScene->removeItem(pl->_itemGroup);
  pl->_itemGroup = nullptr;
  pl->remove();
 }
 removeSelections(comp);
}
/*protected*/ void LayoutEditor::removeSelections(Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p->self());
 Q_ASSERT(pl != nullptr);

 if (_selectionGroup!=nullptr && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i)->self())->remove();
  }
  _selectionGroup = new QList<Positionable*>();
 }
}

/*private*/ MultiSensorIcon* LayoutEditor::checkMultiSensors(QPointF loc)
{
 // check multi sensor icons, if any
 for (int i=multiSensors->size()-1; i>=0; i--)
  {
   MultiSensorIcon* s = multiSensors->at(i);
   double x = ((Positionable*)s)->getLocation().x();
   double y = ((Positionable*)s)->getLocation().y();
   double w = s->maxWidth();
   double h = s->maxHeight();
   QRectF r = QRectF(x ,y ,w ,h);
 // Test this detection rectangle
 if (r.contains(loc)) {
     // mouse was pressed in multi sensor image
     return s;
 }
}
return nullptr;
}
/*private*/ LocoIcon* LayoutEditor::checkMarkers(QPointF loc)
{
 // check marker icons, if any
 for (int i=markerImage->size()-1; i>=0; i--)
 {
      LocoIcon* l = markerImage->at(i);
//      double x = l->getX();
//      double y = l->getY();
      double x = ((Positionable*)l)->getLocation().x();
      double y = ((Positionable*)l)->getLocation().y();
      double w = l->maxWidth();
      double h = l->maxHeight();
      QRectF r = QRectF(x ,y ,w ,h);
      // Test this detection rectangle
      if (r.contains(loc)) {
          // mouse was pressed in marker icon
          return l;
      }
  }
  return nullptr;
}
void LayoutEditor::on_actionAdd_loco_triggered()
{
 InputDialog* dlg = new InputDialog("Enter loco id", "0", nullptr, this);
 if(dlg->exec() == QDialog::Accepted)
 {
  QString nameID= dlg->value();
  if(!nameID.isNull())
  {
   LocoIcon* icon = addLocoIcon(nameID.trimmed());
   icon->setLocation(200,100);
  }
 }
 paintTargetPanel(editScene);
}
/**
* Add a loco marker to the target
*/
/*public*/ LocoIcon* LayoutEditor::addLocoIcon (QString name)
{
  LocoIcon* l = new LocoIcon(this);
  l->setToolTip(name);
  putLocoIcon(l, name);
  l->setPositionable(true);
  return l;
}

/*public*/ void LayoutEditor::putLocoIcon(LocoIcon* l, QString name)
{
 Editor::putLocoIcon(l, name);
 //markerImage->append(l);  // redundant??
}

/**
 * Add a background image
 */
/*public*/ void LayoutEditor::addBackground()
{
 if (inputFileChooser == nullptr)
 {
     inputFileChooser = new JFileChooser(System::getProperty(
                                             "user.dir") + File::separator + "resources" + File::separator +
                                         "icons");
//     FileChooserFilter filt = new jmri.util->FileChooserFilter("Graphics Files");
//     filt.   addExtension("gif");
//     filt.   addExtension("jpg");
     QString filt = "Graphics Files (*.gif, *.jpg)";
     inputFileChooser->setFileFilter(filt);
 }
 //inputFileChooser.rescanCurrentDirectory();

 int retVal = inputFileChooser->showOpenDialog(this);

 if (retVal != JFileChooser::APPROVE_OPTION)
 {
     return; //give up if no file selected
 }
 //NamedIcon icon = new NamedIcon(inputFileChooser.getSelectedFile().getPath(),
 //inputFileChooser.getSelectedFile().getPath());

 QString name = inputFileChooser->getSelectedFile()->getPath();

 //convert to portable path
 name = FileUtil::getPortableFilename(name);

 //setup icon
 backgroundImage->append(Editor::setUpBackground(name));
}   //addBackground

/**
 * Remove a background image from the list of background images
 */
/*protected*/ void LayoutEditor::removeBackground(PositionableLabel* b)
{
 for (int i = 0; i < backgroundImage->size(); i++)
 {
  if (b == backgroundImage->at(i))
  {
   backgroundImage->remove(i);
   setDirty(true);

   return;
  }
 }
}   //removeBackground

/**
*  Control whether panel items are positionable.
*  Markers are always positionable.
* @param state true for positionable.
*/
//@Override
/*public*/ void LayoutEditor::setAllPositionable(bool state)
{
 PanelEditor::setAllPositionable(state);
 ui->actionAllow_repositioning->setChecked(state);
 for (int i = 0; i<markerImage->size(); i++)
 {
  ((Positionable*)markerImage->at(i))->setPositionable(true);
 }
 //_positionable =state;
}

/*private*/ void LayoutEditor::setupMarkerMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* markerMenu = ui->menuMarker;//new QMenu(tr("Marker"));

//    markerMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("MenuMarkerMnemonic")));
    //menuBar.addMenu(markerMenu);
    QAction* act;
    markerMenu->addAction(act = new AbstractAction(tr("AddLoco") + "...",this));
//    {
//        @Override
//        public void actionPerformed(ActionEvent event) {
//            locoMarkerFromInput();
//        }
//    });
    connect(act, SIGNAL(triggered()), this, SLOT(locoMarkerFromInput()));
    markerMenu->addAction(act = new AbstractAction(tr("AddLocoRoster") + "...", this));
//    {
//        @Override
//        public void actionPerformed(ActionEvent event) {
//            locoMarkerFromRoster();
//        }r
//    });
    connect(act, SIGNAL(triggered(bool)), this, SLOT(locoMarkerFromRoster()));
    markerMenu->addAction(act =new AbstractAction(tr("Remove Markers"), this));
//    {
//        @Override
//        public void actionPerformed(ActionEvent event) {
//            removeMarkers();
//        }
//    });
      connect(act, SIGNAL(triggered(bool)), this, SLOT(removeMarkers()));
}

/*private*/ void LayoutEditor::setupDispatcherMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* dispMenu = new QMenu(tr("Dispatcher"));

//    dispMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("MenuDispatcherMnemonic")));
    QAction* act;
    dispMenu->addAction(act = new DispatcherAction(tr("Open"),this));
    menuBar->addMenu(dispMenu);
    QAction* newTrainItem = new QAction(tr("New Train"), this);
    dispMenu->addAction(newTrainItem);
//    newTrainItem.addActionListener((ActionEvent event) -> {
//        if (InstanceManager.getDefault(TransitManager.class).getNamedBeanSet().size() <= 0) {
//            //Inform the user that there are no Transits available, and don't open the window
//            JOptionPane.showMessageDialog(null,
//                    ResourceBundle.getBundle("jmri.jmrit.dispatcher.DispatcherBundle").
//                            getString("NoTransitsMessage"));
//        } else {
//            DispatcherFrame df = InstanceManager.getDefault(DispatcherFrame.class);
//            if (!df.getNewTrainActive()) {
//                df.getActiveTrainFrame().initiateTrain(event, null, null);
//                df.setNewTrainActive(true);
//            } else {
//                df.getActiveTrainFrame().showActivateFrame(null);
//            }
//        }
//    });
}

void LayoutEditor::onNewTrain()
{
 if (static_cast<TransitManager*>(InstanceManager::getDefault("TransitManager"))->getNamedBeanSet().size() <= 0) {
     //Inform the user that there are no Transits available, and don't open the window
     JOptionPane::showMessageDialog(nullptr,
             tr("Cannot open Dispatcher - no Transits found.\nPlease create Transits and try again."));
 } else {
     DispatcherFrame* df = static_cast<DispatcherFrame*>(InstanceManager::getDefault("DispatcherFrame"));
     if (!df->getNewTrainActive()) {
         df->getActiveTrainFrame()->initiateTrain(/*event*/nullptr, nullptr, nullptr);
         df->setNewTrainActive(true);
     } else {
         df->getActiveTrainFrame()->showActivateFrame(nullptr);
     }
 }
}
/*public*/ bool LayoutEditor::isIncludedTurnoutSkipped() {
    return includedTurnoutSkipped;
}

/*public*/ void LayoutEditor::setIncludedTurnoutSkipped(bool boo) {
    includedTurnoutSkipped = boo;
}


//TODO: @Deprecated // Java standard pattern for boolean getters is "isOpenDispatcherOnLoad()"
/*public*/ bool LayoutEditor::getOpenDispatcherOnLoad() {
    return openDispatcherOnLoad;
}

/*public*/ void LayoutEditor::setOpenDispatcherOnLoad(bool boo) {
    openDispatcherOnLoad = boo;
}

/**
* Remove marker icons from panel
*/
/*protected*/ void LayoutEditor::removeMarkers()
{
 if(markerImage->isEmpty())
  return;
 for (int i = markerImage->size(); i >0 ; i--)
 {
  LocoIcon* il = markerImage->at(i-1);
   if ( (il != nullptr) && (il->isActive()) )
   {
     markerImage->remove(i-1);
     il->remove();
     il->dispose();
     setDirty(true);
   }
  }
  Editor::removeMarkers();
  //repaint();
  paintTargetPanel(editScene);
}

/**
 * Assign the block from the toolbar to all selected layout tracks
 */
/*protected*/ void LayoutEditor::assignBlockToSelection() {
    QString newName = ui->blockIDComboBox->currentText();
    LayoutBlock* b = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(newName);
    for (LayoutTrack* lt : _layoutTrackSelection) {
        lt->setAllLayoutBlocks(b);
    }
}

void LayoutEditor::on_actionRemove_markers_triggered()
{
 removeMarkers();
}
void LayoutEditor::on_actionAdd_Turntable_triggered()
{
 addTurntable(windowCenter());
 setDirty(true);
 repaint();
}

/**
* Add a memory label to the Draw Panel
*/
void LayoutEditor::addMemory()
{
 QString memoryName = ui->textMemoryComboBox->getDisplayName();

         if (memoryName.isEmpty()) {
             JOptionPane::showMessageDialog(this, tr("Error - Cannot create a memory label because no memory variable is entered in the\nMemory text field. Please enter the name of a memory variable and try again."),
                     tr("Error"), JOptionPane::ERROR_MESSAGE);
             return;
         }
         LEMemoryIcon* l = new LEMemoryIcon(" ", this);
         l->setMemory(memoryName);
         Memory* xMemory = l->getMemory();

         if (xMemory != nullptr) {
             QString uname = xMemory->getDisplayName();
             if (uname != (memoryName)) {
                 //put the system name in the memory field
                 ui->textMemoryComboBox->setText(xMemory->getSystemName());
             }
         }
         setNextLocation(l);
         l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
         l->setDisplayLevel(Editor::LABELS);
         l->setForeground(defaultTextColor);
         unionToPanelBounds(l->getBounds());
         putItem(l); // note: this calls unionToPanelBounds & setDirty()
     } //addMemory
/**
* Add a Reporter Icon to the panel
*/
void LayoutEditor::addReporter(QString textReporter,int xx,int yy) {
  ReporterIcon* l = new ReporterIcon(this);
  l->setReporter(textReporter);
  ((Positionable*)l)->setLocation(xx,yy);
  l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
  l->setDisplayLevel(LABELS);
  setDirty(true);
  putItem((Positionable*)l);
}
/**
* Add an icon to the target
*/
void LayoutEditor::addIcon() {
  PositionableLabel* l = new PositionableLabel(iconEditor->getIcon(0), this);
  setNextLocation(l);
  l->setDisplayLevel(ICONS);
  setDirty(true);
  putItem((Positionable*)l);
  l->updateSize();
}

void LayoutEditor::on_actionAllow_turnout_animation_toggled(bool bChecked)
{
 animatingLayout = bChecked;
 ui->actionAllow_turnout_animation->setChecked(bChecked);
}
/**
 *  Control whether panel items are positionable.
 *  Markers are always positionable.
 * @param state true for positionable.
 */
void LayoutEditor::on_actionAllow_repositioning_toggled(bool bChecked)
{
 setAllPositionable(bChecked);
 for (int i = 0; i<markerImage->size(); i++)
 {
  ((PositionableLabel*)markerImage->at(i))->setPositionable(true);
 }
}
void LayoutEditor::on_actionAllow_layout_control_toggled(bool bChecked)
{
 setAllControlling(bChecked);
}
/**
*  Control whether target panel items are controlling layout items.
*  Does this by invoke the {@link Positionable#setControlling} function of
*  each item on the target panel. This also controls the relevant pop-up menu items.
* @param state true for controlling.
*/
///*public*/ void LayoutEditor::setAllControlling(bool state)
//{
// _controlLayout = state;
// if (_globalSetsLocal)
// {
//  for (int i = 0; i<_contents->size(); i++)
//  {
//   Positionable* pos = _contents->at(i);
//   if(qobject_cast<PositionableLabel*>((QObject*)pos)!= nullptr)
//    ((PositionableLabel*)pos)->setControlling(state);
//  }
// }
//}
/**
* Does global flag sets Positionable and Control for individual items
*/
/*public*/ void LayoutEditor::setGlobalSetsLocalFlag(bool set) {
  _globalSetsLocal = set;
}
/*private*/ void LayoutEditor::deleteSelectedItems() // SLOT[]
{
 if(!noWarnGlobalDelete)
// {
//      int selectedValue = JOptionPane.showOptionDialog(this,
//          rb.getQString("Question6"),rb.getQString("WarningTitle"),
//          JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,nullptr,
//          new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
//          rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
//      if (selectedValue == 1) return;   // return without creating if "No" response
//      if (selectedValue == 2) {
//          // Suppress future warnings, and continue
//          noWarnGlobalDelete = true;
//      }
   switch(QMessageBox::question(this,tr("Question"),tr("Delete all? Yes to suppress future warnings and continue."),QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
   {
   case QMessageBox::Yes:
    noWarnGlobalDelete = true;
    break;
   default:
   case QMessageBox::No:
    return; // return without creating if "No" response
  }
  if(_positionableSelection!=nullptr)
  {
   for(int i=0; i<_positionableSelection->count(); i++)
   {
    Positionable* comp = _positionableSelection->at(i);
    if(qobject_cast<SensorIcon*>(comp->self()) != nullptr)
    {
     SensorIcon* si = qobject_cast<SensorIcon*>(comp->self());
     Q_ASSERT(si->_itemGroup->scene()!=0);
     editScene->removeItem(si->_itemGroup);
     remove(si);
    }
    else if(qobject_cast<LocoIcon*>(comp->self()) != nullptr)
    {
     LocoIcon* li = qobject_cast<LocoIcon*>(comp->self());
     Q_ASSERT(li->_itemGroup->scene()!=0);
     editScene->removeItem(li->_itemGroup);
     remove(li);
    }
    else if(qobject_cast<LEMemoryIcon*>(comp->self()) != nullptr)
    {
     LEMemoryIcon*mi = qobject_cast<LEMemoryIcon*>(comp->self());
     Q_ASSERT(mi->_itemGroup->scene()!=0);
     editScene->removeItem(mi->_itemGroup);
     remove(mi);
    }
   }
  }
  if(_pointSelection!=nullptr)
  {
   bool oldPosPoint = noWarnPositionablePoint;
   noWarnPositionablePoint = true;
   for (int i=0; i<_pointSelection->count(); i++)
   {
    PositionablePoint* point = _pointSelection->at(i);
    removePositionablePoint(point);
   }
   noWarnPositionablePoint = oldPosPoint;
  }

  if(_xingSelection!=nullptr)
  {
   bool oldLevelXing = noWarnLevelXing;
   noWarnLevelXing = true;
   for(int i = 0; i <_xingSelection->count(); i++)
   {
    LevelXing* point = _xingSelection->at(i);
    removeLevelXing(point);
   }
   noWarnLevelXing = oldLevelXing;
  }
  if(_slipSelection!=nullptr){
      bool oldSlip = noWarnSlip;
      noWarnSlip = true;
      for(int i=0; i < _slipSelection->count(); i++)
      {
       LayoutSlip* point = _slipSelection->at(i);
       removeLayoutSlip(point);
      }
      noWarnSlip = oldSlip;
  }
#if 1 //TODO:
  if(_turntableSelection!=nullptr){
      bool oldTurntable = noWarnTurntable;
      noWarnTurntable = true;
      foreach(LayoutTurntable* point, *_turntableSelection){
          removeTurntable(point);
      }
      noWarnTurntable = oldTurntable;
  }
#endif
  if(_turnoutSelection!=nullptr)
  {
   bool oldTurnout = noWarnLayoutTurnout;
   noWarnLayoutTurnout = true;
   for(int i=0; i <_turnoutSelection->count(); i++)
   {
    LayoutTurnout* point = _turnoutSelection->at(i);
    removeLayoutTurnout(point);
   }
   noWarnLayoutTurnout = oldTurnout;
  }
  selectionActive = false;
  clearSelectionGroups();
  //repaint();

}
/**
* Remove a LayoutTurnout
*/
/*protected*/ bool LayoutEditor::removeLayoutTurnout(LayoutTurnout* o)
{
  // First verify with the user that this is really wanted
  if (!noWarnLayoutTurnout)
  {
//      int selectedValue = JOptionPane.showOptionDialog(this,
//              rb.getQString("Question1"),rb.getQString("WarningTitle"),
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,nullptr,
//              new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
//              rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
//      if (selectedValue == 1) return(false);   // return without removing if "No" response
//      if (selectedValue == 2) {
//          // Suppress future warnings, and continue
//          noWarnLayoutTurnout = true;
//      }
    switch(QMessageBox::question(this,tr("Warning"),tr("Are you sure that you want to remove this turnout from the panel along with any connected track segments? Ignore will continue and suppress further messages like this."),QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore))
    {
    case QMessageBox::Yes:
     break;
    case QMessageBox::Ignore:
     noWarnLayoutTurnout = true;
     break;
    default:
    case QMessageBox::No:
     return false; // return without creating if "No" response
   }
  }
  // remove from selection information
  if (selectedObject==o) selectedObject = nullptr;
  if (prevSelectedObject==o) prevSelectedObject = nullptr;
  // remove connections if any
  TrackSegment* t = (TrackSegment*)o->getConnectA();
  if (t!=nullptr) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectB();
  if (t!=nullptr) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectC();
  if (t!=nullptr) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectD();
  if (t!=nullptr) removeTrackSegment(t);
  // decrement Block use count(s)
  LayoutBlock* b = o->getLayoutBlock();
  if (b!=nullptr) b->decrementUse();
  if ( (o->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
          (o->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
              (o->getTurnoutType()==LayoutTurnout::LH_XOVER) )
  {
   LayoutBlock* b2 = o->getLayoutBlockB();
   if ( (b2!=nullptr) && (b2!=b) ) b2->decrementUse();
   LayoutBlock* b3 = o->getLayoutBlockC();
   if ( (b3!=nullptr) && (b3!=b) && (b3!=b2) ) b3->decrementUse();
   LayoutBlock* b4 = o->getLayoutBlockD();
   if ( (b4!=nullptr) && (b4!=b) &&
                  (b4!=b2) && (b4!=b3) ) b4->decrementUse();
  }
  // delete from array
  if (layoutTrackList->contains(o)) {
      layoutTrackList->removeOne(o);
      setDirty();
      redrawPanel();
      return true;
  }
  return(false);
}
/*private*/ void LayoutEditor::substituteAnchor(QPointF loc, QObject* o, TrackSegment* t)
{
    PositionablePoint* p = addAnchor(loc);
    if (t->getConnect1() == o) {
        t->setNewConnect1(p, POS_POINT);
    }
    if (t->getConnect2() == o) {
        t->setNewConnect2(p, POS_POINT);
    }
    p->setTrackConnection(t);
}

/*protected*/ bool LayoutEditor::removeLayoutSlip (LayoutTurnout* o)
{
 //if(!(o instanceof LayoutSlip)){
 if(qobject_cast<LayoutSlip*>(o)==nullptr)
 {
     return false;
 }
 // First verify with the user that this is really wanted
 if (!noWarnSlip)
 {
//     int selectedValue = JOptionPane.showOptionDialog(this,
//             rb.getQString("Question5"),rb.getQString("WarningTitle"),
//             JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,nullptr,
//             new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
//             rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
//     if (selectedValue == 1) return(false);   // return without creating if "No" response
//     if (selectedValue == 2) {
//         // Suppress future warnings, and continue
//         noWarnSlip = true;
//     }
     switch(QMessageBox::question(this,tr("Warning"),tr("Are you sure that you want to remove this slip turnout from the panel along with any connected track segments? Ignore will continue and suppress further messages like this."),QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore))
     {
     case QMessageBox::Yes:
      break;
     case QMessageBox::Ignore:
      noWarnSlip = true;
      break;
     default:
     case QMessageBox::No:
      return false; // return without creating if "No" response
    }

 }
 // remove from selection information
 if (selectedObject==o) selectedObject = nullptr;
 if (prevSelectedObject==o) prevSelectedObject = nullptr;
 // remove connections if any
 TrackSegment* t = (TrackSegment*)o->getConnectA();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectB();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectC();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectD();
 if (t!=nullptr) removeTrackSegment(t);
 // decrement block use count if any blocks in use
 LayoutBlock* lb = o->getLayoutBlock();
 if (lb != nullptr) lb->decrementUse();

 // delete from array
 if (layoutTrackList->contains(o)) {
     layoutTrackList->removeOne(o);
     o->remove();
     setDirty();
     redrawPanel();
     return true;
 }

 return(false);
}

/**
* Remove a Level Crossing
*/
/*protected*/ bool LayoutEditor::removeLevelXing (LevelXing* o)
{
  // First verify with the user that this is really wanted
  if (!noWarnLevelXing)
  {
//      int selectedValue = JOptionPane.showOptionDialog(this,
//              rb.getQString("Question3"),rb.getQString("WarningTitle"),
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,nullptr,
//              new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
//              rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
//      if (selectedValue == 1) return(false);   // return without creating if "No" response
//      if (selectedValue == 2) {
//          // Suppress future warnings, and continue
//          noWarnLevelXing = true;
//      }
switch(QMessageBox::question(this,tr("Warning"),tr("Are you sure that you want to remove this crossing from the panel along with any connected track segments? Ignore will continue and suppress further messages like this."),QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore))  {
  case QMessageBox::Yes:
   break;
  case QMessageBox::Ignore:
   noWarnLevelXing = true;
   break;
  default:
  case QMessageBox::No:
   return false; // return without creating if "No" response
  }
 }
 // remove from selection information
 if (selectedObject==o) selectedObject = nullptr;
 if (prevSelectedObject==o) prevSelectedObject = nullptr;
 // remove connections if any
 TrackSegment* t = (TrackSegment*)o->getConnectA();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectB();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectC();
 if (t!=nullptr) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectD();
 if (t!=nullptr) removeTrackSegment(t);
  // decrement block use count if any blocks in use
 LayoutBlock* lb = o->getLayoutBlockAC();
 if (lb != nullptr) lb->decrementUse();
 LayoutBlock* lbx = o->getLayoutBlockBD();
 if (lbx!=nullptr && lb!=nullptr && lbx!=lb) lb->decrementUse();
 // delete from array
 if (layoutTrackList->contains(o)) {
     layoutTrackList->removeOne(o);
     o->remove();
     setDirty();
     redrawPanel();
     return true;
 }
 return(false);
}
void LayoutEditor::on_actionShow_turnout_circles_toggled(bool bState)
{
 turnoutCirclesWithoutEditMode = bState;
 ui->actionShow_turnout_circles->setChecked(bState);
 paintTargetPanel(editScene);
}
/**
* Add a checkbox to set visibility of the Positionable item
*/
/*public*/ void LayoutEditor::setHiddenMenu(Positionable* p, QMenu* popup)
{
  if (p->getDisplayLevel() == BKG ) {
      return;
  }
//  JCheckBoxMenuItem hideItem = new JCheckBoxMenuItem(tr("SetHidden"));
//  hideItem->setChecked(p->isHidden());
//  hideItem.addActionListener(new ActionListener(){
//      Positionable comp;
//      JCheckBoxMenuItem checkBox;
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          comp.setHidden(checkBox->isChecked());
//          setSelectionsHidden(checkBox->isChecked(), comp);
//      }
//      ActionListener init(Positionable pos, JCheckBoxMenuItem cb) {
//          comp = pos;
//          checkBox = cb;
//          return this;
//      }
//  }.init(p, hideItem));
//  popup.add(hideItem);
  QAction* hiddenAction = new QAction(tr("Hide when not editing"),this);
  hiddenAction->setCheckable(true);
  hiddenAction->setChecked(p->isHidden());
  connect(hiddenAction, SIGNAL(toggled(bool)), this, SLOT(On_actionHidden_toggled(bool)));
  popup->addAction(hiddenAction);
  saveP = p;
}
void LayoutEditor::On_actionHidden_toggled(bool bState)
{
 Positionable* comp =saveP;
 //comp.setHidden(checkBox->isChecked());
 setSelectionsHidden(bState, comp);
}
/*protected*/ void LayoutEditor::setSelectionsHidden(bool enabled, Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p->self());
 Q_ASSERT(pl != nullptr);
 if (_selectionGroup!=nullptr && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i))->setHidden(enabled);
  }
 }
}
void LayoutEditor::on_actionEdit_track_width_triggered()
{
 SetTrackWidthDlg dlg(sidelineTrackWidth, mainlineTrackWidth, this);
 if(dlg.exec() == QDialog::Accepted)
 {
  sidelineTrackWidth = dlg.sidetrackWidth();
  mainlineTrackWidth = dlg.mainlineTrackWidth();
 }
}

/*protected*/ void LayoutEditor::addBackgroundColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup, const QString name, QColor color)
{
 QVariant var = color;
 QAction* act = new QAction( name, this);
 act->setCheckable(true);
 if( defaultBackgroundColor == color)
  act->setChecked(true);
 act->setData(var);
 colorButtonGroup->addAction(act);
 menu->addAction(act);
}

void LayoutEditor::addBackgroundColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color) {
//    ActionListener a = new ActionListener() {
//        //final String desiredName = name;
//        final Color desiredColor = color;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (!defaultBackgroundColor.equals(desiredColor)) {
//                defaultBackgroundColor = desiredColor;
//                setBackgroundColor(desiredColor);
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    QAction* r = new QAction(getColourIcon(color),name,this);
    r->setCheckable(true);
    backgroundColorButtonMapper->setMapping(r, backgroundColorCount);
    //r.addActionListener(a);
    connect(r, SIGNAL(triggered()), backgroundColorButtonMapper, SLOT(map()));
    backgroundColorButtonGroup->addAction(r);

    if (defaultBackgroundColor == (color)) {
        r->setChecked(true);
    } else {
        r->setChecked(false);
    }
    menu->addAction(r);
    backgroundColorMenuItems->replace(backgroundColorCount, r);
    backgroundColors->replace(backgroundColorCount, color);
    backgroundColorCount++;
}   //addBackgroundColorMenuEntry


void LayoutEditor::addTrackColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color) {
//    ActionListener a = new ActionListener() {
//        /*final*/ QColor desiredColor = color;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (!defaultTrackQColor(Qt::equals(desiredColor)) {
//                LayoutTrack::setDefaultTrackColor(desiredColor);
//                defaultTrackColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    //QAction r = new QAction(name);
    QAction* r = new QAction(getColourIcon(color), name, this);
    r->setCheckable(true);
    trackColorButtonMapper->setMapping(r, trackColorCount);
    connect(r, SIGNAL(triggered(bool)), trackColorButtonMapper, SLOT(map()));
    r->setCheckable(true);

    //r.addActionListener(a);
    trackColorButtonGroup->addAction(r);

    if (defaultTrackColor == (color)) {
        r->setChecked(true);
    } else {
        r->setChecked(false);
    }
    menu->addAction(r);
    trackColorMenuItems->replace(trackColorCount, r);
    trackColors->replace(trackColorCount, color);
    trackColorCount++;
}   //addTrackColorMenuEntry

void LayoutEditor::on_addTrackColorMenuEntry_triggered(int i)
{
 QColor desiredColor = trackColors->at(i);
 if (defaultTrackColor!=(desiredColor)) {
     LayoutTrack::setDefaultTrackColor(desiredColor);
     defaultTrackColor = desiredColor;
     setDirty(true);
     repaint();
 }
}

void LayoutEditor::addTrackOccupiedColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color) {
//    ActionListener a = new ActionListener() {
//        //final String desiredName = name;
//        final Color desiredColor = color;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (!defaultOccupiedTrackQColor(Qt::equals(desiredColor)) {
//                defaultOccupiedTrackColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    QAction* r = new QAction(getColourIcon(color), name, this);
    r->setCheckable(true);
    trackColorButtonMapper->setMapping(r, trackOccupiedColorCount);
    //r.addActionListener(a);
    connect(r, SIGNAL(triggered(bool)), trackColorButtonMapper, SLOT(map()));
    trackOccupiedColorButtonGroup->addAction(r);

    if (defaultOccupiedTrackColor == (color)) {
        r->setChecked(true);
    } else {
        r->setChecked(false);
    }
    menu->addAction(r);
    trackOccupiedColorMenuItems->replace(trackOccupiedColorCount, r);
    trackOccupiedColors->replace(trackOccupiedColorCount, color);
    trackOccupiedColorCount++;
}   //addTrackOccupiedColorMenuEntry

void LayoutEditor::on_addTrackOccupiedColorMenuEntry_triggered(int i)
{
 QColor desiredColor = trackOccupiedColors->at(i);
 if (defaultOccupiedTrackColor != desiredColor)
 {
     defaultOccupiedTrackColor = desiredColor;
     setDirty(true);
     repaint();
 }
}
void LayoutEditor::addTrackAlternativeColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color) {
//    ActionListener a = new ActionListener() {
//        //final String desiredName = name;
//        final Color desiredColor = color;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (!defaultAlternativeTrackQColor(Qt::equals(desiredColor)) {
//                defaultAlternativeTrackColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    QAction* r = new QAction(getColourIcon(color), name, this);
    r->setCheckable(true);
    trackAlternativeColorButtonMapper->setMapping(r, trackAlternativeColorCount);
    //r.addActionListener(a);
    connect(r, SIGNAL(triggered()), trackAlternativeColorButtonMapper, SLOT(map()) );
    trackAlternativeColorButtonGroup->addAction(r);

    if (defaultAlternativeTrackColor ==(color)) {
        r->setChecked(true);
    } else {
        r->setChecked(false);
    }
    menu->addAction(r);
    trackAlternativeColorMenuItems->replace(trackAlternativeColorCount, r);
    trackAlternativeColors->replace(trackAlternativeColorCount,color);
    trackAlternativeColorCount++;
}   //addTrackAlternativeColorMenuEntry

void LayoutEditor::on_addTrackAlternativeColorMenuEntry_triggered(int i)
{
 QColor desiredColor = trackAlternativeColors->at(i);
 if (defaultAlternativeTrackColor != (desiredColor)) {
     defaultAlternativeTrackColor = desiredColor;
     setDirty(true);
     repaint();
 }
}

/*protected*/ void LayoutEditor::setOptionMenuTrackColor() {
    for (int i = 0; i < trackColorCount; i++) {
        trackColorMenuItems->at(i)->setChecked(trackColors->at(i) == (defaultTrackColor));
    }

    for (int i = 0; i < trackOccupiedColorCount; i++) {
        trackOccupiedColorMenuItems->at(i)->setChecked(trackOccupiedColors->at(i) == (defaultOccupiedTrackColor));
    }

    for (int i = 0; i < trackAlternativeColorCount; i++) {
        trackAlternativeColorMenuItems->at(i)->setChecked(trackAlternativeColors->at(i) == (defaultAlternativeTrackColor));
    }
}   //setOptionMenuTrackColor

void LayoutEditor::addTextColorMenuEntry(QMenu* menu, /*final*/ QString name, /*final*/ QColor color) {
//    ActionListener a = new ActionListener() {
//        //final String desiredName = name;
//        final Color desiredColor = color;

//        @Override
//        public void actionPerformed(ActionEvent e) {
//            if (!defaultTextColor == (desiredColor)) {
//                defaultTextColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    QAction* r = new QAction(getColourIcon(color), name, this);
    r->setCheckable(true);
    textColorButtonMapper->setMapping(r, textColorCount);
    connect(r, SIGNAL(triggered()), textColorButtonMapper, SLOT(map()));
    //r.addActionListener(a);
    textColorButtonGroup->addAction(r);

    if (defaultTextColor == (color)) {
        r->setChecked(true);
    } else {
        r->setChecked(false);
    }
    menu->addAction(r);
    textColorMenuItems->replace(textColorCount, r);
    textColors->replace(textColorCount, color);
    textColorCount++;
}   //addTextColorMenuEntry


/*protected*/ void LayoutEditor::setOptionMenuTurnoutCircleColor()
{
 for (int i = 0; i < turnoutCircleColorCount; i++)
 {
     if ((turnoutCircleColors->at(i) == QColor()) && (turnoutCircleColor == QColor())) {
         turnoutCircleColorMenuItems->at(i)->setChecked(true);
     } else if ((turnoutCircleColors->at(i) != QColor()) && turnoutCircleColors->at(i) == (turnoutCircleColor)) {
         turnoutCircleColorMenuItems->at(i)->setChecked(true);
     } else {
         turnoutCircleColorMenuItems->at(i)->setChecked(false);
     }
 }
}   //setOptionMenuTurnoutCircleColor

/*protected*/ void LayoutEditor::setOptionMenuTurnoutCircleSize()
{
 for (int i = 0; i < turnoutCircleSizeCount; i++)
 {
  if (turnoutCircleSizes->at(i) == getTurnoutCircleSize())
  {
   turnoutCircleSizeMenuItems->at(i)->setChecked(true);
  }
  else
  {
   turnoutCircleSizeMenuItems->at(i)->setChecked(false);
  }
 }
}   //setOptionMenuTurnoutCircleSize

/*protected*/ void LayoutEditor::setOptionMenuTextColor() {
    for (int i = 0; i < textColorCount; i++) {
        if (textColors->at(i) == (defaultTextColor)) {
            textColorMenuItems->at(i)->setChecked(true);
        } else {
            textColorMenuItems->at(i)->setChecked(false);
        }
    }
}   //setOptionMenuTextColor

/*protected*/ void LayoutEditor::setOptionMenuBackgroundColor() {
    for (int i = 0; i < backgroundColorCount; i++) {
        if (backgroundColors->at(i) == (defaultBackgroundColor)) {
            backgroundColorMenuItems->at(i)->setChecked(true);
        } else {
            backgroundColorMenuItems->at(i)->setChecked(false);
        }
    }
}   //setOptionMenuBackgroundColor

void LayoutEditor::on_colorBackgroundMenuItemSelected(int i)
{
 QColor color = backgroundColors->at(i);
 editPanel->setBackgroundBrush(QBrush(color, Qt::SolidPattern));
}

void LayoutEditor::on_actionAdd_reporter_label_triggered()
{
 AddReporterDlg* dlg = new AddReporterDlg(this);
 if(dlg->exec() == QDialog::Accepted)
 {
   QString rName = dlg->getName();
   QPoint loc = dlg->getLoc();
   addReporter(rName,loc.x(),loc.y());
 }
}

void LayoutEditor::on_actionAdd_background_image_2_triggered()
{
 addBackground();
 setDirty(true);
 repaint();
}
#if 0
/**
 * Determine right side x of furthest right background
 */
/*private*/ int LayoutEditor::getNextBackgroundLeft()
{
  int left = 0;
  // place to right of background images, if any
  for (int i=0; i<_contents->size(); i++)
  {
   Positionable* p = _contents->at(i);
   if (qobject_cast<PositionableLabel*>(p)!= nullptr)
   {
    PositionableLabel* l = (PositionableLabel*)p;
    if (l->isBackground())
    {
     int test = l->getX() + l->maxWidth();
     if (test>left) left = test;
    }
   }
  }
  return left;
}

void LayoutEditor::on_actionLoad_Other_XML_triggered()
{
 setCursor(Qt::WaitCursor);
 QString fileName = QFileDialog::getOpenFileName(this,tr("Load XML file"), QDir::homePath(), tr("Layout XML files (*.xml)"));
 setCursor(Qt::ArrowCursor);
 if(!fileName.isEmpty())
 {
  LoadXml xml(this);
  setCursor(Qt::WaitCursor);
  xml.loadfile(fileName);
  setCursor(Qt::ArrowCursor);
  //ui->actionSave->setEnabled(true);
  //ui->actionSave_as->setEnabled(true);
  ui->actionLoad_Other_XML->setEnabled(false);
  ui->actionLoad_XML->setEnabled(false);
 }
}

void LayoutEditor::on_actionLoad_XML_triggered()
{
//  LoadXml xml(this);
// connect(&xml, SIGNAL(newSensor(QString,int,int)), this, SLOT(on_newSensor(QString,int,int)));
 setCursor(Qt::WaitCursor);
//  xml.loadfile(QDir::homePath() + "/.jmri/mylayout.xml");
 bool bResult = static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->load(new File(QDir::homePath() + "/.jmri/mylayout.xml"));
 layoutFile = QDir::homePath() + "/.jmri/mylayout.xml";
 setCursor(Qt::ArrowCursor);
// ui->actionSave->setEnabled(true);
// ui->actionSave_as->setEnabled(true);
 ui->actionLoad_Other_XML->setEnabled(false);
 ui->actionLoad_XML->setEnabled(false);
}

void LayoutEditor::on_newSensor(QString name, int x, int y)
{
 QPoint p(x,y);
 xLoc = p.x();
 yLoc = p.y();

 addSensor(name);
}
#endif
void LayoutEditor::setFilename(QString path)
{
 layoutFile = path;
 if(path != nullptr)
  ui->actionSave->setEnabled(true);
}

void LayoutEditor::on_actionSave_triggered()
{
 if(layoutFile.isEmpty())
 {
  //on_actionSave_as_triggered();
  savePanels->actionPerformed();
 }
 setCursor(Qt::WaitCursor);
 makeBackupFile(layoutFile);

 savePanels->saveFile(layoutFile);

 setCursor(Qt::ArrowCursor);
}

void LayoutEditor::on_actionSnap_to_grid_when_adding_toggled(bool bState)
{
 snapToGridOnAdd = bState;
 ui->actionSnap_to_grid_when_adding->setChecked(bState);
}
void LayoutEditor::on_actionSnap_to_grid_when_moving_toggled(bool bState)
{
 snapToGridOnMove = bState;
 ui->actionSnap_to_grid_when_moving->setChecked(bState);
}
void LayoutEditor::OnZoom_selected(QAction *act)
{
 double scale = act->data().toDouble();
 if(scale == xScale)
  return;
 if(xScale > 1.0)
  editPanel->scale(1.0/xScale, 1.0/yScale);

 editPanel->scale(scale, scale);
 xScale = yScale = scale;
}
void LayoutEditor::setScale(double scaleX, double scaleY)
{
 if(scaleX == 1.0)
  ui->actionNo_zoom->setChecked(true);
 else if(scaleX == 1.5)
  ui->actionX_1_5->setChecked(true);
 else if(scaleX == 2.0)
  ui->actionX_2_0->setChecked(true);
 else if(scaleX == 3.0)
  ui->actionX_3_0->setChecked(true);
 else if(scaleX == 4.0)
  ui->actionX_4_0->setChecked(true);
 xScale = scaleX;
 yScale = scaleY;
// editPanel->scale(scaleX, scaleY);
}
const QIcon LayoutEditor::getColourIcon(QColor color)
{
 Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
 // BufferedImage image = new BufferedImage(ICON_DIMENSION,  ICON_DIMENSION,
 // BufferedImage.TYPE_INT_RGB);
 QImage resultImage =  QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

 // Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
painter.fillRect(resultImage.rect(), brBkgnd);
painter.end();
// ImageIcon icon = new ImageIcon(image);
QIcon icon =  QIcon(QPixmap::fromImage(resultImage));
return icon;
}
void LayoutEditor::OnDefaultTrackColorSelected(QAction *act)
{
 QColor c = act->data().value<QColor>();
 Q_ASSERT(c.isValid());

 defaultTrackColor = c;
}

void LayoutEditor::setDefaultTextColor(QString color)
{
 defaultTextColor = ColorUtil::stringToColor(color);
 setOptionMenuTextColor();
}

/**
 * @param color value to set the default text color to.
 */
/*public*/ void LayoutEditor::setDefaultTextColor(/*@Nonnull*/ QColor color) {
    defaultTextColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ void LayoutEditor::setDefaultBackgroundColor(QString color) {
        defaultBackgroundColor = ColorUtil::stringToColor(color);
        setOptionMenuBackgroundColor();
    }
void LayoutEditor::OnDefaultTextColorSelected(int i)
{
 QColor c = textColors->at(i);
 defaultTextColor = c;
}


/*public*/ QString LayoutEditor::getLayoutName() {return layoutName;}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getShowHelpBar() {
    return showHelpBar;
}

/*public*/ void LayoutEditor::setLayoutName(QString name)
{
 layoutName = name;
 setWindowTitle("LayoutEditor - "+name);
}
//QString MyLayoutEditor::colorToString(QColor c)
//{
// for(int i=0; i < _colors.size(); i++)
// {
//  if(c == _colors.at(i))
//   return _Colors.at(i).toLower();
// }
// return "";
//}
QColor LayoutEditor::getBackgroundColor()
{
 QBrush b = editPanel->backgroundBrush();
 if(b == Qt::NoBrush)
  return QColor(Qt::white);
 return b.color();
}
void LayoutEditor::on_actionDelete_this_panel_triggered()
{
 editScene->clear();
 _contents->clear();
 //turnoutList->clear();
 layoutTrackList->clear();
 //pointList->clear();
 //xingList->clear();
 //slipList->clear();
 //turntableList->clear();
 highlightRect = nullptr;
 panelGridGroup = nullptr;
 ui->actionLoad_Other_XML->setEnabled(true);
 ui->actionLoad_XML->setEnabled(true);
// ui->actionSave->setEnabled(false);
// ui->actionSave_as->setEnabled(false);
// ?? InstanceManager::setLayoutBlockManager(new LayoutBlockManager());
}

/*public*/ void LayoutEditor::loadFailed() {
 _loadFailed = true;
}
/**
*
*/
/*public*/ NamedIcon* LayoutEditor::loadFailed(QString /*msg*/, QString url) {
 if (_debug) log->debug("loadFailed _ignore= "+QString(_ignore?"ignore":"accept"));
 QString goodUrl = _urlMap->value(url);
 if (goodUrl!=nullptr) {
     return NamedIcon::getIconByName(goodUrl);
 }
 if (_ignore) {
     _loadFailed = true;
     return new NamedIcon(url, url);
 }
 _newIcon = nullptr;
 _delete = false;
 // TODO: new UrlErrorDialog(msg, url);

 if (_delete) {
     if (_debug) log->debug("loadFailed _delete= "+_delete);
     return nullptr;
 }
 if (_newIcon==nullptr) {
     _loadFailed = true;
     _newIcon =new NamedIcon(url, url);
 }
 if (_debug) log->debug("loadFailed icon nullptr= "+(_newIcon==nullptr));
 return _newIcon;
}

void LayoutEditor::on_actionAdd_loco_from_roster_triggered()
{
 locoMarkerFromRoster();
}

 void LayoutEditor::on_actionSkip_unsignalled_Internal_Turnouts_toggled(bool bState)
 {
  skipIncludedTurnout = bState;
 }

 void LayoutEditor::on_actionSet_Signals_at_Block_Boundary_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtBlockBoundary(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Turnout_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Crossover_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtXoverTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Level_Crossing_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtLevelXing(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Slip_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtSlip(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Throat_to_Throat_Turnouts_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtTToTTurnouts(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Three_Way_Turnout()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAt3WayTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionEntry_Exit_triggered()
 {
  if (tools == nullptr)
  {
   tools = new LayoutEditorTools(this);
  }
  AddEntryExitPairAction act("", this, this);
  act.actionPerformed();
 }

 void LayoutEditor::on_actionAdd_Fast_Clock_triggered()
 {
  addClock();
 }
 /*public*/ ConnectivityUtil* LayoutEditor::getConnectivityUtil() {
     if (conTools == nullptr) {
         conTools = new ConnectivityUtil(/*thisPanel*/this);
     }
     if (conTools==nullptr) log->error("Unable to establish link to Connectivity Tools for Layout Editor panel "+layoutName);
     return conTools;
 }

/*public*/ LayoutEditorTools* LayoutEditor::getLETools() {
    if (tools == nullptr) {
        tools = new LayoutEditorTools(/*thisPanel*/this);
    }
    if (tools==nullptr) log->error("Unable to establish link to Layout Editor Tools for Layout Editor panel "+layoutName);
    return tools;
}
 /*public*/ LayoutEditorAuxTools* LayoutEditor::getLEAuxTools()
 {
    if (auxTools == nullptr) {
        auxTools = new LayoutEditorAuxTools(this);
    }
    return auxTools;
}

 /*public*/ LayoutTrackEditors* LayoutEditor::getLayoutTrackEditors() {
    if (layoutTrackEditors == nullptr) {
        layoutTrackEditors = new LayoutTrackEditors(this);
    }
    return layoutTrackEditors;
}

 /*public*/ LayoutEditorChecks* LayoutEditor::getLEChecks()
 {
    if (layoutEditorChecks == nullptr) {
        layoutEditorChecks = new LayoutEditorChecks(this);
    }
    return layoutEditorChecks;
}
/*public*/ void LayoutEditor::addToPopUpMenu(NamedBean* nb, QMenu* item, int menu)
{
 if(nb==nullptr || item==nullptr){
     return;
 }
 //if(nb instanceof Sensor)
 if(qobject_cast<Sensor*>(nb)!=nullptr)
 {
     foreach(SensorIcon* si, *sensorList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=nullptr){
             switch(menu){
                 case VIEWPOPUPONLY : si->getPopupUtility()->addViewPopUpMenu(item); break;
                 case EDITPOPUPONLY : si->getPopupUtility()->addEditPopUpMenu(item); break;
                 default: si->getPopupUtility()->addEditPopUpMenu(item);
                          si->getPopupUtility()->addViewPopUpMenu(item);
             }
         }
     }
 }
 else
  //if (nb instanceof SignalHead)
  if(qobject_cast<SignalHead*>(nb)!=nullptr)
  {
     foreach(SignalHeadIcon* si, *signalList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=nullptr){
             switch(menu){
                 case VIEWPOPUPONLY : si->getPopupUtility()->addViewPopUpMenu(item); break;
                 case EDITPOPUPONLY : si->getPopupUtility()->addEditPopUpMenu(item); break;
                 default: si->getPopupUtility()->addEditPopUpMenu(item);
                          si->getPopupUtility()->addViewPopUpMenu(item);
             }
         }
     }
 }
 else
 //if (nb instanceof SignalMast)
 if(qobject_cast<SignalMast*>(nb)!=nullptr)
  {
     foreach(SignalMastIcon* si,*signalMastList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=nullptr){
             switch(menu){
                 case VIEWPOPUPONLY : si->getPopupUtility()->addViewPopUpMenu(item); break;
                 case EDITPOPUPONLY : si->getPopupUtility()->addEditPopUpMenu(item); break;
                 default: si->getPopupUtility()->addEditPopUpMenu(item);
                          si->getPopupUtility()->addViewPopUpMenu(item);
             }
         }
     }
 }
 else
 //if (nb instanceof Memory)
 if(qobject_cast<Memory*>(nb)!=nullptr)
 {
  foreach(LEMemoryIcon* si, *memoryLabelList)
  {
   if(si->getNamedBean()==nb && si->getPopupUtility()!=nullptr)
   {
    switch(menu)
    {
     case VIEWPOPUPONLY : si->getPopupUtility()->addViewPopUpMenu(item); break;
     case EDITPOPUPONLY : si->getPopupUtility()->addEditPopUpMenu(item); break;
     default: si->getPopupUtility()->addEditPopUpMenu(item);
              si->getPopupUtility()->addViewPopUpMenu(item);
    }
   }
  }
 }
 else
 //if (nb instanceof Turnout)
 if(qobject_cast<Turnout*>(nb)!=nullptr)
 {
  for (LayoutTurnout* lt : getLayoutTurnoutsAndSlips()) {
  {
   if(lt->getTurnout()==(nb))
   {
    switch(menu)
    {
     case VIEWPOPUPONLY : lt->addViewPopUpMenu(item); break;
     case EDITPOPUPONLY : lt->addEditPopUpMenu(item); break;
     default: lt->addEditPopUpMenu(item);
              lt->addViewPopUpMenu(item);
    }
    break;
   }
  }
//  foreach(LayoutSlip* ls, *slipList)
//  {
//   if(ls->getTurnout()==nb||ls->getTurnoutB()==nb)
//   {
//    switch(menu)
//    {
//     case VIEWPOPUPONLY : ls->addViewPopUpMenu(item); break;
//     case EDITPOPUPONLY : ls->addEditPopUpMenu(item); break;
//     default: ls->addEditPopUpMenu(item);
//              ls->addViewPopUpMenu(item);
//    }
//    break;
//   }
  }
 }
}
/**
* Invoke a window to allow you to add a MultiSensor indicator to the target
*/
void LayoutEditor::startMultiSensor() {
 multiLocX = xLoc;
 multiLocY = yLoc;
#if 1
 if (multiSensorFrame == nullptr) {
     // create a common edit frame
     multiSensorFrame = new MultiSensorIconFrame(this);
     multiSensorFrame->initComponents();
     multiSensorFrame->pack();
 }
 multiSensorFrame->setVisible(true);
#endif
}
// Invoked when window has new multi-sensor ready
/*public*/ void LayoutEditor::addMultiSensor(MultiSensorIcon* l)
{
 ((Positionable*)l)->setLocation(multiLocX,multiLocY);
 setDirty(true);
 putItem((Positionable*)l);
 //multiSensorFrame = nullptr;
}

void LayoutEditor::onChangeIconsButton()
{
 if (ui->sensorButton->isChecked()) {
     sensorFrame->setVisible(true);
 } else if (ui->signalButton->isChecked()) {
     signalFrame->setVisible(true);
 } else if (ui->iconLabelButton->isChecked()) {
     iconFrame->setVisible(true);
 } else {
     //explain to the user why nothing happens
     JOptionPane::showMessageDialog(nullptr, tr("This only works when a Sensor, Signal Head or\nLabel is selected to the right of this button."),
             tr("Change Icons"), JOptionPane::INFORMATION_MESSAGE);
 }

}
void LayoutEditor::closeEvent(QCloseEvent *)
{
 bool save = (isDirty() || (savedEditMode!=isEditable()) || (savedPositionable!=allPositionable()) || (savedControlLayout!=allControlling()) ||	(savedAnimatingLayout!=animatingLayout) ||	 (savedShowHelpBar!=showHelpBar) );
 targetWindowClosing(save);
}

/*public*/ void LayoutEditor::makeBackupFile(QString name)
{
 XmlFile* xmlfile = new XmlFile;
 QFile* file = xmlfile->findFile(name);
 if (file == nullptr)
 {
  log->info("No " + name + " file to backup");
 }
 else
 {
  QFileInfo info(file->fileName());

  QString backupName = xmlfile->backupFileName(info.absoluteFilePath());
  QFile* backupFile = xmlfile->findFile(backupName);
  if (backupFile != nullptr)
  {
   if (backupFile->remove())
   {
    log->debug("deleted backup file " + backupName);
   }
  }
  if (file->rename(backupName))
  {
   log->debug("created new backup file " + backupName);
  }
  else
  {
   log->error("could not create backup file " + backupName);
  }
 }
}
/*=========================================*\
|* Dialog box to enter move selection info *|
\*=========================================*/

//display dialog for translation a selection
/*protected*/ void LayoutEditor::moveSelection()
{
    if (!selectionActive || (selectionWidth == 0.0) || (selectionHeight == 0.0)) {
        //no selection has been made - nothing to move
        JOptionPane::showMessageDialog(this, tr("Error - Cannot translate selection because no selection has been made.\nPlease select by dragging with the mouse and try again."),
                tr("Error"), JOptionPane::ERROR_MESSAGE);

        return;
    }

    if (moveSelectionOpen) {
        moveSelectionFrame->setVisible(true);
        return;
    }

    //Initialize if needed
    if (moveSelectionFrame == nullptr) {
        moveSelectionFrame = new JmriJFrame(tr("Translate Selection"));
        moveSelectionFrame->addHelpMenu("package.jmri.jmrit.display.TranslateSelection", true);
        moveSelectionFrame->setLocation(70, 30);
        QWidget* theContentPane = moveSelectionFrame->getContentPane(false);
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

        //setup x translate
        QWidget* panel31 = new QWidget();
        panel31->setLayout(new FlowLayout());
        QLabel* xMoveLabel = new QLabel(tr("Horizontal (x) Translation:"));
        panel31->layout()->addWidget(xMoveLabel);
        panel31->layout()->addWidget(xMoveField);
        xMoveField->setToolTip(tr("Enter units to move (0 = don't move; negative = move left; positive = move right)."));
        theContentPane->layout()->addWidget(panel31);

        //setup y translate
        QWidget* panel32 = new QWidget();
        panel32->setLayout(new FlowLayout());
        QLabel* yMoveLabel = new QLabel(tr("Vertical (y) Translation:"));
        panel32->layout()->addWidget(yMoveLabel);
        panel32->layout()->addWidget(yMoveField);
        yMoveField->setToolTip(tr("Enter units to move (0 = don't move; negative = move up; positive = move down)."));
        theContentPane->layout()->addWidget(panel32);

        //setup information message
        QWidget* panel33 = new QWidget();
        panel33->setLayout(new FlowLayout());
        QLabel* message1Label = new QLabel(tr("Only items within selection rectangle will be moved."));
        panel33->layout()->addWidget(message1Label);
        theContentPane->layout()->addWidget(panel33);

        //set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5->setLayout(new FlowLayout());
        panel5->layout()->addWidget(moveSelectionDone = new QPushButton(tr("Move Selection")));
//        moveSelectionDone.addActionListener((ActionEvent event) -> {
//            moveSelectionDonePressed(event);
//        });
        connect(moveSelectionDone, SIGNAL(clicked(bool)), this, SLOT(moveSelectionDonePressed()));
        moveSelectionDone->setToolTip(tr("Click here to move items within the selection rectangle."));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(moveSelectionDone);
//            rootPane.setDefaultButton(moveSelectionDone);
//        });
//        setDefaultButton(moveSelectionDone);
        panel5->layout()->addWidget(moveSelectionCancel = new QPushButton(tr("Cancel")));
//        moveSelectionCancel.addActionListener((ActionEvent event) -> {
//            moveSelectionCancelPressed();
//        });
        connect(moveSelectionCancel, SIGNAL(clicked(bool)), this, SLOT(moveSelectionCancelPressed()));
        moveSelectionCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPane->layout()->addWidget(panel5);
    }

    //Set up for Entry of Translation
    xMoveField->setText("0");
    yMoveField->setText("0");
//    moveSelectionFrame.addWindowListener(new WindowAdapter() {
//        @Override
//        public void windowClosing(WindowEvent event) {
//            moveSelectionCancelPressed();
//        }
//    });
    moveSelectionFrame->addWindowListener((WindowListener*)this);
    moveSelectionFrame->pack();
    moveSelectionFrame->setVisible(true);
    moveSelectionOpen = true;
}

/*public*/ void LayoutEditor::windowClosing(QCloseEvent* event) {
    moveSelectionCancelPressed();
}

void LayoutEditor::moveSelectionDonePressed(/*@Nonnull ActionEvent event*/) {
    QString newText = "";
    double xTranslation = 0.0F;
    double yTranslation = 0.0F;

    //get x translation
    newText = xMoveField->text().trimmed();
    bool bok;
        xTranslation = newText.toDouble(&bok);
    if(!bok) {
        JOptionPane::showMessageDialog(moveSelectionFrame,
                QString("%1: %2 %3").arg(tr("Error in entry")).arg(
                        tr("invalid floating point format")).arg(tr("Try Again")),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    //get y translation
    newText = yMoveField->text().trimmed();
    yTranslation = newText.toFloat(&bok);
    if(!bok) {
     JOptionPane::showMessageDialog(moveSelectionFrame,
             QString("%1: %2 %3").arg(tr("Error in entry")).arg(
                     tr("invalid floating point format")).arg(tr("Try Again")),
             tr("Error"),
             JOptionPane::ERROR_MESSAGE);


        return;
    }

    //here when all numbers read in - translation if entered
    if ((xTranslation != 0.0) || (yTranslation != 0.0)) {
        QRectF selectionRect = getSelectionRect();

        //set up undo information
        undoRect = MathUtil::offset(selectionRect, xTranslation, yTranslation);
        undoDeltaX = -xTranslation;
        undoDeltaY = -yTranslation;
        canUndoMoveSelection = true;

        //apply translation to icon items within the selection
        QList<Positionable*> contents = getContents();

        for (Positionable* c : contents) {
            QPointF upperLeft = c->getLocation();

            if (selectionRect.contains(upperLeft)) {
                int xNew = (int) (upperLeft.x() + xTranslation);
                int yNew = (int) (upperLeft.y() + yTranslation);
                c->setLocation(xNew, yNew);
            }
        }

        QPointF delta = QPointF(xTranslation, yTranslation);
        for (LayoutTrack* lt : *layoutTrackList) {
            QPointF center = lt->getCoordsCenter();
            if (selectionRect.contains(center)) {
                lt->setCoordsCenter(MathUtil::add(center, delta));
            }

        }
        selectionX = undoRect.x();
        selectionY = undoRect.y();
        selectionWidth = undoRect.width();
        selectionHeight = undoRect.height();
        resizePanelBounds(false);
        setDirty();
        redrawPanel();
    }

    //success - hide dialog
    moveSelectionOpen = false;
    moveSelectionFrame->setVisible(false);
    moveSelectionFrame->dispose();
    moveSelectionFrame = nullptr;
}

void LayoutEditor::moveSelectionCancelPressed() {
    moveSelectionOpen = false;
    moveSelectionFrame->setVisible(false);
    moveSelectionFrame->dispose();
    moveSelectionFrame = nullptr;
}

void LayoutEditor::undoMoveSelection() {
    if (canUndoMoveSelection) {
        QList<Positionable*> contents = getContents();

        for (Positionable* c : contents) {
            QPointF upperLeft = c->getLocation();

            if (undoRect.contains(upperLeft)) {
                int xNew = (int) (upperLeft.x() + undoDeltaX);
                int yNew = (int) (upperLeft.y() + undoDeltaY);
                c->setLocation(xNew, yNew);
            }
        }

        QPointF delta = QPointF(undoDeltaX, undoDeltaY);
        for (LayoutTrack* lt : *layoutTrackList) {
            QPointF center = lt->getCoordsCenter();
            if (undoRect.contains(center)) {
                lt->setCoordsCenter(MathUtil::add(center, delta));
            }
        }
        undoRect = MathUtil::offset(undoRect, delta.x(), delta.y());
        selectionX = undoRect.x();
        selectionY = undoRect.y();
        selectionWidth = undoRect.width();
        selectionHeight = undoRect.height();
        resizePanelBounds(false);
        redrawPanel();
        canUndoMoveSelection = false;
    }
}

/*public*/ void LayoutEditor::setCurrentPositionAndSize()
{
 // save current panel location and size
 QSize dim = size();

 // Compute window size based on LayoutEditor size
 windowHeight = dim.height();
 windowWidth = dim.width();

 // Compute layout size based on LayoutPane size
 QSizeF dimF = getTargetPanelSize();
 panelHeight = (int) (dimF.height() / getZoom());
 panelWidth = (int) (dimF.width() / getZoom());

 QPoint pt = getLocationOnScreen();
 upperLeftX = pt.x();
 upperLeftY = pt.y();

 UserPreferencesManager* prefsMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if(prefsMgr != nullptr)
 {
  QString windowFrameRef = getWindowFrameRef();

  //the restore code for this isn't working…
  prefsMgr->setWindowLocation(windowFrameRef, QPoint(upperLeftX, upperLeftY));
  prefsMgr->setWindowSize(windowFrameRef, QSize(windowWidth, windowHeight));

  if (true)
  {
   QPoint prefsWindowLocation = prefsMgr->getWindowLocation(windowFrameRef);

   if ((prefsWindowLocation.x() != upperLeftX) || (prefsWindowLocation.y() != upperLeftY))
   {
    log->error("setWindowLocation failure.");
   }
   QSize prefsWindowSize = prefsMgr->getWindowSize(windowFrameRef);

   if ((prefsWindowSize.width() != windowWidth) || (prefsWindowSize.height() != windowHeight)) {
       log->error("setWindowSize failure.");
   }
  }

  //we're going to use this instead
  if (true)
  { //(Nope, it's not working ether)
    //save it in the user preferences for the window
   QRectF windowQRectF =  QRectF(upperLeftX, upperLeftY, windowWidth, windowHeight);
   prefsMgr->setProperty(windowFrameRef, "windowQRectF", windowQRectF);
   QVariant prefsProp = prefsMgr->getProperty(windowFrameRef, "windowQRectF");
   log->info(tr("testing prefsProp: ") + prefsProp.toString());
  }
 } //);

 log->debug("setCurrentPositionAndSize Position - " + QString::number(upperLeftX) + "," + QString::number(upperLeftY) + " WindowSize - " + QString::number(windowWidth) + "," + QString::number(windowHeight) + " PanelSize - " + QString::number(panelWidth) + "," + QString::number(panelHeight));
 setDirty();
}

/*public*/ void LayoutEditor::setDirectTurnoutControl(bool boo) {
    useDirectTurnoutControl = boo;
// TODO:     useDirectTurnoutControlItem->setChecked(useDirectTurnoutControl);

}

/*public*/ bool LayoutEditor::getDirectTurnoutControl() {
    return useDirectTurnoutControl;
}


/*public*/ void LayoutEditor::setLayoutDimensions(int windowWidth, int windowHeight, int x, int y, int panelWidth, int panelHeight, bool merge) {
    upperLeftX = x;
    upperLeftY = y;
    setLocation(upperLeftX, upperLeftY);

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    setSize(windowWidth, windowHeight);

    QRectF panelBounds = QRectF(0.0, 0.0, panelWidth, panelHeight);

    if (merge) {
        panelBounds.united(calculateMinimumLayoutBounds());
    }
    setPanelBounds(panelBounds);
}   //setLayoutDimensions

/*public*/ QRectF LayoutEditor::getPanelBounds() {
        return QRectF(0.0, 0.0, panelWidth, panelHeight);
}

/*public*/ void LayoutEditor::setPanelBounds(QRectF newBounds) {
    // don't let origin go negative
 QRectF zeroToInfinityQRectF(0.0, 0.0, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

 newBounds = newBounds.intersected(zeroToInfinityQRectF);

    if (getPanelBounds() !=(newBounds)) {
        panelWidth = (int) newBounds.width();
        panelHeight = (int) newBounds.height();

        int newTargetWidth = (int) (panelWidth * getZoom());
        int newTargetHeight = (int) (panelHeight * getZoom());

        QSizeF targetPanelSize = getTargetPanelSize();
        int oldTargetWidth = (int) targetPanelSize.width();
        int oldTargetHeight = (int) targetPanelSize.height();

        if ((newTargetWidth != oldTargetWidth) || (newTargetHeight != oldTargetHeight)) {
            setTargetPanelSize(newTargetWidth, newTargetHeight);
//            adjustScrollBars();
        }
    }
    log->debug(tr("setPanelBounds((%1, %2, %3, %4)").arg(newBounds.x()).arg(newBounds.y()).arg(newBounds.width()).arg(newBounds.height()));
}

// this will grow the panel bounds based on items added to the layout
/*public*/ QRectF LayoutEditor::unionToPanelBounds(/*@Nonnull*/ QRectF bounds) {
    QRectF result = getPanelBounds();
#if 0
    // make room to expand
    QRectF b = Mathutil->inset(bounds, gridSize1st * gridSize2nd / -2.0);

    // don't let origin go negative
    b = b.createIntersection(Mathutil->zeroToInfinityQRectF);

    result.add(b);

    setPanelBounds(result);
#endif
    return result;
}

/*public*/ void LayoutEditor::setMainlineTrackWidth(int w) {
    mainlineTrackWidth = w;
}

/*public*/ void LayoutEditor::setSideTrackWidth(int w) {
    sidelineTrackWidth = w;
}
/*public*/ void LayoutEditor::setDefaultTrackColor(QString color) {
    defaultTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}
/**
 * @param color value to set the default track color to.
 */
/*public*/ void LayoutEditor::setDefaultTrackColor(/*@Nonnull*/ QColor color) {
    LayoutTrack::setDefaultTrackColor(color);
    defaultTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ void LayoutEditor::setDefaultOccupiedTrackColor(QString color) {
    defaultOccupiedTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}

/**
 * @param color value to set the default occupied track color to.
 */
/*public*/ void LayoutEditor::setDefaultOccupiedTrackColor(/*@Nonnull*/ QColor color) {
    defaultOccupiedTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ void LayoutEditor::setDefaultAlternativeTrackColor(QString color) {
    defaultAlternativeTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}

/**
 * @param color value to set the default alternate track color to.
 */
/*public*/ void LayoutEditor::setDefaultAlternativeTrackColor(/*@Nonnull*/ QColor color) {
    defaultAlternativeTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ void LayoutEditor::setTurnoutCircleColor(QString color)
{
 turnoutCircleColor = ColorUtil::stringToColor(color);
 setOptionMenuTurnoutCircleColor();
}

/**
 * @param color new color for turnout circle.
 */
/*public*/ void LayoutEditor::setTurnoutCircleColor(QColor color) {
    if (!color.isValid()) {
        turnoutCircleColor = ColorUtil::stringToColor(getDefaultTrackColor());
    } else {
        turnoutCircleColor = color;
        JmriColorChooser::addRecentColor(color);
    }
}

/*public*/ void LayoutEditor::setTurnoutCircleSize(int size) {
    turnoutCircleSize = size;
  setOptionMenuTurnoutCircleSize();
}

/*public*/ void LayoutEditor::setTurnoutDrawUnselectedLeg(bool state)
{
 if (turnoutDrawUnselectedLeg != state)
 {
  turnoutDrawUnselectedLeg = state;
  turnoutDrawUnselectedLegCheckBoxMenuItem->setChecked(turnoutDrawUnselectedLeg);
 }
}

/*public*/ void LayoutEditor::setXScale(double xSc) {
    xScale = xSc;
}

/*public*/ void LayoutEditor::setYScale(double ySc) {
    yScale = ySc;
}

/*public*/ void LayoutEditor::setShowHelpBar(bool state)
{
 if (showHelpBar != state)
  {
   showHelpBar = state;
//   if (toolBarSide.equals(eToolBarSide.eFLOAT)) {
//                   if (floatEditHelpPanel != null) {
//                       floatEditHelpPanel.setVisible(isEditable() && showHelpBar);
//                   }
//               } else {
//                   if (helpBarPanel != null) {
//                       helpBarPanel.setVisible(isEditable() && showHelpBar);
//                   }
//               }
//               InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefsMgr) -> {
//                   prefsMgr.setSimplePreferenceState(getWindowFrameRef() + ".showHelpBar", showHelpBar);
//               });
 }
}

/*public*/ void LayoutEditor::setDrawGrid(bool state)
{
 if (drawGrid != state)
 {
  drawGrid = state;
  //showGridItem->setChecked(drawGrid);
  ui->actionShow_grid_in_edit_mode->setChecked(drawGrid);
  on_actionShow_grid_in_edit_mode_toggled(state);
 }
}
/*public*/ void LayoutEditor::setSnapOnAdd(bool state)
{
 if (snapToGridOnAdd != state)
 {
  snapToGridOnAdd = state;
  //snapToGridOnAddItem->setChecked(snapToGridOnAdd);
  ui->actionSnap_to_grid_when_adding->setChecked(snapToGridOnAdd);
  on_actionSnap_to_grid_when_adding_toggled(state);
 }
}

/*public*/ void LayoutEditor::setSnapOnMove(bool state)
{
 if (snapToGridOnMove != state)
 {
  snapToGridOnMove = state;
  //snapToGridOnMoveItem->setChecked(snapToGridOnMove);
  ui->actionSnap_to_grid_when_moving->setChecked(snapToGridOnMove);
  on_actionSnap_to_grid_when_moving_toggled(state);
 }
}

/*public*/ void LayoutEditor::setAntialiasingOn(bool state)
{
 if (antialiasingOn != state)
 {
  antialiasingOn = state;
  //this may not be set up yet...
  if (antialiasingOnCheckBoxMenuItem != nullptr) {
      antialiasingOnCheckBoxMenuItem->setChecked(antialiasingOn);

  }
  UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"
  ));
  if(prefsMgr)  {
      prefsMgr->setSimplePreferenceState(getWindowFrameRef() + ".antialiasingOn", antialiasingOn);
  }//);
 }
}

//enable/disable using the "Extra" color to highlight the selected block
/*public*/ void LayoutEditor::setHighlightSelectedBlock(bool state) {
    if (highlightSelectedBlockFlag != state) {
        highlightSelectedBlockFlag = state;

        //this may not be set up yet...
        if (ui->highlightBlockCheckBox != nullptr) {
            ui->highlightBlockCheckBox->setChecked(highlightSelectedBlockFlag);
        }

        UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
        if(prefsMgr)
        {
            prefsMgr->setSimplePreferenceState(getWindowFrameRef() + ".highlightSelectedBlock", highlightSelectedBlockFlag);
        }//);

        // thread this so it won't break the AppVeyor checks
//        new Thread(() ->
        {
            if (highlightSelectedBlockFlag) {
                //use the "Extra" color to highlight the selected block
                if (!highlightBlockInComboBox(ui->blockIDComboBox)) {
                    highlightBlockInComboBox(ui->blockContentsComboBox);
                }
            } else {
                //undo using the "Extra" color to highlight the selected block
                highlightBlock(nullptr);
            }
        }//).start();
    }
}
//
//highlight the block selected by the specified combo Box
//
/*private*/ bool LayoutEditor::highlightBlockInComboBox(/*@Nonnull*/ JmriBeanComboBox* inComboBox) {
    Block* block = nullptr;
    if (inComboBox != nullptr) {
        block = (Block*) inComboBox->getNamedBean();
    }
    return highlightBlock(block);
}

/**
 * highlight the specified block
 *
 * @param inBlock the block
 * @return true if block was highlighted
 */
//@SuppressWarnings("unchecked") // Annotate the List<Block> l assignment
                               // First, make JmriBeanComboBox generic on <E extends NamedBean> (and manager) to fix this.
/*public*/ bool LayoutEditor::highlightBlock(/*@Nullable*/ Block* inBlock) {
    bool result = false; //assume failure (pessimist!)

   ui-> blockIDComboBox->setSelectedBean(inBlock);

    LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
    QSet<NamedBean*> l = ui->blockIDComboBox->getManager()->getNamedBeanSet();
    for (NamedBean* nb : l) {
        Block* b = (Block*) nb;
        LayoutBlock* lb = lbm->getLayoutBlock(b);
        if (lb != nullptr) {
            bool enable = ((inBlock != nullptr) && b ==(inBlock));
            lb->setUseExtraColor(enable);
            result |= enable;
        }
    }
    return result;
}

/*public*/ void LayoutEditor::setTurnoutCircles(bool state)
{
 if (turnoutCirclesWithoutEditMode != state)
 {
  turnoutCirclesWithoutEditMode = state;
  //turnoutCirclesOnItem->setChecked(turnoutCirclesWithoutEditMode);
  ui->actionShow_turnout_circles->setChecked(turnoutCirclesWithoutEditMode);
  on_actionShow_turnout_circles_toggled(state);
 }
}

/*public*/ void LayoutEditor::setAutoBlockAssignment(bool boo)
{
 if (autoAssignBlocks != boo)
 {
  autoAssignBlocks = boo;
  autoAssignBlocksItem->setChecked(autoAssignBlocks);
  //ui->action
 }
}
/*======================================*\
|* Dialog box to enter new track widths *|
\*======================================*/

//display dialog for entering track widths
/*protected*/ void LayoutEditor::enterTrackWidth() {
    if (enterTrackWidthOpen) {
        enterTrackWidthFrame->setVisible(true);
        return;
    }

    //Initialize if needed
    if (enterTrackWidthFrame == nullptr) {
        enterTrackWidthFrame = new JmriJFrame(tr("Set Track Line Width"));
        enterTrackWidthFrame->addHelpMenu("package.jmri.jmrit.display.EnterTrackWidth", true);
        enterTrackWidthFrame->setLocation(70, 30);
        QWidget* theContentPane = enterTrackWidthFrame->getContentPane();
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

        //setup mainline track width (placed above side track for clarity, name 'panel3' kept)
        QWidget* panel3 = new QWidget();
        panel3->setLayout(new FlowLayout());
        QLabel* mainlineWidthLabel = new QLabel(tr("Mainline Track Width"));
        panel3->layout()->addWidget(mainlineWidthLabel);
        panel3->layout()->addWidget(mainlineTrackWidthField);
        mainlineTrackWidthField->setToolTip(tr("Enter width for mainline track (1 - 10 allowed)."));
        theContentPane->layout()->addWidget(panel3);

        //setup side track width
        QWidget* panel2 = new QWidget();
        panel2->setLayout(new FlowLayout());
        QLabel* sideWidthLabel = new QLabel(tr("sideline Track Width"));
        panel2->layout()->addWidget(sideWidthLabel);
        panel2->layout()->addWidget(sidelineTrackWidthField);
        sidelineTrackWidthField->setToolTip(tr("sidelineTrackWidthHint"));
        theContentPane->layout()->addWidget(panel2);

        //set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5->setLayout(new FlowLayout());
        panel5->layout()->addWidget(trackWidthDone = new QPushButton(tr("Done")));
//        trackWidthDone.addActionListener((ActionEvent event) -> {
//            trackWidthDonePressed(event);
//        });
        connect(trackWidthDone, SIGNAL(clicked(bool)), this, SLOT(trackWidthDonePressed()));
        trackWidthDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(trackWidthDone);
//            rootPane.setDefaultButton(trackWidthDone);
//        });

        //Cancel
        panel5->layout()->addWidget(trackWidthCancel = new QPushButton(tr("Cancel")));
//        trackWidthCancel.addActionListener((ActionEvent event) -> {
//            trackWidthCancelPressed(event);
//        });
        connect(trackWidthCancel, SIGNAL(clicked(bool)), this, SLOT(trackWidthCancelPressed()));
        trackWidthCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPane->layout()->addWidget(panel5);
    }

    //Set up for Entry of Track Widths
    mainlineTrackWidthField->setText(QString::number((int) mainlineTrackWidth));
    sidelineTrackWidthField->setText(QString::number((int) sidelineTrackWidth));
//    enterTrackWidthFrame.addWindowListener(new WindowAdapter() {
//        @Override
//        public void windowClosing(WindowEvent event) {
//            trackWidthCancelPressed(null);
//        }
//    });
    enterTrackWidthFrame->addWindowListener(new EnterTrackWidthFrameWindowListener(this));
    enterTrackWidthFrame->pack();
    enterTrackWidthFrame->setVisible(true);
    trackWidthChange = false;
    enterTrackWidthOpen = true;

}

void LayoutEditor::trackWidthDonePressed(/*ActionEvent evemt*/) {
    //get side track width
    QString newWidth = sidelineTrackWidthField->text().trimmed();
    float wid = 0.0;
    bool bok;
        wid = (newWidth.toFloat(&bok));
    if(!bok) {
        JOptionPane::showMessageDialog(enterTrackWidthFrame,
                QString("%1: %2 %3").arg(tr("Error in entry")).arg(
                        tr("invalid floating point")).arg(tr("Please reenter or Cancel.")),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        return;
    }

    if ((wid < 1.0) || (wid > 10.0)) {
        JOptionPane::showMessageDialog(enterTrackWidthFrame,
                tr("Error - Entered value \"%1\" is not in the allowed range.\nPlease enter a number from 1 to 10.").arg(
                        tr(" %%1 ").arg(wid)),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    if (!MathUtil::equals(sidelineTrackWidth, wid)) {
        sidelineTrackWidth = wid;
        trackWidthChange = true;
    }

    //get mainline track width
    newWidth = mainlineTrackWidthField->text().trimmed();

        wid = newWidth.toFloat(&bok);
    if(!bok) {
        JOptionPane::showMessageDialog(enterTrackWidthFrame,
                QString("%1: %%2 %%3").arg(tr("Error in entry")).arg(tr("Invlid number format")).arg(
                        tr("Please reenter or Cancel.")),
                tr("ErrorTitle"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    if ((wid < 1.0) || (wid > 10.0)) {
     JOptionPane::showMessageDialog(enterTrackWidthFrame,
             tr("Error - Entered value \"%1\" is not in the allowed range.\nPlease enter a number from 1 to 10.").arg(
                     tr(" %%1 ").arg(wid)),
             tr("Error"),
             JOptionPane::ERROR_MESSAGE);
    } else {
        if (!MathUtil::equals(mainlineTrackWidth, wid)) {
            mainlineTrackWidth = wid;
            trackWidthChange = true;
        }

        //success - hide dialog and repaint if needed
        enterTrackWidthOpen = false;
        enterTrackWidthFrame->setVisible(false);
        enterTrackWidthFrame->dispose();
        enterTrackWidthFrame = nullptr;

        if (trackWidthChange) {
            //Integrate-LayoutEditor-drawing-options-with-previous-drawing-options
            if (layoutTrackDrawingOptions != nullptr) {
                layoutTrackDrawingOptions->setMainBlockLineWidth((int) mainlineTrackWidth);
                layoutTrackDrawingOptions->setSideBlockLineWidth((int) sidelineTrackWidth);
                layoutTrackDrawingOptions->setMainRailWidth((int) mainlineTrackWidth);
                layoutTrackDrawingOptions->setSideRailWidth((int) sidelineTrackWidth);
            }
            redrawPanel();
            setDirty();
        }
    }
}

void LayoutEditor::trackWidthCancelPressed(/*ActionEvent event*/) {
    enterTrackWidthOpen = false;
    enterTrackWidthFrame->setVisible(false);
    enterTrackWidthFrame->dispose();
    enterTrackWidthFrame = nullptr;

    if (trackWidthChange) {
        redrawPanel();
        setDirty();
    }
}

/*====================================*\
|* Dialog box to enter new grid sizes *|
\*====================================*/

//display dialog for entering grid sizes
/*protected*/ void LayoutEditor::enterGridSizes() {
    if (enterGridSizesOpen) {
        enterGridSizesFrame->setVisible(true);
        return;
    }
    //Initialize if needed
    if (enterGridSizesFrame == nullptr) {
        enterGridSizesFrame = new JmriJFrame(tr("SetGridSizes"));
        enterGridSizesFrame->addHelpMenu("package.jmri.jmrit.display.EnterGridSizes", true);
        enterGridSizesFrame->setLocation(70, 30);
        QWidget* theContentPane = enterGridSizesFrame->getContentPane();
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

        //setup primary grid sizes
        QWidget* panel3 = new QWidget();
        panel3->setLayout(new FlowLayout());
        QLabel* primaryGridSIzeLabel = new QLabel(tr("Primary Grid Size:"));
        panel3->layout()->addWidget(primaryGridSIzeLabel);
        panel3->layout()->addWidget(primaryGridSizeField);
        primaryGridSizeField->setToolTip(tr("Enter width for primary grid size"));
        theContentPane->layout()->addWidget(panel3);

        //setup side track width
        QWidget* panel2 = new QWidget();
        panel2->setLayout(new FlowLayout());
        QLabel* secondaryGridSizeLabel = new QLabel(tr("Secondary Grid Size:"));
        panel2->layout()->addWidget(secondaryGridSizeLabel);
        panel2->layout()->addWidget(secondaryGridSizeField);
        secondaryGridSizeField->setToolTip(tr("Enter width for secondary grid size"));
        theContentPane->layout()->addWidget(panel2);

        //set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5->setLayout(new FlowLayout());
        panel5->layout()->addWidget(gridSizesDone = new QPushButton(tr("Done")));
//        gridSizesDone.addActionListener((ActionEvent event) -> {
//            gridSizesDonePressed(event);
//        });
        connect(gridSizesDone, SIGNAL(clicked(bool)), this, SLOT(gridSizesDonePressed()));
        gridSizesDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(gridSizesDone);
//            rootPane.setDefaultButton(gridSizesDone);
//        });

        //Cancel
        panel5->layout()->addWidget(gridSizesCancel = new QPushButton(tr("Cancel")));
//        gridSizesCancel.addActionListener((ActionEvent event) -> {
//            gridSizesCancelPressed(event);
//        });
        connect(gridSizesCancel, SIGNAL(clicked(bool)), this, SLOT(gridSizesCancelPressed()));
        gridSizesCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPane->layout()->addWidget(panel5);
    }

    //Set up for Entry of Track Widths
    primaryGridSizeField->setText(QString::number(gridSize1st));
    secondaryGridSizeField->setText(QString::number(gridSize2nd));
//    enterGridSizesFrame.addWindowListener(new WindowAdapter() {
//        @Override
//        public void windowClosing(WindowEvent event) {
//            gridSizesCancelPressed(null);
//        }
//    });
    enterGridSizesFrame->addWindowListener(new EnterGridSizesFrameWindowListener(this));
    enterGridSizesFrame->pack();
    enterGridSizesFrame->setVisible(true);
    gridSizesChange = false;
    enterGridSizesOpen = true;
}

void LayoutEditor::gridSizesDonePressed(/*ActionEvent event*/) {
    QString newGridSize = "";
    float siz = 0.0;

    //get secondary grid size
    newGridSize = secondaryGridSizeField->text().trimmed();
    bool bok;
        siz = newGridSize.toFloat(&bok);
    if(!bok) {
     JOptionPane::showMessageDialog(enterTrackWidthFrame,
             QString("%1: %%2 %%3").arg(tr("Error in entry")).arg(tr("Invlid number format")).arg(
                     tr("Please reenter or Cancel.")),
             tr("ErrorTitle"),
             JOptionPane::ERROR_MESSAGE);

        return;
    }

    if ((siz < 5.0) || (siz > 100.0)) {
        JOptionPane::showMessageDialog(enterGridSizesFrame,
                tr("Error - Entered value \"%1\" is not in the allowed range.").arg(
                        tr(" %1 ").arg(siz)),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    if (!MathUtil::equals(gridSize2nd, siz)) {
        gridSize2nd = (int) siz;
        gridSizesChange = true;
    }

    //get mainline track width
    newGridSize = primaryGridSizeField->text().trimmed();
        siz = newGridSize.toFloat(&bok);
    if(!bok) {
     JOptionPane::showMessageDialog(enterTrackWidthFrame,
             QString("%1: %%2 %%3").arg(tr("Error in entry")).arg(tr("Invlid number format")).arg(
                     tr("Please reenter or Cancel.")),
             tr("ErrorTitle"),
             JOptionPane::ERROR_MESSAGE);

        return;
    }

    if ((siz < 5) || (siz > 100.0)) {
     JOptionPane::showMessageDialog(enterGridSizesFrame,
             tr("Error - Entered value \"%1\" is not in the allowed range.").arg(
                     tr(" %1 ").arg(siz)),
             tr("Error"),
             JOptionPane::ERROR_MESSAGE);
    } else {
        if (!MathUtil::equals(gridSize1st, siz)) {
            gridSize1st = (int) siz;
            gridSizesChange = true;
        }

        //success - hide dialog and repaint if needed
        enterGridSizesOpen = false;
        enterGridSizesFrame->setVisible(false);
        enterGridSizesFrame->dispose();
        enterGridSizesFrame = nullptr;

        if (gridSizesChange) {
            redrawPanel();
            setDirty();
        }
    }
}

void LayoutEditor::gridSizesCancelPressed(/*ActionEvent event*/) {
    enterGridSizesOpen = false;
    enterGridSizesFrame->setVisible(false);
    enterGridSizesFrame->dispose();
    enterGridSizesFrame = nullptr;

    if (gridSizesChange) {
        redrawPanel();
        setDirty();
    }
}

/*=======================================*\
|* Dialog box to enter new reporter info *|
\*=======================================*/

//display dialog for entering Reporters
/*protected*/ void LayoutEditor::enterReporter(int defaultX, int defaultY) {
    if (reporterOpen) {
        enterReporterFrame->setVisible(true);

        return;
    }
#if 0
    //Initialize if needed
    if (enterReporterFrame == nullptr) {
        enterReporterFrame = new JmriJFrame(tr("AddReporter"));

//enterReporterFrame.addHelpMenu("package.jmri.jmrit.display.AddReporterLabel", true);
        enterReporterFrame.setLocation(70, 30);
        Container theContentPane = enterReporterFrame.getContentPane();
        theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.PAGE_AXIS));

        //setup reporter entry
        JPanel panel2 = new JPanel();
        panel2.setLayout(new FlowLayout());
        JLabel reporterLabel = new JLabel(tr("ReporterName"));
        panel2.add(reporterLabel);
        panel2.add(reporterNameField);
        reporterNameField.setToolTipText(tr("ReporterNameHint"));
        theContentPane.add(panel2);

        //setup coordinates entry
        JPanel panel3 = new JPanel();
        panel3.setLayout(new FlowLayout());
        JLabel xCoordLabel = new JLabel(tr("ReporterLocationX"));
        panel3.add(xCoordLabel);
        panel3.add(xPositionField);
        xPositionField.setToolTipText(tr("ReporterLocationXHint"));
        JLabel yCoordLabel = new JLabel(tr("ReporterLocationY"));
        panel3.add(yCoordLabel);
        panel3.add(yPositionField);
        yPositionField.setToolTipText(tr("ReporterLocationYHint"));
        theContentPane.add(panel3);

        //set up Add and Cancel buttons
        JPanel panel5 = new JPanel();
        panel5.setLayout(new FlowLayout());
        panel5.add(reporterDone = new JButton(tr("AddNewLabel")));
        reporterDone.addActionListener((ActionEvent event) -> {
            reporterDonePressed(event);
        });
        reporterDone.setToolTipText(tr("ReporterDoneHint"));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(reporterDone);
            rootPane.setDefaultButton(reporterDone);
        });

        //Cancel
        panel5.add(reporterCancel = new JButton(tr("ButtonCancel")));
        reporterCancel.addActionListener((ActionEvent event) -> {
            reporterCancelPressed();
        });
        reporterCancel.setToolTipText(tr("CancelHint", tr("ButtonCancel")));
        theContentPane.add(panel5);
    }

    //Set up for Entry of Reporter Icon
    xPositionField.setText(Integer.toString(defaultX));
    yPositionField.setText(Integer.toString(defaultY));
    enterReporterFrame.addWindowListener(new WindowAdapter() {
        @Override
        public void windowClosing(WindowEvent event) {
            reporterCancelPressed();
        }
    });
    enterReporterFrame.pack();
    enterReporterFrame.setVisible(true);
    reporterOpen = true;
#endif
}

void LayoutEditor::reporterDonePressed(/*@Nonnull ActionEvent event*/) {
    //get size of current panel
    QSizeF dim = getTargetPanelSize();

    //get x coordinate
    QString newX = "";
    int xx = 0;
#if 0
    newX = xPositionField->text().trimmed();
    try {
        xx = Integer.parseInt(newX);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(enterReporterFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    if ((xx <= 0) || (xx > dim.width)) {
        JOptionPane.showMessageDialog(enterReporterFrame,
                MessageFormat.format(tr("Error2a"),
                        new Object[]{String.format(" %s ", xx)}),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // get y coordinate
    String newY = "";
    int yy = 0;
    newY = yPositionField.getText().trim();
    try {
        yy = Integer.parseInt(newY);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(enterReporterFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    if ((yy <= 0) || (yy > dim.height)) {
        JOptionPane.showMessageDialog(enterReporterFrame,
                MessageFormat.format(tr("Error2a"),
                        new Object[]{String.format(" %s ", yy)}),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // get reporter name
    Reporter reporter = null;
    String rName = reporterNameField.getText().trim();

    if (InstanceManager.getNullableDefault(ReporterManager.class) != null) {
        try {
            reporter = InstanceManager.getDefault(ReporterManager.class).provideReporter(rName);
        } catch (IllegalArgumentException e) {
            JOptionPane.showMessageDialog(enterReporterFrame,
                    MessageFormat.format(tr("Error18"),
                            new Object[]{rName}), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);

            return;
        }

        if (!rName.equals(reporter.getDisplayName())) {
            rName = rName.toUpperCase();
        }
    } else {
        JOptionPane.showMessageDialog(enterReporterFrame,
                tr("Error17"), tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    //add the reporter icon
    addReporter(rName, xx, yy);

    //success - repaint the panel
    redrawPanel();
    enterReporterFrame.setVisible(true);
#endif
}

void LayoutEditor::reporterCancelPressed() {
    reporterOpen = false;
    enterReporterFrame->setVisible(false);
    enterReporterFrame->dispose();
    enterReporterFrame = nullptr;
    redrawPanel();
}

/*===============================*\
|*  Dialog box to enter scale /  *|
|*  translate track diagram info *|
\*===============================*/

//display dialog for scaling the track diagram
/*protected*/ void LayoutEditor::scaleTrackDiagram() {
    if (scaleTrackDiagramOpen) {
        scaleTrackDiagramFrame->setVisible(true);
        return;
    }
#if 0
    // Initialize if needed
    if (scaleTrackDiagramFrame == null) {
        scaleTrackDiagramFrame = new JmriJFrame(tr("ScaleTrackDiagram"));
        scaleTrackDiagramFrame.addHelpMenu("package.jmri.jmrit.display.ScaleTrackDiagram", true);
        scaleTrackDiagramFrame.setLocation(70, 30);
        Container theContentPane = scaleTrackDiagramFrame.getContentPane();
        theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.PAGE_AXIS));

        // setup x translate
        JPanel panel31 = new JPanel();
        panel31.setLayout(new FlowLayout());
        JLabel xTranslateLabel = new JLabel(tr("XTranslateLabel"));
        panel31.add(xTranslateLabel);
        panel31.add(xTranslateField);
        xTranslateField.setToolTipText(tr("XTranslateHint"));
        theContentPane.add(panel31);

        //setup y translate
        JPanel panel32 = new JPanel();
        panel32.setLayout(new FlowLayout());
        JLabel yTranslateLabel = new JLabel(tr("YTranslateLabel"));
        panel32.add(yTranslateLabel);
        panel32.add(yTranslateField);
        yTranslateField.setToolTipText(tr("YTranslateHint"));
        theContentPane.add(panel32);

        //setup information message 1
        JPanel panel33 = new JPanel();
        panel33.setLayout(new FlowLayout());
        JLabel message1Label = new JLabel(tr("Message1Label"));
        panel33.add(message1Label);
        theContentPane.add(panel33);

        //setup x factor
        JPanel panel21 = new JPanel();
        panel21.setLayout(new FlowLayout());
        JLabel xFactorLabel = new JLabel(tr("XFactorLabel"));
        panel21.add(xFactorLabel);
        panel21.add(xFactorField);
        xFactorField.setToolTipText(tr("FactorHint"));
        theContentPane.add(panel21);

        //setup y factor
        JPanel panel22 = new JPanel();
        panel22.setLayout(new FlowLayout());
        JLabel yFactorLabel = new JLabel(tr("YFactorLabel"));
        panel22.add(yFactorLabel);
        panel22.add(yFactorField);
        yFactorField.setToolTipText(tr("FactorHint"));
        theContentPane.add(panel22);

        //setup information message 2
        JPanel panel23 = new JPanel();
        panel23.setLayout(new FlowLayout());
        JLabel message2Label = new JLabel(tr("Message2Label"));
        panel23.add(message2Label);
        theContentPane.add(panel23);

        //set up Done and Cancel buttons
        JPanel panel5 = new JPanel();
        panel5.setLayout(new FlowLayout());
        panel5.add(scaleTrackDiagramDone = new JButton(tr("ScaleTranslate")));
        scaleTrackDiagramDone.addActionListener((ActionEvent event) -> {
            scaleTrackDiagramDonePressed(event);
        });
        scaleTrackDiagramDone.setToolTipText(tr("ScaleTranslateHint"));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(scaleTrackDiagramDone);
            rootPane.setDefaultButton(scaleTrackDiagramDone);
        });

        panel5.add(scaleTrackDiagramCancel = new JButton(tr("ButtonCancel")));
        scaleTrackDiagramCancel.addActionListener((ActionEvent event) -> {
            scaleTrackDiagramCancelPressed(event);
        });
        scaleTrackDiagramCancel.setToolTipText(tr("CancelHint", tr("ButtonCancel")));
        theContentPane.add(panel5);
    }

    // Set up for Entry of Scale and Translation
    xFactorField.setText("1.0");
    yFactorField.setText("1.0");
    xTranslateField.setText("0");
    yTranslateField.setText("0");
    scaleTrackDiagramFrame.addWindowListener(new WindowAdapter() {
        @Override
        public void windowClosing(WindowEvent event) {
            scaleTrackDiagramCancelPressed(null);
        }
    });
    scaleTrackDiagramFrame.pack();
    scaleTrackDiagramFrame.setVisible(true);
    scaleTrackDiagramOpen = true;
#endif
}

void LayoutEditor::scaleTrackDiagramDonePressed(/*ActionEvent event*/) {
    QString newText = "";
    bool changeFlag = false;
    bool translateError = false;
    float xTranslation = 0.0F;
    float yTranslation = 0.0F;
    float xFactor = 1.0F;
    float yFactor = 1.0F;
#if 0
    // get x translation
    newText = xTranslateField->text().trimmed();
    try {
        xTranslation = Float.parseFloat(newText);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(scaleTrackDiagramFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // get y translation
    newText = yTranslateField.getText().trim();
    try {
        yTranslation = Float.parseFloat(newText);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(scaleTrackDiagramFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // get x factor
    newText = xFactorField.getText().trim();
    try {
        xFactor = Float.parseFloat(newText);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(scaleTrackDiagramFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // get y factor
    newText = yFactorField.getText().trim();
    try {
        yFactor = Float.parseFloat(newText);
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(scaleTrackDiagramFrame,
                String.format("%s: %s %s", tr("EntryError"),
                        e, tr("TryAgain")),
                tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);

        return;
    }

    // here when all numbers read in successfully - check for translation
    if ((xTranslation != 0.0F) || (yTranslation != 0.0F)) {
        //apply translation
        if (translateTrack(xTranslation, yTranslation)) {
            changeFlag = true;
        } else {
            log.error("Error translating track diagram");
            translateError = true;
        }
    }

    if (!translateError && ((xFactor != 1.0) || (yFactor != 1.0))) {
        //apply scale change
        if (scaleTrack(xFactor, yFactor)) {
            changeFlag = true;
        } else {
            log.error("Error scaling track diagram");
        }
    }
    selectionActive = false;
    clearSelectionGroups();

    // success - dispose of the dialog and repaint if needed
    scaleTrackDiagramOpen = false;
    scaleTrackDiagramFrame.setVisible(false);
    scaleTrackDiagramFrame.dispose();
    scaleTrackDiagramFrame = null;

    if (changeFlag) {
        redrawPanel();
        setDirty();
    }
#endif
}

void LayoutEditor::scaleTrackDiagramCancelPressed(/*ActionEvent event*/) {
    scaleTrackDiagramOpen = false;
    scaleTrackDiagramFrame->setVisible(false);
    scaleTrackDiagramFrame->dispose();
    scaleTrackDiagramFrame = nullptr;
}

/*public*/ void LayoutEditor::setScroll(int state)
{
 if (isEditable())
 {
  //In edit mode the scroll bars are always displayed, however we will want to set the scroll for when we exit edit mode
  Editor::setScroll(SCROLL_BOTH);
  _scrollState = state;
 }
 else
 {
  Editor::setScroll(state);
 }
}

/**
 * Add a layout turntable at location specified
 */
/*public*/ void LayoutEditor::addTurntable(QPointF pt)
{
  numLayoutTurntables++;
  QString name = "";
  bool duplicate = true;
  while (duplicate)
  {
   name = "TUR" + QString::number(numLayoutTurntables);
   if (finder->findLayoutTurntableByName(name) == nullptr)
   {
    duplicate = false;
   }
   if (duplicate)
   {
    numLayoutTurntables++;
   }
 }
 LayoutTurntable* x = new LayoutTurntable(name, pt, this);
 //if (x != nullptr) {
 turntableList->append(x);
 layoutTrackList->append(x);
 setDirty(true);
 //}
 x->addRay(0.0);
 x->addRay(90.0);
 x->addRay(180.0);
 x->addRay(270.0);
}
// final initialization routine for loading a LayoutEditor
/*public*/ void LayoutEditor::setConnections()
{
 for (LayoutTrack* lt : *layoutTrackList) {
     lt->setObjects(this);
 }
 getLEAuxTools()->initializeBlockConnectivity();
 log->debug(tr("Initializing Block Connectivity for %1").arg(getLayoutName()));

 //reset the panel changed bit
 resetDirty();
}
//void LayoutEditor::on_actionMoveLayout_triggered()
//{
// JDialog* dlg = new JDialog();
// dlg->setTitle(tr("Move layout"));
// QVBoxLayout* dlgLayout = new QVBoxLayout(dlg);
// QHBoxLayout* hLayout = new QHBoxLayout;
// QLabel* xLabel = new QLabel(tr("X offset"));
// hLayout->addWidget(xLabel);
// xMove = new JTextField(4);
// xMove->setValidator(new QIntValidator(-100, +100));
// hLayout->addWidget(xMove);
// QLabel* yLabel = new QLabel(tr("X offset"));
// hLayout->addWidget(yLabel);
// yMove = new JTextField(4);
// yMove->setValidator(new QIntValidator(-100, +100));
// hLayout->addWidget(yMove);
// dlgLayout->addLayout(hLayout);
// QPushButton* ok = new QPushButton(tr("Move"));
// FlowLayout* buttonLayout = new FlowLayout();
// buttonLayout->addWidget(ok);
// dlgLayout->addLayout(buttonLayout);
// connect(ok, SIGNAL(clicked()), this, SLOT(on_okMove_clicked()));
// dlg->exec();
//}

//void LayoutEditor::on_okMove_clicked()
//{
// int dx = xMove->text().toInt();
// int dy = yMove->text().toInt();
// for(int i =0; i < _contents->size(); i++)
// {
//  moveItem(_contents->at(i), dx, dy);
// }
// for(int i = 0; i < pointList->size(); i++)
// {
//  PositionablePoint* pp = pointList->at(i);
//  QPointF pt = pp->getCoords();
//  pt.setX(pt.x()+ dx);
//  pt.setY(pt.y()+dy);
//  pp->setCoords(pt);
// }
// for (TrackSegment* seg : getTrackSegments()) {
//  QPointF p = seg->getCoordsCenterCircle();
//  seg->setCentreX(p.x()+dx);
//  seg->setCentreY(p.y()+dy);
// }
// for(int i = 0; i < turnoutList->count(); i++)
// {
//  LayoutTurnout* to = turnoutList->at(i);
//  QPointF p = to->getCoordsCenter();
//  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
// }
// for(int i = 0; i < slipList->count(); i++)
// {
//  LayoutSlip* to = slipList->at(i);
//  QPointF p = to->getCoordsCenter();
//  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
// }
// for(int i = 0; i < xingList->count(); i++)
// {
//  LevelXing * to = xingList->at(i);
//  QPointF p = to->getCoordsCenter();
//  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
// }
// for(int i = 0; i < turntableList->count(); i++)
// {
//  LayoutTurntable * to = turntableList->at(i);
//  QPointF p = to->getCoordsCenter();
//  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
// }
// paintTargetPanel(editScene);
//}
/*public*/ LayoutEditorFindItems* LayoutEditor::getFinder() {
    return finder;
}
/*private*/ QPointF LayoutEditor::windowCenter() {
    // Returns window's center coordinates converted to layout space
    // Used for initial setup of turntables and reporters
    // First of all compute center of window in screen coordinates
//    QPointF pt = getLocationOnScreen();
//    QSize dim = size();
//    pt.x += dim.width / 2;
//    pt.y += dim.height / 2 + 40; // 40 = approx. difference between upper and lower menu areas
//    // Now convert to layout space
//    SwingUtilities.convertPointFromScreen(pt, getTargetPanel());
//    pt.x /= getPaintScale();
//    pt.y /= getPaintScale();
    QPointF pt = QPointF(editScene->sceneRect().width()/2, editScene->sceneRect().height()/2);
    return pt;
}

/*public*/ QString LayoutEditor::getClassName()
{
 return "jmri.jmrit.display.layoutEditor.LayoutEditor";
}

///*private*/ /*transient*/ /*static*/ /*final*/ QMap<QString, LayoutEditor::ToolBarSide> LayoutEditor::ToolBarSide::ENUM_MAP = QMap<QString, LayoutEditor::ToolBarSide>();
//LayoutEditor::ToolBarSide::ENUM_MAP //.insert("top",  LayoutEditor::ToolBarSide::eTOP);

/**
 * Set up the Option menu.
 *
 * @param menuBar to add the option menu to
 * @return option menu that was added
 */
#if 1
/*protected*/ QMenu* LayoutEditor::setupOptionMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* optionMenu = ui->menuOptions;//new QMenu(tr("Options"));

//    optionMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("OptionsMnemonic")));
//    menuBar->addMenu(optionMenu);

    //
    //  edit mode
    //
    editModeCheckBoxMenuItem = new QAction(tr("Edit Mode"));
    editModeCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(editModeCheckBoxMenuItem);
//    editModeCheckBoxMenuItem.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("EditModeMnemonic")));
//    int primary_modifier = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
//    editModeCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(
//            stringsToVTCodes.get(Bundle.getMessage("EditModeAccelerator")), primary_modifier));
//    editModeCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        setAllEditable(editModeCheckBoxMenuItem.isSelected());

//        //show/hide the help bar
//        if (toolBarSide.equals(ToolBarSide.eFLOAT)) {
//            floatEditHelpPanel.setVisible(isEditable() && getShowHelpBar());
//        } else {
//            helpBarPanel.setVisible(isEditable() && getShowHelpBar());
//        }

//        if (isEditable()) {
//            setAllShowToolTip(tooltipsInEditMode);

//            //redo using the "Extra" color to highlight the selected block
//            if (highlightSelectedBlockFlag) {
//                if (!highlightBlockInComboBox(blockIDComboBox)) {
//                    highlightBlockInComboBox(blockContentsComboBox);
//                }
//            }
//        } else {
//            setAllShowToolTip(tooltipsWithoutEditMode);

//            //undo using the "Extra" color to highlight the selected block
//            if (highlightSelectedBlockFlag) {
//                highlightBlock(null);
//            }
//        }
//        awaitingIconChange = false;
//    });
    connect(editModeCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setAllEditable(bool)));
    editModeCheckBoxMenuItem->setChecked(isEditable());

    //
    // toolbar
    //
    QMenu* toolBarMenu = new QMenu(tr("Tool Bar")); //used for ToolBar SubMenu
    optionMenu->addMenu(toolBarMenu);

    //
    //create toolbar side menu items: (top, left, bottom, right)
    //

    toolBarSideTopButton = new QAction(tr("Top"),this);
    toolBarSideTopButton->setCheckable(true);
//    toolBarSideTopButton.addActionListener((ActionEvent event) -> {
//        setToolBarSide(ToolBarSide.eTOP);
//    });
    connect(toolBarSideTopButton, SIGNAL(triggered(bool)),this, SLOT(setToolBarSide(bool)));
    toolBarSideTopButton->setChecked(toolBarSide.getName() == (/*ToolBarSide::eTOP*/"top"));

    toolBarSideLeftButton = new QAction(tr("Left"));
//    toolBarSideLeftButton.addActionListener((ActionEvent event) -> {
//        setToolBarSide(ToolBarSide.eLEFT);
//    });
    toolBarSideLeftButton->setChecked(toolBarSide.getName()==(/*ToolBarSide::eLEFT)*/"left"));

    toolBarSideBottomButton = new QAction(tr("Bottom"));
    toolBarSideBottomButton->setCheckable(true);
//    toolBarSideBottomButton.addActionListener((ActionEvent event) -> {
//        setToolBarSide(ToolBarSide.eBOTTOM);
//    });
    toolBarSideBottomButton->setChecked(toolBarSide.getName()==(/*ToolBarSide::eBOTTOM*/"bottom"));

    toolBarSideRightButton = new QAction(tr("Right"));
    toolBarSideRightButton->setCheckable(true);
//    toolBarSideRightButton.addActionListener((ActionEvent event) -> {
//        setToolBarSide(ToolBarSide.eRIGHT);
//    });
    toolBarSideRightButton->setChecked(toolBarSide.getName()==(/*ToolBarSide::eRIGHT*/"right"));

    toolBarSideFloatButton = new QAction(tr("Float"));
    toolBarSideFloatButton->setCheckable(true);
//    toolBarSideFloatButton.addActionListener((ActionEvent event) -> {
//        setToolBarSide(ToolBarSide.eFLOAT);
//    });
    toolBarSideFloatButton->setChecked(toolBarSide.getName()==(/*ToolBarSide::eFLOAT*/"float"));

    QMenu* toolBarSideMenu = new QMenu(tr("ToolBar Side"));
    toolBarSideMenu->addAction(toolBarSideTopButton);
    toolBarSideMenu->addAction(toolBarSideLeftButton);
    toolBarSideMenu->addAction(toolBarSideBottomButton);
    toolBarSideMenu->addAction(toolBarSideRightButton);
    toolBarSideMenu->addAction(toolBarSideFloatButton);

    QActionGroup* toolBarSideGroup = new QActionGroup(this);
    toolBarSideGroup->addAction(toolBarSideTopButton);
    toolBarSideGroup->addAction(toolBarSideLeftButton);
    toolBarSideGroup->addAction(toolBarSideBottomButton);
    toolBarSideGroup->addAction(toolBarSideRightButton);
    toolBarSideGroup->addAction(toolBarSideFloatButton);
    toolBarMenu->addMenu(toolBarSideMenu);

    //
    //toolbar wide menu
    //
    toolBarMenu->addAction(wideToolBarCheckBoxMenuItem);
//    wideToolBarCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        bool newToolBarIsWide = wideToolBarCheckBoxMenuItem.isSelected();
//        setToolBarWide(newToolBarIsWide);
//    });
    wideToolBarCheckBoxMenuItem->setChecked(wideToolBarCheckBoxMenuItem->isChecked());

    //
    //create setup font size menu items
    //
    QActionGroup* toolBarFontSizeGroup = new QActionGroup(this);

    QStringList fontSizes = QStringList() <<"9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18";

    for (QString fontSize : fontSizes) {
        float fontSizeFloat =fontSize.toFloat();
        QAction* fontSizeButton = new QAction(fontSize);
        fontSizeButton->setCheckable(true);
//        fontSizeButton.addActionListener((ActionEvent event) -> {
//            setupToolBarFontSizes(fontSizeFloat);

//            //save it in the user preferences for the window
//            String windowFrameRef = getWindowFrameRef();
//            InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefsMgr) -> {
//                prefsMgr.setProperty(windowFrameRef, "toolBarFontSize", fontSizeFloat);
//            });

//            ///doing this for now (since window prefs seem to be whacked)
//            GuiLafPreferencesManager manager = InstanceManager.getDefault(GuiLafPreferencesManager.class);
//            manager.setFontSize((int) fontSizeFloat);
//        });
        toolBarFontSizeMenu->addAction(fontSizeButton);
        toolBarFontSizeGroup->addAction(fontSizeButton);
        fontSizeButton->setChecked(MathUtil::equals(fontSizeFloat, toolBarFontSize));
    }
#if 0
    toolBarFontSizeMenu.addMenuListener(new MenuListener() {
        @Override
        public void menuSelected(MenuEvent event) {
            String fontSizeString = String.valueOf((int) toolBarFontSize);

            for (Component c : toolBarFontSizeMenu.getMenuComponents()) {
                if (c instanceof JRadioButtonMenuItem) {
                    JRadioButtonMenuItem crb = (JRadioButtonMenuItem) c;
                    String menuItemFontSizeString = crb.getText();
                    crb.setSelected(menuItemFontSizeString.equals(fontSizeString));
                }
            }
        }

        @Override
        public void menuDeselected(MenuEvent event) {
        }

        @Override
        public void menuCanceled(MenuEvent event) {
        }
    });
#endif
    //toolBarMenu.add(toolBarFontSizeMenu); //<<== disabled as per
    //<https://github.com/JMRI/JMRI/pull/3145#issuecomment-283940658>
    //
    //setup drop down list display order menu
    //
    QActionGroup* dropDownListsDisplayOrderGroup = new QActionGroup(this);

    QStringList ddldoChoices = QStringList() << tr("Display Name (User else System)") << tr("UserName") <<
        tr("SystemName") << tr("User Name followed by System Name") <<
        tr("System Name followed by User Name");

    for (QString ddldoChoice : ddldoChoices) {
        QAction* ddldoChoiceMenuItem = new QAction(ddldoChoice, this);
        ddldoChoiceMenuItem->setCheckable(true);
#if 0
        ddldoChoiceMenuItem.addActionListener((ActionEvent event) -> {
            JRadioButtonMenuItem ddldoMenuItem = (JRadioButtonMenuItem) event.getSource();
            JPopupMenu parentMenu = (JPopupMenu) ddldoMenuItem.getParent();
            int ddldoInt = parentMenu.getComponentZOrder(ddldoMenuItem) + 1;
            JmriBeanComboBox.DisplayOptions ddldo = JmriBeanComboBox.DisplayOptions.valueOf(ddldoInt);

            InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefsMgr) -> {
                //change this comboboxes ddldo
                String windowFrameRef = getWindowFrameRef();

                //this is the preference name
                String ddldoPrefName = "DropDownListsDisplayOrder";

                //make a focused component specific preference name
                Component focusedComponent = getFocusOwner();

                if (focusedComponent instanceof JTextField) {
                    focusedComponent = SwingUtilities.getUnwrappedParent(focusedComponent);
                }

                if (focusedComponent instanceof JmriBeanComboBox) {
                    JmriBeanComboBox focusedJBCB = (JmriBeanComboBox) focusedComponent;

                    //now try to get a preference specific to this combobox
                    String ttt = focusedJBCB.getToolTipText();

                    if (ttt != null) {
                        //change the name of the preference based on the tool tip text
                        ddldoPrefName = String.format("%s.%s", ddldoPrefName, ttt);
                    }

                    //now set the combo box display order
                    focusedJBCB.setDisplayOrder(ddldo);
                }

                //update the users preference
                String[] ddldoPrefs = {"DISPLAYNAME", "USERNAME", "SYSTEMNAME", "USERNAMESYSTEMNAME", "SYSTEMNAMEUSERNAME"};
                prefsMgr.setProperty(windowFrameRef, ddldoPrefName, ddldoPrefs[ddldoInt]);
            });
        }); //addActionListener
#endif
        dropDownListsDisplayOrderMenu->addAction(ddldoChoiceMenuItem);
        dropDownListsDisplayOrderGroup->addAction(ddldoChoiceMenuItem);

        //if it matches the 1st choice then select it (for now; it will be updated later)
        ddldoChoiceMenuItem->setChecked(ddldoChoice == (ddldoChoices[0]));
    }
    //TODO: update menu item based on focused combobox (if any)
    //note: commented out to avoid findbug warning
    //dropDownListsDisplayOrderMenu.addMenuListener(new MenuListener() {
    //    @Override
    //    public void menuSelected(MenuEvent event) {
    //        log.debug("update menu item based on focused combobox");
    //    }
    //
    //    @Override
    //    public void menuDeselected(MenuEvent event) {
    //    }
    //
    //    @Override
    //    public void menuCanceled(MenuEvent event) {
    //    }
    //});
    toolBarMenu->addMenu(dropDownListsDisplayOrderMenu);

    //
    // Scroll Bars
    //
    scrollMenu = new QMenu(tr("Panel scrollbars")); //used for ScrollBarsSubMenu
    optionMenu->addMenu(scrollMenu);
    QActionGroup* scrollGroup = new QActionGroup(this);
    scrollBothMenuItem = new QAction(tr("Scroll Both"), this);
    scrollGroup->addAction(scrollBothMenuItem);
    scrollMenu->addAction(scrollBothMenuItem);
    scrollBothMenuItem->setChecked(_scrollState == Editor::SCROLL_BOTH);
//    scrollBothMenuItem.addActionListener((ActionEvent event) -> {
//        _scrollState = Editor.SCROLL_BOTH;
//        setScroll(_scrollState);
//        redrawPanel();
//    });
    connect(scrollBothMenuItem, SIGNAL(triggered(bool)), this, SLOT(onActionBoth_scrollbars()));
    scrollNoneMenuItem = new QAction(tr("No Scrollbars"), this);
    scrollNoneMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollNoneMenuItem);
    scrollMenu->addAction(scrollNoneMenuItem);
    scrollNoneMenuItem->setChecked(_scrollState == Editor::SCROLL_NONE);
//    scrollNoneMenuItem.addActionListener((ActionEvent event) -> {
//        _scrollState = Editor.SCROLL_NONE;
//        setScroll(_scrollState);
//        redrawPanel();
//    });
    connect(scrollNoneMenuItem, SIGNAL(triggered(bool)), this, SLOT(onActionNo_scrollbars()));
    scrollHorizontalMenuItem = new QAction(tr("Horizontal Scrollbars"),this);
    scrollHorizontalMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollHorizontalMenuItem);
    scrollMenu->addAction(scrollHorizontalMenuItem);
    scrollHorizontalMenuItem->setChecked(_scrollState == Editor::SCROLL_HORIZONTAL);
//    scrollHorizontalMenuItem.addActionListener((ActionEvent event) -> {
//        _scrollState = Editor.SCROLL_HORIZONTAL;
//        setScroll(_scrollState);
//        redrawPanel();
//    });
    connect(scrollHorizontalMenuItem, SIGNAL(triggered(bool)), this, SLOT(onActionHorizontal_scrollbars()));
    scrollVerticalMenuItem = new QAction(tr("Vertical scrollbars"), this);
    scrollVerticalMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollVerticalMenuItem);
    scrollMenu->addAction(scrollVerticalMenuItem);
    scrollVerticalMenuItem->setChecked(_scrollState == Editor::SCROLL_VERTICAL);
//    scrollVerticalMenuItem.addActionListener((ActionEvent event) -> {
//        _scrollState = Editor.SCROLL_VERTICAL;
//        setScroll(_scrollState);
//        redrawPanel();
//    });
    connect(scrollVerticalMenuItem, SIGNAL(triggered(bool)), this, SLOT(onActionVertical_scrollbars()));

    //
    // Tooltips
    //
    tooltipMenu = new QMenu(tr("Show Icon tooltips"));
    optionMenu->addMenu(tooltipMenu);
    QActionGroup* tooltipGroup = new QActionGroup(this);
    tooltipNoneMenuItem = new QAction(tr("No Tooltips"), this);
    tooltipNoneMenuItem->setCheckable(true);
    tooltipGroup->addAction(tooltipNoneMenuItem);
    tooltipMenu->addAction(tooltipNoneMenuItem);
    tooltipNoneMenuItem->setChecked((!tooltipsInEditMode) && (!tooltipsWithoutEditMode));
//    tooltipNoneMenuItem.addActionListener((ActionEvent event) -> {
//        tooltipsInEditMode = false;
//        tooltipsWithoutEditMode = false;
//        setAllShowToolTip(false);
//    });
    connect(tooltipNoneMenuItem, SIGNAL(triggered(bool)), this, SLOT(onTooltipNoneMenuItem()));
    tooltipAlwaysMenuItem = new QAction(tr("Tooltips Always"),this);
    tooltipAlwaysMenuItem->setCheckable(true);
    tooltipGroup->addAction(tooltipAlwaysMenuItem);
    tooltipMenu->addAction(tooltipAlwaysMenuItem);
    tooltipAlwaysMenuItem->setChecked((tooltipsInEditMode) && (tooltipsWithoutEditMode));
//    tooltipAlwaysMenuItem.addActionListener((ActionEvent event) -> {
//        tooltipsInEditMode = true;
//        tooltipsWithoutEditMode = true;
//        setAllShowToolTip(true);
//    });
    connect(tooltipAlwaysMenuItem, SIGNAL(triggered(bool)), this, SLOT(onTooltipAlwaysMenuItem()));
    tooltipInEditMenuItem = new QAction(tr("In Edit Mode only"),this);
    tooltipInEditMenuItem->setCheckable(true);
    tooltipGroup->addAction(tooltipInEditMenuItem);
    tooltipMenu->addAction(tooltipInEditMenuItem);
    tooltipInEditMenuItem->setChecked((tooltipsInEditMode) && (!tooltipsWithoutEditMode));
//    tooltipInEditMenuItem.addActionListener((ActionEvent event) -> {
//        tooltipsInEditMode = true;
//        tooltipsWithoutEditMode = false;
//        setAllShowToolTip(isEditable());
//    });
    connect(tooltipInEditMenuItem, SIGNAL(triggered(bool)), this, SLOT(onTooltipInEditMenuItem()));
    tooltipNotInEditMenuItem = new QAction(tr("Not in Edit Mode only"), this);
    tooltipNotInEditMenuItem->setCheckable(true);
    tooltipGroup->addAction(tooltipNotInEditMenuItem);
    tooltipMenu->addAction(tooltipNotInEditMenuItem);
    tooltipNotInEditMenuItem->setChecked((!tooltipsInEditMode) && (tooltipsWithoutEditMode));
//    tooltipNotInEditMenuItem.addActionListener((ActionEvent event) -> {
//        tooltipsInEditMode = false;
//        tooltipsWithoutEditMode = true;
//        setAllShowToolTip(!isEditable());
//    });
    connect(tooltipNotInEditMenuItem, SIGNAL(triggered(bool)), this, SLOT(onTooltipNotInEditMenuItem()));

    //
    // show edit help
    //
    showHelpCheckBoxMenuItem = new QAction(tr("Show Help Bar in Edit Mode"));
    showHelpCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(showHelpCheckBoxMenuItem);
//    showHelpCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        boolean newShowHelpBar = showHelpCheckBoxMenuItem.isSelected();
//        setShowHelpBar(newShowHelpBar);
//    });
    connect(showHelpCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setShowHelpBar(bool)));
    showHelpCheckBoxMenuItem->setChecked(getShowHelpBar());

    //
    // Allow Repositioning
    //
    positionableCheckBoxMenuItem = new QAction(tr("Allow Repositioning"),this);
    positionableCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(positionableCheckBoxMenuItem);
//    positionableCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        setAllPositionable(positionableCheckBoxMenuItem.isSelected());
//    });
    connect(positionableCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setAllPositionable(bool)));
    positionableCheckBoxMenuItem->setChecked(allPositionable());

    //
    // Allow Layout Control
    //
    controlCheckBoxMenuItem = new QAction(tr("Allow Layout Control"),this);
    controlCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(controlCheckBoxMenuItem);
//    controlCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        setAllControlling(controlCheckBoxMenuItem.isSelected());
//        redrawPanel();
//    });
    connect(controlCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_actionAllow_layout_control_toggled(bool)));
    controlCheckBoxMenuItem->setChecked(allControlling());

    //
    // use direct turnout control
    //
    useDirectTurnoutControlCheckBoxMenuItem = new QAction(tr("Use Direct Turnout Control"),this); //IN18N
    useDirectTurnoutControlCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(useDirectTurnoutControlCheckBoxMenuItem);
//    useDirectTurnoutControlCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        setDirectTurnoutControl(useDirectTurnoutControlCheckBoxMenuItem.isSelected());
//    });
    connect(useDirectTurnoutControlCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setDirectTurnoutControl(bool)));
    useDirectTurnoutControlCheckBoxMenuItem->setChecked(useDirectTurnoutControl);

    //
    // antialiasing
    //
    antialiasingOnCheckBoxMenuItem = new QAction(tr("Enable antialiasing (Smoother lines)"),this);
    antialiasingOnCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(antialiasingOnCheckBoxMenuItem);
//    antialiasingOnCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        antialiasingOn = antialiasingOnCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(antialiasingOnCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_actionEnable_antialiasing_smoother_lines_toggled(bool)));
    antialiasingOnCheckBoxMenuItem->setChecked(antialiasingOn);

    //
    // edit title
    //
    optionMenu->addSeparator();
    QAction* titleItem = new QAction(tr("Edit Title") + "...",this);
    optionMenu->addAction(titleItem);
#if 0
    titleItem.addActionListener((ActionEvent event) -> {
        //prompt for name
        String newName = (String) JOptionPane.showInputDialog(getTargetFrame(),
                Bundle.getMessage("MakeLabel", Bundle.getMessage("EnterTitle")),
                Bundle.getMessage("EditTitleMessageTitle"),
                JOptionPane.PLAIN_MESSAGE, null, null, getLayoutName());

        if (newName != null) {
            if (!newName.equals(getLayoutName())) {
                if (InstanceManager.getDefault(PanelMenu.class).isPanelNameUsed(newName)) {
                    JOptionPane.showMessageDialog(null, Bundle.getMessage("CanNotRename"), Bundle.getMessage("PanelExist"),
                            JOptionPane.ERROR_MESSAGE);
                } else {
                    setTitle(newName);
                    setLayoutName(newName);
                    getLayoutTrackDrawingOptions().setName(newName);
                    InstanceManager.getDefault(PanelMenu.class).renameEditorPanel(LayoutEditor.this);
                    setDirty();

                    if (toolBarSide.equals(ToolBarSide.eFLOAT) && isEditable()) {
                        // Rebuild the toolbox after a name change.
                        deleteFloatingEditToolBox();
                        createFloatingEditToolBox();
                    }
                }
            }
        }
    });
#endif


    //
    // set background color
    //
//    QAction* backgroundColorMenuItem = new QAction(t("Set Background Color", "..."),this);
//    optionMenu->addAction(backgroundColorMenuItem);
//    backgroundColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("SetBackgroundColor", ""),
//                defaultBackgroundColor);
//        if (desiredColor != null && !defaultBackgroundColor.equals(desiredColor)) {
//            defaultBackgroundColor = desiredColor;
//            setBackgroundColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
//    connect(backgroundColorMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_colorBackgroundMenuItemSelected()));
    QMenu* backgroundColorMenu = new QMenu(tr("Set Background Color"));
    backgroundColorButtonGroup = new QActionGroup(this);
    backgroundColorButtonMapper = new QSignalMapper();
    connect(backgroundColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_colorBackgroundMenuItemSelected(int)));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Black"),     QColor(Qt::black));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("DarkGray"),  QColor(Qt::darkGray));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Gray"),      QColor(Qt::gray));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("LightGray"), QColor(Qt::lightGray));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("White"),     QColor(Qt::white));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Red"),       QColor(Qt::red));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Pink"),      QColor(255,192,203));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Orange"),    QColor(255, 170, 0));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Yellow"),    QColor(Qt::yellow));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Green"),     QColor(Qt::green));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Blue"),      QColor(Qt::blue));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Magenta"),   QColor(Qt::magenta));
    addBackgroundColorMenuEntry(backgroundColorMenu,    tr("Cyan"),      QColor(Qt::cyan));
    optionMenu->addMenu(backgroundColorMenu);

    //
    // set default text color
    //
//    QAction* textColorMenuItem = new QAction(tr("Default Text Color", "..."),this);
//    optionMenu->addAction(textColorMenuItem);
//    textColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("DefaultTextColor", ""),
//                defaultTextColor);
//        if (desiredColor != null && !defaultTextColor.equals(desiredColor)) {
//            setDefaultTextColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
//    connect(textColorMenuItem, SIGNAL(triggered(bool)), this, SLOT());
    QMenu* textColorMenu = new QMenu(tr("Default Text Color"));
    textColorButtonGroup = new QActionGroup(this);
    textColorButtonMapper = new QSignalMapper();
    connect(textColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(OnDefaultTextColorSelected(int)));
    addTextColorMenuEntry(textColorMenu,  tr("Black"),     QColor(Qt::black));
    addTextColorMenuEntry(textColorMenu,  tr("DarkGray"),  QColor(Qt::darkGray));
    addTextColorMenuEntry(textColorMenu,  tr("Gray"),      QColor(Qt::gray));
    addTextColorMenuEntry(textColorMenu,  tr("LightGray"), QColor(Qt::lightGray));
    addTextColorMenuEntry(textColorMenu,  tr("White"),     QColor(Qt::white));
    addTextColorMenuEntry(textColorMenu,  tr("Red"),       QColor(Qt::red));
    addTextColorMenuEntry(textColorMenu,  tr("Pink"),      QColor(255,192,203));
    addTextColorMenuEntry(textColorMenu,  tr("Orange"),    QColor(255, 170, 0));
    addTextColorMenuEntry(textColorMenu,  tr("Yellow"),    QColor(Qt::yellow));
    addTextColorMenuEntry(textColorMenu,  tr("Green"),     QColor(Qt::green));
    addTextColorMenuEntry(textColorMenu,  tr("Blue"),      QColor(Qt::blue));
    addTextColorMenuEntry(textColorMenu,  tr("Magenta"),   QColor(Qt::magenta));
    addTextColorMenuEntry(textColorMenu,  tr("Cyan"),      QColor(Qt::cyan));
    optionMenu->addMenu(textColorMenu);

    if (editorUseOldLocSize)
    {
     //
     //  save location and size
     //
     QAction* locationItem = new QAction(tr("Set Location"), this);
     optionMenu->addAction(locationItem);
 //    locationItem.addActionListener((ActionEvent event) -> {
 //        setCurrentPositionAndSize();
 //        log.debug("Bounds:{}, {}, {}, {}, {}, {}", upperLeftX, upperLeftY, windowWidth, windowHeight, panelWidth, panelHeight);
 //    });
     connect(locationItem, SIGNAL(triggered(bool)), this, SLOT(on_locationItem()));
    }

    //
    // Add Options
    //
    QMenu* optionsAddMenu = new QMenu(tr("Add"));
    optionMenu->addMenu(optionsAddMenu);

    // add background image
    QAction* backgroundItem = new QAction(tr("Add Background Image") + "...", this);
    optionsAddMenu->addAction(backgroundItem);
//    backgroundItem.addActionListener((ActionEvent event) -> {
//        addBackground();
//        //note: panel resized in addBackground
//        setDirty();
//        redrawPanel();
//    });
    connect(backgroundItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionAdd_background_image_2_triggered()));

    // add fast clock
    QAction* clockItem = new QAction(tr("Add %1").arg(tr("Fast Clock")), this);
    optionsAddMenu->addAction(clockItem);
//    clockItem.addActionListener((ActionEvent event) -> {
//        AnalogClock2Display c = addClock();
//        unionToPanelBounds(c.getBounds());
//        setDirty();
//        redrawPanel();
//    });
    connect(clockItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionAdd_Fast_Clock_triggered()));

    //add turntable
    QAction* turntableItem = new QAction(tr("Add Turntable"),this);
    optionsAddMenu->addAction(turntableItem);
//    turntableItem.addActionListener((ActionEvent event) -> {
//        Point2D pt = windowCenter();
//        if (selectionActive) {
//            pt = MathUtil.midPoint(getSelectionRect());
//        }
//        addTurntable(pt);
//        //note: panel resized in addTurntable
//        setDirty();
//        redrawPanel();
//    });
    connect(turntableItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionAdd_Turntable_triggered()));

    // add reporter
    QAction* reporterItem = new QAction(tr("AddReporter") + "...", this);
    optionsAddMenu->addAction(reporterItem);
//    reporterItem.addActionListener((ActionEvent event) -> {
//        Point2D pt = windowCenter();
//        if (selectionActive) {
//            pt = MathUtil.midPoint(getSelectionRect());
//        }
//        enterReporter((int) pt.getX(), (int) pt.getY());
//        //note: panel resized in enterReporter
//        setDirty();
//        redrawPanel();
//    });
    connect(reporterItem, SIGNAL(triggered(bool)), this, SLOT(on_actionAdd_reporter_label_triggered()));
    //
    // grid menu
    //
    QMenu* gridMenu = new QMenu(tr("Grid Options")); //used for Grid SubMenu
    optionMenu->addMenu(gridMenu);

    //show grid
    showGridCheckBoxMenuItem = new QAction(tr("Show Grid in Edit Mode"), this);
    showGridCheckBoxMenuItem->setCheckable(true);
//    showGridCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(
//            Bundle.getMessage("ShowEditGridAccelerator")), primary_modifier));
    gridMenu->addAction(showGridCheckBoxMenuItem);
//    showGridCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        drawGrid = showGridCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(showGridCheckBoxMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionShow_grid_in_edit_mode_toggled(bool)));
    showGridCheckBoxMenuItem->setChecked(getDrawGrid());

    //snap to grid on add
    snapToGridOnAddCheckBoxMenuItem = new QAction(tr("Snap to Grid when Adding"));
    snapToGridOnAddCheckBoxMenuItem->setCheckable(true);
//    snapToGridOnAddCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(
//            Bundle.getMessage("SnapToGridOnAddAccelerator")),
//            primary_modifier | ActionEvent.SHIFT_MASK));
    gridMenu->addAction(snapToGridOnAddCheckBoxMenuItem);
//    snapToGridOnAddCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        snapToGridOnAdd = snapToGridOnAddCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(snapToGridOnAddCheckBoxMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionSnap_to_grid_when_adding_toggled(bool)));
    snapToGridOnAddCheckBoxMenuItem->setChecked(snapToGridOnAdd);

    //snap to grid on move
    snapToGridOnMoveCheckBoxMenuItem = new QAction(tr("Snap to Grid when Moving"),this);
    snapToGridOnMoveCheckBoxMenuItem->setCheckable(true);
//    snapToGridOnMoveCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(
//            Bundle.getMessage("SnapToGridOnMoveAccelerator")),
//            primary_modifier | ActionEvent.SHIFT_MASK));
    gridMenu->addAction(snapToGridOnMoveCheckBoxMenuItem);
//    snapToGridOnMoveCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        snapToGridOnMove = snapToGridOnMoveCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(snapToGridOnMoveCheckBoxMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_actionSnap_to_grid_when_moving_toggled(bool) ));
    snapToGridOnMoveCheckBoxMenuItem->setChecked(snapToGridOnMove);

    //specify grid square size
    QAction* gridSizeItem = new QAction(tr("SetGridSizes") + "...", this);
    gridMenu->addAction(gridSizeItem);
//    gridSizeItem.addActionListener((ActionEvent event) -> {
//        enterGridSizes();
//    });
    connect(gridSizeItem,  SIGNAL(triggered(bool)), this, SLOT(enterGridSizes()));
    //
    // track menu
    //
    QMenu* trackMenu = new QMenu(tr("Track Options"));
    optionMenu->addMenu(trackMenu);

    // set track drawing options menu item
    QAction* jmi = new QAction(tr("Set Track Drawing Options"));
    trackMenu->addAction(jmi);
    jmi->setToolTip(tr("Select this item to change your track drawing options"));
//    jmi.addActionListener((ActionEvent event) -> {
//        LayoutTrackDrawingOptionsDialog ltdod
//                = new LayoutTrackDrawingOptionsDialog(
//                        this, true, getLayoutTrackDrawingOptions());
//        ltdod.setVisible(true);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onLayoutTrackDrawingOptionsDialog()));
    //set track width menu item
    // Note: Now set via LayoutTrackDrawingOptionsDialog (above)
    //TODO: Dead code strip this
    //JMenuItem widthItem = new JMenuItem(Bundle.getMessage("SetTrackWidth") + "...");
    //trackMenu.add(widthItem);
    //widthItem.addActionListener((ActionEvent event) -> {
    //    //bring up enter track width dialog
    //    enterTrackWidth();
    //});
    //track colors item menu item
    QMenu* trkColourMenu = new QMenu(tr("Default Track Colors"));
    trackMenu->addMenu(trkColourMenu);

//    QAction* trackColorMenuItem = new QAction(tr("Set Default Track Color"),this);
//    trkColourMenu->addAction(trackColorMenuItem);
//    trackColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("DefaultTrackColor"),
//                defaultTrackColor);
//        if (desiredColor != null && !defaultTrackColor.equals(desiredColor)) {
//            setDefaultTrackColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
//    connect(trackColorMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_addTrackColorMenuEntry_triggered));
    QMenu* trackColorMenu = new QMenu(tr("Default Track Color"));
    trackColorButtonGroup = new QActionGroup(this);
    trackColorButtonMapper = new QSignalMapper();
    connect(trackColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackColorMenuEntry_triggered(int)));
    addTrackColorMenuEntry(trackColorMenu, tr("Black"),     QColor(Qt::black));
    addTrackColorMenuEntry(trackColorMenu, tr("DarkGray"),  QColor(Qt::darkGray));
    addTrackColorMenuEntry(trackColorMenu, tr("Gray"),      QColor(Qt::gray));
    addTrackColorMenuEntry(trackColorMenu, tr("LightGray"), QColor(Qt::lightGray));
    addTrackColorMenuEntry(trackColorMenu, tr("White"),     QColor(Qt::white));
    addTrackColorMenuEntry(trackColorMenu, tr("Red"),       QColor(Qt::red));
    addTrackColorMenuEntry(trackColorMenu, tr("Pink"),      QColor(255,192,203));
    addTrackColorMenuEntry(trackColorMenu, tr("Orange"),    QColor(255, 170, 0));
    addTrackColorMenuEntry(trackColorMenu, tr("Yellow"),    QColor(Qt::yellow));
    addTrackColorMenuEntry(trackColorMenu, tr("Green"),     QColor(Qt::green));
    addTrackColorMenuEntry(trackColorMenu, tr("Blue"),      QColor(Qt::blue));
    addTrackColorMenuEntry(trackColorMenu, tr("Magenta"),   QColor(Qt::magenta));
    addTrackColorMenuEntry(trackColorMenu, tr("Cyan"),      QColor(Qt::cyan));
    optionMenu->addMenu(trackColorMenu);

//    QAction* trackOccupiedColorMenuItem = new QAction(tr("Set Default Occupied Track Color"),this);
//    trkColourMenu->addAction(trackOccupiedColorMenuItem);
//    trackOccupiedColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("DefaultOccupiedTrackColor"),
//                defaultOccupiedTrackColor);
//        if (desiredColor != null && !defaultOccupiedTrackColor.equals(desiredColor)) {
//            setDefaultOccupiedTrackColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
//    connect(trackOccupiedColorMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_addTrackOccupiedColorMenuEntry_triggered()));
    QMenu* trackOccupiedColorMenu = new QMenu(tr("Default Occupied Track Color"));
    trackOccupiedColorButtonGroup = new QActionGroup(this);
    trackOccupiedColorButtonMapper = new QSignalMapper();
    connect(trackOccupiedColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackOccupiedColorMenuEntry_triggered(int)));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Black"),     QColor(Qt::black));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("DarkGray"),  QColor(Qt::darkGray));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Gray"),      QColor(Qt::gray));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("LightGray"), QColor(Qt::lightGray));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("White"),     QColor(Qt::white));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Red"),       QColor(Qt::red));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Pink"),      QColor(255,192,203));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Orange"),    QColor(255, 170, 0));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Yellow"),    QColor(Qt::yellow));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Green"),     QColor(Qt::green));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Blue"),      QColor(Qt::blue));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Magenta"),   QColor(Qt::magenta));
    addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, tr("Cyan"),      QColor(Qt::cyan));
    optionMenu->addMenu(trackOccupiedColorMenu);

//    QAction* trackAlternativeColorMenuItem = new QAction(tr("Set Default Alternative Track Color"),this);
//    trkColourMenu->addAction(trackAlternativeColorMenuItem);
//    trackAlternativeColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("DefaultAlternativeTrackColor"),
//                defaultAlternativeTrackColor);
//        if (desiredColor != null && !defaultAlternativeTrackColor.equals(desiredColor)) {
//            setDefaultAlternativeTrackColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
//    connect(trackAlternativeColorMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_addTrackAlternativeColorMenuEntry_triggered()));
    QMenu* trackAlternativeColorMenu = new QMenu(tr("Default Alternative Track Color"));
    trackAlternativeColorButtonGroup = new QActionGroup(this);
    trackAlternativeColorButtonMapper = new QSignalMapper();
    connect(trackAlternativeColorButtonMapper, SIGNAL(mapped(int)), this, SLOT(on_addTrackAlternativeColorMenuEntry_triggered(int)));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Black"),     QColor(Qt::black));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("DarkGray"),  QColor(Qt::darkGray));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Gray"),      QColor(Qt::gray));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("LightGray"), QColor(Qt::lightGray));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("White"),     QColor(Qt::white));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Red"),       QColor(Qt::red));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Pink"),      QColor(255,192,203));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Orange"),    QColor(255, 170, 0));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Yellow"),    QColor(Qt::yellow));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Green"),     QColor(Qt::green));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Blue"),      QColor(Qt::blue));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Magenta"),   QColor(Qt::magenta));
    addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu,  tr("Cyan"),      QColor(Qt::cyan));
    optionMenu->addMenu(trackAlternativeColorMenu);

    //Automatically Assign Blocks to Track
    autoAssignBlocksCheckBoxMenuItem = new QAction(tr("Automatically Assign Blocks to Track"),this);
    autoAssignBlocksCheckBoxMenuItem->setCheckable(true);
    trackMenu->addAction(autoAssignBlocksCheckBoxMenuItem);
//    autoAssignBlocksCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        autoAssignBlocks = autoAssignBlocksCheckBoxMenuItem.isSelected();
//    });
    connect(autoAssignBlocksCheckBoxMenuItem,  SIGNAL(triggered(bool)), this, SLOT(on_autoAssignBlocksItem_triggered(bool)));
    autoAssignBlocksCheckBoxMenuItem->setChecked(autoAssignBlocks);

    //add hideTrackSegmentConstructionLines menu item
    hideTrackSegmentConstructionLinesCheckBoxMenuItem = new QAction(tr("Hide Track Construction Lines"));
    hideTrackSegmentConstructionLinesCheckBoxMenuItem->setCheckable(true);
    trackMenu->addAction(hideTrackSegmentConstructionLinesCheckBoxMenuItem);
//    hideTrackSegmentConstructionLinesCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        int show = TrackSegment.SHOWCON;

//        if (hideTrackSegmentConstructionLinesCheckBoxMenuItem.isSelected()) {
//            show = TrackSegment.HIDECONALL;
//        }

//        for (TrackSegment ts : getTrackSegments()) {
//            ts.hideConstructionLines(show);
//        }
//        redrawPanel();
//    });
    connect(hideTrackSegmentConstructionLinesCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_hideTrackSegmentConstructionLines_toggled(bool) ));
    hideTrackSegmentConstructionLinesCheckBoxMenuItem->setChecked(autoAssignBlocks);

    //
    //add turnout options submenu
    //
    QMenu* turnoutOptionsMenu = new QMenu(tr("Turnout Options"));
    optionMenu->addMenu(turnoutOptionsMenu);

    //animation item
    animationCheckBoxMenuItem = new QAction(tr("Allow Turnout Animation"), this);
    animationCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(animationCheckBoxMenuItem);
//    animationCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        boolean mode = animationCheckBoxMenuItem.isSelected();
//        setTurnoutAnimation(mode);
//    });
    connect(animationCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setTurnoutAnimation(bool)));
    animationCheckBoxMenuItem->setChecked(true);

    //circle on Turnouts
    turnoutCirclesOnCheckBoxMenuItem = new QAction(tr("Show Turnout Circles"), this);
    turnoutCirclesOnCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(turnoutCirclesOnCheckBoxMenuItem);
//    turnoutCirclesOnCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        turnoutCirclesWithoutEditMode = turnoutCirclesOnCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(turnoutCirclesOnCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(On_turnoutCirclesOnItem_triggered(bool)));
    turnoutCirclesOnCheckBoxMenuItem->setChecked(turnoutCirclesWithoutEditMode);

    //select turnout circle color
    QAction* turnoutCircleColorMenuItem = new QAction(tr("Set Turnout Circle Color"), this);

//    turnoutCircleColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                Bundle.getMessage("TurnoutCircleColor"),
//                turnoutCircleColor);
//        if (desiredColor != null && !turnoutCircleColor.equals(desiredColor)) {
//            setTurnoutCircleColor(desiredColor);
//            setDirty();
//            redrawPanel();
//        }
//    });
    connect(turnoutCircleColorMenuItem, SIGNAL(triggered(bool)), this, SLOT(onTurnoutCircleColorMenuItem()));
    turnoutOptionsMenu->addAction(turnoutCircleColorMenuItem);

    //select turnout circle size
    QMenu* turnoutCircleSizeMenu = new QMenu(tr("Set Turnout Circle Size"));
#if 1
    turnoutCircleSizeButtonGroup = new QActionGroup(this);
    turnoutCircleSizeButtonMapper = new QSignalMapper(this);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "1", 1);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "2", 2);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "3", 3);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "4", 4);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "5", 5);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "6", 6);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "7", 7);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "8", 8);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "9", 9);
    addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "10", 10);
#endif
    turnoutOptionsMenu->addMenu(turnoutCircleSizeMenu);

    //add "enable drawing of unselected leg " menu item (helps when diverging angle is small)
    turnoutDrawUnselectedLegCheckBoxMenuItem = new QAction(tr("Draw Unselected Turnout Leg"),this);
    turnoutDrawUnselectedLegCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(turnoutDrawUnselectedLegCheckBoxMenuItem);
//    turnoutDrawUnselectedLegCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        turnoutDrawUnselectedLeg = turnoutDrawUnselectedLegCheckBoxMenuItem.isSelected();
//        redrawPanel();
//    });
    connect(turnoutDrawUnselectedLegCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(On_turnoutDrawUnselectedLegItem_triggered(bool)));
    turnoutDrawUnselectedLegCheckBoxMenuItem->setChecked(turnoutDrawUnselectedLeg);

    return optionMenu;
}
#endif
void LayoutEditor::onTurnoutCircleColorMenuItem()
{
 QColor desiredColor = JmriColorChooser::showDialog(this,
         tr("Turnout Circle Color"),
         turnoutCircleColor);
 if (desiredColor != nullptr && turnoutCircleColor!=(desiredColor)) {
     setTurnoutCircleColor(desiredColor);
     setDirty();
     redrawPanel();
 }
}

void LayoutEditor::onTooltipNoneMenuItem()
{
 tooltipsInEditMode = false;
 tooltipsWithoutEditMode = false;
 setAllShowToolTip(false);
}

void LayoutEditor::onTooltipAlwaysMenuItem()
{
 tooltipsInEditMode = true;
 tooltipsWithoutEditMode = true;
 setAllShowToolTip(true);
}
void LayoutEditor::onTooltipInEditMenuItem()
{
 tooltipsInEditMode = true;
 tooltipsWithoutEditMode = false;
 setAllShowToolTip(isEditable());
}
void LayoutEditor::onTooltipNotInEditMenuItem()
{
 tooltipsInEditMode = false;
 tooltipsWithoutEditMode = true;
 setAllShowToolTip(!isEditable());
}

void LayoutEditor::on_locationItem()
{
 setCurrentPositionAndSize();
 log->debug(tr("Bounds:%1, %2, %3, %4, %5, %6").arg(upperLeftX).arg(upperLeftY).arg(windowWidth).arg(windowHeight).arg(panelWidth).arg(panelHeight));
}

/*============================================*\
|* LayoutTrackDrawingOptions accessor methods *|
\*============================================*/

//@Nonnull
/*public*/ LayoutTrackDrawingOptions* LayoutEditor::getLayoutTrackDrawingOptions() {
    if (layoutTrackDrawingOptions == nullptr) {
        layoutTrackDrawingOptions = new LayoutTrackDrawingOptions(getLayoutName());
        // integrate LayoutEditor drawing options with previous drawing options
        layoutTrackDrawingOptions->setMainBlockLineWidth((int) mainlineTrackWidth);
        layoutTrackDrawingOptions->setSideBlockLineWidth((int) sidelineTrackWidth);
        layoutTrackDrawingOptions->setMainRailWidth((int) mainlineTrackWidth);
        layoutTrackDrawingOptions->setSideRailWidth((int) sidelineTrackWidth);
        layoutTrackDrawingOptions->setMainRailColor(defaultTrackColor);
        layoutTrackDrawingOptions->setSideRailColor(defaultTrackColor);
    }
    return layoutTrackDrawingOptions;
}

/*public*/ void LayoutEditor::setLayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo) {
    layoutTrackDrawingOptions = ltdo;

    // integrate LayoutEditor drawing options with previous drawing options
    mainlineTrackWidth = layoutTrackDrawingOptions->getMainBlockLineWidth();
    sidelineTrackWidth = layoutTrackDrawingOptions->getSideBlockLineWidth();
    defaultTrackColor = layoutTrackDrawingOptions->getMainRailColor();
    redrawPanel();
}
/**
 * setup the Layout Editor Tools menu
 *
 * @param menuBar the menu bar to add the Tools menu to
 */
/*protected*/ void LayoutEditor::setupToolsMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* toolsMenu = ui->menuTools;//new QMenu(tr("Tools"));

//    toolsMenu.setMnemonic(stringsToVTCodes.get(tr("MenuToolsMnemonic")));
//    menuBar->addMenu(toolsMenu);

    //setup checks menu
    getLEChecks()->setupChecksMenu(toolsMenu);

    //assign blocks to selection
    QAction* jmi = new QAction(tr("Assign Block To Selection") + "...");
    setToolTip(tr("Select this to assign the block from the toolbar to all selected layout tracks."));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up scale track diagram dialog
//        assignBlockToSelection();
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(assignBlockToSelection()));

    //scale track diagram
    jmi = new QAction(tr("Scale/Translate Track Diagram") + "...");
    setToolTip(tr("Select this to scale and/or translate all layout track"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up scale track diagram dialog
//        scaleTrackDiagram();
//    });

    //translate selection
    jmi = new QAction(tr("Translate Selection") + "...", this);
    jmi->setToolTip(tr("Click here to translate (move) the currently selected items"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up translate selection dialog
//        moveSelection();
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(moveSelection()));

    //undo translate selection
    jmi = new QAction(tr("Undo Translate Selection"),this);
    jmi->setToolTip(tr("Click here to undo the translate (move) selection"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //undo previous move selection
//        undoMoveSelection();
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(undoMoveSelection()));

    //reset turnout size to program defaults
    jmi = new QAction(tr("Use Program Default Turnout Size"),this);
    jmi->setToolTip(tr("Click here to reset to the default turnout size"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //undo previous move selection
//        resetTurnoutSize();
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(resetTurnoutSize()));
    toolsMenu->addSeparator();

    //skip turnout
    skipTurnoutCheckBoxMenuItem = new QAction(tr("Skip Unsignaled Internal Turnouts"), this);
    skipTurnoutCheckBoxMenuItem->setCheckable(true);
    skipTurnoutCheckBoxMenuItem->setToolTip(tr("SkipInternalTurnoutToolTip"));
    toolsMenu->addAction(skipTurnoutCheckBoxMenuItem);
//    skipTurnoutCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        setIncludedTurnoutSkipped(skipTurnoutCheckBoxMenuItem.isSelected());
//    });
    connect(skipTurnoutCheckBoxMenuItem, SIGNAL(triggered(bool)), this, SLOT(setIncludedTurnoutSkipped(bool)));
    skipTurnoutCheckBoxMenuItem->setChecked(isIncludedTurnoutSkipped());

    //set signals at turnout
    jmi = new QAction(tr("Set Signal Heads at Turnout") + "...");
    jmi->setToolTip(tr("Click here to set up the signal heads at a turnout"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at turnout tool dialog
//        getLETools()->setSignalsAtTurnout(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Turnout_triggered()));

    //set signals at block boundary
    jmi = new QAction(tr("Set Signal Heads at Block Boundary") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a block boundary"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at block boundary tool dialog
//        getLETools().setSignalsAtBlockBoundary(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Block_Boundary_triggered()));

    //set signals at crossover turnout
    jmi = new QAction(tr("Set Signal Heads at Crossover") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a crossover"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at crossover tool dialog
//        getLETools().setSignalsAtXoverTurnout(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Crossover_triggered()));

    //set signals at level crossing
    jmi = new QAction(tr("Set Signal Heads at Level Crossing") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a level crossing"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at level crossing tool dialog
//        getLETools().setSignalsAtLevelXing(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Level_Crossing_triggered()));

    //set signals at throat-to-throat turnouts
    jmi = new QAction(tr("Set Signal Heads at Throat-to-Throat Turnouts") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signals on throat-to-throat turnouts"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at throat-to-throat turnouts tool dialog
//        getLETools().setSignalsAtThroatToThroatTurnouts(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Throat_to_Throat_Turnouts_triggered()));

    //set signals at 3-way turnout
    jmi = new QAction(tr("Set Signal Heads at 3-Way Turnout") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a 3-way turnout"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at 3-way turnout tool dialog
//        getLETools().setSignalsAt3WayTurnout(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Three_Way_Turnout()));

    jmi = new QAction(tr("Set Signal Heads at a Slip") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a single or double slip"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        //bring up signals at throat-to-throat turnouts tool dialog
//        getLETools().setSignalsAtSlip(signalIconEditor, signalFrame);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionSet_Signals_at_Slip_triggered()));

    jmi = new QAction(tr("Entry Exit") + "...", this);
    jmi->setToolTip(tr("Click here to set up Entry-Exit"));
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
//        if (addEntryExitPairAction == null) {
//            addEntryExitPairAction = new AddEntryExitPairAction("ENTRY EXIT", LayoutEditor.this);
//        }
//        addEntryExitPairAction.actionPerformed(event);
//    });
    connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_actionEntry_Exit_triggered()));

    toolsMenu->addSeparator();
    QAction* clearAction = new QAction(tr("Clear track"), this);
    toolsMenu->addAction(clearAction);
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(On_clearTrack()));
}

void LayoutEditor::onTranslateSelections()
{
 //bring up translate selection dialog
 moveSelection();
}

void LayoutEditor::On_clearTrack()
{
 // remove existing items from scene
 for(LayoutTrack* layoutTrack : *layoutTrackList)
 {
  layoutTrack->invalidate(editScene);
 }
 QList<QGraphicsItem*> items = editScene->items();
 foreach(QGraphicsItem* item, items)
 {
  if(item->zValue() == Editor::HANDLES+1)
  {
   editScene->removeItem(item);
   delete item;
  }
 }
}
//
//update drop down menu display order menu
//

/*private*/ void LayoutEditor::updateDropDownMenuDisplayOrderMenu() {
#if 0
    Component* focusedComponent = getFocusOwner();

    if (qobject_cast<JmriBeanComboBox*>(focusedComponent)) {
        JmriBeanComboBox* focusedJBCB = (JmriBeanComboBox*) focusedComponent;
        gDDMDO = focusedJBCB->getDisplayOrder();
    }

    int idx = 0, ddmdoInt = gDDMDO.getValue();

    for (Component* c : dropDownListsDisplayOrderMenu.getMenuComponents()) {
        if (qobject_cast<QAction*>(c)) {
            QAction* crb = (QAction*) c;
            crb->setSelected(ddmdoInt == idx);
            idx++;
        }
    }
#endif
}

//
//update drop down menu display order for all combo boxes (from prefs)
//
/*private*/ void LayoutEditor::updateAllComboBoxesDropDownListDisplayOrderFromPrefs() {
    //1st call the recursive funtion starting from the edit toolbar container
#if 0
    updateComboBoxDropDownListDisplayOrderFromPrefs(editToolBarContainerPanel);
    updateComboBoxDropDownListDisplayOrderFromPrefs(floatingEditContentScrollPane);
#endif
    //and now that that's done update the drop down menu display order menu
    updateDropDownMenuDisplayOrderMenu();
}

//
//update drop down menu display order for all combo boxes (from prefs)
//note: recursive function that walks down the component / container tree
//
/*private*/ void LayoutEditor::updateComboBoxDropDownListDisplayOrderFromPrefs(/*@Nonnull*/ Component* inComponent)
{
#if 0
    if (qobject_cast<JmriBeanComboBox*>(inComponent))
    {
        //try to get the preference
        //InstanceManager::getOptionalDefault("UserPreferencesManager").ifPresent((prefsMgr) ->
     UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
     if(prefsMgr)
     {
            QString windowFrameRef = getWindowFrameRef();

            //this is the preference name
            QString ddldoPrefName = "DropDownListsDisplayOrder";

            //this is the default value if we can't find it in any preferences
            QString ddldoPref = "DISPLAYNAME";

            QVariant ddldoProp = prefsMgr->getProperty(windowFrameRef, ddldoPrefName);

            if (ddldoProp.isValid()) {
                //this will be the value if this combo box doesn't have a saved preference.
                ddldoPref = ddldoProp.toString();
            } else {
                //save a default preference
                prefsMgr->setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
            }

            //now try to get a preference specific to this combobox
            JmriBeanComboBox* jbcb = (JmriBeanComboBox*) inComponent;
            if (qobject_cast<JTextField*>(inComponent)
            {
                jbcb = (JmriBeanComboBox*) SwingUtilities.getUnwrappedParent(jbcb);
            }
            if (jbcb != null) {
                QString ttt = jbcb.getToolTipText();
                if (ttt != null) {
                    //change the name of the preference based on the tool tip text
                    ddldoPrefName = String.format("%s.%s", ddldoPrefName, ttt);
                    //try to get the preference
                    ddldoProp = prefsMgr.getProperty(getWindowFrameRef(), ddldoPrefName);
                    if (ddldoProp != null) { //if we found it...
                        ddldoPref = ddldoProp.toString(); //get it's (string value
                    } else { //otherwise...
                        //save it in the users preferences
                        prefsMgr.setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
                    }
                }

                //now set the combo box display order
                if (ddldoPref.equals("DISPLAYNAME")) {
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
                } else if (ddldoPref.equals("USERNAME")) {
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.USERNAME);
                } else if (ddldoPref.equals("SYSTEMNAME")) {
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.SYSTEMNAME);
                } else if (ddldoPref.equals("USERNAMESYSTEMNAME")) {
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.USERNAMESYSTEMNAME);
                } else if (ddldoPref.equals("SYSTEMNAMEUSERNAME")) {
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.SYSTEMNAMEUSERNAME);
                } else {
                    //must be a bogus value... lets re-set everything to DISPLAYNAME
                    ddldoPref = "DISPLAYNAME";
                    prefsMgr.setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
                }
            }
        });

    } else if (qobject_cast<Container*>(inComponent)) {
        for (Component* c : ((Container*) inComponent).getComponents()) {
            updateComboBoxDropDownListDisplayOrderFromPrefs(c);
        }
    } else {
        //nothing to do here... move along...
    }
#endif
}
#if 1
//
//
//
/*private*/ void LayoutEditor::setToolBarSide(ToolBarSide::TOOLBARSIDES newToolBarSide) {
    // null if edit toolbar is not setup yet...
    if ((editModeCheckBoxMenuItem != nullptr) && !(newToolBarSide ==(toolBarSide.getName()))) {
        toolBarSide.getName() = newToolBarSide;
        UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager")); //.ifPresent((prefsMgr) -> {
        if(prefsMgr)
            prefsMgr->setProperty(getWindowFrameRef(), "toolBarSide", toolBarSide.getName());
        }//);
#if 0
        setupToolBar(); //re-layout all the toolbar items

        if (toolBarSide.equals(ToolBarSide.eFLOAT)) {
            createFloatingEditToolBox();
            if (editToolBarContainerPanel != null) {
                editToolBarContainerPanel.setVisible(false);
            }
        } else {
            if (floatingEditToolBoxFrame != null) {
                deleteFloatingEditToolBox();
            }
            floatingEditContentScrollPane = null; // The switch to toolbar will move the toolbox content to the new toolbar
            editToolBarContainerPanel.setVisible(isEditable());
        }
        toolBarSideTopButton.setSelected(toolBarSide.equals(ToolBarSide.eTOP));
        toolBarSideLeftButton.setSelected(toolBarSide.equals(ToolBarSide.eLEFT));
        toolBarSideBottomButton.setSelected(toolBarSide.equals(ToolBarSide.eBOTTOM));
        toolBarSideRightButton.setSelected(toolBarSide.equals(ToolBarSide.eRIGHT));
        toolBarSideFloatButton.setSelected(toolBarSide.equals(ToolBarSide.eFLOAT));

        if (toolBarSide.equals(ToolBarSide.eFLOAT)) {
            floatEditHelpPanel.setVisible(isEditable() && getShowHelpBar());
        } else if (getShowHelpBar()) {
            //not sure why... but this is the only way I could
            //get everything to layout correctly
            //when the helpbar is visible...
            boolean editMode = isEditable();
            setAllEditable(!editMode);
            setAllEditable(editMode);
        } else {
            helpBarPanel.setVisible(isEditable() && getShowHelpBar());
        }
    }
#endif
}

//
//
//
/*private*/ void LayoutEditor::setToolBarWide(bool newToolBarIsWide) {
    //null if edit toolbar not setup yet...
    if ((editModeCheckBoxMenuItem != nullptr) && (toolBarIsWide != newToolBarIsWide)) {
        toolBarIsWide = newToolBarIsWide;

        wideToolBarCheckBoxMenuItem->setChecked(toolBarIsWide);
        UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
        if(prefsMgr) {
            //Note: since prefs default to false and we want wide to be the default
            //we invert it and save it as thin
            prefsMgr->setSimplePreferenceState(getWindowFrameRef() + ".toolBarThin", !toolBarIsWide);
        }//);
#if 0
        setupToolBar(); //re-layout all the toolbar items

        if (getShowHelpBar()) {
            //not sure why, but this is the only way I could
            //get everything to layout correctly
            //when the helpbar is visible...
            boolean editMode = isEditable();
            setAllEditable(!editMode);
            setAllEditable(editMode);
        } else {
            helpBarPanel.setVisible(isEditable() && getShowHelpBar());
        }
#endif
    }
}
#endif
#if 0 // not necessary; QGraphicsView does this!
/*private*/ void LayoutEditor::adjustScrollBars() {
   QScrollArea* scrollPane = getPanelScrollPane();
   //JViewport viewPort = scrollPane.getViewport();
   //Dimension viewSize = viewPort.getViewSize();
   QSize viewSize = scrollPane->size();
   QSize panelSize = _targetPanel->size();

   if ((panelWidth != (int) panelSize.width())
           || (panelHeight != (int) panelSize.height())) {
       log->debug(tr("viewSize: %1, %2, panelSize: %3, %4, panelWidth: %5, panelHeight: %6").arg(
               viewSize.x()).arg(viewSize.y()).arg(panelSize.x()).arg(panelSize.y()).arg(panelWidth).arg(panelHeight));
   }

   QScrollBar* horScroll = scrollPane->horizontalScrollBar();
   int w = (int) qMax((panelWidth * getZoom()) - viewSize.width(), 0.0);
   int x = qMin(horScroll->value(), w);
   horScroll->setMaximum(w);
   horScroll->setValue(x);

   QScrollBar* vertScroll = scrollPane->verticalScrollBar();
   int h = (int) qMax((panelHeight * getZoom()) - viewSize.height(), 0.0);
   int y = qMin(vertScroll->value(), h);
   vertScroll->setMaximum(h);
   vertScroll->setValue(y);

   log->debug(tr("w: %1, x: %2, h: %3, y: %4").arg(w).arg(x).arg(h).arg(y));
}
#endif
/**
 * @return the point {0, 0}
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF LayoutEditor::zeroQPointF() {
    return QPointF(0, 0);
}

void LayoutEditor::onActionBoth_scrollbars()
{
 editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
 editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
void LayoutEditor::onActionNo_scrollbars()
{
 editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void LayoutEditor::onActionHorizontal_scrollbars()
{
 editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
 editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void LayoutEditor::onActionVertical_scrollbars()
{
 editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

//    protected void rename(String inFrom, String inTo) {
//
//    }
//@Override
/*public*/ void LayoutEditor::dispose() {
    if (sensorFrame != nullptr) {
        sensorFrame->dispose();
        sensorFrame = nullptr;
    }
    if (signalFrame != nullptr) {
        signalFrame->dispose();
        signalFrame = nullptr;
    }
    if (iconFrame != nullptr) {
        iconFrame->dispose();
        iconFrame = nullptr;
    }
    Editor::dispose();
}

//initialize logging
    /*private*/ /*transient*/ /*final*/ /*static*/ Logger* LayoutEditor::log
            = LoggerFactory::getLogger("LayoutEditor");
