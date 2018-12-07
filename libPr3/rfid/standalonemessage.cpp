#include "standalonemessage.h"

/**
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 * <P>
 *
 * @author Matthew Harris Copyright (C) 2011
 */
///*public*/ class StandaloneMessage extends RfidMessage {

/*public*/ StandaloneMessage::StandaloneMessage(int l, QObject* parent) : RfidMessage(l, parent){
    //super(l);
}

/*public*/ StandaloneMessage::StandaloneMessage(QString m, int l, QObject*parent) : RfidMessage(m,l,parent){
    //super(m, l);
}

