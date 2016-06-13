#include "lnpr2packetizer.h"

//LnPr2Packetizer::LnPr2Packetizer()
//{
//}
/**
 * Special LnPr2Packetizer implementation for PR2.
 *
 * Differs only in handling PR2's non-echo
 *
 * @author			Bob Jacobsen  Copyright (C) 2006
 * @version 		$Revision: 22821 $
 *
 */
// /*public*/ class LnPr2Packetizer extends jmri.jmrix.loconet.LnPacketizer {

/*final*/ /*static*/ bool LnPr2Packetizer::fulldebug = false;

//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//                    justification="Only used during system initialization")
/*public*/ LnPr2Packetizer::LnPr2Packetizer(QObject* parent)
    : LnPacketizer(parent)
{
 //super();
 debug = false;
 self=this;
 echo = true;
 log = new Logger("LnPr2Packetizer");
 debug = log->isDebugEnabled();
}

//    static Logger log = LoggerFactory.getLogger(LnPr2Packetizer.class.getName());
//}
