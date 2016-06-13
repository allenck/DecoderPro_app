#include "sdfmacro.h"
#include "stringutil.h"
#include "logger.h"
#include "channelstart.h"
#include "skemestart.h"
#include "sdlversion.h"
#include "endsound.h"
#include "generatetrigger.h"
#include "delaysound.h"
#include "twobytemacro.h"
#include "fourbytemacro.h"
#include "skipontrigger.h"
#include "initiatesound.h"
#include "play.h"
#include "maskcompare.h"
#include "loadmodifier.h"
#include "branchto.h"

SdfMacro::SdfMacro(QObject *parent) :
  QObject(parent)
{
 children = NULL;
 log = new  Logger("SdfMacro");
}
/**
 * Common base for all the SDF macros defined by Digitrax for their sound
 * definition language
 * <p>
 * Each macro has a number of descriptive forms:
 * <dl>
 * <dt>name()<dd>Just the name, in MPASM form.
 * <dt>toString()<dd>A brief description, with a terminating newline
 * <dt>oneInstructionString()<dd>The entire single instruction in MPASM from,
 * with a terminating newline
 * <dt>allInstructionString()<dd>The instruction and all those logically grouped
 * within it.
 * <dt>name()<dd>
 * </dl>
 * <P>
 * SdfMacro and its subclasses don't do the notification needed to be Models in
 * an MVC edit paradyme. This is because there are a lot of SdfMacros in
 * realistic sound file, and the per-object overhead needed would be too large.
 * Hence (or perhaps because of no need), there is no support for simultaneous
 * editing of a single macro instruction updating multiple windows. You can have
 * multiple editors open on a single SdfBuffer, but these are not interlocked
 * against each other. (We could fix this by having a shared pool of "objects to
 * be notified of changes in the SdfBuffer, acccessed by reference during
 * editing (to avoid another dependency), but that's a project for another day)
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version $Revision: 28771 $
 */
///*public*/ abstract class SdfMacro implements SdfConstants {

/**
 * Name used by the macro in the SDF definition
 *
 * @return Fixed name associated with this type of instructio
 */
/*abstract*/ /*public*/ QString SdfMacro::name() {return "";}

/**
 * Provide number of bytes defined by this macro
 *
 * @return Fixed numher of bytes defined (a constant for the instruction
 *         type)
 */
/*abstract*/ /*public*/ int SdfMacro::length() { return 0;}

/**
 * Provide a single-line simplified representation, including the trailing
 * newline. This is used e.g. in the tree format section of the
 * {@link jmri.jmrix.loconet.sdfeditor.EditorFrame}.
 *
 * @return newline-terminated string; never NULL
 */
/*abstract*/ /*public*/ QString SdfMacro::toString() {return "";}

/**
 * Provide single instruction in MPASM format, including the trailing
 * newline.
 *
 * @return Newline terminated string, never NULL
 */
/*abstract*/ /*public*/ QString SdfMacro::oneInstructionString() {return "";}

/**
 * Provide instructions in MPASM format, including the trailing newline and
 * all nested instructions.
 *
 * @return Newline terminated string, never NULL
 * @param indent String inserted at the start of each output line, typically
 *               some number of spaces.
 */
/*abstract*/ /*public*/ QString SdfMacro::allInstructionString(QString indent) {return "";}

/**
 * Access child (nested) instructions.
 *
 * @return List of children, which will be NULL except in case of nesting.
 */
/*public*/ QList<SdfMacro*>* SdfMacro::getChildren() {
    return children;
}

/**
 * Total length, including contained instructions
 */
/*public*/ int SdfMacro::totalLength() {
    int result = length();
    QList<SdfMacro*>* l = getChildren();
    if (l == NULL) {
        return result;
    }
    for (int i = 0; i < l->size(); i++) {
        result += l->at(i)->totalLength();
    }
    return result;
}

