#include "vsdmanagerevent.h"

VSDManagerEvent::VSDManagerEvent(QObject *parent) :
  QObject(parent)
{
}
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
 * @version			$Revision: 28746 $
 */
//import java.util.EventObject;

//@SuppressWarnings("serial")
///*public*/ class VSDManagerEvent extends EventObject {


    /*public*/ VSDManagerEvent::VSDManagerEvent(VSDecoderManager* source) :
  QObject((QObject*)source) {
        //this(source, VSDManagerEvent::NONE, NULL);
 type = VSDManagerEvent::NONE;
 data = QVariant();
    }

    /*public*/ VSDManagerEvent::VSDManagerEvent(VSDecoderManager* source, VSDManagerEvent::EventType t) :
  QObject((QObject*)source)  {
        //this(source, t, null);
 type = t;
 data = QVariant();
    }

    /*public*/ VSDManagerEvent::VSDManagerEvent(VSDecoderManager* source, VSDManagerEvent::EventType t, QVariant d) :
  QObject((QObject*)source)   {
        //super(source);
        type = t;
        data = d;
    }

    /*public*/ void VSDManagerEvent::setType(VSDManagerEvent::EventType t) {
        type = t;
    }

    /*public*/ VSDManagerEvent::EventType VSDManagerEvent::getType() {
        return (type);
    }

    /*public*/ QVariant VSDManagerEvent::getData() {
        return (data);
    }
