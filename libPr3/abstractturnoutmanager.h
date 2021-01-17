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
    virtual int getXMLOrder() const;
    virtual char typeLetter() const;
    Turnout* provideTurnout(QString name)const override;
    Turnout* getTurnout(QString name) const override;
    Turnout* newTurnout(QString systemName, QString userName) const override;
    Turnout* getBySystemName(QString name)const  override;
    Turnout* getByUserName(QString key)const  override;
    /*public*/ QString getBeanTypeHandled(bool plural)const override;
    QString getClosedText() override;
    /**
     * Get text to be used for the Turnout.THROWN state in user communication.
     * Allows text other than "THROWN" to be use with certain hardware system
     * to represent the Turnout.THROWN state.
     */
    QString getThrownText() override;
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
     int askNumControlBits(QString systemName) override;

     bool isNumControlBitsSupported(QString systemName) override;
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
      int askControlType(QString systemName) override;

      bool isControlTypeSupported(QString systemName) override;
      /*
       * Provide list of supported operation types.
       * <p>
       * Order is important because
       * they will be tried in the order specified.
       */
      QStringList getValidOperationTypes() override;
      /**
      * A temporary method that determines if it is possible to add a range
      * of turnouts in numerical order eg 10 to 30
      **/

      virtual bool allowMultipleAdditions(QString systemName)  override{Q_UNUSED(systemName);return true;}

      QString createSystemName(QString curAddress, QString prefix) const override;// throws JmriException{
      QString getNextValidAddress(QString curAddress, QString prefix)const override; // throws JmriException{
      void setDefaultClosedSpeed(QString speed)const override;// throws JmriException {
      void setDefaultThrownSpeed(QString speed)const override;// throws JmriException{
      QString getDefaultThrownSpeed()const override;
      QString getDefaultClosedSpeed()const override;
//      /*public*/ SystemConnectionMemo* getMemo() override;
      /*public*/ QString getEntryToolTip();
      /*public*/ int getOutputInterval();
      /*public*/ void setOutputInterval(int newInterval);
      /*public*/ LocalDateTime outputIntervalEnds();

signals:
      void newTurnoutCreated(AbstractTurnoutManager* mgr, Turnout* t);
    
public slots:
 private:
      /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractTurnoutManager");

  mutable QString defaultClosedSpeed;
  mutable QString defaultThrownSpeed;

 private:
 /**
  * Duration in milliseconds of interval between separate Turnout commands on the same connection.
  * <p>
  * Change from e.g. XNetTurnout extensions and scripts using {@link #setOutputInterval(int)}
  */
 /*private*/ int turnoutInterval;// = memo->getOutputInterval();
 /*private*/ LocalDateTime waitUntil = LocalDateTime::now();
 /*private*/ void handleIntervalChange(int newVal);

protected:
  virtual Turnout* createNewTurnout(QString systemName, QString userName) const=0;
  //QMap<QString, Turnout*> turnoutMap; // key = systemName!
  /*protected*/ /*final*/ SystemConnectionMemo* memo;
};

#endif // ABSTRACTTURNOUTMANAGER_H
