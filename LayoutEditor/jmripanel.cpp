#include "jmripanel.h"
#include "logger.h"
#include <QDesktopWidget>
#include <QApplication>
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "windowinterface.h"

JmriPanel::JmriPanel(QWidget *parent) :
    JPanel(parent)
{
 wi = nullptr;
 log = new Logger("JmriPanel");

 reuseFrameSavedPosition = true;
 reuseFrameSavedSized = true;
 windowFrameRef = "";
}

/**
 * JPanel extension to handle automatic creation
 * of window title and help reference.
 * <p>
 * For use with {@link JmriAbstractAction}
 * or preferably {@link JmriNamedPaneAction}.
 * <p>
 * The expected initialization sequence is:
 *<ol>
 *<li>The constructor, which can initialize internal
 *    variables, but shouldn't expose the object by
 *    installing any listeners, etc.
 *<li>initComponents() is called, which initializes
 *    Swing components and can make other external references.
 *<li>initContext(Object context) is called, which can
 *    make outside connections
 *<li>Optionally, other usage-specific initialization
 *    methods can be called to e.g. connect to
 *    protocol handlers.
 *</ol>
 *<p>
 * A {@link WindowInterface} property is provided for use
 * when the JmriPanel's controller logic wants to
 * pop a subwindow.
 *
 * @author Bob Jacobsen  Copyright 2010
 * @since 2.9.4
 * @version $Revision: 20968 $
 */

///*public*/ class JmriPanel extends JPanel {

/**
 * Provide a help target string which an enclosing
 * frame can provide as a help reference.
 *<p>
 * This automatically provides a reference to the usual
 * place for JMRI window-specific help pages that are named
 * for the implementing class, but note this is a Pane class,
 * not a Frame class.
 */
/*public*/ QString JmriPanel::getHelpTarget() { return tr("package.")+/*this.getClass().getName();*/ metaObject()->className();}

/**
 * Provide a recommended title for an enclosing frame.
 */
/*public*/ QString JmriPanel::getTitle() { return ""; }

/**
 * Can multiple instances of a specific
 * pane subclass exist?
 */
/*public*/ bool JmriPanel::isMultipleInstances() { return true; }

/**
 * Provide menu items
 */
/*public*/ QList<QMenu*> JmriPanel::getMenus() { return QList<QMenu*>(); }

/*public*/ WindowInterface* JmriPanel::getWindowInterface() {
    return wi;
}
/*public*/ void JmriPanel::setWindowInterface(WindowInterface* w)
{
 wi = w;
 setParent(wi->getFrame());
}

/**
 * 2nd stage of initialization, invoked after
 * the constuctor is complete.
 */
/*public*/ void JmriPanel::initComponents() /*throw (Exception)*/ {}

/**
 * 3rd stage of initialization, invoked after
 * Swing components exist.
 */
/*public*/ void JmriPanel::initContext(QObject* context) /*throw (Exception)*/ {}

/*public*/ void JmriPanel::dispose() {}
//}
/*public*/ void JmriPanel::pack()
{
 // work around for Linux, sometimes the stored window size is too small
 if (this->getPreferredSize().width() < 100 || this->size().height() < 100)
 {
  this->setMinimumSize(QSize(100,100)); // try without the preferred size
 }
 //super.pack();
 reSizeToFitOnScreen();
}
/**
 * Tries to get window to fit entirely on screen.  First choice is to
 * move the origin up and left as needed, then to make the
 * window smaller
 */
void JmriPanel::reSizeToFitOnScreen()
{
 QSize dim = getMaximumSize();
 int width = this->getPreferredSize().width();
 int height = this->getPreferredSize().height();
 if (log->isDebugEnabled()) log->debug("reSizeToFitOnScreen of \""+windowTitle()+"\" starts with maximum size "+QString::number(dim.width())+","+QString::number(dim.height()));
 if (log->isDebugEnabled()) log->debug("reSizeToFitOnScreen starts with preferred height "+QString::number(height)+" width "+QString::number(width));
 if (log->isDebugEnabled()) log->debug("reSizeToFitOnScreen starts with location "+QString::number(pos().x())+","+QString::number(pos().y()));

 if ((width+this->pos().x())>=dim.width())
 {
  // not fit in width, try to move position left
  int offsetX = (width+this->pos().x()) - (int)dim.width(); // pixels too large
  if (log->isDebugEnabled()) log->debug("reSizeToFitScreen moves \""+windowTitle()+"\" left "+QString::number(offsetX)+" pixels");
  int positionX = this->pos().x()-offsetX;
  if (positionX < 0)
  {
   if (log->isDebugEnabled()) log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" X to zero");
   positionX = 0;
  }
  this->move(positionX, this->pos().y());
  // try again to see if it doesn't fit
  if ((width + this->pos().x())>=dim.width())
  {
   width = width - (int)((width + this->pos().x())-dim.width());
   if (log->isDebugEnabled()) log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" width to "+QString::number(width));
  }
 }
 if ((height+this->pos().y())>=dim.height())
 {
  // not fit in height, try to move position up
  int offsetY = (height+this->pos().y()) - (int)dim.height(); // pixels too large
  if (log->isDebugEnabled()) log->debug("reSizeToFitScreen moves \""+windowTitle()+"\" up "+QString::number(offsetY)+" pixels");
  int positionY = this->pos().y()-offsetY;
  if (positionY < 0)
  {
   if (log->isDebugEnabled()) log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" Y to zero");
    positionY = 0;
  }
  this->move(this->pos().x(), positionY);
  // try again to see if it doesn't fit
  if ((height+this->pos().y())>=dim.height())
  {
   height = height - (int)((height + this->pos().y())-dim.height());
   if (log->isDebugEnabled()) log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" height to "+QString::number(height));
  }
 }
 this->resize(width, height);
 if (log->isDebugEnabled()) log->debug("reSizeToFitOnScreen sets width "+QString::number(width)+" height "+QString::number(height));
}
/**
 * Provide a maximum frame size that is limited
 * to what can fit on the screen after toolbars, etc
 * are deducted.
 *<P>
 * Some of the methods used here return NULL pointers
 * on some Java implementations, however, so
 * this will return the superclasses's maximum size
 * if the algorithm used here fails.
 */
