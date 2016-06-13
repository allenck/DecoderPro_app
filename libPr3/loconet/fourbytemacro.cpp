#include "fourbytemacro.h"
#include "sdfbuffer.h"
#include <QVector>
#include "stringutil.h"

//FourByteMacro::FourByteMacro(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement generic four-byte macros from the Digitrax sound definition
 * language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class FourByteMacro extends SdfMacro {

/*public*/ FourByteMacro::FourByteMacro(int byte1, int byte2, int byte3, int byte4, QObject *parent) :
SdfMacro(parent) {
    bytes->replace(0, (char) (byte1 & 0xFF));
    bytes->replace(1, (char) (byte2 & 0xFF));
    bytes->replace(2, (char) (byte3 & 0xFF));
    bytes->replace(3,  (char) (byte4 & 0xFF));
    bytes = new QVector<char>(4);
}

/*public*/ QString FourByteMacro::name() {
    return "Four Byte Macro";
}


/*public*/ int FourByteMacro::length() {
    return 4;
}

/*static*/ /*public*/ SdfMacro* FourByteMacro::match(SdfBuffer* buff) {
    // course match
    if ((buff->getAtIndex() & 0xFF) < 0xE0) {
        return NULL;
    }
    return new FourByteMacro(buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc());
}

/**
 * Store into a buffer.
 */
/*public*/ void FourByteMacro::loadByteArray(SdfBuffer* buffer) {
    // data
 buffer->setAtIndexAndInc(bytes->at(0));
 buffer->setAtIndexAndInc(bytes->at(1));
 buffer->setAtIndexAndInc(bytes->at(2));
    buffer->setAtIndexAndInc(bytes->at(3));

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString FourByteMacro::toString() {
    return name() + ' ' + StringUtil::hexStringFromBytes(bytes) + '\n';
}

/*public*/ QString FourByteMacro::oneInstructionString() {
    return name() + ' ' + StringUtil::hexStringFromBytes(bytes) + '\n';
}

/*public*/ QString FourByteMacro::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
