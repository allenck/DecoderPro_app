#include "jmribeancombobox.h"
#include "manager.h"
#include "abstractmanager.h"
#include "comboboxmodel.h"
#include "proxyturnoutmanager.h"
#include "proxysensormanager.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "blockmanager.h"
#include "systemnamecomparator.h"
#include "abstractmanager.h"
#include "proxyreportermanager.h"

JmriBeanComboBox::JmriBeanComboBox(QWidget* parent) :
    QComboBox(parent)
{
 common(nullptr, nullptr, DISPLAYNAME);
}

///*public*/ class JmriBeanComboBox extends JComboBox implements java.beans.PropertyChangeListener{

/*
* Create a default Jmri Combo box for the given bean manager
* @param manager the jmri manager that is used to populate the combo box
*/
/*public*/ JmriBeanComboBox::JmriBeanComboBox(Manager* manager, QWidget *parent) : QComboBox(parent)
{
    //this(manager, NULL, DISPLAYNAME);
 common(manager, nullptr, DISPLAYNAME);
}

/*
* Create a Jmri Combo box for the given bean manager, with the Namedbean already selected and the items displayed and ordered
* @param manager the jmri manager that is used to populate the combo box
* @param nBean the namedBean that should automatically be selected
* @param displayOrder the way in which the namedbeans should be displayed as
*/
/*public*/ JmriBeanComboBox::JmriBeanComboBox(Manager* manager, NamedBean* nBean, int displayOrder, QWidget *parent)
    : QComboBox(parent)
{
 common(manager, nBean, displayOrder);
}

void JmriBeanComboBox::common(Manager *manager, NamedBean *nBean, int displayOrder)
{
 log = new Logger("JmriBeanComboBox");
 exclude = QList<NamedBean*>();
 _displayOrder = displayOrder;
 _firstBlank = false;
 if(manager!= nullptr)
  setManager(manager);
 displayToBean = new QHash<QString, NamedBean*>();

 setSelectedBean(nBean);
 //setEditable(true);
 //setKeySelectionManager(new beanSelectionManager());
 _lastSelected = "";
}

/*public*/ void JmriBeanComboBox::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  // a new NamedBean is available in the manager
  _lastSelected = QString::number(currentIndex());
  updateComboBox(_lastSelected);
  log->debug("Update triggered in name list");
 }
 else if (e->getPropertyName()==("DisplayListName"))
  refreshCombo();
}
/*public*/ Manager* JmriBeanComboBox::getManager() {
        return _manager;
}

/*public*/ void JmriBeanComboBox::setManager(Manager* manager)
{
 this->_manager = manager;
 //((AbstractManager*)_manager)->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(((AbstractManager*)_manager)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 refreshCombo();
}


/*public*/ void JmriBeanComboBox::refreshCombo()
{
 updateComboBox(currentText());
}

/*public*/ void JmriBeanComboBox::addPopupMenuListener(PopupMenuListener *pml)
{
 popupMenuListner = pml;
}

void JmriBeanComboBox::updateComboBox(QString inSelect)
{
 if(_manager == NULL) return;
 displayToBean = new QHash<QString, NamedBean*>();
 clear();
 QStringList displayList = getDisplayList();

 for (int i = 0; i < displayList.length(); i++) {
     addItem(displayList[i]);
     if ((inSelect != "") && (displayList[i]==(inSelect))) {
         setCurrentIndex(i);
     }
 }
 if (_firstBlank) {
     QComboBox::insertItem(0, "");
     if (_lastSelected == "" || _lastSelected == ("")) {
         setCurrentIndex(0);
     }
 }
}

/**
 * Get the display list used by this combo box.
 *
 * @return the display list used by this combo box
 */
