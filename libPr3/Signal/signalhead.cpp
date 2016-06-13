#include "signalhead.h"

SignalHead::SignalHead(QObject *parent) /*: NamedBean(parent)*/
{
}
const /*static*/ int SignalHead::DARK        = 0x00;
const /*static*/ int SignalHead::RED         = 0x01;
const /*static*/ int SignalHead::FLASHRED    = 0x02;
const /*static*/ int SignalHead::YELLOW      = 0x04;
const /*static*/ int SignalHead::FLASHYELLOW = 0x08;
const /*static*/ int SignalHead::GREEN       = 0x10;
const /*static*/ int SignalHead::FLASHGREEN  = 0x20;
const /*static*/ int SignalHead::LUNAR       = 0x40;
const /*static*/ int SignalHead::FLASHLUNAR  = 0x80;
const /*static*/ int SignalHead::HELD 		= 0x0100;
