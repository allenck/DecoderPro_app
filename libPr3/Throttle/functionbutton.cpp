#include "functionbutton.h"
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QtXml>
#include "fileutil.h"
#include "functionlistener.h"
#include <QMouseEvent>
#include "functionpanel.h"
#include <QFont>
#include "fileutil.h"
#include "namedicon.h"
#include "functionbuttonpropertyeditor.h"

//FunctionButton::FunctionButton(QWidget *parent) :
//    JToggleButton(parent)
//{

//}
/**
 * A JButton to activate functions on the decoder. FunctionButtons
 * have a right-click popup menu with several configuration options:
 * <ul>
 * <li> Set the text
 * <li> Set the locking state
 * <li> Set visibility
 * <li> Set Font
 * <li> Set function number identity
 * </ul>
 *
 * @author Glen Oberhauser
 * @author Bob Jacobsen   Copyright 2008
 */
///*public*/ class FunctionButton extends JToggleButton implements ActionListener
//{
void FunctionButton::init()
{
 listeners = QList<FunctionListener*>();
 isLockable = true;
 isDisplayed = true;
 dirty = false;
 _isImageOK = false;
 _isSelectedImageOK = false;
 isOn = true;
 log = new Logger("FunctionButton");
 log->setDebugEnabled(true);
 unSelectedIcon = NULL;
 selectedIcon = NULL;
 setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid pink; }");
}


 /*static*/ int FunctionButton::BUT_HGHT = 30;
 /*static*/ int FunctionButton::BUT_WDTH = 56;
 /*final static*/ int FunctionButton::BUT_IMG_SIZE = 45;



 /*public*/ /*static*/ int FunctionButton::getButtonHeight() { return BUT_HGHT; }
 /*public*/ /*static*/ int FunctionButton::getButtonWidth() { return BUT_WDTH; }

/**
 * Construct the FunctionButton::
 */
/*public*/ FunctionButton::FunctionButton(QWidget *parent) :
        JToggleButton(parent)
{
 init();
 QPushButton* sample = new QPushButton(" Light ");
 BUT_HGHT = qMax(sample->sizeHint().height(), FunctionButton::BUT_HGHT);
 BUT_WDTH = qMax(sample->sizeHint().width(), FunctionButton::BUT_WDTH);
 popup = new QMenu();

 QAction* propertiesItem = new QAction(tr("Properties"),this);
 //propertiesItem.addActionListener(this);
 connect(propertiesItem, SIGNAL(triggered(bool)), this, SLOT(popactionPerformed()));
 popup->addAction(propertiesItem);

    //Add listener to components that can bring up popup menus.
//    MouseListener popupListener = new PopupListener();
//    addMouseListener(popupListener);
 setFont( QFont("Monospace", 8));
//    setMargin(new Insets(2,2,2,2));
//    setRolloverEnabled(false);
 updateLnF();
}
#if 1
/**
 * Set the function number this button will operate
 * @param id An integer from 0 to 28.
 */
/*public*/ void FunctionButton::setIdentity(int id)
{
 this->identity = id;
}

/**
 * Get the function number this button operates
 * @return An integer from 0 to 28.
 */
/*public*/ int FunctionButton::getIdentity()
{
 return identity;
}

/**
 * Set the keycode that this button should respond to.
 * <P>
 * Later, when a key is being processed, checkKeyCode
 * will determine if there's a match between the key that
 * was pressed and the key for this button
 */
/*public*/ void FunctionButton::setKeyCode(int key)
{
 actionKey = key;
}


/**
 * Check to see whether a particular KeyCode corresponds
 * to this function button.
 * @return true if the button should respond to this key
 */
/*public*/ bool FunctionButton::checkKeyCode(int keycode)
{
 return keycode == actionKey;
}

/**
 * Set the state of the function button. Does NOT
 * notify any listeners
 * @param isOn True if the function should be active.
 */
/*public*/ void FunctionButton::setState(bool isOn)
{
    this->isOn = isOn;
    this->setSelected(isOn);
    if(isOn && selectedIcon != NULL)
      setSelectedIcon(selectedIcon);
    else
    if(!isOn && unSelectedIcon != NULL)
      setSelectedIcon(unSelectedIcon);
    else
      setIcon(QIcon());
}

