#include "lncabsignal.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "lntrafficcontroller.h"

/**
 * Ln implementation of a Cab Signal Object, describing the state of the
 * track ahead relative to a locomotive with a given address.  This is
 * effectively a mobile signal mast->
 *
 * @author Steve Young Copyright (C) 2018
 * @author Paul Bender Copyright (C) 2019
 */
///*public*/ class LnCabSignal extends DefaultCabSignal {


    /*public*/ LnCabSignal::LnCabSignal(LocoNetSystemConnectionMemo* memo,LocoAddress* address, QObject *parent)
      :DefaultCabSignal(address, parent)
    {
       //super(address);
       _memo = memo;
       log->debug(tr("created cab signal for %1").arg(address->toString()));
    }

    /**
     * A method for cleaning up the cab signal
     */
    //@Override
    /*public*/ void LnCabSignal::dispose(){
        DefaultCabSignal::dispose();
        _memo=nullptr;
    }

    /**
     * Forward the command to the layout that sets the displayed signal
     * aspect for this address
     */
    //@Override
    /*protected*/ void LnCabSignal::forwardAspectToLayout(){
        LocoAddress* locoaddr = getCabSignalAddress();
        SignalMast* mast = getNextMast();
        // adapted from cabsignaller.py by Nigel Cliffe
        // Message variables are Loco = Decimal loco address,

        // Calculate the two byte loco address value
        int locoD1 = locoaddr->getNumber() / 128;  //integer division, automatically rounds
        int locoD2 = locoaddr->getNumber() % 128;  //modulo division, gets the remainder.
        // determine the mast
        //  others are binary 1 or 0
        //  bit 4 = 1 show mast,  bit 4 = 0 hide mast->
        //  bit 3 = 1 show vertical, bit 3 = 0 hide vertical
        //  bit 2 = 1 show diagonal, bit 2 = 0 hide diagonal
        //  bit 1 = 1 show horizontal, bit 1 = 0 hide horizontal
        //  bit 0 = 1 blink, bit 0 = 0 no blink
        int signalD3=0; // default case, off.

        if(mast!=nullptr){
           QString speed =  mast->getSignalSystem()->getProperty(mast->getAspect(), "speed").toString();
           // set aspect based on signal "speed" first.
           if(speed =="Normal" || speed ==  "Clear")
                    signalD3 = 0x18; // show vertical;
            else if(speed == "Limited")
                    signalD3 = 0x19; // show vertical blinking;
            else if(speed =="Medium")
                    signalD3 = 0x14; // show diagonal;
            else if(speed == "Stop")
                    signalD3 = 0x12; // show horizontal (stop);
            else if(speed == "Restricting" || speed == "RestrictedSlow" || speed == "Restricted" || speed == "Slow")
                    signalD3 = 0x13; // blink horizontal
            else
            {
                   // if no matching speed in the list above, check for
                   // the constant values in the SignalAppearanceMap.
                   if(mast->getAspect() == (mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE))){
                      signalD3 = 0x18; // show vertical;
                   } else if(mast->getAspect() == (mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER))){
                      signalD3 = 0x12; // show horizontal (stop);
                   } else if(mast->getAspect() == (mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD))){
                      signalD3 = 0x12; // show horizontal (stop);
                   } else if(mast->getAspect() == (mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DARK))){
                      signalD3 = 0x00; // show nothing;
                   } else {
                      signalD3 = 0x14; // show diagonal;*/
                   }
             }

        }
        // this is a litteral translation from the script.  it should be
        // created from a method in LocoNetMessage.
        LocoNetMessage* peerXFerMessage = new LocoNetMessage(16);
        peerXFerMessage->setOpCode(229);
        peerXFerMessage->setElement(1,16);
        peerXFerMessage->setElement(2,127);
        peerXFerMessage->setElement(3,0);
        peerXFerMessage->setElement(4,0);
        peerXFerMessage->setElement(5,0);
        peerXFerMessage->setElement(6,locoD1);
        peerXFerMessage->setElement(7,locoD2);
        peerXFerMessage->setElement(8,signalD3);
        peerXFerMessage->setElement(9,0);
        peerXFerMessage->setElement(10,112);
        peerXFerMessage->setElement(11,0);
        peerXFerMessage->setElement(12,0);
        peerXFerMessage->setElement(13,0);
        peerXFerMessage->setElement(14,0);
        peerXFerMessage->setElement(15,0);

        _memo->getLnTrafficController()->sendLocoNetMessage(peerXFerMessage);
    }

    /**
     * Forward the command to the layout that clears any displayed signal
     * for this address
     */
    //@Override
    /*protected*/ void LnCabSignal::resetLayoutCabSignal(){
        LocoAddress* locoaddr = getCabSignalAddress();
        // Calculate the two byte loco address value
        int locoD1 = locoaddr->getNumber() / 128;  //integer division, automatically rounds
        int locoD2 = locoaddr->getNumber() % 128;  //modulo division, gets the remainder.
        int signalD3=0; // off.

        LocoNetMessage* peerXFerMessage = new LocoNetMessage(16);
        peerXFerMessage->setOpCode(229);
        peerXFerMessage->setElement(1,16);
        peerXFerMessage->setElement(2,127);
        peerXFerMessage->setElement(3,0);
        peerXFerMessage->setElement(4,0);
        peerXFerMessage->setElement(5,0);
        peerXFerMessage->setElement(6,locoD1);
        peerXFerMessage->setElement(7,locoD2);
        peerXFerMessage->setElement(8,signalD3);
        peerXFerMessage->setElement(9,0);
        peerXFerMessage->setElement(10,112);
        peerXFerMessage->setElement(11,0);
        peerXFerMessage->setElement(12,0);
        peerXFerMessage->setElement(13,0);
        peerXFerMessage->setElement(14,0);
        peerXFerMessage->setElement(15,0);
        _memo->getLnTrafficController()->sendLocoNetMessage(peerXFerMessage);
    }

    /*private*/ /*final*/ /*static*/ Logger* LnCabSignal::log = LoggerFactory::getLogger("LnCabSignal");

