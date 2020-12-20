#include "jframe.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include "propertychangeevent.h"
#include "exceptions.h"
//include "layouteditortools.h"
//#include "apps.h"
#include "windowlistener.h"
#include <QDesktopWidget>
#include <QDebug>
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "jpanel.h"

JFrame::JFrame(QWidget *parent) :
    QMainWindow(parent)
{
 frameInit();
}
/*public*/ JFrame::JFrame(QString title,QWidget *parent) : QMainWindow(parent) {
    //super(title);
 setTitle(title);
 frameInit();
}
JFrame::~JFrame()
{
 dispose();
 delete log;
}

/** Called by the constructors to init the <code>JFrame</code> properly. */
/*protected*/ void JFrame::frameInit()
{
 log = new Logger("JFrame");
 //log->setDebugEnabled(true);
 defaultCloseOperation = HIDE_ON_CLOSE;
 listeners = new QList<WindowListener*>();
 setVisible(false);
}

/*public*/ void JFrame::pack()
{
 // work around for Linux, sometimes the stored window size is too small
// if (this->getPreferredSize().width() < 100 || this->size().height() < 100)
// {
//  this->setMinimumSize(QSize(100,20)); // try without the preferred size
// }
 //super.pack();
 adjustSize();
 reSizeToFitOnScreen();
}

/**
 * Tries to get window to fit entirely on screen.  First choice is to
 * move the origin up and left as needed, then to make the
 * window smaller
 */
void JFrame::reSizeToFitOnScreen()
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
/*public*/ QSize JFrame::getMaximumSize()
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
  if(menuBar()!= nullptr)
   heightInset += menuBar()->height();
  if(statusBar() != nullptr)
   heightInset+= statusBar()->height();

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
/*public*/ QSize JFrame::getPreferredSize() {
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
     log->debug("getPreferredSize (sizeHint) returns width "+QString::number(sizeHint().width())+" height "+QString::number(sizeHint().height()));
 return sizeHint();
#endif
}
QPoint JFrame::getLocation() { return pos();}
void JFrame::setLocation(int x, int y)
{
    move(x, y);
}

void JFrame::dispose()
{
  close();
 //deleteLater();
  _closed = true;
 if(!_windowClosing)
  log->error(tr("dispose() called but window isn't closing!"));
}

JPanel* JFrame:: getContentPane(bool addLayout)
{
 if(centralWidget() == nullptr)
 {
  JPanel* centralWidget = new JPanel();
  centralWidget->setObjectName("JFrameCentralWidget");
  if(addLayout)
  {
   QVBoxLayout* centralWidgetLayout;
   centralWidget->setLayout(centralWidgetLayout = new QVBoxLayout);
   centralWidgetLayout->setObjectName("centralWidgetLayout");
  }
  setCentralWidget(centralWidget);
 }
 return (JPanel*)centralWidget();
}

void JFrame::toFront()
{
 raise();
 activateWindow();
 show();
 showNormal();

}
/**
 * Sets the title for this frame to the specified string.
 * @param title the title to be displayed in the frame's border.
 *              A <code>null</code> value
 *              is treated as an empty string, "".
 * @see      #getTitle
 */
/*public*/ void JFrame::setTitle(QString title) {
    QString oldTitle = this->_title;
    _title = title;
    setWindowTitle(title);

//    if (title == null) {
//        title = "";
//    }

//    synchronized(this) {
//        this.title = title;
//        FramePeer peer = (FramePeer)this.peer;
//        if (peer != null) {
//            peer.setTitle(title);
//        }
//    }
//    firePropertyChange("title", oldTitle, title);
    emit propertyChange(new PropertyChangeEvent(this, "title", oldTitle, title));
}
/*public*/ QString JFrame::getTitle() { return _title;}

