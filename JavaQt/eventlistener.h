#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT EventListener //:public QObject
{
 //Q_OBJECT
public:
 //EventListener(QObject* parent = nullptr);
 virtual QObject* self() = 0;
    
};
Q_DECLARE_INTERFACE(EventListener, "EventListener")
#endif // EVENTLISTENER_H
