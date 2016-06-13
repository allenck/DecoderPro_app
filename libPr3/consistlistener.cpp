#include "consistlistener.h"

ConsistListener::ConsistListener(QObject *parent) :
    QObject(parent)
{
}
/**
 * Allow notification of delayed consisting errors.
 * <P>
 * This allows a {@link Consist} object to return delayed status.
 *
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
 * @author			Paul Bender  Copyright (C) 2004
 * @version			$Revision: 17977 $
 */
//public interface ConsistListener extends java.util.EventListener{

/** Receive notification at the end of a consisting operation.
 *
 * @param locoaddress  Address of specific locomotive involved, if
     *                     error is locomotive specific.
 * @param status Denotes the completion code. Note that this is a
 *                    bitwise combination of the various status coded defined
 *                    in this interface.
 */
/*public*/ void ConsistListener::consistReply(DccLocoAddress* locoaddress, int status) {}


