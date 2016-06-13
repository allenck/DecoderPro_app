#ifndef ACTIONLISTENER_H
#define ACTIONLISTENER_H

#include <QObject>
#include "actionevent.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT ActionListener : public QObject
{
    Q_OBJECT
public:
    //explicit ActionListener(QObject *parent = 0);
    /**
     * The listener interface for receiving action events.
     * The class that is interested in processing an action event
     * implements this interface, and the object created with that
     * class is registered with a component, using the component's
     * <code>addActionListener</code> method. When the action event
     * occurs, that object's <code>actionPerformed</code> method is
     * invoked.
     *
     * @see ActionEvent
     * @see <a href="http://java.sun.com/docs/books/tutorial/post1.0/ui/eventmodel.html">Tutorial: Java 1.1 Event Model</a>
     *
     * @author Carl Quinn
     * @since 1.1
     */
//    public interface ActionListener extends EventListener {
public slots:
        /**
         * Invoked when an action occurs.
         */
    virtual void actionPerformed(ActionEvent* e = 0){Q_UNUSED(e)}

signals:
    
public slots:
    
};

#endif // ACTIONLISTENER_H
