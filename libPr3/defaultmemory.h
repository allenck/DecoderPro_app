#ifndef DEFAULTMEMORY_H
#define DEFAULTMEMORY_H
#include "abstractmemory.h"

class DefaultMemory : public AbstractMemory
{
    Q_OBJECT
public:
    explicit DefaultMemory(QString sysName, QString userName="", QObject *parent = 0);
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
    /*public*/ int getState();
    /*public*/ void setState(int s);

signals:
    
public slots:
    
};

#endif // DEFAULTMEMORY_H
