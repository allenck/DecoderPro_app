#include "positionablelabel.h"
#include "editor.h"
#include "positionablepopuputil.h"
#include "coordinateedit.h"
#include <QDir>
#include "layouteditor.h"
//#include "itempalette.h"
#include "itempalette.h"
#include "iconadder.h"
#include "loggerfactory.h"
#include "displayframe.h"
#include "itempanel.h"
#include "fileutil.h"

PositionableLabel::PositionableLabel(Positionable *parent) :
    JLabel((QWidget*)parent)
{
 common(parent);
}
/**
 * PositionableLabel is a JLabel that can be dragged around the
 * inside of the enclosing Container using a right-drag.
 * <P>
 * The positionable parameter is a global, set from outside.
 * The 'fixed' parameter is local, set from the popup here.
 *
 * @author Bob Jacobsen Copyright (c) 2002
 * @version $Revision: 22576 $
 */

///*public*/ class PositionableLabel extends JLabel implements Positionable {

//    /*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");


/*public*/ PositionableLabel::PositionableLabel(QString s, Editor* editor, Positionable* parent)
 : JLabel(s, editor)
{
 common(parent);
 //super(s);
 _editor = editor;

 //if(editor != NULL)
  //Q_ASSERT(qobject_cast<Editor*>(editor)!= NULL);
 _text = true;
 _unRotatedText = s;
 //debug = log->isDebugEnabled();
 debug = false;
 if (debug) log->debug("PositionableLabel ctor (text) "+s);
 setHorizontalAlignment(JLabel::CENTER);
 setVerticalAlignment(JLabel::CENTER);
 //setPopupUtility(new PositionablePopupUtil(this, this));
// setToolTip("Positionable Label");
 QTimer::singleShot(100,  this, SLOT(initAfter()));
 setObjectName("positionableLabel");
}

/*public*/ PositionableLabel::PositionableLabel(NamedIcon* s, Editor* editor, Positionable *parent)
 : JLabel(s,editor)
{
 //super(s);
 common(parent);
 _editor = editor;
 if(editor != NULL)
  Q_ASSERT(qobject_cast<Editor*>(editor)!= NULL);
 _icon = true;
 _namedIcon = s;
 currRotation = s->getRotation();
 debug = log->isDebugEnabled();
//    if (debug) log->debug(tr("PositionableLabel ctor (icon) ")+s->name());

// setPopupUtility(new PositionablePopupUtil((Positionable*)this->parent, (JComponent*)this));
// setToolTip("Positionable Label");
 QTimer::singleShot(100,  this, SLOT(initAfter()));
}

void PositionableLabel::common(Positionable* parent)
{
 if(parent == NULL)
  this->parent = (Positionable*)this;
 else
  this->parent = parent;
 debug = false;
 _icon = false;
 _text = false;
 _control = false;
 _namedIcon = nullptr;
 _foreground = QColor(Qt::white);
 _background = QColor(Qt::transparent);
 _preferredSize = QSize(10,20);  // TODO:
 _itemGroup = new MyGraphicsItemGroup();
 _tooltip = "";
 _showTooltip =true;
  _editable = true;
  _positionable = true;
  _viewCoordinates = true;
 _controlling = true;
 _hidden = false;
 _bVisible = true;
 _displayLevel = 0;
 JLabel::setVisible(false); // set_bVisible underlying widget not visiable
 active = true;
 _saveOpaque = false;
 _unRotatedText = "";
 _rotateText = false; // was false
 _popupUtil = NULL;
 //_font = QFont("Arial", 10, QFont::Bold, false);
 _iconEditor = NULL;
 _iconEditorFrame = NULL;
 _icon = false;

 //item = NULL;
 IS_OPAQUE = false;
 needsRotate = false;
 _degrees = 0;
}

/*public*/ void PositionableLabel::initAfter()
{
 if(!_popupUtil)
  setPopupUtility(new PositionablePopupUtil(this, this));
 setToolTip("Positionable Label");
}

/*public*/ /*final*/ bool PositionableLabel::isIcon() { return _icon; }
/*public*/ /*final*/ bool PositionableLabel::isText() { return _text; }
/*public*/ /*final*/ bool PositionableLabel::isControl() { return _control; }

/*public*/ Editor* PositionableLabel::getEditor(){
    return _editor;
}

/*public*/ void PositionableLabel::setEditor(Editor* ed)
{
 _editor = ed;
}

/***************** Positionable methods **********************/

/*public*/ void PositionableLabel::setPositionable(bool enabled) { _positionable = enabled; }
/*public*/ /*final*/ bool PositionableLabel::isPositionable() { return _positionable; }

/*public*/ void PositionableLabel::setEditable(bool enabled) {
    _editable = enabled;
    showHidden();
}
/*public*/ bool PositionableLabel::isEditable() { return _editable; }

/*public*/ void PositionableLabel::setViewCoordinates(bool enabled) { _viewCoordinates = enabled; }
/*public*/ bool PositionableLabel::getViewCoordinates() { return _viewCoordinates; }

/*public*/ void PositionableLabel::setControlling(bool enabled) {_controlling = enabled;}
/*public*/ bool PositionableLabel::isControlling() { return _controlling; }

