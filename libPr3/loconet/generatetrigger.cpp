#include "generatetrigger.h"
#include "sdfbuffer.h"
#include "stringutil.h"
#include "sdfconstants.h"

//GenerateTrigger::GenerateTrigger(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the GENERATE_TRIGGER macro from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class GenerateTrigger extends SdfMacro {

/*public*/ GenerateTrigger::GenerateTrigger(int trigger,QObject *parent) :
SdfMacro(parent) {
    this->trigger = trigger;
}

/*public*/ QString GenerateTrigger::name() {
    return "GENERATE_TRIGGER";
}


/*public*/ int GenerateTrigger::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* GenerateTrigger::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFF) != 0xB1) {
        return NULL;
    }
    buff->getAtIndexAndInc(); // skip op ocde
    return new GenerateTrigger(buff->getAtIndexAndInc());
}

QString GenerateTrigger::triggerVal() {
    QString trigName = StringUtil::getNameFromState(trigger, SdfConstants::triggerCodes, SdfConstants::triggerNames);
    if (trigName != "") {
        return trigName;
    }
    return "(trigger = 0x" + StringUtil::twoHexFromInt(trigger) + ")";
}

/**
 * Store into a buffer->
 */
/*public*/ void GenerateTrigger::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(0xB1);
    buffer->setAtIndexAndInc(trigger);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString GenerateTrigger::toString() {
    return "Cause Trigger " + triggerVal() + '\n';
}

/*public*/ QString GenerateTrigger::oneInstructionString() {
    return name() + ' ' + triggerVal() + '\n';
}

/*public*/ QString GenerateTrigger::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
