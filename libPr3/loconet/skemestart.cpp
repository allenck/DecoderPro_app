#include "skemestart.h"
#include "sdfbuffer.h"

//SkemeStart::SkemeStart(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the SKEME_START macro from the Digitrax sound definition language.
 * <P>
 * This nests until the next SKEME_START.
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
 * @version $Revision: 28746 $
 */
///*public*/ class SkemeStart extends SdfMacro {

/*public*/ SkemeStart::SkemeStart(int byte1, int byte2, int byte3, int byte4, QObject* parent) : SdfMacro(parent)
{
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
    this->byte4 = byte4;

    this->number = byte2;
    this->_length = byte3 * 256 + byte4;
}

/*public*/ int SkemeStart::getNumber() {
    return number;
}

/*public*/ void SkemeStart::setNumber(int num) {
    number = num;
    byte2 = num;
}

/*public*/ QString SkemeStart::name() {
    return "SKEME_START";
}

/*public*/ int SkemeStart::length() {
    return 4;
}

/*static*/ /*public*/ SdfMacro* SkemeStart::match(SdfBuffer* buff) {
    // course match
    if ((buff->getAtIndex() & 0xFF) != 0xF1) {
        return NULL;
    }

    int byte1 = buff->getAtIndexAndInc(); // skip op code
    int byte2 = buff->getAtIndexAndInc();
    int byte3 = buff->getAtIndexAndInc();
    int byte4 = buff->getAtIndexAndInc();

    SkemeStart* result = new SkemeStart(byte1, byte2, byte3, byte4);

    // gather leaves underneath
    SdfMacro* next;
    while (buff->moreData()) {
        // look ahead at next instruction
        int peek = buff->getAtIndex() & 0xFF;

        // if SKEME_START, done
        if (peek == 0xF1) {
            break;
        }

        // next is leaf, keep it
        next = decodeInstruction(buff);
        if (result->children == NULL) {
            result->children = new QList<SdfMacro*>(); // make sure it's initialized
        }
        result->children->append(next);
    }
    return result;
}

/**
 * Store into a buffer.
 */
/*public*/ void SkemeStart::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);
    buffer->setAtIndexAndInc(byte3);
    buffer->setAtIndexAndInc(byte4);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString SkemeStart::toString() {
    return "Scheme " + QString::number(number) + "\n";
}

/*public*/ QString SkemeStart::oneInstructionString()
{
 return name() + ' ' + QString::number(number) + "; length=" + QString::number(_length) + '\n';
}

/*public*/ QString SkemeStart::allInstructionString(QString indent) {
 QString output;
 output = indent + oneInstructionString();

 if (children == NULL) {
     return output;
 }
 for (int i = 0; i < children->size(); i++) {
     output += children->at(i)->allInstructionString(indent + "  ");
 }
 return output;
}
