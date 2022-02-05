#ifndef ATOMICBOOLEAN_H
#define ATOMICBOOLEAN_H

#include <QObject>
#include <QAtomicInteger>

class AtomicBoolean : public QObject
{
  Q_OBJECT
 public:
  explicit AtomicBoolean(QObject *parent = nullptr);
  /*public*/  AtomicBoolean(bool bln, QObject *parent = nullptr);
  /*public*/  /*final*/ bool get();
  /*public*/  /*final*/ bool compareAndSet(bool bln, bool bln1);
  /*public*/  bool weakCompareAndSet(bool bln, bool bln1);
  /*public*/  /*final*/ void set(bool bln) ;
  /*public*/  /*final*/ void lazySet(bool bln);
  /*public*/  /*final*/ bool getAndSet(bool bln);
  /*public*/  QString toString();
 signals:

 private:
  /*private*/ static /*final*/ long serialVersionUID;// = 4654671469794556979L;
  /*private*/ static /*final*/ QAtomicInteger<int> unsafe;
  /*private*/ static /*final*/ long valueOffset;
  /*private*/ volatile int value;
};

#endif // ATOMICBOOLEAN_H
