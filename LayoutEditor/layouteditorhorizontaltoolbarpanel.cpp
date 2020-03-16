#include "layouteditorhorizontaltoolbarpanel.h"
#include <QBoxLayout>
#include "jpanel.h"
#include "box.h"
#include "jlabel.h"
#include "flowlayout.h"
#include <QRadioButton>
#include "namedbeancombobox.h"
#include <QCheckBox>
#include "jtextfield.h"
#include <QPushButton>
/**
 * This is the horizontal toolbar panel
 *
 * @author George Warner Copyright: (c) 2019
 */
//@SuppressWarnings("serial")
//@SuppressFBWarnings(value = "SE_TRANSIENT_FIELD_NOT_RESTORED") //no Serializable support at present
// /*public*/ class LayoutEditorHorizontalToolBarPanel extends LayoutEditorToolBarPanel {

/**
 * constructor for LayoutEditorHorizontalToolBarPanel
 *
 * @param layoutEditor the layout editor that this is for
 */
/*public*/ LayoutEditorHorizontalToolBarPanel::LayoutEditorHorizontalToolBarPanel(/*@Nonnull */LayoutEditor* layoutEditor, QWidget* parent)
: LayoutEditorToolBarPanel(layoutEditor, parent)
{
    //super(layoutEditor);
 layoutComponents();
}   //constructor
#if 1
/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutEditorHorizontalToolBarPanel::layoutComponents()
{
 QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout());//this, BoxLayout.PAGE_AXIS));
    //setMaximumHeight(180);
    thisLayout->setMargin(0);
    thisLayout ->setSpacing(6);

    JPanel* outerBorderPanel = this;
    JPanel* innerBorderPanel = this;

    //Row 1
//    JPanel* hTop1Panel = new JPanel();
//    hTop1Panel->setLayout(new QHBoxLayout());//hTop1Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop1PanelLayout = new QHBoxLayout();
    hTop1PanelLayout->setMargin(0);
    hTop1PanelLayout->setSpacing(6);

    //Row 1 : Left Components
//    JPanel* hTop1Left = new JPanel(new FlowLayout(/*FlowLayout::LEFT, 5, 0*/));
    FlowLayout* hTop1LeftLayout = new FlowLayout();
    turnoutLabel = new JLabel(tr("%1").arg(tr("Turnout")));
    hTop1LeftLayout->addWidget(turnoutLabel);
    hTop1LeftLayout->addWidget(turnoutRHButton);
    hTop1LeftLayout->addWidget(turnoutLHButton);
    hTop1LeftLayout->addWidget(turnoutWYEButton);
    hTop1LeftLayout->addWidget(doubleXoverButton);
    hTop1LeftLayout->addWidget(rhXoverButton);
    hTop1LeftLayout->addWidget(lhXoverButton);
    hTop1LeftLayout->addWidget(layoutSingleSlipButton);
    hTop1LeftLayout->addWidget(layoutDoubleSlipButton);
    hTop1PanelLayout->addLayout(hTop1LeftLayout);

    if (toolBarIsWide) {
        //hTop1Panel->layout()->addWidget(Box::createHorizontalGlue());

//        JPanel* hTop1Right = new JPanel(new FlowLayout(/*FlowLayout::RIGHT, 5, 0*/));
     FlowLayout* hTop1RightLayout = new FlowLayout();
        hTop1RightLayout->addWidget(turnoutNamePanel);
        hTop1RightLayout->addWidget(extraTurnoutPanel);
        hTop1RightLayout->addWidget(rotationPanel);
        hTop1PanelLayout->addLayout(hTop1RightLayout);
    }
    //innerBorderPanel->layout()->addWidget(hTop1Panel);
    thisLayout->addLayout(hTop1PanelLayout);

    //row 2
    if (!toolBarIsWide) {
//        JPanel* hTop2Panel = new JPanel();
     QHBoxLayout* hTop2PanelLayout = new QHBoxLayout();
//        hTop2Panel->setLayout(new QHBoxLayout());//hTop2Panel, BoxLayout.LINE_AXIS));
        hTop2PanelLayout->setMargin(0);
        hTop2PanelLayout->setSpacing(6);

        //Row 2 : Left Components
//        JPanel* hTop2Center = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
        FlowLayout* hTop2CenterLayout = new FlowLayout();
        hTop2CenterLayout->addWidget(turnoutNamePanel);
        hTop2CenterLayout->addWidget(extraTurnoutPanel);
        hTop2CenterLayout->addWidget(rotationPanel);
        hTop1PanelLayout->addLayout(hTop2CenterLayout);

        //innerBorderPanel->layout()->addWidget(hTop2Panel);
        thisLayout->addLayout(hTop2PanelLayout);
    }

    //Row 3 (2 wide)
