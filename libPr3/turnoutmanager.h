#ifndef TURNOUTMANAGER_H
#define TURNOUTMANAGER_H
#include <QObject>
#include <QString>
#include <QStringList>
#include "turnout.h"
#include "abstractmanager.h"
#include "localdatetime.h"

class TurnoutManager :  public AbstractManager
{
    Q_OBJECT
public:
    explicit TurnoutManager(SystemConnectionMemo*memo, QObject *parent = nullptr) : AbstractManager(memo, parent) {}
    /**
         * Locate via user name, then system name if needed.
         * If that fails, create a new turnout. If the name
         * is a valid system name, it will be used for the new
         * turnout.  Otherwise, the makeSystemName method
         * will attempt to turn it into a valid system name.
         *
         * @param name User name, system name, or address which
         *      can be promoted to system name
         * @return Never null
         * @throws IllegalArgumentException if Turnout doesn't
         * already exist and the manager cannot create the Turnout
         * due to e.g. an illegal name or name that can't be parsed.
         */
     virtual Turnout* provideTurnout(QString /*name*/)const {return NULL;}
    /** {@inheritDoc} */ // from ProvidinManager
     //@Override
     virtual /*default*/ /*public*/ Turnout* provide(/*@Nonnull*/ QString name)const throw (IllegalArgumentException) { return provideTurnout(name); }


        /**
         * Locate via user name, then system name if needed.
         * If that fails, return null
         *
         * @param name
         * @return null if no match found
         */
        virtual Turnout* getTurnout(QString /*name*/)const =0;

        /**
         * Locate an instance based on a system name.  Returns null if no
         * instance already exists.
         * @return requested Turnout object or null if none exists
         */
         virtual Turnout* getBySystemName(QString /*systemName*/) const =0;

        /**
         * Locate an instance based on a user name.  Returns null if no
         * instance already exists.
         * @return requested Turnout object or null if none exists
         */
         virtual Turnout* getByUserName(QString /*userName*/) const =0;

        /**
         * Return an instance with the specified system and user names.
         * Note that two calls with the same arguments will get the same instance;
         * there is only one Turnout object representing a given physical turnout
         * and therefore only one with a specific system or user name.
         *<P>
         * This will always return a valid object reference; a new object will be
         * created if necessary. In that case:
         *<UL>
         *<LI>If a null reference is given for user name, no user name will be associated
         *    with the Turnout object created; a valid system name must be provided
         *<LI>If both names are provided, the system name defines the
         *    hardware access of the desired turnout, and the user address
         *    is associated with it. The system name must be valid.
         *</UL>
         * Note that it is possible to make an inconsistent request if both
         * addresses are provided, but the given values are associated with
         * different objects.  This is a problem, and we don't have a
         * good solution except to issue warnings.
         * This will mostly happen if you're creating Turnouts when you should
         * be looking them up.
         * @return requested Turnout object (never null)
         * @throws IllegalArgumentException if cannot create the Turnout
         * due to e.g. an illegal name or name that can't be parsed.
         */
        virtual Turnout* newTurnout(QString /*systemName*/,QString /*userName*/)const  =0;

        /**
         * Get a list of all Turnouts' system names.
         */
//    virtual QStringList getSystemNameList() {return QStringList();}

        /**
         * Get text to be used for the Turnout.CLOSED state in user communication.
         * Allows text other than "CLOSED" to be use with certain hardware system
         * to represent the Turnout.CLOSED state.
         */
    virtual QString getClosedText() {return "";}

        /**
         * Get text to be used for the Turnout.THROWN state in user communication.
         * Allows text other than "THROWN" to be use with certain hardware system
         * to represent the Turnout.THROWN state.
         */
    virtual QString getThrownText() {return "";}

         /**
          * Get a list of the valid TurnoutOPeration subtypes for use with turnouts
          * of this system
          */
    virtual QStringList getValidOperationTypes() { return QStringList();}

        /**
         * Get from the user, the number of addressed bits used to control a turnout.
         * Normally this is 1, and the default routine returns one automatically.
         * Turnout Managers for systems that can handle multiple control bits
         * should override this method with one which asks the user to specify the
         * number of control bits.
         * If the user specifies more than one control bit, this method should
         * check if the additional bits are available (not assigned to another object).
         * If the bits are not available, this method should return 0 for number of
         * control bits, after informing the user of the problem.
         */
         virtual int askNumControlBits(QString /*systemName*/) { return 0;}

         /**
          * Determines if the manager supports multiple control bits, as the
          * askNumControlBits will always return a value even if it is not supported
          */
         virtual bool isNumControlBitsSupported(QString /*systemName*/) {return false;}

        /**
         * Get from the user, the type of output to be used bits to control a turnout.
         * Normally this is 0 for 'steady state' control, and the default routine
         * returns 0 automatically.
         * Turnout Managers for systems that can handle pulsed control as well as
         * steady state control should override this method with one which asks
         * the user to specify the type of control to be used.  The routine should
         * return 0 for 'steady state' control, or n for 'pulsed' control, where n
         * specifies the duration of the pulse (normally in seconds).
         */
         virtual int askControlType(QString /*systemName*/) { return 0;}

         /**
          * Determines if the manager supports the handling of pulsed and steady state
          * control as the askControlType will always return a value even if it is
          * not supported
          */
         virtual bool isControlTypeSupported(QString /*systemName*/) {return false;}

        /**
        * A method that determines if it is possible to add a range
        * of turnouts in numerical order eg 10 to 30 will return true.
        * where as if the address format is 1b23 this will return false.
        **/

         virtual bool allowMultipleAdditions(QString /*systemName*/) {return false;}

       /**
        * Determine if the address supplied is valid and free, if not then it shall
        * return the next free valid address up to a maximum of 10 address away from
        * the initial address.
        * @param prefix - The System Prefix used to make up the systemName
        * @param curAddress - The hardware address of the turnout we which to check.
        */

        virtual QString getNextValidAddress(QString /*curAddress*/, QString /*prefix*/) const {return "";} // throws JmriException;

        /**
         * Returns a system name for a given hardware address and system prefix.
         */
        virtual QString createSystemName(QString /*curAddress*/, QString /*prefix*/)const =0;// throws JmriException;

        virtual void setDefaultClosedSpeed(QString /*speed*/) const{}// throws JmriException;

        virtual void setDefaultThrownSpeed(QString /*speed*/) const {}// throws JmriException;

        virtual QString getDefaultThrownSpeed() const{return "";}

        virtual QString getDefaultClosedSpeed() const {return "";}
        /**
         * Get the Interval (in ms) to wait between output commands.
         * Configured in AdapterConfig, stored in memo.
         *
         * @return the (Turnout) Output Interval in milliseconds
         */
        virtual /*public*/ int getOutputInterval() {return 0;}

        /**
         * Set the Interval (in ms) to wait between output commands.
         *
         * @param newInterval the new Output Interval in Milliseconds
         */
        virtual /*public*/ void setOutputInterval(int newInterval) {}

        /**
         * Get end time of latest OutputInterval, calculated from the current time.
         *
         * @return end time in milliseconds or current time if no interval was set or timer has completed
         */
        //@Nonnull
        virtual /*public*/ LocalDateTime outputIntervalEnds() {}

        virtual /*public*/ QString toString() {return "TurnoutManager";}
    
public slots:
    
};
Q_DECLARE_INTERFACE(TurnoutManager, "Turnout manager")
#endif // TURNOUTMANAGER_H
