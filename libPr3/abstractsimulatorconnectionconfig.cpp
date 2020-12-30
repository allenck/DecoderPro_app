#include "abstractsimulatorconnectionconfig.h"
#include <jtextfield.h>
#include "serialportadapter.h"
#include "systemconnectionmemo.h"
#include <QMessageBox>
#include <QBoxLayout>
#include <QCheckBox>
#include "gridbagconstraints.h"
#include "insets.h"
#include <QComboBox>
#include <QLabel>
#include "gridbaglayout.h"

//AbstractSimulatorConnectionConfig::AbstractSimulatorConnectionConfig(QObject *parent) :
//    AbstractConnectionConfig(parent)
//{
//}
/**
 * Abstract base class for common implementation of the Simulator ConnectionConfig
 * Currently uses the serial adapter, but this will change to the simulator adapter
 * in due course.
 *
 * @author      Kevin Dickerson   Copyright (C) 2001, 2003
 * @version	$Revision: 28389 $
 */

//
// abstract /*public*/ class AbstractSimulatorConnectionConfig extends AbstractConnectionConfig {

/**
 * Ctor for an object being created during load process
 * Currently uses the serialportadapter, but this will
 * change to a simulator port adapter in due course.
 */
/*public*/ AbstractSimulatorConnectionConfig::AbstractSimulatorConnectionConfig(SerialPortAdapter* p,QObject *parent) :
    AbstractConnectionConfig(parent)
{
    adapter = p;
    init = false;
    log = new Logger("AbstractSimulatorConnectionConfig");

}

//@Override
/*public*/ PortAdapter* AbstractSimulatorConnectionConfig::getAdapter()  { return adapter; }

/**
 * Ctor for a functional object with no prexisting adapter.
 * Expect that the subclass setInstance() will fill the adapter member.
 */
/*public*/ AbstractSimulatorConnectionConfig::AbstractSimulatorConnectionConfig(QObject *parent) :
    AbstractConnectionConfig(parent) {
    adapter = NULL;
   init = false;
   log = new Logger("AbstractSimulatorConnectionConfig");
}


/*protected*/ void AbstractSimulatorConnectionConfig::checkInitDone() {
    if (log->isDebugEnabled()) log->debug("init called for "+name());
    if (init) return;

    if(adapter->getSystemConnectionMemo()!=NULL)
    {
//        systemPrefixField.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if(!adapter.getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter.getSystemConnectionMemo().getSystemPrefix());
//                }
//            }
//        });
        connect(systemPrefixField, SIGNAL(editingFinished()), this, SLOT(On_systemPrefixField_editingFinished()));
//        systemPrefixField.addFocusListener( new FocusListener() {
//            /*public*/ void focusLost(FocusEvent e){
//                if(!adapter.getSystemConnectionMemo().setSystemPrefix(systemPrefixField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
//                    systemPrefixField.setText(adapter.getSystemConnectionMemo().getSystemPrefix());
//                }
//            }
//            /*public*/ void focusGained(FocusEvent e){ }
//        });
        connect(systemPrefixField, SIGNAL(leaveField()), this, SLOT(On_systemPrefixField_editingFinished()));

//        connectionNameField.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if(!adapter.getSystemConnectionMemo().setUserName(connectionNameField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter.getSystemConnectionMemo().getUserName());
//                }
//            }
//        });
        connect(connectionNameField, SIGNAL(editingFinished()), this, SLOT(On_connectionNameField_editingFinished()));
//        connectionNameField.addFocusListener( new FocusListener() {
//            /*public*/ void focusLost(FocusEvent e){
//                if(!adapter.getSystemConnectionMemo().setUserName(connectionNameField.getText())){
//                    JOptionPane.showMessageDialog(NULL, "Connection Name " + connectionNameField.getText() + " is already assigned");
//                    connectionNameField.setText(adapter.getSystemConnectionMemo().getUserName());
//                }
//            }
//            /*public*/ void focusGained(FocusEvent e){ }
//        });
        connect(connectionNameField, SIGNAL(leaveField()), this, SLOT(On_connectionNameField_editingFinished()));
        foreach(QString i,options.keys())
        {
            /*final*/ QString item = i;
            if(qobject_cast<QComboBox*>(options.value(i)->getComponent())!= NULL)
            {
//                ((JComboBox)options.get(i).getComponent()).addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        adapter.setOptionState(item, options.get(item).getItem());
//                    }
//                });
                QComboBox* box = (QComboBox*)options.value(i)->getComponent();
                ASCCActionListener* listener = new ASCCActionListener(item,this);
                connect(box, SIGNAL(currentIndexChanged(QString)), listener, SLOT(actionPerformed()));
            }
        }

    }
    init = true;
}
void AbstractSimulatorConnectionConfig::On_systemPrefixField_editingFinished()
{
 if(!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
//  JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"), tr("System Prefix ") + systemPrefixField->text() + " is already assigned");
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
 }
}
void AbstractSimulatorConnectionConfig::On_connectionNameField_editingFinished()
{
 if(!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text()))
 {
//  JOptionPane.showMessageDialog(NULL, "System Prefix " + systemPrefixField.getText() + " is already assigned");
  QMessageBox::warning(NULL, tr("Warning"), tr("Connection Name") + connectionNameField->text() + " is already assigned");
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
}
ASCCActionListener::ASCCActionListener(QString item, AbstractSimulatorConnectionConfig *parent)
{
    this->item = item;
    this->parent = parent;
}

