#include "vsdecoderevent.h"
#include "vsdecoder.h"

//VSDecoderEvent::VSDecoderEvent(QObject *parent) :
//  QObject(parent)
//{
//}
/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 18512 $
 */
//import java.util.EventObject;

//@SuppressWarnings("serial")
///*public*/ class VSDecoderEvent extends EventObject {



    /*public*/ VSDecoderEvent::VSDecoderEvent(VSDecoder* source,QObject *parent) :
  QObject( parent){
        //this(source, VSDecoderEvent.EventType.NONE, null);
 this->source = source;
 type = NONE;
 data = QVariant();
    }

    /*public*/ VSDecoderEvent::VSDecoderEvent(VSDecoder* source, EventType t,QObject *parent) :
  QObject(parent) {
        //this(source, t, null);
 this->source = source;
 type = t;
 data = QVariant();
    }

/*public*/ VSDecoderEvent::VSDecoderEvent(VSDecoder* source, EventType t, QVariant d, QObject* parent)
 : QObject(parent)
{
        //super(source);
 this->source = source;
        type = t;
        data = d;
    }

    /*public*/ void VSDecoderEvent::setType(EventType t) {
        type = t;
    }

    /*public*/ VSDecoderEvent::EventType VSDecoderEvent::getType() {
        return (type);
    }

    /*public*/ QVariant VSDecoderEvent::getData() {
        return (data);
    }
