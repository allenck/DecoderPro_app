#include "layoutshape.h"
#include "loggerfactory.h"
#include "mathutil.h"
#include "layouteditor.h"
#include "layouttrack.h"
#include "quickpromptutil.h"
#include <QGraphicsItemGroup>

/**
 * A LayoutShape is a set of LayoutShapePoint used to draw a shape. Each point
 * can ether be a point on the shape or a control point that defines a curve
 * that's part of the shape. The shape can be open (end points not connected) or
 * closed (end points connected)
 *
 * @author George Warner Copyright (c) 2017-2018
 */
///*public*/ class LayoutShape {

/*public*/ /*static*/ /*final*/ int LayoutShape::MAX_LINEWIDTH = 200;


/**
 * constructor method (used by XML loading code)
 *
 * @param name         the name of the shape
 * @param layoutEditor reference to the LayoutEditor this shape is in
 */
/*public*/ LayoutShape::LayoutShape(QString name, LayoutEditor* layoutEditor, QObject* parent) : QObject(parent){
    this->name = name;
    this->layoutEditor = layoutEditor;
    this->layoutShapeType = new LayoutShapeType(LayoutShapeType::eOpen);
    this->shapePoints = QList<LayoutShapePoint*>();
}

/**
 * constructor method (used by XML loading code)
 *
 * @param name         the name of the shape
 * @param layoutEditor reference to the LayoutEditor this shape is in
 */
/*public*/ LayoutShape::LayoutShape(QString name, LayoutShapeType* t, LayoutEditor* layoutEditor, QObject *parent) : QObject(parent){
 lineColor = QColor(Qt::black);
 fillColor = QColor(Qt::darkGray);

    //this(name, layoutEditor);
 this->name = name;
 this->layoutEditor = layoutEditor;
 this->layoutShapeType = t;
}

/**
 * constructor method (used by LayoutEditor)
 *
 * @param name         the name of the shape
 * @param c            the QPointF for the initial point
 * @param layoutEditor reference to the LayoutEditor this shape is in
 */
/*public*/ LayoutShape::LayoutShape(QString name, QPointF c, LayoutEditor* layoutEditor, QObject* parent) : QObject(parent){
 lineColor = QColor(Qt::black);
 fillColor = QColor(Qt::darkGray);

    //this(name, layoutEditor);
 this->name = name;
 this->layoutEditor = layoutEditor;
 this->shapePoints.append(new LayoutShapePoint(c));
}

/**
 * constructor method (used by duplicate)
 *
 * @param layoutShape to duplicate (deep copy)
 */
/*public*/ LayoutShape::LayoutShape(LayoutShape* layoutShape, QObject* parent) : QObject(parent){
 lineColor = QColor(Qt::black);
 fillColor = QColor(Qt::darkGray);

    //this(layoutShape.getName(), layoutShape.getLayoutEditor());
 this->name = layoutShape->getName();
 this->layoutEditor = layoutShape->getLayoutEditor();
    this->setType(layoutShape->getType());
    this->setLevel(layoutShape->getLevel());
    this->setLineColor(layoutShape->getLineColor());
    this->setFillColor(layoutShape->getFillColor());

    for (LayoutShapePoint* lsp : layoutShape->getPoints()) {
        this->shapePoints.append(new LayoutShapePoint(lsp->getType(), lsp->getPoint()));
    }
}

// this should only be used for debugging...
//@Override
/*public*/ QString LayoutShape::toString() {
    return tr("LayoutShape %1").arg(name);
}

/*public*/ QString LayoutShape::getDisplayName() {
    return tr("%1 %2").arg(tr("LayoutShape")).arg(name);
}

/**
 * accessor methods
 *
 * @return the name of this shape
 */
/*public*/ QString LayoutShape::getName() {
    return name;
}

/*public*/ void LayoutShape::setName(QString n) {
    name = n;
}

