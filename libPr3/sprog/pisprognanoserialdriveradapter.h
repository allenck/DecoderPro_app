#ifndef PISPROGNANOSERIALDRIVERADAPTER_H
#define PISPROGNANOSERIALDRIVERADAPTER_H
#include "sprogserialdriveradapter.h"

namespace Sprog
{
 class PiSprogNanoSerialDriverAdapter : public SprogSerialDriverAdapter
 {
 public:
  PiSprogNanoSerialDriverAdapter(QObject* parent);
  /*public*/ QStringList validBaudRates();

  QT_DEPRECATED static /*public*/ PiSprogNanoSerialDriverAdapter* instance();

 };
}
#endif // PISPROGNANOSERIALDRIVERADAPTER_H