/*public*/ QStringList JmriBeanComboBox::getDisplayList() {
    // working through names in this code is slow, as is making a list and
    // then removing items.  Should be completely rewritten to use the
    // native Manager interfaces

    QStringList nameList = QStringList();
    for (QObject* obj : _manager->getNamedBeanSet()) {
        nameList.append(((NamedBean*)obj)->getSystemName());
    }

    //exclude.stream().filter((bean) -> (bean != null)).forEachOrdered((bean) -> {
    foreach(NamedBean* bean, exclude)
    {
     if(bean != nullptr)
        nameList.removeOne(bean->getSystemName());
    }//);

    QVector<QString> displayList = QVector<QString>(nameList.size());

    if (_displayOrder == DisplayOptions::SYSTEMNAME) {
        displayList = nameList.toVector();//nameList.toArray(displayList);
    } else {
        for (int i = 0; i < nameList.size(); i++) {
            QString name = nameList.at(i);
            NamedBean* nBean = _manager->getBeanBySystemName(name);

            if (nBean != nullptr) {
                QString uname = nBean->getUserName();
                switch (_displayOrder) {
                    case USERNAME:
                        if (uname != "" ) {
                            displayList.replace(i, uname);
                        } else {
                            displayList.replace(i,  name);
                        }
                        break;

                    case USERNAMESYSTEMNAME:
                        if (uname != "" ) {
                            displayList.replace(i, nBean->getUserName() + " - " + name);
                        } else {
                            displayList.replace(i, name);
                        }
                        break;

                    case SYSTEMNAMEUSERNAME:
                        if (uname != "") {
                            displayList.replace(i, name + " - " + nBean->getUserName());
                        } else {
                            displayList.replace(i, name);
                        }
                        break;

                    case DISPLAYNAME:
                    default:
                        displayList.replace(i, nBean->getDisplayName());
                }
                displayToBean->insert(displayList[i], nBean);
            }
        }
    }
    //java.util.Arrays.sort(displayList, new AlphanumComparator());
    qSort(displayList.begin(), displayList.end());
    return displayList.toList();
}

/**
 * Get the selected namedBean.
 *
 * @return the selected bean or null if there is no selection
 */
/*public*/ NamedBean* JmriBeanComboBox::getSelectedBean() {
    QString selectedName =  currentText();
    return displayToBean->value(selectedName);
}

/**
* Get the User name of the selected namedBean
* @return the user name of the selected bean or NULL if there is no selection
*/
/*public*/ QString JmriBeanComboBox::getSelectedUserName(){
    QString selectedName = currentText();
    NamedBean* nBean = displayToBean->value(selectedName);
    if(nBean!=NULL)
        return nBean->getDisplayName();
    return NULL;

}

/**
* Get the system name of the selected namedBean
* @return the system name of the selected bean or NULL if there is no selection
*/
/*public*/ QString JmriBeanComboBox::getSelectedSystemName(){
    QString selectedName = currentText();
    NamedBean* nBean = displayToBean->value(selectedName);
    if(nBean!=NULL)
        return nBean->getSystemName();
    return NULL;
}

/**
* Get the display name of the selected namedBean
* @return the display name of the selected bean or NULL if there is no selection
*/
/*public*/ QString JmriBeanComboBox::getSelectedDisplayName(){
    QString selectedName = currentText();
    NamedBean* nBean = displayToBean->value(selectedName);
    if(nBean!=NULL)
        return nBean->getDisplayName();
    return NULL;
}

/**
 * Get the User Name of the selection in this JmriBeanComboBox (based on
 * typed in text or drop down list).
 *
 * @return the username or null if no selection
 */
/*public*/ QString JmriBeanComboBox::getUserName() {
    QString result = "";
    NamedBean* b;

    if (isEditable()) {
        result = NamedBean::normalizeUserName(getText());
        if (result == "") {
            result = "";
        }

        b = getNamedBean();
    } else {
        b = getSelectedBean();
    }
    if (nullptr != b) {
        result = b->getUserName();
    }
    return result;
}   //getUserName

/**
 * Get the display name for the selection in this JmriBeanComboBox (based on
 * typed in text or drop down list).
 *
 * @return the display name or null if no selection
 */
