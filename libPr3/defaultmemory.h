#ifndef DEFAULTMEMORY_H
#define DEFAULTMEMORY_H
#include "abstractmemory.h"

class DefaultMemory : public AbstractMemory
{
    Q_OBJECT
public:
  explicit DefaultMemory(QString sysName, QString userName="", QObject *parent = 0)
   : AbstractMemory(sysName, userName, parent){
  setObjectName("DefaultMemory");}
    /**
     * Provide generic access to internal state.
     *<P>
     * This generally shouldn't be used by Java code; use
     * the class-specific form instead. (E.g. getCommandedState in Turnout)
     * This provided to make Jython
     * script access easier to read.
     * <P>
     * If the current value can be reduced to an integer, that
     * is returned, otherwise a value of -1 is returned.
     */
  /*public*/ int getState()override {
   //try {
    bool ok;
       int i = getValue().toInt(&ok);
   if(!ok) {
       return -1;
   }
   return i;
  }
  /*public*/ void setState(int s) override{
   setValue( QString::number(s));

  }

signals:
    
public slots:
    
};

#endif // DEFAULTMEMORY_H
