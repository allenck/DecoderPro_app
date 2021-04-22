#ifndef LAYOUTEDITORTOOLBARPANEL_H
#define LAYOUTEDITORTOOLBARPANEL_H
#include "jpanel.h"

class Logger;
class LayoutEditor;
class MultiIconEditor;
class JLabel;
class QRadioButton;
class FlowLayout;
class NamedBeanComboBox;
class JComboBox;
class QCheckBox;
class JTextField;
class JFrame;
class QPushButton;
class MultiSensorIconFrame;
class QButtonGroup;
class JPanel;
class LayoutEditorToolBarPanel : public JPanel
{
 Q_OBJECT

public:
 LayoutEditorToolBarPanel(LayoutEditor* layoutEditor, QWidget *parent = nullptr);

private:
 static Logger* log;
private slots:
 void on_selectionListAction();
 void on_highlightBlockCheckBox();
 void on_blockIdComboBox();
 void on_changeIconsButton();

protected:
 /*protected*/ LayoutEditor* layoutEditor = nullptr;

 //top row of radio buttons
 /*protected*/ /*transient*/ JLabel* turnoutLabel;// = new JLabel();
 /*protected*/ /*transient*/ QRadioButton* turnoutRHButton;// = new QRadioButton(Bundle.getMessage("RightHandAbbreviation"));
 /*protected*/ /*transient*/ QRadioButton* turnoutLHButton;// = new QRadioButton(Bundle.getMessage("LeftHandAbbreviation"));
 /*protected*/ /*transient*/ QRadioButton* turnoutWYEButton;// = new QRadioButton(Bundle.getMessage("WYEAbbreviation"));
 /*protected*/ /*transient*/ QRadioButton* doubleXoverButton;// = new QRadioButton(Bundle.getMessage("DoubleCrossoverAbbreviation"));
 /*protected*/ /*transient*/ QRadioButton* rhXoverButton;// = new QRadioButton(Bundle.getMessage("RightCrossover")); //key is also used by Control Panel
 //Editor, placed in DisplayBundle
 /*protected*/ /*transient*/ QRadioButton* lhXoverButton;// = new QRadioButton(Bundle.getMessage("LeftCrossover")); //idem
 /*protected*/ /*transient*/ QRadioButton* layoutSingleSlipButton;// = new QRadioButton(Bundle.getMessage("LayoutSingleSlip"));
 /*protected*/ /*transient*/ QRadioButton* layoutDoubleSlipButton;// = new QRadioButton(Bundle.getMessage("LayoutDoubleSlip"));

 //Default flow layout definitions for JPanels
 /*protected*/ /*transient*/ FlowLayout* leftRowLayout;// = new FlowLayout(FlowLayout.LEFT, 5, 0);       //5 pixel gap between items, no vertical gap
 /*protected*/ /*transient*/ FlowLayout* centerRowLayout;// = new FlowLayout(FlowLayout.CENTER, 5, 0);   //5 pixel gap between items, no vertical gap
 /*protected*/ /*transient*/ FlowLayout* rightRowLayout;// = new FlowLayout(FlowLayout.RIGHT, 5, 0);     //5 pixel gap between items, no vertical gap

 //top row of check boxes
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Turnout>*/* turnoutNameComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.turnoutManagerInstance(), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 /*protected*/ /*transient*/ JLabel* turnoutNameLabel;// = new JLabel(Bundle.getMessage("MakeLabel", Bundle.getMessage("Name")));
 /*protected*/ /*transient*/ JPanel* turnoutNamePanel;// = new JPanel(leftRowLayout);
 /*protected*/ /*transient*/ JPanel* extraTurnoutPanel;// = new JPanel(leftRowLayout);
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Turnout>*/* extraTurnoutNameComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.turnoutManagerInstance(), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);
 /*protected*/ /*transient*/ JComboBox* rotationComboBox = nullptr;
 /*protected*/ /*transient*/ JPanel* rotationPanel;// = new JPanel(leftRowLayout);

 //2nd row of radio buttons
 /*protected*/ /*transient*/ JLabel* trackLabel;// = new JLabel();
 /*protected*/ /*transient*/ QRadioButton* levelXingButton;// = new QRadioButton(Bundle.getMessage("LevelCrossing"));
 /*protected*/ /*transient*/ QRadioButton* trackButton;// = new QRadioButton(Bundle.getMessage("TrackSegment"));

 //2nd row of check boxes
 /*protected*/ /*transient*/ JPanel* trackSegmentPropertiesPanel;// = new JPanel(leftRowLayout);
 /*protected*/ /*transient*/ QCheckBox* mainlineTrack;// = new JCheckBox(Bundle.getMessage("MainlineBox"));
 /*protected*/ /*transient*/ QCheckBox* dashedLine;// = new JCheckBox(Bundle.getMessage("Dashed"));

