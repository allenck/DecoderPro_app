#include "abstractserialconnectionconfig.h"
#include "portadapter.h"
#include "serialportadapter.h"
#include "instancemanager.h"
#include <QComboBox>
#include "defaultusermessagepreferences.h"
#include "jtextfield.h"
#include "systemconnectionmemo.h"
#include <QMessageBox>
#include <QCheckBox>
#include "gridbagconstraints.h"
#include "jframe.h"
#include <QLabel>
#include <QGridLayout>
#include <QSerialPortInfo>
#include <pr3adapter.h>
#include "jmrixconfigpane.h"

//AbstractSerialConnectionConfig::AbstractSerialConnectionConfig(QObject *parent) :
//    AbstractConnectionConfig(parent)
//{
//}
/**
 * Abstract base class for common implementation of the ConnectionConfig
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003
 * @version	$Revision: 28389 $
 */

//
///*abstract*/ /*public*/ class AbstractSerialConnectionConfig extends AbstractConnectionConfig {

/**
 * Ctor for an object being created during load process
 * @param p port being configured
 */
/*public*/ AbstractSerialConnectionConfig::AbstractSerialConnectionConfig(PortAdapter* p, QObject *parent)
    : AbstractConnectionConfig(parent)
{
 common();
 //this((SerialPortAdapter)p);
 adapter =(SerialPortAdapter*)p;
 Q_ASSERT(adapter != NULL);
 addToActionList();
}
/*public*/ AbstractSerialConnectionConfig::AbstractSerialConnectionConfig(SerialPortAdapter* p, QObject *parent)
: AbstractConnectionConfig(parent)
{
 common();
 adapter = p;
 Q_ASSERT(adapter != NULL);
 addToActionList();
}

//@Override
/*public*/ PortAdapter* AbstractSerialConnectionConfig::getAdapter() { return (PortAdapter*)adapter; }

/**
 * Ctor for a functional object with no prexisting adapter->
 * Expect that the subclass setInstance() will fill the adapter member.
 */
/*public*/ AbstractSerialConnectionConfig::AbstractSerialConnectionConfig(QObject *parent)
    : AbstractConnectionConfig(parent)
{
 common();
 adapter = NULL;
 addToActionList();
}

void AbstractSerialConnectionConfig::common()
{
 init = false;
 adapter = NULL;
 log = new Logger("AbstractSerialConnectionConfig");
 p = (DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager");
 portBox = new QComboBox();
 baudBox = new QComboBox();
 invalidPort = "";
}

//@Override
/*protected*/ void AbstractSerialConnectionConfig::checkInitDone()
{
 if (log->isDebugEnabled()) log->debug("init called for "+name());
 if (init) return;

// baudBox.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            adapter->configureBaudRate((String)baudBox.getSelectedItem());
//            p.addComboBoxLastSelection(adapter->metaObject()->className())+".baud", (String) baudBox.getSelectedItem());
//        }
//    });
 connect(baudBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_baudBox_currentIndexChanged(QString)));

 if(adapter->getSystemConnectionMemo()!=NULL)
 {
//  systemPrefixField.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if(!adapter->getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter->getSystemConnectionMemo().getSystemPrefix());
//                }
//            }
//        });
 connect(systemPrefixField, SIGNAL(editingFinished()), this, SLOT(On_systemPrefixField_editingFinished()));

//        systemPrefixField.addFocusListener( new FocusListener() {
//            @Override
//            /*public*/ void focusLost(FocusEvent e){
//                if(!adapter->getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter->getSystemConnectionMemo().getSystemPrefix());
//                }
//            }
//            @Override
//            /*public*/ void focusGained(FocusEvent e){ }
//        });

//        connectionNameField.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if(!adapter->getSystemConnectionMemo().setUserName(connectionNameField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter->getSystemConnectionMemo().getUserName());
//                }
//            }
//        });
 connect(connectionNameField, SIGNAL(editingFinished()), this, SLOT(On_connectionNameField_editingFinished()));

//        connectionNameField.addFocusListener( new FocusListener() {
//            @Override
//            /*public*/ void focusLost(FocusEvent e){
//                if(!adapter->getSystemConnectionMemo().setUserName(connectionNameField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter->getSystemConnectionMemo().getUserName());
//                }
//            }
//            @Override
//            /*public*/ void focusGained(FocusEvent e){ }
//        });
    }

//    portBox.addFocusListener( new FocusListener() {
//    /*    @Override
//        /*public*/ void focusGained(FocusEvent e){
//            refreshPortBox();
//        }
//        @Override
//        /*public*/ void focusLost(FocusEvent e){}

//    })*/;

 foreach(QString i, options.keys())
 {
  /*final*/ QString item = i;
  //if(options.get(i).getComponent() instanceof JComboBox)
  if(qobject_cast<QComboBox*>(options.value(i)->getComponent()) != NULL)
  {
//   ((JComboBox)options.get(i).getComponent()).addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    adapter->setOptionState(item, options.get(item).getItem());
//                }
//            });
  QComboBox* box = (QComboBox*)options.value(i)->getComponent();
  connect(box, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_optionBox_currentIndexChanged(QString)));
  }
 }

 init = true;
}

