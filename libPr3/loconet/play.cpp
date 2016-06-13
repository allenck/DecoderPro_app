#include "play.h"
#include "sdfbuffer.h"
#include "sdfconstants.h"
#include "stringutil.h"

//Play::Play(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the PLAY macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
 ///*public*/ class Play extends SdfMacro {

 /*public*/ Play::Play(int byte1, int byte2, QObject *parent) :
SdfMacro(parent) {
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->handle = byte2 & 0x3F;
    this->wavebrkFlags = byte1 & 0x18;
    this->brk = ((byte1 & 0x7) << 2) + ((byte2 & 0xC0) >> 6);
    this->byte1 = byte1;
    this->byte2 = byte2;
}

 /*public*/  QString Play::name() {
    return "PLAY";
}

 /*public*/  QString Play::handleVal() {
    return QString::number(handle);
}

 /*public*/ void Play::setHandle(int val) {
    this->handle = val;
    this->byte2 = (this->byte2 & 0xC0) | (val & 0x3f);
}

 /*public*/  QString Play::brkVal() {
    return decodeState(brk, SdfConstants::loopCodes, SdfConstants::loopNames);
}

 /*public*/ void Play::setBrk( QString name) {
    int val = StringUtil::getStateFromName(name, SdfConstants::loopCodes, SdfConstants::loopNames.toVector());
    if (val == -1) {
        val = 0; // no match found is defaulted to zero
    }
    setBrk(val);
}

 /*public*/ void Play::setBrk(int n) {
    // argument is 0 - 31
    this->byte1 = (this->byte1 & 0xF8) | ((n >> 2) & 0x7);
    this->byte2 = (this->byte2 & 0x3F) | ((n << 6) & 0xC0);
    this->brk = ((byte1 & 0x7) << 2) + ((byte2 & 0xC0) >> 6);
}

 /*public*/  QString Play::wavebrkFlagsVal() {
    return decodeFlags(wavebrkFlags, SdfConstants::wavebrkCodes, SdfConstants::wavebrkMasks, SdfConstants::wavebrkNames);
}

 /*public*/ int Play::getWaveBrkFlags() {
    return this->wavebrkFlags >> 3;
}

// doesn't handle case of GLOBAL+INVERT!
/*public*/ void Play::setWaveBrkFlags( QString name) {
    int val = StringUtil::getStateFromName(name,SdfConstants:: wavebrkCodes, SdfConstants::wavebrkNames.toVector());
    if (val == -1) {
        val = 0;  // no match found is defaulted to zero
    }
    setWaveBrkFlags(val >> 3);
}

/*public*/ void Play::setWaveBrkFlags(int n) {
    // argument is 0,1,2,3
    this->byte1 = (this->byte1 & 0xE7) | ((n << 3) & 0x18);
    this->wavebrkFlags = byte1 & 0x18;
}

/*public*/ int Play::length() {
    return 2;
}

/*static*/  /*public*/ SdfMacro* Play::match(SdfBuffer* buff) {
    // course match
    if ((buff->getAtIndex() & 0xC0) != 0x40) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc();
    return new Play(byte1, byte2);
}

/**
 * Store into a buffer.
 */
/*public*/ void Play::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/  QString Play::toString() {
    return "Play Fragment " + handleVal() + '\n';
}

/*public*/  QString Play::oneInstructionString() {
    return name() + ' ' + handleVal() + ',' + brkVal() + ',' + wavebrkFlagsVal() + '\n';
}

/*public*/  QString Play::allInstructionString( QString indent) {
    return indent + oneInstructionString();
}
