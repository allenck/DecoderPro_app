#ifndef ITEMLISTENER_H
#define ITEMLISTENER_H
#include "eventlistener.h"
#include "javaqt_global.h"

class ItemEvent;
class JAVAQTSHARED_EXPORT ItemListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 QObject* self() {return (QObject*)this;}

public slots:

    /**
     * The listener interface for receiving item events.
     * The class that is interested in processing an item event
     * implements this interface. The object created with that
     * class is then registered with a component using the
     * component's <code>addItemListener</code> method. When an
     * item-selection event occurs, the listener object's
     * <code>itemStateChanged</code> method is invoked.
     *
     * @author Amy Fowler
     *
     * @see java.awt.ItemSelectable
     * @see ItemEvent
     * @see <a href="http://java.sun.com/docs/books/tutorial/post1.0/ui/itemlistener.html">Tutorial: Writing an Item Listener</a>
     *
     * @since 1.1
     */
//    public interface ItemListener extends EventListener {

        /**
         * Invoked when an item has been selected or deselected by the user.
         * The code written for this method performs the operations
         * that need to occur when an item is selected (or deselected).
         */
        virtual void itemStateChanged(ItemEvent* /*e*/) = 0;

signals:


};

#endif // ITEMLISTENER_H
