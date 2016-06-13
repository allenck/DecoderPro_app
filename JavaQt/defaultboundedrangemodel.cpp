#include "defaultboundedrangemodel.h"
#include "exceptions.h"

//DefaultBoundedRangeModel::DefaultBoundedRangeModel()
//{
//}
/**
 * A generic implementation of BoundedRangeModel.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author David Kloba
 * @author Hans Muller
 * @see BoundedRangeModel
 */
///*public*/ class DefaultBoundedRangeModel implements BoundedRangeModel, Serializable
//{




/**
 * Initializes all of the properties with default values.
 * Those values are:
 * <ul>
 * <li><code>value</code> = 0
 * <li><code>extent</code> = 0
 * <li><code>minimum</code> = 0
 * <li><code>maximum</code> = 100
 * <li><code>adjusting</code> = false
 * </ul>
 */
/*public*/ DefaultBoundedRangeModel::DefaultBoundedRangeModel() {
changeEvent = NULL;
//listenerList = new EventListenerList();
value = 0;
extent = 0;
min = 0;
max = 100;
isAdjusting = false;

}


/**
 * Initializes value, extent, minimum and maximum. Adjusting is false.
 * Throws an <code>IllegalArgumentException</code> if the following
 * constraints aren't satisfied:
 * <pre>
 * min &lt;= value &lt;= value+extent &lt;= max
 * </pre>
 */
/*public*/ DefaultBoundedRangeModel::DefaultBoundedRangeModel(int value, int extent, int min, int max)
{
 changeEvent = NULL;
// listenerList = new EventListenerList();
 this->value = 0;
 this->extent = 0;
 this->min = 0;
 this->max = 100;
 isAdjusting = false;

 if ((max >= min) &&
        (value >= min) &&
        ((value + extent) >= value) &&
        ((value + extent) <= max))
 {
  this->value = value;
  this->extent = extent;
  this->min = min;
  this->max = max;
 }
 else
 {
  throw new IllegalArgumentException("invalid range properties");
 }
}


/**
 * Returns the model's current value.
 * @return the model's current value
 * @see #setValue
 * @see BoundedRangeModel#getValue
 */
/*public*/ int DefaultBoundedRangeModel::getValue() {
  return value;
}


/**
 * Returns the model's extent.
 * @return the model's extent
 * @see #setExtent
 * @see BoundedRangeModel#getExtent
 */
/*public*/ int DefaultBoundedRangeModel::getExtent() {
  return extent;
}


/**
 * Returns the model's minimum.
 * @return the model's minimum
 * @see #setMinimum
 * @see BoundedRangeModel#getMinimum
 */
/*public*/ int DefaultBoundedRangeModel::getMinimum() {
  return min;
}


/**
 * Returns the model's maximum.
 * @return  the model's maximum
 * @see #setMaximum
 * @see BoundedRangeModel#getMaximum
 */
/*public*/ int DefaultBoundedRangeModel::getMaximum() {
    return max;
}


/**
 * Sets the current value of the model. For a slider, that
 * determines where the knob appears. Ensures that the new
 * value, <I>n</I> falls within the model's constraints:
 * <pre>
 *     minimum &lt;= value &lt;= value+extent &lt;= maximum
 * </pre>
 *
 * @see BoundedRangeModel#setValue
 */
/*public*/ void DefaultBoundedRangeModel::setValue(int n) {
    n = qMin(n, 32767 - extent);

    int newValue = qMax(n, min);
    if (newValue + extent > max) {
        newValue = max - extent;
    }
    setRangeProperties(newValue, extent, min, max, isAdjusting);
}


/**
 * Sets the extent to <I>n</I> after ensuring that <I>n</I>
 * is greater than or equal to zero and falls within the model's
 * constraints:
 * <pre>
 *     minimum &lt;= value &lt;= value+extent &lt;= maximum
 * </pre>
 * @see BoundedRangeModel#setExtent
 */
