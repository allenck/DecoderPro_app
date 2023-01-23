#include "abstractconnectionconfig.h"
#include "instancemanager.h"
#include "jmriuserpreferencesmanager.h"
#include "portadapter.h"
#include <QLabel>
#include <QComboBox>
#include <jtextfield.h>
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QCheckBox>
#include "connectionconfigmanager.h"
#include "configuremanager.h"
#include "loggerfactory.h"
#include "joptionpane.h"


AbstractConnectionConfig::AbstractConnectionConfig(QObject *parent) :
    ConnectionConfig(parent)
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 NUMOPTIONS = 2;

 showAdvanced = new QCheckBox("Additional Connection Settings");

 systemPrefixLabel = new QLabel("Connection Prefix:");
 connectionNameLabel = new QLabel("Connection Name:");
 systemPrefixField = new JTextField(10);
 connectionNameField = new JTextField(16);
 options = QHash<QString, Option*>();
 additionalItems = new QList<QWidget*>();
 gbLayout = new GridBagLayout();
 gbLayout->setObjectName("gbLayout");
 cL = new GridBagConstraints();
 cR = new GridBagConstraints();
 _details = nullptr;
}
/**
 * Abstract base class for common implementation of the ConnectionConfig
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @version	$Revision: 28217 $
 */
// /*abstract*/ /*public*/ class AbstractConnectionConfig implements ConnectionConfig {

/**
 * Ctor for a functional object with no prexisting adapter. Expect that the
 * subclass setInstance() will fill the adapter member.
 */
// /*public*/ AbstractConnectionConfig() {
//}


/*abstract*/ void AbstractConnectionConfig::checkInitDone() {}

/*abstract*/ /*public*/ void AbstractConnectionConfig::updateAdapter() {}



/**
 * Determine if configuration needs to be written to disk.
 *
 * This default implementation always returns true to maintain the existing
 * behavior.
 *
 * @return true if configuration need to be saved, false otherwise
 */
//@Override
/*public*/ bool AbstractConnectionConfig::isDirty() {
    return this->getAdapter()->isDirty();
}

/**
 * Determine if application needs to be restarted for configuration changes
 * to be applied.
 *
 * The default implementation always returns true to maintain the existing
 * behavior.
 *
 * @return true if application needs to restart, false otherwise
 */
//@Override
/*public*/ bool AbstractConnectionConfig::isRestartRequired() {
    return this->getAdapter()->isRestartRequired();
}


/*public*/ AbstractConnectionConfig::Option::Option(QString name, QWidget* optionSelection, bool advanced) {
    this->optionDisplayName = name;
    this->optionSelection = optionSelection;
    this->advanced = advanced;
    label = nullptr;
}

/*protected*/ QString AbstractConnectionConfig::Option::getDisplayName() {
    return optionDisplayName;
}

/*public*/ QLabel* AbstractConnectionConfig::Option::getLabel()
{
 if (label == nullptr)
 {
  label = new QLabel(getDisplayName());//, JLabel.LEFT);
  label->setAlignment(Qt::AlignLeft);
 }
 return label;
}

/*public*/ QWidget* AbstractConnectionConfig::Option::getComponent() {
    return optionSelection;
}

/*protected*/ bool AbstractConnectionConfig::Option::isAdvanced() {
    return advanced;
}

/*protected*/ void AbstractConnectionConfig::Option::setAdvanced(bool boo) {
    advanced = boo;
}

/*public*/ QString AbstractConnectionConfig::Option::getItem()
{
 //if (optionSelection instanceof JComboBox)
 if(qobject_cast<QComboBox*>(optionSelection)!= nullptr)
 {
  return ((QComboBox*) optionSelection)->currentText();
 }
 else
 //if (optionSelection instanceof JTextField)
 if(qobject_cast<JTextField*>(optionSelection)!= nullptr)
 {
  return ((JTextField) optionSelection).text();
 }
 return nullptr;
}

/**
 * Load the adapter with an appropriate object
 * <i>unless</I> its already been set.
 */
/*abstract*/ /*protected*/ void AbstractConnectionConfig::setInstance() {}

//@Override
/*abstract*/ /*public*/ QString AbstractConnectionConfig::getInfo(){return "";}


//static java.util.ResourceBundle rb
//        = java.util.ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");

//@Override
/*abstract*/ /*public*/ void AbstractConnectionConfig::loadDetails(/*final*/ JPanel* details) {}


/*abstract*/ void AbstractConnectionConfig::showAdvancedItems() {}

