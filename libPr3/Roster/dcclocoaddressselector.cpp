#include "dcclocoaddressselector.h"
#include "instancemanager.h"
#include "lnthrottlemanager.h"
#include "locoaddress.h"
#include <QHBoxLayout>

//DccAddressSelector::DccAddressSelector(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Tool for selecting short/long address for DCC throttles.
 *
 * This is made more complex because we want it to appear easier.
 * Some DCC systems allow addresses like 112 to be either long (extended)
 * or short; others default to one or the other.
 * <P>
 * When locked (the default), the short/long selection
 * is forced to stay in synch with what's available from the
 * current ThrottleManager.  If unlocked, this can differ if
 * it's been explicity specified via the GUI  (e.g. you can call
 * 63 a long address even if the DCC system can't actually do it
 * right now). This is useful in decoder programming, for example,
 * where you might be configuring a loco to run somewhere else.
 *
 * @author     Bob Jacobsen   Copyright (C) 2005
 * @version    $Revision: 21286 $
 */
///*public*/ class DccLocoAddressSelector extends JPanel
//{

/*public*/ DccLocoAddressSelector::DccLocoAddressSelector( QWidget *parent) : QWidget(parent)
{
 //super();
 init();
 ThrottleManager* throttleManager = (ThrottleManager*) InstanceManager::throttleManagerInstance();
 if ((throttleManager !=NULL)
        && !throttleManager->addressTypeUnique())
 {
  configureBox(throttleManager->getAddressTypes());
 }
 else
 {
  configureBox( QStringList() <<"DCC Short" << "DCC Long");
 }
}
/*public*/ DccLocoAddressSelector::DccLocoAddressSelector(QComboBox* box, JTextField* text, QWidget *parent)
    : QWidget(parent)
{
    //super();
 init();
    this->box = box;
    this->text = text;
    locked = true;

    boxUsed = false;
    textUsed = false;
    panelUsed = false;

    if ((InstanceManager::throttleManagerInstance() !=NULL)
            && !((LnThrottleManager*)InstanceManager::throttleManagerInstance())->addressTypeUnique())
    {
     configureBox(((LnThrottleManager*)InstanceManager::throttleManagerInstance())->getAddressTypes());
    }
    else
    {
     QStringList list;
     list << "DCC Short" << "DCC Long";
      configureBox(list);
    }
}

/*public*/ DccLocoAddressSelector::DccLocoAddressSelector(QStringList protocols, QWidget* parent) : QWidget(parent){
    //super();
 init();
 if ((InstanceManager::getNullableDefault("ThrottleManager") != nullptr)
                 && !InstanceManager::throttleManagerInstance()->addressTypeUnique())
 {
     configureBox(InstanceManager::throttleManagerInstance()->getAddressTypes());
 } else {
     configureBox(
//             QStringList() << LocoAddress::Protocol::DCC_SHORT.getPeopleName()
//                 << LocoAddress::Protocol::DCC_LONG.getPeopleName());
        QStringList() << locoAddress::getPeopleName(locoAddress::Protocol::DCC_SHORT)
        << locoAddress::getPeopleName(locoAddress::Protocol::DCC_LONG));
 }
}

void DccLocoAddressSelector::init()
{
 box = NULL;
 text = NULL;
 boxUsed = false;
 textUsed = false;
 panelUsed = false;
 varFontSize = false;
 log = new Logger("DccLocoAddressSelector");
}

void DccLocoAddressSelector::configureBox(QStringList protocols)
{
 if(box == NULL)
  box= new QComboBox;
 box->addItems(protocols);
 box->setCurrentIndex(0);
 if(text == NULL)
  text = new JTextField();
 text->setMaxLength(4);
 text->setToolTip(tr("Enter the numeric address here"));
 box->setToolTip(tr("Select the type of address here"));
}

/*public*/ void DccLocoAddressSelector::setLocked(bool l) {
    locked = l;
}
/*public*/ bool DccLocoAddressSelector::getLocked(bool l) { return locked; }

/*
 * Get the currently selected DCC address.
 * <P>
 * This is the primary output of this class.
 * @return DccLocoAddress object containing GUI choices, or NULL if no entries in GUI
 */
/*public*/ DccLocoAddress* DccLocoAddressSelector::getAddress()
{
 // no object if no address
 QString t= text->text();
 if (t ==("")) return NULL;

 // ask the Throttle Manager to handle this!
 locoAddress::Protocol protocol;
 if (InstanceManager::getNullableDefault("ThrottleManager") != nullptr)
 {
  protocol = InstanceManager::throttleManagerInstance()->getProtocolFromString( box->currentText());
  return (DccLocoAddress*) InstanceManager::throttleManagerInstance()->getAddress(text->text(), protocol);
 }
 // nothing, construct a default
 int num = text->text().toInt();
 protocol = locoAddress::DCC_SHORT;
 return new DccLocoAddress(num,protocol);
}

