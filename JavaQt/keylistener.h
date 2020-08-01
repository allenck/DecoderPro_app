#ifndef KEYLISTENER_H
#define KEYLISTENER_H
#include "eventlistener.h"
#include <QKeyEvent>

/*public*/ /*interface*/class  KeyListener : public EventListener {

  /*public*/ virtual void keyTyped(QKeyEvent* ke) {}

  /*public*/ virtual void keyPressed(QKeyEvent* ke){}

  /*public*/ virtual void keyReleased(QKeyEvent* ke) {}
};
Q_DECLARE_INTERFACE(KeyListener, "KeyListener")
#endif // KEYLISTENER_H
