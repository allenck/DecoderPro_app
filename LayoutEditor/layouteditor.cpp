#include "layouteditor.h"
//#include "ui_layouteditor.h"
#include <QGraphicsRectItem>
#include "instancemanager.h"
#include "QMessageBox"
#include "positionablepopuputil.h"
#include "coordinateedit.h"
#include "inputdialog.h"
#include "settrackwidthdlg.h"
#include "enterreporterdialog.h"
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
#include "layouteditorfinditems.h"
#include "jmriconfigurationmanager.h"
#include "userpreferencesmanager.h"
#include "positionablejcomponent.h"
#include "colorutil.h"
#include <QSignalMapper>
#include "jfilechooser.h"
#include "system.h"
#include "layouttrackdrawingoptions.h"
//#include "jmribeancombobox.h"
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
//#include "layouttrackeditors.h"
#include "layouteditorchecks.h"
#include "leblockcontentsicon.h"
#include "layouttrackdrawingoptions.h"
#include "layouttrackdrawingoptionsdialog.h"
#include <QPointF>
#include "transitmanager.h"
#include "dispatcherframe.h"
#include "dispatcheraction.h"
#include "activatetrainframe.h"
#include <QActionGroup>
#include "leblockcontentsicon.h"
#include "guilafpreferencesmanager.h"
#include "namedbeancombobox.h"
#include "layouteditorverticaltoolbarpanel.h"
#include "layouteditorhorizontaltoolbarpanel.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDockWidget>
#include "jtextarea.h"
#include "jpanel.h"
#include <QSysInfo>
#include <QMenuBar>
#include "layouteditorfloatingtoolbarpanel.h"
#include <QScrollBar>
#include "layoutshape.h"
#include <QToolTip>
#include "addentryexitpairaction.h"
#include "scaletrackdiagramdialog.h"
#include "editormanager.h"
#include "layoutrhturnout.h"
#include "layoutlhturnout.h"
#include "layoutdoublexover.h"
#include "layoutlhxover.h"
#include "layoutrhxover.h"
#include "layoutwye.h"
#include "layoutdoubleslip.h"
#include "layoutsingleslip.h"
#include "layouttrackview.h"
#include "positionablepointview.h"
#include "layouteditorcomponent.h"

/*private*/ /*static*/ const double LayoutEditor::SIZE = 3.0;
/*private*/ /*static*/ const double LayoutEditor::SIZE2 = 6.0;  // must be twice SIZE

//@Nonnull
/*public*/ LayoutEditorToolBarPanel* LayoutEditor::getLayoutEditorToolBarPanel() {
    return leToolBarPanel;
}

LayoutEditor::LayoutEditor(QString name, QWidget *parent) :
    PanelEditor(name, parent)//, ui(new Ui::LayoutEditor)
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
 //delete ui;
}

/*private*/ void LayoutEditor::setupMenuBar() {
    //initialize menu bar
    QMenuBar* menuBar = new QMenuBar();

    //set up File menu
    QMenu* fileMenu = new QMenu(tr("File"));
//        fileMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("MenuFileMnemonic")));
    menuBar->addMenu(fileMenu);
    StoreXmlUserAction* store = new StoreXmlUserAction(tr("Store"));
//        int primary_modifier = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
//        store->putValue(Action::ACCELERATOR_KEY, KeyStroke.getKeyStroke(
//                stringsToVTCodes.get(Bundle.getMessage("MenuItemStoreAccelerator")), primary_modifier));
    fileMenu->addAction(store);
    fileMenu->addSeparator();

    QAction* deleteItem = new QAction(tr("Delete Panel"), this);
    fileMenu->addAction(deleteItem);
//        deleteItem.addActionListener((ActionEvent event) -> {
    connect(deleteItem, &QAction::triggered, [=]{
            if (deletePanel()) {
                dispose();
            }
        });
    setMenuBar(menuBar);

    //setup Options menu
    setupOptionMenu(menuBar);

    //setup Tools menu
    setupToolsMenu(menuBar);

    //setup Zoom menu
    setupZoomMenu(menuBar);

    //setup marker menu
    setupMarkerMenu(menuBar);

    //Setup Dispatcher window
    setupDispatcherMenu(menuBar);

    //setup Help menu
    addHelpMenu("package.jmri.jmrit.display.LayoutEditor", true);
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

/*private*/ void LayoutEditor::setupToolBar() {
    //Initial setup for both horizontal and vertical
    //QWidget* contentPane = getContentPane();

    //remove these (if present) so we can add them back (without duplicates)
    if (editToolBarContainerPanel != nullptr)
    {
        editToolBarContainerPanel->setVisible(false);
        if(borderLayout)
         borderLayout->removeWidget(editToolBarContainerPanel);
    }

    if (helpBarPanel != nullptr) {
     if(borderLayout)
        borderLayout-> removeWidget(helpBarPanel);
    }

    deletefloatingEditToolBoxFrame();
    if (toolBarSide->getType() == eFLOAT) {
        createfloatingEditToolBoxFrame();
        createFloatingHelpPanel();
        return;
    }
//    if(borderLayout)
//    {
//     QWidget* cw = centralWidget();
//     if(cw)
//     {
//      //delete centralWidget()->layout();
//      delete cw;
//      delete borderLayout;
//     }
//    }
    //else
    {
     borderLayout = new BorderLayout;
     borderLayout->addWidget(editPanel, BorderLayout::Center);
    }

    //QSize screenDim = Toolkit.getDefaultToolkit().getScreenSize();
    QDesktopWidget* desktop = QApplication::desktop();
    QSize screenDim = desktop->screen()->size();
    bool toolBarIsVertical = ((toolBarSide->getType() == eRIGHT) || (toolBarSide->getType() == eLEFT));
    if (toolBarIsVertical)
    {
     leToolBarPanel = new LayoutEditorVerticalToolBarPanel(this);
     editToolBarScrollPane = new QScrollArea(/*leToolBarPanel*/);
     //editToolBarScrollPane->setWidget(leToolBarPanel);
     editToolBarScrollPane->setWidgetResizable(true);
     toolbarWidth = editToolBarScrollPane->size().width();
     toolbarHeight = screenDim.height();
    }
    else
    {
     leToolBarPanel = new LayoutEditorHorizontalToolBarPanel(this);
//        editToolBarScrollPane = new QScrollArea(/*leToolBarPanel*/);
//        editToolBarScrollPane->setWidget(leToolBarPanel);
//        editToolBarScrollPane->setWidgetResizable(true);
     toolbarWidth = screenDim.width();
     setMinimumWidth(toolbarWidth -100);
     toolbarHeight = leToolBarPanel->maximumHeight();
    }

    //editToolBarContainerPanel = new QDockWidget("Toolbar", this);
    editToolBarContainerPanel = new EditToolBarContainerPanel(this);
    QVBoxLayout* editToolBarContainerPanelLayout;
    editToolBarContainerPanel->setLayout(editToolBarContainerPanelLayout = new QVBoxLayout());//editToolBarContainerPanel, BoxLayout.PAGE_AXIS));
//    editToolBarContainerPanel->setWidget(editToolBarScrollPane);
//    editToolBarScrollPane->show();
//    if(toolBarIsVertical)
//    {
//     editToolBarScrollPane->setWidget(leToolBarPanel);
//     editToolBarContainerPanel->setWidget(editToolBarScrollPane);
//    }
//    else
     editToolBarContainerPanelLayout->addWidget(leToolBarPanel);

    //setup notification for when horizontal scrollbar changes visibility
    //editToolBarScroll.getViewport().addChangeListener(e -> {
    //log.warn("scrollbars visible: " + editToolBarScroll.getHorizontalScrollBar().isVisible());
    //});
    editToolBarContainerPanel->setMinimumSize(QSize(toolbarWidth, toolbarHeight));
    editToolBarContainerPanel->resize(QSize(toolbarWidth, toolbarHeight));
    if(toolBarIsVertical)
    {
     editToolBarContainerPanel->setMaximumWidth(150);
     //editToolBarContainerPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     //addDockWidget(Qt::LeftDockWidgetArea, editToolBarContainerPanel);

    }
    else
    {
     editToolBarContainerPanel->setMaximumHeight(140);
     //editToolBarContainerPanel->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
//     addDockWidget(Qt::TopDockWidgetArea, editToolBarContainerPanel);
    }
    switch (toolBarSide->getType())
    {
    case eLEFT:
     //ui->verticalLayout->addWidget(editToolBarContainerPanel, 0, Qt::AlignLeft);
     borderLayout->addWidget(editToolBarScrollPane, BorderLayout::West);
     editToolBarScrollPane->setWidget(editToolBarContainerPanel);
     break;
    case eRIGHT:
     //ui->verticalLayout->addWidget(editToolBarContainerPanel, 0, Qt::AlignRight);
     borderLayout->addWidget(editToolBarScrollPane, BorderLayout::East);
     editToolBarScrollPane->setWidget(editToolBarContainerPanel);
     break;
    case eTOP:
     //ui->verticalLayout->addWidget(editToolBarContainerPanel, 0, Qt::AlignTop);
     borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::North);
     break;
    case eBOTTOM:
     //ui->verticalLayout->addWidget(editToolBarContainerPanel, 0, Qt::AlignBottom);
     borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::South);
     break;
    default:
     break;
    }
    borderLayout->addWidget(helpBarPanel, BorderLayout::South);

    QWidget* borderWidget = new QWidget();
    borderWidget->setLayout(borderLayout);
    setCentralWidget(borderWidget);
}

/*private*/ void LayoutEditor::createfloatingEditToolBoxFrame()
{
 if (isEditable() && floatingEditToolBoxFrame == nullptr)
 {
  //Create a scroll pane to hold the window content.
  leToolBarPanel = new LayoutEditorFloatingToolBarPanel(this);
  floatingEditContentScrollPane = new QScrollArea();//new JScrollPane(leToolBarPanel);
  floatingEditContentScrollPane->setWidget(leToolBarPanel);
  floatingEditContentScrollPane->setHorizontalScrollBarPolicy(/*JScrollPane.HORIZONTAL_SCROLLBAR_NEVER*/Qt::ScrollBarAlwaysOff);
  floatingEditContentScrollPane->setVerticalScrollBarPolicy(/*JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED*/Qt::ScrollBarAsNeeded);
  floatingEditContentScrollPane->setWidgetResizable(true);
  //Create the window and add the toolbox content
  floatingEditToolBoxFrame = new JmriJFrameX(tr("Tool Box: %1").arg(getLayoutName()));
  floatingEditToolBoxFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  floatingEditToolBoxFrame->setContentPane(floatingEditContentScrollPane);
  floatingEditToolBoxFrame->pack();
  floatingEditToolBoxFrame->setAlwaysOnTop(true);
  floatingEditToolBoxFrame->setVisible(true);
 }
}

/*private*/ void LayoutEditor::deletefloatingEditToolBoxFrame() {
    if (floatingEditContentScrollPane != nullptr) {
//        floatingEditContentScrollPane->removeAll();
        floatingEditContentScrollPane = nullptr;
    }
    if (floatingEditToolBoxFrame != nullptr) {
        floatingEditToolBoxFrame->dispose();
        floatingEditToolBoxFrame = nullptr;
    }
}

/*private*/ void LayoutEditor::createFloatingHelpPanel() {
#if 0
    if (leToolBarPanel instanceof LayoutEditorFloatingToolBarPanel) {
        LayoutEditorFloatingToolBarPanel leftbp = (LayoutEditorFloatingToolBarPanel) leToolBarPanel;
        floatEditHelpPanel = new JPanel();
        leToolBarPanel.add(floatEditHelpPanel);

        //Notice: End tree structure indenting
        // Force the help panel width to the same as the tabs section
        int tabSectionWidth = (int) leftbp.getPreferredSize().getWidth();

        //Change the textarea settings
        for (Component c : helpBar.getComponents()) {
            if (c instanceof JTextArea) {
                JTextArea j = (JTextArea) c;
                j.setSize(new Dimension(tabSectionWidth, j.getSize().height));
                j.setLineWrap(true);
                j.setWrapStyleWord(true);
            }
        }

        //Change the width of the help panel section
        floatEditHelpPanel.setMaximumSize(new Dimension(tabSectionWidth, Integer.MAX_VALUE));
        floatEditHelpPanel.add(helpBar);
        floatEditHelpPanel.setVisible(isEditable() && getShowHelpBar());
    }
#endif
}

