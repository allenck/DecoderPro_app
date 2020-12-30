#include "opath.h"
#include "oblock.h"
#include "portal.h"
#include <QTimer>
#include "abstractturnout.h"
#include "warranttableaction.h"

//OPath::OPath(QObject *parent) :
//    Path(parent)
//{
//}
/**
 * Extends jmri.Path.
 * An OPath is a route that traverses a Block from one boundary to another.
 * The mBlock parameter of Path is used to reference the Block to which this OPath belongs.
 * (Not a destination Block as might be inferred from the naming in Path.java)
 * <P>
 * An OPath inherits the List of BeanSettings for all the turnouts needed to traverse the Block.
 * It also has references to the Portals (block boundary objects) through wich it enters or
 * exits the block.  One of these may be NULL, if the OPath  dead ends within the block.
 *
 * @author	Pete Cressman  Copyright (C) 2009
 */
///*public*/ class OPath extends jmri.Path  {


/**
 * Create an object with default directions of NONE, and
 * no setting element.
 */
/*public*/ OPath::OPath(Block* owner, QString name, QObject *parent)
 : Path(owner, 0, 0, parent)
{
 //super(owner, 0, 0);
 common();
 _name = name;
 setObjectName(name);
}
/*public*/ OPath::OPath(Block* owner, int toBlockDirection, int fromBlockDirection, QObject *parent)
 : Path(owner, toBlockDirection, fromBlockDirection, parent)
{
    //super(owner, toBlockDirection, fromBlockDirection);
 common();
}
/*public*/ OPath::OPath(Block* owner, int toBlockDirection, int fromBlockDirection, BeanSetting* setting, QObject *parent)
 : Path(owner, toBlockDirection, fromBlockDirection, setting, parent)
{
 //super(owner, toBlockDirection, fromBlockDirection, setting);
 common();
}
///*public*/ OPath::OPath(QString name, OBlock* owner, Portal* entry, int fromBlockDirection,
//                     Portal* exit, int toBlockDirection, QObject *parent) : Path(owner, toBlockDirection, fromBlockDirection, parent)
/*public*/ OPath::OPath(QString name, OBlock* owner, Portal* entry, Portal* exit, QList<BeanSetting*> settings,QObject *parent) : Path(owner, 0, 0, parent)
{
 //super(owner, 0, 0);
 common();
 _name = name;
 setObjectName(name);
 _fromPortal = entry;
 _toPortal = exit;
 if (!settings.isEmpty())
 {
  for (int i = 0; i < settings.size(); i++)
  {
   addSetting(settings.at(i));
  }
 }
 if (log->isDebugEnabled())
 {
  log->debug("Ctor: name= " + name + ", block= " + owner->getDisplayName()
          + ", fromPortal= " + (_fromPortal == NULL ? "null" : _fromPortal->getName())
          + ", toPortal= " + (_toPortal == NULL ? "null" : _toPortal->getName()));
 }
}

void OPath::common()
{
 log = new Logger("OPath");
 log->setDebugEnabled(true);
 _timerActive = false;
 _fromPortal = NULL;
 _toPortal = NULL;
 _listener = NULL;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="UR_UNINIT_READ_CALLED_FROM_SUPER_CONSTRUCTOR")
// OPath ctor invokes Path ctor via super(), which calls this, before the internal
// _block variable has been set so that Path.getPath() can work.  In this implementation,
// getPath() only controls whether log->debug(...) is fired, but this might change if/when
// super.setBlock(...) is changed, in which case this logic will fail.
/*public*/ void OPath::setBlock(Block* block)
{
 if (getBlock()==block) { return; }
 if (log->isDebugEnabled()) log->debug("OPath \""+_name+"\" changing blocks from "+
                      (getBlock()!=NULL ? getBlock()->getDisplayName() : NULL)+
                      " to "+(block!=NULL ? block->getDisplayName() : NULL)+".");
 Path::setBlock(block);
}

/*protected*/ QString OPath::getOppositePortalName(QString name)
{
 if (_fromPortal!=NULL && _fromPortal->getName()==(name))
 {
  if (_toPortal!=NULL)
  {
   return _toPortal->getName();
  }
 }
 if (_toPortal!=NULL && _toPortal->getName()==(name))
 {
  if (_fromPortal!=NULL)
  {
   return _fromPortal->getName();
  }
 }
 return NULL;
}

/*protected*/ bool OPath::validatePortals()
{
 if (!_fromPortal->isValid())
 {
  return false;
 }
 return _toPortal->isValid();
}

/*public*/ void OPath::setName(QString name)
{
 if (log->isDebugEnabled()) {
     log->debug("OPath \"" + _name + "\" setName to " + name);
 }
 if (name == NULL || name.length() == 0)
 {
     return;
 }
 QString oldName = _name;
 _name = name;
 setObjectName(name);
 OBlock* block = (OBlock*) getBlock();
 block->pseudoPropertyChange("pathName", oldName, _name);
 WarrantTableAction::pathNameChange(block, oldName, _name);
 if (_fromPortal != NULL)
 {
  if (_fromPortal->addPath(this))
  {
      return;
  }
 }
 if (_toPortal != NULL) {
     _toPortal->addPath(this);
 }
}

/*public*/ QString OPath::getName() { return _name; }

