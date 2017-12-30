#include "abstractnetworkconnectionconfig.h"
#include "loconet/networkportadapter.h"
#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include <QCheckBox>
#include "jtextfield.h"
#include <QLabel>
#include "systemconnectionmemo.h"
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QFont>
#include <QGridLayout>
#include "insets.h"
#include "gridbagconstraints.h"
#include "abstractnetworkportcontroller.h"
#include <QSignalMapper>

AbstractNetworkConnectionConfig::AbstractNetworkConnectionConfig(QObject *parent) :
  AbstractConnectionConfig(parent)
{
 common();
}
/**
 * Abstract base class for common implementation of the ConnectionConfig
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @version	$Revision: 29396 $
 */
//abstract /*public*/ class AbstractNetworkConnectionConfig extends AbstractConnectionConfig {

//    private final static ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");

/**
 * Ctor for an object being created during load process
 *
 * @param p
 */
/*public*/ AbstractNetworkConnectionConfig::AbstractNetworkConnectionConfig(NetworkPortAdapter* p,QObject *parent) :
AbstractConnectionConfig(parent)
{
 common();
 adapter = p;
}

void AbstractNetworkConnectionConfig::common()
{
 log = new Logger("AbstractNetworkConnectionConfig");
 init = false;
 p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 hostNameField = new JTextField(15);
 portField = new JTextField(10);

 showAutoConfig = new QCheckBox(tr("Automatic Configuration"));
 adNameField = new JTextField(15);
 serviceTypeField = new JTextField(15);
 serviceTypeFieldLabel;

 adapter = NULL;
}

/**
 * Ctor for a functional object with no preexisting adapter-> Expect that the
 * subclass setInstance() will fill the adapter member.
 */
///*public*/ AbstractNetworkConnectionConfig() {
//}


//SuppressWarnings("unchecked")
//Override
/*protected*/ void AbstractNetworkConnectionConfig::checkInitDone()
{
 if (log->isDebugEnabled()) {
     log->debug("init called for " + name());
 }
 if (init) {
     return;
 }
//    hostNameField.addActionListener(new ActionListener() {
//    //Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            adapter->setHostName(hostNameField.getText());
//            p.addComboBoxLastSelection(adapter->getClass().getName() + ".hostname", hostNameField.getText());
//        }
//    });
 //connect(hostNameField, SIGNAL(leaveField()), this, SLOT(on_hostNameField_leave()));
 connect(hostNameField, SIGNAL(editingFinished()),this, SLOT(on_hostNameField_leave()));
//    hostNameField.addKeyListener(new KeyListener() {
//    //Override
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//    //Override
//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            adapter->setHostName(hostNameField.getText());
//            p.addComboBoxLastSelection(adapter->getClass().getName() + ".hostname", hostNameField.getText());
//        }

//    //Override
//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });
//    portField.addActionListener(new ActionListener() {
//    //Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                adapter->setPort(Integer.parseInt(portField.getText()));
//            } catch (java.lang.NumberFormatException ex) {
//                log->warn("Could not parse port attribute");
//            }
//        }
//    });
         connect(portField, SIGNAL(editingFinished()), this, SLOT(on_portField_leave()));

//    portField.addKeyListener(new KeyListener() {
//    //Override
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//    //Override
//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            try {
//                adapter->setPort(Integer.parseInt(portField.getText()));
//            } catch (java.lang.NumberFormatException ex) {
//                log->warn("Could not parse port attribute");
//            }
//        }

//    //Override
//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

//    adNameField.addActionListener(new ActionListener() {
//    //Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            adapter->setAdvertisementName(adNameField.getText());
//        }
//    });
 connect(adNameField, SIGNAL(editingFinished()), this, SLOT(on_adNameField_leave()));

//    adNameField.addKeyListener(new KeyListener() {
//    //Override
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//    //Override
//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            adapter->setAdvertisementName(adNameField.getText());
//        }

//    //Override
//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

//    serviceTypeField.addActionListener(new ActionListener() {
//    //Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            adapter->setServiceType(serviceTypeField.getText());
//        }
//    });
 connect(serviceTypeField, SIGNAL(editingFinished()), this, SLOT(on_serviceTypeField_leave()));

//    serviceTypeField.addKeyListener(new KeyListener() {
//    //Override
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//    //Override
//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            adapter->setServiceType(serviceTypeField.getText());
//        }

//    //Override
//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

 foreach (QString i, options.keys())
 {
  /*final*/ QString item = i;
  QSignalMapper* cbMapper = new QSignalMapper;
  if (qobject_cast<QComboBox*>(options.value(i)->getComponent() ) != NULL)
  {
//            ((JComboBox<?>) options.get(i).getComponent()).addActionListener(new ActionListener() {
//            //Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    adapter->setOptionState(item, options.get(item).getItem());
//                }
//            });
   QComboBox* box = (QComboBox*)options.value(i)->getComponent();
   cbMapper->setMapping(box,box);
   connect(box, SIGNAL(currentIndexChanged(QString)), cbMapper, SLOT(map()));
  }
  connect(cbMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_optionCb_currentIndexChanged(QWidget*)));
 }

 if (adapter->getSystemConnectionMemo() != NULL)
 {
//        systemPrefixField.addActionListener(new ActionListener() {
//        //Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!adapter->getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())) {
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter->getSystemConnectionMemo().getSystemPrefix());
//                }
//            }
//        });
  connect(systemPrefixField, SIGNAL(editingFinished()), this, SLOT(on_systemPrefixField_editingFinished()));

