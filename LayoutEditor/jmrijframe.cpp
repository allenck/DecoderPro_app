#include "jmrijframe.h"
#include "windowlistener.h"
#include "layouteditortools.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "jmriuserpreferencesmanager.h"
#include "abstractshutdowntask.h"
#include <QMessageBox>
#include "windowmenu.h"
#include "helputil.h"
#include "panelmenu.h"
#include "jmrijframeinterface.h"
#include "rostergroupselector.h"

//JmriJFrame::JmriJFrame(QWidget *parent) :
//    QMainWindow(parent)
//{
//}
/*static*/ /*volatile*/ QList<JmriJFrame*>* JmriJFrame::frameList =  new QList<JmriJFrame*>();
/**
 * JFrame extended for common JMRI use.
 * <P>
 * We needed a place to refactor common JFrame additions in JMRI
 * code, so this class was created.
 * <P>
 * Features:
 * <ul>
 * <LI>Size limited to the maximum available on the screen, after
 * removing any menu bars (Mac) and taskbars (Windows)
 * <LI>Cleanup upon closing the frame: When the
 * frame is closed (WindowClosing event), the
 * dispose() method is invoked to do cleanup. This is
 * inherited from JFrame itself, so super.dispose() needs
 * to be invoked in the over-loading methods.
 * <LI>Maintains a list of existing JmriJFrames
 * </ul>
 *
 * <h3>Window Closing</h3>
 * Normally, a JMRI window wants to be disposed when it closes.
 * This is what's needed when each invocation of the corresponding action
 * can create a new copy of the window.  To do this, you don't have
 * to do anything in your subclass.  This class has
<p><pre><code>
 setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE)
</code></pre>
 * <p>If you want this behavior, but need to do something when the
 * window is closing, override the {@link #windowClosing(java.awt.event.WindowEvent)} method
 * to do what you want. Also, if you override dispose(),
 * make sure to call super.dispose().
 * <p>
 * If you want the window to just do nothing or just hide, rather than be disposed,
 * when closed, set the DefaultCloseOperation to
 * DO_NOTHING_ON_CLOSE or HIDE_ON_CLOSE depending on what you're looking for.
 *
 * @author Bob Jacobsen  Copyright 2003, 2008
 * @version $Revision: 22611 $
 * GT 28-AUG-2008 Added window menu
 */

///*public*/ class JmriJFrame extends JFrame implements java.awt.event.WindowListener, jmri.ModifiedFlag, java.awt.event.ComponentListener, WindowInterface, BeanInterface {

/**
 * Creates a JFrame with standard settings, optional
 * save/restore of size and position.
 * @param saveSize - Set true to save the last known size
 * @param savePosition - Set true to save the last known location
 */
/*public*/ JmriJFrame::JmriJFrame(bool saveSize, bool savePosition, QWidget *parent) : JFrame(parent)
{
//super();
 init(saveSize, savePosition);
}

/**
 * Creates a JFrame with standard settings, including
 * saving/restoring of size and position.
 */
/*public*/ JmriJFrame::JmriJFrame(QWidget *parent) : JFrame(parent)  {
    //this(true, true);
 init(true, true);
}

/**
 * Creates a JFrame with with given name plus standard settings, including
 * saving/restoring of size and position.
 * @param name - Title of the JFrame
 */
/*public*/ JmriJFrame::JmriJFrame(QString name, QWidget *parent)
    : JFrame(name, parent)
{
 setWindowTitle(name);
 init(true, true);
 //this(name, true, true);
// generateWindowRef();
// if (metaObject()->className()==("JmriJFrame"))
// {
//  if ((this->windowTitle() == "") || (this->windowTitle() == (""))) {
//      return;
//  }
// }
// setFrameLocation();
}

/**
 * Creates a JFrame with with given name plus standard settings, including
 * optional save/restore of size and position.
 * @param name - Title of the JFrame
 * @param saveSize - Set true to save the last knowm size
 * @param savePosition - Set true to save the last known location
 */
/*public*/ JmriJFrame::JmriJFrame(QString name, bool saveSize, bool savePosition, QWidget *parent) : JFrame(parent)
{
 //this(saveSize, savePosition);
 init(saveSize, savePosition);

 setTitle(name);
#if 1
 generateWindowRef();
 if (QString(metaObject()->className())==("JmriJFrame")){
     if ((this->windowTitle()==NULL) || (this->windowTitle()==("")))
         return;
 }
 setFrameLocation();
#endif
}

/*public*/ JmriJFrame::~JmriJFrame()
{
 dispose();
}