/*public*/ void PositionableLabel::setHidden(bool hide) {
    _hidden = hide;
    showHidden();
}
/*public*/ bool PositionableLabel::isHidden() { return _hidden;  }
/*public*/ void PositionableLabel::showHidden()
{
 if(!_hidden || _editor->isEditable())
 {
  //setVisible(true);
  _bVisible = true;
 }
 else
 {
  //setVisible(false);
  _bVisible = false;
 }
}
/**
* Delayed setDisplayLevel for DnD
*/
/*public*/ void PositionableLabel::setLevel(int l)
{
 _displayLevel = l;
}
/*public*/ void PositionableLabel::setDisplayLevel(int l)
{
 int oldDisplayLevel = _displayLevel;
 _displayLevel = l;
 if (oldDisplayLevel!=l)
 {
  if (debug) log->debug("Changing label display level from "+QString("%1").arg(oldDisplayLevel)+" to "+QString("%1").arg(_displayLevel));
  _editor->displayLevelChange((Positionable*)this);
 }
}
/*public*/ int PositionableLabel::getDisplayLevel() {
if(_displayLevel < 0 || _displayLevel > Editor::NUM_LEVELS)
 return Editor::TEMP;
return _displayLevel; }

/*public*/ void PositionableLabel::setShowToolTip(bool set)
{
 _showTooltip = set;
}
/*public*/ bool PositionableLabel::showToolTip()
{
 return _showTooltip;
}
/*public*/ void PositionableLabel::setToolTip(QString tip)
{
 _tooltip = tip;
 //setToolTip(tip);
}
/*public*/ QString PositionableLabel::getToolTip()
{
 return _tooltip;
}

/*public*/ QString PositionableLabel::getNameString()
{
 if (_icon && _displayLevel >Editor::BKG) return "Icon";
 else if (_text) return "Text Label";
 else return "Background";
}

/*public*/ Positionable* PositionableLabel::deepClone()
{
 PositionableLabel* pos;
 if (_icon)
 {
  NamedIcon* icon = new NamedIcon((NamedIcon*)getIcon());
     pos = new PositionableLabel(icon, _editor);
 } else {
     pos = new PositionableLabel(getText(), _editor);
 }
 return finishClone(pos);
}

/**
 * When text is rotated or in an icon mode, the return of getText() may be
 * NULL or some other value
 * @return original defining text set by user
 */
/*public*/ QString PositionableLabel::getUnRotatedText() {
    return _unRotatedText;
}

/*public*/ Positionable* PositionableLabel::finishClone(Positionable* p)
{
 PositionableLabel* pos = (PositionableLabel*)p;
 pos->_text = _text;
 pos->_icon = _icon;
 pos->_control = _control;
 //pos->_rotateText = _rotateText;
 pos->_unRotatedText = _unRotatedText;
 pos->setLocation(getX(), getY());
 pos->_displayLevel = _displayLevel;
 pos->_controlling = _controlling;
 pos->_hidden = _hidden;
 pos->_positionable = _positionable;
 pos->_showTooltip =_showTooltip;
 pos->setToolTip(getToolTip());
 pos->_editable = _editable;
 if (pos->getPopupUtility()==NULL)
 {
    pos->setPopupUtility(NULL);
 } else {
    pos->setPopupUtility(getPopupUtility()->clone(pos,   pos->getTextComponent()));
 }
 pos->setOpaque(isOpaque());
 pos->_saveOpaque = _saveOpaque;
 if ( _namedIcon!=NULL) {
  pos->_namedIcon = cloneIcon(_namedIcon, pos);
  pos->_namedIcon = cloneIcon(_namedIcon, pos);
  pos->setIcon(_namedIcon);
 }
 pos->updateSize();
 return pos;
}

/*public*/ JComponent* PositionableLabel::getTextComponent()
{
 return (JComponent*)this;
}

/*protected*/ NamedIcon* PositionableLabel::cloneIcon(NamedIcon* icon, PositionableLabel* pos)
{
 if (icon !=NULL && icon->getURL()!=NULL)
 {
  return new NamedIcon(icon, pos, this);
 }
 else
 {
  NamedIcon* clone = new NamedIcon(icon->getImage());
  clone->scale(icon->getScale(), pos);
  clone->rotate(icon->getDegrees(), pos);
  return clone;
 }
}

