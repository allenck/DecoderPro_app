#include "layouteditorverticaltoolbarpanel.h"
#include <QBoxLayout>
#include "jpanel.h"
#include "flowlayout.h"
#include "limits.h"
#include "box.h"
#include "titledborder.h"
#include "borderfactory.h"
#include "jlabel.h"
#include <QRadioButton>
#include "namedbeancombobox.h"
#include <QCheckBox>
#include "jlabel.h"
#include "jtextfield.h"
#include <QPushButton>
#include "titledborder.h"
#include "borderfactory.h"

/**
 * This is the vertical toolbar panel
 *
 * @author George Warner Copyright: (c) 2019
 */
//@SuppressWarnings("serial")
//@SuppressFBWarnings(value = "SE_TRANSIENT_FIELD_NOT_RESTORED") //no Serializable support at present
// /*public*/ class LayoutEditorVerticalToolBarPanel extends LayoutEditorToolBarPanel {

/**
 * constructor for LayoutEditorVerticalToolBarPanel
 *
 * @param layoutEditor the layout editor that this is for
 */
/*public*/ LayoutEditorVerticalToolBarPanel::LayoutEditorVerticalToolBarPanel(/*@Nonnull*/ LayoutEditor* layoutEditor, QWidget *parent)
: LayoutEditorToolBarPanel(layoutEditor){
    //super(layoutEditor);
layoutComponents();
}   //constructor

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutEditorVerticalToolBarPanel::layoutComponents()
{
    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout());//this, BoxLayout.PAGE_AXIS));

    Border* blacklineBorder = BorderFactory::createLineBorder(QColor(Qt::black));

    JPanel* outerBorderPanel = new JPanel();
    outerBorderPanel->setLayout(new QVBoxLayout());//outerBorderPanel, BoxLayout.PAGE_AXIS));
    TitledBorder* outerTitleBorder = BorderFactory::createTitledBorder(blacklineBorder, tr("Track"));
    outerTitleBorder->setTitleJustification(TitledBorder::CENTER);
    outerTitleBorder->setTitlePosition(TitledBorder::BOTTOM);
    outerBorderPanel->setBorder(outerTitleBorder);

    JPanel* innerBorderPanel = new JPanel();
    QVBoxLayout* innerBorderPanelLayout;
    innerBorderPanel->setLayout(innerBorderPanelLayout = new QVBoxLayout());//innerBorderPanel, BoxLayout.PAGE_AXIS));
    TitledBorder* beanNameTitleBorder = BorderFactory::createTitledBorder(blacklineBorder, tr("Turnouts"));
    beanNameTitleBorder->setTitleJustification(TitledBorder::CENTER);
    beanNameTitleBorder->setTitlePosition(TitledBorder::BOTTOM);
    innerBorderPanel->setBorder(beanNameTitleBorder);

    //FlowLayout* verticalContentLayout = new FlowLayout(FlowLayout::LEFT, 5, 2); //5 pixel gap between items, 2 vertical gap

    turnoutLabel = new JLabel(tr("-- %1 --").arg(tr("Turnout")));

