#include "endsound.h"
#include "sdfbuffer.h"

//EndSound(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the END_SOUND macro from the Digitrax sound definition language.
 *
 * This carries no additional information.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class EndSound extends SdfMacro {

/*public*/ EndSound::EndSound(int byte1, int byte2,QObject *parent) :
    SdfMacro(parent)
{
}

/*public*/ QString EndSound::name() {
    return "END_SOUND";
}

/*public*/ int EndSound::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* EndSound::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFF) != 0x00) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc(); // skip bytes
    return new EndSound(byte1, byte2);
}

/**
 * Store into a buffer.
 */
/*public*/ void EndSound::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString EndSound::toString() {
    return "End Sequence\n";
}

/*public*/ QString EndSound::oneInstructionString() {
    return name() + '\n';
}

/*public*/ QString EndSound::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
