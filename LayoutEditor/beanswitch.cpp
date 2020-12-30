#include "beanswitch.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "loggerfactory.h"
#include <QPushButton>
#include <QBoxLayout>
#include "flowlayout.h"
#include "switchboardeditor.h"
#include "joptionpane.h"
#include "bufferedimage.h"
#include "file.h"
#include "exceptions.h"
#include "imageio.h"
#include "turnout.h"
#include "fileutil.h"
//#include "borderlayout.h"
#include "jmrijframe.h"
#include "jtextfield.h"
#include <QVariant>
#include "addnewdevicepanel.h"
#include "light.h"
#include <QPaintDevice>
#include "colorutil.h"
#include "borderfactory.h"

/**
 * Class for a switchboard interface object.
 * <p>
 * Contains a JButton or JPanel to control existing turnouts, sensors and
 * lights.
 * Separated from SwitchboardEditor.java in 4.12.3
 *
 * @author Egbert Broerse Copyright (c) 2017, 2018
 */
// /*public*/ class BeanSwitch extends JPanel implements java.beans.PropertyChangeListener, ActionListener {


/**
 * Ctor
 *
 * @param index       DCC address
 * @param bean        layout object to connect to
 * @param switchName  descriptive name corresponding with system name to
 *                    display in switch tooltip, i.e. LT1
 * @param shapeChoice Button, Icon (static) or Drawing (vector graphics)
 */
/*public*/ BeanSwitch::BeanSwitch(int index, NamedBean* bean, QString switchName, int shapeChoice, SwitchboardEditor* editor) : JPanel(){
 setObjectName("BeanSwitch_"+ switchName);
 stateClosed = tr("C"); // StateClosedShort
 stateThrown = tr("T"); // StateThrownShort
 nbhm = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"));
 opac = 0.5f;
 rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/";
 iconOffPath = rootPath + "appslide-off-s.png";
 iconOnPath = rootPath + "appslide-on-s.png";
 keyOffPath = rootPath + "markl-off-s.png";
 keyOnPath = rootPath + "markl-on-s.png";
 symbolOffPath = rootPath + "T-off-s.png"; // default for Turnout, replace T by S or L
 symbolOnPath = rootPath + "T-on-s.png";
 connectNewMenu = new QAction(tr("Connect to new item%1").arg("..."),this);
 addFrame = nullptr;
 sysName = new JTextField(12);
 userName = new JTextField(15);
 setObjectName("BeanSwitch");
 switchPopup = nullptr;
 beanButton = nullptr;
 beanIcon = nullptr;
 beanKey = nullptr;
 beanSymbol = nullptr;

    _label = switchName;
    _editor = editor;
    log->debug(tr("Name = [%1]").arg(switchName));
    switchLabel = _label + ": ?"; // initial state unknown, used on icons
    _bname = bean;
    if (bean != nullptr) {
        _uname = bean->getUserName();
        log->debug(tr("UserName: %1").arg(_uname));
        if (_uname == nullptr) {
            _uname = tr("no user name");
        }
    }
    switchTooltip = switchName + " (" + _uname + ")";

    //this.setLayout(new BorderLayout()); // makes JButtons expand to the whole grid cell
    QHBoxLayout* thisLayout = new QHBoxLayout(this);
    this->layout()->setObjectName("BeanSwitchLayout");
        setFrameStyle(QFrame::Plain);
        setFrameShape(QFrame::Panel);
    if (shapeChoice != 0) {
        _shape = shapeChoice; // Button
    } else {
        _shape = 0;
    }
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

    beanManuPrefix = _editor->getSwitchManu(); // connection/manufacturer i.e. M for MERG
    beanTypeChar = _label.at(beanManuPrefix.length()); // bean type, i.e. L, usually at char(1)
    // check for space char which might be caused by connection name > 2 chars and/or space in name
    if (beanTypeChar != 'T' && beanTypeChar != 'S' && beanTypeChar != 'L')
    { // add if more bean types are supported
     log->error(tr("invalid char '%2' in Switchboard Button \"%1\". Check connection name.").arg( _label).arg(beanTypeChar));
     JOptionPane::showMessageDialog(nullptr, tr("Could not connect to a new item"),
             tr("Warning"),
             JOptionPane::ERROR_MESSAGE);
     return;
    }
#if 1
    beanIcon = new IconSwitch(iconOnPath, iconOffPath, this);
    beanKey = new IconSwitch(keyOnPath, keyOffPath, this);
    beanSymbol = new IconSwitch(rootPath + beanTypeChar + "-on-s.png", rootPath + beanTypeChar + "-off-s.png", this);
#endif
    // look for bean to connect to by name
    log->debug(tr("beanconnect = %1, beantype = %2").arg(beanManuPrefix).arg(beanTypeChar));
    try {
        if (bean != nullptr) {
            namedBean = nbhm->getNamedBeanHandle(switchName, bean);
        }
    } catch (IllegalArgumentException e) {
        log->error(tr("invalid bean name= \"{%1\" in Switchboard Button").arg(switchName));
    }

    // attach shape specific code to this beanSwitch
    switch (_shape) {
        case 1: // icon shape
            log->debug("create Icon");
            beanIcon = new IconSwitch(iconOnPath, iconOffPath, this);
//            beanIcon.addMouseListener(new MouseAdapter() { // handled by JPanel
//                @Override
//                /*public*/ void mouseClicked(MouseEvent me) {
//                    operate(me, switchName);
//                }

//                @Override
//                /*public*/ void mousePressed(MouseEvent e) {
//                    _editor.setBoardToolTip(nullptr); // ends tooltip if displayed
//                    if (e.isPopupTrigger()) {
//                        // display the popup:
//                        showPopUp(e);
//                    }
//                }
//            });
            connect(beanIcon, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseClicked(QMouseEvent*)));
            connect(beanIcon, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressed(QMouseEvent*)) );
            _text = true; // TODO when web supports graphic switches: replace true by false;
            _icon = true;
            beanIcon->setLabel(switchLabel);
            beanIcon->positionLabel(17, 45); // provide x, y offset, depending on image size and free space
            if (_editor->showToolTip()) {
                beanIcon->setToolTip(switchTooltip);
            }
            beanIcon->setBackground(_editor->getDefaultBackgroundColor());
            //remove the line around icon switches?
            thisLayout->addWidget(beanIcon);
            beanIcon->setVisible(true);
            break;

        case 2: // Maerklin style keyboard
            log->debug("create Key");
            beanKey = new IconSwitch(keyOnPath, keyOffPath, this);

