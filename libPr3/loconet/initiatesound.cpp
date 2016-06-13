#include "initiatesound.h"
#include "sdfbuffer.h"
#include "stringutil.h"

//InitiateSound::InitiateSound(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the INITIATE_SOUND macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class InitiateSound extends SdfMacro {

/*public*/ InitiateSound::InitiateSound(int byte1, int byte2, QObject *parent) :
SdfMacro(parent) {
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->trigger = byte2 & 0x7f;
    this->prempt = (byte1 & 0x7) + (byte2 & 0x80);
}

/*public*/ QString InitiateSound::name() {
    return "INITIATE_SOUND";
}

/*public*/ int InitiateSound::getTrigger() {
    return trigger;
}

/*public*/ void InitiateSound::setTrigger(int t) {
    trigger = t & 0x7f;
    byte2 = (byte2 & 0x80) | (t & 0x7f);
}

/*public*/ int InitiateSound::getPrempt() {
    return prempt;
}

/*public*/ void InitiateSound::setPrempt(int prempt) {
    byte1 = (byte1 & 0xF8) | (prempt & 0x7);
    byte2 = (byte2 & 0x7F) | (prempt & 0x80);
    this->prempt = (byte1 & 0x7) + (byte2 & 0x80);
}

/*public*/ int InitiateSound::length() {
    return 2;
}

QString InitiateSound::premptVal() {
    return decodeFlags(prempt, SdfConstants::premptCodes, SdfConstants::premptMasks, SdfConstants::premptNames);
}

QString InitiateSound::triggerVal() {
    QString trigName = StringUtil::getNameFromState(trigger, SdfConstants::triggerCodes, SdfConstants::triggerNames);
    if (trigName != "") {
        return trigName;
    }
    return "(trigger = 0x" + StringUtil::twoHexFromInt(trigger) + ")";
}

/*static*/ /*public*/ SdfMacro* InitiateSound::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xF8) != 0x90) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc();
    InitiateSound* result = new InitiateSound(byte1, byte2);

    // gather leaves underneath
    SdfMacro* next;
    while (buff->moreData()) {
        // look ahead at next instruction
        int peek = buff->getAtIndex() & 0xFF;

        // if SKEME_START, CHANNEL_START, done
        // Note that INITIATE_SOUND can be nested, so isn't here
        if (peek == 0xF1
                || peek == 0x81) {
            break;
        }

        // if this is a INITIATE_SOUND, process it _without_
        // allowing recursion
        if ((peek & 0xF8) == 0x90) {
            // manually create next
            byte1 = buff->getAtIndexAndInc();
            byte2 = buff->getAtIndexAndInc();
            next = new InitiateSound(byte1, byte2);
        } else {
            // next is leaf, keep it
            next = decodeInstruction(buff);
        }
        if (result->children == NULL) {
            result->children = new QList<SdfMacro*>(); // make sure it's initialized
        }
        result->children->append(next);

        // if this was an END_SOUND, we're done now that we've included it
        if (peek == 0x00) {
            break;
        }
    }
    return result;
}

/**
 * Store into a buffer.
 */
/*public*/ void InitiateSound::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString InitiateSound::toString() {
    return "Define Sequence " + triggerVal() + "," + premptVal() + '\n';
}

/*public*/ QString InitiateSound::oneInstructionString() {
    return name() + " " + triggerVal() + "," + premptVal() + '\n';
}

/*public*/ QString InitiateSound::allInstructionString(QString indent) {
    QString output = indent + oneInstructionString();
    if (children == NULL) {
        return output;
    }
    for (int i = 0; i < children->size(); i++) {
        output += children->at(i)->allInstructionString(indent + "  ");
    }
    return output;
}