/*public*/ void DefaultBoundedRangeModel::setExtent(int n) {
    int newExtent = qMax(0, n);
    if(value + newExtent > max) {
        newExtent = max - value;
    }
    setRangeProperties(value, newExtent, min, max, isAdjusting);
}


/**
 * Sets the minimum to <I>n</I> after ensuring that <I>n</I>
 * that the other three properties obey the model's constraints:
 * <pre>
 *     minimum &lt;= value &lt;= value+extent &lt;= maximum
 * </pre>
 * @see #getMinimum
 * @see BoundedRangeModel#setMinimum
 */
/*public*/ void DefaultBoundedRangeModel::setMinimum(int n) {
    int newMax = qMax(n, max);
    int newValue = qMax(n, value);
    int newExtent = qMin(newMax - newValue, extent);
    setRangeProperties(newValue, newExtent, n, newMax, isAdjusting);
}


/**
 * Sets the maximum to <I>n</I> after ensuring that <I>n</I>
 * that the other three properties obey the model's constraints:
 * <pre>
 *     minimum &lt;= value &lt;= value+extent &lt;= maximum
 * </pre>
 * @see BoundedRangeModel#setMaximum
 */
/*public*/ void DefaultBoundedRangeModel::setMaximum(int n) {
    int newMin = qMin(n, min);
    int newExtent = qMin(n - newMin, extent);
    int newValue = qMin(n - newExtent, value);
    setRangeProperties(newValue, newExtent, newMin, n, isAdjusting);
}


/**
 * Sets the <code>valueIsAdjusting</code> property.
 *
 * @see #getValueIsAdjusting
 * @see #setValue
 * @see BoundedRangeModel#setValueIsAdjusting
 */
/*public*/ void DefaultBoundedRangeModel::setValueIsAdjusting(bool b) {
    setRangeProperties(value, extent, min, max, b);
}


/**
 * Returns true if the value is in the process of changing
 * as a result of actions being taken by the user.
 *
 * @return the value of the <code>valueIsAdjusting</code> property
 * @see #setValue
 * @see BoundedRangeModel#getValueIsAdjusting
 */
/*public*/ bool DefaultBoundedRangeModel::getValueIsAdjusting() {
    return isAdjusting;
}


/**
 * Sets all of the <code>BoundedRangeModel</code> properties after forcing
 * the arguments to obey the usual constraints:
 * <pre>
 *     minimum &lt;= value &lt;= value+extent &lt;= maximum
 * </pre>
 * <p>
 * At most, one <code>ChangeEvent</code> is generated.
 *
 * @see BoundedRangeModel#setRangeProperties
 * @see #setValue
 * @see #setExtent
 * @see #setMinimum
 * @see #setMaximum
 * @see #setValueIsAdjusting
 */
/*public*/ void DefaultBoundedRangeModel::setRangeProperties(int newValue, int newExtent, int newMin, int newMax, bool adjusting)
{
    if (newMin > newMax) {
        newMin = newMax;
    }
    if (newValue > newMax) {
        newMax = newValue;
    }
    if (newValue < newMin) {
        newMin = newValue;
    }

    /* Convert the addends to long so that extent can be
     * Integer.MAX_VALUE without rolling over the sum.
     * A JCK test covers this, see bug 4097718.
     */
    if (((long)newExtent + (long)newValue) > newMax) {
        newExtent = newMax - newValue;
    }

    if (newExtent < 0) {
        newExtent = 0;
    }

    bool isChange =
        (newValue != value) ||
        (newExtent != extent) ||
        (newMin != min) ||
        (newMax != max) ||
        (adjusting != isAdjusting);

    if (isChange) {
        value = newValue;
        extent = newExtent;
        min = newMin;
        max = newMax;
        isAdjusting = adjusting;

        fireStateChanged();
    }
}


