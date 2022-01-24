#ifndef TWOINDEXPROGRAMMERFACADE_H
#define TWOINDEXPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "logger.h"


class TwoIndexTcsProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
    Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
    //explicit TwoIndexProgrammerFacade(QObject *parent = 0);
    /*public*/ TwoIndexTcsProgrammerFacade(Programmer* prog, QObject *parent = 0);

    enum ProgState {
        PROGRAMMING,    // doing last read/write, next reply is end
        DOSIFORREAD,    // reading, write to SI next
        DOSTROBEFORREAD,// reading, write to strobe CV next
        DOMSBFORREAD,   // reading, write to MSB next
        DOLSBFORREAD,   // reading, write to LSB next
        DOREADFIRST,    // reading, get MSB next
        FINISHREAD,     // reading, read CV (LSB) next
        DOSIFORWRITE,   // writing, write to SI next
        DOWRITEFIRST,   // writing, write CV (MSB) next
        FINISHWRITE,    // writing, write CV (LSB) next
        NOTPROGRAMMING  // idle, doing nothing, no reply expected
    };
    static /*final*/ QString indexPI;// = "201";
    static /*final*/ QString indexSI;// = "202";
    static /*final*/ QString valMSB;//  = "203";
    static /*final*/ QString valLSB;//  = "204";
    static /*final*/ QString readStrobe;// = "204";  // CV that has to be written before read
    static /*final*/ QString format2Flag;// = "T2CV"; // flag to indicate this type of CV
    static /*final*/ QString format3Flag;// = "T3CV"; // flag to indicate this type of CV
    static /*final*/ int readOffset;// = 100;
    /*synchronized*/ /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void confirmCV(QString CV, int val, ProgListener* p)throw (ProgrammerException) ;
    /*synchronized*/ /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void programmingOpReply(int value, int status);
    /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
private:
    ProgState state;// = ProgState::NOTPROGRAMMING;
    // members for handling the programmer interface

    int _val;	// remember the value being read/written for confirmative reply
    QString _cv;	// remember the cv number being read/written
    int valuePI;   //  value to write to PI or -1
    int valueSI;   //  value to write to SI or -1
    int valueMSB;  //  value to write to MSB or -1
    int valueLSB;  //  value to write to LSB or -1
    void parseCV(QString cv) throw (IllegalArgumentException);
    /*private*/ ProgListener* _usingProgrammer;// = NULL;
    int upperByte;
    Logger* log;

protected:
    /*protected*/ void useProgrammer(ProgListener* p);

};

#endif // TWOINDEXPROGRAMMERFACADE_H
