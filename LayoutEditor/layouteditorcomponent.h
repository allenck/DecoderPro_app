#ifndef LAYOUTEDITORCOMPONENT_H
#define LAYOUTEDITORCOMPONENT_H
#include <QWidget>
#include "jcomponent.h"

class QGraphicsItemGroup;
class EditScene;
class QGraphicsView;
class LayoutEditor;
class Logger;
class LayoutEditorComponent : public QWidget/*, public JComponent*/
{
  Q_OBJECT
  //Q_INTERFACES(JComponent)
 public:
  //explicit LayoutEditorComponent(QWidget *parent = nullptr);
  /*public*/ void paintTargetPanel(EditScene* g2);
  /*public*/ QRect getBounds();
  /*public*/ QRect getBounds(QRect rv);
  /*public*/ int getX();
  /*public*/ int getY();
  /*public*/ int getWidth();
  /*public*/ int getHeight();
  /*public*/ void setClip(QRectF clipBounds);
  //QObject* jself() {return (QObject*)this;}
 signals:

 public slots:

 public:
  static Logger* log;
  /*private*/ /*final*/ LayoutEditor* layoutEditor;

  /*private*/ QRectF clipBounds = QRectF();
  QGraphicsView* editPanel;
  /*private*/ void drawPanelGrid(EditScene* g2);
  /*private*/ void drawLayoutTracksHidden(EditScene* g2);
  /*private*/ void drawTrackSegmentsDashed(EditScene* g2);
  /*private*/ void drawLayoutTracksBallast(EditScene* g2);
  /*private*/ void drawLayoutTracksTies(EditScene* g2);
  /*private*/ void drawLayoutTracksRails(EditScene* g2);
  /*private*/ void drawLayoutTracksBlockLines(EditScene* g2);
  /*private*/ void draw1(EditScene* g2,
          bool isMain,
          bool isBlock,
          bool isHidden);
  /*private*/ void draw1(EditScene* g2,
          bool isMain,
          bool isBlock);
  /*private*/ void draw1(EditScene* g2, bool isMain);
  /*private*/ void draw1(EditScene* g2,
          bool isMain,
          bool isBlock,
          bool isHidden,
          bool isDashed);
  /*private*/ void drawPositionablePoints(EditScene* g2, bool isMain);
  /*private*/ void draw2(EditScene* g2, bool isMain, float railDisplacement);
  /*private*/ void draw2(EditScene* g2, bool isMain,
          float railDisplacement, bool isDashed);
  /*private*/ void drawDecorations(EditScene* g2);
  /*private*/ void drawShapes(EditScene* g2, bool isBackground);
  /*private*/ void drawTrackSegmentInProgress(EditScene* g2);
  /*private*/ void drawShapeInProgress(EditScene* g2);
  /*private*/ void drawLayoutTrackEditControls(EditScene* g2);
  /*private*/ void drawShapeEditControls(EditScene* g2);
  /*private*/ void drawTurnoutControls(EditScene* g2);
  /*private*/ void drawSelectionRect(EditScene* g2);
  /*private*/ void drawMemoryRects(EditScene* g2);
  /*private*/ void drawBlockContentsRects(EditScene* g2);
  /*private*/ void highLightSelection(EditScene* g2);

 protected:
//  /*protected*/ static /*final*/ RenderingHints antialiasing = new RenderingHints(            RenderingHints.KEY_ANTIALIASING,
//                                                                                              RenderingHints.VALUE_ANTIALIAS_ON);

  /*protected*/ LayoutEditorComponent(/*@Nonnull*/ /*final*/ LayoutEditor* LayoutEditor);
 friend class LayoutEditor;
};

#endif // LAYOUTEDITORCOMPONENT_H
