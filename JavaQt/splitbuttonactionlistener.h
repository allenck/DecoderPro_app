#ifndef SPLITBUTTONACTIONLISTENER_H
#define SPLITBUTTONACTIONLISTENER_H
#include <qobject.h>
#include "eventlistener.h"
#include "actionevent.h"

/*public*/ /*interface*/class SplitButtonActionListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public slots:
  virtual  /*public*/ void buttonClicked(JActionEvent* ae) = 0;

  virtual  /*public*/ void splitButtonClicked(JActionEvent* ae) =0;
};

#endif // SPLITBUTTONACTIONLISTENER_H
