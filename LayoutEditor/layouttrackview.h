#ifndef LAYOUTTRACKVIEW_H
#define LAYOUTTRACKVIEW_H

#include <QObject>
#include "layouttrack.h"
#include "layoutturnout.h"

class LayoutTrackView : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LayoutTrackView(/*@Nonnull*/ LayoutTrack* track);
  static /*public*/ LayoutTrackView* makeTrackView(/*@Nonnull*/ LayoutTrack* trk);
  /*public*/ bool hasDecorations();
  /*final*/ /*public*/ QPointF getCoordsCenter();
  /*final*/ /*public*/ QString getId();
  /*final*/ /*public*/ QString getName();
  /*public*/ QMap<QString, QString> *getDecorations();
  /*public*/ bool isMainline();
  /*public*/ bool isHidden();


 signals:

 public slots:

 private:
  static Logger* log;
  /*final*/ /*private*/ LayoutTrack* layoutTrack;

 protected:
  /*protected*/ void drawEditControls(EditScene *g2);
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock);
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement);
  /*protected*/ void drawDecorations(EditScene* g2);

  friend class LayoutEditorComponent;
};

#endif // LAYOUTTRACKVIEW_H
