#include "acelareply.h"

/**
 * Contains the data payload of an Acela reply packet
 *
 * @author Bob Jacobsen Copyright (C) 2002
 *
 * @author Bob Coleman, Copyright (C) 2007, 2008 Based on CMRI serial example,
 * modified to establish Acela support.
 */
// /*public*/ class AcelaReply extends jmri.jmrix.AbstractMRReply {

    // Create a new one
    /*public*/  AcelaReply::AcelaReply(QObject* parent) : AbstractMRReply(parent){
        //super();
    }

    /*public*/  AcelaReply::AcelaReply(QString s, QObject* parent) : AbstractMRReply(s, parent) {
        //super(s);
    }

    /*public*/  AcelaReply::AcelaReply(AcelaReply* l, QObject* parent) : AbstractMRReply(l,parent) {
//        AbstractMRReply(l);
        l->setBinary(true);
    }

    //  Must be here since it is declared abstract
    //@Override
    /*protected*/ int AcelaReply::skipPrefix(int index) {
        // doesn't have to do anything
        return index;
    }

