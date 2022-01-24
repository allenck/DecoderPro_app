#include "throttleframemanager.h"
#include <QKeyEvent>
#include "instancemanager.h"
#include "throttlewindow.h"
#include "throttlespreferences.h"
//#include "listthrottles.h"
#include "throttlespreferencespane.h"
#include "throttleslistpanel.h"
#include <QBoxLayout>

//ThrottleFrameManager::ThrottleFrameManager(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 *  Interface for allocating and deallocating throttles frames. Not to be
 *  confused with ThrottleManager
 *
 * @author     Glen Oberhauser
 * @version    $Revision: 22216 $
 */
///*public*/ class ThrottleFrameManager
//{

/*private*/ /*static*/ int ThrottleFrameManager::NEXT_THROTTLE_KEY = Qt::Key_Right;
/*private*/ /*static*/ int ThrottleFrameManager::PREV_THROTTLE_KEY = Qt::Key_Left;


/**
 *  Constructor for the ThrottleFrameManager object
 */
/*private*/ ThrottleFrameManager::ThrottleFrameManager(QObject *parent) :
QObject(parent) // can only be created by instance() => /*private*/
{
//    throttleCycler = new ThrottleCyclingKeyListener();
 throttlesListPanel = NULL;
 throttlesListFrame = NULL;
 throttleWindows = new QList<ThrottleWindow*>(/*0*/);
 InstanceManager::store(this, "ThrottleFrameManager");  // added ACK

 if(InstanceManager::getNullableDefault("ThrottlesPreferences")==NULL)
 {
  InstanceManager::store(new ThrottlesPreferences(), "ThrottlesPreferences");
 }
 throttlesPref = (ThrottlesPreferences*)InstanceManager::getDefault("ThrottlesPreferences");
 buildThrottleListFrame();
}

/**
 * Get the singleton instance of this class.
 */
