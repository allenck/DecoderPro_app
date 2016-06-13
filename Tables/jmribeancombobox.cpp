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

//JmriBeanComboBox::JmriBeanComboBox(QObject *parent) :
//    QComboBox(parent)
//{
//}
///*public*/ class JmriBeanComboBox extends JComboBox implements java.beans.PropertyChangeListener{

/*
* Create a default Jmri Combo box for the given bean manager
* @param manager the jmri manager that is used to populate the combo box
*/
/*public*/ JmriBeanComboBox::JmriBeanComboBox(Manager* manager, QWidget *parent) : QComboBox(parent)
{
    //this(manager, NULL, DISPLAYNAME);
 log = new Logger("JmriBeanComboBox");
  exclude = new QList<NamedBean*>();
  _firstBlank = false;
 _manager = manager;
 displayToBean = new QHash<QString, NamedBean*>();

 setSelectedBean(NULL);
 _displayOrder = DISPLAYNAME;
 _lastSelected = "";
 //((AbstractManager*)_manager)->addPropertyChangeListener((PropertyChangeListener*)this);
 AbstractManager* abstractManager = (AbstractManager*)_manager;
 connect(abstractManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //setKeySelectionManager(new beanSelectionManager());
 _lastSelected = "";
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
 log = new Logger("JmriBeanComboBox");
 exclude = new QList<NamedBean*>();
 _displayOrder = displayOrder;
 _firstBlank = false;
 _manager = manager;
 displayToBean = new QHash<QString, NamedBean*>();

 setSelectedBean(nBean);
 //setEditable(true);
 ((AbstractManager*)_manager)->addPropertyChangeListener((PropertyChangeListener*)this);
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

/*public*/ void JmriBeanComboBox::refreshCombo()
{
 updateComboBox(QString::number(currentIndex()));
}

void JmriBeanComboBox::updateComboBox(QString select)
{
 if(_manager == NULL) return;
 displayToBean = new QHash<QString, NamedBean*>();
 clear();
 QStringList* nameList;
 if(qobject_cast<ProxyTurnoutManager*>(_manager)!= 0)
   nameList = new QStringList(((ProxyTurnoutManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<ProxySensorManager*>(_manager)!= 0)
   nameList = new QStringList(((ProxySensorManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<ProxyReporterManager*>(_manager)!= 0)
   nameList = new QStringList(((ProxyReporterManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<AbstractSignalHeadManager*>(_manager)!= 0)
   nameList = new QStringList(((AbstractSignalHeadManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<DefaultSignalMastManager*>(_manager)!= 0)
   nameList = new QStringList(((DefaultSignalMastManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<BlockManager*>(_manager) != NULL)
  nameList = new QStringList(((AbstractManager*)_manager)->getSystemNameArray());
 else if(qobject_cast<AbstractManager*>(_manager) != NULL)
  nameList = new QStringList(((AbstractManager*)_manager)->getSystemNameArray());
 else
     Q_ASSERT(false);

 qSort(nameList->begin(), nameList->end(), SystemNameComparator::compare);

 foreach(NamedBean* bean , *exclude)
 {
  if(bean!=NULL)
   nameList->removeOne(bean->getSystemName());
 }


 QVector<QString> displayList =  QVector<QString>(nameList->size()); //[nameList.size()];

 if(_displayOrder==SYSTEMNAME)
 {
  displayList = nameList->toVector();//->toArray(displayList);
 }
 else
 {
  //for(String name: nameList){
  for(int i = 0; i<nameList->size(); i++)
  {
   QString name = nameList->at(i);
   NamedBean* nBean = NULL;
   nBean = ((AbstractManager*)_manager)->getBeanBySystemName(name);

   if (nBean!=NULL)
   {
    switch(_displayOrder)
    {
    case DISPLAYNAME :
     displayList.replace(i, nBean->getDisplayName());
     break;

    case USERNAME :
     if(nBean->getUserName()!=NULL && nBean->getUserName()!=(""))
      displayList.replace(i, nBean->getUserName());
     else
      displayList.replace(i, name);
      break;

    case USERNAMESYSTEMNAME :
     if(nBean->getUserName()!=NULL && nBean->getUserName()!=(""))
        displayList.replace(i, nBean->getUserName() + " - " + name);
     else
        displayList.replace(i, name);
     break;

    case SYSTEMNAMEUSERNAME :
    if(nBean->getUserName()!=NULL && nBean->getUserName()!=(""))
        displayList.replace(i, name + " - " + nBean->getUserName());
    else
        displayList.replace(i, name);
    break;

    default :
      displayList.replace(i, nBean->getDisplayName());
    }
    displayToBean->insert(displayList.at(i), nBean);
   }
  }
 }
//    java.util.Arrays.sort(displayList);

 for(int i = 0; i<displayList.size(); i++)
 {
  addItem(displayList.at(i));
  if ((select!=NULL) && (displayList.at(i)==(select)))
  {
   setCurrentIndex(i);
  }
 }
 if(_firstBlank)
 {
  insertItem(0, "");
  if (_lastSelected==NULL || _lastSelected==(""))
  {
   setCurrentIndex(0);
  }
 }
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


/*public*/ NamedBean* JmriBeanComboBox::getSelectedBean(){
    QString selectedName = currentText();
    return displayToBean->value(selectedName);
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


/*public*/ void JmriBeanComboBox::excludeItems(QList<NamedBean*>* exclude){
    this->exclude = exclude;
    _lastSelected = getSelectedDisplayName();
    updateComboBox(_lastSelected);
}



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
