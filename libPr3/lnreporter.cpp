#include "lnreporter.h"
#include <QRegExp>
#include "instancemanager.h"
#include "rfid/transpondingtagmanager.h"
#include "rfid/abstractidtagreporter.h"
#include "rfid/transpondingtag.h"

//LnReporter::LnReporter(QObject *parent) :
//    AbstractReporter(parent)
//{
//}
/**
 * Extend jmri.AbstractReporter for LocoNet layouts
 * <P>
 * This implementation reports transponding messages.
 *<P>
 * Each transponding message creates a new current report.  The last
 * report is always available, and is the same as the contents of
 * the last transponding message received.
 *<P>
 * Reports are QStrings, formatted as
 *  <ul>
 *  <li>NNNN enter - locomotive address NNNN entered the
 *       transponding zone.  Short vs long address is indicated
 *       by the NNNN value
 *  <LI>NNNN exits - locomotive address NNNN left the transponding zone.
 *  <LI>NNNN seen northbound - LISSY measurement
 *  <LI>NNNN seen southbound - LISSY measurement
 * </ul>
 *<p>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * @author			Bob Jacobsen Copyright (C) 2001, 2007
 * @version			$Revision: 22359 $
 */

//public class LnReporter extends AbstractReporter implements LocoNetListener, PhysicalLocationReporter {

LnReporter::LnReporter(int number, LnTrafficController* tc, QString prefix, QObject* parent) :
        AbstractIdTagReporter(prefix+"R"+QString("%1").arg(number), parent)
{  // a human-readable Reporter number must be specified!
        //super(prefix+"R"+number);  // can't use prefix here, as still in construction
 log.debug("new Reporter "+QString("%1").arg(number));
  _number = number;
 // At construction, register for messages
 tc->addLocoNetListener(~0, (LocoNetListener*)this);
 connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 this->tc = tc;
 lastLoco = -1;
 entrySet = ReporterVariantEntrySet();
}

int LnReporter::getNumber() { return _number; }

     // implementing classes will typically have a function/listener to get
     // updates from the layout, which will then call
     //		public void firePropertyChange(QString propertyName,
     //					      	Object oldValue,
     //						Object newValue)
     // _once_ if anything has changed state (or set the commanded state directly)
    void LnReporter::message(LocoNetMessage* l) {
         // check message type
        if ( (l->getOpCode() == 0xD0) && ( (l->getElement(1) & 0xC0) == 0) )
            transpondingReport(l);
        if ( (l->getOpCode() == 0xE4) && ( l->getElement(1) == 0x08) )
            lissyReport(l);
        else return; // nothing
    }
    /**
      * Process loconet message handed to us from the LnReporterManager
      * @param l - a loconetmessage.
      */
    /*public*/ void LnReporter::messageFromManager(LocoNetMessage* l) {
        // check message type
        if (isTranspondingLocationReport(l) || isTranspondingFindReport(l)) {
            transpondingReport(l);
        }
        if ((l->getOpCode() == LnConstants::OPC_LISSY_UPDATE) && (l->getElement(1) == 0x08)) {
            lissyReport(l);
        } else {
            return; // nothing
        }
    }

    /**
     * Check if message is a Transponding Location Report message
     *
     * A Transponding Location Report message is sent by transponding hardware
     * when a transponding mobile decoder enters or leaves a transponding zone.
     *
     * @param l LocoNet message to check
     * @return true if message is a Transponding Location Report, else false.
     */
    /*public*/ /*final*/ bool LnReporter::isTranspondingLocationReport(LocoNetMessage* l) {
        return ((l->getOpCode() == LnConstants::OPC_MULTI_SENSE)
            && ((l->getElement(1) & 0xC0) == 0)) ;
    }

    /**
     * Check if message is a Transponding Find Report message
     *
     * A Transponding Location Report message is sent by transponding hardware
     * in response to a Transponding Find Request message when the addressed
     * decoder is within a transponding zone and the decoder is transponding-enabled.
     *
     * @param l LocoNet message to check
     * @return true if message is a Transponding Find Report, else false.
     */
    /*public*/ /*final*/ bool LnReporter::isTranspondingFindReport(LocoNetMessage* l) {
        return (l->getOpCode() == LnConstants::OPC_PEER_XFER
            && l->getElement(1) == 0x09
            && l->getElement(2) == 0 );
    }

    /**
     * Handle transponding message passed to us by the LnReporting Manager
     *
     * Assumes that the LocoNet message is a valid transponding message.
     *
     * @param l - incoming loconetmessage
     */
    void LnReporter::transpondingReport(LocoNetMessage* l) {
        bool enter;
        int loco;
        IdTag* idTag;
        if (l->getOpCode() == LnConstants::OPC_MULTI_SENSE) {
            enter = ((l->getElement(1) & 0x20) != 0); // get reported direction
        } else {
            enter = true; // a response for a find request. Always handled as entry.
        }
        loco = getLocoAddrFromTranspondingMsg(l); // get loco address

        notify(nullptr); // set report to null to make sure listeners update

        idTag = ((TranspondingTagManager*)InstanceManager::getDefault("TranspondingTagManager"))->provideIdTag("" + QString::number(loco));
        idTag->setProperty("entryexit", "enter");
        if (enter)
        {
            idTag->setProperty("entryexit", "enter");
            if (!entrySet.contains((TranspondingTag*)idTag)) {
                entrySet.insert((TranspondingTag*) idTag);
            }
        }
        else {
            idTag->setProperty("entryexit", "exits");
            if (entrySet.contains((TranspondingTag*)idTag)) {
                entrySet.remove((TranspondingTag*)idTag);
            }
        }
        log.debug("Tag: " + idTag->toString());
        notify(idTag);
        setState(enter ? loco : -1);
    }

    /**
     * extract long or short address from transponding message
     *
     * Assumes that the LocoNet message is a valid transponding message.
     *
     * @param l LocoNet message
     * @return loco address
     */
    /*public*/ int LnReporter::getLocoAddrFromTranspondingMsg(LocoNetMessage* l) {
        if (l->getElement(3) == 0x7D) {
            return l->getElement(4);
        }
        return l->getElement(3) * 128 + l->getElement(4);

    }
    /**
     * Handle LISSY message
     */
    void LnReporter::lissyReport(LocoNetMessage* l) {
        // check unit address
        int unit = (l->getElement(4)&0x7F);
        if (unit != getNumber()) return;

        // get loco address
        int loco = (l->getElement(6)&0x7F)+128*(l->getElement(5)&0x7F);

        // get direction
        bool north = ( (l->getElement(3) & 0x20) == 0) ;

        // get loco address
        QString s = QString("%1").arg(loco)+" seen "+(north?"northbound":"southbound");
        setReport(QVariant(s));

    }

    /**
     * Provide an int value for use in scripts, etc.  This will be
     * the numeric locomotive address last seen, unless the last
     * message said the loco was exiting. Note that there may still some
     * other locomotive in the transponding zone!
     * @return -1 if the last message specified exiting
     */
    int LnReporter::getState() {
        return lastLoco;
    }

    void LnReporter::setState(int s) {
        lastLoco = s;
    }

    void LnReporter::dispose() {
         tc->removeLocoNetListener(~0, (LocoNetListener*)this);
         //super.dispose();
    }
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
    if (rep == NULL) return(NULL);
    Pattern* ln_p = Pattern.compile("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.
    Matcher* m = ln_p.matcher(rep);
    return(m);
    }