void JmriJFrame::init(bool saveSize, bool savePosition)
{
 log = new Logger("JmriJFrame");
 setVisible(true);
 //reuseFrameSavedPosition = true;
 //reuseFrameSavedSized = true;

 allowInFrameServlet = true;
 properties = new QMap<QString, QVariant>();
 QDesktopWidget* w = QApplication::desktop();
 //setMinimumSize(100,20); // already done in JFrame!
 setLocation(20,50);
 setMaximumHeight(w->height() - 100);
 task = NULL;
 modifiedFlag = false;
 windowMenu = NULL;
 installEventFilter(this);
 mShown = false;

 reuseFrameSavedPosition=savePosition;
 reuseFrameSavedSized=saveSize;

 addWindowListener(new JmriJFrameWindowListener(this));

// TODO: addComponentListener(this);
 windowInterface = new JmriJFrameInterface();
#if 0  // TODO:
 /* This ensures that different jframes do not get placed directly on top
 of each other, but offset by the top inset.  However a saved preferences
 can over ride this */
 for(int i = 0; i<list.size();i++){
     JmriJFrame* j = list.get(i);
     if((j->getExtendedState()!=ICONIFIED) && (j->isVisible())){
         if ((j->getX()==this->getX()) && (j->getY()==this->getY())){
             offSetFrameOnScreen(j);
         }
     }
 }
#endif
 /*synchronized (list)*/ {
  QPointer<JmriJFrame> frame = this;
     frameList->append(frame);
  if(frameList->size() >= 78)
  {
   qDebug() << tr("frameList size = %1").arg(frameList->size());
  }
 }
 // Set the image for use when minimized
 //setIconImage(getToolkit().getImage("resources/jmri32x32.gif"));
 setWindowIcon(QIcon(":/resources/jmri32x32.gif"));
 // set the close short cut
 setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
// TODO:    addWindowCloseShortCut();

// windowFrameRef = getClassName(); //metaObject()->className();
// if (metaObject()->className()!=("JmriJFrame"))
// {
//     generateWindowRef();
//     setFrameLocation();
// }
}

/*
 * This method should be overriden to provide the full java classname
 * so that preferences can be stored in a manner that either this app or the original
 * Java code can interpret save preferences equally.
/*public*/ QString JmriJFrame::getClassName()
{
 return QString(metaObject()->className());
}

/**
  * This function does not exist in the original JMRI Java code. Because C++ subclasses
  * are not yet constructed when JmriJFrame is the superclass, the classname that is
  * returned while performing the constructor does not refelect the ultimate classname.
  * Therefore, this function should be called preferably with the original java class
  * name for the subclass. That way, preferences will refer to the correct class when
  * JRMI (java version) uses these preferences.
  *
  * This function will insure that size and location are saved for the subclass in
  * the preferences.
  * /
/*public*/ void JmriJFrame::setFrameRef(QString initref)
{
 int refNo = 1;
 QString ref = initref;

 for(int i = 0; i<frameList->size();i++)
 {
  JmriJFrame* j = frameList->at(i);
  if(j == NULL)
   continue;
  if(j!=this && j->getWindowFrameRef()==(ref))
  {
      ref = initref+":"+QString::number(refNo);
      refNo++;
  }
 }
 this->windowFrameRef = ref;
 setFrameLocation();
}

#if 1
/**
 * Remove this window from e.g. the Windows Menu
 * by removing it from the list of active JmriJFrames
 */
/*public*/ void JmriJFrame::makePrivateWindow() {
//    synchronized (list) {
        frameList->removeOne(this);
//    }
}
#endif
void JmriJFrame::setFrameLocation()
{
 UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if ((prefsMgr != NULL) && (prefsMgr->isWindowPositionSaved(windowFrameRef)))
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
  if ((reuseFrameSavedSized) &&(!((prefsMgr->getWindowSize(windowFrameRef).width()==0.0) ||
            (prefsMgr->getWindowSize(windowFrameRef).height()==0.0))))
  {
#ifdef Q_OS_LINUX
   if (log->isDebugEnabled()) log->debug("setFrameLocation 2nd clause sets preferredSize to "+QString::number(prefsMgr->getWindowSize(windowFrameRef).width()) + ","+QString::number(prefsMgr->getWindowSize(windowFrameRef).height()));
            this->setMinimumSize(prefsMgr->getWindowSize(windowFrameRef));
#endif
#ifdef Q_OS_WIN32
  if (log->isDebugEnabled()) log->debug("setFrameLocation 2nd clause sets size to "+QString::number(prefsMgr->getWindowSize(windowFrameRef).width()) + ","+QString::number(prefsMgr->getWindowSize(windowFrameRef).height()));
            //this->set(prefsMgr->getWindowSize(windowFrameRef));
#endif
  }

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
 }
}

/**
 * Regenerates the window frame ref that is used for saving and setting
 * frame size and position against.
 */
/*public*/ void JmriJFrame::generateWindowRef()
{
 QString initref = metaObject()->className();
 if(this->windowTitle()!=(""))
 {
  if (initref==("JmriJFrame"))
  {
      initref=this->windowTitle();
  } else {
      initref = initref + ":" + this->windowTitle();
  }
 }
 int refNo = 1;
 QString ref = initref;
 for(int i = 0; i<frameList->size();i++)
 {
  JmriJFrame* j = frameList->at(i);
  if(j == NULL)
   continue;
  if(j != this && j->getWindowFrameRef() == (ref))
  {
      ref = initref+":"+QString::number(refNo);
      refNo++;
  }
 }
 windowFrameRef = ref;
}