/**
 * get the state of the function
 * @return true if the function is active.
 */
/*public*/ bool FunctionButton::getState()
{
    return isOn;
}

/**
 * Set the locking state of the button
 * @param isLockable True if the a clicking and releasing the button
 * changes the function state. False if the state is changed
 * back when the button is released
 */
/*public*/ void FunctionButton::setIsLockable(bool isLockable)
{
 this->isLockable = isLockable;
 if(isDirty())
 {
  // Changes in this parameter should only be sent to the
  // listeners if the dirty bit is set.
//    for (int i=0; i<listeners.size();i++)
//        listeners.at(i)->notifyFunctionLockableChanged(identity, isLockable);
  emit notifyFunctionLockableChanged(identity, isLockable);
 }
}

/**
 * Get the locking state of the function
 * @return True if the a clicking and releasing the button
 * changes the function state. False if the state is changed
 * back when the button is released
 */
/*public*/ bool FunctionButton::getIsLockable()
{
    return isLockable;
}

/**
 * Set the display state of the button
 * @param displayed True if the button exists
 * False if the button has been removed by the user
 */
/*public*/ void FunctionButton::setDisplay(bool displayed)
{
    this->isDisplayed = displayed;
}

/**
 * Get the display state of the button
 * @return True if the button exists
 * False if the button has been removed by the user
 */
/*public*/ bool FunctionButton::getDisplay()
{
    return isDisplayed;
}

/**
 * True when function button has been modified by user.
 *
 */
/*public*/ void FunctionButton::setDirty(bool dirty){
    this->dirty = dirty;
}

/**
 *
 * @return true when function button has been modified by user.
 */
/*public*/ bool FunctionButton::isDirty(){
    return dirty;
}

/*public*/ QString FunctionButton::getButtonLabel() {
    return buttonLabel;
}

/*public*/ void FunctionButton::setButtonLabel(QString label) {
    buttonLabel = label;
}

/*public*/ void FunctionButton::setText(QString s) {
    if (s != NULL )	{
        buttonLabel = s;
        if (_isImageOK) {
            setToolTip(buttonLabel);
            QPushButton::setText(NULL);
        }
        else
            QPushButton::setText(s);
        return;
    }
    QPushButton::setText(NULL);
    if (buttonLabel != NULL) {
        setToolTip(buttonLabel);
        return;
    }
}

/**
 * Decide if it should show the label or an image with text as tooltip
 * Button UI updated according to above result.
 */
/*public*/ void FunctionButton::updateLnF()
{
 if (isImageOK() )
 { // adjust button for image
//        setBorderPainted(false);
//        setContentAreaFilled(false);
  setText(NULL);
  resize(FunctionButton::BUT_IMG_SIZE, FunctionButton::BUT_IMG_SIZE);
 }
 else // adjust button for text
 {
//        setBorderPainted(true);
//        setContentAreaFilled(true);
  setText(getButtonLabel());
  if (getButtonLabel() != "")
  {
            //int butWidth = getFontMetrics(font()).stringWidth(getButtonLabel());
   QFontMetrics fm(font());
   int butWidth = fm.width(getButtonLabel());
   butWidth = butWidth + 20; // pad out the width a bit
   if (butWidth < FunctionButton::BUT_WDTH)
    butWidth = FunctionButton::BUT_WDTH;
   resize(butWidth, FunctionButton::BUT_HGHT);
  }
  else
   resize(BUT_WDTH,BUT_HGHT);
 }
}

/**
 * Handle the selection from the popup menu.
 * @param e The ActionEvent causing the action.
 */
/*public*/ void FunctionButton::popactionPerformed(JActionEvent* /*e*/)
{
    FunctionButtonPropertyEditor* editor = new FunctionButtonPropertyEditor();
    editor->setFunctionButton(this);
    editor->setLocation(this->getLocationOnScreen());
    editor->setVisible(true);
    editor->exec();
}