//    // overide where used - e.g. momentary
/*public*/ void PositionableLabel::doMousePressed(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseReleased(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseClicked(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseDragged(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseMoved(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseEntered(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void PositionableLabel::doMouseExited(QGraphicsSceneMouseEvent* /*event*/) {}

/*public*/ bool PositionableLabel::storeItem() {
    return true;
}
/*public*/ bool PositionableLabel::doViemMenu() {
    return true;
}

/**************** end Positionable methods **********************/
/****************************************************************/

/*public*/ void PositionableLabel::setPopupUtility(PositionablePopupUtil* tu)
{
 _popupUtil = tu;
}

/*public*/ PositionablePopupUtil* PositionableLabel::getPopupUtility()
{
 if(!_popupUtil)
  initAfter();
 return _popupUtil;
}
/**
 * Update the AWT and Swing size information due to change in internal
 * state, e.g. if one or more of the icons that might be displayed
 * is changed
 */
/*public*/ void PositionableLabel::updateSize()
{
 if (debug)
 {
  log->debug(tr("updateSize() w= ")+QString("%1").arg(maxWidth())+", h= "+QString("%1").arg(maxHeight())+" _namedIcon= "+(_namedIcon!=NULL?_namedIcon->getName():"none"));
 }

 setSize(maxWidth(), maxHeight());
 if ( _namedIcon!=NULL && _text)
 {
  //we have a combined icon/text therefore the icon is central to the text.
  setHorizontalTextPosition(CENTER);
 }
}

/*public*/ int PositionableLabel::maxWidth()
{
 if(_rotateText && _namedIcon!=NULL)
 {
  return _namedIcon->getIconWidth();
 }
 if(_popupUtil==NULL)
 {
  return maxWidthTrue();
 }

 switch (_popupUtil->getOrientation())
 {
  case PositionablePopupUtil::VERTICAL_DOWN:
  case PositionablePopupUtil::VERTICAL_UP:
   return maxHeightTrue();
  default:
   return maxWidthTrue();
 }
}


/*public*/ int PositionableLabel::maxHeight()
{
 if(!_rotateText && _namedIcon!=NULL)
 {
  return _namedIcon->getIconHeight();
 }
 if(_popupUtil==NULL)
 {
  return maxHeightTrue();
 }
 switch (_popupUtil->getOrientation())
 {
  case PositionablePopupUtil::VERTICAL_DOWN:
  case PositionablePopupUtil::VERTICAL_UP:
   return maxWidthTrue();
  default:
   return maxHeightTrue();
 }
}

/*public*/ int PositionableLabel::maxWidthTrue()
{
 int result = 0;
 if (_popupUtil!=NULL && _popupUtil->getFixedWidth()!=0)
 {
  result = _popupUtil->getFixedWidth();
  result += _popupUtil->getBorderSize()*2;
  if (result < PositionablePopupUtil::MIN_SIZE)
  {  // don't let item disappear
   _popupUtil->setFixedWidth(PositionablePopupUtil::MIN_SIZE);
   result = PositionablePopupUtil::MIN_SIZE;
  }
 }
 else
 {
  if(_text && getText()!="")
  {
   if (getText().trimmed().length()==0)
   {
    // show width of 1 blank character
    //if (this->getFont()!=NULL)
    {

     //max = getFontMetrics(getFont()).stringWidth("0");
     result = QFontMetrics(getFont()).width("0");
    }
   }
   else
   {
    //max = getFontMetrics(getFont()).stringWidth(getText());
    result = QFontMetrics(getFont()).width(getText());
   }
  }
  if(_icon && _namedIcon!=NULL)
  {
   result = qMax(_namedIcon->getIconWidth(), result);
  }
  if (_text && _popupUtil!=NULL)
  {
   result += _popupUtil->getMargin()*2;
   result += _popupUtil->getBorderSize()*2;
  }
  if (result < PositionablePopupUtil::MIN_SIZE)
  {  // don't let item disappear
    result = PositionablePopupUtil::MIN_SIZE;
  }
 }
// if (debug) log->debug("maxWidth= "+QString("%1").arg(max)+" preferred width= "+QString("%1").arg(getPreferredSize().width()));
  return result;
}

/*public*/ int PositionableLabel::maxHeightTrue()
{
 int max = 0;
 if (_popupUtil!=NULL && _popupUtil->getFixedHeight()!=0)
 {
  max = _popupUtil->getFixedHeight();
  max += _popupUtil->getBorderSize()*2;
  if (max < PositionablePopupUtil::MIN_SIZE)
  {   // don't let item disappear
   _popupUtil->setFixedHeight(PositionablePopupUtil::MIN_SIZE);
  }
 }
 else
 {
  if(_text)
  {
   if(_text && getText()!=NULL /*&& getFont()!=NULL*/)
   {
    //max = getFontMetrics(getFont()).getHeight();
    max = QFontMetrics(getFont()).height();
   }
   if(_icon && _namedIcon!=NULL)
   {
    max = qMax(_namedIcon->getIconHeight(), max);
   }
   if (_text && _popupUtil!=NULL)
   {
    max += _popupUtil->getMargin()*2;
    max += _popupUtil->getBorderSize()*2;
   }
   if (max < PositionablePopupUtil::MIN_SIZE)
   {  // don't let item disappear
    max = PositionablePopupUtil::MIN_SIZE;
   }
  }
 }
// if (debug) log->debug("maxHeight= "+QString("%1").arg(max)+" preferred height= "+QString("%1").arg(getPreferredSize().height()));
 if (max < 1) max = PositionablePopupUtil::MIN_SIZE;
 return max;
}

/*public*/ bool PositionableLabel::isBackground() { return (_displayLevel == Editor::BKG);
}
/*public*/ bool PositionableLabel::isRotated() {
 return _rotateText;
}

/*public*/ void PositionableLabel::updateIcon(NamedIcon* s)
{
 _namedIcon = s;
 JLabel::setIcon(_namedIcon);
 updateSize();
 if(_itemGroup != NULL)
  updateScene();
}

/******* Methods to add menu items to popup ********/

/**
*  Call to a Positionable that has unique requirements
* - e.g. RpsPositionIcon, SecurityElementIcon
*/
/*public*/ bool PositionableLabel::showPopUp(QMenu* /*popup*/)
{
 return false;
}

/**
* Rotate othogonally
* return true if popup is set
*/
/*public*/ bool PositionableLabel::setRotateOrthogonalMenu(QMenu* popup)
{

 if (isIcon() && _displayLevel > Editor::BKG)
 {
//    popup.add(new AbstractAction(Bundle.getMessage("Rotate")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            rotateOrthogonal();
//        }
//    });
  QAction* rotateAction = new QAction(tr("Rotate (Orthogonal)"),this);
  popup->addAction(rotateAction);
  connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateOrthogonal()));
  return true;
 }
 return false;
}
/*protected*/ void PositionableLabel::rotateOrthogonal()
{
 _namedIcon->setRotation(_namedIcon->getRotation()+1, this);
 setIcon(_namedIcon);
 updateSize();
    //repaint();

    // TODO: just repaint this label instead of entire scene.
  if(qobject_cast<LayoutEditor*>(_editor)!=NULL)
  {
   LayoutEditor* myLayoutEditor = (LayoutEditor*)_editor;
   myLayoutEditor->paintTargetPanel(myLayoutEditor->getScene());
  }
  _editor->addToTarget((Positionable*)this);
}

/*public*/ void PositionableLabel::finishItemUpdate(DisplayFrame* paletteFrame, ItemPanel* itemPanel) {
    itemPanel->closeDialogs();
    paletteFrame->dispose();
    //invalidate();
    update();
}

/*public*/ bool PositionableLabel::setEditItemMenu(QMenu* popup)
{
 return setEditIconMenu(popup);
}
/*public*/ bool PositionableLabel::setEditIconMenu(QMenu* popup)
{
 if (_icon && !_text)
 {
//  QString txt = java.text.MessageFormat.format(Bundle.getMessage("EditItem") Bundle.getMessage("Icon"));
  QString txt = tr("Edit %1 Icon").arg(tr("Icon"));
//        popup.add(new AbstractAction(txt) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    edit();
//                }
//            });
  QAction* editAction = new QAction(txt, this) ;
  popup->addAction(editAction);
  connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));
  return true;
 }
 return false;
}

/**
 * For item popups in Panel Editor
 */
/*protected*/ void PositionableLabel::makeIconEditorFrame(QObject* /*pos*/, QString name, bool table, /*AddPanelIconDialog*/IconAdder* editor)
{
 if (editor!=NULL)
 {
  _iconEditor = editor;
 }
 else
 {
  _iconEditor = new IconAdder(name);
 }
 _iconEditorFrame = _editor->makeAddIconFrame(name, false, table, _iconEditor);
//    _iconEditorFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                _iconEditorFrame.dispose();
//                _iconEditorFrame = NULL;
//            }
//        });
 IEFWindowListener* windowListener = new IEFWindowListener(this);
 _iconEditorFrame->addWindowListener(windowListener);

// _iconEditorFrame->setLocationRelativeTo(pos);
 _iconEditorFrame->toFront();
 _iconEditorFrame->setVisible(true);
}
IEFWindowListener::IEFWindowListener(PositionableLabel *l)
{
 this->l = l;
}
void IEFWindowListener::windowClosing(QCloseEvent */*e*/)
{
 if(l->_iconEditor != NULL)
 {
  l->_iconEditor->dispose();
  l->_iconEditor = NULL;
 }
 if(l->_iconEditorFrame != NULL)
 {
  l->_iconEditorFrame->dispose();
  l->_iconEditorFrame = NULL;
 }
}

/*protected*/ void PositionableLabel::edit()
{
 makeIconEditorFrame(this, "Icon", false, NULL);
 _iconEditorFrame->setMinimumHeight(250);
 NamedIcon* icon = new NamedIcon(_namedIcon);
 _iconEditor->setIcon(0, "plainIcon", icon);
 _iconEditor->makeIconPanel(false);

//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editIcon();
//        }
//    };
 AddIconActionListener* addIconAction = new AddIconActionListener(this);
 _iconEditor->complete(addIconAction, true, false, true);
 _iconEditorFrame->pack();
}

/*protected*/ void PositionableLabel::editIcon()
{
 QString url = _iconEditor->getIcon("plainIcon")->getURL();
 _namedIcon = NamedIcon::getIconByName(url);
 setIcon(_namedIcon);
 updateSize();
 _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
// invalidate();
 updateScene();
 _itemGroup->setName(getGroupName());
}


/************ Methods for Item Popups in Control Panel editor ********************/
/**
 * For item popups in Control Panel Editor
 */
/*protected*/ DisplayFrame *PositionableLabel::makePaletteFrame(QString title)
{
 ItemPalette::loadIcons(_editor);

 _paletteFrame = new DisplayFrame(title, false, false);
//    _paletteFrame->setLocationRelativeTo(this);
 _paletteFrame->toFront();
//    _paletteFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            ImageIndexEditor.checkImageIndex();   // write maps to tree
//            }
//    });
 return _paletteFrame;
}

/**
* Rotate degrees
* return true if popup is set
*/
/*public*/ bool PositionableLabel::setRotateMenu(QMenu* popup)
{
 if (_displayLevel > Editor::BKG)
 {
  //CoordinateEdit edit;
  QAction* act = CoordinateEdit::getRotateEditAction((Positionable*)this, (CoordinateEdit*)this);
  popup->addAction(act);
  return true;
 }
 return false;
}

/**
* Scale percentage
* return true if popup is set
*/
/*public*/ bool PositionableLabel::setScaleMenu(QMenu* popup)
{
 if (isIcon() && _displayLevel > Editor::BKG)
 {
  CoordinateEdit edit;
  popup->addAction(CoordinateEdit::getScaleEditAction((Positionable*)this, &edit));
  return true;
 }
 return false;
}


/*public*/ bool PositionableLabel::setTextEditMenu(QMenu* popup)
{
 if (isText())
 {
  CoordinateEdit* edit=nullptr;
  popup->addAction(CoordinateEdit::getTextEditAction((Positionable*)this, "EditText", edit));
  return true;
 }
 return false;
}
#if 1 // TODO:
//JCheckBoxMenuItem disableItem = NULL;
/*public*/ bool PositionableLabel::setDisableControlMenu(QMenu* popup)
{
 if (_control)
 {
  QAction* disableItem = new QAction(tr("Disable"), this);
  disableItem->setCheckable(true);
  disableItem->setChecked(!_controlling);
  popup->addAction(disableItem);
//        disableItem.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                setControlling(!disableItem.isSelected());
//            }
//        });
  connect(disableItem, SIGNAL(toggled(bool)), this, SLOT(on_disableControlMenu_toggled(bool)));
  return true;
 }
 return false;
}
#endif
void PositionableLabel::on_disableControlMenu_toggled(bool bState) // [slot]
{
  setControlling(!bState);
}

/*public*/ void PositionableLabel::setScale(double s) {
    if (_namedIcon!=NULL) {
        _namedIcon->scale(s, this);
        setIcon(_namedIcon);
        updateSize();
    }
}
/*public*/ double PositionableLabel::getScale() {
    if (_namedIcon==NULL) {
        return 1.0;
    }
    return ((NamedIcon*)getIcon())->getScale();
}

/*public*/ void PositionableLabel::saveOpaque(bool set) {
    _saveOpaque =set;
}
/*public*/ bool PositionableLabel::getSaveOpaque() {
    return _saveOpaque;
}

/*public*/ void PositionableLabel::rotate(int deg)
{
 _degrees = deg;
 if (_rotateText)
 {
  if (deg==0)
  {
   // restore unrotated whatever
   _rotateText = false;
   if (_text && _icon)
   {	// restore horizontal icon and its text
    QString url = _namedIcon->getURL();
    _namedIcon = new NamedIcon(url, url);
    JLabel::setText(_unRotatedText);
    setIcon(new NamedIcon(url, url));
   }
   else if (_text)
   {		// restore original text as a label
    setIcon(NULL);
    _namedIcon = NULL;
    JLabel::setText(_unRotatedText);
    setOpaque(_saveOpaque);
    _popupUtil->setBorder(true);
   }
   else
   {
    _namedIcon->rotate(deg, this);
    setIcon(_namedIcon);
   }
  } else
  {
   setOpaque(_saveOpaque);
   if (_text & _icon)
   {	// update text over icon
    _namedIcon = makeTextOverlaidIcon(_unRotatedText, _namedIcon);
   } else if (_text)
   {		// update text only icon image
    _namedIcon = makeTextIcon(_unRotatedText);
   }
   _namedIcon->rotate(deg, this);
   setIcon(_namedIcon);
   setOpaque(false);
  }
 }
#if 1
 else
 {
  if (deg!=0)
  {	// first time text or icon is rotated from horizontal
   if (_text && _icon)
   {	// text overlays icon  e.g. LocoIcon
    _namedIcon = makeTextOverlaidIcon(_unRotatedText, _namedIcon);
    JLabel::setText(NULL);
    _rotateText = true;
   }
   else if (_text)
   {
    _saveOpaque = isOpaque();
    _namedIcon = makeTextIcon(_unRotatedText);
    JLabel::setText(NULL);
    _rotateText = true;
    setOpaque(false);
    _popupUtil->setBorder(false);
   }
   _namedIcon->rotate(deg, this);
   setIcon(_namedIcon);
  }
  else if (_namedIcon!=NULL)
  {
   _namedIcon->rotate(deg, this);
   setIcon(_namedIcon);
  }
 }
#endif
 updateSize();
}

/**
 * Create an image of icon with text overlaid
 */
/*protected*/ NamedIcon* PositionableLabel::makeTextOverlaidIcon(QString text, NamedIcon* ic)
{
    //QString url = ic->getURL();
 NamedIcon* icon = NULL;
//        int textWidth = getFontMetrics(getFont()).stringWidth(text);
//        int iconWidth = icon.getIconWidth();
//        int textHeight = getFontMetrics(getFont()).getHeight();
//        int iconHeight = icon.getIconHeight();

//        int width = Math.max(textWidth, iconWidth);
//        int height = Math.max(textHeight, iconHeight);
//        int hOffset = Math.max((textWidth-iconWidth)/2, 0);
//        int vOffset = Math.max((textHeight-iconHeight)/2, 0);

//        BufferedImage bufIm = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
//        Graphics2D g2d = bufIm.createGraphics();
//        g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
//                             RenderingHints.VALUE_RENDER_QUALITY);
//        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
//                             RenderingHints.VALUE_ANTIALIAS_ON);
//        g2d.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
//                             RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
//        g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
//                             RenderingHints.VALUE_INTERPOLATION_BICUBIC);

//        g2d.drawImage(icon.getImage(), AffineTransform.getTranslateInstance(hOffset, vOffset), this);

//        g2d.setFont(getFont());
//        hOffset = Math.max((iconWidth-textWidth)/2, 0);
//        vOffset = Math.max((iconHeight-textHeight)/2, 0) + getFontMetrics(getFont()).getAscent();
//        g2d.setColor(getForeground());
//        g2d.drawQString(text, hOffset, vOffset);

//        icon = new NamedIcon(bufIm);
//        g2d.dispose();
//        icon.setURL(url);
    QBrush brBkgnd = QBrush(Qt::SolidPattern);
    QFont f;
    QString mUrl = ic->getURL();
    QString fn = FileUtil::getAbsoluteFilename(mUrl);
    QImage image = QImage(fn);
    QSize resultSize = QSize(image.size());
    QImage resultImage = QImage(resultSize,QImage::Format_ARGB32_Premultiplied);
    QRect r = QRect(image.rect());

    QPainter painter(&resultImage);
    //painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.drawImage(0, 0, image);
    QRgb color = image.pixel(10,10);

    brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
    f =  QFont("Arial", 10, QFont::Bold, false);
    painter.setFont(f);

    QRect eRect =painter.boundingRect(r, Qt::AlignCenter, text);
    //eRect.adjust(0, -3.0, 0, 0);
    //painter.fillRect(eRect, brBkgnd);
    QRectF bRect = painter.boundingRect(r, Qt::AlignCenter, text); // bounding rectangle of text
    //bRect.adjust(0, -3.0, 0, 0);
    //painter.fillRect(bRect, brBkgnd);
    painter.setPen(QPen(getForeground()));
    painter.drawText(bRect, Qt::AlignCenter, text);
    painter.end();
    icon = new NamedIcon(resultImage);
    resultImage.save(QDir::homePath()+ "/test.png","PNG");
    return icon;
}
    /**
     * create a text image whose bit map can be rotated
     * @param text
     * @return
     */
/*private*/ NamedIcon* PositionableLabel::makeTextIcon(QString text)
{
//    int width = getFontMetrics(getFont()).stringWidth(text);
 int width = QFontMetrics(getFont()).width(text);
//    int height = getFontMetrics(getFont()).getHeight();
 int height = QFontMetrics(getFont()).height();
 int hOffset = 0;
//    int vOffset = getFontMetrics(getFont2()).getAscent();
 int vOffset = QFontMetrics(getFont()).ascent();
 if (_popupUtil!=NULL)
 {
  if (_popupUtil->getFixedWidth()!=0)
  {
   switch (_popupUtil->getJustification())
   {
   case PositionablePopupUtil::LEFT:
    hOffset = _popupUtil->getBorderSize();
    break;
   case PositionablePopupUtil::RIGHT:
    hOffset = _popupUtil->getFixedWidth()-width;
    hOffset += _popupUtil->getBorderSize();
    break;
   default:
    hOffset = qMax((_popupUtil->getFixedWidth()-width)/2, 0);
    hOffset += _popupUtil->getBorderSize();
    break;
   }
   width = _popupUtil->getFixedWidth() + 2*_popupUtil->getBorderSize();
  }
  else
  {
   width += 2*(_popupUtil->getMargin() +  _popupUtil->getBorderSize());
   hOffset += _popupUtil->getMargin() + _popupUtil->getBorderSize();
  }
  if (_popupUtil->getFixedHeight()!=0)
  {
   vOffset = qMax(vOffset+(_popupUtil->getFixedHeight()-height)/2, 0);
   vOffset += _popupUtil->getBorderSize();
   height = _popupUtil->getFixedHeight() + 2*_popupUtil->getBorderSize();
  }
  else
  {
   height += 2*(_popupUtil->getMargin() + _popupUtil->getBorderSize());
   vOffset += _popupUtil->getMargin() +  _popupUtil->getBorderSize();
  }
 }
//    BufferedImage bufIm = new BufferedImage(width+2, height+2, BufferedImage.TYPE_INT_ARGB);
 QSize resultSize = QSize(width+2, height+2);
 QImage resultImage = QImage(resultSize,QImage::Format_ARGB32_Premultiplied);
 QRect r = QRect(resultImage.rect());

 QPainter painter(&resultImage);
 painter.setFont(getFont());
//    Graphics2D g2d = bufIm.createGraphics();
//    g2d.setFont(getFont());
//    g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
//                         RenderingHints.VALUE_RENDER_QUALITY);
//    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
//                         RenderingHints.VALUE_ANTIALIAS_ON);
//    g2d.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
//                         RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
//    g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
//                         RenderingHints.VALUE_INTERPOLATION_BICUBIC);
 QBrush brBkgnd = QBrush(Qt::SolidPattern);

 if (_popupUtil!=NULL)
 {
  if (!isOpaque() && _popupUtil->getBackground().isValid())
  {
   //g2d.setColor(_popupUtil->getBackground());
   brBkgnd = QBrush(_popupUtil->getBackground(), Qt::SolidPattern);
   //g2d.fillRect(0, 0, width, height);
   QRect eRect = QRect(0,0, width, height );
   painter.fillRect(eRect, brBkgnd);
  }
  else
   painter.fillRect(resultImage.rect(), Qt::transparent);

  if (_popupUtil->getBorderSize()!=0)
  {
   //g2d.setColor(_popupUtil.getBorderColor());
   QPen pen = QPen(_popupUtil->getBorderColor());
   //g2d.setStroke(new java.awt.BasicStroke(2*_popupUtil->getBorderSize()));
   //g2d.drawRect(0, 0, width, height);
   painter.setPen(pen);
   painter.drawRect(QRect(0,0, width,height));
  }
 }
// g2d.setColor(getForeground());
// g2d.drawString(text, hOffset, vOffset);
 QRectF bRect = painter.boundingRect(r, Qt::AlignCenter, text); // bounding rectangle of text
 painter.fillRect(bRect, brBkgnd);
 painter.setPen(getForeground());
 painter.drawText(bRect, Qt::AlignCenter, text);
 painter.end();

 NamedIcon* icon = new NamedIcon(resultImage);
 //dispose();
 resultImage.save(QDir::homePath()+ "/testtext.png","PNG");
 return icon;
}

/*public*/ void PositionableLabel::setDegrees(int deg)
{
 _degrees = deg;
}

/*public*/ int PositionableLabel::getDegrees()
{
 return _degrees;
}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
/*public*/ void PositionableLabel::dispose() {
}

/**
 * Removes this object from display and persistance
 */
/*public*/ void PositionableLabel::remove() {
    _editor->removeFromContents((Positionable*)this);
    // remove from persistance by flagging inactive
    active = false;
    dispose();
    deleteLater();
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool PositionableLabel::isActive() {
    return active;
}
bool PositionableLabel::isVisible()
{
 return _bVisible;
}
void PositionableLabel::setVisible(bool b)
{
 int iB = (int)b;
 Q_ASSERT(iB==0 || iB==1);
 _bVisible = b;
}

/*protected*/ void PositionableLabel::setSuperText(QString text) {
    _unRotatedText = text;
    JLabel::setText(text);
}
//@Override
/*public*/ void PositionableLabel::setText(QString text)
{
 if(text == _unRotatedText)
  return;
 _unRotatedText = text;
 if (_rotateText && _namedIcon!=NULL)
 {
  _namedIcon->rotate(_degrees, this);		//this will change text in icon
 }
 else
 {
  JLabel::setText(text);
 }
 if(isIcon())
 {
  //_namedIcon = makeTextOverlaidIcon(text, _namedIcon);
  _namedIcon->setImage(makeTextOverlaidIcon(text, _namedIcon)->getOriginalImage());
  makeTextIcon(text);
 }
}


//@Override
/*public*/ QSize PositionableLabel::getSize()
{
 if (!needsRotate)
 {
  //return getSize();
   return _size;
 }

 QSize size = getSize();
 if(_popupUtil==NULL)
 {
  //return super.getSize();
  return JLabel::size();
 }
 switch (_popupUtil->getOrientation())
 {
  case PositionablePopupUtil::VERTICAL_DOWN:
  case PositionablePopupUtil::VERTICAL_UP:
   return QSize(size.height(), size.width());
  default:
   return getSize();
 }
}

//@Override
/*public*/ int PositionableLabel::getHeight() {
    return getSize().height();
}

//@Override
/*public*/ int PositionableLabel::getWidth() {
    return getSize().width();
}
#if 0 // TODO:
    //@Override
    /*protected*/ void paintComponent(Graphics g) {
        if(_popupUtil==NULL){
            super.paintComponent(g);
        } else {
            Graphics2D gr = (Graphics2D) g.create();

            switch (_popupUtil.getOrientation()) {
            case PositionablePopupUtil.VERTICAL_UP:
            gr.translate(0, getSize().getHeight());
            gr.transform(AffineTransform.getQuadrantRotateInstance(-1));
            break;
            case PositionablePopupUtil.VERTICAL_DOWN:
            gr.transform(AffineTransform.getQuadrantRotateInstance(1));
            gr.translate(0, -getSize().getWidth());
            break;
            default:
            }

            needsRotate = true;
            super.paintComponent(gr);
            needsRotate = false;
        }
    }
#endif
/**
* Provides a generic method to return the bean associated with the Positionable
*/
/*public*/ NamedBean* PositionableLabel::getNamedBean() { return NULL; }

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionableLabel.class.getName());

//}

QFont PositionableLabel::getFont()
{
 _font = font();
 return _font;
}

void PositionableLabel::setFont(const QFont & font)
{
 _font = font;
 QLabel::setFont(_font);
}

bool PositionableLabel::updateScene() // TODO: this function not in Java
{
 QGraphicsPixmapItem* item = NULL;
 QGraphicsTextItem* itemText = NULL;
 QGraphicsRectItem* rItem = NULL;
 qreal itemRotation = 0;

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsPixmapItem*>(it) != NULL)
   {
    item = qgraphicsitem_cast<QGraphicsPixmapItem*>(it);
    itemRotation = item->rotation();
    //_itemGroup->setRotation(itemRotation - currRotation);
   }
   if(qgraphicsitem_cast<QGraphicsTextItem*>(it) != NULL)
    itemText = qgraphicsitem_cast<QGraphicsTextItem*>(it);
   if(qgraphicsitem_cast<QGraphicsRectItem*>(it) != NULL)
    rItem = qgraphicsitem_cast<QGraphicsRectItem*>(it);
  }
 }
 else
 {
  _itemGroup = new MyGraphicsItemGroup();
  _itemGroup->setName(getGroupName());
  currRotation = 0;
 }
 if(isIcon())
 {
  if(getIcon() == NULL) return false;

  QPixmap pixmap = QPixmap::fromImage(getIcon()->getImage());
  if(item != NULL)
   item->setPixmap(pixmap);
  else
   item = new QGraphicsPixmapItem(pixmap,_itemGroup);
  item->setScale(getScale());
  //item->setPos(getX(), getY());
  if(showToolTip()) item->setToolTip(getToolTip());
  //_itemGroup->addToGroup(item);
  _itemGroup->setPos(getX(), getY());
  if(_itemGroup->name() == "")
   _itemGroup->setName(getGroupName());
  //int degrees = getDegrees() + getIcon()->getRotation();
  currRotation = getIcon()->getRotation()*90;/*getDegrees();*/
  //if((getDegrees()+ currRotation) != 0)
  {
   //l->item->rotate(l->getDegrees());
   QRectF bnd = item->boundingRect();
   QPointF center = bnd.center();
   _itemGroup->setTransformOriginPoint(center);
   _itemGroup->setRotation(getDegrees() + currRotation);
  }
 }
 else
 { // text item
  if(itemText != NULL)
   itemText->setPlainText(getUnRotatedText());
  else
   itemText = new QGraphicsTextItem(getUnRotatedText());
  //itemText->setPos(getX(), getY());
  itemText->setFont(getFont());
  itemText->setDefaultTextColor(getForeground());
  if(showToolTip()) itemText->setToolTip(getToolTip());

  QRectF ir = itemText->boundingRect();
  int margin = getPopupUtility()->getMargin();
  QRectF r = QRectF(ir.x()-margin,ir.y()-margin,ir.right()+margin*2,ir.bottom()+margin*2);
  if(rItem != NULL)
   rItem->setRect(r);
  else
   rItem = new QGraphicsRectItem(r, _itemGroup);
  if(isOpaque())
   rItem->setBrush( QBrush(getBackground()));
  if(getPopupUtility()->getBorderSize() == 0)
   rItem->setPen(Qt::NoPen);
  else
   rItem->setPen(QPen(QBrush(getPopupUtility()->getBorderColor()),getPopupUtility()->getBorderSize()));
  //rItem->setPos(getX(), getY());
  _itemGroup->addToGroup(itemText);
  _itemGroup->setPos(((Positionable*)this)->getX(), ((Positionable*)this)->getY());
  if(_itemGroup->name() == "")
   _itemGroup->setName(getGroupName());
  if(getDegrees() != 0)
  {
   //l->item->rotate(l->getDegrees());
   QRectF bnd = rItem->boundingRect();
   QPointF center = bnd.center();
   _itemGroup->setTransformOriginPoint(center);
   _itemGroup->setRotation(/*_itemGroup->rotation() + */getDegrees());
  }
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}

