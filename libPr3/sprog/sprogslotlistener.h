#ifndef SPROGSLOTLISTENER_H
#define SPROGSLOTLISTENER_H
#include "eventlistener.h"
#include "sprogslot.h"

namespace Sprog
{
/**
 * [describe the SlotListener class here]
 *
 * @author Bob Jacobsen Copyright (C) 2001 Andrew Crosland (c) 2006 ported for
 * SPROG
 */
/*public*/ /*interface*/class SprogSlotListener : public EventListener {
 Q_OBJECT
public:
 SprogSlotListener();
public slots:
    // This and the Loconet equivalent should probably be re-factored
    // to a higher place in the hierarchy
 virtual /*public*/ void notifyChangedSlot(SprogSlot* /*s*/) {}
};
}
#endif // SPROGSLOTLISTENER_H