#if 0
            beanKey.addMouseListener(new MouseAdapter() { // handled by JPanel
                @Override
                /*public*/ void mouseClicked(MouseEvent me) {
                    operate(me, switchName);
                }

                @Override
                /*public*/ void mousePressed(MouseEvent e) {
                    _editor.setBoardToolTip(nullptr); // ends tooltip if displayed
                    if (e.isPopupTrigger()) {
                        // display the popup:
                        showPopUp(e);
                    }
                }
            });
#endif
            connect(beanKey, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseClicked(QMouseEvent*)));
            connect(beanKey, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressed(QMouseEvent*)) );
            _text = true; // TODO when web supports graphic switches: replace true by false;
            _icon = true;
            beanKey->setLabel(switchLabel);
            beanKey->positionLabel(14, 60); // provide x, y offset, depending on image size and free space
            if (_editor->showToolTip()) {
                beanKey->setToolTip(switchTooltip);
            }
            beanKey->setBackground(_editor->getDefaultBackgroundColor());
            //remove the line around icon switches?
            thisLayout->addWidget(beanKey);
            beanKey->setVisible(true);
            break;

        case 3: // drawing turnout/sensor/light symbol (selecting image by letter in switch name/label)
            log->debug("create Symbols");
            beanSymbol = new IconSwitch(rootPath + beanTypeChar + "-on-s.png", rootPath + beanTypeChar + "-off-s.png", this);

//            beanSymbol.addMouseListener(new MouseAdapter() { // handled by JPanel
//                @Override
//                /*public*/ void mouseClicked(MouseEvent me) {
//                    operate(me, switchName);
//                }

//                @Override
//                /*public*/ void mousePressed(MouseEvent e) {
//                    _editor.setBoardToolTip(nullptr); // ends tooltip if displayed
//                    if (e.isPopupTrigger()) {
//                        // display the popup:
//                        showPopUp(e);
//                    }
//                }
//            });
            connect(beanSymbol, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseClicked(QMouseEvent*)));
            connect(beanSymbol,SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressed(QMouseEvent*)));
            _text = true; // TODO when web supports graphic switches: replace true by false;
            _icon = true;
            beanSymbol->setLabel(switchLabel);
            beanSymbol->positionLabel(24, 20); // provide x, y offset, depending on image size and free space
            if (_editor->showToolTip()) {
                beanSymbol->setToolTip(switchTooltip);
            }
            beanSymbol->setBackground(_editor->getDefaultBackgroundColor());
            //remove the line around icon switches?
            this->setBorder(BorderFactory::createLineBorder(_editor->getDefaultBackgroundColor(), 3));
            thisLayout->addWidget(beanSymbol);
            beanSymbol->setVisible(true);
            break;
        default: // 0 = "Button" shape
            log->debug("create Button");
            beanButton = new QPushButton(_label + ": ?"); // initial state unknown

//            beanButton.addMouseListener(new MouseAdapter() { // handled by JPanel
//                @Override
//                /*public*/ void mouseClicked(MouseEvent me) {
//                    operate(me, switchName);
//                }
              connect(this, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseClicked(QMouseEvent*)));
