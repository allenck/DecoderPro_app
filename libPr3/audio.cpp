#include "audio.h"

Audio::Audio(QString systemName, QObject *parent) :
    AbstractNamedBean(systemName, parent)
{
    common();
}
Audio::Audio(QString systemName, QString userName, QObject *parent) :
    AbstractNamedBean(systemName, userName, parent)
{
    common();
}
void Audio::common()
{
}
    // Define orientation constants
    /**
     * Maximum distance for Audio objects
     */
    float Audio::MAX_DISTANCE = 9999.99f;
    /**
     * Number of decimal places for float values to be stored in
     */
    double Audio::DECIMAL_PLACES = 2;


/**
 * Definition of AudioSource NamedBean sub-type code
 */
const QChar Audio::SOURCE    = 'S';

/**
 * Definition of AudioBuffer NamedBean sub-type code
 */
const QChar Audio:: BUFFER    = 'B';

/**
 * Definition of AudioListener NamedBean sub-type code
 */
const QChar Audio::LISTENER  = 'L';
/**
 * State code for an AudioListener when positioned
 */
const /*static*/ int Audio::STATE_POSITIONED = 0x30;
/**
 * State code for an AudioListener when moving
 */
const /*static*/ int Audio::STATE_MOVING     = 0x31;