void AbstractSerialConnectionConfig::On_baudBox_currentIndexChanged(QString s)
{
 //            adapter->configureBaudRate((String)baudBox.getSelectedItem());
 adapter->configureBaudRate(s);
 p->addComboBoxLastSelection(QString(adapter->metaObject()->className())+".baud", s);
}

void AbstractSerialConnectionConfig::On_systemPrefixField_editingFinished()
{
 if(!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
    //                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"),"System Prefix " + systemPrefixField->text() + " is already assigned");
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
 }
}
void AbstractSerialConnectionConfig::On_connectionNameField_editingFinished()
{
 if(!adapter->getSystemConnectionMemo()->setUserName(connectionNameField->text()))
 {
    //                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
     QMessageBox::warning(NULL, tr("Warning"),"Connection Name " + connectionNameField->text() + " is already assigned");
 connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
    //
 }
}

 void AbstractSerialConnectionConfig::On_optionBox_currentIndexChanged(QString item)
 {
  adapter->setOptionState(item, options.value(item)->getItem());
 }

//@Override
/*public*/ void AbstractSerialConnectionConfig::updateAdapter()
{
 adapter->setPort(PortNameMapper::getPortFromName(portBox->currentText()));
 adapter->configureBaudRate(baudBox->currentText());
 foreach(QString i,options.keys())
 {
  adapter->setOptionState(i, options.value(i)->getItem());
 }

 if(adapter->getSystemConnectionMemo()!=NULL && !adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
}

/**
 * Load the adapter with an appropriate object
 * <i>unless</I> its already been set.
 */
//@Override
//abstract /*protected*/ void setInstance();

//@Override
/*public*/ QString AbstractSerialConnectionConfig::getInfo()
{
 //int index = portBox->currentIndex();
 QString t;
 if(portBox->count() > 0)
  t = portBox->currentText();
 if (t!="")
 {
  return PortNameMapper::getPortFromName(t);
  //return t;
 }
 else if ((adapter!=NULL) && (((PR3Adapter*)adapter)->getCurrentPortName()!=NULL))
 {
  return ((PR3Adapter*)adapter)->getCurrentPortName();
 }
 return JmrixConfigPane::NONE;
}


//@SuppressWarnings("UseOfObsoleteCollectionType")
/*public*/ void AbstractSerialConnectionConfig::refreshPortBox()
{
 if (!init)
 {
  v = getPortNames();
  //portBox.setRenderer(new ComboBoxRenderer());
        // Add this line to ensure that the combo box header isn't made too narrow
  //portBox.setPrototypeDisplayValue("A fairly long port name of 40 characters"); //NO18N

 }
 else
 {
   QVector<QString>* v2 = getPortNames();
   if (v2==(originalList))
   {
    log->debug("List of valid Ports has not changed, therefore we will not refresh the port list");
    return;
   }
   log->debug("List of valid Ports has been changed, therefore we will refresh the port list");
   v = new QVector<QString>();
   v->resize(v2->size());
   //Collections.copy(v, v2);
   for(int i=0; i < v2->size(); i++)
    v->replace(i,v2->at(i));
 }

 if(v==NULL)
 {
  log->error("port name Vector v is NULL!");
  return;
 }

 /* as we make amendments to the list of port in vector v, we keep a copy of it before
    modification, this copy is then used to validate against any changes in the port lists.
  */
 originalList = new QVector<QString>();
 originalList->resize(v->size());
 //Collections.copy(originalList, v);
 for(int i=0; i < v->size(); i++) originalList->replace(i,v->at(i));
//  if(portBox.getActionListeners().length >0)
//        portBox.removeActionListener(portBox.getActionListeners()[0]);
 disconnect(portBox);
 portBox->clear();
 log->debug("getting fresh list of available Serial Ports");

  if (v->isEmpty())
    v->insert(0,tr("(no ports found!)"));
  QString portName = adapter->getCurrentPortName();
  if (portName != NULL && portName!=(tr("none selected)")) && portName!=(tr("(no ports found!)")))
  {
   if(!v->contains(portName))
   {
    v->insert(0,portName);
    invalidPort=portName;
    //portBox->setForeground(Color.red);
    portBox->setStyleSheet("QComboBox {color: red;}");
   }
   else if (invalidPort!=NULL && invalidPort==(portName))
   {
    invalidPort="";
   }
 }
 else
 {
  if (!v->contains(portName))
  {
   v->insert(0,tr("(none selected)"));
  }
  else if (p->getComboBoxLastSelection(QString(adapter->metaObject()->className())+".port")==NULL)
  {
   v->insert(0,tr("(none selected)"));
  }
 }
 updateSerialPortNames(portName, portBox, v);
 if (portName == NULL || portName==(tr("(none selected)")) || portName==(tr("noPortsFound")))
 {
  bool bContinue = true;
  for (int i=0; i<portBox->count(); i++)
  {
//   outerloop:
   foreach(QString friendlyName, getPortFriendlyNames())
   {
    if((portBox->itemText(i))==(friendlyName))
    {
     portBox->setCurrentIndex(i);
     adapter->setPort(PortNameMapper::getPortFromName(portBox->itemText(i)));
     //break outerloop;
     bContinue = false;
    }
   }
   if(!bContinue)
    break;
  }
 }

//  portBox.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            String port = PortNameMapper.getPortFromName((String)portBox.getSelectedItem());
//            adapter->setPort(port);
//        }
//    });
 connect(portBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_portBox_currentIndexChanged(QString)));
}
 void AbstractSerialConnectionConfig::On_portBox_currentIndexChanged(QString s)
 {
  QString port = PortNameMapper::getPortFromName(s);
  adapter->setPort(port);
 }



