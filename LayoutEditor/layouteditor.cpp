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
#include "loadxml.h"
#include <QColor>
#include "savexml.h"
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
#include "rfidsensormanager.h"
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

/*private*/ /*static*/ const double LayoutEditor::SIZE = 3.0;
/*private*/ /*static*/ const double LayoutEditor::SIZE2 = 6.0;  // must be twice SIZE

LayoutEditor::LayoutEditor(QString name, bool bTest, QWidget *parent) :
    PanelEditor(name, parent),
    ui(new Ui::LayoutEditor)
{
 ui->setupUi(this);
 memo = NULL;
 this->bTestMode = bTest;
 layoutName = name;
 init();
}

LayoutEditor::LayoutEditor(LocoNetSystemConnectionMemo* memo, QString name,  bool bTest, QWidget *parent) :
    PanelEditor(name, parent),
    ui(new Ui::LayoutEditor)
{
 setObjectName("LayoutEditor");
 ui->setupUi(this);
 this->bTestMode = bTest;
 this->memo = memo;
 layoutName = name;
 init();
}

LayoutEditor::~LayoutEditor()
{
    delete ui;
}
void LayoutEditor::init()
{
 setObjectName("LayoutEditor");
 StoreXmlUserAction* savePanels = new StoreXmlUserAction(tr("Save Panels..."), this);
 ui->menuFile->insertAction(ui->actionSave_panels,savePanels);
 ui->menuFile->removeAction(ui->actionSave_panels); // remove the old one.
 _contents = new QVector<Positionable*>();
 pointList = new QVector<PositionablePoint*>();  // PositionablePoint list
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
 beginObject = NULL; // begin track segment connection object, NULL if none
 beginPointType = 0;   // connection type within begin connection object
 foundObject = NULL; // found object, NULL if nothing found
 foundPointType = 0;   // connection type within the found object
 newTrack = NULL;
 numLevelXings = 0;
 numLayoutSlips = 0;
 numLayoutTurntables = 0;

 if(PanelMenu::instance()->isPanelNameUsed(name))
 {
  log.warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }
 PanelMenu::instance()->addEditorPanel(this);
 PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
 connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));

 HelpUtil::instance()->helpMenu(menuBar(), "package.jmri.jmrit.display.LayoutEditor", true);
 resetDirty();
 // establish link to LayoutEditorAuxTools
 auxTools = new LayoutEditorAuxTools(this);
 tools = NULL;
 if (auxTools==NULL) log.error("Unable to create link to LayoutEditorAuxTools");
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
 _positionableSelection = NULL;
 _turnoutSelection = NULL; //new QVector<LayoutTurnout*>();  // LayoutTurnouts
 _xingSelection = NULL; //new QVector<LevelXing*>();  // LevelXing list
 _slipSelection = NULL; //new QVector<LayoutSlip*>();  // LayoutSlip list
 _turntableSelection = NULL;
 _pointSelection = NULL; //new QVector<PositionablePoint*>();  // PositionablePoint list
 //_labelSelection = NULL; //new QVector<PositionableLabel*>(); // PositionalLabel list
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
 prevSelectedObject = NULL;
 _anchorX = 0;
 _anchorY = 0;
//layoutBlockManager = new LayoutBlockManager(this);
 layoutBlockManager = InstanceManager::layoutBlockManagerInstance();
 blockManger = new BlockManager(this);
 defaultTrackColor =  QColor(Qt::black);;
 defaultOccupiedTrackColor =  QColor(Qt::red);
 defaultAlternativeTrackColor =  QColor(Qt::white);

 defaultTextColor =  QColor(Qt::black);
 turnoutCircleColor = defaultTrackColor; //matches earlier versions
 turnoutCircleSize=2;  //matches earlier versions
 turnoutList = new QVector<LayoutTurnout*>();  // LayoutTurnouts
 turntableList = new QVector<LayoutTurntable*>(); // Turntable list
 noWarnTurntable = false;

 _positionableSelection = NULL;//new QVector<Positionable*>();
 //_turnoutSelection = NULL;//new menuAdd_background_image<LayoutTurnout*>();  // LayoutTurnouts
 foundNeedsConnect = false; // true if found point needs a connection
 xingList = new QVector<LevelXing*>();  // LevelXing list
 slipList = new QVector<LayoutSlip*>();  // Layout slip list
 _editable = false;
 _controlLayout = false;
 _positionable = false;
 animatingLayout = true;
 showHelpBar = true;
 bDirty = false;
 noWarnLevelXing = false;
 noWarnSlip = false;
 selectedObject = NULL;
 selectedPointType = 0;
 skipIncludedTurnout = false;
 mainlineTrackWidth = 4.0F;
 sideTrackWidth = 2.0F;
 main = true;
 trackWidth = sideTrackWidth;
 _selectionGroup = NULL;
 turnoutCirclesWithoutEditMode = false;
 ui->actionShow_turnout_circles->setChecked(turnoutCirclesWithoutEditMode);
 isDragging = false;
 foundObject = NULL;
 trackList = new QVector<TrackSegment*>();  // TrackSegment list
 drawGrid =false;
 ui->actionShow_grid_in_edit_mode->setChecked(drawGrid);
 antialiasingOn = false;
 noWarnPositionablePoint= false;
 _labelImage = new QVector<PositionableLabel*>(); // layout positionable label images
 memoryLabelList = new QVector<MemoryIcon*>(); // Memory Label List
 backgroundImage = new QVector<PositionableLabel*>();  // background images
 sensorImage = new QVector<SensorIcon*>();  // sensor images
 iconEditor = new MultiIconEditor(1);
 iconEditor->setIcon(0, "",":/resources/icons/smallschematics/tracksegments/block.gif");
 iconEditor->complete();
//makeBackgroundColorMenu(ui->menuSet_Background_color);
 signalIconEditor = NULL;
 clocks = new QVector<AnalogClock2Display*>();  // fast clocks
 signalHeadImage = new QVector<SignalHeadIcon*>();  // signal head images
 signalMastImage = new QVector<SignalMastIcon*>();  // signal mast images
 signalList = new QVector<SignalHeadIcon*>();  // Signal Head Icons
 signalMastList = new QVector<SignalMastIcon*>();  // Signal Head Icons
 multiSensors = new QVector<MultiSensorIcon*>(); // MultiSensor Icons
 skipIncludedTurnout = false;

 qApp->processEvents();
 panelGridGroup = NULL;
 trackInProgress = NULL;
 rectItem = NULL;
 highlightRect = NULL;
 noWarnGlobalDelete = false;
 multiSensorFrame = NULL;
 openDispatcherOnLoad = false;
 useDirectTurnoutControl = false; // Uses Left click for closing points, Right click for throwing.
 turnoutDrawUnselectedLeg = true;

 if(memo==NULL)
  memo = new LocoNetSystemConnectionMemo();
 lnSensorManager = memo->getSensorManager();

 turnoutDrawUnselectedLeg = true;
 _showCoordinates = true;
 selectedNeedsConnect = false;
 sensorList = new QVector<SensorIcon*>();  // Sensor Icons
 delayedPopupTrigger = false;
 isDragging = false;
 _defaultToolTip = "";

 buttonGroup = new QButtonGroup(this);
 buttonGroup->addButton(ui->chkAnchorPoint);

 buttonGroup->addButton(ui->chkDoubleXover);
 buttonGroup->addButton(ui->chkEndBumper);
 buttonGroup->addButton(ui->chkIconLabel);
 buttonGroup->addButton(ui->chkLevelCrossing);
 buttonGroup->addButton(ui->chkLH);
 buttonGroup->addButton(ui->chkLHXover);
 buttonGroup->addButton(ui->chkMemoryLabel);
 buttonGroup->addButton(ui->chkMultisensor);
 buttonGroup->addButton(ui->chkRH);
 buttonGroup->addButton(ui->chkRHXover);
 buttonGroup->addButton(ui->chkSensorIcon);
 buttonGroup->addButton(ui->chkSignalHeadIcon);
 buttonGroup->addButton(ui->chkSignalMastIcon);
 buttonGroup->addButton(ui->chkTextLabel);
 buttonGroup->addButton(ui->chkTrackSegment);
 buttonGroup->addButton(ui->chkDoubleSlip);
 buttonGroup->addButton(ui->chkSingleSlip);
 buttonGroup->addButton(ui->chkWYE);
 //trkBtnGrp = new QButtonGroup(this);
 //trkBtnGrp->addButton(ui->chkDashed);
 //trkBtnGrp->addButton(ui->chkMainline);
 paintScale = 1.0;
 editPanel = new QGraphicsView(ui->centralWidget);
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
 _targetPanel = editScene;
 defaultBackgroundColor =  editScene->backgroundBrush().color();//QColor(Qt::lightGray);

#if 0
 _Colors << tr("Black")<<tr("Dark Gray")<<tr("Gray")<<tr("Light Gray")<<tr("White")<<tr("Red")<<tr("Pink") <<tr("Orange")<<tr("Yellow")<<tr("Green")<<tr("Blue")<<tr("Magenta");
 _colors << QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) << QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red)<<QColor(255,192,203) << QColor(255, 170, 0) << QColor(Qt::yellow ) << QColor(Qt::green) <<QColor(Qt::blue) <<QColor(Qt::magenta)<<QColor();