/*public*/ LayoutShapeType* LayoutShape::getType() {
    return layoutShapeType;
}

/*public*/ void LayoutShape::setType(LayoutShapeType* t)
{
 if (layoutShapeType != t)
 {
  switch (t->getType()) {
      case LayoutShapeType::eOpen:
      case LayoutShapeType::eClosed:
      case LayoutShapeType::eFilled:
          layoutShapeType = t;
          break;
      default:    // You shouldn't ever have any invalid LayoutShapeTypes
          log->error("Invalid Shape Type " + t->getName()); //I18IN
  }
 }
}

/*public*/ int LayoutShape::getLineWidth() {
    return lineWidth;
}

/*public*/ void LayoutShape::setLineWidth(int w) {
    lineWidth = qMax(0, w);
}

/*public*/ QColor LayoutShape::getLineColor() {
    return lineColor;
}

/*public*/ void LayoutShape::setLineColor(QColor color) {
    lineColor = color;
}

/*public*/ QColor LayoutShape::getFillColor() {
    return fillColor;
}

/*public*/ void LayoutShape::setFillColor(QColor color) {
    fillColor = color;
}

/*public*/ int LayoutShape::getLevel() {
    return level;
}

/*public*/ void LayoutShape::setLevel(int l) {
    if (level != l) {
        level = l;
        layoutEditor->sortLayoutShapesByLevel();
    }
}

/*public*/ LayoutEditor* LayoutShape::getLayoutEditor() {
    return layoutEditor;
}

/**
 * add point
 *
 * @param p the point to add
 */
/*public*/ void LayoutShape::addPoint(QPointF p) {
    if (shapePoints.size() < getMaxNumberPoints()) {
        shapePoints.append(new LayoutShapePoint(p));
    }
}

/**
 * add point
 *
 * @param p         the point to add
 * @param nearIndex the index of the existing point to add it near note:
 *                  "near" is defined as before or after depending on
 *                  closest neighbor
 */
/*public*/ void LayoutShape::addPoint(QPointF p, int nearIndex) {
    int cnt = shapePoints.size();
    if (cnt < getMaxNumberPoints()) {
        // this point
        LayoutShapePoint* lsp = shapePoints.at(nearIndex);
        QPointF sp = lsp->getPoint();

        // left point
        int idxL = (nearIndex + cnt - 1) % cnt;
        LayoutShapePoint* lspL = shapePoints.at(idxL);
        QPointF pL = lspL->getPoint();
        double distL = MathUtil::distance(p, pL);

        // right point
        int idxR = (nearIndex + 1) % cnt;
        LayoutShapePoint* lspR = shapePoints.at(idxR);
        QPointF pR = lspR->getPoint();
        double distR = MathUtil::distance(p, pR);

        // if nearIndex is the 1st point in open shape...
        if ((getType()->getType() == LayoutShapeType::eOpen) && (nearIndex == 0)) {
            distR = MathUtil::distance(pR, p);
            distL = MathUtil::distance(pR, sp);
        }
        int beforeIndex = (distR < distL) ? idxR : nearIndex;

        // if nearIndex is the last point in open shape...
        if ((getType()->getType() == LayoutShapeType::eOpen) && (idxR == 0)) {
            distR = MathUtil::distance(pL, p);
            distL = MathUtil::distance(pL, sp);
            beforeIndex = (distR < distL) ? nearIndex : nearIndex + 1;
        }

        if (beforeIndex >= cnt) {
            shapePoints.append(new LayoutShapePoint(p));
        } else {
            shapePoints.insert(beforeIndex, new LayoutShapePoint(p));
        }
    }
}

/**
 * add point
 *
 * @param t the type of point to add
 * @param p the point to add
 */
/*public*/ void LayoutShape::addPoint(LayoutShapePointType* t, QPointF p) {
    if (shapePoints.size() < getMaxNumberPoints()) {
        shapePoints.append(new LayoutShapePoint(t, p));
    }
}