void PositionableLabel::setIcon(NamedIcon* s)
{
// if(s != NULL && _itemGroup != NULL)
// {
//  //_degrees = s->getRotation();
//  //_itemGroup->setRotation(_itemGroup->rotation() - _namedIcon->getRotation());
//  currRotation = 0;
// }
// else
//  if(s == NULL)
//   if(log->isDebugEnabled()) log->debug("setIcon called with NULL icon");
 _namedIcon = s;
 JLabel::setIcon(s);
}

NamedIcon* PositionableLabel::getIcon() { return _namedIcon;}

void PositionableLabel::setForeground(QColor c)
{
 _foreground = c;
 QPalette pal = this->palette();
 pal.setColor(QPalette::WindowText,c);
 setPalette(pal);
}
QSize PositionableLabel::getPreferredSize()
{
 return _preferredSize;
}
void PositionableLabel::setSize(int w, int h)
{
 _size = QSize(w,h);
 JLabel::setSize(w,h);
}
/*public*/ void PositionableLabel::setOpaque(bool isOpaque)
{
 bool oldValue = /*getFlag*/(IS_OPAQUE);
//        setFlag(IS_OPAQUE, isOpaque);
 IS_OPAQUE= isOpaque;
//        setFlag(OPAQUE_SET, true);
 OPAQUE_SET = true;
 QColor c = getBackground();
 setBackground(QColor(c.red(), c.green(), c.blue(),0));
 //setStyleSheet(tr("background-color: rgba(%1,%2,%3,%4);").arg(c.red()).arg(c.green()).arg(c.blue()).arg(0));

// emit propertyChange(new PropertyChangeEvent(this, "opaque", oldValue, isOpaque));
// if(_itemGroup != NULL)
//  _itemGroup->update();
// _editor->addToTarget(this);
}