//@Override
//@SuppressWarnings("UseOfObsoleteCollectionType")
/*public*/ void AbstractSerialConnectionConfig::loadDetails(/*final*/ QWidget* details)
{
 _details = details;
 setInstance();
 if(!init)
 {
  //Build up list of options
  QStringList optionsAvailable = adapter->getOptions();
  options =   QHash<QString, Option*>();
  foreach(QString i, optionsAvailable)
  {
   QComboBox/*<String>*/* opt = new QComboBox();
   opt->addItems(adapter->getOptionChoices(i));
   opt->setCurrentIndex(opt->findText(adapter->getOptionState(i)));
   // check that it worked
   if (! (adapter->getOptionState(i)==(opt->currentText())))
   {
    // no, set 1st option choice
    opt->setCurrentIndex(0);
    adapter->setOptionState(i, opt->currentText());
    log->warn(tr("Loading found invalid value for option %1, found \"%2\", setting to \"%3\"").arg(i).arg(adapter->getOptionState(i)).arg( opt->currentText()));
    }
    options.insert(i, new Option(adapter->getOptionDisplayName(i), opt, adapter->isOptionAdvanced(i)));
   }
  }

//  try
// {
  v = getPortNames();
  if (log->isDebugEnabled())
  {
    log->debug(QString("loadDetails called in class ")+this->metaObject()->className());
    log->debug("adapter class: "+QString(adapter->metaObject()->className()));
    log->debug("loadDetails called for "+name());
    if (v!=NULL) log->debug("Found "+QString::number(v->size())+" ports");
    else log->debug("Zero-length port vector");
  }
// }
// catch (UnsatisfiedLinkError e1)
// {
//  log->error("UnsatisfiedLinkError - the gnu.io library has not been installed properly");
//  log->error("java.library.path="+System.getProperty("java.library.path","<unknown>"));
//  //     javax.swing.JOptionPane.showMessageDialog(NULL, "Failed to load comm library.\nYou have to fix that before setting preferences.");
//  QMessageBox::warning(NULL, tr("Warning"), tr("Failed to load comm library.\nYou have to fix that before setting preferences."));
//  return;
// }

 if(adapter->getSystemConnectionMemo()!=NULL)
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
  NUMOPTIONS=NUMOPTIONS+2;
 }

 refreshPortBox();

 baudList = adapter->validBaudRates();
 // need to remove ActionListener before addItem() or action event will occur
