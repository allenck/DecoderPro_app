#include "defaultmemory.h"
#include "exceptions.h"

DefaultMemory::DefaultMemory(QString sysName, QString userName, QObject *parent) :
    AbstractMemory(sysName.toUpper(), userName, parent)
{
}
/**
 * Concrete implementation of the Reporter interface for the Internal system.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 17977 $
 */
///*public*/ class DefaultMemory extends AbstractMemory {

//    /*public*/ DefaultMemory(String systemName) {
//        super(systemName);
//    }

//    /*public*/ DefaultMemory(String systemName, String userName) {
//        super(systemName, userName);
//    }

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
/*public*/ int DefaultMemory::getState()
{
 try
 {
  bool bOk=false;
  QString val = getValue().toString();
  int i = val.toInt(&bOk);
  if(!bOk) throw new NumberFormatException();
  return i;
 }
//        return Integer.valueOf(getValue().toString()).intValue(); }
 catch (NumberFormatException* ex1) { return -1; }
//		catch (java.lang.NullPointerException ex2) { return -1; }

}
/*public*/ void DefaultMemory::setState(int s)
{
 setValue(QString::number(s));
}
