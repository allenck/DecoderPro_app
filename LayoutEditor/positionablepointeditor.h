#ifndef POSITIONABLEPOINTEDITOR_H
#define POSITIONABLEPOINTEDITOR_H
#include "layouttrackeditor.h"

class PositionablePointEditor : public LayoutTrackEditor
{
  Q_OBJECT
 public:
  /*public*/ PositionablePointEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) override;

 private:
  static Logger* log;
};

#endif // POSITIONABLEPOINTEDITOR_H
