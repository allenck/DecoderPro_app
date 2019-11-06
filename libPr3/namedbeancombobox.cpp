#include "namedbeancombobox.h"
#include "loggerfactory.h"
#include "jmribeancombobox.h"
#include "manager.h"
#include "vptr.h"
#include "comparator.h"
#include "namedbeancomparator.h"
#include "namedbeanusernamecomparator.h"

template<class B>
NamedBeanComboBox<B>::NamedBeanComboBox(QObject *parent)
{

}
/**
 * A {@link javax.swing.JComboBox} for {@link jmri.NamedBean}s.
 * <p>
 * When editable, this will create a new NamedBean if backed by a
 * {@link jmri.ProvidingManager} if {@link #getSelectedItem()} is called and the
 * current text is neither the system name nor user name of an existing
 * NamedBean. This will also validate input when editable, showing an
 * Information (blue I in circle) icon to indicate a name will be used to create
 * a new Named Bean, an Error (red X in circle) icon to indicate a typed in name
 * cannot be used (either because it would not be valid as a user name or system
 * name or because the name of an existing NamedBean not usable in the current
 * context has been entered, or no icon to indicate the name of an existing
 * Named Bean has been entered.
 * <p>
 * When not editable, this will allow (but may not actively show) continual
 * typing of a system name or a user name by a user to match a NamedBean even if
 * only the system name or user name or both are displayed (e.g. if a list of
 * turnouts is shown by user name only, a user may type in the system name of
 * the turnout and the turnout will be selected correctly). If the typing speed
 * is slower than the {@link javax.swing.UIManager}'s
 * {@code ComboBox.timeFactor} setting, keyboard input acts like a normal
 * JComboBox, with only the first character displayed matching the user input.
 * <p>
 * <strong>Note:</strong> It is recommended that implementations that exclude
 * some NamedBeans from the combo box call {@link #setToolTipText(String)} to
 * provide a context specific reason for excluding those items. The default tool
 * tip reads (example for Turnouts) "Turnouts not shown cannot be used in this
 * context.", but a better tool tip (example for Signal Heads when creating a
 * Signal Mast) may be "Signal Heads not shown are assigned to another Signal
 * Mast."
 * <p>
 * To change the tool tip text shown when an existing bean is not selected, this
 * class should be subclassed and the methods {@link #getBeanInUseMessage(java.lang.String, java.lang.String)},
 * {@link #getInvalidNameFormatMessage(java.lang.String, java.lang.String, java.lang.String)},
 * {@link #getNoMatchingBeanMessage(java.lang.String, java.lang.String)}, and
 * {@link #getWillCreateBeanMessage(java.lang.String, java.lang.String)} should
 * be overridden.
 *
 * @param <B> the supported type of NamedBean
 */
// /*public*/ class NamedBeanComboBox<B extends NamedBean> extends JComboBox<B> {
template<class B>
/*private*/ /*final*/ /*static*/ Logger* NamedBeanComboBox<B>::log = LoggerFactory::getLogger("NamedBeanComboBox");

/**
 * Create a ComboBox without a selection using the
 * {@link DisplayOptions#DISPLAYNAME} to sort NamedBeans.
 *
 * @param manager the Manager backing the ComboBox
 */
