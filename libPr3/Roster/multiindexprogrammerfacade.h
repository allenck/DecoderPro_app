#ifndef MULTIINDEXPROGRAMMERFACADE_H
#define MULTIINDEXPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "logger.h"

class MultiIndexProgrammerFacade : public AbstractProgrammerFacade
{
    Q_OBJECT
public:
    //explicit MultiIndexProgrammerFacade(QObject *parent = 0);
    /*public*/ MultiIndexProgrammerFacade(Programmer* prog, QString indexPI, QString indexSI, bool cvFirst, QObject* parent = 0);
    enum ProgState { PROGRAMMING, FINISHREAD, FINISHWRITE, NOTPROGRAMMING };
    /*synchronized*/ /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) ;
    /*synchronized*/ /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException) ;
    // internal method to remember who's using the programmer
    /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);
public slots:
    /*public*/ void programmingOpReply(int value, int status);


signals:

public slots:
private:
    QString indexPI;
    QString indexSI;
    bool cvFirst;
    // members for handling the programmer interface

    int _val;	// remember the value being read/written for confirmative reply
    QString _cv;	// remember the cv number being read/written
    int valuePI;  //  value to write to PI or -1
    int valueSI;  //  value to write to SI or -1
    void parseCV(QString cv);
    /*private*/ ProgListener* _usingProgrammer;// = NULL;
    ProgState state;// = ProgState::NOTPROGRAMMING;
    Logger* log;

};

#endif // MULTIINDEXPROGRAMMERFACADE_H
