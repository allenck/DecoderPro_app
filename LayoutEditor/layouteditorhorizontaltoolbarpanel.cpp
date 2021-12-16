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
 setupComponents();
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
    JPanel* hTop1Panel = new JPanel();
    QHBoxLayout* hTop1PanelLayout = new QHBoxLayout();
    hTop1Panel->setLayout(hTop1PanelLayout = new QHBoxLayout());//hTop1Panel, BoxLayout.LINE_AXIS));
    hTop1PanelLayout->setMargin(0);
    hTop1PanelLayout->setSpacing(6);

    //Row 1 : Left Components
    JPanel* hTop1Left = new JPanel(/*FlowLayout::LEFT, 5, 0*/);
    FlowLayout* hTop1LeftLayout = new FlowLayout();
    hTop1Left->setLayout(hTop1LeftLayout);
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
    hTop1PanelLayout->addWidget(hTop1Left);

    if (toolBarIsWide) {
        hTop1Panel->layout()->addWidget(Box::createHorizontalGlue());

     JPanel* hTop1Right = new JPanel(/*FlowLayout::RIGHT, 5, 0*/);
     FlowLayout* hTop1RightLayout = new FlowLayout();
     hTop1Right->setLayout(hTop1RightLayout);
     hTop1RightLayout->addWidget(turnoutNamePanel);
     hTop1RightLayout->addWidget(extraTurnoutPanel);
     hTop1RightLayout->addWidget(rotationPanel);
     hTop1PanelLayout->addWidget(hTop1Right);
    }
    //innerBorderPanel->layout()->addWidget(hTop1Panel);
    thisLayout->addWidget(hTop1Panel,1);

    //row 2
    if (!toolBarIsWide) {
     JPanel* hTop2Panel = new JPanel();
     QHBoxLayout* hTop2PanelLayout = new QHBoxLayout();
     hTop2Panel->setLayout(hTop2PanelLayout);//hTop2Panel, BoxLayout.LINE_AXIS));
     hTop2PanelLayout->setMargin(0);
     hTop2PanelLayout->setSpacing(6);

     //Row 2 : Left Components
     JPanel* hTop2Center = new JPanel(/*FlowLayout::CENTER, 5, 0*/);
     FlowLayout* hTop2CenterLayout = new FlowLayout();
     hTop2Center->setLayout(hTop2CenterLayout);
     hTop2CenterLayout->addWidget(turnoutNamePanel);
     hTop2CenterLayout->addWidget(extraTurnoutPanel);
     hTop2CenterLayout->addWidget(rotationPanel);
     hTop1PanelLayout->addWidget(hTop2Center);

     //innerBorderPanel->layout()->addWidget(hTop2Panel);
     thisLayout->addWidget(hTop2Panel,1);
    }

    //Row 3 (2 wide)
    JPanel* hTop3Panel = new JPanel();