// QActionGroup* trackColorActGrp =new QActionGroup(this);
// QActionGroup* textColorActGrp = new QActionGroup(this);
 QActionGroup* backgroundColorActGrp = new QActionGroup(this);
 QBrush defaultBackgroundBrush = editScene->backgroundBrush();
 QColor defaultBackgroundColor = defaultBackgroundBrush.color();

 for(int i=0; i < _Colors.size(); i++)
 {
  QColor desiredColor = _colors.at(i);
  QVariant var = desiredColor;
  QString sColor = _Colors.at(i);
  const QIcon icon = getColourIcon(desiredColor);
//  QAction* trackColorAct = new QAction(icon, sColor,this);
//  trackColorAct->setCheckable(true);
//  trackColorAct->setData(var);
//  trackColorAct->setIconVisibleInMenu(true);
//  ui->menuSet_default_track_color->addAction(trackColorAct);
//  trackColorActGrp->addAction(trackColorAct);
//  if(defaultTrackColor == desiredColor)
//   trackColorAct->setChecked(true);

//  QAction* textColorAct = new QAction(icon, sColor, this);
//  textColorAct->setCheckable(true);
//  textColorAct->setData(var);
//  textColorAct->setIconVisibleInMenu(true);
//  ui->menuSet_default_text_color->addAction(textColorAct);
//  textColorActGrp->addAction(textColorAct);
//  if(defaultTextColor == desiredColor)
//   textColorAct->setChecked(true);
  QAction* backgroundColorAct = new QAction(icon, sColor, this);
  backgroundColorAct->setCheckable(true);
  backgroundColorAct->setData(var);
  backgroundColorAct->setIconVisibleInMenu(true);
  ui->menuSet_Background_color->addAction(backgroundColorAct);
  backgroundColorActGrp->addAction(backgroundColorAct);
  if(defaultBackgroundColor == desiredColor)
   backgroundColorAct->setChecked(true);
#endif
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

 //
 //background color menu item
 //
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


 editPanel->setMouseTracking(true);
 editPanel->setScene(editScene);
 _turnoutSelection = NULL;


 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(OnScenePos(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)),this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
 // connect(editScene,SIGNAL(sceneDragMove(QGraphicsSceneDragDropEvent*)),this, SLOT(mouseDragged(QGraphicsSceneDragDropEvent*)));
 connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
// connect(trackColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(OnDefaultTrackColorSelected(QAction*)));
// connect(textColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(OnDefaultTextColorSelected(QAction*)));
// connect(backgroundColorActGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_colorBackgroundMenuItemSelected(QAction*)));

 sensorIconEditor = new MultiIconEditor(4);
 sensorIconEditor->setIcon(0, "Active:",":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
 sensorIconEditor->setIcon(1, "Inactive", ":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
 sensorIconEditor->setIcon(2, "Inconsistent:", ":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->setIcon(3, "Unknown:",":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->complete();
 sensorFrame = new JFrame(tr("Edit Sensor Icons"));
 QWidget* sensorFrameContentPane = new QWidget;
 sensorFrame->setCentralWidget(sensorFrameContentPane);
 QVBoxLayout* sensorFrameLayout = new QVBoxLayout(sensorFrameContentPane);
 sensorFrameLayout->addWidget(new QLabel("  "+tr("Select new file, then click on icon to change.")+"  ")/*,BorderLayout::North*/,0,Qt::AlignTop);
 // sensorFrame.getContentPane().add(sensorIconEditor);
 sensorFrameLayout->addWidget(sensorIconEditor/*,BorderLayout::Center*/,0,Qt::AlignCenter);
 sensorFrame->adjustSize();
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
 markerImage = new QVector<LocoIcon*>(); // marker images
 signalFrame = new JmriJFrame("<LayoutEditor>");
 QWidget* centralWidget = new QWidget();
 centralWidget->setLayout(new QVBoxLayout());
 signalFrame->setCentralWidget(centralWidget);
 centralWidget->layout()->addWidget(new QLabel("</html>Select new image from file,<br>then click an upper preview icon to change it.</html>"));
 centralWidget->layout()->addWidget(signalIconEditor);
 signalFrame->resize(600, 400);
 signalFrame->setAllowInFrameServlet(false);
 signalFrame->adjustSize();
 signalFrame->setVisible(false);
 autoAssignBlocks = true;
 tooltipsInEditMode = false;
 tooltipsWithoutEditMode = false;
 _loadFailed = false;
 _debug = true;
 _ignore = false;
 _urlMap = new QMap<QString, QString>();
 _newIcon = NULL;
 _delete = NULL;
 finder = new LayoutEditorFindItems(this);
 ui->menuOptions->addMenu( setupTurnoutSubMenu());

// register the resulting panel for later configuration
 JmriConfigurationManager* cm = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");

 if (cm != NULL) {
     cm->registerUser(this);
 }

 // confirm that panel hasn't already been loaded
 if (PanelMenu::instance()->isPanelNameUsed(name))
 {
  log.warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }
}

/*public*/ void LayoutEditor::setSize(int w, int h)
{
 log.debug("Frame size now w=" + QString::number(w) + ", h=" + QString::number(h));
 Editor::resize(w, h);
}

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
//         turnoutCirclesWithoutEditMode = turnoutCirclesOnItem.isSelected();
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
  autoAssignBlocksItem = new QAction(tr("Automatically Assign Blocks to Track"));
  autoAssignBlocksItem->setCheckable(true);
  turnoutOptionsMenu->addAction(autoAssignBlocksItem);
//  autoAssignBlocksItem.addActionListener((ActionEvent event) -> {
//      autoAssignBlocks = autoAssignBlocksItem.isSelected();
//  });
  connect(autoAssignBlocksItem, SIGNAL(triggered(bool)), this, SLOT(on_autoAssignBlocksItem_triggered(bool)));
  autoAssignBlocksItem->setChecked(autoAssignBlocks);

  //
  //add hideTrackSegmentConstructionLines menu item
  //
  hideTrackSegmentConstructionLines = new QAction(tr("Hide Track Construction Lines"));
  hideTrackSegmentConstructionLines->setCheckable(true);
  ui->menuOptions->addAction(hideTrackSegmentConstructionLines);
 // hideTrackSegmentConstructionLines.addActionListener((ActionEvent event) -> {
//      int show = TrackSegment.SHOWCON;

//      if (hideTrackSegmentConstructionLines.isSelected()) {
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
  useDirectTurnoutControlItem = new QAction(tr("Use Direct Turnout Control"));   //IN18N
  useDirectTurnoutControlItem->setCheckable(true);
  turnoutOptionsMenu->addAction(useDirectTurnoutControlItem);
//  useDirectTurnoutControlItem.addActionListener((ActionEvent event) -> {
//      useDirectTurnoutControl = false;

//      if (useDirectTurnoutControlItem.isSelected()) {
//          useDirectTurnoutControl = true;
//      }
//  });
  connect(useDirectTurnoutControlItem, SIGNAL(triggered(bool)), this, SLOT(on_useDirectTurnoutControlItem_triggered(bool)));
  useDirectTurnoutControlItem->setChecked(useDirectTurnoutControl);

 return turnoutOptionsMenu;
}

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

  for (TrackSegment* t : *trackList) {
      t->hideConstructionLines(show);
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
   selectedObject = NULL;
   selectedPointType = NONE;
   if (checkSelect(dLoc, false))
   {
    selectedObject = foundObject;
    selectedPointType = foundPointType;
    //selectedNeedsConnect = foundNeedsConnect;
    startDel = QPointF(foundLocation.x()-dLoc.x(), foundLocation.y()-dLoc.y());
    foundObject = NULL;
   }
   else
   {
    selectedObject = checkMarkers(dLoc);
    if (selectedObject!=NULL)
    {
     selectedPointType = MARKER;
     startDel= QPointF((((LocoIcon*)selectedObject)->x()-dLoc.y()),(((LocoIcon*)selectedObject)->y()-dLoc.y()));
     selectedNeedsConnect = false;
    }
    else
    {
     selectedObject = checkClocks(dLoc);
     if (selectedObject!=NULL)
     {
      selectedPointType = LAYOUT_POS_JCOMP;
      //startDel.setLocation((((PositionableJComponent)selectedObject).getX()-dLoc.getX()),(((PositionableJComponent)selectedObject).getY()-dLoc.getY()));
      startDel= QPointF((((AnalogClock2Display*)selectedObject)->x()-dLoc.y()),(((AnalogClock2Display*)selectedObject)->x()-dLoc.y()));
      selectedNeedsConnect = false;
     }
#if 1 // TODO:
     else
     {
      selectedObject = checkMultiSensors(dLoc);
      if (selectedObject!=NULL)
      {
       selectedPointType = MULTI_SENSOR;
       startDel= QPointF((((MultiSensorIcon*)selectedObject)->x()-dLoc.y()), (((MultiSensorIcon*)selectedObject)->x()-dLoc.y()));
       //selectedNeedsConnect = false;
      }
     }
#endif
    }
    if (selectedObject==NULL)
    {
     selectedObject = checkSensorIcons(dLoc);
     if (selectedObject==NULL)
     {
      selectedObject = checkSignalHeadIcons(dLoc);
      if (selectedObject==NULL)
      {
       selectedObject = checkLabelImages(dLoc);
       if(selectedObject==NULL)
       {
        selectedObject = checkSignalMastIcons(dLoc);
       }
      }
     }
     if (selectedObject!=NULL)
     {
      selectedPointType = LAYOUT_POS_LABEL;
      //startDel.setLocation((((PositionableLabel*)selectedObject)->getX()-dLoc.getX()),                     (((PositionableLabel*)selectedObject)->getY()-dLoc.getY()));
      startDel = QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),(((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
      //if (selectedObject instanceof MemoryIcon)
      if(qobject_cast<MemoryIcon*>(selectedObject)!= NULL)
      {
       MemoryIcon* pm = (MemoryIcon*) selectedObject;
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
      if (selectedObject!=NULL)
      {
       selectedPointType = LAYOUT_POS_LABEL;
       //startDel.setLocation((((PositionableLabel)selectedObject).getX()-dLoc.x()),                            (((PositionableLabel)selectedObject).getY()-dLoc.y()));
       startDel = QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),                            (((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
      selectedNeedsConnect = false;
      }
     }
    }
   }
  }
  else if (bShift && ui->chkTrackSegment->isChecked() /*&& (!event.isPopupTrigger()) */)
  {
   // starting a Track Segment, check for free connection point
   selectedObject = NULL;
   if (checkSelect(dLoc, true))
   {
    // match to a free connection point
    beginObject = foundObject;
    beginPointType = foundPointType;
    beginLocation = foundLocation;
   }
   else {
    foundObject = NULL;
    beginObject = NULL;
   }
  }
  else if ( (!bShift) && (!bControl) /*&& (!event.isPopupTrigger())*/ && !bPopupTrigger)
  {
   // check if controlling a turnout in edit mode
    selectedObject = NULL;
    if (allControlling())
    {
     // check if mouse is on a turnout
     selectedObject = NULL;
     for (int i = 0; i<turnoutList->size();i++)
     {
      LayoutTurnout* t = turnoutList->at(i);
      // check the center point
      QPointF pt = t->getCoordsCenter();
      QRectF r =  QRectF(
                pt.x()-SIZE2,pt.y()-SIZE2,2.0*SIZE2,2.0*SIZE2);
      if (r.contains(dLoc))
      {
       // mouse was pressed on this turnout
       selectedObject = t;
       selectedPointType = TURNOUT_CENTER;
       break;
      }
     }
     for(int i=0; i < slipList->count(); i++)
     {
      LayoutSlip* sl = slipList->at(i);
      // check the center point
      QPointF pt = sl->getCoordsCenter();
      QRectF r =  QRectF(pt.x()-(SIZE2*2.0),pt.y()-(SIZE2*2.0),4.0*SIZE2,4.0*SIZE2);
      if (r.contains(dLoc))
      {
       // mouse was pressed on this turnout
       selectedObject = sl;
       selectedPointType = SLIP_CENTER;
       break;
      }
     }
#if 1 //TODO:

    for (int i = 0; i<turntableList->size();i++)
    {
     LayoutTurntable* x = turntableList->at(i);
     for (int k = 0; k<x->getNumberRays(); k++)
     {
      if (x->getRayConnectOrdered(k)!=NULL)
      {
       // check the A connection point
       QPointF pt = x->getRayCoordsOrdered(k);
       QRectF r = QRectF(pt.x() - SIZE, pt.y() - SIZE,SIZE2,SIZE2);
       if (r.contains(dLoc))
       {
           // mouse was pressed on this connection point
           selectedObject = x;
           selectedPointType = TURNTABLE_RAY_OFFSET+x->getRayIndex(k);
           break;
       }
      }
     }
    }
#endif
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
   selectedObject = NULL;
   for (int i = 0; i<turnoutList->size();i++)
   {
    LayoutTurnout* t = turnoutList->at(i);
    // check a rectangle as large as turnout circle, but at least size 4
    QPointF pt = t->getCoordsCenter();
    double size = SIZE * turnoutCircleSize;
    if (size < SIZE2*2.0) size = SIZE2*2.0;
    QRectF r = QRectF(
            pt.x()-size, pt.y()-size, size+size, size+size);
    if (r.contains(dLoc))
    {
     // mouse was pressed on this turnout
     selectedObject = t;
     selectedPointType = TURNOUT_CENTER;
     break;
    }
   }
   for(int i=0; i< slipList->count(); i++)
   {
    LayoutSlip* sl = slipList->at(i);
    // check the center point
    QPointF pt = sl->getCoordsCenter();
    QRectF r = QRectF(pt.x()-(SIZE2*2.0),pt.y()-(SIZE2*2.0),4.0*SIZE2,4.0*SIZE2);
    if (r.contains(dLoc))
    {
     // mouse was pressed on this turnout
      selectedObject = sl;
      selectedPointType = SLIP_CENTER;
      break;
     }
    }
#if 1 //TODO

    for (int i = 0; i<turntableList->size();i++)
    {
     LayoutTurntable* x = turntableList->at(i);
     for (int k = 0; k<x->getNumberRays(); k++)
     {
      if (x->getRayConnectOrdered(k)!=NULL)
      {
       // check the A connection point
       QPointF pt = x->getRayCoordsOrdered(k);
       QRectF r = QRectF(
               pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
       if (r.contains(dLoc)) {
           // mouse was pressed on this connection point
           selectedObject = x;
           selectedPointType = TURNTABLE_RAY_OFFSET+x->getRayIndex(k);
           break;
       }
      }
     }
    }
#endif
 }
 else if ( (/*event.isMetaDown() ||*/ /*event.isAltDown()*/event->modifiers()&Qt::AltModifier) &&
              (!(/*event.isShiftDown()*/event->modifiers()&Qt::ShiftModifier)) && (!(/*event.isControlDown()*/event->modifiers()&Qt::ControlModifier)) )
 {
  // not in edit mode - check if moving a marker if there are any
  selectedObject = checkMarkers(dLoc);
  if (selectedObject!=NULL)
  {
   selectedPointType = MARKER;
   startDel= QPointF((((LocoIcon*)selectedObject)->getX()-dLoc.x()),
                                            (((LocoIcon*)selectedObject)->getY()-dLoc.y()));
   //selectedNeedsConnect = false;
  }
 }
 else if ( /*event.isPopupTrigger() && */(!/*event.isShiftDown()*/event->modifiers()&Qt::ShiftModifier) )
 {
  // not in edit mode - check if a marker popup menu is being requested
  LocoIcon* lo = checkMarkers(dLoc);
  if (lo!=NULL) delayedPopupTrigger = true;
 }
 if (/*!event.isPopupTrigger() &&*/ !isDragging)
 {
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  {
   if(qobject_cast<SignalHeadIcon*>(selections.at(0))!=  NULL)
    ((SignalHeadIcon*)selections.at(0))->doMousePressed(event);
   else
   if(qobject_cast<SensorIcon*>(selections.at(0))!=  NULL)
    ((SensorIcon*)selections.at(0))->doMousePressed(event);
   else
    ((PositionableLabel*)selections.at(0))->doMousePressed(event);
  }
 }
 //thisPanel.setFocusable(true);
 //thisPanel.requestFocusInWindow();
 return;
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
//   if(qobject_cast<SensorIcon*>(selections.at(0))!= NULL)
//    ((SensorIcon*)selections.at(0))->doMouseClicked(event);
//   else
   ((PositionableLabel*)selections.at(0))->doMouseClicked(event);
  }
 }
 else if ( (event->buttons()&Qt::RightButton/*==Qt::RightButton*/ ) /*&& whenReleased != event.getWhen()*/)
 {
  calcLocation(event->scenePos(), 0, 0);
  if (isEditable())
  {
   selectedObject = NULL;
   selectedPointType = NONE;
   checkPopUp(event);
  }
  else
  {
   LocoIcon* lo = checkMarkers(dLoc);
   if (lo!=NULL) showPopUp((Positionable*)lo, event);
  }
 }
 if ((event->modifiers()&Qt::ControlModifier) /*&&*/ /*!event.isPopupTrigger()*/)
 {
  if (checkSelect(dLoc, false))
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
   if (s!=NULL)
   {
    amendSelectionGroup((Positionable*)s);
   }

   else
   {
    PositionableLabel* sh = checkSignalHeadIcons(dLoc);
    if (sh!=NULL)
    {
     amendSelectionGroup((Positionable*)sh);
    }
    else
    {
     PositionableLabel* ms = checkMultiSensors(dLoc);
     if (ms!=NULL)
     {
      amendSelectionGroup((Positionable*)ms);
     }
     else
     {
      PositionableLabel* lb = checkLabelImages(dLoc);
      if (lb!=NULL)
      {
       amendSelectionGroup((Positionable*)lb);
      }
//      else
//      {
//       PositionableLabel* b = checkBackgrounds(dLoc);
//       if (b!=NULL)
//       {
//        amendSelectionGroup(b);
//       }
       else
       {
        PositionableLabel* sm = checkSignalMastIcons(dLoc);
        if (sm!=NULL)
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

 if (t == NULL) {
     t = p->getConnect2();
 }

 //Nothing connected to this bit of track so ignore
 if (t == NULL) {
     return;
 }
 beginObject = p;
 beginPointType = LayoutTrack::POS_POINT;
 QPointF loc = p->getCoords();

 if (checkSelect(loc, true, p))
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

     if ((p->getConnect1() == NULL) && (p->getConnect2() == NULL))
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
     if (lt->getConnection(foundPointType) == NULL)
     {
      lt->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(lt, foundPointType);
      } else {
          t->setNewConnect2(lt, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == NULL) && (p->getConnect2() == NULL))
      {
          removePositionablePoint(p);
      }
     }
    } catch (JmriException e) {
       log.debug("Unable to set location");
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
     if (lx->getConnection(foundPointType) == NULL)
     {
      lx->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(lx, foundPointType);
      } else {
          t->setNewConnect2(lx, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == NULL) && (p->getConnect2() == NULL)) {
          removePositionablePoint(p);
      }
     }
    }
    catch (JmriException e) {
       log.debug("Unable to set location");
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
     if (ls->getConnection(foundPointType) == NULL)
     {
      ls->setConnection(foundPointType, t, LayoutTrack::TRACK);

      if (t->getConnect1() == p) {
          t->setNewConnect1(ls, foundPointType);
      } else {
          t->setNewConnect2(ls, foundPointType);
      }
      p->removeTrackConnection(t);

      if ((p->getConnect1() == NULL) && (p->getConnect2() == NULL)) {
          removePositionablePoint(p);
      }
     }
    } catch (JmriException e) {
       log.debug("Unable to set location");
   }
   break;
  }

  default:

   if (foundPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET)
   {
    LayoutTurntable* tt = (LayoutTurntable*) foundObject;
    int ray = foundPointType - LayoutTrack::TURNTABLE_RAY_OFFSET;

    if (tt->getRayConnectIndexed(ray) == NULL)
    {
     tt->setRayConnect(t, ray);

     if (t->getConnect1() == p) {
         t->setNewConnect1(tt, foundPointType);
     } else {
         t->setNewConnect2(tt, foundPointType);
     }
     p->removeTrackConnection(t);

     if ((p->getConnect1() == NULL) && (p->getConnect2() == NULL)) {
         removePositionablePoint(p);
     }
    }
   }
   else
   {
    log.debug("No valid point, so will quit");
    return;
   }
  }   //switch
  update();

  if (t->getLayoutBlock() != NULL)
  {
   auxTools->setBlockConnectivityChanged();
  }
 }
 beginObject = NULL;
 foundObject = NULL;
}   //checkPointOfPositionable

/*private*/ void LayoutEditor::checkPointsOfTurnout(LayoutTurnout* lt)
{
 beginObject = lt;

 if (lt->getConnectA() == NULL) {
     beginPointType = LayoutTrack::TURNOUT_A;
     dLoc = lt->getCoordsA();
     checkPointsOfTurnoutSub(lt->getCoordsA());
 }

 if (lt->getConnectB() == NULL) {
     beginPointType = LayoutTrack::TURNOUT_B;
     dLoc = lt->getCoordsB();
     checkPointsOfTurnoutSub(lt->getCoordsB());
 }

 if (lt->getConnectC() == NULL) {
     beginPointType = LayoutTrack::TURNOUT_C;
     dLoc = lt->getCoordsC();
     checkPointsOfTurnoutSub(lt->getCoordsC());
 }

 if ((lt->getConnectD() == NULL) && ((lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER) ||
                                    (lt->getTurnoutType() == LayoutTurnout::LH_XOVER) ||
                                    (lt->getTurnoutType() == LayoutTurnout::RH_XOVER))) {
     beginPointType = LayoutTrack::TURNOUT_D;
     dLoc = lt->getCoordsD();
     checkPointsOfTurnoutSub(lt->getCoordsD());
 }
 beginObject = NULL;
 foundObject = NULL;
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

    if (((p2->getConnect1() == NULL) && (p2->getConnect2() != NULL)) ||
        ((p2->getConnect1() != NULL) && (p2->getConnect2() == NULL)))
    {
     TrackSegment* t = p2->getConnect1();

     if (t == NULL) {
         t = p2->getConnect2();
     }

     if (t == NULL) {
         return;
     }
     LayoutTurnout* lt = (LayoutTurnout*) beginObject;
     try
     {
      if (lt->getConnection(beginPointType) == NULL)
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

      if (t->getLayoutBlock() != NULL) {
          auxTools->setBlockConnectivityChanged();
      }
     } catch (JmriException e) {
         log.debug("Unable to set location");
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
       log.warn(tr("Unexpected foundPointType %1  in checkPointsOfTurnoutSub").arg(foundPointType));
       break;
   }
  }   //switch
 }
}   //checkPointsOfTurnoutSub

/*private*/ void LayoutEditor::rotateTurnout(LayoutTurnout* t) {
    LayoutTurnout* be = (LayoutTurnout*) beginObject;

    if (((beginPointType == LayoutTrack::TURNOUT_A) && ((be->getConnectB() != NULL) || (be->getConnectC() != NULL))) ||
        ((beginPointType == LayoutTrack::TURNOUT_B) && ((be->getConnectA() != NULL) || (be->getConnectC() != NULL))) ||
        ((beginPointType == LayoutTrack::TURNOUT_C) && ((be->getConnectB() != NULL) || (be->getConnectA() != NULL)))) {
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
 //super.setToolTip(NULL);
 // initialize mouse position
 calcLocation(event->scenePos(), 0, 0);
 if (isEditable())
 {
  ui->xLabel->setText(QString("%1").arg(xLoc));
  ui->yLabel->setText(QString("%1").arg(yLoc));
  // !ALT and SHIFT_DOWN
  Qt::KeyboardModifiers k = event->modifiers();
  Q_UNUSED(k)
  bool bMeta = event->modifiers()&Qt::MetaModifier;
  bool bAlt = event->modifiers()&Qt::AltModifier;
  bool bShift =  event->modifiers()&Qt::ShiftModifier;
  if(delayedPopupTrigger && bShift)
   delayedPopupTrigger = false;
  if (/*(!event.isPopupTrigger()) && (!event.isMetaDown()) &&*/ !delayedPopupTrigger && !bMeta && (!bAlt) && bShift)
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
   if (ui->chkRH->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_TURNOUT);
   }
   else if (ui->chkLH->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_TURNOUT);
   }
   else if (ui->chkWYE->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::WYE_TURNOUT);
   }
   else if (ui->chkDoubleXover->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::DOUBLE_XOVER);
   }
   else if (ui->chkRHXover->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_XOVER);
   }
   else if (ui->chkLHXover->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_XOVER);
   }
   else if (ui->chkLevelCrossing->isChecked())
   {
    addLevelXing();
   }
   else if (ui->chkSingleSlip->isChecked())
   {
    addLayoutSlip(LayoutSlip::SINGLE_SLIP);
   }
   else if (ui->chkDoubleSlip->isChecked())
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
   else if (ui->chkTrackSegment->isChecked())
   {
    if ( (beginObject!=NULL) && (foundObject!=NULL) &&
                (beginObject!=foundObject) )
    {
     if(trackInProgress != NULL && trackInProgress->scene()!=0)
     {
      editScene->removeItem(trackInProgress);
      trackInProgress = NULL;
     }
     addTrackSegment();
     setCursor(Qt::ArrowCursor);
    }
    beginObject = NULL;
    foundObject = NULL;
    }
#if 1

   else if (ui->chkMultisensor->isChecked())
   {
    startMultiSensor();
   }
#endif
    else if (ui->chkSensorIcon->isChecked())
    {
        addSensor();
    }
#if 1
    else if (ui->chkSignalHeadIcon->isChecked()) {
        addSignalHead();
    }
#endif
    else if (ui->chkTextLabel->isChecked()) {
        addLabel();
    }

    else if (ui->chkMemoryLabel->isChecked()) {
        addMemory();
    }
   else if (ui->chkIconLabel->isChecked()) {
        addIcon();
    }
#if 1
    else if (ui->chkSignalMastIcon->isChecked()) {
        addSignalMast();
    }
#endif
   else
   {
    log.warn("No item selected in panel edit mode");
   }
   selectedObject = NULL;
   //repaint();
   paintTargetPanel(editScene);
  }
  else if ( (/*event->isPopupTrigger() ||*/ delayedPopupTrigger)  && !isDragging)
  {
   selectedObject = NULL;
   selectedPointType = NONE;
   //whenReleased = event.getWhen();
   checkPopUp(event);
   delayedPopupTrigger = false;
  }
   // check if controlling turnouts
  else if ( ( selectedObject!=NULL) && (selectedPointType==TURNOUT_CENTER)
             && allControlling() /*&& (!(event->modifiers()&Qt::ControlModifier))*/ /*&& (!(event->modifiers()&Qt::AltModifier)) *//*&& (!event.isPopupTrigger())*/
             && (!(event->modifiers()&Qt::ShiftModifier))
             && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
  else if ( ( selectedObject!=NULL) && ((selectedPointType == LayoutTrack::SLIP_CENTER) ||
                                        (selectedPointType == LayoutTrack::SLIP_LEFT) ||
                                        (selectedPointType == LayoutTrack::SLIP_RIGHT))/* &&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleState(selectedPointType);
  }
  else if ( ( selectedObject!=NULL) && (selectedPointType>=TURNTABLE_RAY_OFFSET) /*&&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurntable* t =  (LayoutTurntable*)selectedObject;
   t->setPosition(selectedPointType-TURNTABLE_RAY_OFFSET);
  }
  else if ((selectedObject != NULL) && (selectedPointType == LayoutTrack::TURNOUT_CENTER) /*&&
                         allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
                         (!event.isShiftDown()) && (!event.isControlDown()) && isDragging)*/
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
        //controlling layout, in edit mode
        checkPointsOfTurnout((LayoutTurnout*) selectedObject);
  }
  else if ((selectedObject != NULL) && (selectedPointType == LayoutTrack::POS_POINT) /*&&
               allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
               (!event.isShiftDown()) && (!event.isControlDown()) && isDragging) */
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
    PositionablePoint* p = (PositionablePoint*) selectedObject;

    if ((p->getConnect1() == NULL) || (p->getConnect2() == NULL)) {
        checkPointOfPositionable(p);
    }
   }

   if ( (ui->chkTrackSegment->isChecked()) && (beginObject!=NULL) && (foundObject!=NULL) )
   {
    // user let up shift key before releasing the mouse when creating a track segment
    setCursor(Qt::ArrowCursor);
    beginObject = NULL;
    foundObject = NULL;
    //repaint();
    paintTargetPanel(editScene);
   }

   createSelectionGroups();
  }
  // check if controlling turnouts out of edit mode
  else if ( ( selectedObject!=NULL) && (selectedPointType==TURNOUT_CENTER) /*&&
            allControlling() && (!event.isMetaDown())*/ && (!(event->modifiers()&Qt::AltModifier)) /*&& (!event.isPopupTrigger()) */&&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   // controlling layout, not in edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
    // check if controlling turnouts out of edit mode
    else if ( ( selectedObject!=NULL) && ((selectedPointType == LayoutTrack::SLIP_CENTER) ||
                                          (selectedPointType == LayoutTrack::SLIP_LEFT) ||
                                          (selectedPointType == LayoutTrack::SLIP_RIGHT)) /*&&
            allControlling() && (!event.isMetaDown())*/ && (!(event->modifiers()&Qt::AltModifier))/* && (!event.isPopupTrigger())*/ &&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   // controlling layout, not in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleState(selectedPointType);
  }
#if 1
  else if ( ( selectedObject!=NULL) && (selectedPointType>=TURNTABLE_RAY_OFFSET)/* &&
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
    if (lo!=NULL) showPopUp((Positionable*)lo, event);
    else
    {
     if (checkSelect(dLoc, false))
     {
      // show popup menu
      switch (foundPointType)
      {
       case TURNOUT_CENTER:
        ((LayoutTurnout*)foundObject)->showPopUp(event, isEditable());
        break;
       case LEVEL_XING_CENTER:
        ((LevelXing*)foundObject)->showPopUp(event, isEditable());
        break;
       case SLIP_CENTER:
        ((LayoutSlip*)foundObject)->showPopUp(event, isEditable());
        break;
       default: break;
      }
     }

     AnalogClock2Display* c = checkClocks(dLoc);
     if (c!=NULL)
     {
       showPopUp((Positionable*)c, event);
     }
     else
     {
      SignalMastIcon* sm = checkSignalMastIcons(dLoc);
      if (sm!=NULL)
      {
       showPopUp((Positionable*)sm, event);
      }
      else
      {
       PositionableLabel* im = checkLabelImages(dLoc);
       if(im!=NULL)
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
   if (selectedObject!=NULL)
   {
    // An object was selected, deselect it
    prevSelectedObject = selectedObject;
    selectedObject = NULL;
   }
   isDragging = false;
   delayedPopupTrigger = false;
//    thisPanel.requestFocusInWindow();
   return;
  }
 }
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
 QPointF newPos = QPointF(dLoc.x() + startDel.y(), dLoc.y() + startDel.y());

 if ((selectedObject!=NULL) && (/*event.isMetaDown() ||*/ ((event->modifiers()&Qt::MetaModifier)!=0) || (selectedPointType==MARKER)))
  {
   // marker moves regardless of editMode or positionable
   PositionableLabel* pl = (PositionableLabel*)selectedObject;
   int xint = (int)newPos.x();
   int yint = (int)newPos.y();
   // don't allow negative placement, object could become unreachable
   if (xint<0) xint = 0;
   if (yint<0) yint = 0;
   pl->setLocation(xint, yint);
   isDragging = true;
   //repaint();
   pl->updateScene();
   paintTargetPanel(editScene);
   return;
  }

  if (isEditable())
  {
   if ((selectedObject!=NULL) && (/*event.isMetaDown() ||*/ !(event->modifiers()&Qt::AltModifier))|| allPositionable())
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
    if (_pointSelection!=NULL || _turnoutSelection!=NULL || _positionableSelection!=NULL /*|| _labelSelection != NULL*/)
    {
     int offsetx = xLoc - _lastX;
     int offsety = yLoc - _lastY;
     //We should do a move based upon a selection group.
     int xNew;
     int yNew;
     if (_positionableSelection!=NULL)
     {
      for (int i = 0; i<_positionableSelection->size(); i++)
      {
       Positionable* c = _positionableSelection->at(i);
       if ((/*c instanceof MemoryIcon*/qobject_cast<MemoryIcon*>(c)!=NULL) && (c->getPopupUtility()->getFixedWidth()==0))
       {
        MemoryIcon* pm = (MemoryIcon*) c;
        xNew = (pm->getOriginalX()+offsetx);
        yNew = (pm->getOriginalY()+offsety);
       }
       else
       {
       QPointF upperLeft = c->getLocation();
       xNew = (int)(upperLeft.x()+offsetx);
       yNew = (int)(upperLeft.y()+offsety);
      }
      if (xNew<0) xNew=0;
      if (yNew<0) yNew=0;
      c->setLocation(xNew,yNew);
      c->updateScene();
     }
    }
//    if(_labelSelection != NULL)
//    {
//     for(int i=0; i < _labelSelection->size(); i++)
//     {
//      PositionableLabel* l = _labelSelection->at(i);
//      QPointF upperLeft = l->getLocation();
//      xNew = (int)(upperLeft.x()+offsetx);
//      yNew = (int)(upperLeft.y()+offsety);

//      if (xNew<0) xNew=0;
//      if (yNew<0) yNew=0;
//      l->setLocation(xNew,yNew);
//     }
//    }
    if(_labelImage != NULL)
    {
      for(int i=0; i < _labelImage->size(); i++)
      {
       PositionableLabel* l = _labelImage->at(i);
       QPointF upperLeft = l->getLocation();
       xNew = (int)(upperLeft.x()+offsetx);
       yNew = (int)(upperLeft.y()+offsety);

       if (xNew<0) xNew=0;
       if (yNew<0) yNew=0;
       l->setLocation(xNew,yNew);
      }
    }
    if (_turnoutSelection!=NULL)
    {
     for (int i = 0; i<_turnoutSelection->size();i++)
     {
      LayoutTurnout* t = _turnoutSelection->at(i);
      QPointF center = t->getCoordsCenter();
      xNew = (int) center.x()+offsetx;
      yNew = (int) center.y()+offsety;
      if (xNew<0) xNew=0;
      if (yNew<0) yNew=0;
      t->setCoordsCenter( QPointF(xNew, yNew));
     }
    }
    if (_xingSelection!=NULL)
    {
     // loop over all defined level crossings
     for (int i = 0; i<_xingSelection->size();i++)
     {
      LevelXing* x = _xingSelection->at(i);
      QPointF center = x->getCoordsCenter();
      xNew = (int) center.x()+offsetx;
      yNew = (int) center.y()+offsety;
      if (xNew<0) xNew=0;
      if (yNew<0) yNew=0;
      x->setCoordsCenter(QPointF(xNew, yNew));
     }
    }
    if (_slipSelection!=NULL)
    {
     // loop over all defined level crossings
     for (int i = 0; i<_slipSelection->size(); i++)
     {
      LayoutSlip* x = _slipSelection->at(i);
      QPointF center = x->getCoordsCenter();
      xNew = (int) center.x()+offsetx;
      yNew = (int) center.y()+offsety;
      if (xNew<0) xNew=0;
      if (yNew<0) yNew=0;
      x->setCoordsCenter(QPointF(xNew, yNew));
     }
    }
#if 1 // TODO:
    // loop over all defined turntables
    if (_turntableSelection!=NULL)
    {
     for (int i = 0; i<_turntableSelection->size();i++)
     {
      LayoutTurntable* x = _turntableSelection->at(i);
                      QPointF center = x->getCoordsCenter();
                      xNew = (int) center.x()+offsetx;
                      yNew = (int) center.y()+offsety;
                      if (xNew<0) xNew=0;
                      if (yNew<0) yNew=0;
                      x->setCoordsCenter( QPointF(xNew, yNew));
                  }
     }
#endif
     // loop over all defined Anchor Points and End Bumpers
     if (_pointSelection!=NULL)
     {
      for (int i = 0; i<_pointSelection->size();i++)
      {
       PositionablePoint* p = _pointSelection->at(i);
       QPointF coord = p->getCoords();
       xNew = (int) coord.x()+offsetx;
       yNew = (int) coord.y()+offsety;
       if (xNew<0) xNew=0;
       if (yNew<0) yNew=0;
       p->setCoords(QPointF(xNew, yNew));
      }
     }
     _lastX = xLoc;
     _lastY = yLoc;
    }
    else
    {
     switch (selectedPointType)
     {
     case POS_POINT:
      ((PositionablePoint*)selectedObject)->setCoords(newPos);
      isDragging = true;
      break;
     case TURNOUT_CENTER:
      ((LayoutTurnout*)selectedObject)->setCoordsCenter(newPos);
      isDragging = true;
      break;
     case TURNOUT_A:
     {
      LayoutTurnout* o = (LayoutTurnout*)selectedObject;
      o->setCoordsA(newPos);
      break;
     }
     case TURNOUT_B:
     {
      LayoutTurnout* o = (LayoutTurnout*)selectedObject;
      o->setCoordsB(newPos);
      break;
     }
     case TURNOUT_C:
     {
      LayoutTurnout* o = (LayoutTurnout*)selectedObject;
      o->setCoordsC(newPos);
      break;
     }
     case TURNOUT_D:
     {
      LayoutTurnout* o = (LayoutTurnout*)selectedObject;
      o->setCoordsD(newPos);
      break;
     }
     case LEVEL_XING_CENTER:
     {
      ((LevelXing*)selectedObject)->setCoordsCenter(newPos);
      isDragging = true;
      break;
     }
     case LEVEL_XING_A:
     {
      LevelXing* x = (LevelXing*)selectedObject;
      x->setCoordsA(newPos);
      break;
     }
     case LEVEL_XING_B:
     {
      LevelXing* x = (LevelXing*)selectedObject;
      x->setCoordsB(newPos);
      break;
     }
     case LEVEL_XING_C:
     {
      LevelXing* x = (LevelXing*)selectedObject;
      x->setCoordsC(newPos);
      break;
     }
     case LEVEL_XING_D:
     {
     LevelXing* x = (LevelXing*)selectedObject;
      x->setCoordsD(newPos);
      break;
     }
     case SLIP_CENTER:
      ((LayoutSlip*)selectedObject)->setCoordsCenter(newPos);
      isDragging = true;
      break;
     case SLIP_A:
     {
      LayoutSlip* sl = (LayoutSlip*)selectedObject;
      sl->setCoordsA(newPos);
      break;
     }
     case SLIP_B:
     {
      LayoutSlip* sl = (LayoutSlip*)selectedObject;
      sl = (LayoutSlip*)selectedObject;
      sl->setCoordsB(newPos);
      break;
     }
     case SLIP_C:
     {
      LayoutSlip* sl = (LayoutSlip*)selectedObject;
      sl = (LayoutSlip*)selectedObject;
      sl->setCoordsC(newPos);
      break;
     }
     case SLIP_D:
     {
      LayoutSlip* sl = (LayoutSlip*)selectedObject;
      sl = (LayoutSlip*)selectedObject;
      sl->setCoordsD(newPos);
      break;
     }
     case TURNTABLE_CENTER:
      ((LayoutTurntable*)selectedObject)->setCoordsCenter(newPos);
      isDragging = true;
      break;
     case LAYOUT_POS_LABEL:
     {
      PositionableLabel* l = (PositionableLabel*)selectedObject;
      if (l->isPositionable())
      {
       int xint = (int)newPos.x();
       int yint = (int)newPos.y();
       // don't allow negative placement, object could become unreachable
       if (xint<0) xint = 0;
       if (yint<0) yint = 0;
       l->setLocation(xint, yint);
       isDragging = true;

//       if(l->item != NULL)
//       {
//        editScene->removeItem(l->item);
//        l->item = NULL;
//       }

//       if(l->isIcon())
//       {
//        l->item = new QGraphicsPixmapItem(QPixmap::fromImage(l->getIcon()->getOriginalImage()));
//        editScene->addItem(l->item);
//        l->item->setPos(l->getLocation());
//       }
//       else
//       {
//        l->item = new QGraphicsTextItem(l->getUnRotatedText());
//        editScene->addItem(l->item);
//        l->item->setPos(l->getLocation());
//       }
      }
      break;
     }
#if 1
     case LAYOUT_POS_JCOMP:
     {
      PositionableJComponent* c = (PositionableJComponent*)selectedObject;
      if (c->isPositionable()) {
          int xint = (int)newPos.x();
          int yint = (int)newPos.y();
          // don't allow negative placement, object could become unreachable
          if (xint<0) xint = 0;
          if (yint<0) yint = 0;
          c->setLocation(xint, yint);
          isDragging = true;
      }
      break;
     }
#endif
     case MULTI_SENSOR:
     {
      PositionableLabel* pl = (PositionableLabel*)selectedObject;
      if (pl->isPositionable())
      {
       int xint = (int)newPos.x();
       int yint = (int)newPos.y();
       // don't allow negative placement, object could become unreachable
       if (xint<0) xint = 0;
       if (yint<0) yint = 0;
       pl->setLocation(xint, yint);
       isDragging = true;
      }
      break;
     }
     case TRACK_CIRCLE_CENTRE:
     {
      TrackSegment* t = (TrackSegment*)selectedObject;
      t->reCalculateTrackSegmentAngle(newPos.x(), newPos.y());
      break;
     }
     case MARKER:
      if(qobject_cast<LocoIcon*>(selectedObject)!= NULL)
      {
       LocoIcon* l = (LocoIcon*)selectedObject;
       int xint = (int)newPos.x();
       int yint = (int)newPos.y();
       // don't allow negative placement, object could become unreachable
       if (xint<0) xint = 0;
       if (yint<0) yint = 0;
       l->setLocation(xint, yint);
       isDragging = true;
      }
      break;
     default:
   if (selectedPointType>=TURNTABLE_RAY_OFFSET)
   {
    LayoutTurntable* turn = (LayoutTurntable*)selectedObject;
    turn->setRayCoordsIndexed(newPos.x(),newPos.y(),
                          selectedPointType-TURNTABLE_RAY_OFFSET);
   }
     break;
    }
   }
   //repaint();
   paintTargetPanel(editScene);
   }
   else
   if ( (beginObject!=NULL) && event->modifiers()&Qt::ShiftModifier && ui->chkTrackSegment->isChecked() )
  {
   // dragging from first end of Track Segment
   currentLocation= QPointF(xLoc,yLoc);
   bool needResetCursor = (foundObject!=NULL);
   if (checkSelect(currentLocation, true))
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
 Positionable* selection = NULL;
 int numSel = selections.size();
 if (numSel > 0)
 {
  selection = selections.at(0);
 }
// if (selection!=NULL && selection.getDisplayLevel()>BKG && selection.showTooltip())
// {
//  showToolTip(selection, event);
// }
// else
// {
//  super.setToolTip(NULL);
// }
 if (numSel != _prevNumSel)
 {
  //repaint();
  //highLightSelection(editScene);
  if(highlightRect != NULL && highlightRect->scene() != 0)
  {
   editScene->removeItem(highlightRect);
  }
  highlightRect = new QGraphicsItemGroup();

  if(qobject_cast<PositionableLabel*>(selection) != NULL)
  {
   PositionableLabel* l = (PositionableLabel*)selection;
   QGraphicsRectItem* item = new QGraphicsRectItem(l->_itemGroup->boundingRect());
   item->setPen(QPen(QBrush(_highlightColor),1,Qt::SolidLine));

   highlightRect->addToGroup(item);
   editScene->addItem(highlightRect);
  }
  else
  if(qobject_cast<LayoutTurnout*>(selection) != NULL)
  {
   LayoutTurnout* t = (LayoutTurnout*)selection;
   QGraphicsRectItem* item = new QGraphicsRectItem(t->item->boundingRect());
   highlightRect->addToGroup(item);
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
 numAnchors ++;
 // get unique name
 QString name = "";
 bool duplicate = true;
 while (duplicate)
 {
  name = "A"+QString::number(numAnchors);
  if (findPositionablePointByName(name)==NULL) duplicate = false;
  if (duplicate) numAnchors ++;
 }
 // create object
 PositionablePoint* o = new PositionablePoint(name,
                     PositionablePoint::ANCHOR, currentPoint, this);
 //if (o!=NULL) {
 pointList->append(o);
 setDirty(true);
 //}
}

/*private*/ PositionablePoint* LayoutEditor::addAnchor(QPointF p) {
        numAnchors++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "A" + numAnchors;
            if (finder->findPositionablePointByName(name) == NULL) {
                duplicate = false;
            }
            if (duplicate) {
                numAnchors++;
            }
        }
        // create object
        PositionablePoint* o = new PositionablePoint(name,
                PositionablePoint::ANCHOR, p, this);
        //if (o!=NULL) {
        pointList->append(o);
        setDirty(true);
        //}
        return o;
    }
/**
 * Add an End Bumper point.
 */
/*public*/ void LayoutEditor::addEndBumper() {
    numEndBumpers ++;
    // get unique name
    QString name = "";
    bool duplicate = true;
    while (duplicate) {
        name = "EB"+numEndBumpers;
        if (findPositionablePointByName(name)==NULL) duplicate = false;
        if (duplicate) numEndBumpers ++;
    }
    // create object
    PositionablePoint* o = new PositionablePoint(name,
                        PositionablePoint::END_BUMPER, currentPoint, this);
    //if (o!=NULL) {
    pointList->append(o);
    setDirty(true);
    //}
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
  if (findTrackSegmentByName(name)==NULL) duplicate = false;
  if (duplicate) numTrackSegments ++;
 }
 // create object
 newTrack = new TrackSegment(name,beginObject,beginPointType,
                 foundObject,foundPointType,ui->chkDashed->isChecked(), ui->chkMainline->isChecked(),this);
 if (newTrack!=NULL)
 {
  trackList->append(newTrack);
  setDirty(true);
  // link to connected objects
  setLink(newTrack,TRACK,beginObject,beginPointType);
  setLink(newTrack,TRACK,foundObject,foundPointType);
  // check on layout block
  LayoutBlock* b = provideLayoutBlock(ui->edBlockName->text().trimmed());
  if (b!=NULL)
  {
   newTrack->setLayoutBlock(b);
   auxTools->setBlockConnectivityChanged();
   // check on occupancy sensor
   QString sensorName = (ui->edOccupancySensor->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b/*,this*/))
    {
     b->setOccupancySensorName("");
    }
    else
    {
     ui->edOccupancySensor->setText( b->getOccupancySensorName() );
    }
   }
   newTrack->updateBlockInfo();
  }
 }
 else
 {
  log.error("Failure to create a new Track Segment");
 }
}

