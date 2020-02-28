#ifndef LAYOUTTRACKEDITORS_H
#define LAYOUTTRACKEDITORS_H

#include <QObject>
#include "popupmenulistener.h"
#include "windowlistener.h"
#include "layoutturnout.h"
#include <QWidget>
#include "decimalformat.h"

class NamedBeanComboBox;
class TestState;
class LayoutBlock;
class LevelXing;
class LayoutTurntable;
class QMenu;
class EditScene;
class LayoutSlip;
class QLabel;
class LayoutTurnout;
class JmriBeanComboBox;
class JTextField;
class QPushButton;
class QCheckBox;
class JmriJFrame;
class QComboBox;
class TrackSegment;
class Logger;
class LayoutEditor;
class LayoutTrack;
class LayoutTrackEditors : public QObject
{
 Q_OBJECT
public:
 /*public*/ LayoutTrackEditors(/*@Nonnull*/ LayoutEditor* layoutEditor, QObject *parent = nullptr);

signals:

public slots:
 /*public*/ void toggleStateTest();

private:
 static Logger* log;
 /*private*/ LayoutEditor* layoutEditor = nullptr;
 QList<QString> sensorList;// = new ArrayList<>();
 // variables for Edit Track Segment pane
 /*private*/ TrackSegment* trackSegment = nullptr;
 /*private*/ JmriJFrame* editTrackSegmentFrame = nullptr;
 /*private*/ QComboBox* editTrackSegmentMainlineComboBox;// = new JComboBox<String>();
 /*private*/ QComboBox* editTrackSegmentDashedComboBox;// = new JComboBox<String>();
 /*private*/ QCheckBox* editTrackSegmentHiddenCheckBox;// = new JCheckBox(tr("HideTrack"));  // NOI18N
 /*private*/ NamedBeanComboBox* editTrackSegmentBlockNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault(BlockManager.class), null, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ JTextField* editTrackSegmentArcTextField;// = new JTextField(5);
 /*private*/ QPushButton* editTrackSegmentSegmentEditBlockButton;
 /*private*/ QPushButton* editTrackSegmentSegmentEditDoneButton;
 /*private*/ QPushButton* editTrackSegmentSegmentEditCancelButton;

 /*private*/ int editTrackSegmentMainlineTrackIndex;
 /*private*/ int editTrackSegmentSideTrackIndex;
 /*private*/ int editTrackSegmentDashedIndex;
 /*private*/ int editTrackSegmentSolidIndex;
 /*private*/ bool editTrackSegmentOpen = false;
 /*private*/ bool editTrackSegmentNeedsRedraw = false;

 /*private*/ bool editLayoutTurnoutOpen = false;
 /*private*/ bool editLayoutTurnoutNeedRedraw = false;
 /*private*/ bool editLayoutTurnoutNeedsBlockUpdate = false;
 /*private*/ int editLayoutTurnoutClosedIndex;
 /*private*/ int editLayoutTurnoutThrownIndex;

 // variables for Edit Layout Turnout pane
 /*private*/ LayoutTurnout* layoutTurnout = nullptr;

 /*private*/ JmriJFrame* editLayoutTurnoutFrame = nullptr;
 /*private*/ NamedBeanComboBox* editLayoutTurnout1stTurnoutComboBox = nullptr;
 /*private*/ NamedBeanComboBox* editLayoutTurnout2ndTurnoutComboBox = nullptr;
 /*private*/ QLabel* editLayoutTurnout2ndTurnoutLabel = nullptr;
 /*private*/ NamedBeanComboBox* editLayoutTurnoutBlockNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ NamedBeanComboBox* editLayoutTurnoutBlockBNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ NamedBeanComboBox* editLayoutTurnoutBlockCNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ NamedBeanComboBox* editLayoutTurnoutBlockDNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ QComboBox* editLayoutTurnoutStateComboBox;// = new JComboBox<String>();
 /*private*/ QCheckBox* editLayoutTurnoutHiddenCheckBox;// = new JCheckBox(tr("HideTurnout"));  // NOI18N
 /*private*/ QPushButton* editLayoutTurnoutBlockButton;
 /*private*/ QPushButton* editLayoutTurnoutDoneButton;
 /*private*/ QPushButton* editLayoutTurnoutCancelButton;
 /*private*/ QPushButton* editLayoutTurnoutBlockBButton;
 /*private*/ QPushButton* editLayoutTurnoutBlockCButton;
 /*private*/ QPushButton* editLayoutTurnoutBlockDButton;
 /*private*/ QCheckBox* editLayoutTurnout2ndTurnoutCheckBox;//= new JCheckBox(tr("SupportingTurnout"));  // NOI18N
 /*private*/ QCheckBox* editLayoutTurnout2ndTurnoutInvertCheckBox;// = new JCheckBox(tr("SecondTurnoutInvert"));  // NOI18N