template<class B>
/*public*/ NamedBeanComboBox<B>::NamedBeanComboBox(ManagerT<B> manager, QObject *parent)
 : QComboBox(parent)
{
    //this(manager, null);
 common(manager, nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
}

/**
 * Create a ComboBox with an existing selection using the
 * {@link DisplayOptions#DISPLAYNAME} to sort NamedBeans.
 *
 * @param manager   the Manager backing the ComboBox
 * @param selection the NamedBean that is selected or null to specify no
 *                  selection
 */
template<class B>
/*public*/ NamedBeanComboBox<B>::NamedBeanComboBox(Manager<B> manager, B selection, QObject*parent)
 : QComboBox(parent)
{
    common(manager, selection, NamedBean::DisplayOptions::DISPLAYNAME);
}

/**
 * Create a ComboBox with an existing selection using the specified display
 * order to sort NamedBeans.
 *
 * @param manager      the Manager backing the ComboBox
 * @param selection    the NamedBean that is selected or null to specify no
 *                     selection
 * @param displayOrder the sorting scheme for NamedBeans
 */
template<class B>
/*public*/ NamedBeanComboBox<B>::NamedBeanComboBox(ManagerT<B> manager, B selection, NamedBean::DisplayOptions* displayOrder, QObject* parent)
 : QComboBox(parent)
{
 common(manager, selection, displayOrder);
 //super();
}

template<class B>
/*private*/ void NamedBeanComboBox<B>::common(ManagerT<B> manager, B selection, JmriBeanComboBox::DisplayOptions* displayOrder)
{
    this->manager = manager;
    QComboBox::setToolTip(tr("%1 not shown cannot be used in this context.").arg(this->manager->getBeanTypeHandled(true)));
    setDisplayOrder(displayOrder);
    /*NamedBeanComboBox.this.*/setEditable(false); // prevent overriding method call in constructor
    NamedBeanRenderer* namedBeanRenderer = new NamedBeanRenderer(/*getRenderer()*/);
    setRenderer(namedBeanRenderer);
    setKeySelectionManager(namedBeanRenderer);
    NamedBeanEditor* namedBeanEditor = new NamedBeanEditor(/*getEditor()*/);
    setEditor(namedBeanEditor);
    this->manager->addPropertyChangeListener("beans", managerListener);
    this->manager->addPropertyChangeListener("DisplayListName", managerListener);
    sort();
    setSelectedItem(selection);
}

template<class B>
/*public*/ ManagerT<B> NamedBeanComboBox<B>::getManager() {
    return manager;
}

template<class B>
/*public*/ JmriBeanComboBox::DisplayOptions* NamedBeanComboBox<B>::getDisplayOrder() {
    return displayOptions;
}

template<class B>
/*public*/ /*final*/ void NamedBeanComboBox<B>::setDisplayOrder(JmriBeanComboBox::DisplayOptions* displayOrder) {
    if (displayOptions != displayOrder) {
        displayOptions = displayOrder;
        sort();
    }
}

/**
 * Is this JComboBox validating typed input?
 *
 * @return true if validating input; false otherwise
 */
/*public*/ bool NamedBeanComboBox::isValidatingInput() {
    return validatingInput;
}

/**
 * Set if this JComboBox validates typed input.
 *
 * @param validatingInput true to validate; false to prevent validation
 */
/*public*/ void NamedBeanComboBox::setValidatingInput(bool validatingInput) {
    this->validatingInput = validatingInput;
}

/**
 * Is this JComboBox allowing a null object to be selected?
 *
 * @return true if allowing a null selection; false otherwise
 */
/*public*/ bool NamedBeanComboBox::isAllowNull() {
    return allowNull;
}

/**
 * Set if this JComboBox allows a null object to be selected. If so, the
 * null object is placed first in the displayed list of NamedBeans.
 *
 * @param allowNull true if allowing a null selection; false otherwise
 */
/*public*/ void NamedBeanComboBox::setAllowNull(bool allowNull) {
    this->allowNull = allowNull;
    if (allowNull && (getModel().getSize() > 0 && getItemAt(0) != null)) {
        this->insertItemAt(null, 0);
    } else if (!allowNull && (getModel().getSize() > 0 && this.getItemAt(0) == null)) {
        this.removeItemAt(0);
    }
}

/**
 * {@inheritDoc}
 *
 * @return the selected item as the supported type of NamedBean, creating a
 *         new NamedBean as needed if {@link #isEditable()} and
 *         {@link #isProviding()} are true, or null if there is no
 *         selection, or {@link #isAllowNull()} is true and the null object
 *         is selected
 */
//@Override
template<class B>
/*public*/ B NamedBeanComboBox<B>::getSelectedItem() {
    B item = getItemAt(currentIndex());
    if (isEditable() && providing && item == null) {
        Component ec = getEditor().getEditorComponent();
        if (ec instanceof JTextComponent && manager instanceof ProvidingManager) {
            JTextComponent jtc = (JTextComponent) ec;
            String text = jtc.getText();
            if (text != null && !text.isEmpty()) {
                if ((manager.isValidSystemNameFormat(text)) || text.equals(NamedBean.normalizeUserName(text))) {
                    ProvidingManager<B> pm = (ProvidingManager<B>) manager;
                    item = pm.provide(jtc.getText());
                }
            }
        }
    }
    return item;
}

template<class B>
/*private*/ B NamedBeanComboBox<B>::getItemAt(int index)
{
 return VPtr<B>::asPtr(itemData(index));
}

/**
 * Check if new NamedBeans can be provided by a
 * {@link jmri.ProvidingManager} when {@link #isEditable} returns
 * {@code true}.
 *
 * @return {@code true} is allowing new NamedBeans to be provided;
 *         {@code false} otherwise
 */
/*public*/ bool NamedBeanComboBox::isProviding() {
    return providing;
}

/**
 * Set if new NamedBeans can be provided by a {@link jmri.ProvidingManager}
 * when {@link #isEditable()} returns {@code true}.
 *
 * @param providing {@code true} to allow new NamedBeans to be provided;
 *                  {@code false} otherwise
 */
/*public*/ void NamedBeanComboBox::setProviding(bool providing) {
    this->providing = providing;
}

//@Override
/*public*/ void NamedBeanComboBox::setEditable(bool editable) {
    if (editable /*&& !(manager instanceof ProvidingManager)*/) {
        log->error("Unable to set editable to true because not backed by editable manager");
        return; // refuse to allow editing if unable to accept user input
    }
    if (editable && !providing) {
        log->error("Refusing to set editable if not allowing new NamedBeans to be created");
        return; // refuse to allow editing if not allowing user input to be accepted
    }
    QComboBox::setEditable(editable);
}

/**
 * Get the display name of the selected item.
 *
 * @return the display name of the selected item or null if the selected
 *         item is null or there is no selection
 */
template<class B>
/*public*/ QString NamedBeanComboBox::getSelectedItemDisplayName() {
    B* item = getSelectedItem();
    //return item != nullptr ? item.getDisplayName() : nullptr;
    return item;
}

/**
 * Get the system name of the selected item.
 *
 * @return the system name of the selected item or null if the selected item
 *         is null or there is no selection
 */
template<class B>
/*public*/ QString NamedBeanComboBox::getSelectedItemSystemName() {
    B item = getSelectedItem();
    //return item != null ? item.getSystemName() : null;
    return item;
}

/**
 * Get the user name of the selected item.
 *
 * @return the user name of the selected item or null if the selected item
 *         is null or there is no selection
 */
template<class B>
/*public*/ QString NamedBeanComboBox<B>::getSelectedItemUserName() {
    B item = getSelectedItem();
    //return item != null ? item.getUserName() : null;
    return item;
}

/**
 * Set the selected item by either its user name or system name.
 *
 * @param name the name of the item to select
 * @throws IllegalArgumentException if {@link #isAllowNull()} is false and
 *                                  no bean exists by name or name is null
 */
template<class B>
/*public*/ void NamedBeanComboBox<B>::setSelectedItemByName(QString name) {
    B item = nullptr;
    if (name != "") {
        item = manager->getNamedBean(name);
    }
    if (item == nullptr && !allowNull) {
        throw IllegalArgumentException();
    }
    setSelectedItem(item);
}

template<class B>
/*private*/ void NamedBeanComboBox<B>::setsetSelectedItem(B item)
{
 setCurrentIndex(this->findData(item));
}

/*public*/ void NamedBeanComboBox::dispose() {
    manager->removePropertyChangeListener(managerListener);
}

template<class B>
/*private*/ void NamedBeanComboBox<B>::sort() {
    B selectedItem = getSelectedItem();
    Comparator<B> comparator = new NamedBeanComparator<B>();
    if (displayOptions != JmriBeanComboBox::DisplayOptions::SYSTEMNAME
            && displayOptions != JmriBeanComboBox::DisplayOptions::QUOTED_SYSTEMNAME) {
        comparator = new NamedBeanUserNameComparator<B>();
    }
#if 0
    TreeSet<B> set = new TreeSet<>(comparator);
    set.addAll(manager.getNamedBeanSet());
    set.removeAll(excludedItems);
    Vector<B> vector = new Vector<>(set);
    if (allowNull) {
        vector.insertElementAt(null, 0);
    }
    setModel(new DefaultComboBoxModel<>(vector));
#endif
    setSelectedItem(selectedItem); // retain selection
}

/**
 * Get the localized message to display in a tooltip when a typed in bean
 * name matches a named bean has been included in a call to
 * {@link #setExcludedItems(java.util.Set)} and {@link #isValidatingInput()}
 * is {@code true}.
 *
 * @param beanType    the type of bean as provided by
 *                    {@link Manager#getBeanTypeHandled()}
 * @param displayName the bean name as provided by
 *                    {@link NamedBean#getDisplayName(jmri.NamedBean.DisplayOptions)}
 *                    with the options in {@link #getDisplayOrder()}
 * @return the localized message
 */
/*public*/ QString NamedBeanComboBox::getBeanInUseMessage(QString beanType, QString displayName) {
    return tr("%1 %2 is not selectable and cannot be used in this context.").arg(beanType).arg(displayName);
}

/**
 * Get the localized message to display in a tooltip when a typed in bean
 * name is not a valid name format for creating a bean.
 *
 * @param beanType  the type of bean as provided by
 *                  {@link Manager#getBeanTypeHandled()}
 * @param text      the typed in name
 * @param exception the localized message text from the exception thrown by
 *                  {@link Manager#validateSystemNameFormat(java.lang.String, java.util.Locale)}
 * @return the localized message
 */
/*public*/ QString NamedBeanComboBox::getInvalidNameFormatMessage(QString beanType, QString text, QString exception) {
    return tr("<html>\"%1\" is not a valid system name.<br>%2</html>\n%3").arg(beanType).arg(text).arg(exception);
}

/**
 * Get the localized message to display when a typed in bean name does not
 * match a named bean, {@link #isValidatingInput()} is {@code true} and
 * {@link #isProviding()} is {@code false}.
 *
 * @param beanType the type of bean as provided by
 *                 {@link Manager#getBeanTypeHandled()}
 * @param text     the typed in name
 * @return the localized message
 */
/*public*/ QString NamedBeanComboBox::getNoMatchingBeanMessage(QString beanType, QString text) {
    return tr("No %1 named \"%2\" exists.").arg(beanType).arg(text);
}

/**
 * Get the localized message to display when a typed in bean name does not
 * match a named bean, {@link #isValidatingInput()} is {@code true} and
 * {@link #isProviding()} is {@code true}.
 *
 * @param beanType the type of bean as provided by
 *                 {@link Manager#getBeanTypeHandled()}
 * @param text     the typed in name
 * @return the localized message
 */
/*public*/ QString NamedBeanComboBox::getWillCreateBeanMessage(QString beanType, QString text) {
    return tr("Will create a %1 named \"%2\".").arg(beanType).arg(text);
}

template<class B>
/*public*/ QSet<B> NamedBeanComboBox<B>::getExcludedItems() {
    return excludedItems;
}

/**
 * Collection of named beans managed by the manager for this combo box that
 * should not be included in the combo box. This may be, for example, a list
 * of SignalHeads already in use, and therefor not available to be added to
 * a SignalMast.
 *
 * @param excludedItems items to be excluded from this combo box
 */
template<class B>
/*public*/ void NamedBeanComboBox<B>::setExcludedItems(QSet<B> excludedItems) {
    this->excludedItems.clear();
    this->excludedItems.addAll(excludedItems);
    sort();
}
#if 0
/*private*/ class NamedBeanEditor implements ComboBoxEditor {

    /*private*/ final ComboBoxEditor editor;

    /**
     * Create a NamedBeanEditor using another editor as its base. This
     * allows the NamedBeanEditor to inherit any platform-specific behaviors
     * that the default editor may implement.
     *
     * @param editor the underlying editor
     */
    /*public*/ NamedBeanEditor(ComboBoxEditor editor) {
        this.editor = editor;
        Component ec = editor.getEditorComponent();
        if (ec instanceof JComponent) {
            JComponent jc = (JComponent) ec;
            jc.setInputVerifier(new JInputValidator(jc, true, false) {
                //@Override
                protected Validation getValidation(JComponent component, JInputValidatorPreferences preferences) {
                    if (component instanceof JTextComponent) {
                        JTextComponent jtc = (JTextComponent) component;
                        String text = jtc.getText();
                        if (text != null && !text.isEmpty()) {
                            B bean = manager.getNamedBean(text);
                            if (bean != null) {
                                setSelectedItem(bean); // won't change if bean is not in model
                                if (!bean.equals(getSelectedItem())) {
                                    jtc.setText(text);
                                    if (validatingInput) {
                                        return new Validation(Validation.Type.DANGER,
                                                getBeanInUseMessage(manager.getBeanTypeHandled(), bean.getDisplayName(DisplayOptions.QUOTED_DISPLAYNAME)),
                                                preferences);
                                    }
                                }
                            } else {
                                if (validatingInput) {
                                    if (providing) {
                                        try {
                                            manager.validateSystemNameFormat(text); // ignore output, we only want to catch exceptions
                                        } catch (IllegalArgumentException ex) {
                                            return new Validation(Validation.Type.DANGER,
                                                    getInvalidNameFormatMessage(manager.getBeanTypeHandled(), text, ex.getLocalizedMessage()),
                                                    preferences);
                                        }
                                        return new Validation(Validation.Type.INFORMATION,
                                                getWillCreateBeanMessage(manager.getBeanTypeHandled(), text),
                                                preferences);
                                    } else {
                                        return new Validation(Validation.Type.WARNING,
                                                getNoMatchingBeanMessage(manager.getBeanTypeHandled(), text),
                                                preferences);
                                    }
                                }
                            }
                        }
                    }
                    return getNoneValidation();
                }
            });
        }
    }

    //@Override
    /*public*/ Component getEditorComponent() {
        return editor.getEditorComponent();
    }

    //@Override
    /*public*/ void setItem(Object anObject) {
        Component c = getEditorComponent();
        if (c instanceof JTextComponent) {
            JTextComponent jtc = (JTextComponent) c;
            if (anObject != null && anObject instanceof NamedBean) {
                NamedBean nb = (NamedBean) anObject;
                jtc.setText(nb.getDisplayName(displayOptions));
            } else {
                jtc.setText("");
            }
        } else {
            editor.setItem(anObject);
        }
    }

    //@Override
    /*public*/ Object getItem() {
        return editor.getItem();
    }

    //@Override
    /*public*/ void selectAll() {
        editor.selectAll();
    }

    //@Override
    /*public*/ void addActionListener(ActionListener l) {
        editor.addActionListener(l);
    }

    //@Override
    /*public*/ void removeActionListener(ActionListener l) {
        editor.removeActionListener(l);
    }
}

/*private*/ class NamedBeanRenderer implements ListCellRenderer<B>, JComboBox.KeySelectionManager {

    /*private*/ final ListCellRenderer<? super B> renderer;
    /*private*/ final long timeFactor;
    /*private*/ long lastTime;
    /*private*/ long time;
    /*private*/ String prefix = "";

    /*public*/ NamedBeanRenderer(ListCellRenderer<? super B> renderer) {
        this.renderer = renderer;
        Long l = (Long) UIManager.get("ComboBox.timeFactor");
        timeFactor = l != null ? l : 1000;
    }

    //@Override
    /*public*/ Component getListCellRendererComponent(JList<? extends B> list, B value, int index, boolean isSelected,
            boolean cellHasFocus) {
        JLabel label = (JLabel) renderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
        if (value != null) {
            label.setText(value.getDisplayName(displayOptions));
        }
        return label;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@SuppressWarnings("unchecked") // unchecked cast due to API constraints
    /*public*/ int selectionForKey(char key, ComboBoxModel model) {
        time = System.currentTimeMillis();

        //  Get the index of the currently selected item
        int size = model.getSize();
        int startIndex = -1;
        B selectedItem = (B) model.getSelectedItem();

        if (selectedItem != null) {
            for (int i = 0; i < size; i++) {
                if (selectedItem == model.getElementAt(i)) {
                    startIndex = i;
                    break;
                }
            }
        }

        //  Determine the "prefix" to be used when searching the model. The
        //  prefix can be a single letter or multiple letters depending on how
        //  fast the user has been typing and on which letter has been typed.
        if (time - lastTime < timeFactor) {
            if ((prefix.length() == 1) && (key == prefix.charAt(0))) {
                // Subsequent same key presses move the keyboard focus to the next
                // object that starts with the same letter.
                startIndex++;
            } else {
                prefix += key;
            }
        } else {
            startIndex++;
            prefix = "" + key;
        }

        lastTime = time;

        //  Search from the current selection and wrap when no match is found
        if (startIndex < 0 || startIndex >= size) {
            startIndex = 0;
        }

        int index = getNextMatch(prefix, startIndex, size, model);

        if (index < 0) {
            // wrap
            index = getNextMatch(prefix, 0, startIndex, model);
        }

        return index;
    }

    /**
     * Find the index of the item in the model that starts with the prefix.
     */
    //@SuppressWarnings("unchecked") // unchecked cast due to API constraints
    /*private*/ int getNextMatch(String prefix, int start, int end, ComboBoxModel model) {
        for (int i = start; i < end; i++) {
            B item = (B) model.getElementAt(i);

            if (item != null) {
                String userName = item.getUserName();

                if (item.getSystemName().toLowerCase().startsWith(prefix)
                        || (userName != null && userName.toLowerCase().startsWith(prefix))) {
                    return i;
                }
            }
        }
        return -1;
    }
}
#endif
