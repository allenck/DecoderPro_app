#include "beanselectcreatepanel.h"
#include "instancemanager.h"
#include <QFormLayout>
#include "abstractmanager.h"
#include "lnturnoutmanager.h"
#include "lnsensormanager.h"
#include "jtextfield.h"
#include "defaultmemorymanager.h"
#include "blockmanager.h"
#include "namedbeancombobox.h"
#include "flowlayout.h"
#include "jmriuserpreferencesmanager.h"
#include "connectionnamefromsystemname.h"
#include "proxymanager.h"
#include "proxylightmanager.h"

//BeanSelectCreatePanel::BeanSelectCreatePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class BeanSelectCreatePanel extends JPanel{



/**
* Create a JPanel, that provides the option to the user to either select an
* already created bean, or to create one on the fly.
* This only currently works with Turnouts, Sensors, Memories and Blocks.
*/
/*public*/ BeanSelectCreatePanel::BeanSelectCreatePanel(Manager* manager, NamedBean* defaultSelect, QWidget *parent) : QWidget(parent)
{
 systemSelectionCombo = "jmri.util.swing.BeanSelectCreatePanel.SystemSelected";

 _manager = manager;
 QValidator* v = new QIntValidator(0,1027);
 hardwareAddress->setValidator(v);

 _defaultSelect = defaultSelect;
 p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 existingItem = new QRadioButton(tr("Use Existing")/*, true*/);
 existingItem->setChecked(true);
 newItem = new QRadioButton(tr("Create new"));
//    existingItem.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            update();
//        }
//    });
 connect(existingItem, SIGNAL(toggled(bool)), this, SLOT(update()));
//    newItem->addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            update();
//        }
//    });
 connect(newItem, SIGNAL(toggled(bool)), this, SLOT(update()));
 selectcreate = new QButtonGroup();
 selectcreate->addButton(existingItem);
 selectcreate->addButton(newItem);
 existingCombo = new NamedBeanComboBox(_manager, defaultSelect, NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
 //If the combo list is empty we go straight to creation.
 if (existingCombo->count()==0)
 {
  newItem->setChecked(true);
 }
 existingCombo->setAllowNull(true);
 QWidget* radio = new QWidget();
 //radio->setLayout(new FlowLayout(/*FlowLayout::Center, 5, 0*/));
 QHBoxLayout* radioHLayout;
 radio->setLayout(radioHLayout = new QHBoxLayout);
 QWidget* bean = new QWidget();
 //bean->setLayout(new FlowLayout(/*FlowLayout.CENTER, 5, 0*/));
 QHBoxLayout* beanHLayout;
 bean->setLayout(beanHLayout = new QHBoxLayout);
 radioHLayout->addWidget(existingItem);
 radioHLayout->addWidget(newItem);

 if ( qobject_cast<ProxyManager*>(_manager)!=NULL)
 {
  QList<Manager*> managerList;
  if(qobject_cast<ProxyTurnoutManager*>(_manager)!=NULL)
  {
   ProxyTurnoutManager* proxy = (ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance();
   prefixBox->setManagers(proxy->getManagerList(), proxy->getDefaultManager());
   if (p->getComboBoxLastSelection(systemSelectionCombo) != "") {
       prefixBox->setSelectedItem(p->getComboBoxLastSelection(systemSelectionCombo));
   }
  }
  else if (qobject_cast<ProxySensorManager*>(_manager)!=NULL)
  {
   ProxySensorManager* proxy = (ProxySensorManager*) InstanceManager::sensorManagerInstance();
   prefixBox->setManagers(proxy->getManagerList(), proxy->getDefaultManager());
   if (p->getComboBoxLastSelection(systemSelectionCombo) != "") {
       prefixBox->setSelectedItem(p->getComboBoxLastSelection(systemSelectionCombo));
   }

  }
  else if (qobject_cast<ProxyLightManager*>(_manager)!=NULL)
  {
   ProxyLightManager* proxy = (ProxyLightManager*) InstanceManager::lightManagerInstance();
   prefixBox->setManagers(proxy->getManagerList(), proxy->getDefaultManager());
   if (p->getComboBoxLastSelection(systemSelectionCombo) != "") {
       prefixBox->setSelectedItem(p->getComboBoxLastSelection(systemSelectionCombo));
   }

  }
  else if (qobject_cast<ProxyReporterManager*>(_manager)!=NULL)
  {
   ProxyReporterManager* proxy = (ProxyReporterManager*) InstanceManager::getDefault("ReporterManager");
   prefixBox->setManagers(proxy->getManagerList(), proxy->getDefaultManager());
   if (p->getComboBoxLastSelection(systemSelectionCombo) != "") {
       prefixBox->setSelectedItem(p->getComboBoxLastSelection(systemSelectionCombo));
   }

  }

  for(int x = 0; x < managerList.size(); x++)
  {
   QString manuName; /* = ConnectionNameFromSystemName.getConnectionName(managerList.at(x)->getSystemPrefix());*/
   if(managerList.at(x)->getSystemPrefix() == "L")
    manuName = "LocoNet";
   else if(managerList.at(x)->getSystemPrefix() == "I")
    manuName = "Internal";

   bool addToPrefix = true;
   //Simple test not to add a system with a duplicate System prefix
   for (int i = 0; i<prefixBox->count(); i++)
   {
    if((QString)prefixBox->itemText(i)==(manuName))
     addToPrefix=false;
   }
   if (addToPrefix)
    prefixBox->addItem(manuName);
  }
  if(p->getComboBoxLastSelection(systemSelectionCombo)!=NULL)
   prefixBox->setCurrentIndex(prefixBox->findText(p->getComboBoxLastSelection(systemSelectionCombo)));
 }
 else
 {
  prefixBox->addItem(/*ConnectionNameFromSystemName.getConnectionName(((AbstractManager*)_manager)->getSystemPrefix()));*/ "LocoNet");
 }

 beanHLayout->addWidget(existingCombo);
 beanHLayout->addWidget(prefixBox);
 beanHLayout->addWidget(hardwareAddress);
 hardwareAddress->setToolTip("Enter in the Hardware address");
 QVBoxLayout* vLayout;
 setLayout(/*new BoxLayout(this, BoxLayout.Y_AXIS)*/vLayout = new QVBoxLayout());
 vLayout->addWidget(radio);
 //vLayout->addLayout(radioHLayout);
 vLayout->addWidget(bean);
 //vLayout->addLayout(beanHLayout);
 update();
}

void BeanSelectCreatePanel::update(){
    bool select = true;
    if (newItem->isChecked()) select=false;
    prefixBox->setVisible(false);
    hardwareAddress->setVisible(false);
    existingCombo->setVisible(false);
    if(select) {
        existingCombo->setVisible(true);
    } else {
        prefixBox->setVisible(true);
        hardwareAddress->setVisible(true);
    }
}

/*public*/ void BeanSelectCreatePanel::setEnabled(bool enabled){
    existingItem->setEnabled(enabled);
    hardwareAddress->setEnabled(enabled);
    prefixBox->setEnabled(enabled);
    newItem->setEnabled(enabled);
    existingCombo->setEnabled(enabled);
    QWidget::setEnabled(enabled);
}

/*public*/ void BeanSelectCreatePanel::refresh(){
    // do nothing
}

/**
* get the display name of the bean that has either been selected in the drop down list or
* has been created
*/
/*public*/ QString BeanSelectCreatePanel::getDisplayName()
{
 if(existingItem->isChecked()){
     return existingCombo->getSelectedItemDisplayName();
 }
 else
 {
  try
  {
   NamedBean* nBean = createBean();
   return nBean->getDisplayName();
  }
  catch (JmriException e){
   return "";
  }
 }
}

/**
* get the named bean that has either been selected in the drop down list or
* has been created
*/

/*public*/ NamedBean* BeanSelectCreatePanel::getNamedBean() throw (JmriException)
{
 if(existingItem->isChecked())
 {
  return existingCombo->getSelectedItem();
 }
 //try {
 return createBean();
//    } catch (JmriException e){
//        throw e;
//    }
}

/*private*/ NamedBean* BeanSelectCreatePanel::createBean() throw (JmriException)
{
 QString prefix = /*ConnectionNameFromSystemName.getPrefixFromName((QString) prefixBox->getSelectedItem());*/ "L";
 NamedBean* nBean = NULL;
 if (qobject_cast<ProxyTurnoutManager*>(_manager)!=NULL)
 {
  QString sName = "";
  try
  {
   sName=((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->createSystemName(hardwareAddress->text(), prefix);
  }
  catch (JmriException e)
  {
   throw e;
  }
  try
  {
   nBean = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(sName);
  }
  catch (IllegalArgumentException ex)
  {
   // user input no good
   throw new JmriException("ErrorTurnoutAddFailed");
  }
 }
 else if (qobject_cast<ProxySensorManager*>(_manager)!=NULL)
 {
  QString sName = "";
  try
  {
   sName=((ProxySensorManager*)InstanceManager::sensorManagerInstance())->createSystemName(hardwareAddress->text(), prefix);
  }
  catch (JmriException e)
  {
   throw e;
  }
  try
  {
   nBean = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(sName);
        } catch (IllegalArgumentException ex) {
            // user input no good
            throw new JmriException("ErrorSensorAddFailed");
        }
    }
    else
    {
        QString sName = _manager->makeSystemName(hardwareAddress->text());
        if(qobject_cast<MemoryManager*>(_manager)!=NULL)
        {
            try {
                nBean = ((DefaultMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(sName);
            } catch (IllegalArgumentException ex) {
                // user input no good
                throw new JmriException("ErrorMemoryAddFailed");
            }
        }
        else if (qobject_cast<BlockManager*>(_manager)!=NULL) {
            try {
                nBean = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->provideBlock(sName);
            } catch (IllegalArgumentException ex) {
                // user input no good
                throw new JmriException("ErrorBlockAddFailed");
            }
        }
    }
    if (nBean==NULL)
        throw new JmriException("Unable to create bean");
    if ((_reference!=NULL && _reference!=("")) && (nBean->getComment()==NULL || nBean->getComment()==("")))
        nBean->setComment(_reference);
    setDefaultNamedBean(nBean);
    return nBean;
}

/**
* Set a reference that can be set against the comment for a bean, only if
* the bean has no previous comment.
*/
/*public*/ void BeanSelectCreatePanel::setReference(QString ref){
    _reference = ref;
}

/**
* Sets the default selected item in the combo box, when this is set the
* combo box becomes active and the add hardware box details are then hidden
*/
/*public*/ void BeanSelectCreatePanel::setDefaultNamedBean(NamedBean* nBean){
    _defaultSelect = nBean;
    existingCombo->setSelectedItem(_defaultSelect);
    existingItem->setChecked(true);
    update();
}

/*public*/ void BeanSelectCreatePanel::dispose(){
    //existingCombo->dispose();
}


