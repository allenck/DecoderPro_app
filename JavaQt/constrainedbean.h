#ifndef CONSTRAINEDBEAN_H
#define CONSTRAINEDBEAN_H
#include "bean.h"
#include "propertyvetoexception.h"
#include "vetoablechangesupport.h"

class PropertyVetoException;
class VetoableChangeListener;
class VetoableChangeSupport;
class ConstrainedBean : public Bean
{
 Q_OBJECT
public:
 ConstrainedBean(QObject* parent = nullptr);
 /*public*/ void setProperty(QString key, QVariant value);
 /*public*/ void setIndexedProperty(QString key, int index, QVariant value);
 /*public*/ void addVetoableChangeListener(VetoableChangeListener* listener);
 /*public*/ void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener);
 /*public*/ QVector<VetoableChangeListener *> *getVetoableChangeListeners();
 /*public*/ QVector<VetoableChangeListener*> *getVetoableChangeListeners(QString propertyName);
 /*public*/ void removeVetoableChangeListener(VetoableChangeListener* listener);
 /*public*/ void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener);
 /*public*/ void fireVetoableChange(PropertyChangeEvent *event) /*throw (PropertyVetoException)*/;
 /*public*/ void fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue) /*throw (PropertyVetoException)*/ ;
 /*public*/ void fireVetoableChange(QString propertyName, int oldValue, int newValue) /*throw (PropertyVetoException)*/ ;
 /*public*/ void fireVetoableChange(QString propertyName, bool oldValue, bool newValue) /*throw (PropertyVetoException)*/ ;

protected:
 /*protected*/ /*final*/ Java_VetoableChangeSupport* vetoableChangeSupport = new Java_VetoableChangeSupport(this);

};

#endif // CONSTRAINEDBEAN_H
