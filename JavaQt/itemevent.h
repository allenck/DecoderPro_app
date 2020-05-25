#ifndef ITEMEVENT_H
#define ITEMEVENT_H

#include <QObject>
#include <QVariant>

class ItemEvent : public QObject
{
 Q_OBJECT
 QObject* source;
 QVariant item;
public:
 explicit ItemEvent(QObject* source, QObject *parent = nullptr) : QObject(parent) {this->source = source;}
 /*public*/ static /*final*/ const int ITEM_FIRST = 701;
 /*public*/ static /*final*/ const int ITEM_LAST = 701;
 /*public*/ static /*final*/ const int ITEM_STATE_CHANGED = 701;
 /*public*/ static /*final*/ const int SELECTED = 1;
 /*public*/ static /*final*/ const int DESELECTED = 2;
 /*public*/ int getStateChange() {
         // <editor-fold defaultstate="collapsed" desc="Compiled Code">
         /* 0: aload_0
          * 1: getfield      java/awt/event/ItemEvent.stateChange:I
          * 4: ireturn
          *  */
         // </editor-fold>
  return SELECTED;
     }
 QObject* getSource() {return source;}
 void setSource(QObject* source) {this->source = source;}
 QVariant getItem() { return item;}
 void setItem(QVariant v) {this->item = v;}

signals:

public slots:
};

#endif // ITEMEVENT_H