QString JFrame::title() { return _title;}
/**
 * Sets the operation that will happen by default when
 * the user initiates a "close" on this frame.
 * You must specify one of the following choices:
 * <p>
 * <ul>
 * <li><code>DO_NOTHING_ON_CLOSE</code>
 * (defined in <code>WindowConstants</code>):
 * Don't do anything; require the
 * program to handle the operation in the <code>windowClosing</code>
 * method of a registered <code>WindowListener</code> object.
 *
 * <li><code>HIDE_ON_CLOSE</code>
 * (defined in <code>WindowConstants</code>):
 * Automatically hide the frame after
 * invoking any registered <code>WindowListener</code>
 * objects.
 *
 * <li><code>DISPOSE_ON_CLOSE</code>
 * (defined in <code>WindowConstants</code>):
 * Automatically hide and dispose the
 * frame after invoking any registered <code>WindowListener</code>
 * objects.
 *
 * <li><code>EXIT_ON_CLOSE</code>
 * (defined in <code>JFrame</code>):
 * Exit the application using the <code>System</code>
 * <code>exit</code> method.  Use this only in applications.
 * </ul>
 * <p>
 * The value is set to <code>HIDE_ON_CLOSE</code> by default. Changes
 * to the value of this property cause the firing of a property
 * change event, with property name "defaultCloseOperation".
 * <p>
 * <b>Note</b>: When the last displayable window within the
 * Java virtual machine (VM) is disposed of, the VM may
 * terminate.  See <a href="../../java/awt/doc-files/AWTThreadIssues.html">
 * AWT Threading Issues</a> for more information.
 *
 * @param operation the operation which should be performed when the
 *        user closes the frame
 * @exception IllegalArgumentException if defaultCloseOperation value
 *             isn't one of the above valid values
 * @see #addWindowListener
 * @see #getDefaultCloseOperation
 * @see WindowConstants
 * @throws  SecurityException
 *        if <code>EXIT_ON_CLOSE</code> has been specified and the
 *        <code>SecurityManager</code> will
 *        not allow the caller to invoke <code>System.exit</code>
 * @see        java.lang.Runtime#exit(int)
 *
 * @beaninfo
 *   preferred: true
 *       bound: true
 *        enum: DO_NOTHING_ON_CLOSE WindowConstants.DO_NOTHING_ON_CLOSE
 *              HIDE_ON_CLOSE       WindowConstants.HIDE_ON_CLOSE
 *              DISPOSE_ON_CLOSE    WindowConstants.DISPOSE_ON_CLOSE
 *              EXIT_ON_CLOSE       WindowConstants.EXIT_ON_CLOSE
 * description: The frame's default close operation.
 */
/*public*/ void JFrame::setDefaultCloseOperation(int operation) {
    if (operation != DO_NOTHING_ON_CLOSE &&
        operation != HIDE_ON_CLOSE &&
        operation != DISPOSE_ON_CLOSE &&
        operation != EXIT_ON_CLOSE) {
        throw IllegalArgumentException("defaultCloseOperation must be one of: DO_NOTHING_ON_CLOSE, HIDE_ON_CLOSE, DISPOSE_ON_CLOSE, or EXIT_ON_CLOSE");
    }
    if (this->defaultCloseOperation != operation) {
//        if (operation == EXIT_ON_CLOSE) {
//            SecurityManager security = System.getSecurityManager();
//            if (security != NULL) {
//                security.checkExit(0);
//            }
//        }
        int oldValue = this->defaultCloseOperation;
        this->defaultCloseOperation = operation;
//        firePropertyChange("defaultCloseOperation", oldValue, operation);
    }
}
/*public*/ int JFrame::getDefaultCloseOperation() { return defaultCloseOperation;}

QPoint JFrame::getLocationOnScreen()
{
 return pos();
}

void JFrame::setLocation(QPoint p)
{
 setLocation(p.x(), p.y());
}
/**
 * Returns the top-level ancestor of this component (either the
 * containing <code>Window</code> or <code>Applet</code>),
 * or <code>null</code> if this component has not
 * been added to any container.
 *
 * @return the top-level <code>Container</code> that this component is in,
 *          or <code>null</code> if not in any container
 */
/*public*/ QWidget* JFrame::getTopLevelAncestor()
{
 for(QObject* p = this; p != nullptr; p = p->parent())
 {
  //if(p instanceof Window || p instanceof Applet)
     if(qobject_cast<JFrame*>(p)!=nullptr)
  {
   return (QWidget*)p;
  }
 }
 return nullptr;
}
void JFrame::setMenuBar(QMenuBar *menubar)
{
 QMainWindow::setMenuBar(menubar);
}

void JFrame::closeEvent(QCloseEvent* e)
{
 _windowClosing = defaultCloseOperation == DISPOSE_ON_CLOSE;
 foreach(WindowListener* l, *listeners)
 {
//  if(qobject_cast<LayoutEditorTools*>(l)!= NULL)
//      ((LayoutEditorTools*)l)->windowClosing(e);
//  if(qobject_cast<Apps*>(l)!= NULL)
//      ((Apps*)l)->windowClosing(e);
//  else
  l->windowClosing(e);
  if(e->isAccepted())
   l->windowClosed(e);
 }
 switch (defaultCloseOperation) {
  case HIDE_ON_CLOSE:
      hide();
      break;
  case DISPOSE_ON_CLOSE:
      dispose();
      deleteLater();
      foreach(WindowListener* l, *listeners)
      {
       l->windowClosed(e);
      }
      break;
  case EXIT_ON_CLOSE:
      // This needs to match the checkExit call in
      // setDefaultCloseOperation
      exit(0);
  case DO_NOTHING_ON_CLOSE:
  default:
  break;
 }

}

