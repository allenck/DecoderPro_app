#include "layouteditor.h"
#include "instancemanager.h"
#include <QHBoxLayout>

//LayoutEditor::LayoutEditor(QString name, QObject *parent) :
//    PanelEditor(parent)
//{
// thisPanel = NULL;
// topEditBar = NULL;
// helpBar = NULL;
// skipIncludedTurnout = false;
//}
/**
 * Provides a scrollable Layout Panel and editor toolbars (that can be
 *		hidden)
 * <P>
 * This module serves as a manager for the LayoutTurnout, Layout Block,
 *		PositionablePoint, Track Segment, and LevelXing objects which are
 *      integral subparts of the LayoutEditor class.
 * <P>
 * All created objects are put on specific levels depending on their
 *		type (higher levels are in front):
 * Note that higher numbers appear behind lower numbers.
 * <P>
 * The "contents" List keeps track of all text and icon label objects
 *		added to the targetframe for later manipulation.  Other Lists
 *      keep track of drawn items.
 * <P>
 * Based in part on PanelEditor.java (Bob Jacobsen (c) 2002, 2003). In
 *		particular, text and icon label items are copied from Panel
 *		editor, as well as some of the control design.
 *
 * @author Dave Duchamp  Copyright: (c) 2004-2007
 * @version $Revision: 22475 $
 */

///*public*/ class LayoutEditor extends jmri.jmrit.display.panelEditor.PanelEditor {

    // Defined text resource
//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");
//    static final ResourceBundle rbx = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");
//    static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");


//    /*public*/ LayoutEditor() { this("My Layout");}

LayoutEditor::LayoutEditor(QString name, QObject *parent) :
    QMainWindow(parent)
{
    //super(name);

 thisPanel = NULL;
 topEditBar = NULL;
 helpBar = NULL;
 skipIncludedTurnout = false;
 //    /*private*/ ConnectivityUtil conTools = NULL;
 itemGroup = NULL;
 blockIDField = new QLineEdit();
 blockIDField->setMaxLength(8);
 blockSensor = new QLineEdit(5);
 blockSensor->setMaxLength(5);
 turnoutRHBox = new QCheckBox(tr("RightHandAbbreviation"));
 turnoutLHBox = new QCheckBox(tr("LeftHandAbbreviation"));
 turnoutWYEBox = new QCheckBox(tr("WYEAbbreviation"));
 doubleXoverBox = new QCheckBox(tr("DoubleCrossOver"));
 rhXoverBox = new QCheckBox(tr("RHCrossOver"));
 lhXoverBox = new QCheckBox(tr("LHCrossOver"));
 rotationPanel = new QDialog(this);
 rotationField = new QLineEdit();
 rotationField->setMaxLength(3);
 nextTurnout = new QLineEdit();
 nextTurnout->setMaxLength(5);
 extraTurnoutPanel = new QDialog(this);
 extraTurnout = new QLineEdit();
 extraTurnout->setMaxLength(5);
 levelXingBox = new QCheckBox(tr("LevelCrossing"));
 layoutSingleSlipBox = new QCheckBox(tr("LayoutSingleSlip"));
 layoutDoubleSlipBox = new QCheckBox(tr("LayoutDoubleSlip"));
 endBumperBox = new QCheckBox(tr("EndBumper"));
 anchorBox = new QCheckBox(tr("Anchor"));
 trackBox = new QCheckBox(tr("TrackSegment"));

 dashedLine = new QCheckBox(tr("Dashed"));
 mainlineTrack = new QCheckBox(tr("MainlineBox"));

 QCheckBox* sensorBox = new QCheckBox(tr("SensorIcon"));
 nextSensor = new QLineEdit();
 nextSensor.setMaxLength(5);
 sensorIconEditor = NULL;
     /*public*/ JFrame sensorFrame;

 signalBox = new QCheckBox(tr("SignalIcon"));
 nextSignalHead = new QLineEdit();
 nextSignalHead->setMaxLength(5);
 signalIconEditor = NULL;
     /*public*/ JFrame signalFrame;

 signalMastBox = new QCheckBox(tr("SignalMastIcon"));
 nextSignalMast = new QLineEdit(5);
 nextSignalMast->setMaxLength(5);
 textLabelBox = new QCheckBox(tr("TextLabel"));
 textLabel = new QLineEdit(this);
 textLabel->setMaxLength(8);
 memoryBox = new QCheckBox(tr("Memory"));
 textMemory = new QLineEdit(this);
 textMemory.setMaxLength(8);
 iconLabelBox = new QCheckBox(tr("IconLabel"));
 iconEditor = NULL;
     /*private*/ JFrame iconFrame = NULL;

 multiSensorBox = new QCheckBox(tr("MultiSensor")+"...");
 multiSensorFrame = NULL;

 xLabel = new QLabel("00");
 yLabel = new QLabel("00");

 delayedPopupTrigger = false;
 currentPoint = new QPointF(100.0,100.0);
 dLoc = new QPointF(0.0,0.0);
     ///*private*/ int savedMSX = 0;
     ///*private*/ int savedMSY = 0;
 height = 100;
 width = 100;
     ///*private*/ int numTurnouts = 0;
 newTrack = NULL;
 panelChanged = false;

     // selection variables
 selectionActive = false;
 selectionX = 0.0;
 selectionY = 0.0;
 selectionWidth = 0.0;
 selectionHeight = 0.0;
 noWarnPositionablePoint = false;
 noWarnLayoutTurnout = false;
 noWarnLevelXing = false;
 noWarnSlip = false;
 noWarnTurntable = false;

     // Option menu items
     /*private*/ QCheckBoxMenuItem editModeItem = NULL;
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
 trackColorButtonGroup = NULL;
 trackOccupiedColorButtonGroup = NULL;
 trackAlternativeColorButtonGroup = NULL;
 textColorButtonGroup = NULL;
 backgroundColorButtonGroup = NULL;
 turnoutCircleColorButtonGroup = NULL;
 turnoutCircleSizeButtonGroup = NULL;
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
 trackColorCount = 0;
 trackOccupiedColorCount = 0;
 trackAlternativeColorCount = 0;
 textColorCount = 0;
 turnoutCircleColorCount = 0;
 turnoutCircleSizeCount = 0;
 turnoutDrawUnselectedLeg = true;
 backgroundColorCount = 0;
 autoAssignBlocks = false;
 startDel = new QPointF(0.0,0.0); // starting delta coordinates
 selectedObject = NULL; // selected object, NULL if nothing selected
 prevSelectedObject = NULL; // previous selected object, for undo
 selectedPointType = 0;   // connection type within the selected object
 foundObject = NULL; // found object, NULL if nothing found
 foundLocation = new QPointF(0.0,0.0);  // location of found object

 foundPointType = 0;   // connection type within the found object

 //@SuppressWarnings("unused")
 foundNeedsConnect = false; // true if found point needs a connection
 beginObject = NULL; // begin track segment connection object, NULL if none
 beginLocation = new QPointF(0.0,0.0);  // location of begin object
 beginPointType = 0;   // connection type within begin connection object
 currentLocation = new QPointF(0.0,0.0); // current location

 // program default turnout size parameters
 turnoutBXDefault = 20.0;  // RH, LH, WYE
 turnoutCXDefault = 20.0;
 turnoutWidDefault = 10.0;
 xOverLongDefault = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 xOverHWidDefault = 10.0;
 xOverShortDefault = 10.0;

 // Lists of items that describe the Layout, and allow it to be drawn
 //		Each of the items must be saved to disk over sessions
 turnoutList = new QVector<LayoutTurnout>();  // LayoutTurnouts
 trackList = new QVector<TrackSegment>();  // TrackSegment list
 pointList = new QVector<PositionablePoint>();  // PositionablePoint list
 xingList = new QVector<LevelXing>();  // LevelXing list
// /*public*/ QVector<LayoutSlip> slipList = new QVector<LayoutSlip>();  // Layout slip list
// /*public*/ QVector<LayoutTurntable> turntableList = new QVector<LayoutTurntable>(); // Turntable list
 // counts used to determine unique internal names
 numAnchors = 0;
 numEndBumpers = 0;
 numTrackSegments = 0;
 numLevelXings = 0;
 numLayoutSlips = 0;
 numLayoutTurnouts = 0;
 numLayoutTurntables = 0;
 // Lists of items that facilitate tools and drawings
// /*public*/ QVector<SignalHeadIcon> signalList = new QVector<SignalHeadIcon>();  // Signal Head Icons
// /*public*/ QVector<MemoryIcon> memoryLabelList = new QVector<MemoryIcon>(); // Memory Label List
// /*public*/ QVector<SensorIcon> sensorList = new QVector<SensorIcon>();  // Sensor Icons
// /*public*/ QVector<SignalMastIcon> signalMastList = new QVector<SignalMastIcon>();  // Signal Head Icons

 // persistent instance variables - saved to disk with Save Panel
 windowWidth = 0;
 windowHeight = 0;
 panelWidth = 0;
 panelHeight = 0;
 upperLeftX = 0;
 upperLeftY = 0;
 mainlineTrackWidth = 4.0F;
 sideTrackWidth = 2.0F;
 defaultTrackColor = Color.black;
 defaultOccupiedTrackColor = Color.black;
 defaultAlternativeTrackColor = Color.black;
 defaultBackgroundColor = Color.lightGray;
 defaultTextColor = Color.black;
 turnoutCircleColor = defaultTrackColor; //matches earlier versions
 turnoutCircleSize = 2;  //matches earlier versions
 layoutName = "";
 xScale = 1.0;
 yScale = 1.0;
 animatingLayout = true;
 showHelpBar = true;
 drawGrid = false;
 snapToGridOnAdd = false;
 snapToGridOnMove = false;
 antialiasingOn = false;
 turnoutCirclesWithoutEditMode = false;
 tooltipsWithoutEditMode = false;
 tooltipsInEditMode = true;
 // turnout size parameters - saved with panel
 turnoutBX = turnoutBXDefault;  // RH, LH, WYE
 turnoutCX = turnoutCXDefault;
 turnoutWid = turnoutWidDefault;
 xOverLong = xOverLongDefault;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
 xOverHWid = xOverHWidDefault;
 xOverShort = xOverShortDefault;

 // saved state of options when panel was loaded or created
 savedEditMode = true;
 savedPositionable = true;
 savedControlLayout = true;
 savedAnimatingLayout = true;
 savedShowHelpBar = false;
 // Antialiasing rendering
// /*private*/ static final RenderingHints antialiasing = new RenderingHints(
//         RenderingHints.KEY_ANTIALIASING,
//         RenderingHints.VALUE_ANTIALIAS_ON);


 layoutName = name;
    // initialize frame
// Container contentPane = getContentPane();
// contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
 centralWidget = new QWidget(this);
 setCentralWidget(centralWidget);
 centralWidget->setObjectName(QString::fromUtf8("centralwidget"));
 QHBoxLayout* horizontalLayout = new QHBoxLayout(centralWidget);
 horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
 // initialize menu bar
 /*JMenu*/ QMenuBar* menuBar = new QMenuBar();
 // set up File menu
 /*JMenu*/QMenu* fileMenu = new /*JMenu*/QMenu(tr("MenuFile"));
 menuBar->addMenu(fileMenu);
 QAction* actionMenuItemStore = new QAction(tr("MenuItemStore"),this);
 fileMenu->addAction(actionMenuItemStore);
 fileMenu->addSeparator();
 ///*JMenu*/QMenuItem* deleteItem = new /*JMenu*/QMenuItem(tr("DeletePanel"));
 QAction* actionDeletePanel = new QAction(tr("DeletePanel"));
 fileMenu->addAction(actionDeletePanel);
//    deleteItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (deletePanel()) {
//                    dispose(true);
//                }
//            }
//        });
 connect(actionDeletePanel, SIGNAL(triggered()), this, SLOT(on_actionDeletePanel()));

    setMenuBar(menuBar);
    // setup Options menu
    setupOptionMenu(menuBar);
    // setup Tools menu
    setupToolsMenu(menuBar);
    // setup Zoom menu
    setupZoomMenu(menuBar);
    // setup Zoom menu
    setupMarkerMenu(menuBar);
    // setup Help menu
    addHelpMenu("package.jmri.jmrit.display.LayoutEditor", true);

    // setup group for radio buttons selecting items to add and line style
    itemGroup = new QButtonGroup();
    itemGroup->add(turnoutRHBox);
    itemGroup->add(turnoutLHBox);
    itemGroup->add(turnoutWYEBox);
    itemGroup->add(doubleXoverBox);
    itemGroup->add(rhXoverBox);
    itemGroup->add(lhXoverBox);
    itemGroup->add(levelXingBox);
    itemGroup->add(layoutSingleSlipBox);
    itemGroup->add(layoutDoubleSlipBox);
    itemGroup->add(endBumperBox);
    itemGroup->add(anchorBox);
    itemGroup->add(trackBox);
    itemGroup->add(multiSensorBox);
    itemGroup->add(sensorBox);
    itemGroup->add(signalBox);
    itemGroup->add(signalMastBox);
    itemGroup->add(textLabelBox);
    itemGroup->add(memoryBox);
    itemGroup->add(iconLabelBox);
#if 0 //TODO:
    ActionListener selectionListAction = new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent a) {
            Component[] extra = extraTurnoutPanel.getComponents();
            if (layoutSingleSlipBox.isSelected() || layoutDoubleSlipBox.isSelected()){
                for (Component item: extra) {
                     item.setEnabled(true);
                }
            }
            else {
                for (Component item: extra) {
                     item.setEnabled(false);
                }
            }
        }
    };
    turnoutRHBox.addActionListener(selectionListAction);
    turnoutLHBox.addActionListener(selectionListAction);
    turnoutWYEBox.addActionListener(selectionListAction);
    doubleXoverBox.addActionListener(selectionListAction);
    rhXoverBox.addActionListener(selectionListAction);
    lhXoverBox.addActionListener(selectionListAction);
    levelXingBox.addActionListener(selectionListAction);
    layoutSingleSlipBox.addActionListener(selectionListAction);
    layoutDoubleSlipBox.addActionListener(selectionListAction);
    endBumperBox.addActionListener(selectionListAction);
    anchorBox.addActionListener(selectionListAction);
    trackBox.addActionListener(selectionListAction);
    multiSensorBox.addActionListener(selectionListAction);
    sensorBox.addActionListener(selectionListAction);
    signalBox.addActionListener(selectionListAction);
    signalMastBox.addActionListener(selectionListAction);
    textLabelBox.addActionListener(selectionListAction);
    memoryBox.addActionListener(selectionListAction);
    iconLabelBox.addActionListener(selectionListAction);
