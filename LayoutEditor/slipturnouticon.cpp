#include "slipturnouticon.h"
#include "abstractturnout.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "namedicon.h"
#include <QAction>
#include <QMenu>
#include "editor.h"
#include "slipiconadder.h"
#include "slipturnouttextedit.h"

//SlipTurnoutIcon::SlipTurnoutIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}
/**
 * An icon to display a status of a Slip, either Single or Double.<P>
 * This responds to only KnownState, leaving CommandedState to some other
 * graphic representation later.
 * <P>
 * A click on the icon will command a state change. Specifically, it
 * will set the CommandedState to the opposite (THROWN vs CLOSED) of
 * the current KnownState.
 *<P>
 * Note: lower west to lower east icon is used for storing the slip icon, in a single slip,
 * even if the slip is set for upper west to upper east.
 * <p>
 * With a 3-Way point we use the following translations
 *<ul>
 * <li>lower west to upper east - to upper exit
 * <li>upper west to lower east - to middle exit
 * <li>lower west to lower east - to lower exit
 * <li>west Turnout - First Turnout
 * <li>east Turnout - Second Turnout
 * <li>singleSlipRoute - translates to which exit the first turnout goes to
 * <li>true if upper, or false if lower
 * </ul>
 *<P>
 * Based upon the TurnoutIcon by Bob Jacobsen
 * @author Kevin Dickerson Copyright (c) 2010
 * @version $Revision: 22320 $
 */

///*public*/ class SlipTurnoutIcon extends PositionableLabel implements java.beans.PropertyChangeListener {

/*static*/ bool SlipTurnoutIcon::LOWERWESTtoLOWEREAST = false;
/*static*/ bool SlipTurnoutIcon::UPPERWESTtoUPPEREAST = true;

/*public*/ SlipTurnoutIcon::SlipTurnoutIcon(Editor* editor, QObject */*parent*/) : PositionableLabel(new NamedIcon("resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif",
                                                                                                               "resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif"), editor)
{
    // super ctor call to make sure this is an icon label
    //super(new NamedIcon("resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif",
//                        "resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif"), editor);
 namedTurnoutWest = nullptr;
 namedTurnoutWestLower = nullptr;
 namedTurnoutEast = nullptr;
 namedTurnoutEastLower = nullptr;
 debug = false;
 log = new Logger("SlipTurnoutIcon");
 turnoutType = DOUBLESLIP;
 singleSlipRoute = false;
 // display icons
 lowerWestToUpperEastLName = "resources/icons/smallschematics/tracksegments/os-slip-lower-west-upper-east.gif";
 lowerWestToUpperEast = new NamedIcon(lowerWestToUpperEastLName, lowerWestToUpperEastLName);
 upperWestToLowerEastLName = "resources/icons/smallschematics/tracksegments/os-slip-upper-west-lower-east.gif";
 upperWestToLowerEast = new NamedIcon(upperWestToLowerEastLName, upperWestToLowerEastLName);
 lowerWestToLowerEastLName = "resources/icons/smallschematics/tracksegments/os-slip-lower-west-lower-east.gif";
 lowerWestToLowerEast = new NamedIcon(lowerWestToLowerEastLName, lowerWestToLowerEastLName);
 upperWestToUpperEastLName = "resources/icons/smallschematics/tracksegments/os-slip-upper-west-upper-east.gif";
 upperWestToUpperEast = new NamedIcon(upperWestToUpperEastLName, upperWestToUpperEastLName);
 inconsistentLName = "resources/icons/smallschematics/tracksegments/os-slip-error-full.gif";
 inconsistent = new NamedIcon(inconsistentLName, inconsistentLName);
 unknownLName = "resources/icons/smallschematics/tracksegments/os-slip-unknown-full.gif";
 unknown = new NamedIcon(unknownLName, unknownLName);
 tristate = false;
 lowerWestToUpperEastText = tr("Lower West To Upper East");
 upperWestToLowerEastText = tr("Upper West To Lower East");
 lowerWestToLowerEastText = tr("Lower West To Lower East");
 upperWestToUpperEastText = tr("Upper West To Upper East");
 tristateItem = nullptr;
 firstStraight = false;
 _turnoutSetting = new QHash <Turnout*, int>();
 busy = false;
 _iconEditor = nullptr;

 _control = true;
 displayState(turnoutState());
 debug = log->isDebugEnabled();
 setPopupUtility(nullptr);
}

/**
 * Attached a named turnout to this display item
 * @param pName Used as a system/user name to lookup the turnout object
 * @param turn is used to determine which turnout position this is for.
 * 0x01 - West
 * 0x02 - East
 * 0x04 - Lower West
 * 0x06 - Upper East
 */
 /*public*/ void SlipTurnoutIcon::setTurnout(QString pName, int turn)
{
 if (InstanceManager::turnoutManagerInstance()!=nullptr)
 {
  Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
             provideTurnout(pName);
  if (turnout != nullptr)
  {
   setTurnout(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, turnout), turn);
  }
  else
  {
   log->error("Turnout '"+pName+"' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No TurnoutManager for this protocol, icon won't see changes");
 }
}

/**
 * Attached a namedBean Handle turnout to this display item
 * @param to Used as the NamedBeanHandle to lookup the turnout object
 * @param turn is used to determine which turnout position this is for.
 * <ul>
 * <li>0x01 - West
 * <li>0x02 - East
 * <li>0x04 - Lower West
 * <li>0x06 - Upper East
 * </ul>
 */
