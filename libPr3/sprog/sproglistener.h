#ifndef SPROGLISTENER_H
#define SPROGLISTENER_H
#include "eventlistener.h"

namespace Sprog {
 class SprogMessage;
 class SprogReply;
 class SprogListener : public EventListener
 {
  Q_OBJECT
 public:
  SprogListener(QObject* parent = 0);

 public slots:
  virtual /*public*/ void notifyMessage(SprogMessage* /*m*/) {}

  virtual /*public*/ void notifyReply(SprogReply* /*m*/) {}

 };
}
#endif // SPROGLISTENER_H
