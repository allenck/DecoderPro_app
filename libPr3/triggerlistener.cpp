#include "triggerlistener.h"

TriggerListener::TriggerListener(QObject *parent) :
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
// Interface for creating anonymous objects for having VSDSounds listen to Triggers...
///*public*/ /*interface*/ TriggerListener {

    /*public*/ void TriggerListener::takeAction() {}

    /*public*/ void TriggerListener::takeAction(int /*i*/){}

    /*public*/ void TriggerListener::takeAction(float /*f*/) {}

//}
