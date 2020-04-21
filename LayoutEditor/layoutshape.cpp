#include "layoutshape.h"
#include "loggerfactory.h"
#include "mathutil.h"
#include "layouteditor.h"
#include "layouttrack.h"
#include "quickpromptutil.h"
#include <QGraphicsItemGroup>
#include "jmricolorchooser.h"
#include "abstractaction.h"
#include "layouteditorfinditems.h"

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
    this->layoutShapeType = LayoutShapeType::eOpen;
    this->shapePoints = QList<LayoutShapePoint*>();

}

/**
 * constructor method (used by XML loading code)
 *
 * @param name         the name of the shape
 * @param layoutEditor reference to the LayoutEditor this shape is in
 */
/*public*/ LayoutShape::LayoutShape(QString name, LayoutShapeType::TYPES t, LayoutEditor* layoutEditor, QObject *parent) : QObject(parent){
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

 this->layoutShapeType = LayoutShapeType::eOpen;

}

/**
 * constructor method (used by duplicate)
 *
 * @param layoutShape to duplicate (deep copy)
 */
/*public*/ LayoutShape::LayoutShape(LayoutShape* layoutShape, QObject* parent) : QObject(parent){
 lineColor = QColor(Qt::black);
 fillColor = QColor(Qt::darkGray);
 layoutShapeType = LayoutShapeType::eOpen;

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

/*public*/ LayoutShapeType::TYPES LayoutShape::getType() {
    return layoutShapeType;
}

/*public*/ void LayoutShape::setType(LayoutShapeType::TYPES t)
{
 if (layoutShapeType != t)
 {
  switch (t ) {
      case LayoutShapeType::eOpen:
      case LayoutShapeType::eClosed:
      case LayoutShapeType::eFilled:
          layoutShapeType = t;
          break;
      default:    // You shouldn't ever have any invalid LayoutShapeTypes
          log->error("Invalid Shape Type " + t); //I18IN
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
 if(nearIndex < 0)
  nearIndex = 0;
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
        if ((getType() == LayoutShapeType::eOpen) && (nearIndex == 0)) {
            distR = MathUtil::distance(pR, p);
            distL = MathUtil::distance(pR, sp);
        }
        int beforeIndex = (distR < distL) ? idxR : nearIndex;

        // if nearIndex is the last point in open shape...
        if ((getType() == LayoutShapeType::eOpen) && (idxR == 0)) {
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
/*public*/ void LayoutShape::addPoint(LayoutShapePointType::TYPES t, QPointF p) {
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
        pointIndex = hitPointType - LayoutTrack::SHAPE_POINT_OFFSET_MIN;

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
#if 1

//            if (true) { // only enable for debugging; TODO: delete or disable this for production
//                jmi = popup.add("hitPointType: " + hitPointType);
//                jmi->setEnabled(false);
//            }
        // add "Change Shape Type to..." menu
        QMenu* shapeTypeMenu = new QMenu(tr("Change shape type from %1 to").arg(LayoutShapeType::getName(getType())));
        if (getType() != LayoutShapeType::eOpen)
        {
         QAction* jmi = new QAction(tr("Open"),this);
         shapeTypeMenu->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setType(LayoutShapeType.eOpen);
//                    layoutEditor.repaint();
//                }
//            }));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setOpen()));
        }
#endif

        if (getType() != LayoutShapeType::eClosed) {
         QAction* jmi = new QAction(tr("Closed"), this);
         shapeTypeMenu->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setType(LayoutShapeType.eClosed);
//                    layoutEditor.repaint();
//                }
//            }));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setClosed()));
        }

        if (getType() != LayoutShapeType::eFilled)
        {
         QAction* jmi = new QAction(tr("Filled"), this);
         shapeTypeMenu->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setType(LayoutShapeType.eFilled);
//                    layoutEditor.repaint();
//                }
//            }));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setFilled()));
        }

        popup->addMenu(shapeTypeMenu);
#if 1
        // Add "Change Shape Type from {0} to..." menu
        if (hitPointType == LayoutTrack::SHAPE_CENTER) {
            QMenu* shapePointTypeMenu = new QMenu(tr("Change all shape point types to"));
            QAction* jmi = new QAction(tr("Straight"),this);
            shapePointTypeMenu->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    for (LayoutShapePoint ls : shapePoints) {
//                        ls.setType(LayoutShapePointType.eStraight);
//                    }
//                    layoutEditor.repaint();
//                }
//            }));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setStraight()));
            jmi = new QAction(tr("Curve"),this);
            shapePointTypeMenu->addAction(jmi);

//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                        for (LayoutShapePoint ls : shapePoints) {
//                         ls.setType(LayoutShapePointType.eCurve);
//                    }
//                    layoutEditor.repaint();
//                }
//            }));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setCurve()));

            popup->addMenu(shapePointTypeMenu);
        }
        else
        {
            LayoutShapePoint* lsp = shapePoints.at(pointIndex);

            if (lsp != nullptr) { // this should never happen... but just in case...
                otherPointTypeName = (lsp->getType() == LayoutShapePointType::eStraight)
                        ? LayoutShapePointType(LayoutShapePointType::eCurve).getName() : LayoutShapePointType(LayoutShapePointType::eStraight).getName();
                QAction* jmi = new QAction(tr("Change shape point type from %1 to %2").arg(LayoutShapePointType::typeName(lsp->getType())).arg(otherPointTypeName),this);
                popup->addAction(jmi);
                jmi->setChecked(hitPointType != LayoutTrack::SHAPE_CENTER);
#if 0
                jmi->addActionListener((java.awt.event.ActionEvent e3) ->
                {
                    switch (lsp->getType()->getType()) {
                        case eStraight: {
                            lsp->setType(LayoutShapePointType::eCurve);
                            break;
                        }
                        case eCurve: {
                            lsp->setType(LayoutShapePointType::eStraight);
                            break;
                        }
                        default:
                            log->error("unexpected enum member!");
                    }
                    layoutEditor->repaint();
                });
#endif
                connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_changeShapePointType()));
            }
        }

        // Add "Set Level: x" menu
        jmi = new QAction(tr("%1").arg(
                tr("Set Level ")) + QString::number(level), this);
        popup->addAction(jmi);
        jmi->setToolTip(tr("Select this to change the level of this shape"));
//        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
//            //prompt for level
//            int newValue = QuickPromptUtil::promptForInteger(layoutEditor,
//                    tr("ShapeLevelMenuItemTitle"),
//                    tr("ShapeLevelMenuItemTitle"),
//                    level, QuickPromptUtil.checkIntRange(1, 10, null));
//            setLevel(newValue);
//            layoutEditor->repaint();
//        });
        connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setLevel()));

        jmi = new QAction(tr("Set Line Color"),this);
        popup->addAction(jmi);
        jmi->setToolTip(tr("Select this to change the line color of this shape"));
//        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
//            Color newColor = JmriColorChooser.showDialog(null, "Choose a color", lineColor);
//            if ((newColor != null) && !newColor.equals(lineColor)) {
//                setLineColor(newColor);
//                layoutEditor.repaint();
//            }
//        });
        connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_lineColor()));
//        jmi->setForeground(lineColor);
//        jmi->setBackground(ColorUtil::contrast(lineColor));

        if (getType() == LayoutShapeType::eFilled) {
            jmi = new QAction(tr("Set Fill Color"));
            popup->addAction(jmi);
            jmi->setToolTip(tr("Select this to change the fill color of this shape"));
//            jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
//                Color newColor = JmriColorChooser.showDialog(null, "Choose a color", fillColor);
//                if ((newColor != null) && !newColor.equals(fillColor)) {
//                    setFillColor(newColor);
//                    layoutEditor.repaint();
//                }
//            });
//            jmi->setForeground(fillColor);
//            jmi->setBackground(ColorUtil.contrast(fillColor));
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_setFillColor()));
        }

        // add "Set Line Width: x" menu
        jmi = new QAction(tr("%1").arg(
                tr("Set Line Width ")) + QString::number(lineWidth),this);
        popup->addAction(jmi);
        jmi->setToolTip(tr("Select this to change the line width of this shape"));
