#include "abstractaction.h"
#include "propertychangeevent.h"
#include "propertychangelistener.h"

//AbstractAction::AbstractAction(QObject *parent) :
//  Action(parent)
//{
//}

/**
 * This class provides default implementations for the JFC <code>Action</code>
 * interface. Standard behaviors like the get and set methods for
 * <code>Action</code> object properties (icon, text, and enabled) are defined
 * here. The developer need only subclass this abstract class and
 * define the <code>actionPerformed</code> method.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Georges Saab
 * @see Action
 */
///*public*/  abstract class AbstractAction implements Action, Cloneable, Serializable
//{
/**
 * Whether or not actions should reconfigure all properties on NULL.
 */
/*private*/ /*static*/ bool AbstractAction::RECONFIGURE_ON_NULL = false;




/**
 * Whether or not to reconfigure all action properties from the
 * specified event.
 */
/*static*/ bool AbstractAction::shouldReconfigure(PropertyChangeEvent* e)
{
 if (e->getPropertyName() == NULL)
 {
  /*synchronized(AbstractAction.class) */
  {
//            if (RECONFIGURE_ON_NULL == NULL) {
//                RECONFIGURE_ON_NULL = Boolean.valueOf(
//                    AccessController.doPrivileged(new GetPropertyAction(
//                    "swing.actions.reconfigureOnNull", "false")));
//            }
   return RECONFIGURE_ON_NULL;
  }
 }
 return false;
}

/**
 * Sets the enabled state of a component from an Action.
 *
 * @param c the Component to set the enabled state on
 * @param a the Action to set the enabled state from, may be NULL
 */
/*static*/ void AbstractAction::setEnabledFromAction(QWidget* c, Action* a) {
    c->setEnabled((a != NULL) ? a->isEnabled() : true);
}

/**
 * Sets the tooltip text of a component from an Action.
 *
 * @param c the Component to set the tooltip text on
 * @param a the Action to set the tooltip text from, may be NULL
 */
/*static*/ void AbstractAction::setToolTipTextFromAction(QWidget* c, Action* a) {
    c->setToolTip(a != NULL ?
       a->getValue(Action::SHORT_DESCRIPTION).toString() : "");
}

/*static*/ bool AbstractAction::hasSelectedKey(Action* a)
{
 return (a != NULL && a->getValue(Action::SELECTED_KEY) != QVariant());
}

/*static*/ bool AbstractAction::isSelected(Action* a)
{
 return true == (a->getValue(Action::SELECTED_KEY));
}



/**
 * Creates an {@code Action}.
 */
/*public*/  AbstractAction::AbstractAction(QObject *parent) :
  Action("?", parent)
{
 common();
}

/**
 * Creates an {@code Action} with the specified name.
 *
 * @param name the name ({@code Action.NAME}) for the action; a
 *        value of {@code NULL} is ignored
 */
/*public*/  AbstractAction::AbstractAction(QString name, QObject *parent) :
  Action(name, parent) {
 common();
    putValue(Action::NAME, name);
}

/**
 * Creates an {@code Action} with the specified name and small icon.
 *
 * @param name the name ({@code Action.NAME}) for the action; a
 *        value of {@code NULL} is ignored
 * @param icon the small icon ({@code Action.SMALL_ICON}) for the action; a
 *        value of {@code NULL} is ignored
 */
/*public*/  AbstractAction::AbstractAction(QString name, QIcon icon, QObject* parent)
 : Action(name, icon, parent)
{
 //this(name);
 common();
 putValue(Action::SMALL_ICON, icon);
}
void AbstractAction::common()
{
 enabled = true;
 arrayTable = NULL;
}

/**
 * Gets the <code>Object</code> associated with the specified key.
 *
 * @param key a string containing the specified <code>key</code>
 * @return the binding <code>Object</code> stored with this key; if there
 *          are no keys, it will return <code>NULL</code>
 * @see Action#getValue
 */
/*public*/  QVariant AbstractAction::getValue(QString key)
{
 if (key == "enabled")
 {
  return enabled;
 }
 if (arrayTable == NULL)
 {
  return QVariant();
 }
 return arrayTable->value(key);
}

/**
 * Sets the <code>Value</code> associated with the specified key.
 *
 * @param key  the <code>String</code> that identifies the stored object
 * @param newValue the <code>Object</code> to store using this key
 * @see Action#putValue
 */
/*public*/  void AbstractAction::putValue(QString key, QVariant newValue)
{
 QVariant oldValue = QVariant();
 if (key == "enabled")
 {
     // Treat putValue("enabled") the same way as a call to setEnabled.
     // If we don't do this it means the two may get out of sync, and a
     // bogus property change notification would be sent.
     //
     // To avoid dependencies between putValue & setEnabled this
     // directly changes enabled. If we instead called setEnabled
     // to change enabled, it would be possible for stack
     // overflow in the case where a developer implemented setEnabled
     // in terms of putValue.
  if (newValue == QVariant() || !(newValue.canConvert<bool>()))
  {
   newValue = false;
  }
  oldValue = enabled;
  enabled = newValue.toBool();
 }
 else
 {
  if (arrayTable == NULL) {
      arrayTable = new QMap<QString, QVariant>();
  }
  if (arrayTable->contains(key))
      oldValue = arrayTable->value(key);
  // Remove the entry for key if newValue is NULL
  // else put in the newValue for key.
  if (newValue == QVariant()) {
      arrayTable->remove(key);
  } else {
      arrayTable->insert(key,newValue);
  }
 }
 firePropertyChange(key, oldValue, newValue);
}