/**
 * set point
 *
 * @param idx the index of the point to add
 * @param p   the point to add
 */
/*public*/ void LayoutShape::setPoint(int idx, QPointF p) {
    if (idx < shapePoints.size()) {
        shapePoints.at(idx)->setPoint(p);
    }
}

/**
 * get point
 *
 * @param idx the index of the point to add
 */
/*public*/ QPointF LayoutShape::getPoint(int idx) {
    QPointF result = MathUtil::zeroPoint2D;
    if (idx < shapePoints.size()) {
        result = shapePoints.at(idx)->getPoint();
    }
    return result;
}

// should only be used by xml save code
/*public*/ QList<LayoutShapePoint*> LayoutShape::getPoints() {
    return shapePoints;
}

/**
 * get the number of points
 *
 * @return the number of points
 */
/*public*/ int LayoutShape::getNumberPoints() {
    return shapePoints.size();
}

/**
 * get the maximum number of points
 *
 * @return the maximum number of points
 */
/*public*/ int LayoutShape::getMaxNumberPoints() {
    return LayoutTrack::SHAPE_POINT_OFFSET_MAX - LayoutTrack::SHAPE_POINT_OFFSET_MIN + 1;
}

/**
 * getBounds() - return the bounds of this shape
 *
 * @return Rectangle2D as bound of this shape
 */
/*public*/ QRectF LayoutShape::getBounds() {
    QRectF result = MathUtil::rectangleAtPoint(shapePoints.at(0)->getPoint(), 1.0, 1.0);

    //shapePoints.forEach((lsp) ->
    foreach(LayoutShapePoint* lsp, shapePoints)
    {
       // result.add(lsp->getPoint());

    }//);
    return result;
}

/**
 * find the hit (location) type for a point
 *
 * @param hitPoint      the point
 * @param useRectangles whether to use (larger) rectangles or (smaller)
 *                      circles for hit testing
 * @return the hit point type for the point (or NONE)
 */
/*protected*/ int LayoutShape::findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles) {
    int result = LayoutTrack::NONE;  // assume point not on shape

    if (useRectangles) {
        // rather than create rectangles for all the points below and
        // see if the passed in point is in one of those rectangles
        // we can create a rectangle for the passed in point and then
        // test if any of the points below are in that rectangle instead.
        QRectF r = layoutEditor->layoutEditorControlRectAt(hitPoint);

        if (r.contains(getCoordsCenter())) {
            result = LayoutTrack::SHAPE_CENTER;
        }
        for (int idx = 0; idx < shapePoints.size(); idx++) {
            if (r.contains(shapePoints.at(idx)->getPoint())) {
                result = LayoutTrack::SHAPE_POINT_OFFSET_MIN + idx;
                break;
            }
        }
    } else {
        double distance, minDistance = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
        for (int idx = 0; idx < shapePoints.size(); idx++) {
            distance = MathUtil::distance(shapePoints.at(idx)->getPoint(), hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                result = LayoutTrack::SHAPE_POINT_OFFSET_MIN + idx;
            }
        }
    }
    return result;
}   // findHitPointType

/*public*/ /*static*/ bool LayoutShape::isShapeHitPointType(int t) {
    return ((t == LayoutTrack::SHAPE_CENTER)
            || isShapePointOffsetHitPointType(t));
}

/*public*/ /*static*/ bool LayoutShape::isShapePointOffsetHitPointType(int t) {
    return ((t >= LayoutTrack::SHAPE_POINT_OFFSET_MIN)
            && (t <= LayoutTrack::SHAPE_POINT_OFFSET_MAX));
}

/**
 * get coordinates of center point of shape
 *
 * @return QPointF coordinates of center point of shape
 */
