#include "maskcompare.h"
#include "sdfbuffer.h"
#include "stringutil.h"
//MaskCompare::MaskCompare(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the MASK_COMPARE macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class MaskCompare extends SdfMacro {

/*public*/ MaskCompare::MaskCompare(int byte1, int byte2, int byte3, int byte4, QObject *parent) :
SdfMacro(parent) {
 bytes = QVector<char>(4);
    bytes.replace(0, (char) (byte1 & 0xFF));
    bytes.replace(1, (char) (byte2 & 0xFF));
    bytes.replace(2, (char) (byte3 & 0xFF));
    bytes.replace(3, (char) (byte4 & 0xFF));

    src = byte2;
    immed = byte1 & 0x04;
    targ = byte3;
    mask = byte4;
    skip = byte1 & 0x03;
}

/*public*/ QString MaskCompare::name() {
    return "MASK_COMPARE";
}

/*public*/ int MaskCompare::length() {
    return 4;
}

QString MaskCompare::srcVal() {
    return "(src = " + QString::number(src) + ")";
}

QString MaskCompare::immedVal() {
    if (immed != 0) {
        return "IMMED_DATA";
    } else {
        return "TARGET_DATA";
    }
}

QString MaskCompare::argVal() {
    return "(target = " + QString::number(targ) + ")";
}

QString MaskCompare::maskVal() {
    return "(mask = " + QString::number(mask) + ")";
}

QString MaskCompare::skipVal() {
    return "(skip = " + QString::number(skip) + ")";
}

/*static*/ /*public*/ SdfMacro* MaskCompare::match(SdfBuffer* buff) {
    // course match
    if ((buff->getAtIndex() & 0xF8) != 0xF8) {
        return NULL;
    }
    return new MaskCompare(buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc(),
            buff->getAtIndexAndInc());
}

/**
 * Store into a buffer->
 */
/*public*/ void MaskCompare::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(bytes[0]);
    buffer->setAtIndexAndInc(bytes[1]);
    buffer->setAtIndexAndInc(bytes[2]);
    buffer->setAtIndexAndInc(bytes[3]);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString MaskCompare::toString() {
    return "Check Mask\n";
}

/*public*/ QString MaskCompare::oneInstructionString() {
    return name() + ' ' + StringUtil::hexStringFromBytes(&bytes) + '\n';
}

/*public*/ QString MaskCompare::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
