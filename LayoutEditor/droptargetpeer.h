#ifndef DROPTARGETPEER_H
#define DROPTARGETPEER_H
#include <QObject>

class DropTarget;
class DropTargetPeer : public QObject
{
  Q_OBJECT
public:
    DropTargetPeer() {}
/**
 * Add the DropTarget to the System
 *
 * @param dt The DropTarget effected
 */

virtual void addDropTarget(DropTarget* /*dt*/) {}

/**
 * Remove the DropTarget from the system
 *
 * @param dt The DropTarget effected
 */

virtual void removeDropTarget(DropTarget* /*dt*/) {}
    friend class DropTarget;
};

#endif // DROPTARGETPEER_H