/*public*/ QPointF LayoutShape::getCoordsCenter() {
    QPointF sumPoint = MathUtil::zeroPoint2D;
    for (LayoutShapePoint* lsp : shapePoints) {
        sumPoint = MathUtil::add(sumPoint, lsp->getPoint());
    }
    return MathUtil::divide(sumPoint, shapePoints.size());
}

/*
 * Modify coordinates methods
 */
/**
 * set center coordinates
 *
 * @param p the coordinates to set
 */
//    @Override
/*public*/ void LayoutShape::setCoordsCenter(/*@Nonnull*/ QPointF p) {
    QPointF factor = MathUtil::subtract(p, getCoordsCenter());
    if (!MathUtil::isEqualToZeroPoint2D(factor))
    {
        //shapePoints.forEach((lsp) ->
     foreach(LayoutShapePoint* lsp, shapePoints)
     {
         lsp->setPoint(MathUtil::add(factor, lsp->getPoint()));
     }//);
    }
}

/**
 * scale this shapes coordinates by the x and y factors
 *
 * @param xFactor the amount to scale X coordinates
 * @param yFactor the amount to scale Y coordinates
 */
/*public*/ void LayoutShape::scaleCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    //shapePoints.forEach((lsp) ->
    foreach(LayoutShapePoint* lsp, shapePoints)
    {
        lsp->setPoint(MathUtil::multiply(lsp->getPoint(), factor));
    }//);
}

/**
 * translate this shapes coordinates by the x and y factors
 *
 * @param xFactor the amount to translate X coordinates
 * @param yFactor the amount to translate Y coordinates
 */
/*public*/ void LayoutShape::translateCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    //shapePoints.forEach((lsp) ->
    foreach(LayoutShapePoint* lsp, shapePoints)
    {
        lsp->setPoint(MathUtil::add(factor, lsp->getPoint()));
    }//);
}

/**
 * rotate this LayoutTrack's coordinates by angleDEG's
 *
 * @param angleDEG the amount to rotate in degrees
 */
/*public*/ void LayoutShape::rotateCoords(double angleDEG) {
    QPointF center = getCoordsCenter();
    //shapePoints.forEach((lsp) ->
    foreach(LayoutShapePoint* lsp, shapePoints)
    {
        lsp->setPoint(MathUtil::rotateDEG(lsp->getPoint(), center, angleDEG));
    }//);
}


//@Nonnull
/*protected*/ QMenu* LayoutShape::showShapePopUp(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent, int hitPointType) {
    if (popup != nullptr) {
        popup->clear();
    } else {
        popup = new QMenu();
    }
    if (layoutEditor->isEditable()) {
        int pointIndex = hitPointType - LayoutTrack::SHAPE_POINT_OFFSET_MIN;

        //JMenuItem jmi = popup.add(tr("MakeLabel", tr("LayoutShape")) + getName());
        QAction* jmi = popup->addAction(tr("Shape Name: %1 (select to change)").arg(getName()));

        jmi->setToolTip(tr("Select this to change the name of this shape"));
//        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
//            //prompt for new name
//            QString newValue = QuickPromptUtil.promptForString(layoutEditor,
//                    tr("LayoutShapeName"),
//                    tr("LayoutShapeName"),
//                    name);
//            setName(newValue);
//            layoutEditor.repaint();
//        });
        connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_changeName()));

        popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));
#if 0