//                @Override
//                /*public*/ void mousePressed(MouseEvent e) {
//                    _editor.setBoardToolTip(nullptr); // ends tooltip if displayed
//                    if (e.isPopupTrigger()) {
//                        // display the popup:
//                        showPopUp(e);
//                    }
//                }
//            });
            connect(beanButton, SIGNAL(clicked()), this, SLOT(mouseClicked()));
            _text = true;
            _icon = false;
            //beanButton->setBackground(_editor->getDefaultBackgroundColor());
            beanButton->setStyleSheet(tr("QPushButton {\
                                      background-color: %1;\
                                      border-style: outset; \
                                      border-width: 2px; \
                                      border-radius: 10px;\
                                      border-color: beige;\
                                      font: bold 14px;\
                                      min-width: 10em;\
                                      padding: 6px;\
                                  }\
                                  QPushButton#evilButton:pressed {\
                                      background-color: rgb(224, 0, 0);\
                                      border-style: inset;\
                                  }").arg(ColorUtil::colorToString( editor->getDefaultBackgroundColor())));
            QColor color = _editor->getDefaultBackgroundColor();
            beanButton->setStyleSheet(tr("QPushButton {background-color: rgb(%1, %2, %3)}").arg(color.red()).arg(color.green()).arg(color.blue()));
            //beanButton->setOpaque(false);
            if (_editor->showToolTip()) {
                beanButton->setToolTip(switchTooltip);
            }
            thisLayout->addWidget(beanButton);
            break;
    }
    setVisible(true);
    // connect to object or dim switch
    if (bean == nullptr)
    {
     if (!_editor->getHideUnconnected())
     {
      switch (_shape)
      {
       case 0:
           beanButton->setEnabled(false);
           break;
       default:
           beanIcon->setOpacity(opac);
           break;
      }
     }
    }
    else
    {  // bean valid
     _control = true;
     if(beanTypeChar ==  'T')
     {
      getTurnout()->addPropertyChangeListener((PropertyChangeListener*)this, _label, "Switchboard Editor Turnout Switch");
      //connect(getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
       if (getTurnout()->canInvert()) {
           this->setInverted(getTurnout()->getInverted()); // only add and set when suppported by object/connection
       }
     }
     else if(beanTypeChar ==  'S')
     {
      getSensor()->addPropertyChangeListener((PropertyChangeListener*)this, _label, "Switchboard Editor Sensor Switch");
      //connect(getSensor()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
       if (getSensor()->canInvert()) {
           this->setInverted(getSensor()->getInverted()); // only add and set when suppported by object/connection
       }
     }
     else
     {// light
      getLight()->addPropertyChangeListener((PropertyChangeListener*)this, _label, "Switchboard Editor Light Switch");
      //connect(getLight()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         // Lights do not support Invert
     }
    }

    // from finishClone
    setTristate(getTristate());
    setMomentary(getMomentary());
    log->debug(tr("Created switch %1").arg(index));
}

void BeanSwitch::mouseClicked(QMouseEvent *me)
{
 operate(me, _label);
}


BeanSwitch::~BeanSwitch()
{

}

/*public*/ NamedBean* BeanSwitch::getNamedBean() {
    return _bname;
}

/**
 * Stores an object as NamedBeanHandle, using _label as the display
 * name.
 *
 * @param bean the object (either a Turnout, Sensor or Light) to attach
 *             to this switch
 */
/*public*/ void BeanSwitch::setNamedBean(/*@Nonnullptr*/ NamedBean* bean) {
    try {
        namedBean = nbhm->getNamedBeanHandle(_label, bean);
    } catch (IllegalArgumentException e) {
        log->error(tr("invalid bean name= \"%1\" in Switchboard Button").arg(_label));
    }
    _uname = bean->getUserName();
    _control = true;
}

/*public*/ Turnout* BeanSwitch::getTurnout() {
    if (namedBean == nullptr) {
        return nullptr;
    }
    return (Turnout*) static_cast<NamedBeanHandle<Turnout*>* >(namedBean)->getBean();
}

/*public*/ Sensor* BeanSwitch::getSensor() {
    if (namedBean == nullptr) {
        return nullptr;
    }
    return (Sensor*)  static_cast<NamedBeanHandle<Sensor*>* >(namedBean)->getBean();
}

/*public*/ Light* BeanSwitch::getLight() {
    if (namedBean == nullptr) {
        return nullptr;
    }
    return (Light*)  static_cast<NamedBeanHandle<Light*>* >(namedBean)->getBean();
}

/**
 * Get the user selected switch shape (e.g. 3 for Slider)
 *
 * @return the index of the selected item in Shape comboBox
 */
/*public*/ int BeanSwitch::getType() {
    return _shape;
}

/**
 * Get text to display on this switch on Switchboard and in Web Server panel when attached
 * object is Inactive.
 *
 * @return text to show on inactive state (differs per type of objects)
 */
/*public*/ QString BeanSwitch::getInactiveText() {
    // fetch bean specific abbreviation
    if (beanTypeChar == 'T')
            _state = stateThrown; // +
     else // Light, Sensor
            _state = "-";         // 1 char abbreviation for StateOff not clear
    return _label + ": " + _state;
}

/**
 * Get text to display on this switch on Switchboard and in Web Server panel when attached
 * object is Active.
 *
 * @return text to show on active state (differs per type of objects)
 */
/*public*/ QString BeanSwitch::getActiveText() {
    // fetch bean specific abbreviation
    if (beanTypeChar == 'T')
            _state = stateClosed; // +
     else // Light, Sensor
            _state = "+";         // 1 char abbreviation for StateOff not clear
    return _label + ": " + _state;
}