//        systemPrefixField.addFocusListener(new FocusListener() {
//        //Override
//            /*public*/ void focusLost(FocusEvent e) {
//                if (!adapter->getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())) {
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter->getSystemConnectionMemo().getSystemPrefix());
//                }
//            }

//        //Override
//            /*public*/ void focusGained(FocusEvent e) {
//            }
//        });
  connect(systemPrefixField, SIGNAL(editingFinished()), this, SLOT(on_systemPrefixField_leave()));

//        connectionNameField.addActionListener(new ActionListener() {
//        //Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!adapter->getSystemConnectionMemo().setUserName(connectionNameField.getText())) {
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter->getSystemConnectionMemo().getUserName());
//                }
//            }
//        });
//        connectionNameField.addFocusListener(new FocusListener() {
//        //Override
//            /*public*/ void focusLost(FocusEvent e) {
//                if (!adapter->getSystemConnectionMemo().setUserName(connectionNameField.getText())) {
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter->getSystemConnectionMemo().getUserName());
//                }
//            }

//        //Override
//            /*public*/ void focusGained(FocusEvent e) {
//            }
//        });
  connect(connectionNameField, SIGNAL(editingFinished()), this, SLOT(on_connectionNameField_leave()));
 }
 init = true;
}
void AbstractNetworkConnectionConfig::on_hostNameField_leave()
{
 adapter->setHostName(hostNameField->text());
 p->addComboBoxLastSelection(QString(adapter->metaObject()->className()) + ".hostname", hostNameField->text());
}

void AbstractNetworkConnectionConfig::on_optionCb_currentIndexChanged(QWidget * widget)
{
 foreach (QString i, options.keys())
 {
  if((QWidget*)options.value(i)->getComponent() == widget)
  {
   adapter->setOptionState(i, ((QComboBox*)widget)->currentText());
  }
 }
}
void AbstractNetworkConnectionConfig::on_portField_leave()
{
 bool bOk;
 adapter->setPort(portField->text().toInt(&bOk));
 //            } catch (java.lang.NumberFormatException ex) {
 //                log->warn("Could not parse port attribute");
 //            }
 if(!bOk) portField->setFocus();
}

void AbstractNetworkConnectionConfig::on_adNameField_leave()
{
 adapter->setAdvertisementName(adNameField->text());

}

void AbstractNetworkConnectionConfig::on_serviceTypeField_leave()
{
 adapter->setServiceType(serviceTypeField->text());

}
void AbstractNetworkConnectionConfig::on_systemPrefixField_editingFinished()
{
 if (!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
 //                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"), tr("System Prefix ") + systemPrefixField->text() + " is already assigned");
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());

 }
}

