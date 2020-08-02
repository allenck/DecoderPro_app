#include "matrixsignalmast.h"
#include "loggerfactory.h"
#include "turnout.h"
#include "instancemanager.h"
#include "defaultsignalappearancemap.h"
#include "vptr.h"

/**
 * SignalMast implemented via a Binary Matrix (Truth Table) of Apects x Turnout objects.
 * <p>
 * A MatrixSignalMast is built up from an array of turnouts to control each aspect.
 * System name specifies the creation information (except for the actual output beans):
 * <pre>
 * IF$xsm:basic:one-searchlight:($0001)-3t
 * </pre> The name is a colon-separated series of terms:
 * <ul>
 * <li>IF$xsm - defines signal masts of this type (x for matri<b>X</b>)
 * <li>basic - name of the signaling system
 * <li>one-searchlight - name of the particular aspect map/mast model
 * <li>($0001) - small ordinal number for telling various matrix signal masts apart
 * <li>name ending in -nt for (binary) Turnout outputs
 * where n = the number of binary outputs, between 1 and mastBitNum i.e. -3t</li>
 * </ul>
 *
 * @author Bob Jacobsen Copyright (C) 2009, 2014, 2020
 * @author Egbert Broerse Copyright (C) 2016, 2018, 2020
 */
// /*public*/ class MatrixSignalMast extends AbstractSignalMast {

/**
 *  Number of columns in logix matrix, default to 6, set in Matrix Mast panel &amp; on loading xml.
 *  Used to set size of char[] bitString.
 *  See MAXMATRIXBITS in {@link jmri.jmrit.beantable.signalmast.MatrixSignalMastAddPane}.
 */
/*static*/ QString MatrixSignalMast::errorChars = "nnnnnn";

/*static*/ QString MatrixSignalMast::emptyChars = "000000"; // default starting value

/*private*/ /*static*/ /*final*/ QString MatrixSignalMast::mastType = "IF$xsm";

/*public*/ MatrixSignalMast::MatrixSignalMast(QString systemName, QString userName, QObject *parent) : AbstractSignalMast(systemName, userName, parent)
{
 common();
    //super(systemName, userName);
    configureFromName(systemName);
}

/*public*/ MatrixSignalMast::MatrixSignalMast(QString systemName, QObject *parent)
 : AbstractSignalMast(systemName, parent)
{
 common();
    //super(systemName);
    configureFromName(systemName);
}

void MatrixSignalMast::common()
{
 errorBits = errorChars.toLocal8Bit();
 emptyBits =emptyChars.toLocal8Bit();
 aspectToOutput = QMap<QString, QByteArray>(/*16*/); // "Clear" - 01001 char[] pairs
 outputsToBeans = QMap<QString, NamedBeanHandle<Turnout*>*>(/*6*/); // output# - bean pairs
}

/*protected*/ void MatrixSignalMast::configureFromName(QString systemName)
{
 // split out the basic information
 QStringList parts = systemName.split(":");
 if (parts.length() < 3) {
     log->error("SignalMast system name needs at least three parts: " + systemName);
     throw IllegalArgumentException("System name needs at least three parts: " + systemName);
 }
 if (parts[0] != (mastType)) {
     log->warn("SignalMast system name should start with " + mastType + " but is " + systemName);
 }
 QString system = parts[1];
 QString mast = parts[2];

 mast = mast.mid(0, mast.indexOf("("));
 setMastType(mast);

 QString tmp = parts[2].mid(parts[2].indexOf("($") + 2, parts[2].indexOf(")") - parts[2].indexOf("($")  -2);
 bool bok;
     int autoNumber = (tmp.toInt(&bok));
     if (autoNumber > lastRef) {
         lastRef = autoNumber;
     }
  if(!bok) {
     log->warn("Auto generated SystemName " + systemName + " is not in the correct format");
 }

 configureSignalSystemDefinition(system); // (checks for system) in AbstractSignalMast
 configureAspectTable(system, mast); // (create -default- appmapping in var "map") in AbstractSignalMast
}


