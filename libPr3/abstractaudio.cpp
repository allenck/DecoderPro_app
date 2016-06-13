#include "abstractaudio.h"
#include <math.h>
#include "abstractaudioframe.h"

//AbstractAudio::AbstractAudio(QObject *parent) :
//  Audio(parent)
//{
//}
/**
 * Base implementation of the Audio class.
 * <P>
 * Specific implementations will extend this base class.
 *
 * <p>
 * Audio bean system names are always upper case.
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
///*public*/ abstract class AbstractAudio extends AbstractNamedBean implements Audio {

/**
 *
 */
// /*private*/ static final long serialVersionUID = 6464454340389625230L;


///*private*/ static /*final*/ int INT_PRECISION = (int) qPow(10, DECIMAL_PLACES);

/**
 * Abstract constructor for new Audio with system name
 *
 * @param systemName Audio object system name (e.g. IAS1, IAB4)
 */
/*public*/ AbstractAudio::AbstractAudio(QString systemName, QObject *parent) :
  AudioBuffer(systemName, parent)
{
 //super(systemName.toUpperCase());
 common();
}

/**
 * Abstract constructor for new Audio with system name and user name
 *
 * @param systemName Audio object system name (e.g. IAS1, IAB4)
 * @param userName   Audio object user name
 */
/*public*/ AbstractAudio::AbstractAudio(QString systemName, QString userName, QObject *parent) :
  AudioBuffer(systemName.toUpper(), userName, parent) {
   // super(systemName.toUpperCase(), userName);
 common();
}
void AbstractAudio::common()
{
 _state = STATE_INITIAL;

}

//@Override
/*public*/ int AbstractAudio::getState() {
    return this->_state;
}

//@Override
/*public*/ void AbstractAudio::setState(int newState) {
    QVariant _old = this->_state;
    this->_state = newState;
    stateChanged( _old.toInt());
    firePropertyChange("State", _old, _state); //NOI18N
}

//@Override
/*public*/ QString AbstractAudio::toString() {
    return QString(this->metaObject()->className()) + " (" + this->getSystemName() + ")"; //NOI18N
}

/**
 * Abstract method that concrete classes will implement to perform necessary
 * cleanup routines.
 */
/*abstract*/ /*protected*/ void AbstractAudio::cleanUp() {}

/**
 * Static method to round a float value to the specified number of decimal
 * places
 *
 * @param value  float value to round
 * @param places number of decimal places to round to
 * @return float value rounded to specified number of decimal places
 */
/*public*/ /*static*/ float AbstractAudio::roundDecimal(float value, double places)
{
 double multiplier = pow(10, places);
 value *= multiplier;
 return (float) (qRound(value) / multiplier);
}

/**
 * Static method to round a float value to the number of decimal places
 * defined by DECIMAL_PLACES.
 *
 * @param value float value to round
 * @return float value rounded to DECIMAL_PLACES decimal places
 */
/*public*/ /*static*/ float AbstractAudio::roundDecimal(float value)
{
 return roundDecimal(value, log10(AbstractAudioFrame::INT_PRECISION));
}

/*public*/ QString AbstractAudio::getBeanType() {
    return tr("Audio");
}
