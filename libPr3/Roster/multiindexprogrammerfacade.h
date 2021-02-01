#ifndef MULTIINDEXPROGRAMMERFACADE_H
#define MULTIINDEXPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "logger.h"

class MultiIndexProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
    Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
    //explicit MultiIndexProgrammerFacade(QObject *parent = 0);
    /*public*/ MultiIndexProgrammerFacade(Programmer* prog, QString indexPI, QString indexSI, bool cvFirst, bool skipDupIndexWrite, QObject* parent = 0);
    enum ProgState { PROGRAMMING, FINISHREAD, FINISHWRITE, FINISHCONFIRM,NOTPROGRAMMING };
    /*synchronized*/ /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) ;
    /*synchronized*/ /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException) ;
    /*public*/ QObject* self() {return (QObject*)this;}
protected:
    // internal method to remember who's using the programmer
    /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);
public slots:
    /*public*/ void programmingOpReply(int value, int status);


signals:

public slots:
private:
    QString defaultIndexPI;
    QString defaultIndexSI;

    QString indexPI;
    QString indexSI;
    bool cvFirst;
    bool skipDupIndexWrite;
    long maxDelay = 1000;  // max mSec since last successful end-of-operation for skipDupIndexWrite; longer delay writes anyway

    // members for handling the programmer interface

    int _val;	// remember the value being read/written for confirmative reply
    QString _cv;	// remember the cv number being read/written
    int valuePI;  //  value to write to PI or -1
    int valueSI;  //  value to write to SI or -1
    // remember last operation for skipDupIndexWrite
    int lastValuePI = -1;  // value written in last operation
    int lastValueSI = -1;  // value written in last operation
    qint64 lastOpTime = -1;  // time of last complete
    void parseCV(QString cv);
    /*private*/ ProgListener* _usingProgrammer;// = NULL;
    ProgState state;// = ProgState::NOTPROGRAMMING;
    static Logger* log;
    bool hasAlternateAddress(QString cv);
    QString getAlternateAddress(QString cv);
    int getAlternateValue(QString cv);
    bool useCachePiSi();
friend class MultiIndexProgrammerFacadeTest;
};

#endif // MULTIINDEXPROGRAMMERFACADE_H
