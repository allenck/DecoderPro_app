#include "layouteditorfloatingtoolbarpanel.h"
#include "jtabbedpane.h"
#include "emptyborder.h"
#include "flowlayout.h"
#include "jlabel.h"
#include "namedbeancombobox.h"
#include <QCheckBox>
#include <QRadioButton>
#include "jtextfield.h"
#include <QPushButton>

/**
 * This is the floating toolbar panel
 *
 * @author George Warner Copyright: (c) 2017-2019
 */
//@SuppressWarnings("serial")
//@SuppressFBWarnings(value = "SE_TRANSIENT_FIELD_NOT_RESTORED") //no Serializable support at present
// /*public*/ class LayoutEditorFloatingToolBarPanel extends LayoutEditorToolBarPanel {


/**
 * constructor for LayoutEditorFloatingToolBarPanel
 *
 * @param layoutEditor the layout editor that this is for
 */
/*public*/ LayoutEditorFloatingToolBarPanel::LayoutEditorFloatingToolBarPanel(/*@Nonnull*/ LayoutEditor* layoutEditor)
 : LayoutEditorToolBarPanel(layoutEditor)
{
 //super(layoutEditor);
 setupComponents();
 layoutComponents();
}   //constructor

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutEditorFloatingToolBarPanel::setupComponents() {
    LayoutEditorToolBarPanel::setupComponents();

    floatEditTabsPanel = new JPanel();
    floatEditTabsPanel->setLayout(new QVBoxLayout());
    floatEditTabsPane = new JTabbedPane();
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutEditorFloatingToolBarPanel::layoutComponents() {
    /*
     *  JPanel - floatEditTabsPanel
     *      JTabbedPane - floatEditTabsPane
     *          ...
     *      JPanel - floatEditLocationPanel
     *          ...
     *      JPanel - floatEditActionPanel  (currently disabled)
     *          ...
     *      JPanel - floatEditHelpPanel
     *          ...
     */
    setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));

    //FlowLayout floatContentLayout = new FlowLayout(FlowLayout.CENTER, 5, 2); //5 pixel gap between items, 2 vertical gap

    //Contains the block and sensor combo boxes.
    //It is moved to the appropriate detail pane when the tab changes.
    blockPropertiesPanel = new JPanel();
    blockPropertiesPanel->setLayout(new QVBoxLayout());//blockPropertiesPanel, BoxLayout.Y_AXIS));

    JPanel* blockPanel = new JPanel(/*floatContentLayout*/);
    FlowLayout* blockPanelLayout = new FlowLayout();
    blockPanelLayout->addWidget(blockLabel);
    blockPanelLayout->addWidget(blockIDComboBox);
    blockPanelLayout->addWidget(highlightBlockCheckBox);
    blockPropertiesPanel->layout()->addWidget(blockPanel);

    JPanel* blockSensorPanel = new JPanel(/*floatContentLayout*/);
    FlowLayout* blockSensorPanelLayout =  new FlowLayout();
    blockSensorPanelLayout->addWidget(blockSensorLabel);
    blockSensorPanelLayout->addWidget(blockSensorComboBox);
    blockSensorPanel->setBorder(new EmptyBorder(0, 20, 0, 0));
    blockPropertiesPanel->layout()->addWidget(blockSensorPanel);

    //Begin the tabs structure
    //
    //Tab 0 - Turnouts
    floatEditTurnout = new JPanel();
    floatEditTurnout->setLayout(floatEditTurnoutLayout = new QVBoxLayout());//floatEditTurnout, BoxLayout.Y_AXIS));

    JPanel* turnoutGroup1 = new JPanel(/*floatContentLayout*/);
    FlowLayout* turnoutGroup1Layout =  new FlowLayout(turnoutGroup1);
    turnoutGroup1Layout->addWidget(turnoutRHButton);
    turnoutGroup1Layout->addWidget(turnoutLHButton);
    turnoutGroup1Layout->addWidget(turnoutWYEButton);
    turnoutGroup1Layout->addWidget(layoutSingleSlipButton);
    turnoutGroup1Layout->addWidget(layoutDoubleSlipButton);
    floatEditTurnout->layout()->addWidget(turnoutGroup1);

    JPanel* turnoutGroup2 = new JPanel(/*floatContentLayout*/);
    FlowLayout* turnoutGroup2Layout =  new FlowLayout(turnoutGroup2);
    turnoutGroup2Layout->addWidget(doubleXoverButton);
    turnoutGroup2Layout->addWidget(rhXoverButton);
    turnoutGroup2Layout->addWidget(lhXoverButton);
    floatEditTurnout->layout()->addWidget(turnoutGroup2);

    JPanel* turnoutGroup3 = new JPanel(/*floatContentLayout*/);
    FlowLayout* turnoutGroup3Layout =  new FlowLayout(turnoutGroup3);
    turnoutGroup3Layout->addWidget(turnoutNamePanel);
    floatEditTurnout->layout()->addWidget(turnoutGroup3);

    JPanel* turnoutGroup3a = new JPanel(/*floatContentLayout*/);
    FlowLayout* turnoutGroup3aLayout =  new FlowLayout(turnoutGroup3a);
    turnoutGroup3aLayout->addWidget(extraTurnoutPanel);
    floatEditTurnout->layout()->addWidget(turnoutGroup3a);

    JPanel* turnoutGroup4 = new JPanel(/*floatContentLayout*/);
    FlowLayout* turnoutGroup4lLayout =  new FlowLayout(turnoutGroup4);
    turnoutGroup4lLayout->addWidget(rotationPanel);
    floatEditTurnout->layout()->addWidget(turnoutGroup4);

    floatEditTurnoutLayout->addWidget(blockPropertiesPanel);

    floatEditTabsPane->addTab(tr("Turnouts"), QIcon(), floatEditTurnout, "");

    //Tab 1 - Track
    floatEditTrack = new JPanel();
    floatEditTrack->setLayout(floatEditTrackLayout = new QVBoxLayout());//floatEditTrack, BoxLayout.Y_AXIS));

    JPanel* trackGroup1 = new JPanel(/*floatContentLayout*/);
    FlowLayout* trackGroup1Layout =  new FlowLayout(trackGroup1);
    trackGroup1Layout->addWidget(endBumperButton);
    trackGroup1Layout->addWidget(anchorButton);
    trackGroup1Layout->addWidget(edgeButton);
    floatEditTrack->layout()->addWidget(trackGroup1);

    JPanel* trackGroup2 = new JPanel(/*floatContentLayout*/);
    FlowLayout* trackGroup2Layout =  new FlowLayout(trackGroup2);
    trackGroup2Layout->addWidget(trackButton);
    trackGroup2Layout->addWidget(levelXingButton);
    floatEditTrack->layout()->addWidget(trackGroup2);

    JPanel* trackGroup3 = new JPanel(/*floatContentLayout*/);
    FlowLayout* trackGroup3Layout =  new FlowLayout(trackGroup3);
    trackGroup3Layout->addWidget(trackSegmentPropertiesPanel);
    floatEditTrack->layout()->addWidget(trackGroup3);

    floatEditTabsPane->addTab(tr("Track"), QIcon(), floatEditTrack, "");

    //Tab 2 - Labels
    JPanel* floatEditLabel = new JPanel();
    floatEditLabel->setLayout(new QVBoxLayout());//floatEditLabel, BoxLayout.Y_AXIS));

    JPanel* labelGroup1 = new JPanel(/*floatContentLayout*/);
    FlowLayout* labelGroup1Layout =  new FlowLayout(labelGroup1);
    labelGroup1Layout->addWidget(textLabelButton);
    labelGroup1Layout->addWidget(textLabelTextField);
    floatEditLabel->layout()->addWidget(labelGroup1);

    JPanel* labelGroup2 = new JPanel(/*floatContentLayout*/);
    FlowLayout* labelGroup2Layout =  new FlowLayout(labelGroup2);
    labelGroup2Layout->addWidget(memoryButton);
    labelGroup2Layout->addWidget(textMemoryComboBox);
    floatEditLabel->layout()->addWidget(labelGroup2);

    JPanel* labelGroup3 = new JPanel(/*floatContentLayout*/);
    FlowLayout* labelGroup3Layout =  new FlowLayout(labelGroup3);
    labelGroup3Layout->addWidget(blockContentsButton);
    labelGroup3Layout->addWidget(blockContentsComboBox);
    floatEditLabel->layout()->addWidget(labelGroup3);

    floatEditTabsPane->addTab(tr("Label"), QIcon(), floatEditLabel, "");

    //Tab 3 - Icons
    JPanel* floatEditIcon = new JPanel();
    floatEditIcon->setLayout(new QVBoxLayout());//floatEditIcon, BoxLayout.Y_AXIS));

    JPanel* iconGroup1 = new JPanel(/*floatContentLayout*/);
    FlowLayout* iconGroup1Layout =  new FlowLayout(iconGroup1);
    iconGroup1Layout->addWidget(multiSensorButton);
    iconGroup1Layout->addWidget(changeIconsButton);
    floatEditIcon->layout()->addWidget(iconGroup1);

    JPanel* iconGroup2 = new JPanel(/*floatContentLayout*/);
    FlowLayout* iconGroup2Layout =  new FlowLayout(iconGroup2);
    iconGroup2Layout->addWidget(sensorButton);
    iconGroup2Layout->addWidget(sensorComboBox);
    floatEditIcon->layout()->addWidget(iconGroup2);

    JPanel* iconGroup3 = new JPanel(/*floatContentLayout*/);
    FlowLayout* iconGroup3Layout =  new FlowLayout(iconGroup3);
    iconGroup3Layout->addWidget(signalMastButton);
    iconGroup3Layout->addWidget(signalMastComboBox);
    floatEditIcon->layout()->addWidget(iconGroup3);

    JPanel* iconGroup4 = new JPanel(/*floatContentLayout*/);
    FlowLayout* iconGroup4Layout =  new FlowLayout(iconGroup4);
    iconGroup4Layout->addWidget(signalButton);
    iconGroup4Layout->addWidget(signalHeadComboBox);
    floatEditIcon->layout()->addWidget(iconGroup4);

    JPanel* iconGroup5 = new JPanel(/*floatContentLayout*/);
    FlowLayout* iconGroup5Layout =  new FlowLayout(iconGroup5);
    iconGroup5Layout->addWidget(iconLabelButton);
    iconGroup5Layout->addWidget(shapeButton);
    floatEditIcon->layout()->addWidget(iconGroup5);

    floatEditTabsPane->addTab(tr("Icon"), QIcon(), floatEditIcon, "");
    floatEditTabsPanel->layout()->addWidget(floatEditTabsPane);
    ((QVBoxLayout*)layout())->addWidget(floatEditTabsPanel, 1);

    //End the tabs structure
    //The next 3 groups reside under the tab secton
    JPanel* floatEditLocationPanel = new JPanel(new FlowLayout());
    floatEditLocationPanel->layout()->addWidget(zoomPanel);
    floatEditLocationPanel->layout()->addWidget(locationPanel);
    ((QVBoxLayout*)layout())->addWidget(floatEditLocationPanel);