/*public*/ void SlipTurnoutIcon::setTurnout(NamedBeanHandle<Turnout*>* to, int turn)
{
 switch(turn)
 {
  case WEST:
   if (namedTurnoutWest != nullptr)
   {
     getTurnout(WEST)->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(WEST);
//    disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   namedTurnoutWest = to;
   if (namedTurnoutWest != nullptr)
   {
    displayState(turnoutState());
    getTurnout(WEST)->addPropertyChangeListener((PropertyChangeListener*)this, namedTurnoutWest->getName(), "Panel Editor Turnout");
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(WEST);
//   connect(to->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   break;
  case EAST:
   if (namedTurnoutEast != nullptr)
   {
    getTurnout(EAST)->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(EAST);
//    disconnect(to->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

   }
   namedTurnoutEast = to;
   if (namedTurnoutEast != nullptr)
   {
    displayState(turnoutState());
    getTurnout(EAST)->addPropertyChangeListener((PropertyChangeListener*)this, namedTurnoutEast->getName(), "Panel Editor Turnout");
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(EAST);
//    connect(to->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

   }
   break;
  case LOWERWEST:
   if (namedTurnoutWestLower != nullptr)
   {
    getTurnout(LOWERWEST)->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(LOWERWEST);
//    disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   namedTurnoutWestLower = to;
   if (namedTurnoutWestLower != nullptr)
   {
    displayState(turnoutState());
    getTurnout(LOWERWEST)->addPropertyChangeListener((PropertyChangeListener*)this, namedTurnoutWestLower->getName(), "Panel Editor Turnout");
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(LOWERWEST);
//    connect(to->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

   }
   break;
  case LOWEREAST:
   if (namedTurnoutEastLower != nullptr)
   {
    getTurnout(LOWEREAST)->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(LOWEREAST);
//    disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   namedTurnoutEastLower = to;
   if (namedTurnoutEastLower != nullptr)
   {
    //displayState(turnoutState());
    getTurnout(LOWEREAST)->addPropertyChangeListener((PropertyChangeListener*)this, namedTurnoutEastLower->getName(), "Panel Editor Turnout");
//    AbstractTurnout* to = (AbstractTurnout*)getTurnout(LOWEREAST);
//    connect(to->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   break;
 }
}

/**
 * Constant used to referred to the Turnout address configured to operate the
 * west (or first for a three way) of the Turnout::
 */
///*public*/ static final int WEST = 0x01;

/**
 * Constant used to referred to the Turnout address configured to operate the
 * east (or second for a three way) of the Turnout::
 */
///*public*/ static final int EAST = 0x02;

/**
 * Constant used for a scissor crossing using 4 turnout address, and refers
 * to the turnout located at the lower west.
 */
///*public*/ static final int LOWERWEST = 0x04;

/**
 * Constant used for a scissor crossing using 4 turnout address, and refers
 * to the turnout located at the lower east.
 */
///*public*/ static final int LOWEREAST = 0x06;

/**
 * Constant used to refer to a Double Slip Configuration.
 */
///*public*/ static final int DOUBLESLIP = 0x00;

/**
 * Constant used to refer to a Single Slip Configuration.
 */
///*public*/ static final int SINGLESLIP = 0x02;

/**
 * Constant used to refer to a Three Way Turnout Configuration.
 */
///*public*/ static final int THREEWAY = 0x04;

 /**
 * Constant used to refer to a Scissor (Double Crossover) Configuration.
 */
///*public*/ static final int SCISSOR = 0x08;

/**
* Sets the type of turnout configuration which is being used
* @param slip - valid values are
* <ul>
* <li>0x00 - Double Slip
* <li>0x02 - Single Slip
* <li>0x04 - Three Way Turnout
* <li>0x08 - Scissor Crossing
* </ul>
*/
/*public*/ void SlipTurnoutIcon::setTurnoutType(int slip){
    turnoutType = slip;
}

/*public*/ int SlipTurnoutIcon::getTurnoutType() { return turnoutType; }


/**
* Single Slip Route, determines if the slip route is from
* upper west to upper east (true) or lower west to lower east (false)
* This also doubles up for the three way and determines if the
* first turnout routes to the upper (true) or lower (false) exit point.
* returns
* <p>
* In a Scissor crossing this returns true if only two turnout address are
* required to set the crossing or false if four turnout address are required
*/

/*public*/ bool SlipTurnoutIcon::getSingleSlipRoute() { return singleSlipRoute; }

/*public*/ void SlipTurnoutIcon::setSingleSlipRoute(bool route) {
    singleSlipRoute = route;
}

/**
* Returns the turnout located at the position specified.
* @param turn See constants for EAST, WEST, LOWEREAST, LOWERWEST
*/

/*public*/ Turnout* SlipTurnoutIcon::getTurnout(int turn) {
    switch(turn) {
        case EAST : return namedTurnoutEast->getBean();
        case WEST : return namedTurnoutWest->getBean();
        case LOWEREAST : return namedTurnoutEastLower->getBean();
        case LOWERWEST : return namedTurnoutWestLower->getBean();
        default: return nullptr;
    }
    /*if(west)
        return namedTurnoutWest.getBean();
    return namedTurnoutEast.getBean();*/
}

/*public*/ NamedBeanHandle <Turnout*>* SlipTurnoutIcon::getNamedTurnout(int turn) {
    switch(turn) {
        case EAST : return namedTurnoutEast;
        case WEST : return namedTurnoutWest;
        case LOWEREAST : return namedTurnoutEastLower;
        case LOWERWEST : return namedTurnoutWestLower;
        default : return nullptr;
    }
}

/*
    Note: lower west to lower east icon is used for storing the slip icon, in a single slip,
    even if the slip is set for upper west to upper east.

    With a 3-Way point we use the following translations

    lower west to upper east - to upper exit
    upper west to lower east - to middle exit
    lower west to lower east - to lower exit

    With a Scissor Crossing we use the following to represent straight
    lower west to lower east
    upper west to upper east
*/



/*public*/ NamedIcon* SlipTurnoutIcon::getLowerWestToUpperEastIcon() { return lowerWestToUpperEast; }
/*public*/ void SlipTurnoutIcon::setLowerWestToUpperEastIcon(NamedIcon* i) {
    lowerWestToUpperEast = i;
    displayState(turnoutState());
}

/*public*/ NamedIcon* SlipTurnoutIcon::getUpperWestToLowerEastIcon() { return upperWestToLowerEast; }
/*public*/ void SlipTurnoutIcon::setUpperWestToLowerEastIcon(NamedIcon* i) {
    upperWestToLowerEast = i;
    displayState(turnoutState());
}

/*public*/ NamedIcon* SlipTurnoutIcon::getLowerWestToLowerEastIcon() { return lowerWestToLowerEast; }
/*public*/ void SlipTurnoutIcon::setLowerWestToLowerEastIcon(NamedIcon* i) {
    lowerWestToLowerEast = i;
    displayState(turnoutState());
    /*Only a double slip needs the fourth icon, we therefore set the upper west to upper east icon
    to be the same as the lower west to upper wast icon*/
    if(turnoutType!=DOUBLESLIP)
        setUpperWestToUpperEastIcon(i);
}

/*public*/ NamedIcon* SlipTurnoutIcon::getUpperWestToUpperEastIcon() { return upperWestToUpperEast; }
/*public*/ void SlipTurnoutIcon::setUpperWestToUpperEastIcon(NamedIcon* i) {
    upperWestToUpperEast = i;
    displayState(turnoutState());
}

/*public*/ NamedIcon* SlipTurnoutIcon::getInconsistentIcon() { return inconsistent; }
/*public*/ void SlipTurnoutIcon::setInconsistentIcon(NamedIcon* i) {
    inconsistent = i;
    displayState(turnoutState());
}

/*public*/ NamedIcon* SlipTurnoutIcon::getUnknownIcon() { return unknown; }
/*public*/ void SlipTurnoutIcon::setUnknownIcon(NamedIcon* i) {
    unknown = i;
    displayState(turnoutState());
}

//@Override
/*public*/ int SlipTurnoutIcon::maxHeight() {
    return qMax(
            qMax( (lowerWestToUpperEast!=nullptr) ? lowerWestToUpperEast->getIconHeight() : 0,
                    (upperWestToLowerEast!=nullptr) ? upperWestToLowerEast->getIconHeight() : 0),
            qMax(
            qMax( (upperWestToUpperEast!=nullptr) ? upperWestToUpperEast->getIconHeight() : 0,
                    (lowerWestToLowerEast!=nullptr) ? lowerWestToLowerEast->getIconHeight() : 0),
            qMax((unknown!=nullptr) ? unknown->getIconHeight() : 0,
                    (inconsistent!=nullptr) ? inconsistent->getIconHeight() : 0))
        );
}
//@Override
/*public*/ int SlipTurnoutIcon::maxWidth() {
    return qMax(
            qMax( (lowerWestToUpperEast!=nullptr) ? lowerWestToUpperEast->getIconWidth() : 0,
                    (upperWestToLowerEast!=nullptr) ? upperWestToLowerEast->getIconWidth() : 0),
            qMax(
            qMax( (upperWestToUpperEast!=nullptr) ? upperWestToUpperEast->getIconWidth() : 0,
                    (lowerWestToLowerEast!=nullptr) ? lowerWestToLowerEast->getIconWidth() : 0),
            qMax((unknown!=nullptr) ? unknown->getIconWidth() : 0,
                    (inconsistent!=nullptr) ? inconsistent->getIconWidth() : 0))
        );
}

/**
 * Get current state of attached turnouts
 * This adds the two turnout states together, however for the second turnout
 * configured it will add 1 to the Closed state and 3 to the Thrown state.
 * This helps to indentify which turnout is thrown and/or closed.
 * <p>
 * For a Scissor crossing that uses four turnouts, the code simply checks to ensure
 * that diagonally opposite turnouts are set the same.
 * If not is will return an Inconsistent state.
 * <p>
 * If any turnout that has either not been configured or in an Unknown or
 * Inconsistent state, the code will return the state UNKNOWN or INCONSISTENT.
 * @return A state variable from a Turnout, e.g. Turnout::CLOSED
 */
int SlipTurnoutIcon::turnoutState() {
    //Need to rework this!
    //might be as simple as adding the two states together.
    //if either turnout is not entered then the state to report
    //back will be unknown
    int state=0x00;
    if (namedTurnoutWest != nullptr){
        if (((AbstractTurnout*)getTurnout(WEST))->getKnownState()==Turnout::UNKNOWN)
            return Turnout::UNKNOWN;
        if (((AbstractTurnout*)getTurnout(WEST))->getKnownState()==Turnout::INCONSISTENT)
            return Turnout::INCONSISTENT;
        state =+ ((AbstractTurnout*)getTurnout(WEST))->getKnownState();
    }
    else return Turnout::UNKNOWN;
    //We add 1 to the value of the west turnout to help identify the states for both turnouts
    if (namedTurnoutEast != nullptr) {
        if (((AbstractTurnout*)getTurnout(EAST))->getKnownState()==Turnout::UNKNOWN)
            return Turnout::UNKNOWN;
        if (((AbstractTurnout*)getTurnout(EAST))->getKnownState()==Turnout::INCONSISTENT)
            return Turnout::INCONSISTENT;
        if (((AbstractTurnout*)getTurnout(EAST))->getKnownState()==Turnout::CLOSED)
            state = state + (((AbstractTurnout*)getTurnout(EAST))->getKnownState() +1);
        if (((AbstractTurnout*)getTurnout(EAST))->getKnownState()==Turnout::THROWN)
            state = state + (((AbstractTurnout*)getTurnout(EAST))->getKnownState() +3);
    }
    else return Turnout::UNKNOWN;
    if ((turnoutType==SCISSOR) && (!singleSlipRoute)){
        //We simply need to check that the opposite turnout is set the same
        if (namedTurnoutEastLower!=nullptr){
            if (((AbstractTurnout*)getTurnout(LOWEREAST))->getKnownState()==Turnout::UNKNOWN)
                return Turnout::UNKNOWN;
            if (((AbstractTurnout*)getTurnout(LOWEREAST))->getKnownState()==Turnout::INCONSISTENT)
                return Turnout::INCONSISTENT;
        } else return Turnout::UNKNOWN;
        if (namedTurnoutWestLower!=nullptr){
            if (((AbstractTurnout*)getTurnout(LOWERWEST))->getKnownState()==Turnout::UNKNOWN)
                return Turnout::UNKNOWN;
            if (((AbstractTurnout*)getTurnout(LOWERWEST))->getKnownState()==Turnout::INCONSISTENT)
                return Turnout::INCONSISTENT;
        } else return Turnout::UNKNOWN;

        if(((AbstractTurnout*)getTurnout(LOWEREAST))->getKnownState()!=((AbstractTurnout*)getTurnout(WEST))->getKnownState()){
            return Turnout::INCONSISTENT;
        }
        if(((AbstractTurnout*)getTurnout(LOWERWEST))->getKnownState()!=((AbstractTurnout*)getTurnout(EAST))->getKnownState()){
            return Turnout::INCONSISTENT;
        }
    }

    return state;
}

// update icon as state of turnout changes
/*public*/ void SlipTurnoutIcon::propertyChange(PropertyChangeEvent* e) {
    if (log->isDebugEnabled())
        log->debug("property change: " + getNameString() + " " + e->getPropertyName() + " is now "
                + e->getNewValue().toString());

    // when there's feedback, transition through inconsistent icon for better
    // animation
    if (getTristate()
            && (((AbstractTurnout*)getTurnout(WEST))->getFeedbackMode() != Turnout::DIRECT)
            && (e->getPropertyName()==("CommandedState")))
    {
        if ((((AbstractTurnout*)getTurnout(WEST))->getCommandedState() != ((AbstractTurnout*)getTurnout(WEST))->getKnownState())
            || (((AbstractTurnout*)getTurnout(WEST))->getCommandedState() != ((AbstractTurnout*)getTurnout(WEST))->getKnownState())){
            int now = Turnout::INCONSISTENT;
            displayState(now);
        }
        // this takes care of the quick double click
        if ((((AbstractTurnout*)getTurnout(WEST))->getCommandedState() == ((AbstractTurnout*)getTurnout(WEST))->getKnownState())
            || (((AbstractTurnout*)getTurnout(EAST))->getCommandedState() == ((AbstractTurnout*)getTurnout(EAST))->getKnownState())) {
            displayState(turnoutState());
        }
    }

    if (e->getPropertyName()==("KnownState")) {
        displayState(turnoutState());
    }
}

/*public*/ QString SlipTurnoutIcon::getNameString() {
    QString name;
    if (namedTurnoutWest == nullptr) name = tr("Not Connected");
    else name = namedTurnoutWest->getName();
    if (namedTurnoutEast != nullptr)
        name = name + " " + namedTurnoutEast->getName();
    if ((getTurnoutType()==SCISSOR) && (!getSingleSlipRoute())){
        if (namedTurnoutWestLower != nullptr)
            name = name + " " + namedTurnoutWestLower->getName();
        if (namedTurnoutEastLower != nullptr)
            name = name + " " + namedTurnoutEastLower->getName();
    }
    return name;
}

/*public*/ void SlipTurnoutIcon::setTristate(bool set)
{
 tristate = set;
}
/*public*/ bool SlipTurnoutIcon::getTristate() { return tristate; }

void SlipTurnoutIcon::addTristateEntry(QMenu* popup)
{
 tristateItem = new QAction(tr("Tristate"),this);
 tristateItem->setCheckable(true);
 tristateItem->setChecked(getTristate());
 popup->addAction(tristateItem);
// tristateItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            setTristate(tristateItem.isSelected());
//        }
//    });
 connect(tristateItem, SIGNAL(toggled(bool)), this, SLOT(setTristate(bool)));
}

/******** popup AbstractAction.actionPerformed method overrides *********/

/*protected*/ void SlipTurnoutIcon::rotateOrthogonal() {
    lowerWestToUpperEast->setRotation(lowerWestToUpperEast->getRotation() + 1, this);
    upperWestToLowerEast->setRotation(upperWestToLowerEast->getRotation() + 1, this);
    lowerWestToLowerEast->setRotation(lowerWestToLowerEast->getRotation() + 1, this);
    upperWestToUpperEast->setRotation(upperWestToUpperEast->getRotation() + 1, this);
    unknown->setRotation(unknown->getRotation() + 1, this);
    inconsistent->setRotation(inconsistent->getRotation() + 1,this);
    displayState(turnoutState());
    // bug fix, must repaint icons that have same width and height
    repaint();
}

/*public*/ void SlipTurnoutIcon::setScale(double s) {
    lowerWestToUpperEast->scale(s, this);
    upperWestToLowerEast->scale(s, this);
    lowerWestToLowerEast->scale(s, this);
    upperWestToUpperEast->scale(s, this);
    unknown->scale(s, this);
    inconsistent->scale(s, this);
    displayState(turnoutState());
}

/*public*/ void SlipTurnoutIcon::rotate(int deg) {
    lowerWestToUpperEast->rotate(deg, this);
    upperWestToLowerEast->rotate(deg, this);
    lowerWestToLowerEast->rotate(deg, this);
    upperWestToUpperEast->rotate(deg, this);
    unknown->rotate(deg, this);
    inconsistent->rotate(deg, this);
    displayState(turnoutState());
}

/**
 * Drive the current state of the display from the state of the turnout.
 * Here we have to alter the passed state to match the type of turnout we
 * are dealing with.
 * @param state An integer value of the turnout states.
 */
void SlipTurnoutIcon::displayState(int state) {
//This needs to be worked on
    if( log->isDebugEnabled()) log->debug(getNameString() +" displayState "+QString::number(state));
    updateSize();
    // we have to make some adjustments if we are using a single slip, three way point
    // or scissor arrangement to make sure that we get the correct representation.
    switch(getTurnoutType()){
        case SINGLESLIP:
            if (singleSlipRoute && state ==9){
                state = 0;
            } else if ((!singleSlipRoute) && state == 7) {
                state = 0;
            }
            break;
        case THREEWAY:
            if ((state == 7) || (state == 11)) {
                if (singleSlipRoute) {
                    state = 11;
                } else {
                    state = 9;
                }
            } else if (state==9) {
                if (!singleSlipRoute) {
                    state = 11;
                }
            }
            break;
        case SCISSOR:

            //State 11 should not be allowed for a scissor.
            switch(state) {
                case 5: state = 9;
                        break;
                case 7: state = 5;
                        break;
                case 9: state = 11;
                        break;
                case 11: state = 0;
                         break;
            }
            break;
    }
    switch (state) {
    case Turnout::UNKNOWN:
        if (isText()) PositionableLabel::setText(tr("UnKnown"));
        if (isIcon()) PositionableLabel::setIcon(unknown);
        break;
    case 5: //first closed, second closed
        if (isText()) PositionableLabel::setText(upperWestToLowerEastText);
        if (isIcon()) PositionableLabel::setIcon(upperWestToLowerEast);
        break;
    case 9: // first Closed, second Thrown
        if (isText()) PositionableLabel::setText(lowerWestToLowerEastText);
        if (isIcon()) PositionableLabel::setIcon(lowerWestToLowerEast);
        break;
    case 7: //first Thrown, second Closed
        if (isText()) PositionableLabel::setText(upperWestToUpperEastText);
        if (isIcon()) PositionableLabel::setIcon(upperWestToUpperEast);
        break;
    case 11: //first Thrown second Thrown
        if (isText()) PositionableLabel::setText(lowerWestToUpperEastText);
        if (isIcon()) PositionableLabel::setIcon(lowerWestToUpperEast);
        break;
    default:
        if (isText()) PositionableLabel::setText(tr("Inconsistent"));
        if (isIcon()) PositionableLabel::setIcon(inconsistent);
        break;
    }
    return;
}

/**
* Get the text used in the pop-up for setting the route from Lower West
* to Upper East
* For a scissor crossing this the Left-hand crossing.
* For a 3 Way turnout this is the Upper Exit.
*/
/*public*/ QString SlipTurnoutIcon::getLWUEText(){ return lowerWestToUpperEastText; }

/**
* Get the text used in the pop-up for setting the route from Upper West
* to Lower East.
* For a scissor crossing this the Right-hand crossing.
* For a 3 Way turnout this is the Middle Exit.
*/
/*public*/ QString SlipTurnoutIcon::getUWLEText(){ return upperWestToLowerEastText; }

/**
* Get the text used in the pop-up for setting the route from Lower West
* to Lower East.
* For a scissor crossing this the Straight (Normal) Route.
* For a 3 Way turnout this is the Lower Exit.
*/
/*public*/ QString SlipTurnoutIcon::getLWLEText(){ return lowerWestToLowerEastText; }

/**
* Get the text used in the pop-up for setting the route from Upper West
* to Upper East.
* For a scissor crossing this is not used.
* For a 3 Way turnout this is not used.
*
/*public*/ QString SlipTurnoutIcon::getUWUEText(){ return upperWestToUpperEastText; }

/*public*/ void SlipTurnoutIcon::setLWUEText(QString txt){ lowerWestToUpperEastText=txt; }
/*public*/ void SlipTurnoutIcon::setUWLEText(QString txt){ upperWestToLowerEastText=txt; }
/*public*/ void SlipTurnoutIcon::setLWLEText(QString txt){ lowerWestToLowerEastText=txt; }
/*public*/ void SlipTurnoutIcon::setUWUEText(QString txt){ upperWestToUpperEastText=txt; }

/*public*/ bool SlipTurnoutIcon::setEditIconMenu(QMenu* popup)
{
 QString s_type = "Turnout";
 switch(turnoutType)
 {
 case DOUBLESLIP:
     s_type = tr("Double Slip");
     break;
 case SINGLESLIP:
     s_type = tr("Single Slip");
     break;
 case THREEWAY:
     s_type = tr("3 Way Turnout");
     break;
 case SCISSOR:
     s_type = tr("Scissor Crossover");
     break;
 }
 QString txt = tr("Edit %1 Item").arg(s_type);
// popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(edit()));
 return true;
}


/*protected*/ void SlipTurnoutIcon::edit()
{
 if (_iconEditor==nullptr)
 {
  _iconEditor = new SlipIconAdder();
 }
 makeIconEditorFrame(this, "SlipTOEditor", true, _iconEditor);
 _iconEditor->setPickList(PickListModel::turnoutPickModelInstance());
 _iconEditor->setTurnoutType(getTurnoutType());
 STOWindowListener* wl = new STOWindowListener(this);
 _iconEditorFrame->addWindowListener(wl);

 switch(getTurnoutType())
 {
 case DOUBLESLIP :
  _iconEditor->setIcon(3, "LowerWestToUpperEast", getLowerWestToUpperEastIcon());
  _iconEditor->setIcon(2, "UpperWestToLowerEast", getUpperWestToLowerEastIcon());
  _iconEditor->setIcon(4, "LowerWestToLowerEast", getLowerWestToLowerEastIcon());
  _iconEditor->setIcon(5, "UpperWestToUpperEast", getUpperWestToUpperEastIcon());
  break;
 case SINGLESLIP:
  _iconEditor->setSingleSlipRoute(getSingleSlipRoute());
  _iconEditor->setIcon(3, "LowerWestToUpperEast", getLowerWestToUpperEastIcon());
  _iconEditor->setIcon(2, "UpperWestToLowerEast", getUpperWestToLowerEastIcon());
  _iconEditor->setIcon(4, "Slip", getLowerWestToLowerEastIcon());
  break;
 case THREEWAY:
  _iconEditor->setSingleSlipRoute(getSingleSlipRoute());
  _iconEditor->setIcon(3, "Upper", getLowerWestToUpperEastIcon());
  _iconEditor->setIcon(2, "Middle", getUpperWestToLowerEastIcon());
  _iconEditor->setIcon(4, "Lower", getLowerWestToLowerEastIcon());
  break;
 case SCISSOR:
  _iconEditor->setSingleSlipRoute(getSingleSlipRoute());
  _iconEditor->setIcon(3, "LowerWestToUpperEast", getLowerWestToUpperEastIcon());
  _iconEditor->setIcon(2, "UpperWestToLowerEast", getUpperWestToLowerEastIcon());
  _iconEditor->setIcon(4, "LowerWestToLowerEast", getLowerWestToLowerEastIcon());
  if (!getSingleSlipRoute())
  {
   _iconEditor->setTurnout("lowerwest", namedTurnoutWestLower);
   _iconEditor->setTurnout("lowereast", namedTurnoutEastLower);
  }
  break;
 }
 _iconEditor->setIcon(0, "BeanStateInconsistent", getInconsistentIcon());
 _iconEditor->setIcon(1, "BeanStateUnknown", getUnknownIcon());
 _iconEditor->setTurnout("west", namedTurnoutWest);
 _iconEditor->setTurnout("east", namedTurnoutEast);
 _iconEditor->makeIconPanel(true);

//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateTurnout();
//        }
//    };
 SlipTurnoutActionListener* addIconAction = new SlipTurnoutActionListener(this);
 _iconEditor->complete(addIconAction, true, true, true);
}
STOWindowListener::STOWindowListener(SlipTurnoutIcon *parent)
{
 this->parent = parent;
}
void STOWindowListener::windowClosing(QCloseEvent */*e*/)
{
 delete parent->_iconEditor;
 parent->_iconEditor = nullptr;
}

void SlipTurnoutIcon::updateTurnout()
{
 setTurnoutType(_iconEditor->getTurnoutType());
 switch(_iconEditor->getTurnoutType())
 {
 case DOUBLESLIP :
  setLowerWestToUpperEastIcon(_iconEditor->getIcon("LowerWestToUpperEast"));
  setUpperWestToLowerEastIcon(_iconEditor->getIcon("UpperWestToLowerEast"));
  setLowerWestToLowerEastIcon(_iconEditor->getIcon("LowerWestToLowerEast"));
  setUpperWestToUpperEastIcon(_iconEditor->getIcon("UpperWestToUpperEast"));
  break;
 case SINGLESLIP:
    setLowerWestToUpperEastIcon(_iconEditor->getIcon("LowerWestToUpperEast"));
    setUpperWestToLowerEastIcon(_iconEditor->getIcon("UpperWestToLowerEast"));
    setSingleSlipRoute(_iconEditor->getSingleSlipRoute());
    setLowerWestToLowerEastIcon(_iconEditor->getIcon("Slip"));
    break;
 case THREEWAY:
    setSingleSlipRoute(_iconEditor->getSingleSlipRoute());
    setLowerWestToUpperEastIcon(_iconEditor->getIcon("Upper"));
    setUpperWestToLowerEastIcon(_iconEditor->getIcon("Middle"));
    setLowerWestToLowerEastIcon(_iconEditor->getIcon("Lower"));
    break;
 case SCISSOR :
  setLowerWestToUpperEastIcon(_iconEditor->getIcon("LowerWestToUpperEast"));
  setUpperWestToLowerEastIcon(_iconEditor->getIcon("UpperWestToLowerEast"));
  setLowerWestToLowerEastIcon(_iconEditor->getIcon("LowerWestToLowerEast"));
  setSingleSlipRoute(_iconEditor->getSingleSlipRoute());
  if (!getSingleSlipRoute())
  {
   setTurnout(_iconEditor->getTurnout("lowerwest"), LOWERWEST);
   setTurnout(_iconEditor->getTurnout("lowereast"), LOWEREAST);
  }
  break;
 }
 setInconsistentIcon(_iconEditor->getIcon("BeanStateInconsistent"));
 setUnknownIcon(_iconEditor->getIcon("BeanStateUnknown"));
 setTurnout(_iconEditor->getTurnout("west"), WEST);
 setTurnout(_iconEditor->getTurnout("east"), EAST);
 _iconEditorFrame->dispose();
 _iconEditorFrame = nullptr;
 _iconEditor = nullptr;
 //invalidate();
 updateScene();
}

/**
 * Throw the turnout when the icon is clicked
 * @param e
 */
/*public*/ void SlipTurnoutIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return;
 if (e->modifiers()&Qt::MetaModifier || e->modifiers()&Qt::AltModifier ) return;
 if ((namedTurnoutWest==nullptr) || (namedTurnoutEast==nullptr))
 {
  log->error("No turnout connection, can't process click");
  return;
 }
 switch(turnoutType)
 {
 case DOUBLESLIP:
  doDoubleSlipMouseClick();
  break;
 case SINGLESLIP:
  doSingleSlipMouseClick();
  break;
 case THREEWAY:
  do3WayMouseClick();
  break;
 case SCISSOR:      \
  doScissorMouseClick();
  break;
 }
}

 /**
 * Throw the turnouts for a double slip when the icon is clicked
 */
/*private*/ void SlipTurnoutIcon::doDoubleSlipMouseClick(){
    switch(turnoutState()){
        case 5:  setUpperWestToUpperEast();
                 break;
        case 7:  setLowerWestToUpperEast();
                 break;
        case 9:  setUpperWestToLowerEast();
                 break;
        case 11: setLowerWestToLowerEast();
                 break;
        default : setUpperWestToLowerEast();
    }
}

 /**
 * Throw the turnouts for a single slip when the icon is clicked
 */
/*private*/ void SlipTurnoutIcon::doSingleSlipMouseClick(){
    switch(turnoutState()){
        case 5: if (singleSlipRoute)
                    setLowerWestToUpperEast();
                else
                    setLowerWestToLowerEast();
                break;
        case 7: if (singleSlipRoute)
                    setUpperWestToLowerEast();
                else
                    setLowerWestToUpperEast();
                break;
        case 9: if (singleSlipRoute)
                    setUpperWestToLowerEast();
                else
                    setLowerWestToUpperEast();
                break;
        case 11: if (singleSlipRoute)
                    setUpperWestToUpperEast();
                 else
                    setUpperWestToLowerEast();
                 break;
        default : setUpperWestToLowerEast();
    }
}

/**
 * Throw the turnouts for a 3 way Turnout when the icon is clicked
 */
/*private*/ void SlipTurnoutIcon::do3WayMouseClick()
{
 switch(turnoutState())
 {
 case 5:
  if (singleSlipRoute)
   setLowerWestToLowerEast();
  else
   setUpperWestToUpperEast();
break;
 case 7: if (singleSlipRoute)
                    setLowerWestToUpperEast();
                else
                    setLowerWestToLowerEast();
                break;
 case 9: if (singleSlipRoute)
                    setLowerWestToUpperEast();
                else
                    setUpperWestToLowerEast();
                break;
 case 11: if (singleSlipRoute)
                    setUpperWestToLowerEast();
                 else
                    setLowerWestToLowerEast();
                 break;
 default : setLowerWestToUpperEast();
 }
}

 /**
 * Throw the turnouts for a scissor crossing when the icon is clicked
 */
/*private*/ void SlipTurnoutIcon::doScissorMouseClick()
{
 if (turnoutState()==5)
 {
  if (firstStraight)
  {
   setUpperWestToLowerEast();
   firstStraight=false;
  }
  else
  {
   setLowerWestToUpperEast();
   firstStraight=true;
  }
 }
 else
 {
  setLowerWestToLowerEast();
 }
}

/*protected*/ QHash<Turnout*, int>* SlipTurnoutIcon::getTurnoutSettings() { return _turnoutSetting; }


/*protected*/ void SlipTurnoutIcon::reset() {
    _turnoutSetting = new QHash <Turnout*, int>();
}
/**
* Set the turnouts appropriate for Upper West to Lower East line in a Slip
* which is the equivalent a of right hand crossing in a scissors.
* With a three way turnout, this is also the middle route.
*/
/*private*/ void SlipTurnoutIcon::setUpperWestToLowerEast(){
    reset();
    if (getTurnoutType()==SCISSOR){
        _turnoutSetting->insert(getTurnout(WEST), Turnout::THROWN);
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::CLOSED));
        if (!singleSlipRoute){
            _turnoutSetting->insert(namedTurnoutWestLower->getBean(), (Turnout::CLOSED));
            _turnoutSetting->insert(namedTurnoutEastLower->getBean(), (Turnout::THROWN));
        }
    } else {
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::CLOSED));
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::CLOSED));
    }
    setSlip();
}

