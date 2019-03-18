#ifndef POPUPMENULISTENER_H
#define POPUPMENULISTENER_H
#include "eventlistener.h"
#include "popupmenuevent.h"

/*public*/ /*interface*/class PopupMenuListener : public  EventListener {
Q_OBJECT
public:
 PopupMenuListener() {}
 /*public*/ virtual void popupMenuWillBecomeVisible(PopupMenuEvent* /*e*/) {}

 /*public*/ virtual void popupMenuWillBecomeInvisible(PopupMenuEvent* /*e*/) {}

 /*public*/ virtual void popupMenuCanceled(PopupMenuEvent* /*e*/) {}
};

Q_DECLARE_INTERFACE(PopupMenuListener, "PopupMenuListener")
#endif // POPUPMENULISTENER_H