void LayoutEditor::init()
{
 setSaveSize(true);
 editorUseOldLocSize = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize();

 //ui->setupUi(this);
 setObjectName("LayoutEditor");
 JmriJFrame::initComponents();
 PanelEditor::init(layoutName);
 savePanels = new StoreXmlUserAction(tr("Save Panels..."), this);
 _contents = new QVector<Positionable*>();

 wideToolBarCheckBoxMenuItem = new QAction(tr("Wide ToolBar"));
 wideToolBarCheckBoxMenuItem->setCheckable(true);
 helpBarPanel = new JPanel();

 editPanel = new QGraphicsView(/*ui->centralWidget*/);

 setupToolBar();
 setupMenuBar();

 //setup help bar

 helpBarPanel->setLayout(new QVBoxLayout());//helpBar, BoxLayout.PAGE_AXIS));
 QTextEdit* textEdit = new QTextEdit(/*centralWidget*/);
 textEdit->setObjectName(QLatin1String("textEdit"));
 QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
 textEdit->setSizePolicy(sizePolicy);
 textEdit->setMaximumSize(QSize(16777215, 42));
 textEdit->setHtml(QApplication::translate("LayoutEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">To add an item check item type, enter needed data then with shift down, click on panel -except track segment. To add a track segment, with shift down, click mouse on one connection point and drag to another connection point. To move an item, drag it with the right mouse button. To show it's popup menu, right click on it. </span></p></body></html>", nullptr));

 helpBarPanel->layout()->addWidget(textEdit);
 if(static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
 {
  log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }

 //HelpUtil::instance()->helpMenu(menuBar(), "package.jmri.jmrit.display.LayoutEditor", true);
 // set to full screen
 QDesktopWidget* desktop = QApplication::desktop();
    QSize screenDim = desktop->screen()->size();
    gContext->setWindowWidth(screenDim.width() - 20);
    gContext->setWindowHeight(screenDim.height() - 120);

    // Let Editor make target, and use this frame
    PanelEditor::setTargetPanel((EditScene*)nullptr, (JmriJFrame*)nullptr);
    PanelEditor::setTargetPanelSize(gContext->getWindowWidth(), gContext->getWindowHeight());
    setSize(screenDim.width(), screenDim.height());

    // register the resulting panel for later configuration
    ConfigureManager* cm = ((ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager"));
            if(cm) cm->registerUser(this);

    // confirm that panel hasn't already been loaded
    if (this != ((EditorManager*)(InstanceManager::getDefault("EditorManager")))->get(name)) {
        log->warn("File contains a panel with the same name ({}) as an existing panel", name);
    }
//    setFocusable(true);
//    addKeyListener(this);
 resetDirty();
 // establish link to LayoutEditorAuxTools
 auxTools = getLEAuxTools();

_contents = new QVector<Positionable*>();
 layoutBlockManager = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 blockManger = new BlockManager(this);

 turntableList = new QVector<LayoutTurntable*>(); // Turntable list
 memoryLabelList = new QVector<LEMemoryIcon*>(); // Memory Label List

//makeBackgroundColorMenu(ui->menuSet_Background_color);
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

 undoTranslateSelectionMenuItem = new QMenu(tr("Undo Translate Selection"));
 assignBlockToSelectionMenuItem = new QMenu(tr("Assign Block To Selection") + "...");


 _labelImage = new QVector<PositionableLabel*>(); // layout positionable label images
 sensorImage = new QVector<SensorIcon*>();  // sensor images
 signalHeadImage = new QVector<SignalHeadIcon*>();  // signal head images

 signalMastImage = new QVector<SignalMastIcon*>();  // signal mast images
 signalList = new QVector<SignalHeadIcon*>();  // Signal Head Icons
 signalMastList = new QVector<SignalMastIcon*>();  // Signal Head Icons
 layoutShapes = new QList<LayoutShape*>();               // LayoutShap list


 qApp->processEvents();

 sensorList = new QVector<SensorIcon*>();  // Sensor Icons
 //_defaultToolTip = "";
 toolBarFontSizeMenu = new QMenu(tr("Font Size"));
 wideToolBarCheckBoxMenuItem = new QAction(("Wide ToolBar"), this);
 wideToolBarCheckBoxMenuItem->setCheckable(true);
 dropDownListsDisplayOrderMenu = new QMenu(tr("Drop Down Lists Display Order..."));



 //use turnoutCircleSize when you need an int and these when you need a double
     //note: these only change when setTurnoutCircleSize is called
     //using these avoids having to call getTurnoutCircleSize() and
     //the multiply (x2) and the int -> double conversion overhead
 circleRadius = SIZE * getTurnoutCircleSize();
 circleDiameter = 2.0 * circleRadius;

 //panelWidth = 600;
 gContext->setLayoutWidth(600);
 //panelHeight =400;
 gContext->setLayoutHeight(400);

 //editScene = new EditScene(QRectF(-100, -100, 400, 400), this);
 editScene = new EditScene(QRectF(0, 0, gContext->getLayoutWidth(), gContext->getLayoutWidth()), this);
 editScene->setObjectName("LayoutEditor_editScene");
 //_targetPanel = editScene;
 defaultBackgroundColor =  editScene->backgroundBrush().color();//QColor(Qt::lightGray);

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
 _layoutShapeSelection = QList<LayoutShape*>();


 editPanel->setMouseTracking(true);
 editPanel->setScene(editScene);

 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(on_scenePos(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)),this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
 // connect(editScene,SIGNAL(sceneDragMove(QGraphicsSceneDragDropEvent*)),this, SLOT(mouseDragged(QGraphicsSceneDragDropEvent*)));
 connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));

 sensorIconEditor = new MultiIconEditor(4);
 sensorIconEditor->setIcon(0, "Active:",":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
 sensorIconEditor->setIcon(1, "Inactive", ":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
 sensorIconEditor->setIcon(2, "Inconsistent:", ":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->setIcon(3, "Unknown:",":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
 sensorIconEditor->complete();

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

 iconEditor = new MultiIconEditor(1);
 iconEditor->setIcon(0, "",":/resources/icons/smallschematics/tracksegments/block.gif");
 iconEditor->complete();
 iconFrame = new JFrame(tr("Edit Icon"));
 QWidget* iconFrameCentralWidget = getContentPane();
 QVBoxLayout* iconFrameLayout = new QVBoxLayout(iconFrameCentralWidget);
 iconFrameLayout->addWidget(iconEditor);
 iconFrame->pack();

 _urlMap = new QMap<QString, QString>();
 finder = new LayoutEditorFindItems(this);

// register the resulting panel for later configuration
 //ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");

 if (cm != nullptr) {
     cm->registerUser(this);
 }

 // confirm that panel hasn't already been loaded
 if (((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
 {
  log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
 }
 sidelineTrackWidthField = new JTextField(6);
 mainlineTrackWidthField = new JTextField(6);

 primaryGridSizeField = new JTextField(6);
 secondaryGridSizeField = new JTextField(6);

 //operational variables for enter reporter pane
 xPositionField = new JTextField(6);
 yPositionField = new JTextField(6);
 reporterNameField = new JTextField(6);

 //operational variables for scale/translate track diagram pane
 xFactorField = new JTextField(6);
 yFactorField = new JTextField(6);
 xTranslateField = new JTextField(6);
 yTranslateField = new JTextField(6);
 gDDMDO = NamedBean::DisplayOptions::DISPLAYNAME;
 _positionableSelection = new QVector<Positionable*>();
 _layoutTrackSelection = QList<LayoutTrack*>();

 xMoveField = new JTextField(6);
 yMoveField = new JTextField(6);

 //initialize preferences
 UserPreferencesManager* prefsMgr= static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
 if(prefsMgr)
 {
     QString windowFrameRef = getWindowFrameRef();

     QVariant prefsProp = prefsMgr->getProperty(windowFrameRef, "toolBarSide");
     log->debug(tr("%1.toolBarSide is %2").arg(windowFrameRef).arg(prefsProp.toString()));
     if (prefsProp != QVariant()) {
         QString newToolBarSide = prefsProp.toString();
         on_setToolBarSide(newToolBarSide);
     }

     //Note: since prefs default to false and we want wide to be the default
     //we invert it and save it as thin
     bool prefsToolBarIsWide = prefsMgr->getSimplePreferenceState(windowFrameRef + ".toolBarThin");
     log->debug(tr("%1.toolBarThin is %2").arg(windowFrameRef).arg(prefsProp.toString()));
     on_setToolBarWide(prefsToolBarIsWide);

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

 }//); //Inst
 // make sure that the layoutEditorComponent is in the _targetPanel components
#if 0
 QList<QWidget*> componentList = QList<QWidget*>(_targetPanel->getComponents());
 if (!componentList.contains(layoutEditorComponent)) {
     try {
         _targetPanel.remove(layoutEditorComponent);
         _targetPanel.add(layoutEditorComponent, Integer.valueOf(3));
         _targetPanel.moveToFront(layoutEditorComponent);
     } catch (Exception e) {
         log.warn("paintTargetPanelBefore: Exception {}", e);
     }
 }
#endif
 //QTimer::singleShot(100, this,  SLOT(trigger_menu()));
 setupToolBar();
} // init

void LayoutEditor::trigger_menu()
{
on_setToolBarSide(toolBarSide->getName().toUpper());
}

/*public*/ void LayoutEditor::setSize(int w, int h)
{
 log->debug("Frame size now w=" + QString::number(w) + ", h=" + QString::number(h));
 Editor::resize(w, h);
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
// turnoutCircleSizeMenuItems->replace(turnoutCircleSizeCount, r);
// turnoutCircleSizes->replace(turnoutCircleSizeCount, size);
// turnoutCircleSizeCount++;
}

//void LayoutEditor::on_turnoutCircleSizeButtonMapper_triggered(int size)
//{
// int desiredSize = size;//act->data().toInt();
// if (turnoutCircleSize != desiredSize)
// {
//  turnoutCircleSize = desiredSize;
//  setDirty(true);
//  repaint();
// }
//}

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
/*public*/ /*static*/ void LayoutEditor::setupComboBox(/*@Nonnull*/ NamedBeanComboBox* inComboBox, bool inValidateMode, bool inEnable) {
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
/*public*/ /*static*/ void LayoutEditor::setupComboBox(/*@Nonnull*/ NamedBeanComboBox* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank) {
    log->debug("LE setupComboBox called");

    inComboBox->setEnabled(inEnable);
    inComboBox->setEditable(true);
    inComboBox->setValidatingInput(inValidateMode);
    inComboBox->setCurrentText("");

    // This has to be set before calling setupComboBoxMaxRows
    // (otherwise if inFirstBlank then the  number of rows will be wrong)
    inComboBox->setAllowNull(!inValidateMode);

    // set the max number of rows that will fit onscreen
//    JComboBoxutil->setupComboBoxMaxRows(inComboBox);

    inComboBox->setCurrentIndex(-1);
}

void LayoutEditor::on_scenePos(QGraphicsSceneMouseEvent* event)
{
 calcLocation(event, 0,0);
 leToolBarPanel->xLabel->setText(QString("%1").arg(xLoc));
 leToolBarPanel->yLabel->setText(QString("%1").arg(yLoc));
 Qt::MouseButtons b = event->buttons();
 if (b == Qt::RightButton || event->modifiers()&Qt::ShiftModifier)
  mouseDragged(event);
}

/*
 * Get mouse coordinates and adjust for zoom.
 * <p>
 * Side effects on xLoc, yLoc and dLoc
 */
//@Nonnull
/*private*/ QPointF LayoutEditor::calcLocation(QGraphicsSceneMouseEvent* event, int dX, int dY)
{
 xLoc = (int) ((event->scenePos().x() + dX) / getZoom());
 yLoc = (int) ((event->scenePos().y() + dY) / getZoom());
 dLoc = QPointF(xLoc, yLoc);
 return dLoc;
}

/*private*/ QPointF LayoutEditor::calcLocation(QGraphicsSceneMouseEvent* event) {
    return calcLocation(event, 0, 0);
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
// delayedPopupTrigger= false;
// isDragging = false;
 calcLocation(event);

 //TODO: Add command-click on nothing to pan view?
 if (isEditable())
 {
  bool prevSelectionActive = selectionActive;
  selectionActive = false;
  leToolBarPanel->xLabel->setText(QString("%1").arg(xLoc));
  leToolBarPanel->yLabel->setText(QString("%1").arg(yLoc));

  if (/*event.isPopupTrigger()*/ bPopupTrigger)
  {
//   if (event.isMetaDown() || event.isAltDown())
   if(bMeta || bAlt)
   {
    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
    delayedPopupTrigger = true;
   }
   else
   {
    // no possible conflict with moving, display the popup now
    showEditPopUps(event);
   }
  }
  if (bMeta || /*(!bAlt && !bShift)*/ bAlt)
  {
   //if dragging an item, identify the item for mouseDragging
   selectedObject = nullptr;
   selectedHitPointType = LayoutTrack::NONE;

   if (findLayoutTracksHitPoint(dLoc))
   {
    selectedObject = foundTrack;
    selectedHitPointType = foundHitPointType;
    startDelta = QPointF(MathUtil::subtract(foundLocation, dLoc));
    foundTrack = nullptr;
   }
   else
   {
    selectedObject = checkMarkerPopUps(dLoc);
    if (selectedObject != nullptr)
    {
     selectedHitPointType = LayoutTrack::MARKER;
     startDelta = MathUtil::subtract(((LocoIcon*) selectedObject)->getLocation(), dLoc);
    }
    else
    {
     selectedObject = checkClockPopUps(dLoc);
     if (selectedObject != nullptr)
     {
      selectedHitPointType = LayoutTrack::LAYOUT_POS_JCOMP;
      startDelta = (MathUtil::subtract(((PositionableJComponent*) selectedObject)->getLocation(), dLoc));
     }
     else
     {
      selectedObject = checkMultiSensorPopUps(dLoc);
      if (selectedObject != nullptr)
      {
       selectedHitPointType = LayoutTrack::MULTI_SENSOR;
       startDelta = (MathUtil::subtract(((MultiSensorIcon*) selectedObject)->getLocation(), dLoc));
      }
     }
    }
     if (selectedObject == nullptr)
     {
      selectedObject = checkSensorIconPopUps(dLoc);
      if (selectedObject == nullptr)
      {
       selectedObject = checkSignalHeadIconPopUps(dLoc);
       if (selectedObject == nullptr)
       {
        selectedObject = checkLabelImagePopUps(dLoc);
        if (selectedObject == nullptr) {
            selectedObject = checkSignalMastIconPopUps(dLoc);
       }
      }
     }

     if (selectedObject != nullptr)
     {
      selectedHitPointType = LayoutTrack::LAYOUT_POS_LABEL;
      startDelta = (MathUtil::subtract(((PositionableLabel*) selectedObject)->getLocation(), dLoc));
      if(qobject_cast<LEMemoryIcon*>(selectedObject))
      {
       LEMemoryIcon* pm = (LEMemoryIcon*) selectedObject;

       if (pm->getPopupUtility()->getFixedWidth() == 0)
       {
        startDelta= QPointF((pm->getOriginalX() - dLoc.x()),
                (pm->getOriginalY() - dLoc.y()));
       }
      }
      // ACK added
      if (!_positionableSelection->contains((Positionable*)selectedObject))
      {
          _positionableSelection->append((Positionable*)selectedObject);
      }

     }
     else
     {
      selectedObject = checkBackgroundPopUps(dLoc);

      if (selectedObject != nullptr)
      {
       selectedHitPointType = LayoutTrack::LAYOUT_POS_LABEL;
       startDelta = (MathUtil::subtract(((PositionableLabel*) selectedObject)->getLocation(), dLoc));

      } else {
       //dragging a shape?
       QListIterator<LayoutShape*> listIterator(*layoutShapes);// = layoutShapes.listIterator(layoutShapes.size());
       listIterator.toBack();
       //hit test in front to back order (reverse order of list)
       while (listIterator.hasPrevious())
       {
        LayoutShape* ls = listIterator.previous();
        selectedHitPointType = ls->findHitPointType(dLoc, true);
        if (LayoutShape::isShapeHitPointType(selectedHitPointType))
        {
         //log.warn("drag selectedObject: ", lt);
         selectedObject = ls;    // found one!
         beginLocation = QPointF(dLoc);
         currentLocation = QPointF(beginLocation);
         startDelta = QPointF(MathUtil::zeroPoint2D);
         ls->drawEditControls(editScene);
         break;
        }
       }
      }
     }
    }
   }
  }
  else if (bShift && leToolBarPanel->trackButton->isChecked() /*&& (!event.isPopupTrigger()) */)
  {
   // starting a Track Segment, check for free connection point
   selectedObject = nullptr;
   if (findLayoutTracksHitPoint(dLoc))
   {
    // match to a free connection point
    beginTrack = foundTrack;
    beginHitPointType = foundHitPointType;
    beginLocation = QPointF(foundLocation);
    //BUGFIX: prevents initial drawTrackSegmentInProgress to {0, 0}
    currentLocation = QPointF(beginLocation);
   }
   else
   {
    //TODO: auto-add anchor point?
    beginTrack = nullptr;
   }
  }
  else if (bShift && leToolBarPanel->shapeButton->isChecked() && !bPopupTrigger)
  {
   //adding or extending a shape
   selectedObject = nullptr;  // assume we're adding...
   for (LayoutShape* ls : *layoutShapes)
   {
       selectedHitPointType = ls->findHitPointType(dLoc, true);
       if (LayoutShape::isShapePointOffsetHitPointType(selectedHitPointType)) {
           //log.warn("extend selectedObject: ", lt);
           selectedObject = ls;    // nope, we're extending
           beginLocation = dLoc;
           currentLocation = beginLocation;
           break;
       }
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
 else if (allControlling()
          && !bMeta && !bPopupTrigger
          && !bAlt && !bShift && !bControl)
 {
  // not in edit mode - check if mouse is on a turnout (using wider search range)
  selectedObject = nullptr;
  checkControls(true);
 }
 else if ((bMeta || bAlt)
                && !bShift && !bControl) {
  // not in edit mode - check if moving a marker if there are any
  selectedObject = checkMarkers(dLoc);
  if (selectedObject!=nullptr)
  {
   selectedHitPointType = MARKER;
   startDelta= QPointF((((PositionableLabel*)selectedObject)->getX()-dLoc.x()),
                                            (((PositionableLabel*)selectedObject)->getY()-dLoc.y()));
   //selectedNeedsConnect = false;
  }
 }
 else if (bPopupTrigger&& !bShift)
 {
  // not in edit mode - check if a marker popup menu is being requested
  LocoIcon* lo = checkMarkers(dLoc);
  if (lo!=nullptr)
   delayedPopupTrigger = true;
 }
 if (/*!event.isPopupTrigger() &&*/ !isDragging)
 {
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  {
   selections.at(0)->doMousePressed(event);
  }
 }
 //thisPanel.requestFocusInWindow();
 return;
}

/**
 * Called by {@link #mousePressed} to determine if the mouse click was in a turnout control location.
 * If so, update selectedHitPointType and selectedObject for use by {@link #mouseReleased}.
 * <p>
 * If there's no match, selectedObject is set to null and selectedHitPointType
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
        selectedHitPointType = theTrack->findHitPointType(dLoc, useRectangles); // deliberate side-effect
        if (LayoutTrack::isControlHitType(selectedHitPointType)) {
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

    foundTrack = nullptr;
    foundHitPointType = LayoutTrack::NONE;

    Optional<LayoutTrack*> opt;// = layoutTrackList->stream().filter(layoutTrack ->
    for(LayoutTrack* layoutTrack : *layoutTrackList)
    {
        if ((layoutTrack != avoid) && (layoutTrack != selectedObject))
            foundHitPointType = layoutTrack->findHitPointType(loc, false, requireUnconnected);

//        return (LayoutTrack::NONE != foundPointType);
        if(LayoutTrack::NONE != foundHitPointType)
        {
         foundTrack = layoutTrack;
         break;
        }
    }//).findFirst();

    LayoutTrack* layoutTrack = foundTrack;
//    if (opt.isPresent()) {
//        layoutTrack = opt.get();
//    }
    if (layoutTrack != nullptr) {
        foundTrack = layoutTrack;
        foundLocation = layoutTrack->getCoordsForConnectionType(foundHitPointType);
        //foundNeedsConnect = layoutTrack->isDisconnected(foundTrack);
        result = true;
    }
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

/*private*/ LayoutShape* LayoutEditor::checkLayoutShapePopUps(/*@Nonnull*/ QPointF loc) {
    LayoutShape* result = nullptr;
    for (LayoutShape* ls : *layoutShapes) {
        selectedHitPointType = ls->findHitPointType(loc, true);
        if (LayoutShape::isShapeHitPointType(selectedHitPointType)) {
            result = ls;
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
    return layoutTrack->getCoordsForConnectionType(connectionType);
}


// mouse pressed and released.
/*public*/ void LayoutEditor::mouseClicked(QGraphicsSceneMouseEvent* event)
{
 bool bMeta = event->modifiers()&Qt::MetaModifier;
 bool bAlt = event->modifiers()&Qt::AltModifier;
 bool bShift =  event->modifiers()&Qt::ShiftModifier;
 bool bPopupTrigger = event->button() & Qt::RightButton;
 bool bControl = event->modifiers()&Qt::ControlModifier;

 //initialize mouse position
 calcLocation(event);

 // if alt modifier is down invert the snap to grid behaviour
 snapToGridInvert = bAlt;

 if (!bMeta && !bPopupTrigger && !bAlt
                 && !awaitingIconChange && !bShift && !bControl)
 {
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  {
   selections.at(0)->doMouseClicked(event);
  }
 }
 else if (bPopupTrigger && (whenReleased != QDateTime::currentMSecsSinceEpoch()))
 {
   if (isEditable())
   {
    selectedObject = nullptr;
    selectedHitPointType = LayoutTrack::NONE;
    showEditPopUps(event);
   } else {
    LocoIcon* lo = checkMarkerPopUps(dLoc);

    if (lo != nullptr) {
        showPopUp(lo, event);
    }
   }
 }
 if (bControl && !bPopupTrigger)
 {
  if (findLayoutTracksHitPoint(dLoc))
  {
   // show popup menu
   switch (foundHitPointType)
   {
   case LayoutTrack::POS_POINT:
   case LayoutTrack::TURNOUT_CENTER:
   case LayoutTrack::LEVEL_XING_CENTER:
   case LayoutTrack::SLIP_LEFT:
   case LayoutTrack::SLIP_RIGHT:
   case LayoutTrack::TURNTABLE_CENTER: {
       amendSelectionGroup(foundTrack);
       break;
   }
   default: {
    break;
   }
  }
 }
 else
 {
   PositionableLabel* s = checkSensorIconPopUps(dLoc);
   if (s!=nullptr)
   {
    amendSelectionGroup(s);
   }
   else
   {
    PositionableLabel* sh = checkSignalHeadIconPopUps(dLoc);
    if (sh!=nullptr)
    {
     amendSelectionGroup(sh);
    }
    else
    {
     PositionableLabel* ms = checkMultiSensorPopUps(dLoc);
     if (ms!=nullptr)
     {
      amendSelectionGroup(ms);
     }
     else
     {
      PositionableLabel* lb = checkLabelImagePopUps(dLoc);
      if (lb!=nullptr)
      {
       amendSelectionGroup(lb);
      }
      else
      {
       PositionableLabel* b = checkBackgroundPopUps(dLoc);
       if (b!=nullptr)
       {
        amendSelectionGroup(b);
       }
       else
       {
        PositionableLabel* sm = checkSignalMastIconPopUps(dLoc);
        if (sm!=nullptr)
        {
         amendSelectionGroup(sm);
        }
        else
        {
         LayoutShape* ls = checkLayoutShapePopUps(dLoc);
         if (ls != nullptr) {
             amendSelectionGroup(ls);
         }
        }
       }
      }
     }
    }
   }
  }
 }
 else if((selectionWidth==0) || (selectionHeight == 0))
 {
  clearSelectionGroups();
 }
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
 beginTrack = p;
 beginHitPointType = LayoutTrack::POS_POINT;
 QPointF loc = p->getCoordsCenter();

 if (findLayoutTracksHitPoint(loc, true, p))
 {
  switch (foundHitPointType)
  {
   case LayoutTrack::POS_POINT:
   {
    PositionablePoint* p2 = (PositionablePoint*) foundTrack;

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
  default:
  {
   if (foundHitPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET)
   {
        LayoutTurntable* tt = (LayoutTurntable*) foundTrack;
        int ray = foundHitPointType - LayoutTrack::TURNTABLE_RAY_OFFSET;

        if (tt->getRayConnectIndexed(ray) == nullptr) {
            tt->setRayConnect(t, ray);

            if (t->getConnect1() == p) {
                t->setNewConnect1(tt, foundHitPointType);
            } else {
                t->setNewConnect2(tt, foundHitPointType);
            }
            p->removeTrackConnection(t);

            if ((p->getConnect1() == nullptr) && (p->getConnect2() == nullptr)) {
                removePositionablePoint(p);
            }
        }
    } else {
        log->debug("No valid point, so will quit");
        return;
    }
    break;
   }
  }
  redrawPanel();

  if (t->getLayoutBlock() != nullptr) {
      getLEAuxTools()->setBlockConnectivityChanged();
  }
 }
 beginTrack = nullptr;
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
    beginTrack = lt;

    if (lt->getConnectA() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginHitPointType = LayoutTrack::SLIP_A;
        } else {
            beginHitPointType = LayoutTrack::TURNOUT_A;
        }
        dLoc = lt->getCoordsA();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }

    if (lt->getConnectB() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginHitPointType = LayoutTrack::SLIP_B;
        } else {
            beginHitPointType = LayoutTrack::TURNOUT_B;
        }
        dLoc = lt->getCoordsB();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }

    if (lt->getConnectC() == nullptr) {
        if (qobject_cast<LayoutSlip*>(lt)) {
            beginHitPointType = LayoutTrack::SLIP_C;
        } else {
            beginHitPointType = LayoutTrack::TURNOUT_C;
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
            beginHitPointType = LayoutTrack::SLIP_D;
        } else {
            beginHitPointType = LayoutTrack::TURNOUT_D;
        }
        dLoc = lt->getCoordsD();
        hitPointCheckLayoutTurnoutSubs(dLoc);
    }
    beginTrack = nullptr;
    foundTrack = nullptr;
}

/*private*/ void LayoutEditor::hitPointCheckLayoutTurnoutSubs(/*@Nonnull*/ QPointF dLoc) {
    if (findLayoutTracksHitPoint(dLoc, true)) {
        switch (foundHitPointType) {
            case LayoutTrack::POS_POINT: {
                PositionablePoint* p2 = (PositionablePoint*) foundTrack;

                if (((p2->getConnect1() == nullptr) && (p2->getConnect2() != nullptr))
                        || ((p2->getConnect1() != nullptr) && (p2->getConnect2() == nullptr))) {
                    TrackSegment* t = p2->getConnect1();

                    if (t == nullptr) {
                        t = p2->getConnect2();
                    }

                    if (t == nullptr) {
                        return;
                    }
                    LayoutTurnout* lt = (LayoutTurnout*) beginTrack;
                    try {
                        if (lt->getConnection(beginHitPointType) == nullptr) {
                            lt->setConnection(beginHitPointType, t, LayoutTrack::TRACK);
                            p2->removeTrackConnection(t);

                            if (t->getConnect1() == p2) {
                                t->setNewConnect1(lt, beginHitPointType);
                            } else {
                                t->setNewConnect2(lt, beginHitPointType);
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
                LayoutTurnout* ft = (LayoutTurnout*) foundTrack;
                addTrackSegment();

                if ((ft->getTurnoutType() == LayoutTurnout::RH_TURNOUT) || (ft->getTurnoutType() == LayoutTurnout::LH_TURNOUT)) {
                    rotateTurnout(ft);
                }

                // Assign a block to the new zero length track segment.
                ft->setTrackSegmentBlock(foundHitPointType, true);
                break;
            }

            default: {
                log->warn(tr("Unexpected foundPointType %1 in hitPointCheckLayoutTurnoutSubs").arg(foundHitPointType));
                break;
            }
        }
    }
}

/*private*/ void LayoutEditor::rotateTurnout(LayoutTurnout* t) {
    LayoutTurnout* be = (LayoutTurnout*) beginTrack;

    if (((beginHitPointType == LayoutTrack::TURNOUT_A) && ((be->getConnectB() != nullptr) || (be->getConnectC() != nullptr))) ||
        ((beginHitPointType == LayoutTrack::TURNOUT_B) && ((be->getConnectA() != nullptr) || (be->getConnectC() != nullptr))) ||
        ((beginHitPointType == LayoutTrack::TURNOUT_C) && ((be->getConnectB() != nullptr) || (be->getConnectA() != nullptr)))) {
        return;
    }

    if ((be->getTurnoutType() != LayoutTurnout::RH_TURNOUT) && (be->getTurnoutType() != LayoutTurnout::LH_TURNOUT)) {
        return;
    }

    double x2;
    double y2;

    QPointF c;
    QPointF diverg;

    if ((foundHitPointType == LayoutTrack::TURNOUT_C) && (beginHitPointType == LayoutTrack::TURNOUT_C)) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();
        x2 = be->getCoordsA().x() - be->getCoordsB().x();
        y2 = be->getCoordsA().y() - be->getCoordsB().y();
    } else if ((foundHitPointType == LayoutTrack::TURNOUT_C) &&
               ((beginHitPointType == LayoutTrack::TURNOUT_A) || (beginHitPointType == LayoutTrack::TURNOUT_B))) {
        c = t->getCoordsCenter();
        diverg = t->getCoordsC();

        if (beginHitPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsB().x() - be->getCoordsA().x();
            y2 = be->getCoordsB().y() - be->getCoordsA().y();
        } else {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        }
    } else if (foundHitPointType == LayoutTrack::TURNOUT_B) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();

        if (beginHitPointType == LayoutTrack::TURNOUT_B) {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        } else if (beginHitPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsB().x() - be->getCoordsA().x();
            y2 = be->getCoordsB().y() - be->getCoordsA().y();
        } else {    //(beginPointType==TURNOUT_C){
            x2 = be->getCoordsCenter().x() - be->getCoordsC().x();
            y2 = be->getCoordsCenter().y() - be->getCoordsC().y();
        }
    } else if (foundHitPointType == LayoutTrack::TURNOUT_A) {
        c = t->getCoordsA();
        diverg = t->getCoordsB();

        if (beginHitPointType == LayoutTrack::TURNOUT_A) {
            x2 = be->getCoordsA().x() - be->getCoordsB().x();
            y2 = be->getCoordsA().y() - be->getCoordsB().y();
        } else if (beginHitPointType == LayoutTrack::TURNOUT_B) {
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

    if (foundHitPointType == LayoutTrack::TURNOUT_B) {
        tCord = t->getCoordsB();
    }

    if (foundHitPointType == LayoutTrack::TURNOUT_A) {
        tCord = t->getCoordsA();
    }

    if (beginHitPointType == LayoutTrack::TURNOUT_B) {
        conCord = be->getCoordsB();
    } else if (beginHitPointType == LayoutTrack::TURNOUT_C) {
        conCord = be->getCoordsC();
    } else if (beginHitPointType == LayoutTrack::TURNOUT_A) {
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
 bool bPopupTrigger = event->button() & Qt::RightButton;

 //super.setToolTip(nullptr);

 // initialize mouse position
 calcLocation(event);

 // if alt modifier is down invert the snap to grid behaviour
 snapToGridInvert = isAltDown;

 if (isEditable())
 {
  leToolBarPanel->xLabel->setText(QString("%1").arg(xLoc));
  leToolBarPanel->yLabel->setText(QString("%1").arg(yLoc));

  // released the mouse with shift down... see what we're adding
  if (!bPopupTrigger && !isMetaDown && bShift)
  {
   currentPoint = QPointF(xLoc, yLoc);

   if (snapToGridOnAdd)
   {
    currentPoint = MathUtil::granulize(currentPoint, gContext->getGridSize());
    yLoc = (int) currentPoint.y();
    leToolBarPanel->xLabel->setText(QString::number(xLoc));
    leToolBarPanel->yLabel->setText(QString::number(yLoc));
   }
   if (leToolBarPanel->turnoutRHButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_TURNOUT);
   }
   else if (leToolBarPanel->turnoutLHButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_TURNOUT);
   }
   else if (leToolBarPanel->turnoutWYEButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::WYE_TURNOUT);
   }
   else if (leToolBarPanel->doubleXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::DOUBLE_XOVER);
   }
   else if (leToolBarPanel->rhXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::RH_XOVER);
   }
   else if (leToolBarPanel->lhXoverButton->isChecked())
   {
    addLayoutTurnout(LayoutTurnout::LH_XOVER);
   }
   else if (leToolBarPanel->levelXingButton->isChecked())
   {
    addLevelXing();
   }
   else if (leToolBarPanel->layoutSingleSlipButton->isChecked())
   {
    addLayoutSlip(LayoutSlip::SINGLE_SLIP);
   }
   else if (leToolBarPanel->layoutDoubleSlipButton->isChecked())
   {
    addLayoutSlip(LayoutSlip::DOUBLE_SLIP);
   }
   else if (leToolBarPanel->endBumperButton->isChecked())
   {
    addEndBumper();
   }
   else if (leToolBarPanel->anchorButton->isChecked())
   {
    addAnchor();
   }
   else if (leToolBarPanel->trackButton->isChecked())
   {
    if ( (beginTrack!=nullptr) && (foundTrack!=nullptr) &&
                (beginTrack!=foundTrack) )
    {
     if(trackInProgress != nullptr && trackInProgress->scene()!=0)
     {
      editScene->removeItem(trackInProgress);
      trackInProgress = nullptr;
     }
     addTrackSegment();
     setCursor(Qt::ArrowCursor);
    }
    beginTrack = nullptr;
    foundTrack = nullptr;
    }
   else if (leToolBarPanel->multiSensorButton->isChecked())
   {
    startMultiSensor();
   }
   else if (leToolBarPanel->sensorButton->isChecked())
   {
       addSensor();
   }
   else if (leToolBarPanel->signalButton->isChecked()) {
       addSignalHead();
   }
   else if (leToolBarPanel->textLabelButton->isChecked()) {
       addLabel();
   }
   else if (leToolBarPanel->memoryButton->isChecked()) {
       addMemory();
   }
   else if (leToolBarPanel->iconLabelButton->isChecked())
   {
        addIcon();
   }
   else if (leToolBarPanel->shapeButton->isChecked())
   {
    if (selectedObject == nullptr ) {
        addLayoutShape(currentPoint);
        setCursor(/*Cursor.getDefaultCursor()*/Qt::ArrowCursor);
    }
    else
    {
     if(qobject_cast<LayoutShape*>(selectedObject))
     {
        LayoutShape* ls = (LayoutShape*) selectedObject;
        ls->addPoint(currentPoint, selectedHitPointType - LayoutTrack::SHAPE_POINT_OFFSET_MIN);
     }
    }
   }
   else if (leToolBarPanel->signalMastButton->isChecked())
   {
        addSignalMast();
   }
   else
   {
    log->warn("No item selected in panel edit mode");
   }
   //resizePanelBounds(false);
   selectedObject = nullptr;
   //repaint();
   redrawPanel();
  }
  else if ( (bPopupTrigger || delayedPopupTrigger)  && !isDragging)
  {
   selectedObject = nullptr;
   selectedHitPointType = LayoutTrack::NONE;
   whenReleased = QDateTime::currentMSecsSinceEpoch();
   showEditPopUps(event);
  }
  else if ( ( selectedObject!=nullptr) && (selectedHitPointType==TURNOUT_CENTER)
             && allControlling() /*&& (!(event->modifiers()&Qt::ControlModifier))*/ /*&& (!(event->modifiers()&Qt::AltModifier)) *//*&& (!event.isPopupTrigger())*/
             && (!(event->modifiers()&Qt::ShiftModifier))
             && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
  else if ( ( selectedObject!=nullptr) && ((selectedHitPointType == LayoutTrack::SLIP_CENTER) ||
                                        (selectedHitPointType == LayoutTrack::SLIP_LEFT) ||
                                        (selectedHitPointType == LayoutTrack::SLIP_RIGHT))/* &&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleTurnout();
  }
  else if ( ( selectedObject!=nullptr) && (selectedHitPointType>=TURNTABLE_RAY_OFFSET) /*&&
               allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier) && (!event.isPopupTrigger())*/ &&
                   (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) )
  {
   // controlling layout, in edit mode
   LayoutTurntable* t =  (LayoutTurntable*)selectedObject;
   t->setPosition(selectedHitPointType-TURNTABLE_RAY_OFFSET);
  }
  else if ((selectedObject != nullptr) && (selectedHitPointType == LayoutTrack::TURNOUT_CENTER) /*&&
                         allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
                         (!event.isShiftDown()) && (!event.isControlDown()) && isDragging)*/
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
        //controlling layout, in edit mode
        hitPointCheckLayoutTurnouts((LayoutTurnout*) selectedObject);
  }
  else if ((selectedObject != nullptr) && (selectedHitPointType == LayoutTrack::POS_POINT) /*&&
               allControlling() && (event.isMetaDown()) && (!event.isAltDown()) &&
               (!event.isShiftDown()) && (!event.isControlDown()) && isDragging) */
           && (!(event->modifiers()&Qt::ShiftModifier)) && (!(event->modifiers()&Qt::ControlModifier)) && isDragging)
  {
    PositionablePoint* p = (PositionablePoint*) selectedObject;

    if ((p->getConnect1() == nullptr) || (p->getConnect2() == nullptr)) {
        checkPointOfPositionable(p);
    }
   }

   if ( (leToolBarPanel->trackButton->isChecked()) && (beginTrack!=nullptr) && (foundTrack!=nullptr) )
   {
    // user let up shift key before releasing the mouse when creating a track segment
    setCursor(Qt::ArrowCursor);
    beginTrack = nullptr;
    foundTrack = nullptr;
    //repaint();
    paintTargetPanel(editScene);
   }
   createSelectionGroups();
  }
  // check if controlling turnouts out of edit mode
  else if ( ( selectedObject!=nullptr) && (selectedHitPointType==TURNOUT_CENTER)
            && allControlling() && !isMetaDown && !isAltDown
            && !bShift && !delayedPopupTrigger )
  {
   // controlling layout, out of edit mode
   LayoutTurnout* t = (LayoutTurnout*)selectedObject;
   t->toggleTurnout();
  }
    // check if controlling turnouts out of edit mode
    else if ( ( selectedObject!=nullptr) && ((selectedHitPointType == LayoutTrack::SLIP_CENTER) ||
                                          (selectedHitPointType == LayoutTrack::SLIP_LEFT) ||
                                          (selectedHitPointType == LayoutTrack::SLIP_RIGHT)) /*&&
            allControlling() && (!event.isMetaDown())*/ && (!(event->modifiers()&Qt::AltModifier))/* && (!event.isPopupTrigger())*/ &&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   // controlling layout, not in edit mode
   LayoutSlip* t = (LayoutSlip*)selectedObject;
   t->toggleTurnout();
  }
#if 1
  else if ( ( selectedObject!=nullptr) && (selectedHitPointType>=TURNTABLE_RAY_OFFSET)/* &&
            allControlling() && (!event.isMetaDown()) && (!(event->modifiers()&Qt::AltModifier)) && (!event.isPopupTrigger())*/ &&
                (!(event->modifiers()&Qt::ShiftModifier)) && (!delayedPopupTrigger) )
  {
   LayoutTurntable*  t =  (LayoutTurntable*)selectedObject;
   t->setPosition(selectedHitPointType-TURNTABLE_RAY_OFFSET);
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
      switch (foundHitPointType)
      {
       case TURNOUT_CENTER:
        ((LayoutTurnout*)foundTrack)->showPopup(event);
        break;
       case LEVEL_XING_CENTER:
        ((LevelXing*)foundTrack)->showPopup(event);
        break;
       case SLIP_CENTER:
        ((LayoutSlip*)foundTrack)->showPopup(event);
        break;
       default: break;
      }
     }

     AnalogClock2Display* c = checkClockPopUps(dLoc);
     if (c!=nullptr)
     {
       showPopUp((Positionable*)c, event);
     }
     else
     {
      SignalMastIcon* sm = checkSignalMastIconPopUps(dLoc);
      if (sm!=nullptr)
      {
       showPopUp((Positionable*)sm, event);
      }
      else
      {
       PositionableLabel* im = checkLabelImagePopUps(dLoc);
       if(im!=nullptr)
       {
        showPopUp((Positionable*)im, event);
       }
    }
   }

   if (/*!event.isPopupTrigger() && */ !isDragging)
   {
    QList <Positionable*> selections = getSelectedItems(event);
    if (selections.size() > 0)
    {
     selections.at(0)->doMouseReleased(event);
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
   return;
  }
 }
}

/*private*/ void LayoutEditor::showEditPopUps(/*@Nonnull */QGraphicsSceneMouseEvent* event)
{
  if (findLayoutTracksHitPoint(dLoc))
  {
   if ((foundHitPointType >= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN)
           && (foundHitPointType <= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MAX)) {
       ((TrackSegment*) foundTrack)->showBezierPopUp(event, foundHitPointType);
   }
   else if (foundHitPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET) {
       LayoutTurntable* t = (LayoutTurntable*) foundTrack;
       if (t->isTurnoutControlled()) {
           ((LayoutTurntable*) foundTrack)->showRayPopUp(event, foundHitPointType - LayoutTrack::TURNTABLE_RAY_OFFSET);
       }
   }
   else if (LayoutTrack::isPopupHitType(foundHitPointType)) {
       foundTrack->showPopup(event);
   }
   else if ((foundHitPointType >= LayoutTrack::TURNOUT_A)
           && (foundHitPointType <= LayoutTrack::TURNOUT_D)) {
       // don't curently have edit popup for these
   }
   else {
       log->warn("Unknown foundPointType:" + QString::number(foundHitPointType));
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
          LayoutShape* ls = checkLayoutShapePopUps(dLoc);
          if (ls != nullptr) {
           ls->showShapePopUp(event, selectedHitPointType);
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
  if (p->isEditable())
  {
      QAction* jmi = nullptr;
      if (showAlignPopup())
      {
          setShowAlignmentMenu(popup);
          popup->addAction(jmi =new QAction(tr("Delete"),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent event) {
          connect(jmi, &QAction::triggered, [=]{
                  deleteSelectedItems();
          });
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
}

/*private*/ double LayoutEditor::returnDeltaPositionX(/*@Nonnull*/ QKeyEvent* event) {
    double result = 0.0;
    double amount = /*event->isShiftDown()*/event->modifiers()&Qt::ShiftModifier ? 5.0 : 1.0;

    switch (event->key()) {
        case Qt::Key_Left: {
            result = -amount;
            break;
        }

        case Qt::Key_Right: {
            result = +amount;
            break;
        }

        default: {
            break;
        }
    }
    return result;
}

/*private*/ double LayoutEditor::returnDeltaPositionY(/*@Nonnull*/ QKeyEvent* event) {
    double result = 0.0;
    double amount = /*event->isShiftDown()*/event->modifiers()&Qt::ShiftModifier ? 5.0 : 1.0;

    switch (event->key()) {
        case Qt::Key_Up: {
            result = -amount;
            break;
        }

        case Qt::Key_Down: {
            result = +amount;
            break;
        }

        default: {
            break;
        }
    }
    return result;
}


/*public*/ void LayoutEditor::mouseMoved(QGraphicsSceneMouseEvent* event)
{
 bool bMeta = event->modifiers()&Qt::MetaModifier;
 bool bAlt = event->modifiers()&Qt::AltModifier;
 bool bShift =  event->modifiers()&Qt::ShiftModifier;
 bool bPopupTrigger = event->button() & Qt::RightButton;
 bool bControl = event->modifiers()&Qt::ControlModifier;

 calcLocation(event);

 // if alt modifier is down invert the snap to grid behaviour
 snapToGridInvert = /*event.isAltDown()*/ bAlt;

 if (isEditable())
 {
  leToolBarPanel->xLabel->setText(QString::number(xLoc));
  leToolBarPanel->yLabel->setText(QString::number(yLoc));
 }
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
     redrawPanel();
     _prevNumSel = numSel;
 }
} // mouseMoved

//@Override
/*public*/ void LayoutEditor::mouseDragged(QGraphicsSceneMouseEvent* event)
{
 bool bMeta = event->modifiers()&Qt::MetaModifier;
 bool bAlt = event->modifiers()&Qt::AltModifier;
 bool bShift =  event->modifiers()&Qt::ShiftModifier;
 bool bPopupTrigger = event->button() & Qt::RightButton;
 bool bControl = event->modifiers()&Qt::ControlModifier;

 // initialize mouse position
 calcLocation(event);

 // ignore this event if still at the original point
 if ((!isDragging) && (xLoc == getAnchorX()) && (yLoc==getAnchorY()))
  return;

 // if alt modifier is down invert the snap to grid behaviour
 snapToGridInvert = /*event.isAltDown()*/ bAlt;

 // process this mouse dragged event
 if (isEditable())
 {
  leToolBarPanel->xLabel->setText(QString("%1").arg(xLoc));
  leToolBarPanel->yLabel->setText(QString("%1").arg(yLoc));
 }
 currentPoint = MathUtil::add(dLoc, startDelta);
 //don't allow negative placement, objects could become unreachable
 currentPoint = MathUtil::max(currentPoint, MathUtil::zeroPoint2D);

 if ((selectedObject != nullptr) && ((bMeta || bAlt)
                                   && (selectedHitPointType==MARKER)))
 {
   // marker moves regardless of editMode or positionable
   PositionableLabel* pl = (PositionableLabel*)selectedObject;
   pl->setLocation((int)currentPoint.x(), (int)currentPoint.y());
   isDragging = true;
   //repaint();
   pl->updateScene();
   //paintTargetPanel(editScene);
   pl->paint(editScene);
   return;
  }

  if (isEditable())
  {
   if ((selectedObject != nullptr) /*&& bMeta*/ && allPositionable())
   {
    if (snapToGridOnMove != snapToGridInvert)
    {
      // this snaps currentPoint to the grid
      currentPoint = MathUtil::granulize(currentPoint, gContext->getGridSize());
      xLoc = (int) currentPoint.x();
      yLoc = (int) currentPoint.y();
      leToolBarPanel->xLabel->setText(QString::number(xLoc));
      leToolBarPanel->yLabel->setText(QString::number(yLoc));
    }

    if ((_positionableSelection && _positionableSelection->size() > 0)
        || (_layoutTrackSelection.size() > 0)
        || (_layoutShapeSelection.size() > 0))
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
           ((PositionableLabel*)c->self())->setLocation((int)currentPoint.x(), (int)currentPoint.y());
           ((PositionableLabel*)c->self())->updateScene();
       }

       for (LayoutTrack* lt : _layoutTrackSelection) {
           QPointF center = lt->getCoordsCenter();
           newPoint = MathUtil::add(center, offset);
           //don't allow negative placement, objects could become unreachable
           newPoint = MathUtil::max(newPoint, MathUtil::zeroPoint2D);
           lt->setCoordsCenter(newPoint);
       }

       for (LayoutShape* ls : _layoutShapeSelection)
       {
           QPointF center = ls->getCoordsCenter();
           newPoint = MathUtil::add(center, offset);
           //don't allow negative placement, objects could become unreachable
           newPoint = MathUtil::max(newPoint, MathUtil::zeroPoint2D);
           ls->setCoordsCenter(newPoint);
       }
       _lastX = xLoc;
       _lastY = yLoc;
    }
    else
    {
       switch (selectedHitPointType) {
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

               if (pl && pl->isPositionable()) {
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

           default:
           {
               if ((foundHitPointType >= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN)
                       && (foundHitPointType <= LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MAX)) {
                   int index = selectedHitPointType - LayoutTrack::BEZIER_CONTROL_POINT_OFFSET_MIN;
                   ((TrackSegment*) selectedObject)->setBezierControlPoint(currentPoint, index);
               }
               else if ((selectedHitPointType == LayoutTrack::SHAPE_CENTER))
               {
                   ((LayoutShape*) selectedObject)->setCoordsCenter(currentPoint);
               }
               else if (LayoutShape::isShapePointOffsetHitPointType(selectedHitPointType))
               {
                   int index = selectedHitPointType - LayoutTrack::SHAPE_POINT_OFFSET_MIN;
                   ((LayoutShape*) selectedObject)->setPoint(index, currentPoint);
               }
               else if (selectedHitPointType >= LayoutTrack::TURNTABLE_RAY_OFFSET)
               {
                   LayoutTurntable* turn = (LayoutTurntable*) selectedObject;
                   turn->setRayCoordsIndexed(currentPoint.x(), currentPoint.y(),
                           selectedHitPointType - LayoutTrack::TURNTABLE_RAY_OFFSET);
               }
               break;
           }
       }
   }
  }
  else if ( (beginTrack!=nullptr)
            && bShift
            && leToolBarPanel->trackButton->isChecked() )
  {
   // dragging from first end of Track Segment
   currentLocation= QPointF(xLoc,yLoc);
   bool needResetCursor = (foundTrack!=nullptr);
   if (findLayoutTracksHitPoint(currentLocation, true))
   {
   // have match to free connection point, change cursor
   //setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
    setCursor(Qt::CrossCursor);
   }
   else if (needResetCursor)
   {
    setCursor(Qt::ArrowCursor);
   }
   //repaint();
   paintTargetPanel(editScene);
  }
  else if ( selectionActive && (!bShift) && (!bAlt) /*&& (!event.isMetaDown())*/ )
  {
   selectionWidth = xLoc - selectionX;
   selectionHeight = yLoc - selectionY;
   //repaint();
   paintTargetPanel(editScene);
  }
 }
  else if (/*event.isShiftDown()*/ (bShift)
         && leToolBarPanel->shapeButton->isChecked() && (selectedObject != nullptr)) {
     //dragging from end of shape
     currentLocation = QPointF(xLoc,yLoc);
 }
 else if (selectionActive && !(bShift) && (!bMeta))
 {
  QRect r =  QRect(event->scenePos().x(), event->scenePos().y(), 1, 1);
      //((JComponent) event->getSource()).scrollRectToVisible(r);
  Q_UNUSED(r);
 }  // isEditable
 return;
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
 QMenu* zoomMenu = new QMenu(tr("Zoom"));
 menuBar->addMenu(zoomMenu);
 QActionGroup* zoomButtonGroup = new QActionGroup(this);

 //add zoom choices to menu
 QAction* zoomInItem = new QAction(tr("Zoom In"),this);
 //zoomInItem.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("zoomInMnemonic")));
 QString zoomInAccelerator = tr("EQUALS");
 //log.debug("zoomInAccelerator: " + zoomInAccelerator);
 //zoomInItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(zoomInAccelerator), primary_modifier));
 zoomMenu->addAction(zoomInItem);
// zoomInItem.addActionListener((ActionEvent event) -> {
 connect(zoomInItem, &QAction::triggered, [=]{
     //zoomIn();
  return setZoom(getZoom() * 1.1);
 });

 QAction* zoomOutItem = new QAction(tr("Zoom Out"));
// zoomOutItem.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("zoomOutMnemonic")));
// String zoomOutAccelerator = Bundle.getMessage("zoomOutAccelerator");
 //log.debug("zoomOutAccelerator: " + zoomOutAccelerator);
// zoomOutItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(zoomOutAccelerator), primary_modifier));
 zoomMenu->addAction(zoomOutItem);
// zoomOutItem.addActionListener((ActionEvent event) -> {
 connect(zoomOutItem, &QAction::triggered, [=]{
//     zoomOut();
  return setZoom(getZoom() / 1.1);
 });

 QAction* zoomFitItem = new QAction(tr("Zoom To Fit"));
 zoomMenu->addAction(zoomFitItem);
// zoomFitItem.addActionListener((ActionEvent event) -> {
 connect(zoomFitItem, &QAction::triggered, [=]{
     zoomToFit();
 });
 zoomMenu->addSeparator();

 zoomButtonGroup->setExclusive(true);
 // add zoom choices to menu
 QAction* zoom025Item = new QAction("x 0.25", this);
 zoom025Item->setCheckable(true);
 zoomMenu->addAction(zoom025Item);
// zoom025Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom025Item, &QAction::triggered, [=]{
         setZoom(0.25);
//     }
 });
 zoomButtonGroup->addAction(zoom025Item);
 QAction* zoom05Item = new QAction("x 0.5", this);
 zoom05Item->setCheckable(true);
 zoomMenu->addAction(zoom05Item);
// zoom05Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom05Item, &QAction::triggered, [=]{
         setZoom(0.5);
//     }
 });
 zoomButtonGroup->addAction(zoom05Item);
 QAction* zoom075Item = new QAction("x 0.75", this);
 zoom075Item->setCheckable(true);
 zoomMenu->addAction(zoom075Item);
// zoom075Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom075Item, &QAction::triggered, [=]{
         setZoom(0.75);
//     }
 });
 zoomButtonGroup->addAction(zoom075Item);
 QAction* noZoomItem = new QAction(tr("No Zoom"), this);
 noZoomItem->setCheckable(true);
 zoomMenu->addAction(noZoomItem);
// noZoomItem.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(noZoomItem, &QAction::triggered, [=]{

//         setZoom(1.0);
  setZoom(1.0/ getZoomRatio());
//     }
 });
 zoomButtonGroup->addAction(noZoomItem);
 QAction* zoom15Item = new QAction("x 1.5", this);
 zoom15Item->setCheckable(true);
 zoomMenu->addAction(zoom15Item);
// zoom15Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom15Item, &QAction::triggered, [=]{
         setZoom(1.5);
//     }
 });
 zoomButtonGroup->addAction(zoom15Item);
 QAction* zoom20Item = new QAction("x 2.0",this);
 zoom20Item->setCheckable(true);
 zoomMenu->addAction(zoom20Item);
// zoom20Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom20Item, &QAction::triggered, [=]{
         setZoom(2.0);
//     }
 });
 zoomButtonGroup->addAction(zoom20Item);
 QAction* zoom30Item = new QAction("x 3.0", this);
 zoomMenu->addAction(zoom30Item);
// zoom30Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom30Item, &QAction::triggered, [=]{
         setZoom(3.0);
//     }
 });
 zoomButtonGroup->addAction(zoom30Item);
 QAction* zoom40Item = new QAction("x 4.0", this);
 zoomMenu->addAction(zoom40Item);
// zoom40Item.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent event) {
 connect(zoom40Item, &QAction::triggered, [=]{
         setZoom(4.0);
//     }
 });
 zoomButtonGroup->addAction(zoom40Item);
 noZoomItem->setChecked(true);
}

/*public*/ double LayoutEditor::setZoom(double zoomFactor) {
    //TODO: add code to re-calculate minZoom (so panel never smaller than view)
    double newZoom = MathUtil::pin(zoomFactor, minZoom, maxZoom);
    selectZoomMenuItem(newZoom);

    if (!MathUtil::equals(newZoom, getPaintScale())) {
        log->debug(tr("zoom: %1").arg(zoomFactor));
        setPaintScale(newZoom);
//        adjustScrollBars();

        leToolBarPanel->zoomLabel->setText(QString().sprintf("x%0.2f", getZoomRatio()));

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

//
// TODO: make this public? (might be useful!)
//
/*private*/ QRectF LayoutEditor::calculateMinimumLayoutBounds() {

 return editScene->sceneRect();
}

//void LayoutEditor::onCalculateBounds()
//{
// QRectF bounds = calculateMinimumLayoutBounds();
// log->info(tr("calculated bounds = %1 %2 %3 %4").arg(bounds.x()).arg(bounds.y()).arg(bounds.width()).arg(bounds.height()));
// log->info(tr("scene bounds = %1 %2 %3 %4").arg(editScene->itemsBoundingRect().x()).arg(editScene->itemsBoundingRect().y()).arg(editScene->itemsBoundingRect().width()).arg(editScene->itemsBoundingRect().height()));
//}

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
    if(result == gContext->getXScale())
     return result;
//    if(xScale > 1.0)
//     editPanel->scale(1.0/xScale, 1.0/yScale);

    editPanel->scale(result, result);
    //xScale = yScale = result;
   gContext->setXScale(result);
   gContext->setYScale(result);
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
 newTrack = new TrackSegment(name,(LayoutTrack*)beginTrack,beginHitPointType,
                 (LayoutTrack*)foundTrack,foundHitPointType,leToolBarPanel->dashedLine->isChecked(), leToolBarPanel->mainlineTrack->isChecked(),this);
 if (newTrack!=nullptr)
 {
  layoutTrackList->append(newTrack);
  unionToPanelBounds(newTrack->getBounds());
  setDirty(true);
  // link to connected objects
  setLink(newTrack,TRACK,beginTrack,beginHitPointType);
  setLink(newTrack,TRACK,foundTrack,foundHitPointType);
  // check on layout block
  LayoutBlock* b = provideLayoutBlock(leToolBarPanel->blockLabel->text().trimmed());
  if (b!=nullptr)
  {
   newTrack->setLayoutBlock(b);
   auxTools->setBlockConnectivityChanged();
   // check on occupancy sensor
   QString sensorName = (leToolBarPanel->blockSensorLabel->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b,(Component*)this))
    {
     b->setOccupancySensorName("");
    }
    else
    {
     leToolBarPanel->blockSensorLabel->setText( b->getOccupancySensorName() );
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
  LayoutBlock* b = provideLayoutBlock(leToolBarPanel->blockLabel->text().trimmed());
  if (b!=nullptr)
  {
   o->setLayoutBlockAC(b);
   o->setLayoutBlockBD(b);
   // check on occupancy sensor
   QString sensorName = (leToolBarPanel->blockSensorLabel->text().trimmed());
   if (sensorName.length()>0)
   {
    if (!validateSensor(sensorName,b,(Component*)this))
    {
     b->setOccupancySensorName("");
    }
    else {
     leToolBarPanel->blockSensorLabel->setText( b->getOccupancySensorName() );
    }
   }
  }
 }
}

/**
 * Add a LayoutSlip
 */
/*public*/ void LayoutEditor::addLayoutSlip(LayoutTurnout::TurnoutType type)
{
 double rot = 0.0;
 QString s = leToolBarPanel->rotationComboBox->currentText().trimmed();
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
 LayoutSlip* o;
 switch(type) {
     case LayoutTurnout::TurnoutType::DOUBLE_SLIP :
         o = new LayoutDoubleSlip(name, currentPoint, rot, this);
         break;
     case LayoutTurnout::TurnoutType::SINGLE_SLIP :
         o = new LayoutSingleSlip(name, currentPoint, rot, this);
         break;
     default:
         log->error(tr("can't create slip %1 with type %2").arg(name).arg(type));
         return; // without creating
 }

 addLayoutTrack(o);
 setDirty();

 // check on layout block
 QString newName = leToolBarPanel->blockIDComboBox->currentText();
 LayoutBlock* b = provideLayoutBlock(leToolBarPanel->blockLabel->text().trimmed());
 if (b != nullptr)
 {
     o->setLayoutBlock(b);

     //check on occupancy sensor
     QString sensorName = leToolBarPanel->blockSensorComboBox->getSelectedItemDisplayName();
                 if (sensorName.isNull()) {
                     sensorName = "";
                 }

     if (!sensorName.isEmpty()) {
         if (!validateSensor(sensorName, b, (Component*)this)) {
             b->setOccupancySensorName("");
         } else {
             leToolBarPanel->blockSensorComboBox->setSelectedItemByName(b->getOccupancySensorName());
         }
     }
 }

 QString turnoutName = leToolBarPanel->turnoutNameComboBox->currentText();

 if (validatePhysicalTurnout(turnoutName, this)) {
     //turnout is valid and unique.
     o->setTurnout(turnoutName);

     if (o->getTurnout()->getSystemName() == (turnoutName.toUpper())) {
         leToolBarPanel->turnoutNameComboBox->setSelectedItemByName(turnoutName.toUpper());
     }
 } else {
     o->setTurnout("");
     leToolBarPanel->turnoutNameComboBox->setSelectedItemByName("");
     leToolBarPanel->turnoutNameComboBox->setCurrentIndex(-1);
 }
 turnoutName = leToolBarPanel->extraTurnoutNameComboBox->getSelectedItemDisplayName();

 if (validatePhysicalTurnout(turnoutName, this)) {
     //turnout is valid and unique.
     o->setTurnoutB(turnoutName);

     if (o->getTurnoutB()->getSystemName()==(turnoutName.toUpper())) {
         leToolBarPanel->extraTurnoutNameComboBox->setSelectedItemByName(turnoutName.toUpper());
     }
 } else {
     o->setTurnoutB("");
     leToolBarPanel->extraTurnoutNameComboBox->setSelectedItemByName("");
     leToolBarPanel->extraTurnoutNameComboBox->setCurrentIndex(-1);
 }
}

/**
 * Add a Layout Turnout
 */
/*public*/ void LayoutEditor::addLayoutTurnout(int type)
{
 // get the rotation entry
 double rot = 0.0;
 QString s = leToolBarPanel->rotationComboBox->currentText().trimmed();
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
 // create object - check all types, although not clear all actually reach here
 LayoutTurnout* o;
 switch(type) {

     case LayoutTurnout::RH_TURNOUT :
         o = new LayoutRHTurnout(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;
     case LayoutTurnout::LH_TURNOUT :
         o = new LayoutLHTurnout(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;
     case LayoutTurnout::WYE_TURNOUT :
         o = new LayoutWye(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;
     case LayoutTurnout::DOUBLE_XOVER :
         o = new LayoutDoubleXOver(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;
     case LayoutTurnout::RH_XOVER :
         o = new LayoutRHXOver(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;
     case LayoutTurnout::LH_XOVER :
         o = new LayoutLHXOver(name, currentPoint, rot, gContext->getXScale(), gContext->getYScale(), this);
         break;

     case LayoutTurnout::DOUBLE_SLIP :
         o = new LayoutDoubleSlip(name, currentPoint, rot, this);
         log->error(tr("Found SINGLE_SLIP in addLayoutTurnout for element %1").arg(name));
         break;
     case LayoutTurnout::SINGLE_SLIP :
         o = new LayoutSingleSlip(name, currentPoint, rot, this);
         log->error(tr("Found SINGLE_SLIP in addLayoutTurnout for element %1").arg(name));
         break;

     default:
         log->error(tr("can't create LayoutTrack %1 with type %2").arg(name).arg(type));
         return; // without creating
 }

 addLayoutTrack(o);
 setDirty();

 // check on layout block
 QString newName = leToolBarPanel->blockIDComboBox->getSelectedItemDisplayName();
 if (newName.isNull()) {
     newName = "";
 }
 LayoutBlock* b = provideLayoutBlock(newName);

 if (b != nullptr) {
     o->setLayoutBlock(b);

     // check on occupancy sensor
     QString sensorName = leToolBarPanel->blockSensorComboBox->getSelectedItemDisplayName();
     if (sensorName.isNull()) {
         sensorName = "";
     }

     if (!sensorName.isEmpty()) {
         if (!validateSensor(sensorName, b, this)) {
             b->setOccupancySensorName("");
         } else {
             leToolBarPanel->blockSensorComboBox->setSelectedItem(b->getOccupancySensor());
         }
     }
 }

 // set default continuing route Turnout State
 o->setContinuingSense(Turnout::CLOSED);

 // check on a physical turnout
 QString turnoutName = leToolBarPanel->turnoutNameComboBox->getSelectedItemDisplayName();
 if (turnoutName.isNull()) {
     turnoutName = "";
 }

 if (validatePhysicalTurnout(turnoutName, this)) {
     // turnout is valid and unique.
     o->setTurnout(turnoutName);

     if (o->getTurnout()->getSystemName() == (turnoutName)) {
         leToolBarPanel->turnoutNameComboBox->setSelectedItem(o->getTurnout());
     }
 } else {
     o->setTurnout("");
     leToolBarPanel->turnoutNameComboBox->setSelectedItem(nullptr);
     leToolBarPanel->turnoutNameComboBox->setCurrentIndex(-1);
 }
}

//LayoutTurnout* LayoutEditor::addLayoutTurnout(QString name, int type, double rot, QPointF currentPoint)
//{
// // create object
// LayoutTurnout* o = new LayoutTurnout(name,type,                                   currentPoint,rot,xScale,yScale,this);
// //if (o!=nullptr) {
// //turnoutList->append(o);
// layoutTrackList->append(o);
// setDirty(true);
// // check on layout block
// LayoutBlock* b = provideLayoutBlock(leToolBarPanel->blockLabel->text().trimmed());
// if (b!=nullptr)
// {
//  o->setLayoutBlock(b);
//  // check on occupancy sensor
//  QString sensorName = (leToolBarPanel->blockSensorLabel->text().trimmed());
//  if (sensorName.length()>0)
//  {
//   if (!validateSensor(sensorName,b,(Component*)this))
//   {
//    b->setOccupancySensorName("");
//   }
//   else
//   {
//    leToolBarPanel->blockSensorLabel->setText( b->getOccupancySensorName() );
//   }
//  }
// }
// // set default continuing route Turnout State
// o->setContinuingSense(Turnout::CLOSED);
// // check on a physical turnout
// QString turnoutName = leToolBarPanel->turnoutNameComboBox->currentText().trimmed();
// if ( validatePhysicalTurnout(turnoutName/*, this*/) )
// {
//  // turnout is valid and unique.
//  o->setTurnout(turnoutName);
//  if (o->getTurnout()->getSystemName()==(turnoutName.toUpper()))
//  {
//   leToolBarPanel->turnoutNameComboBox->setSelectedItemByName(turnoutName.toUpper());
//  }
// }
// else
// {
//  o->setTurnout("");
//  leToolBarPanel->turnoutNameComboBox->setSelectedItemByName("");
// }
// return o;
//}

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
   if((si = static_cast<SensorIcon*>(c->self()))!=nullptr)
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
    QPointF coord = p->getCoordsCenter();
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
  QRectF selectionRect = getSelectionRect();
  for (Positionable* o : contents)
  {
   if (selectionRect.contains(o->getLocation()))
   {
    if (!_positionableSelection->contains(o))
    {
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
 assignBlockToSelectionMenuItem->setEnabled(_layoutTrackSelection.size() > 0);

 //layoutShapes.forEach((ls) ->
 foreach(LayoutShape* ls, *layoutShapes)
 {
     if (selectionRect.intersects(ls->getBounds())) {
         if (!_layoutShapeSelection.contains(ls)) {
             _layoutShapeSelection.append(ls);
         }
     }
 }//);
 redrawPanel();
}


/*public*/ void LayoutEditor::clearSelectionGroups(){
  selectionActive = false;
  _positionableSelection->clear();
  _layoutTrackSelection.clear();
  assignBlockToSelectionMenuItem->setEnabled(false);
  _layoutShapeSelection.clear();
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

   //rect= ((PositionableLabel*)p)->getBounds();
   rect = p->getBounds();
   //if (_debug && !_dragging) log->debug("getSelectedItems: rect= ("+rect.x+","+rect.y+
   //                      ") width= "+rect.width+", height= "+rect.height+
   //                                    " isPositionable= "+p.isPositionable());
   QRectF rect2D(rect.x()*_paintScale, rect.y()*_paintScale, rect.width()*_paintScale,                                                        rect.height()*_paintScale);
   if (rect2D.contains(x, y) && (p->getDisplayLevel()>BKG || event->modifiers()&Qt::ControlModifier))
   {
    //qDebug() << tr("rect %1,%2,%3,%4 contains %5,%6").arg(rect2D.x()).arg(rect2D.y()).arg(rect2D.width()).arg(rect2D.height()).arg(x).arg(y);
    bool added =false;
    int level = p->getDisplayLevel();
    for (int k=0; k<selections->size(); k++)
    {
     if (level >= selections->at(k)->getDisplayLevel())
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
/*public*/ bool LayoutEditor::validateSensor(QString sensorName, LayoutBlock* blk, QWidget* openFrame)
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
  turnoutBX = LayoutTurnout::turnoutBXDefault;
  turnoutCX = LayoutTurnout::turnoutCXDefault;
  turnoutWid = LayoutTurnout::turnoutWidDefault;
  xOverLong = LayoutTurnout::xOverLongDefault;
  xOverHWid = LayoutTurnout::xOverHWidDefault;
  xOverShort = LayoutTurnout::xOverShortDefault;
  setDirty(true);
}

/*public*/ double LayoutEditor::getXScale() {return gContext->getXScale();}

/*public*/ double LayoutEditor::getYScale() {return gContext->getYScale();}

//    public Color getDefaultBackgroundColor() {
//        return defaultBackgroundColor;
//    }
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

//@Nonnull
/*public*/ QString LayoutEditor::getTurnoutCircleThrownColor() {
    return ColorUtil::colorToColorName(turnoutCircleThrownColor);
}

/*public*/ bool LayoutEditor::isTurnoutFillControlCircles() {
        return turnoutFillControlCircles;
    }

/*public*/ int LayoutEditor::getTurnoutCircleSize() {
    return turnoutCircleSize;
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
#if 0
/*static*/ /*protected*/ QPointF LayoutEditor::getCoords(QObject* o, int type)
{
 if (o != nullptr)
 {
  switch (type)
  {
  case POS_POINT:
      return ((PositionablePoint*)o)->getCoordsCenter();
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
#endif
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
//@Override
/*public*/ void LayoutEditor::paintTargetPanel(EditScene* g2)
{
#if 0
 if (qobject_cast<EditScene*>(g2))
 {
     //layoutEditor.draw((Graphics2D) g);

     //Graphics2D g2 = (Graphics2D) g;

//     if (clipBounds.isNull()) {
//         if (!clipBounds == (g2->getClipBounds())) {
//             g2.setClip(clipBounds);
//         }
//     }
     //Optional antialising, to eliminate (reduce) staircase on diagonal lines
      editPanel->setRenderHint(QPainter::Antialiasing, antialiasingOn);

     //drawPositionableLabelBorder(g2);
     // things that only get drawn in edit mode
     if (/*layoutEditor.*/isEditable()) {
         if (/*layoutEditor.*/getDrawGrid()) {
             drawPanelGrid(g2);
         }
         drawLayoutTracksHidden(g2);
     }

     drawShapes(g2, true);
     drawTrackSegmentsDashed(g2);
     drawLayoutTracksBallast(g2);
     drawLayoutTracksTies(g2);
     drawLayoutTracksRails(g2);
     drawLayoutTracksBlockLines(g2);

     drawPositionablePoints(g2, false);
     drawPositionablePoints(g2, true);

     drawShapes(g2, false);

     drawDecorations(g2);

     // things that only get drawn in edit mode
     if (/*layoutEditor.*/isEditable()) {
         drawLayoutTrackEditControls(g2);
         drawShapeEditControls(g2);

         drawMemoryRects(g2);
         drawBlockContentsRects(g2);

         if (/*layoutEditor.*/allControlling()) {
             drawTurnoutControls(g2);
         }
         drawSelectionRect(g2);
         highLightSelection(g2);

         drawTrackSegmentInProgress(g2);
         drawShapeInProgress(g2);
     } else if (/*layoutEditor.*/turnoutCirclesWithoutEditMode) {
         if (/*layoutEditor.*/allControlling()) {
             drawTurnoutControls(g2);
         }
     }
 }
#else // new draw routines
 if(layoutEditorComponent == nullptr)
  layoutEditorComponent = new LayoutEditorComponent(this);
 layoutEditorComponent->paintTargetPanel(g2);
#endif
}

//
// this is called by the layoutEditorComponent
//
#if 0
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
    foreach (LayoutShape* ls, *layoutShapes) {
     ls->draw(editScene);
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

        foreach (LayoutShape* ls, *layoutShapes) {
         ls->drawEditControls(editScene);
        }

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
    draw1(g2, main, block, hidden, dashed/*,LayoutTrack::track*/);
    //g2.setStroke(dashedStroke);
    dashedStroke.setColor(ltdo->getSideRailColor());
    drawingStroke = dashedStroke;
    draw1(g2, main, block, hidden, dashed = true/*,LayoutTrack::track*/);

    //setup for drawing mainline rails
    main = true;
    //g2.setColor(ltdo->getMainRailColor());
    stroke.setColor(ltdo->getMainRailColor());
    //g2.setStroke(stroke);
    drawingStroke = stroke;
    draw1(g2, main, block, hidden, dashed = false/*, LayoutTrack::track*/);
    //g2.setStroke(dashedStroke);
    dashedStroke.setColor(ltdo->getMainRailColor());
    drawingStroke = dashedStroke;
    dashed = true;
    draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
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
            draw1(g2, main, block, hidden/*, LayoutTrack::dashed*/);
        }
        if (ltdo->getSideRailCount() >= 2) {
            float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
            draw2(g2, main, railDisplacement/*, LayoutTrack::dashed*/);
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
            draw1(g2, main, block, hidden, dashed/*, LayoutTrack::dashed*/);
        }
        if (ltdo->getMainRailCount() >= 2) {
            float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
            draw2(g2, main, railDisplacement/*, LayoutTrack::dashed*/);
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
        draw1(g2, main, block, hidden, dashed/*, LayoutTrack::ballast*/);
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
        draw1(g2, main, block, hidden, dashed/*,LayoutTrack::ballast*/);
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
        draw2(g2, main, railDisplacement/*, LayoutTrack::track*/);
    }

    if ((ltdo->getSideRailCount() & 1) == 1) {
        //setup for drawing sideline rails
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
     QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     drawingStroke = stroke;
     draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
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
        draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
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
    draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
    //g2.setStroke(blockLineStroke);
    drawingStroke = blockLineStroke;
    draw1(g2, main, block, hidden, dashed = false/*,LayoutTrack::track*/);

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
    draw1(g2, main = true, block, hidden, dashed = true/*,LayoutTrack::track*/);
    //g2.setStroke(blockLineStroke);
    drawingStroke = blockLineStroke;
    dashed = false;
    draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
}

// isDashed defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden/*, LayoutTrack::ITEMTYPE type*/) {
    draw1(g2, isMain, isBlock, isHidden, false/*, type*/);
}

// isHidden defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock/*, LayoutTrack::ITEMTYPE type*/) {
    draw1(g2, isMain, isBlock, false/*, type*/);
}

// isBlock defaults to false
/*private*/ void LayoutEditor::draw1(EditScene* g2, bool isMain) {
    draw1(g2, isMain, false/*, type*/);
}

// draw single line (ballast, ties & block lines)
/*private*/ void LayoutEditor::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden,
        bool isDashed/*, LayoutTrack::ITEMTYPE itemType*/)
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
      layoutTrack->draw1(g2, isMain, isBlock/*, itemType*/);
     }
    }
    else if (!isDashed)
    {
     layoutTrack->draw1(g2, isMain, isBlock/*, itemType*/);
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
      layoutTrack->draw1(g2, isMain, false/*, LayoutTrack::points*/);
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
       layoutTrack->draw2(g2, isMain, railDisplacement/*, LayoutTrack::dashed*/ );
   }
  } else if (!isDashed) {
      layoutTrack->draw2(g2, isMain, railDisplacement/*, LayoutTrack::track*/ );
  }
 }
}
#endif
// draw decorations
/*private*/ void LayoutEditor::drawDecorations(EditScene* g2) {
    for (LayoutTrack* tr : *layoutTrackList) {
        tr->drawDecorations(g2);
    }
}

// draw shapes
/*private*/ void LayoutEditor::drawShapes(EditScene* g2, bool isBackground) {
    //layoutEditor.getLayoutShapes().forEach((s) ->
 foreach(LayoutShape* s, *getLayoutShapes())
 {
     if (isBackground == (s->getLevel() < 3)) {
         s->draw(g2);
     }
 }//);
}

// draw track segment (in progress)
/*private*/ void LayoutEditor::drawTrackSegmentInProgress(EditScene* g2) {
    //check for segment in progress
    if (isEditable() && (beginTrack != nullptr) && leToolBarPanel->trackButton->isChecked()) {
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
            if (lt != beginTrack) {
                if (lt == foundTrack) {
                    lt->highlightUnconnected(g2);
//                    g2.setColor(connectColor);
                    drawingStroke.setColor(connectColor);
                    lt->highlightUnconnected(g2, foundHitPointType);
//                    g2.setColor(highlightColor);
                    drawingStroke.setColor(highlightColor);
                } else {
                    lt->highlightUnconnected(g2);
                }
            }
        }
    }
}

// draw shape (in progress)
/*private*/ void LayoutEditor::drawShapeInProgress(EditScene* g2)
{
 //check for segment in progress
 if (/*layoutEditor.*/getLayoutEditorToolBarPanel()->shapeButton->isChecked())
 {
  //log.warn("drawShapeInProgress: selectedObject: " + selectedObject);
  if ((/*layoutEditor.*/selectedObject != nullptr)) {
//      g2.setColor(Color.DARK_GRAY);
//      g2.setStroke(new BasicStroke(3.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//      g2.draw(new Line2D.Double(layoutEditor.beginLocation, layoutEditor.currentLocation));
   QPen stroke = QPen(QColor(Qt::darkGray), 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
   drawingStroke = stroke;
   QGraphicsLineItem* item = new QGraphicsLineItem(beginLocation.x(), beginLocation.y(), currentLocation.x(), currentLocation.y());
   item->setPen(stroke);

   g2->addItem(item);
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

/*private*/ void LayoutEditor::drawShapeEditControls(EditScene* g2) {
    //g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(turnoutCircleColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 drawingStroke = stroke;

 //layoutEditor.getLayoutShapes().forEach((s) ->
 foreach(LayoutShape* s, *getLayoutShapes())
 {
     s->drawEditControls(g2);
 }//);
}

// draw layout turnout controls
/*private*/ void LayoutEditor::drawTurnoutControls(EditScene* g2) {
//    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//    g2.setColor(turnoutCircleColor);
 QPen stroke = QPen(turnoutCircleColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 //g2.setBackground(layoutEditor.turnoutCircleThrownColor);
 g2->setBackgroundBrush(QBrush(turnoutCircleThrownColor));

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

/*private*/ QList<LayoutTrack *> *LayoutEditor::getLayoutTracksOfClass(QString type)
{
 QList<LayoutTrack*>* list = new QList<LayoutTrack*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(QString(lt->metaObject()->className()) == type)
   list->append(lt);
 }
 return list;
}

/*@Nonnull*/
/*public*/ QList<PositionablePointView*> LayoutEditor::getPositionablePointViews() {
    QList<PositionablePointView*> list = QList<PositionablePointView*>();
    for (PositionablePoint* p : getPositionablePoints()) {
        list.append(new PositionablePointView(p));
    }
    return list;
}

/*public*/ QList<PositionablePoint*> LayoutEditor::getPositionablePoints()
{
    //return getLayoutTracksOfClass("PositionablePoint");
 QList<LayoutTrack*>* list1 = getLayoutTracksOfClass("PositionablePoint");
 QList<PositionablePoint*> list = QList<PositionablePoint*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<PositionablePoint*>(lt))
   list.append((PositionablePoint*)lt);
 }
 if(list.size() != list1->size())
  log->debug(tr("list sizes differ"));
 return list;
//    )
//            .map(PositionablePoint.class::cast)
//            .collect(Collectors.toCollection(ArrayList<PositionablePoint>::new));
}

#if 0
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
#endif
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
  LayoutTrack* t =layoutTrackList->t(i);
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
 if (_positionableSelection->contains(p)) {
     _positionableSelection->removeOne(p);
 } else {
     _positionableSelection->append(p);
 }
 redrawPanel();
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

/*protected*/ void LayoutEditor::amendSelectionGroup(/*@Nonnull*/ LayoutShape* ls) {
    if (_layoutShapeSelection.contains(ls)) {
        _layoutShapeSelection.removeOne(ls);
    } else {
        _layoutShapeSelection.append(ls);
    }
    redrawPanel();
}
/************************ Options setup **********************/
/**
*  Control whether target panel items are editable.
*  Does this by invoke the {@link Positionable#setEditable(bool)} function of
*  each item on the target panel. This also controls the relevant pop-up menu items
*  (which are the primary way that items are edited).
* @param state true for editable.
*/
/*public*/ void LayoutEditor::setAllEditable(bool editable)
{
  int restoreScroll = _scrollState;

  Editor::setAllEditable(editable);

  if (toolBarSide->getType() == eFLOAT)
  {
     if (editable) {
         createfloatingEditToolBoxFrame();
         createFloatingHelpPanel();
     } else {
         deletefloatingEditToolBoxFrame();
     }
  }
  else {
   if(editToolBarContainerPanel /*&& (editToolBarContainerPanel->isVisible())*/)
   {
     editToolBarContainerPanel->setVisible(editable);
//     if(editable)
//     {
//      switch (toolBarSide->getType()) {
//      case eTOP:
//       borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::North);
//       break;
//      case eBOTTOM:
//       borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::South);
//       break;
//      case eLEFT:
//       borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::West);
//       break;
//      case eRIGHT:
//       borderLayout->addWidget(editToolBarContainerPanel, BorderLayout::East);
//       break;
//      default:
//       break;
//      }
//     }
//     else
//      borderLayout->removeWidget(editToolBarContainerPanel);
   }
 }
 setShowHidden(editable);

 if (editable) {
     setScroll(Editor::SCROLL_BOTH);
     _scrollState = restoreScroll;
 } else {
     setScroll(_scrollState);
 }

 //these may not be set up yet...
 if (helpBarPanel != nullptr) {
     if (toolBarSide->getType() ==eFLOAT) {
         if (floatEditHelpPanel != nullptr) {
             floatEditHelpPanel->setVisible(isEditable() && getShowHelpBar());
         }
     } else {
         helpBarPanel->setVisible(editable && getShowHelpBar());
     }
 }
 awaitingIconChange = false;
 editModeCheckBoxMenuItem->setChecked(editable);
 redrawPanel();
}


/**
 * Control whether target panel items are controlling layout items. Does
 * this by invoke the {@link Positionable#setControlling} function of each
 * item on the target panel. This also controls the relevant pop-up menu
 * items.
 *
 * @param state true for controlling.
 */
/*public*/ void LayoutEditor::setTurnoutAnimation(bool state) {
    if (animationCheckBoxMenuItem->isChecked() != state) {
        animationCheckBoxMenuItem->setChecked(state);
    }

    if (animatingLayout != state) {
        animatingLayout = state;
        redrawPanel();
    }
}

/*public*/ bool LayoutEditor::isAnimating() {
  return animatingLayout;
}

/*public*/ int LayoutEditor::getLayoutWidth() {return gContext->getLayoutWidth();}

/*public*/ int LayoutEditor::getLayoutHeight() {return gContext->getLayoutHeight();}

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

/*public*/ int LayoutEditor::setGridSize(int newSize) {
    gContext->setGridSize(newSize);
    return gContext->getGridSize();
}

/*public*/ int LayoutEditor::getGridSize() {
    return gContext->getGridSize();
}

/*public*/ int LayoutEditor::setGridSize2nd(int newSize) {
 gContext->setGridSize2nd(newSize);
 return gContext->getGridSize2nd();
}

/*public*/ int LayoutEditor::getGridSize2nd() {
    return gContext->getGridSize2nd();
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

double LayoutEditor::toDegrees(double radians)
{
 return (radians/M_PI)*180;
}
double LayoutEditor::toRadians(double degrees)
{
 return (degrees/180)*M_PI;
}

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
//    return layoutTrackList->stream() // next line excludes LayoutSlips
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
    QList<LayoutTrack*>* layoutTracks =  getLayoutTracksOfClass("LevelXing");
    QList<LevelXing*> l = QList<LevelXing*>();
    for(LayoutTrack* t : *layoutTracks)
     l.append((LevelXing*)t);
  return l;
}

/*public*/ QList<LayoutTrack*>* LayoutEditor::getLayoutTracks() {
    return layoutTrackList;
}

/**
 * Read-only access to the list of LayoutTrackView family objects.
 * The returned list will throw UnsupportedOperationException
 * if you attempt to modify it.
 * @return unmodifiable copy of track views.
 */
//@Nonnull
/*final*/ /*public*/ QList<LayoutTrackView*>* LayoutEditor::getLayoutTrackViews() {
    return /*Collections.unmodifiableList*/(layoutTrackViewList);
}

/**
 * Add a LayoutTrack to the list of LayoutTrack family objects.
 * @param trk the layout track to add.
 */
/*final*/ /*public*/ void LayoutEditor::addLayoutTrack(/*@Nonnull*/ LayoutTrack* trk) {
    log->trace(tr("addLayoutTrack %1").arg(trk->getName()));
    if (layoutTrackList->contains(trk)) log->warn(tr("LayoutTrack %1 already being maintained").arg(trk->getName()));
    layoutTrackList->append(trk);

    // create the view on the fly
    LayoutTrackView* v = LayoutTrackView::makeTrackView(trk);
    layoutTrackViewList->append(v);
    trkToView.insert(trk, v);
    viewToTrk.insert(v, trk);
    unionToPanelBounds(trk->getBounds());
}

/**
 * If item present, delete from the list of LayoutTracks
 * and force a dirty redraw.
 * @param trk the layout track to remove and redraw.
 * @return true is item was deleted and a redraw done.
 */
/*final*/ /*public*/ bool LayoutEditor::removeLayoutTrackAndRedraw(/*@Nonnull*/ LayoutTrack* trk) {
    if (layoutTrackList->contains(trk)) {
        removeLayoutTrack(trk);
        setDirty();
        redrawPanel();
        log->trace(tr("removeLayoutTrackAndRedraw present %1").arg(trk->getId()));
        return true;
    }
    log->trace(tr("removeLayoutTrackAndRedraw absent %1").arg(trk->getId()));
    return false;
}

/**
 * If item present, delete from the list of LayoutTracks
 * and force a dirty redraw.
 * @param trk the layout track to remove.
 */
/*final*/ /*public*/ void LayoutEditor::removeLayoutTrack(/*@Nonnull */LayoutTrack* trk) {
    log->trace(tr("removeLayoutTrack %1").arg(trk->getId()));
    layoutTrackList->removeOne(trk);
    LayoutTrackView* v = trkToView.value(trk);
    layoutTrackViewList->removeOne(v);
    trkToView.remove(trk);
    viewToTrk.remove(v);
}
/**
 * Clear the list of layout tracks. Not intended for general use.
 *
 */
/*private*/ void LayoutEditor::clearLayoutTracks() {
    layoutTrackList->clear();
    layoutTrackViewList->clear();
    trkToView.clear();
    viewToTrk.clear();
}

/*public*/ QList<LayoutTurnout *> *LayoutEditor::getLayoutTurnoutsAndSlips() {
//    return getLayoutTracksOfClass("LayoutTurnout");
 QList<LayoutTurnout*>* list = new QList<LayoutTurnout*>();
 foreach(LayoutTrack* lt, *layoutTrackList)
 {
  if(qobject_cast<LayoutTurnout*>(lt))
   list->append((LayoutTurnout*)lt);
 }
 return list;
}

/*public*/ /*@Nonnull*/ QList<LayoutShape*>* LayoutEditor::getLayoutShapes() {
    return layoutShapes;
}

/*public*/ void LayoutEditor::sortLayoutShapesByLevel()
{
#if 0
    Collections.sort(layoutShapes, new Comparator<LayoutShape>() {
        @Override
        public int compare(LayoutShape lhs, LayoutShape rhs) {
            // -1 == less than, 0 == equal, +1 == greater than
            return Integer.signum(lhs.getLevel() - rhs.getLevel());
        }
    });
#endif
}

/*public*/ void LayoutEditor::alignSelection(bool alignX) {
    QPointF minPoint = MathUtil::infinityPoint2D();
    QPointF maxPoint = MathUtil::zeroPoint2D;
    QPointF sumPoint = MathUtil::zeroPoint2D;
    int cnt = 0;

    for (Positionable* comp : *_positionableSelection) {
        if (!getFlag(Editor::OPTION_POSITION, comp->isPositionable())) {
            continue;   // skip non-positionables
        }
        QPointF p = MathUtil::pointToPoint2D(QPoint(comp->getLocation().x(), comp->getLocation().y()));
        minPoint = MathUtil::min(minPoint, p);
        maxPoint = MathUtil::max(maxPoint, p);
        sumPoint = MathUtil::add(sumPoint, p);
        cnt++;
    }

    for (LayoutTrack* lt : _layoutTrackSelection) {
        QPointF p = lt->getCoordsCenter();
        minPoint = MathUtil::min(minPoint, p);
        maxPoint = MathUtil::max(maxPoint, p);
        sumPoint = MathUtil::add(sumPoint, p);
        cnt++;
    }

    for (LayoutShape* ls : _layoutShapeSelection) {
        QPointF p = ls->getCoordsCenter();
        minPoint = MathUtil::min(minPoint, p);
        maxPoint = MathUtil::max(maxPoint, p);
        sumPoint = MathUtil::add(sumPoint, p);
        cnt++;
    }

    QPointF avePoint = MathUtil::divide(sumPoint, cnt);
    int aveX = (int) avePoint.x();
    int aveY = (int) avePoint.y();

    for (Positionable* comp : *_positionableSelection) {
        if (!getFlag(Editor::OPTION_POSITION, comp->isPositionable())) {
            continue;   // skip non-positionables
        }

        if (alignX) {
            comp->setLocation(aveX, comp->getY());
        } else {
            comp->setLocation(comp->getX(), aveY);
        }
    }

    //_layoutTrackSelection.forEach((lt) ->
    foreach(LayoutTrack* lt, _layoutTrackSelection)
    {
        if (alignX) {
            lt->setCoordsCenter(QPointF(aveX, lt->getCoordsCenter().y()));
        } else {
            lt->setCoordsCenter(QPointF(lt->getCoordsCenter().x(), aveY));
        }
    }//);

    //_layoutShapeSelection.forEach((ls) ->
    foreach(LayoutShape* ls, _layoutShapeSelection)
    {
        if (alignX) {
            ls->setCoordsCenter(QPointF(aveX, ls->getCoordsCenter().y()));
        } else {
            ls->setCoordsCenter(QPointF(ls->getCoordsCenter().x(), aveY));
        }
    }//);

    redrawPanel();
}

/*protected*/ bool LayoutEditor::showAlignPopup()
{
 return ((_positionableSelection->size() > 0)
         || (_layoutTrackSelection.size() > 0)
         || (_layoutShapeSelection.size() > 0));
}

 /**
* Offer actions to align the selected Positionable items either
* Horizontally (at avearage y coord) or Vertically (at avearage x coord).
*/
/*public*/ bool LayoutEditor::setShowAlignmentMenu(QMenu* popup)
{
 if (showAlignPopup())
 {
  /*JMenu*/QMenu* edit = new /*JMenu*/QMenu(tr("Alignment"));

//     edit.add(new AbstractAction(rb.getQString("AlignX")) {
  QAction* alignXAction = new QAction("Align Vertically to Left Edge",this);
//         /*public*/ void actionPerformed(ActionEvent e) {
  connect(alignXAction, &QAction::triggered, [=]{
    alignSelection(true);
  });
  edit->addAction(alignXAction);
//     edit.add(new AbstractAction(rb.getQString("AlignY")) {
  QAction* alignYAction = new QAction("Align Horizontally to Top Edge",this);
//         /*public*/ void actionPerformed(ActionEvent e) {
  connect(alignYAction, &QAction::triggered, [=]{
   alignSelection(false);
  });
  edit->addAction(alignYAction);

  popup->addMenu(edit);
  return true;
 }
 return false;
}
#if 1
//@Override
    /*public*/ void LayoutEditor::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Delete) {
            deleteSelectedItems();
            return;
        }

        double deltaX = returnDeltaPositionX(event);
        double deltaY = returnDeltaPositionY(event);

        if ((deltaX != 0) || (deltaY != 0)) {
            selectionX += deltaX;
            selectionY += deltaY;

            QPointF delta = QPointF(deltaX, deltaY);
            //_positionableSelection.forEach((c) ->
            foreach(Positionable* c, *_positionableSelection)
            {
                QPointF newPoint = c->getLocation();
                //if ((c instanceof MemoryIcon) && (c.getPopupUtility().getFixedWidth() == 0))
                if(qobject_cast<LEMemoryIcon*>(c->self()) && c->getPopupUtility()->getFixedWidth()==0)
                {
                    LEMemoryIcon* pm = (LEMemoryIcon*) c;
                    newPoint = QPointF(pm->getOriginalX(), pm->getOriginalY());
                }
                newPoint = MathUtil::add(newPoint, delta);
                newPoint = MathUtil::max(MathUtil::zeroPoint2D, newPoint);
                c->setLocation(MathUtil::point2DToPoint(newPoint));
            }//);

            //_layoutTrackSelection.forEach((lt) ->
            foreach(LayoutTrack*lt, _layoutTrackSelection)
            {
                QPointF newPoint = MathUtil::add(lt->getCoordsCenter(), delta);
                newPoint = MathUtil::max(MathUtil::zeroPoint2D, newPoint);
                lt->setCoordsCenter(newPoint);
            }//);

            //_layoutShapeSelection.forEach((ls) -> {
            foreach(LayoutShape* ls, _layoutShapeSelection)
            {
                QPointF newPoint = MathUtil::add(ls->getCoordsCenter(), delta);
                newPoint = MathUtil::max(MathUtil::zeroPoint2D, newPoint);
                ls->setCoordsCenter(newPoint);
            }//);
            redrawPanel();
        }
    }
#endif

QGraphicsView* LayoutEditor::panel()
{
 return editPanel;
}
/**
* Remove a PositionablePoint -- an Anchor or an End Bumper.
*/
/*protected*/ bool LayoutEditor::removePositionablePoint(PositionablePoint* o)
{
 // First verify with the user that this is really wanted, only show message if there is a bit of track connected
 if ((o->getConnect1() != nullptr) || (o->getConnect2() != nullptr)) {
     if (!noWarnPositionablePoint) {
         int selectedValue = JOptionPane::showOptionDialog(this,
                 tr("Are you sure you want to remove this point from the panel, along with any connected Track Segments?"), tr("Warning"),
                 JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                 QVariantList() <<QVariant("ButtonYes") <<
                     QVariant("No") <<
                     QVariant("YesPlus"),
                 QVariant("No"));

         if (selectedValue == JOptionPane::NO_OPTION) {
             return false; // return without creating if "No" response
         }

         if (selectedValue == JOptionPane::CANCEL_OPTION) {
             // Suppress future warnings, and continue
             noWarnPositionablePoint = true;
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
     TrackSegment* t1 = o->getConnect1();
     TrackSegment* t2 = o->getConnect2();

     if (t1 != nullptr) {
         removeTrackSegment(t1);
     }

     if (t2 != nullptr) {
         removeTrackSegment(t2);
     }

     // delete from array
 }

 if (removeLayoutTrackAndRedraw(o))
  return true;

 return false;
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

/**
  * Add a signal head to the Panel
  */
 void LayoutEditor::addSignalHead() {
     // check for valid signal head entry
  QString newName = leToolBarPanel->signalHeadComboBox->getSelectedItemDisplayName();

     SignalHead* mHead = nullptr;
     if ( (newName!=("")) ) {
         mHead = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(newName);
         /*if (mHead == nullptr)
             mHead = InstanceManager.signalHeadManagerInstance().getByUserName(tName);
         else */
         leToolBarPanel->signalHeadComboBox->setCurrentText(newName);
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
     l->setIcon(tr("Flashing Red"), signalIconEditor->getIcon(1));
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
     SignalHead* sh = (SignalHead*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name);
     if (sh == nullptr) sh = (SignalHead*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getByUserName(name);
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
     QString newName = leToolBarPanel->signalMastComboBox->getSelectedItemDisplayName();
     SignalMast* mMast = nullptr;
     if ( (newName!=("")) ) {
         mMast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(newName);
         leToolBarPanel->signalMastComboBox->setSelectedItemByName(newName);
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
 QString labelText = leToolBarPanel->textLabelTextField->text();
 labelText = (labelText != "") ? labelText.trimmed() : "";

 if (labelText.isEmpty()) {
     JOptionPane::showMessageDialog(this, tr("Error - Cannot create a text label because no text is entered in the\nLabel text field. Please enter some text and try again."),
             tr("Error"), JOptionPane::ERROR_MESSAGE);
     return;
 }
 PositionableLabel* l = Editor::addLabel(labelText);
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
 if (qobject_cast<SensorIcon*>(l->self())!= nullptr)
 {
  sensorImage->append((SensorIcon*)l);
  sensorList->append((SensorIcon*)l);
 }
 else if (qobject_cast<LocoIcon*>(l->self())!= nullptr)
 {
  markerImage->append((LocoIcon*)l);
 }
 else if (qobject_cast<SignalHeadIcon*>(l->self())!=nullptr)
 {
     signalHeadImage->append((SignalHeadIcon*)l);
     signalList->append((SignalHeadIcon*)l);
 }
 else if (qobject_cast<SignalMastIcon*>(l->self())!=nullptr)
 {
     signalMastImage->append((SignalMastIcon*)l);
     signalMastList->append((SignalMastIcon*)l);
 }
 else
  //if (l instanceof MemoryIcon*)
 if(qobject_cast<LEMemoryIcon*>(l->self())!= nullptr)
 {
  memoryLabelList->append((LEMemoryIcon*)l);
 }
 else if (qobject_cast<AnalogClock2Display*>(l->self())!=nullptr)
 {
  clocks->append((AnalogClock2Display*)l);
 }
 else if (qobject_cast<MultiSensorIcon*>(l->self()) != nullptr)
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

/**
* Add a sensor indicator to the Draw Panel
*/
void LayoutEditor::addSensor()
{
 QString newName = leToolBarPanel->sensorComboBox->getSelectedItemDisplayName();
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
  l->setSensor(newName);
  l->setDisplayLevel(SENSORS);
  //Sensor xSensor = l.getSensor();
  if (l->getSensor() != nullptr)
  {
   if (newName != (l->getNamedSensor()->getName()))
   {
       leToolBarPanel->sensorComboBox->setSelectedItemByName(l->getNamedSensor()->getName());
   }
  }
  NamedBeanHandle<Sensor*>* s = l->getNamedSensor();
  QString sensorName = "";
  if(s != nullptr)
   sensorName = s->getName();
  leToolBarPanel->sensorComboBox->setSelectedItemByName(sensorName);
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
 connect(removeMenuAction, SIGNAL(triggered()), this, SLOT(on_removeMenuAction_triggered()));
 popup->addAction(removeMenuAction);
}

void LayoutEditor::on_removeMenuAction_triggered()
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
 * Control whether panel items are positionable. Markers are always
 * positionable.
 *
 * @param state true for positionable.
 */
//@Override
/*public*/ void LayoutEditor::setAllPositionable(bool state) {
    Editor::setAllPositionable(state);

    //markerImage.forEach((p) ->
    foreach (Positionable* p, *markerImage) {
        p->setPositionable(true);
    }//);
}

/*private*/ void LayoutEditor::setupMarkerMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* markerMenu = new QMenu(tr("Marker"));

//    markerMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("MenuMarkerMnemonic")));
    menuBar->addMenu(markerMenu);
    QAction* act;
    markerMenu->addAction(act = new AbstractAction(tr("Add Loco") + "...",this));
    connect(act, &QAction::triggered, [=]{
            locoMarkerFromInput();
    });
    markerMenu->addAction(act = new AbstractAction(tr("Add Loco from Roster") + "...", this));
    connect(act, &QAction::triggered, [=]{
            locoMarkerFromRoster();
    });
    markerMenu->addAction(act =new AbstractAction(tr("Remove Markers"), this));
    connect(act, &QAction::triggered, [=]{
            removeMarkers();
    });
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
    connect(newTrainItem, &QAction::triggered, [=]{

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
    });
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
 QString newName = leToolBarPanel->blockIDComboBox->getSelectedItemDisplayName();
 if (newName.isNull()) {
     newName = "";
 }
 LayoutBlock* b = (LayoutBlock*)((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(newName);
 //_layoutTrackSelection.forEach((lt) ->
 foreach(LayoutTrack* lt, _layoutTrackSelection)
 {
     lt->setAllLayoutBlocks(b);
 }//);
}

/*public*/ bool LayoutEditor::translateTrack(float xDel, float yDel) {
    QPointF delta = QPointF(xDel, yDel);
    //layoutTrackList->forEach((lt) ->
    foreach (LayoutTrack*lt, *layoutTrackList)
    {
        lt->setCoordsCenter(MathUtil::add(lt->getCoordsCenter(), delta));
    }//);
    resizePanelBounds(true);
    return true;
}

/**
 * scale all LayoutTracks coordinates by the x and y factors
 *
 * @param xFactor the amount to scale X coordinates
 * @param yFactor the amount to scale Y coordinates
 */
/*public*/ bool LayoutEditor::scaleTrack(float xFactor, float yFactor) {
    //layoutTrackList->forEach((lt) -> {
 foreach (LayoutTrack*lt, *layoutTrackList)
 {
     lt->scaleCoords(xFactor, yFactor);
 }//);

 //update the overall scale factors
 gContext->setXScale(gContext->getXScale() * xFactor);
 gContext->setYScale(gContext->getYScale() * yFactor);

 resizePanelBounds(true);
 return true;
}

/**
* Add a memory label to the Draw Panel
*/
void LayoutEditor::addMemory()
{
 QString memoryName = leToolBarPanel->textMemoryComboBox->getSelectedItemDisplayName();

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
            leToolBarPanel->textMemoryComboBox->setSelectedItemByName(xMemory->getSystemName());
        }
    }
    setNextLocation(l);
    l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
    l->setDisplayLevel(Editor::LABELS);
    l->setForeground(defaultTextColor);
    unionToPanelBounds(l->getBounds());
    putItem(l); // note: this calls unionToPanelBounds & setDirty()
} //addMemory

void LayoutEditor::addBlockContents()
{
    QString newName = leToolBarPanel->blockContentsComboBox->getSelectedItemDisplayName();
    if (newName == nullptr) {
        newName = "";
    }

    if (newName.isEmpty()) {
        JOptionPane::showMessageDialog(this, tr("Error - Cannot create a Block Contents label because no block name is entered in the\nBlock Contents text field. Please enter the name of a Block and try again."),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        return;
    }
    BlockContentsIcon* l = new BlockContentsIcon(" ", this);
    l->setBlock(newName);
    Block* xMemory = l->getBlock();

    if (xMemory != nullptr) {
        QString uname = xMemory->getDisplayName();
        if (uname != (newName)) {
            //put the system name in the memory field
            leToolBarPanel->blockContentsComboBox->setSelectedItem(xMemory);
        }
    }
    setNextLocation(l);
    l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
    l->setDisplayLevel(Editor::LABELS);
    l->setForeground(defaultTextColor);
    putItem(l); // note: this calls unionToPanelBounds & setDirty()
}

/**
* Add a Reporter Icon to the panel
*/
void LayoutEditor::addReporter(Reporter* textReporter,int xx,int yy) {
  ReporterIcon* l = new ReporterIcon(this);
  l->setReporter(textReporter);
  ((Positionable*)l)->setLocation(xx,yy);
  l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
  l->setDisplayLevel(LABELS);
  setDirty(true);
  putItem((Positionable*)l);
  l->paint(editScene);
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

  //layoutShapes->removeAll(_layoutShapeSelection);
  foreach(LayoutShape* ls, _layoutShapeSelection)
   layoutShapes->removeOne(ls);

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

#if 0
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

#endif
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
//void LayoutEditor::OnDefaultTrackColorSelected(QAction *act)
//{
// QColor c = act->data().value<QColor>();
// Q_ASSERT(c.isValid());

// defaultTrackColor = c;
//}

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
/*public*/ QString LayoutEditor::getLayoutName() {return layoutName;}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getShowHelpBar() {
    return showHelpBar;
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getDrawGrid() {
    return drawGrid;
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getSnapOnAdd() {
    return snapToGridOnAdd;
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getSnapOnMove() {
    return snapToGridOnMove;
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getAntialiasingOn() {
    return antialiasingOn;
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "isShowHelpBar()"
/*public*/ bool LayoutEditor::getHighlightSelectedBlock() {
    return highlightSelectedBlockFlag;
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

// /*public*/ LayoutTrackEditors* LayoutEditor::getLayoutTrackEditors() {
//    if (layoutTrackEditors == nullptr) {
//        layoutTrackEditors = new LayoutTrackEditors(this);
//    }
//    return layoutTrackEditors;
//}

 /*public*/ LayoutEditorChecks* LayoutEditor::getLEChecks()
 {
    if (layoutEditorChecks == nullptr) {
        layoutEditorChecks = new LayoutEditorChecks(this);
    }
    return layoutEditorChecks;
}

/**
* Invoked by DeletePanel menu item Validate user intent before deleting
*/
//@Override
/*public*/ bool LayoutEditor::deletePanel() {
    //verify deletion
    if (!Editor::deletePanel()) {
        return false; //return without deleting if "No" response
    }
    layoutTrackList->clear();
    return true;
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
  for (LayoutTurnout* lt : *getLayoutTurnoutsAndSlips()) {
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
 * add a layout shape to the list of layout shapes
 *
 * @param p Point2D where the shape should be
 * @return the LayoutShape
 */
//@Nonnull
/*protected*/ LayoutShape* LayoutEditor::addLayoutShape(/*@Nonnull*/ QPointF p) {
    //get unique name
    QString name = finder->uniqueName("S", ++numShapes);

    //create object
    LayoutShape* o = new LayoutShape(name, p, this);
    layoutShapes->append(o);
    unionToPanelBounds(o->getBounds());
    setDirty();
    return o;
}

/**
 * Remove a layout shape from the list of layout shapes
 *
 * @param s the LayoutShape to add
 * @return true if added
 */
/*protected*/ bool LayoutEditor::removeLayoutShape(/*@Nonnull*/ LayoutShape* s) {
    bool result = false;
    if (layoutShapes->contains(s)) {
        layoutShapes->removeOne(s);
        setDirty();
        result = true;
        redrawPanel();
    }
    return result;
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

//void LayoutEditor::onChangeIconsButton()
//{
// if (leToolBarPanel->sensorButton->isChecked()) {
//     sensorFrame->setVisible(true);
// } else if (leToolBarPanel->signalButton->isChecked()) {
//     signalFrame->setVisible(true);
// } else if (leToolBarPanel->iconLabelButton->isChecked()) {
//     iconFrame->setVisible(true);
// } else {
//     //explain to the user why nothing happens
//     JOptionPane::showMessageDialog(nullptr, tr("This only works when a Sensor, Signal Head or\nLabel is selected to the right of this button."),
//             tr("Change Icons"), JOptionPane::INFORMATION_MESSAGE);
// }

//}
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
        moveSelectionFrame = new JmriJFrameX(tr("Translate Selection"));
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
/**
 * Translate entire layout by x and y amounts.
 *
 * @param xTranslation horizontal (X) translation value
 * @param yTranslation vertical (Y) translation value
 */
/*public*/ void LayoutEditor::translate(float xTranslation, float yTranslation) {
    // here when all numbers read in - translation if entered
    if ((xTranslation != 0.0F) || (yTranslation != 0.0F)) {
        QPointF delta = QPointF(xTranslation, yTranslation);
        QRectF selectionRect = getSelectionRect();

        //set up undo information
        undoRect = MathUtil::offset(selectionRect, delta);
        undoDelta = MathUtil::subtract(MathUtil::zeroPoint2D, delta);
        canUndoMoveSelection = true;
        undoTranslateSelectionMenuItem->setEnabled(canUndoMoveSelection);

        //apply translation to icon items within the selection
        for (Positionable* c : *_positionableSelection) {
            QPointF newPoint = MathUtil::add(c->getLocation(), delta);
            c->setLocation((int) newPoint.x(), (int) newPoint.y());
        }

        for (LayoutTrack* lt : _layoutTrackSelection) {
            lt->setCoordsCenter(MathUtil::add(lt->getCoordsCenter(), delta));
        }

        for (LayoutShape* ls : _layoutShapeSelection) {
            ls->setCoordsCenter(MathUtil::add(ls->getCoordsCenter(), delta));
        }

        selectionX = undoRect.x();
        selectionY = undoRect.y();
        selectionWidth = undoRect.width();
        selectionHeight = undoRect.height();
        resizePanelBounds(false);
        setDirty();
        redrawPanel();
    }
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

/**
 * Rotate selection by 90 degrees clockwise.
 */
/*public*/ void LayoutEditor::rotateSelection90() {
    QRectF bounds = getSelectionRect();
    QPointF center = MathUtil::midPoint(bounds);

    for (Positionable* positionable : *_positionableSelection) {
        QRectF cBounds = positionable->getBounds(QRectF());
        QPointF oldBottomLeft = QPointF(cBounds.left(), cBounds.top());
        QPointF newTopLeft = MathUtil::rotateDEG(oldBottomLeft, center, 90);
        bool rotateFlag = true;
        if (qobject_cast<PositionableLabel*>(positionable->self())) {
            PositionableLabel* positionableLabel = (PositionableLabel*) positionable->self();
            if (positionableLabel->isBackground()) {
                rotateFlag = false;
            }
        }
        if (rotateFlag) {
            positionable->rotate(positionable->getDegrees() + 90);
            positionable->setLocation((int) newTopLeft.x(), (int) newTopLeft.y());
        }
    }

    for (LayoutTrack* lt : _layoutTrackSelection) {
        lt->setCoordsCenter(MathUtil::rotateDEG(lt->getCoordsCenter(), center, 90));
        lt->rotateCoords(90);
    }

    for (LayoutShape* ls : _layoutShapeSelection) {
        ls->setCoordsCenter(MathUtil::rotateDEG(ls->getCoordsCenter(), center, 90));
        ls->rotateCoords(90);
    }

    resizePanelBounds(true);
    setDirty();
    redrawPanel();
}

/**
 * Rotate the entire layout by 90 degrees clockwise.
 */
/*public*/ void LayoutEditor::rotateLayout90() {
    QVector<Positionable*> positionables = QVector<Positionable*>(*_contents);
    //positionables.append(backgroundImage);
    for(PositionableLabel* l: *backgroundImage)
     positionables.append(l);
    //positionables.append(blockContentsLabelList);
    for(LEBlockContentsIcon* l: *blockContentsLabelList)
     positionables.append(l);
    //positionables.append(labelImage);
    for(PositionableLabel* l: *labelImage)
     positionables.append(l);
    //positionables.append(memoryLabelList);
    for(LEMemoryIcon* l: *memoryLabelList)
     positionables.append(l);
    //positionables.append(sensorImage);
    for(SensorIcon* l: *sensorImage)
     positionables.append(l);
    //positionables.append(sensorList);
    for(SensorIcon* l: *sensorList)
     positionables.append(l);
    //positionables.append(signalHeadImage);
    for(SignalHeadIcon* l: *signalHeadImage)
     positionables.append(l);
    //positionables.append(signalList);
    for(SignalHeadIcon* l: *signalList)
     positionables.append(l);
    //positionables.append(signalMastList);
    for(SignalMastIcon* l: *signalMastList)
     positionables.append(l);

    //do this to remove duplicates that may be in more than one list
#if 0
    positionables = positionables.stream().distinct().collect(Collectors.toList());
#endif

    QRectF bounds = getPanelBounds();
    QPointF lowerLeft = QPointF(bounds.bottom(), bounds.top());

    for (Positionable* positionable : positionables) {
        QRectF cBounds = positionable->getBounds(QRectF());
        QPointF newTopLeft = MathUtil::subtract(MathUtil::rotateDEG(positionable->getLocation(), lowerLeft, 90), lowerLeft);
        bool reLocateFlag = true;
        if (qobject_cast<PositionableLabel*>(positionable->self())) {
            try {
                PositionableLabel* positionableLabel = (PositionableLabel*) positionable->self();
                if (positionableLabel->isBackground()) {
                    reLocateFlag = false;
                }
                positionableLabel->rotate(positionableLabel->getDegrees() + 90);
            } catch (NullPointerException ex) {
            }
        }
        if (reLocateFlag) {
            try {
                positionable->setLocation((int) (newTopLeft.x() - cBounds.height()), (int) newTopLeft.y());
            } catch (NullPointerException ex) {

            }
        }
    }

    for (LayoutTrack* lt : *layoutTrackList) {
        try {
            QPointF newPoint = MathUtil::subtract(MathUtil::rotateDEG(lt->getCoordsCenter(), lowerLeft, 90), lowerLeft);
            lt->setCoordsCenter(newPoint);
            lt->rotateCoords(90);
        } catch (NullPointerException ex) {

        }
    }

    for (LayoutShape* ls : *layoutShapes) {
        QPointF newPoint = MathUtil::subtract(MathUtil::rotateDEG(ls->getCoordsCenter(), lowerLeft, 90), lowerLeft);
        ls->setCoordsCenter(newPoint);
        ls->rotateCoords(90);
    }

    resizePanelBounds(true);
    setDirty();
    redrawPanel();
}

/**
 * align the layout to grid
 */
/*public*/ void LayoutEditor::alignLayoutToGrid() {
    //align to grid
    QVector<Positionable*> positionables = QVector<Positionable*>(*_contents);
    //positionables.append(backgroundImage);
    for(PositionableLabel* l: *backgroundImage)
     positionables.append(l);
    //positionables.append(blockContentsLabelList);
    for(LEBlockContentsIcon* l: *blockContentsLabelList)
     positionables.append(l);
    //positionables.append(labelImage);
    for(PositionableLabel* l: *labelImage)
     positionables.append(l);
    //positionables.append(memoryLabelList);
    for(LEMemoryIcon* l: *memoryLabelList)
     positionables.append(l);
    //positionables.append(sensorImage);
    for(SensorIcon* l: *sensorImage)
     positionables.append(l);
    //positionables.append(sensorList);
    for(SensorIcon* l: *sensorList)
     positionables.append(l);
    //positionables.append(signalHeadImage);
    for(SignalHeadIcon* l: *signalHeadImage)
     positionables.append(l);
    //positionables.append(signalList);
    for(SignalHeadIcon* l: *signalList)
     positionables.append(l);
    //positionables.append(signalMastList);
    for(SignalMastIcon* l: *signalMastList)
     positionables.append(l);


    //do this to remove duplicates that may be in more than one list
#if 0
    positionables = positionables.stream().distinct().collect(Collectors.toList());
    alignToGrid(positionables, layoutTrackList, layoutShapes);
#endif
}

/**
 * align selection to grid
 */
/*public*/ void LayoutEditor::alignSelectionToGrid() {
    alignToGrid(*_positionableSelection, _layoutTrackSelection, _layoutShapeSelection);
}

/*private*/ void LayoutEditor::alignToGrid(QVector<Positionable*> positionables, QList<LayoutTrack*> tracks, QList<LayoutShape*> shapes) {
    for (Positionable* positionable : positionables) {
        QPointF newLocation = MathUtil::granulize(positionable->getLocation(), gContext->getGridSize());
        positionable->setLocation((int) (newLocation.x()), (int) newLocation.y());
    }
    for (LayoutTrack* lt : tracks) {
        lt->setCoordsCenter(MathUtil::granulize(lt->getCoordsCenter(), gContext->getGridSize()));
        if (qobject_cast<LayoutTurntable*>(lt)) {
            LayoutTurntable* tt = (LayoutTurntable*) lt;
            for (RayTrack* rt : tt->getRayTrackList()) {
                int rayIndex = rt->getConnectionIndex();
                tt->setRayCoordsIndexed(MathUtil::granulize(tt->getRayCoordsIndexed(rayIndex), gContext->getGridSize()), rayIndex);
            }
        }
    }
    for (LayoutShape* ls : shapes) {
        ls->setCoordsCenter(MathUtil::granulize(ls->getCoordsCenter(), gContext->getGridSize()));
        for (int idx = 0; idx < ls->getNumberPoints(); idx++) {
            ls->setPoint(idx, MathUtil::granulize(ls->getPoint(idx), gContext->getGridSize()));
        }
    }

    resizePanelBounds(true);
    setDirty();
    redrawPanel();
}

/*public*/ void LayoutEditor::setCurrentPositionAndSize()
{
 // save current panel location and size
 QSize dim = size();

 // Compute window size based on LayoutEditor size
 gContext->setWindowHeight(dim.height());
 gContext->setWindowWidth(dim.width());

 // Compute layout size based on LayoutPane size
 dim = getTargetPanelSize();
 gContext->setLayoutWidth( (int) (dim.width() / getZoom()) );
 gContext->setLayoutHeight( (int) (dim.height() / getZoom()) );
 //adjustScrollBars();

 QPoint pt = getLocationOnScreen();
 gContext->setUpperLeftY(pt.x());
 gContext->setUpperLeftY(pt.y());

 log->debug(tr("setCurrentPositionAndSize Position - %1,%2 WindowSize - %3,%4 PanelSize - %5,%6").arg(gContext->getUpperLeftX()).arg(gContext->getUpperLeftY()).arg(gContext->getWindowWidth()).arg(gContext->getWindowHeight()).arg(gContext->getLayoutWidth()).arg(gContext->getLayoutHeight()));
 setDirty();
}

/*public*/ void LayoutEditor::setDirectTurnoutControl(bool boo) {
    useDirectTurnoutControl = boo;
    useDirectTurnoutControlItem->setChecked(useDirectTurnoutControl);

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
        return QRectF(0.0, 0.0, gContext->getLayoutWidth(), gContext->getLayoutHeight());
}

/*public*/ void LayoutEditor::setPanelBounds(QRectF newBounds) {
    // don't let origin go negative
    newBounds = newBounds.intersected(QRectF(0.0, 0.0, INFINITY, INFINITY));

    if (getPanelBounds() !=(newBounds)) {
     gContext->setLayoutWidth((int) newBounds.width());
     gContext->setLayoutHeight( (int) newBounds.height());
     resetTargetSize();
    }
    log->debug(tr("setPanelBounds((%1, %2, %3, %4)").arg(newBounds.x()).arg(newBounds.y()).arg(newBounds.width()).arg(newBounds.height()));
}

/*private*/ void LayoutEditor::resetTargetSize() {
    int newTargetWidth = (int) (gContext->getLayoutWidth() * getZoom());
    int newTargetHeight = (int) (gContext->getLayoutHeight() * getZoom());

    QSize targetPanelSize = getTargetPanelSize();
    int oldTargetWidth = (int) targetPanelSize.width();
    int oldTargetHeight = (int) targetPanelSize.height();

    if ((newTargetWidth != oldTargetWidth) || (newTargetHeight != oldTargetHeight)) {
        setTargetPanelSize(newTargetWidth, newTargetHeight);
//        adjustScrollBars();
    }
}

// this will grow the panel bounds based on items added to the layout
/*public*/ QRectF LayoutEditor::unionToPanelBounds(/*@Nonnull*/ QRectF bounds) {
    QRectF result = getPanelBounds();
    // make room to expand
    QRectF b = MathUtil::inset(bounds, gContext->getGridSize() * gContext->getGridSize2nd() / -2.0);

    // don't let origin go negative
    b = b.intersected(/*MathUtil::zeroToInfinityRectangle2D*/QRectF(0.0, 0.0, INFINITY, INFINITY));

    //result.add(b);
    result.adjust(b.x(), b.y(), b.width(), b.height());

    setPanelBounds(result);
    return result;
}

/*public*/ void LayoutEditor::setMainlineTrackWidth(int w) {
    gContext->setMainlineTrackWidth(w);
}

/*public*/ void LayoutEditor::setSideTrackWidth(int w) {
    gContext->setSidelineTrackWidth(w);
}

/**
 * @param color value to set the default track color to.
 */
/*public*/ void LayoutEditor::setDefaultTrackColor(/*@Nonnull*/ QColor color) {
    LayoutTrack::setDefaultTrackColor(color);
    defaultTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/**
 * @param color value to set the default occupied track color to.
 */
/*public*/ void LayoutEditor::setDefaultOccupiedTrackColor(/*@Nonnull*/ QColor color) {
    defaultOccupiedTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/**
 * @param color value to set the default alternate track color to.
 */
/*public*/ void LayoutEditor::setDefaultAlternativeTrackColor(/*@Nonnull*/ QColor color) {
    defaultAlternativeTrackColor = color;
    JmriColorChooser::addRecentColor(color);
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

/**
 * @param color new color for turnout circle.
 */
/*public*/ void LayoutEditor::setTurnoutCircleThrownColor(/*@CheckForNull*/ QColor color) {
    if (!color.isValid()) {
        turnoutCircleThrownColor = getDefaultTrackColor();
    } else {
        turnoutCircleThrownColor = color;
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
    gContext->setXScale(xSc);
}

/*public*/ void LayoutEditor::setYScale(double ySc) {
    gContext->setYScale(ySc);
}

/*public*/ void LayoutEditor::setShowHelpBar(bool state)
{
 if (showHelpBar != state)
 {
  showHelpBar = state;

  //these may not be set up yet...
  if (showHelpCheckBoxMenuItem != nullptr) {
      showHelpCheckBoxMenuItem->setChecked(showHelpBar);
  }

  if (toolBarSide->getType() == eFLOAT) {
      if (floatEditHelpPanel != nullptr) {
          floatEditHelpPanel->setVisible(isEditable() && showHelpBar);
      }
  }
  else
  {
   if (helpBarPanel != nullptr)
   {
    helpBarPanel->setVisible(isEditable() && showHelpBar);
    bool visible = isEditable() && getShowHelpBar();
    if(visible)
     borderLayout->addWidget(helpBarPanel, BorderLayout::South);
    else
     borderLayout->removeWidget(helpBarPanel);
    adjustSize();
   }
  }
  UserPreferencesManager* prefsMgr=
   ((UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager"));
  if(prefsMgr)
  {
      prefsMgr->setSimplePreferenceState(getWindowFrameRef() + ".showHelpBar", showHelpBar);
  }//);
 }
}

/*public*/ void LayoutEditor::setDrawGrid(bool state)
{
 if (drawGrid != state)
 {
  drawGrid = state;
  //showGridItem->setChecked(drawGrid);
  showGridCheckBoxMenuItem->setChecked(drawGrid);
 }
}

/*public*/ void LayoutEditor::setSnapOnAdd(bool state)
{
 if (snapToGridOnAdd != state)
 {
  snapToGridOnAdd = state;
  //snapToGridOnAddItem->setChecked(snapToGridOnAdd);
  snapToGridOnAddCheckBoxMenuItem->setChecked(snapToGridOnAdd);
 }
}

/*public*/ void LayoutEditor::setSnapOnMove(bool state)
{
 if (snapToGridOnMove != state)
 {
  snapToGridOnMove = state;
  //snapToGridOnMoveItem->setChecked(snapToGridOnMove);
  snapToGridOnMoveCheckBoxMenuItem->setChecked(snapToGridOnMove);
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
        if (leToolBarPanel->highlightBlockCheckBox != nullptr) {
            leToolBarPanel->highlightBlockCheckBox->setChecked(highlightSelectedBlockFlag);
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
                if (!highlightBlockInComboBox(leToolBarPanel->blockIDComboBox)) {
                    highlightBlockInComboBox(leToolBarPanel->blockContentsComboBox);
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
/*private*/ bool LayoutEditor::highlightBlockInComboBox(/*@Nonnull*/ NamedBeanComboBox* inComboBox) {
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

   leToolBarPanel-> blockIDComboBox->setSelectedItem((NamedBean*)inBlock);

    LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
    QSet<NamedBean*> l = leToolBarPanel->blockIDComboBox->getManager()->getNamedBeanSet();
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
  if (turnoutCirclesWithoutEditMode != state)
  {
      turnoutCirclesWithoutEditMode = state;
      if (turnoutCirclesOnCheckBoxMenuItem != nullptr) {
          turnoutCirclesOnCheckBoxMenuItem->setChecked(turnoutCirclesWithoutEditMode);
      }
  }
 }
}

/*public*/ void LayoutEditor::setAutoBlockAssignment(bool boo)
{
 if (autoAssignBlocks != boo)
 {
  autoAssignBlocks = boo;
  if (autoAssignBlocksCheckBoxMenuItem != nullptr) {
      autoAssignBlocksCheckBoxMenuItem->setChecked(autoAssignBlocks);
  }
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
        enterTrackWidthFrame = new JmriJFrameX(tr("Set Track Line Width"));
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
    mainlineTrackWidthField->setText(QString::number( gContext->getMainlineTrackWidth()));
    sidelineTrackWidthField->setText(QString::number(gContext->getSidelineTrackWidth()));
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

    if (!MathUtil::equals(gContext->getSidelineTrackWidth(), wid)) {
        gContext->setSidelineTrackWidth(wid);
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
        if (!MathUtil::equals(gContext->getMainlineTrackWidth(), wid)) {
            gContext->setMainlineTrackWidth(wid);
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
                layoutTrackDrawingOptions->setMainBlockLineWidth((int) gContext->getMainlineTrackWidth());
                layoutTrackDrawingOptions->setSideBlockLineWidth((int) gContext->getSidelineTrackWidth());
                layoutTrackDrawingOptions->setMainRailWidth((int) gContext->getMainlineTrackWidth());
                layoutTrackDrawingOptions->setSideRailWidth((int) gContext->getSidelineTrackWidth());
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
        enterGridSizesFrame = new JmriJFrameX(tr("SetGridSizes"));
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
    primaryGridSizeField->setText(QString::number(gContext->getGridSize()));
    secondaryGridSizeField->setText(QString::number(gContext->getGridSize2nd()));
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

    if (!MathUtil::equals(gContext->getGridSize2nd(), siz)) {
        gContext->setGridSize2nd(siz);
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
        if (!MathUtil::equals(gContext->getGridSize(), siz)) {
            gContext->setGridSize(siz);
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

//these are convenience methods to return rectangles
//to use when (hit point-in-rect testing
//
//compute the control point rect at inPoint
/*public*/ /*@Nonnull*/ QRectF LayoutEditor::layoutEditorControlRectAt(/*@Nonnull*/ QPointF inPoint) {
    return QRectF(inPoint.x() - SIZE,
            inPoint.y() - SIZE, SIZE2, SIZE2);
}

//compute the turnout circle control rect at inPoint
/*public*/ /*@Nonnull*/ QRectF LayoutEditor::layoutEditorControlCircleRectAt(/*@Nonnull*/ QPointF inPoint) {
    return QRectF(inPoint.x() - circleRadius,
            inPoint.y() - circleRadius, circleDiameter, circleDiameter);
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
/*protected*/ QMenu* LayoutEditor::setupOptionMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* optionMenu = new QMenu(tr("Options"));

//    optionMenu.setMnemonic(stringsToVTCodes.get(Bundle.getMessage("OptionsMnemonic")));
    menuBar->addMenu(optionMenu);

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
    connect(editModeCheckBoxMenuItem, &QAction::triggered, [=]{
        setAllEditable(editModeCheckBoxMenuItem->isChecked());

        //show/hide the help bar
        if (toolBarSide->getType() == eFLOAT) {
            floatEditHelpPanel->setVisible(isEditable() && getShowHelpBar());
        } else {
            helpBarPanel->setVisible(isEditable() && getShowHelpBar());
        }

        if (isEditable()) {
            setAllShowToolTip(tooltipsInEditMode);

            //redo using the "Extra" color to highlight the selected block
            if (highlightSelectedBlockFlag) {
                if (!highlightBlockInComboBox(leToolBarPanel->blockIDComboBox)) {
                    highlightBlockInComboBox(leToolBarPanel->blockContentsComboBox);
                }
            }
        } else {
            setAllShowToolTip(tooltipsWithoutEditMode);

            //undo using the "Extra" color to highlight the selected block
            if (highlightSelectedBlockFlag) {
                highlightBlock(nullptr);
            }
        }
        awaitingIconChange = false;
    });
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
    connect(toolBarSideTopButton, &QAction::triggered, [=]{
        setToolBarSide(new ToolBarSide(eTOP));
    });
    toolBarSideTopButton->setChecked(toolBarSide->getName() == (/*ToolBarSide::eTOP*/"top"));

    toolBarSideLeftButton = new QAction(tr("Left"));
//    toolBarSideLeftButton.addActionListener((ActionEvent event) -> {
//    connect(toolBarSideLeftButton, &QAction::triggered, [=]{
//        setToolBarSide( new ToolBarSide(eLEFT));
//    });
    toolBarSideLeftButton->setChecked(toolBarSide->getName()==(/*ToolBarSide::eLEFT)*/"left"));

    toolBarSideBottomButton = new QAction(tr("Bottom"));
    toolBarSideBottomButton->setCheckable(true);
//    toolBarSideBottomButton.addActionListener((ActionEvent event) -> {
//    connect(toolBarSideBottomButton, &QAction::triggered, [=]{
//        setToolBarSide( new ToolBarSide(eBOTTOM));
//    });
    toolBarSideBottomButton->setChecked(toolBarSide->getName()==(/*ToolBarSide::eBOTTOM*/"bottom"));

    toolBarSideRightButton = new QAction(tr("Right"));
    toolBarSideRightButton->setCheckable(true);
//    toolBarSideRightButton.addActionListener((ActionEvent event) -> {
//    connect(toolBarSideRightButton, &QAction::triggered, [=]{
//        setToolBarSide( new ToolBarSide(eRIGHT));
//    });
    toolBarSideRightButton->setChecked(toolBarSide->getName()==(/*ToolBarSide::eRIGHT*/"right"));

    toolBarSideFloatButton = new QAction(tr("Float"));
    toolBarSideFloatButton->setCheckable(true);
//    toolBarSideFloatButton.addActionListener((ActionEvent event) -> {
//    connect(toolBarSideFloatButton, &QAction::triggered, [=]{
//        setToolBarSide( new ToolBarSide(eFLOAT));
//    });
    toolBarSideFloatButton->setChecked(toolBarSide->getName()==(/*ToolBarSide::eFLOAT*/"float"));

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
    connect(toolBarSideGroup, SIGNAL(triggered(QAction*)), this, SLOT(on_setToolBarSide(QAction*)));

    //
    //toolbar wide menu
    //
    toolBarMenu->addAction(wideToolBarCheckBoxMenuItem);
//    wideToolBarCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
//        bool newToolBarIsWide = wideToolBarCheckBoxMenuItem.isSelected();
//        setToolBarWide(newToolBarIsWide);
//    });
    wideToolBarCheckBoxMenuItem->setChecked(leToolBarPanel->toolBarIsWide);
    wideToolBarCheckBoxMenuItem->setEnabled((toolBarSide->getType() == eTOP) || (toolBarSide->getType() == eBOTTOM));
    connect(wideToolBarCheckBoxMenuItem, SIGNAL(toggled(bool)), this, SLOT(on_setToolBarWide(bool)));

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
    connect(scrollBothMenuItem, &QAction::triggered, [=]{
        _scrollState = Editor::SCROLL_BOTH;
        setScroll(_scrollState);
        redrawPanel();
    });

    scrollNoneMenuItem = new QAction(tr("No Scrollbars"), this);
    scrollNoneMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollNoneMenuItem);
    scrollMenu->addAction(scrollNoneMenuItem);
    scrollNoneMenuItem->setChecked(_scrollState == Editor::SCROLL_NONE);
//    scrollNoneMenuItem.addActionListener((ActionEvent event) -> {
    connect(scrollNoneMenuItem, &QAction::triggered, [=]{
        _scrollState = Editor::SCROLL_NONE;
        setScroll(_scrollState);
        redrawPanel();
    });

    scrollHorizontalMenuItem = new QAction(tr("Horizontal Scrollbars"),this);
    scrollHorizontalMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollHorizontalMenuItem);
    scrollMenu->addAction(scrollHorizontalMenuItem);
    scrollHorizontalMenuItem->setChecked(_scrollState == Editor::SCROLL_HORIZONTAL);
//    scrollHorizontalMenuItem.addActionListener((ActionEvent event) -> {
    connect(scrollHorizontalMenuItem, &QAction::triggered, [=]{
        _scrollState = Editor::SCROLL_HORIZONTAL;
        setScroll(_scrollState);
        redrawPanel();
    });

    scrollVerticalMenuItem = new QAction(tr("Vertical scrollbars"), this);
    scrollVerticalMenuItem->setCheckable(true);
    scrollGroup->addAction(scrollVerticalMenuItem);
    scrollMenu->addAction(scrollVerticalMenuItem);
    scrollVerticalMenuItem->setChecked(_scrollState == Editor::SCROLL_VERTICAL);
//    scrollVerticalMenuItem.addActionListener((ActionEvent event) -> {
    connect(scrollVerticalMenuItem, &QAction::triggered, [=]{
        _scrollState = Editor::SCROLL_VERTICAL;
        setScroll(_scrollState);
        redrawPanel();
    });

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
    connect(tooltipNoneMenuItem, &QAction::triggered, [=]{
     tooltipsInEditMode = false;
     tooltipsWithoutEditMode = false;
     setAllShowToolTip(false);
    });

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
    connect(tooltipAlwaysMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_TooltipAlwaysMenuItem()));
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
    connect(tooltipInEditMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_TooltipInEditMenuItem()));
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
    connect(tooltipNotInEditMenuItem, SIGNAL(triggered(bool)), this, SLOT(on_TooltipNotInEditMenuItem()));

    //
    // show edit help
    //
    showHelpCheckBoxMenuItem = new QAction(tr("Show Help Bar in Edit Mode"));
    showHelpCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(showHelpCheckBoxMenuItem);
//    showHelpCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(showHelpCheckBoxMenuItem, &QAction::triggered, [=]{
        bool newShowHelpBar = showHelpCheckBoxMenuItem->isChecked();
        setShowHelpBar(newShowHelpBar);
    });
    showHelpCheckBoxMenuItem->setChecked(getShowHelpBar());

    //
    // Allow Repositioning
    //
    positionableCheckBoxMenuItem = new QAction(tr("Allow Repositioning"),this);
    positionableCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(positionableCheckBoxMenuItem);
//    positionableCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(positionableCheckBoxMenuItem, &QAction::triggered, [=]{
        setAllPositionable(positionableCheckBoxMenuItem->isChecked());
    });
    positionableCheckBoxMenuItem->setChecked(allPositionable());

    //
    // Allow Layout Control
    //
    controlCheckBoxMenuItem = new QAction(tr("Allow Layout Control"),this);
    controlCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(controlCheckBoxMenuItem);
//    controlCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(controlCheckBoxMenuItem, &QAction::triggered, [=]{
        setAllControlling(controlCheckBoxMenuItem->isChecked());
        redrawPanel();
    });
    controlCheckBoxMenuItem->setChecked(allControlling());

    //
    // use direct turnout control
    //
    useDirectTurnoutControlCheckBoxMenuItem = new QAction(tr("Use Direct Turnout Control"),this); //IN18N
    useDirectTurnoutControlCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(useDirectTurnoutControlCheckBoxMenuItem);
//    useDirectTurnoutControlCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(useDirectTurnoutControlCheckBoxMenuItem, &QAction::triggered, [=]{
        setDirectTurnoutControl(useDirectTurnoutControlCheckBoxMenuItem->isChecked());
    });
    useDirectTurnoutControlCheckBoxMenuItem->setChecked(useDirectTurnoutControl);

    //
    // antialiasing
    //
    antialiasingOnCheckBoxMenuItem = new QAction(tr("Enable antialiasing (Smoother lines)"),this);
    antialiasingOnCheckBoxMenuItem->setCheckable(true);
    optionMenu->addAction(antialiasingOnCheckBoxMenuItem);
//    antialiasingOnCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(antialiasingOnCheckBoxMenuItem, &QAction::triggered, [=]{
        antialiasingOn = antialiasingOnCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    antialiasingOnCheckBoxMenuItem->setChecked(antialiasingOn);

    //
    // edit title
    //
    optionMenu->addSeparator();
    QAction* titleItem = new QAction(tr("Edit Title") + "...",this);
    optionMenu->addAction(titleItem);
    //titleItem.addActionListener((ActionEvent event) -> {
    connect(titleItem, &QAction::triggered, [=]{
    //prompt for name
    QString newName =  JOptionPane::showInputDialog(getTargetFrame(),
            tr("%1").arg(tr("Enter New Title")),
            tr("Edit Layout Name"),
            JOptionPane::PLAIN_MESSAGE, QIcon(), QVariantList(), getLayoutName()).toString();

    if (newName != "") {
        if (newName != (getLayoutName())) {
            if (((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(newName)) {
                JOptionPane::showMessageDialog(nullptr, tr("Can not rename panel with the same name as an existing panel"), tr("Panel name already exists!"),
                        JOptionPane::ERROR_MESSAGE);
            } else {
                JmriJFrame::setTitle(newName);
                setLayoutName(newName);
                getLayoutTrackDrawingOptions()->setName(newName);
                ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->renameEditorPanel(this);
                setDirty();

                if (toolBarSide->getType() == (eFLOAT) && isEditable()) {
                    // Rebuild the toolbox after a name change.
                    deletefloatingEditToolBoxFrame();
                    createfloatingEditToolBoxFrame();
                }
            }
        }
     }
    });

    //
    // set background color
    //
    QAction* backgroundColorMenuItem = new QAction(tr("Set Background Color", "..."),this);
    optionMenu->addAction(backgroundColorMenuItem);
//    backgroundColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(backgroundColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Background Color%1").arg(""),
                defaultBackgroundColor);
        if (!desiredColor.isValid() && defaultBackgroundColor != (desiredColor)) {
            defaultBackgroundColor = desiredColor;
            setBackgroundColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });

    //
    // set default text color
    //
    QAction* textColorMenuItem = new QAction(tr("Default Text Color", "..."),this);
    optionMenu->addAction(textColorMenuItem);
//    textColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(textColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Default Text Color%1").arg(""),
                defaultTextColor);
        if (!desiredColor.isValid() && defaultTextColor != (desiredColor)) {
            setDefaultTextColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });

    if (editorUseOldLocSize)
    {
     //
     //  save location and size
     //
     QAction* locationItem = new QAction(tr("Set Location"), this);
     optionMenu->addAction(locationItem);
 //    locationItem.addActionListener((ActionEvent event) -> {
     connect(locationItem, &QAction::triggered, [=] {
     setCurrentPositionAndSize();
     log->debug(tr("Bounds:%1, %2, %3, %4, %5, %6").arg(gContext->getUpperLeftX()).arg(gContext->getUpperLeftY()).arg(gContext->getWindowWidth()).arg(gContext->getWindowHeight()).arg(gContext->getLayoutWidth()).arg(gContext->getLayoutHeight()));
     });
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
    connect(backgroundItem, &QAction::triggered, [=]{
        addBackground();
        //note: panel resized in addBackground
        setDirty();
        redrawPanel();
    });

    // add fast clock
    QAction* clockItem = new QAction(tr("Add %1").arg(tr("Fast Clock")), this);
    optionsAddMenu->addAction(clockItem);
//    clockItem.addActionListener((ActionEvent event) -> {
    connect(clockItem, &QAction::triggered, [=]{
        AnalogClock2Display* c = addClock();
        unionToPanelBounds(c->getBounds());
        setDirty();
        c->paint(editScene);
        redrawPanel();
    });

    //add turntable
    QAction* turntableItem = new QAction(tr("Add Turntable"),this);
    optionsAddMenu->addAction(turntableItem);
//    turntableItem.addActionListener((ActionEvent event) -> {
    connect(turntableItem, &QAction::triggered, [=]{
        QPointF pt = windowCenter();
        if (selectionActive) {
            pt = MathUtil::midPoint(getSelectionRect());
        }
        addTurntable(pt);
        //note: panel resized in addTurntable
        setDirty();
        redrawPanel();
    });

    // add reporter
    QAction* reporterItem = new QAction(tr("Add Reporter Label") + "...", this);
    optionsAddMenu->addAction(reporterItem);
//    reporterItem.addActionListener((ActionEvent event) -> {
    connect(reporterItem, &QAction::triggered, [=]{
        QPointF pt = windowCenter();
        if (selectionActive) {
            pt = MathUtil::midPoint(getSelectionRect());
        }
        EnterReporterDialog* d = new EnterReporterDialog(this);
        d->enterReporter((int) pt.x(), (int) pt.y());
        //note: panel resized in enterReporter        //note: panel resized in enterReporter
        setDirty();
        redrawPanel();
    });

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
    connect(showGridCheckBoxMenuItem, &QAction::triggered, [=]{
        drawGrid = showGridCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    showGridCheckBoxMenuItem->setChecked(getDrawGrid());

    //snap to grid on add
    snapToGridOnAddCheckBoxMenuItem = new QAction(tr("Snap to Grid when Adding"));
    snapToGridOnAddCheckBoxMenuItem->setCheckable(true);
//    snapToGridOnAddCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(
//            Bundle.getMessage("SnapToGridOnAddAccelerator")),
//            primary_modifier | ActionEvent.SHIFT_MASK));
    gridMenu->addAction(snapToGridOnAddCheckBoxMenuItem);
//    snapToGridOnAddCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(snapToGridOnAddCheckBoxMenuItem, &QAction::triggered, [=]{
        snapToGridOnAdd = snapToGridOnAddCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    snapToGridOnAddCheckBoxMenuItem->setChecked(snapToGridOnAdd);

    //snap to grid on move
    snapToGridOnMoveCheckBoxMenuItem = new QAction(tr("Snap to Grid when Moving"),this);
    snapToGridOnMoveCheckBoxMenuItem->setCheckable(true);
//    snapToGridOnMoveCheckBoxMenuItem.setAccelerator(KeyStroke.getKeyStroke(stringsToVTCodes.get(
//            Bundle.getMessage("SnapToGridOnMoveAccelerator")),
//            primary_modifier | ActionEvent.SHIFT_MASK));
    gridMenu->addAction(snapToGridOnMoveCheckBoxMenuItem);
//    snapToGridOnMoveCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(snapToGridOnMoveCheckBoxMenuItem, &QAction::triggered, [=]{
        snapToGridOnMove = snapToGridOnMoveCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    snapToGridOnMoveCheckBoxMenuItem->setChecked(snapToGridOnMove);

    //specify grid square size
    QAction* gridSizeItem = new QAction(tr("SetGridSizes") + "...", this);
    gridMenu->addAction(gridSizeItem);
//    gridSizeItem.addActionListener((ActionEvent event) -> {
    connect(gridSizeItem, &QAction::triggered, [=]{
        enterGridSizes();
    });

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
    connect(jmi, &QAction::triggered, [=]{
        LayoutTrackDrawingOptionsDialog* ltdod
                = new LayoutTrackDrawingOptionsDialog(
                        this, true, getLayoutTrackDrawingOptions());
        ltdod->setVisible(true);
    });

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

    QAction* trackColorMenuItem = new QAction(tr("Set Default Track Color"),this);
    trkColourMenu->addAction(trackColorMenuItem);
//    trackColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(trackColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Default Track Color"),
                defaultTrackColor);
        if (!desiredColor .isValid() && defaultTrackColor != (desiredColor)) {
            setDefaultTrackColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });

    QAction* trackOccupiedColorMenuItem = new QAction(tr("Set Default Occupied Track Color"),this);
    trkColourMenu->addAction(trackOccupiedColorMenuItem);
//    trackOccupiedColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(trackOccupiedColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Default Occupied Track Color"),
                defaultOccupiedTrackColor);
        if (!desiredColor.isValid() && defaultOccupiedTrackColor != (desiredColor)) {
            setDefaultOccupiedTrackColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });

    QAction* trackAlternativeColorMenuItem = new QAction(tr("Set Default Alternative Track Color"),this);
    trkColourMenu->addAction(trackAlternativeColorMenuItem);
//    trackAlternativeColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(trackAlternativeColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Default Alternative Track Color"),
                defaultAlternativeTrackColor);
        if (!desiredColor.isValid() && defaultAlternativeTrackColor != (desiredColor)) {
            setDefaultAlternativeTrackColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });
    //Automatically Assign Blocks to Track
    autoAssignBlocksCheckBoxMenuItem = new QAction(tr("Automatically Assign Blocks to Track"),this);
    autoAssignBlocksCheckBoxMenuItem->setCheckable(true);
    trackMenu->addAction(autoAssignBlocksCheckBoxMenuItem);
//    autoAssignBlocksCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(autoAssignBlocksCheckBoxMenuItem, &QAction::triggered, [=]{
        autoAssignBlocks = autoAssignBlocksCheckBoxMenuItem->isChecked();
    });
    autoAssignBlocksCheckBoxMenuItem->setChecked(autoAssignBlocks);

    //add hideTrackSegmentConstructionLines menu item
    hideTrackSegmentConstructionLinesCheckBoxMenuItem = new QAction(tr("Hide Track Construction Lines"));
    hideTrackSegmentConstructionLinesCheckBoxMenuItem->setCheckable(true);
    trackMenu->addAction(hideTrackSegmentConstructionLinesCheckBoxMenuItem);
//    hideTrackSegmentConstructionLinesCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(hideTrackSegmentConstructionLinesCheckBoxMenuItem, &QAction::triggered, [=]{
        int show = TrackSegment::SHOWCON;

        if (hideTrackSegmentConstructionLinesCheckBoxMenuItem->isChecked()) {
            show = TrackSegment::HIDECONALL;
        }

        for (TrackSegment* ts : getTrackSegments()) {
            ts->hideConstructionLines(show);
        }
        redrawPanel();
    });
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
    connect(animationCheckBoxMenuItem, &QAction::triggered, [=]{
        bool mode = animationCheckBoxMenuItem->isChecked();
        setTurnoutAnimation(mode);
    });
    animationCheckBoxMenuItem->setChecked(true);

    //circle on Turnouts
    turnoutCirclesOnCheckBoxMenuItem = new QAction(tr("Show Turnout Circles"), this);
    turnoutCirclesOnCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(turnoutCirclesOnCheckBoxMenuItem);
//    turnoutCirclesOnCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(turnoutCirclesOnCheckBoxMenuItem, &QAction::triggered, [=]{
        turnoutCirclesWithoutEditMode = turnoutCirclesOnCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    turnoutCirclesOnCheckBoxMenuItem->setChecked(turnoutCirclesWithoutEditMode);

    //select turnout circle color
    QAction* turnoutCircleColorMenuItem = new QAction(tr("Set Turnout Circle Color"), this);

//    turnoutCircleColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(turnoutCircleColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("Set Turnout Circle Color"),
                turnoutCircleColor);
        if (!desiredColor.isValid() && turnoutCircleColor != (desiredColor)) {
            setTurnoutCircleColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });
    turnoutOptionsMenu->addAction(turnoutCircleColorMenuItem);

    //select turnout circle thrown color
    QAction* turnoutCircleThrownColorMenuItem = new QAction("Set Turnout Circle Thrown Color",this);
//    turnoutCircleThrownColorMenuItem.addActionListener((ActionEvent event) -> {
    connect(turnoutCircleThrownColorMenuItem, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(this,
                tr("TurnoutCircleThrownColor"),
                turnoutCircleThrownColor);
        if (!desiredColor.isValid() && turnoutCircleThrownColor != (desiredColor)) {
            setTurnoutCircleThrownColor(desiredColor);
            setDirty();
            redrawPanel();
        }
    });
    turnoutOptionsMenu->addAction(turnoutCircleThrownColorMenuItem);

    turnoutFillControlCirclesCheckBoxMenuItem = new QAction(tr("Fill Turnout Circles"));
    turnoutFillControlCirclesCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(turnoutFillControlCirclesCheckBoxMenuItem);
//    turnoutFillControlCirclesCheckBoxMenuItem.addActionListener((ActionEvent event) ->
    connect(turnoutFillControlCirclesCheckBoxMenuItem, &QAction::triggered, [=]{
//    {
        turnoutFillControlCircles = turnoutFillControlCirclesCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    turnoutFillControlCirclesCheckBoxMenuItem->setChecked(turnoutFillControlCircles);

    //select turnout circle size
    QMenu* turnoutCircleSizeMenu = new QMenu(tr("Set Turnout Circle Size"));
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
    turnoutOptionsMenu->addMenu(turnoutCircleSizeMenu);

    //add "enable drawing of unselected leg " menu item (helps when diverging angle is small)
    turnoutDrawUnselectedLegCheckBoxMenuItem = new QAction(tr("Draw Unselected Turnout Leg"),this);
    turnoutDrawUnselectedLegCheckBoxMenuItem->setCheckable(true);
    turnoutOptionsMenu->addAction(turnoutDrawUnselectedLegCheckBoxMenuItem);
//    turnoutDrawUnselectedLegCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(turnoutDrawUnselectedLegCheckBoxMenuItem, &QAction::triggered, [=]{
        turnoutDrawUnselectedLeg = turnoutDrawUnselectedLegCheckBoxMenuItem->isChecked();
        redrawPanel();
    });
    turnoutDrawUnselectedLegCheckBoxMenuItem->setChecked(turnoutDrawUnselectedLeg);

    return optionMenu;
}

void LayoutEditor::on_TooltipAlwaysMenuItem()
{
 tooltipsInEditMode = true;
 tooltipsWithoutEditMode = true;
 setAllShowToolTip(true);
}
void LayoutEditor::on_TooltipInEditMenuItem()
{
 tooltipsInEditMode = true;
 tooltipsWithoutEditMode = false;
 setAllShowToolTip(isEditable());
}
void LayoutEditor::on_TooltipNotInEditMenuItem()
{
 tooltipsInEditMode = false;
 tooltipsWithoutEditMode = true;
 setAllShowToolTip(!isEditable());
}

/*============================================*\
|* LayoutTrackDrawingOptions accessor methods *|
\*============================================*/

//@Nonnull
/*public*/ LayoutTrackDrawingOptions* LayoutEditor::getLayoutTrackDrawingOptions()
{
 if (layoutTrackDrawingOptions == nullptr)
 {
  layoutTrackDrawingOptions = new LayoutTrackDrawingOptions(getLayoutName());
  // integrate LayoutEditor drawing options with previous drawing options
  layoutTrackDrawingOptions->setMainBlockLineWidth(gContext->getMainlineTrackWidth());
  layoutTrackDrawingOptions->setSideBlockLineWidth(gContext->getSidelineTrackWidth());
  layoutTrackDrawingOptions->setMainRailWidth(gContext->getMainlineTrackWidth());
  layoutTrackDrawingOptions->setSideRailWidth(gContext->getSidelineTrackWidth());
  layoutTrackDrawingOptions->setMainRailColor(mainlineTrackColor);
  layoutTrackDrawingOptions->setSideRailColor(sidelineTrackColor);
  layoutTrackDrawingOptions->setBlockDefaultColor(defaultTrackColor);
  layoutTrackDrawingOptions->setBlockOccupiedColor(defaultOccupiedTrackColor);
  layoutTrackDrawingOptions->setBlockAlternativeColor(defaultAlternativeTrackColor);
 }
 return layoutTrackDrawingOptions;
}

/*public*/ void LayoutEditor::setLayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo) {
    layoutTrackDrawingOptions = ltdo;

    // integrate LayoutEditor drawing options with previous drawing options
    gContext->setMainlineTrackWidth( layoutTrackDrawingOptions->getMainBlockLineWidth() );
    gContext->setSidelineTrackWidth( layoutTrackDrawingOptions->getSideBlockLineWidth() );
    defaultTrackColor = layoutTrackDrawingOptions->getMainRailColor();
    sidelineTrackColor = layoutTrackDrawingOptions->getSideRailColor();

    redrawPanel();
}
/**
 * setup the Layout Editor Tools menu
 *
 * @param menuBar the menu bar to add the Tools menu to
 */
/*protected*/ void LayoutEditor::setupToolsMenu(/*@Nonnull*/ QMenuBar* menuBar) {
    QMenu* toolsMenu = new QMenu(tr("Tools"));

//    toolsMenu.setMnemonic(stringsToVTCodes.get(tr("MenuToolsMnemonic")));
    menuBar->addMenu(toolsMenu);

    //setup checks menu
    getLEChecks()->setupChecksMenu(toolsMenu);

    //assign blocks to selection
    QAction* jmi = new QAction(tr("Assign Block To Selection") + "...");
    jmi->setToolTip(tr("Select this to assign the block from the toolbar to all selected layout tracks."));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up scale track diagram dialog
        assignBlockToSelection();
    });

    //scale track diagram
    jmi = new QAction(tr("Scale/Translate Track Diagram") + "...");
    jmi->setToolTip(tr("Select this to scale and/or translate all layout track"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
    //bring up scale track diagram dialog
    ScaleTrackDiagramDialog* d = new ScaleTrackDiagramDialog(this);
    d->scaleTrackDiagram();
    });

    //translate selection
    jmi = new QAction(tr("Translate Selection") + "...", this);
    jmi->setToolTip(tr("Click here to translate (move) the currently selected items"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up translate selection dialog
        moveSelection();
    });

    //undo translate selection
    jmi = new QAction(tr("Undo Translate Selection"),this);
    jmi->setToolTip(tr("Click here to undo the translate (move) selection"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //undo previous move selection
        undoMoveSelection();
    });

    //reset turnout size to program defaults
    jmi = new QAction(tr("Use Program Default Turnout Size"),this);
    jmi->setToolTip(tr("Click here to reset to the default turnout size"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //undo previous move selection
        resetTurnoutSize();
    });
    toolsMenu->addSeparator();

    //skip turnout
    skipTurnoutCheckBoxMenuItem = new QAction(tr("Skip Unsignaled Internal Turnouts"), this);
    skipTurnoutCheckBoxMenuItem->setCheckable(true);
    skipTurnoutCheckBoxMenuItem->setToolTip(tr("SkipInternalTurnoutToolTip"));
    connect(skipTurnoutCheckBoxMenuItem, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), skipTurnoutCheckBoxMenuItem->toolTip(), this);
    });
    toolsMenu->addAction(skipTurnoutCheckBoxMenuItem);
//    skipTurnoutCheckBoxMenuItem.addActionListener((ActionEvent event) -> {
    connect(skipTurnoutCheckBoxMenuItem, &QAction::triggered, [=]{
        setIncludedTurnoutSkipped(skipTurnoutCheckBoxMenuItem->isChecked());
    });
    skipTurnoutCheckBoxMenuItem->setChecked(isIncludedTurnoutSkipped());

    //set signals at turnout
    jmi = new QAction(tr("Set Signal Heads at Turnout") + "...");
    jmi->setToolTip(tr("Click here to set up the signal heads at a turnout"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at turnout tool dialog
        getLETools()->setSignalsAtTurnout(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    //set signals at block boundary
    jmi = new QAction(tr("Set Signal Heads at Block Boundary") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a block boundary"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at block boundary tool dialog
        getLETools()->setSignalsAtBlockBoundary(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    //set signals at crossover turnout
    jmi = new QAction(tr("Set Signal Heads at Crossover") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a crossover"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at crossover tool dialog
        getLETools()->setSignalsAtXoverTurnout(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    //set signals at level crossing
    jmi = new QAction(tr("Set Signal Heads at Level Crossing") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a level crossing"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at level crossing tool dialog
        getLETools()->setSignalsAtLevelXing(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    //set signals at throat-to-throat turnouts
    jmi = new QAction(tr("Set Signal Heads at Throat-to-Throat Turnouts") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signals on throat-to-throat turnouts"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at throat-to-throat turnouts tool dialog
        getLETools()->setSignalsAtThroatToThroatTurnouts(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    //set signals at 3-way turnout
    jmi = new QAction(tr("Set Signal Heads at 3-Way Turnout") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a 3-way turnout"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at 3-way turnout tool dialog
        getLETools()->setSignalsAt3WayTurnout(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    jmi = new QAction(tr("Set Signal Heads at a Slip") + "...", this);
    jmi->setToolTip(tr("Click here to set up the signal heads at a single or double slip"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        //bring up signals at throat-to-throat turnouts tool dialog
        getLETools()->setSignalsAtSlip(leToolBarPanel->signalIconEditor, leToolBarPanel->signalFrame);
    });

    jmi = new QAction(tr("Entry Exit") + "...", this);
    jmi->setToolTip(tr("Click here to set up Entry-Exit"));
    connect(jmi, &QAction::hovered, [=]{
        QToolTip::showText(QCursor::pos(), jmi->toolTip(), this);
    });
    toolsMenu->addAction(jmi);
//    jmi.addActionListener((ActionEvent event) -> {
    connect(jmi, &QAction::triggered, [=]{
        if (addEntryExitPairAction == nullptr) {
            addEntryExitPairAction = new AddEntryExitPairAction("ENTRY EXIT", this);
        }
        addEntryExitPairAction->actionPerformed(0);
    });

//    toolsMenu->addSeparator();
//    QAction* clearAction = new QAction(tr("Clear track"), this);
//    toolsMenu->addAction(clearAction);
//    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(on_clearTrack()));
}   // setupToolsMenu

/**
 * get the toolbar side
 *
 * @return the side where to put the tool bar
 */
/*public*/ ToolBarSide* LayoutEditor::getToolBarSide() {
    return toolBarSide;
}

/**
 * set the tool bar side
 *
 * @param newToolBarSide on which side to put the toolbar
 */
/*public*/ void LayoutEditor::setToolBarSide(ToolBarSide* newToolBarSide) {
    // null if edit toolbar is not setup yet...
    if (newToolBarSide != (toolBarSide)) {
        toolBarSide = newToolBarSide;
        UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");//.ifPresent((prefsMgr) -> prefsMgr.setProperty(getWindowFrameRef(), "toolBarSide", toolBarSide->getName()));
        if(prefsMgr)
         prefsMgr->setProperty(getWindowFrameRef(), "toolBarSide", toolBarSide->getName());
        toolBarSideTopButton->setChecked(toolBarSide->getType() == eTOP);
        toolBarSideLeftButton->setChecked(toolBarSide->getType() == eLEFT);
        toolBarSideBottomButton->setChecked(toolBarSide->getType() == eBOTTOM);
        toolBarSideRightButton->setChecked(toolBarSide->getType() == eRIGHT);
        toolBarSideFloatButton->setChecked(toolBarSide->getType() == eFLOAT);

        setupToolBar(); // re-layout all the toolbar items

        if (toolBarSide->getType() == eFLOAT) {
            if (editToolBarContainerPanel != nullptr) {
                editToolBarContainerPanel->setVisible(false);
            }
            if (floatEditHelpPanel != nullptr) {
                floatEditHelpPanel->setVisible(isEditable() && getShowHelpBar());
            }
        } else {
            if (floatingEditToolBoxFrame != nullptr) {
                deletefloatingEditToolBoxFrame();
            }
            editToolBarContainerPanel->setVisible(isEditable());
            if (getShowHelpBar()) {
                helpBarPanel->setVisible(isEditable());
                // not sure why... but this is the only way I could
                // get everything to layout correctly
                // when the helpbar is visible...
                bool editMode = isEditable();
                setAllEditable(!editMode);
                setAllEditable(editMode);
            }
        }
        wideToolBarCheckBoxMenuItem->setEnabled(
                toolBarSide->getType() == eTOP
                || toolBarSide->getType() == eBOTTOM);
    }
}   // setToolBarSide

void LayoutEditor::on_translateSelections()
{
 //bring up translate selection dialog
 moveSelection();
}

void LayoutEditor::on_clearTrack()
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



#if 0
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
#endif
//
//update drop down menu display order for all combo boxes (from prefs)
//
///*private*/ void LayoutEditor::updateAllComboBoxesDropDownListDisplayOrderFromPrefs() {
//    //1st call the recursive funtion starting from the edit toolbar container
//#if 0
//    updateComboBoxDropDownListDisplayOrderFromPrefs(editToolBarContainerPanel);
//    updateComboBoxDropDownListDisplayOrderFromPrefs(floatingEditContentScrollPane);
//#endif
//    //and now that that's done update the drop down menu display order menu
//    updateDropDownMenuDisplayOrderMenu();
//}

//
//update drop down menu display order for all combo boxes (from prefs)
//note: recursive function that walks down the component / container tree
//
///*private*/ void LayoutEditor::updateComboBoxDropDownListDisplayOrderFromPrefs(/*@Nonnull*/ Component* inComponent)
//{
//#if 0
//    if (qobject_cast<JmriBeanComboBox*>(inComponent))
//    {
//        //try to get the preference
//        //InstanceManager::getOptionalDefault("UserPreferencesManager").ifPresent((prefsMgr) ->
//     UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
//     if(prefsMgr)
//     {
//            QString windowFrameRef = getWindowFrameRef();

//            //this is the preference name
//            QString ddldoPrefName = "DropDownListsDisplayOrder";

//            //this is the default value if we can't find it in any preferences
//            QString ddldoPref = "DISPLAYNAME";

//            QVariant ddldoProp = prefsMgr->getProperty(windowFrameRef, ddldoPrefName);

//            if (ddldoProp.isValid()) {
//                //this will be the value if this combo box doesn't have a saved preference.
//                ddldoPref = ddldoProp.toString();
//            } else {
//                //save a default preference
//                prefsMgr->setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
//            }

//            //now try to get a preference specific to this combobox
//            JmriBeanComboBox* jbcb = (JmriBeanComboBox*) inComponent;
//            if (qobject_cast<JTextField*>(inComponent)
//            {
//                jbcb = (JmriBeanComboBox*) SwingUtilities.getUnwrappedParent(jbcb);
//            }
//            if (jbcb != null) {
//                QString ttt = jbcb.getToolTipText();
//                if (ttt != null) {
//                    //change the name of the preference based on the tool tip text
//                    ddldoPrefName = String.format("%s.%s", ddldoPrefName, ttt);
//                    //try to get the preference
//                    ddldoProp = prefsMgr.getProperty(getWindowFrameRef(), ddldoPrefName);
//                    if (ddldoProp != null) { //if we found it...
//                        ddldoPref = ddldoProp.toString(); //get it's (string value
//                    } else { //otherwise...
//                        //save it in the users preferences
//                        prefsMgr.setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
//                    }
//                }

//                //now set the combo box display order
//                if (ddldoPref.equals("DISPLAYNAME")) {
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
//                } else if (ddldoPref.equals("USERNAME")) {
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.USERNAME);
//                } else if (ddldoPref.equals("SYSTEMNAME")) {
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.SYSTEMNAME);
//                } else if (ddldoPref.equals("USERNAMESYSTEMNAME")) {
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.USERNAMESYSTEMNAME);
//                } else if (ddldoPref.equals("SYSTEMNAMEUSERNAME")) {
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.SYSTEMNAMEUSERNAME);
//                } else {
//                    //must be a bogus value... lets re-set everything to DISPLAYNAME
//                    ddldoPref = "DISPLAYNAME";
//                    prefsMgr.setProperty(windowFrameRef, ddldoPrefName, ddldoPref);
//                    jbcb.setDisplayOrder(JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
//                }
//            }
//        });

//    } else if (qobject_cast<Container*>(inComponent)) {
//        for (Component* c : ((Container*) inComponent).getComponents()) {
//            updateComboBoxDropDownListDisplayOrderFromPrefs(c);
//        }
//    } else {
//        //nothing to do here... move along...
//    }
//#endif
//}
#if 1
//
//
//
/*private*/ void LayoutEditor::on_setToolBarSide(QAction* act)
{
 if(editToolBarContainerPanel)
   //removeDockWidget(editToolBarContainerPanel);
  editToolBarContainerPanel->layout()->removeWidget(editToolBarContainerPanel);
 on_setToolBarSide(act->text());
}

/*private*/ void LayoutEditor::on_setToolBarSide(QString newToolBarSide)
{
 // null if edit toolbar is not setup yet...
 if (newToolBarSide !=(toolBarSide->getName()))
 {
  if ((editModeCheckBoxMenuItem != nullptr) && !(newToolBarSide ==(toolBarSide->getName()))) {
   //toolBarSide->getName() = newToolBarSide;
   UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager")); //.ifPresent((prefsMgr) -> {
   if(prefsMgr)
   prefsMgr->setProperty(getWindowFrameRef(), "toolBarSide", toolBarSide->getName());
  }//);
  toolBarSide = new ToolBarSide(newToolBarSide);
  toolBarSideTopButton->setChecked(toolBarSide->getType() == (eTOP));
  toolBarSideLeftButton->setChecked(toolBarSide->getType() == (eLEFT));
  toolBarSideBottomButton->setChecked(toolBarSide->getType() == (eBOTTOM));
  toolBarSideRightButton->setChecked(toolBarSide->getType() == (eRIGHT));
  toolBarSideFloatButton->setChecked(toolBarSide->getType() == (eFLOAT));

 #if 1
  setupToolBar(); //re-layout all the toolbar items

  if (toolBarSide->getType() == eFLOAT)
  {
    if (editToolBarContainerPanel != nullptr) {
        editToolBarContainerPanel->setVisible(false);
    }
    if (floatEditHelpPanel != nullptr) {
        floatEditHelpPanel->setVisible(isEditable() && getShowHelpBar());
    }
  }
  else
  {
   if (floatingEditToolBoxFrame != nullptr)
   {
       deletefloatingEditToolBoxFrame();
   }
   editToolBarContainerPanel->setVisible(isEditable());
//   if (getShowHelpBar()) {
//       helpBarPanel->setVisible(isEditable());
//       //not sure why... but this is the only way I could
//       //get everything to layout correctly
//       //when the helpbar is visible...
//       bool editMode = isEditable();
//       setAllEditable(!editMode);
//       setAllEditable(editMode);
//   }
  }
  wideToolBarCheckBoxMenuItem->setEnabled(
          toolBarSide->getType() == eTOP
          || toolBarSide->getType() == eBOTTOM);
 }
}   // setToolBarSide
#endif


//
//
//
/*private*/ void LayoutEditor::on_setToolBarWide(bool newToolBarIsWide)
{
 //null if edit toolbar not setup yet...
 if ((editModeCheckBoxMenuItem != nullptr) && (toolBarIsWide != newToolBarIsWide))
 {
  toolBarIsWide = newToolBarIsWide;

  wideToolBarCheckBoxMenuItem->setChecked(toolBarIsWide);
  UserPreferencesManager* prefsMgr = static_cast<UserPreferencesManager*>(InstanceManager::getOptionalDefault("UserPreferencesManager"));
  if(prefsMgr) {
      //Note: since prefs default to false and we want wide to be the default
      //we invert it and save it as thin
      prefsMgr->setSimplePreferenceState(getWindowFrameRef() + ".toolBarThin", !toolBarIsWide);
  }//);
#if 1
  setupToolBar(); //re-layout all the toolbar items

  if (getShowHelpBar()) {
      //not sure why, but this is the only way I could
      //get everything to layout correctly
      //when the helpbar is visible...
      bool editMode = isEditable();
      setAllEditable(!editMode);
      setAllEditable(editMode);
  } else {
      helpBarPanel->setVisible(isEditable() && getShowHelpBar());
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
