#ifndef NAMEDBEANHANDLEMANAGER_H
#define NAMEDBEANHANDLEMANAGER_H
#include "abstractnamedbeanhandlemanager.h"
#include "logger.h"
#include "exceptions.h"
#include "namedbeanhandle.h"
#include <QList>
#include "javaqt_global.h"
//template <typename T> class NamedBeanhandle;
//template <class T>

class JAVAQTSHARED_EXPORT NamedBeanHandleManager:  public AbstractNamedBeanHandleManager
{
//Q_OBJECT
public:
explicit NamedBeanHandleManager(QObject *parent = 0);
 ~NamedBeanHandleManager() {}
 NamedBeanHandleManager(const NamedBeanHandleManager&) : AbstractNamedBeanHandleManager() {}
//template <typename T>
template<class T>
NamedBeanHandle<T>* getNamedBeanHandle(QString name, T bean)
{
 if (bean==NULL || name==NULL || name==(""))
  return NULL;
 NamedBeanHandle<T>* temp = new NamedBeanHandle<T>(name, bean);

 foreach (QObject* h , *namedBeanHandles )
 {
  if (temp==(h))
  {
   temp = NULL;
   return (NamedBeanHandle<T>*)h;
  }
 }
 namedBeanHandles->append(temp);
 return temp;
}

/**
* A Method to update the name on a bean.
* Note this does not change the name on the bean, it only changes the references
*
*/
// <typename T>
template<class T>
/*public*/ void renameBean(QString oldName, QString newName, T bean);
/**
*  A method to effectivily move a name from one bean to another.
*  This method only updates the references to point to the new bean
*  It does not move the name provided from one bean to another.
*/
//Checks are performed to make sure that the beans are the same type before being moved
//template <typename T>
//template<class T>
/*public*/ void moveBean(NamedBean* oldBean, NamedBean* newBean, QString name);

/*public*/ void updateBeanFromUserToSystem(NamedBean* bean);
/*public*/ void updateBeanFromSystemToUser(NamedBean* bean) throw(JmriException);
// <typename T>
//template<class T>
/*public*/ bool inUse(QString name, NamedBean* bean);
// <typename T>
template<class T>
/*public*/  NamedBeanHandle<T> newNamedBeanHandle(QString name, T bean, QString type);
// abstract methods to be extended by subclasses
// to free resources when no longer used
/*public*/ virtual void dispose()override;
/*public*/ char systemLetter();
/*public*/ QString getSystemPrefix() const override;
/*public*/ char typeLetter() const override;
/*public*/ QString makeSystemName(QString s)const override;
/*public*/ QStringList getSystemNameArray() override;
/*public*/ QStringList getSystemNameList()override;
PropertyChangeSupport* pcs; // = new PropertyChangeSupport(this);
/*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l)override;
/*public synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
 /*public*/ void Register(NamedBean* n)const override;
/*public*/ void deregister(NamedBean* n)const override;
/*public*/ int getXMLOrder()const override;
///*public*/ NamedBean* getBySystemName(QString /*systemName*/) const override {return nullptr;}
///*public*/ NamedBean* getByUserName(QString /*userName*/) const override{return nullptr;}
/*public*/ QString getNamedBeanClass()const override {
    return "NamedBean";
}
signals:

public slots:
private:
Logger log;
/**
* A method to update the listener reference from oldName to a newName
*/
/*private*/ void updateListenerRef(QString oldName, QString newName, NamedBean* nBean);
/**
* Moves a propertyChangeListener from one bean to another, where the listerner
* reference matches the currentName.
*/
/*private*/ void moveListener(NamedBean* oldBean, NamedBean* newBean, QString currentName);

//template<class T>
QList<QObject* >*  namedBeanHandles;// = new ArrayList<NamedBeanHandle>();
protected:
/*protected*/ void registerSelf();
/*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

};
Q_DECLARE_METATYPE(NamedBeanHandleManager)
#endif // NAMEDBEANHANDLEMANAGER_H
