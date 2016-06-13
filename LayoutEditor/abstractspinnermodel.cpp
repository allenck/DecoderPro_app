#include "abstractspinnermodel.h"

AbstractSpinnerModel::AbstractSpinnerModel(QObject *parent)
//    :  SpinnerModel(parent)
{
 changeEvent = NULL;
 listenerList = new QHash<QString, ChangeListener*>();
}
/**
 * This class provides the ChangeListener part of the
 * SpinnerModel interface that should be suitable for most concrete SpinnerModel
 * implementations.  Subclasses must provide an implementation of the
 * <code>setValue</code>, <code>getValue</code>, <code>getNextValue</code> and
 * <code>getPreviousValue</code> methods.
 *
 * @see JSpinner
 * @see SpinnerModel
 * @see SpinnerListModel
 * @see SpinnerNumberModel
 * @see SpinnerDateModel
 *
 * @author Hans Muller
 * @since 1.4
 */
///*public*/ abstract class AbstractSpinnerModel implements SpinnerModel, Serializable
//{





    /**
     * Adds a ChangeListener to the model's listener list.  The
     * ChangeListeners must be notified when the models value changes.
     *
     * @param l the ChangeListener to add
     * @see #removeChangeListener
     * @see SpinnerModel#addChangeListener
     */
    /*public*/ void AbstractSpinnerModel::addChangeListener(ChangeListener* l) {
    listenerList->insert("ChangeListener", l);
    }


    /**
     * Removes a ChangeListener from the model's listener list.
     *
     * @param l the ChangeListener to remove
     * @see #addChangeListener
     * @see SpinnerModel#removeChangeListener
     */
    /*public*/ void AbstractSpinnerModel::removeChangeListener(ChangeListener* l) {
    listenerList->remove("ChangeListener"/*, l*/);
    }


    /**
     * Returns an array of all the <code>ChangeListener</code>s added
     * to this AbstractSpinnerModel with addChangeListener().
     *
     * @return all of the <code>ChangeListener</code>s added or an empty
     *         array if no listeners have been added
     * @since 1.4
     */
    /*public*/ QList<ChangeListener*> AbstractSpinnerModel::getChangeListeners() {
    return listenerList->values();
    }


    /**
     * Run each ChangeListeners stateChanged() method.
     *
     * @see #setValue
     * @see EventListenerList
     */
    /*protected*/ void AbstractSpinnerModel::fireStateChanged()
    {
#if 0
        QObjectList listeners = listenerList.getListenerList();
        for (int i = listeners.length - 2; i >= 0; i -=2 ) {
            if (listeners.at(i)->metaObject()->className() == "ChangeListener") {
                if (changeEvent == NULL) {
                    changeEvent = new ChangeEvent(this);
                }
                ((ChangeListener*)listeners.at(i+1)).stateChanged(changeEvent);
            }
        }
#endif
    }


    /**
     * Return an array of all the listeners of the given type that
     * were added to this model.  For example to find all of the
     * ChangeListeners added to this model:
     * <pre>
     * myAbstractSpinnerModel.getListeners(ChangeListener.class);
     * </pre>
     *
     * @param listenerType the type of listeners to return, e.g. ChangeListener.class
     * @return all of the objects receiving <em>listenerType</em> notifications
     *         from this model
     */
//    /*public*/ <T extends EventListener> T[] getListeners(Class<T> listenerType) {
//        return listenerList.getListeners(listenerType);
//    }
//}