/**
* Set the turns appropriate for Lower West to Upper East line in a Slip
* which is the equivalent of the left hand crossing in a scissors.
* With a three way turnout, this is also the upper route.
*/
/*private*/ void SlipTurnoutIcon::setLowerWestToUpperEast(){
    reset();
    if (getTurnoutType()==SCISSOR){
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::THROWN));
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::CLOSED));
        if (!singleSlipRoute){
            _turnoutSetting->insert(namedTurnoutWestLower->getBean(), (Turnout::THROWN));
            _turnoutSetting->insert(namedTurnoutEastLower->getBean(), (Turnout::CLOSED));
        }
    } else {
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::THROWN));
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::THROWN));
    }
    setSlip();
}

/**
* Set the turnouts appropriate for Upper West to Upper East line in a Slip
* which is the equivalent of the straight (normal route) in a scissors.
* With a three way turnout, this is not used.
*/

/*private*/ void SlipTurnoutIcon::setUpperWestToUpperEast(){
    reset();
    if (getTurnoutType()==SCISSOR){
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::CLOSED));
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::CLOSED));
        if (!singleSlipRoute){
            _turnoutSetting->insert(namedTurnoutWestLower->getBean(), (Turnout::CLOSED));
            _turnoutSetting->insert(namedTurnoutEastLower->getBean(), (Turnout::CLOSED));
        }
    } else {
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::THROWN));
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::CLOSED));
    }
    setSlip();
}

