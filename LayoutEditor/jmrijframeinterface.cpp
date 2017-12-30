#include "jmrijframeinterface.h"
#include <jmrijframe.h>
#include "jmripanel.h"
#include "QMenuBar"
#include "windowinterface.h"
#include "panelmenu.h"

JmriJFrameInterface::JmriJFrameInterface(QWidget *parent) :   WindowInterface(parent)
{
 frames =  QHash<JmriPanel*, JmriJFrame*>();
}
/**
 * Display a JmriPanel in a JFrame of its own.
 *
 * Dispose() of a multi-instance panel is invoked when the containing window is fully closed
 * via a listener installed here. Single instance (non-multi-instance)
 * panels are cached and never disposed.
 *
 * @author Bob Jacobsen  Copyright 2010
 * @since 2.9.4
 * @version $Revision: 21373 $
 */

// /*public*/ class JmriJFrameInterface implements jmri.util.swing.WindowInterface {


/*public*/ void JmriJFrameInterface::show(
     /*final*/ JmriPanel* child,
               QAction* /*act*/,
               Hint /*hint*/)
{

 // display cached frame if available
 JmriJFrame* frame = frames.value(child);
 if (frame != NULL)
 {
  frame->setVisible(true);
  return;
 }

 // create frame
 frame = new JmriJFrame("<JmriJFrameInterface>");

 // cache if single instance
 if ( !child->isMultipleInstances())
  frames.insert(child, frame);
 child->setVisible(true);

 // add gui object, responsible for own layout
 //frame.add(child);
 frame->setCentralWidget(child);

 // add menus if requested
 QList<QMenu*> list = child->getMenus();
 if (!list.isEmpty())
 {
  QMenuBar* bar = frame->menuBar();
  if (bar == NULL) bar = new QMenuBar();
  foreach (QMenu* menu, list)
  {
   bar->addMenu(menu);
  }
  frame->setMenuBar(bar);
 }

 // add help menu if requested
 if (child->getHelpTarget() != NULL)
  frame->addHelpMenu(child->getHelpTarget(), true);

 // set title if available
 if (child->getTitle() != NULL)
  frame->setTitle(child->getTitle());

 // if multi-instance, arrange to run dispose on close
 if ( child->isMultipleInstances())
 {
//  frame.addWindowListener( new java.awt.event.WindowAdapter(){
//            jmri.util.swing.JmriPanel c;
//            { c = child; }
//            /*public*/ void windowClosed(java.awt.event.WindowEvent e) {
//                c.dispose();
//            }
//        });
 }
 FIWindowListener* windowListener = new FIWindowListener( child, this);
 frame->addWindowListener(windowListener);
 PanelMenu::instance()->addEditorPanel((Editor*)frame);
 // pack and show
 frame->setVisible(true);
 frame->setLocation(10, 100);
 frame->adjustSize();
}
FIWindowListener::FIWindowListener(JmriPanel* c, JmriJFrameInterface * _interface)
{
this->c = c;
}
/*public*/ void FIWindowListener::windowClosing(QCloseEvent *e)
{
 c->dispose();
}

/*public*/ void JmriJFrameInterface::show(/*final*/ JmriPanel* child, QAction* act)
{
 show(child, act, WindowInterface::DEFAULT);
}

/**
 * Create new windows on each request
 */
/*public*/ bool JmriJFrameInterface::multipleInstances() { return true; }

/*public*/ void JmriJFrameInterface::dispose() {}

//@Override
/*public*/ JFrame* JmriJFrameInterface::getFrame()
{
 return NULL;
}