//@Override
///*public*/ void JmriJFrame::pack()
//{
// // work around for Linux, sometimes the stored window size is too small
// if (this->getPreferredSize().width() < 100 || this->getPreferredSize().height() < 100)
// {
//  this->setMinimumSize(QSize(100,100)); // try without the preferred size
// }
// //super.pack();
// reSizeToFitOnScreen();
//}

/**
 * Tries to get window to fix entirely on screen.  First choice is to
 * move the origin up and left as needed, then to make the
 * window smaller
 */
void JmriJFrame::reSizeToFitOnScreen()
{
 QSize dim = getMaximumSize();
 int width = this->getPreferredSize().width();
 int height = this->getPreferredSize().height();
 if (log->isDebugEnabled())
  log->debug("reSizeToFitOnScreen of \""+windowTitle()+"\" starts with maximum size "+QString::number(dim.width())+","+QString::number(dim.height()));
 if (log->isDebugEnabled())
  log->debug("reSizeToFitOnScreen starts with preferred width "+QString::number(width)+" height "+QString::number(height));
 if (log->isDebugEnabled())
  log->debug("reSizeToFitOnScreen starts with location "+QString::number(pos().x())+","+QString::number(pos().y()));

 if ((width+this->pos().x())>=dim.width())
 {
  // not fit in width, try to move position left
  int offsetX = (width+this->pos().x()) - (int)dim.width(); // pixels too large
  if (log->isDebugEnabled())
   log->debug("reSizeToFitScreen moves \""+windowTitle()+"\" left "+QString::number(offsetX)+" pixels");
  int positionX = this->pos().x()-offsetX;
  if (positionX < 0)
  {
   if (log->isDebugEnabled())
    log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" X to zero");
   positionX = 0;
  }
  this->move(positionX, this->pos().y());
  // try again to see if it doesn't fit
  if ((width + this->pos().x())>=dim.width())
  {
   width = width - (int)((width + this->pos().x())-dim.width());
   if (log->isDebugEnabled())
    log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" width to "+QString::number(width));
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
   if (log->isDebugEnabled())
    log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" Y to zero");
   positionY = 0;
  }
  this->move(this->pos().x(), positionY);
  // try again to see if it doesn't fit
  if ((height+this->pos().y())>=dim.height())
  {
   height = height - (int)((height + this->pos().y())-dim.height());
   if (log->isDebugEnabled())
    log->debug("reSizeToFitScreen sets \""+windowTitle()+"\" height to "+QString::number(height));
  }
 }
 this->resize(width, height);
 if (log->isDebugEnabled())
  log->debug("reSizeToFitOnScreen sets height "+QString::number(height)+" width "+QString::number(width));
}

void JmriJFrame::offSetFrameOnScreen(JmriJFrame* f)
{
/* We use the frame that we are moving away from insets, as at this point
our own insets have not been correctly built and always return a size of zero */
//    int frameOffSetx = this->pos().x()+f->getInsets().top;
//    int frameOffSety = this->pos().y()+f->getInsets().top;
 int frameOffSetx = this->pos().x()+20;
 int frameOffSety = this->pos().y()+20;

    QSize dim = maximumSize();

    if (frameOffSetx>=(dim.width()*0.75)){
        frameOffSety = 0;
        frameOffSetx = (/*f.getInsets().top*/20)*2;
    }
    if (frameOffSety>=(dim.height()*0.75)){
        frameOffSety = 0;
        frameOffSetx = (/*f.getInsets().top*/20)*2;
    }
    /* If we end up with our off Set of X being greater than the width of the
    screen we start back at the beginning but with a half offset */
    if (frameOffSetx>=dim.width())
        frameOffSetx=/*f.getInsets().top*/20/2;
    this->move(frameOffSetx, frameOffSety);
}


/*public*/ QString JmriJFrame::getWindowFrameRef(){ return windowFrameRef; }

/**
 * By default, Swing components should be
 * created an installed in this method, rather than
 * in the ctor itself.
 */
/*public*/ void JmriJFrame::initComponents() /*throw (Exception)*/
{
 windowFrameRef = getClassName(); //metaObject()->className();
 if (windowFrameRef!=("JmriJFrame"))
 {
     generateWindowRef();
     setFrameLocation();
 }
}

/**
 * Add a standard help menu, including window specific help item.
 * @param ref JHelp reference for the desired window-specific help page
 * @param direct true if the help menu goes directly to the help system,
 *        e.g. there are no items in the help menu
 */
/*public*/ void JmriJFrame::addHelpMenu(QString ref, bool direct)
{
 // only works if no menu present?
 QMenuBar* bar = menuBar();
// if (bar == NULL)
//   bar = new QMenuBar();
 // add Window menu

 bar->addMenu(windowMenu = new WindowMenu((WindowInterface*)this,this));
 //connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));// * GT 28-AUG-2008 Added window menu
    // add Help menu
 HelpUtil::instance()->helpMenu(bar, ref, direct);
 //bar->addMenu(new QMenu(tr("Help")));
 //setMenuBar(bar);
}
//void JmriJFrame::on_menuWindow_aboutToShow()
//{
// if(WindowMenu != NULL)
// {
//  windowMenu->clear();
//  PanelMenu::instance()->updatePanelMenu(windowMenu);
// }
//}