void AbstractNetworkConnectionConfig::on_systemPrefixField_leave()
{
 if (!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
 //                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"), tr("System Prefix ") + systemPrefixField->text() + " is already assigned");
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
 }
}
void AbstractNetworkConnectionConfig::on_connectionNameField_leave()
{
 if (!adapter->getSystemConnectionMemo()->setUserName(connectionNameField->text()))
 {
  //                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"), tr("Connection Name ") + systemPrefixField->text() + " is already assigned");
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
}
//Override
/*public*/ void AbstractNetworkConnectionConfig::updateAdapter()
{
 if (adapter->getMdnsConfigure())
 {
  // set the hostname if it is not blank.
  if (!(hostNameField->text()==("")))
  {
   adapter->setHostName(hostNameField->text());
  }
  // set the advertisement name if it is not blank.
  if (!(adNameField->text()==("")))
  {
   adapter->setAdvertisementName(adNameField->text());
  }
  // set the Service Type if it is not blank.
  if (!(serviceTypeField->text()==("")))
  {
   adapter->setServiceType(serviceTypeField->text());
  }
  // and get the host IP and port number
  // via mdns
  adapter->autoConfigure();
 }
 else
 {
  adapter->setHostName(hostNameField->text());
  adapter->setPort(portField->text().toInt());
 }
 foreach (QString i, options.keys())
 {
  adapter->setOptionState(i, options.value(i)->getItem());
 }
 if (adapter->getSystemConnectionMemo() != NULL && !adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
}


//Override
/*public*/ PortAdapter* AbstractNetworkConnectionConfig::getAdapter() {
    return adapter;
}

/**
 * Load the adapter with an appropriate object
 * <i>unless</I> its already been set.
 */
//Override
/*abstract*/ /*protected*/ void AbstractNetworkConnectionConfig::setInstance() {}

//Override
/*public*/ QString AbstractNetworkConnectionConfig::getInfo() {
    return adapter->getCurrentPortName();
}

//Override
/*public*/ void AbstractNetworkConnectionConfig::loadDetails(/*final*/ QWidget* details)
{
 _details = details;
 setInstance();
 if (!init)
 {
  //Build up list of options
  //Hashtable<String, AbstractPortController.Option> adapterOptions = ((AbstractPortController)adapter).getOptionList();
  QStringList optionsAvailable = adapter->getOptions();
  options = QHash<QString, Option*>();
  foreach (QString i, optionsAvailable)
  {
   QComboBox* opt = new QComboBox(/*adapter->getOptionChoices(i)*/);
   opt->addItems(adapter->getOptionChoices(i));
   opt->setCurrentIndex(opt->findText(adapter->getOptionState(i)));
   // check that it worked
   if (adapter->getOptionState(i)!=(opt->currentText()))
   {
    // no, set 1st option choice
    opt->setCurrentIndex(0);
    adapter->setOptionState(i, opt->currentText());
    log->warn(tr("Loading found invalid value for option %1, found \"%2\", setting to \"%3\"").arg( i).arg( adapter->getOptionState(i)).arg( opt->currentText()));
   }
   options.insert(i, new Option(adapter->getOptionDisplayName(i), opt, adapter->isOptionAdvanced(i)));
  }
 }

//    if (hostNameField.getActionListeners().length > 0) {
//        hostNameField.removeActionListener(hostNameField.getActionListeners()[0]);
//    }

 if (adapter->getSystemConnectionMemo() != NULL)
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
  NUMOPTIONS = NUMOPTIONS + 2;
 }
 NUMOPTIONS = NUMOPTIONS + options.size();
 hostNameField->setText(((AbstractNetworkPortController*)adapter)->getHostName());
 hostNameFieldLabel = new QLabel(tr("IP Address/Host Name: "));
 hostNameField->setToolTip(tr("IP Address for fully manual configuration.  Optional hostname for ZeroConf/mDNS configuration. "));
 //if(adapter->getHostName()==(""))
 if(hostNameField->text().isEmpty())
 {
  hostNameField->setText(p->getComboBoxLastSelection(QString(adapter->metaObject()->className()) + ".hostname"));
  adapter->setHostName(hostNameField->text());
 }

 portField->setToolTip(tr("Port address setting of the TCP Connection"));
 portField->setEnabled(true);
 portField->setText(QString::number(((AbstractNetworkPortController*)adapter)->getPort()));
 portFieldLabel = new QLabel(tr("TCP/UDP Port: "));

 adNameField->setToolTip(tr("Expected ZeroConf/mDNS Advertisement Identifier"));
 adNameField->setEnabled(false);
 adNameField->setText("" + ((AbstractNetworkPortController*)adapter)->getAdvertisementName());
 adNameFieldLabel = new QLabel(tr("Advertisement Identifier: "));
 adNameFieldLabel->setEnabled(false);

 serviceTypeField->setToolTip(tr("ZeroConf/mDNS service type. "));
 serviceTypeField->setEnabled(false);
 serviceTypeField->setText("" + ((AbstractNetworkPortController*)adapter)->getServiceType());
 serviceTypeFieldLabel = new QLabel(tr("Service Type Name: "));
 serviceTypeFieldLabel->setEnabled(false);
 QFont f = showAutoConfig->font();
 f.setPointSizeF(9.0);
 showAutoConfig->setFont(f);
 //showAutoConfig->setForeground(Qt::blue);
 showAutoConfig->setStyleSheet("QCheckBox {color: blue} ");
//    showAutoConfig.addItemListener(
//            new ItemListener() {
//            //Override
//                /*public*/ void itemStateChanged(ItemEvent e) {
//                    setAutoNetworkConfig();
//                }
//            });
 connect(showAutoConfig, SIGNAL(toggled(bool)), this, SLOT(setAutoNetworkConfig()));
 showAutoConfig->setChecked(((AbstractNetworkPortController*)adapter)->getMdnsConfigure());
 setAutoNetworkConfig();

 f = showAdvanced->font();
 f.setPointSizeF(9.0);showAdvanced->setFont(f);
 //showAdvanced->setForeground(Qt::blue);
 showAdvanced->setStyleSheet("QCheckBox {color: blue} ");
//    showAdvanced.addItemListener(
//            new ItemListener() {
//            //Override
//                /*public*/ void itemStateChanged(ItemEvent e) {
//                    showAdvancedItems();
//                }
//            });
 connect(showAdvanced, SIGNAL(toggled(bool)), this, SLOT(showAdvancedItems()));
 showAdvancedItems();

 init = false;		// need to reload action listeners
 checkInitDone();
}

//Override
/*protected*/ void AbstractNetworkConnectionConfig::showAdvancedItems()
{
 //_details->removeAll();
 QObjectList l = _details->children();
 foreach(QObject* o, l)
 {
  if(qobject_cast<QWidget*>(o) != NULL)
  {
   ((QGridLayout*)_details->layout())->removeWidget((QWidget*)o);
//   if(o != hostNameField && o != hostNameFieldLabel)
//    delete o;
   ((QWidget*)o)->setVisible(false);
  }
 }
 delete _details->layout();
 gbLayout = new QGridLayout;

 cL->anchor = GridBagConstraints::WEST;
 cL->insets = new Insets(2, 5, 0, 5);
 cR->insets = new Insets(2, 0, 0, 5);
 cR->anchor = GridBagConstraints::WEST;
 cR->gridx = 1;
 cL->gridx = 0;
 int i = 0;
 int stdrows = 0;
 bool incAdvancedOptions = true;
 if (!isPortAdvanced())
 {
  stdrows++;
 }
 if (!isHostNameAdvanced())
 {
  stdrows++;
 }
 foreach (QString item, options.keys())
 {
  if (!options.value(item)->isAdvanced())
  {
   stdrows++;
  }
 }
 if (adapter->getSystemConnectionMemo() != NULL)
 {
  stdrows = stdrows + 2;
 }
 if (stdrows == NUMOPTIONS)
 {
  incAdvancedOptions = false;
 }
// if(_details->layout() == NULL)
 _details->setLayout(gbLayout);
 i = addStandardDetails(incAdvancedOptions, i);
 if (showAdvanced->isChecked())
 {
  if (isHostNameAdvanced())
  {
   cR->gridy = i;
   cL->gridy = i;
//   gbLayout->setConstraints(hostNameFieldLabel, cL);
//   gbLayout->setConstraints(hostNameField, cR);
   //_details.add(hostNameFieldLabel);
   gbLayout->addWidget(hostNameFieldLabel,cL->gridy, cL->gridx);
   //_details.add(hostNameField);
   gbLayout->addWidget(hostNameField, cR->gridy, cR->gridx);
   hostNameFieldLabel->setVisible(true);
   hostNameField->setVisible(true);
   i++;
  }

  if (isPortAdvanced())
  {
   cR->gridy = i;
   cL->gridy = i;
//   gbLayout->setConstraints(portFieldLabel, cL);
//   gbLayout->setConstraints(portField, cR);
   //_details.add(portFieldLabel);
   gbLayout->addWidget(portFieldLabel,cL->gridy, cL->gridx);
   //_details.add(portField);
   gbLayout->addWidget(portField, cR->gridy, cR->gridx);
   portField->setVisible(true);
   portField->setVisible(true);
   i++;
  }

  if (showAutoConfig->isChecked())
  {
   cR->gridy = i;
   cL->gridy = i;
//   gbLayout->setConstraints(adNameFieldLabel, cL);
//   gbLayout->setConstraints(adNameField, cR);
   //_details.add(adNameFieldLabel);
   gbLayout->addWidget(adNameFieldLabel,cL->gridy, cL->gridx);
   //_details.add(adNameField);
   gbLayout->addWidget(adNameField, cR->gridy, cR->gridx);
   adNameFieldLabel->setVisible(true);
   adNameField->setVisible(true);
   cR->gridy = i;
   cL->gridy = i;
//   gbLayout->setConstraints(serviceTypeFieldLabel, cL);
//   gbLayout->setConstraints(serviceTypeField, cR);
   //_details.add(serviceTypeFieldLabel);
   gbLayout->addWidget(serviceTypeFieldLabel,cL->gridy, cL->gridx);
   //_details.add(serviceTypeField);
   gbLayout->addWidget(serviceTypeField, cR->gridy, cR->gridx);
   i++;
   serviceTypeField->setVisible(true);
   serviceTypeFieldLabel->setVisible(true);
  }

  foreach (QString item, options.keys())
  {
   if (options.value(item)->isAdvanced())
   {
    cR->gridy = i;
    cL->gridy = i;
//    gbLayout->setConstraints(options.get(item).getLabel(), cL);
//    gbLayout->setConstraints(options.get(item).getComponent(), cR);
//                _details.add(options.get(item).getLabel());
    gbLayout->addWidget(options.value(item)->getLabel(),cL->gridy, cL->gridx);
//                _details.add(options.get(item).getComponent());
    gbLayout->addWidget(options.value(item)->getComponent(), cR->gridy, cR->gridx);
    i++;
    options.value(item)->getLabel()->setVisible(true);
    options.value(item)->getComponent()->setVisible(true);
   }
  }
 }
 cL->gridwidth = 2;
 foreach (QWidget* item, *additionalItems)
 {
  cL->gridy = i;
//  gbLayout->setConstraints(item, cL);
  //_details.add(item);
  gbLayout->addWidget(item,cL->gridy, cL->gridx);
  item->setVisible(true);
  i++;
 }
 cL->gridwidth = 1;
//    if (qobject_cast<_details.getParent() != NULL && _details.getParent() instanceof javax.swing.JViewport) {
//        javax.swing.JViewport vp = (javax.swing.JViewport) _details.getParent();
//        vp.revalidate();
//        vp.repaint();
//    }
}

/*protected*/ int AbstractNetworkConnectionConfig::addStandardDetails(bool incAdvanced, int i)
{

 if (isAutoConfigPossible())
 {
  cR->gridy = i;
  cL->gridy = i;
//     gbLayout->setConstraints(showAutoConfig, cR);
//     _details.add(showAutoConfig);
  gbLayout->addWidget(showAutoConfig,cL->gridy, cL->gridx);
//     _details.add(showAutoConfig);
//     gbLayout->setConstraints(showAutoConfig, cR);
  i++;
  showAutoConfig->setVisible(true);
 }

 if (!isHostNameAdvanced())
 {
  cR->gridy = i;
  cL->gridy = i;
//     gbLayout->setConstraints(hostNameFieldLabel, cL);
//     gbLayout->setConstraints(hostNameField, cR);
//     _details.add(hostNameFieldLabel);
  gbLayout->addWidget(hostNameFieldLabel,cL->gridy, cL->gridx);
//     _details.add(hostNameField);
  gbLayout->addWidget(hostNameField, cR->gridy, cR->gridx);
  i++;
  hostNameField->setVisible(true);
  hostNameFieldLabel->setVisible(true);
 }

 if (!isPortAdvanced())
 {
  cR->gridy = i;
  cL->gridy = i;
//     gbLayout->setConstraints(portFieldLabel, cL);
//     gbLayout->setConstraints(portField, cR);
//     _details.add(portFieldLabel);
  gbLayout->addWidget(portFieldLabel,cL->gridy, cL->gridx);
//     _details.add(portField);
  gbLayout->addWidget(portField, cR->gridy, cR->gridx);
  i++;
  portFieldLabel->setVisible(true);
  portField->setVisible(true);
 }
 return AbstractConnectionConfig::addStandardDetails((PortAdapter*)adapter, incAdvanced, i);
}

/*public*/ bool AbstractNetworkConnectionConfig::isHostNameAdvanced() {
    return false;
}

/*public*/ bool AbstractNetworkConnectionConfig::isPortAdvanced()
{
 return true;
}

/*public*/ bool AbstractNetworkConnectionConfig::isAutoConfigPossible()
{
 return false;
}

/*public*/ void AbstractNetworkConnectionConfig::setAutoNetworkConfig()
{
 if (showAutoConfig->isChecked())
 {
  portField->setEnabled(false);
  portFieldLabel->setEnabled(false);
  ((AbstractNetworkPortController*)adapter)->setMdnsConfigure(true);
 }
 else
 {
  portField->setEnabled(true);
  portFieldLabel->setEnabled(true);
  ((AbstractNetworkPortController*)adapter)->setMdnsConfigure(false);
 }
}

//Override
/*public*/ QString AbstractNetworkConnectionConfig::getManufacturer()
{
 if(adapter == NULL) return "";
 return ((AbstractNetworkPortController*)adapter)->getManufacturer();
}

//Override
/*public*/ void AbstractNetworkConnectionConfig::setManufacturer(QString manufacturer) {
    ((AbstractNetworkPortController*)adapter)->setManufacturer(manufacturer);
}

//Override
/*public*/ bool AbstractNetworkConnectionConfig::getDisabled() {
    if (adapter == NULL) {
        return true;
    }
    return ((AbstractNetworkPortController*)adapter)->getDisabled();
}

//Override
/*public*/ void AbstractNetworkConnectionConfig::setDisabled(bool disabled) {
    if (adapter != NULL) {
        ((AbstractNetworkPortController*)adapter)->setDisabled(disabled);
    }
}

//Override
/*public*/ QString AbstractNetworkConnectionConfig::getConnectionName() {
    if (((AbstractNetworkPortController*)adapter)->getSystemConnectionMemo() != NULL) {
        return ((AbstractNetworkPortController*)adapter)->getSystemConnectionMemo()->getUserName();
    } else {
        return name();
    }
}

//Override
/*public*/ void AbstractNetworkConnectionConfig::dispose() {
    if (adapter != NULL) {
        ((AbstractNetworkPortController*)adapter)->dispose();
        adapter = NULL;
    }
    AbstractConnectionConfig::dispose();
}