/**
 * Store into a buffer.
 * <P>
 * This provides a default implementation for children, but each subclass
 * needs to store it's own data with setAtIndexAndInc()
 */
/*public*/ void SdfMacro::loadByteArray(SdfBuffer* buffer) {
    QList<SdfMacro*>* l = getChildren();
    if (l==NULL) {
        return;
    }
    for (int i = 0; i < l->size(); i++) {
        l->at(i)->loadByteArray(buffer);
    }
}

/**
 * Return the next instruction macro in a buffer.
 * <P>
 * Note this uses the index contained in the SdfBuffer implementation, and
 * has the side-effect of bumping that forward.
 *
 * @param buff The SdfBuffer being scanned for instruction macros.
 * @return Object of SdfMacro subtype for specific next instruction
 */
/*static*/ /*public*/ SdfMacro* SdfMacro::decodeInstruction(SdfBuffer* buff)
{
    SdfMacro* m;
    Logger log("SdfMacro");

    // full 1st byte decoder
    if ((m = ChannelStart::match(buff)) != NULL)
    {
     return m;
    }
    else if ((m = SdlVersion::match(buff)) != NULL)
    {
     return m;
    }
    else if ((m = SkemeStart::match(buff)) != NULL)
    {
     return m;
    }
    else if ((m = GenerateTrigger::match(buff)) != NULL) {
        return m;
    }
    else if ((m = EndSound::match(buff)) != NULL) {
        return m;
    }
    else // 7 bit decode
    if ((m = DelaySound::match(buff)) != NULL) {
        return m;
    }
    else // 6 bit decode
    if ((m = SkipOnTrigger::match(buff)) != NULL) {
        return m;
    }
    else // 5 bit decode
    if ((m = InitiateSound::match(buff)) != NULL) {
        return m;
    }
    else if ((m = MaskCompare::match(buff)) != NULL) {
        return m;
    }
    else // 4 bit decode
    if ((m = LoadModifier::match(buff)) != NULL) {
        return m;
    }
    else if ((m = BranchTo::match(buff)) != NULL) {
        return m;
    }

    else // 2 bit decode
    if ((m = Play::match(buff)) != NULL) {
        return m;
    }
    else // generics
    if ((m = FourByteMacro::match(buff)) != NULL) {
        return m;
    }
    else if ((m = TwoByteMacro::match(buff)) != NULL) {
        return m;
    }

    log.warn("dropped through");
    return NULL;
}

/**
 * Service method to unpack various bit-coded values for display, using a
 * mask array.
 * <P>
 * Note that multiple values can be returned, e.g. this can be used to scan
 * for individual bits set in a variable.
 *
 * @param input  Single value to be matched
 * @param values Array of possible values which the input might match
 * @param masks  Array of masks to be applied when comparing against the
 *               corresponding items in the values array. This is separate
 *               for each possible value to e.g. allow the encoding of a set
 *               of independent bits.
 * @param labels Should there be a match-under-mask of a value, the
 *               corresponding label is returned
 * @return "+" separated list of labels, or "&lt;ERROR&gt;" if none matched
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
QString SdfMacro::decodeFlags(int input, QVector<int> values, QVector<int> masks, QStringList labels)
{
    QStringList names = StringUtil::getNamesFromStateMasked(input, values, masks, labels);
    if (names.isEmpty()) {
        return "<ERROR>"; // unexpected case, internal error, should also log?
    } else if (names.length() == 0) {
     return labels.at(labels.length() - 1);  // last name is non-of-above special case
    } else if (names.length() == 1) {
        return names.at(0);
    }
    QString output = names.at(0);
    for (int i = 1; i < names.length(); i++) {
        output += "+" + names.at(i);
    }
    return output;
}

QString SdfMacro::decodeState(int input, QVector<int> values, QStringList labels) {
    QString val = StringUtil::getNameFromState(input, values, labels);
    if (val.isEmpty()) {
     return labels.at(labels.length() - 1);
    }
    return val;
}
