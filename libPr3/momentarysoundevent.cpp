#include "momentarysoundevent.h"
#include <QPushButton>
#include <QDomElement>
#include "logger.h"
#include "trigger.h"
#include "buttontrigger.h"
#include <QMetaEnum>
#include <QMouseEvent>

//MomentarySoundEvent::MomentarySoundEvent(QObject *parent) :
//  SoundEvent(parent)
//{
//}

///*public*/ class MomentarySoundEvent extends SoundEvent implements PropertyChangeListener {



/*public*/MomentarySoundEvent:: MomentarySoundEvent(QObject *parent) :
SoundEvent("", "", parent)
{
 //this(null, null);
 bt = NULL;
 log = new Logger("MomentarySoundEvent");
}

/*public*/ MomentarySoundEvent::MomentarySoundEvent(QString n,QObject *parent) :
SoundEvent(n, n, parent) {
    //this(n, n);
 bt = NULL;
 log = new Logger("MomentarySoundEvent");
}

/*public*/ MomentarySoundEvent::MomentarySoundEvent(QString n, QString bl,QObject *parent) :
SoundEvent(n, bl, parent) {
    //super(n, bl);
 bt = NULL;
    button = NULL;
    log = new Logger("MomentarySoundEvent");
}

//@Override
/*public*/ bool MomentarySoundEvent::hasButton() {
    if ((buttontype == NONE) || (buttontype == ENGINE) || (button == NULL)) {
        return (false);
    } else {
        return (true);
    }
}

/*public*/ void MomentarySoundEvent::setButton(MSButton* b) {
    button = b;
}

//@Override
/*public*/ QAbstractButton* MomentarySoundEvent::getButton() {
    return (QAbstractButton*)button;
}

//@Override
/*public*/ void MomentarySoundEvent::setButtonLabel(QString bl) {
    button->setText(bl);
}

//@Override
/*public*/ QString MomentarySoundEvent::getButtonLabel() {
    return (button->text());
}

//@Override
/*protected*/ ButtonTrigger* MomentarySoundEvent::setupButtonAction(QDomElement te) {
    bt = new ButtonTrigger(te.attribute("name"));
    button_trigger_list.insert(bt->getName(), bt);
    const QMetaObject &mo = SoundEvent::staticMetaObject;
    int index = mo.indexOfEnumerator("ButtonType");
    QMetaEnum metaEnum = mo.enumerator(index);

    log->debug("new ButtonTrigger " + bt->getName() + " type " +metaEnum.valueToKey( buttontype));
    button->addMouseListener(bt);
    return (bt);  // cast OK since we just instantiated it up above.
}

//@Override
/*public*/ QDomElement MomentarySoundEvent::getXml() {
    //Element me = new Element("SoundEvent");
 QDomElement me = QDomElement();
 me.setTagName("SoundEvent");
    me.setAttribute("name", name);
    me.setAttribute("label", me.text());
    foreach (Trigger* t, trigger_list.values()) {
        me.appendChild(t->getXml());
    }

    return (me);
}

//@Override
/*public*/ void MomentarySoundEvent::setXml(QDomElement el) {
 this->setXml(el, NULL);
}

//@Override
/*public*/ void MomentarySoundEvent::setXml(QDomElement el, VSDFile* vf) {

    // Create the button first (put this in constructor?)
    button = new MSButton();
    button->setVisible(true);

    // Handle common stuff.
    SoundEvent::setXml(el, vf);

    // We know it's momentary, or this class wouldn't have been constructed.
    button->setText(el.attribute("label"));

    /*
     for (ButtonTrigger bt : button_trigger_list.values()) {
     log.debug("Button Trigger: " + bt.getName());
     if (bt.getTarget() != null)
     log.debug("  Target: " + bt.getTarget().getName());
     else
     log.debug("  Target: null");
     if (bt.getTargetAction() != null)
     log.debug("  Action: " + bt.getTargetAction().toString());
     else
     log.debug("  Target Action: null");

     }
     */

    /*
     MouseListener [] listeners = button.getListeners(MouseListener.class);
     for (MouseListener l : listeners) {
     log.debug("Listener: " + l.toString());
     }
     */
}  // end setXml()
MSButton::MSButton()
{
 bt = NULL;
}
void MSButton::addMouseListener(ButtonTrigger* bt)
{
 Q_ASSERT(bt != NULL);
 this->bt =bt;
}
void MSButton::mousePressEvent(QMouseEvent *e)
{
 if(bt == NULL) return;
 if(e->buttons()&& Qt::LeftButton != 0)
 {
  bt->mousePressed(e);
  bt->mouseDown();
 }
}
void MSButton::mouseReleaseEvent(QMouseEvent *e)
{
 if(bt == NULL) return;
 bt->mouseReleased(e);
}

void MomentarySoundEvent::addButtonMouseHandler(ButtonTrigger* bt)
{
 this->bt = bt;
 button->addMouseListener(bt);
}
