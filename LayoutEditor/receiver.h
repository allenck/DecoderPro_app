#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QVector3D>

namespace RPS
{


class Receiver : public QObject
{
 Q_OBJECT
public:
 explicit Receiver(QVector3D position, QObject *parent = nullptr);
 /*public*/ void setPosition(QVector3D position);
 /*public*/ QVector3D getPosition();
 /*public*/ bool isActive();
 /*public*/ void setActive(bool active);
 /*public*/ int getLastTime();
 /*public*/ void setLastTime(int m);
 /*public*/ int getMinTime();
 /*public*/ void setMinTime(int m);
 /*public*/ int getMaxTime() ;
 /*public*/ void setMaxTime(int m);

signals:

public slots:

  private:
  /*private*/ QVector3D position;
  bool active;// = false;
  int max;// = 99999;
  int min;// = 0;
  int last;// = -1;

};
}
#endif // RECEIVER_H