///*public*/ void JFrame::windowClosing(QCloseEvent* /*e*/)
//{
//    //handleModified();
//    switch (defaultCloseOperation) {
//     case HIDE_ON_CLOSE:
//         setVisible(false);
//         break;
//     case DISPOSE_ON_CLOSE:
//         dispose();
//         break;
//     case EXIT_ON_CLOSE:
//         // This needs to match the checkExit call in
//         // setDefaultCloseOperation
//         exit(0);
//     case DO_NOTHING_ON_CLOSE:
//     default:
//     break;
// }
//}

void JFrame::addWindowListener(WindowListener* l)
{
 listeners->append(l);
}

QVector<WindowListener*> JFrame::getWindowListeners()
{
 return QVector<WindowListener*>(listeners->toVector());
}

/**
 * Removes the specified window listener so that it no longer
 * receives window events from this window.
 * If l is null, no exception is thrown and no action is performed.
 * <p>Refer to <a href="doc-files/AWTThreadIssues.html#ListenersThreads"
 * >AWT Threading Issues</a> for details on AWT's threading model.
 *
 * @param   l the window listener
 * @see #addWindowListener
 * @see #getWindowListeners
 */
/*public*/ /*synchronized*/ void JFrame::removeWindowListener(WindowListener* l) {
    if (l == nullptr) {
        return;
    }
    //windowListener = AWTEventMulticaster.remove(windowListener, l);
    listeners->removeOne(l);
}

void JFrame::setAlwaysOnTop(bool checked)
{
#ifdef Q_OS_WIN
    // #include <windows.h>
    if (checked)
    {
        SetWindowPos(this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    else
    {
        SetWindowPos(this->winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
#else
    Qt::WindowFlags flags = this->windowFlags();
    if (checked)
    {
        this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
        this->show();
    }
    else
    {
        this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
        this->show();
    }
#endif
}

void JFrame::hideEvent(QHideEvent *)
{
 //qDebug() << "hide";
}
#if 0
//@Override
/*public*/ void JFrame::moveEvent(/*java.awt.event.ComponentEvent*/QMoveEvent* e)
{
    //InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent(p -> {
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if(p != NULL)
 {
  if (reuseFrameSavedPosition && isVisible()) {
      p->setWindowLocation(windowFrameRef, this->pos());
  }
 }//);
}

//@Override
/*public*/ void JFrame::resizeEvent(/*java.awt.event.ComponentEvent*/QResizeEvent* e) {
    //InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent(p -> {
 UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
 if(p != NULL)
 {
  if (reuseFrameSavedSized && isVisible()) {
      saveWindowSize(p);
  }
 } //);
}
#endif

void JFrame::setVisible(bool visible)
{
 QMainWindow::setVisible(visible);
}
/*public*/ bool JFrame::isOpaque()
{
 return _opaque;
}
/*public*/ QColor JFrame::getForeground()
{
 return palette().color(QWidget::foregroundRole());
}
/*public*/ QColor JFrame::getBackground()
{
 return palette().color(QWidget::backgroundRole());
}
/*public*/ void JFrame::setBackground(QColor c)
{
 setStyleSheet(tr("QMainWindow{background-color: rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue()));
}
/*public*/ void JFrame::setOpaque(bool b)
{
 _opaque = b;
}
/*public*/ QFont JFrame::getFont()
{
 return QWidget::font();
}

/*public*/ void JFrame::setFont(QFont f)
{
 QWidget::setFont(f);
}

// remove and hide all child widgets and delete layout.
/*public*/ void JFrame::removeAll()
{
 QList<QWidget*> children = findChildren<QWidget*>();
 QLayout* _layout = layout();
 if(_layout)
 {
  foreach(QWidget* w, children)
  {
   _layout->removeWidget(w);
   w->hide();
  }
  delete _layout;
  _layout = nullptr;
 }
}

/*public*/ void JFrame::setBounds(QRect r)
{
 resize(r.width(), r.height());
 setLocation(r.left(), r.top());
}