/**
 * Change the state of the function.
 * @param newState The new state. True = Is on, False = Is off.
 */
/*public*/ void FunctionButton::changeState(bool newState)
{
    if (log->isDebugEnabled()) {
        log->debug(tr("Change state to ")+(newState?"true":"false"));
    }
    isOn = newState;
    this->setSelected(isOn);
//    for (int i=0; i<listeners.size();i++)
//        listeners.at(i)->notifyFunctionStateChanged(identity, isOn);
    emit notifyFunctionStateChanged(identity, isOn);
    if(isOn && selectedIcon != NULL)
      setSelectedIcon(selectedIcon);
    else
    if(!isOn && unSelectedIcon != NULL)
      setSelectedIcon(unSelectedIcon);
    else
      setIcon(QIcon());

}


/**
 * Add a listener to this button, probably some sort of keypad panel.
 * @param l The FunctionListener that wants notifications via the
 * FunctionListener.notifyFunctionStateChanged.
 */
/*public*/ void FunctionButton::setFunctionListener(FunctionListener* l) {
    //addFunctionListener(l);
 //connect(this, SIGNAL(notifyFunctionLockableChanged(int,bool)), l, SLOT(notifyFunctionLockableChanged(int,bool)));
}

/**
 * Add a listener to this button, probably some sort of keypad panel.
 * @param l The FunctionListener that wants notifications via the
 * FunctionListener.notifyFunctionStateChanged.
 */
/*public*/ void FunctionButton::addFunctionListener(FunctionListener* l) {
    if (!listeners.contains(l))
        listeners.append(l);
}

/**
 * Remove a listener from this button.
 * @param l The FunctionListener to be removed
 */
/*public*/ void FunctionButton::removeFunctionListener(FunctionListener* l) {
    if (listeners.contains(l))
        listeners.removeAt(listeners.indexOf(l));
}

/**
 * A PopupListener to handle mouse clicks and releases. Handles
 * the popup menu.
 */
//class PopupListener extends MouseAdapter
//{
/**
 * If the event is the popup trigger, which is dependent on
 * the platform, present the popup menu. Otherwise change
 * the state of the function depending on the locking state
 * of the button.
 * @param e The MouseEvent causing the action.
 */
/*public*/ void FunctionButton::mousePressEvent(QMouseEvent* e)
{
//    if (log->isDebugEnabled()) log->debug("pressed "+(e->modifiers() & MouseEvent::BUTTON1_MASK)+" "+e.isPopupTrigger()
//            +" "+(e.getModifiers() & (MouseEvent.ALT_MASK+MouseEvent.META_MASK+MouseEvent.CTRL_MASK))
//            +(" "+MouseEvent.ALT_MASK+"/"+MouseEvent.META_MASK+"/"+MouseEvent.CTRL_MASK));
//    JToggleButton* button = (JToggleButton*)e->getSource();
    //if (e->isPopupTrigger())
    if(e->button() == Qt::RightButton)
    {
//        popup->show(e.getComponent(),
//                   e.getX(), e.getY());
     popup->exec(QCursor::pos());
    }
    /* Must check button mask since some platforms wait
    for mouse release to do popup. */
    else if (isEnabled()
             //&& ((e.getModifiers() & MouseEvent.BUTTON1_MASK) != 0)
             && (e->button() != Qt::RightButton)
            //&& ((e.getModifiers() & (MouseEvent.ALT_MASK+MouseEvent.META_MASK+MouseEvent.CTRL_MASK)) == 0)
//             && ((e->modifiers() & Qt::MetaModifier == 0) &&(e->modifiers()&Qt::ControlModifier == 0) )
             && !isLockable)
    {
        changeState(true);
    }
    // force button to desired state; click might have changed it
    setSelected(isOn);
}

/**
 * If the event is the popup trigger, which is dependent on
 * the platform, present the popup menu. Otherwise change
 * the state of the function depending on the locking state
 * of the button.
 * @param e The MouseEvent causing the action.
 */
