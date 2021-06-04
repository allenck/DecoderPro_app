#include "namedbeancombobox.h"
#include "vptr.h"
#include "loggerfactory.h"
#include "namedbeanusernamecomparator.h"
#include "propertychangesupport.h"
#include "abstractmanager.h"

NamedBeanComboBox::NamedBeanComboBox(QWidget *parent): JComboBox(parent)
{
 excludedItems = QSet<NamedBean*>();
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
 * class should be subclassed and the methods
 * {@link #getBeanInUseMessage(java.lang.String, java.lang.String)},
 * {@link #getInvalidNameFormatMessage(java.lang.String, java.lang.String, java.lang.String)},
 * {@link #getNoMatchingBeanMessage(java.lang.String, java.lang.String)}, and
 * {@link #getWillCreateBeanMessage(java.lang.String, java.lang.String)} should
 * be overridden.
 *
 * @param <B> the supported type of NamedBean
 */
///*public*/ class NamedBeanComboBox<B extends NamedBean> extends JComboBox<B> {

/*private*/ /*static*/ /*final*/ Logger* NamedBeanComboBox::log = LoggerFactory::getLogger("NamedBeanComboBox");

/**
 * Create a ComboBox without a selection using the
 * {@link DisplayOptions#DISPLAYNAME} to sort NamedBeans.
 *
 * @param manager the Manager backing the ComboBox
 */
/*public*/ NamedBeanComboBox::NamedBeanComboBox(Manager/*<B>*/* manager, QWidget *parent)
: JComboBox(parent)
{
    //this(manager, null);
  this->manager = manager;
  JComboBox::setToolTip(
         tr("%1 not shown cannot be used in this context.").arg(this->manager->getBeanTypeHandled(true)));
 this->setEditable(false); // prevent overriding method
#if 0
    NamedBeanRenderer namedBeanRenderer = new NamedBeanRenderer(getRenderer());
    setRenderer(namedBeanRenderer);
    setKeySelectionManager(namedBeanRenderer);
    NamedBeanEditor namedBeanEditor = new NamedBeanEditor(getEditor());
    setEditor(namedBeanEditor);
#endif
    ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("beans", managerListener);
    ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("DisplayListName", managerListener);
    sort();
}

/**
 * Create a ComboBox with an existing selection using the
 * {@link DisplayOptions#DISPLAYNAME} to sort NamedBeans.
 *
 * @param manager   the Manager backing the ComboBox
 * @param selection the NamedBean that is selected or null to specify no
 *                  selection
 */
/*public*/ NamedBeanComboBox::NamedBeanComboBox(Manager/*<B>*/* manager, NamedBean* selection, QWidget* parent)
  : JComboBox( parent)
{
    //this(manager, selection, DisplayOptions::DISPLAYNAME);
  this->manager = manager;
  JComboBox::setToolTip(
         tr("%1 not shown cannot be used in this context.").arg(((AbstractManager*)this->manager->self())->getBeanTypeHandled(true)));
 setDisplayOrder(NamedBean::DisplayOptions::DISPLAYNAME);
 this->setEditable(false); // prevent overriding method
#if 0
    NamedBeanRenderer namedBeanRenderer = new NamedBeanRenderer(getRenderer());
    setRenderer(namedBeanRenderer);
    setKeySelectionManager(namedBeanRenderer);
    NamedBeanEditor namedBeanEditor = new NamedBeanEditor(getEditor());
    setEditor(namedBeanEditor);
#endif
    ((PropertyChangeSupport*)((AbstractManager*)this->manager->self()))->addPropertyChangeListener("beans", managerListener);
    ((PropertyChangeSupport*)((AbstractManager*)this->manager->self()))->addPropertyChangeListener("DisplayListName", managerListener);
    sort();
    setSelectedItem(selection);
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
/*public*/ NamedBeanComboBox::NamedBeanComboBox(Manager/*<B>*/* manager, NamedBean* selection, NamedBean::DisplayOptions displayOrder, QWidget* parent)
 : JComboBox(parent)
{
    //super();
    this->manager = manager;
//    JComboBox::setToolTip(
//            tr("%1 not shown cannot be used in this context.").arg(this->manager->getBeanTypeHandled(true)));
    setDisplayOrder(displayOrder);
    this->setEditable(false); // prevent overriding method
                                               // call in constructor
#if 0
    NamedBeanRenderer namedBeanRenderer = new NamedBeanRenderer(getRenderer());
    setRenderer(namedBeanRenderer);
    setKeySelectionManager(namedBeanRenderer);
    NamedBeanEditor namedBeanEditor = new NamedBeanEditor(getEditor());
    setEditor(namedBeanEditor);
#endif
    ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("beans", managerListener);
    ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("DisplayListName", managerListener);
    sort();
    setSelectedItem(selection);
}

/*public*/ Manager/*<B>*/* NamedBeanComboBox::getManager() {
    return manager;
}

/*public*/NamedBean::DisplayOptions NamedBeanComboBox::getDisplayOrder() {
    return displayOptions;
}

/*public*/ /*final*/ void NamedBeanComboBox::setDisplayOrder(NamedBean::DisplayOptions displayOrder) {
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
    if (allowNull && (/*getModel().getSize()*/count() > 0 && /*getItemAt(0)*/itemData(0) != QVariant())) {
        this->insertItem(0, "");
    } else if (!allowNull && (/*getModel().getSize()*/count() > 0 && this->itemData(0) == QVariant())) {
        this->removeItem(0);
    }
}

/**
 * {@inheritDoc}
 * <p>
 * To get the current selection <em>without</em> potentially creating a
 * NamedBean call {@link #getItemAt(int)} with {@link #getSelectedIndex()}
 * as the index instead (as in {@code getItemAt(getSelectedIndex())}).
 *
 * @return the selected item as the supported type of NamedBean, creating a
 *         new NamedBean as needed if {@link #isEditable()} and
 *         {@link #isProviding()} are true, or null if there is no
 *         selection, or {@link #isAllowNull()} is true and the null object
 *         is selected
 */
//@Override
/*public*/ NamedBean* NamedBeanComboBox::getSelectedItem() {
    QString txt = currentText();
    QVariant var = currentData();
    NamedBean* item = VPtr<NamedBean>::asPtr(currentData());
    if (isEditable() && providing && item == nullptr)
    {
  #if 0
        Component ec = getEditor().getEditorComponent();
        if (ec instanceof JTextComponent && manager instanceof ProvidingManager) {
            JTextComponent jtc = (JTextComponent) ec;
            userInput = jtc.getText();
            if (userInput != null &&
                    !userInput.isEmpty() &&
                    ((manager.isValidSystemNameFormat(userInput)) || userInput.equals(NamedBean.normalizeUserName(userInput)))) {
                ProvidingManager/*<B>*/* pm = (ProvidingManager/*<B>*/*) manager;
                item = pm.provide(userInput);
                setSelectedItem(item);
            }
        }
  #endif
    }
    return item;
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
#if 0
    if (editable && !(manager instanceof ProvidingManager)) {
        log.error("Unable to set editable to true because not backed by editable manager");
        return; // refuse to allow editing if unable to accept user input
    }
    if (editable && !providing) {
        log.error("Refusing to set editable if not allowing new NamedBeans to be created");
        return; // refuse to allow editing if not allowing user input to be
                // accepted
    }
#endif
    JComboBox::setEditable(editable);
}

/**
 * Get the display name of the selected item.
 *
 * @return the display name of the selected item or null if the selected
 *         item is null or there is no selection
 */
/*public*/ QString NamedBeanComboBox::getSelectedItemDisplayName() {
    NamedBean* item = getSelectedItem();
    return item != nullptr ? item->getDisplayName() : QString();
}

/**
 * Get the system name of the selected item.
 *
 * @return the system name of the selected item or null if the selected item
 *         is null or there is no selection
 */
/*public*/ QString NamedBeanComboBox::getSelectedItemSystemName() {
    NamedBean* item = getSelectedItem();
    return item != nullptr ? item->getSystemName() : QString();
}

/**
 * Get the user name of the selected item.
 *
 * @return the user name of the selected item or null if the selected item
 *         is null or there is no selection
 */
/*public*/ QString NamedBeanComboBox::getSelectedItemUserName() {
    NamedBean* item = getSelectedItem();
    return item != nullptr ? item->getUserName() : QString();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void NamedBeanComboBox::setSelectedItem(NamedBean* item) {
 if(item == nullptr)
 {
  //JComboBox::setCurrentIndex(-1);
  return;
 }

 JComboBox::setCurrentIndex(JComboBox::findData(VPtr<NamedBean>::asQVariant(item)));
 if (itemData(currentIndex()) !=QVariant()) {
     userInput = QString();
 }
}

/**
 * Set the selected item by either its user name or system name.
 *
 * @param name the name of the item to select
 * @throws IllegalArgumentException if {@link #isAllowNull()} is false and
 *                                  no bean exists by name or name is null
 */
/*public*/ void NamedBeanComboBox::setSelectedItemByName(QString name) {
    NamedBean* item = nullptr;
    if (!name.isEmpty()) {
        item = manager->getNamedBean(name);
    }
    if (item == nullptr && !allowNull) {
        throw IllegalArgumentException();
    }
    setSelectedItem(item);
}

/*public*/ void NamedBeanComboBox::dispose() {
    ((PropertyChangeSupport*)this->manager->self())->removePropertyChangeListener("beans", managerListener);
    ((PropertyChangeSupport*)this->manager->self())->removePropertyChangeListener("DisplayListName", managerListener);
}

/*private*/ void NamedBeanComboBox::sort() {
    // use getItemAt instead of getSelectedItem to avoid
    // possibility of creating a NamedBean in this method
    NamedBean* selectedItem = VPtr<NamedBean>::asPtr(itemData(currentIndex()));//getItemAt(getSelectedIndex());
#if 0
    ComparatorT<NamedBean*> comparator = new NamedBeanComparator<NamedBean*>();

    if (displayOptions != NamedBean::DisplayOptions::SYSTEMNAME && displayOptions != NamedBean::DisplayOptions::QUOTED_SYSTEMNAME) {
        comparator = new NamedBeanUserNameComparator<NamedBean*>();
    }
    QSet<NamedBean*> set = QSet<NamedBean*>(/*comparator*/);
#else
    QSet<NamedBean*> set = QSet<NamedBean*>();
#endif
    set.unite(manager->getNamedBeanSet());
    set.subtract(excludedItems);
#if 0
    Vector<B> vector = new Vector<>(set);
    if (allowNull) {
        vector.add(0, null);
    }
    setModel(new DefaultComboBoxModel<>(vector));
    // retain selection
    if (selectedItem == null && userInput != null) {
        setSelectedItemByName(userInput);
    } else {
        setSelectedItem(selectedItem);
    }
#else
    foreach(NamedBean* bean, set)
     addItem(bean->getSystemName(), VPtr<NamedBean>::asQVariant(bean));
#endif
}
/*public*/ void NamedBeanComboBox::setManager(Manager* manager)
{
 this->manager = manager;
 ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("beans", managerListener);
 ((PropertyChangeSupport*)this->manager->self())->addPropertyChangeListener("DisplayListName", managerListener);
 sort();

}

/*public*/ NamedBean* NamedBeanComboBox::getNamedBean()
{
 if(count() >0)
  return VPtr<NamedBean>::asPtr(itemData(0));
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
    return tr("<html>%1 \"%2\" is not a valid system name.<br>%3</html>").arg(beanType).arg(text).arg(exception);
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

/*public*/ QSet<NamedBean*> NamedBeanComboBox::getExcludedItems() {
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
/*public*/ void NamedBeanComboBox::setExcludedItems(QSet<NamedBean*> excludedItems) {
    this->excludedItems.clear();
    this->excludedItems.unite(excludedItems);
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
                @Override
                protected Validation getValidation(JComponent component, JInputValidatorPreferences preferences) {
                    if (component instanceof JTextComponent) {
                        JTextComponent jtc = (JTextComponent) component;
                        String text = jtc.getText();
                        if (text != null && !text.isEmpty()) {
                            B bean = manager.getNamedBean(text);
                            if (bean != null) {
                                // selection won't change if bean is not in model
                                setSelectedItem(bean);
                                if (!bean.equals(getItemAt(getSelectedIndex()))) {
                                    jtc.setText(text);
                                    if (validatingInput) {
                                        return new Validation(Validation.Type.DANGER,
                                                getBeanInUseMessage(manager.getBeanTypeHandled(),
                                                        bean.getDisplayName(DisplayOptions.QUOTED_DISPLAYNAME)),
                                                preferences);
                                    }
                                }
                            } else {
                                if (validatingInput) {
                                    if (providing) {
                                        try {
                                            // ignore output, only interested in exceptions
                                            manager.validateSystemNameFormat(text);
                                        } catch (IllegalArgumentException ex) {
                                            return new Validation(Validation.Type.DANGER,
                                                    getInvalidNameFormatMessage(manager.getBeanTypeHandled(), text,
                                                            ex.getLocalizedMessage()),
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

    @Override
    /*public*/ Component getEditorComponent() {
        return editor.getEditorComponent();
    }

    @Override
    /*public*/ void setItem(Object anObject) {
        Component c = getEditorComponent();
        if (c instanceof JTextComponent) {
            JTextComponent jtc = (JTextComponent) c;
            if (anObject instanceof NamedBean) {
                NamedBean nb = (NamedBean) anObject;
                jtc.setText(nb.getDisplayName(displayOptions));
            } else {
                jtc.setText("");
            }
        } else {
            editor.setItem(anObject);
        }
    }

    @Override
    /*public*/ Object getItem() {
        return editor.getItem();
    }

    @Override
    /*public*/ void selectAll() {
        editor.selectAll();
    }

    @Override
    /*public*/ void addActionListener(ActionListener l) {
        editor.addActionListener(l);
    }

    @Override
    /*public*/ void removeActionListener(ActionListener l) {
        editor.removeActionListener(l);
    }
}

/*private*/ class NamedBeanRenderer implements ListCellRenderer<B>, JComboBox.KeySelectionManager {

    /*private*/ final ListCellRenderer<? super B> renderer;
    /*private*/ final long timeFactor;
    /*private*/ long lastTime;
    /*private*/ String prefix = "";

    /*public*/ NamedBeanRenderer(ListCellRenderer<? super B> renderer) {
        this.renderer = renderer;
        Long l = (Long) UIManager.get("ComboBox.timeFactor");
        timeFactor = l != null ? l : 1000;
    }

    @Override
    /*public*/ Component getListCellRendererComponent(JList<? extends B> list, B value, int index, bool isSelected,
            bool cellHasFocus) {
        JLabel label = (JLabel) renderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
        if (value != null) {
            label.setText(value.getDisplayName(displayOptions));
        }
        return label;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings({"unchecked", "rawtypes"}) // unchecked cast due to API constraints
    /*public*/ int selectionForKey(char key, ComboBoxModel model) {
        long time = System.currentTimeMillis();

        // Get the index of the currently selected item
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

        // Determine the "prefix" to be used when searching the model. The
        // prefix can be a single letter or multiple letters depending on
        // how
        // fast the user has been typing and on which letter has been typed.
        if (time - lastTime < timeFactor) {
            if ((prefix.length() == 1) && (key == prefix.charAt(0))) {
                // Subsequent same key presses move the keyboard focus to
                // the next object that starts with the same letter.
                startIndex++;
            } else {
                prefix += key;
            }
        } else {
            startIndex++;
            prefix = "" + key;
        }

        lastTime = time;

        // Search from the current selection and wrap when no match is found
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
    @SuppressWarnings({"unchecked", "rawtypes"}) // unchecked cast due to API constraints
    /*private*/ int getNextMatch(String prefix, int start, int end, ComboBoxModel model) {
        for (int i = start; i < end; i++) {
            B item = (B) model.getElementAt(i);

            if (item != null) {
                String userName = item.getUserName();

                if (item.getSystemName().toLowerCase().startsWith(prefix) ||
                        (userName != null && userName.toLowerCase().startsWith(prefix))) {
                    return i;
                }
            }
        }
        return -1;
    }
}

#endif