#if 0
/**
 * Adds a "Close Window" key short cut to close window on op-W.
 */
void addWindowCloseShortCut() {
    // modelled after code in JavaDev mailing list item by Bill Tschumy <bill@otherwise.com> 08 Dec 2004
    AbstractAction act = new AbstractAction() {
        /*public*/ void actionPerformed(ActionEvent e) {
            // if (log->isDebugEnabled()) log->debug("keystroke requested close window "+JmriJFrame.this->windowTitle());
            JmriJFrame.this->processWindowEvent(
                new java.awt.event.WindowEvent(JmriJFrame.this,
                                            java.awt.event.WindowEvent.WINDOW_CLOSING));
        }
    };
    getRootPane().getActionMap().put("close", act);

    int stdMask = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
    InputMap im = getRootPane().getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);

    // We extract the modifiers as a string, then add the I18N string, and
    // build a key code
    String modifier = KeyStroke.getKeyStroke(KeyEvent.VK_W, stdMask).toString();
    String keyCode = modifier.substring(0, modifier.length()-1)+Bundle.getMessage("VkKeyWindowClose").substring(0,1);

    im.put(KeyStroke.getKeyStroke(keyCode), "close"); // NOI18N
    //im.put(KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "close");
}

private static String escapeKeyAction = "escapeKeyAction";
private bool escapeKeyActionClosesWindow = false;

/**
 * Bind an action to the Escape key.
 * <p>
 * Binds an AbstractAction to the Escape key. If an action is already
 * bound to the Escape key, that action will be replaced. Passing
 * <code>NULL</code> unbinds any existing actions from the Escape key.
 * <p>
 * Note that binding the Escape key to any action may break expected or
 * standardized behaviors. See <a href="http://java.sun.com/products/jlf/ed2/book/Appendix.A.html">Keyboard
 * Shortcuts, Mnemonics, and Other Keyboard Operations</a> in the Java Look
 * and Feel Design Guidelines for standardized behaviors.
 * @param action The AbstractAction to bind to.
 * @see #getEscapeKeyAction()
 * @see #setEscapeKeyClosesWindow(bool)
 */
/*public*/ void setEscapeKeyAction(AbstractAction action) {
    JRootPane root = this->getRootPane();
    KeyStroke escape = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
    escapeKeyActionClosesWindow = false; // setEscapeKeyClosesWindow will set to true as needed
    if (action != NULL) {
        root.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(escape, escapeKeyAction);
        root.getActionMap().put(escapeKeyAction, action);
    } else {
        root.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).remove(escape);
        root.getActionMap().remove(escapeKeyAction);
    }
}

/**
 * The action associated with the Escape key.
 *
 * @return An AbstractAction or NULL if no action is bound to the
 * Escape key.
 * @see #setEscapeKeyAction(javax.swing.AbstractAction)
 * @see javax.swing.AbstractAction
 */
/*public*/ AbstractAction getEscapeKeyAction() {
    return (AbstractAction) this->getRootPane().getActionMap().get(escapeKeyAction);
}

/**
 * Bind the Escape key to an action that closes the window.
 * <p>
 * If closesWindow is true, this method creates an action that triggers the
 * "window is closing" event; otherwise this method removes any actions from
 * the Escape key.
 *
 * @param closesWindow Create or destroy an action to close the window.
 * @see java.awt.event.WindowEvent#WINDOW_CLOSING
 * @see #setEscapeKeyAction(javax.swing.AbstractAction)
 */
/*public*/ void setEscapeKeyClosesWindow(bool closesWindow) {
    if (closesWindow) {
        setEscapeKeyAction(new AbstractAction() {

            /*public*/ void actionPerformed(ActionEvent ae) {
                JmriJFrame.this->processWindowEvent(
                        new java.awt.event.WindowEvent(JmriJFrame.this,
                        java.awt.event.WindowEvent.WINDOW_CLOSING));
            }
        });
    } else {
        setEscapeKeyAction(NULL);
    }
    escapeKeyActionClosesWindow = closesWindow;
}

/**
 * Does the Escape key close the window?
 * @return <code>true</code> if Escape key is bound to action created by
 * setEscapeKeyClosesWindow, <code>false</code> in all other cases.
 * @see #setEscapeKeyClosesWindow
 * @see #setEscapeKeyAction
 */