/*public*/ QSize JmriPanel::getMaximumSize()
{
 // adjust maximum size to full screen minus any toolbars
// try
// {
  // Try our own alorithm.  This throws NULL-pointer exceptions on
  // some Java installs, however, for unknown reasons, so be
  // prepared to fall back.
//  try
//  {
   // First, ask for the physical screen size
   //Dimension screen = getToolkit().getScreenSize();
   QDesktopWidget* desktop = QApplication::desktop();
   QSize screen = desktop->screen()->size();

//            // Next, ask for any insets on the screen.
//            Insets insets = JmriInsets.getInsets();
//            int widthInset = insets.right+insets.left;
//            int heightInset = insets.top+insets.bottom;

//            // If insets are zero, guess based on system type
//            if (widthInset == 0 && heightInset == 0) {
//                String osName = SystemType.getOSName();
//                if (SystemType.isLinux()) {
//                    // Linux generally has a bar across the top and/or bottom
//                    // of the screen, but lets you have the full width.
//                    heightInset = 70;
//                }
//                // Windows generally has values, but not always,
//                // so we provide observed values just in case
//                else if (osName==("Windows XP") || osName==("Windows 98") || osName==("Windows 2000")) {
//                    heightInset = 28;  // bottom 28
//                }
//            }

//            // Insets may also be provided as system parameters
//            String sw = System.getProperty("jmri.inset.width");
//            if (sw!=NULL) try {
//                widthInset = Integer.parseInt(sw);
//            } catch (Exception e1) {log->error("Error parsing jmri.inset.width: "+e1);}
//            String sh = System.getProperty("jmri.inset.height");
//            if (sh!=NULL) try {
//                heightInset = Integer.parseInt(sh);
//            } catch (Exception e1) {log->error("Error parsing jmri.inset.height: "+e1);}

  int widthInset = 0;
  int heightInset = 0;
//  if(menuBar()!= NULL)
//   heightInset += menuBar()->height();
//  if(statusBar() != NULL)
//   heightInset+= statusBar()->height();

  // calculate size as screen size minus space needed for offsets
  if (log->isDebugEnabled()) log->debug("getMaximumSize returns normally   width:"+QString::number(screen.width()-widthInset)+", height:"+QString::number(screen.height()-heightInset));
  return  QSize(screen.width()-widthInset, screen.height()-heightInset);
// }
// catch (NoSuchMethodError e) {
//            Dimension screen = getToolkit().getScreenSize();
//            if (log->isDebugEnabled()) log->debug("getMaximumSize returns approx due to failure "+screen.width+","+screen.height);
//            return new Dimension(screen.width,
//                screen.height-45);  // approximate this->..
//        }
//    } catch (Exception e2) {
//        // failed completely, fall back to standard method
//        if (log->isDebugEnabled()) log->debug("getMaximumSize returns super due to failure "+super.getMaximumSize());
//        return super.getMaximumSize();
//    }
}

/**
 * The preferred size must fit on the physical screen, so
 * calculate the lesser of either the preferred size from the
 * layout or the screen size.
 */
/*public*/ QSize JmriPanel::getPreferredSize() {

 if (log->isDebugEnabled())
     log->debug("getPreferredSize (sizeHint) returns width "+QString::number(sizeHint().width())+" height "+QString::number(sizeHint().height()));
 return sizeHint();
}

/**
 * Set whether the frame Position is saved or not after it has been created.
 */
/*public*/ void JmriPanel::setSavePosition(bool save){
    reuseFrameSavedPosition=save;
    UserPreferencesManager* prefsMgr = (UserPreferencesManager* )InstanceManager::getDefault("UserPreferencesManager");
    if (prefsMgr != nullptr) {
        prefsMgr->setSaveWindowLocation(windowFrameRef, save);
    } else {
        log->warn("setSavePosition() UserPreferencesManager() not initialised" );
    }
}

