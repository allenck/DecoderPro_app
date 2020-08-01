#ifndef KEYADAPTER_H
#define KEYADAPTER_H

#include <QObject>
#include <QKeyEvent>
class KeyAdapter : public QObject
{
  Q_OBJECT
 public:
  explicit KeyAdapter(QObject *parent = nullptr);
 public slots:
  /*public*/ virtual void keyTyped(QKeyEvent* ke);
  /*public*/ virtual void keyPressed(QKeyEvent* ke);
  /*public*/ virtual void keyReleased(QKeyEvent* ke);

 signals:

 public slots:
};

#endif // KEYADAPTER_H