/**
 * Add a Level Crossing
 */
/*public*/ void LayoutEditor::addLevelXing()
{
 numLevelXings ++;
 // get unique name
 QString name = "";
 bool duplicate = true;
 while (duplicate)
 {
  name = "X"+QString("%1").arg(numLevelXings);
  if (findLevelXingByName(name)==NULL)
   duplicate = false;
  if (duplicate)
   numLevelXings ++;
 }
 // create object
 LevelXing* o = new LevelXing(name,currentPoint,this);
 if (o!=NULL)
 {
  xingList->append(o);
  setDirty(true);
  // check on layout block
  LayoutBlock* b = provideLayoutBlock(ui->edBlockName->text().trimmed());
  if (b!=NULL)
  {
   o->setLayoutBlockAC(b);
   o->setLayoutBlockBD(b);
   // check on occupancy sensor
   QString sensorName = (ui->edOccupancySensor->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b/*,this*/))
    {
     b->setOccupancySensorName("");
    }
    else {
     ui->edOccupancySensor->setText( b->getOccupancySensorName() );
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
 QString s = ui->edRotation->text().trimmed();
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
 QString name = "";
 bool duplicate = true;
 while (duplicate)
 {
  name = "SL"+QString("%1").arg(numLayoutSlips);
  if (findLayoutSlipByName(name)==NULL) duplicate = false;
  if (duplicate) numLayoutSlips ++;
 }
 // create object
 LayoutSlip* o = new LayoutSlip(name,currentPoint, rot, this, type);
 slipList->append(o);
 setDirty(true);

 // check on layout block
 LayoutBlock* b = provideLayoutBlock(ui->edBlockName->text().trimmed());
 if (b!=NULL)
 {
  o->setLayoutBlock(b);
  // check on occupancy sensor
  QString sensorName = (ui->edOccupancySensor->text().trimmed());
  if (sensorName.length()>0)
  {
   if (!validateSensor(sensorName,b/*,this*/))
   {
    b->setOccupancySensorName("");
   }
   else
   {
    ui->edOccupancySensor->setText( b->getOccupancySensorName() );
   }
  }
 }
 QString turnoutName = ui->edTurnoutName->text().trimmed();
 if ( validatePhysicalTurnout(turnoutName/*, this*/) )
 {
  // turnout is valid and unique.
  o->setTurnout(turnoutName);
  if (o->getTurnout()->getSystemName()==(turnoutName.toUpper()))
  {
   ui->edTurnoutName->setText(turnoutName.toUpper());
  }
 }
 else
 {
  o->setTurnout("");
  ui->edTurnoutName->setText("");
 }
 turnoutName = ui->edExtraName->text().trimmed();
 if ( validatePhysicalTurnout(turnoutName/*, this*/) )
 {
  // turnout is valid and unique.
  o->setTurnoutB(turnoutName);
  if (o->getTurnoutB()->getSystemName()==(turnoutName.toUpper()))
  {
   ui->edExtraName->setText(turnoutName.toUpper());
  }
 }
 else
 {
  o->setTurnoutB("");
  ui->edExtraName->setText("");
 }
}

/**
 * Add a Layout Turnout
 */
/*public*/ void LayoutEditor::addLayoutTurnout(int type)
{
 // get the rotation entry
 double rot = 0.0;
 QString s = ui->edRotation->text().trimmed();
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
 QString name = "";
 bool duplicate = true;
 while (duplicate)
 {
  name = "TO"+QString("%1").arg(numLayoutTurnouts);
  if (findLayoutTurnoutByName(name)==NULL) duplicate = false;
  if (duplicate) numLayoutTurnouts ++;
 }
 addLayoutTurnout(name, type, rot, currentPoint);
}

LayoutTurnout* LayoutEditor::addLayoutTurnout(QString name, int type, double rot, QPointF currentPoint)
{
 // create object
 LayoutTurnout* o = new LayoutTurnout(name,type,                                   currentPoint,rot,xScale,yScale,this);
 //if (o!=NULL) {
 turnoutList->append(o);
 setDirty(true);
 // check on layout block
 LayoutBlock* b = provideLayoutBlock(ui->edBlockName->text().trimmed());
 if (b!=NULL)
 {
  o->setLayoutBlock(b);
  // check on occupancy sensor
  QString sensorName = (ui->edOccupancySensor->text().trimmed());
  if (sensorName.length()>0)
  {
   if (!validateSensor(sensorName,b/*,this*/))
   {
    b->setOccupancySensorName("");
   }
   else
   {
    ui->edOccupancySensor->setText( b->getOccupancySensorName() );
   }
  }
 }
 // set default continuing route Turnout State
 o->setContinuingSense(Turnout::CLOSED);
 // check on a physical turnout
 QString turnoutName = ui->edTurnoutName->text().trimmed();
 if ( validatePhysicalTurnout(turnoutName/*, this*/) )
 {
  // turnout is valid and unique.
  o->setTurnout(turnoutName);
  if (o->getTurnout()->getSystemName()==(turnoutName.toUpper()))
  {
   ui->edTurnoutName->setText(turnoutName.toUpper());
  }
 }
 else
 {
  o->setTurnout("");
  ui->edTurnoutName->setText("");
 }
 return o;
}

/**
 * Validates that a physical turnout exists and is unique among Layout Turnouts
 *    Returns true if valid turnout was entered, false otherwise
 */
/*public*/ bool LayoutEditor::validatePhysicalTurnout(QString turnoutName, QWidget* openPane)
{
 // check if turnout name was entered
 if (turnoutName.length() < 1)
 {
  // no turnout entered
  return false;
 }
 // ensure that this turnout is unique among Layout Turnouts
 LayoutTurnout* t = NULL;
 for (int i=0;i<turnoutList->size();i++)
 {
  t = turnoutList->at(i);
  log.debug("LT '"+t->getName()+"', Turnout tested '"+t->getTurnoutName()+"' ");
  Turnout* to = t->getTurnout();
  /*Only check for the second turnout if the type is a double cross over
   otherwise the second turnout is used to throw an additional turnout at
   the same time.*/
  Turnout* to2 = NULL;
  if(t->getTurnoutType()>=LayoutTurnout::DOUBLE_XOVER)
  {
   to2 = t->getSecondTurnout();
  }
  if (to!=NULL)
  {
   if ( (to->getSystemName()==(turnoutName.toUpper())) ||
                ((to->getUserName()!=NULL) && (to->getUserName()==(turnoutName))) )
   {
//              JOptionPane.showMessageDialog(openPane,
//                        java.text.MessageFormat.format(rb.getQString("Error4"),
//                        new Object[]{turnoutName}),
//                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(openPane, tr("Error"), tr("Error - Physical turnout \"%1\" is already linked to a different Panel Turnout.\nPlease enter another turnout name and try again.").arg(turnoutName));

    return false;
   }
  }
  if (to2!=NULL)
  {
   if ( (to2->getSystemName()==(turnoutName.toUpper())) ||
                ((to2->getUserName()!=NULL) && (to2->getUserName()==(turnoutName))) )
   {
//                JOptionPane.showMessageDialog(openPane,
//                        java.text.MessageFormat.format(rb.getQString("Error4"),
//                        new Object[]{turnoutName}),
//                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Error"), tr("Error - Physical turnout \"%1\" is already linked to a different Panel Turnout.\nPlease enter another turnout name and try again.").arg(turnoutName));
    return false;
   }
  }
 }
#if 1 // TODO:
 foreach(LayoutSlip* slip, *slipList)
 {
  Turnout* to = slip->getTurnout();
  if(to!=NULL)
  {
   if(to->getSystemName()==(turnoutName) || (to->getUserName()!=NULL && to->getUserName()==(turnoutName)))
  {
//                JOptionPane.showMessageDialog(openPane,
//                        java.text.MessageFormat.format(rb.getQString("Error4"),
//                        new Object[]{turnoutName}),
//                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("Error - Physical turnout \"%1\" is already linked to a different Panel Turnout.\nPlease enter another turnout name and try again.").arg(turnoutName));
   return false;
  }
 }
 to=slip->getTurnoutB();
 if(to!=NULL)
  {
   if(to->getSystemName()==(turnoutName) || (to->getUserName()!=NULL && to->getUserName()==(turnoutName)))
  {
//                JOptionPane.showMessageDialog(openPane,
//                        java.text.MessageFormat.format(rb.getQString("Error4"),
//                        new Object[]{turnoutName}),
//                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("Error - Physical turnout \"%1\" is already linked to a different Panel Turnout.\nPlease enter another turnout name and try again.").arg(turnoutName));
   return false;
  }
 }
}
#endif
 // check that the unique turnout name corresponds to a defined physical turnout
 Turnout* to = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnoutName);
 if (to == NULL)
 {
        // There is no turnout corresponding to this name
//        JOptionPane.showMessageDialog(openPane,
//                java.text.MessageFormat.format(rb.getQString("Error8"),
//                new Object[]{turnoutName}),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Error - Cannot assign turnout because there\nis no turnout defined for \"%1\"\nPlease enter turnout via the Turnout Table and try again.").arg(turnoutName));

  return false;
 }
 return true;
}

/*private*/ void LayoutEditor::highLightSelection(EditScene* g)
{
  //java.awt.Stroke stroke = g.getStroke();
//  Color color = g.getColor();
//  g.setColor(new Color(204, 207, 88));
//  g.setStroke(new java.awt.BasicStroke(2.0f));
 QColor color = QColor(204,207,88);
 QPen pen(color,2.0);
 if(highlightRect != NULL && highlightRect->scene() != 0)
 {
  g->removeItem(highlightRect);
 }
 highlightRect = new QGraphicsItemGroup();

 if (_positionableSelection!=NULL)
 {
  for (int i = 0; i<_positionableSelection->size(); i++)
  {
   Positionable* c = _positionableSelection->at(i);
   //g.drawRect(c.getX(), c.getY(), c.maxWidth(), c.maxHeight());
   QGraphicsRectItem* item;
   SensorIcon* si;
   LocoIcon* li;
   MemoryIcon* mi;
   if((si = qobject_cast<SensorIcon*>(c))!=NULL)
    item = new QGraphicsRectItem(QRectF(si->getX(), si->getY(), si->maxWidth(), si->maxHeight()));
   else if((li = qobject_cast<LocoIcon*>(c))!=NULL)
    item = new QGraphicsRectItem(QRectF(li->getX(), li->getY(), li->maxWidth(), li->maxHeight()));
   else if((mi = qobject_cast<MemoryIcon*>(c))!=NULL)
    item = new QGraphicsRectItem(QRectF(mi->getX(), mi->getY(), mi->maxWidth(), mi->maxHeight()));

   item->setPen(pen);
   highlightRect->addToGroup(item);
  }
 }
 // loop over all defined turnouts
 if (_turnoutSelection!=NULL)
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
 if (_xingSelection!=NULL)
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
#if 1 //TODO:
  if (_slipSelection!=NULL)
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
#endif
#if 1 //TODO:
  // loop over all defined turntables
  if (_turntableSelection!=NULL)
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
#endif
  // loop over all defined Anchor Points and End Bumpers
  if (_pointSelection!=NULL)
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
  g->addItem(highlightRect);
}

/*private*/ void LayoutEditor::createSelectionGroups(){
  QList <Positionable*> contents = getContents();
  QRectF selectRect(selectionX, selectionY, selectionWidth, selectionHeight);
  QPointF upperLeft;
  for (int i = 0; i<contents.size(); i++)
  {
   Positionable* c = contents.at(i);
   PositionableLabel* pl = qobject_cast<PositionableLabel*>(c);
   if(pl == NULL)
   {
    qDebug() << "Error casting to PositionableLabel";
    continue;
   }
   upperLeft = pl->getLocation();
   if (selectRect.contains(upperLeft))
   {
    if (_positionableSelection==NULL) _positionableSelection = new QVector<Positionable*>();
    if(!_positionableSelection->contains(c))
     _positionableSelection->append(c);
   }
  }
  // loop over all defined turnouts
  for (int i = 0; i<turnoutList->size();i++)
  {
   LayoutTurnout* t = turnoutList->at(i);
   QPointF center = t->getCoordsCenter();
   if (selectRect.contains(center))
   {
    if (_turnoutSelection==NULL) _turnoutSelection = new QVector<LayoutTurnout*>();
    if(!_turnoutSelection->contains(t))
     _turnoutSelection->append(t);
   }
  }
  // loop over all defined level crossings
  for (int i = 0; i<xingList->size();i++)
  {
   LevelXing* x = xingList->at(i);
   QPointF center = x->getCoordsCenter();
   if (selectRect.contains(center))
   {
    if (_xingSelection==NULL)
     _xingSelection = new QVector<LevelXing*>();
    if(!_xingSelection->contains(x))
     _xingSelection->append(x);
   }
  }
 #if 1 // TODO::
  // loop over all defined level crossings
  for (int i = 0; i<slipList->size();i++)
  {
   LayoutSlip* x = slipList->at(i);
   QPointF center = x->getCoordsCenter();
   if (selectRect.contains(center))
  {
   if (_slipSelection==NULL) _slipSelection = new QVector<LayoutSlip*>();
   if(!_slipSelection->contains(x))
       _slipSelection->append(x);
   }
  }
#endif
#if 1  // TODO:
  // loop over all defined turntables
  for (int i = 0; i<turntableList->size();i++)
  {
   LayoutTurntable* x = turntableList->at(i);
   QPointF center = x->getCoordsCenter();
   if (selectRect.contains(center))
   {
    if (_turntableSelection==NULL) _turntableSelection = new QVector<LayoutTurntable*>();
    if(!_turntableSelection->contains(x))
        _turntableSelection->append(x);
   }
  }
#endif
  // loop over all defined Anchor Points and End Bumpers
  for (int i = 0; i<pointList->size();i++)
  {
   PositionablePoint* p = pointList->at(i);
   QPointF coord = p->getCoords();
   if (selectRect.contains(coord))
   {
    if (_pointSelection==NULL)
     _pointSelection = new QVector<PositionablePoint*>();
    if(!_pointSelection->contains(p))
     _pointSelection->append(p);
   }
  }
//  // loop over all defined Labels
//  for (int i=0; i < _labelImage->size(); i++)
//  {
//   PositionableLabel* l = _labelImage->at(i);
//   QPointF coord = l->getLocation();
//   if (selectRect.contains(coord))
//   {
//    if (_labelSelection==NULL)
//    _labelSelection = new QVector<PositionableLabel*>();
//    if(!_labelSelection->contains(l))
//      _labelSelection->append(l);
//   }
//  }
  //repaint();
  paintTargetPanel(editScene);
}


/*private*/ void LayoutEditor::clearSelectionGroups(){
  _pointSelection=NULL;
//  _turntableSelection=NULL;
  _xingSelection=NULL;
//  _slipSelection=NULL;
  _turnoutSelection=NULL;
  _positionableSelection=NULL;
  _labelSelection=NULL;
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
   //if (_debug && !_dragging) log.debug("getSelectedItems: rect= ("+rect.x+","+rect.y+
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
  //if (_debug)  log.debug("getSelectedItems at ("+x+","+y+") "+selections.size()+" found,");
  return selections->toList();
}

/*public*/ PositionablePoint* LayoutEditor::findPositionablePointByName(QString name) {
  if (name.length()<=0) return NULL;
  for (int i = 0; i<pointList->size(); i++) {
      PositionablePoint* p = pointList->at(i);
      if (p->getID()==(name)) {
          return p;
      }
  }
  return NULL;
}
/*public*/ PositionablePoint* LayoutEditor::findPositionablePointAtTrackSegments(TrackSegment* tr1, TrackSegment* tr2) {
  for (int i = 0; i<pointList->size(); i++) {
      PositionablePoint* p = pointList->at(i);
      if ( ( (p->getConnect1()==tr1) && (p->getConnect2()==tr2) ) ||
              ( (p->getConnect1()==tr2) && (p->getConnect2()==tr1) ) ) {
          return p;
      }
  }
  return NULL;
}
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
  if (name.length()<=0) return NULL;
  for (int i = 0; i<trackList->size(); i++) {
      TrackSegment* t = trackList->at(i);
      if (t->getID()==(name)) {
          return t;
      }
  }
  return NULL;
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
    log.error("Attempt to set a non-TRACK connection to a Positionable Point");
   }
   break;
  case TURNOUT_A:
      ((LayoutTurnout*)toObject)->setConnectA(fromObject,fromPointType);
      break;
  case TURNOUT_B:
      ((LayoutTurnout*)toObject)->setConnectB(fromObject,fromPointType);
      break;
  case TURNOUT_C:
      ((LayoutTurnout*)toObject)->setConnectC(fromObject,fromPointType);
      break;
  case TURNOUT_D:
      ((LayoutTurnout*)toObject)->setConnectD(fromObject,fromPointType);
      break;
  case LEVEL_XING_A:
      ((LevelXing*)toObject)->setConnectA(fromObject,fromPointType);
      break;
  case LEVEL_XING_B:
      ((LevelXing*)toObject)->setConnectB(fromObject,fromPointType);
      break;
  case LEVEL_XING_C:
      ((LevelXing*)toObject)->setConnectC(fromObject,fromPointType);
      break;
  case LEVEL_XING_D:
      ((LevelXing*)toObject)->setConnectD(fromObject,fromPointType);
      break;
  case SLIP_A:
      ((LayoutSlip*)toObject)->setConnectA(fromObject,fromPointType);
      break;
  case SLIP_B:
      ((LayoutSlip*)toObject)->setConnectB(fromObject,fromPointType);
      break;
  case SLIP_C:
      ((LayoutSlip*)toObject)->setConnectC(fromObject,fromPointType);
      break;
  case SLIP_D:
      ((LayoutSlip*)toObject)->setConnectD(fromObject,fromPointType);
      break;
  case TRACK:
      // should never happen, Track Segment links are set in ctor
      log.error("Illegal request to set a Track Segment link");
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
/*public*/ bool LayoutEditor::validateSensor(QString sensorName, LayoutBlock* blk/*, Component* openFrame*/)
{
 // check if anything entered
 if (sensorName.length()<1)
 {
  // no sensor entered
  return false;
 }
 // get a validated sensor corresponding to this name and assigned to block
 Sensor* s = blk->validateSensor(sensorName,openFrame);
 if (s==NULL)
 {
  // There is no sensor corresponding to this name
  return false;
 }
 return true;
}
/*public*/ LevelXing* LayoutEditor::findLevelXingByName(QString name)
 {
  if (name.length()<=0) return NULL;
  for (int i = 0; i<xingList->size(); i++)
  {
   LevelXing* x = xingList->at(i);
   if (x->getID()==(name))
   {
    return x;
   }
  }
  return NULL;
}
/*public*/ LayoutSlip* LayoutEditor::findLayoutSlipByName(QString name)
{
 if (name.length()<=0) return NULL;
 for (int i = 0; i<slipList->size(); i++)
 {
  LayoutSlip* x = slipList->at(i);
  if (x->getName()==(name))
  {
   return x;
  }
 }
 return NULL;
}
/**
 * @deprecated As of 3.9.2, ... use getFinder().find...
 */
