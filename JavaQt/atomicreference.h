#ifndef ATOMICREFERENCE_H
#define ATOMICREFERENCE_H
#include <QAtomicPointer>
template <class E>
class AtomicReference
{
 public:
  AtomicReference<E>() {}
  /*public*/  /*final*/ E get() {return value;}
  /*public*/  /*final*/ void set(E newValue) {value = newValue; }

 private:
  /*private*/ volatile E value;
  /*private*/ static /*final*/ QAtomicPointer<E> unsafe;
};
#endif // ATOMICREFERENCE_H
