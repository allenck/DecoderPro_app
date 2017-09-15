#include "dccaddresspanel.h"
#include <QHBoxLayout>
#include "enumvariablevalue.h"
#include "variabletablemodel.h"
#include "jtextfield.h"
#include "longaddrvariablevalue.h"
#include "shortaddrvariablevalue.h"
#include <QIntValidator>

//DccAddressPanel::DccAddressPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
#if 0 // replaced by adding propertyChange
class DccNews : public PropertyChangeListener
{
public:
    DccNews(PropertyChangeEvent*, DccAddressPanel* dccAddressPanel)
    {
     this->dccAddressPanel = dccAddressPanel;
    }
private:
    DccAddressPanel* dccAddressPanel;
public slots:
    void propertyChange(PropertyChangeEvent *e)
    {
     dccAddressPanel->updateDccAddress();
    }
};
#endif

/**
 * Provide a graphical representation of the DCC address, either long or short
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2012
 * @version			$Revision: 22092 $
 */
///*public*/ class DccAddressPanel extends JPanel {


/**
 * Ctor using default label for the address.
 * @param mod The current table of variables, used to locate the
 * status information needed.
 */
///*public*/ DccAddressPanel::DccAddressPanel(VariableTableModel* mod, QWidget *parent) : QWidget(parent)
//{
// //this(mod, ResourceBundle.getBundle("jmri.jmrit.symbolicprog.SymbolicProgBundle").getString("TextDccAddress"));
// val = new QLineEdit();
// val->setMaxLength(6);
// variableModel = mod;

// primaryAddr = NULL;
// extendAddr = NULL;
// addMode = NULL;
// log = new Logger("DccAddressPanel");