void ASCCActionListener::actionPerformed(JActionEvent */*e*/)
{
    parent->adapter->setOptionState(item, parent->options.value(item)->getItem());
}

/*public*/ void AbstractSimulatorConnectionConfig::updateAdapter()
{
 foreach(QString i, options.keys())
 {
  adapter->setOptionState(i, options.value(i)->getItem());
 }

 if(!adapter->getSystemConnectionMemo()->setSystemPrefix(systemPrefixField->text().trimmed()))
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
}



/**
 * Load the adapter with an appropriate object
 * <i>unless</I> its already been set.
 */
/*abstract*/ /*protected*/ void AbstractSimulatorConnectionConfig::setInstance() {}

/**
 * Returns the port the simulator is connected to
 * which is "none";
 */
/*public*/ QString AbstractSimulatorConnectionConfig::getInfo() {
    return tr("<none>");
}

//static java.util.ResourceBundle rb =
//    java.util.ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");

/*public*/ void AbstractSimulatorConnectionConfig::loadDetails(/*final*/ JPanel* details)
{
 _details = details;
 setInstance();
 if(!init)
 {
  QStringList optionsAvailable = adapter->getOptions();
  options =  QHash<QString, Option*>();
  foreach(QString i, optionsAvailable)
  {
   QComboBox* opt = new QComboBox();//(adapter.getOptionChoices(i));
   opt->addItems(adapter->getOptionChoices(i));
   opt->setCurrentIndex(opt->findText(adapter->getOptionState(i)));
   // check that it worked
   if (adapter->getOptionState(i)!=(opt->currentText()))
   {
    // no, set 1st option choice
    opt->setCurrentIndex(0);
    adapter->setOptionState(i, opt->currentText());
    log->warn(tr("Loading found invalid value for option %1, found \"%2\", setting to \"%3\"").arg(i).arg( adapter->getOptionState(i)).arg(opt->currentText()));
   }
   options.insert(i, new Option(adapter->getOptionDisplayName(i), opt, adapter->isOptionAdvanced(i)));
  }
 }

 if(adapter->getSystemConnectionMemo()!=NULL)
 {
  systemPrefixField->setText(adapter->getSystemConnectionMemo()->getSystemPrefix());
  connectionNameField->setText(adapter->getSystemConnectionMemo()->getUserName());
 }
 NUMOPTIONS = NUMOPTIONS+options.size();
 QFont f = showAdvanced->font();
 f. setPointSizeF(9.0);
 showAdvanced->setFont(/*showAdvanced.getFont().deriveFont(9f)*/ f);
 //showAdvanced->setStyleSheet("QCheckBox { color: blue; }");
 showAdvanced->setStyleSheet("QCheckBox { color: blue; background-color: lightgray;} QCheckBox::hover { background-color: lightpink; }");
//    showAdvanced.addItemListener(
//        new ItemListener() {
//            /*public*/ void itemStateChanged(ItemEvent e){
//                showAdvancedItems();
//            }
//        });
 connect(showAdvanced, SIGNAL(toggled(bool)), this, SLOT(showAdvancedItems()));
 showAdvancedItems();
 init = false;		// need to reload action listeners
 checkInitDone();
}

