#include "branchto.h"
#include "sdfbuffer.h"

//BranchTo::BranchTo(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the BRANCH_TO macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class BranchTo extends SdfMacro {

/*public*/ BranchTo::BranchTo(int byte1, int byte2,QObject *parent) :
SdfMacro(parent) {
    this->addr = (byte1 & 0x0F) * 256 + byte2;
    this->skemebase = 0;  // probably not right!
    this->byte1 = byte1;
    this->byte2 = byte2;
}

/*public*/ QString BranchTo::name() {
    return "BRANCH_TO";
}

/*public*/ int BranchTo::length() {
    return 2;
}


/*static*/ /*public*/ SdfMacro* BranchTo::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xF0) != 0xC0) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc();
    int byte2 = buff->getAtIndexAndInc();
    return new BranchTo(byte1, byte2);
}

/**
 * Store into a buffer->
 */
/*public*/ void BranchTo::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte1);
    buffer->setAtIndexAndInc(byte2);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString BranchTo::toString() {
    return "Branch\n";
}

/*public*/ QString BranchTo::oneInstructionString() {
    return name() + ' ' + addr + "; from base of " + QString::number(skemebase) + '\n';
}

/*public*/ QString BranchTo::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
