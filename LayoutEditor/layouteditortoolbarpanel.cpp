#include "layouteditortoolbarpanel.h"
#include "loggerfactory.h"
#include "layouteditor.h"
#include "multiiconeditor.h"
#include "jlabel.h"
#include <QRadioButton>
#include "flowlayout.h"
#include "namedbeancombobox.h"
#include "jcombobox.h"
#include <QCheckBox>
#include "jtextfield.h"
#include "jframe.h"
#include <QPushButton>
#include "multisensoriconframe.h"
#include <QButtonGroup>
#include "joptionpane.h"
#include "signalmastmanager.h"

LayoutEditorToolBarPanel::LayoutEditorToolBarPanel(LayoutEditor *layoutEditor, QWidget *parent)
 : JPanel(parent)
{
 //top row of radio buttons
 turnoutLabel = new JLabel();
 turnoutRHButton = new QRadioButton(tr("RH"));
 turnoutLHButton = new QRadioButton(tr("LH"));
 turnoutWYEButton = new QRadioButton(tr("Wye"));
 doubleXoverButton = new QRadioButton(tr("Double X-over"));
 rhXoverButton = new QRadioButton(tr("RightCrossover")); //key is also used by Control Panel Editor, placed in DisplayBundle
 lhXoverButton = new QRadioButton(tr("LeftCrossover")); //idem
 layoutSingleSlipButton = new QRadioButton(tr("Single Slip"));
 layoutDoubleSlipButton = new QRadioButton(tr("Double Slip"));

 //Default flow layout definitions for JPanels
 leftRowLayout = new FlowLayout(/*FlowLayout::LEFT, 5, 0*/);       //5 pixel gap between items, no vertical gap
 centerRowLayout = new FlowLayout(/*FlowLayout::CENTER, 5, 0*/);   //5 pixel gap between items, no vertical gap
 rightRowLayout = new FlowLayout(/*FlowLayout::RIGHT, 5, 0*/);     //5 pixel gap between items, no vertical gap

 //top row of check boxes
 turnoutNameComboBox = new NamedBeanComboBox(InstanceManager::turnoutManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 turnoutNameLabel = new JLabel(tr("%1").arg(tr("Name")));
 turnoutNamePanel = new JPanel(new QHBoxLayout(/*FlowLayout::LEFT, 5, 0*/));
 //turnoutNamePanelLayout = new FlowLayout();
 turnoutNamePanel->layout()->setSpacing(6);
 extraTurnoutPanel = new JPanel(new QHBoxLayout(/*FlowLayout::LEFT, 5, 0*/));
 extraTurnoutPanel->layout()->setSpacing(6);
 //extraTurnoutPanelLayout = new FlowLayout(extraTurnoutPanel);
 extraTurnoutNameComboBox = new NamedBeanComboBox(InstanceManager::turnoutManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 rotationComboBox = nullptr;
 rotationPanel = new JPanel(new QHBoxLayout(/*FlowLayout::LEFT, 5, 0*/));
 rotationPanel->layout()->setSpacing(6);

 //2nd row of radio buttons
 trackLabel = new JLabel();
 levelXingButton = new QRadioButton(tr("Level Crossing"));
 trackButton = new QRadioButton(tr("Track Segment"));

 //2nd row of check boxes
 trackSegmentPropertiesPanel = new JPanel(new QHBoxLayout(/*FlowLayout::LEFT, 5, 0*/));
 //trackSegmentPropertiesPanelLayout = new FlowLayout();
 trackSegmentPropertiesPanel->layout()->setSpacing(6);

 mainlineTrack = new QCheckBox(tr("Mainline"));
 dashedLine = new QCheckBox(tr("Dashed"));

 blockLabel = new JLabel(tr("%1").arg(tr("Block Name:")));
 blockIDComboBox = new NamedBeanComboBox((BlockManager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 highlightBlockCheckBox = new QCheckBox(tr("Highlight"));

 blockSensorLabel = new JLabel(tr("%1").arg(tr("Block Sensor Name")));
 blockSensorComboBox = new NamedBeanComboBox((SensorManager*) InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 //3rd row of radio buttons (and any associated text fields)
 endBumperButton = new QRadioButton(tr("End Bumper"));
 anchorButton = new QRadioButton(tr("Anchor"));
 edgeButton = new QRadioButton(tr("Edge Connector"));

 labelsLabel = new JLabel();
 textLabelButton = new QRadioButton(tr("Label Text"));
 textLabelTextField = new JTextField(12);

 memoryButton = new QRadioButton(tr("Memory"));
 textMemoryComboBox = new NamedBeanComboBox((MemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 blockContentsButton = new QRadioButton(tr("Block Contents"));
 blockContentsComboBox = new NamedBeanComboBox((BlockManager*) InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 //4th row of radio buttons (and any associated text fields)
 multiSensorButton = new QRadioButton(tr("MultiSensor") + "...");

 signalMastButton = new QRadioButton(tr("Signal Mast Icon"));
 signalMastComboBox = new NamedBeanComboBox((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 sensorButton = new QRadioButton(tr("Sensor Icon"));
 sensorComboBox = new NamedBeanComboBox((ProxySensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 signalButton = new QRadioButton(tr("Signal Head Icon"));
 signalHeadComboBox = new NamedBeanComboBox((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

 iconLabelButton = new QRadioButton(tr("Icon Label"));
 shapeButton = new QRadioButton(tr("Shape"));

 changeIconsButton = new QPushButton(tr("Change Icons") + "...");

 sensorIconEditor = nullptr;
 sensorFrame = nullptr;
 signalIconEditor = nullptr;
 signalFrame = nullptr;

 iconEditor = nullptr;
 iconFrame = nullptr;

 multiSensorFrame = nullptr;

 xLabel = new JLabel("00");
 yLabel = new JLabel("00");

 zoomPanel = new JPanel(new QHBoxLayout());
 zoomLabel = new JLabel("x1");

 locationPanel = new JPanel(new QHBoxLayout());

 blockPropertiesPanel = nullptr;

 //non-GUI variables
 toolBarIsWide = true;
 itemGroup = nullptr;


 // temp code until fully implemented;
 signalIconEditor = layoutEditor->getLETools()->signalIconEditor;

 this->layoutEditor = layoutEditor;

 //setupComponents();

 // layoutComponents(); must be called after constructor completes
}

/**
 * This is the base class for the horizontal, vertical and floating toolbar
 * panels
 *
 * @author George Warner Copyright: (c) 2017-2019
 */
//@SuppressWarnings("serial")
//@SuppressFBWarnings(value = "SE_/*transient*/_FIELD_NOT_RESTORED") //no Serializable support at present
///*public*/ class LayoutEditorToolBarPanel extends JPanel* {

#if 0

    /**
     * constructor for LayoutEditorToolBarPanel
     *
     * @param layoutEditor the layout editor that this is for
     */
    /*public*/ LayoutEditorToolBarPanel(@Nonnull LayoutEditor layoutEditor) {
        this.layoutEditor = layoutEditor;

        setupComponents();

        layoutComponents();
    }   //constructor
#endif
#if 1
    /*protected*/ void LayoutEditorToolBarPanel::setupComponents() {
     QFont f = font();
     f.setPointSize(8);
     setFont(f);
        //setup group for radio buttons selecting items to add and line style
        itemGroup = new QButtonGroup(this);
        itemGroup->addButton(turnoutRHButton);
        itemGroup->addButton(turnoutLHButton);
        itemGroup->addButton(turnoutWYEButton);
        itemGroup->addButton(doubleXoverButton);
        itemGroup->addButton(rhXoverButton);
        itemGroup->addButton(lhXoverButton);
        itemGroup->addButton(levelXingButton);
        itemGroup->addButton(layoutSingleSlipButton);
        itemGroup->addButton(layoutDoubleSlipButton);
        itemGroup->addButton(endBumperButton);
        itemGroup->addButton(anchorButton);
        itemGroup->addButton(edgeButton);
        itemGroup->addButton(trackButton);
        itemGroup->addButton(multiSensorButton);
        itemGroup->addButton(sensorButton);
        itemGroup->addButton(signalButton);
        itemGroup->addButton(signalMastButton);
        itemGroup->addButton(textLabelButton);
        itemGroup->addButton(memoryButton);
        itemGroup->addButton(blockContentsButton);
        itemGroup->addButton(iconLabelButton);
        itemGroup->addButton(shapeButton);

        //This is used to enable/disable property controls depending on which (radio) button is selected
#if 0
        ActionListener selectionListAction = (ActionEvent event) -> {
            //turnout properties
            bool e = (turnoutRHButton->isChecked()
                    || turnoutLHButton->isChecked()
                    || turnoutWYEButton->isChecked()
                    || doubleXoverButton->isChecked()
                    || rhXoverButton->isChecked()
                    || lhXoverButton->isChecked()
                    || layoutSingleSlipButton->isChecked()
                    || layoutDoubleSlipButton->isChecked());
            log->debug(tr("turnoutPropertiesPanel is %1").arg(e ? "enabled" : "disabled"));
            turnoutNamePanel->setEnabled(e);

            for (Component i : turnoutNamePanel.getComponents()) {
                i.setEnabled(e);
            }
            rotationPanel.setEnabled(e);

            for (Component i : rotationPanel.getComponents()) {
                i.setEnabled(e);
            }

            //second turnout property
            e = (layoutSingleSlipButton->isChecked() || layoutDoubleSlipButton->isChecked());
            log.debug("extraTurnoutPanel is {}", e ? "enabled" : "disabled");

            for (Component i : extraTurnoutPanel.getComponents()) {
                i.setEnabled(e);
            }

            //track Segment properties
            e = trackButton->isChecked();
            log.debug("trackSegmentPropertiesPanel is {}", e ? "enabled" : "disabled");

            for (Component i : trackSegmentPropertiesPanel.getComponents()) {
                i.setEnabled(e);
            }

            //block properties
            e = (turnoutRHButton->isChecked()
                    || turnoutLHButton->isChecked()
                    || turnoutWYEButton->isChecked()
                    || doubleXoverButton->isChecked()
                    || rhXoverButton->isChecked()
                    || lhXoverButton->isChecked()
                    || layoutSingleSlipButton->isChecked()
                    || layoutDoubleSlipButton->isChecked()
                    || levelXingButton->isChecked()
                    || trackButton->isChecked());
            log.debug("blockPanel is {}", e ? "enabled" : "disabled");

            if (blockPropertiesPanel != null) {
                for (Component i : blockPropertiesPanel.getComponents()) {
                    i.setEnabled(e);
                }

                if (e) {
                    blockPropertiesPanel.setBackground(Color.lightGray);
                } else {
                    blockPropertiesPanel.setBackground(new Color(238, 238, 238));
                }
            } else {
                blockLabel.setEnabled(e);
                blockIDComboBox.setEnabled(e);
                blockSensorLabel.setEnabled(e);
                blockSensorLabel.setEnabled(e);
                blockSensorComboBox.setEnabled(e);
            }

            //enable/disable text label, memory & block contents text fields
            textLabelTextField.setEnabled(textLabelButton->isChecked());
            textMemoryComboBox.setEnabled(memoryButton->isChecked());
            blockContentsComboBox.setEnabled(blockContentsButton->isChecked());

            //enable/disable signal mast, sensor & signal head text fields
            signalMastComboBox.setEnabled(signalMastButton->isChecked());
            sensorComboBox.setEnabled(sensorButton->isChecked());
            signalHeadComboBox.setEnabled(signalButton->isChecked());

            //changeIconsButton
            e = (sensorButton->isChecked()
                    || signalButton->isChecked()
                    || iconLabelButton->isChecked());
            log.debug("changeIconsButton is {}", e ? "enabled" : "disabled");
            changeIconsButton.setEnabled(e);
        };
#endif
        //turnoutRHButton.addActionListener(selectionListAction);
        connect(turnoutRHButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
        //turnoutLHButton.addActionListener(selectionListAction);
        connect(turnoutLHButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        turnoutWYEButton.addActionListener(selectionListAction);
        connect(turnoutWYEButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        doubleXoverButton.addActionListener(selectionListAction);
        connect(doubleXoverButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        rhXoverButton.addActionListener(selectionListAction);
        connect(rhXoverButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        lhXoverButton.addActionListener(selectionListAction);
        connect(lhXoverButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        levelXingButton.addActionListener(selectionListAction);
        connect(levelXingButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        layoutSingleSlipButton.addActionListener(selectionListAction);
        connect(layoutSingleSlipButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        layoutDoubleSlipButton.addActionListener(selectionListAction);
        connect(layoutDoubleSlipButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        endBumperButton.addActionListener(selectionListAction);
        connect(endBumperButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        anchorButton.addActionListener(selectionListAction);
        connect(anchorButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        edgeButton.addActionListener(selectionListAction);
        connect(edgeButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        trackButton.addActionListener(selectionListAction);
        connect(trackButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        multiSensorButton.addActionListener(selectionListAction);
        connect(multiSensorButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        sensorButton.addActionListener(selectionListAction);
        connect(sensorButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        signalButton.addActionListener(selectionListAction);
        connect(signalButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        signalMastButton.addActionListener(selectionListAction);
        connect(signalMastButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        textLabelButton.addActionListener(selectionListAction);
        connect(textLabelButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        memoryButton.addActionListener(selectionListAction);
        connect(memoryButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        blockContentsButton.addActionListener(selectionListAction);
        connect(blockContentsButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        iconLabelButton.addActionListener(selectionListAction);
        connect(iconLabelButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));
//        shapeButton.addActionListener(selectionListAction);
        connect(shapeButton, SIGNAL(clicked(bool)), this, SLOT(on_selectionListAction()));

        //first row of edit tool bar items
        //turnout items
        turnoutRHButton->setChecked(true);
        turnoutRHButton->setToolTip(tr("Select to add a right-handed turnout when next clicking with shift down."));
        turnoutLHButton->setToolTip(tr("Select to add a left-handed turnout when next clicking with shift down."));
        turnoutWYEButton->setToolTip(tr("Select to add a wye turnout when next clicking with shift down."));
        doubleXoverButton->setToolTip(tr("Select to add a double crossover turnout when next clicking with shift down."));
        rhXoverButton->setToolTip(tr("Select to add a right-hand single crossover turnout when next clicking with shift down."));
        lhXoverButton->setToolTip(tr("Select to add a left-hand single crossover turnout when next clicking with shift down."));
        layoutSingleSlipButton->setToolTip(tr("Select to add a single slip when next clicking with shift down."));
        layoutDoubleSlipButton->setToolTip(tr("Select to add a double slip when next clicking with shift down."));

        turnoutNamePanel->layout()->addWidget(turnoutNameLabel);

        layoutEditor->setupComboBox(turnoutNameComboBox, false, true, false);
        turnoutNameComboBox->setToolTip(tr("Enter name of physical turnout."));
        turnoutNamePanel->layout()->addWidget(turnoutNameComboBox);

        // disable turnouts that are already in use
// TODO:       turnoutNameComboBox->addPopupMenuListener(layoutEditor->newTurnoutComboBoxPopupMenuListener(turnoutNameComboBox));
        // turnoutNameComboBox.setEnabledColor(Color.green.darker().darker());
        // turnoutNameComboBox.setDisabledColor(Color.red);

        layoutEditor->setupComboBox(extraTurnoutNameComboBox, false, true, false);
        extraTurnoutNameComboBox->setToolTip(tr("Enter name of second physical turnout."));

// TODO:        extraTurnoutNameComboBox->addPopupMenuListener(layoutEditor->newTurnoutComboBoxPopupMenuListener(extraTurnoutNameComboBox));
        // extraTurnoutNameComboBox.setEnabledColor(Color.green.darker().darker());
        // extraTurnoutNameComboBox.setDisabledColor(Color.red);

        //this is enabled/disabled via selectionListAction above
        JLabel* extraTurnoutLabel = new JLabel(tr("Additional Name"));
        extraTurnoutLabel->setEnabled(false);
        extraTurnoutPanel->layout()->addWidget(extraTurnoutLabel);
        extraTurnoutPanel->layout()->addWidget(extraTurnoutNameComboBox);
        extraTurnoutPanel->setEnabled(false);

        QStringList angleStrings = {"-180", "-135", "-90", "-45", "0", "+45", "+90", "+135", "+180"};
        rotationComboBox = new JComboBox(angleStrings);
        rotationComboBox->setEditable(true);
        rotationComboBox->setCurrentIndex(4);
//        rotationComboBox->setMaximumRowCount(9);
        rotationComboBox->setToolTip(tr("<html>Enter clockwise rotation<br>for turnout (degrees).</html>"));

        JLabel* rotationLabel = new JLabel(tr("Rotation"));
        rotationPanel->layout()->addWidget(rotationLabel);
        rotationPanel->layout()->addWidget(rotationComboBox);

        zoomPanel->layout()->addWidget(new JLabel(tr("%1").arg(tr("Zoom"))));
        zoomPanel->layout()->addWidget(zoomLabel);

        QSize coordSize = xLabel->sizeHint();
        coordSize.setWidth( coordSize.width() * 2);
        xLabel->resize(coordSize);
        yLabel->resize(coordSize);


        locationPanel->layout()->addWidget(new JLabel(tr("%1").arg(tr("Location"))));
        locationPanel->layout()->addWidget(new JLabel("{x:"));
        locationPanel->layout()->addWidget(xLabel);
        locationPanel->layout()->addWidget(new JLabel(", y:"));
        locationPanel->layout()->addWidget(yLabel);
        locationPanel->layout()->addWidget(new JLabel("}    "));

        //second row of edit tool bar items
        levelXingButton->setToolTip(tr("Select to add a level crossing track when next clicking with shift down."));
        trackButton->setToolTip(tr("Select to add a track segment when next clicking with shift down and dragging."));

        //this is enabled/disabled via selectionListAction above
        trackSegmentPropertiesPanel->layout()->addWidget(mainlineTrack);

        mainlineTrack->setChecked(false);
        mainlineTrack->setEnabled(false);
        mainlineTrack->setToolTip(tr("Sets track segment type - check for mainline track, uncheck for side track."));

        trackSegmentPropertiesPanel->layout()->addWidget(dashedLine);
        dashedLine->setChecked(false);
        dashedLine->setEnabled(false);
        dashedLine->setToolTip(tr("Sets track segment style - check for dashed, uncheck for solid."));

        //the blockPanel is enabled/disabled via selectionListAction above
        layoutEditor->setupComboBox(blockIDComboBox, false, true, false);
        blockIDComboBox->setToolTip(tr("Enter name of Block for new turnout, level crossing, or track segment."));

        highlightBlockCheckBox->setToolTip(tr("Check to highlight the selected block on the layout"));
//        highlightBlockCheckBox.addActionListener((ActionEvent event) -> {
//            layoutEditor.setHighlightSelectedBlock(highlightBlockCheckBox->isChecked());
//        });
        connect(highlightBlockCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_highlightBlockCheckBox()));
        highlightBlockCheckBox->setChecked(layoutEditor->getHighlightSelectedBlock());

        //change the block name
//        blockIDComboBox.addActionListener((ActionEvent event) -> {
//            //use the "Extra" color to highlight the selected block
//            if (layoutEditor.highlightSelectedBlockFlag) {
//                layoutEditor.highlightBlockInComboBox(blockIDComboBox);
//            }
//            String newName = blockIDComboBox.getSelectedItemDisplayName();
//            if (newName == null) {
//                newName = "";
//            }
//            LayoutBlock lb = InstanceManager.getDefault(LayoutBlockManager.class).getByUserName(newName);
//            if (lb != null) {
//                //if there is an occupancy sensor assigned already
//                String sensorName = lb.getOccupancySensorName();

//                if (!sensorName.isEmpty()) {
//                    //update the block sensor ComboBox
//                    blockSensorComboBox.setSelectedItem(lb.getOccupancySensor());
//                } else {
//                    blockSensorComboBox.setSelectedItem(null);
//                }
//            }
//        });

        layoutEditor->setupComboBox(blockSensorComboBox, false, true, false);
        blockSensorComboBox->setToolTip(tr("Enter name of occupancy sensor for this block; no entry means don't change."));

        //third row of edit tool bar items
        endBumperButton->setToolTip(tr("Select to add an end bumper track node when next clicking with shift down."));
        anchorButton->setToolTip(tr("Select to add an anchor track node when next clicking with shift down."));
        edgeButton->setToolTip(tr("Select to add an edge connector track node when next clicking with shift down."));
        textLabelButton->setToolTip(tr("Select to add a label with the entered text when next clicking with shift down."));

        textLabelTextField->setToolTip(tr("Enter text to be displayed in a new text label."));
        textLabelTextField->setEnabled(false);

        memoryButton->setToolTip(tr("Select to add a %1 when next clicking with shift down.").arg(tr("Memory")));

        layoutEditor->setupComboBox(textMemoryComboBox, true, false, false);
        textMemoryComboBox->setToolTip(tr("Enter name of memory variable to be displayed in a new memory label."));

        blockContentsButton->setToolTip(tr("Select to add a Block label when next clicking with shift down."));

        layoutEditor->setupComboBox(blockContentsComboBox, true, false, false);
        blockContentsComboBox->setToolTip(tr("Select to add a Block label when next clicking with shift down."));
//        blockContentsComboBox.addActionListener((ActionEvent event) -> {
//            //use the "Extra" color to highlight the selected block
//            if (layoutEditor.highlightSelectedBlockFlag) {
//                layoutEditor.highlightBlockInComboBox(blockContentsComboBox);
//            }
//        });
        connect(blockContentsComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_blockIdComboBox()));

        //fourth row of edit tool bar items
        //multi sensor...
        multiSensorButton->setToolTip(tr("Select to add a MultiSensor when next clicking with shift down."));

        //Signal Mast & text
        signalMastButton->setToolTip(tr("Select to add a Signal Mast icon when next clicking with shift down."));
        layoutEditor->setupComboBox(signalMastComboBox, true, false, false);

        //sensor icon & text
        sensorButton->setToolTip(tr("Select to add a Sensor icon when next clicking with shift down."));

        layoutEditor->setupComboBox(sensorComboBox, true, false, false);
        sensorComboBox->setToolTip(tr("Enter name of Sensor represented by a new Sensor icon."));

        sensorIconEditor = new MultiIconEditor(4);
        sensorIconEditor->setIcon(0, tr("%1").arg(tr("Active")),
                "resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
        sensorIconEditor->setIcon(1, tr("%1").arg(tr("Inactive")),
                "resources/icons/smallschematics/tracksegments/circuit-empty.gif");
        sensorIconEditor->setIcon(2, tr("%1").arg(tr("Inconsistent")),
                "resources/icons/smallschematics/tracksegments/circuit-error.gif");
        sensorIconEditor->setIcon(3, tr("%1").arg(tr("Unknown")),
                "resources/icons/smallschematics/tracksegments/circuit-error.gif");
        sensorIconEditor->complete();

        //Signal icon & text
        signalButton->setToolTip(tr("Select to add a Signal Head icon when next clicking with shift down."));

        layoutEditor->setupComboBox(signalHeadComboBox, true, false, false);
        signalHeadComboBox->setToolTip(tr("Enter name of Signal Head represented by a new signal head icon."));

        signalIconEditor = new MultiIconEditor(10);
        signalIconEditor->setIcon(0, "Red:", "resources/icons/smallschematics/searchlights/left-red-short.gif");
        signalIconEditor->setIcon(1, "Flash red:", "resources/icons/smallschematics/searchlights/left-flashred-short.gif");
        signalIconEditor->setIcon(2, "Yellow:", "resources/icons/smallschematics/searchlights/left-yellow-short.gif");
        signalIconEditor->setIcon(3,
                "Flash yellow:",
                "resources/icons/smallschematics/searchlights/left-flashyellow-short.gif");
        signalIconEditor->setIcon(4, "Green:", "resources/icons/smallschematics/searchlights/left-green-short.gif");
        signalIconEditor->setIcon(5, "Flash green:",
                "resources/icons/smallschematics/searchlights/left-flashgreen-short.gif");
        signalIconEditor->setIcon(6, "Dark:", "resources/icons/smallschematics/searchlights/left-dark-short.gif");
        signalIconEditor->setIcon(7, "Held:", "resources/icons/smallschematics/searchlights/left-held-short.gif");
        signalIconEditor->setIcon(8,
                "Lunar",
                "resources/icons/smallschematics/searchlights/left-lunar-short-marker.gif");
        signalIconEditor->setIcon(9,
                "Flash Lunar",
                "resources/icons/smallschematics/searchlights/left-flashlunar-short-marker.gif");
        signalIconEditor->complete();

        sensorFrame = new JFrame(tr("EditSensorIcons"));
        ((QVBoxLayout*)sensorFrame->getContentPane()->layout())->addWidget(new JLabel(tr("IconChangeInfo")), 0, Qt::AlignTop);//BorderLayout.NORTH);
        sensorFrame->getContentPane()->layout()->addWidget(sensorIconEditor);
        sensorFrame->pack();

        signalFrame = new JFrame(tr("EditSignalIcons"));
        ((QVBoxLayout*)signalFrame->getContentPane()->layout())->addWidget(new JLabel(tr("IconChangeInfo")),  0, Qt::AlignTop);//BorderLayout.NORTH);
        // no spaces around Label as that breaks html formatting
        signalFrame->getContentPane()->layout()->addWidget(signalIconEditor);
        signalFrame->pack();
        signalFrame->setVisible(false);

        //icon label
        iconLabelButton->setToolTip(tr("Select to add a general purpose icon when next clicking with shift down."));
        shapeButton->setToolTip(tr("Select to add a shape when next clicking with shift down."));

        //change icons...
        //this is enabled/disabled via selectionListAction above
//        changeIconsButton.addActionListener((ActionEvent event) -> {
//            if (sensorButton->isChecked()) {
//                sensorFrame.setVisible(true);
//            } else if (signalButton->isChecked()) {
//                signalFrame.setVisible(true);
//            } else if (iconLabelButton->isChecked()) {
//                iconFrame.setVisible(true);
//            } else {
//                //explain to the user why nothing happens
//                JOptionPane.showMessageDialog(null, tr("ChangeIconNotApplied"),
//                        tr("ChangeIcons"), JOptionPane.INFORMATION_MESSAGE);
//            }
//        });
        connect(changeIconsButton, SIGNAL(clicked(bool)), this, SLOT(on_changeIconsButton()));

        changeIconsButton->setToolTip(tr("Select to change icons used to represent Sensors, Signal Heads or Label (whichever is checked at the right)."));
        changeIconsButton->setEnabled(false);

        //??
        iconEditor = new MultiIconEditor(1);
        iconEditor->setIcon(0, "", "resources/icons/smallschematics/tracksegments/block.gif");
        iconEditor->complete();
        iconFrame = new JFrame(tr("EditIcon"));
        iconFrame->getContentPane()->layout()->addWidget(iconEditor);
        iconFrame->pack();
    }   //setupComponents()
#endif
    /**
     * layout the components in this panel
     */
    /*protected*/ void LayoutEditorToolBarPanel::layoutComponents() {
        log->error("layoutComponents called in LayoutEditorToolBarPanel base class");
    }

void LayoutEditorToolBarPanel::on_selectionListAction()
{
 //turnout properties
 bool e = (turnoutRHButton->isChecked()
         || turnoutLHButton->isChecked()
         || turnoutWYEButton->isChecked()
         || doubleXoverButton->isChecked()
         || rhXoverButton->isChecked()
         || lhXoverButton->isChecked()
         || layoutSingleSlipButton->isChecked()
         || layoutDoubleSlipButton->isChecked());
 log->debug(tr("turnoutPropertiesPanel is %1").arg(e ? "enabled" : "disabled"));
 turnoutNamePanel->setEnabled(e);

// for (Component i : turnoutNamePanel.getComponents()) {
//     i.setEnabled(e);
// }
 QList<QWidget*> list = turnoutNamePanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  w->setEnabled(e);
 }
 rotationPanel->setEnabled(e);

// for (Component i : rotationPanel.getComponents()) {
//     i.setEnabled(e);
// }
 list = rotationPanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  w->setEnabled(e);
 }

 //second turnout property
 e = (layoutSingleSlipButton->isChecked() || layoutDoubleSlipButton->isChecked());
 log->debug(tr("extraTurnoutPanel is %1").arg(e ? "enabled" : "disabled"));

// for (Component i : extraTurnoutPanel.getComponents()) {
//     i.setEnabled(e);
// }
 list = extraTurnoutPanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  w->setEnabled(e);
 }


 //track Segment properties
 e = trackButton->isChecked();
 log->debug(tr("trackSegmentPropertiesPanel is %1").arg(e ? "enabled" : "disabled"));

// for (Component i : trackSegmentPropertiesPanel.getComponents()) {
//     i.setEnabled(e);
// }
 list = trackSegmentPropertiesPanel->findChildren<QWidget*>();
 foreach (QWidget* w, list) {
  w->setEnabled(e);
 }

 //block properties
 e = (turnoutRHButton->isChecked()
         || turnoutLHButton->isChecked()
         || turnoutWYEButton->isChecked()
         || doubleXoverButton->isChecked()
         || rhXoverButton->isChecked()
         || lhXoverButton->isChecked()
         || layoutSingleSlipButton->isChecked()
         || layoutDoubleSlipButton->isChecked()
         || levelXingButton->isChecked()
         || trackButton->isChecked());
 log->debug(tr("blockPanel is %1").arg(e ? "enabled" : "disabled"));

 if (blockPropertiesPanel != nullptr) {
//     for (Component i : blockPropertiesPanel.getComponents()) {
//         i.setEnabled(e);
//     }
  QList<QWidget*> list = blockPropertiesPanel->findChildren<QWidget*>();
  foreach (QWidget* w, list) {
   w->setEnabled(e);
  }

     if (e) {
         blockPropertiesPanel->setBackground(QColor(Qt::lightGray));
     } else {
         blockPropertiesPanel->setBackground(QColor(238, 238, 238));
     }
 } else {
     blockLabel->setEnabled(e);
     blockIDComboBox->setEnabled(e);
     blockSensorLabel->setEnabled(e);
     blockSensorLabel->setEnabled(e);
     blockSensorComboBox->setEnabled(e);
 }

 //enable/disable text label, memory & block contents text fields
 textLabelTextField->setEnabled(textLabelButton->isChecked());
 textMemoryComboBox->setEnabled(memoryButton->isChecked());
 blockContentsComboBox->setEnabled(blockContentsButton->isChecked());

 //enable/disable signal mast, sensor & signal head text fields
 signalMastComboBox->setEnabled(signalMastButton->isChecked());
 sensorComboBox->setEnabled(sensorButton->isChecked());
 signalHeadComboBox->setEnabled(signalButton->isChecked());

 //changeIconsButton
 e = (sensorButton->isChecked()
         || signalButton->isChecked()
         || iconLabelButton->isChecked());
 log->debug(tr("changeIconsButton is %1").arg(e ? "enabled" : "disabled"));
 changeIconsButton->setEnabled(e);
}

void LayoutEditorToolBarPanel::on_highlightBlockCheckBox()
{
 layoutEditor->setHighlightSelectedBlock(highlightBlockCheckBox->isChecked());
}

void LayoutEditorToolBarPanel::on_blockIdComboBox()
{
 //use the "Extra" color to highlight the selected block
 if (layoutEditor->highlightSelectedBlockFlag) {
     layoutEditor->highlightBlockInComboBox(blockIDComboBox);
 }
 QString newName = blockIDComboBox->currentText();
 if (newName.isNull()) {
     newName = "";
 }
 LayoutBlock* lb = (LayoutBlock*)((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(newName);
 if (lb != nullptr) {
     //if there is an occupancy sensor assigned already
     QString sensorName = lb->getOccupancySensorName();

     if (!sensorName.isEmpty()) {
         //update the block sensor ComboBox
         blockSensorComboBox->setSelectedItem(lb->getOccupancySensor());
     } else {
         blockSensorComboBox->setSelectedItem(nullptr);
     }
 }
}

void LayoutEditorToolBarPanel::on_changeIconsButton()
{
 if (sensorButton->isChecked()) {
     sensorFrame->setVisible(true);
 } else if (signalButton->isChecked()) {
     signalFrame->setVisible(true);
 } else if (iconLabelButton->isChecked()) {
     iconFrame->setVisible(true);
 } else {
     //explain to the user why nothing happens
     JOptionPane::showMessageDialog(nullptr, tr("This only works when a Sensor, Signal Head or\nLabel is selected to the right of this button."),
             tr("Change Icons"), JOptionPane::INFORMATION_MESSAGE);
 }
}
    //initialize logging
    /*private*/ /*transient*/ /*final*/ /*static*/ Logger* LayoutEditorToolBarPanel::log = LoggerFactory::getLogger("LayoutEditorToolBarPanel");
