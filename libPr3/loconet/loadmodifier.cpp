#include "loadmodifier.h"
#include "sdfbuffer.h"
#include "stringutil.h"
#include "sdfconstants.h"

//LoadModifier::LoadModifier(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the LOAD_MODIFIER macro from the Digitrax sound definition language
 *
 * Arg1: Upper 4 bits - math modifiers FMATH_LODE et al Arg2: Arg3:
 *
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class LoadModifier extends SdfMacro {

/*public*/ LoadModifier::LoadModifier(int byte0, int arg1, int arg2, int arg3, QObject *parent) :
  SdfMacro(parent) {
    this->modType = byte0 & 0x0F;
    this->byte0 = byte0;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;
}

/*public*/ QString LoadModifier::name() {
    return "LOAD_MODIFIER";
}

/*public*/ int LoadModifier::length() {
    return 4;
}

/*static*/ /*public*/ SdfMacro* LoadModifier::match(SdfBuffer* buff) {
    // course match
    if ((buff->getAtIndex() & 0xF0) != 0xE0) {
        return NULL;
    }
    int byte1 = buff->getAtIndexAndInc() & 0xFF;
    int byte2 = buff->getAtIndexAndInc() & 0xFF;
    int byte3 = buff->getAtIndexAndInc() & 0xFF;
    int byte4 = buff->getAtIndexAndInc() & 0xFF;
    return new LoadModifier(byte1, byte2, byte3, byte4);
}

QString LoadModifier::modTypeVal() {
    return StringUtil::getNameFromState(modType, SdfConstants::modControlCodes, SdfConstants::modControlNames);
}

/**
 * Format the three bytes as simple numbers, for lack of anything better
 * right now
 */
QString LoadModifier::argVal() {
    QString arg1Val = QString::number(arg1);
    QString arg2Val = QString::number(arg2);
    QString arg3Val = QString::number(arg3);
    return arg1Val + "," + arg2Val + "," + arg3Val;
}

/**
 * Store into a buffer.
 */
/*public*/ void LoadModifier::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(byte0);
    buffer->setAtIndexAndInc(arg1);
    buffer->setAtIndexAndInc(arg2);
    buffer->setAtIndexAndInc(arg3);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString LoadModifier::toString() {
    return "Set Modifier " + modTypeVal() + '\n';
}

/*public*/ QString LoadModifier::oneInstructionString() {
    QString args;
    QString arg1Val;
    QString arg2Val;
    QString arg3Val;
    QString temp1, temp2;

    switch (modType) {
        case SdfConstants::MTYPE_TIME:
            args = argVal();
            return name() + ' ' + modTypeVal() + "," + args + '\n';

        case SdfConstants::MTYPE_GAIN:
            // arg1 is IMMED_GAIN_MODIFY or ANALOG_GAIN_MODIFY
            // plus possible 5 bit modifier
            if ((arg1 & 0xE0) == SdfConstants::IMMED_GAIN_MODIFY) {
                if (arg1 == SdfConstants::IMMED_GAIN_MODIFY) {
                    arg1Val = "IMMED_GAIN_MODIFY";
                } else {
                    arg1Val = "IMMED_GAIN_MODIFY+0x" + StringUtil::twoHexFromInt(arg1 & 0x1f);
                }
            } else if ((arg1 & 0xE0) == SdfConstants::ANALOG_GAIN_MODIFY) {
                if (arg1 == SdfConstants::ANALOG_GAIN_MODIFY) {
                    arg1Val = "ANALOG_GAIN_MODIFY";
                } else {
                    arg1Val = "ANALOG_GAIN_MODIFY+"
                            + StringUtil::getNameFromState(arg1 & 0x1f, SdfConstants::workRegCodes, SdfConstants::workRegNames);
                }
            } else {
                arg1Val = StringUtil::twoHexFromInt(arg1);
            }
            arg2Val = StringUtil::getNameFromState(arg2, SdfConstants::fixedCVCodes, SdfConstants::fixedCVNames);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }
            arg3Val = decodeFlags(arg3, SdfConstants::arg3ModCodes, SdfConstants::arg3ModMasks, SdfConstants::arg3ModNames);
            if (arg3Val == NULL) {
                arg3Val = "0x" + StringUtil::twoHexFromInt(arg3);
            }
            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_PITCH:
            // arg1 is CV_PITCH_MODIFY or ANALOG_PITCH_MODIFY
            // plus possible 5 bit modifier
            if ((arg1 & 0xE0) == SdfConstants::CV_PITCH_MODIFY) {
                if (arg1 == SdfConstants::CV_PITCH_MODIFY) {
                    arg1Val = "CV_PITCH_MODIFY";
                } else {
                    arg1Val = "CV_PITCH_MODIFY+0x" + StringUtil::twoHexFromInt(arg1 & 0x1f);
                }
            } else if ((arg1 & 0xE0) == SdfConstants::ANALOG_PITCH_MODIFY) {
                if (arg1 == SdfConstants::ANALOG_PITCH_MODIFY) {
                    arg1Val = "ANALOG_PITCH_MODIFY";
                } else {
                    arg1Val = "ANALOG_PITCH_MODIFY+"
                            + StringUtil::getNameFromState(arg1 & 0x1f, SdfConstants::workRegCodes, SdfConstants::workRegNames);
                }
            } else {
                arg1Val = StringUtil::twoHexFromInt(arg1);
            }
            arg2Val = StringUtil::getNameFromState(arg2, SdfConstants::maxPCodes, SdfConstants::maxPNames);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }
            arg3Val = StringUtil::getNameFromState(arg3, SdfConstants::ditherPCodes, SdfConstants::ditherPNames);
            if (arg3Val == NULL) {
                arg3Val = "0x" + StringUtil::twoHexFromInt(arg3);
            }
            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_BLEND:
            arg1Val = decodeFlags(arg1, SdfConstants::blendArg1Codes, SdfConstants::blendArg1Masks, SdfConstants::blendArg1Names);

            arg2Val = StringUtil::getNameFromState(arg2, SdfConstants::blendArg2Codes, SdfConstants::blendArg2Names);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }

            arg3Val = StringUtil::getNameFromState(arg3, SdfConstants::blendArg3Codes, SdfConstants::blendArg3Names);
            if (arg3Val == NULL) {
                arg3Val = "0x" + StringUtil::twoHexFromInt(arg3);
            }

            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_SCATTER:
            arg1Val = StringUtil::getNameFromState(arg1 & 0x38, SdfConstants::scatCommandCodes, SdfConstants::scatCommandNames)
                    + "+" + StringUtil::getNameFromState(arg1 & 0x03, SdfConstants::scatChannelCodes, SdfConstants::scatChannelNames);

            arg2Val = StringUtil::getNameFromState(arg2, SdfConstants::fixedCVCodes, SdfConstants::fixedCVNames);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }

            arg3Val = StringUtil::getNameFromState(arg3, SdfConstants::sintenCodes, SdfConstants::sintenNames);
            if (arg3Val == NULL) {
                arg3Val = "0x" + StringUtil::twoHexFromInt(arg3);
            }

            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_SNDCV:
            arg1Val = StringUtil::getNameFromState(arg1, SdfConstants::fixedCVCodes, SdfConstants::fixedCVNames);
            if (arg1Val == NULL) {
                arg1Val = "0x" + StringUtil::twoHexFromInt(arg1);
            }
            arg2Val = QString::number(arg2);
            arg3Val = QString::number(arg3);
            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_WORK_IMMED:
            // math operations w immediate operands
            temp1 = StringUtil::getNameFromState(arg1 & 0xE0, SdfConstants::arg1ModCodes, SdfConstants::arg1ModNames);
            temp2 = StringUtil::getNameFromState(arg1 & 0x1F, SdfConstants::workRegCodes, SdfConstants::workRegNames);
            if (temp1 != NULL && temp2 != NULL) {
                arg1Val = temp1 + "+" + temp2;
            } else if (temp1 != NULL && temp2 == NULL) {
                arg1Val = temp1;
            } else if (temp1 == NULL && temp2 != NULL) {
                arg1Val = temp2;
            } else {
                arg1Val = "0"; // an odd error, actually
            }
            arg2Val = StringUtil::getNameFromState(arg2, SdfConstants::maxPCodes, SdfConstants::maxPNames);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }

            // occasionally see MERGE_ALL_MASK in arg3, but that's zero
            arg3Val = QString::number(arg3);

            // special cases
            //   status bit register
            if ((arg1 & 0x1F) == SdfConstants::WORK_STATUS_BITS) {
                arg2Val = decodeFlags(arg2, SdfConstants::workStatusBitCodes, SdfConstants::workStatusBitCodes, SdfConstants::workStatusBitNames);
            }
            if ((arg1 & 0x1F) == SdfConstants::WORK_GLBL_GAIN && arg2 == SdfConstants::DEFAULT_GLBL_GAIN) {
                arg2Val = "DEFAULT_GLBL_GAIN";
            }
            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';

        case SdfConstants::MTYPE_WORK_INDIRECT:
            // math operations from one reg to another
            temp1 = StringUtil::getNameFromState(arg1 & 0xE0, SdfConstants::arg1ModCodes, SdfConstants::arg1ModNames);
            temp2 = StringUtil::getNameFromState(arg1 & 0x1F, SdfConstants::workRegCodes, SdfConstants::workRegNames);
            if (temp1 != NULL && temp2 != NULL) {
                arg1Val = temp1 + "+" + temp2;
            } else if (temp1 != NULL && temp2 == NULL) {
                arg1Val = temp1;
            } else if (temp1 == NULL && temp2 != NULL) {
                arg1Val = temp2;
            } else {
                arg1Val = "0"; // an odd error, actually
            }
            arg2Val = StringUtil::getNameFromState(arg2 & 0x1F, SdfConstants::workRegCodes, SdfConstants::workRegNames);
            if (arg2Val == NULL) {
                arg2Val = "0x" + StringUtil::twoHexFromInt(arg2);
            }

            // occasionally see MERGE_ALL_MASK in arg3, but that's zero
            arg3Val = QString::number(arg3);

            return name() + ' ' + modTypeVal() + "," + arg1Val + "," + arg2Val + "," + arg3Val + '\n';
    }
    return "<could not parse, should not happen>";
}

/*public*/ QString LoadModifier::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
