#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT EventListener :public QObject
{
public:
 EventListener();
    
};
Q_DECLARE_INTERFACE(EventListener, "EventListener")
#endif // EVENTLISTENER_H