/*public*/ void FunctionButton::mouseReleaseEvent(QMouseEvent* e)
{
//    if (log->isDebugEnabled()) log->debug("released "+(e.getModifiers() & MouseEvent.BUTTON1_MASK)+" "+e.isPopupTrigger()
//            +" "+(e.getModifiers() & (MouseEvent.ALT_MASK+MouseEvent.META_MASK+MouseEvent.CTRL_MASK)));
    //JToggleButton* button = (JToggleButton*)e->getSource();
    //if (e->isPopupTrigger())
    if(e->button() == Qt::RightButton)
    {
//        popup.show(e.getComponent(),
//                   e.getX(), e.getY());
        popup->exec(QCursor::pos());
    }
    // mouse events have to be unmodified; to change function, so that
    // we don't act on 1/2 of a popup request.
    else if (isEnabled()
            //&& ((e.getModifiers() & MouseEvent.BUTTON1_MASK) != 0)
//             && (e->button() == Qt::RightButton)
//            && ((e.getModifiers() & (MouseEvent.ALT_MASK+MouseEvent.META_MASK+MouseEvent.CTRL_MASK)) == 0)
//             && ((e->modifiers() & Qt::MetaModifier == 0) &&(e->modifiers()&Qt::ControlModifier == 0)
            )
    {
        if (!isLockable)
        {
            changeState(false);
        }
        else
        {
            changeState(!isOn);
        }
    }
    // force button to desired state
    setSelected(isOn);
}
//};

/**
 * Collect the prefs of this object into XML Element
 * <ul>
 * <li> identity
 * <li> text
 * <li> isLockable
 * </ul>
 * @return the XML of this object.
 */
/*public*/ QDomElement FunctionButton::getXml()
{
    QDomDocument doc;

    QDomElement me = doc.createElement("FunctionButton");
    me.setAttribute("id", (this->getIdentity()));
    me.setAttribute("text", this->getButtonLabel());
    me.setAttribute("isLockable",  (this->getIsLockable()));
    me.setAttribute("isVisible",  (this->getDisplay()));
    me.setAttribute("fontSize",  (this->font().pointSize()));
    if ( this->getIconPath().startsWith(FileUtil::getUserResourcePath()))
        me.setAttribute("iconPath", this->getIconPath().mid( FileUtil::getUserResourcePath().length() ));
    else
        me.setAttribute("iconPath", this->getIconPath());
    if (this->getSelectedIconPath().startsWith(FileUtil::getUserResourcePath()))
        me.setAttribute("selectedIconPath", this->getSelectedIconPath().mid( FileUtil::getUserResourcePath().length() ));
    else
        me.setAttribute("selectedIconPath", this->getSelectedIconPath());
    return me;
}

/*private*/ bool FunctionButton::checkFile(QString name) {
    QFile* fp = new QFile(name);
    if (fp->exists()) return true;
    return false;
}

/**
 * Set the preferences based on the XML Element.
 * <ul>
 * <li> identity
 * <li> text
 * <li> isLockable
  * </ul>
 * @param e The Element for this object.
 */
/*public*/ void FunctionButton::setXml(QDomElement e)
{
 try
 {
  this->setIdentity(e.attribute("id").toInt());
  this->setText(e.attribute("text"));
  bool isLockable = (e.attribute("isLockable")=="true");
  this->setIsLockable(isLockable);
  bool isVisible = (e.attribute("isVisible")=="true");
  this->setDisplay(isVisible);
  if (this->getIdentity() < FunctionPanel::NUM_FUNC_BUTTONS_INIT)
    this->setVisible(isVisible);
  else
    this->setVisible(false);
  this->setFont(QFont("Monospace", e.attribute("fontSize").toInt()));
  if ((e.attribute("iconPath")!=NULL) && (e.attribute("iconPath").length()>0))
  if (checkFile(FileUtil::getUserResourcePath()+e.attribute("iconPath")) )
   this->setIconPath(FileUtil::getUserResourcePath()+e.attribute("iconPath"));
  else
   this->setIconPath(e.attribute("iconPath"));
  if ((e.attribute("selectedIconPath")!=NULL) && (e.attribute("selectedIconPath").length()>0))
  if (checkFile(FileUtil::getUserResourcePath()+e.attribute("selectedIconPath")))
   this->setSelectedIconPath(FileUtil::getUserResourcePath()+e.attribute("selectedIconPath"));
  else
   this->setSelectedIconPath(e.attribute("selectedIconPath"));
  updateLnF();
 }
 catch (DataConversionException ex)
 {
  log->error("DataConverstionException in setXml: "+ex.msg);
 }
}

