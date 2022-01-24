#include "ctcexceptionbuffer.h"

/**
 * Most times the user does not have the System Console displayed when the CTC
 * system is being started up.  As such, errors logged to the CTCException class
 * just "disappear" into the ether on that console, and the user has no
 * knowledge of any problems.
 *
 * In this object, I will also gather up all of the errors, warnings and info
 * messages that my system generates in CTCException, and display them to the
 * user via a dialog box of some form, after the CTC system is fully started.
 *
 * For safety, I implement InstanceManagerAutoDefault so that the objects
 * default constructor is called (for future safety).  I'm not sure
 * if "class" variables below are initialized properly if this is not done.
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 */
// /*public*/ class CTCExceptionBuffer implements InstanceManagerAutoDefault {
#if 0
    /*public*/ enum ExceptionBufferRecordSeverity {
        INFO(0), WARN(1), ERROR(2);     // Order: The more severe, the HIGHER the number.  See function "getHighestExceptionBufferRecordSeverity" for why.
        /*private*/ /*final*/ int _mSeverity;
        ExceptionBufferRecordSeverity(int severity) { this._mSeverity = severity; }
        /*public*/ int getSeverity() { return _mSeverity; }
    }
#endif
    /*public*/ CTCExceptionBuffer::CTCExceptionBuffer() {}
    /*public*/ void CTCExceptionBuffer::logString(ExceptionBufferRecordSeverity exceptionBufferRecordSeverity, QString string) {
     _mArrayListOfExceptionBufferRecords.append(new ExceptionBufferRecord(exceptionBufferRecordSeverity, string)); }
    /*public*/ bool CTCExceptionBuffer::isEmpty() { return _mArrayListOfExceptionBufferRecords.isEmpty(); }
    /*public*/ void CTCExceptionBuffer::clear() { _mArrayListOfExceptionBufferRecords.clear(); }
    /**
     * You SHOULD call "isEmpty()" first, because this routine returns by default "INFO"
     * IF there are NO entries in the list.
     *
     * It's purpose is to give the user an idea of the worst case scenario in the errors.
     *
     * @return The highest level of severity in our list.
     */
    /*public*/ CTCExceptionBuffer::ExceptionBufferRecordSeverity CTCExceptionBuffer::getHighestExceptionBufferRecordSeverity() {
        ExceptionBufferRecordSeverity highestExceptionBufferRecordSeverityEncountered = ExceptionBufferRecordSeverity::INFO; // Start with lowest, in case there are none
        for (ExceptionBufferRecord* exceptionBufferRecord : _mArrayListOfExceptionBufferRecords) {
#if 0
            if (exceptionBufferRecord->_mExceptionBufferRecordSeverity.getSeverity() > highestExceptionBufferRecordSeverityEncountered.getSeverity()) {
                highestExceptionBufferRecordSeverityEncountered = exceptionBufferRecord->_mExceptionBufferRecordSeverity;
            }
#endif
        }
        return highestExceptionBufferRecordSeverityEncountered;
    }
    /*public*/ QString CTCExceptionBuffer::getAllMessages() {
        QString returnStringBuilder = QString("<html>");  // NOI18N
        for (ExceptionBufferRecord* exceptionBufferRecord : _mArrayListOfExceptionBufferRecords) {
            returnStringBuilder.append(exceptionBufferRecord->_mMessage + "<br>");  // NOI18N
        }
        returnStringBuilder.append("</html>");  // NOI18N
        return returnStringBuilder/*.toString()*/;
    }
