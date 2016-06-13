#include "turnout.h"
const int Turnout::DIRECT = 1;
const int Turnout::ONESENSOR = 16;
const int Turnout::TWOSENSOR = 32;
const int Turnout::INDIRECT = 4;
const int Turnout::MONITORING     = 8;
const int Turnout::EXACT    = 2;
//const /*static*/ int Turnout::CLOSED       = 0x02;
//const /*static*/ int Turnout::THROWN       = 0x04;


//Turnout::Turnout(QObject *parent)
//{
// _state = UNKNOWN;
// _knownState = UNKNOWN;
//}
//int Turnout::getKnownState() const {return _knownState;}
//void Turnout::setCommandedState(int s) const
//{

//}