//}
/*public*/ DccAddressPanel::DccAddressPanel(VariableTableModel* mod, QString label, QWidget *parent) : QWidget(parent)
{
 primaryAddr = NULL;
 extendAddr = NULL;
 addMode = NULL;
 log = new Logger("DccAddressPanel");
 log->setDebugEnabled(true);
 variableModel = mod;
 val = new JTextField(6);
 QVBoxLayout* vLayout = new QVBoxLayout();
 setLayout(vLayout);

 // arrange for the field to be updated when any of the variables change
 //PropertyChangeListener* dccNews = new PropertyChangeListener();
 //connect(dccNews, SIGNAL(signalPropertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//    {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) { updateDccAddress(); }
//        };

 // connect to variables
 primaryAddr = variableModel->findVar("Short Address");
 if (primaryAddr==NULL) log->debug("DCC Address monitor did not find a Short Address variable");
 else
 {
  primaryAddr->addPropertyChangeListener(/*dccNews*/(PropertyChangeListener*)this);
  if(qobject_cast<DecVariableValue*>(primaryAddr) != NULL)
  {
   DecVariableValue* decVar = (DecVariableValue*)primaryAddr;
   connect(decVar->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  else
  {
   connect(primaryAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }

 extendAddr = variableModel->findVar("Long Address");
 if (extendAddr==NULL) log->debug("DCC Address monitor did not find a Long Address variable");
 else
 {
  extendAddr->addPropertyChangeListener(/*dccNews*/(PropertyChangeListener*)this);
  connect(extendAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 addMode = (EnumVariableValue*)variableModel->findVar("Address Format");
 if (addMode==NULL) log->debug("DCC Address monitor didnt find an Address Format variable");
 else
 {
  addMode->addPropertyChangeListener(/*dccNews*/(PropertyChangeListener*)this);
  connect(addMode->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 // show the selection
 if (addMode != NULL)
 {
  vLayout->addWidget(addMode->getNewRep("radiobuttons"));
  connect(addMode, SIGNAL(valueChanged(int)), this, SLOT(actionPerformed()));
 }

 // show address field
 vLayout->addWidget(new QLabel(label, this));
 val->setToolTip(tr("This field shows the DCC address currently in use. CV1 provides the short address; CV17 & 18 provide the long address"));
 vLayout->addWidget(val);

 new MyDccAddressVarHandler1(primaryAddr, extendAddr, addMode, val);

 // start listening for changes to this value
// val->addActionListener(new ActionListener());
//    {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (addMode == NULL || extendAddr == NULL || !addMode.getValueString()==("1")) {
//                    if (primaryAddr!=NULL) {
//                        // short address mode
//                        primaryAddr.updatedTextField();
//                        val.setBackground(primaryAddr.getCommonRep().getBackground());
//                        if (log->isDebugEnabled()) log->debug("set color: "+primaryAddr.getCommonRep().getBackground());
//                    }
//                }int
//                else {
//                    // long address
//                    extendAddr.updatedTextField();
//                    val.setBackground(extendAddr.getCommonRep().getBackground());
//                    if (log->isDebugEnabled()) log->debug("set color: "+extendAddr.getCommonRep().getBackground());
//                }
//            }
//        });
 connect(val, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));

//    val.addFocusListener(new FocusListener() {
//            /*public*/ void focusGained(FocusEvent e) {
//                if (log->isDebugEnabled()) log->debug("focusGained");
//                enterField();
//            }
//            /*public*/ void focusLost(FocusEvent e) {
//                if (log->isDebugEnabled()) log->debug("focusLost");
//                exitField();
//            }
//        });
 connect(val, SIGNAL(enterField()), this, SLOT(focusGained()));
 connect(val, SIGNAL(leaveField()), this, SLOT(focusLost()));
}
void DccAddressPanel::focusGained()
{
 if (log->isDebugEnabled()) log->debug("focusGained");
 enterField();
}
void DccAddressPanel::focusLost()
{
 if (log->isDebugEnabled()) log->debug("focusLost");
  exitField();
}

//void DccAddressPanel::actionPerformed(ActionEvent* /*e*/)
void DccAddressPanel::actionPerformed()
{
 new MyDccAddressVarHandler2(primaryAddr, extendAddr, addMode, val);
}


/**
 * Handle focus entering the address field by recording the contents.
 */
void DccAddressPanel::enterField()
{
    oldContents = val->text();
}

/**
 * Handle focus leaving the address field by checking to see if the
 * contents changed.  We do this because we want to record that change
 * even if it hasn't been "entered" via return key et al.
 */
void DccAddressPanel::exitField()
{
 if (oldContents!=(val->text()))
 {
  new MyDccAddressVarHandler2(primaryAddr, extendAddr,addMode, val);
 }
}
void DccAddressPanel::valueChanged()
{
 int newVal = val->text().toInt();
 if(primaryAddr != NULL)
 {
   ((ShortAddrVariableValue*)primaryAddr)->setValue(newVal);
 }
 else if(extendAddr != NULL)
 {
   ((LongAddrVariableValue*)extendAddr)->setValue(newVal);
 }
 else return; // ACK add in case all are NULL!
 updateDccAddress();
}

/**
 * Handle a (possible) update to the active DCC address, either because
 * the state changed or the address mode changed.  Note that value changes
 * of the active address are directly reflected, so we don't have to do
 * anything on those, but we still go ahead and update the state color.
 */
void DccAddressPanel::updateDccAddress()
{
 if (log->isDebugEnabled())
  log->debug("updateDccAddress: short "+(primaryAddr==NULL?"<NULL>":primaryAddr->getValueString())+
                  " long "+(extendAddr==NULL?"<NULL>":extendAddr->getValueString())+
                  " mode "+(addMode==NULL?"<NULL>":addMode->getValueString()));
 new MyDccAddressVarHandler1(primaryAddr, extendAddr, addMode, val);
}



void DccAddressPanel::propertyChange(PropertyChangeEvent *e)
{
 updateDccAddress();
}
void MyDccAddressVarHandler1::doPrimary()
{
 // short address commonRep will be JTextField* if variable, JLabel if constant
 JTextField* f;

 //if (primaryAddr.getCommonRep() instanceof QLineEdit*) f = (QLineEdit*)primaryAddr.getCommonRep();
 if(qobject_cast<JTextField*>(((ShortAddrVariableValue*)primaryAddr)->getCommonRep())!= NULL)
 {
  f = (JTextField*)((ShortAddrVariableValue*)primaryAddr)->getCommonRep();
  f->setValidator(new QIntValidator(0,255));
 }
 else
 {
  f = new JTextField();
  f->setText(((QLabel*)((ShortAddrVariableValue*)primaryAddr)->getCommonRep())->text());
 }
 val->setText(f->text());
 val->setBackground(((JTextField*)((ShortAddrVariableValue*)primaryAddr)->getCommonRep())->getBackground());
 val->setDocument( f->getDocument());
}
void MyDccAddressVarHandler1::doExtended()
{
 // long address commonRep will be JTextField* if variable, JLabel if constant
 JTextField* f;
 //if (extendAddr.getCommonRep() instanceof QLineEdit*) f = (QLineEdit*)extendAddr.getCommonRep();
 if(qobject_cast<JTextField*>(((LongAddrVariableValue*)extendAddr)->getCommonRep())!=NULL)
 {
  f = (JTextField*)((LongAddrVariableValue*)extendAddr)->getCommonRep();
  f->setValidator(new QIntValidator(((LongAddrVariableValue*)extendAddr)->_minVal,((LongAddrVariableValue*)extendAddr)->_maxVal));
 }
 else
 {
  f = new JTextField();
  f->setText(((QLabel*)((LongAddrVariableValue*)extendAddr)->getCommonRep())->text());
 }
 val->setText(f->text());
 val->setBackground(( (JTextField*)((LongAddrVariableValue*)extendAddr)->getCommonRep())->getBackground());
 val->setDocument( f->getDocument());
}
void MyDccAddressVarHandler2::doPrimary()
{
 // short address mode
 primaryAddr->updatedTextField();
 val->setBackground(((JTextField*)primaryAddr->getCommonRep())->getBackground());
 if (log->isDebugEnabled()) log->debug("set color: "+((JTextField*)primaryAddr->getCommonRep())->styleSheet());
}
void MyDccAddressVarHandler2::doExtended()
{
 // long address
 extendAddr->updatedTextField();
 val->setBackground(((JTextField*)extendAddr->getCommonRep())->getBackground());
 if (log->isDebugEnabled()) log->debug("set color: "+((JTextField*)extendAddr->getCommonRep())->styleSheet());
}
