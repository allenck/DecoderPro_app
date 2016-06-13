#include "component.h"
#include "droptarget.h"

Component::Component(QObject *parent) :
    QObject(parent)
{
 peer = NULL;
 dropTarget = NULL;
}
/**
 * Associate a <code>DropTarget</code> with this component.
 * The <code>Component</code> will receive drops only if it
 * is enabled.
 *
 * @see #isEnabled
 * @param dt The DropTarget
 */

/*public*/ /*synchronized*/ void Component::setDropTarget(DropTarget* dt)
{
 if (dt == dropTarget || (dropTarget != NULL && dropTarget==(dt)))
  return;

 DropTarget* old = NULL;

 if ((old = dropTarget) != NULL)
 {
  if (peer != NULL) dropTarget->removeNotify((ComponentPeer*)peer);

  DropTarget* t = dropTarget;

  dropTarget = NULL;

  try
  {
   t->setComponent(NULL);
  }
  catch (IllegalArgumentException iae)
  {
            // ignore it.
  }
 }

  // if we have a new one, and we have a peer, add it!

  if ((dropTarget = dt) != NULL)
  {
        try {
            dropTarget->setComponent(this);
            if (peer != NULL) dropTarget->addNotify((ComponentPeer*)peer);
        } catch (IllegalArgumentException iae) {
            if (old != NULL) {
                try {
                    old->setComponent(this);
                    if (peer != NULL) dropTarget->addNotify((ComponentPeer*)peer);
                } catch (IllegalArgumentException iae1) {
                    // ignore it!
                }
            }
        }
    }
}

/**
 * Gets the <code>DropTarget</code> associated with this
 * <code>Component</code>.
 */

/*public*/ /*synchronized*/ DropTarget* Component::getDropTarget() { return dropTarget; }