 // variables for Edit slip Crossing pane
 /*private*/ LayoutSlip* layoutSlip = nullptr;

 /*private*/ JmriJFrame* editLayoutSlipFrame = nullptr;
 /*private*/ QPushButton* editLayoutSlipDoneButton;
 /*private*/ QPushButton* editLayoutSlipCancelButton;
 /*private*/ QPushButton* editLayoutSlipBlockButton;
 /*private*/ NamedBeanComboBox* editLayoutSlipTurnoutAComboBox;
 /*private*/ NamedBeanComboBox* editLayoutSlipTurnoutBComboBox;
 /*private*/ QCheckBox* editLayoutSlipHiddenBox;// = new QCheckBox(tr("HideSlip"));
 /*private*/ NamedBeanComboBox* editLayoutSlipBlockNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager::getDefault("BlockManager")), nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);

 /*private*/ bool editLayoutSlipOpen = false;
 /*private*/ bool editLayoutSlipNeedsRedraw = false;
 /*private*/ bool editLayoutSlipNeedsBlockUpdate = false;
 /*private*/ void drawSlipState(QPainter* g2, int state);
 QMenu* popup;
 /*private*/ TestState* testPanel;
 /*private*/ int testState = LayoutTurnout::UNKNOWN;

 // variables for Edit Track Segment pane
 /*private*/ LevelXing* levelXing;

 // variables for Edit Level Crossing pane
 /*private*/ JmriJFrame* editLevelXingFrame =  nullptr;
 /*private*/ QCheckBox* editLevelXingHiddenCheckBox ;//= new JCheckBox(tr("HideCrossing"));  // NOI18N

 /*private*/ NamedBeanComboBox* editLevelXingBlock1NameComboBox;// = new JmriBeanComboBox(
//     InstanceManager::getDefault(BlockManager.class),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 /*private*/ NamedBeanComboBox* editLevelXingBlock2NameComboBox;// = new JmriBeanComboBox(
//     InstanceManager::getDefault(BlockManager.class),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 /*private*/ QPushButton* editLevelXingDoneButton;
 /*private*/ QPushButton* editLevelXingCancelButton;
 /*private*/ QPushButton* editLevelXingBlock1Button;
 /*private*/ QPushButton* editLevelXingBlock2Button;

 /*private*/ bool editLevelXingOpen = false;
 /*private*/ bool editLevelXingNeedsRedraw = false;
 /*private*/ bool editLevelXingNeedsBlockUpdate = false;

 // variables for Edit Turntable pane
 /*private*/ LayoutTurntable* layoutTurntable =  nullptr;

 /*private*/ JmriJFrame* editLayoutTurntableFrame =  nullptr;
 /*private*/ JTextField* editLayoutTurntableRadiusTextField;// = new JTextField(8);
 /*private*/ JTextField* editLayoutTurntableAngleTextField;// = new JTextField(8);
 /*private*/ QPushButton* editLayoutTurntableDoneButton;
 /*private*/ QPushButton* editLayoutTurntableCancelButton;

 /*private*/ QWidget* editLayoutTurntableRayPanel;
 /*private*/ QPushButton* editLayoutTurntableAddRayTrackButton;
 ///*private*/ QPushButton* editLayoutTurntableDeleteRayTrackButton;
 /*private*/ QCheckBox* editLayoutTurntableDccControlledCheckBox;

 /*private*/ QString editLayoutTurntableOldRadius = "";
 /*private*/ bool editLayoutTurntableOpen = false;
 /*private*/ bool editLayoutTurntableNeedsRedraw = false;
 /*private*/ void updateRayPanel();
 /*private*/ void saveRayPanelDetail();



 bool hasNxSensorPairs(LayoutBlock* loBlk);
 void showSensorMessage();


