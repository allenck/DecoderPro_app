#ifndef REQUESTEDDIRECTIONOBSERVED_H
#define REQUESTEDDIRECTIONOBSERVED_H

#include <QObject>
#include "propertychangesupport.h"

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
  /*private*/ /*final*/ PropertyChangeSupport*_mPropertyChangeSupport = new PropertyChangeSupport(this);
  /*private*/ /*final*/ static QString PROPERTY;// = "RequestedDirection";  // NOI18N  NEVER pass "null" for propertyName, there is a bug relating to this (for safety!)

};

#endif // REQUESTEDDIRECTIONOBSERVED_H
