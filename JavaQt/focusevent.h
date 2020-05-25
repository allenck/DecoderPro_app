#ifndef FOCUSEVENT_H
#define FOCUSEVENT_H
#include "eventlistener.h"
#include "focusevent.h"
#include<QFocusEvent>
#include <QObject>

class FocusEvent :  public QObject
{
 Q_OBJECT
QFocusEvent* e;

public:
 FocusEvent() : QObject() {this->e = e;}
 QObject* self() {return (QObject*)this;}
public slots:

};
#endif // FOCUSEVENT_H