// if(baudBox.getActionListeners().length >0)
//        baudBox.removeActionListener(baudBox.getActionListeners()[0]);
 disconnect(baudBox);
 baudBox->clear();
 if (log->isDebugEnabled()) log->debug("after remove, "+QString::number(baudBox->count())+" items, first is "
            +baudBox->itemText(0));
 foreach(QString baudList1, baudList)
 {
  baudBox->addItem(baudList1);
 }
 if (log->isDebugEnabled()) log->debug("after reload, "+QString::number(baudBox->count())+" items, first is "
               +baudBox->itemText(0));

 if (baudList.length()>1)
 {
  baudBox->setToolTip("Must match the baud rate setting of your hardware");
  baudBox->setEnabled(true);
 }
 else
 {
  baudBox->setToolTip("The baud rate is fixed for this protocol");
  baudBox->setEnabled(false);
 }

 NUMOPTIONS = NUMOPTIONS+options.size();

 portBoxLabel = new QLabel("Serial port: ");

 baudBoxLabel = new QLabel("Baud rate:");
 baudBox->setCurrentIndex(baudBox->findText(adapter->getCurrentBaudRate()));
 //showAdvanced->setFont(showAdvanced->font().setPointSizeF(9.0));
 QFont f = showAdvanced->font();
 f.setPointSizeF(9.0);
 showAdvanced->setFont(f);
 //showAdvanced.setForeground(Color.blue);
 showAdvanced->setStyleSheet("QCheckBox { color: blue; background-color: lightgray;} QCheckBox::hover { background-color: lightpink; }");
// showAdvanced.addItemListener(
//        new ItemListener() {
//            @Override
//            /*public*/ void itemStateChanged(ItemEvent e){
//                showAdvancedItems();
//            }
//        });
 connect(showAdvanced, SIGNAL(clicked()), this, SLOT(showAdvancedItems()));
 showAdvancedItems();
 init = false;       // need to reload action listeners
 checkInitDone();
}

