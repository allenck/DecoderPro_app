#include "jmriconfigurexmlexception.h"

/**
 * Base for JMRI-specific ConfigureXml exceptions. No functionality, just used
 * to confirm type-safety.
 *
 * @author Bob Jacobsen Copyright (C) 2009, 2010
 */
// /*public*/  class JmriConfigureXmlException extends jmri.JmriException {

    /*public*/  JmriConfigureXmlException::JmriConfigureXmlException(QString s, Throwable* t) : JmriException(s, t){
        //super(s, t);
    }

    /*public*/  JmriConfigureXmlException::JmriConfigureXmlException(QString s) : JmriException(s){
        //super(s);
    }

    /*public*/  JmriConfigureXmlException::JmriConfigureXmlException(Exception* s) : JmriException(s){
        //super(s);
    }

    /*public*/  JmriConfigureXmlException::JmriConfigureXmlException() {
        //super();
    }

