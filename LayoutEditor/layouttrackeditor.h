#ifndef LAYOUTTRACKEDITOR_H
#define LAYOUTTRACKEDITOR_H

#include <QObject>
//#include "layouteditor.h"
#include "jrootpane.h"
#include "jpanel.h"
#include "namedbeancombobox.h"
#include "jlabel.h"

class LayoutBlock;
class ActionListener;
class LayoutTrack;
class BlockManager;
class LayoutEditor;
class LayoutTrackEditor : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LayoutTrackEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  static /*public*/ LayoutTrackEditor* makeTrackEditor(/*@Nonnull*/ LayoutTrack* layoutTrack, /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*abstract*/ /*public*/ virtual void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) =0;

 signals:

 public slots:

 private:
  QStringList sensorList = QStringList();
  void showSensorMessage();
  bool hasNxSensorPairs(LayoutBlock* loBlk);
  static Logger* log;

 protected:
  /*final*/ /*protected*/ LayoutEditor* layoutEditor;
  /*protected*/ void addDoneCancelButtons(JPanel* target, JRootPane* rp, ActionListener* doneCallback, ActionListener* cancelCallback);

  friend class LayoutSlipEditor;
  friend class LayoutTurnoutEditor;
  friend class LTE_LayoutTrackEditor;
  friend class LayoutXOverEditor;
  friend class TrackSegmentEditor;
  friend class LevelXingEditor;
  friend class LayoutTurntableEditor;
};

class LTE_LayoutTrackEditor : public LayoutTrackEditor
{
  Q_OBJECT
 public:
  LTE_LayoutTrackEditor(LayoutEditor* editor): LayoutTrackEditor(editor){}
  /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* /*layoutTrack*/) override
  {
   log->error("Not a valid LayoutTrackEditor implementation",  Exception("traceback"));
  }

};
#endif // LAYOUTTRACKEDITOR_H
