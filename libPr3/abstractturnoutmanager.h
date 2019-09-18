#ifndef ABSTRACTTURNOUTMANAGER_H
#define ABSTRACTTURNOUTMANAGER_H
#include "turnout.h"
//#include "lnturnout.h"
#include "turnoutmanager.h"
#include "turnoutoperationmanager.h"
#include "systemconnectionmemo.h"

class AbstractManager;
class LIBPR3SHARED_EXPORT AbstractTurnoutManager : public TurnoutManager
{
 Q_OBJECT
public:
    explicit AbstractTurnoutManager(SystemConnectionMemo* memo, QObject *parent = 0);
    virtual int getXMLOrder();
    virtual char typeLetter() ;
    Turnout* provideTurnout(QString name);
    Turnout* getTurnout(QString name);
    Turnout* newTurnout(QString systemName, QString userName);
    Turnout* getBySystemName(QString name);
    Turnout* getByUserName(QString key);
    QString getClosedText();
    /**
     * Get text to be used for the Turnout.THROWN state in user communication.
     * Allows text other than "THROWN" to be use with certain hardware system
     * to represent the Turnout.THROWN state.
     */
    QString getThrownText();
    /**
     * Get from the user, the number of addressed bits used to control a turnout.
     * Normally this is 1, and the default routine returns 1 automatically.
     * Turnout Managers for systems that can handle multiple control bits
     * should override this method with one which asks the user to specify the
     * number of control bits.
     * If the user specifies more than one control bit, this method should
     * check if the additional bits are available (not assigned to another object).
     * If the bits are not available, this method should return 0 for number of
     * control bits, after informing the user of the problem.
     */
     int askNumControlBits(QString systemName);

     bool isNumControlBitsSupported(QString systemName);
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
      int askControlType(QString systemName);

      bool isControlTypeSupported(QString systemName);
      /*
       * Provide list of supported operation types.
       * <p>
       * Order is important because
       * they will be tried in the order specified.
       */
      QStringList getValidOperationTypes();
      /**
      * A temporary method that determines if it is possible to add a range
      * of turnouts in numerical order eg 10 to 30
      **/

      virtual bool allowMultipleAdditions(QString systemName) {Q_UNUSED(systemName);return true;}

      QString createSystemName(QString curAddress, QString prefix);// throws JmriException{
      QString getNextValidAddress(QString curAddress, QString prefix); // throws JmriException{
      void setDefaultClosedSpeed(QString speed);// throws JmriException {
      void setDefaultThrownSpeed(QString speed);// throws JmriException{
      QString getDefaultThrownSpeed();
      QString getDefaultClosedSpeed();
      /*public*/ SystemConnectionMemo* getMemo();

signals:
      void newTurnoutCreated(AbstractTurnoutManager* mgr, Turnout* t);
    
public slots:
 private:
      /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractTurnoutManager");

  QString defaultClosedSpeed;
  QString defaultThrownSpeed;


protected:
  virtual Turnout* createNewTurnout(QString systemName, QString userName)=0;
  //QMap<QString, Turnout*> turnoutMap; // key = systemName!
  /*protected*/ /*final*/ SystemConnectionMemo* memo;
};

#endif // ABSTRACTTURNOUTMANAGER_H