/*public*/ bool getEscapeKeyClosesWindow() {
    return (escapeKeyActionClosesWindow && getEscapeKeyAction() != NULL);
}
#endif
#if 0
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
/*public*/ QSize JmriJFrame::getMaximumSize()
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
  if(menuBar()!= NULL)
   heightInset += menuBar()->height();
  if(statusBar() != NULL)
   heightInset+= statusBar()->height();

  // calculate size as screen size minus space needed for offsets
  if (log->isDebugEnabled()) log->debug("getMaximumSize returns normally "+QString::number(screen.width()-widthInset)+","+QString::number(screen.height()-heightInset));
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
/*public*/ QSize JmriJFrame::getPreferredSize()
{
 #if 0
 // limit preferred size to size of screen (from getMaximumSize())
 QSize screen = getMaximumSize();
 int width = qMin(size().width(), screen.width());
 int height = qMin(size().height(), screen.height());
 if (log->isDebugEnabled())
   log->debug("getPreferredSize returns width "+QString::number(width)+" height "+QString::number(height));
 return  QSize(width, height);
#else

  if (log->isDebugEnabled())
      log->debug("getPreferredSize (sizeHint) returns width "+QString::number(sizeHint.width())+" height "+QString::number(sizeHint.height()));
  return sizeHint();
#endif
}
#endif
/**
 * Get a List of the currently-existing JmriJFrame objects.
 * The returned list is a copy made at the time of the call,
 * so it can be manipulated as needed by the caller.
 */
/*public*/ /*static*/ QList<JmriJFrame*>* JmriJFrame::getFrameList()
{
    QMutex mutex;
    QList<JmriJFrame*>* returnList;
    /*synchronized(list)*/ {
        QMutexLocker locker(&mutex);
        returnList = new QList<JmriJFrame*>(*frameList);
    }
    return returnList;
}
#if 0
/**
 * Get a list of currently-existing JmriJFrame objects that are
 * specific sub-classes of JmriJFrame.
 * <p>
 * The returned list is a copy made at the time of the call,
 * so it can be manipulated as needed by the caller.
 * <p>
 * If subClass is NULL, returns a list of all JmriJFrames.
 *
 * @param subClass The Class the list should be limited to.
 * @return An ArrayList of Frames.
 */
// this probably should use and return a generic type
/*public*/ static java.util.List<JmriJFrame> getFrameList(Class<?> subClass) {
    if (subClass == NULL) {
        return JmriJFrame.getFrameList();
    }
    java.util.List<JmriJFrame> result = new ArrayList<JmriJFrame>();
    synchronized(list) {
        for (JmriJFrame f : list) {
            if (subClass.isInstance(f)) {
                result.add(f);
            }
        }
    }
    return result;
}
#endif
/**
 * Get a JmriJFrame of a particular name.
 * If more than one exists, there's no guarantee
 * as to which is returned.
 */
/*public*/ /*static*/ JmriJFrame* JmriJFrame::getFrame(QString name) {
    QList<JmriJFrame*>* list = getFrameList();  // needed to get synch copy
    for (int i=0; i<list->size(); i++) {
        JmriJFrame* j = list->at(i);
        if (j->title()==(name)) return j;
    }
    return NULL;
}
#if 0

// handle resizing when first shown
/*public*/ void addNotify() {
    super.addNotify();
    // log->debug("addNotify window ("+windowTitle()+")");
    if (mShown)
        return;
    // resize frame to account for menubar
    JMenuBar jMenuBar = getJMenuBar();
    if (jMenuBar != NULL) {
        int jMenuBarHeight = jMenuBar.getPreferredSize().height;
        Dimension dimension = getSize();
        dimension.height += jMenuBarHeight;
        setSize(dimension);
    }
    mShown = true;
}
#endif
/**
 * Set whether the frame Position is saved or not after it has been created.
 */
/*public*/ void JmriJFrame::setSavePosition(bool save){
    reuseFrameSavedPosition=save;
    UserPreferencesManager* prefsMgr = (UserPreferencesManager* )InstanceManager::getDefault("UserPreferencesManager");
    if (prefsMgr != NULL) {
        prefsMgr->setSaveWindowLocation(windowFrameRef, save);
    } else {
        log->warn("setSavePosition() UserPreferencesManager() not initialised" );
    }
}

/**
 * Set whether the frame Size is saved or not after it has been created
 */
/*public*/ void JmriJFrame::setSaveSize(bool save){
    reuseFrameSavedSized=save;
    UserPreferencesManager* prefsMgr = (UserPreferencesManager* )InstanceManager::getDefault("UserPreferencesManager");
    if (prefsMgr != NULL) {
        prefsMgr->setSaveWindowSize(windowFrameRef, save);
    } else {
        log->warn("setSaveSize() UserPreferencesManager() not initialised" );
    }
}

/**
 * Returns if the frame Position is saved or not
 */
/*public*/ bool JmriJFrame::getSavePosition(){
    return reuseFrameSavedPosition;
}

/**
 * Returns if the frame Size is saved or not
 */
/*public*/ bool JmriJFrame::getSaveSize(){
    return reuseFrameSavedSized;
}


/**
 * A frame is considered "modified" if it has changes
 * that have not been stored.
 */
/*public*/ void JmriJFrame::setModifiedFlag(bool flag) {
    this->modifiedFlag = flag;
    // mark the window in the GUI
    markWindowModified(this->modifiedFlag);
}

/**
 * Get the value of the modified flag.
 * <p>Not a bound parameter
 */
/*public*/ bool JmriJFrame::getModifiedFlag() { return modifiedFlag; }

