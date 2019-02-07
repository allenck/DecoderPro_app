#ifndef LINE_H
#define LINE_H

#include <QObject>
#include "control.h"

class LineListener;
class Control;
class /*interface*/ Line : public QObject
{
 Q_OBJECT
public:
 explicit Line(QObject *parent = 0);
 /*public*/ /*static*/ class Info
 {
  /*private*/ /*final*/ QString lineClass;
 public:
  /*public*/ Info(QString lineClass);
  /*public*/ virtual QString getLineClass();
  /*public*/ virtual bool matches(Info* info);
  /*public*/ virtual QString toString();
  /*public*/ virtual void close() {}

 }; // class Info
 /*public*/ virtual Info* getLineInfo();
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
