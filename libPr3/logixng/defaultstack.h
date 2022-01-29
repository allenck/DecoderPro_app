#ifndef DEFAULTSTACK_H
#define DEFAULTSTACK_H

#include <QObject>
#include "stack.h"
#include <QVector>
#include <QVariant>

class DefaultStack : public QObject, public Stack
{
  Q_OBJECT
 public:
  explicit DefaultStack(QObject *parent = nullptr) : QObject(parent){}
  /*public*/  void push(QVariant value)override;
  /*public*/  QVariant pop() override;
  /*public*/  QVariant getValueAtIndex(int index)override;
  /*public*/  void setValueAtIndex(int index, QVariant value)override;
  /*public*/  int getCount()override;
  /*public*/  void setCount(int newCount)override;

 private:
  static /*final*/const  int INITIAL_SIZE = 100;
  static /*final*/const  int GROW_SIZE = 100;
  int _size;
  int _count;
  /*private*/ QVector<QVariant> _stack = QVector<QVariant>(INITIAL_SIZE);

 signals:

};

#endif // DEFAULTSTACK_H