/**
 * Store bits in aspectToOutput hashmap
 * @param aspect String valid aspect to define
 * @param bitArray char[] of on/off outputs for the aspect, like "00010"
 * length of bitArray should match the number of outputs defined, so one digit per output
*/
/*public*/ void MatrixSignalMast::setBitsForAspect(QString aspect,QByteArray bitArray) {
    if (aspectToOutput.contains(aspect)) {
//        if (log->isDebugEnabled()) log->debug(tr("Aspect %1 is already defined as %2").arg( aspect).arg(aspectToOutput.value(aspect)));
        aspectToOutput.remove(aspect);
    }
    aspectToOutput.insert(aspect, bitArray); // store keypair aspectname - bitArray in hashmap
}

/**
 * Look up the pattern for an aspect
 * @param aspect String describing a (valid) signal mast aspect, like "Clear"
 * only called for an already existing mast
 * @return char[] of on/off outputs per aspect, like "00010"
 * length of array should match the number of outputs defined
 * when a mast is changed in the interface, extra 0's are added or superfluous elements deleted by the Add Mast panel
*/
/*public*/ QByteArray MatrixSignalMast::getBitsForAspect(QString aspect) {
    if (!aspectToOutput.contains(aspect) || aspectToOutput.value(aspect) == "") {
        log->error(tr("Trying to get aspect %1 but it has not been configured").arg(aspect));
        return errorBits; // error flag
    }
    return aspectToOutput.value(aspect);
}

//@Override
/*public*/ void MatrixSignalMast::setAspect(QString aspect) {
    // check it's a valid choice
    if (!map->checkAspect(aspect)) {
        // not a valid aspect
        log->warn("attempting to set invalid Aspect: " + aspect + " on mast: " + getDisplayName());
        throw new IllegalArgumentException("attempting to set invalid Aspect: " + aspect + " on mast: " + getDisplayName());
    } else if (disabledAspects->contains(aspect)) {
        log->warn("attempting to set an Aspect that has been Disabled: " + aspect + " on mast: " + getDisplayName());
        throw new IllegalArgumentException("attempting to set an Aspect that has been Disabled: " + aspect + " on mast: " + getDisplayName());
    }
    if (getLit()) {
        // If the signalmast is lit, then send the commands to change the aspect.
        if (_resetPreviousStates) {
            // Clear all the current states, this will result in the signalmast going blank (RED) for a very short time.
            // ToDo: check if decoder will accept direct DCC packets
            // or pick up drop down choice to choose between DCCPackets or Turnouts outputs
            // c.sendPacket(NmraPacket.altAccSignalDecoderPkt(dccSignalDecoderAddress, aspectToOutput.get(aspect)), packetRepeatCount);
            if (aspectToOutput.contains("Stop")) {
                updateOutputs(getBitsForAspect("Stop")); // show Red
            } else {
                if (unLitBits.isNull()) {
                    updateOutputs(unLitBits); // Dark (instead of Red), always available
                }
            }
        }
        if (aspectToOutput.contains(aspect) && aspectToOutput.value(aspect) != errorBits) {
            // ToDo: pick up drop down choice for either DCC direct packets or Turnouts as outputs
            // c.sendPacket(NmraPacket.altAccSignalDecoderPkt(dccSignalDecoderAddress, aspectToOutput.get(aspect)), packetRepeatCount);
            QByteArray bitArray = getBitsForAspect(aspect);
            // for  MatrixMast nest a loop, using setBitsForAspect(), provides extra check on value
            updateOutputs(bitArray);
            // Set the new Signal Mast state
        } else {
            log->error("Trying to set an aspect (" + aspect + ") on signal mast " + getDisplayName() + " which has not been configured");
        }
    } else if (log->isDebugEnabled()) {
        log->debug("Mast set to unlit, will not send aspect change to hardware");
    }
    AbstractSignalMast::setAspect(aspect);
}

//@Override
/*public*/ void MatrixSignalMast::setLit(bool newLit) {
    if (!allowUnLit() || newLit == getLit()) {
        return;
    }
    if (newLit) {
        if (getAspect() != "") {
            setAspect(getAspect());
        }
        // if true, activate prior aspect
    } else {
        if (!unLitBits.isNull()) {
            updateOutputs(unLitBits); // directly set outputs
            //c.sendPacket(NmraPacket.altAccSignalDecoderPkt(dccSignalDecoderAddress, unLitId), packetRepeatCount);
        }
    }
    AbstractSignalMast::setLit(newLit);
}

/*public*/ void MatrixSignalMast::setUnLitBits(/*@Nonnull*/ QByteArray bits) {
    unLitBits = bits;
}

