#include "nullaudiolistener.h"

//NullAudioListener::NullAudioListener(QObject *parent) :
//  AbstractAudioListener(parent)
//{
//}
/**
 * Null implementation of the Audio Listener sub-class.
 * <P>
 * For now, no system-specific implementations are forseen - this will remain
 * internal-only
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28771 $
 */
//public class NullAudioListener extends AbstractAudioListener {

/**
 *
 */
//private static final long serialVersionUID = 8149788369213980559L;

/**
 * Constructor for new NullAudioListener with system name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 */
/*public*/ NullAudioListener::NullAudioListener(QString systemName, QObject *parent) :
  AbstractAudioListener(systemName, parent){
    //super(systemName);
 common();
    if (log->isDebugEnabled()) {
        log->debug("New NullAudioListener: " + systemName);
    }
}

/**
 * Constructor for new NullAudioListener with system name and user name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 * @param userName   AudioListener object user name
 */
/*public*/ NullAudioListener::NullAudioListener(QString systemName, QString userName, QObject *parent) :
  AbstractAudioListener(systemName, userName, parent)
{
    //super(systemName, userName);
 common();
    if (log->isDebugEnabled()) {
        log->debug("New NullAudioListener: " + userName + " (" + systemName + ")");
    }
}
void NullAudioListener::common()
{
 log = new Logger("NullAudioListener");
}

//@Override
/*protected*/ void NullAudioListener::changePosition(QVector3D pos) {
    // Do nothing
}

//@Override
/*protected*/ void NullAudioListener::cleanUp() {
    if (log->isDebugEnabled()) {
        log->debug("Cleanup NullAudioBuffer (" + this->getSystemName() + ")");
    }
    this->dispose();
}