//@Deprecated
/*public*/ LayoutTurntable* LayoutEditor::findLayoutTurntableByName(QString name) {
    return finder->findLayoutTurntableByName(name);
}

/*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByName(QString name)
{
 if (name.length()<=0) return NULL;
 for (int i = 0; i<turnoutList->size(); i++)
 {
  LayoutTurnout* t = turnoutList->at(i);
  if (t->getName()==(name))
  {
   return t;
  }
 }
 return NULL;
}

/*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByTurnoutName(QString name)
{
 if (name.length()<=0) return NULL;
 for (int i = 0; i<turnoutList->size(); i++)
 {
  LayoutTurnout* t = turnoutList->at(i);
  if (t->getTurnoutName()==(name))
  {
   return t;
  }
 }
 return NULL;
}
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
 LayoutBlock* blk = layoutBlockManager->getByUserName(blockID);
 if (blk==NULL)
 {
  log.error("LayoutBlock '"+blockID+"' not found when panel loaded");
  return NULL;
 }
 blk->addLayoutEditor(this);
 return blk;
}
/*public*/ QObject* LayoutEditor::findObjectByTypeAndName(int type,QString name)
{
  if (name.length()<=0) return NULL;
  switch (type) {
      case NONE:
          return NULL;
      case POS_POINT:
          return findPositionablePointByName(name);
      case TURNOUT_A:
      case TURNOUT_B:
      case TURNOUT_C:
      case TURNOUT_D:
          return findLayoutTurnoutByName(name);
      case LEVEL_XING_A:
      case LEVEL_XING_B:
      case LEVEL_XING_C:
      case LEVEL_XING_D:
          return findLevelXingByName(name);
      case SLIP_A:
      case SLIP_B:
      case SLIP_C:
      case SLIP_D:
          return findLayoutSlipByName(name);
      case TRACK:
          return findTrackSegmentByName(name);
      default:
          if (type>=TURNTABLE_RAY_OFFSET)
           return findLayoutTurntableByName(name);
      break;
  }
  log.error("did not find Object '"+name+"' of type "+type);
  return NULL;
}
/*public*/ LayoutBlock* LayoutEditor::getAffectedBlock(QObject* o, int type) {
  if (o==NULL)
   return NULL;
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
  return NULL;
}

/*protected*/ QPointF LayoutEditor::getCoords(QObject* o, int type)
{
 if (o != NULL)
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
  log.error("NULL connection point of type "+QString("%1").arg(type));
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
   return NULL;
  }
  else
  {
   //blk = InstanceManager::layoutBlockManagerInstance().createNewLayoutBlock();
   blk = layoutBlockManager->createNewLayoutBlock();
   if (blk == NULL)
   {
    log.error("Unable to create a layout block");
    return NULL;
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
  blk = layoutBlockManager->getByUserName(s);
  if (blk == NULL)
  {
   //blk = InstanceManager::layoutBlockManagerInstance().createNewLayoutBlock(NULL,s);
   blk = layoutBlockManager->createNewLayoutBlock("",s);
   if (blk == NULL)
   {
    log.error("Failure to create LayoutBlock '"+s+"'.");
    return NULL;
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
  if (name.length()<=0) return NULL;
  QVector<TrackSegment*>* ts = new QVector<TrackSegment*>();
  for (int i = 0; i<trackList->size(); i++) {
      TrackSegment* t = trackList->at(i);
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

/**
*  Special internal class to allow drawing of layout to a JLayeredPane
*  This is the 'target' pane where the layout is displayed
*/
/*protected*/ void LayoutEditor::paintTargetPanel(EditScene* g2)
{
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
  trackWidth = sideTrackWidth;
//      g2.setStroke(new BasicStroke(sideTrackWidth,BasicStroke.CAP_BUTT,                                                      BasicStroke.JOIN_ROUND));
 }
}
#if 1 // TODO:

/*protected*/ void LayoutEditor::drawTurnouts(EditScene* g2)
{
 //float trackWidth = sideTrackWidth;
 // loop over all defined turnouts
 for (int i = 0; i<turnoutList->size();i++)
 {
  LayoutTurnout* t = turnoutList->at(i);
  t->invalidate(g2);
  t->drawTurnouts(this, g2);
 }
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
#endif
/*private*/ void LayoutEditor::drawXings(EditScene* g2)
{
 // loop over all defined level crossings
 for (int i = 0; i<xingList->size();i++)
 {
  LevelXing* x = xingList->at(i);
  x->invalidate(g2);
  x->drawXings(this, g2);
 }
}

/*private*/ void LayoutEditor::drawSlips(QGraphicsScene* g2)
{
 for (int i = 0; i<slipList->size();i++)
 {
  LayoutSlip* x = slipList->at(i);
  LayoutBlock* b = x->getLayoutBlock();
  setTrackStrokeWidth(x->isMainline());
  QColor mainColour;
  QColor subColour;
  if (b!=NULL)
  {
   mainColour = b->getBlockColor();
   subColour = b->getBlockTrackColor();
  }
  else
  {
   mainColour = defaultTrackColor;
   subColour = defaultTrackColor;
  }
  if(x->item != NULL && x->item->scene()!=0)
  {
   g2->removeItem(x->item);
   x->item = NULL;
  }
  if(x->rects != NULL)
  {
   Q_ASSERT(x->rects->scene()!=0);
   g2->removeItem(x->rects);
   x->rects = NULL;
  }
  x->item = new QGraphicsItemGroup();

  //g2.setColor(subColour);

//  g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsC())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsC())));
  line1->setPen(QPen(subColour,trackWidth));
  x->item->addToGroup(line1);

//  g2.draw(new Line2D.Double(x.getCoordsC(),
//          third(x.getCoordsC(),x.getCoordsA())));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(),third(x->getCoordsC(),x->getCoordsA())));
  line2->setPen(QPen(subColour,trackWidth));
  x->item->addToGroup(line2);

//      g2.draw(new Line2D.Double(x.getCoordsB(),
//          third(x.getCoordsB(),x.getCoordsD())));
  QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(),third(x->getCoordsB(),x->getCoordsD())));
  line3->setPen(QPen(subColour,trackWidth));
  x->item->addToGroup(line3);

//      g2.draw(new Line2D.Double(x.getCoordsD(),
//          third(x.getCoordsD(),x.getCoordsB())));
  QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(),third(x->getCoordsD(),x->getCoordsB())));
  line4->setPen(QPen(subColour,trackWidth));
  x->item->addToGroup(line4);


  if(x->getSlipType()==LayoutSlip::DOUBLE_SLIP)
  {
   if (x->getSlipState()==LayoutSlip::STATE_AC)
   {
//          g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsD())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);

//          g2.draw(new Line2D.Double(x.getCoordsD(),
//              third(x.getCoordsD(),x.getCoordsA())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);

//          g2.draw(new Line2D.Double(x.getCoordsB(),
//              third(x.getCoordsB(),x.getCoordsC())));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
    line3->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line3);

//          g2.draw(new Line2D.Double(x.getCoordsC(),
//              third(x.getCoordsC(),x.getCoordsB())));
    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
    line4->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line4);

//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
    QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
    line5->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line5);

   }
   else if (x->getSlipState()==LayoutSlip::STATE_BD)
   {
//          g2.draw(new Line2D.Double(x.getCoordsB(),
//              third(x.getCoordsB(),x.getCoordsC())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);

//          g2.draw(new Line2D.Double(x.getCoordsC(),
//              third(x.getCoordsC(),x.getCoordsB())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);


//          g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsD())));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
    line3->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line3);

//          g2.draw(new Line2D.Double(x.getCoordsD(),
//              third(x.getCoordsD(),x.getCoordsA())));
    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
    line4->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line4);

//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
    QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
    line5->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line5);

   }
   else if (x->getSlipState()==LayoutSlip::STATE_AD)
   {
//          g2.draw(new Line2D.Double(x.getCoordsB(),
//              third(x.getCoordsB(),x.getCoordsC())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);

//          g2.draw(new Line2D.Double(x.getCoordsC(),
//              third(x.getCoordsC(),x.getCoordsB())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);

//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsD()));
    line3->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line3);

   }
   else if (x->getSlipState()==LayoutSlip::STATE_BC)
   {
//          g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsD())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);


//          g2.draw(new Line2D.Double(x.getCoordsD(),
//              third(x.getCoordsD(),x.getCoordsA())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);

//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsC()));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsC()));
    line3->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line3);

   }
   else
   {
//          g2.draw(new Line2D.Double(x.getCoordsB(),
//              third(x.getCoordsB(),x.getCoordsC())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), third(x->getCoordsB(),x->getCoordsC())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);


//          g2.draw(new Line2D.Double(x.getCoordsC(),
//              third(x.getCoordsC(),x.getCoordsB())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsC(), third(x->getCoordsC(),x->getCoordsB())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);

//          g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsD())));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
    line3->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line3);

