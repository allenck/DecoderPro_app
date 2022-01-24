#ifndef SPROGCSSERIALDRIVERADAPTER_H
#define SPROGCSSERIALDRIVERADAPTER_H
#include "sprogserialdriveradapter.h"

namespace Sprog
{
 class SprogCSSerialDriverAdapter : public SprogSerialDriverAdapter
 {
 public:
  SprogCSSerialDriverAdapter(QObject* parent = 0);
  QT_DEPRECATED static /*public*/ SprogCSSerialDriverAdapter* instance();

 };
}
#endif // SPROGCSSERIALDRIVERADAPTER_H