/**
 * Handle closing a window or quiting the program
 * while the modified bit was set.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="LI_LAZY_INIT_STATIC", justification="modified is only on Swing thread")
/*protected*/ void JmriJFrame::handleModified()
{
 if (getModifiedFlag())
 {
  this->setVisible(true);
//        int result = javax.swing.JOptionPane.showOptionDialog(this,
//            Bundle.getMessage("WarnChangedMsg"),
//            Bundle.getMessage("WarnChangedTitle"),
//            javax.swing.JOptionPane.YES_NO_OPTION,
//            javax.swing.JOptionPane.WARNING_MESSAGE,
//            NULL, // icon
//            new String[]{Bundle.getMessage("WarnYesSave"),Bundle.getMessage("WarnNoClose")},
//            Bundle.getMessage("WarnYesSave")
//        );
  switch(QMessageBox::question(NULL, tr("Warning"), tr("This window contains changed values.\nDo you want to save them?\nYes, save values and close\nNo, just close"), QMessageBox::Yes | QMessageBox::No))
  {
  case QMessageBox::Yes:
   // user wants to save
   storeValues();
   break;
  default:
   break;
  }
 }
}
/*protected*/ void JmriJFrame::storeValues() {
    log->error("default storeValues does nothing for "+windowTitle());
}


// For marking the window as modified on Mac OS X
// See: http://developer.apple.com/qa/qa2001/qa1146.html
/*final*/ /*static*/ QString JmriJFrame::WINDOW_MODIFIED = "windowModified";
/*public*/ void JmriJFrame::markWindowModified(bool /*yes*/){
    //getRootPane().putClientProperty(WINDOW_MODIFIED, yes ? Boolean.TRUE : Boolean.FALSE);
}
#if 0
// Window methods
/*public*/ void windowOpened(java.awt.event.WindowEvent e) {}
/*public*/ void windowClosed(java.awt.event.WindowEvent e) {}

/*public*/ void windowActivated(java.awt.event.WindowEvent e) {}
/*public*/ void windowDeactivated(java.awt.event.WindowEvent e) {}
/*public*/ void windowIconified(java.awt.event.WindowEvent e) {}
/*public*/ void windowDeiconified(java.awt.event.WindowEvent e) {}
#endif
//@Override
/*public*/ void JmriJFrame::windowClosing(QCloseEvent* e) {
    handleModified();
}

#if 0
/*public*/ void componentHidden(java.awt.event.ComponentEvent e) {}
#endif
// /*public*/ void componentMoved(java.awt.event.ComponentEvent e)


// /*public*/ void componentResized(java.awt.event.ComponentEvent e)

// /*public*/ void componentShown(java.awt.event.ComponentEvent e) { }

/*protected*/ void JmriJFrame::setShutDownTask()
{
 if (InstanceManager::shutDownManagerInstance()!=NULL)
 {
//  task = new AbstractShutDownTask(windowTitle())
//  {
//    /*public*/ bool execute()
//   {
//    handleModified();
//    return true;
//   }
//  };
  task = (AbstractShutDownTask*)new MyAbstractShutDownTask(windowTitle(),this);
  InstanceManager::shutDownManagerInstance()->_register(task);
 }
}
MyAbstractShutDownTask::MyAbstractShutDownTask(QString windowTitle, JmriJFrame *frame, QObject *parent) : AbstractShutDownTask(windowTitle, parent)
{
 this->windowTitle = windowTitle;
 this->frame = frame;
}
bool MyAbstractShutDownTask::execute()
{
 frame->handleModified();
 return true;
}

/**
 * When window is finally destroyed, remove it from the
 * list of windows.
 * <P>
 * Subclasses that over-ride this method must invoke this implementation
 * with super.dispose()
 */
/*public*/ void JmriJFrame::dispose()
{
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if (p != NULL)
 {
  if (reuseFrameSavedPosition)
   p->setWindowLocation(windowFrameRef, this->pos());
  if (reuseFrameSavedSized)
  {
   //Windows sets the size parameter when resizing a frame, while Unix uses the preferredsize
#ifdef Q_OS_LINUX
   p->setWindowSize(windowFrameRef, size());
#else
      p->setWindowSize(windowFrameRef, /*super.getPreferredSize()*/QMainWindow::iconSize());
#endif
  }
 }
 //log->debug("dispose "+windowTitle());
 if (windowInterface != NULL)
 {
  windowInterface->dispose();
 }
 if (task != NULL)
 {
  InstanceManager::shutDownManagerInstance()->deregister(task);
  task = NULL;
 }
 /*synchronized (list)*/
 {
  //QMutexLocker locker(&mutex);
  if(frameList->indexOf(this) >=0);
   frameList->removeOne(this);
 }
 JFrame::dispose();
 //close();
}
#if 0
/*
 * This field contains a list of properties that do not correspond to the
 * JavaBeans properties coding pattern, or known properties that do correspond
 * to that pattern. The default JmriJFrame implementation of
 * BeanInstance.hasProperty checks this hashmap before using introspection
 * to find properties corresponding to the JavaBean properties
 * coding pattern.
 */
protected HashMap<String, Object> properties = new HashMap<String, Object>();

