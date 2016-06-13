#ifndef VSDECODEREVENT_H
#define VSDECODEREVENT_H

#include <QObject>
#include <QVariant>
#include "libPr3_global.h"

class VSDecoder;
class LIBPR3SHARED_EXPORT VSDecoderEvent : public QObject
{
 Q_OBJECT
public:
 //explicit VSDecoderEvent(QObject *parent = 0);
 /*public*/ /*static*/ enum EventType {

     NONE, LOCATION_CHANGE
 };  // propertyChangeEvents fired by the Manager.
 /*public*/ VSDecoderEvent(VSDecoder* source,QObject *parent = 0) ;
 /*public*/ VSDecoderEvent(VSDecoder* source, EventType t,QObject *parent = 0);
 /*public*/ VSDecoderEvent(VSDecoder* source, EventType t, QVariant d, QObject *parent = 0);
 /*public*/ void setType(EventType t);
 /*public*/ EventType getType();
 /*public*/ QVariant getData();

signals:

public slots:
private:
 EventType type;
 QVariant data;
 VSDecoder* source;

};

#endif // VSDECODEREVENT_H
