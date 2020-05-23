#ifndef ITEMEVENT_H
#define ITEMEVENT_H

#include <QObject>

class ItemEvent : public QObject
{
 Q_OBJECT
public:
 explicit ItemEvent(QObject *parent = nullptr);

signals:

public slots:
 /*public*/ int getStateChange() {
         // <editor-fold defaultstate="collapsed" desc="Compiled Code">
         /* 0: aload_0
          * 1: getfield      java/awt/event/ItemEvent.stateChange:I
          * 4: ireturn
          *  */
         // </editor-fold>
     }
};

#endif // ITEMEVENT_H
