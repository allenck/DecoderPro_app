#ifndef RPSPOSITIONICON_H
#define RPSPOSITIONICON_H
#include "positionablelabel.h"

class Measurement;
class RpsPositionIcon : public PositionableLabel
{
 Q_OBJECT
public:
 RpsPositionIcon();

private:
 // store coordinate system information
 Measurement* lastMeasurement;

 double sxScale, syScale;
 int sxOrigin, syOrigin;
};

#endif // RPSPOSITIONICON_H
