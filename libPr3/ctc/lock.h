#ifndef LOCK_H
#define LOCK_H

/*public*/ class Lock {

  virtual /*public*/ void lock() {}

//  virtual   /*public*/ void lockInterruptibly() throw (InterruptedException);

//  virtual   /*public*/ bool tryLock();

//  virtual   /*public*/ bool tryLock(long l, TimeUnit tu) throw (InterruptedException);

  virtual   /*public*/ void unlock() {}

// virtual    /*public*/ Condition newCondition();
};
Q_DECLARE_INTERFACE(Lock, "Lock")

#endif // LOCK_H
