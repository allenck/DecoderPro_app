#include "namedbeanhandle.h"

//template<class T>
//NamedBeanHandle<T>::NamedBeanHandle(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Utility class for managing access to a NamedBean
 *
 * @author Bob Jacobsen  Copyright 2009
 * @version $Revision: 19100 $
 */

//public class NamedBeanHandle<T> implements java.io.Serializable {
//template<class T>
///*public*/ NamedBeanHandle<T>::NamedBeanHandle(QString name, T bean)
//{
// this->name = name;
// this->bean = bean;
//}
//template<class T>
///*public*/ QString NamedBeanHandle<T>::getName() {return name;}
//template<class T>
///*public*/ T NamedBeanHandle<T>::getBean() { return this->bean; }
//{ return this->bean; }

//template<class T>
///*public*/ void NamedBeanHandle<T>::setBean(T bean) { this->bean = bean; }

//template<class T>
///*public*/ void NamedBeanHandle<T>::setName(QString name)
//{
// this->name = name;
//}


    //@Override
//template<class T>
///*public*/ bool NamedBeanHandle<T>::equals(QObject* obj)
//{
// if(obj ==this)
//  return true;
// if(obj ==NULL)
//  return false;

////            if(!(getClass()==obj->getClass()))
////                return false;
//            else{
//                NamedBeanHandle<T> tmp = (NamedBeanHandle<T>)obj;
//                if(!tmp.getName().equals(this.getName()))
//                    return false;
//                if(tmp.getBean()!=this.getBean())
//                    return false;
//            }
//        return true;
//    }

    //@Override
template<class T>
/*public*/ int NamedBeanHandle<T>::hashCode() {
        int hash = 7;
        hash = 37 * hash + (getBean() != NULL ? this->getBean().hashCode() : 0);
        hash = 37 * hash + (this->getName() != NULL ? this->getName().hashCode() : 0);
        return hash;
    }
