#ifndef LNREPORTER_H
#define LNREPORTER_H
#include "abstractreporter.h"
#include "lntrafficcontroller.h"
#include "locoaddress.h"
#include "dcclocoaddress.h"
#include "physicallocationreporter.h"

class LnReporter : public AbstractReporter /*, public PhysicalLocationReporter*/

{
    Q_OBJECT
public:
    //explicit LnReporter(QObject *parent = 0);
    LnReporter(int number, LnTrafficController* tc, QString prefix, QObject* parent); // a human-readable Reporter number must be specified!
    int getNumber();
    // implementing classes will typically have a function/listener to get
    // updates from the layout, which will then call
    //		public void firePropertyChange(QString propertyName,
    //					      	Object oldValue,
    //						Object newValue)
    // _once_ if anything has changed state (or set the commanded state directly)
    /*public*/ void messageFromManager(LocoNetMessage* l);
    /*public*/ /*final*/ bool isTranspondingLocationReport(LocoNetMessage* l);
    /*public*/ /*final*/ bool isTranspondingFindReport(LocoNetMessage* l);
   /**
    * Provide an int value for use in scripts, etc.  This will be
    * the numeric locomotive address last seen, unless the last
    * message said the loco was exiting. Note that there may still some
    * other locomotive in the transponding zone!
    * @return -1 if the last message specified exiting
    */
   int getState();
   void setState(int s);
   void dispose();
#if 0
   // parseReport()
   // Parses out a (possibly old) LnReporter-generated report string to extract info used by
   // the public PhysicalLocationReporter methods.  Returns a Matcher that, if successful, should
   // have the following groups defined.
   // matcher.group(1) : the locomotive address
   // matcher.group(2) : (enter | exit | seen)
   // matcher.group(3) | (northbound | southbound) -- Lissy messages only
   //
   // NOTE: This code is dependent on the transpondingReport() and lissyReport() methods above.  If they change, the regex here must change.
   Matcher* LnReporter::parseReport(QString rep) {
#endif

   // Parses out a (possibly old) LnReporter-generated report string to extract the address from the front.
   // Assumes the LocoReporter format is "NNNN [enter|exit]"
   LocoAddress* getLocoAddress(QString rep);
   // Parses out a (possibly old) LnReporter-generated report string to extract the direction from the end.
   // Assumes the LocoReporter format is "NNNN [enter|exit]"
   PhysicalLocationReporter::Direction getDirection(QString rep);
   PhysicalLocation* getPhysicalLocation();
   PhysicalLocation* getPhysicalLocation(QString s);

signals:
    
public slots:
 void message(LocoNetMessage* l);

private:
    LnTrafficController* tc;
    /**
     * Handle transponding message
     */
    void transpondingReport(LocoNetMessage* l);
    /**
     * Handle LISSY message
     */
    void lissyReport(LocoNetMessage* l);
    int lastLoco;
    // parseReport()
    // Parses out a (possibly old) LnReporter-generated report string to extract info used by
    // the public PhysicalLocationReporter methods.  Returns a Matcher that, if successful, should
    // have the following groups defined.
    // matcher.group(1) : the locomotive address
    // matcher.group(2) : (enter | exit | seen)
    // matcher.group(3) | (northbound | southbound) -- Lissy messages only
    //
    // NOTE: This code is dependent on the transpondingReport() and lissyReport() methods above.  If they change, the regex here must change.
#if 0
    Matcher* parseReport(QString rep);
#endif
    // data members
    int _number;   // loconet Reporter number
    bool myAddress(int a1, int a2);
  Logger log;
    
};

#endif // LNREPORTER_H
