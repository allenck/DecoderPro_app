#include "jseparator.h"

JSeparator::JSeparator(enum ORIENTATION e , QWidget *parent) :
    QFrame(parent)
{
 setObjectName(QString::fromUtf8("line"));
 setGeometry(QRect(10, 30, 571, 16));
 if(e == HORIZONTAL)
 {
  setGeometry(QRect(10, 30, 571, 16));
  setFrameShape(QFrame::HLine);
 }
 else
 {
  setGeometry(QRect(10, 30, 571, 16));
  setFrameShape(QFrame::VLine);
 }
 setFrameShadow(QFrame::Sunken);
}
