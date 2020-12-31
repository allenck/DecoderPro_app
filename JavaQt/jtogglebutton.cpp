#include "jtogglebutton.h"
#include "../LayoutEditor/namedicon.h"
#include <QButtonGroup>

const QString JToggleButton::uiClassID = "ToggleButtonUI";

//JToggleButton::JToggleButton(QWidget *parent) :
//    QAbstractButton(parent)
//{
//}
/**
 * An implementation of a two-state button.
 * The <code>JRadioButton</code> and <code>JCheckBox</code> classes
 * are subclasses of this class.
 * For information on using them see
 * <a
 href="http://java.sun.com/docs/books/tutorial/uiswing/components/button.html">How to Use Buttons, Check Boxes, and Radio Buttons</a>,
 * a section in <em>The Java Tutorial</em>.
 * <p>
 * Buttons can be configured, and to some degree controlled, by
 * <code><a href="Action.html">Action</a></code>s.  Using an
 * <code>Action</code> with a button has many benefits beyond directly
 * configuring a button.  Refer to <a href="Action.html#buttonActions">
 * Swing Components Supporting <code>Action</code></a> for more
 * details, and you can find more information in <a
 * href="http://java.sun.com/docs/books/tutorial/uiswing/misc/action.html">How
 * to Use Actions</a>, a section in <em>The Java Tutorial</em>.
 * <p>
 * <strong>Warning:</strong> Swing is not thread safe. For more
 * information see <a
 * href="package-summary.html#threading">Swing's Threading
 * Policy</a>.
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
 * @beaninfo
 *   attribute: isContainer false
 * description: An implementation of a two-state button.
 *
 * @see JRadioButton
 * @see JCheckBox
 * @author Jeff Dinkins
 */
//public class JToggleButton extends AbstractButton implements Accessible {

/**
 * @see #getUIClassID
 * @see #readObject
 */

/**
 * Creates an initially unselected toggle button
 * without setting the text or image.
 */
/*public*/ JToggleButton::JToggleButton (QWidget *parent) : QPushButton(parent)
{
    //this(NULL, NULL, false);
    init();
}

/**
 * Creates an initially unselected toggle button
 * with the specified image but no text.
 *
 * @param icon  the image that the button should display
 */
/*public*/ JToggleButton::JToggleButton(QIcon icon, QWidget *parent) : QPushButton(icon,"",parent)
{
    //this(NULL, icon, false);
    init();
}
/*public*/ JToggleButton::JToggleButton(NamedIcon* icon, QWidget *parent) : QPushButton("",parent)
{
    //this(NULL, icon, false);
    init();
    setIcon(QIcon(QPixmap::fromImage(icon->getImage())));
    this->icon  = icon;
    setIconSize(QSize(this->icon->getIconWidth(),this->icon->getIconHeight()));
    setMaximumSize(icon->getIconWidth() + 8, icon->getIconHeight()+8);
    setMinimumHeight(icon->getIconHeight() + 8);
}

/**
 * Creates a toggle button with the specified image
 * and selection state, but no text.
 *
 * @param icon  the image that the button should display
 * @param selected  if true, the button is initially selected;
 *                  otherwise, the button is initially unselected
 */
/*public*/ JToggleButton::JToggleButton(QIcon icon, bool selected, QWidget *parent) : QPushButton(icon, "", parent)
{
 //this(NULL, icon, selected);
 init();
 setChecked(selected);
}

/**
 * Creates an unselected toggle button with the specified text.
 *
 * @param text  the string displayed on the toggle button
 */
/*public*/ JToggleButton::JToggleButton (QString text, QWidget *parent) : QPushButton(text,parent)
{
 //this(text, NULL, false);
 init();
}

/**
 * Creates a toggle button with the specified text
 * and selection state.
 *
 * @param text  the string displayed on the toggle button
 * @param selected  if true, the button is initially selected;
 *                  otherwise, the button is initially unselected
 */
/*public*/ JToggleButton::JToggleButton (QString text, bool selected, QWidget *parent) :QPushButton(text,parent)
{
    //this(text, NULL, selected);
    init();
    //this->_selected = !selected;
    this->setChecked(selected);
}

/**
 * Creates a toggle button where properties are taken from the
 * Action supplied.
 *
 * @since 1.3
 */
///*public*/ JToggleButton::JToggleButton(QAction* a, QWidget *parent) {
//    //this();
////    setAction(a);
//}

/**
 * Creates a toggle button that has the specified text and image,
 * and that is initially unselected.
 *
 * @param text the string displayed on the button
 * @param icon  the image that the button should display
 */