/**
 * Get text to display on this switch in Web Server panel when attached
 * object is Unknown (initial state displayed).
 *
 * @return text to show on unknown state (used on all types of objects)
 */
/*public*/ QString BeanSwitch::getUnknownText() {
    return _label + ": ?";
}

/*public*/ QString BeanSwitch::getInconsistentText() {
    return _label + ": X";
}

/**
 * Get text to display as switch tooltip in Web Server panel.
 * Used in jmri.jmrit.display.switchboardEditor.configureXml.BeanSwitchXml#store(Object)
 *
 * @return switch tooltip text
 */
/*public*/ QString BeanSwitch::getToolTip() {
    return switchTooltip;
}

// ******************* Display ***************************

//@Override
/*public*/ void BeanSwitch::actionPerformed(JActionEvent* e) {
    //updateBean();
}

/**
 * Get the label of this switch.
 *
 * @return display name plus current state
 */
/*public*/ QString BeanSwitch::getNameString() {
    return _label;
}

/**
 * Drive the current state of the display from the state of the
 * connected bean.
 *
 * @param state integer representing the new state e.g. Turnout.CLOSED
 */
/*public*/ void BeanSwitch::displayState(int state) {
    QString switchLabel;
    log->debug("heard change");
    if (getNamedBean() == nullptr) {
        log->debug(tr("Display state %1, disconnected").arg(state));
    } else {
        // display abbreviated name of state instead of state index
        switch (state) {
            case 2:
                switchLabel = getActiveText();
                break;
            case 4:
                switchLabel = getInactiveText();
                break;
            case 1:
                switchLabel = getUnknownText();
                break;
            default:
                switchLabel = getInconsistentText();
                log->warn(tr("invalid char in Switchboard Button \"%1\". ERROR state shown.").arg(_label));
        }
        log->debug(tr("Switch label %1 state: %2 ").arg(switchLabel).arg(state));
        if (isText() && !isIcon()) { // to allow text buttons on web switchboard. TODO add graphic switches on web
            beanButton->setText(switchLabel);
        }
        if (isIcon() ) //&& beanIcon != nullptr && beanKey != nullptr && beanSymbol != nullptr)
        {
         switch(_shape)
         {
         case 1:
            beanIcon->showSwitchIcon(state);
            beanIcon->setLabel(switchLabel);
          break;
         case 2:
            beanKey->showSwitchIcon(state);
            beanKey->setLabel(switchLabel);
          break;
         case 3:
            beanSymbol->showSwitchIcon(state);
            beanSymbol->setLabel(switchLabel);
          break;
        }
       }
    }
}

/**
 * Switch presentation is graphic image based.
 *
 * @see #displayState(int)
 * @return true when switch shape other than 'Button' is selected
 */
/*public*/ /*final*/ bool BeanSwitch::isIcon() {
    return _icon;
}

/**
 * Switch presentation is text based.
 *
 * @see #displayState(int)
 * @return true when switch shape 'Button' is selected (and also for the
 *         other, graphic switch types until SwitchboardServlet directly
 *         supports their graphic icons)
 */
/*public*/ /*final*/ bool BeanSwitch::isText() {
    return _text;
}

/**
 * Get current state of attached turnout.
 *
 * @return A state variable from a Turnout, e.g. Turnout.CLOSED
 */
int BeanSwitch::turnoutState() {
    if (namedBean != nullptr) {
        return getTurnout()->getKnownState();
    } else {
        return Turnout::UNKNOWN;
    }
}

/**
 * Update switch as state of turnout changes.
 *
 * @param e the PropertyChangeEvent heard
 */
//@Override
/*public*/ void BeanSwitch::propertyChange(PropertyChangeEvent* e)
{
    if (log->isDebugEnabled())
    {
     log->debug(tr("property change: %1 %2 is now: %3").arg(_label).arg(e->getPropertyName()).arg( e->getNewValue().toString()));
    }
    // when there's feedback, transition through inconsistent icon for better animation
    if (getTristate()
            && (getTurnout()->getFeedbackMode() != Turnout::DIRECT)
            && (e->getPropertyName() == ("CommandedState")))
    {
        if (getTurnout()->getCommandedState() != getTurnout()->getKnownState()) {
            int now = Turnout::INCONSISTENT;
            displayState(now);
        }
        // this takes care of the quick double click
        if (getTurnout()->getCommandedState() == getTurnout()->getKnownState()) {
            int now =  e->getNewValue().toInt();
            displayState(now);
        }
    }
    if (e->getPropertyName() == ("KnownState")) {
        int now =  e->getNewValue().toInt();
        displayState(now);
        log->debug("Item state changed");
    }
    if (e->getPropertyName() == ("UserName"))
    {
     // update tooltip
     QString newUserName;
     if (_editor->showToolTip())
     {
       newUserName = e->getNewValue().toString();
       if (newUserName == nullptr || newUserName == ("")) {
           newUserName = tr("No User Name");
       }
       if(beanButton != nullptr)
        beanButton->setToolTip(_label + " (" + newUserName + ")");
       if(beanIcon != nullptr)
        beanIcon->setToolTip(_label + " (" + newUserName + ")");
       if(beanKey != nullptr)
        beanKey->setToolTip(_label + " (" + newUserName + ")");
       if(beanSymbol != nullptr)
        beanSymbol->setToolTip(_label + " (" + newUserName + ")");
       log->debug(tr("User Name changed to %1").arg(newUserName));
     }
    }
}

