#ifndef WINDOWINTERFACE_H
#define WINDOWINTERFACE_H
#include "jframe.h"
#include "javaqt_global.h"
#include "jmriabstractaction.h"

/**
 * Interface for an object that can arrange for a
 * {@link JmriPanel} to be displayed.
 * <p>
 * Typically used by some component that wants to display
 * a pane (e.g. in an independent JmriJFrame
 * or as part of a paned interface) to do some more stuff.
 * Rather than have the component build it's own window, etc
 * it invokes one of these, so that the position and
 * display of that component can controlled.
 * <p>
 * Any {@link JmriAbstractAction} that uses the show() method
 * will have its dispose() invoked when the associated frame
 * goes away.  It should dispose() any cached panes at that time.
 *
 * @author Bob Jacobsen  Copyright 2010
 * @since 2.9.4
 * @version $Revision: 21373 $
 */
 class JmriPanel;
 class QAction;
 class QFrame;
/*public*/ /*interface*/ class JAVAQTSHARED_EXPORT WindowInterface : public QObject
 {
  Q_OBJECT
 public:
     WindowInterface(QWidget* parent = nullptr) : QObject(parent) {}
//     WindowInterface(const WindowInterface&) : QObject() {}
//     virtual ~WindowInterface() {}
     /**
      * Suggested location for subsequent panels
      */
     /*public*/ enum Hint {
         DEFAULT,   // let the interface pick
         REPLACE,   // replace the current content with new
         EXTEND     // place nearby
     };

    /**
     * Show, in whatever way is appropriate,
     * a specific JmriPanel
     * @param child new JmriPanel to show
     * @param action JmriAbstractAction making the request
     */
    /*public*/ virtual void show(JmriPanel* /*child*/, AbstractAction* /*action*/ ) {}

    /**
     * Show, in whatever way is appropriate,
     * a specific JmriPanel
     * @param child new JmriPanel to show
     * @param action JmriAbstractAction making the request
     * @param hint suggestion on where to put the content
     */
    /*public*/ virtual void show(JmriPanel* /*child*/, AbstractAction* /*action*/, Hint /*hint*/ ) {}

    /**
     * Should 2nd and subsequent requests
     * for a panel (e.g. in an Action) create a
     * new instance, or provide the 1st one
     * for reuse?
     *
     * This would be true e.g. if separate windows
     * were being provided, or false if there
     * was only one window which is being populated
     * with one pane after another.
     *
     *@return true if multiple instances should be provided,
     *         false if only one should be provided.
     */
    /*public*/ virtual bool multipleInstances() {return false;}

    /*public*/ virtual void dispose() {}

    ///*public*/ void runMethod(String method, Object args[]);

    /**
     * Returns the WindowInterface as a Frame or null.
     *
     * @return a Frame or null
     */
    /*public*/ virtual JFrame* getFrame() {return nullptr;}

     friend class WindowMenu;
};
#endif // WINDOWINTERFACE_H
