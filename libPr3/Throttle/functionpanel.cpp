#include "functionpanel.h"
#include "ui_functionpanel.h"
#include "addresspanel.h"
#include "dccthrottle.h"
#include "functionbutton.h"
#include "addresslistener.h"
#include "rosterentry.h"
#include "QtXml"
#include "dccthrottle.h"
#include "abstractthrottle.h"
#include "roster.h"
#include "throttleframemanager.h"
#include "throttlespreferences.h"
#include <QKeyEvent>
#include "flowlayout.h"
#include "windowpreferences.h"


/**
 * Constructor
 */
FunctionPanel::FunctionPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::FunctionPanel)
{
 ui->setupUi(this);
 functionButton = QList<FunctionButton*>();
 functionButton.append(ui->btnLight);
 functionButton.append(ui->btnF1);
 functionButton.append(ui->btnF2);
 functionButton.append(ui->btnF3);
 functionButton.append(ui->btnF4);
 functionButton.append(ui->btnF5);
 functionButton.append(ui->btnF6);
 functionButton.append(ui->btnF7);
 functionButton.append(ui->btnF8);
 functionButton.append(ui->btnF9);
 functionButton.append(ui->btnF10);
 functionButton.append(ui->btnF11);
 functionButton.append(ui->btnF12);
 functionButton.append(ui->btnF13);
 functionButton.append(ui->btnF14);
 functionButton.append(ui->btnF15);
 functionButton.append(new FunctionButton); //F16
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton);
 functionButton.append(new FunctionButton); // F29
 for(int i =0; i < functionButton.count(); i++)
 {
  FunctionButton* b = functionButton.at(i);
  b->setIdentity(i);
  connect(b, SIGNAL(notifyFunctionStateChanged(int,bool)), this, SLOT(notifyFunctionStateChanged(int,bool)));
 }

 log = new Logger("FunctionPanel");
 QString ss = "border: 2px solid #8f8f91; border-radius: 6px;  min-width: 15px;";
 alt1Button = new JToggleButton();
 alt1Button->setStyleSheet(ss);
 alt2Button = new JToggleButton();
 alt2Button->setStyleSheet(ss);

 addressPanel = NULL; // to access roster infos
 keyReleased = true;
 mThrottle = NULL;
 setWindowTitle(tr("Function Panel"));
 //initGUI();
}

FunctionPanel::~FunctionPanel()
{
    delete ui;
}

/**
 * A JInternalFrame that contains buttons for each decoder function.
 */
///*public*/ class FunctionPanel extends JInternalFrame implements FunctionListener, java.beans.PropertyChangeListener, AddressListener
//{
/*public*/ /*static final*/ int FunctionPanel::NUM_FUNCTION_BUTTONS = 29;
/*public*/ /*static final*/ int FunctionPanel::NUM_FUNC_BUTTONS_INIT = 16;	//only show 16 function buttons at start