//            if (true) { // only enable for debugging; TODO: delete or disable this for production
//                jmi = popup.add("hitPointType: " + hitPointType);
//                jmi->setEnabled(false);
//            }
        // add "Change Shape Type to..." menu
        JMenu shapeTypeMenu = new JMenu(tr("ChangeShapeTypeFromTo", getType().getName()));
        if (getType() != LayoutShapeType.eOpen) {
            jmi = shapeTypeMenu.add(new JCheckBoxMenuItem(new AbstractAction(tr("ShapeTypeOpen")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    setType(LayoutShapeType.eOpen);
                    layoutEditor.repaint();
                }
            }));
        }

        if (getType() != LayoutShapeType.eClosed) {
            jmi = shapeTypeMenu.add(new JCheckBoxMenuItem(new AbstractAction(tr("ShapeTypeClosed")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    setType(LayoutShapeType.eClosed);
                    layoutEditor.repaint();
                }
            }));
        }

        if (getType() != LayoutShapeType.eFilled) {
            jmi = shapeTypeMenu.add(new JCheckBoxMenuItem(new AbstractAction(tr("ShapeTypeFilled")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    setType(LayoutShapeType.eFilled);
                    layoutEditor.repaint();
                }
            }));
        }

        popup.add(shapeTypeMenu);

        // Add "Change Shape Type from {0} to..." menu
        if (hitPointType == LayoutTrack.SHAPE_CENTER) {
            JMenu shapePointTypeMenu = new JMenu(tr("ChangeAllShapePointTypesTo"));
            jmi = shapePointTypeMenu.add(new JCheckBoxMenuItem(new AbstractAction(tr("ShapePointTypeStraight")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    for (LayoutShapePoint ls : shapePoints) {
                        ls.setType(LayoutShapePointType.eStraight);
                    }
                    layoutEditor.repaint();
                }
            }));

            jmi = shapePointTypeMenu.add(new JCheckBoxMenuItem(new AbstractAction(tr("ShapePointTypeCurve")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    for (LayoutShapePoint ls : shapePoints) {
                        ls.setType(LayoutShapePointType.eCurve);
                    }
                    layoutEditor.repaint();
                }
            }));

            popup.add(shapePointTypeMenu);
        } else {
            LayoutShapePoint lsp = shapePoints.get(pointIndex);

            if (lsp != null) { // this should never happen... but just in case...
                String otherPointTypeName = (lsp.getType() == LayoutShapePointType.eStraight)
                        ? LayoutShapePointType.eCurve.getName() : LayoutShapePointType.eStraight.getName();
                jmi = popup.add(tr("ChangeShapePointTypeFromTo", lsp.getType().getName(), otherPointTypeName));
                jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
                    switch (lsp.getType()) {
                        case eStraight: {
                            lsp.setType(LayoutShapePointType.eCurve);
                            break;
                        }
                        case eCurve: {
                            lsp.setType(LayoutShapePointType.eStraight);
                            break;
                        }
                        default:
                            log.error("unexpected enum member!");
                    }
                    layoutEditor.repaint();
                });
            }
        }

        // Add "Set Level: x" menu
        jmi = popup.add(new JMenuItem(tr("MakeLabel",
                tr("ShapeLevelMenuItemTitle")) + level));
        jmi->setToolTipText(tr("ShapeLevelMenuItemToolTip"));
        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
            //prompt for level
            int newValue = QuickPromptUtil.promptForInteger(layoutEditor,
                    tr("ShapeLevelMenuItemTitle"),
                    tr("ShapeLevelMenuItemTitle"),
                    level, QuickPromptUtil.checkIntRange(1, 10, null));
            setLevel(newValue);
            layoutEditor.repaint();
        });

        jmi = popup.add(new JMenuItem(tr("ShapeLineColorMenuItemTitle")));
        jmi->setToolTipText(tr("ShapeLineColorMenuItemToolTip"));
        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
            Color newColor = JmriColorChooser.showDialog(null, "Choose a color", lineColor);
            if ((newColor != null) && !newColor.equals(lineColor)) {
                setLineColor(newColor);
                layoutEditor.repaint();
            }
        });
        jmi->setForeground(lineColor);
        jmi->setBackground(ColorUtil.contrast(lineColor));

        if (getType() == LayoutShapeType.eFilled) {
            jmi = popup.add(new JMenuItem(tr("ShapeFillColorMenuItemTitle")));
            jmi->setToolTipText(tr("ShapeFillColorMenuItemToolTip"));
            jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
                Color newColor = JmriColorChooser.showDialog(null, "Choose a color", fillColor);
                if ((newColor != null) && !newColor.equals(fillColor)) {
                    setFillColor(newColor);
                    layoutEditor.repaint();
                }
            });
            jmi->setForeground(fillColor);
            jmi->setBackground(ColorUtil.contrast(fillColor));
        }

        // add "Set Line Width: x" menu
        jmi = popup.add(new JMenuItem(tr("MakeLabel",
                tr("ShapeLineWidthMenuItemTitle")) + lineWidth));
        jmi->setToolTipText(tr("ShapeLineWidthMenuItemToolTip"));
        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
            //prompt for lineWidth
            int newValue = QuickPromptUtil.promptForInteger(layoutEditor,
                    tr("ShapeLineWidthMenuItemTitle"),
                    tr("ShapeLineWidthMenuItemTitle"),
                    lineWidth, QuickPromptUtil.checkIntRange(1, MAX_LINEWIDTH, null));
            setLineWidth(newValue);
            layoutEditor.repaint();
        });

        popup.add(new JSeparator(JSeparator.HORIZONTAL));
        if (hitPointType == LayoutTrack.SHAPE_CENTER) {
            jmi = popup.add(new AbstractAction(tr("ShapeDuplicateMenuItemTitle")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    LayoutShape ls = new LayoutShape(LayoutShape.this);
                    ls.setName(layoutEditor.getFinder().uniqueName("S"));

                    double gridSize = layoutEditor.getGridSize();
                    QPointF delta = new QPointF.Double(gridSize, gridSize);
                    for (LayoutShapePoint lsp : ls.getPoints()) {
                        lsp.setPoint(MathUtil::add(lsp.getPoint(), delta));
                    }
                    layoutEditor.getLayoutShapes().add(ls);
                    layoutEditor.clearSelectionGroups();
                    layoutEditor.amendSelectionGroup(ls);
                }
            });
            jmi->setToolTipText(tr("ShapeDuplicateMenuItemToolTip"));

            popup.add(new AbstractAction(tr("ButtonDelete")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (layoutEditor.removeLayoutShape(LayoutShape.this)) {
                        // Returned true if user did not cancel
                        remove();
                        dispose();
                    }
                }
            });
        } else {
            popup.add(new AbstractAction(tr("ButtonDelete")) {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    shapePoints.remove(pointIndex);
                    layoutEditor.repaint();
                }
            });
        }
        if (mouseEvent != null) {
            popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
        }