//    JPanel* hTop3Panel = new JPanel();
//    hTop3Panel->setLayout(new QHBoxLayout());//hTop3Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop3PanelLayout = new QHBoxLayout();
    hTop3PanelLayout->setMargin(0);
    hTop3PanelLayout->setSpacing(6);

    //Row 3 : Left Components
//    JPanel* hTop3Left = new JPanel(new FlowLayout(/*FlowLayout::LEFT, 5, 0*/));
    FlowLayout* hTop3LeftLayout = new FlowLayout();
    trackLabel = new JLabel(tr("%1").arg(tr("Track")));

    hTop3LeftLayout->addWidget(trackLabel);
    hTop3LeftLayout->addWidget(levelXingButton);
    hTop3LeftLayout->addWidget(trackButton);
    hTop3LeftLayout->addWidget(trackSegmentPropertiesPanel);

    hTop3PanelLayout->addLayout(hTop3LeftLayout);
    //hTop3Panel->layout()->addWidget(Box::createHorizontalGlue());

    //Row 3 : Center Components
//    JPanel* hTop3Center = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
    FlowLayout* hTop3CenterLayout = new FlowLayout();
    hTop3CenterLayout->addWidget(blockLabel);
    hTop3CenterLayout->addWidget(blockIDComboBox);
    hTop3CenterLayout->addWidget(highlightBlockCheckBox);

//    JPanel* hTop3CenterA = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
    //FlowLayout* hTop3CenterALayout = new FlowLayout();
    hTop3CenterLayout->addWidget(blockSensorLabel);
    hTop3CenterLayout->addWidget(blockSensorComboBox);
//        hTop3CenterA.setBorder(new EmptyBorder(0, 20, 0, 0));
    //hTop3CenterLayout->addLayout(hTop3CenterALayout);

    hTop3PanelLayout->addLayout(hTop3CenterLayout);
    //hTop3Panel->layout()->addWidget(Box::createHorizontalGlue());

    if (toolBarIsWide) {
        //row 3 : Right Components
//        JPanel* hTop3Right = new JPanel(new FlowLayout(/*FlowLayout::RIGHT, 5, 0*/));
     FlowLayout* hTop3RightLayout = new FlowLayout();
        hTop3RightLayout->addWidget(zoomPanel);
        hTop3RightLayout->addWidget(locationPanel);
        hTop3PanelLayout->addLayout(hTop3RightLayout);
    }
    //outerBorderPanel->layout()->addWidget(hTop3Panel);
    thisLayout->addLayout(hTop3PanelLayout);

    //Row 4
//    JPanel* hTop4Panel = new JPanel();
//    hTop4Panel->setLayout(new QHBoxLayout());//hTop4Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop4PanelLayout = new QHBoxLayout();
    hTop4PanelLayout->setMargin(0);
    hTop4PanelLayout->setSpacing(6);

    //Row 4 : Left Components
