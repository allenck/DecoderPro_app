#ifndef ABSTRACTPROGRAMMERFACADE_H
#define ABSTRACTPROGRAMMERFACADE_H
#include "programmer.h"

class ProgrammingMode;
class PropertyChangeListener;
class AbstractProgrammerFacade : public Programmer
{
    Q_OBJECT
public:
   // explicit AbstractProgrammerFacade(QObject *parent = 0);
    /*public*/ AbstractProgrammerFacade(Programmer* prog, QObject *parent = 0);
    /*public*/ QString decodeErrorCode(int code);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void writeCV(int CV, int val, ProgListener*p) throw (ProgrammerException);
    /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void readCV(int CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(int CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(QString CV, int val, ProgListener* p)throw (ProgrammerException);
    /*public*/ ProgrammingMode* getMode();
    /*public*/ QList<ProgrammingMode*> getSupportedModes();
    /*public*/ void setMode(ProgrammingMode* p);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);

signals:

public slots:
protected:
    /*protected*/ Programmer* prog;

};

#endif // ABSTRACTPROGRAMMERFACADE_H
