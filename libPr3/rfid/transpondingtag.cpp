#include "transpondingtag.h"

/**
 * Concrete implementation of the {@link jmri.IdTag} interface for the LocoNet
 * based Transponding reports.
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Matthew Harris Copyright (C) 2011
 * @author Paul Bender Copyright (C) 2019
 * @since 4.15.4
 */
///*public*/ class TranspondingTag extends jmri.implementation.DefaultIdTag implements jmri.AddressedIdTag {

    /*public*/ TranspondingTag::TranspondingTag(QString systemName, QObject* parent) : DefaultIdTag(systemName, parent){
        //super(systemName);
    }

    /*public*/ TranspondingTag::TranspondingTag(QString systemName, QString userName, QObject* parent) : DefaultIdTag(systemName, userName, parent){
        //super(systemName, userName);
    }

    /**
     * @deprecated since 4.15.4.  Eventually will be removed in favor of
     * the {@link jmri.implementation.AbstractNamedBean#toString()}, which
     * does not produce the same result. Use {@link #toReportString()} instead.
     */
    //@Deprecated
    //@Override
    /*public*/ QString TranspondingTag::toString(){
       QString exit = getProperty("entryexit").toString();
       if(exit!="") {
          return getTagID() + " " + exit;
       } else {
          return getTagID();
       }
    }