/*public*/ void FunctionPanel::destroy()
{
 if(addressPanel!=NULL)
  addressPanel->removeAddressListener((AddressListener*)this);
 if (mThrottle != NULL)
 {
  //mThrottle->removePropertyChangeListener((PropertyChangeListener*)this);
  disconnect(mThrottle, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
  mThrottle=NULL;
 }
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QList<FunctionButton*> FunctionPanel::getFunctionButtons() { return functionButton; }
#if 1
/**
 * Get notification that a function has changed state
 * @param functionNumber The function that has changed (0-9).
 * @param isSet True if the function is now active (or set).
 */
/*public*/ void FunctionPanel::notifyFunctionStateChanged(int functionNumber, bool isSet)
{
 if(mThrottle != NULL)
 {
  switch (functionNumber)
  {
   case 0: mThrottle->setF0(isSet); break;
   case 1: mThrottle->setF1(isSet); break;
   case 2: mThrottle->setF2(isSet); break;
   case 3: mThrottle->setF3(isSet); break;
   case 4: mThrottle->setF4(isSet); break;
   case 5: mThrottle->setF5(isSet); break;
   case 6: mThrottle->setF6(isSet); break;
   case 7: mThrottle->setF7(isSet); break;
   case 8: mThrottle->setF8(isSet); break;
   case 9: mThrottle->setF9(isSet); break;
   case 10: mThrottle->setF10(isSet); break;
   case 11: mThrottle->setF11(isSet); break;
   case 12: mThrottle->setF12(isSet); break;
   case 13: mThrottle->setF13(isSet); break;
   case 14: mThrottle->setF14(isSet); break;
   case 15: mThrottle->setF15(isSet); break;
   case 16: mThrottle->setF16(isSet); break;
   case 17: mThrottle->setF17(isSet); break;
   case 18: mThrottle->setF18(isSet); break;
   case 19: mThrottle->setF19(isSet); break;
   case 20: mThrottle->setF20(isSet); break;
   case 21: mThrottle->setF21(isSet); break;
   case 22: mThrottle->setF22(isSet); break;
   case 23: mThrottle->setF23(isSet); break;
   case 24: mThrottle->setF24(isSet); break;
   case 25: mThrottle->setF25(isSet); break;
   case 26: mThrottle->setF26(isSet); break;
   case 27: mThrottle->setF27(isSet); break;
   case 28: mThrottle->setF28(isSet); break;
    default: break;
  }
 }
}

/**
 * Get notification that a function's lockable status has changed.
 * @param functionNumber The function that has changed (0-28).
 * @param isLockable True if the function is now Lockable
 * (continuously active).
 */
/*public*/ void FunctionPanel::notifyFunctionLockableChanged(int functionNumber, bool isLockable)
{
    if (mThrottle==NULL) {
        // throttle can be NULL when loading throttle layout
        if (log->isDebugEnabled())log->debug("throttle pointer NULL in notifyFunctionLockableChanged");
        return;
    }

    switch (functionNumber)
    {
    case 0: mThrottle->setF0Momentary(!isLockable); break;
    case 1: mThrottle->setF1Momentary(!isLockable); break;
    case 2: mThrottle->setF2Momentary(!isLockable); break;
    case 3: mThrottle->setF3Momentary(!isLockable); break;
    case 4: mThrottle->setF4Momentary(!isLockable); break;
    case 5: mThrottle->setF5Momentary(!isLockable); break;
    case 6: mThrottle->setF6Momentary(!isLockable); break;
    case 7: mThrottle->setF7Momentary(!isLockable); break;
    case 8: mThrottle->setF8Momentary(!isLockable); break;
    case 9: mThrottle->setF9Momentary(!isLockable); break;
    case 10: mThrottle->setF10Momentary(!isLockable); break;
    case 11: mThrottle->setF11Momentary(!isLockable); break;
    case 12: mThrottle->setF12Momentary(!isLockable); break;
    case 13: mThrottle->setF13Momentary(!isLockable); break;
    case 14: mThrottle->setF14Momentary(!isLockable); break;
    case 15: mThrottle->setF15Momentary(!isLockable); break;
    case 16: mThrottle->setF16Momentary(!isLockable); break;
    case 17: mThrottle->setF17Momentary(!isLockable); break;
    case 18: mThrottle->setF18Momentary(!isLockable); break;
    case 19: mThrottle->setF19Momentary(!isLockable); break;
    case 20: mThrottle->setF20Momentary(!isLockable); break;
    case 21: mThrottle->setF21Momentary(!isLockable); break;
    case 22: mThrottle->setF22Momentary(!isLockable); break;
    case 23: mThrottle->setF23Momentary(!isLockable); break;
    case 24: mThrottle->setF24Momentary(!isLockable); break;
    case 25: mThrottle->setF25Momentary(!isLockable); break;
    case 26: mThrottle->setF26Momentary(!isLockable); break;
    case 27: mThrottle->setF27Momentary(!isLockable); break;
    case 28: mThrottle->setF28Momentary(!isLockable); break;
    default: break;
    }
}

/**
 * Enable or disable all the buttons
 */
/*public*/ void FunctionPanel::setEnabled(bool isEnabled)
{
    //super.setEnabled(isEnabled);
    for (int i=0; i < NUM_FUNCTION_BUTTONS; i++)
    {
        functionButton.at(i)->setEnabled(isEnabled);
    }
    alt1Button->setEnabled(isEnabled);
    alt2Button->setEnabled(isEnabled);
}

/*public*/ void FunctionPanel::setEnabled()
{
    setEnabled(mThrottle!=NULL);
}

/*public*/ void FunctionPanel::setAddressPanel(AddressPanel* addressPanel){
    this->addressPanel = addressPanel;

}

/*public*/ void FunctionPanel::saveFunctionButtonsToRoster (RosterEntry* rosterEntry)
{
 log->debug("saveFunctionButtonsToRoster");
 if (rosterEntry == NULL)
  return;
 for (int i=0; i < NUM_FUNCTION_BUTTONS; i++)
 {
  int functionNumber = functionButton.at(i)->getIdentity();
  QString text = functionButton.at(i)->getButtonLabel();
  bool lockable = functionButton.at(i)->getIsLockable();
  QString imagePath = functionButton.at(i)->getIconPath();
  QString imageSelectedPath = functionButton.at(i)->getSelectedIconPath();
  if (functionButton.at(i)->isDirty() && text!=(rosterEntry->getFunctionLabel(functionNumber)))
  {
   functionButton.at(i)->setDirty(false);
   if (text==(""))
    text = "";		// reset button text to default
   rosterEntry->setFunctionLabel(functionNumber, text);
  }
  if (rosterEntry->getFunctionLabel(functionNumber) != NULL && lockable != rosterEntry->getFunctionLockable(functionNumber))
  {
   rosterEntry->setFunctionLockable(functionNumber, lockable);
  }
  if (rosterEntry->getFunctionLabel(functionNumber) != NULL && imagePath!=NULL && imagePath.compare(rosterEntry->getFunctionImage(functionNumber))!=0)
  {
   rosterEntry->setFunctionImage(functionNumber, imagePath);
  }
  if (rosterEntry->getFunctionLabel(functionNumber) != NULL && imageSelectedPath!=NULL && imageSelectedPath.compare(rosterEntry->getFunctionSelectedImage(functionNumber))!=0)
  {
   rosterEntry->setFunctionSelectedImage(functionNumber, imageSelectedPath);
  }
 }
 Roster::getDefault()->writeRoster();
}

/**
 * Place and initialize all the buttons.
 */
/*private*/ void FunctionPanel::initGUI()
{
 mainPanel = new QWidget();
    //mainPanel->removeAll();
    //setContentPane(mainPanel);
 setWidget(mainPanel);
    //setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
 FlowLayout* mainPanelLayout;
 mainPanel->setLayout(mainPanelLayout = new FlowLayout(/*FlowLayout::Center,*/5,5));
 functionButton = QList< FunctionButton*>();//[NUM_FUNCTION_BUTTONS];
 for (int i=0; i<NUM_FUNCTION_BUTTONS; i++)
 {
  functionButton.append(new FunctionButton());
  // place function button 0 at the button of the panel
  if (i > 0)
  {
   mainPanelLayout->addWidget(functionButton.at(i));
   if (i >= NUM_FUNC_BUTTONS_INIT)
   {
    functionButton.at(i)->setVisible(false);
   }
  }
 }
 alt1Button->setText("*");
 alt1Button->resize( QSize(FunctionButton::BUT_WDTH,FunctionButton::BUT_HGHT));
 alt1Button->setToolTip(tr("Push_for_alternate_set_of_function_keys"));
// alt1Button.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            buttonActionCmdPerformed();
//        }
//    });
 connect(alt1Button, SIGNAL(clicked(bool)), this, SLOT(buttonActionCmdPerformed()));
 mainPanelLayout->addWidget(alt1Button);

 mainPanelLayout->addWidget(functionButton.at(0));

 alt2Button->setText("#");
 alt2Button->resize( QSize(FunctionButton::BUT_WDTH,FunctionButton::BUT_HGHT));
 alt2Button->setToolTip("currently_not_used");
 mainPanelLayout->addWidget(alt2Button);

 resetFnButtons();
 // TODO: is this necessary?
 //KeyListenerInstaller.installKeyListenerOnAllComponents(	new FunctionButtonKeyListener(), this);
}


// activated when alt1Button is pressed or released
/*public*/ void FunctionPanel::buttonActionCmdPerformed()
{
 // swap f3 through f15 with f16 through f28
 for (int i = 3; i < NUM_FUNCTION_BUTTONS; i++)
 {
  if (alt1Button->isSelected())
  {
   if (i < NUM_FUNC_BUTTONS_INIT)
   {
    functionButton.at(i)->setVisible(false);
   }
   else
   {
    functionButton.at(i)->setVisible(functionButton.at(i)->getDisplay());
   }

  }
  else
  {
   if (i < NUM_FUNC_BUTTONS_INIT)
   {
    functionButton.at(i)->setVisible(functionButton.at(i)->getDisplay());
   } else
   {
    functionButton.at(i)->setVisible(false);
   }
  }
 }
}
#endif
/**
 * Make sure that all function buttons are being displayed
 * if buttons label loaded from a roster entry, update buttons accordingly
 */
/*public*/ void FunctionPanel::resetFnButtons()
{
 // Buttons names, ids,
 for (int i=0; i < NUM_FUNCTION_BUTTONS; i++)
 {
  functionButton.at(i)->setIdentity(i);
  functionButton.at(i)->setFunctionListener((FunctionListener*)this);
  if(i < 3)
   functionButton.at(i)->setButtonLabel(("F"+QString::number(i)));
  else
   functionButton.at(i)->setButtonLabel("F"+QString::number(i));

  functionButton.at(i)->setDisplay(true);
  if ((i<3)
            && ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()
            && ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingFunctionIcon())
  switch (i)
  {
   case 0:
    functionButton.at(i)->setIconPath("icons/throttles/Light.png");
    functionButton.at(i)->setSelectedIconPath("icons/throttles/LightOn.png");
    break;
   case 1:
    functionButton.at(i)->setIconPath("icons/throttles/Bell.png");
    functionButton.at(i)->setSelectedIconPath("icons/throttles/BellOn.png");
    break;
   case 2:
    functionButton.at(i)->setIconPath("icons/throttles/Horn.png");
    functionButton.at(i)->setSelectedIconPath("icons/throttles/HornOn.png");
    break;
   default: break;
  }
  else
  {
   functionButton.at(i)->setIconPath("");
   functionButton.at(i)->setSelectedIconPath(NULL);
  }
  functionButton.at(i)->updateLnF();

  // always display f0, F1 and F2
   if (i<3)
    functionButton.at(i)->setVisible(true);
 }
 functionButton.at(0)->setKeyCode(Qt::KeypadModifier+Qt::Key_0);
 functionButton.at(1)->setKeyCode(Qt::KeypadModifier+Qt::Key_1);
 functionButton.at(2)->setKeyCode(Qt::KeypadModifier+Qt::Key_2);
 functionButton.at(3)->setKeyCode(Qt::KeypadModifier+Qt::Key_3);
 functionButton.at(4)->setKeyCode(Qt::KeypadModifier+Qt::Key_4);
 functionButton.at(5)->setKeyCode(Qt::KeypadModifier+Qt::Key_5);
 functionButton.at(6)->setKeyCode(Qt::KeypadModifier+Qt::Key_6);
 functionButton.at(7)->setKeyCode(Qt::KeypadModifier+Qt::Key_7);
 functionButton.at(8)->setKeyCode(Qt::KeypadModifier+Qt::Key_8);
 functionButton.at(9)->setKeyCode(Qt::KeypadModifier+Qt::Key_9);
 functionButton.at(10)->setKeyCode(110); // numpad decimal (f10 button causes problems)
 functionButton.at(11)->setKeyCode(Qt::Key_F11);
 functionButton.at(12)->setKeyCode(Qt::Key_F12);
 functionButton.at(13)->setKeyCode(Qt::Key_F13);
 functionButton.at(14)->setKeyCode(Qt::Key_F14);
 functionButton.at(15)->setKeyCode(Qt::Key_F15);
 functionButton.at(16)->setKeyCode(Qt::Key_F16);
 functionButton.at(17)->setKeyCode(Qt::Key_F17);
 functionButton.at(18)->setKeyCode(Qt::Key_F18);
 functionButton.at(19)->setKeyCode(Qt::Key_F19);
 functionButton.at(20)->setKeyCode(Qt::Key_F20);
 functionButton.at(21)->setKeyCode(Qt::Key_F21);
 functionButton.at(22)->setKeyCode(Qt::Key_F22);
 functionButton.at(23)->setKeyCode(Qt::Key_F23);
 functionButton.at(24)->setKeyCode(Qt::Key_F24);
 functionButton.at(25)->setKeyCode(Qt::Key_F25);			// keycodes 25 - 28 don't exist in KeyEvent
 functionButton.at(26)->setKeyCode(Qt::Key_F26);
 functionButton.at(27)->setKeyCode(Qt::Key_F27);
 functionButton.at(28)->setKeyCode(Qt::Key_F28);
    // Make F2 (Horn) momentary
 functionButton.at(2)->setIsLockable(false);

 alt1Button->setVisible(true);
 alt1Button->setEnabled(true);
 alt2Button->setVisible(true);
 buttonActionCmdPerformed();
 setFnButtons();
}

// Update buttons value from slot + load buttons definition from roster if any
/*private*/ void FunctionPanel::setFnButtons()
{
 if (mThrottle != NULL)
 {
  if (addressPanel == NULL) return;
  RosterEntry* rosterEntry = addressPanel->getRosterEntry();
  if ((rosterEntry != NULL) && (log->isDebugEnabled()))
   log->debug("RosterEntry found: "+rosterEntry->getId());
  int maxi = 0;	// the number of function buttons defined for this entry
  for (int i = 0; i < FunctionPanel::NUM_FUNCTION_BUTTONS; i++)
  {
//   try
//   {
   functionButton.at(i)->setIdentity(i); // full reset of function
   // buttons in this case
//   Method getter = mThrottle->getClass()
//                .getMethod("getF" + i, (Class[]) NULL);
//                bool state =  getter.invoke(mThrottle,
//                        (Object[]) NULL);
   bool state;
   switch(i)
   {
   case 0:
    state = mThrottle->getF0();
   case 1:
    state = mThrottle->getF1();
    break;
   case 2:
    state = mThrottle->getF2();
    break;
   case 3:
    state = mThrottle->getF3();
    break;
   case 4:
    state = mThrottle->getF4();
    break;
   case 5:
    state = mThrottle->getF5();
    break;
   case 6:
    state = mThrottle->getF6();
    break;
   case 7:
    state = mThrottle->getF7();
    break;
   case 8:
    state = mThrottle->getF8();
    break;
   case 9:
    state = mThrottle->getF9();
    break;
   case 10:
    state = mThrottle->getF10();
    break;
   case 11:
    state = mThrottle->getF11();
    break;
   case 12:
    state = mThrottle->getF12();
    break;
   case 13:
    state = mThrottle->getF13();
    break;
   case 14:
    state = mThrottle->getF14();
    break;
   case 15:
    state = mThrottle->getF15();
    break;
   case 16:
    state = mThrottle->getF16();
    break;
   case 17:
    state = mThrottle->getF17();
    break;
   case 18:
    state = mThrottle->getF18();
    break;
   case 19:
    state = mThrottle->getF19();
    break;
   case 20:
    state = mThrottle->getF20();
    break;
   case 21:
    state = mThrottle->getF21();
    break;
   case 22:
    state = mThrottle->getF22();
    break;
   case 23:
    state = mThrottle->getF23();
    break;
   case 24:
    state = mThrottle->getF24();
    break;
   case 25:
    state = mThrottle->getF25();
    break;
   case 26:
    state = mThrottle->getF26();
    break;
   case 27:
    state = mThrottle->getF27();
    break;
   case 28:
    state = mThrottle->getF28();
    break;
   default:
     Q_ASSERT(false);
   }

   functionButton.at(i)->setState(state); // reset button state
//   }
//   catch (NoSuchMethodException ex1)
//   {
//    log->warn("Exception in notifyThrottleFound: " + ex1);
//   } catch (IllegalAccessException ex2) {
//                log->warn("Exception in notifyThrottleFound: " + ex2);
//   } catch (InvocationTargetException ex3) {
//                log->warn("Exception in notifyThrottleFound: " + ex3);
//   }
   if (rosterEntry!=NULL)
   { // from here, update button text with roster data
    QString text = rosterEntry->getFunctionLabel(i);
    if (text != "")
    {
     functionButton.at(i)->setDisplay(true);
     functionButton.at(i)->setButtonLabel(text);
     if ((ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle() )
                            && (ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingFunctionIcon()))
     {
      functionButton.at(i)->setIconPath(rosterEntry->getFunctionImage(i));
      functionButton.at(i)->setSelectedIconPath(rosterEntry->getFunctionSelectedImage(i));
     }
     else
     {
      functionButton.at(i)->setIconPath(NULL);
      functionButton.at(i)->setSelectedIconPath(NULL);
     }
     functionButton.at(i)->setIsLockable(rosterEntry->getFunctionLockable(i));
     functionButton.at(i)->updateLnF();
     if (maxi < NUM_FUNC_BUTTONS_INIT)
      functionButton.at(i)->setVisible(true);
     maxi++; // bump number of buttons shown
    }
    else if (ThrottleFrameManager::instance()->getThrottlesPreferences()
                        ->isUsingExThrottle()
                        && ThrottleFrameManager::instance()->getThrottlesPreferences()
                        ->isHidingUndefinedFuncButt())
    {
     functionButton.at(i)->setDisplay(false);
     functionButton.at(i)->setVisible(false);
    }
   }
  }
  // hide alt buttons if not required
  if ((rosterEntry!=NULL) && (maxi < NUM_FUNC_BUTTONS_INIT
                && ThrottleFrameManager::instance()
                ->getThrottlesPreferences()->isUsingExThrottle()
                && ThrottleFrameManager::instance()
                ->getThrottlesPreferences()
                ->isHidingUndefinedFuncButt()))
  {
   alt1Button->setVisible(false);
   alt2Button->setVisible(false);
  }
 }
}

/**
 * A KeyAdapter that listens for the keys that work the function buttons
 *
 * @author glen
 * @version $Revision: 22216 $
 */
//class FunctionButtonKeyListener :  KeyAdapter {
//    /*private*/ bool keyReleased = true;

/**
 *  Description of the Method
 *
 * @param  e  Description of the Parameter
 */
/*public*/ void FunctionPanel::keyPressEvent(QKeyEvent* e)
{
    if (keyReleased) {
        for (int i=0; i<NUM_FUNCTION_BUTTONS; i++) {
            if ( functionButton.at(i)->checkKeyCode(e->key()) )
                functionButton.at(i)->changeState(!functionButton.at(i)->isSelected());
        }
    }
    keyReleased = false;
}

/*public*/ void FunctionPanel::keyReleaseEvent(QKeyEvent* e)
{
 for (int i=0; i<NUM_FUNCTION_BUTTONS; i++)
 {
  if ( (functionButton.at(i)->checkKeyCode(e->key())) && (!functionButton.at(i)->getIsLockable()) )
            functionButton.at(i)->changeState(!functionButton.at(i)->isSelected());
 }
 keyReleased = true;
}
//};

// update the state of this panel if any of the properties change
/*public*/ void FunctionPanel::propertyChange(PropertyChangeEvent* e)
{
 for(int i=0;i<=28;i++)
 {
  if (e->getPropertyName()==("F"+QString::number(i)))
  {
   bool function= e->getNewValue().toBool();
   functionButton.at(i)->setState(function);
   break; // stop the loop, only one function property
          // will be matched.
  }
  else if (e->getPropertyName()==("F"+QString::number(i)+"Momentary"))
  {
   bool lockable=!(e->getNewValue().toBool());
   functionButton.at(i)->setIsLockable(lockable);
   break; // stop the loop, only one function property
          // will be matched.
  }
 }
}

/**
 * Collect the prefs of this object into XML Element
 * <ul>
 * <li> Window prefs
 * <li> Each button has id, text, lock state.
 * </ul>
 * @return the XML of this object.
 */
/*public*/ QDomElement FunctionPanel::getXml()
{
 QDomDocument doc;
    QDomElement me = doc.createElement("FunctionPanel");
#if 1
    //QDomNodeList children =  QDomNodeList(1+FunctionPanel::NUM_FUNCTION_BUTTONS);
    //children.add(WindowPreferences::getPreferences(this));
    me.appendChild(WindowPreferences::getPreferences(this));
    for (int i=0; i<FunctionPanel::NUM_FUNCTION_BUTTONS; i++)
        //children.add(functionButton.at(i)->getXml());
     me.appendChild(functionButton.at(i)->getXml());
    //me.setContent(children);
#endif
    return me;
}

/**
 * Set the preferences based on the XML Element.
 * <ul>
 * <li> Window prefs
 * <li> Each button has id, text, lock state.
 * </ul>
 * @param e The Element for this object.
 */
//@SuppressWarnings("unchecked")
/*public*/ void FunctionPanel::setXml(QDomElement e)
{
    QDomElement window = e.firstChildElement("window");
#if 0
    WindowPreferences.setPreferences(this, window);

    java.util.List<Element> buttonElements =
        e.getChildren("FunctionButton");

    if (buttonElements != NULL && buttonElements.size()>0) {
        int i = 0;
        for (java.util.Iterator<Element> iter =
            buttonElements.iterator(); iter.hasNext();)
        {
            Element buttonElement = iter.next();
            functionButton.at(i++].setXml(buttonElement);
        }
    }
#endif
}

/**
 * Get notification that a throttle has been found as we requested.
 * Use reflection to find the proper getF? method for each button.
 *
 * @param t An instantiation of the DccThrottle with the address requested.
 */
/*public*/ void FunctionPanel::notifyAddressThrottleFound(DccThrottle* t)
{
 if (log->isDebugEnabled()) log->debug("Throttle found");
 mThrottle = t;
 setEnabled(true);
 //mThrottle->addPropertyChangeListener(this);
 AbstractThrottle* at = (AbstractThrottle*)t;
 connect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 setFnButtons();
 connect(addressPanel, SIGNAL(notifyAddressReleased(LocoAddress*)), this, SLOT(notifyAddressReleased(LocoAddress*)));
}

/*public*/ void FunctionPanel::notifyAddressReleased(LocoAddress* la)
{
 if (log->isDebugEnabled()) log->debug("Throttle released");
 setEnabled(false);
 if (mThrottle != NULL)
 {
  //mThrottle->removePropertyChangeListener(this);
  AbstractThrottle* at = (AbstractThrottle*)mThrottle;
  connect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 mThrottle = NULL;
}

/*public*/ void FunctionPanel::notifyAddressChosen(LocoAddress* l) {
}

/*public*/ void FunctionPanel::notifyConsistAddressChosen(int newAddress, bool isLong) {
}

/*public*/ void FunctionPanel::notifyConsistAddressReleased(int address, bool isLong) {
}

/*public*/ void FunctionPanel::notifyConsistAddressThrottleFound(DccThrottle* throttle) {
}