#endif

    turnoutRHBox->setSelected(true);
    dashedLine->setSelected(false);
    mainlineTrack->setSelected(false);
    // setup top edit bar
    topEditBar = new JPanel();
    topEditBar.setLayout(new BoxLayout(topEditBar, BoxLayout.Y_AXIS));
    // add first row of edit tool bar items
    JPanel top1 = new JPanel();
    Dimension coordSize = xLabel.getPreferredSize();
    coordSize.width *= 2;
    xLabel.setPreferredSize(coordSize);
    yLabel.setPreferredSize(coordSize);
    top1.add(new QLabel(rb.getQString("Location")+" - x:"));
    top1.add(xLabel);
    top1.add(new QLabel(" y:"));
    top1.add(yLabel);
    // add turnout items
    top1.add (new QLabel("    "+rb.getQString("Turnout")+": "));
    top1.add (new QLabel(rb.getQString("Name")));
    top1.add (nextTurnout);
    nextTurnout.setToolTipText(rb.getQString("TurnoutNameToolTip"));
    QLabel extraTurnLabel = new QLabel(rb.getQString("SecondName"));
    extraTurnLabel.setEnabled(false);
    extraTurnout.setEnabled(false);
    extraTurnoutPanel.add (extraTurnLabel);
    extraTurnoutPanel.add (extraTurnout);
    extraTurnout.setToolTipText(rb.getQString("TurnoutNameToolTip"));
    top1.add(extraTurnoutPanel);
    top1.add (new QLabel(rb.getQString("Type")));
    top1.add (turnoutRHBox);
    turnoutRHBox.setToolTipText(rb.getQString("RHToolTip"));
    top1.add (turnoutLHBox);
    turnoutLHBox.setToolTipText(rb.getQString("LHToolTip"));
    top1.add (turnoutWYEBox);
    turnoutWYEBox.setToolTipText(rb.getQString("WYEToolTip"));
    top1.add (doubleXoverBox);
    doubleXoverBox.setToolTipText(rb.getQString("DoubleCrossOverToolTip"));
    top1.add (rhXoverBox);
    rhXoverBox.setToolTipText(rb.getQString("RHCrossOverToolTip"));
    top1.add (lhXoverBox);
    lhXoverBox.setToolTipText(rb.getQString("LHCrossOverToolTip"));
    top1.add (layoutSingleSlipBox);
    layoutSingleSlipBox.setToolTipText(rb.getQString("SingleSlipToolTip"));
    top1.add (layoutDoubleSlipBox);
    layoutDoubleSlipBox.setToolTipText(rb.getQString("DoubleSlipToolTip"));
    rotationPanel.add (new QLabel("    "+rb.getQString("Rotation")));
    rotationPanel.add (rotationField);
    top1.add(rotationPanel);
    rotationField.setToolTipText(rb.getQString("RotationToolTip"));
    topEditBar.add(top1);
    // add second row of edit tool bar items
    JPanel top2 = new JPanel();
    top2.add(new QLabel(rb.getQString("BlockID")));
    top2.add(blockIDField);
    blockIDField.setToolTipText(rb.getQString("BlockIDToolTip"));
    top2.add(new QLabel(rb.getQString("OccupancySensor")));
    top2.add(blockSensor);
    blockSensor.setText("");
    blockSensor.setToolTipText(rb.getQString("OccupancySensorToolTip"));
    top2.add (new QLabel("  "+rb.getQString("Track")+":  "));
    top2.add (levelXingBox);
    levelXingBox.setToolTipText(rb.getQString("LevelCrossingToolTip"));
    top2.add (trackBox);
    trackBox.setToolTipText(rb.getQString("TrackSegmentToolTip"));
    top2.add (dashedLine);
    dashedLine.setToolTipText(rb.getQString("DashedCheckBoxTip"));
    top2.add (mainlineTrack);
    mainlineTrack.setToolTipText(rb.getQString("MainlineCheckBoxTip"));
    topEditBar.add(top2);
    // add third row of edit tool bar items
    JPanel top3 = new JPanel();
    top3.add(new QLabel("  "+rb.getQString("Nodes")+": "));
    top3.add (endBumperBox);
    endBumperBox.setToolTipText(rb.getQString("EndBumperToolTip"));
    top3.add (anchorBox);
    anchorBox.setToolTipText(rb.getQString("AnchorToolTip"));
    top3.add(new QLabel("   "+rb.getQString("Labels")+": "));
    top3.add (textLabelBox);
    textLabelBox.setToolTipText(rb.getQString("TextLabelToolTip"));
    top3.add (textLabel);
    textLabel.setToolTipText(rb.getQString("TextToolTip"));
    top3.add (memoryBox);
    memoryBox.setToolTipText(rb.getQString("MemoryBoxToolTip"));
    top3.add (textMemory);
    textMemory.setToolTipText(rb.getQString("MemoryToolTip"));
    topEditBar.add(top3);
    // add fourth row of edit tool bar items
    JPanel top4 = new JPanel();
    // multi sensor
    top4.add (multiSensorBox);
    multiSensorBox.setToolTipText(rb.getQString("MultiSensorToolTip"));
    // change icon
    top4.add (new QLabel("    "));
    JButton changeIcon = new JButton(rb.getQString("ChangeIcons")+"...");
    changeIcon.addActionListener( new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent a) {
                if (sensorBox.isSelected())
                    sensorFrame.setVisible(true);
                else if (signalBox.isSelected())
                    signalFrame.setVisible(true);
                else if (iconLabelBox.isSelected())
                    iconFrame.setVisible(true);
            }
        } );
    top4.add(changeIcon);
    changeIcon.setToolTipText(rb.getQString("ChangeIconToolTip"));
    // sensor icon
    top4.add (new QLabel("    "));
    top4.add (sensorBox);
    sensorBox.setToolTipText(rb.getQString("SensorBoxToolTip"));
    top4.add (nextSensor);
    nextSensor.setToolTipText(rb.getQString("SensorIconToolTip"));
    sensorIconEditor = new MultiIconEditor(4);
    sensorIconEditor.setIcon(0, "Active:","resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
    sensorIconEditor.setIcon(1, "Inactive", "resources/icons/smallschematics/tracksegments/circuit-empty.gif");
    sensorIconEditor.setIcon(2, "Inconsistent:", "resources/icons/smallschematics/tracksegments/circuit-error.gif");
    sensorIconEditor.setIcon(3, "Unknown:","resources/icons/smallschematics/tracksegments/circuit-error.gif");
    sensorIconEditor.complete();
    sensorFrame = new JFrame(rb.getQString("EditSensorIcons"));
    sensorFrame.getContentPane().add(new QLabel("  "+rb.getQString("IconChangeInfo")+"  "),BorderLayout.NORTH);
    sensorFrame.getContentPane().add(sensorIconEditor);
    sensorFrame.pack();
    // signal icon
    top4.add (new QLabel("    "));
    top4.add (signalBox);
    signalBox.setToolTipText(rb.getQString("SignalMastBoxToolTip"));
    top4.add (nextSignalHead);
    nextSignalHead.setToolTipText(rb.getQString("SignalIconToolTip"));
    signalIconEditor = new MultiIconEditor(10);
    signalIconEditor.setIcon(0, "Red:","resources/icons/smallschematics/searchlights/left-red-short.gif");
    signalIconEditor.setIcon(1, "Flash red:", "resources/icons/smallschematics/searchlights/left-flashred-short.gif");
    signalIconEditor.setIcon(2, "Yellow:", "resources/icons/smallschematics/searchlights/left-yellow-short.gif");
    signalIconEditor.setIcon(3, "Flash yellow:", "resources/icons/smallschematics/searchlights/left-flashyellow-short.gif");
    signalIconEditor.setIcon(4, "Green:","resources/icons/smallschematics/searchlights/left-green-short.gif");
    signalIconEditor.setIcon(5, "Flash green:","resources/icons/smallschematics/searchlights/left-flashgreen-short.gif");
    signalIconEditor.setIcon(6, "Dark:","resources/icons/smallschematics/searchlights/left-dark-short.gif");
    signalIconEditor.setIcon(7, "Held:","resources/icons/smallschematics/searchlights/left-held-short.gif");
    signalIconEditor.setIcon(8, "Lunar","resources/icons/smallschematics/searchlights/left-lunar-short-marker.gif");
    signalIconEditor.setIcon(9, "Flash Lunar","resources/icons/smallschematics/searchlights/left-flashlunar-short-marker.gif");
    signalIconEditor.complete();
    signalFrame = new JFrame(rb.getQString("EditSignalIcons"));
    signalFrame.getContentPane().add(new QLabel("  "+rb.getQString("IconChangeInfo")+"  "),BorderLayout.NORTH);
    signalFrame.getContentPane().add(signalIconEditor);
    signalFrame.pack();
    signalFrame.setVisible(false);

    top4.add (new QLabel("    "));
    top4.add (signalMastBox);
    top4.add (nextSignalMast);
    // icon label
    top4.add (new QLabel("    "));
    top4.add (iconLabelBox);
    iconLabelBox.setToolTipText(rb.getQString("IconLabelToolTip"));
    iconEditor = new MultiIconEditor(1);
    iconEditor.setIcon(0, "","resources/icons/smallschematics/tracksegments/block.gif");
    iconEditor.complete();
    iconFrame = new JFrame(rb.getQString("EditIcon"));
    iconFrame.getContentPane().add(iconEditor);
    iconFrame.pack();

    topEditBar.add(top4);
    contentPane.add(topEditBar);
    topEditBar.setVisible(false);

    // set to full screen
    Dimension screenDim = Toolkit.getDefaultToolkit().getScreenSize();
    height = screenDim.height-120;
    width = screenDim.width-20;
    // Let Editor make target, and use this frame
    super.setTargetPanel(NULL, NULL);
    super.setTargetPanelSize(width, height);
    setSize(screenDim.width, screenDim.height);
    topEditBar.setSize(screenDim.width, topEditBar.getPreferredSize().height);
    super.setDefaultToolTip(new ToolTip(NULL,0,0,new Font("SansSerif", Font.PLAIN, 12),
                                                 Color.black, new Color(215, 225, 255), Color.black));
    // setup help bar
    helpBar = new JPanel();
    helpBar.setLayout(new BoxLayout(helpBar, BoxLayout.Y_AXIS));
    JPanel help1 = new JPanel();
    help1.add(new QLabel(rb.getQString("Help1")));
    helpBar.add(help1);
    JPanel help2 = new JPanel();
    help2.add(new QLabel(rb.getQString("Help2")));
    helpBar.add(help2);
    JPanel help3 = new JPanel();
            switch (SystemType.getType()) {
                case SystemType.MACOSX:
                    help3.add(new QLabel(rb.getQString("Help3Mac")));
                    break;
                case SystemType.WINDOWS:
                    help3.add(new QLabel(rb.getQString("Help3Win")));
                    break;
                case SystemType.LINUX:
                    help3.add(new QLabel(rb.getQString("Help3Win")));
                    break;
                default:
                    help3.add(new QLabel(rb.getQString("Help3")));
            }
    helpBar.add(help3);

    contentPane.add(helpBar);
    helpBar.setVisible(false);

    // register the resulting panel for later configuration
    InstanceManager::configureManagerInstance().registerUser(this);
    // confirm that panel hasn't already been loaded
    if(jmri.jmrit.display.PanelMenu.instance().isPanelNameUsed(name)){
        log.warn("File contains a panel with the same name (" + name + ") as an existing panel");
    }
    jmri.jmrit.display.PanelMenu.instance().addEditorPanel(this);
    thisPanel = this;
    thisPanel.setFocusable(true);
    thisPanel.addKeyListener(this);
    resetDirty();
    // establish link to LayoutEditorAuxTools
    auxTools = new LayoutEditorAuxTools(thisPanel);
    if (auxTools==NULL) log.error("Unable to create link to LayoutEditorAuxTools");
}

    /*protected*/ void LayoutEditor::init(QString name) {}

    /*public*/ void LayoutEditor::initView() {
        editModeItem.setSelected(isEditable());
        positionableItem.setSelected(allPositionable());
        controlItem.setSelected(allControlling());
        if (isEditable()) setAllShowTooltip(tooltipsInEditMode);
        else setAllShowTooltip(tooltipsWithoutEditMode);
        switch (_scrollState) {
            case SCROLL_NONE:
                scrollNone.setSelected(true);
                break;
            case SCROLL_BOTH:
                scrollBoth.setSelected(true);
                break;
            case SCROLL_HORIZONTAL:
                scrollHorizontal.setSelected(true);
                break;
            case SCROLL_VERTICAL:
                scrollVertical.setSelected(true);
                break;
            default: break;
        }
    }

    /*public*/ void LayoutEditor::setSize(int w, int h) {
        log.debug("Frame size now w="+width+", h="+height);
        super.setSize(w,h);
    }

    /*protected*/ void LayoutEditor::targetWindowClosingEvent(WindowEvent* e) {
        bool save = (isDirty() || (savedEditMode!=isEditable()) ||
                (savedPositionable!=allPositionable()) ||
                (savedControlLayout!=allControlling()) ||
                (savedAnimatingLayout!=animatingLayout) ||
                (savedShowHelpBar!=showHelpBar) );
        targetWindowClosing(save);
    }

    void LayoutEditor::setupToolsMenu(QMenuBar menuBar) {
        /*JMenu*/QMenu toolsMenu = new /*JMenu*/QMenu(rb.getQString("MenuTools"));
        menuBar.add(toolsMenu);
        // scale track diagram
        /*JMenu*/QMenuItem scaleItem = new /*JMenu*/QMenuItem(rb.getQString("ScaleTrackDiagram")+"...");
        toolsMenu.add(scaleItem);
        scaleItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // bring up scale track diagram dialog
                    scaleTrackDiagram();
                }
            });
        // translate selection
        /*JMenu*/QMenuItem moveItem = new /*JMenu*/QMenuItem(rb.getQString("TranslateSelection")+"...");
        toolsMenu.add(moveItem);
        moveItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // bring up translate selection dialog
                    moveSelection();
                }
            });
        // undo translate selection
        /*JMenu*/QMenuItem undoMoveItem = new /*JMenu*/QMenuItem(rb.getQString("UndoTranslateSelection"));
        toolsMenu.add(undoMoveItem);
        undoMoveItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // undo previous move selection
                    undoMoveSelection();
                }
            });
        // reset turnout size to program defaults
        /*JMenu*/QMenuItem undoTurnoutSize = new /*JMenu*/QMenuItem(rb.getQString("ResetTurnoutSize"));
        toolsMenu.add(undoTurnoutSize);
        undoTurnoutSize.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // undo previous move selection
                    resetTurnoutSize();
                }
            });
        toolsMenu.addSeparator();
        // skip turnout
        skipTurnoutItem = new JCheckBoxMenuItem(rb.getQString("SkipInternalTurnout"));
        toolsMenu.add(skipTurnoutItem);
        skipTurnoutItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    skipIncludedTurnout = skipTurnoutItem.isSelected();
                }
            });
        skipTurnoutItem.setSelected(skipIncludedTurnout);
        // set signals at turnout
        /*JMenu*/QMenuItem turnoutItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtTurnout")+"...");
        toolsMenu.add(turnoutItem);
        turnoutItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at turnout tool dialog
                    tools.setSignalsAtTurnout(signalIconEditor,signalFrame);
                }
            });
        // set signals at block boundary
        /*JMenu*/QMenuItem boundaryItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtBoundary")+"...");
        toolsMenu.add(boundaryItem);
        boundaryItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at block boundary tool dialog
                    tools.setSignalsAtBlockBoundary(signalIconEditor,signalFrame);
                }
            });
        // set signals at crossover turnout
        /*JMenu*/QMenuItem xoverItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtXoverTurnout")+"...");
        toolsMenu.add(xoverItem);
        xoverItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at double crossover tool dialog
                    tools.setSignalsAtXoverTurnout(signalIconEditor,signalFrame);
                }
            });
        // set signals at level crossing
        /*JMenu*/QMenuItem xingItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtLevelXing")+"...");
        toolsMenu.add(xingItem);
        xingItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at level crossing tool dialog
                    tools.setSignalsAtLevelXing(signalIconEditor,signalFrame);
                }
            });
        // set signals at throat-to-throat turnouts
        /*JMenu*/QMenuItem tToTItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtTToTTurnout")+"...");
        toolsMenu.add(tToTItem);
        tToTItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at throat-to-throat turnouts tool dialog
                    tools.setSignalsAtTToTTurnouts(signalIconEditor,signalFrame);
                }
            });
        // set signals at 3-way turnout
        /*JMenu*/QMenuItem way3Item = new /*JMenu*/QMenuItem(rb.getQString("SignalsAt3WayTurnout")+"...");
        toolsMenu.add(way3Item);
        way3Item.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at 3-way turnout tool dialog
                    tools.setSignalsAt3WayTurnout(signalIconEditor,signalFrame);
                }
            });
        /*JMenu*/QMenuItem slipItem = new /*JMenu*/QMenuItem(rb.getQString("SignalsAtSlip")+"...");
        toolsMenu.add(slipItem);
        slipItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(thisPanel);
                    }
                    // bring up signals at throat-to-throat turnouts tool dialog
                    tools.setSignalsAtSlip(signalIconEditor,signalFrame);
                }
            });

        /*JMenu*/QMenuItem entryExitItem = new /*JMenu*/QMenuItem("Entry Exit"+"...");
        toolsMenu.add(entryExitItem);
        entryExitItem.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent event){
                if(entryExit == NULL)
                    entryExit = new jmri.jmrit.signalling.AddEntryExitPairAction("ENTRY EXIT", thisPanel);
                entryExit.actionPerformed(event);
            }
        });

    }

    /*protected*/ /*JMenu*/QMenu LayoutEditor::setupOptionMenu(QMenuBar* menuBar) {
        /*JMenu*/QMenu optionMenu = new /*JMenu*/QMenu(rbx.getQString("Options"));
        menuBar.add(optionMenu);
        // edit mode item
        editModeItem = new JCheckBoxMenuItem(rb.getQString("EditMode"));
        optionMenu.add(editModeItem);
        editModeItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setAllEditable(editModeItem.isSelected());
                    if (isEditable()) {
                        helpBar.setVisible(showHelpBar);
                        setAllShowTooltip(tooltipsInEditMode);
                    }
                    else {
                        setAllShowTooltip(tooltipsWithoutEditMode);
                    }
                    awaitingIconChange = false;
                }
            });
        editModeItem.setSelected(isEditable());
        // positionable item
        positionableItem = new JCheckBoxMenuItem(rb.getQString("AllowRepositioning"));
        optionMenu.add(positionableItem);
        positionableItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setAllPositionable(positionableItem.isSelected());
                }
            });
        positionableItem.setSelected(allPositionable());
        // controlable item
        controlItem = new JCheckBoxMenuItem(rb.getQString("AllowLayoutControl"));
        optionMenu.add(controlItem);
        controlItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setAllControlling(controlItem.isSelected());
                }
            });
        controlItem.setSelected(allControlling());

        // animation item
        animationItem = new JCheckBoxMenuItem(rb.getQString("AllowTurnoutAnimation"));
        optionMenu.add(animationItem);
        animationItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    bool mode = animationItem.isSelected();
                    setTurnoutAnimation(mode);
                }
            });
        animationItem.setSelected(true);
        // show help item
        showHelpItem = new JCheckBoxMenuItem(rb.getQString("ShowEditHelp"));
        optionMenu.add(showHelpItem);
        showHelpItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    showHelpBar = showHelpItem.isSelected();
                    if (isEditable()) {
                        helpBar.setVisible(showHelpBar);
                    }
                }
            });
        showHelpItem.setSelected(showHelpBar);
        // show grid item
        showGridItem = new JCheckBoxMenuItem(rb.getQString("ShowEditGrid"));
        optionMenu.add(showGridItem);
        showGridItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    drawGrid = showGridItem.isSelected();
                    repaint();
                }
            });
        showGridItem.setSelected(drawGrid);
        // snap to grid on add item
        snapToGridOnAddItem = new JCheckBoxMenuItem(rb.getQString("SnapToGridOnAdd"));
        optionMenu.add(snapToGridOnAddItem);
        snapToGridOnAddItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    snapToGridOnAdd = snapToGridOnAddItem.isSelected();
                    repaint();
                }
            });
        snapToGridOnAddItem.setSelected(snapToGridOnAdd);
        // snap to grid on move item
        snapToGridOnMoveItem = new JCheckBoxMenuItem(rb.getQString("SnapToGridOnMove"));
        optionMenu.add(snapToGridOnMoveItem);
        snapToGridOnMoveItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    snapToGridOnMove = snapToGridOnMoveItem.isSelected();
                    repaint();
                }
            });
        snapToGridOnMoveItem.setSelected(snapToGridOnMove);

        // Show/Hide Scroll Bars
        scrollMenu = new /*JMenu*/QMenu(rb.getQString("ScrollBarsSubMenu"));
        optionMenu.add(scrollMenu);
        ButtonGroup scrollGroup = new ButtonGroup();
        scrollBoth = new JRadioButtonMenuItem(rbx.getQString("ScrollBoth"));
        scrollGroup.add(scrollBoth);
        scrollMenu.add(scrollBoth);
        scrollBoth.setSelected(_scrollState==SCROLL_BOTH);
        scrollBoth.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    _scrollState = SCROLL_BOTH;
                    setScroll(_scrollState);
                    repaint();
                }
            });
        scrollNone = new JRadioButtonMenuItem(rbx.getQString("ScrollNone"));
        scrollGroup.add(scrollNone);
        scrollMenu.add(scrollNone);
        scrollNone.setSelected(_scrollState==SCROLL_NONE);
        scrollNone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    _scrollState = SCROLL_NONE;
                    setScroll(_scrollState);
                    repaint();
                }
            });
        scrollHorizontal = new JRadioButtonMenuItem(rbx.getQString("ScrollHorizontal"));
        scrollGroup.add(scrollHorizontal);
        scrollMenu.add(scrollHorizontal);
        scrollHorizontal.setSelected(_scrollState==SCROLL_HORIZONTAL);
        scrollHorizontal.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    _scrollState = SCROLL_HORIZONTAL;
                    setScroll(_scrollState);
                    repaint();
                }
            });
        scrollVertical = new JRadioButtonMenuItem(rbx.getQString("ScrollVertical"));
        scrollGroup.add(scrollVertical);
        scrollMenu.add(scrollVertical);
        scrollVertical.setSelected(_scrollState==SCROLL_VERTICAL);
        scrollVertical.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    _scrollState = SCROLL_VERTICAL;
                    setScroll(_scrollState);
                    repaint();
                }
            });

        // Tooltip options
        tooltipMenu = new /*JMenu*/QMenu(rb.getQString("TooltipSubMenu"));
        optionMenu.add(tooltipMenu);
        ButtonGroup tooltipGroup = new ButtonGroup();
        tooltipNone = new JRadioButtonMenuItem(rb.getQString("TooltipNone"));
        tooltipGroup.add(tooltipNone);
        tooltipMenu.add(tooltipNone);
        tooltipNone.setSelected((!tooltipsInEditMode) && (!tooltipsWithoutEditMode));
        tooltipNone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    tooltipsInEditMode = false;
                    tooltipsWithoutEditMode = false;
                    setAllShowTooltip(false);
                }
            });
        tooltipAlways = new JRadioButtonMenuItem(rb.getQString("TooltipAlways"));
        tooltipGroup.add(tooltipAlways);
        tooltipMenu.add(tooltipAlways);
        tooltipAlways.setSelected((tooltipsInEditMode) && (tooltipsWithoutEditMode));
        tooltipAlways.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    tooltipsInEditMode = true;
                    tooltipsWithoutEditMode = true;
                    setAllShowTooltip(true);
                }
            });
        tooltipInEdit = new JRadioButtonMenuItem(rb.getQString("TooltipEdit"));
        tooltipGroup.add(tooltipInEdit);
        tooltipMenu.add(tooltipInEdit);
        tooltipInEdit.setSelected((tooltipsInEditMode) && (!tooltipsWithoutEditMode));
        tooltipInEdit.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    tooltipsInEditMode = true;
                    tooltipsWithoutEditMode = false;
                    setAllShowTooltip(isEditable());
                }
            });
        tooltipNotInEdit = new JRadioButtonMenuItem(rb.getQString("TooltipNotEdit"));
        tooltipGroup.add(tooltipNotInEdit);
        tooltipMenu.add(tooltipNotInEdit);
        tooltipNotInEdit.setSelected((!tooltipsInEditMode) && (tooltipsWithoutEditMode));
        tooltipNotInEdit.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    tooltipsInEditMode = false;
                    tooltipsWithoutEditMode = true;
                    setAllShowTooltip(!isEditable());
                }
            });
        // antialiasing
        antialiasingOnItem = new JCheckBoxMenuItem(rb.getQString("AntialiasingOn"));
        optionMenu.add(antialiasingOnItem);
        antialiasingOnItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    antialiasingOn = antialiasingOnItem.isSelected();
                    repaint();
                }
            });
        antialiasingOnItem.setSelected(antialiasingOn);
        // title item
        optionMenu.addSeparator();
        /*JMenu*/QMenuItem titleItem = new /*JMenu*/QMenuItem(rb.getQString("EditTitle")+"...");
        optionMenu.add(titleItem);
        titleItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // prompt for name
                    QString newName = (QString)JOptionPane.showInputDialog(getTargetFrame(),
                                        rb.getQString("EnterTitle")+":", rb.getQString("EditTitleMessageTitle"),
                                            JOptionPane.PLAIN_MESSAGE, NULL, NULL,layoutName);
                    if (newName==NULL) return;  // cancelled
                    if(newName==(layoutName)){
                        return;
                    }
                    if (jmri.jmrit.display.PanelMenu.instance().isPanelNameUsed(newName)){
                        JOptionPane.showMessageDialog(NULL, rb.getQString("CanNotRename"), rb.getQString("PanelExist"),
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                    setTitle(newName);
                    layoutName = newName;
                    jmri.jmrit.display.PanelMenu.instance().renameEditorPanel(thisPanel);
                    setDirty(true);
                }
            });
        // add background image
        /*JMenu*/QMenuItem backgroundItem = new /*JMenu*/QMenuItem(rb.getQString("AddBackground")+"...");
        optionMenu.add(backgroundItem);
        backgroundItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    addBackground();
                    setDirty(true);
                    repaint();
                }
            });

        /*JMenu*/QMenu backgroundColorMenu = new /*JMenu*/QMenu(rb.getQString("SetBackgroundColor"));
        backgroundColorButtonGroup = new ButtonGroup();
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Black"), Color.black);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Gray"),Color.gray);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("White"),Color.white);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Red"),Color.red);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Pink"),Color.pink);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Orange"),Color.orange);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Yellow"),Color.yellow);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Green"),Color.green);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Blue"),Color.blue);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Magenta"),Color.magenta);
        addBackgroundColorMenuEntry(backgroundColorMenu, rb.getQString("Cyan"),Color.cyan);
        optionMenu.add(backgroundColorMenu);
        // add fast clock
        /*JMenu*/QMenuItem clockItem = new /*JMenu*/QMenuItem(rb.getQString("AddFastClock"));
        optionMenu.add(clockItem);
        clockItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    addClock();
                    setDirty(true);
                    repaint();
                }
            });
        // add turntable
        /*JMenu*/QMenuItem turntableItem = new /*JMenu*/QMenuItem(rb.getQString("AddTurntable"));
        optionMenu.add(turntableItem);
        turntableItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    addTurntable(windowCenter());
                    setDirty(true);
                    repaint();
                }
            });
        // add reporter
        /*JMenu*/QMenuItem reporterItem = new /*JMenu*/QMenuItem(rb.getQString("AddReporter")+"...");
        optionMenu.add(reporterItem);
        reporterItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    QPointF pt = windowCenter();
                    enterReporter((int)pt.getX() , (int)pt.getY());
                    setDirty(true);
                    repaint();
                }
            });
        // set location and size
        /*JMenu*/QMenuItem locationItem = new /*JMenu*/QMenuItem(rb.getQString("SetLocation"));
        optionMenu.add(locationItem);
        locationItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setCurrentPositionAndSize();
                    log.debug("Bounds:"+upperLeftX+", "+upperLeftY+", "+windowWidth+", "+windowHeight+", "+panelWidth+", "+panelHeight);
                }
            });
        // set track width
        /*JMenu*/QMenuItem widthItem = new /*JMenu*/QMenuItem(rb.getQString("SetTrackWidth")+"...");
        optionMenu.add(widthItem);
        widthItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    // bring up enter track width dialog
                    enterTrackWidth();
                }
            });
        // track color item
        /*JMenu*/QMenu trkColourMenu = new /*JMenu*/QMenu(rb.getQString("DefaultTrackColor"));
        optionMenu.add(trkColourMenu);
        /*JMenu*/QMenu trackColorMenu = new /*JMenu*/QMenu(rb.getQString("DefaultTrackColor"));
        trackColorButtonGroup = new ButtonGroup();
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Black"), Color.black);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Gray"),Color.gray);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("White"),Color.white);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Red"),Color.red);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Pink"),Color.pink);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Orange"),Color.orange);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Yellow"),Color.yellow);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Green"),Color.green);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Blue"),Color.blue);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Magenta"),Color.magenta);
        addTrackColorMenuEntry(trackColorMenu, rb.getQString("Cyan"),Color.cyan);
        trkColourMenu .add(trackColorMenu);

        /*JMenu*/QMenu trackOccupiedColorMenu = new /*JMenu*/QMenu(rb.getQString("DefaultOccupiedTrackColor"));
        trackOccupiedColorButtonGroup = new ButtonGroup();
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Black"), Color.black);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Gray"),Color.gray);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("White"),Color.white);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Red"),Color.red);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Pink"),Color.pink);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Orange"),Color.orange);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Yellow"),Color.yellow);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Green"),Color.green);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Blue"),Color.blue);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Magenta"),Color.magenta);
        addTrackOccupiedColorMenuEntry(trackOccupiedColorMenu, rb.getQString("Cyan"),Color.cyan);
        trkColourMenu .add(trackOccupiedColorMenu);

        /*JMenu*/QMenu trackAlternativeColorMenu = new /*JMenu*/QMenu(rb.getQString("DefaultAlternativeTrackColor"));
        trackAlternativeColorButtonGroup = new ButtonGroup();
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Black"), Color.black);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Gray"),Color.gray);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("White"),Color.white);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Red"),Color.red);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Pink"),Color.pink);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Orange"),Color.orange);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Yellow"),Color.yellow);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Green"),Color.green);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Blue"),Color.blue);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Magenta"),Color.magenta);
        addTrackAlternativeColorMenuEntry(trackAlternativeColorMenu, rb.getQString("Cyan"),Color.cyan);
        trkColourMenu .add(trackAlternativeColorMenu);

        /*JMenu*/QMenu textColorMenu = new /*JMenu*/QMenu(rb.getQString("DefaultTextColor"));
        textColorButtonGroup = new ButtonGroup();
        addTextColorMenuEntry(textColorMenu, rb.getQString("Black"), Color.black);
        addTextColorMenuEntry(textColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Gray"),Color.gray);
        addTextColorMenuEntry(textColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addTextColorMenuEntry(textColorMenu, rb.getQString("White"),Color.white);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Red"),Color.red);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Pink"),Color.pink);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Orange"),Color.orange);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Yellow"),Color.yellow);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Green"),Color.green);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Blue"),Color.blue);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Magenta"),Color.magenta);
        addTextColorMenuEntry(textColorMenu, rb.getQString("Cyan"),Color.cyan);
        optionMenu.add(textColorMenu);

        //turnout options submenu
        /*JMenu*/QMenu turnoutOptionsMenu = new /*JMenu*/QMenu(rb.getQString("TurnoutOptions"));
        optionMenu.add(turnoutOptionsMenu);

        // circle on Turnouts
        turnoutCirclesOnItem = new JCheckBoxMenuItem(rb.getQString("TurnoutCirclesOn"));
        turnoutOptionsMenu.add(turnoutCirclesOnItem);
        turnoutCirclesOnItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    turnoutCirclesWithoutEditMode = turnoutCirclesOnItem.isSelected();
                    repaint();
                }
            });
        turnoutCirclesOnItem.setSelected(turnoutCirclesWithoutEditMode);

        // select turnout circle color
        /*JMenu*/QMenu turnoutCircleColorMenu = new /*JMenu*/QMenu(rb.getQString("TurnoutCircleColor"));
        turnoutCircleColorButtonGroup = new ButtonGroup();
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("UseDefaultTrackColor"), NULL);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Black"), Color.black);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("DarkGray"),Color.darkGray);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Gray"),Color.gray);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("LightGray"),Color.lightGray);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("White"),Color.white);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Red"),Color.red);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Pink"),Color.pink);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Orange"),Color.orange);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Yellow"),Color.yellow);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Green"),Color.green);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Blue"),Color.blue);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Magenta"),Color.magenta);
        addTurnoutCircleColorMenuEntry(turnoutCircleColorMenu, rb.getQString("Cyan"),Color.cyan);
        turnoutOptionsMenu.add(turnoutCircleColorMenu);

        // select turnout circle size
        /*JMenu*/QMenu turnoutCircleSizeMenu = new /*JMenu*/QMenu(rb.getQString("TurnoutCircleSize"));
        turnoutCircleSizeButtonGroup = new ButtonGroup();
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "1", 1);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "2", 2);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "3", 3);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "4", 4);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "5", 5);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "6", 6);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "7", 7);
        addTurnoutCircleSizeMenuEntry(turnoutCircleSizeMenu, "8", 8);
        turnoutOptionsMenu.add(turnoutCircleSizeMenu);

        // enable drawing of unselected leg (helps when diverging angle is small)
        turnoutDrawUnselectedLegItem = new JCheckBoxMenuItem(rb.getQString("TurnoutDrawUnselectedLeg"));
        turnoutOptionsMenu.add(turnoutDrawUnselectedLegItem);
        turnoutDrawUnselectedLegItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    turnoutDrawUnselectedLeg = turnoutDrawUnselectedLegItem.isSelected();
                    repaint();
                }
            });
        turnoutDrawUnselectedLegItem.setSelected(turnoutDrawUnselectedLeg);

                // show grid item
        autoAssignBlocksItem = new JCheckBoxMenuItem(rb.getQString("AutoAssignBlock"));
        optionMenu.add(autoAssignBlocksItem);
        autoAssignBlocksItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    autoAssignBlocks = autoAssignBlocksItem.isSelected();
                }
            });
        autoAssignBlocksItem.setSelected(autoAssignBlocks);

        return optionMenu;
    }

    /*private*/ void LayoutEditor::setupZoomMenu(QMenuBar* menuBar) {
        /*JMenu*/QMenu zoomMenu = new /*JMenu*/QMenu(rb.getQString("MenuZoom"));
        menuBar.add(zoomMenu);
        ButtonGroup zoomButtonGroup = new ButtonGroup();
        // edit mode item
        JRadioButtonMenuItem noZoomItem = new JRadioButtonMenuItem(rb.getQString("NoZoom"));
        zoomMenu.add(noZoomItem);
        noZoomItem.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setZoom(1.0);
                }
            });
        zoomButtonGroup.add(noZoomItem);
        JRadioButtonMenuItem zoom15Item = new JRadioButtonMenuItem("x 1.5");
        zoomMenu.add(zoom15Item);
        zoom15Item.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setZoom(1.5);
                }
            });
        zoomButtonGroup.add(zoom15Item);
        JRadioButtonMenuItem zoom20Item = new JRadioButtonMenuItem("x 2.0");
        zoomMenu.add(zoom20Item);
        zoom20Item.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setZoom(2.0);
                }
            });
        zoomButtonGroup.add(zoom20Item);
        JRadioButtonMenuItem zoom30Item = new JRadioButtonMenuItem("x 3.0");
        zoomMenu.add(zoom30Item);
        zoom30Item.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setZoom(3.0);
                }
            });
        zoomButtonGroup.add(zoom30Item);
        JRadioButtonMenuItem zoom40Item = new JRadioButtonMenuItem("x 4.0");
        zoomMenu.add(zoom40Item);
        zoom40Item.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent event) {
                    setZoom(4.0);
                }
            });
        zoomButtonGroup.add(zoom40Item);
        noZoomItem.setSelected(true);
    }

    /*private*/ void LayoutEditor::setZoom(double factor) {
        setPaintScale(factor);
    }

    /*private*/ QPointF* LayoutEditor::windowCenter() {
        // Returns window's center coordinates converted to layout space
        // Used for initial setup of turntables and reporters
        // First of all compute center of window in screen coordinates
        Point pt = getLocationOnScreen();
        Dimension dim = getSize();
        pt.x += dim.width/2;
        pt.y += dim.height/2 + 40; // 40 = approx. difference between upper and lower menu areas
        // Now convert to layout space
        SwingUtilities.convertPointFromScreen(pt, getTargetPanel());
        pt.x /= getPaintScale();
        pt.y /= getPaintScale();
        return pt;
    }
    /*private*/ void LayoutEditor::setupMarkerMenu(QMenuBar* menuBar) {
        /*JMenu*/QMenu markerMenu = new /*JMenu*/QMenu(rbx.getQString("MenuMarker"));
        menuBar.add(markerMenu);
        markerMenu.add(new AbstractAction(rbx.getQString("AddLoco")+"..."){
            /*public*/ void actionPerformed(ActionEvent e) {
                locoMarkerFromInput();
            }
        });
        markerMenu.add(new AbstractAction(rbx.getQString("AddLocoRoster")+"..."){
            /*public*/ void actionPerformed(ActionEvent e) {
                locoMarkerFromRoster();
            }
        });
        markerMenu.add(new AbstractAction(rbx.getQString("RemoveMarkers")){
            /*public*/ void actionPerformed(ActionEvent e) {
                removeMarkers();
            }
        });
    }
    /**
     * Remove marker icons from panel
     */
    /*protected*/ void LayoutEditor::removeMarkers() {
        for (int i = markerImage.size(); i >0 ; i--) {
            LocoIcon il = markerImage.get(i-1);
            if ( (il != NULL) && (il.isActive()) ) {
                markerImage.remove(i-1);
                il.remove();
                il.dispose();
                setDirty(true);
            }
        }
        super.removeMarkers();
        repaint();
    }


    // display dialog for entering track widths
    /*protected*/ void LayoutEditor::enterTrackWidth() {
        if (enterWidthOpen) {
            enterTrackWidthFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (enterTrackWidthFrame == NULL) {
            enterTrackWidthFrame = new JmriJFrame( rb.getQString("SetTrackWidth") );
            enterTrackWidthFrame.addHelpMenu("package.jmri.jmrit.display.EnterTrackWidth", true);
            enterTrackWidthFrame.setLocation(70,30);
            Container theContentPane = enterTrackWidthFrame.getContentPane();
            theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.Y_AXIS));
            // setup side track width
            JPanel panel2 = new JPanel();
            panel2.setLayout(new FlowLayout());
            QLabel sideWidthLabel = new QLabel( rb.getQString("SideTrackWidth"));
            panel2.add(sideWidthLabel);
            panel2.add(sideWidthField);
            sideWidthField.setToolTipText( rb.getQString("SideTrackWidthHint") );
            theContentPane.add(panel2);
            // setup mainline track width
            JPanel panel3 = new JPanel();
            panel3.setLayout(new FlowLayout());
            QLabel mainlineWidthLabel = new QLabel( rb.getQString("MainlineTrackWidth"));
            panel3.add(mainlineWidthLabel);
            panel3.add(mainlineWidthField);
            mainlineWidthField.setToolTipText( rb.getQString("MainlineTrackWidthHint") );
            theContentPane.add(panel3);
            // set up Done and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            panel5.add(trackWidthDone = new JButton(rb.getQString("Done")));
            trackWidthDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    trackWidthDonePressed(e);
                }
            });
            trackWidthDone.setToolTipText( rb.getQString("DoneHint") );
            // Cancel
            panel5.add(trackWidthCancel = new JButton(rb.getQString("Cancel")));
            trackWidthCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    trackWidthCancelPressed(e);
                }
            });
            trackWidthCancel.setToolTipText( rb.getQString("CancelHint") );
            theContentPane.add(panel5);
        }
        // Set up for Entry of Track Widths
        mainlineWidthField.setText(""+getMainlineTrackWidth());
        sideWidthField.setText(""+getSideTrackWidth());
        enterTrackWidthFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    trackWidthCancelPressed(NULL);
                }
            });
        enterTrackWidthFrame.pack();
        enterTrackWidthFrame.setVisible(true);
        trackWidthChange = false;
        enterWidthOpen = true;
    }
    void LayoutEditor::trackWidthDonePressed(ActionEvent a) {
        QString newWidth = "";
        float wid = 0.0F;
        // get side track width
        newWidth = sideWidthField.getText().trim();
        try {
            wid = Float.parseFloat(newWidth);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(enterTrackWidthFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if ( (wid<=0.99) || (wid>10.0) ) {
            JOptionPane.showMessageDialog(enterTrackWidthFrame,
                    java.text.MessageFormat.format(rb.getQString("Error2"),
                    new Object[]{" "+wid+" "}),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (sideTrackWidth!=wid) {
            sideTrackWidth = wid;
            trackWidthChange = true;
        }
        // get mainline track width
        newWidth = mainlineWidthField.getText().trim();
        try {
            wid = Float.parseFloat(newWidth);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(enterTrackWidthFrame,rb.getQString("EntryError")+": "+
                    e+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if ( (wid<=0.99) || (wid>10.0) ) {
            JOptionPane.showMessageDialog(enterTrackWidthFrame,
                    java.text.MessageFormat.format(rb.getQString("Error2"),
                    new Object[]{" "+wid+" "}),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (mainlineTrackWidth!=wid) {
            mainlineTrackWidth = wid;
            trackWidthChange = true;
        }
        // success - hide dialog and repaint if needed
        enterWidthOpen = false;
        enterTrackWidthFrame.setVisible(false);
        enterTrackWidthFrame.dispose();
        enterTrackWidthFrame = NULL;
        if (trackWidthChange) {
            repaint();
            setDirty(true);
        }
    }
    void LayoutEditor::trackWidthCancelPressed(ActionEvent a) {
        enterWidthOpen = false;
        enterTrackWidthFrame.setVisible(false);
        enterTrackWidthFrame.dispose();
        enterTrackWidthFrame = NULL;
        if (trackWidthChange) {
            repaint();
            setDirty(true);
        }
    }


    // display dialog for entering Reporters
    /*protected*/ void LayoutEditor::enterReporter(int defaultX, int defaultY) {
        if (reporterOpen) {
            enterReporterFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (enterReporterFrame == NULL) {
            enterReporterFrame = new JmriJFrame( rb.getQString("AddReporter") );
//            enterReporterFrame.addHelpMenu("package.jmri.jmrit.display.AddReporterLabel", true);
            enterReporterFrame.setLocation(70,30);
            Container theContentPane = enterReporterFrame.getContentPane();
            theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.Y_AXIS));
            // setup reporter entry
            JPanel panel2 = new JPanel();
            panel2.setLayout(new FlowLayout());
            QLabel reporterLabel = new QLabel( rb.getQString("ReporterName")+":");
            panel2.add(reporterLabel);
            panel2.add(reporterNameField);
            reporterNameField.setToolTipText( rb.getQString("ReporterNameHint") );
            theContentPane.add(panel2);
            // setup coordinates entry
            JPanel panel3 = new JPanel();
            panel3.setLayout(new FlowLayout());
            QLabel xCoordLabel = new QLabel( rb.getQString("ReporterLocationX"));
            panel3.add(xCoordLabel);
            panel3.add(xPositionField);
            xPositionField.setToolTipText( rb.getQString("ReporterLocationXHint") );
            QLabel yCoordLabel = new QLabel( rb.getQString("ReporterLocationY"));
            panel3.add(yCoordLabel);
            panel3.add(yPositionField);
            yPositionField.setToolTipText( rb.getQString("ReporterLocationYHint") );
            theContentPane.add(panel3);
            // set up Add and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            panel5.add(reporterDone = new JButton(rb.getQString("AddNewLabel")));
            reporterDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    reporterDonePressed(e);
                }
            });
            reporterDone.setToolTipText( rb.getQString("ReporterDoneHint") );
            // Cancel
            panel5.add(reporterCancel = new JButton(rb.getQString("Cancel")));
            reporterCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    reporterCancelPressed(e);
                }
            });
            reporterCancel.setToolTipText( rb.getQString("CancelHint") );
            theContentPane.add(panel5);

        }
        // Set up for Entry of Reporter Icon
        xPositionField.setText(""+defaultX);
        yPositionField.setText(""+defaultY);
        enterReporterFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    reporterCancelPressed(NULL);
                }
            });
        enterReporterFrame.pack();
        enterReporterFrame.setVisible(true);
        reporterOpen = true;
    }
    void LayoutEditor::reporterDonePressed(ActionEvent a) {
        // get size of current panel
        Dimension dim = getTargetPanelSize();
        // get x coordinate
        QString newX = "";
        int xx = 0;
        newX = xPositionField.getText().trim();
        try {
            xx = Integer.parseInt(newX);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(enterReporterFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if ( ( xx<=0) || (xx>dim.width) ) {
            JOptionPane.showMessageDialog(enterReporterFrame,
                    java.text.MessageFormat.format(rb.getQString("Error2a"),
                    new Object[]{" "+xx+" "}),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get y coordinate
        QString newY = "";
        int yy = 0;
        newY = yPositionField.getText().trim();
        try {
            yy = Integer.parseInt(newY);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(enterReporterFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        if ( ( yy<=0) || (yy>dim.height) ) {
            JOptionPane.showMessageDialog(enterReporterFrame,
                    java.text.MessageFormat.format(rb.getQString("Error2a"),
                    new Object[]{" "+yy+" "}),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get reporter name
        Reporter reporter = NULL;
        QString rName = reporterNameField.getText().trim();
        if (InstanceManager.reporterManagerInstance()!=NULL) {
            reporter = InstanceManager.reporterManagerInstance().
                provideReporter(rName);
            if (reporter == NULL) {
                JOptionPane.showMessageDialog(enterReporterFrame,
                    java.text.MessageFormat.format(rb.getQString("Error18"),
                    new Object[]{rName}),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
                return;
            }
            if ( !rName==(reporter.getUserName()) )
                rName = rName.toUpperCase();
        }
        else {
            JOptionPane.showMessageDialog(enterReporterFrame,
                    rb.getQString("Error17"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // add the reporter icon
        addReporter(rName,xx,yy);
        // success - repaint the panel
        repaint();
        enterReporterFrame.setVisible(true);
    }
    void LayoutEditor::reporterCancelPressed(ActionEvent a) {
        reporterOpen = false;
        enterReporterFrame.setVisible(false);
        enterReporterFrame.dispose();
        enterReporterFrame = NULL;
        repaint();
    }


    // display dialog for scaling the track diagram
    /*protected*/ void LayoutEditor::scaleTrackDiagram() {
        if (scaleTrackDiagramOpen) {
            scaleTrackDiagramFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (scaleTrackDiagramFrame == NULL) {
            scaleTrackDiagramFrame = new JmriJFrame( rb.getQString("ScaleTrackDiagram") );
            scaleTrackDiagramFrame.addHelpMenu("package.jmri.jmrit.display.ScaleTrackDiagram", true);
            scaleTrackDiagramFrame.setLocation(70,30);
            Container theContentPane = scaleTrackDiagramFrame.getContentPane();
            theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.Y_AXIS));
            // setup x translate
            JPanel panel31 = new JPanel();
            panel31.setLayout(new FlowLayout());
            QLabel xTranslateLabel = new QLabel( rb.getQString("XTranslateLabel"));
            panel31.add(xTranslateLabel);
            panel31.add(xTranslateField);
            xTranslateField.setToolTipText( rb.getQString("XTranslateHint") );
            theContentPane.add(panel31);
            // setup y translate
            JPanel panel32 = new JPanel();
            panel32.setLayout(new FlowLayout());
            QLabel yTranslateLabel = new QLabel( rb.getQString("YTranslateLabel"));
            panel32.add(yTranslateLabel);
            panel32.add(yTranslateField);
            yTranslateField.setToolTipText( rb.getQString("YTranslateHint") );
            theContentPane.add(panel32);
            // setup information message 1
            JPanel panel33 = new JPanel();
            panel33.setLayout(new FlowLayout());
            QLabel message1Label = new QLabel( rb.getQString("Message1Label"));
            panel33.add(message1Label);
            theContentPane.add(panel33);
            // setup x factor
            JPanel panel21 = new JPanel();
            panel21.setLayout(new FlowLayout());
            QLabel xFactorLabel = new QLabel( rb.getQString("XFactorLabel"));
            panel21.add(xFactorLabel);
            panel21.add(xFactorField);
            xFactorField.setToolTipText( rb.getQString("FactorHint") );
            theContentPane.add(panel21);
            // setup y factor
            JPanel panel22 = new JPanel();
            panel22.setLayout(new FlowLayout());
            QLabel yFactorLabel = new QLabel( rb.getQString("YFactorLabel"));
            panel22.add(yFactorLabel);
            panel22.add(yFactorField);
            yFactorField.setToolTipText( rb.getQString("FactorHint") );
            theContentPane.add(panel22);
            // setup information message 2
            JPanel panel23 = new JPanel();
            panel23.setLayout(new FlowLayout());
            QLabel message2Label = new QLabel( rb.getQString("Message2Label"));
            panel23.add(message2Label);
            theContentPane.add(panel23);
            // set up Done and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            panel5.add(scaleTrackDiagramDone = new JButton(rb.getQString("ScaleTranslate")));
            scaleTrackDiagramDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    scaleTrackDiagramDonePressed(e);
                }
            });
            scaleTrackDiagramDone.setToolTipText( rb.getQString("ScaleTranslateHint") );
            panel5.add(scaleTrackDiagramCancel = new JButton(rb.getQString("Cancel")));
            scaleTrackDiagramCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    scaleTrackDiagramCancelPressed(e);
                }
            });
            scaleTrackDiagramCancel.setToolTipText( rb.getQString("CancelHint") );
            theContentPane.add(panel5);
        }
        // Set up for Entry of Scale and Translation
        xFactorField.setText("1.0");
        yFactorField.setText("1.0");
        xTranslateField.setText("0");
        yTranslateField.setText("0");
        scaleTrackDiagramFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    scaleTrackDiagramCancelPressed(NULL);
                }
            });
        scaleTrackDiagramFrame.pack();
        scaleTrackDiagramFrame.setVisible(true);
        scaleTrackDiagramOpen = true;
    }
    void LayoutEditor::scaleTrackDiagramDonePressed(ActionEvent a) {
        QString newText = "";
        bool scaleChange = false;
        bool translateError = false;
        float xTranslation = 0.0F;
        float yTranslation = 0.0F;
        float xFactor = 1.0F;
        float yFactor = 1.0F;
        // get x translation
        newText = xTranslateField.getText().trim();
        try {
            xTranslation = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(scaleTrackDiagramFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get y translation
        newText = yTranslateField.getText().trim();
        try {
            yTranslation = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(scaleTrackDiagramFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get x factor
        newText = xFactorField.getText().trim();
        try {
            xFactor = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(scaleTrackDiagramFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get y factor
        newText = yFactorField.getText().trim();
        try {
            yFactor = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(scaleTrackDiagramFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // here when all numbers read in successfully - check for translation
        if ( (xTranslation!=0.0F) || (yTranslation!=0.0F) ) {
            // apply translation
            if ( translateTrack(xTranslation,yTranslation) )
                scaleChange = true;
            else {
                log.error("Error translating track diagram");
                translateError = true;
            }
        }
        if ( !translateError && ( (xFactor!=1.0) || (yFactor!=1.0) ) ) {
            // apply scale change
            if ( scaleTrack(xFactor,yFactor) )
                scaleChange = true;
            else
                log.error("Error scaling track diagram");
        }
        // success - dispose of the dialog and repaint if needed
        scaleTrackDiagramOpen = false;
        scaleTrackDiagramFrame.setVisible(false);
        scaleTrackDiagramFrame.dispose();
        scaleTrackDiagramFrame = NULL;
        if (scaleChange) {
            repaint();
            setDirty(true);
        }
    }
    void LayoutEditor::scaleTrackDiagramCancelPressed(ActionEvent a) {
        scaleTrackDiagramOpen = false;
        scaleTrackDiagramFrame.setVisible(false);
        scaleTrackDiagramFrame.dispose();
        scaleTrackDiagramFrame = NULL;
    }
    bool LayoutEditor::translateTrack (float xDel, float yDel) {
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout* t = turnoutList.get(i);
            QPointF center = t.getCoordsCenter();
            t.setCoordsCenter(new QPointF.Double(center.getX()+xDel,center.getY()+yDel));
        }
        // loop over all defined level crossings
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            QPointF center = x.getCoordsCenter();
            x.setCoordsCenter(new QPointF.Double(center.getX()+xDel,center.getY()+yDel));
        }
        // loop over all defined level crossings
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip x = slipList.get(i);
            QPointF center = x.getCoordsCenter();
            x.setCoordsCenter(new QPointF.Double(center.getX()+xDel,center.getY()+yDel));
        }
        // loop over all defined turntables
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            QPointF center = x.getCoordsCenter();
            x.setCoordsCenter(new QPointF.Double(center.getX()+xDel,center.getY()+yDel));
        }
        // loop over all defined Anchor Points and End Bumpers
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            QPointF coord = p.getCoords();
            p.setCoords(new QPointF.Double(coord.getX()+xDel,coord.getY()+yDel));
        }
        return true;
    }
    bool LayoutEditor::scaleTrack (float xFactor, float yFactor) {
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            t.scaleCoords(xFactor,yFactor);
        }
        // loop over all defined level crossings
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            x.scaleCoords(xFactor,yFactor);
        }
        // loop over all defined level crossings
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip x = slipList.get(i);
            x.scaleCoords(xFactor,yFactor);
        }
        // loop over all defined turntables
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            x.scaleCoords(xFactor,yFactor);
        }
        // loop over all defined Anchor Points and End Bumpers
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            QPointF coord = p.getCoords();
            p.setCoords(new QPointF.Double(round(coord.getX()*xFactor),
                                        round(coord.getY()*yFactor)));
        }
        // update the overall scale factors
        xScale = xScale*xFactor;
        yScale = yScale*yFactor;
        return true;
    }
    double round (double x) {
        int i = (int)(x+0.5);
        return (i);
    }


    // display dialog for translation a selection
    /*protected*/ void LayoutEditor::moveSelection() {
        if (!selectionActive || (selectionWidth==0.0) || (selectionHeight==0.0) ) {
            // no selection has been made - nothing to move
            JOptionPane.showMessageDialog(this,rb.getQString("Error12"),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (moveSelectionOpen) {
            moveSelectionFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (moveSelectionFrame == NULL) {
            moveSelectionFrame = new JmriJFrame( rb.getQString("TranslateSelection") );
            moveSelectionFrame.addHelpMenu("package.jmri.jmrit.display.TranslateSelection", true);
            moveSelectionFrame.setLocation(70,30);
            Container theContentPane = moveSelectionFrame.getContentPane();
            theContentPane.setLayout(new BoxLayout(theContentPane, BoxLayout.Y_AXIS));
            // setup x translate
            JPanel panel31 = new JPanel();
            panel31.setLayout(new FlowLayout());
            QLabel xMoveLabel = new QLabel( rb.getQString("XTranslateLabel"));
            panel31.add(xMoveLabel);
            panel31.add(xMoveField);
            xMoveField.setToolTipText( rb.getQString("XTranslateHint") );
            theContentPane.add(panel31);
            // setup y translate
            JPanel panel32 = new JPanel();
            panel32.setLayout(new FlowLayout());
            QLabel yMoveLabel = new QLabel( rb.getQString("YTranslateLabel"));
            panel32.add(yMoveLabel);
            panel32.add(yMoveField);
            yMoveField.setToolTipText( rb.getQString("YTranslateHint") );
            theContentPane.add(panel32);
            // setup information message
            JPanel panel33 = new JPanel();
            panel33.setLayout(new FlowLayout());
            QLabel message1Label = new QLabel( rb.getQString("Message3Label"));
            panel33.add(message1Label);
            theContentPane.add(panel33);
            // set up Done and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            panel5.add(moveSelectionDone = new JButton(rb.getQString("MoveSelection")));
            moveSelectionDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    moveSelectionDonePressed(e);
                }
            });
            moveSelectionDone.setToolTipText( rb.getQString("MoveSelectionHint") );
            panel5.add(moveSelectionCancel = new JButton(rb.getQString("Cancel")));
            moveSelectionCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    moveSelectionCancelPressed(e);
                }
            });
            moveSelectionCancel.setToolTipText( rb.getQString("CancelHint") );
            theContentPane.add(panel5);
        }
        // Set up for Entry of Translation
        xMoveField.setText("0");
        yMoveField.setText("0");
        moveSelectionFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    moveSelectionCancelPressed(NULL);
                }
            });
        moveSelectionFrame.pack();
        moveSelectionFrame.setVisible(true);
        moveSelectionOpen = true;
    }
    void LayoutEditor::moveSelectionDonePressed(ActionEvent a) {
        QString newText = "";
        float xTranslation = 0.0F;
        float yTranslation = 0.0F;
        // get x translation
        newText = xMoveField.getText().trim();
        try {
            xTranslation = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(moveSelectionFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // get y translation
        newText = yMoveField.getText().trim();
        try {
            yTranslation = Float.parseFloat(newText);
        }
        catch (Exception e) {
            JOptionPane.showMessageDialog(moveSelectionFrame,rb.getQString("EntryError")+": "+
                    e+" "+rb.getQString("TryAgain"),rb.getQString("Error"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        // here when all numbers read in - translation if entered
        if ( (xTranslation!=0.0F) || (yTranslation!=0.0F) ) {
            // set up selection rectangle
            Rectangle2D selectRect = new Rectangle2D.Double (selectionX, selectionY,
                                                            selectionWidth, selectionHeight);
            // set up undo information
            undoRect = new Rectangle2D.Double (selectionX+xTranslation, selectionY+yTranslation,
                                                            selectionWidth, selectionHeight);
            undoDeltaX = -xTranslation;
            undoDeltaY = -yTranslation;
            canUndoMoveSelection = true;
            // apply translation to icon items within the selection
            List <Positionable> contents = getContents();
            for (int i = 0; i<contents.size(); i++) {
                Positionable c = contents.get(i);
                QPointF upperLeft = c.getLocation();
                if (selectRect.contains(upperLeft)) {
                    int xNew = (int)(upperLeft.getX()+xTranslation);
                    int yNew = (int)(upperLeft.getY()+yTranslation);
                    c.setLocation(xNew,yNew);
                }
            }
            // loop over all defined turnouts
            for (int i = 0; i<turnoutList.size();i++) {
                LayoutTurnout t = turnoutList.get(i);
                QPointF center = t.getCoordsCenter();
                if (selectRect.contains(center)) {
                    t.setCoordsCenter(new QPointF.Double(center.getX()+xTranslation,
                                                                center.getY()+yTranslation));
                }
            }
            // loop over all defined level crossings
            for (int i = 0; i<xingList.size();i++) {
                LevelXing x = xingList.get(i);
                QPointF center = x.getCoordsCenter();
                if (selectRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+xTranslation,
                                                                center.getY()+yTranslation));
                }
            }
            // loop over all defined level crossings
            for (int i = 0; i<slipList.size();i++) {
                LayoutSlip x = slipList.get(i);
                QPointF center = x.getCoordsCenter();
                if (selectRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+xTranslation,
                                                                center.getY()+yTranslation));
                }
            }
            // loop over all defined turntables
            for (int i = 0; i<turntableList.size();i++) {
                LayoutTurntable x = turntableList.get(i);
                QPointF center = x.getCoordsCenter();
                if (selectRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+xTranslation,
                                                                center.getY()+yTranslation));
                }
            }
            // loop over all defined Anchor Points and End Bumpers
            for (int i = 0; i<pointList.size();i++) {
                PositionablePoint p = pointList.get(i);
                QPointF coord = p.getCoords();
                if (selectRect.contains(coord)) {
                    p.setCoords(new QPointF.Double(coord.getX()+xTranslation,
                                                                coord.getY()+yTranslation));
                }
            }
            repaint();
            setDirty(true);
        }
        // success - hide dialog
        moveSelectionOpen = false;
        moveSelectionFrame.setVisible(false);
        moveSelectionFrame.dispose();
        moveSelectionFrame = NULL;
    }
    void LayoutEditor::moveSelectionCancelPressed(ActionEvent a) {
        moveSelectionOpen = false;
        moveSelectionFrame.setVisible(false);
        moveSelectionFrame.dispose();
        moveSelectionFrame = NULL;
    }
    void LayoutEditor::undoMoveSelection() {
        if (canUndoMoveSelection) {
            List <Positionable> contents = getContents();
            for (int i = 0; i<contents.size(); i++) {
                Positionable c = contents.get(i);
                QPointF upperLeft = c.getLocation();
                if (undoRect.contains(upperLeft)) {
                    int xNew = (int)(upperLeft.getX()+undoDeltaX);
                    int yNew = (int)(upperLeft.getY()+undoDeltaY);
                    c.setLocation(xNew,yNew);
                }
            }
            for (int i = 0; i<turnoutList.size();i++) {
                LayoutTurnout t = turnoutList.get(i);
                QPointF center = t.getCoordsCenter();
                if (undoRect.contains(center)) {
                    t.setCoordsCenter(new QPointF.Double(center.getX()+undoDeltaX,
                                                            center.getY()+undoDeltaY));
                }
            }
            for (int i = 0; i<xingList.size();i++) {
                LevelXing x = xingList.get(i);
                QPointF center = x.getCoordsCenter();
                if (undoRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+undoDeltaX,
                                                                center.getY()+undoDeltaY));
                }
            }
            for (int i = 0; i<slipList.size();i++) {
                LayoutSlip x = slipList.get(i);
                QPointF center = x.getCoordsCenter();
                if (undoRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+undoDeltaX,
                                                                center.getY()+undoDeltaY));
                }
            }
            for (int i = 0; i<turntableList.size();i++) {
                LayoutTurntable x = turntableList.get(i);
                QPointF center = x.getCoordsCenter();
                if (undoRect.contains(center)) {
                    x.setCoordsCenter(new QPointF.Double(center.getX()+undoDeltaX,
                                                                center.getY()+undoDeltaY));
                }
            }
            for (int i = 0; i<pointList.size();i++) {
                PositionablePoint p = pointList.get(i);
                QPointF coord = p.getCoords();
                if (undoRect.contains(coord)) {
                    p.setCoords(new QPointF.Double(coord.getX()+undoDeltaX,
                                                                coord.getY()+undoDeltaY));
                }
            }
            repaint();
            canUndoMoveSelection = false;
        }
        return;
    }

    /*public*/ void LayoutEditor::setCurrentPositionAndSize() {
        // save current panel location and size
        Dimension dim = getSize();
        // Compute window size based on LayoutEditor size
        windowHeight = dim.height;
        windowWidth = dim.width;
        // Compute layout size based on LayoutPane size
        dim = getTargetPanelSize();
        panelHeight = (int)(dim.height/getPaintScale());
        panelWidth = (int)(dim.width/getPaintScale());
        Point pt = getLocationOnScreen();
        upperLeftX = pt.x;
        upperLeftY = pt.y;
        log.debug("setCurrentPositionAndSize Position - "+upperLeftX+","+upperLeftY+" WindowSize - "+windowWidth+","+windowHeight+" PanelSize - "+panelWidth+","+panelHeight);
        setDirty(true);
    }

    void LayoutEditor::addBackgroundColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  Color color) {
        ActionListener a = new ActionListener() {
                //final QString desiredName = name;
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (!defaultBackgroundColor==(desiredColor)) {
                        defaultBackgroundColor = desiredColor;
                        setBackgroundColor(desiredColor);
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        backgroundColorButtonGroup.add(r);
        if (defaultBackgroundColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        backgroundColorMenuItems[backgroundColorCount] = r;
        backgroundColors[backgroundColorCount] = color;
        backgroundColorCount ++;
    }

    void LayoutEditor::addTrackColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  Color color) {
        ActionListener a = new ActionListener() {
                //final QString desiredName = name;
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (!defaultTrackColor==(desiredColor)) {
                        defaultTrackColor = desiredColor;
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        trackColorButtonGroup.add(r);
        if (defaultTrackColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        trackColorMenuItems[trackColorCount] = r;
        trackColors[trackColorCount] = color;
        trackColorCount ++;
    }

    void LayoutEditor::addTrackOccupiedColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  Color color) {
        ActionListener a = new ActionListener() {
                //final QString desiredName = name;
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (!defaultOccupiedTrackColor==(desiredColor)) {
                        defaultOccupiedTrackColor = desiredColor;
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        trackOccupiedColorButtonGroup.add(r);
        if (defaultOccupiedTrackColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        trackOccupiedColorMenuItems[trackOccupiedColorCount] = r;
        trackOccupiedColors[trackOccupiedColorCount] = color;
        trackOccupiedColorCount ++;
    }

    void LayoutEditor::addTrackAlternativeColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  QColor color) {
        ActionListener a = new ActionListener() {
                //final QString desiredName = name;
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (!defaultAlternativeTrackColor==(desiredColor)) {
                        defaultAlternativeTrackColor = desiredColor;
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        trackAlternativeColorButtonGroup.add(r);
        if (defaultAlternativeTrackColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        trackAlternativeColorMenuItems[trackAlternativeColorCount] = r;
        trackAlternativeColors[trackAlternativeColorCount] = color;
        trackAlternativeColorCount ++;
    }

    /*protected*/ void LayoutEditor::setOptionMenuTrackColor() {
        for (int i = 0;i<trackColorCount;i++) {
            if (trackColors[i]==(defaultTrackColor))
                trackColorMenuItems[i].setSelected(true);
            else
                trackColorMenuItems[i].setSelected(false);
        }
        for (int i = 0;i<trackOccupiedColorCount;i++) {
            if (trackOccupiedColors[i]==(defaultOccupiedTrackColor))
                trackOccupiedColorMenuItems[i].setSelected(true);
            else
                trackOccupiedColorMenuItems[i].setSelected(false);
        }
        for (int i = 0;i<trackAlternativeColorCount;i++) {
            if (trackAlternativeColors[i]==(defaultAlternativeTrackColor))
                trackAlternativeColorMenuItems[i].setSelected(true);
            else
                trackAlternativeColorMenuItems[i].setSelected(false);
        }
    }

    void LayoutEditor::addTextColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  QColor color) {
        ActionListener a = new ActionListener() {
                //final QString desiredName = name;
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (!defaultTextColor==(desiredColor)) {
                        defaultTextColor = desiredColor;
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        textColorButtonGroup.add(r);
        if (defaultTextColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        textColorMenuItems[textColorCount] = r;
        textColors[textColorCount] = color;
        textColorCount ++;
    }

    void LayoutEditor::addTurnoutCircleColorMenuEntry(/*JMenu*/QMenu menu,  QString name,  Color color) {
        ActionListener a = new ActionListener() {
                final Color desiredColor = color;
                /*public*/ void actionPerformed(ActionEvent e) {
                    turnoutCircleColor = desiredColor;
                    setDirty(true);
                    repaint();
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        turnoutCircleColorButtonGroup.add(r);
        if (turnoutCircleColor==(color)) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        turnoutCircleColorMenuItems[turnoutCircleColorCount] = r;
        turnoutCircleColors[turnoutCircleColorCount] = color;
        turnoutCircleColorCount ++;
    }

    void LayoutEditor::addTurnoutCircleSizeMenuEntry(/*JMenu*/QMenu menu,  QString name,  int size) {
        ActionListener a = new ActionListener() {
                final int desiredSize = size;
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (turnoutCircleSize!=desiredSize) {
                        turnoutCircleSize = desiredSize;
                        setDirty(true);
                        repaint();
                    }
                }
            };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);
        turnoutCircleSizeButtonGroup.add(r);
        if (turnoutCircleSize == size) r.setSelected(true);
        else r.setSelected(false);
        menu.add(r);
        turnoutCircleSizeMenuItems[turnoutCircleSizeCount] = r;
        turnoutCircleSizes[turnoutCircleSizeCount] = size;
        turnoutCircleSizeCount ++;
    }

    /*protected*/ void LayoutEditor::setOptionMenuTurnoutCircleColor() {
        for (int i = 0;i<turnoutCircleColorCount;i++) {
            if (turnoutCircleColors[i] == NULL && turnoutCircleColor == NULL)
                turnoutCircleColorMenuItems[i].setSelected(true);
            else if (turnoutCircleColors[i] != NULL && turnoutCircleColors[i]==(turnoutCircleColor))
                turnoutCircleColorMenuItems[i].setSelected(true);
            else
                turnoutCircleColorMenuItems[i].setSelected(false);
        }
    }

    /*protected*/ void LayoutEditor::setOptionMenuTurnoutCircleSize() {
        for (int i = 0;i<turnoutCircleSizeCount;i++) {
            if (turnoutCircleSizes[i] == turnoutCircleSize)
                turnoutCircleSizeMenuItems[i].setSelected(true);
            else
                turnoutCircleSizeMenuItems[i].setSelected(false);
        }
    }


    /*protected*/ void LayoutEditor::setOptionMenuTextColor() {
        for (int i = 0;i<textColorCount;i++) {
            if (textColors[i]==(defaultTextColor))
                textColorMenuItems[i].setSelected(true);
            else
                textColorMenuItems[i].setSelected(false);
        }
    }

    /*protected*/ void LayoutEditor::setOptionMenuBackgroundColor() {
        for (int i = 0;i<backgroundColorCount;i++) {
            if (backgroundColors[i]==(defaultBackgroundColor))
                backgroundColorMenuItems[i].setSelected(true);
            else
                backgroundColorMenuItems[i].setSelected(false);
        }
    }

    /*public*/ void LayoutEditor::setScroll(int state) {
        if (isEditable()) {
            //In edit mode the scroll bars are always displayed, however we will want to set the scroll for when we exit edit mode
            super.setScroll(SCROLL_BOTH);
            _scrollState = state;
        } else {
            super.setScroll(state);
        }
    }

    /**
     * Add a layout turntable at location specified
     */
    /*public*/ void LayoutEditor::addTurntable(QPointF pt) {
        numLayoutTurntables ++;
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "TUR"+numLayoutTurntables;
            if (findLayoutTurntableByName(name)==NULL) duplicate = false;
            if (duplicate) numLayoutTurntables ++;
        }
        LayoutTurntable x = new LayoutTurntable(name,pt,this);
        //if (x != NULL) {
        turntableList.add(x);
        setDirty(true);
        //}
        x.addRay(0.0);
        x.addRay(90.0);
        x.addRay(180.0);
        x.addRay(270.0);
    }

    /**
     * Allow external trigger of re-draw
     */
    /*public*/ void LayoutEditor::redrawPanel() {
        repaint();
    }

    /**
     * Allow external set/reset of awaitingIconChange
     */
    /*public*/ void LayoutEditor::setAwaitingIconChange() {
        awaitingIconChange = true;
    }
    /*public*/ void LayoutEditor::resetAwaitingIconChange() {
        awaitingIconChange = false;
    }

    /**
     * Allow external reset of dirty bit
     */
    /*public*/ void LayoutEditor::resetDirty() {
        setDirty(false);
        savedEditMode = isEditable();
        savedPositionable = allPositionable();
        savedControlLayout = allControlling();
        savedAnimatingLayout = animatingLayout;
        savedShowHelpBar = showHelpBar;
    }

    /**
     * Allow external set of dirty bit
     */
    /*public*/ void LayoutEditor::setDirty(bool val) { panelChanged = val; }
    /*public*/ void LayoutEditor::setDirty() { setDirty(true); }

    /**
     * Check the dirty state
     */
    /*public*/ bool LayoutEditor::isDirty() { return panelChanged; }

    /*
     * Get mouse coordinates and adjust for zoom
     */
    /*private*/ void LayoutEditor::calcLocation(MouseEvent event, int dX, int dY) {
        xLoc = (int)((event.getX() + dX)/getPaintScale());
        yLoc = (int)((event.getY() + dY)/getPaintScale());
        dLoc.setLocation(xLoc,yLoc);
    }

    /**
     * Handle a mouse pressed event
     */
    /*public*/ void LayoutEditor::mousePressed(MouseEvent event)
    {
        // initialize cursor position
        _anchorX = xLoc;
        _anchorY = yLoc;
        _lastX = _anchorX;
        _lastY = _anchorY;
        calcLocation(event,0,0);
        if (isEditable()) {
            bool prevSelectionActive = selectionActive;
            selectionActive = false;
            xLabel.setText(Integer.toQString(xLoc));
            yLabel.setText(Integer.toQString(yLoc));
            if (event.isPopupTrigger()) {
                if (event.isMetaDown() || event.isAltDown()) {
                    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
                    delayedPopupTrigger = true;
                }
                else {
                    // no possible conflict with moving, display the popup now
                    checkPopUp(event);
                }
            }
            if (event.isMetaDown() || event.isAltDown()) {
                // if moving an item, identify the item for mouseDragging
                selectedObject = NULL;
                selectedPointType = NONE;
                if (checkSelect(dLoc, false)) {
                    selectedObject = foundObject;
                    selectedPointType = foundPointType;
                    //selectedNeedsConnect = foundNeedsConnect;
                    startDel.setLocation(foundLocation.getX()-dLoc.getX(), foundLocation.getY()-dLoc.getY());
                    foundObject = NULL;
                }
                else {
                    selectedObject = checkMarkers(dLoc);
                    if (selectedObject!=NULL) {
                        selectedPointType = MARKER;
                        startDel.setLocation((((LocoIcon)selectedObject).getX()-dLoc.getX()),
                                                (((LocoIcon)selectedObject).getY()-dLoc.getY()));
                        //selectedNeedsConnect = false;
                    }
                    else {
                        selectedObject = checkClocks(dLoc);
                        if (selectedObject!=NULL) {
                            selectedPointType = LAYOUT_POS_JCOMP;
                            startDel.setLocation((((PositionableJComponent)selectedObject).getX()-dLoc.getX()),
                                                (((PositionableJComponent)selectedObject).getY()-dLoc.getY()));
                            //selectedNeedsConnect = false;
                        }
                        else {
                            selectedObject = checkMultiSensors(dLoc);
                            if (selectedObject!=NULL) {
                                selectedPointType = MULTI_SENSOR;
                                startDel.setLocation((((MultiSensorIcon)selectedObject).getX()-dLoc.getX()),
                                                (((MultiSensorIcon)selectedObject).getY()-dLoc.getY()));
                                //selectedNeedsConnect = false;
                            }
                        }
                    }
                    if (selectedObject==NULL) {
                        selectedObject = checkSensorIcons(dLoc);
                        if (selectedObject==NULL) {
                            selectedObject = checkSignalHeadIcons(dLoc);
                            if (selectedObject==NULL) {
                                selectedObject = checkLabelImages(dLoc);
                                if(selectedObject==NULL) {
                                    selectedObject = checkSignalMastIcons(dLoc);
                                }
                            }
                        }
                        if (selectedObject!=NULL) {
                            selectedPointType = LAYOUT_POS_LABEL;
                            startDel.setLocation((((PositionableLabel)selectedObject).getX()-dLoc.getX()),
                                                (((PositionableLabel)selectedObject).getY()-dLoc.getY()));
                            if (selectedObject instanceof MemoryIcon) {
                                MemoryIcon pm = (MemoryIcon) selectedObject;
                                if (pm.getPopupUtility().getFixedWidth()==0){
                                    startDel.setLocation((pm.getOriginalX()-dLoc.getX()),
                                                        (pm.getOriginalY()-dLoc.getY()));
                                }
                            }

                            //selectedNeedsConnect = false;

                        }
                        else {
                            selectedObject = checkBackgrounds(dLoc);
                            if (selectedObject!=NULL) {
                                selectedPointType = LAYOUT_POS_LABEL;
                                startDel.setLocation((((PositionableLabel)selectedObject).getX()-dLoc.getX()),
                                                    (((PositionableLabel)selectedObject).getY()-dLoc.getY()));
                                //selectedNeedsConnect = false;
                            }
                        }
                    }
                }
            }
            else if (event.isShiftDown() && trackBox.isSelected() && (!event.isPopupTrigger()) ) {
                // starting a Track Segment, check for free connection point
                selectedObject = NULL;
                if (checkSelect(dLoc, true)) {
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
            else if ( (!event.isShiftDown()) && (!event.isControlDown()) && (!event.isPopupTrigger()) ) {
            // check if controlling a turnout in edit mode
                selectedObject = NULL;
                if (allControlling()) {
                    // check if mouse is on a turnout
                    selectedObject = NULL;
                    for (int i = 0; i<turnoutList.size();i++) {
                        LayoutTurnout t = turnoutList.get(i);
                        // check the center point
                        QPointF pt = t.getCoordsCenter();
                        Rectangle2D r = new Rectangle2D.Double(
                                pt.getX()-SIZE2,pt.getY()-SIZE2,2.0*SIZE2,2.0*SIZE2);
                        if (r.contains(dLoc)) {
                            // mouse was pressed on this turnout
                            selectedObject = t;
                            selectedPointType = TURNOUT_CENTER;
                            break;
                        }
                    }
                    for(LayoutSlip sl : slipList){
                        // check the center point
                        QPointF pt = sl.getCoordsCenter();
                        Rectangle2D r = new Rectangle2D.Double(
                                pt.getX()-(SIZE2*2.0),pt.getY()-(SIZE2*2.0),4.0*SIZE2,4.0*SIZE2);
                        if (r.contains(dLoc)) {
                            // mouse was pressed on this turnout
                            selectedObject = sl;
                            selectedPointType = SLIP_CENTER;
                            break;
                        }
                    }
                    for (int i = 0; i<turntableList.size();i++) {
                        LayoutTurntable x = turntableList.get(i);
                        for (int k = 0; k<x.getNumberRays(); k++) {
                            if (x.getRayConnectOrdered(k)!=NULL) {
                                // check the A connection point
                                QPointF pt = x.getRayCoordsOrdered(k);
                                Rectangle2D r = new Rectangle2D.Double(
                                        pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                                if (r.contains(dLoc)) {
                                    // mouse was pressed on this connection point
                                    selectedObject = x;
                                    selectedPointType = TURNTABLE_RAY_OFFSET+x.getRayIndex(k);
                                    break;
                                }
                            }
                        }
                    }
                }
                // initialize starting selection - cancel any previous selection rectangle
                selectionActive = true;
                selectionX = dLoc.getX();
                selectionY = dLoc.getY();
                selectionWidth = 0.0;
                selectionHeight = 0.0;
            }
            if (prevSelectionActive) repaint();
        }

        else if (allControlling() && (!event.isMetaDown()) && (!event.isPopupTrigger()) &&
                        (!event.isAltDown()) &&(!event.isShiftDown()) && (!event.isControlDown()) ) {
            // not in edit mode - check if mouse is on a turnout (using wider search range)
            selectedObject = NULL;
            for (int i = 0; i<turnoutList.size();i++) {
                LayoutTurnout t = turnoutList.get(i);
                // check a rectangle as large as turnout circle, but at least size 4
                QPointF pt = t.getCoordsCenter();
                double size = SIZE * turnoutCircleSize;
                if (size < SIZE2*2.0) size = SIZE2*2.0;
                Rectangle2D r = new Rectangle2D.Double(
                        pt.getX()-size, pt.getY()-size, size+size, size+size);
                if (r.contains(dLoc)) {
                    // mouse was pressed on this turnout
                    selectedObject = t;
                    selectedPointType = TURNOUT_CENTER;
                    break;
                }
            }
            for(LayoutSlip sl : slipList){
                // check the center point
                QPointF pt = sl.getCoordsCenter();
                Rectangle2D r = new Rectangle2D.Double(
                        pt.getX()-(SIZE2*2.0),pt.getY()-(SIZE2*2.0),4.0*SIZE2,4.0*SIZE2);
                if (r.contains(dLoc)) {
                    // mouse was pressed on this turnout
                    selectedObject = sl;
                    selectedPointType = SLIP_CENTER;
                    break;
                }
            }
            for (int i = 0; i<turntableList.size();i++) {
                LayoutTurntable x = turntableList.get(i);
                for (int k = 0; k<x.getNumberRays(); k++) {
                    if (x.getRayConnectOrdered(k)!=NULL) {
                        // check the A connection point
                        QPointF pt = x.getRayCoordsOrdered(k);
                        Rectangle2D r = new Rectangle2D.Double(
                                pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                        if (r.contains(dLoc)) {
                            // mouse was pressed on this connection point
                            selectedObject = x;
                            selectedPointType = TURNTABLE_RAY_OFFSET+x.getRayIndex(k);
                            break;
                        }
                    }
                }
            }
        }
        else if ( (event.isMetaDown() || event.isAltDown()) &&
                            (!event.isShiftDown()) && (!event.isControlDown()) ) {
            // not in edit mode - check if moving a marker if there are any
            selectedObject = checkMarkers(dLoc);
            if (selectedObject!=NULL) {
                selectedPointType = MARKER;
                startDel.setLocation((((LocoIcon)selectedObject).getX()-dLoc.getX()),
                                                (((LocoIcon)selectedObject).getY()-dLoc.getY()));
                //selectedNeedsConnect = false;
            }
        }
        else if ( event.isPopupTrigger() && (!event.isShiftDown()) ) {
            // not in edit mode - check if a marker popup menu is being requested
            LocoIcon lo = checkMarkers(dLoc);
            if (lo!=NULL) delayedPopupTrigger = true;
        }
        if (!event.isPopupTrigger() && !isDragging) {
            List <Positionable> selections = getSelectedItems(event);
            if (selections.size() > 0) {
                selections.get(0).doMousePressed(event);
            }
        }
        //thisPanel.setFocusable(true);
        thisPanel.requestFocusInWindow();

        return;
    }

    /*private*/ bool LayoutEditor::checkSelect(QPointF loc, bool requireUnconnected) {
        // check positionable points, if any
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            if ( (p!=selectedObject) && !requireUnconnected ||
                    (p.getConnect1()==NULL) ||
                    ((p.getType()!=PositionablePoint.END_BUMPER) &&
                                                (p.getConnect2()==NULL)) ) {
                QPointF pt = p.getCoords();
                Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                if (r.contains(loc)) {
                    // mouse was pressed on this connection point
                    foundLocation = pt;
                    foundObject = p;
                    foundPointType = POS_POINT;
                    foundNeedsConnect = ((p.getConnect1()==NULL)||(p.getConnect2()==NULL));
                    return true;
                }
            }
        }
        // check turnouts, if any
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            if (t!=selectedObject) {
                if (!requireUnconnected) {
                    // check the center point
                    QPointF pt = t.getCoordsCenter();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE2,pt.getY() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = t;
                        foundPointType = TURNOUT_CENTER;
                        foundNeedsConnect = false;
                        return true;
                    }
                }
                if (!requireUnconnected || (t.getConnectA()==NULL)) {
                    // check the A connection point
                    QPointF pt = t.getCoordsA();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = t;
                        foundPointType = TURNOUT_A;
                        foundNeedsConnect = (t.getConnectA()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (t.getConnectB()==NULL)) {
                    // check the B connection point
                    QPointF pt = t.getCoordsB();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = t;
                        foundPointType = TURNOUT_B;
                        foundNeedsConnect = (t.getConnectB()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (t.getConnectC()==NULL)) {
                    // check the C connection point
                    QPointF pt = t.getCoordsC();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = t;
                        foundPointType = TURNOUT_C;
                        foundNeedsConnect = (t.getConnectC()==NULL);
                        return true;
                    }
                }
                if (( (t.getTurnoutType()==LayoutTurnout.DOUBLE_XOVER) ||
                        (t.getTurnoutType()==LayoutTurnout.RH_XOVER) ||
                        (t.getTurnoutType()==LayoutTurnout.LH_XOVER) ) && (
                        !requireUnconnected || (t.getConnectD()==NULL))) {
                    // check the D connection point, double crossover turnouts only
                    QPointF pt = t.getCoordsD();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = t;
                        foundPointType = TURNOUT_D;
                        foundNeedsConnect = (t.getConnectD()==NULL);
                        return true;
                    }
                }
            }
        }

        // check level Xings, if any
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            if (x!=selectedObject) {
                if (!requireUnconnected) {
                    // check the center point
                    QPointF pt = x.getCoordsCenter();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE2,pt.getY() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = LEVEL_XING_CENTER;
                        foundNeedsConnect = false;
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectA()==NULL)) {
                    // check the A connection point
                    QPointF pt = x.getCoordsA();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = LEVEL_XING_A;
                        foundNeedsConnect = (x.getConnectA()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectB()==NULL)) {
                    // check the B connection point
                    QPointF pt = x.getCoordsB();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = LEVEL_XING_B;
                        foundNeedsConnect = (x.getConnectB()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectC()==NULL)) {
                    // check the C connection point
                    QPointF pt = x.getCoordsC();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = LEVEL_XING_C;
                        foundNeedsConnect = (x.getConnectC()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectD()==NULL)) {
                    // check the D connection point
                    QPointF pt = x.getCoordsD();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = LEVEL_XING_D;
                        foundNeedsConnect = (x.getConnectD()==NULL);
                        return true;
                    }
                }
            }
        }

        // check level Xings, if any
        for(LayoutSlip x: slipList){
            if (x!=selectedObject) {
                if (!requireUnconnected) {
                    // check the center point
                    QPointF pt = x.getCoordsCenter();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE2,pt.getY() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = SLIP_CENTER;
                        foundNeedsConnect = false;
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectA()==NULL)) {
                    // check the A connection point
                    QPointF pt = x.getCoordsA();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = SLIP_A;
                        foundNeedsConnect = (x.getConnectA()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectB()==NULL)) {
                    // check the B connection point
                    QPointF pt = x.getCoordsB();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = SLIP_B;
                        foundNeedsConnect = (x.getConnectB()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectC()==NULL)) {
                    // check the C connection point
                    QPointF pt = x.getCoordsC();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = SLIP_C;
                        foundNeedsConnect = (x.getConnectC()==NULL);
                        return true;
                    }
                }
                if (!requireUnconnected || (x.getConnectD()==NULL)) {
                    // check the D connection point
                    QPointF pt = x.getCoordsD();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this connection point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = SLIP_D;
                        foundNeedsConnect = (x.getConnectD()==NULL);
                        return true;
                    }
                }
            }
        }
        // check turntables, if any
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            if (x!=selectedObject) {
                if (!requireUnconnected) {
                    // check the center point
                    QPointF pt = x.getCoordsCenter();
                    Rectangle2D r = new Rectangle2D.Double(
                            pt.getX() - SIZE2,pt.getY() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
                    if (r.contains(loc)) {
                        // mouse was pressed on this center point
                        foundLocation = pt;
                        foundObject = x;
                        foundPointType = TURNTABLE_CENTER;
                        foundNeedsConnect = false;
                        return true;
                    }
                }
                for (int k = 0; k<x.getNumberRays(); k++) {
                    if (!requireUnconnected || (x.getRayConnectOrdered(k)==NULL)) {
                        QPointF pt = x.getRayCoordsOrdered(k);
                        Rectangle2D r = new Rectangle2D.Double(
                                pt.getX() - SIZE,pt.getY() - SIZE,SIZE2,SIZE2);
                        if (r.contains(loc)) {
                            // mouse was pressed on this connection point
                            foundLocation = pt;
                            foundObject = x;
                            foundPointType = TURNTABLE_RAY_OFFSET+x.getRayIndex(k);
                            foundNeedsConnect = (x.getRayConnectOrdered(k)==NULL);
                            return true;
                        }
                    }
                }
            }
        }

        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            if (t.getCircle()){
                QPointF pt = t.getCoordsCenterCircle();
                Rectangle2D r = new Rectangle2D.Double(
                        pt.getX() - SIZE2,pt.getY() - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
                if (r.contains(loc)) {
                    // mouse was pressed on this connection point
                    foundLocation = pt;
                    foundObject = t;
                    foundPointType = TRACK_CIRCLE_CENTRE;
                    foundNeedsConnect = false;
                    return true;
                }
            }
        }
        // no connection point found
        foundObject = NULL;
        return false;
    }

    /*private*/ TrackSegment* LayoutEditor::checkTrackSegments(QPointF loc) {
        // check Track Segments, if any
        for (int i = 0; i<trackList.size(); i++) {
            TrackSegment tr = trackList.get(i);
            Object o = tr.getConnect1();
            int type = tr.getType1();
            // get coordinates of first end point
            QPointF pt1 = getEndCoords(o,type);
            o = tr.getConnect2();
            type = tr.getType2();
            // get coordinates of second end point
            QPointF pt2 = getEndCoords(o,type);
            // construct a detection rectangle
            double cX = (pt1.getX() + pt2.getX())/2.0D;
            double cY = (pt1.getY() + pt2.getY())/2.0D;
            Rectangle2D r = new Rectangle2D.Double(
                        cX - SIZE2,cY - SIZE2,SIZE2+SIZE2,SIZE2+SIZE2);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in detection rectangle
                return tr;
            }
        }
        return NULL;
    }

    /*private*/ PositionableLabel* LayoutEditor::checkBackgrounds(QPointF loc) {
        // check background images, if any
        for (int i=backgroundImage.size()-1; i>=0; i--) {
            PositionableLabel b = backgroundImage.get(i);
            double x = b.getX();
            double y = b.getY();
            double w = b.maxWidth();
            double h = b.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in background image
                return b;
            }
        }
        return NULL;
    }

    /*private*/ SensorIcon* checkSensorIcons(QPointF loc) {
        // check sensor images, if any
        for (int i=sensorImage.size()-1; i>=0; i--) {
            SensorIcon* s = sensorImage.get(i);
            double x = s.getX();
            double y = s.getY();
            double w = s.maxWidth();
            double h = s.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in sensor icon image
                return s;
            }
        }
        return NULL;
    }

    /*private*/ SignalHeadIcon* LayoutEditor::checkSignalHeadIcons(QPointF loc) {
        // check signal head images, if any
        for (int i=signalHeadImage.size()-1; i>=0; i--) {
            SignalHeadIcon s = signalHeadImage.get(i);
            double x = s.getX();
            double y = s.getY();
            double w = s.maxWidth();
            double h = s.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in signal head image
                return s;
            }
        }
        return NULL;
    }

    /*private*/ SignalMastIcon* LayoutEditor::checkSignalMastIcons(QPointF loc) {
        // check signal head images, if any
        for (int i=signalMastImage.size()-1; i>=0; i--) {
            SignalMastIcon s = signalMastImage.get(i);
            double x = s.getX();
            double y = s.getY();
            double w = s.maxWidth();
            double h = s.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in signal head image
                return s;
            }
        }
        return NULL;
    }

    /*private*/ PositionableLabel* LayoutEditor::checkLabelImages(QPointF loc) {
           PositionableLabel l =NULL;
           int level = 0;
           for (int i=labelImage.size()-1; i>=0; i--) {
                   PositionableLabel s = labelImage.get(i);
                   double x = s.getX();
                   double y = s.getY();
                   double w = 10.0;
                   double h = 5.0;
                   if (s.isIcon() || s.isRotated()) {
                           w = s.maxWidth();
                           h = s.maxHeight();
                   }
                   else if (s.isText()) {
                           h = s.getFont().getSize();
                           w = (h*2*(s.getText().length()))/3;
                   }

                   Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
                   // Test this detection rectangle
                   if (r.contains(loc)) {
                       // mouse was pressed in label image
                       if (s.getDisplayLevel()>=level){
                       //Check to make sure that we are returning the highest level label.
                           l = s;
                           level = s.getDisplayLevel();
                       }
                   }
            }
            return l;
    }

    /*private*/ AnalogClock2Display* LayoutEditor::checkClocks(QPointF loc) {
        // check clocks, if any
        for (int i=clocks.size()-1; i>=0; i--) {
            AnalogClock2Display s = clocks.get(i);
            double x = s.getX();
            double y = s.getY();
            double w = s.getFaceWidth();
            double h = s.getFaceHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in clock image
                return s;
            }
        }
        return NULL;
    }

    /*private*/ MultiSensorIcon* LayoutEditor::checkMultiSensors(QPointF loc) {
        // check multi sensor icons, if any
        for (int i=multiSensors.size()-1; i>=0; i--) {
            MultiSensorIcon s = multiSensors.get(i);
            double x = s.getX();
            double y = s.getY();
            double w = s.maxWidth();
            double h = s.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in multi sensor image
                return s;
            }
        }
        return NULL;
    }

    /*private*/ LocoIcon* LayoutEditor::checkMarkers(QPointF loc) {
        // check marker icons, if any
        for (int i=markerImage.size()-1; i>=0; i--) {
            LocoIcon l = markerImage.get(i);
            double x = l.getX();
            double y = l.getY();
            double w = l.maxWidth();
            double h = l.maxHeight();
            Rectangle2D r = new Rectangle2D.Double(x ,y ,w ,h);
            // Test this detection rectangle
            if (r.contains(loc)) {
                // mouse was pressed in marker icon
                return l;
            }
        }
        return NULL;
    }

    /*public*/ QPointF LayoutEditor::getEndCoords(QObject* o, int type) {
        switch (type) {
            case POS_POINT:
                return ((PositionablePoint)o).getCoords();
            case TURNOUT_A:
                return ((LayoutTurnout)o).getCoordsA();
            case TURNOUT_B:
                return ((LayoutTurnout)o).getCoordsB();
            case TURNOUT_C:
                return ((LayoutTurnout)o).getCoordsC();
            case TURNOUT_D:
                return ((LayoutTurnout)o).getCoordsD();
            case LEVEL_XING_A:
                return ((LevelXing)o).getCoordsA();
            case LEVEL_XING_B:
                return ((LevelXing)o).getCoordsB();
            case LEVEL_XING_C:
                return ((LevelXing)o).getCoordsC();
            case LEVEL_XING_D:
                return ((LevelXing)o).getCoordsD();
            case SLIP_A:
                return ((LayoutSlip)o).getCoordsA();
            case SLIP_B:
                return ((LayoutSlip)o).getCoordsB();
            case SLIP_C:
                return ((LayoutSlip)o).getCoordsC();
            case SLIP_D:
                return ((LayoutSlip)o).getCoordsD();
            default:
                if (type>=TURNTABLE_RAY_OFFSET) {
                    return ((LayoutTurntable)o).getRayCoordsIndexed(type-TURNTABLE_RAY_OFFSET);
                }
        }
        return (new QPointF.Double(0.0,0.0));
    }