//          g2.draw(new Line2D.Double(x.getCoordsD(),
//              third(x.getCoordsD(),x.getCoordsA())));
    QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
    line4->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line4);
   }
  }
  else
  {
//      g2.draw(new Line2D.Double(x.getCoordsA(),
//          third(x.getCoordsA(),x.getCoordsD())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
   line1->setPen(QPen(subColour,trackWidth));
   x->item->addToGroup(line1);

//      g2.draw(new Line2D.Double(x.getCoordsD(),
//          third(x.getCoordsD(),x.getCoordsA())));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
   line2->setPen(QPen(subColour,trackWidth));
   x->item->addToGroup(line2);
   if (x->getSlipState()==LayoutSlip::STATE_AD)
   {
//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsD()));
    line1->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line1);

   }
   else if (x->getSlipState()==LayoutSlip::STATE_BD)
   {
//          g2.setColor(mainColour);
//          g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
    line1->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line1);

    if(x->singleSlipStraightEqual())
    {
//              g2.setColor(mainColour);
//              g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
     QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
       line1->setPen(QPen(mainColour,trackWidth));
     x->item->addToGroup(line1);

    }
   }
   else if (x->getSlipState()==LayoutSlip::STATE_AC)
   {
             //          g2.setColor(mainColour);
             //          g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
       QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), x->getCoordsC()));
    line1->setPen(QPen(mainColour,trackWidth));
    x->item->addToGroup(line1);

    if(x->singleSlipStraightEqual())
    {
//              g2.setColor(mainColour);
//              g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
     QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsB(), x->getCoordsD()));
     line1->setPen(QPen(mainColour,trackWidth));
     x->item->addToGroup(line1);

    }
   }
   else
   {
//          g2.draw(new Line2D.Double(x.getCoordsA(),
//              third(x.getCoordsA(),x.getCoordsD())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(x->getCoordsA(), third(x->getCoordsA(),x->getCoordsD())));
    line1->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line1);

//          g2.draw(new Line2D.Double(x.getCoordsD(),
//              third(x.getCoordsD(),x.getCoordsA())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(x->getCoordsD(), third(x->getCoordsD(),x->getCoordsA())));
    line2->setPen(QPen(subColour,trackWidth));
    x->item->addToGroup(line2);

   }
  }
  g2->addItem(x->item);
 }
}

/*private*/ void LayoutEditor::drawTurnoutCircles(EditScene* g2)
{
  // loop over all defined turnouts
  for (int i = 0; i<turnoutList->size();i++)
  {
   LayoutTurnout* t = turnoutList->at(i);
   if(!(t->getHidden() && !isEditable()))
   {
    t->drawTurnoutCircles(this, g2);
   }
  }
} //drawTurnoutCircles

/*private*/ void LayoutEditor::drawSlipCircles(EditScene* g2)
{
 //loop over all defined slips

 for (int i = 0; i<slipList->size();i++)
 {
  LayoutSlip* sl = slipList->at(i);
  if(!(sl->getHidden() && !isEditable()))
  {
   sl->drawSlipCircles(g2);
  }
 }
}  //drawSlipCircles

/*private*/ void LayoutEditor::drawTurnoutRects(EditScene* g2)
{
  // loop over all defined turnouts
  for (int i = 0; i<turnoutList->size();i++)
  {
   LayoutTurnout* t = turnoutList->at(i);
   t->drawTurnoutRects(this, g2);
  }
  for(int i=0; i < slipList->count(); i++)
  {
   LayoutSlip* s = slipList->at(i);
   s->drawTurnoutRects(this, g2);
  }
}
#if 1
/*private*/ void LayoutEditor::drawTurntables(EditScene* g2)
{
  // loop over all defined layout turntables
  if (turntableList->size()<=0) return;
  for (int i = 0; i<turntableList->size();i++)
  {
   LayoutTurntable* x = turntableList->at(i);
   if(x->item != NULL && x->item->scene()!=0)
   {
    g2->removeItem(x->item);
    x->item = NULL;
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
   circle->setPen(QPen(defaultTrackColor, sideTrackWidth));
   x->item->addToGroup(circle);

   // draw ray tracks
   QColor color;
   for (int j = 0; j<x->getNumberRays(); j++)
   {
    QPointF pt = x->getRayCoordsOrdered(j);
    TrackSegment* t = x->getRayConnectOrdered(j);
    if (t!=NULL)
    {
     setTrackStrokeWidth(/*g2,*/t->getMainline());
     LayoutBlock* b = t->getLayoutBlock();
     if (b!=NULL) color = (b->getBlockColor());
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
   g2->addItem(x->item);
  }
}
#endif
/*private*/ void LayoutEditor::drawXingRects(EditScene* g2)
{
 // loop over all defined level crossings
 for (int i = 0; i<xingList->size();i++)
 {
  LevelXing* x = xingList->at(i);
  x->drawXingRects(this, g2);
 }
}
#if 1// see drawSlips.
/*private*/ void LayoutEditor::drawSlipRects(EditScene* /*g2*/)
{
  // loop over all defined level crossings
  for (int i = 0; i<slipList->size();i++)
  {
   QColor color;
      LayoutSlip* x = slipList->at(i);
      QPointF pt = x->getCoordsCenter();
//      g2.setColor(defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
      QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2);
      circle->setPen(QPen(defaultTrackColor,1));
      x->item->addToGroup(circle);
      pt = x->getCoordsA();
      if (x->getConnectA()==NULL) {
          //g2.setColor(QColor::red);
       color = Qt::red;
      }
      else {
          //g2.setColor(QColor::green);
       color = Qt::green;
      }
//      g2.draw(new Rectangle2D.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      QGraphicsRectItem* rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
      rect->setPen(QPen(color, 1));
      x->item->addToGroup(rect);
      pt = x->getCoordsB();
      if (x->getConnectB()==NULL) {
          //g2.setColor(QColor::red);
       color = Qt::red;
      }
      else {
          //g2.setColor(QColor::green);
       color = Qt::green;
      }
//      g2.draw(new Rectangle2D.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
      rect->setPen(QPen(color, 1));
      x->item->addToGroup(rect);
      pt = x->getCoordsC();
      if (x->getConnectC()==NULL) {
          //g2.setColor(QColor::red);
       color = Qt::red;
      }
      else {
          //g2.setColor(QColor::green);
       color = Qt::green;
      }
//      g2.draw(new Rectangle2D.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
      rect->setPen(QPen(color, 1));
      x->item->addToGroup(rect);
      pt = x->getCoordsD();
      if (x->getConnectD()==NULL) {
          //g2.setColor(QColor::red);
       color = Qt::red;
      }
      else {
          //g2.setColor(QColor::green);
       color = Qt::green;
      }
//      g2.draw(new Rectangle2D.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
      rect->setPen(QPen(color, 1));
      x->item->addToGroup(rect);
  }
}
#endif
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
          if (x->getRayConnectOrdered(j)==NULL) {
              //g2.setColor(QColor::red);
           color = Qt::red;
          }
          else {
              //g2.setColor(QColor::green);
           color = Qt::green;
          }
//          g2.draw(new Rectangle2D.Double (
//                      pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
          QGraphicsRectItem* rect = new QGraphicsRectItem(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2);
          rect->setPen(QPen(color, trackWidth));
          x->item->addToGroup(rect);
      }
  }
}

/*private*/ void LayoutEditor::drawHiddenTrack(EditScene* g2)
{
 for (int i = 0; i<trackList->size();i++)
 {
  TrackSegment* t = trackList->at(i);
  if (isEditable() && t->getHidden())
  {
   t->invalidate(g2);
   t->drawHiddenTrack(this, g2);
  }
 }
}
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
//   if(l->item != NULL)
//   {
//    g2->removeItem(l->item);
//    l->item = NULL;
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

/*private*/ void LayoutEditor::drawDashedTrack(EditScene* g2, bool mainline)
{
 for (int i = 0; i<trackList->size();i++)
 {
  TrackSegment* t = trackList->at(i);
  if ( (!t->getHidden()) && t->getDashed() && (mainline == t->getMainline()) )
  {
   t->invalidate(g2);
   t->drawDashedTrack(this, g2, mainline);
  }
 }
}

/* draw all track segments which are not hidden, not dashed, and that match the isMainline parm */
/*private*/ void LayoutEditor::drawSolidTrack(EditScene* g2, bool isMainline)
{
  for (int i = 0; i<trackList->size();i++)
  {
   setTrackStrokeWidth(isMainline);
   TrackSegment* t = trackList->at(i);
   if ( (!t->getHidden()) && (!t->getDashed()) && (isMainline == t->getMainline()) )
   {
    t->invalidate(g2);
    t->drawSolidTrack(this, g2, isMainline);
   }
  }
}


/*
* Draws a square at the circles centre, that then allows the user to dynamically change
* the angle by dragging the mouse.
*/
/*private*/ void LayoutEditor::drawTrackCircleCentre(EditScene* g2)
{
  // loop over all defined turnouts
  for (int i = 0; i<trackList->size();i++)
  {
   TrackSegment* t = trackList->at(i);
   if (t->getCircle())
   {
    t->drawTrackCircleCentre(this,g2);
   }
  }
}

/*private*/ void LayoutEditor::drawTrackInProgress(EditScene* g2)
{
 // check for segment in progress

 if ( isEditable() && (beginObject!=NULL) && ui->chkTrackSegment->isChecked() )
 {
//      g2.setColor(defaultTrackColor);
//      setTrackStrokeWidth(g2,false);
//      g2.draw(new Line2D.Double(beginLocation,currentLocation));
  if(trackInProgress != NULL && trackInProgress->scene()!=0)
  {
   g2->removeItem(trackInProgress);
  }
   //g2->addLine(QLineF(beginLocation,currentLocation),QPen(QColor(defaultTrackColor),1));
   QGraphicsLineItem* item  = new QGraphicsLineItem(QLineF(beginLocation,currentLocation));
   item->setPen(QPen(QColor(defaultTrackColor),1));
   trackInProgress = item;
   g2->addItem(trackInProgress);
  }
}
/*private*/ void LayoutEditor::drawTrackOvals(EditScene* g2)
{
  // loop over all defined track segments
  for (int i = 0; i<trackList->size();i++)
  {
   TrackSegment* t = trackList->at(i);
   t->drawTrackOvals(this, g2);
  }
}

/*private*/ void LayoutEditor::drawPoints(EditScene* g2)
{
  if(!isEditable())
   return;
  for (int i = 0; i<pointList->size();i++)
  {
   PositionablePoint* p = pointList->at(i);
   p->invalidate( g2);
   p->draw( g2);
  }
}

#if 1

/*private*/ void LayoutEditor::drawSelectionRect(EditScene* editScene)
{
  if ( selectionActive && (selectionWidth!=0.0) && (selectionHeight!=0.0) )
  {
//      g2.setColor(defaultTrackColor);
//      g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
//      g2.draw(new Rectangle2D.Double (selectionX, selectionY, selectionWidth, selectionHeight));
   if(rectItem != NULL)
   {
    Q_ASSERT(rectItem->scene()!=0);
    editScene->removeItem(rectItem);
   }
   rectItem = new QGraphicsRectItem(QRect(selectionX, selectionY, selectionWidth, selectionHeight),0);
   rectItem->setPen(QPen(defaultTrackColor, 3, Qt::SolidLine));
   editScene->addItem(rectItem);
  }
}
#endif
#if 1
/*private*/ void LayoutEditor::drawMemoryRects(EditScene* g2)
{
 QColor color;
  if (memoryLabelList->size()<=0) return;
  color =(defaultTrackColor);
//  g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
  for (int i = 0;i<memoryLabelList->size();i++)
  {
   MemoryIcon* l = memoryLabelList->at(i);
   if(l->_itemGroup != NULL && l->_itemGroup->scene() != 0)
   {
    Q_ASSERT(l->_itemGroup->scene()!=0);
    g2->removeItem(l->_itemGroup);
    l->_itemGroup = NULL;
   }
   l->_itemGroup = new MyGraphicsItemGroup();
   l->_itemGroup->setName("drawMemoryRects");
   //g2.draw(new Rectangle2D.Double (l.x(), l.y(), l.getSize().width, l.getSize().height));
   //g2->addRect(QRectF(l->getX(), l->getY(), l->getSize().width(), l->getSize().height()),QPen(color, 1));
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(l->getX(), l->getY(), l->getSize().width(), l->getSize().height()));
   item->setPen(QPen(color, 1));
   l->_itemGroup->addToGroup(item);
   g2->addItem(l->_itemGroup);
  }
}
#endif
#if 1
/*private*/ void LayoutEditor::drawPanelGrid(EditScene* g2)
{
  //Dimension dim = getSize();
  if(panelGridGroup!=NULL)
  {
   Q_ASSERT(panelGridGroup->scene()!=0);
   g2->removeItem(panelGridGroup);
   //g2->destroyItemGroup(panelGridGroup);
  }
  panelGridGroup = NULL;
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
 g2->addItem(panelGridGroup);
}
#endif

/*private*/ bool LayoutEditor::checkSelect(QPointF loc, bool requireUnconnected) {
    return checkSelect(loc, requireUnconnected, NULL);
}

