#include "rfidcomponentfactory.h"
#include "rfidsystemconnectionmemo.h"
#include "rfidmenu.h"

/**
 * Provide access to Swing components for the Rfid subsystem.
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Matthew Harris Copyright (C) 2011
 */
///*public*/ class RfidComponentFactory extends jmri.jmrix.swing.ComponentFactory {


/*public*/ RfidComponentFactory::RfidComponentFactory(RfidSystemConnectionMemo* memo, QObject *parent)
 : ComponentFactory(parent)
{
    this->memo = memo;
}

//@Override
/*public*/ QMenu* RfidComponentFactory::getMenu() {
    if (memo->getDisabled()) {
        return nullptr;
    }
    return new RfidMenu(memo);
}


