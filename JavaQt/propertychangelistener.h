#ifndef PROPERTYCHANGELISTENER_H
#define PROPERTYCHANGELISTENER_H

#include <QObject>
#include "propertychangeevent.h"
#include <QStringList>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT PropertyChangeListener : public QObject
{
    Q_OBJECT
public:
 explicit PropertyChangeListener(QObject *parent = 0);
public slots:
 virtual void propertyChange(PropertyChangeEvent* e);
// {
//  //Q_UNUSED(e)
//  emit signalPropertyChange(e);
// }pnc

signals:
 void signalPropertyChange(PropertyChangeEvent* e);
public slots:
private:
    
};
Q_DECLARE_INTERFACE(PropertyChangeListener, "PropertyChangeListener")
#endif // PROPERTYCHANGELISTENER_H