//@Override
/*protected*/ void AbstractSerialConnectionConfig::showAdvancedItems()
{
  //_details->removeAll();
//  QObjectList items = _details->children();
//  foreach (QObject* o, items)
//  {
//   if(qobject_cast<QWidget*>(o) != NULL)
//   {
//    _details->layout()->removeWidget((QWidget*)o);
//    //delete o;
//    ((QWidget*)o)->hide();
//   }
//   else
//    o->deleteLater();
//  }
 if(_details->layout() != NULL)
 {
  QLayoutItem *child;
  while ((child = _details->layout()->takeAt(0)) != 0)
  {
   child->widget()->hide();
   delete child;
  }
 }
//  if(qobject_cast<QLayout*>(o) != NULL)
//  {
//   _details->layout()->removeItem((QLayout*)o);
  delete _details->layout();
  gbLayout = new QGridLayout;
//    //o->deleteLater();
//  }
 cL->anchor = GridBagConstraints::WEST;
 cL->insets = new Insets(2, 5, 0, 5);
 cR->insets = new Insets(2, 0, 0, 5);
 cR->anchor = GridBagConstraints::WEST;
 cR->gridx = 1;
 cL->gridx = 0;
 int i = 0;
 int stdrows = 0;
 bool incAdvancedOptions=true;
 if(!isBaudAdvanced()) stdrows++;
 if(!isPortAdvanced()) stdrows++;
 foreach(QString item,options.keys())
 {
  if(!options.value(item)->isAdvanced())
   stdrows++;
 }

 if(adapter->getSystemConnectionMemo()!=NULL) stdrows=stdrows+2;
 if (stdrows == NUMOPTIONS)
 {
  incAdvancedOptions=false;
 }
 if(_details->layout() == NULL)
  _details->setLayout(gbLayout);
 else
  if(qobject_cast<QGridLayout*>(_details->layout()) != NULL)
    gbLayout = (QGridLayout*)_details->layout();
 i = addStandardDetails(incAdvancedOptions, i);
 if (showAdvanced->isChecked())
 {

  if(isPortAdvanced())
  {
   cR->gridy = i;
   cL->gridy = i;
//    gbLayout.setConstraints(portBoxLabel, cL);
//    gbLayout.setConstraints(portBox, cR);

    //panel.add(row1Label);
   gbLayout->addWidget(portBoxLabel, cL->gridy, cL->gridx);
   portBoxLabel->setVisible(true);
   gbLayout->addWidget(portBox, cR->gridy, cR->gridx);
   portBox->setVisible(true);
   i++;
  }

  if(isBaudAdvanced())
  {
   cR->gridy = i;
   cL->gridy = i;
//    gbLayout.setConstraints(baudBoxLabel, cL);
//    gbLayout.setConstraints(baudBox, cR);
   gbLayout->addWidget(baudBoxLabel, cL->gridy, cL->gridx);
   baudBoxLabel->setVisible(true);
   gbLayout->addWidget(baudBox, cR->gridy, cR->gridx);
   baudBox->setVisible(true);
   i++;
  }
  foreach(QString item,options.keys())
  {
   if(options.value(item)->isAdvanced())
   {
    cR->gridy = i;
    cL->gridy = i;
//    gbLayout.setConstraints(options.get(item).getLabel(), cL);
//    gbLayout.setConstraints(options.get(item).getComponent(), cR);
    gbLayout->addWidget(options.value(item)->getLabel(), cL->gridy, cL->gridx);
    options.value(item)->getLabel()->setVisible(true);
    gbLayout->addWidget(options.value(item)->getComponent(), cR->gridy, cR->gridx);
    options.value(item)->getComponent()->setVisible(true);
    i++;
   }
  }
 }
 cL->gridwidth=2;
 foreach(QWidget* item, *additionalItems)
 {
  cL->gridy = i;
//  gbLayout.setConstraints(item, cL);
  gbLayout->addWidget(item, cL->gridy, cL->gridx);
  item->setVisible(true);
  i++;
 }
 cL->gridwidth=1;

 //if (_details.getParent()!=NULL && _details.getParent() instanceof javax.swing.JViewport)
 if(_details->parent()!=NULL && qobject_cast<QWidget*>(_details->parent())!=NULL)
 {
  //JViewport* vp = (JViewport*)_details->parent();
     QWidget* vp = (QWidget*)_details->parent();
  //vp.validate();
  vp->repaint();
 }
}

