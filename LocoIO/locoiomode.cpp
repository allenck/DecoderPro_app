#include "locoiomode.h"

LocoIOMode::LocoIOMode(QObject *parent) :
    QObject(parent)
{
}
/**
     * Creates a new instance of LocoIOMode
     */
    /*public*/ LocoIOMode::LocoIOMode(int isOutput, int opcode, int sv0, int sv2, QString mode) {
        this->isOutput   = isOutput;
        this->opcode     = opcode;
        this->sv0        = sv0;
        this->sv2        = sv2;
        this->mode       = mode;
    }

    /*public*/ QString LocoIOMode::getMode()     { return mode; }
    /*public*/ QString LocoIOMode::getFullMode() { return ((isOutput == 1) ? "Output: " : "Input: ") + mode + "  "; }
    /*public*/ int    LocoIOMode::getOutput()   { return isOutput; }
    /*public*/ int    LocoIOMode::getOpcode()   { return opcode; }
    /*public*/ int    LocoIOMode::getSV()       { return sv0; }
    /*public*/ int    LocoIOMode::getV2()       { return sv2; }

