#include "locoicon.h"
#include "layouteditor.h"
#include "positionablepopuputil.h"
#include "Throttle/throttleframemanager.h"
#include "Throttle/throttlewindow.h"

//LocoIcon::LocoIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}

const QString LocoIcon::WHITE = "White";		//loco background colors
const QString LocoIcon::GREEN = "Green";
const QString LocoIcon::GRAY = "Gray";
const QString LocoIcon::RED = "Red";
const QString LocoIcon::BLUE = "Blue";
const QString LocoIcon::YELLOW = "Yellow";

/**
 * An icon that displays the position of a loco on a panel.<P>
 * The icon can always be repositioned and its popup menu is
 * always active.
 * @author Bob Jacobsen  Copyright (c) 2002
 * @author Daniel Boudreau Copyright (C) 2008, 2010
 * @version $Revision: 22320 $
 */

///*public*/ class LocoIcon extends PositionableLabel {

/*public*/ LocoIcon::LocoIcon(Editor* editor) :
    PositionableLabel(new NamedIcon(":/resources/icons/markers/loco-white.gif",                                                                                        ":/resources/icons/markers/loco-white.gif"), editor, (Positionable*)this)
{
 common();
 this->editor = editor;

 // super ctor call to make sure this is an icon label
 //super(new NamedIcon("resources/icons/markers/loco-white.gif",
//                        "resources/icons/markers/loco-white.gif"), editor);
 setDisplayLevel(LayoutEditor::MARKERS);
 setShowTooltip(false);
 //setEditable(false);
 _text = true;	//Markers are an icon with text
 setPopupUtility(new PositionablePopupUtil((Positionable*)this, this));
// {       // need this class for Font Edit
//        /*public*/ void setFixedTextMenu(JPopupMenu popup) {}
//        /*public*/ void setTextMarginMenu(JPopupMenu popup) {}
//        /*public*/ void setTextBorderMenu(JPopupMenu popup) {}
//        /*public*/ void setTextJustificationMenu(JPopupMenu popup) {}
//    });
}

void LocoIcon::common()
{
 _dockX = 0;
 _dockY = 0;
 locoButtonGroup = NULL;
 white = new NamedIcon(":/resources/icons/markers/loco-white.gif",
                                  "resources/icons/markers/loco-white.gif");
 green = new NamedIcon(":/resources/icons/markers/loco-green.gif",
                                 "resources/icons/markers/loco-green.gif");
 gray = new NamedIcon(":/resources/icons/markers/loco-gray.gif",
                                 "resources/icons/markers/loco-gray.gif");
 red = new NamedIcon(":/resources/icons/markers/loco-red.gif",
                                 "resources/icons/markers/loco-red.gif");
 blue = new NamedIcon(":/resources/icons/markers/loco-blue.gif",
                                 "resources/icons/markers/loco-blue.gif");
 yellow = new NamedIcon(":/resources/icons/markers/loco-yellow.gif",
                                 "resources/icons/markers/loco-yellow.gif");
//_itemGroup = NULL;
entry = NULL;
_bVisible = true;
_locoColor = QColor(Qt::white);
}

