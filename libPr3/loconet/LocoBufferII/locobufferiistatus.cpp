#include "locobufferiistatus.h"

/**
 * LocoBufferII status
 *
 * @author Bob Milhaupt Copyright (C) 2017
 */
// /*public*/ class LocoBufferIIStatus {
/*public*/ LocoBufferIIStatus::LocoBufferIIStatus(int version, int breaks, int errors, QObject *parent) : QObject(parent){
    this->version = version;
    this->breaks = breaks;
    this->errors = errors;
    setObjectName("LocoBufferIIStatus");
}



