#include "layouteditorcomponent.h"
#include "loggerfactory.h"
#include "editscene.h"
#include "layouteditor.h"
#include "layouttrackdrawingoptions.h"
#include "positionablepointview.h"
#include "tracksegmentview.h"
#include "layouteditortoolbarpanel.h"
#include "layoutturntable.h"
#include "layoutshape.h"
#include "leblockcontentsicon.h"
#include "layoutturnoutview.h"
#include "layoutturntableview.h"

//LayoutEditorComponent::LayoutEditorComponent(QWidget *parent) : QWidget(parent)
//{

//}
/*
* This is an intermediate component used to put the Layout Editor
* into the component layers hierarchy so that objects can be drawn
* in front of or behind layout editor objects.
*
* @author George Warner Copyright (c) 2017-2018
 */
//class LayoutEditorComponent extends JComponent {


// Antialiasing rendering
//    /*protected*/ static /*final*/ RenderingHints antialiasing = new RenderingHints(
//            RenderingHints.KEY_ANTIALIASING,
//            RenderingHints.VALUE_ANTIALIAS_ON);

/*protected*/ LayoutEditorComponent::LayoutEditorComponent(/*@Nonnull*/ /*final*/ LayoutEditor* LayoutEditor) {
    //super();
    this->layoutEditor = LayoutEditor;
 editPanel = layoutEditor->editPanel;
}
#if 1
/*
* {@inheritDoc}
 */
//@Override
//public void paint(Graphics g) {
/*public*/ void LayoutEditorComponent::paintTargetPanel(EditScene* g2)
{
// if(!initialized)
//  return;
 if (qobject_cast<EditScene*>(g2))
 {
        // layoutEditor.draw((Graphics2D) g);

//            Graphics2D g2 = (Graphics2D) g;

//            if (clipBounds != null) {
//                if (!clipBounds.isEmpty()) {
//                    if ((clipBounds.getWidth() > 0) && (clipBounds.getHeight() > 0)) {
//                        if (!clipBounds.equals(g2.getClipBounds())) {
//                            //log.debug("LEComponent.paint(); clipBounds: {}, oldClipBounds: {}",
//                            //        clipBounds, g2.getClipBounds());
//                            g2.setClip(clipBounds);
//                        }
//                    }
//                }
//            }
        // Optional antialising, to eliminate (reduce) staircase on diagonal lines
//            if (layoutEditor->antialiasingOn) {
//                g2.setRenderingHints(antialiasing);
//            }
  layoutEditor->editPanel->setRenderHint(QPainter::Antialiasing, layoutEditor->antialiasingOn);

        // drawPositionableLabelBorder(g2);
        // things that only get drawn in edit mode
        if (layoutEditor->isEditable()) {
            if (layoutEditor->getDrawGrid()) {
                drawPanelGrid(g2);
            }
            drawLayoutTracksHidden(g2);
        }

        drawShapes(g2, true);
        drawTrackSegmentsDashed(g2);
        drawLayoutTracksBallast(g2);
        drawLayoutTracksTies(g2);
        drawLayoutTracksRails(g2);
        drawLayoutTracksBlockLines(g2);

        drawPositionablePoints(g2, false);
        drawPositionablePoints(g2, true);

        drawShapes(g2, false);

        drawDecorations(g2);

        // things that only get drawn in edit mode
        if (layoutEditor->isEditable()) {
            drawLayoutTrackEditControls(g2);
            drawShapeEditControls(g2);

            drawMemoryRects(g2);
            drawBlockContentsRects(g2);

            if (layoutEditor->allControlling()) {
                drawTurnoutControls(g2);
            }
            drawSelectionRect(g2);
            highLightSelection(g2);

            drawTrackSegmentInProgress(g2);
            drawShapeInProgress(g2);

            if (layoutEditor->isDrawLayoutTracksLabel()) {
                drawLayoutTracksLabel(g2);
            }
        } else if (layoutEditor->getTurnoutCircles()) {
            if (layoutEditor->allControlling()) {
                drawTurnoutControls(g2);
            }
        }
    }
//    else {
//        log.error("LayoutEditor drawing requires Graphics2D");
//    }
}