//    JPanel* hTop4Left = new JPanel(new FlowLayout(/*FlowLayout::LEFT, 5, 0*/));
    FlowLayout* hTop4LeftLayout = new FlowLayout();
    hTop4LeftLayout->addWidget(new JLabel(tr("%1").arg(tr("Nodes"))));
    hTop4LeftLayout->addWidget(endBumperButton);
    hTop4LeftLayout->addWidget(anchorButton);
    hTop4LeftLayout->addWidget(edgeButton);
    hTop4PanelLayout->addLayout(hTop4LeftLayout);
    //hTop4Panel->layout()->addWidget(Box::createHorizontalGlue());

    if (!toolBarIsWide) {
        //Row 4 : Right Components
//        JPanel* hTop4Right = new JPanel(new FlowLayout(/*FlowLayout::RIGHT, 5, 0*/));
     FlowLayout* hTop4RightLayout = new FlowLayout();
        hTop4RightLayout->addWidget(zoomPanel);
        hTop4RightLayout->addWidget(locationPanel);
        hTop4PanelLayout->addLayout(hTop4RightLayout);
    }
    //thisLayout->addWidget(hTop4Panel);
    thisLayout->addLayout(hTop4PanelLayout);

    //Row 5 Components (wide 4-center)
    labelsLabel = new JLabel(tr("%1").arg(tr("Labels")));
    if (toolBarIsWide) {
//        JPanel* hTop4Center = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
     FlowLayout* hTop4CenterLayout = new FlowLayout();
        hTop4CenterLayout->addWidget(labelsLabel);
        hTop4CenterLayout->addWidget(textLabelButton);
        hTop4CenterLayout->addWidget(textLabelTextField);
        hTop4CenterLayout->addWidget(memoryButton);
        hTop4CenterLayout->addWidget(textMemoryComboBox);
        hTop4CenterLayout->addWidget(blockContentsButton);
        hTop4CenterLayout->addWidget(blockContentsComboBox);
        hTop4PanelLayout->addLayout(hTop4CenterLayout);
        //hTop4Panel->layout()->addWidget(Box::createHorizontalGlue());
        thisLayout->addLayout(hTop4PanelLayout);
    }
    else {
        thisLayout->addLayout(hTop4PanelLayout);

//        JPanel* hTop5Left = new JPanel(new FlowLayout(/*FlowLayout::LEFT, 5, 0*/));
        FlowLayout* hTop5LeftLayout = new FlowLayout();
        hTop5LeftLayout->addWidget(labelsLabel);
        hTop5LeftLayout->addWidget(textLabelButton);
        hTop5LeftLayout->addWidget(textLabelTextField);
        hTop5LeftLayout->addWidget(memoryButton);
        hTop5LeftLayout->addWidget(textMemoryComboBox);
        hTop5LeftLayout->addWidget(blockContentsButton);
        hTop5LeftLayout->addWidget(blockContentsComboBox);
        //hTop5LeftLayout->addWidget(Box::createHorizontalGlue());
        thisLayout->addLayout(hTop5LeftLayout);
    }

    //Row 6
//    JPanel* hTop6Panel = new JPanel();
//    hTop6Panel->setLayout(new QHBoxLayout());//hTop6Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop6PanelLayout = new QHBoxLayout();
    hTop6PanelLayout->setMargin(0);
    hTop6PanelLayout->setSpacing(6);

    //Row 6 : Left Components
    //JPanel* hTop6Left = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
    FlowLayout* hTop6LeftLayout = new FlowLayout();
    hTop6LeftLayout->addWidget(multiSensorButton);
    hTop6LeftLayout->addWidget(changeIconsButton);
    hTop6LeftLayout->addWidget(sensorButton);
    hTop6LeftLayout->addWidget(sensorComboBox);
    hTop6LeftLayout->addWidget(signalMastButton);
    hTop6LeftLayout->addWidget(signalMastComboBox);
    hTop6LeftLayout->addWidget(signalButton);
    hTop6LeftLayout->addWidget(signalHeadComboBox);
    hTop6LeftLayout->addWidget(new JLabel(" "));
    hTop6LeftLayout->addWidget(iconLabelButton);
    hTop6LeftLayout->addWidget(shapeButton);

    hTop6PanelLayout->addLayout(hTop6LeftLayout);
    thisLayout->addLayout(hTop6PanelLayout);
}   //layoutComponents

#endif