//        JPanel* vTop1Panel = new JPanel(verticalContentLayout);
    FlowLayout* vTop1PanelLayout = new FlowLayout();
    vTop1PanelLayout->addWidget(turnoutLHButton);
    vTop1PanelLayout->addWidget(turnoutRHButton);
    innerBorderPanelLayout->addLayout(vTop1PanelLayout);

    JPanel* vTop2Panel = new JPanel(new FlowLayout());
    vTop2Panel->layout()->addWidget(turnoutWYEButton);
    vTop2Panel->layout()->addWidget(doubleXoverButton);
    vTop2Panel->setMaximumSize(QSize(INT_MAX, vTop2Panel->sizeHint().height() * 2));
    innerBorderPanel->layout()->addWidget(vTop2Panel);

    JPanel* vTop3Panel = new JPanel(new FlowLayout());
    vTop3Panel->layout()->addWidget(lhXoverButton);
    vTop3Panel->layout()->addWidget(rhXoverButton);
    vTop3Panel->setMaximumSize(QSize(INT_MAX, vTop3Panel->sizeHint().height()));
    innerBorderPanel->layout()->addWidget(vTop3Panel);

    JPanel* vTop4Panel = new JPanel(new FlowLayout());
    vTop4Panel->layout()->addWidget(layoutSingleSlipButton);
    vTop4Panel->layout()->addWidget(layoutDoubleSlipButton);
    vTop4Panel->setMaximumSize(QSize(INT_MAX, vTop4Panel->sizeHint().height()));
    innerBorderPanel->layout()->addWidget(vTop4Panel);

    JPanel* vTop5Panel = new JPanel(new FlowLayout());
    vTop5Panel->layout()->addWidget(turnoutNamePanel);
    vTop5Panel->setMaximumSize(QSize(INT_MAX, vTop5Panel->sizeHint().height()));
    innerBorderPanel->layout()->addWidget(vTop5Panel);

    JPanel* vTop6Panel = new JPanel(new FlowLayout());
    vTop6Panel->layout()->addWidget(extraTurnoutPanel);
    vTop6Panel->setMaximumSize(QSize(INT_MAX, vTop6Panel->sizeHint().height()));
    innerBorderPanel->layout()->addWidget(vTop6Panel);

    JPanel* vTop7Panel = new JPanel(new FlowLayout());
    vTop7Panel->layout()->addWidget(rotationPanel);
    vTop7Panel->setMaximumSize(QSize(INT_MAX, vTop7Panel->sizeHint().height()));
    innerBorderPanel->layout()->addWidget(vTop7Panel);

    innerBorderPanel->setMaximumSize(QSize(INT_MAX, innerBorderPanel->sizeHint().height()));
    outerBorderPanel->layout()->addWidget(innerBorderPanel);

    trackLabel = new JLabel(tr("-- %1 --").arg(tr("Track")));

    JPanel* vTop8Panel = new JPanel(new FlowLayout());
    vTop8Panel->layout()->addWidget(levelXingButton);
    vTop8Panel->layout()->addWidget(trackButton);
    vTop8Panel->setMaximumSize(QSize(INT_MAX, vTop8Panel->sizeHint().height()));
    outerBorderPanel->layout()->addWidget(vTop8Panel);

    //this would be vTop9Panel
    trackSegmentPropertiesPanel->setMaximumSize(QSize(INT_MAX,
            trackSegmentPropertiesPanel->sizeHint().height()));
    outerBorderPanel->layout()->addWidget(trackSegmentPropertiesPanel);

    JPanel* vTop10Panel = new JPanel(new FlowLayout());
    vTop10Panel->layout()->addWidget(blockLabel);
    vTop10Panel->layout()->addWidget(blockIDComboBox);
    vTop10Panel->layout()->addWidget(highlightBlockCheckBox);
    vTop10Panel->setMaximumSize(QSize(INT_MAX, vTop10Panel->sizeHint().height()));
    outerBorderPanel->layout()->addWidget(vTop10Panel);

    JPanel* vTop11Panel = new JPanel(new FlowLayout());
    vTop11Panel->layout()->addWidget(blockSensorLabel);
    vTop11Panel->layout()->addWidget(blockSensorComboBox);
    vTop11Panel->setMaximumSize(QSize(INT_MAX, vTop11Panel->sizeHint().height()));
    vTop11Panel->setBorder(new EmptyBorder(0, 10, 0, 0));

    outerBorderPanel->layout()->addWidget(vTop11Panel);
    layout()->addWidget(outerBorderPanel);

    JPanel* nodesBorderPanel = new JPanel();
    nodesBorderPanel->setLayout(new QVBoxLayout());//nodesBorderPanel, BoxLayout.PAGE_AXIS));
    TitledBorder* nodesTitleBorder = BorderFactory::createTitledBorder(blacklineBorder, tr("Nodes"));
    nodesTitleBorder->setTitleJustification(TitledBorder::CENTER);
    nodesTitleBorder->setTitlePosition(TitledBorder::BOTTOM);
    nodesBorderPanel->setBorder(nodesTitleBorder);

    JPanel* vTop12Panel = new JPanel(new FlowLayout());
    vTop12Panel->layout()->addWidget(endBumperButton);
    vTop12Panel->layout()->addWidget(anchorButton);
    vTop12Panel->setMaximumSize(QSize(INT_MAX, vTop12Panel->sizeHint().height()));
    nodesBorderPanel->layout()->addWidget(vTop12Panel);

    JPanel* vTop13Panel = new JPanel(new FlowLayout());
    vTop13Panel->layout()->addWidget(edgeButton);
    vTop13Panel->setMaximumSize(QSize(INT_MAX, vTop13Panel->sizeHint().height()));
    nodesBorderPanel->layout()->addWidget(vTop13Panel);

    thisLayout->addWidget(nodesBorderPanel);

    labelsLabel = new JLabel(tr("-- %1 --").arg(tr("Labels")));

    JPanel* labelsBorderPanel = new JPanel();
    labelsBorderPanel->setLayout(new QVBoxLayout());//labelsBorderPanel, BoxLayout.PAGE_AXIS));
    TitledBorder* innerTitleBorder = BorderFactory::createTitledBorder(blacklineBorder,tr("Labels"));
    innerTitleBorder->setTitleJustification(TitledBorder::CENTER);
    innerTitleBorder->setTitlePosition(TitledBorder::BOTTOM);
    labelsBorderPanel->setBorder(innerTitleBorder);

    JPanel* vTop14Panel = new JPanel(new FlowLayout());
    vTop14Panel->layout()->addWidget(textLabelButton);
    vTop14Panel->layout()->addWidget(textLabelTextField);
    vTop14Panel->setMaximumSize(QSize(INT_MAX, vTop14Panel->sizeHint().height()));
    labelsBorderPanel->layout()->addWidget(vTop14Panel);

    JPanel* vTop15Panel = new JPanel(new FlowLayout());
    vTop15Panel->layout()->addWidget(memoryButton);
    vTop15Panel->layout()->addWidget(textMemoryComboBox);
    vTop15Panel->setMaximumSize(QSize(INT_MAX, vTop15Panel->sizeHint().height()));
    labelsBorderPanel->layout()->addWidget(vTop15Panel);

    JPanel* vTop16Panel = new JPanel(new FlowLayout());
    vTop16Panel->layout()->addWidget(blockContentsButton);
    vTop16Panel->layout()->addWidget(blockContentsComboBox);
    vTop16Panel->setMaximumSize(QSize(INT_MAX, vTop16Panel->sizeHint().height()));
    labelsBorderPanel->layout()->addWidget(vTop16Panel);

    thisLayout->addWidget(labelsBorderPanel);

    JPanel* iconsBorderPanel = new JPanel();
    iconsBorderPanel->setLayout(new QVBoxLayout());//iconsBorderPanel, BoxLayout.PAGE_AXIS));
    TitledBorder* iconsTitleBorder = BorderFactory::createTitledBorder(blacklineBorder, tr("IconsTitle"));
    iconsTitleBorder->setTitleJustification(TitledBorder::CENTER);
    iconsTitleBorder->setTitlePosition(TitledBorder::BOTTOM);
    iconsBorderPanel->setBorder(iconsTitleBorder);

    JPanel* vTop18Panel = new JPanel(new FlowLayout());
    vTop18Panel->layout()->addWidget(multiSensorButton);
    vTop18Panel->setMaximumSize(QSize(INT_MAX, vTop18Panel->sizeHint().height()));
    iconsBorderPanel->layout()->addWidget(vTop18Panel);

    JPanel* vTop20Panel = new JPanel(new FlowLayout());
    vTop20Panel->layout()->addWidget(sensorButton);
    vTop20Panel->layout()->addWidget(sensorComboBox);
    vTop20Panel->setMaximumSize(QSize(INT_MAX, vTop20Panel->sizeHint().height()));
    iconsBorderPanel->layout()->addWidget(vTop20Panel);

    JPanel* vTop19Panel = new JPanel(new FlowLayout());
    vTop19Panel->layout()->addWidget(signalMastButton);
    vTop19Panel->layout()->addWidget(signalMastComboBox);
    vTop19Panel->setMaximumSize(QSize(INT_MAX, vTop19Panel->sizeHint().height()));
    iconsBorderPanel->layout()->addWidget(vTop19Panel);

    JPanel* vTop21Panel = new JPanel(new FlowLayout());
    vTop21Panel->layout()->addWidget(signalButton);
    vTop21Panel->layout()->addWidget(signalHeadComboBox);
    vTop21Panel->setMaximumSize(QSize(INT_MAX, vTop21Panel->sizeHint().height()));
    iconsBorderPanel->layout()->addWidget(vTop21Panel);

    JPanel* vTop22Panel = new JPanel(new FlowLayout());
    vTop22Panel->layout()->addWidget(iconLabelButton);
    vTop22Panel->layout()->addWidget(shapeButton);
    vTop22Panel->setMaximumSize(QSize(INT_MAX, vTop22Panel->sizeHint().height()));
    vTop22Panel->layout()->addWidget(changeIconsButton);
    iconsBorderPanel->layout()->addWidget(vTop22Panel);

    thisLayout->addWidget(iconsBorderPanel);
    thisLayout->addWidget(Box::createVerticalGlue());

    JPanel* bottomPanel = new JPanel();
    FlowLayout* bottomPanelLayout = new FlowLayout(bottomPanel);
    zoomPanel->setMaximumSize(QSize(INT_MAX, zoomPanel->sizeHint().height()));
    locationPanel->setMaximumSize(QSize(INT_MAX, locationPanel->sizeHint().height()));
    bottomPanel->layout()->addWidget(zoomPanel);
    bottomPanel->layout()->addWidget(locationPanel);
    bottomPanel->setMaximumSize(QSize(INT_MAX, bottomPanel->sizeHint().height()));
    thisLayout->addWidget(bottomPanel, 0, Qt::AlignBottom);//BorderLayout.SOUTH);
}   //layoutComponents