/*private*/ void LayoutEditorComponent::drawPanelGrid(EditScene* g2) {
 if(layoutEditor->panelGridGroup != nullptr)
 {
  //Q_ASSERT(panelGridGroup->scene()!=0);
  g2->removeItem(layoutEditor->panelGridGroup);
  delete layoutEditor->panelGridGroup;
  //g2->destroyItemGroup(panelGridGroup);
 }
 if(!layoutEditor->isEditable() || !layoutEditor->drawGrid)
  return;
 layoutEditor->panelGridGroup = new QGraphicsItemGroup();
    int wideMod = layoutEditor->gContext->getGridSize() * layoutEditor->gContext->getGridSize2nd();
    int wideMin = layoutEditor->gContext->getGridSize() / 2;

    // granulize puts these on getGridSize() increments
    int minX = 0;
    int minY = 0;
    int maxX = (int) MathUtil::granulize(layoutEditor->gContext->getLayoutWidth(), layoutEditor->gContext->getGridSize());
    int maxY = (int) MathUtil::granulize(layoutEditor->gContext->getLayoutHeight(), layoutEditor->gContext->getGridSize());

    log->debug(tr("drawPanelGrid: minX: %1, minY: %2, maxX: %3, maxY: %4").arg(minX).arg(minY).arg(maxX).arg(maxY));

    QPointF startPt = QPointF();
    QPointF stopPt = QPointF();
//    BasicStroke narrow = new BasicStroke(1.0F, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
//    BasicStroke wide = new BasicStroke(2.0F, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

//    g2.setColor(Color.gray);
//    g2.setStroke(narrow);
    //  BasicStroke narrow = new   BasicStroke(1.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
    //  BasicStroke wide = new BasicStroke(2.0F,BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND);
    //  g2.setColor(QColor::gray);
    //  g2.setStroke(narrow);
    QPen narrow = QPen(QColor(Qt::gray),1,  Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QPen wide = QPen(QColor(Qt::gray),2,  Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

    // draw horizontal lines
    for (int y = minY; y <= maxY; y += layoutEditor->gContext->getGridSize()) {
     startPt= QPointF(minX,y);
     stopPt = QPointF(maxX,y);

     QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
        if ((y % wideMod) < wideMin) {
//            g2->setStroke(wide);
//            g2.draw(new Line2D.Double(startPt, stopPt));
//            g2.setStroke(narrow);
         line->setPen(wide);
        } else {
            //g2.draw(new Line2D.Double(startPt, stopPt));
         line->setPen(narrow);
        }
        layoutEditor->panelGridGroup->addToGroup(line);
    }

    // draw vertical lines
    for (int x = minX; x <= maxX; x += layoutEditor->gContext->getGridSize()) {
     startPt=QPointF(x,minX);
     stopPt= QPointF(x,maxY);

     QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(startPt, stopPt));
        if ((x % wideMod) < wideMin) {
//            g2.setStroke(wide);
//            g2.draw(new Line2D.Double(startPt, stopPt));
//            g2.setStroke(narrow);
         line->setPen(wide);
        } else {
//            g2.draw(new Line2D.Double(startPt, stopPt));
         line->setPen(narrow);
        }
        layoutEditor->panelGridGroup->addToGroup(line);
    }
    g2->addItem(layoutEditor->panelGridGroup);
}

//
//  draw hidden layout tracks
//
/*private*/ void LayoutEditorComponent::drawLayoutTracksHidden(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();
//    Stroke stroke = new BasicStroke(1.F);
 QPen stroke = QPen(ltdo->getSideRailColor(),1.0, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
 QVector<qreal> dashArray = QVector<qreal>() << 6.0 << 4.0;
//            BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//            new float[]{6.F, 4.F}, 0);

 QPen dashedStroke = QPen(ltdo->getMainRailColor(), 1.0, Qt::DashLine,Qt::RoundCap, Qt::RoundJoin);
 dashedStroke.setDashOffset(10.);
 dashedStroke.setDashPattern(dashArray);

 //setup for drawing hidden sideline rails
//    g2.setColor(ltdo->getSideRailColor());
 stroke.setColor(ltdo->getSideRailColor());
//    g2.setStroke(stroke);
 layoutEditor->drawingStroke = stroke;
 bool main = false, block = false, hidden = true, dashed = false;
 draw1(g2, main, block, hidden, dashed/*,LayoutTrack::track*/);
 //g2.setStroke(dashedStroke);
 dashedStroke.setColor(ltdo->getSideRailColor());
 layoutEditor->drawingStroke = dashedStroke;
 draw1(g2, main, block, hidden, dashed = true/*,LayoutTrack::track*/);

 //setup for drawing mainline rails
 main = true;
 //g2.setColor(ltdo->getMainRailColor());
 stroke.setColor(ltdo->getMainRailColor());
 //g2.setStroke(stroke);
 layoutEditor->drawingStroke = stroke;
 draw1(g2, main, block, hidden, dashed = false/*, LayoutTrack::track*/);
 //g2.setStroke(dashedStroke);
 dashedStroke.setColor(ltdo->getMainRailColor());
 layoutEditor->drawingStroke = dashedStroke;
 dashed = true;
 draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
}

//
//  draw dashed track segments
//
/*private*/ void LayoutEditorComponent::drawTrackSegmentsDashed(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();
 bool main = false, block = false, hidden = false, dashed = true;

 if (ltdo->getSideRailCount() > 0)
 {
     //setup for drawing dashed sideline rails
     int railWidth = ltdo->getSideRailWidth();
     //float[] dashArray = new float[]{6.F + railWidth, 4.F + railWidth};
     QVector<qreal> dashArray = QVector<qreal>() << 6.0 + railWidth << 4.0 + railWidth;
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
//        g2.setColor(ltdo->getSideRailColor());
     QPen stroke = QPen(ltdo->getSideRailColor(), railWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
     stroke.setDashPattern(dashArray);
     stroke.setDashOffset(10.0);
     layoutEditor->drawingStroke = stroke;
     if ((ltdo->getSideRailCount() & 1) == 1) {
         draw1(g2, main, block, hidden/*, LayoutTrack::dashed*/);
     }
     if (ltdo->getSideRailCount() >= 2) {
         float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
         draw2(g2, main, railDisplacement/*, LayoutTrack::dashed*/);
     }
 }

 if (ltdo->getMainRailCount() > 0) {
     //setup for drawing dashed mainline rails
     main = true;
     int railWidth = ltdo->getMainRailWidth();
     //float[] dashArray = new float[]{6.F + railWidth, 4.F + railWidth};
     QVector<qreal> dashArray = QVector<qreal>() << 6.0 + railWidth << 4.0 + railWidth;
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
//        g2.setColor(ltdo->getMainRailColor());
     QPen stroke = QPen(ltdo->getMainRailColor(), railWidth,  Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
     stroke.setDashPattern(dashArray);
     stroke.setDashOffset(10.0);
     layoutEditor->drawingStroke = stroke;
     if ((ltdo->getMainRailCount() & 1) == 1) {
         draw1(g2, main, block, hidden, dashed/*, LayoutTrack::dashed*/);
     }
     if (ltdo->getMainRailCount() >= 2) {
         float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
         draw2(g2, main, railDisplacement/*, LayoutTrack::dashed*/);
     }
 }
}   // drawTrackSegmentsDashed

//
// draw layout track ballast
//
/*private*/ void LayoutEditorComponent::drawLayoutTracksBallast(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();
 bool main = false, block = false, hidden = false, dashed = false;

 //setup for drawing sideline ballast
 int ballastWidth = ltdo->getSideBallastWidth();
 if (ballastWidth > 0) {
//        g2.setStroke(new BasicStroke(ballastWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(ltdo->getSideBallastColor());
  QPen stroke = QPen(ltdo->getSideBallastColor(), ballastWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  layoutEditor->drawingStroke = stroke;
     draw1(g2, main, block, hidden, dashed/*, LayoutTrack::ballast*/);
 }

 //setup for drawing mainline ballast
 ballastWidth = ltdo->getMainBallastWidth();
 if (ballastWidth > 0) {
//        g2.setStroke(new BasicStroke(ballastWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(ltdo->getMainBallastColor());
  QPen stroke = QPen(ltdo->getMainBallastColor(), ballastWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  layoutEditor->drawingStroke = stroke;
     main = true;
     draw1(g2, main, block, hidden, dashed/*,LayoutTrack::ballast*/);
 }
}

//
// draw layout track ties
//
/*private*/ void LayoutEditorComponent::drawLayoutTracksTies(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();

 // setup for drawing sideline ties
 int tieLength = ltdo->getSideTieLength();
 int tieWidth = ltdo->getSideTieWidth();
 int tieGap = ltdo->getSideTieGap();
 if ((tieLength > 0) && (tieWidth > 0) && (tieGap > 0)) {
//        g2.setStroke(new BasicStroke(tieLength,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//                new float[]{tieWidth, tieGap}, 0));
//        g2.setColor(ltdo->getSideTieColor());
  QPen stroke = QPen(ltdo->getSideTieColor(), tieLength, Qt::DashLine, Qt::FlatCap, Qt::BevelJoin);
  QVector<qreal> dashPattern = QVector<qreal>() << tieWidth << tieGap;
  stroke.setDashPattern(dashPattern);
  stroke.setDashOffset(10.);
  layoutEditor->drawingStroke = stroke;
  draw1(g2, false, LayoutTrack::ties);  // main = false
 }

 // setup for drawing mainline ties
 tieLength = ltdo->getMainTieLength();
 tieWidth = ltdo->getMainTieWidth();
 tieGap = ltdo->getMainTieGap();
 if ((tieLength > 0) && (tieWidth > 0) && (tieGap > 0)) {
//        g2.setStroke(new BasicStroke(tieLength,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//                new float[]{tieWidth, tieGap}, 0));
//        g2.setColor(ltdo->getMainTieColor());
  QPen stroke = QPen(ltdo->getMainTieColor(), tieLength, Qt::DashLine, Qt::FlatCap, Qt::BevelJoin);
  QVector<qreal> dashPattern = QVector<qreal>() << tieWidth << tieGap;
  stroke.setDashPattern(dashPattern);
  stroke.setDashOffset(10.);
  layoutEditor->drawingStroke = stroke;

     draw1(g2, true, LayoutTrack::ties); // main = true
 }
}

//
// draw layout track rails
//
/*private*/ void LayoutEditorComponent::drawLayoutTracksRails(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();
 int railWidth = ltdo->getSideRailWidth();
 QColor railColor = ltdo->getSideRailColor();

 bool main = false, block = false, hidden = false, dashed = false;

 if (ltdo->getSideRailCount() > 1) {
     //setup for drawing sideline rails
     float railDisplacement = railWidth + (ltdo->getSideRailGap() / 2.F);
//        g2.setStroke(new BasicStroke(railWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
     QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     layoutEditor->drawingStroke = stroke;
     draw2(g2, main, railDisplacement/*, LayoutTrack::track*/);
 }

 if ((ltdo->getSideRailCount() & 1) == 1) {
     //setup for drawing sideline rails
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
  QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  layoutEditor->drawingStroke = stroke;
  draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
 }

 main = true;

 railWidth = ltdo->getMainRailWidth();
 railColor = ltdo->getMainRailColor();
 if (ltdo->getMainRailCount() > 1) {
     //setup for drawing mainline rails
     float railDisplacement = railWidth + (ltdo->getMainRailGap() / 2.F);
//        g2.setStroke(new BasicStroke(railWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
     QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     layoutEditor->drawingStroke = stroke;
     draw2(g2, main, railDisplacement);
 }
 if ((ltdo->getMainRailCount() & 1) == 1) {
     //setup for drawing mainline rails
//        g2.setStroke(new BasicStroke(
//                railWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//        g2.setColor(railColor);
     dashed = false;
     QPen stroke = QPen(railColor, railWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     layoutEditor->drawingStroke = stroke;
     draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
 }

}   // drawLayoutTracksRails

//
// draw layout track block lines
//
/*private*/ void LayoutEditorComponent::drawLayoutTracksBlockLines(EditScene* g2) {
 LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();

 //setup for drawing sideline block lines
 int blockLineWidth = ltdo->getSideBlockLineWidth();
 //float[] dashArray = new float[]{6.F + blockLineWidth, 4.F + blockLineWidth};
 QVector<qreal> dashArray = QVector<qreal>() << 6.0 + blockLineWidth << 4.0 + blockLineWidth;

 //Stroke blockLineStroke = null;
 QPen blockLineStroke;
 QPen stroke;
 int dashPercentageX10 = ltdo->getSideBlockLineDashPercentageX10();
 if (dashPercentageX10 > 0)
 {
  //float[] blockLineDashArray = new float[]{
  QVector<qreal> blockLineDashArray = QVector<qreal>() <<
  dashPercentageX10 + blockLineWidth <<
         10.0 - dashPercentageX10 + blockLineWidth;
//        blockLineStroke = new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, blockLineDashArray, 0);
  //g2.setStroke(blockLineStroke);
     blockLineStroke = QPen(layoutEditor->defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     blockLineStroke.setDashOffset(10.0);
     blockLineStroke.setDashPattern(blockLineDashArray);
     stroke = blockLineStroke;
 } else {
//        blockLineStroke = new BasicStroke(
//                ltdo->getSideBlockLineWidth(),
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
  blockLineStroke = QPen(layoutEditor->defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

//        g2.setStroke(new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
  stroke = QPen(layoutEditor->defaultTrackColor, ltdo->getSideBlockLineWidth(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  stroke.setDashPattern(dashArray);
  stroke.setDashOffset(10.0);
  layoutEditor->drawingStroke = stroke;
 }

 //note: color is set in layout track's draw1 when isBlock is true
 bool main = false, block = true, hidden = false, dashed = true;
 draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
 //g2.setStroke(blockLineStroke);
 layoutEditor->drawingStroke = blockLineStroke;
 draw1(g2, main, block, hidden, dashed = false/*,LayoutTrack::track*/);

 //setup for drawing mainline block lines
 blockLineWidth = ltdo->getMainBlockLineWidth();
 //dashArray = new float[]{6.F + blockLineWidth, 4.F + blockLineWidth};
 dashArray = QVector<qreal>() << 6.0 + blockLineWidth << 4.0 + blockLineWidth;
 dashPercentageX10 = ltdo->getMainBlockLineDashPercentageX10();
 if (dashPercentageX10 > 0) {
//        float[] blockLineDashArray = new float[]{
//            dashPercentageX10 + blockLineWidth,
//            10 - dashPercentageX10 + blockLineWidth};
  QVector<qreal> blockLineDashArray = QVector<qreal>() << dashPercentageX10 + blockLineWidth << 10 - dashPercentageX10 + blockLineWidth;
//        blockLineStroke = new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, blockLineDashArray, 0);
  blockLineStroke = QPen(layoutEditor->defaultTrackColor, blockLineWidth, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  blockLineStroke.setDashPattern(blockLineDashArray);
  blockLineStroke.setDashOffset(10.0);
//        g2.setStroke(blockLineStroke);
  layoutEditor->drawingStroke = blockLineStroke;
 } else {
//        blockLineStroke = new BasicStroke(
//                ltdo->getMainBlockLineWidth(),
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
  blockLineStroke=QPen(layoutEditor->defaultTrackColor, blockLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        g2.setStroke(new BasicStroke(
//                blockLineWidth,
//                BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
//                10.F, dashArray, 0));
  layoutEditor->drawingStroke = QPen(layoutEditor->defaultTrackColor, ltdo->getMainBlockLineWidth(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  layoutEditor->drawingStroke.setDashOffset(10.0);
 }
 //note: color is set in layout track's draw1 when isBlock is true
 draw1(g2, main = true, block, hidden, dashed = true/*,LayoutTrack::track*/);
 //g2.setStroke(blockLineStroke);
 layoutEditor->drawingStroke = blockLineStroke;
 dashed = false;
 draw1(g2, main, block, hidden, dashed/*, LayoutTrack::track*/);
}


// isDashed defaults to false
/*private*/ void LayoutEditorComponent::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden) {
    draw1(g2, isMain, isBlock, isHidden, false);
}

// isHidden defaults to false
/*private*/ void LayoutEditorComponent::draw1(EditScene* g2,
        bool isMain,
        bool isBlock) {
    draw1(g2, isMain, isBlock, false);
}

// isBlock defaults to false
/*private*/ void LayoutEditorComponent::draw1(EditScene* g2, bool isMain) {
    draw1(g2, isMain, false);
}

// draw single line (ballast, ties & block lines)
/*private*/ void LayoutEditorComponent::draw1(EditScene* g2,
        bool isMain,
        bool isBlock,
        bool isHidden,
        bool isDashed) {
 for (LayoutTrackView* layoutTrackView : layoutEditor->getLayoutTrackViews()) {
     if (!(qobject_cast<PositionablePointView*>(layoutTrackView))) {
         if (isHidden == layoutTrackView->isHidden()) {
             if ((qobject_cast<TrackSegmentView*>(layoutTrackView))) {
                 if (((TrackSegmentView*) layoutTrackView)->isDashed() == isDashed) {
                     layoutTrackView->draw1(g2, isMain, isBlock);
                 }
             } else if (!isDashed) {
                 layoutTrackView->draw1(g2, isMain, isBlock);
             }
         }
     }
 }
}

// draw positionable points
/*private*/ void LayoutEditorComponent::drawPositionablePoints(EditScene* g2, bool isMain) {
    for (PositionablePointView* positionablePointView : layoutEditor->getPositionablePointViews()) {
        positionablePointView->draw1(g2, isMain, false);
    }
}

// isDashed defaults to false
/*private*/ void LayoutEditorComponent::draw2(EditScene* g2, bool isMain, float railDisplacement) {
    draw2(g2, isMain, railDisplacement, false);
}

// draw parallel lines (rails)
/*private*/ void LayoutEditorComponent::draw2(EditScene* g2, bool isMain,
        float railDisplacement, bool isDashed) {
    for (LayoutTrackView* layoutTrackView : layoutEditor->getLayoutTrackViews()) {
        if ((qobject_cast<TrackSegmentView*>(layoutTrackView))) {
            if (((TrackSegmentView*) layoutTrackView)->isDashed() == isDashed) {
                layoutTrackView->draw2(g2, isMain, railDisplacement);
            }
        } else if (!isDashed) {
            layoutTrackView->draw2(g2, isMain, railDisplacement);
        }
    }
}

// draw decorations
/*private*/ void LayoutEditorComponent::drawDecorations(EditScene* g2) {
    //layoutEditor->getLayoutTrackViews().forEach((tr) -> tr.drawDecorations(g2));
 for (LayoutTrackView* tr : layoutEditor->getLayoutTrackViews()) {
     tr->drawDecorations(g2);
 }
}

// draw shapes
/*private*/ void LayoutEditorComponent::drawShapes(EditScene* g2, bool isBackground) {
 //layoutEditor.getLayoutShapes().forEach((s) ->
foreach(LayoutShape* s, layoutEditor->getLayoutShapes())
{
  if (isBackground == (s->getLevel() < 3)) {
      s->draw(g2);
  }
 }//);
}

// draw track segment (in progress)
/*private*/ void LayoutEditorComponent::drawTrackSegmentInProgress(EditScene* g2) {
 //check for segment in progress
 if (layoutEditor->isEditable() && (layoutEditor->beginTrack != nullptr) && layoutEditor->leToolBarPanel->trackButton->isChecked()) {
//        g2.setColor(defaultTrackColor);
//        g2.setStroke(new BasicStroke(sidelineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
  QPen stroke = QPen(layoutEditor->defaultTrackColor, 1, Qt::SolidLine,Qt::FlatCap, Qt::RoundJoin);
     //g2.draw(new Line2D.Double(beginLocation, currentLocation));
  QGraphicsLineItem* item = new QGraphicsLineItem(layoutEditor->beginLocation.x(), layoutEditor->beginLocation.y(), layoutEditor->currentLocation.x(), layoutEditor->currentLocation.y());
  item->setPen(stroke);

     // highlight unconnected endpoints of all tracks
     QColor highlightColor = ColorUtil::setAlpha(QColor(Qt::red), 0.25);
     QColor connectColor = ColorUtil::setAlpha(QColor(Qt::green), 0.5);
//        g2.setColor(highlightColor);
//        g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
     stroke = QPen(highlightColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

     for (LayoutTrack* lt : layoutEditor->getLayoutTracks()) {
         if (lt != layoutEditor->beginTrack) {
           LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
             if (lt == layoutEditor->foundTrack) {
                 ltv->highlightUnconnected(g2);
//                    g2.setColor(connectColor);
                 layoutEditor->drawingStroke.setColor(connectColor);
                 ltv->highlightUnconnected(g2, layoutEditor->foundHitPointType);
//                    g2.setColor(highlightColor);
                 layoutEditor->drawingStroke.setColor(highlightColor);
             } else {
                 ltv->highlightUnconnected(g2);
             }
         }
     }
 }
}

// draw shape (in progress)
/*private*/ void LayoutEditorComponent::drawShapeInProgress(EditScene* g2) {
 //check for segment in progress
 if (layoutEditor->getLayoutEditorToolBarPanel()->shapeButton->isChecked())
 {
  //log.warn("drawShapeInProgress: selectedObject: " + selectedObject);
  if ((/*layoutEditor.*/layoutEditor->selectedObject != nullptr)) {
//      g2.setColor(Color.DARK_GRAY);
//      g2.setStroke(new BasicStroke(3.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
//      g2.draw(new Line2D.Double(layoutEditor.beginLocation, layoutEditor.currentLocation));
   QPen stroke = QPen(QColor(Qt::darkGray), 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
   layoutEditor->drawingStroke = stroke;
   QGraphicsLineItem* item = new QGraphicsLineItem(layoutEditor->beginLocation.x(), layoutEditor->beginLocation.y(), layoutEditor->currentLocation.x(), layoutEditor->currentLocation.y());
   item->setPen(stroke);

   g2->addItem(item);
  }
 }
}

// draw layout track edit controls
/*private*/ void LayoutEditorComponent::drawLayoutTrackEditControls(EditScene* g2) {
 //g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(layoutEditor->defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 layoutEditor->drawingStroke = stroke;
  for (LayoutTrackView* tr : layoutEditor->getLayoutTrackViews()) {
     tr->drawEditControls(g2);
 }
}

/*private*/ void LayoutEditorComponent::drawShapeEditControls(EditScene* g2) {
 //g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 QPen stroke = QPen(layoutEditor->turnoutCircleColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
 layoutEditor->drawingStroke = stroke;

 //layoutEditor.getLayoutShapes().forEach((s) ->
 foreach(LayoutShape* s, layoutEditor->getLayoutShapes())
 {
   s->drawEditControls(g2);
 }//);
}

// draw layout turnout controls
/*private*/ void LayoutEditorComponent::drawTurnoutControls(EditScene* g2) {
 //    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
 //    g2.setColor(turnoutCircleColor);
  QPen stroke = QPen(layoutEditor->turnoutCircleColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
  //g2.setBackground(layoutEditor.turnoutCircleThrownColor);
  g2->setBackgroundBrush(QBrush(layoutEditor->turnoutCircleThrownColor));

  layoutEditor->drawingStroke = stroke;
     // loop over all turnouts
     bool editable = layoutEditor->isEditable();
     for (LayoutTrackView* tr : layoutEditor->getLayoutTrackViews()) {
         if (qobject_cast<LayoutTurnoutView*>(tr)) {  //<== this includes LayoutSlips
             LayoutTurnoutView* lt = (LayoutTurnoutView*) tr;
             if (editable || !(lt->isHidden() || lt->isDisabled())) {
                 lt->drawTurnoutControls(g2);
             }
         } else if (qobject_cast<LayoutTurntable*>(tr)) {
             LayoutTurntableView* lt = (LayoutTurntableView*) tr;
             if (editable || !lt->isHidden()) {
                 lt->drawTurnoutControls(g2);
             }
         }
     }
 }

/*private*/ void LayoutEditorComponent::drawSelectionRect(EditScene* g2) {
    if (layoutEditor->selectionActive && (layoutEditor->selectionWidth != 0.0) && (layoutEditor->selectionHeight != 0.0)) {
     // The Editor super class draws a dashed red selection rectangle...
     // We're going to also draw a non-dashed yellow selection rectangle...
     // This could be code stripped if the super-class implementation is "good enough"
//        Stroke stroke = g2.getStroke();
//        Color color = g2.getColor();

//        g2.setColor(new Color(204, 207, 88));
//        g2.setStroke(new BasicStroke(3.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
  QPen stroke = QPen(QColor(204, 207, 88), 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);


     //g2.draw(getSelectionRect());    // this sets _selectRect also
  QGraphicsRectItem* r = new QGraphicsRectItem(layoutEditor->getSelectionRect());
  r->setPen(stroke);
  g2->addItem(r);

//        g2.setColor(color);
//        g2.setStroke(stroke);
 } else {
     layoutEditor->_selectRect = QRectF(); // and clear it to turn it off
 }
}

/*private*/ void LayoutEditorComponent::drawMemoryRects(EditScene* g2) {
 //    g2.setColor(defaultTrackColor);
 //    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
  QPen stroke = QPen(layoutEditor->defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

     for (LEMemoryIcon* l : *layoutEditor->memoryLabelList) {
         //g2.draw(new Rectangle2D.Double(l.getX(), l.getY(), l.getSize().width, l.getSize().height));
      QGraphicsRectItem* r = new QGraphicsRectItem(QRectF(l->x(), l->y(), l->getSize().width(), l->getSize().height()));
      r->setPen(stroke);
      r->setPos(((Positionable*)l)->getLocation());
      g2->addItem(r);
     }
 }

/*private*/ void LayoutEditorComponent::drawBlockContentsRects(EditScene* g2) {
 //    g2.setColor(defaultTrackColor);
 //    g2.setStroke(new BasicStroke(1.0F, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
  QPen stroke = QPen(layoutEditor->defaultTrackColor, 1, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

     for (LEBlockContentsIcon* l : *layoutEditor->blockContentsLabelList) {
         //g2.draw(new Rectangle2D.Double(l.getX(), l.getY(), l.getSize().width, l.getSize().height));
      QGraphicsRectItem* r = new QGraphicsRectItem(QRectF(l->x(), l->y(), l->getSize().width(), l->getSize().height()));
      r->setPen(stroke);
      r->setPos(((Positionable*)l)->getLocation());
      g2->addItem(r);
     }
 }

/*private*/ void LayoutEditorComponent::highLightSelection(EditScene* g) { // TODO: must be updated
 //java.awt.Stroke stroke = g.getStroke();
 //  Color color = g.getColor();
 //  g.setColor(new Color(204, 207, 88));
 //  g.setStroke(new java.awt.BasicStroke(2.0f));
 QColor color = QColor(204,207,88);
 QPen pen(color,2.0);
 if(layoutEditor->highlightRect != nullptr && layoutEditor->highlightRect->scene() != 0)
 {
  g->removeItem(layoutEditor->highlightRect);
 }
 layoutEditor->highlightRect = new QGraphicsItemGroup();

#if 0
 if (layoutEditor->_positionableSelection!=nullptr)
 {
  for (int i = 0; i<layoutEditor->_positionableSelection->size(); i++)
  {
   Positionable* c = layoutEditor->_positionableSelection->at(i);
   //g.drawRect(c.getX(), c.getY(), c.maxWidth(), c.maxHeight());
   QGraphicsRectItem* item;
   SensorIcon* si;
   LocoIcon* li;
   LEMemoryIcon* mi;
   if((si = static_cast<SensorIcon*>(c->self()))!=nullptr)
    item = new QGraphicsRectItem(QRectF(si->getX(), si->getY(), si->maxWidth(), si->maxHeight()));
   else if((li = static_cast<LocoIcon*>(c))!=nullptr)
    item = new QGraphicsRectItem(QRectF(li->getX(), li->getY(), li->maxWidth(), li->maxHeight()));
   else if((mi = static_cast<LEMemoryIcon*>(c))!=nullptr)
    item = new QGraphicsRectItem(QRectF(mi->getX(), mi->getY(), mi->maxWidth(), mi->maxHeight()));

   item->setPen(pen);
   layoutEditor->highlightRect->addToGroup(item);
  }
 }
 // loop over all defined turnouts

 if (layoutEditor->_turnoutSelection!=nullptr)
 {
  for (int i = 0; i<layoutEditor->_turnoutSelection->size();i++)
  {
   LayoutTurnout* t = layoutEditor->_turnoutSelection->at(i);
   LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(t);
   int minx = (int) qMin(qMin(ltv->getCoordsA().x(), ltv->getCoordsB().x()),qMin(ltv->getCoordsC().x(), ltv->getCoordsD().x()));
   int miny = (int) qMin(qMin(t->getCoordsA().y(), t->getCoordsB().y()),qMin(t->getCoordsC().y(), t->getCoordsD().y()));
   int maxx = (int) qMax(qMax(t->getCoordsA().x(), t->getCoordsB().x()),qMax(t->getCoordsC().x(), t->getCoordsD().x()));
   int maxy = (int) qMax(qMax(t->getCoordsA().y(), t->getCoordsB().y()),qMax(t->getCoordsC().y(), t->getCoordsD().y()));
   int width = maxx-minx;
   int height = maxy-miny;
   int x = (int) ltv->getCoordsCenter().x()-(width/2);
   int y = (int) ltv->getCoordsCenter().y()-(height/2);
   //g.drawRect(x, y, width, height);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
   item->setPen(pen);
   layoutEditor->highlightRect->addToGroup(item);
  }
 }

 if (layoutEditor->_xingSelection!=nullptr)
 {
  // loop over all defined level crossings
  for (int i = 0; i<layoutEditor->_xingSelection->size();i++)
  {
   LevelXing* xing = layoutEditor->_xingSelection->at(i);
   int minx = (int) qMin(qMin(xing->getCoordsA().x(), xing->getCoordsB().x()),qMin(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int miny = (int) qMin(qMin(xing->getCoordsA().y(), xing->getCoordsB().y()),qMin(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int maxx = (int) qMax(qMax(xing->getCoordsA().x(), xing->getCoordsB().x()),qMax(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int maxy = (int) qMax(qMax(xing->getCoordsA().y(), xing->getCoordsB().y()),qMax(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int width = maxx-minx;
   int height = maxy-miny;
   int x = (int) xing->getCoordsCenter().x()-(width/2);
   int y = (int) xing->getCoordsCenter().y()-(height/2);
   //g.drawRect(x, y, width, height);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
   item->setPen(pen);
   layoutEditor->highlightRect->addToGroup(item);
  }
 }
 if (layoutEditor->_slipSelection!=nullptr)
 {
 // loop over all defined level crossings
  for (int i = 0; i<layoutEditor->_slipSelection->size();i++)
 {
   LayoutSlip* xing = layoutEditor->_slipSelection->at(i);
   int minx = (int) qMin(qMin(xing->getCoordsA().x(), xing->getCoordsB().x()),qMin(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int miny = (int) qMin(qMin(xing->getCoordsA().y(), xing->getCoordsB().y()),qMin(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int maxx = (int) qMax(qMax(xing->getCoordsA().x(), xing->getCoordsB().x()),qMax(xing->getCoordsC().x(), xing->getCoordsD().x()));
   int maxy = (int) qMax(qMax(xing->getCoordsA().y(), xing->getCoordsB().y()),qMax(xing->getCoordsC().y(), xing->getCoordsD().y()));
   int width = maxx-minx;
   int height = maxy-miny;
   int x = (int) xing->getCoordsCenter().x()-(width/2);
   int y = (int) xing->getCoordsCenter().y()-(height/2);
   //g->drawRect(x, y, width, height);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width, height));
   item->setPen(pen);
   layoutEditor->highlightRect->addToGroup(item);
  }
 }
 // loop over all defined turntables
 if (layoutEditor->_turntableSelection!=nullptr)
 {
  for (int i = 0; i<layoutEditor->_turntableSelection->size();i++)
  {
      LayoutTurntable* tt = layoutEditor->_turntableSelection->at(i);
      QPointF center = tt->getCoordsCenter();
      int x = (int) center.x() - (int)tt->getRadius();
      int y = (int) center.y() - (int)tt->getRadius();
      //g.drawRect(x, y, ((int)tt->getRadius()*2), ((int)tt->getRadius()*2));
         QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(x, y, width(), height()));
         item->setPen(pen);
         layoutEditor->highlightRect->addToGroup(item);
  }
 }
 // loop over all defined Anchor Points and End Bumpers
 if (layoutEditor->_pointSelection!=nullptr)
 {
  for (int i = 0; i<layoutEditor->_pointSelection->size();i++)
  {
   PositionablePoint* p = layoutEditor->_pointSelection->at(i);
   PositionablePointView* pv = layoutEditor->getPositionablePointView(p);
   QPointF coord = pv->getCoordsCenter();
   //g.drawRect((int)coord.getX()-4, (int)coord.getY()-4, 9, 9);
   QGraphicsRectItem* item = new QGraphicsRectItem(QRectF((int)coord.x()-4, (int)coord.y()-4, 9, 9));
   item->setPen(pen);
   layoutEditor->highlightRect->addToGroup(item);
  }
 }
#else
 //layoutEditor.getPositionalSelection().forEach((c) -> g.drawRect(c.getX(), c.getY(), c.maxWidth(), c.maxHeight()));
 for(Positionable* c : *layoutEditor->getPositionalSelection())
 {
  //g.drawRect(c->getX(), c->getY(), c->maxWidth(), c->maxHeight());
  QGraphicsRectItem* item;
  SensorIcon* si;
  LocoIcon* li;
  LEMemoryIcon* mi;
  if((si = static_cast<SensorIcon*>(c->self()))!=nullptr)
   item = new QGraphicsRectItem(QRectF(si->getX(), si->getY(), si->maxWidth(), si->maxHeight()));
  else if((li = static_cast<LocoIcon*>(c))!=nullptr)
   item = new QGraphicsRectItem(QRectF(li->getX(), li->getY(), li->maxWidth(), li->maxHeight()));
  else if((mi = static_cast<LEMemoryIcon*>(c))!=nullptr)
   item = new QGraphicsRectItem(QRectF(mi->getX(), mi->getY(), mi->maxWidth(), mi->maxHeight()));

  item->setPen(pen);
  layoutEditor->highlightRect->addToGroup(item);
 }
#if 0 //TODO
         //layoutEditor._layoutTrackSelection.stream().map((lt) -> {
 for(LayoutTrack* lt : layoutEditor->_layoutTrackSelection)
 {
     LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
     QRectF r = ltv->getBounds();
     if (r.isEmpty()) {
         r = MathUtil::inset(r, -4.0);
     }
     //r = MathUtil.centerRectangleOnPoint(r, ltv.getCoordsCenter());
     return r;
 }//).forEachOrdered(g::draw);

         layoutEditor._layoutShapeSelection.stream().map((ls) -> {
             Rectangle2D r = ls.getBounds();
             if (r.isEmpty()) {
                 r = MathUtil.inset(r, -4.0);
             }
             //r = MathUtil.centerRectangleOnPoint(r, ls.getCoordsCenter());
             return r;
         }).forEachOrdered(g::draw);
#endif
#endif
//  g.setColor(color);
//  g.setStroke(stroke);
 if(layoutEditor->highlightRect && layoutEditor->highlightRect->scene())
  log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
 g->addItem(layoutEditor->highlightRect);
}

/*private*/ void LayoutEditorComponent::drawLayoutTracksLabel(EditScene* g) {
//    g.setFont(new Font(Font.MONOSPACED, Font.BOLD, 12));

//    g.setColor(Color.red);
 //QPen pen(Qt::red);

 for (LayoutTrackView* layoutTrackView : layoutEditor->getLayoutTrackViews()) {
     layoutTrackView->drawLayoutTrackText(g);
 }
}
/*
* {@inheritDoc}
 */
//@Override
/*public*/ QRect LayoutEditorComponent::getBounds() {
    EditScene* targetPanel = layoutEditor->getTargetPanel();
    QRectF targetBounds = targetPanel->itemsBoundingRect();
//    Container parent = getParent();
//    if (parent != null) {   // if there is a parent...
//        Rectangle2D parentBounds = parent.getBounds();

//        // convert our origin to parent coordinates
//        Point2D origin = new Point2D.Double(
//                targetBounds.getX() - parentBounds.getX(),
//                targetBounds.getY() - parentBounds.getY());

//        return new Rectangle((int) origin.getX(), (int) origin.getY(),
//                (int) targetBounds.getWidth(), (int) targetBounds.getHeight());
//    } else {
        return MathUtil::rectangle2DToRectangle(targetBounds);
//    }
}

/*
* {@inheritDoc}
 */
//@Override
/*public*/ QRect LayoutEditorComponent::getBounds(QRect rv) {
    //rv.setBounds(getBounds());

    return rv;
}

/*
* {@inheritDoc}
 */
//@Override
/*public*/ int LayoutEditorComponent::getX() {
    QRectF bounds = getBounds();
    return (int) bounds.x();
}

/*
* {@inheritDoc}
 */
//@Override
/*public*/ int LayoutEditorComponent::getY() {
    QRectF bounds = getBounds();
    return (int) bounds.y();
}

/*
* {@inheritDoc}
 */
//@Override
/*public*/ int LayoutEditorComponent::getWidth() {
    QRectF bounds = getBounds();
    return (int) bounds.width();
}

/*
* {@inheritDoc}
 */
//@Override
/*public*/ int LayoutEditorComponent::getHeight() {
    QRectF bounds = getBounds();
    return (int) bounds.height();
}


/*public*/ void LayoutEditorComponent::setClip(QRectF clipBounds) {
    this->clipBounds = clipBounds;
}
#endif
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LayoutEditorComponent::log = LoggerFactory::getLogger("LayoutEditorComponent");