private slots:
 /*private*/ void editLayoutSlipEditBlockPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutSlipDonePressed(/*ActionEvent a*/);
 /*private*/ void editLayoutSlipCancelPressed(/*ActionEvent a*/);
 /*private*/ void editTrackSegmentEditBlockPressed(/*ActionEvent a*/);
 /*private*/ void editTracksegmentDonePressed(/*ActionEvent a*/);
 /*private*/ void editTrackSegmentCancelPressed(/*ActionEvent a*/);
 /*private*/ void onEditLayoutTurnout2ndTurnoutCheckBox(bool);
 /*private*/ void onEditLayoutTurnout2ndTurnoutInvertCheckBox(bool);
 /*private*/ void editLayoutTurnoutCancelPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurnoutEditBlockPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurnoutEditBlockBPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurnoutEditBlockCPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurnoutEditBlockDPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurnoutDonePressed(/*ActionEvent a*/);
 /*private*/ void editLevelXingBlockACPressed(/*ActionEvent a*/);
 /*private*/ void editLevelXingBlockBDPressed(/*ActionEvent a*/);
 /*private*/ void editLevelXingDonePressed(/*ActionEvent a*/);
 /*private*/ void editLevelXingCancelPressed(/*ActionEvent a*/);
 /*private*/ void addRayTrackPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutTurntableDonePressed(/*ActionEvent a*/);
 /*private*/ void turntableEditCancelPressed(/*ActionEvent a*/);
 void onEditLayoutTurntableAddRayTrackButton();
 void onEditLayoutTurntableDccControlledCheckBox();


protected:
 /*protected*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack);
 /*protected*/ void editTrackSegment(/*@Nonnull*/ TrackSegment* trackSegment);
 /*protected*/ void editLayoutTurnout(/*@Nonnull*/ LayoutTurnout* layoutTurnout);
 /*protected*/ void editLayoutSlip(LayoutSlip* layoutSlip);
 /*protected*/ void editLevelXing(LevelXing* levelXing);
 /*protected*/ void editLayoutTurntable(LayoutTurntable* layoutTurntable);

friend class LayoutEditorChecks;
friend class TrackSegment;
friend class SlipEditWindowListener;
friend class SlipEditWindowListener;
friend class SlipPopupMenuListener;
friend class EditTrackSegmentWindowListener;
friend class EditLayoutWindowListener;
friend class TurnoutPopupMenuListener;
friend class LayoutSlip;
friend class TestState;
friend class SampleStates;
friend class LevelXingEditWindowListener;
friend class TurntableEditWindowListener;
friend class TurntableRayPanel;
};

class SlipPopupMenuListener : public PopupMenuListener
{
 Q_OBJECT
 LayoutTrackEditors* lte;
public:
 SlipPopupMenuListener( LayoutTrackEditors* lte);
public slots:
 /*public*/ void popupMenuWillBecomeVisible(PopupMenuEvent *e);

 /*public*/ void popupMenuWillBecomeInvisible(PopupMenuEvent*);

 /*public*/ void popupMenuCanceled(PopupMenuEvent*);
private:
};
class SlipEditWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 SlipEditWindowListener(LayoutTrackEditors* layoutTrackEditors) {this->layoutTrackEditors = layoutTrackEditors;}
 void windowClosing(QCloseEvent *)
 {
  layoutTrackEditors->editLayoutSlipCancelPressed();
 }
};

class EditTrackSegmentWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 EditTrackSegmentWindowListener(LayoutTrackEditors* layoutTrackEditors) {this->layoutTrackEditors = layoutTrackEditors;}
 void windowClosing(QCloseEvent *)
 {
  layoutTrackEditors->editTrackSegmentCancelPressed();
 }

};
class EditLayoutWindowListener : public  WindowListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 EditLayoutWindowListener(LayoutTrackEditors* layoutTrackEditors) {this->layoutTrackEditors = layoutTrackEditors;}
 void windowClosing(QCloseEvent *)
 {
  layoutTrackEditors->editLayoutTurnoutCancelPressed();
 }

};

class TurnoutPopupMenuListener : public PopupMenuListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 TurnoutPopupMenuListener(LayoutTrackEditors* layoutTrackEditors);

public slots:
 /*public*/ void popupMenuWillBecomeVisible(/*PopupMenuEvent e*/);

 /*public*/ void popupMenuWillBecomeInvisible(/*PopupMenuEvent e*/);

 /*public*/ void popupMenuCanceled(/*PopupMenuEvent e*/);

};
class TestState : public QWidget {
 Q_OBJECT
 LayoutTrackEditors* lte;
 public:
 TestState(LayoutTrackEditors* lte){this->lte = lte;}
 //@Override
#if 0
 /*public*/ void paintComponent(Graphics g) {
     super.paintComponent(g);
     if (g instanceof Graphics2D) {
         drawSlipState((Graphics2D) g, testState);
     }
 }
#endif
 /*public*/ void paintEvent(QPaintEvent *event)
 {
  QPainter* painter = new QPainter(this);
  lte->drawSlipState(painter, lte->testState);
 }

};

class SampleStates :  public QWidget {
 Q_OBJECT
LayoutTrackEditors* lte;
int state;
public:
// Methods, constructors, fields.
SampleStates(int state, LayoutTrackEditors* lte) {
    //super();
    this->state = state;
 this->lte = lte;
}

//@Override
/*public*/ void paintEvent(QPaintEvent *event)
{
//    super.paintComponent(g);    // paints background
//    if (g instanceof Graphics2D) {
//        drawSlipState((Graphics2D) g, state);
//    }
    QPainter* painter = new QPainter(this);
    lte->drawSlipState(painter, state);

 }
};

class LevelXingEditWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 LevelXingEditWindowListener(LayoutTrackEditors* layoutTrackEditors) {this->layoutTrackEditors = layoutTrackEditors;}
 void windowClosing(QCloseEvent *)
 {
  layoutTrackEditors->editLevelXingCancelPressed();
 }
};
class TurntableEditWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 TurntableEditWindowListener(LayoutTrackEditors* layoutTrackEditors) {this->layoutTrackEditors = layoutTrackEditors;}
 void windowClosing(QCloseEvent *)
 {
  layoutTrackEditors->turntableEditCancelPressed();
 }
};

class RayTrack;
class QGroupBox;
/*public*/ class TurntableRayPanel  : public QWidget
{
 Q_OBJECT
 // variables for Edit Turntable ray pane
 /*private*/ RayTrack* rayTrack =  nullptr;
 /*private*/ QWidget* rayTurnoutPanel;
 /*private*/ /*transient*/ NamedBeanComboBox* turnoutNameComboBox;
 /*private*/ QGroupBox* rayTitledBorder;
 /*private*/ QComboBox* rayTurnoutStateComboBox;
 /*private*/ QLabel* rayTurnoutStateLabel;
 /*private*/ JTextField* rayAngleTextField;
 /*private*/ /*final*/ QVector<int> rayTurnoutStateValues;// = new int[]{Turnout.CLOSED, Turnout.THROWN};
 /*private*/ /*final*/ DecimalFormat* twoDForm;// = new DecimalFormat("#.00");
 LayoutTrackEditors* layoutTrackEditors;
 /**
  * constructor method
  */
 /*public*/ TurntableRayPanel(/*@Non nullptr*/ RayTrack* rayTrack, LayoutTrackEditors* layoutTrackEditors);
private:
 /*private*/ void _delete();
 /*private*/ void updateDetails();
 /*private*/ void showTurnoutDetails();

private slots:
 void rayAngleTextFieldEditingFinished();
 void onDelete();
friend class LayoutTrackEditors;
};   // class TurntableRayPanel
#endif // LAYOUTTRACKEDITORS_H
