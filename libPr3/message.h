#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>

/**
 * Basic interface for messages to and from the layout hardware
 *
 * @author jake Copyright 2008
 * @version   $Revision: 17977 $
 */
/*public*/ /*interface*/ class Message : public QObject
{
 Q_OBJECT
 public:
 Message(QObject* parent=0) : QObject(parent) {}
    virtual int getElement(int n) = 0;

    virtual int getNumDataElements() = 0;

    virtual void setElement(int n, int v) = 0;

 virtual QString toString() {return "";}
 /*
  * @return a human readable representation of the message.
  */
 /*public*/ /*default*/ QString toMonitorString(){
       return toString();
 }

};

#endif // MESSAGE_H