/**
 *  Receive unLitBits from xml and store
 *  @param bitString String for 1-n 1/0 chararacters setting an unlit aspect
 */
/*public*/ void MatrixSignalMast::setUnLitBits(/*@Nonnull*/ QString bitString) {
    //setUnLitBits(bitString.toCharArray());
 setUnLitBits(bitString.toLocal8Bit());
}

/**
 *  Provide Unlit bits to panel for editing.
 *
 *  @return char[] containing a series of 1's and 0's set for Unlit mast
 */
/*@Nonnull*/ /*public*/ QByteArray MatrixSignalMast::getUnLitBits() {
    if (!unLitBits.isNull()) {
        return unLitBits;
    } else {
        return emptyBits;
    }
}

/**
 *  Hand unLitBits to xml.
 *
 *  @return String for 1-n 1/0 chararacters setting an unlit aspect
 */
//@Nonnull
/*public*/ QString MatrixSignalMast::getUnLitChars() {
    if (!unLitBits.isNull()) {
        return QString(unLitBits);
    } else {
        log->error("Returning 0 values because unLitBits is empty");
        return emptyChars.mid(0, (mastBitNum)); // should only be called when Unlit = true
    }
}


/**
 *  Fetch output as Turnout from outputsToBeans hashmap.
 *
 *  @param colNum int index (1 up to mastBitNum) for the column of the desired output
 *  @return Turnout object connected to configured output
 */
//@CheckForNull
/*private*/ Turnout* MatrixSignalMast::getOutputBean(int colNum) { // as bean
    QString key = "output" + QString::number(colNum);
    if (colNum > 0 && colNum <= outputsToBeans.size()) {
        return outputsToBeans.value(key)->getBean();
    }
    log->error("Trying to read bean for output {} which has not been configured", colNum);
    return nullptr;
}

/**
 *  Fetch output from outputsToBeans hashmap.
 *  Used?
 *
 *  @param colNum int index (1 up to mastBitNum) for the column of the desired output
 *  @return NamedBeanHandle to the configured turnout output
 */
//@CheckForNull
/*public*/ NamedBeanHandle<Turnout*>* MatrixSignalMast::getOutputHandle(int colNum) {
    QString key = "output" + QString::number(colNum);
    if (colNum > 0 && colNum <= outputsToBeans.size()) {
        return outputsToBeans.value(key);
    }
    log->error(tr("Trying to read output NamedBeanHandle %1 which has not been configured").arg(key));
    return nullptr;
}

/**
 *  Fetch output from outputsToBeans hashmap and provide to xml.
 *
 *  @see jmri.implementation.configurexml.MatrixSignalMastXml#store(java.lang.Object)
 *  @param colnum int index (1 up to mastBitNum) for the column of the desired output
 *  @return String with the desplay name of the configured turnout output
 */
//@Nonnull
/*public*/ QString MatrixSignalMast::getOutputName(int colnum) {
    QString key = "output" + QString::number(colnum);
    if (colnum > 0 && colnum <= outputsToBeans.size()) {
        return outputsToBeans.value(key)->getName();
    }
    log->error(tr("Trying to read name of output %1 which has not been configured").arg(colnum));
    return "";
}

/**
 *  Receive aspect name from xml and store matching setting in outputsToBeans hashmap
 *  @see jmri.implementation.configurexml.MatrixSignalMastXml#load(org.jdom2.Element, org.jdom2.Element)
 *  @param aspect String describing (valid) signal mast aspect, like "Clear"
 *  @param bitString String of 1/0 digits representing on/off outputs per aspect, like "00010"
 */
/*public*/ void MatrixSignalMast::setBitstring(/*@Nonnull*/ QString aspect, /*@Nonnull*/ QString bitString) {
    if (aspectToOutput.contains(aspect)) {
        log->debug("Aspect " + aspect + " is already defined so will override");
        aspectToOutput.remove(aspect);
    }
    QByteArray bitArray = bitString.toLocal8Bit(); // for faster lookup, stored as char[] array
    aspectToOutput.insert(aspect, bitArray);
}

/**
 *  Receive aspect name from xml and store matching setting in outputsToBeans hashmap
 *  @param aspect String describing (valid) signal mast aspect, like "Clear"
 *  @param bitArray char[] of 1/0 digits representing on/off outputs per aspect, like {0,0,0,1,0}
 */