/*protected*/ int AbstractSerialConnectionConfig::addStandardDetails(bool incAdvanced, int i)
{
 if(!isPortAdvanced())
 {
  cR->gridy = i;
  cL->gridy = i;
//    gbLayout.setConstraints(portBoxLabel, cL);
//    gbLayout.setConstraints(portBox, cR);
  gbLayout->addWidget(portBoxLabel, cL->gridy, cL->gridx);
  portBoxLabel->setVisible(true);
  gbLayout->addWidget(portBox, cR->gridy, cR->gridx);
  portBox->setVisible(true);
  i++;
 }

 if(!isBaudAdvanced())
 {
  cR->gridy = i;
  cL->gridy = i;
//    gbLayout.setConstraints(baudBoxLabel, cL);
//    gbLayout.setConstraints(baudBox, cR);
  gbLayout->addWidget(baudBoxLabel, cL->gridy, cL->gridx);
  baudBoxLabel->setVisible(true);
  gbLayout->addWidget(baudBox, cR->gridy, cR->gridx);
  baudBox->setVisible(true);
  i++;
 }
 return AbstractConnectionConfig::addStandardDetails(adapter, incAdvanced, i);
}

/*public*/ bool AbstractSerialConnectionConfig::isPortAdvanced() { return false; }
/*public*/ bool AbstractSerialConnectionConfig::isBaudAdvanced() { return true; }

//@Override
/*public*/ QString AbstractSerialConnectionConfig::getManufacturer() { return adapter->getManufacturer(); }

//@Override
/*public*/ void AbstractSerialConnectionConfig::setManufacturer(QString manufacturer)
{
 if (adapter!=NULL)
 {
  adapter->setManufacturer(manufacturer);
 }
}

//@Override
/*public*/ bool AbstractSerialConnectionConfig::getDisabled() {
    if (adapter==NULL) return true;
    return adapter->getDisabled();
}

//@Override
/*public*/ void AbstractSerialConnectionConfig::setDisabled(bool disabled) {
    if(adapter!=NULL)
        adapter->setDisabled(disabled);
}

//@Override
/*public*/ QString AbstractSerialConnectionConfig::getConnectionName() {
    if((adapter!=NULL) && (adapter->getSystemConnectionMemo()!=NULL))
        return adapter->getSystemConnectionMemo()->getUserName();
    else return name();
}

//@Override
/*public*/ void AbstractSerialConnectionConfig::dispose()
{
 if (adapter!=NULL)
 {
  adapter->dispose();
  adapter=NULL;
 }
 removeFromActionList();
}
#if 0
class ComboBoxRenderer extends JLabel
                   implements ListCellRenderer<String> {

    /**
     *
     */
    /*private*/ static final long serialVersionUID = 3617752100442828216L;

    /*public*/ ComboBoxRenderer() {
        setHorizontalAlignment(LEFT);
        setVerticalAlignment(CENTER);
    }

    /*
     * This method finds the image and text corresponding
     * to the selected value and returns the label, set up
     * to display the text and image.
     */
    @Override
    /*public*/ Component getListCellRendererComponent(
                                       JList<? extends String> list,
                                       String name,
                                       int index,
                                       boolean isSelected,
                                       boolean cellHasFocus) {

        String displayName = name.toString();
        setOpaque(index > -1);
        setForeground(Color.black);
        list.setSelectionForeground(Color.black);
        if(isSelected && index > -1){
            setBackground(list.getSelectionBackground());
        } else {
            setBackground(list.getBackground());
        }
        if(invalidPort!=NULL){
            String port = PortNameMapper.getPortFromName(displayName);
            if (port==(invalidPort)){
                list.setSelectionForeground(Color.red);
                setForeground(Color.red);
            }
        }

        setText(displayName);

        return this;
    }
}
#endif
//@SuppressWarnings("UseOfObsoleteCollectionType")
/*protected*/ /*synchronized*/ /*static*/ void AbstractSerialConnectionConfig::updateSerialPortNames(QString portName, QComboBox/*<String>*/* portCombo, QVector<QString>* portList)
{
//    for(Entry<String, SerialPortFriendlyName> en : PortNameMapper.getPortNameMap().entrySet()){
//        en.getValue().setValidPort(false);
//    }
 for (int i=0; i<portList->size(); i++)
 {
  QString commPort = portList->at(i);
//        SerialPortFriendlyName port = PortNameMapper.getPortNameMap().get(commPort);
//        if(port==NULL){
//            port = new SerialPortFriendlyName(commPort, NULL);
//            PortNameMapper.getPortNameMap().put(commPort, port);
//        }
//        port.setValidPort(true);
//        portCombo.addItem(port.getDisplayName());
  portCombo->addItem(commPort);
  if(commPort==(portName))
  {
   portCombo->setCurrentIndex(i);
  }
 }
}