/*public*/ void DccLocoAddressSelector::setAddress(DccLocoAddress* a)
{
 if (a!=NULL)
 {
//        if (a instanceof jmri.jmrix.openlcb.OpenLcbLocoAddress) {
//            // now special case, should be refactored
//            jmri.jmrix.openlcb.OpenLcbLocoAddress oa = (jmri.jmrix.openlcb.OpenLcbLocoAddress) a;
//            text.setText(oa.getNode().toString());
//            box.setSelectedItem(jmri.LocoAddress.Protocol.OPENLCB.getPeopleName());
//        } else
  {
   text->setText(QString::number(a->getNumber()));
   if(InstanceManager::throttleManagerInstance()!=NULL)
   {
    QString newText = ((LnThrottleManager*)InstanceManager::throttleManagerInstance())->getAddressTypeString(a->getProtocol());
    box->setCurrentIndex(box->findText(newText));
   }
  }
 }
}

/*public*/ void DccLocoAddressSelector::setVariableSize(bool s) { varFontSize = s; }
bool varFontSize = false;

/*
 * Put back to original state, clearing GUI
 */

/*public*/ void DccLocoAddressSelector::reset()
{
    box->setCurrentIndex(0);
    text->setText("");
}

/* Get a JPanel containing the combined selector.
 *
 * <P>
 * Because Swing only allows a component to be inserted in one
 * container, this can only be done once
 */
/*public*/ QWidget* DccLocoAddressSelector::getCombinedJPanel()
{
 if (panelUsed) {
        log->error("getCombinedPanel invoked after panel already requested");
        return NULL;
    }
    if (textUsed) {
        log->error("getCombinedPanel invoked after text already requested");
        return NULL;
    }
    if (boxUsed) {
        log->error("getCombinedPanel invoked after text already requested");
        return NULL;
    }
    panelUsed = true;

    if (varFontSize) text->setFont( QFont("", QFont::Normal, 32));

    QWidget* p = new QWidget();
    QHBoxLayout* pLayout;
    p->setLayout(pLayout = new QHBoxLayout);//(p, BoxLayout.X_AXIS));
    pLayout->addWidget(text);
    if (!locked ||
          ( (InstanceManager::throttleManagerInstance() !=NULL)
                && !InstanceManager::throttleManagerInstance()->addressTypeUnique()
          )
       )
        pLayout->addWidget(box);

//     pLayout->addWidgetComponentListener(
//             new ComponentAdapter()
//     {
//         /*public*/ void componentResized(ComponentEvent e)
//         {
//             changeFontSizes();
//         }
//     });

    return p;
}

/** The longest 4 character string. Used for resizing. */
/*private*/ /*static*/ /*final*/ QString DccLocoAddressSelector::LONGEST_STRING = "MMMM";

/**
 * A resizing has occurred, so determine the optimum font size
 * for the localAddressField.
 */
/*private*/ void DccLocoAddressSelector::changeFontSizes()
{
#if 0
 if (!varFontSize) return;
 double fieldWidth = text->getSize().width();
 int stringWidth = text->fontMetrics(/*text->getFont()*/).
                      stringWidth(LONGEST_STRING)+8;
    int fontSize = text.getFont().getSize();
    if (stringWidth > fieldWidth) // component has shrunk.
    {
        while ( (stringWidth > fieldWidth) && (fontSize>12) )
        {
            fontSize -= 2;
            Font f = new Font("", Font.PLAIN, fontSize);
            text.setFont(f);
            stringWidth = text.getFontMetrics(text.getFont()).
                          stringWidth(LONGEST_STRING)+8;
        }
    }
    else // component has grown
    {
        while ( (fieldWidth - stringWidth > 10) && (fontSize<48) )
        {
            fontSize += 2;
            Font f = new Font("", Font.PLAIN, fontSize);
            text.setFont(f);
            stringWidth = text.getFontMetrics(text.getFont()).
                          stringWidth(LONGEST_STRING)+8;
        }
    }
#endif
}

/*
 * Provide a common setEnable call for the GUI components in the
 * selector
 */
/*public*/ void DccLocoAddressSelector::setEnabled(bool e) {
    text->setReadOnly(!e);
    text->setEnabled(e);
    box->setEnabled(e);
    if (e) {
        text->setToolTip(tr("Enter the numeric address here"));
        box->setToolTip(tr("Select the type of address here"));
   } else {
        text->setToolTip(tr("This is the current numeric address; you can't update it here"));
        box->setToolTip(tr("This is the current address type; you can't update it here"));
   }
}

/*public*/ void DccLocoAddressSelector::setEnabledProtocol(bool e) {
    box->setEnabled(e);
    if(e)
        box->setToolTip(tr("Select the type of address here"));
    else
        box->setToolTip(tr("This is the current address type; you can't update it here"));
}

/*
 * Get the text field for entering the number as a separate
 * component.
 * <P>
 * Because Swing only allows a component to be inserted in one
 * container, this can only be done once
 */
/*public*/ JTextField* DccLocoAddressSelector::getTextField() {
    if (textUsed) {
        reportError("getTextField invoked after text already requested");
        return NULL;
    }
    textUsed = true;
    return text;
}

void DccLocoAddressSelector::reportError(QString msg) {
    log->error(msg,  ("traceback"));
}

/*
 * Get the selector box for picking long/short as a separate
 * component.
 * Because Swing only allows a component to be inserted in one
 * container, this can only be done once
 */
/*public*/ QComboBox* DccLocoAddressSelector::getSelector() {
    if (boxUsed) {
        log->error("getSelector invoked after text already requested");
        return NULL;
    }
    boxUsed = true;
    return box;
}

