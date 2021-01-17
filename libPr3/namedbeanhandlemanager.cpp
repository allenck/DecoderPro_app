#include "namedbeanhandlemanager.h"
#include "propertychangesupport.h"
#include "abstractnamedbean.h"

//template<class T>
NamedBeanHandleManager::NamedBeanHandleManager(QObject *parent) :
    AbstractNamedBeanHandleManager(parent)
{
    namedBeanHandles = new QList<QObject*>();
    pcs = new PropertyChangeSupport(this);
    registerSelf();
    setProperty("InstanceManagerAutoDefault", "yes");

}
/**
 * Instance for controlling the issuing of NamedBeanHandles.
 * <hr>
 * The NamedBeanHandleManager, deals with controlling and updating NamedBeans
 * across JMRI.  When a piece of code requires persistent access to a bean, it
 * should use a NamedBeanHandle, the NamedBeanHandle stores not only the bean
 * that has been requested but also the named that was used to request it
 * (either User or System Name).
 * <p>
 * This Manager will only issue out one NamedBeanHandle per Bean/Name request.
 * The Manager also deals with updates and changes to the names of Beans, along
 * with moving usernames between different beans.
 * <p>
 * If a beans username is changed by the user, then the name will be updated in
 * the NamedBeanHandle.  If a username is moved from one bean to another, then
 * the bean reference will be updated and the propertyChangeListener attached to
 * that bean will also be moved, so long as the correct method of adding the
 * listener has been used.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Kevin Dickerson Copyright (C) 2011
 * @version			$Revision: 19100 $
 */

//    public class NamedBeanHandleManager extends jmri.managers.AbstractManager implements java.io.Serializable{

//        Checks are performed to make sure that the beans are the same type before being returned
//template<class T>
///*public*/ NamedBeanHandle<T>* NamedBeanHandleManager::getNamedBeanHandle(QString name, T bean)
//{
// if (bean==NULL || name==NULL || name==(""))
//  return NULL;
// NamedBeanHandle<T>* temp = new NamedBeanHandle<T>(name, bean);

// foreach (QObject* h , *namedBeanHandles )
// {
//  if (temp==(h))
//  {
//   temp = NULL;
//   return h;
//   }
//  }
//  namedBeanHandles->append(temp);
//  return temp;
//}

/**
* A Method to update the name on a bean.
* Note this does not change the name on the bean, it only changes the references
*
*/
template<class T>
/*public*/ void NamedBeanHandleManager::renameBean(QString oldName, QString newName, T bean){

    /*Gather a list of the beans in the system with the oldName ref.
    Although when we get a new bean we always return the first one that exists
    when a rename is performed it doesn't delete the bean with the old name
    it simply updates the name to the new one. So hence you can end up with
    multiple named bean entries for one name.
    */
    NamedBeanHandle<T>* oldBean = new NamedBeanHandle<T>(oldName, bean);
    foreach (QObject* h , *namedBeanHandles ) {
        if (oldBean==(NamedBeanHandle<T>*)(h)){
            ((NamedBeanHandle<T>*)h)->setName(newName);
        }
    }
    updateListenerRef(oldName, newName, ((NamedBean*)bean));
    oldBean=NULL;
}

/**
*  A method to effectivily move a name from one bean to another.
*  This method only updates the references to point to the new bean
*  It does not move the name provided from one bean to another.
*/
//Checks are performed to make sure that the beans are the same type before being moved
//template<class T>
/*public*/ void NamedBeanHandleManager::moveBean(NamedBean* oldBean, NamedBean* newBean, QString name)
{
    /*Gather a list of the beans in the system with the oldBean ref.
    Although when a new bean is requested, we always return the first one that exists
    when a move is performed it doesn't delete the namedbeanhandle with the oldBean
    it simply updates the bean to the new one. So hence you can end up with
    multiple bean entries with the same name.
    */

    NamedBeanHandle<NamedBean*>* oldNamedBean = new NamedBeanHandle<NamedBean*>(name, oldBean);
    foreach (QObject* o , *namedBeanHandles )
    {
     NamedBeanHandle<NamedBean*>* h = (NamedBeanHandle<NamedBean*>*)o;
//        if (oldNamedBean->equals(h))
     if(oldNamedBean == h)
            h->setBean(newBean);
    }
    moveListener((NamedBean*)oldBean, (NamedBean*)newBean, name);
    oldNamedBean=NULL;
}

//template<class T>
/*public*/ void NamedBeanHandleManager::updateBeanFromUserToSystem(NamedBean* bean){
    QString systemName = bean->getSystemName();
    QString userName = bean->getUserName();
    renameBean(userName, systemName, bean);
}

