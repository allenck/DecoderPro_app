#ifndef CLIPBOARDEVENTLISTENER_H
#define CLIPBOARDEVENTLISTENER_H
#include "eventlistener.h"

/*public*/ /*interface*/class  ClipboardEventListener : public EventListener {
        Q_INTERFACES(EventListener)
 public:
    /*public*/ virtual void clipboardEventOccurred()=0;

};
Q_DECLARE_INTERFACE(ClipboardEventListener, "ClipboardEventListener")
#endif // CLIPBOARDEVENTLISTENER_H