/*public*/ bool PositionableLabel::isOpaque()
{ return IS_OPAQUE;}
QColor PositionableLabel::getForeground()
{
 return _foreground;
}
void PositionableLabel::setBackgroundColor(QColor color)
{
  // TODO:
 _background = color;
// QPalette pal = QLabel::palette();
// pal.setColor(QPalette::Window, color);
// setPalette(pal);
// repaint();
}
QColor PositionableLabel::getBackground()
{
 return _background;
}

/*public*/ QRectF PositionableLabel::getBounds(QRectF r)
{
 if(r.isNull())
  return QRectF(((Positionable*)this)->getX(), ((Positionable*)this)->getY(), getWidth(), getHeight());
 else
 {
  r.setCoords(((Positionable*)this)->getX(), ((Positionable*)this)->getY(), getWidth(), getHeight());
  return  r;
 }
}
/* public*/ void PositionableLabel::setStyleSheet()
{
 QString ss = QString("QLabel {border: %1px solid rgb(%2, %3, %4);").arg(_popupUtil->getBorderSize()).arg(_popupUtil->getBorderColor().red()).arg(_popupUtil->getBorderColor().green()).arg(_popupUtil->getBorderColor().blue());
 if(isOpaque())
  ss.append(QString(" background-color: rgb(%1, %2, %3);").arg(_popupUtil->getBackground().red()).arg(_popupUtil->getBackground().green()).arg(_popupUtil->getBackground().blue()));
 ss.append(QString(" margin: %1px;").arg(_popupUtil->getMargin()));
 ss.append("}");
 QLabel::setStyleSheet( ss);
}

