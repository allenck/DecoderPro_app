#include "sdlversion.h"
#include "sdfbuffer.h"

//SdlVersion::SdlVersion(QObject *parent) :
//  SdfMacro(parent)
//{
//}
/**
 * Implement the SDL_VERSION macro from the Digitrax sound definition language
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class SdlVersion extends SdfMacro {

/*public*/ SdlVersion::SdlVersion(int version, QObject *parent) :
  SdfMacro(parent) {
    this->version = version;
}

/*public*/ QString SdlVersion::name() {
    return "SDL_VERSION";
}

/*public*/ int SdlVersion::length() {
    return 2;
}

/*static*/ /*public*/ SdfMacro* SdlVersion::match(SdfBuffer* buff) {
    if ((buff->getAtIndex() & 0xFF) != 0x82) {
        return NULL;
    }
    buff->getAtIndexAndInc(); // drop op code
    return new SdlVersion(buff->getAtIndexAndInc());
}

/**
 * Store into a buffer.
 */
/*public*/ void SdlVersion::loadByteArray(SdfBuffer* buffer) {
    // data
    buffer->setAtIndexAndInc(0x82);
    buffer->setAtIndexAndInc(version);

    // store children
    SdfMacro::loadByteArray(buffer);
}

/*public*/ QString SdlVersion::toString() {
    return QString("Version ") + (version == 0x10 ? "1" : "<unknown code>") + '\n';
}

/*public*/ QString SdlVersion::oneInstructionString() {
    return name() + ' ' + (version == 0x10 ? "VERSION_1" : "Unknown code " + QString::number(version)) + '\n';
}

/*public*/ QString SdlVersion::allInstructionString(QString indent) {
    return indent + oneInstructionString();
}
