#include "twobytemacro.h"
#include "stringutil.h"
#include "sdfbuffer.h"

//TwoByteMacro::TwoByteMacro()
//{
//}
/**
 * Implement generic two-byte macros from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class TwoByteMacro extends SdfMacro {

/*public*/ TwoByteMacro::TwoByteMacro(int byte1, int byte2, QObject* parent)
: SdfMacro(parent)
{
  bytes->replace(0, (char) (byte1 & 0xFF));
  bytes->replace(1, (char) (byte2 & 0xFF));
  bytes = new QVector<char>(2);
}

/*public*/ QString TwoByteMacro::name() {
    return "Two Byte Macro";
}


/*public*/ int TwoByteMacro::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* TwoByteMacro::match(SdfBuffer* buff) {
    // always match
    return new TwoByteMacro(buff->getAtIndexAndInc(), buff->getAtIndexAndInc());
}

/**
 * Store into a buffer.
 */
/*public*/ void TwoByteMacro::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(bytes->at(0));
    buffer->setAtIndexAndInc(bytes->at(1));

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString TwoByteMacro::toString() {
    return name() + ' ' + StringUtil::hexStringFromBytes(bytes) + '\n';
}

/*public*/ QString TwoByteMacro::oneInstructionString() {
    return name() + ' ' + StringUtil::hexStringFromBytes(bytes) + '\n';
}

/*public*/ QString TwoByteMacro::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