/*public*/ void BeanSwitch::mousePressed(QMouseEvent* e) {
    _editor->setBoardToolTip(""); // ends tooltip if displayed
    if (e->buttons()&Qt::RightButton) {
        // display the popup:
        showPopUp(e);
    }
}

/*public*/ void BeanSwitch::mouseExited(QMouseEvent* e) {
    //super.mouseExited(e);
}

/**
 * Process mouseClick on this switch.
 *
 * @param e    the event heard
 * @param name ID of this button (identical to name of suggested bean
 *             object)
 */
/*public*/ void BeanSwitch::operate(QMouseEvent* e, QString name) {
    log->debug(tr("Button %1 clicked").arg(name));
    //if (!_editor.getFlag(Editor.OPTION_CONTROLS, isControlling())) {
    //    return;
    //}
    if (namedBean == nullptr) //|| /*e.isMetaDown()*/(e->modifiers()&Qt::MetaModifier))
    { // || e.isAltDown() || !buttonLive() || getMomentary()) {
        return;
    }
    alternateOnClick();
}

void BeanSwitch::cleanup() {
    if (namedBean != nullptr) {
     getTurnout()->removePropertyChangeListener((PropertyChangeListener*)this);
     //disconnect(getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedBean = nullptr;
}


/*public*/ void BeanSwitch::setTristate(bool set) {
    tristate = set;
}

/*public*/ bool BeanSwitch::getTristate() {
    return tristate;
}

/*public*/ bool BeanSwitch::getMomentary() {
    return momentary;
}

/*public*/ void BeanSwitch::setMomentary(bool m) {
    momentary = m;
}
void BeanSwitch::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseMove(e);
 QFrame::mouseMoveEvent(e);
}
void BeanSwitch::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseRelease(e);
 QFrame::mouseReleaseEvent(e);
}
void BeanSwitch::mousePressEvent(QMouseEvent *event)
{
 emit mousePress(event);
 QFrame::mousePressEvent(event);
}
void BeanSwitch::mouseDoubleClickEvent(QMouseEvent *event)
{
 emit mouseDoubleClick(event);
 QFrame::mouseDoubleClickEvent(event);
}



/**
 * Show pop-up on a switch with its unique attributes including the
 * (un)connected bean. Derived from
 * {@link jmri.jmrit.display.switchboardEditor.SwitchboardEditor#showPopUp(Positionable, MouseEvent)}
 *
 * @param e the event
 */
/*public*/ bool BeanSwitch::showPopUp(QMouseEvent* e)
{
 if (switchPopup != nullptr) {
     switchPopup->clear();
 } else {
     switchPopup = new QMenu();
 }

 switchPopup->addSection(getNameString());

 if (_editor->isEditable())
 {
  // add tristate option if turnout has feedback
  if (namedBean != nullptr)
  {
   //addTristateEntry(switchPopup); // switches don't do anything with this property
   addEditUserName(switchPopup);
   if(beanTypeChar == 'T')
   {
    if (getTurnout()->canInvert()) { // check whether supported by this turnout
        addInvert(switchPopup);
    }
}
   else  if(beanTypeChar ==  'S')
   {
    if (getSensor()->canInvert()) { // check whether supported by this sensor
        addInvert(switchPopup);
    }
   }
       // invert is not supported by Lights, so skip
  }
  else
  {
      // show option to attach a new bean
    switchPopup->addAction(connectNewMenu);
//         connectNewMenu.addActionListener((java.awt.event.ActionEvent e1) -> {
//             connectNew(_label);
//         });
    connect(connectNewMenu, SIGNAL(triggered(bool)), this, SLOT(onConnectNewLabel()));
  }
 }
 // display the popup
//    switchPopup.show(this, this.getWidth() / 3 + (int) ((_editor.getPaintScale() - 1.0) * this.getX()),
//            this.getHeight() / 3 + (int) ((_editor.getPaintScale() - 1.0) * this.getY()));
 switchPopup->exec(QCursor::pos());

 return true;
}

void BeanSwitch::onConnectNewLabel()
{
 connectNew(_label);
}

void BeanSwitch::addEditUserName(QMenu* popup) {
    editItem = new QAction(tr("Edit User Name%1").arg("..."));
    popup->addAction(editItem);
//    editItem.addActionListener((java.awt.event.ActionEvent e) -> {
//        renameBean();
//    });
    connect(editItem, SIGNAL(triggered(bool)), this, SLOT(renameBean()));
}