/*public*/ void FunctionButton::setIconPath(QString fnImg) {
    iconPath = fnImg;
#if 0
    ResizableImagePanel* fnImage = new ResizableImagePanel();
    fnImage.setBackground(new Color(0,0,0,0));
    fnImage.setRespectAspectRatio(true);
    fnImage.setSize( QSize(FunctionButton::BUT_IMG_SIZE, FunctionButton::BUT_IMG_SIZE));
    fnImage.setImagePath(fnImg);
    if (fnImage.getScaledImage()!=NULL)
#endif
    if(fnImg == "")
     fnImg = ":/resources/icons/smallschematics/tracksegments/circuit-error.gif";
    if(fnImg != "")
    {
     unSelectedIcon = new NamedIcon(fnImg, fnImg);
     unSelectedIcon->reduceTo(BUT_WDTH, BUT_HGHT, BUT_IMG_SIZE);
     //setIcon(new ImageIcon(fnImage.getScaledImage()));
     //setIcon(QIcon(/*FileUtil::getUserResourcePath()+ */fnImg));
        setSelectedIcon(unSelectedIcon);
     _isImageOK = true;

    }
    else
    {
     setIcon(QIcon());
     _isImageOK = false;
    }
#endif
}

/*public*/ QString FunctionButton::getIconPath() {
    if (iconPath == NULL)
    {
     if(unSelectedIcon != NULL)
     {
      iconPath = unSelectedIcon->getURL();
     }
    }
    return iconPath;
}

/*public*/ void FunctionButton::setSelectedIconPath(QString fnImg) {
    selectedIconPath = fnImg;
#if 0
    ResizableImagePanel fnSelectedImage = NULL;
    if (fnImg != NULL) {
        fnSelectedImage = new ResizableImagePanel();
        fnSelectedImage.setBackground(new Color(0,0,0,0));
        fnSelectedImage.setRespectAspectRatio(true);
        fnSelectedImage.setSize(new Dimension(FunctionButton::BUT_IMG_SIZE, FunctionButton::BUT_IMG_SIZE));
        fnSelectedImage.setImagePath(fnImg);
    }
    if ((fnSelectedImage != NULL) && (fnSelectedImage.getScaledImage()!=NULL)) {
        ImageIcon icon = new ImageIcon(fnSelectedImage.getScaledImage());
        setSelectedIcon(icon);
        setPressedIcon(icon);
        isSelectedImageOK = true;
    }
    else {
        setSelectedIcon(NULL);
        setPressedIcon(NULL);
        isSelectedImageOK = false;
    }
#endif
    if(fnImg == "")
        fnImg = ":/resources/icons/smallschematics/tracksegments/circuit-green.gif";
    if(fnImg != "")
    {
     selectedIcon = new NamedIcon(fnImg, fnImg);
     selectedIcon->reduceTo(BUT_WDTH, BUT_HGHT, BUT_IMG_SIZE);
     //setIcon(new ImageIcon(fnImage.getScaledImage()));
     setSelectedIcon(selectedIcon);
     selectedIconPath = fnImg;
     //setPressedIcon(new NamedIcon(FileUtil::getUserResourcePath()+ fnImg, fnImg));
     _isImageOK = true;
    }
    else
    {
     setIcon(QIcon());
     _isImageOK = false;
    }
}

/*public*/ QString FunctionButton::getSelectedIconPath() {
    if (selectedIconPath == "")
        return "";
    return selectedIconPath;
}

/*public*/ bool FunctionButton::isImageOK() {
    return _isImageOK;
}

/*public*/ bool FunctionButton::isSelectedImageOK() {
    return _isSelectedImageOK;
}

