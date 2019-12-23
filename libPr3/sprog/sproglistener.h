#ifndef SPROGLISTENER_H
#define SPROGLISTENER_H
#include "eventlistener.h"

namespace Sprog {
 class SprogMessage;
 class SprogReply;
 class SprogListener : public QObject, public EventListener
 {
  Q_OBJECT
  Q_INTERFACES(EventListener)
 public:
  SprogListener(QObject* parent = 0);
  QObject* self() {return (QObject*)this;}

 public slots:
  virtual /*public*/ void notifyMessage(SprogMessage* /*m*/) {}

  virtual /*public*/ void notifyReply(SprogReply* /*m*/) {}

 };
}
#endif // SPROGLISTENER_H