//@SuppressWarnings({"unchecked", "UseOfObsoleteCollectionType"})
/*protected*/ QVector<QString>* AbstractSerialConnectionConfig::getPortNames()
{
 //reloadDriver(); // Refresh the list of communication ports
 // first, check that the comm package can be opened and ports seen
 QVector<QString>* portNameVector = new  QVector<QString>();

//    Enumeration<CommPortIdentifier> portIDs = CommPortIdentifier.getPortIdentifiers();
//    // find the names of suitable ports
//    while (portIDs.hasMoreElements()) {
//        CommPortIdentifier id = portIDs.nextElement();
//        // filter out line printers
//        if (id.getPortType() != CommPortIdentifier.PORT_PARALLEL)
//            // accumulate the names in a vector
//            portNameVector.addElement(id.getName());
//    }
 QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();
 foreach (QSerialPortInfo info, infoList)
 {
  portNameVector->append(info.portName());
 }
 return portNameVector;
}

/**
* This provides a method to return potentially meaningful names that are used
* in OS to help identify ports against Hardware.
 * @return array of friendly port names
*/
/*protected*/ QStringList AbstractSerialConnectionConfig::getPortFriendlyNames()
{
 return  QStringList();
}

/**
* This is purely here for systems that do not implement the SystemConnectionMemo
* Acela, CAN BUS, CMRI, Grapevine, QSI, Zimo & RPS and can be removed one they have been migrated
 * @return Resource bundle for action model
*/
///*protected*/ ResourceBundle getActionModelResourceBundle(){
//    return NULL;
//}

/*protected*/ /*final*/ void AbstractSerialConnectionConfig::addToActionList()
{
#if 0
    CreateButtonModel bm = InstanceManager.getDefault("CreateButtonModel");
    ResourceBundle rb = getActionModelResourceBundle();
    if (rb==NULL || bm==NULL)
        return;
    Enumeration<String> e = rb.getKeys();
    while (e.hasMoreElements()) {
        String key = e.nextElement();
        try {
            bm.addAction(key, tr(key));
        } catch (ClassNotFoundException ex) {
            log->error("Did not find class "+key);
        }
    }
#endif
}

/*protected*/ void AbstractSerialConnectionConfig::removeFromActionList()
{
#if 0
    apps.CreateButtonModel bm = jmri.InstanceManager.getDefault(apps.CreateButtonModel.class);
    ResourceBundle rb = getActionModelResourceBundle();
    if (rb==NULL || bm==NULL)
        return;
    Enumeration<String> e = rb.getKeys();
    while (e.hasMoreElements()) {
        String key = e.nextElement();
        try {
            bm.removeAction(key);
        } catch (ClassNotFoundException ex) {
            log->error("Did not find class "+key);
        }
    }
#endif
}
