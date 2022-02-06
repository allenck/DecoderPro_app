#include "beansetting.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"

//BeanSetting::BeanSetting(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Represent a Named Bean (e.g.&nbsp;Turnout)
 * and specific setting for it.
 * These can be used e.g. to represent part of a particular
 * path through a layout, or a condition that has to be
 * true as part of something.
 *<p>
 * Objects of this class are immutable, in that once created
 * the selected bean and required setting cannot be changed.
 * However, the value of the <code><a href="#check()">check</a></code> method does
 * change, because it's a function of the current bean setting(s).
 *
 * @author	Bob Jacobsen  Copyright (C) 2006, 2008, 2010
 * @version	$Revision: 18109 $
 */
//@net.jcip.annotations.Immutable
//public class BeanSetting  {

/*public*/ BeanSetting::BeanSetting(NamedBean* t, QString pName, int setting)
{
 _setting = setting;
 if(t==NULL)
 {
  _namedBean=NULL;
  return;
 }
 QObject* nbhm =   InstanceManager::getDefault("NamedBeanHandleManager");
   // _namedBean = ((NamedBeanHandleManager<NamedBeanHandle*>*)InstanceManager::getDefault("NamedBeanHandleManager<NamedBeanHandle*>"))->getNamedBeanHandle(pName, t);
    _namedBean = ((NamedBeanHandleManager*)nbhm)->getNamedBeanHandle(pName,t);

}

/*public*/ BeanSetting::BeanSetting(NamedBean* t, int setting){
    _setting = setting;
    if(t==NULL){
        _namedBean=NULL;
        return;
    }
    _namedBean = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(t->getDisplayName(), t);
}

/**
 * Convenience method; check if the Bean currently has the desired setting
 */
/*public*/ bool BeanSetting::check(){
    if(_namedBean==NULL)
        return false;
    return _namedBean->getBean()->getState() == _setting;
}

/*public*/ NamedBean* BeanSetting::getBean() {
    if(_namedBean==NULL)
        return NULL;
    return _namedBean->getBean();
}

/*public*/ QString BeanSetting::getBeanName() {
    if(_namedBean==NULL)
        return "";
    return _namedBean->getName();
}

/*public*/ int BeanSetting::getSetting() { return _setting; }
/**
 * {@inheritDoc}
 * <p>
 * This implementation always throws an UnsupportedOperationException since
 * a BeanSetting is immutable.
 *
 * @throws UnsupportedOperationException if called
 */
//@Override
/*public*/ void BeanSetting::setExpectedState(int state) {
    throw new UnsupportedOperationException("The expected state of a BeanSetting is immutable");
}

// include bean and expected state in equals() and hashCode() because they can't
// change after construction
//@Override
/*public*/ bool BeanSetting::equals(QObject* obj) {
    if (obj == this) {
        return true;
    } else if (obj == nullptr) {
        return false;
    }
    //else if (!Objects.equals(getClass(), obj.getClass())) {
    else if(metaObject()->className() == obj->metaObject()->className())
    {
        return false;
    }
    else
    {
     BeanSetting* p = (BeanSetting*) obj;
     if (p->getSetting() != this->getSetting())
     {
         return false;
     }
     if (!p->getBean()->equals( this->getBean()->self())) {
         return false;
     }
    }
    return true;
}

//static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(BeanSetting.class.getName());
//}