/*public*/ JToggleButton::JToggleButton(QString text, QIcon icon, QWidget *parent) :QPushButton(icon,text,parent){
//    this(text, icon, false);
    init();
}
/*public*/ JToggleButton::JToggleButton(QString text, NamedIcon* icon, QWidget *parent) :QPushButton(text,parent){
//    this(text, icon, false);
    init();
    setIcon(QIcon(QPixmap::fromImage(icon->getImage())));
    this->icon  = icon;
    setIconSize(QSize(this->icon->getIconWidth(),this->icon->getIconHeight()));
    setMaximumSize(icon->getIconWidth() + 8, icon->getIconHeight()+8);
    setMinimumHeight(icon->getIconHeight() + 8);
}

/**
 * Creates a toggle button with the specified text, image, and
 * selection state.
 *
 * @param text the text of the toggle button
 * @param icon  the image that the button should display
 * @param selected  if true, the button is initially selected;
 *                  otherwise, the button is initially unselected
 */
/*public*/ JToggleButton::JToggleButton (QString text, QIcon icon, bool selected, QWidget *parent) :QPushButton(icon,text,parent)
{
    // Create the model
//    setModel(new ToggleButtonModel());

//    model.setSelected(selected);

    // initialize
//    init(text, icon);
    init();
}
void JToggleButton::init()
{
 setCheckable(true);
// QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
// sizePolicy.setHorizontalStretch(0);
// sizePolicy.setVerticalStretch(0);
// sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
// this->setSizePolicy(sizePolicy);
 //connect(this, SIGNAL(clicked()), this, SLOT(toggleSelect()));
 //this->_selected = false;
 //this->setSelected(false);
 setChecked(false);
 setStyleSheet("QPushButton {border: 2px solid #8f8f91; border-radius: 6px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #aaabae); min-width: 15px;} ");
}

/**
 * Resets the UI property to a value from the current look and feel.
 *
 * @see JComponent#updateUI
 */
/*public*/ void JToggleButton::updateUI() {
//    setUI((ButtonUI)UIManager.getUI(this));
}

/**
 * Returns a string that specifies the name of the l&f class
 * that renders this component.
 *
 * @return String "ToggleButtonUI"
 * @see JComponent#getUIClassID
 * @see UIDefaults#getUI
 * @beaninfo
 *  description: A string that specifies the name of the L&F class
 */
/*public*/ QString JToggleButton::getUIClassID() {
    return uiClassID;
}


/**
 * Overriden to return true, JToggleButton supports
 * the selected state.
 */
bool shouldUpdateSelectedStateFromAction() {
    return true;
}

// *********************************************************************
#if 0 // TODO:
/**
 * The ToggleButton model
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
/*public*/ static class ToggleButtonModel extends DefaultButtonModel {

    /**
     * Creates a new ToggleButton Model
     */
    /*public*/ ToggleButtonModel () {
    }
#endif
/**
 * Checks if the button is selected.
 */
/*public*/ bool JToggleButton::isSelected() {
//              if(group() != NULL) {
//                  return group()->isSelected(this);
//              } else {
//            return (stateMask & SELECTED) != 0;
//              }
 return isChecked();
}


/**
 * Sets the selected state of the button.
 * @param b true selects the toggle button,
 *          false deselects the toggle button.
 */
/*public*/ void JToggleButton::setSelected(bool b)
{
// QButtonGroup* group = group();
// if (group != NULL)
// {
//  // use the group model instead
//  group->setSelected(this, b);
//  b = group->isSelected(this);
// }


 if (isChecked() == b)
 {
  return;
 }

//    if (b) {
//        stateMask |= SELECTED;
//    } else {
//        stateMask &= ~SELECTED;
//    }
 //_selected=b;
 setChecked(b);

 if(isChecked())
  setStyleSheet("border: 2px solid #8f8f91; border-radius: 6px; background-color gray; min-width: 15px;");
 else
  setStyleSheet("border: 2px solid #8f8f91; border-radius: 6px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 #dadbde); min-width: 15px;");
//    // Send ChangeEvent
//    fireStateChanged();
 //emit selected(isChecked());
 emit toggled(isChecked());

//    // Send ItemEvent
//    fireItemStateChanged(
//            new ItemEvent(this,
//                          ItemEvent.ITEM_STATE_CHANGED,
//                          this,
//                          this.isSelected() ?  ItemEvent.SELECTED : ItemEvent.DESELECTED));

}
#if 0
    /**
     * Sets the pressed state of the toggle button.
     */
    /*public*/ void setPressed(boolean b) {
        if ((isPressed() == b) || !isEnabled()) {
            return;
        }

        if (b == false && isArmed()) {
            setSelected(!this.isSelected());
        }

        if (b) {
            stateMask |= PRESSED;
        } else {
            stateMask &= ~PRESSED;
        }

        fireStateChanged();

        if(!isPressed() && isArmed()) {
            int modifiers = 0;
            AWTEvent currentEvent = EventQueue.getCurrentEvent();
            if (currentEvent instanceof InputEvent) {
                modifiers = ((InputEvent)currentEvent).getModifiers();
            } else if (currentEvent instanceof ActionEvent) {
                modifiers = ((ActionEvent)currentEvent).getModifiers();
            }
            fireActionPerformed(
                new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
                                getActionCommand(),
                                EventQueue.getMostRecentEventTime(),
                                modifiers));
        }

    }
}


