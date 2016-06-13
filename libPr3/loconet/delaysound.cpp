#include "delaysound.h"
#include "sdfbuffer.h"
#include "sdfconstants.h"

//DelaySound::DelaySound(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the DELAY_SOUND macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
 * @version $Revision: 28746 $
 */
///*public*/ class DelaySound extends SdfMacro {

/*public*/ DelaySound::DelaySound(int byte1, int byte2 , QObject *parent) :
SdfMacro(parent) {
    this->mode = byte2 & 0x80;
    this->value = byte2 & 0x7F;
    this->glbl = byte1 & 0x01;
    this->byte1 = byte1;
    this->byte2 = byte2;
}

/*public*/ QString DelaySound::name() {
    return "DELAY_SOUND";
}

/*public*/ int DelaySound::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* DelaySound::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFE) != 0xB4) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc();
    return new DelaySound(byte1, byte2);
}

/**
 * Store into a buffer.
 */
/*public*/ void DelaySound::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString DelaySound::toString() {
    return "Delay Sound\n";
}

/*public*/ QString DelaySound::oneInstructionString() {
    QString modeVal = (SdfConstants::DELAY_THIS == mode) ? "DELAY_THIS" : "DELAY_CV";
    QString valueVal = (SdfConstants::DELAY_THIS == mode) ? QString::number(value) : "CV=" + QString::number(value);
    QString glblVal = (glbl == 1) ? "DELAY_GLOBAL" : "0";  // what should 0 case be?
    return name() + ' ' + modeVal + "," + valueVal + "," + glblVal + '\n';
}

/*public*/ QString DelaySound::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
