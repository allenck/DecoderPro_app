#ifndef RPSPOSITIONICON_H
#define RPSPOSITIONICON_H
#include "positionablelabel.h"

class Measurement;
class RpsPositionIcon : public PositionableLabel
{
 Q_OBJECT
public:
 RpsPositionIcon(Editor*);

private:
 // store coordinate system information
 Measurement* lastMeasurement;

 double sxScale, syScale;
 int sxOrigin, syOrigin;
 // display icon for a correct reading
 QString activeName;// = "resources/icons/smallschematics/tracksegments/circuit-occupied.gif";
 NamedIcon* active;// = new NamedIcon(activeName, activeName);

 // display icon if the last reading not OK
 QString errorName;// = "resources/icons/smallschematics/tracksegments/circuit-error.gif";
 NamedIcon* error;// = new NamedIcon(errorName, errorName);

};

#endif // RPSPOSITIONICON_H
