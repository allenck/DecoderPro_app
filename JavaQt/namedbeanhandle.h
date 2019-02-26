#ifndef NAMEDBEANHANDLE_H
#define NAMEDBEANHANDLE_H

#include <QObject>
#include "javaqt_global.h"
#include "namedbean.h"

template <class T>
class  NamedBeanHandle : public QObject
{
 //Q_OBJECT
public:
 //explicit NamedBeanHandle(QObject *parent = 0);
 /*public*/ NamedBeanHandle(QString name, T bean){
    this->name = name;
    this->bean = bean;
   }
 /*public*/ QString getName() {return name;}
 /*public*/ T getBean() { return this->bean; }
 /*public*/ void setBean(T bean) { this->bean = bean; }
 /*public*/ void setName(QString name){this->name = name;}
 /*public*/ bool equals(QObject* obj)
 {
 if(obj ==this)
  return true;
 if(obj ==NULL)
  return false;

//            if(!(getClass()==obj->getClass()))
//                return false;
     else{
         NamedBeanHandle<T>* tmp = (NamedBeanHandle<T>*)obj;
         if(tmp->getName() != (this->getName()))
             return false;
         if(tmp->getBean()!=this->getBean())
             return false;
     }
 return true;

}

/*public*/ int hashCode();

signals:
    
public slots:
private:
    QString name;
    //template<class T>
    T bean = nullptr;

    
};

#endif // NAMEDBEANHANDLE_H