//@CheckReturnValue
/*public*/ QString JmriBeanComboBox::getDisplayName() {
    QString result = "";
    NamedBean* b;

    if (isEditable()) {
        result = NamedBean::normalizeUserName(getText());
        if (result == "") {
            result = "";
        }
        b = getNamedBean();
    } else {
        b = getSelectedBean();
    }
    if (nullptr != b) {
        result = b->getDisplayName();
    }
    return result;
}   //getDisplayName

/**
 * Get the text from the editor for this JmriBeanComboBox.
 *
 * @return the text
 */
/*public*/ QString JmriBeanComboBox::getText() {
   // return getEditor().getItem().toString();
 return QComboBox::currentText();
}   // getText

/**
 * Set the text from the editor for this JmriBeanComboBox
 *
 * @param inText the text to set
 */
/*public*/ void JmriBeanComboBox::setText(QString inText) {
    //getEditor().setItem(inText);
 setCurrentText(inText);
    if ((inText != "") && !inText.isEmpty()) {
        setSelectedBeanByName(inText);
    } else {
        setCurrentIndex(-1);
    }
    validateText();
}   // setText

/**
* Insert a blank entry at the top of the list
* @param blank true to insert, false to remove
*/
/*public*/ void JmriBeanComboBox::setFirstItemBlank(bool blank){
    if(_firstBlank == blank)
        return; // no Change to make
    if(_firstBlank)
         removeItem(0);
    else {
        insertItem(0, "");
        if (_lastSelected==NULL || _lastSelected==("")){
            setCurrentIndex(0);
        }
    }
    _firstBlank = blank;
}


/*public*/ void JmriBeanComboBox::setSelectedBean(NamedBean* nBean){
    QString selectedItem = "";
    if(nBean!=NULL){
        switch(_displayOrder){
            case DISPLAYNAME :
                    selectedItem = nBean->getDisplayName();
                    break;

            case USERNAME :
                    selectedItem = nBean->getUserName();
                    break;

            case SYSTEMNAME :
                    selectedItem = nBean->getSystemName();
                    break;

            case USERNAMESYSTEMNAME :
                    if(nBean->getUserName()!=NULL && nBean->getUserName()!=(""))
                        selectedItem = nBean->getUserName() + " - " + nBean->getSystemName();
                    else
                        selectedItem = nBean->getSystemName();
                    break;

            case SYSTEMNAMEUSERNAME :
                    if(nBean->getUserName()!=NULL && nBean->getUserName()!=(""))
                        selectedItem = nBean->getSystemName() + " - " + nBean->getUserName();
                    else
                        selectedItem = nBean->getSystemName();
                    break;

            default :
                    selectedItem = nBean->getDisplayName();
        }
    } else if (_firstBlank) {
        _lastSelected="";
    }
    _lastSelected = selectedItem;
    updateComboBox(_lastSelected);
}

/*public*/ void JmriBeanComboBox::setSelectedBeanByName(QString inBeanName) {
    if (inBeanName == NULL) {
        return;
    }
    NamedBean* nBean = _manager->getNamedBean(inBeanName);
    setSelectedBean(nBean);
}

/*public*/ void JmriBeanComboBox::excludeItems(QList<NamedBean*> exclude){
    this->exclude = exclude;
    _lastSelected = getSelectedDisplayName();
    updateComboBox(_lastSelected);
}

/*public*/ QList<NamedBean*> JmriBeanComboBox::getExcludeItems() {
        return this->exclude;
}