//    floatEditTabsPane.addChangeListener((e) ->
//    {
//        //Move the block group between the turnouts and track tabs
//        int selIndex = floatEditTabsPane.getSelectedIndex();

//        if (selIndex == 0) {
//            floatEditTurnout->layout()->addWidget(blockPropertiesPanel);
//        } else if (selIndex == 1) {
//            floatEditTrack->layout()->addWidget(blockPropertiesPanel);
//        }
//    });
    connect(floatEditTabsPane, SIGNAL(tabBarClicked(int)), this, SLOT(onTabBar(int)));
    floatEditTabsPane->setCurrentIndex(0);
    floatEditTurnout->layout()->addWidget(blockPropertiesPanel);

// JPanel floatEditActionPanel = new JPanel();
    // floatEditActionPanel->layout()->addWidget(new JLabel("floatEditActionPanel", JLabel.CENTER));
    // add(floatEditActionPanel);
}   //layoutComponents

/*public*/ JTabbedPane* LayoutEditorFloatingToolBarPanel::getfloatEditTabsPane() {
    return floatEditTabsPane;
}

void LayoutEditorFloatingToolBarPanel::onTabBar(int)
{
    //Move the block group between the turnouts and track tabs
    int selIndex = floatEditTabsPane->currentIndex();
    QObject* parent = blockPropertiesPanel->parent();
    if(parent)
    {
     if(qobject_cast<QWidget*>(parent))
     {
      qobject_cast<QWidget*>(parent)->layout()->removeWidget(blockPropertiesPanel);
     }
    }

    if (selIndex == 0) {
        floatEditTurnout->layout()->addWidget(blockPropertiesPanel);
    } else if (selIndex == 1) {
        floatEditTrack->layout()->addWidget(blockPropertiesPanel);
    }
}//);
