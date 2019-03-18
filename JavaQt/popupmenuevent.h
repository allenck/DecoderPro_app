#ifndef POPUPMENUEVENT_H
#define POPUPMENUEVENT_H
#include "eventobject.h"

/*public*/ class PopupMenuEvent : public EventObject {

 Q_OBJECT
public:
    /*public*/ PopupMenuEvent(QObject* source) : EventObject(source){
        // compiled code
    }
private:
};
#endif // POPUPMENUEVENT_H
