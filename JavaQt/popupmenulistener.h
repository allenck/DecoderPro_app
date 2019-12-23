#ifndef POPUPMENULISTENER_H
#define POPUPMENULISTENER_H
#include "eventlistener.h"
#include "popupmenuevent.h"

/*public*/ /*interface*/class PopupMenuListener : public QObject, public  EventListener {
Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 PopupMenuListener() {}
 QObject* self() {return (QObject*)this;}

 /*public*/ virtual void popupMenuWillBecomeVisible(PopupMenuEvent* /*e*/) {}

 /*public*/ virtual void popupMenuWillBecomeInvisible(PopupMenuEvent* /*e*/) {}

 /*public*/ virtual void popupMenuCanceled(PopupMenuEvent* /*e*/) {}
};

#endif // POPUPMENULISTENER_H