/**
 * Sets the background color of this component.  The background
 * color is used only if the component is opaque, and only
 * by subclasses of <code>JComponent</code> or
 * <code>ComponentUI</code> implementations.  Direct subclasses of
 * <code>JComponent</code> must override
 * <code>paintComponent</code> to honor this property.
 * <p>
 * It is up to the look and feel to honor this property, some may
 * choose to ignore it.
 *
 * @param bg the desired background <code>Color</code>
 * @see java.awt.Component#getBackground
 * @see #setOpaque
 *
 * @beaninfo
 *    preferred: true
 *        bound: true
 *    attribute: visualUpdate true
 *  description: The background color of the component.
 */
/*public*/ void PositionableLabel::setBackground(QColor bg) {
    QColor oldBg = getBackground();
#if 0
    //super.setBackground(bg);
    if ((oldBg != null) ? !oldBg.equals(bg) : ((bg != null) && !bg.equals(oldBg))) {
        // background already bound in AWT1.2
        repaint();
    }
#endif
    IS_OPAQUE = true;
    setBackgroundColor(bg);
}
QPointF PositionableLabel::getLocation(){return QPointF(_x, _y);}
void PositionableLabel::setLocation(QPointF pt)
{
 this->_x = (int)pt.x();
 this->_y = (int)pt.y();
}

void PositionableLabel::setLocation(int x, int y)
{
 this->_x = x;
 this->_y = y;
}

int PositionableLabel::getX() {return _x;}

int PositionableLabel::getY() {return _y;}

/*public*/ QString PositionableLabel::getClassName() { return QString(metaObject()->className());}

/*public*/ void PositionableLabel::mousePressEvent(QMouseEvent *ev)
{
 JLabel::mousePressEvent(ev);
}


/*private*/ /*final*/ /*static*/ Logger* PositionableLabel::log = LoggerFactory::getLogger("PositionableLabel");
