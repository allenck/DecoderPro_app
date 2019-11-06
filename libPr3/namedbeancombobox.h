#ifndef NAMEDBEANCOMBOBOX_H
#define NAMEDBEANCOMBOBOX_H
#include <QComboBox>
#include <QSet>
#include "namedbean.h"
#include "managert.h"
#include "loggerfactory.h"
#include "vptr.h"

class ManagerT;
class Logger;
class PropertyChangeListener;
template<class B>
class NamedBeanComboBox : public QComboBox
{
public:
 /*public*/ NamedBeanComboBox(ManagerT<B> manager, QObject *parent= nullptr) : QComboBox(parent)
 {
  common(manager, nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 }
 /*public*/ NamedBeanComboBox(ManagerT<B> manager, B selection, QObject*parent= nullptr): QComboBox(parent)
 {
     common(manager, selection, NamedBean::DisplayOptions::DISPLAYNAME);
 }

 /*public*/ NamedBeanComboBox(ManagerT<B> manager, B selection,NamedBean::DisplayOptions* displayOrder, QObject* parent)
 : QComboBox(parent)
 {
  common(manager, selection, displayOrder);
  //super();
 }

 /*public*/ ManagerT<B> getManager() {
  return manager;
}
 /*public*/ NamedBean::DisplayOptions* getDisplayOrder(){
  return displayOptions;
}
 /*public*/ /*final*/ void setDisplayOrder(NamedBean::DisplayOptions* displayOrder){
  if (displayOptions != displayOrder) {
      displayOptions = displayOrder;
      sort();
  }
}
 /*public*/ bool isValidatingInput() {
  return validatingInput;
}
 /*public*/ void setValidatingInput(bool validatingInput) {
  this->validatingInput = validatingInput;
}
 /*public*/ bool isAllowNull() {
  return allowNull;
}
 /*public*/ void setAllowNull(bool allowNull){
  this->allowNull = allowNull;
  if (allowNull && (getModel().getSize() > 0 && getItemAt(0) != nullptr)) {
      this->insertItemAt(nullptr, 0);
  } else if (!allowNull && (getModel().getSize() > 0 && this.getItemAt(0) == nullptr)) {
      this.removeItemAt(0);
  }
}
 /*public*/ B getSelectedItem() {
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
 /*public*/ bool isProviding(){
  return providing;
}
 /*public*/ void setProviding(bool providing){
  this->providing = providing;
}
 /*public*/ void setEditable(bool editable) {
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
 /*public*/ QString getSelectedItemDisplayName() {
  B* item = getSelectedItem();
  //return item != nullptr ? item.getDisplayName() : nullptr;
  return item;
}
 /*public*/ QString getSelectedItemSystemName() {
  B item = getSelectedItem();
  //return item != nullptr ? item.getSystemName() : nullptr;
  return item;
}
 /*public*/ QString getSelectedItemUserName() {
  B item = getSelectedItem();
  //return item != null ? item.getUserName() : null;
  return item;
}
 /*public*/ void setSelectedItemByName(QString name) {
  B item = nullptr;
  if (name != "") {
      item = manager->getNamedBean(name);
  }
  if (item == nullptr && !allowNull) {
      throw IllegalArgumentException();
  }
  setSelectedItem(item);
}
 /*public*/ void dispose(){
  manager->removePropertyChangeListener(managerListener);
}
 /*public*/ QString getBeanInUseMessage(QString beanType, QString displayName){
  return tr("%1 %2 is not selectable and cannot be used in this context.").arg(beanType).arg(displayName);
}
 /*public*/ QString getInvalidNameFormatMessage(QString beanType, QString text, QString exception){
  return tr("<html>\"%1\" is not a valid system name.<br>%2</html>\n%3").arg(beanType).arg(text).arg(exception);
}
 /*public*/ QString getNoMatchingBeanMessage(QString beanType, QString text){
  return tr("No %1 named \"%2\" exists.").arg(beanType).arg(text);
}
 /*public*/ QString getWillCreateBeanMessage(QString beanType, QString text) {
  return tr("Will create a %1 named \"%2\".").arg(beanType).arg(text);
}
 /*public*/ QSet<B> getExcludedItems(){
  return excludedItems;
}
 /*public*/ void setExcludedItems(QSet<B> excludedItems){
  this->excludedItems.clear();
  this->excludedItems.addAll(excludedItems);
  sort();
}


private:
 /*private*/ /*final*/ Manager/*<B>*/* manager;
 /*private*/ NamedBean::DisplayOptions* displayOptions;
 /*private*/ bool allowNull = false;
 /*private*/ bool providing = true;
 /*private*/ bool validatingInput = true;
 /*private*/ /*final*/ QSet<B> excludedItems;// = new HashSet<>();
 /*private*/ /*final*/ PropertyChangeListener* managerListener;// = ThreadingPropertyChangeListener.guiListener(evt -> sort());
 /*private*/ /*final*/ static Logger* log = LoggerFactory::getLogger("NamedBeanComboBox");
 /*private*/ B getItemAt(int index){
  return VPtr<B>::asPtr(itemData(index));
 }

 /*private*/ void sort(){
  B selectedItem = getSelectedItem();
  Comparator<B> comparator = new NamedBeanComparator<>();
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

 /*private*/ void setsetSelectedItem(B item){
  setCurrentIndex(this->findData(item));
 }


private:
 /*private*/ commom(Manager<B> manager, B selection, JmriBeanComboBox::DisplayOptions* displayOrder){
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


};

/*private*/ class NamedBeanEditor //implements ComboBoxEditor
{

//    /*private*/ final ComboBoxEditor editor;
public:
    /**
     * Create a NamedBeanEditor using another editor as its base. This
     * allows the NamedBeanEditor to inherit any platform-specific behaviors
     * that the default editor may implement.
     *
     * @param editor the underlying editor
     */
    /*public*/ NamedBeanEditor(/*ComboBoxEditor editor*/) {
#if 0
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
#endif
    }
#if 0
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
#endif
};

/*private*/ class NamedBeanRenderer //implements ListCellRenderer<B>, JComboBox.KeySelectionManager
{
//    /*private*/ final ListCellRenderer<? super B> renderer;
    /*private*/ /*final*/ long timeFactor;
    /*private*/ long lastTime;
    /*private*/ long time;
    /*private*/ QString prefix = "";
public:
    /*public*/ NamedBeanRenderer(/*ListCellRenderer<? super B> renderer*/) {
//        this->renderer = renderer;
        long l = 1000;//(Long) UIManager.get("ComboBox.timeFactor");
        timeFactor = l != 0 ? l : 1000;
    }
#if 0
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
#endif
};

#endif // NAMEDBEANCOMBOBOX_H
