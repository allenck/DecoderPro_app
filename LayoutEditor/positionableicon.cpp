#include "positionableicon.h"
#include "namedicon.h"
#include "positionablelabel.h"
#include <QString>
#include "editor.h"

//PositionableIcon::PositionableIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}
/**
 * Gather common methods for Turnouts, Semsors, SignalHeads, Masts, etc.
 *
 * @author PeteCressman Copyright (C) 2011
 * @version $Revision: 21072 $
 */
//import java.util.Enumeration;
//import java.util.Hashtable;
//import java.util.Iterator;
//import java.util.Map.Entry;

//import jmri.jmrit.catalog.NamedIcon;

///*public*/ class PositionableIcon extends PositionableLabel {


/*public*/ PositionableIcon::PositionableIcon(Editor* editor, Positionable *parent)
    : PositionableLabel(new NamedIcon(":/resources/icons/misc/X-red.gif","resources/icons/misc/X-red.gif"), editor,parent)
{
 init(editor, parent);
 // super ctor call to make sure this is an icon label
 //super(new NamedIcon("resources/icons/misc/X-red.gif","resources/icons/misc/X-red.gif"), editor);
 _control = true;
//    setPopupUtility(NULL);
}

/*public*/ PositionableIcon::PositionableIcon(NamedIcon* s, Editor* editor, Positionable *parent) : PositionableLabel(s,editor,parent)
{
 // super ctor call to make sure this is an icon label
 //super(s, editor);
 init(editor,parent);
 _control = true;
//    setPopupUtility(NULL);
}

/*public*/ PositionableIcon::PositionableIcon(QString s, Editor* editor, Positionable *parent) :  PositionableLabel(s,editor, parent)
{
 // super ctor call to make sure this is an icon label
 //super(s, editor);
 init(editor, parent);
 _control = true;
//    setPopupUtility(NULL);
}
void PositionableIcon::init(Editor* editor, Positionable* parent)
{
 _scale = 1.0;			// getScale, come from net result found in one of the icons
 _rotate = 0;
 _iconMap = new QHash <QString, NamedIcon*>;
 this->parent = parent;
 this->_editor = editor;
 _icon = true;
}

/*public*/ Positionable* PositionableIcon::finishClone(Positionable* p)
{
 PositionableIcon* pos = (PositionableIcon*)p;
 pos->_iconFamily = _iconFamily;
 pos->_scale = _scale;
 pos->_rotate = _rotate;
 //return super.finishClone(pos);
 return PositionableLabel::finishClone((Positionable*)pos);
}

/**
* Get icon by its bean state name key found in jmri.NamedBeanBundle.properties
* Get icon by its localized bean state name
*/
/*public*/ NamedIcon* PositionableIcon::getIcon(QString state)
{
 if(_iconMap == NULL ||_iconMap->isEmpty() || !(_iconMap->contains(state)))
     return new NamedIcon(":/resources/icons/misc/X-red.gif","resources/icons/misc/X-red.gif");
 return _iconMap->value(state);
}

/*public*/ QString PositionableIcon::getFamily() {
    return _iconFamily;
}
/*public*/ void PositionableIcon::setFamily(QString family) {
    _iconFamily = family;
}

/*public*/ QStringListIterator PositionableIcon::getIconStateNames() {
    return _iconMap->keys();
}

/*public*/ int PositionableIcon::maxHeight()
{
 int max = PositionableLabel::maxHeight();
 if (_iconMap!=NULL)
 {
//        Iterator<NamedIcon> iter = _iconMap.values().iterator();
//        while (iter.hasNext()) {
//            max = Math.max(iter.next().getIconHeight(), max);
//        }
  QHashIterator<QString, NamedIcon*> it(*_iconMap);
  while(it.hasNext())
  {
   it.next();
   if(it.value()!= NULL)
    max = qMax(it.value()->getIconHeight(),max);
  }
 }
 return max;
}
/*public*/ int PositionableIcon::maxWidth()
{
 int max = PositionableLabel::maxWidth();
 if (_iconMap!=NULL)
 {
//        Iterator<NamedIcon> iter = _iconMap.values().iterator();
//        while (iter.hasNext()) {
//            max = Math.max(iter.next().getIconWidth(), max);
//        }
  QHashIterator<QString, NamedIcon*> it(*_iconMap);
  while(it.hasNext())
  {
   it.next();
   if(it.value()!= NULL)
    max = qMax(it.value()->getIconWidth(),max);
  }
 }
 return max;
}

