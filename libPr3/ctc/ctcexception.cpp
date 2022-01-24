#include "ctcexception.h"
#include "loggerfactory.h"
#include "ctcexceptionbuffer.h"
#include "instancemanager.h"

/**
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 *
 * The purpose of this class is to provide a single point of interface to the
 * JMRI error logging system.
 */
///*public*/ class CTCException extends Exception {
    /*public*/ CTCException::CTCException(QString module, QString userIdentifier, QString parameter, QString reason) {
        _mModule = module;
        _mUserIdentifier = userIdentifier;
        _mParameter = parameter;
        _mReason = reason;
    }
    /*public*/ QString CTCException::getExceptionString() {
     return _mModule + ", " + _mUserIdentifier + _mParameter + ", " + _mReason;
    }
    /*public*/ void CTCException::logError() {
     QString exceptionString = getExceptionString();
     LoggerFactory::getLogger("CTCException")->error(exceptionString);
     ((CTCExceptionBuffer*)InstanceManager::getDefault("CTCExceptionBuffer"))->logString(CTCExceptionBuffer::ExceptionBufferRecordSeverity::ERROR, exceptionString);
    }
    /*public*/ void CTCException::logWarning()
    {
     QString exceptionString = getExceptionString();
     LoggerFactory::getLogger("CTCException")->warn(exceptionString);
     ((CTCExceptionBuffer*)InstanceManager::getDefault("CTCExceptionBuffer"))->logString(CTCExceptionBuffer::ExceptionBufferRecordSeverity::WARN, exceptionString); }
    /*static*/ /*public*/ void CTCException::logError(QString string) {
     LoggerFactory::getLogger("CTCException")->error(string);
     ((CTCExceptionBuffer*)InstanceManager::getDefault("CTCExceptionBuffer"))->logString(CTCExceptionBuffer::ExceptionBufferRecordSeverity::ERROR, string);
    }
    /*static*/ /*public*/ void CTCException::logWarning(QString string) {
     LoggerFactory::getLogger("CTCException")->warn(string);
     ((CTCExceptionBuffer*)InstanceManager::getDefault("CTCExceptionBuffer"))->logString(CTCExceptionBuffer::ExceptionBufferRecordSeverity::WARN, string); }
    /*static*/ /*public*/ void CTCException::logInfo(QString string) {
     LoggerFactory::getLogger("CTCException")->info(string);
     ((CTCExceptionBuffer*)InstanceManager::getDefault("CTCExceptionBuffer"))->logString(CTCExceptionBuffer::ExceptionBufferRecordSeverity::INFO, string); }