/**
 * See readObject() and writeObject() in JComponent for more
 * information about serialization in Swing.
 */
private void writeObject(ObjectOutputStream s) throws IOException {
    s.defaultWriteObject();
    if (getUIClassID().equals(uiClassID)) {
        byte count = JComponent.getWriteObjCounter(this);
        JComponent.setWriteObjCounter(this, --count);
        if (count == 0 && ui != NULL) {
            ui.installUI(this);
        }
    }
}


/**
 * Returns a string representation of this JToggleButton. This method
 * is intended to be used only for debugging purposes, and the
 * content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not
 * be <code>NULL</code>.
 *
 * @return  a string representation of this JToggleButton.
 */
protected String paramString() {
    return super.paramString();
}


/////////////////
// Accessibility support
////////////////

/**
 * Gets the AccessibleContext associated with this JToggleButton.
 * For toggle buttons, the AccessibleContext takes the form of an
 * AccessibleJToggleButton.
 * A new AccessibleJToggleButton instance is created if necessary.
 *
 * @return an AccessibleJToggleButton that serves as the
 *         AccessibleContext of this JToggleButton
 * @beaninfo
 *       expert: true
 *  description: The AccessibleContext associated with this ToggleButton.
 */
/*public*/ AccessibleContext getAccessibleContext() {
    if (accessibleContext == NULL) {
        accessibleContext = new AccessibleJToggleButton();
    }
    return accessibleContext;
}

/**
 * This class implements accessibility support for the
 * <code>JToggleButton</code> class.  It provides an implementation of the
 * Java Accessibility API appropriate to toggle button user-interface
 * elements.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
protected class AccessibleJToggleButton extends AccessibleAbstractButton
        implements ItemListener {

    /*public*/ AccessibleJToggleButton() {
        super();
        JToggleButton.this.addItemListener(this);
    }

    /**
     * Fire accessible property change events when the state of the
     * toggle button changes.
     */
    /*public*/ void itemStateChanged(ItemEvent e) {
        JToggleButton tb = (JToggleButton) e.getSource();
        if (JToggleButton.this.accessibleContext != NULL) {
            if (tb.isSelected()) {
                JToggleButton.this.accessibleContext.firePropertyChange(
                        AccessibleContext.ACCESSIBLE_STATE_PROPERTY,
                        NULL, AccessibleState.CHECKED);
            } else {
                JToggleButton.this.accessibleContext.firePropertyChange(
                        AccessibleContext.ACCESSIBLE_STATE_PROPERTY,
                        AccessibleState.CHECKED, NULL);
            }
        }
    }

    /**
     * Get the role of this object.
     *
     * @return an instance of AccessibleRole describing the role of the
     * object
     */
    /*public*/ AccessibleRole getAccessibleRole() {
        return AccessibleRole.TOGGLE_BUTTON;
    }
} // inner class AccessibleJToggleButton
#endif
NamedIcon* JToggleButton::getIcon()
{
    return icon;
}
void JToggleButton::setSelectedIcon(NamedIcon *icon)
{
    setIcon(QIcon(QPixmap::fromImage(icon->getImage())));
    this->icon  = icon;
    setIconSize(QSize(this->icon->getIconWidth(),this->icon->getIconHeight()));
    setMinimumHeight(this->icon->getIconHeight());
}

void JToggleButton::toggleSelect()
{
 //setSelected(!_selected);
 toggle();
 //emit selected(isChecked());
 emit toggled(isChecked());
}

void JToggleButton::setText(const QString &text)
{
 QAbstractButton::setText(text);
 resize(minimumSize());
}

/**
 * Gets the location of this component in the form of a point
 * specifying the component's top-left corner in the screen's
 * coordinate space.
 * @return an instance of <code>Point</code> representing
 *          the top-left corner of the component's bounds in the
 *          coordinate space of the screen
 * @throws IllegalComponentStateException if the
 *          component is not showing on the screen
 * @see #setLocation
 * @see #getLocation
 */
/*public*/ QPoint JToggleButton::getLocationOnScreen() {
//    synchronized (getTreeLock()) {
//        return getLocationOnScreen_NoTreeLock();
 return window()->pos();
}