/*public*/ void PositionableIcon::displayState(int /*state*/) {
}

/******** popup AbstractAction method overrides *********/

/*protected*/ void PositionableIcon::rotateOrthogonal()
{
//    Iterator<Entry<QString, NamedIcon>> it = _iconMap.entrySet().iterator();
//    while (it.hasNext()) {
//        Entry<QString, NamedIcon> entry = it.next();
//        entry.getValue().setRotation(entry.getValue().getRotation()+1, this);
//    }
 QHashIterator<QString, NamedIcon*> it(*_iconMap);
 while(it.hasNext())
 {
  it.next();
  it.value()->setRotation(it.value()->getRotation()+1,this);
 }
 updateSize();
}

/*public*/ void PositionableIcon::setScale(double s) {
    _scale = s;
    if (_iconMap==NULL) {
        return;
    }
//    Iterator<Entry<QString, NamedIcon>> it = _iconMap.entrySet().iterator();
//    while (it.hasNext()) {
//        Entry<QString, NamedIcon> entry = it.next();
//        entry.getValue().scale(s, this);
//    }
    QHashIterator<QString, NamedIcon*> it(*_iconMap);
    while(it.hasNext())
    {
     it.next();
     it.value()->scale(s,this);
    }
    updateSize();
}

/*public*/ int PositionableIcon::getDegrees()
{
 if (_text)
 {
  return PositionableLabel::getDegrees();
 }
#if 0 // not needed since scaling and rotating is done by QT's QGraphicsScene

 if (_iconMap!=NULL)
 {
//        Iterator<NamedIcon> it = _iconMap.values().iterator();
//        if (it.hasNext()) {
//            return it.next().getDegrees();
//        }
  QHashIterator<QString, NamedIcon*> it(*_iconMap);
  if(it.hasNext())
  {
   it.next();
    return it.value()->getDegrees();
  }
 }
#endif
 return PositionableLabel::getDegrees();
}


/*public*/ void PositionableIcon::rotate(int deg)
{
 _rotate = deg%360;
 setDegrees(deg);
#if 0 // not needed since scaling and rotating is done by QT's QGraphicsScene
 if (_text && !_icon)
 {
  PositionableLabel::rotate(deg);
 }
 if (_iconMap==NULL)
 {
  return;
 }
//    Iterator<Entry<QString, NamedIcon>> it = _iconMap.entrySet().iterator();
//    while (it.hasNext()) {
//        Entry<QString, NamedIcon> entry = it.next();
//        entry.getValue().rotate(deg, this);
//    }
 QHashIterator<QString, NamedIcon*> it(*_iconMap);
 while(it.hasNext())
 {
  it.next();
  if(it.value()!= NULL)
   it.value()->rotate(deg,this);
 }
#endif
}

/*protected*/ QHash<QString, NamedIcon*>* PositionableIcon::cloneMap(QHash<QString, NamedIcon*>* map,
                                                         PositionableLabel* pos)
{
 QHash<QString, NamedIcon*>* clone = new QHash<QString, NamedIcon*>();
// if (map!=NULL)
// {
//  Iterator<Entry<QString, NamedIcon>> it = map.entrySet().iterator();
//  while (it.hasNext())
//  {
//   Entry<QString, NamedIcon> entry = it.next();
//   clone.put(entry.getKey(), cloneIcon(entry.getValue(), pos));
//  }
// }
 if(map != NULL)
 {
  QHashIterator<QString, NamedIcon*> it(*map);
  while (it.hasNext())
  {
   it.next();
   clone->insert(it.key(),it.value());
  }
 }
 return clone;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionableIcon.class.getName());
//}
void PositionableIcon::invalidate()
{
 //_editor->addToTarget(this);
 updateScene();
}