#endif
    }

    return popup;
}   // showPopup

void LayoutShape::on_changeName()
{
 //prompt for new name
 QString newValue = QuickPromptUtil::promptForString((Component*)layoutEditor,
         tr("Shape name"),
         tr("Shape name"),
         name);
 setName(newValue);
 layoutEditor->repaint();

}


/**
 * Clean up when this object is no longer needed. Should not be called while
 * the object is still displayed; see remove()
 */
//@Override
void LayoutShape::dispose() {
    if (popup != nullptr) {
        popup->clear();
    }
    popup = nullptr;
}

/**
 * Removes this object from display and persistence
 */
//@Override
void LayoutShape::remove() {
}

//@Override
/*protected*/ void LayoutShape::draw(EditScene* g2) {
#if 1
    //GeneralPath path = new GeneralPath();
 QPainterPath path = QPainterPath();

    int idx, cnt = shapePoints.size();
    for (idx = 0; idx < cnt; idx++) {
        // this point
        LayoutShapePoint* lsp = shapePoints.at(idx);
        QPointF p = lsp->getPoint();

        // left point
        int idxL = (idx + cnt - 1) % cnt;
        LayoutShapePoint* lspL = shapePoints.at(idxL);
        QPointF pL = lspL->getPoint();
        QPointF midL = MathUtil::midPoint(pL, p);

        // right point
        int idxR = (idx + 1) % cnt;
        LayoutShapePoint* lspR = shapePoints.at(idxR);
        QPointF pR = lspR->getPoint();
        QPointF midR = MathUtil::midPoint(p, pR);

        // if this is an open shape...
        LayoutShapePointType* lspt = lsp->getType();
        if (getType()->getType() == LayoutShapeType::eOpen) {
            // and this is first or last point...
            if ((idx == 0) || (idxR == 0)) {
                // then force straight shape point type
                lspt = new LayoutShapePointType(LayoutShapePointType::eStraight);
            }
        }
        switch (lspt->getType()) {
            case LayoutShapePointType::eStraight: {
                if (idx == 0) { // if this is the first point...
                    // ...and our shape is open...
                    if (getType()->getType() == LayoutShapeType::eOpen) {
                        path.moveTo(p.x(), p.y());    // then start here
                    } else {    // otherwise
                        path.moveTo(midL.x(), midL.y());  //start here
                        path.lineTo(p.x(), p.y());        //draw to here
                    }
                } else {
                    path.lineTo(midL.x(), midL.y());  //start here
                    path.lineTo(p.x(), p.y());        //draw to here
                }
                // if this is not the last point...
                // ...or our shape isn't open
                if ((idxR != 0) || (getType()->getType() != LayoutShapeType::eOpen)) {
                    path.lineTo(midR.x(), midR.y());      // draw to here
                }
                break;
            }

            case LayoutShapePointType::eCurve: {
                if (idx == 0) { // if this is the first point
                    path.moveTo(midL.x(), midL.y());  // then start here
                }
                path.quadTo(p.x(), p.y(), midR.x(), midR.y());
                break;
            }

            default:
                log->error("unexpected enum member!");
        }
    }   // for (idx = 0; idx < cnt; idx++)

    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
    QPen stroke = QPen(fillColor);
    if (getType()->getType() == LayoutShapeType::eFilled) {
//        g2.setColor(fillColor);
//        g2.fill(path);
     pathItem->setPen(stroke);

    }
//    g2.setStroke(new BasicStroke(lineWidth,
//            BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//    g2.setColor(lineColor);
//    g2.draw(path);
#endif
}   // draw

