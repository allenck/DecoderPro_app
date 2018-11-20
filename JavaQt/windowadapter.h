#ifndef WINDOWADAPTER_H
#define WINDOWADAPTER_H
#include <QCloseEvent>
#include "windowlistener.h"

/**
 * An abstract adapter class for receiving window events.
 * The methods in this class are empty. This class exists as
 * convenience for creating listener objects.
 * <P>
 * Extend this class to create a <code>WindowEvent</code> listener
 * and override the methods for the events of interest. (If you implement the
 * <code>WindowListener</code> interface, you have to define all of
 * the methods in it. This abstract class defines null methods for them
 * all, so you can only have to define methods for events you care about.)
 * <P>
 * Create a listener object using the extended class and then register it with
 * a Window using the window's <code>addWindowListener</code>
 * method. When the window's status changes by virtue of being opened,
 * closed, activated or deactivated, iconified or deiconified,
 * the relevant method in the listener
 * object is invoked, and the <code>WindowEvent</code> is passed to it.
 *
 * @see WindowEvent
 * @see WindowListener
 * @see <a href="https://docs.oracle.com/javase/tutorial/uiswing/events/windowlistener.html">Tutorial: Writing a Window Listener</a>
 *
 * @author Carl Quinn
 * @author Amy Fowler
 * @author David Mendenhall
 * @since 1.1
 */
//public abstract class WindowAdapter
//    implements WindowListener, WindowStateListener, WindowFocusListener
class WindowAdapter : public WindowListener
{
    /**
     * Invoked when a window has been opened.
     */
    /*public*/ virtual  void windowOpened(QShowEvent* e) {}

    /**
     * Invoked when a window is in the process of being closed.
     * The close operation can be overridden at this point.
     */
    /*public*/ virtual  void windowClosing(QEvent* e) {}

    /**
     * Invoked when a window has been closed.
     */
    /*public*/ virtual  void windowClosed(QCloseEvent* e) {}

    /**
     * Invoked when a window is iconified.
     */
    /*public*/ virtual  void windowIconified(QEvent* e) {}

    /**
     * Invoked when a window is de-iconified.
     */
    /*public*/ virtual  void windowDeiconified(QEvent* e) {}

    /**
     * Invoked when a window is activated.
     */
    /*public*/ virtual  void windowActivated(QEvent* e) {}

    /**
     * Invoked when a window is de-activated.
     */
    /*public*/ virtual  void windowDeactivated(QEvent* e) {}

    /**
     * Invoked when a window state is changed.
     * @since 1.4
     */
    /*public*/ virtual  void windowStateChanged(QEvent* e) {}

    /**
     * Invoked when the Window is set to be the focused Window, which means
     * that the Window, or one of its subcomponents, will receive keyboard
     * events.
     *
     * @since 1.4
     */
    /*public*/ virtual  void windowGainedFocus(QEvent* e) {}

    /**
     * Invoked when the Window is no longer the focused Window, which means
     * that keyboard events will no longer be delivered to the Window or any of
     * its subcomponents.
     *
     * @since 1.4
     */
    /*public*/ virtual  void windowLostFocus(QEvent* e) {}
};
#endif // WINDOWADAPTER_H
