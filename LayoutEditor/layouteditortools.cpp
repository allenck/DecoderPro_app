#include "layouteditortools.h"
#include "jtextfield.h"
#include <QMessageBox>
#include "signalheadmanager.h"
#include "signalheadmanager.h"
#include "signalheadicon.h"
#include "signalmast.h"
#include "layoutturnout.h"
#include "blockbosslogic.h"
#include "defaultsignalmastmanager.h"
#include "../Tables/jmribeancombobox.h"
#include "sensoricon.h"
#include "tracksegment.h"
#include "signalmasticon.h"
#include "signalmastlogicmanager.h"
#include "defaultsignalmastlogicmanager.h"
#include "signallingguitools.h"
#include "inputdialog.h"
#include "jmrijframe.h"
#include "jseparator.h"
#include "defaultconditionalaction.h"
#include "logix.h"
#include "defaultconditionalaction.h"
#include "conditionalvariable.h"
#include <QCompleter>
#include <QGroupBox>
#include "borderlayout.h"
#include "jmribeancombobox.h"
#include "joptionpane.h"
#include <QVariant>
#include "layoutslip.h"
#include "mathutil.h"
#include "layouteditorfinditems.h"
#include "path.h"
#include "levelxing.h"
#include "jmrijframe.h"
#include "borderlayout.h"

//LayoutEditorTools::LayoutEditorTools(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Layout Editor Tools provides tools making use of layout connectivity available
 *	in Layout Editor panels.
 * <P>
 * The tools in this module are accessed via the Tools menu in Layout Editor.
 * <P>
 * @author Dave Duchamp Copyright (c) 2007
 * @version $Revision: 21247 $
 */

///*public*/ class LayoutEditorTools
//{

//	// Defined text resource
//	static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor->LayoutEditorBundle");
//    static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");


// constructor method
/*public*/ LayoutEditorTools::LayoutEditorTools(LayoutEditor* thePanel, QObject* parent) :QObject(parent)
{
    // constants
 NONE = 0;  // Signal at Turnout Positions
 A1 = 1;
 A2 = 2;
 A3 = 3;
 B1 = 4;
 B2 = 5;
 C1 = 6;
 C2 = 7;
 D1 = 8;
 D2 = 9;
 // operational instance variables shared between tools

 layoutEditor = thePanel;


 // operational variables for Set Signals at Double Crossover Turnout tool

// setSignalMastsOpen =false;
// turnoutMastFromMenu = false;
// signalMastsJmriFrame = NULL;

// turnoutMastNameField = new JTextField(16);
 signalMastTurnoutPanel = new QWidget();
 turnoutBlocks =  QVector<QString>(4);
 usedMasts = QList<NamedBean*>();

 changeSensorIcon = NULL;

 turnoutSenBlocks = QVector<QString>(4);

 sensorTurnoutPanel = new QWidget();
 getAnchorSavedSensors = NULL;
 changeSensorAtBoundaryIcon = NULL;
 setSensorsAtBlockBoundaryDone = NULL;
 setSensorsAtBlockBoundaryCancel = NULL;
 setSensorsAtBoundaryOpen = false;
 setSensorsAtBlockBoundaryFrame = NULL;

 sensorFrame = NULL;

 getAnchorSavedSignalMasts = NULL;
// setSignalMastsAtBoundaryDone = NULL;
// setSignalMastsAtBoundaryCancel = NULL;
 setSignalMastsAtBoundaryOpen = false;
 setSignalMastsAtBoundaryFrame = NULL;
 adjust = (5.0/90.0);
 awayright = 5;
 offSetFromPoint = 5;

 setSignalsAtTToTFrame = NULL;
// turnout1NameField = new JTextField(16);
// turnout2NameField = new JTextField(16);
 setA1TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA1TToTLogic = new QCheckBox(tr("Set up Logic"));
 setA2TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA2TToTLogic = new QCheckBox(tr("Set up Logic"));
 setB1TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB1TToTLogic = new QCheckBox(tr("Set up Logic"));
 setB2TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB2TToTLogic = new QCheckBox(tr("Set up Logic"));
 setC1TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC1TToTLogic = new QCheckBox(tr("Set up Logic"));
 setC2TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC2TToTLogic = new QCheckBox(tr("Set up Logic"));
 setD1TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD1TToTLogic = new QCheckBox(tr("Set up Logic"));
 setD2TToTHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD2TToTLogic = new QCheckBox(tr("Set up Logic"));
 getSavedTToTSignalHeads = NULL;
 changeTToTSignalIcon = NULL;
 setTToTSignalsDone = NULL;
 setTToTSignalsCancel = NULL;
 layoutTurnout1 = NULL;
 layoutTurnout2 = NULL;
 turnout1 = NULL;
 turnout2 = NULL;
 connectorTrack = NULL;
 a1TToTHead = NULL;
 a2TToTHead = NULL;
 b1TToTHead = NULL;
 b2TToTHead = NULL;
 c1TToTHead = NULL;
 c2TToTHead = NULL;
 d1TToTHead = NULL;
 d2TToTHead = NULL;
 layoutTurnout1Horizontal = false;
 layoutTurnout1Vertical = false;
 layoutTurnout2Horizontal = false;
 layoutTurnout2Vertical = false;
 layoutTurnout1ThroatLeft = false;
 layoutTurnout1ThroatUp = false;
 layoutTurnout2ThroatLeft = false;
 layoutTurnout2ThroatUp = false;
 layoutTurnout1BUp = false;
 layoutTurnout1BLeft = false;
 layoutTurnout2BUp = false;
 layoutTurnout2BLeft = false;

 // operational variables for Set Sensors at Level Crossing tool
// setSensorsAtSlipFrame = NULL;
// setSensorsAtSlipOpenFlag = false;

// getSavedSlipSensors = NULL;
// setSlipSensorsDone = NULL;
// setSlipSensorsCancel = NULL;
// changeSensorSlipIcon = NULL;
 sensorSlipFrame = NULL;

 //setSensorsAtSlipFromMenuFlag = false;
 slipSensorBlocks = new QVector<QString>(4);

 sensorSlipPanel = new QWidget();

 // operational variables for Set Signals at Double Crossover Turnout tool
 setSignalsAtSlipFrame = NULL;
 setA1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setA2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setB1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setB2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setC1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setC2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setD1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setD2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD2SlipLogic = new QCheckBox(tr("Set up Logic"));

 setSlipSignalsDone = NULL;
 setSlipSignalsCancel = NULL;
 layoutSlip = NULL;

 a1SlipHead = NULL;
 a2SlipHead = NULL;
 b1SlipHead = NULL;
 b2SlipHead = NULL;
 c1SlipHead = NULL;
 c2SlipHead = NULL;
 d1SlipHead = NULL;
 d2SlipHead = NULL;


 // operational variables for Set Signals at Level Crossing tool
 setSignalsAtLevelXingFrame = NULL;
// setSignalsAtLevelXingOpen = false;
// blockANameField = new JTextField(16);
// blockCNameField = new JTextField(16);
// aField = new JTextField(16);
// bField = new JTextField(16);
// cField = new JTextField(16);
// dField = new JTextField(16);
 setAHead = new QCheckBox(tr("Place Head"));
 setupALogic = new QCheckBox(tr("Set Logic"));
 setBHead = new QCheckBox(tr("Place Head"));
 setupBLogic = new QCheckBox(tr("Set Logic"));
 setCHead = new QCheckBox(tr("Place Head"));
 setupCLogic = new QCheckBox(tr("Set Logic"));
 setDHead = new QCheckBox(tr("Place Head"));
 setupDLogic = new QCheckBox(tr("Set Logic"));
 getSavedXingSignalHeads = NULL;
 changeXingSignalIcon = NULL;
 setXingSignalsDone = NULL;
 setXingSignalsCancel = NULL;
 levelXingACHorizontal = false;
 levelXingACVertical = false;
 levelXingALeft = false;
 levelXingAUp = false;
 levelXingBUp = false;
 levelXingBLeft = false;
 xingFromMenu = false;
 levelXing = NULL;
 aHead = NULL;
 bHead = NULL;
 cHead = NULL;
 dHead = NULL;

 // operational variables for Set Sensors at Level Crossing tool
// sensorsAtLevelXingFrame = NULL;
// setSensorsAtLevelXingOpenFlag = false;
// blockANameSensorField = new JTextField(16);
// blockCNameSensorField = new JTextField(16);

 getSavedXingSensors = NULL;
 setXingSensorsDone = NULL;
 setXingSensorsCancel = NULL;
 changeSensorXingIcon = NULL;
 sensorXingFrame = NULL;

// setSignalsAtLevelXingFromMenuFlag = false;
// xingSensorBlocks = new QVector<QString>(4);

// sensorXingPanel = new QWidget();

 // operational variables for Set Signals at Double Crossover Turnout tool
 setSignalsAtSlipFrame = NULL;
 setA1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setA2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setB1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setB2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setC1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setC2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC2SlipLogic = new QCheckBox(tr("Set up Logic"));
 setD1SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD1SlipLogic = new QCheckBox(tr("Set up Logic"));
 setD2SlipHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD2SlipLogic = new QCheckBox(tr("Set up Logic"));

 setSlipSignalsDone = NULL;
 setSlipSignalsCancel = NULL;
 layoutSlip = NULL;

 a1SlipHead = NULL;
 a2SlipHead = NULL;
 b1SlipHead = NULL;
 b2SlipHead = NULL;
 c1SlipHead = NULL;
 c2SlipHead = NULL;
 d1SlipHead = NULL;
 d2SlipHead = NULL;


 // operational variables for Set SignalMast at Slip tool
// setSignalMastsAtLayoutSlipFrame = NULL;
// setSignalMastsAtSlipOpen = false;

 getSavedSlipSignalMasts = NULL;
 setSlipSignalMastsDone = NULL;
 setSlipSignalMastsCancel = NULL;

// slipMastFromMenu = false;
 slipBlocks = new QVector<QString>(4);


 signalMastLayoutSlipPanel = new QWidget();

 // operational variables for Set SignalMast at Level Crossing tool
// setSignalsAtLevelXingFrame = NULL;
// setSignalsAtLevelXingFrameFlag = false;
// blockANameMastField = new JTextField(16);
// blockCNameMastField = new JTextField(16);

 getSavedXingSignalMasts = NULL;
 setXingSignalMastsDone = NULL;
 setXingSignalMastsCancel = NULL;

 xingMastFromMenu = false;
 xingBlocks = new QVector<QString>(4);

 signalMastLevelXingPanel = new QWidget();

 // operational variables for Set Signals at 3-Way Turnout tool
 setSignalsAt3WayTurnoutFrame = nullptr;
 setSignalsAt3WayOpen = false;
// turnoutANameField = new JTextField(16);
// turnoutBNameField = new JTextField(16);
// a13WayField = new JTextField(16);
// a23WayField = new JTextField(16);
// a33WayField = new JTextField(16);
// b3WayField = new JTextField(16);
// c3WayField = new JTextField(16);
// d3WayField = new JTextField(16);
 setA13WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA13WayLogic = new QCheckBox(tr("Set up Logic"));
 setA23WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA23WayLogic = new QCheckBox(tr("Set up Logic"));
 setA33WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupA33WayLogic = new QCheckBox(tr("Set up Logic"));
 setB3WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupB3WayLogic = new QCheckBox(tr("Set up Logic"));
 setC3WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupC3WayLogic = new QCheckBox(tr("Set up Logic"));
 setD3WayHead = new QCheckBox(tr("Add Signal Head Icon to Panel"));
 setupD3WayLogic = new QCheckBox(tr("Set up Logic"));
 getSaved3WaySignalHeads = NULL;
 change3WaySignalIcon = NULL;
 set3WaySignalsDone = NULL;
 set3WaySignalsCancel = NULL;
 layoutTurnoutA = NULL;
 layoutTurnoutB = NULL;
 turnoutA = NULL;
 turnoutB = NULL;
 ///*private*/ TrackSegment* conTrack = NULL;
 a13WayHead = NULL;   // saved in A1 of Turnout A - Throat - continuing
 a23WayHead = NULL;   // saved in A2 of Turnout A - Throat - diverging A (optional)
 a33WayHead = NULL;   // saved in A3 of Turnout A - Throat - diverging B (optional)
 b3WayHead = NULL;    // saved in C1 of Turnout A - at diverging A
 c3WayHead = NULL;    // saved in B1 of Turnout B - at continuing
 d3WayHead = NULL;    // saved in C1 of Turnout B - at diverging B
 layoutTurnoutAHorizontal = false;
 layoutTurnoutAVertical = false;
 layoutTurnoutBHorizontal = false;
 layoutTurnoutBVertical = false;
 layoutTurnoutAThroatLeft = false;
 layoutTurnoutAThroatUp = false;
 layoutTurnoutBThroatLeft = false;
 layoutTurnoutBThroatUp = false;
 layoutTurnoutABUp = false;
 layoutTurnoutABLeft = false;
 layoutTurnoutBBUp = false;
 layoutTurnoutBBLeft = false;
 //Border blackline = BorderFactory.createLineBorder(Color.black);

// signalMastsTurnoutComboBox = new JmriBeanComboBox(
//             InstanceManager::turnoutManagerInstance(), nullptr,
//             BeanComboBox::DisplayOptions::DISPLAYNAME);
}
/*public*/ void LayoutEditorTools::setSignalsAtThroatToThroatTurnoutsFromMenu(
        /*@Nonnull*/ LayoutTurnout* to, /*@Nonnull*/ QString linkedTurnoutName,
        /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame) {
    ttotTurnoutName1 = to->getTurnoutName();
    ttotTurnoutName2 = linkedTurnoutName;

    turnout1ComboBox->setSelectedItem(to->getTurnout());
    turnout2ComboBox->setSelectedItem(to->getSecondTurnout());

    a1TToTSignalHeadComboBox->setSelectedItem(nullptr);
    a2TToTSignalHeadComboBox->setSelectedItem(nullptr);
    b1TToTSignalHeadComboBox->setSelectedItem(nullptr);
    b2TToTSignalHeadComboBox->setSelectedItem(nullptr);
    c1TToTSignalHeadComboBox->setSelectedItem(nullptr);
    c2TToTSignalHeadComboBox->setSelectedItem(nullptr);
    d1TToTSignalHeadComboBox->setSelectedItem(nullptr);
    d2TToTSignalHeadComboBox->setSelectedItem(nullptr);

    setSignalsAtThroatToThroatTurnoutsFromMenuFlag = true;
    setSignalsAtThroatToThroatTurnouts(theEditor, theFrame);
    setSignalsAtThroatToThroatTurnoutsFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAtThroatToThroatTurnouts(
        /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame) {
    signalIconEditor = theEditor;
    signalFrame = theFrame;

    //Initialize if needed
    if (setSignalsAtThroatToThroatTurnoutsFrame == nullptr) {
        setSignalsAtThroatToThroatTurnoutsOpenFlag = false;
        setSignalsAtThroatToThroatTurnoutsFrame = new JmriJFrameX(tr("Set Signal Heads at Throat-to-Throat Turnouts"), false, true);
        oneFrameToRuleThemAll(setSignalsAtThroatToThroatTurnoutsFrame);
        setSignalsAtThroatToThroatTurnoutsFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
        setSignalsAtThroatToThroatTurnoutsFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtTToTTurnout", true);
        setSignalsAtThroatToThroatTurnoutsFrame->setLocation(70, 30);
        QFont font;
        font.setPointSize(8);
        setSignalsAtThroatToThroatTurnoutsFrame->setFont(font);//        QWidget* theContentPane = setSignalsAtThroatToThroatTurnoutsFrame->getContentPane();
        QVBoxLayout* theContentPaneLayout;
//        theContentPane->setLayout(theContentPaneLayout = new QVBoxLayout()); //theContentPane, BoxLayout.Y_AXIS));
        QScrollArea* scrollarea = new QScrollArea();
        QWidget* theContentPane = new QWidget();
        theContentPane->setLayout(theContentPaneLayout = new QVBoxLayout());
        scrollarea->setWidget(theContentPane);
        scrollarea->setWidgetResizable(true);
        setSignalsAtThroatToThroatTurnoutsFrame->setCentralWidget(scrollarea);

        JPanel* panel1a = new JPanel(new FlowLayout());
        ttotTurnoutName1Label = new JLabel(tr("Turnout") + " 1 "
                + tr("Name"));
        panel1a->layout()->addWidget(ttotTurnoutName1Label);
        panel1a->layout()->addWidget(turnout1ComboBox);
        turnout1ComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
        theContentPaneLayout->addWidget(panel1a);

        JPanel* panel1b = new JPanel(new FlowLayout());
        ttotTurnoutName2Label = new JLabel(tr("Turnout") + " 2 "
                + tr("Name"));
        panel1b->layout()->addWidget(ttotTurnoutName2Label);
        panel1b->layout()->addWidget(turnout2ComboBox);
        turnout2ComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
        theContentPaneLayout->addWidget(panel1b);
        theContentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        //Provide for retrieval of names of previously saved signal heads

        JPanel* panel20 = new JPanel(new FlowLayout());
        JLabel* shTitle = new JLabel(tr("SignalHeads"));
        panel20->layout()->addWidget(shTitle);
        panel20->layout()->addWidget(new JLabel("		"));
        panel20->layout()->addWidget(getSavedTToTSignalHeads = new QPushButton(tr("GetSaved")));
        //getSavedTToTSignalHeads.addActionListener((ActionEvent e) -> {
        connect(getSavedTToTSignalHeads, &QPushButton::clicked, [=] {
            setSignalsAtTToTTurnoutsGetSaved();
        });
        getSavedTToTSignalHeads->setToolTip(tr("Select to retrieve signal heads previously stored."));
        theContentPaneLayout->addWidget(panel20);
        theContentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        JPanel* panel2a = new JPanel(new FlowLayout());
        panel2a->layout()->addWidget(new JLabel("   "));
        panel2a->layout()->addWidget(setPlaceAllHeads);
        setPlaceAllHeads->setToolTip(tr("Check to place all signal head icons"));
        //setPlaceAllHeads.addActionListener((ActionEvent e) -> {
        connect(setPlaceAllHeads, &QCheckBox::clicked, [=]{
            bool isSelected = setPlaceAllHeads->isChecked();
            //(de)select all checkboxes
            setA1TToTHead->setChecked(isSelected);
            setA2TToTHead->setChecked(isSelected);
            setB1TToTHead->setChecked(isSelected);
            setB2TToTHead->setChecked(isSelected);
            setC1TToTHead->setChecked(isSelected);
            setC2TToTHead->setChecked(isSelected);
            setD1TToTHead->setChecked(isSelected);
            setD2TToTHead->setChecked(isSelected);
        });
        panel2a->layout()->addWidget(new JLabel("  "));
        panel2a->layout()->addWidget(setupAllLogic);
        setupAllLogic->setToolTip(tr("Check to set up Simple Signal Logic for all Signal Heads"));
        //setupAllLogic.addActionListener((ActionEvent e) -> {
        connect(setupAllLogic, &QCheckBox::clicked, [=]{
            bool isSelected = setupAllLogic->isChecked();
            //(de)select all checkboxes
            setupA1TToTLogic->setChecked(isSelected);
            setupA2TToTLogic->setChecked(isSelected);
            setupB1TToTLogic->setChecked(isSelected);
            setupB2TToTLogic->setChecked(isSelected);
            setupC1TToTLogic->setChecked(isSelected);
            setupC2TToTLogic->setChecked(isSelected);
            setupD1TToTLogic->setChecked(isSelected);
            setupD2TToTLogic->setChecked(isSelected);
        });
        theContentPaneLayout->addWidget(panel2a);
        theContentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        //Signal heads located at turnout 1
        JPanel* panel20a = new JPanel(new FlowLayout());
        panel20a->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " 1 - "
                + tr("continuing track")));
        theContentPaneLayout->addWidget(panel20a);

        JPanel* panel21 = new JPanel(new FlowLayout());
        panel21->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 2 - "
                + tr("continuing track"))));
        panel21->layout()->addWidget(a1TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel21);
        a1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel22 = new JPanel(new FlowLayout());
        panel22->layout()->addWidget(new JLabel(tr("Or Both") + " 2 " + tr("Tracks)") + "	  "));
        panel22->layout()->addWidget(setA1TToTHead);
        setA1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel22->layout()->addWidget(new JLabel("  "));
        panel22->layout()->addWidget(setupA1TToTLogic);
        setupA1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel22);

        JPanel* panel23 = new JPanel(new FlowLayout());
        panel23->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 2 - "
                + tr("Protects Turnout"))));
        panel23->layout()->addWidget(a2TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel23);
        a2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel24 = new JPanel(new FlowLayout());
        panel24->layout()->addWidget(new JLabel("				"));
        panel24->layout()->addWidget(setA2TToTHead);
        setA2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel24->layout()->addWidget(new JLabel("  "));
        panel24->layout()->addWidget(setupA2TToTLogic);
        setupA2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel24);

        JPanel* panel31x = new JPanel(new FlowLayout());
        panel31x->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " 1 - "
                + tr("Protects Turnout")));
        theContentPaneLayout->addWidget(panel31x);

        JPanel* panel31 = new JPanel(new FlowLayout());
        panel31->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 2 - "
                + tr("continuing track"))));
        panel31->layout()->addWidget(b1TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel31);
        b1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel32 = new JPanel(new FlowLayout());
        panel32->layout()->addWidget(new JLabel(tr("Or Both") + " 2 " + tr("Tracks)") + "	  "));
        panel32->layout()->addWidget(setB1TToTHead);
        setB1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel32->layout()->addWidget(new JLabel("  "));
        panel32->layout()->addWidget(setupB1TToTLogic);
        setupB1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel32);

        JPanel* panel33 = new JPanel(new FlowLayout());
        panel33->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 2 - "
                + tr("Protects Turnout"))));
        panel33->layout()->addWidget(b2TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel33);
        b2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel34 = new JPanel(new FlowLayout());
        panel34->layout()->addWidget(new JLabel("				"));
        panel34->layout()->addWidget(setB2TToTHead);
        setB2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel34->layout()->addWidget(new JLabel("  "));
        panel34->layout()->addWidget(setupB2TToTLogic);
        setupB2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel34);
        theContentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        //Signal heads located at turnout 2

        JPanel* panel41x = new JPanel(new FlowLayout());
        panel41x->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " 2 - "
                + tr("continuing track")));
        theContentPaneLayout->addWidget(panel41x);

        JPanel* panel41 = new JPanel(new FlowLayout());
        panel33->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 1 - "
                + tr("continuing track"))));
        panel41->layout()->addWidget(c1TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel41);
        c1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel42 = new JPanel(new FlowLayout());
        panel42->layout()->addWidget(new JLabel(tr("Or Both") + " 1 " + tr("Tracks)") + "	  "));
        panel42->layout()->addWidget(setC1TToTHead);
        setC1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel42->layout()->addWidget(new JLabel("  "));
        panel42->layout()->addWidget(setupC1TToTLogic);
        setupC1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel42);

        JPanel* panel43 = new JPanel(new FlowLayout());
        panel43->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 1 - "
                + tr("Protects Turnout"))));
        panel43->layout()->addWidget(c2TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel43);
        c2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel44 = new JPanel(new FlowLayout());
        panel44->layout()->addWidget(new JLabel("				"));
        panel44->layout()->addWidget(setC2TToTHead);
        setC2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel44->layout()->addWidget(new JLabel("  "));
        panel44->layout()->addWidget(setupC2TToTLogic);
        setupC2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel44);

        JPanel* panel51x = new JPanel(new FlowLayout());
        panel51x->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " 2 - "
                + tr("Protects Turnout")));
        theContentPaneLayout->addWidget(panel51x);

        JPanel* panel51 = new JPanel(new FlowLayout());
        panel51->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 1 - "
                + tr("continuing track"))));
        panel51->layout()->addWidget(d1TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel51);
        d1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel52 = new JPanel(new FlowLayout());
        panel52->layout()->addWidget(new JLabel(tr("Or Both") + " 1 " + tr("Tracks)") + "	  "));
        panel52->layout()->addWidget(setD1TToTHead);
        setD1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel52->layout()->addWidget(new JLabel("  "));
        panel52->layout()->addWidget(setupD1TToTLogic);
        setupD1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel52);

        JPanel* panel53 = new JPanel(new FlowLayout());
        panel53->layout()->addWidget(new JLabel(tr("%1").arg(
                tr("Protects Turnout") + " 1 - "
                + tr("Protects Turnout"))));
        panel53->layout()->addWidget(d2TToTSignalHeadComboBox);
        theContentPaneLayout->addWidget(panel53);
        d2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

        JPanel* panel54 = new JPanel(new FlowLayout());
        panel54->layout()->addWidget(new JLabel("				"));
        panel54->layout()->addWidget(setD2TToTHead);
        setD2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel54->layout()->addWidget(new JLabel("  "));
        panel54->layout()->addWidget(setupD2TToTLogic);
        setupD2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPaneLayout->addWidget(panel54);
        theContentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        JPanel* panel6 = new JPanel(new FlowLayout());
        panel6->layout()->addWidget(changeTToTSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
        //changeTToTSignalIcon.addActionListener((ActionEvent e) -> {
        connect(changeTToTSignalIcon, &QPushButton::clicked, [=]{
            signalFrame->setVisible(true);
        });
        changeTToTSignalIcon->setToolTip(tr("Select to change icons used to represent signal heads (Use left-facing icons)"));
        panel6->layout()->addWidget(new JLabel("	 "));
        panel6->layout()->addWidget(setTToTSignalsDone = new QPushButton(tr("Done")));
        //setTToTSignalsDone.addActionListener((ActionEvent e) -> {
        connect(setTToTSignalsDone, &QPushButton::clicked, [=]{
            setTToTSignalsDonePressed();
        });
        setTToTSignalsDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.eHint").arg(tr("Done")));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
#if 0
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(setTToTSignalsDone);
            rootPane.setDefaultButton(setTToTSignalsDone);
        });
#else
        setTToTSignalsDone->setDefault(true);
#endif
        panel6->layout()->addWidget(setTToTSignalsCancel = new QPushButton(tr("Cancel")));
        //setTToTSignalsCancel.addActionListener((ActionEvent e) -> {
        connect(setTToTSignalsCancel, &QPushButton::clicked, [=]{
            setTToTSignalsCancelPressed();
        });
        setTToTSignalsCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPaneLayout->addWidget(panel6);
#if 0
        setSignalsAtThroatToThroatTurnoutsFrame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                setTToTSignalsCancelPressed(null);
            }
        });
#else
        class MyWindowListener : public WindowListener
        {
         LayoutEditorTools* let;
        public:
         MyWindowListener(LayoutEditorTools* let) {this->let = let;}
         void windowClosing(QCloseEvent *)
         {
          let->setTToTSignalsCancelPressed();
         }
        };
#endif
    }
    setPlaceAllHeads->setChecked(false);
    setupAllLogic->setChecked(false);

    turnout1ComboBox->setVisible(!setSignalsAtThroatToThroatTurnoutsFromMenuFlag);
    turnout2ComboBox->setVisible(!setSignalsAtThroatToThroatTurnoutsFromMenuFlag);

    if (setSignalsAtThroatToThroatTurnoutsFromMenuFlag) {
        ttotTurnoutName1Label->setText(tr("%1").arg(
                tr("Turnout") + " 1 "
                + tr("Name")) + ttotTurnoutName1);
        ttotTurnoutName2Label->setText(tr("%1").arg(
                tr("Turnout") + " 2 "
                + tr("Name")) + ttotTurnoutName2);

//        SwingUtilities.invokeLater(() -> {
            setSignalsAtTToTTurnoutsGetSaved();
//        });
    } else {
        ttotTurnoutName1Label->setText(
                tr("Turnout") + " 1 "
                + tr("Name"));
        ttotTurnoutName2Label->setText(
                tr("Turnout") + " 2 "
                + tr("Name"));
    }

    if (!setSignalsAtThroatToThroatTurnoutsOpenFlag) {
        //setSignalsAtThroatToThroatTurnoutsFrame->resize(QSize());
        setSignalsAtThroatToThroatTurnoutsFrame->pack();
        setSignalsAtThroatToThroatTurnoutsOpenFlag = true;
    }
    setSignalsAtThroatToThroatTurnoutsFrame->setVisible(true);
}   //setSignalsAtTToTTurnouts

/*private*/ void LayoutEditorTools::setSignalsAtTToTTurnoutsGetSaved(/*ActionEvent* a*/) {
    if (!getTToTTurnoutInformation()) {
        return;
    }
    a1TToTSignalHeadComboBox->setSelectedItem(layoutTurnout1->getSignalB1());
    a2TToTSignalHeadComboBox->setSelectedItem(layoutTurnout1->getSignalB2());
    b1TToTSignalHeadComboBox->setSelectedItem(layoutTurnout1->getSignalC1());
    b2TToTSignalHeadComboBox->setSelectedItem(layoutTurnout1->getSignalC2());
    c1TToTSignalHeadComboBox->setSelectedItem(layoutTurnout2->getSignalB1());
    c2TToTSignalHeadComboBox->setSelectedItem(layoutTurnout2->getSignalB2());
    d1TToTSignalHeadComboBox->setSelectedItem(layoutTurnout2->getSignalC1());
    d2TToTSignalHeadComboBox->setSelectedItem(layoutTurnout2->getSignalC2());
}

/*private*/ void LayoutEditorTools::setTToTSignalsCancelPressed(/*ActionEvent a*/) {
    setSignalsAtThroatToThroatTurnoutsOpenFlag = false;
    setSignalsAtThroatToThroatTurnoutsFrame->setVisible(false);
}

/**
 * Tool to set signals at a turnout, including placing the signal icons and
 *		optionally setup of Simple Signal Logic for each signal head
 * <P>
 * This tool assumes left facing signal head icons have been selected, and
 *		will rotate the signal head icons accordingly.
 * <P>
 * This tool will place throat icons on the right side of the track, and
 *		continuing and diverging icons on the outside edge of the turnout.
 * <P>
 * This tool only places signal icons if the turnout is either mostly vertical
 *		or mostly horizontal. Some user adjustment may be needed.
 */

// display dialog for Set Signals at Turnout tool
/*public*/ void LayoutEditorTools::setSignalsAtTurnoutFromMenu( LayoutTurnout* to,
                MultiIconEditor* theEditor, JFrame* theFrame )
{
//    turnoutFromMenu = true;
    layoutTurnout = to;
    turnout = to->getTurnout();
    turnoutComboBox->setSelectedItem(to->getTurnout());
    setSignalsAtTurnoutFromMenuFlag = true;
    setSignalsAtTurnout(theEditor, theFrame);
    setSignalsAtTurnoutFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAtTurnout( MultiIconEditor* theEditor, JFrame* theFrame )
{
 signalIconEditor = theEditor;
 signalFrame = theFrame;
 if (setSignalsOpen)
 {
  setSignalsFrame->setVisible(true);
  return;
 }
 // Initialize if needed
 if (setSignalsFrame == nullptr)
 {
  setSignalsFrame = new JmriJFrameX(tr("Signals At Turnout"), false, true);
  setSignalsFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtTurnout", true);
  setSignalsFrame->setLocation(70,30);
  //Container theContentPane = setSignalsFrame.getContentPane();
  QFont font;
  font.setPointSize(8);
  setSignalsFrame->setFont(font);
  QWidget* theContentPane = new QWidget();
  QVBoxLayout* centralWidgetLayout;
  theContentPane->setLayout(centralWidgetLayout = new QVBoxLayout(theContentPane/*, BoxLayout.Y_AXIS)*/));
  setSignalsFrame->setCentralWidget(theContentPane);
  QWidget* panel1 = new QWidget();
  panel1->setLayout(new QHBoxLayout());
  if (turnoutFromMenu)
  {
   QLabel* turnoutNameLabel = new QLabel( tr("Turnout")+" "+
                tr("Name")+" : "+layoutTurnout->getTurnoutName());
            panel1->layout()->addWidget(turnoutNameLabel);
  }
  else
  {
   QLabel* turnoutNameLabel = new QLabel( tr("Turnout")+" "+
                                                    tr("Name") );
   panel1->layout()->addWidget(turnoutNameLabel);
   panel1->layout()->addWidget(turnoutComboBox);
   turnoutComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
  }
  centralWidgetLayout->addWidget(panel1);
  QFrame* line = new QFrame();
  line->setObjectName(QString::fromUtf8("line"));
  line->setGeometry(QRect(10, 30, 571, 16));
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  centralWidgetLayout->addWidget(line);
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Heads"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedSignalHeads = new QPushButton(tr("Get Saved")));
//        getSavedSignalHeads->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    turnoutSignalsGetSaved(e);
//                }
//            });
  connect(getSavedSignalHeads, SIGNAL(clicked()), this, SLOT(turnoutSignalsGetSaved()));
  getSavedSignalHeads->setToolTip( tr("Click to retrieve signal heads previously stored.") );
  centralWidgetLayout->addWidget(panel2);
  QWidget* panel21 = new QWidget();
  panel21->setLayout(new QHBoxLayout());
  QLabel* throatContinuingLabel = new QLabel(tr("Throat - Continuing")+" : ");
  panel21->layout()->addWidget(throatContinuingLabel);
  panel21->layout()->addWidget(throatContinuingSignalHeadComboBox);
  centralWidgetLayout->addWidget(panel21);
  throatContinuingSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
  QWidget* panel22 = new QWidget();
  panel22->setLayout(new QHBoxLayout());
  panel22->layout()->addWidget(new QLabel("   "));
  panel22->layout()->addWidget(setThroatContinuing);
  setThroatContinuing->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
  panel22->layout()->addWidget(new QLabel("  "));
  panel22->layout()->addWidget(setupLogicThroatContinuing);
  setupLogicThroatContinuing->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
  centralWidgetLayout->addWidget(panel22);
  QWidget* panel31 = new QWidget();
  panel31->setLayout(new QHBoxLayout());
  QLabel* throatDivergingLabel = new QLabel(tr("Throat - Diverging")+" : ");
  panel31->layout()->addWidget(throatDivergingLabel);
  panel31->layout()->addWidget(throatDivergingSignalHeadComboBox);
  centralWidgetLayout->addWidget(panel31);
  throatDivergingSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
  QWidget* panel32 = new QWidget();
  panel32->setLayout(new QHBoxLayout());
  panel32->layout()->addWidget(new QLabel("   "));
  panel32->layout()->addWidget(setThroatDiverging);
  setThroatDiverging->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
  panel32->layout()->addWidget(new QLabel("  "));
  panel32->layout()->addWidget(setupLogicThroatDiverging);
  setupLogicThroatDiverging->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
  centralWidgetLayout->addWidget(panel32);
  QWidget* panel41 = new QWidget();
  panel41->setLayout(new QHBoxLayout());
  QLabel* continuingLabel = new QLabel(tr("Continuing")+" : ");
  panel41->layout()->addWidget(continuingLabel);
  panel41->layout()->addWidget(continuingSignalHeadComboBox);
  centralWidgetLayout->addWidget(panel41);
  continuingSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
  QWidget* panel42 = new QWidget();
  panel42->setLayout(new QHBoxLayout());
  panel42->layout()->addWidget(new QLabel("   "));
  panel42->layout()->addWidget(setContinuing);
  setContinuing->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
  panel42->layout()->addWidget(new QLabel("  "));
  panel42->layout()->addWidget(setupLogicContinuing);
  setupLogicContinuing->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
  centralWidgetLayout->addWidget(panel42);
  QWidget* panel51 = new QWidget();
  panel51->setLayout(new QHBoxLayout());
  QLabel* divergingLabel = new QLabel(tr("Diverging")+" : ");
  panel51->layout()->addWidget(divergingLabel);
  panel51->layout()->addWidget(divergingSignalHeadComboBox);
  centralWidgetLayout->addWidget(panel51);
  divergingSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
  QWidget* panel52 = new QWidget();
  panel52->setLayout(new QHBoxLayout());
  panel52->layout()->addWidget(new QLabel("   "));
  panel52->layout()->addWidget(setDiverging);
  setDiverging->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
  panel52->layout()->addWidget(new QLabel("  "));
  panel52->layout()->addWidget(setupLogicDiverging);
  setupLogicDiverging->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
  centralWidgetLayout->addWidget(panel52);
  QFrame* line2 = new QFrame();
  line2->setObjectName(QString::fromUtf8("line"));
  line2->setGeometry(QRect(10, 30, 571, 16));
  line2->setFrameShape(QFrame::HLine);
  line2->setFrameShadow(QFrame::Sunken);
  centralWidgetLayout->addWidget(line2);
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());
  panel6->layout()->addWidget(changeSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
//    changeSignalIcon->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
  connect(changeSignalIcon, &QPushButton::clicked, [=]{
                signalFrame->setVisible(true);
//            }
        });
  changeSignalIcon->setToolTip( tr("Click to change icons used to represent signal heads. (Use left-facing icons.)") );
  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setSignalsDone = new QPushButton(tr("Done")));
//    setSignalsDone->layout()->addWidgetActionListener(new ActionListener() {
  connect(setSignalsDone, &QPushButton::clicked, [=]{
//        /*public*/ void actionPerformed(ActionEvent e) {
            setSignalsDonePressed(/*e*/);
//        }
    });
  setSignalsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
  panel6->layout()->addWidget(setSignalsCancel = new QPushButton(tr("Cancel")));
//    setSignalsCancel->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setSignalsCancelPressed(e);
//        }
//    });
 connect(setSignalsCancel, SIGNAL(clicked()), this, SLOT(setSignalsCancelPressed()));
 setSignalsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
 centralWidgetLayout->addWidget(panel6);
//    setSignalsFrame->addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            setSignalsCancelPressed(nullptr);
//        }
//    });
 setSignalsFrame->addWindowListener(new SSFWindowListener(this));
 if (turnoutFromMenu) turnoutSignalsGetSaved(nullptr);
 }
 //setSignalsFrame.pack();
 setSignalsFrame->setVisible(true);
 setSignalsOpen = true;
}
void LayoutEditorTools::windowClosing(QCloseEvent* /*e*/)
{
 if(setSignalsCancel !=NULL && setSignalsOpen)
  setSignalsCancelPressed();

}

/*private*/ void LayoutEditorTools::turnoutSignalsGetSaved (JActionEvent* /*a*/) // SLOT[]
{
 if (getTurnoutInformation(false)) {
     throatContinuingSignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalA1());
     throatDivergingSignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalA2());
     continuingSignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalB1());
     divergingSignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalC1());
 }
}

/*private*/ void LayoutEditorTools::setSignalsCancelPressed (JActionEvent* /*a*/) // SLOT[]
{
 setSignalsOpen = false;
 turnoutFromMenu = false;
 setSignalsFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setSignalsDonePressed (JActionEvent* /*a*/) // SLOT[]
{
 // process turnout name
 if ( !getTurnoutInformation(false) )
  return;

 // process signal head names
 if ( !getTurnoutSignalHeadInformation() )
  return;

 // place signals as requested
 QString signalHeadName = throatContinuingSignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 if (setThroatContinuing->isChecked())
 {
  if (isHeadOnPanel(throatContinuingHead) &&
    (throatContinuingHead!=getHeadFromName(layoutTurnout->getSignalA1Name())))
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
             signalHeadName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);
    return;
  }
  else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) )
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

   if (throatContinuingHead!=getHeadFromName(layoutTurnout->getSignalA1Name()))
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
    removeAssignment(throatContinuingHead);
    layoutTurnout->setSignalA1Name(signalHeadName);
   }
  }
  else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
   placeThroatContinuing();
   removeAssignment(throatContinuingHead);
   layoutTurnout->setSignalA1Name(signalHeadName);
   needRedraw = true;
  }
 }
 else
 {
  int assigned = isHeadAssignedHere(throatContinuingHead,layoutTurnout);
  if (assigned == NONE)
  {
   if ( isHeadOnPanel(throatContinuingHead) &&
                        isHeadAssignedAnywhere(throatContinuingHead) )
   {
        JOptionPane::showMessageDialog(setSignalsFrame,
            tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                signalHeadName),
                    tr("Error"),JOptionPane::ERROR_MESSAGE);
    return;
   }
   else
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
    removeAssignment(throatContinuingHead);
    layoutTurnout->setSignalA1Name(signalHeadName);
   }
  }
//  else if (assigned!=A1)
//  {
//   // need to figure out what to do in this case.
//  }
 }
 signalHeadName = throatDivergingSignalHeadComboBox->getSelectedItemDisplayName();
 if ( (setThroatDiverging->isChecked()) && (throatDivergingHead!=nullptr) )
 {
  if (isHeadOnPanel(throatDivergingHead) &&
    (throatDivergingHead!=getHeadFromName(layoutTurnout->getSignalA2Name())))
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
          signalHeadName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);
   return;
  }
  else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) )
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

  if (throatDivergingHead!=getHeadFromName(layoutTurnout->getSignalA2Name()))
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
   removeAssignment(throatDivergingHead);
   layoutTurnout->setSignalA2Name(signalHeadName);
  }
 }
 else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
   placeThroatDiverging();
   removeAssignment(throatDivergingHead);
   layoutTurnout->setSignalA2Name(signalHeadName);
   needRedraw = true;
  }
 }
 else if (throatDivergingHead!=nullptr) {
 int assigned = isHeadAssignedHere(throatDivergingHead,layoutTurnout);
 if (assigned == NONE)
 {
  if (isHeadOnPanel(throatDivergingHead) &&
                        isHeadAssignedAnywhere(throatDivergingHead) ) {
   JOptionPane::showMessageDialog(setSignalsFrame,
            tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                signalHeadName),
                    tr("Error"),JOptionPane::ERROR_MESSAGE);
  return;
 }
 else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
   removeAssignment(throatDivergingHead);
   layoutTurnout->setSignalA2Name(signalHeadName);
  }
 }
// else if (assigned!=A2)
// {
//  // need to figure out what to do in this case.
// }
}
else if (throatDivergingHead==nullptr)
 {
  removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
  layoutTurnout->setSignalA2Name("");
 }

 signalHeadName = continuingSignalHeadComboBox->getSelectedItemDisplayName();
 if (setContinuing->isChecked())
 {
  if (isHeadOnPanel(continuingHead) &&
    (continuingHead!=getHeadFromName(layoutTurnout->getSignalB1Name())))
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
            signalHeadName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);
   return;
  }
  else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) )
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

   if (continuingHead!=getHeadFromName(layoutTurnout->getSignalB1Name()))
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
    removeAssignment(continuingHead);
    layoutTurnout->setSignalB1Name(signalHeadName);
   }
  }
  else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
    if (layoutTurnout->getContinuingSense()==Turnout::CLOSED)
        placeContinuing(signalHeadName);
    else
        placeDiverging(signalHeadName);
    removeAssignment(continuingHead);
    layoutTurnout->setSignalB1Name(signalHeadName);
    needRedraw = true;
  }
 }
 else
 {
  int assigned = isHeadAssignedHere(continuingHead,layoutTurnout);
  if (assigned == NONE)
  {
   if (isHeadOnPanel(continuingHead)  &&
                        isHeadAssignedAnywhere(continuingHead) )
   {
        JOptionPane::showMessageDialog(setSignalsFrame,
            tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                signalHeadName),
                    tr("Error"),JOptionPane::ERROR_MESSAGE);

    return;
   }
   else
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
    removeAssignment(continuingHead);
    layoutTurnout->setSignalB1Name(signalHeadName);
   }
  }
//  else if (assigned!=B1)
//  {
//   // need to figure out what to do in this case.
//  }
 }

 signalHeadName = divergingSignalHeadComboBox->getSelectedItemDisplayName();
 if (setDiverging->isChecked())
 {
  if (isHeadOnPanel(divergingHead) &&
    (divergingHead!=getHeadFromName(layoutTurnout->getSignalC1Name())))
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
            signalHeadName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);
   return;
  }
  else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) )
  {
    JOptionPane::showMessageDialog(setSignalsFrame,
        tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

   if (divergingHead!=getHeadFromName(layoutTurnout->getSignalC1Name()))
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
    removeAssignment(divergingHead);
    layoutTurnout->setSignalC1Name(signalHeadName);
   }
  }
  else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
    if (layoutTurnout->getContinuingSense()==Turnout::CLOSED)
        placeDiverging(signalHeadName);
    else
        placeContinuing(signalHeadName);
    removeAssignment(divergingHead);
    layoutTurnout->setSignalC1Name(signalHeadName);
    needRedraw = true;
  }
 }
 else
 {
  int assigned = isHeadAssignedHere(divergingHead,layoutTurnout);
  if (assigned == NONE)
  {
   if (isHeadOnPanel(divergingHead) &&
                        isHeadAssignedAnywhere(divergingHead) )
   {
        JOptionPane::showMessageDialog(setSignalsFrame,
            tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                signalHeadName),
                    tr("Error"),JOptionPane::ERROR_MESSAGE);

    return;
   }
   else
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
    removeAssignment(divergingHead);
    layoutTurnout->setSignalC1Name(signalHeadName);
   }
  }
//  else if (assigned!=C1)
//  {
//   // need to figure out what to do in this case.
//  }
 }
 // setup Logic if requested and enough information is available
 if (setupLogicThroatContinuing->isChecked())
 {
  setLogicThroatContinuing();
 }
 if ( (throatDivergingHead!=nullptr) && setupLogicThroatDiverging->isChecked() )
 {
  setLogicThroatDiverging();
 }
 if (setupLogicContinuing->isChecked())
 {
  setLogicContinuing();
 }
 if ( setupLogicDiverging->isChecked() )
 {
  setLogicDiverging();
 }
 // make sure this layout turnout is not linked to another
 layoutTurnout->setLinkType(LayoutTurnout::NO_LINK);
 layoutTurnout->setLinkedTurnoutName("");
 // finish up
 setSignalsOpen = false;
 turnoutFromMenu = false;
 setSignalsFrame->setVisible(false);
 if (needRedraw) {
 layoutEditor->redrawPanel();
 needRedraw = false;
 layoutEditor->setDirty();
 }
}
/*private*/ bool LayoutEditorTools::getTurnoutInformation(bool isCrossover)
{
 QString str = "";
 if ((!setSignalsAtTurnoutFromMenuFlag && !isCrossover)
         || (!setSignalsAtXoverTurnoutFromMenuFlag && isCrossover)) {
     turnout = nullptr;
     layoutTurnout = nullptr;
     if (isCrossover) {
         str = NamedBean::normalizeUserName(xoverTurnoutName);
     } else {
         str = turnoutComboBox->currentText();
     }
     if ((str == "") || str.isEmpty()) {
         JOptionPane::showMessageDialog(layoutEditor, tr("Error - No turnout name was entered. Please enter a turnout name or cancel."),
                 tr("Error"), JOptionPane::ERROR_MESSAGE);
         return false;
     }
     turnout = InstanceManager::turnoutManagerInstance()->getTurnout(str);
     if (turnout == nullptr) {
         JOptionPane::showMessageDialog(layoutEditor,
                 tr("Error - No turnout is defined for \"%1\". Please enter\na turnout name in the Turnout Table and on the panel.").arg(str),
                         tr("ErrorTitle"),
                 JOptionPane::ERROR_MESSAGE);
         return false;
     } else {
         QString uname = turnout->getUserName();
         if ((uname == nullptr) || uname.isEmpty() || uname!=(str)) {
             str = str.toUpper();
             if (isCrossover) {
                 xoverTurnoutName = str;
             } else {
                 turnoutComboBox->setSelectedItem(turnout);
             }
         }
     }
     for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
      LayoutTurnout* t = (LayoutTurnout*)lt;
         if (t->getTurnout() == turnout) {
             layoutTurnout = t;
             if (((t->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
                     || (t->getTurnoutType() == LayoutTurnout::RH_XOVER)
                     || (t->getTurnoutType() == LayoutTurnout::LH_XOVER))
                     && (!isCrossover)) {
                 JOptionPane::showMessageDialog(layoutEditor,
                         tr("Sorry, this tool does\nnot work with crossover turnouts."), "",
                         JOptionPane::INFORMATION_MESSAGE);
                 setSignalsCancelPressed(nullptr);
                 return false;
             }
             if ((!((t->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
                     || (t->getTurnoutType() == LayoutTurnout::RH_XOVER)
                     || (t->getTurnoutType() == LayoutTurnout::LH_XOVER)))
                     && isCrossover) {
                 JOptionPane::showMessageDialog(layoutEditor,
                         tr("Sorry, Set Signal Heads at Crossover does\nnot work with other types of turnouts."), "",
                         JOptionPane::INFORMATION_MESSAGE);
                 setXoverSignalsCancelPressed(nullptr);
                 return false;
             }
         }
     }
 }

 if (layoutTurnout != nullptr) {
     if (isCrossover) {
         QPointF coordsA = layoutTurnout->getCoordsA();
         QPointF coordsB = layoutTurnout->getCoordsB();
         placeSignalDirectionDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsA));
     } else {
         QPointF coordsA = layoutTurnout->getCoordsA();
         QPointF coordsCenter = layoutTurnout->getCoordsCenter();
         placeSignalDirectionDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsCenter, coordsA));
     }
     return true;
 }
 JOptionPane::showMessageDialog(layoutEditor,
         tr("Error - Turnout \"%1\" is not drawn on the panel.\nPlease enter the name of a drawn turnout.").arg(str),
                  tr("Error"),
         JOptionPane::ERROR_MESSAGE);
 return false;
}   // getTurnoutInformation}

/*private*/ bool LayoutEditorTools::getTurnoutSignalHeadInformation()
{
 throatContinuingHead = getSignalHeadFromEntry(throatContinuingSignalHeadComboBox, true, setSignalsAtTurnoutFrame);
 if (throatContinuingHead == nullptr) {
     return false;
 }
 throatDivergingHead = getSignalHeadFromEntry(throatDivergingSignalHeadComboBox, false, setSignalsAtTurnoutFrame);
 continuingHead = getSignalHeadFromEntry(continuingSignalHeadComboBox, true, setSignalsAtTurnoutFrame);
 if (continuingHead == nullptr) {
     return false;
 }
 divergingHead = getSignalHeadFromEntry(divergingSignalHeadComboBox, true, setSignalsAtTurnoutFrame);
 if (divergingHead == nullptr) {
     return false;
 }
 return true;
}

/*private*/ void LayoutEditorTools::placeThroatContinuing()
{
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = throatContinuingSignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsA = layoutTurnout->getCoordsA();
 QPointF delta = QPointF(+shift, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsA, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeThroatDiverging() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = throatDivergingSignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsA = layoutTurnout->getCoordsA();
 QPointF delta = QPointF(-shift, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsA, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::placeContinuing(QString signalHeadName)
{
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsB = layoutTurnout->getCoordsB();
 QPointF coordsC = layoutTurnout->getCoordsC();
 QPointF coordsCenter = layoutTurnout->getCoordsCenter();

 double bDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsCenter));
 double cDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsCenter));
 double diffDirDEG = MathUtil::diffAngleDEG(cDirDEG, bDirDEG);
 double shiftX = 0.0;
 if (diffDirDEG < 0.0) {
     shiftX += shift * qCos(qDegreesToRadians(diffDirDEG));
 }
 QPointF delta = QPointF(shiftX, -shift);

 delta = MathUtil::rotateDEG(delta, bDirDEG);
 QPointF where = MathUtil::add(coordsB, delta);
 setSignalHeadOnPanel(bDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeDiverging(QString signalHeadName) {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsB = layoutTurnout->getCoordsB();
 QPointF coordsC = layoutTurnout->getCoordsC();
 QPointF coordsCenter = layoutTurnout->getCoordsCenter();

 double bDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsCenter));
 double cDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsCenter));
 double diffDirDEG = MathUtil::diffAngleDEG(cDirDEG, bDirDEG);
 double shiftX = 0.0;
 if (diffDirDEG >= 0.0) {
     shiftX += shift * qCos(qDegreesToRadians(diffDirDEG));
 }
 QPointF delta = QPointF(shiftX, -shift);

 delta = MathUtil::rotateDEG(delta, cDirDEG);
 QPointF where = MathUtil::add(coordsC, delta);
 setSignalHeadOnPanel(cDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::setLogicThroatContinuing() {
    TrackSegment* track = nullptr;
    if (layoutTurnout->getContinuingSense()==Turnout::CLOSED)
        track = (TrackSegment*)layoutTurnout->getConnectB();
    else
        track = (TrackSegment*)layoutTurnout->getConnectC();
    if (track==nullptr)
    {
        JOptionPane::showMessageDialog(setSignalsFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr)
    {
        JOptionPane::showMessageDialog(setSignalsFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));

     return;
    }

    QString signalHeadName = throatContinuingSignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track,
            layoutTurnout, signalHeadName, setSignalsFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) )
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
     return;
    }
    if (throatDivergingHead!=nullptr)
    {
     if (!initializeBlockBossLogic(signalHeadName)) return;
        logic->setMode(BlockBossLogic::TRAILINGMAIN);
        logic->setTurnout(turnout->getSystemName());
        logic->setSensor1(occupancy->getSystemName());
        if (nextHead!=nullptr) {
            logic->setWatchedSignal1(nextHead->getSystemName(),false);
        }
        if (auxSignal!=nullptr) {
            logic->setWatchedSignal1Alt(auxSignal->getSystemName());
        }
        finalizeBlockBossLogic();
        return;
    }
    SignalHead* savedAuxSignal = auxSignal;
    TrackSegment* track2 = NULL;
    if (layoutTurnout->getContinuingSense()==Turnout::CLOSED)
        track2 = (TrackSegment*)layoutTurnout->getConnectC();
    else
        track2 = (TrackSegment*)layoutTurnout->getConnectB();
    if (track2==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));

     return;
    }
    LayoutBlock* block2 = track2->getLayoutBlock();
    if (block2==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));

     return;
    }
    Sensor* occupancy2 = block2->getOccupancySensor();
    if (occupancy2==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block2.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block2->getUserName()));

     return;
    }

    signalHeadName = throatContinuingSignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead2 = getNextSignalFromObject(track2,
            layoutTurnout, signalHeadName, setSignalsFrame);
    if ( (nextHead2==nullptr) && (!reachedEndBumper()) )
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block2.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block2->getUserName()));

        return;
    }
    if (!initializeBlockBossLogic(signalHeadName)) return;
    logic->setMode(BlockBossLogic::FACING);
    logic->setTurnout(turnout->getSystemName());
    logic->setWatchedSensor1(occupancy->getSystemName());
    logic->setWatchedSensor2(occupancy2->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (savedAuxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(savedAuxSignal->getSystemName());
    }
    if (nextHead2!=nullptr) {
        logic->setWatchedSignal2(nextHead2->getSystemName());
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal2Alt(auxSignal->getSystemName());
    }
    if (!layoutTurnout->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::setLogicThroatDiverging()
{
    TrackSegment* track = NULL;
    if (layoutTurnout->getContinuingSense()==Turnout::CLOSED)
        track = (TrackSegment*)layoutTurnout->getConnectC();
    else
        track = (TrackSegment*)layoutTurnout->getConnectB();
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
     return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
     return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."));
     return;
    }

    QString signalHeadName = throatDivergingSignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track,
            layoutTurnout, signalHeadName, setSignalsFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) )
    {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
     return;
    }
    if (!initializeBlockBossLogic(signalHeadName)) return;
    logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
    logic->setTurnout(turnout->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr)
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    if (!layoutTurnout->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::setLogicContinuing()
{
 TrackSegment* track = (TrackSegment*)layoutTurnout->getConnectA();
 if (track==nullptr)
 {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
  return;
 }
 LayoutBlock* block = track->getLayoutBlock();
 if (block==nullptr)
 {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because blocks have\n                                                                     not been defined around this item."));
  return;
 }
 Sensor* occupancy = block->getOccupancySensor();
 if (occupancy==nullptr)
 {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
  return;
 }

 QString signalHeadName = continuingSignalHeadComboBox->getSelectedItemDisplayName();
 SignalHead* nextHead = getNextSignalFromObject(track,
                layoutTurnout, signalHeadName, setSignalsFrame);
 if ( (nextHead==nullptr) && (!reachedEndBumper()) )
 {
//        JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
  return;
 }
 if (!initializeBlockBossLogic(signalHeadName)) return;
 logic->setMode(BlockBossLogic::TRAILINGMAIN);
 logic->setTurnout(turnout->getSystemName());
 logic->setSensor1(occupancy->getSystemName());
 if (nextHead!=nullptr)
 {
  logic->setWatchedSignal1(nextHead->getSystemName(),false);
 }
 if (auxSignal!=nullptr)
 {
  logic->setWatchedSignal1Alt(auxSignal->getSystemName());
 }
 finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::setLogicDiverging()
{
 TrackSegment* track = (TrackSegment*)layoutTurnout->getConnectA();
 if (track==nullptr)
 {
//    JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
  return;
 }
 LayoutBlock* block = track->getLayoutBlock();
 if (block==nullptr)
 {
//    JOptionPane::showMessageDialog(setSignalsFrame,
//            tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
  return;
 }
 Sensor* occupancy = block->getOccupancySensor();
 if (occupancy==nullptr)
 {
//    JOptionPane::showMessageDialog(setSignalsFrame,
//        tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//            new Object[]{block->getUserName()}),
//                NULL,JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because block \"{0}\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
  return;
 }

 QString signalHeadName = divergingSignalHeadComboBox->getSelectedItemDisplayName();
 SignalHead* nextHead = getNextSignalFromObject(track,
        layoutTurnout, signalHeadName, setSignalsFrame);
 if ( (nextHead==nullptr) && (!reachedEndBumper()) )
 {
//    JOptionPane::showMessageDialog(setSignalsFrame,
//        tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//            new Object[]{block->getUserName()}),
//                NULL,JOptionPane::INFORMATION_MESSAGE);
  QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
  return;
 }
 if (!initializeBlockBossLogic(signalHeadName)) return;
 logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
 logic->setTurnout(turnout->getSystemName());
 logic->setSensor1(occupancy->getSystemName());
 if (nextHead!=nullptr)
 {
    logic->setWatchedSignal1(nextHead->getSystemName(),false);
 }
 if (auxSignal!=nullptr)
 {
    logic->setWatchedSignal1Alt(auxSignal->getSystemName());
 }
 if (!layoutTurnout->isMainlineC())
    logic->setLimitSpeed2(true);
 finalizeBlockBossLogic();
}

/**
 * Utility routines used by multiple tools
 */

/**
 * Returns the layout turnout corresponding to a given turnout.
 * If require double crossover is requested, and error message is sent to the user if the
 *		layout turnout is not a double crossover, and NULL is returned.
 * If a layout turnout corresponding to the turnout is not found, an error message
 *		is sent to the user and NULL is returned.
 */
/*public*/ LayoutTurnout* LayoutEditorTools::getLayoutTurnoutFromTurnout(Turnout* turnout, bool requireDoubleXover, QString str, JFrame* theFrame)
{
 LayoutTurnout* t = NULL;
 for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
  t = (LayoutTurnout*)lt;
  if (t->getTurnout() == turnout)
  {
   // have the layout turnout corresponding to the turnout
   if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) && (!requireDoubleXover) )
   {
//                javax->swing.JOptionPane::showMessageDialog(theFrame,
//                            tr("InfoMessage1"),"",
//                            javax->swing.JOptionPane::INFORMATION_MESSAGE);
    QMessageBox::information(theFrame, tr("information"), tr("Sorry, this tool does\nnot work with crossover turnouts."));

    return NULL;
   }
   if (requireDoubleXover && (t->getTurnoutType()!=LayoutTurnout::DOUBLE_XOVER) ) {
//                javax->swing.JOptionPane::showMessageDialog(theFrame,
//                            tr("InfoMessage8"),"",
//                            javax->swing.JOptionPane::INFORMATION_MESSAGE);
    QMessageBox::information(theFrame, tr("Information"), tr("Sorry, Set Signals at Crossover does\nnot work with other types of turnouts."));
    return NULL;
   }
   return t;
  }
 }
    // layout turnout not found
//    JOptionPane::showMessageDialog(theFrame,
//            tr("SignalsError3"),
//                    new Object[]{str}), tr("Error"),
//                        JOptionPane::ERROR_MESSAGE);
 QMessageBox::critical(theFrame, tr("Error"), tr("Error - Turnout \"%1\" is not drawn on the panel.\nPlease enter the name of a drawn turnout.").arg(str));
 return NULL;
}

/**
 * Returns the SignalHead corresponding to an entry field in the specified
 * dialog. This also takes care of UpperCase and trimming of leading and
 * trailing blanks. If entry is required, and no entry is present, and error
 * message is sent. An error message also results if a signal head with the
 * entered name is not found in the SignalTable.
 */
//@CheckReturnValue
/*public*/ SignalHead* LayoutEditorTools::getSignalHeadFromEntry(
        /*@Nonnull*/ NamedBeanComboBox/*<SignalHead>*/* signalNameComboBox,
        bool requireEntry,
        /*@Nonnull*/ JmriJFrame* frame) {
    QString signalName = signalNameComboBox->getSelectedItemDisplayName();
    SignalHead* result = getSignalHeadFromEntry(signalName, requireEntry, frame);
    if (result != nullptr) {
        QString uname = result->getUserName();
        if ((uname.isNull()) || uname.isEmpty() || uname!=(signalName)) {
            signalNameComboBox->setSelectedItem(result);
        }
    }
    return result;
}

/**
 * Returns the SignalHead* corresponding to an entry field in the specified dialog->
 *		This also takes care of UpperCase and trimming of leading and trailing blanks.
 *		If entry is required, and no entry is present, and error message is sent.
 *      An error message also results if a signal head with the entered name is not
 *      found in the SignalTable.
 */
/*public*/ SignalHead* LayoutEditorTools::getSignalHeadFromEntry(JTextField* signalName, bool requireEntry, JFrame* frame)
{
 QString str = signalName->text().trimmed();
 if ( (str==nullptr) || (str==("")) )
 {
  if (requireEntry)
  {
//            JOptionPane::showMessageDialog(frame,tr("SignalsError5"),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(frame, tr("Error"), tr("Error - Signal head name was not entered. Please enter\na signal head name for required positions or cancel."));
  }
  return NULL;
 }
 SignalHead* head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(str);
 if (head==nullptr)
 {
//        JOptionPane::showMessageDialog(frame,
//                tr("SignalsError4"),
//                    new Object[]{str}), tr("Error"),
//                        JOptionPane::ERROR_MESSAGE);
  QMessageBox::critical(0, tr("Error"), tr("Error - Signal head \"%1\" does not exist. Please correct name\nor enter this Signal Head in the Signal Table, and try again.").arg(str));
  return NULL ;
 }
 else if ( (head->getUserName()==nullptr) || (head->getUserName()==("")) ||
                                head->getUserName()!=(str) )
 {
//  str = str.toUpper();
  signalName->setText(str);
 }
 return (head);
}

//@CheckReturnValue
/*public*/ SignalHead* LayoutEditorTools::getSignalHeadFromEntry(/*@CheckForNull*/ QString signalName,
        bool requireEntry, /*@Nonnull*/ JmriJFrame* frame) {
    if ((signalName.isNull()) || signalName.isEmpty()) {
        if (requireEntry) {
            JOptionPane::showMessageDialog(frame, tr("Error - Signal head name was not entered. Please enter\na signal head name for required positions or cancel."),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
        }
        return nullptr;
    }
    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalName);
    if (head == nullptr) {
        JOptionPane::showMessageDialog(frame,
                tr("Error - Signal head \"%1\" does not exist. Please correct name\nor enter this Signal Head in the Signal Table, and try again.").arg(
                        signalName), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        return nullptr;
    }
    return (head);
}

/**
 * Returns a SignalHead* given a name
 */
/*public*/ SignalHead* LayoutEditorTools::getHeadFromName(QString str) {
    if ( (str==nullptr) || (str==("")) ) {
        return NULL;
    }
    return  (((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(str));
}

/**
 * Places a signal head icon on the panel after rotation at the designated
 * place, with all icons taken care of.
 *
 * @param directionDEG   rotation in degrees.
 * @param signalHeadName name of a signal head.
 * @param where          coordinates for placing signal head on panel.
 */
/*public*/ void LayoutEditorTools::setSignalHeadOnPanel(double directionDEG,
        /*@Nonnull*/ QString signalHeadName,
        /*@Nonnull*/ QPointF where) {
    setSignalHeadOnPanel(directionDEG, signalHeadName, (int) where.x(), (int) where.y());
}

/**
 * Places a signal head icon on the panel after rotation at the designated
 * place, with all icons taken care of.
 *
 * @param directionDEG   rotation in degrees.
 * @param signalHeadName name of a signal head.
 * @param xLoc           x coordinate for placing signal head on panel.
 * @param yLoc           y coordinate for placing signal head on panel.
 */
/*public*/ void LayoutEditorTools::setSignalHeadOnPanel(double directionDEG, /*@Nonnull */QString signalHeadName, int xLoc, int yLoc) {
    SignalHeadIcon* l = getSignalHeadIcon(signalHeadName);

    if (directionDEG > 0) {
        QListIterator<QString> e (l->getIconStateNames());
        while (e.hasNext()) {
            l->getIcon(e.next())->rotate((int) directionDEG, l);
        }
    }

    l->setLocation(xLoc - (int) (l->maxWidth() / 2.0), yLoc - (int) (l->maxHeight() / 2.0));

    layoutEditor->putSignal(l);
}

/**
 * Returns an index if the specified signal head is assigned to the
 *		LayoutTurnout initialized. Otherwise returns the NONE index->
 *		The index specifies the turnout position of the signal head
 *		according to the code listed at the beginning of this module.
 */
/*private*/ int LayoutEditorTools::isHeadAssignedHere(SignalHead* head, LayoutTurnout* lTurnout) {
    QString sysName = head->getSystemName();
    QString uName = head->getUserName();
    QString name = lTurnout->getSignalA1Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A1;
    name = lTurnout->getSignalA2Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A2;
    name = lTurnout->getSignalA3Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A3;
    name = lTurnout->getSignalB1Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return B1;
    name = lTurnout->getSignalB2Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return B2;
    name = lTurnout->getSignalC1Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return C1;
    name = lTurnout->getSignalC2Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return C2;
    name = lTurnout->getSignalD1Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return D1;
    name = lTurnout->getSignalD2Name();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return D2;
    return NONE;
}

/**
 * Returns true if an icon for the specified SignalHead* is on the panel
 */
/*public*/ bool LayoutEditorTools::isHeadOnPanel(SignalHead* head)
{
    SignalHeadIcon* h = NULL;
    for (int i=0;i<layoutEditor->signalList->size();i++) {
        h = layoutEditor->signalList->at(i);
        if (h->getSignalHead() == head) {
            return true;
        }
    }
    return false;
}
/**
 * Returns true if the specified Signal Head is assigned to an object
 *		on the panel, regardless of whether an icon is displayed or not
 */
/*public*/ bool LayoutEditorTools::isHeadAssignedAnywhere(SignalHead* head)
{
    QString sName = head->getSystemName();
    QString uName = head->getUserName();
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        LayoutTurnout* to = (LayoutTurnout*)lt;
        if ((to->getSignalA1Name()!=nullptr) &&
                (to->getSignalA1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA1Name()==(uName))))) return true;
        if ((to->getSignalA2Name()!=nullptr) &&
                (to->getSignalA2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA2Name()==(uName))))) return true;
        if ((to->getSignalA3Name()!=nullptr) &&
                (to->getSignalA3Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA3Name()==(uName))))) return true;
        if ((to->getSignalB1Name()!=nullptr) &&
                (to->getSignalB1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalB1Name()==(uName))))) return true;
        if ((to->getSignalB2Name()!=nullptr) &&
                (to->getSignalB2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalB2Name()==(uName))))) return true;
        if ((to->getSignalC1Name()!=nullptr) &&
                (to->getSignalC1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalC1Name()==(uName))))) return true;
        if ((to->getSignalC2Name()!=nullptr) &&
                (to->getSignalC2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalC2Name()==(uName))))) return true;
        if ((to->getSignalD1Name()!=nullptr) &&
                (to->getSignalD1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalD1Name()==(uName))))) return true;
        if ((to->getSignalD2Name()!=nullptr) &&
                (to->getSignalD2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalD2Name()==(uName))))) return true;
    }
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        PositionablePoint* po = (PositionablePoint*)lt;
        if ((po->getEastBoundSignal()!=nullptr) &&
                (po->getEastBoundSignal()==(sName) || ((uName!=nullptr) &&
                (po->getEastBoundSignal()==(uName))))) return true;
        if ((po->getWestBoundSignal()!=nullptr) &&
                (po->getWestBoundSignal()==(sName) || ((uName!=nullptr) &&
                (po->getWestBoundSignal()==(uName))))) return true;
    }
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        LevelXing* x = (LevelXing*)lt;
        if ((x->getSignalAName()!=nullptr) &&
                (x->getSignalAName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalAName()==(uName))))) return true;
        if ((x->getSignalBName()!=nullptr) &&
                (x->getSignalBName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalBName()==(uName))))) return true;
        if ((x->getSignalCName()!=nullptr) &&
                (x->getSignalCName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalCName()==(uName))))) return true;
        if ((x->getSignalDName()!=nullptr) &&
                (x->getSignalDName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalDName()==(uName))))) return true;
    }
    return false;
}
/**
 * Removes the assignment of the specified SignalHead* to either a turnout,
 *		a positionable point, or a level crossing wherever it is assigned
 */
/*public*/ void LayoutEditorTools::removeAssignment(SignalHead* head)
{
    QString sName = head->getSystemName();
    QString uName = head->getUserName();
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        LayoutTurnout* to = (LayoutTurnout*)lt;
        if ((to->getSignalA1Name()!=nullptr) &&
                (to->getSignalA1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA1Name()==(uName))))) to->setSignalA1Name("");
        if ((to->getSignalA2Name()!=nullptr) &&
                (to->getSignalA2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA2Name()==(uName))))) to->setSignalA2Name("");
        if ((to->getSignalA3Name()!=nullptr) &&
                (to->getSignalA3Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalA3Name()==(uName))))) to->setSignalA3Name("");
        if ((to->getSignalB1Name()!=nullptr) &&
                (to->getSignalB1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalB1Name()==(uName))))) to->setSignalB1Name("");
        if ((to->getSignalB2Name()!=nullptr) &&
                (to->getSignalB2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalB2Name()==(uName))))) to->setSignalB2Name("");
        if ((to->getSignalC1Name()!=nullptr) &&
                (to->getSignalC1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalC1Name()==(uName))))) to->setSignalC1Name("");
        if ((to->getSignalC2Name()!=nullptr) &&
                (to->getSignalC2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalC2Name()==(uName))))) to->setSignalC2Name("");
        if ((to->getSignalD1Name()!=nullptr) &&
                (to->getSignalD1Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalD1Name()==(uName))))) to->setSignalD1Name("");
        if ((to->getSignalD2Name()!=nullptr) &&
                (to->getSignalD2Name()==(sName) || ((uName!=nullptr) &&
                (to->getSignalD2Name()==(uName))))) to->setSignalD2Name("");
    }
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        PositionablePoint* po = (PositionablePoint*)lt;
        if ((po->getEastBoundSignal()!=nullptr) &&
                (po->getEastBoundSignal()==(sName) || ((uName!=nullptr) &&
                (po->getEastBoundSignal()==(uName)))))
            po->setEastBoundSignal("");
        if ((po->getWestBoundSignal()!=nullptr) &&
                (po->getWestBoundSignal()==(sName) || ((uName!=nullptr) &&
                (po->getWestBoundSignal()==(uName)))))
            po->setWestBoundSignal("");
    }
    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
        LevelXing* x = (LevelXing*)lt;
        if ((x->getSignalAName()!=nullptr) &&
                (x->getSignalAName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalAName()==(uName))))) x->setSignalAName("");
        if ((x->getSignalBName()!=nullptr) &&
                (x->getSignalBName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalBName()==(uName))))) x->setSignalBName("");
        if ((x->getSignalCName()!=nullptr) &&
                (x->getSignalCName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalCName()==(uName))))) x->setSignalCName("");
        if ((x->getSignalDName()!=nullptr) &&
                (x->getSignalDName()==(sName) || ((uName!=nullptr) &&
                (x->getSignalDName()==(uName))))) x->setSignalDName("");
    }
}

/**
 * Removes the SignalHead* with the specified name from the panel and from
 *		assignment to any turnout, positionable point, or level crossing
 */
//@SuppressWarnings("NULL")
/*public*/ void LayoutEditorTools::removeSignalHeadFromPanel(QString signalName) {
    if ( (signalName==nullptr) || (signalName.length()<1) ) return;
    SignalHead* head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                                    getSignalHead(signalName);
    removeAssignment(head);
    SignalHeadIcon* h = NULL;
    int index = -1;
    for (int i=0;(i<layoutEditor->signalList->size())&&(index==-1);i++) {
        h = layoutEditor->signalList->at(i);
        if (h->getSignalHead() == head) {
            index = i;
        }
    }
    if (index!=(-1)) {
        layoutEditor->signalList->remove(index);
        h->remove();
        h->dispose();
        needRedraw = true;
    }
}

/*
 * Initializes a BlockBossLogic for creation of a signal logic for the signal
 *		head named in "signalHeadName".
 * Should not be called until enough informmation has been gathered to allow
 *		configuration of the Simple Signal Logic.
 */
/*public*/ bool LayoutEditorTools::initializeBlockBossLogic(QString signalHeadName) {
    logic = BlockBossLogic::getStoppedObject(signalHeadName);
    if (logic==nullptr) {
        log->error("Trouble creating BlockBossLogic for '"+signalHeadName+"'.");
        return false;
    }
    return true;
}
/*
 * Finalizes a successfully created signal logic
 */
/*public*/ void LayoutEditorTools::finalizeBlockBossLogic() {
    if (logic==nullptr) return;
    logic->retain();
    logic->start();
    logic = NULL;
}

/*
 * Returns the signal head at the end of the block "track" is assigned to->
 *		"track" is the Track Segment leaving "object".
 *		"object" must be either an anchor point or one of the connecting
 *			points of a turnout or level crossing.
 * Note: returns 'NULL' is signal is not present where it is expected, or
 *		if an End Bumper is reached. To test for end bumper, use the
 *      associated routine "reachedEndBumper()". Reaching a turntable ray
 *		track connection is considered reaching an end bumper.
 * Note: Normally this routine requires a signal at any turnout it finds.
 *		However, if 'skipIncludedTurnout' is true, this routine will skip
 *		over an absent signal at an included turnout, that is a turnout
 *		with its throat track segment and its continuing track segment in
 *		the same block-> When this happens, the user is warned.
 */
/*public*/ SignalHead* LayoutEditorTools::getNextSignalFromObject(TrackSegment* track, QObject* object,
                            QString headName, JmriJFrame* frame) {
    hitEndBumper = false;
    auxSignal = NULL;
    TrackSegment* t = track;
    QObject* obj = object;
    bool inBlock = true;
    int type = 0;
    QObject* connect = NULL;
    while (inBlock) {
        if (t->getConnect1()==obj) {
            type = t->getType2();
            connect = t->getConnect2();
        }
        else {
            type = t->getType1();
            connect = t->getConnect1();
        }
        if (type==LayoutEditor::POS_POINT) {
            PositionablePoint* p = (PositionablePoint*)connect;
            if (p->getType()==PositionablePoint::END_BUMPER) {
                hitEndBumper = true;
                return NULL;
            }
            if (p->getConnect1()==t)
                t=p->getConnect2();
            else
                t=p->getConnect1();
            if (t==nullptr) return NULL;
            if (track->getLayoutBlock()!=t->getLayoutBlock()) {
                // p is a block boundary - should be signalled
                QString signalName;
                if (isAtWestEndOfAnchor(t,p))
                    signalName = p->getWestBoundSignal();
                else signalName = p->getEastBoundSignal();
                if ((signalName==nullptr)||(signalName==(""))) return NULL;
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalName);
            }
            obj = p;
        }
        else if (type==LayoutEditor::TURNOUT_A) {
            // Reached turnout throat, should be signalled
            LayoutTurnout* to = (LayoutTurnout*)connect;
            QString signalName = to->getSignalA2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            signalName = to->getSignalA1Name();
            if ((signalName==nullptr)||(signalName==(""))) {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(to,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, to->getTurnoutName(), headName);
                obj = to;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::TURNOUT_B) {
            // Reached turnout continuing, should be signalled
            LayoutTurnout* to = (LayoutTurnout*)connect;
            QString signalName = to->getSignalB2Name();
            if (to->getContinuingSense()==Turnout::THROWN)
                signalName = to->getSignalC2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            if (to->getContinuingSense()==Turnout::CLOSED)
                signalName = to->getSignalB1Name();
            else
                signalName = to->getSignalC1Name();
            if ((signalName==nullptr)||(signalName==("")))  {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(to,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, to->getTurnoutName(), headName);
                obj = to;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::TURNOUT_C) {
            // Reached turnout diverging, should be signalled
            LayoutTurnout* to = (LayoutTurnout*)connect;
            QString signalName = to->getSignalC2Name();
            if (to->getContinuingSense()==Turnout::THROWN)
                signalName = to->getSignalB2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            if (to->getContinuingSense()==Turnout::CLOSED)
                signalName = to->getSignalC1Name();
            else
                signalName = to->getSignalB1Name();
            if ((signalName==nullptr)||(signalName==("")))  {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(to,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, to->getTurnoutName(), headName);
                obj = to;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::TURNOUT_D) {
            // Reached turnout xover 4, should be signalled
            LayoutTurnout* to = (LayoutTurnout*)connect;
            QString signalName = to->getSignalD2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            signalName = to->getSignalD1Name();
            if ((signalName==nullptr)||(signalName==("")))   {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(to,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, to->getTurnoutName(), headName);
                obj = to;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::LEVEL_XING_A) {
            // Reached level crossing that may or may not be a block boundary
            LevelXing* x = (LevelXing*)connect;
            QString signalName = x->getSignalAName();
            if ((signalName!=nullptr)&&(signalName!=("")))
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            t=(TrackSegment*)x->getConnectC();
            if (t==nullptr) return NULL;
            if (track->getLayoutBlock()!=t->getLayoutBlock()) return NULL;
            obj = x;
        }
        else if (type==LayoutEditor::LEVEL_XING_B) {
            // Reached level crossing that may or may not be a block boundary
            LevelXing* x = (LevelXing*)connect;
            QString signalName = x->getSignalBName();
            if ((signalName!=nullptr)&&(signalName!=("")))
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->                                getSignalHead(signalName);
            t=(TrackSegment*)x->getConnectD();
            if (t==nullptr) return NULL;
            if (track->getLayoutBlock()!=t->getLayoutBlock()) return NULL;
            obj = x;
        }
        else if (type==LayoutEditor::LEVEL_XING_C) {
            // Reached level crossing that may or may not be a block boundary
            LevelXing* x = (LevelXing*)connect;
            QString signalName = x->getSignalCName();
            if ((signalName!=nullptr)&&(signalName!=("")))
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            t=(TrackSegment*)x->getConnectA();
            if (t==nullptr) return NULL;
            if (track->getLayoutBlock()!=t->getLayoutBlock()) return NULL;
            obj = x;
        }
        else if (type==LayoutEditor::LEVEL_XING_D) {
            // Reached level crossing that may or may not be a block boundary
            LevelXing* x = (LevelXing*)connect;
            QString signalName = x->getSignalDName();
            if ((signalName!=nullptr)&&(signalName!=("")))
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            t=(TrackSegment*)x->getConnectB();
            if (t==nullptr) return NULL;
            if (track->getLayoutBlock()!=t->getLayoutBlock()) return NULL;
            obj = x;
        }
        else if (type==LayoutEditor::SLIP_A) {
            LayoutSlip* sl = (LayoutSlip*)connect;
            QString signalName = sl->getSignalA2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            signalName = sl->getSignalA1Name();
            if ((signalName==nullptr)||(signalName==(""))) {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(sl,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, sl->getTurnoutName(), headName);
                obj = sl;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::SLIP_B) {
            LayoutSlip* sl = (LayoutSlip*)connect;
            QString signalName;
            if(sl->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                signalName = sl->getSignalB2Name();
                if ((!(signalName==nullptr))&&(!(signalName==(""))))
                    auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                    getSignalHead(signalName);
            }
            signalName = sl->getSignalB1Name();
            if ((signalName==nullptr)||(signalName==(""))) {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(sl,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, sl->getTurnoutName(), headName);
                obj = sl;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::SLIP_C) {
            LayoutSlip* sl = (LayoutSlip*)connect;
            QString signalName;
            if(sl->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                signalName = sl->getSignalC2Name();
                if ((!(signalName==nullptr))&&(!(signalName==(""))))
                    auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                    getSignalHead(signalName);
            }
            signalName = sl->getSignalC1Name();
            if ((signalName==nullptr)||(signalName==(""))) {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(sl,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, sl->getTurnoutName(), headName);
                obj = sl;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }
        else if (type==LayoutEditor::SLIP_D) {
            LayoutSlip* sl = (LayoutSlip*)connect;
            QString signalName = sl->getSignalD2Name();
            if ((!(signalName==nullptr))&&(!(signalName==(""))))
                auxSignal = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            signalName = sl->getSignalD1Name();
            if ((signalName==nullptr)||(signalName==(""))) {
                if (!layoutEditor->skipIncludedTurnout)
                    return NULL;
                t = getContinuingTrack(sl,type);
                if ( (t==nullptr) || (track->getLayoutBlock()!=t->getLayoutBlock()) )
                    return NULL;
                warnOfSkippedTurnout(frame, sl->getTurnoutName(), headName);
                obj = sl;
            }
            else {
                return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->
                                getSignalHead(signalName);
            }
        }

        else if (type>=LayoutEditor::TURNTABLE_RAY_OFFSET) {
            hitEndBumper = true;
            return NULL;
        }
    }
    return NULL;
}

/*private*/ void LayoutEditorTools::warnOfSkippedTurnout(JmriJFrame* frame, QString turnoutName, QString headName)
{
//    JOptionPane::showMessageDialog(frame,
//            tr("SignalsWarn2"),
//                new Object[]{turnoutName, headName}),
//                    NULL,JOptionPane::WARNING_MESSAGE);
    QMessageBox::warning(frame, tr("Warning"), tr("Warning - Per your instructions, the absense of signals at turnout \"%1\"\nwas ignored when setting up logic for signal head \"%2\".").arg(turnoutName).arg(headName));
}
/*private*/ TrackSegment* LayoutEditorTools::getContinuingTrack(LayoutTurnout* to, int type)	{
    int ty = to->getTurnoutType();
    if ( (ty==LayoutTurnout::RH_TURNOUT) || (ty==LayoutTurnout::LH_TURNOUT) ||
                                                (ty==LayoutTurnout::RH_TURNOUT) ) {
        if (type == LayoutEditor::TURNOUT_A) {
            if (to->getContinuingSense()==Turnout::CLOSED) return (TrackSegment*)to->getConnectB();
            else return (TrackSegment*)to->getConnectC();
        }
        else return (TrackSegment*)to->getConnectA();
    }
    else if ( (ty==LayoutTurnout::DOUBLE_XOVER) || (ty==LayoutTurnout::RH_XOVER) ||
                (ty==LayoutTurnout::LH_XOVER) ) {
        if (type==LayoutEditor::TURNOUT_A) return (TrackSegment*)to->getConnectB();
        else if (type==LayoutEditor::TURNOUT_B) return (TrackSegment*)to->getConnectA();
        else if (type==LayoutEditor::TURNOUT_C) return (TrackSegment*)to->getConnectD();
        else if (type==LayoutEditor::TURNOUT_D) return (TrackSegment*)to->getConnectC();
    }
    log->error("Bad connection type around turnout "+to->getTurnoutName());
    return NULL;
}

/*
 * Returns 'true' if an end bumper was reached during the last call to
 *		GetNextSignalFromObject. Also used in the odd case of reaching a
 *		turntable ray track connection, which is treated as an end
 *		bumper here.
 */
/*public*/ bool LayoutEditorTools::reachedEndBumper() {return hitEndBumper;}
/*
 * Returns 'true' if "track" enters a block boundary at the west(north) end of
 *		"point". Returns "false" otherwise. If track is neither horizontal or
 *      vertical, assumes horizontal, as done when setting signals at block boundary->
 *	"track" is a TrackSegment* connected to "point".
 *  "point" is an anchor point serving as a block boundary->
 */
/*static*/ /*public*/ bool LayoutEditorTools::isAtWestEndOfAnchor(TrackSegment* t, PositionablePoint* p)
{
 if (p->getType() == PositionablePoint::EDGE_CONNECTOR)
 {
  if (p->getConnect1() == t) {
      if (p->getConnect1Dir() == Path::NORTH || p->getConnect1Dir() == Path::WEST) {
          return false;
      }
      return true;
  } else {
      if (p->getConnect1Dir() == Path::NORTH || p->getConnect1Dir() == Path::WEST) {
          return true;
      }
      return false;
  }
 }

    TrackSegment* tx = NULL;
    if (p->getConnect1()==t)
        tx = p->getConnect2();
    else if (p->getConnect2() == t)
        tx = p->getConnect1();
    else {
        log->error("track not connected to anchor point");
        return false;
    }
    QPointF coords1;
    if (t->getConnect1()==p)
        coords1 = LayoutEditor::getCoords(t->getConnect2(),t->getType2());
    else
        coords1 = LayoutEditor::getCoords(t->getConnect1(),t->getType1());
    QPointF coords2;
    if(tx!=nullptr) {
        if (tx->getConnect1()==p)
            coords2 = LayoutEditor::getCoords(tx->getConnect2(),tx->getType2());
        else
            coords2 = LayoutEditor::getCoords(tx->getConnect1(),tx->getType1());
    } else {
        if (t->getConnect1()==p)
            coords2 = LayoutEditor::getCoords(t->getConnect1(),t->getType1());
        else
            coords2 = LayoutEditor::getCoords(t->getConnect2(),t->getType2());
    }
    double delX = coords1.x() - coords2.x();
    double delY = coords1.y() - coords2.y();
    if (qAbs(delX) > 2.0*qAbs(delY)) {
        // track is Horizontal
        if (delX>0.0) return false;
        else return true;
    }
    else if(qAbs(delY) > 2.0*qAbs(delX)) {
        // track is Vertical
        if (delY>0.0) return false;
        else return true;
    }
    // track is not vertical or horizontal, assume horizontal
//		logError ("Track is not vertical or horizontal at anchor");
    if (delX>0.0) return false;
    return true;
}

/**
 * Tool to set signals at a block boundary, including placing the signal icons and
 *		setup of Simple Signal Logic for each signal head
 * <P>
 * Block boundary must be at an Anchor Point on the LayoutEditor panel.
 */


// display dialog for Set Signals at Block Boundary tool
/*public*/ void LayoutEditorTools::setSignalsAtBlockBoundaryFromMenu(PositionablePoint* p, MultiIconEditor* theEditor, JFrame *theFrame )
{
 boundary = p;

 //if this is an edge connector...
 if ((p->getType() == PositionablePoint::EDGE_CONNECTOR) && ((p->getLinkedPoint() == nullptr)
         || (p->getLinkedPoint()->getConnect1() == nullptr))) {
     if (p->getConnect1Dir() == Path::EAST || p->getConnect1Dir() == Path::SOUTH) {
         showWest = false;
     } else {
         showEast = false;
     }
     block1IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
 } else {
     block1IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
     block2IDComboBox->setSelectedItem(boundary->getConnect2()->getLayoutBlock()->getBlock());
 }
 setSignalsAtBlockBoundaryFromMenuFlag = true;
 setSignalsAtBlockBoundary(theEditor, theFrame);
 setSignalsAtBlockBoundaryFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAtBlockBoundary( MultiIconEditor* theEditor, JFrame* theFrame )
{
 signalIconEditor = theEditor;
 signalFrame = theFrame;

 // Initialize if needed
 if (setSignalsAtBlockBoundaryFrame == nullptr)
 {
  setSignalsAtBlockBoundaryFrame = new JmriJFrameX(tr("Set Signals at Block Boundary"), false, true );
  //setSignalsAtBlockBoundaryFrame->layout()->addWidgetHelpMenu("package.jmri.jmrit.display.SetSignalsAtBoundary", true);
  //setSignalsAtBlockBoundaryFrame->setLocation(70,30);
  QWidget* theContentPane = new QWidget(setSignalsAtBlockBoundaryFrame);
  setSignalsAtBlockBoundaryFrame->setCentralWidget(theContentPane);
  QVBoxLayout* centralWidgetLayout;
  theContentPane->setLayout(centralWidgetLayout=new QVBoxLayout(theContentPane/*, BoxLayout.Y_AXIS)*/));
  JPanel* panel11 = new JPanel(new FlowLayout());
  block1NameLabel = new JLabel(
          tr("Block") + " 1 ");
  panel11->layout()->addWidget(block1NameLabel);
  panel11->layout()->addWidget(block1IDComboBox);
  block1IDComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11);

  JPanel* panel12 = new JPanel(new FlowLayout());
  block2NameLabel = new JLabel(
          tr("Block")
                  + " 2 " + tr("Name"));
  panel12->layout()->addWidget(block2NameLabel);
  panel12->layout()->addWidget(block2IDComboBox);
  block2IDComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel12);
  theContentPane->layout()-> addWidget(new JSeparator(JSeparator::HORIZONTAL));

  QFrame* line = new QFrame();
  line->setObjectName(QString::fromUtf8("line"));
  line->setGeometry(QRect(10, 30, 571, 16));
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  centralWidgetLayout->addWidget(/*new JSeparator(JSeparator::HORIZONTAL)*/line);
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Heads"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getAnchorSavedSignalHeads = new QPushButton(tr("Get Saved")));
//        getAnchorSavedSignalHeads->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
  connect(getAnchorSavedSignalHeads, &QPushButton::clicked, [=]{
          getSavedAnchorSignals(/*e*/);
//                }
  });
  getAnchorSavedSignalHeads->setToolTip( tr("Click to retrieve signal heads previously stored.") );
  centralWidgetLayout->addWidget(panel2);
  if (showEast) {
   QWidget* panel21 = new QWidget();
   panel21->setLayout(new QHBoxLayout());
   QLabel* eastBoundLabel = new QLabel(tr("East (or South) Bound")+" : ");
   panel21->layout()->addWidget(eastBoundLabel);
   panel21->layout()->addWidget(eastBoundSignalHeadComboBox);
   centralWidgetLayout->addWidget(panel21);
   eastBoundSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head for left-bound (east) or down-bound (south) trains."));
   QWidget* panel22 = new QWidget();
   panel22->setLayout(new QHBoxLayout());
   panel22->layout()->addWidget(new QLabel("   "));
   panel22->layout()->addWidget(setEastBound);
   setEastBound->setToolTip(tr("Check to place icon for above signal head on panel near anchor point."));
   panel22->layout()->addWidget(new QLabel("  "));
   panel22->layout()->addWidget(setupLogicEastBound);
   setupLogicEastBound->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
   centralWidgetLayout->addWidget(panel22);
  }
  if (showWest) {
   QWidget* panel31 = new QWidget();
   panel31->setLayout(new QHBoxLayout());
   QLabel* westBoundLabel = new QLabel(tr("West (or North) Bound")+" : ");
   panel31->layout()->addWidget(westBoundLabel);
   panel31->layout()->addWidget(westBoundSignalHeadComboBox);
   centralWidgetLayout->addWidget(panel31);
   westBoundSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head for right-bound (west) or up-bound (north) trains."));
   QWidget* panel32 = new QWidget();
   panel32->setLayout(new QHBoxLayout());
   panel32->layout()->addWidget(new QLabel("   "));
   panel32->layout()->addWidget(setWestBound);
   setWestBound->setToolTip(tr("AnchorCheck to place icon for above signal head on panel near turnout."));
   panel32->layout()->addWidget(new QLabel("  "));
   panel32->layout()->addWidget(setupLogicWestBound);
   setupLogicWestBound->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
   centralWidgetLayout->addWidget(panel32);
  }
  QFrame* line2 = new QFrame();
  line2->setObjectName(QString::fromUtf8("line"));
  line2->setGeometry(QRect(10, 30, 571, 16));
  line2->setFrameShape(QFrame::HLine);
  centralWidgetLayout->addWidget(/*new JSeparator(JSeparator::HORIZONTAL)*/line2);
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());
  panel6->layout()->addWidget(changeSignalAtBoundaryIcon = new QPushButton(tr("Change Signal Head Icon")));
//    changeSignalAtBoundaryIcon->layout()->addWidgetActionListener(new ActionListener() {
  connect(changeSignalAtBoundaryIcon, &QPushButton::clicked, [=]{
//            /*public*/ void actionPerformed(ActionEvent e) {
                signalFrame->setVisible(true);
//            }
        });
  changeSignalAtBoundaryIcon->setToolTip( tr("Click to change icons used to represent signal heads. (Use left-facing icons.)") );
  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setSignalsAtBlockBoundaryDone = new QPushButton(tr("Done")));
//    setSignalsAtBoundaryDone->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
  connect(setSignalsAtBlockBoundaryDone, &QPushButton::clicked, [=]{
            setSignalsAtBlockBoundaryDonePressed(/*e*/);
//        }
    });
  setSignalsAtBlockBoundaryDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
  panel6->layout()->addWidget(setSignalsAtBlockBoundaryCancel = new QPushButton(tr("Cancel")));
//    setSignalsAtBoundaryCancel->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
  connect(setSignalsAtBlockBoundaryCancel, &QPushButton::clicked, [=]{
            setSignalsAtBlockBoundaryCancelPressed(/*e*/);
//        }
    });
  setSignalsAtBlockBoundaryCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  centralWidgetLayout->addWidget(panel6);

  //make this button the default button (return or enter activates)
//  JRootPane rootPane = SwingUtilities.getRootPane(setSignalsDone);
//  rootPane.setDefaultButton(setSignalsDone);
  setSignalsAtBlockBoundaryDone->setDefault(true);

//  setSignalsAtBlockBoundaryFrame.addWindowListener(new WindowAdapter() {
//      @Override
//      public void windowClosing(WindowEvent e) {
//          setSignalsAtBlockBoundaryCancelPressed(null);
//      }
//  });
  setSignalsAtBlockBoundaryFrame->addWindowListener(new SBBWindowListener(this));
 }
  block1IDComboBox->setVisible(!setSignalsAtBlockBoundaryFromMenuFlag);
  block2IDComboBox->setVisible(!setSignalsAtBlockBoundaryFromMenuFlag);

  if (setSignalsAtBlockBoundaryFromMenuFlag) {
      getSavedAnchorSignals(/*null*/);
      block1NameLabel->setText(tr("Block")
              + " 1 " + tr("Name")
              + boundary->getConnect1()->getLayoutBlock()->getId());
      if (boundary->getConnect2() != nullptr) {
          block2NameLabel->setText(tr("Block")
                  + " 2 " + tr("Name")
                  + boundary->getConnect2()->getLayoutBlock()->getId());
      }
  }
 if (!setSignalsAtBlockBoundaryOpenFlag)
 {
        setSignalsAtBlockBoundaryFrame->resize(QSize());
        setSignalsAtBlockBoundaryFrame->pack();
        setSignalsAtBlockBoundaryOpenFlag = true;
 }
 setSignalsAtBlockBoundaryFrame->setVisible(true);
}   //setSignalsAtBlockBoundary


/*private*/ void LayoutEditorTools::getSavedAnchorSignals (JActionEvent* /*a*/) // SLOT[]
{
    if ( !getBlockInformation() ) 
     return;
    eastBoundSignalHeadComboBox->setSelectedItem(boundary->getEastBoundSignalHead());
    westBoundSignalHeadComboBox->setSelectedItem(boundary->getWestBoundSignalHead());
}

/*private*/ void LayoutEditorTools::setSignalsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/) // SLOT() []
{
    setSignalsAtBlockBoundaryOpenFlag = false;
    setSignalsAtBlockBoundaryFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setSignalsAtBlockBoundaryDonePressed (JActionEvent* /*a*/) // SLOT[]
{
 if ( !getBlockInformation() ) return;
 eastBoundHead = getSignalHeadFromEntry(eastBoundSignalHeadComboBox,false,setSignalsAtBlockBoundaryFrame);
 westBoundHead = getSignalHeadFromEntry(westBoundSignalHeadComboBox,false,setSignalsAtBlockBoundaryFrame);
 if ( (eastBoundHead==nullptr) && (westBoundHead==nullptr) )
 {
        JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                        tr("Error - No signal heads entered.\nPlease enter signal heads or cancel."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
        return;
 }
 //place or update signals as requested
 QString newEastBoundSignalName = eastBoundSignalHeadComboBox->getSelectedItemDisplayName();
    if (newEastBoundSignalName.isNull()) {
        newEastBoundSignalName = "";
    }
    if ((eastBoundHead != nullptr) && setEastBound->isChecked()) {
        if (isHeadOnPanel(eastBoundHead)
                && (eastBoundHead != getHeadFromName(boundary->getEastBoundSignal()))) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                    tr("Error - Cannot place signal head \"%1\" on the panelbecause it is already on the panel.").arg(
                            newEastBoundSignalName),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        } else {
            removeSignalHeadFromPanel(boundary->getEastBoundSignal());
            placeEastBound();
            removeAssignment(eastBoundHead);
            boundary->setEastBoundSignal(newEastBoundSignalName);
            needRedraw = true;
        }
    } else if ((eastBoundHead != nullptr)
            && (eastBoundHead != getHeadFromName(boundary->getEastBoundSignal()))
            && (eastBoundHead != getHeadFromName(boundary->getWestBoundSignal()))) {
        if (isHeadOnPanel(eastBoundHead)) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                            newEastBoundSignalName),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        } else {
            removeSignalHeadFromPanel(boundary->getEastBoundSignal());
            removeAssignment(eastBoundHead);
            boundary->setEastBoundSignal(newEastBoundSignalName);
        }
        //} else if ((eastBoundHead != null)
        //            && (eastBoundHead == getHeadFromName(boundary.getWestBoundSignal()))) {
        //need to figure out what to do in this case.
    }
    QString newWestBoundSignalName = westBoundSignalHeadComboBox->getSelectedItemDisplayName();
    if (newWestBoundSignalName.isNull()) {
        newWestBoundSignalName = "";
    }
    if ((westBoundHead != nullptr) && setWestBound->isChecked()) {
        if (isHeadOnPanel(westBoundHead)
                && (westBoundHead != getHeadFromName(boundary->getWestBoundSignal()))) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                    tr("Error - Cannot place signal head \"%1\" on the panelnbecause it is already on the panel.").arg(
                            newWestBoundSignalName),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        } else {
            removeSignalHeadFromPanel(boundary->getWestBoundSignal());
            placeWestBound();
            removeAssignment(westBoundHead);
            boundary->setWestBoundSignal(newWestBoundSignalName);
            needRedraw = true;
        }
    } else if ((westBoundHead != nullptr)
            && (westBoundHead != getHeadFromName(boundary->getEastBoundSignal()))
            && (westBoundHead != getHeadFromName(boundary->getWestBoundSignal()))) {
        if (isHeadOnPanel(westBoundHead)) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                            newWestBoundSignalName),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        } else {
            removeSignalHeadFromPanel(boundary->getWestBoundSignal());
            removeAssignment(westBoundHead);
            boundary->setWestBoundSignal(newWestBoundSignalName);
        }
        //} else if ((westBoundHead != null)
        //    && (westBoundHead == getHeadFromName(boundary.getEastBoundSignal()))) {
        //need to figure out what to do in this case.
    }
    if ((eastBoundHead != nullptr) && setupLogicEastBound->isChecked()) {
        setLogicEastBound();
    }
    if ((westBoundHead != nullptr) && setupLogicWestBound->isChecked()) {
        setLogicWestBound();
    }
    setSignalsAtBlockBoundaryOpenFlag = false;
    setSignalsAtBlockBoundaryFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}   //setSignalsAtBlockBoundaryDonePressedptr

/*
* Do some thing here for end bumpers.
*
*/
/*private*/ bool LayoutEditorTools::getBlockInformation()
{
    //might have to do something to trick it with an end bumper
 if (!setSignalsAtBlockBoundaryFromMenuFlag) {
        block1 = getBlockFromEntry(block1IDComboBox);
        if (block1==nullptr) return false;
        block2 = getBlockFromEntry(block2IDComboBox);
        if (block2==nullptr) return false;
        PositionablePoint* p = NULL;
        boundary = NULL;
        for (PositionablePoint* p : layoutEditor->getPositionablePoints()) {
            if (p->getType() == PositionablePoint::ANCHOR) {
                LayoutBlock* bA = NULL;
                LayoutBlock* bB = NULL;
                if (p->getConnect1()!=nullptr) bA = p->getConnect1()->getLayoutBlock();
                if (p->getConnect2()!=nullptr) bB = p->getConnect2()->getLayoutBlock();
                if ( (bA!=nullptr) && (bB!=nullptr) && (bA!=bB) ) {
                    if ( ( (bA==block1) && (bB==block2) ) ||
                                ( (bA==block2) && (bB==block1) ) ) {
                        boundary = p;
                    }
                }
            }
        }
        if (boundary==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                        tr("Error - The two blocks entered do not join at an anchor point.\nPlease enter the correct blocks and try again."),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
           return false;
        }
    }
    // set track orientation at boundary
    eastTrack = NULL;
    westTrack = NULL;
    TrackSegment* track1 = boundary->getConnect1();
    QPointF point1;
    if (track1->getConnect1()==boundary)
        point1 = layoutEditor->getCoords(track1->getConnect2(),track1->getType2());
    else
        point1 = layoutEditor->getCoords(track1->getConnect1(),track1->getType1());
    TrackSegment* track2 = boundary->getConnect2();
    QPointF point2;
    if(boundary->getType()==PositionablePoint::END_BUMPER)
        return true;
    if (track2->getConnect1()==boundary)
        point2 = layoutEditor->getCoords(track2->getConnect2(),track2->getType2());
    else
        point2 = layoutEditor->getCoords(track2->getConnect1(),track2->getType1());

    double delX = point1.x() - point2.x();
    double delY = point1.y() - point2.y();

    if (qAbs(delX) >= qAbs(delY)) {
        if (delX > 0.0) {
            eastTrack = track1;
            westTrack = track2;
        } else {
            eastTrack = track2;
            westTrack = track1;
        }
    } else {
        if (delY > 0.0) {
            eastTrack = track1;	 //south
            westTrack = track2;	 //north
        } else {
            eastTrack = track2;	 //south
            westTrack = track1;	 //north
        }
    }
    return true;
}   //getBlockInformation

//@CheckReturnValue
/*private*/ LayoutBlock* LayoutEditorTools::getBlockFromEntry(/*@Nonnull*/ NamedBeanComboBox/*<Block>*/* blockNameComboBox) {
    return getBlockFromEntry(blockNameComboBox->getSelectedItemDisplayName());
}

/*private*/ LayoutBlock* LayoutEditorTools::getBlockFromEntry(/*@CheckForNull*/ QString blockName) {
 if ((blockName.isNull()) || blockName.isEmpty()) {
     JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
             tr("Error - Block name was not entered.Please\nenter the name of a block on the panel."),
             tr("Error"),
             JOptionPane::ERROR_MESSAGE);
     return nullptr;
 }
 LayoutBlock* block = (LayoutBlock*)((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(blockName);
 if (block == nullptr) {
     block = (LayoutBlock*)((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getBySystemName(blockName);
     if (block == nullptr) {
         JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                 tr("Error - Block \"%1\" does not exist.Please correct name\nor assign this block to track on the panel.").arg(
                         blockName), tr("Error"),
                 JOptionPane::ERROR_MESSAGE);
         return nullptr;
     }
 }
 if (!block->isOnPanel(layoutEditor)
         && ((boundary == nullptr) || boundary->getType() != PositionablePoint::EDGE_CONNECTOR)) {
     JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
             tr("Error - Block \"%1\" exists, but is not\nassigned to track on this panel.").arg(
                     blockName), tr("Error"),
             JOptionPane::ERROR_MESSAGE);
     return nullptr;
 }
 return (block);
}

/*private*/ void LayoutEditorTools::placeEastBound() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = eastBoundSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


    QPointF coords = boundary->getCoordsCenter();
    QPointF delta = QPointF(0.0, +shift);

    delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
    QPointF where = MathUtil::add(coords, delta);
    setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeWestBound() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = westBoundSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

    QPointF coords = boundary->getCoordsCenter();

    QPointF delta = QPointF(0.0, -shift);
    delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
    QPointF where = MathUtil::add(coords, delta);
    setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::setLogicEastBound() {
    LayoutBlock* eastBlock = eastTrack->getLayoutBlock();
    Sensor* eastBlockOccupancy = eastBlock->getOccupancySensor();
    if (eastBlockOccupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{eastBlock.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(0, tr("Information"), tr("Cannot set up logic because block \"%1\"\n                                                          doesn''t have an occupancy sensor.").arg(eastBlock->getUserName()));
        return;
    }

    QString newEastBoundSignalName = eastBoundSignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(eastTrack,
            boundary, newEastBoundSignalName, setSignalsAtBlockBoundaryFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                eastBlock->getUserName()),
                    "",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(newEastBoundSignalName)) return;
    logic->setMode(BlockBossLogic::SINGLEBLOCK);
    logic->setSensor1(eastBlockOccupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    finalizeBlockBossLogic();
}
/*private*/ void LayoutEditorTools::setLogicWestBound() {
    LayoutBlock* westBlock = westTrack->getLayoutBlock();
    Sensor* westBlockOccupancy = westBlock->getOccupancySensor();
    if (westBlockOccupancy==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                westBlock->getUserName()),
                    nullptr,JOptionPane::INFORMATION_MESSAGE);
        return;
    }

    QString newWestBoundSignalName = westBoundSignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(westTrack,
            boundary, newWestBoundSignalName, setSignalsAtBlockBoundaryFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
//        JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{westBlock.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(0, tr("Information"), tr("Cannot set up logic because the next signal (in or\n                                                          at the end of block \"%1\") apparently is not yet defined.").arg(westBlock->getUserName()));

        return;
    }
    if (!initializeBlockBossLogic(newWestBoundSignalName)) return;
    logic->setMode(BlockBossLogic::SINGLEBLOCK);
    logic->setSensor1(westBlockOccupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    finalizeBlockBossLogic();
}

/**
 * Tool to set signals at a double crossover turnout, including placing the
 *		signal icons and setup of Simple Signal Logic for each signal head
 * <P>
 * This tool assumes left facing signal head icons have been selected, and
 *		will rotate the signal head icons accordingly.
 * <P>
 * This tool will place icons on the outside edge of the turnout.
 * <P>
 * At least one signal at each of the four connection points is
 *		required. A second signal at each is optional.
 * <P>
 * This tool only places signal icons if the turnout is either mostly vertical
 *		or mostly horizontal. Some user adjustment may be needed.
 */


// display dialog for Set Signals at Crossover Turnout tool
/*public*/ void LayoutEditorTools::setSignalsAtXoverTurnoutFromMenu( LayoutTurnout* to,
                MultiIconEditor* theEditor, JFrame* theFrame )
{
 layoutTurnout = to;
 turnout = to->getTurnout();
 xoverType = layoutTurnout->getTurnoutType();
 if ( (xoverType!=LayoutTurnout::DOUBLE_XOVER) && (xoverType!=LayoutTurnout::RH_XOVER) &&
                                     (xoverType!=LayoutTurnout::LH_XOVER) )
 {
  log->error("entered Set Signals at XOver, with a non-crossover turnout");
  return;
 }
 xoverTurnoutName = layoutTurnout->getTurnoutName();
 setSignalsAtXoverTurnoutFromMenuFlag = true;
 setSignalsAtXoverTurnout(theEditor, theFrame);
 setSignalsAtXoverTurnoutFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAtXoverTurnout( MultiIconEditor* theEditor, JFrame* theFrame )
{
 signalIconEditor = theEditor;
 signalFrame = theFrame;
 if (!setSignalsAtXoverTurnoutFromMenuFlag)
 {
  QList<LayoutTurnout*> xovers = QList<LayoutTurnout*>();
  for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts())
  {
   if(qobject_cast<LayoutTurnout*>(lt))
   {
    LayoutTurnout* layoutTurnout = qobject_cast<LayoutTurnout*>(lt);
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER))
    {
        xovers.append(layoutTurnout);
    }
   }
  }
  QComboBox* jcb = new QComboBox();
  //xovers.toArray(new LayoutTurnout[xovers.size()]));
  //jcb->addItems(xovers);
  foreach (LayoutTurnout* lt, xovers) {
   jcb->addItem(lt->getName(), VPtr<LayoutTurnout>::asQVariant(lt));
  }
  jcb->setEditable(true);
  JOptionPane::showMessageDialog(layoutEditor, VPtr<QComboBox>::asQVariant(jcb),
          tr("Enter name of crossover turnout"),
          JOptionPane::QUESTION_MESSAGE);
  LayoutTurnout* layoutTurnout = VPtr<LayoutTurnout>::asPtr(jcb->currentData());
  xoverTurnoutName = layoutTurnout->getTurnoutName();

  if (xoverTurnoutName.length()<3) return;  // cancelled
 }
 if (!getTurnoutInformation(true))
  return;

 //Initialize if needed which can be the first time or the crossover type has changed.
 if (setSignalsAtXoverTurnoutFrame == nullptr || xoverCurr != xoverType)
 {
  xoverCurr = xoverType;
  setSignalsAtXoverTurnoutOpenFlag = false;
  setSignalsAtXoverTurnoutFrame = new JmriJFrameX(tr("Set Signals at Crossover"), false, true);
  oneFrameToRuleThemAll(setSignalsAtXoverTurnoutFrame);
  setSignalsAtXoverTurnoutFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
  setSignalsAtXoverTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtXoverTurnout", true);
  setSignalsAtXoverTurnoutFrame->setLocation(70, 30);
  QFont font;
  font.setPointSize(8);
  setSignalsAtXoverTurnoutFrame->setFont(font);
  QScrollArea* scrollArea = new QScrollArea();
  scrollArea->setWidgetResizable(true);
  setSignalsAtXoverTurnoutFrame->setCentralWidget(scrollArea);
  QWidget* scrollWidget = new QWidget;
  scrollArea->setWidget(scrollWidget);
  QVBoxLayout* centralWidgetLayout;
  scrollWidget->setLayout(centralWidgetLayout = new QVBoxLayout(scrollWidget/*, BoxLayout.Y_AXIS*/));
  ((QVBoxLayout*)centralWidgetLayout)->setSpacing(1);
  ((QVBoxLayout*)centralWidgetLayout)->setMargin(0);
  QWidget* panel1 = new QWidget();
  panel1->setLayout(new QHBoxLayout());
  panel1->layout()->addWidget(xoverTurnoutNameLabel);
  centralWidgetLayout->addWidget(panel1);
  QFrame* line = new QFrame();
  line->setObjectName(QString::fromUtf8("line"));
  line->setGeometry(QRect(10, 30, 571, 16));
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  centralWidgetLayout->addWidget(line);
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Heads"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedXoverSignalHeads = new QPushButton(tr("Get Saved")));
//  getSavedXoverSignalHeads->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                xoverTurnoutSignalsGetSaved(e);
//            }
//        });
  connect(getSavedXoverSignalHeads, SIGNAL(clicked()), this, SLOT(xoverTurnoutSignalsGetSaved()));
  getSavedXoverSignalHeads->setToolTip( "Click to retrieve signal heads previously stored.");
  centralWidgetLayout->addWidget(panel2);
    QWidget* panel21 = new QWidget();
    panel21->setLayout(new QHBoxLayout());
    QLabel* a1Label = new QLabel(tr("A Corner - Continuing")+" : ");
    panel21->layout()->addWidget(a1Label);
    panel21->layout()->addWidget(a1SignalHeadComboBox);
    centralWidgetLayout->addWidget(panel21);
    a1SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
    QWidget* panel22 = new QWidget();
    panel22->setLayout(new QHBoxLayout());
    panel22->layout()->addWidget(new QLabel("   "));
    panel22->layout()->addWidget(setA1Head);
    setA1Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
    panel22->layout()->addWidget(new QLabel("  "));
    panel22->layout()->addWidget(setupA1Logic);
    setupA1Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
    centralWidgetLayout->addWidget(panel22);
    if (!(xoverType == LayoutTurnout::LH_XOVER))
    {
        QWidget* panel23 = new QWidget();
        panel23->setLayout(new QHBoxLayout());
        QLabel* a2Label = new QLabel(tr("A Corner - Diverging")+" : ");
        panel23->layout()->addWidget(a2Label);
        panel23->layout()->addWidget(a2SignalHeadComboBox);
        centralWidgetLayout->addWidget(panel23);
        a2SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel24 = new QWidget();
        panel24->setLayout(new QHBoxLayout());
        panel24->layout()->addWidget(new QLabel("   "));
        panel24->layout()->addWidget(setA2Head);
        setA2Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel24->layout()->addWidget(new QLabel("  "));
        panel24->layout()->addWidget(setupA2Logic);
        setupA2Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel24);
    }
    QWidget* panel31 = new QWidget();
    panel31->setLayout(new QHBoxLayout());
    QLabel* b1Label = new QLabel(tr("B Corner - Continuing")+" : ");
    panel31->layout()->addWidget(b1Label);
    panel31->layout()->addWidget(b1SignalHeadComboBox);
    centralWidgetLayout->addWidget(panel31);
    b1SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
    QWidget* panel32 = new QWidget();
    panel32->setLayout(new QHBoxLayout());
    panel32->layout()->addWidget(new QLabel("   "));
    panel32->layout()->addWidget(setB1Head);
    setB1Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
    panel32->layout()->addWidget(new QLabel("  "));
    panel32->layout()->addWidget(setupB1Logic);
    setupB1Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
    centralWidgetLayout->addWidget(panel32);
    if (!(xoverType == LayoutTurnout::RH_XOVER)) {
        QWidget* panel33 = new QWidget();
        panel33->setLayout(new QHBoxLayout());
        QLabel* b2Label = new QLabel(tr("B Corner - Diverging")+" : ");
        panel33->layout()->addWidget(b2Label);
        panel33->layout()->addWidget(b2SignalHeadComboBox);
        centralWidgetLayout->addWidget(panel33);
        b2SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel34 = new QWidget();
        panel34->setLayout(new QHBoxLayout());
        panel34->layout()->addWidget(new QLabel("   "));
        panel34->layout()->addWidget(setB2Head);
        setB2Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel34->layout()->addWidget(new QLabel("  "));
        panel34->layout()->addWidget(setupB2Logic);
        setupB2Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel34);
    }
    QWidget* panel41 = new QWidget();
    panel41->setLayout(new QHBoxLayout());
    QLabel* c1Label = new QLabel(tr("C Corner - Continuing")+" : ");
    panel41->layout()->addWidget(c1Label);
    panel41->layout()->addWidget(c1SignalHeadComboBox);
    centralWidgetLayout->addWidget(panel41);
    c1SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
    QWidget* panel42 = new QWidget();
    panel42->setLayout(new QHBoxLayout());
    panel42->layout()->addWidget(new QLabel("   "));
    panel42->layout()->addWidget(setC1Head);
    setC1Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
    panel42->layout()->addWidget(new QLabel("  "));
    panel42->layout()->addWidget(setupC1Logic);
    setupC1Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
    centralWidgetLayout->addWidget(panel42);
    if (!(xoverType == LayoutTurnout::LH_XOVER)) {
        QWidget* panel43 = new QWidget();
        panel43->setLayout(new QHBoxLayout());
        QLabel* c2Label = new QLabel(tr("C Corner - Diverging")+" : ");
        panel43->layout()->addWidget(c2Label);
        panel43->layout()->addWidget(c2SignalHeadComboBox);
        centralWidgetLayout->addWidget(panel43);
        c2SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel44 = new QWidget();
        panel44->setLayout(new QHBoxLayout());
        panel44->layout()->addWidget(new QLabel("   "));
        panel44->layout()->addWidget(setC2Head);
        setC2Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel44->layout()->addWidget(new QLabel("  "));
        panel44->layout()->addWidget(setupC2Logic);
        setupC2Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel44);
    }
    QWidget* panel51 = new QWidget();
    panel51->setLayout(new QHBoxLayout());
    QLabel* d1Label = new QLabel(tr("D Corner - Continuing")+" : ");
    panel51->layout()->addWidget(d1Label);
    panel51->layout()->addWidget(d1SignalHeadComboBox);
    centralWidgetLayout->addWidget(panel51);
    d1SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
    QWidget* panel52 = new QWidget();
    panel52->setLayout(new QHBoxLayout());
    panel52->layout()->addWidget(new QLabel("   "));
    panel52->layout()->addWidget(setD1Head);
    setD1Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
    panel52->layout()->addWidget(new QLabel("  "));
    panel52->layout()->addWidget(setupD1Logic);
    setupD1Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
    centralWidgetLayout->addWidget(panel52);
    if (!(xoverType == LayoutTurnout::RH_XOVER))
    {
        QWidget* panel53 = new QWidget();
        panel53->setLayout(new QHBoxLayout());
        QLabel* d2Label = new QLabel(tr("D Corner - Diverging")+" : ");
        panel53->layout()->addWidget(d2Label);
        panel53->layout()->addWidget(d2SignalHeadComboBox);
        centralWidgetLayout->addWidget(panel53);
        d2SignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel54 = new QWidget();
        panel54->setLayout(new QHBoxLayout());
        panel54->layout()->addWidget(new QLabel("   "));
        panel54->layout()->addWidget(setD2Head);
        setD2Head->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel54->layout()->addWidget(new QLabel("  "));
        panel54->layout()->addWidget(setupD2Logic);
        setupD2Logic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel54);
    }
    QFrame* line2 = new QFrame();
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(10, 30, 571, 16));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    centralWidgetLayout->addWidget(line);
    QWidget* panel6 = new QWidget();
    panel6->setLayout(new QHBoxLayout());
    panel6->layout()->addWidget(changeXoverSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
//    changeXoverSignalIcon->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
    connect(changeXoverSignalIcon, &QPushButton::clicked, [=]{
                signalFrame->setVisible(true);
//            }
        });
    changeXoverSignalIcon->setToolTip( tr("Click to change icons used to represent signal heads. (Use left-facing icons.)") );
    panel6->layout()->addWidget(new QLabel("  "));
    panel6->layout()->addWidget(setXoverSignalsDone = new QPushButton(tr("Done")));
//    setXoverSignalsDone->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(setXoverSignalsDone, &QPushButton::clicked, [=]{
            setXoverSignalsDonePressed(/*e*/);
//        }
    });
    setXoverSignalsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
    panel6->layout()->addWidget(setXoverSignalsCancel = new QPushButton(tr("Cancel")));
//    setXoverSignalsCancel->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setXoverSignalsCancelPressed(e);
//        }
//    });
    connect(setXoverSignalsCancel, SIGNAL(clicked()), this, SLOT(setXoverSignalsCancelPressed()));
    setXoverSignalsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
    centralWidgetLayout->addWidget(panel6);
    setSignalsAtXoverTurnoutFrame->addWindowListener(new XSSSWindowListener(this));
//    {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            setXoverSignalsCancelPressed(nullptr);
//        }
//    });
 }
    setPlaceAllHeads->setChecked(false);
 setupAllLogic->setChecked(false);

 xoverTurnoutNameLabel->setText(
         tr("Turnout")
         + " " + tr("Name") + xoverTurnoutName);
 xoverType = layoutTurnout->getTurnoutType();

 xoverTurnoutSignalsGetSaved(/*null*/);

 if (!setSignalsAtXoverTurnoutOpenFlag) {
     //setSignalsAtXoverTurnoutFrame->resize(QSize());
     setSignalsAtXoverTurnoutFrame->pack();
     setSignalsAtXoverTurnoutOpenFlag = true;
 }
 setSignalsAtXoverTurnoutFrame->setVisible(true);
} //setSignalsAtXoverTurnout

/*private*/ void LayoutEditorTools::xoverTurnoutSignalsGetSaved (JActionEvent* /*a*/)  // SLOT[]
{
  a1SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalA1());
  a2SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalA2());
  b1SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalB1());
  b2SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalB2());
  c1SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalC1());
  c2SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalC2());
  d1SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalD1());
  d2SignalHeadComboBox->setSelectedItem(layoutTurnout->getSignalD2());
}

/*private*/ void LayoutEditorTools::setXoverSignalsCancelPressed (JActionEvent* /*a*/) // SLOT[]
{
 setSignalsAtXoverTurnoutOpenFlag = false;
 setSignalsAtXoverTurnoutFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setXoverSignalsDonePressed (JActionEvent* /*a*/)
{
 if ( !getXoverSignalHeadInformation() ) return;
 // place signal icons if requested, and assign signal heads to this turnout
 QString signalHeadName = a1SignalHeadComboBox->getSelectedItemDisplayName();
 if (setA1Head->isChecked())
 {
  if (isHeadOnPanel(a1Head) &&
            (a1Head!=getHeadFromName(layoutTurnout->getSignalA1Name())))
  {
   JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
       tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
           signalHeadName),
               tr("Error"),JOptionPane::ERROR_MESSAGE);
   return;
  }
   else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) )
  {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts/nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
   QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

   if (a1Head!=getHeadFromName(layoutTurnout->getSignalA1Name()))
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
    removeAssignment(a1Head);
    layoutTurnout->setSignalA1Name(signalHeadName);
   }
  }
  else
  {
   removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
   placeA1();
   removeAssignment(a1Head);
   layoutTurnout->setSignalA1Name(signalHeadName);
   needRedraw = true;
  }
 }
 else
 {
  int assigned = isHeadAssignedHere(a1Head,layoutTurnout);
  if (assigned == NONE)
  {
   if ( isHeadOnPanel(a1Head) &&
                                isHeadAssignedAnywhere(a1Head) )
   {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
    return;
   }
   else
   {
    removeSignalHeadFromPanel(layoutTurnout->getSignalA1Name());
    removeAssignment(a1Head);
    layoutTurnout->setSignalA1Name(signalHeadName);
   }
  }
  else if (assigned!=A1)
  {
// need to figure out what to do in this case.
  }
 }
 signalHeadName = a2SignalHeadComboBox->getSelectedItemDisplayName();
 if ( (a2Head!=nullptr) && setA2Head->isChecked() )
 {
        if (isHeadOnPanel(a2Head) &&
            (a2Head!=getHeadFromName(layoutTurnout->getSignalA2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts/nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (a2Head!=getHeadFromName(layoutTurnout->getSignalA2Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
                removeAssignment(a2Head);
                layoutTurnout->setSignalA2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
            placeA2();
            removeAssignment(a2Head);
            layoutTurnout->setSignalA2Name(signalHeadName);
            needRedraw = true;
        }
 }
 else if (a2Head!=nullptr)
 {
        int assigned = isHeadAssignedHere(a2Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a2Head) &&
                                isHeadAssignedAnywhere(a2Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
                removeAssignment(a2Head);
                layoutTurnout->setSignalA2Name(signalHeadName);
            }
        }
        else if (assigned!=A2) {
// need to figure out what to do in this case.
        }
 }
 else if (a2Head==nullptr)
 {
  removeSignalHeadFromPanel(layoutTurnout->getSignalA2Name());
        layoutTurnout->setSignalA2Name("");
 }
 signalHeadName = b1SignalHeadComboBox->getSelectedItemDisplayName();
 if (setB1Head->isChecked())
 {
  if (isHeadOnPanel(b1Head) &&
            (b1Head!=getHeadFromName(layoutTurnout->getSignalB1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts/nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."));

            if (b1Head!=getHeadFromName(layoutTurnout->getSignalB1Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
                removeAssignment(b1Head);
                layoutTurnout->setSignalB1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
            placeB1();
            removeAssignment(b1Head);
            layoutTurnout->setSignalB1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(b1Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b1Head) &&
                                isHeadAssignedAnywhere(b1Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalB1Name());
                removeAssignment(b1Head);
                layoutTurnout->setSignalB1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case.
        }
    }
 signalHeadName = b2SignalHeadComboBox->getSelectedItemDisplayName();
    if ( (b2Head!=nullptr) && setB2Head->isChecked() ) {
        if (isHeadOnPanel(b2Head) &&
            (b2Head!=getHeadFromName(layoutTurnout->getSignalB2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (b2Head!=getHeadFromName(layoutTurnout->getSignalB2Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalB2Name());
                removeAssignment(b2Head);
                layoutTurnout->setSignalB2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalB2Name());
            placeB2();
            removeAssignment(b2Head);
            layoutTurnout->setSignalB2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (b2Head!=nullptr) {
        int assigned = isHeadAssignedHere(b2Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b2Head) &&
                                isHeadAssignedAnywhere(b2Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalB2Name());
                removeAssignment(b2Head);
                layoutTurnout->setSignalB2Name(signalHeadName);
            }
        }
        else if (assigned!=B2) {
// need to figure out what to do in this case.
        }
    }
    else if (b2Head==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout->getSignalB2Name());
        layoutTurnout->setSignalB2Name("");
    }
    signalHeadName = c1SignalHeadComboBox->getSelectedItemDisplayName();
    if (setC1Head->isChecked()) {
        if (isHeadOnPanel(c1Head) &&
            (c1Head!=getHeadFromName(layoutTurnout->getSignalC1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (c1Head!=getHeadFromName(layoutTurnout->getSignalC1Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
                removeAssignment(c1Head);
                layoutTurnout->setSignalC1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
            placeC1();
            removeAssignment(c1Head);
            layoutTurnout->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(c1Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(c1Head) &&
                                isHeadAssignedAnywhere(c1Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
                removeAssignment(c1Head);
                layoutTurnout->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
// need to figure out what to do in this case.
        }
    }
    signalHeadName = c2SignalHeadComboBox->getSelectedItemDisplayName();
    if ( (c2Head!=nullptr) && setC2Head->isChecked() ) {
        if (isHeadOnPanel(c2Head) &&
            (c2Head!=getHeadFromName(layoutTurnout->getSignalC2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts/that are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (c2Head!=getHeadFromName(layoutTurnout->getSignalC2Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalC2Name());
                removeAssignment(c2Head);
                layoutTurnout->setSignalC2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalC2Name());
            placeC2();
            removeAssignment(c2Head);
            layoutTurnout->setSignalC2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (c2Head!=nullptr) {
        int assigned = isHeadAssignedHere(c2Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(c2Head) &&
                                isHeadAssignedAnywhere(c2Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalC2Name());
                removeAssignment(c2Head);
                layoutTurnout->setSignalC2Name(signalHeadName);
            }
        }
        else if (assigned!=C2) {
// need to figure out what to do in this case.
        }
    }
    else if (c2Head==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout->getSignalC2Name());
        layoutTurnout->setSignalC2Name("");
    }
    signalHeadName = d1SignalHeadComboBox->getSelectedItemDisplayName();
    if (setD1Head->isChecked()) {
        if (isHeadOnPanel(d1Head) &&
            (d1Head!=getHeadFromName(layoutTurnout->getSignalD1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (d1Head!=getHeadFromName(layoutTurnout->getSignalD1Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalD1Name());
                removeAssignment(d1Head);
                layoutTurnout->setSignalD1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalD1Name());
            placeD1();
            removeAssignment(d1Head);
            layoutTurnout->setSignalD1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(d1Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d1Head) &&
                                isHeadAssignedAnywhere(d1Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalD1Name());
                removeAssignment(d1Head);
                layoutTurnout->setSignalD1Name(signalHeadName);
            }
        }
        else if (assigned!=D1) {
// need to figure out what to do in this case.
        }
    }
    signalHeadName = d2SignalHeadComboBox->getSelectedItemDisplayName();
    if ( (d2Head!=nullptr) && setD2Head->isChecked() ) {
        if (isHeadOnPanel(d2Head) &&
            (d2Head!=getHeadFromName(layoutTurnout->getSignalD2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutHorizontal) && (!layoutTurnoutVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                tr("Sorry, cannot place signal heads at turnouts/nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (d2Head!=getHeadFromName(layoutTurnout->getSignalD2Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalD2Name());
                removeAssignment(d2Head);
                layoutTurnout->setSignalD2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout->getSignalD2Name());
            placeD2();
            removeAssignment(d2Head);
            layoutTurnout->setSignalD2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (d2Head!=nullptr) {
        int assigned = isHeadAssignedHere(d2Head,layoutTurnout);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d2Head) &&
                                isHeadAssignedAnywhere(d2Head) ) {
                JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout->getSignalD2Name());
                removeAssignment(d2Head);
                layoutTurnout->setSignalD2Name(signalHeadName);
            }
        }
        else if (assigned!=D2) {
// need to figure out what to do in this case.
        }
    }
    else if (d2Head==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout->getSignalD2Name());
        layoutTurnout->setSignalD2Name("");
    }
    // setup logic if requested
    if (setupA1Logic->isChecked() || setupA2Logic->isChecked()) {
        if (xoverType == LayoutTurnout::LH_XOVER) {
            setLogicXoverContinuing(a1Head,(TrackSegment*)layoutTurnout->getConnectB());
        }
        else {
            setLogicXover(a1Head,(TrackSegment*)layoutTurnout->getConnectB(),a2Head,
                    (TrackSegment*)layoutTurnout->getConnectC(),setupA1Logic->isChecked(),
                            setupA2Logic->isChecked());
        }
    }
    if (setupB1Logic->isChecked() || setupB2Logic->isChecked()) {
        if (xoverType == LayoutTurnout::RH_XOVER) {
            setLogicXoverContinuing(b1Head,(TrackSegment*)layoutTurnout->getConnectA());
        }
        else {
            setLogicXover(b1Head,(TrackSegment*)layoutTurnout->getConnectA(),b2Head,
                    (TrackSegment*)layoutTurnout->getConnectD(),setupB1Logic->isChecked(),
                            setupB2Logic->isChecked());
        }
    }
    if (setupC1Logic->isChecked() || setupC2Logic->isChecked()) {
        if (xoverType == LayoutTurnout::LH_XOVER) {
            setLogicXoverContinuing(c1Head,(TrackSegment*)layoutTurnout->getConnectD());
        }
        else {
            setLogicXover(c1Head,(TrackSegment*)layoutTurnout->getConnectD(),c2Head,
                    (TrackSegment*)layoutTurnout->getConnectA(),setupC1Logic->isChecked(),
                            setupC2Logic->isChecked());
        }
    }
    if (setupD1Logic->isChecked() || setupD2Logic->isChecked()) {
        if (xoverType == LayoutTurnout::RH_XOVER) {
            setLogicXoverContinuing(d1Head,(TrackSegment*)layoutTurnout->getConnectC());
        }
        else {
            setLogicXover(d1Head,(TrackSegment*)layoutTurnout->getConnectC(),d2Head,
                    (TrackSegment*)layoutTurnout->getConnectB(),setupD1Logic->isChecked(),
                            setupD2Logic->isChecked());
        }
    }
    // make sure this layout turnout is not linked to another
    layoutTurnout->setLinkType(LayoutTurnout::NO_LINK);
    layoutTurnout->setLinkedTurnoutName("");
    // finish up
    setSignalsAtXoverTurnoutOpenFlag = false;
    setSignalsAtXoverTurnoutFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}

/*private*/ bool LayoutEditorTools::getXoverSignalHeadInformation() {
    a1Head = getSignalHeadFromEntry(a1SignalHeadComboBox,true,setSignalsAtXoverTurnoutFrame);
    if (a1Head==nullptr) return false;
    if (!(xoverType == LayoutTurnout::LH_XOVER ))
        a2Head = getSignalHeadFromEntry(a2SignalHeadComboBox,false,setSignalsAtXoverTurnoutFrame);
    else
        a2Head = NULL;
    b1Head = getSignalHeadFromEntry(b1SignalHeadComboBox,true,setSignalsAtXoverTurnoutFrame);
    if (b1Head==nullptr) return false;
    if (!(xoverType == LayoutTurnout::RH_XOVER ))
        b2Head = getSignalHeadFromEntry(b2SignalHeadComboBox,false,setSignalsAtXoverTurnoutFrame);
    else
        b2Head = NULL;
    c1Head = getSignalHeadFromEntry(c1SignalHeadComboBox,true,setSignalsAtXoverTurnoutFrame);
    if (c1Head==nullptr) return false;
    if (!(xoverType == LayoutTurnout::LH_XOVER ))
        c2Head = getSignalHeadFromEntry(c2SignalHeadComboBox,false,setSignalsAtXoverTurnoutFrame);
    else
        c2Head = NULL;
    d1Head = getSignalHeadFromEntry(d1SignalHeadComboBox,true,setSignalsAtXoverTurnoutFrame);
    if (d1Head==nullptr) return false;
    if (!(xoverType == LayoutTurnout::RH_XOVER ))
        d2Head = getSignalHeadFromEntry(d2SignalHeadComboBox,false,setSignalsAtXoverTurnoutFrame);
    else
        d2Head = NULL;
    return true;
}
/*private*/ void LayoutEditorTools::placeA1() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = a1SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //qHypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsA = layoutTurnout->getCoordsA();
 QPointF delta = QPointF(0.0, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsA, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::placeA2() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = a2SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsA = layoutTurnout->getCoordsA();
 QPointF delta = QPointF(-2.0 * shift, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsA, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::placeB1() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = b1SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName == nullptr) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsB = layoutTurnout->getCoordsB();
 QPointF delta = QPointF(-shift, -shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsB, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeB2() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = b2SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsB = layoutTurnout->getCoordsB();
 QPointF delta = QPointF(+shift, -shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsB, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeC1() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = c1SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsC = layoutTurnout->getCoordsC();
 QPointF delta = QPointF(0.0, -shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsC, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeC2()
{
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = c2SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName == nullptr) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsC = layoutTurnout->getCoordsC();
 QPointF delta = QPointF(+2.0 * shift, -shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsC, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::placeD1()
{
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = d1SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsD = layoutTurnout->getCoordsD();
 QPointF delta = QPointF(+shift, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsD, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::placeD2() {
 if (testIcon == nullptr) {
     testIcon = signalIconEditor->getIcon(0);
 }
 QString signalHeadName = d2SignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

 QPointF coordsD = layoutTurnout->getCoordsD();
 QPointF delta = QPointF(-shift, +shift);

 delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
 QPointF where = MathUtil::add(coordsD, delta);
 setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}

//@SuppressWarnings("NULL")
/*private*/ void LayoutEditorTools::setLogicXover(SignalHead* head,TrackSegment* track,SignalHead* secondHead,TrackSegment* track2,
            bool setup1, bool setup2)
{
 if ( (track==nullptr) && setup1 )
 {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
     return;
 }
 Sensor* occupancy = NULL;
 SignalHead* nextHead = NULL;
 if ( (track!=nullptr) && setup1) {
     LayoutBlock* block = track->getLayoutBlock();
     if (block==nullptr) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
         return;
     }
     occupancy = block->getOccupancySensor();
     if (occupancy==nullptr) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
         return;
     }
     nextHead = getNextSignalFromObject(track,
             layoutTurnout, head->getSystemName(), setSignalsAtXoverTurnoutFrame);
     if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
//            JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
         return;
     }
     if (secondHead!=nullptr) {
         if (!initializeBlockBossLogic(head->getSystemName())) return;
         logic->setMode(BlockBossLogic::TRAILINGMAIN);
         logic->setTurnout(turnout->getSystemName());
         logic->setSensor1(occupancy->getSystemName());
         if (nextHead!=nullptr) {
             logic->setWatchedSignal1(nextHead->getSystemName(),false);
         }
         if (auxSignal!=nullptr) {
             logic->setWatchedSignal1Alt(auxSignal->getSystemName());
         }
         finalizeBlockBossLogic();
     }
 }
 if ( (secondHead!=nullptr) && !setup2 ) return;
 SignalHead* savedAuxSignal = auxSignal;
 if (track2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
     return;
 }
 LayoutBlock* block2 = track2->getLayoutBlock();
 if (block2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
     return;
 }
 Sensor* occupancy2 = block2->getOccupancySensor();
 if (occupancy2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block2.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\n doesn''t have an occupancy sensor.").arg(block2->getUserName()));
     return;
 }
 QString headName = head->getSystemName();
 if (secondHead!=nullptr) headName = secondHead->getSystemName();
 SignalHead* nextHead2 = getNextSignalFromObject(track2,
         layoutTurnout, headName, setSignalsAtXoverTurnoutFrame);
 if ( (nextHead2==nullptr) && (!reachedEndBumper()) ) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block2.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block2->getUserName()));
     return;
 }
 if ( (secondHead==nullptr) && (track!=nullptr) && setup1 )
 {
  if (!initializeBlockBossLogic(head->getSystemName())) return;
  logic->setMode(BlockBossLogic::FACING);
  logic->setTurnout(turnout->getSystemName());
  logic->setWatchedSensor1(occupancy->getSystemName());
  logic->setWatchedSensor2(occupancy2->getSystemName());
  if (nextHead!=nullptr) {
      logic->setWatchedSignal1(nextHead->getSystemName(),false);
  }
  if (savedAuxSignal!=nullptr) {
      logic->setWatchedSignal1Alt(savedAuxSignal->getSystemName());
  }
  if (nextHead2!=nullptr) {
      logic->setWatchedSignal2(nextHead2->getSystemName());
  }
  if (auxSignal!=nullptr) {
      logic->setWatchedSignal2Alt(auxSignal->getSystemName());
  }
  logic->setLimitSpeed2(true);
  finalizeBlockBossLogic();
 }
 else if ( (secondHead!=nullptr) && setup2)
 {
  if (!initializeBlockBossLogic(secondHead->getSystemName())) return;
  logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
  logic->setTurnout(turnout->getSystemName());
  logic->setSensor1(occupancy2->getSystemName());
  if (nextHead2!=nullptr)
  {
   logic->setWatchedSignal1(nextHead2->getSystemName(),false);
  }
  if (auxSignal!=nullptr)
  {
   logic->setWatchedSignal1Alt(auxSignal->getSystemName());
  }
  logic->setLimitSpeed2(true);
  finalizeBlockBossLogic();
 }
}
/*private*/ void LayoutEditorTools::setLogicXoverContinuing(SignalHead* head,TrackSegment* track) {
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }
    SignalHead* nextHead = getNextSignalFromObject(track,
            layoutTurnout, head->getSystemName(), setSignalsAtXoverTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
//        JOptionPane::showMessageDialog(setSignalsAtXoverTurnoutFrame,
//            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtXoverTurnoutFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
        return;
    }
    if (!initializeBlockBossLogic(head->getSystemName())) return;
    logic->setMode(BlockBossLogic::TRAILINGMAIN);
    logic->setTurnout(turnout->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    finalizeBlockBossLogic();
}

/**
 * Tool to set signals at a level crossing, including placing the
 *		signal icons and setup of Simple Signal Logic for each signal head
 * <P>
 * This tool assumes left facing signal head icons have been selected, and
 *		will rotate the signal head icons accordingly.
 * <P>
 * This tool will place icons on the right side of each track->
 * <P>
 * Both tracks do not need to be signalled. If one signal for a track,
 *		A-C or B-D, the other must also be present.
 * <P>
 * Some user adjustment of turnout positions may be needed.
 */


// display dialog for Set Signals at Level Crossing tool
/*public*/ void LayoutEditorTools::setSignalsAtLevelXingFromMenu (LevelXing* xing, MultiIconEditor* theEditor,
        JFrame* theFrame )
{
    xingFromMenu = true;
    levelXing = xing;
    blockACComboBox->setSelectedItem(levelXing->getLayoutBlockAC()->getBlock());
    blockBDComboBox->setSelectedItem(levelXing->getLayoutBlockBD()->getBlock());
    setSignalsAtLevelXingFromMenuFlag = true;
    setSignalsAtLevelXing(theEditor, theFrame);
    setSignalsAtLevelXingFromMenuFlag = false;
    return;
}

/*public*/ void LayoutEditorTools::setSignalsAtLevelXing( MultiIconEditor* theEditor, JFrame* theFrame )
{
    signalIconEditor = theEditor;
    signalFrame = theFrame;

    // Initialize if needed
    if (setSignalsAtLevelXingFrame == nullptr)
    {
        setSignalsAtLevelXingFrame = new JmriJFrameX( tr("SignalsAtLevelXing"), false, true );
        setSignalsAtLevelXingFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtLevelXing", true);
        setSignalsAtLevelXingFrame->setLocation(70,30);
        QWidget* theContentPane = setSignalsAtLevelXingFrame->getContentPane();
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
        QWidget* centralWidget = new QWidget;
        QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
        setSignalsAtLevelXingFrame->setCentralWidget(centralWidget);
        JPanel* panel11 = new JPanel(new FlowLayout());
        blockACNameLabel = new JLabel(tr("Block") + " AC");
        panel11->layout()->addWidget(blockACNameLabel);
        panel11->layout()->addWidget(blockACComboBox);
        blockACComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
        theContentPane->layout()->addWidget(panel11);

        JPanel* panel12 = new JPanel(new FlowLayout());
        blockBDNameLabel = new JLabel(tr("Block") + " BD");
        panel12->layout()->addWidget(blockBDNameLabel);
        panel12->layout()->addWidget(blockBDComboBox);
        blockBDComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));

        theContentPane->layout()->addWidget(panel12);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        QWidget* panel2 = new QWidget();
        panel2->setLayout(new QHBoxLayout());
        QLabel* shTitle = new QLabel(tr("SignalHeads"));
        panel2->layout()->addWidget(shTitle);
        panel2->layout()->addWidget(new QLabel("   "));
        panel2->layout()->addWidget(getSavedXingSignalHeads = new QPushButton(tr("GetSaved")));
//        getSavedXingSignalHeads->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    xingSignalsGetSaved(e);
//                }
//            });
        connect(getSavedXoverSignalHeads, SIGNAL(clicked()), this, SLOT(xingSignalsGetSaved()));
        getSavedXingSignalHeads->setToolTip("Click to retrieve signal heads previously stored.");
        centralWidgetLayout->addWidget(panel2);
        QWidget* panel21 = new QWidget();
        panel21->setLayout(new QHBoxLayout());
        QLabel* aLabel = new QLabel(tr("ATrack")+" : ");
        panel21->layout()->addWidget(aLabel);
        panel21->layout()->addWidget(aSignalHeadComboBox);
        centralWidgetLayout->addWidget(panel21);
        aSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel22 = new QWidget();
        panel22->setLayout(new QHBoxLayout());
        panel22->layout()->addWidget(new QLabel("   "));
        panel22->layout()->addWidget(setAHead);
        setAHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel22->layout()->addWidget(new QLabel("  "));
        panel22->layout()->addWidget(setupALogic);
        setupALogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel22);
        QWidget* panel31 = new QWidget();
        panel31->setLayout(new QHBoxLayout());
        QLabel* bLabel = new QLabel(tr("BTrack")+" : ");
        panel31->layout()->addWidget(bLabel);
        panel31->layout()->addWidget(bSignalHeadComboBox);
        centralWidgetLayout->addWidget(panel31);
        bSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel32 = new QWidget();
        panel32->setLayout(new QHBoxLayout());
        panel32->layout()->addWidget(new QLabel("   "));
        panel32->layout()->addWidget(setBHead);
        setBHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel32->layout()->addWidget(new QLabel("  "));
        panel32->layout()->addWidget(setupBLogic);
        setupBLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel32);
        QWidget* panel41 = new QWidget();
        panel41->setLayout(new QHBoxLayout());
        QLabel* cLabel = new QLabel(tr("CTrack")+" : ");
        panel41->layout()->addWidget(cLabel);
        panel41->layout()->addWidget(cSignalHeadComboBox);
        centralWidgetLayout->addWidget(panel41);
        cSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel42 = new QWidget();
        panel42->setLayout(new QHBoxLayout());
        panel42->layout()->addWidget(new QLabel("   "));
        panel42->layout()->addWidget(setCHead);
        setCHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel42->layout()->addWidget(new QLabel("  "));
        panel42->layout()->addWidget(setupCLogic);
        setupCLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel42);
        QWidget* panel51 = new QWidget();
        panel51->setLayout(new QHBoxLayout());
        QLabel* dLabel = new QLabel(tr("DTrack")+" : ");
        panel51->layout()->addWidget(dLabel);
        panel51->layout()->addWidget(dSignalHeadComboBox);
        centralWidgetLayout->addWidget(panel51);
        dSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        QWidget* panel52 = new QWidget();
        panel52->setLayout(new QHBoxLayout());
        panel52->layout()->addWidget(new QLabel("   "));
        panel52->layout()->addWidget(setDHead);
        setDHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel52->layout()->addWidget(new QLabel("  "));
        panel52->layout()->addWidget(setupDLogic);
        setupDLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
        centralWidgetLayout->addWidget(panel52);
        centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        QWidget* panel6 = new QWidget();
        panel6->setLayout(new QHBoxLayout());
        panel6->layout()->addWidget(changeXingSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
//        changeXingSignalIcon->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    signalFrame->setVisible(true);
//                }
//            });
        connect(changeXingSignalIcon, SIGNAL(clicked()), this, SLOT(on_changeSignalIcon_clicked()));
        changeXingSignalIcon->setToolTip( tr("Click to change icons used to represent signal heads. (Use left-facing icons.)") );
        panel6->layout()->addWidget(new QLabel("  "));
        panel6->layout()->addWidget(setXingSignalsDone = new QPushButton(tr("Done")));
//        setXingSignalsDone->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setXingSignalsDonePressed(e);
//            }
//        });
        connect(setXingSignalsDone, SIGNAL(clicked()), this, SLOT(setXingSignalsDonePressed()));
        setXingSignalsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
        panel6->layout()->addWidget(setXingSignalsCancel = new QPushButton(tr("Cancel")));
//        setXingSignalsCancel->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setXingSignalsCancelPressed(e);
//            }
//        });
        connect(setXingSignalsCancel, SIGNAL(clicked()), this, SLOT(setXingSignalsCancelPressed()));
        setXingSignalsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
        centralWidgetLayout->addWidget(panel6);
//        setSignalsAtLevelXingFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                setXingSignalsCancelPressed(nullptr);
//            }
//        });
        setSignalsAtLevelXingFrame->addWindowListener(new SXWindowListener(this));
        if (xingFromMenu) xingSignalsGetSaved(nullptr);
    }
    aSignalHeadComboBox->setSelectedItem(nullptr);
    bSignalHeadComboBox->setSelectedItem(nullptr);
    cSignalHeadComboBox->setSelectedItem(nullptr);
    dSignalHeadComboBox->setSelectedItem(nullptr);

    setPlaceAllHeads->setChecked(false);
    setupAllLogic->setChecked(false);

    blockACComboBox->setVisible(!setSignalsAtLevelXingFromMenuFlag);
    blockBDComboBox->setVisible(!setSignalsAtLevelXingFromMenuFlag);

    if (setSignalsAtLevelXingFromMenuFlag) {
        blockACNameLabel->setText(tr("Block") + " AC"
                + levelXing->getBlockNameAC());
        blockBDNameLabel->setText(tr("Block") + " BD"
                + levelXing->getBlockNameBD());
        xingSignalsGetSaved(/*null*/);
    } else {
        blockACNameLabel->setText(tr("Block") + " AC");
        blockBDNameLabel->setText(tr("Block") + " BD");
    }

    if (!setSignalsAtLevelXingOpenFlag) {
        setSignalsAtLevelXingFrame->resize(QSize());
        setSignalsAtLevelXingFrame->pack();
        setSignalsAtLevelXingOpenFlag = true;
    }

    setSignalsAtLevelXingFrame->setVisible(true);
}   //setSignalsAtLevelXing

/*private*/ void LayoutEditorTools::xingSignalsGetSaved (JActionEvent* /*a*/)
{
 if (!getLevelCrossingSensorInformation()) {
     return;
 }

 xingSensorBlocks = levelXing->getBlockBoundaries();

 xingSensorA->setTextField(levelXing->getSensorAName());
 xingSensorB->setTextField(levelXing->getSensorBName());
 xingSensorC->setTextField(levelXing->getSensorCName());
 xingSensorD->setTextField(levelXing->getSensorDName());

 sensorXingPanel->layout()->removeWidget(xingSensorA->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorB->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorC->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorD->getDetailsPanel());

 xingSensorA->setBoundaryLabel(xingSensorBlocks->at(0));
 xingSensorB->setBoundaryLabel(xingSensorBlocks->at(1));
 xingSensorC->setBoundaryLabel(xingSensorBlocks->at(2));
 xingSensorD->setBoundaryLabel(xingSensorBlocks->at(3));

 bool boundaryFlag = false;
 if (xingSensorBlocks->at(0) != nullptr) {
     sensorXingPanel->layout()->addWidget(xingSensorA->getDetailsPanel());
     boundaryFlag = true;
 }
 if (xingSensorBlocks->at(1) != nullptr) {
     sensorXingPanel->layout()->addWidget(xingSensorB->getDetailsPanel());
     boundaryFlag = true;
 }
 if (xingSensorBlocks->at(2)!= nullptr) {
     sensorXingPanel->layout()->addWidget(xingSensorC->getDetailsPanel());
     boundaryFlag = true;
 }
 if (xingSensorBlocks->at(3) != nullptr) {
     sensorXingPanel->layout()->addWidget(xingSensorD->getDetailsPanel());
     boundaryFlag = true;
 }
 if (!boundaryFlag) {
     JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame, tr("There are no block boundaries on this level crossing.\nIt is therefore not possible to add Sensors to it"));
 }
 setSensorsAtLevelXingFrame->resize(QSize());
 setSensorsAtLevelXingFrame->pack();
}

/*private*/ void LayoutEditorTools::setXingSignalsCancelPressed (JActionEvent* /*a*/) {

    setSignalsAtLevelXingFrame->setVisible(false);
    xingFromMenu = false;

}
/*private*/ void LayoutEditorTools::setXingSignalsDonePressed (JActionEvent* /*a*/)
{
#if 1
    if ( !getLevelCrossingInformation() ) return;
    if ( !getXingSignalHeadInformation() ) return;

    // place or update signals as requested
    QString signalName = aSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (aHead!=nullptr) && setAHead->isChecked() ) {
        if (isHeadOnPanel(aHead) &&
                (aHead!=getHeadFromName(levelXing->getSignalAName())) ) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!levelXingACHorizontal) && (!levelXingACVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtLevelXingFrame, tr("Information"), tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."));
            if ( aHead!=getHeadFromName(levelXing->getSignalAName()) ) {
                removeSignalHeadFromPanel(levelXing->getSignalAName());
                removeAssignment(aHead);
                levelXing->setSignalAName(signalName);
            }
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalAName());
            placeXingA();
            removeAssignment(aHead);
            levelXing->setSignalAName(signalName);
            needRedraw = true;
        }
    }
    else if ( (aHead!=nullptr) &&
            (aHead!=getHeadFromName(levelXing->getSignalAName())) &&
            (aHead!=getHeadFromName(levelXing->getSignalBName())) &&
            (aHead!=getHeadFromName(levelXing->getSignalCName())) &&
            (aHead!=getHeadFromName(levelXing->getSignalDName())) )
    {
        if (isHeadOnPanel(aHead))
        {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         return;
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalAName());
            removeAssignment(aHead);
            levelXing->setSignalAName(signalName);
        }
    }
    else if ( (aHead!=nullptr) &&
            ( (aHead==getHeadFromName(levelXing->getSignalBName())) ||
                (aHead==getHeadFromName(levelXing->getSignalCName())) ||
                (aHead==getHeadFromName(levelXing->getSignalDName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (aHead==nullptr) {
        removeSignalHeadFromPanel(levelXing->getSignalAName());
        levelXing->setSignalAName("");
    }

    signalName = bSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (bHead!=nullptr) && setBHead->isChecked() ) {
        if (isHeadOnPanel(bHead) &&
                (bHead!=getHeadFromName(levelXing->getSignalBName()))) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!levelXingACHorizontal) && (!levelXingACVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtLevelXingFrame, tr("Information"), tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."));
            if (bHead!=getHeadFromName(levelXing->getSignalBName())) {
                removeSignalHeadFromPanel(levelXing->getSignalBName());
                removeAssignment(bHead);
                levelXing->setSignalBName(signalName);
            }
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalBName());
            placeXingB();
            removeAssignment(bHead);
            levelXing->setSignalBName(signalName);
            needRedraw = true;
        }
    }
    else if ( (bHead!=nullptr) &&
            (bHead!=getHeadFromName(levelXing->getSignalAName())) &&
            (bHead!=getHeadFromName(levelXing->getSignalBName())) &&
            (bHead!=getHeadFromName(levelXing->getSignalCName())) &&
            (bHead!=getHeadFromName(levelXing->getSignalDName())) ) {
        if (isHeadOnPanel(bHead)) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalBName());
            removeAssignment(bHead);
            levelXing->setSignalBName(signalName);
        }
    }
    else if ( (bHead!=nullptr) &&
            ( (bHead==getHeadFromName(levelXing->getSignalAName())) ||
                (bHead==getHeadFromName(levelXing->getSignalCName())) ||
                (bHead==getHeadFromName(levelXing->getSignalDName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (bHead==nullptr) {
        removeSignalHeadFromPanel(levelXing->getSignalBName());
        levelXing->setSignalBName("");
    }

    signalName = cSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (cHead!=nullptr) && setCHead->isChecked() ) {
        if (isHeadOnPanel(cHead) &&
                (cHead!=getHeadFromName(levelXing->getSignalCName())) ) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!levelXingACHorizontal) && (!levelXingACVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(setSignalsAtLevelXingFrame, tr("Information"), tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."));
            if ( cHead!=getHeadFromName(levelXing->getSignalCName()) ) {
                removeSignalHeadFromPanel(levelXing->getSignalCName());
                removeAssignment(cHead);
                levelXing->setSignalCName(signalName);
            }
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalCName());
            placeXingC();
            removeAssignment(cHead);
            levelXing->setSignalCName(signalName);
            needRedraw = true;
        }
    }
    else if ( (cHead!=nullptr) &&
            (cHead!=getHeadFromName(levelXing->getSignalAName())) &&
            (cHead!=getHeadFromName(levelXing->getSignalBName())) &&
            (cHead!=getHeadFromName(levelXing->getSignalCName())) &&
            (cHead!=getHeadFromName(levelXing->getSignalDName())) ) {
        if (isHeadOnPanel(cHead)) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalCName());
            removeAssignment(cHead);
            levelXing->setSignalCName(signalName);
        }
    }
    else if ( (cHead!=nullptr) &&
            ( (cHead==getHeadFromName(levelXing->getSignalBName())) ||
                (cHead==getHeadFromName(levelXing->getSignalAName())) ||
                (cHead==getHeadFromName(levelXing->getSignalDName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (cHead==nullptr) {
        removeSignalHeadFromPanel(levelXing->getSignalCName());
        levelXing->setSignalCName("");
    }

    signalName = dSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (dHead!=nullptr) && setDHead->isChecked() ) {
        if (isHeadOnPanel(dHead) &&
                (dHead!=getHeadFromName(levelXing->getSignalDName())) ) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!levelXingACHorizontal) && (!levelXingACVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Sorry, cannot place signal heads at anchor points\nwhere track is not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            if ( dHead!=getHeadFromName(levelXing->getSignalDName()) ) {
                removeSignalHeadFromPanel(levelXing->getSignalDName());
                removeAssignment(dHead);
                levelXing->setSignalDName(signalName);
            }
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalDName());
            placeXingD();
            removeAssignment(dHead);
            levelXing->setSignalDName(signalName);
            needRedraw = true;
        }
    }
    else if ( (dHead!=nullptr) &&
            (dHead!=getHeadFromName(levelXing->getSignalAName())) &&
            (dHead!=getHeadFromName(levelXing->getSignalBName())) &&
            (dHead!=getHeadFromName(levelXing->getSignalCName())) &&
            (dHead!=getHeadFromName(levelXing->getSignalDName())) ) {
        if (isHeadOnPanel(dHead)) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot assign signal head \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                    signalName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(levelXing->getSignalDName());
            removeAssignment(dHead);
            levelXing->setSignalDName(signalName);
        }
    }
    else if ( (dHead!=nullptr) &&
            ( (dHead==getHeadFromName(levelXing->getSignalBName())) ||
                (dHead==getHeadFromName(levelXing->getSignalCName())) ||
                (dHead==getHeadFromName(levelXing->getSignalAName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (dHead==nullptr) {
        removeSignalHeadFromPanel(levelXing->getSignalDName());
        levelXing->setSignalDName("");
    }
    // setup logic if requested
    if ( setupALogic->isChecked() && (aHead!=nullptr) ) {
        setLogicXing( aHead, (TrackSegment*)levelXing->getConnectC(),
            levelXing->getLayoutBlockBD(), (TrackSegment*)levelXing->getConnectB(),
                (TrackSegment*)levelXing->getConnectD(), aSignalHeadComboBox->getSelectedItemDisplayName());
    }
    if ( setupBLogic->isChecked() && (bHead!=nullptr) ) {
        setLogicXing( bHead, (TrackSegment*)levelXing->getConnectD(),
            levelXing->getLayoutBlockAC(), (TrackSegment*)levelXing->getConnectA(),
                (TrackSegment*)levelXing->getConnectC(), bSignalHeadComboBox->getSelectedItemDisplayName());
    }
    if ( setupCLogic->isChecked() && (cHead!=nullptr) ) {
        setLogicXing( cHead, (TrackSegment*)levelXing->getConnectA(),
            levelXing->getLayoutBlockBD(), (TrackSegment*)levelXing->getConnectB(),
                (TrackSegment*)levelXing->getConnectD(), cSignalHeadComboBox->getSelectedItemDisplayName());
    }
    if ( setupDLogic->isChecked() && (dHead!=nullptr) ) {
        setLogicXing( dHead, (TrackSegment*)levelXing->getConnectB(),
            levelXing->getLayoutBlockAC(), (TrackSegment*)levelXing->getConnectA(),
                (TrackSegment*)levelXing->getConnectC(), dSignalHeadComboBox->getSelectedItemDisplayName());
    }
    // finish up
    setSignalsAtLevelXingOpenFlag = false;
    setSignalsAtLevelXingFrame->setVisible(false);
    xingFromMenu = false;
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
#endif
}
#if 1
/*private*/ bool LayoutEditorTools::getLevelCrossingInformation() {
 if (!setSignalsAtLevelXingFromMenuFlag) {
   levelXing = nullptr;
   QList<LevelXing*> levelXings = layoutEditor->getLevelXings();
   if (levelXings.size() <= 0) {
       JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
               tr("Error - There are no level crossings on your panel\nPlease add a level crossing or cancel."),
               tr("Error"),
               JOptionPane::ERROR_MESSAGE);
       return false;
   } else if (levelXings.size() == 1) {
       levelXing = levelXings.at(0);
   } else {
       LayoutBlock* xingBlockA = nullptr;
       xingBlockA = getBlockFromEntry(blockACComboBox);
       if (xingBlockA == nullptr) {
           return false;
       }

       LayoutBlock* xingBlockC = getBlockFromEntry(blockBDComboBox);
       if (xingBlockC == nullptr) {
           return false;
       }

       int foundCount = 0;
       //make two block tests first
       for (LevelXing* x : layoutEditor->getLevelXings()) {
           LayoutBlock* xA = nullptr;
           LayoutBlock* xB = nullptr;
           LayoutBlock* xC = nullptr;
           LayoutBlock* xD = nullptr;
           LayoutBlock* xAC = x->getLayoutBlockAC();
           LayoutBlock* xBD = x->getLayoutBlockBD();
           if (x->getConnectA() != nullptr) {
               xA = ((TrackSegment*) x->getConnectA())->getLayoutBlock();
           }
           if (x->getConnectB() != nullptr) {
               xB = ((TrackSegment*) x->getConnectB())->getLayoutBlock();
           }
           if (x->getConnectC() != nullptr) {
               xC = ((TrackSegment*) x->getConnectC())->getLayoutBlock();
           }
           if (x->getConnectD() != nullptr) {
               xD = ((TrackSegment*) x->getConnectD())->getLayoutBlock();
           }
           if (((xA != nullptr) && (xC != nullptr) && (((xA == xingBlockA) && (xC == xingBlockC))
                   || ((xA == xingBlockC) && (xC == xingBlockA))))
                   || ((xB != nullptr) && (xD != nullptr) && (((xB == xingBlockA) && (xD == xingBlockC))
                   || ((xB == xingBlockC) && (xD == xingBlockA))))) {
               levelXing = x;
               foundCount++;
           } else if ((xAC != nullptr) && (xBD != nullptr) && (((xAC == xingBlockA) && (xBD == xingBlockC))
                   || ((xAC == xingBlockC) && (xBD == xingBlockA)))) {
               levelXing = x;
               foundCount++;
           }
       }
       if (foundCount == 0) {
           //try one block test
           for (LevelXing* x : layoutEditor->getLevelXings()) {
               if ((xingBlockA == x->getLayoutBlockAC()) || (xingBlockA == x->getLayoutBlockBD())) {
                   levelXing = x;
                   foundCount++;
               }
           }
       }
       if (foundCount > 1) {
           JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                   tr("Error - The entered block names match \"%1\" level crossings.\nPlease enter block names that match only one level crossing.").arg(
                           " " + QString::number(foundCount) + " "),
                   tr("Error"),
                   JOptionPane::ERROR_MESSAGE);
           return false;
       }
       if (levelXing == nullptr) {
           JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                   tr("Error - No level crossing matches the block(s)\nentered. Please try again or cancel."),
                   tr("Error"),
                   JOptionPane::ERROR_MESSAGE);
           return false;
       }
   }
 }

 QPointF coordsA = levelXing->getCoordsA();
 QPointF coordsC = levelXing->getCoordsC();
 placeSignalDirectionDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsA));

 return true;
}   //getLevelCrossingInformation

/*private*/ bool LayoutEditorTools::getXingSignalHeadInformation() {
    // note that all heads are optional, but pairs must be present
    aHead = getSignalHeadFromEntry(aSignalHeadComboBox,false,setSignalsAtLevelXingFrame);
    bHead = getSignalHeadFromEntry(bSignalHeadComboBox,false,setSignalsAtLevelXingFrame);
    cHead = getSignalHeadFromEntry(cSignalHeadComboBox,false,setSignalsAtLevelXingFrame);
    dHead = getSignalHeadFromEntry(dSignalHeadComboBox,false,setSignalsAtLevelXingFrame);
    if ( ((aHead!=nullptr) && (cHead==nullptr)) || ((aHead==nullptr) && (cHead!=nullptr)) ||
            ((bHead!=nullptr) && (dHead==nullptr)) || ((bHead==nullptr) && (dHead!=nullptr)) ) {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("SignalsError14"),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
     QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Error"), tr("Error - This tool requires signal heads be entered as pairs, A and C,\nand/or B and D. You entered only one head of a pair. "));
        return false;
    }
    if ( (aHead==nullptr) && (bHead==nullptr) && (cHead==nullptr) && (dHead==nullptr) ) {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - No signal heads entered.\nPlease enter signal heads or cancel."),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
     QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Error"), tr("Error - No signal heads entered.\nPlease enter signal heads or cancel."));
        return false;
    }
    return true;
}
/*private*/ void LayoutEditorTools::placeXingA()
{
if (testIcon == nullptr)
testIcon = signalIconEditor->getIcon(0);
QString signalHeadName = aSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

    QPointF coordsA = levelXing->getCoordsA();
    QPointF delta = QPointF(0.0, +shift);

    delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
    QPointF where = MathUtil::add(coordsA, delta);
    setSignalHeadOnPanel(placeSignalDirectionDEG + 180.0, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeXingB() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = bSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

    QPointF coordsB = levelXing->getCoordsB();
    QPointF coordsD = levelXing->getCoordsD();

    double directionDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsD));
    QPointF delta = QPointF(0.0, -shift);

    delta = MathUtil::rotateDEG(delta, directionDEG);
    QPointF where = MathUtil::add(coordsB, delta);
    setSignalHeadOnPanel(directionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeXingC() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = cSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
        qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


    QPointF coordsC = levelXing->getCoordsC();
    QPointF delta = QPointF(0.0, -shift);

    delta = MathUtil::rotateDEG(delta, placeSignalDirectionDEG);
    QPointF where = MathUtil::add(coordsC, delta);
    setSignalHeadOnPanel(placeSignalDirectionDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::placeXingD() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = dSignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
    qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

    QPointF coordsB = levelXing->getCoordsB();
    QPointF coordsD = levelXing->getCoordsD();

    double directionDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsD, coordsB));
    double diffDirDEG = MathUtil::diffAngleDEG(placeSignalDirectionDEG, directionDEG + 180.0);
    QPointF delta = QPointF(-shift * qCos(qDegreesToRadians(diffDirDEG)), -shift);

    delta = MathUtil::rotateDEG(delta, directionDEG);
    QPointF where = MathUtil::add(coordsD, delta);
    setSignalHeadOnPanel(directionDEG, signalHeadName, where);
}

//@SuppressWarnings("NULL")
/*private*/ void LayoutEditorTools::setLogicXing(SignalHead* head, TrackSegment* track, LayoutBlock*crossBlock,
            TrackSegment* crossTrack1, TrackSegment* crossTrack2, QString headName) {
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Error"), tr("Error - The two blocks entered do not join at an anchor point.\nPlease enter the correct blocks and try again."));
        return;
    }
    Sensor* occupancy = NULL;
    Sensor* crossOccupancy = NULL;
    Sensor* track1Occupancy = NULL;
    Sensor* track2Occupancy = NULL;
    SignalHead* nextHead = NULL;
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
     QMessageBox::information(setSignalsAtLevelXingFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    occupancy = block->getOccupancySensor();
    if (occupancy==nullptr)
    {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }
    if (crossBlock!=nullptr) {
        crossOccupancy = crossBlock->getOccupancySensor();
    }
    if (crossTrack1!=nullptr) {
        block = crossTrack1->getLayoutBlock();
        if (block!=nullptr) {
            track1Occupancy = block->getOccupancySensor();
            if (track1Occupancy==crossOccupancy) track1Occupancy = NULL;
        }
    }
    if (crossTrack2!=nullptr) {
        block = crossTrack2->getLayoutBlock();
        if (block!=nullptr) {
            track2Occupancy = block->getOccupancySensor();
            if ( (track2Occupancy==crossOccupancy) ||
                 (track2Occupancy==track1Occupancy) ) track2Occupancy = NULL;
        }
    }
    nextHead = getNextSignalFromObject(track,levelXing,
                            head->getSystemName(), setSignalsAtXoverTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
        return;
    }
    if ( (crossOccupancy==nullptr) && (track1Occupancy==nullptr) && (track2Occupancy==nullptr) ) {
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("SignalsWarn1"),
//                    new Object[]{headName}),
//                        NULL,JOptionPane::WARNING_MESSAGE);
     QMessageBox::warning(setSignalsAtLevelXingFrame, tr("Warning"), tr("Warning - Logic was set up at signal head \"%1\", but no sensors\nto protect for cross traffic at the level crossing were found.").arg(headName));
    }
    if (!initializeBlockBossLogic(head->getSystemName())) return;
    logic->setMode(BlockBossLogic::SINGLEBLOCK);
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    if (crossOccupancy!=nullptr) {
        logic->setSensor2(crossOccupancy->getSystemName());
        if (track1Occupancy!=nullptr) {
            logic->setSensor3(track1Occupancy->getSystemName());
            if (track2Occupancy!=nullptr)
                logic->setSensor4(track2Occupancy->getSystemName());
        }
        else if (track2Occupancy!=nullptr)
            logic->setSensor3(track2Occupancy->getSystemName());
    }
    else if (track1Occupancy!=nullptr) {
        logic->setSensor2(track1Occupancy->getSystemName());
        if (track2Occupancy!=nullptr)
            logic->setSensor3(track2Occupancy->getSystemName());
    }
    else if (track2Occupancy!=nullptr)
        logic->setSensor2(track2Occupancy->getSystemName());
    finalizeBlockBossLogic();
}
#endif
/**
 * Tool to set signals at throat-to-throat turnouts, including placing the
 *		signal icons and setup of signal logic for each signal head
 * <P>
 * This tool can only be accessed from the Tools menu. There is no access
 *		from a turnout pop-up menu.
 * <P>
 * This tool requires a situation where two turnouts are connected throat-
 *		to-throat by a single "short" track segment.  The actual length of
 *		the track segment is not tested. If this situation is not found,
 *		and error message is sent to the user.  To get started with this
 *      the user needs to enter at least one of the two connected turnouts.
 * <P>
 * This tool assumes two turnouts connected throat-to-throat, as would be
 *		used to represent a double slip turnout. The turnouts may be either
 *		left-handed, right-handed, wye, or any pair of these. This tool also
 *		assumes that there are no signals at the throat junction. The signal
 *		heads will be rotated to face outward--away from the throats. Four
 *		sets of one or two signal heads will be placed, one at each of the
 *		converging and diverging for each turnout.
 * <P>
 * This tool assumes that each of the four tracks is contained in a
 *		different block-> Things work best if the two throat-to-throat
 *		turnouts are in their own separate block, but this is not necessary.
 * <P>
 * This tool will place icons on the outside edges of each turnout.
 * <P>
 * At least one signal at each of the four connection points is
 *		required. A second signal at each is optional.
 * <P>
 * This tool only places signal icons if the turnout is either mostly vertical
 *		or mostly horizontal. Some user adjustment may be needed.
 */

/*public*/ void LayoutEditorTools::setSignalsAtTToTTurnouts( MultiIconEditor* theEditor, JFrame* theFrame )
{
 signalIconEditor = theEditor;
 signalFrame = (JmriJFrame*)theFrame;
 if (setSignalsAtTToTOpen) {
     setSignalsAtTToTFrame->setVisible(true);
     return;
 }
 // Initialize if needed
 if (setSignalsAtTToTFrame == nullptr)
 {
     setSignalsAtTToTFrame = new JmriJFrameX( tr("SignalsAtTToTTurnout"), false, true );
     setSignalsAtTToTFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtTToTTurnout", true);
     setSignalsAtTToTFrame->setLocation(70,30);
     QWidget* theContentPane = setSignalsAtTToTFrame->getContentPane();
     QVBoxLayout* centralWidgetLayout;
     theContentPane->setLayout(centralWidgetLayout = new QVBoxLayout(theContentPane/*, BoxLayout.Y_AXIS*/));
     JPanel* panel1a = new JPanel(new FlowLayout());
     ttotTurnoutName1Label = new JLabel(tr("Turnout") + " 1 "
             + tr("Name"));
     panel1a->layout()->addWidget(ttotTurnoutName1Label);
     panel1a->layout()->addWidget(turnout1ComboBox);
     turnout1ComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
     theContentPane->layout()->addWidget(panel1a);

     JPanel* panel1b = new JPanel(new FlowLayout());
     ttotTurnoutName2Label = new JLabel(tr("Turnout") + " 2 "
             + tr("Name"));
     panel1b->layout()->addWidget(ttotTurnoutName2Label);
     panel1b->layout()->addWidget(turnout2ComboBox);
     turnout2ComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
     theContentPane->layout()->addWidget(panel1b);
     theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

     // Provide for retrieval of names of previously saved signal heads
     JPanel* panel20 = new JPanel(new FlowLayout());
     JLabel* shTitle = new JLabel(tr("Signal Heads"));
     panel20->layout()->addWidget(shTitle);
     panel20->layout()->addWidget(new JLabel("		"));
     panel20->layout()->addWidget(getSavedTToTSignalHeads = new QPushButton(tr("Get Saved")));
     //getSavedTToTSignalHeads.addActionListener((ActionEvent e) -> {
     connect(getSavedTToTSignalHeads, &QPushButton::clicked, [=]{
         setSignalsAtTToTTurnoutsGetSaved();
     });
     getSavedTToTSignalHeads->setToolTip(tr("Select to retrieve signal heads previously stored."));
     theContentPane->layout()->addWidget(panel20);
     theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

     JPanel* panel2a = new JPanel(new FlowLayout());
     panel2a->layout()->addWidget(new JLabel("   "));
     panel2a->layout()->addWidget(setPlaceAllHeads);
     setPlaceAllHeads->setToolTip(tr("Check to place all signal head icons"));
     //setPlaceAllHeads.addActionListener((ActionEvent e) -> {
     connect(setPlaceAllHeads, &QCheckBox::clicked, [=]{
         bool isSelected = setPlaceAllHeads->isChecked();
         //(de)select all checkboxes
         setA1TToTHead->setChecked(isSelected);
         setA2TToTHead->setChecked(isSelected);
         setB1TToTHead->setChecked(isSelected);
         setB2TToTHead->setChecked(isSelected);
         setC1TToTHead->setChecked(isSelected);
         setC2TToTHead->setChecked(isSelected);
         setD1TToTHead->setChecked(isSelected);
         setD2TToTHead->setChecked(isSelected);
     });
     panel2a->layout()->addWidget(new JLabel("  "));
     panel2a->layout()->addWidget(setupAllLogic);
     setupAllLogic->setToolTip(tr("Check to set up Simple Signal Logic for all Signal Heads"));
     //setupAllLogic.addActionListener((ActionEvent e) -> {
     connect(setupAllLogic, &QCheckBox::clicked, [=]{
         bool isSelected = setupAllLogic->isChecked();
         //(de)select all checkboxes
         setupA1TToTLogic->setChecked(isSelected);
         setupA2TToTLogic->setChecked(isSelected);
         setupB1TToTLogic->setChecked(isSelected);
         setupB2TToTLogic->setChecked(isSelected);
         setupC1TToTLogic->setChecked(isSelected);
         setupC2TToTLogic->setChecked(isSelected);
         setupD1TToTLogic->setChecked(isSelected);
         setupD2TToTLogic->setChecked(isSelected);
     });
     theContentPane->layout()->addWidget(panel2a);
     theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

     //Signal heads located at turnout 1
     JPanel* panel20a = new JPanel(new FlowLayout());
     panel20a->layout()->addWidget(new JLabel(tr("Signal located at")
             + " " + tr("Turnout") + " 1 - "
             + tr("Continuing Track")));
     theContentPane->layout()->addWidget(panel20a);

     QWidget* panel21 = new QWidget();
     panel21->setLayout(new QHBoxLayout());
     panel21->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 2 - "+tr("continuing track")+" : "));
     panel21->layout()->addWidget(a1TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel21);
     a1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel22 = new QWidget();
     panel22->setLayout(new QHBoxLayout());
     panel22->layout()->addWidget(new QLabel(tr("Or Both")+" 2 "+tr("Tracks)")+"   "));
     panel22->layout()->addWidget(setA1TToTHead);
     setA1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel22->layout()->addWidget(new QLabel("  "));
     panel22->layout()->addWidget(setupA1TToTLogic);
     setupA1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel22);
     QWidget* panel23 = new QWidget();
     panel23->setLayout(new QHBoxLayout());
     panel23->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 2 - "+tr("diverging track")+" : "));
     panel23->layout()->addWidget(a2TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel23);
     a2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel24 = new QWidget();
     panel24->setLayout(new QHBoxLayout());
     panel24->layout()->addWidget(new QLabel("                "));
     panel24->layout()->addWidget(setA2TToTHead);
     setA2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel24->layout()->addWidget(new QLabel("  "));
     panel24->layout()->addWidget(setupA2TToTLogic);
     setupA2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel24);
     QWidget* panel31x = new QWidget();
     panel31x->setLayout(new QHBoxLayout());
     panel31x->layout()->addWidget(new QLabel(tr("Signal located at ")+" "+tr("Turnout")+" 1 - "+
                                     tr("diverging track")));
     centralWidgetLayout->addWidget(panel31x);
     QWidget* panel31 = new QWidget();
     panel31->setLayout(new QHBoxLayout());
     panel31->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 2 - "+tr("continuing track")+" : "));
     panel31->layout()->addWidget(b1TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel31);
     b1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel32 = new QWidget();
     panel32->setLayout(new QHBoxLayout());
     panel32->layout()->addWidget(new QLabel(tr("(or both Turnout")+" 2 "+tr("Tracks)")+"   "));
     panel32->layout()->addWidget(setB1TToTHead);
     setB1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel32->layout()->addWidget(new QLabel("  "));
     panel32->layout()->addWidget(setupB1TToTLogic);
     setupB1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel32);
     QWidget* panel33 = new QWidget();
     panel33->setLayout(new QHBoxLayout());
     panel33->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 2 - "+tr("diverging track")+" : "));
     panel33->layout()->addWidget(b2TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel33);
     b2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel34 = new QWidget();
     panel34->setLayout(new QHBoxLayout());
     panel34->layout()->addWidget(new QLabel("                "));
     panel34->layout()->addWidget(setB2TToTHead);
     setB2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel34->layout()->addWidget(new QLabel("  "));
     panel34->layout()->addWidget(setupB2TToTLogic);
     setupB2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel34);
     centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
     // Signal heads located at turnout 2
     QWidget* panel41x = new QWidget();
     panel41x->setLayout(new QHBoxLayout());
     panel41x->layout()->addWidget(new QLabel(tr("Signal located at ")+" "+tr("Turnout")+" 2 - "+
                                     tr("continuing track")));
     centralWidgetLayout->addWidget(panel41x);
     QWidget* panel41 = new QWidget();
     panel41->setLayout(new QHBoxLayout());
     panel41->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 1 - "+tr("continuing track")+" : "));
     panel41->layout()->addWidget(c1TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel41);
     c1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel42 = new QWidget();
     panel42->setLayout(new QHBoxLayout());
     panel42->layout()->addWidget(new QLabel(tr("Or Both")+" 1 "+tr("Tracks)")+"   "));
     panel42->layout()->addWidget(setC1TToTHead);
     setC1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel42->layout()->addWidget(new QLabel("  "));
     panel42->layout()->addWidget(setupC1TToTLogic);
     setupC1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel42);
     QWidget* panel43 = new QWidget();
     panel43->setLayout(new QHBoxLayout());
     panel43->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 1 - "+tr("diverging track")+" : "));
     panel43->layout()->addWidget(c2TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel43);
     c2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel44 = new QWidget();
     panel44->setLayout(new QHBoxLayout());
     panel44->layout()->addWidget(new QLabel("                "));
     panel44->layout()->addWidget(setC2TToTHead);
     setC2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel44->layout()->addWidget(new QLabel("  "));
     panel44->layout()->addWidget(setupC2TToTLogic);
     setupC2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel44);
     QWidget* panel51x = new QWidget();
     panel51x->setLayout(new QHBoxLayout());
     panel51x->layout()->addWidget(new QLabel(tr("Signal located at ")+" "+tr("Turnout")+" 2 - "+
                                     tr("diverging track")));
     centralWidgetLayout->addWidget(panel51x);
     QWidget* panel51 = new QWidget();
     panel51->setLayout(new QHBoxLayout());
     panel51->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 1 - "+tr("continuing track")+" : "));
     panel51->layout()->addWidget(d1TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel51);
     d1TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel52 = new QWidget();
     panel52->setLayout(new QHBoxLayout());
     panel52->layout()->addWidget(new QLabel(tr("Or Both")+" 1 "+tr("Tracks)")+"   "));
     panel52->layout()->addWidget(setD1TToTHead);
     setD1TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel52->layout()->addWidget(new QLabel("  "));
     panel52->layout()->addWidget(setupD1TToTLogic);
     setupD1TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel52);
     QWidget* panel53 = new QWidget();
     panel53->setLayout(new QHBoxLayout());
     panel53->layout()->addWidget(new QLabel(tr("Protects Turnout")+" 1 - "+tr("diverging track")+" : "));
     panel53->layout()->addWidget(d2TToTSignalHeadComboBox);
     centralWidgetLayout->addWidget(panel53);
     d2TToTSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
     QWidget* panel54 = new QWidget();
     panel54->setLayout(new QHBoxLayout());
     panel54->layout()->addWidget(new QLabel("                "));
     panel54->layout()->addWidget(setD2TToTHead);
     setD2TToTHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
     panel54->layout()->addWidget(new QLabel("  "));
     panel54->layout()->addWidget(setupD2TToTLogic);
     setupD2TToTLogic->setToolTip(tr("Check to set up Simple Signal Logic for above signal head."));
     centralWidgetLayout->addWidget(panel54);
     centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
     QWidget* panel6 = new QWidget();
     panel6->setLayout(new QHBoxLayout());
     panel6->layout()->addWidget(changeTToTSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
//        changeTToTSignalIcon->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
     connect(changeTToTSignalIcon, &QPushButton::clicked, [=]{
                    signalFrame->setVisible(true);
//                }
            });
     changeTToTSignalIcon->setToolTip( tr("Change Signal Head IconHint") );
     panel6->layout()->addWidget(new QLabel("  "));
     panel6->layout()->addWidget(setTToTSignalsDone = new QPushButton(tr("Done")));
//        setTToTSignalsDone->addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setTToTSignalsDonePressed(e);
//            }
//        });
     connect(setTToTSignalsDone, SIGNAL(clicked()), this, SLOT(setTToTSignalsDonePressed()));
     setTToTSignalsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
     panel6->layout()->addWidget(setTToTSignalsCancel = new QPushButton(tr("Cancel")));
//        setTToTSignalsCancel->addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setTToTSignalsCancelPressed(e);
//            }
//        });
     connect(setTToTSignalsCancel, SIGNAL(clicked()), this, SLOT(setTToTSignalsCancelPressed()));
     setTToTSignalsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
     centralWidgetLayout->addWidget(panel6);
//        setSignalsAtTToTFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                setTToTSignalsCancelPressed(nullptr);
//            }
//        });
}
setSignalsAtTToTFrame->pack();
setSignalsAtTToTFrame->setVisible(true);
setSignalsAtTToTOpen = true;
}

/*private*/ bool LayoutEditorTools::getTToTTurnoutInformation() {
 int type = 0;
 QObject* connect = NULL;

 turnout1 = NULL;
 turnout2 = NULL;

 layoutTurnout1 = NULL;
 layoutTurnout2 = NULL;

 if (!setSignalsAtThroatToThroatTurnoutsFromMenuFlag)
 {
   ttotTurnoutName1 = turnout1ComboBox->getSelectedItemDisplayName();
   if (ttotTurnoutName1.isNull())
   {
       ttotTurnoutName1 = "";
   }
 }
 if (ttotTurnoutName1.isEmpty())
 {
  // turnout 1 not entered, test turnout 2
  ttotTurnoutName2 = turnout2ComboBox->getSelectedItemDisplayName();
  if (ttotTurnoutName2.isNull()) {
      ttotTurnoutName2 = "";
  }
  if (ttotTurnoutName2.isEmpty())
  {
   // no entries in turnout fields
      JOptionPane::showMessageDialog(setSignalsAtTToTFrame,tr("SignalsError1"),
                          tr("Error"),JOptionPane::ERROR_MESSAGE);
         return false;
  }
  turnout2 = (Turnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(ttotTurnoutName2);
  if (turnout2==nullptr)
  {
    JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
        tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
            ttotTurnoutName2), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
  return false ;
  }
  if ( (turnout2->getUserName()==nullptr) || (turnout2->getUserName()==("")) ||
                          turnout2->getUserName()!=(ttotTurnoutName2) ) {
//         str = str.toUpper();
      turnout2ComboBox->setSelectedItem(turnout2);
  }
  layoutTurnout2 = getLayoutTurnoutFromTurnout(turnout2,false,ttotTurnoutName2,setSignalsAtTToTFrame);
  if (layoutTurnout2==nullptr)
      return false;
  // have turnout 2 and layout turnout 2 - look for turnout 1
  connectorTrack = (TrackSegment*)layoutTurnout2->getConnectA();
  if (connectorTrack == nullptr)
  {
      // Inform user of error, and terminate
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                    tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalsAtTToTFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."));
      return false;
  }
  type = connectorTrack->getType1();
  connect = connectorTrack->getConnect1();
  if (connect == layoutTurnout2) {
      type = connectorTrack->getType2();
      connect = connectorTrack->getConnect2();
  }
  if ( (type != LayoutEditor::TURNOUT_A) || (connect==nullptr) ) {
      // Not two turnouts connected throat-to-throat by a single Track Segment
      // Inform user of error and terminate
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                    tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalsAtTToTFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."));
      return false;
  }
  layoutTurnout1 = (LayoutTurnout*)connect;
  turnout1 = layoutTurnout1->getTurnout();
  if (turnout1==nullptr) {
         JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                 tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
                     tr("Error"),JOptionPane::ERROR_MESSAGE);
      return false;
  }
  turnout1ComboBox->setSelectedItem(turnout1);
 }
 else {
     // something was entered in the turnout 1 field
     turnout1 = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(ttotTurnoutName1);
     if (turnout1==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
                    ttotTurnoutName1), tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
         return false ;
     }
     if ( (turnout1->getUserName()==nullptr) || (turnout1->getUserName()==("")) ||
                             turnout1->getUserName()!=(ttotTurnoutName1) ) {
//         str = str.toUpper();
         turnout1ComboBox->setSelectedItem(turnout1);
     }
     // have turnout 1 - get corresponding layoutTurnout
     layoutTurnout1 = getLayoutTurnoutFromTurnout(turnout1,false,ttotTurnoutName1,setSignalsAtTToTFrame);
     if (layoutTurnout1 == nullptr)
         return false;
     turnout1ComboBox->setSelectedItem(layoutTurnout1->getTurnout());
     // have turnout 1 and layout turnout 1 - was something entered for turnout 2
     ttotTurnoutName2 = turnout2ComboBox->getSelectedItemDisplayName();
     if (ttotTurnoutName2.isNull()) {
         ttotTurnoutName2 = "";
     }
     if (ttotTurnoutName2.isEmpty()) {

         // no entry for turnout 2
         connectorTrack = (TrackSegment*)layoutTurnout1->getConnectA();
         if (connectorTrack == nullptr) {
             // Inform user of error, and terminate
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                        tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
             return false;
         }
         type = connectorTrack->getType1();
         connect = connectorTrack->getConnect1();
         if (connect == layoutTurnout1) {
             type = connectorTrack->getType2();
             connect = connectorTrack->getConnect2();
         }
         if ( (type != LayoutEditor::TURNOUT_A) || (connect==nullptr) ) {
             // Not two turnouts connected throat-to-throat by a single Track Segment
             // Inform user of error and terminate
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                        tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
             return false;
         }
         layoutTurnout2 = (LayoutTurnout*)connect;
         turnout2 = layoutTurnout2->getTurnout();
         if (turnout2==nullptr) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                        tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
             return false;
         }
         turnout2ComboBox->setSelectedItem(turnout2);

     }
     else {
         // turnout 2 entered also
         turnout2 = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(ttotTurnoutName2);
         if (turnout2==nullptr) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
                            ttotTurnoutName2), tr("Error"),
                                JOptionPane::ERROR_MESSAGE);
             return false ;
         }
         if ( (turnout2->getUserName()==nullptr) || (turnout2->getUserName()==("")) ||
                             turnout2->getUserName()!=(ttotTurnoutName2) ) {
          turnout2ComboBox->setSelectedItem(turnout2);
         }
         layoutTurnout2 = getLayoutTurnoutFromTurnout(turnout2,false,ttotTurnoutName2,setSignalsAtTToTFrame);
         if (layoutTurnout2==nullptr)
             return false;
         turnout2ComboBox->setSelectedItem(layoutTurnout2->getTurnout());
         // check that layout turnout 1 and layout turnout 2 are connected throat-to-throat
         if (layoutTurnout1->getConnectA()!=layoutTurnout2->getConnectA()) {
             // Not two turnouts connected throat-to-throat by a single Track Segment
             // Inform user of error and terminate
//                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                        tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
             QMessageBox::critical(setSignalsAtTToTFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH, LH, or WYE)\nconnected throat-to-throat by a single track segment."));
             return false;
         }
         connectorTrack = (TrackSegment*)layoutTurnout1->getConnectA();
     }
 }
 // have both turnouts, correctly connected - complete initialization
 layoutTurnout1Horizontal = false;
 layoutTurnout1Vertical = false;
 layoutTurnout2ThroatLeft = false;
 layoutTurnout2Vertical = false;
 layoutTurnout1ThroatLeft = false;
 layoutTurnout1ThroatUp = false;
 layoutTurnout2ThroatLeft = false;
 layoutTurnout2ThroatUp = false;
 layoutTurnout1BUp = false;
 layoutTurnout1BLeft = false;
 layoutTurnout2BUp = false;
 layoutTurnout2BLeft = false;
 double delX = layoutTurnout1->getCoordsA().x() - layoutTurnout1->getCoordsB().x();
 double delY = layoutTurnout1->getCoordsA().y() - layoutTurnout1->getCoordsB().y();
 if (qAbs(delX) > 2.0*qAbs(delY)) {
     layoutTurnout1Horizontal = true;
     if (delX < 0.0) layoutTurnout1ThroatLeft = true;
     if (layoutTurnout1->getCoordsB().y() < layoutTurnout1->getCoordsC().y())
         layoutTurnout1BUp = true;
 }
    else if (qAbs(delY) > 2.0*qAbs(delX)) {
        layoutTurnout1Vertical = true;
        if (delY <0.0) layoutTurnout1ThroatUp = true;
        if (layoutTurnout1->getCoordsB().x() < layoutTurnout1->getCoordsC().x())
            layoutTurnout1BLeft = true;
    }
    delX = layoutTurnout2->getCoordsA().x() - layoutTurnout2->getCoordsB().x();
    delY = layoutTurnout2->getCoordsA().y() - layoutTurnout2->getCoordsB().y();
    if (qAbs(delX) > 2.0*qAbs(delY)) {
        layoutTurnout2Horizontal = true;
        if (delX < 0.0) layoutTurnout2ThroatLeft = true;
        if (layoutTurnout2->getCoordsB().y() < layoutTurnout2->getCoordsC().y())
            layoutTurnout2BUp = true;
    }
    else if (qAbs(delY) > 2.0*qAbs(delX)) {
        layoutTurnout2Vertical = true;
        if (delY <0.0) layoutTurnout2ThroatUp = true;
        if (layoutTurnout2->getCoordsB().x() < layoutTurnout2->getCoordsC().x())
            layoutTurnout2BLeft = true;
    }
    return true;
 }

/*private*/ void LayoutEditorTools::setTToTSignalsDonePressed (JActionEvent* /*a*/) {
    if ( !getTToTTurnoutInformation() ) return;
    if ( !getTToTSignalHeadInformation() ) return;

    // place signal icons if requested, and assign signal heads to this turnout
    QString signalHeadName = a1TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if (setA1TToTHead->isChecked()) {
        if (isHeadOnPanel(a1TToTHead) &&
            (a1TToTHead!=getHeadFromName(layoutTurnout1->getSignalB1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout1Horizontal) && (!layoutTurnout1Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (a1TToTHead!=getHeadFromName(layoutTurnout1->getSignalB1Name())) {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalB1Name());
                removeAssignment(a1TToTHead);
                layoutTurnout1->setSignalB1Name(signalHeadName);
                needRedraw = true;
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout1->getSignalB1Name());
            if (layoutTurnout1->getContinuingSense()==Turnout::CLOSED)
                placeA1TToT(signalHeadName);
            else
                placeB1TToT(signalHeadName);
            removeAssignment(a1TToTHead);
            layoutTurnout1->setSignalB1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(a1TToTHead,layoutTurnout1);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a1TToTHead) &&
                                isHeadAssignedAnywhere(a1TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                                             return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalB1Name());
                removeAssignment(a1TToTHead);
                layoutTurnout1->setSignalB1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case - assigned to a different position on the same turnout.
        }
    }

    signalHeadName = a2TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (a2TToTHead!=nullptr) && setA2TToTHead->isChecked() ) {
        if (isHeadOnPanel(a2TToTHead) &&
            (a2TToTHead!=getHeadFromName(layoutTurnout1->getSignalB2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout1Horizontal) && (!layoutTurnout1Vertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (a2TToTHead!=getHeadFromName(layoutTurnout1->getSignalB2Name())) {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalB2Name());
                removeAssignment(a2TToTHead);
                layoutTurnout1->setSignalB2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout1->getSignalB2Name());
            if (layoutTurnout1->getContinuingSense()==Turnout::CLOSED)
                placeA2TToT(signalHeadName);
            else
                placeB2TToT(signalHeadName);
            removeAssignment(a2TToTHead);
            layoutTurnout1->setSignalB2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (a2TToTHead!=nullptr) {
        int assigned = isHeadAssignedHere(a2TToTHead,layoutTurnout1);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a2TToTHead) &&
                                isHeadAssignedAnywhere(a2TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalB2Name());
                removeAssignment(a2TToTHead);
                layoutTurnout1->setSignalB2Name(signalHeadName);
            }
        }
        else if (assigned!=B2) {
// need to figure out what to do in this case.
        }
    }
    else if (a2TToTHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout1->getSignalB2Name());
        layoutTurnout1->setSignalB2Name("");
    }

    signalHeadName = b1TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if (setB1TToTHead->isChecked()) {
        if (isHeadOnPanel(b1TToTHead) &&
            (b1TToTHead!=getHeadFromName(layoutTurnout1->getSignalC1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout1Horizontal) && (!layoutTurnout1Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            if (b1TToTHead!=getHeadFromName(layoutTurnout1->getSignalC1Name())) {
                removeSignalHeadFromPanel(layoutTurnout->getSignalC1Name());
                removeAssignment(b1TToTHead);
                layoutTurnout1->setSignalC1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout1->getSignalC1Name());
            if (layoutTurnout1->getContinuingSense()==Turnout::CLOSED)
                placeB1TToT(signalHeadName);
            else
                placeA1TToT(signalHeadName);
            removeAssignment(b1TToTHead);
            layoutTurnout1->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(b1TToTHead,layoutTurnout1);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b1TToTHead) &&
                                isHeadAssignedAnywhere(b1TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalC1Name());
                removeAssignment(b1TToTHead);
                layoutTurnout1->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
// need to figure out what to do in this case.
        }
    }

    signalHeadName = b2TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (b2TToTHead!=nullptr) && setB2TToTHead->isChecked() ) {
        if (isHeadOnPanel(b2TToTHead) &&
            (b2TToTHead!=getHeadFromName(layoutTurnout1->getSignalC2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout1Horizontal) && (!layoutTurnout1Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (b2TToTHead!=getHeadFromName(layoutTurnout1->getSignalC2Name())) {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalC2Name());
                removeAssignment(b2TToTHead);
                layoutTurnout1->setSignalC2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout1->getSignalC2Name());
            if (layoutTurnout1->getContinuingSense()==Turnout::CLOSED)
                placeB2TToT(signalHeadName);
            else
                placeA2TToT(signalHeadName);
            removeAssignment(b2TToTHead);
            layoutTurnout1->setSignalC2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (b2TToTHead!=nullptr) {
        int assigned = isHeadAssignedHere(b2TToTHead,layoutTurnout1);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b2TToTHead) &&
                                isHeadAssignedAnywhere(b2TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout1->getSignalC2Name());
                removeAssignment(b2TToTHead);
                layoutTurnout1->setSignalC2Name(signalHeadName);
            }
        }
        else if (assigned!=C2) {
// need to figure out what to do in this case.
        }
    }
    else if (b2TToTHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout1->getSignalC2Name());
        layoutTurnout1->setSignalC2Name("");
    }
    // signal heads on turnout 2
    signalHeadName = c1TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if (setC1TToTHead->isChecked()) {
        if (isHeadOnPanel(c1TToTHead) &&
            (c1TToTHead!=getHeadFromName(layoutTurnout2->getSignalB1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout2Horizontal) && (!layoutTurnout2Vertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (c1TToTHead!=getHeadFromName(layoutTurnout2->getSignalB1Name())) {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalB1Name());
                removeAssignment(c1TToTHead);
                layoutTurnout2->setSignalB1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout2->getSignalB1Name());
            if (layoutTurnout2->getContinuingSense()==Turnout::CLOSED)
                placeC1TToT(signalHeadName);
            else
                placeD1TToT(signalHeadName);
            removeAssignment(c1TToTHead);
            layoutTurnout2->setSignalB1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(c1TToTHead,layoutTurnout2);
        if (assigned == NONE) {
            if ( isHeadOnPanel(c1TToTHead) &&
                                isHeadAssignedAnywhere(c1TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);

                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalB1Name());
                removeAssignment(c1TToTHead);
                layoutTurnout2->setSignalB1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case.
        }
    }

    signalHeadName = c2TToTSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (c2TToTHead!=nullptr) && setC2TToTHead->isChecked() ) {
        if (isHeadOnPanel(c2TToTHead) &&
            (c2TToTHead!=getHeadFromName(layoutTurnout2->getSignalB2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout2Horizontal) && (!layoutTurnout2Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (c2TToTHead!=getHeadFromName(layoutTurnout2->getSignalB2Name())) {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalB2Name());
                removeAssignment(c2TToTHead);
                layoutTurnout2->setSignalC2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout2->getSignalB2Name());
            if (layoutTurnout2->getContinuingSense()==Turnout::CLOSED)
                placeC2TToT(signalHeadName);
            else
                placeD2TToT(signalHeadName);
            removeAssignment(c2TToTHead);
            layoutTurnout2->setSignalB2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (c2TToTHead!=nullptr) {
        int assigned = isHeadAssignedHere(c2TToTHead,layoutTurnout2);
        if (assigned == NONE) {
            if ( isHeadOnPanel(c2TToTHead) &&
                                isHeadAssignedAnywhere(c2TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalB2Name());
                removeAssignment(c2TToTHead);
                layoutTurnout2->setSignalB2Name(signalHeadName);
            }
        }
        else if (assigned!=B2) {
// need to figure out what to do in this case.
        }
    }
    else if (c2TToTHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout2->getSignalB2Name());
        layoutTurnout2->setSignalB2Name("");
    }
    if (setD1TToTHead->isChecked()) {
        if (isHeadOnPanel(d1TToTHead) &&
            (d1TToTHead!=getHeadFromName(layoutTurnout2->getSignalC1Name()))) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout2Horizontal) && (!layoutTurnout2Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (d1TToTHead!=getHeadFromName(layoutTurnout2->getSignalC1Name())) {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalC1Name());
                removeAssignment(d1TToTHead);
                layoutTurnout2->setSignalC1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout2->getSignalC1Name());
            if (layoutTurnout2->getContinuingSense()==Turnout::CLOSED)
                placeD1TToT(signalHeadName);
            else
                placeC1TToT(signalHeadName);
            removeAssignment(d1TToTHead);
            layoutTurnout2->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(d1TToTHead,layoutTurnout2);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d1TToTHead) &&
                                isHeadAssignedAnywhere(d1TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalC1Name());
                removeAssignment(d1TToTHead);
                layoutTurnout2->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
// need to figure out what to do in this case.
        }
    }
    if ( (d2TToTHead!=nullptr) && setD2TToTHead->isChecked() ) {
        if (isHeadOnPanel(d2TToTHead) &&
            (d2TToTHead!=getHeadFromName(layoutTurnout2->getSignalC2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnout2Horizontal) && (!layoutTurnout2Vertical) ) {
            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (d2TToTHead!=getHeadFromName(layoutTurnout2->getSignalC2Name())) {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalC2Name());
                removeAssignment(d2TToTHead);
                layoutTurnout2->setSignalC2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnout2->getSignalC2Name());
            if (layoutTurnout2->getContinuingSense()==Turnout::CLOSED)
                placeD2TToT(signalHeadName);
            else
                placeC2TToT(signalHeadName);
            removeAssignment(d2TToTHead);
            layoutTurnout2->setSignalC2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (d2TToTHead!=nullptr) {
        int assigned = isHeadAssignedHere(d2TToTHead,layoutTurnout2);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d2TToTHead) &&
                                isHeadAssignedAnywhere(d2TToTHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnout2->getSignalC2Name());
                removeAssignment(d2TToTHead);
                layoutTurnout2->setSignalC2Name(signalHeadName);
            }
        }
        else if (assigned!=C2) {
// need to figure out what to do in this case.
        }
    }
    else if (d2TToTHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnout2->getSignalC2Name());
        layoutTurnout2->setSignalC2Name("");
    }

    // setup logic if requested
    if (setupA1TToTLogic->isChecked() || setupA2TToTLogic->isChecked()) {
        setLogicTToT(a1TToTHead,(TrackSegment*)layoutTurnout2->getConnectB(),a2TToTHead,
                (TrackSegment*)layoutTurnout2->getConnectC(),setupA1TToTLogic->isChecked(),
                setupA2TToTLogic->isChecked(),true,layoutTurnout2,layoutTurnout1);
    }
    if (setupB1TToTLogic->isChecked() || setupB2TToTLogic->isChecked()) {
        setLogicTToT(b1TToTHead,(TrackSegment*)layoutTurnout2->getConnectB(),b2TToTHead,
                (TrackSegment*)layoutTurnout2->getConnectC(),setupB1TToTLogic->isChecked(),
                setupB2TToTLogic->isChecked(),false,layoutTurnout2,layoutTurnout1);
    }
    if (setupC1TToTLogic->isChecked() || setupC2TToTLogic->isChecked()) {
        setLogicTToT(c1TToTHead,(TrackSegment*)layoutTurnout1->getConnectB(),c2TToTHead,
                (TrackSegment*)layoutTurnout1->getConnectC(),setupC1TToTLogic->isChecked(),
                setupC2TToTLogic->isChecked(),true,layoutTurnout1,layoutTurnout2);
    }
    if (setupD1TToTLogic->isChecked() || setupD2TToTLogic->isChecked()) {
        setLogicTToT(d1TToTHead,(TrackSegment*)layoutTurnout1->getConnectB(),d2TToTHead,
                (TrackSegment*)layoutTurnout1->getConnectC(),setupD1TToTLogic->isChecked(),
                setupD2TToTLogic->isChecked(),false,layoutTurnout1,layoutTurnout2);
    }
    // link the two turnouts
    layoutTurnout1->setLinkedTurnoutName(turnout2ComboBox->getSelectedItemDisplayName());
    layoutTurnout1->setLinkType(LayoutTurnout::THROAT_TO_THROAT);
    layoutTurnout2->setLinkedTurnoutName(turnout1ComboBox->getSelectedItemDisplayName());
    layoutTurnout2->setLinkType(LayoutTurnout::THROAT_TO_THROAT);
    // finish up
    setSignalsAtTToTOpen = false;
    setSignalsAtTToTFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}
/*private*/ bool LayoutEditorTools::getTToTSignalHeadInformation() {
 a1TToTHead = getSignalHeadFromEntry(a1TToTSignalHeadComboBox, true, setSignalsAtThroatToThroatTurnoutsFrame);
 if (a1TToTHead == nullptr) {
     return false;
 }
 a2TToTHead = getSignalHeadFromEntry(a2TToTSignalHeadComboBox, false, setSignalsAtThroatToThroatTurnoutsFrame);
 b1TToTHead = getSignalHeadFromEntry(b1TToTSignalHeadComboBox, true, setSignalsAtThroatToThroatTurnoutsFrame);
 if (b1TToTHead == nullptr) {
     return false;
 }
 b2TToTHead = getSignalHeadFromEntry(b2TToTSignalHeadComboBox, false, setSignalsAtThroatToThroatTurnoutsFrame);
 c1TToTHead = getSignalHeadFromEntry(c1TToTSignalHeadComboBox, true, setSignalsAtThroatToThroatTurnoutsFrame);
 if (c1TToTHead == nullptr) {
     return false;
 }
 c2TToTHead = getSignalHeadFromEntry(c2TToTSignalHeadComboBox, false, setSignalsAtThroatToThroatTurnoutsFrame);
 d1TToTHead = getSignalHeadFromEntry(d1TToTSignalHeadComboBox, true, setSignalsAtThroatToThroatTurnoutsFrame);
 if (d1TToTHead == nullptr) {
     return false;
 }
 d2TToTHead = getSignalHeadFromEntry(d2TToTSignalHeadComboBox, false, setSignalsAtThroatToThroatTurnoutsFrame);
 return true;
}

/*private*/ void LayoutEditorTools::placeA1TToT(QString headName) {
    // place head near the continuing track of turnout 1
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsB().x()),
            (int)(layoutTurnout1->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsB().x()),
            (int)(layoutTurnout1->getCoordsB().y()+4) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsB().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsB().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()+4) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4),
            (int)(layoutTurnout1->getCoordsB().y()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4),
            (int)(layoutTurnout1->getCoordsB().y()-testIcon->getIconHeight()) );
    }
}
/*private*/ void LayoutEditorTools::placeA2TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()+4) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout1->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout1->getCoordsB().y()+4) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4),
            (int)(layoutTurnout1->getCoordsB().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsB().y()-4-(2*testIcon->getIconHeight())) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsB().x()+4),
            (int)(layoutTurnout1->getCoordsB().y()-4-(2*testIcon->getIconHeight())) );
    }
}
/*private*/ void LayoutEditorTools::placeB1TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && layoutTurnout1BUp) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsC().x()),
            (int)(layoutTurnout1->getCoordsC().y()+4) );
    }
    else if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsC().x()),
            (int)(layoutTurnout1->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsC().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()+4) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsC().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4),
            (int)(layoutTurnout1->getCoordsC().y()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4),
            (int)(layoutTurnout1->getCoordsC().y()-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()-testIcon->getIconHeight()) );
    }
}
/*private*/ void LayoutEditorTools::placeB2TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && layoutTurnout1BUp) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()+4) );
    }
    else if( layoutTurnout1Horizontal && layoutTurnout1ThroatLeft && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && layoutTurnout1BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout1->getCoordsC().y()+4) );
    }
    else if( layoutTurnout1Horizontal && (!layoutTurnout1ThroatLeft) && (!layoutTurnout1BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout1->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4),
            (int)(layoutTurnout1->getCoordsC().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && layoutTurnout1ThroatUp && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && layoutTurnout1BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsC().x()+4),
            (int)(layoutTurnout1->getCoordsC().y()-4-(2*testIcon->getIconHeight())) );
    }
    else if( layoutTurnout1Vertical && (!layoutTurnout1ThroatUp) && (!layoutTurnout1BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout1->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout1->getCoordsC().y()-4-(2*testIcon->getIconHeight())) );
    }
}
/*private*/ void LayoutEditorTools::placeC1TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsB().x()),
            (int)(layoutTurnout2->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsB().x()),
            (int)(layoutTurnout2->getCoordsB().y()+4) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsB().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsB().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()+4) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4),
            (int)(layoutTurnout2->getCoordsB().y()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4),
            (int)(layoutTurnout2->getCoordsB().y()-testIcon->getIconHeight()) );
    }
}
/*private*/ void LayoutEditorTools::placeC2TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()+4) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout2->getCoordsB().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout2->getCoordsB().y()+4) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4),
            (int)(layoutTurnout2->getCoordsB().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsB().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsB().y()-4-(2*testIcon->getIconHeight())) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsB().x()+4),
            (int)(layoutTurnout2->getCoordsB().y()-4-(2*testIcon->getIconHeight())) );
    }
}
/*private*/ void LayoutEditorTools::placeD1TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && layoutTurnout2BUp) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsC().x()),
            (int)(layoutTurnout2->getCoordsC().y()+4) );
    }
    else if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsC().x()),
            (int)(layoutTurnout2->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsC().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()+4) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsC().x()-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4),
            (int)(layoutTurnout2->getCoordsC().y()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4),
            (int)(layoutTurnout2->getCoordsC().y()-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()-testIcon->getIconHeight()) );
    }
}
/*private*/ void LayoutEditorTools::placeD2TToT(QString headName) {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && layoutTurnout2BUp) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()+4) );
    }
    else if( layoutTurnout2Horizontal && layoutTurnout2ThroatLeft && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(0,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4+testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && layoutTurnout2BUp ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout2->getCoordsC().y()+4) );
    }
    else if( layoutTurnout2Horizontal && (!layoutTurnout2ThroatLeft) && (!layoutTurnout2BUp) ) {
        setSignalHeadOnPanel(2,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-(2*testIcon->getIconWidth())),
            (int)(layoutTurnout2->getCoordsC().y()-4-testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4),
            (int)(layoutTurnout2->getCoordsC().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && layoutTurnout2ThroatUp && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(3,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()+4+testIcon->getIconHeight()) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && layoutTurnout2BLeft ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsC().x()+4),
            (int)(layoutTurnout2->getCoordsC().y()-4-(2*testIcon->getIconHeight())) );
    }
    else if( layoutTurnout2Vertical && (!layoutTurnout2ThroatUp) && (!layoutTurnout2BLeft) ) {
        setSignalHeadOnPanel(1,headName,
            (int)(layoutTurnout2->getCoordsC().x()-4-testIcon->getIconWidth()),
            (int)(layoutTurnout2->getCoordsC().y()-4-(2*testIcon->getIconHeight())) );
    }
}
//@SuppressWarnings("NULL")
/*private*/ void LayoutEditorTools::setLogicTToT(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2,
                bool setup1, bool setup2, bool continuing,
                    LayoutTurnout* farTurnout, LayoutTurnout* nearTurnout) {
    // initialize common components and ensure all is defined
    LayoutBlock* connectorBlock = connectorTrack->getLayoutBlock();
    LayoutBlock* nearTurnoutBlock = nearTurnout->getLayoutBlock();
    LayoutBlock* farTurnoutBlock = farTurnout->getLayoutBlock();
    Sensor* connectorOccupancy = NULL;
    if ( (connectorBlock==nullptr) || (nearTurnoutBlock==nullptr) || (farTurnoutBlock==nullptr) ) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    connectorOccupancy = connectorBlock->getOccupancySensor();
    if (connectorOccupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                    new Object[]{connectorBlock.getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(connectorBlock->getUserName()));
        return;
    }
    // setup signal head for continuing track of far turnout (or both tracks of far turnout)
    if ( (track1==nullptr) && setup1 ) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    Sensor* occupancy = NULL;
    SignalHead* nextHead = NULL;
    if ( (track1!=nullptr) && setup1) {
        LayoutBlock* block = track1->getLayoutBlock();
        if (block==nullptr) {
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
            return;
        }
        occupancy = block->getOccupancySensor();
        if (occupancy==nullptr) {
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
            return;
        }
        nextHead = getNextSignalFromObject(track1,farTurnout,
                                    head->getSystemName(), setSignalsAtTToTFrame);
        if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
//            JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                    new Object[]{block->getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(setSignalsFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block->getUserName()));
            return;
        }
        if (secondHead!=nullptr) {
            // this head signals only the continuing track of the far turnout
            if (!initializeBlockBossLogic(head->getSystemName())) return;
            logic->setMode(BlockBossLogic::TRAILINGMAIN);
            logic->setTurnout(farTurnout->getTurnout()->getSystemName());
            logic->setSensor1(occupancy->getSystemName());
            if (occupancy!=connectorOccupancy)
                logic->setSensor2(connectorOccupancy->getSystemName());
            if (nextHead!=nullptr) {
                logic->setWatchedSignal1(nextHead->getSystemName(),false);
            }
            if (auxSignal!=nullptr) {
                logic->setWatchedSignal1Alt(auxSignal->getSystemName());
            }
            QString nearSensorName = setupNearLogix(nearTurnout,continuing,head);
            addNearSensorToLogic(nearSensorName);
            finalizeBlockBossLogic();
        }
    }
    if ( (secondHead!=nullptr) && !setup2 ) return;
    SignalHead* savedAuxSignal = auxSignal;
    if (track2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    LayoutBlock* block2 = track2->getLayoutBlock();
    if (block2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    Sensor* occupancy2 = block2->getOccupancySensor();
    if (occupancy2==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block2.getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block2->getUserName()));
        return;
    }
    SignalHead* nextHead2 = NULL;
    if (secondHead!=nullptr) {
        nextHead2 = getNextSignalFromObject(track2,
                farTurnout, secondHead->getSystemName(), setSignalsAtTToTFrame);
        if ( (nextHead2==nullptr) && (!reachedEndBumper()) ) {
//            JOptionPane::showMessageDialog(setSignalsAtTToTFrame,
//                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined."),
//                    new Object[]{block2.getUserName()}),
//                        NULL,JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because the next signal (in or\nat the end of block \"%1\") apparently is not yet defined.").arg(block2->getUserName()));
            return;
        }
    }
    if ( (secondHead==nullptr) && (track1!=nullptr) && setup1 ) {
        if (!initializeBlockBossLogic(head->getSystemName())) return;
        logic->setMode(BlockBossLogic::FACING);
        logic->setTurnout(farTurnout->getTurnout()->getSystemName());
        logic->setWatchedSensor1(occupancy->getSystemName());
        logic->setWatchedSensor2(occupancy2->getSystemName());
        logic->setSensor2(connectorOccupancy->getSystemName());
        if (nextHead!=nullptr) {
            logic->setWatchedSignal1(nextHead->getSystemName(),false);
        }
        if (savedAuxSignal!=nullptr) {
            logic->setWatchedSignal1Alt(savedAuxSignal->getSystemName());
        }
        if (nextHead2!=nullptr) {
            logic->setWatchedSignal2(nextHead2->getSystemName());
        }
        if (auxSignal!=nullptr) {
            logic->setWatchedSignal2Alt(auxSignal->getSystemName());
        }
        QString nearSensorName = setupNearLogix(nearTurnout,continuing,head);
        addNearSensorToLogic(nearSensorName);
        logic->setLimitSpeed2(true);
        finalizeBlockBossLogic();
    }
    else if ( (secondHead!=nullptr) && setup2) {
        if (!initializeBlockBossLogic(secondHead->getSystemName())) return;
        logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
        logic->setTurnout(farTurnout->getTurnout()->getSystemName());
        logic->setSensor1(occupancy2->getSystemName());
        if (occupancy2!=connectorOccupancy)
            logic->setSensor2(connectorOccupancy->getSystemName());
        if (nextHead2!=nullptr) {
            logic->setWatchedSignal1(nextHead2->getSystemName(),false);
        }
        if (auxSignal!=nullptr) {
            logic->setWatchedSignal1Alt(auxSignal->getSystemName());
        }
        QString nearSensorName = setupNearLogix(nearTurnout,continuing,head);
        addNearSensorToLogic(nearSensorName);
        logic->setLimitSpeed2(true);
        finalizeBlockBossLogic();
    }
}

/*
 * Sets up a Logix to set a sensor active if a turnout is set against
 *      a track->  This routine creates an internal sensor for the purpose.
 * Note: The sensor and logix are named IS or IX followed by TTT_X_HHH where
 *		TTT is the system name of the turnout, X is either C or T depending
 *      on "continuing", and HHH is the system name of the signal head.
 * Note: If there is any problem, a string of "" is returned, and a warning
 *		message is issued.
 */
/*private*/ QString LayoutEditorTools::setupNearLogix(LayoutTurnout* nearTurnout, bool continuing, SignalHead* head) {
    QString turnoutName = nearTurnout->getTurnout()->getSystemName();
    QString namer = turnoutName+"_T_"+head->getSystemName();
    if (!continuing) namer = turnoutName+"_C_"+head->getSystemName();
    QString sensorName = "IS"+namer;
    QString logixName = "IX"+namer;
    Sensor* sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(sensorName);
    if (sensor==nullptr) {
        log->error("Trouble creating sensor "+sensorName+" while setting up Logix->");
        return "";
    }
    if (((LogixManager*)InstanceManager::getDefault("LogixManager"))->getBySystemName(logixName)==nullptr)
    {
        // Logix does not exist, create it
        Logix* x = ((LogixManager*)InstanceManager::getDefault("LogixManager"))->createNewLogix(logixName,"");
        if (x==nullptr) {
            log->error("Trouble creating logix "+logixName+" while setting up signal logic->");
            return "";
        }
        QString cName = x->getSystemName() + "C1";
        Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->
                                            createNewConditional(cName,"");
        if (c==nullptr) {
            log->error("Trouble creating conditional "+cName+" while setting up Logix->");
            return "";
        }
        int type = Conditional::TYPE_TURNOUT_THROWN;
        if (!continuing) type = Conditional::TYPE_TURNOUT_CLOSED;
        QList <ConditionalVariable*>* variableList = c->getCopyOfStateVariables();
        variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND, type, turnoutName, true));
        c->setStateVariables(variableList);
       QList <ConditionalAction*>* actionList = c->getCopyOfActions();
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                                             Conditional::ACTION_SET_SENSOR, sensorName,
                                             Sensor::ACTIVE, ""));
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE,
                                             Conditional::ACTION_SET_SENSOR, sensorName,
                                             Sensor::INACTIVE, ""));
        c->setAction(actionList);										// string data
        x->addConditional(cName,-1);
        x->activateLogix();
    }
    return sensorName;
}
/*
 * Adds the sensor specified to the open BlockBossLogic, provided it is not already there and
 *		provided there is an open slot. If 'name' is NULL or empty, returns without doing anything.
 */
/*private*/ void LayoutEditorTools::addNearSensorToLogic(QString name) {
    if ( (name==nullptr) || name==("") ) return;
    // return if a sensor by this name is already present
    if ( (logic->getSensor1()!=nullptr) && (logic->getSensor1())==(name) ) return;
    if ( (logic->getSensor2()!=nullptr) && (logic->getSensor2())==(name) ) return;
    if ( (logic->getSensor3()!=nullptr) && (logic->getSensor3())==(name) ) return;
    if ( (logic->getSensor4()!=nullptr) && (logic->getSensor4())==(name) ) return;
    if ( (logic->getSensor5()!=nullptr) && (logic->getSensor5())==(name) ) return;
    // add in the first available slot
    if (logic->getSensor1()==nullptr) logic->setSensor1(name);
    else if (logic->getSensor2()==nullptr) logic->setSensor2(name);
    else if (logic->getSensor3()==nullptr) logic->setSensor3(name);
    else if (logic->getSensor4()==nullptr) logic->setSensor4(name);
    else if (logic->getSensor5()==nullptr) logic->setSensor5(name);
    else log->error("Error - could not add sensor to SSL for signal head "+logic->getDrivenSignal());
}

/**
 * Tool to set signals at a three-way turnout, including placing the
 *		signal icons and setup of signal logic for each signal head
 * <P>
 * This tool can only be accessed from the Tools menu. There is no access
 *		from a turnout pop-up menu.
 * <P>
 * This tool requires a situation where two turnouts are connected to model a 3-way
 *		turnout, with the throat of the second turnout connected to the continuing
 *		leg of the first turnout by a very short track segment. The actual length of
 *		the track segment is not tested. If this situation is not found,
 *		and error message is sent to the user.
 * <P>
 * This tool assumes two turnouts connected with the throat of the second turnout
 *		connected to the continuing leg of the first turnout, as used to
 *		represent a 3-way turnout. The turnouts may be either
 *		left-handed, or right-handed, or any pair of these. This tool also
 *		assumes that there are no signals between the two turnouts. Signal
 *		heads are allowed/required at the continuing leg of the second turnout, at
 *		each of the diverging legs, and at the throat. At the throat, either one or
 *		three heads are provided for. So four or six heads will be placed.
 * <P>
 * This tool assumes that each of the four tracks, the continuing, the two diverging,
 *		and the throat is contained in a different block-> The two turnouts used to
 *		model the 3-way turnout must be in the same block-> Things work best if the
 *		two turnouts are in the same block as the track connecting at the throat, or
 *		if the two turnouts are in their own separate block, either works fine.
 * <P>
 * This tool only places signal icons if the turnout is either mostly vertical
 *		or mostly horizontal. Some user adjustment may be needed.
 */



/*public*/ void LayoutEditorTools::setSignalsAt3WayTurnoutFromMenu(
        /*@Nonnull*/ QString aName, /*@Nonnull*/ QString bName,
        /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame) {
    Turnout* ta = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(aName);
    Turnout* tb = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(bName);
    turnoutAComboBox->setSelectedItem(ta);
    turnoutBComboBox->setSelectedItem(tb);
    a1_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    a2_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    a3_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    b_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    c_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    d_3WaySignalHeadComboBox->setSelectedItem(nullptr);
    setSignalsAt3WayTurnoutFromMenuFlag = true;
    setSignalsAt3WayTurnout(theEditor, theFrame);
    setSignalsAt3WayTurnoutFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAt3WayTurnout(/*@Nonnull */MultiIconEditor* theEditor,
        /*@Nonnull*/ JFrame* theFrame) {
    signalIconEditor = theEditor;
    signalFrame = theFrame;

    //Initialize if needed
    if (setSignalsAt3WayTurnoutFrame == nullptr) {
        setSignalsAt3WayTurnoutOpenFlag = false;
        setSignalsAt3WayTurnoutFrame = new JmriJFrameX(tr("Set Signal Heads at 3-Way Turnout"), false, true);
        oneFrameToRuleThemAll(setSignalsAt3WayTurnoutFrame);
        setSignalsAt3WayTurnoutFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
        setSignalsAt3WayTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAt3WayTurnout", true);
        setSignalsAt3WayTurnoutFrame->setLocation(70, 30);
        QFont font;
        font.setPointSize(8);
        setSignalsAt3WayTurnoutFrame->setFont(font);
//        QWidget* theContentPane = setSignalsAt3WayTurnoutFrame->getContentPane();
//        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
        QScrollArea* scrollarea = new QScrollArea();
        QWidget* theContentPane = new QWidget();
        theContentPane->setLayout(new QVBoxLayout());
        scrollarea->setWidget(theContentPane);
        scrollarea->setWidgetResizable(true);
        setSignalsAt3WayTurnoutFrame->setCentralWidget(scrollarea);

        JPanel* panel1A = new JPanel(new FlowLayout());
        turnoutANameLabel = new JLabel(tr("Turnout A Name (closest to throat)"));
        panel1A->layout()->addWidget(turnoutANameLabel);
        panel1A->layout()->addWidget(turnoutAComboBox);
        turnoutAComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
        theContentPane->layout()->addWidget(panel1A);

        JPanel* panel1B = new JPanel(new FlowLayout());
        turnoutBNameLabel = new JLabel(tr("Turnout B Name (farthest from throat)"));
        panel1B->layout()->addWidget(turnoutBNameLabel);
        panel1B->layout()->addWidget(turnoutBComboBox);
        turnoutBComboBox->setToolTip(tr("Enter name (system or user) of turnout where signals are needed."));
        theContentPane->layout()->addWidget(panel1B);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        //Provide for retrieval of names of previously saved signal heads

        JPanel* panel2 = new JPanel(new FlowLayout());
        JLabel* shTitle = new JLabel(tr("SignalHeads"));
        panel2->layout()->addWidget(shTitle);
        panel2->layout()->addWidget(new JLabel("		"));
        panel2->layout()->addWidget(getSaved3WaySignalHeads = new QPushButton(tr("Get Saved")));
        //getSaved3WaySignalHeads.addActionListener((ActionEvent e) -> {
        connect(getSaved3WaySignalHeads, &QPushButton::clicked, [=]{
            getSaved3WaySignals(/*e*/);
        });
        getSaved3WaySignalHeads->setToolTip(tr("GetSavedHint"));
        theContentPane->layout()->addWidget(panel2);

        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        JPanel* panel2a = new JPanel(new FlowLayout());
        panel2a->layout()->addWidget(new JLabel("   "));
        panel2a->layout()->addWidget(setPlaceAllHeads);
        setPlaceAllHeads->setToolTip(tr("Check to place all signal head icons"));
        //setPlaceAllHeads.addActionListener((ActionEvent e) -> {
        connect(setPlaceAllHeads, &QCheckBox::clicked, [=]{
            bool isSelected = setPlaceAllHeads->isChecked();
            //(de)select all checkboxes
            setA13WayHead->setChecked(isSelected);
            setA23WayHead->setChecked(isSelected);
            setA33WayHead->setChecked(isSelected);
            setB3WayHead->setChecked(isSelected);
            setC3WayHead->setChecked(isSelected);
            setD3WayHead->setChecked(isSelected);
        });
        panel2a->layout()->addWidget(new JLabel("  "));
        panel2a->layout()->addWidget(setupAllLogic);
        setupAllLogic->setToolTip(tr("Check to set up Simple Signal Logic for all Signal Heads"));
        //setupAllLogic.addActionListener((ActionEvent e) -> {
        connect(setupAllLogic, &QCheckBox::clicked, [=]{
            bool isSelected = setupAllLogic->isChecked();
            //(de)select all checkboxes
            setupA13WayLogic->setChecked(isSelected);
            setupA23WayLogic->setChecked(isSelected);
            setupA33WayLogic->setChecked(isSelected);
            setupB3WayLogic->setChecked(isSelected);
            setupC3WayLogic->setChecked(isSelected);
            setupD3WayLogic->setChecked(isSelected);
        });
        theContentPane->layout()->addWidget(panel2a);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        //Signal heads located at turnout A
        JPanel* panel20 = new JPanel(new FlowLayout());
        panel20->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " A "));
        theContentPane->layout()->addWidget(panel20);

        JPanel* panel21 = new JPanel(new FlowLayout());
        panel21->layout()->addWidget(new JLabel(
                throatString + " - "
                + continuingString));
        panel21->layout()->addWidget(a1_3WaySignalHeadComboBox);
        a1_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel21);

        JPanel* panel22 = new JPanel(new FlowLayout());
        panel22->layout()->addWidget(new JLabel("   "));
        panel22->layout()->addWidget(setA13WayHead);
        setA13WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel22->layout()->addWidget(new JLabel("  "));
        panel22->layout()->addWidget(setupA13WayLogic);
        setupA13WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel22);

        JPanel* panel23 = new JPanel(new FlowLayout());
        panel23->layout()->addWidget(new JLabel(
                throatString + " - "
                + divergingAString));
        panel23->layout()->addWidget(a2_3WaySignalHeadComboBox);
        a2_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel23);

        JPanel* panel24 = new JPanel(new FlowLayout());
        panel24->layout()->addWidget(new JLabel("   "));
        panel24->layout()->addWidget(setA23WayHead);
        setA23WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel24->layout()->addWidget(new JLabel("  "));
        panel24->layout()->addWidget(setupA23WayLogic);
        setupA23WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel24);

        JPanel* panel25 = new JPanel(new FlowLayout());
        panel25->layout()->addWidget(new JLabel(
                throatString + " - "
                + divergingBString));
        panel25->layout()->addWidget(a3_3WaySignalHeadComboBox);
        a3_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel25);

        JPanel* panel26 = new JPanel(new FlowLayout());
        panel26->layout()->addWidget(new JLabel("   "));
        panel26->layout()->addWidget(setA33WayHead);
        setA33WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel26->layout()->addWidget(new JLabel("  "));
        panel26->layout()->addWidget(setupA33WayLogic);
        setupA33WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel26);

        JPanel* panel31 = new JPanel(new FlowLayout());
        panel31->layout()->addWidget(new JLabel(
                divergingBString));
        panel31->layout()->addWidget(b_3WaySignalHeadComboBox);
        b_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel31);

        JPanel* panel32 = new JPanel(new FlowLayout());
        panel32->layout()->addWidget(new JLabel("   "));
        panel32->layout()->addWidget(setB3WayHead);
        setB3WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel32->layout()->addWidget(new JLabel("  "));
        panel32->layout()->addWidget(setupB3WayLogic);
        setupB3WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel32);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        //Signal heads located at turnout B

        JPanel* panel40 = new JPanel(new FlowLayout());
        panel40->layout()->addWidget(new JLabel(tr("Signal located at")
                + " " + tr("Turnout") + " B "));
        theContentPane->layout()->addWidget(panel40);

        JPanel* panel41 = new JPanel(new FlowLayout());
        panel41->layout()->addWidget(new JLabel(
                continuingString));
        panel41->layout()->addWidget(c_3WaySignalHeadComboBox);
        c_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel41);

        JPanel* panel42 = new JPanel(new FlowLayout());
        panel42->layout()->addWidget(new JLabel("   "));
        panel42->layout()->addWidget(setC3WayHead);
        setC3WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel42->layout()->addWidget(new JLabel("  "));
        panel42->layout()->addWidget(setupC3WayLogic);
        setupC3WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel42);

        JPanel* panel43 = new JPanel(new FlowLayout());
        panel43->layout()->addWidget(new JLabel(
                divergingBString));
        panel43->layout()->addWidget(d_3WaySignalHeadComboBox);
        d_3WaySignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));
        theContentPane->layout()->addWidget(panel43);

        JPanel* panel44 = new JPanel(new FlowLayout());
        panel44->layout()->addWidget(new JLabel("   "));
        panel44->layout()->addWidget(setD3WayHead);
        setD3WayHead->setToolTip(tr("Check to place icon for above signal head on panel near turnout."));
        panel44->layout()->addWidget(new JLabel("  "));
        panel44->layout()->addWidget(setupD3WayLogic);
        setupD3WayLogic->setToolTip(tr("Check to set up Simple Signal Logic for the above signal head."));
        theContentPane->layout()->addWidget(panel44);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
        //buttons

        JPanel* panel6 = new JPanel(new FlowLayout());
        panel6->layout()->addWidget(change3WaySignalIcon = new QPushButton(tr("Change Signal Head Icon")));
        //change3WaySignalIcon.addActionListener((ActionEvent e) -> {
        connect(change3WaySignalIcon, &QPushButton::clicked, [=]{
            signalFrame->setVisible(true);
        });
        change3WaySignalIcon->setToolTip(tr("ChangeSignalIconHint"));
        panel6->layout()->addWidget(new JLabel("	 "));
        panel6->layout()->addWidget(set3WaySignalsDone = new QPushButton(tr("Done")));
        //set3WaySignalsDone.addActionListener((ActionEvent e) -> {
        connect(set3WaySignalsDone, &QPushButton::clicked, [=]{
            set3WaySignalsDonePressed(/*e*/);
        });
        set3WaySignalsDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

        //make this button the default button (return or enter activates)
        //Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(set3WaySignalsDone);
//            rootPane.setDefaultButton(set3WaySignalsDone);
        set3WaySignalsDone->setDefault(true);
//        });

        panel6->layout()->addWidget(set3WaySignalsCancel = new QPushButton(tr("Cancel")));
        //set3WaySignalsCancel.addActionListener((ActionEvent e) -> {
        connect(set3WaySignalsCancel, &QPushButton::clicked, [=]{
            set3WaySignalsCancelPressed(/*e*/);
        });
        set3WaySignalsCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPane->layout()->addWidget(panel6);
#if 0
        setSignalsAt3WayTurnoutFrame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                set3WaySignalsCancelPressed(null);
            }
        });
#endif
    }
    setPlaceAllHeads->setChecked(false);
    setupAllLogic->setChecked(false);

    turnoutAComboBox->setVisible(!setSignalsAt3WayTurnoutFromMenuFlag);
    turnoutBComboBox->setVisible(!setSignalsAt3WayTurnoutFromMenuFlag);
    if (setSignalsAt3WayTurnoutFromMenuFlag) {
        turnoutANameLabel->setText(tr("Turnout") + " A"
                + turnoutAComboBox->getSelectedItemDisplayName());
        turnoutBNameLabel->setText(
                tr("Turnout") + " B"
                + turnoutBComboBox->getSelectedItemDisplayName());
        getSaved3WaySignals(/*null*/);
    } else {
        turnoutANameLabel->setText(
                tr("Turnout A Name (closest to throat)"));
        turnoutBNameLabel->setText(
                tr("Turnout B Name (farthest from throat)"));
    }

    if (!setSignalsAt3WayTurnoutOpenFlag) {
        setSignalsAt3WayTurnoutFrame->resize(QSize());
        setSignalsAt3WayTurnoutFrame->pack();
        setSignalsAt3WayTurnoutOpenFlag = true;
    }
    setSignalsAt3WayTurnoutFrame->setVisible(true);
}   //setSignalsAt3WayTurnout

/*private*/ void LayoutEditorTools::getSaved3WaySignals (JActionEvent* /*a*/) {
 if (!get3WayTurnoutInformation()) {
     return;
 }
 a1_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutA->getSignalA1());
 a2_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutA->getSignalA2());
 a3_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutA->getSignalA3());
 b_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutA->getSignalC1());
 c_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutB->getSignalB1());
 d_3WaySignalHeadComboBox->setSelectedItem(layoutTurnoutB->getSignalC1());
}

/*private*/ void LayoutEditorTools::set3WaySignalsCancelPressed (JActionEvent* /*a*/) {
    setSignalsAt3WayOpen = false;
    setSignalsAt3WayTurnoutFrame->setVisible(false);
}

/*private*/ bool LayoutEditorTools::get3WayTurnoutInformation() {
    int type = 0;
    QObject* connect = NULL;
    turnoutA = NULL;
    turnoutB = NULL;
    layoutTurnoutA = NULL;
    layoutTurnoutB = NULL;

    QString str = turnoutAComboBox->getSelectedItemDisplayName();
    if ( (str.isNull()) || (str.isEmpty()) ) {
        // turnout A not entered, test turnout B
        str = turnoutBComboBox->getSelectedItemDisplayName();
        if ( (str==nullptr) || (str==("")) ) {
            // no entries in turnout fields
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,tr("SignalsError1"),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
            return false;
        }
        turnoutB = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(str);
        if (turnoutB==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
                   str), tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
            return false ;
        }
        if ( (turnoutB->getUserName()==nullptr) || (turnoutB->getUserName()==("")) ||
                                turnoutB->getUserName()!=(str) ) {
//            str = str.toUpper();
            turnoutBComboBox->setSelectedItem(turnoutB);
        }
        layoutTurnoutB = getLayoutTurnoutFromTurnout(turnoutB,false,str,setSignalsAt3WayTurnoutFrame);
        if (layoutTurnoutB==nullptr)
            return false;
        // have turnout B and layout turnout B - look for turnout A
        connectorTrack = (TrackSegment*)layoutTurnoutB->getConnectA();
        if (connectorTrack == nullptr) {
            // Inform user of error, and terminate
//            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                    tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalsAt3WayTurnoutFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH or LH) connected,\nas specified, by a short track segment. Cannot find these."));
            return false;
        }
        type = connectorTrack->getType1();
        connect = connectorTrack->getConnect1();
        if (connect == layoutTurnoutB) {
            type = connectorTrack->getType2();
            connect = connectorTrack->getConnect2();
        }
        if ( (type != LayoutEditor::TURNOUT_B) || (connect==nullptr) ) {
            // Not two turnouts connected as required by a single Track Segment
            // Inform user of error and terminate
//            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                    tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalsAt3WayTurnoutFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH or LH) connected,\nas specified, by a short track segment. Cannot find these."));
            return false;
        }
        layoutTurnoutA = (LayoutTurnout*)connect;
        turnoutA = layoutTurnoutA->getTurnout();
        if (turnoutA==nullptr) {
//            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                    tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalsAt3WayTurnoutFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH or LH) connected,\nas specified, by a short track segment. Cannot find these."));
            return false;
        }
        turnoutAComboBox->setSelectedItem(turnoutA);
    }
    else {
        // something was entered in the turnout A field
        turnoutA = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(str);
        if (turnoutA==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
                    str), tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
            return false ;
        }
        QString uname = turnoutA->getUserName();
        if ((uname.isNull()) || uname.isEmpty()
                || uname !=(str)) {
            turnoutAComboBox->setSelectedItem(turnoutA);
        }
        // have turnout A - get corresponding layoutTurnout
        layoutTurnoutA = getLayoutTurnoutFromTurnout(turnoutA,false,str,setSignalsAt3WayTurnoutFrame);
        if (layoutTurnoutA == nullptr)
            return false;
        turnoutAComboBox->setSelectedItem(layoutTurnoutA->getTurnout());

        // have turnout A and layout turnout A - was something entered for turnout B
        str = turnoutBComboBox->getSelectedItemDisplayName();
        if ( (str==nullptr) || (str==("")) ) {
            // no entry for turnout B
            connectorTrack = (TrackSegment*)layoutTurnoutA->getConnectB();
            if (connectorTrack == nullptr) {
                // Inform user of error, and terminate
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                        tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return false;
            }
            type = connectorTrack->getType1();
            connect = connectorTrack->getConnect1();
            if (connect == layoutTurnoutA) {
                type = connectorTrack->getType2();
                connect = connectorTrack->getConnect2();
            }
            if ( (type != LayoutEditor::TURNOUT_A) || (connect==nullptr) ) {
                // Not two turnouts connected with the throat of B connected to the continuing of A
                //    by a single Track Segment.  Inform user of error and terminat.e
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                        tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return false;
            }
            layoutTurnoutB = (LayoutTurnout*)connect;
            turnoutB = layoutTurnoutB->getTurnout();
            if (turnoutB==nullptr) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                        tr("Error - This tool requires two turnouts (RH or LH) connected, \nas specified, by a short track segment. Cannot find these."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return false;
            }
            turnoutBComboBox->setSelectedItem(turnoutB);

        }
        else {
            // turnout B entered also
            turnoutB = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(str);
            if (turnoutB==nullptr) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
                            str), tr("Error"),
                                JOptionPane::ERROR_MESSAGE);
                return false ;
            }
            if ( (turnoutB->getUserName()==nullptr) || (turnoutB->getUserName()==("")) ||
                                turnoutB->getUserName()!=(str) ) {
//                str = str.toUpper();
                turnoutBComboBox->setSelectedItem(turnoutB);
            }
            layoutTurnoutB = getLayoutTurnoutFromTurnout(turnoutB,false,str,setSignalsAt3WayTurnoutFrame);
            if (layoutTurnoutB==nullptr)
                return false;
            turnoutBComboBox->setSelectedItem(layoutTurnoutB->getTurnout());
            // check that layout turnout A and layout turnout B are connected as required
            if (layoutTurnoutA->getConnectB()!=layoutTurnoutB->getConnectA()) {
                // Not two turnouts connected as required by a single Track Segment
                // Inform user of error and terminate
             QMessageBox::critical(setSignalsAt3WayTurnoutFrame, tr("Error"), tr("Error - This tool requires two turnouts (RH or LH) connected,\nas specified, by a short track segment. Cannot find these."));
                return false;
            }
            connectorTrack = (TrackSegment*)layoutTurnoutA->getConnectB();
        }
    }
    // have both turnouts, correctly connected - complete initialization
    layoutTurnoutAHorizontal = false;
    layoutTurnoutAVertical = false;
    layoutTurnoutBThroatLeft = false;
    layoutTurnoutBVertical = false;
    layoutTurnoutAThroatLeft = false;
    layoutTurnoutAThroatUp = false;
    layoutTurnoutBThroatLeft = false;
    layoutTurnoutBThroatUp = false;
    layoutTurnoutABUp = false;
    layoutTurnoutABLeft = false;
    layoutTurnoutBBUp = false;
    layoutTurnoutBBLeft = false;
    double delX = layoutTurnoutA->getCoordsA().x() - layoutTurnoutA->getCoordsB().x();
    double delY = layoutTurnoutA->getCoordsA().y() - layoutTurnoutA->getCoordsB().y();
    if (qAbs(delX) > 2.0*qAbs(delY)) {
        layoutTurnoutAHorizontal = true;
        if (delX < 0.0) layoutTurnoutAThroatLeft = true;
        if (layoutTurnoutA->getCoordsB().y() < layoutTurnoutA->getCoordsC().y())
            layoutTurnoutABUp = true;
    }
    else if (qAbs(delY) > 2.0*qAbs(delX)) {
        layoutTurnoutAVertical = true;
        if (delY <0.0) layoutTurnoutAThroatUp = true;
        if (layoutTurnoutA->getCoordsB().x() < layoutTurnoutA->getCoordsC().x())
            layoutTurnoutABLeft = true;
    }
    delX = layoutTurnoutB->getCoordsA().x() - layoutTurnoutB->getCoordsB().x();
    delY = layoutTurnoutB->getCoordsA().y() - layoutTurnoutB->getCoordsB().y();
    if (qAbs(delX) > 2.0*qAbs(delY)) {
        layoutTurnoutBHorizontal = true;
        if (delX < 0.0) layoutTurnoutBThroatLeft = true;
        if (layoutTurnoutB->getCoordsB().y() < layoutTurnoutB->getCoordsC().y())
            layoutTurnoutBBUp = true;
    }
    else if (qAbs(delY) > 2.0*qAbs(delX)) {
        layoutTurnoutBVertical = true;
        if (delY <0.0) layoutTurnoutBThroatUp = true;
        if (layoutTurnoutB->getCoordsB().x() < layoutTurnoutB->getCoordsC().x())
            layoutTurnoutBBLeft = true;
    }
    return true;
}

/*private*/ void LayoutEditorTools::set3WaySignalsDonePressed (JActionEvent* /*a*/) {
    // process turnout names
    if ( !get3WayTurnoutInformation() )
     return;

    // process signal head names
    if ( !get3WaySignalHeadInformation() )
     return;

    // place signals as requested at turnout A
    QString signalHeadName = a1_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (setA13WayHead->isChecked()) {
        if (isHeadOnPanel(a13WayHead) &&
            (a13WayHead!=getHeadFromName(layoutTurnoutA->getSignalA1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutAHorizontal) && (!layoutTurnoutAVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (a13WayHead!=getHeadFromName(layoutTurnoutA->getSignalA1Name())) {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA1Name());
                removeAssignment(a13WayHead);
                layoutTurnoutA->setSignalA1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnoutA->getSignalA1Name());
            place3WayThroatContinuing();
            removeAssignment(a13WayHead);
            layoutTurnoutA->setSignalA1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(a13WayHead,layoutTurnoutA);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a13WayHead) &&
                                isHeadAssignedAnywhere(a13WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA1Name());
                removeAssignment(a13WayHead);
                layoutTurnoutA->setSignalA1Name(signalHeadName);
            }
        }
        else if (assigned!=A1) {
// need to figure out what to do in this case.
        }
    }

    signalHeadName = a2_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if ( (setA23WayHead->isChecked()) && (a23WayHead!=nullptr) ) {
        if (isHeadOnPanel(a23WayHead) &&
            (a23WayHead!=getHeadFromName(layoutTurnoutA->getSignalA2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutAHorizontal) && (!layoutTurnoutAVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (a23WayHead!=getHeadFromName(layoutTurnoutA->getSignalA2Name())) {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA2Name());
                removeAssignment(a23WayHead);
                layoutTurnoutA->setSignalA2Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnoutA->getSignalA2Name());
            place3WayThroatDivergingA();
            removeAssignment(a23WayHead);
            layoutTurnoutA->setSignalA2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (a23WayHead!=nullptr) {
        int assigned = isHeadAssignedHere(a23WayHead,layoutTurnoutA);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a23WayHead) &&
                                isHeadAssignedAnywhere(a23WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA2Name());
                removeAssignment(a23WayHead);
                layoutTurnoutA->setSignalA2Name(signalHeadName);
            }
        }
        else if (assigned!=A2) {
// need to figure out what to do in this case.
        }
    }
    else if (a23WayHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnoutA->getSignalA2Name());
        layoutTurnoutA->setSignalA2Name("");
    }

    signalHeadName = a3_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if ( (setA33WayHead->isChecked()) && (a33WayHead!=nullptr) ) {
        if (isHeadOnPanel(a33WayHead) &&
            (a33WayHead!=getHeadFromName(layoutTurnoutA->getSignalA3Name()))) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutAHorizontal) && (!layoutTurnoutAVertical) ) {
//            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
            QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

            if (a33WayHead!=getHeadFromName(layoutTurnoutA->getSignalA3Name())) {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA3Name());
                removeAssignment(a33WayHead);
                layoutTurnoutA->setSignalA3Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnoutA->getSignalA3Name());
            place3WayThroatDivergingB();
            removeAssignment(a33WayHead);
            layoutTurnoutA->setSignalA3Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (a33WayHead!=nullptr) {
        int assigned = isHeadAssignedHere(a33WayHead,layoutTurnoutA);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a33WayHead) &&
                                isHeadAssignedAnywhere(a33WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalA3Name());
                removeAssignment(a33WayHead);
                layoutTurnoutA->setSignalA3Name(signalHeadName);
            }
        }
        else if (assigned!=A3) {
// need to figure out what to do in this case.
        }
    }
    else if (a33WayHead==nullptr) {
        removeSignalHeadFromPanel(layoutTurnoutA->getSignalA3Name());
        layoutTurnoutA->setSignalA3Name("");
    }

    signalHeadName = b_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (setB3WayHead->isChecked()) {
        if (isHeadOnPanel(b3WayHead) &&
            (b3WayHead!=getHeadFromName(layoutTurnoutA->getSignalC1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutAHorizontal) && (!layoutTurnoutAVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (b3WayHead!=getHeadFromName(layoutTurnoutA->getSignalB1Name())) {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalC1Name());
                removeAssignment(b3WayHead);
                layoutTurnoutA->setSignalC1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnoutA->getSignalC1Name());
            place3WayDivergingA();
            removeAssignment(b3WayHead);
            layoutTurnoutA->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(b3WayHead,layoutTurnoutA);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b3WayHead) &&
                                isHeadAssignedAnywhere(b3WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutA->getSignalC1Name());
                removeAssignment(b3WayHead);
                layoutTurnoutA->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=A1) {
// need to figure out what to do in this case.
        }
    }
    // place signals as requested at Turnout B
    signalHeadName = c_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (setC3WayHead->isChecked())
    {
     if (isHeadOnPanel(c3WayHead) &&
         (c3WayHead!=getHeadFromName(layoutTurnoutB->getSignalB1Name()))) {
         JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
             tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                 signalHeadName),
                     tr("Error"),JOptionPane::ERROR_MESSAGE);
         return;
     }
     else if ( (!layoutTurnoutBHorizontal) && (!layoutTurnoutBVertical) ) {
         JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
             tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);
         QMessageBox::information(0, tr("Information"), tr("Sorry, cannot place signal heads at turnouts\n                                                   that are not oriented vertical or horizontal."));

         if (c3WayHead!=getHeadFromName(layoutTurnoutB->getSignalB1Name())) {
             removeSignalHeadFromPanel(layoutTurnoutB->getSignalB1Name());
             removeAssignment(c3WayHead);
             layoutTurnoutB->setSignalB1Name(signalHeadName);
         }
     }
     else {
         removeSignalHeadFromPanel(layoutTurnoutB->getSignalB1Name());
         place3WayContinuing();
         removeAssignment(c3WayHead);
         layoutTurnoutB->setSignalB1Name(signalHeadName);
         needRedraw = true;
     }
    }
    else {
        int assigned = isHeadAssignedHere(c3WayHead,layoutTurnoutB);
        if (assigned == NONE) {
            if (isHeadOnPanel(c3WayHead)  &&
                                isHeadAssignedAnywhere(c3WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutB->getSignalB1Name());
                removeAssignment(c3WayHead);
                layoutTurnoutB->setSignalB1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case.
        }
    }

    signalHeadName = d_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (setD3WayHead->isChecked()) {
        if (isHeadOnPanel(d3WayHead) &&
            (d3WayHead!=getHeadFromName(layoutTurnoutB->getSignalC1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else if ( (!layoutTurnoutBHorizontal) && (!layoutTurnoutBVertical) ) {
            JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Sorry, cannot place signal heads at turnouts\nthat are not oriented vertical or horizontal."),"",JOptionPane::INFORMATION_MESSAGE);

            if (d3WayHead!=getHeadFromName(layoutTurnoutB->getSignalC1Name())) {
                removeSignalHeadFromPanel(layoutTurnoutB->getSignalC1Name());
                removeAssignment(d3WayHead);
                layoutTurnoutB->setSignalC1Name(signalHeadName);
            }
        }
        else {
            removeSignalHeadFromPanel(layoutTurnoutB->getSignalC1Name());
            place3WayDivergingB();
            removeAssignment(d3WayHead);
            layoutTurnoutB->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(d3WayHead,layoutTurnoutB);
        if (assigned == NONE) {
            if (isHeadOnPanel(d3WayHead) &&
                                isHeadAssignedAnywhere(d3WayHead) ) {
                JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutTurnoutB->getSignalC1Name());
                removeAssignment(d3WayHead);
                layoutTurnoutB->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
// need to figure out what to do in this case.
        }
    }
    // setup Logic if requested and enough information is available
    if (setupA13WayLogic->isChecked()) {
        set3WayLogicThroatContinuing();
    }
    if ( (a23WayHead!=nullptr) && setupA23WayLogic->isChecked() ) {
        set3WayLogicThroatDivergingA();
    }
    if ( (a33WayHead!=nullptr) && setupA33WayLogic->isChecked() ) {
        set3WayLogicThroatDivergingB();
    }
    if (setupB3WayLogic->isChecked()) {
        set3WayLogicDivergingA();
    }
    if (setupC3WayLogic->isChecked()) {
        set3WayLogicContinuing();
    }
    if (setupD3WayLogic->isChecked()) {
        set3WayLogicDivergingB();
    }
    // link the two turnouts
    layoutTurnoutA->setLinkedTurnoutName(signalHeadName);
    layoutTurnoutA->setLinkType(LayoutTurnout::FIRST_3_WAY);
    signalHeadName = turnoutAComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    layoutTurnoutB->setLinkedTurnoutName(signalHeadName);
    layoutTurnoutB->setLinkType(LayoutTurnout::SECOND_3_WAY);
    // finish up
    setSignalsAt3WayOpen = false;
    setSignalsAt3WayTurnoutFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}

/*private*/ bool LayoutEditorTools::get3WaySignalHeadInformation() {
 a13WayHead = getSignalHeadFromEntry(a1_3WaySignalHeadComboBox, true, setSignalsAt3WayTurnoutFrame);
  if (a13WayHead == nullptr) {
      return false;
  }
  a23WayHead = getSignalHeadFromEntry(a2_3WaySignalHeadComboBox, false, setSignalsAt3WayTurnoutFrame);
  a33WayHead = getSignalHeadFromEntry(a3_3WaySignalHeadComboBox, false, setSignalsAt3WayTurnoutFrame);
  if (((a23WayHead == nullptr) && (a33WayHead != nullptr)) || ((a33WayHead == nullptr)
          && (a23WayHead != nullptr))) {
      return false;
  }
  b3WayHead = getSignalHeadFromEntry(b_3WaySignalHeadComboBox, true, setSignalsAt3WayTurnoutFrame);
  if (b3WayHead == nullptr) {
      return false;
  }
  c3WayHead = getSignalHeadFromEntry(c_3WaySignalHeadComboBox, true, setSignalsAt3WayTurnoutFrame);
  if (c3WayHead == nullptr) {
      return false;
  }
  d3WayHead = getSignalHeadFromEntry(d_3WaySignalHeadComboBox, true, setSignalsAt3WayTurnoutFrame);
  if (d3WayHead == nullptr) {
      return false;
  }
  return true;
}

/*private*/ void LayoutEditorTools::place3WayThroatContinuing() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = a1_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


    QPointF coordsA = layoutTurnoutA->getCoordsA();
    QPointF coordsCenter = layoutTurnoutA->getCoordsCenter();

    double aDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsA, coordsCenter));
    QPointF delta =  QPointF(-shift, -shift);

    delta = MathUtil::rotateDEG(delta, aDirDEG);
    QPointF where = MathUtil::add(coordsA, delta);
    setSignalHeadOnPanel(aDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::place3WayThroatDivergingA() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = a2_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);

    QPointF coordsA = layoutTurnoutA->getCoordsA();
    QPointF coordsCenter = layoutTurnoutA->getCoordsCenter();

    double aDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsA, coordsCenter));
    QPointF delta = QPointF(+shift, -shift);

    delta = MathUtil::rotateDEG(delta, aDirDEG);
    QPointF where = MathUtil::add(coordsA, delta);
    setSignalHeadOnPanel(aDirDEG, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::place3WayThroatDivergingB() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = a3_3WaySignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


 QPointF coordsA = layoutTurnoutA->getCoordsA();
 QPointF coordsCenter = layoutTurnoutA->getCoordsCenter();

 double aDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsA, coordsCenter));
 QPointF delta = QPointF(+3.0 * shift, -shift);

 delta = MathUtil::rotateDEG(delta, aDirDEG);
 QPointF where = MathUtil::add(coordsA, delta);
 setSignalHeadOnPanel(aDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::place3WayDivergingA() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = b_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


    QPointF coordsB = layoutTurnoutA->getCoordsB();
    QPointF coordsC = layoutTurnoutA->getCoordsC();
    QPointF coordsCenter = layoutTurnoutA->getCoordsCenter();

    double bDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsCenter));
    double cDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsCenter));
    double diffDirDEG = MathUtil::diffAngleDEG(cDirDEG, bDirDEG);
    double shiftX = shift;
    if (diffDirDEG >= 0.0) {
        shiftX += shift * qCos(qDegreesToRadians(diffDirDEG));
    }
    QPointF delta =  QPointF(shiftX, -shift);

    delta = MathUtil::rotateDEG(delta, cDirDEG);
    QPointF where = MathUtil::add(coordsC, delta);
    setSignalHeadOnPanel(cDirDEG, signalHeadName, where);
}
/*private*/ void LayoutEditorTools::place3WayContinuing() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = c_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    if (signalHeadName.isNull()) {
        signalHeadName = "";
    }
    double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
      qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


    QPointF coordsB = layoutTurnoutB->getCoordsB();
    QPointF coordsC = layoutTurnoutB->getCoordsC();
    QPointF coordsCenter = layoutTurnoutB->getCoordsCenter();

    double bDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsCenter));
    double cDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsCenter));
    double diffDirDEG = MathUtil::diffAngleDEG(cDirDEG, bDirDEG);
    double shiftX = shift;
    if (diffDirDEG >= 0.0) {
        shiftX += shift * qCos(qDegreesToRadians(diffDirDEG));
    }
    QPointF delta = QPointF(shiftX, -shift);

    delta = MathUtil::rotateDEG(delta, bDirDEG);
    QPointF where = MathUtil::add(coordsB, delta);
    setSignalHeadOnPanel(bDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::place3WayDivergingB() {
    if (testIcon == nullptr)
        testIcon = signalIconEditor->getIcon(0);
    QString signalHeadName = d_3WaySignalHeadComboBox->getSelectedItemDisplayName();
 if (signalHeadName.isNull()) {
     signalHeadName = "";
 }
 double shift = //Math.hypot(testIcon.getIconHeight(), testIcon.getIconWidth()) / 2.0;
   qSqrt(pow(testIcon->getIconHeight(),2)+ pow(testIcon->getIconWidth(),2) / 2.0);


 QPointF coordsC = layoutTurnoutB->getCoordsC();
 QPointF coordsB = layoutTurnoutB->getCoordsB();
 QPointF coordsCenter = layoutTurnoutB->getCoordsCenter();

 double bDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsB, coordsCenter));
 double cDirDEG = MathUtil::wrap360(90.0 - MathUtil::computeAngleDEG(coordsC, coordsCenter));
 double diffDirDEG = MathUtil::diffAngleDEG(cDirDEG, bDirDEG);
 double shiftX = shift;
 if (diffDirDEG >= 0.0) {
     shiftX += shift * qCos(qDegreesToRadians(diffDirDEG));
 }
 QPointF delta = QPointF(shiftX, -shift);

 delta = MathUtil::rotateDEG(delta, cDirDEG);
 QPointF where = MathUtil::add(coordsC, delta);
 setSignalHeadOnPanel(cDirDEG, signalHeadName, where);
}

/*private*/ void LayoutEditorTools::set3WayLogicThroatContinuing() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutB->getConnectB();
    if (track==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }

    QString signalHeadName = a1_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutB,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                signalHeadName),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (a23WayHead!=nullptr) {
        // set up logic for continuing head with 3 heads at throat
        if (!initializeBlockBossLogic(signalHeadName))
            return;
        logic->setMode(BlockBossLogic::TRAILINGMAIN);
        logic->setTurnout(turnoutB->getSystemName());
        logic->setSensor1(occupancy->getSystemName());
        if (nextHead!=nullptr) {
            logic->setWatchedSignal1(nextHead->getSystemName(),false);
        }
        if (auxSignal!=nullptr) {
            logic->setWatchedSignal1Alt(auxSignal->getSystemName());
        }
        QString nearSensorName = setupNearLogix(layoutTurnoutA,true,a13WayHead);
        addNearSensorToLogic(nearSensorName);
        finalizeBlockBossLogic();
        return;
    }
    // only one head at the throat
//    JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("InfoMessage9"),"",JOptionPane::INFORMATION_MESSAGE);
    QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Sorry, Layout Editor does not support setting up\nlogic for a single head at the throat of a 3-way turnout."));
    return;
}

/*private*/ void LayoutEditorTools::set3WayLogicThroatDivergingA() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutA->getConnectC();
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }

    QString signalHeadName = a1_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutA,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(signalHeadName))
     return;
    logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
    logic->setTurnout(turnoutA->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr)
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    if (!layoutTurnoutA->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::set3WayLogicThroatDivergingB() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutB->getConnectC();
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because blocks have\nnot been defined around this item."));
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor."),
//                new Object[]{block->getUserName()}),
//                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }

    QString signalHeadName = a3_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutB,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(signalHeadName) )
        return;
    logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
    logic->setTurnout(turnoutB->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr)
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    QString nearSensorName = setupNearLogix(layoutTurnoutA,true,a33WayHead);
    addNearSensorToLogic(nearSensorName);
    if (!layoutTurnoutB->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}
/*private*/ void LayoutEditorTools::set3WayLogicDivergingA() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutA->getConnectA();
    if (track==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }

    QString signalHeadName = b_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutA,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(signalHeadName)) return;
    logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
    logic->setTurnout(turnoutA->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    if (!layoutTurnoutA->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::set3WayLogicContinuing() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutA->getConnectA();
    if (track==nullptr) {
//        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
//                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAtTToTFrame, tr("Information"), tr("Cannot set up logic because all connections\nhave not been defined around this item."));
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }

    QString signalHeadName = c_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutA,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(signalHeadName))
     return;
    logic->setMode(BlockBossLogic::TRAILINGMAIN);
    logic->setTurnout(turnoutB->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    QString nearSensorName = setupNearLogix(layoutTurnoutA,true,c3WayHead);
    addNearSensorToLogic(nearSensorName);
    if (!layoutTurnoutB->isMainlineB())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

/*private*/ void LayoutEditorTools::set3WayLogicDivergingB() {
    TrackSegment* track = (TrackSegment*)layoutTurnoutA->getConnectA();
    if (track==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    LayoutBlock* block = track->getLayoutBlock();
    if (block==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy = block->getOccupancySensor();
    if (occupancy==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
     QMessageBox::information(setSignalsAt3WayTurnoutFrame, tr("Information"), tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(block->getUserName()));
        return;
    }

    QString signalHeadName = d_3WaySignalHeadComboBox->getSelectedItemDisplayName();
    SignalHead* nextHead = getNextSignalFromObject(track, layoutTurnoutA,
            signalHeadName, setSignalsAt3WayTurnoutFrame);
    if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
        JOptionPane::showMessageDialog(setSignalsAt3WayTurnoutFrame,
            tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                block->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    if (!initializeBlockBossLogic(signalHeadName)) return;
    logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
    logic->setTurnout(turnoutB->getSystemName());
    logic->setSensor1(occupancy->getSystemName());
    if (nextHead!=nullptr) {
        logic->setWatchedSignal1(nextHead->getSystemName(),false);
    }
    if (auxSignal!=nullptr) {
        logic->setWatchedSignal1Alt(auxSignal->getSystemName());
    }
    QString nearSensorName = setupNearLogix(layoutTurnoutA,true,d3WayHead);
    addNearSensorToLogic(nearSensorName);
    if (!layoutTurnoutB->isMainlineC())
        logic->setLimitSpeed2(true);
    finalizeBlockBossLogic();
}

//
//The following is for placement of sensors and signal masts at points around the layout
//

/*public*/ void LayoutEditorTools::setSensorsAtBlockBoundaryFromMenu( PositionablePoint* p, MultiIconEditor* theEditor, JFrame* theFrame) {
    boundary = p;
    block1IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
    if (boundary->getConnect2() == nullptr)
    {
        block2IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
    } else {
        block2IDComboBox->setSelectedItem(boundary->getConnect2()->getLayoutBlock()->getBlock());
    }
    setSensorsAtBlockBoundaryFromMenuFlag = true;
    setSensorsAtBlockBoundary(theEditor, theFrame);
    setSensorsAtBlockBoundaryFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSensorsAtBlockBoundary( MultiIconEditor* theEditor, JFrame* theFrame)
{
 sensorIconEditor = theEditor;
 sensorFrame = theFrame;
 if (setSensorsAtBoundaryOpen)
 {
  setSensorsAtBlockBoundaryFrame->setVisible(true);
  return;
 }
 // Initialize if needed
 if (setSensorsAtBlockBoundaryFrame == nullptr)
 {
  westBoundSensor = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  eastBoundSensor = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());

  setSensorsAtBlockBoundaryFrame = new JmriJFrameX( tr("Set Sensors at Block Boundary"), false, true );
  setSensorsAtBlockBoundaryFrame->addHelpMenu("package.jmri.jmrit.display.SetSensorsAtBoundary", true);
  setSensorsAtBlockBoundaryFrame->setLocation(70,30);
//  if(setSensorsAtBlockBoundaryFrame->centralWidget() == nullptr)
//  {
//   QWidget* centralWidget = new QWidget();
//   QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
//   centralWidget->setLayout(centralWidgetLayout);
//   setSensorsAtBlockBoundaryFrame->setCentralWidget(centralWidget);
//  }
  QWidget* theContentPane = setSensorsAtBlockBoundaryFrame->getContentPane();
  QVBoxLayout* centralWidgetLayout;
  theContentPane->setLayout(centralWidgetLayout = new QVBoxLayout());
  QWidget* header = new QWidget();
  header->setLayout(new QVBoxLayout); //(header, BoxLayout.Y_AXIS));

  JPanel* panel11 = new JPanel(new FlowLayout());
  block1NameLabel = new JLabel(tr("Block") + " 1 - "
          + tr("Name"));
  panel11->layout()->addWidget(block1NameLabel);

  panel11->layout()->addWidget(block1IDComboBox);
  block1IDComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  header->layout()->addWidget(panel11);

  JPanel* panel12 = new JPanel(new FlowLayout());
  block2NameLabel = new JLabel(tr("Block") + " 2 - "
          + tr("Name"));
  panel12->layout()->addWidget(block2NameLabel);

  panel12->layout()->addWidget(block2IDComboBox);
  block2IDComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  header->layout()->addWidget(panel12);

  header->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  theContentPane->layout()->addWidget(header);;

  JPanel* panel2 = new JPanel(new FlowLayout());
  QLabel* shTitle = new QLabel(tr("Sensors"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getAnchorSavedSensors = new QPushButton(tr("Get Saved")));
//        getAnchorSavedSensors->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    getSavedAnchorSensors(e);
//                }
//            });
  connect(getAnchorSavedSensors, SIGNAL(clicked()), this, SLOT(getSavedAnchorSensors()));
  getAnchorSavedSensors->setToolTip( "Click to retrieve signal heads previously stored.");
  theContentPane->layout()->addWidget(panel2);

  sensorBlockPanel->setLayout(new QGridLayout());//; 0, 1));
  theContentPane->layout()->addWidget(sensorBlockPanel);

  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  JPanel* panel6 = new JPanel(new FlowLayout());
  panel6->layout()->addWidget(changeSensorAtBoundaryIcon = new QPushButton(tr("Change Sensor Icon")));
  //changeSensorAtBoundaryIcon.addActionListener((ActionEvent e) -> {
  connect(changeSensorAtBoundaryIcon, &QPushButton::clicked, [=]{
      sensorFrame->setVisible(true);
  });
  changeSensorAtBoundaryIcon->setToolTip(tr("Select to change icons used to represent sensors."));
  panel6->layout()->addWidget(new JLabel("	 "));
  panel6->layout()->addWidget(setSensorsAtBlockBoundaryDone = new QPushButton(tr("Done")));
  //setSensorsAtBlockBoundaryDone.addActionListener((ActionEvent e) -> {
  connect(setSensorsAtBlockBoundaryDone, &QPushButton::clicked, [=]{
      setSensorsAtBlockBoundaryDonePressed(/*e*/);
  });
  setSensorsAtBlockBoundaryDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

  //make this button the default button (return or enter activates)
  //Note: We have to invoke this later because we don't currently have a root pane
//  SwingUtilities.invokeLater(() -> {
//      JRootPane rootPane = SwingUtilities.getRootPane(setSensorsAtBlockBoundaryDone);
//      rootPane.setDefaultButton(setSensorsAtBlockBoundaryDone);
//  });
  setSensorsAtBlockBoundaryDone->setDefault(true);

  panel6->layout()->addWidget(setSensorsAtBlockBoundaryCancel = new QPushButton(("Cancel")));
  //setSensorsAtBlockBoundaryCancel.addActionListener((ActionEvent e) -> {
  connect(setSensorsAtBlockBoundaryCancel, &QPushButton::clicked, [=]{
      setSensorsAtBlockBoundaryCancelPressed(/*e*/);
  });
  setSensorsAtBlockBoundaryCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
  ((BorderLayout*)theContentPane->layout())->addWidget(panel6, BorderLayout::South);
#if 0
  setSensorsAtBlockBoundaryFrame.addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
          setSensorsAtBlockBoundaryCancelPressed(null);
      }
  });
#endif
 }

 //sensorBlockPanel.removeAll();
 QList<QWidget*> list = sensorBlockPanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  sensorBlockPanel->layout()->removeWidget(w);
  delete w;
 }

 if (boundary->getType() != PositionablePoint::END_BUMPER) {
     eastBoundSensor->setBoundaryTitle(tr("East (or South) Bound"));
     if ((setSensorsAtBlockBoundaryFromMenuFlag) && (boundary->getType() == PositionablePoint::ANCHOR)) {
         if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
             eastBoundSensor->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
         } else {
             eastBoundSensor->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
         }
     }
     //eastBoundSensor->getDetailsPanel()->setBackground(QColor(255, 255, 200));
     eastBoundSensor->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(255, 255, 200)}");
     sensorBlockPanel->layout()->addWidget(eastBoundSensor->getDetailsPanel());

     westBoundSensor->setBoundaryTitle(tr("West (or North) Bound"));
     if (setSensorsAtBlockBoundaryFromMenuFlag) {
         if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
             westBoundSensor->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
         } else {
             westBoundSensor->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
         }
     }
     //westBoundSensor->getDetailsPanel()->setBackground(QColor(200, 255, 255));
     westBoundSensor->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(200, 255, 255)}");
     sensorBlockPanel->layout()->addWidget(westBoundSensor->getDetailsPanel());
 } else {
     if (setSensorsAtBlockBoundaryFromMenuFlag) {
         if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
             eastBoundSensor->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
             //eastBoundSensor->getDetailsPanel()->setBackground(QColor(200, 255, 255));
             eastBoundSensor->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(200, 255, 255)}");
             sensorBlockPanel->layout()->addWidget(eastBoundSensor->getDetailsPanel());
         } else {
             westBoundSensor->setBoundaryLabelText(tr("ProtectingBlock") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
             //westBoundSensor->getDetailsPanel()->setBackground(QColor(255, 255, 200));
             westBoundSensor->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(200, 255, 255)}");
             sensorBlockPanel->layout()->addWidget(westBoundSensor->getDetailsPanel());
         }
     }
 }

 block1IDComboBox->setVisible(!setSensorsAtBlockBoundaryFromMenuFlag);
 block2IDComboBox->setVisible(!setSensorsAtBlockBoundaryFromMenuFlag);

 if (setSensorsAtBlockBoundaryFromMenuFlag) {
     block1NameLabel->setText(tr("Block") + " 1 "
             + tr("Name")
             + " " + boundary->getConnect1()->getLayoutBlock()->getId());
     if (boundary->getConnect2() != nullptr) {
         block2NameLabel->setText(tr("Block") + " 2 "
                 + tr("Name")
                 + " " + boundary->getConnect2()->getLayoutBlock()->getId());
     }
     getSavedAnchorSensors(/*null*/);
 } else {
     block1NameLabel->setText(tr("Name") + " 1 "
             + tr("Name"));
     block2NameLabel->setText(tr("Name") + " 2  "
             + tr("Name"));
 }
 //boundary should never be null... however, just in case...
 bool enable = ((boundary != nullptr) && (boundary->getType() != PositionablePoint::END_BUMPER));
 block2NameLabel->setVisible(enable);

 if (!setSensorsAtBlockBoundaryOpenFlag) {
     setSensorsAtBlockBoundaryFrame->resize(QSize());
     setSensorsAtBlockBoundaryFrame->pack();
     setSensorsAtBlockBoundaryOpenFlag = true;
 }
 setSensorsAtBlockBoundaryFrame->setVisible(true);
}   //setSensorsAtBlockBoundary

/**
 * Returns the Sensor* corresponding to an entry field in the specified dialog->
 *		This also takes care of UpperCase and trimming of leading and trailing blanks.
 *		If entry is required, and no entry is present, and error message is sent.
 *      An error message also results if a sensor head with the entered name is not
 *      found in the SensorTable.
 */
/*public*/ Sensor* LayoutEditorTools::getSensorFromEntry(QString sensorName, bool requireEntry,
                JmriJFrame* frame) {
    QString str = sensorName;
    if ( (str==nullptr) || (str==("")) ) {
        if (requireEntry) {
//            JOptionPane::showMessageDialog(frame,tr("SensorsError5"),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
            QMessageBox::critical(frame, tr("Error"), tr("Error - Sensor name was not entered. Please enter\na sensor name for required positions or cancel."));
        }
        return NULL;
    }
    Sensor* head = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(str);
    if (head==nullptr) {
//        JOptionPane::showMessageDialog(frame,
//                tr("SensorsError4"),
//                    new Object[]{str}), tr("Error"),
//                        JOptionPane::ERROR_MESSAGE);
        QMessageBox::critical(frame, tr("Error"), tr("Error - Sensor \"%1\" does not exist. Please correct name\nor enter this Sensor in the Sensor Table, and try again.").arg(str));
        return NULL ;
    }
    return (head);
}
/**
 * Returns a Sensor* given a name
 */
/*public*/ Sensor* LayoutEditorTools::getSensorFromName(QString str) {
    if ( (str==nullptr) || (str==("")) ) {
        return NULL;
    }
    return  (((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(str));
}

/*public*/ SensorIcon* LayoutEditorTools::getSensorIcon(QString sensorName) {
    SensorIcon* l = new SensorIcon(new NamedIcon("program:/resources/icons/smallschematics/tracksegments/circuit-error.gif",
                                                "program:/resources/icons/smallschematics/tracksegments/circuit-error.gif"),layoutEditor);
    l->setIcon("SensorStateActive", sensorIconEditor->getIcon(0));
    l->setIcon("SensorStateInactive", sensorIconEditor->getIcon(1));
    l->setIcon("BeanStateInconsistent", sensorIconEditor->getIcon(2));
    l->setIcon("BeanStateUnknown", sensorIconEditor->getIcon(3));
    l->setSensor(sensorName);
    return l;
}

/**
 * Returns true if the specified Sensor*  is assigned to an object
 *		on the panel, regardless of whether an icon is displayed or not
 * With sensors we do allow the same sensor to be allocated in both directions.
 */
/*public*/ bool LayoutEditorTools::isSensorAssignedAnywhere(Sensor* sensor)
{
 bool result = false;
 for (PositionablePoint* po : layoutEditor->getPositionablePoints())
 {
     if (po->getEastBoundSensor() == sensor) {
      result = true;
      break;
     }
     if (po->getWestBoundSensor() == sensor) {
      result = true;
      break;
     }
 }
 if (!result)
 {
  //check turnouts and slips
  for (LayoutTurnout* to : *layoutEditor->getLayoutTurnoutsAndSlips()) {
      if (whereIsSensorAssigned(sensor, to) != LayoutTurnout::NONE) {
          result = true;
          break;
      }
  }
 }
 if (!result)
 {
  //check level crossings
  for (LevelXing* x : layoutEditor->getLevelXings())
  {
   if ((x->getSensorA() != nullptr) && x->getSensorA() == sensor) {
       result = true;
       break;
   }
   if ((x->getSensorB() != nullptr) && x->getSensorB() == sensor) {
       result = true;
       break;
   }
   if ((x->getSensorC() != nullptr) && x->getSensorC() == sensor) {
       result = true;
       break;
   }
   if ((x->getSensorD() != nullptr) && x->getSensorD() == sensor) {
       result = true;
       break;
   }
  }
 }

 return result;
}   //isSensorAssignedAnywhere

/*private*/ int LayoutEditorTools::whereIsSensorAssigned(Sensor* sensor, LayoutTurnout* lTurnout) {
    int result = LayoutTurnout::NONE;

    if (sensor != nullptr && lTurnout != nullptr) {
        QString sName = sensor->getSystemName();
        QString uName = sensor->getUserName();

        QString name = lTurnout->getSensorAName();
        if (!name.isEmpty() && name == (uName) || name == (sName)) {
            return LayoutTurnout::POINTA1;
        }
        name = lTurnout->getSensorBName();
        if (!name.isEmpty() && name == (uName) || name == (sName)) {
            return LayoutTurnout::POINTA2;
        }
        name = lTurnout->getSensorCName();
        if (!name.isEmpty() && name == (uName) || name == (sName)) {
            return LayoutTurnout::POINTA3;
        }
        name = lTurnout->getSensorDName();
        if (!name.isEmpty() && name == (uName) || name == (sName)) {
            return LayoutTurnout::POINTB1;
        }
    }
    return result;
}   //whereIsSensorAssigned

bool LayoutEditorTools::sensorAssignedElseWhere(Sensor* sensor){
//        int i = JOptionPane::showConfirmDialog(NULL, tr("DuplicateSensorAssign"),
//                new Object[]{ sensor }),
//        tr("DuplicateSensorAssignTitle"),
//        JOptionPane::YES_NO_OPTION);
//    if(i ==0) {
//        return true;
    switch(QMessageBox::question(0, tr("Sensor Already Assigned"), tr("Sensor \"%1\" has already been assigned on the panel\nAre you sure you want to assign it again?").arg(sensor->getDisplayName()), QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
     return true;
    default:
     break;
    }
    return false;
}
/**
 * Removes the assignment of the specified Sensor* to either a turnout,
 *		a positionable point, or a level crossing wherever it is assigned
 */
/*public*/ bool LayoutEditorTools::removeSensorAssignment(Sensor* sensor)
{
 log->trace(tr("Remove sensor assignment at block boundary for '%1'").arg(sensor->getDisplayName()));  // NOI18N
         if (!static_cast<EntryExitPairs*>(InstanceManager::getDefault("EntryExitPairs"))->deleteNxPair(sensor)) {
             log->trace(tr("Removal of NX pairs for sensor '%1' failed").arg(sensor->getDisplayName()));  // NOI18N
             return false;
         }
         for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
             if (po->getEastBoundSensor() == sensor) {
                 po->setEastBoundSensor(nullptr);
             }
             if (po->getWestBoundSensor() == sensor) {
                 po->setWestBoundSensor(nullptr);
             }
         }

         for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
          LayoutTurnout* to = (LayoutTurnout*)lt;
             if (to->getSensorA() == sensor) {
                 to->setSensorA(nullptr);
             }
             if (to->getSensorB() == sensor) {
                 to->setSensorB(nullptr);
             }
             if (to->getSensorC() == sensor) {
                 to->setSensorC(nullptr);
             }
             if (to->getSensorD() == sensor) {
                 to->setSensorD(nullptr);
             }
         }

         for (LayoutTrack* lt : layoutEditor->getLayoutSlips())
         {
          LayoutSlip* to = (LayoutSlip*)lt;
             if (to->getSensorA() == sensor) {
                 to->setSensorA(nullptr);
             }
             if (to->getSensorB() == sensor) {
                 to->setSensorB(nullptr);
             }
             if (to->getSensorC() == sensor) {
                 to->setSensorC(nullptr);
             }
             if (to->getSensorD() == sensor) {
                 to->setSensorD(nullptr);
             }
         }

         for (LayoutTrack* lt : layoutEditor->getLevelXings()) {
          LevelXing* x = (LevelXing*)lt;
             if (x->getSensorA() == sensor) {
                 x->setSensorAName(nullptr);
             }
             if (x->getSensorB() == sensor) {
                 x->setSensorBName(nullptr);
             }
             if (x->getSensorC() == sensor) {
                 x->setSensorCName(nullptr);
             }
             if (x->getSensorD() == sensor) {
                 x->setSensorDName(nullptr);
             }
         }

         return true;
}

/**
 * Removes the Sensor* with the specified name from the panel and from
 *		assignment to any turnout, positionable point, or level crossing
 */
//@SuppressWarnings("NULL")
/*public*/ bool LayoutEditorTools::removeSensorFromPanel(Sensor* sensor)
{
 log->trace(tr("Remove sensor icon and assignment for '%1'").arg(sensor->getDisplayName()));  // NOI18N
 if (!removeSensorAssignment(sensor)) {
     return false;
 }

 SensorIcon* h = nullptr;
 int index = -1;
 for (int i = 0; (i < layoutEditor->sensorList->size()) && (index == -1); i++) {
     h = layoutEditor->sensorList->at(i);
     if (h->getSensor() == sensor) {
         index = i;
     }
 }
 if ((h != nullptr) && (index != -1)) {
     layoutEditor->sensorList->remove(index);
     h->remove();
     h->dispose();
     needRedraw = true;
 }
 return true;
}

/*private*/ void LayoutEditorTools::getSavedAnchorSensors (JActionEvent* /*a*/) // SLOT
{
    if ( !getSimpleBlockInformation() ) return;
    eastBoundSensor->setTextField(boundary->getEastBoundSensorName());
    westBoundSensor->setTextField(boundary->getWestBoundSensorName());

    if(boundary->getType()!=PositionablePoint::END_BUMPER)
    {
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary))
        {
            eastBoundSensor->setBoundaryLabelText("Protecting Block : " + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
        }
        else {
            eastBoundSensor->setBoundaryLabelText("Protecting Block : " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        }
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            westBoundSensor->setBoundaryLabelText("Protecting Block : " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        } else {
            westBoundSensor->setBoundaryLabelText("Protecting Block : " + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
        }
    } else {
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            westBoundSensor->setBoundaryLabelText("End of Block " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        } else{
            eastBoundSensor->setBoundaryLabelText("End of Block " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        }
    }

//    setSensorsAtBlockBoundaryFrame->setPreferredSize(nullptr);
//    setSensorsAtBlockBoundaryFrame.pack();
}

/*private*/ void LayoutEditorTools::setSensorsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/) {
    setSensorsAtBoundaryOpen = false;
    setSensorsAtBlockBoundaryFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setSensorsAtBlockBoundaryDonePressed (JActionEvent* /*a*/) // SLOT
{
 if ( !getSimpleBlockInformation() ) return;
 Sensor* eastSensor = getSensorFromEntry(eastBoundSensor->getText(),false,setSensorsAtBlockBoundaryFrame);
 Sensor* westSensor = getSensorFromEntry(westBoundSensor->getText(),false,setSensorsAtBlockBoundaryFrame);
 Sensor* currEastSensor = InstanceManager::sensorManagerInstance()->getSensor(boundary->getEastBoundSensorName());
 Sensor* currWestSensor = InstanceManager::sensorManagerInstance()->getSensor(boundary->getWestBoundSensorName());

 if (log->isTraceEnabled()) {
     log->trace(tr("current sensors: east = %1, west = %2").arg(  // NOI18N
             (currEastSensor == nullptr) ? "- none- " : currEastSensor->getDisplayName()).arg(  // NOI18N
             (currWestSensor == nullptr) ? "- none- " : currWestSensor->getDisplayName()));  // NOI18N
     log->trace(tr("new sensors: east = %1, west = %2").arg(  // NOI18N
             (eastSensor == nullptr) ? "- none- " : eastSensor->getDisplayName()).arg(  // NOI18N
             (westSensor == nullptr) ? "- none- " : westSensor->getDisplayName()));  // NOI18N
 }

 if (eastSensor == nullptr) {
     if (currEastSensor != nullptr && removeSensorFromPanel(currEastSensor)) {
         boundary->setEastBoundSensor(nullptr);
     }
 } else if (eastBoundSensor != nullptr) {
     setBoundarySensor(eastSensor, currEastSensor, eastBoundSensor, "East");  // NOI18N
 }

 if (westSensor == nullptr) {
     if (currWestSensor != nullptr && removeSensorFromPanel(currWestSensor)) {
         boundary->setWestBoundSensor(nullptr);
     }
 } else if (westBoundSensor != nullptr) {
     setBoundarySensor(westSensor, currWestSensor, westBoundSensor, "West");  // NOI18N
 }

 setSensorsAtBlockBoundaryOpenFlag = false;
 setSensorsAtBlockBoundaryFrame->setVisible(false);
 if (needRedraw) {
     layoutEditor->redrawPanel();
     needRedraw = false;
     layoutEditor->setDirty();
 }
}

/**
 * Attached a sensor to the block boundary positional point.
 * @since 4.11.2
 * @param newSensor The sensor that is being added.
 * @param currSensor The sensor that might already be there, otherwise null.
 * @param beanDetail The BeanDetails object that contains the supporting data.
 * @param direction The direction, East or West.
 */
void LayoutEditorTools::setBoundarySensor(Sensor* newSensor, Sensor* currSensor,
        BeanDetails* beanDetail, QString direction) {
    if (currSensor == nullptr) {
        if (!isSensorAssignedAnywhere(newSensor)) {
            log->trace(tr("Add sensor '%1'").arg(newSensor->getDisplayName()));  // NOI18N
            if (direction == ("West")) {  // NOI18N
                boundary->setWestBoundSensor(beanDetail->getText());
            } else {
                boundary->setEastBoundSensor(beanDetail->getText());
            }
            if (beanDetail->addToPanel()) {
                log->trace(tr("Add icon for sensor '%1'").arg(newSensor->getDisplayName()));  // NOI18N
                if (direction == ("West")) {  // NOI18N
                    placeWestBoundIcon(getSensorIcon(beanDetail->getText()),
                            beanDetail->isRightSelected(), 0.0);
                } else {
                    placeEastBoundIcon(getSensorIcon(beanDetail->getText()),
                            beanDetail->isRightSelected(), 0.0);
                }
                needRedraw = true;
            }
        } else {
            sensorAssignedElseWhere(newSensor);
        }
    } else if (currSensor == newSensor) {
         if (beanDetail->addToPanel()) {
            if (!isSensorOnPanel(newSensor)) {
                log->trace(tr("Add icon for existing sensor '%1'").arg(newSensor->getDisplayName()));  // NOI18N
                if (direction == ("West")) {  // NOI18N
                    placeWestBoundIcon(getSensorIcon(beanDetail->getText()),
                            beanDetail->isRightSelected(), 0.0);
                } else {
                    placeEastBoundIcon(getSensorIcon(beanDetail->getText()),
                            beanDetail->isRightSelected(), 0.0);
                }
                needRedraw = true;
            }
        }
    } else {
        if (!isSensorAssignedAnywhere(newSensor)) {
            if (removeSensorFromPanel(currSensor)) {
                log->trace(tr("Replace sensor '%1' with sensor '%2'").arg(  // NOI18N
                        currSensor->getDisplayName()).arg(newSensor->getDisplayName()));
                if (direction == ("West")) {  // NOI18N
                    boundary->setWestBoundSensor(beanDetail->getText());
                } else {
                    boundary->setEastBoundSensor(beanDetail->getText());
                }
                if (beanDetail->addToPanel()) {
                    log->trace(tr("Add icon for replacement sensor '%1'").arg(  // NOI18N
                            newSensor->getDisplayName()));
                    if (direction == ("West")) {  // NOI18N
                        placeWestBoundIcon(getSensorIcon(beanDetail->getText()),
                                beanDetail->isRightSelected(), 0.0);
                    } else {
                        placeEastBoundIcon(getSensorIcon(beanDetail->getText()),
                                beanDetail->isRightSelected(), 0.0);
                    }
                    needRedraw = true;
                }
            }
        } else {
            sensorAssignedElseWhere(newSensor);
        }
    }
}

/*public*/ bool LayoutEditorTools::isSensorOnPanel(Sensor* sensor)
{
    SensorIcon* s = NULL;
    for (int i=0;i<layoutEditor->sensorList->size();i++) {
        s = layoutEditor->sensorList->at(i);
        if (s->getSensor() == sensor) {
            return true;
        }
    }
    return false;
}



/*public*/ void LayoutEditorTools::setSignalMastsAtBlockBoundaryFromMenu(PositionablePoint* p)
{
 boundary = p;
 block1IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
 if (boundary->getType() != PositionablePoint::END_BUMPER)
 {
     block2IDComboBox->setSelectedItem(boundary->getConnect2()->getLayoutBlock()->getBlock());
 } else {
     block2IDComboBox->setSelectedItem(boundary->getConnect1()->getLayoutBlock()->getBlock());
 }
 setSignalMastsAtBlockBoundaryFromMenuFlag = true;
 setSignalMastsAtBlockBoundary();
 setSignalMastsAtBlockBoundaryFromMenuFlag = false; return;
}

/*public*/ void LayoutEditorTools::setSignalMastsAtBlockBoundary()
{
 if (setSignalMastsAtBoundaryOpen) {
     setSignalMastsAtBoundaryFrame->setVisible(true);
     return;
 }
 // Initialize if needed
 if (setSignalMastsAtBoundaryFrame == nullptr)
 {
  eastSignalMast = new BeanDetails("Signal Mast", (Manager*)InstanceManager::getDefault("SignalMastManager"));
  westSignalMast = new BeanDetails("Signal Mast", (Manager*)InstanceManager::getDefault("SignalMastManager"));
  setSignalMastsAtBoundaryFrame = new JmriJFrameX( tr("Set Signal Masts at Block Boundary"), false, true );
  setSignalMastsAtBoundaryFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalMastsAtBoundary", true);
  setSignalMastsAtBoundaryFrame->setLocation(70,30);
  QWidget* theContentPane = setSignalMastsAtBoundaryFrame->getContentPane();

  QWidget*header = new QWidget();
  header->setLayout(new QVBoxLayout); //(header, BoxLayout.Y_AXIS));

  //Create the block 1 label and combo box
  JPanel* panel11 = new JPanel(new FlowLayout());
  block1NameLabel = new JLabel(tr("Block") + " 1 "
          + tr("Name"));
  panel11->layout()->addWidget(block1NameLabel);
  panel11->layout()->addWidget(block1IDComboBox);
  block1IDComboBox->setToolTip(tr("Enter name of one block where signal masts are needed at block boundary."));
  header->layout()->addWidget(panel11);

  //Create the block 2 label and combo box, visibility will be controlled later
  block2NameLabel = new JLabel(tr("Block") + " 2 "
          + tr("Name"));
  block2IDComboBox->setToolTip(tr("Enter name of one block where signal masts are needed at block boundary."));

  JPanel* panel12 = new JPanel(new FlowLayout());
  panel12->layout()->addWidget(block2NameLabel);
  panel12->layout()->addWidget(block2IDComboBox);
  header->layout()->addWidget(panel12);

  header->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  theContentPane->layout()->addWidget(header);

  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Masts"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getAnchorSavedSignalMasts = new QPushButton(tr("Get Saved")));
//        getAnchorSavedSignalMasts->layout()->addWidgetActionListener(new ActionListener();
//        {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    getSavedAnchorSignalMasts(e);
//                }
//            });
  connect(getAnchorSavedSignalMasts, SIGNAL(clicked()), this, SLOT(getSavedAnchorSignalMasts()));
  getAnchorSavedSignalMasts->setToolTip( "Click to retrieve signal heads previously stored." );
  theContentPane->layout()->addWidget(panel2);

  signalMastBlockPanel->setLayout(new QGridLayout()); //(0, 1));
  theContentPane->layout()->addWidget(signalMastBlockPanel);

  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  JPanel* panel6 = new JPanel(new FlowLayout());
  panel6->layout()->addWidget(setSignalMastsAtBlockBoundaryDone = new QPushButton(tr("Done")));
  //setSignalMastsAtBlockBoundaryDone.addActionListener((ActionEvent e) -> {
  connect(setSignalMastsAtBlockBoundaryDone, &QPushButton::clicked, [=]{
      setSignalMastsAtBlockBoundaryDonePressed(/*e*/);
  });
  setSignalMastsAtBlockBoundaryDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

  //make this button the default button (return or enter activates)
  //Note: We have to invoke this later because we don't currently have a root pane
//  SwingUtilities.invokeLater(() -> {
//      JRootPane rootPane = SwingUtilities.getRootPane(setSignalMastsAtBlockBoundaryDone);
//      rootPane.setDefaultButton(setSignalMastsAtBlockBoundaryDone);
//  });
  setSignalMastsAtBlockBoundaryDone->setDefault(true);

  panel6->layout()->addWidget(setSignalMastsAtBlockBoundaryCancel = new QPushButton(tr("Cancel")));
  //setSignalMastsAtBlockBoundaryCancel.addActionListener((ActionEvent e) -> {
  connect(setSignalMastsAtBlockBoundaryCancel, &QPushButton::clicked, [=]{
      setSignalMastsAtBlockBoundaryCancelPressed(/*e*/);
  });
  setSignalMastsAtBlockBoundaryCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
  theContentPane->layout()->addWidget(panel6);

//  setSignalMastsAtBlockBoundaryFrame.addWindowListener(new WindowAdapter() {
//      @Override
//      public void windowClosing(WindowEvent e) {
//          setSignalMastsAtBlockBoundaryCancelPressed(null);
//      }
//  });
  setSignalMastsAtBlockBoundaryFrame->addWindowListener(new SBBWindowListener(this));
 }

 eastSignalMast->getCombo()->setExcludedItems(QSet<NamedBean*>());
 westSignalMast->getCombo()->setExcludedItems(QSet<NamedBean*>());
 //signalMastBlockPanel->removeAll();
 QList<QWidget*> list = signalMastBlockPanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  signalMastBlockPanel->layout()->removeWidget(w);
  delete w;
 }

 if (boundary->getType() != PositionablePoint::END_BUMPER) {   //Anchor points and Edge Connectors
   eastSignalMast->setBoundaryTitle(tr("East (or South) Bound"));
   if (boundary->getType() == PositionablePoint::EDGE_CONNECTOR) {
       eastSignalMast->setBoundaryTitle(tr("West (or North) Bound"));
   }
   if (setSignalMastsAtBlockBoundaryFromMenuFlag) {
       if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
           eastSignalMast->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
       } else {
           eastSignalMast->setBoundaryLabelText(tr("ProtectingBlock") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
       }
   }
   //eastSignalMast->getDetailsPanel()->setBackground(new Color(255, 255, 200));
   eastSignalMast->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(255, 255, 200)}");
   signalMastBlockPanel->layout()->addWidget(eastSignalMast->getDetailsPanel());

   westSignalMast->setBoundaryTitle(tr("West (or North) Bound"));
   if (boundary->getType() == PositionablePoint::EDGE_CONNECTOR) {
       westSignalMast->setBoundaryTitle(tr("East or SouthBound"));
   }
   if (setSignalMastsAtBlockBoundaryFromMenuFlag) {
       if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
           westSignalMast->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
       } else {
           westSignalMast->setBoundaryLabelText(tr("Protecting Block") + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
       }
   }
   //westSignalMast->getDetailsPanel().setBackground(new Color(200, 255, 255));
   westSignalMast->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(200, 255, 255)}");
   signalMastBlockPanel->layout()->addWidget(westSignalMast->getDetailsPanel());
 } else {    //End Bumper
   if (setSignalMastsAtBlockBoundaryFromMenuFlag) {
       if (isAtWestEndOfAnchor(boundary->getConnect1(), boundary)) {
           eastSignalMast->setBoundaryLabelText(tr("End Of Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
           //eastSignalMast.getDetailsPanel().setBackground(new Color(200, 255, 255));
           eastSignalMast->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(200, 255, 255)}");
           signalMastBlockPanel->layout()->addWidget(eastSignalMast->getDetailsPanel());
       } else {
           westSignalMast->setBoundaryLabelText(tr("End Of Block") + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
           //westSignalMast->getDetailsPanel().setBackground(new Color(255, 255, 200));
           westSignalMast->getDetailsPanel()->setStyleSheet("QWidget{background-color: rgb(255, 255, 200)}");
           signalMastBlockPanel->layout()->addWidget(westSignalMast->getDetailsPanel());
       }
   }
 }
 block1IDComboBox->setVisible(!setSignalMastsAtBlockBoundaryFromMenuFlag);
 block2IDComboBox->setVisible(!setSignalMastsAtBlockBoundaryFromMenuFlag);

 if (setSignalMastsAtBlockBoundaryFromMenuFlag) {
   block1NameLabel->setText(tr("Block") + " 1 "
           + tr("Name")
           + " " + boundary->getConnect1()->getLayoutBlock()->getId());
   if (boundary->getConnect2() != nullptr) {
       block2NameLabel->setText(tr("Block") + " 2 "
               + tr("Name")
               + " " + boundary->getConnect2()->getLayoutBlock()->getId());
       block2NameLabel->setVisible(true);
   } else {
       block2NameLabel->setVisible(false);
   }
   getSavedAnchorSignalMasts(/*null*/);
 }

 if (!setSignalMastsAtBlockBoundaryOpenFlag) {
   setSignalMastsAtBlockBoundaryFrame->resize(QSize());
   setSignalMastsAtBlockBoundaryFrame->pack();
   setSignalMastsAtBlockBoundaryOpenFlag = true;
 }
 refreshSignalMastAtBoundaryComboBox();
 setSignalMastsAtBlockBoundaryFrame->setVisible(true);
}

/**
 * Returns the SignalMast corresponding to an entry field in the specified dialog->
 *		This also takes care of UpperCase and trimming of leading and trailing blanks.
 *		If entry is required, and no entry is present, and error message is sent.
 *      An error message also results if a signalMast head with the entered name is not
 *      found in the SignalMastTable.
 */
/*public*/ SignalMast* LayoutEditorTools::getSignalMastFromEntry(QString signalMastName,bool requireEntry,
                JmriJFrame* /*frame*/) {
    QString str = signalMastName;
    if ( (str==nullptr) || (str==("")) ) {
        if (requireEntry) {
//            JOptionPane::showMessageDialog(frame,tr("SignalMastsError5"),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
            QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - SignalMast name was not entered. Please enter\n                                                                                 a signal mast name for required positions or cancel."));
        }
        return NULL;
    }
    SignalMast* head = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(str);
    if (head==nullptr) {
//        JOptionPane::showMessageDialog(frame,
//                tr("SignalMastsError4"),
//                    new Object[]{str}), tr("Error"),
//                        JOptionPane::ERROR_MESSAGE);
        QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - SignalMast \"%1\" does not exist. Please correct name\nor enter this SignalMast in the SignalMast Table, and try again.").arg(str));
        return NULL ;
    }
    return (head);
}
/**
 * Returns a SignalMast given a name
 */
/*public*/ SignalMast* LayoutEditorTools::getSignalMastFromName(QString str) {
    if ( (str==nullptr) || (str==("")) ) {
        return NULL;
    }
    return  (((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(str));
}

/**
 * Returns true if the specified SignalMast  is assigned to an object
 *		on the panel, regardless of whether an icon is displayed or not
 */
/*public*/ bool LayoutEditorTools::isSignalMastAssignedAnywhere(SignalMast* signalMast)
{
 for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
     if ((po->getEastBoundSignalMast() != nullptr) && po->getEastBoundSignalMast() == signalMast) {
         return true;
     }
     if ((po->getWestBoundSignalMast() != nullptr) && po->getWestBoundSignalMast() == signalMast) {
         return true;
     }
 }

 for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
  LayoutTurnout* to = (LayoutTurnout*)lt;
     if ((to->getSignalAMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalBMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalCMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalDMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
 }

 for (LayoutTrack* lt : layoutEditor->getLayoutSlips()) {
  LayoutSlip* to = (LayoutSlip*)lt;
     if ((to->getSignalAMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalBMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalCMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
     if ((to->getSignalDMast() != nullptr) && to->getSignalDMast() == signalMast) {
         return true;
     }
 }

 for (LayoutTrack* lt : layoutEditor->getLevelXings()) {
  LevelXing* x = (LevelXing*)lt;
     if ((x->getSignalAMast() != nullptr) && x->getSignalAMast() == signalMast) {
         return true;
     }
     if ((x->getSignalBMast() != nullptr) && x->getSignalAMast() == signalMast) {
         return true;
     }
     if ((x->getSignalCMast() != nullptr) && x->getSignalAMast() == signalMast) {
         return true;
     }
     if ((x->getSignalDMast() != nullptr) && x->getSignalAMast() == signalMast) {
         return true;
     }
 }

 return false;
}
/**
 * Removes the assignment of the specified SignalMast to either a turnout,
 *		a positionable point, or a level crossing wherever it is assigned
 */
/*public*/ void LayoutEditorTools::removeSignalMastAssignment(SignalMast* signalMast)
{
    if (signalMast==nullptr)
        return;
    for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
        if ((po->getEastBoundSignalMast() != nullptr) && po->getEastBoundSignalMast() == signalMast) {
            po->setEastBoundSignalMast(nullptr);
        }
        if ((po->getWestBoundSignalMast() != nullptr) && po->getWestBoundSignalMast() == signalMast) {
            po->setWestBoundSignalMast(nullptr);
        }
    }

    for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts())
    {
     LayoutTurnout* to = (LayoutTurnout*)lt;
     if ((to->getSignalAMast() != nullptr) && to->getSignalAMast() == signalMast) {
         to->setSignalAMast(nullptr);
     }
     if ((to->getSignalBMast() != nullptr) && to->getSignalBMast() == signalMast) {
         to->setSignalBMast(nullptr);
     }
     if ((to->getSignalCMast() != nullptr) && to->getSignalCMast() == signalMast) {
         to->setSignalCMast(nullptr);
     }
     if ((to->getSignalDMast() != nullptr) && to->getSignalDMast() == signalMast) {
         to->setSignalDMast(nullptr);
     }
 }

 for (LayoutTrack* lt : layoutEditor->getLayoutSlips()) {
  LayoutSlip* to = (LayoutSlip*)lt;
     if ((to->getSignalAMast() != nullptr) && to->getSignalAMast() == signalMast) {
         to->setSignalAMast(nullptr);
     }

     if ((to->getSignalBMast() != nullptr) && to->getSignalBMast() == signalMast) {
         to->setSignalBMast(nullptr);
     }

     if ((to->getSignalCMast() != nullptr) && to->getSignalCMast() == signalMast) {
         to->setSignalCMast(nullptr);
     }

     if ((to->getSignalDMast() != nullptr) && to->getSignalDMast() == signalMast) {
         to->setSignalDMast(nullptr);
     }
 }

 for (LayoutTrack* lt : layoutEditor->getLevelXings()) {
  LevelXing* x = (LevelXing*)lt;
     if ((x->getSignalAMast() != nullptr) && x->getSignalAMast() == signalMast) {
         x->setSignalAMast(nullptr);
     }

     if ((x->getSignalBMast() != nullptr) && x->getSignalBMast() == signalMast) {
         x->setSignalBMast(nullptr);
     }

     if ((x->getSignalCMast() != nullptr) && x->getSignalCMast() == signalMast) {
         x->setSignalCMast(nullptr);
     }

     if ((x->getSignalDMast() != nullptr) && x->getSignalDMast() == signalMast) {
         x->setSignalDMast(nullptr);
     }
 }
}
/**
 * Removes the SignalMast with the specified name from the panel and from
 *		assignment to any turnout, positionable point, or level crossing
 */
//@SuppressWarnings("NULL")
/*public*/ void LayoutEditorTools::removeSignalMastFromPanel(QString signalMastName) {
    if ( (signalMastName==nullptr) || (signalMastName.length()<1) ) return;
    SignalMast* signalMast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->
                                                    getSignalMast(signalMastName);
    removeSignalMastAssignment(signalMast);
    SignalMastIcon* h = NULL;
    int index = -1;
    for (int i=0;(i<layoutEditor->signalMastList->size())&&(index==-1);i++) {
        h = layoutEditor->signalMastList->at(i);
        if (h->getSignalMast() == signalMast) {
            index = i;
        }
    }
    if (index!=(-1)) {
        layoutEditor->signalMastList->remove(index);
        h->remove();
        h->dispose();
        needRedraw = true;
    }
}

/*private*/ void LayoutEditorTools::getSavedAnchorSignalMasts (JActionEvent* /*a*/) {
    if ( !getSimpleBlockInformation() ) return;
    eastSignalMast->setTextField(boundary->getEastBoundSignalMastName());
    westSignalMast->setTextField(boundary->getWestBoundSignalMastName());
    if(boundary->getType()!=PositionablePoint::END_BUMPER){
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            eastSignalMast->setBoundaryLabelText("Protecting Block : " + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
        }
        else {
            eastSignalMast->setBoundaryLabelText("Protecting Block : " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        }
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            westSignalMast->setBoundaryLabelText("Protecting Block : " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        } else {
            westSignalMast->setBoundaryLabelText("Protecting Block : " + boundary->getConnect2()->getLayoutBlock()->getDisplayName());
        }
    } else {
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            westSignalMast->setBoundaryLabelText("End of Block " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        } else{
            eastSignalMast->setBoundaryLabelText("End of Block " + boundary->getConnect1()->getLayoutBlock()->getDisplayName());
        }
    }
//    setSignalMastsAtBoundaryFrame->setPreferredSize(nullptr);
//    setSignalMastsAtBoundaryFrame.pack();
}

/*private*/ void LayoutEditorTools::setSignalMastsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/) {
    setSignalMastsAtBoundaryOpen = false;
    setSignalMastsAtBoundaryFrame->setVisible(false);
}

void LayoutEditorTools::refreshSignalMastAtBoundaryComboBox(){
    createListUsedSignalMasts();
    usedMasts.removeAt(usedMasts.indexOf(eastSignalMast->getBean()));
    usedMasts.removeAt(usedMasts.indexOf(westSignalMast->getBean()));
    eastSignalMast->getCombo()->setExcludedItems(usedMasts.toSet());
    westSignalMast->getCombo()->setExcludedItems(usedMasts.toSet());
}

/*private*/ void LayoutEditorTools::setSignalMastsAtBlockBoundaryDonePressed (JActionEvent* /*a*/) // SLOT[]
{
 if ( !getSimpleBlockInformation() ) return;
 SignalMast* oldBlock1SignalMast = getSignalMastFromName(boundary->getEastBoundSignalMastName());
 SignalMast* oldBlock2SignalMast = getSignalMastFromName(boundary->getWestBoundSignalMastName());
 SignalMast* block1BoundSignalMast = getSignalMastFromEntry(eastSignalMast->getText(),false,setSignalMastsAtBoundaryFrame);
 SignalMast* block2BoundSignalMast = getSignalMastFromEntry(westSignalMast->getText(),false,setSignalMastsAtBoundaryFrame);

 if(block1BoundSignalMast==nullptr)
 {
  if(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled() && ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->isSignalMastUsed(oldBlock1SignalMast))
  {
   SignallingGuiTools::removeSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock1SignalMast);
  }

  removeSignalMastFromPanel(boundary->getEastBoundSignalMastName());
  removeSignalMastAssignment(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(boundary->getEastBoundSignalMastName()));
  boundary->setEastBoundSignalMast("");
 }
 if(block2BoundSignalMast==nullptr)
 {
  if(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled() && ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->isSignalMastUsed(oldBlock2SignalMast))
  {
   SignallingGuiTools::removeSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock2SignalMast);
  }

  removeSignalMastFromPanel(boundary->getWestBoundSignalMastName());
  removeSignalMastAssignment(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(boundary->getWestBoundSignalMastName()));
  boundary->setWestBoundSignalMast("");
 }
 if(block2BoundSignalMast!=NULL && block1BoundSignalMast!=nullptr)
 {
  if(block1BoundSignalMast == block2BoundSignalMast)
  {
//            JOptionPane::showMessageDialog(setSignalMastsAtBoundaryFrame,
//                tr("SignalMastsError14"),
//                tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - Can not assign the same signal mast in both directions"));
   return;
  }
  if(oldBlock1SignalMast==block2BoundSignalMast && oldBlock2SignalMast==block1BoundSignalMast)
  {
   //We are going for a swap!
   //Need to remove old items first
   removeSignalMastFromPanel(boundary->getWestBoundSignalMastName());
   removeSignalMastFromPanel(boundary->getEastBoundSignalMastName());
   removeSignalMastAssignment(block1BoundSignalMast);
   removeSignalMastAssignment(block2BoundSignalMast);
   //Then place new ones
   SignalMastIcon* l;
   if (eastSignalMast->addToPanel())
   {
    l = new SignalMastIcon(layoutEditor);
    l->setSignalMast(eastSignalMast->getText());
    placeEastBoundIcon(l, eastSignalMast->isRightSelected(), 0);
   }
   if (westSignalMast->addToPanel())
   {
    l = new SignalMastIcon(layoutEditor);
    l->setSignalMast(westSignalMast->getText());
    placeWestBoundIcon(l, westSignalMast->isRightSelected(), 0);
   }
   boundary->setEastBoundSignalMast(eastSignalMast->getText());
   boundary->setWestBoundSignalMast(westSignalMast->getText());
   //Then sort out the logic
   if(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
   {
    SignallingGuiTools::swapSignalMastLogic(setSignalMastsAtBoundaryFrame, block1BoundSignalMast, block2BoundSignalMast);
   }
   needRedraw = true;
  }
 }
 if(!needRedraw)
 {
  if(block1BoundSignalMast!=nullptr)
  {
   if (eastSignalMast->addToPanel())
   {
    if (isSignalMastAssignedAnywhere(block1BoundSignalMast) &&
                        (block1BoundSignalMast!=oldBlock1SignalMast))
    {
//                    JOptionPane::showMessageDialog(setSignalMastsAtBoundaryFrame,
//                        tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                            new Object[]{eastSignalMast->getText()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
     QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1}\" on the panel\n                                                                                         because it is already on the panel.").arg(eastSignalMast->getText()));
     return;
    }
    else
    {
     removeSignalMastFromPanel(boundary->getEastBoundSignalMastName());
     SignalMastIcon* l = new SignalMastIcon(layoutEditor);
     l->setSignalMast(eastSignalMast->getText());
     placeEastBoundIcon(l, eastSignalMast->isRightSelected(), 0);
     removeSignalMastAssignment(block1BoundSignalMast);
     boundary->setEastBoundSignalMast(eastSignalMast->getText());
     needRedraw = true;
    }
   }
   else if ((block1BoundSignalMast!=getSignalMastFromName(boundary->getEastBoundSignalMastName())) &&
    (block1BoundSignalMast!=getSignalMastFromName(boundary->getWestBoundSignalMastName())) )
   {
    if (isSignalMastOnPanel(block1BoundSignalMast))
    {
    //                    JOptionPane::showMessageDialog(setSignalMastsAtBoundaryFrame,
    //                        tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
    //                            new Object[]{eastSignalMast->getText()}),
    //                                tr("Error"),JOptionPane::ERROR_MESSAGE);
     QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(eastSignalMast->getText()));
     return;
    }
    else
    {
     removeSignalMastFromPanel(boundary->getEastBoundSignalMastName());
     removeSignalMastAssignment(block1BoundSignalMast);
     boundary->setEastBoundSignalMast(eastSignalMast->getText());
    }
   }
  }
  if(block2BoundSignalMast!=nullptr)
  {
   if (westSignalMast->addToPanel() )
   {
    if (isSignalMastAssignedAnywhere(block2BoundSignalMast) &&
                        (block2BoundSignalMast!=oldBlock2SignalMast))
    {
//                    JOptionPane::showMessageDialog(setSignalMastsAtBoundaryFrame,
//                        tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                            new Object[]{westSignalMast->getText()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
     QMessageBox::critical(setSignalMastsAtBoundaryFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1}\" on the panel\n                                                                                         because it is already on the panel.").arg(westSignalMast->getText()));
     return;
    }
    else /*(oldBlock2SignalMast!=block2BoundSignalMast)*/
    {
     removeSignalMastFromPanel(boundary->getWestBoundSignalMastName());
     SignalMastIcon* l = new SignalMastIcon(layoutEditor);
     l->setSignalMast(westSignalMast->getText());
     placeWestBoundIcon(l, westSignalMast->isRightSelected(), 0);
     removeSignalMastAssignment(block2BoundSignalMast);
     boundary->setWestBoundSignalMast(westSignalMast->getText());
     needRedraw = true;
    }
   }
   else if ( (block2BoundSignalMast!=getSignalMastFromName(boundary->getEastBoundSignalMastName())) &&
    (block2BoundSignalMast!=oldBlock2SignalMast) )
   {
    if (isSignalMastAssignedAnywhere(block2BoundSignalMast))
    {
     //Need to do this better, so that the signalMast can be on panel multiple times but only alocated to one anchor at a time
     JOptionPane::showMessageDialog(setSignalMastsAtBoundaryFrame,
         tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
             westSignalMast->getText()),
                 tr("Error"),JOptionPane::ERROR_MESSAGE);
     return;
    }
    else
    {
     removeSignalMastFromPanel(boundary->getWestBoundSignalMastName());
     removeSignalMastAssignment(block2BoundSignalMast);
     boundary->setWestBoundSignalMast(westSignalMast->getText());
    }
   }
  }

    //If advanced routing is enabled and then this indicates that we are using this for discovering the signalmast logic paths.
  if(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled() && (block1BoundSignalMast!=NULL || block2BoundSignalMast!=nullptr))
  {
   updateBoundaryBasedSignalMastLogic(oldBlock1SignalMast, oldBlock2SignalMast,
                                                        block1BoundSignalMast,block2BoundSignalMast);
  }
 }
 setSignalMastsAtBoundaryOpen = false;

 setSignalMastsAtBoundaryFrame->setVisible(false);
 if (needRedraw)
 {
  layoutEditor->redrawPanel();
  needRedraw = false;
  layoutEditor->setDirty();
 }
}

/*public*/ void LayoutEditorTools::updateBoundaryBasedSignalMastLogic(SignalMast* oldBlock1SignalMast, SignalMast* oldBlock2SignalMast,
                                                    SignalMast* block1BoundSignalMast,SignalMast* block2BoundSignalMast){
    SignalMastLogicManager* smlm = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"));
    bool old1Used = ((DefaultSignalMastLogicManager*)smlm)->isSignalMastUsed(oldBlock1SignalMast);
    bool old2Used = ((DefaultSignalMastLogicManager*)smlm)->isSignalMastUsed(oldBlock2SignalMast);
    //Just check that the old ones are used in logics somewhere.
    if(old1Used || old2Used){
        bool new1Used = ((DefaultSignalMastLogicManager*)smlm)->isSignalMastUsed(block1BoundSignalMast);
        bool new2Used = ((DefaultSignalMastLogicManager*)smlm)->isSignalMastUsed(block2BoundSignalMast);
        if(new1Used || new2Used) {
            if((new1Used) && (block1BoundSignalMast!=oldBlock1SignalMast)){
                SignallingGuiTools::removeAlreadyAssignedSignalMastLogic(setSignalMastsAtBoundaryFrame, block1BoundSignalMast);
            }
            if((new2Used) && (block2BoundSignalMast!=oldBlock2SignalMast)){
                SignallingGuiTools::removeAlreadyAssignedSignalMastLogic(setSignalMastsAtBoundaryFrame, block2BoundSignalMast);
            }
        }
        if(block1BoundSignalMast!=nullptr){
            if (oldBlock2SignalMast!=NULL && old2Used &&
                  oldBlock2SignalMast==block1BoundSignalMast){
                SignallingGuiTools::updateSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock2SignalMast, block1BoundSignalMast);
            }

            if(oldBlock1SignalMast!=NULL && old1Used &&
                  oldBlock1SignalMast!=block1BoundSignalMast){

                SignallingGuiTools::updateSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock1SignalMast, block1BoundSignalMast);
            }
        }
        if(block2BoundSignalMast!=nullptr){
            if(oldBlock1SignalMast!=NULL && old1Used &&
                  oldBlock1SignalMast==block2BoundSignalMast){

                SignallingGuiTools::updateSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock1SignalMast, block2BoundSignalMast);
            }
            if (oldBlock2SignalMast!=NULL && old2Used &&
                    oldBlock2SignalMast!=block2BoundSignalMast){
                SignallingGuiTools::updateSignalMastLogic(setSignalMastsAtBoundaryFrame, oldBlock2SignalMast, block2BoundSignalMast);
            }
        }
    }
}

/*public*/ void LayoutEditorTools::setIconOnPanel(PositionableIcon* l, int rotation,
                QPoint p) {
    ((Positionable*)l)->setLocation((int)p.x(), (int)p.y());
    if (rotation>0) {
        l->rotate(rotation);
    }
    if(qobject_cast<SignalMastIcon*>(l)!=nullptr){
        layoutEditor->putSignalMast((SignalMastIcon*) l);
    } else if (qobject_cast<SensorIcon*>(l)!=nullptr){
        layoutEditor->putSensor((SensorIcon*) l);
    } else if (qobject_cast<SignalHeadIcon*>(l)!=nullptr){
        layoutEditor->putSignal((SignalHeadIcon*) l);
    }
}

/*public*/ void LayoutEditorTools::setIconOnPanel(PositionableIcon* l, int rotation,
                int xLoc, int yLoc) {
    ((Positionable*)l)->setLocation(xLoc,yLoc);
    if (rotation>0) {
        l->rotate(rotation);
    }
    if(qobject_cast<SignalMastIcon*>(l)!=nullptr){
        layoutEditor->putSignalMast((SignalMastIcon*) l);
    } else if (qobject_cast<SensorIcon*>(l)!=nullptr){
        layoutEditor->putSensor((SensorIcon*) l);
    } else if (qobject_cast<SignalHeadIcon*>(l)!=nullptr){
        layoutEditor->putSignal((SignalHeadIcon*) l);
    }
}

/*private*/ void LayoutEditorTools::placeEastBoundIcon(PositionableIcon* icon, bool right, double fromPoint) {

    QPointF p = boundary->getCoordsCenter();

    //Track segment is used to determine the alignment, therefore this is opposite to the block that we are protecting
    TrackSegment* t = boundary->getConnect2();
    bool dir = true;
    if(boundary->getType()==PositionablePoint::END_BUMPER){
        t = boundary->getConnect1();
    }
    else {
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            t = boundary->getConnect1();
        }
    }

    QPointF pt2;
    if(t->getConnect1()==boundary){
        pt2 = layoutEditor->getCoords(t->getConnect2(),t->getType2());
    } else {
        pt2 = layoutEditor->getCoords(t->getConnect1(),t->getType1());
    }
    setIconOnPanel(t, icon, dir, QPoint(p.x(), p.y()), QPoint(pt2.x(),pt2.y()), right, fromPoint);

}

/*private*/ void LayoutEditorTools::placeWestBoundIcon(PositionableIcon* icon, bool right, double fromPoint) {

    QPointF p = boundary->getCoordsCenter();

    //Track segment is used to determine the alignment, therefore this is opposite to the block that we are protecting
    TrackSegment* t = boundary->getConnect1();
    bool dir = false;
    if(boundary->getType()!=PositionablePoint::END_BUMPER){
        if(isAtWestEndOfAnchor(boundary->getConnect1(), boundary)){
            t = boundary->getConnect2();
        }
    }

    QPointF pt2;
    if(t->getConnect1()==boundary){
        pt2 = layoutEditor->getCoords(t->getConnect2(),t->getType2());
    } else {
        pt2 = layoutEditor->getCoords(t->getConnect1(),t->getType1());
    }
    setIconOnPanel(t, icon, dir, QPoint(p.x(), p.y()), QPoint(pt2.x(),pt2.y()), right, fromPoint);

}

void LayoutEditorTools::setIconOnPanel(TrackSegment* /*t*/, PositionableIcon* l, bool eastbound, QPoint p, QPoint pt2, bool side, double fromPoint){

    QPoint pt1 = p;

    double pt1x;
    double pt1y;
    pt1x = pt1.x();
    pt1y = pt1.y();

    double pt2x;
    double pt2y;
    pt2x = pt2.x();
    pt2y = pt2.y();


    double triX = pt2x-pt1x;
    double triY = pt2y-pt1y;
    double toDegrees = 57.2957795;

    log->debug(QString("X") + QString::number(triX) + " Y" + QString::number(triY));
    QPoint loc =  QPoint(0,0);
    if(triX==0.0)
    {
        //In a vertical Striaght Line
        if(eastbound){
            loc = northToSouth(p, l, side, fromPoint);
        } else {
            loc = southToNorth(p, l, side, fromPoint);
        }
    }
    else if(triY==0.0)
    {
        //In a Horizontal Straight Line
        if(eastbound){
            loc = westToEast(p, l, side, fromPoint);
        } else {
            loc = eastToWest(p, l, side, fromPoint);
        }
    }
    else
    {
        double a;
        double o;
        // Compute arc's chord
        a = pt2x - pt1x;
        o = pt2y - pt1y;
        double radius=qSqrt(((a*a)+(o*o)));  //chord equates to radius of circle

        double pt1xa;
        double pt1ya;
        pt1xa=pt1x+radius;
        pt1ya=pt1y;
        double a1;
        double o1;
        a1 = pt2x - pt1xa;
        o1 = pt2y - pt1ya;
        double chord=qSqrt(((a1*a1)+(o1*o1)));

        double rsq = qPow(radius,2);

        double anglefromdatum = qAcos((rsq+rsq-qPow(chord, 2))/(2*radius*radius));

        log->debug("radius " + QString::number(radius) + " Chord " + QString::number(chord));
        log->debug("Angle from datum line " + /*Math.toDegrees*/QString::number((anglefromdatum)*toDegrees));
        double tanx = o / a;

        double angletan = qAtan(tanx);

        int oldHeight = l->maxHeight();
        int oldWidth = l->maxWidth();

        int rotate = ((int) toDegrees*(anglefromdatum));
        log->debug(QString::number(toDegrees*(angletan))+ " " + a + " " + o + " " + QString::number(toDegrees*(tanx)));


        //pt1 is always our boundary point
        //East side
        if(pt2x>pt1x){
        //East Sides
            if(pt2y>pt1y){
                //"South East Corner"
                rotate = rotate + 270;  //Correct for SM111, sm101, sm121, SM80
                l->rotate(rotate);
                loc = southEastToNorthWest(p, l, oldWidth, oldHeight, rotate, side, fromPoint);
            } else {
                //"North East corner" //correct for sm110, sm70, sm131
                rotate = 270-rotate;
                l->rotate(rotate);
                loc = northEastToSouthWest(p, l, oldWidth, oldHeight, rotate, side, fromPoint);
            }

        } else {
            //West Side
            if(pt2y>pt1y){
                //South West //WORKING FOR SM141, sm130, SM71
                l->rotate(rotate-90);
                //South West
                loc = southWestToNorthEast(p, l, oldWidth, oldHeight, rotate, side, fromPoint);
            } else {
                //North West //Working FOR SM140, SM81, sm120
                rotate = (180-rotate)+90;
                l->rotate(rotate);
                loc = northWestToSouthEast(p, l, oldWidth, oldHeight, rotate, side, fromPoint);
            }
        }
    }
    setIconOnPanel(l, 0, loc);
}

QPoint LayoutEditorTools::southToNorth(QPoint p, PositionableIcon* l, bool right, double fromPoint){
    int offsetx=0;
    int offsety=(int)(p.y()+offSetFromPoint+fromPoint);
    if (right){
        offsetx = (int)p.x()+offSetFromPoint;
    } else {
        offsetx = (int)p.x()-offSetFromPoint-l->maxWidth();
    }
    return  QPoint(offsetx, offsety);
}

QPoint LayoutEditorTools::northToSouth(QPoint p, PositionableIcon* l, bool right, double fromPoint){
    l->rotate(180);
    int offsetx=0;
    int offsety=(int)(p.y()-(offSetFromPoint+fromPoint)-l->maxHeight());
    if(right){
        offsetx = (int)p.x()-offSetFromPoint-l->maxWidth();
    } else {
        offsetx = (int)p.x()+offSetFromPoint;
    }
    return  QPoint(offsetx, offsety);
}

QPoint LayoutEditorTools::westToEast(QPoint p, PositionableIcon* l, bool right, double fromPoint){
    l->rotate(90);
    int offsetx=(int)(p.x()-(l->maxWidth()+(offSetFromPoint+fromPoint-1)));
    int offsety=0;
    if(right){
        offsety = (int)p.y()+(offSetFromPoint-1);
    } else {
        offsety = (int)p.y() - (offSetFromPoint) - l->maxHeight();
    }
    return  QPoint(offsetx, offsety);
}

QPoint LayoutEditorTools::eastToWest(QPoint p, PositionableIcon* l, bool right, double fromPoint){
    l->rotate(-90);
    int offsetx=(int)(p.x()+offSetFromPoint+fromPoint);
    int offsety=0;
    if(right){
        offsety = (int)p.y() - (offSetFromPoint-1) - l->maxHeight();

    } else {
        offsety = (int)p.y()+(offSetFromPoint);
    }
    return  QPoint(offsetx, offsety);
}

/**
* come back to this as its a bit tight to the rail on SM110 need re checking
*/
QPoint LayoutEditorTools::northEastToSouthWest(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angle, bool right, double fromPoint){
    angle = angle-180;
    if (angle<45){
        //Because of the angle things get shifted about.
        int tmpWidth = oldWidth;
        int tmpHeight=oldHeight;
        oldWidth=tmpHeight;
        oldHeight=tmpWidth;
    }
    double toDegrees = 57.2957795;
    double ang = angle;
    double oppAng = 90-ang;
    angle = /*Math.toRadians*/(angle)/toDegrees;
    double oppAngRad = /*Math.toRadians*/(oppAng)/toDegrees;
    double iconAdj = qSin(angle)*oldHeight;
    double iconAdjOpp = qSin(oppAngRad)*oldHeight;
    double bpa = qSin(angle)*(offSetFromPoint+fromPoint);
    double bpo = qSin(oppAngRad)*(offSetFromPoint+fromPoint);
    double ta = qSin(angle)*offSetFromPoint;
    double to = qSin(oppAngRad)*offSetFromPoint;

    if(log->isDebugEnabled()){
        log->debug("north east to south west " + QString::number(angle));
        log->debug("oldWidth " + QString::number(oldWidth) + " oldHeight " + QString::number(oldHeight));
        log->debug("newWidth " + QString::number(l->maxWidth()) + " newHeight " + QString::number(l->maxHeight()));
        log->debug("Icon adj: " + QString::number(iconAdj) + " opp adj: " + QString::number(iconAdjOpp));
        log->debug("boundary point opp " + QString::number(bpo));
        log->debug("boundary point adj " + QString::number(bpa));
        log->debug("track opp " + QString::number(to));
        log->debug("track adj " + QString::number(ta));
    }
    int xpos =0;
    int ypos = 0;
    if (right){
        //double x_dist_to_Icon = (l.maxWidth()-iconAdj)-(bpa-bpo);
        //double y_dist_to_Icon = bpa+bpo+l.maxHeight();

        double x_dist_to_Icon = (iconAdjOpp)-(bpa-to);
        double y_dist_to_Icon = ta+bpo+l->maxHeight();

        log->debug("x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));

        xpos = (int) (p.x()-x_dist_to_Icon);
        ypos = (int) (p.y()-y_dist_to_Icon);

    } else {
        double y_dist_to_Icon = iconAdjOpp+(bpo-ta);
        double x_dist_to_Icon = to+bpa;
        //double y_dist_to_Icon = (l.maxHeight()-iconAdj)-(ta-bpo);
        //double x_dist_to_Icon = bpa+to;
        log->debug("x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));

        xpos = (int) (p.x()+x_dist_to_Icon);
        ypos = (int) (p.y()-y_dist_to_Icon);

    }
    if(log->isDebugEnabled()){
        log->debug("xpos " + xpos);
        log->debug("yPos " + ypos);
    }
    return  QPoint(xpos, ypos);

}

QPoint LayoutEditorTools::southWestToNorthEast(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angle, bool right, double fromPoint){
    angle = 180-angle;


    double oppAng = angle;
    double ang = 90-oppAng;

    //Because of the angle things get shifted about.
    if (ang<45){ //was angle
        int tmpWidth = oldWidth;
        int tmpHeight=oldHeight;
        oldWidth=tmpHeight;
        oldHeight=tmpWidth;
    }
    double toDegrees = 57.2957795;
    ang = (ang)/toDegrees;
    double oppAngRad = /*Math.toRadians*/(oppAng/toDegrees);
    double iconAdj = qSin(ang)*oldHeight;
    double iconAdjOpp = qSin(oppAngRad)*oldHeight;
    double bpa = qSin(ang)*(offSetFromPoint+fromPoint);  //was angle
    double bpo = qSin(oppAngRad)*(offSetFromPoint+fromPoint);
    double ta = qSin(ang)*offSetFromPoint; //was angle
    double to = qSin(oppAngRad)*offSetFromPoint;

    if(log->isDebugEnabled()){
        log->debug("south west to north east " + QString::number(angle));
        log->debug("oldWidth " + QString::number(oldWidth) + " oldHeight " + QString::number(oldHeight));
        log->debug("newWidth " + QString::number(l->maxWidth()) + " newHeight " + QString::number(l->maxHeight()));
        log->debug("Icon adj: " + QString::number(iconAdj) + " opp adj: " + QString::number(iconAdjOpp));
        log->debug("boundary point opp " +QString::number( bpo));
        log->debug("boundary point adj " + QString::number(bpa));
        log->debug("track opp " + QString::number(to));
        log->debug("track adj " + QString::number(ta));
    }

    int xpos;
    int ypos;

    if(right)
    {
        double x_dist_to_Icon = iconAdj+(bpa-to);
        double y_dist_to_Icon = ta+bpo;
        log->debug("x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));

        xpos = (int) (p.x()-x_dist_to_Icon);
        log->debug("xpos " + xpos);
        ypos = (int) (p.y()+y_dist_to_Icon);
        log->debug("yPos " + ypos);
    }
    else {
        double x_dist_to_Icon = (bpa+to)+l->maxWidth();
        //double y_dist_to_Icon = (iconAdj+(ta-bpo));
        double y_dist_to_Icon = (bpo-ta)-(l->maxHeight()-iconAdjOpp);
        //double y_dist_to_Icon = (iconAdj+(ta-bpo));
        log->debug("x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));
        xpos = (int) (p.x()-x_dist_to_Icon);
        ypos = (int) (p.y()+y_dist_to_Icon);
    }
    if(log->isDebugEnabled()){
        log->debug("xpos " + xpos);
        log->debug("yPos " + ypos);
    }
    return  QPoint(xpos, ypos);

}

//Working FOR SM140, SM81, sm120
QPoint LayoutEditorTools::northWestToSouthEast(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angledeg, bool right, double fromPoint){
    log->debug("angle before " + QString::number(angledeg));
    angledeg=180-angledeg;
    angledeg=90-angledeg;
    log->debug("north west to south east " + QString::number(angledeg));
    if (angledeg<45){
        //Because of the angle things get shifted about.
        int tmpWidth = oldWidth;
        int tmpHeight=oldHeight;
        oldWidth=tmpHeight;
        oldHeight=tmpWidth;
    }
    log->debug("oldWidth " + QString::number(oldWidth) + " oldHeight " + QString::number(oldHeight));
    log->debug("newWidth " + QString::number(l->maxWidth()) + " newHeight " + QString::number(l->maxHeight()));
    //double ang = angle;
    double oppAng = 90-angledeg;
    double angle = /*Math.toRadians*/(angledeg)/57.2957795;
    double oppAngRad = /*Math.toRadians*/(oppAng)/57.2957795;
    double iconAdj = qSin(angle)*oldHeight;
    double iconAdjOpp = qSin(oppAngRad)*oldHeight;

    double bpa = qSin(angle)*(offSetFromPoint+fromPoint);  //distance from point
    double bpo = qSin(oppAngRad)*(offSetFromPoint+fromPoint);
    double ta = qSin(angle)*offSetFromPoint; //distance from track
    double to = qSin(oppAngRad)*offSetFromPoint;

    if(log->isDebugEnabled()){
        log->debug("north west to south east " + QString::number(angledeg));
        log->debug("oldWidth " + QString::number(oldWidth) + " oldHeight " + QString::number(oldHeight));
        log->debug("newWidth " + QString::number(l->maxWidth()) + " newHeight " + QString::number(l->maxHeight()));
        log->debug("Icon adj: " + QString::number(iconAdj) + " opp adj: " + QString::number(iconAdjOpp));
        log->debug("boundary point opp " + QString::number(bpo));
        log->debug("boundary point adj " + QString::number(bpa));
        log->debug("track opp " + QString::number(to));
        log->debug("track adj " + QString::number(ta));
    }
    int xpos = 0;
    int ypos = 0;
    if (right){
        //double x_dist_to_Icon = bpa+bpo+l.maxWidth();
        //double y_dist_to_Icon = bpa-(l.maxHeight()-iconAdj);
        double x_dist_to_Icon = (l->maxWidth()+ta+bpo);
        double y_dist_to_Icon = iconAdj+(bpa-to);


        log->debug("right x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));

        xpos = (int) (p.x()-x_dist_to_Icon);
        ypos = (int) (p.y()-y_dist_to_Icon); //was +
    } else {
        //This still needs to be worked out.
        //double y_dist_to_Icon = bpa+bpo+l.maxHeight();
        //double x_dist_to_Icon = iconAdj+(bpa-bpo);

        double y_dist_to_Icon = l->maxHeight()+bpa+to;//+(l.maxWidth()-iconAdj);
        //double y_dist_to_Icon = bpa-(l.maxHeight()-iconAdj);
        //double y_dist_to_Icon = ta+bpo+l.maxHeight();
        double x_dist_to_Icon = (iconAdjOpp)+(bpo-ta);
        //double x_dist_to_Icon = iconAdj+(bpa-to);
        log->debug("left x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));

        xpos = (int) (p.x()-x_dist_to_Icon);
        ypos = (int) (p.y()-y_dist_to_Icon);
    }
    if(log->isDebugEnabled()){
        log->debug(p.x() + " xpos " + xpos);
        log->debug(p.y() + " yPos " + ypos);
    }
    return  QPoint(xpos, ypos);
}


//Correct for SM111, sm101, sm121, SM80
QPoint LayoutEditorTools::southEastToNorthWest(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angleDeg, bool right, double fromPoint){
    angleDeg = 360-angleDeg;

    if (angleDeg>45){
        //Because of the angle things get shifted about.
        int tmpWidth = oldWidth;
        int tmpHeight=oldHeight;
        oldWidth=tmpWidth;
        oldHeight=tmpHeight;
    }

//        double ang = angle;
    double oppAng = 90-angleDeg;
    double angle = /*Math.toRadians*/(angleDeg)/57.2957795;
    double oppAngRad = /*Math.toRadians*/(oppAng)/57.2957795;
    double iconAdj = qSin(angle)*oldHeight;
    double iconAdjOpp = qSin(oppAngRad)*oldHeight;
    double bpa = qSin(angle)*(offSetFromPoint+fromPoint);
    double bpo = qSin(oppAngRad)*(offSetFromPoint+fromPoint);
    double ta = qSin(angle)*offSetFromPoint; //distance from track
    double to = qSin(oppAngRad)*offSetFromPoint;
    if(log->isDebugEnabled()){
        log->debug("south east to north west " + QString::number(angleDeg));
        log->debug("oldWidth " + QString::number(oldWidth) + " oldHeight " + QString::number(oldHeight));
        log->debug("newWidth " + QString::number(l->maxWidth()) + " newHeight " + QString::number(l->maxHeight()));
        log->debug("Icon adj: " + QString::number(iconAdj) + " opp adj: " + QString::number(iconAdjOpp));
        log->debug("boundary point opp " + QString::number(bpo));
        log->debug("boundary point adj " + QString::number(bpa));
        log->debug("track opp " + QString::number(to));
        log->debug("track adj " + QString::number(ta));
    }
    int xpos = 0;
    int ypos = 0;
    if (right){
        //double x_dist_to_Icon = bpa+bpo;
        //double y_dist_to_Icon = (iconAdj+bpa-bpo);
        double x_dist_to_Icon = bpa+to;
        double y_dist_to_Icon = (bpo-ta)-(l->maxHeight()-iconAdjOpp);

        log->debug(QString::number((bpo-ta)-(l->maxHeight()-iconAdjOpp)));
        log->debug(QString::number(bpo-(iconAdj+ta)));
        /*if(angleDeg<45){
            y_dist_to_Icon = (bpo-ta)-(l.maxHeight()-iconAdjOpp);
        } else {
            y_dist_to_Icon = bpo-(iconAdj+ta);
        }*/
        //double y_dist_to_Icon = (l.maxHeight()-iconAdj)+(bpo-ta);
        xpos = (int) (p.x()+x_dist_to_Icon);
        ypos = (int) (p.y()+y_dist_to_Icon);
        log->debug("right x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));
    }
    else {
        //double x_dist_to_Icon = l.maxWidth()-(iconAdj+(bpa-bpo));
        //double y_dist_to_Icon = bpa+bpo;

        double x_dist_to_Icon = (bpa-to)-(l->maxWidth()-iconAdj);
        double y_dist_to_Icon = bpo+ta;

        xpos = (int) (p.x()+x_dist_to_Icon);
        ypos = (int) (p.y()+y_dist_to_Icon);
        log->debug("left x dist " + QString::number(x_dist_to_Icon) + ", y dist " + QString::number(y_dist_to_Icon));
    }
    if(log->isDebugEnabled()){
        log->debug(QString::number(p.x()) + " xpos " + QString::number(xpos));
        log->debug(QString::number(p.y()) + " yPos " + QString::number(ypos));
    }

    return  QPoint(xpos, ypos);
}


/*public*/ bool LayoutEditorTools::isSignalMastOnPanel(SignalMast* signalMast)
{
    SignalMastIcon* s = NULL;
    for (int i=0;i<layoutEditor->signalMastList->size();i++) {
        s = layoutEditor->signalMastList->at(i);
        if (s->getSignalMast() == signalMast) {
            return true;
        }
    }
    return false;
}


/*public*/ void LayoutEditorTools::setSignalMastsAtTurnoutFromMenu(LayoutTurnout* to, QStringList blocks){
    layoutTurnout = to;
    turnout = to->getTurnout();
    signalMastsTurnoutComboBox->setSelectedItem(turnout);
    turnoutBlocks= QVector<QString>(4);
    for(int i = 0; i<blocks.length();i++){
        turnoutBlocks.replace(i,blocks.at(i));
    }
    setSignalMastsAtTurnouts();
}


void LayoutEditorTools::createListUsedSignalMasts(){
    usedMasts = QList<NamedBean*>();
    for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
        //We allow the same sensor to be allocated in both directions.
        if (po!=boundary){
            if (po->getEastBoundSignalMast()!=NULL && po->getEastBoundSignalMastName()!=(""))
                usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(po->getEastBoundSignalMastName()));
            if (po->getWestBoundSignalMast()!=NULL && po->getWestBoundSignalMastName()!=(""))
                usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(po->getWestBoundSignalMastName()));
        }
    }

    for (LayoutTurnout* to : layoutEditor->getLayoutTurnouts()) {
        if (to->getSignalAMast()!=NULL && to->getSignalAMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(to->getSignalAMastName()));
        if (to->getSignalBMastName()!=NULL && to->getSignalBMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(to->getSignalBMastName()));
        if (to->getSignalCMastName()!=NULL && to->getSignalCMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(to->getSignalCMastName()));
        if (to->getSignalDMast()!=NULL && to->getSignalDMastName()!=("") )
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(to->getSignalDMastName()));
    }
    for (LevelXing* x : layoutEditor->getLevelXings()) {
        if (x->getSignalAMastName()!=NULL && x->getSignalAMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(x->getSignalAMastName()));
        if (x->getSignalBMastName()!=NULL && x->getSignalBMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(x->getSignalBMastName()));
        if (x->getSignalCMastName()!=NULL && x->getSignalCMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(x->getSignalCMastName()));
        if (x->getSignalDMastName()!=NULL && x->getSignalDMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(x->getSignalDMastName()));
    }
#if 1
    for (LayoutSlip* sl : layoutEditor->getLayoutSlips()) {
        if (sl->getSignalAMast()!=NULL && sl->getSignalAMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(sl->getSignalAMastName()));
        if (sl->getSignalBMast()!=NULL && sl->getSignalBMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(sl->getSignalBMastName()));
        if (sl->getSignalCMast()!=NULL && sl->getSignalCMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(sl->getSignalCMastName()));
        if (sl->getSignalDMast()!=NULL && sl->getSignalDMastName()!=(""))
            usedMasts.append(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(sl->getSignalDMastName()));
    }
#endif
}

void LayoutEditorTools::refreshSignalMastAtTurnoutComboBox(){
    turnoutSignalMastsGetSaved(nullptr);
    createListUsedSignalMasts();
    usedMasts.removeAt(usedMasts.indexOf(turnoutSignalMastA->getBean()));
    usedMasts.removeAt(usedMasts.indexOf(turnoutSignalMastB->getBean()));
    usedMasts.removeAt(usedMasts.indexOf(turnoutSignalMastC->getBean()));
    usedMasts.removeAt(usedMasts.indexOf(turnoutSignalMastD->getBean()));
    turnoutSignalMastA->getCombo()->setExcludedItems(usedMasts.toSet());
    turnoutSignalMastB->getCombo()->setExcludedItems(usedMasts.toSet());
    turnoutSignalMastC->getCombo()->setExcludedItems(usedMasts.toSet());
    turnoutSignalMastD->getCombo()->setExcludedItems(usedMasts.toSet());
}

/*public*/ void LayoutEditorTools::setSignalMastsAtTurnouts(){

 // Initialize if needed
 if (setSignalMastsAtTurnoutFrame == nullptr) {
        setSignalMastsAtTurnoutOpenFlag = false;

        turnoutSignalMastA = new BeanDetails("SignalMast", // NOI18N
                (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
        turnoutSignalMastB = new BeanDetails("SignalMast", // NOI18N
                (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
        turnoutSignalMastC = new BeanDetails("SignalMast", // NOI18N
                (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
        turnoutSignalMastD = new BeanDetails("SignalMast", // NOI18N
                (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));

//        turnoutSignalMastA.getDetailsPanel().setBackground(new Color(255, 255, 200));
//        turnoutSignalMastB.getDetailsPanel().setBackground(new Color(200, 255, 255));
//        turnoutSignalMastC.getDetailsPanel().setBackground(new Color(200, 200, 255));
//        turnoutSignalMastD.getDetailsPanel().setBackground(new Color(255, 200, 200));
        turnoutSignalMastA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");
        turnoutSignalMastB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");
        turnoutSignalMastC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,255)}");
        turnoutSignalMastD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");

        setSignalMastsAtTurnoutFrame = new JmriJFrameX(tr("Set Signal Masts at Turnout"), false, true);
        oneFrameToRuleThemAll(setSignalMastsAtTurnoutFrame);
        setSignalMastsAtTurnoutFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
//         setSignalMastsAtTurnoutFrame.addHelpMenu("package.jmri.jmrit.display.SetSignalMastsAtTurnout", true);
        setSignalMastsAtTurnoutFrame->setLocation(70, 30);
        QWidget* theContentPane = setSignalMastsAtTurnoutFrame->getContentPane();
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));

        JPanel* panel1 = new JPanel(new FlowLayout());

        turnoutMastNameLabel = new JLabel(
                tr("Turnout")
                + " " + tr("Name"));
        panel1->layout()->addWidget(turnoutMastNameLabel);
        panel1->layout()->addWidget(signalMastsTurnoutComboBox);
        signalMastsTurnoutComboBox->setToolTip(tr("Enter name (system or user) of signal mast"));

        theContentPane->layout()->addWidget(panel1);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        JPanel* panel2 = new JPanel(new FlowLayout());
        JLabel* shTitle = new JLabel(tr("Signal Masts"));
        panel2->layout()->addWidget(shTitle);
        panel2->layout()->addWidget(new JLabel("	  "));
        panel2->layout()->addWidget(getSavedSignalMasts = new QPushButton(tr("Get Saved")));
        //getSavedSignalMasts.addActionListener((ActionEvent e) -> {
        connect(getSavedSignalMasts, &QPushButton::clicked, [=]{
            turnoutSignalMastsGetSaved(/*e*/);
        });
        getSavedSignalMasts->setToolTip(tr("Select to retrieve signal heads previously stored."));
        theContentPane->layout()->addWidget(panel2);

        signalMastTurnoutPanel->setLayout(new QGridLayout());//0, 2));
        theContentPane->layout()->addWidget(signalMastTurnoutPanel);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        QWidget* panel6 = new QWidget();
        panel6->layout()->addWidget(new QLabel("  "));
        panel6->layout()->addWidget(setSignalMastsDone = new QPushButton(tr("Done")));
//        setSignalMastsDone->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setSignalMastsDonePressed(e);
//            }
//        });
        connect(setSignalMastsDone, SIGNAL(clicked()), this, SLOT(setSignalMastsDonePressed()));
        setSignalMastsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
        panel6->layout()->addWidget(setSignalMastsCancel = new QPushButton(tr("Cancel")));
//        setSignalMastsCancel->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setSignalMastsCancelPressed(e);
//            }
//        });
        setSignalMastsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
        theContentPane->layout()->addWidget(panel6);
//        signalMastsJmriFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
////					setSignalMastsCancelPressed(nullptr);
//            }
//        });
        if (turnoutFromMenu) turnoutSignalMastsGetSaved(nullptr);
 }
 turnoutSignalMastA->getCombo()->setExcludedItems(QSet<NamedBean*>());
    turnoutSignalMastB->getCombo()->setExcludedItems(QSet<NamedBean*>());
    turnoutSignalMastC->getCombo()->setExcludedItems(QSet<NamedBean*>());
    turnoutSignalMastD->getCombo()->setExcludedItems(QSet<NamedBean*>());
    //signalMastTurnoutPanel.removeAll();
    QList<QWidget*> list = signalMastTurnoutPanel->findChildren<QWidget*>();
    foreach (QWidget* w, list) {
     signalMastTurnoutPanel->layout()->removeWidget(w);
     delete w;
    }

    signalMastsTurnoutComboBox->setVisible(!setSignalMastsAtTurnoutFromMenuFlag);

    if (setSignalMastsAtTurnoutFromMenuFlag) {
        turnoutMastNameLabel->setText(tr("Turnout")
                + " " + tr("Name")
                + " " + layoutTurnout->getTurnoutName());
    }

    if (!setSignalMastsAtTurnoutOpenFlag) {
        setSignalMastsAtTurnoutFrame->resize(QSize());
        setSignalMastsAtTurnoutFrame->pack();
        setSignalMastsAtTurnoutOpenFlag = true;
    }
    refreshSignalMastAtTurnoutComboBox();
    setSignalMastsAtTurnoutFrame->setVisible(true);
}   //setSignalMastsAtTurnout

/*private*/ void LayoutEditorTools::turnoutSignalMastsGetSaved (JActionEvent* /*a*/) // SLOT
{
 if ( !getTurnoutMastInformation() ) return;
 turnoutBlocks = layoutTurnout->getBlockBoundaries().toVector();
 turnoutSignalMastA->setTextField(layoutTurnout->getSignalAMastName());
 turnoutSignalMastB->setTextField(layoutTurnout->getSignalBMastName());
 turnoutSignalMastC->setTextField(layoutTurnout->getSignalCMastName());
 turnoutSignalMastD->setTextField(layoutTurnout->getSignalDMastName());

 turnoutSignalMastA->setBoundaryLabel(turnoutBlocks.at(0));
 turnoutSignalMastB->setBoundaryLabel(turnoutBlocks.at(1));
 turnoutSignalMastC->setBoundaryLabel(turnoutBlocks.at(2));
 turnoutSignalMastD->setBoundaryLabel(turnoutBlocks.at(3));
 signalMastTurnoutPanel->layout()->removeWidget(turnoutSignalMastA->getDetailsPanel());
 signalMastTurnoutPanel->layout()->removeWidget(turnoutSignalMastB->getDetailsPanel());
 signalMastTurnoutPanel->layout()->removeWidget(turnoutSignalMastC->getDetailsPanel());
 signalMastTurnoutPanel->layout()->removeWidget(turnoutSignalMastD->getDetailsPanel());

 bool blockBoundary = false;
 if(turnoutBlocks.at(0)!=nullptr)
 {
  signalMastTurnoutPanelLayout->addWidget(turnoutSignalMastA->getDetailsPanel(),0,0);
  blockBoundary = true;
 }
 if(turnoutBlocks.at(1)!=nullptr)
 {
  signalMastTurnoutPanelLayout->addWidget(turnoutSignalMastB->getDetailsPanel(),0,1);
  blockBoundary = true;
 }
 if(turnoutBlocks.at(2)!=nullptr)
 {
  signalMastTurnoutPanelLayout->addWidget(turnoutSignalMastC->getDetailsPanel(),1,0);
  blockBoundary = true;
 }
 if(turnoutBlocks.at(3)!=nullptr)
 {
  signalMastTurnoutPanelLayout->addWidget(turnoutSignalMastD->getDetailsPanel(),1,1);
  blockBoundary = true;
 }
 if (!blockBoundary)
  //JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame, "There are no block boundaries on this turnout\nIt is therefore not possible to add Signal Masts to it");
  QMessageBox::critical(0, tr("Error"), tr("There are no block boundaries on this turnout\nIt is therefore not possible to add Signal Masts to it"));
 setSignalMastsAtTurnoutFrame->resize(QSize());
 setSignalMastsAtTurnoutFrame->pack();
}

/*private*/ int LayoutEditorTools::isMastAssignedHere(SignalMast* mast, LayoutTurnout* lTurnout)
{
 if ((mast==nullptr) || (lTurnout==nullptr))
     return NONE;
 QString sysName = mast->getSystemName();
 QString uName = mast->getUserName();
 QString name = lTurnout->getSignalAMastName();
 if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                 (name==(sysName))) ) return A1;
 name = lTurnout->getSignalBMastName();
 if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                 (name==(sysName))) ) return A2;
 name = lTurnout->getSignalCMastName();
 if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                 (name==(sysName))) ) return A3;
 name = lTurnout->getSignalDMastName();
 if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                 (name==(sysName))) ) return B1;
 return NONE;
}

/*public*/ void LayoutEditorTools::removeAssignment(SignalMast* mast)
{
 QString sName = mast->getSystemName();
 QString uName = mast->getUserName();
 for (LayoutTurnout* to : layoutEditor->getLayoutTurnouts()) {
     if ((to->getSignalAMast()!=nullptr) &&
             (to->getSignalAMastName()==(sName) || ((uName!=nullptr) &&
             (to->getSignalAMastName()==(uName))))) to->setSignalAMast("");
     if ((to->getSignalBMast()!=nullptr) &&
             (to->getSignalBMastName()==(sName) || ((uName!=nullptr) &&
             (to->getSignalBMastName()==(uName))))) to->setSignalBMast("");
     if ((to->getSignalCMast()!=nullptr) &&
             (to->getSignalCMastName()==(sName) || ((uName!=nullptr) &&
             (to->getSignalCMastName()==(uName))))) to->setSignalCMast("");
     if ((to->getSignalDMast()!=nullptr) &&
             (to->getSignalDMastName()==(sName) || ((uName!=nullptr) &&
             (to->getSignalDMastName()==(uName))))) to->setSignalDMast("");
 }
 for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
     if ((po->getEastBoundSignalMast()!=nullptr) &&
             (po->getEastBoundSignalMastName()==(sName) || ((uName!=nullptr) &&
             (po->getEastBoundSignalMastName()==(uName)))))
         po->setEastBoundSignalMast("");
     if ((po->getWestBoundSignalMast()!=nullptr) &&
             (po->getWestBoundSignalMastName()==(sName) || ((uName!=nullptr) &&
             (po->getWestBoundSignalMastName()==(uName)))))
         po->setWestBoundSignalMast("");
 }
 for (LevelXing* x : layoutEditor->getLevelXings()) {
     if ((x->getSignalAMastName()!=nullptr) &&
             (x->getSignalAMastName()==(sName) || ((uName!=nullptr) &&
             (x->getSignalAMastName()==(uName))))) x->setSignalAMastName("");
     if ((x->getSignalBMastName()!=nullptr) &&
             (x->getSignalBMastName()==(sName) || ((uName!=nullptr) &&
             (x->getSignalBMastName()==(uName))))) x->setSignalBMastName("");
     if ((x->getSignalCMastName()!=nullptr) &&
             (x->getSignalCMastName()==(sName) || ((uName!=nullptr) &&
             (x->getSignalCMastName()==(uName))))) x->setSignalCMastName("");
     if ((x->getSignalDMastName()!=nullptr) &&
             (x->getSignalDMastName()==(sName) || ((uName!=nullptr) &&
             (x->getSignalDMastName()==(uName))))) x->setSignalDMastName("");
 }
}
/*private*/ void LayoutEditorTools::setSignalMastsDonePressed (JActionEvent* /*a*/) {
    // process turnout name
    if ( !getTurnoutMastInformation() ) return;
    // process signal head names
    SignalMast* turnoutMast = getSignalMastFromEntry(turnoutSignalMastA->getText(),false,setSignalsFrame);
    SignalMast* turnoutMastB = getSignalMastFromEntry(turnoutSignalMastB->getText(),false,setSignalsFrame);
    SignalMast* turnoutMastC = getSignalMastFromEntry(turnoutSignalMastC->getText(),false,setSignalsFrame);
    SignalMast* turnoutMastD = getSignalMastFromEntry(turnoutSignalMastD->getText(),false,setSignalsFrame);
    // place signals as requested
    if (turnoutSignalMastA->addToPanel()) {
        if (isSignalMastOnPanel(turnoutMast) &&
            (turnoutMast!=getSignalMastFromName(layoutTurnout->getSignalAMastName())))
        {
//            JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
//                    new Object[]{turnoutSignalMastA->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot place signal head \"%1\" on the panel\n                                                                   because it is already on the panel.").arg(turnoutSignalMastA->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(layoutTurnout->getSignalAMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(turnoutSignalMastA->getText());
            placingBlock(l, turnoutSignalMastA->isRightSelected(), 0.0);
            removeAssignment(turnoutMast);
            layoutTurnout->setSignalAMast(turnoutSignalMastA->getText());
            needRedraw = true;
        }
    }
    else if (turnoutMast!=nullptr){
        int assigned = isMastAssignedHere(turnoutMast,layoutTurnout);
        if (assigned == NONE) {
            if ( isSignalMastOnPanel(turnoutMast) &&
                                isSignalMastAssignedAnywhere(turnoutMast) ) {
//                JOptionPane::showMessageDialog(setSignalsFrame,
//                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
//                        new Object[]{turnoutSignalMastA->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot assign signal head \"{0}\" to this turnout\n                                                                       because it is already on the panel at a different place.").arg(turnoutSignalMastA->getText()));
                return;
            }
            else {
                removeSignalMastFromPanel(layoutTurnout->getSignalAMastName());
                removeAssignment(turnoutMast);
                layoutTurnout->setSignalAMast(turnoutSignalMastA->getText());
            }
        }
        else if (assigned!=A1) {
// need to figure out what to do in this case.
        }
    }
    else {
        removeSignalMastFromPanel(layoutTurnout->getSignalAMastName());
        layoutTurnout->setSignalAMast("");
    }
    if ( (turnoutSignalMastB->addToPanel()) && (turnoutMastB!=nullptr) ) {
        if (isSignalMastOnPanel(turnoutMastB) &&
            (turnoutMastB!=getSignalMastFromName(layoutTurnout->getSignalBMastName()))) {
//            JOptionPane::showMessageDialog(setSignalsFrame,
//                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
//                    new Object[]{turnoutSignalMastB->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot place signal head \"%1\" on the panel\n                                                                   because it is already on the panel.").arg(turnoutSignalMastB->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(layoutTurnout->getSignalBMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(turnoutSignalMastB->getText());
            placingBlockB(l, turnoutSignalMastB->isRightSelected(), 0.0);
            removeAssignment(turnoutMastB);
            layoutTurnout->setSignalBMast(turnoutSignalMastB->getText());
            needRedraw = true;
        }
    }
    else if (turnoutMastB!=nullptr) {
        int assigned = isMastAssignedHere(turnoutMastB,layoutTurnout);
        if (assigned == NONE) {
            if (isSignalMastOnPanel(turnoutMastB) &&
                                isSignalMastAssignedAnywhere(turnoutMastB) ) {
//                JOptionPane::showMessageDialog(setSignalsFrame,
//                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
//                        new Object[]{turnoutSignalMastB->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot assign signal head \"{0}\" to this turnout\n                                                                       because it is already on the panel at a different place.").arg(turnoutSignalMastB->getText()));
                return;
            }
            else {
                removeSignalMastFromPanel(layoutTurnout->getSignalBMastName());
                removeAssignment(turnoutMastB);
                layoutTurnout->setSignalBMast(turnoutSignalMastB->getText());
            }
        }
        else if (assigned!=A2) {
// need to figure out what to do in this case.
        }
    }
    else {
        removeSignalMastFromPanel(layoutTurnout->getSignalBMastName());
        layoutTurnout->setSignalBMast("");
    }
    if(turnoutMastC!=nullptr){
        if (turnoutSignalMastC->addToPanel()) {
            if (isSignalMastOnPanel(turnoutMastC) &&
                (turnoutMastC!=getSignalMastFromName(layoutTurnout->getSignalCMastName()))) {
//                JOptionPane::showMessageDialog(setSignalsFrame,
//                    tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
//                        new Object[]{turnoutSignalMastC->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot place signal head \"%1\" on the panel\n                                                                   because it is already on the panel.").arg(turnoutSignalMastC->getText()));
                return;
            }
            else {
                removeSignalMastFromPanel(layoutTurnout->getSignalCMastName());
                SignalMastIcon* l = new SignalMastIcon(layoutEditor);
                l->setSignalMast(turnoutSignalMastC->getText());
                placingBlockC(l, turnoutSignalMastC->isRightSelected(), 0.0);
                removeAssignment(turnoutMastC);
                layoutTurnout->setSignalCMast(turnoutSignalMastC->getText());
                needRedraw = true;
            }
        }
        else {
            int assigned = isMastAssignedHere(turnoutMastC,layoutTurnout);
            if (assigned == NONE) {
                if (isSignalMastOnPanel(turnoutMastC)  &&
                                    isSignalMastAssignedAnywhere(turnoutMastC) ) {
//                    JOptionPane::showMessageDialog(setSignalsFrame,
//                        tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
//                            new Object[]{turnoutSignalMastC->text()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot assign signal head \"{0}\" to this turnout\n                                                                       because it is already on the panel at a different place.").arg(turnoutSignalMastC->getText()));
                    return;
                }
                else {
                    removeSignalMastFromPanel(layoutTurnout->getSignalCMastName());
                    removeAssignment(turnoutMastC);
                    layoutTurnout->setSignalCMast(turnoutSignalMastC->getText());
                }
            }
            else if (assigned!=A3) {
// need to figure out what to do in this case.
            }
        }
    }
    else{
        removeSignalMastFromPanel(layoutTurnout->getSignalCMastName());
        layoutTurnout->setSignalCMast("");
    }
    if(turnoutMastD!=nullptr){
        if (turnoutSignalMastD->addToPanel()) {
            if (isSignalMastOnPanel(turnoutMastD) &&
                (turnoutMastD!=getSignalMastFromName(layoutTurnout->getSignalDMastName()))) {
//                JOptionPane::showMessageDialog(setSignalsFrame,
//                    tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
//                        new Object[]{divergingField->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(turnoutSignalMastD->getText()));
                return;
            }
            else {
                removeSignalMastFromPanel(layoutTurnout->getSignalDMastName());
                SignalMastIcon* l = new SignalMastIcon(layoutEditor);
                l->setSignalMast(turnoutSignalMastD->getText());
                placingBlockD(l, turnoutSignalMastD->isRightSelected(), 0.0);
                removeAssignment(turnoutMastD);
                layoutTurnout->setSignalDMast(turnoutSignalMastD->getText());
                needRedraw = true;
            }
        }
        else {
            int assigned = isMastAssignedHere(turnoutMastD,layoutTurnout);
            if (assigned == NONE) {
                if (isSignalMastOnPanel(turnoutMastD) &&
                                    isSignalMastAssignedAnywhere(turnoutMastD) ) {
//                    JOptionPane::showMessageDialog(setSignalsFrame,
//                        tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
//                            new Object[]{turnoutSignalMastD->text()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                                    QMessageBox::critical(setSignalsFrame, tr("Error"), tr("Error - Cannot assign signal head \"{0}\" to this turnout\n                                                                       because it is already on the panel at a different place.").arg(turnoutSignalMastD->getText()));
return;
                }
                else {
                    removeSignalMastFromPanel(layoutTurnout->getSignalDMastName());
                    removeAssignment(turnoutMastD);
                    layoutTurnout->setSignalDMast(turnoutSignalMastD->getText());
                }
            }
            else if (assigned!=B1) {
// need to figure out what to do in this case.
            }
        }
    } else {
        removeSignalMastFromPanel(layoutTurnout->getSignalDMastName());
        layoutTurnout->setSignalDMast("");
    }

    // make sure this layout turnout is not linked to another
    layoutTurnout->setLinkType(LayoutTurnout::NO_LINK);
    layoutTurnout->setLinkedTurnoutName("");
    // finish up
    setSignalMastsAtTurnoutOpenFlag = false;
    setSignalMastsAtTurnoutFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}   //setSignalMastsDonePressed

/*private*/ bool LayoutEditorTools::getTurnoutMastInformation(){
 turnout = nullptr;
 layoutTurnout = nullptr;
 QString str = signalMastsTurnoutComboBox->currentText();
 if ((str == "") || str.isEmpty()) {
     JOptionPane::showMessageDialog(layoutEditor, tr("Error - No turnout name was entered. Please enter a turnout name or cancel."),
            tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);
     return false;
 }
 turnout = InstanceManager::turnoutManagerInstance()->getTurnout(str);
 if (turnout == nullptr) {
     JOptionPane::showMessageDialog(setSignalsAtTurnoutFrame,
             tr("Error - No turnout is defined for \"%1\". Please enter\na turnout name in the Turnout Table and on the panel.").arg(
                     str), tr("Error"),
             JOptionPane::ERROR_MESSAGE);
     return false;
 } else {
     QString uname = turnout->getUserName();
     if ((uname.isNull()) || uname.isEmpty()
             || uname != (str)) {
         signalMastsTurnoutComboBox->setSelectedItem(turnout);
     }
 }
 layoutTurnout = layoutEditor->getFinder()->findLayoutTurnoutByBean(turnout);

 if (layoutTurnout == nullptr) {
     JOptionPane::showMessageDialog(layoutEditor,
             tr("Error - Turnout \"%1\" is not drawn on the panel.\n Please enter the name of a drawn turnout.").arg(str),
                     tr("Error"),
             JOptionPane::ERROR_MESSAGE);
     return false;
 }
 return true;
}

/*private*/ void LayoutEditorTools::placingBlock(PositionableIcon* icon, bool right, double fromPoint) {
    if(qobject_cast<TrackSegment*>(layoutTurnout->getConnectA())!= nullptr)
    {
        TrackSegment* ts = (TrackSegment*) layoutTurnout->getConnectA();
        QPointF p = layoutTurnout->getCoordsA();
        QPointF endPoint;
        if(ts->getConnect1()==layoutTurnout){
            endPoint = layoutEditor->getCoords(ts->getConnect2(), ts->getType2());

        } else {
            endPoint = layoutEditor->getCoords(ts->getConnect1(), ts->getType1());
        }
        bool isEast = false;

        if (MathUtil::equals(endPoint.x(), p.x()))
        {
            log->debug("X in both is the same");
            if (endPoint.y() < p.y()) {
                log->debug("Y end point is less than our point");
                isEast = true;
            }
        } else if (endPoint.x() < p.x()) {
            log->debug("end X point is less than our point");
            isEast = true;
        }

        log->debug(QString("East set is ") + (isEast?"true":"false"));
        setIconOnPanel(ts, icon, isEast, QPoint(p.x(), p.y()), QPoint(endPoint.x(),endPoint.y()), right, fromPoint);
        return;
    }
}
/*private*/ void LayoutEditorTools::placingBlockB(PositionableIcon* icon, bool right, double fromPoint) {

    if(qobject_cast<TrackSegment*>(layoutTurnout->getConnectB())!= nullptr)
    {
        TrackSegment* t = (TrackSegment*) layoutTurnout->getConnectB();
        QPointF p = layoutTurnout->getCoordsB();

        QPointF end;
        if(t->getConnect1()==layoutTurnout){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }

        bool east = false;
        if(end.x()<p.x())
            east =true;
        setIconOnPanel(t, icon, east, QPoint(p.x(),p.y()), QPoint(end.x(),end.y()), right, fromPoint);
        return;
    }
}
/*private*/ void LayoutEditorTools::placingBlockC(PositionableIcon* icon, bool right, double fromPoint) {

    if(qobject_cast<TrackSegment*>(layoutTurnout->getConnectC())!= nullptr)
    {
        TrackSegment* t = (TrackSegment*) layoutTurnout->getConnectC();
        QPointF p = layoutTurnout->getCoordsC();

        QPointF end;
        if(t->getConnect1()==layoutTurnout){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }
        bool east = false;

        if(end.x()<p.x())
            east = true;
        setIconOnPanel(t, icon, east, QPoint(p.x(),p.y()), QPoint(end.x(),end.y()), right, fromPoint);
        return;
    }
}
/*private*/ void LayoutEditorTools::placingBlockD(PositionableIcon* icon, bool right, double fromPoint)
{
    //if(layoutTurnout->getConnectD() instanceof TrackSegment){
    if(qobject_cast<TrackSegment*>(layoutTurnout->getConnectD())!= nullptr)
    {
        TrackSegment* t = (TrackSegment*) layoutTurnout->getConnectD();
        QPointF p = layoutTurnout->getCoordsD();

        QPointF end;
        if(t->getConnect1()==layoutTurnout){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }

        //TrackSegment* t = boundary->getConnect2();
        bool east = false;
        if(end.x()<p.x())
            east = true;
        setIconOnPanel(t, icon, east, QPoint(p.x(),p.y()), QPoint(end.x(),end.y()), right, fromPoint);
        return;
    }
}

/*private*/ void LayoutEditorTools::setSignalMastsCancelPressed (JActionEvent* /*a*/) {
 setSignalMastsAtTurnoutOpenFlag = false;
 setSignalMastsAtTurnoutFrame->setVisible(false);
}

/*public*/ void LayoutEditorTools::setSignalMastsAtSlipFromMenu (LayoutSlip* slip, QVector<QString> blocks,
        JFrame* theFrame )
{
 layoutSlip = slip;
 layoutTurnout = slip;

 BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
 slipSignalBlockAComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockName()));
 slipSignalBlockBComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockBName()));
 slipSignalBlockCComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockCName()));
 slipSignalBlockDComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockDName()));

 slipBlocks = new QVector<QString>(4);
 for(int i = 0; i<blocks.size(); i++)
 {
  slipBlocks->replace(i, blocks[i]);
 }
 setSignalMastsAtLayoutSlip(theFrame);
 return;
}
/*public*/ void LayoutEditorTools::setSignalMastsAtLayoutSlip(JFrame* theFrame)
{
 signalFrame = theFrame;

 // Initialize if needed
 if (setSignalMastsAtLayoutSlipFrame == nullptr) {
  setSignalMastsAtLayoutSlipOpenFlag = false;

  slipSignalMastA = new BeanDetails("SignalMast",
          (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
  slipSignalMastB = new BeanDetails("SignalMast",
          (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
  slipSignalMastC = new BeanDetails("SignalMast",
          (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));
  slipSignalMastD = new BeanDetails("SignalMast",
          (SignalMastManager*)InstanceManager::getDefault("SignalMastManager"));

  //slipSignalMastA->getDetailsPanel().setBackground(new Color(255, 255, 200));
  slipSignalMastA->getDetailsPanel()->setStyleSheet("background: {color rgb(255,255,200)}");
  //slipSignalMastB->getDetailsPanel().setBackground(new Color(200, 255, 255));
  slipSignalMastB->getDetailsPanel()->setStyleSheet("background: {color rgb(200,255,255)}");
  //slipSignalMastC->getDetailsPanel().setBackground(new Color(200, 200, 255));
  slipSignalMastC->getDetailsPanel()->setStyleSheet("background: {color rgb(200,200,255)}");
  //slipSignalMastD->getDetailsPanel().setBackground(new Color(255, 200, 200));
  slipSignalMastD->getDetailsPanel()->setStyleSheet("background: {color rgb(255,200,255)}");

  setSignalMastsAtLayoutSlipFrame = new JmriJFrameX(tr("Set Signal Masts at a Slip"), false, true);
  oneFrameToRuleThemAll(setSignalMastsAtLayoutSlipFrame);
  setSignalMastsAtLayoutSlipFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
//         setSignalMastsAtLayoutSlipFrame.addHelpMenu("package.jmri.jmrit.display.SetSignalsAtLayoutSlip", true);
  setSignalMastsAtLayoutSlipFrame->setLocation(70, 30);
  QFont font;
  font.setPointSize(8);
  setSignalMastsAtLayoutSlipFrame->setFont(font);//  QWidget* theContentPane = setSignalMastsAtLayoutSlipFrame->getContentPane();
//  theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
  QScrollArea* scrollarea = new QScrollArea();
  QWidget* theContentPane = new QWidget();
  theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
  scrollarea->setWidget(theContentPane);
  scrollarea->setWidgetResizable(true);
  setSignalMastsAtLayoutSlipFrame->setCentralWidget(scrollarea);

  JPanel* panel11A = new JPanel(new FlowLayout());
  //note: this is just placeholder text; real text is set below
  slipSignalBlockANameLabel = new JLabel(" A ");
  panel11A->layout()->addWidget(slipSignalBlockANameLabel);
  panel11A->layout()->addWidget(slipSignalBlockAComboBox);
  slipSignalBlockAComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11A);

  JPanel* panel11B = new JPanel(new FlowLayout());
  //note: this is just placeholder text; real text is set below
  slipSignalBlockBNameLabel = new JLabel(" B ");
  panel11B->layout()->addWidget(slipSignalBlockBNameLabel);
  panel11B->layout()->addWidget(slipSignalBlockBComboBox);
  slipSignalBlockBComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11B);

  JPanel* panel11C = new JPanel(new FlowLayout());
  //note: this is just placeholder text; real text is set below
  slipSignalBlockCNameLabel = new JLabel(" C ");
  panel11C->layout()->addWidget(slipSignalBlockCNameLabel);
  panel11C->layout()->addWidget(slipSignalBlockCComboBox);
  slipSignalBlockCComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11C);

  JPanel* panel11D = new JPanel(new FlowLayout());
  //note: this is just placeholder text; real text is set below
  slipSignalBlockDNameLabel = new JLabel(" D ");
  panel11D->layout()->addWidget(slipSignalBlockDNameLabel);
  panel11D->layout()->addWidget(slipSignalBlockDComboBox);
  slipSignalBlockDComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11D);

  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Mast"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedSlipSignalMasts = new QPushButton(tr("GetSaved")));
//        getSavedSlipSignalMasts->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    slipSignalMastsGetSaved(e);
//                }
//            });
  connect(getSavedSlipSignalMasts, SIGNAL(clicked()), this, SLOT(slipSignalMastsGetSaved()));
  getSavedSlipSignalMasts->setToolTip("Click to retrieve signal heads previously stored.");
  theContentPane->layout()->addWidget(panel2);

  //slipSignalMastA->getDetailsPanel()->setBackground(new Color(255,255,200));
  slipSignalMastA->getDetailsPanel()->setStyleSheet("QWidget {background: rgb(255,255,200)");

  //slipSignalMastB->getDetailsPanel()->setBackground(new Color(200,255,255));
  slipSignalMastB->getDetailsPanel()->setStyleSheet("QWidget {background: rgb(200,255,255)");

  //slipSignalMastC.getDetailsPanel()->setBackground(new Color(200,200,255));
  slipSignalMastC->getDetailsPanel()->setStyleSheet("QWidget {background: rgb(200,200,255)");

  //slipSignalMastD.getDetailsPanel()->setBackground(new Color(255,200,200));
  slipSignalMastD->getDetailsPanel()->setStyleSheet("QWidget {background: rgb(255,200,200)");

  signalMastLayoutSlipPanel->setLayout(signalMastLayoutSlipPanelLayout =new QGridLayout(/*0,2*/));

  slipSignalMastA->setBoundaryLabel(slipBlocks->at(0));
  slipSignalMastB->setBoundaryLabel(slipBlocks->at(1));
  slipSignalMastC->setBoundaryLabel(slipBlocks->at(2));
  slipSignalMastD->setBoundaryLabel(slipBlocks->at(3));

  if(slipBlocks->at(0)!=nullptr)
      signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastA->getDetailsPanel(),0,0);
  if(slipBlocks->at(1)!=nullptr)
      signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastB->getDetailsPanel(),0,1);
  if(slipBlocks->at(2)!=nullptr)
      signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastC->getDetailsPanel(),1,0);
  if(slipBlocks->at(3)!=nullptr)
      signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastD->getDetailsPanel(),1,1);

  theContentPane->layout()->addWidget(signalMastLayoutSlipPanel);
  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());

  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setSlipSignalMastsDone = new QPushButton(tr("Done")));
//        setSlipSignalMastsDone->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setSlipSignalMastsDonePressed(e);
//            }
//        });
  connect(setSlipSignalMastsDone, SIGNAL(clicked()), this, SLOT(setSlipSignalMastsDonePressed()));
  setSlipSignalMastsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
  panel6->layout()->addWidget(setSlipSignalMastsCancel = new QPushButton(tr("Cancel")));
//        setSlipSignalMastsCancel->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setSlipSignalMastsCancelPressed(e);
//            }
//        });
  connect(setSlipSignalMastsCancel, SIGNAL(clicked()), this, SLOT(setSlipSignalMastsCancelPressed()));
  setSlipSignalMastsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  theContentPane->layout()->addWidget(panel6);
//        setSignalMastsAtLayoutSlipFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                setSlipSignalMastsCancelPressed(nullptr);
//            }
//        });
  setSignalMastsAtLayoutSlipFrame->addWindowListener(new SMSWindowListener(this));
 }
  //Unhide any excluded masts
 slipSignalMastA->getCombo()->setExcludedItems(QSet<NamedBean*>());
 slipSignalMastB->getCombo()->setExcludedItems(QSet<NamedBean*>());
 slipSignalMastC->getCombo()->setExcludedItems(QSet<NamedBean*>());
 slipSignalMastD->getCombo()->setExcludedItems(QSet<NamedBean*>());
 //signalMastLayoutSlipPanel.removeAll();
 QList<QWidget*> list = signalMastLayoutSlipPanel->findChildren<QWidget*>();
 foreach(QWidget* w, list)
 {
  signalMastLayoutSlipPanel->layout()->removeWidget(w);
  delete w;
 }

 slipSignalBlockAComboBox->setVisible(!setSignalMastsAtLayoutSlipFromMenuFlag);
 slipSignalBlockBComboBox->setVisible(!setSignalMastsAtLayoutSlipFromMenuFlag);
 slipSignalBlockCComboBox->setVisible(!setSignalMastsAtLayoutSlipFromMenuFlag);
 slipSignalBlockDComboBox->setVisible(!setSignalMastsAtLayoutSlipFromMenuFlag);

 if (setSignalMastsAtLayoutSlipFromMenuFlag) {
     slipSignalBlockANameLabel->setText(tr("Block") + " A "
             + tr("Name")
             + " " + layoutSlip->getBlockName());
     slipSignalBlockBNameLabel->setText(tr("Block") + " B "
             + tr("Name")
             + " " + layoutSlip->getBlockBName());
     slipSignalBlockCNameLabel->setText(tr("Block") + " C "
             + tr("Name")
             + " " + layoutSlip->getBlockCName());
     slipSignalBlockDNameLabel->setText(tr("Block") + " D "
             + tr("Name")
             + " " + layoutSlip->getBlockDName());
     refreshSignalMastAtSlipComboBox();
 } else {
     slipSignalBlockANameLabel->setText(tr("Block") + " A "
             + tr("Name"));
     slipSignalBlockBNameLabel->setText(tr("Block") + " B "
             + tr("Name"));
     slipSignalBlockCNameLabel->setText(tr("Block") + " C "
             + tr("Name"));
     slipSignalBlockDNameLabel->setText(tr("Block") + " D "
             + tr("Name"));
 }

 if (!setSignalMastsAtLayoutSlipOpenFlag) {
     setSignalMastsAtLayoutSlipFrame->resize(QSize());
     setSignalMastsAtLayoutSlipFrame->pack();
     setSignalMastsAtLayoutSlipOpenFlag = true;
 }
 setSignalMastsAtLayoutSlipFrame->setVisible(true);
}


void LayoutEditorTools::refreshSignalMastAtSlipComboBox(){
 slipSignalMastsGetSaved(nullptr);
 createListUsedSignalMasts();
 usedMasts.removeOne(slipSignalMastA->getBean());
 usedMasts.removeOne(slipSignalMastB->getBean());
 usedMasts.removeOne(slipSignalMastC->getBean());
 usedMasts.removeOne(slipSignalMastD->getBean());
 slipSignalMastA->getCombo()->setExcludedItems(usedMasts.toSet());
 slipSignalMastB->getCombo()->setExcludedItems(usedMasts.toSet());
 slipSignalMastC->getCombo()->setExcludedItems(usedMasts.toSet());
 slipSignalMastD->getCombo()->setExcludedItems(usedMasts.toSet());
}

/*private*/ void LayoutEditorTools::slipSignalMastsGetSaved (JActionEvent* /*a*/) {
 if ( !getSlipMastInformation() ) return;
 slipBlocks = layoutSlip->getBlockBoundaries();
 slipSignalMastA->setTextField(layoutSlip->getSignalAMastName());
 slipSignalMastB->setTextField(layoutSlip->getSignalBMastName());
 slipSignalMastC->setTextField(layoutSlip->getSignalCMastName());
 slipSignalMastD->setTextField(layoutSlip->getSignalDMastName());

 slipSignalMastA->setBoundaryLabel(slipBlocks->at(0));
 slipSignalMastB->setBoundaryLabel(slipBlocks->at(1));
 slipSignalMastC->setBoundaryLabel(slipBlocks->at(2));
 slipSignalMastD->setBoundaryLabel(slipBlocks->at(3));

 bool boundaryFlag = false;
 signalMastLayoutSlipPanel->layout()->removeWidget(slipSignalMastA->getDetailsPanel());
 signalMastLayoutSlipPanel->layout()->removeWidget(slipSignalMastB->getDetailsPanel());
 signalMastLayoutSlipPanel->layout()->removeWidget(slipSignalMastC->getDetailsPanel());
 signalMastLayoutSlipPanel->layout()->removeWidget(slipSignalMastD->getDetailsPanel());
 if(slipBlocks->at(0)!=nullptr){
     signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastA->getDetailsPanel());
     boundaryFlag = true;
 }
 if(slipBlocks->at(1)!=nullptr){
     signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastB->getDetailsPanel());
     boundaryFlag = true;
 }
 if(slipBlocks->at(2)!=nullptr){
     signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastC->getDetailsPanel());
     boundaryFlag = true;
 }
 if(slipBlocks->at(3)!=nullptr){
     signalMastLayoutSlipPanelLayout->addWidget(slipSignalMastD->getDetailsPanel());
     boundaryFlag = true;
 }
 if (!boundaryFlag){
        JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame, "There are no block boundaries on this level crossing\nIt is therefore not possible to add Signal Masts to it");
 }
 setSignalMastsAtLayoutSlipFrame->resize(QSize());
 setSignalMastsAtLayoutSlipFrame->adjustSize();
}

/*private*/ bool LayoutEditorTools::getSlipMastInformation() {
    if (!setSignalMastsAtLayoutSlipFromMenuFlag) {
        layoutSlip = NULL;
        QList<LayoutSlip*> layoutSlips = layoutEditor->getLayoutSlips();
        if (layoutSlips.size()<=0) {
            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
                tr("Error - There are no level crossings on your panel\nPlease add a level crossing or cancel."),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
            return false;
        }
        else if (layoutSlips.size()==1) {
            layoutSlip = layoutSlips.at(0);
        }
        else {
            LayoutBlock*slipBlockA = NULL;
            //LayoutBlock*slipBlockC = NULL;
            slipBlockA = getBlockFromEntry(xingBlockACComboBox);
            if (slipBlockA==nullptr) return false;

            LayoutSlip* x = NULL;
            int foundCount = 0;
            // make two block tests first
            for (LayoutSlip* x : layoutEditor->getLayoutSlips()) {
                LayoutBlock* xA = NULL;
                LayoutBlock* xB = NULL;
                LayoutBlock* xC = NULL;
                LayoutBlock* xD = NULL;
                LayoutBlock* xAC = x->getLayoutBlock();
                if (x->getConnectA()!=nullptr) xA = ((TrackSegment*)x->getConnectA())->getLayoutBlock();
                if (x->getConnectB()!=nullptr) xB = ((TrackSegment*)x->getConnectB())->getLayoutBlock();
                if (x->getConnectC()!=nullptr) xC = ((TrackSegment*)x->getConnectC())->getLayoutBlock();
                if (x->getConnectD()!=nullptr) xD = ((TrackSegment*)x->getConnectD())->getLayoutBlock();
                if ( ( (xA!=nullptr) && (xC!=nullptr) && ( (xA==slipBlockA) ||
                        (xC==slipBlockA) ) ) ||
                        ( (xB!=nullptr) && (xD!=nullptr) && ( (xB==slipBlockA) ||
                        (xD==slipBlockA) ) ) ) {
                    layoutSlip = x;
                    foundCount ++;
                }
                else if ( (xAC!=nullptr) && ( xAC==slipBlockA
                             )) {
                    layoutSlip = x;
                    foundCount ++;
                }
            }
            if (foundCount==0) {
                // try one block test
                for (LayoutSlip* x : layoutEditor->getLayoutSlips()) {
                    if (slipBlockA == x->getLayoutBlock())
                    {
                        layoutSlip = x;
                        foundCount ++;
                    }
                }
            }
            if (foundCount>1) {
                JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
                        tr("Error - The entered block names match \"%1\" level crossings.\nPlease enter block names that match only one level crossing.").arg(
                            " "+QString::number(foundCount)+" "),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
            }
            if (layoutSlip==nullptr) {
                JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
                            tr("Error - No level crossing matches the block(s)\nentered. Please try again or cancel."),
                                    tr("Error"),JOptionPane::ERROR_MESSAGE);
            }
        }
    }
    return true;
}

/*private*/ void LayoutEditorTools::setSlipSignalMastsCancelPressed (JActionEvent* /*a*/) {
 setSignalMastsAtLayoutSlipOpenFlag = false;
 setSignalMastsAtLayoutSlipFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setSlipSignalMastsDonePressed (JActionEvent* /*a*/)
{
 if ( !getSlipMastInformation() ) return;
 SignalMast* aMast = getSignalMastFromEntry(slipSignalMastA->getText(),false,setSignalMastsAtLayoutSlipFrame);
 SignalMast* bMast = getSignalMastFromEntry(slipSignalMastB->getText(),false,setSignalMastsAtLayoutSlipFrame);
 SignalMast* cMast = getSignalMastFromEntry(slipSignalMastC->getText(),false,setSignalMastsAtLayoutSlipFrame);
 SignalMast* dMast = getSignalMastFromEntry(slipSignalMastD->getText(),false,setSignalMastsAtLayoutSlipFrame);
 // place or update signals as requested
 if ( (aMast!=nullptr) && slipSignalMastA->addToPanel() )
 {
     if (isSignalMastOnPanel(aMast) &&
             (aMast!=getSignalMastFromName(layoutSlip->getSignalAMastName())) )
     {
            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    slipSignalMastA->getText()),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalAMastName());
         SignalMastIcon* l = new SignalMastIcon(layoutEditor);
         l->setSignalMast(slipSignalMastA->getText());
         placingBlock(l, slipSignalMastA->isRightSelected(), 0.0);
         removeAssignment(aMast);
         layoutSlip->setSignalAMast(slipSignalMastA->getText());
         needRedraw = true;
     }
 }
 else if ( (aMast!=nullptr) &&
         (aMast!=getSignalMastFromName(layoutSlip->getSignalAMastName())) &&
         (aMast!=getSignalMastFromName(layoutSlip->getSignalBMastName())) &&
         (aMast!=getSignalMastFromName(layoutSlip->getSignalCMastName())) &&
         (aMast!=getSignalMastFromName(layoutSlip->getSignalDMastName())) ) {
     if (isSignalMastOnPanel(aMast)) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{slipSignalMastA->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(slipSignalMastA->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalAMastName());
         removeAssignment(aMast);
         layoutSlip->setSignalAMast(slipSignalMastA->getText());
     }
 }
 else if ( (aMast!=nullptr) &&
         ( (aMast==getSignalMastFromName(layoutSlip->getSignalBMastName())) ||
             (aMast==getSignalMastFromName(layoutSlip->getSignalCMastName())) ||
             (aMast==getSignalMastFromName(layoutSlip->getSignalDMastName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (aMast==nullptr) {
     removeSignalMastFromPanel(layoutSlip->getSignalAMastName());
     layoutSlip->setSignalAMast("");
 }
 if ( (bMast!=nullptr) && slipSignalMastB->addToPanel()) {
     if (isSignalMastOnPanel(bMast) &&
             (bMast!=getSignalMastFromName(layoutSlip->getSignalBMastName()))) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{slipSignalMastB->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
                                       QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(slipSignalMastB->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalBMastName());
         SignalMastIcon* l = new SignalMastIcon(layoutEditor);
         l->setSignalMast(slipSignalMastB->getText());
         placingBlockB(l, slipSignalMastB->isRightSelected(), 0.0);
         removeAssignment(bMast);
         layoutSlip->setSignalBMast(slipSignalMastB->getText());
         needRedraw = true;
     }
 }
 else if ( (bMast!=nullptr) &&
         (bMast!=getSignalMastFromName(layoutSlip->getSignalAMastName())) &&
         (bMast!=getSignalMastFromName(layoutSlip->getSignalBMastName())) &&
         (bMast!=getSignalMastFromName(layoutSlip->getSignalCMastName())) &&
         (bMast!=getSignalMastFromName(layoutSlip->getSignalDMastName())) ) {
     if (isSignalMastOnPanel(bMast)) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{slipSignalMastB->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(slipSignalMastB->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalBMastName());
         removeAssignment(bMast);
         layoutSlip->setSignalBMast(slipSignalMastB->getText());
     }
 }
 else if ( (bMast!=nullptr) &&
         ( (bMast==getSignalMastFromName(layoutSlip->getSignalAMastName())) ||
             (bMast==getSignalMastFromName(layoutSlip->getSignalCMastName())) ||
             (bMast==getSignalMastFromName(layoutSlip->getSignalDMastName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (bMast==nullptr) {
     removeSignalMastFromPanel(layoutSlip->getSignalBMastName());
     layoutSlip->setSignalBMast("");
 }
 if ( (cMast!=nullptr) && slipSignalMastC->addToPanel() ) {
     if (isSignalMastOnPanel(cMast) &&
             (cMast!=getSignalMastFromName(layoutSlip->getSignalCMastName())) ) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{slipSignalMastC->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(slipSignalMastC->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalCMastName());
         SignalMastIcon* l = new SignalMastIcon(layoutEditor);
         l->setSignalMast(slipSignalMastC->getText());
         placingBlockC(l, slipSignalMastA->isRightSelected(), 0.0);
         removeAssignment(cMast);
         layoutSlip->setSignalCMast(slipSignalMastC->getText());
         needRedraw = true;
     }
 }
 else if ( (cMast!=nullptr) &&
         (cMast!=getSignalMastFromName(layoutSlip->getSignalAMastName())) &&
         (cMast!=getSignalMastFromName(layoutSlip->getSignalBMastName())) &&
         (cMast!=getSignalMastFromName(layoutSlip->getSignalCMastName())) &&
         (cMast!=getSignalMastFromName(layoutSlip->getSignalDMastName())) ) {
     if (isSignalMastOnPanel(cMast)) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{slipSignalMastC->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(slipSignalMastC->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalCMastName());
         removeAssignment(cMast);
         layoutSlip->setSignalCMast(slipSignalMastC->getText());
     }
 }
 else if ( (cMast!=nullptr) &&
         ( (cMast==getSignalMastFromName(layoutSlip->getSignalBMastName())) ||
             (cMast==getSignalMastFromName(layoutSlip->getSignalAMastName())) ||
             (cMast==getSignalMastFromName(layoutSlip->getSignalDMastName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (cMast==nullptr) {
     removeSignalMastFromPanel(layoutSlip->getSignalCMastName());
     layoutSlip->setSignalCMast("");
 }
 if ( (dMast!=nullptr) && slipSignalMastD->addToPanel() ) {
     if (isSignalMastOnPanel(dMast) &&
             (dMast!=getSignalMastFromName(layoutSlip->getSignalDMastName())) ) {
      //            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
      //                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
      //                    new Object[]{slipSignalMastD->text()}),
      //                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(slipSignalMastD->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalDMastName());
         SignalMastIcon* l = new SignalMastIcon(layoutEditor);
         l->setSignalMast(slipSignalMastD->getText());
         placingBlockD(l, slipSignalMastD->isRightSelected(), 0.0);
         removeAssignment(dMast);
         layoutSlip->setSignalDMast(slipSignalMastD->getText());
         needRedraw = true;
     }
 }
 else if ( (dMast!=nullptr) &&
         (dMast!=getSignalMastFromName(layoutSlip->getSignalAMastName())) &&
         (dMast!=getSignalMastFromName(layoutSlip->getSignalBMastName())) &&
         (dMast!=getSignalMastFromName(layoutSlip->getSignalCMastName())) &&
         (dMast!=getSignalMastFromName(layoutSlip->getSignalDMastName())) ) {
     if (isSignalMastOnPanel(dMast)) {
//            JOptionPane::showMessageDialog(setSignalMastsAtLayoutSlipFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{slipSignalMastD->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(slipSignalMastD->getText()));
         return;
     }
     else {
         removeSignalMastFromPanel(layoutSlip->getSignalDMastName());
         removeAssignment(dMast);
         layoutSlip->setSignalDMast(slipSignalMastD->getText());
     }
 }
 else if ( (dMast!=nullptr) &&
         ( (dMast==getSignalMastFromName(layoutSlip->getSignalBMastName())) ||
             (dMast==getSignalMastFromName(layoutSlip->getSignalCMastName())) ||
             (dMast==getSignalMastFromName(layoutSlip->getSignalAMastName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (dMast==nullptr) {
     removeSignalMastFromPanel(layoutSlip->getSignalDMastName());
     layoutSlip->setSignalDMast("");
 }
 // setup logic if requested
 // finish up
 setSensorsAtSlipOpenFlag = false;
 setSignalMastsAtLayoutSlipFrame->setVisible(false);
 if (needRedraw) {
     layoutEditor->redrawPanel();
     needRedraw = false;
     layoutEditor->setDirty();
 }
}


// display dialog for Set Signals at Level Crossing tool
/*public*/ void LayoutEditorTools::setSignalMastsAtLevelXingFromMenu (LevelXing* xing, QVector<QString>* blocks, JFrame* theFrame )
{
  xingMastFromMenu = true;
  levelXing = xing;
  BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
  xingBlockACComboBox->setSelectedItem(bm->getBlock(levelXing->getBlockNameAC()));
  xingBlockBDComboBox->setSelectedItem(bm->getBlock(levelXing->getBlockNameBD()));
  xingBlocks = new QVector<QString>(4);
  for (int i = 0; i < blocks->length(); i++) {
      xingBlocks->replace(i, blocks->at(i));
  }
  setSignalMastsAtLevelXingFromMenuFlag = true;
  setSignalMastsAtLevelXing(theFrame);
  setSignalMastsAtLevelXingFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalMastsAtLevelXing(JFrame* theFrame)
{
 signalFrame = theFrame;

 // Initialize if needed
 if (setSignalMastsAtLevelXingFrame == nullptr)
 {
  setSignalMastsAtLevelXingOpenFlag = false;

  xingSignalMastA = new BeanDetails("Signal Mast", (Manager*) InstanceManager::getDefault("SignalMastManager"));
  xingSignalMastB = new BeanDetails("Signal Mast",(Manager*) InstanceManager::getDefault("SignalMastManager"));
  xingSignalMastC = new BeanDetails("Signal Mast",(Manager*) InstanceManager::getDefault("SignalMastManager"));
  xingSignalMastD = new BeanDetails("Signal Mast",(Manager*) InstanceManager::getDefault("SignalMastManager"));

  setSignalsAtLevelXingFrame = new JmriJFrameX( tr("SignalMastsAtLevelXing"), false, true );
  oneFrameToRuleThemAll(setSignalMastsAtLevelXingFrame);
  setSignalsAtLevelXingFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtLevelXing", true);
  setSignalsAtLevelXingFrame->setLocation(70,30);
  QWidget* theContentPane = new QWidget;
  /*setSignalsAtLevelXingFrame.getContentPane();*/
  setSignalsAtLevelXingFrame->setCentralWidget(theContentPane);
  QVBoxLayout* centralWidgetLayout;
  theContentPane->setLayout(centralWidgetLayout = new QVBoxLayout); //(theContentPane, BoxLayout.Y_AXIS));

  QWidget* panel11 = new QWidget();
  panel11->setLayout(new QHBoxLayout());
  if (xingMastFromMenu)
  {
   QLabel* blockANameLabel = new QLabel( tr("BlockAtA")+" "+
                  tr("Name")+" : "+levelXing->getBlockNameAC());
   panel11->layout()->addWidget(blockANameLabel);
   xingSignalMastA->setTextField(levelXing->getSignalAMastName());
   xingSignalMastB->setTextField(levelXing->getSignalBMastName());
   xingSignalMastC->setTextField(levelXing->getSignalCMastName());
   xingSignalMastD->setTextField(levelXing->getSignalDMastName());
  }
  else
  {
   QLabel* xingSignalBlockACNameLabel = new QLabel( tr("BlockAtA")+" "+ tr("Name")+" : ");
   panel11->layout()->addWidget(xingSignalBlockACNameLabel);
   panel11->layout()->addWidget(xingBlockACComboBox);
   xingBlockACComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  }
  centralWidgetLayout->addWidget(panel11);
  QWidget* panel12 = new QWidget();
  panel12->setLayout(new QHBoxLayout());
  if (xingMastFromMenu)
  {
   QLabel* blockCNameLabel = new QLabel( tr("BlockAtC")+" "+ tr("Name")+" : "+levelXing->getBlockNameBD());

   panel12->layout()->addWidget(blockCNameLabel);
  }
  else
  {
   QLabel* xingSignalBlockBDNameLabel = new QLabel( tr("BlockAtC")+" "+tr("Name")+" : ");
   panel12->layout()->addWidget(xingSignalBlockBDNameLabel);
   panel12->layout()->addWidget(xingBlockBDComboBox);
   xingBlockBDComboBox->setToolTip(tr("Enter name of one block where signals are needed at block boundary."));
  }
  centralWidgetLayout->addWidget(panel12);
  centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Signal Mast"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedXingSignalMasts = new QPushButton(tr("Get Saved")));
//        getSavedXingSignalMasts->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    xingSignalMastsGetSaved(e);
//                }
//            });
  connect(getSavedXingSignalMasts, SIGNAL(clicked()), this, SLOT(xingSignalMastsGetSaved()));
  getSavedXingSignalMasts->setToolTip("Click to retrieve signal heads previously stored.");
  centralWidgetLayout->addWidget(panel2);

  //xingSignalMastA.getDetailsPanel()->setBackground(new Color(255,255,200));
  xingSignalMastA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");

  //xingSignalMastB.getDetailsPanel()->setBackground(new Color(200,255,255));
  xingSignalMastB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");

  //xingSignalMastC.getDetailsPanel()->setBackground(new Color(200,200,255));
  xingSignalMastC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,255)}");

  //xingSignalMastD.getDetailsPanel()->setBackground(new Color(255,200,200));
  xingSignalMastD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");


  signalMastLevelXingPanel->setLayout(signalMastLevelXingPanelLayout = new QGridLayout(/*0,2*/));

  xingSignalMastA->setBoundaryLabel(xingBlocks->at(0));
  xingSignalMastB->setBoundaryLabel(xingBlocks->at(1));
  xingSignalMastC->setBoundaryLabel(xingBlocks->at(2));
  xingSignalMastD->setBoundaryLabel(xingBlocks->at(3));

  if(xingBlocks->at(0)!=nullptr)
      signalMastLevelXingPanelLayout->addWidget(xingSignalMastA->getDetailsPanel(),0,0);
  if(xingBlocks->at(1)!=nullptr)
      signalMastLevelXingPanelLayout->addWidget(xingSignalMastB->getDetailsPanel(),0,1);
  if(xingBlocks->at(2)!=nullptr)
      signalMastLevelXingPanelLayout->addWidget(xingSignalMastC->getDetailsPanel(),1, 0);
  if(xingBlocks->at(3)!=nullptr)
      signalMastLevelXingPanelLayout->addWidget(xingSignalMastD->getDetailsPanel(),1,1);

  centralWidgetLayout->addWidget(signalMastLevelXingPanel);
  centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());

  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setXingSignalMastsDone = new QPushButton(tr("Done")));
//  setXingSignalMastsDone->layout()->addWidgetActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          setXingSignalMastsDonePressed(e);
//      }
//  });
  connect(setXingSignalMastsDone, SIGNAL(clicked()), this, SLOT(setXingSignalMastsDonePressed()));
  setXingSignalMastsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
  panel6->layout()->addWidget(setXingSignalMastsCancel = new QPushButton(tr("Cancel")));
//  setXingSignalMastsCancel->layout()->addWidgetActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          setXingSignalMastsCancelPressed(e);
//      }
//  });
  connect(setXingSignalMastsCancel, SIGNAL(clicked()), this, SLOT(setXingSignalMastsCancelPressed()));
  setXingSignalMastsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  centralWidgetLayout->addWidget(panel6);
//  setSignalsAtLevelXingFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//      /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//          setXingSignalMastsCancelPressed(nullptr);
//      }
//  });
  setSignalsAtLevelXingFrame->addWindowListener(new XSMSWindowListener(this));
  if (xingMastFromMenu) xingSignalMastsGetSaved(nullptr);
 }
 refreshSignalMastAtXingComboBox();
 setSignalsAtLevelXingFrame->setMinimumSize(QSize());
 setSignalsAtLevelXingFrame->adjustSize();
 setSignalsAtLevelXingFrame->setVisible(true);
 setSignalMastsAtLevelXingOpenFlag = true;
}
void LayoutEditorTools::refreshSignalMastAtXingComboBox()
{
 xingSignalMastsGetSaved(nullptr);
 createListUsedSignalMasts();
 usedMasts.removeOne(xingSignalMastA->getBean());
 usedMasts.removeOne(xingSignalMastB->getBean());
 usedMasts.removeOne(xingSignalMastC->getBean());
 usedMasts.removeOne(xingSignalMastD->getBean());
 xingSignalMastA->getCombo()->setExcludedItems(usedMasts.toSet());
 xingSignalMastB->getCombo()->setExcludedItems(usedMasts.toSet());
 xingSignalMastC->getCombo()->setExcludedItems(usedMasts.toSet());
 xingSignalMastD->getCombo()->setExcludedItems(usedMasts.toSet());
}

/*private*/ void LayoutEditorTools::xingSignalMastsGetSaved (JActionEvent* /*a*/)
{
 if ( !getLevelCrossingMastInformation() ) return;
 xingBlocks = levelXing->getBlockBoundaries();
 xingSignalMastA->setTextField(levelXing->getSignalAMastName());
 xingSignalMastB->setTextField(levelXing->getSignalBMastName());
 xingSignalMastC->setTextField(levelXing->getSignalCMastName());
 xingSignalMastD->setTextField(levelXing->getSignalDMastName());

 xingSignalMastA->setBoundaryLabel(xingBlocks->at(0));
 xingSignalMastB->setBoundaryLabel(xingBlocks->at(1));
 xingSignalMastC->setBoundaryLabel(xingBlocks->at(2));
 xingSignalMastD->setBoundaryLabel(xingBlocks->at(3));

 bool boundary = false;
 signalMastLevelXingPanel->layout()->removeWidget(xingSignalMastA->getDetailsPanel());
 signalMastLevelXingPanel->layout()->removeWidget(xingSignalMastB->getDetailsPanel());
 signalMastLevelXingPanel->layout()->removeWidget(xingSignalMastC->getDetailsPanel());
 signalMastLevelXingPanel->layout()->removeWidget(xingSignalMastD->getDetailsPanel());
 if(xingBlocks->at(0)!=nullptr){
     signalMastLevelXingPanelLayout->addWidget(xingSignalMastA->getDetailsPanel());
     boundary = true;
 }
 if(xingBlocks->at(1)!=nullptr){
     signalMastLevelXingPanelLayout->addWidget(xingSignalMastB->getDetailsPanel());
     boundary = true;
 }
 if(xingBlocks->at(2)!=nullptr){
     signalMastLevelXingPanelLayout->addWidget(xingSignalMastC->getDetailsPanel());
     boundary = true;
 }
 if(xingBlocks->at(3)!=nullptr){
     signalMastLevelXingPanelLayout->addWidget(xingSignalMastD->getDetailsPanel());
     boundary = true;
 }
 if (!boundary){
//        JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame, "There are no block boundaries on this level crossing\nIt is therefore not possible to add Signal Masts to it");
  QMessageBox::information(setSignalsAtLevelXingFrame, tr("Information"), tr("There are no block boundaries on this level crossing\nIt is therefore not possible to add Signal Masts to it"));
 }
 setSignalsAtLevelXingFrame->setMinimumSize(QSize());
 setSignalsAtLevelXingFrame->adjustSize();
}
/*private*/ bool LayoutEditorTools::getLevelCrossingMastInformation()
{
 if (!xingMastFromMenu)
 {
  levelXing = NULL;
  QList<LevelXing*> levelXings = layoutEditor->getLevelXings();
  if (levelXings.size()<=0)
  {
      JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
          tr("Error - There are no level crossings on your panel\nPlease add a level crossing or cancel."),
                      tr("Error"),JOptionPane::ERROR_MESSAGE);
      return false;
  }
  else if(levelXings.size()==1)
  {
   levelXing = levelXings.at(0);
  }
  else
  {
   LayoutBlock* xingBlockA = NULL;
   LayoutBlock* xingBlockC = NULL;
   xingBlockA = getBlockFromEntry(xingBlockACComboBox);
   if (xingBlockA==nullptr)
    return false;

   QString theBlockName = xingBlockBDComboBox->getSelectedItemDisplayName();
   if ((!theBlockName.isNull()) && !theBlockName.isEmpty()) {
       xingBlockC = getBlockFromEntry(xingBlockBDComboBox);
       if (xingBlockC == nullptr) {
           return false;
       }
   }

   int foundCount = 0;
   // make two block tests first
   if (xingBlockC!=nullptr)
   {
for (LevelXing* x : layoutEditor->getLevelXings()) {
     LayoutBlock* xA = NULL;
     LayoutBlock* xB = NULL;
     LayoutBlock* xC = NULL;
     LayoutBlock* xD = NULL;
     LayoutBlock* xAC = x->getLayoutBlockAC();
     LayoutBlock* xBD = x->getLayoutBlockBD();
     if (x->getConnectA()!=nullptr)
      xA = ((TrackSegment*)x->getConnectA())->getLayoutBlock();
     if (x->getConnectB()!=nullptr)
      xB = ((TrackSegment*)x->getConnectB())->getLayoutBlock();
     if (x->getConnectC()!=nullptr)
      xC = ((TrackSegment*)x->getConnectC())->getLayoutBlock();
     if (x->getConnectD()!=nullptr)
      xD = ((TrackSegment*)x->getConnectD())->getLayoutBlock();
     if ( ( (xA!=nullptr) && (xC!=nullptr) && ( ((xA==xingBlockA)&&(xC==xingBlockC)) ||
             ((xA==xingBlockC)&&(xC==xingBlockA)) ) ) ||
             ( (xB!=nullptr) && (xD!=nullptr) && ( ((xB==xingBlockA)&&(xD==xingBlockC)) ||
             ((xB==xingBlockC)&&(xD==xingBlockA)) ) ) )
     {
      levelXing = x;
      foundCount ++;
     }
     else if ( (xAC!=nullptr) && (xBD!=nullptr) && ( ((xAC==xingBlockA) && (xBD==xingBlockC)) ||
                 ((xAC==xingBlockC) && (xBD==xingBlockA)) ) )
     {
      levelXing = x;
      foundCount ++;
     }
    }
   }
   if (foundCount==0)
   {
    // try one block test
    for (LevelXing* x : layoutEditor->getLevelXings()) {
     if ((xingBlockA == x->getLayoutBlockAC()) || (xingBlockA == x->getLayoutBlockBD()))
     {
      levelXing = x;
      foundCount ++;
     }
    }
   }
   if (foundCount>1)
   {
//       JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//               tr("Error - The entered block names match \"%1\" level crossings.\nPlease enter block names that match only one level crossing."),
//                   new Object[]{" "+foundCount+" "}),
//                       tr("Error"),JOptionPane::ERROR_MESSAGE);
    QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Error"), tr("Error - The entered block names match \"%1\" level crossings.\n           Please enter block names that match only one level crossing.").arg(foundCount)); return false;
    return false;
   }
   if (levelXing==nullptr)
   {
//       JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                   tr("Error - No level crossing matches the block(s)\nentered. Please try again or cancel."),
//                           tr("Error"),JOptionPane::ERROR_MESSAGE);
    QMessageBox::critical(setSignalsAtLevelXingFrame, tr("Error"), tr("Error - No level crossing matches the block(s)\n                            entered. Please try again or cancel."));return false;
    return false;
   }
  }
 }

 return true;
}

/*private*/ void LayoutEditorTools::setXingSignalMastsCancelPressed (JActionEvent* /*a*/)
{
 setSignalMastsAtLevelXingOpenFlag = false;
 setSignalMastsAtLevelXingFrame->setVisible(false);
}

/*private*/ void LayoutEditorTools::setXingSignalMastsDonePressed (JActionEvent* /*a*/) {
    if ( !getLevelCrossingMastInformation() ) return;
    SignalMast* aMast = getSignalMastFromEntry(xingSignalMastA->getText(),false,setSignalsAtLevelXingFrame);
    SignalMast* bMast = getSignalMastFromEntry(xingSignalMastB->getText(),false,setSignalsAtLevelXingFrame);
    SignalMast* cMast = getSignalMastFromEntry(xingSignalMastC->getText(),false,setSignalsAtLevelXingFrame);
    SignalMast* dMast = getSignalMastFromEntry(xingSignalMastD->getText(),false,setSignalsAtLevelXingFrame);
    //if ( !getXingSignalMastInformation() ) return;
    // place or update signals as requested
    if ( (aMast!=nullptr) && xingSignalMastA->addToPanel() ) {
        if (isSignalMastOnPanel(aMast) &&
                (aMast!=getSignalMastFromName(levelXing->getSignalAMastName())) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{xingSignalMastA->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(xingSignalMastA->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalAMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(xingSignalMastA->getText());
            placeXingAIcon(l, xingSignalMastA->isRightSelected(), 0.0);
            removeAssignment(aMast);
            levelXing->setSignalAMastName(xingSignalMastA->getText());
            needRedraw = true;
        }
    }
    else if ( (aMast!=nullptr) &&
            (aMast!=getSignalMastFromName(levelXing->getSignalAMastName())) &&
            (aMast!=getSignalMastFromName(levelXing->getSignalBMastName())) &&
            (aMast!=getSignalMastFromName(levelXing->getSignalCMastName())) &&
            (aMast!=getSignalMastFromName(levelXing->getSignalDMastName())) ) {
        if (isSignalMastOnPanel(aMast)) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{xingSignalMastA->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(xingSignalMastA->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalAMastName());
            removeAssignment(aMast);
            levelXing->setSignalAMastName(xingSignalMastA->getText());
        }
    }
    else if ( (aMast!=nullptr) &&
            ( (aMast==getSignalMastFromName(levelXing->getSignalBMastName())) ||
                (aMast==getSignalMastFromName(levelXing->getSignalCMastName())) ||
                (aMast==getSignalMastFromName(levelXing->getSignalDMastName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (aMast==nullptr) {
        removeSignalMastFromPanel(levelXing->getSignalAMastName());
        levelXing->setSignalAMastName("");
    }
    if ( (bMast!=nullptr) && xingSignalMastB->addToPanel()) {
        if (isSignalMastOnPanel(bMast) &&
                (bMast!=getSignalMastFromName(levelXing->getSignalBMastName()))) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{xingSignalMastB->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(xingSignalMastB->getText()));
         return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalBMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(xingSignalMastB->getText());
            placeXingBIcon(l, xingSignalMastB->isRightSelected(), 0.0);
            removeAssignment(bMast);
            levelXing->setSignalBMastName(xingSignalMastB->getText());
            needRedraw = true;
        }
    }
    else if ( (bMast!=nullptr) &&
            (bMast!=getSignalMastFromName(levelXing->getSignalAMastName())) &&
            (bMast!=getSignalMastFromName(levelXing->getSignalBMastName())) &&
            (bMast!=getSignalMastFromName(levelXing->getSignalCMastName())) &&
            (bMast!=getSignalMastFromName(levelXing->getSignalDMastName())) ) {
        if (isSignalMastOnPanel(bMast)) {
            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(
                    xingSignalMastB->getText()),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalBMastName());
            removeAssignment(bMast);
            levelXing->setSignalBMastName(xingSignalMastB->getText());
        }
    }
    else if ( (bMast!=nullptr) &&
            ( (bMast==getSignalMastFromName(levelXing->getSignalAMastName())) ||
                (bMast==getSignalMastFromName(levelXing->getSignalCMastName())) ||
                (bMast==getSignalMastFromName(levelXing->getSignalDMastName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (bMast==nullptr) {
        removeSignalMastFromPanel(levelXing->getSignalBMastName());
        levelXing->setSignalBMastName("");
    }
    if ( (cMast!=nullptr) && xingSignalMastC->addToPanel() ) {
        if (isSignalMastOnPanel(cMast) &&
                (cMast!=getSignalMastFromName(levelXing->getSignalCMastName())) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{xingSignalMastC->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(xingSignalMastC->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalCMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(xingSignalMastC->getText());
            placeXingCIcon(l, xingSignalMastA->isRightSelected(), 0.0);
            removeAssignment(cMast);
            levelXing->setSignalCMastName(xingSignalMastC->getText());
            needRedraw = true;
        }
    }
    else if ( (cMast!=nullptr) &&
            (cMast!=getSignalMastFromName(levelXing->getSignalAMastName())) &&
            (cMast!=getSignalMastFromName(levelXing->getSignalBMastName())) &&
            (cMast!=getSignalMastFromName(levelXing->getSignalCMastName())) &&
            (cMast!=getSignalMastFromName(levelXing->getSignalDMastName())) ) {
        if (isSignalMastOnPanel(cMast)) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{xingSignalMastC->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(xingSignalMastC->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalCMastName());
            removeAssignment(cMast);
            levelXing->setSignalCMastName(xingSignalMastC->getText());
        }
    }
    else if ( (cMast!=nullptr) &&
            ( (cMast==getSignalMastFromName(levelXing->getSignalBMastName())) ||
                (cMast==getSignalMastFromName(levelXing->getSignalAMastName())) ||
                (cMast==getSignalMastFromName(levelXing->getSignalDMastName())) ) )
    {
// need to figure out what to do in this case.
    }
    else if (cMast==nullptr) {
        removeSignalMastFromPanel(levelXing->getSignalCMastName());
        levelXing->setSignalCName("");
    }
    if ( (dMast!=nullptr) && xingSignalMastD->addToPanel() )
    {
        if (isSignalMastOnPanel(dMast) &&
                (dMast!=getSignalMastFromName(levelXing->getSignalDMastName())) ) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot place signal mast \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{xingSignalMastD->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot place signal mast \"%1\" on the panel\n                                                                because it is already on the panel.").arg(xingSignalMastD->getText()));
         return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalDMastName());
            SignalMastIcon* l = new SignalMastIcon(layoutEditor);
            l->setSignalMast(xingSignalMastD->getText());
            placeXingDIcon(l, xingSignalMastD->isRightSelected(), 0.0);
            removeAssignment(dMast);
            levelXing->setSignalDMastName(xingSignalMastD->getText());
            needRedraw = true;
        }
    }
    else if ( (dMast!=nullptr) &&
            (dMast!=getSignalMastFromName(levelXing->getSignalAMastName())) &&
            (dMast!=getSignalMastFromName(levelXing->getSignalBMastName())) &&
            (dMast!=getSignalMastFromName(levelXing->getSignalCMastName())) &&
            (dMast!=getSignalMastFromName(levelXing->getSignalDMastName())) ) {
        if (isSignalMastOnPanel(dMast)) {
//            JOptionPane::showMessageDialog(setSignalsAtLevelXingFrame,
//                tr("Error - Cannot assign signal mast \"%1\" to this block boundary\nbecause it is already on the panel at a different place."),
//                    new Object[]{xingSignalMastD->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSignalMastsAtLayoutSlipFrame, tr("Error"), tr("Error - Cannot assign signal mast \"%1\" to this block boundary\n                                                        because it is already on the panel at a different place.").arg(xingSignalMastD->getText()));
            return;
        }
        else {
            removeSignalMastFromPanel(levelXing->getSignalDMastName());
            removeAssignment(dMast);
            levelXing->setSignalDMastName(xingSignalMastD->getText());
        }
    }
    else if ( (dMast!=nullptr) &&
            ( (dMast==getSignalMastFromName(levelXing->getSignalBMastName())) ||
                (dMast==getSignalMastFromName(levelXing->getSignalCMastName())) ||
                (dMast==getSignalMastFromName(levelXing->getSignalAMastName())) ) ) {
// need to figure out what to do in this case.
    }
    else if (dMast==nullptr) {
        removeSignalMastFromPanel(levelXing->getSignalDMastName());
        levelXing->setSignalDMastName("");
    }
    // setup logic if requested
    // finish up
    setSignalMastsAtLevelXingOpenFlag = false;
    setSignalsAtLevelXingFrame->setVisible(false);
    xingMastFromMenu = false;
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}

/*private*/ void LayoutEditorTools::placeXingAIcon(PositionableIcon* icon, bool right, double fromPoint)
{

    //if(levelXing->getConnectA() instanceof TrackSegment)
 if(qobject_cast<TrackSegment*>(levelXing->getConnectA()))
    {
        TrackSegment* t = (TrackSegment*) levelXing->getConnectA();
        QPointF pf = levelXing->getCoordsA();
        QPoint p((int)pf.x(), (int)pf.y());

        QPointF end;
        if(t->getConnect1()==levelXing){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }

        bool east = false;

        if(end.x()<p.x())
            east = true;

        setIconOnPanel(t, icon, east, p, QPoint((int)end.x(),(int)end.y()), right, fromPoint);
        return;
    }
}
/*private*/ void LayoutEditorTools::placeXingBIcon(PositionableIcon* icon, bool right, double fromPoint)
{

    //if(levelXing->getConnectB() instanceof TrackSegment){
 if(qobject_cast<TrackSegment*>(levelXing->getConnectB()))
 {
        TrackSegment* t = (TrackSegment*) levelXing->getConnectB();
        QPointF pf = levelXing->getCoordsB();
        QPoint p((int)pf.x(), (int)pf.y());

        QPointF end;
        if(t->getConnect1()==levelXing){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }
        bool east = false;

        if(end.x()<p.x())
            east = true;

        setIconOnPanel(t, icon, east, p, QPoint((int)end.x(),(int)end.y()), right, fromPoint);
        return;
    }
}
/*private*/ void LayoutEditorTools::placeXingCIcon(PositionableIcon* icon, bool right, double fromPoint)
{
    //if(levelXing->getConnectC() instanceof TrackSegment) {
 if(qobject_cast<TrackSegment*>(levelXing->getConnectC()))
 {
        TrackSegment* t = (TrackSegment*) levelXing->getConnectC();
        QPointF pf = levelXing->getCoordsC();
        QPoint p((int)pf.x(), (int)pf.y());

        QPointF end;
        if(t->getConnect1()==levelXing){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }
        bool east = false;

        if(end.x()<p.x())
            east = true;

        setIconOnPanel(t, icon, east, p, QPoint((int)end.x(),(int)end.y()), right, fromPoint);
        return;
    }
}

/*private*/ void LayoutEditorTools::placeXingDIcon(PositionableIcon* icon, bool right, double fromPoint)
{
    //if(levelXing->getConnectD() instanceof TrackSegment){
 if(qobject_cast<TrackSegment*>(levelXing->getConnectD()))
 {
        TrackSegment* t = (TrackSegment*) levelXing->getConnectD();
        QPointF pf = levelXing->getCoordsD();
        QPoint p((int)pf.x(), (int)pf.y());

        QPointF end;
        if(t->getConnect1()==levelXing){
            end = layoutEditor->getCoords(t->getConnect2(), t->getType2());

        } else {
            end = layoutEditor->getCoords(t->getConnect1(), t->getType1());
        }
        //TrackSegment* t = boundary->getConnect2();
        bool east = false;

        if(end.x()<p.x())
            east = true;

        setIconOnPanel(t, icon, east, p, QPoint((int)end.x(),(int)end.y()), right, fromPoint);
        return;
    }
}	// initialize logging

/*public*/ void LayoutEditorTools::setSensorsAtTurnoutFromMenu(LayoutTurnout* to, QStringList blocks, MultiIconEditor* theEditor, JFrame* frame)
{
 sensorIconEditor = theEditor;
 layoutTurnout = to;
 turnout = to->getTurnout();
 sensorsTurnoutComboBox->setSelectedItem(turnout);
 turnoutSenBlocks =  QVector<QString>(4);
 for(int i = 0; i<blocks.length(); i++)
 {
  turnoutSenBlocks.replace(i, blocks.at(i));
 }
 setSensorsAtTurnouts(frame);
}

/*public*/ void LayoutEditorTools::setSensorsAtTurnouts(JFrame* frame)
{
    turnoutSensorFrame = frame;

    // Initialize if needed
    if (setSensorsAtTurnoutFrame == nullptr) {
        setSensorsAtTurnoutOpenFlag = false;

        turnoutSensorA = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());  // NOI18N
        turnoutSensorB = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());  // NOI18N
        turnoutSensorC = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());  // NOI18N
        turnoutSensorD = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());  // NOI18N

        //xingSignalMastA.getDetailsPanel()->setBackground(new Color(255,255,200));
        turnoutSensorA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");

        //xingSignalMastB.getDetailsPanel()->setBackground(new Color(200,255,255));
        turnoutSensorB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");

        //xingSignalMastC.getDetailsPanel()->setBackground(new Color(200,200,255));
        turnoutSensorC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,255)}");

        //xingSignalMastD.getDetailsPanel()->setBackground(new Color(255,200,200));
        turnoutSensorD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");


        setSensorsAtTurnoutFrame = new JmriJFrameX(tr("Sensors At Turnout"), false, true);
        oneFrameToRuleThemAll(setSensorsAtTurnoutFrame);
        setSensorsAtTurnoutFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
        setSensorsAtTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.SetSensorsAtTurnout", true);
        setSensorsAtTurnoutFrame->setLocation(70,30);
        QWidget* theContentPane = new QWidget();
        setSensorsAtTurnoutFrame->setCentralWidget(theContentPane);
        theContentPane->setLayout(new QVBoxLayout(theContentPane/*, BoxLayout.Y_AXIS*/));

        JPanel* panel1 = new JPanel(new FlowLayout());
        turnoutSensorNameLabel = new JLabel(tr("Turnout") + " "
                + tr("Name"));
        panel1->layout()->addWidget(turnoutSensorNameLabel);
        panel1->layout()->addWidget(sensorsTurnoutComboBox);
        sensorsTurnoutComboBox->setToolTip(tr("Enter name (system or user) of turnout where sensors are needed."));

        theContentPane->layout()->addWidget(panel1);
        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        JPanel* panel2 = new JPanel(new FlowLayout());
        JLabel* shTitle = new JLabel(tr("Sensors"));
        panel2->layout()->addWidget(shTitle);
        panel2->layout()->addWidget(new JLabel("	  "));
        panel2->layout()->addWidget(getSavedSensors = new QPushButton(tr("Get Saved")));
        //getSavedSensors.addActionListener((ActionEvent e) -> {
        connect(getSavedSensors, &QPushButton::clicked, [=]{
            turnoutSensorsGetSaved(/*e*/);
        });
        getSavedSensors->setToolTip(tr("Select to retrieve signal heads previously stored."));
        theContentPane->layout()->addWidget(panel2);

        sensorTurnoutPanel->setLayout(new QGridLayout());//0, 2)); //Content added as needed
        theContentPane->layout()->addWidget(sensorTurnoutPanel);

        theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

        QWidget* panel6 = new QWidget();
        panel6->setLayout(new QHBoxLayout());
        panel6->layout()->addWidget(changeSensorIcon = new QPushButton(tr("Change Sensor Icon")));
//        changeSensorIcon->layout()->addWidgetActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    turnoutSensorFrame->setVisible(true);
//                }
//            });
        connect(changeSensorIcon, SIGNAL(clicked()), this, SLOT(on_changeSignalIcon_clicked()));
        changeSensorIcon->setToolTip( tr("Click to change icons used to represent sensors.") );
        panel6->layout()->addWidget(new QLabel("  "));
        panel6->layout()->addWidget(setSensorsDone = new QPushButton(tr("Done")));
//        setSensorsDone->layout()->addWidgetActionListener(new ActionListener() {
 //            /*public*/ void actionPerformed(ActionEvent e) {
//                setSensorsDonePressed(e);
//            }
//        });
        connect(setSensorsDone, SIGNAL(clicked()), this, SLOT(setSensorsDonePressed()));
        setSensorsDone->setToolTip( tr("SensorDoneHint") );
        panel6->layout()->addWidget(setSensorsCancel = new QPushButton(tr("Cancel")));
//        setSensorsCancel->layout()->addWidgetActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setSensorsCancelPressed(e);
//            }
//        });
        connect(setSensorsCancel, SIGNAL(clicked()), this, SLOT(setSensorsCancelPressed()));
        setSensorsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
        theContentPane->layout()->addWidget(panel6);
//        setSensorsAtTurnoutFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                setSensorsCancelPressed(nullptr);
//            }
//        });
    }
    //sensorTurnoutPanel.removeAll();
    QList<QWidget*> list = sensorTurnoutPanel->findChildren<QWidget*>();
    foreach(QWidget* w, list)
    {
     sensorTurnoutPanel->layout()->removeWidget(w);
     delete w;
    }

    sensorsTurnoutComboBox->setVisible(!setSensorsAtTurnoutFromMenuFlag);

    if (setSensorsAtTurnoutFromMenuFlag) {
        turnoutSensorNameLabel->setText(tr("Turnout")
                + " " + tr("Name")
                + " " + layoutTurnout->getTurnoutName());
        turnoutSensorsGetSaved(/*null*/);
    } else {
        turnoutSensorNameLabel->setText(tr("Turnout") + " "
                + tr("Name"));
    }

    if (!setSensorsAtTurnoutOpenFlag) {
        setSensorsAtTurnoutFrame->resize(QSize());
        setSensorsAtTurnoutFrame->pack();
        setSensorsAtTurnoutOpenFlag = true;
    }
    setSensorsAtTurnoutFrame->setVisible(true);
}   //setSensorsAtTurnout

/*private*/ void LayoutEditorTools::turnoutSensorsGetSaved (JActionEvent* /*a*/) {
    if ( !getTurnoutSensorInformation() ) return;
    turnoutSenBlocks = layoutTurnout->getBlockBoundaries().toVector();
    turnoutSensorA->setTextField(layoutTurnout->getSensorAName());
    turnoutSensorB->setTextField(layoutTurnout->getSensorBName());
    turnoutSensorC->setTextField(layoutTurnout->getSensorCName());
    turnoutSensorD->setTextField(layoutTurnout->getSensorDName());

    turnoutSensorA->setBoundaryLabel(turnoutSenBlocks.at(0));
    turnoutSensorB->setBoundaryLabel(turnoutSenBlocks.at(1));
    turnoutSensorC->setBoundaryLabel(turnoutSenBlocks.at(2));
    turnoutSensorD->setBoundaryLabel(turnoutSenBlocks.at(3));

    sensorTurnoutPanel->layout()->removeWidget(turnoutSensorA->getDetailsPanel());
    sensorTurnoutPanel->layout()->removeWidget(turnoutSensorB->getDetailsPanel());
    sensorTurnoutPanel->layout()->removeWidget(turnoutSensorC->getDetailsPanel());
    sensorTurnoutPanel->layout()->removeWidget(turnoutSensorD->getDetailsPanel());

    bool blockBoundary = false;
    if(turnoutSenBlocks[0]!=nullptr){
        sensorTurnoutPanel->layout()->addWidget(turnoutSensorA->getDetailsPanel());
        blockBoundary = true;
    }
    if(turnoutSenBlocks[1]!=nullptr){
        sensorTurnoutPanel->layout()->addWidget(turnoutSensorB->getDetailsPanel());
        blockBoundary = true;
    }
    if(turnoutSenBlocks[2]!=nullptr){
        sensorTurnoutPanel->layout()->addWidget(turnoutSensorC->getDetailsPanel());
        blockBoundary = true;
    }
    if(turnoutSenBlocks[3]!=nullptr){
        sensorTurnoutPanel->layout()->addWidget(turnoutSensorD->getDetailsPanel());
        blockBoundary = true;
    }
    if (!blockBoundary)
//        JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame, "There are no block boundaries on this turnout\nIt is therefore not possible to add Sensors to it");
        QMessageBox::information(setSensorsAtTurnoutFrame, tr("Information"), tr("There are no block boundaries on this turnout\nIt is therefore not possible to add Sensors to it"));
//    setSensorsAtTurnoutFrame->setPreferredSize(nullptr);
//    setSensorsAtTurnoutFrame.pack();
}

/*private*/ int LayoutEditorTools::isSensorAssignedHere(Sensor* sensor, LayoutTurnout* lTurnout)
{
    if ((sensor==nullptr) || (lTurnout==nullptr))
        return NONE;
    QString sysName = sensor->getSystemName();
    QString uName = sensor->getUserName();
    QString name = lTurnout->getSensorAName();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A1;
    name = lTurnout->getSensorBName();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A2;
    name = lTurnout->getSensorCName();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return A3;
    name = lTurnout->getSensorDName();
    if ( (name!=nullptr) && (name.length()>0) && ((name==(uName)) ||
                    (name==(sysName))) ) return B1;
    return NONE;
}

///*public*/ bool LayoutEditorTools::removeAssignment(Sensor* sensor)
//{
// QString sysName = sensor->getSystemName();
// QString uName = sensor->getUserName();
// log->trace(tr("Remove sensor assignment at block boundary for '%1'").(arg(sensor->getDisplayName())));  // NOI18N
//         if (!static_cast<EntryExitPairs*>(InstanceManager::getDefault("EntryExitPairs"))->deleteNxPair(sensor)) {
//             log->trace(tr("Removal of NX pairs for sensor '%1' failed").arg(sensor->getDisplayName()));  // NOI18N
//             return false;
//         }
//         for (PositionablePoint* po : layoutEditor->getPositionablePoints()) {
//             if (po->getEastBoundSensor() == sensor) {
//                 po->setEastBoundSensor("");
//             }
//             if (po->getWestBoundSensor() == sensor) {
//                 po->setWestBoundSensor("");
//             }
//         }

//         for (LayoutTurnout* to : layoutEditor->getLayoutTurnouts()) {
//          if ((to->getSensorA()!=nullptr) &&
//                (to->getSensorAName()==(sName) || ((uName!=nullptr) &&
//                (to->getSensorAName()==(uName))))) to->setSensorA("");
//        if ((to->getSensorB()!=nullptr) &&
//                (to->getSensorBName()==(sName) || ((uName!=nullptr) &&
//                (to->getSensorBName()==(uName))))) to->setSensorB("");
//        if ((to->getSensorC()!=nullptr) &&
//                (to->getSensorCName()==(sName) || ((uName!=nullptr) &&
//                (to->getSensorCName()==(uName))))) to->setSensorC("");
//        if ((to->getSensorD()!=nullptr) &&
//                (to->getSensorDName()==(sName) || ((uName!=nullptr) &&
//                (to->getSensorDName()==(uName))))) to->setSensorD("");
//    }

//         for (LayoutSlip* to : layoutEditor->getLayoutSlips()) {
//                    if (to->getSensorA() == sensor) {
//                        to->setSensorA("");
//                    }
//                    if (to->getSensorB() == sensor) {
//                        to->setSensorB("");
//                    }
//                    if (to->getSensorC() == sensor) {
//                        to->setSensorC("");
//                    }
//                    if (to->getSensorD() == sensor) {
//                        to->setSensorD("");
//                    }
//                }
//         for (LevelXing* x : layoutEditor->getLevelXings()) {
//        if ((x->getSensorAName()!=nullptr) &&
//                (x->getSensorAName()==(sName) || ((uName!=nullptr) &&
//                (x->getSensorAName()==(uName))))) x->setSensorAName("");
//        if ((x->getSensorBName()!=nullptr) &&
//                (x->getSensorBName()==(sName) || ((uName!=nullptr) &&
//                (x->getSensorBName()==(uName))))) x->setSensorBName("");
//        if ((x->getSensorCName()!=nullptr) &&
//                (x->getSensorCName()==(sName) || ((uName!=nullptr) &&
//                (x->getSensorCName()==(uName))))) x->setSensorCName("");
//        if ((x->getSensorDName()!=nullptr) &&
//                (x->getSensorDName()==(sName) || ((uName!=nullptr) &&
//                (x->getSensorDName()==(uName))))) x->setSensorDName("");
//    }
//}


/*private*/ void LayoutEditorTools::setSensorsDonePressed (JActionEvent* /*a*/) // SLOT
{
//Placing of turnouts needs to be better handled
    // process turnout name
    if ( !getTurnoutSensorInformation() ) return;
    // process signal head names
    //if ( !getSensorTurnoutInformation() ) return;
    Sensor* sensorA = getSensorFromEntry(turnoutSensorA->getText(),false,setSensorsAtTurnoutFrame);
    //if (turnoutSensor==nullptr) return false;
    Sensor* sensorB = getSensorFromEntry(turnoutSensorB->getText(),false,setSensorsAtTurnoutFrame);
    //if (turnoutSensorB==nullptr) return false;
    Sensor* sensorC = getSensorFromEntry(turnoutSensorC->getText(),false,setSensorsAtTurnoutFrame);
    //if (turnoutSensorC==nullptr) return false;
    Sensor* sensorD = getSensorFromEntry(turnoutSensorD->getText(),false,setSensorsAtTurnoutFrame);
    // place signals as requested
    if (turnoutSensorA->addToPanel())
    {
     if (isSensorOnPanel(sensorA) &&
            (sensorA!=getSensorFromName(layoutTurnout->getSensorAName())))
     {
//            JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{turnoutSensorA->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(turnoutSensorA->getText())) ;
      return;
     }
     else {
            removeSensorFromPanel(layoutTurnout->getSensorA());
            placingBlock(getSensorIcon(turnoutSensorA->getText()), turnoutSensorA->isRightSelected(), 0.0);
//            removeAssignment(sensorA);
            layoutTurnout->setSensorA(turnoutSensorA->getText());
            needRedraw = true;
        }
    }
    else if (sensorA!=nullptr)
    {
        int assigned = isSensorAssignedHere(sensorA,layoutTurnout);
        if (assigned == NONE) {
            if ( isSensorOnPanel(sensorA) &&
                                isSensorAssignedAnywhere(sensorA) )
            {

//                JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                    tr("SensorsError8"),
//                        new Object[]{turnoutSensorA->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(turnoutSensorA->getText()));
                return;
            }
            else {
                removeSensorFromPanel(layoutTurnout->getSensorA());
//                removeAssignment(sensorA);
                layoutTurnout->setSensorA(turnoutSensorA->getText());
            }
        }
        else if (assigned!=A1) {
// need to figure out what to do in this case.
        }
    }
    else {
        removeSensorFromPanel(layoutTurnout->getSensorA());
        layoutTurnout->setSensorA("");
    }
    if ( (turnoutSensorB!=nullptr) && (turnoutSensorB->addToPanel())) {
        if (isSensorOnPanel(sensorB) &&
            (sensorB!=getSensorFromName(layoutTurnout->getSensorBName())))
        {
//            JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                    new Object[]{turnoutSensorB->text()}),
//                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(turnoutSensorB->getText()));
            return;
        }
        else {
            removeSensorFromPanel(layoutTurnout->getSensorB());

            placingBlockB(getSensorIcon(turnoutSensorB->getText()), turnoutSensorB->isRightSelected(), 0.0);
//            removeAssignment(sensorB);
            layoutTurnout->setSensorB(turnoutSensorB->getText());
            needRedraw = true;
        }
    }
    else if (sensorB!=nullptr) {
        int assigned = isSensorAssignedHere(sensorB,layoutTurnout);
        if (assigned == NONE) {
            if (isSensorOnPanel(sensorB) &&
                                isSensorAssignedAnywhere(sensorB) ) {
//                JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                    tr("SensorsError8"),
//                        new Object[]{turnoutSensorB->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(turnoutSensorB->getText()));

                return;
            }
            else {
                removeSensorFromPanel(layoutTurnout->getSensorB());
//                removeAssignment(sensorB);
                layoutTurnout->setSensorB(turnoutSensorB->getText());
            }
        }
        else if (assigned!=A2) {
// need to figure out what to do in this case.
        }
    }
    else {
        removeSensorFromPanel(layoutTurnout->getSensorB());
        layoutTurnout->setSensorB("");
    }
    if(sensorC!=nullptr){
        if (turnoutSensorC->addToPanel()) {
            if (isSensorOnPanel(sensorC) &&
                (sensorC!=getSensorFromName(layoutTurnout->getSensorCName()))) {
//                JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                    tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                        new Object[]{turnoutSensorC->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(turnoutSensorC->getText()));

                return;
            }
            else {
                removeSensorFromPanel(layoutTurnout->getSensorC());

                placingBlockC(getSensorIcon(turnoutSensorC->getText()), turnoutSensorC->isRightSelected(), 0.0);
//                removeAssignment(sensorC);
                layoutTurnout->setSensorC(turnoutSensorC->getText());
                needRedraw = true;
            }
        }
        else {
            int assigned = isSensorAssignedHere(sensorC,layoutTurnout);
            if (assigned == NONE) {
                if (isSensorOnPanel(sensorC)  &&
                                    isSensorAssignedAnywhere(sensorC) ) {
//                    JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                        tr("SensorsError8"),
//                            new Object[]{turnoutSensorC->text()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                    QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(turnoutSensorC->getText()));

                    return;
                }
                else {
                    removeSensorFromPanel(layoutTurnout->getSensorC());
//                    removeAssignment(sensorC);
                    layoutTurnout->setSensorC(turnoutSensorC->getText());
                }
            }
            else if (assigned!=A3) {
// need to figure out what to do in this case.
            }
        }
    }
    else {
        removeSensorFromPanel(layoutTurnout->getSensorC());
        layoutTurnout->setSensorC("");
    }
    if(sensorD!=nullptr){
        if (turnoutSensorD->addToPanel()) {
            if (isSensorOnPanel(sensorD) &&
                (sensorD!=getSensorFromName(layoutTurnout->getSensorDName()))) {
//                JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                    tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                        new Object[]{divergingField->text()}),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(turnoutSensorD->getText()));

                return;
            }
            else {
                removeSensorFromPanel(layoutTurnout->getSensorD());
                placingBlockD(getSensorIcon(turnoutSensorD->getText()), turnoutSensorD->isRightSelected(), 0.0);
//                removeAssignment(sensorD);
                layoutTurnout->setSensorD(turnoutSensorD->getText());
                needRedraw = true;
            }
        }
        else {
            int assigned = isSensorAssignedHere(sensorD,layoutTurnout);
            if (assigned == NONE) {
                if (isSensorOnPanel(sensorD) &&
                                    isSensorAssignedAnywhere(sensorD) ) {
//                    JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//                        tr("SensorsError8"),
//                            new Object[]{turnoutSensorD->text()}),
//                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                    QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(turnoutSensorD->getText()));

                    return;
                }
                else {
                    removeSensorFromPanel(layoutTurnout->getSensorD());
//                    removeAssignment(sensorD);
                    layoutTurnout->setSensorD(turnoutSensorD->getText());
                }
            }
            else if (assigned!=B1) {
// need to figure out what to do in this case.
            }
        }
    } else {
        removeSensorFromPanel(layoutTurnout->getSensorD());
        layoutTurnout->setSensorD("");
    }

    // make sure this layout turnout is not linked to another
    layoutTurnout->setLinkType(LayoutTurnout::NO_LINK);
    layoutTurnout->setLinkedTurnoutName("");
    // finish up
    setSensorsAtTurnoutOpenFlag = false;
    setSensorsAtTurnoutFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}   //setSensorsDonePressed

/*private*/ bool LayoutEditorTools::getTurnoutSensorInformation(){
    LayoutTurnout* t = NULL;
    QString str = "";
    turnout = NULL;
    layoutTurnout = NULL;
    str = sensorsTurnoutComboBox->currentText();
    if ( (str==nullptr) || (str==("")) ) {
//        JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,tr("SensorsError1"),
//                            tr("Error"),JOptionPane::ERROR_MESSAGE);
        QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"),tr("Error - No turnout name was entered. Please enter a turnout name or cancel."));
        return false;
    }
    turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(str);
    if (turnout==nullptr) {
//        JOptionPane::showMessageDialog(setSensorsAtTurnoutFrame,
//            tr("SensorsError2"),
//                new Object[]{str}), tr("Error"),
//                    JOptionPane::ERROR_MESSAGE);
        QMessageBox::critical(setSensorsAtTurnoutFrame, tr("Error"), tr("Error - No turnout is defined for \"%1\". Please enter\n                                                               a turnout name in the Turnout Table and on the panel.").arg(str));
        return false ;
    }
    else if ( (turnout->getUserName()==nullptr) || (turnout->getUserName()==("")) ||
                            turnout->getUserName()!=(str) ) {
        sensorsTurnoutComboBox->setSelectedItem(turnout);
    }
    layoutTurnout = layoutEditor->getFinder()->findLayoutTurnoutByBean(turnout);
            if (layoutTurnout == nullptr) {
                JOptionPane::showMessageDialog(layoutEditor,
                        tr("Error - Turnout \"{0}\" is not drawn on the panel.\nPlease enter the name of a drawn turnout.").arg(
                                str), tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
                return false;
            }
            return true;
}

/*private*/ void LayoutEditorTools::setSensorsCancelPressed (JActionEvent* /*a*/) {
 setSensorsAtTurnoutOpenFlag = false;
 setSensorsAtTurnoutFrame->setVisible(false);
}

// display dialog for Set Signals at Level Crossing tool
/*public*/ void LayoutEditorTools::setSensorsAtLevelXingFromMenu (LevelXing* xing, QVector<QString>* blocks, MultiIconEditor* theEditor,
        JFrame* theFrame )
{
 levelXing = xing;
 BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
 xingSensorsBlockACComboBox->setSelectedItem(bm->getBlock(levelXing->getBlockNameAC()));
 xingSensorsBlockBDComboBox->setSelectedItem(bm->getBlock(levelXing->getBlockNameBD()));
 for(int i = 0; i<blocks->size(); i++)
 {
  xingSensorBlocks->replace(i, blocks->at(i));
 }
 setSensorsAtLevelXing(theEditor, theFrame);
 return;
}

/*public*/ void LayoutEditorTools::setSensorsAtLevelXing(MultiIconEditor* theEditor, JFrame* theFrame)
{
 sensorIconEditor = theEditor;
 sensorXingFrame = theFrame;

 // Initialize if needed
 if (setSensorsAtLevelXingFrame == nullptr) {
  setSensorsAtLevelXingOpenFlag = false;

  xingSensorA = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  xingSensorB = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  xingSensorC = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  xingSensorD = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());

//  xingSensorA->getDetailsPanel().setBackground(new Color(255, 255, 200));
  xingSensorA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");
//  xingSensorB->getDetailsPanel().setBackground(new Color(200, 255, 255));
  xingSensorB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");
//  xingSensorC->getDetailsPanel().setBackground(new Color(200, 200, 255));
  xingSensorC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,255)}");
//  xingSensorD->getDetailsPanel().setBackground(new Color(255, 200, 200));
  xingSensorD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");

  setSensorsAtLevelXingFrame = new JmriJFrameX( tr("Set Sensors at Level Crossing"), false, true );

  setSensorsAtLevelXingFrame->addHelpMenu("package.jmri.jmrit.display.SetSensorsAtLevelXing", true);
  setSensorsAtLevelXingFrame->setLocation(70,30);
  QWidget* theContentPane = /*sensorsAtLevelXingFrame.getContentPane();*/ new QWidget;
  setSensorsAtLevelXingFrame->setCentralWidget(theContentPane);
  QVBoxLayout* centralWidgetLayout;
  theContentPane->setLayout(centralWidgetLayout = new QVBoxLayout); //, BoxLayout.Y_AXIS));

  QWidget* panel11 = new QWidget();
  panel11->setLayout(new QHBoxLayout());
  xingSensorA = new BeanDetails("Sensor", (Manager*)InstanceManager::sensorManagerInstance());
  xingSensorB = new BeanDetails("Sensor", (Manager*)InstanceManager::sensorManagerInstance());
  xingSensorC = new BeanDetails("Sensor", (Manager*)InstanceManager::sensorManagerInstance());
  xingSensorD = new BeanDetails("Sensor", (Manager*)InstanceManager::sensorManagerInstance());
  if (setSignalsAtLevelXingFromMenuFlag)
  {
   QLabel* blockANameLabel = new QLabel( tr("BlockAtA")+" "+
               tr("Name")+" : "+levelXing->getBlockNameAC());

   panel11->layout()->addWidget(blockANameLabel);
   xingSensorA->setTextField(levelXing->getSensorAName());
   xingSensorB->setTextField(levelXing->getSensorBName());
   xingSensorC->setTextField(levelXing->getSensorCName());
   xingSensorD->setTextField(levelXing->getSensorDName());
  }
  else
  {
   xingSensorsBlockACNameLabel = new JLabel(tr("Block") + " AC "
                      + tr("Name"));
   panel11->layout()->addWidget(xingSensorsBlockACNameLabel);
   panel11->layout()->addWidget(xingSensorsBlockACComboBox);
   xingSensorsBlockACComboBox->setToolTip(tr("Enter name of one block where sensors are needed at block boundary."));
  }
  centralWidgetLayout->addWidget(panel11);
  QWidget* panel12 = new QWidget();
  panel12->setLayout(new QHBoxLayout());
  if (setSignalsAtLevelXingFromMenuFlag)
  {
   QLabel* blockCNameLabel = new QLabel( tr("BlockAtC")+" "+
               tr("Name")+" : "+levelXing->getBlockNameBD());

   panel12->layout()->addWidget(blockCNameLabel);
  }
  else
  {
   xingSensorsBlockBDNameLabel = new JLabel(tr("Block") + " BD "
                       + tr("Name"));
   panel12->layout()->addWidget(xingSensorsBlockBDNameLabel);
   panel12->layout()->addWidget(xingSensorsBlockBDComboBox);
   xingSensorsBlockBDComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  }
  centralWidgetLayout->addWidget(panel12);
  centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Sensor"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedXingSensors = new QPushButton(tr("GetSaved")));
//  getSavedXingSensors->layout()->addWidgetActionListener(new ActionListener() {
//          /*public*/ void actionPerformed(ActionEvent e) {
//              xingSensorsGetSaved(e);
//          }
//      });
  connect(getSavedXingSensors, SIGNAL(clicked()), this, SLOT(xingSensorsGetSaved()));
  getSavedXingSensors->setToolTip( "Click to retrieve signal heads previously stored.");
  centralWidgetLayout->addWidget(panel2);

  //xingSensorA.getDetailsPanel()->setBackground(new Color(255,255,200));
  xingSensorA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");

  //xingSensorB.getDetailsPanel()->setBackground(new Color(200,255,255));
  xingSensorB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");

  //xingSensorC.getDetailsPanel()->setBackground(new Color(200,200,255));
  xingSensorC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,2055)}");

  //xingSensorD.getDetailsPanel()->setBackground(new Color(255,200,200));
  xingSensorD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");


  sensorXingPanel->setLayout(sensorXingPanelLayout = new QGridLayout(/*0,2*/));

  xingSensorA->setBoundaryLabel(xingSensorBlocks->at(0));
  xingSensorB->setBoundaryLabel(xingSensorBlocks->at(1));
  xingSensorC->setBoundaryLabel(xingSensorBlocks->at(2));
  xingSensorD->setBoundaryLabel(xingSensorBlocks->at(3));

  if(xingSensorBlocks->at(0)!=nullptr)
      sensorXingPanelLayout->addWidget(xingSensorA->getDetailsPanel(),0,0);
  if(xingSensorBlocks->at(1)!=nullptr)
      sensorXingPanelLayout->addWidget(xingSensorB->getDetailsPanel(),0,1);
  if(xingSensorBlocks->at(2)!=nullptr)
      sensorXingPanelLayout->addWidget(xingSensorC->getDetailsPanel(),1,0);
  if(xingSensorBlocks->at(3)!=nullptr)
      sensorXingPanelLayout->addWidget(xingSensorD->getDetailsPanel(), 1,1);
  centralWidgetLayout->addWidget(sensorXingPanel);

  centralWidgetLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());
  panel6->layout()->addWidget(changeSensorXingIcon = new QPushButton(tr("Change Sensor con")));
  //  changeSensorXingIcon->layout()->addWidgetActionListener(new ActionListener() {
  connect(changeSensorXingIcon, &QPushButton::clicked, [=]{
//            /*public*/ void actionPerformed(ActionEvent e) {
                sensorXingFrame->setVisible(true);
//            }
        });
  changeSensorXingIcon->setToolTip( tr("Click to change icons used to represent sensors.") );

  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setXingSensorsDone = new QPushButton(tr("Done")));
//  setXingSensorsDone->layout()->addWidgetActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          setXingSensorsDonePressed(e);
//      }
//  });
  connect(setXingSensorsDone, SIGNAL(clicked()), this, SLOT(setXingSensorsDonePressed()));
  setXingSensorsDone->setToolTip( tr("SensorDoneHint") );
  panel6->layout()->addWidget(setXingSensorsCancel = new QPushButton(tr("Cancel")));
//  setXingSensorsCancel->layout()->addWidgetActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          setXingSensorsCancelPressed(e);
//      }
//  });
  connect(setXingSensorsCancel, SIGNAL(clicked()), this, SLOT(setXingSensorsCancelPressed()));
  setXingSensorsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  centralWidgetLayout->addWidget(panel6);
//  sensorsAtLevelXingFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//      /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//          setXingSensorsCancelPressed(nullptr);
//      }
//     });
  setSensorsAtLevelXingFrame->addWindowListener(new XSSSWindowListener(this));
 }

 //sensorXingPanel.removeAll();
 QList<QWidget*> list = sensorXingPanel->findChildren<QWidget*>();
 foreach(QWidget* w, list)
 {
  sensorXingPanel->layout()->removeWidget(w);
  delete w;
 }

 xingSensorsBlockACComboBox->setVisible(!setSensorsAtLevelXingFromMenuFlag);
 xingSensorsBlockBDComboBox->setVisible(!setSensorsAtLevelXingFromMenuFlag);

 if (setSensorsAtLevelXingFromMenuFlag) {
     xingSensorsBlockACNameLabel->setText(tr("Block") + " AC "
             + tr("Name") + " " + levelXing->getBlockNameAC());
     xingSensorsBlockBDNameLabel->setText(tr("Block") + " BD "
             + tr("Name") + " " + levelXing->getBlockNameBD());

     xingSensorA->setTextField(levelXing->getSensorAName());
     xingSensorB->setTextField(levelXing->getSensorBName());
     xingSensorC->setTextField(levelXing->getSensorCName());
     xingSensorD->setTextField(levelXing->getSensorDName());
     xingSensorsGetSaved(/*null*/);
 } else {
     xingSensorsBlockACNameLabel->setText(tr("Block") + " AC "
             + tr("Name"));
     xingSensorsBlockBDNameLabel->setText(tr("Block") + " BD "
             + tr("Name"));
 }

 if (!setSensorsAtLevelXingOpenFlag) {
     setSensorsAtLevelXingFrame->resize(QSize());
     setSensorsAtLevelXingFrame->pack();
     setSensorsAtLevelXingOpenFlag = true;
 }
 setSensorsAtLevelXingFrame->setVisible(true);
}

/*private*/ void LayoutEditorTools::xingSensorsGetSaved (JActionEvent* /*a*/)
{
 if ( !getLevelCrossingSensorInformation() ) return;

 xingSensorBlocks = levelXing->getBlockBoundaries();
 xingSensorA->setTextField(levelXing->getSensorAName());
 xingSensorB->setTextField(levelXing->getSensorBName());
 xingSensorC->setTextField(levelXing->getSensorCName());
 xingSensorD->setTextField(levelXing->getSensorDName());

 sensorXingPanel->layout()->removeWidget(xingSensorA->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorB->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorC->getDetailsPanel());
 sensorXingPanel->layout()->removeWidget(xingSensorD->getDetailsPanel());

 xingSensorA->setBoundaryLabel(xingSensorBlocks->at(0));
 xingSensorB->setBoundaryLabel(xingSensorBlocks->at(1));
 xingSensorC->setBoundaryLabel(xingSensorBlocks->at(2));
 xingSensorD->setBoundaryLabel(xingSensorBlocks->at(3));

 bool boundary = false;
 if(xingSensorBlocks->at(0)!=nullptr)
 {
  sensorXingPanelLayout->addWidget(xingSensorA->getDetailsPanel());
  boundary = true;
 }
 if(xingSensorBlocks->at(1)!=nullptr)
 {
  sensorXingPanelLayout->addWidget(xingSensorB->getDetailsPanel());
  boundary = true;
 }
 if(xingSensorBlocks->at(2)!=nullptr){
     sensorXingPanelLayout->addWidget(xingSensorC->getDetailsPanel());
     boundary = true;
 }
 if(xingSensorBlocks->at(3)!=nullptr){
     sensorXingPanelLayout->addWidget(xingSensorD->getDetailsPanel());
     boundary = true;
 }
 if (!boundary)
 {
  JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame, tr("NoBoundaryXingSensor"));
 }
 setSensorsAtLevelXingFrame->setMinimumSize(QSize());
 setSensorsAtLevelXingFrame->adjustSize();
}

/*private*/ bool LayoutEditorTools::getLevelCrossingSensorInformation()
{
 if (!setSignalsAtLevelXingFromMenuFlag)
 {
  levelXing = nullptr;
     QList<LevelXing*> levelXings = layoutEditor->getLevelXings();
     if (levelXings.size() <= 0) {
         JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
                 tr("Error - There are no level crossings on your panel.\nPlease add a level crossing or cancel."),
                 tr("Error"),
                 JOptionPane::ERROR_MESSAGE);
         return false;
     } else if (levelXings.size() == 1) {
         levelXing = levelXings.at(0);
     } else {
         LayoutBlock* xingSensorBlockA = nullptr;
         LayoutBlock* xingSensorBlockC = nullptr;
         xingSensorBlockA = getBlockFromEntry(xingSensorsBlockACComboBox);
         if (xingSensorBlockA == nullptr) {
             return false;
         }
         QString theBlockName = xingSensorsBlockBDComboBox->getSelectedItemDisplayName();
         if ((theBlockName != nullptr) && !theBlockName.isEmpty()) {
             xingSensorBlockC = getBlockFromEntry(xingSensorsBlockBDComboBox);
             if (xingSensorBlockC == nullptr) {
                 return false;
             }
         }

         int foundCount = 0;
         //make two block tests first
         if (xingSensorBlockC != nullptr) {
             for (LevelXing* x : layoutEditor->getLevelXings()) {
                 LayoutBlock* xA = nullptr;
                 LayoutBlock* xB = nullptr;
                 LayoutBlock*xC = nullptr;
                 LayoutBlock* xD = nullptr;
                 LayoutBlock* xAC = x->getLayoutBlockAC();
                 LayoutBlock* xBD = x->getLayoutBlockBD();
                 if (x->getConnectA() != nullptr) {
                     xA = ((TrackSegment*) x->getConnectA())->getLayoutBlock();
                 }
                 if (x->getConnectB() != nullptr) {
                     xB = ((TrackSegment*) x->getConnectB())->getLayoutBlock();
                 }
                 if (x->getConnectC() != nullptr) {
                     xC = ((TrackSegment*) x->getConnectC())->getLayoutBlock();
                 }
                 if (x->getConnectD() != nullptr) {
                     xD = ((TrackSegment*) x->getConnectD())->getLayoutBlock();
                 }
                 if (((xA != nullptr) && (xC != nullptr) && (((xA == xingSensorBlockA) && (xC == xingSensorBlockC))
                         || ((xA == xingSensorBlockC) && (xC == xingSensorBlockA))))
                         || ((xB != nullptr) && (xD != nullptr) && (((xB == xingSensorBlockA) && (xD == xingSensorBlockC))
                         || ((xB == xingSensorBlockC) && (xD == xingSensorBlockA))))) {
                     levelXing = x;
                     foundCount++;
                 } else if ((xAC != nullptr) && (xBD != nullptr) && (((xAC == xingSensorBlockA) && (xBD == xingSensorBlockC))
                         || ((xAC == xingSensorBlockC) && (xBD == xingSensorBlockA)))) {
                     levelXing = x;
                     foundCount++;
                 }
             }
         }
         if (foundCount == 0) {
             //try one block test
             for (LevelXing* x : layoutEditor->getLevelXings()) {
                 if ((xingSensorBlockA == x->getLayoutBlockAC()) || (xingSensorBlockA == x->getLayoutBlockBD())) {
                     levelXing = x;
                     foundCount++;
                 }
             }
         }
         if (foundCount > 1) {
             JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
                     tr("Error - The entered block names match \"%1\" level crossings.\nPlease enter block names that match only one level crossing.").arg(
                             " " + QString::number(foundCount) + " "),
                     tr("Error"),
                     JOptionPane::ERROR_MESSAGE);
             return false;
         }
         if (levelXing == nullptr) {
             JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
                     tr("Error - No level crossing matches the block(s)\nentered. Please try again or cancel."),
                     tr("Error"),
                     JOptionPane::ERROR_MESSAGE);
             return false;
         }
     }
 }
 return true;
}

/*private*/ void LayoutEditorTools::setXingSensorsCancelPressed (JActionEvent* /*a*/)
{
 setSensorsAtLevelXingFrame->setVisible(false);
 setSignalsAtLevelXingFromMenuFlag = false;
}

/*private*/ void LayoutEditorTools::setXingSensorsDonePressed (JActionEvent* /*a*/)
{
  log->trace("setXingSensorsDonePressed");  // NOI18N

 if ( !getLevelCrossingSensorInformation() )
  return;

 Sensor* aSensor = getSensorFromEntry(xingSensorA->getText(),false,setSensorsAtLevelXingFrame);
 Sensor* bSensor = getSensorFromEntry(xingSensorB->getText(),false,setSensorsAtLevelXingFrame);
 Sensor* cSensor = getSensorFromEntry(xingSensorC->getText(),false,setSensorsAtLevelXingFrame);
 Sensor* dSensor = getSensorFromEntry(xingSensorD->getText(),false,setSensorsAtLevelXingFrame);
 // place or update signals as requested
 if ( (aSensor!=nullptr) && xingSensorA->addToPanel() )
 {
  if (isSensorOnPanel(aSensor) &&
            (aSensor!=getSensorFromName(levelXing->getSensorAName())) )
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                new Object[]{xingSensorA->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(xingSensorA->getText()));
        return;
  }
  else
  {
   removeSensorFromPanel(levelXing->getSensorA());
   placeXingAIcon(getSensorIcon(xingSensorA->getText()), xingSensorA->isRightSelected(), 0.0);
//   removeAssignment(aSensor);
   levelXing->setSensorAName(xingSensorB->getText());
   needRedraw = true;
  }
 }
 else if ( (aSensor!=nullptr) &&
        (aSensor!=getSensorFromName(levelXing->getSensorAName())) &&
        (aSensor!=getSensorFromName(levelXing->getSensorBName())) &&
        (aSensor!=getSensorFromName(levelXing->getSensorCName())) &&
        (aSensor!=getSensorFromName(levelXing->getSensorDName())) )
 {
  if (isSensorOnPanel(aSensor))
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("SensorsError13"),
//                new Object[]{xingSensorA->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(xingSensorA->getText()));
      return;
    }
    else
  {
      removeSensorFromPanel(levelXing->getSensorA());
//      removeAssignment(aSensor);
      levelXing->setSensorAName(xingSensorA->getText());
  }
 }
 else if ( (aSensor!=nullptr) &&
        ( (aSensor==getSensorFromName(levelXing->getSensorBName())) ||
            (aSensor==getSensorFromName(levelXing->getSensorCName())) ||
            (aSensor==getSensorFromName(levelXing->getSensorDName())) ) )
 {
 // need to figure out what to do in this case.
 }
 else if (aSensor==nullptr)
 {
  removeSensorFromPanel(levelXing->getSensorA());
  levelXing->setSensorAName("");
 }

 if ( (bSensor!=nullptr) && xingSensorB->addToPanel() )
 {
  if (isSensorOnPanel(bSensor) &&
          (bSensor!=getSensorFromName(levelXing->getSensorBName()))) {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                new Object[]{xingSensorB->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(xingSensorB->getText()));
      return;
  }
  else
  {
   removeSensorFromPanel(levelXing->getSensorB());
   placeXingBIcon(getSensorIcon(xingSensorB->getText()), xingSensorB->isRightSelected(), 0.0);
//   removeAssignment(bSensor);
   levelXing->setSensorBName(xingSensorB->getText());
   needRedraw = true;
  }
 }
 else if ( (bSensor!=nullptr) &&
        (bSensor!=getSensorFromName(levelXing->getSensorAName())) &&
        (bSensor!=getSensorFromName(levelXing->getSensorBName())) &&
        (bSensor!=getSensorFromName(levelXing->getSensorCName())) &&
        (bSensor!=getSensorFromName(levelXing->getSensorDName())) )
 {
  if (isSensorOnPanel(bSensor))
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("SensorsError13"),
//                new Object[]{xingSensorB->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(xingSensorB->getText()));
      return;
  }
  else
  {
   removeSensorFromPanel(levelXing->getSensorB());
//   removeAssignment(bSensor);
   levelXing->setSensorBName(xingSensorB->getText());
  }
 }
 else if ( (bSensor!=nullptr) &&
        ( (bSensor==getSensorFromName(levelXing->getSensorAName())) ||
            (bSensor==getSensorFromName(levelXing->getSensorCName())) ||
            (bSensor==getSensorFromName(levelXing->getSensorDName())) ) )
 {
  // need to figure out what to do in this case.
 }
 else if (bSensor==nullptr)
 {
  removeSensorFromPanel(levelXing->getSensorB());
  levelXing->setSensorBName("");
 }

 if ( (cSensor!=nullptr) && xingSensorC->addToPanel() )
 {
  if (isSensorOnPanel(cSensor) &&
            (cSensor!=getSensorFromName(levelXing->getSensorCName())) )
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                new Object[]{xingSensorC->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(xingSensorC->getText()));
   return;
  }
  else
  {
    removeSensorFromPanel(levelXing->getSensorC());
    placeXingCIcon(getSensorIcon(xingSensorC->getText()), xingSensorC->isRightSelected(), 0.0);
//    removeAssignment(cSensor);
    levelXing->setSensorCName(xingSensorC->getText());
    needRedraw = true;
  }
 }
 else if ( (cSensor!=nullptr) &&
        (cSensor!=getSensorFromName(levelXing->getSensorAName())) &&
        (cSensor!=getSensorFromName(levelXing->getSensorBName())) &&
        (cSensor!=getSensorFromName(levelXing->getSensorCName())) &&
        (cSensor!=getSensorFromName(levelXing->getSensorDName())) )
 {
  if (isSensorOnPanel(cSensor))
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("SensorsError13"),
//                new Object[]{xingSensorC->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
    QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(xingSensorC->getText()));
    return;
  }
  else
  {
    removeSensorFromPanel(levelXing->getSensorC());
//    removeAssignment(cSensor);
   levelXing->setSensorCName(xingSensorC->getText());
  }
 }
 else if ( (cSensor!=nullptr) &&
        ( (cSensor==getSensorFromName(levelXing->getSensorBName())) ||
            (cSensor==getSensorFromName(levelXing->getSensorAName())) ||
            (cSensor==getSensorFromName(levelXing->getSensorDName())) ) )
 {
   // need to figure out what to do in this case.
 }
 else if (cSensor==nullptr)
 {
   removeSensorFromPanel(levelXing->getSensorC());
   levelXing->setSensorCName("");
 }

 if ( (dSensor!=nullptr) && xingSensorD->addToPanel() )
 {
  if (isSensorOnPanel(dSensor) &&
          (dSensor!=getSensorFromName(levelXing->getSensorDName())) )
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                new Object[]{xingSensorD->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel.").arg(xingSensorD->getText()));
   return;
  }
  else
  {
    removeSensorFromPanel(levelXing->getSensorD());
    placeXingDIcon(getSensorIcon(xingSensorD->getText()), xingSensorD->isRightSelected(), 0.0);
//    removeAssignment(dSensor);
    levelXing->setSensorDName(xingSensorD->getText());
    needRedraw = true;
  }
 }
 else if ( (dSensor!=nullptr) &&
        (dSensor!=getSensorFromName(levelXing->getSensorAName())) &&
        (dSensor!=getSensorFromName(levelXing->getSensorBName())) &&
        (dSensor!=getSensorFromName(levelXing->getSensorCName())) &&
        (dSensor!=getSensorFromName(levelXing->getSensorDName())) )
 {
  if (isSensorOnPanel(dSensor))
  {
//        JOptionPane::showMessageDialog(setSensorsAtLevelXingFrame,
//            tr("SensorsError13"),
//                new Object[]{xingSensorD->text()}),
//                    tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtLevelXingFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\nbecause it is already on the panel at a different place.").arg(xingSensorD->getText()));
   return;
  }
  else
  {
   removeSensorFromPanel(levelXing->getSensorD());
//   removeAssignment(dSensor);
   levelXing->setSensorDName(xingSensorD->getText());
  }
 }
 else if ( (dSensor!=nullptr) &&
        ( (dSensor==getSensorFromName(levelXing->getSensorBName())) ||
            (dSensor==getSensorFromName(levelXing->getSensorCName())) ||
            (dSensor==getSensorFromName(levelXing->getSensorAName())) ) )
 {
  // need to figure out what to do in this case.
 }
 else if (dSensor==nullptr)
 {
  removeSensorFromPanel(levelXing->getSensorD());
  levelXing->setSensorDName("");
 }
 // setup logic if requested
 // finish up
 setSensorsAtLevelXingOpenFlag = false;
 setSensorsAtLevelXingFrame->setVisible(false);
 setSignalsAtLevelXingFromMenuFlag = false;
 if (needRedraw)
 {
  layoutEditor->redrawPanel();
  needRedraw = false;
  layoutEditor->setDirty();
 }
}

/*private*/ bool LayoutEditorTools::getSimpleBlockInformation() {
    //might have to do something to trick it with an end bumper
    if (!setSignalMastsAtBlockBoundaryFromMenuFlag) {
        block1 = getBlockFromEntry(block1IDComboBox);
        if (block1==nullptr) return false;
        block2 = getBlockFromEntry(block2IDComboBox);
        if (block2==nullptr){
            PositionablePoint* p = NULL;
           for (PositionablePoint* p : layoutEditor->getPositionablePoints()) {
                if (p->getType() == PositionablePoint::END_BUMPER) {
                    boundary = p;
                } else {
                    return false;
                }
            }
        }

        //now we try to find an anchor that connected to blocks 1 and 2
        //(if this fails boundary will still be set to the pp set if
        //block2 was null or equal to block1 above.)
        boundary = NULL;
        for (PositionablePoint* p : layoutEditor->getPositionablePoints()) {
         if (p->getType() == PositionablePoint::ANCHOR) {
                LayoutBlock* bA = NULL;
                LayoutBlock* bB = NULL;
                if (p->getConnect1()!=nullptr) bA = p->getConnect1()->getLayoutBlock();
                if (p->getConnect2()!=nullptr) bB = p->getConnect2()->getLayoutBlock();
                if ( (bA!=nullptr) && (bB!=nullptr) && (bA!=bB) ) {
                    if ( ( (bA==block1) && (bB==block2) ) ||
                                ( (bA==block2) && (bB==block1) ) ) {
                        boundary = p;
                    }
                }
            }
        }
        if (boundary==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAtBlockBoundaryFrame,
                        tr("Error - The two blocks entered do not join at an anchor point.\nPlease enter the correct blocks and try again."),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
            return false;
        }
    }
    return true;
}

// display dialog for Set Signals at Level Crossing tool
/*public*/ void LayoutEditorTools::setSensorsAtSlipFromMenu (LayoutSlip* slip, QVector<QString> blocks, MultiIconEditor* theEditor, JFrame* theFrame )
{
 layoutSlip = slip;
 BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
 slipSensorsBlockAComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockName()));
 slipSensorsBlockBComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockBName()));
 slipSensorsBlockCComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockCName()));
 slipSensorsBlockDComboBox->setSelectedItem(bm->getBlock(layoutSlip->getBlockDName()));
 for (int i = 0; i < blocks.length(); i++) {
     slipSensorBlocks->replace(i, blocks[i]);
 }
 setSensorsAtSlipFromMenuFlag = true;
 setSensorsAtSlip(theEditor, theFrame);
 setSensorsAtSlipFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSensorsAtSlip(MultiIconEditor* theEditor, JFrame* theFrame)
{
 sensorIconEditor = theEditor;
 sensorSlipFrame = theFrame;

 // Initialize if needed
 if (setSensorsAtSlipFrame == nullptr)
 {
  setSensorsAtSlipOpenFlag = false;
  slipSensorA = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  slipSensorB = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  slipSensorC = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());
  slipSensorD = new BeanDetails("Sensor", InstanceManager::sensorManagerInstance());

  slipSensorA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");
  slipSensorB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200, 255, 255)}");
  slipSensorC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200, 200, 255)}");
  slipSensorD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255, 200, 200)}");

  setSensorsAtSlipFrame = new JmriJFrameX( tr("Set Sensors at a Slip"), false, true );
  oneFrameToRuleThemAll(setSensorsAtSlipFrame);
  setSensorsAtSlipFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
//  setSensorsAtSlipFrame->addHelpMenu("package.jmri.jmrit.display.SetSensorsAtLevelSlip", true);
  setSensorsAtSlipFrame->setLocation(70,30);
  QWidget* theContentPane = setSensorsAtSlipFrame->getContentPane();
  theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));

  JPanel* panel11A = new JPanel(new FlowLayout());
  slipSignalBlockANameLabel = new JLabel(tr("Block") + " A "
          + tr("Name"));
  panel11A->layout()->addWidget(slipSignalBlockANameLabel);
  panel11A->layout()->addWidget(slipSensorsBlockAComboBox);
  slipSensorsBlockAComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11A);

  JPanel* panel11B = new JPanel(new FlowLayout());
  slipSignalBlockBNameLabel = new JLabel(tr("Block") + " B "
          + tr("Name"));
  panel11B->layout()->addWidget(slipSignalBlockBNameLabel);
  panel11B->layout()->addWidget(slipSensorsBlockBComboBox);
  slipSensorsBlockBComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11B);

  JPanel* panel11C = new JPanel(new FlowLayout());
  slipSignalBlockCNameLabel = new JLabel(tr("Block") + " C "
          + tr("Name"));
  panel11C->layout()->addWidget(slipSignalBlockCNameLabel);
  panel11C->layout()->addWidget(slipSensorsBlockCComboBox);
  slipSensorsBlockCComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11C);

  JPanel* panel11D = new JPanel(new FlowLayout());
  slipSignalBlockDNameLabel = new JLabel(tr("Block") + " D "
          + tr("Name"));
  panel11D->layout()->addWidget(slipSignalBlockDNameLabel);
  panel11D->layout()->addWidget(slipSensorsBlockDComboBox);
  slipSensorsBlockDComboBox->setToolTip(tr("Enter name of one Block where Sensors are needed at block boundary."));
  theContentPane->layout()->addWidget(panel11D);

  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  QWidget* panel2 = new QWidget();
  panel2->setLayout(new QHBoxLayout());
  QLabel* shTitle = new QLabel(tr("Sensor"));
  panel2->layout()->addWidget(shTitle);
  panel2->layout()->addWidget(new QLabel("   "));
  panel2->layout()->addWidget(getSavedSlipSensors = new QPushButton(tr("Get Saved")));
//     getSavedSlipSensors->layout()->addWidgetActionListener(new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent e) {
//                 slipSensorsGetSaved(e);
//             }
//         });
  connect(getSavedSlipSensors, SIGNAL(clicked()), this, SLOT(slipSensorsGetSaved()));
  getSavedSlipSensors->setToolTip("Click to retrieve signal heads previously stored.");
  theContentPane->layout()->addWidget(panel2);

  //slipSensorA->getDetailsPanel()->setBackground(new Color(255,255,200));
  slipSensorA->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,255,200)}");

  //slipSensorB->getDetailsPanel()->setBackground(new Color(200,255,255));
  slipSensorB->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,255,255)}");

  //slipSensorC->getDetailsPanel()->setBackground(new Color(200,200,255));
  slipSensorC->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(200,200,255)}");

  //slipSensorD->getDetailsPanel()->setBackground(new Color(255,200,200));
  slipSensorD->getDetailsPanel()->setStyleSheet("QWidget { background: rgb(255,200,200)}");

  sensorSlipPanelLayout = new QGridLayout(sensorSlipPanel);
  //sensorSlipPanel->setLayout(new GridLayout(2,2));

  slipSensorA->setBoundaryLabel(slipSensorBlocks->at(0));
  slipSensorB->setBoundaryLabel(slipSensorBlocks->at(1));
  slipSensorC->setBoundaryLabel(slipSensorBlocks->at(2));
  slipSensorD->setBoundaryLabel(slipSensorBlocks->at(3));

  if(slipSensorBlocks->at(0)!=nullptr)
      sensorSlipPanelLayout->addWidget(slipSensorA->getDetailsPanel(),0,0);
  else
      sensorSlipPanelLayout->addWidget(new QWidget(),0,0);
  if(slipSensorBlocks->at(3)!=nullptr)
      sensorSlipPanelLayout->addWidget(slipSensorD->getDetailsPanel(),0,1);
  else
      sensorSlipPanelLayout->addWidget(new QWidget(),0,1);
  if(slipSensorBlocks->at(1)!=nullptr)
      sensorSlipPanelLayout->addWidget(slipSensorB->getDetailsPanel(),1,0);
  else
      sensorSlipPanelLayout->addWidget(new QWidget(),1,0);
  if(slipSensorBlocks->at(2)!=nullptr)
      sensorSlipPanelLayout->addWidget(slipSensorC->getDetailsPanel(),1,1);
  else
      sensorSlipPanelLayout->addWidget(new QWidget(),1,1);

  theContentPane->layout()->addWidget(sensorSlipPanel);

  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new QHBoxLayout());
  panel6->layout()->addWidget(changeSensorSlipIcon = new QPushButton(tr("Change Sensor Icon")));
//     changeSensorSlipIcon->layout()->addWidgetActionListener(new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent e) {
  connect(changeSensorSlipIcon, &QPushButton::clicked, [=]{
                 sensorSlipFrame->setVisible(true);
//             }
         });
  changeSensorSlipIcon->setToolTip( tr("ChangeSensorIconHint") );

  panel6->layout()->addWidget(new QLabel("  "));
  panel6->layout()->addWidget(setSlipSensorsDone = new QPushButton(tr("Done")));
//     setSlipSensorsDone->layout()->addWidgetActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             setSlipSensorsDonePressed(e);
//         }
//     });
  connect(setSlipSensorsDone, SIGNAL(clicked()),this, SLOT(setSlipSensorsDonePressed()));
  setSlipSensorsDone->setToolTip( tr("Click Done to perform tasks requested above and dismiss this dialog.") );
  panel6->layout()->addWidget(setSlipSensorsCancel = new QPushButton(tr("Cancel")));
//     setSlipSensorsCancel->layout()->addWidgetActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             setSlipSensorsCancelPressed(e);
//         }
//     });
  connect(setSlipSensorsCancel, SIGNAL(clicked()),this, SLOT(setSlipSensorsCancelPressed()));
  setSlipSensorsCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  theContentPane->layout()->addWidget(panel6);
//     setSensorsAtSlipFrame->layout()->addWidgetWindowListener(new java.awt.event.WindowAdapter() {
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             setSlipSensorsCancelPressed(nullptr);
//         }
//     });
  setSensorsAtSlipFrame->addWindowListener(new SASWindowListener(this));
 }//if (setSensorsAtSlipFrame == null)

 //sensorSlipPanel.removeAll();
 QList<QWidget*> list = sensorSlipPanel->findChildren<QWidget*>();
 foreach(QWidget* w, list)
 {
  sensorSlipPanel->layout()->removeWidget(w);
  delete w;
 }
 slipSensorsBlockAComboBox->setVisible(!setSensorsAtSlipFromMenuFlag);
 slipSensorsBlockBComboBox->setVisible(!setSensorsAtSlipFromMenuFlag);
 slipSensorsBlockCComboBox->setVisible(!setSensorsAtSlipFromMenuFlag);
 slipSensorsBlockDComboBox->setVisible(!setSensorsAtSlipFromMenuFlag);

 if (setSensorsAtSlipFromMenuFlag) {
     slipSignalBlockANameLabel->setText(tr("Block") + " A "
             + tr("Name") + " " + layoutSlip->getBlockName());
     slipSignalBlockBNameLabel->setText(tr("Block") + " B "
             + tr("Name") + " " + layoutSlip->getBlockBName());
     slipSignalBlockCNameLabel->setText(tr("Block") + " C "
             + tr("Name") + " " + layoutSlip->getBlockCName());
     slipSignalBlockDNameLabel->setText(tr("Block") + " D "
             + tr("Name") + " " + layoutSlip->getBlockDName());
     slipSensorsGetSaved(/*null*/);
 } else {
     slipSignalBlockANameLabel->setText(tr("Block")+ " A "
             + tr("Name"));
     slipSignalBlockBNameLabel->setText(tr("Block") + " B "
             + tr("Name"));
     slipSignalBlockCNameLabel->setText(tr("Block") + " C "
             + tr("Name"));
     slipSignalBlockDNameLabel->setText(tr("Block") + " D "
             + tr("Name"));
 }

 if (setSensorsAtSlipOpenFlag) {
     slipSensorsGetSaved();
 } else {
     setSensorsAtSlipFrame->resize(QSize());
     setSensorsAtSlipFrame->setVisible(true);
     setSensorsAtSlipOpenFlag = true;
 }
 setSensorsAtSlipFrame->resize(QSize());
 setSensorsAtSlipFrame->pack();
}

/*private*/ void LayoutEditorTools::slipSensorsGetSaved (JActionEvent* /*a*/)
{
 if ( !getSlipSensorInformation() ) return;

 slipSensorBlocks = layoutSlip->getBlockBoundaries();
 slipSensorA->setTextField(layoutSlip->getSensorAName());
 slipSensorB->setTextField(layoutSlip->getSensorBName());
 slipSensorC->setTextField(layoutSlip->getSensorCName());
 slipSensorD->setTextField(layoutSlip->getSensorDName());

 sensorSlipPanel->layout()->removeWidget(slipSensorA->getDetailsPanel());
 sensorSlipPanel->layout()->removeWidget(slipSensorB->getDetailsPanel());
 sensorSlipPanel->layout()->removeWidget(slipSensorC->getDetailsPanel());
 sensorSlipPanel->layout()->removeWidget(slipSensorD->getDetailsPanel());

 slipSensorA->setBoundaryLabel(slipSensorBlocks->at(0));
 slipSensorB->setBoundaryLabel(slipSensorBlocks->at(1));
 slipSensorC->setBoundaryLabel(slipSensorBlocks->at(2));
 slipSensorD->setBoundaryLabel(slipSensorBlocks->at(3));

 bool boundary = false;
 if(slipSensorBlocks->at(0)!=nullptr){
     sensorSlipPanelLayout->addWidget(slipSensorA->getDetailsPanel());
     boundary = true;
 }
 if(slipSensorBlocks->at(1)!=nullptr){
     sensorSlipPanelLayout->addWidget(slipSensorB->getDetailsPanel());
     boundary = true;
 }
 if(slipSensorBlocks->at(2)!=nullptr){
     sensorSlipPanelLayout->addWidget(slipSensorC->getDetailsPanel());
     boundary = true;
 }
 if(slipSensorBlocks->at(3)!=nullptr){
     sensorSlipPanelLayout->addWidget(slipSensorD->getDetailsPanel());
     boundary = true;
 }
 if (!boundary)
 {
     JOptionPane::showMessageDialog(setSensorsAtSlipFrame, tr("NoBoundarySlipSensor"));
 }
 setSensorsAtSlipFrame->resize(QSize());
 setSensorsAtSlipFrame->pack();
}

/*private*/ bool LayoutEditorTools::getSlipSensorInformation()
{
 if (!setSensorsAtSlipFromMenuFlag)
 {
  layoutSlip = NULL;
  QList<LayoutSlip*> layoutSlips = layoutEditor->getLayoutSlips();
  if (layoutSlips.size()<=0)
  {
//      JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//          tr("Error - There are no level crossings on your panel\nPlease add a level crossing or cancel."),
//                      tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - There are no level crossings on your panel.\n                                                             Please add a level crossing or cancel."));
   return false;
  }
  else if (layoutSlips.size()==1) {
      layoutSlip = layoutSlips.at(0);
  }
  else {
      LayoutBlock* slipSensorBlockA = NULL;
      slipSensorBlockA = getBlockFromEntry(slipSensorsBlockAComboBox);
      if (slipSensorBlockA==nullptr) return false;
      LayoutSlip* x = NULL;
      int foundCount = 0;

      for (int i = 0;(i<layoutSlips.size());i++) {
          x = layoutSlips.at(i);
          LayoutBlock* xA = NULL;
          LayoutBlock* xB = NULL;
          LayoutBlock* xC = NULL;
          LayoutBlock* xD = NULL;
          LayoutBlock* xAC = x->getLayoutBlock();
          if (x->getConnectA()!=nullptr) xA = ((TrackSegment*)x->getConnectA())->getLayoutBlock();
          if (x->getConnectB()!=nullptr) xB = ((TrackSegment*)x->getConnectB())->getLayoutBlock();
          if (x->getConnectC()!=nullptr) xC = ((TrackSegment*)x->getConnectC())->getLayoutBlock();
          if (x->getConnectD()!=nullptr) xD = ((TrackSegment*)x->getConnectD())->getLayoutBlock();
          if ( ( (xA!=nullptr) && (xC!=nullptr) && ( (xA==slipSensorBlockA) ||
                  (xC==slipSensorBlockA) ) ) ||
                  ( (xB!=nullptr) && (xD!=nullptr) && ( ((xB==slipSensorBlockA)) ||
                  ((xD==slipSensorBlockA)) ) ) ) {
              layoutSlip = x;
              foundCount ++;
          }
          else if ( (xAC!=nullptr) && (xAC==slipSensorBlockA) ) {
              layoutSlip = x;
              foundCount ++;
          }
      }
      if (foundCount==0) {
          // try one block test
          for (int i = 0;(i<layoutSlips.size());i++) {
              x = layoutSlips.at(i);
              if (slipSensorBlockA == x->getLayoutBlock()) {
                  layoutSlip = x;
                  foundCount ++;
              }
          }
      }
      if (foundCount>1)
      {
          JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
                  tr("Error - The entered block names match \"%1\" level crossings.\nPlease enter block names that match only one level crossing.").arg(
                      " "+QString::number(foundCount)+" "),
                          tr("Error"),JOptionPane::ERROR_MESSAGE);

          return false;
      }
      if (layoutSlip==nullptr) {
          JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
                      tr("Error - No level crossing matches the block(s)\nentered. Please try again or cancel."),
                              tr("Error"),JOptionPane::ERROR_MESSAGE);
          return false;
      }
  }
 }
 return true;
}

/*private*/ void LayoutEditorTools::setSlipSensorsCancelPressed (JActionEvent* /*a*/)
{
    setSensorsAtSlipOpenFlag = false;
    setSensorsAtSlipFrame->setVisible(false);
    setSensorsAtSlipFromMenuFlag = false;
}

/*private*/ void LayoutEditorTools::setSlipSensorsDonePressed (JActionEvent* /*a*/)
{
 if ( !getSlipSensorInformation() ) return;
 Sensor* aSensor = getSensorFromEntry(slipSensorA->getText(),false,setSensorsAtSlipFrame);
 Sensor* bSensor = getSensorFromEntry(slipSensorB->getText(),false,setSensorsAtSlipFrame);
 Sensor* cSensor = getSensorFromEntry(slipSensorC->getText(),false,setSensorsAtSlipFrame);
 Sensor* dSensor = getSensorFromEntry(slipSensorD->getText(),false,setSensorsAtSlipFrame);
 // place or update signals as requested
 if ( (aSensor!=nullptr) && slipSensorA->addToPanel() )
 {
  if (isSensorOnPanel(aSensor) &&
             (aSensor!=getSensorFromName(layoutSlip->getSensorAName())) )
  {
         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
             tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
                     tr("Error"),JOptionPane::ERROR_MESSAGE);
   return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorA());
   placingBlock(getSensorIcon(slipSensorA->getText()), slipSensorA->isRightSelected(), 0.0);
//   removeAssignment(aSensor);
   layoutSlip->setSensorA(slipSensorA->getText());
   needRedraw = true;
  }
 }
 else if ( (aSensor!=nullptr) &&
         (aSensor!=getSensorFromName(layoutSlip->getSensorAName())) &&
         (aSensor!=getSensorFromName(layoutSlip->getSensorBName())) &&
         (aSensor!=getSensorFromName(layoutSlip->getSensorCName())) &&
         (aSensor!=getSensorFromName(layoutSlip->getSensorDName())) )
 {
  if (isSensorOnPanel(aSensor))
  {
//      JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//          tr("SensorsError13"),
//              new Object[]{slipSensorA->text()}),
//                  tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot assign signal head \"%1\" to this block boundary\n                                                             because it is already on the panel at a different place.").arg(slipSensorA->getText()));
      return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorA());
//   removeAssignment(aSensor);
   layoutSlip->setSensorA(slipSensorA->getText());
  }
 }
 else if ( (aSensor!=nullptr) &&
         ( (aSensor==getSensorFromName(layoutSlip->getSensorBName())) ||
             (aSensor==getSensorFromName(layoutSlip->getSensorCName())) ||
             (aSensor==getSensorFromName(layoutSlip->getSensorDName())) ) )
 {
  // need to figure out what to do in this case.
 }
 else if (aSensor==nullptr)
 {
  removeSensorFromPanel(layoutSlip->getSensorA());
  layoutSlip->setSensorA("");
 }
 if ( (bSensor!=nullptr) && slipSensorB->addToPanel() )
 {
  if (isSensorOnPanel(bSensor) &&
             (bSensor!=getSensorFromName(layoutSlip->getSensorBName())))
  {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                 new Object[]{slipSensorB->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\n                                                             because it is already on the panel.").arg(slipSensorB->getText()));
   return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorB());
   placingBlockB(getSensorIcon(slipSensorB->getText()), slipSensorB->isRightSelected(), 0.0);
//   removeAssignment(bSensor);
   layoutSlip->setSensorB(slipSensorB->getText());
   needRedraw = true;
  }
 }
 else if ( (bSensor!=nullptr) &&
         (bSensor!=getSensorFromName(layoutSlip->getSensorAName())) &&
         (bSensor!=getSensorFromName(layoutSlip->getSensorBName())) &&
         (bSensor!=getSensorFromName(layoutSlip->getSensorCName())) &&
         (bSensor!=getSensorFromName(layoutSlip->getSensorDName())) )
 {
  if (isSensorOnPanel(bSensor))
  {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("SensorsError13"),
//                 new Object[]{slipSensorB->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\n                                                                because it is already on the panel at a different place.").arg(slipSensorB->getText()));
   return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorB());
//   removeAssignment(bSensor);
   layoutSlip->setSensorB(slipSensorB->getText());
  }
 }
 else if ( (bSensor!=nullptr) &&
         ( (bSensor==getSensorFromName(layoutSlip->getSensorAName())) ||
             (bSensor==getSensorFromName(layoutSlip->getSensorCName())) ||
             (bSensor==getSensorFromName(layoutSlip->getSensorDName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (bSensor==nullptr)
 {
  removeSensorFromPanel(layoutSlip->getSensorB());
  layoutSlip->setSensorB("");
 }
 if ( (cSensor!=nullptr) && slipSensorC->addToPanel() )
 {
  if (isSensorOnPanel(cSensor) &&
             (cSensor!=getSensorFromName(layoutSlip->getSensorCName())) )
  {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                 new Object[]{slipSensorC->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\n                                                             because it is already on the panel.").arg(slipSensorC->getText()));
   return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorC());
   placingBlockC(getSensorIcon(slipSensorC->getText()), slipSensorC->isRightSelected(), 0.0);
//   removeAssignment(cSensor);
   layoutSlip->setSensorC(slipSensorC->getText());
   needRedraw = true;
  }
 }
 else if ( (cSensor!=nullptr) &&
         (cSensor!=getSensorFromName(layoutSlip->getSensorAName())) &&
         (cSensor!=getSensorFromName(layoutSlip->getSensorBName())) &&
         (cSensor!=getSensorFromName(layoutSlip->getSensorCName())) &&
         (cSensor!=getSensorFromName(layoutSlip->getSensorDName())) )
 {
     if (isSensorOnPanel(cSensor)) {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("SensorsError13"),
//                 new Object[]{slipSensorC->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
         QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\n                                                                because it is already on the panel at a different place.").arg(slipSensorC->getText()));return;
     }
     else {
         removeSensorFromPanel(layoutSlip->getSensorC());
//         removeAssignment(cSensor);
         layoutSlip->setSensorC(slipSensorC->getText());
     }
 }
 else if ( (cSensor!=nullptr) &&
         ( (cSensor==getSensorFromName(layoutSlip->getSensorBName())) ||
             (cSensor==getSensorFromName(layoutSlip->getSensorAName())) ||
             (cSensor==getSensorFromName(layoutSlip->getSensorDName())) ) ) {
// need to figure out what to do in this case.
 }
 else if (cSensor==nullptr) {
     removeSensorFromPanel(layoutSlip->getSensorC());
     layoutSlip->setSensorC("");
 }
 if ( (dSensor!=nullptr) && slipSensorD->addToPanel() )
 {
     if (isSensorOnPanel(dSensor) &&
             (dSensor!=getSensorFromName(layoutSlip->getSensorDName())) ) {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("Error - Cannot place sensor \"%1\" on the panel\nbecause it is already on the panel."),
//                 new Object[]{slipSensorD->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
      QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot place sensor \"%1\" on the panel\n                                                             because it is already on the panel.").arg(slipSensorD->getText()));
         return;
     }
     else {
         removeSensorFromPanel(layoutSlip->getSensorD());
         placingBlockD(getSensorIcon(slipSensorD->getText()), slipSensorD->isRightSelected(), 0.0);
//         removeAssignment(dSensor);
         layoutSlip->setSensorD(slipSensorD->getText());
         needRedraw = true;
     }
 }
 else if ( (dSensor!=nullptr) &&
         (dSensor!=getSensorFromName(layoutSlip->getSensorAName())) &&
         (dSensor!=getSensorFromName(layoutSlip->getSensorBName())) &&
         (dSensor!=getSensorFromName(layoutSlip->getSensorCName())) &&
         (dSensor!=getSensorFromName(layoutSlip->getSensorDName())) )
 {
  if (isSensorOnPanel(dSensor))
  {
//         JOptionPane::showMessageDialog(setSensorsAtSlipFrame,
//             tr("SensorsError13"),
//                 new Object[]{slipSensorD->text()}),
//                     tr("Error"),JOptionPane::ERROR_MESSAGE);
   QMessageBox::critical(setSensorsAtSlipFrame, tr("Error"), tr("Error - Cannot assign sensor \"%1\" to this block boundary\n                                                                because it is already on the panel at a different place.").arg(slipSensorD->getText()));
   return;
  }
  else
  {
   removeSensorFromPanel(layoutSlip->getSensorD());
//   removeAssignment(dSensor);
   layoutSlip->setSensorD(slipSensorD->getText());
  }
 }
 else if ( (dSensor!=nullptr) &&
         ( (dSensor==getSensorFromName(layoutSlip->getSensorBName())) ||
             (dSensor==getSensorFromName(layoutSlip->getSensorCName())) ||
             (dSensor==getSensorFromName(layoutSlip->getSensorAName())) ) )
 {
  // need to figure out what to do in this case.
 }
 else if (dSensor==nullptr)
 {
  removeSensorFromPanel(layoutSlip->getSensorD());
  layoutSlip->setSensorD("");
 }
 // setup logic if requested
 // finish up
 setSensorsAtSlipOpenFlag = false;
 setSensorsAtSlipFrame->setVisible(false);
 setSensorsAtSlipFromMenuFlag = false;
 if (needRedraw)
 {
  layoutEditor->redrawPanel();
  needRedraw = false;
  layoutEditor->setDirty();
 }
}

BeanDetails::BeanDetails(QString beanType, Manager* manager) : QObject()
{
 beanCombo = new NamedBeanComboBox(manager);
 beanCombo->setAllowNull(true);
 //JComboBoxUtil.setupComboBoxMaxRows(beanCombo);
 //I18N translate from type (Sensor) to BeanNameSensor
 //to use NamedBeanBundle property
 if ("Sensor" == (beanType)) {
     bundleName = "Sensor";
 } else if ("SignalMast"== (beanType)) {
     bundleName = "SignalMast";
 } else {
//     log.error("Unexpected value for BeanDetails: '{}'", beanType);
     bundleName = beanType;
 }
 beanString = /*Bundle.getMessage*/(bundleName);
 textLabel = new JLabel(beanString);
 this->manager = manager;
 //this.beanType = beanType;

 buttonGroup->addButton(addBeanCheck);
 buttonGroup->addButton(left);
 buttonGroup->addButton(right);
 addBeanCheck->setChecked(true);

 boundaryBlocks->setAlignment(Qt::AlignCenter);
 //boundaryBlocks->setOpaque(false);
 detailsPanel->setLayout(new BorderLayout());
 //detailsPanel.setBorder(BorderFactory.createTitledBorder(blackline, Bundle.getMessage("BlockBoundary")));
 detailsPanel->setTitle(tr("Block Boundary"));
 boundaryLabel->setAlignment(/*Component.CENTER_ALIGNMENT*/Qt::AlignHCenter);

 JPanel* boundaryDetails = new JPanel(new FlowLayout());
 //boundaryDetails.setOpaque(false);
 boundaryDetails->setLayout(new QVBoxLayout());//boundaryDetails, BoxLayout.Y_AXIS));
 boundaryDetails->layout()->addWidget(boundaryLabel);
 boundaryDetails->layout()->addWidget(boundaryBlocks);

 ((BorderLayout*)detailsPanel->layout())->addWidget(boundaryDetails, BorderLayout::North);
 ((BorderLayout*)detailsPanel->layout())->addWidget(addIconPanel(), BorderLayout::Center);
 ((BorderLayout*)detailsPanel->layout())->addWidget(positionLeftRight(), BorderLayout::South);
}

void BeanDetails::setTextField(QString value)
{
 beanCombo->setSelectedItem(manager->getNamedBean(value));
}

QString BeanDetails::getText()
{
 return beanCombo->getSelectedItemDisplayName();
}

NamedBean* BeanDetails::getBean()
{
 return beanCombo->getSelectedItem();
}

QWidget* BeanDetails::getDetailsPanel()
{
 return detailsPanel;
}

bool BeanDetails::addToPanel()
{
 return !addBeanCheck->isChecked();
}

bool BeanDetails::isRightSelected()
{
 return right->isChecked();
}

void BeanDetails::setBoundaryTitle(QString text)
{
//        detailsPanel->setBorder(BorderFactory.createTitledBorder(blackline, text));
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 detailsPanel->setStyleSheet(gbStyleSheet);
 detailsPanel->setTitle(text);
}

void BeanDetails::setBoundaryLabelText(QString text)
{
 boundaryLabel->setText(text);
}

void BeanDetails::setBoundaryLabel(QString label)
{
 boundaryBlocks->setText(label);
}

NamedBeanComboBox* BeanDetails::getCombo()
{
 return beanCombo;
}

QWidget* BeanDetails::positionLeftRight()
{
 QWidget* placementPanel = new QWidget();
//        placementPanel->setBorder(BorderFactory.createTitledBorder(blackline, tr("PlaceItem"),
//                        new Object[]{beanString})));
 placementPanel->setLayout(new QVBoxLayout(placementPanel/*, BoxLayout.Y_AXIS*/));
 //placementPanel->setOpaque(false);
 placementPanel->layout()->addWidget(addBeanCheck);
 placementPanel->layout()->addWidget(left);
 placementPanel->layout()->addWidget(right);
//        addBeanCheck->setOpaque(false);
//        left->setOpaque(false);
//        right->setOpaque(false);

 addBeanCheck->setToolTip(tr("Check to place icon for above %1 on panel near anchor point.").arg(beanString));

 right->setToolTip(tr("Place %1 on the right hand side of the track as if you were facing it").arg(beanString));

 left->setToolTip(tr("Place %1 on the left hand side of the track as if you were facing it").arg(beanString));
 return placementPanel;
}

QWidget* BeanDetails::addIconPanel()
{
 QWidget*addBeanPanel = new QWidget();
//        addBeanPanel->setOpaque(false);
 addBeanPanel->setLayout(new QHBoxLayout());
 addBeanPanel->layout()->addWidget(textLabel);
//        textLabel->setOpaque(false);
 addBeanPanel->layout()->addWidget(beanCombo);
 return addBeanPanel;
}

/*public*/ void LayoutEditorTools::setSlipFromMenu( LayoutSlip* ls,
        MultiIconEditor* theEditor, JFrame* theFrame )
    {
 layoutSlip = ls;

 setSignalsAtSlip(theEditor,theFrame);
}
/*public*/ void LayoutEditorTools::setSignalsAtSlipFromMenu(/*@Nonnull*/ LayoutSlip* ls,
            /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame)
{
    layoutSlip = ls;
    a1SlipSignalHeadComboBox->setSelectedItem(nullptr);
    a2SlipSignalHeadComboBox->setSelectedItem(nullptr);
    b1SlipSignalHeadComboBox->setSelectedItem(nullptr);
    b2SlipSignalHeadComboBox->setSelectedItem(nullptr);
    c1SlipSignalHeadComboBox->setSelectedItem(nullptr);
    c2SlipSignalHeadComboBox->setSelectedItem(nullptr);
    d1SlipSignalHeadComboBox->setSelectedItem(nullptr);
    d2SlipSignalHeadComboBox->setSelectedItem(nullptr);

    setSignalsAtSlipFromMenuFlag = true;
    setSignalsAtSlip(theEditor, theFrame);
    setSignalsAtSlipFromMenuFlag = false;
}

/*public*/ void LayoutEditorTools::setSignalsAtSlip( MultiIconEditor* theEditor, JFrame* theFrame )
{
 signalIconEditor = theEditor;
 signalFrame = theFrame;

 //Initialize if needed
 if (setSignalsAtSlipFrame == nullptr) {
  setSignalsAtSlipOpenFlag = false;
  setSignalsAtSlipFrame = new JmriJFrameX(tr("Set Signal Heads at a Slip"), false, true);
  oneFrameToRuleThemAll(setSignalsAtSlipFrame);
  setSignalsAtSlipFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
  setSignalsAtSlipFrame->addHelpMenu("package.jmri.jmrit.display.SetSignalsAtSlip", true);
  setSignalsAtSlipFrame->setLocation(70, 30);
  QFont font;
  font.setPointSize(8);
  setSignalsAtSlipFrame->setFont(font);//  QWidget* theContentPane = setSignalsAtSlipFrame->getContentPane();
//  theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
  QScrollArea* scrollArea = new QScrollArea();
  QWidget* theContentPane = new QWidget();
  theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.Y_AXIS));
  scrollArea->setWidget(theContentPane);
  scrollArea->setWidgetResizable(true);
  setSignalsAtSlipFrame->setCentralWidget(scrollArea);

  JPanel* panel1 = new JPanel(new FlowLayout());
  JLabel* turnout1NameLabel = new JLabel(tr("Slip") + " "
          + tr("Name"));
  panel1->layout()->addWidget(turnout1NameLabel);
  panel1->layout()->addWidget(slipNameComboBox);
  for (LayoutSlip* slip : layoutEditor->getLayoutSlips()) {
      slipNameComboBox->addItem(slip->getDisplayName());
  }

  slipNameComboBox->insertItem(0,"");

  if (layoutSlip != nullptr) {
      slipNameComboBox->setCurrentText(layoutSlip->getDisplayName());
      getSlipTurnoutSignalsGetSaved(/*null*/);
  } else {
      slipNameComboBox->setCurrentIndex(0);
  }
  //slipNameComboBox.addActionListener((ActionEvent e) -> {
  connect(slipNameComboBox, &QComboBox::currentTextChanged, [=]{
      for (LayoutSlip* slip : layoutEditor->getLayoutSlips()) {
          if (slip->getDisplayName() == (slipNameComboBox->currentText())) {
              //slip1NameField.setText(slip.getDisplayName());
              getSlipTurnoutSignalsGetSaved(/*e*/);
              bool enable = (slip->getSlipType() == LayoutSlip::DOUBLE_SLIP);
              dblSlipC2SigPanel->setVisible(enable);
              dblSlipB2SigPanel->setVisible(enable);
              setSignalsAtSlipFrame->pack();
              return;
          }
      }
  });
  theContentPane->layout()->addWidget(panel1);
  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  JPanel* panel2a = new JPanel(new FlowLayout());
  panel2a->layout()->addWidget(new JLabel("   "));
  panel2a->layout()->addWidget(setPlaceAllHeads);
  setPlaceAllHeads->setToolTip(tr("Check to place all signal head icons"));
  //setPlaceAllHeads.addActionListener((ActionEvent e) -> {
  connect(setPlaceAllHeads, &QCheckBox::clicked, [=]{
      bool isSelected = setPlaceAllHeads->isChecked();
      //(de)select all checkboxes
      setA1SlipHead->setChecked(isSelected);
      setA2SlipHead->setChecked(isSelected);
      setB1SlipHead->setChecked(isSelected);
      setB2SlipHead->setChecked(isSelected);
      setC1SlipHead->setChecked(isSelected);
      setC2SlipHead->setChecked(isSelected);
      setD1SlipHead->setChecked(isSelected);
      setD2SlipHead->setChecked(isSelected);
  });
  panel2a->layout()->addWidget(new JLabel("  "));
  panel2a->layout()->addWidget(setupAllLogic);
  setupAllLogic->setToolTip(tr("SetAllLogicHint"));
  //setupAllLogic.addActionListener((ActionEvent e) -> {
  connect(setupAllLogic, &QCheckBox::clicked, [=]{
      bool isSelected = setupAllLogic->isChecked();
      //(de)select all checkboxes
      setupA1SlipLogic->setChecked(isSelected);
      setupA2SlipLogic->setChecked(isSelected);
      setupB1SlipLogic->setChecked(isSelected);
      setupB2SlipLogic->setChecked(isSelected);
      setupC1SlipLogic->setChecked(isSelected);
      setupC2SlipLogic->setChecked(isSelected);
      setupD1SlipLogic->setChecked(isSelected);
      setupD2SlipLogic->setChecked(isSelected);
  });
  theContentPane->layout()->addWidget(panel2a);
  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  //Signal heads located at turnout 1
  JPanel* panel21x = new JPanel(new FlowLayout());
  panel21x->layout()->addWidget(new JLabel(tr("Signal located at")
          + " " + tr("Turnout") + " 1 - "
          + tr("continuing track")));
  theContentPane->layout()->addWidget(panel21x);

  JPanel* panel21 = new JPanel(new FlowLayout());
  panel21->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 2 - "
          + tr("continuing track")));
  panel21->layout()->addWidget(a1SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel21);
  a1SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel22 = new JPanel(new FlowLayout());
  panel22->layout()->addWidget(new JLabel(tr("Or Both") + " 2 " + tr("Tracks)") + "	  "));
  panel22->layout()->addWidget(setA1SlipHead);
  setA1SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel22->layout()->addWidget(new JLabel("  "));
  panel22->layout()->addWidget(setupA1SlipLogic);
  setupA1SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel22);

  JPanel* panel23 = new JPanel(new FlowLayout());
  panel23->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 2 - "
          + tr("Protects Turnout")));
  panel23->layout()->addWidget(a2SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel23);
  a2SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel24 = new JPanel(new FlowLayout());
  panel24->layout()->addWidget(new JLabel("				"));
  panel24->layout()->addWidget(setA2SlipHead);
  setA2SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel24->layout()->addWidget(new JLabel("  "));
  panel24->layout()->addWidget(setupA2SlipLogic);
  setupA2SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel24);

  JPanel* panel31x = new JPanel(new FlowLayout());
  panel31x->layout()->addWidget(new JLabel(tr("Signal located at")
          + " " + tr("Turnout") + " 1 - "
          + tr("Protects Turnout")));
  theContentPane->layout()->addWidget(panel31x);

  JPanel* panel31 = new JPanel(new FlowLayout());
  panel31->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 2 - "
          + tr("continuing track")));
  panel31->layout()->addWidget(b1SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel31);
  b1SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel32 = new JPanel(new FlowLayout());
  panel32->layout()->addWidget(new JLabel(tr("Or Both") + " 2 " + tr("Tracks)") + "	  "));
  panel32->layout()->addWidget(setB1SlipHead);
  setB1SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel32->layout()->addWidget(new JLabel("  "));
  panel32->layout()->addWidget(setupB1SlipLogic);
  setupB1SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel32);

  dblSlipB2SigPanel = new JPanel(new FlowLayout());
  dblSlipB2SigPanel->setLayout(new QVBoxLayout());//dblSlipB2SigPanel, BoxLayout.Y_AXIS));

  JPanel* panel33 = new JPanel(new FlowLayout());
  panel33->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 2 - "
          + tr("diverging track")));
  panel33->layout()->addWidget(b2SlipSignalHeadComboBox);
  dblSlipB2SigPanel->layout()->addWidget(panel33);
  b2SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel34 = new JPanel(new FlowLayout());
  panel34->layout()->addWidget(new JLabel("				"));
  panel34->layout()->addWidget(setB2SlipHead);
  setB2SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel34->layout()->addWidget(new JLabel("  "));
  panel34->layout()->addWidget(setupB2SlipLogic);
  setupB2SlipLogic->setToolTip(tr("SetLogicHint"));
  dblSlipB2SigPanel->layout()->addWidget(panel34);

  theContentPane->layout()->addWidget(dblSlipB2SigPanel);
  dblSlipB2SigPanel->setVisible(false);
  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  //Signal heads located at turnout 2

  JPanel* panel41x = new JPanel(new FlowLayout());
  panel41x->layout()->addWidget(new JLabel(tr("Signal located at")
          + " " + tr("Turnout") + " 2 - "
          + tr("continuing track")));
  theContentPane->layout()->addWidget(panel41x);

  JPanel* panel41 = new JPanel(new FlowLayout());
  panel41->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 2 - "
          + tr("continuing track")));
  panel41->layout()->addWidget(c1SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel41);
  c1SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel42 = new JPanel(new FlowLayout());
  panel42->layout()->addWidget(new JLabel(tr("Or Both") + " 1 " + tr("Tracks)") + "	  "));
  panel42->layout()->addWidget(setC1SlipHead);
  setC1SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel42->layout()->addWidget(new JLabel("  "));
  panel42->layout()->addWidget(setupC1SlipLogic);
  setupC1SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel42);
  dblSlipC2SigPanel = new JPanel(new FlowLayout());
  dblSlipC2SigPanel->setLayout(new QVBoxLayout());//dblSlipC2SigPanel, BoxLayout.Y_AXIS));

  JPanel* panel43 = new JPanel(new FlowLayout());
  panel43->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 1 - "
          + tr("diverging track")));
  panel43->layout()->addWidget(c2SlipSignalHeadComboBox);
  dblSlipC2SigPanel->layout()->addWidget(panel43);
  c2SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel44 = new JPanel(new FlowLayout());
  panel44->layout()->addWidget(new JLabel("				"));
  panel44->layout()->addWidget(setC2SlipHead);
  setC2SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel44->layout()->addWidget(new JLabel("  "));
  panel44->layout()->addWidget(setupC2SlipLogic);
  setupC2SlipLogic->setToolTip(tr("SetLogicHint"));
  dblSlipC2SigPanel->layout()->addWidget(panel44);
  theContentPane->layout()->addWidget(dblSlipC2SigPanel);

  JPanel* panel51x = new JPanel(new FlowLayout());
  panel51x->layout()->addWidget(new JLabel(tr("Signal located at")
          + " " + tr("Turnout") + " 2 - "
          + tr("Protects Turnout")));
  theContentPane->layout()->addWidget(panel51x);

  JPanel* panel51 = new JPanel(new FlowLayout());
  panel51->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 1 - "
          + tr("continuing track")));
  panel51->layout()->addWidget(d1SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel51);
  d1SlipSignalHeadComboBox->setToolTip(tr("SignalHeadNameHint"));

  JPanel* panel52 = new JPanel(new FlowLayout());
  panel52->layout()->addWidget(new JLabel(tr("Or Both") + " 1 " + tr("Tracks)") + "	  "));
  panel52->layout()->addWidget(setD1SlipHead);
  setD1SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel52->layout()->addWidget(new JLabel("  "));
  panel52->layout()->addWidget(setupD1SlipLogic);
  setupD1SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel52);

  JPanel* panel53 = new JPanel(new FlowLayout());
  panel53->layout()->addWidget(new JLabel(
          tr("Protects Turnout") + " 1 - "
          + tr("diverging track")));
  panel53->layout()->addWidget(d2SlipSignalHeadComboBox);
  theContentPane->layout()->addWidget(panel53);
  d2SlipSignalHeadComboBox->setToolTip(tr("Enter name (system or user) of signal head located here."));

  JPanel* panel54 = new JPanel(new FlowLayout());
  panel54->layout()->addWidget(new JLabel("				"));
  panel54->layout()->addWidget(setD2SlipHead);
  setD2SlipHead->setToolTip(tr("PlaceHeadHint"));
  panel54->layout()->addWidget(new JLabel("  "));
  panel54->layout()->addWidget(setupD2SlipLogic);
  setupD2SlipLogic->setToolTip(tr("SetLogicHint"));
  theContentPane->layout()->addWidget(panel54);
  theContentPane->layout()->addWidget(new JSeparator(JSeparator::HORIZONTAL));

  JPanel* panel6 = new JPanel(new FlowLayout());
  panel6->layout()->addWidget(changeTToTSignalIcon = new QPushButton(tr("Change Signal Head Icon")));
  //changeTToTSignalIcon.addActionListener((ActionEvent e) -> {
    connect(changeTToTSignalIcon, &QPushButton::clicked, [=]{
      signalFrame->setVisible(true);
  });
  changeTToTSignalIcon->setToolTip(tr("Select to change icons used to represent signal heads (Use left-facing icons)"));
  panel6->layout()->addWidget(new JLabel("	 "));
  panel6->layout()->addWidget(setSlipSignalsDone = new QPushButton(tr("Done")));
  //setSlipSignalsDone.addActionListener((ActionEvent e) -> {
    connect(setSlipSignalsDone, &QPushButton::clicked, [=]{
      setSlipSignalsDonePressed(/*e*/);
  });
  setSlipSignalsDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));
  panel6->layout()->addWidget(setSlipSignalsCancel = new QPushButton(tr("Cancel")));
  //setSlipSignalsCancel.addActionListener((ActionEvent e) -> {
  connect(setSlipSignalsCancel, &QPushButton::clicked, [=]{
      setSlipSignalsCancelPressed(/*e*/);
  });
  setSlipSignalsCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
  theContentPane->layout()->addWidget(panel6);
  setSignalsAtSlipFrame->addWindowListener(new SASWindowListener(this));//
//  {
//      @Override
//      public void windowClosing(WindowEvent e) {
//          setSlipSignalsCancelPressed(null);
//      }
//  });
 }
 setPlaceAllHeads->setChecked(false);
 setupAllLogic->setChecked(false);

 bool enable = (layoutSlip != nullptr
      && layoutSlip->getSlipType() == LayoutSlip::DOUBLE_SLIP);
 dblSlipC2SigPanel->setVisible(enable);
 dblSlipB2SigPanel->setVisible(enable);

 if (setSignalsAtSlipFromMenuFlag) {
  getSlipTurnoutSignalsGetSaved(/*null*/);
 }

 if (!setSignalsAtSlipOpenFlag) {
  setSignalsAtSlipFrame->resize(QSize());
  setSignalsAtSlipFrame->pack();
  setSignalsAtSlipOpenFlag = true;
 }
 setSignalsAtSlipFrame->setVisible(true);
}

/*private*/ void LayoutEditorTools::getSlipTurnoutSignalsGetSaved (JActionEvent* /*a*/)
{
 if ( !getSlipTurnoutInformation() ) return;
 a1SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalA1());
 a2SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalA2());
 b1SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalB1());
 b2SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalB2());
 c1SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalC1());
 c2SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalC2());
 d1SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalD1());
 d2SlipSignalHeadComboBox->setSelectedItem(layoutSlip->getSignalD2());
}

/*private*/ void LayoutEditorTools::setSlipSignalsCancelPressed (JActionEvent* /*a*/)
{
 setSignalsAtSlipOpenFlag = false;
 setSignalsAtSlipFrame->setVisible(false);
}

/*private*/ bool LayoutEditorTools::getSlipTurnoutInformation()
{
 QString str = "";
 turnout1 = NULL;
 turnout2 = NULL;
 layoutSlip = NULL;
 foreach(LayoutSlip* ls, layoutEditor->getLayoutSlips())
 {
  if(ls->getDisplayName()==(slipNameComboBox->currentText()))
  {
   turnout1 = ls->getTurnout();
   turnout2 = ls->getTurnoutB();
   layoutSlip=ls;
   layoutTurnout = layoutSlip;
   break;
  }
 }
 if(layoutSlip==nullptr){
     return false;
 }
 if (turnout1==nullptr)
 {
  JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
      tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
          str), tr("Error"),JOptionPane::ERROR_MESSAGE);
  return false ;
 }
 if (turnout2==nullptr)
 {
  JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
      tr("Error - No turnout is defined for \"%1\". Please enter \na turnout name in the Turnout Table and on the panel.").arg(
              str), tr("Error"),JOptionPane::ERROR_MESSAGE);
  return false ;
 }
 return true;
}

/*private*/ void LayoutEditorTools::setSlipSignalsDonePressed (JActionEvent* /*a*/) {
    if ( !getSlipTurnoutInformation() ) return;
    if ( !getSlipSignalHeadInformation() ) return;

    // place signal icons if requested, and assign signal heads to this turnout
    QString signalHeadName = a1SlipSignalHeadComboBox->getSelectedItemDisplayName();
    if (setA1SlipHead->isChecked()) {
        if (isHeadOnPanel(a1SlipHead) &&
            (a1SlipHead!=getHeadFromName(layoutSlip->getSignalB1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalA1Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeA1Slip(signalHeadName);
            else
                placeB1Slip(signalHeadName);
            removeAssignment(a1SlipHead);
            layoutSlip->setSignalA1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(a1SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a1SlipHead) &&
                                isHeadAssignedAnywhere(a1SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalB1Name());
                removeAssignment(a1SlipHead);
                layoutSlip->setSignalA1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case - assigned to a different position on the same turnout.
        }
    }
    signalHeadName = a2SlipSignalHeadComboBox->getSelectedItemDisplayName();

    if ( (a2SlipHead!=nullptr) && setA2SlipHead->isChecked() ) {
        if (isHeadOnPanel(a2SlipHead) &&
            (a2SlipHead!=getHeadFromName(layoutSlip->getSignalB2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalB2Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeA2Slip(signalHeadName);
            else
                placeB2Slip(signalHeadName);
            removeAssignment(a2SlipHead);
            layoutSlip->setSignalA2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (a2SlipHead!=nullptr) {
        int assigned = isHeadAssignedHere(a2SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(a2SlipHead) &&
                                isHeadAssignedAnywhere(a2SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalA2Name());
                removeAssignment(a2SlipHead);
                layoutSlip->setSignalA2Name(signalHeadName);
            }
        }
        else if (assigned!=B2) {
// need to figure out what to do in this case.
        }
    }
    else if (a2SlipHead==nullptr) {
        removeSignalHeadFromPanel(layoutSlip->getSignalA2Name());
        layoutSlip->setSignalB2Name("");
    }

    signalHeadName = b1SlipSignalHeadComboBox->getSelectedItemDisplayName();
    if (setB1SlipHead->isChecked())
    {
        log->info(signalHeadName);
        if (isHeadOnPanel(b1SlipHead) &&
            (b1SlipHead!=getHeadFromName(layoutSlip->getSignalC1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
           return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalB1Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeB1Slip(signalHeadName);
            else
                placeA1Slip(signalHeadName);
            removeAssignment(b1SlipHead);
            layoutSlip->setSignalB1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(b1SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(b1SlipHead) &&
                                isHeadAssignedAnywhere(b1SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalB1Name());
                removeAssignment(b1SlipHead);
                layoutSlip->setSignalB1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
            // need to figure out what to do in this case.
        }
    }
    if(layoutSlip->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
     signalHeadName = b2SlipSignalHeadComboBox->getSelectedItemDisplayName();

        if ( (b2SlipHead!=nullptr) && setB2SlipHead->isChecked() ) {
            if (isHeadOnPanel(b2SlipHead) &&
                (b2SlipHead!=getHeadFromName(layoutSlip->getSignalC2Name()))) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalB2Name());
                if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                    placeB2Slip(signalHeadName);
                else
                    placeA2Slip(signalHeadName);
                removeAssignment(b2SlipHead);
                layoutSlip->setSignalB2Name(signalHeadName);
                needRedraw = true;
            }
        }
        else if (b2SlipHead!=nullptr) {
            int assigned = isHeadAssignedHere(b2SlipHead,layoutSlip);
            if (assigned == NONE) {
                if ( isHeadOnPanel(b2SlipHead) &&
                                    isHeadAssignedAnywhere(b2SlipHead) ) {
                    JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                        tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                            signalHeadName),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                    return;
                }
                else {
                    removeSignalHeadFromPanel(layoutSlip->getSignalB2Name());
                    removeAssignment(b2SlipHead);
                    layoutSlip->setSignalB2Name(signalHeadName);
                }
            }
            else if (assigned!=C2) {
// need to figure out what to do in this case.
            }
        }
        else if (b2SlipHead==nullptr) {
            removeSignalHeadFromPanel(layoutSlip->getSignalB2Name());
            layoutSlip->setSignalB2Name("");
        }
    } else {
        if(b2SlipHead!=nullptr){
            BlockBossLogic::getStoppedObject(layoutSlip->getSignalB2Name());
            removeSignalHeadFromPanel(layoutSlip->getSignalB2Name());
            layoutSlip->setSignalB2Name("");
            b2SlipHead=NULL;
        }
    }
    // signal heads on turnout 2
    if (setC1SlipHead->isChecked()) {
     signalHeadName = c1SlipSignalHeadComboBox->getSelectedItemDisplayName();
        if (isHeadOnPanel(c1SlipHead) &&
            (c1SlipHead!=getHeadFromName(layoutSlip->getSignalB1Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalC1Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeC1Slip(signalHeadName);
            else
                placeD1Slip(signalHeadName);
            removeAssignment(c1SlipHead);
            layoutSlip->setSignalC1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(c1SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(c1SlipHead) &&
                                isHeadAssignedAnywhere(c1SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalC1Name());
                removeAssignment(c1SlipHead);
                layoutSlip->setSignalC1Name(signalHeadName);
            }
        }
        else if (assigned!=B1) {
// need to figure out what to do in this case.
        }
    }
    if(layoutSlip->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
     signalHeadName = c2SlipSignalHeadComboBox->getSelectedItemDisplayName();

        if ( (c2SlipHead!=nullptr) && setC2SlipHead->isChecked() ) {
            if (isHeadOnPanel(c2SlipHead) &&
                (c2SlipHead!=getHeadFromName(layoutSlip->getSignalB2Name()))) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalC2Name());
                if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                    placeC2Slip(signalHeadName);
                else
                    placeD2Slip(signalHeadName);
                removeAssignment(c2SlipHead);
                layoutSlip->setSignalC2Name(signalHeadName);
                needRedraw = true;
            }
        }
        else if (c2SlipHead!=nullptr) {
            int assigned = isHeadAssignedHere(c2SlipHead,layoutSlip);
            if (assigned == NONE) {
                if ( isHeadOnPanel(c2SlipHead) &&
                                    isHeadAssignedAnywhere(c2SlipHead) ) {
                    JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                        tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                            signalHeadName),
                                tr("Error"),JOptionPane::ERROR_MESSAGE);
                    return;
                }
                else {
                    removeSignalHeadFromPanel(layoutSlip->getSignalC2Name());
                    removeAssignment(c2SlipHead);
                    layoutSlip->setSignalC2Name(signalHeadName);
                }
            }
            else if (assigned!=B2) {
// need to figure out what to do in this case.
            }
        }
        else if (c2SlipHead==nullptr) {
            removeSignalHeadFromPanel(layoutSlip->getSignalC2Name());
            layoutSlip->setSignalC2Name("");
        }
    } else {
        if(c2SlipHead!=nullptr){
            BlockBossLogic::getStoppedObject(layoutSlip->getSignalC2Name());
            removeSignalHeadFromPanel(layoutSlip->getSignalC2Name());
            layoutSlip->setSignalC2Name("");
            c2SlipHead=NULL;
        }
    }
    if (setD1SlipHead->isChecked()) {
        if (isHeadOnPanel(d1SlipHead) &&
            (d1SlipHead!=getHeadFromName(layoutSlip->getSignalC1Name()))) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalD1Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeD1Slip(signalHeadName);
            else
                placeC1Slip(signalHeadName);
            removeAssignment(d1SlipHead);
            layoutSlip->setSignalD1Name(signalHeadName);
            needRedraw = true;
        }
    }
    else {
        int assigned = isHeadAssignedHere(d1SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d1SlipHead) &&
                                isHeadAssignedAnywhere(d1SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalD1Name());
                removeAssignment(d1SlipHead);
                layoutSlip->setSignalD1Name(signalHeadName);
            }
        }
        else if (assigned!=C1) {
// need to figure out what to do in this case.
        }
    }

    signalHeadName = d2SlipSignalHeadComboBox->getSelectedItemDisplayName();
    if ( (d2SlipHead!=nullptr) && setD2SlipHead->isChecked() ) {
        if (isHeadOnPanel(d2SlipHead) &&
            (d2SlipHead!=getHeadFromName(layoutSlip->getSignalC2Name()))) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Error - Cannot place signal head \"%1\" on the panel\nbecause it is already on the panel.").arg(
                    signalHeadName),
                        tr("Error"),JOptionPane::ERROR_MESSAGE);
            return;
        }
        else {
            removeSignalHeadFromPanel(layoutSlip->getSignalD2Name());
            if (layoutSlip->getContinuingSense()==Turnout::CLOSED)
                placeD2Slip(signalHeadName);
            else
                placeC2Slip(signalHeadName);
            removeAssignment(d2SlipHead);
            layoutSlip->setSignalD2Name(signalHeadName);
            needRedraw = true;
        }
    }
    else if (d2SlipHead!=nullptr) {
        int assigned = isHeadAssignedHere(d2SlipHead,layoutSlip);
        if (assigned == NONE) {
            if ( isHeadOnPanel(d2SlipHead) &&
                                isHeadAssignedAnywhere(d2SlipHead) ) {
                JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                    tr("Error - Cannot assign signal head \"%1\" to this turnout\nbecause it is already on the panel at a different place.").arg(
                        signalHeadName),
                            tr("Error"),JOptionPane::ERROR_MESSAGE);
                return;
            }
            else {
                removeSignalHeadFromPanel(layoutSlip->getSignalD2Name());
                removeAssignment(d2SlipHead);
                layoutSlip->setSignalD2Name(signalHeadName);
            }
        }
        else if (assigned!=C2) {
// need to figure out what to do in this case.
        }
    }
    else if (d2SlipHead==nullptr) {
        removeSignalHeadFromPanel(layoutSlip->getSignalD2Name());
        layoutSlip->setSignalD2Name("");
    }
    // setup logic if requested
    if (setupA1SlipLogic->isChecked() || setupA2SlipLogic->isChecked()) {
        setLogicSlip(a1SlipHead,(TrackSegment*)layoutSlip->getConnectC(),a2SlipHead,
                (TrackSegment*)layoutSlip->getConnectD(),setupA1SlipLogic->isChecked(),
                setupA2SlipLogic->isChecked(),layoutSlip, layoutSlip->getTurnout(),
                   layoutSlip->getTurnoutB(), LayoutSlip::STATE_AC, LayoutSlip::STATE_AD, 0);
    }
    if (setupB1SlipLogic->isChecked() || setupB2SlipLogic->isChecked()) {
        setLogicSlip(b1SlipHead,(TrackSegment*)layoutSlip->getConnectD(),b2SlipHead,
                (TrackSegment*)layoutSlip->getConnectC(),setupB1SlipLogic->isChecked(),
                setupB2SlipLogic->isChecked(),layoutSlip, layoutSlip->getTurnout(),
                  layoutSlip->getTurnoutB(), LayoutSlip::STATE_BD, LayoutSlip::STATE_BC, 2);
    }
    if (setupC1SlipLogic->isChecked() || setupC2SlipLogic->isChecked()) {
        setLogicSlip(c1SlipHead,(TrackSegment*)layoutSlip->getConnectA(),c2SlipHead,
                (TrackSegment*)layoutSlip->getConnectB(),setupC1SlipLogic->isChecked(),
                setupC2SlipLogic->isChecked(),layoutSlip, layoutSlip->getTurnoutB(),
                 layoutSlip->getTurnout(),LayoutSlip::STATE_AC, LayoutSlip::STATE_BC, 4);
    }
    if (setupD1SlipLogic->isChecked() || setupD2SlipLogic->isChecked()) {
        setLogicSlip(d1SlipHead,(TrackSegment*)layoutSlip->getConnectB(),d2SlipHead,
                (TrackSegment*)layoutSlip->getConnectA(),setupD1SlipLogic->isChecked(),
                setupD2SlipLogic->isChecked(),layoutSlip, layoutSlip->getTurnoutB(),
                 layoutSlip->getTurnout(),LayoutSlip::STATE_BD, LayoutSlip::STATE_AD, 6);
    }
    // finish up
    setSignalsAtSlipOpenFlag = false;
    setSignalsAtSlipFrame->setVisible(false);
    if (needRedraw) {
        layoutEditor->redrawPanel();
        needRedraw = false;
        layoutEditor->setDirty();
    }
}
/*private*/ bool LayoutEditorTools::getSlipSignalHeadInformation() {
 a1SlipHead = getSignalHeadFromEntry(a1SlipSignalHeadComboBox, true, setSignalsAtSlipFrame);
 if (a1SlipHead == nullptr) {
     return false;
 }
 a2SlipHead = getSignalHeadFromEntry(a2SlipSignalHeadComboBox, false, setSignalsAtSlipFrame);

 b1SlipHead = getSignalHeadFromEntry(b1SlipSignalHeadComboBox, true, setSignalsAtSlipFrame);
 if (b1SlipHead == nullptr) {
     return false;
 }
 b2SlipHead = getSignalHeadFromEntry(b2SlipSignalHeadComboBox, false, setSignalsAtSlipFrame);

 c1SlipHead = getSignalHeadFromEntry(c1SlipSignalHeadComboBox, true, setSignalsAtSlipFrame);
 if (c1SlipHead == nullptr) {
     return false;
 }
 c2SlipHead = getSignalHeadFromEntry(c2SlipSignalHeadComboBox, false, setSignalsAtSlipFrame);

 d1SlipHead = getSignalHeadFromEntry(d1SlipSignalHeadComboBox, true, setSignalsAtSlipFrame);
 if (d1SlipHead == nullptr) {
     return false;
 }
 d2SlipHead = getSignalHeadFromEntry(d2SlipSignalHeadComboBox, false, setSignalsAtSlipFrame);
    return true;
}

/*private*/ void LayoutEditorTools::placeA1Slip(QString headName) {
    // place head near the continuing track of turnout 1
    placingBlock(getSignalHeadIcon(headName), false, 0.0);
}
/*private*/ void LayoutEditorTools::placeA2Slip(QString headName) {
    SignalHeadIcon* l = getSignalHeadIcon(headName);
    placingBlock(l, false, (4+l->getHeight()));
}
/*private*/ void LayoutEditorTools::placeB1Slip(QString headName) {
    placingBlockB(getSignalHeadIcon(headName), true, 0.0);
}
/*private*/ void LayoutEditorTools::placeB2Slip(QString headName) {
    SignalHeadIcon* l = getSignalHeadIcon(headName);
    placingBlockB(l, true, (4+l->getHeight()));
}
/*private*/ void LayoutEditorTools::placeC1Slip(QString headName) {
    placingBlockC(getSignalHeadIcon(headName), false, 0.0);
}
/*private*/ void LayoutEditorTools::placeC2Slip(QString headName) {
    SignalHeadIcon* l = getSignalHeadIcon(headName);
    placingBlockC(l, false, (4+l->getHeight()));
}
/*private*/ void LayoutEditorTools::placeD1Slip(QString headName) {
    placingBlockD(getSignalHeadIcon(headName), true, 0.0);
}
/*private*/ void LayoutEditorTools::placeD2Slip(QString headName) {
 SignalHeadIcon* l = getSignalHeadIcon(headName);
 placingBlockD(l, true, (4+l->getHeight()));
}

/*private*/ void LayoutEditorTools::setLogicSlip(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2, bool setup1, bool setup2,  LayoutSlip* slip, Turnout* nearTurnout, Turnout* farTurnout, int continueState, int divergeState, int number)
{
    // initialize common components and ensure all is defined
    LayoutBlock*connectorBlock = slip->getLayoutBlock();
    Sensor* connectorOccupancy = NULL;
    if (connectorBlock==nullptr){
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    connectorOccupancy = connectorBlock->getOccupancySensor();
    if (connectorOccupancy==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                    connectorBlock->getUserName()),
                        NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }

    int nearState = layoutSlip->getTurnoutState(nearTurnout, continueState);
    int farState = layoutSlip->getTurnoutState(farTurnout, continueState);

    // setup signal head for continuing track of far turnout (or both tracks of far turnout)
    if ( (track1==nullptr) && setup1 ) {
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy = NULL;
    SignalHead* nextHead = NULL;
    if ( (track1!=nullptr) && setup1) {
        LayoutBlock* block = track1->getLayoutBlock();
        if (block==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
            return;
        }
        occupancy = block->getOccupancySensor();
        if (occupancy==nullptr) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                    block->getUserName()),
                        NULL,JOptionPane::INFORMATION_MESSAGE);
            return;
        }
        //need to sort this out???
        nextHead = getNextSignalFromObject(track1,slip,
                                    head->getSystemName(), setSignalsAtSlipFrame);
        if ( (nextHead==nullptr) && (!reachedEndBumper()) ) {
            JOptionPane::showMessageDialog(setSignalsFrame,
                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                    block->getUserName()),
                        NULL,JOptionPane::INFORMATION_MESSAGE);
            return;
        }
        if (secondHead!=nullptr)
        {
         // this head signals only the continuing track of the far turnout
         if (!initializeBlockBossLogic(head->getSystemName())) return;
         logic->setMode(BlockBossLogic::TRAILINGMAIN);
         if(farState==Turnout::THROWN)
             logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
         logic->setTurnout(farTurnout->getSystemName());
         logic->setSensor1(occupancy->getSystemName());
         if (occupancy!=connectorOccupancy)
             logic->setSensor2(connectorOccupancy->getSystemName());
         if (nextHead!=nullptr) {
             logic->setWatchedSignal1(nextHead->getSystemName(),false);
         }
         if (auxSignal!=nullptr) {
             logic->setWatchedSignal1Alt(auxSignal->getSystemName());
         }
         QString nearSensorName = setupNearLogixSlip(nearTurnout, nearState, head, farTurnout, farState, slip, number);
         addNearSensorToSlipLogic(nearSensorName);
         finalizeBlockBossLogic();
        }
       }
    if ( (secondHead!=nullptr) && !setup2 ) return;
    SignalHead* savedAuxSignal = auxSignal;
    if (track2==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because all connections\nhave not been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    LayoutBlock* block2 = track2->getLayoutBlock();
    if (block2==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because blocks have\nnot been defined around this item."),"",JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    Sensor* occupancy2 = block2->getOccupancySensor();
    if (occupancy2==nullptr) {
        JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
            tr("Cannot set up logic because block \"%1\"\ndoesn''t have an occupancy sensor.").arg(
                block2->getUserName()),
                    NULL,JOptionPane::INFORMATION_MESSAGE);
        return;
    }
    SignalHead* nextHead2 = NULL;
    if (secondHead!=nullptr)
    {
     nextHead2 = getNextSignalFromObject(track2,
             slip, secondHead->getSystemName(), setSignalsAtSlipFrame);
     if ( (nextHead2==nullptr) && (!reachedEndBumper()) ) {
            JOptionPane::showMessageDialog(setSignalsAtSlipFrame,
                tr("Cannot set up logic because the next signal (in or \nat the end of block \"%1\") apparently is not yet defined.").arg(
                    block2->getUserName()),
                        NULL,JOptionPane::INFORMATION_MESSAGE);
         return;
     }
    }
    if ( (secondHead==nullptr) && (track1!=nullptr) && setup1 )
    {
     if (!initializeBlockBossLogic(head->getSystemName())) return;
     logic->setMode(BlockBossLogic::FACING);
     logic->setTurnout(farTurnout->getSystemName());
     if(occupancy!=nullptr)
         logic->setWatchedSensor1(occupancy->getSystemName());
     logic->setWatchedSensor2(occupancy2->getSystemName());
     logic->setSensor2(connectorOccupancy->getSystemName());
     if (nextHead!=nullptr) {
         logic->setWatchedSignal1(nextHead->getSystemName(),false);
     }
     if (savedAuxSignal!=nullptr) {
         logic->setWatchedSignal1Alt(savedAuxSignal->getSystemName());
     }
     if (nextHead2!=nullptr) {
         logic->setWatchedSignal2(nextHead2->getSystemName());
     }
     if (auxSignal!=nullptr) {
         logic->setWatchedSignal2Alt(auxSignal->getSystemName());
     }
     QString nearSensorName = setupNearLogixSlip(nearTurnout, nearState,head, farTurnout, farState, slip, number+1);
     addNearSensorToSlipLogic(nearSensorName);
     logic->setLimitSpeed2(true);
     finalizeBlockBossLogic();
    }
    else if ( (secondHead!=nullptr) && setup2)
    {
        if (!initializeBlockBossLogic(secondHead->getSystemName())) return;
        nearState = layoutSlip->getTurnoutState(nearTurnout, divergeState);
        farState = layoutSlip->getTurnoutState(farTurnout, divergeState);

        logic->setMode(BlockBossLogic::TRAILINGDIVERGING);
        if(farState==Turnout::CLOSED){
            logic->setMode(BlockBossLogic::TRAILINGMAIN);
            logic->setLimitSpeed1(true);
        } else {
            logic->setLimitSpeed2(true);
        }
        logic->setTurnout(farTurnout->getSystemName());
        logic->setSensor1(occupancy2->getSystemName());
        if (occupancy2!=connectorOccupancy)
            logic->setSensor2(connectorOccupancy->getSystemName());
        if (nextHead2!=nullptr) {
            logic->setWatchedSignal1(nextHead2->getSystemName(),false);
        }
        if (auxSignal!=nullptr) {
            logic->setWatchedSignal1Alt(auxSignal->getSystemName());
        }
        QString nearSensorName = setupNearLogixSlip(nearTurnout, nearState, secondHead, farTurnout, farState, slip, number+1);
        addNearSensorToSlipLogic(nearSensorName);
        finalizeBlockBossLogic();
    }
}

/*private*/ QString LayoutEditorTools::setupNearLogixSlip(Turnout* turn, int nearState, SignalHead* /*head*/, Turnout* farTurn, int farState, LayoutSlip* slip, int number)
{
 QString turnoutName = turn->getDisplayName();
 QString farTurnoutName = farTurn->getDisplayName();

 QString logixName = "SYS_LAYOUTSLIP:"+slip->getName();
 QString sensorName = "IS:"+logixName+"C"+number;
 Sensor* sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(sensorName);
 if (sensor==nullptr) {
     log->error("Trouble creating sensor "+sensorName+" while setting up Logix->");
     return "";
 }
 bool newConditional = false;
 Logix* x = (Logix*)((LogixManager*)InstanceManager::getDefault("LogixManager"))->getBySystemName(logixName);
 if(x == nullptr)
 {
  // Logix does not exist, create it
  x = ((LogixManager*)InstanceManager::getDefault("LogixManager"))->createNewLogix(logixName, "");
  if(x==nullptr)
  {
   log->error("Trouble creating logix "+logixName+" while setting up signal logic->");
   return "";
  }
  x->setComment("Layout Slip, Signalhead logic");
 }
 x->deActivateLogix();
 QString cName = logixName+"C" + QString::number(number);

 Conditional* c = ((ConditionalManager*) InstanceManager::getDefault("ConditionalManager"))->getBySystemName(cName);
 if (c == nullptr)
 {
  c = ((ConditionalManager*) InstanceManager::getDefault("ConditionalManager"))->
                     createNewConditional(cName, "");
  newConditional = true;
  if (c == nullptr)
  {
   log->error("Trouble creating conditional " + cName + " while setting up Logix.");
                 return "";
  }
 }
 int type = Conditional::TYPE_TURNOUT_THROWN;
 if (nearState == Turnout::CLOSED) {
     type = Conditional::TYPE_TURNOUT_CLOSED;
 }

 QList<ConditionalVariable*>* variableList = new QList<ConditionalVariable*>();
 variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND,
         type, turnoutName, true));

 type = Conditional::TYPE_TURNOUT_THROWN;
 if (farState == Turnout::CLOSED) {
     type = Conditional::TYPE_TURNOUT_CLOSED;
 }
 variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND,
         type, farTurnoutName, true));
 c->setStateVariables(variableList);
 QList<ConditionalAction*>* actionList = new QList<ConditionalAction*>();
 actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
         Conditional::ACTION_SET_SENSOR, sensorName,
         Sensor::INACTIVE, ""));
 actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE,
         Conditional::ACTION_SET_SENSOR, sensorName,
         Sensor::ACTIVE, ""));
 c->setAction(actionList);        // string data
 if (newConditional) {
     x->addConditional(cName, -1);
 }
 x->activateLogix();
 return sensorName;
}

/*
 * Adds the sensor specified to the open BlockBossLogic, provided it is not already there and
 *		provided there is an open slot. If 'name' is NULL or empty, returns without doing anything.
 */
/*private*/ void LayoutEditorTools::addNearSensorToSlipLogic(QString name)
{
 if ( (name==nullptr) || name==("") ) return;
 // return if a sensor by this name is already present
 if ( (logic->getSensor1()!=nullptr) && (logic->getSensor1())==(name) ) return;
 if ( (logic->getSensor2()!=nullptr) && (logic->getSensor2())==(name) ) return;
 if ( (logic->getSensor3()!=nullptr) && (logic->getSensor3())==(name) ) return;
 if ( (logic->getSensor4()!=nullptr) && (logic->getSensor4())==(name) ) return;
 if ( (logic->getSensor5()!=nullptr) && (logic->getSensor5())==(name) ) return;
 // add in the first available slot
 if (logic->getSensor1()==nullptr) logic->setSensor1(name);
 else if (logic->getSensor2()==nullptr) logic->setSensor2(name);
 else if (logic->getSensor3()==nullptr) logic->setSensor3(name);
 else if (logic->getSensor4()==nullptr) logic->setSensor4(name);
 else if (logic->getSensor5()==nullptr) logic->setSensor5(name);
 else log->error("Error - could not add sensor to SSL for signal head "+logic->getDrivenSignal());
}

/*public*/ SignalHeadIcon* LayoutEditorTools::getSignalHeadIcon(QString signalName)
{
 SignalHeadIcon* l = new SignalHeadIcon(layoutEditor);
 l->setSignalHead(signalName);
 l->setIcon(tr("Red"), signalIconEditor->getIcon(0));
 l->setIcon(tr("Flashing Red"), signalIconEditor->getIcon(1));
 l->setIcon(tr("Yellow"), signalIconEditor->getIcon(2));
 l->setIcon(tr("Flashing Yellow"), signalIconEditor->getIcon(3));
 l->setIcon(tr("Green"), signalIconEditor->getIcon(4));
 l->setIcon(tr("Flashing Green"), signalIconEditor->getIcon(5));
 l->setIcon(tr("Dark"), signalIconEditor->getIcon(6));
 l->setIcon(tr("Held"), signalIconEditor->getIcon(7));
 l->setIcon(tr("Lunar"), signalIconEditor->getIcon(8));
 l->setIcon(tr("Flashing Lunar"), signalIconEditor->getIcon(9));
 l->rotate(90);
 return l;
}
/*protected*/ bool LayoutEditorTools::addLayoutTurnoutSignalHeadInfoToMenu(
        /*@Nonnull*/ QString inTurnoutNameA, /*@Nonnull*/ QString inTurnoutNameB,
        /*@Nonnull*/ QMenu* inMenu) {
    bool result = false; //assume failure (pessimist!)

    //lookup turnouts
    turnout = turnout1 = turnoutA = InstanceManager::turnoutManagerInstance()->getTurnout(inTurnoutNameA);
    turnout2 = turnoutB = InstanceManager::turnoutManagerInstance()->getTurnout(inTurnoutNameB);
    //map those to layout turnouts (if possible)
    for (LayoutTurnout* lt : layoutEditor->getLayoutTurnouts()) {
        Turnout* to = lt->getTurnout();
        if (to != nullptr) {
            QString uname = to->getUserName();
            QString sname = to->getSystemName();
            if (!inTurnoutNameA.isEmpty() && (sname == (inTurnoutNameA) || ((uname != "") && uname == (inTurnoutNameA)))) {
                layoutTurnout = layoutTurnout1 = layoutTurnoutA = lt;
            }
            if (!inTurnoutNameB.isEmpty() && (sname == (inTurnoutNameB) || ((uname != "") && uname == (inTurnoutNameB)))) {
                layoutTurnout2 = layoutTurnoutB = lt;
            }
        }
    }

    int before_mcc = inMenu->actions().count();
    if (before_mcc != 0) {
        inMenu->addSeparator();// new JSeparator());
    }
    int linkType = layoutTurnout->getLinkType();
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)) {
        QAction* jmi = inMenu->addSection(tr("Crossover"));
        jmi->setEnabled(false);
        inMenu->addSeparator();//new JSeparator());
        before_mcc += 2;
        addInfoToMenu("A " + continuingString,  layoutTurnout->getSignalA1Name(), inMenu);
        addInfoToMenu("A " + divergingString,  layoutTurnout->getSignalA2Name(), inMenu);
        addInfoToMenu("B " + continuingString,  layoutTurnout->getSignalB1Name(), inMenu);
        addInfoToMenu("B " + divergingString,  layoutTurnout->getSignalB2Name(), inMenu);
        addInfoToMenu("C " + continuingString,  layoutTurnout->getSignalC1Name(), inMenu);
        addInfoToMenu("C " + divergingString,  layoutTurnout->getSignalC2Name(), inMenu);
        addInfoToMenu("D " + continuingString,  layoutTurnout->getSignalD1Name(), inMenu);
        addInfoToMenu("D " + divergingString,  layoutTurnout->getSignalD2Name(), inMenu);
    } else if (linkType ==  LayoutTurnout::NO_LINK) {
        QAction* jmi = inMenu->addSection(tr("Turnout"));
        jmi->setEnabled(false);
        inMenu->addSeparator();//new JSeparator());
        before_mcc += 2;
        addInfoToMenu(throatContinuingString,  layoutTurnout->getSignalA1Name(), inMenu);
        addInfoToMenu(throatDivergingString,  layoutTurnout->getSignalA2Name(), inMenu);
        addInfoToMenu(continuingString,  layoutTurnout->getSignalB1Name(), inMenu);
        addInfoToMenu(divergingString,  layoutTurnout->getSignalC1Name(), inMenu);
    } else if (linkType ==  LayoutTurnout::THROAT_TO_THROAT) {
        QString menuString = tr("Throat to Throat") + " (";
        menuString += tr("Turnout") + ", " + tr("Route");
        menuString += ", " + tr("SignalHead") + ":)";
        QAction* jmi = inMenu->addSection(menuString);
        jmi->setEnabled(false);
        inMenu->addSeparator();//new JSeparator());
        before_mcc += 2;
        addInfoToMenu(eastString + ", " + continuingString + ", " + continuingString,  layoutTurnout1->getSignalB1Name(), inMenu);
        addInfoToMenu(eastString + ", " + continuingString + ", " + divergingString,  layoutTurnout1->getSignalB2Name(), inMenu);
        addInfoToMenu(eastString + ", " + divergingString + ", " + continuingString,  layoutTurnout1->getSignalC1Name(), inMenu);
        addInfoToMenu(eastString + ", " + divergingString + ", " + divergingString,  layoutTurnout1->getSignalC2Name(), inMenu);
        addInfoToMenu(westString + ", " + continuingString + ", " + continuingString,  layoutTurnout2->getSignalB1Name(), inMenu);
        addInfoToMenu(westString + ", " + continuingString + ", " + divergingString,  layoutTurnout2->getSignalB2Name(), inMenu);
        addInfoToMenu(westString + ", " + divergingString + ", " + continuingString,  layoutTurnout2->getSignalC1Name(), inMenu);
        addInfoToMenu(westString + ", " + divergingString + ", " + divergingString,  layoutTurnout2->getSignalC2Name(), inMenu);
    } else if (linkType ==  LayoutTurnout::FIRST_3_WAY) {
        QAction* jmi = inMenu->addSection(tr("ThreeWay"));
        jmi->setEnabled(false);
        inMenu->addSeparator();//new JSeparator());
        before_mcc += 2;
        addInfoToMenu(throatString + " " + continuingString, layoutTurnoutA->getSignalA1Name(), inMenu);
        addInfoToMenu(throatString + " " + divergingAString, layoutTurnoutA->getSignalA2Name(), inMenu);
        addInfoToMenu(throatString + " " + divergingBString, layoutTurnoutA->getSignalA3Name(), inMenu);
        addInfoToMenu(continuingString, layoutTurnoutA->getSignalC1Name(), inMenu);
        addInfoToMenu(divergingAString, layoutTurnoutB->getSignalB1Name(), inMenu);
        addInfoToMenu(divergingBString, layoutTurnoutB->getSignalC1Name(), inMenu);
    } else if (linkType ==  LayoutTurnout::SECOND_3_WAY) {
        QAction* jmi = inMenu->addSection(tr("ThreeWay"));
        jmi->setEnabled(false);
        inMenu->addSeparator();// new JSeparator());
        before_mcc += 2;
        addInfoToMenu(throatString + " " + continuingString, layoutTurnoutB->getSignalA1Name(), inMenu);
        addInfoToMenu(throatString + " " + divergingAString, layoutTurnoutB->getSignalA2Name(), inMenu);
        addInfoToMenu(throatString + " " + divergingBString, layoutTurnoutB->getSignalA3Name(), inMenu);
        addInfoToMenu(continuingString, layoutTurnoutB->getSignalC1Name(), inMenu);
        addInfoToMenu(divergingAString, layoutTurnoutA->getSignalB1Name(), inMenu);
        addInfoToMenu(divergingBString, layoutTurnoutA->getSignalC1Name(), inMenu);
    }
    int after_mcc = inMenu->actions().count();
    if (before_mcc != after_mcc) {
        inMenu->addSeparator();//new JSeparator());
        result = true;   //it's GOOD!
    }
    return result;
}   //addLayoutTurnoutSignalHeadInfoToMenu

/*protected*/ bool LayoutEditorTools::addBlockBoundarySignalHeadInfoToMenu(
    /*@Nonnull*/ PositionablePoint* inPositionablePoint,
        /*@Nonnull*/ QMenu* inMenu) {
    bool result = false; //assume failure (pessimist!)

    int before_mcc = inMenu->actions().count();
    if (before_mcc != 0) {
        inMenu->addSeparator();//new JSeparator());
    }

    QAction* jmi = inMenu->addSection(tr("Block Boundary"));
    jmi->setEnabled(false);
    inMenu->addSeparator();//new JSeparator());
    before_mcc += 2;

    addInfoToMenu(tr("East (or South) Bound"), inPositionablePoint->getEastBoundSignal(), inMenu);
    addInfoToMenu(tr("West (or North) Bound"), inPositionablePoint->getWestBoundSignal(), inMenu);

    int after_mcc = inMenu->actions().count();
    if (before_mcc != after_mcc) {
        inMenu->addSeparator();//new JSeparator());
        result = true;   //it's GOOD!
    }

    return result;
}

/*protected*/ bool LayoutEditorTools::addLevelXingSignalHeadInfoToMenu(
        /*@Nonnull*/ LevelXing* inLevelXing,
        /*@Nonnull*/ QMenu* inMenu)
{
    bool result = false; //assume failure (pessimist!)

    int before_mcc = inMenu->actions().count();
    if (before_mcc != 0) {
        inMenu->addSeparator();//new JSeparator());
    }

    QAction* jmi = inMenu->addSection(tr("Level Crossing"));
    jmi->setEnabled(false);
    inMenu->addSeparator();//new JSeparator());
    before_mcc += 2;

    addInfoToMenu(
            tr("%1 Connecting Point").arg("A"),
            inLevelXing->getSignalAName(), inMenu);
    addInfoToMenu(
            tr("%1 Connecting Point").arg("B"),
            inLevelXing->getSignalBName(), inMenu);
    addInfoToMenu(
            tr("%1 Connecting Point").arg("C"),
            inLevelXing->getSignalCName(), inMenu);
    addInfoToMenu(
            tr("%1 Connecting Point").arg("D"),
            inLevelXing->getSignalDName(), inMenu);

    int after_mcc = inMenu->actions().count();
    if (before_mcc != after_mcc) {
        inMenu->addSeparator();//new JSeparator());
        result = true;   //it's GOOD!
    }

    return result;
}

/*protected*/ bool LayoutEditorTools::addLayoutSlipSignalHeadInfoToMenu(
        /*@Nonnull*/ LayoutTurnout* inLayoutTurnout,
        /*@Nonnull*/ QMenu* inMenu) {
    bool result = false; //assume failure (pessimist!)

    int before_mcc = inMenu->actions().count();
    if (before_mcc != 0) {
        inMenu->addSeparator();//new JSeparator());
    }

    QAction* jmi = inMenu->addSection(tr("Slip"));
    jmi->setEnabled(false);
    inMenu->addSeparator();//new JSeparator());
    before_mcc += 2;

    addInfoToMenu("A " + continuingString, inLayoutTurnout->getSignalA1Name(), inMenu);
    addInfoToMenu("A " + divergingString, inLayoutTurnout->getSignalA2Name(), inMenu);
    addInfoToMenu("B " + continuingString, inLayoutTurnout->getSignalB1Name(), inMenu);
    addInfoToMenu("B " + divergingString, inLayoutTurnout->getSignalB2Name(), inMenu);
    addInfoToMenu("C " + continuingString, inLayoutTurnout->getSignalC1Name(), inMenu);
    addInfoToMenu("C " + divergingString, inLayoutTurnout->getSignalC2Name(), inMenu);
    addInfoToMenu("D " + continuingString, inLayoutTurnout->getSignalD1Name(), inMenu);
    addInfoToMenu("D " + divergingString, inLayoutTurnout->getSignalD2Name(), inMenu);

    int after_mcc = inMenu->actions().count();
    if (before_mcc != after_mcc) {
        inMenu->addSeparator();//new JSeparator());
        result = true;   //it's GOOD!
    }

    return result;
}

/*private*/ void LayoutEditorTools::addInfoToMenu(/*@CheckForNull*/ QString title,
        /*@CheckForNull*/ QString info, /*@Nonnull*/ QMenu* menu) {
    if ((!title.isNull()) && !title.isEmpty() && (!info.isNull()) && !info.isEmpty()) {
        addInfoToMenu(title + ": " + info, menu);
    }
}

/*private*/ void LayoutEditorTools::addInfoToMenu(/*@CheckForNull*/ QString info, /*@Nonnull*/ QMenu* menu) {
    if ((info != nullptr) && !info.isEmpty()) {
        QAction* jmi = menu->addSection(info);
        jmi->setEnabled(false);
    }
}

  /*static*/ Logger* LayoutEditorTools::log = LoggerFactory::getLogger("LayoutEditorTools");
//}

/*private*/ void LayoutEditorTools::oneFrameToRuleThemAll(/*@Nonnull*/ JmriJFrame* goodFrame) {
 setSensorsAtBlockBoundaryFrame = closeIfNotFrame(goodFrame, setSensorsAtBlockBoundaryFrame);
 setSensorsAtLevelXingFrame = closeIfNotFrame(goodFrame, setSensorsAtLevelXingFrame);
 setSensorsAtSlipFrame = closeIfNotFrame(goodFrame, setSensorsAtSlipFrame);
 setSensorsAtTurnoutFrame = closeIfNotFrame(goodFrame, setSensorsAtTurnoutFrame);
 setSignalMastsAtBlockBoundaryFrame = closeIfNotFrame(goodFrame, setSignalMastsAtBlockBoundaryFrame);
 setSignalMastsAtLayoutSlipFrame = closeIfNotFrame(goodFrame, setSignalMastsAtLayoutSlipFrame);
 setSignalMastsAtLevelXingFrame = closeIfNotFrame(goodFrame, setSignalMastsAtLevelXingFrame);
 setSignalMastsAtTurnoutFrame = closeIfNotFrame(goodFrame, setSignalMastsAtTurnoutFrame);
 setSignalsAt3WayTurnoutFrame = closeIfNotFrame(goodFrame, setSignalsAt3WayTurnoutFrame);
 setSignalsAtBlockBoundaryFrame = closeIfNotFrame(goodFrame, setSignalsAtBlockBoundaryFrame);
 setSignalsAtLevelXingFrame = closeIfNotFrame(goodFrame, setSignalsAtLevelXingFrame);
 setSignalsAtSlipFrame = closeIfNotFrame(goodFrame, setSignalsAtSlipFrame);
 setSignalsAtThroatToThroatTurnoutsFrame = closeIfNotFrame(goodFrame, setSignalsAtThroatToThroatTurnoutsFrame);
 setSignalsAtTurnoutFrame = closeIfNotFrame(goodFrame, setSignalsAtTurnoutFrame);
 setSignalsAtXoverTurnoutFrame = closeIfNotFrame(goodFrame, setSignalsAtXoverTurnoutFrame);
}

/*private*/ JmriJFrame* LayoutEditorTools::closeIfNotFrame(/*@Nonnull */JmriJFrame* goodFrame, /*@CheckForNull*/ JmriJFrame* badFrame) {
    JmriJFrame* result = badFrame;
    if ((badFrame != nullptr) && (goodFrame != badFrame)) {
        badFrame->setVisible(false);
        badFrame->dispose();
        result = nullptr;
    }
    return result;
}