/**
* Set the turnouts appropriate for Lower West to Lower East line in a Slip
* which is the equivalent of the straight (normal route) in a scissors.
* With a three way turnout, this is the lower route.
*/

/*private*/ void SlipTurnoutIcon::setLowerWestToLowerEast(){
    reset();
    if (getTurnoutType()==SCISSOR){
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::CLOSED));
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::CLOSED));
        if (!singleSlipRoute){
            _turnoutSetting->insert(namedTurnoutWestLower->getBean(), (Turnout::CLOSED));
            _turnoutSetting->insert(namedTurnoutEastLower->getBean(), (Turnout::CLOSED));
        }
    } else {
        _turnoutSetting->insert(getTurnout(WEST), (Turnout::CLOSED));
        _turnoutSetting->insert(getTurnout(EAST), (Turnout::THROWN));
    }
    setSlip();
}

/**
* Displays a popup menu to select a given state, rather than cycling
* through each state
* @param popup
*/
/*public*/ bool SlipTurnoutIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  // add tristate option if turnout has feedback
  bool returnstate=false;
  if (namedTurnoutWest != nullptr && ((AbstractTurnout*)getTurnout(WEST))->getFeedbackMode() != Turnout::DIRECT)
  {
   addTristateEntry(popup);
   returnstate = true;
  }
  if (namedTurnoutEast != nullptr && ((AbstractTurnout*)getTurnout(EAST))->getFeedbackMode() != Turnout::DIRECT)
  {
   addTristateEntry(popup);
   returnstate = true;
  }
  return returnstate;
 }
 else
 {
  QAction* LWUE = new QAction(lowerWestToUpperEastText, this);
  if ((turnoutType==THREEWAY) && (!singleSlipRoute))
  {
//            LWUE.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToLowerEast(); }
//            });
   connect(LWUE, SIGNAL(triggered()), this, SLOT(setLowerWestToLowerEast()));

  }
  else
  {
//            LWUE.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToUpperEast(); }
//            });
   connect(LWUE, SIGNAL(triggered()), this, SLOT(setLowerWestToUpperEast()));
  }
  popup->addAction(LWUE);
  QAction* UWLE = new QAction(upperWestToLowerEastText, this);
//        UWLE.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) { setUpperWestToLowerEast(); }
//        });
  connect(UWLE, SIGNAL(triggered()), this, SLOT(setUpperWestToLowerEast()));
  popup->addAction(UWLE);
  if ((turnoutType==DOUBLESLIP)||((turnoutType==SINGLESLIP)&&(!singleSlipRoute)))
  {
   QAction* LWLE = new QAction(lowerWestToLowerEastText, this);
//            LWLE.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToLowerEast(); }
//            });
   connect(LWLE, SIGNAL(triggered()), this, SLOT(setLowerWestToLowerEast()));
   popup->addAction(LWLE);
  }
  if ((turnoutType==DOUBLESLIP)||((turnoutType==SINGLESLIP)&&(singleSlipRoute)))
  {
   QAction* UWUE = new QAction(upperWestToUpperEastText, this);
//            UWUE.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) { setUpperWestToUpperEast(); }
//            });
   connect(UWUE, SIGNAL(triggered()), this, SLOT(setUpperWestToUpperEast()));
   popup->addAction(UWUE);
  }
  if (turnoutType==THREEWAY)
  {
   QAction* LWLE = new QAction(lowerWestToLowerEastText, this);
   if(!singleSlipRoute)
   {
//                LWLE.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToUpperEast(); }
//                });
    connect(LWLE, SIGNAL(triggered()), this, SLOT(setLowerWestToUpperEast()));
   }
   else
   {
//                LWLE.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToLowerEast(); }
//                });
    connect(LWLE, SIGNAL(triggered()), this, SLOT(setLowerWestToLowerEast()));
   }
   popup->addAction(LWLE);
  }
  if (turnoutType==SCISSOR)
  {
   QAction* LWLE = new QAction(lowerWestToLowerEastText, this);
//            LWLE.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) { setLowerWestToLowerEast(); }
//                });
   connect(LWLE, SIGNAL(triggered()), this, SLOT(setLowerWestToLowerEast()));
   popup->addAction(LWLE);
  }
 }
 return true;
}