/*public*/ void MatrixSignalMast::setBitstring(QString aspect, QByteArray bitArray) {
    if (aspectToOutput.contains(aspect)) {
        log->debug("Aspect " + aspect + " is already defined so will override");
        aspectToOutput.remove(aspect);
    }
    // is supplied as char array, no conversion needed
    aspectToOutput.insert(aspect, bitArray);
}

/**
 *  Provide one series of on/off digits from aspectToOutput hashmap to xml
 *  @return bitString String of 1 (= on) and 0 (= off) chars
 *  @param aspect String describing valid signal mast aspect, like "Clear"
 */
/*@Nonnull*/ /*public*/ QString MatrixSignalMast::getBitstring(/*@Nonnull*/ QString aspect) {
    if (aspectToOutput.contains(aspect)) { // hashtable
        QString bitString = QString(aspectToOutput.value(aspect)); // convert char[] to string
        return bitString;
    }
    return "";
}

/**
 *  Provide the names of the on/off turnout outputs from outputsToBeans hashmap to xml
 *  @return outputlist List&lt;String&gt; of display names for the outputs in order 1 to (max) 6
 */
/*@Nonnull*/ /*public*/ QStringList MatrixSignalMast::getOutputs() { // provide to xml
    // to do: use for loop
    QStringList outputlist = QStringList(); // (6) or (mastBitNum) ?
    //list = outputsToBeans.keySet();
    outputlist.append(outputsToBeans.value("output1")->getName()); // convert NBH to name (String)
    if (outputsToBeans.contains("output2")) {
        // outputsToBeans hashmap
        outputlist.append(outputsToBeans.value("output2")->getName());
    }
    if (outputsToBeans.contains("output3")) {
        outputlist.append(outputsToBeans.value("output3")->getName());
    }
    if (outputsToBeans.contains("output4")) {
        outputlist.append(outputsToBeans.value("output4")->getName());
    }
    if (outputsToBeans.contains("output5")) {
        outputlist.append(outputsToBeans.value("output5")->getName());
    }
    if (outputsToBeans.contains("output6")) {
        outputlist.append(outputsToBeans.value("output6")->getName());
    }
    // repeat in order to set MAXMATRIXBITS > 6
    return outputlist;
}

// adjust Hashmap size in order to set MAXMATRIXBITS > 6
/**
 * Receive properties from xml, convert name to NamedBeanHandle, store in hashmap outputsToBeans
 * @param colname String describing the name of the corresponding output, like "output1"
 * @param turnoutname String for the display name of the output, like "LT1"
*/
/*public*/ void MatrixSignalMast::setOutput(/*@Nonnull*/ QString colname, /*@Nonnull*/ QString turnoutname) {
    if (colname == "" || turnoutname == ""){
        log->error("Trying to store a null output. Fix output configuration for mast");
    } else {
        Turnout* turn = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutname);
        if (turn == nullptr) {
            log->error(tr("setOutpout couldn't locate turnout %1").arg(turnoutname));
            return;
        }
        NamedBeanHandle<Turnout*>* namedTurnout = static_cast<NamedBeanHandleManager*>( InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutname, turn);
        if (outputsToBeans.contains(colname)) {
            log->debug("Output " + colname + " is already defined so will override");
            outputsToBeans.remove(colname);
        }
        outputsToBeans.insert(colname, namedTurnout);
    }
}

/**
 *  Send hardware instruction
 *  @param bits char[] of on/off outputs per aspect, like "00010"
 *  length of array should match the number of outputs defined
 */
/*public*/ void MatrixSignalMast::updateOutputs (QByteArray bits) {
    if (bits.isNull()){
        log->debug("Empty char[] received");
    } else {
        for (int i = 0; i < outputsToBeans.size(); i++) {
            //log.debug("Setting bits[1] = " + bits[i] + " for output #" + i);
            Turnout* t = getOutputBean(i + 1);
            if ( t != nullptr) {
                t->setBinaryOutput(true); // prevent feedback etc.
            }
            if (bits[i] == '1' && getOutputBean(i + 1) != nullptr && getOutputBean(i + 1)->getCommandedState() != Turnout::CLOSED) {
                // no need to set a state already set
                getOutputBean(i + 1)->setCommandedState(Turnout::CLOSED);
            } else if (bits[i] == '0' && getOutputBean(i + 1) != nullptr && getOutputBean(i + 1)->getCommandedState() != Turnout::THROWN) {
                getOutputBean(i + 1)->setCommandedState(Turnout::THROWN);
            } else if (bits[i] == 'n' || bits[i] == 'u') {
                // let pass, extra chars up to 6 are not defined
            } else {
                // invalid char
                log->debug("Invalid element " + QString::number(bits[i]) + " cannot be converted to state for output #" + QString::number(i));
            }
        }
    }
}