void BeanSwitch::addInvert(QMenu* popup) {
    invertItem = new QAction(tr("Invert %1").arg(_label));
    invertItem->setCheckable(true);
    invertItem->setChecked(getInverted());
    popup->addAction(invertItem);
//    invertItem.addActionListener((java.awt.event.ActionEvent e) -> {
//        setBeanInverted(invertItem.isSelected());
//    });
    connect(invertItem, SIGNAL(toggled(bool)), this, SLOT(setBeanInverted(bool)));
}

/**
 * Edit user name on a switch using N11N. Copied from
 * BeanTableDataModel.
 */
/*public*/ void BeanSwitch::renameBean() {
    NamedBean* nb;
    QString oldName = _uname;
    // show input dialog
#if 1
    QVariant newUserName = JOptionPane::showInputDialog(nullptr,
            tr("Enter new user name for \"%1\":").arg(_label),
            /*tr("Edit User Name%1").arg(""), JOptionPane::PLAIN_MESSAGE, QIcon(), QList<QVariant>(),*/ oldName);
    if (newUserName == QVariant()) { // user cancelled
        log->debug("NewName dialog returned Null, cancelled");
        return;
    }
    newUserName = newUserName.toString().trimmed(); // N11N
    log->debug(tr("New name: %1").arg(newUserName.toString()));
    if (newUserName.toString().length() == 0) {
        log->debug("new user name is empty");
        JOptionPane::showMessageDialog(nullptr, tr("User Name cannot be empty.\nPlease use Tools > Tables to make advanced changes."),
                tr("Warning"),
                JOptionPane::ERROR_MESSAGE);
        return;
    }

    if (newUserName == (oldName)) { // name was not changed by user
        return;
    }
    else
    { // check if name is already in use
     if (beanTypeChar== 'T')
     {
      nb = InstanceManager::turnoutManagerInstance()->getTurnout(newUserName.toString());
     }
     else  if(beanTypeChar ==  'S')
     {
      nb = InstanceManager::sensorManagerInstance()->getSensor(newUserName.toString());
     }
     else  if(beanTypeChar ==  'L')
     {
      nb = InstanceManager::lightManagerInstance()->getLight(newUserName.toString());
     }
     else
     {
      log->error(tr("Check userName: cannot parse bean name. userName = %1").arg(newUserName.toString()));
      return;
     }
     if (nb != nullptr)
     {
      log->error(tr("User name is not unique %1").arg(newUserName.toString()));
      QString msg = tr("User Name \"%1\" has already been used.").arg( newUserName.toString());
      JOptionPane::showMessageDialog(nullptr, msg,
              tr("Warning"),
              JOptionPane::ERROR_MESSAGE);
      return;
     }
    }
    _bname->setUserName(newUserName.toString());
    if (newUserName != (""))
    {
     if (oldName == nullptr || oldName == ("")) {
         if (!nbhm->inUse(_label, _bname)) {
             return; // no problem, so stop
         }
         QString msg = tr("UpdateToUserName %1 %2 %3").arg( _editor->getSwitchTypeName()).arg(newUserName.toString()).arg( _label);
         int optionPane = JOptionPane::showConfirmDialog(nullptr,
                 msg, tr("UpdateToUserNameTitle"),
                 JOptionPane::YES_NO_OPTION);
         if (optionPane == JOptionPane::YES_OPTION) {
             //This will update the bean reference from the systemName to the userName
             try {
                 nbhm->updateBeanFromSystemToUser(_bname);
             } catch (JmriException ex) {
                 //We should never get an exception here as we already check that the username is not valid
             }
         }

     } else {
         nbhm->renameBean(oldName, newUserName.toString(), _bname);
     }
    } else {
        //This will update the bean reference from the old userName to the SystemName
        nbhm->updateBeanFromUserToSystem(_bname);
    }
#endif
}



/*public*/ void BeanSwitch::setInverted(bool set) {
    inverted = set;
}

/*public*/ bool BeanSwitch::getInverted() {
    return inverted;
}

/**
 * Invert attached object on the layout, if supported by its connection.
 */
/*public*/ void BeanSwitch::setBeanInverted(bool set) {
    if(beanTypeChar ==  'T')
    {
            if (getTurnout()->canInvert()) { // if supported
                this->setInverted(set);
                getTurnout()->setInverted(set);
            } else {
                // show error message?
            }
    }
    else if(beanTypeChar ==  'S')
    {
            if (getSensor()->canInvert()) { // if supported
                this->setInverted(set);
                getSensor()->setInverted(set);
            } else {
                // show error message?
            }
    }
    else if(beanTypeChar == 'L')
    {
            // Lights cannot be inverted, so never called
            return;
    }
     else
            log->error(tr("Invert item: cannot parse bean name. userName = %1").arg(_label));

}

/*public*/ void BeanSwitch::doMouseClicked(QMouseEvent* e) {
    log->debug("Switch clicked");
    //if (!_editor.getFlag(Editor.OPTION_CONTROLS, isControlling())) {
    //    return;
    //}
    if (namedBean == nullptr || /*e.isMetaDown()*/(e->modifiers()&Qt::MetaModifier)) { //|| e.isAltDown() || !buttonLive() || getMomentary()) {
        return;
    }
    alternateOnClick();
}