/*public*/ void JmriBeanComboBox::setItemEnabled(int inIndex, bool inEnabled) {
#if 0
    ListSelectionModel lsm = getEnabledItems();
    if (lsm != null) {
        if (inEnabled) {
            lsm.addSelectionInterval(inIndex, inIndex);
        } else {
            lsm.removeSelectionInterval(inIndex, inIndex);
        }
    }
#endif
}
#if 0
/*public*/ bool isItemEnabled(int inIndex) {
    bool result = false;
    ListSelectionModel lsm = getEnabledItems();
    if (lsm != null) {
        result = lsm.isSelectedIndex(inIndex);
    }
    return result;
}
#endif
/*public*/ void JmriBeanComboBox::enableItem(int inIndex) {
    setItemEnabled(inIndex, true);
}

/*public*/ void JmriBeanComboBox::disableItem(int inIndex) {
    setItemEnabled(inIndex, false);
}

/*public*/ void JmriBeanComboBox::setEnabledColor(QColor inEnabledColor) {
//    getEnabledComboBoxRenderer().setEnabledColor(inEnabledColor);
}

/*public*/ QColor JmriBeanComboBox::getEnabledColor() {
//    return getEnabledComboBoxRenderer().getEnabledColor();
}

/*public*/ void JmriBeanComboBox::setDisabledColor(QColor inDisabledColor) {
//    getEnabledComboBoxRenderer().setDisabledColor(inDisabledColor);
}

/*public*/ QColor JmriBeanComboBox::getDisabledColor() {
//    return getEnabledComboBoxRenderer().getDisabledColor();
}

/*public*/ void JmriBeanComboBox::setEnabledBackgroundColor(QColor inEnabledBackgroundColor) {
//    getEnabledComboBoxRenderer().setEnabledBackgroundColor(inEnabledBackgroundColor);
}

/*public*/ QColor JmriBeanComboBox::getEnabledBackgroundColor() {
//    return getEnabledComboBoxRenderer().getEnabledBackgroundColor();
}

/*public*/ void JmriBeanComboBox::setDisabledBackgroundColor(QColor inDisabledBackgroundColor) {
//    getEnabledComboBoxRenderer().setDisabledBackgroundColor(inDisabledBackgroundColor);
}

/*public*/ QColor JmriBeanComboBox::getDisabledBackgroundColor() {
//    return getEnabledComboBoxRenderer().getDisabledBackgroundColor();
}

/*public*/ void JmriBeanComboBox::setValidateMode(bool inValidateMode) {
    if (_validateMode != inValidateMode) {
        _validateMode = inValidateMode;
    }
}

/*public*/ bool JmriBeanComboBox::isValidateMode() {
    return _validateMode;
}

// this is called to validate that the text in the textfield
// is a valid member of the managed data.
// note:  if _validateMode is true
//           if text is valid set textfield background to green else red
//       if _validateMode is false
//           if text is valid set textfield background to green else yellow
/*private*/ void JmriBeanComboBox::validateText() {
//    ComboBoxEditor cbe = getEditor();
//    JTextComponent c = (JTextComponent) cbe.getEditorComponent();
//    String comboBoxText = cbe.getItem().toString();
 QString comboBoxText = currentText();

    if (isEditable() && !comboBoxText.isEmpty()) {
//        setOpaque(true);
        if (nullptr != getNamedBean()) {
            //c.setBackground(new Color(0xBDECB6));   //pastel green
         setStyleSheet("QComboBox {background: 0xBDECB6}");
        } else if (_validateMode) {
            //c.setBackground(new Color(0xFFC0C0));   //pastel red
         setStyleSheet("QComboBox {background: 0xFFC0C0}");

        } else {
            //c.setBackground(new Color(0xFDFD96));   //pastel yellow
         setStyleSheet("QComboBox {background: 0xFDFD96}");

        }
    } else {
//        setOpaque(false);
        //c.setBackground(new Color(0xFFFFFF));   //white (pastel grey?)
     setStyleSheet("QComboBox {background: 0xFFFFFF}");

    }
}   //validateText

/**
 * Get the bean for ether the typed in text or selected item from this
 * ComboBox.
 *
 * @return the selected bean or null if no selection
 */