/*protected*/ void LayoutShape::drawEditControls(EditScene* g2) {
    QColor backgroundColor = layoutEditor->getBackground();
    QColor controlsColor = ColorUtil::contrast(backgroundColor);
    controlsColor = ColorUtil::setAlpha(controlsColor, 0.5);
#if 0
    g2.setColor(controlsColor);

    shapePoints.forEach((slp) -> {
        g2.draw(layoutEditor.layoutEditorControlRectAt(slp.getPoint()));
    });
    if (shapePoints.size() > 0) {
        QPointF end0 = shapePoints.get(0).getPoint();
        QPointF end1 = end0;
        for (LayoutShapePoint lsp : shapePoints) {
            QPointF end2 = lsp.getPoint();
            g2.draw(new Line2D.Double(end1, end2));
            end1 = end2;
        }

        if (getType() != LayoutShapeType.eOpen) {
            g2.draw(new Line2D.Double(end1, end0));
        }
    }

    g2.draw(trackEditControlCircleAt(getCoordsCenter()));
#endif
}   // drawEditControls

//these are convenience methods to return circles used to draw onscreen
//
//compute the control point rect at inPoint; use the turnout circle size
/*public*/ QGraphicsEllipseItem* LayoutShape::trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint) {
    return trackControlCircleAt(inPoint);
}

//compute the turnout circle at inPoint (used for drawing)
/*public*/ QGraphicsEllipseItem* LayoutShape::trackControlCircleAt(/*@Nonnull*/ QPointF inPoint) {
//    return new Ellipse2D.Double(inPoint.x() - layoutEditor->circleRadius,
//            inPoint.y() - layoutEditor->circleRadius,
//            layoutEditor->circleDiameter, layoutEditor->circleDiameter);
 return new QGraphicsEllipseItem(inPoint.x() - layoutEditor->circleRadius, inPoint.y() - layoutEditor->circleRadius,layoutEditor->circleDiameter, layoutEditor->circleDiameter);
}

