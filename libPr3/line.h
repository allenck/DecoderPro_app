#ifndef LINE_H
#define LINE_H

#include <QObject>
#include "control.h"

class LineListener;
class Control;
class Line : public QObject
{
 Q_OBJECT
public:
 explicit Line(QObject *parent = 0);
 template <class T>
 /*public*/ /*static*/ class Info
 {
  /*private*/ /*final*/ T lineClass;
  /*public*/ Info(T lineClass);
  /*public*/ T getLineClass();
  /*public*/ bool matches(Info<T>* info);
  /*public*/ QString toString();
  /*public*/ void close();

 }; // class Info
 template<class T>
 /*public*/ Info<T>* getLineInfo();
 virtual /*public*/ void open() /*throws LineUnavailableException*/;
 virtual /*public*/ void close();
 virtual /*public*/ bool isOpen();
 virtual /*public*/ QList<Control*> getControls();
 virtual /*public*/ bool isControlSupported(Control::Type* control);
 virtual /*public*/ Control* getControl(Control::Type* control);
 virtual /*public*/ void addLineListener(LineListener* listener);

signals:

public slots:

};

#endif // LINE_H
