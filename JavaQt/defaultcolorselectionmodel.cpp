#include "defaultcolorselectionmodel.h"
#include "eventlistenerlist.h"
#include "changeevent.h"
/**
 * A generic implementation of <code>ColorSelectionModel</code>.
 *
 * @author Steve Wilson
 *
 * @see java.awt.Color
 */
// /*public*/ class DefaultColorSelectionModel implements ColorSelectionModel, Serializable {

    /**
     * Only one <code>ChangeEvent</code> is needed per model instance
     * since the event's only (read-only) state is the source property.
     * The source of events generated here is always "this".
     */

    /**
     * Creates a <code>DefaultColorSelectionModel</code> with the
     * current color set to <code>Color.white</code>.  This is
     * the default constructor.
     */
    /*public*/ DefaultColorSelectionModel::DefaultColorSelectionModel(QObject *parent) : QObject(parent) {
        selectedColor = QColor(Qt::white);
        listenerList =  new EventListenerList();
    }

    /**
     * Creates a <code>DefaultColorSelectionModel</code> with the
     * current color set to <code>color</code>, which should be
     * non-<code>null</code>.  Note that setting the color to
     * <code>null</code> is undefined and may have unpredictable
     * results.
     *
     * @param color the new <code>Color</code>
     */
    /*public*/ DefaultColorSelectionModel::DefaultColorSelectionModel(QColor color,QObject *parent) : QObject(parent) {
        selectedColor = color;
        listenerList = new EventListenerList();
    }

    /**
     * Returns the selected <code>Color</code> which should be
     * non-<code>null</code>.
     *
     * @return the selected <code>Color</code>
     */
    /*public*/ QColor DefaultColorSelectionModel::getSelectedColor() {
        return selectedColor;
    }

    /**
     * Sets the selected color to <code>color</code>.
     * Note that setting the color to <code>null</code>
     * is undefined and may have unpredictable results.
     * This method fires a state changed event if it sets the
     * current color to a new non-<code>null</code> color;
     * if the new color is the same as the current color,
     * no event is fired.
     *
     * @param color the new <code>Color</code>
     */
    /*public*/ void DefaultColorSelectionModel::setSelectedColor(QColor color) {
        if (color != QColor() && selectedColor != (color)) {
            selectedColor = color;
            fireStateChanged();
        }
    }

    /**
     * Adds a <code>ChangeListener</code> to the model.
     *
     * @param l the <code>ChangeListener</code> to be added
     */
    /*public*/ void DefaultColorSelectionModel::addChangeListener(ChangeListener* l) {
//        listenerList->add("ChangeListener", l);
     connect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));
    }

    /**
     * Removes a <code>ChangeListener</code> from the model.
     * @param l the <code>ChangeListener</code> to be removed
     */
    /*public*/ void DefaultColorSelectionModel::removeChangeListener(ChangeListener* l) {
//        listenerList->remove("ChangeListener", l);
     disconnect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));
    }

    /**
     * Returns an array of all the <code>ChangeListener</code>s added
     * to this <code>DefaultColorSelectionModel</code> with
     * <code>addChangeListener</code>.
     *
     * @return all of the <code>ChangeListener</code>s added, or an empty
     *         array if no listeners have been added
     * @since 1.4
     */
    /*public*/ QVector<EventListener*> DefaultColorSelectionModel::getChangeListeners() {
        return listenerList->getListeners("ChangeListener");
    }

    /**
     * Runs each <code>ChangeListener</code>'s
     * <code>stateChanged</code> method.
     *
     * <!-- @see #setRangeProperties    //bad link-->
     * @see EventListenerList
     */
    /*protected*/ void DefaultColorSelectionModel::fireStateChanged()
    {
//        QVector<EventListener*> listeners = listenerList->getListenerList();
////        for (int i = listeners.length() - 2; i >= 0; i -=2 ) {
//        for(int i= 0; i < listeners.length(); i ++)
//        {
//            if (qobject_cast<EventListener*>(listeners[i]->self())) {
//                if (changeEvent == nullptr) {
//                    changeEvent = new ChangeEvent(this);
//                }
//                ((ChangeListener*)listeners[i])->stateChanged(changeEvent);
//            }
//        }
    if (changeEvent == nullptr) {
         changeEvent = new ChangeEvent(this);
     }
     emit stateChanged(changeEvent);
    }