/**
 * Returns true if the action is enabled.
 *
 * @return true if the action is enabled, false otherwise
 * @see Action#isEnabled
 */
/*public*/  bool AbstractAction::isEnabled() {
    return enabled;
}

/**
 * Sets whether the {@code Action} is enabled. The default is {@code true}.
 *
 * @param newValue  {@code true} to enable the action, {@code false} to
 *                  disable it
 * @see Action#setEnabled
 */
/*public*/  void AbstractAction::setEnabled(bool newValue) {
    bool oldValue = this->enabled;

    if (oldValue != newValue) {
        this->enabled = newValue;
        firePropertyChange("enabled",
                          (oldValue),(newValue));
    }
}


/**
 * Returns an array of <code>Object</code>s which are keys for
 * which values have been set for this <code>AbstractAction</code>,
 * or <code>NULL</code> if no keys have values set.
 * @return an array of key objects, or <code>NULL</code> if no
 *                  keys have values set
 * @since 1.3
 */
/*public*/  QStringList  AbstractAction::getKeys() {
    if (arrayTable == NULL) {
     return QStringList();
    }
    //Object[] keys = new Object[arrayTable.size()];
//    arrayTable.getKeys(keys);
//    return keys;
    return arrayTable->keys();
}


/**
 * Supports reporting bound property changes.  This method can be called
 * when a bound property has changed and it will send the appropriate
 * <code>PropertyChangeEvent</code> to any registered
 * <code>PropertyChangeListeners</code>.
 */
/*protected*/  void AbstractAction::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue) {
//    if (changeSupport == NULL ||
//        (oldValue != NULL && newValue != NULL && oldValue.equals(newValue))) {
//        return;
//    }
    //changeSupport.firePropertyChange(propertyName, oldValue, newValue);
    emit propertyChange(new PropertyChangeEvent(this, propertyName, oldValue, newValue));
}


/**
 * Adds a <code>PropertyChangeListener</code> to the listener list.
 * The listener is registered for all properties.
 * <p>
 * A <code>PropertyChangeEvent</code> will get fired in response to setting
 * a bound property, e.g. <code>setFont</code>, <code>setBackground</code>,
 * or <code>setForeground</code>.
 * Note that if the current component is inheriting its foreground,
 * background, or font from its container, then no event will be
 * fired in response to a change in the inherited property.
 *
 * @param listener  The <code>PropertyChangeListener</code> to be added
 *
 * @see Action#addPropertyChangeListener
 */
/*public*/  /*synchronized*/ void AbstractAction::addPropertyChangeListener(PropertyChangeListener* listener) {
//    if (changeSupport == NULL) {
//        changeSupport = new SwingPropertyChangeSupport(this);
//    }
//    changeSupport.addPropertyChangeListener(listener);
 connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
}


/**
 * Removes a <code>PropertyChangeListener</code> from the listener list.
 * This removes a <code>PropertyChangeListener</code> that was registered
 * for all properties.
 *
 * @param listener  the <code>PropertyChangeListener</code> to be removed
 *
 * @see Action#removePropertyChangeListener
 */
/*public*/  /*synchronized*/ void AbstractAction::removePropertyChangeListener(PropertyChangeListener* listener) {
//    if (changeSupport == NULL) {
//        return;
//    }
//    changeSupport.removePropertyChangeListener(listener);
 disconnect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
}

#if 0
/**
 * Returns an array of all the <code>PropertyChangeListener</code>s added
 * to this AbstractAction with addPropertyChangeListener().
 *
 * @return all of the <code>PropertyChangeListener</code>s added or an empty
 *         array if no listeners have been added
 * @since 1.4
 */
/*public*/  /*synchronized*/ PropertyChangeListener[] getPropertyChangeListeners() {
    if (changeSupport == NULL) {
        return new PropertyChangeListener[0];
    }
    return changeSupport.getPropertyChangeListeners();
}
#endif

/**
 * Clones the abstract action. This gives the clone
 * its own copy of the key/value list,
 * which is not handled for you by <code>Object.clone()</code>.
 **/

/*protected*/  QVariant clone() /*throws CloneNotSupportedException*/ {
#if 0
    AbstractAction* newAction = (AbstractAction*)super.clone();
    /*synchronized(this)*/ {
        if (arrayTable != NULL) {
            newAction.arrayTable = (ArrayTable)arrayTable.clone();
        }
    }
    return newAction;
#endif
    return QVariant();
}
#if 0
/*private*/ void writeObject(ObjectOutputStream s) throws IOException {
    // Store the default fields
    s.defaultWriteObject();

    // And the keys
    ArrayTable.writeArrayTable(s, arrayTable);
}

/*private*/ void readObject(ObjectInputStream s) throws ClassNotFoundException,
    IOException {
    s.defaultReadObject();
    for (int counter = s.readInt() - 1; counter >= 0; counter--) {
        putValue((String)s.readObject(), s.readObject());
    }
}
#endif