// overide
/*public*/ bool SlipTurnoutIcon::setTextEditMenu(QMenu* popup) {
    QString popuptext = tr("Set Slip Text");
    if (turnoutType==THREEWAY)
        popuptext = tr("Set 3Way Text");
    else if (turnoutType==SCISSOR)
        popuptext = tr("Set Scissor Text");
    QAction* act;
    popup->addAction(act = new QAction(popuptext, this));
//    {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            QString name = getNameString();
//            slipTurnoutTextEdit(name);
//        }
//    });
    connect(act, SIGNAL(triggered()), this, SLOT(on_slipTurnoutTextEdit()));
    return true;
}
void SlipTurnoutIcon::on_slipTurnoutTextEdit()
{
 QString name = getNameString();
 slipTurnoutTextEdit(name);
}

/*public*/ void SlipTurnoutIcon::slipTurnoutTextEdit(QString name) {
    if (debug) log->debug("make text edit menu");

    SlipTurnoutTextEdit* f = new SlipTurnoutTextEdit();
    f->addHelpMenu("package.jmri.jmrit.display.SlipTurnoutTextEdit", true);
    try {
        f->initComponents(this, name);
        }
    catch (Exception* ex) {
        log->error("Exception: "+ex->getMessage());
        }
    f->setVisible(true);

}