/*public*/ /*static*/ ThrottleFrameManager* ThrottleFrameManager::instance()
{
 return (ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager");
}


/**
 *  Tell this manager that a new ThrottleWindow was created.
 * @return The newly created ThrottleWindow
 */
/*public*/ ThrottleWindow* ThrottleFrameManager::createThrottleWindow() {
    ThrottleWindow* tw = new ThrottleWindow();
//		tw.pack();
//    KeyListenerInstaller.installKeyListenerOnAllComponents(throttleCycler, tw);
    throttleWindows->append(tw);
    activeFrame = throttleWindows->indexOf(tw);
    emit newThrottle(tw);
    return tw ;
}

/**
 *  Tell this manager that a new ThrottleFrame was created.
 * @return The newly created ThrottleFrame
 */
/*public*/ /*ThrottleFrame*/ ThrottleWindow* ThrottleFrameManager::createThrottleFrame() {
    return createThrottleWindow()/*.getCurrentThrottleFrame()*/ ;
}

/**
 *  Request that this manager destroy a throttle frame.
 *
 * @param  frame  The to-be-destroyed ThrottleFrame
 */
/*public*/ void ThrottleFrameManager::requestThrottleWindowDestruction(ThrottleWindow* frame)
{
 if (frame != NULL)
 {
//  destroyThrottleWindow(frame);
  throttleWindows->removeAt(throttleWindows->indexOf(frame));
  if (throttleWindows->size() > 0)
  {
   requestFocusForNextFrame();
  }
 }
}

/*public*/ void ThrottleFrameManager::requestAllThrottleWindowsDestroyed()
{
 //for (QListIterator<ThrottleWindow*> i = QListIterator<ThrottleWindow*> iter(throttleWindows); i.hasNext();)
 QListIterator<ThrottleWindow*> i(*throttleWindows);
 while(i.hasNext())
 {
  ThrottleWindow* frame = i.next();
  destroyThrottleWindow(frame);
 }
 throttleWindows = new QList<ThrottleWindow*>(/*0*/);
}

/**
 * Perform the destruction of a ThrottleFrame. This method will not
 * affect the throttleFrames list, thus ensuring no synchronozation problems.
 * @param window The ThrottleFrame to be destroyed.
 */
/*private*/ void ThrottleFrameManager::destroyThrottleWindow(ThrottleWindow* window)
{
    window->dispose();
}

/**
 *  Retrieve an Iterator over all the ThrottleFrames in existence.
 *
 * @return    The Iterator on the list of ThrottleFrames.
 */
/*public*/ QListIterator<ThrottleWindow*> ThrottleFrameManager::getThrottleWindows()
{
 //   return throttleWindows->Iterator();
    QListIterator<ThrottleWindow*> iter(*throttleWindows);
    return iter;
}

/*public*/ int ThrottleFrameManager::getNumberThrottleWindows(){
    return throttleWindows->size();
}

/*private*/ void ThrottleFrameManager::requestFocusForNextFrame()
{
    activeFrame = (activeFrame + 1) % throttleWindows->size();
    ThrottleWindow* tf = throttleWindows->at(activeFrame);
    tf->setFocus();
    tf->toFront();
}

/*private*/ void ThrottleFrameManager::requestFocusForPreviousFrame()
{
    activeFrame--;
    if (activeFrame < 0)
    {
        activeFrame = throttleWindows->size() - 1;
    }
    ThrottleWindow* tf = throttleWindows->at(activeFrame);
    tf->setFocus();
    tf->toFront();
}

/*public*/ ThrottleWindow* ThrottleFrameManager::getCurrentThrottleFrame() {
    if (throttleWindows == NULL) return NULL;
    if (throttleWindows->size() == 0) return NULL;
    return throttleWindows->at(activeFrame);
}

/*public*/ ThrottlesPreferences* ThrottleFrameManager::getThrottlesPreferences() {
    return throttlesPref;
}
#if 0
/**
 *  Description of the Class
 *
 * @author     glen
 */
class ThrottleCyclingKeyListener extends KeyAdapter	{
    /**
     *  Description of the Method
     *
     * @param  e  Description of the Parameter
     */
    /*public*/ void keyReleased(KeyEvent e)	{
        if (e.isShiftDown() && e.getKeyCode() == NEXT_THROTTLE_KEY)
            requestFocusForNextFrame();
        else if (e.isShiftDown() && e.getKeyCode() == PREV_THROTTLE_KEY)
            requestFocusForPreviousFrame();
    }
}
#endif
/*public*/ ThrottlesListPanel* ThrottleFrameManager::getThrottlesListPanel() {
    return throttlesListPanel ;
}

/*private*/ void ThrottleFrameManager::buildThrottlePreferencesFrame()
{
#if 1
 throttlePreferencesFrame = new ThrottlePreferencesFrame(tr("Throttles preferences"));
 ThrottlesPreferencesPane* tpP = new ThrottlesPreferencesPane();
 QVBoxLayout* tpPLayout = new QVBoxLayout(tpP);
 tpPLayout->addWidget(tpP);
 tpP->setContainer(throttlePreferencesFrame);
 throttlePreferencesFrame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
 throttlePreferencesFrame->setCentralWidget(tpP);
 throttlePreferencesFrame->pack();
#endif
}

/*private*/ void ThrottleFrameManager::buildThrottleListFrame() {
 throttlesListFrame = new ThrottlesListFrame(tr("Local JMRI throttles"));
 throttlesListPanel = new ThrottlesListPanel();
 throttlesListFrame->setContentPane(throttlesListPanel);
 throttlesListFrame->adjustSize();
 //QTimer::singleShot(10000, this, SLOT(initFrame()));
}

/*private*/ void ThrottleFrameManager::initFrame()
{
 JmriJFrame* jFrame = static_cast<JmriJFrame*>(throttlesListFrame);
 jFrame->setWindowState((jFrame->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
 throttlesListFrame->setVisible(false);

}

/*public*/ void ThrottleFrameManager::showThrottlesList()
{
 if (throttlesListFrame == NULL)
     buildThrottleListFrame();
 throttlesListFrame->setVisible( ! throttlesListFrame->isVisible() );
}

/*public*/ void ThrottleFrameManager::showThrottlesPreferences() {
    if (throttlePreferencesFrame == NULL)
        buildThrottlePreferencesFrame();
    throttlePreferencesFrame->setVisible( true );
    throttlePreferencesFrame->setFocus();
}
