#ifndef SPROGVERSIONLISTENER_H
#define SPROGVERSIONLISTENER_H
#include "sprogversion.h"
#include "eventlistener.h"
namespace Sprog
{
 /**
  * Defines the interface for listening to SPROG version replies.
  *
  * @author	Andrew Crosland Copyright (C) 2012
  *
  */
 /*public*/ /*interface*/class SprogVersionListener : public QObject, public EventListener
 {
  Q_OBJECT
  Q_INTERFACES(EventListener)
  public:
   SprogVersionListener();
   QObject* self() {return (QObject*)this;}
  public slots:
   virtual /*public*/ void notifyVersion(SprogVersion* /*v*/) {}
 };
}
#endif // SPROGVERSIONLISTENER_H