/*public*/ void setIndexedProperty(String key, int index, Object value) {
    if (Beans.hasIntrospectedProperty(this, key)) {
        Beans.setIntrospectedIndexedProperty(this, key, index, value);
    } else {
        if (!properties.containsKey(key)) {
            properties.put(key, new Object[0]);
        }
        ((Object[])properties.get(key))[index] = value;
    }
}

/*public*/ Object getIndexedProperty(String key, int index) {
    if (properties.containsKey(key) && properties.get(key).getClass().isArray()) {
        return ((Object[])properties.get(key))[index];
    }
    return Beans.getIntrospectedIndexedProperty(this, key, index);
}

// subclasses should override this method with something more direct and faster
/*public*/ void setProperty(String key, Object value) {
    if (Beans.hasIntrospectedProperty(this, key)) {
        Beans.setIntrospectedProperty(this, key, value);
    } else {
        properties.put(key, value);
    }
}

// subclasses should override this method with something more direct and faster
/*public*/ Object getProperty(String key) {
    if (properties.containsKey(key)) {
        return properties.get(key);
    }
    return Beans.getIntrospectedProperty(this, key);
}

/*public*/ bool hasProperty(String key) {
    if (properties.containsKey(key)) {
        return true;
    } else {
        return Beans.hasIntrospectedProperty(this, key);
    }
}


/*public*/ void show(JmriPanel child, JmriAbstractAction action) {
    if (NULL != windowInterface) {
        windowInterface.show(child, action);
    }
}

/*public*/ void show(JmriPanel child, JmriAbstractAction action, Hint hint) {
    if (NULL != windowInterface) {
        windowInterface.show(child, action, hint);
    }
}

/*public*/ bool multipleInstances() {
    if (NULL != windowInterface) {
        return windowInterface.multipleInstances();
    }
    return false;
}

/*public*/ void setWindowInterface(WindowInterface wi) {
    windowInterface = wi;
}

/*public*/ WindowInterface getWindowInterface() {
    return windowInterface;
}

/*public*/ Set<String> getPropertyNames() {
    HashSet<String> names = new HashSet<String>();
    names.addAll(properties.keySet());
    names.addAll(Beans.getIntrospectedPropertyNames(this));
    return names;
}

/*public*/ void setAllowInFrameServlet(bool allow) {
    allowInFrameServlet = allow;
}

/*public*/ bool getAllowInFrameServlet() {
    return allowInFrameServlet;
}

//@Override
/*public*/ QFrame getFrame() {
    return this;
}
#endif
void JmriJFrame::setLocation(int x, int y)
{
    move(x, y);
}
/**
     * Gets the name of the component.
     * @return this component's name
     * @see    #setName
     * @since JDK1.1
     */
    /*public*/ QString JmriJFrame::getName() {
//        if (name == null && !nameExplicitlySet) {
//            synchronized(getObjectLock()) {
//                if (name == null && !nameExplicitlySet)
//                    name = constructComponentName();
//            }
//        }
        return name;
    }

/**
 * Sets the name of the component to the specified string.
 * @param name  the string that is to be this
 *           component's name
 * @see #getName
 * @since JDK1.1
 */
/*public*/ void JmriJFrame::setName(QString name) {
    QString oldName;
    /*synchronized(getObjectLock())*/ {
        oldName = this->name;
        this->name = name;
//            nameExplicitlySet = true;
    }
//        firePropertyChange("name", oldName, name);
}
void JmriJFrame::setWindowTitle(const QString &title)
{
 setTitle(title);
}

void JmriJFrame::setTitle(QString name)
{
 this->name = name;
 JFrame::setTitle(name);
 QMainWindow::setWindowTitle(name);
}
QString JmriJFrame::getTitle() { return windowTitle();}

//@Override
/*public*/ QVariant JmriJFrame::getProperty(QString key)
{
 if (properties->contains(key)) {
     return properties->value(key);
 }
 //return Beans.getIntrospectedProperty(this, key);
 return QVariant();
}

QWidget* JmriJFrame::getContentPane()
{
 if(centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget();
  centralWidget->resize(300,300);
  //centralWidget()->setLayout(new QVBoxLayout);
  setCentralWidget(centralWidget);
 }
 return centralWidget();
}
void JmriJFrame::setAlwaysOnTop(bool checked)
{
 JFrame::setAlwaysOnTop(checked);
}
void JmriJFrame::setContentPane(QWidget * p)
{
 setCentralWidget(p);
}

/**
 * Bind an action to the Escape key.
 * <p>
 * Binds an AbstractAction to the Escape key. If an action is already bound
 * to the Escape key, that action will be replaced. Passing
 * <code>null</code> unbinds any existing actions from the Escape key.
 * <p>
 * Note that binding the Escape key to any action may break expected or
 * standardized behaviors. See <a
 * href="http://java.sun.com/products/jlf/ed2/book/Appendix.A.html">Keyboard
 * Shortcuts, Mnemonics, and Other Keyboard Operations</a> in the Java Look
 * and Feel Design Guidelines for standardized behaviors.
 *
 * @param action The AbstractAction to bind to.
 * @see #getEscapeKeyAction()
 * @see #setEscapeKeyClosesWindow(boolean)
 */