/*public*/ Positionable* LocoIcon::deepClone()
{
 LocoIcon* pos = new LocoIcon(_editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* LocoIcon::finishClone(Positionable* p)
{
 LocoIcon* pos = (LocoIcon*)p;
 if (entry!=NULL)
 {
  pos->setRosterEntry(getRosterEntry());
 }
 else
 {
  pos->setText(getText());
 }
 return PositionableLabel::finishClone((Positionable*)pos);
}

// Marker tool tips are always disabled
/*public*/ void LocoIcon::setShowTooltip(bool /*set*/){PositionableLabel::setShowTooltip(false);}

// Markers are always positionable
/*public*/ void LocoIcon::setPositionable(bool /*enabled*/) {PositionableLabel::setPositionable(true);}

// Markers always have a popup menu
/*public*/ bool LocoIcon::doViemMenu() {
    return false;
}


/**
 * Pop-up only if right click and not dragged
 */
/*public*/ bool LocoIcon::showPopUp(QMenu* popup)
{
 if (entry != NULL)
 {
//  popup.add(new AbstractAction("Throttle") {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                tf = jmri.jmrit.throttle.ThrottleFrameManager.instance().createThrottleFrame();
//                tf.getAddressPanel().setRosterEntry(entry);
//                tf.toFront();
//            }
//        });
//    }
  QAction* throttleAction = new QAction(tr("Throttle"),this);
  popup->addAction(throttleAction);
  connect(throttleAction, SIGNAL(triggered()), this, SLOT(on_throttleAction()));
 }
 popup->addMenu(makeLocoIconMenu());
 if (isEditable())
 {
  getEditor()->setShowAlignmentMenu((Positionable*)this, popup);
  getEditor()->setShowCoordinatesMenu((Positionable*)this, popup);
  popup->addAction(makeDockingMenu());
  popup->addAction(makeDockMenu());
  getPopupUtility()->setTextFontMenu(popup);
 }
 else
 {
  setRotateMenu(popup);
  if (entry==NULL)
  {
  setTextEditMenu(popup);
  }
  popup->addAction(makeDockMenu());
  getPopupUtility()->setTextFontMenu(popup);
  getEditor()->setRemoveMenu((Positionable*)this, popup);
 }
 return true;
}

void LocoIcon::on_throttleAction()
{
 //tf = ThrottleFrameManager::instance()->createThrottleFrame();
 //tf.getAddressPanel().setRosterEntry(entry);
 //tf.toFront();
 tw = new ThrottleWindow();
 //tw->setId(entry->getId());
 tw->show();
}

/*protected*/ QMenu* LocoIcon::makeLocoIconMenu()
{
 QMenu* iconMenu = new QMenu(tr("Loco Marker Color"));
 locoButtonGroup = new QActionGroup(this);
 QStringList colors = getLocoColors();
 for (int i=0; i<colors.length(); i++)
 {
  addLocoMenuEntry(iconMenu, colors.at(i));
 }
 connect(locoButtonGroup, SIGNAL(selected(QAction*)), this, SLOT(on_locoColor_selected(QAction*)));
 return iconMenu;
}

// loco icons

/*public*/ void LocoIcon::addLocoMenuEntry (QMenu* iconMenu, /*final*/ QString color)
{
    //JRadioButtonMenuItem r = new JRadioButtonMenuItem(color);
//    r.addActionListener(new ActionListener() {
//        final QString desiredColor = color;
//        /*public*/ void actionPerformed(ActionEvent e) { setLocoColor(desiredColor); }
//    });
 QAction* r = new QAction(color, this);
 r->setCheckable(true);
 if(_locoColor ==  QColor(Qt::white) && color == WHITE)
  r->setChecked(true);
 else if(_locoColor ==  QColor(Qt::green) && color == GREEN)
  r->setChecked(true);
 else if(_locoColor ==  QColor(Qt::gray) && color == GRAY)
  r->setChecked(true);
 else if(_locoColor ==  QColor(Qt::red) && color == RED)
  r->setChecked(true);
 else if(_locoColor ==  QColor(Qt::blue) && color == BLUE)
  r->setChecked(true);
 else if(_locoColor ==  QColor(Qt::yellow) && color == YELLOW)
  r->setChecked(true);

 locoButtonGroup->addAction(r);
 iconMenu->addAction(r);
}
void LocoIcon::on_locoColor_selected(QAction *act)
{
 setLocoColor(act->text());
 _unRotatedText = "";
 setText(getText());
 updateScene();
}

/*public*/ void LocoIcon::setLocoColor(QString color)
{
 log.debug("Set loco color to " + color);
 if(color==(WHITE))
 {
  PositionableLabel::updateIcon (white);
  _locoColor = QColor(Qt::white);
  setForeground (QColor(Qt::black));
 }
 if(color==(GREEN))
 {
  PositionableLabel::updateIcon (green);
  _locoColor = QColor(Qt::green);
  setForeground (QColor(Qt::black));
 }
 if(color==(GRAY))
 {
  PositionableLabel::updateIcon (gray);
  _locoColor = QColor(Qt::gray);
  setForeground (QColor(Qt::white));
 }
 if(color==(RED))
 {
  PositionableLabel::updateIcon (red);
  _locoColor = QColor(Qt::red);
  setForeground (QColor(Qt::white));
 }
 if(color==(BLUE))
 {
  PositionableLabel::updateIcon (blue);
  _locoColor = QColor(Qt::blue);
  setForeground (QColor(Qt::white));
 }
 if(color==(YELLOW))
 {
  PositionableLabel::updateIcon (yellow);
  _locoColor = QColor(Qt::yellow);
  setForeground (QColor(Qt::black));
 }
}

/*public*/ /*static*/ QStringList LocoIcon::getLocoColors()
{
    //QString[] colors = {WHITE,GREEN,GRAY,RED,BLUE,YELLOW};
 QStringList colors;
 colors << WHITE<<GREEN<<GRAY<<RED<<BLUE<<YELLOW;
 return colors;
}

/*public*/ void LocoIcon::setRosterEntry (RosterEntry* entry)
{
 this->entry = entry;
}

/*public*/ RosterEntry* LocoIcon::getRosterEntry ()
{
    return entry;
}

/*protected*/ QAction* LocoIcon::makeDockingMenu() {
//    JMenuItem dockingMenu = new JMenuItem(Bundle.getMessage("setDockingLocation"));
//    dockingMenu.addActionListener(new ActionListener() {
//        Editor ed;
//        LocoIcon loco;
//        ActionListener init(Editor e, LocoIcon l) {
//            ed = e;
//            loco =l;
//            return this;
//        }
//        /*public*/ void actionPerformed(ActionEvent e) {
//            ed.setSelectionsDockingLocation(loco);
//        }
//    }.init(getEditor(), this));
 DockingActionListener* dal = new DockingActionListener();
 dal->init(getEditor(), this);
 QAction* dockingMenu = new QAction(tr("Set Location for Docking"),this);
 connect(dockingMenu, SIGNAL(triggered()), dal, SLOT(actionPerformed()));
 return dockingMenu;
}

DockingActionListener* DockingActionListener::init(Editor *e, LocoIcon *l)
{
 ed = e;
 loco =l;
 return this;
}
void DockingActionListener::actionPerformed()
{
 ed->setSelectionsDockingLocation((Positionable*)loco);
}
/*public*/ void LocoIcon::setDockingLocation(int x, int y) {
 _dockX = x;
 _dockY = y;
}
/**
 * Called at load time to get "background" color
 */
/*public*/ void LocoIcon::init()
{
 NamedIcon* icon = (NamedIcon*) getIcon();
 QString name = icon->getURL();
 if (name.endsWith("loco-white.gif"))
 {
  _locoColor = QColor(Qt::white);
 }
 else if (name.endsWith("loco-green.gif"))
 {
  _locoColor = QColor(Qt::green);
 }
 else if (name.endsWith("loco-gray.gif"))
 {
  _locoColor = QColor(Qt::gray);
 }
 else if (name.endsWith("loco-red.gif"))
 {
  _locoColor = QColor(Qt::red);
 }
 else if (name.endsWith("loco-blue.gif"))
 {
  _locoColor = QColor(Qt::blue);
 }
 else if (name.endsWith("loco-yellow.gif"))
 {
  _locoColor = QColor(Qt::yellow);
 }
}

/*public*/ int LocoIcon::getDockX() {
    return _dockX;
}
/*public*/ int LocoIcon::getDockY() {
    return _dockY;
}

/*public*/ void LocoIcon::dock()
{
 setLocation(_dockX, _dockY);
 //editor->addToTarget((Positionable*)this);
 if(_itemGroup != NULL)
  updateScene();
}

/*protected*/ QAction* LocoIcon::makeDockMenu()
{
//    JMenuItem dockMenu = new JMenuItem(Bundle.getMessage("dockIcon"));
//    dockMenu.addActionListener(new ActionListener() {
//        Editor ed;
//        LocoIcon loco;
//        ActionListener init(Editor e, LocoIcon l) {
//            ed = e;
//            loco =l;
//            return this;
//        }
//       /*public*/ void actionPerformed(ActionEvent e) {
//            ed.dockSelections(loco); }
//    }.init(getEditor(), this));
 QAction* dockMenu = new QAction(tr("Dock Icon"),this);
 DockMenuListener* dml = new DockMenuListener();
 connect(dockMenu, SIGNAL(triggered()), dml, SLOT(actionPerformed()));
 dml->init(getEditor(), this);
 return dockMenu;
}
DockMenuListener* DockMenuListener::init(Editor* e, LocoIcon* l)
{
 ed = e;
 loco =l;
 return this;
}

 /*public*/ void DockMenuListener::actionPerformed()
{
 ed->dockSelections((Positionable*)loco);
}

/*public*/ bool LocoIcon::updateScene()
{
 if(isIcon())
 {
  QGraphicsPixmapItem* item = NULL;

  QPixmap pixmap = QPixmap::fromImage(getIcon()->getOriginalImage());
  if(pixmap.isNull())
  {
   log.debug(QString("LocoIcon null pixmap: %1").arg(JLabel::getIcon()->getURL()));
   return false;
  }
  if(_itemGroup != NULL)
  {
   QList<QGraphicsItem*> itemList = _itemGroup->childItems();
   foreach(QGraphicsItem* it, itemList)
   {
    if(qgraphicsitem_cast<QGraphicsPixmapItem*>(it) != NULL)
    {
     _itemGroup->setRotation(_itemGroup->rotation() - currRotation);
     item = qgraphicsitem_cast<QGraphicsPixmapItem*>(it);
     continue;
    }
    _itemGroup->removeFromGroup(item);
   }
  }
  else
   _itemGroup = new MyGraphicsItemGroup();
  if(item != NULL)
   item->setPixmap(pixmap);
  else
   item = new QGraphicsPixmapItem(pixmap, _itemGroup);
  setSize(pixmap.width(),pixmap.height());
  item->setPos(getX(), getY());
  if(showTooltip()) item->setToolTip(getTooltip());
  //_itemGroup->addToGroup(item);
  //_itemGroup->setPos(getX(), getY());
  currRotation = getIcon()->getRotation()*90;
  if((getDegrees() + currRotation) != 0)
  {
   QPointF center = item->boundingRect().center();
   _itemGroup->setTransformOriginPoint(center);
   _itemGroup->setRotation(item->rotation()+ currRotation);
  }
 }
 else
 { // text
  if(_itemGroup != NULL)
  {
   QList<QGraphicsItem*> itemList = _itemGroup->childItems();
   foreach(QGraphicsItem* item, itemList)
   {
    _itemGroup->removeFromGroup(item);
   }
  }
  else
   _itemGroup = new MyGraphicsItemGroup();
  _itemGroup->setName("LocoIcon");

  QGraphicsTextItem* item = new QGraphicsTextItem(getUnRotatedText(),_itemGroup);
  //item->setPos(getX(), getY());
  if(showTooltip()) item->setToolTip(getTooltip());
  _itemGroup->addToGroup(item);
  _itemGroup->setPos(getX(), getY());
  if(getDegrees() != 0)
  {
   QPointF center = item->boundingRect().center();
   _itemGroup->setTransformOriginPoint(center);
   _itemGroup->setRotation(item->rotation()+ getDegrees());
  }
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 //editScene->addItem(pl->_itemGroup);
 return true;
}

void LocoIcon::setLocation(double x, double y)
{
 if(_itemGroup != NULL)
 {
  _itemGroup->setPos(QPointF(x,y));
 }
 JLabel::setLocation(x, y);
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoIcon.class.getName());
//}