#endif
    // Parses out a (possibly old) LnReporter-generated report string to extract the address from the front.
    // Assumes the LocoReporter format is "NNNN [enter|exit]"
    LocoAddress* LnReporter::getLocoAddress(QString rep) {
     // Extract the number from the head of the report string
     log.debug("report string: " + rep);
//     Matcher* m = this.parseReport(rep);
//     if ((m!= NULL) && m.find()) {
     QRegularExpression regExp("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.)
     QStringList sl = rep.split(regExp);
     QRegularExpressionMatch match = regExp.match(rep);
     if(match.hasMatch() && sl.count() == 2)
     {
      //log.debug("Parsed address: " + m.group(1));
      log.debug("Parsed address: " + match.captured(1));
      //return(new DccLocoAddress(Integer.parseInt(m.group(1)), LocoAddress.Protocol.DCC));
      bool bok;
      DccLocoAddress* addr = new DccLocoAddress(match.captured(1).toInt(&bok), LocoAddress::DCC);
      if(bok)
       return addr;
      else
       return nullptr;

     } else {
        return(NULL);
     }
    }

    // Parses out a (possibly old) LnReporter-generated report string to extract the direction from the end.
    // Assumes the LocoReporter format is "NNNN [enter|exit]"
    PhysicalLocationReporter::Direction LnReporter::getDirection(QString rep)
    {
     // Extract the direction from the tail of the report string
     log.debug("report string: " + rep);
 //    Matcher* m = this.parseReport(rep);
 //    if (m.find())
     QRegularExpression regExp("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.)
     QStringList sl = rep.split(" ");
     QRegularExpressionMatch match = regExp.match(rep);
     if(match.hasMatch() /*&& sl.count() == 3*/)
     {
 //        log.debug("Parsed direction: " + m.group(2));
 //        if (m.group(2).equals("enter")) {
         log.debug("Parsed direction: " + match.captured(2));
         if(match.captured(2) == "enter")
         {
         // LocoNet Enter message
         return(PhysicalLocationReporter::ENTER);
 //        } else if (m.group(2).equals("seen")) {
         } else if (match.captured(2)==("seen")) {

         // Lissy message.  Treat them all as "entry" messages.
         return(PhysicalLocationReporter::ENTER);
         } else {
         return(PhysicalLocationReporter::EXIT);
         }
     } else {
         return(PhysicalLocationReporter::UNKNOWN);
     }
    }

    PhysicalLocation* LnReporter::getPhysicalLocation() {
    return(PhysicalLocation::getBeanPhysicalLocation(this));
    }

    // Does not use the parameter S.
    PhysicalLocation* LnReporter::getPhysicalLocation(QString s) {
     return(PhysicalLocation::getBeanPhysicalLocation(this));
    }
    // Collecting Reporter Interface methods
    /**
      * {@inheritDoc}
      */
     //Override
     /*public*/ ReporterVariantEntrySet LnReporter::getCollection(){
        return entrySet;
     }
    //@SuppressWarnings("unused")
    bool LnReporter::myAddress(int a1, int a2) {
         // the "+ 1" in the following converts to throttle-visible numbering
         return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1) == _number;
    }

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnReporter.class.getName());
