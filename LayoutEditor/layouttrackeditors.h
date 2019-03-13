#ifndef LAYOUTTRACKEDITORS_H
#define LAYOUTTRACKEDITORS_H

#include <QObject>
#include "popupmenulistener.h"
#include "windowlistener.h"
#include "layoutturnout.h"

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
 /*private*/ JmriBeanComboBox* editTrackSegmentBlockNameComboBox;// = new JmriBeanComboBox(
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
 /*private*/ JmriBeanComboBox* editLayoutTurnout1stTurnoutComboBox = nullptr;
 /*private*/ JmriBeanComboBox* editLayoutTurnout2ndTurnoutComboBox = nullptr;
 /*private*/ QLabel* editLayoutTurnout2ndTurnoutLabel = nullptr;
 /*private*/ JmriBeanComboBox* editLayoutTurnoutBlockNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ JmriBeanComboBox* editLayoutTurnoutBlockBNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ JmriBeanComboBox* editLayoutTurnoutBlockCNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager.getDefault("BlockManager"), nullptr, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
 /*private*/ JmriBeanComboBox* editLayoutTurnoutBlockDNameComboBox;// = new JmriBeanComboBox(
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
 /*private*/ JmriBeanComboBox* editLayoutSlipTurnoutAComboBox;
 /*private*/ JmriBeanComboBox* editLayoutSlipTurnoutBComboBox;
 /*private*/ QCheckBox* editLayoutSlipHiddenBox;// = new QCheckBox(tr("HideSlip"));
 /*private*/ JmriBeanComboBox* editLayoutSlipBlockNameComboBox;// = new JmriBeanComboBox(
//         InstanceManager::getDefault("BlockManager")), nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);

 /*private*/ bool editLayoutSlipOpen = false;
 /*private*/ bool editLayoutSlipNeedsRedraw = false;
 /*private*/ bool editLayoutSlipNeedsBlockUpdate = false;
 /*private*/ void drawSlipState(EditScene* g2, int state);
 QMenu* popup;
 /*private*/ TestState* testPanel;
 /*private*/ int testState = LayoutTurnout::UNKNOWN;
 LayoutTurntable* layoutTurntable;

 bool hasNxSensorPairs(LayoutBlock* loBlk);
 void showSensorMessage();


private slots:
 /*private*/ void editLayoutSlipEditBlockPressed(/*ActionEvent a*/);
 /*private*/ void editLayoutSlipDonePressed(/*ActionEvent a*/);
 /*private*/ void editLayoutSlipCancelPressed(/*ActionEvent a*/);

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
};

class SlipPopupMenuListener : public PopupMenuListener
{
 Q_OBJECT
 LayoutTrackEditors* layoutTrackEditors;
public:
 SlipPopupMenuListener(QMenu *popup, LayoutTrackEditors* layoutTrackEditors);
public slots:
 /*public*/ void popupMenuWillBecomeVisible(/*PopupMenuEvent e*/);

 /*public*/ void popupMenuWillBecomeInvisible(/*PopupMenuEvent e*/);

 /*public*/ void popupMenuCanceled(/*PopupMenuEvent e*/);
private:
 QMenu* popup;
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
#endif // LAYOUTTRACKEDITORS_H