/*public*/ void LayoutEditor::mouseReleased(MouseEvent event)
{
    //super.setToolTip(NULL);
    // initialize mouse position
    calcLocation(event, 0, 0);
    if (isEditable()) {
        xLabel->setText(QString("%1").arg(xLoc));
        yLabel->setText(QString("%1").arg(yLoc));
        if (/*(!event.isPopupTrigger()) && (!event.isMetaDown()) &&*/ (!event.isAltDown()) && event.isShiftDown())
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
            if (turnoutRHBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.RH_TURNOUT);
            }
            else if (turnoutLHBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.LH_TURNOUT);
            }
            else if (turnoutWYEBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.WYE_TURNOUT);
            }
            else if (doubleXoverBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.DOUBLE_XOVER);
            }
            else if (rhXoverBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.RH_XOVER);
            }
            else if (lhXoverBox.isSelected()) {
                addLayoutTurnout(LayoutTurnout.LH_XOVER);
            }
            else if (levelXingBox.isSelected()) {
                addLevelXing();
            }
            else if (layoutSingleSlipBox.isSelected()) {
                addLayoutSlip(LayoutSlip.SINGLE_SLIP);
            }
            else if (layoutDoubleSlipBox.isSelected()) {
                addLayoutSlip(LayoutSlip.DOUBLE_SLIP);
            }
            else if (endBumperBox.isSelected()) {
                addEndBumper();
            }
            else if (anchorBox.isSelected()) {
                addAnchor();
            }
            else if (trackBox.isSelected()) {
                if ( (beginObject!=NULL) && (foundObject!=NULL) &&
                        (beginObject!=foundObject) ) {
                    addTrackSegment();
                    setCursor(Cursor.getDefaultCursor());
                }
                beginObject = NULL;
                foundObject = NULL;
            }
            else if (multiSensorBox.isSelected()) {
                startMultiSensor();
            }
            else if (sensorBox.isSelected()) {
                addSensor();
            }
            else if (signalBox.isSelected()) {
                addSignalHead();
            }
            else if (textLabelBox.isSelected()) {
                addLabel();
            }
            else if (memoryBox.isSelected()) {
                addMemory();
            }
            else if (iconLabelBox.isSelected()) {
                addIcon();
            }
            else if (signalMastBox.isSelected()) {
                addSignalMast();
            }
            else {
                log.warn("No item selected in panel edit mode");
            }
            selectedObject = NULL;
            repaint();
        }
        else if ( (event.isPopupTrigger() || delayedPopupTrigger)  && !isDragging) {
            selectedObject = NULL;
            selectedPointType = NONE;
            whenReleased = event.getWhen();
            checkPopUp(event);
        }
        // check if controlling turnouts
        else if ( ( selectedObject!=NULL) && (selectedPointType==TURNOUT_CENTER) &&
                allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                    (!event.isShiftDown()) && (!event.isControlDown()) ) {
            // controlling layout, in edit mode
            LayoutTurnout t = (LayoutTurnout)selectedObject;
            t.toggleTurnout();
        }
        else if ( ( selectedObject!=NULL) && (selectedPointType==SLIP_CENTER) &&
                allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                    (!event.isShiftDown()) && (!event.isControlDown()) ) {
            // controlling layout, in edit mode
            LayoutSlip t = (LayoutSlip)selectedObject;
            t.toggleState();
        }
        else if ( ( selectedObject!=NULL) && (selectedPointType>=TURNTABLE_RAY_OFFSET) &&
                allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                    (!event.isShiftDown()) && (!event.isControlDown()) ) {
            // controlling layout, in edit mode
            LayoutTurntable t =  (LayoutTurntable)selectedObject;
            t.setPosition(selectedPointType-TURNTABLE_RAY_OFFSET);
        }
        if ( (trackBox.isSelected()) && (beginObject!=NULL) && (foundObject!=NULL) ) {
            // user let up shift key before releasing the mouse when creating a track segment
            setCursor(Cursor.getDefaultCursor());
            beginObject = NULL;
            foundObject = NULL;
            repaint();
        }
        createSelectionGroups();
    }
    // check if controlling turnouts out of edit mode
    else if ( ( selectedObject!=NULL) && (selectedPointType==TURNOUT_CENTER) &&
            allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                (!event.isShiftDown()) && (!delayedPopupTrigger) ) {
        // controlling layout, not in edit mode
        LayoutTurnout t = (LayoutTurnout)selectedObject;
        t.toggleTurnout();
    }
    // check if controlling turnouts out of edit mode
    else if ( ( selectedObject!=NULL) && (selectedPointType==SLIP_CENTER) &&
            allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                (!event.isShiftDown()) && (!delayedPopupTrigger) ) {
        // controlling layout, not in edit mode
        LayoutSlip t = (LayoutSlip)selectedObject;
        t.toggleState();
    }
    else if ( ( selectedObject!=NULL) && (selectedPointType>=TURNTABLE_RAY_OFFSET) &&
            allControlling() && (!event.isMetaDown()) && (!event.isAltDown()) && (!event.isPopupTrigger()) &&
                (!event.isShiftDown()) && (!delayedPopupTrigger) ) {
            LayoutTurntable t =  (LayoutTurntable)selectedObject;
            t.setPosition(selectedPointType-TURNTABLE_RAY_OFFSET);
    }
    // check if requesting marker popup out of edit mode
    else if ( (event.isPopupTrigger() || delayedPopupTrigger) && (!isDragging) ) {
        LocoIcon lo = checkMarkers(dLoc);
        if (lo!=NULL) showPopUp(lo, event);
        else {
            if (checkSelect(dLoc, false)) {
                // show popup menu
                switch (foundPointType) {
                    case TURNOUT_CENTER:
                        ((LayoutTurnout)foundObject).showPopUp(event, isEditable());
                        break;
                    case LEVEL_XING_CENTER:
                        ((LevelXing)foundObject).showPopUp(event, isEditable());
                        break;
                    case SLIP_CENTER:
                        ((LayoutSlip)foundObject).showPopUp(event, isEditable());
                        break;
                    default: break;
                }
            }
            AnalogClock2Display c = checkClocks(dLoc);
            if (c!=NULL){
                showPopUp(c, event);
            } else {
                SignalMastIcon sm = checkSignalMastIcons(dLoc);
                if (sm!=NULL) {
                    showPopUp(sm, event);
                } else {
                    PositionableLabel im = checkLabelImages(dLoc);
                    if(im!=NULL){
                        showPopUp(im, event);
                    }
                }
            }
        }
    }
    if (!event.isPopupTrigger() && !isDragging) {
        List <Positionable> selections = getSelectedItems(event);
        if (selections.size() > 0) {
            selections.get(0).doMouseReleased(event);
            whenReleased = event.getWhen();
        }
    }
    if (selectedObject!=NULL) {
        // An object was selected, deselect it
        prevSelectedObject = selectedObject;
        selectedObject = NULL;
    }
    isDragging = false;
    delayedPopupTrigger = false;
    thisPanel.requestFocusInWindow();
    return;
}

    /*private*/ void LayoutEditor::checkPopUp(MouseEvent* event) {
        if (checkSelect(dLoc, false)) {
            // show popup menu
            switch (foundPointType) {
                case POS_POINT:
                    ((PositionablePoint)foundObject).showPopUp(event);
                    break;
                case TURNOUT_CENTER:
                    ((LayoutTurnout)foundObject).showPopUp(event, isEditable());
                    break;
                case LEVEL_XING_CENTER:
                    ((LevelXing)foundObject).showPopUp(event, isEditable());
                    break;
                case SLIP_CENTER:
                    ((LayoutSlip)foundObject).showPopUp(event, isEditable());
                    break;
                case TURNTABLE_CENTER:
                    ((LayoutTurntable)foundObject).showPopUp(event);
                    break;
                default: break;
            }
            if(foundPointType>=TURNTABLE_RAY_OFFSET){
                LayoutTurntable t = (LayoutTurntable)foundObject;
                if(t.isTurnoutControlled()){
                    ((LayoutTurntable)foundObject).showRayPopUp(event, foundPointType-TURNTABLE_RAY_OFFSET);
                }
            }
        }
        else {
            TrackSegment tr = checkTrackSegments(dLoc);
            if (tr!=NULL) {
                tr.showPopUp(event);
            }
            else {
                SensorIcon s = checkSensorIcons(dLoc);
                if (s!=NULL) {
                    showPopUp(s, event);
                }
                else {
                    LocoIcon lo = checkMarkers(dLoc);
                    if (lo!=NULL) {
                        showPopUp(lo, event);
                    }
                    else {
                        SignalHeadIcon sh = checkSignalHeadIcons(dLoc);
                        if (sh!=NULL) {
                            showPopUp(sh, event);
                        }
                        else {
                            AnalogClock2Display c = checkClocks(dLoc);
                            if (c!=NULL) {
                                showPopUp(c, event);
                            }
                            else {
                                MultiSensorIcon ms = checkMultiSensors(dLoc);
                                if (ms!=NULL) {
                                    showPopUp(ms, event);
                                }
                                else {
                                    PositionableLabel lb = checkLabelImages(dLoc);
                                    if (lb!=NULL) {
                                        showPopUp(lb, event);
                                    }
                                    else {
                                        PositionableLabel b = checkBackgrounds(dLoc);
                                        if (b!=NULL) {
                                            showPopUp(b, event);
                                        }
                                        else {
                                            SignalMastIcon sm = checkSignalMastIcons(dLoc);
                                            if (sm!=NULL) {
                                                showPopUp(sm, event);
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
    /*protected*/ void LayoutEditor::showPopUp(Positionable p, MouseEvent event) {
        if (!((JComponent)p).isVisible()) {
            return;     // component must be showing on the screen to determine its location
        }
        JPopupMenu popup = new JPopupMenu();

        if (p.isEditable()) {
            if(showAlignPopup()){
                setShowAlignmentMenu(popup);
                popup.add(new AbstractAction(rb.getQString("Remove")) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        deleteSelectedItems();
                    }
                }
                );
            } else {
                if (p.doViemMenu()) {
                    popup.add(p.getNameQString());
                    if (p.isPositionable()) {
                        setShowCoordinatesMenu(p, popup);
                    }
                    setDisplayLevelMenu(p, popup);
                    setPositionableMenu(p, popup);
                }

                bool popupSet =false;
                popupSet = p.setRotateOrthogonalMenu(popup);
                popupSet = p.setRotateMenu(popup);
                if (popupSet) {
                    popup.addSeparator();
                    popupSet = false;
                }
                popupSet = p.setEditIconMenu(popup);
                popupSet = p.setTextEditMenu(popup);

                PositionablePopupUtil util = p.getPopupUtility();
                if (util!=NULL) {
                    util.setFixedTextMenu(popup);
                    util.setTextMarginMenu(popup);
                    util.setTextBorderMenu(popup);
                    util.setTextFontMenu(popup);
                    util.setBackgroundMenu(popup);
                    util.setTextJustificationMenu(popup);
                    util.setTextOrientationMenu(popup);
                    popup.addSeparator();
                    util.propertyUtil(popup);
                    util.setAdditionalEditPopUpMenu(popup);
                    popupSet = true;
                }
                if (popupSet) {
                    popup.addSeparator();
                    popupSet = false;
                }
                p.setDisableControlMenu(popup);
                setShowAlignmentMenu(popup);
                // for Positionables with unique settings
                p.showPopUp(popup);
                setShowTooltipMenu(p, popup);

                setRemoveMenu(p, popup);
                if (p.doViemMenu()) {
                    setHiddenMenu(p, popup);
                }
            }
        } else {
            p.showPopUp(popup);
            PositionablePopupUtil util = p.getPopupUtility();
            if(util!=NULL)
                util.setAdditionalViewPopUpMenu(popup);
        }
        popup.show((Component)p, p.getWidth()/2+(int)((getPaintScale()-1.0)*p.getX()),
                    p.getHeight()/2+(int)((getPaintScale()-1.0)*p.getY()));
        /*popup.show((Component)p, event.getX(), event.getY());*/
    }

/*public*/ void LayoutEditor::mouseClicked(MouseEvent* event)
{
 if ( (!event.isMetaDown()) && (!event.isPopupTrigger()) && (!event.isAltDown()) &&
                    (!awaitingIconChange) && (!event.isShiftDown()) && (!event.isControlDown()) )
 {
  calcLocation(event, 0, 0);
  QList <Positionable*> selections = getSelectedItems(event);
  if (selections.size() > 0)
  {
   selections.get(0).doMouseClicked(event);
  }
 }
 else if ( event.isPopupTrigger() && whenReleased != event.getWhen())
 {
  calcLocation(event, 0, 0);
  if (isEditable())
  {
   selectedObject = NULL;
   selectedPointType = NONE;
   checkPopUp(event);
  }
  else
  {
   LocoIcon* lo = checkMarkers(dLoc);
   if (lo!=NULL) showPopUp(lo, event);
  }
 }
 if (event.isControlDown() && !event.isPopupTrigger())
 {
  if (checkSelect(dLoc, false))
  {
   // show popup menu
   switch (foundPointType)
   {
    case POS_POINT:
        amendSelectionGroup((PositionablePoint)foundObject);
        break;
    case TURNOUT_CENTER:
        amendSelectionGroup((LayoutTurnout)foundObject);
        break;
    case LEVEL_XING_CENTER:
        amendSelectionGroup((LevelXing)foundObject);
        break;
    case SLIP_CENTER:
        amendSelectionGroup((LayoutSlip)foundObject);
        break;
    case TURNTABLE_CENTER:
        amendSelectionGroup((LayoutTurntable)foundObject);
        break;
    default: break;
   }
  }
  else
  {

   PositionableLabel* s = checkSensorIcons(dLoc);
   if (s!=NULL)
   {
    amendSelectionGroup(s);
   }
   else
   {
    PositionableLabel* sh = checkSignalHeadIcons(dLoc);
    if (sh!=NULL)
    {
     amendSelectionGroup(sh);
    }
    else
    {
     PositionableLabel* ms = checkMultiSensors(dLoc);
     if (ms!=NULL)
     {
      amendSelectionGroup(ms);
     }
     else
     {
      PositionableLabel* lb = checkLabelImages(dLoc);
      if (lb!=NULL)
      {
       amendSelectionGroup(lb);
      }
      else
      {
       PositionableLabel* b = checkBackgrounds(dLoc);
       if (b!=NULL)
       {
        amendSelectionGroup(b);
       }
       else
       {
        PositionableLabel* sm = checkSignalMastIcons(dLoc);
        if (sm!=NULL)
        {
         amendSelectionGroup(sm);
        }
       }
      }
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
 thisPanel.requestFocusInWindow();
 return;
}


    /*private*/ void LayoutEditor::highLightSelection(Graphics2D* g){
        java.awt.Stroke stroke = g.getStroke();
        Color color = g.getColor();
        g.setColor(new Color(204, 207, 88));
        g.setStroke(new java.awt.BasicStroke(2.0f));
        if (_positionableSelection!=NULL){
            for (int i = 0; i<_positionableSelection.size(); i++) {
                Positionable c = _positionableSelection.get(i);
                g.drawRect(c.getX(), c.getY(), c.maxWidth(), c.maxHeight());
            }
        }
        // loop over all defined turnouts
        if (_turnoutSelection!=NULL){
            for (int i = 0; i<_turnoutSelection.size();i++) {
                LayoutTurnout t = _turnoutSelection.get(i);
                int minx = (int) Math.min(Math.min(t.getCoordsA().getX(), t.getCoordsB().getX()),Math.min(t.getCoordsC().getX(), t.getCoordsD().getX()));
                int miny = (int) Math.min(Math.min(t.getCoordsA().getY(), t.getCoordsB().getY()),Math.min(t.getCoordsC().getY(), t.getCoordsD().getY()));
                int maxx = (int) Math.max(Math.max(t.getCoordsA().getX(), t.getCoordsB().getX()),Math.max(t.getCoordsC().getX(), t.getCoordsD().getX()));
                int maxy = (int) Math.max(Math.max(t.getCoordsA().getY(), t.getCoordsB().getY()),Math.max(t.getCoordsC().getY(), t.getCoordsD().getY()));
                int width = maxx-minx;
                int height = maxy-miny;
                int x = (int) t.getCoordsCenter().getX()-(width/2);
                int y = (int) t.getCoordsCenter().getY()-(height/2);
                g.drawRect(x, y, width, height);
                }
        }
        if (_xingSelection!=NULL){
        // loop over all defined level crossings
            for (int i = 0; i<_xingSelection.size();i++) {
                LevelXing xing = _xingSelection.get(i);
                int minx = (int) Math.min(Math.min(xing.getCoordsA().getX(), xing.getCoordsB().getX()),Math.min(xing.getCoordsC().getX(), xing.getCoordsD().getX()));
                int miny = (int) Math.min(Math.min(xing.getCoordsA().getY(), xing.getCoordsB().getY()),Math.min(xing.getCoordsC().getY(), xing.getCoordsD().getY()));
                int maxx = (int) Math.max(Math.max(xing.getCoordsA().getX(), xing.getCoordsB().getX()),Math.max(xing.getCoordsC().getX(), xing.getCoordsD().getX()));
                int maxy = (int) Math.max(Math.max(xing.getCoordsA().getY(), xing.getCoordsB().getY()),Math.max(xing.getCoordsC().getY(), xing.getCoordsD().getY()));
                int width = maxx-minx;
                int height = maxy-miny;
                int x = (int) xing.getCoordsCenter().getX()-(width/2);
                int y = (int) xing.getCoordsCenter().getY()-(height/2);
                g.drawRect(x, y, width, height);
                }
        }
        if (_slipSelection!=NULL){
        // loop over all defined level crossings
            for (int i = 0; i<_slipSelection.size();i++) {
                LayoutSlip xing = _slipSelection.get(i);
                int minx = (int) Math.min(Math.min(xing.getCoordsA().getX(), xing.getCoordsB().getX()),Math.min(xing.getCoordsC().getX(), xing.getCoordsD().getX()));
                int miny = (int) Math.min(Math.min(xing.getCoordsA().getY(), xing.getCoordsB().getY()),Math.min(xing.getCoordsC().getY(), xing.getCoordsD().getY()));
                int maxx = (int) Math.max(Math.max(xing.getCoordsA().getX(), xing.getCoordsB().getX()),Math.max(xing.getCoordsC().getX(), xing.getCoordsD().getX()));
                int maxy = (int) Math.max(Math.max(xing.getCoordsA().getY(), xing.getCoordsB().getY()),Math.max(xing.getCoordsC().getY(), xing.getCoordsD().getY()));
                int width = maxx-minx;
                int height = maxy-miny;
                int x = (int) xing.getCoordsCenter().getX()-(width/2);
                int y = (int) xing.getCoordsCenter().getY()-(height/2);
                g.drawRect(x, y, width, height);
            }
        }
        // loop over all defined turntables
        if (_turntableSelection!=NULL){
            for (int i = 0; i<_turntableSelection.size();i++) {
                LayoutTurntable tt = _turntableSelection.get(i);
                QPointF center = tt.getCoordsCenter();
                int x = (int) center.getX() - (int)tt.getRadius();
                int y = (int) center.getY() - (int)tt.getRadius();
                g.drawRect(x, y, ((int)tt.getRadius()*2), ((int)tt.getRadius()*2));
            }
        }
        // loop over all defined Anchor Points and End Bumpers
        if (_pointSelection!=NULL){
            for (int i = 0; i<_pointSelection.size();i++) {
                PositionablePoint p = _pointSelection.get(i);
                QPointF coord = p.getCoords();
                g.drawRect((int)coord.getX()-4, (int)coord.getY()-4, 9, 9);
            }
        }
        g.setColor(color);
        g.setStroke(stroke);
    }

    /*private*/ void createSelectionGroups(){
        List <Positionable> contents = getContents();
        Rectangle2D selectRect = new Rectangle2D.Double (selectionX, selectionY,
                                                selectionWidth, selectionHeight);
        for (int i = 0; i<contents.size(); i++) {
            Positionable c = contents.get(i);
            QPointF upperLeft = c.getLocation();
            if (selectRect.contains(upperLeft)) {
                if (_positionableSelection==NULL) _positionableSelection = new QVector<Positionable>();
                if(!_positionableSelection.contains(c))
                    _positionableSelection.add(c);
            }
        }
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            QPointF center = t.getCoordsCenter();
            if (selectRect.contains(center)) {
                if (_turnoutSelection==NULL) _turnoutSelection = new QVector<LayoutTurnout>();
                if(!_turnoutSelection.contains(t))
                    _turnoutSelection.add(t);
            }
        }
        // loop over all defined level crossings
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            QPointF center = x.getCoordsCenter();
            if (selectRect.contains(center)) {
                if (_xingSelection==NULL) _xingSelection = new QVector<LevelXing>();
                if(!_xingSelection.contains(x))
                    _xingSelection.add(x);
            }
        }
        // loop over all defined level crossings
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip x = slipList.get(i);
            QPointF center = x.getCoordsCenter();
            if (selectRect.contains(center)) {
                if (_slipSelection==NULL) _slipSelection = new QVector<LayoutSlip>();
                if(!_slipSelection.contains(x))
                    _slipSelection.add(x);
            }
        }
        // loop over all defined turntables
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            QPointF center = x.getCoordsCenter();
            if (selectRect.contains(center)) {
                if (_turntableSelection==NULL) _turntableSelection = new QVector<LayoutTurntable>();
                if(!_turntableSelection.contains(x))
                    _turntableSelection.add(x);
            }
        }
        // loop over all defined Anchor Points and End Bumpers
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            QPointF coord = p.getCoords();
            if (selectRect.contains(coord)) {
                if (_pointSelection==NULL) _pointSelection = new QVector<PositionablePoint>();
                if(!_pointSelection.contains(p))
                    _pointSelection.add(p);
            }
        }
        repaint();
    }

    /*private*/ void clearSelectionGroups(){
        _pointSelection=NULL;
        _turntableSelection=NULL;
        _xingSelection=NULL;
        _slipSelection=NULL;
        _turnoutSelection=NULL;
        _positionableSelection=NULL;
    }


    /*private*/ void LayoutEditor::deleteSelectedItems() {
        if(!noWarnGlobalDelete){
            int selectedValue = JOptionPane.showOptionDialog(this,
                rb.getQString("Question6"),rb.getQString("WarningTitle"),
                JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return;   // return without creating if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnGlobalDelete = true;
            }
        }
        if(_positionableSelection!=NULL){
            for(Positionable comp: _positionableSelection){
                remove(comp);
            }
        }
        if(_pointSelection!=NULL){
            bool oldPosPoint = noWarnPositionablePoint;
            noWarnPositionablePoint = true;
            for(PositionablePoint point: _pointSelection){
                removePositionablePoint(point);
            }
            noWarnPositionablePoint = oldPosPoint;
        }

        if(_xingSelection!=NULL){
            bool oldLevelXing = noWarnLevelXing;
            noWarnLevelXing = true;
            for(LevelXing point: _xingSelection){
                removeLevelXing(point);
            }
            noWarnLevelXing = oldLevelXing;
        }
        if(_slipSelection!=NULL){
            bool oldSlip = noWarnSlip;
            noWarnSlip = true;
            for(LayoutSlip point: _slipSelection){
                removeLayoutSlip(point);
            }
            noWarnSlip = oldSlip;
        }
        if(_turntableSelection!=NULL){
            bool oldTurntable = noWarnTurntable;
            noWarnTurntable = true;
            for(LayoutTurntable point: _turntableSelection){
                removeTurntable(point);
            }
            noWarnTurntable = oldTurntable;
        }
        if(_turnoutSelection!=NULL){
            bool oldTurnout = noWarnLayoutTurnout;
            noWarnLayoutTurnout = true;
            for(LayoutTurnout point: _turnoutSelection){
                removeLayoutTurnout(point);
            }
            noWarnLayoutTurnout = oldTurnout;
        }
        selectionActive = false;
        clearSelectionGroups();
        repaint();

    }
    /*private*/ void LayoutEditor::amendSelectionGroup(Positionable p){
        if (_positionableSelection==NULL){
            _positionableSelection = new QVector <Positionable>();
        }
        bool removed = false;
        for(int i=0; i<_positionableSelection.size();i++){
            if (_positionableSelection.get(i)==p){
                _positionableSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _positionableSelection.add(p);
        if (_positionableSelection.size()==0){
            _positionableSelection=NULL;
        }
        repaint();
    }

    /*private*/ void LayoutEditor::amendSelectionGroup(LayoutTurnout p){
        if (_turnoutSelection==NULL){
            _turnoutSelection = new QVector <LayoutTurnout>();
        }
        bool removed = false;
        for(int i=0; i<_turnoutSelection.size();i++){
            if (_turnoutSelection.get(i)==p){
                _turnoutSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _turnoutSelection.add(p);
        if (_turnoutSelection.size()==0){
            _turnoutSelection=NULL;
        }
        repaint();
    }

    /*private*/ void LayoutEditor::amendSelectionGroup(PositionablePoint p){
        if (_pointSelection==NULL){
            _pointSelection = new QVector <PositionablePoint>();
        }
        bool removed = false;
        for(int i=0; i<_pointSelection.size();i++){
            if (_pointSelection.get(i)==p){
                _pointSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _pointSelection.add(p);
        if (_pointSelection.size()==0){
            _pointSelection=NULL;
        }
        repaint();
    }

    /*private*/ void LayoutEditor::amendSelectionGroup(LevelXing p){
        if (_xingSelection==NULL){
            _xingSelection = new QVector <LevelXing>();
        }
        bool removed = false;
        for(int i=0; i<_xingSelection.size();i++){
            if (_xingSelection.get(i)==p){
                _xingSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _xingSelection.add(p);
        if (_xingSelection.size()==0){
            _xingSelection=NULL;
        }
        repaint();
    }

    /*private*/ void LayoutEditor::amendSelectionGroup(LayoutSlip p){
        if (_slipSelection==NULL){
            _slipSelection = new QVector <LayoutSlip>();
        }
        bool removed = false;
        for(int i=0; i<_slipSelection.size();i++){
            if (_slipSelection.get(i)==p){
                _slipSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _slipSelection.add(p);
        if (_slipSelection.size()==0){
            _slipSelection=NULL;
        }
        repaint();
    }

    /*private*/ void LayoutEditor::amendSelectionGroup(LayoutTurntable* p){
        if (_turntableSelection==NULL){
            _turntableSelection = new QVector <LayoutTurntable>();
        }
        bool removed = false;
        for(int i=0; i<_turntableSelection.size();i++){
            if (_turntableSelection.get(i)==p){
                _turntableSelection.remove(i);
                removed = true;
                break;
            }
        }
        if(!removed)
            _turntableSelection.add(p);
        if (_turntableSelection.size()==0){
            _turntableSelection=NULL;
        }
        repaint();
    }

    /*public*/ void LayoutEditor::alignSelection(bool alignX){
        int sum = 0;
        int cnt = 0;

        if(_positionableSelection!=NULL){
            for (int i = 0; i<_positionableSelection.size(); i++){
                Positionable comp = _positionableSelection.get(i);
                if (!getFlag(OPTION_POSITION, comp.isPositionable()))  { continue; }
                if (alignX) {
                    sum += comp.getX();
                } else {
                    sum += comp.getY();
                }
                cnt++;
            }
        }

        if(_pointSelection!=NULL){
            for (int i = 0; i<_pointSelection.size(); i++){
                PositionablePoint comp = _pointSelection.get(i);
                if (alignX) {
                    sum += comp.getCoords().getX();
                } else {
                    sum += comp.getCoords().getY();
                }
                cnt++;
            }
        }

        if(_turnoutSelection!=NULL){
            for (int i = 0; i<_turnoutSelection.size(); i++){
                LayoutTurnout comp = _turnoutSelection.get(i);
                if (alignX) {
                    sum += comp.getCoordsCenter().getX();
                } else {
                    sum += comp.getCoordsCenter().getY();
                }
                cnt++;
            }
        }

        if(_xingSelection!=NULL){
            for (int i = 0; i<_xingSelection.size(); i++){
                LevelXing comp = _xingSelection.get(i);
                if (alignX) {
                    sum += comp.getCoordsCenter().getX();
                } else {
                    sum += comp.getCoordsCenter().getY();
                }
                cnt++;
            }
        }
        if(_slipSelection!=NULL){
            for (int i = 0; i<_slipSelection.size(); i++){
                LayoutSlip comp = _slipSelection.get(i);
                if (alignX) {
                    sum += comp.getCoordsCenter().getX();
                } else {
                    sum += comp.getCoordsCenter().getY();
                }
                cnt++;
            }
        }
        if(_turntableSelection!=NULL){
            for (int i = 0; i<_turntableSelection.size(); i++){
                LayoutTurntable comp = _turntableSelection.get(i);
                if (alignX) {
                    sum += comp.getCoordsCenter().getX();
                } else {
                    sum += comp.getCoordsCenter().getY();
                }
                cnt++;
            }
        }

        int ave = Math.round((float)sum/cnt);
        if(_positionableSelection!=NULL){
            for (int i=0; i<_positionableSelection.size(); i++) {
                Positionable comp = _positionableSelection.get(i);
                if (!getFlag(OPTION_POSITION, comp.isPositionable()))  { continue; }
                if (alignX) {
                    comp.setLocation(ave, comp.getY());
                } else {
                    comp.setLocation(comp.getX(), ave);
                }
            }
        }
        if(_pointSelection!=NULL){
            for (int i=0; i<_pointSelection.size(); i++) {
                PositionablePoint comp = _pointSelection.get(i);
                if (alignX) {
                    comp.setCoords(new QPointF.Double(ave, comp.getCoords().getY()));
                } else {
                    comp.setCoords(new QPointF.Double(comp.getCoords().getX(), ave));
                }
            }
        }
        if(_turnoutSelection!=NULL){
            for (int i=0; i<_turnoutSelection.size(); i++) {
                LayoutTurnout comp = _turnoutSelection.get(i);
                if (alignX) {
                    comp.setCoordsCenter(new QPointF.Double(ave, comp.getCoordsCenter().getY()));
                } else {
                    comp.setCoordsCenter(new QPointF.Double(comp.getCoordsCenter().getX(), ave));
                }
            }
        }
        if(_xingSelection!=NULL){
            for (int i=0; i<_xingSelection.size(); i++) {
                LevelXing comp = _xingSelection.get(i);
                if (alignX) {
                    comp.setCoordsCenter(new QPointF.Double(ave, comp.getCoordsCenter().getY()));
                } else {
                    comp.setCoordsCenter(new QPointF.Double(comp.getCoordsCenter().getX(), ave));
                }
            }
        }
        if(_slipSelection!=NULL){
            for (int i=0; i<_slipSelection.size(); i++) {
                LayoutSlip comp = _slipSelection.get(i);
                if (alignX) {
                    comp.setCoordsCenter(new QPointF.Double(ave, comp.getCoordsCenter().getY()));
                } else {
                    comp.setCoordsCenter(new QPointF.Double(comp.getCoordsCenter().getX(), ave));
                }
            }
        }
        if(_turntableSelection!=NULL){
            for (int i=0; i<_turntableSelection.size(); i++) {
                LayoutTurntable comp = _turntableSelection.get(i);
                if (alignX) {
                    comp.setCoordsCenter(new QPointF.Double(ave, comp.getCoordsCenter().getY()));
                } else {
                    comp.setCoordsCenter(new QPointF.Double(comp.getCoordsCenter().getX(), ave));
                }
            }
        }
        repaint();
    }

    /*protected*/ bool showAlignPopup() {
        if (_positionableSelection!=NULL) {
            return true;
        } else if (_pointSelection!=NULL) {
            return true;
        } else if (_turnoutSelection!=NULL){
            return true;
        } else if (_turntableSelection!=NULL){
            return true;
        } else if (_xingSelection!=NULL){
            return true;
        } else if (_slipSelection!=NULL){
            return true;
        }
        return false;
    }

        /**
    * Offer actions to align the selected Positionable items either
    * Horizontally (at avearage y coord) or Vertically (at avearage x coord).
    */
    /*public*/ bool LayoutEditor::setShowAlignmentMenu(JPopupMenu* popup) {
        if (showAlignPopup()) {
            /*JMenu*/QMenu edit = new /*JMenu*/QMenu(rb.getQString("EditAlignment"));
            edit.add(new AbstractAction(rb.getQString("AlignX")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    alignSelection(true);
                }
            });
            edit.add(new AbstractAction(rb.getQString("AlignY")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    alignSelection(false);
                }
            });
            popup.add(edit);
            return true;
        }
        return false;
    }

    /*public*/ void LayoutEditor::keyPressed(KeyEvent e) {
        if(e.getKeyCode()==KeyEvent.VK_DELETE){
            deleteSelectedItems();
            return;
        }
        if (_positionableSelection!=NULL){
            for (int i = 0; i<_positionableSelection.size(); i++) {
                Positionable c = _positionableSelection.get(i);
                int xNew;
                int yNew;
                if ((c instanceof MemoryIcon) && (c.getPopupUtility().getFixedWidth()==0)) {
                    MemoryIcon pm = (MemoryIcon) c;
                    xNew = (int)(returnNewXPostition(e, pm.getOriginalX()));
                    yNew = (int)(returnNewYPostition(e, pm.getOriginalY()));
                } else {
                    QPointF upperLeft = c.getLocation();
                    xNew = (int)(returnNewXPostition(e, upperLeft.getX()));
                    yNew = (int)(returnNewYPostition(e, upperLeft.getY()));
                }
                c.setLocation(xNew,yNew);
            }
        }
        // loop over all defined turnouts
        if (_turnoutSelection!=NULL){
            for (int i = 0; i<_turnoutSelection.size();i++) {
                LayoutTurnout t = _turnoutSelection.get(i);
                QPointF center = t.getCoordsCenter();
                t.setCoordsCenter(new QPointF.Double(returnNewXPostition(e, center.getX()),
                                                                returnNewYPostition(e, center.getY())));
                }
        }
        if (_xingSelection!=NULL){
        // loop over all defined level crossings
            for (int i = 0; i<_xingSelection.size();i++) {
                LevelXing x = _xingSelection.get(i);
                QPointF center = x.getCoordsCenter();
                x.setCoordsCenter(new QPointF.Double(returnNewXPostition(e, center.getX()),
                                                                returnNewYPostition(e, center.getY())));
                }
        }
        if (_slipSelection!=NULL){
        // loop over all defined level crossings
            for (int i = 0; i<_slipSelection.size();i++) {
                LayoutSlip x = _slipSelection.get(i);
                QPointF center = x.getCoordsCenter();
                x.setCoordsCenter(new QPointF.Double(returnNewXPostition(e, center.getX()),
                                                                returnNewYPostition(e, center.getY())));
                }
        }
        // loop over all defined turntables
        if (_turntableSelection!=NULL){
            for (int i = 0; i<_turntableSelection.size();i++) {
                LayoutTurntable x = _turntableSelection.get(i);
                QPointF center = x.getCoordsCenter();
                x.setCoordsCenter(new QPointF.Double(returnNewXPostition(e, center.getX()),
                                                                returnNewYPostition(e, center.getY())));
            }
        }
        // loop over all defined Anchor Points and End Bumpers
        if (_pointSelection!=NULL){
            for (int i = 0; i<_pointSelection.size();i++) {
                PositionablePoint p = _pointSelection.get(i);
                QPointF coord = p.getCoords();
                p.setCoords(new QPointF.Double(returnNewXPostition(e, coord.getX()),
                                                                returnNewYPostition(e, coord.getY())));
            }
        }
        repaint();
    }

    /*private*/ double LayoutEditor::returnNewXPostition(KeyEvent* e, double val){
        if(e.isShiftDown()){
            switch (e.getKeyCode()){
                case KeyEvent.VK_LEFT: val=val-1;
                                    break;
                case KeyEvent.VK_RIGHT: val=val+1;
                                        break;
                default: break;
            }
        } else {
            switch (e.getKeyCode()){
                case KeyEvent.VK_LEFT: val=val-5;
                                    break;
                case KeyEvent.VK_RIGHT: val=val+5;
                                        break;
                default: break;
            }
        }
        if (val<0) val = 0;
        return val;

    }

    /*private*/ double LayoutEditor::returnNewYPostition(KeyEvent* e, double val){
        if(e.isShiftDown()){
            switch (e.getKeyCode()){
                case KeyEvent.VK_UP: val=val-1;
                                    break;
                case KeyEvent.VK_DOWN: val=val+1;
                                    break;
            }
        } else {
            switch (e.getKeyCode()){
                case KeyEvent.VK_UP: val=val-5;
                                    break;
                case KeyEvent.VK_DOWN: val=val+5;
                                    break;
            }
        }
        if (val<0) val = 0;
        return val;

    }

    /*public*/ void LayoutEditor::mouseMoved(MouseEvent event)
    {
        calcLocation(event, 0, 0);
        if (isEditable()) {
            xLabel.setText(Integer.toQString(xLoc));
            yLabel.setText(Integer.toQString(yLoc));
        }
        List <Positionable> selections = getSelectedItems(event);
        Positionable selection = NULL;
        int numSel = selections.size();
        if (numSel > 0) {
            selection = selections.get(0);
        }
        if (selection!=NULL && selection.getDisplayLevel()>BKG && selection.showTooltip()) {
            showToolTip(selection, event);
        } else {
            super.setToolTip(NULL);
        }
        if (numSel != _prevNumSel) {
           repaint();
           _prevNumSel = numSel;
        }
    }

    /*public*/ void LayoutEditor::mouseDragged(MouseEvent* event)
    {
        // initialize mouse position
        calcLocation(event, 0, 0);
        // ignore this event if still at the original point
        if ((!isDragging) && (xLoc==getAnchorX()) && (yLoc==getAnchorY())) return;
        // process this mouse dragged event
        if (isEditable()) {
            xLabel.setText(Integer.toQString(xLoc));
            yLabel.setText(Integer.toQString(yLoc));
        }
        QPointF newPos = new QPointF.Double(dLoc.getX() + startDel.getX(),
                        dLoc.getY() + startDel.getY());
        if ((selectedObject!=NULL) && (event.isMetaDown() || event.isAltDown()) && (selectedPointType==MARKER)) {
            // marker moves regardless of editMode or positionable
            PositionableLabel pl = (PositionableLabel)selectedObject;
            int xint = (int)newPos.getX();
            int yint = (int)newPos.getY();
            // don't allow negative placement, object could become unreachable
            if (xint<0) xint = 0;
            if (yint<0) yint = 0;
            pl.setLocation(xint, yint);
            isDragging = true;
            repaint();
            return;
        }
        if (isEditable()) {
            if ((selectedObject!=NULL) && (event.isMetaDown() || event.isAltDown()) && allPositionable()) {
                // moving a point
                if (snapToGridOnMove) {
                    int xx = (((int)newPos.getX()+4)/10)*10;
                    int yy = (((int)newPos.getY()+4)/10)*10;
                    newPos.setLocation(xx,yy);
                }
                if (_pointSelection!=NULL||_turntableSelection!=NULL||_xingSelection!=NULL||
                            _turnoutSelection!=NULL||_positionableSelection!=NULL){
                    int offsetx = xLoc - _lastX;
                    int offsety = yLoc - _lastY;
                    //We should do a move based upon a selection group.
                    int xNew;
                    int yNew;
                    if (_positionableSelection!=NULL){
                        for (int i = 0; i<_positionableSelection.size(); i++) {
                            Positionable c = _positionableSelection.get(i);
                            if ((c instanceof MemoryIcon) && (c.getPopupUtility().getFixedWidth()==0)) {
                                MemoryIcon pm = (MemoryIcon) c;
                                xNew = (pm.getOriginalX()+offsetx);
                                yNew = (pm.getOriginalY()+offsety);
                            } else {
                                QPointF upperLeft = c.getLocation();
                                xNew = (int)(upperLeft.getX()+offsetx);
                                yNew = (int)(upperLeft.getY()+offsety);
                            }
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            c.setLocation(xNew,yNew);
                        }
                    }

                    if (_turnoutSelection!=NULL){
                        for (int i = 0; i<_turnoutSelection.size();i++) {
                            LayoutTurnout t = _turnoutSelection.get(i);
                            QPointF center = t.getCoordsCenter();
                            xNew = (int) center.getX()+offsetx;
                            yNew = (int) center.getY()+offsety;
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            t.setCoordsCenter(new QPointF.Double(xNew, yNew));
                        }
                    }
                    if (_xingSelection!=NULL){
                    // loop over all defined level crossings
                        for (int i = 0; i<_xingSelection.size();i++) {
                            LevelXing x = _xingSelection.get(i);
                            QPointF center = x.getCoordsCenter();
                            xNew = (int) center.getX()+offsetx;
                            yNew = (int) center.getY()+offsety;
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            x.setCoordsCenter(new QPointF.Double(xNew, yNew));
                        }
                    }
                    if (_slipSelection!=NULL){
                    // loop over all defined level crossings
                        for (int i = 0; i<_slipSelection.size();i++) {
                            LayoutSlip x = _slipSelection.get(i);
                            QPointF center = x.getCoordsCenter();
                            xNew = (int) center.getX()+offsetx;
                            yNew = (int) center.getY()+offsety;
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            x.setCoordsCenter(new QPointF.Double(xNew, yNew));
                        }
                    }
                    // loop over all defined turntables
                    if (_turntableSelection!=NULL){
                        for (int i = 0; i<_turntableSelection.size();i++) {
                            LayoutTurntable x = _turntableSelection.get(i);
                            QPointF center = x.getCoordsCenter();
                            xNew = (int) center.getX()+offsetx;
                            yNew = (int) center.getY()+offsety;
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            x.setCoordsCenter(new QPointF.Double(xNew, yNew));
                        }
                    }
                    // loop over all defined Anchor Points and End Bumpers
                    if (_pointSelection!=NULL){
                        for (int i = 0; i<_pointSelection.size();i++) {
                            PositionablePoint p = _pointSelection.get(i);
                            QPointF coord = p.getCoords();
                            xNew = (int) coord.getX()+offsetx;
                            yNew = (int) coord.getY()+offsety;
                            if (xNew<0) xNew=0;
                            if (yNew<0) yNew=0;
                            p.setCoords(new QPointF.Double(xNew, yNew));
                        }
                    }
                    _lastX = xLoc;
                    _lastY = yLoc;
                } else {
                    switch (selectedPointType) {
                        case POS_POINT:
                            ((PositionablePoint)selectedObject).setCoords(newPos);
                            isDragging = true;
                            break;
                        case TURNOUT_CENTER:
                            ((LayoutTurnout)selectedObject).setCoordsCenter(newPos);
                            isDragging = true;
                            break;
                        case TURNOUT_A:
                            LayoutTurnout o = (LayoutTurnout)selectedObject;
                            o.setCoordsA(newPos);
                            break;
                        case TURNOUT_B:
                            o = (LayoutTurnout)selectedObject;
                            o.setCoordsB(newPos);
                            break;
                        case TURNOUT_C:
                            o = (LayoutTurnout)selectedObject;
                            o.setCoordsC(newPos);
                            break;
                        case TURNOUT_D:
                            o = (LayoutTurnout)selectedObject;
                            o.setCoordsD(newPos);
                            break;
                        case LEVEL_XING_CENTER:
                            ((LevelXing)selectedObject).setCoordsCenter(newPos);
                            isDragging = true;
                            break;
                        case LEVEL_XING_A:
                            LevelXing x = (LevelXing)selectedObject;
                            x.setCoordsA(newPos);
                            break;
                        case LEVEL_XING_B:
                            x = (LevelXing)selectedObject;
                            x.setCoordsB(newPos);
                            break;
                        case LEVEL_XING_C:
                            x = (LevelXing)selectedObject;
                            x.setCoordsC(newPos);
                            break;
                        case LEVEL_XING_D:
                            x = (LevelXing)selectedObject;
                            x.setCoordsD(newPos);
                            break;
                        case SLIP_CENTER:
                            ((LayoutSlip)selectedObject).setCoordsCenter(newPos);
                            isDragging = true;
                            break;
                        case SLIP_A:
                            LayoutSlip sl = (LayoutSlip)selectedObject;
                            sl.setCoordsA(newPos);
                            break;
                        case SLIP_B:
                            sl = (LayoutSlip)selectedObject;
                            sl.setCoordsB(newPos);
                            break;
                        case SLIP_C:
                            sl = (LayoutSlip)selectedObject;
                            sl.setCoordsC(newPos);
                            break;
                        case SLIP_D:
                            sl = (LayoutSlip)selectedObject;
                            sl.setCoordsD(newPos);
                            break;
                        case TURNTABLE_CENTER:
                            ((LayoutTurntable)selectedObject).setCoordsCenter(newPos);
                            isDragging = true;
                            break;
                        case LAYOUT_POS_LABEL:
                            PositionableLabel l = (PositionableLabel)selectedObject;
                            if (l.isPositionable()) {
                                int xint = (int)newPos.getX();
                                int yint = (int)newPos.getY();
                                // don't allow negative placement, object could become unreachable
                                if (xint<0) xint = 0;
                                if (yint<0) yint = 0;
                                l.setLocation(xint, yint);
                                isDragging = true;
                            }
                            break;
                        case LAYOUT_POS_JCOMP:
                            PositionableJComponent c = (PositionableJComponent)selectedObject;
                            if (c.isPositionable()) {
                                int xint = (int)newPos.getX();
                                int yint = (int)newPos.getY();
                                // don't allow negative placement, object could become unreachable
                                if (xint<0) xint = 0;
                                if (yint<0) yint = 0;
                                c.setLocation(xint, yint);
                                isDragging = true;
                            }
                            break;
                        case MULTI_SENSOR:
                            PositionableLabel pl = (PositionableLabel)selectedObject;
                            if (pl.isPositionable()) {
                                int xint = (int)newPos.getX();
                                int yint = (int)newPos.getY();
                                // don't allow negative placement, object could become unreachable
                                if (xint<0) xint = 0;
                                if (yint<0) yint = 0;
                                pl.setLocation(xint, yint);
                                isDragging = true;
                            }
                            break;
                        case TRACK_CIRCLE_CENTRE: TrackSegment t = (TrackSegment)selectedObject;
                                                    reCalculateTrackSegmentAngle(t, newPos.getX(), newPos.getY());
                                                break;
                        default:
                            if (selectedPointType>=TURNTABLE_RAY_OFFSET) {
                                LayoutTurntable turn = (LayoutTurntable)selectedObject;
                                turn.setRayCoordsIndexed(newPos.getX(),newPos.getY(),
                                                selectedPointType-TURNTABLE_RAY_OFFSET);
                            }
                    }
                }
                repaint();
            }
            else if ( (beginObject!=NULL) && event.isShiftDown()
                                            && trackBox.isSelected() ) {
                // dragging from first end of Track Segment
                currentLocation.setLocation(xLoc,yLoc);
                bool needResetCursor = (foundObject!=NULL);
                if (checkSelect(currentLocation, true)) {
                    // have match to free connection point, change cursor
                    setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
                }
                else if (needResetCursor) {
                    setCursor(Cursor.getDefaultCursor());
                }
                repaint();
            }
            else if ( selectionActive && (!event.isShiftDown()) && (!event.isAltDown()) && (!event.isMetaDown()) ) {
                selectionWidth = xLoc - selectionX;
                selectionHeight = yLoc - selectionY;
                repaint();
            }
        } else {
            Rectangle r = new Rectangle(event.getX(), event.getY(), 1, 1);
            (       (JComponent) event->getSource()).scrollRectToVisible(r);
        }
        return;
    }

    //@SuppressWarnings("unused")
    /*private*/ void LayoutEditor::updateLocation(QObject* o,int pointType,QPointF newPos) {
        switch (pointType) {
            case TURNOUT_A:
                ((LayoutTurnout)o).setCoordsA(newPos);
                break;
            case TURNOUT_B:
                ((LayoutTurnout)o).setCoordsB(newPos);
                break;
            case TURNOUT_C:
                ((LayoutTurnout)o).setCoordsC(newPos);
                break;
            case TURNOUT_D:
                ((LayoutTurnout)o).setCoordsD(newPos);
                break;
            case LEVEL_XING_A:
                ((LevelXing)o).setCoordsA(newPos);
                break;
            case LEVEL_XING_B:
                ((LevelXing)o).setCoordsB(newPos);
                break;
            case LEVEL_XING_C:
                ((LevelXing)o).setCoordsC(newPos);
                break;
            case LEVEL_XING_D:
                ((LevelXing)o).setCoordsD(newPos);
                break;
            case SLIP_A:
                ((LayoutSlip)o).setCoordsA(newPos);
                break;
            case SLIP_B:
                ((LayoutSlip)o).setCoordsB(newPos);
                break;
            case SLIP_C:
                ((LayoutSlip)o).setCoordsC(newPos);
                break;
            case SLIP_D:
                ((LayoutSlip)o).setCoordsD(newPos);
                break;
            default:
                if (pointType>=TURNTABLE_RAY_OFFSET) {
                    LayoutTurntable turn = (LayoutTurntable)o;
                    turn.setRayCoordsIndexed(newPos.getX(),newPos.getY(),
                                    pointType-TURNTABLE_RAY_OFFSET);
                }
        }
        setDirty(true);
    }
    /*public*/ void setLoc(int x, int y) {
        if (isEditable()) {
            xLoc = x;
            yLoc = y;
            xLabel.setText(Integer.toQString(xLoc));
            yLabel.setText(Integer.toQString(yLoc));
        }
    }

    /**
     * Add an Anchor point.
     */
    /*public*/ void LayoutEditor::addAnchor() {
        numAnchors ++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "A"+numAnchors;
            if (findPositionablePointByName(name)==NULL) duplicate = false;
            if (duplicate) numAnchors ++;
        }
        // create object
        PositionablePoint o = new PositionablePoint(name,
                            PositionablePoint.ANCHOR, currentPoint, this);
        //if (o!=NULL) {
        pointList.add(o);
        setDirty(true);
        //}
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
        PositionablePoint o = new PositionablePoint(name,
                            PositionablePoint.END_BUMPER, currentPoint, this);
        //if (o!=NULL) {
        pointList.add(o);
        setDirty(true);
        //}
    }

    /**
     * Add a Track Segment
     */
    /*public*/ void LayoutEditor::addTrackSegment() {
        numTrackSegments ++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "T"+numTrackSegments;
            if (findTrackSegmentByName(name)==NULL) duplicate = false;
            if (duplicate) numTrackSegments ++;
        }
        // create object
        newTrack = new TrackSegment(name,beginObject,beginPointType,
                        foundObject,foundPointType,dashedLine.isSelected(), mainlineTrack.isSelected(),this);
        if (newTrack!=NULL) {
            trackList.add(newTrack);
            setDirty(true);
            // link to connected objects
            setLink(newTrack,TRACK,beginObject,beginPointType);
            setLink(newTrack,TRACK,foundObject,foundPointType);
            // check on layout block
            LayoutBlock b = provideLayoutBlock(blockIDField.getText().trim());
            if (b!=NULL) {
                newTrack.setLayoutBlock(b);
                auxTools.setBlockConnectivityChanged();
                // check on occupancy sensor
                QString sensorName = (blockSensor.getText().trim());
                if (sensorName.length()>0) {
                    if (!validateSensor(sensorName,b,this)) {
                        b.setOccupancySensorName("");
                    }
                    else {
                        blockSensor.setText( b.getOccupancySensorName() );
                    }
                }
                newTrack.updateBlockInfo();
            }

        }
        else {
            log.error("Failure to create a new Track Segment");
        }
    }

    /**
     * Add a Level Crossing
     */
    /*public*/ void LayoutEditor::addLevelXing() {
        numLevelXings ++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "X"+numLevelXings;
            if (findLevelXingByName(name)==NULL) duplicate = false;
            if (duplicate) numLevelXings ++;
        }
        // create object
        LevelXing o = new LevelXing(name,currentPoint,this);
        //if (o!=NULL) {
        xingList.add(o);
        setDirty(true);
        // check on layout block
        LayoutBlock b = provideLayoutBlock(blockIDField.getText().trim());
        if (b!=NULL) {
            o.setLayoutBlockAC(b);
            o.setLayoutBlockBD(b);
            // check on occupancy sensor
            QString sensorName = (blockSensor.getText().trim());
            if (sensorName.length()>0) {
                if (!validateSensor(sensorName,b,this)) {
                    b.setOccupancySensorName("");
                }
                else {
                    blockSensor.setText( b.getOccupancySensorName() );
                }
            }
        }
        //}
    }

    /**
     * Add a LayoutSlip
     */
    /*public*/ void LayoutEditor::addLayoutSlip(int type) {
        double rot = 0.0;
        QString s = rotationField.getText().trim();
        if (s.length()<1) {
            rot = 0.0;
        }
        else {
            try {
                rot = Double.parseDouble(s);
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(this, rb.getQString("Error3")+" "+
                        e,rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                return;
            }
        }
        numLayoutSlips ++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "SL"+numLayoutSlips;
            if (findLayoutSlipByName(name)==NULL) duplicate = false;
            if (duplicate) numLayoutSlips ++;
        }
        // create object
        LayoutSlip o = new LayoutSlip(name,currentPoint, rot, this, type);
        slipList.add(o);
        setDirty(true);

        // check on layout block
        LayoutBlock b = provideLayoutBlock(blockIDField.getText().trim());
        if (b!=NULL) {
            o.setLayoutBlock(b);
            // check on occupancy sensor
            QString sensorName = (blockSensor.getText().trim());
            if (sensorName.length()>0) {
                if (!validateSensor(sensorName,b,this)) {
                    b.setOccupancySensorName("");
                }
                else {
                    blockSensor.setText( b.getOccupancySensorName() );
                }
            }
        }
        QString turnoutName = nextTurnout.getText().trim();
        if ( validatePhysicalTurnout(turnoutName, this) ) {
            // turnout is valid and unique.
            o.setTurnout(turnoutName);
            if (o.getTurnout().getSystemName()==(turnoutName.toUpperCase())) {
                nextTurnout.setText(turnoutName.toUpperCase());
            }
        }
        else {
            o.setTurnout("");
            nextTurnout.setText("");
        }
        turnoutName = extraTurnout.getText().trim();
        if ( validatePhysicalTurnout(turnoutName, this) ) {
            // turnout is valid and unique.
            o.setTurnoutB(turnoutName);
            if (o.getTurnoutB().getSystemName()==(turnoutName.toUpperCase())) {
                extraTurnout.setText(turnoutName.toUpperCase());
            }
        }
        else {
            o.setTurnoutB("");
            extraTurnout.setText("");
        }
    }

    /**
     * Add a Layout Turnout
     */
    /*public*/ void LayoutEditor::addLayoutTurnout(int type) {
        // get the rotation entry
        double rot = 0.0;
        QString s = rotationField->getText().trim();
        if (s.length()<1) {
            rot = 0.0;
        }
        else
        {
         try {
                bool bOk = false;
                rot = /*Double.parseDouble(s)*/ s.toDouble(&bOk);
                if(!bOk) throw NumberFormatException();
            }
            catch (NumberFormatException* e) {
                JOptionPane.showMessageDialog(this, tr("Error3")+" "+
                        e,tr("Error"),JOptionPane.ERROR_MESSAGE);
                return;
            }
        }
        numLayoutTurnouts ++;
        // get unique name
        QString name = "";
        bool duplicate = true;
        while (duplicate) {
            name = "TO"+QString("%1").arg(numLayoutTurnouts);
            if (findLayoutTurnoutByName(name)==NULL) duplicate = false;
            if (duplicate) numLayoutTurnouts ++;
        }
        // create object
        LayoutTurnout* o = new LayoutTurnout(name,type,
                                        currentPoint,rot,xScale,yScale,this);
        //if (o!=NULL) {
        turnoutList->append(o);
        setDirty(true);
        // check on layout block
        LayoutBlock* b = provideLayoutBlock(blockIDField->getText().trim());
        if (b!=NULL) {
            o->setLayoutBlock(b);
            // check on occupancy sensor
            QString sensorName = (blockSensor->getText().trim());
            if (sensorName.length()>0) {
                if (!validateSensor(sensorName,b,this)) {
                    b->setOccupancySensorName("");
                }
                else {
                    blockSensor->setText( b->getOccupancySensorName() );
                }
            }
        }
        // set default continuing route Turnout State
        o->setContinuingSense(Turnout::CLOSED);
        // check on a physical turnout
        QString turnoutName = nextTurnout->getText().trim();
        if ( validatePhysicalTurnout(turnoutName, this) ) {
            // turnout is valid and unique.
            o->setTurnout(turnoutName);
            if (o->getTurnout()->getSystemName()==(turnoutName.toUpper())) {
                nextTurnout->setText(turnoutName.toUpperCase());
            }
        }
        else {
            o->setTurnout("");
            nextTurnout->setText("");
        }
        //}
    }

    /**
     * Validates that a physical turnout exists and is unique among Layout Turnouts
     *    Returns true if valid turnout was entered, false otherwise
     */
    /*public*/ bool LayoutEditor::validatePhysicalTurnout(QString turnoutName, Component* openPane) {
        // check if turnout name was entered
        if (turnoutName.length() < 1) {
            // no turnout entered
            return false;
        }
        // ensure that this turnout is unique among Layout Turnouts
        LayoutTurnout* t = NULL;
        for (int i=0;i<turnoutList.size();i++) {
            t = turnoutList->at(i);
            log.debug("LT '"+t->getName()+"', Turnout tested '"+t->getTurnoutName()+"' ");
            Turnout* to = t->getTurnout();
            /*Only check for the second turnout if the type is a double cross over
            otherwise the second turnout is used to throw an additional turnout at
            the same time.*/
            Turnout* to2 = NULL;
            if(t->getTurnoutType()>=LayoutTurnout::DOUBLE_XOVER){
                to2 = t->getSecondTurnout();
            }
            if (to!=NULL) {
                if ( (to->getSystemName()==(turnoutName.toUpper())) ||
                    ((to->getUserName()!=NULL) && (to->getUserName()==(turnoutName))) ) {
                    JOptionPane.showMessageDialog(openPane,
                            java.text.MessageFormat.format(rb.getQString("Error4"),
                            new Object[]{turnoutName}),
                            rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
            if (to2!=NULL){
                if ( (to2->getSystemName()==(turnoutName.toUpper())) ||
                    ((to2->getUserName()!=NULL) && (to2->getUserName()==(turnoutName))) ) {
                    JOptionPane.showMessageDialog(openPane,
                            java.text.MessageFormat.format(rb.getQString("Error4"),
                            new Object[]{turnoutName}),
                            rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
        }
#if 0 // TODO:
        for(LayoutSlip* slip: slipList)
        {
            Turnout* to = slip.getTurnout();
            if(to!=NULL){
                if(to->getSystemName()==(turnoutName) || (to->getUserName()!=NULL && to.getUserName()==(turnoutName))){
                    JOptionPane.showMessageDialog(openPane,
                            java.text.MessageFormat.format(rb.getQString("Error4"),
                            new Object[]{turnoutName}),
                            rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
            to=slip.getTurnoutB();
            if(to!=NULL){
                if(to.getSystemName()==(turnoutName) || (to.getUserName()!=NULL && to.getUserName()==(turnoutName))){
                    JOptionPane.showMessageDialog(openPane,
                            java.text.MessageFormat.format(rb.getQString("Error4"),
                            new Object[]{turnoutName}),
                            rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                    return false;
                }
            }
        }
#endif
        // check that the unique turnout name corresponds to a defined physical turnout
        Turnout* to = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        if (to == NULL) {
            // There is no turnout corresponding to this name
            JOptionPane.showMessageDialog(openPane,
                    java.text.MessageFormat.format(rb.getQString("Error8"),
                    new Object[]{turnoutName}),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return false;
        }
        return true;
    }

    /**
     * Adds a link in the 'to' object to the 'from' object
     */
    /*private*/ void LayoutEditor::setLink(QObject* fromObject,int fromPointType,
                                            QObject* toObject,int toPointType) {
        switch (toPointType) {
            case POS_POINT:
                if (fromPointType==TRACK) {
                    ((PositionablePoint)toObject).setTrackConnection(
                                                    (TrackSegment)fromObject);
                }
                else {
                    log.error("Attempt to set a non-TRACK connection to a Positionable Point");
                }
                break;
            case TURNOUT_A:
                ((LayoutTurnout)toObject).setConnectA(fromObject,fromPointType);
                break;
            case TURNOUT_B:
                ((LayoutTurnout)toObject).setConnectB(fromObject,fromPointType);
                break;
            case TURNOUT_C:
                ((LayoutTurnout)toObject).setConnectC(fromObject,fromPointType);
                break;
            case TURNOUT_D:
                ((LayoutTurnout)toObject).setConnectD(fromObject,fromPointType);
                break;
            case LEVEL_XING_A:
                ((LevelXing)toObject).setConnectA(fromObject,fromPointType);
                break;
            case LEVEL_XING_B:
                ((LevelXing)toObject).setConnectB(fromObject,fromPointType);
                break;
            case LEVEL_XING_C:
                ((LevelXing)toObject).setConnectC(fromObject,fromPointType);
                break;
            case LEVEL_XING_D:
                ((LevelXing)toObject).setConnectD(fromObject,fromPointType);
                break;
            case SLIP_A:
                ((LayoutSlip)toObject).setConnectA(fromObject,fromPointType);
                break;
            case SLIP_B:
                ((LayoutSlip)toObject).setConnectB(fromObject,fromPointType);
                break;
            case SLIP_C:
                ((LayoutSlip)toObject).setConnectC(fromObject,fromPointType);
                break;
            case SLIP_D:
                ((LayoutSlip)toObject).setConnectD(fromObject,fromPointType);
                break;
            case TRACK:
                // should never happen, Track Segment links are set in ctor
                log.error("Illegal request to set a Track Segment link");
                break;
            default:
                if ( (toPointType>=TURNTABLE_RAY_OFFSET) && (fromPointType==TRACK) ) {
                    ((LayoutTurntable)toObject).setRayConnect((TrackSegment)fromObject,
                                            toPointType-TURNTABLE_RAY_OFFSET);
                }
        }
    }

    /**
     * Return a layout block with the entered name, creating a new one if needed.
     *   Note that the entered name becomes the user name of the LayoutBlock, and
     *		a system name is automatically created by LayoutBlockManager if needed.
     */
    /*public*/ LayoutBlock* provideLayoutBlock(QString s) {
        LayoutBlock* blk;
        if (s.length() < 1) {
            if(!autoAssignBlocks){
                // nothing entered
                return NULL;
            } else {
                blk = InstanceManager::layoutBlockManagerInstance().createNewLayoutBlock();
                if (blk == NULL) {
                    log.error("Unable to create a layout block");
                    return NULL;
                }
                // initialize the new block
                blk.initializeLayoutBlock();
                blk.initializeLayoutBlockRouting();
                blk.setBlockTrackColor(defaultTrackColor);
                blk.setBlockOccupiedColor(defaultOccupiedTrackColor);
                blk.setBlockExtraColor(defaultAlternativeTrackColor);
            }
        } else {
            // check if this Layout Block already exists
            blk = InstanceManager.layoutBlockManagerInstance().getByUserName(s);
            if (blk == NULL) {
                blk = InstanceManager.layoutBlockManagerInstance().createNewLayoutBlock(NULL,s);
                if (blk == NULL) {
                    log.error("Failure to create LayoutBlock '"+s+"'.");
                    return NULL;
                }
                else {
                    // initialize the new block
                    blk.initializeLayoutBlock();
                    blk.initializeLayoutBlockRouting();
                    blk.setBlockTrackColor(defaultTrackColor);
                    blk.setBlockOccupiedColor(defaultOccupiedTrackColor);
                    blk.setBlockExtraColor(defaultAlternativeTrackColor);
                }
            }
        }
        // set both new and previously existing block
        blk.addLayoutEditor(this);
        setDirty(true);
        blk.incrementUse();
        return blk;
    }

    /**
     * Validates that the supplied occupancy sensor name corresponds to an existing sensor
     *   and is unique among all blocks.  If valid, returns true and sets the block sensor
     *   name in the block.  Else returns false, and does nothing to the block.
     */
    /*public*/ bool LayoutEditor::validateSensor(QString sensorName, LayoutBlock* blk, Component* openFrame) {
        // check if anything entered
        if (sensorName.length()<1) {
            // no sensor entered
            return false;
        }
        // get a validated sensor corresponding to this name and assigned to block
        Sensor s = blk.validateSensor(sensorName,openFrame);
        if (s==NULL) {
            // There is no sensor corresponding to this name
            return false;
        }
        return true;
    }

    /**
     * Return a layout block with the given name if one exists.
     * Registers this LayoutEditor with the layout block.
     * This method is designed to be used when a panel is loaded. The calling
     *		method must handle whether the use count should be incremented.
     */
    /*public*/ LayoutBlock* LayoutEditor::getLayoutBlock(QString blockID) {
        // check if this Layout Block already exists
        LayoutBlock* blk = InstanceManager::layoutBlockManagerInstance().getByUserName(blockID);
        if (blk==NULL) {
            log.error("LayoutBlock '"+blockID+"' not found when panel loaded");
            return NULL;
        }
        blk.addLayoutEditor(this);
        return blk;
    }

    /**
     * Remove object from all Layout Editor temmporary lists of items not part of track schematic
     */
    /*protected*/ bool LayoutEditor::remove(QObject* s) {
        bool found = false;
        for (int i = 0; i<sensorImage.size();i++) {
            if (s == sensorImage.get(i)) {
                sensorImage.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<sensorList.size();i++) {
            if (s == sensorList.get(i)) {
                sensorList.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<backgroundImage.size();i++) {
            if (s == backgroundImage.get(i)) {
                backgroundImage.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<memoryLabelList.size();i++) {
            if (s == memoryLabelList.get(i)) {
                memoryLabelList.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<signalList.size();i++) {
            if (s == signalList.get(i)) {
                signalList.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<signalMastList.size();i++) {
            if (s == signalMastList.get(i)) {
                signalMastList.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<multiSensors.size();i++) {
            if (s == multiSensors.get(i)) {
                multiSensors.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<clocks.size();i++) {
            if (s == clocks.get(i)) {
                clocks.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<signalMastImage.size();i++) {
            if (s == signalMastImage.get(i)) {
                signalMastImage.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<signalHeadImage.size();i++) {
            if (s == signalHeadImage.get(i)) {
                signalHeadImage.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<signalMastImage.size();i++) {
            if (s == signalMastImage.get(i)) {
                signalMastImage.remove(i);
                found = true;
                break;
            }
        }
        for (int i = 0; i<labelImage.size();i++) {
            if (s == labelImage.get(i)) {
                labelImage.remove(i);
                found = true;
                break;
            }
        }
        super.removeFromContents((Positionable)s);
        if (found) {
            setDirty(true);
            repaint();
        }
        return found;
    }

    /*public*/ bool removeFromContents(Positionable l) {
        return remove(l);
    }

    //bool noWarnPositionablePoint = false;

    /**
     * Remove a PositionablePoint -- an Anchor or an End Bumper.
     */
    /*protected*/ bool LayoutEditor::removePositionablePoint(PositionablePoint o) {
        // First verify with the user that this is really wanted
        if (!noWarnPositionablePoint) {
            int selectedValue = JOptionPane.showOptionDialog(this,
                    rb.getQString("Question2"),rb.getQString("WarningTitle"),
                    JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                    new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                    rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return(false);   // return without creating if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnPositionablePoint = true;
            }
        }
        // remove from selection information
        if (selectedObject==o) selectedObject = NULL;
        if (prevSelectedObject==o) prevSelectedObject = NULL;
        // remove connections if any
        TrackSegment t = o.getConnect1();
        if (t!=NULL) removeTrackSegment(t);
        t = o.getConnect2();
        if (t!=NULL) removeTrackSegment(t);
        // delete from array
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            if (p==o) {
                // found object
                pointList.remove(i);
                setDirty(true);
                repaint();
                return(true);
            }
        }
        return (false);
    }

    //bool noWarnLayoutTurnout = false;

    /**
     * Remove a LayoutTurnout
     */
    /*protected*/ bool LayoutEditor::removeLayoutTurnout(LayoutTurnout o) {
        // First verify with the user that this is really wanted
        if (!noWarnLayoutTurnout) {
            int selectedValue = JOptionPane.showOptionDialog(this,
                    rb.getQString("Question1"),rb.getQString("WarningTitle"),
                    JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                    new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                    rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return(false);   // return without removing if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnLayoutTurnout = true;
            }
        }
        // remove from selection information
        if (selectedObject==o) selectedObject = NULL;
        if (prevSelectedObject==o) prevSelectedObject = NULL;
        // remove connections if any
        TrackSegment t = (TrackSegment)o.getConnectA();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectB();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectC();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectD();
        if (t!=NULL) removeTrackSegment(t);
        // decrement Block use count(s)
        LayoutBlock b = o.getLayoutBlock();
        if (b!=NULL) b.decrementUse();
        if ( (o.getTurnoutType()==LayoutTurnout.DOUBLE_XOVER) ||
                (o.getTurnoutType()==LayoutTurnout.RH_XOVER) ||
                    (o.getTurnoutType()==LayoutTurnout.LH_XOVER) ) {
            LayoutBlock b2 = o.getLayoutBlockB();
            if ( (b2!=NULL) && (b2!=b) ) b2.decrementUse();
            LayoutBlock b3 = o.getLayoutBlockC();
            if ( (b3!=NULL) && (b3!=b) && (b3!=b2) ) b3.decrementUse();
            LayoutBlock b4 = o.getLayoutBlockD();
            if ( (b4!=NULL) && (b4!=b) &&
                        (b4!=b2) && (b4!=b3) ) b4.decrementUse();
        }
        // delete from array
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout lt = turnoutList.get(i);
            if (lt==o) {
                // found object
                turnoutList.remove(i);
                setDirty(true);
                repaint();
                return(true);
            }
        }
        return(false);
    }

    //bool noWarnLevelXing = false;

    /**
     * Remove a Level Crossing
     */
    /*protected*/ bool LayoutEditor::removeLevelXing (LevelXing o) {
        // First verify with the user that this is really wanted
        if (!noWarnLevelXing) {
            int selectedValue = JOptionPane.showOptionDialog(this,
                    rb.getQString("Question3"),rb.getQString("WarningTitle"),
                    JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                    new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                    rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return(false);   // return without creating if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnLevelXing = true;
            }
        }
        // remove from selection information
        if (selectedObject==o) selectedObject = NULL;
        if (prevSelectedObject==o) prevSelectedObject = NULL;
        // remove connections if any
        TrackSegment t = (TrackSegment)o.getConnectA();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectB();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectC();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectD();
        if (t!=NULL) removeTrackSegment(t);
        // decrement block use count if any blocks in use
        LayoutBlock lb = o.getLayoutBlockAC();
        if (lb != NULL) lb.decrementUse();
        LayoutBlock lbx = o.getLayoutBlockBD();
        if (lbx!=NULL && lb!=NULL && lbx!=lb) lb.decrementUse();
        // delete from array
        for (int i = 0; i<xingList.size();i++) {
            LevelXing lx = xingList.get(i);
            if (lx==o) {
                // found object
                xingList.remove(i);
                o.remove();
                setDirty(true);
                repaint();
                return(true);
            }
        }
        return(false);
    }

    //bool noWarnSlip = false;

    /*protected*/ bool LayoutEditor::removeLayoutSlip (LayoutTurnout o) {
        if(!(o instanceof LayoutSlip)){
            return false;
        }
        // First verify with the user that this is really wanted
        if (!noWarnSlip) {
            int selectedValue = JOptionPane.showOptionDialog(this,
                    rb.getQString("Question5"),rb.getQString("WarningTitle"),
                    JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                    new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                    rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return(false);   // return without creating if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnSlip = true;
            }
        }
        // remove from selection information
        if (selectedObject==o) selectedObject = NULL;
        if (prevSelectedObject==o) prevSelectedObject = NULL;
        // remove connections if any
        TrackSegment t = (TrackSegment)o.getConnectA();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectB();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectC();
        if (t!=NULL) removeTrackSegment(t);
        t = (TrackSegment)o.getConnectD();
        if (t!=NULL) removeTrackSegment(t);
        // decrement block use count if any blocks in use
        LayoutBlock lb = o.getLayoutBlock();
        if (lb != NULL) lb.decrementUse();

        // delete from array
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip lx = slipList.get(i);
            if (lx==o) {
                // found object
                slipList.remove(i);
                o.remove();
                setDirty(true);
                repaint();
                return(true);
            }
        }
        return(false);
    }

    //bool noWarnTurntable = false;

    /**
     * Remove a Layout Turntable
     */
    /*protected*/ bool LayoutEditor::removeTurntable (LayoutTurntable* o) {
        // First verify with the user that this is really wanted
        if (!noWarnTurntable) {
            int selectedValue = JOptionPane.showOptionDialog(this,
                    rb.getQString("Question4"),rb.getQString("WarningTitle"),
                    JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
                    new Object[]{rb.getQString("ButtonYes"),rb.getQString("ButtonNo"),
                    rb.getQString("ButtonYesPlus")},rb.getQString("ButtonNo"));
            if (selectedValue == 1) return(false);   // return without creating if "No" response
            if (selectedValue == 2) {
                // Suppress future warnings, and continue
                noWarnTurntable = true;
            }
        }
        // remove from selection information
        if (selectedObject==o) selectedObject = NULL;
        if (prevSelectedObject==o) prevSelectedObject = NULL;
        // remove connections if any
        for (int j = 0; j<o.getNumberRays();j++) {
            TrackSegment t = o.getRayConnectOrdered(j);
            if (t!=NULL) removeTrackSegment(t);
        }
        // delete from array
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable lx = turntableList.get(i);
            if (lx==o) {
                // found object
                turntableList.remove(i);
                o.remove();
                setDirty(true);
                repaint();
                return(true);
            }
        }
        return(false);
    }

    /**
     * Remove a Track Segment
     */
    /*protected*/ void LayoutEditor::removeTrackSegment(TrackSegment o) {
        // save affected blocks
        LayoutBlock block1 = NULL;
        LayoutBlock block2 = NULL;
        LayoutBlock block = o.getLayoutBlock();
        // remove any connections
        int type = o.getType1();
        if (type==POS_POINT) {
            PositionablePoint p = (PositionablePoint)(o.getConnect1());
            if (p!=NULL) {
                p.removeTrackConnection(o);
                if (p.getConnect1()!=NULL)
                    block1 = p.getConnect1().getLayoutBlock();
                else if (p.getConnect2()!=NULL)
                    block1 = p.getConnect2().getLayoutBlock();
            }
        }
        else {
            block1 = getAffectedBlock(o.getConnect1(),type);
            disconnect(o.getConnect1(),type);
        }
        type = o.getType2();
        if (type==POS_POINT) {
            PositionablePoint p = (PositionablePoint)(o.getConnect2());
            if (p!=NULL) {
                p.removeTrackConnection(o);
                if (p.getConnect1()!=NULL)
                    block2 = p.getConnect1().getLayoutBlock();
                else if (p.getConnect2()!=NULL)
                    block2 = p.getConnect2().getLayoutBlock();
            }
        }
        else {
            block2 = getAffectedBlock(o.getConnect2(),type);
            disconnect(o.getConnect2(),type);
        }
        // delete from array
        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            if (t==o) {
                // found object
                trackList.remove(i);
            }
        }
        // update affected blocks
        if (block!=NULL) {
            // decrement Block use count
            block.decrementUse();
            auxTools.setBlockConnectivityChanged();
            block.updatePaths();
        }
        if ( (block1!=NULL) && (block1!=block) ) block1.updatePaths();
        if ( (block2!=NULL) && (block2!=block) && (block2!=block1) ) block2.updatePaths();
        //
        setDirty(true);
        repaint();
    }

    /*private*/ void LayoutEditor::disconnect(Object o, int type) {
        if (o==NULL) return;
        switch (type) {
            case TURNOUT_A:
                ((LayoutTurnout)o).setConnectA(NULL,NONE);
                break;
            case TURNOUT_B:
                ((LayoutTurnout)o).setConnectB(NULL,NONE);
                break;
            case TURNOUT_C:
                ((LayoutTurnout)o).setConnectC(NULL,NONE);
                break;
            case TURNOUT_D:
                ((LayoutTurnout)o).setConnectD(NULL,NONE);
                break;
            case LEVEL_XING_A:
                ((LevelXing)o).setConnectA(NULL,NONE);
                break;
            case LEVEL_XING_B:
                ((LevelXing)o).setConnectB(NULL,NONE);
                break;
            case LEVEL_XING_C:
                ((LevelXing)o).setConnectC(NULL,NONE);
                break;
            case LEVEL_XING_D:
                ((LevelXing)o).setConnectD(NULL,NONE);
                break;
            case SLIP_A:
                ((LayoutSlip)o).setConnectA(NULL,NONE);
                break;
            case SLIP_B:
                ((LayoutSlip)o).setConnectB(NULL,NONE);
                break;
            case SLIP_C:
                ((LayoutSlip)o).setConnectC(NULL,NONE);
                break;
            case SLIP_D:
                ((LayoutSlip)o).setConnectD(NULL,NONE);
                break;
            default:
                if (type>=TURNTABLE_RAY_OFFSET) {
                    ((LayoutTurntable)o).setRayConnect(NULL,type-TURNTABLE_RAY_OFFSET);
                }
        }
    }

    /*public*/ LayoutBlock LayoutEditor::getAffectedBlock(Object o, int type) {
        if (o==NULL) return NULL;
        switch (type) {
            case TURNOUT_A:
                return ((LayoutTurnout)o).getLayoutBlock();
            case TURNOUT_B:
                return ((LayoutTurnout)o).getLayoutBlockB();
            case TURNOUT_C:
                return ((LayoutTurnout)o).getLayoutBlockC();
            case TURNOUT_D:
                return ((LayoutTurnout)o).getLayoutBlockD();
            case LEVEL_XING_A:
                return ((LevelXing)o).getLayoutBlockAC();
            case LEVEL_XING_B:
                return ((LevelXing)o).getLayoutBlockBD();
            case LEVEL_XING_C:
                return ((LevelXing)o).getLayoutBlockAC();
            case LEVEL_XING_D:
                return ((LevelXing)o).getLayoutBlockBD();
            case SLIP_A:
                return ((LayoutSlip)o).getLayoutBlock();
            case SLIP_B:
                return ((LayoutSlip)o).getLayoutBlock();
            case SLIP_C:
                return ((LayoutSlip)o).getLayoutBlock();
            case SLIP_D:
                return ((LayoutSlip)o).getLayoutBlock();
            case TRACK:
                return ((TrackSegment)o).getLayoutBlock();
        }
        return NULL;
    }

    /**
     * Add a sensor indicator to the Draw Panel
     */
    void LayoutEditor::addSensor() {
        if ((nextSensor.getText()).trim().length()<=0) {
            JOptionPane.showMessageDialog(this,rb.getQString("Error10"),
                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        SensorIcon l = new SensorIcon(new NamedIcon("resources/icons/smallschematics/tracksegments/circuit-error.gif",
                                                    "resources/icons/smallschematics/tracksegments/circuit-error.gif"),this);
//        l.setActiveIcon(sensorIconEditor.getIcon(0));
//        l.setInactiveIcon(sensorIconEditor.getIcon(1));
//        l.setInconsistentIcon(sensorIconEditor.getIcon(2));
//        l.setUnknownIcon(sensorIconEditor.getIcon(3));
        l.setIcon("SensorStateActive", sensorIconEditor.getIcon(0));
        l.setIcon("SensorStateInactive", sensorIconEditor.getIcon(1));
        l.setIcon("BeanStateInconsistent", sensorIconEditor.getIcon(2));
        l.setIcon("BeanStateUnknown", sensorIconEditor.getIcon(3));
        l.setSensor(nextSensor.getText().trim());
        l.setDisplayLevel(SENSORS);
        //Sensor xSensor = l.getSensor();
        if (l.getSensor() != NULL) {
            if ( (l.getNamedSensor().getName()==NULL) ||
                    (!(l.getNamedSensor().getName()==(nextSensor.getText().trim()))) )
                nextSensor.setText(l.getNamedSensor().getName());
        }
        nextSensor.setText(l.getNamedSensor().getName());
        setNextLocation(l);
        setDirty(true);
        putItem(l);
    }

    /*public*/ void putSensor(SensorIcon l){
        putItem(l);
        l.updateSize();
        l.setDisplayLevel(SENSORS);
    }

    /**
     * Add a signal head to the Panel
     */
    void LayoutEditor::addSignalHead() {
        // check for valid signal head entry
        QString tName = nextSignalHead.getText().trim();
        SignalHead mHead = NULL;
        if ( (tName!=NULL) && (!tName==("")) ) {
            mHead = InstanceManager.signalHeadManagerInstance().getSignalHead(tName);
            /*if (mHead == NULL)
                mHead = InstanceManager.signalHeadManagerInstance().getByUserName(tName);
            else */
            nextSignalHead.setText(tName);
        }
        if (mHead == NULL) {
            // There is no signal head corresponding to this name
            JOptionPane.showMessageDialog(thisPanel,
                    java.text.MessageFormat.format(rb.getQString("Error9"),
                    new Object[]{tName}),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        // create and set up signal icon
        SignalHeadIcon* l = new SignalHeadIcon(this);
        l.setSignalHead(tName);
        l.setIcon(rbean.getQString("SignalHeadStateRed"), signalIconEditor.getIcon(0));
        l.setIcon(rbean.getQString("SignalHeadStateFlashingRed"), signalIconEditor.getIcon(1));
        l.setIcon(rbean.getQString("SignalHeadStateYellow"), signalIconEditor.getIcon(2));
        l.setIcon(rbean.getQString("SignalHeadStateFlashingYellow"), signalIconEditor.getIcon(3));
        l.setIcon(rbean.getQString("SignalHeadStateGreen"), signalIconEditor.getIcon(4));
        l.setIcon(rbean.getQString("SignalHeadStateFlashingGreen"), signalIconEditor.getIcon(5));
        l.setIcon(rbean.getQString("SignalHeadStateDark"), signalIconEditor.getIcon(6));
        l.setIcon(rbean.getQString("SignalHeadStateHeld"), signalIconEditor.getIcon(7));
        l.setIcon(rbean.getQString("SignalHeadStateLunar"), signalIconEditor.getIcon(8));
        l.setIcon(rbean.getQString("SignalHeadStateFlashingLunar"), signalIconEditor.getIcon(9));
        setNextLocation(l);
        setDirty(true);
        putSignal(l);
    }
    /*public*/ void LayoutEditor::putSignal(SignalHeadIcon* l) {
        putItem(l);
        l.updateSize();
        l.setDisplayLevel(SIGNALS);
    }

    SignalHead* getSignalHead(QString name) {
        SignalHead sh = InstanceManager.signalHeadManagerInstance().getBySystemName(name);
        if (sh == NULL) sh = InstanceManager.signalHeadManagerInstance().getByUserName(name);
        if (sh == NULL) log.warn("did not find a SignalHead named "+name);
        return sh;
    }

    void LayoutEditor::addSignalMast() {
        // check for valid signal head entry
        QString tName = nextSignalMast.getText().trim();
        SignalMast mMast = NULL;
        if ( (tName!=NULL) && (!tName==("")) ) {
            mMast = InstanceManager::signalMastManagerInstance().getSignalMast(tName);
            nextSignalMast.setText(tName);
        }
        if (mMast == NULL) {
            // There is no signal head corresponding to this name
            JOptionPane.showMessageDialog(thisPanel,
                    java.text.MessageFormat.format(rb.getQString("Error9"),
                    new Object[]{tName}),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        // create and set up signal icon
        SignalMastIcon l = new SignalMastIcon(this);
        l.setSignalMast(tName);
        setNextLocation(l);
        setDirty(true);
        putSignalMast(l);
    }

    /*public*/ void LayoutEditor::putSignalMast(SignalMastIcon l) {
        putItem(l);
        l.updateSize();
        l.setDisplayLevel(SIGNALS);
    }

    SignalMast* LayoutEditor::getSignalMast(QString name) {
        SignalMast sh = InstanceManager.signalMastManagerInstance().getBySystemName(name);
        if (sh == NULL) sh = InstanceManager.signalMastManagerInstance().getByUserName(name);
        if (sh == NULL) log.warn("did not find a SignalMast named "+name);
        return sh;
    }

    /**
     * Add a label to the Draw Panel
     */
    void LayoutEditor::addLabel() {
        PositionableLabel l = super.addLabel(textLabel.getText().trim());
        setDirty(true);
        l.setForeground(defaultTextColor);
    }

    /*public*/ void LayoutEditor::putItem(Positionable l) {
        super.putItem(l);
        if (l instanceof SensorIcon) {
            sensorImage.add((SensorIcon)l);
            sensorList.add((SensorIcon)l);
        } else if (l instanceof LocoIcon) {
            markerImage.add((LocoIcon)l);
        } else if (l instanceof SignalHeadIcon) {
            signalHeadImage.add((SignalHeadIcon)l);
            signalList.add((SignalHeadIcon)l);
        }  else if (l instanceof SignalMastIcon) {
            signalMastImage.add((SignalMastIcon)l);
            signalMastList.add((SignalMastIcon)l);
        } else if (l instanceof MemoryIcon) {
            memoryLabelList.add((MemoryIcon)l);
        } else if (l instanceof AnalogClock2Display) {
            clocks.add((AnalogClock2Display)l);
        } else if (l instanceof MultiSensorIcon) {
            multiSensors.add((MultiSensorIcon)l);
        } if (l instanceof PositionableLabel) {
            if ( !(((PositionableLabel)l).isBackground()) ) {
                labelImage.add((PositionableLabel)l);
            } else {
                backgroundImage.add((PositionableLabel)l);
            }
        }
    }

     /**
     * Add a memory label to the Draw Panel
     */
    void LayoutEditor::addMemory() {
        if ((textMemory.getText()).trim().length()<=0) {
            JOptionPane.showMessageDialog(this, rb.getQString("Error11"),
                        rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        MemoryIcon l = new MemoryIcon("   ", this);
        l.setMemory(textMemory.getText().trim());
        Memory xMemory = l.getMemory();
        if (xMemory != NULL) {
            if ( (xMemory.getUserName() == NULL) ||
                    (!(xMemory.getUserName()==(textMemory.getText().trim())))  ) {
                // put the system name in the memory field
                textMemory.setText(xMemory.getSystemName());
            }
        }
        setNextLocation(l);
        l.setSize(l.getPreferredSize().width, l.getPreferredSize().height);
        l.setDisplayLevel(LABELS);
        l.setForeground(defaultTextColor);
        setDirty(true);
        putItem(l);
    }

    /**
     * Add a Reporter Icon to the panel
     */
    void LayoutEditor::addReporter(QString textReporter,int xx,int yy) {
        ReporterIcon l = new ReporterIcon(this);
        l.setReporter(textReporter);
        l.setLocation(xx,yy);
        l.setSize(l.getPreferredSize().width, l.getPreferredSize().height);
        l.setDisplayLevel(LABELS);
        setDirty(true);
        putItem(l);
   }

    /**
     * Add an icon to the target
     */
    void LayoutEditor::addIcon() {
        PositionableLabel l = new PositionableLabel(iconEditor.getIcon(0), this);
        setNextLocation(l);
        l.setDisplayLevel(ICONS);
        setDirty(true);
        putItem(l);
        l.updateSize();
    }

    /**
     * Add a loco marker to the target
     */
    /*public*/ LocoIcon* LayoutEditor::addLocoIcon (QString name){
        LocoIcon l = new LocoIcon(this);
        QPointF pt = windowCenter();
        l.setLocation( (int)pt.getX(), (int)pt.getY() );
        putLocoIcon(l, name);
        l.setPositionable(true);
        return l;
     }

    /*public*/ void putLocoIcon(LocoIcon l, QString name) {
        super.putLocoIcon(l, name);
        markerImage.add(l);
    }

    JFileChooser inputFileChooser;

    /**
     * Add a background image
     */
    /*public*/ void LayoutEditor::addBackground() {
        if (inputFileChooser == NULL) {
            inputFileChooser = new JFileChooser(System.getProperty("user.dir")+java.io.File.separator+"resources"+java.io.File.separator+"icons");
            jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Graphics Files");
            filt.addExtension("gif");
            filt.addExtension("jpg");
            inputFileChooser.setFileFilter(filt);
        }
        inputFileChooser.rescanCurrentDirectory();

        int retVal = inputFileChooser.showOpenDialog(this);
        if (retVal != JFileChooser.APPROVE_OPTION) return;  // give up if no file selected
//        NamedIcon icon = new NamedIcon(inputFileChooser.getSelectedFile().getPath(),
//                                       inputFileChooser.getSelectedFile().getPath());

        QString name = inputFileChooser.getSelectedFile().getPath();

        // convert to portable path
        name = jmri.util.FileUtil.getPortableFilename(name);

        // setup icon
        backgroundImage.add(super.setUpBackground(name));
    }

    /**
     * Remove a background image from the list of background images
     */
    /*protected*/ void LayoutEditor::removeBackground(PositionableLabel b) {
        for (int i=0; i<backgroundImage.size(); i++) {
            if (b == backgroundImage.get(i)) {
                backgroundImage.remove(i);
                setDirty(true);
                return;
            }
        }
    }

    /**
     * Invoke a window to allow you to add a MultiSensor indicator to the target
     */
    void LayoutEditor::startMultiSensor() {
        multiLocX = xLoc;
        multiLocY = yLoc;
        if (multiSensorFrame == NULL) {
            // create a common edit frame
            multiSensorFrame = new MultiSensorIconFrame(this);
            multiSensorFrame.initComponents();
            multiSensorFrame.pack();
        }
        multiSensorFrame.setVisible(true);
    }
    // Invoked when window has new multi-sensor ready
    /*public*/ void LayoutEditor::addMultiSensor(MultiSensorIcon l) {
        l.setLocation(multiLocX,multiLocY);
        setDirty(true);
        putItem(l);
        multiSensorFrame = NULL;
    }

    /**
     * Set object location and size for icon and label object as it is created.
     * Size comes from the preferredSize; location comes
     * from the fields where the user can spec it.
     */
    /*protected*/ void LayoutEditor::setNextLocation(Positionable* obj) {
        obj.setLocation(xLoc,yLoc);
    }

    /*public*/ ConnectivityUtil getConnectivityUtil() {
        if (conTools == NULL) {
            conTools = new ConnectivityUtil(thisPanel);
        }
        if (conTools==NULL) log.error("Unable to establish link to Connectivity Tools for Layout Editor panel "+layoutName);
        return conTools;
    }
    /*public*/ LayoutEditorTools getLETools() {
        if (tools == NULL) {
            tools = new LayoutEditorTools(thisPanel);
        }
        if (tools==NULL) log.error("Unable to establish link to Layout Editor Tools for Layout Editor panel "+layoutName);
        return tools;
    }

    /**
     * Invoked by DeletePanel menu item
     *     Validate user intent before deleting
     */
    /*public*/ bool LayoutEditor::deletePanel() {
        // verify deletion
        if (!super.deletePanel()) return false;   // return without deleting if "No" response

        turnoutList.clear();
        trackList.clear();
        pointList.clear();
        xingList.clear();
        slipList.clear();
        turntableList.clear();
        return true;
    }

    /**
     *  Control whether target panel items are editable.
     *  Does this by invoke the {@link Editor#setAllEditable} function of
     *  the parent class. This also controls the relevant pop-up menu items
     *  (which are the primary way that items are edited).
     * @param editable true for editable.
     */
    /*public*/ void LayoutEditor::setAllEditable(bool editable) {
        int restoreScroll = _scrollState;
        super.setAllEditable(editable);
        topEditBar.setVisible(editable);
        setShowHidden(editable);
        if (editable) {
            setScroll(SCROLL_BOTH);
            _scrollState = restoreScroll;
            helpBar.setVisible(showHelpBar);
        } else {
            setScroll(_scrollState);
            helpBar.setVisible(false);
        }
        awaitingIconChange = false;
        editModeItem.setSelected(editable);
        repaint();
    }

    /**
     *  Control whether panel items are positionable.
     *  Markers are always positionable.
     * @param state true for positionable.
     */
    /*public*/ void LayoutEditor::setAllPositionable(bool state) {
        super.setAllPositionable(state);
        for (int i = 0; i<markerImage.size(); i++) {
            ((Positionable)markerImage.get(i)).setPositionable(true);
        }
    }


    /**
     *  Control whether target panel items are controlling layout items.
     *  Does this by invoke the {@link Positionable#setControlling} function of
     *  each item on the target panel. This also controls the relevant pop-up menu items.
     * @param state true for controlling.
     */
    /*public*/ void LayoutEditor::setTurnoutAnimation(bool state) {
        if (animationItem.isSelected()!=state) animationItem.setSelected(state);
        animatingLayout = state;
        repaint();
    }

    /*public*/ bool LayoutEditor::isAnimating() {
        return animatingLayout;
    }
    /*public*/ int LayoutEditor::getLayoutWidth() {return panelWidth;}
    /*public*/ int LayoutEditor::getLayoutHeight() {return panelHeight;}
    /*public*/ int LayoutEditor::getWindowWidth() {return windowWidth;}
    /*public*/ int LayoutEditor::getWindowHeight() {return windowHeight;}
    /*public*/ int LayoutEditor::getUpperLeftX() {return upperLeftX;}
    /*public*/ int LayoutEditor::getUpperLeftY() {return upperLeftY;}
    /*public*/ bool LayoutEditor::getScroll() {
        // deprecated but kept to allow opening files
        // on version 2.5.1 and earlier
        if (_scrollState==SCROLL_NONE) return false;
        else return true;
    }
    /*public*/ int LayoutEditor::getMainlineTrackWidth() {
        int wid = (int)mainlineTrackWidth;
        return wid;
    }
    /*public*/ int LayoutEditor::getSideTrackWidth() {
        int wid = (int)sideTrackWidth;
        return wid;
    }
    /*public*/ double LayoutEditor::getXScale() {return xScale;}
    /*public*/ double LayoutEditor::getYScale() {return yScale;}
    /*public*/ QString LayoutEditor::getDefaultTrackColor() {return colorToString(defaultTrackColor);}
    /*public*/ QString LayoutEditor::getDefaultOccupiedTrackColor() {return colorToString(defaultOccupiedTrackColor);}
    /*public*/ QString LayoutEditor::getDefaultAlternativeTrackColor() {return colorToString(defaultAlternativeTrackColor);}
    /*public*/ QString LayoutEditor::getDefaultTextColor() {return colorToString(defaultTextColor);}
    /*public*/ QString LayoutEditor::getTurnoutCircleColor() {return colorToQString(turnoutCircleColor);}
    /*public*/ int LayoutEditor::getTurnoutCircleSize() {return turnoutCircleSize;}
    /*public*/ bool LayoutEditor::getTurnoutDrawUnselectedLeg() {return turnoutDrawUnselectedLeg;}
    /*public*/ QString getLayoutName() {return layoutName;}
    /*public*/ bool LayoutEditor::getShowHelpBar() {return showHelpBar;}
    /*public*/ bool LayoutEditor::getDrawGrid() {return drawGrid;}
    /*public*/ bool LayoutEditor::getSnapOnAdd() {return snapToGridOnAdd;}
    /*public*/ bool LayoutEditor::getSnapOnMove() {return snapToGridOnMove;}
    /*public*/ bool LayoutEditor::getAntialiasingOn() {return antialiasingOn;}
    /*public*/ bool LayoutEditor::getTurnoutCircles() {return turnoutCirclesWithoutEditMode;}
    /*public*/ bool LayoutEditor::getTooltipsNotEdit() {return tooltipsWithoutEditMode;}
    /*public*/ bool LayoutEditor::getTooltipsInEdit() {return tooltipsInEditMode;}
    /*public*/ bool LayoutEditor::getAutoBlockAssignment() { return autoAssignBlocks;}
    /*public*/ void LayoutEditor::setLayoutDimensions(int windowW, int windowH, int x, int y, int panelW, int panelH) {
        upperLeftX = x;
        upperLeftY = y;
        windowWidth = windowW;
        windowHeight = windowH;
        panelWidth = panelW;
        panelHeight = panelH;
        setTargetPanelSize(panelWidth,panelHeight);
        setLocation(upperLeftX,upperLeftY);
        setSize(windowWidth,windowHeight);
        log.debug("setLayoutDimensions Position - "+upperLeftX+","+upperLeftY+" windowSize - "+windowWidth+","+windowHeight+" panelSize - "+panelWidth+","+panelHeight);
    }
    /*public*/ void LayoutEditor::setMainlineTrackWidth(int w) {mainlineTrackWidth = w;}
    /*public*/ void LayoutEditor::setSideTrackWidth(int w) {sideTrackWidth = w;}
    /*public*/ void LayoutEditor::setDefaultTrackColor(QString color) {
        defaultTrackColor = stringToColor(color);
        setOptionMenuTrackColor();
    }
    /*public*/ void LayoutEditor::setDefaultOccupiedTrackColor(QString color) {
        defaultOccupiedTrackColor = stringToColor(color);
        setOptionMenuTrackColor();
    }
    /*public*/ void LayoutEditor::setDefaultAlternativeTrackColor(QString color) {
        defaultAlternativeTrackColor = stringToColor(color);
        setOptionMenuTrackColor();
    }
    /*public*/ void LayoutEditor::setTurnoutCircleColor(QString color) {
        turnoutCircleColor = stringToColor(color);
        setOptionMenuTurnoutCircleColor();
    }
    /*public*/ void LayoutEditor::setTurnoutCircleSize(int size) {
        turnoutCircleSize = size;
        setOptionMenuTurnoutCircleSize();
    }
    /*public*/ void LayoutEditor::setTurnoutDrawUnselectedLeg(bool state) {
        if (turnoutDrawUnselectedLeg != state) {
            turnoutDrawUnselectedLeg = state;
            turnoutDrawUnselectedLegItem.setSelected(turnoutDrawUnselectedLeg);
        }
    }
    /*public*/ void LayoutEditor::setDefaultTextColor(QString color) {
        defaultTextColor = stringToColor(color);
        setOptionMenuTextColor();
    }
    /*public*/ void LayoutEditor::setDefaultBackgroundColor(QString color) {
        defaultBackgroundColor = stringToColor(color);
        setOptionMenuBackgroundColor();
    }
    /*public*/ void LayoutEditor::setXScale(double xSc) {xScale = xSc;}
    /*public*/ void LayoutEditor::setYScale(double ySc) {yScale = ySc;}
    /*public*/ void LayoutEditor::setLayoutName(QString name) {layoutName = name;}
    /*public*/ void LayoutEditor::setShowHelpBar(bool state) {
        if (showHelpBar!=state) {
            showHelpBar = state;
            showHelpItem.setSelected(showHelpBar);
            if (isEditable()) {
                helpBar.setVisible(showHelpBar);
            }
        }
    }
    /*public*/ void LayoutEditor::setDrawGrid(bool state) {
        if (drawGrid != state) {
            drawGrid = state;
            showGridItem.setSelected(drawGrid);
        }
    }
    /*public*/ void LayoutEditor::setSnapOnAdd(bool state) {
        if (snapToGridOnAdd != state) {
            snapToGridOnAdd = state;
            snapToGridOnAddItem.setSelected(snapToGridOnAdd);
        }
    }
    /*public*/ void LayoutEditor::setSnapOnMove(bool state) {
        if (snapToGridOnMove != state) {
            snapToGridOnMove = state;
            snapToGridOnMoveItem.setSelected(snapToGridOnMove);
        }
    }
    /*public*/ void LayoutEditor::setAntialiasingOn(bool state) {
        if (antialiasingOn != state) {
            antialiasingOn = state;
            antialiasingOnItem.setSelected(antialiasingOn);
        }
    }
    /*public*/ void LayoutEditor::setTurnoutCircles(bool state) {
        if (turnoutCirclesWithoutEditMode != state) {
            turnoutCirclesWithoutEditMode = state;
            turnoutCirclesOnItem.setSelected(turnoutCirclesWithoutEditMode);
        }
    }

    /*public*/ void LayoutEditor::setAutoBlockAssignment(bool boo){
        if(autoAssignBlocks != boo){
            autoAssignBlocks = boo;
            autoAssignBlocksItem.setSelected(autoAssignBlocks);
        }
    }
    /*public*/ void LayoutEditor::setTooltipsNotEdit(bool state) {
        if (tooltipsWithoutEditMode != state) {
            tooltipsWithoutEditMode = state;
            setTooltipSubMenu();
        }
    }
    /*public*/ void LayoutEditor::setTooltipsInEdit(bool state) {
        if (tooltipsInEditMode != state) {
            tooltipsInEditMode = state;
            setTooltipSubMenu();
        }
    }
    /*private*/ void LayoutEditor::setTooltipSubMenu() {
        tooltipNone.setSelected((!tooltipsInEditMode) && (!tooltipsWithoutEditMode));
        tooltipAlways.setSelected((tooltipsInEditMode) && (tooltipsWithoutEditMode));
        tooltipInEdit.setSelected((tooltipsInEditMode) && (!tooltipsWithoutEditMode));
        tooltipNotInEdit.setSelected((!tooltipsInEditMode) && (tooltipsWithoutEditMode));
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

    // final initialization routine for loading a LayoutEditor
    /*public*/ void LayoutEditor::setConnections() {
        // initialize TrackSegments if any
        if (trackList.size()>0) {
            for (int i = 0; i<trackList.size(); i++) {
                (trackList.get(i)).setObjects(this);
            }
        }
        // initialize PositionablePoints if any
        if (pointList.size()>0) {
            for (int i = 0; i<pointList.size(); i++) {
                (pointList.get(i)).setObjects(this);
            }
        }
        // initialize LevelXings if any
        if (xingList.size()>0) {
            for (int i = 0; i<xingList.size(); i++) {
                (xingList.get(i)).setObjects(this);
            }
        }
        // initialize LevelXings if any
        if (slipList.size()>0) {
            for (LayoutSlip l : slipList) {
                l.setObjects(this);
            }
        }
        // initialize LayoutTurntables if any
        if (turntableList.size()>0) {
            for (int i = 0; i<turntableList.size(); i++) {
                (turntableList.get(i)).setObjects(this);
            }
        }
        // initialize LayoutTurnouts if any
        if (turnoutList.size()>0) {
            for (int i = 0; i<turnoutList.size(); i++) {
                (turnoutList.get(i)).setObjects(this);
            }
        }
        auxTools.initializeBlockConnectivity();
        log.debug("Initializing Block Connectivity for "+layoutName);
        // reset the panel changed bit
        resetDirty();
    }

    // utility routines
    /*public*/ static QString LayoutEditor::colorToQString(QColor color) {
        if (color == NULL) return "track";
        else if (color==(Color.black)) return "black";
        else if (color==(Color.darkGray)) return "darkGray";
        else if (color==(Color.gray)) return "gray";
        else if (color==(Color.lightGray)) return "lightGray";
        else if (color==(Color.white)) return "white";
        else if (color==(Color.red)) return "red";
        else if (color==(Color.pink)) return "pink";
        else if (color==(Color.orange)) return "orange";
        else if (color==(Color.yellow)) return "yellow";
        else if (color==(Color.green)) return "green";
        else if (color==(Color.blue)) return "blue";
        else if (color==(Color.magenta)) return "magenta";
        else if (color==(Color.cyan)) return "cyan";
        log.error ("unknown color sent to colorToQString");
        return "black";
    }
    /*public*/ static QColor LayoutEditor::stringToColor(QString string) {
        if(string==("black")) return Color.black;
        else if (string==("darkGray")) return Color.darkGray;
        else if (string==("gray")) return Color.gray;
        else if (string==("lightGray")) return Color.lightGray;
        else if (string==("white")) return Color.white;
        else if (string==("red")) return Color.red;
        else if (string==("pink")) return Color.pink;
        else if (string==("orange")) return Color.orange;
        else if (string==("yellow")) return Color.yellow;
        else if (string==("green")) return Color.green;
        else if (string==("blue")) return Color.blue;
        else if (string==("magenta")) return Color.magenta;
        else if (string==("cyan")) return Color.cyan;
        else if (string==("track")) return NULL;
        log.error("unknown color text '"+string+"' sent to stringToColor");
        return Color.black;
    }
    /*public*/ TrackSegment* LayoutEditor::findTrackSegmentByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<trackList.size(); i++) {
            TrackSegment t = trackList.get(i);
            if (t.getID()==(name)) {
                return t;
            }
        }
        return NULL;
    }
    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList.get(i);
            if (p->getID()==(name)) {
                return p;
            }
        }
        return NULL;
    }
    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointAtTrackSegments(TrackSegment tr1, TrackSegment tr2) {
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList.get(i);
            if ( ( (p->getConnect1()==tr1) && (p.getConnect2()==tr2) ) ||
                    ( (p->getConnect1()==tr2) && (p.getConnect2()==tr1) ) ) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByEastBoundSignal(QString signalName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList->at(i);
            if (p->getEastBoundSignal()==(signalName))
                return p;
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSignal(QString signalName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList->at(i);
            if (p->getWestBoundSignal()==(signalName))
                return p;
        }
        return NULL;
    }

    /*public*/ PositionablePoint LayoutEditor::findPositionablePointByEastBoundSignalMast(QString signalMastName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList->at(i);
            if (p.getEastBoundSignalMast()==(signalMastName))
                return p;
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSignalMast(QString signalMastName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList->at(i);
            if (p->getWestBoundSignalMast()==(signalMastName))
                return p;

        }
        return NULL;
    }

    /*public*/ LayoutTurnout LayoutEditor::findLayoutTurnoutBySignalMast(QString signalMastName){
        for(int i = 0; i<turnoutList.size(); i++){
            LayoutTurnout* t = turnoutList->at(i);
            if((t->getSignalAMast()==(signalMastName)) ||
                (t->getSignalBMast()==(signalMastName)) ||
                (t->getSignalCMast()==(signalMastName)) ||
                (t->getSignalDMast()==(signalMastName)))
                return t;
        }
        return NULL;
    }

    /*public*/ LayoutTurnout LayoutEditor::findLayoutTurnoutBySensor(QString sensorName){
        for(int i = 0; i<turnoutList.size(); i++){
            LayoutTurnout* t = turnoutList->at(i);
            if((t->getSensorA()==(sensorName)) ||
                (t->getSensorB()==(sensorName)) ||
                (t->getSensorC()==(sensorName)) ||
                (t->getSensorD()==(sensorName)))
                return t;
        }
        return NULL;
    }

    /*public*/ LevelXing LayoutEditor::findLevelXingBySignalMast(QString signalMastName){
        for(int i = 0; i<xingList.size(); i++){
            LevelXing* l = xingList.at(i);
            if((l->getSignalAMastName()==(signalMastName)) ||
                (l->getSignalBMastName()==(signalMastName)) ||
                (l->getSignalCMastName()==(signalMastName)) ||
                (l->getSignalDMastName()==(signalMastName)))
                return l;
        }
        return NULL;
    }

    /*public*/ LevelXing LayoutEditor::findLevelXingBySensor(QString sensorName){
        for(int i = 0; i<xingList.size(); i++){
            LevelXing* l = xingList.get(i);
            if((l->getSensorAName()==(sensorName)) ||
                (l->getSensorBName()==(sensorName)) ||
                (l.getSensorCName()==(sensorName)) ||
                (l.getSensorDName()==(sensorName)))
                return l;
        }
        return NULL;
    }

//    /*public*/ LayoutSlip LayoutEditor::findLayoutSlipBySignalMast(QString signalMastName){
//        for(LayoutSlip l: slipList){
//            if((l.getSignalAMast()==(signalMastName)) ||
//                (l.getSignalBMast()==(signalMastName)) ||
//                (l.getSignalCMast()==(signalMastName)) ||
//                (l.getSignalDMast()==(signalMastName)))
//                return l;
//        }
//        return NULL;
//    }

//    /*public*/ LayoutSlip* LayoutEditor::findLayoutSlipBySensor(QString sensorName){
//        for(LayoutSlip l: slipList){
//            if((l.getSensorA()==(sensorName)) ||
//                (l.getSensorB()==(sensorName)) ||
//                (l.getSensorC()==(sensorName)) ||
//                (l.getSensorD()==(sensorName)))
//                return l;
//        }
//        return NULL;
//    }

    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByEastBoundSensor(QString sensorName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint* p = pointList.get(i);
            if (p->getEastBoundSensor()==sensorName))
                return p;
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditor::findPositionablePointByWestBoundSensor(QString sensorName){
        for (int i = 0; i<pointList.size(); i++) {
            PositionablePoint p = pointList.get(i);
            if (p.getWestBoundSensor()==(sensorName))
                return p;

        }
        return NULL;
    }

    /*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<turnoutList.size(); i++) {
            LayoutTurnout* t = turnoutList->get(i);
            if (t->getName()==(name)) {
                return t;
            }
        }
        return NULL;
    }

    /*public*/ LayoutTurnout* LayoutEditor::findLayoutTurnoutByTurnoutName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<turnoutList.size(); i++) {
            LayoutTurnout* t = turnoutList->get(i);
            if (t->getTurnoutName()==(name)) {
                return t;
            }
        }
        return NULL;
    }
    /*public*/ LevelXing* LayoutEditor::findLevelXingByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<xingList.size(); i++) {
            LevelXing* x = xingList.get(i);
            if (x->getID()==(name)) {
                return x;
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip findLayoutSlipByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<slipList.size(); i++) {
            LayoutSlip x = slipList.get(i);
            if (x.getName()==(name)) {
                return x;
            }
        }
        return NULL;
    }

    /*public*/ LayoutTurntable findLayoutTurntableByName(QString name) {
        if (name.length()<=0) return NULL;
        for (int i = 0; i<turntableList.size(); i++) {
            LayoutTurntable x = turntableList.get(i);
            if (x.getID()==(name)) {
                return x;
            }
        }
        return NULL;
    }
    /*public*/ Object findObjectByTypeAndName(int type,QString name) {
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
        }
        log.error("did not find Object '"+name+"' of type "+type);
        return NULL;
    }

    /**
     *  Special internal class to allow drawing of layout to a JLayeredPane
     *  This is the 'target' pane where the layout is displayed
     */
    /*protected*/ void paintTargetPanel(Graphics g) {
        Graphics2D g2 = (Graphics2D)g;
        //drawPositionableLabelBorder(g2);
        // Optional antialising, to eliminate (reduce) staircase on diagonal lines
        if(antialiasingOn) g2.setRenderingHints(antialiasing);
        if (isEditable() && drawGrid) drawPanelGrid(g2);
        g2.setColor(defaultTrackColor);
        main = false;
        g2.setStroke(new BasicStroke(sideTrackWidth,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
        drawHiddenTrack(g2);
        drawDashedTrack(g2,false);
        drawDashedTrack(g2,true);
        drawSolidTrack(g2,false);
        drawSolidTrack(g2,true);
        drawTurnouts(g2);
        drawXings(g2);
        drawSlips(g2);
        drawTurntables(g2);
        drawTrackInProgress(g2);
        g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
        drawPoints(g2);

        if (isEditable()) {
            drawTurnoutRects(g2);
            drawXingRects(g2);
            drawSlipRects(g2);
            drawTrackOvals(g2);
            drawSelectionRect(g2);
            drawTurntableRects(g2);
            drawMemoryRects(g2);
            drawTrackCircleCentre(g2);
            highLightSelection(g2);
        }
        else if (turnoutCirclesWithoutEditMode) {
            drawTurnoutCircles(g2);
        }
    }

    bool main = true;
    float trackWidth = sideTrackWidth;

    /*protected*/ void setTrackStrokeWidth(Graphics2D g2, bool need) {
        if (main == need) return;
        main = need;
        // change track stroke width
        if ( main ) {
            trackWidth = mainlineTrackWidth;
            g2.setStroke(new BasicStroke(mainlineTrackWidth,BasicStroke.CAP_BUTT,
                                                            BasicStroke.JOIN_ROUND));
        }
        else {
            trackWidth = sideTrackWidth;
            g2.setStroke(new BasicStroke(sideTrackWidth,BasicStroke.CAP_BUTT,
                                                            BasicStroke.JOIN_ROUND));
        }
    }

    /*protected*/ void drawTurnouts(Graphics2D g2)
    {
        //float trackWidth = sideTrackWidth;
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            LayoutBlock b = t.getLayoutBlock();
            if (b!=NULL) {
                g2.setColor(b.getBlockColor());
            }
            else {
                g2.setColor(defaultTrackColor);
            }
            if(!(t.getHidden() && !isEditable())){
            if (t.getTurnoutType()==LayoutTurnout.DOUBLE_XOVER) {
                //  double crossover turnout
                Turnout t1 = t.getTurnout();
                if (t1==NULL) {
                    // no physical turnout linked - draw A corner
                    setTrackStrokeWidth(g2,t.isMainlineA());
                    g2.draw(new Line2D.Double(t.getCoordsA(),
                                        midpoint(t.getCoordsA(),t.getCoordsB())));
                    setTrackStrokeWidth(g2,false);
                    g2.draw(new Line2D.Double(t.getCoordsA(),
                                        midpoint(t.getCoordsA(),t.getCoordsC())));
                    // change block if needed
                    b = t.getLayoutBlockB();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw B corner
                    setTrackStrokeWidth(g2,t.isMainlineB());
                    g2.draw(new Line2D.Double(t.getCoordsB(),
                                        midpoint(t.getCoordsA(),t.getCoordsB())));
                    setTrackStrokeWidth(g2,false);
                    g2.draw(new Line2D.Double(t.getCoordsB(),
                                        midpoint(t.getCoordsB(),t.getCoordsD())));
                    // change block if needed
                    b = t.getLayoutBlockC();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw C corner
                    setTrackStrokeWidth(g2,t.isMainlineC());
                    g2.draw(new Line2D.Double(t.getCoordsC(),
                                        midpoint(t.getCoordsC(),t.getCoordsD())));
                    setTrackStrokeWidth(g2,false);
                    g2.draw(new Line2D.Double(t.getCoordsC(),
                                        midpoint(t.getCoordsA(),t.getCoordsC())));
                    // change block if needed
                    b = t.getLayoutBlockD();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw D corner
                    setTrackStrokeWidth(g2,t.isMainlineD());
                    g2.draw(new Line2D.Double(t.getCoordsD(),
                                        midpoint(t.getCoordsC(),t.getCoordsD())));
                    setTrackStrokeWidth(g2,false);
                    g2.draw(new Line2D.Double(t.getCoordsD(),
                                        midpoint(t.getCoordsB(),t.getCoordsD())));
                }
                else {
                    int state = Turnout.CLOSED;
                    if (animatingLayout)
                        state = t1.getKnownState();
                    if ( state == Turnout.CLOSED ) {
                        // continuing path - not crossed over
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                third(t.getCoordsA(),t.getCoordsC())));

                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                third(t.getCoordsB(),t.getCoordsD())));

                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                third(t.getCoordsC(),t.getCoordsA())));

                        b = t.getLayoutBlockD();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                third(t.getCoordsD(),t.getCoordsB())));
                    }
                    else if (state == Turnout.THROWN) {
                        // diverting (crossed) path
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                third(t.getCoordsA(),t.getCoordsB())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));

                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                third(t.getCoordsB(),t.getCoordsA())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockColor());

                        g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));

                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                third(t.getCoordsC(),t.getCoordsD())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));

                        b = t.getLayoutBlockD();

                        if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                third(t.getCoordsD(),t.getCoordsC())));
                        setTrackStrokeWidth(g2,false);
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        g2.draw(new Line2D.Double(t.getCoordsD(),t.getCoordsCenter()));
                    }
                    else {
                        // unknown or inconsistent
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                third(t.getCoordsA(),t.getCoordsB())));
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                third(t.getCoordsA(),t.getCoordsC())));
                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                third(t.getCoordsB(),t.getCoordsA())));
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                third(t.getCoordsB(),t.getCoordsD())));
                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                third(t.getCoordsC(),t.getCoordsD())));
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                third(t.getCoordsC(),t.getCoordsA())));
                        b = t.getLayoutBlockD();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                third(t.getCoordsD(),t.getCoordsC())));
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                third(t.getCoordsD(),t.getCoordsB())));
                    }
                }
            }
            else if ( (t.getTurnoutType()==LayoutTurnout.RH_XOVER) ||
                            (t.getTurnoutType()==LayoutTurnout.LH_XOVER) ) {
                //  LH and RH crossover turnouts
                int ttype = t.getTurnoutType();
                Turnout t1 = t.getTurnout();
                if (t1==NULL) {
                    // no physical turnout linked - draw A corner
                    setTrackStrokeWidth(g2,t.isMainlineA());
                    g2.draw(new Line2D.Double(t.getCoordsA(),
                                        midpoint(t.getCoordsA(),t.getCoordsB())));
                    if (ttype == LayoutTurnout.RH_XOVER) {
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),
                                                                t.getCoordsCenter()));
                    }
                    // change block if needed
                    b = t.getLayoutBlockB();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw B corner
                    setTrackStrokeWidth(g2,t.isMainlineB());
                    g2.draw(new Line2D.Double(t.getCoordsB(),
                                        midpoint(t.getCoordsA(),t.getCoordsB())));
                    if (ttype == LayoutTurnout.LH_XOVER) {
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),
                                                                t.getCoordsCenter()));
                    }
                    // change block if needed
                    b = t.getLayoutBlockC();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw C corner
                    setTrackStrokeWidth(g2,t.isMainlineC());
                    g2.draw(new Line2D.Double(t.getCoordsC(),
                                        midpoint(t.getCoordsC(),t.getCoordsD())));
                    if (ttype == LayoutTurnout.RH_XOVER) {
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()),
                                                                t.getCoordsCenter()));
                    }
                    // change block if needed
                    b = t.getLayoutBlockD();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                    // draw D corner
                    setTrackStrokeWidth(g2,t.isMainlineD());
                    g2.draw(new Line2D.Double(t.getCoordsD(),
                                        midpoint(t.getCoordsC(),t.getCoordsD())));
                    if (ttype == LayoutTurnout.LH_XOVER) {
                        setTrackStrokeWidth(g2,false);
                        g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()),
                                                                t.getCoordsCenter()));
                    }
                }
                else {
                    int state = Turnout.CLOSED;
                    if (animatingLayout)
                        state = t1.getKnownState();
                    if ( state == Turnout.CLOSED ) {
                        // continuing path - not crossed over
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        g2.draw(new Line2D.Double(t.getCoordsA(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            setTrackStrokeWidth(g2,false);
                            if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
                        }
                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        g2.draw(new Line2D.Double(t.getCoordsB(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            setTrackStrokeWidth(g2,false);
                            if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
                        }
                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        g2.draw(new Line2D.Double(t.getCoordsC(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            setTrackStrokeWidth(g2,false);
                            if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
                        }
                        b = t.getLayoutBlockD();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        g2.draw(new Line2D.Double(t.getCoordsD(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            setTrackStrokeWidth(g2,false);
                            if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
                        }
                    }
                    else if (state == Turnout.THROWN) {
                        // diverting (crossed) path
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsA(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),
                                                                t.getCoordsCenter()));
                        }
                        else if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsA(),
                                                fourth(t.getCoordsA(),t.getCoordsB())));
                        }
                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsB(),
                                                midpoint(t.getCoordsB(),t.getCoordsA())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),
                                                                t.getCoordsCenter()));
                        }
                        else if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsB(),
                                                fourth(t.getCoordsB(),t.getCoordsA())));
                        }
                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsC(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()),
                                                                t.getCoordsCenter()));
                        }
                        else if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsC(),
                                                fourth(t.getCoordsC(),t.getCoordsD())));
                        }
                        b = t.getLayoutBlockD();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsD(),
                                                midpoint(t.getCoordsD(),t.getCoordsC())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()),
                                                                t.getCoordsCenter()));
                        }
                        else if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsD(),
                                                fourth(t.getCoordsD(),t.getCoordsC())));
                        }
                    }
                    else {
                        // unknown or inconsistent
                        setTrackStrokeWidth(g2,t.isMainlineA());
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsA(),
                                                midpoint(t.getCoordsA(),t.getCoordsB())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
                        }
                        else if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsA(),
                                                fourth(t.getCoordsA(),t.getCoordsB())));
                        }
                        b = t.getLayoutBlockB();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineB());
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsB(),
                                                midpoint(t.getCoordsB(),t.getCoordsA())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
                        }
                        else if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsB(),
                                                fourth(t.getCoordsB(),t.getCoordsA())));
                        }
                        b = t.getLayoutBlockC();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineC());
                        if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsC(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
                        }
                        else if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsC(),
                                                fourth(t.getCoordsC(),t.getCoordsD())));
                        }
                        b = t.getLayoutBlockD();
                        if (b!=NULL) g2.setColor(b.getBlockColor());
                        else g2.setColor(defaultTrackColor);
                        setTrackStrokeWidth(g2,t.isMainlineD());
                        if (ttype == LayoutTurnout.LH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsD(),
                                                midpoint(t.getCoordsC(),t.getCoordsD())));
                            setTrackStrokeWidth(g2,false);
                            g2.draw(new Line2D.Double(t.getCoordsCenter(),
                                    third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
                        }
                        else if (ttype == LayoutTurnout.RH_XOVER) {
                            g2.draw(new Line2D.Double(t.getCoordsD(),
                                                fourth(t.getCoordsD(),t.getCoordsC())));
                        }
                    }
                }
            }
            else {
                // LH, RH, or WYE Turnouts
                Turnout t2 = t.getTurnout();
                if (t2==NULL) {
                    // no physical turnout linked - draw connected
                    setTrackStrokeWidth(g2,t.isMainlineA());
                    g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
                    setTrackStrokeWidth(g2,t.isMainlineB());
                    g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
                    setTrackStrokeWidth(g2,t.isMainlineC());
                    g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
                }
                else {
                    setTrackStrokeWidth(g2,t.isMainlineA());
                    //line from throat to center
                    g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
                    int state = Turnout.CLOSED;
                    if (animatingLayout)
                        state = t2.getKnownState();
                    switch (state) {
                        case Turnout.CLOSED:
                            if (t.getContinuingSense()==Turnout.CLOSED) {
                                setTrackStrokeWidth(g2,t.isMainlineB());
                                //line from continuing leg to center
                                g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
                                if (turnoutDrawUnselectedLeg) {
                                    //line from diverging leg halfway to center
                                    setTrackStrokeWidth(g2,t.isMainlineC());
                                    if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                                    g2.draw(new Line2D.Double(t.getCoordsC(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsC())));
                                }
                            }
                            else {
                                setTrackStrokeWidth(g2,t.isMainlineC());
                                //line from diverging leg to center
                                g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
                                if (turnoutDrawUnselectedLeg) {
                                    //line from continuing leg halfway to center
                                    setTrackStrokeWidth(g2,t.isMainlineB());
                                    if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                                    g2.draw(new Line2D.Double(t.getCoordsB(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsB())));
                                }
                            }
                            break;
                        case Turnout.THROWN:
                            if (t.getContinuingSense()==Turnout.THROWN) {
                                setTrackStrokeWidth(g2,t.isMainlineB());
                                g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
                                if (turnoutDrawUnselectedLeg) {
                                    setTrackStrokeWidth(g2,t.isMainlineC());
                                    if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                                    g2.draw(new Line2D.Double(t.getCoordsC(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsC())));
                                }
                            }
                            else {
                                setTrackStrokeWidth(g2,t.isMainlineC());
                                g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
                                if (turnoutDrawUnselectedLeg) {
                                    setTrackStrokeWidth(g2,t.isMainlineB());
                                    if (b!=NULL) g2.setColor(b.getBlockTrackColor());
                                    g2.draw(new Line2D.Double(t.getCoordsB(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsB())));
                                }
                            }
                            break;
                        default:
                            // inconsistent or unknown
                            setTrackStrokeWidth(g2,t.isMainlineC());
                            g2.draw(new Line2D.Double(t.getCoordsC(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsC())));
                            setTrackStrokeWidth(g2,t.isMainlineB());
                            g2.draw(new Line2D.Double(t.getCoordsB(),
                                            midpoint(t.getCoordsCenter(),t.getCoordsB())));
                    }
                }
            }
            }
        }
    }

    /*private*/ QPointF midpoint (QPointF p1,QPointF p2) {
        return new QPointF.Double((p1.getX()+p2.getX())/2.0,(p1.getY()+p2.getY())/2.0);
    }

    /*protected*/ QPointF third (QPointF p1,QPointF p2) {
        return new QPointF.Double( p1.getX()+((p2.getX()-p1.getX())/3.0),
                        p1.getY()+((p2.getY()-p1.getY())/3.0) );
    }

    /*private*/ QPointF fourth (QPointF p1,QPointF p2) {
        return new QPointF.Double( p1.getX()+((p2.getX()-p1.getX())/4.0),
                        p1.getY()+((p2.getY()-p1.getY())/4.0) );
    }

    /*private*/ void drawXings(Graphics2D g2)
    {
        // loop over all defined level crossings
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            if ( x.isMainlineBD() && (!x.isMainlineAC()) ) {
                drawXingAC(g2,x);
                drawXingBD(g2,x);
            }
            else {
                drawXingBD(g2,x);
                drawXingAC(g2,x);
            }
        }
    }
    /*private*/ void drawXingAC(Graphics2D g2,LevelXing x) {
        // set color - check for an AC block
        LayoutBlock b = x.getLayoutBlockAC();
        if (b!=NULL) {
            g2.setColor(b.getBlockColor());
        }
        else {
            g2.setColor(defaultTrackColor);
        }
        // set track width for AC block
        setTrackStrokeWidth(g2,x.isMainlineAC());
        // draw AC segment
        g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
    }
    /*private*/ void drawXingBD(Graphics2D g2,LevelXing x) {
        // set color - check for an BD block
        LayoutBlock b = x.getLayoutBlockBD();
        if (b!=NULL) {
            g2.setColor(b.getBlockColor());
        }
        else {
            g2.setColor(defaultTrackColor);
        }
        // set track width for BD block
        setTrackStrokeWidth(g2,x.isMainlineBD());
        // draw BD segment
        g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
    }

    /*private*/ void drawSlips(Graphics2D g2) {
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip x = slipList.get(i);
            LayoutBlock b = x.getLayoutBlock();
            setTrackStrokeWidth(g2,x.isMainline());
            Color mainColour;
            Color subColour;
            if (b!=NULL) {
                mainColour = b.getBlockColor();
                subColour = b.getBlockTrackColor();
            }
            else {
                mainColour = defaultTrackColor;
                subColour = defaultTrackColor;
            }

            g2.setColor(subColour);

            g2.draw(new Line2D.Double(x.getCoordsA(),
                third(x.getCoordsA(),x.getCoordsC())));
            g2.draw(new Line2D.Double(x.getCoordsC(),
                third(x.getCoordsC(),x.getCoordsA())));

            g2.draw(new Line2D.Double(x.getCoordsB(),
                third(x.getCoordsB(),x.getCoordsD())));
            g2.draw(new Line2D.Double(x.getCoordsD(),
                third(x.getCoordsD(),x.getCoordsB())));

            if(x.getSlipType()==LayoutSlip.DOUBLE_SLIP){
                if (x.getSlipState()==LayoutSlip.STATE_AC){
                    g2.draw(new Line2D.Double(x.getCoordsA(),
                    third(x.getCoordsA(),x.getCoordsD())));

                    g2.draw(new Line2D.Double(x.getCoordsD(),
                        third(x.getCoordsD(),x.getCoordsA())));

                    g2.draw(new Line2D.Double(x.getCoordsB(),
                        third(x.getCoordsB(),x.getCoordsC())));

                    g2.draw(new Line2D.Double(x.getCoordsC(),
                        third(x.getCoordsC(),x.getCoordsB())));

                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));

                } else if (x.getSlipState()==LayoutSlip.STATE_BD){
                    g2.draw(new Line2D.Double(x.getCoordsB(),
                        third(x.getCoordsB(),x.getCoordsC())));

                    g2.draw(new Line2D.Double(x.getCoordsC(),
                        third(x.getCoordsC(),x.getCoordsB())));

                    g2.draw(new Line2D.Double(x.getCoordsA(),
                    third(x.getCoordsA(),x.getCoordsD())));
                    g2.draw(new Line2D.Double(x.getCoordsD(),
                        third(x.getCoordsD(),x.getCoordsA())));

                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));

                } else if (x.getSlipState()==LayoutSlip.STATE_AD){
                    g2.draw(new Line2D.Double(x.getCoordsB(),
                        third(x.getCoordsB(),x.getCoordsC())));

                    g2.draw(new Line2D.Double(x.getCoordsC(),
                        third(x.getCoordsC(),x.getCoordsB())));

                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));

                } else if (x.getSlipState()==LayoutSlip.STATE_BC){

                    g2.draw(new Line2D.Double(x.getCoordsA(),
                    third(x.getCoordsA(),x.getCoordsD())));

                    g2.draw(new Line2D.Double(x.getCoordsD(),
                        third(x.getCoordsD(),x.getCoordsA())));
                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsC()));
                }
                else {
                    g2.draw(new Line2D.Double(x.getCoordsB(),
                        third(x.getCoordsB(),x.getCoordsC())));

                    g2.draw(new Line2D.Double(x.getCoordsC(),
                        third(x.getCoordsC(),x.getCoordsB())));

                    g2.draw(new Line2D.Double(x.getCoordsA(),
                    third(x.getCoordsA(),x.getCoordsD())));

                    g2.draw(new Line2D.Double(x.getCoordsD(),
                        third(x.getCoordsD(),x.getCoordsA())));
                }
            } else {
                g2.draw(new Line2D.Double(x.getCoordsA(),
                    third(x.getCoordsA(),x.getCoordsD())));

                g2.draw(new Line2D.Double(x.getCoordsD(),
                    third(x.getCoordsD(),x.getCoordsA())));
                if (x.getSlipState()==LayoutSlip.STATE_AD){
                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsD()));

                } else if (x.getSlipState()==LayoutSlip.STATE_BD){
                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
                    if(x.singleSlipStraightEqual()){
                        g2.setColor(mainColour);
                        g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
                    }

                } else if (x.getSlipState()==LayoutSlip.STATE_AC){
                    g2.setColor(mainColour);
                    g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
                    if(x.singleSlipStraightEqual()){
                        g2.setColor(mainColour);
                        g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
                    }
                } else {
                    g2.draw(new Line2D.Double(x.getCoordsA(),
                        third(x.getCoordsA(),x.getCoordsD())));

                    g2.draw(new Line2D.Double(x.getCoordsD(),
                        third(x.getCoordsD(),x.getCoordsA())));
                }
            }
        }
    }

    /*private*/ void drawTurnoutCircles(Graphics2D g2)
    {
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            if(!(t.getHidden() && !isEditable())){
                QPointF pt = t.getCoordsCenter();
                double size = SIZE * turnoutCircleSize;
                g2.setColor(turnoutCircleColor != NULL ? turnoutCircleColor : defaultTrackColor);
                g2.draw(new Ellipse2D.Double (
                                pt.getX()-size, pt.getY()-size, size+size, size+size));
            }
        }
    }

    /*private*/ void drawTurnoutRects(Graphics2D g2)
    {
        // loop over all defined turnouts
        for (int i = 0; i<turnoutList.size();i++) {
            LayoutTurnout t = turnoutList.get(i);
            QPointF pt = t.getCoordsCenter();
            g2.setColor(turnoutCircleColor != NULL ? turnoutCircleColor : defaultTrackColor);
            g2.draw(new Ellipse2D.Double (
                            pt.getX()-SIZE2, pt.getY()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
            pt = t.getCoordsA();
            if (t.getConnectA()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = t.getCoordsB();
            if (t.getConnectB()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = t.getCoordsC();
            if (t.getConnectC()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            if ( (t.getTurnoutType()==LayoutTurnout.DOUBLE_XOVER) ||
                    (t.getTurnoutType()==LayoutTurnout.RH_XOVER) ||
                        (t.getTurnoutType()==LayoutTurnout.LH_XOVER) ) {
                pt = t.getCoordsD();
                if (t.getConnectD()==NULL) {
                    g2.setColor(Color.red);
                }
                else {
                    g2.setColor(Color.green);
                }
                g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            }
        }
    }

    /*private*/ void drawTurntables(Graphics2D g2)
    {
        // loop over all defined layout turntables
        if (turntableList.size()<=0) return;
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            // draw turntable circle - default track color, side track width
            setTrackStrokeWidth(g2,false);
            QPointF c = x.getCoordsCenter();
            double r = x.getRadius();
            g2.setColor(defaultTrackColor);
            g2.draw(new Ellipse2D.Double (
                c.getX()-r, c.getY()-r, r+r, r+r));
            // draw ray tracks
            for (int j = 0; j<x.getNumberRays(); j++) {
                QPointF pt = x.getRayCoordsOrdered(j);
                TrackSegment t = x.getRayConnectOrdered(j);
                if (t!=NULL) {
                    setTrackStrokeWidth(g2,t.getMainline());
                    LayoutBlock b = t.getLayoutBlock();
                    if (b!=NULL) g2.setColor(b.getBlockColor());
                    else g2.setColor(defaultTrackColor);
                }
                else {
                    setTrackStrokeWidth(g2,false);
                    g2.setColor(defaultTrackColor);
                }
                g2.draw(new Line2D.Double(new QPointF.Double(
                        pt.getX()-((pt.getX()-c.getX())*0.2),
                            pt.getY()-((pt.getY()-c.getY())*0.2)), pt));
            }
            if(x.isTurnoutControlled() && x.getPosition()!=-1){
                QPointF pt = x.getRayCoordsIndexed(x.getPosition());
                g2.draw(new Line2D.Double(new QPointF.Double(
                        pt.getX()-((pt.getX()-c.getX())*1.8/*2*/),
                            pt.getY()-((pt.getY()-c.getY())*1.8/**2*/)), pt));
            }
        }
    }

    /*private*/ void drawXingRects(Graphics2D g2)
    {
        // loop over all defined level crossings
        for (int i = 0; i<xingList.size();i++) {
            LevelXing x = xingList.get(i);
            QPointF pt = x.getCoordsCenter();
            g2.setColor(defaultTrackColor);
            g2.draw(new Ellipse2D.Double (
                            pt.getX()-SIZE2, pt.getY()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
            pt = x.getCoordsA();
            if (x.getConnectA()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsB();
            if (x.getConnectB()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsC();
            if (x.getConnectC()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsD();
            if (x.getConnectD()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
        }
    }

    /*private*/ void drawSlipRects(Graphics2D g2)
    {
        // loop over all defined level crossings
        for (int i = 0; i<slipList.size();i++) {
            LayoutSlip x = slipList.get(i);
            QPointF pt = x.getCoordsCenter();
            g2.setColor(defaultTrackColor);
            g2.draw(new Ellipse2D.Double (
                            pt.getX()-SIZE2, pt.getY()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
            pt = x.getCoordsA();
            if (x.getConnectA()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsB();
            if (x.getConnectB()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsC();
            if (x.getConnectC()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            pt = x.getCoordsD();
            if (x.getConnectD()==NULL) {
                g2.setColor(Color.red);
            }
            else {
                g2.setColor(Color.green);
            }
            g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
        }
    }

    /*private*/ void drawTurntableRects(Graphics2D g2)
    {
        // loop over all defined turntables
        for (int i = 0; i<turntableList.size();i++) {
            LayoutTurntable x = turntableList.get(i);
            QPointF pt = x.getCoordsCenter();
            g2.setColor(defaultTrackColor);
            g2.draw(new Ellipse2D.Double (
                            pt.getX()-SIZE2, pt.getY()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
            for (int j = 0; j<x.getNumberRays();j++) {
                pt = x.getRayCoordsOrdered(j);
                if (x.getRayConnectOrdered(j)==NULL) {
                    g2.setColor(Color.red);
                }
                else {
                    g2.setColor(Color.green);
                }
                g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            }
        }
    }

    /*private*/ void drawHiddenTrack(Graphics2D g2)
    {
        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            if (isEditable() && t.getHidden()) {
                LayoutBlock b = t.getLayoutBlock();
                if (b!=NULL) g2.setColor(b.getBlockColor());
                else g2.setColor(defaultTrackColor);
                g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
                g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()),
                                        getCoords(t.getConnect2(),t.getType2())));
                setTrackStrokeWidth(g2,!main);
            }
        }
    }
    /*private*/ void drawDashedTrack(Graphics2D g2, bool mainline)
    {
        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            if ( (!t.getHidden()) && t.getDashed() && (mainline == t.getMainline()) ) {
                LayoutBlock b = t.getLayoutBlock();
                if (b!=NULL) g2.setColor(b.getBlockColor());
                else g2.setColor(defaultTrackColor);
                setTrackStrokeWidth(g2,mainline);
                if (t.getArc()){
                    CalculateTrackSegmentAngle(t);
                    Stroke drawingStroke;
                    Stroke originalStroke = g2.getStroke();
                    if (mainline)
                        drawingStroke = new BasicStroke(mainlineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
                    else
                        drawingStroke = new BasicStroke(sideTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
                    g2.setStroke(drawingStroke);
                    g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
                    g2.setStroke(originalStroke);
                } else {
                    QPointF end1 = getCoords(t.getConnect1(),t.getType1());
                    QPointF end2 = getCoords(t.getConnect2(),t.getType2());
                    double delX = end1.getX() - end2.getX();
                    double delY = end1.getY() - end2.getY();
                    double cLength = Math.sqrt( (delX*delX) + (delY*delY) );
                    // note: The preferred dimension of a dash (solid + blank space) is
                    //         5 * the track width - about 60% solid and 40% blank.
                    int nDashes = (int)( cLength / ((trackWidth)*5.0) );
                    if (nDashes < 3) nDashes = 3;
                    double delXDash = -delX/( (nDashes) - 0.5 );
                    double delYDash = -delY/( (nDashes) - 0.5 );
                    double begX = end1.getX();
                    double begY = end1.getY();
                    for (int k = 0; k<nDashes; k++) {
                        g2.draw(new Line2D.Double(new QPointF.Double(begX,begY),
                            new QPointF.Double((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))));
                        begX += delXDash;
                        begY += delYDash;
                    }
                }
            }
        }
    }

    /* draw all track segments which are not hidden, not dashed, and that match the isMainline parm */
    /*private*/ void drawSolidTrack(Graphics2D g2, bool isMainline)
    {
        for (int i = 0; i<trackList.size();i++) {
            setTrackStrokeWidth(g2, isMainline);
            TrackSegment t = trackList.get(i);
            if ( (!t.getHidden()) && (!t.getDashed()) && (isMainline == t.getMainline()) ) {
                LayoutBlock b = t.getLayoutBlock();
                if (b!=NULL) g2.setColor(b.getBlockColor());
                else g2.setColor(defaultTrackColor);
                //setTrackStrokeWidth(g2,mainline);
                if(t.getArc()){
                    CalculateTrackSegmentAngle(t);
                    g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
                } else {
                    g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
                }
                t.trackRedrawn();
            }
        }
    }

    /*
     * Calculates the initally parameters for drawing a circular track segment.
     */
    /*private*/ void CalculateTrackSegmentAngle(TrackSegment t){
        QPointF pt1 = getCoords(t.getConnect1(),t.getType1());
        QPointF pt2 = getCoords(t.getConnect2(),t.getType2());
        if (t.getFlip()){
            pt1 = getCoords(t.getConnect2(),t.getType2());
            pt2 = getCoords(t.getConnect1(),t.getType1());
        }
        if((t.getTmpPt1()!=pt1) || (t.getTmpPt2()!=pt2) || t.trackNeedsRedraw()){
            t.setTmpPt1(pt1);
            t.setTmpPt2(pt2);
            //setTrackStrokeWidth(g2,false);
            double pt2x;
            double pt2y;
            double pt1x;
            double pt1y;
            pt2x = pt2.getX();
            pt2y = pt2.getY();
            pt1x = pt1.getX();
            pt1y = pt1.getY();

            if (t.getAngle() == 0.0D)
                t.setTmpAngle(90.0D);
            else
                t.setTmpAngle(t.getAngle());
            // Convert angle to radiants in order to speed up maths
            double halfAngle = java.lang.Math.toRadians(t.getTmpAngle())/2.0D;
            double chord;
            double a;
            double o;
            double radius;
            // Compute arc's chord
            a = pt2x - pt1x;
            o = pt2y - pt1y;
            chord=java.lang.Math.sqrt(((a*a)+(o*o)));
            t.setChordLength(chord);
            // Make sure chord is not NULL
            // In such a case (pt1 == pt2), there is no arc to draw
            if (chord > 0.0D) {
                radius = (chord/2)/(java.lang.Math.sin(halfAngle));
                // Circle
                double startRad = java.lang.Math.atan2(a, o) - halfAngle;
                t.setStartadj(java.lang.Math.toDegrees(startRad));
                if(t.getCircle()){
                    // Circle - Compute center
                    t.setCentreX(pt2x - java.lang.Math.cos(startRad) * radius);
                    t.setCentreY(pt2y + java.lang.Math.sin(startRad) * radius);
                    // Circle - Compute rectangle required by Arc2D.Double
                    t.setCW(radius * 2.0D);
                    t.setCH(radius * 2.0D);
                    t.setCX(t.getCentreX()-(radius));
                    t.setCY(t.getCentreY()-(radius));
                }
                else {
                    // Elipse - Round start angle to the closest multiple of 90
                    t.setStartadj(java.lang.Math.round(t->getStartadj() / 90.0D) * 90.0D);
                    // Elipse - Compute rectangle required by Arc2D.Double
                    t.setCW(java.lang.Math.abs(a)*2.0D);
                    t.setCH(java.lang.Math.abs(o)*2.0D);
                    // Elipse - Adjust rectangle corner, depending on quadrant
                    if (o * a < 0.0D)
                        a = -a;
                    else
                        o = -o;
                    t.setCX(java.lang.Math.min(pt1x, pt2x)-java.lang.Math.max(a, 0.0D));
                    t.setCY(java.lang.Math.min(pt1y, pt2y)-java.lang.Math.max(o, 0.0D));
                }
            }
        }
    }
    /*
     * The recalculation method is used when the user changes the angle dynamically in edit mode
     * by dragging the centre of the cirle
     */
    /*private*/ void reCalculateTrackSegmentAngle(TrackSegment t, double x, double y){

        double pt2x;
        double pt2y;
        double pt1x;
        double pt1y;

        pt2x = t.getTmpPt2().getX();
        pt2y = t.getTmpPt2().getY();
        pt1x = t.getTmpPt1().getX();
        pt1y = t.getTmpPt1().getY();
        if (t.getFlip()){
            pt1x = t.getTmpPt2().getX();
            pt1y = t.getTmpPt2().getY();
            pt2x = t.getTmpPt1().getX();
            pt2y = t.getTmpPt1().getY();
        }
        //Point 1 to new point length
        double a;
        double o;
        double la;
        // Compute arc's chord
        a = pt2x - x;
        o = pt2y - y;
        la=java.lang.Math.sqrt(((a*a)+(o*o)));

        double lb;
        a = pt1x - x;
        o = pt1y - y;
        lb=java.lang.Math.sqrt(((a*a)+(o*o)));

        double newangle=Math.toDegrees(Math.acos((-t.getChordLength()*t.getChordLength()+la*la+lb*lb)/(2*la*lb)));
        t.setAngle(newangle);

    }

    /*
     * Draws a square at the circles centre, that then allows the user to dynamically change
     * the angle by dragging the mouse.
     */
    /*private*/ void drawTrackCircleCentre(Graphics2D g2)
    {
        // loop over all defined turnouts
        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            if (t.getCircle()){
                QPointF pt = t.getCoordsCenterCircle();
                g2.setColor(Color.black);
                g2.draw(new Rectangle2D.Double (
                            pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
            }
        }
    }
    /*private*/ void drawTrackInProgress(Graphics2D g2)
    {
        // check for segment in progress
        if ( isEditable() && (beginObject!=NULL) && trackBox.isSelected() ) {
            g2.setColor(defaultTrackColor);
            setTrackStrokeWidth(g2,false);
            g2.draw(new Line2D.Double(beginLocation,currentLocation));
        }
    }

    /*private*/ void drawTrackOvals(Graphics2D g2)
    {
        // loop over all defined track segments
        g2.setColor(defaultTrackColor);
        for (int i = 0; i<trackList.size();i++) {
            TrackSegment t = trackList.get(i);
            QPointF pt1 = getCoords(t.getConnect1(),t.getType1());
            QPointF pt2 = getCoords(t.getConnect2(),t.getType2());
            double cX = (pt1.getX() + pt2.getX())/2.0D;
            double cY = (pt1.getY() + pt2.getY())/2.0D;
            g2.draw(new Ellipse2D.Double (cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
            if (t.getArc()) {
                LayoutBlock b = t.getLayoutBlock();
                if (b!=NULL) g2.setColor(b.getBlockColor());
                else g2.setColor(defaultTrackColor);
                g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
                if (t.getCircle()){
                    g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), new QPointF.Double(t.getCentreX(),t.getCentreY())));
                    g2.draw(new Line2D.Double(getCoords(t.getConnect2(),t.getType2()), new QPointF.Double(t.getCentreX(),t.getCentreY())));

                }
                g2.setColor(defaultTrackColor);
            }
        }
    }

    /*private*/ void drawPoints(Graphics2D g2)
    {
        for (int i = 0; i<pointList.size();i++) {
            PositionablePoint p = pointList.get(i);
            switch (p.getType()) {
                case PositionablePoint.ANCHOR:
                    // nothing to draw unless in edit mode
                    if (isEditable()) {
                        // in edit mode, draw locater rectangle
                        QPointF pt = p.getCoords();
                        if ((p.getConnect1()==NULL) || (p.getConnect2()==NULL)) {
                            g2.setColor(Color.red);
                        }
                        else {
                            g2.setColor(Color.green);
                        }
                        g2.draw(new Rectangle2D.Double (
                                    pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
                    }
                    break;
                case PositionablePoint.END_BUMPER:
                    // nothing to draw unless in edit mode
                    if (isEditable()) {
                        // in edit mode, draw locater rectangle
                        QPointF pt = p.getCoords();
                        if (p.getConnect1()==NULL) {
                            g2.setColor(Color.red);
                        }
                        else {
                            g2.setColor(Color.green);
                        }
                        g2.draw(new Rectangle2D.Double (
                                    pt.getX()-SIZE, pt.getY()-SIZE, SIZE2, SIZE2));
                    }
                    break;
                default:
                    log.error("Illegal type of Positionable Point");
            }
        }
    }

    /*private*/ void drawSelectionRect(Graphics2D g2) {
        if ( selectionActive && (selectionWidth!=0.0) && (selectionHeight!=0.0) ){
            g2.setColor(defaultTrackColor);
            g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
            g2.draw(new Rectangle2D.Double (selectionX, selectionY, selectionWidth, selectionHeight));
        }
    }

    /*private*/ void drawMemoryRects(Graphics2D g2) {
        if (memoryLabelList.size()<=0) return;
        g2.setColor(defaultTrackColor);
        g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
        for (int i = 0;i<memoryLabelList.size();i++) {
            MemoryIcon l = memoryLabelList.get(i);
            g2.draw(new Rectangle2D.Double (l.getX(), l.getY(), l.getSize().width, l.getSize().height));
        }
    }

    /*private*/ void drawPanelGrid(Graphics2D g2) {
        Dimension dim = getSize();
        double pix = 10.0;
        double maxX = dim.width;
        double maxY = dim.height;
        QPointF startPt = new QPointF.Double(0.0, 10.0);
        QPointF stopPt = new QPointF.Double(maxX, 10.0);
        BasicStroke narrow = new BasicStroke(1.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
        BasicStroke wide = new BasicStroke(2.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
        g2.setColor(Color.gray);
        g2.setStroke(narrow);
        // draw horizontal lines
        while (pix<maxY) {
            startPt.setLocation(0.0,pix);
            stopPt.setLocation(maxX,pix);
            if ( (((int)pix) % 100) < 5.0) {
                g2.setStroke(wide);
                g2.draw(new Line2D.Double(startPt,stopPt));
                g2.setStroke(narrow);
            }
            else {
                g2.draw(new Line2D.Double(startPt,stopPt));
            }
            pix += 10.0;
        }
        // draw vertical lines
        pix = 10.0;
        while (pix<maxX) {
            startPt.setLocation(pix,0.0);
            stopPt.setLocation(pix,maxY);
            if ( (((int)pix) % 100) < 5.0) {
                g2.setStroke(wide);
                g2.draw(new Line2D.Double(startPt,stopPt));
                g2.setStroke(narrow);
            }
            else {
                g2.draw(new Line2D.Double(startPt,stopPt));
            }
            pix += 10.0;
        }
    }

    /*protected*/ QPointF getCoords(Object o, int type) {
        if (o != NULL) {
            switch (type) {
                case POS_POINT:
                    return ((PositionablePoint)o).getCoords();
                case TURNOUT_A:
                    return ((LayoutTurnout)o).getCoordsA();
                case TURNOUT_B:
                    return ((LayoutTurnout)o).getCoordsB();
                case TURNOUT_C:
                    return ((LayoutTurnout)o).getCoordsC();
                case TURNOUT_D:
                    return ((LayoutTurnout)o).getCoordsD();
                case LEVEL_XING_A:
                    return ((LevelXing)o).getCoordsA();
                case LEVEL_XING_B:
                    return ((LevelXing)o).getCoordsB();
                case LEVEL_XING_C:
                    return ((LevelXing)o).getCoordsC();
                case LEVEL_XING_D:
                    return ((LevelXing)o).getCoordsD();
                case SLIP_A:
                    return ((LayoutSlip)o).getCoordsA();
                case SLIP_B:
                    return ((LayoutSlip)o).getCoordsB();
                case SLIP_C:
                    return ((LayoutSlip)o).getCoordsC();
                case SLIP_D:
                    return ((LayoutSlip)o).getCoordsD();
                default:
                    if (type>=TURNTABLE_RAY_OFFSET)
                        return ((LayoutTurntable)o).getRayCoordsIndexed(type-TURNTABLE_RAY_OFFSET);
            }
        }
        else {
            log.error("Null connection point of type "+type);
        }
        return (new QPointF.Double(0.0,0.0));
    }

    /*protected*/ bool showAlignPopup(Positionable l) {
        return false;
    }

    /*public*/ void showToolTip(Positionable selection, MouseEvent event) {
        ToolTip tip = selection.getTooltip();
        tip.setLocation(selection.getX()+selection.getWidth()/2, selection.getY()+selection.getHeight());
        tip.setText(selection.getNameQString());
        setToolTip(tip);
    }

    @Override
    /*public*/ void addToPopUpMenu(jmri.NamedBean nb, /*JMenu*/QMenuItem item, int menu){
        if(nb==NULL || item==NULL){
            return;
        }
        if(nb instanceof Sensor){
            for(SensorIcon si:sensorList){
                if(si.getNamedBean()==nb && si.getPopupUtility()!=NULL){
                    switch(menu){
                        case VIEWPOPUPONLY : si.getPopupUtility().addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : si.getPopupUtility().addEditPopUpMenu(item); break;
                        default: si.getPopupUtility().addEditPopUpMenu(item);
                                 si.getPopupUtility().addViewPopUpMenu(item);
                    }
                }
            }
        } else if (nb instanceof SignalHead){
            for(SignalHeadIcon si:signalList){
                if(si.getNamedBean()==nb && si.getPopupUtility()!=NULL){
                    switch(menu){
                        case VIEWPOPUPONLY : si.getPopupUtility().addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : si.getPopupUtility().addEditPopUpMenu(item); break;
                        default: si.getPopupUtility().addEditPopUpMenu(item);
                                 si.getPopupUtility().addViewPopUpMenu(item);
                    }
                }
            }
        } else if (nb instanceof SignalMast){
            for(SignalMastIcon si:signalMastList){
                if(si.getNamedBean()==nb && si.getPopupUtility()!=NULL){
                    switch(menu){
                        case VIEWPOPUPONLY : si.getPopupUtility().addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : si.getPopupUtility().addEditPopUpMenu(item); break;
                        default: si.getPopupUtility().addEditPopUpMenu(item);
                                 si.getPopupUtility().addViewPopUpMenu(item);
                    }
                }
            }
        } else if (nb instanceof Memory){
            for(MemoryIcon si: memoryLabelList){
                if(si.getNamedBean()==nb && si.getPopupUtility()!=NULL){
                    switch(menu){
                        case VIEWPOPUPONLY : si.getPopupUtility().addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : si.getPopupUtility().addEditPopUpMenu(item); break;
                        default: si.getPopupUtility().addEditPopUpMenu(item);
                                 si.getPopupUtility().addViewPopUpMenu(item);
                    }
                }
            }
        } else if (nb instanceof Turnout){
            for(LayoutTurnout ti: turnoutList){
                if(ti.getTurnout()==(nb)){
                    switch(menu){
                        case VIEWPOPUPONLY : ti.addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : ti.addEditPopUpMenu(item); break;
                        default: ti.addEditPopUpMenu(item);
                                 ti.addViewPopUpMenu(item);
                    }
                    break;
                }
            }
            for(LayoutSlip ls: slipList){
                if(ls.getTurnout()==nb||ls.getTurnoutB()==nb){
                    switch(menu){
                        case VIEWPOPUPONLY : ls.addViewPopUpMenu(item); break;
                        case EDITPOPUPONLY : ls.addEditPopUpMenu(item); break;
                        default: ls.addEditPopUpMenu(item);
                                 ls.addViewPopUpMenu(item);
                    }
                    break;
                }

            }
        }
    }
//    // initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutEditor.class.getName());
//}