/**
 * If the signal mast driver requires the previous state to be cleared down
 * before the next state is set.
 *
 * @param boo true to configure for intermediate reset step
 */
/*public*/ void MatrixSignalMast::resetPreviousStates(bool boo) {
    _resetPreviousStates = boo;
}

/*public*/ bool MatrixSignalMast::resetPreviousStates() {
    return _resetPreviousStates;
}


bool MatrixSignalMast::isTurnoutUsed(Turnout* t) {
    for (int i = 1; i <= outputsToBeans.size(); i++) {
        if (t == (getOutputBean(i))) {
            return true;
        }
    }
    return false;
}

/*public*/ /*static*/ int MatrixSignalMast::getLastRef() {
    return lastRef;
}

/*static*/ int MatrixSignalMast::lastRef = 0;
/**
 *
 * @param newVal for ordinal of all MatrixSignalMasts in use
 */
/*protected*/ /*static*/ void MatrixSignalMast::setLastRef(int newVal) {
    lastRef = newVal;
}
//@Override
/*public*/ void MatrixSignalMast::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)
{

    if ("CanDelete"==(evt->getPropertyName())) { //NOI18N
        //if (evt->getOldValue() instanceof Turnout)
     if(qobject_cast<Turnout*>(VPtr<Turnout>::asPtr(evt->getOldValue())))
        {
            if (isTurnoutUsed(VPtr<Turnout>::asPtr(evt->getOldValue()))) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw PropertyVetoException(tr("Turnout is in use by SignalMast \"%1\"").arg( getDisplayName()), e);
            }
        }
    }
}

/** Store number of outputs from integer
* @param number int for the number of outputs defined for this mast
* @see #mastBitNum
*/
/*public*/ void MatrixSignalMast::setBitNum(int number) {
        mastBitNum = number;
}

/** Store number of outputs from integer
 * @param bits char[] for outputs defined for this mast
 * @see #mastBitNum
 */
/*public*/ void MatrixSignalMast::setBitNum(QByteArray bits) {
    mastBitNum = bits.length();
}

/*public*/ int MatrixSignalMast::getBitNum() {
    return mastBitNum;
}

//@Override
/*public*/ void MatrixSignalMast::setAspectDisabled(QString aspect) {
    if (aspect.isEmpty()) {
        return;
    }
    if (!map->checkAspect(aspect)) {
        log->warn("attempting to disable an aspect: " + aspect + " that is not on the mast " + getDisplayName());
        return;
    }
    if (!disabledAspects->contains(aspect)) {
        disabledAspects->append(aspect);
        firePropertyChange("aspectDisabled", QVariant(), aspect);
    }
}
/**
 * Set the delay between issuing Matrix Output commands to the outputs on this specific mast.
 * Delay be extended by a connection specific Output Delay set in the connection config.
 *
 * @see jmri.implementation.configurexml.MatrixSignalMastXml#load(org.jdom2.Element, org.jdom2.Element)
 * @param delay the new delay in milliseconds
 */
/*public*/ void MatrixSignalMast::setMatrixMastCommandDelay(int delay) {
    if (delay >= 0) {
        mDelay = delay;
    }
}

/**
 * Get the delay between issuing Matrix Output commands to the outputs on this specific mast.
 * Delay be extended by a connection specific Output Delay set in the connection config.
 *
 * @see jmri.implementation.configurexml.MatrixSignalMastXml#load(org.jdom2.Element, org.jdom2.Element)
 * @return the delay in milliseconds
 */
/*public*/ int MatrixSignalMast::getMatrixMastCommandDelay() {
    return mDelay;
}
//@Override
/*public*/ void MatrixSignalMast::dispose() {
    AbstractSignalMast::dispose();
}

/*public*/ QString MatrixSignalMast::className(){return "jmri.implementation.MatrixSignalMast";}

/*private*/ /*final*/ /*static*/ Logger* MatrixSignalMast::log = LoggerFactory::getLogger("MatrixSignalMast");