/*protected*/ int AbstractConnectionConfig::addStandardDetails(PortAdapter* adapter, bool incAdvanced, int i)
{
 foreach (QString item, options.keys())
 {
  if (!options.value(item)->isAdvanced())
  {
   cR->gridy = i;
   cL->gridy = i;
//   gbLayout.setConstraints(options.value(item).getLabel(), cL);
//   gbLayout.setConstraints(options.get(item).getComponent(), cR);
   gbLayout->addWidget(options.value(item)->getLabel(), *cL);
   options.value(item)->getLabel()->setVisible(true);
   gbLayout->addWidget(options.value(item)->getComponent(), *cR);
   options.value(item)->getComponent()->setVisible(true);
   i++;
  }
 }

 if (adapter->getSystemConnectionMemo() != nullptr)
 {
  cR->gridy = i;
  cL->gridy = i;
//  gbLayout.setConstraints(systemPrefixLabel, cL);
//  gbLayout.setConstraints(systemPrefixField, cR);
  gbLayout->addWidget(systemPrefixLabel, *cL);
  systemPrefixLabel->setVisible(true);
  gbLayout->addWidget(systemPrefixField, *cR);
  systemPrefixField->setVisible(true);
  i++;
  cR->gridy = i;
  cL->gridy = i;
//  gbLayout.setConstraints(connectionNameLabel, cL);
//  gbLayout.setConstraints(connectionNameField, cR);
  gbLayout->addWidget(connectionNameLabel, *cL);
  connectionNameLabel->setVisible(true);
  gbLayout->addWidget(connectionNameField, *cR);
  connectionNameField->setVisible(true);
  i++;
 }
 if (incAdvanced)
 {
  cL->gridwidth = 2;
  cL->gridy = i;
  cR->gridy = i;
//  gbLayout.setConstraints(showAdvanced, cL);
  gbLayout->addWidget(showAdvanced, *cL);
  showAdvanced->setVisible(true);
  cL->gridwidth = 1;
  i++;
 }
 return i;
}

//@Override
/*abstract*/ /*public*/QString AbstractConnectionConfig::getManufacturer() {return "";}

//@Override
/*abstract*/ /*public*/ void AbstractConnectionConfig::setManufacturer(QString /*manufacturer*/) {}

//@Override
/*abstract*/ /*public*/ QString AbstractConnectionConfig::getConnectionName(){return "";}

//@Override
/*abstract*/ /*public*/ bool AbstractConnectionConfig::getDisabled() {return false;}

//@Override
/*abstract*/ /*public*/ void AbstractConnectionConfig::setDisabled(bool /*disable*/) {}

/**
 * Register the ConnectionConfig with the running JMRI process. It is
 * strongly recommended that overriding implementations call
 * super.register() since this implementation performs all required
 * registration tasks.
 */
//@Override
/*public*/ void AbstractConnectionConfig::_register() {
    this->setInstance();
    ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerPref(this);
    ConnectionConfigManager* ccm = (ConnectionConfigManager*)InstanceManager::getNullableDefault("ConnectionConfigManager");
    if (ccm != nullptr) {
        ccm->add(this);
    }
}

//@Override
/*public*/ void AbstractConnectionConfig::dispose() {
    ConnectionConfigManager* ccm = (ConnectionConfigManager*)InstanceManager::getNullableDefault("ConnectionConfigManager");
    if (ccm != nullptr) {
        ccm->remove(this);
    }
}

/*protected*/ void AbstractConnectionConfig::addNameEntryCheckers(/*@Nonnull*/ PortAdapter* adapter) {
    if (adapter->getSystemConnectionMemo() != nullptr) {
//        systemPrefixField.addActionListener(e -> checkPrefixEntry(adapter));
//        systemPrefixField.addFocusListener(new FocusListener() {
//            @Override
//            public void focusLost(FocusEvent e) {
//                checkPrefixEntry(adapter);
//            }

//            @Override
//            public void focusGained(FocusEvent e) {
//            }
//        });
     connect(systemPrefixField, &JTextField::editingFinished, [=]{checkPrefixEntry(adapter);});
//        connectionNameField.addActionListener(e -> checkNameEntry(adapter));
//        connectionNameField.addFocusListener(new FocusListener() {
//            @Override
//            public void focusLost(FocusEvent e) {
//                checkNameEntry(adapter);
//            }

//            @Override
//            public void focusGained(FocusEvent e) {
//            }
//        });
     connect(connectionNameField, &JTextField::editingFinished, [=]{checkNameEntry(adapter);});
    }
}

/*private*/ void AbstractConnectionConfig::checkPrefixEntry(/*@Nonnull*/ PortAdapter* adapter) {
    if (!systemPrefixField->isValid()) { // invalid prefix format entry, actually can't lose focus until valid
        systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
    }
    if (!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text())) { // in use
        JOptionPane::showMessageDialog(nullptr, tr("Connection Prefix %1 is already assigned").arg(systemPrefixField->text()));
        systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
    }
}

/*private*/ void AbstractConnectionConfig::checkNameEntry(/*@Nonnull*/ PortAdapter* adapter) {
    if (!adapter->getSystemConnectionMemo()->setUserName(connectionNameField->text())) {
        JOptionPane::showMessageDialog(nullptr, tr("Connection Name %1 is already assigned").arg(connectionNameField->text()));
        connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
    }
}

/*private*/ /*final*/ /*static*/ Logger* AbstractConnectionConfig::log = LoggerFactory::getLogger("AbstractConnectionConfig");