/*public*/ void OPath::setFromPortal(Portal* p)
{
 if (log->isDebugEnabled() && p!=NULL) log->debug("OPath \""+_name+"\" setFromPortal= "+p->getName());
 _fromPortal = p;
}
/*public*/ Portal* OPath::getFromPortal() { return _fromPortal; }

/*public*/ void OPath::setToPortal(Portal* p)
{
 if (log->isDebugEnabled() && p!=NULL) log->debug("OPath \""+_name+"\" setToPortal= "+p->getName());
 _toPortal = p;
}
/*public*/ Portal* OPath::getToPortal() { return _toPortal; }

/**
* Set path turnout commanded state and lock state
* @param delay following actions in seconds
* @param set when true, command turnout to settings, false don't set command - just do lock setting
* @param lockState set when lock==true, lockState unset when lock==false
* @param lock
* If lockState==0 setLocked() is not called.  (lockState should be 1,2,3)
*/
/*public*/ void OPath::setTurnouts(int delay, bool set, int lockState, bool lock)
{
 if(delay>0)
 {
  if (!_timerActive)
  {
   // Create a timer if one does not exist
   if (_timer==NULL)
   {
    _listener = new OPTimeTurnout(this);
    //_timer = new Timer(2000, _listener);
    _timer = new QTimer();
    //_timer.setRepeats(false);
    _timer->setSingleShot(true);
   }
   _listener->setList(getSettings());
   _listener->setParams(set, lockState, lock);
   //_timer->setInitialDelay(delay*1000);
   _timer->start(2000);
   _timerActive = true;
   connect(_timer, SIGNAL(timeout()), _listener, SLOT(actionPerformed()));
  }
  else
  {
   log->warn("timer already active for delayed turnout action on path "+toString());
  }
 }
 else
 {
  fireTurnouts(getSettings(), set, lockState, lock);
 }
}

void OPath::fireTurnouts(QList<BeanSetting*> list, bool set, int lockState, bool lock) {
    for (int i=0; i<list.size(); i++)  {
        BeanSetting* bs = list.at(i);
        Turnout* t = (Turnout*)bs->getBean();
        if (t==NULL) {
            log->error("Invalid turnout on path "+toString());
        } else {
            if (set) {
                ((AbstractTurnout*)t)->setCommandedState(bs->getSetting());
            }
            if (lockState>0) {
                ((AbstractTurnout*)t)->setLocked(lockState, lock);
            }
        }
    }
}

/*public*/ void OPath::dispose() {
    if (_fromPortal!=NULL) { _fromPortal->removePath(this); }
    if (_toPortal!=NULL) { _toPortal->removePath(this); }
}


/**
 *	Class for defining ActionListener for ACTION_DELAYED_TURNOUT
 */
//class TimeTurnout implements java.awt.event.ActionListener
//{
    /*public*/ OPTimeTurnout::OPTimeTurnout(OPath* self ) {
    this->self = self;
    }

    void OPTimeTurnout::setList(QList<BeanSetting*> l) {
        list =  l;
    }
    void OPTimeTurnout::setParams(bool s, int ls, bool l) {
        set = s;
        lockState = ls;
        lock = l;
    }

    /*public*/ void OPTimeTurnout::actionPerformed(JActionEvent* event)
    {
        self->fireTurnouts(list, set, lockState, lock);
        // Turn Timer OFF
        if (self->_timer != NULL)
        {
            self->_timer->stop();
            self->_timerActive = false;
        }
    }
//};

/*public*/ QString OPath::getDescription() {
    return "\""+_name+"\""+(_fromPortal==NULL?"":" from portal "+_fromPortal->getName())+
                (_toPortal==NULL?"":" to portal "+ _toPortal->getName());
}

/*public*/ QString OPath::toString()
{
 return "OPath \""+_name+"\"on block "+(getBlock()!=NULL ? getBlock()->getDisplayName(): "NULL")+
     (_fromPortal==NULL?"":" from portal "+_fromPortal->getName())+
     (_toPortal==NULL?"":" to portal "+ _toPortal->getName());
}

/**
 * override to disallow duplicate setting
 */
/*public*/ void OPath::addSetting(BeanSetting* t)
{
 QListIterator<BeanSetting*> iter(getSettings());
 while (iter.hasNext())
 {
  BeanSetting* bs = iter.next();
  if (bs->getBeanName() == (t->getBeanName()))
  {
   log->error("TO setting for \"" + t->getBeanName() + "\" already set to " + QString::number(bs->getSetting()));
   return;
  }
 }
 Path::addSetting(t);
}

/**
 * Override to indicate logical equality for use as paths in OBlocks.
 *
 */
/*public*/ bool OPath::equals(OPath* path)
{
 if (_fromPortal != NULL && _fromPortal != (path->getFromPortal()))
 {
  return false;
 }
 if (_toPortal != NULL && _toPortal != (path->getToPortal()))
 {
  return false;
 }

 if(_name != path->_name) // ACK I added this!
  return false;

 QListIterator<BeanSetting*> iter(path->getSettings());
 while (iter.hasNext())
 {
  BeanSetting* beanSetting = iter.next();
  QListIterator<BeanSetting*> it( getSettings());
  while (it.hasNext())
  {
   BeanSetting* bs = it.next();
   if ((bs->getBeanName().compare(beanSetting->getBeanName()) != 0))
   {
    return false;
   }
   if (bs->getSetting() != beanSetting->getSetting())
   {
    return false;
   }
  }
 }
 return true;
}