/*public*/ void JmriPanel::setFrameLocation()
{
 UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if ((prefsMgr != nullptr) && (prefsMgr->isWindowPositionSaved(windowFrameRef)))
 {
  //QSize screen = getToolkit().getScreenSize();
  QDesktopWidget* desktop = QApplication::desktop();
  QSize screen = desktop->screen()->size();
  if ((reuseFrameSavedPosition) && (!((prefsMgr->getWindowLocation(windowFrameRef).x()>=screen.width()) ||
            (prefsMgr->getWindowLocation(windowFrameRef).y()>=screen.height()))))
  {
   if (log->isDebugEnabled()) log->debug("setFrameLocation 1st clause sets location to "+QString::number(prefsMgr->getWindowLocation(windowFrameRef).x()) + ","+QString::number(prefsMgr->getWindowLocation(windowFrameRef).y()));
   this->move(prefsMgr->getWindowLocation(windowFrameRef));
  }

  /* Simple case that if either height or width are zero, then we should
        not set them */
  if ((reuseFrameSavedSized) &&(!((prefsMgr->getWindowSize(windowFrameRef).width()==0.0) || (prefsMgr->getWindowSize(windowFrameRef).height()==0.0))))
  {
#ifdef Q_OS_LINUX
   if (log->isDebugEnabled())
    log->debug("setFrameLocation 2nd clause sets preferredSize to "+QString::number(prefsMgr->getWindowSize(windowFrameRef).width()) + ","+QString::number(prefsMgr->getWindowSize(windowFrameRef).height()));
   this->resize(prefsMgr->getWindowSize(windowFrameRef));
#endif
#ifdef Q_OS_WIN32
  if (log->isDebugEnabled()) log->debug("setFrameLocation 2nd clause sets size to "+QString::number(prefsMgr->getWindowSize(windowFrameRef).width()) + ","+QString::number(prefsMgr->getWindowSize(windowFrameRef).height()));
            //this->set(prefsMgr->getWindowSize(windowFrameRef));
#endif
  }
#if 0
  /* We just check to make sure that having set the location
  that we do not have anther frame with the same class name and title
  in the same location, if it is we offset */
  for(int i = 0; i<frameList->size();i++)
  {
   JmriJFrame* j = frameList->at(i);
   if(j->getClassName()== getClassName()  && (j->isMinimized()) && (j->isVisible())
           && j->windowTitle()==(windowTitle()))
   {
    if ((j->pos().x()==this->pos().x()) && (j->pos().y()==this->pos().y()))
    {
     if (log->isDebugEnabled()) log->debug("setFrameLocation 3rd clause calls offSetFrameOnScreen("+j->windowTitle()+")");
     offSetFrameOnScreen(j);
    }
   }
  }
#endif
 }
}

void JmriPanel::moveEvent(QMoveEvent*)
{
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if ((p != nullptr) && (reuseFrameSavedPosition) && isVisible()) {
     p->setWindowLocation(windowFrameRef, this->pos());
 }

}

void JmriPanel::resizeEvent(QResizeEvent*)
{
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if ((p != nullptr) && (reuseFrameSavedSized) && isVisible()) {
     saveWindowSize(p);
 }

}

/*private*/ void JmriPanel::saveWindowSize(UserPreferencesManager* p) {
//        if (SystemType.isLinux()) {
//            // try to determine if user has resized the window
//            log.debug("getSize() width: {}, height: {}", super.getSize().getWidth(), super.getSize().getHeight());
//            log.debug("getPreferredSize() width: {}, height: {}", super.getPreferredSize().getWidth(), super.getPreferredSize().getHeight());
//            if (Math.abs(super.getPreferredSize().getWidth() - (super.getSize().getWidth() + 4)) > 5
//                    || Math.abs(super.getPreferredSize().getHeight() - (super.getSize().getHeight() + 3)) > 5) {
//                // adjust the new window size to be slight wider and higher than actually returned
//                Dimension size = new Dimension((int) super.getSize().getWidth() + 4, (int) super.getSize().getHeight() + 3);
//                log.debug("setting new window size {}", size);
//                p.setWindowSize(windowFrameRef, size);
//            } else {
//                p.setWindowSize(windowFrameRef, super.getPreferredSize());
//            }
//        } else {
        p->setWindowSize(windowFrameRef, /*super.getSize()*/size());
//        }
}
/*public*/ void JmriPanel::setFrameRef(QString initref)
{
 int refNo = 1;
 QString ref = initref;
#if 0
 for(int i = 0; i<frameList->size();i++)
 {
  JmriJFrame* j = frameList->at(i);
  if(j == nullptr)
   continue;
  if(j!=this && j->getWindowFrameRef()==(ref))
  {
      ref = initref+":"+QString::number(refNo);
      refNo++;
  }
 }
#endif
 this->windowFrameRef = ref;
 setFrameLocation();
}