/**
 * Change the state of attached Turnout, Light or Sensor on the layout
 * unless menu option Panel Items Control Layout is set to off.
 */
void BeanSwitch::alternateOnClick() {
    if (_editor->allControlling()) {
        if(beanTypeChar == 'T')
        {
         // Turnout
                log->debug("T clicked");
                if (getTurnout()->getKnownState() == Turnout::CLOSED) // if clear known state, set to opposite
                {
                    getTurnout()->setCommandedState(Turnout::THROWN);
                } else if (getTurnout()->getKnownState() == Turnout::THROWN) {
                    getTurnout()->setCommandedState(Turnout::CLOSED);
                } else if (getTurnout()->getCommandedState() == Turnout::CLOSED) {
                    getTurnout()->setCommandedState(Turnout::THROWN);  // otherwise, set to opposite of current commanded state if known
                } else {
                    getTurnout()->setCommandedState(Turnout::CLOSED);  // just force Closed
                }
         }
         else if(beanTypeChar ==  'L')
        {
         // Light
                log->debug("L clicked");
                if (getLight()->getState() == Light::OFF) {
                    getLight()->setState(Light::ON);
                } else {
                    getLight()->setState(Light::OFF);
                }
            }
            else if(beanTypeChar ==  'S')
         {// Sensor
                log->debug("S clicked");
                try {
                    if (getSensor()->getKnownState() == Sensor::INACTIVE) {
                        getSensor()->setKnownState(Sensor::ACTIVE);
                    } else {
                        getSensor()->setKnownState(Sensor::INACTIVE);
                    }
                } catch (JmriException reason) {
                    log->warn(tr("Exception flipping sensor: %1").arg(reason.getMessage()));
                }
            }
    }
            else
                log->error(tr("invalid char in Switchboard Button \"%1\". State not set.").arg(_label));


}

/*public*/ void BeanSwitch::setBackgroundColor(QColor bgcolor) {
    //this->setBackground(bgcolor);
 setStyleSheet(tr("{background: %1}").arg(ColorUtil::colorToHexString(bgcolor)));
}


/**
 * Create new bean and connect it to this switch. Use type letter from
 * switch label (S, T or L).
 */
/*protected*/ void BeanSwitch::connectNew(QString systemName) {
    log->debug("Request new bean");
    sysName->setText(systemName);
    userName->setText("");
    // provide etc.
    if (addFrame == nullptr) {
        addFrame = new JmriJFrameX(tr("ConnectNewMenu", ""), false, true);
        addFrame->addHelpMenu("package.jmri.jmrit.display.switchboardEditor.SwitchboardEditor", true);
        QVBoxLayout* addFrameLayout;
        addFrame->getContentPane()->setLayout(addFrameLayout = new QVBoxLayout()); //addFrame->getContentPane(), BoxLayout.Y_AXIS));
#if 0
        ActionListener okListener = (ActionEvent ev) -> {
            okAddPressed(ev);
        };
        ActionListener cancelListener = (ActionEvent ev) -> {
            cancelAddPressed(ev);
        };
#endif
        OkActionListener* okListener = new OkActionListener(this);
        CancelActionListener*cancelListener = new CancelActionListener(this);
        AddNewDevicePanel* switchConnect = new AddNewDevicePanel(sysName, userName, "OK", okListener, cancelListener);
        switchConnect->setSystemNameFieldIneditable(); // prevent user interference with switch label
        switchConnect->setOK(); // activate OK button on Add new device pane
        addFrameLayout->addWidget(switchConnect);
    }
    addFrame->pack();
    addFrame->setVisible(true);
}
/*protected*/ void BeanSwitch::cancelAddPressed(JActionEvent* e) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = nullptr;
}

/*protected*/ void BeanSwitch::okAddPressed(JActionEvent* e) {
    NamedBean* nb;
    QString manuPrefix = _editor->getSwitchManu();
    QString user = userName->text().trimmed();
    if (user == ("")) {
        user = nullptr;
    }
    QString sName = sysName->text(); // can't be changed, but pick it up from panel

    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = nullptr;

    if(sName.at(manuPrefix.length())=='T')
    {
            Turnout* t;
            try {
                // add turnout to JMRI (w/appropriate manager)
                t = InstanceManager::turnoutManagerInstance()->provideTurnout(sName);
                t->setUserName(user);
            } catch (IllegalArgumentException ex) {
                // user input no good
                handleCreateException(sName);
                return; // without creating
            }
            nb = InstanceManager::turnoutManagerInstance()->getTurnout(sName);
    }
    else if(sName.at(manuPrefix.length())=='S')
    {
            Sensor* s;
            try {
                // add Sensor to JMRI (w/appropriate manager)
                s = InstanceManager::sensorManagerInstance()->provideSensor(sName);
                s->setUserName(user);
            } catch (IllegalArgumentException ex) {
                // user input no good
                handleCreateException(sName);
                return; // without creating
            }
            nb = InstanceManager::sensorManagerInstance()->getSensor(sName);
    }
    else if(sName.at(manuPrefix.length())== 'L')
    {
            Light* l;
            try {
                // add Light to JMRI (w/appropriate manager)
                l = InstanceManager::lightManagerInstance()->provideLight(sName);
                l->setUserName(user);
            } catch (IllegalArgumentException ex) {
                // user input no good
                handleCreateException(sName);
                return; // without creating
            }
            nb = InstanceManager::lightManagerInstance()->getLight(sName);
        }
        else
    {
            log->error(tr("connectNew - OKpressed: cannot parse bean name. sName = %1").arg(sName));
            return;
    }
    if (nb == nullptr) {
        log->warn(tr("failed to connect switch to item %1").arg(sName));
    } else {
        // set switch on Switchboard to display current state of just connected bean
        log->debug(tr("sName state: %1").arg(nb->getState()));
        try {
            if (_editor->getSwitch(sName) == nullptr) {
                log->warn(tr("failed to update switch to state of %1").arg(sName));
            } else {
                _editor->updatePressed();
            }
        } catch (NullPointerException npe) {
            handleCreateException(sName);
            // exit without updating
        }
    }
}