//    hTop3Panel->setLayout(new QHBoxLayout());//hTop3Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop3PanelLayout = new QHBoxLayout(hTop3Panel);
    hTop3PanelLayout->setMargin(0);
    hTop3PanelLayout->setSpacing(6);

    //Row 3 : Left Components
    JPanel* hTop3Left = new JPanel(/*FlowLayout::LEFT, 5, 0*/);
    FlowLayout* hTop3LeftLayout = new FlowLayout(hTop3Left);
    trackLabel = new JLabel(tr("%1").arg(tr("Track")));

    hTop3LeftLayout->addWidget(trackLabel);
    hTop3LeftLayout->addWidget(levelXingButton);
    hTop3LeftLayout->addWidget(trackButton);
    hTop3LeftLayout->addWidget(trackSegmentPropertiesPanel);

    hTop3PanelLayout->addWidget(hTop3Left);
    hTop3Panel->layout()->addWidget(Box::createHorizontalGlue());

    //Row 3 : Center Components
    JPanel* hTop3Center = new JPanel(/*FlowLayout::CENTER, 5, 0*/);
    FlowLayout* hTop3CenterLayout = new FlowLayout(hTop3Center);
    //QHBoxLayout* hTop3CenterLayout = new QHBoxLayout();
    hTop3CenterLayout->addWidget(blockLabel);
    hTop3CenterLayout->addWidget(blockIDComboBox);
    hTop3CenterLayout->addWidget(highlightBlockCheckBox);

    JPanel* hTop3CenterA = new JPanel(new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
    //FlowLayout* hTop3CenterALayout = new FlowLayout();
    hTop3CenterLayout->addWidget(blockSensorLabel);
    hTop3CenterLayout->addWidget(blockSensorComboBox);
//        hTop3CenterA.setBorder(new EmptyBorder(0, 20, 0, 0));
    hTop3CenterLayout->addWidget(hTop3CenterA);

    hTop3PanelLayout->addWidget(hTop3Center);
    hTop3Panel->layout()->addWidget(Box::createHorizontalGlue());

    if (toolBarIsWide) {
     //row 3 : Right Components
     JPanel* hTop3Right = new JPanel(/*FlowLayout::RIGHT, 5, 0*/);
     FlowLayout* hTop3RightLayout = new FlowLayout(hTop3Right);
        hTop3RightLayout->addWidget(zoomPanel);
        hTop3RightLayout->addWidget(locationPanel);
        hTop3PanelLayout->addWidget(hTop3Right);
    }
//    outerBorderPanel->layout()->addWidget(hTop3Panel);
    thisLayout->addWidget(hTop3Panel,1);

    //Row 4
    JPanel* hTop4Panel = new JPanel();
//    hTop4Panel->setLayout(new QHBoxLayout());//hTop4Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop4PanelLayout = new QHBoxLayout(hTop4Panel);
    hTop4PanelLayout->setMargin(0);
    hTop4PanelLayout->setSpacing(6);

    //Row 4 : Left Components
    JPanel* hTop4Left = new JPanel(/*FlowLayout::LEFT, 5, 0*/);
    FlowLayout* hTop4LeftLayout = new FlowLayout(hTop4Left);
    hTop4LeftLayout->addWidget(new JLabel(tr("%1").arg(tr("Nodes"))));
    hTop4LeftLayout->addWidget(endBumperButton);
    hTop4LeftLayout->addWidget(anchorButton);
    hTop4LeftLayout->addWidget(edgeButton);
    hTop4PanelLayout->addWidget(hTop4Left);
    hTop4Panel->layout()->addWidget(Box::createHorizontalGlue());

    if (!toolBarIsWide) {
     //Row 4 : Right Components
     JPanel* hTop4Right = new JPanel(/*FlowLayout::RIGHT, 5, 0*/);
     FlowLayout* hTop4RightLayout = new FlowLayout(hTop4Right);
     hTop4RightLayout->addWidget(zoomPanel);
     hTop4RightLayout->addWidget(locationPanel);
     hTop4PanelLayout->addWidget(hTop4Right);
    }
    //thisLayout->addWidget(hTop4Panel);
    thisLayout->addWidget(hTop4Panel,1);

    //Row 5 Components (wide 4-center)
    labelsLabel = new JLabel(tr("%1").arg(tr("Labels")));
    if (toolBarIsWide) {
     JPanel* hTop4Center = new JPanel(/*FlowLayout::CENTER, 5, 0*/);
     FlowLayout* hTop4CenterLayout = new FlowLayout(hTop4Center);
     //QHBoxLayout* hTop4CenterLayout = new QHBoxLayout();
        hTop4CenterLayout->addWidget(labelsLabel);
        hTop4CenterLayout->addWidget(textLabelButton);
        hTop4CenterLayout->addWidget(textLabelTextField);
        hTop4CenterLayout->addWidget(memoryButton);
        hTop4CenterLayout->addWidget(textMemoryComboBox);
        hTop4CenterLayout->addWidget(blockContentsButton);
        hTop4CenterLayout->addWidget(blockContentsComboBox);
        hTop4PanelLayout->addWidget(hTop4Center);
        hTop4Panel->layout()->addWidget(Box::createHorizontalGlue());
        thisLayout->addWidget(hTop4Panel,1);
    }
    else {
        thisLayout->addWidget(hTop4Panel,1);

        JPanel* hTop5Left = new JPanel(/*FlowLayout::LEFT, 5, 0*/);
        FlowLayout* hTop5LeftLayout = new FlowLayout(hTop5Left);
        //QHBoxLayout* hTop5LeftLayout = new QHBoxLayout(hTop5Left);
        hTop5LeftLayout->addWidget(labelsLabel);
        hTop5LeftLayout->addWidget(textLabelButton);
        hTop5LeftLayout->addWidget(textLabelTextField);
        hTop5LeftLayout->addWidget(memoryButton);
        hTop5LeftLayout->addWidget(textMemoryComboBox);
        hTop5LeftLayout->addWidget(blockContentsButton);
        hTop5LeftLayout->addWidget(blockContentsComboBox);
        hTop5LeftLayout->addWidget(Box::createHorizontalGlue());
        thisLayout->addWidget(hTop5Left,1);
    }

    //Row 6
    JPanel* hTop6Panel = new JPanel();
//    hTop6Panel->setLayout(new QHBoxLayout());//hTop6Panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* hTop6PanelLayout = new QHBoxLayout(hTop6Panel);
    hTop6PanelLayout->setMargin(0);
    hTop6PanelLayout->setSpacing(6);

    //Row 6 : Left Components
    JPanel* hTop6Left = new JPanel();//new FlowLayout(/*FlowLayout::CENTER, 5, 0*/));
    //FlowLayout* hTop6LeftLayout = new FlowLayout();
    QHBoxLayout* hTop6LeftLayout = new QHBoxLayout();
    hTop6Left->setLayout(hTop6LeftLayout);
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

    hTop6PanelLayout->addWidget(hTop6Left);
    thisLayout->addWidget(hTop6Panel,1);
}   //layoutComponents

#endif