/**
 * These are the points that make up the outline of the shape. Each point
 * can be ether a straight or a control point for a curve
 */
///*public*/ static class LayoutShapePoint {

//    /*private*/ transient LayoutShapePointType type;
//    /*private*/ transient QPointF point;

    /**
     * constructor method
     *
     * @param c QPointF for initial point
     */
    /*public*/ LayoutShapePoint::LayoutShapePoint(QPointF c) {
        this->type = new LayoutShapePointType("Straight");
        this->point = c;
    }

    /**
     * constructor method
     *
     * @param c QPointF for initial point
     */
    /*public*/ LayoutShapePoint::LayoutShapePoint(LayoutShapePointType* t, QPointF c) {
        //this(c);
     this->point = c;
        this->type = t;
    }

    /**
     * accessor methods
     *
     * @return the LayoutShapePointType
     */
    /*public*/ LayoutShapePointType* LayoutShapePoint::getType() {
        return type;
    }

    /*public*/ void LayoutShapePoint::setType(LayoutShapePointType *type) {
        this->type = type;
    }

    /*public*/ QPointF LayoutShapePoint::getPoint() {
        return point;
    }

    /*public*/ void LayoutShapePoint::setPoint(QPointF point) {
        this->point = point;
    }
//}   // class LayoutShapePoint

/**
 * enum LayoutShapeType eOpen, eClosed, eFilled
 */
///*public*/ enum LayoutShapeType {
//    eOpen("Open"), eClosed("Closed"), eFilled("Filled");

//    /*private*/ /*final*/ transient String name;
//    /*private*/ transient static /*final*/ Map<String, LayoutShapeType> ENUM_MAP;

    LayoutShapeType::LayoutShapeType(QString name) {
        this->name = name;
    }

//    //Build an immutable map of String name to enum pairs.
//    static {
        QMap<QString, LayoutShapeType*> LayoutShapeType::ENUM_MAP = QMap<QString, LayoutShapeType*>();

//        for (LayoutShapeType instance : LayoutShapeType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//    }

    /*public*/ /*static*/ LayoutShapeType* LayoutShapeType::getName(/*@CheckForNull*/ QString name) {
        return ENUM_MAP.value(name);
    }

    /*public*/ QString LayoutShapeType::getName() {
        return name;
    }
//}

/**
 * enum LayoutShapePointType eStraight, eCurve
 */
///*public*/ /*enum*/class  LayoutShapePointType
//{
// enum TYPES
//{
//  eStraight, //("Straight"),
//  eCurve //("Curve");
// };

//    /*private*/ /*final*/ /*transient*/ QString name;
//    /*private*/ static /*final*/ /*transient*/ QMap<QString, LayoutShapePointType*> ENUM_MAP;
//private:
/*public*/ LayoutShapePointType::LayoutShapePointType(QString name)
{
 this->name = name;
}

    //Build an immutable map of String name to enum pairs.
//    static {
        QMap<QString, LayoutShapePointType*> LayoutShapePointType::ENUM_MAP = QMap<QString, LayoutShapePointType*>();
//        for (LayoutShapePointType instance : LayoutShapePointType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//    }

    /*public*/ /*static*/ LayoutShapePointType* LayoutShapePointType::getName(/*@CheckForNull*/ QString name) {
 return ENUM_MAP.value(name);
}

    /*public*/ QString LayoutShapePointType::getName()
{
 return name;
}
//}; // enum LayoutShapePointType

/*private*/ /*final*/ /*static*/ Logger*  LayoutShape::log = LoggerFactory::getLogger("LayoutShape");
//}   // class LayoutShape
