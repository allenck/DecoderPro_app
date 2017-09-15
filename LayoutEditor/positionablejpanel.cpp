#include "positionablejpanel.h"
#include <QGraphicsSceneMouseEvent>
#include "editor.h"
#include "positionablepopuputil.h"
#include "iconadder.h"
#include <QGraphicsScene>

//PositionableJPanel::PositionableJPanel(QObject *parent) :
//    QWidget(parent)
//{
//}
/**
 * <p> </p>
 *
 * @author  Bob Jacobsen copyright (C) 2009
 * @version $Revision: 22320 $
 */
///*public*/ class PositionableJPanel extends JPanel implements Positionable, MouseListener, MouseMotionListener {


/*public*/ PositionableJPanel::PositionableJPanel(Editor* editor, QObject* parent)
 : PositionableLabel("", editor,(Positionable*)parent)
{
 _editor = NULL;
 debug = false;

 _showTooltip =true;
 _editable = true;
 _positionable = true;
 _viewCoordinates = false;
 _controlling = true;
 _hidden = false;
 lock = NULL;
 showTooltipItem = NULL;
 log = new Logger("PositionableJPanel");
 active = true;
 _popupUtil = NULL;

 _editor = editor;
  debug = log->isDebugEnabled();
}

/*public*/ Positionable* PositionableJPanel::deepClone() {
    PositionableJPanel* pos = new PositionableJPanel(_editor);
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* PositionableJPanel::finishClone(Positionable* p) {
    PositionableJPanel* pos = (PositionableJPanel*)p;
    pos->setLocation(_x, _y);
    pos->_displayLevel = _displayLevel;
    pos->_controlling = _controlling;
    pos->_hidden = _hidden;
    pos->_positionable = _positionable;
    pos->_showTooltip =_showTooltip;
    pos->setTooltip(getTooltip());
    pos->_editable = _editable;
    if (getPopupUtility()==NULL) {
        pos->setPopupUtility(NULL);
    } else {
        pos->setPopupUtility(getPopupUtility()->clone((Positionable*)pos, pos->getTextComponent()));
    }
    pos->updateSize();
    return (Positionable*)pos;
}

///*public*/ void PositionableJPanel::setPositionable(bool enabled) {_positionable = enabled;}
///*public*/ bool PositionableJPanel::isPositionable() { return _positionable; }

///*public*/ void PositionableJPanel::setEditable(bool enabled) {_editable = enabled;}
///*public*/ bool PositionableJPanel::isEditable() { return _editable; }

///*public*/ void PositionableJPanel::setViewCoordinates(bool enabled) { _viewCoordinates = enabled; }
///*public*/ bool PositionableJPanel::getViewCoordinates() { return _viewCoordinates; }

///*public*/ void PositionableJPanel::setControlling(bool enabled) {_controlling = enabled;}
///*public*/ bool PositionableJPanel::isControlling() { return _controlling; }

///*public*/ void PositionableJPanel::setHidden(bool hide) {_hidden = hide; }
///*public*/ bool PositionableJPanel::isHidden() { return _hidden;  }
///*public*/ void PositionableJPanel::showHidden() {
//    if(!_hidden || _editor->isEditable()) {
//        setVisible(true);
//    } else {
//        setVisible(false);
//    }
//}

///**
//* Delayed setDisplayLevel for DnD
//*/
///*public*/ void PositionableJPanel::setLevel(int l) {
//    _displayLevel = l;
//}
///*public*/ void PositionableJPanel::setDisplayLevel(int l) {
//    int oldDisplayLevel = _displayLevel;
//    _displayLevel = l;
//    if (oldDisplayLevel!=l){
//        log->debug("Changing label display level from "+QString::number(oldDisplayLevel)+" to "+QString::number(_displayLevel));
//        _editor->displayLevelChange((Positionable*)this);
//    }
//}
///*public*/ int PositionableJPanel::getDisplayLevel() { return _displayLevel; }

///*public*/ void PositionableJPanel::setShowTooltip(bool set) {
//    _showTooltip = set;
//}
///*public*/ bool PositionableJPanel::showTooltip() {
//    return _showTooltip;
//}
///*public*/ void PositionableJPanel::setTooltip(QString tip) {
//    _tooltip = tip;
//}
///*public*/ QString PositionableJPanel::getTooltip() {
//    return _tooltip;
//}
/*public*/ void PositionableJPanel::setScale(double s) {
    _scale = s;
}
/*public*/ double PositionableJPanel::getScale() {
    return _scale;
}
// no subclasses support rotations (yet)
/*public*/ void PositionableJPanel::rotate(int /*deg*/) {
}
/*public*/ int PositionableJPanel::getDegrees() {
    return 0;
}
/*public*/ bool PositionableJPanel::getSaveOpaque() {
    return isOpaque();
}
/*public*/ QObject* PositionableJPanel::getTextComponent() {
    return this;
}

/*public*/ QString PositionableJPanel::getNameString() {
    return getName();
}

/*public*/ Editor* PositionableJPanel::getEditor(){
    return _editor;
}
/*public*/ void PositionableJPanel::setEditor(Editor* ed) {
    _editor = ed;
}

// overide where used - e.g. momentary
/*public*/ void PositionableJPanel::doMousePressed(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseReleased(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseClicked(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseDragged(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseMoved(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseEntered(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableJPanel::doMouseExited(QGraphicsSceneMouseEvent* /*event*/) {}

/*public*/ bool PositionableJPanel::storeItem() {
    return true;
}
/*public*/ bool PositionableJPanel::doViemMenu() {
    return true;
}
/**
 * For over-riding in the using classes: add item specific menu choices
 */
/*public*/ bool PositionableJPanel::setRotateOrthogonalMenu(QMenu*/*popup*/){
    return false;
}
/*public*/ bool PositionableJPanel::setRotateMenu(QMenu*/*popup*/){
    return false;
}
/*public*/ bool PositionableJPanel::setScaleMenu(QMenu*/*popup*/){
    return false;
}
/*public*/ bool PositionableJPanel::setDisableControlMenu(QMenu*/*popup*/) {
    return false;
}
/*public*/ bool PositionableJPanel::setTextEditMenu(QMenu*/*popup*/) {
    return false;
}
/*public*/ bool PositionableJPanel::showPopUp(QMenu*/*popup*/) {
    return false;
}

/*public*/ bool PositionableJPanel::setEditIconMenu(QMenu*/*popup*/) {
    return false;
}
/*public*/ bool PositionableJPanel::setEditItemMenu(QMenu*popup) {
    return setEditIconMenu(popup);
}

/**
*  Utility
*/
/*protected*/ void PositionableJPanel::makeIconEditorFrame(QObject* /*pos*/, QString name, bool table, IconAdder* editor) {
    if (editor!=NULL) {
        _iconEditor = editor;
    } else {
        _iconEditor = new IconAdder(name);
    }
    _iconEditorFrame = _editor->makeAddIconFrame(name, false, table, _iconEditor);
//    _iconEditorFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                _iconEditorFrame.dispose();
//                _iconEditorFrame = NULL;
//            }
//        });
//    _iconEditorFrame->setLocationRelativeTo(pos);
//    _iconEditorFrame->toFront();
    _iconEditorFrame->setVisible(true);
}

void PositionableJPanel::edit() {
}

/**************** end Positionable methods **********************/

/**
 * Removes this object from display and persistance
 */
/*public*/ void PositionableJPanel::remove() {
    _editor->removeFromContents((Positionable*)this);
    cleanup();
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * To be overridden if any special work needs to be done
 */
void PositionableJPanel::cleanup() {}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool PositionableJPanel::isActive() {
    return active;
}
/*public*/ void PositionableJPanel::mousePressed(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mousePressed(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
//    _editor->mousePressed(e);
}

/*public*/ void PositionableJPanel::mouseReleased(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mouseReleased(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}

/*public*/ void PositionableJPanel::mouseClicked(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mouseClicked(new QGraphicsSceneMouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}
/*public*/ void PositionableJPanel::mouseExited(QGraphicsSceneMouseEvent* /*e*/) {
//    transferFocus();
//    _editor->mouseExited(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}
/*public*/ void PositionableJPanel::mouseEntered(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mouseEntered(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}

/*public*/ void PositionableJPanel::mouseMoved(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mouseMoved(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}
/*public*/ void PositionableJPanel::mouseDragged(QGraphicsSceneMouseEvent* /*e*/) {
//    _editor->mouseDragged(new MouseEvent(this, e.getID(), e.getWhen(), e.getModifiersEx(),
//                                         e.getX()+this.getX(), e.getY()+this.getY(),
//                                         e.getClickCount(), e.isPopupTrigger()));
}

/***************************************************************/

///*public*/ void PositionableJPanel::setPopupUtility(PositionablePopupUtil* tu) {
//    _popupUtil = tu;
//}
///*public*/ PositionablePopupUtil* PositionableJPanel::getPopupUtility() {
//    return _popupUtil;
//}

/**
 * Update the AWT and Swing size information due to change in internal
 * state, e.g. if one or more of the icons that might be displayed
 * is changed
 */
/*public*/ void PositionableJPanel::updateSize() {
//    invalidate();
    setSize(maxWidth(), maxHeight());
    if (debug) {
//            javax.swing.JTextField text = (javax.swing.JTextField)_popupUtil->_textComponent;
//        log->debug("updateSize: "+_popupUtil->toString()+
//                  ", text: w="+getFontMetrics(_popupUtil->getFont()).stringWidth(_popupUtil->getText())+
//                  "h="+getFontMetrics(_popupUtil->getFont()).getHeight());
    }
    //validate();
    repaint();
}

/*public*/ int PositionableJPanel::maxWidth() {
    int max = 0;
    if (_popupUtil!=NULL) {
        if (_popupUtil->getFixedWidth()!=0) {
            max = _popupUtil->getFixedWidth();
            max += _popupUtil->getMargin()*2;
            if (max < PositionablePopupUtil::MIN_SIZE) {  // don't let item disappear
                _popupUtil->setFixedWidth(PositionablePopupUtil::MIN_SIZE);
                max = PositionablePopupUtil::MIN_SIZE;
            }
        } else {
            max = size().width();
            /*
            if(_popupUtil->_textComponent instanceof javax.swing.JTextField) {
                javax.swing.JTextField text = (javax.swing.JTextField)_popupUtil->_textComponent;
                max = getFontMetrics(text.getFont()).stringWidth(text.getText());
            } */
            max += _popupUtil->getMargin()*2;
            if (max < PositionablePopupUtil::MIN_SIZE) {  // don't let item disappear
                max = PositionablePopupUtil::MIN_SIZE;
            }
        }
    }
    if (debug) log->debug("maxWidth= "+QString::number(max)+" preferred width= "+QString::number(size().width()));
    return max;
}

/*public*/ int PositionableJPanel::maxHeight() {
    int max = 0;
    if (_popupUtil!=NULL) {
        if (_popupUtil->getFixedHeight()!=0) {
            max = _popupUtil->getFixedHeight();
            max += _popupUtil->getMargin()*2;
            if (max < PositionablePopupUtil::MIN_SIZE) {   // don't let item disappear
                _popupUtil->setFixedHeight(PositionablePopupUtil::MIN_SIZE);
                max = PositionablePopupUtil::MIN_SIZE;
            }
        } else {
            max = size().height();
            /*
            if(_popupUtil->_textComponent!=NULL) {
                max = getFontMetrics(_popupUtil->_textComponent.getFont()).getHeight();
            }  */
            if (_popupUtil!=NULL) {
                max += _popupUtil->getMargin()*2;
            }
            if (max < PositionablePopupUtil::MIN_SIZE) {  // don't let item disappear
                max = PositionablePopupUtil::MIN_SIZE;
            }
        }
    }
    if (debug) log->debug("maxHeight= "+QString::number(max)+" preferred height= "+QString::number(size().height()));
    return max;
}

/*public*/ NamedBean* getNamedBean() { return NULL; }

void PositionableJPanel::setSize(int w, int h)
{
 resize(w, h);

}
void PositionableJPanel::setName(QString name){ this->name = name;}
QString PositionableJPanel::getName() {return name;}
//void PositionableJPanel::setLocation(int x, int y)
//{
// _x = x;
// _y = y;
//}
bool PositionableJPanel::isOpaque() {return _bOpaque;}
/**
 * Stores the bounds of this component into "return value"
 * <code>rv</code> and returns <code>rv</code>.
 * If <code>rv</code> is <code>null</code> a new <code>Rectangle</code>
 * is allocated.  This version of <code>getBounds</code> is useful
 * if the caller wants to avoid allocating a new <code>Rectangle</code>
 * object on the heap.
 *
 * @param rv the return value, modified to the component's bounds
 * @return <code>rv</code>; if <code>rv</code> is <code>null</code>
 *          return a newly created <code>Rectangle</code> with this
 *          component's bounds
 */
///*public*/ QRect PositionableJPanel::getBounds(QRect rv) {
//    if (rv.isNull()) {
//        return  QRect(_x, _y, size().width(), size().height());
//    }
//    else {
//        rv.setCoords(_x, _y, size().width(), size().height());
//        return rv;
//    }
//}

QRectF PositionableJPanel::getBounds(QRectF r)
{
 if(r.isNull())
  return QRectF(getX(), getY(), /*getWidth()*/_itemGroup->boundingRect().width(), /*getHeight()*/_itemGroup->boundingRect().height());
    //return QRectF(getX(), getY(), _itemGroup->boundingRect().width(), _itemGroup->boundingRect().height());

 r.setCoords(getX(), getY(), getWidth(), getHeight());
 return r;
}

bool PositionableJPanel::updateScene() // TODO: this function not in Java
{
 MyGraphicsProxyWidget* item = NULL;
 if(widget == NULL) return false;
 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<MyGraphicsProxyWidget*>(it) != NULL)
   {
    item = qgraphicsitem_cast<MyGraphicsProxyWidget*>(it);
   }
  }
 }
 else
  _itemGroup = new QGraphicsItemGroup();

 if(item == NULL)
 {
  item = widget;
  _itemGroup->addToGroup(widget);
 }
 //item->setPos(getX(), getY());
 if(showTooltip()) item->setToolTip(getTooltip());
 //_itemGroup->addToGroup(item);
 item->setPos(getX(), getY());
 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 if((getDegrees()) != 0)
 {
  //l->item->rotate(l->getDegrees());
  QRectF bnd = _itemGroup->boundingRect();
  QPointF center = bnd.center();
  _itemGroup->setTransformOriginPoint(center);
  _itemGroup->setRotation(item->rotation());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
