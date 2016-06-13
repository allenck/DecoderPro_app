#ifndef DROPTARGETEVENT_H
#define DROPTARGETEVENT_H
#include <QDropEvent>
#include <QObject>

class DropTargetContext;
class DropTargetEvent : public QObject
{
 Q_OBJECT
public:
    /*public*/ DropTargetEvent(DropTargetContext* dtc);
    /*public*/ DropTargetContext* getDropTargetContext();
protected:
   /*protected*/ DropTargetContext*   context;
};

#endif // DROPTARGETEVENT_H
