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
 /*public*/ bool equals(QObject* obj);
 /*public*/ int hashCode();

signals:
    
public slots:
private:
    QString name;
    //template<class T>
    T bean;

    
};

#endif // NAMEDBEANHANDLE_H
