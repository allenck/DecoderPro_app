#ifndef REQUESTEDDIRECTIONOBSERVED_H
#define REQUESTEDDIRECTIONOBSERVED_H

#include <QObject>
#include "swingpropertychangesupport.h"

class RequestedDirectionObserved : public QObject
{
  Q_OBJECT
 public:
  /*public*/ RequestedDirectionObserved(QObject *parent = nullptr);
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* pcl);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* pcl);
  /*public*/ void setRequestedDirection(int newRequestedDirection);
  /*public*/ int getRequestedDirection();

 signals:

 public slots:

 private:
  /*private*/ int _mRequestedDirection;
  /*private*/ /*final*/ SwingPropertyChangeSupport*_mSwingPropertyChangeSupport = new SwingPropertyChangeSupport(this, nullptr);
  /*private*/ /*final*/ static QString PROPERTY;// = "RequestedDirection";  // NOI18N  NEVER pass "null" for propertyName, there is a bug relating to this (for safety!)

};

#endif // REQUESTEDDIRECTIONOBSERVED_H
