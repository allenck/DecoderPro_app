#include "skipontrigger.h"
#include "sdfbuffer.h"
#include "stringutil.h"
#include "sdfconstants.h"

//SkipOnTrigger::SkipOnTrigger(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the SKIP_ON_TRIGGER macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
 * @version $Revision: 28746 $
 */
///*public*/ class SkipOnTrigger extends SdfMacro {

/*public*/ SkipOnTrigger::SkipOnTrigger(int byte1, int byte2, QObject* parent)
 : SdfMacro(parent)
{
 this->byte1 = byte1;
 this->byte2 = byte2;
 this->logic = byte1 & 0x03;
 this->trigger = byte2;
}

/*public*/ QString SkipOnTrigger::name() {
    return "SKIP_ON_TRIGGER";
}

/*public*/ int SkipOnTrigger::length() {
    return 2;
}

QString SkipOnTrigger::logicVal() {
    return decodeFlags(logic, SdfConstants::trigLogicCodes, SdfConstants::trigLogicMasks, SdfConstants::trigLogicNames);
}

QString SkipOnTrigger::triggerVal() {
    QString trigName = StringUtil::getNameFromState(trigger, SdfConstants::triggerCodes, SdfConstants::triggerNames);
    if (trigName != NULL) {
        return trigName;
    }
    return "(trigger = 0x" + StringUtil::twoHexFromInt(trigger) + ")";
}

/*static*/ /*public*/ SdfMacro* SkipOnTrigger::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFC) != 0x04) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc();
    return new SkipOnTrigger(byte1, byte2);
}

/**
 * Store into a buffer.
 */
/*public*/ void SkipOnTrigger::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString SkipOnTrigger::toString() {
    return "Skip on Trigger\n";
}

/*public*/ QString SkipOnTrigger::oneInstructionString() {
    return name() + ' ' + logicVal() + ", " + triggerVal() + '\n';
}

/*public*/ QString SkipOnTrigger::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
