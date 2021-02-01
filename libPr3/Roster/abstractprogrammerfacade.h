#ifndef ABSTRACTPROGRAMMERFACADE_H
#define ABSTRACTPROGRAMMERFACADE_H
#include "programmer.h"

class ProgrammingMode;
class PropertyChangeListener;
class AbstractProgrammerFacade : public QObject, public Programmer
{
    Q_OBJECT
 Q_INTERFACES(Programmer)
public:
   // explicit AbstractProgrammerFacade(QObject *parent = 0);
    /*public*/ AbstractProgrammerFacade(Programmer* prog, QObject *parent = 0);
    /*public*/ QString decodeErrorCode(int code);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(QString CV, int val, ProgListener* p)throw (ProgrammerException);
    /*public*/ ProgrammingMode* getMode();
    /*public*/ QList<QString> getSupportedModes();
    /*public*/ void setMode(ProgrammingMode* p);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);

signals:

public slots:
 /*public*/ virtual void programmingOpReply(int value, int status) =0;

protected:
    /*protected*/ Programmer* prog;

};

#endif // ABSTRACTPROGRAMMERFACADE_H