//        jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
//            //prompt for lineWidth
//            int newValue = QuickPromptUtil.promptForInteger(layoutEditor,
//                    tr("ShapeLineWidthMenuItemTitle"),
//                    tr("ShapeLineWidthMenuItemTitle"),
//                    lineWidth, QuickPromptUtil.checkIntRange(1, MAX_LINEWIDTH, null));
//            setLineWidth(newValue);
//            layoutEditor.repaint();
//        });
        connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_lineWidth()));

        popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));
        if (hitPointType == LayoutTrack::SHAPE_CENTER) {
            jmi = new QAction(tr("Duplicate shape"),this);
            popup->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    LayoutShape ls = new LayoutShape(LayoutShape.this);
//                    ls.setName(layoutEditor.getFinder().uniqueName("S"));

//                    double gridSize = layoutEditor.getGridSize();
//                    QPointF delta = new QPointF.Double(gridSize, gridSize);
//                    for (LayoutShapePoint lsp : ls.getPoints()) {
//                        lsp.setPoint(MathUtil::add(lsp.getPoint(), delta));
//                    }
//                    layoutEditor.getLayoutShapes().add(ls);
//                    layoutEditor.clearSelectionGroups();
//                    layoutEditor.amendSelectionGroup(ls);
//                }
//            });
            connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_duplicateShape()));
            jmi->setToolTip(tr("Select this to duplicate this shape"));

            jmi = new QAction(new AbstractAction(tr("Delete"), this));
            popup->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (layoutEditor.removeLayoutShape(LayoutShape.this)) {
//                        // Returned true if user did not cancel
//                        remove();
//                        dispose();
//                    }
//                }
//            });
              connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_deleteShape()));
        } else