/*protected*/ void AbstractSimulatorConnectionConfig::showAdvancedItems()
{
 //_details.removeAll();
// QObjectList ol = _details->children();
// foreach(QObject* o, ol)
// {
//  if(qobject_cast<QWidget*>(o) != NULL)
//  {
//   _details->layout()->removeWidget((QWidget*)o);
//   ((QWidget*)o)->hide();
//  }
//  else
//   o->deleteLater();
// }
    if(_details->layout() != NULL)
    {
     QLayoutItem *child;
     while ((child = _details->layout()->takeAt(0)) != 0)
     {
      child->widget()->hide();
      delete child;
     }
    }cL->anchor = GridBagConstraints::WEST;
 cL->insets = new Insets(2, 5, 0, 5);
 cR->insets = new Insets(2, 0, 0, 5);
 cR->anchor = GridBagConstraints::WEST;
 cR->gridx = 1;
 cL->gridx = 0;

 if(_details->layout() == NULL)
  _details->setLayout(gbLayout);
 else
  if(qobject_cast<GridBagLayout*>(_details->layout()) != NULL)
    gbLayout = (GridBagLayout*)_details->layout();

 int i = 0;

 bool incAdvancedOptions=false;
 foreach(QString item, options.keys())
 {
  if(options.value(item)->isAdvanced())
   incAdvancedOptions=true;
 }

 i = addStandardDetails(adapter, incAdvancedOptions, i);

 if (showAdvanced->isChecked())
 {
  foreach(QString item, options.keys())
  {
   if(options.value(item)->isAdvanced())
   {
    cR->gridy = i;
    cL->gridy = i;
//                gbLayout.setConstraints(options.get(item).getLabel(), cL);
//                gbLayout.setConstraints(options.get(item).getComponent(), cR);
    gbLayout->addWidget(options.value(item)->getLabel(),*cL);
    options.value(item)->getLabel()->setVisible(true);
    gbLayout->addWidget(options.value(item)->getComponent(),*cR);
    options.value(item)->getComponent()->setVisible(true);
    i++;
   }
  }
 }
 cL->gridwidth=2;
 foreach(QWidget* item, *additionalItems)
 {
  cL->gridy = i;
  //gbLayout.setConstraints(item, cL);
  gbLayout->addWidget(item,*cL);
  item->setVisible(true);
  i++;
 }
 cL->gridwidth=1;
//    if (_details->getParent()!=NULL && _details->getParent() instanceof javax.swing.JViewport){
//        javax.swing.JViewport vp = (javax.swing.JViewport)_details->getParent();
//        vp.validate();
//        vp.repaint();
//    }
}

/*public*/ QString AbstractSimulatorConnectionConfig::getManufacturer() { return adapter->getManufacturer(); }
/*public*/ void AbstractSimulatorConnectionConfig::setManufacturer(QString manufacturer)
{
 setInstance();
 adapter->setManufacturer(manufacturer);
}

/*public*/ QString AbstractSimulatorConnectionConfig::getConnectionName() {
    if(adapter->getSystemConnectionMemo()!=NULL)
        return adapter->getSystemConnectionMemo()->getUserName();
    else return NULL;
}

/*public*/ bool AbstractSimulatorConnectionConfig::getDisabled() {
    if (adapter==NULL) return true;
    return adapter->getDisabled();
}
/*public*/ void AbstractSimulatorConnectionConfig::setDisabled(bool disabled) { adapter->setDisabled(disabled); }

/*public*/ void AbstractSimulatorConnectionConfig::dispose(){
    if (adapter!=NULL){
        adapter->dispose();
        adapter=NULL;
    }
    AbstractConnectionConfig::dispose();
}