/*public*/ void SlipTurnoutIcon::dispose() {
    if (namedTurnoutWest != nullptr) {
     getTurnout(WEST)->removePropertyChangeListener((PropertyChangeListener*)this);
//     AbstractTurnout* to = (AbstractTurnout*)getTurnout(WEST);
//     disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedTurnoutWest = nullptr;
    if (namedTurnoutEast != nullptr) {
        getTurnout(EAST)->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractTurnout* to = (AbstractTurnout*)getTurnout(EAST);
//        disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    }
    namedTurnoutEast = nullptr;
    if (namedTurnoutWestLower != nullptr) {
        getTurnout(WEST)->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractTurnout* to = (AbstractTurnout*)getTurnout(WEST);
//        disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedTurnoutWestLower = nullptr;
    if (namedTurnoutEastLower != nullptr) {
        getTurnout(EAST)->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractTurnout* to = (AbstractTurnout*)getTurnout(EAST);
//        disconnect(to, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedTurnoutEastLower = nullptr;
    lowerWestToUpperEast = nullptr;
    upperWestToLowerEast = nullptr;
    lowerWestToLowerEast = nullptr;
    upperWestToUpperEast = nullptr;
    inconsistent = nullptr;
    unknown = nullptr;

    PositionableLabel::dispose();
}


/**
 * Method to set Slip busy when commands are being issued to
 *   Slip turnouts
 */
/*protected*/ void SlipTurnoutIcon::setSlipBusy() {
    busy = true;
}

/**
 * Method to set Slip not busy when all commands have been
 *   issued to Slip turnouts
 */
/*protected*/ void SlipTurnoutIcon::setSlipNotBusy() {
    busy = false;
}

/**
 * Method to query if Slip is busy (returns true if commands are
 *   being issued to Slips turnouts)
 */
/*protected*/ bool SlipTurnoutIcon::isSlipBusy() {
    return (busy);
}

 /**
 * Method to set the Slip
 * Sets the slips Turnouts to the state required
 * This call is ignored if the slip is 'busy', i.e., if there is a
 *    thread currently sending commands to this Slips's turnouts.
 */
/*private*/ void SlipTurnoutIcon::setSlip() {
        if (!busy) {
            setSlipBusy();
            SetSlipThread* thread = new SetSlipThread(this);
            thread->start();
        }
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SlipTurnoutIcon.class.getName());
//}

//class SetSlipThread extends Thread {
/**
 * Constructs the thread
 */
/*public*/ SetSlipThread::SetSlipThread(SlipTurnoutIcon* aSlip) {
    s = aSlip;
}
//This is used to set the two turnouts, with a delay of 250ms between each one.
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="WMI_WRONG_MAP_ITERATOR", justification="iterator really short, efficiency not as important as clarity here")
/*public*/ void SetSlipThread::run() {

    QHash <Turnout*, int>* _turnoutSetting = s->getTurnoutSettings();

    QListIterator<Turnout*> itr (_turnoutSetting->keys());
    while(itr.hasNext())
    {
        Turnout* t = itr.next();
        int state = _turnoutSetting->value(t);
        t->setCommandedState(state);
        try {
            QThread::msleep(250);
        } catch (InterruptedException e) {
            QThread::currentThread()->exit(); // retain if needed later
        }
    }

    //set Slip not busy
    s->setSlipNotBusy();
}

/*public*/ QString SlipTurnoutIcon::getGroupName()
{
 return "SlipTurnoutIcon";
}



//static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SetSlipThread.class.getName());

