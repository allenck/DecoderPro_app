#ifndef MEMORY_H
#define MEMORY_H
#include <QObject>
#include "abstractnamedbean.h"

class LIBPR3SHARED_EXPORT Memory : public AbstractNamedBean
{
public:
    Memory(QString sysName, QString usrName="", QObject* parent = 0);

    /**
     * Get the stored value.  The type of this depends on what
     * was stored...
     */
    virtual QVariant getValue() {return QVariant();}

    /**
     * Set the value.  Any type of Object can be stored,
     * but various utilities use the toString method of the
     * stored Object.
     */
    virtual void setValue(QVariant ) {}
};
Q_DECLARE_INTERFACE(Memory, "Memory")
#endif // MEMORY_H