//template<class T>
/*public*/ void NamedBeanHandleManager::updateBeanFromSystemToUser(NamedBean* bean) throw(JmriException){
    QString userName = bean->getUserName();
    QString systemName = bean->getSystemName();

    if((userName.isEmpty()) || (userName==(""))){
        log.error("UserName is empty, can not update items to use UserName");
        throw JmriException("UserName is empty, can not update items to use UserName");
    }
    renameBean(systemName, userName, bean);
}

//template<class T>
/*public*/ bool NamedBeanHandleManager::inUse(QString name, NamedBean* bean){
    NamedBeanHandle<NamedBean*>* temp = new NamedBeanHandle<NamedBean*>(name, bean);
    foreach (QObject* h , *namedBeanHandles ) {
        if (temp==(h)){
            temp = NULL;
            return true;
        }
    }
    return false;
}

template<class T>
/*public*/  NamedBeanHandle<T> NamedBeanHandleManager::newNamedBeanHandle(QString name, T bean, QString type){
    return getNamedBeanHandle(name, bean);
}

/**
* A method to update the listener reference from oldName to a newName
*/
//template<class T>
/*private*/ void NamedBeanHandleManager::updateListenerRef(QString oldName, QString newName, NamedBean* nBean){
    QVector<PropertyChangeListener*> listeners = nBean->getPropertyChangeListenersByReference(oldName);
    for(int i = 0; i<listeners.size();i++){
        nBean->updateListenerRef(listeners.at(i), newName);
    }
}

/**
* Moves a propertyChangeListener from one bean to another, where the listerner
* reference matches the currentName.
*/
//template<class T>
/*private*/ void NamedBeanHandleManager::moveListener(NamedBean* oldBean, NamedBean* newBean, QString currentName)
{
 QVector<PropertyChangeListener*> listeners = oldBean->getPropertyChangeListenersByReference(currentName);
 foreach (PropertyChangeListener* l , listeners )
 {
  QString listenerRef = oldBean->getListenerRef(l);
  oldBean->removePropertyChangeListener(l);
  disconnect(((AbstractNamedBean*)newBean)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
  newBean->addPropertyChangeListener(l, currentName, listenerRef);
  connect(((AbstractNamedBean*)newBean)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

// abstract methods to be extended by subclasses
// to free resources when no longer used
//        @Override
//template<class T>
/*public*/ void NamedBeanHandleManager::dispose() {
    //super.dispose();
}

//        @SuppressWarnings("rawtypes")

/**
 * Don't want to store this information
 */
//        @Override
//template<class T>
/*protected*/ void NamedBeanHandleManager::registerSelf() {}

//        @Override
//template<class T>
/*public*/ char NamedBeanHandleManager::systemLetter() {
    throw UnsupportedOperationException("Not supported yet.");
}

//template<class T>
/*public*/ QString NamedBeanHandleManager::getSystemPrefix() const{
    throw UnsupportedOperationException("Not supported yet.");
}

//template<class T>
/*public*/ char NamedBeanHandleManager::typeLetter()const{
    throw UnsupportedOperationException("Not supported yet.");
}

//        @Override
//template<class T>
/*public*/ QString NamedBeanHandleManager::makeSystemName(QString /*s*/) const {
    throw  UnsupportedOperationException("Not supported yet.");
}

//        @Override
//template<class T>
/*public*/ QStringList NamedBeanHandleManager::getSystemNameArray() {
    throw UnsupportedOperationException("Not supported yet.");
}

//        @Override
//template<class T>
/*public*/ QStringList NamedBeanHandleManager::getSystemNameList()
{
    throw UnsupportedOperationException("Not supported yet.");
}

//        @Override
//template<class T>
/*public synchronized*/ void NamedBeanHandleManager::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->addPropertyChangeListener(l);
}

//        @Override
//template<class T>
/*public synchronized*/ void NamedBeanHandleManager::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

//        @Override
//template<class T>
/*protected*/ void NamedBeanHandleManager::firePropertyChange(QString p, QVariant old, QVariant n) { pcs->firePropertyChange(p,old,n);}

//        @Override
//template<class T>
/*public*/ void NamedBeanHandleManager::Register(NamedBean* /*n*/) const {
    throw UnsupportedOperationException("Not supported yet.");
}

//        @Override
//template<class T>
/*public*/ void NamedBeanHandleManager::deregister(NamedBean* /*n*/)const {
    throw UnsupportedOperationException("Not supported yet.");
}

//template<class T>
/*public*/ int NamedBeanHandleManager::getXMLOrder()const {
    throw UnsupportedOperationException("Not supported yet.");
}

//        static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(NamedBeanHandleManager.class.getName());