/*private*/ bool LayoutEditor::checkSelect(QPointF loc, bool requireUnconnected, QObject* avoid)
{
 // check positionable points, if any
 for (int i = 0; i<pointList->size();i++)
 {
  PositionablePoint* p = pointList->at(i);
  if(p != avoid)
  {
   if ( (p!=selectedObject) && !requireUnconnected ||
               (p->getConnect1()==NULL) ||
               ((p->getType()!=PositionablePoint::END_BUMPER) &&
                                           (p->getConnect2()==NULL)) )
   {
    QPointF pt = p->getCoords();
    QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
    if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = p;
     foundPointType = POS_POINT;
     foundNeedsConnect = ((p->getConnect1()==NULL)||(p->getConnect2()==NULL));
     return true;
    }
   }
  }
 }
 // check turnouts, if any
 for (int i = 0; i<turnoutList->size();i++)
 {
  LayoutTurnout* t = turnoutList->at(i);
  if (t!=selectedObject)
  {
   if (!requireUnconnected)
   {
    // check the center point
    QPointF pt = t->getCoordsCenter();
    QRectF r =  QRectF(pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
    if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = t;
     foundNeedsConnect = false;
     foundPointType = TURNOUT_CENTER;
     return true;
    }
   }
   if (!requireUnconnected || (t->getConnectA()==NULL))
   {
    // check the A connection point
    QPointF pt = t->getCoordsA();
    QRectF r =  QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
    if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = t;
     foundPointType = TURNOUT_A;
     foundNeedsConnect = (t->getConnectA()==NULL);
     return true;
    }
   }
   if (!requireUnconnected || (t->getConnectB()==NULL))
   {
    // check the B connection point
    QPointF pt = t->getCoordsB();
    QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
    if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = t;
     foundPointType = TURNOUT_B;
     foundNeedsConnect = (t->getConnectB()==NULL);
     return true;
    }
   }
   if (!requireUnconnected || (t->getConnectC()==NULL))
   {
    // check the C connection point
    QPointF pt = t->getCoordsC();
    QRectF r =  QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
    if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = t;
     foundPointType = TURNOUT_C;
     foundNeedsConnect = (t->getConnectC()==NULL);
     return true;
    }
   }
   if (( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
          (t->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
          (t->getTurnoutType()==LayoutTurnout::LH_XOVER) ) && (
          !requireUnconnected || (t->getConnectD()==NULL)))
   {
    // check the D connection point, double crossover turnouts only
    QPointF pt = t->getCoordsD();
    QRectF r =  QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
      if (r.contains(loc))
    {
     // mouse was pressed on this connection point
     foundLocation = pt;
     foundObject = t;
     foundPointType = TURNOUT_D;
     foundNeedsConnect = (t->getConnectD()==NULL);
     return true;
    }
   }
  }
  }

  // check level Xings, if any
  for (int i = 0; i<xingList->size();i++)
  {
   LevelXing* x = xingList->at(i);
   if (x!=selectedObject)
   {
    if (!requireUnconnected)
    {
     // check the center point
     QPointF pt = x->getCoordsCenter();
     QRectF r = QRectF(pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
     if (r.contains(loc))
     {
      // mouse was pressed on this connection point
      foundLocation = pt;
      foundObject = x;
      foundPointType = LEVEL_XING_CENTER;
      foundNeedsConnect = false;
      return true;
     }
    }
    if (!requireUnconnected || (x->getConnectA()==NULL))
    {
     // check the A connection point
     QPointF pt = x->getCoordsA();
     QRectF r = QRectF(pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
     if (r.contains(loc))
     {
      // mouse was pressed on this connection point
      foundLocation = pt;
      foundObject = x;
      foundPointType = LEVEL_XING_A;
      foundNeedsConnect = (x->getConnectA()==NULL);
      return true;
     }
    }
    if (!requireUnconnected || (x->getConnectB()==NULL))
    {
     // check the B connection point
     QPointF pt = x->getCoordsB();
     QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
     if (r.contains(loc))
     {
      // mouse was pressed on this connection point
      foundLocation = pt;
      foundObject = x;
      foundPointType = LEVEL_XING_B;
      foundNeedsConnect = (x->getConnectB()==NULL);
      return true;
     }
    }
    if (!requireUnconnected || (x->getConnectC()==NULL))
    {
     // check the C connection point
     QPointF pt = x->getCoordsC();
     QRectF r =  QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
     if (r.contains(loc))
     {
      // mouse was pressed on this connection point
      foundLocation = pt;
      foundObject = x;
      foundPointType = LEVEL_XING_C;
      foundNeedsConnect = (x->getConnectC()==NULL);
      return true;
     }
    }
    if (!requireUnconnected || (x->getConnectD()==NULL))
    {
     // check the D connection point
     QPointF pt = x->getCoordsD();
     QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
     if (r.contains(loc))
     {
      // mouse was pressed on this connection point
      foundLocation = pt;
      foundObject = x;
      foundPointType = LEVEL_XING_D;
      foundNeedsConnect = (x->getConnectD()==NULL);
      return true;
     }
    }
   }
  }
  // check level Xings, if any
  for(int i=0; i < slipList->count(); i++)
  {
   LayoutSlip* x = slipList->at(i);
   if (x!=selectedObject)
   {
    LayoutSlip* x = slipList->at(i);
    if (!requireUnconnected)
    {
      // check the center point
      QPointF pt = x->getCoordsCenter();
      QRectF r = QRectF(pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
      if (r.contains(loc))
      {
          // mouse was pressed on this connection point
          foundLocation = pt;
          foundObject = x;
          foundPointType = SLIP_CENTER;
          foundNeedsConnect = false;
          return true;
      }
     }
     if (!requireUnconnected || (x->getConnectA()==NULL))
     {
          // check the A connection point
          QPointF pt = x->getCoordsA();
          QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
          if (r.contains(loc))
          {
              // mouse was pressed on this connection point
              foundLocation = pt;
              foundObject = x;
              foundPointType = SLIP_A;
              foundNeedsConnect = (x->getConnectA()==NULL);
              return true;
          }
      }
      if (!requireUnconnected || (x->getConnectB()==NULL)) {
          // check the B connection point
          QPointF pt = x->getCoordsB();
          QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
          if (r.contains(loc))
          {
              // mouse was pressed on this connection point
              foundLocation = pt;
              foundObject = x;
              foundPointType = SLIP_B;
              foundNeedsConnect = (x->getConnectB()==NULL);
              return true;
          }
      }
      if (!requireUnconnected || (x->getConnectC()==NULL))
      {
          // check the C connection point
          QPointF pt = x->getCoordsC();
          QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
          if (r.contains(loc))
          {
              // mouse was pressed on this connection point
              foundLocation = pt;
              foundObject = x;
              foundPointType = SLIP_C;
              foundNeedsConnect = (x->getConnectC()==NULL);
              return true;
          }
      }
      if (!requireUnconnected || (x->getConnectD()==NULL))
      {
          // check the D connection point
          QPointF pt = x->getCoordsD();
          QRectF r = QRectF(pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
          if (r.contains(loc))
          {
              // mouse was pressed on this connection point
              foundLocation = pt;
              foundObject = x;
              foundPointType = SLIP_D;
              foundNeedsConnect = (x->getConnectD()==NULL);
              return true;
          }
      }
    }
  }
  #if 1
  // check turntables, if any
  for (int i = 0; i<turntableList->size();i++) {
      LayoutTurntable* x = turntableList->at(i);
      if (x!=selectedObject) {
          if (!requireUnconnected) {
              // check the center point
              QPointF pt = x->getCoordsCenter();
              QRectF r = QRectF(
                      pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
              if (r.contains(loc)) {
                  // mouse was pressed on this center point
                  foundLocation = pt;
                  foundObject = x;
                  foundPointType = TURNTABLE_CENTER;
                  foundNeedsConnect = false;
                  return true;
              }
          }
          for (int k = 0; k<x->getNumberRays(); k++) {
              if (!requireUnconnected || (x->getRayConnectOrdered(k)==NULL)) {
                  QPointF pt = x->getRayCoordsOrdered(k);
                  QRectF r = QRectF(
                          pt.x() - SIZE,pt.y() - SIZE,SIZE2,SIZE2);
                  if (r.contains(loc)) {
                      // mouse was pressed on this connection point
                      foundLocation = pt;
                      foundObject = x;
                      foundPointType = TURNTABLE_RAY_OFFSET+x->getRayIndex(k);
                      foundNeedsConnect = (x->getRayConnectOrdered(k)==NULL);
                      return true;
                  }
              }
          }
      }
  }
#endif
 for (int i = 0; i<trackList->size();i++)
 {
  TrackSegment* t = trackList->at(i);
  if (t->getCircle())
  {
   QPointF pt = t->getCoordsCenterCircle();
   QRectF r = QRectF(pt.x() - SIZE2,pt.y() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
   if (r.contains(loc))
   {
    // mouse was pressed on this connection point
    foundLocation = pt;
    foundObject = t;
    foundPointType = TRACK_CIRCLE_CENTRE;
    foundNeedsConnect = false;
    return true;
   }
  }
 }
 for(int i=0; i < _labelImage->size(); i++)
 {
  PositionableLabel* l = _labelImage->at(i);
  if(l->getItem() != NULL)
  {
   QPointF pt = l->getItem()->mapFromParent(loc);
   if(l->getItem()->contains(pt))
   {
    foundLocation = loc;
    foundObject = l;
    foundPointType = LAYOUT_POS_LABEL;
    return true;
   }
  }
 }
 // no connection point found
 foundObject = NULL;
 return false;
}
/*private*/ void LayoutEditor::amendSelectionGroup(Positionable* p)
{
 if (_positionableSelection==NULL)
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
  _positionableSelection=NULL;
 }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(LayoutTurnout* p){
  if (_turnoutSelection==NULL){
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
      _turnoutSelection=NULL;
  }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(PositionablePoint* p){
  if (_pointSelection==NULL){
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
      _pointSelection=NULL;
  }
  //repaint();
  paintTargetPanel(editScene);
}

/*private*/ void LayoutEditor::amendSelectionGroup(LevelXing* p){
  if (_xingSelection==NULL){
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
      _xingSelection=NULL;
  }
  //repaint();
  paintTargetPanel(editScene);
}

 #if 1 // TODO:
/*private*/ void LayoutEditor::amendSelectionGroup(LayoutTurntable* p){
  if (_turntableSelection==NULL){
      _turntableSelection = new QVector <LayoutTurntable*>();
  }
  bool removed = false;
  for(int i=0; i<_turntableSelection->size();i++){
      if (_turntableSelection->at(i)==p){
          _turntableSelection->remove(i);
          removed = true;
          break;
      }
  }
  if(!removed)
      _turntableSelection->append(p);
  if (_turntableSelection->size()==0){
      _turntableSelection=NULL;
  }
  //repaint();
  paintTargetPanel(editScene);
}
#endif
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
//      _highlightcomponent = NULL;
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

/*public*/ bool LayoutEditor::allPositionable() {
  return _positionable;
}
/*public*/ bool LayoutEditor::allControlling()
{
  return _controlLayout;
}
void LayoutEditor::on_actionShow_grid_in_edit_mode_toggled(bool bChecked)
{
 drawGrid = bChecked;
 ui->actionShow_grid_in_edit_mode->setChecked(bChecked);
 paintTargetPanel(editScene);
}
void LayoutEditor::on_actionEdit_mode_toggled(bool bState)
{
 bIsEditable = bState;
 ui->actionEdit_mode->setChecked(bState);
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
#if 1 // TODO
  case TURNTABLE_CENTER:
      ((LayoutTurntable*)foundObject)->showPopUp(event);
      break;
#endif
  default: break;
  }
#if 1 // TODO::
  if(foundPointType>=TURNTABLE_RAY_OFFSET)
  {
   LayoutTurntable* t = (LayoutTurntable*)foundObject;
   if(t->isTurnoutControlled())
   {
     ((LayoutTurntable*)foundObject)->showRayPopUp(event, foundPointType-TURNTABLE_RAY_OFFSET);
   }
  }
#endif
 }
 else
 {
  TrackSegment* tr = checkTrackSegments(dLoc);
  if (tr!=NULL)
  {
   tr->showPopUp(event);
  }
  else
  {
   SensorIcon* s = checkSensorIcons(dLoc);
   if (s!=NULL)
   {
    showPopUp((Positionable*)s, event);
   }
   else
   {
    LocoIcon* lo = checkMarkers(dLoc);
    if (lo!=NULL)
    {
     showPopUp((Positionable*)lo, event);
    }
    else
    {
     SignalHeadIcon* sh = checkSignalHeadIcons(dLoc);
     if (sh!=NULL)
     {
      showPopUp((Positionable*)sh, event);
     }
     else
     {
      AnalogClock2Display* c = checkClocks(dLoc);
      if (c!=NULL)
      {
       showPopUp((Positionable*)c, event);
      }
      else
      {
       MultiSensorIcon* ms = checkMultiSensors(dLoc);
       if (ms!=NULL)
       {
        showPopUp((Positionable*)ms, event);
       }
       else
       {
        PositionableLabel* lb = checkLabelImages(dLoc);
        if (lb!=NULL)
        {
         showPopUp((Positionable*)lb, event);
        }
        else
        {
         PositionableLabel* b = checkBackgrounds(dLoc);
         if (b!=NULL)
         {
          showPopUp((Positionable*)b, event);
         }
         else
         {
          SignalMastIcon* sm = checkSignalMastIcons(dLoc);
          if (sm!=NULL)
          {
            showPopUp((Positionable*)sm, event);
          }
          else
          {
           MemoryIcon* mi = checkMemoryMarkerIcons(dLoc);
           if(mi != NULL)
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
 PositionableLabel* positionableLabel = qobject_cast<PositionableLabel*>(p);
 Q_ASSERT(positionableLabel != NULL);
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
   if (util!=NULL)
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
   setShowTooltipMenu(p, popup);

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
  if(util!=NULL)
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


/*private*/ TrackSegment* LayoutEditor::checkTrackSegments(QPointF loc)
{
 // check Track Segments, if any
 for (int i = 0; i<trackList->size(); i++)
 {
  TrackSegment* tr = trackList->at(i);
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
 return NULL;
}
/*protected*/ bool LayoutEditor::showAlignPopup()
{
 if (_positionableSelection!=NULL)
 {
  return true;
 }
 else if (_pointSelection!=NULL)
 {
  return true;
 }
 else if (_turnoutSelection!=NULL && !_turnoutSelection->isEmpty())
 {
     return true;
 }
 #if 1 // TODO:
 else if (_turntableSelection!=NULL)
 {
     return true;
 }
 #endif
 else if (_xingSelection!=NULL)
 {
     return true;
 }
 else if (_slipSelection!=NULL && !_slipSelection->isEmpty())
 {
     return true;
 }
// else if(_labelSelection !=NULL)
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
             if(o == NULL)
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
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
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
  if (selectedObject==o) selectedObject = NULL;
  if (prevSelectedObject==o) prevSelectedObject = NULL;
  // remove connections if any
  TrackSegment* t = o->getConnect1();
  if (t!=NULL) removeTrackSegment(t);
  t = o->getConnect2();
  if (t!=NULL) removeTrackSegment(t);
  // delete from array
  for (int i = 0; i<pointList->size();i++)
  {
   PositionablePoint* p = pointList->at(i);
   if (p==o)
   {
    // found object
    pointList->remove(i);
    p->invalidate(editScene);
    setDirty(true);
    //repaint();
    paintTargetPanel(editScene);
    return(true);
   }
  }
  return (false);
}
/**
* Remove a Track Segment
*/
/*protected*/ void LayoutEditor::removeTrackSegment(TrackSegment* o) {
  // save affected blocks
  LayoutBlock* block1 = NULL;
  LayoutBlock* block2 = NULL;
  LayoutBlock* block = o->getLayoutBlock();
  // remove any connections
  int type = o->getType1();
  if (type==POS_POINT) {
      PositionablePoint* p = (PositionablePoint*)(o->getConnect1());
      if (p!=NULL) {
          p->removeTrackConnection(o);
          if (p->getConnect1()!=NULL)
              block1 = p->getConnect1()->getLayoutBlock();
          else if (p->getConnect2()!=NULL)
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
      if (p!=NULL) {
          p->removeTrackConnection(o);
          if (p->getConnect1()!=NULL)
              block2 = p->getConnect1()->getLayoutBlock();
          else if (p->getConnect2()!=NULL)
              block2 = p->getConnect2()->getLayoutBlock();
      }
  }
  else {
      block2 = getAffectedBlock(o->getConnect2(),type);
      disconnect(o->getConnect2(),type);
  }
  // delete from array
  for (int i = 0; i<trackList->size();i++) {
      TrackSegment* t = trackList->at(i);
      if (t==o) {
          // found object
          trackList->remove(i);
      }
  }
  // update affected blocks
  if (block!=NULL) {
      // decrement Block use count
      block->decrementUse();
      auxTools->setBlockConnectivityChanged();
      block->updatePaths();
  }
  if ( (block1!=NULL) && (block1!=block) ) block1->updatePaths();
  if ( (block2!=NULL) && (block2!=block) && (block2!=block1) ) block2->updatePaths();
  //
  o->invalidate(editScene);
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
//             JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, NULL,
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
     selectedObject = NULL;
 }
 if (prevSelectedObject == o) {
     prevSelectedObject = NULL;
 }
 // remove connections if any
 for (int j = 0; j < o->getNumberRays(); j++) {
     TrackSegment* t = o->getRayConnectOrdered(j);
     if (t != NULL) {
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
  if (o==NULL) return;
  switch (type) {
      case TURNOUT_A:
          ((LayoutTurnout*)o)->setConnectA(NULL,NONE);
          break;
      case TURNOUT_B:
          ((LayoutTurnout*)o)->setConnectB(NULL,NONE);
          break;
      case TURNOUT_C:
          ((LayoutTurnout*)o)->setConnectC(NULL,NONE);
          break;
      case TURNOUT_D:
          ((LayoutTurnout*)o)->setConnectD(NULL,NONE);
          break;
      case LEVEL_XING_A:
          ((LevelXing*)o)->setConnectA(NULL,NONE);
          break;
      case LEVEL_XING_B:
          ((LevelXing*)o)->setConnectB(NULL,NONE);
          break;
      case LEVEL_XING_C:
          ((LevelXing*)o)->setConnectC(NULL,NONE);
          break;
      case LEVEL_XING_D:
          ((LevelXing*)o)->setConnectD(NULL,NONE);
          break;
      case SLIP_A:
          ((LayoutSlip*)o)->setConnectA(NULL,NONE);
          break;
      case SLIP_B:
          ((LayoutSlip*)o)->setConnectB(NULL,NONE);
          break;
      case SLIP_C:
          ((LayoutSlip*)o)->setConnectC(NULL,NONE);
          break;
      case SLIP_D:
          ((LayoutSlip*)o)->setConnectD(NULL,NONE);
          break;
      default:
#if 1 // TODO:
          if (type>=TURNTABLE_RAY_OFFSET) {
              ((LayoutTurntable*)o)->setRayConnect(NULL,type-TURNTABLE_RAY_OFFSET);
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
  double x = s->getX();
  double y = s->getY();
  double w = s->maxWidth();
  double h = s->maxHeight();
  QRectF r =  QRectF(x ,y ,w ,h);
  if(s->getItem() == NULL)
   return NULL;
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
 return NULL;
}

/*private*/ SignalMastIcon* LayoutEditor::checkSignalMastIcons(QPointF loc) {
 // check signal head images, if any
 for (int i=signalMastImage->size()-1; i>=0; i--) {
     SignalMastIcon* s = signalMastImage->at(i);
     double x = s->getX();
     double y = s->getY();
     double w = s->maxWidth();
     double h = s->maxHeight();
     QRectF r = QRectF(x ,y ,w ,h);
     // Test this detection rectangle
     if (r.contains(loc)) {
         // mouse was pressed in signal head image
         return s;
     }
 }
 return NULL;
}
#endif
/*private*/ PositionableLabel* LayoutEditor::checkLabelImages(QPointF loc)
{
 PositionableLabel* l =NULL;
 int level = 0;
 for (int i=_contents->size()-1; i>=0; i--)
 {
  PositionableLabel* s = (PositionableLabel*)_contents->at(i);
  double x = s->getX();
  double y = s->getY();
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
   if(s->getItem() != NULL)
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
     return NULL;
 }
MemoryIcon* LayoutEditor::checkMemoryMarkerIcons(QPointF loc)
{
 MemoryIcon* l =NULL;
 int level = 0;
 for (int i=memoryLabelList->size()-1; i>=0; i--)
 {
  MemoryIcon* s = memoryLabelList->at(i);
  double x = s->getX();
  double y = s->getY();
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
     if(s->getItem() != NULL)
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
  l->setPopupUtility(NULL);        // no text
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
     QString tName = ui->edSignalHeadIcon->text().trimmed();
     SignalHead* mHead = NULL;
     if ( (tName!=("")) ) {
         mHead = ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getSignalHead(tName);
         /*if (mHead == NULL)
             mHead = InstanceManager.signalHeadManagerInstance().getByUserName(tName);
         else */
         ui->edSignalHeadIcon->setText(tName);
     }
     if (mHead == NULL) {
         // There is no signal head corresponding to this name
//         JOptionPane.showMessageDialog(thisPanel,
//                 java.text.MessageFormat.format(rb.getQString("Error9"),
//                 new Object[]{tName}),
//                 rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
             QMessageBox::critical(this, tr("Error"),tr("Error - Cannot create a signal head icon because there is no signal head defined for - \"%1\". Please enter the name of a Signal Head in\nthe Signal Table and try again.").arg(tName) );
         return;
     }
     // create and set up signal icon
     SignalHeadIcon* l = new SignalHeadIcon(this);
     l->setSignalHead(tName);
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
     putItem((Positionable*)l);
     l->updateSize();
     l->setDisplayLevel(SIGNALS);
 }

 SignalHead* LayoutEditor::getSignalHead(QString name) {
     SignalHead* sh = InstanceManager::signalHeadManagerInstance()->getBySystemName(name);
     if (sh == NULL) sh = InstanceManager::signalHeadManagerInstance()->getByUserName(name);
     if (sh == NULL) log.warn("did not find a SignalHead named "+name);
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
    SignalHeadIcon* h = NULL;
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

        if (h != NULL) {
            h->remove();
            h->dispose();
        }
        setDirty(true);
        repaint();
    }
}   //removeSignalHead

 void LayoutEditor::addSignalMast() {
     // check for valid signal head entry
     QString tName = ui->edSignalMastIcon->text().trimmed();
     SignalMast* mMast = NULL;
     if ( (tName!=("")) ) {
         mMast = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(tName);
         ui->edSignalMastIcon->setText(tName);
     }
     if (mMast == NULL) {
         // There is no signal head corresponding to this name
//         JOptionPane.showMessageDialog(thisPanel,
//                 java.text.MessageFormat.format(rb.getQString("Error9"),
//                 new Object[]{tName}),
//                 rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
             QMessageBox::critical(0, tr("Error"),tr("Error - Cannot create a signal mast icon because there is no signal mast defined for - \"%1\". Please enter the name of a Signal mast in                                              the Signal Table and try again.").arg(tName) );
         return;
     }
     // create and set up signal icon
     SignalMastIcon* l = new SignalMastIcon(this);
     l->setSignalMast(tName);
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
     if (sh == NULL) sh = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName(name);
     if (sh == NULL) log.warn("did not find a SignalMast named "+name);
     return sh;
 }
/**
* Add a label to the Draw Panel
*/
void LayoutEditor::addLabel()
{
 PositionableLabel* l = addLabel(ui->edTextLabel->text().trimmed());
 setDirty(true);
 l->setForeground(defaultTextColor);
 l->setLocation(dLoc.x(),dLoc.y());
}

/*protected*/ PositionableLabel* LayoutEditor::addLabel(QString text)
{
 PositionableLabel* l = new PositionableLabel(text, this);
 l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
 l->setDisplayLevel(LABELS);
 setNextLocation(l);
 putItem((Positionable*)l);
 return l;
}
/**
* Set object location and size for icon and label object as it is created.
* Size comes from the preferredSize; location comes
* from the fields where the user can spec it.
*/
/*protected*/ void LayoutEditor::setNextLocation(PositionableLabel* obj) {
  obj->setLocation(xLoc,yLoc);
}
/*public*/ void LayoutEditor::putItem(Positionable* l)
{
  Editor::putItem(l);
  if (qobject_cast<SensorIcon*>(l)!= NULL)
  {
   sensorImage->append((SensorIcon*)l);
   sensorList->append((SensorIcon*)l);
  }
  else if (qobject_cast<LocoIcon*>(l)!= NULL)
  {
   markerImage->append((LocoIcon*)l);
  }
  else if (qobject_cast<SignalHeadIcon*>(l)!=NULL)
  {
      signalHeadImage->append((SignalHeadIcon*)l);
      signalList->append((SignalHeadIcon*)l);
  }
  else if (qobject_cast<SignalMastIcon*>(l)!=NULL)
  {
      signalMastImage->append((SignalMastIcon*)l);
      signalMastList->append((SignalMastIcon*)l);
  }
  else
   //if (l instanceof MemoryIcon*)
  if(qobject_cast<MemoryIcon*>(l)!= NULL)
  {
   memoryLabelList->append((MemoryIcon*)l);
  }
  else if (qobject_cast<AnalogClock2Display*>(l)!=NULL)
  {
   clocks->append((AnalogClock2Display*)l);
  }
  else if (qobject_cast<MultiSensorIcon*>(l) != NULL)
  {
   multiSensors->append((MultiSensorIcon*)l);
  }
  else
  //if (l instanceof PositionableLabel*)
  if(qobject_cast<PositionableLabel*>(l)!= NULL)
  {
   if ( !(((PositionableLabel*)l)->isBackground()) )
  {
   _labelImage->append((PositionableLabel*)l);
  }
  else
  {
   backgroundImage->append((PositionableLabel*)l);
  }
 }
}

///*public*/ void MyLayoutEditor::super_putItem(Positionable* l)
//  {
//   PositionableLabel* pl = qobject_cast<PositionableLabel*>(l);
//  //l->invalidate();
//  pl->setPositionable(true);
//  //pl->setVisible(true);

//  if (pl->getTooltip().isEmpty())
//  {
//   pl->setTooltip(_defaultToolTip);
//   //pl->setTooltip();
//  }
//  addToTarget(l);
////  if (!_contents->append((Positionable*)l))
////  {
////      log.error("Unable to add "+l->getNameString()+" to _contents");
////  }
//  _contents->append(l);
//  /*if (_debug)*/ log.debug(tr("putItem ")+pl->getNameString()+" to _contents. level= "+QString("%1").arg(pl->getDisplayLevel()));
//}

#if 0
/*protected*/ void MyLayoutEditor::addToTarget(Positionable* l)
{
//  JComponent c = (JComponent)l;
//  c.invalidate();
//  _targetPanel.remove(c);
//  _targetPanel.add(c, Integer.valueOf(l.getDisplayLevel()));
//  _targetPanel.moveToFront(c);
//  c.repaint();
//  _targetPanel.validate();

// this is trial code to see if it works.
 PositionableLabel* pl = qobject_cast<PositionableLabel*> (l);
 if(pl != NULL)
 {
  if(pl->item != NULL)
  {
   Q_ASSERT(pl->item->scene()!=0);
   editScene->removeItem(pl->item);
   pl->item = NULL;
  }
  if(pl->isIcon())
  {
   pl->item = new QGraphicsPixmapItem(QPixmap::fromImage(pl->getIcon()->getOriginalImage()));
   editScene->addItem(pl->item);
   pl->item->setPos(pl->getLocation());
   pl->item->setToolTip(pl->getTooltip());
  }
  else
  {
   pl->item = new QGraphicsTextItem(pl->getUnRotatedText());
   editScene->addItem(pl->item);
   pl->item->setPos(pl->getLocation());
   pl->item->setToolTip(pl->getTooltip());
  }
  if(pl->getDegrees() != 0)
   //pl->item->rotate(pl->getDegrees());
   pl->item->setRotation(pl->item->rotation()+ pl->getDegrees());

 }
}
#endif
///*public*/ bool MyLayoutEditor::removeFromContents(Positionable* l)
//{
// return remove(l);
//}
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
#if 1
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
//  for (int i = 0; i<multiSensors.size();i++) {
//      if (s == multiSensors.get(i)) {
//          multiSensors.remove(i);
//          found = true;
//          break;
//      }
//  }
  for (int i = 0; i<clocks->size();i++) {
      if (s == clocks->at(i)) {
          clocks->remove(i);
          found = true;
          break;
      }
  }
  for (int i = 0; i<signalMastImage->size();i++) {
      if (s == signalMastImage->at(i)) {
          signalMastImage->remove(i);
          found = true;
          break;
      }
  }
  for (int i = 0; i<signalHeadImage->size();i++) {
      if (s == signalHeadImage->at(i)) {
          signalHeadImage->remove(i);
          found = true;
          break;
      }
  }
#endif
  for (int i = 0; i<_labelImage->size(); i++)
  {
   if (s == _labelImage->at(i))
   {
    _labelImage->remove(i);
    found = true;
    break;
   }
  }
  //this->removeFromContents((Positionable*)s);
  int index = _contents->indexOf((Positionable*)s);
  if(index >= 0)
   _contents->remove(index);
  else
   Logger::error(tr("Unable to remove Positionable from contents"));
  if (found)
  {
   setDirty(true);
   //repaint();
   paintTargetPanel(editScene);
  }
  return found;
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
  SensorIcon* s = qobject_cast<SensorIcon*>(sensorImage->at(i));
  if(s == NULL)
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
 return NULL;
}
/**
* Add a sensor indicator to the Draw Panel
*/
void LayoutEditor::addSensor()
{
  if (ui->edSensorIcon->text().trimmed().length()<=0)
  {
//      JOptionPane.showMessageDialog(this,rb.getQString("Error10"),
//                  rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(0, "Error", "Sensor name must be specified!");
   return;
  }
  addSensor(ui->edSensorIcon->text().trimmed());
 }
void LayoutEditor::addSensor(QString name)
{
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
  if (l->getSensor() != NULL)
  {
   if ( (l->getNamedSensor()->getName()==NULL) || (!(l->getNamedSensor()->getName()==(ui->edSensorIcon->text().trimmed()))) )
    ui->edSensorIcon->setText(l->getNamedSensor()->getName());
  }
  NamedBeanHandle<Sensor*>* s = l->getNamedSensor();
  QString sensorName = "";
  if(s != NULL)
   sensorName = s->getName();
  ui->edSensorIcon->setText(sensorName);
  if(l->getNamedBean() != NULL)
   l->setTooltip(l->getNamedBean()->getSystemName());
  setNextLocation(l);
  setDirty(true);
  putItem((Positionable*)l);
}

/*public*/ void LayoutEditor::putSensor(SensorIcon* l){
  putItem((Positionable*)l);
  l->updateSize();
  l->setDisplayLevel(SENSORS);
}
///**
//* Display the X & Y coordinates of the Positionable item and provide a
//* dialog memu item to edit them.
//*/
///*public*/ bool MyLayoutEditor::setShowCoordinatesMenu(Positionable* p, QMenu* popup)
//{
// if (showCoordinates())
// {
//  QMenu* edit = new QMenu(tr("Edit Location"));
//  if ((/*p instanceof MemoryIcon*/qobject_cast<MemoryIcon*>(p)!= NULL) && (((MemoryIcon*)p)->getPopupUtility()->getFixedWidth()==0))
//  {
//   MemoryIcon* pm = (MemoryIcon*) p;
//   edit->addAction(new QAction("x= " + QString("%1").arg(pm->getOriginalX()),this));
//   edit->addAction(new QAction("y= " + QString("%1").arg(pm->getOriginalY()),this));

//   edit->addAction(((MemoryIconCoordinateEdit*) pm->cEdit)->getCoordinateEditAction(pm,this));
//  }
//  else
//  {
////   SensorIcon* ps;
////   if((ps = qobject_cast<SensorIcon*>(p))!= NULL)
//   PositionableLabel* ps;
//   if((ps = qobject_cast<PositionableLabel*>(p))!= NULL)
//   {
//    edit->addMenu(new QMenu("x= " + QString("%1").arg(ps->getX())));
//    edit->addMenu(new QMenu("y= " + QString("%1").arg(ps->getY())));
//    CoordinateEdit* ce = new CoordinateEdit();
//    edit->addAction(CoordinateEdit::getCoordinateEditAction(p,ce));
//   }
//  }
//  popup->addMenu(edit);
//  return true;
// }
// return false;
//}
/* Positionable has set a new level.  Editor must change it in the target panel.
*/
///*public*/ void MyLayoutEditor::displayLevelChange(Positionable* /*l*/){
//  removeFromTarget(l);
//  addToTarget(l);
//}
///*public*/ void MyLayoutEditor::setDisplayLevelMenu(Positionable* p, QMenu* popup)
//{
//  QMenu* edit = new QMenu(tr("Edit Level"));
//  SensorIcon* ps = qobject_cast<SensorIcon*>(p);
//  if(ps != NULL)
//   edit->addAction(new QAction(tr("level= ") + QString("%1").arg(ps->getDisplayLevel()),this));
//  CoordinateEdit* coordinateEdit = new CoordinateEdit();
//  edit->addAction(CoordinateEdit::getLevelEditAction(p, coordinateEdit));
//  popup->addMenu(edit);
//}

///*public*/ void MyLayoutEditor::setPositionableMenu(Positionable* p, QMenu* popup)
//{
// saveP = p;
////  JCheckBoxMenuItem lockItem = new JCheckBoxMenuItem(tr("LockPosition"));
////  lockItem.setSelected(!p.isPositionable());
// QAction* lockItem = new QAction(tr("Lock Position"),this);
// lockItem->setCheckable(true);
// PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
// if(pl != NULL)
//  lockItem->setChecked(!pl->isPositionable());

////  lockItem.addActionListener(new ActionListener(){
////      Positionable comp;
////      JCheckBoxMenuItem checkBox;
////      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
////          comp.setPositionable(!checkBox.isSelected());
////          setSelectionsPositionable(!checkBox.isSelected(), comp);
////      }
////      ActionListener init(Positionable pos, JCheckBoxMenuItem cb) {
////          comp = pos;
////          checkBox = cb;
////          return this;
////      }
////  }.init(p, lockItem));

//  popup->addAction(lockItem);
//  connect(lockItem, SIGNAL(toggled(bool)), this, SLOT(On_lockPosition_triggered(bool)));
//}

//void MyLayoutEditor::On_lockPosition_triggered(bool bChecked)
//{
//   PositionableLabel* pl = qobject_cast<PositionableLabel*>(saveP);
//   if(pl != NULL)
//    pl->setPositionable(!bChecked);
//  SensorIcon* ps = qobject_cast<SensorIcon*>(saveP);
//   if(ps != NULL)
//    ps->setPositionable(!bChecked);
//}

///*public*/ void MyLayoutEditor::setShowCoordinates(bool state)
//{
//  _showCoordinates = state;
//  for (int i = 0; i<_contents->size(); i++)
//  {
//   _contents->at(i)->setViewCoordinates(state);
//  }
//}
///*public*/ bool MyLayoutEditor::showCoordinates()
//{
//  return _showCoordinates;
//}
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
 return NULL;
}
/*protected*/ void LayoutEditor::setSelectionsScale(double s, Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
 Q_ASSERT(pl != NULL);
 if (_selectionGroup!=NULL && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i))->setScale(s);
  }
 }
 else
 {
  pl->setScale(s);
 }
}

/*protected*/ void LayoutEditor::setSelectionsRotation(int k, Positionable* p)
{
  PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
  Q_ASSERT(pl != NULL);
  if (_selectionGroup!=NULL && _selectionGroup->contains(p))
  {
   for (int i=0; i<_selectionGroup->size(); i++)
   {
    ((PositionableLabel*)_selectionGroup->at(i))->rotate(k);
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
 SensorIcon* si = qobject_cast<SensorIcon*>(comp);
 if(si != NULL)
 {
  Q_ASSERT(si->_itemGroup->scene()!=0);
  editScene->removeItem(si->_itemGroup);
  si->_itemGroup = NULL;
  si->remove();
 }
 LocoIcon* li = qobject_cast<LocoIcon*>(comp);
 if(li != NULL)
 {
  Q_ASSERT(li->_itemGroup->scene()!=0);
  editScene->removeItem(li->_itemGroup);
  li->_itemGroup = NULL;
  li->remove();
 }
 MemoryIcon* mi = qobject_cast<MemoryIcon*>(comp);
 if(mi != NULL)
 {
  Q_ASSERT(mi->_itemGroup->scene()!=0);
  editScene->removeItem(mi->_itemGroup);
  mi->_itemGroup = NULL;
  mi->remove();
 }
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(comp);
 if(pl != NULL)
 {
  Q_ASSERT(pl->_itemGroup->scene()!=0);
  editScene->removeItem(pl->_itemGroup);
  pl->_itemGroup = NULL;
  pl->remove();
 }
 removeSelections(comp);
}
/*protected*/ void LayoutEditor::removeSelections(Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
 Q_ASSERT(pl != NULL);

 if (_selectionGroup!=NULL && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i))->remove();
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
   double x = s->getLocation().x();
   double y = s->getLocation().y();
   double w = s->maxWidth();
   double h = s->maxHeight();
   QRectF r = QRectF(x ,y ,w ,h);
 // Test this detection rectangle
 if (r.contains(loc)) {
     // mouse was pressed in multi sensor image
     return s;
 }
}
return NULL;
}
/*private*/ LocoIcon* LayoutEditor::checkMarkers(QPointF loc)
{
 // check marker icons, if any
 for (int i=markerImage->size()-1; i>=0; i--)
 {
      LocoIcon* l = markerImage->at(i);
//      double x = l->getX();
//      double y = l->getY();
      double x = l->getLocation().x();
      double y = l->getLocation().y();
      double w = l->maxWidth();
      double h = l->maxHeight();
      QRectF r = QRectF(x ,y ,w ,h);
      // Test this detection rectangle
      if (r.contains(loc)) {
          // mouse was pressed in marker icon
          return l;
      }
  }
  return NULL;
}
void LayoutEditor::on_actionAdd_loco_triggered()
{
 InputDialog* dlg = new InputDialog("Enter loco id", "0", NULL, this);
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
  l->setTooltip(name);
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
 if (inputFileChooser == NULL)
 {
     inputFileChooser = new JFileChooser(System::getProperty(
                                             "user.dir") + File::separator + "resources" + File::separator +
                                         "icons");
//     FileChooserFilter filt = new jmri.util.FileChooserFilter("Graphics Files");
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
   if ( (il != NULL) && (il->isActive()) )
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
 if (ui->edMemoryLabel->text().trimmed().length()<=0)
 {
//     JOptionPane.showMessageDialog(this, rb.getQString("Error11"),
//                 rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Error"), tr("Memory label text must be entered!"));
  return;
 }
 addMemory(ui->edMemoryLabel->text().trimmed());
}
MemoryIcon* LayoutEditor::addMemory(QString text)
  {
 MemoryIcon* l = new MemoryIcon("<memory>", this);
 l->setMemory(ui->edMemoryLabel->text().trimmed());
 Memory* xMemory = l->getMemory();
 if (xMemory != NULL)
 {
  QString userName = xMemory->getUserName();
  if ( (xMemory->getUserName() == NULL) ||
             (!(xMemory->getUserName()==(text)))  )
  {
   // put the system name in the memory field
   ui->edMemoryLabel->setText(xMemory->getSystemName());
  }
 }
 if(xMemory != NULL)
  l->setTooltip(xMemory->getSystemName());
 setNextLocation(l);
 l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
 l->setDisplayLevel(LABELS);
 l->setForeground(defaultTextColor);
 setDirty(true);
 putItem((Positionable*)l);
 return l;
}
/**
* Add a Reporter Icon to the panel
*/
void LayoutEditor::addReporter(QString textReporter,int xx,int yy) {
  ReporterIcon* l = new ReporterIcon(this);
  l->setReporter(textReporter);
  l->setLocation(xx,yy);
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
/*public*/ void LayoutEditor::setAllControlling(bool state)
{
 _controlLayout = state;
 if (_globalSetsLocal)
 {
  for (int i = 0; i<_contents->size(); i++)
  {
   Positionable* pos = _contents->at(i);
   if(qobject_cast<PositionableLabel*>(pos)!= NULL)
    ((PositionableLabel*)pos)->setControlling(state);
  }
 }
}
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
//          JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
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
  if(_positionableSelection!=NULL)
  {
   for(int i=0; i<_positionableSelection->count(); i++)
   {
    Positionable* comp = _positionableSelection->at(i);
    if(qobject_cast<SensorIcon*>(comp) != NULL)
    {
     SensorIcon* si = qobject_cast<SensorIcon*>(comp);
     Q_ASSERT(si->_itemGroup->scene()!=0);
     editScene->removeItem(si->_itemGroup);
     remove(si);
    }
    else if(qobject_cast<LocoIcon*>(comp) != NULL)
    {
     LocoIcon* li = qobject_cast<LocoIcon*>(comp);
     Q_ASSERT(li->_itemGroup->scene()!=0);
     editScene->removeItem(li->_itemGroup);
     remove(li);
    }
    else if(qobject_cast<MemoryIcon*>(comp) != NULL)
    {
     MemoryIcon*mi = qobject_cast<MemoryIcon*>(comp);
     Q_ASSERT(mi->_itemGroup->scene()!=0);
     editScene->removeItem(mi->_itemGroup);
     remove(mi);
    }
   }
  }
  if(_pointSelection!=NULL)
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

  if(_xingSelection!=NULL)
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
  if(_slipSelection!=NULL){
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
  if(_turntableSelection!=NULL){
      bool oldTurntable = noWarnTurntable;
      noWarnTurntable = true;
      foreach(LayoutTurntable* point, *_turntableSelection){
          removeTurntable(point);
      }
      noWarnTurntable = oldTurntable;
  }
#endif
  if(_turnoutSelection!=NULL)
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
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
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
  if (selectedObject==o) selectedObject = NULL;
  if (prevSelectedObject==o) prevSelectedObject = NULL;
  // remove connections if any
  TrackSegment* t = (TrackSegment*)o->getConnectA();
  if (t!=NULL) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectB();
  if (t!=NULL) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectC();
  if (t!=NULL) removeTrackSegment(t);
  t = (TrackSegment*)o->getConnectD();
  if (t!=NULL) removeTrackSegment(t);
  // decrement Block use count(s)
  LayoutBlock* b = o->getLayoutBlock();
  if (b!=NULL) b->decrementUse();
  if ( (o->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
          (o->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
              (o->getTurnoutType()==LayoutTurnout::LH_XOVER) )
  {
   LayoutBlock* b2 = o->getLayoutBlockB();
   if ( (b2!=NULL) && (b2!=b) ) b2->decrementUse();
   LayoutBlock* b3 = o->getLayoutBlockC();
   if ( (b3!=NULL) && (b3!=b) && (b3!=b2) ) b3->decrementUse();
   LayoutBlock* b4 = o->getLayoutBlockD();
   if ( (b4!=NULL) && (b4!=b) &&
                  (b4!=b2) && (b4!=b3) ) b4->decrementUse();
  }
  // delete from array
  for (int i = 0; i<turnoutList->size();i++)
  {
   LayoutTurnout* lt = turnoutList->at(i);
   if (lt==o)
   {
    // found object
    Q_ASSERT(lt->item->scene()!=0);
    editScene->removeItem(lt->item);
    Q_ASSERT(lt->rects->scene()!=0);
    editScene->removeItem(lt->rects);
    turnoutList->remove(i);
    setDirty(true);
    //repaint();
    return(true);
   }
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
 if(qobject_cast<LayoutSlip*>(o)==NULL)
 {
     return false;
 }
 // First verify with the user that this is really wanted
 if (!noWarnSlip)
 {
//     int selectedValue = JOptionPane.showOptionDialog(this,
//             rb.getQString("Question5"),rb.getQString("WarningTitle"),
//             JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
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
 if (selectedObject==o) selectedObject = NULL;
 if (prevSelectedObject==o) prevSelectedObject = NULL;
 // remove connections if any
 TrackSegment* t = (TrackSegment*)o->getConnectA();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectB();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectC();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectD();
 if (t!=NULL) removeTrackSegment(t);
 // decrement block use count if any blocks in use
 LayoutBlock* lb = o->getLayoutBlock();
 if (lb != NULL) lb->decrementUse();

 // delete from array
 for (int i = 0; i<slipList->size();i++)
 {
  LayoutSlip* lx = slipList->at(i);
  if (lx==o)
  {
   // found object
   slipList->remove(i);
   o->remove();
   setDirty(true);
   repaint();
   return(true);
  }
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
//              JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
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
 if (selectedObject==o) selectedObject = NULL;
 if (prevSelectedObject==o) prevSelectedObject = NULL;
 // remove connections if any
 TrackSegment* t = (TrackSegment*)o->getConnectA();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectB();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectC();
 if (t!=NULL) removeTrackSegment(t);
 t = (TrackSegment*)o->getConnectD();
 if (t!=NULL) removeTrackSegment(t);
  // decrement block use count if any blocks in use
 LayoutBlock* lb = o->getLayoutBlockAC();
 if (lb != NULL) lb->decrementUse();
 LayoutBlock* lbx = o->getLayoutBlockBD();
 if (lbx!=NULL && lb!=NULL && lbx!=lb) lb->decrementUse();
 // delete from array
 for (int i = 0; i<xingList->size();i++)
 {
  LevelXing* lx = xingList->at(i);
  if (lx==o)
  {
   // found object
   Q_ASSERT(lx->item->scene()!=0);
   editScene->removeItem(lx->item);
   Q_ASSERT(lx->rects->scene()!=0);
   editScene->removeItem(lx->rects);
   xingList->remove(i);
   o->invalidate(editScene);
   o->remove();
   setDirty(true);
   //repaint();
   return(true);
  }
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
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
 Q_ASSERT(pl != NULL);
//  if (p.getDisplayLevel() == BKG || p instanceof PositionableShape) {
//      return;
//  }
//  JCheckBoxMenuItem hideItem = new JCheckBoxMenuItem(tr("SetHidden"));
//  hideItem.setSelected(p->isHidden());
//  hideItem.addActionListener(new ActionListener(){
//      Positionable comp;
//      JCheckBoxMenuItem checkBox;
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          comp.setHidden(checkBox.isSelected());
//          setSelectionsHidden(checkBox.isSelected(), comp);
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
  hiddenAction->setChecked(pl->isHidden());
  connect(hiddenAction, SIGNAL(toggled(bool)), this, SLOT(On_actionHidden_toggled(bool)));
  popup->addAction(hiddenAction);
  saveP = p;
}
void LayoutEditor::On_actionHidden_toggled(bool bState)
{
 Positionable* comp =saveP;
 //comp.setHidden(checkBox.isSelected());
 setSelectionsHidden(bState, comp);
}
/*protected*/ void LayoutEditor::setSelectionsHidden(bool enabled, Positionable* p)
{
 PositionableLabel* pl = qobject_cast<PositionableLabel*>(p);
 Q_ASSERT(pl != NULL);
 if (_selectionGroup!=NULL && _selectionGroup->contains(p))
 {
  for (int i=0; i<_selectionGroup->size(); i++)
  {
   ((PositionableLabel*)_selectionGroup->at(i))->setHidden(enabled);
  }
 }
}
void LayoutEditor::on_actionEdit_track_width_triggered()
{
 SetTrackWidthDlg dlg(sideTrackWidth, mainlineTrackWidth, this);
 if(dlg.exec() == QDialog::Accepted)
 {
  sideTrackWidth = dlg.sidetrackWidth();
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
    QAction* r = new QAction(getColourIcon(color),name);
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
//                LayoutTrack.setDefaultTrackColor(desiredColor);
//                defaultTrackColor = desiredColor;
//                setDirty(true);
//                repaint();
//            }
//        }   //actionPerformed
//    };
    //JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
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
   if (qobject_cast<PositionableLabel*>(p)!= NULL)
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
#endif
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
  ui->actionSave->setEnabled(true);
  ui->actionSave_as->setEnabled(true);
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
 bool bResult = ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->load(new File(QDir::homePath() + "/.jmri/mylayout.xml"));
 layoutFile = QDir::homePath() + "/.jmri/mylayout.xml";
 setCursor(Qt::ArrowCursor);
 ui->actionSave->setEnabled(true);
 ui->actionSave_as->setEnabled(true);
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
#if 1
void LayoutEditor::on_actionSave_triggered()
{
 if(layoutFile.isEmpty())
 {
  on_actionSave_as_triggered();
 }
 setCursor(Qt::WaitCursor);
 makeBackupFile(layoutFile);

// SaveXml saveXml(this);
// saveXml.store(layoutFile);
 try
 {
 bool results = ((JmriConfigurationManager*)InstanceManager::getNullableDefault("JmriConfigurationManager"))->storeUser(new File(layoutFile));
 } catch (NullPointerException ex)
 {}
 setCursor(Qt::ArrowCursor);
}

void LayoutEditor::on_actionSave_as_triggered()
{
 QString path = QFileDialog::getSaveFileName(this,tr("Save file as"),layoutFile);
 if(path.isEmpty()) 
 {
  QMessageBox::warning(this, tr("Warning"), tr("No file name specified"));
  return;
 }
 setCursor(Qt::WaitCursor);
 SaveXml saveXml(this);  // TODO: get rid of this; use Jmri code to save
 saveXml.store(path);
 layoutFile = path;
 setCursor(Qt::ArrowCursor);

}
#endif
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
 editPanel->scale(scaleX, scaleY);
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
 turnoutList->clear();
 trackList->clear();
 pointList->clear();
 xingList->clear();
 slipList->clear();
 //turntableList->clear();
 highlightRect = NULL;
 panelGridGroup = NULL;
 ui->actionLoad_Other_XML->setEnabled(true);
 ui->actionLoad_XML->setEnabled(true);
 ui->actionSave->setEnabled(false);
 ui->actionSave_as->setEnabled(false);
 InstanceManager::setLayoutBlockManager(new LayoutBlockManager());
}
/*public*/ void LayoutEditor::loadFailed() {
 _loadFailed = true;
}
/**
*
*/
/*public*/ NamedIcon* LayoutEditor::loadFailed(QString /*msg*/, QString url) {
 if (_debug) log.debug("loadFailed _ignore= "+_ignore);
 QString goodUrl = _urlMap->value(url);
 if (goodUrl!=NULL) {
     return NamedIcon::getIconByName(goodUrl);
 }
 if (_ignore) {
     _loadFailed = true;
     return new NamedIcon(url, url);
 }
 _newIcon = NULL;
 _delete = false;
 // TODO: new UrlErrorDialog(msg, url);

 if (_delete) {
     if (_debug) log.debug("loadFailed _delete= "+_delete);
     return NULL;
 }
 if (_newIcon==NULL) {
     _loadFailed = true;
     _newIcon =new NamedIcon(url, url);
 }
 if (_debug) log.debug("loadFailed icon NULL= "+(_newIcon==NULL));
 return _newIcon;
}

void LayoutEditor::on_actionAdd_loco_from_roster_triggered()
{
 locoMarkerFromRoster();
}

void LayoutEditor::on_menuWindow_aboutToShow()
{
 ui->menuWindow->clear();
 PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
}

int LayoutEditor::getTurnoutType(QString name)
{
 foreach (LayoutTurnout* t, *turnoutList)
  {
   if(t->getTurnoutName() == name)
   return t->getTurnoutType();
 }
 foreach (LayoutSlip* s, *slipList)
 {
  if(s->getName() == name)
  return s->getTurnoutType();
 }
 return -1;
}
 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByEastBoundSignal(QString signalName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getEastBoundSignal()==(signalName))
             return p;
     }
     return NULL;
 }

 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSignal(QString signalName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getWestBoundSignal()==(signalName))
             return p;
     }
     return NULL;
 }

 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByEastBoundSignalMast(QString signalMastName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getEastBoundSignalMast()==(signalMastName))
             return p;
     }
     return NULL;
 }

 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSignalMast(QString signalMastName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getWestBoundSignalMast()==(signalMastName))
             return p;

     }
     return NULL;
 }
 /*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutBySignalMast(QString signalMastName){
     for(int i = 0; i<turnoutList->size(); i++){
         LayoutTurnout* t = turnoutList->at(i);
         if((t->getSignalAMast()==(signalMastName)) ||
             (t->getSignalBMast()==(signalMastName)) ||
             (t->getSignalCMast()==(signalMastName)) ||
             (t->getSignalDMast()==(signalMastName)))
             return t;
     }
     return NULL;
 }
 /*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutBySensor(QString sensorName){
     for(int i = 0; i<turnoutList->size(); i++){
         LayoutTurnout* t = turnoutList->at(i);
         if((t->getSensorA()==(sensorName)) ||
             (t->getSensorB()==(sensorName)) ||
             (t->getSensorC()==(sensorName)) ||
             (t->getSensorD()==(sensorName)))
             return t;
     }
     return NULL;
 }

 /*public*/ LevelXing* LayoutEditor::findLevelXingBySignalMast(QString signalMastName){
     for(int i = 0; i<xingList->size(); i++){
         LevelXing* l = xingList->at(i);
         if((l->getSignalAMastName()==(signalMastName)) ||
             (l->getSignalBMastName()==(signalMastName)) ||
             (l->getSignalCMastName()==(signalMastName)) ||
             (l->getSignalDMastName()==(signalMastName)))
             return l;
     }
     return NULL;
 }

 /*public*/ LevelXing* LayoutEditor::findLevelXingBySensor(QString sensorName){
     for(int i = 0; i<xingList->size(); i++){
         LevelXing* l = xingList->at(i);
         if((l->getSensorAName()==(sensorName)) ||
             (l->getSensorBName()==(sensorName)) ||
             (l->getSensorCName()==(sensorName)) ||
             (l->getSensorDName()==(sensorName)))
             return l;
     }
     return NULL;
 }

 /*public*/ LayoutSlip* LayoutEditor::findLayoutSlipBySignalMast(QString signalMastName)
  {
  foreach(LayoutSlip* l, *slipList)
  {
   if((l->getSignalAMast()==(signalMastName)) ||
       (l->getSignalBMast()==(signalMastName)) ||
       (l->getSignalCMast()==(signalMastName)) ||
       (l->getSignalDMast()==(signalMastName)))
    return l;
  }
  return NULL;
 }

 /*public*/ LayoutSlip* LayoutEditor::findLayoutSlipBySensor(QString sensorName){
     foreach(LayoutSlip* l, *slipList){
         if((l->getSensorA()==(sensorName)) ||
             (l->getSensorB()==(sensorName)) ||
             (l->getSensorC()==(sensorName)) ||
             (l->getSensorD()==(sensorName)))
             return l;
     }
     return NULL;
 }
 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByEastBoundSensor(QString sensorName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getEastBoundSensor()==sensorName)
             return p;
     }
     return NULL;
 }

 /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSensor(QString sensorName){
     for (int i = 0; i<pointList->size(); i++) {
         PositionablePoint* p = pointList->at(i);
         if (p->getWestBoundSensor()==(sensorName))
             return p;

     }
     return NULL;
 }
 void LayoutEditor::on_actionSkip_unsignalled_Internal_Turnouts_toggled(bool bState)
 {
  skipIncludedTurnout = bState;
 }

 void LayoutEditor::on_actionSet_Signals_at_Block_Boundary_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtBlockBoundary(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Turnout_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Crossover_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtXoverTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Level_Crossing_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtLevelXing(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Slip_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtSlip(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Throat_to_Throat_Turnouts_triggered()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAtTToTTurnouts(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionSet_Signals_at_Three_Way_Turnout()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(this);
  }
  tools->setSignalsAt3WayTurnout(signalIconEditor, signalFrame);
 }

 void LayoutEditor::on_actionEntry_Exit_triggered()
 {
  if (tools == NULL)
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
     if (conTools == NULL) {
         conTools = new ConnectivityUtil(/*thisPanel*/this);
     }
     if (conTools==NULL) log.error("Unable to establish link to Connectivity Tools for Layout Editor panel "+layoutName);
     return conTools;
 }
 /*public*/ LayoutEditorTools* LayoutEditor::getLETools() {
     if (tools == NULL) {
         tools = new LayoutEditorTools(/*thisPanel*/this);
     }
     if (tools==NULL) log.error("Unable to establish link to Layout Editor Tools for Layout Editor panel "+layoutName);
     return tools;
 }
/*public*/ void LayoutEditor::addToPopUpMenu(NamedBean* nb, QMenu* item, int menu)
{
 if(nb==NULL || item==NULL){
     return;
 }
 //if(nb instanceof Sensor)
 if(qobject_cast<Sensor*>(nb)!=NULL)
 {
     foreach(SensorIcon* si, *sensorList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=NULL){
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
  if(qobject_cast<SignalHead*>(nb)!=NULL)
  {
     foreach(SignalHeadIcon* si, *signalList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=NULL){
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
 if(qobject_cast<SignalMast*>(nb)!=NULL)
  {
     foreach(SignalMastIcon* si,*signalMastList){
         if(si->getNamedBean()==nb && si->getPopupUtility()!=NULL){
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
 if(qobject_cast<Memory*>(nb)!=NULL)
 {
  foreach(MemoryIcon* si, *memoryLabelList)
  {
   if(si->getNamedBean()==nb && si->getPopupUtility()!=NULL)
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
 if(qobject_cast<Turnout*>(nb)!=NULL)
 {
  foreach(LayoutTurnout* ti, *turnoutList)
  {
   if(ti->getTurnout()==(nb))
   {
    switch(menu)
    {
     case VIEWPOPUPONLY : ti->addViewPopUpMenu(item); break;
     case EDITPOPUPONLY : ti->addEditPopUpMenu(item); break;
     default: ti->addEditPopUpMenu(item);
              ti->addViewPopUpMenu(item);
    }
    break;
   }
  }
  foreach(LayoutSlip* ls, *slipList)
  {
   if(ls->getTurnout()==nb||ls->getTurnoutB()==nb)
   {
    switch(menu)
    {
     case VIEWPOPUPONLY : ls->addViewPopUpMenu(item); break;
     case EDITPOPUPONLY : ls->addEditPopUpMenu(item); break;
     default: ls->addEditPopUpMenu(item);
              ls->addViewPopUpMenu(item);
    }
    break;
   }
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
 if (multiSensorFrame == NULL) {
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
 l->setLocation(multiLocX,multiLocY);
 setDirty(true);
 putItem((Positionable*)l);
 //multiSensorFrame = NULL;
}
void LayoutEditor::on_btnChange_clicked()
{

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
 if (file == NULL)
 {
  log.info("No " + name + " file to backup");
 }
 else
 {
  QFileInfo info(file->fileName());

  QString backupName = xmlfile->backupFileName(info.absoluteFilePath());
  QFile* backupFile = xmlfile->findFile(backupName);
  if (backupFile != NULL)
  {
   if (backupFile->remove())
   {
    log.debug("deleted backup file " + backupName);
   }
  }
  if (file->rename(backupName))
  {
   log.debug("created new backup file " + backupName);
  }
  else
  {
   log.error("could not create backup file " + backupName);
  }
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
 panelHeight = (int) (dimF.height() / getPaintScale());
 panelWidth = (int) (dimF.width() / getPaintScale());
 QPoint pt = getLocationOnScreen();
 upperLeftX = pt.x();
 upperLeftY = pt.y();

 UserPreferencesManager* prefsMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if(prefsMgr != NULL)
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
    log.error("setWindowLocation failure.");
   }
   QSize prefsWindowSize = prefsMgr->getWindowSize(windowFrameRef);

   if ((prefsWindowSize.width() != windowWidth) || (prefsWindowSize.height() != windowHeight)) {
       log.error("setWindowSize failure.");
   }
  }

  //we're going to use this instead
  if (true)
  { //(Nope, it's not working ether)
    //save it in the user preferences for the window
   QRectF windowRectangle2D =  QRectF(upperLeftX, upperLeftY, windowWidth, windowHeight);
   prefsMgr->setProperty(windowFrameRef, "windowRectangle2D", windowRectangle2D);
   QVariant prefsProp = prefsMgr->getProperty(windowFrameRef, "windowRectangle2D");
   log.info(tr("testing prefsProp: ") + prefsProp.toString());
  }
 } //);

 log.debug("setCurrentPositionAndSize Position - " + QString::number(upperLeftX) + "," + QString::number(upperLeftY) + " WindowSize - " + QString::number(windowWidth) + "," + QString::number(windowHeight) + " PanelSize - " + QString::number(panelWidth) + "," + QString::number(panelHeight));
 setDirty(true);
}

/*public*/ bool LayoutEditor::getOpenDispatcherOnLoad() {
    return openDispatcherOnLoad;
}

/*public*/ void LayoutEditor::setOpenDispatcherOnLoad(bool boo) {
    openDispatcherOnLoad = boo;
}
/*public*/ void LayoutEditor::setDirectTurnoutControl(bool boo) {
    useDirectTurnoutControl = boo;
// TODO:     useDirectTurnoutControlItem.setSelected(useDirectTurnoutControl);

}

/*public*/ bool LayoutEditor::getDirectTurnoutControl() {
    return useDirectTurnoutControl;
}

/*public*/ void LayoutEditor::setLayoutDimensions(int windowW, int windowH, int x, int y, int panelW, int panelH) {
    upperLeftX = x;
    upperLeftY = y;
    windowWidth = windowW;
    windowHeight = windowH;
    panelWidth = panelW;
    panelHeight = panelH;
    setTargetPanelSize(panelWidth, panelHeight);
    setLocation(upperLeftX, upperLeftY);
    setSize(windowWidth, windowHeight);
    log.debug(
        "setLayoutDimensions Position - " + QString::number(upperLeftX) + "," + QString::number(upperLeftY) + " windowSize - " + QString::number(windowWidth) + "," + QString::number(windowHeight) + " panelSize - " + QString::number(panelWidth) + "," +
        QString::number(panelHeight));
}   //setLayoutDimensions

/*public*/ void LayoutEditor::setMainlineTrackWidth(int w) {
    mainlineTrackWidth = w;
}

/*public*/ void LayoutEditor::setSideTrackWidth(int w) {
    sideTrackWidth = w;
}
/*public*/ void LayoutEditor::setDefaultTrackColor(QString color) {
    defaultTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}

/*public*/ void LayoutEditor::setDefaultOccupiedTrackColor(QString color) {
    defaultOccupiedTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}

/*public*/ void LayoutEditor::setDefaultAlternativeTrackColor(QString color) {
    defaultAlternativeTrackColor = ColorUtil::stringToColor(color);
    setOptionMenuTrackColor();
}

/*public*/ void LayoutEditor::setTurnoutCircleColor(QString color)
{
 turnoutCircleColor = ColorUtil::stringToColor(color);
 setOptionMenuTurnoutCircleColor();
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
  turnoutDrawUnselectedLegItem->setChecked(turnoutDrawUnselectedLeg);
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
  //showGridItem.setSelected(drawGrid);
  ui->actionShow_grid_in_edit_mode->setChecked(drawGrid);
  on_actionShow_grid_in_edit_mode_toggled(state);
 }
}
/*public*/ void LayoutEditor::setSnapOnAdd(bool state)
{
 if (snapToGridOnAdd != state)
 {
  snapToGridOnAdd = state;
  //snapToGridOnAddItem.setSelected(snapToGridOnAdd);
  ui->actionSnap_to_grid_when_adding->setChecked(snapToGridOnAdd);
  on_actionSnap_to_grid_when_adding_toggled(state);
 }
}

/*public*/ void LayoutEditor::setSnapOnMove(bool state)
{
 if (snapToGridOnMove != state)
 {
  snapToGridOnMove = state;
  //snapToGridOnMoveItem.setSelected(snapToGridOnMove);
  ui->actionSnap_to_grid_when_moving->setChecked(snapToGridOnMove);
  on_actionSnap_to_grid_when_moving_toggled(state);
 }
}

/*public*/ void LayoutEditor::setAntialiasingOn(bool state)
{
 if (antialiasingOn != state)
 {
  antialiasingOn = state;
  //antialiasingOnItem.setSelected(antialiasingOn);
  ui->actionEnable_antialiasing_smoother_lines->setChecked(antialiasingOn);
  on_actionEnable_antialiasing_smoother_lines_toggled(state);
 }
}

/*public*/ void LayoutEditor::setTurnoutCircles(bool state)
{
 if (turnoutCirclesWithoutEditMode != state)
 {
  turnoutCirclesWithoutEditMode = state;
  //turnoutCirclesOnItem.setSelected(turnoutCirclesWithoutEditMode);
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
   if (finder->findLayoutTurntableByName(name) == NULL)
   {
    duplicate = false;
   }
   if (duplicate)
   {
    numLayoutTurntables++;
   }
 }
 LayoutTurntable* x = new LayoutTurntable(name, pt, this);
 //if (x != NULL) {
 turntableList->append(x);
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
 // initialize TrackSegments if any
 if (trackList->size() > 0)
  {
   for (int i = 0; i < trackList->size(); i++)
  {
   (trackList->at(i))->setObjects(this);
  }
 }
 // initialize PositionablePoints if any
 if (pointList->size() > 0)
  {
   for (int i = 0; i < pointList->size(); i++)
  {
   (pointList->at(i))->setObjects(this);
  }
 }
 // initialize LevelXings if any
 if (xingList->size() > 0)
 {
  for (int i = 0; i < xingList->size(); i++)
  {
   (xingList->at(i))->setObjects(this);
  }
 }
 // initialize LevelXings if any
 if (slipList->size() > 0)
  {
   foreach (LayoutSlip* l,  *slipList)
  {
   l->setObjects(this);
  }
 }
 // initialize LayoutTurntables if any
 if (turntableList->size() > 0)
  {
   for (int i = 0; i < turntableList->size(); i++)
  {
   (turntableList->at(i))->setObjects(this);
  }
 }
 // initialize LayoutTurnouts if any
 if (turnoutList->size() > 0)
  {
   for (int i = 0; i < turnoutList->size(); i++)

  {
   (turnoutList->at(i))->setObjects(this);
  }
 }
 auxTools->initializeBlockConnectivity();
 log.debug("Initializing Block Connectivity for " + layoutName);
 // reset the panel changed bit
 resetDirty();
}
void LayoutEditor::on_actionMoveLayout_triggered()
{
 JDialog* dlg = new JDialog();
 dlg->setTitle(tr("Move layout"));
 QVBoxLayout* dlgLayout = new QVBoxLayout(dlg);
 QHBoxLayout* hLayout = new QHBoxLayout;
 QLabel* xLabel = new QLabel(tr("X offset"));
 hLayout->addWidget(xLabel);
 xMove = new JTextField(4);
 xMove->setValidator(new QIntValidator(-100, +100));
 hLayout->addWidget(xMove);
 QLabel* yLabel = new QLabel(tr("X offset"));
 hLayout->addWidget(yLabel);
 yMove = new JTextField(4);
 yMove->setValidator(new QIntValidator(-100, +100));
 hLayout->addWidget(yMove);
 dlgLayout->addLayout(hLayout);
 QPushButton* ok = new QPushButton(tr("Move"));
 FlowLayout* buttonLayout = new FlowLayout();
 buttonLayout->addWidget(ok);
 dlgLayout->addLayout(buttonLayout);
 connect(ok, SIGNAL(clicked()), this, SLOT(on_okMove_clicked()));
 dlg->exec();
}

void LayoutEditor::on_okMove_clicked()
{
 int dx = xMove->text().toInt();
 int dy = yMove->text().toInt();
 for(int i =0; i < _contents->size(); i++)
 {
  moveItem(_contents->at(i), dx, dy);
 }
 for(int i = 0; i < pointList->size(); i++)
 {
  PositionablePoint* pp = pointList->at(i);
  QPointF pt = pp->getCoords();
  pt.setX(pt.x()+ dx);
  pt.setY(pt.y()+dy);
  pp->setCoords(pt);
 }
 for(int i = 0; i < trackList->count(); i++)
 {
  TrackSegment* seg = trackList->at(i);
  QPointF p = seg->getCoordsCenterCircle();
  seg->setCentreX(p.x()+dx);
  seg->setCentreY(p.y()+dy);
 } 
 for(int i = 0; i < turnoutList->count(); i++)
 {
  LayoutTurnout* to = turnoutList->at(i);
  QPointF p = to->getCoordsCenter();
  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
 }
 for(int i = 0; i < slipList->count(); i++)
 {
  LayoutSlip* to = slipList->at(i);
  QPointF p = to->getCoordsCenter();
  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
 }
 for(int i = 0; i < xingList->count(); i++)
 {
  LevelXing * to = xingList->at(i);
  QPointF p = to->getCoordsCenter();
  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
 }
 for(int i = 0; i < turntableList->count(); i++)
 {
  LayoutTurntable * to = turntableList->at(i);
  QPointF p = to->getCoordsCenter();
  to->setCoordsCenter(QPointF(p.x()+dx, p.y()+dy));
 }
 paintTargetPanel(editScene);
}
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
