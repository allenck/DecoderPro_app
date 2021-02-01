#include "abstractprogrammerfacade.h"

//AbstractProgrammerFacade::AbstractProgrammerFacade(QObject *parent) :
//    Programmer(parent)
//{
//}
/**
 * Common implementations of the Programmer interface
 * for making Programmer facade classes.
 *
 * @author	Bob Jacobsen  Copyright (C) 2013
 * @version     $Revision: 28270 $
 */
// /*public*/ abstract class AbstractProgrammerFacade implements Programmer {


/*public*/ AbstractProgrammerFacade::AbstractProgrammerFacade(Programmer* prog, QObject *parent) :
    QObject(parent)
{
    this->prog = prog;
}

//@Override
/*public*/ QString AbstractProgrammerFacade::decodeErrorCode(int code) {
    return prog->decodeErrorCode(code);
}

//@Override
/*public*/ /*synchronized*/ void AbstractProgrammerFacade::addPropertyChangeListener(PropertyChangeListener* l)
{
    prog->addPropertyChangeListener(l);
}

//@Override
/*public*/ /*synchronized*/ void AbstractProgrammerFacade::removePropertyChangeListener(PropertyChangeListener* l)
{
    prog->removePropertyChangeListener(l);
}

//@Override
/*public*/ void AbstractProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
    prog->writeCV(CV, val, p);
}
//@Override
/*public*/ void AbstractProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
{
    prog->readCV(CV, p);
}

//@Override
/*public*/ void AbstractProgrammerFacade::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
    prog->confirmCV(CV, val, p);
}

//@Override
/*public*/ ProgrammingMode* AbstractProgrammerFacade::getMode() { return prog->getMode(); }
//@Override
/*public*/ QList<QString> AbstractProgrammerFacade::getSupportedModes()
{ return prog->getSupportedModes(); }
//@Override
/*public*/ void AbstractProgrammerFacade::setMode(ProgrammingMode* p)

{ prog->setMode(p); }

//@Override
/*public*/ bool AbstractProgrammerFacade::getCanRead()
{ return prog->getCanRead(); }
//@Override
/*public*/ bool AbstractProgrammerFacade::getCanRead(QString addr)
{ return prog->getCanRead(addr); }

//@Override
/*public*/ bool AbstractProgrammerFacade::getCanWrite()
{ return prog->getCanWrite(); }
//@Override
/*public*/ bool AbstractProgrammerFacade::getCanWrite(QString addr)
{ return prog->getCanWrite(addr); }