void BeanSwitch::handleCreateException(QString sysName) {
    JOptionPane::showMessageDialog(addFrame,

                    tr("Could not connect to a new item %1").arg(
                    sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}


/**
 * Class to display individual bean state switches on a JMRI Switchboard
 * using 2 image files.
 */
///*public*/ class IconSwitch extends JPanel {

//    /*private*/ BufferedImage image;
//    /*private*/ BufferedImage image1;
//    /*private*/ BufferedImage image2;
//    /*private*/ String tag = "tag";
//    /*private*/ int labelX = 16;
//    /*private*/ int labelY = 53;

/**
 * Create an icon from 2 alternating png images.
 *
 * @param filepath1 the ON image
 * @param filepath2 the OFF image
 */
/*public*/ IconSwitch::IconSwitch(QString filepath1, QString filepath2, BeanSwitch* bs)
{
 this->bs = bs;
 QString tag = "tag";
 labelX = 16;
 labelY = 53;
 setObjectName("IconSwitch");
    // resize to maximum 100
    try
    {
        image1 = ImageIO::read(FileUtil::getFile(filepath1));

        image2 = ImageIO::read(FileUtil::getFile(filepath2));
        image = image1;
    } catch (Exception ex) {
        bs->log->error(tr("error reading image from %1 - %2").arg(filepath1).arg(filepath2), ex);
    }
}

/*protected*/ void IconSwitch::setOpacity(float /*opac*/) {
    //this.opacity = opac; // not functional, use alfa instead
}

/*protected*/ void IconSwitch::showSwitchIcon(int stateIndex) {
    bs->log->debug(tr("showSwitchIcon %1").arg(stateIndex));
    if (image1 != nullptr && image2 != nullptr) {
        switch (stateIndex) {
            case 2:
                image = image1; // on/Thrown/Active
                break;
            default:
                image = image2; // off, also for connected & unknown
                break;
        }
        setVisible(true);
        this->repaint();
    }
}

/*protected*/ void IconSwitch::setImage1(QString newImagePath) {
    try {
        image1 = ImageIO::read(new File(newImagePath));
    } catch (IOException ex) {
        bs->log->error(tr("error reading image from %1").arg(newImagePath), ex);
    }
}

/**
 * Set or change label text on switch.
 *
 * @param text string to display
 */
/*protected*/ void IconSwitch::setLabel(QString text) {
    tag = text;
    this->repaint();
}

/**
 * Position label on switch.
 *
 * @param x horizontal offset from top left corner, positive to the
 *          right
 * @param y vertical offset from top left corner, positive down
 */
/*protected*/ void IconSwitch::positionLabel(int x, int y) {
    labelX = x;
    labelY = y;
    this->repaint();
}
void IconSwitch::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseMove(e);
 JPanel::mouseMoveEvent(e);
}
void IconSwitch::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseRelease(e);
 JPanel::mouseReleaseEvent(e);
}
void IconSwitch::mousePressEvent(QMouseEvent *event)
{
 emit mousePress(event);
 JPanel::mousePressEvent(event);
}
void IconSwitch::mouseDoubleClickEvent(QMouseEvent *event)
{
 emit mouseDoubleClick(event);
 JPanel::mouseDoubleClickEvent(event);
}

void IconSwitch::paintEvent(QPaintEvent *e)
{
 QPainter* painter = new QPainter(this);
 paintComponent(painter);
 painter->end();
}

//@Override
/*protected*/ void IconSwitch::paintComponent(QPainter* g) {
    //QFrame::paintComponent(g);
    g->drawImage(0,0, *image);
    g->setFont(font());
    g->setBrush(QBrush(bs->_editor->getDefaultTextColorAsColor()));
    g->drawText(labelX, labelY, tag); // draw name on top of button image (vertical, horizontal offset from top left)
    //g->end();
}

//};

/*private*/ /*final*/ /*static*/ Logger* BeanSwitch::log = LoggerFactory::getLogger("BeanSwitch");


