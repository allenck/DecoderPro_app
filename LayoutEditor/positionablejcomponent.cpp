#include "positionablejcomponent.h"
//#include "positionable.h"
#include "editor.h"


//PositionableJComponent::PositionableJComponent(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * <p> <private>
 *
 * @author  Howard G. Penny copyright (C) 2005
 * @version $Revision: 22320 $
 */
///*public*/ class PositionableJComponent extends JComponent implements Positionable {


/*public*/ PositionableJComponent::PositionableJComponent(Editor* editor, QObject* parent) :  Positionable((QWidget*)parent)
{
 _editor = NULL;
 debug = false;
 active = true;
 //_bVisible  =true;

 _showTooltip =true;
 _editable = true;
 _positionable = true;
 _viewCoordinates = false;
 _controlling = true;
 _hidden = false;
 _itemGroup = NULL;

 _editor = editor;
 _scale = 1.0;
 log = new Logger("PositionableJComponent");
 debug = log->isDebugEnabled();
}
/*public*/ Positionable* PositionableJComponent::deepClone()
{
 PositionableJComponent* pos = new PositionableJComponent(_editor, NULL);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* PositionableJComponent::finishClone(Positionable* pos) {
    pos->setLocation(getX(), getY());
    pos->setDisplayLevel(getDisplayLevel());
    pos->setControlling(isControlling());
    pos->setHidden(isHidden());
    pos->setPositionable(isPositionable());
    pos->setShowTooltip(showTooltip());
    //pos->setTooltip(getTooltip());
    pos->setEditable(isEditable());
    pos->updateSize();
    return pos;
}
/*public*/ QObject* PositionableJComponent::getTextComponent() {
    return (QObject*)this;
}

/***************** Positionable methods **********************/

/*public*/ void PositionableJComponent::setPositionable(bool enabled) {
    _positionable = enabled;
    showHidden();
}
/*public*/ bool PositionableJComponent::isPositionable() { return _positionable; }

/*public*/ void PositionableJComponent::setEditable(bool enabled) {_editable = enabled;}
/*public*/ bool PositionableJComponent::isEditable() { return _editable; }

/*public*/ void PositionableJComponent::setViewCoordinates(bool enabled) { _viewCoordinates = enabled; }
/*public*/ bool PositionableJComponent::getViewCoordinates() { return _viewCoordinates; }

/*public*/ void PositionableJComponent::setControlling(bool enabled) {_controlling = enabled;}
/*public*/ bool PositionableJComponent::isControlling() { return _controlling; }

/*public*/ void PositionableJComponent::setHidden(bool hide) {_hidden = hide; }
/*public*/ bool PositionableJComponent::isHidden() { return _hidden;  }
/*public*/ void PositionableJComponent::showHidden() {
    if(!_hidden || _editor->isEditable()) {
        setVisible(true);
    } else {
        setVisible(false);
    }
}

/**
* Delayed setDisplayLevel for DnD
*/
/*public*/ void PositionableJComponent::setLevel(int l) {
    _displayLevel = l;
}
/*public*/ void PositionableJComponent::setDisplayLevel(int l) {
    int oldDisplayLevel = _displayLevel;
    _displayLevel = l;
    if (oldDisplayLevel!=l) {
        log->debug("Changing label display level from "+QString("%1").arg(oldDisplayLevel)+" to "+_displayLevel);
        _editor->displayLevelChange(this);
    }
}
/*public*/ int PositionableJComponent::getDisplayLevel() { return _displayLevel; }

/*public*/ void PositionableJComponent::setShowTooltip(bool set) {
    _showTooltip = set;
}
/*public*/ bool PositionableJComponent::showTooltip() {
    return _showTooltip;
}
/*public*/ void PositionableJComponent::setTooltip(QString tip) {
    _tooltip = tip;
}
/*public*/ QString PositionableJComponent::getTooltip() {
    return _tooltip;
}
/*public*/ void PositionableJComponent::setScale(double s) {
    _scale = s;
}
/*public*/ double PositionableJComponent::getScale() {
    return _scale;
}
// no subclasses support rotations (yet)
/*public*/ void PositionableJComponent::rotate(int /*deg*/) {
}
/*public*/ int PositionableJComponent::getDegrees() {
    return 0;
}
/*public*/ bool PositionableJComponent::getSaveOpaque() {
    return isOpaque();
}

/*public*/ QString PositionableJComponent::getNameString() {
    //return getName();
 return QString(this->metaObject()->className());
}

/*public*/ Editor* PositionableJComponent::getEditor(){
    return _editor;
}
/*public*/ void PositionableJComponent::setEditor(Editor* ed) {
    _editor = ed;
}

// overide where used - e.g. momentary
/*public*/ void PositionableJComponent::doMousePressed(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseReleased(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseClicked(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseDragged(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseMoved(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseEntered(QGraphicsSceneMouseEvent*  /*event*/) {}
/*public*/ void PositionableJComponent::doMouseExited(QGraphicsSceneMouseEvent*  /*event*/) {}

/*public*/ bool PositionableJComponent::storeItem() {
    return true;
}
/*public*/ bool PositionableJComponent::doViemMenu() {
    return true;
}
/**
 * For over-riding in the using classes: add item specific menu choices
 */
/*public*/ bool PositionableJComponent::setRotateOrthogonalMenu(QMenu* /*popup*/){
    return false;
}
/*public*/ bool PositionableJComponent::setRotateMenu(QMenu* /*popup*/){
    return false;
}
/*public*/ bool PositionableJComponent::setScaleMenu(QMenu* /*popup*/){
    return false;
}
/*public*/ bool PositionableJComponent::setDisableControlMenu(QMenu* /*popup*/) {
    return false;
}
/*public*/ bool PositionableJComponent::setTextEditMenu(QMenu* /*popup*/) {
    return false;
}
/*public*/ bool PositionableJComponent::setEditItemMenu(QMenu* /*popup*/) {
    return false;
}
/*public*/ bool PositionableJComponent::showPopUp(QMenu* /*popup*/) {
    return false;
}
/*public*/ bool PositionableJComponent::setEditIconMenu(QMenu* /*popup*/) {
    return false;
}

/*public*/ PositionablePopupUtil* PositionableJComponent::getPopupUtility() {
     return NULL;
}
/*public*/ void PositionableJComponent::setPopupUtility(PositionablePopupUtil* /*tu*/) { }

/*public*/ void PositionableJComponent::updateSize() {
}
/*public*/ int PositionableJComponent::maxWidth() {
    return getWidth();
}
/*public*/ int PositionableJComponent::maxHeight() {
    return getHeight();
}

/**************** end Positionable methods **********************/

/**
 * Removes this object from display and persistance
 */
/*public*/ void PositionableJComponent::remove() {
    _editor->removeFromContents(this);
    cleanup();
    // remove from persistance by flagging inactive
    active = false;
    //dispose();
    deleteLater();

}

/**
 * To be overridden if any special work needs to be done
 */
void PositionableJComponent::cleanup() {}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool PositionableJComponent::isActive() {
    return active;
}

/*public*/ NamedBean* PositionableJComponent::getNamedBean() { return NULL; }

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionableJComponent.class.getName());
//}

// JComponent stuff
/*public*/ QRectF PositionableJComponent::getBounds()
{
  return  QRectF(getX(), getY(), getWidth(), getHeight());
}
QRectF PositionableJComponent::getBounds(QRectF r)
{
 return r;
}

bool PositionableJComponent::contains(int /*x*/, int /*y*/)
{
 return false; // TODO:
}
int PositionableJComponent::getX()
{
 return _x;
}
int PositionableJComponent::getY()
{
 return _y;
}
void PositionableJComponent::setLocation(int x, int y)
{
 _loc = QPointF(x,y);
 _x = x;
 _y = y;
}
void PositionableJComponent::setLocation(QPointF p)
{
 _loc = p;
 _x = p.x();
 _y = p.y();
}
QPointF PositionableJComponent:: getLocation() { return _loc;}

void PositionableJComponent::setSize(int width, int height)
{
 _size = QSize(width, height);
}
QSize PositionableJComponent::getSize() {return _size;}

//void PositionableJComponent::setVisible(bool b)
//{
// _bVisible = b;
//}
//bool PositionableJComponent::isVisible() { return QLabel::isVisible();}

int PositionableJComponent::getWidth()
{
 return _size.width();
}
int PositionableJComponent::getHeight()
{
 return _size.height();
}
void PositionableJComponent::setOpaque(bool isOpaque)
{
 _bOpaque = isOpaque;
}
bool PositionableJComponent::isOpaque() { return _bOpaque;}

void PositionableJComponent::setBackground(QColor bg)
{
 _background = bg;
}
QColor PositionableJComponent::getBackground() { return _background;}

void PositionableJComponent::setForeground(QColor bg)
{
 _foreground = bg;
}
QColor PositionableJComponent::getForeground() { return _foreground;}

QFont PositionableJComponent::getFont() {return _font;}

void PositionableJComponent::invalidate()
{

}
void PositionableJComponent::repaint()
{

}
bool PositionableJComponent::requestFocusInWindow()
{
 return false;
}

