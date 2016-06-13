#include "abstractmemory.h"

AbstractMemory::AbstractMemory(QString systemName, QString userName, QObject* parent) :    Memory(systemName.toUpper(), userName, parent)
{
    _current = QVariant();
}
/**
 * Base for the Memory interface.
 * <P>
 * Implements the parameter binding support.
 * <P>
 * Note that we consider it an error for there to be more than one object
 * that corresponds to a particular physical Reporter on the layout.
 * <p>
 * Memory system names are always upper case.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 17977 $
 */
//public abstract class AbstractMemory extends AbstractNamedBean implements Memory, java.io.Serializable {

//    public AbstractMemory(String systemName) {
//        super(systemName.toUpperCase());
//    }

//    public AbstractMemory(String systemName, String userName) {
//        super(systemName.toUpperCase(), userName);
//    }

/*public*/ QVariant AbstractMemory::getValue() {return _current;}

/**
 * Provide a general method for updating the report.
 */
/*public*/ void AbstractMemory::setValue(QVariant v)
{
 QVariant old = _current;
 _current = v;
 // notify
 firePropertyChange("value", old, _current);
 //emit propertyChange("value", old, _current);
}