/*public*/ void JmriJFrame::setEscapeKeyAction(AbstractAction* action) {
#if 0 // TODO:
    JRootPane root = this.getRootPane();
    KeyStroke escape = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
    escapeKeyActionClosesWindow = false; // setEscapeKeyClosesWindow will set to true as needed
    if (action != null) {
        root.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(escape, escapeKeyAction);
        root.getActionMap().put(escapeKeyAction, action);
    } else {
        root.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).remove(escape);
        root.getActionMap().remove(escapeKeyAction);
    }
#endif
}

/**
 * The action associated with the Escape key.
 *
 * @return An AbstractAction or null if no action is bound to the Escape
 *         key.
 * @see #setEscapeKeyAction(javax.swing.AbstractAction)
 * @see javax.swing.AbstractAction
 */
/*public*/ AbstractAction* JmriJFrame::getEscapeKeyAction()
{
// TODO:    return (AbstractAction*) this->getRootPane().getActionMap().get(escapeKeyAction);
 return NULL;
}

/**
 * Bind the Escape key to an action that closes the window.
 * <p>
 * If closesWindow is true, this method creates an action that triggers the
 * "window is closing" event; otherwise this method removes any actions from
 * the Escape key.
 *
 * @param closesWindow Create or destroy an action to close the window.
 * @see java.awt.event.WindowEvent#WINDOW_CLOSING
 * @see #setEscapeKeyAction(javax.swing.AbstractAction)
 */
/*public*/ void JmriJFrame::setEscapeKeyClosesWindow(bool closesWindow)
{
#if 0 //TODO::
    if (closesWindow) {
        setEscapeKeyAction(new AbstractAction() {

            /**
             *
             */
            private static final long serialVersionUID = -814207277600217890L;

            public void actionPerformed(ActionEvent ae) {
                JmriJFrame.this.processWindowEvent(new java.awt.event.WindowEvent(JmriJFrame.this,
                        java.awt.event.WindowEvent.WINDOW_CLOSING));
            }
        });
    } else {
        setEscapeKeyAction(null);
    }
#endif
    escapeKeyActionClosesWindow = closesWindow;
}
/*private*/ /*static*/ QString JmriJFrame::escapeKeyAction = "escapeKeyAction";

/**
 * Does the Escape key close the window?
 *
 * @return <code>true</code> if Escape key is bound to action created by
 *         setEscapeKeyClosesWindow, <code>false</code> in all other cases.
 * @see #setEscapeKeyClosesWindow
 * @see #setEscapeKeyAction
 */
/*public*/ bool JmriJFrame::getEscapeKeyClosesWindow() {
    return (escapeKeyActionClosesWindow && getEscapeKeyAction() != NULL);
}

bool JmriJFrame::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Escape && escapeKeyActionClosesWindow)
        {
            this->close();
            return QMainWindow::eventFilter(target,event);
        }
    }
    return QMainWindow::eventFilter(target,event);
}
//QWidget* JmriJFrame::centralWidget()
//{
// return this;
//}

JmriJFrameWindowListener::JmriJFrameWindowListener(JmriJFrame *frame) { this->frame = frame;}
void JmriJFrameWindowListener::windowClosing(QCloseEvent *)
{
 frame->handleModified();
 frame->dispose();
}
void JmriJFrame::resizeEvent(QResizeEvent *e) { componentResized(e);}
void JmriJFrame::moveEvent(QMoveEvent *e) { componentMoved(e);}
/*public*/ void JmriJFrame::componentMoved(QMoveEvent* /*e*/)
{
    UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if ((p != NULL) && (reuseFrameSavedPosition) && isVisible()) {
        p->setWindowLocation(windowFrameRef, this->pos());
    }
}

/*public*/ void JmriJFrame::componentResized(QResizeEvent* /*e*/)
{
    UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if ((p != NULL) && (reuseFrameSavedSized) && isVisible()) {
        saveWindowSize(p);
    }
}

/*
     * Daniel Boudreau 3/19/2014. There is a problem with saving the correct window size on a Linux OS. The testing was
     * done using Oracle Java JRE 1.7.0_51 and Debian (Wheezy) Linux on a PC. One issue is that the window size returned
     * by getSize() is slightly smaller than the actual window size. If we use getSize() to save the window size the
     * window will shrink each time the window is closed and reopened. The previous workaround was to use
     * getPreferredSize(), that returns whatever we've set in setPreferredSize() which keeps the window size constant
     * when we save the data to the user preference file. However, if the user resizes the window, getPreferredSize()
     * doesn't change, only getSize() changes when the user resizes the window. So we need to try and detect when the
     * window size was modified by the user. Testing has shown that the window width is short by 4 pixels and the height
     * is short by 3. This code will save the window size if the width or height was changed by at least 5 pixels. Sorry
     * for this kludge.
     */
    /*private*/ void JmriJFrame::saveWindowSize(UserPreferencesManager* p) {
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
/*public*/ void JmriJFrame::setAllowInFrameServlet(bool allow) {
        allowInFrameServlet = allow;
}

/*public*/ bool JmriJFrame::getAllowInFrameServlet() {
    return allowInFrameServlet;
}
