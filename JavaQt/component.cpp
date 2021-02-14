#include "component.h"
#include "droptarget.h"
#include "droptargetlistener.h"
#include <QBoxLayout>

Component::Component(QWidget *parent) :  JPanel(parent)
{
 peer = NULL;
 dropTarget = NULL;
 setLayout(new QVBoxLayout);
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

 DropTarget* old = dropTarget;

 if (old != NULL)
 {
  if (peer != NULL) dropTarget->removeNotify((ComponentPeer*)peer);

  DropTarget* t = dropTarget;

  dropTarget = NULL;

//  try
//  {
  if(t != NULL)
   t->setComponent(NULL);
//  }
//  catch (IllegalArgumentException iae)
//  {
//            // ignore it.
//  }
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

void Component::dragEnterEvent(QDragEnterEvent * e)
{
 if(dropTarget != NULL)
 {
  if(dropTarget->getListener() != NULL)
  {
   dropTarget->getListener()->dragEnter(e);
  }
 }
}

void Component::dropEvent(QDropEvent *e)
{
 if(dropTarget != NULL)
 {
  if(dropTarget->getListener() != NULL)
  {
   dropTarget->getListener()->drop(e);
  }
 }
}
