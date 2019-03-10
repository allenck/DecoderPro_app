#ifndef LAYOUTTRACKEDITORS_H
#define LAYOUTTRACKEDITORS_H

#include <QObject>

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


protected:
 /*protected*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack);
 /*protected*/ void editTrackSegment(/*@Nonnull*/ TrackSegment* trackSegment);

friend class LayoutEditorChecks;
};

#endif // LAYOUTTRACKEDITORS_H