//@SuppressWarnings("unchecked")  // Uses Manager instead of Manager<E> and List<NamedBean>
                                // instead of List<E>, which can only really be made
                                // safe and efficient with the class being generic
/*public*/ NamedBean* JmriBeanComboBox::getNamedBean() {
    NamedBean* result;

    Manager* uDaManager = getManager();

    QString comboBoxText = NamedBean::normalizeUserName(currentText());
    if (comboBoxText != "") {

        //try user name
        result = uDaManager->getBeanByUserName(comboBoxText);

        if (nullptr == result) {
            //try system name
            //note: don't use getBeanBySystemName here
            //throws an IllegalArgumentException if text is invalid
            result = uDaManager->getNamedBean(comboBoxText);
        }

        if (nullptr == result) {
            //quick search to see if text matches anything in the drop down list
            QStringList displayList = getDisplayList();
            bool found = false;  //assume failure (pessimist!)

            for (QString item : displayList) {
                if (item == (comboBoxText)) {
                    found = true;
                    break;
                }
            }

            if (found) {    //if we found it there then...
                //walk the namedBeanList...
                QList<NamedBean*>* namedBeanList = uDaManager->getNamedBeanList();

                for (NamedBean* namedBean : *namedBeanList) {
                    //checking to see if it matches "<sname> - <uname>" or "<uname> - <sname>"
                    QString uname = namedBean->getUserName();
                    QString sname = namedBean->getSystemName();

                    if (("" != uname)) {
                        QString usname = uname + " - " + sname;
                        QString suname = sname + " - " + uname;

                        if (comboBoxText == (usname) || comboBoxText == (suname)) {
                            result = namedBean;
                            break;
                        }
                    }
                }
            }
        }
        return result;
    }
    return nullptr;
}   //getBean

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(JmriBeanComboBox.class.getName());
//}
   #if 0
    /**
         * The interface that defines a <code>KeySelectionManager</code>.
         * To qualify as a <code>KeySelectionManager</code>,
         * the class needs to implement the method
         * that identifies the list index given a character and the
         * combo box data model.
         */
        /*public*/ /*interface*/class KeySelectionManager {
            /** Given <code>aKey</code> and the model, returns the row
             *  that should become selected. Return -1 if no match was
             *  found.
             *
             * @param  aKey  a char value, usually indicating a keyboard key that
             *               was pressed
             * @param aModel a ComboBoxModel -- the component's data model, containing
             *               the list of selectable items
             * @return an int equal to the selected row, where 0 is the
             *         first item and -1 is none.
             */
            int selectionForKey(char aKey,ComboBoxModel aModel);
        };

        class DefaultKeySelectionManager : KeySelectionManager/*, Serializable*/ {
            /*public*/ int selectionForKey(char aKey,ComboBoxModel aModel) {
                int i,c;
                int currentSelection = -1;
                Object selectedItem = aModel.getSelectedItem();
                String v;
                String pattern;

                if ( selectedItem != null ) {
                    for ( i=0,c=aModel.getSize();i<c;i++ ) {
                        if ( selectedItem == aModel.getElementAt(i) ) {
                            currentSelection  =  i;
                            break;
                        }
                    }
                }

                pattern = ("" + aKey).toLowerCase();
                aKey = pattern.charAt(0);

                for ( i = ++currentSelection, c = aModel.getSize() ; i < c ; i++ ) {
                    Object elem = aModel.getElementAt(i);
                    if (elem != null && elem.toString() != null) {
                        v = elem.toString().toLowerCase();
                        if ( v.length() > 0 && v.charAt(0) == aKey )
                            return i;
                    }
                }

                for ( i = 0 ; i < currentSelection ; i ++ ) {
                    Object elem = aModel.getElementAt(i);
                    if (elem != null && elem.toString() != null) {
                        v = elem.toString().toLowerCase();
                        if ( v.length() > 0 && v.charAt(0) == aKey )
                            return i;
                    }
                }
                return -1;
            }
        };
#endif
