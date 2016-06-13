#ifndef VSDMANAGEREVENT_H
#define VSDMANAGEREVENT_H

#include <QObject>
#include <QVariant>
#include "appslib_global.h"

class VSDecoderManager;
class APPSLIBSHARED_EXPORT VSDManagerEvent : public QObject
{
 Q_OBJECT
public:
 explicit VSDManagerEvent(QObject *parent = 0);
 /*public*/  enum EventType {

     NONE, DECODER_LIST_CHANGE, PROFILE_LIST_CHANGE
 };  // propertyChangeEvents fired by the Manager.
 /*public*/ VSDManagerEvent(VSDecoderManager* source);
 /*public*/ VSDManagerEvent(VSDecoderManager* source, VSDManagerEvent::EventType t);
 /*public*/ VSDManagerEvent(VSDecoderManager* source, VSDManagerEvent::EventType t, QVariant d);
 /*public*/ void setType(VSDManagerEvent::EventType t);
 /*public*/ VSDManagerEvent::EventType getType();
 /*public*/ QVariant getData();

signals:

public slots:
private:
 VSDManagerEvent::EventType type;
 QVariant data;


};

#endif // VSDMANAGEREVENT_H