 /*protected*/ /*transient*/ JLabel* blockLabel;// = new JLabel(Bundle.getMessage("MakeLabel", Bundle.getMessage("BlockID")));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Block>*/* blockIDComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(BlockManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);
 /*protected*/ /*transient*/ QCheckBox* highlightBlockCheckBox;// = new JCheckBox(Bundle.getMessage("HighlightSelectedBlockTitle"));

 /*protected*/ /*transient*/ JLabel* blockSensorLabel;// = new JLabel(Bundle.getMessage("MakeLabel", Bundle.getMessage("BlockSensorName")));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* blockSensorComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(SensorManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 //3rd row of radio buttons (and any associated text fields)
 /*protected*/ /*transient*/ QRadioButton* endBumperButton;// = new QRadioButton(Bundle.getMessage("EndBumper"));
 /*protected*/ /*transient*/ QRadioButton* anchorButton;// = new QRadioButton(Bundle.getMessage("Anchor"));
 /*protected*/ /*transient*/ QRadioButton* edgeButton;// = new QRadioButton(Bundle.getMessage("EdgeConnector"));

 /*protected*/ /*transient*/ JLabel* labelsLabel;// = new JLabel();
 /*protected*/ /*transient*/ QRadioButton* textLabelButton;// = new QRadioButton(Bundle.getMessage("TextLabel"));
 /*protected*/ /*transient*/ JTextField* textLabelTextField;// = new JTextField(12);

 /*protected*/ /*transient*/ QRadioButton* memoryButton;// = new QRadioButton(Bundle.getMessage("BeanNameMemory"));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Memory>*/* textMemoryComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(MemoryManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 /*protected*/ /*transient*/ QRadioButton* blockContentsButton;// = new QRadioButton(Bundle.getMessage("BlockContentsLabel"));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Block>*/* blockContentsComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(BlockManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 //4th row of radio buttons (and any associated text fields)
 /*protected*/ /*transient*/ QRadioButton* multiSensorButton;// = new QRadioButton(Bundle.getMessage("MultiSensor") + "...");

 /*protected*/ /*transient*/ QRadioButton* signalMastButton;// = new QRadioButton(Bundle.getMessage("SignalMastIcon"));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<SignalMast>*/* signalMastComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(SignalMastManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 /*protected*/ /*transient*/ QRadioButton* sensorButton;// = new QRadioButton(Bundle.getMessage("SensorIcon"));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sensorComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(SensorManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 /*protected*/ /*transient*/ QRadioButton* signalButton;// = new QRadioButton(Bundle.getMessage("SignalIcon"));
 /*protected*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* signalHeadComboBox;// = new NamedBeanComboBox<>(
//         InstanceManager.getDefault(SignalHeadManager.class), nullptr, NamedBean.DisplayOptions.DISPLAYNAME);

 /*protected*/ /*transient*/ QRadioButton* iconLabelButton;// = new QRadioButton(Bundle.getMessage("IconLabel"));
 /*protected*/ /*transient*/ QRadioButton* shapeButton;// = new QRadioButton(Bundle.getMessage("LayoutShape"));

 /*protected*/ /*transient*/ QPushButton* changeIconsButton;// = new JButton(Bundle.getMessage("ChangeIcons") + "...");

 /*protected*/ /*transient*/ MultiIconEditor* sensorIconEditor = nullptr;
 /*protected*/ /*transient*/ JFrame* sensorFrame = nullptr;
 /*protected*/ /*transient*/ MultiIconEditor* signalIconEditor = nullptr;
 /*protected*/ /*transient*/ JFrame* signalFrame = nullptr;

 /*protected*/ /*transient*/ MultiIconEditor* iconEditor = nullptr;
 /*protected*/ /*transient*/ JFrame* iconFrame = nullptr;

 /*protected*/ /*transient*/ MultiSensorIconFrame* multiSensorFrame = nullptr;

 /*protected*/ /*transient*/ JLabel* xLabel;// = new JLabel("00");
 /*protected*/ /*transient*/ JLabel* yLabel;// = new JLabel("00");

 /*protected*/ /*transient*/ JPanel* zoomPanel;// = new JPanel();
 /*protected*/ /*transient*/ JLabel* zoomLabel;// = new JLabel("x1");

 /*protected*/ /*transient*/ JPanel* locationPanel;// = new JPanel();

 /*protected*/ /*transient*/ JPanel* blockPropertiesPanel = nullptr;

 //non-GUI variables
 /*protected*/ /*transient*/ bool toolBarIsWide = true;
 /*protected*/ /*transient*/ QButtonGroup* itemGroup = nullptr;
 /*protected*/ virtual void layoutComponents() =0;
 /*protected*/ virtual void setupComponents();

 friend class LayoutEditorToolsTest;
 friend class LayoutEditor;
 friend class LayoutTurnoutView;
 friend class LevelXing;
 friend class LayoutSlip;
 friend class LayoutEditorComponent;
 friend class PositionablePointView;
 friend class LayoutSlipView;
};

#endif // LAYOUTEDITORTOOLBARPANEL_H