/**
 * Adds a <code>ChangeListener</code>.  The change listeners are run each
 * time any one of the Bounded Range model properties changes.
 *
 * @param l the ChangeListener to add
 * @see #removeChangeListener
 * @see BoundedRangeModel#addChangeListener
 */
/*public*/ void DefaultBoundedRangeModel::addChangeListener(ChangeListener* l) {
//    listenerList.add(ChangeListener.class, l);
}


/**
 * Removes a <code>ChangeListener</code>.
 *
 * @param l the <code>ChangeListener</code> to remove
 * @see #addChangeListener
 * @see BoundedRangeModel#removeChangeListener
 */
/*public*/ void DefaultBoundedRangeModel::removeChangeListener(ChangeListener* l) {
//    listenerList.remove(ChangeListener.class, l);
}


/**
 * Returns an array of all the change listeners
 * registered on this <code>DefaultBoundedRangeModel</code>.
 *
 * @return all of this model's <code>ChangeListener</code>s
 *         or an empty
 *         array if no change listeners are currently registered
 *
 * @see #addChangeListener
 * @see #removeChangeListener
 *
 * @since 1.4
 */
///*public*/ ChangeListener[] DefaultBoundedRangeModel::getChangeListeners() {
//    return listenerList.getListeners(ChangeListener.class);
//}


/**
 * Runs each <code>ChangeListener</code>'s <code>stateChanged</code> method.
 *
 * @see #setRangeProperties
 * @see EventListenerList
 */
/*protected*/ void DefaultBoundedRangeModel::fireStateChanged()
{
#if 0 // TODO:
    Object[] listeners = listenerList.getListenerList();
    for (int i = listeners.length - 2; i >= 0; i -=2 ) {
        if (listeners[i] == ChangeListener.class) {
            if (changeEvent == null) {
                changeEvent = new ChangeEvent(this);
            }
            ((ChangeListener)listeners[i+1]).stateChanged(changeEvent);
        }
    }
#endif
}


/**
 * Returns a string that displays all of the
 * <code>BoundedRangeModel</code> properties.
 */
/*public*/ QString DefaultBoundedRangeModel::toString()  {
    QString modelString =
        "value=" + QString::number(getValue()) + ", " +
        "extent=" + QString::number(getExtent()) + ", " +
        "min=" + QString::number(getMinimum()) + ", " +
        "max=" + QString::number(getMaximum()) + ", " +
        "adj=" + QString::number(getValueIsAdjusting());

    return /*getClass().getName()*/QString("DefaultBoundedRangeModel") + "[" + modelString + "]";
}

/**
 * Returns an array of all the objects currently registered as
 * <code><em>Foo</em>Listener</code>s
 * upon this model.
 * <code><em>Foo</em>Listener</code>s
 * are registered using the <code>add<em>Foo</em>Listener</code> method.
 * <p>
 * You can specify the <code>listenerType</code> argument
 * with a class literal, such as <code><em>Foo</em>Listener.class</code>.
 * For example, you can query a <code>DefaultBoundedRangeModel</code>
 * instance <code>m</code>
 * for its change listeners
 * with the following code:
 *
 * <pre>ChangeListener[] cls = (ChangeListener[])(m.getListeners(ChangeListener.class));</pre>
 *
 * If no such listeners exist,
 * this method returns an empty array.
 *
 * @param listenerType  the type of listeners requested;
 *          this parameter should specify an interface
 *          that descends from <code>java.util.EventListener</code>
 * @return an array of all objects registered as
 *          <code><em>Foo</em>Listener</code>s
 *          on this model,
 *          or an empty array if no such
 *          listeners have been added
 * @exception ClassCastException if <code>listenerType</code> doesn't
 *          specify a class or interface that implements
 *          <code>java.util.EventListener</code>
 *
 * @see #getChangeListeners
 *
 * @since 1.3
 */
///*public*/ <T extends EventListener> T[] getListeners(Class<T> listenerType) {
//    return listenerList.getListeners(listenerType);
//}
//}
