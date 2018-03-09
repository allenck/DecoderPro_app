#ifndef SPROGCSSERIALDRIVERADAPTER_H
#define SPROGCSSERIALDRIVERADAPTER_H
#include "serialdriveradapter.h"

namespace Sprog
{
 class SprogCSSerialDriverAdapter : public SerialDriverAdapter
 {
 public:
  SprogCSSerialDriverAdapter(QObject* parent = 0);
  QT_DEPRECATED static /*public*/ SprogCSSerialDriverAdapter* instance();

 };
}
#endif // SPROGCSSERIALDRIVERADAPTER_H