#endif
        {
         jmi = new AbstractAction(tr("Delete"), this);
         popup->addAction(jmi);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    shapePoints.remove(pointIndex);
//                    layoutEditor.repaint();
//                }
//            });
              connect(jmi, SIGNAL(triggered(bool)), this, SLOT(on_deletePoint()));
        }
        if (mouseEvent != nullptr) {
            //popup->show(mouseEvent->getComponent(), mouseEvent->pos().x(), mouseEvent.getY());
         popup->exec();
        }
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

/*public*/ void LayoutShape::on_setOpen() {
    setType(LayoutShapeType::eOpen);
    layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_setClosed()
{
    setType(LayoutShapeType::eClosed);
    layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_setStraight() {
    for (LayoutShapePoint* ls : shapePoints) {
        ls->setType(LayoutShapePointType::eStraight);
    }
    layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_setCurve() {
        for (LayoutShapePoint* ls : shapePoints) {
         ls->setType(LayoutShapePointType::eCurve);
    }
    layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_lineColor()
{
 QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", lineColor);
 if ((newColor.isValid()) && newColor!=(lineColor)) {
     setLineColor(newColor);
     layoutEditor->repaint();
 }
}

/*public*/ void LayoutShape::on_setFillColor()
{
 QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", lineColor);
 if ((newColor.isValid()) && newColor!=(lineColor)) {
     setFillColor(newColor);
     layoutEditor->repaint();
 }
}

/*public*/ void LayoutShape::on_setFilled()
{
  setType(LayoutShapeType::eFilled);
  layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_lineWidth()
{
 int newValue = QuickPromptUtil::promptForInteger((Component*)layoutEditor,
         tr("Set Line Width"),
         tr("Set Line Width"),
         lineWidth, QuickPromptUtil::checkIntRange(1, MAX_LINEWIDTH, nullptr));
 setLineWidth(newValue);
 layoutEditor->repaint();
}

/*public*/ void LayoutShape::on_setLevel()
{
 //prompt for level
 int newValue = QuickPromptUtil::promptForInteger((Component*)layoutEditor,
         tr("Set Level"),
         tr("Set Level"),
         level, QuickPromptUtil::checkIntRange(1, 10, nullptr));
 setLevel(newValue);
 layoutEditor->repaint();

}

/*public*/ void LayoutShape::on_duplicateShape() {
    LayoutShape* ls = new LayoutShape(this);
    ls->setName(layoutEditor->getFinder()->uniqueName("S"));

    double gridSize = layoutEditor->getGridSize();
    QPointF delta = QPointF(gridSize, gridSize);
    for (LayoutShapePoint* lsp : ls->getPoints()) {
        lsp->setPoint(MathUtil::add(lsp->getPoint(), delta));
    }
    layoutEditor->getLayoutShapes()->append(ls);
    layoutEditor->clearSelectionGroups();
    layoutEditor->amendSelectionGroup(ls);
}

/*public*/ void LayoutShape::on_deleteShape()
{
    if (layoutEditor->removeLayoutShape(this)) {
        // Returned true if user did not cancel
        remove();
        dispose();
    }
}

/*public*/ void LayoutShape::on_deletePoint()
{
    shapePoints.removeAt(pointIndex);
    layoutEditor->repaint();
}

/*pubic*/ void LayoutShape::on_changeShapePointType()
{
 LayoutShapePoint* lsp = shapePoints.at(pointIndex);
 switch (lsp->getType()) {
     case LayoutShapePointType::eStraight: {
         lsp->setType(LayoutShapePointType::eCurve);
         break;
     }
     case LayoutShapePointType::eCurve: {
         lsp->setType(LayoutShapePointType::eStraight);
         break;
     }
     default:
         log->error("unexpected enum member!");
 }
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
/*protected*/ void LayoutShape::draw(EditScene* g2)
{

 paths = invalidateItem(g2, paths);

 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

 //GeneralPath path = new GeneralPath();
 QPainterPath path = QPainterPath();

 int idx, cnt = shapePoints.size();
 for (idx = 0; idx < cnt; idx++)
 {
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
  LayoutShapePointType::TYPES lspt = lsp->getType();
  if (getType() == LayoutShapeType::eOpen)
  {
   // and this is first or last point...
   if ((idx == 0) || (idxR == 0)) {
       // then force straight shape point type
       lspt = LayoutShapePointType::eStraight;
   }
  }
  switch (lspt)
  {
   case LayoutShapePointType::eStraight:
   {
     if (idx == 0) { // if this is the first point...
         // ...and our shape is open...
         if (getType() == LayoutShapeType::eOpen) {
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
     if ((idxR != 0) || (getType() != LayoutShapeType::eOpen)) {
         path.lineTo(midR.x(), midR.y());      // draw to here
     }
     break;
    }

   case LayoutShapePointType::eCurve:
   {
    if (idx == 0) { // if this is the first point
        path.moveTo(midL.x(), midL.y());  // then start here
    }
    path.quadTo(p.x(), p.y(), midR.x(), midR.y());
    break;
   }

   default:
    log->error(tr("LayoutShape: unexpected enum member! %1").arg(lspt));
  }
 }   // for (idx = 0; idx < cnt; idx++)

 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
 QPen fillPen = QPen(fillColor);
 if (getType() == LayoutShapeType::eFilled) {
//        g2.setColor(fillColor);
//        g2.fill(path);
  pathItem->setPen(fillPen);

 }
//    g2.setStroke(new BasicStroke(lineWidth,
//            BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
//    g2.setColor(lineColor);
 QPen stroke = QPen(lineColor,1,  Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
 pathItem->setPen(stroke);
 itemGroup->addToGroup(pathItem);
 paths = itemGroup;
 g2->addItem(paths);
//    g2.draw(path);
}   // draw

/*protected*/ void LayoutShape::drawEditControls(EditScene* g2)
{
 QColor backgroundColor = layoutEditor->getBackground();
 QColor controlsColor = ColorUtil::contrast(backgroundColor);
 if(layoutEditor->selectedObject == this)
  controlsColor = QColor(Qt::magenta);
 //controlsColor = ColorUtil::setAlpha(controlsColor, 0.5);
 log->debug(tr("LayoutShape::drawEditControls controls color %1 ").arg(ColorUtil::colorToColorName(controlsColor)));
#if 1
 rects = invalidateItem(g2, rects);

 //g2.setColor(controlsColor);

 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 QPen drawingStroke = QPen(controlsColor);

//    shapePoints.forEach((slp) -> {
//        g2.draw(layoutEditor.layoutEditorControlRectAt(slp.getPoint()));
//    });
 foreach(LayoutShapePoint* slp, shapePoints)
 {
  QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->layoutEditorControlRectAt(slp->getPoint()));
  rectItem->setPen(drawingStroke);
  itemGroup->addToGroup(rectItem);
 }
 if (shapePoints.size() > 0) {
     QPointF end0 = shapePoints.at(0)->getPoint();
     QPointF end1 = end0;
     QGraphicsLineItem* lineItem;
     for (LayoutShapePoint* lsp : shapePoints) {
         QPointF end2 = lsp->getPoint();
         //g2.draw(new Line2D.Double(end1, end2));
         lineItem = new QGraphicsLineItem(end1.x(), end1.y(), end2.x(), end2.y() );
         lineItem->setPen(drawingStroke);
         itemGroup->addToGroup(lineItem);
         end1 = end2;
     }

     if (getType() != LayoutShapeType::eOpen) {
         //g2.draw(new Line2D.Double(end1, end0));
      lineItem = new QGraphicsLineItem(end1.x(), end1.y(), end0.x(), end0.y() );
      lineItem->setPen(drawingStroke);
      itemGroup->addToGroup(lineItem);
     }
 }

 //g2.draw(trackEditControlCircleAt(getCoordsCenter()));
 QGraphicsEllipseItem* circle = trackEditControlCircleAt(getCoordsCenter());
 itemGroup->addToGroup(circle);
 rects = itemGroup;
 g2->addItem(rects);
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
        this->type = LayoutShapePointType::eStraight;
        this->point = c;
    }

    /**
     * constructor method
     *
     * @param c QPointF for initial point
     */
    /*public*/ LayoutShapePoint::LayoutShapePoint(LayoutShapePointType::TYPES t, QPointF c) {
        //this(c);
     this->point = c;
        this->type = t;
    }

    /**
     * accessor methods
     *
     * @return the LayoutShapePointType
     */
    /*public*/ LayoutShapePointType::TYPES LayoutShapePoint::getType() {
        return type;
    }

    /*public*/ void LayoutShapePoint::setType(LayoutShapePointType::TYPES type) {
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
     if(LayoutShapeType::ENUM_MAP.isEmpty())
     {
      LayoutShapeType::ENUM_MAP.insert("Open", eOpen);
      LayoutShapeType::ENUM_MAP.insert("Closed", eClosed);
      LayoutShapeType::ENUM_MAP.insert("Filled", eFilled);
     }
    }

//    //Build an immutable map of String name to enum pairs.
//    static {
        QMap<QString, LayoutShapeType::TYPES> LayoutShapeType::ENUM_MAP = QMap<QString, LayoutShapeType::TYPES>();

//        for (LayoutShapeType instance : LayoutShapeType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//    }

    /*public*/ /*static*/ LayoutShapeType::TYPES LayoutShapeType::getName(/*@CheckForNull*/ QString name) {
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
 if(LayoutShapePointType::ENUM_MAP.isEmpty())
 {
  LayoutShapePointType::ENUM_MAP.insert("Straight", eStraight);
  LayoutShapePointType::ENUM_MAP.insert("Curve", eCurve);
 }
}

    //Build an immutable map of String name to enum pairs.
//    static {
        QMap<QString, LayoutShapePointType::TYPES> LayoutShapePointType::ENUM_MAP = QMap<QString, LayoutShapePointType::TYPES>();
//        for (LayoutShapePointType instance : LayoutShapePointType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//        LayoutShapePointType::ENUM_MAP.insert("Straight", new LayoutShapePointType("Straight"));
//        LayoutShapePointType::ENUM_MAP.insert("Curve", new LayoutShapePointType("Curve"));

//    }

    /*public*/ /*static*/ LayoutShapePointType::TYPES LayoutShapePointType::getName(/*@CheckForNull*/ QString name) {
 return ENUM_MAP.value(name);
}

/*public*/ QString LayoutShapePointType::getName()
{
 return name;
}
//}; // enum LayoutShapePointType

/*private*/ /*final*/ /*static*/ Logger*  LayoutShape::log = LoggerFactory::getLogger("LayoutShape");
//}   // class LayoutShape

/*public*/ QGraphicsItemGroup* LayoutShape::invalidateItem(EditScene* g2, QGraphicsItemGroup* item)
{
 if(item!=nullptr && item->scene() != nullptr)
 {
  for(QGraphicsItem* i : item->childItems())
  {
   if(qgraphicsitem_cast<QGraphicsItemGroup*>(i) && qgraphicsitem_cast<QGraphicsItemGroup*>(i)->childItems().count()>0)
    invalidateItem(g2, qgraphicsitem_cast<QGraphicsItemGroup*>(i));
   g2->removeItem(i);
  }
  if(item->scene() == g2)
   g2->destroyItemGroup(item);

 }
 item = nullptr;
 return item;
}
