#include "atomicboolean.h"

///*public*/  class AtomicBoolean implements Serializable {

    /*private*/ /*static*/ /*final*/ long AtomicBoolean::serialVersionUID = 4654671469794556979L;
    /*private*/ /*static*/ /*final*/ QAtomicInteger<int> unsafe;
    /*private*/ /*static*/ /*final*/ long AtomicBoolean::valueOffset;


    /*public*/  AtomicBoolean::AtomicBoolean(bool initialValue, QObject* parent) :  QObject(parent) {
        value = initialValue ? 1 : 0;
    }

    /*public*/  AtomicBoolean::AtomicBoolean(QObject* parent) :  QObject(parent){
    }

    /*public*/  /*final*/ bool AtomicBoolean::get() {
        return value != 0;
    }

    /*public*/  /*final*/ bool AtomicBoolean::compareAndSet(bool expect, bool update) {
     int e = expect ? 1 : 0;
     int u = update ? 1 : 0;
     //return unsafe.compareAndSwapInt(this, valueOffset, e, u);    }
     return unsafe.testAndSetAcquire(e, u);
    }

    /*public*/  bool AtomicBoolean::weakCompareAndSet(bool expect, bool update) {
      int e = expect ? 1 : 0;
      int u = update ? 1 : 0;
      //return unsafe.compareAndSwapInt(this, valueOffset, e, u);
      return  unsafe.testAndSetRelaxed(e,u);
    }

    /*public*/  /*final*/ void AtomicBoolean::set(bool newValue) {
     value = newValue ? 1 : 0;
    }

    /*public*/  /*final*/ void AtomicBoolean::lazySet(bool newValue) {
     int v = newValue ? 1 : 0;
     //unsafe.putOrderedInt(this, valueOffset, v);
     unsafe.store(v);
    }

    /*public*/  /*final*/ bool AtomicBoolean::getAndSet(bool newValue) {
     for (;;) {
         bool current = get();
         if (compareAndSet(current, newValue))
             return current;
     }
    }

    /*public*/  QString AtomicBoolean::toString() {
       //return Boolean.toString(get());
     return get()? "true":"false";
    }
