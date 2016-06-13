#include "channelstart.h"
#include "sdfbuffer.h"

//ChannelStart::ChannelStart(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the CHANNEL_START macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class ChannelStart extends SdfMacro {

/*public*/ ChannelStart::ChannelStart(int number,QObject *parent) :
  SdfMacro(parent)
{
    this->number = number;
}

/*public*/ QString ChannelStart::name() {
    return "CHANNEL_START";
}

/*public*/ int ChannelStart::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* ChannelStart::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFF) != 0x81) {
        return NULL;
    }
    buff->getAtIndexAndInc(); // drop opcode
    ChannelStart* result = new ChannelStart(buff->getAtIndexAndInc());

    // gather leaves underneath
    SdfMacro* next;
    while (buff->moreData()) {
        // look ahead at next instruction
        int peek = buff->getAtIndex() & 0xFF;

        // if SKEME_START or CHANNEL_START, done
        if (peek == 0xF1
                || peek == 0x81) {
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
/*public*/ void ChannelStart::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(0x81);
    buffer->setAtIndexAndInc(number);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString ChannelStart::toString() {
    return "Channel " + QString::number(number) + '\n';
}

/*public*/ QString ChannelStart::oneInstructionString() {
    return name() + ' ' + QString::number(number) + '\n';
}

/*public*/ QString ChannelStart::allInstructionString(QString indent) {
    QString output = indent + oneInstructionString();
    if (children == NULL) {
        return output;
    }
    for (int i = 0; i < children->size(); i++) {
        output += children->at(i)->allInstructionString(indent + "  ");
    }
    return output;
}
