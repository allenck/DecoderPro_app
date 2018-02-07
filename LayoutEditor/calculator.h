#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include "measurement.h"
namespace RPS
{


/**
 * Describes a specific method of calculating a measurement
 * <P>
 * Information that the algorithm needs, e.g. received positions, etc, should be
 * provided to the actual object via ctor or other initialization. This
 * interface does not describe that.
 *
 * @author	Bob Jacobsen Copyright (C) 2006
  */
/*public*/ /*interface*/class Calculator {
public:
 virtual /*public*/ Measurement* convert(Reading* r) {return NULL;}

 virtual /*public*/ Measurement* convert(Reading* r, QVector3D guess) {return NULL;}

 virtual /*public*/ Measurement* convert(Reading* r, Measurement* last) {return NULL;}
};
}
#endif // CALCULATOR_H
